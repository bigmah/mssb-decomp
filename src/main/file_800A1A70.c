#include "main/file_800A1A70.h"
#include "Dolphin/OS/OSUtil.h"

extern u8 lbl_8010F158[]; // GD2HWFiltConv
extern u8 lbl_803CBA98[8]; // GDTexMode0Ids
extern u8 lbl_803CBAA0[8]; // GDTexMode1Ids
extern u8 lbl_803CBAA8[8]; // GDTexImage0Ids
extern u8 lbl_803CBAB0[8]; // GDTexImage3Ids
extern u8 lbl_803CBAB8[8]; // GDTexTlutIds

// .text:0x800A1A70 size:0x18
void GDInitGDLObj(GDLObj* dl, void* start, u32 length) {
    dl->start = (u8*)start;
    dl->ptr = (u8*)start;
    dl->top = (u8*)start + length;
    dl->length = length;
}

// .text:0x800A1A88 size:0xF8
void GDPadCurr32(void) {
    u32 n = (u32)__GDCurrentDL->ptr & 0x1F;

    if (n != 0) {
        for (; n < 32; n++) {
            __GDWrite(0);
        }
    }
}

// .text:0x800A1B80 size:0x30
void GDOverflowed(void) {
    if (lbl_803CC0F4 != NULL) {
        lbl_803CC0F4();
    }
}

// .text:0x800A1BB0 size:0x28C
void GDSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp logic_op) {
    return;
}

// .text:0x800A1E3C size:0x104
void GDSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1) {
    return;
}

// .text:0x800A1F40 size:0x254
void GDSetTexLookupMode(GXTexMapID id, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXTexFilter min_filt,
                        GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias, u8 bias_clamp,
                        u8 do_edge_lod, GXAnisotropy max_aniso) {
    return;
}

// .text:0x800A2194 size:0x100
void GDSetTexImgAttr(GXTexMapID id, u16 width, u16 height, GXTexFmt format) {
    return;
}

// .text:0x800A2294 size:0xE8
void GDSetTexImgPtr(GXTexMapID id, void* image_ptr) {
    return;
}

// .text:0x800A237C size:0xF0
void GDSetTexTlut(GXTexMapID id, u32 tmem_addr, GXTlutFmt format) {
    return;
}

// .text:0x800A246C size:0x290
void GDSetTexCoordScale2(GXTexCoordID coord, u16 s_scale, u8 s_bias, u8 s_wrap, u16 t_scale, u8 t_bias,
                         u8 t_wrap) {
    return;
}

// .text:0x800A26FC size:0x460
void GDLoadTlut(void* tlut_ptr, u32 tmem_addr, GXTlutSize size) {
    return;
}
