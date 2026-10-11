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

// Same layout as RigidBody (main/file_80037054.h); simulated by fn_800385F0/fn_80037BAC.
typedef struct {
    /* 0x000 */ Vec p0;
    /* 0x00C */ Vec p1;
    /* 0x018 */ Vec d;
    /* 0x024 */ u8 pad24[0x50 - 0x24];
    /* 0x050 */ f32 depth;
    /* 0x054 */ f32 unk54;
    /* 0x058 */ Mtx world;
    /* 0x088 */ Mtx rot;
    /* 0x0B8 */ Mtx invRot;
    /* 0x0E8 */ Vec pos;
    /* 0x0F4 */ Quaternion quat;
    /* 0x104 */ u8 pad104[0x140 - 0x104];
    /* 0x140 */ Vec angVel;
    /* 0x14C */ u8 pad14C[0x154 - 0x14C];
} ChallengeProjectionState; // size 0x154

typedef struct {
    u8 padding[0x18];
    f32 scale;
    f32 unk1C;
    u8 steps;
    u8 pointCount;
    u8 drawFlat;
    u8 colorMode;
    u8 drawFull;
    u8 unk25;
} ChallengeCurveDrawing;

typedef struct {
    u8 padding[0x0C];
    Vec position;
    u8 padding18[0x24];
    s32 mode;
} ChallengeCurvePoint;

typedef struct {
    f32 params[6];
    f32 step;
    f32 stepSq;
    s32 steps;
    f32 inv;
} ChallengeCurveTiming;

typedef struct {
    f32 scale;
    u8 padding4[8];
    Vec position;
    u8 padding18[0xC];
    Vec side;
    Vec up;
    u8 padding3C[4];
} ChallengePathNode;

typedef struct {
    u32 unk0;
    Vec current;
    u32 unk10;
} ChallengeCurveCamera;

// Debug/texture test state (queue object): value/toggle/cursor/stageCount are edited by fn_1_1FD78.
typedef struct {
    /* 0x00 */ u8 pad0[0x1C];
    /* 0x1C */ u32 value;
    /* 0x20 */ u8 toggle;
    /* 0x21 */ u8 cursor;
    /* 0x22 */ u8 stageCount;
    /* 0x23 */ u8 unk23;
} ChallengeTextureStages;

typedef struct {
    /* 0x00 */ Mtx view;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u16 unk32;
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ Vec target;
    /* 0x48 */ Vec camera;
    /* 0x54 */ u8 pad54[4];
} ChallengeCameraState; // size 0x58


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

void fn_1_20640(ChallengeTextureStages* stages, u32* indices);

void fn_1_1D944(void);

void fn_1_247A0(void);

void fn_1_21180(ChallengeCurveDrawing* arg);

void fn_1_248BC(s32 count);

void fn_1_22DF4(ChallengeCurveDrawing* arg);

void fn_1_1F05C(void);

void fn_1_1F418(u8* menu);

void fn_1_1F2D8(void);

void fn_1_22F4C(s32 h, s32 w, f32* out, f32* cur, f32* prev);

void fn_1_24A8C(void);

void fn_1_20E00(u8* obj);

void fn_1_20BD8(void);

void fn_1_22644(void);

void fn_1_2004C(void);

void fn_1_1DA54(void);

void fn_1_24410(void);

void fn_1_1D694(u8* obj);
void fn_1_21040(void);
void fn_1_20950(ChallengeCurvePoint* points, s32 count, MtxPtr camera);
void fn_1_23804(s32 arg0, s32 arg1, s32 rows, s32 cols, f32 arg4, f32 arg5);
void fn_1_1FD78(ChallengeTextureStages* menu);
void fn_1_1F618(ChallengeTextureStages* stages);
void fn_1_1E5D0(ChallengeProjectionState* body);
void fn_1_25C68(void);
s16 fn_1_1E290(s16 sel, u16 held, u16 pressed, u16 repeat);

#endif
