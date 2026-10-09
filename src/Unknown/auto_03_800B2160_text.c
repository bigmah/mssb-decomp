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

// fn_800B21A8, size:0x98
void fn_800B21A8(s32 mode) {
    if (mode == 2) {
        s32 changed;
        u32 old = *(u32*)(lbl_803CBB34 + 0x78);
        if (old == 0x40000013) {
            changed = 0;
        } else {
            *(u32*)(lbl_803CBB34 + 0x78) = 0x40000013;
            changed = 1;
        }
        if (changed != 0) {
            *(u32*)(lbl_803CBB34 + 0x7C) = old;
        }
    } else if (mode != 0) {
        if (*(u32*)(lbl_803CBB34 + 0x78) != 0x40000017) {
            *(u32*)(lbl_803CBB34 + 0x78) = 0x40000017;
        }
    } else {
        if (*(u32*)(lbl_803CBB34 + 0x78) != 0x4000001F) {
            *(u32*)(lbl_803CBB34 + 0x78) = 0x4000001F;
        }
    }
}
