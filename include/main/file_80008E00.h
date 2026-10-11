#ifndef __MAIN_FILE_80008E00_H__
#define __MAIN_FILE_80008E00_H__

#include "mssbTypes.h"
#include "main/file_8000BA3C.h" // QuadCallback

// System/reset state block at 0x80366158.
typedef struct {
    /*0x00*/ void* arenaStart;
    /*0x04*/ void* arenaEnd;
    /*0x08*/ void* arenaAfterDll; // arena position after the current dll was linked
    /*0x0C*/ u32 resetCode;
    /*0x10*/ u8 _10[0xC];
    /*0x1C*/ u8 _1C;
    /*0x1D*/ u8 _1D;
    /*0x1E*/ u8 _1E;
    /*0x1F*/ u8 _1F;
    /*0x20*/ u8 _20;
    /*0x21*/ u8 resetRequested; // hard reset (OSResetSystem restart)
    /*0x22*/ u8 _22;
    /*0x23*/ u8 _23;
    /*0x24*/ u8 _24;
    /*0x25*/ u8 _25;
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
    /*0x28*/ u8 _28;
    /*0x29*/ u8 _29;
    /*0x2A*/ u8 _2A; // logo screen state (0: loading, 2: done)
    /*0x2B*/ u8 _2B[5];
} lbl_80366158_s; // size: 0x30

extern lbl_80366158_s lbl_80366158;


// Spline control point; only x/y are used by the interpolation code.
typedef struct {
    /*0x00*/ f32 x;
    /*0x04*/ f32 y;
    /*0x08*/ f32 _08;
    /*0x0C*/ f32 _0C;
} BezierPoint; // size: 0x10

void fn_80008E00(void (*value)(void));
BOOL fn_80008E08(void);
void PostRetraceCallback(u32 retraceCount);
void fn_8000900C(void);
void* fn_80009018(void* value);
u8 fn_80009028(void);
void fn_80009094(void);
void fn_800090B4(void);
void fn_80009144(void);
void PrepFilesToBeLoaded(void);
void fn_800097A0(void);
void interpolatePointsUnknown(s32 index, BezierPoint* points, u32 first, u32 last);
void BezierInterpolate(f32 t, BezierPoint* out, BezierPoint* p0, BezierPoint* p1, BezierPoint* p2, BezierPoint* p3);
QuadCallback fn_8000A094(QuadCallback callback);

#endif
