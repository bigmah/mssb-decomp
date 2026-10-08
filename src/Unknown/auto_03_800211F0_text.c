#include "Unknown/auto_03_800211F0_text.h"

extern u8 lbl_800EFBC0[];

extern u8 lbl_800EF808[];
extern u8 lbl_800E8754[];

// fn_80021204, size:0x24
void fn_80021204(void) {
    u8 first = lbl_800EF808[0x398];
    u8 second = lbl_800EF808[0x396];
    lbl_800E8754[0x23] = first;
    lbl_800E8754[0x24] = second;
}

// fn_800211F0, size:0x14
u8 fn_800211F0(void) {
    return *(u32*)(lbl_800EFBC0 + 0x18) & 0xFF;
}
