#include "game/auto_00_000759BC_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1838.h"

extern LineScore lbl_80353A90;
extern BattingRecord lbl_803537E4[2][9];
extern PitchingRecord lbl_803535C8[2][9];
extern PitcherGameStat lbl_3_common_bss_32A38[2][9];
extern s8 lbl_3_common_bss_32888[2][100];
extern ScoresView g_Scores;
extern RunningLogicView g_RunningLogic;
extern FielderView g_Fielders[];
extern Bss37400View lbl_3_common_bss_37400;
extern Bss8034E9A0View lbl_8034E9A0;
extern MvpWeights lbl_3_data_60F8;
extern u8 lbl_80354768[];
extern u8 lbl_800E8558[];
extern void fn_3_161588(int, s16);
extern void fn_3_162D54(void);

// fn_3_76D08 updates its counters in place (no address temp).
#define STAT_INC_U8_FIELD(x) ((x) < 0xFE ? ((x) = (x) + 1) : ((x) = 0xFF))
#define STAT_INC_U16_FIELD(x) ((x) < 0xFFFE ? ((x) = (x) + 1) : ((x) = 0xFFFF))

// .text:0x000759BC size:0x7B8 mapped:0x806B4A50
void fn_3_759BC(void) {
    return;
}

// .text:0x00076174 size:0x3E4 mapped:0x806B5208
// Picks the winning pitcher.
// NONMATCHING 82%: register allocation and reload order of g_Scores bytes differ
#if NONMATCHING
void fn_3_76174(void) {
    s32 r = g_Scores.result;
    s32 recTeam = r ^ g_GameLogic.homeTeamInd;
    PitchingRecord* p = lbl_803535C8[recTeam];
    PitcherGameStat* g;
    s8 cur;
    s8 starter;
    s32 i;
    s32 bestIdx;
    s32 best;
    s32 v;
    s32 d;

    if (g_Scores._BB[r] == 1) {
        lbl_80353A90.winningPitcher = g_Scores._AF[r];
        return;
    }
    if (g_Scores.runs[1][g_Scores.inning] > 0 && g_Scores.result == 1) {
        lbl_80353A90.winningPitcher = g_Scores._B1[r];
        return;
    }
    if (g_Scores.inning < 5) {
        lbl_80353A90.winningPitcher = g_Scores._B1[r];
        return;
    }
    cur = g_Scores._B3[r];
    if (g_Scores._B9[r] == 1) {
        if (g_Scores.inning == 5) {
            if (p[cur].outsPitched >= 12) {
                lbl_80353A90.winningPitcher = g_Scores._AF[r];
                return;
            }
        } else if (p[cur].outsPitched >= 15) {
            lbl_80353A90.winningPitcher = g_Scores._AF[r];
            return;
        }
        best = 0;
        bestIdx = -1;
        for (i = 0; i < 9; i++) {
            if (p[i].battersFaced != 0 && cur != i) {
                if (bestIdx == -1) {
                    best = p[i].outsPitched;
                    bestIdx = i;
                } else {
                    v = p[i].outsPitched;
                    d = v - (u8)best;
                    if (d >= 3) {
                        best = v;
                        bestIdx = i;
                    } else if (d > -3) {
                        if (p[i]._04 < p[bestIdx]._04) {
                            bestIdx = i;
                        } else if (p[i]._04 == p[bestIdx]._04) {
                            if (p[i].battersFaced - v < p[bestIdx].battersFaced - p[bestIdx].outsPitched) {
                                bestIdx = i;
                            } else if (p[i].battersFaced - v == p[bestIdx].battersFaced - p[bestIdx].outsPitched) {
                                if (v > (u8)best) {
                                    bestIdx = i;
                                } else if ((u8)best == v && p[i]._0E < p[bestIdx]._0E) {
                                    bestIdx = i;
                                }
                            }
                        }
                        if (v > (u8)best) {
                            best = v;
                        }
                    }
                }
            }
        }
        lbl_80353A90.winningPitcher = lbl_803537E4[recTeam][bestIdx].rosterSlot;
        return;
    }

    best = 0;
    bestIdx = -1;
    if (g_Scores._BB[r] == 2) {
        lbl_80353A90.winningPitcher = cur;
        return;
    }
    if (cur == -1 || cur == g_Scores._AF[r]) {
        starter = g_Scores._AF[r];
        g = lbl_3_common_bss_32A38[g_Scores.result];
        for (i = 0; i < 9; i++) {
            if (starter != i && cur != i) {
                if (bestIdx == -1) {
                    if (g[i]._0 != 0 && best == 0) {
                        bestIdx = i;
                        best = g[i]._0;
                    }
                } else {
                    v = g[i]._0;
                    if (v > best) {
                        bestIdx = i;
                        best = v;
                    } else if (best == v) {
                        if (p[i]._04 < p[bestIdx]._04) {
                            bestIdx = i;
                        } else if (p[i]._04 == p[bestIdx]._04) {
                            if (p[i].battersFaced < p[bestIdx].battersFaced) {
                                bestIdx = i;
                            } else if (p[i].battersFaced == p[bestIdx].battersFaced && p[i]._0E < p[bestIdx]._0E) {
                                bestIdx = i;
                            }
                        }
                    }
                }
            }
        }
        g_Scores._AF[g_Scores.result] = starter;
    }
    if (bestIdx == -1) {
        lbl_80353A90.winningPitcher = g_Scores._B3[r];
    } else {
        lbl_80353A90.winningPitcher = lbl_803537E4[recTeam][bestIdx].rosterSlot;
    }
    if (lbl_80353A90.winningPitcher == -1) {
        lbl_80353A90.winningPitcher = g_Scores._B1[g_Scores.result];
    }
}
#endif

// .text:0x00076558 size:0x544 mapped:0x806B55EC
// End of game: winner, winning/losing/save pitchers, then the MVP.
// NONMATCHING 83%: original re-indexes lbl_803535C8 per counter (lbzu) instead of a record pointer
#if NONMATCHING
void fn_3_76558(void) {
    PitchingRecord* wp;
    PitchingRecord* lp;
    s32 loser;
    s32 t;
    s32 i;
    s8 save;
    u8 flag;

    if (g_Scores.result == 0) {
        lbl_80353A90.winner = g_GameLogic.homeTeamInd;
    }
    if (g_Scores.result == 1) {
        lbl_80353A90.winner = g_GameLogic.homeTeamInd ^ 1;
    }
    if (g_Scores.result == 2) {
        lbl_80353A90.winner = 2;
    }
    if (g_Scores.result == 0 || g_Scores.result == 1) {
        fn_3_76174();
        wp = &lbl_803535C8[lbl_80353A90.winner][lbl_80353A90.winningPitcher];
        STAT_INC_U8(wp->wins);
        if (g_Scores._BB[g_Scores.result] == 1) {
            STAT_INC_U8(wp->_17);
            if (lbl_80353A90.runs[lbl_80353A90.winner ^ 1][0] == 0) {
                STAT_INC_U8(wp->_18);
                flag = lbl_3_common_bss_32A94._63[g_Scores.result];
                if (flag == 1) {
                    lbl_80353A90._0F7 = 1;
                }
                if (flag == 2) {
                    lbl_80353A90._0F7 = 2;
                }
            }
        }
        if (lbl_80353A90.winningPitcher != g_Scores._AF[g_Scores.result]) {
            STAT_INC_U8(lbl_803535C8[lbl_80353A90.winner][lbl_80353A90.winningPitcher]._16);
        }
        loser = g_Scores.result ^ 1;
        lbl_80353A90.losingPitcher = g_Scores._B5[loser];
        lp = &lbl_803535C8[lbl_80353A90.winner ^ 1][lbl_80353A90.losingPitcher];
        STAT_INC_U8(lp->losses);
        if (g_Scores._BB[loser] == 1) {
            STAT_INC_U8(lp->_17);
        }
        save = g_Scores._B7[g_Scores.result];
        if (save != lbl_80353A90.winningPitcher && save >= 0) {
            lbl_80353A90.savePitcher = save;
            STAT_INC_U8(lbl_803535C8[lbl_80353A90.winner][save].saves);
        }
        loser = g_Scores.result ^ 1;
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                if (t == g_Scores.result) {
                    if (i == lbl_80353A90.winningPitcher) {
                        lbl_3_common_bss_32A38[lbl_80353A90.winner][i]._1 = 0;
                    }
                    if (i == lbl_80353A90.savePitcher) {
                        lbl_3_common_bss_32A38[lbl_80353A90.winner][i]._1 = 0;
                    }
                }
                if (t == loser && i == lbl_80353A90.losingPitcher) {
                    lbl_3_common_bss_32A38[lbl_80353A90.winner ^ 1][i]._1 = 0;
                }
            }
        }
    }
    for (i = 0; i < 9; i++) {
        lbl_803535C8[0][i]._19 += lbl_3_common_bss_32A38[0][i]._1;
        lbl_803535C8[1][i]._19 += lbl_3_common_bss_32A38[1][i]._1;
    }
    lbl_80353A90.innings = g_Scores.inning;
    fn_3_759BC();
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        fn_3_162D54();
    }
}
#endif

// .text:0x00076A9C size:0x1DC mapped:0x806B5B30
// Credits runners who advanced and runners who scored.
void fn_3_76A9C(void) {
    InMemRunnerType* runner;
    BattingRecord* rec;
    s32 i;
    s32 runs;

    for (i = 1, runner = &g_Runners[1]; i < 4; i++, runner++) {
        if ((runner->runnerOnFieldOrOutOrScored == 1 || runner->runnerOnFieldOrOutOrScored == 3) && i != runner->currentBase &&
            (g_FieldingLogic._107 != 3 || runner->furthestBaseForcedToGoToOnWalk != 0) && runner->forceOutCd <= 0) {
            rec = &lbl_803537E4[g_GameLogic.teamBatting][runner->rosterID];
            STAT_INC_U8(rec->_12);
            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400._40 == g_GameLogic.teamBatting) {
                fn_3_161588(10, runner->rosterID);
            }
        }
    }
    runs = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] - g_Scores._A0;
    i = 3;
    runner = &g_Runners[3];
    do {
        if (runs <= 0) {
            break;
        }
        if (runner->runnerOnFieldOrOutOrScored == 3) {
            rec = &lbl_803537E4[g_GameLogic.teamBatting][runner->rosterID];
            STAT_INC_U8(rec->runs);
            runs--;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.teamBatting == lbl_3_common_bss_37400._40) {
                fn_3_161588(11, runner->rosterID);
            }
        }
        runner--;
    } while (--i >= 0);
}

// .text:0x00076C78 size:0x90 mapped:0x806B5D0C
// Logs a home run by the current batter.
void fn_3_76C78(void) {
    s32 i;

    for (i = 0; i < 50; i++) {
        if (lbl_80353A90._0A0[i] == -1) {
            if (g_GameLogic.teamBatting == 0) {
                lbl_80353A90._0A0[i] = g_Batter.rosterID;
            } else {
                lbl_80353A90._0A0[i] = (s8)g_Batter.rosterID + 9;
            }
            return;
        }
    }
}

// .text:0x00076D08 size:0xC0C mapped:0x806B5D9C
// Records the result of a plate appearance in the box score and play log.
// NONMATCHING 93%: register allocation; original addresses lbl_8034E9A0+0x4908 directly
#if NONMATCHING
void fn_3_76D08(s32 batterSlot, s32 result, u8 detail, s32 rbi) {
    BattingRecord* bat;
    PitchingRecord* pit;
    PlayLogEntry* log;
    s32 pitcher;
    s32 atBat = 0;
    s32 idx;
    s32 i;
    s32 runs;
    s16 dist;
    InMemRunnerType* runner;
    BattingRecord* rec;
    u8 flag;

    pitcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    bat = &lbl_803537E4[g_GameLogic.teamBatting][batterSlot];
    pit = &lbl_803535C8[g_GameLogic.teamFielding][pitcher];
    STAT_INC_U8_FIELD(bat->plateAppearances);

    idx = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] +
          (lbl_3_common_bss_32A94._44[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1) * 9 - 1;
    if (idx >= 100) {
        log = lbl_8034E9A0.playLog[g_GameLogic.teamBatting];
        for (i = 0; i < 99; i++) {
            lbl_3_common_bss_32888[g_GameLogic.teamBatting][i] = lbl_3_common_bss_32888[g_GameLogic.teamBatting][i + 1];
            log[i].inning = log[i + 1].inning;
            log[i].batter = log[i + 1].batter;
            log[i].batterSlot = log[i + 1].batterSlot;
            log[i].result = log[i + 1].result;
            log[i].detail = log[i + 1].detail;
            log[i].rbi = log[i + 1].rbi;
        }
        idx = 99;
    }
    log = &lbl_8034E9A0.playLog[g_GameLogic.teamBatting][idx];
    log->inning = g_Scores.inning;
    log->batter = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    log->batterSlot = batterSlot;
    log->result = result;
    lbl_3_common_bss_32888[g_GameLogic.teamBatting][idx] = lbl_3_common_bss_32A94._0;
    log->detail = detail;
    log->rbi = rbi;

    if (result == 10) {
        dist = fn_3_9FB8C(g_Ball.landingSpotLocation.x, g_Ball.landingSpotLocation.z);
        if (dist < 0x380) {
            lbl_8034E9A0.playLog[g_GameLogic.teamBatting][idx].detail = 8;
        } else if (dist < 0x480) {
            lbl_8034E9A0.playLog[g_GameLogic.teamBatting][idx].detail = 7;
        } else {
            lbl_8034E9A0.playLog[g_GameLogic.teamBatting][idx].detail = 6;
        }
    }

    switch (result) {
    case 1:
        STAT_INC_U8_FIELD(bat->strikeouts);
        atBat = 1;
        break;
    case 2:
        STAT_INC_U8_FIELD(bat->walks);
        break;
    case 3:
        STAT_INC_U8_FIELD(bat->hitByPitch);
        break;
    case 7:
        STAT_INC_U8_FIELD(bat->singles);
        STAT_INC_U8_FIELD(bat->hits);
        atBat = 1;
        break;
    case 8:
        STAT_INC_U8_FIELD(bat->doubles);
        STAT_INC_U8_FIELD(bat->hits);
        atBat = 1;
        break;
    case 9:
        STAT_INC_U8_FIELD(bat->triples);
        STAT_INC_U8_FIELD(bat->hits);
        atBat = 1;
        break;
    case 10:
        STAT_INC_U8_FIELD(bat->homeRuns);
        STAT_INC_U8_FIELD(bat->hits);
        atBat = 1;
        for (i = 0; i < 50; i++) {
            if (lbl_80353A90._0A0[i] == -1) {
                if (g_GameLogic.teamBatting == 0) {
                    lbl_80353A90._0A0[i] = g_Batter.rosterID;
                } else {
                    lbl_80353A90._0A0[i] = (s8)g_Batter.rosterID + 9;
                }
                break;
            }
        }
        break;
    case 13:
        STAT_INC_U8_FIELD(bat->_0A);
        break;
    case 14:
        STAT_INC_U8_FIELD(bat->_0B);
        break;
    case 15:
        STAT_INC_U8_FIELD(bat->_0C);
        atBat = 1;
        break;
    default:
        atBat = 1;
        break;
    }

    if (bat->atBats < 0xFF - atBat) {
        bat->atBats += atBat;
    } else {
        bat->atBats = 0xFF;
    }
    if (bat->rbi < 0xFF - rbi) {
        bat->rbi += rbi;
    } else {
        bat->rbi = 0xFF;
    }
    if (g_RunningLogic._15 != 0) {
        if (bat->_13 < 0xFF - atBat) {
            bat->_13 += atBat;
        } else {
            bat->_13 = 0xFF;
        }
        if (result >= 7 && result <= 10) {
            STAT_INC_U8_FIELD(bat->_14);
        }
        if (result == 10) {
            STAT_INC_U8_FIELD(bat->_18);
        }
        if (rbi != 0) {
            if (bat->_17 < 0xFF - rbi) {
                bat->_17 += rbi;
            } else {
                bat->_17 = 0xFF;
            }
        }
    }

    runs = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] - g_Scores._A0;
    i = 3;
    runner = &g_Runners[3];
    do {
        if (runs <= 0) {
            break;
        }
        if (runner->runnerOnFieldOrOutOrScored == 3) {
            rec = &lbl_803537E4[g_GameLogic.teamBatting][runner->rosterID];
            STAT_INC_U8_FIELD(rec->runs);
            runs--;
            if (g_d_GameSettings.exhibitionMatchInd == 0 && g_GameLogic.teamBatting == lbl_3_common_bss_37400._40) {
                fn_3_161588(11, runner->rosterID);
            }
        }
        runner--;
    } while (--i >= 0);

    g_Scores._B1[g_GameLogic.awayTeamBattingInd_battingTeam] = pitcher;
    STAT_INC_U16_FIELD(pit->battersFaced);
    if (pit->outsPitched < 0xFF - g_Strikes.outs - g_Strikes.storedOuts) {
        pit->outsPitched += g_Strikes.outs - g_Strikes.storedOuts;
    } else {
        pit->outsPitched = 0xFF;
    }
    if (g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0] >
        g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0]) {
        lbl_3_common_bss_32A38[g_GameLogic.awayTeamBattingInd_battingTeam][pitcher]._0 +=
            g_Strikes.outs - g_Strikes.storedOuts;
    }
    if (result >= 7 && result <= 10) {
        STAT_INC_U16_FIELD(pit->hitsAllowed);
    }
    if (result == 10) {
        STAT_INC_U16_FIELD(pit->homeRunsAllowed);
    }
    if (result == 1) {
        STAT_INC_U8_FIELD(pit->strikeouts);
    }
    if (result == 2) {
        if (g_Strikes._1E >= 0) {
            STAT_INC_U16_FIELD(lbl_803535C8[g_GameLogic.teamFielding][g_Strikes._1E].walks);
        } else {
            STAT_INC_U16_FIELD(pit->walks);
        }
    }
    if (result == 3) {
        STAT_INC_U16_FIELD(pit->hitByPitch);
    }

    flag = lbl_3_common_bss_32A94._63[g_GameLogic.awayTeamBattingInd_battingTeam];
    if (flag != 0) {
        if (lbl_3_common_bss_32A94._4C[g_GameLogic.awayTeamBattingInd_battingTeam] > 1) {
            lbl_3_common_bss_32A94._63[g_GameLogic.awayTeamBattingInd_battingTeam] = 0;
        } else {
            if (flag == 1 && ((u32)(result - 2) <= 1 || result == 11 || result == 12)) {
                lbl_3_common_bss_32A94._63[g_GameLogic.awayTeamBattingInd_battingTeam] = 2;
            }
            if (lbl_3_common_bss_32A94._63[g_GameLogic.awayTeamBattingInd_battingTeam] != 0 &&
                ((u32)(result - 7) <= 3 || g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] > 0 ||
                 lbl_80353A90._0A0[0x20 + g_GameLogic.teamFielding * 0x14] >= 0)) {
                lbl_3_common_bss_32A94._63[g_GameLogic.awayTeamBattingInd_battingTeam] = 0;
            }
        }
    }

    if (g_FieldingLogic._113 == 9) {
        STAT_INC_U8_FIELD(g_Scores._A8[g_GameLogic.awayTeamBattingInd_battingTeam]);
        STAT_INC_U8_FIELD(lbl_803537E4[g_GameLogic.teamFielding][g_Fielders[g_FieldingLogic._EA].rosterID]._15);
    }
    if (g_Ball.fielderWithBallIndexStored >= 0 && g_Ball.fielderWithBallIndexStored <= 8) {
        STAT_INC_U8_FIELD(lbl_803537E4[g_GameLogic.teamFielding][g_Fielders[g_Ball.fielderWithBallIndexStored].rosterID]._16);
    }
    if (g_FieldingLogic._133 == 2 && g_Ball.fielderWithBallIndexStored2 >= 0) {
        STAT_INC_U8_FIELD(lbl_803537E4[g_GameLogic.teamFielding][g_Fielders[g_Ball.fielderWithBallIndexStored2].rosterID]._16);
    }

    lbl_80353A90.runs[g_GameLogic.teamBatting][g_Scores.inning] =
        g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][g_Scores.inning];
    lbl_80353A90.hits[g_GameLogic.teamBatting][g_Scores.inning] =
        g_Scores.hits[g_GameLogic.homeTeamBattingInd_fieldingTeam][g_Scores.inning];
    lbl_80353A90.runs[g_GameLogic.teamBatting][0] = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0];
    lbl_80353A90.hits[g_GameLogic.teamBatting][0] = g_Scores.hits[g_GameLogic.homeTeamBattingInd_fieldingTeam][0];
    lbl_80353A90.errors[g_GameLogic.teamBatting] = g_Scores._A8[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    lbl_80353A90.errors[g_GameLogic.teamFielding] = g_Scores._A8[g_GameLogic.awayTeamBattingInd_battingTeam];
}
#endif
