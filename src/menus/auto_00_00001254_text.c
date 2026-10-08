#include "menus/auto_00_00001254_text.h"

extern u32 lbl_803CB750[];

extern u8 lbl_2_bss_F468[];

// fn_2_8780, size:0x14
s32 fn_2_8780(s32 mode) {
    if (mode != 0) {
        return 0x13;
    }
    return 9;
}

// fn_2_8794, size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}

// fn_2_57E8, size:0x8
s8 fn_2_57E8(s32 unused, s32 value) {
    return value;
}

// fn_2_EC34, size:0x20
void fn_2_EC34(void) {
    if (lbl_2_bss_F468[0x56] == 0) lbl_2_bss_F468[0x56] = 1;
}

// fn_2_1554, size:0x24
u32 fn_2_1554(void) {
    lbl_803CB750[0] = lbl_803CB750[0] * 0x5D588B65 + 1;
    return lbl_803CB750[0];
}
