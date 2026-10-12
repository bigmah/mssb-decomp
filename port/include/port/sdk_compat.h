// Names the decomp's own SDK headers (include/Dolphin) use that aurora's
// headers spell differently or lack. Included by the prelude after aurora's
// SDK headers, so every game TU sees the same SDK.
#pragma once

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

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
