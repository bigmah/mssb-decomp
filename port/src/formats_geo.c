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
// game reads them on the CPU, e.g. skinning; GXSetArray gets le=true). Color
// arrays, display lists and names stay as they are.
#include "port/formats.h"
#include "port/endian.h"

#include <stdio.h>

#define MAX_SWAPPED 16384

typedef struct
{
    uint32_t offs[MAX_SWAPPED]; // array offsets (from the palette) already swapped
    uint32_t count;
} SwapSet;

static int swap_set_add(SwapSet* set, uint32_t off)
{
    for (uint32_t i = 0; i < set->count; i++)
        if (set->offs[i] == off)
            return 0;
    if (set->count < MAX_SWAPPED)
        set->offs[set->count++] = off;
    return 1;
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
    set.count = 0;

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
            if (arr != 0 && swap_set_add(&set, (uint32_t)(layout + arr - pal)))
                swap_comps(layout + arr, (uint32_t)*(uint16_t*)(h + 4) * h[7], comp_size(h[6]));
        }
        if (lp[1] != 0)
            swap_attr(pal, layout, layout + lp[1], 0, 0, &set); // colors stay big-endian
        if (lp[2] != 0)
        {
            for (uint32_t t = 0; t < numTex; t++)
            {
                uint8_t* h = layout + lp[2] + t * 0x10;
                swap32_inplace(h);
                swap16_inplace(h + 4);
                swap32_array(h + 8, 2);
                uint32_t arr = *(uint32_t*)h;
                if (arr != 0 && swap_set_add(&set, (uint32_t)(layout + arr - pal)))
                    swap_comps(layout + arr, (uint32_t) * (uint16_t*)(h + 4) * h[7], comp_size(h[6]));
            }
        }
        if (lp[3] != 0)
        {
            uint8_t* h = layout + lp[3];
            swap32_inplace(h);
            swap16_inplace(h + 4);
            swap32_inplace(h + 8);
            uint32_t arr = *(uint32_t*)h;
            if (arr != 0 && swap_set_add(&set, (uint32_t)(layout + arr - pal)))
            {
                // compCount 2 (NBT) is read as 3-component vectors.
                uint32_t comps = h[7] == 2 ? 3 : h[7];
                swap_comps(layout + arr, (uint32_t) * (uint16_t*)(h + 4) * comps, comp_size(h[6]));
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
    if (set.count == MAX_SWAPPED)
        fprintf(stderr, "[port] geo palette %p: too many arrays to track\n", palette);
}

// Actor layout (C3 ActorLayout / MSSB MActorLayout, include/C3/actor.h):
//   header 0x20: u32 version, u16 actorID, u16 totalBones, u32 hierarchy.Offset,
//                u32 hierarchy.Root, u32 geoPaletteName, u16 skinFileID,
//                u16 pad16, u32 userDataSize, u32 userData
//   bones[totalBones] 0x1C at +0x20: u32 orientationCtrl, u32 branch[4],
//                u16 geoFileID, u16 boneID, u8 inheritance, u8 priority, u16 flags
//   orientation controls (Control, 0x3C): u8 type, u8 pad, u16 pad16, f32[14]
// All pointers are offsets from the layout.
void port_swap_actor_layout(void* layoutFile)
{
    uint8_t* lay = (uint8_t*)layoutFile;
    static SwapSet set;
    set.count = 0;

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
            swap16_inplace(lay + ctrl + 2);
            swap32_array(lay + ctrl + 4, 14);
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
    set.count = 0;

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
    if (set.count == MAX_SWAPPED)
        fprintf(stderr, "[port] anim bank %p: too many key frames to track\n", bankFile);
}
