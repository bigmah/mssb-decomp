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
extern void fn_2_8EA80(void);
extern void fn_2_8E478(void);
extern void fn_2_47CFC(void);
extern void fn_2_8AEE0(void);
extern void fn_2_8ACB0(s32, s32);
extern void fn_2_68FBC(s32, s32);
extern void fn_2_8CCAC(s32, u8);
extern u8 lbl_80366B18[];
extern void fn_2_68DAC(s32 index, void* result);
extern void fn_80068720(s32);
extern void fn_8001F228(void);
extern void fn_80021410(void);

// fn_2_1B314, size:0x218
void fn_2_1B314(void) {
    u8* o = lbl_803CC1B8;
    u8* q;
    s32 i;
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197746) = 7;
        q = fn_800B0A5C_insertQueue(fn_2_8EA80, 2);
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
        q = fn_800B0A5C_insertQueue(fn_2_8E478, 2);
        q[0x28] = 0;
        *(s16*)(o + 0x10) = 0;
        o[0x28] = 3;
        break;
    case 3:
        if (*(s16*)(o + 0x10) == 1) {
            o[0x28] = 0xC;
        }
        break;
    case 4:
        for (i = 0; i < *(s16*)(lbl_2_bss_1A824C[0] + 0x197746); i++) {
            fn_2_8CCAC(i, 1);
            fn_2_68FBC(i, 1);
        }
        o[0x28] = 5;
        break;
    case 5:
        fn_2_47CFC();
        o[0x28] = 6;
        break;
    case 6:
        for (i = 0; i < *(s16*)(lbl_2_bss_1A824C[0] + 0x197746); i++) {
            fn_2_8CCAC(i, 0);
        }
        fn_2_47CFC();
        o[0x28] = 7;
        break;
    case 7:
        fn_2_47CFC();
        o[0x28] = 8;
        break;
    case 8:
        o[0x28] = 9;
        break;
    case 9:
        fn_2_8AEE0();
        o[0x28] = 10;
        break;
    case 10:
        for (i = 0; i < 0x1D; i++) {
            fn_2_8ACB0(i, 0);
        }
        fn_2_8AEE0();
        o[0x28] = 11;
        break;
    case 11:
        fn_2_8AEE0();
        o[0x28] = 12;
        break;
    case 12:
        q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
}

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

// fn_2_1BFD0, size:0x104
void fn_2_1BFD0(void) {
    fn_80068720(0xA);
    lbl_2_bss_1A824C[0][0x1972BC] = 1;
    lbl_2_bss_1A824C[0][0x1972C0] = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x1976D6) = 0;
    lbl_2_bss_1A8248[0x44F2] = 0;
    if (lbl_2_bss_1A824C[0][0x197864] == 0) {
        fn_2_4E7EC();
    }
    fn_8001F228();
    fn_80021410();
    fn_800ACFB0(*(void**)(lbl_800EF808 + 0x9C));
    if ((s8)lbl_2_bss_1A8248[0x44F4] != 0) {
        fn_2_4E8BC();
        fn_2_4E904();
        fn_2_4E928();
    } else {
        fn_2_4E928();
    }
    fn_2_4E94C();
    if (*(u32*)(lbl_80366B18 + 0x7A8) != 0) {
        fn_800ACFB0(*(void**)(lbl_80366B18 + 0x7A8));
        *(u32*)(lbl_80366B18 + 0x7A8) = 0;
    }
    lbl_2_bss_1A823C[0][0x34] = 0;
}

// fn_2_1C21C, size:0x28
void fn_2_1C21C(void) {
    u8 buf[0x18];
    fn_2_68DAC(0, buf);
}

// fn_2_1C3A4, size:0x4
void fn_2_1C3A4(void) {
    return;
}

// fn_2_1C3A8, size:0x74
void fn_2_1C3A8(void) {
    if ((s32)lbl_2_bss_1A824C[0][0x1978FB] == 1) {
        lbl_2_bss_1A8234[0][0x16268A] = 1;
        lbl_2_bss_1A8234[0][0x162874] = 0;
        return;
    }
    lbl_2_bss_1A8234[0][0x162874] = 1;
    lbl_2_bss_1A8234[0][0x16268A] = 0;
}

// fn_2_1C41C, size:0x74
void fn_2_1C41C(void) {
    lbl_2_bss_1A8234[0][0x162657] = 1;
    lbl_2_bss_1A8234[0][0x162676] = 1;
    lbl_2_bss_1A8234[0][0x162677] = 1;
    lbl_2_bss_1A8234[0][0x162678] = 1;
    lbl_2_bss_1A8234[0][0x162841] = 0;
    lbl_2_bss_1A8234[0][0x162860] = 0;
    lbl_2_bss_1A8234[0][0x162861] = 0;
    lbl_2_bss_1A8234[0][0x162862] = 0;
}

// fn_2_1C490, size:0x74
void fn_2_1C490(void) {
    lbl_2_bss_1A8234[0][0x162841] = 1;
    lbl_2_bss_1A8234[0][0x162860] = 1;
    lbl_2_bss_1A8234[0][0x162861] = 1;
    lbl_2_bss_1A8234[0][0x162862] = 1;
    lbl_2_bss_1A8234[0][0x162657] = 0;
    lbl_2_bss_1A8234[0][0x162676] = 0;
    lbl_2_bss_1A8234[0][0x162677] = 0;
    lbl_2_bss_1A8234[0][0x162678] = 0;
}

// fn_2_1C504, size:0xC4
void fn_2_1C504(s32 arg) {
    s32 i;
    for (i = 0; i < 0x33; i++) {
        if (arg == lbl_2_bss_1A8248[i * 10 + 0x40F0] && (lbl_2_bss_1A8248[i * 10 + 0x40F1] == 1 || lbl_2_bss_1A8248[i * 10 + 0x40F1] == 0)) {
            if (lbl_2_bss_1A8248[0x441C] == 5) {
                if (lbl_2_bss_1A8248[i * 10 + 0x40F2] == 1) {
                    lbl_2_bss_1A8248[i * 10 + 0x40F1] = 3;
                } else {
                    lbl_2_bss_1A8248[i * 10 + 0x40F1] = 0;
                }
            } else {
                lbl_2_bss_1A8248[i * 10 + 0x40F1] = 0;
            }
        }
    }
    lbl_2_bss_1A8248[arg + 0x440C] = 1;
    if (!(lbl_2_bss_1A8248[0x4428] & (1 << arg))) {
        lbl_2_bss_1A8248[0x4423]++;
        lbl_2_bss_1A8248[0x4428] |= 1 << arg;
    }
}

typedef struct {
    u32 w0;
    u8 pad[0x14];
} Cell18;

// fn_2_1C244, size:0xF8
void fn_2_1C244(void) {
    s32 row;
    s32 col;
    for (row = 0; row < 70; row++) {
        for (col = 0; col < 864; col++) {
            Cell18* c = &((Cell18(*)[864])lbl_2_bss_1A8234[0])[row][col];
            if (row >= 35 && col >= 100 && c->w0 != 0) {
                return;
            }
        }
    }
}

// fn_2_1C714, size:0x14C
void fn_2_1C714(s32 arg) {
    s32 i;
    s32 t;
    for (i = 0; i < 0x33; i++) {
        if (arg == lbl_2_bss_1A8248[i * 10 + 0x40F0] && (lbl_2_bss_1A8248[i * 10 + 0x40F1] == 1 || lbl_2_bss_1A8248[i * 10 + 0x40F1] == 0)) {
            if (lbl_2_bss_1A8248[i * 10 + 0x40F2] == 0 && lbl_2_bss_1A8248[0x441C] != arg) {
                if (lbl_2_bss_1A8248[0x441C] == 5) {
                    lbl_2_bss_1A8248[i * 10 + 0x40F1] = 3;
                } else {
                    lbl_2_bss_1A8248[i * 10 + 0x40F1] = 0;
                }
            } else {
                lbl_2_bss_1A8248[i * 10 + 0x40F1] = 0;
            }
            if (lbl_2_bss_1A8248[i * 10 + 0x40F2] == 2) {
                lbl_2_bss_1A8248[i * 10 + 0x40F1] = 0;
            }
        }
        if (lbl_2_bss_1A8248[i * 10 + 0x40F0] == 6 || lbl_2_bss_1A8248[i * 10 + 0x40F0] == 7 || lbl_2_bss_1A8248[i * 10 + 0x40F0] == 8) {
            lbl_2_bss_1A8248[i * 10 + 0x40F1] = 0;
            lbl_2_bss_1A8248[0x4412] = 1;
            lbl_2_bss_1A8248[0x4413] = 1;
            lbl_2_bss_1A8248[0x4414] = 1;
        }
    }
    lbl_2_bss_1A8248[arg + 0x440C] = 1;
    if (lbl_2_bss_1A8248[0x441C] != arg) {
        t = 1 << arg;
        if (!(lbl_2_bss_1A8248[0x4426] & t)) {
            lbl_2_bss_1A8248[0x4422] = lbl_2_bss_1A8248[0x4422] + 1;
            lbl_2_bss_1A8248[0x4426] = lbl_2_bss_1A8248[0x4426] | t;
        }
    }
}
