#include "Unknown/auto_03_80052734_text.h"

extern u32 lbl_803CB880;

extern u8 lbl_803C639C[];

// fn_80052734, size:0x34
void* fn_80052734(s32 index) {
    u8* camera;
    if (index < 0) {
        index = 0;
    } else if (index >= 2) {
        index = 1;
    }
    camera = lbl_803C639C + index * 0xA8;
    return camera + 0x150;
}

// fn_800527BC, size:0x8
u32 fn_800527BC(void) {
    return lbl_803CB880;
}
