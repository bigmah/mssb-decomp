#include "Unknown/auto_03_800BD2B0_text.h"

extern u32 lbl_803CC224;

extern u8 lbl_803CC220;

// fn_800BD2B0, size:0x1C
u8 fn_800BD2B0(u32* value) {
    if (lbl_803CC220 != 0) {
        *value = lbl_803CC224;
    }
    return lbl_803CC220;
}

// fn_800BD2CC, size:0x10
void fn_800BD2CC(u8 flag, u32* value) {
    u32 input = *value;
    lbl_803CC220 = flag;
    lbl_803CC224 = input;
}
