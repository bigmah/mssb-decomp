#include "menus/rep_0438.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_800639BC.h"
#include "main/file_800A7C08.h"
#include "main/file_800527C4.h"
#include "main/file_8004C5F8.h"
#include "main/menu_globals.h"
#include "static/GameSettings.h"
#include "main/file_8001FE00.h"
#include "main/file_80011640.h" // lbl_8036E548
#include "main/file_80034F50.h"
#include "main/file_800B0724.h"
#include "menus/rep_04B0.h"
#include "menus/rep_0568.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/auto_00_00016870_text.h"
#include "menus/auto_00_00000D08_text.h"
#include "menus/auto_00_00001254_text.h"
#include "menus/auto_00_000194BC_text.h"
#include "Dolphin/os.h"
#include <string.h>
#include "menus/auto_00_00013BA4_text.h"

// Globals as seen by this unit (other units still use raw or differently named views).
extern DebugMenuState lbl_2_bss_100B8;

// Menus REL bss block at 0xF410 (size 0x58, only the fields used here).
typedef struct MenusBssF410 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s32 _10[2]; // per team
    /*0x18*/ u8 _18[0x54 - 0x18];
    /*0x54*/ u32 _54;
} MenusBssF410; // size: 0x58

extern MenusBssF410 lbl_2_bss_F410;
// Menus REL bss flags at 0x100B4.
typedef struct MenusBss100B4 {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1; // nonzero: team select input blocked
} MenusBss100B4;

extern MenusBss100B4 lbl_2_bss_100B4;
extern u16 lbl_2_bss_AE0; // frame counter, wraps at 60000
extern UnlockFlags lbl_80361B20;
extern u8 lbl_800FE930[2][6]; // captain character id per [lbl_80361B20._F4][F410._10]
extern u8 lbl_80108EC4[12];   // captain character ids, in preset order
extern u8 lbl_800FE5D4[];     // captain character ids (first 12 entries)
extern u8 lbl_803CBBC4[];

// main.dol globals only used here so far.
typedef struct Unk803CBCD8 {
    /*0x0*/ u8 _0[5];
    /*0x5*/ u8 _5;
    /*0x6*/ u8 _6[2];
} Unk803CBCD8; // size: 0x8

extern Unk803CBCD8 lbl_803CBCD8;

typedef struct Unk803CBD24 {
    /*0x0*/ u8 _0[4];
    /*0x4*/ u8 team; // team whose controller drives fn_8004CA6C
    /*0x5*/ u8 _5[7];
} Unk803CBD24; // size: 0xC

extern Unk803CBD24 lbl_803CBD24;

typedef struct Unk800E877C {
    /*0x00*/ u8 _00[0x30];
    /*0x30*/ s16 _30;
    /*0x32*/ s16 _32;
    /*0x34*/ u8 _34[4];
} Unk800E877C; // size: 0x38

extern Unk800E877C lbl_800E877C;

typedef struct Unk800EF808 {
    /*0x000*/ u8 _000[0x98];
    /*0x098*/ void* _098; // block freed with fn_800ACFB0
    /*0x09C*/ u8 _09C[0x39C - 0x9C];
} Unk800EF808; // size: 0x39C

extern Unk800EF808 lbl_800EF808;


// main.dol functions whose headers clash with static/UnknownHomes_Static.h.
s32 fn_80021410(void);                 // main/file_80021308.h
void fn_80021AC0(s32 team, s32 arg1);  // main/file_80021308.h
void fn_80021AC4(void);                // main/file_80021308.h
void fn_80035CA4(s32 id);              // main/file_80034F50.h

// .text:0x00012238 size:0x194
// NONMATCHING 91.5%: preset-copy loop scheduling (loads of presets hoisted differently)
#if NONMATCHING
void fn_2_12238(void) {
    s32 i;
    s32 preset;
    s32 captain = lbl_800FE930[lbl_80361B20._F4][lbl_2_bss_F410._10[0]];

    for (i = 0; i < 6; i++) {
        if (lbl_80108EC4[i] == captain) {
            preset = i;
            break;
        }
    }
    if (i == 6) {
        OSPanic("teamselect.c", 0x459, " Captain Not Found ");
    }
    for (i = 0; i < 9; i++) {
        lbl_803C6724.picks[0][i] = lbl_8034E9A0.presets[preset][i];
        gChallengeState.teams[i].pos[1] = i;
        lbl_803C6724.pos[0][i] = i;
    }
    fn_800678CC(0);
}
#endif

// NONMATCHING 99.9%: register allocation of the constant 1 / port byte before fn_8004E5B4
#if NONMATCHING
// Mark the controller ports in use by the two teams and hand them to fn_8004EEF4.
static inline void fn_2_123CC_setPorts(void) {
    s8 ports[4];

    memset(ports, 2, 4);
    if (g_d_GameSettings._10 == 0) {
        ports[((s8*)lbl_8034E9A0.ports)[0]] = 1;
        if (!((s8*)lbl_8034E9A0.ports)[0]) {
            ports[1] = 2;
        } else {
            ports[0] = 2;
        }
    } else {
        ports[((s8*)lbl_8034E9A0.ports)[1]] = 1;
        ports[((s8*)lbl_8034E9A0.ports)[0]] = 1;
    }
    fn_8004EEF4(ports[0], ports[1], ports[2], ports[3], 1);
}

// .text:0x000123CC size:0x5BC
void fn_2_123CC(void) {
    s32 i;
    s32 j;
    s32 prev;
    u8 mode;
    u16 scene;

    memset(lbl_8034E9A0.charFlag, 0, sizeof(lbl_8034E9A0.charFlag));
    lbl_8034E9A0.teamRating[1] = 0;
    lbl_8034E9A0.teamRating[0] = 0;
    mode = g_d_GameSettings.GameModeSelected;
    if (mode == 5) {
        lbl_803C5EA4._36 = 1;
        lbl_803C5EA4.prevMode = lbl_803C5EA4.mode;
        lbl_803C5EA4.mode = 5;
    }
    scene = lbl_803CBBCC->prevScene;
    if (scene == 5 || (scene == 12 && mode == 5)) {
        fn_2_129D0();
        lbl_8034E9A0._472A = 0xFF;
        lbl_8034E9A0.captain[1] = -1;
        lbl_8034E9A0.captain[0] = -1;
        fn_2_1641C();
        switch (lbl_2_bss_100B8._20) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            lbl_8034E9A0._4729 = 0;
            g_d_GameSettings._10 = 0;
            lbl_803C5EA4._05 = 0;
            break;
        }
        memset(&lbl_2_bss_100B8, 0, sizeof(lbl_2_bss_100B8));
        lbl_803C6724._00[1] = 0;
        lbl_803C6724._00[0] = 0;
        if (g_d_GameSettings.GameModeSelected != 5) {
            fn_800625A4(0, 1);
            fn_800625A4(1, 1);
        } else {
            fn_2_82E58();
            fn_800B0A5C_insertQueue(fn_2_73758, 0x3000);
            fn_800625A4(0, 1);
            lbl_803CBBC4[0] = 1;
        }
        lbl_803C66B0.portOf[0] = 0;
        lbl_803C66B0.portOf[1] = 1;
        lbl_2_bss_F410._10[0] = 0;
        lbl_2_bss_F410._10[1] = 1;
        fn_2_16A48(0, 1);
        fn_2_16A48(1, 0);
        fn_2_123CC_setPorts();
    } else {
        if (mode != 5 && g_d_GameSettings._10 != 0) {
            lbl_2_bss_100B8._10[0] = 0;
            lbl_2_bss_100B8._12[0] = 0;
            lbl_2_bss_100B8._10[1] = 0;
            lbl_2_bss_100B8._12[1] = 0;
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 12; j++) {
                if (lbl_8034E9A0.captain[i] == lbl_800FE5D4[j]) {
                    lbl_2_bss_F410._10[i] = j;
                    break;
                }
            }
            if (g_d_GameSettings.GameModeSelected != 5) {
                prev = -1;
                while (fn_2_15104(lbl_2_bss_F410._10[i], prev, i, 1) == 0) {
                    prev = lbl_2_bss_F410._10[i];
                }
            }
        }
        if (g_d_GameSettings.GameModeSelected != 5) {
            fn_2_123CC_setPorts();
        }
        if (g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) {
            lbl_2_bss_100B8._10[0] = 1;
            lbl_2_bss_100B8._12[0] = 1;
            lbl_803C66B0.portOf[0] = 1;
            fn_8004E5B4(lbl_8034E9A0.ports[0], lbl_8034E9A0.captain[0], 1);
        } else if (g_d_GameSettings.GameModeSelected == 5) {
            lbl_2_bss_100B8._10[0] = 0;
            lbl_2_bss_100B8._12[0] = 0;
            lbl_803C66B0.portOf[0] = 0;
        }
        fn_800625A4(0, 8);
        fn_800625A4(1, 8);
    }
    lbl_2_bss_100B4._0 = 0;
    lbl_8034E9A0._472A = 0xFF;
}
#endif

// .text:0x00012988 size:0x24
void fn_2_12988(void) {
    lbl_8034E9A0.heapMarkB[0] = lbl_803C7898.lo;
    lbl_8034E9A0.heapMarkB[1] = lbl_803C7898.hi;
}

// .text:0x000129AC size:0x24
void fn_2_129AC(void) {
    lbl_8034E9A0.heapMarkA[0] = lbl_803C7898.lo;
    lbl_8034E9A0.heapMarkA[1] = lbl_803C7898.hi;
}

// .text:0x000129D0 size:0xA0
void fn_2_129D0(void) {
    memset(lbl_2_bss_100B8._14, 0, lbl_2_bss_100B8._2D);
    memset(lbl_2_bss_100B8._1C, 0, lbl_2_bss_100B8._2D);
    memset(lbl_2_bss_100B8._23, -1, 2);
    lbl_2_bss_100B8._18[0] = 0;
    lbl_2_bss_100B8._18[1] = 0;
    lbl_2_bss_100B8._18[2] = 0;
    lbl_2_bss_100B8._18[3] = 0;
    lbl_2_bss_100B8._20 = 0;
    lbl_2_bss_100B8._21[0] = -1;
    lbl_2_bss_100B8._21[1] = -1;
    lbl_2_bss_100B8._0C = -1;
    lbl_2_bss_100B8._2D = 0;
}

// .text:0x00012A70 size:0xF0
void fn_2_12A70(void) {
    if (lbl_2_bss_100B8._12[0] != 0) {
        lbl_2_bss_100B8._12[0] = 0;
        fn_800628D4(lbl_8034E9A0.captain[0]);
    }
    if (lbl_2_bss_100B8._12[1] != 0) {
        lbl_2_bss_100B8._12[1] = 0;
        fn_800628D4(lbl_8034E9A0.captain[1]);
    }
    if (lbl_2_bss_100B8._10[0] != 0 && lbl_2_bss_100B8._10[1] != 0) {
        if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_2_bss_100B4._0 = 1;
        }
        lbl_803CBBCC->step = 4;
        if (g_d_GameSettings._10 == 0) {
            lbl_2_bss_100B8._10[1] = 0;
            lbl_2_bss_100B8._12[1] = 0;
        }
    }
}

// .text:0x00012B60 size:0xD4
void fn_2_12B60(void) {
    s32 prev[2];
    s32 i;

    prev[0] = lbl_2_bss_F410._10[0];
    prev[1] = lbl_2_bss_F410._10[1];
    fn_2_15E80(0);
    if (g_d_GameSettings._10 == 1) {
        fn_2_15E80(1);
    }
    for (i = 0; i < 2; i++) {
        while (fn_2_15104(lbl_2_bss_F410._10[i], prev[i], i, 1) == 0 && lbl_2_bss_100B8._10[i] != 0) {
            prev[i] = lbl_2_bss_F410._10[i];
        }
    }
}

// .text:0x00012C34 size:0xA4
void fn_2_12C34(void) {
    u8 n;
    s32 i;
    s32 j;

    if (lbl_2_bss_100B8._46[4] != 0) {
        return;
    }
    if (lbl_2_bss_100B8._20 == 1 || lbl_803C5EA4._05 == 0) {
        if (lbl_2_bss_AE0 == 60000) {
            lbl_2_bss_AE0 = 0;
        }
        lbl_2_bss_AE0++;
    }
    n = 12;
    j = 4;
    if (g_d_GameSettings.GameModeSelected == 5) {
        n = 6;
    }
    for (i = 0; i < n; i++) {
        j++;
        if (j == 21) {
            j = 5;
        }
    }
}

// .text:0x00012CD8 size:0x2B0
// NONMATCHING 93.6%: inlines fn_2_12238 (equivalent); heap-mark store scheduling
#if NONMATCHING
void fn_2_12CD8(void) {
    if (lbl_803CBBCC->prevScene == 5) {
        lbl_2_bss_F410._10[0] = 0;
        lbl_2_bss_F410._10[1] = 1;
    }
    lbl_8034E9A0._48AD = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        g_d_GameSettings._10 = 0;
        lbl_2_bss_100B8._2D = 1;
    } else {
        lbl_2_bss_100B8._2D = 2;
    }
    lbl_8034E9A0._4755 = 0;
    lbl_803C66B0.steps[0][0] = 1;
    fn_2_129AC();
    fn_2_18FBC();
    if (g_d_GameSettings.GameModeSelected == 5) {
        fn_2_12238();
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        fn_8004D990(lbl_8034E9A0.ports[0], 0, lbl_80361B20._F4);
        fn_8004D460(0, lbl_2_bss_F410._10[0]);
    }
    lbl_8034E9A0._4701 = 1;
}
#endif

// .text:0x00012F88 size:0xC1C
// NONMATCHING 97.6%: inlines the equivalent fn_2_12238/fn_2_12CD8; case 5 result tests merged
#if NONMATCHING
void fn_2_12F88(void) {
    u16 scene;
    s32 result;
    s32 team;
    s32 slot;

    switch (lbl_803CBBCC->step) {
    case 0:
        if (lbl_803CBBCC->prevScene == 12 && g_d_GameSettings.GameModeSelected == 5 && lbl_803C66B0.active[0] != 0) {
            break;
        }
        fn_2_123CC();
        lbl_803CBBCC->step++;
        // fallthrough
    case 1:
        lbl_803CBBCC->step = 2;
        fn_2_12CD8();
        fn_2_738C8();
        scene = lbl_803CBBCC->prevScene;
        if (scene == 5 || (scene == 12 && g_d_GameSettings.GameModeSelected == 5)) {
            fn_2_1641C();
        }
        changeScene(1, 6);
        break;
    case 2:
        fn_2_12B60();
        fn_2_14790();
        fn_2_12A70();
        break;
    case 4:
        if (g_d_GameSettings.GameModeSelected != 5) {
            if (lbl_2_bss_100B8._40[0] == 0 || lbl_2_bss_100B8._40[1] == 0 || lbl_803C66B0.active[0] != 0 ||
                lbl_803C66B0.active[1] != 0) {
                break;
            }
            fn_800625A4(0, 7);
            fn_800625A4(1, 7);
        } else {
            if (lbl_2_bss_100B8._40[0] == 0) {
                break;
            }
            lbl_2_bss_100B4._0 = 1;
            lbl_803CBCD8._5 = 1;
            lbl_8034E9A0._48B1 = 1;
            changeScene(3, 6);
        }
        lbl_803CBBCC->step = 5;
        break;
    case 5:
        if (lbl_2_bss_100B4._1 != 0) {
            break;
        }
        if (lbl_803297E0._CF5F != 0) {
            if (g_d_GameSettings.GameModeSelected == 5) {
                result = fn_8004D93C(0);
            } else {
                result = fn_8004EE84(0);
            }
        } else {
            if (g_d_GameSettings.GameModeSelected == 5) {
                result = fn_8004D93C(1);
            } else {
                result = fn_8004EE84(2);
            }
        }
        if (result == 0) {
            break;
        }
        lbl_803CBBCC->step = 6;
        // fallthrough
    case 6:
        if (g_d_GameSettings.GameModeSelected != 5 && fn_80062578() == 0) {
            break;
        }
        if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
            break;
        }
        if (lbl_803297E0._CF5F != 0) {
            fn_2_19F2C();
            lbl_8034E9A0._48AD = 1;
            lbl_803C66B0.steps[0][0] = 0;
            memset(&lbl_803C66B0.steps[0][1], 0, 6);
            lbl_8034E9A0._4755 = 3;
            fn_80062A74();
            fn_80021410();
            fn_80035CA4(15);
            fn_80035CA4(18);
            fn_80035CA4(9);
            fn_80035CA4(6);
            lbl_8034E9A0._48AF = 1;
            lbl_8034E9A0._48B1 = 1;
            lbl_8034E978._26 = 1;
            lbl_803297E0._CF5F = 0;
            fn_2_11A0(4);
            break;
        }
        lbl_8034E9A0._48AD = 1;
        lbl_803C66B0.steps[0][0] = 0;
        memset(&lbl_803C66B0.steps[0][1], 0, 6);
        lbl_8034E9A0._4755 = 3;
        if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_8034E9A0._472A = 0;
            fn_800AD038(lbl_8034E9A0.heapMarkA[0]);
            fn_2_19F2C();
            for (team = 0; team < 2; team++) {
                for (slot = 0; slot < 9; slot++) {
                    if (slot == 0) {
                        lbl_803C6724.picks[team][slot] = lbl_8034E9A0.captain[team];
                    } else {
                        lbl_803C6724.picks[team][slot] = -1;
                    }
                }
            }
            fn_80021AC0(0, 0);
            fn_80021AC0(1, 0);
            fn_8006496C();
            fn_2_11A0(10);
        } else {
            lbl_8034E9A0._48AF = 1;
            fn_8006496C();
            if (lbl_8036E548.actors[1].kind != lbl_8034E9A0.captain[0]) {
                lbl_2_bss_100B8._14[0] = 1;
            }
            fn_2_11EA8();
            changeScene(4, 6);
            lbl_8034E9A0._48B2 = 1;
            lbl_8034E978._26 = 1;
            lbl_8034E9A0._48AF = 1;
            fn_800AD038(lbl_8034E9A0.heapMarkA[0]);
            fn_2_19F2C();
            fn_80062A74();
            fn_80035B50(15);
            fn_80035B50(18);
            fn_80035B50(9);
            fn_80035B50(6);
            fn_800AD054(lbl_8034E9A0.heapMarkB[0], lbl_8034E9A0.heapMarkB[1]);
            fn_80021410();
            fn_800ACFB0(lbl_800EF808._098);
            lbl_800E877C._30 = 0;
            lbl_800E877C._32 = 0;
            fn_2_11A0(16);
        }
        break;
    case 8:
        if (lbl_2_bss_100B4._1 != 0) {
            break;
        }
        lbl_2_bss_100B8._40[0] = 1;
        lbl_2_bss_100B8._40[1] = 1;
        if (lbl_803C66B0.active[0] != 0 || lbl_803C66B0.active[1] != 0) {
            break;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            result = fn_8004D93C(0);
        } else {
            result = fn_8004EE84(0);
        }
        if (result == 0) {
            break;
        }
        lbl_803CBBCC->step = 9;
        // fallthrough
    case 9:
        if (g_d_GameSettings.GameModeSelected == 5) {
            if (lbl_803C50E8._47 != 0) {
                lbl_8034E978._26 = 1;
            }
            lbl_8034E9A0._48B1 = 1;
            lbl_803CBCD8._5 = 1;
            fn_800AD038(lbl_8034E9A0.heapMarkA[0]);
            fn_2_11A0(12);
        } else {
            lbl_8034E978._26 = 1;
            fn_80021AC4();
            lbl_8034E9A0._48AD = 1;
            lbl_8034E9A0._4755 = 3;
            lbl_803C66B0.steps[0][0] = 0;
            lbl_803C66B0.portOf[1] = 0;
            lbl_803C66B0.portOf[0] = 0;
            lbl_8034E9A0._472A = 0xFF;
            lbl_8034E9A0._48AF = 1;
            lbl_8034E9A0._48B1 = 1;
            memset(&lbl_803C66B0.steps[0][1], 0, 6);
            lbl_8034E978._26 = 1;
            fn_800AD038(lbl_8034E9A0.heapMarkA[0]);
            g_d_GameSettings._10 = 0;
            fn_2_11A0(5);
        }
        break;
    case 10:
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        lbl_803CBBCC->step = 11;
        break;
    case 11:
        switch (fn_8004CA6C(lbl_8034E9A0.input[(s8)lbl_8034E9A0.ports[lbl_803CBD24.team]].pressed)) {
        case 1:
            fn_8004CC2C();
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 3:
            fn_8006496C();
            lbl_2_bss_100B8._40[0] = 1;
            lbl_2_bss_100B8._40[1] = 1;
            fn_800625A4(0, 7);
            fn_800625A4(1, 7);
            lbl_2_bss_100B4._0 = 1;
            lbl_803CBD24.team = 0;
            lbl_2_bss_100B8._40[1] = 1;
            lbl_2_bss_100B8._40[0] = 1;
            changeScene(15, 6);
            lbl_803CBBCC->step = 5;
            break;
        case 4:
            lbl_803CBD24.team = 0;
            lbl_803CBBCC->step = 2;
            lbl_803297E0._CF5F = 0;
            break;
        }
        break;
    }
}
#endif
