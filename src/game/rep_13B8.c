#include "game/rep_13B8.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_0009CD90_text.h"
#include "static/GameSettings.h"
#include "game/auto_00_000AC9F8_text.h"
#include "game/auto_00_001658F0_text.h"
#include "main/file_80011640.h"
#define REP_HEADER_FN repHeader_13B8
#include "header_rep_inline.h"
#include "math.h"
extern const f32 lbl_3_rodata_14E4;
extern const f32 lbl_3_rodata_14E0;
extern const f32 lbl_3_rodata_14DC;
extern const f32 lbl_3_rodata_14D8;
extern const f32 lbl_3_rodata_1494;
#include "game/rep_D0.h"
extern const f32 lbl_3_rodata_1460;
extern f32 lbl_3_data_4A34[];
extern int fn_3_A6810(f32, f32, f32, f32);
extern s16 lbl_3_data_1C88[];
extern f32 lbl_3_data_4B58[][3]; // per base: three angles
extern int fn_3_52560(int, f32, f32);
extern f32 lbl_3_data_4444[];
extern s16 lbl_3_data_21904[];
extern f32 lbl_3_data_218BC[];
extern const f32 lbl_3_rodata_1430;
extern const f32 lbl_3_rodata_14BC;
extern const f32 lbl_3_rodata_1438;
extern const f32 lbl_3_rodata_1440;
extern const f32 lbl_3_rodata_144C;
extern const f32 lbl_3_rodata_1450;
extern const f32 lbl_3_rodata_14A8;
extern int fn_3_A6ABC(f32, f32);
extern const f32 lbl_3_rodata_149C;
extern const f32 lbl_3_rodata_14A0;
extern const f32 lbl_3_rodata_14A4;
extern const f32 lbl_3_rodata_1454;
extern const f32 lbl_3_rodata_1458;
extern const f32 lbl_3_rodata_145C;
extern s16 lbl_3_data_4C54[];
extern s16 lbl_3_data_4B90[];
extern f32 lbl_3_data_4C44[];
typedef struct { f32 x, z; } P2;

extern f32 lbl_3_rodata_1498;
extern const f32 lbl_3_rodata_1408;
extern const f32 lbl_3_rodata_140C;
extern const f32 lbl_3_rodata_1410;
extern const f32 lbl_3_rodata_1414;
typedef struct { f32 x, z; } XZ13B8;
extern f32 lbl_3_data_4444[];
extern XZ13B8 lbl_3_data_4A54[2][13];
extern void running_roundBasePosition(f32 frame, XZ13B8* outPos, XZ13B8* points, int count);
extern const f64 lbl_3_rodata_1488;
extern const f64 lbl_3_rodata_14E8;
extern const f32 lbl_3_rodata_14F0;
extern const f32 lbl_3_rodata_14F4;
extern f32 fn_3_9FEA8(f32);
extern const f32 lbl_3_rodata_143C;
extern const f32 lbl_3_rodata_1434;
extern const f32 lbl_3_rodata_1444;
extern const f32 lbl_3_rodata_1448;
extern f32 lbl_3_data_4B44;
extern s16 lbl_3_data_4B48[];
extern const f32 lbl_3_rodata_1470;
extern const f32 lbl_3_rodata_1484;
extern u8 lbl_3_data_7760[];
extern const f32 lbl_3_rodata_1490;

#pragma dont_inline on



// Base coordinates (x, z) indexed by base number.
#define BASE_XZ_13B8 ((XZ13B8*)lbl_3_data_4444)

extern StarChanceState lbl_3_common_bss_37400;
extern void fn_3_161588(int, s16);
extern const f32 lbl_3_rodata_14F8;
extern void fn_3_59918(s32, s32);
extern void fn_3_5C74C(s32);
extern void fn_3_5D094(s32);
extern void fn_3_6D964(int, int);
extern s16 lbl_3_data_4B40[];
extern u32 fn_3_107DF8(u8);
extern s16 lbl_3_data_1C58[];
extern s16 lbl_3_data_49DC[];
extern int RandomInt_Game(int);

// .text:0x0007D79C size:0x184 mapped:0x806BC830
void fn_3_7D79C(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->runningToDugoutFrameCounter <= 0) {
        XZ13B8 pos;
        int idx;
        int count;
        f32 dist = r->fractionalBasesRan;
        f32 frame = r->percentTowardsNextBase;
        if (dist < lbl_3_rodata_1408) {
            idx = 0;
            count = 4;
        } else if (dist < lbl_3_rodata_140C) {
            idx = 3;
            count = 4;
        } else if (dist < lbl_3_rodata_1410) {
            idx = 6;
            count = 4;
        } else if (g_GameLogic.secondaryGameMode == 6) {
            idx = 9;
            count = 4;
        } else {
            idx = 9;
            count = 3;
        }
        running_roundBasePosition(frame, &pos, &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == 6][idx], count);
        r->position.x = pos.x;
        r->position.z = pos.z;
        r->position.y = lbl_3_rodata_1414;
        r->velocity.x = lbl_3_rodata_1414;
        r->velocity.z = lbl_3_rodata_1414;
    }
    if (r->runningToDugoutFrameCounter < 0x7FFE) {
        r->runningToDugoutFrameCounter += 1;
    } else {
        r->runningToDugoutFrameCounter = 0x7FFF;
    }
    if (r->runningToDugoutFrameCounter >= lbl_3_data_21904[2]) {
        g_Minigame._1B15[g_Minigame._18FC[i]] = 0;
    }
}

// .text:0x0007D920 size:0xBC mapped:0x806BC9B4
void fn_3_7D920(int i) {
    InMemRunnerType* r = &g_Runners[i];
    s8 k = g_Minigame._18FC[i];
    if (g_Minigame._1B15[k] == 2) {
        if (g_Minigame._1B19 == 0) {
            g_Minigame._1B15[k] = 3;
            r->runningToDugoutFrameCounter = 0;
        }
        return;
    }
    if (r->runningToDugoutFrameCounter < lbl_3_data_21904[1]) {
        r->position.x += r->velocity.x;
        r->position.z += r->velocity.z;
    } else {
        g_Minigame._1B15[k] = 2;
    }
    if (r->runningToDugoutFrameCounter < 0x7FFE) {
        r->runningToDugoutFrameCounter += 1;
    } else {
        r->runningToDugoutFrameCounter = 0x7FFF;
    }
}

extern const f64 lbl_3_rodata_1418;
extern const f64 lbl_3_rodata_1420;
extern const f64 lbl_3_rodata_1428;
extern const f32 lbl_3_rodata_1414;

// .text:0x0007D9DC size:0x154 mapped:0x806BCA70
static inline float sqrt13B8(float x) {
    if (x > lbl_3_rodata_1414) {
        double half = lbl_3_rodata_1418;
        double three = lbl_3_rodata_1420;
        double xd = (double)x;
        double guess = __frsqrte(xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        return (float)(xd * guess);
    } else if (x < lbl_3_rodata_1428)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}


void fn_3_7D9DC(int i) {
    InMemRunnerType* r = &g_Runners[i];
    f32 m = sqrt13B8(g_Minigame._1AEC * g_Minigame._1AEC + g_Minigame._1AF4 * g_Minigame._1AF4);
    f32 k = lbl_3_data_218BC[7];
    r->velocity.x = k * (g_Minigame._1AEC / m);
    r->velocity.z = k * (g_Minigame._1AF4 / m);
    r->runningToDugoutFrameCounter = 0;
}

// .text:0x0007DB30 size:0x1F4 mapped:0x806BCBC4
void fn_3_7DB30(int i) {
    InMemRunnerType* r;
    u8 k;
    InputStruct* c;
    u8 t;
    u16 b;
    k = (u8)g_Minigame._18FC[i];
    c = &g_Controls[(s8)k];
    r = &g_Runners[i];
    if (fn_3_107DF8(k)) {
        c = &g_Minigame._1D7C[g_Minigame._18FC[i]];
    }
    t = r->runningDirectionCode;
    if (t == 3) {
        u8 u = r->nextDirectionBeingProcessed;
        if (u == 2 || u == 1) {
            b = c->newButtonInput;
            if (b & 0x400) {
                if (r->rosterID >= 0) {
                    r->runningDirectionDesired = 3;
                }
            } else if (b & 0x800) {
                if (r->rosterID >= 0) {
                    r->runningDirectionDesired = 1;
                }
            }
        } else if (c->newButtonInput & 0x800) {
            if (r->rosterID >= 0) {
                r->runningDirectionDesired = 2;
            }
        }
    } else if (t == 1) {
        u8 u = r->nextDirectionBeingProcessed;
        if (u == 2 || u == 3) {
            b = c->newButtonInput;
            if (b & 0x400) {
                if (r->rosterID >= 0) {
                    r->runningDirectionDesired = 3;
                }
            } else if (b & 0x800) {
                if (r->rosterID >= 0) {
                    r->runningDirectionDesired = 1;
                }
            }
        } else if (c->newButtonInput & 0x400) {
            if (r->rosterID >= 0) {
                r->runningDirectionDesired = 2;
            }
        }
    } else {
        b = c->buttonInput;
        if (b & 0x800) {
            if (r->rosterID >= 0) {
                r->runningDirectionDesired = 1;
            }
        } else if (b & 0x400) {
            if (r->rosterID >= 0) {
                r->runningDirectionDesired = 3;
            }
        }
    }
    if (c->newButtonInput & 0xF00) {
        r->newButtonThisFrame_forMashPurposes = 1;
    }
}

// .text:0x0007DD24 size:0x48 mapped:0x806BCDB8
void fn_3_7DD24(int a) {
    if (g_GameLogic.gameStatus == 2 && g_Minigame.turnOverStatus == 0) {
        fn_3_7DB30(a);
    }
}

// .text:0x0007DD6C size:0x550 mapped:0x806BCE00
// 99%: body matches (88C24 tail written out inline with `base`, switch as an if-chain, 7D920/7D79C/833EC bodies copied inline).
// Left: (1) orig does `addi r25,base; mr r27,r25`, we get `addi r27; mr r25,r27`; (2) tail hoisted-load order (orig: lha, li counter, lbz fl, ...).
// NONMATCHING 99%: register copy direction for the runner base and tail load order (see note above)
#if NONMATCHING
void fn_3_7DD6C(void) {
    InMemRunnerType* r;
    s8* mp;
    InMemRunnerType* base;
    int i;
    u8 m;
    s8 k;
    int v;
    XZ13B8 pos;
    int idx;
    int count;
    f32 dist;
    f32 frame;
    fn_3_87424();
    base = g_Runners;
    for (i = 0, mp = g_Minigame._18FC, r = base; i < 4; r++, i++, mp++) {
        if (r->runnerOnFieldOrOutOrScored != 0) {
            g_Minigame.runnerNum = i;
            if (r->runningDirectionCode == 0) {
                r->runningDirectionCode = 2;
            }
            r->turningAroundInd = idx = 0;
            k = *mp;
            m = g_Minigame._1B15[k];
            if (m == 4) {
            } else if (m == 1 || m == 2) {
                if (m == 2) {
                    if (g_Minigame._1B19 == 0) {
                        g_Minigame._1B15[k] = 3;
                        r->runningToDugoutFrameCounter = 0;
                    }
                } else {
                if (r->runningToDugoutFrameCounter < lbl_3_data_21904[1]) {
                    r->position.x += r->velocity.x;
                    r->position.z += r->velocity.z;
                } else {
                    g_Minigame._1B15[k] = 2;
                }
                if (r->runningToDugoutFrameCounter < 0x7FFE) {
                    r->runningToDugoutFrameCounter += 1;
                } else {
                    r->runningToDugoutFrameCounter = 0x7FFF;
                }
                }
            } else if (m == 3) {
                if (r->runningToDugoutFrameCounter <= 0) {
                    dist = r->fractionalBasesRan;
                    frame = r->percentTowardsNextBase;
                    if (dist < lbl_3_rodata_1408) {
                        count = 4;
                    } else if (dist < lbl_3_rodata_140C) {
                        idx = 3;
                        count = 4;
                    } else if (dist < lbl_3_rodata_1410) {
                        idx = 6;
                        count = 4;
                    } else if (g_GameLogic.secondaryGameMode == 6) {
                        idx = 9;
                        count = 4;
                    } else {
                        idx = 9;
                        count = 3;
                    }
                    running_roundBasePosition(frame, &pos, &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == 6][idx], count);
                    r->position.x = pos.x;
                    r->position.z = pos.z;
                    r->position.y = lbl_3_rodata_1414;
                    r->velocity.x = lbl_3_rodata_1414;
                    r->velocity.z = lbl_3_rodata_1414;
                }
                if (r->runningToDugoutFrameCounter < 0x7FFE) {
                    r->runningToDugoutFrameCounter += 1;
                } else {
                    r->runningToDugoutFrameCounter = 0x7FFF;
                }
                if (r->runningToDugoutFrameCounter >= lbl_3_data_21904[2]) {
                    g_Minigame._1B15[*mp] = 0;
                }
            } else {
                if (g_GameLogic.gameStatus == 2 && g_Minigame.turnOverStatus == 0) {
                    fn_3_7DB30(i);
                }
                fn_3_8307C(i);
                if ((r->runningToDugoutInd == 0 || r->runningToDugoutStage == 0) && r->actionCode == 0) {
                    if (r->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] || (r->runningDirectionCode != 1 && r->runningDirectionCode != 3)) {
                        u8 s = r->runningDirectionDesired;
                        if (s != 0) {
                            if (g_GameLogic.secondaryGameMode == 6) {
                                if (r->runnerOnFieldOrOutOrScored == 1) {
                                    r->nextDirectionBeingProcessed = s;
                                }
                            } else {
                                if ((i != 0 || r->nextBase != 1) && r->runnerOnFieldOrOutOrScored == 1) {
                                    r->nextDirectionBeingProcessed = s;
                                }
                                if (r->nextDirectionBeingProcessed == 3 && r->tagUpInd != 3 && r->baseStandingOn >= 0) {
                                    r->nextDirectionBeingProcessed = 0;
                                }
                            }
                        }
                    }
                    v = fn_3_7FA78(i);
                    if (v != 0) {
                        r->nextDirectionBeingProcessed = v;
                    }
                }
                if (r->runningToDugoutInd != 0) {
                    r->baseRoundingState = 0;
                    r->actionCode = 0;
                } else {
                    fn_3_7ECFC(i);
                    fn_3_7F494(i);
                    if (g_GameLogic.secondaryGameMode != 6) {
                        if (i == 0 && r->nextBase == 1) {
                            fn_3_7F2D8();
                        } else if (r->baseRoundingState == 1) {
                            r->baseRoundingState = 0;
                        }
                        fn_3_7EBD4(i);
                    }
                }
                fn_3_82670(i);
                fn_3_81190(i);
                fn_3_80028(i);
                fn_3_8307C(i);
            }
        }
    }
    fn_3_87AE8();
    if (g_GameLogic.secondaryGameMode == 6) {
        fn_3_87CC8();
    } else {
        fn_3_88408();
        fn_3_88B18();
        for (i = 0; i < 4; base++, i++) {
            s16 a = g_Ball.AtBat_ContactResult;
            u8 b1 = g_Ball.landingSpotZoneAwayFromHome;
            u8 fl = g_FieldingLogic._108;
            u8 b2 = g_Ball.ballZoneAwayFromHome;
            u8 b3 = g_Ball.ballState;
            if (base->runnerOnFieldOrOutOrScored == 1) {
                if ((a == 3 || fl == 2) && b1 <= 1) {
                    base->isEligibleToScore = 0;
                } else if (b2 <= 1 && b3 != 0 && (u16)a > 1) {
                    u8 t = base->currentBase;
                    if (t != 0 && t < 3) {
                        base->isEligibleToScore = 0;
                    }
                }
            }
        }
        fn_3_87E80();
    }
    fn_3_8781C();
}
#endif

// .text:0x0007E2BC size:0x7AC mapped:0x806BD350
// Steal / return input for the runners (controller stick + buttons).
// NONMATCHING 97%: register allocation; original keeps a dead never-incremented counter check in the return loop
#if NONMATCHING
void fn_3_7E2BC(void) {
    InputStruct* c;
    InMemRunnerType* r;
    int k;
    int found;
    int target;
    int skipped;
    u16 held;
    s16 stick;

    c = &g_Controls[(s32)g_GameLogic.teams[g_GameLogic.teamBatting]];
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.loadingGuidedPractice != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        c = &g_Practice.inputs[g_GameLogic.teamBatting];
    }
    held = c->buttonInput;
    if (g_Ball.framesSinceHit < 30) {
        held = c->newButtonInput;
    }
    stick = c->controlStickAngle;
    if (stick < 0) {
        found = 0;
        for (k = 0, r = g_Runners; k < 4; k++, r++) {
            if (r->runnerOnFieldOrOutOrScored == 1) {
                if (r->runningDirectionCode == 3) {
                    if (r->nextDirectionBeingProcessed != 2 && r->nextDirectionBeingProcessed != 1 && (c->newButtonInput & 0x800)) {
                        found = 1;
                        break;
                    }
                } else if (r->runningDirectionCode == 1 && r->currentBase != 0 && r->nextDirectionBeingProcessed != 2 && r->nextDirectionBeingProcessed != 3 && (c->newButtonInput & 0x400)) {
                    found = 1;
                    break;
                }
            }
        }
        if (found) {
            for (k = 0, r = g_Runners; k < 4; k++, r++) {
                if (r->runnerOnFieldOrOutOrScored == 1 && r->rosterID >= 0) {
                    r->runningDirectionDesired = 2;
                }
            }
        } else {
            for (k = 0, r = g_Runners; k < 4; k++, r++) {
                if (r->runnerOnFieldOrOutOrScored != 1) {
                    continue;
                }
                if (r->runningDirectionCode == 3) {
                    if (r->nextDirectionBeingProcessed == 2 || r->nextDirectionBeingProcessed == 1) {
                        if (held & 0x400) {
                            if (r->rosterID >= 0) {
                                r->runningDirectionDesired = 3;
                            }
                        } else if ((c->newButtonInput & 0x800) && r->rosterID >= 0) {
                            r->runningDirectionDesired = 1;
                        }
                    }
                } else if (r->runningDirectionCode == 1) {
                    if (r->nextDirectionBeingProcessed == 2 || r->nextDirectionBeingProcessed == 3) {
                        if (c->newButtonInput & 0x400) {
                            if (r->rosterID >= 0) {
                                r->runningDirectionDesired = 3;
                            }
                        } else if ((held & 0x800) && r->rosterID >= 0) {
                            r->runningDirectionDesired = 1;
                        }
                    }
                } else if (r->runningDirectionCode == 5 && (held & 0x800)) {
                    if (r->rosterID >= 0) {
                        r->runningDirectionDesired = 1;
                    }
                } else if (c->newButtonInput & 0x800) {
                    if (r->rosterID >= 0) {
                        r->runningDirectionDesired = 1;
                    }
                } else if ((c->newButtonInput & 0x400) && r->rosterID >= 0) {
                    r->runningDirectionDesired = 3;
                }
            }
        }
        if (c->newButtonInput & 0xF00) {
            for (k = 0; k < 4; k++) {
                g_Runners[k].newButtonThisFrame_forMashPurposes = 1;
            }
        }
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0 && g_Practice.practice_runner_countInputForMashing != 0) {
            for (k = 0; k < 4; k++) {
                g_Runners[k].newButtonThisFrame_forMashPurposes = 1;
            }
        }
    } else if (held & 0x800) {
        // Advance: pick the runner heading to the base the stick points at.
        target = -1;
        if (stick >= 0xA00 && stick < 0xE00) {
            target = 0;
        } else if (stick >= 0x600) {
            target = 3;
        } else if (stick >= 0x200) {
            target = 2;
        }
        if (target < 0) {
            return;
        }
        skipped = 0;
        for (k = 3, r = &g_Runners[3]; k >= 0; k--, r--) {
            if (r->runnerOnFieldOrOutOrScored != 1 || r->nextBase != target) {
                continue;
            }
            if (skipped != 0) {
                if ((s8)r->_151 <= 0) {
                    r->_151 = 1;
                } else {
                    r->_151++;
                }
                r->someCountdown_unused = lbl_3_data_4C54[5];
                if ((s8)r->_151 <= lbl_3_data_4C54[6]) {
                    return;
                }
            }
            if (r->runningDirectionCode == 1) {
                if (r->nextDirectionBeingProcessed == 2 || r->nextDirectionBeingProcessed == 3) {
                    if (g_Runners[k].rosterID >= 0) {
                        g_Runners[k].runningDirectionDesired = 1;
                    }
                    return;
                }
                if (skipped != 0) {
                    return;
                }
                skipped++;
                continue;
            } else if (r->runningDirectionCode == 3) {
                if (r->nextDirectionBeingProcessed == 2 || r->nextDirectionBeingProcessed == 1) {
                    if (g_Runners[k].rosterID >= 0) {
                        g_Runners[k].runningDirectionDesired = 1;
                    }
                } else if (c->newButtonInput & 0x800) {
                    if (g_Runners[k].rosterID >= 0) {
                        g_Runners[k].runningDirectionDesired = 2;
                    }
                }
                return;
            } else if (r->runningDirectionCode == 5 && (held & 0x800)) {
                if (g_Runners[k].rosterID >= 0) {
                    g_Runners[k].runningDirectionDesired = 1;
                }
                return;
            } else {
                if ((c->newButtonInput & 0x800) && g_Runners[k].rosterID >= 0) {
                    g_Runners[k].runningDirectionDesired = 1;
                }
                return;
            }
        }
    } else if (held & 0x400) {
        // Return: pick the runner standing on the base the stick points at.
        target = -1;
        if (stick < 0xA00 || stick >= 0xE00) {
            if (stick >= 0x600) {
                target = 3;
            } else if (stick >= 0x200) {
                target = 2;
            } else {
                target = 1;
            }
        }
        if (target < 0) {
            return;
        }
        for (k = 0, r = g_Runners; k < 4; k++, r++) {
            if (r->runnerOnFieldOrOutOrScored != 1 || r->currentBase != target) {
                continue;
            }
            if (r->runningDirectionCode == 1) {
                if (r->nextDirectionBeingProcessed == 2 || r->nextDirectionBeingProcessed == 3) {
                    if (g_Runners[k].rosterID >= 0) {
                        g_Runners[k].runningDirectionDesired = 3;
                    }
                } else if (c->newButtonInput & 0x400) {
                    if (g_Runners[k].rosterID >= 0) {
                        g_Runners[k].runningDirectionDesired = 2;
                    }
                }
                return;
            } else if (r->runningDirectionCode == 3) {
                if (r->nextDirectionBeingProcessed == 2 || r->nextDirectionBeingProcessed == 1) {
                    if (g_Runners[k].rosterID >= 0) {
                        g_Runners[k].runningDirectionDesired = 3;
                    }
                    return;
                }
            } else if (c->newButtonInput & 0x400) {
                if (g_Runners[k].rosterID >= 0) {
                    g_Runners[k].runningDirectionDesired = 3;
                }
                return;
            }
        }
    }
}
#endif

// .text:0x0007EA68 size:0x16C mapped:0x806BDAFC
void fn_3_7EA68(void) {
    InputStruct* c = &g_Controls[(s32)g_GameLogic.teams[g_GameLogic.teamBatting]];
    if (g_Pitcher.pitcherActionState == 1 || g_Pitcher.pitcherActionState == 2 || g_Pitcher.pitcherActionState == 3) {
        s16 v;
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
            c = &g_Practice.inputs[g_GameLogic.teamBatting];
        }
        if (!(c->newButtonInput & 0x800)) {
            return;
        }
        v = c->controlStickAngle;
        if (v < 0) {
            int k;
            for (k = 1; k < 4; k++) {
                if (g_Runners[k].runnerOnFieldOrOutOrScored != 0 && g_Runners[k].stealingStatus == 0) {
                    g_Runners[k].stealingStatus = 1;
                }
            }
        } else {
            if (v >= 0x1C0 && v <= 0x640) {
                g_Runners[1].stealingStatus = 1;
            }
            if (c->controlStickAngle >= 0x5C0 && c->controlStickAngle <= 0xA40) {
                g_Runners[2].stealingStatus = 1;
            }
            if (c->controlStickAngle >= 0x9C0 && c->controlStickAngle <= 0xE40) {
                g_Runners[3].stealingStatus = 1;
            }
        }
    }
}

// .text:0x0007EBD4 size:0x128 mapped:0x806BDC68
void fn_3_7EBD4(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if (g_GameLogic.gameStatus == 1) {
        return;
    }
    if (r->runnerOnFieldOrOutOrScored == 2) {
        if (r->runningToDugoutInd != 0) {
            return;
        }
        if (r->actionCode != 0) {
            if (r->actionStage == 3) {
                r->actionCode = 0;
                r->actionStage = 0;
            } else {
                return;
            }
        }
        if (r->forceOutCd == 2) {
            u8 c = r->overRun1BStage;
            if (c != 0) {
                if (c == 3) {
                    r->baseRoundingState = 0;
                    r->overRun1BStage = 0;
                } else {
                    return;
                }
            } else {
                if (!(r->percentTowardsNextBase < lbl_3_rodata_1430)) {
                    if (r->runningDirectionCode != 2) {
                        return;
                    }
                }
            }
        }
        r->runningToDugoutInd = 1;
        r->runningToDugoutStage = 0;
        r->overRun1BStage = 0;
    } else {
        if (g_Strikes.outs < 3) {
            return;
        }
        if (r->actionCode != 0) {
            if (r->actionStage == 3) {
                r->actionCode = 0;
                r->actionStage = 0;
            } else {
                return;
            }
        }
        r->runningToDugoutInd = 1;
        r->runningToDugoutStage = 0;
    }
}

// .text:0x0007ECFC size:0x5DC mapped:0x806BDD90
int fn_3_7ECFC(int i) {
    InMemRunnerType* r = &g_Runners[i];
    f32 d = lbl_3_rodata_1434;
    int flag = 0;
    if (g_GameLogic.secondaryGameMode == 6) {
        r->baseRoundingState = 2;
        r->offsetFromNormalRunningPathInd = 1;
        return 1;
    }
    if (r->baseRoundingState == 2) {
        r->baseRoundingState = 0;
    }
    r->offsetFromNormalRunningPathInd = 0;
    if (g_Ball.framesSinceHit <= 0 && g_Practice.practiceType_2 != 3) {
        return 0;
    }
    if (r->actionCode != 0) {
        return 0;
    }
    if (r->baseRoundingState == 1) {
        return 0;
    }
    if (r->runningDirectionCode == 3) {
        flag = 1;
    } else {
        if (g_FieldingLogic._0C4 >= 0) {
            f32 a = sqrt13B8((lbl_3_data_4444[r->baseRunningTowards * 2] - g_Ball.throwTarget.x) * (lbl_3_data_4444[r->baseRunningTowards * 2] - g_Ball.throwTarget.x) +
                             (lbl_3_data_4444[r->baseRunningTowards * 2 + 1] - g_Ball.throwTarget.z) * (lbl_3_data_4444[r->baseRunningTowards * 2 + 1] - g_Ball.throwTarget.z));
            f32 b = sqrt13B8((g_Ball.AtBat_Contact_BallPos.x - g_Ball.throwTarget.x) * (g_Ball.AtBat_Contact_BallPos.x - g_Ball.throwTarget.x) +
                             (g_Ball.AtBat_Contact_BallPos.z - g_Ball.throwTarget.z) * (g_Ball.AtBat_Contact_BallPos.z - g_Ball.throwTarget.z));
            d = a + b;
        }
        if (r->distanceFromBall < lbl_3_rodata_1438) {
            flag = 1;
        } else if (d < lbl_3_rodata_143C) {
            flag = 1;
        } else if (g_Pitcher.strikeOutOrWalk >= 2) {
            flag = 1;
        } else if (g_Ball.ballZoneAwayFromHome <= 1 && (g_Ball.AtBat_ContactResult == 1 || g_Ball.AtBat_ContactResult == 2) && r->percentTowardsNextBase < lbl_3_rodata_1440) {
            flag = 1;
        } else if (g_FieldingLogic._107 == 2) {
            flag = 1;
        }
        if (g_Practice.practiceType_2 == 3) {
            flag = 0;
        }
        if (flag != 0 && g_Ball.ballState == 0 && g_Ball.ballZoneAwayFromHome >= 1 && g_Ball.ballVelocity > lbl_3_rodata_1444) {
            if (r->percentTowardsNextBase >= lbl_3_rodata_1448 && r->percentTowardsNextBase <= lbl_3_rodata_1430) {
                if (g_Ball.ballDistanceFromHome > lbl_3_rodata_140C + g_Fielders[2]._070 && g_Ball.ballDistanceFromHome > lbl_3_rodata_140C + g_Fielders[4]._070) {
                    if (g_Ball.ballDistanceFromHome > lbl_3_rodata_140C + g_Fielders[3]._070 && g_Ball.ballDistanceFromHome > lbl_3_rodata_140C + g_Fielders[5]._070) {
                        flag = 0;
                    } else if (g_Fielders[3]._07C > g_Fielders[3]._070 - g_Ball.ballDistanceFromHome && g_Fielders[5]._07C > g_Fielders[5]._070 - g_Ball.ballDistanceFromHome) {
                        flag = 0;
                    }
                }
            }
        }
    }
    if (g_Ball.ballState == 1 && g_Ball.ballDistanceFromBase[r->baseRunningTowards] < lbl_3_rodata_144C && r->percentTowardsNextBase > lbl_3_rodata_1450) {
        flag = 1;
    }
    if ((r->runningDirectionCode == 1 || r->runningDirectionCode == 2) && lbl_3_rodata_1414 == r->roundingStrengthPercent &&
        (r->percentTowardsNextBase < lbl_3_rodata_1450 || r->fractionalBasesRan >= lbl_3_rodata_1410)) {
        flag = 1;
    }
    if (r->overrunBaseStage != 3 && flag != 0) {
        r->offsetFromNormalRunningPathInd = 0;
        return 0;
    }
    r->baseRoundingState = 2;
    r->offsetFromNormalRunningPathInd = 1;
    if (r->baseStandingOn >= 0) {
        r->roundingStrengthPercent = lbl_3_rodata_1408;
    }
    return 1;
}

// .text:0x0007F2D8 size:0x1BC mapped:0x806BE36C
int fn_3_7F2D8(void) {
    InMemRunnerType* r = g_Runners;
    f32 dist;
    s16 s;
    if (r->actionCode == 0 && r->overrun1st_doneChecking == 0) {
        if (r->overRun1BStage != 0) {
            return 1;
        }
        s = g_Ball.AtBat_ContactResult;
        if (s != 3) {
            dist = r->fractionalBasesRan;
            if (dist < lbl_3_rodata_1450) {
                goto fail;
            }
            if (s == 0 && r[1].runnerOnFieldOrOutOrScored == 1) {
                if (r[1].baseStandingOn == 1) {
                    goto fail;
                }
                if (g_Ball.landingSpotZoneAwayFromHome <= 2 && r[1].fractionalBasesRan < lbl_3_rodata_1454) {
                    goto fail;
                }
            }
            if (s == 0 && g_Ball.maxYOfHit > lbl_3_rodata_1438) {
                goto set;
            }
            if (g_Ball.ballZoneAwayFromHome <= 1) {
                goto fail;
            }
            if (g_Ball.ballZoneAwayFromHome <= 2 && g_Ball.ballVelocity < lbl_3_rodata_1458) {
                goto fail;
            }
            s = g_Ball.fielderWBallIndex;
            if (s >= 0 && g_Ball.ballDistanceFromBase[1] < lbl_3_rodata_144C) {
                goto fail;
            }
            if (s == 8 && dist <= lbl_3_rodata_145C) {
                goto fail;
            }
            if (g_FieldingLogic._0C4 == 1 && g_Ball.ballState == 2 && r->framesToNextBase + 0x1E > g_Ball.framesUntilThrowReachesDest) {
                goto fail;
            }
set:
            r->overrun1st_doneChecking = 1;
        }
    }
    if (r->baseRoundingState == 1) {
        r->baseRoundingState = 0;
    }
    return 0;
fail:
    r->baseRoundingState = 1;
    if (r->fractionalBasesRan > lbl_3_rodata_1430) {
        r->overRun1BStage = 1;
    }
    return 1;
}

// .text:0x0007F494 size:0x530 mapped:0x806BE528
extern u8 bodyCheckProbabiliities[][5];
extern BOOL checkFieldingStat(int, int, int);
extern void fn_3_6C854(int team, int kind);
extern void fn_3_1682AC(void* actor, int);
extern u32 fn_3_90220(s32 idx, s32 off);
extern u32 playSoundEffect(s32 id);
extern void fn_3_1AE44(u8 arg4, u16 arg5, f32 arg1, f32 arg2, f32 arg3);
// NONMATCHING 99.6%: register allocation in the body-check fielder/probability lookup
#if NONMATCHING
int fn_3_7F494(int i) {
    InMemRunnerType* r = &g_Runners[i];
    int bodyCheckWindow = 0;
    u8 dir;
    int frames;
    f32 t;
    int d;
    int k;
    InMemFielderType* f;
    u8 prob;

    if (g_GameLogic.secondaryGameMode == 6) {
        return 0;
    }
    if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 2) {
        return 0;
    }
    if (r->baseStandingOn >= 0) {
        return 0;
    }
    dir = r->runningDirectionCode;
    if (!(dir == 1 && r->percentRanPerFrame_slideAdj > lbl_3_rodata_1414) && !(dir == 3 && r->percentRanPerFrame_slideAdj < lbl_3_rodata_1414)) {
        return 0;
    }
    if (r->actionCode != 0) {
        return 1;
    }
    if (r->baseRoundingState == 2) {
        return 0;
    }
    if (r->nextBase == 1) {
        return 0;
    }
    if (dir == 3) {
        if (r->tagUpInd == 2 && r->currentBase != r->startingBase_baseAchieved) {
            return 0;
        }
        if (r->forceOutCd == 1 && g_Ball.AtBat_ContactResult != 0) {
            return 0;
        }
    }
    if (dir == 1) {
        t = r->percentTowardsNextBase_slideAdj / r->percentRanPerFrame_slideAdj;
    } else {
        t = r->percentFromCurrentBase_slideAdj / -r->percentRanPerFrame_slideAdj;
    }
    frames = (int)t + 1;
    if (g_Ball.ballState == 2) {
        if (g_FieldingLogic._0C4 == r->baseRunningTowards) {
            d = g_Ball.framesUntilThrowReachesDest + 6 - frames;
            if (d >= lbl_3_data_4C54[1] && d <= lbl_3_data_4C54[2]) {
                bodyCheckWindow = 1;
            }
        }
    } else if (g_Ball.ballState == 1) {
        d = 6 - g_Ball.timeSinceBallPickedUp - frames;
        if (d >= lbl_3_data_4C54[1] && d <= lbl_3_data_4C54[2]) {
            bodyCheckWindow = 1;
        }
    }
    d = r->charID * 5;
    if (frames < lbl_3_data_7760[d] || frames > lbl_3_data_7760[d + 1]) {
        return 0;
    }
    r->actionCode = 1;
    r->actionFrames_countUp = 0;
    r->actionFrames_countDown = frames;
    r->actionStage = 1;
    if (r->runningDirectionCode == 1) {
        r->actionInForwardDirectionInd = 1;
        if (bodyCheckWindow != 0 && r->forceOutCd == 0 && r->mashPercent >= lbl_3_data_4C44[0] &&
            checkFieldingStat(g_GameLogic.teamBatting, r->rosterID, 0xC) != 0) {
            k = r->baseRunningTowards;
            if (g_FieldingLogic._101[k] != 0 &&
                ((g_Ball.fielderWBallIndex >= 0 && g_Ball.fielderWBallIndex == g_FieldingLogic._0D0[k] &&
                  g_Ball.timeSinceBallPickedUp <= 9) ||
                 (g_FieldingLogic._0C4 == k && g_Ball.framesUntilThrowReachesDest < 15))) {
                f = &g_Fielders[g_FieldingLogic._0D0[k]];
                prob = bodyCheckProbabiliities[r->weight][f->weight];
                f->_211 = 1;
                f->_214 = r->baseRunningTowards;
                if (RandomInt_Game(100) < prob) {
                    r->actionCode = 2;
                    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamBatting) {
                        fn_3_161588(0xC, r->rosterID);
                    }
                } else {
                    r->actionCode = 3;
                    if (g_GameLogic._13E[g_GameLogic.teamBatting] == 0) {
                        fn_3_6C854(g_GameLogic.teamBatting, 2);
                    }
                }
                fn_3_1682AC(lbl_8036E548.active[i + 9], 0xC);
                fn_3_90220(r->charID, 0xA);
                playSoundEffect(0x19C);
                fn_3_1AE44(4, 0, lbl_3_data_4444[r->baseRunningTowards * 2], lbl_3_rodata_1414, lbl_3_data_4444[r->baseRunningTowards * 2 + 1]);
            }
        }
    } else {
        r->actionInForwardDirectionInd = 0;
    }
    if (r->forceOutCd == 1 && r->baseRunningTowards != r->startingBase_baseAchieved) {
        r->forceOutType_unsed = 1;
    }
    if (r->tagUpInd == 2 && r->baseRunningTowards == r->startingBase_baseAchieved) {
        r->forceOutType_unsed = 2;
    }
    if (g_Pitcher.strikeOutOrWalk == 2 && (r->furthestBaseForcedToGoToOnWalk > r->currentBase || (r->forcedToAdvanceInd != 0 && r->currentBase == r->startingBase_baseAchieved))) {
        r->forceOutType_unsed = 3;
    }
    return 1;
}
#endif

// .text:0x0007F9C4 size:0xB4 mapped:0x806BEA58
void fn_3_7F9C4(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->runningToDugoutInd != 0) {
        r->baseRoundingState = 0;
        r->actionCode = 0;
        return;
    }
    fn_3_7ECFC(i);
    fn_3_7F494(i);
    if (g_GameLogic.secondaryGameMode != 6) {
        if (i == 0 && r->nextBase == 1) {
            fn_3_7F2D8();
        } else if (r->baseRoundingState == 1) {
            r->baseRoundingState = 0;
        }
        fn_3_7EBD4(i);
    }
}

// .text:0x0007FA78 size:0x318 mapped:0x806BEB0C
int fn_3_7FA78(int i) {
    InMemRunnerType* r = &g_Runners[i];
    u8 gm;
    u8 fl;
    s16 b66;
    s16 f0;
    s16 f2;
    gm = g_GameLogic.secondaryGameMode;
    if (gm == 6) {
        if (g_Minigame.turnOverStatus != 0) {
            return 2;
        }
        if (g_Minigame._1B19 == 2 || g_Minigame._1B19 == 3) {
            return 2;
        }
        return 0;
    }
    if (gm != 0xE) {
        b66 = g_Ball.framesSinceHit;
        if (b66 <= 0) {
            return 0;
        }
        fl = g_FieldingLogic._107;
        if (fl == 1) {
            if (i != 0 && r->runningDirectionCode == 2 && r->runningDirectionDesired == 0 && g_Ball.framesSincePickOff == lbl_3_data_4C54[4]) {
                return 3;
            }
        } else if (fl == 2 && i != 0 && r->runningDirectionCode == 2 && r->runningDirectionDesired == 0 && g_Ball.framesSincePickOff == lbl_3_data_4C54[4]) {
            return 3;
        }
        if (i == 0) {
            if (r->fractionalBasesRan < lbl_3_rodata_1408 && r->forceOutCd == 1 && g_FieldingLogic._108 == 0 && fl == 0) {
                return 1;
            }
        } else if (r->leadOffStatus == 1) {
            return 1;
        }
        if (g_Ball.deadBallReason == 1) {
            return 1;
        }
        if (b66 == 5) {
            return 1;
        }
    }
    f0 = r->restrictedMovementCodes;
    if (f0 & 4) {
        u8 a = r->runningDirectionCode;
        if (a == 1) {
            return 2;
        }
        if (r->nextDirectionBeingProcessed == 1 && a == 2) {
            return 2;
        }
    } else if (f0 & 1) {
        if ((r->baseRoundingState != 1 || r->overRun1BStage == 0) && r->runningDirectionCode == 1) {
            return 2;
        }
        if (r->nextDirectionBeingProcessed == 1) {
            return 2;
        }
    } else if (f0 & 2) {
        if (r->runningDirectionCode == 3) {
            return 2;
        }
        if (r->nextDirectionBeingProcessed == 3) {
            return 2;
        }
    } else {
        f2 = r->restrictedMovementCodes_stored;
        if (f2 & 4) {
            if ((f0 & 1) == 0 && g_Ball.framesSinceHit > 0 && (r->runningDirectionCode == 2 || r->nextDirectionBeingProcessed == 2) && r->tagUpInd == 0) {
                return 1;
            }
        } else if ((f2 & 8) && (f0 & 2) == 0 && (r->runningDirectionCode == 2 || r->nextDirectionBeingProcessed == 2)) {
            return 3;
        }
    }
    if (g_Ball.AtBat_ContactResult == 3 && r->tagUpInd == 2) {
        return 3;
    }
    return 0;
}

// .text:0x0007FD90 size:0x118 mapped:0x806BEE24
void fn_3_7FD90(int i) {
    InMemRunnerType* r = &g_Runners[i];
    int v;
    if ((r->runningToDugoutInd == 0 || r->runningToDugoutStage == 0) && r->actionCode == 0) {
        if (r->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] || (r->runningDirectionCode != 1 && r->runningDirectionCode != 3)) {
            u8 s = r->runningDirectionDesired;
            if (s != 0) {
                if (g_GameLogic.secondaryGameMode == 6) {
                    if (r->runnerOnFieldOrOutOrScored == 1) {
                        r->nextDirectionBeingProcessed = s;
                    }
                } else {
                    if ((i != 0 || r->nextBase != 1) && r->runnerOnFieldOrOutOrScored == 1) {
                        r->nextDirectionBeingProcessed = s;
                    }
                    if (r->nextDirectionBeingProcessed == 3 && r->tagUpInd != 3 && r->baseStandingOn >= 0) {
                        r->nextDirectionBeingProcessed = 0;
                    }
                }
            }
        }
        v = fn_3_7FA78(i);
        if (v != 0) {
            r->nextDirectionBeingProcessed = v;
        }
    }
}

// .text:0x0007FEA8 size:0x2C mapped:0x806BEF3C
void fn_3_7FEA8(s32 i, s32 v) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->rosterID < 0) {
        return;
    }
    if (v == 0) {
        return;
    }
    r->runningDirectionDesired = v;
}

// .text:0x0007FED4 size:0xFC mapped:0x806BEF68
void fn_3_7FED4(f32* out, f32 dist, f32 frame) {
    XZ13B8 pos;
    int idx;
    int count;
    if (dist < lbl_3_rodata_1408) {
        idx = 0;
        count = 4;
    } else if (dist < lbl_3_rodata_140C) {
        idx = 3;
        count = 4;
    } else if (dist < lbl_3_rodata_1410) {
        idx = 6;
        count = 4;
    } else if (g_GameLogic.secondaryGameMode == 6) {
        idx = 9;
        count = 4;
    } else {
        idx = 9;
        count = 3;
    }
    running_roundBasePosition(frame, &pos, &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == 6][idx], count);
    out[0] = pos.x;
    out[2] = pos.z;
    out[1] = lbl_3_rodata_1414;
}

// .text:0x0007FFD0 size:0x58 mapped:0x806BF064
#pragma fp_contract off
void fn_3_7FFD0(f32* out, int a, int b, f32 t) {
    f32* T = lbl_3_data_4A34;
    f32 d[2];
    d[0] = T[b * 2] - T[a * 2];
    d[1] = T[b * 2 + 1] - T[a * 2 + 1];
    d[0] *= t;
    d[1] *= t;
    out[0] = d[0] + T[a * 2];
    out[2] = d[1] + T[a * 2 + 1];
    out[1] = 0.0f;
}
#pragma fp_contract on

// .text:0x00080028 size:0x109C mapped:0x806BF0BC
// Dugout entrance per stadium (g_d_GameSettings+9) and team.
extern XZ13B8 lbl_3_data_4290[7][2];
extern f32 lbl_3_data_4B24;
extern XZ13B8 lbl_3_data_4B28[3];
extern f32 lbl_3_data_4B50;
extern s16 lbl_3_data_4B54;

// Aim runner r at its team's dugout and start walking there (state 2).
static inline void walkToDugout13B8(InMemRunnerType* r) {
    XZ13B8* dugout = &lbl_3_data_4290[g_d_GameSettings.StadiumID][g_GameLogic.homeTeamBattingInd_fieldingTeam];
    f32 dx;
    f32 dz;
    f32 dist;
    r->nextBaseCoordinates.x = dugout->x;
    r->nextBaseCoordinates.z = dugout->z;
    dx = r->nextBaseCoordinates.x - r->position.x;
    dz = r->nextBaseCoordinates.z - r->position.z;
    dist = sqrt13B8(dx * dx + dz * dz);
    r->velocity.x = (dx / dist) * lbl_3_data_4B50;
    r->velocity.z = (dz / dist) * lbl_3_data_4B50;
    r->velocity.y = lbl_3_rodata_1414;
    r->runningToDugoutFrameCounter = 0;
    r->framesToReachDugout = (int)(dist / lbl_3_data_4B50) + 1;
    r->runningToDugoutStage = 2;
}

static inline void stepToDugout13B8(InMemRunnerType* r) {
    r->runningToDugoutFrameCounter += 1;
    r->framesToReachDugout -= 1;
    r->position.x += r->velocity.x;
    r->position.y += r->velocity.y;
    r->position.z += r->velocity.z;
    if (r->framesToReachDugout < 0) {
        r->velocity.x = lbl_3_rodata_1414;
        r->velocity.y = lbl_3_rodata_1414;
        r->velocity.z = lbl_3_rodata_1414;
        r->runningToDugoutStage = 3;
    }
}

// Point on the leg from the stored position (0xC) towards the base ahead/behind,
// scaled by how far along the leg the runner is now vs. when it was stored.
static inline void legPoint13B8(InMemRunnerType* r, f32* out, f32 a, f32 b, f32 tx, f32 ty, f32 tz, f32 px, f32 py, f32 pz) {
    f32 t;
    if (lbl_3_rodata_1414 == a) {
        out[0] = px;
        out[1] = py;
        out[2] = pz;
    } else {
        t = lbl_3_rodata_1408 - b / a;
        out[0] = r->positionStored.x + scaleValue(tx - r->positionStored.x, t);
        out[1] = r->positionStored.y + scaleValue(ty - r->positionStored.y, t);
        out[2] = r->positionStored.z + scaleValue(tz - r->positionStored.z, t);
    }
}

// Updates runner i's world position from its baserunning state.
// NONMATCHING 82%: float scheduling/register allocation, branch layout of the 0x140 state switch; the original also computes an unused distance to the dugout in the knock-back path
#if NONMATCHING
void fn_3_80028(int i) {
    InMemRunnerType* r = &g_Runners[i];
    XZ13B8 round;
    f32 pos[3];
    f32 px;
    f32 py;
    f32 pz;
    f32 tx;
    f32 tz;
    f32 a;
    f32 b;
    f32 dx;
    f32 dz;
    f32 d;
    int n;
    int base;
    int idx;
    int count;

    if (g_GameLogic.secondaryGameMode != 6) {
        if (g_Ball.framesSinceHit <= 0 && i == 0) {
            // Still in the batter's box.
            r->position.x = g_Batter.batterPos.x;
            r->position.y = lbl_3_rodata_1414;
            r->position.z = g_Batter.batterPos.z;
            r->fractionalBasesRan = lbl_3_rodata_1414;
            r->percentTowardsNextBase = lbl_3_rodata_1414;
            r->fractionalBasesRan_stored = lbl_3_rodata_1414;
            r->percentTowardsNextBase_stored = lbl_3_rodata_1414;
            r->groundVelocity[0] = lbl_3_rodata_1414;
            r->runningDirectionCode = 0;
            r->nextDirectionBeingProcessed = 0;
            goto done;
        }
        if (r->overRun1BStage == 2) {
            running_roundBasePosition(r->overrun1B_somePositionControl, (XZ13B8*)pos, lbl_3_data_4B28, 3);
            r->position.x = pos[0];
            r->position.z = pos[1];
            goto done;
        }
        if (r->overRun1BStage == 3) {
            // Walking back to first after overrunning.
            n = r->overrunBaseFrames_countDown;
            tx = scaleValue(lbl_3_data_4A34[4] - lbl_3_data_4A34[2], r->slidingAdjustment_backwards) + lbl_3_data_4A34[2];
            tz = scaleValue(lbl_3_data_4A34[5] - lbl_3_data_4A34[3], r->slidingAdjustment_backwards) + lbl_3_data_4A34[3];
            pos[0] = (tx - r->position.x) / (f32)n;
            r->position.x += pos[0];
            pos[1] = (lbl_3_rodata_1414 - r->position.y) / (f32)n;
            r->position.y += pos[1];
            pos[2] = (tz - r->position.z) / (f32)n;
            r->position.z += pos[2];
            goto done;
        }
        if (r->overRun1BStage > 3) {
            goto done;
        }
        if (r->slideHomeFrames_CountDown != 0) {
            r->slideHomeFrames_CountDown -= 1;
            goto done;
        }
        if (r->actionCode != 0 && r->actionStage == 2) {
            // Sliding into a base.
            if (r->timeStandingOnBase < 6) {
                goto done;
            }
            if (r->baseOfFailedBodyCheck >= 0) {
                base = r->baseOfFailedBodyCheck;
            } else {
                base = r->baseStandingOn;
            }
            tx = scaleValue(lbl_3_data_4A34[((base + 1) & 3) * 2] - lbl_3_data_4A34[base * 2], r->slidingAdjustment_backwards) + lbl_3_data_4A34[base * 2];
            tz = scaleValue(lbl_3_data_4A34[((base + 1) & 3) * 2 + 1] - lbl_3_data_4A34[base * 2 + 1], r->slidingAdjustment_backwards) +
                 lbl_3_data_4A34[base * 2 + 1];
            n = r->actionFrames_countDown;
            pos[0] = (tx - r->position.x) / (f32)n;
            r->position.x += pos[0];
            pos[1] = (lbl_3_rodata_1414 - r->position.y) / (f32)n;
            r->position.y += pos[1];
            pos[2] = (tz - r->position.z) / (f32)n;
            r->position.z += pos[2];
            goto done;
        }
        if (r->runningToDugoutInd == 1) {
            if (r->runningToDugoutStage == 0) {
                walkToDugout13B8(r);
            }
            if (r->runningToDugoutStage == 2) {
                stepToDugout13B8(r);
            }
            goto done;
        }
        if (r->runningToDugoutInd == 3) {
            // Knocked back first, then walk to the dugout.
            if (r->runningToDugoutStage == 0) {
                XZ13B8* dugout = &lbl_3_data_4290[g_d_GameSettings.StadiumID][g_GameLogic.homeTeamBattingInd_fieldingTeam];
                r->nextBaseCoordinates.x = dugout->x;
                r->nextBaseCoordinates.z = dugout->z;
                d = sqrt13B8(r->velocity.x * r->velocity.x + r->velocity.z * r->velocity.z);
                if (d <= lbl_3_rodata_1414) {
                    r->velocity.x = lbl_3_rodata_1408;
                    r->velocity.z = lbl_3_rodata_1460;
                } else {
                    r->velocity.x /= d;
                    r->velocity.z /= d;
                }
                r->velocity.y = lbl_3_rodata_1414;
                r->velocity.x *= r->maximumBaseVelocity;
                r->velocity.z *= r->maximumBaseVelocity;
                r->runningToDugoutFrameCounter = 0;
                r->framesToReachDugout = lbl_3_data_4B54;
                r->runningToDugoutStage = 1;
            }
            if (r->runningToDugoutStage == 1) {
                r->framesToReachDugout -= 1;
                r->position.x += r->velocity.x;
                r->position.y += r->velocity.y;
                r->position.z += r->velocity.z;
                if (r->framesToReachDugout <= 0) {
                    walkToDugout13B8(r);
                }
            }
            if (r->runningToDugoutStage == 2) {
                stepToDugout13B8(r);
            }
            goto done;
        }
        if (r->runningToDugoutInd != 0) {
            if (r->runningToDugoutStage == 0) {
                walkToDugout13B8(r);
            }
            if (r->runningToDugoutStage == 2) {
                stepToDugout13B8(r);
            }
            goto done;
        }
    }
    // Normal running: straight-line point on the current leg, and the rounded path.
    px = r->currentBaseCoordinates.x + scaleValue(r->nextBaseCoordinates.x - r->currentBaseCoordinates.x, r->percentTowardsNextBase);
    py = r->currentBaseCoordinates.y + scaleValue(r->nextBaseCoordinates.y - r->currentBaseCoordinates.y, r->percentTowardsNextBase);
    pz = r->currentBaseCoordinates.z + scaleValue(r->nextBaseCoordinates.z - r->currentBaseCoordinates.z, r->percentTowardsNextBase);
    if (r->fractionalBasesRan < lbl_3_rodata_1408) {
        idx = 0;
        count = 4;
    } else if (r->fractionalBasesRan < lbl_3_rodata_140C) {
        idx = 3;
        count = 4;
    } else if (r->fractionalBasesRan < lbl_3_rodata_1410) {
        idx = 6;
        count = 4;
    } else if (g_GameLogic.secondaryGameMode == 6) {
        idx = 9;
        count = 4;
    } else {
        idx = 9;
        count = 3;
    }
    running_roundBasePosition(r->percentTowardsNextBase, &round, &lbl_3_data_4A54[g_GameLogic.secondaryGameMode == 6][idx], count);
    pos[0] = round.x;
    pos[2] = round.z;
    pos[1] = lbl_3_rodata_1414;
    if (r->overrunning1BIndicator != 0 && r->fractionalBasesRan < lbl_3_rodata_140C) {
        // Overrunning first base.
        if (r->runningDirectionCode == 1) {
            a = lbl_3_rodata_1408 - r->percentTowardsNextBase_stored;
            b = lbl_3_rodata_1408 - r->percentTowardsNextBase;
            legPoint13B8(r, pos, a, b, r->nextBaseCoordinates.x, r->nextBaseCoordinates.y, r->nextBaseCoordinates.z, px, py, pz);
        } else {
            a = -r->percentTowardsNextBase_stored;
            b = -r->percentTowardsNextBase;
            legPoint13B8(r, pos, a, b, r->currentBaseCoordinates.x, r->currentBaseCoordinates.y, r->currentBaseCoordinates.z, px, py, pz);
        }
        r->position.x = pos[0];
        r->position.y = pos[1];
        r->position.z = pos[2];
    } else if (r->offsetFromNormalRunningPathInd != 0 && r->roundingInitiaializedInd == 0) {
        // Blend from the straight line into the rounded path.
        if (r->runningDirectionCode != 2 && r->nextDirectionBeingProcessed == 0 && r->turningAroundInd != 1) {
            r->roundingStrengthPercent += lbl_3_data_4B24;
        }
        if (r->roundingStrengthPercent < lbl_3_rodata_1414) {
            r->roundingStrengthPercent = lbl_3_rodata_1414;
        }
        if (r->roundingStrengthPercent > lbl_3_rodata_1408) {
            r->roundingStrengthPercent = lbl_3_rodata_1408;
        }
        r->position.x = px + scaleValue(pos[0] - px, r->roundingStrengthPercent);
        r->position.y = py + scaleValue(pos[1] - py, r->roundingStrengthPercent);
        r->position.z = pz + scaleValue(pos[2] - pz, r->roundingStrengthPercent);
        r->offsetPositionForRoundingInd = 1;
        r->_110 = 0;
    } else {
        r->roundingStrengthPercent = lbl_3_rodata_1414;
        if (r->offsetPositionForRoundingInd == 0) {
            r->position.x = px;
            r->position.y = py;
            r->position.z = pz;
        } else {
            if (g_GameLogic.secondaryGameMode != 6) {
                r->roundingInitiaializedInd = 1;
            }
            if (r->runningDirectionCode == 1) {
                a = lbl_3_rodata_1408 - r->percentTowardsNextBase_stored;
                b = lbl_3_rodata_1408 - r->percentTowardsNextBase;
                if (b > a) {
                    a += lbl_3_rodata_1408;
                }
                legPoint13B8(r, pos, a, b, r->nextBaseCoordinates.x, r->nextBaseCoordinates.y, r->nextBaseCoordinates.z, px, py, pz);
            } else {
                a = -r->percentTowardsNextBase_stored;
                b = -r->percentTowardsNextBase;
                legPoint13B8(r, pos, a, b, r->currentBaseCoordinates.x, r->currentBaseCoordinates.y, r->currentBaseCoordinates.z, px, py, pz);
            }
            r->position.x = pos[0];
            r->position.y = pos[1];
            r->position.z = pos[2];
        }
    }
done:
    r->position.y = lbl_3_rodata_1414;
}
#endif

// .text:0x000810C4 size:0xCC mapped:0x806C0158
void fn_3_810C4(int idx, int base) {
    InMemRunnerType* r = &g_Runners[idx];
    int next = (base + 1) & 3;
    if (g_GameLogic.secondaryGameMode == 6) {
        f32* e = lbl_3_data_4B58[0];
        e += base * 3;
        r->runningAngle = e[2];
        r->percentTowardsNextBase = 0.0f;
    } else {
        r->percentTowardsNextBase = r->slidingAdjustment_backwards;
    }
    r->fractionalBasesRan = r->percentTowardsNextBase + base;
    r->baseStandingOn = base;
    r->currentBaseCoordinates.x = lbl_3_data_4A34[base * 2];
    r->currentBaseCoordinates.z = lbl_3_data_4A34[base * 2 + 1];
    r->nextBaseCoordinates.x = lbl_3_data_4A34[next * 2];
    r->nextBaseCoordinates.z = lbl_3_data_4A34[next * 2 + 1];
}

// .text:0x00081190 size:0x928 mapped:0x806C0224
extern const f32 lbl_3_rodata_1474;
// Stops runner r standing on base `base` and sets up the leg to the next base.
static inline void standOnBase13B8(InMemRunnerType* r, int base) {
    int next = (base + 1) & 3;
    if (g_GameLogic.secondaryGameMode == 6) {
        r->runningAngle = lbl_3_data_4B58[base][2];
        r->percentTowardsNextBase = lbl_3_rodata_1414;
    } else {
        r->percentTowardsNextBase = r->slidingAdjustment_backwards;
    }
    r->fractionalBasesRan = r->percentTowardsNextBase + (f32)base;
    r->baseStandingOn = base;
    r->currentBaseCoordinates.x = lbl_3_data_4A34[base * 2];
    r->currentBaseCoordinates.z = lbl_3_data_4A34[base * 2 + 1];
    r->nextBaseCoordinates.x = lbl_3_data_4A34[next * 2];
    r->nextBaseCoordinates.z = lbl_3_data_4A34[next * 2 + 1];
}

// Base arrival / touch handling for runner i.
// NONMATCHING 99.3%: branch layout of the status check, constant reload in the wrap-around path
#if NONMATCHING
void fn_3_81190(int i) {
    InMemRunnerType* r = &g_Runners[i];
    int stopBase = -1;
    int wrap = 0;
    s16 prevBase = r->baseStandingOn;
    int whole;
    f32 progress;

    if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 2 && r->runnerOnFieldOrOutOrScored != 4) {
        return;
    }
    if (r->groundVelocity[0] > lbl_3_rodata_1414) {
        whole = (int)r->fractionalBasesRan;
        if (whole > (int)r->fractionalBasesRan_stored) {
            if (r->baseRoundingState == 2) {
                r->fractionalBasesRan = (f32)whole;
                r->percentTowardsNextBase = lbl_3_rodata_1414;
                if (g_GameLogic.secondaryGameMode == 6) {
                    if (r->fractionalBasesRan >= lbl_3_rodata_1470) {
                        r->fractionalBasesRan = r->fractionalBasesRan - lbl_3_rodata_1470;
                    }
                } else if (r->runningDirectionDesired != 1) {
                    r->runningDirectionCode = 2;
                    r->nextDirectionBeingProcessed = 2;
                    r->overrunBaseStage = 1;
                }
            } else if (r->baseRoundingState == 1) {
                r->fractionalBasesRan = (f32)whole;
                r->percentTowardsNextBase = lbl_3_rodata_1414;
            } else if (r->actionCode != 0) {
                r->fractionalBasesRan = (f32)whole;
                r->percentTowardsNextBase = lbl_3_rodata_1414;
                if (r->runnerOnFieldOrOutOrScored != 1) {
                    fn_3_8307C(i);
                }
            } else {
                stopBase = whole & 3;
            }
        }
    } else if (r->groundVelocity[0] < lbl_3_rodata_1414) {
        if (g_GameLogic.secondaryGameMode == 6) {
            wrap = 1;
        }
        if (g_Ball.AtBat_ContactResult == 3 && r->tagUpInd == 2 && r->currentBase > r->startingBase_baseAchieved) {
            wrap = 1;
        }
        if (wrap != 0) {
            if (r->fractionalBasesRan < lbl_3_rodata_1414) {
                r->fractionalBasesRan = r->fractionalBasesRan + lbl_3_rodata_1470;
                r->percentTowardsNextBase = r->percentTowardsNextBase + lbl_3_rodata_1408;
            }
        } else if (r->percentTowardsNextBase <= r->slidingAdjustment_backwards) {
            if (r->actionCode != 0) {
                r->fractionalBasesRan = (f32)(int)r->fractionalBasesRan + r->slidingAdjustment_backwards;
                r->percentTowardsNextBase = r->slidingAdjustment_backwards;
            } else {
                stopBase = r->currentBase;
            }
        }
    }
    if (stopBase >= 0) {
        r->runningDirectionCode = 2;
        r->nextDirectionBeingProcessed = 2;
        r->groundVelocity[0] = lbl_3_rodata_1414;
        r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
        r->roundingStrengthPercent = lbl_3_rodata_1414;
        standOnBase13B8(r, stopBase);
    }
    if (!(r->runnerOnFieldOrOutOrScored == 1 || (r->runnerOnFieldOrOutOrScored == 4 && g_Ball.AtBat_ContactResult == -1))) {
        return;
    }
    // Which base (if any) the runner is touching.
    r->baseStandingOn = -1;
    progress = r->fractionalBasesRan;
    if (progress > lbl_3_rodata_1450 || g_GameLogic.secondaryGameMode == 6) {
        if (progress >= lbl_3_rodata_1470) {
            r->baseStandingOn = 0;
        } else if (r->percentTowardsNextBase <= r->slidingAdjustment_backwards) {
            r->baseStandingOn = (int)progress;
        } else if (r->percentTowardsNextBase >= lbl_3_rodata_1408 - r->slidingAdjustment_forwards) {
            r->baseStandingOn = ((int)progress + 1) & 3;
        }
    }
    if (r->baseStandingOn >= 0) {
        if (lbl_3_rodata_1414 == r->groundVelocity[0] && r->percentTowardsNextBase > lbl_3_rodata_1450) {
            standOnBase13B8(r, r->baseStandingOn);
        }
        if (r->baseStandingOn == g_Ball.baseBallAndFielderAreOn && prevBase == -1) {
            // Ball holder is on the base the runner just reached.
            g_FieldingLogic._125 = -1;
            if (g_FieldingLogic._116 == 1) {
                if (!(g_Pitcher.strikeOutOrWalk == 2 && (r->furthestBaseForcedToGoToOnWalk > r->currentBase || (r->forcedToAdvanceInd != 0 && r->currentBase == r->startingBase_baseAchieved)))) {
                    r->baseOfFailedBodyCheck = r->baseStandingOn;
                    r->baseStandingOn = -1;
                    g_FieldingLogic._111 = 1;
                    g_FieldingLogic._0E8 = i;
                }
            } else if (g_Strikes.outs < 3 && (r->tagUpInd != 2 || g_Ball.baseBallAndFielderAreOn == r->startingBase_baseAchieved)) {
                fn_3_59918(2, 0);
            }
        } else if (prevBase == -1 && g_Ball.framesSinceHit > 100 && g_Ball.fielderWBallIndex >= 0 &&
                   g_Ball.ballDistanceFromBase[r->baseStandingOn] < lbl_3_rodata_1474) {
            if (r->forceOutCd == 1) {
                fn_3_59918(2, 0);
            } else if (r->tagUpInd == 2) {
                fn_3_59918(2, 0);
            } else if (r->baseOfFailedBodyCheck < 0 && r->tagType != 2 && r->runnerOnFieldOrOutOrScored != 2 &&
                       (g_FieldingLogic._111 == 2 || g_FieldingLogic._111 == 4)) {
                fn_3_59918(2, 0);
            }
        }
        fn_3_8307C(i);
        if (r->baseStandingOn == r->startingBase_baseAchieved && r->tagUpInd == 2) {
            r->tagUpInd = 0;
        }
        if (r->runningDirectionCode == 1) {
            if (r->percentTowardsNextBase < lbl_3_rodata_1450) {
                r->roundingInitiaializedInd = 0;
                r->offsetPositionForRoundingInd = 0;
            }
        } else if (r->runningDirectionCode == 3) {
            if (r->percentTowardsNextBase > lbl_3_rodata_1450) {
                r->roundingInitiaializedInd = 0;
                r->offsetPositionForRoundingInd = 0;
            }
        } else {
            r->roundingInitiaializedInd = 0;
            r->offsetPositionForRoundingInd = 0;
        }
        r->overrunning1BIndicator = 0;
    }
    if (r->baseStandingOn == 0) {
        // Reached home.
        if (g_Strikes.outs < 3 && g_d_GameSettings.GameModeSelected != 7 &&
            (g_Ball.AtBat_ContactResult == 1 || g_Ball.AtBat_ContactResult == 2 || (g_Ball.AtBat_ContactResult == 3 && r->tagUpInd == 0) ||
             (g_Ball.AtBat_ContactResult == 0 && g_Strikes.storedOuts == 2) || g_Practice.practiceType_2 == 3)) {
            r->runningDirectionCode = 0;
            r->runnerOnFieldOrOutOrScored = 3;
            if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                r->runnerOnFieldOrOutOrScored = 4;
            } else if (g_Ball.deadBallReason != 0) {
                r->runnerOnFieldOrOutOrScored = 4;
            } else {
                g_Scores._9C += 1;
            }
            if (r->actionCode != 0) {
                r->runningToDugoutInd = 2;
            } else {
                r->runningToDugoutInd = 3;
            }
            r->runningToDugoutStage = 0;
        }
        if (r->actionCode != 0 && r->slideHomeFrames_CountDown == 0 && g_GameLogic.secondaryGameMode != 6) {
            r->slideHomeFrames_CountDown = lbl_3_data_4C54[0];
        }
    } else if (r->fractionalBasesRan >= lbl_3_rodata_1470 && g_GameLogic.EventTriggers_EndOfGame != 0 && r->actionCode != 0) {
        r->runningToDugoutInd = 2;
    }
}
#endif

// .text:0x00081AB8 size:0x34 mapped:0x806C0B4C
void fn_3_81AB8(int i) {
    InMemRunnerType* r = &g_Runners[i];
    r->runningDirectionCode = 2;
    r->nextDirectionBeingProcessed = 2;
    r->groundVelocity[0] = lbl_3_rodata_1414;
    r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
    r->roundingStrengthPercent = lbl_3_rodata_1414;
}

// .text:0x00081AEC size:0xDC mapped:0x806C0B80
void fn_3_81AEC(int i) {
    InMemRunnerType* r = &g_Runners[i];
    s16 n;
    f32 v;
    if (r->leadoffDurationFrames < 0x7FFE) {
        r->leadoffDurationFrames = r->leadoffDurationFrames + 1;
    } else {
        r->leadoffDurationFrames = 0x7FFF;
    }
    n = r->leadOffTotalFrameCountDown;
    if (n <= 0) {
        r->leadOffStatus = 2;
        r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
    } else {
        v = r->leadoffDistancePercent + r->slidingAdjustment_backwards;
        v -= r->percentTowardsNextBase;
        v /= (f32)n;
        r->percentRanPerFrame_slideAdj = v;
        r->percentTowardsNextBase = r->percentTowardsNextBase + v;
        r->fractionalBasesRan = (f32)r->startingBase_baseAchieved + r->percentTowardsNextBase;
        r->leadOffTotalFrameCountDown = r->leadOffTotalFrameCountDown - 1;
    }
}

// .text:0x00081BC8 size:0x2E4 mapped:0x806C0C5C
// 95%: only first block differs - orig hoists the 1468/4B44 const loads and stw 0x4330 above the sth 0x106 store
// NONMATCHING 95%: hoisted constant loads in the first block (see note above)
#if NONMATCHING
int fn_3_81BC8(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->runningDirectionDesired == 1) {
        r->nextDirectionBeingProcessed = 1;
        r->overrunBaseStage = 0;
        return 0;
    }
    if (r->overrunBaseStage == 1) {
        s16 t;
        r->overrunBaseStage = 2;
        r->overrunBaseFrames_countUp = 0;
        r->overrunBaseFrames_countDown = lbl_3_data_4B48[0];
        r->runningDirectionCode = 5;
        t = r->overrunBaseFrames_countDown;
        r->overrun1B_someDistConst_proportionPerFrame = lbl_3_data_4B44 / (f32)((t + 1) * (t / 2));
    }
    if (r->overrunBaseStage == 2) {
        s16 t;
        r->overrunBaseFrames_countUp = r->overrunBaseFrames_countUp + 1;
        r->overrunBaseFrames_countDown = r->overrunBaseFrames_countDown - 1;
        t = r->overrunBaseFrames_countDown;
        if (t < 0) {
            r->overrunBaseStage = 3;
            r->overrunBaseFrames_countUp = 0;
            r->overrunBaseFrames_countDown = lbl_3_data_4B48[1];
            r->overrun1B_someDistConst_proportionPerFrame = (r->slidingAdjustment_backwards - r->percentTowardsNextBase) / (f32) r->overrunBaseFrames_countDown;
        } else {
            r->percentRanPerFrame_slideAdj = r->overrun1B_someDistConst_proportionPerFrame * (f32)t;
        }
    }
    if (r->overrunBaseStage == 3) {
        r->overrunBaseFrames_countUp = r->overrunBaseFrames_countUp + 1;
        r->overrunBaseFrames_countDown = r->overrunBaseFrames_countDown - 1;
        if (r->overrunBaseFrames_countDown < 0) {
            s32 nx;
            s32 k;
            r->overrunBaseStage = 0;
            r->runningDirectionCode = 2;
            r->nextDirectionBeingProcessed = 2;
            r->groundVelocity[0] = lbl_3_rodata_1414;
            r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
            r->roundingStrengthPercent = lbl_3_rodata_1414;
            k = r->currentBase;
            nx = (k + 1) & 3;
            if (g_GameLogic.secondaryGameMode == 6) {
                f32* e = lbl_3_data_4B58[0];
                e += k * 3;
                r->runningAngle = e[2];
                r->percentTowardsNextBase = lbl_3_rodata_1414;
            } else {
                r->percentTowardsNextBase = r->slidingAdjustment_backwards;
            }
            r->fractionalBasesRan = r->percentTowardsNextBase + (f32)k;
            r->baseStandingOn = k;
            {
                f32* t0 = lbl_3_data_4A34;
                f32* t1 = t0 + 1;
                r->currentBaseCoordinates.x = t0[k * 2];
                r->currentBaseCoordinates.z = t1[k * 2];
                r->nextBaseCoordinates.x = t0[nx * 2];
                r->nextBaseCoordinates.z = t1[nx * 2];
            }
        } else {
            r->percentRanPerFrame_slideAdj = r->overrun1B_someDistConst_proportionPerFrame;
            r->offsetFromNormalRunningPathInd = 0;
        }
    }
    r->fractionalBasesRan = r->fractionalBasesRan + r->percentRanPerFrame_slideAdj;
    r->percentTowardsNextBase = r->percentTowardsNextBase + r->percentRanPerFrame_slideAdj;
    r->percentFromCurrentBase_slideAdj = r->percentTowardsNextBase - r->slidingAdjustment_backwards;
    r->percentTowardsNextBase_slideAdj = (lbl_3_rodata_1408 - r->percentTowardsNextBase) - r->slidingAdjustment_forwards;
    return 1;
}
#endif

// .text:0x00081EAC size:0x508 mapped:0x806C0F40
int fn_3_81EAC(int i) {
    InMemRunnerType* r = &g_Runners[i];
    f32 a;
    f32 b;
    f32 t;
    s16 h;
    if (r->fractionalBasesRan < lbl_3_rodata_1408) {
        return 0;
    }
    if (r->nextDirectionBeingProcessed == 1) {
        r->overRun1BStage = 0;
        r->runningDirectionCode = 2;
        r->overrunning1BIndicator = 1;
        a = sqrt13B8((lbl_3_data_4A34[2] - r->position.x) * (lbl_3_data_4A34[2] - r->position.x) + (lbl_3_data_4A34[3] - r->position.z) * (lbl_3_data_4A34[3] - r->position.z));
        b = sqrt13B8((lbl_3_data_4A34[4] - r->position.x) * (lbl_3_data_4A34[4] - r->position.x) + (lbl_3_data_4A34[5] - r->position.z) * (lbl_3_data_4A34[5] - r->position.z));
        t = (f32)(s32)(10000.0f * (a / (a + b))) / 10000.0f;
        r->percentTowardsNextBase = t;
        r->fractionalBasesRan = lbl_3_rodata_1408 + t;
        r->fractionalBasesRan_stored = r->fractionalBasesRan;
        r->percentTowardsNextBase_stored = r->percentTowardsNextBase;
        r->groundVelocity[0] = lbl_3_rodata_1414;
        r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
        r->percentFromCurrentBase_slideAdj = r->percentTowardsNextBase - r->slidingAdjustment_backwards;
        r->percentTowardsNextBase_slideAdj = (lbl_3_rodata_1408 - r->percentTowardsNextBase) - r->slidingAdjustment_forwards;
        return 1;
    }
    if (r->overRun1BStage == 1) {
        r->overRun1BStage = 2;
        r->overrunBaseFrames_countUp = 0;
        r->overrunBaseFrames_countDown = lbl_3_data_4B40[0];
        r->runningDirectionCode = 4;
        r->overrun1B_someDistConst_proportionPerFrame = lbl_3_rodata_1408 / (f32)((r->overrunBaseFrames_countDown + 1) * (r->overrunBaseFrames_countDown / 2));
        r->overrun1B_somePositionControl = lbl_3_rodata_1414;
    }
    if (r->overRun1BStage == 2) {
        r->overrunBaseFrames_countUp = r->overrunBaseFrames_countUp + 1;
        r->overrunBaseFrames_countDown = r->overrunBaseFrames_countDown - 1;
        h = r->overrunBaseFrames_countDown;
        if (h == 0) {
            r->overRun1BStage = 3;
            r->overrunBaseFrames_countUp = 0;
            r->overrunBaseFrames_countDown = lbl_3_data_4B40[1];
        } else {
            r->overrun1B_somePositionControl = r->overrun1B_someDistConst_proportionPerFrame * (f32)h + r->overrun1B_somePositionControl;
        }
    }
    if (r->overRun1BStage == 3) {
        r->overrunBaseFrames_countUp = r->overrunBaseFrames_countUp + 1;
        r->overrunBaseFrames_countDown = r->overrunBaseFrames_countDown - 1;
        if (r->overrunBaseFrames_countDown == 0) {
            r->runningDirectionCode = 2;
            r->overRun1BStage = 0;
            if (g_GameLogic.secondaryGameMode == 6) {
                r->runningAngle = lbl_3_data_4B58[1][2];
                r->percentTowardsNextBase = lbl_3_rodata_1414;
            } else {
                r->percentTowardsNextBase = r->slidingAdjustment_backwards;
            }
            r->fractionalBasesRan = r->percentTowardsNextBase + lbl_3_rodata_1408;
            r->baseStandingOn = 1;
            r->currentBaseCoordinates.x = lbl_3_data_4A34[2];
            r->currentBaseCoordinates.z = lbl_3_data_4A34[3];
            r->nextBaseCoordinates.x = lbl_3_data_4A34[4];
            r->nextBaseCoordinates.z = lbl_3_data_4A34[5];
            return 1;
        }
    }
    return 1;
}

// .text:0x000823B4 size:0x2BC mapped:0x806C1448
void fn_3_823B4(int i) {
    InMemRunnerType* r = &g_Runners[i];
    r->actionFrames_countUp = r->actionFrames_countUp + 1;
    r->actionFrames_countDown = r->actionFrames_countDown - 1;
    if (r->actionStage == 1) {
        f32 t;
        s16 n;
        if (r->actionInForwardDirectionInd != 0) {
            n = r->actionFrames_countDown;
            t = (lbl_3_rodata_1408 - r->slidingAdjustment_forwards) - r->percentTowardsNextBase;
            if (n <= 0) {
                r->percentRanPerFrame_slideAdj = lbl_3_rodata_1484 + t;
            } else {
                r->percentRanPerFrame_slideAdj = t / (f32)(n + 1);
            }
        } else {
            n = r->actionFrames_countDown;
            t = r->percentTowardsNextBase - r->slidingAdjustment_backwards;
            if (n <= 0) {
                r->percentRanPerFrame_slideAdj = -t - lbl_3_rodata_1484;
            } else {
                r->percentRanPerFrame_slideAdj = -t / (f32)(n + 1);
            }
        }
        if (r->actionFrames_countDown <= 0) {
            r->actionFrames_countUp = 0;
            r->actionFrames_countDown = lbl_3_data_7760[r->charID * 5 + 3];
            r->actionStage = 2;
            r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
            r->fractionalBasesRan = (f32)r->baseRunningTowards;
            r->percentTowardsNextBase = lbl_3_rodata_1414;
            if (r->baseRunningTowards == 0) {
                r->fractionalBasesRan = lbl_3_rodata_1470;
            }
            if (r->runnerOnFieldOrOutOrScored == 2) {
                r->actionStage = 3;
            }
        }
    } else if (r->actionStage == 2) {
        r->groundVelocity[0] = lbl_3_rodata_1414;
        r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
        if (r->actionFrames_countDown <= 0) {
            s32 nx;
            s16 k;
            r->actionCode = 0;
            r->actionStage = 0;
            if (r->baseStandingOn >= 0) {
                r->runningDirectionCode = 2;
                r->nextDirectionBeingProcessed = 2;
                r->groundVelocity[0] = lbl_3_rodata_1414;
                r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
                r->roundingStrengthPercent = lbl_3_rodata_1414;
                k = r->baseStandingOn;
                nx = (k + 1) & 3;
                if (g_GameLogic.secondaryGameMode == 6) {
                    {
                        f32* e = lbl_3_data_4B58[0];
                        e += k * 3;
                        r->runningAngle = e[2];
                    }
                    r->percentTowardsNextBase = lbl_3_rodata_1414;
                } else {
                    r->percentTowardsNextBase = r->slidingAdjustment_backwards;
                }
                r->fractionalBasesRan = r->percentTowardsNextBase + (f32)k;
                r->baseStandingOn = k;
                {
                    f32* t0 = lbl_3_data_4A34;
                    f32* t1 = t0 + 1;
                    r->currentBaseCoordinates.x = t0[k * 2];
                    r->currentBaseCoordinates.z = t1[k * 2];
                    r->nextBaseCoordinates.x = t0[nx * 2];
                    r->nextBaseCoordinates.z = t1[nx * 2];
                }
                r->framesSinceLastDirectionChange = 1;
            }
        }
    }
}

// .text:0x00082670 size:0x910 mapped:0x806C1704
extern f32 lbl_3_data_2191C[];
extern f32 lbl_3_data_4B88[];
extern const f32 lbl_3_rodata_1480;
// Per-frame baserunning movement for runner i: direction changes, speed and progress.
// NONMATCHING 99.7%: float register allocation / load order in the mash-speed update
#if NONMATCHING
void fn_3_82670(int i) {
    InMemRunnerType* r = &g_Runners[i];
    int prevTurn = r->turnaroundCode;
    f32 maxSpeed;
    f32 mult;
    f32 inv;
    int clamped;
    int q;

    if (lbl_3_common_bss_34C90.active != 0) {
        return;
    }
    r->groundVelocity[3] = r->groundVelocity[2];
    r->groundVelocity[2] = r->groundVelocity[1];
    r->groundVelocity[1] = r->groundVelocity[0];
    if (g_GameLogic.secondaryGameMode != 6) {
        if (i == 0 && r->delayBeforeStartingToRun > g_Ball.framesSinceHit) {
            return;
        }
        if (r->batterStayInBattersBoxReason == 3) {
            r->acceleration = lbl_3_rodata_1414;
            return;
        }
    }
    if (r->actionCode != 0) {
        fn_3_823B4(i);
    } else {
        if (r->overRun1BStage != 0 && fn_3_81EAC(i) != 0) {
            return;
        }
        if (r->overrunBaseStage != 0 && fn_3_81BC8(i) != 0) {
            return;
        }
        if (r->leadOffStatus == 1) {
            // Leading off.
            if (r->leadoffDurationFrames < 0x7FFE) {
                r->leadoffDurationFrames += 1;
            } else {
                r->leadoffDurationFrames = 0x7FFF;
            }
            if (r->leadOffTotalFrameCountDown <= 0) {
                r->leadOffStatus = 2;
                r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
            } else {
                inv = (r->leadoffDistancePercent + r->slidingAdjustment_backwards - r->percentTowardsNextBase) / (f32)r->leadOffTotalFrameCountDown;
                r->percentRanPerFrame_slideAdj = inv;
                r->percentTowardsNextBase += inv;
                r->fractionalBasesRan = (f32)r->startingBase_baseAchieved + r->percentTowardsNextBase;
                r->leadOffTotalFrameCountDown -= 1;
            }
            goto done;
        }
        if (r->slideHomeFrames_CountDown != 0) {
            return;
        }
        if (r->fractionalBasesRan >= lbl_3_rodata_1470) {
            return;
        }
        r->acceleration = lbl_3_rodata_1414;
        r->turnaroundCode = 0;
        if (r->framesSinceLastDirectionChange < 0x7FFE) {
            r->framesSinceLastDirectionChange += 1;
        } else {
            r->framesSinceLastDirectionChange = 0x7FFF;
        }
        // Acceleration from the requested direction (0x136) vs the current one (0x137).
        if (r->nextDirectionBeingProcessed == 1) {
            if (r->runningDirectionCode == 3) {
                r->acceleration = r->baseAccelerationWhileChaingingDirection * r->accelerationStaminaEffectWhileChangingDirection;
            } else {
                r->acceleration = r->baseAcceleration * r->accelerationStaminaEffect;
            }
        } else if (r->nextDirectionBeingProcessed == 2) {
            if (r->runningDirectionCode == 1) {
                r->acceleration = -(r->baseAccelerationWhileChaingingDirection * r->accelerationStaminaEffectWhileChangingDirection);
            } else if (r->runningDirectionCode == 3) {
                r->acceleration = r->baseAccelerationWhileChaingingDirection * r->accelerationStaminaEffectWhileChangingDirection;
            } else if (r->runningDirectionCode == 2) {
                r->groundVelocity[0] = lbl_3_rodata_1414;
            }
        } else if (r->nextDirectionBeingProcessed == 3) {
            if (r->runningDirectionCode == 1) {
                r->acceleration = -(r->baseAccelerationWhileChaingingDirection * r->accelerationStaminaEffectWhileChangingDirection);
            } else {
                r->acceleration = -(r->baseAcceleration * r->accelerationStaminaEffect);
            }
        } else {
            if (r->runningDirectionCode == 1) {
                r->acceleration = r->baseAcceleration * r->accelerationStaminaEffect;
            } else if (r->runningDirectionCode == 3) {
                r->acceleration = -(r->baseAcceleration * r->accelerationStaminaEffect);
            } else if (r->runningDirectionCode == 2) {
                r->groundVelocity[0] = lbl_3_rodata_1414;
            }
        }
        if (g_GameLogic.secondaryGameMode == 6) {
            mult = lbl_3_data_218BC[0x10] * (f32)g_Minigame.miniGameCurrentPoints[r->miniGamePlayerNum] + lbl_3_rodata_1408;
            if (mult > lbl_3_data_218BC[0x11]) {
                mult = lbl_3_data_218BC[0x11];
            }
            if ((s8)g_Minigame.playerIDWithPowerup[0] == i) {
                mult *= lbl_3_data_2191C[1];
            }
            maxSpeed = mult * (r->maximumBaseVelocity * r->staminaMult);
        } else if (r->stealingStatus != 0) {
            maxSpeed = lbl_3_data_4B88[1] * (r->maximumBaseVelocity * r->staminaMult);
        } else {
            maxSpeed = lbl_3_data_4B88[0] * (r->maximumBaseVelocity * r->staminaMult);
        }
        clamped = 0;
        r->groundVelocity[0] += r->acceleration;
        if (r->groundVelocity[0] > maxSpeed) {
            r->groundVelocity[0] = maxSpeed;
            clamped = 1;
        }
        if (r->groundVelocity[0] < -maxSpeed) {
            r->groundVelocity[0] = -maxSpeed;
            clamped = -1;
        }
        // Button mashing adds speed on top of the cap.
        if (clamped != 0) {
            if (r->newButtonThisFrame_forMashPurposes != 0) {
                r->framesSinceLastMash = r->FramesUntilNotSprinting;
                r->mashPercent += r->percentAddedPerMash;
                if (r->mashPercent > lbl_3_rodata_1408) {
                    r->mashPercent = lbl_3_rodata_1408;
                }
            } else if (r->framesSinceLastMash != 0) {
                r->framesSinceLastMash--;
            } else {
                r->mashPercent -= r->stamina_MashPercentTakenAwayPerFrame;
                if (r->mashPercent < lbl_3_rodata_1414) {
                    r->mashPercent = lbl_3_rodata_1414;
                }
            }
            r->mashVeloAdjustment = r->mashPercent * r->maxMashVeloAdjustment;
            if (clamped == 1 && r->acceleration > lbl_3_rodata_1414) {
                r->groundVelocity[0] += r->mashVeloAdjustment;
            } else if (r->acceleration < lbl_3_rodata_1414) {
                r->groundVelocity[0] -= r->mashVeloAdjustment;
            }
        } else {
            r->mashPercent = lbl_3_rodata_1414;
            r->framesSinceLastMash = 0;
        }
        // Commit a requested direction change once the speed allows it.
        if (r->nextDirectionBeingProcessed == 1) {
            if (r->groundVelocity[0] >= lbl_3_rodata_1414) {
                if (r->runningDirectionCode != 1) {
                    r->runnerDirectionCode_stored = r->runningDirectionCode;
                }
                r->runningDirectionCode = 1;
                r->nextDirectionBeingProcessed = 0;
                r->framesSinceLastDirectionChange = 0;
                if (prevTurn == 2 || r->groundVelocity[1] < lbl_3_rodata_1414 || r->groundVelocity[2] < lbl_3_rodata_1414 ||
                    r->groundVelocity[3] < lbl_3_rodata_1414) {
                    r->turningAroundInd = 1;
                    playSoundEffect(0x174);
                } else {
                    r->turningAroundInd = 0;
                }
                r->leadOffStatus = 0;
            } else {
                r->turnaroundCode = 2;
            }
        } else if (r->nextDirectionBeingProcessed == 2) {
            if ((r->runningDirectionCode == 1 && r->groundVelocity[0] < lbl_3_rodata_1414) ||
                (r->runningDirectionCode == 3 && r->groundVelocity[0] > lbl_3_rodata_1414) || r->groundVelocity[0] == lbl_3_rodata_1414) {
                if (r->runningDirectionCode != 2) {
                    r->runningDirectionCode = 2;
                    r->framesSinceLastDirectionChange = 0;
                }
                r->nextDirectionBeingProcessed = 0;
                r->groundVelocity[0] = lbl_3_rodata_1414;
                r->turningAroundInd = 0;
            } else {
                r->turnaroundCode = 1;
            }
        } else if (r->nextDirectionBeingProcessed == 3) {
            if (r->groundVelocity[0] <= lbl_3_rodata_1414) {
                if (r->runningDirectionCode != 3) {
                    r->runnerDirectionCode_stored = r->runningDirectionCode;
                }
                r->runningDirectionCode = 3;
                r->nextDirectionBeingProcessed = 0;
                r->framesSinceLastDirectionChange = 0;
                if (prevTurn == 2 || r->groundVelocity[1] > lbl_3_rodata_1414 || r->groundVelocity[2] > lbl_3_rodata_1414 ||
                    r->groundVelocity[3] > lbl_3_rodata_1414) {
                    r->turningAroundInd = 1;
                    playSoundEffect(0x174);
                } else {
                    r->turningAroundInd = 0;
                }
            } else {
                r->turnaroundCode = 2;
            }
        }
        if (r->runningDirectionCode == 1) {
            r->baseRunningTowards = r->nextBase;
        } else if (r->runningDirectionCode == 3) {
            if (r->baseStandingOn >= 0 && r->startingBase_baseAchieved == r->baseStandingOn && r->tagUpInd == 2) {
                r->baseRunningTowards = (r->currentBase + 3) & 3;
            } else {
                r->baseRunningTowards = r->currentBase;
            }
        }
        inv = lbl_3_rodata_1408 / r->calculatedLengthOfCurrentBaseline;
        r->percentRanPerFrame_slideAdj = r->groundVelocity[0] * inv;
        r->velocityPercent_stamAdj = inv * (r->maximumBaseVelocity * r->staminaMult);
        r->accelerationPercent_stamAdj = inv * (r->baseAcceleration * r->accelerationStaminaEffect);
    }
    // Advance, keeping the progress quantized to 1/10000 of a base.
    if (lbl_3_rodata_1414 != r->percentRanPerFrame_slideAdj) {
        q = (int)(lbl_3_rodata_1480 * (r->fractionalBasesRan + r->percentRanPerFrame_slideAdj));
        r->fractionalBasesRan = (f32)q / lbl_3_rodata_1480;
        r->percentTowardsNextBase = (f32)(q % 10000) / lbl_3_rodata_1480;
    }
done:
    r->percentFromCurrentBase_slideAdj = r->percentTowardsNextBase - r->slidingAdjustment_backwards;
    r->percentTowardsNextBase_slideAdj = lbl_3_rodata_1408 - r->percentTowardsNextBase - r->slidingAdjustment_forwards;
    if (r->overRun1BStage != 0) {
        fn_3_81EAC(i);
    }
}
#endif

// .text:0x00082F80 size:0xFC mapped:0x806C2014
void fn_3_82F80(int i, s16* b, s16* a) {
    InMemRunnerType* r = &g_Runners[i];
    s32 n = 0;
    s32 q;
    f32 step;
    f32 lim;
    f32 rem;
    f32 v;
    f32 s;
    f32 step2;
    f32 nl;
    f32 lim2;
    f32 rem2;
    f32 s2;
    rem = r->percentTowardsNextBase_slideAdj;
    if (rem > lbl_3_rodata_1414) {
        s = r->percentRanPerFrame_slideAdj;
        lim = r->velocityPercent_stamAdj;
        if (s < lim) {
            v = s;
            step = r->accelerationPercent_stamAdj;
            do {
                v += step;
                n++;
                if (v > lim) {
                    rem -= lim;
                    break;
                }
                rem -= v;
            } while (!(rem < lbl_3_rodata_1414));
        }
        n += (s32)(rem / lim) + 1;
    }
    *a = n;
    n = 0;
    rem2 = r->percentFromCurrentBase_slideAdj;
    if (rem2 > lbl_3_rodata_1414) {
        lim2 = r->velocityPercent_stamAdj;
        nl = -lim2;
        if ((s2 = r->percentRanPerFrame_slideAdj) > nl) {
            step2 = r->accelerationPercent_stamAdj;
            do {
                s2 -= step2;
                n++;
                if (s2 < nl) {
                    rem2 -= lim2;
                    break;
                }
                rem2 -= s2;
            } while (!(rem2 < lbl_3_rodata_1414));
        }
        n += (s32)(rem2 / lim2) + 1;
    }
    *b = n;
}

// .text:0x0008307C size:0x370 mapped:0x806C2110
void fn_3_8307C(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if ((r->runningToDugoutInd != 1 || r->runningToDugoutStage == 0) && g_Pitcher.pitcherActionState != 6) {
        s32 k;
        s32 nx;
        f32 a;
        f32 b;
        f32 dx;
        f32 dz;
        k = (s32) r->fractionalBasesRan;
        r->currentBaseCoordinates.y = lbl_3_rodata_1414;
        r->nextBaseCoordinates.y = lbl_3_rodata_1414;
        nx = (k + 1) % 4;
        if (g_GameLogic.secondaryGameMode == 6) {
            r->currentBaseCoordinates.x = lbl_3_data_4A34[k * 2];
            r->currentBaseCoordinates.z = lbl_3_data_4A34[k * 2 + 1];
        } else if (k + 1 == 1) {
            r->currentBaseCoordinates.x = g_Batter.batterPos.x;
            r->currentBaseCoordinates.z = g_Batter.batterPos.z;
        } else {
            r->currentBaseCoordinates.x = lbl_3_data_4A34[k * 2];
            r->currentBaseCoordinates.z = lbl_3_data_4A34[k * 2 + 1];
        }
        r->nextBaseCoordinates.x = lbl_3_data_4A34[nx * 2];
        r->nextBaseCoordinates.z = lbl_3_data_4A34[nx * 2 + 1];
        a = sqrt13B8((r->currentBaseCoordinates.x - r->position.x) * (r->currentBaseCoordinates.x - r->position.x) + (r->currentBaseCoordinates.z - r->position.z) * (r->currentBaseCoordinates.z - r->position.z));
        b = sqrt13B8((r->nextBaseCoordinates.x - r->position.x) * (r->nextBaseCoordinates.x - r->position.x) + (r->nextBaseCoordinates.z - r->position.z) * (r->nextBaseCoordinates.z - r->position.z));
        r->calculatedLengthOfCurrentBaseline = a + b;
        r->fractionOfCalculatedBaselineRan = a / (a + b);
        r->distToCurrentBase = a;
        r->distToNextBase = b;
        r->currentBase = k;
        r->nextBase = nx;
        fn_3_82F80(i, &r->framesToPreviousBase, &r->framesToNextBase);
    }
}

// .text:0x000833EC size:0x1C4 mapped:0x806C2480
void fn_3_833EC(int i) {
    InMemRunnerType* r;
    int v;
    fn_3_8307C(i);
    r = &g_Runners[i];
    if ((r->runningToDugoutInd == 0 || r->runningToDugoutStage == 0) && r->actionCode == 0) {
        if (r->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] || (r->runningDirectionCode != 1 && r->runningDirectionCode != 3)) {
            u8 s = r->runningDirectionDesired;
            if (s != 0) {
                if (g_GameLogic.secondaryGameMode == 6) {
                    if (r->runnerOnFieldOrOutOrScored == 1) {
                        r->nextDirectionBeingProcessed = s;
                    }
                } else {
                    if ((i != 0 || r->nextBase != 1) && r->runnerOnFieldOrOutOrScored == 1) {
                        r->nextDirectionBeingProcessed = s;
                    }
                    if (r->nextDirectionBeingProcessed == 3 && r->tagUpInd != 3 && r->baseStandingOn >= 0) {
                        r->nextDirectionBeingProcessed = 0;
                    }
                }
            }
        }
        v = fn_3_7FA78(i);
        if (v != 0) {
            r->nextDirectionBeingProcessed = v;
        }
    }
    if (r->runningToDugoutInd != 0) {
        r->baseRoundingState = 0;
        r->actionCode = 0;
    } else {
        fn_3_7ECFC(i);
        fn_3_7F494(i);
        if (g_GameLogic.secondaryGameMode != 6) {
            if (i == 0 && r->nextBase == 1) {
                fn_3_7F2D8();
            } else if (r->baseRoundingState == 1) {
                r->baseRoundingState = 0;
            }
            fn_3_7EBD4(i);
        }
    }
    fn_3_82670(i);
    fn_3_81190(i);
    fn_3_80028(i);
    fn_3_8307C(i);
}

// .text:0x000835B0 size:0x164 mapped:0x806C2644
// 99.5%: 12 diff lines, post-RandomInt_Game table temps (r0/r4/r5 allocation of idx*8 + DATA base)
// NONMATCHING 99.5%: register allocation of the AI table temps after RandomInt_Game
#if NONMATCHING
void fn_3_835B0(void) {
    AIStruct* ai;
    s32* t;
    s32 k;
    if (g_GameLogic._13E[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
        if (g_Controls[(s32)g_GameLogic.teams[g_GameLogic.teamBatting]].newButtonInput & 0xF00) {
            g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
            g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
        }
    } else {
        ai = &g_AiLogic;
        if (ai->_44 > 0) {
            t = (s32*)g_GameLogic.AIDifficulty0Special3Weak;
            if (g_Ball.framesSinceHit >= lbl_3_data_1C58[t[g_GameLogic.homeTeamBattingInd_fieldingTeam] * 4]) {
                if (ai->_77 != 0) {
                    ai->_77 = ai->_77 - 1;
                    return;
                }
                if (RandomInt_Game(0x64) < lbl_3_data_1C58[(k = t[g_GameLogic.homeTeamBattingInd_fieldingTeam] * 4) + 3]) {
                    g_Runners[0].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[1].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[2].newButtonThisFrame_forMashPurposes = 1;
                    g_Runners[3].newButtonThisFrame_forMashPurposes = 1;
                    ai->_44 = ai->_44 - 1;
                }
                ai->_77 = lbl_3_data_1C58[k + 2];
            }
        }
    }
}
#endif

// .text:0x00083714 size:0xAAC mapped:0x806C27A8
// 1 = go, -1 = hold: compares the runner's frames to the next base with the
// time the ball needs to get back (trajectory sample `traj`, frame `frame`).
static inline int runnerBeatsThrow13B8(InMemRunnerType* r, CoordAndDist* traj, int frame) {
    int eta;
    if (r->forceOutCd == 1) {
        return 1;
    }
    eta = frame + fn_3_A6810(traj->pos.x, traj->pos.z, BASE_XZ_13B8[r->nextBase].x, BASE_XZ_13B8[r->nextBase].z) + 45;
    if ((s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        eta -= 30;
    } else {
        eta += lbl_3_data_1C88[(s32)g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (g_Ball.ballZoneAwayFromHome <= 1) {
        if (eta - 20 > r->framesToNextBase) {
            return 1;
        }
    } else if (eta > r->framesToNextBase) {
        return 1;
    }
    return -1;
}

// CPU baserunning decisions for all runners (dec[k]: 1 advance, 0 stay, -1 return, -2 none).
// NONMATCHING 94%: register allocation and loop/pointer strength reduction differ
#if NONMATCHING
void fn_3_83714(void) {
    int dec[4];
    int level = 3;
    int frame = 0;
    int best;
    int k;
    int j;
    int t;
    int same;
    s16 hit;
    u8 st;
    InMemRunnerType* r;
    CoordAndDist* traj;
    int team;
    s16* ai;

    if (g_d_GameSettings.GameModeSelected == 2) {
        return;
    }
    if (g_GameLogic.gameStatus == 2 && g_GameLogic.FrameCountOfCurrentPitch < g_RunningLogic._14) {
        return;
    }
    if (g_FieldingLogic._10E != 0) {
        return;
    }
    if (g_Ball.framesSinceHit >= 0 && g_Ball.AtBat_ContactResult == 0) {
        level = fn_3_86118();
    } else if (g_Ball.AtBat_ContactResult == 1 || g_Ball.ballState == 3) {
        // Earliest frame any fielder can reach the ball's path.
        best = 9999;
        for (k = 0; k < 9; k++) {
            st = g_FieldingLogic._0F8[k];
            if (st == 1 || st == 10 || st == 11) {
                j = 1;
                do {
                    t = fn_3_52560(k, g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.z);
                    if (t < j + 15) {
                        break;
                    }
                    j += 5;
                } while (j < 120);
                if (j >= 120) {
                    if (best >= 120) {
                        best = 120;
                    }
                } else if (best > t) {
                    best = t;
                }
            }
        }
        frame = best;
    }
    hit = g_Ball.AtBat_ContactResult;
    if (g_Ball.framesSinceHit < 0) {
        hit = -2;
    }
    if (g_Ball.AtBat_ContactResult == 0 && g_Ball.hitClassification1 == 0) {
        hit = 1;
    }
    traj = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];
    for (k = 3; k >= 0; k--) {
        r = &g_Runners[k];
        dec[k] = -2;
        if (r->runnerOnFieldOrOutOrScored != 1 || r->unused_const_1 == 0 || g_Strikes.outs >= 3 || g_FieldingLogic._10E != 0) {
            continue;
        }
        if (k == 0 && g_Ball.framesSinceHit < r->delayBeforeStartingToRun) {
            dec[k] = 0;
        } else if (k == 0 && g_Ball.framesSinceHit == r->delayBeforeStartingToRun) {
            dec[k] = 1;
        } else if (g_Ball.deadBallReason == 1) {
            dec[k] = 1;
        } else if (k == 0 && g_Ball.framesSinceHit == -1) {
            dec[k] = 0;
        } else if (k == 0 && r->currentBase == 0) {
        } else if ((g_Ball.AtBat_ContactResult == 0 || g_Ball.AtBat_ContactResult == 1) && g_FieldingLogic._108 != 0) {
            dec[k] = -1;
        } else if (g_Ball.howFoulTheBallWillBe >= 2 && (g_Ball.numFieldersWhoHandledBallDuringPlay == 0 || g_Ball.bobbleLocation_1fair_2foul != 1)) {
            dec[k] = -1;
        } else if (g_Strikes.storedOuts == 2 && g_FieldingLogic._107 == 0 && r->currentBase == r->startingBase_baseAchieved) {
            dec[k] = 1;
        } else {
            if (hit == 3) {
                if (r->tagUpInd == 2) {
                    r->relatedToRunnerPos = 0;
                    dec[k] = -1;
                    r->unused_someBaseNum = -1;
                    continue;
                }
                for (j = 3; j > k; j--) {
                    if (g_Runners[j].runnerOnFieldOrOutOrScored == 1 && g_Runners[j].tagUpInd == 2) {
                        dec[k] = -1;
                        r->unused_someBaseNum = -1;
                    }
                }
            }
            if (hit == 3 && r->tagUpInd == 2) {
                dec[k] = -1;
            } else if (r->forceOutCd == 1 && hit >= 1 && hit <= 2) {
                dec[k] = 1;
            } else {
                if ((s8)r->unused_someBaseNum >= 0) {
                    if (g_Ball.AtBat_ContactResult == 3 && r->tagUpInd != 0) {
                        r->unused_someBaseNum = -1;
                    } else if ((s8)r->unused_someBaseNum == r->currentBase) {
                        r->unused_someBaseNum = -1;
                    } else if (r->actionCode != 0) {
                        r->unused_someBaseNum = -1;
                    } else {
                        dec[k] = 1;
                        continue;
                    }
                }
                // Forced if a runner behind is on the same base.
                same = 0;
                for (j = 0; j < k; j++) {
                    if (g_Runners[j].runnerOnFieldOrOutOrScored == 1 && r->currentBase == g_Runners[j].currentBase &&
                        (j != 0 || (g_Ball.AtBat_ContactResult != 0 && g_Ball.AtBat_ContactResult != 3))) {
                        same = 1;
                        break;
                    }
                }
                if (same != 0) {
                    dec[k] = 1;
                    continue;
                }
                if (!(r->fractionalBasesRan > lbl_3_rodata_1488)) {
                    if (r->distanceFromBall < lbl_3_rodata_143C && g_Ball.ballState == 3) {
                        r->relatedToRunnerPos = 0;
                    }
                    t = g_FieldingLogic._0C4;
                    if ((t == 5 || t == 6 || t == r->currentBase) && r->percentTowardsNextBase >= lbl_3_rodata_1490 && r->runningDirectionCode == 1 &&
                        g_Ball.ballZoneAwayFromHome <= 3) {
                        r->relatedToRunnerPos = 0;
                    }
                    if (r->baseStandingOn >= 0 && r->baseRoundingState == 2) {
                        r->relatedToRunnerPos = 1;
                        if (lbl_3_rodata_1414 == r->groundVelocity[0]) {
                            r->relatedToRunnerPos = 0;
                        }
                    }
                }
                t = fn_3_85840(k, level, dec);
                if (t == 1) {
                    if (g_Ball.framesSinceHit < 60 || g_Ball.AtBat_ContactResult == 0) {
                        dec[k] = 0;
                    } else {
                        dec[k] = -1;
                    }
                } else if (t == 2) {
                    dec[k] = 0;
                } else if (g_Ball.framesSinceHit == -1 || g_Ball.framesSinceHit < 10) {
                } else if (hit == 0) {
                    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
                        dec[k] = fn_3_85074(k, 5);
                    } else if (g_Ball.maxYOfHit <= lbl_3_rodata_1494) {
                        dec[k] = fn_3_84AD0(k, frame);
                    } else {
                        dec[k] = fn_3_85074(k, level);
                    }
                } else if (g_Ball.ballStoppingCode1ReallySlow2Stopped != 0 &&
                           (g_Ball.ballState == 3 || (g_Ball.AtBat_ContactResult == 1 && g_Ball.framesSinceHit > 400))) {
                    dec[k] = runnerBeatsThrow13B8(r, traj, frame);
                } else if (g_Ball.numberOfThrowsDuringPlay >= 1 && g_Ball.ballState == 3 &&
                           (g_Ball.ballVelocity < lbl_3_rodata_1498 || g_FieldingLogic._12C != 0)) {
                    dec[k] = runnerBeatsThrow13B8(r, traj, frame);
                } else if (hit == 1 || g_Ball.ballState == 3) {
                    dec[k] = fn_3_84AD0(k, frame);
                } else if (g_Ball.ballState == 1) {
                    dec[k] = fn_3_846C8(k);
                } else {
                    dec[k] = fn_3_842E4(k);
                }
            }
        }
    }
    for (k = 3; k >= 0; k--) {
        r = &g_Runners[k];
        t = dec[k];
        if (t != -2 && (r->baseRoundingState != 1 || r->overRun1BStage < 2 || t == 1)) {
            if (t == -1 && r->startingBase_baseAchieved == r->baseStandingOn) {
                t = 0;
            }
            fn_3_85EF4(k, t);
        }
    }
    team = g_GameLogic.homeTeamBattingInd_fieldingTeam;
    if (g_GameLogic.battingAIInd[team] == 0) {
        return;
    }
    if (g_GameLogic._13E[team] == 0) {
        // Human team: any steal button makes everyone mash.
        if (g_Controls[(s32)g_GameLogic.teams[g_GameLogic.teamBatting]].newButtonInput & 0xF00) {
            for (k = 0; k < 4; k++) {
                g_Runners[k].newButtonThisFrame_forMashPurposes = 1;
            }
        }
    } else if (g_AiLogic._44 > 0) {
        // CPU team: random mashing, with a cooldown.
        ai = &lbl_3_data_1C58[(s32)g_GameLogic.AIDifficulty0Special3Weak[team] * 4];
        if (g_Ball.framesSinceHit >= ai[0]) {
            if (g_AiLogic._77 != 0) {
                g_AiLogic._77--;
                return;
            }
            ai = &lbl_3_data_1C58[(s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam] * 4];
            if (RandomInt_Game(100) < ai[3]) {
                for (k = 0; k < 4; k++) {
                    g_Runners[k].newButtonThisFrame_forMashPurposes = 1;
                }
                g_AiLogic._44 -= 1;
            }
            g_AiLogic._77 = ai[2];
        }
    }
}
#endif

// .text:0x000841C0 size:0x124 mapped:0x806C3254
int fn_3_841C0(int i, int j) {
    InMemRunnerType* r = &g_Runners[i];
    int v;
    int k;
    if (r->forceOutCd == 1) {
        return 1;
    }
    k = r->nextBase;
    v = j + fn_3_A6810(g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.z, lbl_3_data_4444[k * 2], lbl_3_data_4444[k * 2 + 1]);
    v += 0x2D;
    if ((s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        v -= 0x1E;
    } else {
        v += lbl_3_data_1C88[(s32)g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (g_Ball.ballZoneAwayFromHome <= 1) {
        if (v - 0x14 > r->framesToNextBase) {
            return 1;
        }
    } else if (v > r->framesToNextBase) {
        return 1;
    }
    return -1;
}

// .text:0x000842E4 size:0x3E4 mapped:0x806C3378
int fn_3_842E4(int i) {
    s32 idx;
    s32 y;
    u8 s;
    s32* t;
    s32 fl;
    s32 b;
    s32 a;
    f32* t4;
    u8* f1c;
    u8* f14;
    InMemRunnerType* r;
    s32 x;
    g_FieldingLogic_s* fp;
    r = &g_Runners[i];
    if (g_Ball.throwTimeEstimatesCompleteInd == 0) {
        return -2;
    }
    b = r->nextBase;
    a = r->currentBase;
    x = g_Ball.framesUntilThrowReachesDest;
    t = (s32*)g_GameLogic.AIDifficulty0Special3Weak;
    if (t[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        x -= 0x1E;
    } else {
        x += lbl_3_data_1C88[(s32)g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    s = r->runningDirectionCode;
    if (s == 1 && r->percentTowardsNextBase > lbl_3_rodata_1430) {
        r->baseRunningTowards = b;
        return -2;
    }
    if (s == 3 && r->percentTowardsNextBase < lbl_3_rodata_1458 && g_Ball.ballZoneAwayFromHome <= 3) {
        r->baseRunningTowards = a;
        return -2;
    }
    fl = g_FieldingLogic._0C4;
    if (r->baseStandingOn == fl) {
        return (fl == a) ? -1 : 0;
    }
    if (s == 1 && fl == b) {
        if (r->percentTowardsNextBase >= lbl_3_rodata_149C) {
            x += 0x1E;
            if ((u8)a == 3) {
                x += 0x14;
            }
        }
        if (r->framesToNextBase < x) {
            return 1;
        }
        if (g_FieldingLogic._119 != 0) {
            s32 m = t[g_GameLogic.teamBatting] + 5;
            if (g_Ball.StaticRandomInt1 % m != 0) {
                return 1;
            }
        }
        return -1;
    }
    if (s == 3 && fl == a) {
        if (r->percentTowardsNextBase <= lbl_3_rodata_149C) {
            x += 0xF;
        }
        if (r->framesToPreviousBase < x) {
            return -1;
        }
        if (g_FieldingLogic._119 != 0) {
            s32 m = t[g_GameLogic.teamBatting] + 5;
            if (g_Ball.StaticRandomInt1 % m != 0) {
                return -1;
            }
        }
        return 1;
    }
    if (fl == 6) {
        fp = &g_FieldingLogic;
        // byte pointers into g_Fielders[0], stepped by idx = fielder * sizeof(InMemFielderType)
        f14 = (u8*)&g_Fielders[0].dest.x;
        f1c = (u8*)&g_Fielders[0].dest.z;
        t4 = lbl_3_data_4444 + 1;
        idx = fp->_0BE * sizeof(InMemFielderType);
        y = x + fn_3_A6810(*(f32*)(f14 + idx), *(f32*)(f1c + idx), lbl_3_data_4444[b * 2], t4[b * 2]);
        y += 0x1E;
        if (b == 0) {
            y += 0xF;
            if (g_Strikes.outs >= 2) {
                y += 0xA;
            }
        }
        if (r->percentTowardsNextBase >= lbl_3_rodata_1450) {
            y += 0xF;
        } else if (r->percentTowardsNextBase >= lbl_3_rodata_14A0) {
            y += 5;
        }
        if (r->framesToNextBase < y) {
            if (r->fractionalBasesRan >= lbl_3_rodata_14A4 && g_Ball.ballZoneAwayFromHome >= 3) {
                r->unused_someBaseNum = 0;
            }
            return 1;
        }
        if (r->baseRoundingState == 2 && r->overrunBaseStage == 2) {
            idx = fp->_0BE * 0x268;
            y = x + 0x14 + fn_3_A6810(*(f32*)(f14 + idx), *(f32*)(f1c + idx), lbl_3_data_4444[a * 2], t4[a * 2]);
            return (r->framesToPreviousBase > y) ? -1 : -2;
        }
        return -1;
    }
    return -2;
}

// .text:0x000846C8 size:0x408 mapped:0x806C375C
int fn_3_846C8(int i) {
    InMemRunnerType* r = &g_Runners[i];
    u8 bb;
    s32 b;
    s32 a;
    u8 s;
    s16* fa;
    f32* t4;
    s32 bi;
    s32 d1;
    s32 d2;
    s32 x;
    s32 e;
    s32 ea;
    s32 ec;
    u8 bb2;
    bb = g_Ball.ballZoneAwayFromHome;
    b = r->nextBase;
    a = r->currentBase;
    if (bb <= 2 && r->baseStandingOn >= 0) {
        return 0;
    }
    if (bb >= 3 && r->percentTowardsNextBase >= lbl_3_rodata_14A8 && r->runningDirectionCode == 1 && r->baseRoundingState == 2) {
        r->unused_someBaseNum = 0;
        return 1;
    }
    s = r->runningDirectionCode;
    if (s == 1 && r->percentTowardsNextBase > lbl_3_rodata_1430 && r->baseStandingOn < 0) {
        return -2;
    }
    if (s == 3 && r->percentTowardsNextBase < lbl_3_rodata_1458 && bb <= 2) {
        return -2;
    }
    fa = g_FieldingLogic._0D0;
    bi = fa[b];
    if (bi == g_Ball.fielderWBallIndex) {
        return -1;
    }
    bi = fa[a];
    if (bi == g_Ball.fielderWBallIndex) {
        return 1;
    }
    if (g_FieldingLogic._0CC != -1 && bb <= 2) {
        s32 v = fn_3_85A70(i);
        if (v != -2) {
            return v;
        }
    }
    t4 = lbl_3_data_4444 + 1;
    d1 = fn_3_A6ABC(lbl_3_data_4444[b * 2], t4[b * 2]);
    d2 = fn_3_A6ABC(lbl_3_data_4444[a * 2], t4[a * 2]);
    if ((s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        x = d1 - 0x1E;
    } else {
        x = d1 + lbl_3_data_1C88[(s32)g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (g_FieldingLogic._0C4 >= 0) {
        e = 0x1E - g_FieldingLogic._0F0;
        if (e > 0) {
            x += e;
            d2 += e;
        }
    } else {
        x += 0x1E;
        d2 += 0x1E;
    }
    if (r->runningDirectionCode == 1 && r->percentTowardsNextBase > lbl_3_rodata_1450) {
        x += 0x28;
        if (r->currentBase == 3) {
            x += 0x14;
        }
    } else if (r->runningDirectionCode == 1) {
        if (r->baseRoundingState != 1 || r->overrunBaseStage != 2) {
            if (r->percentTowardsNextBase >= lbl_3_rodata_14A0) {
                x += 0x14;
            }
        }
    }
    ea = r->framesToNextBase;
    if (x > ea) {
        if (i == 3 && g_Ball.AtBat_ContactResult == 3 && g_Ball.timeSinceBallPickedUp <= 1 && g_Ball.numberOfThrowsDuringPlay == 1) {
            r->unused_someBaseNum = 0;
        }
        return 1;
    }
    bb2 = g_Ball.ballZoneAwayFromHome;
    if (bb2 >= 3 && i >= 1 && r->currentBase == r->startingBase_baseAchieved && g_Ball.AtBat_ContactResult != 3 && x > ea - 0x14) {
        return 1;
    }
    if (r->currentBase == 3 && bb2 >= 3 && g_Ball.AtBat_ContactResult != 3) {
        if (x > ea - 0x14) {
            return 1;
        }
        if (x > ea - 0x1E && g_Strikes.outs >= 2) {
            return 1;
        }
    }
    ec = r->framesToPreviousBase;
    if (d2 > ec) {
        if (r->baseRoundingState == 2 && r->overrunBaseStage == 2 && d2 - 0x14 > ec) {
            return -2;
        }
        return -1;
    }
    return (x - ea > d2 - ec) ? 1 : -1;
}

// .text:0x00084AD0 size:0x5A4 mapped:0x806C3B64
extern const f32 lbl_3_rodata_14AC;
extern const f32 lbl_3_rodata_14B0;
extern const f32 lbl_3_rodata_14B4;
extern const f32 lbl_3_rodata_14B8;
// NONMATCHING 96%: fielder loop not unrolled the same way, register allocation, constant reload
#if NONMATCHING
int fn_3_84AD0(int i, int frame) {
    InMemRunnerType* r = &g_Runners[i];
    int eta;
    f32 best;
    int bestK;
    f32 ballDist;
    s16 ballFrames;
    s16 ballPos;
    InMemFielderType* f;
    int k;

    if (r->forceOutCd == 1) {
        return 1;
    }
    if (i == 3 && g_RunningLogic.occupiedBases == 0x1011) {
        r->unused_someBaseNum = 0;
        return 1;
    }
    if ((g_FieldingLogic._107 == 3 || g_FieldingLogic._107 == 4) && r->currentBase == r->startingBase_baseAchieved) {
        r->unused_someBaseNum = r->nextBase;
        return 1;
    }
    eta = frame + fn_3_A6810(g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z,
                             BASE_XZ_13B8[r->nextBase].x, BASE_XZ_13B8[r->nextBase].z);
    eta += 20;
    if ((s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.awayTeamBattingInd_battingTeam] >= 3) {
        eta -= 30;
    } else {
        eta += lbl_3_data_1C88[(s32)g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (i == 2) {
        ballFrames = g_Ball.framesSinceHit;
        if (ballFrames < 100 && g_Runners[3].runnerOnFieldOrOutOrScored == 0) {
            ballPos = g_Ball.Hit_HorizontalAngle;
            if (ballPos > 0x2A8 && ballPos < 0x30C) {
                if (eta + 45 > r->framesToNextBase) {
                    r->unused_someBaseNum = 3;
                    return 1;
                }
                if (ballFrames < 60 && g_Ball.ballZoneAwayFromHome <= 1) {
                    return 0;
                }
            }
            if (ballPos > 0x3A0 && ballPos < 0x460 && ballFrames < 60 && g_Ball.ballZoneAwayFromHome <= 1) {
                return 0;
            }
            if (g_Ball.maybeBuntInd != 0 && ballFrames < 60) {
                r->unused_someBaseNum = 3;
                return 1;
            }
        }
    }
    if (g_Ball.ballZoneAwayFromHome >= 3) {
        if (r->fractionalBasesRan >= lbl_3_rodata_14AC && r->runningDirectionCode == 1) {
            r->unused_someBaseNum = 0;
            return 1;
        }
        if (r->currentBase == r->startingBase_baseAchieved && eta > r->framesToNextBase - 30) {
            return 1;
        }
        if (eta > r->framesToNextBase) {
            return 1;
        }
        return -2;
    }
    best = lbl_3_rodata_14B0;
    bestK = -1;
    if (g_Ball.someCollisionInd != 0) {
        ballDist = g_Ball.ballDistanceFromHome;
        for (k = 2; k < 6; k++) {
            f = &g_Fielders[k];
            if (!(ballDist > lbl_3_rodata_1410 + f->_070) && f->_07C < best) {
                best = f->_07C;
                bestK = k;
            }
        }
        if (best < lbl_3_rodata_1410) {
            k = bestK;
            if (g_Fielders[k]._070 > ballDist && (r->runningDirectionCode == 3 || r->runningDirectionCode == 2)) {
                if (fn_3_A6810(g_Fielders[k].pos.x, g_Fielders[k].pos.x, BASE_XZ_13B8[r->currentBase].x, BASE_XZ_13B8[r->currentBase].z) <
                    r->framesToPreviousBase - 20) {
                    return -1;
                }
            }
        }
    }
    if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballVelocity > lbl_3_rodata_1450 &&
        g_Ball.ballDistanceFromHome > lbl_3_rodata_14B4) {
        if (bestK >= 0) {
            if (g_Fielders[bestK]._070 - g_Ball.ballDistanceFromHome < best) {
                return 1;
            }
        } else {
            return 1;
        }
    }
    if (g_Ball.ballZoneAwayFromHome >= 2 || bestK == -1) {
        if (r->fractionalBasesRan >= lbl_3_rodata_14B8 && r->runningDirectionCode == 1) {
            r->unused_someBaseNum = 0;
            return 1;
        }
        if (r->currentBase == r->startingBase_baseAchieved && eta > r->framesToNextBase - 30) {
            return 1;
        }
        if (g_Ball.someCollisionInd != 0) {
            if (eta > r->framesToNextBase + 30) {
                return 1;
            }
            if (r->percentTowardsNextBase > lbl_3_rodata_1450) {
                return 1;
            }
            return -1;
        }
        if (g_Ball.ballState == 3) {
            if (eta > r->framesToNextBase + 20) {
                return 1;
            }
            if (r->percentTowardsNextBase > lbl_3_rodata_1450) {
                return 1;
            }
            return -1;
        }
    }
    return 0;
}
#endif

// .text:0x00085074 size:0x6D0 mapped:0x806C4108
extern const f32 lbl_3_rodata_14C0;
extern const f32 lbl_3_rodata_14C4;
extern const f32 lbl_3_rodata_14C8;
extern const f32 lbl_3_rodata_1474;
// NONMATCHING 92%: expression/scheduling order around the fn_3_A6810 eta calls, register allocation
#if NONMATCHING
int fn_3_85074(int i, int b) {
    InMemRunnerType* r = &g_Runners[i];
    int next = r->nextBase;
    int cur = r->currentBase;
    int eta;
    int lim;
    f32 dx;
    f32 dz;
    f32 reach3;
    f32 reach5;

    if (g_Ball.pauseBallMovementWhenInPlant == 0 && g_Ball.hitClassification1 == 0) {
        if (r->forceOutCd == 1) {
            return 1;
        }
        return -1;
    }
    if (g_Strikes.outs == 2) {
        return 1;
    }
    if (g_Ball.landingSpotZoneAwayFromHome <= 1) {
        if (g_Ball.maxYOfHit >= lbl_3_rodata_14BC) {
            return -1;
        }
        if (g_Ball.maxYOfHit < lbl_3_rodata_140C && r->forceOutCd == 1) {
            return 1;
        }
        if (b <= 2) {
            return -1;
        }
        if (r->forceOutCd == 1) {
            return 1;
        }
        eta = fn_3_A6810(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, BASE_XZ_13B8[next].x, BASE_XZ_13B8[next].z);
        if (g_Ball.framesUntilBallHitsGround + eta + 30 > r->framesToNextBase) {
            return 1;
        }
        return -1;
    }
    if (b >= 6) {
        return 1;
    }
    if (b >= 5 && g_Ball.someCollisionVariable >= 2 && g_Ball.landingSpotZoneAwayFromHome < 3) {
        return 1;
    }
    if (i == 3) {
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_14C0) {
            return -1;
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > lbl_3_rodata_14C4 && b <= 5) {
            return -1;
        }
    }
    if (i == 2 && b <= 1) {
        dx = BASE_XZ_13B8[3].x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        dz = BASE_XZ_13B8[3].z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        if (sqrt13B8(dx * dx + dz * dz) > lbl_3_rodata_14C8 && g_Ball.ballAngleFromHome < 0x48C) {
            return -1;
        }
    }
    if (g_Ball.framesUntilBallHitsGround < 60 && i != 0) {
        if (b <= 2 || (b == 3 && g_Ball.landingSpotZoneAwayFromHome <= 2)) {
            eta = fn_3_A6810(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, BASE_XZ_13B8[cur].x, BASE_XZ_13B8[cur].z);
            if (r->framesToPreviousBase > g_Ball.framesUntilBallHitsGround + eta) {
                return -1;
            }
        }
        if (b >= 4) {
            if (i == 3 && b == 4 && g_Ball.landingSpotZoneAwayFromHome >= 4) {
                return -1;
            }
            if (b >= 5) {
                if (r->forceOutCd != 0) {
                    return 1;
                }
                if (g_Ball.maxYOfHit < lbl_3_rodata_1474 && g_Ball.ballVelocity > lbl_3_rodata_1450) {
                    reach3 = g_Fielders[3]._07C;
                    reach5 = g_Fielders[5]._07C;
                    if (reach3 < reach5) {
                        if (g_Ball.ballDistanceFromHome - lbl_3_rodata_140C > g_Fielders[3]._070 &&
                            reach3 > lbl_3_rodata_1410) {
                            return 1;
                        }
                        if (reach3 > lbl_3_rodata_1470 && g_Ball.ballDistanceFromHome + reach3 > g_Fielders[3]._070) {
                            return 1;
                        }
                    } else {
                        if (g_Ball.ballDistanceFromHome - lbl_3_rodata_140C > g_Fielders[5]._070) {
                            return 1;
                        }
                        if (reach5 > lbl_3_rodata_1470 && g_Ball.ballDistanceFromHome + reach5 > g_Fielders[5]._070) {
                            return 1;
                        }
                    }
                }
                eta = fn_3_A6810(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, BASE_XZ_13B8[next].x, BASE_XZ_13B8[next].z);
                if (g_Ball.framesUntilBallHitsGround + eta + 30 > r->framesToNextBase) {
                    return 1;
                }
            }
        }
    }
    if (i != 0) {
        eta = fn_3_A6810(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, BASE_XZ_13B8[cur].x, BASE_XZ_13B8[cur].z);
        if (g_Ball.framesUntilBallHitsGround < 45) {
            lim = r->framesToPreviousBase + 30;
        } else {
            lim = r->framesToPreviousBase + 15;
        }
        if (lim > eta) {
            return 0;
        }
        if (r->runningDirectionCode == 2 && lim + 5 > eta) {
            return 0;
        }
        if (!(lbl_3_rodata_1430 + r->startingBase_baseAchieved <= r->fractionalBasesRan)) {
            return 1;
        }
        if (b >= 5 && g_Ball.ballDistanceFromHome > lbl_3_rodata_1410 + g_Fielders[6]._070 &&
            g_Ball.ballDistanceFromHome > lbl_3_rodata_1410 + g_Fielders[7]._070 &&
            g_Ball.ballDistanceFromHome > lbl_3_rodata_1410 + g_Fielders[8]._070) {
            return 1;
        }
        return 0;
    }
    eta = fn_3_A6810(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z, BASE_XZ_13B8[next].x, BASE_XZ_13B8[next].z);
    eta = g_Ball.framesUntilBallHitsGround + eta + 30;
    if (r->overRun1BStage != 0) {
        return -2;
    }
    if (eta > r->framesToNextBase) {
        return 1;
    }
    return -2;
}
#endif

// .text:0x00085744 size:0xFC mapped:0x806C47D8
void fn_3_85744(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->fractionalBasesRan > lbl_3_rodata_1488) {
        return;
    }
    if (r->distanceFromBall < lbl_3_rodata_143C && g_Ball.ballState == 3) {
        r->relatedToRunnerPos = 0;
    }
    if (g_FieldingLogic._0C4 == 5 || g_FieldingLogic._0C4 == 6 ||
        g_FieldingLogic._0C4 == r->currentBase) {
        if (r->percentTowardsNextBase >= lbl_3_rodata_1490 && r->runningDirectionCode == 1 && g_Ball.ballZoneAwayFromHome <= 3) {
            r->relatedToRunnerPos = 0;
        }
    }
    if (r->baseStandingOn >= 0 && r->baseRoundingState == 2) {
        r->relatedToRunnerPos = 1;
        if (lbl_3_rodata_1414 == r->groundVelocity[0]) {
            r->relatedToRunnerPos = 0;
        }
    }
}

// .text:0x00085840 size:0x230 mapped:0x806C48D4
// 97%: logic matches; register roles differ (arr copied to r10 and bc4 lands in r5; original keeps arr in r5, bc4 in r11, temp r10)
// NONMATCHING 97%: register roles of arr/temps (see note above)
#if NONMATCHING
int fn_3_85840(int i, int b, int* arr) {
    u8 bc9;
    InMemRunnerType* r;
    s16 b7a;
    u8 sf;
    u8 bc4;
    InMemRunnerType* self;
    int j;
    self = &g_Runners[i];
    sf = self->nextBase;
    if ((s32)sf == 0) {
        return 0;
    }
    j = i + 1;
    r = &g_Runners[j];
    arr += j;
    bc9 = g_Ball.ballState;
    b7a = g_Ball.AtBat_ContactResult;
    bc4 = g_Ball.hitClassification2;
    for (; j < 4; j++, r++, arr++) {
        u8 t;
        u8 u;
        if (r->runnerOnFieldOrOutOrScored == 1) {
            t = r->currentBase;
            if (t == self->currentBase) {
                if (r->baseRoundingState == 2 && r->overrunBaseStage == 3) {
                    return 1;
                }
                u = r->runningDirectionCode;
                if (u == 3) {
                    return 1;
                }
                if (u == 2 && r->fractionalBasesRan - self->fractionalBasesRan < (*(f32*)&lbl_3_rodata_1440)) {
                    return 2;
                }
                if (bc9 != 0) {
                    return 1;
                }
                if (i == 0 && b7a == 0) {
                    f32 f = self->fractionalBasesRan;
                    if (f > (*(f32*)&lbl_3_rodata_1408) && b <= 3 && r->fractionalBasesRan < f) {
                        return 2;
                    }
                }
            }
            if (t == sf) {
                if (b7a == 0) {
                    if (bc4 <= 4 && r->percentTowardsNextBase < (*(f32*)&lbl_3_rodata_1450)) {
                        if (self->forceOutCd == 1 && b > 3) {
                            return 0;
                        }
                        u = r->runningDirectionCode;
                        if (u == 3 || u == 2) {
                            return 1;
                        }
                    }
                } else if (r->percentTowardsNextBase < (*(f32*)&lbl_3_rodata_1450) && arr[0] <= 0) {
                    u = r->runningDirectionCode;
                    if (u == 2 || u == 3 || (u == 1 && r->nextDirectionBeingProcessed == 3)) {
                        return 1;
                    }
                    if (r->baseRoundingState == 2 && r->overrunBaseStage >= 2) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
#endif

// .text:0x00085A70 size:0x1D4 mapped:0x806C4B04
int fn_3_85A70(int i) {
    InMemRunnerType* r = &g_Runners[i];
    int a;
    int b;
    int y1;
    int y2;
    int st;
    u8 k;
    int w;
    int s2;
    int res;
    s16 e;
    s16 g;
    st = g_FieldingLogic._0CC;
    if (st == 9 && g_FieldingLogic._0DE != i) {
        return -2;
    }
    if (r->baseStandingOn >= 0) {
        return -2;
    }
    a = r->nextBase;
    b = r->currentBase;
    if (a == g_FieldingLogic._0DC && (st == b || st == 9)) {
        return -1;
    }
    if (b == g_FieldingLogic._0DC && (st == a || st == 9)) {
        return 1;
    }
    y1 = fn_3_52560(g_Ball.fielderWBallIndex, lbl_3_data_4444[a * 2], lbl_3_data_4444[a * 2 + 1]);
    y2 = fn_3_52560(g_Ball.fielderWBallIndex, lbl_3_data_4444[b * 2], lbl_3_data_4444[b * 2 + 1]);
    e = r->framesToNextBase;
    g = r->framesToPreviousBase;
    s2 = g_FieldingLogic._0CC;
    if (s2 == 9) {
        k = r->runningDirectionCode;
        if (k == 1 || k == 2) {
            if (e < y1) {
                return 1;
            }
            return -1;
        }
        res = 1;
        if (g < y2) {
            res = -1;
        }
        return res;
    }
    if (r->distanceFromBall > 20.0f) {
        return -2;
    }
    k = r->runningDirectionCode;
    w = r->currentBase;
    if (k == 1 || k == 2) {
        w = r->nextBase;
    }
    if (w != s2) {
        return -2;
    }
    if (k == 1) {
        res = -1;
        if (e <= y1) {
            res = 1;
        }
        return res;
    }
    res = 1;
    if (g <= y2) {
        res = -1;
    }
    return res;
}

// .text:0x00085C44 size:0x6C mapped:0x806C4CD8
#pragma dont_inline off
static inline void h85C44(InMemRunnerType* r, s32 i, s32 d) {
    if (r->baseRoundingState == 1 && r->overRun1BStage >= 2 && d != 1) {
        return;
    }
    if (d == -1) {
        if (r->startingBase_baseAchieved == r->baseStandingOn) {
            d = 0;
        }
    }
    fn_3_85EF4(i, d);
}

void fn_3_85C44(s32 i, s32 d) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->baseRoundingState == 1 && r->overRun1BStage >= 2 && d != 1) {
        return;
    }
    if (d == -1) {
        if (r->startingBase_baseAchieved == r->baseStandingOn) {
            d = 0;
        }
    }
    fn_3_85EF4(i, d);
}

// .text:0x00085CB0 size:0x244 mapped:0x806C4D44
void fn_3_85CB0(void) {
    InMemRunnerType* r;
    InMemRunnerType* q;
    int j;
    int i;
    if (g_Ball.pitchHangtimeCounter <= 0x1E && g_Pitcher.pitcherActionState == 2) {
        if (g_Strikes.outs == 2 && g_Strikes.GameControls_StrikeBallBitVector == 0x23) {
            for (i = 1, r = &g_Runners[1]; i <= 3; i++, r++) {
                if (r->runnerOnFieldOrOutOrScored == 0) {
                    break;
                }
                if (g_Pitcher.pitchTotalTimeCounter >= g_AiLogic.batterAIStealingStartFrame) {
                    h85C44(r, i, 1);
                }
            }
        } else if (g_AiLogic.batterAIStealIndicator != 0) {
            for (j = 1, q = &g_Runners[1]; j <= 2; j++, q++) {
                if (g_Pitcher.pitchTotalTimeCounter >= g_AiLogic.batterAIStealingStartFrame) {
                    if (q->stealingStatus == 0) {
                        if (g_AiLogic.batterAIStealingStartFrame < lbl_3_data_4B90[2]) {
                            q->stealingStatus = 3;
                        } else {
                            q->stealingStatus = 2;
                        }
                        q->leadOffStatus = 0;
                    }
                    h85C44(q, j, 1);
                }
            }
        } else if (g_AiLogic._74 == 2 && g_Pitcher.pitchTotalTimeCounter >= g_AiLogic.batterAIStealingStartFrame) {
            fn_3_85C44(3, 1);
        }
    }
}
#pragma dont_inline on

// .text:0x00085EF4 size:0x158 mapped:0x806C4F88
void fn_3_85EF4(s32 i, s32 d) {
    s16 e;
    u8 t;
    InMemRunnerType* r = &g_Runners[i];
    if (r->runnerOnFieldOrOutOrScored != 1) {
        return;
    }
    if (r->tagUpInd == 2 && d != -1) {
        return;
    }
    if (r->actionCode != 0 && r->actionStage != 0) {
        if (r->actionInForwardDirectionInd == 1) {
            r->baseRunningTowards = r->nextBase;
            return;
        }
        r->baseRunningTowards = r->currentBase;
        return;
    }
    if (d == 1) {
        r->baseRunningTowards = r->nextBase;
    }
    if (d == -1) {
        t = r->currentBase;
        if (t == 0) {
            return;
        }
        if (r->runningDirectionCode == 1 && r->baseStandingOn >= 0 && r->tagUpInd == 0) {
            if (r->baseRoundingState == 1) {
                return;
            }
            r->runningDirectionCode = 2;
            return;
        } else {
            e = r->baseStandingOn;
            if (e >= 0) {
                if (e == 1) {
                    return;
                }
                if (i == 0) {
                    return;
                }
                if (r->tagUpInd == 0) {
                    return;
                }
                r->baseRunningTowards = (e + 3) & 3;
            } else {
                r->baseRunningTowards = t;
            }
        }
    }
    if (d == 0 && i == 0 && r->currentBase == 0) {
        return;
    }
    if (d == 0) {
        r->runningDirectionDesired = 2;
        return;
    }
    if (d == 1) {
        r->runningDirectionDesired = 1;
        return;
    }
    r->runningDirectionDesired = 3;
}

// .text:0x0008604C size:0xCC mapped:0x806C50E0
int fn_3_8604C(int* out) {
    int i;
    int best;
    int j;
    int t;
    best = 9999;
    for (i = 0; i < 9; i++) {
        if (g_FieldingLogic._0F8[i] == 1 || g_FieldingLogic._0F8[i] == 0xA || g_FieldingLogic._0F8[i] == 0xB) {
            for (j = 1; j < 0x78; j += 5) {
                t = fn_3_52560(i, g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.z);
                if (t < j + 0xF) {
                    break;
                }
            }
            if (j >= 0x78) {
                if (best >= 0x78) {
                    best = 0x78;
                }
            } else if (best > t) {
                best = t;
                *out = i;
            }
        }
    }
    return best;
}

// .text:0x00086118 size:0x684 mapped:0x806C51AC
extern const f32 lbl_3_rodata_14CC;
extern const f32 lbl_3_rodata_14D0;
extern const f32 lbl_3_rodata_14D4;
extern s16 lbl_3_data_1C80[];
// Note: the original also computes an unused squared distance from the ball
// (g_Ball+0x348/0x34C) to the chosen sample; it has no effect and is omitted.
// NONMATCHING 81%: unused distance calc and unrolled trajectory search in the original, register allocation
#if NONMATCHING
int fn_3_86118(void) {
    int best = 9999;
    int bestFrame = 0;
    int closest = -1;
    int frame;
    int k;
    int found;
    int a;
    int b;
    int diff;
    u8 st;
    InMemFielderType* f;
    f32 reach;

    if (g_Ball.landingSpotZoneAwayFromHome <= 1 && g_Ball.maxYOfHit < lbl_3_rodata_14CC && g_Ball.framesSinceHit <= 45 &&
        g_Ball.Hit_HorizontalPower > 80) {
        for (k = 2; k < 6; k++) {
            f = &g_Fielders[k];
            if (f->_07C < lbl_3_rodata_140C && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > f->_070) {
                return 2;
            }
        }
        return 7;
    }
    if ((g_Ball.physicsSubstruct.velocity.y < lbl_3_rodata_1414 && g_Ball.AtBat_Contact_BallPos.y < lbl_3_rodata_140C) ||
        g_Ball.maxYOfHit < lbl_3_rodata_140C) {
        frame = 1;
    } else {
        // Step back 5 samples at a time until the ball is at least 2.0 high,
        // then take the following sample.
        for (frame = g_Ball.framesUntilBallHitsGround; frame > 0; frame -= 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.y >= lbl_3_rodata_140C) {
                frame++;
                break;
            }
        }
        if (frame < 1) {
            frame = 1;
        }
    }
    k = 1;
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_144C && g_Ball.hangtimeOfHit > 30 &&
        g_Ball.maxYOfHit > lbl_3_rodata_1410) {
        k = 0;
    }
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_14D0 && g_Ball.hangtimeOfHit > 30 &&
        g_Ball.maxYOfHit > lbl_3_rodata_1470) {
        k = 0;
    }
    if (g_Ball.maxYOfHit <= lbl_3_rodata_1410) {
        found = -1;
        for (; k < 6; k++) {
            st = g_FieldingLogic._0F8[k];
            if (st == 1 || st == 10 || st == 11) {
                f = &g_Fielders[k];
                reach = f->_07C;
                if (reach < lbl_3_rodata_1410 && lbl_3_rodata_1410 + g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > f->_070) {
                    if (reach < lbl_3_rodata_1454 * f->reach[0]) {
                        return 1;
                    }
                    if (f->_070 > lbl_3_rodata_1454 * reach + g_Ball.ballDistanceFromHome) {
                        return 1;
                    }
                }
                if (reach < lbl_3_rodata_14BC && lbl_3_rodata_140C + g_Ball.ballDistanceFromHome < f->_070 &&
                    lbl_3_rodata_14BC + g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > f->_070) {
                    found = k;
                }
            }
        }
        if (found >= 0) {
            return 3;
        }
        return 5;
    }
    for (; k < 9; k++) {
        st = g_FieldingLogic._0F8[k];
        if (st == 1 || st == 10 || st == 11) {
            f = &g_Fielders[k];
            if (f->_07C < lbl_3_rodata_1410 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > f->_070) {
                a = fn_3_52560(k, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) - 10;
                if (best > a) {
                    best = a;
                    bestFrame = frame;
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].dist > lbl_3_rodata_1408 + f->_070) {
                        best = a + 15;
                    }
                }
                closest = k;
            } else {
                a = fn_3_52560(k, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z) - 10;
                b = fn_3_52560(k, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.z) - 10;
                if (a < b) {
                    if (best > a) {
                        bestFrame = g_Ball.framesUntilBallHitsGround;
                        best = a + 3;
                    }
                } else if (best > b) {
                    best = b;
                    bestFrame = frame;
                }
            }
        }
    }
    diff = best - bestFrame;
    if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
        diff += lbl_3_data_1C80[(s32)g_GameLogic.runnerAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
    }
    if (best <= 0) {
        return 0;
    }
    if (g_Ball.someCollisionVariable != 0 && diff < 5) {
        return 3;
    }
    if (diff < -60) {
        return 0;
    }
    if (diff < -30) {
        return 1;
    }
    if (diff < -5) {
        return 2;
    }
    if (diff < 8) {
        if (!(g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < lbl_3_rodata_14D4)) {
            return 3;
        }
        if (diff <= 5) {
            return 3;
        }
    }
    if (closest >= 0 && g_Ball.AtBat_Contact_BallPos.y < g_Fielders[closest].reach[6]) {
        return 3;
    }
    if (diff < 20) {
        return 4;
    }
    if (diff < 40) {
        return 5;
    }
    if (diff < 90) {
        return 6;
    }
    return 7;
}
#endif

// .text:0x0008679C size:0x660 mapped:0x806C5830
void fn_3_8679C(void) {
    int j;
    f32 prevd0 = lbl_3_rodata_1460;
    int prev = -1;
    f32 prevd = prevd0;
    InMemRunnerType* r;
    InMemRunnerType* q;
    int i;
    s16 t;
    s16 cnt;
    s16 re;
    s16 qe;
    g_Runners[0].restrictedMovementCodes_stored = g_Runners[0].restrictedMovementCodes;
    g_Runners[0].restrictedMovementCodes = 0;
    g_Runners[1].restrictedMovementCodes_stored = g_Runners[1].restrictedMovementCodes;
    g_Runners[1].restrictedMovementCodes = 0;
    g_Runners[2].restrictedMovementCodes_stored = g_Runners[2].restrictedMovementCodes;
    g_Runners[2].restrictedMovementCodes = 0;
    g_Runners[3].restrictedMovementCodes_stored = g_Runners[3].restrictedMovementCodes;
    g_Runners[3].restrictedMovementCodes = 0;
    if (g_Strikes.outs < 3) {
        for (i = 3, r = &g_Runners[3]; i >= 0; r--, i--) {
            if (r->runnerOnFieldOrOutOrScored == 1) {
                if (i == 1 && g_Ball.AtBat_ContactResult != 3 && g_FieldingLogic._108 == 0 && g_FieldingLogic._107 == 0 &&
                    r->fractionalBasesRan <= lbl_3_rodata_1494 && g_Ball.framesSinceHit >= 1) {
                    if (g_Ball.AtBat_ContactResult != 0 || g_Ball.framesUntilBallHitsGround >= 0x78 ||
                        !(sqrt13B8((lbl_3_data_4444[2] - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x) * (lbl_3_data_4444[2] - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x) +
                                   (lbl_3_data_4444[3] - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z) * (lbl_3_data_4444[3] - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z)) < lbl_3_rodata_14D8)) {
                        if (g_Batter.hitTrajectory != 3 && g_Runners[0].runnerOnFieldOrOutOrScored != 2) {
                            r->restrictedMovementCodes |= 2;
                            if (r->runningDirectionCode == 3 && r->tagUpInd != 0) {
                                r->restrictedMovementCodes |= 8;
                            }
                        }
                    }
                } else if (i == 0 && g_Ball.AtBat_ContactResult == 0 && g_Runners[1].runnerOnFieldOrOutOrScored == 1 && g_Runners[1].fractionalBasesRan < lbl_3_rodata_140C &&
                           g_Runners[1].runningDirectionCode == 3) {
                    r->restrictedMovementCodes |= 1;
                } else if (prevd < lbl_3_rodata_1414) {
                    if (r->fractionalBasesRan >= lbl_3_rodata_14DC && g_GameLogic.secondaryGameMode != 0xE && g_Strikes.storedOuts < 2) {
                        if (r->tagUpInd != 0) {
                            r->restrictedMovementCodes |= 4;
                        } else if (g_Ball.AtBat_ContactResult == 0 || g_Ball.AtBat_ContactResult == -1) {
                            r->restrictedMovementCodes |= 4;
                        }
                    }
                } else {
                    f32 f;
                    q = &g_Runners[prev];
                    f = prevd - r->fractionalBasesRan;
                    if (r->runningDirectionCode == 3) {
                        f -= lbl_3_rodata_14A0;
                    } else if (r->runningDirectionCode == 2) {
                        f -= lbl_3_rodata_1498;
                    }
                    if (q->runningDirectionCode == 3) {
                        f -= lbl_3_rodata_14E0;
                    }
                    if (r->currentBase != q->currentBase && q->baseStandingOn < 0) {
                        f -= lbl_3_rodata_14A0;
                    }
                    if (f < lbl_3_rodata_14E4) {
                        r->restrictedMovementCodes |= 1;
                        q->restrictedMovementCodes |= 2;
                        if (q->runningDirectionCode == 3 && q->tagUpInd != 0 && (g_Ball.AtBat_ContactResult == 0 || g_Ball.AtBat_ContactResult == 3)) {
                            q->restrictedMovementCodes |= 8;
                        }
                        if (q->percentTowardsNextBase < lbl_3_rodata_1450) {
                            qe = q->baseStandingOn;
                            if (qe == -1 && r->percentTowardsNextBase > lbl_3_rodata_1450) {
                                re = r->baseStandingOn;
                                if (re == -1) {
                                    if (q->distToCurrentBase <= r->distToNextBase) {
                                        if (q->runningDirectionCode == 3 && re == -1) {
                                            q->restrictedMovementCodes &= 0xFD;
                                        } else if (r->runningDirectionCode == 1 && qe == -1) {
                                            q->restrictedMovementCodes &= 0xFE;
                                        } else if (re == -1) {
                                            q->restrictedMovementCodes &= 0xFD;
                                        } else if (qe == -1) {
                                            r->restrictedMovementCodes &= 0xFE;
                                        }
                                    } else if (q->tagUpInd != 0 && re == -1) {
                                        q->restrictedMovementCodes &= 0xFD;
                                    } else if (r->runningDirectionCode == 1 && qe == -1) {
                                        r->restrictedMovementCodes &= 0xFE;
                                    } else if (q->runningDirectionCode == 3 && re == -1) {
                                        q->restrictedMovementCodes &= 0xFD;
                                    } else if (qe == -1) {
                                        r->restrictedMovementCodes &= 0xFE;
                                    } else if (re == -1) {
                                        q->restrictedMovementCodes &= 0xFD;
                                    }
                                }
                            }
                        }
                    }
                }
                prevd = r->fractionalBasesRan;
                prev = i;
            }
        }
        for (i = 0; i <= 1; i++) {
            r = &g_Runners[i];
            cnt = 0;
            t = r->currentBase + 1;
            if (t <= 3 && !(r->percentTowardsNextBase < lbl_3_rodata_145C)) {
                for (j = i + 1; j < 4; j++) {
                    if (g_Runners[j].runnerOnFieldOrOutOrScored == 1 && t == g_Runners[j].currentBase) {
                        cnt++;
                    }
                }
                if (cnt >= 2) {
                    r->restrictedMovementCodes |= 1;
                }
            }
        }
    }
}

// .text:0x00086DFC size:0xFC mapped:0x806C5E90
void fn_3_86DFC(void) {
    InMemRunnerType* r = g_Runners;
    int i;
    for (i = 0; i < 4; i++) {
        if (r->runnerOnFieldOrOutOrScored != 0) {
            if (g_FieldingLogic._107 == 1 && r->stealingStatus != 0 && r->rosterID >= 0) {
                r->runningDirectionDesired = 1;
            }
            r->stealingStatus = 0;
        }
        r++;
    }
}

// .text:0x00086EF8 size:0x1B4 mapped:0x806C5F8C
// 99%: body matches; only d1/base/lo register numbering differs (r7/r8 swapped) around the data[1]/data[0] range check
// NONMATCHING 99.5%: load scheduling around the steal-timing compare
#if NONMATCHING
void fn_3_86EF8(void) {
    int i;
    int j;
    int all;
    s16 pt;
    InMemRunnerType* r;
    for (i = 1; i < 4; i++) {
        r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored != 0 && r->stealingStatus != 0) {
            if (r->framesSinceStealInput < 0xFE) {
                r->framesSinceStealInput = r->framesSinceStealInput + 1;
            } else {
                r->framesSinceStealInput = 0xFF;
            }
            pt = g_Pitcher.pitchTotalTimeCounter;
            if (pt > 0 && r->stealingStatus == 1) {
                if (pt == lbl_3_data_4B90[2]) {
                    u8 t = r->framesSinceStealInput;
                    s32 lo = lbl_3_data_4B90[2] - lbl_3_data_4B90[1];
                    s32 hi = lbl_3_data_4B90[2] - lbl_3_data_4B90[0];
                    if (t >= lo && t <= hi) {
                        r->stealingStatus = 3;
                        r->leadOffStatus = 0;
                        if (r->rosterID >= 0) {
                            r->runningDirectionDesired = 1;
                        }
                    }
                } else if (pt >= lbl_3_data_4B90[3]) {
                    r->stealingStatus = 2;
                    r->leadOffStatus = 0;
                    if (r->rosterID >= 0) {
                        r->runningDirectionDesired = 1;
                    }
                }
            }
            if (r->runnerOnFieldOrOutOrScored == 1 && r->runningDirectionCode == 1 && r->furthestBaseForcedToGoToOnWalk == 0) {
                all = 1;
                for (j = 1; j < i; j++) {
                    if (g_Runners[j].runnerOnFieldOrOutOrScored == 0) {
                        all = 0;
                    }
                }
                if (all != 0) {
                    r->furthestBaseForcedToGoToOnWalk = i + 1;
                } else {
                    r->furthestBaseForcedToGoToOnWalk = 1;
                }
            }
            if (r->furthestBaseForcedToGoToOnWalk != 0) {
                if (r->framesSinceStealStarted < 0x7FFE) {
                    r->framesSinceStealStarted = r->framesSinceStealStarted + 1;
                } else {
                    r->framesSinceStealStarted = 0x7FFF;
                }
            }
        }
    }
}
#endif

// .text:0x000870AC size:0x110 mapped:0x806C6140
void fn_3_870AC(void) {
    InMemRunnerType* r;
    g_Runners[0].tagType = 0;
    g_Runners[1].tagType = 0;
    g_Runners[2].tagType = 0;
    g_Runners[3].tagType = 0;
    if ((g_FieldingLogic._111 == 2 || g_FieldingLogic._111 == 4) && g_FieldingLogic._0E8 >= 0) {
        r = &g_Runners[g_FieldingLogic._0E8];
        if (r->runnerOnFieldOrOutOrScored == 1) {
            r->tagType = 1;
        }
        if (g_FieldingLogic._0EC < 5 && r->actionCode != 0) {
            r->tagType = 2;
        }
        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
            {
                InMemFielderType* f;
                f = g_Fielders;
                f += g_Ball.fielderWBallIndex;
                fn_3_161588(6, f->rosterID);
            }
        }
    }
}

// .text:0x000871BC size:0x110 mapped:0x806C6250
// ~90%: body matches; prologue base-register order and hoisted lha/lfs scheduling differ (tried ~200 decl/init/loop-form variants)
// NONMATCHING 90%: prologue base-register order and load scheduling (see note above)
#if NONMATCHING
void fn_3_871BC(void) {
    int n;
    f32 c1 = lbl_3_data_4C44[1];
    f32 c2 = lbl_3_data_4C44[2];
    f32 c3 = lbl_3_data_4C44[3];
    s16 a = lbl_3_data_4C54[10];
    s16 b = lbl_3_data_4C54[11];
    s16 mx = lbl_3_data_4C54[9];
    for (n = 0; n < 4; n++) {
        InMemRunnerType* r = &g_Runners[n];
        if (r->runnerOnFieldOrOutOrScored == 1) {
            s32 d = 0;
            f32 t;
            if (r->groundVelocity[0] >= lbl_3_rodata_1498) {
                d = a;
            }
            if (r->turnaroundCode != 0) {
                d += b;
            }
            if (d != 0) {
                r->stamina = r->stamina - d;
                if (r->stamina < 0) {
                    r->stamina = 0;
                }
            }
            t = 1.0f - (f32)r->stamina / (f32)mx;
            r->staminaMult = 1.0f - c1 * t;
            r->accelerationStaminaEffect = 1.0f - c2 * t;
            r->accelerationStaminaEffectWhileChangingDirection = 1.0f - c3 * t;
        }
    }
}
#endif

// .text:0x000872CC size:0x158 mapped:0x806C6360
void fn_3_872CC(void) {
    int n;
    for (n = 0; n < 4; n++) {
        InMemRunnerType* r = &g_Runners[n];
        if (r->runnerOnFieldOrOutOrScored != 0) {
            r->baseStandingOn_Stored = r->baseStandingOn;
            r->positionStored.x = r->position.x;
            r->positionStored.y = r->position.y;
            r->positionStored.z = r->position.z;
            r->velocityStored.x = r->velocity.x;
            r->velocityStored.y = r->velocity.y;
            r->velocityStored.z = r->velocity.z;
            r->fractionalBasesRan_stored = r->fractionalBasesRan;
            r->percentTowardsNextBase_stored = r->percentTowardsNextBase;
            r->runningDirectionDesired = 0;
            r->newButtonThisFrame_forMashPurposes = 0;
            if (g_Ball.AtBat_ContactResult == 3 && g_Strikes.storedOuts < 2 && r->tagUpInd == 1) {
                r->tagUpInd = 2;
                if (r->baseStandingOn == r->startingBase_baseAchieved) {
                    r->tagUpInd = 0;
                }
            }
            if (r->someCountdown_unused != 0) {
                r->someCountdown_unused = r->someCountdown_unused - 1;
                if (r->someCountdown_unused == 0) {
                    r->_151 = 0;
                }
            }
            if (g_GameLogic.gameStatus == 2) {
                r->leadOffStatus = 0;
            }
        }
    }
    if (g_Ball.framesSinceHit == 1 && g_Ball.maxYOfHit >= lbl_3_rodata_14BC && g_Ball.landingSpotZoneAwayFromHome >= 2) {
        g_RunningLogic._14 = 10;
    }
}

// .text:0x00087424 size:0x3F8 mapped:0x806C64B8
// 97%: only prologue load order differs (orig loads 4C54 table first: lha 0x14,0x16,0x12 then lfs 4C44; ours starts with 4C44 base)
// NONMATCHING 97%: instruction scheduling
#if NONMATCHING
void fn_3_87424(void) {
    InMemRunnerType* q;
    s16 t;
    InMemFielderType* f;
    s16 a;
    s16 b86;
    int ri;
    int i;
    InMemRunnerType* r;
    s32 d;
    f32 p;
    s16 h1;
    s16 h2;
    s16 h3;
    f32 c1;
    f32 c2;
    f32 c3;
    fn_3_872CC();
    if (g_GameLogic.secondaryGameMode != 6 && g_GameLogic.secondaryGameMode != 0xE) {
        b86 = g_Ball.baseBallAndFielderAreOn;
        if (b86 >= 0 && (a = g_Ball.AtBat_ContactResult) >= 0 && a != 3 && g_Fielders[g_Ball.fielderWBallIndex]._1E7 == 0) {
            ri = (b86 + 3) & 3;
            q = &g_Runners[ri];
            if (q->forceOutCd == 1) {
                fn_3_88D88(ri);
                q->forceOutCd = 2;
                q->outType = 2;
                if (g_Ball.fielderWhoGotLastOut < 0) {
                    t = g_Ball.throwingFielder;
                    if (t < 0) {
                        g_Ball.fielderWhoGotLastOut = g_Ball.fielderWBallIndex;
                    } else {
                        g_Ball.fielderWhoGotLastOut = t;
                        if (g_FieldingLogic._141 != 0 && g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
                            f = g_Fielders;
                            f += t;
                            fn_3_161588(8, f->rosterID);
                        }
                        if ((s8)g_FieldingLogic._115 > 0 && g_FieldingLogic._133 != 0) {
                            g_UnkSound_32718._08 = 4;
                            t = g_Ball.fielderWithBallIndexStored2;
                            g_FieldingLogic._134 = t;
                            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
                                f = g_Fielders;
                                f += t;
                                fn_3_161588(2, f->rosterID);
                            }
                        }
                    }
                }
            }
        }
        h1 = lbl_3_data_4C54[10];
        h2 = lbl_3_data_4C54[11];
        c1 = lbl_3_data_4C44[1];
        c2 = lbl_3_data_4C44[2];
        c3 = lbl_3_data_4C44[3];
        h3 = lbl_3_data_4C54[9];
        for (i = 0; i < 4; i++) {
            r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == 1) {
                d = 0;
                if (r->groundVelocity[0] >= lbl_3_rodata_1498) {
                    d = h1;
                }
                if (r->turnaroundCode != 0) {
                    d += h2;
                }
                if (d != 0) {
                    r->stamina = r->stamina - d;
                    if (r->stamina < 0) {
                        r->stamina = 0;
                    }
                }
                p = lbl_3_rodata_1408 - (f32) r->stamina / (f32)h3;
                r->staminaMult = lbl_3_rodata_1408 - c1 * p;
                r->accelerationStaminaEffect = lbl_3_rodata_1408 - c2 * p;
                r->accelerationStaminaEffectWhileChangingDirection = lbl_3_rodata_1408 - c3 * p;
            }
        }
        g_Runners[0].tagType = 0;
        g_Runners[1].tagType = 0;
        g_Runners[2].tagType = 0;
        g_Runners[3].tagType = 0;
        if (g_FieldingLogic._111 == 2 || g_FieldingLogic._111 == 4) {
            s16 fi = g_FieldingLogic._0E8;
            if (fi >= 0) {
                q = &g_Runners[fi];
                if (q->runnerOnFieldOrOutOrScored == 1) {
                    q->tagType = 1;
                }
                if (g_FieldingLogic._0EC < 5 && q->actionCode != 0) {
                    q->tagType = 2;
                }
                if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
                    f = g_Fielders;
                    f += g_Ball.fielderWBallIndex;
                    fn_3_161588(6, f->rosterID);
                }
            }
        }
    }
}
#endif

// .text:0x0008781C size:0x2CC mapped:0x806C68B0
void fn_3_8781C(void) {
    int n;
    u8 b1;
    u8 b2;
    u8 b3;
    u8 b4;
    s16 h;
    int i;
    InMemRunnerType* r;
    VecSrcDst p;
    CollisionStruct c;
    g_RunningLogic._00 = 0;
    g_RunningLogic._04 = 0;
    g_RunningLogic._10 = 0;
    for (n = 0; n < 4; n++) {
        r = &g_Runners[n];
        if (r->percentTowardsNextBase > lbl_3_rodata_1458) {
            r->relatedToRunnerPos = 0;
        }
        if (r->runnerOnFieldOrOutOrScored == 1) {
            g_RunningLogic._00 |= 1 << (n * 4);
            g_RunningLogic._10++;
            if (r->currentBase <= 3) {
                g_RunningLogic._04 |= 1 << (r->currentBase * 4);
            }
        }
        if (g_Ball.AtBat_ContactResult == -1 && r->runnerOnFieldOrOutOrScored == 1) {
            r->runnerOnFieldOrOutOrScored = 4;
        }
        if (r->baseStandingOn >= 0) {
            if (r->timeStandingOnBase < 0x7FFE) {
                r->timeStandingOnBase = r->timeStandingOnBase + 1;
            } else {
                r->timeStandingOnBase = 0x7FFF;
            }
        } else {
            r->timeStandingOnBase = 0;
        }
        r->nextBase = (r->currentBase + 1) & 3;
        if (r->runnerOnFieldOrOutOrScored != 0) {
            p.src.x = r->position.x;
            p.src.y = lbl_3_rodata_1460;
            p.src.z = r->position.z;
            p.dst.x = r->position.x;
            p.dst.y = lbl_3_rodata_1408;
            p.dst.z = r->position.z;
            r->someCollisionCheck = checkCollision(&p, &c, 0, 0);
        }
    }
    if (g_Runners[0].baseNumberEarned_NotIncludingFieldersChoice == -1) {
        b1 = g_Ball.ballState;
        b2 = g_Ball.ballZoneAwayFromHome;
        b3 = *(u8*)&g_Ball.ballZoneWhenCaught;
        b4 = g_FieldingLogic._10E;
        for (i = 0; i < 4; i++) {
            if ((b1 == 1 && b2 <= 2) || b3 <= 1 || b4 != 0) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 2) {
                    g_Runners[i].baseNumberEarned_NotIncludingFieldersChoice = g_Runners[i].currentBase;
                } else if (g_Runners[i].runnerOnFieldOrOutOrScored != 0) {
                    h = g_Runners[i].baseStandingOn;
                    if (h >= 0) {
                        g_Runners[i].baseNumberEarned_NotIncludingFieldersChoice = h;
                    }
                }
            } else if (g_Runners[i].runnerOnFieldOrOutOrScored == 3) {
                g_Runners[i].baseNumberEarned_NotIncludingFieldersChoice = 0;
            }
        }
    }
}

// .text:0x00087AE8 size:0x1E0 mapped:0x806C6B7C
void fn_3_87AE8(void) {
    InMemRunnerType* r = g_Runners;
    s16 b;
    r->batterStayInBattersBoxReason = 0;
    if (g_GameLogic.secondaryGameMode != 6) {
        if (g_Minigame.GameMode_MiniGame == 3) {
            r->batterStayInBattersBoxReason = 1;
        } else if ((b = g_Ball.framesSinceHit) < 0) {
            r->batterStayInBattersBoxReason = 1;
        } else if (g_FieldingLogic._107 == 1 || g_FieldingLogic._107 == 2 || g_FieldingLogic._107 == 3) {
            if (g_Strikes.outs < 3) {
                r->batterStayInBattersBoxReason = 1;
            }
        } else if (r->outType == 0 || r->runnerOnFieldOrOutOrScored != 2) {
            if (b < r->delayBeforeStartingToRun) {
                r->batterStayInBattersBoxReason = 2;
            } else if (g_Batter.hitTrajectory == 4 && b < 0x5A) {
                r->batterStayInBattersBoxReason = 2;
            } else if (g_Batter.hitTrajectory == 3 || g_Batter.hitTrajectory == 6) {
                r->batterStayInBattersBoxReason = 3;
            }
        }
    }
    g_Runners[0].velocity.x = g_Runners[0].position.x - g_Runners[0].positionStored.x;
    g_Runners[0].velocity.y = g_Runners[0].position.y - g_Runners[0].positionStored.y;
    g_Runners[0].velocity.z = g_Runners[0].position.z - g_Runners[0].positionStored.z;
    g_Runners[1].velocity.x = g_Runners[1].position.x - g_Runners[1].positionStored.x;
    g_Runners[1].velocity.y = g_Runners[1].position.y - g_Runners[1].positionStored.y;
    g_Runners[1].velocity.z = g_Runners[1].position.z - g_Runners[1].positionStored.z;
    g_Runners[2].velocity.x = g_Runners[2].position.x - g_Runners[2].positionStored.x;
    g_Runners[2].velocity.y = g_Runners[2].position.y - g_Runners[2].positionStored.y;
    g_Runners[2].velocity.z = g_Runners[2].position.z - g_Runners[2].positionStored.z;
    g_Runners[3].velocity.x = g_Runners[3].position.x - g_Runners[3].positionStored.x;
    g_Runners[3].velocity.y = g_Runners[3].position.y - g_Runners[3].positionStored.y;
    g_Runners[3].velocity.z = g_Runners[3].position.z - g_Runners[3].positionStored.z;
}

// .text:0x00087CC8 size:0x1B8 mapped:0x806C6D5C
void fn_3_87CC8(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored != 0) {
            f32 v;
            atan2(-r->velocity.x, -r->velocity.y);
            if (g_Minigame._1B15[g_Minigame._18FC[i]] == 1) {
                v = fn_3_9FEA8((f32)(lbl_3_rodata_14E8 + atan2(-r->velocity.x, -r->velocity.z)));
            } else if (r->runningDirectionCode != 0 && r->runningDirectionCode != 2) {
                if (lbl_3_rodata_1414 == r->velocity.x && lbl_3_rodata_1414 == r->velocity.z) {
                    v = (f32)atan2(-r->velocityStored.x, -r->velocityStored.z);
                    if (r->turningAroundInd == 1 && r->runningDirectionCode == 1 && r->acceleration > lbl_3_rodata_1414) {
                        v = fn_3_9FEA8(lbl_3_rodata_14F0 + v);
                    }
                } else {
                    v = (f32)atan2(-r->velocity.x, -r->velocity.z);
                }
            } else if (lbl_3_rodata_1414 == r->percentTowardsNextBase) {
                v = lbl_3_data_4B58[r->currentBase][2];
            } else {
                v = lbl_3_data_4B58[r->currentBase][0];
            }
            r->runningAngle = v;
            r->angleToBall = v;
        }
    }
}

// .text:0x00087E80 size:0x3A8 mapped:0x806C6F14
void fn_3_87E80(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored != 0) {
            f32 v = r->runningAngle;
            f32 ang = (f32)atan2(-r->velocity.x, -r->velocity.y);
            if (g_GameLogic.secondaryGameMode != 6) {
                if (i == 0 && (r->batterStayInBattersBoxReason == 1 || (g_Pitcher.strikeOutOrWalk == 1 && g_FieldingLogic._107 != 4))) {
                    v = lbl_3_rodata_14F0;
                } else if (i == 0 && g_Batter.hitTrajectory != 0 && r->batterStayInBattersBoxReason != 0) {
                    if (r->groundVelocity[0] >= lbl_3_rodata_14F4) {
                        v = ang;
                    } else {
                        v = lbl_3_rodata_14F0;
                    }
                } else if (i == 0 && (g_FieldingLogic._107 == 1 || g_FieldingLogic._107 == 2) && g_Strikes.outs < 3) {
                    v = lbl_3_rodata_14F0;
                } else if (r->actionCode != 0) {
                    if (r->actionStage == 2 && r->actionFrames_countDown <= 1) {
                        v = lbl_3_data_4B58[r->baseStandingOn][0];
                    }
                } else if (r->overRun1BStage >= 2) {
                    v = (f32)atan2(-r->velocity.x, -r->velocity.z);
                } else if (r->baseRoundingState == 2 && r->baseStandingOn >= 0) {
                    v = (f32)atan2(-r->velocity.x, -r->velocity.z);
                } else if (r->leadOffStatus == 1) {
                    v = (f32)atan2(-r->velocity.x, -r->velocity.z);
                } else if (r->runningToDugoutInd != 0) {
                    if (r->runningToDugoutInd == 2 && r->slideHomeFrames_CountDown != 0) {
                        v = r->runningAngle;
                    } else if (lbl_3_rodata_1414 == r->velocity.x) {
                        v = r->runningAngle;
                    } else {
                        v = (f32)atan2(-r->velocity.x, -r->velocity.z);
                    }
                } else {
                    goto blk37;
                }
            } else {
            blk37:
                if (r->runningDirectionCode != 0 && r->runningDirectionCode != 2) {
                    if (r->leadOffStatus == 2) {
                        v = lbl_3_data_4B58[r->currentBase][0];
                    } else if (lbl_3_rodata_1414 == r->velocity.x && lbl_3_rodata_1414 == r->velocity.z) {
                        v = (f32)atan2(-r->velocityStored.x, -r->velocityStored.z);
                        if (r->turningAroundInd == 1 && r->runningDirectionCode == 1 && r->acceleration > lbl_3_rodata_1414) {
                            v = fn_3_9FEA8(lbl_3_rodata_14F0 + v);
                        }
                    } else {
                        v = (f32)atan2(-r->velocity.x, -r->velocity.z);
                    }
                } else {
                    v = lbl_3_data_4B58[r->currentBase][0];
                }
            }
            r->runningAngle = v;
            if (g_Ball.ballZoneAwayFromHome != 0) {
                v = (f32)atan2(-(g_Ball.AtBat_Contact_BallPos.x - r->position.x), -(g_Ball.AtBat_Contact_BallPos.z - r->position.z));
            }
            r->angleToBall = v;
        }
    }
}

// .text:0x00088228 size:0x1E0 mapped:0x806C72BC
void fn_3_88228(void) {
    u8* q;
    int off;
    s16 t;
    InMemFielderType* f;
    s16 a;
    s16 b86 = g_Ball.baseBallAndFielderAreOn;
    int ri;
    if (b86 >= 0 && (a = g_Ball.AtBat_ContactResult) >= 0 && a != 3 && g_Fielders[g_Ball.fielderWBallIndex]._1E7 == 0) {
        ri = (b86 + 3) & 3;
        // byte offsets into g_Runners, as the original addresses it
        off = ri * sizeof(InMemRunnerType);
        q = (u8*)g_Runners + off;
        if (*(s16*)(q += OFFSET_OF(InMemRunnerType, forceOutCd)) == 1) {
            fn_3_88D88(ri);
            *(s16*)q = 2;
            ((u8*)g_Runners)[off + OFFSET_OF(InMemRunnerType, outType)] = 2;
            if (g_Ball.fielderWhoGotLastOut < 0) {
                t = g_Ball.throwingFielder;
                if (t < 0) {
                    g_Ball.fielderWhoGotLastOut = g_Ball.fielderWBallIndex;
                } else {
                    g_Ball.fielderWhoGotLastOut = t;
                    if (g_FieldingLogic._141 != 0 && g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
                        f = g_Fielders;
                        f += t;
                        fn_3_161588(8, f->rosterID);
                    }
                    if ((s8)g_FieldingLogic._115 > 0 && g_FieldingLogic._133 != 0) {
                        g_UnkSound_32718._08 = 4;
                        t = g_Ball.fielderWithBallIndexStored2;
                        g_FieldingLogic._134 = t;
                        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
                            f = g_Fielders;
                            f += t;
                            fn_3_161588(2, f->rosterID);
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00088408 size:0x5F4 mapped:0x806C749C
void fn_3_88408(void) {
    InMemRunnerType* fr;
    InMemFielderType* f;
    s16 bs;
    s16 h;
    int i;
    if (g_Strikes.outs < 3) {
        bs = g_Ball.AtBat_ContactResult;
        if (bs == 1 || bs == -1 || bs == 2) {
            g_Runners[0].tagUpInd = 0;
            g_Runners[1].tagUpInd = 0;
            g_Runners[2].tagUpInd = 0;
            g_Runners[3].tagUpInd = 0;
        }
        if (bs != -1) {
            if (g_FieldingLogic._0E8 >= 0 && g_FieldingLogic._0E8 <= 3) {
                fr = &g_Runners[g_FieldingLogic._0E8];
            }
            if (bs == 3 || g_FieldingLogic._108 == 2) {
                fn_3_88D88(0);
                g_Runners[0].outType = 1;
                if (g_Ball.fielderWhoGotLastOut < 0) {
                    g_Ball.fielderWhoGotLastOut = g_Ball.fielderWBallIndex;
                }
            }
            if (g_FieldingLogic._116 != 0 && g_FieldingLogic._111 == 1 && fr->tagUpInd != 2) {
                if (fr->baseOfFailedBodyCheck >= 0) {
                    fn_3_88D88(g_FieldingLogic._0E8);
                    fr->outType = 3;
                    g_FieldingLogic._0E8 = -1;
                    g_FieldingLogic._111 = 0;
                    if (g_Ball.fielderWhoGotLastOut < 0) {
                        h = g_Ball.fielderWithBallIndexStored2;
                        g_Ball.fielderWhoGotLastOut = h;
                        if (h >= 6 && fr->baseOfFailedBodyCheck == 0 && g_Ball.numberOfThrowsDuringPlay == 2 && g_Ball.timeSinceBallPickedUp < lbl_3_data_49DC[0x4E / 2]) {
                            g_UnkSound_32718._08 = 4;
                            g_FieldingLogic._134 = h;
                            if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding) {
                                f = g_Fielders;
                                f += h;
                                fn_3_161588(2, f->rosterID);
                            }
                        }
                    }
                    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding && g_Ball.throwingFielder >= 0 &&
                        g_FieldingLogic._141 != 0) {
                        f = g_Fielders;
                        f += g_Ball.throwingFielder;
                        fn_3_161588(8, f->rosterID);
                    }
                }
            } else if (g_FieldingLogic._111 >= 2 && g_FieldingLogic._111 <= 5 && g_FieldingLogic._112 == 2) {
                if (fr->tagUpInd == 2) {
                    fn_3_88D88(g_FieldingLogic._0E8);
                    fr->outType = 4;
                    g_FieldingLogic._0E8 = -1;
                    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding && g_Ball.throwingFielder >= 0 &&
                        g_FieldingLogic._141 != 0) {
                        f = g_Fielders;
                        f += g_Ball.throwingFielder;
                        fn_3_161588(8, f->rosterID);
                    }
                } else if ((fr->baseStandingOn < 0 || fr->forceOutCd == 1) && (fr->actionStage == 0 || fr->actionFrames_countDown >= 0xF)) {
                    fn_3_88D88(g_FieldingLogic._0E8);
                    if (fr->forceOutCd == 1) {
                        fr->forceOutCd = 2;
                    }
                    fr->outType = 3;
                    g_FieldingLogic._0E8 = -1;
                    if (g_Ball.fielderWhoGotLastOut < 0) {
                        g_Ball.fielderWhoGotLastOut = g_Ball.fielderWithBallIndexStored2;
                    }
                    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding && g_Ball.throwingFielder >= 0 &&
                        g_FieldingLogic._141 != 0) {
                        f = g_Fielders;
                        f += g_Ball.throwingFielder;
                        fn_3_161588(8, f->rosterID);
                    }
                }
                g_FieldingLogic._111 = 0;
                g_FieldingLogic._112 = 0;
                g_FieldingLogic._0CC = -1;
            }
            if (g_Ball.baseBallAndFielderAreOn >= 1 && g_Runners[g_Ball.baseBallAndFielderAreOn].tagUpInd == 2) {
                fn_3_88D88(g_Ball.baseBallAndFielderAreOn);
                g_Runners[g_Ball.baseBallAndFielderAreOn].outType = 4;
                if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400.humanPlayer == g_GameLogic.teamFielding && g_Ball.throwingFielder >= 0 &&
                    g_FieldingLogic._141 != 0) {
                    f = g_Fielders;
                        f += g_Ball.throwingFielder;
                        fn_3_161588(8, f->rosterID);
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 2) {
            if (g_Runners[i].framesSinceOut < 0x7FFE) {
                g_Runners[i].framesSinceOut = g_Runners[i].framesSinceOut + 1;
            } else {
                g_Runners[i].framesSinceOut = 0x7FFF;
            }
        }
    }
}

// .text:0x000889FC size:0x11C mapped:0x806C7A90
void fn_3_889FC(void) {
    int i;

    for (i = 0; i < 4; i++) {
        s16 a = g_Ball.AtBat_ContactResult;
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            if ((a == 3 || g_FieldingLogic._108 == 2) && g_Ball.landingSpotZoneAwayFromHome <= 1) {
                g_Runners[i].isEligibleToScore = 0;
            } else if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballState != 0 && (u16)a > 1) {
                u8 t = g_Runners[i].currentBase;
                if (t != 0 && t < 3) {
                    g_Runners[i].isEligibleToScore = 0;
                }
            }
        }
    }
}

// .text:0x00088B18 size:0x10C mapped:0x806C7BAC
void fn_3_88B18(void) {
    int i;
    InMemRunnerType* r;
    s16 t;
    int m;
    m = 0;
    if (g_FieldingLogic._107 != 0 && g_FieldingLogic._107 != 4) {
        m = 1;
    }
    r = g_Runners;
    for (i = 0; i < 4; i++, r++) {
        if (r->forceOutCd == 2) {
            m = 2;
        } else {
            r->forceOutCd = 0;
            if (g_Ball.AtBat_ContactResult >= 0 && g_FieldingLogic._108 == 0) {
                if (m != 0) {
                    if (r->runnerOnFieldOrOutOrScored == 0) {
                        m = 1;
                    }
                    if (m == 2 && r->startingBase_baseAchieved == r->currentBase) {
                        r->forceOutCd = -1;
                    }
                } else if (r->runnerOnFieldOrOutOrScored == 1) {
                    t = r->baseStandingOn;
                    if ((t < 0 || t != ((r->startingBase_baseAchieved + 1) & 3)) && r->startingBase_baseAchieved == r->currentBase) {
                        r->forceOutCd = 1;
                    }
                } else {
                    m = 1;
                }
            }
        }
    }
}

// .text:0x00088C24 size:0x164 mapped:0x806C7CB8
void fn_3_88C24(void) {
    int i;
    InMemRunnerType* r;
    fn_3_87AE8();
    if (g_GameLogic.secondaryGameMode == 6) {
        fn_3_87CC8();
    } else {
        fn_3_88408();
        fn_3_88B18();
        for (i = 0, r = g_Runners; i < 4; r++, i++) {
            s16 a = g_Ball.AtBat_ContactResult;
            u8 fl = g_FieldingLogic._108;
            u8 b1 = g_Ball.landingSpotZoneAwayFromHome;
            u8 b2 = g_Ball.ballZoneAwayFromHome;
            u8 b3 = g_Ball.ballState;
            if (r->runnerOnFieldOrOutOrScored == 1) {
                if ((a == 3 || fl == 2) && b1 <= 1) {
                    r->isEligibleToScore = 0;
                } else if (b2 <= 1 && b3 != 0 && (u16)a > 1) {
                    u8 t = r->currentBase;
                    if (t != 0 && t < 3) {
                        r->isEligibleToScore = 0;
                    }
                }
            }
        }
        fn_3_87E80();
    }
    fn_3_8781C();
}

// .text:0x00088D88 size:0x210 mapped:0x806C7E1C
// 98%: only r4/r5 swap between g_Strikes.outs value and idx*0x154 in the prologue
// NONMATCHING 99.8%: register allocation of the runner base/index in the prologue
#if NONMATCHING
void fn_3_88D88(int idx) {
    InMemRunnerType* r = g_Runners;
    int k;
    r += idx;
    if (g_Strikes.outs < 3 && g_GameLogic.EventTriggers_EndOfGame == 0 && r->runnerOnFieldOrOutOrScored == 1) {
        if (g_GameLogic.freeFieldingPracticeInd == 0) {
            g_Strikes.outs = g_Strikes.outs + 1;
        } else if ((g_Practice.practiceType_2 == 2 && g_Practice.practiceLevel == 1) || g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6) {
            g_Strikes.outs++;
        }
        if (g_Ball.maybeBuntInd != 0 && g_Strikes.strikes >= 3) {
            fn_3_59918(0x16, 0);
        } else if (r->fractionalBasesRan >= lbl_3_rodata_14F8 && g_Ball.baseBallAndFielderAreOn == 0) {
            fn_3_59918(1, 1);
        } else {
            fn_3_59918(1, 0);
        }
        {
            s16* p = g_Strikes.runnerIndexForEachOutThisPitch;
            for (k = 0; k < 3; p++, k++) {
                if (*p == -1) {
                    g_Strikes.runnerIndexForEachOutThisPitch[k] = idx;
                    break;
                }
            }
        }
        if (g_Strikes.outs == 3) {
            if (r->forceOutCd == 1) {
                g_Strikes.forcedOutToEndInningInd = 1;
            } else {
                fn_3_5C74C(1);
            }
            fn_3_5D094(0);
            if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
        r->runnerOnFieldOrOutOrScored = 2;
    }
}
#endif

// .text:0x00088F98 size:0x90 mapped:0x806C802C
void fn_3_88F98(void) {
    int i;
    InMemRunnerType* rs = g_Runners;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            fn_3_85EF4(i, 1);
        }
        if (i == 0) {
            rs[i].unused_AIRelated = 1;
        } else {
            rs[i].unused_AIRelated = 0;
            if (g_Strikes.storedOuts < 2) {
                rs[i].tagUpInd = 1;
            } else {
                rs[i].tagUpInd = 0;
            }
        }
    }
}

// .text:0x00089028 size:0xF4 mapped:0x806C80BC
void fn_3_89028(void) {
    int i;
    for (i = 0; i < 4; i++) {
        g_Runners[i].leadOffStatus = 0;
    }
    for (i = 1; i < 4; i++) {
        g_Runners[i].unused_AIRelated = 0;
        g_Runners[i].tagUpInd = 0;
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            fn_3_85EF4(i, 1);
        }
    }
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 5;
    } else if (g_FieldingLogic._107 == 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 1;
        fn_3_85EF4(0, 1);
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = 4;
    }
}

// .text:0x0008911C size:0x20 mapped:0x806C81B0
void fn_3_8911C(void) {
    g_Runners[0].leadOffStatus = 0;
    g_Runners[1].leadOffStatus = 0;
    g_Runners[2].leadOffStatus = 0;
    g_Runners[3].leadOffStatus = 0;
}

// .text:0x0008913C size:0x728 mapped:0x806C81D0
extern s32 fn_3_6D658(s32 team, s32 charId, s32 otherId);
extern s16 lbl_3_data_4638[];
extern const f32 lbl_3_rodata_14FC;
extern const f32 lbl_3_rodata_1500;
// NONMATCHING 92%: register allocation and load scheduling in the per-runner reset loop
#if NONMATCHING
void fn_3_8913C(void) {
    InMemRunnerType* r;
    int k;
    int next;
    int bit;
    f32 dx;
    f32 dz;

    g_RunningLogic.occupiedBases = 0;
    g_RunningLogic._00 = 0;
    g_RunningLogic._10 = 0;
    g_RunningLogic._14 = 20;
    g_RunningLogic._1F = -1;
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.z = g_Batter.batterPos.z;
    for (k = 0, r = g_Runners; k < 4; k++, r++) {
        if (r->rosterID >= 0) {
            bit = 1 << (k * 4);
            r->runnerOnFieldOrOutOrScored = 1;
            g_RunningLogic.occupiedBases |= bit;
            g_RunningLogic._00 |= bit;
            g_RunningLogic._10++;
        } else {
            r->runnerOnFieldOrOutOrScored = 0;
        }
        r->baseStandingOn = -1;
        next = (k + 1) & 3;
        r->currentBase = k;
        r->nextBase = next;
        r->tagUpInd = 0;
        r->restrictedMovementCodes = 0;
        r->relatedToRunnerPos = 0;
        r->outType = 0;
        r->forceOutCd = 0;
        r->isEligibleToScore = 1;
        r->furthestBaseForcedToGoToOnWalk = 0;
        r->framesSinceStealStarted = 0;
        r->batterStayInBattersBoxReason = 0;
        r->baseOfFailedBodyCheck = -1;
        r->timeStandingOnBase = 0;
        r->framesSinceOut = 0;
        r->baseNumberEarned_NotIncludingFieldersChoice = -1;
        r->stealingStatus = 0;
        r->framesSinceStealInput = 0;
        r->unused_someBaseNum = -1;
        r->unused_const_1 = 1;
        r->stamina = lbl_3_data_4C54[9];
        r->staminaMult = lbl_3_rodata_1408;
        r->accelerationStaminaEffect = lbl_3_rodata_1408;
        r->accelerationStaminaEffectWhileChangingDirection = lbl_3_rodata_1408;
        if (k == 0) {
            r->runningAngle = lbl_3_rodata_14F0;
        }
        if (k >= 1) {
            r->runningAngle = lbl_3_data_4B58[k][0];
        }
        dx = g_Ball.AtBat_Contact_BallPos.x - r->position.x;
        dz = g_Ball.AtBat_Contact_BallPos.z - r->position.z;
        r->distanceFromBall = sqrt13B8(dx * dx + dz * dz);
        r->groundVelocity[0] = lbl_3_rodata_1414;
        r->groundVelocity[1] = lbl_3_rodata_1414;
        r->groundVelocity[2] = lbl_3_rodata_1414;
        r->groundVelocity[3] = lbl_3_rodata_1414;
        r->acceleration = lbl_3_rodata_1414;
        r->percentRanPerFrame_slideAdj = lbl_3_rodata_1414;
        r->slidingAdjustment_backwards = lbl_3_rodata_1484;
        r->slidingAdjustment_forwards = lbl_3_rodata_1484;
        r->roundingStrengthPercent = lbl_3_rodata_1414;
        r->mashVeloAdjustment = lbl_3_rodata_1414;
        r->mashPercent = lbl_3_rodata_1414;
        r->actionFrames_countUp = 0;
        r->actionFrames_countDown = 0;
        r->_110 = 0;
        r->framesSinceLastDirectionChange = 0;
        r->slideHomeFrames_CountDown = 0;
        r->runningDirectionDesired = 0;
        r->nextDirectionBeingProcessed = 0;
        r->runningDirectionCode = 0;
        r->offsetFromNormalRunningPathInd = 0;
        r->actionCode = 0;
        r->actionStage = 0;
        r->forceOutType_unsed = 0;
        r->baseRoundingState = 0;
        r->overrun1st_doneChecking = 0;
        r->overRun1BStage = 0;
        r->overrunning1BIndicator = 0;
        r->overrunBaseStage = 0;
        r->offsetPositionForRoundingInd = 0;
        r->roundingInitiaializedInd = 0;
        r->runningToDugoutInd = 0;
        r->runningToDugoutStage = 0;
        r->turnaroundCode = 0;
        r->turningAroundInd = 0;
        r->framesSinceLastMash = 0;
        r->someCountdown_unused = 0;
        r->_151 = 0;
        r->scoredOnGRD = 0;
        if (r->rosterID >= 0) {
            r->runningDirectionCode = 2;
        }
        r->runnerDirectionCode_stored = r->runningDirectionCode;
        if (r->leadOffStatus == 0) {
            if (g_GameLogic.secondaryGameMode == 14) {
                r->leadOffStatus = 0;
            } else {
                r->leadOffStatus = 1;
            }
            r->leadoffDurationFrames = 0;
            r->leadOffTotalFrameCountDown = 45;
            if (g_GameLogic.secondaryGameMode == 6) {
                r->runningAngle = lbl_3_data_4B58[k][2];
                r->percentTowardsNextBase = lbl_3_rodata_1414;
            } else {
                r->percentTowardsNextBase = r->slidingAdjustment_backwards;
            }
            r->fractionalBasesRan = r->percentTowardsNextBase + (f32)k;
            r->baseStandingOn = k;
            r->currentBaseCoordinates.x = lbl_3_data_4A34[k * 2];
            r->currentBaseCoordinates.z = lbl_3_data_4A34[k * 2 + 1];
            r->nextBaseCoordinates.x = lbl_3_data_4A34[next * 2];
            r->nextBaseCoordinates.z = lbl_3_data_4A34[next * 2 + 1];
        }
    }
    g_AiLogic._77 = 0;
    g_RunningLogic._12 = g_RunningLogic._10;
    g_AiLogic._44 = lbl_3_data_1C58[(s32)g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam] * 4 + 1];
    g_RunningLogic._15 = 0;
    if (g_RunningLogic.occupiedBases & 0x1000) {
        g_RunningLogic._15 = 1;
    }
    if (g_RunningLogic.occupiedBases & 0x100) {
        g_RunningLogic._15++;
    }
    // A runner is forced to advance if he is on the field and the runner behind him is.
    for (k = 1, r = &g_Runners[1]; k < 4; k++, r++) {
        if (r->runnerOnFieldOrOutOrScored == 0) {
            r->forcedToAdvanceInd = 0;
        } else if (r[-1].forcedToAdvanceInd != 0) {
            r->forcedToAdvanceInd = 1;
        } else {
            r->forcedToAdvanceInd = 0;
        }
    }
    r = g_Runners;
    r->forcedToAdvanceInd = 1;
    r->unused_AIRelated = 1;
    r->battingHand = g_Batter.batterHand;
    r->runnerDidntReachOnError = 1;
    r->pitcherWhoLetRunnerOnBase = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    r->batterStayInBattersBoxReason = 1;
    r->position.x = g_Batter.batterPos.x;
    r->position.y = lbl_3_rodata_1414;
    r->position.z = g_Batter.batterPos.z;
    r->positionStored.x = g_Batter.batterPos.x;
    r->positionStored.y = lbl_3_rodata_1414;
    r->positionStored.z = g_Batter.batterPos.z;
    for (k = 1; k < 4; k++) {
        r = &g_Runners[k];
        r->positionStored.x = r->position.x;
        r->positionStored.y = r->position.y;
        r->positionStored.z = r->position.z;
    }
    if (g_Batter.batterHand == 0) {
        g_RunningLogic._0E = (int)(lbl_3_rodata_14FC / g_Runners[0].maximumBaseVelocity) + 35;
    } else {
        g_RunningLogic._0E = (int)(lbl_3_rodata_1500 / g_Runners[0].maximumBaseVelocity) + 35;
    }
    g_RunningLogic._0E += 20;
    g_Batter.runnersOnBase = 0;
    g_Batter.chemLinksOnBase = 0;
    for (k = 1, r = &g_Runners[1]; k < 4; k++, r++) {
        if (r->rosterID >= 0 && fn_3_6D658(g_GameLogic.teamBatting, g_Batter.charID, r->charID) >= lbl_3_data_4638[3]) {
            g_Batter.chemLinksOnBase++;
            g_Batter.runnersOnBase |= 1 << (k - 1);
        }
    }
}
#endif

// .text:0x00089864 size:0x58 mapped:0x806C88F8
void fn_3_89864(s32 i, s32 d) {
    InMemRunnerType* r = &g_Runners[i];
    r->currentBase += d;
    r->nextBase = (r->currentBase + 1) & 3;
    if (r->currentBase < 4) {
        return;
    }
    r->runnerOnFieldOrOutOrScored = 3;
    g_Scores._9C += 1;
}

// .text:0x000898BC size:0x58 mapped:0x806C8950
void fn_3_898BC(s32 i, s32 j) {
    InMemRunnerType* r = &g_Runners[i];
    r->rosterID = j;
    r->battingHand = inMemRoster[g_GameLogic.teamBatting][j].stats.FieldingArm;
    if (r->battingHand == 2) {
        r->battingHand = 0;
    }
}

// .text:0x00089914 size:0xA8 mapped:0x806C89A8
void fn_3_89914(s32 a, s32 b) {
    InMemRunnerType* ra = &g_Runners[a];
    InMemRunnerType* rb = &g_Runners[b];
    if (a >= 0 && a <= 3) {
        if (g_GameLogic.secondaryGameMode == 0xF && a == 0) {
            rb->rosterID = g_Practice.rosterID;
        } else {
            rb->rosterID = ra->rosterID;
            rb->battingHand = ra->battingHand;
            rb->runnerDidntReachOnError = ra->runnerDidntReachOnError;
            rb->pitcherWhoLetRunnerOnBase = ra->pitcherWhoLetRunnerOnBase;
        }
        g_RunningLogic._06[a] = b;
        return;
    }
    rb->rosterID = -1;
    rb->runnerDidntReachOnError = 0;
    rb->pitcherWhoLetRunnerOnBase = -1;
}

// .text:0x000899BC size:0x81C mapped:0x806C8A50
// Puts runner `src` (-1 = nobody) on base slot `dst`.
static inline void moveRunner13B8(int dst, int src) {
    InMemRunnerType* d = &g_Runners[dst];
    InMemRunnerType* s = &g_Runners[src];
    if (src >= 0 && src <= 3) {
        if (g_GameLogic.secondaryGameMode == 15 && src == 0) {
            d->rosterID = g_Practice.rosterID;
        } else {
            d->rosterID = s->rosterID;
            d->battingHand = s->battingHand;
            d->runnerDidntReachOnError = s->runnerDidntReachOnError;
            d->pitcherWhoLetRunnerOnBase = s->pitcherWhoLetRunnerOnBase;
        }
        g_RunningLogic._06[src] = dst;
    } else {
        d->rosterID = -1;
        d->runnerDidntReachOnError = 0;
        d->pitcherWhoLetRunnerOnBase = -1;
    }
}

// Rebuilds the runner slots after a play: map[base] = runner that ends up there.
// NONMATCHING 99.9%: only the stack frame size; map[] is 5 long here to avoid the original's out-of-bounds write
#if NONMATCHING
void fn_3_899BC(void) {
    // The original declares map[4] and writes map[4] (onto the saved
    // registers) when a forced runner advances from third.
    s32 map[5];
    int k;
    int b;
    int t;
    InMemRunnerType* r;

    if (g_d_GameSettings.GameModeSelected == 2 && g_Strikes.outs >= 3) {
        for (k = 0; k < 4; k++) {
            g_Runners[k].runnerOnFieldOrOutOrScored = 0;
            g_Runners[k].rosterID = -1;
        }
    }
    map[0] = -1;
    g_RunningLogic._06[0] = -1;
    map[1] = -1;
    g_RunningLogic._06[1] = -1;
    map[2] = -1;
    g_RunningLogic._06[2] = -1;
    map[3] = -1;
    g_RunningLogic._06[3] = -1;
    if (g_Pitcher.strikeOutOrWalk == 2 && g_FieldingLogic._107 != 0) {
        for (k = 3; k >= 1; k--) {
            r = &g_Runners[k];
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                if (r->currentBase == k && r->forcedToAdvanceInd != 0) {
                    map[k + 1] = k;
                } else {
                    map[r->currentBase] = k;
                }
            }
        }
        map[1] = 0;
        for (b = 3; b >= 0; b--) {
            moveRunner13B8(b, map[b]);
        }
        return;
    }
    if (g_Ball.maybebuntOn2Strikes != 0) {
        map[3] = 3;
        moveRunner13B8(3, 3);
        map[2] = 2;
        moveRunner13B8(2, 2);
        map[1] = 1;
        moveRunner13B8(1, 1);
        return;
    }
    if (g_Pitcher.strikeOutOrWalk == 3) {
        if (g_Runners[1].runnerOnFieldOrOutOrScored == 0) {
            map[3] = 3;
            moveRunner13B8(3, 3);
            map[2] = 2;
            moveRunner13B8(2, 2);
        } else if (g_Runners[2].runnerOnFieldOrOutOrScored == 0) {
            map[2] = 1;
            moveRunner13B8(2, 1);
            map[3] = 3;
            moveRunner13B8(3, 3);
        } else {
            map[3] = 2;
            moveRunner13B8(3, 2);
            map[2] = 1;
            moveRunner13B8(2, 1);
        }
        map[1] = 0;
        moveRunner13B8(1, 0);
        return;
    }
    if (g_Ball.deadBallReason == 3) {
        map[3] = 1;
        moveRunner13B8(3, 1);
        map[2] = 0;
        moveRunner13B8(2, 0);
        map[1] = -1;
        moveRunner13B8(1, -1);
        return;
    }
    if (g_Ball.deadBallReason == 4) {
        if (g_Runners[1].baseReachedAtTimeOfThrow >= 0 && g_Runners[1].runnerOnFieldOrOutOrScored == 1 &&
            g_Runners[1].baseReachedAtTimeOfThrow == 1) {
            map[3] = 1;
        }
        if (g_Runners[0].baseReachedAtTimeOfThrow >= 0 && g_Runners[0].runnerOnFieldOrOutOrScored == 1) {
            t = g_Runners[0].baseReachedAtTimeOfThrow + 2;
            if (t < 4) {
                if (map[3] >= 0 && t == 3) {
                    t--;
                }
                map[t] = 0;
            }
        }
        for (b = 3; b >= 1; b--) {
            moveRunner13B8(b, map[b]);
        }
        return;
    } else {
        for (k = 0, r = g_Runners; k < 4; k++, r++) {
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                map[r->currentBase] = k;
            }
        }
    }
    for (b = 3; b >= 1; b--) {
        moveRunner13B8(b, map[b]);
    }
}
#endif

// .text:0x0008A1D8 size:0x178 mapped:0x806C926C
// ~98%: loop regs match now; prologue differs (original loads the 0.0f via addi+lfs 0(r4) and copies i to r3 for the 0x133 stores)
// NONMATCHING 93%: prologue constant load / register copy (see note above)
#if NONMATCHING
void fn_3_8A1D8(void) {
    InMemRunnerType* r;
    int i;
    P2* p;
    for (i = 0, r = g_Runners, p = (P2*)lbl_3_data_4A34; i < 4; i++, r++, p++) {
        r->position.x = p->x;
        r->position.z = p->z;
        r->velocity.x = 0.0f;
        r->velocity.y = 0.0f;
        r->velocity.z = 0.0f;
        r->startingBase_baseAchieved = i;
        r->currentBase = i;
        r->nextBase = (i + 1) & 3;
        r->baseStandingOn = i;
        r->baseRunningTowards = 0xFF;
        r->leadOffStatus = 0;
    }
    if (g_GameLogic.secondaryGameMode != 0xC) {
        for (i = 1; i < 4; i++) {
            InMemRunnerType* r = &g_Runners[i];
            if (r->rosterID >= 0) {
                fn_3_6D964(r->rosterID, i);
            } else {
                r->runnerOnFieldOrOutOrScored = 0;
            }
        }
    }
    {
        int a = g_GameLogic.homeTeamBattingInd_fieldingTeam;
        fn_3_6D964(g_GameLogic.battingOrderAndPositionMapping[a][g_GameLogic.currentBatterPerTeam[a]][0], 0);
    }
}
#endif

// .text:0x0008A350 size:0x178 mapped:0x806C93E4
// ~97%: loop 1 regs now match (u32 a/b); loop 2 differs: extra `mr r8,r4` for the runner pointer, table/i regs (r5/r6 vs r6/r4) and lis order.
// Tried: index-form loop 2 / inlining fn_3_8A4E4 gets regs but folds offsets (no addi r8 between unrolled iterations); ~300 variants.
// NONMATCHING 93%: extra register copy for the runner pointer in loop 2 (see note above)
#if NONMATCHING
void fn_3_8A350(void) {
    int i;
    InMemRunnerType* r;
    f32* p;
    InMemRunnerType* q;
    u32 a = g_d_GameSettings.GameModeSelected;
    u32 b = g_d_GameSettings.bJMatchInd;
    for (i = 1; i < 4; i++) {
        r = &g_Runners[i];
        if (a != 5 || b != 1 || r->rosterID < 0) {
            r->rosterID = -1;
            r->battingHand = 0;
            r->runnerDidntReachOnError = 0;
            r->pitcherWhoLetRunnerOnBase = -1;
        }
    }
    g_RunningLogic._15 = 0;
    p = lbl_3_data_4A34;
    q = g_Runners;
    for (i = 0; i < 4; i++, q++, p += 2) {
        q->position.x = p[0];
        q->position.z = p[1];
        q->velocity.x = 0.0f;
        q->velocity.y = 0.0f;
        q->velocity.z = 0.0f;
        q->startingBase_baseAchieved = i;
        q->currentBase = i;
        q->nextBase = (i + 1) & 3;
        q->baseStandingOn = i;
        q->baseRunningTowards = 0xFF;
        q->leadOffStatus = 0;
    }
}
#endif

// .text:0x0008A4C8 size:0x1C mapped:0x806C955C

void fn_3_8A4C8(void) {
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.z = g_Batter.batterPos.z;
}

// .text:0x0008A4E4 size:0xC0 mapped:0x806C9578
void fn_3_8A4E4(void) {
    int i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        r->position.x = ((P2*)lbl_3_data_4A34)[i].x;
        r->position.z = ((P2*)lbl_3_data_4A34)[i].z;
        r->velocity.x = 0.0f;
        r->velocity.y = 0.0f;
        r->velocity.z = 0.0f;
        r->startingBase_baseAchieved = i;
        r->currentBase = i;
        r->nextBase = (i + 1) & 3;
        r->baseStandingOn = i;
        r->baseRunningTowards = 0xFF;
        r->leadOffStatus = 0;
    }
}

// .text:0x0008A5A4 size:0x74 mapped:0x806C9638
void fn_3_8A5A4(void) {
    s8 i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        r->rosterID = -1;
        r->_121 = 10;
        r->delayBeforeStartingToRun = 30;
        r->leadoffDistancePercent = lbl_3_rodata_1498;
        r->someCollisionCheck = 0;
    }
}

// .text:0x0008A618 size:0x19C mapped:0x806C96AC
// ~98%: shape matches; only regs of hoisted constants/temps differ (orig: temp r3, m r4, 1->r0, 0->r6; ours: temp r4, m r6, 1->r3, 0->r0). ~100 variants tried.
// NONMATCHING 98%: register allocation of hoisted constants/temps (see note above)
#if NONMATCHING
void fn_3_8A618(void) {
    int i;
    InMemRunnerType* r;
    u8 m;
    if ((g_GameLogic.gameStatus != 2 || g_GameLogic.FrameCountOfCurrentPitch >= g_RunningLogic._14 || g_GameLogic.secondaryGameMode == 0xE ||
         g_FieldingLogic._107 != 0) &&
        g_FieldingLogic._10E == 0) {
        if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
            fn_3_7E2BC();
        } else {
            fn_3_83714();
        }
        m = g_FieldingLogic._107;
        r = g_Runners;
        for (i = 0; i < 4; i++, r++) {
            if (r->runnerOnFieldOrOutOrScored != 0) {
                if (m == 1 && r->stealingStatus != 0 && r->rosterID >= 0) {
                    r->runningDirectionDesired = 1;
                }
                r->stealingStatus = 0;
            }
        }
    }
}
#endif

// .text:0x0008A7B4 size:0x1A4 mapped:0x806C9848
void fn_3_8A7B4(void) {
    int i;
    InputStruct* c;
    u8 p;
    int idx;
    if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
        fn_3_85CB0();
    } else {
        idx = g_GameLogic.teamBatting;
        c = &g_Controls[(s32)g_GameLogic.teams[idx]];
        p = g_Pitcher.pitcherActionState;
        if (!(p != 1 && p != 2 && p != 3)) {
            if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
                c = &g_Practice.inputs[idx];
            }
            if (c->newButtonInput & 0x800) {
                if (c->controlStickAngle < 0) {
                    for (i = 1; i < 4; i++) {
                        if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].stealingStatus == 0) {
                            g_Runners[i].stealingStatus = 1;
                        }
                    }
                } else {
                    if (c->controlStickAngle >= 0x1C0 && c->controlStickAngle <= 0x640) {
                        g_Runners[1].stealingStatus = 1;
                    }
                    if (c->controlStickAngle >= 0x5C0 && c->controlStickAngle <= 0xA40) {
                        g_Runners[2].stealingStatus = 1;
                    }
                    if (c->controlStickAngle >= 0x9C0 && c->controlStickAngle <= 0xE40) {
                        g_Runners[3].stealingStatus = 1;
                    }
                }
            }
        }
    }
    fn_3_86EF8();
}

// .text:0x0008A958 size:0x73C mapped:0x806C99EC
// NONMATCHING 93%: register allocation, FieldingLogic+0x107 reload in the steal-reset loop, fused multiply-add in the distance
#if NONMATCHING
void fn_3_8A958(void) {
    InMemRunnerType* r;
    InputStruct* c;
    int i;
    s16 stick;
    u8 s;
    int v;
    f32 dx;
    f32 dz;
    s16 acr;

    fn_3_87424();
    fn_3_8679C();
    if (g_GameLogic.gameStatus == 1) {
        if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
            fn_3_85CB0();
        } else {
            c = &g_Controls[(s32)g_GameLogic.teams[g_GameLogic.teamBatting]];
            if (g_Pitcher.pitcherActionState == 1 || g_Pitcher.pitcherActionState == 2 || g_Pitcher.pitcherActionState == 3) {
                if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
                    c = &g_Practice.inputs[g_GameLogic.teamBatting];
                }
                if (c->newButtonInput & 0x800) {
                    stick = c->controlStickAngle;
                    if (stick < 0) {
                        for (i = 1, r = &g_Runners[1]; i < 4; i++, r++) {
                            if (r->runnerOnFieldOrOutOrScored != 0 && r->stealingStatus == 0) {
                                r->stealingStatus = 1;
                            }
                        }
                    } else {
                        if (stick >= 0x1C0 && stick <= 0x640) {
                            g_Runners[1].stealingStatus = 1;
                        }
                        if (c->controlStickAngle >= 0x5C0 && c->controlStickAngle <= 0xA40) {
                            g_Runners[2].stealingStatus = 1;
                        }
                        if (c->controlStickAngle >= 0x9C0 && c->controlStickAngle <= 0xE40) {
                            g_Runners[3].stealingStatus = 1;
                        }
                    }
                }
            }
        }
        fn_3_86EF8();
    } else if (g_GameLogic.gameStatus == 2 &&
               (g_GameLogic.FrameCountOfCurrentPitch >= g_RunningLogic._14 || g_GameLogic.secondaryGameMode == 14 || g_FieldingLogic._107 != 0) &&
               g_FieldingLogic._10E == 0) {
        if (g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
            fn_3_7E2BC();
        } else {
            fn_3_83714();
        }
        for (i = 0, r = g_Runners; i < 4; i++, r++) {
            if (r->runnerOnFieldOrOutOrScored != 0) {
                if (g_FieldingLogic._107 == 1 && r->stealingStatus != 0 && r->rosterID >= 0) {
                    r->runningDirectionDesired = 1;
                }
                r->stealingStatus = 0;
            }
        }
    }
    for (i = 0, r = g_Runners; i < 4; i++, r++) {
        if (r->runnerOnFieldOrOutOrScored != 0) {
            fn_3_8307C(i);
            if ((r->runningToDugoutInd == 0 || r->runningToDugoutStage == 0) && r->actionCode == 0) {
                if (r->framesSinceLastDirectionChange >= lbl_3_data_4C54[3] || (r->runningDirectionCode != 1 && r->runningDirectionCode != 3)) {
                    s = r->runningDirectionDesired;
                    if (s != 0) {
                        if (g_GameLogic.secondaryGameMode == 6) {
                            if (r->runnerOnFieldOrOutOrScored == 1) {
                                r->nextDirectionBeingProcessed = s;
                            }
                        } else {
                            if ((i != 0 || r->nextBase != 1) && r->runnerOnFieldOrOutOrScored == 1) {
                                r->nextDirectionBeingProcessed = s;
                            }
                            if (r->nextDirectionBeingProcessed == 3 && r->tagUpInd != 3 && r->baseStandingOn >= 0) {
                                r->nextDirectionBeingProcessed = 0;
                            }
                        }
                    }
                }
                v = fn_3_7FA78(i);
                if (v != 0) {
                    r->nextDirectionBeingProcessed = v;
                }
            }
            if (r->runningToDugoutInd != 0) {
                r->baseRoundingState = 0;
                r->actionCode = 0;
            } else {
                fn_3_7ECFC(i);
                fn_3_7F494(i);
                if (g_GameLogic.secondaryGameMode != 6) {
                    if (i == 0 && r->nextBase == 1) {
                        fn_3_7F2D8();
                    } else if (r->baseRoundingState == 1) {
                        r->baseRoundingState = 0;
                    }
                    fn_3_7EBD4(i);
                }
            }
            fn_3_82670(i);
            fn_3_81190(i);
            fn_3_80028(i);
            fn_3_8307C(i);
            dx = g_Ball.AtBat_Contact_BallPos.x - r->position.x;
            dz = g_Ball.AtBat_Contact_BallPos.z - r->position.z;
            r->distanceFromBall = sqrt13B8(dx * dx + dz * dz);
        }
    }
    fn_3_87AE8();
    if (g_GameLogic.secondaryGameMode == 6) {
        fn_3_87CC8();
    } else {
        fn_3_88408();
        fn_3_88B18();
        for (i = 0, r = g_Runners; i < 4; i++, r++) {
            if (r->runnerOnFieldOrOutOrScored == 1) {
                acr = g_Ball.AtBat_ContactResult;
                if ((acr == 3 || g_FieldingLogic._108 == 2) && g_Ball.landingSpotZoneAwayFromHome <= 1) {
                    r->isEligibleToScore = 0;
                } else if (g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.ballState != 0 && (u16)g_Ball.AtBat_ContactResult > 1) {
                    if (r->currentBase != 0 && r->currentBase < 3) {
                        r->isEligibleToScore = 0;
                    }
                }
            }
        }
        fn_3_87E80();
    }
    fn_3_8781C();
}
#endif

#pragma dont_inline off
