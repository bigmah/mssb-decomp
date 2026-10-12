#ifndef __GAME_AUTO_00_0015C230_TEXT_H_
#define __GAME_AUTO_00_0015C230_TEXT_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Textured quad display entry (same layout as rep_3B70's Ent3B70).
typedef struct BallQuad {
    /* 0x00 */ u8 _00[4];
    /* 0x04 */ void (*draw)(struct BallQuad* q);
    /* 0x08 */ Mtx m;
    /* 0x38 */ f32 proj[7];
    /* 0x54 */ Vec v[4];
    /* 0x84 */ u8* counter;
} BallQuad;

// Ball quad size (x100000) and colour (lbl_3_data_273CC: pitch, lbl_3_data_273D4: hit ball).
typedef struct BallQuadStyle {
    /* 0x0 */ s32 size;
    /* 0x4 */ u32 color;
} BallQuadStyle;
extern BallQuadStyle lbl_3_data_273CC;
extern BallQuadStyle lbl_3_data_273D4;

void fn_3_15C230(BallQuad* q);

#endif
