#include "challenge/rep_00B0.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "Dolphin/OS/OSCache.h"
#include "stl/math.h"
#include <string.h>

extern void OSReport(const char* msg, ...);
extern void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);

// Challenge-wide graphics state (shared with rep_0138, which accesses it by offset).
typedef struct ChalGfxState {
    /* 0x000 */ Mtx viewMtx;
    /* 0x030 */ u8 unk30[0x20C - 0x30];
    /* 0x20C */ GDLObj dl;
    /* 0x21C */ u8* dlBuf;
    /* 0x220 */ u32 dlSize;
    /* 0x224 */ ChalColModel* colModel;
    /* 0x228 */ s16 numBlocks;
    /* 0x22A */ u8 unk22A[0x22E - 0x22A];
    /* 0x22E */ s16 selBlock;
    /* 0x230 */ u8 unk230[0x239 - 0x230];
    /* 0x239 */ s8 showBox;
    /* 0x23A */ u8 unk23A[0x240 - 0x23A];
} ChalGfxState;

extern ChalGfxState lbl_1_common_bss_472B4;

// .data 0x200..0x298 (file statics; the split leaves them in the unsplit data section).
static Vec lbl_1_data_200[2] = {
    { 0.21f, -3.0f, 17.26f },
    { 0.21f, 3.0f, 17.26f },
}; // debug ray
static Vec lbl_1_data_218 = { 0.0f, 1.0f, 0.0f }; // up vector for the ray matrix
static Vec lbl_1_data_224 = { 0.0f, 0.0f, 0.0f }; // hit point in ray space
static u32 lbl_1_data_230[4] = { 0, 0, 0, 0 };
static GXColor lbl_1_data_240[21] = {
    { 0x00, 0xC0, 0x00, 0xFF }, { 0x00, 0x70, 0x00, 0xFF }, { 0x00, 0x00, 0xC0, 0xFF },
    { 0x00, 0x00, 0x70, 0xFF }, { 0xC0, 0x00, 0x00, 0xFF }, { 0x70, 0x00, 0x00, 0xFF },
    { 0xC0, 0xC0, 0x00, 0xFF }, { 0x70, 0x70, 0x00, 0xFF }, { 0x00, 0xC0, 0xC0, 0xFF },
    { 0x00, 0x70, 0x70, 0xFF }, { 0xC0, 0x00, 0xC0, 0xFF }, { 0x70, 0x00, 0x70, 0xFF },
    { 0xFF, 0x00, 0x00, 0x40 }, { 0x00, 0xFF, 0x00, 0x40 }, { 0xFF, 0xFF, 0x00, 0x40 },
    { 0x00, 0x00, 0xFF, 0x40 }, { 0xFF, 0x00, 0xFF, 0x40 }, { 0x00, 0xFF, 0xFF, 0x40 },
    { 0xC0, 0xC0, 0x20, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0x3A, 0x6E, 0xA5, 0xFF },
}; // debug colors (GX_VA_CLR0 index array)
static GXColor lbl_1_data_294 = { 0x00, 0x00, 0x00, 0x00 }; // copy clear color

const f32 lbl_1_rodata_B0[20] = {
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
};

// Corners of the selected block's bounding box.
Vec lbl_1_bss_60[8];

#define CHAL_COLOR(id) (u8)(((u32)(id) >> 7) + (((u32)(id) & 0x7F) - 1) * 2)

// .text:0x000019AC size:0x24C
void fn_1_19AC(void) {
    return;
}

// .text:0x00001BF8 size:0x1C4
void fn_1_1BF8(ChalColBox* boxes, s32 index) {
    return;
}

// .text:0x00001DBC size:0x800
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s8 color) {
    return;
}

// .text:0x000025BC size:0x187C
void fn_1_25BC(ChalColBlock* block) {
    return;
}

// .text:0x00003E38 size:0x23C
void fn_1_3E38(Vec* pos, u32 id) {
    return;
}

// .text:0x00004074 size:0x21C
void fn_1_4074(Vec* pos) {
    return;
}

// .text:0x00004290 size:0x498
void fn_1_4290(Vec* line) {
    GDBegin(GX_LINES, GX_VTXFMT0, 2);
    GDPosition3f32(line[0].x, line[0].y, line[0].z);
    GDColor1x8(0x13);
    GDPosition3f32(line[1].x, line[1].y, line[1].z);
    GDColor1x8(0x14);
}

#define SIGN_BITS(f) (*(s32*)&(f))

// .text:0x00004728 size:0x2FC
u32 fn_1_4728(Vec* ray, Vec* out) {
    return 0;
}

// .text:0x00004A24 size:0x3B4
void fn_1_4A24(ChalRayCast* cast, ChalColBlock* block) {
    return;
}

