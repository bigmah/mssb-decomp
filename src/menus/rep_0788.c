#include "menus/rep_0788.h"

#include "static/UnknownHomes_Static.h"
#include "static/UnknownHomes_Static.h"
extern void fn_2_243BC(void);
extern u8 lbl_2_data_F0EC[];
extern void fn_2_54354(void* data, s32 id);

extern void fn_2_24488(void);
extern u8 lbl_2_data_9FC8[];
extern void fn_2_54354(void* data, s32 id);

typedef struct { u8* object; s32 _04; } MenuTableEntry;
extern MenuTableEntry lbl_80371C30[];
extern u8* lbl_2_bss_1A824C[];
extern s16 lbl_2_data_3D30[][4];
extern u8* lbl_803CC1B8[];

// .text:0x24724 size:0x4
void fn_2_24724(void) {
}

// .text:0x20258 size:0x4
void fn_2_20258(void) {
}

// .text:0x1FF10 size:0x4
void fn_2_1FF10(void) {
}

// .text:0x1FF0C size:0x4
void fn_2_1FF0C(void) {
}

void fn_2_24EB0(s16 value) {
    *(s16*)(lbl_803CC1B8[0] + 0x10) = value;
}

s16 fn_2_24E9C(void) {
    return *(s16*)(lbl_803CC1B8[0] + 0x10);
}

s16 fn_2_201E4(s16 row, s16 column) {
    if (column < 0) return -1;
    return lbl_2_data_3D30[row][column];
}

void fn_2_20218(void) {
    lbl_2_bss_1A824C[0][0x19782B] = 0;
    lbl_2_bss_1A824C[0][0x19782C] = 0;
    lbl_2_bss_1A824C[0][0x19782A] = 0;
    lbl_2_bss_1A824C[0][0x197832] = 0;
}

void fn_2_272BC(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

void fn_2_25D6C(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

void fn_2_25A1C(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

void fn_2_25850(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

// fn_2_246E0, size:0x44
void fn_2_246E0(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_24488, 2);
    *(s16*)(object + 0x1C) = 0;
    fn_2_54354(lbl_2_data_9FC8, 0x293);
}

// fn_2_2469C, size:0x44
void fn_2_2469C(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_243BC, 2);
    *(s16*)(object + 0x1C) = 0;
    fn_2_54354(lbl_2_data_F0EC, 0x13A);
}
