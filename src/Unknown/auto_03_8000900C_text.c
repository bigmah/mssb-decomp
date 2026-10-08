#include "Unknown/auto_03_8000900C_text.h"

extern u32 lbl_803CBBBC;

extern u32 lbl_803CBBAC;

extern u8 lbl_803C6CF8[];
extern s32 lbl_803CBBA0;
extern u8 lbl_803CBBA4;

// fn_80009028, size:0x6C
u8 fn_80009028(void) {
    switch (*(s8*)(lbl_803C6CF8 + 0x722)) {
    case 0:
        lbl_803CBBA4 = 0;
        break;
    case -1:
    case 4:
    case 5:
    case 6:
    case 11:
        lbl_803CBBA0 = *(s8*)(lbl_803C6CF8 + 0x722);
        lbl_803CBBA4 = 1;
        break;
    }
    return lbl_803CBBA4;
}

// fn_8000900C, size:0xC
void fn_8000900C(void) {
    lbl_803CBBAC = 0x1;
}

// fn_80009018, size:0x10
u32 fn_80009018(u32 value) {
    u32 previous = lbl_803CBBBC;
    lbl_803CBBBC = value;
    return previous;
}
