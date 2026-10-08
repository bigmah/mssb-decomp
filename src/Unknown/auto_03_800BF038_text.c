#include "Unknown/auto_03_800BF038_text.h"

extern u8 lbl_803009F8[];

// fn_800BF038, size:0x10
void fn_800BF038(u32 value) {
    *(u32*)(lbl_803009F8 + 0x20) = value;
}
