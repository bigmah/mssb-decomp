#include "Unknown/auto_03_800B0D28_text.h"

extern void* lbl_803CC1D8[2];

extern s32 lbl_803CBB30;
extern u8 lbl_80111340[];

// fn_800B0D38, size:0x30
void fn_800B0D38(s32 index, s32 value) {
    if (index >= 0 && index < lbl_803CBB30) {
        u8* entry = lbl_80111340 + index * 0xC;
        *(s32*)(entry + 0x120) = value;
        ((s32*)lbl_80111340)[index * 3] = value;
    }
}

// fn_800B0D28, size:0x10
void fn_800B0D28(void* value) {
    lbl_803CC1D8[0] = value;
    lbl_803CC1D8[1] = value;
}
