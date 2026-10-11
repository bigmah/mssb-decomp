#include "game/auto_00_0015C5F4_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0015C5F4 size:0x44 mapped:0x8079B688
void fn_3_15C5F4(void) {
    SceneTask* task = lbl_803CC1B8;

    if (g_GameLogic._125 == 7) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}

// .text:0x0015C638 size:0xAC mapped:0x8079B6CC
void fn_3_15C638(void) {
    ScoreBookTask* task = SB_TASK;

    fn_80034E20(task, lbl_3_data_27C54);
    if (lbl_80353A90._104 == 2) {
        SB_OBJ(task, 0)->_64 = 0xD3;
    } else if (lbl_80353A90._104 == 3) {
        SB_OBJ(task, 0)->_64 = 0xC0;
    }
    SB_TASK->func = fn_3_15C5F4;
}

// .text:0x0015C6E4 size:0xAF4 mapped:0x8079B778
// Shows a number in the digit sprites of object idx, in one of several layouts.
void fn_3_15C6E4(ScoreBookTask* task, s32 idx, s32 value, s32 format) {
    fn_800362F0(task, idx);
    if (format == 0x15) {
        SB_OBJ(task, idx)->_64 = 0x10;
        fn_800363D8(task, idx, 1, 0x1A, 0xE);
        fn_800363D8(task, idx, 2, 0x1A, 0xE);
    } else if (format == 0x16) {
        SB_OBJ(task, idx)->_64 = 0x15;
        fn_800363D8(task, idx, 3, 0x1A, 0xE);
        fn_800363D8(task, idx, 2, 0x1A, 0xE);
        fn_800363D8(task, idx, 1, 0x1A, 0xE);
        fn_800363D8(task, idx, 6, 0x1A, 0xE);
        fn_800363D8(task, idx, 5, 0x1A, 0xE);
        fn_800363D8(task, idx, 4, 0x1A, 0xE);
    } else if (format == 10) {
        if (value >= 1000) {
            SB_OBJ(task, idx)->_64 = 0x18;
            fn_800363D8(task, idx, 1, 0x1A, 1);
            fn_800363D8(task, idx, 3, 0x1A, 0);
            fn_800363D8(task, idx, 4, 0x1A, 0);
            fn_800363D8(task, idx, 5, 0x1A, 0);
            fn_800363D8(task, idx, 6, 0x1A, 1);
            fn_800363D8(task, idx, 8, 0x1A, 0);
            fn_800363D8(task, idx, 9, 0x1A, 0);
            fn_800363D8(task, idx, 10, 0x1A, 0);
        } else {
            s32 a, b, c;

            SB_OBJ(task, idx)->_64 = 0x19;
            a = value / 100;
            fn_800363D8(task, idx, 2, 0x1A, a);
            b = (value / 10) % 10;
            fn_800363D8(task, idx, 3, 0x1A, b);
            c = value % 10;
            fn_800363D8(task, idx, 4, 0x1A, c);
            fn_800363D8(task, idx, 6, 0x1A, a);
            fn_800363D8(task, idx, 7, 0x1A, b);
            fn_800363D8(task, idx, 8, 0x1A, c);
        }
    } else if (format == 11) {
        if (value >= 1000) {
            s32 a, b, c, d;

            if (value >= 10000) {
                value = 9999;
            }
            SB_OBJ(task, idx)->_64 = 0x17;
            a = value / 1000;
            fn_800363D8(task, idx, 1, 0x1A, a);
            b = (value / 100) % 10;
            fn_800363D8(task, idx, 2, 0x1A, b);
            c = (value / 10) % 10;
            fn_800363D8(task, idx, 4, 0x1A, c);
            d = value % 10;
            fn_800363D8(task, idx, 5, 0x1A, d);
            fn_800363D8(task, idx, 6, 0x1A, a);
            fn_800363D8(task, idx, 7, 0x1A, b);
            fn_800363D8(task, idx, 9, 0x1A, c);
            fn_800363D8(task, idx, 10, 0x1A, d);
        } else {
            s32 a, b, c;

            SB_OBJ(task, idx)->_64 = 0x16;
            a = (value / 100) % 10;
            fn_800363D8(task, idx, 1, 0x1A, a);
            b = (value / 10) % 10;
            fn_800363D8(task, idx, 3, 0x1A, b);
            c = value % 10;
            fn_800363D8(task, idx, 4, 0x1A, c);
            fn_800363D8(task, idx, 5, 0x1A, a);
            fn_800363D8(task, idx, 7, 0x1A, b);
            fn_800363D8(task, idx, 8, 0x1A, c);
        }
    } else {
        if (format == 12) {
            s32 r;
            s32 q;

            // thirds (innings pitched): whole part, then a 1/3 or 2/3 glyph
            r = value % 3;
            q = value / 3;
            if (value == 0) {
                SB_OBJ(task, idx)->_64 = 0x11;
                fn_800363D8(task, idx, 1, 0x1A, 0xB);
                fn_800363D8(task, idx, 2, 0x1A, 0xB);
                return;
            }
            if (r != 0) {
                if (q >= 10) {
                    s32 a, b;

                    SB_OBJ(task, idx)->_64 = 0x14;
                    a = q / 10;
                    fn_800363D8(task, idx, 1, 0x1A, a);
                    b = q % 10;
                    fn_800363D8(task, idx, 2, 0x1A, b);
                    fn_800363D8(task, idx, 3, 0x1A, r + 0xB);
                    fn_800363D8(task, idx, 4, 0x1A, a);
                    fn_800363D8(task, idx, 5, 0x1A, b);
                    fn_800363D8(task, idx, 6, 0x1A, r + 0xB);
                } else if (q != 0) {
                    SB_OBJ(task, idx)->_64 = 0x12;
                    fn_800363D8(task, idx, 1, 0x1A, q);
                    fn_800363D8(task, idx, 2, 0x1A, r + 0xB);
                    fn_800363D8(task, idx, 3, 0x1A, q);
                    fn_800363D8(task, idx, 4, 0x1A, r + 0xB);
                } else {
                    SB_OBJ(task, idx)->_64 = 0x11;
                    fn_800363D8(task, idx, 1, 0x1A, r + 0xB);
                    fn_800363D8(task, idx, 2, 0x1A, r + 0xB);
                }
                return;
            }
            value = q;
        }
        if (value < 10) {
            SB_OBJ(task, idx)->_64 = 0x10;
            fn_800363D8(task, idx, 1, 0x1A, value);
            fn_800363D8(task, idx, 2, 0x1A, value);
        } else if (format == 2 || value < 100) {
            s32 a, b;

            if (value >= 100) {
                value = 99;
            }
            SB_OBJ(task, idx)->_64 = 0x13;
            a = value % 10;
            fn_800363D8(task, idx, 2, 0x1A, a);
            b = value / 10;
            fn_800363D8(task, idx, 1, 0x1A, b);
            fn_800363D8(task, idx, 4, 0x1A, a);
            fn_800363D8(task, idx, 3, 0x1A, b);
        } else {
            s32 a, b, c;

            if (value >= 1000) {
                value = 999;
            }
            SB_OBJ(task, idx)->_64 = 0x15;
            a = value % 10;
            fn_800363D8(task, idx, 3, 0x1A, a);
            b = (value / 10) % 10;
            fn_800363D8(task, idx, 2, 0x1A, b);
            c = value / 100;
            fn_800363D8(task, idx, 1, 0x1A, c);
            fn_800363D8(task, idx, 6, 0x1A, a);
            fn_800363D8(task, idx, 5, 0x1A, b);
            fn_800363D8(task, idx, 4, 0x1A, c);
        }
    }
}

// .text:0x0015D1D8 size:0x96C mapped:0x8079C26C
void fn_3_15D1D8(void) {
    return;
}

// .text:0x0015DB44 size:0x12E8 mapped:0x8079CBD8
void fn_3_15DB44(void) {
    return;
}

// .text:0x0015EE2C size:0x25C mapped:0x8079DEC0
void fn_3_15EE2C(void) {
    return;
}

// .text:0x0015F088 size:0x198 mapped:0x8079E11C
void fn_3_15F088(void) {
    return;
}

// .text:0x0015F220 size:0x160 mapped:0x8079E2B4
void fn_3_15F220(void) {
    return;
}

// .text:0x0015F380 size:0x44 mapped:0x8079E414
void fn_3_15F380(void) {
    return;
}

// .text:0x0015F3C4 size:0x4C mapped:0x8079E458
void fn_3_15F3C4(void) {
    return;
}

// .text:0x0015F410 size:0x164 mapped:0x8079E4A4
void fn_3_15F410(void) {
    return;
}
