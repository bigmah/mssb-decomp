#include "Unknown/auto_03_800A97D0_text.h"

extern u8 lbl_80110080[];

extern u8 lbl_803C77B8[];

// fn_800A97EC, size:0x50
void fn_800A97EC(s32 index, u32 enable, u8 type) {
    u8* entry = lbl_803C77B8 + index * 0x20;
    if (!(lbl_80110080[6] & (1 << index))) {
        entry[0xA] = enable;
        entry[0xB] = 0;
        if (enable != 0) {
            entry[0xB] = type;
        }
        entry[9] = 1;
    }
}

// fn_800A97D0, size:0x1C
void fn_800A97D0(u8 value, s32 index) {
    lbl_80110080[7] = value;
    lbl_80110080[8] = -index;
    lbl_80110080[9] = index;
}
