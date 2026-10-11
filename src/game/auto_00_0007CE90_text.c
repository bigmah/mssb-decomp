#include "game/auto_00_0007CE90_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1D58.h"
#include "game/rep_720.h"
#include "game/rep_1330.h"
#include "game/auto_00_0007976C_text.h"
#include "game/auto_00_0005985C_text.h"

extern ScoresView g_Scores;
extern RunningLogicView g_RunningLogic;
extern u8 g_Fielders[];
extern u8 lbl_803537E4[];
extern u8 lbl_803535C8[];
extern u8 lbl_3_common_bss_32234[];
extern u8 lbl_3_common_bss_32230[];
extern u8 lbl_3_common_bss_32220[];
extern u8 g_UnkThrowing_31ACC[];
extern u8 g_UnkAnimation_31EAC[];
extern u8 lbl_3_common_bss_321A0[];
extern ReplayActorMgrView lbl_8036E548;
extern void* memcpy(void*, const void*, u32);
extern void fn_8001B2D0(void);
extern s32 fn_3_6C938(s32, s32);
extern ReplayFadeView lbl_8037169C;

// Same as fn_3_7C194: can the replay be skipped this frame?
static inline s32 replayCanSkip(void) {
    if (g_Stats.playFrameCounter < 0x5A) {
        return 0;
    }
    if (g_Stats.playFrameCounter > g_Stats.endFrame - 0x3C) {
        return 0;
    }
    if (fn_3_6C938(1, 0x1100) != 0) {
        return 1;
    }
    return 0;
}

// Records both controllers' input for the current replay frame.
static inline void recordReplayFrame(void) {
    ReplayFrame* frame;
    InputStruct* in;

    if (g_Stats.playFrameCounter >= REPLAY_MAX_FRAMES) {
        g_Stats.endFrame = REPLAY_MAX_FRAMES - 1;
    } else {
        in = &g_Controls[g_Stats.controller[0]];
        frame = &g_ReplayLogic[g_Stats.playFrameCounter];
        frame->input[0].controlStickAngle = g_Controls[g_Stats.controller[0]].controlStickAngle;
        frame->input[0].buttonInput = in->buttonInput & 0xEFFF;
        frame->input[0].newButtonInput = in->newButtonInput & 0xEFFF;
        frame->input[0].right_left = in->right_left;
        frame->input[0].up_down = in->up_down;
        in = &g_Controls[g_Stats.controller[1]];
        frame->input[1].controlStickAngle = g_Controls[g_Stats.controller[1]].controlStickAngle;
        frame->input[1].buttonInput = in->buttonInput & 0xEFFF;
        frame->input[1].newButtonInput = in->newButtonInput & 0xEFFF;
        frame->input[1].right_left = in->right_left;
        frame->input[1].up_down = in->up_down;
        g_Stats.playFrameCounter++;
    }
}

// .text:0x0007CE90 size:0xF8 mapped:0x806BBF24
void fn_3_7CE90(void) {
    if (g_Stats.recording != 0) {
        g_Stats.recording = 0;
        g_Stats.endFrame = g_Stats.playFrameCounter;
        g_Stats._2A = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs;
        g_Stats._2C = g_Scores._A0;
        g_Stats._2E = g_Scores._C2;
        g_Stats._30 = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs;
        if (g_Ball.deadBallReason == 1) {
            g_Stats._2E = g_RunningLogic._12;
            g_Stats._2A = g_Scores._A0 + g_RunningLogic._12;
        }
        g_Stats.hitVerticalAngle = g_Ball.Hit_VerticalAngle;
        g_Stats.hitHorizontalAngle = g_Ball.Hit_HorizontalAngle;
        g_Stats.hitHorizontalPower = g_Ball.Hit_HorizontalPower;
        g_Stats.landingSpotLocation.x = g_Ball.landingSpotLocation.x;
        g_Stats.landingSpotLocation.z = g_Ball.landingSpotLocation.z;
        g_Stats.ballPickedUpCaught.x = g_Ball.ballPickedUpCaught.x;
        g_Stats.ballPickedUpCaught.z = g_Ball.ballPickedUpCaught.z;
        g_Stats.deadballLastLoc.x = g_Ball.deadballLastLoc.x;
        g_Stats.deadballLastLoc.y = g_Ball.deadballLastLoc.y;
        g_Stats.deadballLastLoc.z = g_Ball.deadballLastLoc.z;
    }
}

// .text:0x0007CF88 size:0x358 mapped:0x806BC01C
// NONMATCHING 90%: inlined recordReplayFrame differs (see fn_3_7D2E0); original also re-reads the stored counter/controllers
#if NONMATCHING
void fn_3_7CF88(void) {
    memcpy(g_Stats.gameLogic, &g_GameLogic, 0x158);
    memcpy(g_Stats.strikes, &g_Strikes, 0x24);
    memcpy(g_Stats.scores, &g_Scores, 0xC8);
    memcpy(g_Stats.ball, &g_Ball, 0x1BF8);
    memcpy(g_Stats.pitcher, &g_Pitcher, 0x178);
    memcpy(g_Stats.batter, &g_Batter, 0xB0);
    memcpy(g_Stats.aiLogic, &g_AiLogic, 0xBC);
    memcpy(g_Stats.fieldingLogic, &g_FieldingLogic, 0x150);
    memcpy(g_Stats.runningLogic, &g_RunningLogic, 0x20);
    memcpy(g_Stats.fielders, g_Fielders, 0x15A8);
    memcpy(g_Stats.runners, g_Runners, 0x550);
    memcpy(g_Stats.lbl_803537E4, lbl_803537E4, 0x2AC);
    memcpy(g_Stats.lbl_803535C8, lbl_803535C8, 0x21C);
    memcpy(g_Stats.bss_32234, lbl_3_common_bss_32234, 6);
    memcpy(g_Stats.bss_32230, lbl_3_common_bss_32230, 4);
    memcpy(g_Stats.bss_32220, lbl_3_common_bss_32220, 0xE);
    memcpy(g_Stats.throwing, g_UnkThrowing_31ACC, 0x14);
    memcpy(g_Stats.animation, g_UnkAnimation_31EAC, 0x2F4);
    memcpy(g_Stats.bss_321A0, lbl_3_common_bss_321A0, 0x80);
    g_Stats.playFrameCounter = 0;
    g_Stats.recording = 1;
    g_Stats._39 = 0;
    g_Stats._3B = 0;
    g_Stats._3C = 0;
    g_Stats._3D = 0;
    g_Stats._3E = 1;
    g_Stats._3A = 0;
    g_Stats._32 = 0;
    g_Stats.controller[0] = g_GameLogic.teams[0];
    g_Stats.controller[1] = g_GameLogic.teams[1];
    recordReplayFrame();
    fn_8001B2D0();
    if (lbl_8036E548.active[9] != NULL) {
        g_Stats._34 = lbl_8036E548.active[9]->_68;
    }
    fn_3_B9124();
    fn_3_15D90();
}
#endif

// .text:0x0007D2E0 size:0xBC mapped:0x806BC374
// NONMATCHING 65%: original loads controlStickAngle with lhax off g_Controls and schedules differently
#if NONMATCHING
void fn_3_7D2E0(void) {
    recordReplayFrame();
}
#endif

// .text:0x0007D39C size:0xBC mapped:0x806BC430
// NONMATCHING 65%: original loads controlStickAngle with lhax off g_Controls and schedules differently
#if NONMATCHING
void fn_3_7D39C(void) {
    recordReplayFrame();
}
#endif

// .text:0x0007D458 size:0x328 mapped:0x806BC4EC
// NONMATCHING 84%: inlined recordReplayFrame differs (see fn_3_7D2E0) and g_Stats base register reloads differ
#if NONMATCHING
void fn_3_7D458(void) {
    if (g_Stats.replayInd != 0) {
        if (g_Stats.playFrameCounter == 9) {
            changeScene(1, 6);
        }
        if (g_Stats.playFrameCounter + 1 >= g_Stats.endFrame && g_Stats._3A != 0) {
            g_Stats._3A = 2;
            g_Stats._39 = 0xFF;
            fn_3_7C9D8(0);
            g_Stats._39 = 3;
            changeScene(1, 6);
            return;
        }
        if (g_Stats._39 == 4) {
            if (lbl_8037169C.done != 0) {
                g_Stats._39 = 0;
                fn_3_7C1FC(1);
            }
        } else if (g_Stats._39 == 5) {
            g_Stats.playFrameCounter = g_Stats.endFrame - 7;
            g_Stats._39 = 0;
            changeScene(3, 6);
        } else if (replayCanSkip() && g_d_GameSettings.GameModeSelected != 4) {
            g_Stats._39 = 4;
            changeScene(3, 6);
        }
        fn_3_7C4E4();
        if (g_Stats.replayInd == 0) {
            if (g_Stats._3C == 2 || g_Stats._3C == 13) {
                fn_3_5A6D4(0x13);
            } else if (g_Stats._3C == 4 || (g_Stats._3C == 1 && g_Stats._3D == 4)) {
                fn_3_5A6D4(0x15);
            }
        }
    } else if (g_Stats.recording != 0) {
        recordReplayFrame();
        fn_3_7C190();
    } else if (g_Stats._39 == 2) {
        fn_3_7C9D8(0);
        changeScene(1, 6);
        g_Stats._39 = 3;
        fn_3_15D64();
    } else if (g_Stats._38 == 1) {
        fn_3_7CF88();
        g_Stats._38 = 2;
    }
    if (g_pCamera->_AC5 != 0) {
        fn_3_15D7C(0);
        fn_3_15D64();
        if (g_Stats._3C != 12 && g_Stats._3C != 1) {
            fn_3_15D28();
        }
    }
}
#endif

// .text:0x0007D780 size:0x1C mapped:0x806BC814
void fn_3_7D780(void) {
    g_Stats.replayInd = 0;
    g_Stats.recording = 0;
    g_Stats._38 = 0;
}
