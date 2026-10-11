#include "game/rep_540.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "header_rep_data.h"
#include "stl/math.h"

// One g_Fielders entry (stride 0x268); only the fields used by this unit.
typedef struct Fielder540 {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ u8 _00C[0x74 - 0xC];
    /*0x074*/ f32 _74;
    /*0x078*/ u8 _078[0x17A - 0x78];
    /*0x17A*/ s16 animID; // index into lbl_800E8558 (6 bytes per entry)
    /*0x17C*/ u8 _17C[0x1C7 - 0x17C];
    /*0x1C7*/ u8 _1C7;
    /*0x1C8*/ u8 _1C8[0x268 - 0x1C8];
} Fielder540; // size: 0x268

extern Fielder540 g_Fielders[9];

// g_Ball keeps 60 past positions: pastCoordinates[27] runs on into
// physicsSubstruct.startOfWallJumpChecksMaybe[33] (contiguous VecXYZ).
#define BALL_PAST(i) (g_Ball.pastCoordinates[i])

extern u8 lbl_3_data_450C[];
extern f32 lbl_3_data_4428[];
extern int fn_3_B7D6C(f32, f32);
extern void fn_3_8FF5C(s32, void*, f32, f32, f32);
extern u8 lbl_800E8558[];
extern int getAnimRelatedCoordinates(int, int, void*);
typedef struct {
    f32 f0, f4, f8, fC, f10;
} Row4388;
extern Row4388 lbl_3_data_4388[];
extern u8 lbl_3_data_4414[];
extern int fn_3_B7E10(f32, f32);
extern void fn_3_8C5C8(void);
extern u8 lbl_3_data_4444[];
extern u8 lbl_3_data_4604[];
extern u8 lbl_3_data_4608;
extern int RandomInt_Game(int);
extern void getComponentsFromSAng(s16, f32*, f32*);
extern int fn_3_B7DD8(f32, f32);
extern f64 lbl_3_rodata_600;
extern void fn_3_88D88(s32);
extern void fn_3_27648(void);

extern s16 g_RunningLogic;
extern void fn_3_59918(s32, s32);

extern const f64 lbl_3_rodata_5B8;
extern const f64 lbl_3_rodata_5C0;
extern const f64 lbl_3_rodata_5C8;



// lbl_3_data_228 is a 0x14-byte object; its first word is a running counter.
typedef struct {
    /*0x00*/ u32 counter;
    /*0x04*/ u8 _04[0x10];
} RandSeedObj;
extern RandSeedObj lbl_3_data_228;

// Same as fn_3_FF98 (reseeds g_Ball's static random ints).
static inline void ballReseedRandom(void) {
    s32 a;
    a = (((lbl_3_data_228.counter % 10) + 1) * (g_Ball.StaticRandomInt2 * g_Ball.StaticRandomInt1) + g_Ball.StaticRandomInt2 * 16 + (s32)(lbl_3_data_228.counter >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu) & 0x7FFF;
    g_Ball.StaticRandomInt1 = a;
    g_Ball.StaticRandomInt1_prePitch = a;
    g_Ball.StaticRandomInt2 = (((lbl_3_data_228.counter % 10) + 1) * (g_Ball.StaticRandomInt2 * (g_Ball.StaticRandomInt2 + 1)) + a * 8 + (s32)(lbl_3_data_228.counter >> 1) + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1)) & 0x7FFF;
}

static inline float sqrt540(float x) {
    if (x > 0.0f) {
        double half = lbl_3_rodata_5B8;
        double three = lbl_3_rodata_5C0;
        double xd = (double)x;
        double guess = __frsqrte(xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        return (float)(xd * guess);
    } else if (x < lbl_3_rodata_5C8)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}

// .text:0x00006530 size:0x78 mapped:0x806455C4
void fn_3_6530(void) {
    g_Ball.someCollisionInd = 1;
    if (g_Ball.ballState == 2) {
        g_Ball.ballState = 1;
    }
    g_Ball.currentStarSwing = 0;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.someCollisionInd = 1;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    fn_3_27648();
}

// .text:0x000065A8 size:0x20 mapped:0x8064563C
void fn_3_65A8(void) {
    if (g_Ball.ballState == 2) {
        g_Ball.ballState = 1;
    }
}

// .text:0x000065C8 size:0x2C mapped:0x8064565C
void fn_3_65C8(void) {
    if (g_Ball.matchFramesAndBallAngle.framesInsidePlant < 0x7FFE) {
        g_Ball.matchFramesAndBallAngle.framesInsidePlant += 1;
    } else {
        g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0x7FFF;
    }
}

// .text:0x000065F4 size:0x2C mapped:0x80645688

void fn_3_65F4(void) {
    g_Ball.pauseBallMovementWhenInPlant = 0;
    g_FieldingLogic._13B = 1;
    g_Ball.frameCountdownAfterLeavingPlant = 3;
}

// .text:0x00006620 size:0x74 mapped:0x806456B4
void fn_3_6620(void) {
    if (g_Ball.pauseBallMovementWhenInPlant == 0) {
        g_Ball.pauseBallMovementWhenInPlant = 1;
        g_Ball.ballCughtByPlantInd = 1;
        g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0;
        g_Ball.someCollisionVariable = 0;
        g_Ball.currentStarSwing = 0;
        g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
        g_Ball.someCollisionInd = 1;
        g_Ball.warioWaluGarlicIsActive = 0;
        g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
        g_Ball.physicsSubstruct.acceleration.x = 0.0f;
        g_Ball.physicsSubstruct.acceleration.y = 0.0f;
        g_Ball.physicsSubstruct.acceleration.z = 0.0f;
        fn_3_27648();
    }
}

// .text:0x00006694 size:0x5A4 mapped:0x80645728
void fn_3_6694(void) {
    s32 low = g_Ball.collisionCode & 0x7F;
    s32 hit = g_Ball.collisionCode & 0x80;
    s32 done;
    if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
        hit = 1;
    }
    if (low == 3 && g_Ball.deadBallReason == 0) {
        switch (g_Ball.AtBat_ContactResult) {
        case -1:
            if (g_Ball.deadBallReason == 0) {
                g_Ball.deadBallReason = 2;
                done = 0;
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.AtBat_ContactResult = -1;
                g_Ball.ballInitialHitDoneInd = 1;
                if (g_FieldingLogic._110 != 1) {
                    g_FieldingLogic._110 = 1;
                    g_Strikes.strikes = g_Strikes.strikes + 1;
                    if (g_Strikes.strikes >= 3) {
                        if (g_Ball.maybeBuntInd != 0) {
                            g_Ball.maybebuntOn2Strikes = 1;
                            fn_3_88D88(0);
                            done = 1;
                        } else {
                            g_Strikes.strikes = 2;
                        }
                    }
                    if (done == 0) {
                        fn_3_59918(3, 0);
                    }
                }
            }
            break;
        case 0:
            if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames >= 5) {
                if (hit != 0) {
                    if (g_Ball.deadBallReason == 0) {
                        g_Ball.deadBallReason = 2;
                        done = 0;
                        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                        g_Ball.AtBat_ContactResult = -1;
                        g_Ball.ballInitialHitDoneInd = 1;
                        if (g_FieldingLogic._110 != 1) {
                            g_FieldingLogic._110 = 1;
                            g_Strikes.strikes = g_Strikes.strikes + 1;
                            if (g_Strikes.strikes >= 3) {
                                if (g_Ball.maybeBuntInd != 0) {
                                    g_Ball.maybebuntOn2Strikes = 1;
                                    fn_3_88D88(0);
                                    done = 1;
                                } else {
                                    g_Strikes.strikes = 2;
                                }
                            }
                            if (done == 0) {
                                fn_3_59918(3, 0);
                            }
                        }
                    }
                } else if (g_Ball.deadBallReason == 0) {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 1;
                    g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
                    g_Ball.AtBat_ContactResult = 1;
                    g_Ball.ballInitialHitDoneInd = 1;
                    if (g_d_GameSettings.GameModeSelected != 6) {
                        fn_3_59918(0xF, 0);
                    }
                }
            }
            break;
        case 1:
            if (g_Ball.ballInitialHitDoneInd == 0 && hit != 0) {
                if (g_Ball.deadBallReason == 0) {
                    g_Ball.deadBallReason = 2;
                    done = 0;
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.AtBat_ContactResult = -1;
                    g_Ball.ballInitialHitDoneInd = 1;
                    if (g_FieldingLogic._110 != 1) {
                        g_FieldingLogic._110 = 1;
                        g_Strikes.strikes = g_Strikes.strikes + 1;
                        if (g_Strikes.strikes >= 3) {
                            if (g_Ball.maybeBuntInd != 0) {
                                g_Ball.maybebuntOn2Strikes = 1;
                                fn_3_88D88(0);
                                done = 1;
                            } else {
                                g_Strikes.strikes = 2;
                            }
                        }
                        if (done == 0) {
                            fn_3_59918(3, 0);
                        }
                    }
                }
            } else if ((g_Ball.maybeCollisionRelated & 0x7F) == 3 && g_Ball.deadBallReason == 0) {
                if (g_FieldingLogic._107 != 0) {
                    if (g_Ball.deadBallReason != 4) {
                        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                        g_Ball.deadBallReason = 4;
                        if (g_RunningLogic != 0) {
                            fn_3_59918(0x14, 0);
                        }
                    }
                } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
                    if (g_Ball.deadBallReason != 4) {
                        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                        g_Ball.deadBallReason = 4;
                        if (g_RunningLogic != 0) {
                            fn_3_59918(0x14, 0);
                        }
                    }
                } else {
                    g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                    g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                    g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                    g_Ball.deadBallReason = 3;
                    fn_3_59918(7, 0);
                }
            }
            break;
        default:
            if (g_Ball.deadBallReason != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
            break;
        }
        if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames == 0) {
            g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
        }
    } else if (g_Ball.AtBat_ContactResult == 1 && g_Ball.ballInitialHitDoneInd == 0 && g_Ball.AtBat_Contact_BallPos.z > *(f32*)(lbl_3_data_4444 + 0xC)) {
        g_Ball.ballInitialHitDoneInd = 1;
        if (hit != 0) {
            g_Ball.AtBat_ContactResult = -1;
            done = 0;
            g_Ball.ballInitialHitDoneInd = 1;
            if (g_FieldingLogic._110 != 1) {
                g_FieldingLogic._110 = 1;
                g_Strikes.strikes = g_Strikes.strikes + 1;
                if (g_Strikes.strikes >= 3) {
                    if (g_Ball.maybeBuntInd != 0) {
                        g_Ball.maybebuntOn2Strikes = 1;
                        fn_3_88D88(0);
                        done = 1;
                    } else {
                        g_Strikes.strikes = 2;
                    }
                }
                if (done == 0) {
                    fn_3_59918(3, 0);
                }
            }
        } else {
            g_Ball.AtBat_ContactResult = 1;
            if (g_d_GameSettings.GameModeSelected != 6 && fn_3_B7D6C(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
                fn_3_59918(4, 1);
            }
        }
    }
}

// .text:0x00006C38 size:0x20B8 mapped:0x80645CCC
void fn_3_6C38(void) {
    return;
}

// .text:0x00008CF0 size:0x35C mapped:0x80647D84
void fn_3_8CF0(f32* p, s32 n, u8* flag, s32 skip) {
    s32 low = g_Ball.collisionCode & 0x7F;
    f32 sp10;
    f32 spC;
    f32 d;
    f32 v;
    s32 r;
    if ((g_Ball.currentStarSwing == 9 || g_Ball.currentStarSwing == 0xA) && skip == 0) {
        f32 dx = g_Ball.pastCoordinates[1].x - g_Ball.pastCoordinates[0].x;
        f32 dy = g_Ball.pastCoordinates[1].y - g_Ball.pastCoordinates[0].y;
        f32 dz = g_Ball.pastCoordinates[1].z - g_Ball.pastCoordinates[0].z;
        f32 sx = dx * dx;
        f32 sy = dy * dy;
        f32 sz = dz * dz;
        d = sqrt540(sz + (sx + sy));
        v = d * g_hitFloats.eggVeloMaintainedOnBounce;
        getComponentsFromSAng((s16)(RandomInt_Game(0x200) + 0x80), &sp10, &spC);
        *p = v * spC;
        v = v * sp10;
        r = RandomInt_Game(0x800);
        getComponentsFromSAng((s16)(g_Ball.ballTravelAngle + r - 0x400), &sp10, &spC);
        g_Ball.knockoutProcessedFlag = 1;
        g_Ball.savedVelocity.x = v * sp10;
        g_Ball.savedVelocity.z = v * spC;
        g_FieldingLogic._13B = 1;
        fn_3_27648();
    } else if (g_d_GameSettings.GameModeSelected == 6 && low >= 0x70 && low < 0x79) {
        if (n == 0) {
            *p *= *(f32*)(lbl_3_data_4414 + 0);
        } else {
            *p *= *(f32*)(lbl_3_data_4414 + 4);
        }
    } else if (n == 0) {
        *p *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f0;
    } else {
        *p *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f4;
    }
    if (*flag == 0 && *p < *(f32*)(lbl_3_data_4604) && n >= lbl_3_data_4608) {
        *flag = 1;
    }
    if (*flag != 0) {
        *p = 0.0f;
    }
}

// .text:0x0000904C size:0x214 mapped:0x806480E0
void fn_3_904C(void) {
    u8 st;
    g_Ball.physicsSubstruct.velocity.x = 0.3f * g_Ball.physicsSubstruct.velocity.x;
    g_Ball.physicsSubstruct.velocity.y = 0.3f * g_Ball.physicsSubstruct.velocity.y;
    g_Ball.physicsSubstruct.velocity.z = 0.3f * g_Ball.physicsSubstruct.velocity.z;
    st = g_Ball.deadBallReason;
    if (st == 1) {
        g_Ball.homeRunInd = 1;
    } else if (g_Ball.AtBat_ContactResult != -1) {
        if (g_Ball.AtBat_ContactResult == 0 || st == 1 || (g_Ball.numberOfThrowsDuringPlay == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.framesOnGroundUntilPickedUp == 0)) {
            fn_3_9FA4();
            g_Ball.homeRunInd = 1;
        } else {
            fn_3_9E84();
        }
    }
}

// .text:0x00009260 size:0x2A8 mapped:0x806482F4
void fn_3_9260(s32 flags) {
    s32 done;
    s32 i;
    Fielder540* f;
    s32 low = flags & 0x7F;
    g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4428[g_d_GameSettings.StadiumID];
    g_Ball.physicsSubstruct.velocity.y *= lbl_3_data_4428[g_d_GameSettings.StadiumID];
    g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4428[g_d_GameSettings.StadiumID];
    if (low != 0xB && g_Ball.AtBat_ContactResult == 0) {
        if ((flags & 0x80) && g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
            done = 0;
            g_Ball.AtBat_ContactResult = -1;
            g_Ball.ballInitialHitDoneInd = 1;
            if (g_FieldingLogic._110 != 1) {
                g_FieldingLogic._110 = 1;
                g_Strikes.strikes = g_Strikes.strikes + 1;
                if (g_Strikes.strikes >= 3) {
                    if (g_Ball.maybeBuntInd != 0) {
                        g_Ball.maybebuntOn2Strikes = 1;
                        fn_3_88D88(0);
                        done = 1;
                    } else {
                        g_Strikes.strikes = 2;
                    }
                }
                if (done == 0) {
                    fn_3_59918(3, 0);
                }
            }
        } else {
            g_Ball.AtBat_ContactResult = 1;
            g_Ball.ballInitialHitDoneInd = 1;
            if (g_d_GameSettings.GameModeSelected != 6) {
                if (fn_3_B7D6C(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
                    fn_3_59918(4, 1);
                } else if (g_Ball.AtBat_Contact_BallPos.y < 5.0f) {
                    f = g_Fielders;
                    for (i = 0; i < 9; i++) {
                        if (f->_74 < 2.0f) {
                            fn_3_59918(4, 1);
                            break;
                        }
                        f++;
                    }
                }
            }
        }
    }
    switch (g_d_GameSettings.StadiumID) {
    case 0:
        fn_3_8FF5C(0x172, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    case 1:
        fn_3_8FF5C(0x1A1, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    case 2:
        fn_3_8FF5C(0x1A1, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    case 3:
        fn_3_8FF5C(0x1A3, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    case 4:
        fn_3_8FF5C(0x1A1, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    case 5:
        fn_3_8FF5C(0x172, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    case 6:
        fn_3_8FF5C(0x172, &g_Ball, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        break;
    }
}

// .text:0x00009508 size:0x300 mapped:0x8064859C
void fn_3_9508(void) {
    s32 low = g_Ball.collisionCode & 0x7F;
    u8 flag = g_Ball.ballIsRollingIndicator;
    s32 done;
    f32 v;
    if (g_Ball.knockoutProcessedFlag != 0) {
        g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
        g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
        g_Ball.knockoutProcessedFlag = 0;
    } else if (g_d_GameSettings.GameModeSelected == 6 && low >= 0x70 && low < 0x79) {
        if (flag != 0) {
            g_Ball.physicsSubstruct.velocity.x *= *(f32*)(lbl_3_data_4414 + 0x10);
            g_Ball.physicsSubstruct.velocity.z *= *(f32*)(lbl_3_data_4414 + 0x10);
        } else {
            g_Ball.physicsSubstruct.velocity.x *= *(f32*)(lbl_3_data_4414 + 0xC);
            g_Ball.physicsSubstruct.velocity.z *= *(f32*)(lbl_3_data_4414 + 0xC);
        }
    } else if (flag != 0) {
        VecXYZ* a = &g_Ball.physicsSubstruct.velocity;
        f32 m = lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
        a->x *= m;
        a->z *= m;
    } else {
        VecXYZ* a = &g_Ball.physicsSubstruct.velocity;
        f32 m = lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
        a->x *= m;
        a->z *= m;
    }
    if (g_Ball.ballInitialHitDoneInd == 0) {
        if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
            if (fn_3_B7DD8(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) == 0) {
                if (g_Ball.AtBat_Contact_BallPos.x > 0.0f) {
                    v = g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x;
                } else {
                    v = g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x;
                }
                if (v < -5.0f || g_Ball.ballVelocity < 0.05f) {
                    goto strike;
                }
            } else {
strike:
            done = 0;
            g_Ball.AtBat_ContactResult = -1;
            g_Ball.ballInitialHitDoneInd = 1;
            if (g_FieldingLogic._110 != 1) {
                g_FieldingLogic._110 = 1;
                g_Strikes.strikes = g_Strikes.strikes + 1;
                if (g_Strikes.strikes >= 3) {
                    if (g_Ball.maybeBuntInd != 0) {
                        g_Ball.maybebuntOn2Strikes = 1;
                        fn_3_88D88(0);
                        done = 1;
                    } else {
                        g_Strikes.strikes = 2;
                    }
                }
                if (done == 0) {
                    fn_3_59918(3, 0);
                }
            }
            }
        } else if (g_Ball.ballVelocity < 0.003f) {
            g_Ball.ballInitialHitDoneInd = 1;
        }
    } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.framesOnGroundUntilPickedUp == 0 && g_Ball.AtBat_ContactResult == 1) {
        fn_3_59918(4, 1);
    }
end:
    if (g_Ball.framesOnGroundUntilPickedUp < 3) {
        fn_3_8C5C8();
    }
}

// .text:0x00009808 size:0x36C mapped:0x8064889C
void fn_3_9808(void) {
    s32 low = g_Ball.collisionCode & 0x7F;
    s32 done;
    if (g_Ball.knockoutProcessedFlag != 0) {
        g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
        g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
        g_Ball.knockoutProcessedFlag = 0;
    } else if (g_d_GameSettings.GameModeSelected == 6 && low >= 0x70 && low < 0x79) {
        g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
        g_Ball.physicsSubstruct.velocity.x *= *(f32*)(lbl_3_data_4414 + 8);
        g_Ball.physicsSubstruct.velocity.z *= *(f32*)(lbl_3_data_4414 + 8);
    } else {
        VecXYZ* a = &g_Ball.physicsSubstruct.velocity;
        f32 m = lbl_3_data_4388[g_d_GameSettings.StadiumID].f8;
        a->x *= m;
        a->z *= m;
    }
    g_Ball.AtBat_ContactResult = 1;
    g_Ball.ballHitGrroundDistanceFromHome = g_Ball.ballDistanceFromHome;
    if (g_Ball.always0_fairFoulRelated == 1 || g_Ball.bobbleLocation_1fair_2foul == 2) {
        g_Ball.AtBat_ContactResult = -1;
        done = 0;
        g_Ball.ballInitialHitDoneInd = 1;
        if (g_FieldingLogic._110 != 1) {
            g_FieldingLogic._110 = 1;
            g_Strikes.strikes = g_Strikes.strikes + 1;
            if (g_Strikes.strikes >= 3) {
                if (g_Ball.maybeBuntInd != 0) {
                    g_Ball.maybebuntOn2Strikes = 1;
                    fn_3_88D88(0);
                    done = 1;
                } else {
                    g_Strikes.strikes = 2;
                }
            }
            if (done == 0) {
                fn_3_59918(3, 0);
            }
        }
    } else if (g_Ball.always0_fairFoulRelated == 2 || g_Ball.bobbleLocation_1fair_2foul == 1) {
        g_Ball.ballInitialHitDoneInd = 1;
        g_Ball.AtBat_ContactResult = 1;
        if (g_d_GameSettings.GameModeSelected != 6) {
            fn_3_59918(4, 1);
        }
    } else if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
        if (fn_3_B7DD8(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) == 0) {
            f32 v;
            if (g_Ball.AtBat_Contact_BallPos.x > 0.0f) {
                v = g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x;
            } else {
                v = g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x;
            }
            if (v < -5.0f || g_Ball.ballVelocity < 0.05f) {
                goto strike;
            }
        } else {
strike:
            g_Ball.AtBat_ContactResult = -1;
            done = 0;
            g_Ball.ballInitialHitDoneInd = 1;
            if (g_FieldingLogic._110 != 1) {
                g_FieldingLogic._110 = 1;
                g_Strikes.strikes = g_Strikes.strikes + 1;
                if (g_Strikes.strikes >= 3) {
                    if (g_Ball.maybeBuntInd != 0) {
                        g_Ball.maybebuntOn2Strikes = 1;
                        fn_3_88D88(0);
                        done = 1;
                    } else {
                        g_Strikes.strikes = 2;
                    }
                }
                if (done == 0) {
                    fn_3_59918(3, 0);
                }
            }
        }
    } else if (fn_3_B7DD8(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
        g_Ball.ballInitialHitDoneInd = 1;
        if (fn_3_B7D6C(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0 && g_d_GameSettings.GameModeSelected != 6) {
            fn_3_59918(4, 1);
        }
    }
    fn_3_8C5C8();
}

// .text:0x00009B74 size:0x16C mapped:0x80648C08
#pragma opt_common_subs off
void fn_3_9B74(void) {
    f32 v;
    f32 a;
    if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x > 0.0f) {
        v = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    } else {
        v = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
    }
    if (v < -5.0f) {
        g_Ball.howFoulTheBallWillBe = 3;
    } else if (v < -20.0f) {
        g_Ball.howFoulTheBallWillBe = 2;
    } else if (v < -10.0f) {
        g_Ball.howFoulTheBallWillBe = 1;
    } else {
        g_Ball.howFoulTheBallWillBe = 0;
    }
    if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 110.0f) {
        a = g_Ball.ballWillHitBallPos.x;
        if (a < 0.0f) {
            a = -a;
        }
        v = g_Ball.ballWillHitBallPos.z - a;
        if (v < -5.0f) {
            g_Ball.howFoulTheBallWillBe = 3;
        } else if (v < -20.0f) {
            g_Ball.howFoulTheBallWillBe = 2;
        } else if (v < -10.0f) {
            g_Ball.howFoulTheBallWillBe = 1;
        } else {
            g_Ball.howFoulTheBallWillBe = 0;
        }
    }
    if (g_Ball.deadBallReason == 1) {
        g_Ball.howFoulTheBallWillBe = 0;
    }
}
#pragma opt_common_subs reset

// .text:0x00009CE0 size:0x138 mapped:0x80648D74
f32 fn_3_9CE0(f32 x, f32 z) {
    f32 dx = x - g_Ball.AtBat_Contact_BallPos.x;
    f32 dz = z - g_Ball.AtBat_Contact_BallPos.z;
    f32 t = g_Ball.ballVelocityPercent.x * dx + g_Ball.ballVelocityPercent.z * dz;
    f32 d = dx * dx + dz * dz - t * t;
    if (d < 0.0f) return 0.0f;
    return sqrt540(d);
}

// .text:0x00009E18 size:0x6C mapped:0x80648EAC
void fn_3_9E18(void) {
    if (g_Ball.deadBallReason != 4) {
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.deadBallReason = 4;
        if (g_RunningLogic != 0) {
            fn_3_59918(0x14, 0);
        }
    }
}

// .text:0x00009E84 size:0x120 mapped:0x80648F18
void fn_3_9E84(void) {
    u8 st = g_Ball.deadBallReason;
    if (st == 0) {
        if (g_FieldingLogic._107 != 0) {
            if (st != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
            if (st != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else {
            g_Ball.deadBallReason = 3;
            g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
            fn_3_59918(7, 0);
        }
    }
}

// .text:0x00009FA4 size:0x7C mapped:0x80649038
void fn_3_9FA4(void) {
    if (g_Ball.deadBallReason == 0) {
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.deadBallReason = 1;
        g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
        g_Ball.AtBat_ContactResult = 1;
        g_Ball.ballInitialHitDoneInd = 1;
        if (g_d_GameSettings.GameModeSelected != 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x0000A020 size:0xD0 mapped:0x806490B4
void fn_3_A020(void) {
    s32 done;
    if (g_Ball.deadBallReason == 0) {
        g_Ball.deadBallReason = 2;
        done = 0;
        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.AtBat_ContactResult = -1;
        g_Ball.ballInitialHitDoneInd = 1;
        if (g_FieldingLogic._110 != 1) {
            g_FieldingLogic._110 = 1;
            g_Strikes.strikes = g_Strikes.strikes + 1;
            if (g_Strikes.strikes >= 3) {
                if (g_Ball.maybeBuntInd != 0) {
                    g_Ball.maybebuntOn2Strikes = 1;
                    fn_3_88D88(0);
                    done = 1;
                } else {
                    g_Strikes.strikes = 2;
                }
            }
            if (done == 0) {
                fn_3_59918(3, 0);
            }
        }
    }
}

// .text:0x0000A0F0 size:0xA8 mapped:0x80649184
void fn_3_A0F0(void) {
    s32 done;
    g_Ball.AtBat_ContactResult = -1;
    g_Ball.ballInitialHitDoneInd = 1;
    done = 0;
    if (g_FieldingLogic._110 != 1) {
        g_FieldingLogic._110 = 1;
        g_Strikes.strikes = g_Strikes.strikes + 1;
        if (g_Strikes.strikes >= 3) {
            if (g_Ball.maybeBuntInd != 0) {
                g_Ball.maybebuntOn2Strikes = 1;
                fn_3_88D88(0);
                done = 1;
            } else {
                g_Strikes.strikes = 2;
            }
        }
        if (done == 0) {
            fn_3_59918(3, 0);
        }
    }
}

// .text:0x0000A198 size:0x6A4 mapped:0x8064922C
void fn_3_A198(void) {
    return;
}

// .text:0x0000A83C size:0x134 mapped:0x806498D0
void fn_3_A83C(void) {
    int i;
    VecXYZ* p = &BALL_PAST(54);
    for (i = 0x3B; i != 0; i--) {
        p[5].x = p[4].x;
        p[5].y = p[4].y;
        p[5].z = p[4].z;
        p--;
    }
    if (g_Ball.catchAnimationTotalFrames != 0 || g_Ball.fielderActionOccuring != 0) {
        g_Ball.pastCoordinates[0].x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.pastCoordinates[0].y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.pastCoordinates[0].z = g_Ball.fielderActionCatchCoords.z;
    } else {
        g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    if (g_Ball.currentStarSwing == 3 || g_Ball.currentStarSwing == 4) {
        for (i = 9; i > 0; i--) {
            g_Ball.warioStarHitCoords[i + 3].x = g_Ball.warioStarHitCoords[i + 2].x;
            g_Ball.warioStarHitCoords[i + 3].y = g_Ball.warioStarHitCoords[i + 2].y;
            g_Ball.warioStarHitCoords[i + 3].z = g_Ball.warioStarHitCoords[i + 2].z;
        }
        g_Ball.warioStarHitCoords[3].x = g_Ball.warioStarHitCoords[0].x;
        g_Ball.warioStarHitCoords[3].y = g_Ball.warioStarHitCoords[0].y;
        g_Ball.warioStarHitCoords[3].z = g_Ball.warioStarHitCoords[0].z;
    }
}

// .text:0x0000A970 size:0xAD0 mapped:0x80649A04
void fn_3_A970(s32 arg) {
    return;
}

// .text:0x0000B440 size:0x500 mapped:0x8064A4D4
void fn_3_B440(void) {
    return;
}

// .text:0x0000B940 size:0x27C mapped:0x8064A9D4
void fn_3_B940(void) {
    Fielder540* fl;
    s32 shifted = 0;
    s32 i;
    s32 idx = g_Ball.fielderWBallIndex;
    s32 id = idx;
    f32 p[3];
    s16 anim;
    if (idx >= 0) {
        fl = &g_Fielders[idx];
        if (g_d_GameSettings.minigamesEnabled != 0) {
            // TODO type: per-fielder player slot table at g_Minigame + 0x18F2
            id = g_Minigame.minigameControlStruct[0].characterIndex[((s8*)&g_Minigame)[idx + 0x18F2]];
        }
        anim = fl->animID;
        if (anim == 0x11 && g_FieldingLogic._109 != 0) {
            getAnimRelatedCoordinates(id, 0x42, p);
        } else if (anim == 0x26) {
            getAnimRelatedCoordinates(id, 9, p);
        } else if (lbl_800E8558[anim * 6 + 1] == 0x21) {
            if (fl->_1C7 == 0) {
                getAnimRelatedCoordinates(id, 0x4F, p);
            } else {
                getAnimRelatedCoordinates(id, 0x4E, p);
            }
            shifted = 1;
        } else if (fl->_1C7 == 0) {
            getAnimRelatedCoordinates(id, 0x19, p);
        } else {
            getAnimRelatedCoordinates(id, 0x13, p);
        }
        if (shifted != 0) {
            if (g_Ball.timeSinceBallPickedUp <= 1) {
                f32 x = p[0] - fl->pos.x;
                f32 y = -p[1] - fl->pos.y;
                f32 z = p[2] - fl->pos.z;
                g_Ball.offsetWhilePickedUpHistory[0].x = x;
                g_Ball.offsetWhilePickedUpHistory[0].y = y;
                g_Ball.offsetWhilePickedUpHistory[0].z = z;
                g_Ball.offsetWhilePickedUpHistory[1].x = x;
                g_Ball.offsetWhilePickedUpHistory[1].y = y;
                g_Ball.offsetWhilePickedUpHistory[1].z = z;
                g_Ball.offsetWhilePickedUpHistory[2].x = x;
                g_Ball.offsetWhilePickedUpHistory[2].y = y;
                g_Ball.offsetWhilePickedUpHistory[2].z = z;
                g_Ball.offsetWhilePickedUpHistory[3].x = x;
                g_Ball.offsetWhilePickedUpHistory[3].y = y;
                g_Ball.offsetWhilePickedUpHistory[3].z = z;
            } else {
                for (i = 3; i > 1; i--) {
                    g_Ball.offsetWhilePickedUpHistory[i].x = g_Ball.offsetWhilePickedUpHistory[i - 1].x;
                    g_Ball.offsetWhilePickedUpHistory[i].y = g_Ball.offsetWhilePickedUpHistory[i - 1].y;
                    g_Ball.offsetWhilePickedUpHistory[i].z = g_Ball.offsetWhilePickedUpHistory[i - 1].z;
                }
                g_Ball.offsetWhilePickedUpHistory[1].x = g_Ball.offsetWhilePickedUpHistory[0].x;
                g_Ball.offsetWhilePickedUpHistory[1].y = g_Ball.offsetWhilePickedUpHistory[0].y;
                g_Ball.offsetWhilePickedUpHistory[1].z = g_Ball.offsetWhilePickedUpHistory[0].z;
                g_Ball.offsetWhilePickedUpHistory[0].x = p[0] - fl->pos.x;
                g_Ball.offsetWhilePickedUpHistory[0].y = -p[1] - fl->pos.y;
                g_Ball.offsetWhilePickedUpHistory[0].z = p[2] - fl->pos.z;
            }
        } else {
            g_Ball.offsetWhilePickedUpHistory[0].x = p[0] - fl->pos.x;
            g_Ball.offsetWhilePickedUpHistory[0].y = -p[1] - fl->pos.y;
            g_Ball.offsetWhilePickedUpHistory[0].z = p[2] - fl->pos.z;
        }
    }
}

// .text:0x0000BBBC size:0x98 mapped:0x8064AC50
s32 fn_3_BBBC(f32* out, s32 n, s32 step, f32 x, f32 z) {
    f32 best = 100000000.0f;
    s32 i;
    s32 found = -1;
    for (i = 0; i < n; i += step) {
        f32 dx = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - x;
        f32 dz = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - z;
        f32 d = dx * dx + dz * dz;
        if (d < best) {
            best = d;
            found = i;
        } else {
            break;
        }
    }
    if (found < 0) {
        return -1;
    }
    out[0] = g_Ball.physicsSubstruct.futureCoordsAndDist[found].pos.x;
    out[1] = g_Ball.physicsSubstruct.futureCoordsAndDist[found].pos.y;
    out[2] = g_Ball.physicsSubstruct.futureCoordsAndDist[found].pos.z;
    return found;
}

// .text:0x0000BC54 size:0x124 mapped:0x8064ACE8
void fn_3_BC54(void) {
    f32 v;
    if (fn_3_B7DD8(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) == 0) {
        if (g_Ball.AtBat_Contact_BallPos.x > 0.0f) {
            v = g_Ball.AtBat_Contact_BallPos.z - g_Ball.AtBat_Contact_BallPos.x;
        } else {
            v = g_Ball.AtBat_Contact_BallPos.z + g_Ball.AtBat_Contact_BallPos.x;
        }
        if (!(v < -5.0f || g_Ball.ballVelocity < 0.05f)) {
            return;
        }
    }
    fn_3_A0F0();
}

// .text:0x0000BD78 size:0x2BC mapped:0x8064AE0C
void fn_3_BD78(void) {
    s32 zone = -1;
    f32 d;
    if (g_Ball.Hit_HorizontalAngle > 0xC00) {
        zone = 0;
    } else if (g_Ball.Hit_HorizontalAngle < 0x400 && g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00) {
        zone = 0;
    } else if (g_Ball.Hit_HorizontalAngle > 0x800) {
        zone = 1;
    } else if (g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00) {
        zone = 1;
    } else if (g_Ball.Hit_HorizontalAngle < 0x1B0) {
        zone = 2;
    } else if (g_Ball.Hit_HorizontalAngle > 0x650) {
        zone = 3;
    }
    if (zone == 0 || zone == 2) {
        g_Ball.hitClassification3 = 7;
    } else if (zone == 1 || zone == 3) {
        g_Ball.hitClassification3 = 8;
    } else {
        d = sqrt540(g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x + g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z);
        if (d < 3.5f) {
            g_Ball.hitClassification3 = 0;
            return;
        }
        if (d < 8.0f) {
            g_Ball.hitClassification3 = 1;
            return;
        }
        if (d < 10.0f) {
            if (g_Ball.Hit_HorizontalAngle < 0x340) {
                g_Ball.hitClassification3 = 2;
                return;
            }
            if (g_Ball.Hit_HorizontalAngle >= 0x4C0) {
                g_Ball.hitClassification3 = 4;
                return;
            }
            g_Ball.hitClassification3 = 3;
            return;
        }
        if (g_Ball.hitClassification2 <= 4) {
            g_Ball.hitClassification3 = 5;
            return;
        }
        g_Ball.hitClassification3 = 6;
        return;
    }
}

// .text:0x0000C034 size:0x9C0 mapped:0x8064B0C8
void fn_3_C034(void) {
    return;
}

// .text:0x0000C9F4 size:0x434 mapped:0x8064BA88
void fn_3_C9F4(void) {
    int i;
    VecXYZ* p;
    f32 d;
    s16 v;
    if (g_Ball.framesSinceHit < 0x7FFE) {
        g_Ball.framesSinceHit += 1;
    } else {
        g_Ball.framesSinceHit = 0x7FFF;
    }
    if (g_Ball.timeSinceBallPickedUp < 0x7FFE) {
        g_Ball.timeSinceBallPickedUp += 1;
    } else {
        g_Ball.timeSinceBallPickedUp = 0x7FFF;
    }
    v = g_Ball.framesSinceBallHitGroundOrWasCaught;
    if (v == -1) {
        g_Ball.framesSinceBallHitGroundOrWasCaught = 1;
    } else if (v < 0x7FFE) {
        g_Ball.framesSinceBallHitGroundOrWasCaught = v + 1;
    } else {
        g_Ball.framesSinceBallHitGroundOrWasCaught = 0x7FFF;
    }
    p = &BALL_PAST(54);
    for (i = 0x3B; i != 0; i--) {
        p[5].x = p[4].x;
        p[5].y = p[4].y;
        p[5].z = p[4].z;
        p--;
    }
    if (g_Ball.catchAnimationTotalFrames != 0 || g_Ball.fielderActionOccuring != 0) {
        g_Ball.pastCoordinates[0].x = g_Ball.fielderActionCatchCoords.x;
        g_Ball.pastCoordinates[0].y = g_Ball.fielderActionCatchCoords.y;
        g_Ball.pastCoordinates[0].z = g_Ball.fielderActionCatchCoords.z;
    } else {
        g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    }
    if (g_Ball.currentStarSwing == 3 || g_Ball.currentStarSwing == 4) {
        for (i = 9; i > 0; i--) {
            g_Ball.warioStarHitCoords[i + 3].x = g_Ball.warioStarHitCoords[i + 2].x;
            g_Ball.warioStarHitCoords[i + 3].y = g_Ball.warioStarHitCoords[i + 2].y;
            g_Ball.warioStarHitCoords[i + 3].z = g_Ball.warioStarHitCoords[i + 2].z;
        }
        g_Ball.warioStarHitCoords[3].x = g_Ball.warioStarHitCoords[0].x;
        g_Ball.warioStarHitCoords[3].y = g_Ball.warioStarHitCoords[0].y;
        g_Ball.warioStarHitCoords[3].z = g_Ball.warioStarHitCoords[0].z;
    }
    if (g_Ball.fielderWBallIndex >= 0) {
        g_Ball.AtBat_Contact_BallPos.x = g_Fielders[g_Ball.fielderWBallIndex].pos.x;
        g_Ball.AtBat_Contact_BallPos.y = g_Fielders[g_Ball.fielderWBallIndex].pos.y;
        g_Ball.AtBat_Contact_BallPos.z = g_Fielders[g_Ball.fielderWBallIndex].pos.z;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = g_Ball.AtBat_Contact_BallPos.z;
    }
    d = sqrt540(g_Ball.AtBat_Contact_BallPos.x * g_Ball.AtBat_Contact_BallPos.x + g_Ball.AtBat_Contact_BallPos.z * g_Ball.AtBat_Contact_BallPos.z);
    g_Ball.ballDistanceFromHome = d;
    {
        s32 u;
        for (u = 0; u < 0x168; u++) {
        g_Ball.physicsSubstruct.futureCoordsAndDist[u].pos.x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.physicsSubstruct.futureCoordsAndDist[u].pos.y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.physicsSubstruct.futureCoordsAndDist[u].pos.z = g_Ball.AtBat_Contact_BallPos.z;
        }
    }
    g_Ball.ballOnMoundInd = 0;
    g_Ball.framesSinceLastBounce = -1;
    if (g_Ball.currentStarSwing != 0) {
        g_Ball.currentStarSwing = 0;
        g_Batter.invisibleBallForPeachStarHit = 0;
        g_Ball.warioWaluGarlicIsActive = 0;
    }
}

// .text:0x0000CE28 size:0xBC4 mapped:0x8064BEBC
void estimateAndSetFutureCoords(int) {
    return;
}

// .text:0x0000D9EC size:0x1E4 mapped:0x8064CA80
void fn_3_D9EC(void) {
    f32 r = sqrt540(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x + g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
    f64 d = r;
    f32 e;
    g_Ball.ballVelocity = r;
    g_Ball.ballStoppingCode1ReallySlow2Stopped = 0;
    e = (f32)d;
    if (0.0f != e) {
        g_Ball.ballVelocityPercent.x = g_Ball.physicsSubstruct.velocity.x / e;
        g_Ball.ballVelocityPercent.z = g_Ball.physicsSubstruct.velocity.z / e;
    }
    if (g_Ball.ballVelocity <= 0.1f && g_Ball.AtBat_Contact_BallPos.y <= 0.08f && g_Ball.physicsSubstruct.velocity.y < 0.01f && g_Ball.physicsSubstruct.velocity.y > -0.01f) {
        if (g_Ball.ballVelocity < 0.005f) {
            g_Ball.ballStoppingCode1ReallySlow2Stopped = 2;
            g_Ball.physicsSubstruct.velocity.x = 0.0f;
            g_Ball.physicsSubstruct.velocity.z = 0.0f;
            g_Ball.ballVelocity = 0.0f;
        } else {
            g_Ball.ballStoppingCode1ReallySlow2Stopped = 1;
        }
    }
}

// .text:0x0000DBD0 size:0x78 mapped:0x8064CC64
void fn_3_DBD0(void) {
    f32 t = 1.0f - (f32)g_Ball.airResistance / 10000.0f;
    g_Ball.physicsSubstruct.velocity.x = g_Ball.physicsSubstruct.velocity.x * t;
    g_Ball.physicsSubstruct.velocity.y = g_Ball.physicsSubstruct.velocity.y * t;
    g_Ball.physicsSubstruct.velocity.z = g_Ball.physicsSubstruct.velocity.z * t;
}

// .text:0x0000DC48 size:0x68C mapped:0x8064CCDC
void fn_3_DC48(void) {
    return;
}

// .text:0x0000E2D4 size:0xB78 mapped:0x8064D368
void fn_3_E2D4(void) {
    return;
}

// .text:0x0000EE4C size:0x390 mapped:0x8064DEE0
void fn_3_EE4C(void) {
    return;
}

// .text:0x0000F1DC size:0x39C mapped:0x8064E270
void fn_3_F1DC(void) {
    return;
}

// .text:0x0000F578 size:0x240 mapped:0x8064E60C
void fn_3_F578(void) {
    s32 i;
    g_Ball.AtBat_Contact_BallPos.x = *(f32*)(lbl_3_data_450C + 0);
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = *(f32*)(lbl_3_data_450C + 4);
    if (g_Minigame.GameMode_MiniGame == 6) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 0x3C; i++) {
        BALL_PAST(i).x = g_Ball.AtBat_Contact_BallPos.x;
        BALL_PAST(i).y = g_Ball.AtBat_Contact_BallPos.y;
        BALL_PAST(i).z = g_Ball.AtBat_Contact_BallPos.z;
    }
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    ballReseedRandom();
    g_Ball.deadBallReason = 0;
}

// .text:0x0000F7B8 size:0x240 mapped:0x8064E84C
void fn_3_F7B8(void) {
    s32 i;
    g_Ball.AtBat_Contact_BallPos.x = *(f32*)(lbl_3_data_450C + 0);
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = *(f32*)(lbl_3_data_450C + 4);
    if (g_Minigame.GameMode_MiniGame == 6) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 0x3C; i++) {
        BALL_PAST(i).x = g_Ball.AtBat_Contact_BallPos.x;
        BALL_PAST(i).y = g_Ball.AtBat_Contact_BallPos.y;
        BALL_PAST(i).z = g_Ball.AtBat_Contact_BallPos.z;
    }
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    ballReseedRandom();
    g_Ball.fielderWBallIndex = -1;
}

// .text:0x0000F9F8 size:0x1B0 mapped:0x8064EA8C
void fn_3_F9F8(void) {
    s32 i;
    g_Ball.AtBat_Contact_BallPos.x = *(f32*)(lbl_3_data_450C + 0);
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = *(f32*)(lbl_3_data_450C + 4);
    if (g_Minigame.GameMode_MiniGame == 6) {
        g_Ball.AtBat_Contact_BallPos.x = 0.0f;
        g_Ball.AtBat_Contact_BallPos.z = 0.0f;
        g_Ball.AtBat_Contact_BallPos.y = 1.0f;
    }
    for (i = 0; i < 0x3C; i++) {
        BALL_PAST(i).x = g_Ball.AtBat_Contact_BallPos.x;
        BALL_PAST(i).y = g_Ball.AtBat_Contact_BallPos.y;
        BALL_PAST(i).z = g_Ball.AtBat_Contact_BallPos.z;
    }
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
}

// .text:0x0000FBA8 size:0x3A4 mapped:0x8064EC3C
void fn_3_FBA8(void) {
    return;
}
