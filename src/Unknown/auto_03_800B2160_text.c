#include "Unknown/auto_03_800B2160_text.h"

extern u8* lbl_803CBB34;

// fn_800B2160, size:0xC
void fn_800B2160(u8 value) {
    lbl_803CBB34[0x8A] = value;
}

// fn_800B216C, size:0x3C
s32 fn_800B216C(u8 flag, u32 mode, u8 index) {
    u32 value = ((u32)index << 4) | (flag | (mode << 1)) | 0x40000000;
    if (*(u32*)(lbl_803CBB34 + 0x78) == value) {
        return 0;
    }
    *(u32*)(lbl_803CBB34 + 0x78) = value;
    return 1;
}
