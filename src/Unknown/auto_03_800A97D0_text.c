#include "Unknown/auto_03_800A97D0_text.h"

extern u8 lbl_80110080[];

// fn_800A97D0, size:0x1C
void fn_800A97D0(u8 value, s32 index) {
    lbl_80110080[7] = value;
    lbl_80110080[8] = -index;
    lbl_80110080[9] = index;
}
