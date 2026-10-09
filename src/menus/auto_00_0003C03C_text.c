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

// fn_2_46C24, size:0x8
s32 fn_2_46C24(void) {
    return 0;
}

// fn_2_46C2C, size:0x5C
void fn_2_46C2C(s32 unused, Vec* src) {
    Vec position;
    position.x = src->x;
    position.y = src->y;
    position.z = src->z;
    *lbl_2_data_13374[0] = lbl_803CBD0C[0];
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// fn_2_422FC, size:0x8C
void fn_2_422FC(s32 index) {
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197694) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x19768C) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12C0C[index], 0x4000);
    *(u8**)(lbl_2_bss_1A824C[0] + 0x197684) = lbl_2_bss_15B8;
}

// fn_2_42270, size:0x8C
void fn_2_42270(s32 index) {
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197694) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x19768C) = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x197690) = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12CE8[index], 0x4000);
    *(u8**)(lbl_2_bss_1A824C[0] + 0x197684) = lbl_2_bss_15B8;
}

// fn_2_44238, size:0xB0
s32 fn_2_44238(s32 value) {
    s32 count = 0;
    s32 i;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        if (*(s16*)(menu + 0x40B8 + i * 6) == value) count++;
    }
    return count != 0;
}

// fn_2_44184, size:0xB4
void fn_2_44184(void) {
    s32 count = 0;
    s32 i;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        if (*(s16*)(menu + 0x40B8 + i * 6) == 12) count++;
    }
    if (count == 0) {
        menu[0x44F7] = 1;
    }
}

// fn_2_442E8, size:0x80
s32 fn_2_442E8(void) {
    s32 i;
    s32 count = 0;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        s32 a = *(s16*)(menu + 0x40B8 + i * 6);
        if (a == 0 || a == 1) count++;
    }
    return count == 2;
}

// fn_2_44368, size:0xAC
s32 fn_2_44368(void) {
    s32 i;
    s32 count = 0;
    u8* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        s32 a = *(s16*)(menu + 0x40B8 + i * 6);
        if (a == 13 || a == 29 || a == 30 || a == 31 || a == 32) count++;
    }
    return count >= 5;
}

// fn_2_42638, size:0xD0
void fn_2_42638(void) {
    s32 i;
    u8* d;
    u8* s;
    for (i = 0; i < 20; i++) {
        d = lbl_2_bss_1A824C[0] + 0x1978C7;
        s = lbl_2_bss_1A8248[0] + 0x43C2;
        d[i] = s[i];
    }
}

// fn_2_467FC, size:0xE0
void fn_2_467FC(void) {
    u8* entry;
    s32 i;
    for (i = 0; i < 54; i++) {
        entry = lbl_2_bss_1A8248[0] + i * 0x34;
        if (*(s8*)(entry + 4) == (s32)lbl_2_bss_1A8248[0][0x441C] && *(s8*)(entry + 5) <= 3) {
            entry[0x31] = 1;
        } else {
            entry[0x31] = 0;
        }
    }
}

// fn_2_45978, size:0x10C
void fn_2_45978(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        u8* entry = lbl_2_bss_1A8248[0] + i * 0x34;
        entry[7] = entry[6];
        for (j = 0; j < 10; j++) {
            entry[0x1D + j * 2] = entry[9 + j * 2];
            entry[0x1E + j * 2] = entry[10 + j * 2];
        }
        lbl_2_bss_1A8248[0][i + 0x444D] = 0;
        lbl_2_bss_1A8248[0][i + 0x4483] = 0;
        lbl_2_bss_1A8248[0][i + 0x44B9] = 0;
    }
}
