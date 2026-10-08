#include "menus/rep_0B08.h"

extern const f32 lbl_2_rodata_B6C[];

#include <string.h>

#include "static/UnknownHomes_Static.h"
extern const f32 lbl_2_rodata_BA0;

extern u8 lbl_800F7478[];

extern void fn_2_69E1C(s32 index);


extern f64 __fabs(f64 value);
extern const f32 lbl_2_rodata_BA8;

typedef struct {
    u8 _00[0xC0];
    s8 flagC0;
    u8 _C1[3];
    u8 flagC4;
    u8 _C5[5];
    s8 flagCA;
    s8 flagCB;
    s8 flagCC;
    s8 flagCD;
    s8 flagCE;
    s8 flagCF;
    u8 flagD0;
    u8 _D1[7];
} MenuEntry;

typedef struct {
    u8 _00[0x1610];
    MenuEntry entries[4];
} MenuEntries;

extern MenuEntries* lbl_2_bss_1A8248[];

extern void (*lbl_2_data_2A2E0[])(u8* object);
extern void (*lbl_2_data_2A2D4[])(u8* object);
extern void (*lbl_2_data_2A2C4[])(u8* object);
extern void (*lbl_2_data_2A2B8[])(u8* object);
extern void (*lbl_2_data_2A2AC[])(u8* object);
extern void (*lbl_2_data_2A29C[])(u8* object);
extern void (*lbl_2_data_2A28C[])(u8* object);
extern void (*lbl_2_data_2A280[])(u8* object);
extern void (*lbl_2_data_2A274[])(u8* object);
extern void (*lbl_2_data_2A268[])(u8* object);
extern void (*lbl_2_data_2A25C[])(u8* object);
extern void (*lbl_2_data_2A250[])(u8* object);
extern void (*lbl_2_data_2A248[])(u8* object);
extern void (*lbl_2_data_2A234[])(u8* object);
extern void (*lbl_2_data_2A220[])(u8* object);
extern void (*lbl_2_data_2A210[])(u8* object);
extern void (*lbl_2_data_2A208[])(u8* object);
extern void (*lbl_2_data_2A200[])(u8* object);
extern void (*lbl_2_data_2A1F4[])(u8* object);

// .text:0x71A38 size:0x38
void fn_2_71A38(u8* object) {
    lbl_2_data_2A1F4[*(s16*)(object + 0x94)](object);
}

// .text:0x70588 size:0x38
void fn_2_70588(u8* object) {
    lbl_2_data_2A200[*(s16*)(object + 0x94)](object);
}

// .text:0x704A0 size:0xC
void fn_2_704A0(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x70494 size:0xC
void fn_2_70494(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x7045C size:0x38
void fn_2_7045C(u8* object) {
    lbl_2_data_2A208[*(s16*)(object + 0x94)](object);
}

// .text:0x6FE34 size:0x38
void fn_2_6FE34(u8* object) {
    lbl_2_data_2A210[*(s16*)(object + 0x94)](object);
}

// .text:0x6F6F4 size:0x38
void fn_2_6F6F4(u8* object) {
    lbl_2_data_2A220[*(s16*)(object + 0x94)](object);
}

// .text:0x6E880 size:0xC
void fn_2_6E880(u8* object) {
    *(s16*)(object + 0x94) = 4;
}

// .text:0x6E848 size:0x38
void fn_2_6E848(u8* object) {
    lbl_2_data_2A234[*(s16*)(object + 0x94)](object);
}

// .text:0x6D840 size:0x38
void fn_2_6D840(u8* object) {
    lbl_2_data_2A248[*(s16*)(object + 0x94)](object);
}

// .text:0x6D748 size:0xC
void fn_2_6D748(u8* object) {
    *(s16*)(object + 0x94) = 1;
}

// .text:0x6D710 size:0x38
void fn_2_6D710(u8* object) {
    lbl_2_data_2A250[*(s16*)(object + 0x94)](object);
}

// .text:0x6D4E8 size:0x10
void fn_2_6D4E8(u8* object) {
    *(s16*)(object + 0xA2) -= 1;
}

// .text:0x6D4B0 size:0x38
void fn_2_6D4B0(u8* object) {
    lbl_2_data_2A25C[*(s16*)(object + 0x94)](object);
}

// .text:0x6D288 size:0x10
void fn_2_6D288(u8* object) {
    *(s16*)(object + 0xA2) -= 1;
}

// .text:0x6D250 size:0x38
void fn_2_6D250(u8* object) {
    lbl_2_data_2A268[*(s16*)(object + 0x94)](object);
}

// .text:0x6D078 size:0x10
void fn_2_6D078(u8* object) {
    *(s16*)(object + 0xA2) -= 1;
}

// .text:0x6D040 size:0x38
void fn_2_6D040(u8* object) {
    lbl_2_data_2A274[*(s16*)(object + 0x94)](object);
}

// .text:0x6CB78 size:0x38
void fn_2_6CB78(u8* object) {
    lbl_2_data_2A280[*(s16*)(object + 0x94)](object);
}

// .text:0x6C97C size:0xC
void fn_2_6C97C(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x6C970 size:0xC
void fn_2_6C970(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x6C938 size:0x38
void fn_2_6C938(u8* object) {
    lbl_2_data_2A28C[*(s16*)(object + 0x94)](object);
}

// .text:0x6C28C size:0x38
void fn_2_6C28C(u8* object) {
    lbl_2_data_2A29C[*(s16*)(object + 0x94)](object);
}

// .text:0x6BF88 size:0x38
void fn_2_6BF88(u8* object) {
    lbl_2_data_2A2AC[*(s16*)(object + 0x94)](object);
}

// .text:0x6BDD4 size:0xC
void fn_2_6BDD4(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x6BD9C size:0x38
void fn_2_6BD9C(u8* object) {
    lbl_2_data_2A2B8[*(s16*)(object + 0x94)](object);
}

// .text:0x6BC00 size:0xC
void fn_2_6BC00(u8* object) {
    *(s16*)(object + 0x94) = 2;
}

// .text:0x6BBC8 size:0x38
void fn_2_6BBC8(u8* object) {
    lbl_2_data_2A2C4[*(s16*)(object + 0x94)](object);
}

// .text:0x6BA18 size:0x38
void fn_2_6BA18(u8* object) {
    lbl_2_data_2A2D4[*(s16*)(object + 0x94)](object);
}

// .text:0x6B4C4 size:0x38
void fn_2_6B4C4(u8* object) {
    lbl_2_data_2A2E0[*(s16*)(object + 0x94)](object);
}

// .text:0x6ACF0 size:0x4
void fn_2_6ACF0(void) {
}

// .text:0x6AAB8 size:0x4
void fn_2_6AAB8(void) {
}

// fn_2_6C2C4, size:0x24
void fn_2_6C2C4(void) {
    u8* menu;
    ((u8*)lbl_2_bss_1A8248[0])[0x442F] = 0;
    menu = (u8*)lbl_2_bss_1A8248[0];
    menu[0x17AB] = 0;
    *(s16*)(menu + 0x177C) = 0;
}

// fn_2_68638, size:0x1C
void fn_2_68638(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DE] = value;
}

// fn_2_68654, size:0x1C
void fn_2_68654(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DD] = value;
}

// fn_2_686D0, size:0x1C
void fn_2_686D0(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DF] = value;
}

// fn_2_68D90, size:0x1C
void fn_2_68D90(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DA] = value;
}

// fn_2_68F08, size:0x1C
void fn_2_68F08(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16D0] = value;
}

// fn_2_6AF80, size:0x1C
void fn_2_6AF80(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16D4] = value;
}

// fn_2_68670, size:0x20
s32 fn_2_68670(s32 index) {
    return ((s8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DD];
}

// fn_2_68690, size:0x20
s32 fn_2_68690(s32 index) {
    return ((s8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DC];
}

// fn_2_686B0, size:0x20
s32 fn_2_686B0(s32 index) {
    return ((s8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DB];
}

// fn_2_6BAAC, size:0x2C
void fn_2_6BAAC(u8* object) {
    ((u8*)lbl_2_bss_1A8248[0])[*(s32*)(object + 0x80) * 0xD8 + 0x16DA] = 0xFF;
    *(s16*)(object + 0x94) = 3;
}

// fn_2_6F72C, size:0x60
void fn_2_6F72C(u8* object) {
    f32 distance = (f32)__fabs(PSVECDistance((Vec*)((u8*)lbl_2_bss_1A8248[0] + 0x1610), (Vec*)object));
    if (distance > lbl_2_rodata_BA8) {
        *(s16*)(object + 0x94) = 1;
    }
}

// fn_2_6BFC0, size:0x60
void fn_2_6BFC0(u8* object) {
    f32 distance = (f32)__fabs(PSVECDistance((Vec*)((u8*)lbl_2_bss_1A8248[0] + 0x1610), (Vec*)object));
    if (distance > lbl_2_rodata_BA8) {
        *(s16*)(object + 0x94) = 1;
    }
}

// fn_2_6C2E8, size:0x60
void fn_2_6C2E8(u8* object) {
    fn_2_69E1C(*(s32*)(object + 0x80));
    if (*(f32*)(object + 0x50) <= 0.0f) {
        object[0xBA] = 4;
        object[0xC4] = 1;
        *(s16*)(object + 0x94) = 3;
    }
}

// fn_2_6BA50, size:0x5C
void fn_2_6BA50(u8* object) {
    GXColor color = *(GXColor*)(lbl_800F7478 + 0x28);
    color.a = 0xFF;
    fn_800BD2CC(0, color);
    *(s16*)(object + 0x94) = 2;
}

// fn_2_6BB7C, size:0x4C
void fn_2_6BB7C(u8* object) {
    ((u8*)lbl_2_bss_1A8248[0])[*(s32*)(object + 0x80) * 0xD8 + 0x16D0] = 1;
    ((u8*)lbl_2_bss_1A8248[0])[*(s32*)(object + 0x80) * 0xD8 + 0x16DA] = 0xFF;
    *(f32*)(object + 0x8C) = lbl_2_rodata_BA0;
    *(s16*)(object + 0x94) = 1;
}

// fn_2_6C120, size:0x70
void fn_2_6C120(u8* object) {
    f32 distance = (f32)__fabs(PSVECDistance((Vec*)((u8*)lbl_2_bss_1A8248[0] + 0x1610), (Vec*)object));
    if (distance < lbl_2_rodata_BA8 && distance != 0.0f) {
        *(s16*)(object + 0x94) = 2;
    }
}

// fn_2_6AF9C, size:0x38
s32 fn_2_6AF9C(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    if (entry->flagD0 == 0) {
        entry->flagD0 = 0;
        return 1;
    }
    return 0;
}

// fn_2_6AFD4, size:0x50
s32 fn_2_6AFD4(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    u8 flag = entry->flagC4;
    if (flag == 1) {
        entry->flagC4 = 0;
        return 1;
    }
    if (flag == 2) {
        entry->flagC4 = 0;
        return 2;
    }
    return 0;
}

// fn_2_68DAC, size:0x3C
void fn_2_68DAC(s32 index, void* result) {
    memcpy(result, &lbl_2_bss_1A8248[0]->entries[index], 0xC);
}

// fn_2_696D4, size:0x3C
void fn_2_696D4(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    if (*(s16*)((u8*)entry + 0xA0) != 0) {
        *(f32*)((u8*)entry + 0x38) = *(f32*)((u8*)entry + 0x3C);
        return;
    }
    *(f32*)((u8*)entry + 0x38) = 0.0f;
}

// fn_2_68DE8, size:0x80
void fn_2_68DE8(s32 index, Vec* result) {
    if (index != -1) {
        memcpy(result, &lbl_2_bss_1A8248[0]->entries[index], 0xC);
        PSVECScale(result, lbl_2_rodata_B6C[0], result);
        return;
    }
    result->z = 0.0f;
    result->y = 0.0f;
    result->x = 0.0f;
}
