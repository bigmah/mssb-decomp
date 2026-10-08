#include "Unknown/auto_03_800B993C_text.h"

extern f32 lbl_803CC1FC;

extern f32 lbl_803CC1F8;

extern u32 lbl_803CC1F4;

extern u32 lbl_803CC200;

// fn_800B993C, size:0xC
void fn_800B993C(void) {
    lbl_803CC200 = 0x0;
}

// fn_800B9948, size:0x8
void fn_800B9948(u32 value) {
    lbl_803CC200 = value;
}

// fn_800B996C, size:0x8
void fn_800B996C(u32 value) {
    lbl_803CC1F4 = value;
}

// fn_800B9950, size:0x1C
void fn_800B9950(u32 mask, f32 first, f32 second) {
    if (mask & 1) {
        lbl_803CC1F8 = first;
    }
    if (mask & 2) {
        lbl_803CC1FC = second;
    }
}
