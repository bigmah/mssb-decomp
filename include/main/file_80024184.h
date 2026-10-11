#ifndef __MAIN_FILE_80024184_H__
#define __MAIN_FILE_80024184_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"

// MSSB texture image header (used for GXInitTexObj and texture blits).
typedef struct TexImage {
    /* 0x00 */ u8* data;
    /* 0x04 */ void* tlut;       // non-NULL: color-indexed texture
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 wrapS;
    /* 0x0D */ u8 wrapT;
    /* 0x0E */ u8 minFilter;
    /* 0x0F */ u8 magFilter;
    /* 0x10 */ f32 lodBias;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 minLOD;
    /* 0x16 */ u8 maxLOD;
    /* 0x17 */ u8 format;
    /* 0x18 */ u16 tlutEntries;
    /* 0x1A */ u8 tlutFormat;
    /* 0x1B */ u8 pad1B;
} TexImage; // size: 0x1C (lbl_800F7700 is 0x20)

// lbl_800E8558 entries.
typedef struct StarMissionIndex {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 trackerIndex;
    /* 0x2 */ u8 missionRow;
    /* 0x3 */ u8 pad3[3];
} StarMissionIndex;

// lbl_80109AE8[row][10] entries.
typedef struct StarMission {
    /* 0x0 */ s16 type;
    /* 0x2 */ s16 target;
    /* 0x4 */ s16 flags;
    /* 0x6 */ u8 pad6[4];
} StarMission;

typedef struct FielderSortInfo {
    /* 0x000 */ u8 unk0[0x252];
    /* 0x252 */ s8 kind;
    /* 0x253 */ u8 unk253;
    /* 0x254 */ s8 unk254;
    /* 0x255 */ u8 unk255[5];
    /* 0x25A */ u8 team;
    /* 0x25B */ u8 unk25B[0x19];
    /* 0x274 */ u8 active;
} FielderSortInfo;

void gOz_GXSetTexture(GXTevMode tevMode, s32 texFrac, s32 hasNormal);
void fn_80024390(f32* src, f32* out, s32 which);
void SetDisplayStateTexture(TexImage* tex, s32 map, u32 tlutName);
void fn_800245EC(Mtx44 proj, Mtx view, Vec* points, f32* out, s32 count, s32 ySign);
void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);
s32 fn_800247E4(s32 x, s32 y, s32 width, s32 bytesPerTexel);
s32 challengeStarRelatedInd(s32 team, s32 mission);
f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

#endif
