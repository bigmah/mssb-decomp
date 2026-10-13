// Byte-swap pass for geometry palettes (charPipeline DODisplayData files,
// include/C3/geoPalette.h), run once at load before the game relocates them.
//
// Disc layout (big-endian, offsets relative to the palette unless noted):
//   DODisplayData  0x14: u32 version, u32 userDataSize, u32 userData,
//                        u32 numDescriptors, u32 descriptorArray
//   DODescriptor   0x08: u32 layout, u32 name
//   DODisplayLayout 0x34 (pointers relative to the layout):
//                        u32 positionData, colorData, textureData,
//                        lightingData, displayData; u8 numTextureChannels,
//                        u8 unk15, u16 pad16; u32 unk18; f32 bounds[6]
//   PositionData/ColorData 0x08: u32 array, u16 count, u8 quantizeInfo, u8 compCount
//   TextureData    0x10: u32 coordArray, u16 count, u8 quant, u8 compCount,
//                        u32 paletteName, u32 palette
//   LightingData   0x0C: u32 normalArray, u16 count, u8 quant, u8 compCount, f32 ambient
//   DisplayData    0x0C: u32 primitiveBank, u32 stateList, u16 numStates, u16 pad
//   DisplayStateList 0x10: u8 id, u8 pad, u16 pad16, u32 setting,
//                        u32 primitiveList, u32 listSize
//
// Position, texture coordinate and normal arrays are swapped to native (the
// game reads them on the CPU, e.g. skinning; GXSetArray gets le=true), and
// so are 16-bit color arrays. Byte colors, display lists and names stay.
#include "port/formats.h"
#include "port/endian.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SWAPPED 16384

// Offsets (from the file) already swapped: an open-addressing hash set, since
// one animation bank has tens of thousands of key frames.
typedef struct
{
    uint32_t* slots; // UINT32_MAX: empty
    uint32_t cap;    // power of two
    uint32_t count;
} SwapSet;

static void swap_set_clear(SwapSet* set)
{
    set->count = 0;
    if (set->slots != NULL)
        memset(set->slots, 0xFF, set->cap * sizeof(uint32_t));
}

static int swap_set_insert(SwapSet* set, uint32_t off)
{
    uint32_t mask = set->cap - 1;
    for (uint32_t i = (off * 2654435761u) & mask;; i = (i + 1) & mask)
    {
        if (set->slots[i] == off)
            return 0;
        if (set->slots[i] == UINT32_MAX)
        {
            set->slots[i] = off;
            set->count++;
            return 1;
        }
    }
}

static int swap_set_add(SwapSet* set, uint32_t off)
{
    if ((set->count + 1) * 2 > set->cap)
    {
        uint32_t* old = set->slots;
        uint32_t oldCap = set->cap;
        set->cap = oldCap != 0 ? oldCap * 2 : 1024;
        set->slots = (uint32_t*)malloc(set->cap * sizeof(uint32_t));
        swap_set_clear(set);
        for (uint32_t i = 0; i < oldCap; i++)
            if (old[i] != UINT32_MAX)
                swap_set_insert(set, old[i]);
        free(old);
    }
    return swap_set_insert(set, off);
}

static uint32_t comp_size(uint8_t quant)
{
    switch (quant >> 4)
    {
    case 0: // GX_U8
    case 1: // GX_S8
        return 1;
    case 2: // GX_U16
    case 3: // GX_S16
        return 2;
    case 4: // GX_F32
        return 4;
    default:
        return 0;
    }
}

static void swap_comps(uint8_t* p, uint32_t n, uint32_t size)
{
    if (size == 2)
        swap16_array(p, n);
    else if (size == 4)
        swap32_array(p, n);
}

// Byte ranges (from the palette) of vertex arrays already swapped. Arrays
// overlap: a skin's normals are interleaved with its positions (position
// compCount 6, normal array = positions + one vector), so each array swaps
// only the parts no earlier array covered.
typedef struct
{
    uint32_t start[MAX_SWAPPED];
    uint32_t end[MAX_SWAPPED];
    uint32_t count;
} RangeSet;

static void swap_array_range(RangeSet* set, uint8_t* pal, uint8_t* data, uint32_t n, uint32_t size)
{
    if (size < 2 || n == 0)
        return;
    uint32_t lo = (uint32_t)(data - pal);
    uint32_t hi = lo + n * size;
    // Walk [lo, hi), swapping the gaps between covered ranges.
    uint32_t cur = lo;
    while (cur < hi)
    {
        uint32_t next = hi; // end of the uncovered gap starting at cur
        int covered = 0;
        for (uint32_t i = 0; i < set->count; i++)
        {
            if (set->start[i] <= cur && cur < set->end[i])
            {
                cur = set->end[i];
                covered = 1;
                break;
            }
            if (set->start[i] > cur && set->start[i] < next)
                next = set->start[i];
        }
        if (covered)
            continue;
        swap_comps(pal + cur, (next - cur) / size, size);
        cur = next;
    }
    if (set->count < MAX_SWAPPED)
    {
        set->start[set->count] = lo;
        set->end[set->count] = hi;
        set->count++;
    }
}

// An attribute array {u32 array, u16 count, u8 quant, u8 compCount}: swap the
// header and, if numeric, the array itself (count * comps elements).
static void swap_attr(uint8_t* pal, uint8_t* layout, uint8_t* hdr, uint32_t compsPer, int swapArray, SwapSet* set)
{
    swap32_inplace(hdr);
    swap16_inplace(hdr + 4);
    uint32_t arr = *(uint32_t*)hdr;
    uint16_t count = *(uint16_t*)(hdr + 4);
    if (!swapArray || arr == 0)
        return;
    uint8_t* data = layout + arr;
    if (!swap_set_add(set, (uint32_t)(data - pal)))
        return;
    uint32_t size = comp_size(hdr[6]);
    swap_comps(data, (uint32_t)count * compsPer, size);
}

void port_swap_geo_palette(void* palette)
{
    uint8_t* pal = (uint8_t*)palette;
    static SwapSet set;
    static RangeSet ranges;
    swap_set_clear(&set);
    ranges.count = 0;

    swap32_array(pal, 5);
    uint32_t numDesc = ((uint32_t*)pal)[3];
    uint8_t* desc = pal + ((uint32_t*)pal)[4];
    swap32_array(desc, numDesc * 2);

    for (uint32_t i = 0; i < numDesc; i++)
    {
        uint32_t layoutOff = ((uint32_t*)desc)[i * 2];
        if (!swap_set_add(&set, layoutOff | 0x80000000u))
            continue; // layout shared with an earlier descriptor
        uint8_t* layout = pal + layoutOff;
        swap32_array(layout, 5);
        swap16_inplace(layout + 0x16);
        swap32_inplace(layout + 0x18);
        swap32_array(layout + 0x1C, 6);
        uint32_t* lp = (uint32_t*)layout;
        uint8_t numTex = layout[0x14];

        if (lp[0] != 0)
        {
            uint8_t* h = layout + lp[0];
            // compCount is 3 (xyz) or 6 (position + normal, skinned).
            swap_attr(pal, layout, h, 0, 0, &set);
            uint32_t arr = *(uint32_t*)h;
            if (arr != 0)
                swap_array_range(&ranges, pal, layout + arr, (uint32_t)*(uint16_t*)(h + 4) * h[7], comp_size(h[6]));
        }
        if (lp[1] != 0)
        {
            // 16-bit colors (RGB565, RGBA4) to native (the game blends RGBA4
            // morph targets on the CPU); 24/32-bit colors are bytes.
            uint8_t* h = layout + lp[1];
            swap_attr(pal, layout, h, 0, 0, &set);
            uint32_t arr = *(uint32_t*)h;
            uint8_t fmt = h[6] >> 4;
            if (arr != 0 && (fmt == 0 || fmt == 3))
                swap_array_range(&ranges, pal, layout + arr, *(uint16_t*)(h + 4), 2);
        }
        if (lp[2] != 0)
        {
            for (uint32_t t = 0; t < numTex; t++)
            {
                uint8_t* h = layout + lp[2] + t * 0x10;
                swap32_inplace(h);
                swap16_inplace(h + 4);
                swap32_array(h + 8, 2);
                uint32_t arr = *(uint32_t*)h;
                if (arr != 0)
                    swap_array_range(&ranges, pal, layout + arr, (uint32_t) * (uint16_t*)(h + 4) * h[7], comp_size(h[6]));
            }
        }
        if (lp[3] != 0)
        {
            uint8_t* h = layout + lp[3];
            swap32_inplace(h);
            swap16_inplace(h + 4);
            swap32_inplace(h + 8);
            uint32_t arr = *(uint32_t*)h;
            if (arr != 0)
            {
                // compCount 2 (NBT) is read as 3-component vectors.
                uint32_t comps = h[7] == 2 ? 3 : h[7];
                swap_array_range(&ranges, pal, layout + arr, (uint32_t) * (uint16_t*)(h + 4) * comps, comp_size(h[6]));
            }
        }
        if (lp[4] != 0)
        {
            uint8_t* h = layout + lp[4];
            swap32_array(h, 2);
            swap16_array(h + 8, 2);
            uint32_t states = *(uint32_t*)(h + 4);
            uint16_t numStates = *(uint16_t*)(h + 8);
            if (states != 0)
            {
                for (uint32_t s = 0; s < numStates; s++)
                {
                    uint8_t* st = layout + states + s * 0x10;
                    swap16_inplace(st + 2);
                    swap32_array(st + 4, 3);
                }
            }
        }
    }
    if (ranges.count == MAX_SWAPPED)
        fprintf(stderr, "[port] geo palette %p: too many arrays to track\n", palette);
}

// Actor layout (C3 ActorLayout / MSSB MActorLayout, include/C3/actor.h):
//   header 0x20: u32 version, u16 actorID, u16 totalBones, u32 hierarchy.Offset,
//                u32 hierarchy.Root, u32 geoPaletteName, u16 skinFileID,
//                u16 pad16, u32 userDataSize, u32 userData
//   bones[totalBones] 0x1C at +0x20: u32 orientationCtrl, u32 branch[4],
//                u16 geoFileID, u16 boneID, u8 inheritance, u8 priority, u16 flags
//   orientation controls 0x34: u8 type, u8 pad, u16 pad16, f32[12] (Srt or Mtx)
// All pointers are offsets from the layout.
void port_swap_actor_layout(void* layoutFile)
{
    uint8_t* lay = (uint8_t*)layoutFile;
    static SwapSet set;
    swap_set_clear(&set);

    swap32_inplace(lay);
    swap16_array(lay + 4, 2);
    swap32_array(lay + 8, 3);
    swap16_array(lay + 0x14, 2);
    swap32_array(lay + 0x18, 2);
    uint16_t totalBones = *(uint16_t*)(lay + 6);
    for (uint32_t i = 0; i < totalBones; i++)
    {
        uint8_t* bone = lay + 0x20 + i * 0x1C;
        swap32_array(bone, 5);
        swap16_array(bone + 0x14, 2);
        swap16_inplace(bone + 0x1A);
        uint32_t ctrl = *(uint32_t*)bone;
        if (ctrl != 0 && swap_set_add(&set, ctrl))
        {
            // 0x34 bytes in the file (Srt or a 3x4 matrix), packed back to
            // back: swapping the C3 Control's full 0x3C would reach into the
            // next one.
            swap16_inplace(lay + ctrl + 2);
            swap32_array(lay + ctrl + 4, 12);
        }
    }
}

// Animation bank (C3 ANIMBank, include/C3/anim.h):
//   header 0x18: u32 version, u32 animSequences, u16 bankID, u16 numSequences,
//                u16 numTracks, u16 numKeyFrames, u32 userDataSize, u32 userData
//   sequences 0x0C (at +0x18): u32 name, u32 trackArray, u16 totalTracks, u16 pad
//   tracks 0x10: f32 animTime, u32 keyFrames, u16 totalFrames, u16 trackID,
//                u8 quantizeInfo, u8 animType, u8 interpolationType, u8 replace
//   key frames 0x0C: f32 time, u32 setting, u32 interpolation
// Key frame data (layout from file_800B516C.c): setting = [scale vec]
// [scale quat] [euler vec] [quat: 4 x s16] [translation vec], or a 3x4 f32
// matrix (ANIM_MTX); interpolation = per part, Bezier: 2 vecs, Hermite: 2
// vecs + 2 x s16 ease, Squad: 2 quats (+ 2 x s16 ease). Vector components
// have the track's type (quantizeInfo >> 4).
enum
{
    ANIM_TRANS = 0x01,
    ANIM_SCALE = 0x02,
    ANIM_ROT_EULER = 0x04,
    ANIM_ROT_QUAT = 0x08,
    ANIM_MTX = 0x10,
    ANIM_SCALE_QUAT = 0x20,
};

// Swaps n components of the given size at *p and advances p.
static void swap_run(uint8_t** p, uint32_t n, uint32_t size)
{
    swap_comps(*p, n, size);
    *p += n * size;
}

// Interpolation data of a vector part (scale, euler or translation).
static void swap_vec_interp(uint8_t** p, uint32_t interp, uint32_t cs)
{
    if (interp == 2) // Bezier
        swap_run(p, 6, cs);
    else if (interp == 3) // Hermite
    {
        swap_run(p, 6, cs);
        swap_run(p, 2, 2);
    }
}

void port_swap_anim_bank(void* bankFile)
{
    uint8_t* bank = (uint8_t*)bankFile;
    static SwapSet set;
    swap_set_clear(&set);

    swap32_array(bank, 2);
    swap16_array(bank + 8, 4);
    swap32_array(bank + 0x10, 2);
    uint16_t numSeq = *(uint16_t*)(bank + 0xA);
    uint16_t numTracks = *(uint16_t*)(bank + 0xC);
    uint16_t numKeys = *(uint16_t*)(bank + 0xE);
    uint8_t* seqs = bank + 0x18;
    uint8_t* tracks = seqs + numSeq * 0xC;
    uint8_t* keys = tracks + numTracks * 0x10;

    for (uint32_t i = 0; i < numSeq; i++)
    {
        swap32_array(seqs + i * 0xC, 2);
        swap16_array(seqs + i * 0xC + 8, 2);
    }
    for (uint32_t i = 0; i < numTracks; i++)
    {
        swap32_array(tracks + i * 0x10, 2);
        swap16_array(tracks + i * 0x10 + 8, 2);
    }
    swap32_array(keys, numKeys * 3u);

    for (uint32_t i = 0; i < numTracks; i++)
    {
        uint8_t* t = tracks + i * 0x10;
        uint32_t kf = *(uint32_t*)(t + 4);
        uint16_t frames = *(uint16_t*)(t + 8);
        uint8_t quant = t[0xC], type = t[0xD], it = t[0xE];
        uint32_t cs = comp_size(quant);
        for (uint32_t f = 0; f < frames; f++)
        {
            uint8_t* key = bank + kf + f * 0xC;
            uint32_t setting = *(uint32_t*)(key + 4);
            uint32_t interp = *(uint32_t*)(key + 8);
            if (setting != 0 && swap_set_add(&set, setting))
            {
                uint8_t* p = bank + setting;
                if (type & ANIM_MTX)
                    swap_run(&p, 12, 4);
                else
                {
                    if (type & ANIM_SCALE)
                    {
                        swap_run(&p, 3, cs);
                        if (type & ANIM_SCALE_QUAT)
                            swap_run(&p, 4, cs);
                    }
                    if (type & ANIM_ROT_EULER)
                        swap_run(&p, 3, cs);
                    if (type & ANIM_ROT_QUAT)
                        swap_run(&p, 4, 2);
                    if (type & ANIM_TRANS)
                        swap_run(&p, 3, cs);
                }
            }
            if (interp != 0 && !(type & ANIM_MTX) && swap_set_add(&set, interp | 0x80000000u))
            {
                uint8_t* p = bank + interp;
                if (type & ANIM_SCALE)
                    swap_vec_interp(&p, (it >> 2) & 3, cs);
                if (type & ANIM_ROT_QUAT)
                {
                    uint32_t ri = (it >> 4) & 7;
                    if (ri == 4) // Squad
                        swap_run(&p, 8, 2);
                    else if (ri == 5) // Squad with ease
                        swap_run(&p, 10, 2);
                }
                else if (type & ANIM_ROT_EULER)
                    swap_vec_interp(&p, (it >> 4) & 7, cs);
                if (type & ANIM_TRANS)
                    swap_vec_interp(&p, it & 3, cs);
            }
        }
    }
}

// Skin file (SKNHeader / sHdr, include/main/file_800BDEA0.h):
//   header 0x24: u16 numSk1, numSk2, numAcc; u8 posNrmShift, pad;
//                u32 sk1Lists, sk2Lists, accLists, bzeroBase, bzeroSize,
//                flushIndices, flushCount
//   SKN1List 0x40: f32 m[12]; u32 vertSrc, vertDst; u16 bone, count;
//                  u8 vertSrcOffset, pad[3]
//   SKN2List 0x74: f32 m0[12], m1[12]; u32 vertSrc, weights, vertDst;
//                  u16 bone0, bone1, count; u8 vertSrcOffset, pad
//   SKNAccList 0x44: f32 m[12]; u32 vertSrc, vertIndices, vertDst, weights;
//                  u16 bone, count
// Vertices are position + normal, 6 components of compSize bytes (4: f32
// skins, 2: s16), at vertSrc + vertSrcOffset; weights are bytes, vertex
// indices and flush indices u16.
void port_swap_skin(void* skinFile, uint32_t compSize)
{
    uint8_t* hdr = (uint8_t*)skinFile;
    static SwapSet set;
    swap_set_clear(&set);

    swap16_array(hdr, 3);
    swap32_array(hdr + 8, 7);
    uint16_t n1 = ((uint16_t*)hdr)[0], n2 = ((uint16_t*)hdr)[1], na = ((uint16_t*)hdr)[2];
    uint32_t* h32 = (uint32_t*)(hdr + 8);

    for (uint32_t i = 0; i < n1 && h32[0] != 0; i++)
    {
        uint8_t* l = hdr + h32[0] + i * 0x40;
        swap32_array(l, 14);
        swap16_array(l + 0x38, 2);
        uint32_t src = *(uint32_t*)(l + 0x30);
        if (src != 0 && swap_set_add(&set, src))
            swap_comps(hdr + src + l[0x3C], *(uint16_t*)(l + 0x3A) * 6u, compSize);
    }
    for (uint32_t i = 0; i < n2 && h32[1] != 0; i++)
    {
        uint8_t* l = hdr + h32[1] + i * 0x74;
        swap32_array(l, 27);
        swap16_array(l + 0x6C, 3);
        uint32_t src = *(uint32_t*)(l + 0x60);
        if (src != 0 && swap_set_add(&set, src))
            swap_comps(hdr + src + l[0x72], *(uint16_t*)(l + 0x70) * 6u, compSize);
    }
    for (uint32_t i = 0; i < na && h32[2] != 0; i++)
    {
        uint8_t* l = hdr + h32[2] + i * 0x44;
        swap32_array(l, 16);
        swap16_array(l + 0x40, 2);
        uint16_t count = *(uint16_t*)(l + 0x42);
        uint32_t src = *(uint32_t*)(l + 0x30);
        uint32_t idx = *(uint32_t*)(l + 0x34);
        if (src != 0 && swap_set_add(&set, src))
            swap_comps(hdr + src, count * 6u, compSize);
        if (idx != 0 && swap_set_add(&set, idx))
            swap16_array(hdr + idx, count);
    }
    if (h32[5] != 0)
        swap16_array(hdr + h32[5], h32[6]);
}

// Shape (morph target) data (ShapeData, include/main/file_80024D2C.h):
//   header 0x14: u16 unk0, groupCount, targetCount, unk6; u32 groups,
//                targets, owner
//   ShapeGroup 0x0C: u16 srcCount, entryCount; u32 entryStride, entries
//   ShapeEntry (entryStride bytes): u8 unk[4], id, bits, compCount, compSize;
//                u32 ranges, src[srcCount]
//   ShapeRange: u16 start, count; a 0 count ends the list
//   ShapeTarget 0x10: u16 idx; u8 bits, fmt; u32 dataSlot, buf[2]
// Source data: for each range, count vertices of compCount components of
// compSize bytes; swapped to native like the vertex arrays they patch.
void port_swap_shape(void* shapeFile)
{
    uint8_t* h = (uint8_t*)shapeFile;
    static SwapSet set;
    swap_set_clear(&set);

    swap16_array(h, 4);
    swap32_array(h + 8, 3);
    uint16_t groupCount = ((uint16_t*)h)[1];
    uint16_t targetCount = ((uint16_t*)h)[2];
    uint32_t groups = ((uint32_t*)(h + 8))[0];
    uint32_t targets = ((uint32_t*)(h + 8))[1];

    for (uint32_t g = 0; g < groupCount && groups != 0; g++)
    {
        uint8_t* grp = h + groups + g * 0xC;
        swap16_array(grp, 2);
        swap32_array(grp + 4, 2);
        uint16_t srcCount = ((uint16_t*)grp)[0];
        uint16_t entryCount = ((uint16_t*)grp)[1];
        uint32_t stride = *(uint32_t*)(grp + 4);
        uint32_t entries = *(uint32_t*)(grp + 8);
        for (uint32_t i = 0; i < entryCount && entries != 0; i++)
        {
            uint8_t* e = h + entries + i * stride;
            swap32_array(e + 8, 1u + srcCount);
            uint32_t compCount = e[6], compSize = e[7];
            uint32_t ranges = *(uint32_t*)(e + 8);
            uint32_t verts = 0;
            if (ranges != 0)
            {
                uint16_t* r = (uint16_t*)(h + ranges);
                int fresh = swap_set_add(&set, ranges);
                for (;; r += 2)
                {
                    if (fresh)
                        swap16_array(r, 2);
                    if (r[1] == 0)
                        break;
                    verts += r[1];
                }
            }
            for (uint32_t s = 0; s < srcCount; s++)
            {
                uint32_t src = ((uint32_t*)(e + 0xC))[s];
                if (src != 0 && swap_set_add(&set, src | 0x80000000u))
                    swap_comps(h + src, verts * compCount, compSize);
            }
        }
    }
    for (uint32_t t = 0; t < targetCount && targets != 0; t++)
    {
        uint8_t* tg = h + targets + t * 0x10;
        swap16_inplace(tg);
        swap32_array(tg + 4, 3);
    }
}

// Shape animation set (ShapeAnimSet): u32 seqCount, seqs, tables, tableCount;
// seqs -> u32 offsets[seqCount] -> {u16 length, keyCount; keys[keyCount]
// {u16 bits, u8 weight, u8 target}}; tables -> u32 offsets[tableCount] -> s8[].
void port_swap_shape_anim_set(void* setFile)
{
    uint8_t* s = (uint8_t*)setFile;
    static SwapSet set;
    swap_set_clear(&set);
    swap32_array(s, 4);
    uint32_t seqCount = ((uint32_t*)s)[0];
    uint32_t seqs = ((uint32_t*)s)[1];
    uint32_t tables = ((uint32_t*)s)[2];
    uint32_t tableCount = ((uint32_t*)s)[3];
    if (seqs != 0)
    {
        uint32_t* offs = (uint32_t*)(s + seqs);
        swap32_array(offs, seqCount);
        for (uint32_t i = 0; i < seqCount; i++)
        {
            if (offs[i] == 0 || !swap_set_add(&set, offs[i]))
                continue;
            uint8_t* seq = s + offs[i];
            swap16_array(seq, 2);
            uint16_t keyCount = ((uint16_t*)seq)[1];
            for (uint32_t k = 0; k < keyCount; k++)
                swap16_inplace(seq + 4 + k * 4);
        }
    }
    if (tables != 0)
        swap32_array(s + tables, tableCount);
}
