#include "Unknown/auto_03_8004ACC4_text.h"

extern u32 lbl_803CBD08;

extern u32 lbl_803CBD04;

// fn_8004ACC4, size:0x18
u32 fn_8004ACC4(s32 clear) {
    u32 value = lbl_803CBD04;
    if (clear != 0) {
        lbl_803CBD04 = 0;
    }
    return value;
}

// fn_8004ACDC, size:0x18
u32 fn_8004ACDC(s32 clear) {
    u32 value = lbl_803CBD08;
    if (clear != 0) {
        lbl_803CBD08 = 0;
    }
    return value;
}
