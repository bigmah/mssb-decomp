#ifndef __GAME_AUTO_00_0015C230_TEXT_H_
#define __GAME_AUTO_00_0015C230_TEXT_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Textured quad display entry (same layout as rep_3B70's Ent3B70).
typedef struct BallQuad {
    /* 0x00 */ u8 _00[8];
    /* 0x08 */ Mtx m;
    /* 0x38 */ f32 proj[7];
    /* 0x54 */ Vec v[4];
    /* 0x84 */ u8* counter;
} BallQuad;

// Quad colours (lbl_3_data_273CC / lbl_3_data_273D4, defined in rep_3B70.c).
typedef struct QuadColor {
    /* 0x0 */ s32 _00;
    /* 0x4 */ u32 color; // RGB in the top 24 bits; the low byte is replaced by 0xFF
} QuadColor;
typedef struct QuadColor2 {
    /* 0x0 */ s32 _00;
    /* 0x4 */ u32 color;
    /* 0x8 */ s32 _08;
} QuadColor2;
extern QuadColor lbl_3_data_273CC;
extern QuadColor2 lbl_3_data_273D4;

void fn_3_15C230(BallQuad* q);

#endif
