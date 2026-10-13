// High-level emulation of the GameCube DSP audio microcode used by MusyX.
//
// Every 5 ms MusyX (hw_dspctrl.c, salBuildCommandList) builds a command list
// and mails its address to the DSP. The microcode mixes all voices of each
// studio into nine 160-sample s32 buses (main L/R/S, aux A L/R/S, aux B L/R/S),
// exchanges aux buses with the CPU effect callbacks, sums the master studios and
// writes the final stereo frame into an AI DMA buffer. This file interprets
// that list. The command set and parameters follow exactly what
// salBuildCommandList emits:
//
//   0  SETUP            spb            reset the buses to the studio's depop ramps
//   1  DL_AND_VOL_MIX   addr vol volA volB
//                                      mix another studio's L/R/S output (previous
//                                      frame) into main/auxA/auxB with volumes
//   2  PB_ADDR          addr           first voice parameter block (PB)
//   3  PROCESS                         render the PB list (linked by nextHi/Lo)
//   4  MIX_AUXA         write read     store aux A buses for the CPU, add the
//                                      CPU-processed buffer into main
//   5  MIX_AUXB         write read     same for aux B
//   6  UPLOAD_LRS       addr           store main L/R/S (the studio's output)
//   9  MIX_AUXB_NOWRITE addr           add L/R/S from memory into main
//   13 MORE             addr size      continue with the list at addr
//   14 OUTPUT           surr dest      store main S to surr, clamp main L/R to dest
//   15 END
//   16 MIX_AUXB_LR      write read     DPL2: store aux B L/R/S, fold the previous
//                                      frame's aux B L/R into main L/R
//   17 SET_OPPOSITE_LR  addr           main L = -S', R = +S' (S' = last frame's
//                                      surround), S = 0
//   18 COMPRESSOR       4 words        (MusyX >= 2.0.1; not emulated)
//
// Memory: every address is a 32-bit "physical" address = a game-heap offset
// (port_heap_virt). PBs, studio buffers and command lists are written natively
// by the CPU, so they are read as native u16/s32. Sample data lives in ARAM
// (aurora's host buffer) and is big-endian disc data.
//
// Voices are rendered in five 32-sample sub-frames; before each, the PB's
// update list (pairs of {PB word offset, value}) for that sub-frame is applied,
// which is how MusyX schedules envelope, pitch, start/stop and ramp changes.
// Sample-rate conversion uses a 4-point cubic (polyphase mode; the DSP-ROM
// coefficient tables aren't available), linear, or none, as srcSelect asks.

#include "dsp_ax.h"

#include <dolphin/ar.h>

#include "port/game_heap.h"

extern "C" {
#include "musyx/musyx.h"
#include "musyx/voice.h"
}

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>

static_assert(sizeof(_PBMIX) == 0x24, "PB mixer layout");
static_assert(offsetof(_PB, state) == 0x0E, "PB layout");
static_assert(offsetof(_PB, mix) == 0x12, "PB layout");
static_assert(offsetof(_PB, ve) == 0x64, "PB layout");
static_assert(offsetof(_PB, addr) == 0x6E, "PB layout");
static_assert(offsetof(_PB, src) == 0xA6, "PB layout");
static_assert(sizeof(_SPB) == 0x36, "SPB layout");

namespace {

constexpr int kFrameSamples = 160; // 5 ms at 32 kHz
constexpr int kSubFrames = 5;
constexpr int kSubSamples = kFrameSamples / kSubFrames;

// Bus order matches the _SPB depop entries and the L/R/S buffer triplets in
// memory (L at +0, R at +160, S at +320 s32 entries).
enum Bus
{
    kMainL,
    kMainR,
    kMainS,
    kAuxAL,
    kAuxAR,
    kAuxAS,
    kAuxBL,
    kAuxBR,
    kAuxBS,
    kNumBuses
};

s32 s_bus[kNumBuses][kFrameSamples];
u32 s_pbAddr = 0;

// Debugging aids: MSSB_DSP_STATS=1 prints a line per second of audio;
// MSSB_DSP_VOICES=<n> lists the active voices every n frames (default 200,
// one second);
// MSSB_DSP_DUMP=<file> appends every output frame as raw s16 stereo PCM
// (32 kHz, native-endian).
struct Debug
{
    bool init = false;
    bool stats = false;
    FILE* dump = nullptr;
    u32 frames = 0;
    u32 voiceSubFrames = 0;
    u32 maxVoices = 0;
    u32 frameVoices = 0;
    s32 peak = 0;
} s_debug;

void debug_init()
{
    if (s_debug.init)
        return;
    s_debug.init = true;
    const char* stats = getenv("MSSB_DSP_STATS");
    s_debug.stats = stats != nullptr && stats[0] != '\0' && stats[0] != '0';
    if (const char* path = getenv("MSSB_DSP_DUMP"))
        s_debug.dump = fopen(path, "wb");
}

void debug_frame_done(const s16* out)
{
    if (s_debug.dump != nullptr && out != nullptr)
    {
        fwrite(out, sizeof(s16), kFrameSamples * 2, s_debug.dump);
        if (s_debug.frames % 200 == 0)
            fflush(s_debug.dump);
    }
    ++s_debug.frames;
    if (!s_debug.stats)
        return;
    if (out != nullptr)
        for (int i = 0; i < kFrameSamples * 2; i++)
            s_debug.peak = std::max(s_debug.peak, std::abs((s32)out[i]));
    s_debug.maxVoices = std::max(s_debug.maxVoices, s_debug.frameVoices);
    s_debug.frameVoices = 0;
    if (s_debug.frames % 200 == 0)
    {
        fprintf(stderr, "[dsp] %u frames: max %u voices/frame, %u voice-ms rendered, output peak %d\n",
                s_debug.frames, s_debug.maxVoices, s_debug.voiceSubFrames, s_debug.peak);
        s_debug.maxVoices = 0;
        s_debug.voiceSubFrames = 0;
        s_debug.peak = 0;
    }
}

void warn_once(const char* what, u32 value)
{
    static int s_count = 0;
    if (s_count < 16)
    {
        s_count++;
        fprintf(stderr, "[dsp] %s (0x%08X)\n", what, value);
    }
}

// Physical address -> host pointer; null if it isn't inside the game heap.
template <typename T>
T* mem(u32 addr)
{
    if (addr == 0)
        return nullptr;
    void* p = port_heap_virt(addr);
    if (!port_heap_contains(p))
    {
        warn_once("address outside the game heap", addr);
        return nullptr;
    }
    return static_cast<T*>(p);
}

inline s16 clamp16(s32 v)
{
    return (s16)std::clamp(v, -32768, 32767);
}

// ---------------------------------------------------------------------------
// Bus helpers

void store_lrs(u32 addr, int firstBus)
{
    s32* dst = mem<s32>(addr);
    if (dst == nullptr)
        return;
    for (int c = 0; c < 3; c++)
        memcpy(dst + c * kFrameSamples, s_bus[firstBus + c], sizeof(s_bus[0]));
}

void add_lrs_to_main(u32 addr, int channels)
{
    const s32* src = mem<const s32>(addr);
    if (src == nullptr)
        return;
    for (int c = 0; c < channels; c++)
        for (int i = 0; i < kFrameSamples; i++)
            s_bus[kMainL + c][i] += src[c * kFrameSamples + i];
}

void cmd_setup(u32 spbAddr)
{
    const _SPB* spb = mem<const _SPB>(spbAddr);
    if (spb == nullptr)
    {
        memset(s_bus, 0, sizeof(s_bus));
        return;
    }
    const u16* w = reinterpret_cast<const u16*>(spb);
    for (int b = 0; b < kNumBuses; b++)
    {
        // MusyX stores each start value with a native 32-bit write over the
        // Hi/Lo pair (DoDepopFade), so read it back the same way.
        s32 value;
        memcpy(&value, &w[b * 3], sizeof(value));
        s32 delta = (s16)w[b * 3 + 2];
        for (int i = 0; i < kFrameSamples; i++)
        {
            s_bus[b][i] = value;
            value += delta;
        }
    }
}

void cmd_dl_and_vol_mix(u32 addr, u16 vol, u16 volA, u16 volB)
{
    const s32* src = mem<const s32>(addr);
    if (src == nullptr)
        return;
    for (int c = 0; c < 3; c++)
    {
        for (int i = 0; i < kFrameSamples; i++)
        {
            s64 v = src[c * kFrameSamples + i];
            s_bus[kMainL + c][i] += (s32)((v * vol) >> 15);
            s_bus[kAuxAL + c][i] += (s32)((v * volA) >> 15);
            s_bus[kAuxBL + c][i] += (s32)((v * volB) >> 15);
        }
    }
}

void cmd_mix_aux(int firstBus, u32 writeAddr, u32 readAddr)
{
    if (writeAddr != 0)
        store_lrs(writeAddr, firstBus);
    if (readAddr != 0)
        add_lrs_to_main(readAddr, 3);
}

void cmd_mix_auxb_lr(u32 writeAddr, u32 readAddr)
{
    // Dolby Pro Logic II studios: aux B L/R are the rear channels. They're
    // stored for the next frame and the previous frame's are folded into the
    // front (a stereo downmix; the DPL2 matrix encoding isn't emulated).
    if (writeAddr != 0)
        store_lrs(writeAddr, kAuxBL);
    if (readAddr != 0)
        add_lrs_to_main(readAddr, 2);
}

void cmd_set_opposite_lr(u32 addr)
{
    const s32* surround = mem<const s32>(addr);
    for (int i = 0; i < kFrameSamples; i++)
    {
        s32 s = surround != nullptr ? surround[i] : 0;
        s_bus[kMainL][i] = -s;
        s_bus[kMainR][i] = s;
        s_bus[kMainS][i] = 0;
    }
}

void cmd_output(u32 surroundAddr, u32 destAddr)
{
    if (s32* surround = mem<s32>(surroundAddr))
        memcpy(surround, s_bus[kMainS], sizeof(s_bus[0]));
    s16* dest = mem<s16>(destAddr);
    if (dest == nullptr)
    {
        debug_frame_done(nullptr);
        return;
    }
    // The AI layer feeds SDL natively: interleaved L/R, native-endian.
    for (int i = 0; i < kFrameSamples; i++)
    {
        dest[i * 2 + 0] = clamp16(s_bus[kMainL][i]);
        dest[i * 2 + 1] = clamp16(s_bus[kMainR][i]);
    }
    debug_frame_done(dest);
}

// ---------------------------------------------------------------------------
// Sample fetch (the ARAM "accelerator")

enum SampleFormat : u16
{
    kFormatADPCM = 0x00,
    kFormatPCM16 = 0x0A,
    kFormatPCM8 = 0x19,
};

class SampleReader
{
public:
    explicit SampleReader(_PB& pb) : m_pb(pb)
    {
        m_aram = static_cast<const u8*>(ARGetStorageAddress());
        m_aramSize = m_aram != nullptr ? ARGetSize() : 0;
        m_cur = join(pb.addr.currentAddressHi, pb.addr.currentAddressLo);
        m_end = join(pb.addr.endAddressHi, pb.addr.endAddressLo);
        m_loop = join(pb.addr.loopAddressHi, pb.addr.loopAddressLo);
        m_ps = pb.adpcm.pred_scale;
        m_yn1 = (s16)pb.adpcm.yn1;
        m_yn2 = (s16)pb.adpcm.yn2;
    }

    bool stopped() const { return m_stopped; }

    s16 next()
    {
        if (m_stopped)
            return 0;

        s16 sample;
        switch (m_pb.addr.format)
        {
        case kFormatADPCM:
            sample = next_adpcm();
            break;
        case kFormatPCM16:
            sample = (s16)((byte(m_cur * 2) << 8) | byte(m_cur * 2 + 1));
            break;
        case kFormatPCM8:
            sample = (s16)((s8)byte(m_cur) << 8);
            break;
        default:
            warn_once("unknown sample format", m_pb.addr.format);
            m_stopped = true;
            m_pb.state = 0;
            return 0;
        }

        if (m_cur == m_end)
        {
            if (m_pb.addr.loopFlag != 0)
            {
                m_cur = m_loop;
                if (m_pb.addr.format == kFormatADPCM)
                {
                    m_ps = m_pb.adpcmLoop.loop_pred_scale;
                    // Streams (loopType 1) keep the decoder history running.
                    if (m_pb.loopType == 0)
                    {
                        m_yn1 = (s16)m_pb.adpcmLoop.loop_yn1;
                        m_yn2 = (s16)m_pb.adpcmLoop.loop_yn2;
                    }
                }
                m_pb.streamLoopCnt++;
            }
            else
            {
                // One-shot sample finished: the voice stops. The loop address
                // points at MusyX's ARAM zero buffer.
                m_cur = m_loop;
                m_stopped = true;
                m_pb.state = 0;
            }
        }
        else
        {
            m_cur++;
        }
        return sample;
    }

    void store()
    {
        m_pb.addr.currentAddressHi = (u16)(m_cur >> 16);
        m_pb.addr.currentAddressLo = (u16)m_cur;
        m_pb.adpcm.pred_scale = m_ps;
        m_pb.adpcm.yn1 = (u16)m_yn1;
        m_pb.adpcm.yn2 = (u16)m_yn2;
    }

private:
    static u32 join(u16 hi, u16 lo) { return ((u32)hi << 16) | lo; }

    u8 byte(u32 aramAddr) const { return aramAddr < m_aramSize ? m_aram[aramAddr] : 0; }

    // DSP-ADPCM: 8-byte frames of a predictor/scale header byte and 14 nibbles.
    // Addresses count nibbles; the header occupies the first two of a frame.
    s16 next_adpcm()
    {
        if ((m_cur & 15) == 0)
        {
            m_ps = byte(m_cur >> 1);
            m_cur += 2;
        }
        u8 b = byte(m_cur >> 1);
        s32 nibble = (m_cur & 1) ? (b & 0xF) : (b >> 4);
        if (nibble >= 8)
            nibble -= 16;
        s32 scale = 1 << (m_ps & 0xF);
        u32 coefIndex = (m_ps >> 4) & 7;
        s32 c1 = (s16)m_pb.adpcm.a[coefIndex][0];
        s32 c2 = (s16)m_pb.adpcm.a[coefIndex][1];
        s32 v = (((nibble * scale) << 11) + 1024 + c1 * m_yn1 + c2 * m_yn2) >> 11;
        s16 sample = clamp16(v);
        m_yn2 = m_yn1;
        m_yn1 = sample;
        return sample;
    }

    _PB& m_pb;
    const u8* m_aram = nullptr;
    u32 m_aramSize = 0;
    u32 m_cur;
    u32 m_end;
    u32 m_loop;
    u16 m_ps;
    s16 m_yn1;
    s16 m_yn2;
    bool m_stopped = false;
};

// ---------------------------------------------------------------------------
// Voice rendering

enum SrcType : u16
{
    kSrcPolyphase = 0,
    kSrcLinear = 1,
    kSrcNone = 2,
};

// Resamples the voice's sample stream into `out`. The last four input samples
// live in pb.src.last_samples (oldest first) and the read position's fraction
// in currentAddressFrac. Output is taken between history[1] and history[2],
// a fixed two-sample latency for every mode.
void render_source(_PB& pb, SampleReader& reader, s16* out, int count)
{
    u32 ratio = ((u32)pb.src.ratioHi << 16) | pb.src.ratioLo;
    if (pb.srcSelect == kSrcNone)
        ratio = 0x10000;
    u32 frac = pb.src.currentAddressFrac;
    s16 h[4];
    for (int i = 0; i < 4; i++)
        h[i] = (s16)pb.src.last_samples[i];

    for (int i = 0; i < count; i++)
    {
        s32 v;
        switch (pb.srcSelect)
        {
        case kSrcNone:
            v = h[2];
            break;
        case kSrcLinear:
            v = h[1] + (((s32)h[2] - h[1]) * (s32)frac >> 16);
            break;
        default:
        {
            // Catmull-Rom cubic between h[1] and h[2].
            float t = (float)frac * (1.0f / 65536.0f);
            float p0 = h[0], p1 = h[1], p2 = h[2], p3 = h[3];
            float r = p1 + 0.5f * t *
                               (p2 - p0 +
                                t * (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3 + t * (3.0f * (p1 - p2) + p3 - p0)));
            v = (s32)(r >= 0.0f ? r + 0.5f : r - 0.5f);
            break;
        }
        }
        out[i] = clamp16(v);

        frac += ratio;
        u32 advance = frac >> 16;
        frac &= 0xFFFF;
        for (; advance != 0; advance--)
        {
            h[0] = h[1];
            h[1] = h[2];
            h[2] = h[3];
            h[3] = reader.next();
        }
    }

    pb.src.currentAddressFrac = (u16)frac;
    for (int i = 0; i < 4; i++)
        pb.src.last_samples[i] = (u16)h[i];
}

void apply_envelope(_PB& pb, s16* samples, int count)
{
    s32 vol = pb.ve.currentVolume;
    s32 delta = (s16)pb.ve.currentDelta;
    for (int i = 0; i < count; i++)
    {
        samples[i] = clamp16((s32)samples[i] * vol >> 15);
        vol = std::clamp(vol + delta, 0, 0x7FFF);
    }
    pb.ve.currentVolume = (u16)vol;
}

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
void apply_lpf(_PB& pb, s16* samples, int count)
{
    if (pb.lpf.flag == 0)
        return;
    // Coefficients are unsigned 1.15 (MusyX hwLowPassFrqToCoef can produce 0x8000).
    s32 a0 = (u16)pb.lpf.a0;
    s32 b0 = (u16)pb.lpf.b0;
    s32 y = (s16)pb.lpf.yn1;
    for (int i = 0; i < count; i++)
    {
        y = clamp16((samples[i] * a0 + y * b0) >> 15);
        samples[i] = (s16)y;
    }
    pb.lpf.yn1 = (u16)y;
}
#endif

// Interaural time difference: the left and right sends read the voice through
// a 32-sample delay line (stored in the voice's ITD buffer), offset by
// shiftL/shiftR, which glide towards their targets.
void apply_itd(_PB& pb, const s16* in, s16* left, s16* right)
{
    s16* history = mem<s16>(((u32)pb.itd.bufferHi << 16) | pb.itd.bufferLo);
    if (history == nullptr)
    {
        memcpy(left, in, kSubSamples * sizeof(s16));
        memcpy(right, in, kSubSamples * sizeof(s16));
        return;
    }
    s16 line[kSubSamples * 2];
    memcpy(line, history, kSubSamples * sizeof(s16));
    memcpy(line + kSubSamples, in, kSubSamples * sizeof(s16));
    u32 shiftL = std::min<u32>(pb.itd.shiftL, kSubSamples);
    u32 shiftR = std::min<u32>(pb.itd.shiftR, kSubSamples);
    for (int i = 0; i < kSubSamples; i++)
    {
        left[i] = line[kSubSamples + i - shiftL];
        right[i] = line[kSubSamples + i - shiftR];
    }
    memcpy(history, in, kSubSamples * sizeof(s16));

    auto glide = [](u16& shift, u16 target) {
        if (shift < target)
            shift++;
        else if (shift > target)
            shift--;
    };
    glide(pb.itd.shiftL, pb.itd.targetShiftL);
    glide(pb.itd.shiftR, pb.itd.targetShiftR);
}

struct BusSend
{
    u8 volume; // u16 index into _PBMIX (the delta follows it)
    u8 dpop;   // u16 index into _PBDPOP
    u8 side;   // 0 = centre, 1 = left, 2 = right
};

#define MIX_INDEX(field) (u8)(offsetof(_PBMIX, field) / sizeof(u16))
#define DPOP_INDEX(field) (u8)(offsetof(_PBDPOP, field) / sizeof(u16))

const BusSend kSends[kNumBuses] = {
    {MIX_INDEX(vL), DPOP_INDEX(aL), 1},         {MIX_INDEX(vR), DPOP_INDEX(aR), 2},
    {MIX_INDEX(vS), DPOP_INDEX(aS), 0},         {MIX_INDEX(vAuxAL), DPOP_INDEX(aAuxAL), 1},
    {MIX_INDEX(vAuxAR), DPOP_INDEX(aAuxAR), 2}, {MIX_INDEX(vAuxAS), DPOP_INDEX(aAuxAS), 0},
    {MIX_INDEX(vAuxBL), DPOP_INDEX(aAuxBL), 1}, {MIX_INDEX(vAuxBR), DPOP_INDEX(aAuxBR), 2},
    {MIX_INDEX(vAuxBS), DPOP_INDEX(aAuxBS), 0},
};

#undef MIX_INDEX
#undef DPOP_INDEX

void mix_voice(_PB& pb, const s16* centre, const s16* left, const s16* right, int offset)
{
    u16* mix = reinterpret_cast<u16*>(&pb.mix);
    u16* dpop = reinterpret_cast<u16*>(&pb.dpop);
    const s16* sources[3] = {centre, left, right};
    for (int b = 0; b < kNumBuses; b++)
    {
        const BusSend& send = kSends[b];
        u16 vol = mix[send.volume];
        s16 delta = (s16)mix[send.volume + 1];
        if (vol == 0 && delta == 0)
        {
            dpop[send.dpop] = 0;
            continue;
        }
        const s16* src = sources[send.side];
        s32* dst = &s_bus[b][offset];
        s32 last = 0;
        for (int i = 0; i < kSubSamples; i++)
        {
            last = ((s32)src[i] * vol) >> 15;
            dst[i] += last;
            vol = (u16)(vol + delta);
        }
        mix[send.volume] = vol;
        dpop[send.dpop] = (u16)clamp16(last);
    }
}

void process_pb(_PB& pb)
{
    const u16* updates = mem<const u16>(((u32)pb.update.dataHi << 16) | pb.update.dataLo);
    u16* words = reinterpret_cast<u16*>(&pb);

    for (int sub = 0; sub < kSubFrames; sub++)
    {
        for (u32 n = pb.update.updNum[sub]; n != 0 && updates != nullptr; n--, updates += 2)
        {
            u16 offset = updates[0];
            if (offset < sizeof(_PB) / sizeof(u16))
                words[offset] = updates[1];
        }

        if (pb.state != 1)
            continue;
        s_debug.voiceSubFrames++;

        s16 samples[kSubSamples];
        {
            SampleReader reader(pb);
            render_source(pb, reader, samples, kSubSamples);
            reader.store();
        }
        apply_envelope(pb, samples, kSubSamples);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
        apply_lpf(pb, samples, kSubSamples);
#endif
        if (pb.itd.flag != 0)
        {
            s16 left[kSubSamples];
            s16 right[kSubSamples];
            apply_itd(pb, samples, left, right);
            mix_voice(pb, samples, left, right, sub * kSubSamples);
        }
        else
        {
            mix_voice(pb, samples, samples, samples, sub * kSubSamples);
        }
    }
}

void debug_list_voices(u32 addr)
{
    static const bool s_on = getenv("MSSB_DSP_VOICES") != nullptr;
    static const int s_every = getenv("MSSB_DSP_VOICES") ? std::max(1, atoi(getenv("MSSB_DSP_VOICES"))) : 200;
    if (!s_on || s_debug.frames % s_every != 0)
        return;
    for (int n = 0; addr != 0 && n < 256; n++)
    {
        const _PB* pb = mem<const _PB>(addr);
        if (pb == nullptr)
            break;
        if (pb->state == 1)
            fprintf(stderr, "[voice] f%u pb %08X fmt %02X loop %u type %u src %u cur %08X end %08X loopa %08X ratio %08X vol %04X ps %02X lps %02X a %d %d %d %d\n",
                    s_debug.frames, addr, pb->addr.format, pb->addr.loopFlag, pb->loopType, pb->srcSelect,
                    ((u32)pb->addr.currentAddressHi << 16) | pb->addr.currentAddressLo,
                    ((u32)pb->addr.endAddressHi << 16) | pb->addr.endAddressLo,
                    ((u32)pb->addr.loopAddressHi << 16) | pb->addr.loopAddressLo,
                    ((u32)pb->src.ratioHi << 16) | pb->src.ratioLo, pb->ve.currentVolume, pb->adpcm.pred_scale,
                    pb->adpcmLoop.loop_pred_scale, (s16)pb->adpcm.a[0][0], (s16)pb->adpcm.a[0][1],
                    (s16)pb->adpcm.a[1][0], (s16)pb->adpcm.a[1][1]);
        addr = ((u32)pb->nextHi << 16) | pb->nextLo;
    }
}

void cmd_process()
{
    u32 addr = s_pbAddr;
    debug_list_voices(addr);
    // The list is terminated by a zero next pointer; cap it in case of a cycle.
    for (int n = 0; addr != 0 && n < 256; n++)
    {
        _PB* pb = mem<_PB>(addr);
        if (pb == nullptr)
            break;
        process_pb(*pb);
        s_debug.frameVoices++;
        addr = ((u32)pb->nextHi << 16) | pb->nextLo;
    }
}

} // namespace

extern "C" void dsp_ax_reset(void)
{
    memset(s_bus, 0, sizeof(s_bus));
    s_pbAddr = 0;
}

extern "C" void dsp_ax_execute(u32 listAddr)
{
    debug_init();
    const u16* p = mem<const u16>(listAddr);
    auto word = [&p]() -> u16 { return *p++; };
    auto addr = [&word]() -> u32 {
        u32 hi = word();
        return (hi << 16) | word();
    };

    // Bound the work in case the list is corrupt.
    for (int executed = 0; p != nullptr && executed < 4096; executed++)
    {
        u16 cmd = word();
        switch (cmd)
        {
        case 0: // SETUP
            cmd_setup(addr());
            break;
        case 1: // DL_AND_VOL_MIX
        {
            u32 a = addr();
            u16 vol = word();
            u16 volA = word();
            u16 volB = word();
            cmd_dl_and_vol_mix(a, vol, volA, volB);
            break;
        }
        case 2: // PB_ADDR
            s_pbAddr = addr();
            break;
        case 3: // PROCESS
            cmd_process();
            break;
        case 4: // MIX_AUXA
        {
            u32 w = addr();
            u32 r = addr();
            cmd_mix_aux(kAuxAL, w, r);
            break;
        }
        case 5: // MIX_AUXB
        {
            u32 w = addr();
            u32 r = addr();
            cmd_mix_aux(kAuxBL, w, r);
            break;
        }
        case 6: // UPLOAD_LRS
            store_lrs(addr(), kMainL);
            break;
        case 9: // MIX_AUXB_NOWRITE
            add_lrs_to_main(addr(), 3);
            break;
        case 13: // MORE
        {
            u32 next = addr();
            word(); // size of the next chunk (the real DSP DMAs it in)
            p = mem<const u16>(next);
            break;
        }
        case 14: // OUTPUT
        {
            u32 surround = addr();
            u32 dest = addr();
            cmd_output(surround, dest);
            break;
        }
        case 15: // END
            return;
        case 16: // MIX_AUXB_LR
        {
            u32 w = addr();
            u32 r = addr();
            cmd_mix_auxb_lr(w, r);
            break;
        }
        case 17: // SET_OPPOSITE_LR
            cmd_set_opposite_lr(addr());
            break;
        case 18: // COMPRESSOR: {0x8000, 10, table hi, table lo}
            word();
            word();
            addr();
            break;
        default:
            warn_once("unknown command, aborting list", cmd);
            return;
        }
    }
}
