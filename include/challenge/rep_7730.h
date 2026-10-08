#ifndef __CHALLENGE_REP_7730_H__
#define __CHALLENGE_REP_7730_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"

typedef struct {
    void* image;
    void* palette;
    u16 height;
    u16 width;
    u8 wrapS;
    u8 wrapT;
    u8 minFilter;
    u8 magFilter;
    f32 lodBias;
    u8 padding14;
    u8 minLod;
    u8 maxLod;
    u8 format;
    u16 paletteEntries;
    u8 paletteFormat;
    u8 padding1B;
} ChallengeTextureHeader;

typedef struct {
    u8 padding[0x10];
    s16 complete;
    u8 padding12[2];
    void* data;
} ChallengeTransfer;

typedef struct {
    u8 padding[0x50];
    f32 depth;
    u8 padding54[0x98];
    f32 distance;
} ChallengeProjectionState;

typedef struct {
    u8 padding[0x21];
    u8 pointCount;
    u8 drawFlat;
    u8 colorMode;
    u8 drawFull;
} ChallengeCurveDrawing;

typedef struct {
    u8 padding[0x0C];
    Vec position;
    u8 padding18[0x28];
} ChallengeCurvePoint;

void fn_1_1DE5C(void);

void fn_1_1E8C0(s32 index);

void fn_1_1DD94(void);

void fn_1_1DCE4(void);

void fn_1_1EFF4(void);

void fn_1_225B8(void);

void fn_1_1E28C(void);

void fn_1_1DDE4(f32 value);

void fn_1_1DDF4(f32 value);

void fn_1_1DE04(f32 value);

void fn_1_1DE14(f32 value);

f32 fn_1_1DE20(void);

f32 fn_1_1DE30(void);

f32 fn_1_1DE40(void);

f32 fn_1_1DE50(void);

void fn_1_267BC(void);

void fn_1_24778(void);

void fn_1_20DC8(void);

f32 fn_1_1DD48(u16 buttons, s32 reverse, f32 value, f32 positive, f32 delta, f32 negative, f32 minimum, f32 maximum);

void fn_1_20F8C(void);

void fn_1_23AD8(Mtx44 projection, Vec* camera, Vec* target);

void fn_1_1F23C(ChallengeProjectionState* state);

void fn_1_207D4(void);

void fn_1_20890(void);

void fn_1_26A34(void);

void fn_1_246AC(void);

void fn_1_26928(void);

void fn_1_2040C(void);

s32 fn_1_2051C(ChallengeTextureHeader* texture, GXTexObj* object, GXTlutObj* palette, GXTlut name);

void fn_1_202A4(void);

void fn_1_21298(ChallengeCurveDrawing* drawing);

#endif
