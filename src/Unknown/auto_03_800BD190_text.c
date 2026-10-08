#include "Unknown/auto_03_800BD190_text.h"

extern u32 lbl_803CC20C;

// fn_800BD190, size:0x58
void fn_800BD190(GQRValueGroups* groups, s32 value) {
    u32 i;
    s32 j;
    for (i = 0; i < groups->count; i++) {
        for (j = 0; j < groups->groups[i].group->count; j++) {
            groups->groups[i].group->entries[j].value = value;
        }
    }
}

// __MTGQR5, size:0x8
void __MTGQR5(register u32 value) {
    asm {
        mtspr GQR5, value
    }
}

// fn_800BD1E8, size:0x8
void fn_800BD1E8(u32 value) {
    lbl_803CC20C = value;
}

// __MTGQR6, size:0x8
void __MTGQR6(register u32 value) {
    asm {
        mtspr GQR6, value
    }
}

// __MTGQR7, size:0x8
void __MTGQR7(register u32 value) {
    asm {
        mtspr GQR7, value
    }
}
