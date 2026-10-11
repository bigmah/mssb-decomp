#ifndef __MAIN_FILE_8000BA3C_H__
#define __MAIN_FILE_8000BA3C_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

typedef struct Vec2f {
    f32 x;
    f32 y;
} Vec2f;

// A 2D quad: four corner points given as x/y pairs, transformed in place into
// 3D points (stride 0x10).
typedef struct QuadPoint {
    Vec pos;
    f32 pad;
} QuadPoint;

typedef union SpriteQuad {
    f32 xy[4][2];
    QuadPoint pt[4];
} SpriteQuad;

// Per-draw parameters: integer offsets for the four corners, then their colors.
typedef struct SpriteDrawParams {
    /* 0x00 */ s32 ofs[4][2];
    /* 0x20 */ u32 color[4];
} SpriteDrawParams;

// One vertex of the quad being built in lbl_80366188.
typedef struct QuadVtx {
    /* 0x00 */ Vec pos;
    /* 0x0C */ u32 color;
    /* 0x10 */ s16 s;
    /* 0x12 */ s16 t;
} QuadVtx; // size 0x14

void fn_8000E764(f32 angle, Vec2f* out);
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params);

#endif
