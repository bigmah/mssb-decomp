// DVD audio streaming (DTK) emulation: the game's music is ADP files on the
// disc (/snd/my_snd_h/*.adp) that the drive streams straight to the AI, which
// mixes them with the DSP output. On PC the prepared file is read into memory,
// decoded (GameCube DTK ADPCM: 32-byte blocks of 28 stereo samples, 48 kHz) and
// mixed into each AI period by ai.cpp (port_dtk_mix).
//
// The DVD stream calls are mapped to the port_* versions for game code by the
// prelude; the AI stream calls (AISetStream*) are implemented here.

#include <dolphin/types.h>
#include <dolphin/ai.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <mutex>
#include <vector>

namespace {
constexpr int kBlockBytes = 32;
constexpr int kBlockSamples = 28;
constexpr int kStreamRate = 48000;

std::recursive_mutex s_lock;
std::vector<u8> s_data;       // the prepared file
size_t s_filled = 0;          // bytes of it read so far (web: it arrives over time)
size_t s_pos = 0;             // next block to decode (bytes)
bool s_prepared = false;
bool s_ended = false;         // the stream ran off the end (stop-at-end)
bool s_playing = false;       // AISetStreamPlayState
u8 s_volL = 0;
u8 s_volR = 0;
u32 s_sampleCount = 0;
u32 s_trigger = 0;
AISCallback s_callback = nullptr;
s32 s_hist[4]; // left h1, h2, right h1, h2
s16 s_pcm[kBlockSamples * 2];
int s_pcmPos = kBlockSamples; // samples of s_pcm consumed
u32 s_resample = 0;           // 48 kHz -> output rate phase (in 1/outRate units)
bool s_debug = false;

s16 decode_sample(s32 bits, s32 q, s32& hist1, s32& hist2)
{
    s32 hist = 0;
    switch (q >> 4)
    {
    case 1:
        hist = hist1 * 0x3C;
        break;
    case 2:
        hist = hist1 * 0x73 - hist2 * 0x34;
        break;
    case 3:
        hist = hist1 * 0x62 - hist2 * 0x37;
        break;
    default:
        break;
    }
    hist = std::clamp((hist + 0x20) >> 6, -0x200000, 0x1FFFFF);
    s32 cur = (((s16)(bits << 12) >> (q & 0xF)) << 6) + hist;
    hist2 = hist1;
    hist1 = cur;
    cur >>= 6;
    return (s16)std::clamp(cur, -0x8000, 0x7FFF);
}

// Next 48 kHz stereo frame of the stream (silence once it has ended).
void next_frame(s16& l, s16& r)
{
    if (s_pcmPos >= kBlockSamples)
    {
        if (s_prepared && s_pos + kBlockBytes > s_filled && s_filled < s_data.size())
        {
            // Web: the next bytes are still coming over the network.
            l = r = 0;
            return;
        }
        if (!s_prepared || s_pos + kBlockBytes > s_data.size())
        {
            if (s_prepared && !s_ended)
            {
                s_ended = true;
                if (s_debug)
                    fprintf(stderr, "[dtk] stream ended\n");
            }
            l = r = 0;
            return;
        }
        const u8* src = &s_data[s_pos];
        for (int i = 0; i < kBlockSamples; i++)
        {
            s_pcm[i * 2] = decode_sample(src[i + 4] & 0xF, src[0], s_hist[0], s_hist[1]);
            s_pcm[i * 2 + 1] = decode_sample(src[i + 4] >> 4, src[1], s_hist[2], s_hist[3]);
        }
        s_pos += kBlockBytes;
        s_pcmPos = 0;
    }
    l = s_pcm[s_pcmPos * 2];
    r = s_pcm[s_pcmPos * 2 + 1];
    s_pcmPos++;
}
} // namespace

extern "C" {

// Mixes the stream into `frames` stereo frames at `rate` Hz. Runs in the AI
// period, under the port's interrupt lock (the stream callback may run).
void port_dtk_mix(s16* out, int frames, int rate)
{
    AISCallback fire = nullptr;
    u32 fireCount = 0;
    {
        std::lock_guard lk(s_lock);
        if (!s_playing)
            return;
        for (int i = 0; i < frames; i++)
        {
            // Consume 48 kHz frames until this output frame is covered
            // (nearest-sample resampling for a 32 kHz DSP rate).
            s16 l = 0, r = 0;
            s_resample += kStreamRate;
            while (s_resample >= (u32)rate)
            {
                s_resample -= rate;
                next_frame(l, r);
                s_sampleCount++;
                if (s_trigger != 0 && s_sampleCount == s_trigger && s_callback != nullptr)
                {
                    fire = s_callback;
                    fireCount = s_sampleCount;
                }
            }
            s32 ml = out[i * 2] + l * s_volL / 255;
            s32 mr = out[i * 2 + 1] + r * s_volR / 255;
            out[i * 2] = (s16)std::clamp(ml, -0x8000, 0x7FFF);
            out[i * 2 + 1] = (s16)std::clamp(mr, -0x8000, 0x7FFF);
        }
    }
    if (fire != nullptr)
        fire(fireCount);
}

// ---------------------------------------------------------------- AI stream

AISCallback AIRegisterStreamCallback(AISCallback callback)
{
    std::lock_guard lk(s_lock);
    AISCallback old = s_callback;
    s_callback = callback;
    return old;
}

void AIResetStreamSampleCount(void)
{
    std::lock_guard lk(s_lock);
    s_sampleCount = 0;
}

u32 AIGetStreamSampleCount(void)
{
    std::lock_guard lk(s_lock);
    return s_sampleCount;
}

void AISetStreamTrigger(u32 trigger)
{
    std::lock_guard lk(s_lock);
    s_trigger = trigger;
}

void AISetStreamPlayState(u32 state)
{
    std::lock_guard lk(s_lock);
    s_playing = state != 0;
}

u32 AIGetStreamPlayState(void)
{
    std::lock_guard lk(s_lock);
    return s_playing ? 1 : 0;
}

void AISetStreamVolLeft(u8 vol)
{
    std::lock_guard lk(s_lock);
    s_volL = vol;
}

void AISetStreamVolRight(u8 vol)
{
    std::lock_guard lk(s_lock);
    s_volR = vol;
}

u8 AIGetStreamVolLeft(void)
{
    return s_volL;
}

u8 AIGetStreamVolRight(void)
{
    return s_volR;
}

// ---------------------------------------------------------------- DVD stream
// The callbacks run synchronously, "in interrupt context" (interrupts off).

static void run_cb(DVDCBCallback cb, s32 result, DVDCommandBlock* block)
{
    if (cb == nullptr)
        return;
    BOOL level = OSDisableInterrupts();
    cb(result, block);
    OSRestoreInterrupts(level);
}

#ifdef __EMSCRIPTEN__
// Web builds: a song is ~15 MB of disc, too much to wait for in one read
// (every thread stalls while a read misses the page's cache). It's read in
// chunks as the page fetches them, a few seconds ahead of playback; the
// prepare callback runs once the start is in.
int64_t aurora_dvd_file_disc_offset(const DVDFileInfo* fileInfo);
int port_web_disc_ready(uint64_t offset, uint64_t len);
int64_t port_web_disc_read(uint64_t offset, void* out, uint64_t len);
void port_raise_interrupt(void (*fn)(void*), void* arg);

namespace {
constexpr size_t kWebChunk = 256 << 10;
constexpr size_t kWebAhead = 2 << 20;  // ~37 s of music
constexpr size_t kWebStart = 256 << 10; // before the prepare callback
int64_t s_webBase = -1;                 // disc offset of the stream's first byte
DVDFileInfo* s_webFileInfo = nullptr;
DVDCallback s_webPrepareCb = nullptr;
bool s_webPreparing = false;
void deliver_prepared(void*)
{
    if (s_webPrepareCb != nullptr && s_webBase >= 0)
        s_webPrepareCb(DVD_RESULT_GOOD, s_webFileInfo);
}
} // namespace

// Reads what has arrived of the stream (called every frame and while threads wait).
void port_dtk_web_pump(void)
{
    if (s_webBase < 0)
        return;
    for (;;)
    {
        size_t filled;
        size_t total;
        size_t pos;
        {
            std::lock_guard lk(s_lock);
            filled = s_filled;
            total = s_data.size();
            pos = s_pos;
        }
        if (filled >= total || (!s_webPreparing && filled >= pos + kWebAhead))
            break;
        const size_t n = std::min(kWebChunk, total - filled);
        if (!port_web_disc_ready((uint64_t)s_webBase + filled, n))
        {
            // Ask for the rest of the window too, so it arrives in parallel.
            const size_t want = std::min(total, (s_webPreparing ? 0 : pos) + kWebAhead);
            if (want > filled + n)
                port_web_disc_ready((uint64_t)s_webBase + filled + n, want - filled - n);
            break;
        }
        {
            std::lock_guard lk(s_lock);
            if (port_web_disc_read((uint64_t)s_webBase + filled, &s_data[filled], n) != (int64_t)n)
            {
                fprintf(stderr, "[dtk] stream read failed\n");
                s_webBase = -1;
                return;
            }
            s_filled = filled + n;
        }
        if (s_webPreparing && (s_filled >= kWebStart || s_filled >= total))
        {
            s_webPreparing = false;
            {
                std::lock_guard lk(s_lock);
                s_prepared = true;
            }
            if (s_debug)
                fprintf(stderr, "[dtk] prepared %zu bytes\n", total);
            if (s_webPrepareCb != nullptr)
                port_raise_interrupt(deliver_prepared, nullptr); // like the drive's interrupt
        }
    }
}
#endif

BOOL port_DVDPrepareStreamAsync(DVDFileInfo* fileInfo, u32 length, u32 offset, DVDCallback callback)
{
    s_debug = getenv("MSSB_DEBUG_DTK") != nullptr;
    if (fileInfo == nullptr)
        return FALSE;
    if (length == 0)
        length = fileInfo->length - offset;
#ifdef __EMSCRIPTEN__
    if (const int64_t base = aurora_dvd_file_disc_offset(fileInfo); base >= 0)
    {
        {
            std::lock_guard lk(s_lock);
            s_data.assign(length, 0);
            s_filled = 0;
            s_pos = 0;
            s_pcmPos = kBlockSamples;
            std::fill(std::begin(s_hist), std::end(s_hist), 0);
            s_prepared = false;
            s_ended = false;
        }
        s_webBase = base + offset;
        s_webFileInfo = fileInfo;
        s_webPrepareCb = callback;
        s_webPreparing = true;
        port_dtk_web_pump();
        return TRUE;
    }
#endif
    std::vector<u8> data((length + 31) & ~31u);
    // The read goes through aurora's DVD worker, whose queued completion
    // callbacks take the interrupt lock: never wait for it while holding it.
    BOOL wasEnabled = OSEnableInterrupts();
    s32 got = DVDReadPrio(fileInfo, data.data(), (s32)data.size(), (s32)offset, 2);
    OSRestoreInterrupts(wasEnabled);
    if (got < 0)
    {
        fprintf(stderr, "[dtk] stream read failed (%d)\n", got);
        data.clear();
    }
    data.resize(std::min<size_t>(data.size(), length));
    {
        std::lock_guard lk(s_lock);
        s_data.swap(data);
        s_filled = s_data.size();
        s_pos = 0;
        s_pcmPos = kBlockSamples;
        std::fill(std::begin(s_hist), std::end(s_hist), 0);
        s_prepared = true;
        s_ended = false;
    }
    if (s_debug)
        fprintf(stderr, "[dtk] prepared %u bytes at 0x%x\n", length, offset);
    if (callback != nullptr)
    {
        BOOL level = OSDisableInterrupts();
        callback(DVD_RESULT_GOOD, fileInfo);
        OSRestoreInterrupts(level);
    }
    return TRUE;
}

// The page's ?debug "static!" button: where the music stream is, and a checksum of what it plays
// next (compare with the disc: port/tools/dtk_check.py).
void port_dtk_debug_state(void)
{
    std::lock_guard lk(s_lock);
    u32 sum = 0;
    const size_t end = std::min(s_filled, s_pos + 4096);
    for (size_t i = s_pos; i < end; i++)
        sum = sum * 31 + s_data[i];
#ifdef __EMSCRIPTEN__
    const long long base = (long long)s_webBase;
#else
    const long long base = -1;
#endif
    fprintf(stderr, "[dtk] playing %d prepared %d base %lld pos %zu filled %zu size %zu vol %u/%u sum4k %08X\n", s_playing ? 1 : 0,
            s_prepared ? 1 : 0, base, s_pos, s_filled, s_data.size(), s_volL, s_volR, sum);
}

BOOL port_DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    {
        std::lock_guard lk(s_lock);
        s_prepared = false;
        s_data.clear();
        s_filled = 0;
    }
#ifdef __EMSCRIPTEN__
    s_webBase = -1;
    s_webPreparing = false;
    s_webPrepareCb = nullptr;
#endif
    run_cb(callback, DVD_RESULT_GOOD, block);
    return TRUE;
}

BOOL port_DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    // Streams always stop at the end here (no loop back to the start).
    run_cb(callback, DVD_RESULT_GOOD, block);
    return TRUE;
}

// 0 once the stream has stopped (run off its end or cancelled), else 1.
BOOL port_DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    s32 status;
    {
        std::lock_guard lk(s_lock);
        status = (s_prepared && !s_ended) ? 1 : 0;
    }
    run_cb(callback, status, block);
    return TRUE;
}

BOOL port_DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    s32 addr;
    {
        std::lock_guard lk(s_lock);
        addr = (s_prepared && !s_ended) ? (s32)s_pos : 0;
    }
    run_cb(callback, addr, block);
    return TRUE;
}
}
