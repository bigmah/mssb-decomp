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
    GDWriteBPCmd(0xFE00FFE3);
    GDWriteBPCmd((u32)(type == GX_BM_BLEND || type == GX_BM_SUBTRACT) << 0 | (u32)(type == GX_BM_LOGIC) << 1 |
                 (u32)0 << 2 | (u32)0 << 3 | (u32)0 << 4 | (u32)dst_factor << 5 | (u32)src_factor << 8 |
                 (u32)(type == GX_BM_SUBTRACT) << 11 | (u32)logic_op << 12 | (u32)0x41 << 24);
}

// .text:0x800A1E3C size:0x104
void GDSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1) {
    GDWriteBPCmd((u32)ref0 << 0 | (u32)ref1 << 8 | (u32)comp0 << 16 | (u32)comp1 << 19 | (u32)op << 22 |
                 (u32)0xF3 << 24);
}

// .text:0x800A1F40 size:0x254
// NONMATCHING 99%: code is identical; the 32.0f/16.0f literals land in our own .sdata2 instead of
// lbl_803CCEC0/lbl_803CCEC4 (needs a .sdata2 split 0x803CCEC0-0x803CCEC8 for this unit; extern f32 schedules differently)
#if NONMATCHING
void GDSetTexLookupMode(GXTexMapID id, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, GXTexFilter min_filt,
                        GXTexFilter mag_filt, f32 min_lod, f32 max_lod, f32 lod_bias, u8 bias_clamp,
                        u8 do_edge_lod, GXAnisotropy max_aniso) {
    GDWriteBPCmd((u32)wrap_s << 0 | (u32)wrap_t << 2 | (u32)(mag_filt == GX_LINEAR) << 4 |
                 (u32)lbl_8010F158[min_filt] << 5 | (u32)(!do_edge_lod) << 8 | (u32)(u8)(32.0f * lod_bias) << 9 |
                 (u32)max_aniso << 19 | (u32)bias_clamp << 21 | (u32)lbl_803CBA98[id] << 24);
    GDWriteBPCmd((u32)(u8)(16.0f * min_lod) << 0 | (u32)(u8)(16.0f * max_lod) << 8 | (u32)lbl_803CBAA0[id] << 24);
}
#endif

// .text:0x800A2194 size:0x100
void GDSetTexImgAttr(GXTexMapID id, u16 width, u16 height, GXTexFmt format) {
    GDWriteBPCmd((u32)(width - 1) << 0 | (u32)(height - 1) << 10 | (u32)format << 20 | (u32)lbl_803CBAA8[id] << 24);
}

// .text:0x800A2294 size:0xE8
void GDSetTexImgPtr(GXTexMapID id, void* image_ptr) {
    GDWriteBPCmd((u32)(OSCachedToPhysical(image_ptr) >> 5) << 0 | (u32)lbl_803CBAB0[id] << 24);
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
