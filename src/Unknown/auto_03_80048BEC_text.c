#include "Unknown/auto_03_80048BEC_text.h"

extern u32 lbl_803CBCE8;

// fn_80048BEC, size:0x28
void fn_80048BEC(s32* limits) {
    s32 count = limits[1] < limits[2] ? limits[1] : limits[2];
    while (count > 0) {
        count--;
    }
}

// fn_80048C14, size:0x8
void fn_80048C14(u32 value) {
    lbl_803CBCE8 = value;
}
