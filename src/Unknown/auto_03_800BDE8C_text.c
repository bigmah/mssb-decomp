#include "Unknown/auto_03_800BDE8C_text.h"

extern u8 lbl_803009F8[];

// fn_800BDE8C, size:0x14
void fn_800BDE8C(u32 value) {
    lbl_803009F8[0x4C] = (value & 7) << 5;
}
