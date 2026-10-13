#ifdef TARGET_PC
// PC build: the SDK comes from aurora.
#include <dolphin/gx.h>
#else
#ifndef _DOLPHIN_GXGEOMETRY_H
#define _DOLPHIN_GXGEOMETRY_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

#include "Dolphin/GX/GXEnum.h"
#include "Dolphin/GX/GXTypes.h"

//////////// GEOMETRY FUNCTIONS ////////////
// Basic GX functions.
extern void __GXSetDirtyState();
extern void GXBegin(GXPrimitive type, GXVtxFmt format, u16 numVertices);
extern void __GXSendFlushPrim();

// Attr functions.
extern void GXSetVtxDesc(GXAttr attr, GXAttrType type);
extern void GXClearVtxDesc();

extern void GXSetVtxAttrFmt(GXVtxFmt format, GXAttr attr, GXCompCnt count, GXCompType type, u8 frac);
extern void GXSetVtxAttrFmtv(GXVtxFmt format, GXVtxAttrFmtList* list);

extern void GXSetArray(GXAttr attr, void* basePtr, u8 stride);
extern void GXInvalidateVtxCache();
extern void GXSetTexCoordGen2(GXTexCoordID coord, GXTexGenType genType, GXTexGenSrc srcParam, u32 mtx, GXBool doNormalise, u32 postMtx);
extern void GXSetNumTexGens(u8 count);

// Geometry functions.
extern void GXSetLineWidth(u8 width, GXTexOffset offset);
extern void GXSetPointSize(u8 pointSize, GXTexOffset offset);
extern void GXEnableTexOffsets(GXTexCoordID coord, GXBool enableLine, GXBool enablePoint);
extern void __GXSetGenMode();

// Cull and manip functions.
extern void GXSetCullMode(GXCullMode mode);
extern void GXSetCoPlanar(GXBool doEnable);

// Unused/inlined in P2.
extern void GXSetVtxDescv(GXVtxDescList* attrList);
extern void GXGetVtxDesc(GXAttr attr, GXAttrType* type);
extern void GXGetVtxDescv(GXVtxDescList* list);
extern void GXGetVtxAttrFmtv(GXVtxFmt format, GXVtxAttrFmtList* list);
extern void GXGetLineWidth(u8* width, GXTexOffset* offset);
extern void GXGetPointSize(u8* pointSize, GXTexOffset* offset);
extern void GXGetCullMode(GXCullMode* mode);

////////////////////////////////////////////

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
#endif // TARGET_PC

// GXSetArray for an array the game builds or initialises itself (not loaded
// from disc). On PC it holds native byte order and aurora copies `size`
// bytes of it to the GPU, so pass both. GX_RGBA8 colours are fetched byte by
// byte (R, G, B, A in memory), so u32 colours must be stored big-endian.
#ifndef GX_SET_ARRAY_NATIVE
#ifdef TARGET_PC
#define GX_SET_ARRAY_NATIVE(attr, data, size, stride) (GXSetArray)((attr), (data), (size), (stride), true)
#else
#define GX_SET_ARRAY_NATIVE(attr, data, size, stride) GXSetArray((attr), (data), (stride))
#endif
#endif
