#include "menus/auto_00_00016870_text.h"

extern u8 lbl_2_bss_100B8[];
extern u8 lbl_8036E548[];


// fn_2_16A34, size:0x14
u8 fn_2_16A34(s32 index) {
    u8* entry = lbl_2_bss_100B8 + index;
    return entry[0x46];
}

// fn_2_16A48, size:0x14
void fn_2_16A48(s32 index, u8 value) {
    u8* entry = lbl_2_bss_100B8 + index;
    entry[0x46] = value;
}

// fn_2_16A5C, size:0x18
u8 fn_2_16A5C(s32 index) {
    u8* entry = lbl_8036E548;
    entry += index * 0x27C;
    return entry[0xE61];
}
