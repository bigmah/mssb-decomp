#include "game/rep_12D0.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_0009CD90_text.h"

extern f32 lbl_3_rodata_1328;
extern f32 lbl_3_rodata_132C;

// .text:0x00077914 size:0xC60 mapped:0x806B69A8
void fn_3_77914(void) {
    return;
}

// .text:0x00078574 size:0x1BC mapped:0x806B7608
// 99%: only idx/runner-ptr registers swapped (ours r6/r10, orig r10/r6); `s16 idx` fixed the ball ptr (r7)
// decl order, locals' types, r/e forms and inline idx all tried; no change
void fn_3_78574(s16 arg) {
    s32 flag = 0;
    s16 idx;
    s16 cur;
    s32 val;
    InMemRunnerType* r;
    if (g_FieldingLogic._126 == -1) {
        if (g_FieldingLogic._107 == 1) {
            if (g_Runners[g_FieldingLogic._0C4].runnerOnFieldOrOutOrScored != 1) {
                g_FieldingLogic._127 = -1;
                return;
            }
            g_FieldingLogic._126 = g_FieldingLogic._0C4;
        }
        if (g_FieldingLogic._107 == 2) {
            idx = (g_FieldingLogic._0C4 + 3) & 3;
            if (g_Runners[idx].runnerOnFieldOrOutOrScored != 1) {
                g_FieldingLogic._127 = -1;
                return;
            }
            g_FieldingLogic._126 = idx;
        }
    }
    if (g_FieldingLogic._107 != 0) {
        return;
    }
    if (g_Ball.numberOfThrowsDuringPlay > 1) {
        return;
    }
    cur = g_FieldingLogic._0C4;
    if (cur < 0 || cur > 3) {
        return;
    }
    if (g_Ball.AtBat_ContactResult == 3) {
        return;
    }
    if (lbl_3_common_bss_32A94._22 >= 1) {
        return;
    }
    if (g_Ball.ballZoneAwayFromHome >= 2) {
        return;
    }
    if (g_Strikes.outs > g_Strikes.storedOuts) {
        return;
    }
    idx = (cur + 3) & 3;
    r = &g_Runners[idx];
    if (r->runnerOnFieldOrOutOrScored != 1) {
        return;
    }
    val = g_Ball.framesUntilThrowReachesDest + 0xF;
    if (r->forceOutCd == 0) {
        if (cur != r->baseRunningTowards) {
            return;
        }
        if (cur == r->currentBase) {
            return;
        }
        val += 0x1E;
    }
    if (val < g_Runners[idx].framesToNextBase) {
        flag = 1;
    }
    if (flag != 0) {
        g_FieldingLogic._0EA = arg;
        g_FieldingLogic._113 = idx + 3;
    }
}

// .text:0x00078730 size:0x394 mapped:0x806B77C4
void fn_3_78730(void) {
    s32 i;
    u8 state;
    u8 status;
    s16 contact;

    if (g_FieldingLogic._107 != 0) {
        if (g_FieldingLogic._127 != 0) {
            return;
        }
        if (g_FieldingLogic._126 < 0 && g_Ball.framesSinceHit > 160) {
            g_FieldingLogic._127 = -1;
            return;
        }
        if (g_FieldingLogic._107 == 1 && g_FieldingLogic._126 >= 0) {
            if (g_FieldingLogic._126 <= 3) {
                if (g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt == 1) {
                    g_FieldingLogic._126 += 4;
                }
            } else if (g_FieldingLogic._126 <= 7) {
                i = g_FieldingLogic._126 - 4;
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    g_FieldingLogic._127 = 1;
                    return;
                }
                if (g_Runners[i].baseStandingOn >= i + 1) {
                    g_FieldingLogic._127 = 1;
                    return;
                }
            }
        }
        if (g_FieldingLogic._107 == 2 && g_FieldingLogic._126 >= 0) {
            if (g_FieldingLogic._126 <= 3) {
                if (g_FieldingLogic._126 == 3) {
                    g_FieldingLogic._127 = -1;
                    return;
                }
                if (g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt == 1) {
                    g_FieldingLogic._126 += 4;
                }
            } else if (g_FieldingLogic._126 <= 7) {
                i = g_FieldingLogic._126 - 4;
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    g_FieldingLogic._127 = 2;
                    return;
                }
                if (g_Runners[i].baseStandingOn >= i + 2) {
                    g_FieldingLogic._127 = 2;
                    return;
                }
            }
        }
        return;
    }

    state = g_FieldingLogic._113;
    if (state == 9 && g_Runners[0].currentBase >= 1) {
        g_Strikes.allForcedRunnersReachedTheirBaseInd = 2;
        return;
    }
    if ((state == 1 || state == 2) && g_Ball.lineDriveThroughPitcherInd == 0 && g_FieldingLogic._121 < 0 &&
        g_FieldingLogic._129 == 0 && (contact = g_Ball.AtBat_ContactResult) != 0 && g_Ball.deadBallReason == 0) {
        if ((g_Runners[0].runnerOnFieldOrOutOrScored == 1 && g_Runners[0].fractionalBasesRan >= 1.0f) ||
            g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
            if (state == 1) {
                g_FieldingLogic._132 = 1;
            } else {
                g_FieldingLogic._132 = 2;
            }
            g_FieldingLogic._113 = 9;
            g_Runners[0].runnerDidntReachOnError = 0;
        }
        if (g_Runners[0].runnerOnFieldOrOutOrScored == 2 && (g_Runners[0].forceOutCd == 2 || contact == 3)) {
            g_FieldingLogic._113 = 0;
        }
    }
    if (g_FieldingLogic._113 >= 3 && g_FieldingLogic._113 <= 7) {
        // states 3..7 refer to runner (state - 3)
        status = g_Runners[g_FieldingLogic._113 - 3].runnerOnFieldOrOutOrScored;
        if ((status == 1 && g_Runners[g_FieldingLogic._113 - 3].baseStandingOn >= 0 &&
             g_Runners[g_FieldingLogic._113 - 3].forceOutCd <= 0) ||
            status == 3) {
            g_FieldingLogic._113 = 9;
            g_Runners[0].runnerDidntReachOnError = 0;
            g_FieldingLogic._132 = 3;
        }
        // NOTE: after the state was set to 9 above this reads past g_Runners (index 6), as the original does
        if (g_Runners[g_FieldingLogic._113 - 3].runnerOnFieldOrOutOrScored == 2) {
            g_FieldingLogic._113 = 0;
        }
    }
    if (g_FieldingLogic._113 == 9 && g_Strikes.storedOuts == 2) {
        g_Runners[0].runnerDidntReachOnError = 0;
        g_Runners[1].runnerDidntReachOnError = 0;
        g_Runners[2].runnerDidntReachOnError = 0;
        g_Runners[3].runnerDidntReachOnError = 0;
    }
}

// .text:0x00078AC4 size:0x57C mapped:0x806B7B58
extern s32 fn_3_A6810(f32 fromX, f32 fromZ, f32 toX, f32 toZ); // throw time in frames
extern f32 lbl_3_data_4444[10]; // base positions (x, z) for home, 1st, 2nd, 3rd, ...

// NONMATCHING 97%: one dead `b` after the forced-out runner loop, and register picks in the
// tens/units runner-pair branch
#if NONMATCHING
void fn_3_78AC4(void) {
    s32 play;
    s32 batterSafe = 0;
    s32 n;
    s32 i;

    play = lbl_3_common_bss_32A94._20;
    if (lbl_3_common_bss_32A94.baseOccupied[0] == 0 && g_Ball.ballState == 1) {
        lbl_3_common_bss_32A94.baseOccupied[0] = 2;
        if ((g_Runners[0].forceOutCd != 0 || g_Runners[0].runnerOnFieldOrOutOrScored != 1) &&
            g_Ball.AtBat_ContactResult != 3 && g_Ball.ballZoneAwayFromHome < 2 &&
            fn_3_A6810(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z, lbl_3_data_4444[2],
                       lbl_3_data_4444[3]) + 75 <
                g_Runners[0].framesToNextBase) {
            lbl_3_common_bss_32A94.baseOccupied[0] = 1;
        }
    } else if (lbl_3_common_bss_32A94.baseOccupied[0] == 0 && g_Ball.AtBat_ContactResult != 0 &&
               g_Ball.ballState != 1 && g_Runners[0].runnerOnFieldOrOutOrScored == 1 &&
               g_Runners[0].currentBase >= 1) {
        lbl_3_common_bss_32A94.baseOccupied[0] = 2;
    }

    if (lbl_3_common_bss_32A94.baseOccupied[0] == 1) {
        for (i = 1; i < 4; i++) {
            if (g_Runners[i].baseStandingOn >= 0 || g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                lbl_3_common_bss_32A94.baseOccupied[i] = 2;
            }
        }
        for (n = 0; n < 3; n++) {
            if (lbl_3_common_bss_32A94.baseOccupied[n + 1] == 1) {
                break;
            }
        }
        if (n >= 3) {
            lbl_3_common_bss_32A94.baseOccupied[0] = 2;
        }
    }

    if (g_Runners[0].forceOutCd == 0 && g_Runners[0].runnerOnFieldOrOutOrScored == 1) {
        batterSafe = 1;
    }

    if (play == 5) {
        if (batterSafe) {
            g_FieldingLogic._113 = 9;
            lbl_3_common_bss_32A94._20 = 0;
            g_Runners[0].runnerDidntReachOnError = 0;
            g_FieldingLogic._132 = 3;
        }
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 2 && g_Runners[i].forceOutCd == 2) {
                lbl_3_common_bss_32A94._20 = 0;
                return;
            }
        }
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == 2 && g_Runners[0].currentBase == 0) {
        lbl_3_common_bss_32A94._20 = 0;
        return;
    }
    if (play == -1 || play == 0 || play == 4) {
        if (play == -1 && g_Runners[0].currentBase >= 1 &&
            (g_Ball.AtBat_ContactResult == 1 || g_Ball.AtBat_ContactResult == 2)) {
            lbl_3_common_bss_32A94._20 = 0;
        }
        if (lbl_3_common_bss_32A94._20 == 4 && g_Strikes.allForcedRunnersReachedTheirBaseInd == 0 &&
            g_Runners[0].forceOutCd == 0) {
            g_Strikes.allForcedRunnersReachedTheirBaseInd = 3;
        }
    } else if (play >= 100) {
        u8 s1 = g_Runners[1].runnerOnFieldOrOutOrScored;
        u8 s2;
        u8 s3;
        if (s1 == 2 || (s2 = g_Runners[2].runnerOnFieldOrOutOrScored) == 2 ||
            (s3 = g_Runners[3].runnerOnFieldOrOutOrScored) == 2) {
            lbl_3_common_bss_32A94._20 = 0;
        } else if (g_Runners[1].baseStandingOn >= 0 && s1 != 2) {
            lbl_3_common_bss_32A94._20 = 0x17;
        } else if (g_Runners[2].baseStandingOn >= 0 && s2 != 2) {
            lbl_3_common_bss_32A94._20 = 0xD;
        } else if (g_Runners[3].baseStandingOn >= 0 && s3 != 2) {
            lbl_3_common_bss_32A94._20 = 0xC;
        }
    } else if (play >= 10) {
        // two runners encoded as tens/units digits
        s32 a = play / 10;
        u8 sa = g_Runners[a].runnerOnFieldOrOutOrScored;
        s32 b = play % 10;
        u8 sb;
        if (sa == 2 || (sb = g_Runners[b].runnerOnFieldOrOutOrScored) == 2) {
            lbl_3_common_bss_32A94._20 = 0;
        } else if (g_Runners[a].baseStandingOn >= 0 && sa != 2) {
            lbl_3_common_bss_32A94._20 = b;
        } else if (g_Runners[b].baseStandingOn >= 0 && sb != 2) {
            lbl_3_common_bss_32A94._20 = a;
        }
    } else {
        u8 st = g_Runners[play].runnerOnFieldOrOutOrScored;
        if (st == 2) {
            lbl_3_common_bss_32A94._20 = 0;
        }
        if (((g_Runners[play].baseStandingOn >= 0 && st == 1) || st == 3) && batterSafe) {
            lbl_3_common_bss_32A94._20 = 4;
        }
    }
}
#endif

// .text:0x00079040 size:0x2F8 mapped:0x806B80D4
extern s32 fn_3_A63E4(s32 runnerIdx, s32 flag, s32* outA, s32* outB);

void fn_3_79040(void) {
    s32 a;
    s32 b;
    s32 margin;

    if (lbl_3_common_bss_32A94._20 != -1) {
        return;
    }
    if (g_Ball.fielderWBallIndex > 5) {
        lbl_3_common_bss_32A94._20 = 0;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored != 1 || g_Runners[0].currentBase != 0) {
        lbl_3_common_bss_32A94._20 = 0;
        return;
    }
    if (g_FieldingLogic._0C4 == 1) {
        lbl_3_common_bss_32A94._20 = 0;
        return;
    }
    margin = fn_3_A63E4(0, 1, &a, &b) + 10;
    if (g_Fielders[g_Ball.fielderWBallIndex]._1E0 != 0) {
        margin += 20;
    }
    if (margin >= 0) {
        lbl_3_common_bss_32A94._20 = 0;
        return;
    }
    lbl_3_common_bss_32A94._20 = 5;
    if (g_FieldingLogic._0C4 == 0) {
        if (g_Runners[3].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 3;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored == 3 && g_Runners[3].timeStandingOnBase < 60) {
            lbl_3_common_bss_32A94._20 = 3;
        }
        if (g_Runners[2].runnerOnFieldOrOutOrScored == 1 && g_Runners[2].currentBase == 3 &&
            lbl_3_common_bss_32A94._20 == 3) {
            lbl_3_common_bss_32A94._20 = 0x17;
        }
    } else if (g_FieldingLogic._0C4 == 3) {
        if (g_Runners[1].runnerOnFieldOrOutOrScored == 1 && g_Runners[1].currentBase == 2) {
            if (g_Runners[3].runnerOnFieldOrOutOrScored == 1 && g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
                lbl_3_common_bss_32A94._20 = 0x7B;
            } else if (g_Runners[3].runnerOnFieldOrOutOrScored == 1) {
                lbl_3_common_bss_32A94._20 = 0xD;
            } else if (g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
                lbl_3_common_bss_32A94._20 = 0xC;
            } else {
                lbl_3_common_bss_32A94._20 = 1;
            }
        } else if (g_Runners[3].runnerOnFieldOrOutOrScored == 1 && g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 0x17;
        } else if (g_Runners[3].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 3;
        } else if (g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 2;
        }
    } else if (g_FieldingLogic._0C4 == 2) {
        if (g_Runners[2].runnerOnFieldOrOutOrScored == 1 && g_Runners[1].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 0xC;
        } else if (g_Runners[2].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 2;
        } else if (g_Runners[1].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_common_bss_32A94._20 = 1;
        }
    }
    if (lbl_3_common_bss_32A94._20 == 5) {
        g_FieldingLogic._0EA = g_Ball.fielderWBallIndex;
    }
}

// .text:0x00079338 size:0xDC mapped:0x806B83CC
void fn_3_79338(void) {
    s32 i;
    if (g_Strikes.storedOuts == 2) {
        return;
    }
    if (g_Strikes.outs >= 3) {
        return;
    }
    if (lbl_3_common_bss_32A94._24 == 0) {
        if (g_Ball.AtBat_ContactResult == 3 || g_FieldingLogic._113 == 1) {
            if (g_Ball.landingSpotZoneAwayFromHome >= 2) {
                lbl_3_common_bss_32A94._24 = 2;
            }
        }
    } else if (lbl_3_common_bss_32A94._24 == 2) {
        if (g_Ball.AtBat_ContactResult == 3) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                    lbl_3_common_bss_32A94._24 = 1;
                }
            }
        }
    }
}

// .text:0x00079414 size:0x194 mapped:0x806B84A8
void fn_3_79414(void) {
    InMemRunnerType* q;
    InMemRunnerType* p;
    u8 a;
    u8 b;
    u8 t;
    s32 i;
    s32 r7;
    s32 r8;
    if (g_Ball.maybebuntOn2Strikes != 0) {
        lbl_3_common_bss_32A94._24 = 0xE;
        return;
    }
    if (g_Strikes.storedOuts >= 2) {
        return;
    }
    if (g_RunningLogic._12 <= 1) {
        return;
    }
    if (lbl_3_common_bss_32A94._24 == 0) {
        if (g_Ball.ballState == 1 || g_Ball.ballState == 2 || g_FieldingLogic._0CC >= 0 || g_FieldingLogic._0E8 >= 0) {
            lbl_3_common_bss_32A94._24 = 0xC;
        }
    }
    if (lbl_3_common_bss_32A94._24 == 0xC || lbl_3_common_bss_32A94._24 == 0xF) {
        r7 = 0;
        r8 = 0;
        p = &g_Runners[1];
        q = p;
        for (i = 0; i < 3; i++, q++) {
            if (q->forceOutCd != 0) r8++;
        }

        for (i = 1; i < 4; i++, p++) {
            a = p->currentBase;
            b = p->startingBase_baseAchieved;
            if (a > b || (t = p->runnerOnFieldOrOutOrScored) == 3) {
                if (a == 4 && b == 3 && p->runnerOnFieldOrOutOrScored == 2) {
                    lbl_3_common_bss_32A94._24 = 0xD;
                    break;
                }
                if (p->forceOutCd == 0) {
                    r7++;
                }
            } else if (t == 2) {
                lbl_3_common_bss_32A94._24 = 0xD;
                break;
            }
        }
        if (r7 != 0 && r8 == 0) {
            lbl_3_common_bss_32A94._24 = 0xB;
        }
    }
}

// .text:0x000795A8 size:0x1C4 mapped:0x806B863C
// 90%: first half matches; tail (lbl[0x23] s8 handling) has different register allocation (raw s8 in r5, extended copy r7, runners base r4)
// orig tail: raw `u8 x` (r5) + `sx=(s8)x` (r7), `mulli x,-1` (try `x * 0xFFFFFFFF` to get mulli, needs u8 raw x), lbl[0x23] and g_Runners base re-read in the else-if arm; decl order/types brute-forced w/o luck
void fn_3_795A8(void) {
    s32 v;
    u8 cur;
    s8 x;
    s32 sx;
    u8 c;
    u8 y;
    f32 spd;
    if ((s8)lbl_3_common_bss_32A94._23 > 0) {
        return;
    }
    if (g_Ball.deadBallReason == 1) {
        lbl_3_common_bss_32A94._22 = 4;
        lbl_3_common_bss_32A94._23 = 4;
        return;
    }
    if (g_Ball.deadBallReason == 3) {
        lbl_3_common_bss_32A94._22 = 2;
        lbl_3_common_bss_32A94._23 = 2;
        return;
    }
    if (g_Runners[0].runnerOnFieldOrOutOrScored == 3) {
        lbl_3_common_bss_32A94._22 = 4;
        lbl_3_common_bss_32A94._23 = 4;
        return;
    }
    if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballState != 0) {
        cur = g_Runners[0].currentBase;
        if (cur == 0) {
            v = 1;
        } else {
            spd = g_Runners[0].percentTowardsNextBase;
            if (spd < lbl_3_rodata_1328) {
                if (g_Runners[0].runnerOnFieldOrOutOrScored == 2 && lbl_3_rodata_132C == spd) {
                    v = cur - 1;
                } else {
                    v = cur;
                }
            } else {
                v = g_Runners[0].nextBase;
            }
        }
        lbl_3_common_bss_32A94._23 = -v;
    }
    x = lbl_3_common_bss_32A94._23;
    sx = x;
    c = g_Runners[0].currentBase;
    if (c == -sx) {
        if (x != 0) {
            y = x * -1;
            lbl_3_common_bss_32A94._23 = y;
            if ((s8)g_Runners[0].baseOfFailedBodyCheck == (s8)y) {
                lbl_3_common_bss_32A94._23 = y - 1;
            }
            lbl_3_common_bss_32A94._22 = lbl_3_common_bss_32A94._23;
            return;
        }
    } else if (c - 1 == -sx) {
        if (x != 0) {
            if ((s8)g_Runners[0].baseOfFailedBodyCheck == (1 - sx) % 4) {
                lbl_3_common_bss_32A94._23 = lbl_3_common_bss_32A94._23 * -1;
                lbl_3_common_bss_32A94._22 = lbl_3_common_bss_32A94._23;
                return;
            }
        }
    }
    if (c != 0) {
        lbl_3_common_bss_32A94._22 = c;
    }
}

