#include "menus/rep_0438.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_800639BC.h"
#include "main/file_800A7C08.h"
#include "main/file_800527C4.h"
#include "main/file_8004C5F8.h"
#include "main/menu_globals.h"
#include "static/GameSettings.h"
#include "menus/rep_04B0.h"
#include "menus/rep_0568.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/auto_00_00016870_text.h"
#include "Dolphin/os.h"
#include <string.h>

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
    lbl_2_bss_100B4 = 0;
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
            lbl_2_bss_100B4 = 1;
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
void fn_2_12F88(void) {
    return;
}
