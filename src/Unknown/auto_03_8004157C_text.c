#include "Unknown/auto_03_8004157C_text.h"

extern u16 lbl_803CBCC0;

// fn_8004157C, size:0x24
s32 fn_8004157C(void) {
    if (lbl_803CBCC0 != 0) {
        lbl_803CBCC0--;
        return 1;
    }
    return 0;
}

// fn_800415A0, size:0x8
void fn_800415A0(u16 value) {
    lbl_803CBCC0 = value;
}
