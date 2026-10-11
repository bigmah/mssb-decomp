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
// NONMATCHING 97%: inMemRoster row address and the li 0 for differentClass are scheduled differently
#if NONMATCHING
s32 fn_3_1D86C(void) {
    s32 team;
    CharacterStats* roster;
    s32 n;
    s32 r;
    s32 i;
    PitcherCandidate cand[9];
    s32 cnt;
    s32 cls;
    s32 sel;
    s16 pitcher;
    s16 savedPos;

    team = g_GameLogic.teamFielding;
    pitcher = lbl_3_common_bss_34C90.lineup[team][0].roster[0];
    if (fn_3_6D564(team, pitcher, 0) >= lbl_3_data_5EDC[3]) {
        return 0;
    }

    for (i = 0, n = 0; i < 9; i++) {
        if (fn_3_6D564(g_GameLogic.teamFielding, i, 0) >= lbl_3_data_5EDC[3]) {
            cand[n].idx = i;
            n++;
        }
    }
    if (n == 0) {
        return 0;
    }

    roster = inMemRoster[team];
    cls = roster[pitcher].stats.CharacterClass;
    cnt = 0;
    for (i = 0; i < n; i++) {
        cand[i].differentClass = 0;
        if (cls != roster[cand[i].idx].stats.CharacterClass) {
            cand[i].differentClass = 1;
            cnt++;
        }
    }

    if (cnt != 0) {
        r = random_fn_3_9EE24(cnt);
        for (i = 0; i < n; i++) {
            if (cand[i].differentClass) {
                if (r == 0) {
                    sel = cand[i].idx;
                    goto found;
                }
                r--;
            }
        }
    }
    r = random_fn_3_9EE24(n);
    for (i = 0; i < n; i++) {
        if (r == 0) {
            sel = cand[i].idx;
            goto found;
        }
        r--;
    }
    return 0;

found:
    for (i = 1; i < 10; i++) {
        if (sel == lbl_3_common_bss_34C90.lineup[team][i].roster[0]) {
            savedPos = lbl_3_common_bss_34C90.lineup[team][i].position[0];
            lbl_3_common_bss_34C90.lineup[team][i].position[1] = 0;
            lbl_3_common_bss_34C90.lineup[team][0].roster[1] = sel;
        }
    }
    for (i = 1; i < 10; i++) {
        if (pitcher == lbl_3_common_bss_34C90.lineup[team][i].roster[0]) {
            lbl_3_common_bss_34C90.lineup[team][i].position[1] = savedPos;
        }
    }
    return 1;
}
#endif

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
