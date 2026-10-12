// Byte swap for 2D keyframe animations ("Spani" / Anim, file_8000BA3C.c),
// run once at load from fn_8000B9C8 before its offset relocation.
//
// Layout (all offsets are file offsets, relative to the noted base):
//   Anim (0x10):   u16 width, u16 height, u8 unk4, u8 paramCount (words per
//                  decoded frame), u16 unk6 (0: old format), u32 table (rel.
//                  anim), u32 unkC (old format: palette, rel. anim; often it
//                  is the table's count word: table == 0xC)
//   Track table:   u32 count, u32 pad, u32 tracks[count] (rel. table)
//   Track:         u32 count (bit 31: flag), u32 unk4,
//                  u32 offsets[count] (rel. track): [0] loop table, then blocks
//   Loop table:    u16 count, u16 pad, then count markers of 6 u16
//                  (end, mode, start, pad x3)
//   Block (new):   u16 count, u16 size (bytes of a FULL entry), entries:
//                  u16 type (bit 15 flag, low bits AnimEntryType), u16 time,
//                  FULL: frame bytes up to size; RAW: paramCount words;
//                  SPARSE: u16 count, u16 size (words), u16 idx[count] (padded
//                  to 4), u32 values[count] at the end (frame word idx + 1);
//                  SPANS: u16 count, u16 size (words), (u16 off, u16 len)
//                  pairs, then the span bytes (frame offset 4 + off)
//   Block (old):   u16 count, u16 pad, count keys of 0x28 bytes (LayoutKey2)
//   Palette (old): u32 count, then count entries of 4 RGBA colors (u32)
//
// Frame data is swapped field by field with the maps below, so decoded
// frames (and the in-place edits fn_8000CC4C makes) are native.
#include "port/formats.h"
#include "port/endian.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Size of the field starting at `off` in a decoded (new-format) frame, or 0
// if `off` is inside a field. kind: frame byte 4.
static int frame_field(uint32_t off, int kind)
{
    if (off < 4)
        return 2; // type, time
    if (off < 6)
        return 1; // kind, blend
    if (off < 8)
        return off == 6 ? 2 : 0; // subTrack
    if (off < 0xC)
        return 1; // flags, flags2, pad
    if (off < 0x1C)
        return (off & 1) ? 0 : 2; // scale, pivot, pos, 0x18, z
    if (off < 0x2C)
    {
        if (kind != 2)
            return 1; // colors[4][4] (RGBA bytes)
        if (off < 0x20)
            return (off & 1) ? 0 : 2;
        if (off < 0x28)
            return (off & 3) ? 0 : 4; // text colors (u32)
        return 1;
    }
    if (off < 0x32)
        return (off & 1) ? 0 : 2; // rot[3]
    if (off < 0x34)
        return 1;
    if (off < 0x3C)
        return (off & 1) ? 0 : 2; // path handles
    if (off < 0x40)
        return 1;
    return (off & 1) ? 0 : 2; // 0x40: s16[8]
}

// Old-format key (0x28 bytes, LayoutKey2/AnimKeyV0). type: key byte 0.
static int key_field(uint32_t off, int type)
{
    if (off < 2)
        return 1; // type/blend, flags
    if (off < 8)
        return (off & 1) ? 0 : 2; // palette/subTrack, pos
    if (off < 0xC)
        return 1; // color
    if (off < 0x18)
        return (off & 1) ? 0 : 2; // time, rot, scale, pivot
    if ((type & 0xF) == 3)
    {
        if (off < 0x1C)
            return (off & 1) ? 0 : 2;
        if (off < 0x24)
            return (off & 3) ? 0 : 4;
        return 1;
    }
    return (off & 1) ? 0 : 2; // corners
}

static void swap_field(uint8_t* p, int size)
{
    if (size == 2)
        swap16_inplace(p);
    else if (size == 4)
        swap32_inplace(p);
}

// Swap `len` bytes at `p`, which hold frame bytes [off, off + len).
static void swap_frame_span(uint8_t* p, uint32_t off, uint32_t len, int kind)
{
    uint32_t end = off + len;
    while (off < end)
    {
        int size = off < 0x50 ? frame_field(off, kind) : 1;
        if (size == 0 || off + size > end)
        {
            // Partial field: the patch splits a scalar. Leave it.
            static int warned;
            if (!warned++)
                fprintf(stderr, "[port] spani: patch splits a field at frame offset 0x%x\n", off);
            size = 1;
        }
        else
        {
            swap_field(p, size);
        }
        p += size;
        off += size;
    }
}

typedef struct
{
    uint32_t* items;
    size_t count, cap;
} Seen;

// Returns 1 the first time `off` is seen.
static int seen_once(Seen* s, uint32_t off)
{
    for (size_t i = 0; i < s->count; i++)
        if (s->items[i] == off)
            return 0;
    if (s->count == s->cap)
    {
        s->cap = s->cap ? s->cap * 2 : 64;
        s->items = (uint32_t*)realloc(s->items, s->cap * sizeof(uint32_t));
    }
    s->items[s->count++] = off;
    return 1;
}

static void swap_block_new(uint8_t* block, uint32_t paramWords)
{
    swap16_array(block, 2);
    uint16_t count = *(uint16_t*)block;
    uint16_t size = *(uint16_t*)(block + 2);
    uint8_t* e = block + 4;
    int baseKind = e[4];
    for (uint32_t i = 0; i < count; i++)
    {
        swap16_array(e, 2);
        uint16_t type = *(uint16_t*)e & 0x7FFF;
        uint8_t* next = e;
        switch (type)
        {
        case 0: // FULL
            swap_frame_span(e + 4, 4, size - 4u, e[4]);
            next = e + size;
            break;
        case 1: // RAW
            swap_frame_span(e + 4, 4, paramWords * 4 - 4, e[4]);
            next = e + paramWords * 4;
            break;
        case 2: // SPARSE
        {
            swap16_array(e + 4, 2);
            uint16_t n = *(uint16_t*)(e + 4);
            uint16_t words = *(uint16_t*)(e + 6);
            uint16_t* idx = (uint16_t*)(e + 8);
            swap16_array(idx, n);
            uint8_t* values = e + (words - n) * 4u;
            int kind = baseKind;
            for (uint32_t j = 0; j < n; j++)
                if (idx[j] == 0)
                    kind = values[j * 4]; // patches the kind byte
            for (uint32_t j = 0; j < n; j++)
                swap_frame_span(values + j * 4, 4 + idx[j] * 4u, 4, kind);
            next = e + words * 4u;
            break;
        }
        case 3: // SPANS
        {
            swap16_array(e + 4, 2);
            uint16_t n = *(uint16_t*)(e + 4);
            uint16_t words = *(uint16_t*)(e + 6);
            uint16_t* span = (uint16_t*)(e + 8);
            swap16_array(span, n * 2u);
            uint8_t* src = e + 8 + n * 4u;
            int kind = baseKind;
            uint8_t* s = src;
            for (uint32_t j = 0; j < n; j++)
            {
                if (span[j * 2] == 0 && span[j * 2 + 1] > 0)
                    kind = s[0];
                s += span[j * 2 + 1];
            }
            for (uint32_t j = 0; j < n; j++)
            {
                swap_frame_span(src, 4 + span[j * 2], span[j * 2 + 1], kind);
                src += span[j * 2 + 1];
            }
            next = e + words * 4u;
            break;
        }
        default:
            fprintf(stderr, "[port] spani: unknown entry type %u\n", type);
            return;
        }
        e = next;
    }
}

static void swap_block_old(uint8_t* block)
{
    swap16_array(block, 2);
    uint16_t count = *(uint16_t*)block;
    uint8_t* k = block + 4;
    for (uint32_t i = 0; i < count; i++, k += 0x28)
    {
        int type = k[0];
        for (uint32_t off = 0; off < 0x28;)
        {
            int size = key_field(off, type);
            swap_field(k + off, size);
            off += size ? size : 1;
        }
    }
}

void port_swap_spani_anim(void* animp)
{
    uint8_t* anim = (uint8_t*)animp;
    swap16_array(anim, 2);
    swap16_inplace(anim + 6);
    swap32_inplace(anim + 8);
    uint32_t paramWords = anim[5];
    int oldFormat = *(uint16_t*)(anim + 6) == 0;
    uint32_t tableOff = *(uint32_t*)(anim + 8);
    if (tableOff != 0xC)
        swap32_inplace(anim + 0xC);

    uint8_t* table = anim + tableOff;
    swap32_array(table, 2);
    uint32_t ntracks = *(uint32_t*)table;
    uint32_t* tracks = (uint32_t*)(table + 8);
    swap32_array(tracks, ntracks);

    Seen seen = {0};
    for (uint32_t t = 0; t < ntracks; t++)
    {
        uint32_t trackOff = tableOff + tracks[t];
        if (!seen_once(&seen, trackOff))
            continue;
        uint8_t* track = anim + trackOff;
        swap32_array(track, 2);
        uint32_t n = *(uint32_t*)track & 0x7FFFFFFF;
        uint32_t* offs = (uint32_t*)(track + 8);
        swap32_array(offs, n);
        for (uint32_t i = 0; i < n; i++)
        {
            uint32_t off = trackOff + offs[i];
            if (!seen_once(&seen, off))
                continue;
            uint8_t* p = anim + off;
            if (i == 0)
            {
                swap16_array(p, 2);
                swap16_array(p + 4, *(uint16_t*)p * 6u);
            }
            else if (oldFormat)
            {
                swap_block_old(p);
            }
            else
            {
                swap_block_new(p, paramWords);
            }
        }
    }
    free(seen.items);

    if (oldFormat && tableOff != 0xC)
    {
        uint32_t palOff = *(uint32_t*)(anim + 0xC);
        if (palOff != 0)
        {
            uint8_t* pal = anim + palOff;
            swap32_inplace(pal);
            swap32_array(pal + 4, *(uint32_t*)pal * 4u);
        }
    }
}

