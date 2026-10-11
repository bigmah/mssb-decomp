#ifndef __MAIN_FILE_8000A0AC_H__
#define __MAIN_FILE_8000A0AC_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80008E00.h"

// Result of interpolating two layout keyframes (written by fn_8000A3EC / fn_8000AF1C).
typedef struct {
    /*0x00*/ s32 corners[4][2]; // fn_8000AF1C; fn_8000A3EC writes 8 values from LayoutKey._40
    /*0x20*/ u32 colors[4];     // RGBA, one per corner
    /*0x30*/ f32 _30;
    /*0x34*/ s16 _34;
    /*0x36*/ u8 _36;
} LayoutFrame;

// Keyframe format read by fn_8000A3EC.
typedef struct {
    /*0x00*/ u8 _00[4];
    /*0x04*/ u8 type;
    /*0x05*/ u8 blend; // 2: premultiply rgb by alpha
    /*0x06*/ u8 _06[2];
    /*0x08*/ u8 flags; // bit 2: per-corner colors, bit 4: position from the caller
    /*0x09*/ u8 _09[3];
    /*0x0C*/ s16 scale[2]; // 1/1024 units
    /*0x10*/ s16 pivot[2];
    /*0x14*/ s16 pos[2];
    /*0x18*/ u8 _18[4];
    /*0x1C*/ union {
        u8 colors[4][4];
        struct {
            /*0x1C*/ u16 _1C;
            /*0x1E*/ u16 _1E;
            /*0x20*/ u32 colors[2];
            /*0x28*/ u8 _28;
            /*0x29*/ u8 _29;
            /*0x2A*/ u8 _2A;
            /*0x2B*/ u8 _2B;
        } text; // type == 2
    } u;
    /*0x2C*/ s16 rot[3]; // 1/4096 turns, x/y/z
    /*0x32*/ u8 _32[2];
    /*0x34*/ s16 handles[4]; // bezier in/out handles for the position path
    /*0x3C*/ u8 _3C[4];
    /*0x40*/ s16 _40[8];
} LayoutKey;

// Keyframe format read by fn_8000AF1C.
typedef struct {
    /*0x00*/ u8 type;  // low nibble: 2 palette colors, 3 text
    /*0x01*/ u8 flags; // bit 1: rotate around y, bit 3: position from the caller
    /*0x02*/ u16 palette;
    /*0x04*/ s16 pos[2];
    /*0x08*/ u8 color[4];
    /*0x0C*/ u8 _0C[2];
    /*0x0E*/ s16 rot; // 1/4096 turns
    /*0x10*/ s16 scale[2]; // 1/1024 units
    /*0x14*/ s16 pivot[2];
    /*0x18*/ union {
        s16 corners[4][2];
        struct {
            /*0x18*/ u16 _18;
            /*0x1A*/ u16 _1A;
            /*0x1C*/ u32 _1C;
            /*0x20*/ u32 _20;
            /*0x24*/ u8 _24[2];
            /*0x26*/ u8 _26;
            /*0x27*/ u8 _27;
        } text; // type == 3
    } u;
} LayoutKey2;

// Point of a path interpolated by interpolatePointsBezier_Vec2s.
typedef struct {
    /*0x00*/ u8 _00[4];
    /*0x04*/ s16 x;
    /*0x06*/ s16 y;
} PathPoint;

void fn_8000A0AC(f32 t, BezierPoint* out, LayoutKey* a, LayoutKey* b);
void interpolatePointsBezier_Vec2s(f32 t, BezierPoint* out, PathPoint* p0, PathPoint* p1, PathPoint* p2,
                                   PathPoint* p3, u32 segment);
void fn_8000B9C8(void* file);

#endif
