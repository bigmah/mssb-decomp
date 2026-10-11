#include "game/rep_1770.h"
#include "header_rep_data.h"

#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_data_D258[];
extern u8 lbl_3_data_D378[];
extern u8 lbl_3_data_D4F8[];
extern void playSoundEffect(int);

// .text:0x000993A8 size:0x3C4 mapped:0x806D843C
void fn_3_993A8(void) {
    return;
}

// .text:0x0009976C size:0xAC mapped:0x806D8800
void fn_3_9976C(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_D378);
    if (g_Batter.batterHand != 0) {
        HUD_OBJ(task, 0)->_5C = 0;
    } else {
        HUD_OBJ(task, 0)->_5C = 0x10000;
    }
    task->state = 0;
    HUD_TASK->func = fn_3_993A8;
}

// .text:0x00099818 size:0x3C4 mapped:0x806D88AC
void fn_3_99818(void) {
    return;
}

// .text:0x00099BDC size:0xAC mapped:0x806D8C70
void fn_3_99BDC(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_D258);
    if (g_Minigame.GameMode_MiniGame == 2) {
        HUD_OBJ(task, 0)->_5C = 0x30000;
    } else {
        HUD_OBJ(task, 0)->_5C = 0x20000;
    }
    task->state = 0;
    HUD_TASK->func = fn_3_99818;
}

// .text:0x00099C88 size:0x74 mapped:0x806D8D1C
void fn_3_99C88(void) {
    HudTask* task = HUD_TASK;
    u8 v;
    if (lbl_3_common_bss_32724.hudOff == 0 && (v = lbl_3_common_bss_32724._A7) != 0) {
        LayoutObj* o = HUD_OBJ(task, 0);
        u32 w = o->color;
        w = v | (w & ~0xFF);
        o->color = w;
    } else {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}

// .text:0x00099CFC size:0x114 mapped:0x806D8D90
void fn_3_99CFC(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_D4F8);
    if (!(g_Batter.runnersOnBase & 1)) {
        HUD_OBJ(task, 3)->flags &= ~2;
    }
    if (!(g_Batter.runnersOnBase & 2)) {
        HUD_OBJ(task, 2)->flags &= ~2;
    }
    if (!(g_Batter.runnersOnBase & 4)) {
        HUD_OBJ(task, 1)->flags &= ~2;
    }
    if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0) {
        playSoundEffect(0x1AB);
    }
    HUD_TASK->func = fn_3_99C88;
}

// .text:0x00099E10 size:0xA94 mapped:0x806D8EA4
void fn_3_99E10(void) {
    return;
}

// .text:0x0009A8A4 size:0x864 mapped:0x806D9938
void fn_3_9A8A4(void) {
    return;
}

// .text:0x0009B108 size:0x218 mapped:0x806DA19C
void fn_3_9B108(HudTask* task) {
    if (g_Scores.team[0].runs[0] >= 10) {
        fn_3_972A0(task, 11, 4, g_Scores.team[0].runs[0] % 10);
        fn_3_972A0(task, 12, 3, g_Scores.team[0].runs[0] / 10);
        fn_3_972A0(task, 11, 10, g_Scores.team[0].runs[0] % 10);
        fn_3_972A0(task, 12, 9, g_Scores.team[0].runs[0] / 10);
    } else {
        fn_3_972A0(task, 10, 1, g_Scores.team[0].runs[0]);
        fn_3_972A0(task, 10, 7, g_Scores.team[0].runs[0]);
    }
    if (g_Scores.team[1].runs[0] >= 10) {
        fn_3_972A0(task, 14, 6, g_Scores.team[1].runs[0] % 10);
        fn_3_972A0(task, 15, 5, g_Scores.team[1].runs[0] / 10);
        fn_3_972A0(task, 14, 12, g_Scores.team[1].runs[0] % 10);
        fn_3_972A0(task, 15, 11, g_Scores.team[1].runs[0] / 10);
    } else {
        fn_3_972A0(task, 13, 2, g_Scores.team[1].runs[0]);
        fn_3_972A0(task, 13, 8, g_Scores.team[1].runs[0]);
    }
}

// .text:0x0009B320 size:0x4D4 mapped:0x806DA3B4
void fn_3_9B320(void) {
    return;
}

// .text:0x0009B7F4 size:0x6EC mapped:0x806DA888
void fn_3_9B7F4(void) {
    return;
}

// .text:0x0009BEE0 size:0x134 mapped:0x806DAF74
void fn_3_9BEE0(HudTask* task) {
    // TODO type: strikes/balls/outs read as an s32[3]; the named fields change register allocation
    s32 target = ((s32*)&g_Strikes)[2];
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        target = g_Minigame._190D - g_Minigame._1910;
    }
    for (i = 0; i < 7; i++) {
        s32 state = 3;
        if (g_d_GameSettings.GameModeSelected == 6 && i >= 5) {
            break;
        }
        if (i < 2) {
            if (task->state == ((s32*)&g_Strikes)[0]) {
                continue;
            }
            if (((s32*)&g_Strikes)[0] >= i + 1) {
                state = 0;
            }
        } else if (i < 5) {
            if (task->_1E == ((s32*)&g_Strikes)[1]) {
                continue;
            }
            if (((s32*)&g_Strikes)[1] >= i - 1) {
                state = 1;
            }
        } else {
            if (task->_20 == target) {
                continue;
            }
            if (target >= i - 4) {
                state = 2;
            }
        }
        fn_8003649C(task, i + 1, i + 1, 0x107, state);
    }
    task->state = ((s32*)&g_Strikes)[0];
    task->_1E = ((s32*)&g_Strikes)[1];
    task->_20 = target;
}

// .text:0x0009C014 size:0x278 mapped:0x806DB0A8
void fn_3_9C014(void) {
    return;
}

// .text:0x0009C28C size:0x2EC mapped:0x806DB320
void fn_3_9C28C(void) {
    return;
}

