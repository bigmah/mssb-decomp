#include "Unknown/auto_03_800BF038_text.h"

extern u8 lbl_803009F8[];

// fn_800BF038, size:0x10
void fn_800BF038(u32 value) {
    *(u32*)(lbl_803009F8 + 0x20) = value;
}

// fn_800BF048, size:0x10
void fn_800BF048(u32 value) {
    *(u32*)(lbl_803009F8 + 0x18) = value;
}

// fn_800BF058, size:0x10
void fn_800BF058(u32 value) {
    *(u32*)(lbl_803009F8 + 0x1c) = value;
}

// fn_800BF068, size:0xC
void* fn_800BF068(void) {
    return lbl_803009F8;
}
