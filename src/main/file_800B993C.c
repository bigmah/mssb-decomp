#include "main/file_800B993C.h"

extern f32 lbl_803CC1FC;

extern f32 lbl_803CC1F8;


// fn_800B993C, size:0xC
void fn_800B993C(void) {
    lbl_803CC200 = NULL;
}

// fn_800B9948, size:0x8
void fn_800B9948(DOTevHook hook) {
    lbl_803CC200 = hook;
}

// fn_800B996C, size:0x8
void fn_800B996C(DOTevPass pass) {
    lbl_803CC1F4 = pass;
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
