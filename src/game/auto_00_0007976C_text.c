#include "game/auto_00_0007976C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000759BC_text.h"

extern ScoresView g_Scores;
extern PitcherGameStat lbl_3_common_bss_32A38[2][9];

extern u8 lbl_803535C8[];
extern u8 lbl_803537E4[];
extern s32 fn_3_6C938(s32, s32);

#pragma dont_inline on

// fn_3_79A00, size:0xCC
void fn_3_79A00(void) {
    s8* b = (s8*)&lbl_3_common_bss_32A94;
    s16 idx;
    s16 fo;
    if (b[0x25] == -1) {
        return;
    }
    if (b[0x25] == 0 && (idx = g_Strikes.runnerIndexForEachOutThisPitch[0]) >= 0) {
        if (g_Runners[idx].forceOutCd == 2) {
            b[0x25] = 1;
        } else {
            b[0x25] = -1;
        }
    }
    if (b[0x25] == 1 && (idx = g_Strikes.runnerIndexForEachOutThisPitch[1]) >= 0) {
        fo = g_Runners[idx].forceOutCd;
        if (fo == 2) {
            b[0x25] = 2;
            return;
        }
        if (fo == -1) {
            b[0x25] = 3;
            return;
        }
        b[0x25] = -1;
    }
}

// fn_3_79DD4, size:0x120
// Marks the fielding team's current pitcher as in a save situation.
void fn_3_79DD4(void) {
    s32 onBase;
    s32 pitcher;
    s32 i;
    s32 team;
    s32 lead;
    s8* save;

    s16 (*runs)[19] = g_Scores.runs;
    lead = runs[team = g_GameLogic.awayTeamBattingInd_battingTeam][0] - runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0];
    save = &g_Scores._B7[team];
    *save = -1;
    if (lead <= 0) {
        return;
    }
    if (g_Scores.inning + 2 >= g_Scores._AA && (g_Scores.inning + 2 != g_Scores._AA || g_Strikes.outs != 0) &&
        (lead > 3 || (g_Scores.inning >= g_Scores._AA && (g_Scores.inning < g_Scores._AA || g_Strikes.outs != 0)))) {
        onBase = 0;
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
                onBase++;
            }
        }
        if (lead > onBase + 2) {
            return;
        }
    }
    pitcher = g_GameLogic.battingOrderAndPositionMapping[team][0][0];
    *save = pitcher;
    lbl_3_common_bss_32A38[g_GameLogic.teamFielding][pitcher]._1 = 1;
}

// fn_3_7AB34, size:0x44
void fn_3_7AB34(void) {
    u8* r = lbl_803535C8 + *(s32*)((u8*)&g_GameLogic + 0x8) * 0x10E + ((s32*)((u8*)&g_GameLogic + *(s32*)((u8*)&g_GameLogic + 0x10) * 0x50))[0xF] * 0x1E;
    *(u16*)(r + 0xE) = *(u16*)(r + 0xE) + 1;
}

// fn_3_7AD68, size:0x140
// NONMATCHING 89%: original walks the batting-order rows with a pointer and uses lbzu for the stat bytes
#if NONMATCHING
void fn_3_7AD68(void) {
    s32 i;
    s32 t;
    s32 f;

    t = g_GameLogic.awayTeamBattingInd_battingTeam;
    f = g_GameLogic.teamFielding;
    if (lbl_3_common_bss_32A38[f][g_GameLogic.battingOrderAndPositionMapping[t][0][0]]._2 < 0) {
        lbl_3_common_bss_32A38[f][g_GameLogic.battingOrderAndPositionMapping[t][0][0]]._2 = 0;
    } else {
        lbl_3_common_bss_32A38[f][g_GameLogic.battingOrderAndPositionMapping[t][0][0]]._4 = 0;
    }
    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[t][i][1] > 0 &&
            lbl_3_common_bss_32A38[f][g_GameLogic.battingOrderAndPositionMapping[t][i][0]]._2 == 0 &&
            g_GameLogic.battingOrderAndPositionMapping[t][i][1] !=
                lbl_3_common_bss_32A38[f][g_GameLogic.battingOrderAndPositionMapping[t][i][0]]._3) {
            lbl_3_common_bss_32A38[f][g_GameLogic.battingOrderAndPositionMapping[t][i][0]]._3 =
                g_GameLogic.battingOrderAndPositionMapping[t][i][1];
        }
    }
}
#endif

// fn_3_7AEA8, size:0x40
s32 fn_3_7AEA8(void) {
    return g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + (((s16*)((u8*)&lbl_3_common_bss_32A94 + 0x44))[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1) * 9 - 1;
}

// fn_3_7AEE8, size:0x4
void fn_3_7AEE8(void) {
    return;
}

// fn_3_7AEEC, size:0x7C
// Snapshot of which bases are occupied at the start of an at-bat.
void fn_3_7AEEC(void) {
    s32 i;

    lbl_3_common_bss_32A94._22 = -1;
    lbl_3_common_bss_32A94.baseOccupied[0] = 0;
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != 0) {
            lbl_3_common_bss_32A94.baseOccupied[i] = 1;
        } else {
            lbl_3_common_bss_32A94.baseOccupied[i] = 0;
        }
    }
}

// fn_3_7AF68, size:0x7C
void fn_3_7AF68(void) {
    s32 i;

    lbl_3_common_bss_32A94._22 = -1;
    lbl_3_common_bss_32A94.baseOccupied[0] = 0;
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != 0) {
            lbl_3_common_bss_32A94.baseOccupied[i] = 1;
        } else {
            lbl_3_common_bss_32A94.baseOccupied[i] = 0;
        }
    }
}

// fn_3_7BB74, size:0x4C
u8* fn_3_7BB74(void) {
    return lbl_803537E4 + *(s32*)((u8*)&g_GameLogic + 4) * 0x156 + ((s32*)((u8*)&g_GameLogic + *(s32*)((u8*)&g_GameLogic + 0xC) * 0x50 + ((s32*)((u8*)&g_GameLogic + *(s32*)((u8*)&g_GameLogic + 0xC) * 4))[0xDC/4] * 8))[0xF] * 0x26;
}

// fn_3_7BBC0, size:0x38
u8* fn_3_7BBC0(void) {
    return lbl_803535C8 + *(s32*)((u8*)&g_GameLogic + 0x8) * 0x10E + ((s32*)((u8*)&g_GameLogic + *(s32*)((u8*)&g_GameLogic + 0x10) * 0x50))[0xF] * 0x1E;
}

// fn_3_7BBF8, size:0x14
void fn_3_7BBF8(void) {
    ((u8*)&g_Stats)[0x39] = 1;
}

// fn_3_7BC0C, size:0x14
void fn_3_7BC0C(void) {
    ((u8*)&g_Stats)[0x39] = 1;
}

// fn_3_7C190, size:0x4
void fn_3_7C190(void) {
    return;
}

// fn_3_7C194, size:0x68
s32 fn_3_7C194(void) {
    u8* st = (u8*)&g_Stats;
    s32 f = *(s32*)(st + 0x24);
    if (f < 0x5A) {
        return 0;
    }
    if (f > *(s16*)(st + 0x28) - 0x3C) {
        return 0;
    }
    return fn_3_6C938(1, 0x1100) != 0;
}
