#include "Unknown/auto_03_800BEB3C_text.h"

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
