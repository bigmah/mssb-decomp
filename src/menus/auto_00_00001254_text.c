#include "menus/auto_00_00001254_text.h"

extern u8 lbl_8034E9A0[];

extern u32 lbl_803CB750[];

extern u8 lbl_2_bss_F468[];

// fn_2_8780, size:0x14
s32 fn_2_8780(s32 mode) {
    if (mode != 0) {
        return 0x13;
    }
    return 9;
}

// fn_2_8794, size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}

// fn_2_57E8, size:0x8
s8 fn_2_57E8(s32 unused, s32 value) {
    return value;
}

// fn_2_EC34, size:0x20
void fn_2_EC34(void) {
    if (lbl_2_bss_F468[0x56] == 0) lbl_2_bss_F468[0x56] = 1;
}

// fn_2_1554, size:0x24
u32 fn_2_1554(void) {
    lbl_803CB750[0] = lbl_803CB750[0] * 0x5D588B65 + 1;
    return lbl_803CB750[0];
}

// fn_2_1328, size:0x2C
void fn_2_1328(u32* value, u16 increment) {
    u32 sum = *value + increment;
    if (sum > 0x7FFFFFFF) {
        *value = 0x7FFFFFFF;
        return;
    }
    *value = sum;
}

// fn_2_12A0, size:0x2C
void fn_2_12A0(s16* value, s32 increment) {
    s16 current = *value;
    if (current < 0x7FFF - (s16)increment) {
        *value = current + increment;
        return;
    }
    *value = 0x7FFF;
}

// fn_2_12CC, size:0x2C
void fn_2_12CC(u8* value, s32 increment) {
    u8 current = *value;
    if (current + (u16)increment > 0xFF) {
        *value = 0xFF;
        return;
    }
    *value = current + increment;
}

// fn_2_12F8, size:0x30
void fn_2_12F8(u16* value, s32 increment) {
    u16 current = *value;
    if (current + (u16)increment > 0xFFFF) {
        *value = 0xFFFF;
        return;
    }
    *value = current + increment;
}

// fn_2_1D28, size:0x2C
void fn_2_1D28(void) {
    lbl_8034E9A0[0x472A] = 0xFF;
    lbl_8034E9A0[0x4756] = 0;
    lbl_8034E9A0[0x4754] = 0;
    lbl_8034E9A0[0x4755] = 3;
    lbl_8034E9A0[0x48B3] = 0;
}

// fn_2_1254, size:0x4
void fn_2_1254(void) {
    return;
}

// fn_2_1DC4, size:0x4
void fn_2_1DC4(void) {
    return;
}

// fn_2_893C, size:0x4
void fn_2_893C(void) {
    return;
}
