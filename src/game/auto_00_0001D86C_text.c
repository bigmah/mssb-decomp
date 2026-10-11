#include "game/auto_00_0001D86C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0006D4A0_text.h"
#include "game/rep_1838.h"
#include "game/rep_8C8.h"

extern s16 lbl_3_data_5EDC[]; // [3]: stamina threshold below which the pitcher is replaced

typedef struct PitcherCandidate {
    s32 idx;
    s32 differentClass;
} PitcherCandidate;

// .text:0x0001D86C size:0x2F0 mapped:0x8065C900
void fn_3_1D86C(void) {
    return;
}

// .text:0x0001DB5C size:0xD4 mapped:0x8065CBF0
void fn_3_1DB5C(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].roster[1] =
            lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].roster[0] =
                g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0];
        lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].position[1] =
            lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].position[0] =
                g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
    }
    fn_3_1D86C();
}

// .text:0x0001DC30 size:0x118 mapped:0x8065CCC4
void fn_3_1DC30(void) {
    s32 changed;
    s32 i;

    if (g_GameLogic._13E[g_GameLogic.teamFielding] != 0) {
        changed = 0;
        for (i = 0; i < 10; i++) {
            lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].roster[1] =
                lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].roster[0] =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0];
            lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].position[1] =
                lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i].position[0] =
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
        }
        changed |= fn_3_1D86C();
        if (changed) {
            lbl_3_common_bss_34C90.changed[g_GameLogic.teamFielding] = 1;
        }
    }
}

// .text:0x0001DD48 size:0x20 mapped:0x8065CDDC
void fn_3_1DD48(void) {
    fn_3_1FF48();
}

// .text:0x0001DD68 size:0x150 mapped:0x8065CDFC
void fn_3_1DD68(void) {
    s32 fielding;
    s32 runners;
    s32 batting;
    g_AiLogic._48 = 1;
    runners = 0;
    if (g_RunningLogic.runnerBits & 0x1000) {
        runners = 1;
    }
    if (g_RunningLogic.runnerBits & 0x100) {
        runners++;
    }
    if (g_Scores.inning >= 4 && g_Scores._AD != 0 && runners != 0 &&
        g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs + runners >
            g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs) {
        g_AiLogic._48 = 4;
        return;
    }
    if (g_Scores.inning >= 3 && runners != 0) {
        fielding = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs;
        batting = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs;
        if (fielding < batting && fielding + runners >= batting) {
            g_AiLogic._48 = 3;
            return;
        }
        if (fielding == batting) {
            g_AiLogic._48 = 2;
            return;
        }
    }
    if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs + 5 <
        g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs) {
        g_AiLogic._48 = 0;
    }
}
