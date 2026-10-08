#include "Unknown/auto_03_8003AE54_text.h"

extern u32 lbl_803CBCB8;

extern u8 lbl_803CBCB4;

extern u8 lbl_802D4B00[];

// fn_8003AE70, size:0x5C
u8 fn_8003AE70(s32 selector) {
    u8 value = 0;
    switch (selector) {
    case 0:
        value = lbl_802D4B00[0x95];
        break;
    case 1:
        value = lbl_802D4B00[0x94];
        break;
    case 2:
        value = lbl_802D4B00[0x96];
        break;
    }
    return value;
}

// fn_8003AE54, size:0x8
u8 fn_8003AE54(void) {
    return lbl_803CBCB4;
}

// fn_8003AE5C, size:0x8
void fn_8003AE5C(u8 value) {
    lbl_803CBCB4 = value;
}

// fn_8003AE64, size:0xC
void fn_8003AE64(void) {
    lbl_803CBCB8 = 0x0;
}
