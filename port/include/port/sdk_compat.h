// Names the decomp's own SDK headers (include/Dolphin) use that aurora's
// headers spell differently or lack. Included by the prelude after aurora's
// SDK headers, so every game TU sees the same SDK.
#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/card.h>
#include <dolphin/mtx/mtx44ext.h>

// --- MTX ---
typedef f32 Mtx23[2][3];
typedef f32 Mtx33[3][3];
typedef f32 Mtx34[3][4];
typedef f32 Mtx43[4][3];

// The decomp declares PSVECScale(src, scale, dst): on PowerPC the float goes
// in f1 whatever its position, so both orders are the same call. aurora uses
// the SDK order (src, dst, scale).
#undef PSVECScale
#define PSVECScale(src, scale, dst) C_VECScale((src), (dst), (scale))
#undef PSQUATScale
#define PSQUATScale(q, scale, r) C_QUATScale((q), (r), (scale))

// --- CARD ---
// The card work area (the decomp spells out its layout; aurora ignores it).
typedef struct CARDMemoryCard {
    u8 data[CARD_WORKAREA_SIZE];
} CARDMemoryCard;

// 4x4 matrices: aurora declares the C versions but doesn't implement them
// (port/src/mtx44.c does, as in strikers); the game calls the PS names.
void C_MTX44Scale(Mtx44 m, f32 xS, f32 yS, f32 zS);
void C_MTX44Trans(Mtx44 m, f32 xT, f32 yT, f32 zT);
void C_MTX44RotRad(Mtx44 m, char axis, f32 rad);
#define PSMTX44Identity C_MTX44Identity
#define PSMTX44Copy C_MTX44Copy
#define PSMTX44Concat C_MTX44Concat
#define PSMTX44Transpose C_MTX44Transpose
#define PSMTX44Inverse C_MTX44Inverse
#define PSMTX44Scale C_MTX44Scale
#define PSMTX44Trans C_MTX44Trans
#define PSMTX44RotRad C_MTX44RotRad

// --- GX functions aurora doesn't declare (stubbed in Phase 2) ---
void GXSetDrawSync(u16 token);
u16 GXReadDrawSync(void);
void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1);
void GXClearGPMetric(void);
void GXReadGPMetric(u32* count0, u32* count1);
u32 GXReadGP0Metric(void);
u32 GXReadGP1Metric(void);
void GXReadPixMetric(u32* topIn, u32* topOut, u32* bottomIn, u32* bottomOut, u32* clearIn, u32* copyClocks);
void GXClearPixMetric(void);
void GXSetVCacheMetric(GXVCachePerf attr);
void GXReadVCacheMetric(u32* check, u32* miss, u32* stall);
void GXClearVCacheMetric(void);

// --- GX enums under their decomp names ---
typedef enum _GXTevClampMode {
    GX_TC_LINEAR = 0,
    GX_TC_GE = 1,
    GX_TC_EQ = 2,
    GX_TC_LE = 3,
    GX_MAX_TEVCLAMPMODE,
} GXTevClampMode;

#define GX_TG_MTX3X4 GX_TG_MTX3x4
#define GX_TG_MTX2X4 GX_TG_MTX2x4
#define GX_IND_TEX_STAGE_0 GX_INDTEXSTAGE0
#define GX_IND_TEX_STAGE_1 GX_INDTEXSTAGE1
#define GX_IND_TEX_STAGE_2 GX_INDTEXSTAGE2
#define GX_IND_TEX_STAGE_3 GX_INDTEXSTAGE3
#define GX_BL_DSTCOL GX_BL_DSTCLR
#define GX_BL_INVDSTCOL GX_BL_INVDSTCLR

// aurora's GXSetArray needs the array's byte size and endianness so it can
// copy the data to the GPU. The game's arrays come from disc (big-endian).
// TODO(port): pass real sizes (GXSETARRAY) at each call site; until then the
// size is unknown (0).
#define GXSetArray(attr, data, stride) GXSetArray((attr), (data), 0, (stride), false)
// Arrays the game builds or initialises itself: native byte order, real size
// (include/Dolphin/GX/GXGeometry.h has the MWCC side).
#define GX_SET_ARRAY_NATIVE(attr, data, size, stride) (GXSetArray)((attr), (data), (size), (stride), true)

// Writes to the GX write-gather pipe (include/Dolphin/GX/GXFifo.h has the
// MWCC side): aurora's FIFO writers append the same raw values.
#ifndef MSSB_GXWGFIFO_WRITES
#define MSSB_GXWGFIFO_WRITES
#define GXWGFIFO_U8(x)  GXTexCoord1u8((u8)(x))
#define GXWGFIFO_U16(x) GXTexCoord1u16((u16)(x))
#define GXWGFIFO_S16(x) GXTexCoord1s16((s16)(x))
#define GXWGFIFO_U32(x) GXColor1u32((u32)(x))
#define GXWGFIFO_F32(x) GXTexCoord1f32((f32)(x))
#endif
