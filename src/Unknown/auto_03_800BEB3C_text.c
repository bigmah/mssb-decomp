#include "Unknown/auto_03_800BEB3C_text.h"

extern u8 lbl_803009F8[];

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
