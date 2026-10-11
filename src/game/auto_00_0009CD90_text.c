#include "game/auto_00_0009CD90_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/rep_17E0.h"

extern s32 rand(void);

// Inlined copies of RandomInt_Game / random_fn_3_9EE24 (game/rep_1838.c).
static inline int BallRandomInt(int max) {
    int ret;
    int sign = max;
    if (max < 0) {
        max = -max;
    }
    if (max <= 1) {
        return 0;
    }
    g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - ((u8)g_Ball.StaticRandomInt2) + g_Ball.StaticRandomInt2 / max + g_Ball.totalFramesAtPlay;
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        return 0;
    }
    if (g_d_GameSettings.GameModeSelected == 7) {
        g_Ball.StaticRandomInt1 += rand();
    }
    ret = g_Ball.StaticRandomInt1 % max;
    if (ret < 0) {
        ret = -ret;
    }
    if (sign < 0) {
        return -ret;
    } else {
        return ret;
    }
}

static inline int SimRandomInt(int max) {
    int r2;
    int sign = max;
    if (max < 0) {
        max = -max;
    }
    if (max <= 1) {
        return 0;
    }
    unkSimulationRelatedStruct._00 = unkSimulationRelatedStruct._00 + g_d_GameSettings.FrameCountWhileNotAtMainMenu +
                                     (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1) - g_Ball.StaticRandomInt1 +
                                     ((u8)g_Ball.StaticRandomInt2) + (unkSimulationRelatedStruct._00 / max);
    r2 = unkSimulationRelatedStruct._00 % (u32)max;
    if (r2 < 0) {
        r2 = -r2;
    }
    if (sign < 0) {
        return -r2;
    } else {
        return r2;
    }
}

// .text:0x0009CD90 size:0xE8
void fn_3_9CD90(void) {
    s32 i;
    if (lbl_3_common_bss_32A94._2 == 0) {
        if (g_Strikes.allForcedRunnersReachedTheirBaseInd == 3) {
            lbl_3_common_bss_32A94._0 = 0x10;
            return;
        }
        if (g_Runners[0].runnerOnFieldOrOutOrScored == 2) {
            if (g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._108 == 2) {
                if (g_Ball.Hit_VerticalAngle > 0xA0) {
                    lbl_3_common_bss_32A94._2 = 0x12;
                } else {
                    lbl_3_common_bss_32A94._2 = 0x13;
                }
            } else {
                lbl_3_common_bss_32A94._2 = 0x15;
            }
        }
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].forceOutCd == 2) {
                lbl_3_common_bss_32A94._2 = 0x15;
            }
        }
    }
}

// .text:0x0009CE78 size:0x2C8
void fn_3_9CE78(void) {
    s32 i;
    BOOL moving;

    if (g_RunningLogic._12 == 1 || g_Strikes.storedOuts == 2) {
        if ((g_Runners[0].runnerOnFieldOrOutOrScored == 2 && g_Strikes.allForcedRunnersReachedTheirBaseInd == 0) ||
            g_Ball.AtBat_ContactResult == 3) {
            lbl_3_common_bss_32A94._0 = 0x1D;
            return;
        }
        if (g_Runners[0].forceOutCd == 0) {
            lbl_3_common_bss_32A94._0 = 0x1C;
        }
    } else if (g_Runners[3].runnerOnFieldOrOutOrScored != 0 && g_Runners[3].furthestBaseForcedToGoToOnWalk != 0) {
        if (g_Runners[3].runnerOnFieldOrOutOrScored == 3) {
            if (g_Ball.AtBat_ContactResult == 3) {
                lbl_3_common_bss_32A94._2 = 0x20;
                return;
            }
            lbl_3_common_bss_32A94._0 = 0x1E;
        } else if (g_Runners[3].runnerOnFieldOrOutOrScored == 2) {
            lbl_3_common_bss_32A94._0 = 0x1F;
        }
    } else {
        if (g_Scores._9E > g_Scores.team[g_Scores._AD].runs[g_Scores.inning]) {
            lbl_3_common_bss_32A94._2 = 0x20;
            return;
        }
        if (lbl_3_common_bss_32A94._2 != 0x22) {
            if (g_Ball.AtBat_ContactResult == 3) {
                lbl_3_common_bss_32A94._2 = 0x22;
                return;
            }
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].currentBase == g_Runners[i].startingBase_baseAchieved &&
                    g_Runners[i].runnerOnFieldOrOutOrScored == 2) {
                    lbl_3_common_bss_32A94._2 = 0x22;
                    return;
                }
            }
            moving = FALSE;
            for (i = 1; i < 4; i++) {
                if ((g_Runners[i].runnerOnFieldOrOutOrScored == 1 || g_Runners[i].runnerOnFieldOrOutOrScored == 3) &&
                    g_Runners[i].currentBase != g_Runners[i].startingBase_baseAchieved) {
                    moving = TRUE;
                    break;
                }
            }
            if (moving) {
                lbl_3_common_bss_32A94._2 = 0x21;
            }
        }
    }
}

// .text:0x0009D140 size:0x234
void fn_3_9D140(void) {
    s32 n;
    s32 i;

    if (g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._108 == 2) {
        n = 0;
        for (i = 1; i < 3; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 2 && g_Runners[i].outType == 4) {
                n++;
            }
        }
        if (n == 2) {
            lbl_3_common_bss_32A94._0 = 0x17;
            return;
        }
        if (n == 1) {
            lbl_3_common_bss_32A94._2 = 0x1A;
        }
    }
    if (g_Strikes.storedOuts + 3 == g_Strikes.outs && g_Ball.AtBat_ContactResult == 2 &&
        (g_Strikes.outs == 3 || g_RunningLogic._10 == 0)) {
        lbl_3_common_bss_32A94._0 = 0x17;
        if (lbl_3_common_bss_32A94.plays[2].outs == 3 || lbl_3_common_bss_32A94.plays[3].outs == 3) {
            lbl_3_common_bss_32A94._0 = 0x16;
            return;
        }
    }
    if (g_Strikes.storedOuts + 2 == g_Strikes.outs && g_Ball.AtBat_ContactResult == 2) {
        lbl_3_common_bss_32A94._2 = 0x19;
        if (lbl_3_common_bss_32A94.plays[2].fielder == 2 && lbl_3_common_bss_32A94.plays[0].outs == 0 &&
            lbl_3_common_bss_32A94.plays[1].outs == 1) {
            lbl_3_common_bss_32A94._2 = 0x18;
        }
        if (lbl_3_common_bss_32A94.plays[3].fielder >= 0 && lbl_3_common_bss_32A94.plays[2].outs == 2) {
            lbl_3_common_bss_32A94._0 = lbl_3_common_bss_32A94._2;
            return;
        }
    }
    if (g_Strikes.storedOuts + 1 == g_Strikes.outs && g_Ball.AtBat_ContactResult == 2 && lbl_3_common_bss_32A94.plays[2].fielder == 2 &&
               lbl_3_common_bss_32A94.plays[0].outs == 0 && g_Runners[(lbl_3_common_bss_32A94.plays[1].base + 3) & 3].forcedToAdvanceInd != 0 &&
               lbl_3_common_bss_32A94.plays[1].base >= 0 && lbl_3_common_bss_32A94.plays[1].base != 1 && lbl_3_common_bss_32A94.plays[1].outs == 1 &&
               lbl_3_common_bss_32A94.plays[2].outs == 1 && lbl_3_common_bss_32A94.plays[2].base == 1) {
        lbl_3_common_bss_32A94._2 = 0x14;
    }
}


// .text:0x0009D374 size:0x1DC
s32 fn_3_9D374(void) {
    s16 earned;
    s32 diff;
    s32 flag = 0;
    if (g_Strikes.allForcedRunnersReachedTheirBaseInd == 1) {
        diff = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] - g_Scores._A0;
        if (diff == 1 && g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
            flag = 1;
        }
        earned = g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice;
        if (earned == 0 && g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
            lbl_3_common_bss_32A94._0 = 5;
        } else if (earned == 3) {
            if (diff != 0 && flag == 0) {
                lbl_3_common_bss_32A94._0 = 6;
            } else {
                lbl_3_common_bss_32A94._2 = 0xB;
            }
        } else if (earned == 2) {
            if (diff != 0 && flag == 0) {
                lbl_3_common_bss_32A94._0 = 7;
            } else {
                lbl_3_common_bss_32A94._2 = 0xC;
            }
        } else if (earned == 1) {
            s8 zone = *(s8*)&g_Ball.ballZoneWhenCaught; // TODO type: read as signed here
            if (zone >= 0 && zone <= 1) {
                if (diff != 0 && flag == 0) {
                    lbl_3_common_bss_32A94._0 = 9;
                } else {
                    lbl_3_common_bss_32A94._2 = 0xE;
                }
            } else if (diff != 0 && flag == 0) {
                lbl_3_common_bss_32A94._0 = 8;
            } else {
                lbl_3_common_bss_32A94._2 = 0xD;
            }
        } else {
            if (diff != 0 && flag == 0) {
                lbl_3_common_bss_32A94._2 = 0xA;
            } else {
                lbl_3_common_bss_32A94._2 = 0xF;
            }
        }
        return 1;
    }
    return 0;
}

// .text:0x0009D550 size:0x44
void fn_3_9D550(void) {
    if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
        lbl_3_common_bss_32A94._0 = 0x27;
        return;
    }
    lbl_3_common_bss_32A94._0 = 0x2C;
}

// .text:0x0009D594 size:0x6C
void fn_3_9D594(void) {
    switch (g_RunningLogic._12) {
    case 4:
        lbl_3_common_bss_32A94._0 = 1;
        return;
    case 3:
        lbl_3_common_bss_32A94._0 = 2;
        return;
    case 2:
        lbl_3_common_bss_32A94._0 = 3;
        return;
    default:
        lbl_3_common_bss_32A94._0 = 4;
        return;
    }
}

// .text:0x0009D600 size:0xA4
void fn_3_9D600(void) {
    if (g_Pitcher.strikeOutOrWalk == 1) {
        if (g_Batter.missedBuntStatus != 0) {
            lbl_3_common_bss_32A94._2 = 0x26;
            return;
        }
        if (g_Batter.missSwingOrBunt != 0) {
            lbl_3_common_bss_32A94._2 = 0x24;
            return;
        }
        lbl_3_common_bss_32A94._2 = 0x25;
    } else if (g_Pitcher.strikeOutOrWalk == 2) {
        lbl_3_common_bss_32A94._2 = 0x2A;
    } else if (g_Pitcher.strikeOutOrWalk == 3) {
        lbl_3_common_bss_32A94._0 = 0x2B;
    }
}

// .text:0x0009D6A4 size:0x4B8
void fn_3_9D6A4(void) {
    BOOL tracked = FALSE;
    s32 i;

    if (g_Stats.replayInd != 0) {
        return;
    }
    if (lbl_3_common_bss_32A94._0 == 0) {
        if (g_FieldingLogic._107 == 4) {
            lbl_3_common_bss_32A94._0 = 0x28;
        } else if (g_GameLogic.gameStatus == 1) {
            fn_3_9D600();
        } else if (g_Ball.deadBallReason == 1) {
            fn_3_9D594();
        } else if (g_Ball.AtBat_ContactResult == -1) {
            fn_3_9D550();
        } else {
            if (g_GameLogic.gameStatus == 2) {
                if (g_Ball.fielderWBallIndex >= 0) {
                    if (lbl_3_common_bss_32A94.lastFielder == -1) {
                        for (i = 0; i < 5; i++) {
                            if (lbl_3_common_bss_32A94.plays[i].fielder == -1) {
                                s16 base;
                                lbl_3_common_bss_32A94.plays[i].fielder = g_Ball.fielderWBallIndex;
                                lbl_3_common_bss_32A94.plays[i].outs = g_Strikes.outs - g_Strikes.storedOuts;
                                base = g_Fielders[g_Ball.fielderWBallIndex]._18C;
                                if (base >= 0 && base <= 3) {
                                    switch (base) {
                                    case 0:
                                        if ((g_RunningLogic.occupiedBases & 0x1111) == 0x1111) {
                                            lbl_3_common_bss_32A94.plays[i].base = 0;
                                        }
                                        break;
                                    case 1:
                                        lbl_3_common_bss_32A94.plays[i].base = 1;
                                        break;
                                    case 2:
                                        if ((g_RunningLogic.occupiedBases & 0x11) == 0x11) {
                                            lbl_3_common_bss_32A94.plays[i].base = 2;
                                        }
                                        break;
                                    default:
                                        if ((g_RunningLogic.occupiedBases & 0x111) == 0x111) {
                                            lbl_3_common_bss_32A94.plays[i].base = 3;
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        tracked = TRUE;
                    } else if (lbl_3_common_bss_32A94.lastFielder == g_Ball.fielderWBallIndex) {
                        for (i = 4; i >= 0; i--) {
                            if (lbl_3_common_bss_32A94.plays[i].fielder == g_Ball.fielderWBallIndex) {
                                if (g_Ball.timeSinceBallPickedUp <= 0x3C) {
                                    lbl_3_common_bss_32A94.plays[i].outs = g_Strikes.outs - g_Strikes.storedOuts;
                                }
                                break;
                            }
                        }
                        tracked = TRUE;
                    }
                }
                lbl_3_common_bss_32A94.lastFielder = g_Ball.fielderWBallIndex;
            }
            if (g_Ball.maybeBuntInd != 0) {
                fn_3_9CE78();
            } else if (fn_3_9D374() == 0) {
                if (tracked) {
                    fn_3_9D140();
                }
                fn_3_9CD90();
            }
        }
    }
    fn_3_9CAF0();
    if (lbl_3_common_bss_32A94._0 != 0) {
        lbl_3_common_bss_32A94._2 = lbl_3_common_bss_32A94._0;
    }
}

// .text:0x0009DB5C size:0x88
void fn_3_9DB5C(void) {
    s32 i;
    for (i = 7; i > 3; i--) {
        lbl_3_common_bss_32A94._6[i - 3] = lbl_3_common_bss_32A94._6[i - 4];
    }
    lbl_3_common_bss_32A94._6[0] = lbl_3_common_bss_32A94._0;
    lbl_3_common_bss_32A94._0 = 0;
    lbl_3_common_bss_32A94._2 = 0;
    lbl_3_common_bss_32A94._4 = 0;
    for (i = 0; i < 5; i++) {
        lbl_3_common_bss_32A94.plays[i].fielder = -1;
        lbl_3_common_bss_32A94.plays[i].outs = -1;
        lbl_3_common_bss_32A94.plays[i].base = -1;
    }
    lbl_3_common_bss_32A94.lastFielder = -1;
}

// .text:0x0009DBE4 size:0x34
void fn_3_9DBE4(void) {
    lbl_3_common_bss_32A94._7D = 0;
    lbl_3_common_bss_32A94._7F = 0;
    lbl_3_common_bss_32A94._81 = 0;
    lbl_3_common_bss_32A94._82 = 0;
    lbl_3_common_bss_32A94._84 = 0;
    lbl_3_common_bss_32A94._85 = 0;
    lbl_3_common_bss_32A94._87 = 0;
    lbl_3_common_bss_32A94._88 = 0;
    lbl_3_common_bss_32A94._8A = 0;
}

// .text:0x0009DC18 size:0x460
// Shuffles arr[0..n) in place.
// NONMATCHING 97%: shuffle result kept in r0 and copied (extra mr); loop pointer regs rotated
#if NONMATCHING
void fn_3_9DC18(u8* arr, u32 n, BOOL useBallRng) {
    s32 used[20];
    s32 src[20];
    s32 tmp[10];
    u32 k;
    s32 i;
    s32 r;
    s32 j;

    for (k = 0; k < n; k++) {
        tmp[k] = arr[k];
    }
    for (i = 0; i < (s32)n; i++) {
        src[i] = tmp[i];
        used[i] = 0;
    }
    for (i = n - 1; i >= 0; i--) {
        r = useBallRng ? BallRandomInt(i + 1) : SimRandomInt(i + 1);
        for (j = 0; j < (s32)n; j++) {
            if (used[j] == 0) {
                if (r == 0) {
                    tmp[i] = src[j];
                    used[j] = 1;
                    break;
                }
                r--;
            }
        }
    }
    for (k = 0; k < n; k++) {
        arr[k] = tmp[k];
    }
}
#endif

// .text:0x0009E078 size:0x2F0
// Shuffles arr[0..n) in place.
void fn_3_9E078(s32* arr, s32 n, BOOL useBallRng) {
    s32 src[20];
    s32 used[20];
    s32 i;
    s32 j;
    s32 r;

    for (i = 0; i < n; i++) {
        src[i] = arr[i];
        used[i] = 0;
    }
    for (i = n - 1; i >= 0; i--) {
        if (useBallRng) {
            r = BallRandomInt(i + 1);
        } else {
            r = SimRandomInt(i + 1);
        }
        for (j = 0; j < n; j++) {
            if (used[j] == 0) {
                if (r == 0) {
                    arr[i] = src[j];
                    used[j] = 1;
                    break;
                }
                r--;
            }
        }
    }
}

// .text:0x0009E368 size:0x238
s32 fn_3_9E368(s32* weights, s32 n) {
    s32 buf[10];
    s32 i;
    s32 total;
    s32 sum;
    s32 r;
    s32 rem;
    sum = 0;
    for (i = 0; i < n; i++) {
        buf[i] = weights[i];
        sum += buf[i];
    }
    total = sum;
    if (sum < 0) {
        total = -sum;
    }
    if (total <= 1) {
        r = 0;
    } else {
        g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - (g_Ball.StaticRandomInt2 & 0xFF) + g_Ball.StaticRandomInt2 / total + g_Ball.totalFramesAtPlay;
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
            r = 0;
        } else {
            if (g_d_GameSettings.GameModeSelected == 7) {
                g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 + rand();
            }
            r = g_Ball.StaticRandomInt1 % total;
            if (r < 0) {
                r = -r;
            }
            if (sum < 0) {
                r = -r;
            }
        }
    }
    rem = r;
    for (i = 0; i < n; i++) {
        if (rem < buf[i]) {
            return i;
        }
        rem -= buf[i];
    }
    return 0;
}

// .text:0x0009E5A0 size:0x234
int RandomIndexFromWeights(u8* weights, int count) {
    s32 n = count;
    s32 buf[10];
    s32 i;
    s32 total;
    s32 sum;
    s32 r;
    s32 rem;
    sum = 0;
    for (i = 0; i < n; i++) {
        buf[i] = weights[i];
        sum += buf[i];
    }
    total = sum;
    if (sum < 0) {
        total = -sum;
    }
    if (total <= 1) {
        r = 0;
    } else {
        g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 - (g_Ball.StaticRandomInt2 & 0xFF) + g_Ball.StaticRandomInt2 / total + g_Ball.totalFramesAtPlay;
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
            r = 0;
        } else {
            if (g_d_GameSettings.GameModeSelected == 7) {
                g_Ball.StaticRandomInt1 = g_Ball.StaticRandomInt1 + rand();
            }
            r = g_Ball.StaticRandomInt1 % total;
            if (r < 0) {
                r = -r;
            }
            if (sum < 0) {
                r = -r;
            }
        }
    }
    rem = r;
    for (i = 0; i < n; i++) {
        if (rem < buf[i]) {
            return i;
        }
        rem -= buf[i];
    }
    return 0;
}

// .text:0x0009E7D4 size:0x60
void fn_3_9E7D4(s32 i) {
    if (g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xF) {
        return;
    }
    if (g_GameLogic.currentBatterPerTeam[i] == 9) {
        g_GameLogic.currentBatterPerTeam[i] = 1;
    } else {
        g_GameLogic.currentBatterPerTeam[i]++;
    }
}

// .text:0x0009E834 size:0x1E8
s32 fn_3_9E834(void) {
    s32 i;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        for (i = 0; i < 54; i++) {
            // TODO type: starMissionCompletionTracker is 0x4508 bytes, header only covers the first 0xAF8
            if (((u8*)starMissionCompletionTracker)[0x43D6 + i] != 0) {
                return 1;
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            if (lbl_80361B20[i] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x0009EA1C size:0xC8
s32 fn_3_9EA1C(s32 idx) {
    s32 i;
    for (i = 1; i < 10; i++) {
        if (g_GameLogic.battingOrderAndPositionMapping[idx][i][1] % 10 == 9) {
            return 1;
        }
    }
    return 0;
}
