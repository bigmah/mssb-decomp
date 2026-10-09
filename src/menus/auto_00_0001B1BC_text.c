#include "menus/auto_00_0001B1BC_text.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "static/UnknownHomes_Static.h"

extern u8* lbl_2_bss_1A8234[];
extern u8* lbl_2_bss_1A824C[];
extern u8* lbl_2_bss_1A8248;
extern u8* lbl_2_bss_1A823C[];
extern u8* lbl_803CC1B8;
extern void fn_2_409CC(void);
extern s32 fn_2_4EB2C(void);
extern s32 fn_2_4EAF4(void);
extern s32 fn_2_4E9A8(void);
extern u8 lbl_800EF808[];
extern u8 lbl_80366B18[];
extern void fn_2_68DAC(s32 index, void* result);
extern void fn_80068720(s32);
extern void fn_8001F228(void);
extern void fn_80021410(void);

// fn_2_1B52C, size:0x94
void fn_2_1B52C(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        if (fn_2_4E970() == 1) {
            o[0x28] = 1;
        }
        break;
    case 1:
        o[0x28] = 6;
        break;
    case 6:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

// fn_2_1B5C0, size:0x10C
void fn_2_1B5C0(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        q = fn_800B0A5C_insertQueue(fn_2_409CC, 2);
        q[0x28] = 0;
        *(s16*)(o + 0x10) = 0;
        o[0x28] = 1;
        break;
    case 1:
        if (*(s16*)(o + 0x10) == 1) {
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == 1) {
            o[0x28] = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == 1) {
            o[0x28] = 4;
        }
        break;
    case 4:
        if (fn_2_4EAF4() == 1) {
            o[0x28] = 5;
        }
        break;
    case 5:
        if (fn_2_4E9A8() == 1) {
            o[0x28] = 6;
        }
        break;
    case 6:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

// fn_2_1B6CC, size:0xE8
void fn_2_1B6CC(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        q = fn_800B0A5C_insertQueue(fn_2_409CC, 2);
        q[0x28] = 0;
        *(s16*)(o + 0x10) = 0;
        o[0x28] = 1;
        break;
    case 1:
        if (*(s16*)(o + 0x10) == 1) {
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_2_4EB64() == 1) {
            o[0x28] = 3;
        }
        break;
    case 3:
        if (fn_2_4EB2C() == 1) {
            o[0x28] = 4;
        }
        break;
    case 4:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

// fn_2_1BF50, size:0x80
void fn_2_1BF50(void) {
    fn_80068720(0xD);
    lbl_2_bss_1A824C[0][0x1972BC] = 1;
    lbl_2_bss_1A824C[0][0x1972C0] = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x1976D6) = 0;
    lbl_2_bss_1A8248[0x44F2] = 0;
    fn_2_4E898();
    lbl_2_bss_1A823C[0][0x34] = 0;
}

