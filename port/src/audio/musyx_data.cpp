// Endian conversion for MusyX data files and DSP-ADPCM stream headers.
//
// Layouts below are taken from the MusyX runtime (decomp/musyx) and checked
// against the files on the disc (sebring.proj/.pool/.sdir, *.song, *.idsp).
// Every scalar is swapped once, with its own width; sub-structures reached
// through offsets are tracked so a shared one is never swapped twice.
#include "port/musyx_data.h"
#include "port/endian.h"

#include <stdio.h>
#include <unordered_set>

namespace {

struct Blob
{
    uint8_t* base;
    uint32_t size;

    bool in(uint32_t off, uint32_t len) const { return off <= size && len <= size - off; }

    // Swap in place and return the native value.
    uint16_t s16(uint32_t off) const
    {
        swap16_inplace(base + off);
        uint16_t v;
        memcpy(&v, base + off, 2);
        return v;
    }
    uint32_t s32(uint32_t off) const
    {
        swap32_inplace(base + off);
        uint32_t v;
        memcpy(&v, base + off, 4);
        return v;
    }
    uint32_t be32at(uint32_t off) const { return read_be32(base + off); }
    uint16_t be16at(uint32_t off) const { return read_be16(base + off); }
};

void bad(const char* what, uint32_t off)
{
    fprintf(stderr, "[musyx_data] %s out of range at 0x%x\n", what, off);
}

// ---------------------------------------------------------------------------
// Project (s_data.c sndPushGroup / ScanIDList, snd_synthapi.c seqPlaySong)
//
// GROUP_DATA (0x28), linked by absolute nextOff (0xFFFFFFFF ends the list):
//   u32 nextOff; u16 id; u16 type; u32 macroOff, sampleOff, curveOff,
//   keymapOff, layerOff; union { u32 fx.tableOff; u32 song.normpageOff,
//   drumpageOff, midiSetupOff; }
// ID list: u16 ids, 0xFFFF-terminated; an id with bit 15 set starts a range
//   whose (u16) end id follows.
// type 1 (SFX): FX_DATA at tableOff: u16 num, u16 reserved, FX_TAB[num] {u16 id,
//   u16 macro, u8 maxVoices, priority, volume, panning, key, vGroup} (0xA each).
// type 0 (song): PAGE[] {u16 macro, u8 prio, maxVoices, index, reserved} ended
//   by index 0xFF; MIDISETUP[] {u16 songId, u16 reserved, u8 channel[16][5]}
//   ended by songId 0xFFFF.
// ---------------------------------------------------------------------------

void swap_idlist(const Blob& b, uint32_t off)
{
    while (b.in(off, 2))
    {
        uint16_t v = b.s16(off);
        if (v == 0xFFFF)
            return;
        if (v & 0x8000)
        {
            if (!b.in(off + 2, 2))
                break;
            b.s16(off + 2);
            off += 4;
        }
        else
        {
            off += 2;
        }
    }
    bad("proj id list", off);
}

void swap_pages(const Blob& b, uint32_t off)
{
    while (b.in(off, 6))
    {
        if (b.base[off + 4] == 0xFF)
            return;
        b.s16(off);
        off += 6;
    }
    bad("proj page table", off);
}

void swap_midisetups(const Blob& b, uint32_t off)
{
    while (b.in(off, 0x54))
    {
        uint16_t id = b.s16(off);
        if (id == 0xFFFF)
            return;
        b.s16(off + 2);
        off += 0x54;
    }
    bad("proj midi setup", off);
}

void swap_fxdata(const Blob& b, uint32_t off)
{
    if (!b.in(off, 4))
        return bad("proj fx table", off);
    uint16_t num = b.s16(off);
    b.s16(off + 2);
    if (!b.in(off + 4, num * 10u))
        return bad("proj fx entries", off);
    for (uint32_t i = 0; i < num; i++)
    {
        uint32_t e = off + 4 + i * 10;
        b.s16(e);     // id
        b.s16(e + 2); // macro
    }
}

} // namespace

extern "C" void port_musyx_swap_proj(void* data, uint32_t size)
{
    Blob b{(uint8_t*)data, size};
    std::unordered_set<uint32_t> done;
    auto once = [&](uint32_t off) { return off != 0 && done.insert(off).second; };

    uint32_t o = 0;
    while (b.in(o, 4))
    {
        uint32_t next = b.s32(o);
        if (next == 0xFFFFFFFF)
            return;
        if (!b.in(o, 0x28))
            break;
        b.s16(o + 4); // id
        uint16_t type = b.s16(o + 6);
        uint32_t offs[8];
        for (int i = 0; i < 8; i++)
            offs[i] = b.s32(o + 8 + i * 4);
        // Five ID lists: macros, samples, curves, keymaps, layers. An empty
        // list is just the 0xFFFF terminator; lists are never at offset 0.
        for (int i = 0; i < 5; i++)
            if (once(offs[i]))
                swap_idlist(b, offs[i]);
        if (type == 1)
        {
            if (once(offs[5]))
                swap_fxdata(b, offs[5]);
        }
        else if (type == 0)
        {
            if (once(offs[5]))
                swap_pages(b, offs[5]);
            if (once(offs[6]))
                swap_pages(b, offs[6]);
            if (once(offs[7]))
                swap_midisetups(b, offs[7]);
        }
        if (next <= o)
            break;
        o = next;
    }
    bad("proj group list", o);
}

// ---------------------------------------------------------------------------
// Pool (s_data.c GetPoolAddr, synth*.c consumers)
//
// POOL_DATA: u32 macroOff, curveOff, keymapOff, layerOff (0 = section absent).
// Each section is a MEM_DATA chain linked by a *relative* nextOff, ended by
// nextOff 0xFFFFFFFF: u32 nextOff; u16 id; u16 reserved; data[nextOff - 8].
//   macros: MSTEP[] = pairs of u32 command words.
//   curves: byte tables (volume curves) and ADSR tables. ADSR tables are
//           little-endian on disc and read by explicit byte composition, so
//           the whole section stays as is.
//   keymaps: KEYMAP[128] {u16 id, s8 transpose, u8 panning, s16 prioOffset, u8[2]}.
//   layers: u32 num; LAYER[num] {u16 id, u8 keyLow, keyHigh, s8 transpose,
//           u8 volume, s16 prioOffset, u8 panning, u8[3]} (0xC each).
// ---------------------------------------------------------------------------

namespace {

enum PoolSection
{
    kMacro,
    kCurve,
    kKeymap,
    kLayer
};

void swap_pool_section(const Blob& b, uint32_t off, PoolSection kind)
{
    uint32_t m = off;
    while (b.in(m, 4))
    {
        uint32_t next = b.s32(m);
        if (next == 0xFFFFFFFF)
            return;
        if (next < 8 || !b.in(m, next))
            break;
        b.s16(m + 4); // id
        b.s16(m + 6); // reserved
        uint32_t d = m + 8;
        uint32_t len = next - 8;
        switch (kind)
        {
        case kMacro:
            swap32_array(b.base + d, len / 4);
            break;
        case kCurve:
            break;
        case kKeymap:
            for (uint32_t k = 0; k + 8 <= len; k += 8)
            {
                b.s16(d + k);     // id
                b.s16(d + k + 4); // prioOffset
            }
            break;
        case kLayer:
        {
            uint32_t num = b.s32(d);
            for (uint32_t k = 0; k < num && 4 + (k + 1) * 12 <= len; k++)
            {
                uint32_t e = d + 4 + k * 12;
                b.s16(e);     // id
                b.s16(e + 6); // prioOffset
            }
            break;
        }
        }
        m += next;
    }
    bad("pool chain", m);
}

} // namespace

extern "C" void port_musyx_swap_pool(void* data, uint32_t size)
{
    Blob b{(uint8_t*)data, size};
    if (!b.in(0, 16))
        return bad("pool header", 0);
    uint32_t offs[4];
    for (int i = 0; i < 4; i++)
        offs[i] = b.s32(i * 4);
    for (int i = 0; i < 4; i++)
    {
        if (offs[i] == 0)
            continue;
        // Sections sharing a chain would be swapped twice.
        bool dup = false;
        for (int j = 0; j < i; j++)
            dup |= offs[j] == offs[i];
        if (!dup)
            swap_pool_section(b, offs[i], (PoolSection)i);
    }
}

// ---------------------------------------------------------------------------
// Sample directory (synthdata.c dataInsertSDir / dataAddSampleReference /
// dataGetSample, hw_dspctrl.c voice setup)
//
// SDIR_DATA (0x20), sorted by id, ended by an id of 0xFFFF (only the id is
// present for the terminator):
//   u16 id; u16 ref_cnt; u32 offset (into .samp); u32 addr (ARAM, runtime);
//   SAMPLE_HEADER {u32 info (key << 24 | rate), u32 length (compType << 24 |
//   samples), u32 loopOffset, u32 loopLength}; u32 extraData (offset from the
//   sdir start, 0 = none).
// extraData for compType 0/4/5: SNDADPCMinfo {u16 numCoef; u8 initialPS,
//   loopPS; s16 loopY0, loopY1; s16 coefTab[8][2]} (0x28).
// compType 1 (ADPCM+): the same 0x28 bytes followed by DSPADPCMblock
//   {s16 Y0, Y1; u8 PS, reserved} per 14-sample frame.
// ---------------------------------------------------------------------------

extern "C" void port_musyx_swap_sdir(void* data, uint32_t size)
{
    Blob b{(uint8_t*)data, size};
    std::unordered_set<uint32_t> done;
    uint32_t o = 0;
    for (;;)
    {
        if (!b.in(o, 2))
            return bad("sdir entry", o);
        if (b.s16(o) == 0xFFFF)
            break;
        if (!b.in(o, 0x20))
            return bad("sdir entry", o);
        b.s16(o + 2);
        for (uint32_t f = 4; f < 0x20; f += 4)
            b.s32(o + f);
        o += 0x20;
    }

    for (uint32_t e = 0; e < o; e += 0x20)
    {
        uint32_t length;
        uint32_t extra;
        memcpy(&length, b.base + e + 0x10, 4);
        memcpy(&extra, b.base + e + 0x1C, 4);
        uint8_t compType = length >> 24;
        if (extra == 0 || !done.insert(extra).second)
            continue;
        if (compType != 0 && compType != 1 && compType != 4 && compType != 5)
            continue;
        if (!b.in(extra, 0x28))
        {
            bad("sdir adpcm info", extra);
            continue;
        }
        b.s16(extra); // numCoef
        for (uint32_t f = 4; f < 0x28; f += 2)
            b.s16(extra + f);
        if (compType == 1)
        {
            uint32_t blocks = ((length & 0xFFFFFF) + 13) / 14;
            if (!b.in(extra + 0x28, blocks * 6))
            {
                bad("sdir adpcm+ blocks", extra);
                continue;
            }
            for (uint32_t k = 0; k < blocks; k++)
            {
                b.s16(extra + 0x28 + k * 6);
                b.s16(extra + 0x28 + k * 6 + 2);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// Song (seq.c seqStartPlay / GenerateNextTrackEvent / HandleEvent)
//
// ARR header: u32 tTab, pTab, tmTab, mTrack, info, loopPoint[16], tsTab. Songs
// on this disc were built with a short header (tTab = 0x18), so the header
// only extends up to the first table; header words beyond that belong to the
// track table.
// tTab: u32[64] track offsets (0 = none).
// TENTRY (0xC): u32 time; u8 prgChange, velocity, res[2]; u16 pattern;
//   s8 transpose, velocityAdd. pattern 0xFFFF ends the track; 0xFFFE is a loop
//   whose target entry index is read as a u16 over transpose/velocityAdd.
// pTab: u32 pattern offsets, indexed by TENTRY.pattern.
// SEQ_PATTERN: u32 headerLen, pitchBend, modulation (stream offsets), then
//   note data: {u16 time; u8 key, velocity; u16 length} (6 bytes), or 4 bytes
//   (no length) for controller events (key bit 7) and time-only steps
//   (key == velocity == 0); key == velocity == 0xFF ends the pattern.
// Pitch-bend/modulation streams, tmTab (u8[64]) and tsTab (u8[64]) are bytes.
// mTrack: MTRACK_DATA {u32 time, u32 bpm}[] ended by time 0xFFFFFFFF.
// The game never plays songs (the MIDI helpers are dead-stripped in retail),
// so nothing calls this yet; it is validated offline against all .song files.
// ---------------------------------------------------------------------------

extern "C" void port_musyx_swap_song(void* data, uint32_t size)
{
    Blob b{(uint8_t*)data, size};
    if (!b.in(0, 0x18))
        return bad("song header", 0);
    uint32_t tTab = b.be32at(0);
    uint32_t hdrEnd = 0x58;
    for (int i = 0; i < 4; i++)
    {
        uint32_t v = b.be32at(i * 4);
        if (v != 0 && v < hdrEnd)
            hdrEnd = v;
    }
    hdrEnd &= ~3u;
    if (!b.in(0, hdrEnd))
        return bad("song header", 0);
    swap32_array(b.base, hdrEnd / 4);
    uint32_t pTab, mTrack;
    memcpy(&pTab, b.base + 4, 4);
    memcpy(&mTrack, b.base + 12, 4);

    if (!b.in(tTab, 64 * 4))
        return bad("song track table", tTab);
    // Header words past hdrEnd overlap the track table; swap only the rest.
    for (uint32_t i = 0; i < 64; i++)
    {
        uint32_t off = tTab + i * 4;
        if (off >= hdrEnd)
            b.s32(off);
    }

    std::unordered_set<uint32_t> patterns;
    uint32_t maxPattern = 0;
    bool anyPattern = false;
    for (uint32_t i = 0; i < 64; i++)
    {
        uint32_t t;
        memcpy(&t, b.base + tTab + i * 4, 4);
        if (t == 0)
            continue;
        for (uint32_t e = t;; e += 12)
        {
            if (!b.in(e, 12))
            {
                bad("song track", e);
                break;
            }
            b.s32(e); // time
            uint16_t pat = b.s16(e + 8);
            if (pat == 0xFFFF)
                break;
            if (pat == 0xFFFE)
            {
                b.s16(e + 10); // loop target index
                break;
            }
            anyPattern = true;
            if (pat > maxPattern)
                maxPattern = pat;
        }
    }

    if (anyPattern)
    {
        if (!b.in(pTab, (maxPattern + 1) * 4))
            return bad("song pattern table", pTab);
        for (uint32_t i = 0; i <= maxPattern; i++)
        {
            uint32_t p = b.s32(pTab + i * 4);
            if (!patterns.insert(p).second)
                continue;
            if (!b.in(p, 12))
            {
                bad("song pattern", p);
                continue;
            }
            b.s32(p);
            b.s32(p + 4);
            b.s32(p + 8);
            for (uint32_t n = p + 12;;)
            {
                if (!b.in(n, 4))
                {
                    bad("song notes", n);
                    break;
                }
                uint8_t key = b.base[n + 2];
                uint8_t vel = b.base[n + 3];
                b.s16(n); // time
                if (key == 0xFF && vel == 0xFF)
                    break;
                if ((key & 0x80) || (key | vel) == 0)
                {
                    n += 4;
                }
                else
                {
                    if (!b.in(n, 6))
                    {
                        bad("song notes", n);
                        break;
                    }
                    b.s16(n + 4); // length
                    n += 6;
                }
            }
        }
    }

    if (mTrack != 0)
    {
        for (uint32_t m = mTrack;; m += 8)
        {
            // The terminator may be just the 4-byte time at the end of the file.
            if (!b.in(m, 4))
            {
                bad("song tempo track", m);
                break;
            }
            if (b.s32(m) == 0xFFFFFFFF)
                break;
            if (!b.in(m, 8))
            {
                bad("song tempo track", m);
                break;
            }
            b.s32(m + 4);
        }
    }
}

// ---------------------------------------------------------------------------
// DSPADPCM stream header (0x60):
//   u32 num_samples, num_adpcm_nibbles, sample_rate; u16 loop_flag, format;
//   u32 sa, ea, ca; u16 coef[16], gain, ps, yn1, yn2, lps, lyn1, lyn2, pad[11].
// ---------------------------------------------------------------------------

extern "C" void port_swap_dsp_adpcm_header(void* hdr)
{
    uint8_t* p = (uint8_t*)hdr;
    swap32_array(p, 3);
    swap16_array(p + 0x0C, 2);
    swap32_array(p + 0x10, 3);
    swap16_array(p + 0x1C, (0x60 - 0x1C) / 2);
}

extern "C" void port_swap_idsp_header(void* hdr)
{
    swap32_array((uint8_t*)hdr + 4, 2);
}
