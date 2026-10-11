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

// Rope node (same layout as RopeNode in main/file_80037054.h).
typedef struct {
    /* 0x00 */ f32 mass;
    /* 0x04 */ u8 padding4[0x08];
    /* 0x0C */ Vec position;
    /* 0x18 */ Vec prevPos;
    /* 0x24 */ u8 padding24[0x18];
    /* 0x3C */ s32 mode;
} ChallengeCurvePoint;

// Queue object of the wave-surface test mode (fn_1_24410 / fn_1_23B54).
typedef struct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ f32 farZ;
    /* 0x18 */ f32 nearZ;
    /* 0x1C */ f32 impulse;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u16 frame;
    /* 0x26 */ u8 cursor;
    /* 0x27 */ u8 lines;
    /* 0x28 */ u8 cols;
    /* 0x29 */ u8 rows;
    /* 0x2A */ u8 freeze;
    /* 0x2B */ u8 waveOn;
    /* 0x2C */ u8 buffer;
} ChallengeWaveState;

// Queue object of the sprite-animation viewer (fn_1_25F98).
typedef struct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ struct ChallengeSpriteTask* sprite;
    /* 0x18 */ u16 trackCount;
    /* 0x1A */ s16 x;
    /* 0x1C */ s16 y;
    /* 0x1E */ u8 pad1E[3];
    /* 0x21 */ u8 track;
    /* 0x22 */ u8 cursor;
    /* 0x23 */ u8 hold;
    /* 0x24 */ u8 frame;
} ChallengeSpriteViewer;

// Sprite task created by fn_80034E20 (only the fields used here).
typedef struct ChallengeSpriteTask {
    /* 0x00 */ u8 pad0[0x10];
    /* 0x10 */ u16 done;
    /* 0x12 */ u8 pad12[2];
    /* 0x14 */ u16 slot; // index into lbl_80371C30
} ChallengeSpriteTask;

// Texture/animation bank (same layout as SpaniTexSlot in main/file_80034F50.h).
typedef struct {
    /* 0x00 */ Mtx mtx;
    /* 0x30 */ void* data;
    /* 0x34 */ u8* tex;
    /* 0x38 */ struct Anim* anim;
} ChallengeTexSlot;

typedef struct {
    Mtx m;
} ChallengeMtxBox;

// Sprite descriptor passed to fn_80034E20 (lbl_1_data_10344, 0x40 bytes).
typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ s16 track;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ u8 padC[0x34];
} ChallengeSpriteDesc;

// Queue object of the path (spline) test mode (fn_1_25C68 / fn_1_25064 / fn_1_24A8C).
typedef struct {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ u8 pad4[0x8];
    /* 0x0C */ ChallengeTransfer* transfer;
    /* 0x10 */ u8 pad10[4];
    /* 0x14 */ f32 param1;
    /* 0x18 */ u16 param2;
    /* 0x1A */ u16 param0;
    /* 0x1C */ u16 param3;
    /* 0x1E */ u16 param4;
    /* 0x20 */ u16 param5;
    /* 0x22 */ u16 force;
    /* 0x24 */ u16 mass;
    /* 0x26 */ u16 unk26;
    /* 0x28 */ u16 unk28;
    /* 0x2A */ u8 steps;
    /* 0x2B */ u8 count;
    /* 0x2C */ u8 cursor;
} ChallengePathTest;

// Rope mass point used by fn_1_24C4C (0x3C bytes, cf. RopeNode in main/file_80037054.h).
typedef struct {
    /* 0x00 */ f32 mass;
    /* 0x04 */ f32 invMass;
    /* 0x08 */ Vec pos;
    /* 0x14 */ Vec prevPos;
    /* 0x20 */ Vec vel;
    /* 0x2C */ Vec force;
    /* 0x38 */ u32 fixed;
} ChallengeRopeNode;

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
s16 fn_1_1E90C(s16 sel, u16 held, u16 pressed, u16 repeat);
s16 fn_1_1DE60(s16 sel, u16 held, u16 pressed, u16 repeat);
void fn_1_1F900(ChallengeTextureStages* stages);
void fn_1_24C4C(ChallengeRopeNode* nodes, s32 count, Vec* force, f32 springK, f32 damping, f32 restLen, f32 dtScale);
s32 fn_1_22874(void);
s32 fn_1_23098(Mtx44 proj, Mtx camera, s32 lines, s32 cols, f32 nearZ, f32 farZ);
void fn_1_23B54(void);
void fn_1_21CE8(void);
void fn_1_21408(void);
void fn_1_25F98(void);
void fn_1_25064(void);

#endif
