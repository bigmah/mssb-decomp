#include "game/rep_1330.h"
#define REP_HEADER_FN repHeader_1330
#include "header_rep_inline.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "stl/math.h"

#pragma dont_inline on

extern u8 lbl_3_common_bss_32724[];
extern void fn_3_8FC0C(void);
extern void fn_8001B224(void);
extern void fn_3_B908C(void);
extern void fn_3_21C7C(s32, s32);
// .bss (laid out last-defined-first)
u32 lbl_3_bss_1748[0x6];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_1CBCC(void);
extern void fn_80052798(s32);
extern void fn_3_8C07C(void);
extern void fn_3_675B8(s32);
extern void fn_3_BF1AC(void);
extern void fn_3_BF158(void);
extern void fn_3_B902C(void);
extern void sndFXKeyOff(u32);
extern u8 g_ReplayCopies[];
extern u8 g_Scores[];
extern u8 g_RunningLogic[];
extern u8 g_Fielders[];
extern u8 lbl_803537E4[];
extern u8 lbl_803535C8[];
extern u8 lbl_3_common_bss_32234[];
extern u8 lbl_3_common_bss_32230[];
extern u8 lbl_3_common_bss_32220[];
extern u8 g_UnkThrowing_31ACC[];
extern u8 g_UnkAnimation_31EAC[];
extern u8 lbl_3_common_bss_321A0[];

// .text:0x0007C1FC size:0x2E8
void fn_3_7C1FC(s32 flag) {
    g_Stats_s* st = &g_Stats;
    st->replayInd = 0;
    st->_39 = 0;
    memcpy(&g_GameLogic, g_ReplayCopies, 0x158);
    memcpy(&g_Strikes, g_ReplayCopies + 0x158, 0x24);
    memcpy(g_Scores, g_ReplayCopies + 0x17c, 0xc8);
    memcpy(&g_Ball, g_ReplayCopies + 0x244, 0x1bf8);
    memcpy(&g_Pitcher, g_ReplayCopies + 0x1e3c, 0x178);
    memcpy(&g_Batter, g_ReplayCopies + 0x1fb4, 0xb0);
    memcpy(&g_AiLogic, g_ReplayCopies + 0x2064, 0xbc);
    memcpy(&g_FieldingLogic, g_ReplayCopies + 0x2120, 0x150);
    memcpy(g_RunningLogic, g_ReplayCopies + 0x2270, 0x20);
    memcpy(g_Fielders, g_ReplayCopies + 0x2290, 0x15a8);
    memcpy(g_Runners, g_ReplayCopies + 0x3838, 0x550);
    memcpy(lbl_803537E4, g_ReplayCopies + 0x4128, 0x2ac);
    memcpy(lbl_803535C8, g_ReplayCopies + 0x43d4, 0x21c);
    memcpy(lbl_3_common_bss_32234, g_ReplayCopies + 0x3d88, 0x6);
    memcpy(lbl_3_common_bss_32230, g_ReplayCopies + 0x3d8e, 0x4);
    memcpy(lbl_3_common_bss_32220, g_ReplayCopies + 0x3d92, 0xe);
    memcpy(g_UnkThrowing_31ACC, g_ReplayCopies + 0x3da0, 0x14);
    memcpy(g_UnkAnimation_31EAC, g_ReplayCopies + 0x3db4, 0x2f4);
    memcpy(lbl_3_common_bss_321A0, g_ReplayCopies + 0x40a8, 0x80);
    if (g_Stats._3C != 2 && st->_3C != 0xD) {
        fn_3_FBD70();
        if (flag != 0) {
            fn_3_FBD58();
            fn_3_1CBCC();
        }
    }
    fn_80052798(1);
    lbl_3_common_bss_34C58._2A = 1;
    lbl_3_common_bss_34C58._24 = 1;
    fn_3_8C07C();
    lbl_3_common_bss_34C58._33 = 2;
    fn_3_675B8(0);
    fn_3_BF1AC();
    fn_3_BF158();
    fn_3_B902C();
    if (lbl_3_bss_1748[0] != 0) {
        sndFXKeyOff(lbl_3_bss_1748[0]);
    }
}

// .text:0x0007C4E4 size:0x2C8 mapped:0x806BB578
// NONMATCHING 89%: the original addresses its float constants as separate .rodata symbols
// (lbl_3_rodata_1380..13B0, not yet split) and keeps the replay-frame offset in its own register
#if NONMATCHING
void fn_3_7C4E4(void) {
    g_Stats_s* st = &g_Stats;
    ReplayFrame* frame;
    int i;
    ReplayInput* in;

    if (st->playFrameCounter >= st->endFrame) {
        fn_3_7C1FC(1);
        return;
    }
    if (st->playFrameCounter + 7 == st->endFrame && st->_3C != 2 && st->_3C != 0xD) {
        changeScene(3, 6);
    }
    frame = &g_ReplayLogic[st->playFrameCounter];
    in = frame->input;
    for (i = 0; i < 2; i++, in++) {
        InputStruct* c = &g_Controls[g_Stats.controller[i]];
        f32 mag;
        c->buttonInput = frame->input[i].buttonInput;
        c->newButtonInput = frame->input[i].newButtonInput;
        c->right_left = frame->input[i].right_left;
        c->up_down = frame->input[i].up_down;
        g_Controls[g_Stats.controller[i]].controlStickAngle = in->controlStickAngle;
        mag = dolsqrtf2((f32)c->right_left * (f32)c->right_left + (f32)c->up_down * (f32)c->up_down) - 16.0f;
        if (mag > 56.0f) {
            mag = 56.0f;
        }
        g_Controls[g_Stats.controller[i]].controlStickMagnitude = 64.0f * mag / 56.0f;
    }
    st->playFrameCounter++;
}
#endif


// .text:0x0007C7AC size:0x22C
void fn_3_7C7AC(void) {
    memcpy(g_ReplayCopies, &g_GameLogic, 0x158);
    memcpy(g_ReplayCopies + 0x158, &g_Strikes, 0x24);
    memcpy(g_ReplayCopies + 0x17c, g_Scores, 0xc8);
    memcpy(g_ReplayCopies + 0x244, &g_Ball, 0x1bf8);
    memcpy(g_ReplayCopies + 0x1e3c, &g_Pitcher, 0x178);
    memcpy(g_ReplayCopies + 0x1fb4, &g_Batter, 0xb0);
    memcpy(g_ReplayCopies + 0x2064, &g_AiLogic, 0xbc);
    memcpy(g_ReplayCopies + 0x2120, &g_FieldingLogic, 0x150);
    memcpy(g_ReplayCopies + 0x2270, g_RunningLogic, 0x20);
    memcpy(g_ReplayCopies + 0x2290, g_Fielders, 0x15a8);
    memcpy(g_ReplayCopies + 0x3838, g_Runners, 0x550);
    memcpy(g_ReplayCopies + 0x4128, lbl_803537E4, 0x2ac);
    memcpy(g_ReplayCopies + 0x43d4, lbl_803535C8, 0x21c);
    memcpy(g_ReplayCopies + 0x3d88, lbl_3_common_bss_32234, 0x6);
    memcpy(g_ReplayCopies + 0x3d8e, lbl_3_common_bss_32230, 0x4);
    memcpy(g_ReplayCopies + 0x3d92, lbl_3_common_bss_32220, 0xe);
    memcpy(g_ReplayCopies + 0x3da0, g_UnkThrowing_31ACC, 0x14);
    memcpy(g_ReplayCopies + 0x3db4, g_UnkAnimation_31EAC, 0x2f4);
    memcpy(g_ReplayCopies + 0x40a8, lbl_3_common_bss_321A0, 0x80);
}

// .text:0x0007C9D8 size:0x4B8
void fn_3_7C9D8(s32 flag) {
    s32 i;
    if (flag == 0) {
        memcpy(g_ReplayCopies, &g_GameLogic, 0x158);
        memcpy(g_ReplayCopies + 0x158, &g_Strikes, 0x24);
        memcpy(g_ReplayCopies + 0x17c, g_Scores, 0xc8);
        memcpy(g_ReplayCopies + 0x244, &g_Ball, 0x1bf8);
        memcpy(g_ReplayCopies + 0x1e3c, &g_Pitcher, 0x178);
        memcpy(g_ReplayCopies + 0x1fb4, &g_Batter, 0xb0);
        memcpy(g_ReplayCopies + 0x2064, &g_AiLogic, 0xbc);
        memcpy(g_ReplayCopies + 0x2120, &g_FieldingLogic, 0x150);
        memcpy(g_ReplayCopies + 0x2270, g_RunningLogic, 0x20);
        memcpy(g_ReplayCopies + 0x2290, g_Fielders, 0x15a8);
        memcpy(g_ReplayCopies + 0x3838, g_Runners, 0x550);
        memcpy(g_ReplayCopies + 0x4128, lbl_803537E4, 0x2ac);
        memcpy(g_ReplayCopies + 0x43d4, lbl_803535C8, 0x21c);
        memcpy(g_ReplayCopies + 0x3d88, lbl_3_common_bss_32234, 0x6);
        memcpy(g_ReplayCopies + 0x3d8e, lbl_3_common_bss_32230, 0x4);
        memcpy(g_ReplayCopies + 0x3d92, lbl_3_common_bss_32220, 0xe);
        memcpy(g_ReplayCopies + 0x3da0, g_UnkThrowing_31ACC, 0x14);
        memcpy(g_ReplayCopies + 0x3db4, g_UnkAnimation_31EAC, 0x2f4);
        memcpy(g_ReplayCopies + 0x40a8, lbl_3_common_bss_321A0, 0x80);
    }
    memcpy(&g_GameLogic, g_Stats.gameLogic, 0x158);
    memcpy(&g_Strikes, g_Stats.strikes, 0x24);
    memcpy(g_Scores, g_Stats.scores, 0xc8);
    memcpy(&g_Ball, g_Stats.ball, 0x1bf8);
    memcpy(&g_Pitcher, g_Stats.pitcher, 0x178);
    memcpy(&g_Batter, g_Stats.batter, 0xb0);
    memcpy(&g_AiLogic, g_Stats.aiLogic, 0xbc);
    memcpy(&g_FieldingLogic, g_Stats.fieldingLogic, 0x150);
    memcpy(g_RunningLogic, g_Stats.runningLogic, 0x20);
    memcpy(g_Fielders, g_Stats.fielders, 0x15a8);
    memcpy(g_Runners, g_Stats.runners, 0x550);
    memcpy(lbl_803537E4, g_Stats.lbl_803537E4, 0x2ac);
    memcpy(lbl_803535C8, g_Stats.lbl_803535C8, 0x21c);
    memcpy(lbl_3_common_bss_32234, g_Stats.bss_32234, 0x6);
    memcpy(lbl_3_common_bss_32230, g_Stats.bss_32230, 0x4);
    memcpy(lbl_3_common_bss_32220, g_Stats.bss_32220, 0xe);
    memcpy(g_UnkThrowing_31ACC, g_Stats.throwing, 0x14);
    memcpy(g_UnkAnimation_31EAC, g_Stats.animation, 0x2f4);
    memcpy(lbl_3_common_bss_321A0, g_Stats.bss_321A0, 0x80);
    g_Stats.replayInd = 1;
    g_Stats.playFrameCounter = 0;
    fn_3_7C4E4();
    fn_3_1CBCC();
    fn_3_8FC0C();
    lbl_3_common_bss_32724[0xC8] = 0;
    fn_8001B224();
    fn_3_B908C();
    for (i = 0; i < 13; i++) {
        fn_3_21C7C(i, 1);
    }
    lbl_3_common_bss_34C58._34 = 0;
}

