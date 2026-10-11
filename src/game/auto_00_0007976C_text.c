#include "game/auto_00_0007976C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_000759BC_text.h"
#include "game/rep_12D0.h"

extern ScoresView g_Scores;
extern PitcherGameStat lbl_3_common_bss_32A38[2][9];
extern RosterLogEntry lbl_80353260[2][9];
extern PlayLogEntry lbl_803532A8[2][100];
extern Lbl80354720Entry lbl_80354720[2][9];
extern LineScore lbl_80353A90;
extern FielderView g_Fielders[];
extern RunningLogicView g_RunningLogic;
extern s16 lbl_3_data_5EDC[];
extern void fn_3_6D564(s32 team, s32 rosterIdx, s32 delta);
extern void fn_3_9C794(void);
extern void fn_3_162080(void);

// Saturating counters updated in place (no address temp).
#define STAT_INC_U8_FIELD(x)     \
    if ((x) < 0xFE) {            \
        (x)++;                   \
    } else {                     \
        (x) = 0xFF;              \
    }
#define STAT_INC_U16_FIELD(x)    \
    if ((x) < 0xFFFE) {          \
        (x)++;                   \
    } else {                     \
        (x) = 0xFFFF;            \
    }

extern PitchingRecord lbl_803535C8[2][9];
extern BattingRecord lbl_803537E4[2][9];
extern s32 fn_3_6C938(s32, s32);

#pragma dont_inline on

// fn_3_7976C, size:0x294
// Decides whether the batter is credited (1), not credited (0) or undecided (-1).
void fn_3_7976C(void) {
    s32 force = 0;
    s32 result = -1;
    s32 i;
    s32 j;

    if (g_FieldingLogic._107 != 0) {
        lbl_3_common_bss_32A94._22 = 0;
        return;
    }
    if (g_Ball.ballInitialHitDoneInd != 0 && g_Ball.AtBat_ContactResult != 0 && g_Ball.AtBat_ContactResult != -1) {
        if (g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._108 == 2) {
            result = 0;
        } else if (g_Ball.deadBallReason == 1 || g_Ball.deadBallReason == 3) {
            result = 1;
        } else {
            for (i = 0; i < 4; i++) {
                if (g_Runners[i].forceOutCd == 1) {
                    force = 1;
                }
                if (g_Runners[i].forceOutCd == 2) {
                    force = 2;
                }
            }
            if (force == 2) {
                result = 0;
            } else if (force == 0) {
                if (lbl_3_common_bss_32A94.baseOccupied[0] == 2 && g_Runners[0].runnerOnFieldOrOutOrScored == 1) {
                    result = 1;
                }
                if (g_Ball.fielderWithBallIndexStored2 >= 0 && g_Ball.fielderWithBallIndexStored2 <= 5 &&
                    (s8)g_Ball.ballZoneWhenCaught <= 1 && result == 1) {
                    for (j = 1; j < 4; j++) {
                        if (g_Runners[j].runnerOnFieldOrOutOrScored == 2) {
                            result = 0;
                            goto done;
                        }
                    }
                    // Undecided while a runner is still short of a base.
                    for (i = 1; i < 4; i++) {
                        if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].baseStandingOn < 0 &&
                            g_Runners[i].runnerOnFieldOrOutOrScored != 3 &&
                            g_Runners[i].currentBase <= g_Runners[i].startingBase_baseAchieved) {
                            break;
                        }
                    }
                    if (i < 4) {
                        result = -1;
                    }
                }
            }
        }
    }
done:
    lbl_3_common_bss_32A94._22 = result;
}

// fn_3_79A00, size:0xCC
void fn_3_79A00(void) {
    s16 idx;
    s16 fo;
    if (lbl_3_common_bss_32A94._25 == -1) {
        return;
    }
    if (lbl_3_common_bss_32A94._25 == 0 && (idx = g_Strikes.runnerIndexForEachOutThisPitch[0]) >= 0) {
        if (g_Runners[idx].forceOutCd == 2) {
            lbl_3_common_bss_32A94._25 = 1;
        } else {
            lbl_3_common_bss_32A94._25 = -1;
        }
    }
    if (lbl_3_common_bss_32A94._25 == 1 && (idx = g_Strikes.runnerIndexForEachOutThisPitch[1]) >= 0) {
        fo = g_Runners[idx].forceOutCd;
        if (fo == 2) {
            lbl_3_common_bss_32A94._25 = 2;
            return;
        }
        if (fo == -1) {
            lbl_3_common_bss_32A94._25 = 3;
            return;
        }
        lbl_3_common_bss_32A94._25 = -1;
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

// fn_3_79EF4, size:0x260
// Tracks lead changes for the winning/losing pitcher decision.
void fn_3_79EF4(void) {
    s32 d;
    s32 i;
    s32 n;
    u8 v;
    s16 (*runs)[19] = g_Scores.runs;

    d = runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] - runs[g_GameLogic.awayTeamBattingInd_battingTeam][0];
    if (d > 0 && d <= g_Scores._9C) {
        g_Scores._AE = g_Scores.inning;
    }
    if (d >= 0) {
        g_Scores._B5[g_GameLogic.homeTeamBattingInd_fieldingTeam] = -1;
    }
    if (d <= g_Scores._9C && d > 0) {
        if (g_Scores._9C == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    g_Scores._B5[g_GameLogic.awayTeamBattingInd_battingTeam] = g_Runners[i].pitcherWhoLetRunnerOnBase;
                    break;
                }
            }
        } else {
            n = g_Scores._9C;
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    if (d == n) {
                        g_Scores._B5[g_GameLogic.awayTeamBattingInd_battingTeam] = g_Runners[i].pitcherWhoLetRunnerOnBase;
                        break;
                    }
                    n--;
                }
            }
        }
    }
    if (d >= 0) {
        g_Scores._B3[g_GameLogic.awayTeamBattingInd_battingTeam] = -1;
        if (g_Scores._B9[g_GameLogic.awayTeamBattingInd_battingTeam] == 1) {
            if (g_Scores._BB[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 1) {
                g_Scores._B9[g_GameLogic.awayTeamBattingInd_battingTeam] = 0;
            } else {
                g_Scores._B9[g_GameLogic.awayTeamBattingInd_battingTeam] = 2;
            }
        }
    }
    if (d <= g_Scores._9C && d > 0) {
        g_Scores._B3[g_GameLogic.homeTeamBattingInd_fieldingTeam] = g_Scores._B1[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        g_Scores._BD[g_GameLogic.homeTeamBattingInd_fieldingTeam] = g_Scores._BB[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        v = g_Scores._B9[g_GameLogic.homeTeamBattingInd_fieldingTeam];
        if (v == 0) {
            if (g_Scores._BB[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 1) {
                g_Scores._B9[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
            } else {
                g_Scores._B9[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 2;
            }
        } else if (v == 1 && g_Scores._BB[g_GameLogic.homeTeamBattingInd_fieldingTeam] > 1) {
            g_Scores._B9[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 2;
        }
    }
    if (d >= 0) {
        lbl_3_common_bss_32A38[g_GameLogic.teamFielding]
                              [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                                  ._1 = 0;
    }
}

// fn_3_79ACC, size:0x308
// Per-frame bookkeeping while a play is live.
void fn_3_79ACC(void) {
    s32 i;
    s16 idx;
    s16 fo;

    if (lbl_3_common_bss_32A94._22 == -1) {
        fn_3_7976C();
    } else if (lbl_3_common_bss_32A94._22 >= 1) {
        fn_3_795A8();
    }
    if (lbl_3_common_bss_32A94._22 == 1 && lbl_3_common_bss_32A94._20 == 0 &&
        g_Strikes.allForcedRunnersReachedTheirBaseInd == 0 &&
        (g_FieldingLogic._113 == 0 || g_Ball.lineDriveThroughPitcherInd != 0 || (s8)g_FieldingLogic._121 >= 0)) {
        g_Strikes.allForcedRunnersReachedTheirBaseInd = 1;
    }
    if (g_Ball.maybeBuntInd != 0) {
        fn_3_79414();
    } else if (g_Strikes.storedOuts != 2 && g_Strikes.outs < 3) {
        if (lbl_3_common_bss_32A94._24 == 0) {
            if ((g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._113 == 1) &&
                g_Ball.landingSpotZoneAwayFromHome >= 2) {
                lbl_3_common_bss_32A94._24 = 2;
            }
        } else if (lbl_3_common_bss_32A94._24 == 2 && g_Ball.AtBat_ContactResult == 3) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    lbl_3_common_bss_32A94._24 = 1;
                }
            }
        }
    }

    // same as fn_3_79A00
    if (lbl_3_common_bss_32A94._25 != -1) {
        if (lbl_3_common_bss_32A94._25 == 0 && (idx = g_Strikes.runnerIndexForEachOutThisPitch[0]) >= 0) {
            if (g_Runners[idx].forceOutCd == 2) {
                lbl_3_common_bss_32A94._25 = 1;
            } else {
                lbl_3_common_bss_32A94._25 = -1;
            }
        }
        if (lbl_3_common_bss_32A94._25 == 1 && (idx = g_Strikes.runnerIndexForEachOutThisPitch[1]) >= 0) {
            fo = g_Runners[idx].forceOutCd;
            if (fo == 2) {
                lbl_3_common_bss_32A94._25 = 2;
            } else if (fo == -1) {
                lbl_3_common_bss_32A94._25 = 3;
            } else {
                lbl_3_common_bss_32A94._25 = -1;
            }
        }
    }

    fn_3_78AC4();
    fn_3_78730();
    if ((g_Batter.captainStarSwingActivated != 0 || g_Batter.nonCaptainStarSwingActivated != 0 ||
         g_Batter.moonShotInd != 0) &&
        g_Ball.framesSinceHit == 1) {
        if (lbl_803537E4[g_GameLogic.teamBatting][g_Batter.rosterID].starSwingHits < 0xFE) {
            lbl_803537E4[g_GameLogic.teamBatting][g_Batter.rosterID].starSwingHits++;
        } else {
            lbl_803537E4[g_GameLogic.teamBatting][g_Batter.rosterID].starSwingHits = 0xFF;
        }
    }
}

// fn_3_7A154, size:0x9E0
// End of a pitch: appearance flags, pitcher stats, runs charged to pitchers.
// NONMATCHING 91%: register allocation/scheduling
#if NONMATCHING
void fn_3_7A154(s32 inPlay) {
    s32 charge = 0;
    s32 lead;
    s32 d;
    s32 i;
    s32 n;
    s32 any;
    s32 scored[4];
    s32 pitch;
    PitchingRecord* pit;
    PitchingRecord* team;
    InMemRunnerType* runner;

    pit = &lbl_803535C8[g_GameLogic.teamFielding]
                       [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]];
    if (g_Stats.replayInd != 0) {
        return;
    }
    for (i = 0; i < 9; i++) {
        lbl_803537E4[g_GameLogic.teamFielding][g_Fielders[i].rosterID].played = 1;
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].rosterID >= 0) {
            lbl_803537E4[g_GameLogic.teamBatting][g_Runners[i].rosterID].played = 1;
        }
    }
    lbl_803535C8[g_GameLogic.teamFielding]
                [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                    .played = 1;
    fn_3_7AB78(0);
    if (pit->topPitchSpeed < g_Pitcher.pitchSpeed) {
        pit->topPitchSpeed = g_Pitcher.pitchSpeed;
    }
    if (g_FieldingLogic._107 == 0) {
        if (g_Pitcher.starPitchType != 0 || g_Pitcher.nonCaptainStarPitchTriggeredType != 0) {
            fn_3_6D564(g_GameLogic.teamFielding, g_Pitcher.rosterID, lbl_3_data_5EDC[1]);
            STAT_INC_U8_FIELD(lbl_803535C8[g_GameLogic.teamFielding]
                                    [g_GameLogic.battingOrderAndPositionMapping
                                         [g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                                        .starPitches);
        }
        if ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_RunningLogic._12 >= 4) {
            fn_3_6D564(g_GameLogic.teamFielding, g_Pitcher.rosterID, lbl_3_data_5EDC[2]);
        } else if (g_Scores._C2 != 0) {
            fn_3_6D564(g_GameLogic.teamFielding, g_Pitcher.rosterID, lbl_3_data_5EDC[2] * g_Scores._C2);
        }
    }
    for (i = 1; i < 10; i++) {
        RosterLogEntry* e =
            &lbl_80353260[g_GameLogic.teamFielding]
                                   [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0]];
        if (e->position == 0xA) {
            e->position = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1];
        }
    }

    lead = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] -
           g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0];
    d = lead - (g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][g_Scores.inning] - g_Scores._9E);
    if (lead >= 0 && d <= 0) {
        charge = 1;
    }
    if (inPlay == 0) {
        // walk / hit-by-pitch with the bases loaded
        if ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_RunningLogic._12 >= 4 &&
            g_Runners[3].pitcherWhoLetRunnerOnBase >= 0) {
            team = lbl_803535C8[g_GameLogic.teamFielding];
            STAT_INC_U16_FIELD(team[g_Runners[3].pitcherWhoLetRunnerOnBase]._02);
            if (g_Runners[3].runnerDidntReachOnError != 0) {
                STAT_INC_U16_FIELD(team[g_Runners[3].pitcherWhoLetRunnerOnBase]._04);
            }
            if (charge != 0 && d + 1 >= 0) {
                lbl_3_common_bss_32A38[g_GameLogic.teamFielding][g_Runners[3].pitcherWhoLetRunnerOnBase]._1 = 0;
            }
        }
    } else {
        n = g_Scores._9C;
        for (i = 0; i < 4; i++) {
            scored[i] = 0;
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 3 || g_Runners[i].scoredOnGRD != 0) {
                if (n <= 0) {
                    scored[i] = 1;
                } else {
                    n--;
                }
            }
        }
        if (g_Strikes.storedOuts == 2) {
            any = 0;
            if (g_Ball.AtBat_ContactResult == 3) {
                any = 1;
            } else {
                for (i = 0; i < 4; i++) {
                    if (g_Runners[i].forceOutCd == 2) {
                        any = 1;
                    }
                }
            }
            if (any != 0) {
                scored[0] = scored[1] = scored[2] = scored[3] = 0;
            }
        }
        if (g_Strikes.storedOuts == 1) {
            n = 2;
            if (g_Runners[0].forceOutCd == 2) {
                n = 1;
            }
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].forceOutCd == 2) {
                    n--;
                }
            }
            if (n <= 0) {
                scored[0] = scored[1] = scored[2] = scored[3] = 0;
            }
        }
        team = lbl_803535C8[g_GameLogic.teamFielding];
        for (i = 3, runner = &g_Runners[3]; i >= 0; i--, runner--) {
            if (scored[i] != 0 && runner->pitcherWhoLetRunnerOnBase >= 0) {
                STAT_INC_U16_FIELD(team[runner->pitcherWhoLetRunnerOnBase]._02);
                if (runner->runnerDidntReachOnError != 0) {
                    if (g_FieldingLogic._113 == 9) {
                        if (i == 3 && g_FieldingLogic._132 == 1 && g_Ball.landingSpotZoneAwayFromHome == 4) {
                            STAT_INC_U16_FIELD(team[runner->pitcherWhoLetRunnerOnBase]._04);
                        }
                    } else {
                        STAT_INC_U16_FIELD(team[runner->pitcherWhoLetRunnerOnBase]._04);
                    }
                }
                if (charge != 0 && ++d >= 0) {
                    lbl_3_common_bss_32A38[g_GameLogic.teamFielding][runner->pitcherWhoLetRunnerOnBase]._1 = 0;
                }
            }
        }
    }

    if (lbl_3_common_bss_32A94._50[g_GameLogic.awayTeamBattingInd_battingTeam].pitcher !=
        g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]) {
        lbl_3_common_bss_32A94._50[g_GameLogic.awayTeamBattingInd_battingTeam].pitcher =
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
        lbl_3_common_bss_32A94._50[g_GameLogic.awayTeamBattingInd_battingTeam]._2 = 0;
        lbl_3_common_bss_32A94._34 = 0;
    }
    pitch = g_Strikes.balls + g_Strikes.strikes * 16;
    for (i = 0; i < 7; i++) {
        if (lbl_3_common_bss_32A94.pitchCountLog[i] == 0) {
            if (i <= 0 || lbl_3_common_bss_32A94.pitchCountLog[i - 1] != pitch) {
                lbl_3_common_bss_32A94.pitchCountLog[i] = pitch;
            }
            break;
        }
    }
    if (lbl_3_common_bss_32A94._34 < 0x7FFE) {
        lbl_3_common_bss_32A94._34++;
    } else {
        lbl_3_common_bss_32A94._34 = 0x7FFF;
    }
    fn_3_9C794();
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        fn_3_162080();
    }
}
#endif

// fn_3_7AB34, size:0x44
void fn_3_7AB34(void) {
    PitchingRecord* rec =
        &lbl_803535C8[g_GameLogic.teamFielding]
                     [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]];
    rec->_0E = rec->_0E + 1;
}

// fn_3_7AB78, size:0x1F0
// Logs the fielding team's current pitcher in the line score.
// NONMATCHING 98%: registers only (batting team index kept in r4 vs r0)
#if NONMATCHING
void fn_3_7AB78(s32 newPitcher) {
    s32 i;
    s32 f;
    s32 pitcher;
    s32 slot; // NOTE: left unset if no batting-order entry plays position 1 (as in the original)

    if (newPitcher != 0) {
        if (g_Scores._BB[g_GameLogic.awayTeamBattingInd_battingTeam] < 0xFE) {
            g_Scores._BB[g_GameLogic.awayTeamBattingInd_battingTeam]++;
        } else {
            g_Scores._BB[g_GameLogic.awayTeamBattingInd_battingTeam] = 0xFF;
        }
    }
    pitcher = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][1] == 1) {
            slot = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][i][0];
            break;
        }
    }
    f = g_GameLogic.teamFielding;
    if (lbl_80353A90.pitcherLog[f][0].pitcher == -1) {
        lbl_80353A90.pitcherLog[f][0].pitcher = pitcher;
        lbl_80353A90.pitcherLog[f][0].inning = 1;
        lbl_80353A90._0E6[f][0] = slot;
        return;
    }
    for (i = 1; i < 10; i++) {
        if (lbl_80353A90.pitcherLog[f][i].pitcher == -1) {
            if (lbl_80353A90.pitcherLog[f][i - 1].pitcher != pitcher) {
                lbl_80353A90.pitcherLog[f][i].pitcher = pitcher;
                lbl_80353A90.pitcherLog[f][i].inning = g_Scores.inning;
                if (lbl_3_common_bss_32A94._4C[g_GameLogic.awayTeamBattingInd_battingTeam] < 0x7FFE) {
                    lbl_3_common_bss_32A94._4C[g_GameLogic.awayTeamBattingInd_battingTeam]++;
                } else {
                    lbl_3_common_bss_32A94._4C[g_GameLogic.awayTeamBattingInd_battingTeam] = 0x7FFF;
                }
            }
            break;
        }
    }
    if (newPitcher == 0) {
        for (i = 1; i < 5; i++) {
            if (lbl_80353A90._0E6[f][i] == -1) {
                if (lbl_80353A90._0E6[f][i - 1] != slot) {
                    lbl_80353A90._0E6[f][i] = slot;
                }
                return;
            }
        }
    }
}
#endif

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
    return g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + (lbl_3_common_bss_32A94._44[g_GameLogic.homeTeamBattingInd_fieldingTeam] - 1) * 9 - 1;
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

// fn_3_7AFE4, size:0x14C
// Start of a new at-bat.
// NONMATCHING 97%: registers only; original inlines fn_3_7AEEC here (blocked by #pragma dont_inline on)
#if NONMATCHING
void fn_3_7AFE4(void) {
    s32 i;
    u8 team = g_Scores._AD;
    s32 batter = g_GameLogic.currentBatterPerTeam[team];

    lbl_3_common_bss_32A94._22 = -1;
    lbl_3_common_bss_32A94._23 = 0;
    lbl_3_common_bss_32A94._24 = 0;
    lbl_3_common_bss_32A94._20 = -1;
    lbl_3_common_bss_32A94._25 = 0;
    lbl_3_common_bss_32A94._26 = 0;
    if (lbl_3_common_bss_32A94._61 < 0xFE) {
        lbl_3_common_bss_32A94._61++;
    } else {
        lbl_3_common_bss_32A94._61 = 0xFF;
    }
    if (batter == 1) {
        if (lbl_3_common_bss_32A94._61 > 1 || g_Scores.inning != 1) {
            lbl_3_common_bss_32A94._44[team]++;
        }
        // same as fn_3_7AEEC
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
    for (i = 0; i < 7; i++) {
        lbl_3_common_bss_32A94.pitchCountLog[i] = 0;
    }
}
#endif

// fn_3_7B130, size:0x1D8
// Start of a half-inning.
void fn_3_7B130(void) {
    s32 i;
    s32 t;

    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            if ((s32)lbl_80354720[t][i]._3 == 1) {
                lbl_80353260[t][i].inning = g_Scores.inning;
            }
        }
    }
    lbl_3_common_bss_32A94._36[0] = 0;
    lbl_3_common_bss_32A94._36[1] = 0;
    lbl_3_common_bss_32A94._36[2] = 0;
    lbl_3_common_bss_32A94._36[3] = 0;
    lbl_3_common_bss_32A94._36[4] = 0;
    lbl_3_common_bss_32A94._32 = -1;
    lbl_3_common_bss_32A94._34 = 0;
    lbl_3_common_bss_32A94._3C = 0;
    lbl_3_common_bss_32A94._60 = 1;
    lbl_3_common_bss_32A94._62 = lbl_3_common_bss_32A94._61;
    lbl_3_common_bss_32A94._61 = 0;
    lbl_3_common_bss_32A94._3E[0] = 0;
    lbl_3_common_bss_32A94._3E[1] = 0;
    lbl_3_common_bss_32A94._3E[2] = 0;
    lbl_3_common_bss_32A94._3E[3] = 0;
    lbl_3_common_bss_32A94._3E[4] = 0;
    for (i = 0; i < 9; i++) {
        lbl_3_common_bss_32A38[g_GameLogic.teamFielding][i]._2 = -1;
        lbl_3_common_bss_32A38[g_GameLogic.teamFielding][i]._3 = -1;
        lbl_3_common_bss_32A38[g_GameLogic.teamFielding][i]._4 = -1;
    }
    lbl_3_common_bss_32A38[g_GameLogic.teamFielding]
                          [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]]
                              ._2 = 0;
}


// fn_3_7BB74, size:0x4C
BattingRecord* fn_3_7BB74(void) {
    return &lbl_803537E4[g_GameLogic.teamBatting]
                        [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam]
                                                                   [g_GameLogic.currentBatterPerTeam
                                                                        [g_GameLogic.homeTeamBattingInd_fieldingTeam]][0]];
}

// fn_3_7BBC0, size:0x38
PitchingRecord* fn_3_7BBC0(void) {
    return &lbl_803535C8[g_GameLogic.teamFielding]
                        [g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]];
}

// fn_3_7BBF8, size:0x14
void fn_3_7BBF8(void) {
    g_Stats._39 = 1;
}

// fn_3_7BC0C, size:0x14
void fn_3_7BC0C(void) {
    g_Stats._39 = 1;
}

// fn_3_7BC20, size:0x570
// Picks the replay camera/commentary kind for the play that just ended.
// NONMATCHING 94%: register allocation; original keeps different global bases live
#if NONMATCHING
void fn_3_7BC20(void) {
    GameControlsStruct* gl = &g_GameLogic;
    InMemBallType* ball = &g_Ball;
    inMemStrikes* strikes = &g_Strikes;
    s32 kind = 0;
    s32 alt = 0;
    s32 diff;
    s32 n;
    s16 t;

    if (gl->freeFieldingPracticeInd != 0) {
        return;
    }
    if (ball->deadBallReason == 1) {
        kind = 2;
        if (lbl_3_common_bss_32A94._8A != 0) {
            kind = 9;
        }
        if (g_Ball.homeRunClassification == 1) {
            kind = 13;
        }
    } else if (g_Scores._C2 != 0) {
        if (lbl_3_common_bss_32A94._2 >= 6 && lbl_3_common_bss_32A94._2 <= 10) {
            kind = 3;
            if (kind == 3 && strikes->outs != 3 && g_Runners[0].runnerOnFieldOrOutOrScored != 2 &&
                g_Runners[0].runnerOnFieldOrOutOrScored != 3) {
                kind = 4;
            }
            if (ball->fielderWithBallIndexStored2 != 6 && ball->fielderWithBallIndexStored2 != 7 &&
                ball->fielderWithBallIndexStored2 != 8) {
                alt = kind;
                kind = 1;
            }
            if (g_pCamera->_AC6 == 3) {
                alt = kind;
                kind = 1;
            }
        }
        if (lbl_3_common_bss_32A94._2 == 0x11) {
            if (g_Scores._A6 <= 1) {
                kind = 5;
            } else if (g_Scores._A6 <= 1 && g_Scores._AC >= 3) {
                kind = 5;
            }
            if (lbl_3_common_bss_32A94._8A != 0) {
                kind = 11;
            }
        }
        diff = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] -
               g_Scores.runs[g_GameLogic.awayTeamBattingInd_battingTeam][0];
        if (diff > 4 || diff < -4) {
            kind = 0;
        }
    } else {
        if (g_pCamera->_A50 >= 2) {
            if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                t = g_pCamera->_A98;
                if (t > 0 && (lbl_3_common_bss_32A94._2 == 0x12 || lbl_3_common_bss_32A94._2 == 0x13 ||
                              lbl_3_common_bss_32A94._2 == 0x1A)) {
                    kind = 7;
                } else if (t > 0 && lbl_3_common_bss_32A94._2 >= 0x14 && lbl_3_common_bss_32A94._2 <= 0x1B) {
                    kind = 8;
                }
            } else {
                n = 0;
                if (g_Runners[1].rosterID != -1) {
                    n = 1;
                }
                if (g_Runners[2].rosterID != -1) {
                    n++;
                }
                if (g_Runners[3].rosterID != -1) {
                    n++;
                }
                if (g_Scores._A6 <= 4 && n == 3) {
                    t = g_pCamera->_A98;
                    if (t > 0 && (lbl_3_common_bss_32A94._2 == 0x12 || lbl_3_common_bss_32A94._2 == 0x13 ||
                                  lbl_3_common_bss_32A94._2 == 0x1A)) {
                        kind = 7;
                    } else if (t > 0 && lbl_3_common_bss_32A94._2 >= 0x14 && lbl_3_common_bss_32A94._2 <= 0x1B) {
                        kind = 8;
                    }
                }
                n = 0;
                if (g_Runners[2].rosterID != -1) {
                    n = 1;
                }
                if (g_Runners[3].rosterID != -1) {
                    n++;
                }
                if (g_Scores._A6 <= n && n > 0) {
                    t = g_pCamera->_A98;
                    if (t > 0 && (lbl_3_common_bss_32A94._2 == 0x12 || lbl_3_common_bss_32A94._2 == 0x13 ||
                                  lbl_3_common_bss_32A94._2 == 0x1A)) {
                        kind = 7;
                    } else if (t > 0 && lbl_3_common_bss_32A94._2 >= 0x14 && lbl_3_common_bss_32A94._2 <= 0x1B) {
                        kind = 8;
                    }
                }
            }
        }
        if (lbl_3_common_bss_32A94._2 >= 0x24 && lbl_3_common_bss_32A94._2 <= 0x26 && g_pCamera->_A50 == 2) {
            if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                kind = 6;
            } else {
                n = 0;
                if (g_Runners[1].rosterID != -1) {
                    n = 1;
                }
                if (g_Runners[2].rosterID != -1) {
                    n++;
                }
                if (g_Runners[3].rosterID != -1) {
                    n++;
                }
                if (g_Scores._A6 <= 4 && n == 3) {
                    kind = 6;
                }
                n = 0;
                if (g_Runners[2].rosterID != -1) {
                    n = 1;
                }
                if (g_Runners[3].rosterID != -1) {
                    n++;
                }
                if (g_Scores._A6 <= n && n > 0) {
                    kind = 6;
                }
            }
        }
    }
    if (kind == 0) {
        return;
    }
    switch (kind) {
    case 2:
    case 9:
        g_Stats._3C = 2;
        break;
    case 13:
        g_Stats._3C = 13;
        break;
    case 3:
    case 10:
        g_Stats._3C = 3;
        break;
    case 4:
        g_Stats._3C = 4;
        break;
    case 5:
        g_Stats._3C = 5;
        break;
    case 6:
        g_Stats._3C = 6;
        break;
    case 7:
        g_Stats._3C = 7;
        break;
    case 8:
        g_Stats._3C = 1;
        g_Stats._3D = 0;
        break;
    case 11:
        g_Stats._3C = 11;
        break;
    default:
        g_Stats._3C = 1;
        g_Stats._3D = alt;
        break;
    }
    g_Stats._39 = 1;
}
#endif

// fn_3_7C190, size:0x4
void fn_3_7C190(void) {
    return;
}

// fn_3_7C194, size:0x68
s32 fn_3_7C194(void) {
    s32 f = g_Stats.playFrameCounter;
    if (f < 0x5A) {
        return 0;
    }
    if (f > g_Stats.endFrame - 0x3C) {
        return 0;
    }
    return fn_3_6C938(1, 0x1100) != 0;
}
