#include "game/auto_00_0007CE90_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern ScoresView g_Scores;
extern RunningLogicView g_RunningLogic;

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
void fn_3_7CF88(void) {
    return;
}

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
void fn_3_7D458(void) {
    return;
}

// .text:0x0007D780 size:0x1C mapped:0x806BC814
void fn_3_7D780(void) {
    g_Stats.replayInd = 0;
    g_Stats.recording = 0;
    g_Stats._38 = 0;
}
