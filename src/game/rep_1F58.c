#include "game/rep_1F58.h"
#include "header_rep_data.h"

extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_3_bss_9D20[];
extern u8 lbl_3_bss_9D40[];
extern void GXInitTexObj(void* obj, void* img, u16 w, u16 h, int fmt, int ws, int wt, int mip);
extern void GXInitTexObjLOD(void* obj, int minF, int maxF, f32 minLOD, f32 maxLOD, f32 bias, int biasClamp, int edgeLOD, int maxAniso);

// .text:0x000C0854 size:0x108 mapped:0x806FF8E8
void fn_3_C0854(void) {
    return;
}

// .text:0x000C095C size:0x17C mapped:0x806FF9F0
void fn_3_C095C(void) {
    return;
}

// .text:0x000C0AD8 size:0x174 mapped:0x806FFB6C
void fn_3_C0AD8(void) {
    return;
}

// .text:0x000C0C4C size:0x9C mapped:0x806FFCE0
void fn_3_C0C4C(void) {
    return;
}

// .text:0x000C0CE8 size:0x28 mapped:0x806FFD7C
void fn_3_C0CE8(u8 v, f32 x, f32 y, f32 z) {
    *(f32*)(lbl_3_common_bss_35154 + 0x434) = x;
    *(f32*)(lbl_3_common_bss_35154 + 0x438) = y;
    *(f32*)(lbl_3_common_bss_35154 + 0x43C) = z;
    lbl_3_common_bss_35154[0x467] = v;
    *(u32*)(lbl_3_common_bss_35154 + 0x3AC) |= 0x100;
}

// .text:0x000C0D10 size:0xC8 mapped:0x806FFDA4
void fn_3_C0D10(void) {
    return;
}

// .text:0x000C0DD8 size:0x1B4 mapped:0x806FFE6C
void fn_3_C0DD8(void) {
    return;
}

// .text:0x000C0F8C size:0x78 mapped:0x80700020
void fn_3_C0F8C(void) {
    GXInitTexObj(lbl_3_bss_9D20, lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
    GXInitTexObjLOD(lbl_3_bss_9D20, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
}

// .text:0x000C1004 size:0x1C8 mapped:0x80700098
void fn_3_C1004(void) {
    return;
}

// .text:0x000C11CC size:0x178 mapped:0x80700260
void fn_3_C11CC(void) {
    return;
}

// .text:0x000C1344 size:0x42C mapped:0x807003D8
void fn_3_C1344(void) {
    return;
}

// .text:0x000C1770 size:0x1C0 mapped:0x80700804
void fn_3_C1770(void) {
    return;
}
