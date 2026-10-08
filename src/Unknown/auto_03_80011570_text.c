#include "Unknown/auto_03_80011570_text.h"

extern u32 lbl_803CBC18;

extern u8 lbl_8036E548[];

// fn_800115C8, size:0x3C
void fn_800115C8(s8 index) {
    if (index >= 0 && index < 13) {
        u8* base = lbl_8036E548;
        u8* object;
        base += index * 4;
        object = *(u8**)(base + 0x2C50);
        if (object != NULL) {
            *(u32*)(object + 0x5C) = 0;
        }
    }
}

// fn_80011570, size:0x8
u32 fn_80011570(void) {
    return lbl_803CBC18;
}

// fn_80011604, size:0x3C
void fn_80011604(s8 index, u32 value) {
    u8* base;
    u8* object;
    if (index < 0 || index >= 13) {
        return;
    }
    base = lbl_8036E548;
    base += index * 4;
    object = *(u8**)(base + 0x2C50);
    if (object != NULL) {
        *(u32*)(object + 0x5C) = value;
    }
}
