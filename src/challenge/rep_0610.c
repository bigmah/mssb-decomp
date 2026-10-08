#include "challenge/rep_0610.h"

extern u8 lbl_1_bss_5F74;
extern u8 lbl_1_bss_5F78[];

extern void* lbl_1_bss_67B8[];

extern u8 lbl_1_bss_67E0[];

extern u8 lbl_1_bss_5F71;

extern void* lbl_80366158[];
extern u8* lbl_803CC1B8[];

extern s32 lbl_1_data_F4DC[3];
extern u8 lbl_1_bss_3216[];
extern void fn_1_1496C(u8* object);
#include "static/UnknownHomes_Static.h"
extern void fn_1_10560(void* object);
extern void* lbl_1_bss_3098[];
extern u8 lbl_1_bss_3215[];
extern u8 lbl_1_bss_3214[];
extern u8 lbl_1_bss_30B8;

// .text:0x163FC size:0x4
void fn_1_163FC(void) {
}

void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

void fn_1_D650(void) {
    lbl_1_bss_3214[0] = 1;
}

void fn_1_D67C(u8 value) {
    lbl_1_bss_3215[0] = value;
}

void fn_1_106B4(void) {
    lbl_1_bss_3098[0] = 0;
}

void* fn_1_106A4(void) {
    return lbl_1_bss_3098[0];
}

void fn_1_10670(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_10560, 11);
    *(s16*)(object + 0x10) = 0;
}

void fn_1_176EC(u8* object) {
    fn_1_1496C(object);
}

u8 fn_1_D638(void) {
    u8 flag = lbl_1_bss_3214[0];
    lbl_1_bss_3214[0] = 0;
    return flag;
}

s32 fn_1_D660(void) {
    return lbl_1_bss_3215[0] != 0;
}

void fn_1_D688(void) {
    lbl_1_bss_3216[0]++;
    if (lbl_1_bss_3216[0] == 3) lbl_1_bss_3216[0] = 0;
}

void fn_1_D6B4(void) {
    if (lbl_1_bss_3216[0] == 0) lbl_1_bss_3216[0] = 3;
    lbl_1_bss_3216[0]--;
}

s32 fn_1_D6E4(void) {
    u8 index = lbl_1_bss_3216[0];
    switch (index) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[index];
    default:
        return 0;
    }
}

// fn_1_160D8, size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) return 0xFF0F;
    return 0xFFFF;
}

// fn_1_116EC, size:0x28
void fn_1_116EC(void* object) {
    SetDisplayStateTexture(object, 0, 0);
}

// fn_1_14928, size:0x44
void fn_1_14928(void) {
    fn_800AD038(lbl_80366158[2]);
    *(s16*)(*(u8**)(lbl_803CC1B8[0] + 0xC) + 0x10) = 1;
}

// fn_1_148CC, size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(lbl_80366158[2]);
    *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
    *(void (**)(u8*))(lbl_803CC1B8[0]) = fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// fn_1_15170, size:0x88
void fn_1_15170(void) {
    u16 buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 0x200) {
        fn_1_148CC();
    } else if (buttons & 0x100) {
        lbl_1_bss_5F71 = 1;
    }
}

// fn_1_14888, size:0x44
void fn_1_14888(u8* object) {
    if (lbl_1_bss_67E0[0x118]) {
        fn_800B9AA8(lbl_1_bss_67E0 + 0x30);
    } else {
        fn_800B9AA8(*(void**)(object + 0x70));
    }
}

// fn_1_E9F8, size:0x28
void fn_1_E9F8(u8* object, s32 index, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        index++;
        if (index == *(u16*)(object + 6)) index = 0;
    }
}

// fn_1_10AA4, size:0x28
void fn_1_10AA4(u8* object, f32 value) {
    *(f32*)(object + 0x54) = value;
    object[0x5A] = 1;
    if (lbl_1_bss_67B8[0] != 0) {
        *(f32*)((u8*)lbl_1_bss_67B8[0] + 4) = value;
    }
}

// fn_1_161D0, size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F74 ^= 1;
    fn_800B9A9C(lbl_1_bss_5F74, *(f32*)lbl_1_bss_5F78);
}
