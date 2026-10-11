#include "game/rep_540.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/rep_1838.h"
#include "game/rep_D0.h"
#include "Dolphin/rand.h"
#include "header_rep_data.h"
#include "stl/math.h"

// One g_Fielders entry (stride 0x268); only the fields used by this unit.
typedef struct Fielder540 {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ u8 _00C[0x74 - 0xC];
    /*0x074*/ f32 _74;
    /*0x078*/ u8 _078[0xF4 - 0x78];
    /*0x0F4*/ f32 _F4; // height (used for the pitcher, index 0)
    /*0x0F8*/ u8 _0F8[0x17A - 0xF8];
    /*0x17A*/ s16 animID; // index into lbl_800E8558 (6 bytes per entry)
    /*0x17C*/ u8 _17C[0x1C7 - 0x17C];
    /*0x1C7*/ u8 _1C7;
    /*0x1C8*/ u8 _1C8;
    /*0x1C9*/ u8 _1C9;
    /*0x1CA*/ u8 _1CA[0x1E1 - 0x1CA];
    /*0x1E1*/ u8 _1E1;
    /*0x1E2*/ u8 _1E2[0x268 - 0x1E2];
} Fielder540; // size: 0x268

extern Fielder540 g_Fielders[9];

// g_Ball keeps 60 past positions: pastCoordinates[27] runs on into
// physicsSubstruct.startOfWallJumpChecksMaybe[33] (contiguous VecXYZ).
#define BALL_PAST(i) (g_Ball.pastCoordinates[i])

extern f32 lbl_3_data_450C[2]; // ball start x, z
extern f32 lbl_3_data_4428[];
extern f32 lbl_3_data_4930[];
// Common BSS blocks touched by fn_3_6C38 (only the bytes used here).
extern struct {
    u8 _00[0xCA];
    u8 _CA; // surface sound set
} lbl_3_common_bss_32724;
extern struct {
    u8 _00[0x6B];
    u8 _6B; // note block hit still animating
} lbl_3_common_bss_350E4;
extern struct {
    u8 _00[0x40];
    s16 _40; // team whose stats feed fn_3_161588
} lbl_3_common_bss_37400;
extern f32 lbl_3_data_610C[6]; // speed factor for collision codes 0x10-0x15
extern f32 lbl_3_data_6124[2]; // speed factor for collision codes 0x20-0x21
extern void fn_3_15F648(u8 surface, u8 soundSet, VecXYZ* vel);
extern void fn_3_161588(int arg, s16 rosterID);
extern void fn_3_16D5E4(int arg);
extern void fn_3_E7350(void);
extern void fn_80064344(Vec* pos, Vec* v);
extern void vecCrossProduct(VecXYZ* out, VecXYZ* a, VecXYZ* b);
extern struct {
    f32 _00; // Bob-omb Derby gravity
    f32 _04;
    f32 _08;
} lbl_3_data_21438;
extern void fn_3_15C000(void);
extern u32 fn_3_15C014(void);
extern int fn_3_51DF0(f32 x, f32 z); // infield zone of point (x, z)
extern f32 lbl_3_data_47BC[]; // garlic-hit catch radius, by fielder _1C9
extern int fn_3_253A4(int fielder, s16 angle);
extern f32 lbl_3_data_45FC; // default ball gravity
extern f32 lbl_3_data_45F4[2]; // ground y for bounces [normal, game mode 6]
extern u8 lbl_3_data_4600; // default air resistance // fielding tuning floats
extern int fn_3_B7D6C(f32, f32);
extern void fn_3_8FF5C(s32, void*, f32, f32, f32);
extern u8 lbl_800E8558[];
extern int getAnimRelatedCoordinates(int, int, void*);
typedef struct {
    f32 f0, f4, f8, fC, f10;
} Row4388;
extern Row4388 lbl_3_data_4388[];
extern Row4388 lbl_3_data_4414; // bounce factors for game mode 6 surfaces 0x70-0x78
extern int fn_3_B7E10(f32, f32);
extern void fn_3_8C5C8(void);
extern VecXZ lbl_3_data_4444[5]; // home, 1st, 2nd, 3rd, mound
extern f32 lbl_3_data_5CDC[3]; // ball energy: min, per-frame decay, bounce decay
extern f32 lbl_3_data_4604; // min bounce speed
extern u8 lbl_3_data_4608; // min bounce count before stopping
extern int fn_3_B7DD8(f32, f32);
extern f64 lbl_3_rodata_600;
extern void fn_3_88D88(s32);
extern void fn_3_27648(void);

// g_RunningLogic (0x20 bytes); only the fields used here.
typedef struct RunningLogic540 {
    /*0x00*/ s16 _00; // play-event flags
    /*0x02*/ u8 _02[0x13 - 0x2];
    /*0x13*/ u8 _13; // home run hit
    /*0x14*/ u8 _14[0x20 - 0x14];
} RunningLogic540;
extern RunningLogic540 g_RunningLogic;
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
// Same update without the prePitch copy.
static inline void ballSeedRandom(void) {
    s32 a;
    a = (((lbl_3_data_228.counter % 10) + 1) * (g_Ball.StaticRandomInt2 * g_Ball.StaticRandomInt1) + g_Ball.StaticRandomInt2 * 16 + (s32)(lbl_3_data_228.counter >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu) & 0x7FFF;
    g_Ball.StaticRandomInt1 = a;
    g_Ball.StaticRandomInt2 = (((lbl_3_data_228.counter % 10) + 1) * (g_Ball.StaticRandomInt2 * (g_Ball.StaticRandomInt2 + 1)) + a * 8 + (s32)(lbl_3_data_228.counter >> 1) + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1)) & 0x7FFF;
}

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

// Horizontal friction after a bounce (thrown ball / foul ball); same tables as fn_3_9508.
static inline void ballBounceFriction(void) {
    s32 surface = g_Ball.collisionCode & 0x7F;
    u8 rolling = g_Ball.ballIsRollingIndicator;
    if (g_Ball.knockoutProcessedFlag != 0) {
        g_Ball.physicsSubstruct.velocity.x = g_Ball.savedVelocity.x;
        g_Ball.physicsSubstruct.velocity.z = g_Ball.savedVelocity.z;
        g_Ball.knockoutProcessedFlag = 0;
    } else if (g_d_GameSettings.GameModeSelected == 6 && surface >= 0x70 && surface < 0x79) {
        if (rolling != 0) {
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.f10;
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.f10;
        } else {
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.fC;
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.fC;
        }
    } else if (rolling != 0) {
        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
    } else {
        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
    }
}

// Keep a slow ball moving at least 0.03 horizontally (away from home if stopped).
static inline void ballMinSpeed(void) {
    f32 speed = sqrt540(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                        g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
    if (speed < 0.03f) {
        if (speed == 0.0f) {
            g_Ball.physicsSubstruct.velocity.x = 0.03f * (g_Ball.AtBat_Contact_BallPos.x / g_Ball.ballDistanceFromHome);
            g_Ball.physicsSubstruct.velocity.z = 0.03f * (g_Ball.AtBat_Contact_BallPos.z / g_Ball.ballDistanceFromHome);
        } else {
            g_Ball.physicsSubstruct.velocity.x = 0.03f * (g_Ball.physicsSubstruct.velocity.x / speed);
            g_Ball.physicsSubstruct.velocity.z = 0.03f * (g_Ball.physicsSubstruct.velocity.z / speed);
        }
    }
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
                        if (g_RunningLogic._00 != 0) {
                            fn_3_59918(0x14, 0);
                        }
                    }
                } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
                    if (g_Ball.deadBallReason != 4) {
                        g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                        g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                        g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                        g_Ball.deadBallReason = 4;
                        if (g_RunningLogic._00 != 0) {
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
                if (g_RunningLogic._00 != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
            break;
        }
        if (g_Ball.matchFramesAndBallAngle.ballOverWallFrames == 0) {
            g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 1;
        }
    } else if (g_Ball.AtBat_ContactResult == 1 && g_Ball.ballInitialHitDoneInd == 0 && g_Ball.AtBat_Contact_BallPos.z > lbl_3_data_4444[1].z) {
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
// Ball collision with the ground, walls and stadium objects for this frame.
// NONMATCHING 90%: register allocation; dead-ball/strike helpers (fn_3_9E84/9FA4/A0F0) and the friction block are inlined in the original
#if NONMATCHING
void fn_3_6C38(void) {
    VecSrcDst ray;
    CollisionStruct hit;
    VecXYZ up;
    VecXYZ t1;
    VecXYZ t2;
    VecXYZ vel;
    BALL_COLLISION_TYPE type;
    u32 c;
    f32 rest;
    f32 nx;
    f32 k;
    f32 a, b, n;
    s32 i;
    g_Ball.ballOnMoundInd = 0;
    ray.src.x = g_Ball.AtBat_Contact_BallPos.x;
    ray.src.y = -g_Ball.AtBat_Contact_BallPos.y;
    ray.src.z = g_Ball.AtBat_Contact_BallPos.z;
    ray.dst.x = g_Ball.AtBat_Contact_BallPos.x;
    ray.dst.y = 10.0f;
    ray.dst.z = g_Ball.AtBat_Contact_BallPos.z;
    if (ray.src.y >= -0.1f) {
        ray.src.y = -0.1f;
    }
    // ground below the ball (game y is negated for the collision system)
    if (g_d_GameSettings.GameModeSelected == 6) {
        ray.src.y -= 1.0f;
        type = checkCollision(&ray, &hit, 1, FALSE);
    } else {
        type = checkCollision(&ray, &hit, 0, FALSE);
    }
    g_Ball.maybeCollisionRelated = g_Ball.collisionCode;
    g_Ball.physicsSubstruct.twoFrameLookback[1] = -hit.position.y;
    if (type != 0) {
        g_Ball.collisionCode = type;
    }
    if ((g_Ball.collisionCode & 0x7F) == 9) {
        fn_3_16D5E4(0);
    }
    if (g_Ball.ballState == BALL_STATE_THROWN && g_Ball.framesSinceThrowStarted < 20) {
        return;
    }
    if (g_Ball.hitNoteBlockInd != 0) {
        if (lbl_3_common_bss_350E4._6B != 0) {
            return;
        }
        g_Ball.hitNoteBlockInd = 0;
        g_FieldingLogic._13B = 1;
        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400._40 == g_GameLogic.teamBatting) {
            fn_3_161588(0, g_Batter.rosterID);
        }
    }
    // swept test from last frame's position to this one
    ray.src.x = g_Ball.pastCoordinates[0].x;
    ray.src.y = -(g_Ball.pastCoordinates[0].y - g_Ball.groundYForBounces);
    ray.src.z = g_Ball.pastCoordinates[0].z;
    ray.dst.x = g_Ball.AtBat_Contact_BallPos.x;
    ray.dst.y = -(g_Ball.AtBat_Contact_BallPos.y - g_Ball.groundYForBounces);
    ray.dst.z = g_Ball.AtBat_Contact_BallPos.z;
    if (g_d_GameSettings.GameModeSelected == 6) {
        type = checkCollision(&ray, &hit, 2, TRUE);
    } else {
        type = checkCollision(&ray, &hit, 1, TRUE);
    }
    if (type == 0) {
        fn_3_6694();
        return;
    }
    c = type & 0x7F;
    if (g_Ball.ballState == BALL_STATE_THROWN) {
        if ((c >= 0x10 && c <= 0x15) || c == 0x21 || c == 0x30 || c == 0x40 || c == 0x60 || c == 0x61) {
            return;
        }
    }
    if (g_Ball.someCollisionInd != 0) {
        if (c == 0x21 || c == 0x30 || c == 0x40 || c == 0x60 || c == 0x61) {
            return;
        }
    }
    if ((g_Ball.currentStarSwing2 == 0xB || g_Ball.currentStarSwing2 == 0xC) && g_Ball.AtBat_ContactResult == 0) {
        if ((c >= 0x10 && c <= 0x15) || c == 0x21 || c == 0x40) {
            return;
        }
    }
    if (g_Minigame.GameMode_MiniGame == 1 && g_Ball.bODQualifyingHitInd != 0) {
        return;
    }
    if (g_Ball.matchFramesAndBallAngle.framesOnGround < 0x7FFE) {
        g_Ball.matchFramesAndBallAngle.framesOnGround++;
    } else {
        g_Ball.matchFramesAndBallAngle.framesOnGround = 0x7FFF;
    }
    // fraction of this frame's movement left after the hit
    if (0.0f == ray.src.y - ray.dst.y) {
        rest = 1.0f;
    } else {
        rest = 1.0f - (ray.src.y - hit.position.y) / (ray.src.y - ray.dst.y);
    }
    k = 0.005f + g_Ball.groundYForBounces;
    nx = hit.normal.x;
    g_Ball.AtBat_Contact_BallPos.x = hit.normal.x * k + hit.position.x;
    g_Ball.AtBat_Contact_BallPos.y = -(hit.normal.y * k + hit.position.y);
    g_Ball.AtBat_Contact_BallPos.z = hit.normal.z * k + hit.position.z;
    vel.x = g_Ball.physicsSubstruct.velocity.x;
    vel.y = -g_Ball.physicsSubstruct.velocity.y;
    vel.z = g_Ball.physicsSubstruct.velocity.z;
    if (nx < 0.0f) {
        nx = -nx;
    }
    if (nx < 0.5f) {
        up.x = 1.0f;
        up.y = 0.0f;
        up.z = 0.0f;
    } else {
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
    }
    // reflect the velocity about the surface normal
    vecCrossProduct(&t1, &hit.normal, &up);
    vecCrossProduct(&t2, &hit.normal, &t1);
    a = vecDotProduct(&vel, &t1);
    b = vecDotProduct(&vel, &t2);
    n = -vecDotProduct(&vel, &hit.normal);
    g_Ball.physicsSubstruct.velocity.y = hit.normal.y * n + (t1.y * a + t2.y * b);
    g_Ball.physicsSubstruct.velocity.x = hit.normal.x * n + (t1.x * a + t2.x * b);
    g_Ball.physicsSubstruct.velocity.z = hit.normal.z * n + (t1.z * a + t2.z * b);
    g_Ball.physicsSubstruct.velocity.y *= -1.0f;
    if (c == 1 || c == 6 || c == 9 || c == 10 || c == 0x22 || c == 0x32) {
        // ground bounce
        if (g_Ball.ballIsRollingIndicator == 0) {
            fn_3_15F648(c, lbl_3_common_bss_32724._CA, &g_Ball.physicsSubstruct.velocity);
        } else if (c == 10) {
            fn_80064344(&g_Ball.AtBat_Contact_BallPos, &g_Ball.physicsSubstruct.velocity);
        }
        if (g_Ball.AtBat_ContactResult == 0) {
            fn_3_8CF0(&g_Ball.physicsSubstruct.velocity.y, 0, &g_Ball.ballIsRollingIndicator, 0);
        } else {
            fn_3_8CF0(&g_Ball.physicsSubstruct.velocity.y, g_Ball.framesOnGroundUntilPickedUp, &g_Ball.ballIsRollingIndicator, 0);
        }
        g_Ball.physicsSubstruct.acceleration.x *= 0.5f;
        g_Ball.physicsSubstruct.acceleration.z *= 0.5f;
        if (g_Ball.ballState == BALL_STATE_THROWN) {
            ballBounceFriction();
            g_Ball.thrownBallHasHitGround = 1;
        } else {
            switch (g_Ball.AtBat_ContactResult) {
            case 0:
                fn_3_9808();
                break;
            case 1:
                fn_3_9508();
                break;
            case -1:
                ballBounceFriction();
                break;
            default:
                ballBounceFriction();
                break;
            }
        }
        ray.src.x = g_Ball.AtBat_Contact_BallPos.x;
        ray.src.y = -(g_Ball.AtBat_Contact_BallPos.y - g_Ball.groundYForBounces);
        ray.src.z = g_Ball.AtBat_Contact_BallPos.z;
        ray.dst.x = g_Ball.physicsSubstruct.velocity.x * rest + g_Ball.AtBat_Contact_BallPos.x;
        ray.dst.y = -((g_Ball.physicsSubstruct.velocity.y * rest + g_Ball.AtBat_Contact_BallPos.y) - g_Ball.groundYForBounces);
        ray.dst.z = g_Ball.physicsSubstruct.velocity.z * rest + g_Ball.AtBat_Contact_BallPos.z;
        if (checkCollision(&ray, &hit, 1, FALSE) == 0) {
            g_Ball.AtBat_Contact_BallPos.x += g_Ball.physicsSubstruct.velocity.x * rest;
            g_Ball.AtBat_Contact_BallPos.y += g_Ball.physicsSubstruct.velocity.y * rest;
            g_Ball.AtBat_Contact_BallPos.z += g_Ball.physicsSubstruct.velocity.z * rest;
        }
        if (g_Ball.distLandingSpotToMound <= 3.0f) {
            g_Ball.ballOnMoundInd = 1;
        }
        if (g_Ball.framesOnGroundUntilPickedUp < 0xFE) {
            g_Ball.framesOnGroundUntilPickedUp++;
        } else {
            g_Ball.framesOnGroundUntilPickedUp = 0xFF;
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_3_E7350();
        }
    } else {
        // wall / object
        g_Ball.framesSinceBallHitWall = 1;
        g_Ball.AtBat_Contact_BallPos.y += g_Ball.groundYForBounces;
        g_Ball.physicsSubstruct.acceleration.x = 0.0f;
        g_Ball.physicsSubstruct.acceleration.y = 0.0f;
        g_Ball.physicsSubstruct.acceleration.z = 0.0f;
        if (c == 4) {
            fn_3_904C();
            g_Ball.currentStarSwing = 0;
        } else if (c == 2 || c == 5 || c == 0x20) {
            fn_3_9260(type);
            fn_3_27648();
            g_Ball.currentStarSwing = 0;
            if (g_d_GameSettings.GameModeSelected == 6) {
                fn_3_E7350();
            }
        } else if (c == 0xB) {
            fn_3_9260(type);
            fn_3_27648();
            g_Ball.currentStarSwing = 0;
        } else if ((c == 3 || c == 7 || c == 8 || c == 0x23) && g_Ball.AtBat_ContactResult == 0) {
            // foul pole / stands on a fresh hit
            if (g_Ball.bobbleLocation_1fair_2foul == 1) {
                if (g_d_GameSettings.GameModeSelected == 6 && (c == 7 || c == 8)) {
                    fn_3_A0F0();
                } else if (g_Ball.numberOfThrowsDuringPlay == 0 && g_Ball.numFieldersWhoHandledBallDuringPlay != 0 &&
                           g_Ball.framesOnGroundUntilPickedUp == 0) {
                    if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
                        fn_3_9E84();
                    } else {
                        fn_3_9FA4();
                    }
                } else {
                    fn_3_9E84();
                }
            } else if (!(type & BALL_COLLISION_TYPE_FOUL)) {
                fn_3_9FA4();
            } else {
                fn_3_A0F0();
            }
            g_Ball.currentStarSwing = 0;
            g_Ball.physicsSubstruct.velocity.x *= 0.3f;
            g_Ball.physicsSubstruct.velocity.y *= 0.3f;
            g_Ball.physicsSubstruct.velocity.z *= 0.3f;
        } else if ((c >= 0x10 && c <= 0x14) || c == 0x15) {
            if (c == 0x12 || c == 0x15) {
                g_Ball.hitNoteBlockInd = 1;
            } else {
                g_FieldingLogic._13B = 1;
            }
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_610C[c - 0x10];
            g_Ball.physicsSubstruct.velocity.y *= lbl_3_data_610C[c - 0x10];
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_610C[c - 0x10];
            ballMinSpeed();
            if (g_Ball.ballState == BALL_STATE_THROWN) {
                g_Ball.ballState = BALL_STATE_HELD;
            }
            fn_3_27648();
            g_Ball.someCollisionVariable = 0;
            g_Ball.someCollisionInd = 1;
        } else if (c == 0x20 || c == 0x21) {
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_6124[c - 0x20];
            g_Ball.physicsSubstruct.velocity.y *= lbl_3_data_6124[c - 0x20];
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_6124[c - 0x20];
            ballMinSpeed();
            g_Ball.someCollisionVariable = 0;
            if (g_Ball.ballState == BALL_STATE_THROWN) {
                g_Ball.ballState = BALL_STATE_HELD;
            }
            g_Ball.someCollisionInd = 1;
        } else if (c == 0x30 || c == 0x40 || c == 0x60 || c == 0x61) {
            g_Ball.physicsSubstruct.velocity.x *= 0.5f;
            g_Ball.physicsSubstruct.velocity.y *= 0.5f;
            g_Ball.physicsSubstruct.velocity.z *= 0.5f;
            ballMinSpeed();
            if (g_Ball.ballState == BALL_STATE_THROWN) {
                g_Ball.ballState = BALL_STATE_HELD;
            }
            fn_3_27648();
            g_Ball.someCollisionVariable = 0;
            g_Ball.someCollisionInd = 1;
        } else if (c >= 0x70 && c < 0x79) {
            // toy field (game mode 6) targets
            if (c == 0x70) {
                g_Ball.physicsSubstruct.velocity.x *= 0.3f;
                g_Ball.physicsSubstruct.velocity.y *= 0.3f;
                g_Ball.physicsSubstruct.velocity.z *= 0.3f;
            } else {
                if (g_Minigame.toyFieldStateInd_collisionRelated == 0) {
                    g_Minigame.toyFieldStateInd_collisionRelated = c;
                }
                g_Ball.physicsSubstruct.velocity.x *= 0.3f;
                g_Ball.physicsSubstruct.velocity.y *= 0.3f;
                g_Ball.physicsSubstruct.velocity.z *= 0.3f;
            }
        } else {
            if (g_Ball.ballState != BALL_STATE_HIT) {
                g_Ball.physicsSubstruct.velocity.x *= 0.05f;
                g_Ball.physicsSubstruct.velocity.y *= 0.05f;
                g_Ball.physicsSubstruct.velocity.z *= 0.05f;
            } else {
                g_Ball.physicsSubstruct.velocity.x *= 0.3f;
                g_Ball.physicsSubstruct.velocity.y *= 0.3f;
                g_Ball.physicsSubstruct.velocity.z *= 0.3f;
            }
            if (c == 7 || c == 8) {
                if (g_d_GameSettings.GameModeSelected == 6) {
                    fn_3_A0F0();
                } else if (g_Ball.AtBat_ContactResult == -1) {
                    fn_3_A0F0();
                } else if (g_Ball.AtBat_ContactResult > 0) {
                    fn_3_9E84();
                } else if (g_Ball.numberOfThrowsDuringPlay == 0) {
                    if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0) {
                        if (g_Ball.bobbleLocation_1fair_2foul == 2) {
                            fn_3_A0F0();
                        } else {
                            fn_3_9E84();
                        }
                    } else if (type & BALL_COLLISION_TYPE_FOUL) {
                        fn_3_A0F0();
                    } else {
                        fn_3_9E84();
                    }
                } else {
                    fn_3_9E84();
                }
            }
            g_Ball.collisionRelated++;
            if (g_Ball.deadBallReason == 3) {
                g_Ball.collisionRelated = 2;
            }
            g_Ball.currentStarSwing = 0;
            fn_3_27648();
        }
        if (g_d_GameSettings.StadiumID == 0 || (g_d_GameSettings.StadiumID >= 2 && g_d_GameSettings.StadiumID <= 4) ||
            g_d_GameSettings.StadiumID == 5) {
            if (g_Ball.AtBat_Contact_BallPos.y < 0.005f + g_Ball.groundYForBounces) {
                g_Ball.AtBat_Contact_BallPos.y = 0.005f + g_Ball.groundYForBounces;
                if (g_Ball.physicsSubstruct.velocity.y < 0.0f) {
                    g_Ball.physicsSubstruct.velocity.y *= -1.0f;
                }
            }
        }
        if (g_Ball.ballIsRollingIndicator != 0 && g_Ball.physicsSubstruct.velocity.y < 0.0f) {
            g_Ball.physicsSubstruct.velocity.y *= -1.0f;
        }
        g_Ball.ballBounceState = 3;
        g_Ball.hitWallInd = 1;
        if (g_Ball.framesOnGroundUntilPickedUp < 0xFE) {
            g_Ball.framesOnGroundUntilPickedUp++;
        } else {
            g_Ball.framesOnGroundUntilPickedUp = 0xFF;
        }
        if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
            for (i = 0; i < 9; i++) {
                g_Fielders[i]._1E1 = 0;
            }
        }
    }
    if (sqrt540(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z) < 0.0001f) {
        g_Ball.physicsSubstruct.velocity.x = 0.0f;
        g_Ball.physicsSubstruct.velocity.z = 0.0f;
    }
    g_Ball.framesSinceLastBounce = 0;
    if (g_Ball.currentStarSwing == 3 || g_Ball.currentStarSwing == 4) {
        g_Ball.currentStarSwing = 0;
    }
    g_Ball.warioWaluGarlicIsActive = 0;
}
#endif

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
            *p *= lbl_3_data_4414.f0;
        } else {
            *p *= lbl_3_data_4414.f4;
        }
    } else if (n == 0) {
        *p *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f0;
    } else {
        *p *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f4;
    }
    if (*flag == 0 && *p < lbl_3_data_4604 && n >= lbl_3_data_4608) {
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
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.f10;
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.f10;
        } else {
            g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.fC;
            g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.fC;
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
        g_Ball.physicsSubstruct.velocity.x *= lbl_3_data_4414.f8;
        g_Ball.physicsSubstruct.velocity.z *= lbl_3_data_4414.f8;
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
        if (g_RunningLogic._00 != 0) {
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
                if (g_RunningLogic._00 != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0 && g_Ball.numberOfThrowsDuringPlay != 0) {
            if (st != 4) {
                g_Ball.deadballLastLoc.x = g_Ball.AtBat_Contact_BallPos.x;
                g_Ball.deadballLastLoc.y = g_Ball.AtBat_Contact_BallPos.y;
                g_Ball.deadballLastLoc.z = g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.deadBallReason = 4;
                if (g_RunningLogic._00 != 0) {
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
// Garlic (Wario/Waluigi star) hit: split into two balls and fly them until one lands near a fielder.
// NONMATCHING 86%: original reloads the split-ball vectors after every store; float regalloc
#if NONMATCHING
void fn_3_A198(void) {
    s32 i;
    f32 angle;
    f32 speed;
    f32 ax, az, bx, bz;
    f32 drag;
    f32 best;
    f32 d;
    f32 dx;
    f32 dz;
    s32 nearest;
    Fielder540* f;
    if (g_Ball.framesUntilBallHitsGround > g_Ball.matchFramesAndBallAngle.garlicHitFramesUntilHitGroundForSplit) {
        return;
    }
    if (g_Ball.framesUntilBallHitsGround == g_Ball.matchFramesAndBallAngle.garlicHitFramesUntilHitGroundForSplit) {
        for (i = 9; i >= 0; i--) {
            g_Ball.warioStarHitCoords[i + 3].x = BALL_PAST(i).x;
            g_Ball.warioStarHitCoords[i + 3].y = BALL_PAST(i).y;
            g_Ball.warioStarHitCoords[i + 3].z = BALL_PAST(i).z;
        }
        g_Ball.physicsSubstruct.acceleration.x = 0.0f;
        g_Ball.physicsSubstruct.acceleration.y = 0.0f;
        g_Ball.physicsSubstruct.acceleration.z = 0.0f;
        g_Ball.warioStarHitCoords[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[0].z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.warioStarHitCoords[1].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[1].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[1].z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.warioStarHitCoords[2].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[2].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[2].z = g_Ball.AtBat_Contact_BallPos.z;
        angle = game_atan2(g_Ball.physicsSubstruct.velocity.x, g_Ball.physicsSubstruct.velocity.z);
        speed = sqrt540(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x + g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
        getComponentsFromRad(angle + RandomF32_Game_Range(g_hitFloats.garlicSpreadLower, g_hitFloats.garlicSpreadUpper), &ax, &az);
        getComponentsFromRad(angle - RandomF32_Game_Range(g_hitFloats.garlicSpreadLower, g_hitFloats.garlicSpreadUpper), &bx, &bz);
        ax *= speed;
        az *= speed;
        bx *= speed;
        bz *= speed;
        if (g_Ball.warioWaluStarHitDirection != 0) {
            g_Ball.warioStarHitCoords[13].x = ax;
            g_Ball.warioStarHitCoords[13].y = g_Ball.physicsSubstruct.velocity.y;
            g_Ball.warioStarHitCoords[13].z = az;
            g_Ball.warioStarHitCoords[14].x = bx;
            g_Ball.warioStarHitCoords[14].y = g_Ball.physicsSubstruct.velocity.y;
            g_Ball.warioStarHitCoords[14].z = bz;
        } else {
            g_Ball.warioStarHitCoords[13].x = bx;
            g_Ball.warioStarHitCoords[13].y = g_Ball.physicsSubstruct.velocity.y;
            g_Ball.warioStarHitCoords[13].z = bz;
            g_Ball.warioStarHitCoords[14].x = ax;
            g_Ball.warioStarHitCoords[14].y = g_Ball.physicsSubstruct.velocity.y;
            g_Ball.warioStarHitCoords[14].z = az;
        }
        g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit = 0;
    } else {
        g_Ball.warioStarHitCoords[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[0].z = g_Ball.AtBat_Contact_BallPos.z;
        if (g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit == 3) {
            g_AiLogic._79[0] = RandomInt_Game(2);
            g_FieldingLogic._13B = 1;
        }
        drag = 1.0f - (f32)g_Ball.airResistance / 10000.0f;
        // [13]/[14] are the two split balls' velocities, [1]/[2] their positions
        g_Ball.warioStarHitCoords[13].y -= g_Ball.physicsSubstruct.gravity;
        g_Ball.warioStarHitCoords[13].x *= drag;
        g_Ball.warioStarHitCoords[13].y *= drag;
        g_Ball.warioStarHitCoords[13].z *= drag;
        g_Ball.warioStarHitCoords[1].x += g_Ball.warioStarHitCoords[13].x;
        g_Ball.warioStarHitCoords[1].y += g_Ball.warioStarHitCoords[13].y;
        g_Ball.warioStarHitCoords[1].z += g_Ball.warioStarHitCoords[13].z;
        g_Ball.warioStarHitCoords[14].y -= g_Ball.physicsSubstruct.gravity;
        g_Ball.warioStarHitCoords[14].x *= drag;
        g_Ball.warioStarHitCoords[14].y *= drag;
        g_Ball.warioStarHitCoords[14].z *= drag;
        g_Ball.warioStarHitCoords[2].x += g_Ball.warioStarHitCoords[14].x;
        g_Ball.warioStarHitCoords[2].y += g_Ball.warioStarHitCoords[14].y;
        g_Ball.warioStarHitCoords[2].z += g_Ball.warioStarHitCoords[14].z;
        g_Ball.AtBat_Contact_BallPos.x = g_Ball.warioStarHitCoords[1].x;
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.warioStarHitCoords[1].y;
        g_Ball.AtBat_Contact_BallPos.z = g_Ball.warioStarHitCoords[1].z;
        if (g_Ball.warioStarHitCoords[1].y < 2.0f && g_Ball.framesUntilBallHitsGround < 30) {
            best = 999.9f;
            nearest = -1;
            f = g_Fielders;
            for (i = 0; i < 9; i++) {
                dx = g_Ball.warioStarHitCoords[2].x - f->pos.x;
                dz = g_Ball.warioStarHitCoords[2].z - f->pos.z;
                d = sqrt540(dx * dx + dz * dz);
                if (d < best) {
                    nearest = i;
                    best = d;
                }
                f++;
            }
            if (best < lbl_3_data_47BC[g_Fielders[nearest]._1C9]) {
                fn_3_253A4(nearest, fn_3_9FB8C(g_Fielders[nearest].pos.x - g_Ball.warioStarHitCoords[2].x, g_Fielders[nearest].pos.z - g_Ball.warioStarHitCoords[2].z));
                g_Ball.currentStarSwing = 0;
                g_Ball.warioWaluGarlicIsActive = 0;
                return;
            }
        }
    }
    if (g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit < 0x7FFE) {
        g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit++;
    } else {
        g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit = 0x7FFF;
    }
    if (g_Ball.warioWaluGarlicIsActive == 0) {
        playSoundEffect(0x1B3);
    }
    g_Ball.warioWaluGarlicIsActive = 1;
}
#endif

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
// Per-frame ball update while in play: counters, history, physics step, star-hit effects.
// NONMATCHING 95%: original indexes g_hitShorts by star-swing id; branch layout of the early returns
#if NONMATCHING
void fn_3_A970(s32 arg) {
    f32 drag;
    f32 speed;
    f32 ang;
    s32 handled;
    int i;
    VecXYZ* p;
    if (arg != 1) {
        if (g_Ball.framesSinceHit < 0x7FFE) {
            g_Ball.framesSinceHit++;
        } else {
            g_Ball.framesSinceHit = 0x7FFF;
        }
        if (g_Ball.AtBat_ContactResult != 0) {
            if (g_Ball.framesSinceBallHitGroundOrWasCaught == -1) {
                g_Ball.framesSinceBallHitGroundOrWasCaught = 1;
            } else if (g_Ball.framesSinceBallHitGroundOrWasCaught < 0x7FFE) {
                g_Ball.framesSinceBallHitGroundOrWasCaught++;
            } else {
                g_Ball.framesSinceBallHitGroundOrWasCaught = 0x7FFF;
            }
        }
        if (g_Ball.framesSinceLastBounce >= 0) {
            if (g_Ball.framesSinceLastBounce < 0x7FFE) {
                g_Ball.framesSinceLastBounce++;
            } else {
                g_Ball.framesSinceLastBounce = 0x7FFF;
            }
        }
        if (g_Ball.ballBounceState != 0) {
            g_Ball.ballBounceState--;
        }
        if (g_Ball.ballState == BALL_STATE_THROWN) {
            if (g_Ball.framesSinceThrowStarted < 0x7FFE) {
                g_Ball.framesSinceThrowStarted++;
            } else {
                g_Ball.framesSinceThrowStarted = 0x7FFF;
            }
            if (g_Ball.framesSinceThrowStarted == 2) {
                fn_3_B440();
            } else {
                g_Ball.framesUntilThrowReachesDest--;
                if (g_Ball.framesUntilThrowReachesDest < -1) {
                    g_Ball.framesUntilThrowReachesDest = -1;
                }
            }
        }
    }
    // same as fn_3_A83C
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
    if (g_Ball.pauseBallMovementWhenInPlant != 0) {
        if (g_Ball.matchFramesAndBallAngle.framesInsidePlant < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.framesInsidePlant++;
        } else {
            g_Ball.matchFramesAndBallAngle.framesInsidePlant = 0x7FFF;
        }
        return;
    }
    if (g_Ball.catchAnimationTotalFrames != 0) {
        return;
    }
    if (g_Ball.warioWaluGarlicIsActive != 0) {
        g_Ball.AtBat_Contact_BallPos.x = g_Ball.warioStarHitCoords[0].x;
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.warioStarHitCoords[0].y;
        g_Ball.AtBat_Contact_BallPos.z = g_Ball.warioStarHitCoords[0].z;
    }
    if (g_Minigame.GameMode_MiniGame == 1 && g_Ball.bODQualifyingHitInd != 0) {
        g_Ball.physicsSubstruct.velocity.y -= lbl_3_data_21438._00;
    } else {
        drag = 1.0f - (f32)g_Ball.airResistance / 10000.0f;
        g_Ball.physicsSubstruct.velocity.y -= g_Ball.physicsSubstruct.gravity;
        g_Ball.physicsSubstruct.velocity.x *= drag;
        g_Ball.physicsSubstruct.velocity.y *= drag;
        g_Ball.physicsSubstruct.velocity.z *= drag;
    }
    g_Ball.physicsSubstruct.velocity.x += g_Ball.physicsSubstruct.acceleration.x;
    g_Ball.physicsSubstruct.velocity.y += g_Ball.physicsSubstruct.acceleration.y;
    g_Ball.physicsSubstruct.velocity.z += g_Ball.physicsSubstruct.acceleration.z;
    // banana (DK/Diddy star) hit curves for a window of frames
    if ((g_Ball.currentStarSwing == 5 || g_Ball.currentStarSwing == 6) &&
        g_Ball.framesSinceHit > g_Ball.matchFramesAndBallAngle.bananaHitStartFrame &&
        g_Ball.framesSinceHit < g_Ball.matchFramesAndBallAngle.bananaHitEndFrame) {
        speed = sqrt540(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                        g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z);
        ang = game_atan2(g_Ball.physicsSubstruct.velocity.x, g_Ball.physicsSubstruct.velocity.z);
        if (g_Ball.directionOfBananaHit != 0) {
            ang += g_hitFloats.DKStarAngleDelta;
        } else {
            ang -= g_hitFloats.DKStarAngleDelta;
        }
        getComponentsFromRad(ang, &g_Ball.physicsSubstruct.velocity.x, &g_Ball.physicsSubstruct.velocity.z);
        g_Ball.physicsSubstruct.velocity.x *= speed;
        g_Ball.physicsSubstruct.velocity.z *= speed;
    }
    g_Ball.AtBat_Contact_BallPos.x += g_Ball.physicsSubstruct.velocity.x;
    g_Ball.AtBat_Contact_BallPos.y += g_Ball.physicsSubstruct.velocity.y;
    g_Ball.AtBat_Contact_BallPos.z += g_Ball.physicsSubstruct.velocity.z;
    if (g_Ball.currentStarSwing == 3 || g_Ball.currentStarSwing == 4) {
        fn_3_A198();
    }
    fn_3_6C38();
    if ((g_d_GameSettings.StadiumID == 0 || (g_d_GameSettings.StadiumID >= 2 && g_d_GameSettings.StadiumID <= 4) ||
         g_d_GameSettings.StadiumID == 5) &&
        g_Ball.AtBat_Contact_BallPos.y < g_Ball.groundYForBounces) {
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.groundYForBounces;
        if (g_Ball.physicsSubstruct.velocity.y < 0.0f) {
            g_Ball.physicsSubstruct.velocity.y *= -1.0f;
        }
    }
    g_Ball.ballDistanceFromHome = sqrt540(g_Ball.AtBat_Contact_BallPos.x * g_Ball.AtBat_Contact_BallPos.x +
                                          g_Ball.AtBat_Contact_BallPos.z * g_Ball.AtBat_Contact_BallPos.z);
    if (g_Minigame.GameMode_MiniGame == 1) {
        return;
    }
    estimateAndSetFutureCoords(1);
    if (g_Ball.currentStarSwing == 0) {
        return;
    }
    handled = 0;
    if (g_Ball.someCollisionInd != 0) {
        handled = 1;
    } else if (g_Ball.numFieldersWhoHandledBallDuringPlay != 0) {
        handled = 1;
    }
    if (g_Ball.currentStarSwing == 0xB || g_Ball.currentStarSwing == 0xC) {
        // Peach / Daisy star hit: ball turns invisible for a while
        if (handled || g_Ball.AtBat_ContactResult != 0) {
            g_Ball.currentStarSwing = 0;
            g_Batter.invisibleBallForPeachStarHit = 0;
            if (fn_3_15C014() != 0) {
                fn_3_15C000();
            }
        } else if (g_Ball.currentStarSwing == 0xC) {
            if (g_Ball.framesSinceHit >= (s32)fn_3_15C014()) {
                g_Ball.currentStarSwing = 0;
                g_Batter.invisibleBallForPeachStarHit = 0;
            } else if (g_Ball.framesSinceHit >= g_hitShorts.FrameWhenDaisyHitAppearsAgain) {
                g_Batter.invisibleBallForPeachStarHit = 1;
            }
        } else {
            if (g_Ball.framesSinceHit >= g_hitShorts._16) {
                g_Ball.currentStarSwing = 0;
                g_Batter.invisibleBallForPeachStarHit = 0;
            } else if (g_Ball.framesSinceHit >= g_hitShorts.FrameWhenPeachHitAppearsAgain) {
                g_Batter.invisibleBallForPeachStarHit = 1;
            }
        }
        if (g_Batter.invisibleBallForPeachStarHit == 0) {
            g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
        }
    } else if (handled) {
        g_Ball.currentStarSwing = 0;
    } else if (g_Ball.ballIsRollingIndicator != 0) {
        g_Ball.currentStarSwing = 0;
    } else if (g_Ball.framesSinceLastBounce == 0) {
        switch (g_Ball.currentStarSwing) {
        case 5:
        case 6:
            g_Ball.currentStarSwing = 0;
            break;
        case 7:
        case 8:
            g_Ball.currentStarSwing = 0;
            break;
        case 9:
        case 10:
            if (g_Ball.framesOnGroundUntilPickedUp >= g_hitShorts.NEggBounces) {
                g_Ball.currentStarSwing = 0;
            }
            break;
        default:
            if (g_Ball.framesOnGroundUntilPickedUp >= g_hitShorts.framesOnGroundBeforeCheckingMinStarVelo) {
                if (sqrt540(g_Ball.physicsSubstruct.velocity.x * g_Ball.physicsSubstruct.velocity.x +
                            g_Ball.physicsSubstruct.velocity.z * g_Ball.physicsSubstruct.velocity.z) < g_hitFloats.minStarHitVelo) {
                    g_Ball.currentStarSwing = 0;
                }
            }
            break;
        }
    }
}
#endif

// .text:0x0000B440 size:0x500 mapped:0x8064A4D4
// Find the first future frame the throw passes its target (coarse then fine search).
void fn_3_B440(void) {
    s32 i;
    f32 dx;
    f32 dz;
    g_Ball.throwTimeEstimatesCompleteInd = 1;
    if (g_Ball.framesUntilThrowReachesDest < 15) {
        return;
    }
    dx = ABS(g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x);
    dz = ABS(g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z);
    if (dx > dz) {
        if (g_Ball.throwTarget.x < g_Ball.AtBat_Contact_BallPos.x) {
            for (i = 10; i < 360; i += 10) {
                if (g_Ball.throwTarget.x >= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x) {
                    i -= 10;
                    break;
                }
            }
            for (; i < 360; i++) {
                if (g_Ball.throwTarget.x >= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x) {
                    break;
                }
            }
        } else {
            for (i = 10; i < 360; i += 10) {
                if (g_Ball.throwTarget.x <= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x) {
                    i -= 10;
                    break;
                }
            }
            for (; i < 360; i++) {
                if (g_Ball.throwTarget.x <= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x) {
                    break;
                }
            }
        }
    } else if (g_Ball.throwTarget.z < g_Ball.AtBat_Contact_BallPos.z) {
        for (i = 10; i < 360; i += 10) {
            if (g_Ball.throwTarget.z >= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z) {
                i -= 10;
                break;
            }
        }
        for (; i < 360; i++) {
            if (g_Ball.throwTarget.z >= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z) {
                break;
            }
        }
    } else {
        for (i = 10; i < 360; i += 10) {
            if (g_Ball.throwTarget.z <= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z) {
                i -= 10;
                break;
            }
        }
        for (; i < 360; i++) {
            if (g_Ball.throwTarget.z <= g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z) {
                break;
            }
        }
    }
    g_Ball.framesUntilThrowReachesDest = i;
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
// Classify a fresh hit (ground ball / fly / line drive / home run) for AI and commentary.
// NONMATCHING 97%: zone (fn_3_51DF0 result) is narrowed at the call, original narrows at each use; star-swing 9/10 range test
#if NONMATCHING
void fn_3_C034(void) {
    u8 foulSide = 0;
    u8 zone;
    s16 ang;
    f32 d;
    f32 wallAdj;
    s32 i;
    g_Ball.hitClassification1 = 1;
    if (g_Ball.Hit_HorizontalAngle < 0x1B0 || g_Ball.Hit_HorizontalAngle > 0x650 ||
        (g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00)) {
        if (g_Ball.Hit_VerticalAngle > 0x800 || g_Ball.Hit_VerticalAngle < 0) {
            g_Ball.hitClassification1 = 3;
        } else if (g_Ball.Hit_VerticalAngle > 0x154) {
            g_Ball.hitClassification1 = 5;
        } else {
            g_Ball.hitClassification1 = 4;
        }
    } else if (g_Ball.Hit_VerticalAngle > 0x800 || g_Ball.Hit_VerticalAngle < 0) {
        g_Ball.hitClassification1 = 0;
    } else if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 18.0f && g_Ball.Hit_VerticalAngle < 100) {
        g_Ball.hitClassification1 = 0;
    } else if (g_Ball.Hit_VerticalAngle > 0x154) {
        g_Ball.hitClassification1 = 2;
    }
    zone = fn_3_51DF0(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    ang = fn_3_9FB8C(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    if (ang < 0x1A0 || ang > 0x660) {
        foulSide = 1;
    }
    if ((g_Ball.Hit_HorizontalAngle < 0x1A0 || g_Ball.Hit_HorizontalAngle > 0x660) && foulSide) {
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 60.0f) {
            g_Ball.hitClassification2 = 8;
        } else {
            g_Ball.hitClassification2 = 7;
        }
    } else if (g_Ball.Hit_VerticalAngle > 0x400 && g_Ball.Hit_VerticalAngle < 0xC00) {
        g_Ball.hitClassification2 = 7;
    } else if (g_Ball.hitClassification1 == 0) {
        d = sqrt540(g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x +
                    g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z);
        if (g_Ball.Hit_HorizontalPower < 70 && d < 14.0f) {
            g_Ball.hitClassification2 = 1;
        } else {
            g_Ball.hitClassification2 = 2;
        }
    } else {
        if (zone <= 1) {
            d = sqrt540(g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x +
                        g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z);
            if (g_Ball.Hit_HorizontalPower < 70 && d < 10.0f && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 18.0f) {
                g_Ball.hitClassification2 = 1;
                goto classified;
            }
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 30.0f && g_Ball.maxYOfHit < 2.0f) {
            g_Ball.hitClassification2 = 2;
        } else if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 20.0f && g_Ball.maxYOfHit < 4.0f) {
            g_Ball.hitClassification2 = 2;
        } else if (zone <= 1 && g_Ball.hangtimeOfHit > 180) {
            g_Ball.hitClassification2 = 4;
        } else if (zone <= 1) {
            g_Ball.hitClassification2 = 3;
        } else if (zone == 2 && g_Ball.maxYOfHit < 4.5f) {
            g_Ball.hitClassification2 = 3;
        } else if (zone <= 2) {
            g_Ball.hitClassification2 = 5;
        } else if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 70.0f ||
                   (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome < 80.0f && g_Ball.hangtimeOfHit < 180)) {
            g_Ball.hitClassification2 = 5;
        } else {
            g_Ball.hitClassification2 = 6;
        }
    }
classified:
    fn_3_BD78();
    g_Batter.hitTrajectory = 2;
    if (g_Ball.maybeBuntInd != 0) {
        g_Batter.hitTrajectory = 5;
    }
    wallAdj = 0.04f * (f32)__abs(0x400 - g_Ball.Hit_HorizontalAngle);
    g_RunningLogic._13 = 0;
    if (g_Ball.Hit_HorizontalAngle >= 0x260 && g_Ball.Hit_HorizontalAngle < 0x5A0 && g_d_GameSettings.GameModeSelected != 2) {
        if (135.0f - wallAdj < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
            if (g_Ball.Hit_VerticalAngle >= 0x118) {
                g_Ball.homeRunClassification = 2;
                if (145.0f - wallAdj < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                    g_Ball.homeRunClassification = 1;
                }
                g_Batter.hitTrajectory = 4;
                g_RunningLogic._13 = 1;
                if (g_Batter.batterHand == 0) {
                    if (g_Ball.Hit_HorizontalAngle < 0x480) {
                        g_Batter.hitTrajectory = 4;
                    }
                } else if (g_Ball.Hit_HorizontalAngle >= 0x380) {
                    g_Batter.hitTrajectory = 4;
                }
            }
        } else if (125.0f - wallAdj < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome && g_Ball.Hit_VerticalAngle >= 0x154) {
            g_Ball.homeRunClassification = 3;
        }
    }
    ang = fn_3_9FB8C(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    if ((g_Ball.Hit_HorizontalAngle < 0x1E0 || g_Ball.Hit_HorizontalAngle >= 0x620 ||
         (ang < 0x100 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 10.0f) ||
         (ang > 0x700 && g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 10.0f)) &&
        (g_d_GameSettings.StadiumID != 2 || g_Ball.Hit_HorizontalAngle <= 0x13C || g_Ball.Hit_HorizontalAngle > 0x6C4) &&
        g_Ball.currentStarSwing != 5 && g_Ball.currentStarSwing != 6 && g_Ball.currentStarSwing != 9 && g_Ball.currentStarSwing != 10 &&
        (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f ||
         g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < -g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f)) {
        if (g_Ball.maybeBuntInd != 0) {
            if (g_Ball.Hit_HorizontalAngle < 0x1A0 || g_Ball.Hit_HorizontalAngle >= 0x660) {
                g_Batter.hitTrajectory = 6;
            }
        } else if (ang < 0x1A0 || ang > 0xD80) {
            if (g_Ball.maxYOfHit > 15.0f && ang > 0xD80 && ang < 0xF80) {
                g_Batter.hitTrajectory = 3;
            } else {
                g_Batter.hitTrajectory = 3;
            }
        } else if (ang > 0x660 && ang < 0xA80) {
            if (g_Ball.maxYOfHit > 15.0f && ang > 0x880) {
                g_Batter.hitTrajectory = 3;
            } else {
                g_Batter.hitTrajectory = 3;
            }
        } else if (ang >= 0xA80 && ang <= 0xD80) {
            g_Batter.hitTrajectory = 3;
        }
    }
    // low liner over the mound: did it pass under the pitcher's reach?
    if (g_Ball.physicsSubstruct.futureCoordsAndDist[50].dist > 16.5f && g_Ball.Hit_HorizontalAngle <= 0x430 &&
        g_Ball.Hit_HorizontalAngle >= 0x3D0 && g_Ball.maxYOfHit < 10.0f) {
        for (i = 10; i < 100; i += 5) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > 16.0f) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.y < 0.2f + g_Fielders[0]._F4) {
                    g_Ball.lineDriveThroughPitcherInd = 1;
                }
                break;
            }
        }
    }
}
#endif

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
// Simulate the ball's flight (with bounces) and record 360 future positions.
// mode 0: live ball, 1: after a bounce, 2: fresh hit (also classifies it).
// NONMATCHING 93.6%: regalloc; flag tests (u8 vs int) and fmadds contraction differ
#if NONMATCHING
void estimateAndSetFutureCoords(int mode) {
    s32 frame = 1;
    u8 bounces = 0;
    s32 pastApex = 0;
    s32 landed = 0;
    u8 stopped = 0;
    u8 secondBall = 0;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 ax, ay, az;
    f32 drag;
    f32 px, py, pz;
    f32 t, rest, bounceVy;
    s32 surface;
    s32 i;
    CoordAndDist* fc;
    do {
        if (mode == 1) {
            bounces = g_Ball.framesOnGroundUntilPickedUp;
        }
        if (mode == 2) {
            x = g_Pitcher._30.x;
            y = g_Pitcher._30.y;
            z = g_Pitcher._30.z;
        } else if (g_Ball.warioWaluGarlicIsActive != 0) {
            if (secondBall) {
                x = g_Ball.warioStarHitCoords[2].x;
                y = g_Ball.warioStarHitCoords[2].y;
                z = g_Ball.warioStarHitCoords[2].z;
            } else {
                x = g_Ball.warioStarHitCoords[1].x;
                y = g_Ball.warioStarHitCoords[1].y;
                z = g_Ball.warioStarHitCoords[1].z;
            }
        } else {
            x = g_Ball.AtBat_Contact_BallPos.x;
            y = g_Ball.AtBat_Contact_BallPos.y;
            z = g_Ball.AtBat_Contact_BallPos.z;
        }
        if (g_Ball.warioWaluGarlicIsActive != 0) {
            if (secondBall) {
                vx = g_Ball.warioStarHitCoords[14].x;
                vy = g_Ball.warioStarHitCoords[14].y;
                vz = g_Ball.warioStarHitCoords[14].z;
            } else {
                vx = g_Ball.warioStarHitCoords[13].x;
                vy = g_Ball.warioStarHitCoords[13].y;
                vz = g_Ball.warioStarHitCoords[13].z;
            }
        } else {
            vx = g_Ball.physicsSubstruct.velocity.x;
            vy = g_Ball.physicsSubstruct.velocity.y;
            vz = g_Ball.physicsSubstruct.velocity.z;
        }
        ax = g_Ball.physicsSubstruct.acceleration.x;
        ay = g_Ball.physicsSubstruct.acceleration.y;
        az = g_Ball.physicsSubstruct.acceleration.z;
        drag = 1.0f - (f32)g_Ball.airResistance / 10000.0f;
        if (!secondBall) {
            g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.x = x;
            g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.y = y;
            g_Ball.physicsSubstruct.futureCoordsAndDist[0].pos.z = z;
            // note: stored at [frame] (1), not [0]; overwritten below
            g_Ball.physicsSubstruct.futureCoordsAndDist[frame].dist = sqrt540(x * x + z * z);
            if (0.0f == g_Ball.physicsSubstruct.velocity.x && 0.0f == g_Ball.physicsSubstruct.velocity.y &&
                0.0f == g_Ball.physicsSubstruct.velocity.z) {
                stopped = 1;
            }
            if (g_Ball.AtBat_ContactResult != 0) {
                landed = 1;
            }
        }
        fc = &g_Ball.physicsSubstruct.futureCoordsAndDist[frame];
        for (;;) {
            px = x;
            py = y;
            pz = z;
            vy -= g_Ball.physicsSubstruct.gravity;
            if (!pastApex && !landed && vy < 0.0f) {
                if (g_Ball.maxYOfHit < y) {
                    g_Ball.maxYOfHit = y;
                }
                pastApex = 1;
            }
            vy = vy * drag + ay;
            vx = vx * drag + ax;
            vz = vz * drag + az;
            y += vy;
            x += vx;
            z += vz;
            if (y < g_Ball.groundYForBounces) {
                t = (py - g_Ball.groundYForBounces) / (py - y);
                x = t * (x - px) + px;
                rest = 1.0f - t;
                z = t * (z - pz) + pz;
                bounceVy = -vy;
                if (secondBall) {
                    g_Ball.peachDaisyStarHitFielderLoc.x = x;
                    g_Ball.peachDaisyStarHitFielderLoc.z = z;
                    return;
                }
                if (!landed) {
                    // first landing
                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x = x;
                    g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z = z;
                    g_Ball.landingSpotAngle = fn_3_9FB8C(x, z);
                    if (mode == 0) {
                        g_Ball.landingSpotLocation.x = x;
                        g_Ball.landingSpotLocation.z = z;
                    } else if (mode == 1 && g_Ball.AtBat_ContactResult == 0) {
                        g_Ball.landingSpotLocation.x = x;
                        g_Ball.landingSpotLocation.z = z;
                    }
                    if (g_Ball.AtBat_ContactResult == 0) {
                        g_Ball.hangtimeOfHit = frame + g_Ball.framesSinceHit;
                    }
                    landed = 1;
                    g_Ball.framesUntilBallHitsGround = frame;
                    if (g_Ball.AtBat_ContactResult == 0) {
                        surface = g_Ball.collisionCode & 0x7F;
                        vx *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f8;
                        vz *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f8;
                        if (g_d_GameSettings.GameModeSelected == 6 && surface >= 0x70 && surface < 0x79) {
                            vy = bounceVy * lbl_3_data_4414.f0;
                        } else {
                            vy = bounceVy * lbl_3_data_4388[g_d_GameSettings.StadiumID].f0;
                        }
                        if (!stopped && vy < lbl_3_data_4604 && 0 >= lbl_3_data_4608) {
                            stopped = 1;
                        }
                        if (stopped) {
                            vy = 0.0f;
                        }
                    } else {
                        surface = g_Ball.collisionCode & 0x7F;
                        if (g_d_GameSettings.GameModeSelected == 6 && surface >= 0x70 && surface < 0x79) {
                            if (bounces == 0) {
                                vy = bounceVy * lbl_3_data_4414.f0;
                            } else {
                                vy = bounceVy * lbl_3_data_4414.f4;
                            }
                        } else if (bounces == 0) {
                            vy = bounceVy * lbl_3_data_4388[g_d_GameSettings.StadiumID].f0;
                        } else {
                            vy = bounceVy * lbl_3_data_4388[g_d_GameSettings.StadiumID].f4;
                        }
                        if (!stopped && vy < lbl_3_data_4604 && bounces >= lbl_3_data_4608) {
                            stopped = 1;
                        }
                        if (stopped) {
                            vy = 0.0f;
                        }
                        if (g_d_GameSettings.GameModeSelected == 6 && surface >= 0x70 && surface < 0x79) {
                            if (stopped) {
                                vx *= lbl_3_data_4414.f10;
                                vz *= lbl_3_data_4414.f10;
                            } else {
                                vx *= lbl_3_data_4414.fC;
                                vz *= lbl_3_data_4414.fC;
                            }
                        } else if (stopped) {
                            vx *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
                            vz *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
                        } else {
                            vx *= lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
                            vz *= lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
                        }
                    }
                } else {
                    // later bounces (same as fn_3_8CF0 / fn_3_9508)
                    surface = g_Ball.collisionCode & 0x7F;
                    if (g_d_GameSettings.GameModeSelected == 6 && surface >= 0x70 && surface < 0x79) {
                        if (bounces == 0) {
                            vy = bounceVy * lbl_3_data_4414.f0;
                        } else {
                            vy = bounceVy * lbl_3_data_4414.f4;
                        }
                    } else if (bounces == 0) {
                        vy = bounceVy * lbl_3_data_4388[g_d_GameSettings.StadiumID].f0;
                    } else {
                        vy = bounceVy * lbl_3_data_4388[g_d_GameSettings.StadiumID].f4;
                    }
                    if (!stopped && vy < lbl_3_data_4604 && bounces >= lbl_3_data_4608) {
                        stopped = 1;
                    }
                    if (stopped) {
                        vy = 0.0f;
                    }
                    if (g_d_GameSettings.GameModeSelected == 6 && surface >= 0x70 && surface < 0x79) {
                        if (stopped) {
                            vx *= lbl_3_data_4414.f10;
                            vz *= lbl_3_data_4414.f10;
                        } else {
                            vx *= lbl_3_data_4414.fC;
                            vz *= lbl_3_data_4414.fC;
                        }
                    } else if (stopped) {
                        vx *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
                        vz *= lbl_3_data_4388[g_d_GameSettings.StadiumID].f10;
                    } else {
                        vx *= lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
                        vz *= lbl_3_data_4388[g_d_GameSettings.StadiumID].fC;
                    }
                }
                x = vx * rest + x;
                z = vz * rest + z;
                bounces++;
                ax *= 0.5f;
                az *= 0.5f;
                y = vy * rest + (0.005f + g_Ball.groundYForBounces);
            }
            if (frame < 360 && !secondBall) {
                fc->pos.x = x;
                fc->pos.y = y;
                fc->pos.z = z;
                fc->dist = fc->pos.x * fc->pos.x + fc->pos.z * fc->pos.z;
                if (mode == 0 && g_Ball.someYCoord < 0.0f && fc->dist > 1089.0f) {
                    g_Ball.someYCoord = fc->pos.y;
                }
            }
            fc++;
            frame++;
            if (landed && frame >= 360) {
                break;
            }
        }
        for (frame = 0; frame < 360; frame++) {
            g_Ball.physicsSubstruct.futureCoordsAndDist[frame].dist = sqrt540(g_Ball.physicsSubstruct.futureCoordsAndDist[frame].dist);
        }
        if (mode == 0 && g_Ball.someYCoord < 0.0f) {
            g_Ball.someYCoord = 0.0f;
        }
        if (g_Ball.AtBat_ContactResult == 0) {
            g_Ball.physicsSubstruct.hitLandingSpotDistFromHome = sqrt540(
                g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x * g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x +
                g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z * g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
            if (mode == 2) {
                fn_3_DC48(TRUE);
            }
            if (g_Ball.framesUntilBallHitsGround < 360) {
                for (frame = g_Ball.framesUntilBallHitsGround; frame > 0; frame--) {
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[frame].pos.y > 1.3f) {
                        g_Ball._1B98 = frame;
                        break;
                    }
                }
                if (frame == 0) {
                    g_Ball._1B98 = -1;
                }
            } else {
                g_Ball._1B98 = 0;
            }
        }
        if (mode == 2) {
            fn_3_C034();
        }
        if (g_Ball.warioWaluGarlicIsActive == 0 || g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit != 1) {
            return;
        }
        // garlic hit just split: simulate the second ball too
        pastApex = 0;
        landed = 0;
        stopped = 0;
        secondBall = 1;
    } while (1);
}
#endif

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
// NONMATCHING 98.8%: float register allocation around the inlined sqrtf calls
#if NONMATCHING
void fn_3_DC48(BOOL fromPitcher) {
    VecSrcDst ray;
    CollisionStruct hit;
    BALL_COLLISION_TYPE type;
    f32 len;
    s32 i;
    s32 j;
    s32 n;
    f32 wallPlus20;
    f32 ax;
    f32 sx;
    f32 sz;
    if (fromPitcher) {
        ray.src.x = g_Pitcher._30.x;
        ray.src.y = -0.5f;
        ray.src.z = g_Pitcher._30.z;
        if (0.0f == g_Ball.physicsSubstruct.futureCoordsAndDist[60].dist) {
            ray.dst.x = 200.0f * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x;
            ray.dst.y = -0.5f;
            ray.dst.z = 200.0f * g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z;
        } else {
            ray.dst.x = 200.0f * (g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.x / g_Ball.physicsSubstruct.futureCoordsAndDist[60].dist);
            ray.dst.y = -0.5f;
            ray.dst.z = 200.0f * (g_Ball.physicsSubstruct.futureCoordsAndDist[60].pos.z / g_Ball.physicsSubstruct.futureCoordsAndDist[60].dist);
        }
    } else {
        ray.src.x = g_Ball.AtBat_Contact_BallPos.x;
        ray.src.y = -0.5f;
        ray.src.z = g_Ball.AtBat_Contact_BallPos.z;
        ray.dst.x = 200.0f * g_Ball.ballVelocityPercent.x + g_Ball.AtBat_Contact_BallPos.x;
        ray.dst.y = -0.5f;
        ray.dst.z = 200.0f * g_Ball.ballVelocityPercent.z + g_Ball.AtBat_Contact_BallPos.z;
    }
    if (ray.src.x == ray.dst.x && ray.src.z == ray.dst.z) {
        ray.dst.z = 10.0f + ray.src.z;
    }
    type = checkCollision(&ray, &hit, 0, FALSE) & 0x7F;
    g_Ball.someCollisionVariable = 0;
    if (type == BALL_COLLISION_TYPE_WALL || type == BALL_COLLISION_TYPE_UNCLIMBABLE_WALL) {
        g_Ball.ballWillHitBallPos.x = hit.position.x;
        g_Ball.ballWillHitBallPos.z = hit.position.z;
        sx = hit.position.x * hit.position.x;
        sz = hit.position.z * hit.position.z;
        g_Ball.wallAndBallIntersectionDistFromHome = sqrt540(sx + sz);
        len = sqrt540(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z) == 0.0f ? 1.0f : sqrt540(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z);
        g_Ball._1BC0 = 1;
        g_Ball._19E4 = hit.normal.x / len;
        g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint = 0.0f;
        g_Ball.frameBallWillHitWall = -1;
        g_Ball._19E8 = hit.normal.z / len;
        // find the first future frame past the wall
        for (i = 0; i < 360; i += 10) {
            if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > g_Ball.wallAndBallIntersectionDistFromHome) {
                for (j = i - 9, n = 0; n < 10; n++, j++) {
                    if (g_Ball.physicsSubstruct.futureCoordsAndDist[j].dist > g_Ball.wallAndBallIntersectionDistFromHome) {
                        i = 360;
                        g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint = g_Ball.physicsSubstruct.futureCoordsAndDist[j].pos.y;
                        g_Ball.frameBallWillHitWall = j;
                        break;
                    }
                }
            }
        }
        if (g_Ball.Hit_HorizontalAngle >= 0x200 && g_Ball.Hit_HorizontalAngle <= 0x600 && g_Ball.someCollisionInd == 0) {
            wallPlus20 = 20.0f + g_Ball.wallAndBallIntersectionDistFromHome;
            if (((wallPlus20 < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome && g_Ball.Hit_VerticalAngle > 300) ||
                 g_Ball.physicsSubstruct.hitLandingSpotDistFromHome >= 140.0f) &&
                g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint >= 8.0f) {
                ax = g_Ball.ballWillHitBallPos.x;
                if (ax < 0.0f) {
                    ax = -ax;
                }
                if (ax < g_Ball.ballWillHitBallPos.z) {
                    g_Ball.someCollisionVariable = 3;
                    return;
                }
            }
            if (wallPlus20 < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                g_Ball.someCollisionVariable = 2;
            } else if (10.0f + g_Ball.wallAndBallIntersectionDistFromHome < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome && g_Ball.Hit_VerticalAngle > 300) {
                g_Ball.someCollisionVariable = 2;
            } else if (1.0f + g_Ball.wallAndBallIntersectionDistFromHome < g_Ball.physicsSubstruct.hitLandingSpotDistFromHome) {
                g_Ball.someCollisionVariable = 1;
            }
        }
    } else {
        g_Ball.wallAndBallIntersectionDistFromHome = 999.9f;
        g_Ball.physicsSubstruct.throwYAtSelectedFuturePoint = 0.0f;
        g_Ball.frameBallWillHitWall = -1;
    }
}
#endif

// .text:0x0000E2D4 size:0xB78 mapped:0x8064D368
// Per-frame ball bookkeeping: speed, zones, distances to bases, foul estimate, throw timing.
// NONMATCHING 97%: register allocation (float temps, base-table pointer)
#if NONMATCHING
void fn_3_E2D4(void) {
    s32 i;
    f32 d;
    f32 best;
    f32 dx;
    f32 dz;
    f32 foul;
    f32 wx;
    s32 found;
    s32 frame;
    f32 sx;
    f32 sz;
    g_Ball.ballAngleFromHome = fn_3_9FB8C(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);
    fn_3_D9EC();
    g_Ball.ballTravelAngle = fn_3_9FB8C(g_Ball.physicsSubstruct.velocity.x, g_Ball.physicsSubstruct.velocity.z);
    g_Ball.ballZoneAwayFromHome = fn_3_51DF0(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z);
    if (g_Ball.AtBat_ContactResult == 0 && g_Ball.framesSinceHit < 10) {
        g_Ball.landingSpotZoneAwayFromHome = fn_3_51DF0(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x, g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z);
    }
    for (i = 1; i < 4; i++) {
        dx = lbl_3_data_4444[i].x - g_Ball.AtBat_Contact_BallPos.x;
        dz = lbl_3_data_4444[i].z - g_Ball.AtBat_Contact_BallPos.z;
        sx = dx * dx;
        sz = dz * dz;
        g_Ball.ballDistanceFromBase[i] = sqrt540(sx + sz);
    }
    dx = lbl_3_data_4444[4].x - g_Ball.AtBat_Contact_BallPos.x;
    dz = lbl_3_data_4444[4].z - g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.ballDistanceFromBase[0] = g_Ball.ballDistanceFromHome;
    sx = dx * dx;
    sz = dz * dz;
    g_Ball.distLandingSpotToMound = sqrt540(sx + sz);
    if (g_Ball.AtBat_ContactResult == 0) {
        if (g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x > 0.0f) {
            foul = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        } else {
            foul = g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        }
        if (foul < -20.0f) {
            g_Ball.howFoulTheBallWillBe = 3;
        } else if (foul < -10.0f) {
            g_Ball.howFoulTheBallWillBe = 2;
        } else if (foul < -5.0f) {
            g_Ball.howFoulTheBallWillBe = 1;
        } else {
            g_Ball.howFoulTheBallWillBe = 0;
        }
        if (g_Ball.physicsSubstruct.hitLandingSpotDistFromHome > 110.0f) {
            wx = g_Ball.ballWillHitBallPos.x;
            if (wx < 0.0f) {
                wx = -wx;
            }
            foul = g_Ball.ballWillHitBallPos.z - wx;
            if (foul < -20.0f) {
                g_Ball.howFoulTheBallWillBe = 3;
            } else if (foul < -10.0f) {
                g_Ball.howFoulTheBallWillBe = 2;
            } else if (foul < -5.0f) {
                g_Ball.howFoulTheBallWillBe = 1;
            } else {
                g_Ball.howFoulTheBallWillBe = 0;
            }
        }
        if (g_Ball.deadBallReason == 1) {
            g_Ball.howFoulTheBallWillBe = 0;
        }
    }
    if (g_Ball.ballState != BALL_STATE_HELD) {
        g_Ball.fielderWBallIndex = -1;
        g_Ball._1B88 = -1;
        g_Ball.baseBallAndFielderAreOn = -1;
    }
    if (g_Ball.fielderAboutToGetBall_hasBall >= 0) {
        g_Ball.ballIsLooseInd_unused = 0;
    }
    // deep fly ball near the mound with runners on 1st and 2nd: infield fly
    if (g_Ball.AtBat_ContactResult == 0 && g_FieldingLogic._108 == 0 && g_Ball.currentStarSwing2 == 0 &&
        g_Ball.maybeBuntInd == 0 && g_Ball.hangtimeOfHit >= 120 && g_Ball.maxYOfHit > 10.0f &&
        g_Strikes.storedOuts < 2 && g_Ball.howFoulTheBallWillBe < 3 && g_Ball.framesSinceHit == 60 &&
        g_Ball.numFieldersWhoHandledBallDuringPlay == 0) {
        dx = lbl_3_data_4444[4].x - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
        dz = lbl_3_data_4444[4].z - g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        sx = dx * dx;
        sz = dz * dz;
        if (sqrt540(sx + sz) < 30.0f &&
            ((!(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f) &&
              !(g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z < -g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x - 5.0f)) ||
             (g_Ball.Hit_HorizontalAngle >= 0x220 && g_Ball.Hit_HorizontalAngle <= 0x5E0)) &&
            (g_RunningLogic._00 & 0x110) == 0x110) {
            g_FieldingLogic._108 = 1;
        }
    }
    if (g_FieldingLogic._108 != 0 && g_Ball.framesSinceHit == 60) {
        fn_3_59918(6, 0);
    }
    fn_3_DC48(FALSE);
    if (g_Ball.collisionRelated >= 2) {
        g_Ball.groundRuleDoubleInd = 1;
    }
    if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow != 0) {
        if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow++;
        } else {
            g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0x7FFF;
        }
        if (g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow >= 120 || g_Ball.AtBat_ContactResult == 2 ||
            g_Ball.AtBat_ContactResult == 3) {
            g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0;
        }
    }
    g_Ball.throwHasLastedEstimatedNOfFrames = 0;
    if (g_Ball.ballOnMoundInd != 0 && g_Ball.ballState == BALL_STATE_THROWN) {
        // closest future frame to the throw target
        found = -1;
        best = 1e8f;
        for (i = 0; i < 300; i += 2) {
            dz = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z - g_Ball.throwTarget.z;
            dx = g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x - g_Ball.throwTarget.x;
            d = dx * dx + dz * dz;
            if (d < best) {
                found = i;
                best = d;
            } else {
                break;
            }
        }
        frame = -1;
        if (found >= 0) {
            frame = found;
        }
        if (frame == -1) {
            g_Ball.throwHasLastedEstimatedNOfFrames = 1;
        } else {
            g_Ball.framesUntilThrowReachesDest = frame;
        }
    }
    if (g_Ball.baseBallAndFielderAreOn >= 0) {
        if (g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames < 0x7FFE) {
            g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames++;
        } else {
            g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames = 0x7FFF;
        }
    } else {
        g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames = 0;
    }
    fn_3_B940();
    if (g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy != 0) {
        g_Ball.ballEnergy *= lbl_3_data_5CDC[1];
        if (g_Ball.framesSinceLastBounce == 1) {
            g_Ball.ballEnergy *= lbl_3_data_5CDC[2];
        }
        if (g_Ball.ballEnergy < lbl_3_data_5CDC[0]) {
            g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
            g_Ball.ballEnergy = 0.0f;
        }
    }
}
#endif

// .text:0x0000EE4C size:0x390 mapped:0x8064DEE0
void fn_3_EE4C(void) {
    f32 x;
    f32 z;
    f32 radius;
    s32 i;
    g_Ball.offsetWhilePickedUpHistory[0].x = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].y = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].z = 0.0f;
    g_Ball.framesSinceHit = 0;
    g_Ball.framesSinceThrowStarted = -1;
    g_Ball.framesSinceBallHitGroundOrWasCaught = -1;
    g_Ball.framesSinceLastBounce = -1;
    g_Ball.ballHitGrroundDistanceFromHome = 0.0f;
    g_Ball.AtBat_ContactResult = 0;
    g_Ball.ballInitialHitDoneInd = 0;
    g_Ball.fairBallInd = -1;
    g_Ball.howFoulTheBallWillBe = 0;
    g_Ball.ballState = 0;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.maxYOfHit = 0.0f;
    g_Ball.deadBallReason = 0;
    g_Ball.someCollisionVariable = 0;
    g_Ball.deadBallRBIsAddedInd = 0;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.homeRunClassification = 0;
    g_Ball.lineDriveThroughPitcherInd = 0;
    g_Ball.hitWallInd = 0;
    g_Ball.collisionRelated = 0;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = -1;
    g_Ball.groundRuleDoubleInd = 0;
    g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0;
    g_Ball.numberOfThrowsDuringPlay = 0;
    g_Ball.ballZoneWhenCaught = -1;
    if (g_Ball.currentStarSwing == 3 || g_Ball.currentStarSwing == 4) {
        g_Ball.warioStarHitCoords[0].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[0].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[0].z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.warioStarHitCoords[1].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[1].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[1].z = g_Ball.AtBat_Contact_BallPos.z;
        g_Ball.warioStarHitCoords[2].x = g_Ball.AtBat_Contact_BallPos.x;
        g_Ball.warioStarHitCoords[2].y = g_Ball.AtBat_Contact_BallPos.y;
        g_Ball.warioStarHitCoords[2].z = g_Ball.AtBat_Contact_BallPos.z;
        for (i = 0; i < 10; i++) {
            g_Ball.warioStarHitCoords[i + 3].x = g_Ball.AtBat_Contact_BallPos.x;
            g_Ball.warioStarHitCoords[i + 3].y = g_Ball.AtBat_Contact_BallPos.y;
            g_Ball.warioStarHitCoords[i + 3].z = g_Ball.AtBat_Contact_BallPos.z;
        }
    }
    if (g_Minigame.GameMode_MiniGame == 1) {
        g_Batter.hitTrajectory = 3;
        if (g_Batter.buntStatus != 0) {
            g_Batter.hitTrajectory = 6;
        }
        if (g_Ball.bODQualifyingHitInd != 0) {
            for (i = 0; i < 360; i += 5) {
                if (g_Ball.physicsSubstruct.futureCoordsAndDist[i].dist > 80.0f) {
                    s16 ang = fn_3_9FB8C(g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.x, g_Ball.physicsSubstruct.futureCoordsAndDist[i].pos.z);
                    if (ang > 0x240 && ang < 0x5C0) {
                        g_Batter.hitTrajectory = 4;
                    }
                    return;
                }
            }
        }
    } else {
        if (g_Minigame.GameMode_MiniGame == 3) {
            g_Batter.hitTrajectory = 3;
            if (g_Batter.buntStatus != 0) {
                g_Batter.hitTrajectory = 6;
            }
        }
        estimateAndSetFutureCoords(0);
        fn_3_C034();
        if (g_Ball.autoFielderAvoidDropSpotForPeachesStarHit != 0) {
            if (g_Ball.currentStarSwing == 0xB) {
                radius = RandomF32_Game_Range(lbl_3_data_4930[0x9C / 4], lbl_3_data_4930[0xA0 / 4]);
            } else {
                radius = RandomF32_Game_Range(lbl_3_data_4930[0xA4 / 4], lbl_3_data_4930[0xA8 / 4]);
            }
            getComponentsFromSAng(RandomInt_Game(0x1000), &x, &z);
            g_Ball.peachDaisyStarHitFielderLoc.x = x * radius + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.x;
            g_Ball.peachDaisyStarHitFielderLoc.z = z * radius + g_Ball.physicsSubstruct.ballLandingSpotOrHeldSpot.z;
        }
    }
}

// .text:0x0000F1DC size:0x39C mapped:0x8064E270
// NONMATCHING 87%: scheduling of the inlined random reseed against the resets
#if NONMATCHING
void fn_3_F1DC(void) {
    s32 i;
    g_Ball.AtBat_Contact_BallPos.x = lbl_3_data_450C[0];
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = lbl_3_data_450C[1];
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
    ballSeedRandom();
    g_Ball.StaticRandomInt1_prePitch = g_Ball.StaticRandomInt1;
    g_Ball.framesSinceHit = -1;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.physicsSubstruct.gravity = lbl_3_data_45FC;
    g_Ball.framesSinceThrowStarted = -1;
    g_Ball.pitchHangtimeCounter = -1;
    g_Ball.postPitchResultCounter = -1;
    g_Ball.framesSinceBallHitGroundOrWasCaught = -1;
    g_Ball.framesSinceLastBounce = -1;
    g_Ball.framesSincePickOff = -1;
    g_Ball.ballHitGrroundDistanceFromHome = 0.0f;
    g_Ball.AtBat_ContactResult = 0;
    g_Ball.ballInitialHitDoneInd = 0;
    g_Ball.fairBallInd = -1;
    g_Ball.howFoulTheBallWillBe = 0;
    g_Ball.always0_fairFoulRelated = 0;
    g_Ball.ballState = 0;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.maxYOfHit = 0.0f;
    g_Ball.deadBallReason = 0;
    g_Ball.someCollisionVariable = 0;
    g_Ball.deadBallRBIsAddedInd = 0;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.fielderBeingThrownTo = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.homeRunClassification = 0;
    g_Ball.lineDriveThroughPitcherInd = 0;
    g_Ball.hitWallInd = 0;
    g_Ball.fielderWithBallIndexStored = -1;
    g_Ball.fielderWithBallIndexStored2 = -1;
    g_Ball.fielderWhoGotLastOut = -1;
    g_Ball.throwingFielder = -1;
    g_Ball.maybeBuntInd = 0;
    g_Ball.maybebuntOn2Strikes = 0;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = -1;
    g_Ball.groundRuleDoubleInd = 0;
    g_Ball.matchFramesAndBallAngle.framesAfterReceivingThrow = 0;
    g_Ball.numberOfThrowsDuringPlay = 0;
    g_Ball.framesOnGroundUntilPickedUp = 0;
    g_Ball.numFieldersWhoHandledBallDuringPlay = 0;
    g_Ball.numThrowsDuringPlay = 0;
    g_Ball.bobbleLocation_1fair_2foul = 0;
    g_Ball.matchFramesAndBallAngle.ballAndFielderOnBaseFrames = 0;
    g_Ball.homeRunInd = 0;
    g_Ball.matchFramesAndBallAngle.ballOverWallFrames = 0;
    g_Ball.ballZoneWhenCaught = -1;
    g_Ball._1BDF = 0;
    g_Ball.matchFramesAndBallAngle.framesSinceFoulCalled = 0;
    g_Ball.collisionRelated = 0;
    g_Ball.landingSpotZoneAwayFromHome = 0;
    g_Ball.ballZoneAwayFromHome = 0;
    g_Ball.looseBall_codeForHowLongUntilSomeoneWillGetIt = 0;
    g_Ball.someYCoord = -1.0f;
    g_Ball.looseBall_5FrameCountdown = 0;
    g_Ball.ballIsRollingIndicator = 0;
    g_Ball.ballPickedUpCaught.x = 0.0f;
    g_Ball.ballPickedUpCaught.z = 0.0f;
    g_Ball.matchFramesAndBallAngle.framesOnGround = 0;
    g_Ball.inAirOrBefore2ndBounceOrLowBallEnergy = 0;
    g_Ball.hardHitIndicator = 0;
    g_Ball.ballEnergy = 0.0f;
    g_Ball.framesSinceBallHitWall = 0;
    g_Ball.hittingAddedGravityFactor = 0.0f;
    g_Ball.currentStarSwing = 0;
    g_Ball.currentStarSwing2 = 0;
    g_Ball.knockoutProcessedFlag = 0;
    g_Ball.bODQualifyingHitInd = 0;
    g_Ball.IsAntichemistryThrow = 0;
    g_Ball.warioWaluGarlicIsActive = 0;
    g_Ball.matchFramesAndBallAngle.garlicHitFramesSinceSplit = 0;
    g_Ball.autoFielderAvoidDropSpotForPeachesStarHit = 0;
    g_Ball.fielderActionOccuring = 0;
    g_Ball.catchAnimationTotalFrames = 0;
    g_Ball._1BC0 = 1;
    g_Ball.someCollisionInd = 0;
    g_Ball.hitNoteBlockInd = 0;
    g_Ball.pauseBallMovementWhenInPlant = 0;
    g_Ball.ballCughtByPlantInd = 0;
}
#endif

// .text:0x0000F578 size:0x240 mapped:0x8064E60C
void fn_3_F578(void) {
    s32 i;
    g_Ball.AtBat_Contact_BallPos.x = lbl_3_data_450C[0];
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = lbl_3_data_450C[1];
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
    g_Ball.AtBat_Contact_BallPos.x = lbl_3_data_450C[0];
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = lbl_3_data_450C[1];
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
    g_Ball.AtBat_Contact_BallPos.x = lbl_3_data_450C[0];
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = lbl_3_data_450C[1];
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
    s32 i;
    s32 t;
    g_Ball.AtBat_Contact_BallPos.x = lbl_3_data_450C[0];
    g_Ball.AtBat_Contact_BallPos.y = 0.0f;
    g_Ball.AtBat_Contact_BallPos.z = lbl_3_data_450C[1];
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
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.physicsSubstruct.velocity.x = 0.0f;
    g_Ball.physicsSubstruct.velocity.y = 0.0f;
    g_Ball.physicsSubstruct.velocity.z = 0.0f;
    g_Ball.physicsSubstruct.acceleration.x = 0.0f;
    g_Ball.physicsSubstruct.acceleration.y = 0.0f;
    g_Ball.physicsSubstruct.acceleration.z = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].x = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].y = 0.0f;
    g_Ball.offsetWhilePickedUpHistory[0].z = 0.0f;
    g_Ball.physicsSubstruct.gravity = lbl_3_data_45FC;
    g_Ball.airResistance = lbl_3_data_4600;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.ballState = 0;
    g_Ball.AtBat_ContactResult = 0;
    g_Ball.ballInitialHitDoneInd = 0;
    g_Ball.fairBallInd = -1;
    g_Ball.ballStoppingCode1ReallySlow2Stopped = 0;
    g_Ball.framesSinceHit = -1;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = -1;
    g_Ball.framesSinceBallHitGroundOrWasCaught = -1;
    g_Ball.Hit_HorizontalPower = 0x6E;
    g_Ball.Hit_VerticalAngle = 0x18D;
    g_Ball.Hit_HorizontalAngle = 0x272;
    g_FieldingLogic._0C4 = -1;
    g_FieldingLogic._0C6 = -1;
    g_Strikes.outs = 0;
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    if (g_d_GameSettings.GameModeSelected == 6) {
        g_Ball.groundYForBounces = lbl_3_data_45F4[1];
    } else {
        g_Ball.groundYForBounces = lbl_3_data_45F4[0];
    }
    // same as fn_3_10030 (`- (-t)` keeps the original add operand order)
    t = ((lbl_3_data_228.counter % 10) + 1) * (g_Ball.StaticRandomInt1 * rand());
    g_Ball.StaticRandomInt1 = (rand() * 16 - (-t) + (s32)(lbl_3_data_228.counter >> 1) + g_d_GameSettings.FrameCountWhileNotAtMainMenu) & 0x7FFF;
    t = ((lbl_3_data_228.counter % 10) + 1) * ((g_Ball.StaticRandomInt2 + 1) * rand());
    g_Ball.StaticRandomInt2 = (rand() * 8 - (-t) + (s32)(lbl_3_data_228.counter >> 1) + (g_d_GameSettings.FrameCountWhileNotAtMainMenu >> 1)) & 0x7FFF;
}
