#include "game/auto_00_0009C578_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_00097144_text.h"
#include "game/rep_16B8.h"
#include "game/rep_1770.h"

extern GameScores g_Scores;

// .text:0x0009C578 size:0x21C mapped:0x806DB60C
void fn_3_9C578(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && lbl_3_common_bss_32724._A5 == 0) {
        lbl_3_common_bss_32724._A5 = 1;
        lbl_3_common_bss_32724._A6 = 0;
        lbl_3_common_bss_32724._A7 = 0xFF;
        fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
        fn_800B0A5C_insertQueue(fn_3_9B7F4, 2);
        if (lbl_3_common_bss_32724._A8 == 0) {
            fn_800B0A5C_insertQueue(fn_3_9A8A4, 2);
        }
        if (g_Batter.chemLinksOnBase != 0) {
            fn_800B0A5C_insertQueue(fn_3_99CFC, 2);
        }
    }
    if (lbl_3_common_bss_32724._AC == 1 && g_GameLogic.FrameCountOfCurrentPitch == 0xA) {
        fn_800B0A5C_insertQueue(fn_3_955CC, 2);
        lbl_3_common_bss_32724._AC = 2;
    }
    if (lbl_3_common_bss_32724._A5 != 0 && lbl_3_common_bss_32724._A6 < 0xFF) {
        if (lbl_3_common_bss_32724._A6 < 0xF0) {
            lbl_3_common_bss_32724._A6 += 0x10;
        } else {
            lbl_3_common_bss_32724._A6 = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724._A7 != 0 && lbl_3_common_bss_32724._A7 < 0xFF) {
        if (lbl_3_common_bss_32724._A7 <= 0x10) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        } else {
            lbl_3_common_bss_32724._A7 -= 0x10;
        }
    } else if (lbl_3_common_bss_32724._A5 != 0) {
        if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && (g_Batter.moonShotInd == 0 || g_Ball.framesSinceHit > 1)) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
        if (lbl_3_common_bss_34C90._1D5 != 0) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
    }
    if (g_GameLogic.gameStatus == 8) {
        lbl_3_common_bss_32724._A7 = 0;
        lbl_3_common_bss_32724._A5 = 0;
    }
}

// .text:0x0009C794 size:0x35C mapped:0x806DB828
void fn_3_9C794(void) {
    s32 fielding;
    s32 batting;
    s32 before;
    BOOL changed;
    s32 scored;
    s32 i;

    changed = FALSE;
    fielding = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0];
    batting = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
    before = g_Scores._A0;
    if (g_Scores._C2 == 0) {
        return;
    }
    if (before == 0 && batting == 0) {
        lbl_3_common_bss_32A94._7D = g_Scores.inning;
        changed = TRUE;
        lbl_3_common_bss_32A94._7E = g_Scores._AD;
        lbl_3_common_bss_32A94._88 = g_Scores.inning;
        lbl_3_common_bss_32A94._89 = g_Scores._AD;
        lbl_80353A90._F8 = g_Pitcher.rosterID;
    } else if (fielding == batting) {
        lbl_3_common_bss_32A94._7F = g_Scores.inning;
        lbl_3_common_bss_32A94._80 = g_Scores._AD;
        lbl_3_common_bss_32A94._81++;
    } else if (fielding > batting) {
        if (before == batting) {
            if (lbl_3_common_bss_32A94._7F != 0 && lbl_3_common_bss_32A94._80 == g_Scores._AD) {
                lbl_3_common_bss_32A94._83 = g_Scores._AD;
                lbl_3_common_bss_32A94._82 = g_Scores.inning;
                lbl_3_common_bss_32A94._84++;
                lbl_3_common_bss_32A94._88 = g_Scores.inning;
                lbl_3_common_bss_32A94._89 = g_Scores._AD;
            } else {
                lbl_3_common_bss_32A94._85 = g_Scores.inning;
                lbl_3_common_bss_32A94._86 = g_Scores._AD;
                lbl_3_common_bss_32A94._87++;
                lbl_3_common_bss_32A94._88 = g_Scores.inning;
                lbl_3_common_bss_32A94._89 = g_Scores._AD;
            }
            changed = TRUE;
            lbl_80353A90._F8 = g_Pitcher.rosterID;
        } else if (before < batting) {
            lbl_3_common_bss_32A94._82 = g_Scores.inning;
            changed = TRUE;
            lbl_3_common_bss_32A94._83 = g_Scores._AD;
            lbl_3_common_bss_32A94._84++;
            lbl_3_common_bss_32A94._88 = g_Scores.inning;
            lbl_3_common_bss_32A94._89 = g_Scores._AD;
            lbl_80353A90._F8 = g_Pitcher.rosterID;
        }
    }
    if (fielding > batting && g_Scores.inning >= g_Scores.maxInnings && g_Scores._AD != 0) {
        lbl_3_common_bss_32A94._8A = g_Scores.inning;
        lbl_80353A90._FA = g_Batter.rosterID;
        if (g_Ball.deadBallReason == 1) {
            lbl_80353A90._F9 = g_Batter.rosterID;
            lbl_80353A90._FB = g_Batter.rosterID;
        } else {
            scored = 0;
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    scored++;
                    if (before + scored > batting) {
                        lbl_80353A90._F9 = g_Runners[i].rosterID;
                        break;
                    }
                }
            }
        }
    }
    if (changed) {
        if (g_Scores._AC >= 3) {
            if (lbl_3_common_bss_32A94._22 > 0) {
                lbl_80353A90._FC = g_GameLogic.teamBatting;
                lbl_80353A90._FD = g_Batter.rosterID;
            } else {
                lbl_80353A90._FC = -1;
                lbl_80353A90._FD = -1;
            }
        }
        lbl_80353A90._FE = g_GameLogic.teamBatting;
        lbl_80353A90._FF = g_Batter.rosterID;
        if (lbl_3_common_bss_32A94._22 > 0) {
            lbl_80353A90._100 = 1;
        } else {
            lbl_80353A90._100 = 0;
        }
    }
}
