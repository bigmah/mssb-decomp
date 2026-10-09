#include "menus/auto_00_0003C03C_text.h"
#include "string.h"
#include "Dolphin/vec.h"

extern u8* lbl_2_bss_1A8248[];
extern u8* lbl_2_bss_1A824C[];
extern u8 lbl_803CB8F0[];
extern u32 lbl_803CBD0C[];
extern u32* lbl_2_data_13374[];
extern void fn_80031CA4(Vec*, u32*);
extern u8 lbl_2_bss_15B8[];
extern void* lbl_2_data_12C0C[];
extern void* lbl_2_data_12CE8[];

// fn_2_42474, size:0x1C
void fn_2_42474(void) {
    u8* menu = lbl_2_bss_1A824C[0];
    *(s16*)(menu + 0x1976E4) = 0x78;
}

// fn_2_44F14, size:0x20
s32 fn_2_44F14(s32 index) {
    u8* menu = lbl_2_bss_1A8248[0];
    u8* entry = menu + index * 0x34;
    return *(s8*)(entry + 5);
}

// fn_2_44F34, size:0x30
s32 fn_2_44F34(s32 index) {
    return *(s8*)(lbl_2_bss_1A8248[0] + index * 0x34 + 5) <= 3;
}

// fn_2_4668C, size:0x20
void fn_2_4668C(s32 index) {
    u8* menu = lbl_2_bss_1A8248[0];
    u8* entry = menu + index * 0x34;
    entry[0x31] = 1;
}

// fn_2_45938, size:0x40
s32 fn_2_45938(s32 index) {
    u8* menu = lbl_2_bss_1A8248[0];
    return *(s8*)(menu + lbl_803CB8F0[menu[index * 10 + 0x40F3]] * 0x34 + 0x31) == 0;
}

// fn_2_460EC, size:0x4
void fn_2_460EC(void) {
    return;
}

// fn_2_460F0, size:0x4
void fn_2_460F0(void) {
    return;
}

// fn_2_460F4, size:0x4
void fn_2_460F4(void) {
    return;
}
