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

// Texture info record in a sprite bank (0x20 bytes, starting at bank + 4).
typedef struct SpriteTexInfo {
    /* 0x00 */ u8 pad0[8];
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 padC[0x10];
    /* 0x1C */ u16 texIndex; // index of the record holding the image
    /* 0x1E */ u8 pad1E[2];
} SpriteTexInfo;

typedef struct SpriteBank {
    /* 0x00 */ u32 unk0;
    /* 0x04 */ SpriteTexInfo tex[1]; // variable length
} SpriteBank;

// Generic sprite element header.
typedef struct SpriteElem {
    /* 0x00 */ u8 type; // low nibble
    /* 0x01 */ u8 flags; // bit 7: flip x, bit 6: flip y, bit 4: per-corner colors
    /* 0x02 */ u16 texIdx;
} SpriteElem;

// Sprite rectangle element.
typedef struct SpriteRectElem {
    /* 0x00 */ u8 pad0[6];
    /* 0x06 */ u16 texIdx;
    /* 0x08 */ u8 flipX : 1;
    /* 0x08 */ u8 flipY : 1;
    /* 0x08 */ u8 perCorner : 1; // per-corner vertex colors
    /* 0x08 */ u8 unk8_b4 : 5;
} SpriteRectElem;

// Quad being assembled for drawing.
typedef struct QuadState {
    /* 0x00 */ QuadVtx v[4];
    /* 0x50 */ u8 pad50[0x14];
    /* 0x64 */ void* unk64;
    /* 0x68 */ void* unk68;
    /* 0x6C */ void* unk6C;
    /* 0x70 */ SpriteBank* bank;
    /* 0x74 */ u8 pad74[4];
    /* 0x78 */ void* elem;
    /* 0x7C */ u16 perCornerColor;
    /* 0x7E */ u8 unk7E;
    /* 0x7F */ u8 unk7F;
    /* 0x80 */ u8 pad80[8];
    /* 0x88 */ void (*callback)(struct QuadState*, Mtx);
    /* 0x8C */ u8 pad8C[4];
} QuadState; // size 0x90

extern QuadState lbl_80366188;
extern SpriteTexInfo* lbl_803CBBD8;

void fn_8000E7BC(SpriteElem* elem, Mtx mtx, SpriteDrawParams* params, s32 perCorner);
void SetSpriteRect(SpriteRectElem* elem, SpriteBank* bank, Mtx mtx, SpriteDrawParams* params, s32 perCorner);
void fn_8000E764(f32 angle, Vec2f* out);
void AddVec2iToQuad(SpriteQuad* quad, Mtx mtx, SpriteDrawParams* params);

#endif
