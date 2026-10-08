#include "Unknown/auto_03_8000900C_text.h"

extern u32 lbl_803CBBBC;

extern u32 lbl_803CBBAC;

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
