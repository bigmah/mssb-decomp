#include "Unknown/auto_03_8004CC18_text.h"

extern u8 lbl_803C5F74[];

// fn_8004CC18, size:0x14
void fn_8004CC18(void) {
    *(u8*)(lbl_803C5F74 + 0x3) = 0x4;
}

// fn_8004CC2C, size:0x20
void fn_8004CC2C(void) {
    if (lbl_803C5F74[3] != 4) {
        lbl_803C5F74[3] = 3;
    }
}
