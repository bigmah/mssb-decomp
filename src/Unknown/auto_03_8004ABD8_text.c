#include "Unknown/auto_03_8004ABD8_text.h"

extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD00;

extern s32 lbl_803CB848;

// Set_803cb848, size:0x8
void Set_803cb848(s32 value) {
    lbl_803CB848 = value;
}

// fn_8004ABE0, size:0x8
s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

// fn_8004ABE8, size:0x18
s32 fn_8004ABE8(s32 clear) {
    s32 value = lbl_803CBD00;
    if (clear != 0) {
        lbl_803CBD00 = 0;
    }
    return value;
}
