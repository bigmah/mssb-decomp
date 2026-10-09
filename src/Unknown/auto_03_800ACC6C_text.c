#include "Unknown/auto_03_800ACC6C_text.h"

extern u8 lbl_803C7838[];

// fn_800ACCD4, size:0x14
void fn_800ACCD4(void) {
    *(u8*)(lbl_803C7838 + 0x55) = 0x7;
}

// fn_800ACC6C, size:0x68
s32 fn_800ACC6C(s32 mode, s32 a, s32 b) {
    s32 base = mode;
    s32 total;
    s32 q;
    switch (mode) {
    case 0:
        base = 0;
        break;
    case 1:
        base = 0x1800;
        break;
    case 2:
        base = 0xE00;
        break;
    }
    total = base + a + b;
    q = total / 0x2000;
    if (total % 0x2000 != 0) {
        q++;
    }
    return q;
}
