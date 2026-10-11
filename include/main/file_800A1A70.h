#ifndef __MAIN_FILE_800A1A70_H__
#define __MAIN_FILE_800A1A70_H__

#include "mssbTypes.h"
#include "Dolphin/GX/GXEnum.h"

// Dolphin SDK GD (display-list building) library: GDBase, GDPixel, GDTev, GDTexture.

typedef void (*GDOverflowCb)(void);

typedef struct GDLObj {
    /* 0x0 */ u8* start;
    /* 0x4 */ u32 length;
    /* 0x8 */ u8* ptr;
    /* 0xC */ u8* top;
} GDLObj;

extern GDLObj* lbl_803CC0F0; // __GDCurrentDL
extern GDOverflowCb lbl_803CC0F4; // overflowcb

void GDInitGDLObj(GDLObj* dl, void* start, u32 length);
void GDPadCurr32(void);
void GDOverflowed(void);
void GDSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp logic_op);
void GDSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GDSetTexLookupMode(GXTexMapID id, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXTexFilter min_filt,
                        GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias, u8 bias_clamp,
                        u8 do_edge_lod, GXAnisotropy max_aniso);
void GDSetTexImgAttr(GXTexMapID id, u16 width, u16 height, GXTexFmt format);
void GDSetTexImgPtr(GXTexMapID id, void* image_ptr);
void GDSetTexTlut(GXTexMapID id, u32 tmem_addr, GXTlutFmt format);
void GDSetTexCoordScale2(GXTexCoordID coord, u16 s_scale, u8 s_bias, u8 s_wrap, u16 t_scale, u8 t_bias,
                         u8 t_wrap);
void GDLoadTlut(void* tlut_ptr, u32 tmem_addr, GXTlutSize size);

#define __GDCurrentDL lbl_803CC0F0

static inline void GDOverflowCheck(u32 size) {
    if (__GDCurrentDL->ptr + size > __GDCurrentDL->top) {
        GDOverflowed();
    }
}

static inline void __GDWrite(u8 data) {
    *__GDCurrentDL->ptr++ = data;
}

static inline void GDWrite_u8(u8 data) {
    GDOverflowCheck(sizeof(u8));
    __GDWrite(data);
}

static inline void GDWrite_u32(u32 data) {
    GDOverflowCheck(sizeof(u32));
    __GDWrite((u8)(data >> 24));
    __GDWrite((u8)((data >> 16) & 0xFF));
    __GDWrite((u8)((data >> 8) & 0xFF));
    __GDWrite((u8)(data & 0xFF));
}

static inline void GDWrite_u16(u16 data) {
    GDOverflowCheck(sizeof(u16));
    __GDWrite((u8)(data >> 8));
    __GDWrite((u8)(data & 0xFF));
}

static inline void GDWrite_f32(f32 data) {
    union {
        f32 f;
        u32 u;
    } fid;
    fid.f = data;
    GDWrite_u32(fid.u);
}

static inline void GDBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts) {
    GDWrite_u8((u8)(type | vtxfmt));
    GDWrite_u16(nverts);
}

static inline void GDPosition3f32(f32 x, f32 y, f32 z) {
    GDWrite_f32(x);
    GDWrite_f32(y);
    GDWrite_f32(z);
}

static inline void GDColor1x8(u8 index) {
    GDWrite_u8(index);
}

static inline void GDWriteBPCmd(u32 regval) {
    GDWrite_u8(0x61); // GX_LOAD_BP_REG
    GDWrite_u32(regval);
}

#endif
