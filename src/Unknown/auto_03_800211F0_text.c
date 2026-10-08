#include "Unknown/auto_03_800211F0_text.h"

extern u8 lbl_800EFBC0[];

// fn_800211F0, size:0x14
u8 fn_800211F0(void) {
    return *(u32*)(lbl_800EFBC0 + 0x18) & 0xFF;
}
