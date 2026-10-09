#include "menus/auto_00_00001254_text.h"
#include "static/UnknownHomes_Static.h"

extern void fn_800625A4(u8, s32);

extern u8 lbl_803297E0[];
extern void fn_2_2FC0(u8, s32, s32);

extern void fn_2_7DDC(void);
extern void fn_2_7504(void);

extern u8 lbl_8034E9A0[];

extern u32 lbl_803CB750[];

extern u8 lbl_2_bss_F468[];

typedef struct MenuEntrySlot {
    u8* object;
    u32 pad;
} MenuEntrySlot;

extern MenuEntrySlot lbl_80371C30[];

extern u8 lbl_2_bss_100B4;
extern u8* lbl_803CBBCC[];

// fn_2_1D54, size:0x70
void fn_2_1D54(s32* selection, u8 controller, s32 count) {
    u8* controls = lbl_8034E9A0;
    u16 buttons;
    controls += controller * 6;
    buttons = *(u16*)(controls + 0x4730);
    if (buttons & 8) {
        (*selection)--;
        if (*selection < 0) {
            *selection = count - 1;
        }
    } else if (buttons & 4) {
        (*selection)++;
        if (*selection == count) {
            *selection = 0;
        }
    }
}

// fn_2_6138, size:0x68
void fn_2_6138(void) {
    fn_800625A4(0, 19);
    fn_800625A4(1, 19);
    lbl_2_bss_F468[0x4F] = 0;
    lbl_2_bss_F468[0x2E] = 0;
    lbl_2_bss_100B4 = 1;
    *(s16*)(lbl_803CBBCC[0] + 4) = 8;
}

// fn_2_35D0, size:0x54
s32 fn_2_35D0(u8 index) {
    u8* flag = (u8*)((u32)lbl_2_bss_F468 + 0x45 + index);
    if (*flag != 0) {
        *flag = 0;
        sndFXRelated(0x200);
        return 1;
    }
    return 0;
}

// fn_2_112F4, size:0x4C
s32 fn_2_112F4(void* menu, s32 item, s32 index, const u16* values, s16 value) {
    u8* object = lbl_80371C30[*(u16*)((u8*)menu + 0x14) + item].object;
    if ((s32)(*(u32*)(object + 0x5C) >> 16) == values[index + 1] - 1) {
        *(s16*)(object + 0x64) = value;
        return 1;
    }
    return 0;
}

// fn_2_1258, size:0x48
u32 fn_2_1258(const void* base, u32 offset, s32 size) {
    u32 value = 0;
    switch (size) {
    case 1:
        value = *(const u8*)(offset + (u32)base);
        break;
    case 2:
        value = *(const u16*)((const u8*)base + offset);
        break;
    case 3:
        break;
    case 4:
        value = *(const u32*)((const u8*)base + offset);
        break;
    }
    return value;
}

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

// fn_2_145C, size:0x30
s32 fn_2_145C(u16* a, u16* b) {
    for (;;) {
        u16 x = *a++;
        u16 y = *b++;
        if (x != y) {
            return 0;
        }
        if (x == 0x4000) {
            return 1;
        }
    }
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

// fn_2_CCBC, size:0x24
void fn_2_CCBC(void) {
    fn_2_7DDC();
    fn_2_7504();
}

// fn_2_3204, size:0x38
void fn_2_3204(void) {
    fn_2_2FC0(lbl_803297E0[0xCF5F], 1, 1);
}

// fn_2_6098, size:0x3C
void fn_2_6098(s32 index) {
    ((u32*)lbl_2_bss_F468)[(u8)index] = 9;
    fn_800625A4((u8)index, 0x17);
}
