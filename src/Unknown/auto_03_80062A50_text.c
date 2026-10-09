#include "Unknown/auto_03_80062A50_text.h"

extern u8 lbl_8034E9A0[];

extern u8 lbl_803C6714[];

// initializeUnknown, size:0x24
void initializeUnknown(void) {
    lbl_8034E9A0[0x48B3] = 0;
    *(u32*)lbl_803C6714 = 0;
    lbl_803C6714[5] = 0;
    lbl_803C6714[4] = 0;
}

// fn_80062A74, size:0x20
void fn_80062A74(void) {
    lbl_803C6714[5] = 1;
    lbl_8034E9A0[0x48B3] = 1;
}
