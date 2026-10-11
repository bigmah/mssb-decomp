#include "main/file_800BDEA0.h"

// .text:0x800BDEA0 size:0xD0
void fn_800BDEA0(void) {
    return;
}

// .text:0x800BDF70 size:0x70
void fn_800BDF70(void) {
    return;
}

// .text:0x800BDFE0 size:0xBC
void fn_800BDFE0(void) {
    return;
}

// .text:0x800BE09C size:0xBC
void fn_800BE09C(void) {
    return;
}

// .text:0x800BE158 size:0x340
void fn_800BE158(void) {
    return;
}

// .text:0x800BE498 size:0x56C
void fn_800BE498(void) {
    return;
}

// .text:0x800BEA04 size:0x138
void fn_800BEA04(void) {
    return;
}

extern u8 lbl_803009F8[];

extern const f32 lbl_803CD068;
extern const f32 lbl_803CD06C;
extern const f32 lbl_803CD070;

// fn_800BEB3C, size:0x44
void fn_800BEB3C(void) {
    *(s16*)(lbl_803009F8 + 0x24) = 0;
    *(f32*)(lbl_803009F8 + 0x38) = lbl_803CD068;
    *(f32*)(lbl_803009F8 + 0x30) = lbl_803CD068;
    *(f32*)(lbl_803009F8 + 0x28) = lbl_803CD068;
    *(f32*)(lbl_803009F8 + 0x3C) = lbl_803CD06C;
    *(f32*)(lbl_803009F8 + 0x34) = lbl_803CD06C;
    *(f32*)(lbl_803009F8 + 0x2C) = lbl_803CD06C;
    *(f32*)(lbl_803009F8 + 0x48) = lbl_803CD070;
    *(f32*)(lbl_803009F8 + 0x44) = lbl_803CD070;
    *(f32*)(lbl_803009F8 + 0x40) = lbl_803CD070;
}

// fn_800BEBA0, size:0x10
u8 fn_800BEBA0(void) {
    return *(u8*)(lbl_803009F8 + 0x0);
}

// GetDrawShadows, size:0x10
u8 GetDrawShadows(void) {
    return *(u8*)(lbl_803009F8 + 0x0);
}

// fn_800BEB80, size:0x20
void* fn_800BEB80(u8 index) {
    return *(u8**)(lbl_803009F8 + 0x14) + index * 0xE0 + 0xB0;
}

// DrawShadows, size:0xC
void DrawShadows(u8 enable) {
    lbl_803009F8[0] = enable;
}

// fn_800BEC00, size:0x30
void fn_800BEC00(s32 reverse) {
    if (reverse != 0) {
        *(s8*)(lbl_803009F8 + 0x4D) = -1;
        return;
    }
    *(s8*)(lbl_803009F8 + 0x4D) = 1;
}

// .text:0x800BEBCC size:0x34
void fn_800BEBCC(void) {
    return;
}

// .text:0x800BEC30 size:0x3D8
void fn_800BEC30(void) {
    return;
}

// .text:0x800BF008 size:0x30
void fn_800BF008(void) {
    return;
}

extern u8 lbl_803009F8[];

// fn_800BF038, size:0x10
void fn_800BF038(u32 value) {
    *(u32*)(lbl_803009F8 + 0x20) = value;
}

// fn_800BF048, size:0x10
void fn_800BF048(u32 value) {
    *(u32*)(lbl_803009F8 + 0x18) = value;
}

// fn_800BF058, size:0x10
void fn_800BF058(u32 value) {
    *(u32*)(lbl_803009F8 + 0x1c) = value;
}

// fn_800BF068, size:0xC
void* fn_800BF068(void) {
    return lbl_803009F8;
}

// .text:0x800BF074 size:0x130
void SKNLoadFile(void) {
    return;
}

// .text:0x800BF1A4 size:0x1C
void SKNFlushByIndex1(void) {
    return;
}

// .text:0x800BF1C0 size:0x28
void SKNFlushByIndex2(void) {
    return;
}

// .text:0x800BF1E8 size:0x1C
void SKNBzero32B(void) {
    return;
}

// .text:0x800BF204 size:0xA4
void SKNInit(void) {
    return;
}

// .text:0x800BF2A8 size:0x5F4
void fn_800BF2A8(void) {
    return;
}

// .text:0x800BF89C size:0x5F4
void SKNIt(void) {
    return;
}

// .text:0x800BFE90 size:0x10C
void SKN1Vecs16Norms16(void) {
    return;
}

// .text:0x800BFF9C size:0x10C
void fn_800BFF9C(void) {
    return;
}

// .text:0x800C00A8 size:0x220
void SKN2Vecs16Norms16NoTouch(void) {
    return;
}

// .text:0x800C02C8 size:0x220
void fn_800C02C8(void) {
    return;
}

// .text:0x800C04E8 size:0x148
void SKNAccVecs16Norms16Iu161(void) {
    return;
}

// .text:0x800C0630 size:0x140
void SKNAccVecs16Norms16Iu162(void) {
    return;
}

// .text:0x800C0770 size:0x4C
void convertTextureHeader(void) {
    return;
}

// .text:0x800C07BC size:0x2D0
void fn_800C07BC(void) {
    return;
}
