#include "game/rep_1200.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#include "static/GameSettings.h"

extern GameScores g_Scores;
extern f32 lbl_3_data_446C[];
extern const f32 lbl_3_rodata_1250;
extern const f32 lbl_3_rodata_1258;
extern const f32 lbl_3_rodata_12A8;
extern const f32 lbl_3_rodata_1290;
extern const f32 lbl_3_rodata_12AC;
extern f32 lbl_3_data_5E98[];
extern void fn_3_5C69C(s32 type);
extern void fn_3_6EBB4(s32 rosterLoc);
extern void fn_3_89864(s32 i, s32 d);
extern s32 fn_8001C920(s32 id);
extern void fn_3_7A154(s32 inPlay);
// the callee returns u8, but callers here test the full register (int-returning prototype in the original)
extern u32 fn_3_107DB4(s8 i);
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

// View of lbl_3_common_bss_32724 (in-game HUD flags), only the fields used here.
typedef struct Rep1200Bss32724View {
    /*0x00*/ u8 _00[0x9C];
    /*0x9C*/ u8 _9C;
    /*0x9D*/ u8 _9D[0xB1 - 0x9D];
    /*0xB1*/ u8 _B1;
    /*0xB2*/ u8 _B2;
    /*0xB3*/ u8 _B3;
    /*0xB4*/ u8 _B4;
} Rep1200Bss32724View;
extern Rep1200Bss32724View lbl_3_common_bss_32724;

// View of lbl_803CBC3C, only the fields used here.
typedef struct Rep1200CBC3CView {
    /*0x00*/ u8 _00;
    /*0x01*/ u8 _01;
} Rep1200CBC3CView;
extern Rep1200CBC3CView lbl_803CBC3C;

// Character table (lbl_800E8558), only the fields used here.
typedef struct Rep1200CharEntry {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 id;
    /*0x2*/ u8 group; // index into the hit-by-pitch box table
    /*0x3*/ u8 _3[3];
} Rep1200CharEntry; // size: 0x6
extern Rep1200CharEntry lbl_800E8558[];

extern f32 lbl_3_data_5F90[];

// .text:0x0006F6CC size:0x7C mapped:0x806AE760
int fn_3_6F6CC(void) {
    int i;
    InMemRunnerType* r = &g_Runners[1];
    for (i = 0; i < 3; i++) {
        if (r->runnerOnFieldOrOutOrScored == 1 && r->percentTowardsNextBase > 0.5f) {
            g_Pitcher.pickOffLoc = 4;
            fn_3_5C69C(0);
            return 1;
        }
        r++;
    }
    return 0;
}

// .text:0x0006F748 size:0x2E0 mapped:0x806AE7DC
// g_RunningLogic (0x20 bytes), only the fields used here.
typedef struct Rep1200RunningLogicView {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11[0x20 - 0x11];
} Rep1200RunningLogicView;
extern Rep1200RunningLogicView g_RunningLogic;
extern s32 fn_3_20B30(void);
static inline void countPickoffAttempt(void) {
    if (g_Pitcher.nPickoffAttempts < 0xFE) {
        g_Pitcher.nPickoffAttempts += 1;
    } else {
        g_Pitcher.nPickoffAttempts = 0xFF;
    }
}
// Pitcher pickoff input; returns 1 when a pickoff was started.
int fn_3_6F748(void) {
    s32 team = g_GameLogic.teamFielding;
    InputStruct* c = &g_Controls[g_GameLogic.teams[team]];
    u16 buttons;
    if (g_Pitcher.AIInd != 0) {
        if (fn_3_20B30() == 0) {
            return 0;
        }
        goto pickoff;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        c = &g_Practice.inputs[team];
    } else {
        MiniGameControlStruct* m = g_Minigame.minigameControlStruct;
        if (fn_3_107DB4(m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]) != 0) {
            c = &g_Minigame._1D7C[m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
        } else if (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame.minigamePlayerSelectedOrder >= 0) {
            c = &g_Controls[m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
        }
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0x5A) {
        return 0;
    }
    if (g_RunningLogic._10 <= 1) {
        return 0;
    }
    if (fn_3_6F6CC()) {
        countPickoffAttempt();
        return 1;
    }
    if (c->newButtonInput & 0x200) {
        g_Pitcher.pickOffLoc = 4;
        buttons = c->buttonInput;
        if (buttons & 1) {
            if (g_Runners[3].runnerOnFieldOrOutOrScored != 0) {
                g_Pitcher.pickOffLoc = 3;
            }
        } else if (buttons & 8) {
            if (g_Runners[2].runnerOnFieldOrOutOrScored != 0) {
                g_Pitcher.pickOffLoc = 2;
            }
        } else if (buttons & 2) {
            if (g_Runners[1].runnerOnFieldOrOutOrScored != 0) {
                g_Pitcher.pickOffLoc = 1;
            }
        }
    pickoff:
        fn_3_5C69C(0);
        countPickoffAttempt();
        return 1;
    }
    return 0;
}

// .text:0x0006FA28 size:0x170 mapped:0x806AEABC
extern const f32 lbl_3_rodata_1254;
extern void fn_3_DBD0(void);
// Ball bounce physics (per stadium, indexed by g_d_GameSettings.StadiumID).
typedef struct BallBounceParams {
    /*0x00*/ f32 _00;
    /*0x04*/ f32 bounceDamp;
    /*0x08*/ f32 _08;
    /*0x0C*/ f32 groundFriction;
    /*0x10*/ f32 rollFriction;
} BallBounceParams; // size: 0x14
extern BallBounceParams lbl_3_data_4388[];
// 6FA28 and 6FB98 share this block (inlined).
static inline void ballStep(void) {
    f32 v;
    f32 vy;
    if (g_Ball.pitchHangtimeCounter < 0x7FFE) {
        g_Ball.pitchHangtimeCounter += 1;
    } else {
        g_Ball.pitchHangtimeCounter = 0x7FFF;
    }
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter += 1;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    g_Ball.pastCoordinates[0].x = g_Ball.AtBat_Contact_BallPos.x;
    g_Ball.pastCoordinates[0].y = g_Ball.AtBat_Contact_BallPos.y;
    g_Ball.pastCoordinates[0].z = g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.physicsSubstruct.velocity.y = g_Ball.physicsSubstruct.velocity.y - g_Ball.physicsSubstruct.gravity;
    fn_3_DBD0();
    g_Ball.AtBat_Contact_BallPos.x = g_Ball.AtBat_Contact_BallPos.x + g_Ball.physicsSubstruct.velocity.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Ball.AtBat_Contact_BallPos.y + g_Ball.physicsSubstruct.velocity.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Ball.AtBat_Contact_BallPos.z + g_Ball.physicsSubstruct.velocity.z;
    if (g_Ball.AtBat_Contact_BallPos.y < g_Ball.groundYForBounces) {
        vy = g_Ball.physicsSubstruct.velocity.y;
        v = vy * -(vy * lbl_3_rodata_1250 - lbl_3_data_4388[g_d_GameSettings.StadiumID].bounceDamp);
        g_Ball.physicsSubstruct.velocity.y = v;
        g_Ball.physicsSubstruct.velocity.y = -v;
        if (g_Ball.physicsSubstruct.velocity.y < lbl_3_rodata_1254) {
            g_Ball.physicsSubstruct.velocity.x = g_Ball.physicsSubstruct.velocity.x * lbl_3_data_4388[g_d_GameSettings.StadiumID].rollFriction;
            g_Ball.physicsSubstruct.velocity.z = g_Ball.physicsSubstruct.velocity.z * lbl_3_data_4388[g_d_GameSettings.StadiumID].rollFriction;
        } else {
            g_Ball.physicsSubstruct.velocity.x = g_Ball.physicsSubstruct.velocity.x * lbl_3_data_4388[g_d_GameSettings.StadiumID].groundFriction;
            g_Ball.physicsSubstruct.velocity.z = g_Ball.physicsSubstruct.velocity.z * lbl_3_data_4388[g_d_GameSettings.StadiumID].groundFriction;
        }
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.groundYForBounces;
    }
}
void fn_3_6FA28(void) {
    ballStep();
}

// .text:0x0006FB98 size:0x208 mapped:0x806AEC2C
extern void fn_3_59918(s32 x, s32 unused);
void fn_3_6FB98(void) {
    u8* stars;
    ballStep();
    if (g_Pitcher.currentStateFrameCounter == 10) {
        fn_3_59918(0xB, 0);
        g_Pitcher.pitcherActionState = 5;
        g_Pitcher.currentStateFrameCounter = 0;
        if (g_GameLogic.IsStarChance == 1) {
            // &g_GameLogic.TeamStars[teamBatting], spelled as byte offsets to match (lbzu)
            stars = (u8*)&g_GameLogic + g_GameLogic.teamBatting;
            if (*(stars += 0x14A) < 5) {
                *stars += 1;
                if (g_Stats.replayInd == 0) {
                    playSoundEffect(0x19D);
                }
            }
            g_GameLogic.IsStarChance = 3;
        }
    }
}

// .text:0x0006FDA0 size:0x224 mapped:0x806AEE34
extern const f32 lbl_3_rodata_1278;
extern const f64 lbl_3_rodata_1260;
extern const f64 lbl_3_rodata_1268;
extern const f64 lbl_3_rodata_1270;
static inline f32 sqrt_ext(f32 x) {
    if (x > 0.0f) {
        f64 h = lbl_3_rodata_1260;
        f64 th = lbl_3_rodata_1268;
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = h * guess * (th - guess * guess * xd);
        guess = h * guess * (th - guess * guess * xd);
        guess = h * guess * (th - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (x < lbl_3_rodata_1270)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}
void fn_3_6FDA0(void) {
    s16 ang;
    f32 a;
    f32 b;
    f32 mag;
    f32 k;
    f32 t;
    s32 off = g_Ball.StaticRandomInt1 % 257 - 0x80;
    ang = fn_3_9FB8C(g_Pitcher.ballVelocity.x, -g_Pitcher.ballVelocity.z);
    getComponentsFromSAng(ang + off, &a, &b);
    t = lbl_3_rodata_1254 * (f32)(g_Ball.StaticRandomInt2 % 10);
    mag = sqrt_ext(g_Pitcher.ballVelocity.x * g_Pitcher.ballVelocity.x + g_Pitcher.ballVelocity.z * g_Pitcher.ballVelocity.z);
    k = lbl_3_rodata_1278 + t;
    g_Ball.physicsSubstruct.velocity.x = k * (a * mag);
    g_Ball.physicsSubstruct.velocity.z = k * (b * mag);
    g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_1258;
}

// .text:0x0006FFC4 size:0x2BC mapped:0x806AF058
// NONMATCHING 99%: f4/f5 swapped (orig keeps the |v|^2 sum in f5 and t in f4); same code as fn_3_6FDA0 which matches
#if NONMATCHING
void fn_3_6FFC4(void) {
    s16 ang;
    f32 b;
    f32 a;
    f32 mag;
    f32 k;
    f32 t;
    s32 off = g_Ball.StaticRandomInt1 % 257 - 0x80;
    ang = fn_3_9FB8C(g_Pitcher.ballVelocity.x, -g_Pitcher.ballVelocity.z);
    getComponentsFromSAng(ang + off, &a, &b);
    t = lbl_3_rodata_1254 * (f32)(g_Ball.StaticRandomInt2 % 10);
    mag = sqrt_ext(g_Pitcher.ballVelocity.x * g_Pitcher.ballVelocity.x + g_Pitcher.ballVelocity.z * g_Pitcher.ballVelocity.z);
    k = lbl_3_rodata_1278 + t;
    g_Ball.physicsSubstruct.velocity.x = k * (a * mag);
    g_Ball.physicsSubstruct.velocity.z = k * (b * mag);
    g_Ball.physicsSubstruct.velocity.y = lbl_3_rodata_1258;
    g_Pitcher.strikeOutOrWalk = 3;
    g_Pitcher.miniGameRelated = 1;
    g_Pitcher.framesSinceAtBatEnded = 0;
    playSoundEffect(0x170);
    if (g_Batter.aiControlledInd == 0) {
        if (g_d_GameSettings.minigamesEnabled != 0) {
            fn_3_6C854(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID], 2);
        } else {
            fn_3_6C854(g_GameLogic.teamBatting, 2);
        }
    }
    fn_3_7A154(0);
}
#endif

// .text:0x00070280 size:0x16C mapped:0x806AF314
// Hit-by-pitch box per character group: {max y, max x, max -x}.
extern u8 lbl_3_data_76FC[];
extern const f32 lbl_3_rodata_1288;
void fn_3_70280(void) {
    s32 k;
    s32 x;
    s32 y;
    s32 hit = 0;
    if ((g_GameLogic.secondaryGameMode != 0xB || g_Practice._1DB != 0) && g_Minigame.GameMode_MiniGame != 2 &&
        g_Batter.framesSinceStartOfSwing <= 0 && g_Pitcher.calledStrikeInd == 0) {
        x = (s32)(lbl_3_rodata_1288 * (g_Pitcher.ballCurrentPosition.x - g_Batter.batterPos.x));
        y = (s32)(lbl_3_rodata_1288 * (g_Pitcher.ballCurrentPosition.z - g_Batter.batterPos.z));
        if (g_Batter.batterHand != 0) {
            x = -x;
        }
        k = lbl_800E8558[g_Batter.charID].group * 3;
        if (y <= lbl_3_data_76FC[k]) {
            if ((f32)y >= lbl_3_rodata_1258) {
                if (x <= lbl_3_data_76FC[k + 1] && x >= -lbl_3_data_76FC[k + 2]) {
                    hit = 1;
                }
            }
        }
        if (hit != 0) {
            g_Batter.hitByPitch = 1;
        }
    }
}

// .text:0x000703EC size:0x294 mapped:0x806AF480
extern void fn_3_1DD48(void);
void fn_3_703EC(void) {
    u8* p;
    s16 fr = g_Batter.framesSinceStartOfSwing;
    if (fr <= 0 || fr >= swingSoundFrame[0][1] || g_Batter._95 != 0) {
        g_Pitcher.miniGameRelated = 1;
        if (g_Pitcher.strikeInd != 0) {
            if (++g_Strikes.strikes >= 3) {
                g_Pitcher.strikeOutOrWalk = 1;
                g_Pitcher.framesSinceAtBatEnded = 0;
                g_Pitcher.pitcherActionState = 5;
                g_Pitcher.currentStateFrameCounter = 0;
                fn_3_59918(0x10, 0);
                if (g_GameLogic.IsStarChance == 1) {
                    GameScoresTeam* sc;
                    if ((g_Scores.inning < g_Scores.maxInnings || g_Scores._AD == 0 || g_Strikes.outs < 2 ||
                         !((sc = g_Scores.team)[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0] > sc[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0])) &&
                        (g_Scores.inning < g_Scores._AB || g_Scores._AD == 0 || g_Strikes.outs < 2)) {
                        // &g_GameLogic.TeamStars[teamFielding], spelled as byte offsets to match (lbzu)
                        p = (u8*)&g_GameLogic + g_GameLogic.teamFielding;
                        if (*(p += 0x14A) < 5) {
                            (*p)++;
                            if (g_Stats.replayInd == 0) {
                                playSoundEffect(0x19D);
                            }
                        }
                    }
                    g_GameLogic.IsStarChance = 2;
                }
                if (g_d_GameSettings.GameModeSelected == 6) {
                    g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
                }
            } else {
                fn_3_59918(8, 0);
            }
        } else {
            if (++g_Strikes.balls >= 4) {
                g_Pitcher.strikeOutOrWalk = 2;
                g_Pitcher.framesSinceAtBatEnded = 0;
                g_Pitcher.pitcherActionState = 5;
                g_Pitcher.currentStateFrameCounter = 0;
                fn_3_59918(0xA, 0);
                if (g_GameLogic.IsStarChance == 1) {
                    // &g_GameLogic.TeamStars[teamBatting], spelled as byte offsets to match (lbzu)
                    p = (u8*)&g_GameLogic + g_GameLogic.teamBatting;
                    if (*(p += 0x14A) < 5) {
                        (*p)++;
                        if (g_Stats.replayInd == 0) {
                            playSoundEffect(0x19D);
                        }
                    }
                    g_GameLogic.IsStarChance = 3;
                }
            } else {
                fn_3_59918(9, 0);
            }
        }
        fn_3_7A154(0);
        fn_3_1DD48();
    }
}

// .text:0x00070680 size:0x38 mapped:0x806AF714
int fn_3_70680(f32 v) {
    if (v >= g_Pitcher.strikeZoneLeft && v <= g_Pitcher.strikeZoneRight) {
        return 1;
    }
    return 0;
}

// .text:0x000706B8 size:0xB0 mapped:0x806AF74C
void fn_3_706B8(int idx) {
    f32 t;
    f32 x;
    f32 y;
    if (g_Minigame.GameMode_MiniGame != 2) {
        t = ((&g_Pitcher.beginningOfStrikeCheckZ)[idx] - g_Pitcher.ballCurrentPosition.z) / (g_Pitcher.ballLastPosition.z - g_Pitcher.ballCurrentPosition.z);
        x = t * (g_Pitcher.ballLastPosition.x - g_Pitcher.ballCurrentPosition.x) + g_Pitcher.ballCurrentPosition.x;
        y = t * (g_Pitcher.ballLastPosition.y - g_Pitcher.ballCurrentPosition.y) + g_Pitcher.ballCurrentPosition.y;
        g_Pitcher.estimatedEndingPos.x = x;
        g_Pitcher.estimatedEndingPos.z = y;
        if (fn_3_70680(x)) {
            g_Pitcher.calledStrikeInd = 1;
            g_Pitcher.strikeInd = 1;
        }
    }
}

// .text:0x00070768 size:0xD0 mapped:0x806AF7FC
extern const f32 lbl_3_rodata_128C;
// NONMATCHING 96%: only the trailing lerp differs (orig computes z-pz before z-target and does not fuse
// px + dx*t into fmadds); ~1000 variants tried (docs/patterns/unsolved.md)
#if NONMATCHING
int fn_3_70768(f32* out, int flag, f32 target) {
    int n = 0;
    f32 z = g_Pitcher.ballCurrentPosition.z;
    f32 x = g_Pitcher.ballCurrentPosition.x;
    f32 vx = g_Pitcher.ballVelocity.x;
    f32 vy = g_Pitcher.ballVelocity.y;
    f32 vz = g_Pitcher.ballVelocity.z;
    f32 add = g_Pitcher.pitchCurveVeloV1;
    f32 px, pz;
    f32 fl, bo, dr;
    f32 t;
    if (z < target) {
        return 0;
    }
    fl = g_Pitcher.pitchZ_whenAirResistanceStarts;
    bo = g_Pitcher.airResistance_veloAdj;
    dr = g_Pitcher.decelerationFactor;
    do {
        px = x;
        pz = z;
        n++;
        if (z <= fl) {
            f32 nvz = vz - vz * bo;
            if (nvz < lbl_3_rodata_128C) {
                vz = nvz;
                vx = vx - vx * bo;
                vy = vy - vy * bo;
            }
        }
        vx *= dr;
        vz *= dr;
        vy *= dr;
        x += vx;
        z += vz;
        if (flag != 0) {
            x += add;
        }
    } while (!(z < target));
    {
        f32 dz = z - pz;
        f32 num = z - target;
        f32 dx = x - px;
        *out = px + dx * (lbl_3_rodata_1290 - num / dz);
    }
    return n;
}
#endif

// .text:0x00070838 size:0x17C mapped:0x806AF8CC
// Egg-ball bounce params: [0] y, [1..2] z range, [3] x range, [4..5] bounce z range, [6..7] x range.
extern f32 lbl_3_data_5F5C[];
typedef struct PitchSpeedRange {
    /*0x00*/ s16 speedMin; // star-pitch (egg) speed range
    /*0x02*/ s16 speedMax;
    /*0x04*/ u8 _04[4];
    /*0x08*/ s16 eggMin;
    /*0x0A*/ s16 eggMax;
    /*0x0C*/ s16 eggVeloMin;
    /*0x0E*/ s16 eggVeloMax;
} PitchSpeedRange;
extern PitchSpeedRange lbl_3_data_5F7C;
void fn_3_70838(void) {
    f32 d;
    f32 dx;
    f32 dy;
    u8 v;
    if (g_Pitcher.eggBallBounceNumber == 0) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-lbl_3_data_5F5C[6], lbl_3_data_5F5C[6]);
        g_Pitcher.eggBallBounceYHeight = lbl_3_data_5F5C[0];
        g_Pitcher.eggBallBounceZLoc = RandomF32_Game_Range(lbl_3_data_5F5C[4], lbl_3_data_5F5C[5]);
        g_Pitcher.frontOfPlateZ = lbl_3_rodata_1250 * (g_Pitcher.eggBallBounceZLoc + g_Pitcher.frontOfPlateZ);
    } else {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-lbl_3_data_5F5C[7], lbl_3_data_5F5C[7]);
        g_Pitcher.eggBallBounceYHeight = lbl_3_data_5F5C[0];
        g_Pitcher.frontOfPlateZ = g_Pitcher.centerOfStrikeZone.z;
    }
    v = RandomInt_Game_Range(lbl_3_data_5F7C.eggMin, lbl_3_data_5F7C.eggMax);
    dx = g_Pitcher.pitchStartingPosition_AIMaxCurve - g_Pitcher.ballCurrentPosition.x;
    dy = g_Pitcher.eggBallBounceYHeight - g_Pitcher.ballCurrentPosition.y;
    d = g_Pitcher.ballCurrentPosition.z - g_Pitcher.frontOfPlateZ;
    g_Pitcher.pitchSpeed = v;
    g_Pitcher.eggBallBounceNumber = g_Pitcher.eggBallBounceNumber + 1;
    g_Pitcher.ballVelocity.z = -((f32)v / g_Pitcher.pitchSpeedScaler);
    g_Pitcher.framesSinceFirstEggBounce = 0;
    g_Pitcher.ballVelocity.x = -((dx * g_Pitcher.ballVelocity.z) / d);
    g_Pitcher.ballVelocity.y = -((dy * g_Pitcher.ballVelocity.z) / d);
}

// .text:0x000709B4 size:0x138 mapped:0x806AFA48
extern u8 lbl_3_data_5F50[];
extern const f32 lbl_3_rodata_12A0;
extern const f32 lbl_3_rodata_12A4;
void fn_3_709B4(void) {
    f32 c;
    f32 s;
    f32 a;
    f32 t;
    u8 n = g_Pitcher.bulletPitchFrameCounter + 1;
    g_Pitcher.bulletPitchFrameCounter = n;
    if (n >= g_Pitcher.bulletPitchLoopFrames) {
        g_Pitcher.bulletPitchStageCode = 2;
        return;
    }
    a = (f32)n / (f32)g_Pitcher.bulletPitchLoopFrames;
    a = a * lbl_3_rodata_12A0;
    a = a + lbl_3_rodata_12A4;
    getComponentsFromRad(a, &c, &s);
    t = lbl_3_rodata_1254 * (f32)lbl_3_data_5F50[g_Pitcher.starPitchType * 5 - 0x1F];
    g_Pitcher.starPitchPositionAdjustment.y = c * t + t;
    g_Pitcher.starPitchPositionAdjustment.z = s * t;
    g_Pitcher.starPitchPositionAdjustment.x = lbl_3_rodata_1258;
    g_Pitcher.bulletPitchLoopAngleRadians = a;
}

// .text:0x00070AEC size:0xA8 mapped:0x806AFB80
void fn_3_70AEC(void) {
    f32 t;
    if (g_Pitcher.cancelParabolicAdjustmentInd != 0) {
        g_Pitcher.pitchX_parabolicAdjustment = lbl_3_rodata_1258;
        return;
    }
    t = g_Ball.pitchHangtimeCounter - g_Pitcher.frameWhenUnhittable * lbl_3_rodata_1250;
    g_Pitcher.pitchX_parabolicAdjustment = g_Pitcher.horizontalOffsetParabolaMidpoint - (t * (g_Pitcher.horizontalGlobalParabolicVelo * t)) / lbl_3_rodata_12A8;
}

// .text:0x00070B94 size:0x360 mapped:0x806AFC28
extern s32 LERPToNewRange_Float(s32 value, s32 inMin, s32 inMax, s32 outMin, s32 outMax);
// Vertical (y) parabolic offset of the pitch; egg-ball pitches bounce.
void fn_3_70B94(void) {
    f32 t;
    if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 0xA) {
        if (g_Pitcher.eggBallBounceNumber == 0) {
            t = g_Ball.pitchHangtimeCounter - g_Pitcher.frameWhenUnhittable * lbl_3_rodata_1250;
            g_Pitcher.pitchY_parabolicAdjustment =
                g_Pitcher.verticalOffsetParabolaMidpoint - (t * (g_Pitcher.verticalGlobalParabolicVelo * t)) / lbl_3_rodata_12A8;
        } else if (g_Pitcher.eggBallBounceNumber == 1 || g_Pitcher.eggBallBounceNumber == 2) {
            if (g_Pitcher.framesSinceFirstEggBounce == 1) {
                if (g_Pitcher.eggBallBounceNumber == 1) {
                    f32 frames = fn_3_70768(&t, 0, g_Pitcher.eggBallBounceZLoc);
                    g_Pitcher.ballBouncePeakZ = frames * lbl_3_rodata_1250;
                    g_Pitcher.verticalGlobalParabolicVelo = LERPToNewRange_Float(
                        g_Pitcher.pitchSpeed, lbl_3_data_5F7C.eggMin, lbl_3_data_5F7C.eggMax, lbl_3_data_5F7C.eggVeloMin, lbl_3_data_5F7C.eggVeloMax);
                    t = g_Pitcher.ballBouncePeakZ;
                    g_Pitcher.verticalOffsetParabolaMidpoint = (t * (g_Pitcher.verticalGlobalParabolicVelo * t)) / lbl_3_rodata_12A8;
                } else {
                    g_Pitcher.ballBouncePeakZ = g_Pitcher.framesUntilBallReachesBatterZ;
                    g_Pitcher.verticalOffsetParabolaMidpoint = lbl_3_rodata_12AC + lbl_3_data_5E98[4];
                    t = g_Pitcher.framesUntilBallReachesBatterZ;
                    g_Pitcher.verticalGlobalParabolicVelo = (lbl_3_rodata_12A8 * g_Pitcher.verticalOffsetParabolaMidpoint) / (t * t);
                }
            }
            t = (f32)g_Pitcher.framesSinceFirstEggBounce - (f32)g_Pitcher.ballBouncePeakZ;
            g_Pitcher.pitchY_parabolicAdjustment =
                g_Pitcher.verticalOffsetParabolaMidpoint - (t * (g_Pitcher.verticalGlobalParabolicVelo * t)) / lbl_3_rodata_12A8;
        } else {
            g_Pitcher.pitchY_parabolicAdjustment = lbl_3_rodata_1258;
        }
    } else if (g_Pitcher.cancelParabolicAdjustmentInd != 0) {
        g_Pitcher.pitchY_parabolicAdjustment = lbl_3_rodata_1258;
    } else {
        t = g_Ball.pitchHangtimeCounter - g_Pitcher.frameWhenUnhittable * lbl_3_rodata_1250;
        g_Pitcher.pitchY_parabolicAdjustment =
            g_Pitcher.verticalOffsetParabolaMidpoint - (t * (g_Pitcher.verticalGlobalParabolicVelo * t)) / lbl_3_rodata_12A8;
    }
}

// .text:0x00070EF4 size:0x354 mapped:0x806AFF88
// Per special-pitch-type curve parameters (lbl_3_data_5D6C).
typedef struct PitchCurveParams {
    /*0x0*/ s16 speed;
    /*0x2*/ s16 curveMin;
    /*0x4*/ s16 curveMax;
    /*0x6*/ s16 _6[4];
} PitchCurveParams; // size: 0xE
extern PitchCurveParams lbl_3_data_5D6C[];
extern f32 lbl_3_data_5E78[];
extern const f32 lbl_3_rodata_1288;
extern const f32 lbl_3_rodata_12B0;
extern s32 fn_3_20CEC(f32 k);
// Curve input while the pitch is in the air.
void fn_3_70EF4(void) {
    InputStruct* c = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    PitchCurveParams* e = &lbl_3_data_5D6C[g_Pitcher.specialPitchTypeCode];
    s32 dir;
    f32 maxCurve;
    f32 control;
    u16 buttons;
    g_Pitcher.pitchCurveVeloV1 = lbl_3_rodata_1258;
    g_Pitcher._60 = lbl_3_rodata_1258;
    dir = 0;
    if (g_Pitcher.cancelParabolicAdjustmentInd == 0 && g_Pitcher.calced_curve != 0) {
        maxCurve = lbl_3_rodata_12B0 *
                   LinearInterpolateToNewRange(g_Pitcher.calced_curve, lbl_3_rodata_1290, lbl_3_rodata_1288, e->curveMin, e->curveMax);
        if (g_Pitcher.AIInd != 0) {
            dir = fn_3_20CEC(maxCurve);
        } else {
            if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
                c = &g_Practice.inputs[g_GameLogic.teamFielding];
            } else {
                MiniGameControlStruct* m = g_Minigame.minigameControlStruct;
                if (fn_3_107DB4(m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]) != 0) {
                    c = &g_Minigame._1D7C[m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
                } else if (g_d_GameSettings.minigamesEnabled != 0) {
                    c = &g_Controls[m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
                }
            }
            buttons = c->buttonInput;
            if (buttons & 1) {
                dir = -1;
            } else if (buttons & 2) {
                dir = 1;
            }
        }
        control = LinearInterpolateToNewRange(g_Pitcher.calced_curveControl, lbl_3_rodata_1290, lbl_3_rodata_1288, lbl_3_data_5E78[0], lbl_3_data_5E78[1]);
        if (control < lbl_3_rodata_1290) {
            control = lbl_3_rodata_1290;
        }
        if (dir == 0) {
            f32 step = maxCurve / control;
            if (g_Pitcher.pitchCurveVeloV2 < lbl_3_rodata_1258) {
                g_Pitcher.pitchCurveVeloV2 = g_Pitcher.pitchCurveVeloV2 + step;
                if (g_Pitcher.pitchCurveVeloV2 > lbl_3_rodata_1258) {
                    g_Pitcher.pitchCurveVeloV2 = lbl_3_rodata_1258;
                }
            } else {
                g_Pitcher.pitchCurveVeloV2 = g_Pitcher.pitchCurveVeloV2 - step;
                if (g_Pitcher.pitchCurveVeloV2 < lbl_3_rodata_1258) {
                    g_Pitcher.pitchCurveVeloV2 = lbl_3_rodata_1258;
                }
            }
        } else {
            g_Pitcher.pitchCurveVeloV2 = g_Pitcher.pitchCurveVeloV2 + (maxCurve * dir) / control;
            if (dir < 0) {
                if (g_Pitcher.pitchCurveVeloV2 < -maxCurve) {
                    g_Pitcher.pitchCurveVeloV2 = -maxCurve;
                }
            } else if (g_Pitcher.pitchCurveVeloV2 > maxCurve) {
                g_Pitcher.pitchCurveVeloV2 = maxCurve;
            }
        }
        g_Pitcher.pitchCurveVeloV1 = g_Pitcher.pitchCurveVeloV2;
        if (dir != 0) {
            g_Pitcher.anyCurveInput = 1;
        }
    }
}

#pragma dont_inline on
// .text:0x00071248 size:0x1520 mapped:0x806B02DC
void fn_3_71248(void) {
    return;
}
#pragma dont_inline reset

// .text:0x00072768 size:0x540 mapped:0x806B17FC
void fn_3_72768(void) {
    return;
}

// .text:0x00072CA8 size:0x464 mapped:0x806B1D3C
// Pitch stat multipliers (lbl_3_data_5F08), only the fields used here.
typedef struct PitchStatMults {
    /*0x00*/ f32 _00[2];
    /*0x08*/ f32 chargeCurve;
    /*0x0C*/ f32 _0C[2];
    /*0x14*/ f32 chargeCurveControl;
    /*0x18*/ f32 _18[2];
    /*0x20*/ f32 chargeCursedBall;
    /*0x24*/ f32 changeUpSpeed;
    /*0x28*/ f32 fastBallSpeed;
} PitchStatMults;
extern PitchStatMults lbl_3_data_5F08;
// Low-stamina pitch penalties (lbl_3_data_5EDC), only the fields used here.
typedef struct PitchStaminaPenalty {
    /*0x00*/ u8 _00[6];
    /*0x06*/ s16 threshold;
    /*0x08*/ s16 _08;
    /*0x0A*/ s16 curvePct;
    /*0x0C*/ s16 speedPct;
    /*0x0E*/ s16 curveControlPct;
    /*0x10*/ s16 cursedBallPct;
} PitchStaminaPenalty;
extern PitchStaminaPenalty lbl_3_data_5EDC;
extern s32 fn_3_6D564(s32 team, s32 idx, s32 delta);
// Compute the pitch speed and the effective curse/curve-control/curve stats.
// NONMATCHING 99%: register allocation only (r0/r4 in the star branch, r6/r7 + f0/f1 in the change-up, f2-f4 for the
// stamina-penalty constants)
#if NONMATCHING
void fn_3_72CA8(void) {
    f32 cursed = g_Pitcher.cursedBallStat;
    f32 control = g_Pitcher.curveControlStat;
    f32 curve = g_Pitcher.curveStat;
    if (g_Pitcher.starPitchType != 0) {
        g_Pitcher.calced_cursedBall = 100;
        g_Pitcher.calced_curveControl = 100;
        g_Pitcher.calced_curve = 100;
        g_Pitcher.pitchSpeed = lbl_3_data_5D6C[g_Pitcher.specialPitchTypeCode].speed;
        if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 0xA) {
            g_Pitcher.pitchSpeed = RandomInt_Game_Range(lbl_3_data_5F7C.speedMin, lbl_3_data_5F7C.speedMax);
        }
        return;
    }
    if (g_Pitcher.ChargePitchType == 3 || g_Pitcher.nonCaptainStarPitchTriggeredType == 2) {
        g_Pitcher.pitchSpeed = g_Pitcher.fastBallSpeed * lbl_3_data_5F08.fastBallSpeed;
    } else if (g_Pitcher.ChargePitchType != 0) {
        if (g_Pitcher.ChargePitchType == 1) {
            g_Pitcher.ChargePitchType = 2;
        }
        g_Pitcher.pitchSpeed = g_Pitcher.fastBallSpeed -
                               (s32)(lbl_3_data_5F08.changeUpSpeed * ((f32)g_Pitcher.fastBallSpeed - (f32)g_Pitcher.curveBallSpeed) *
                                     (lbl_3_rodata_1290 - g_Pitcher.pitchChargeUp));
    } else if (g_Pitcher.TypeOfPitch == 2) {
        g_Pitcher.pitchSpeed = g_Pitcher.curveBallSpeed;
    } else {
        g_Pitcher.pitchSpeed = g_Pitcher.curveBallSpeed;
    }
    if (g_Pitcher.ChargePitchType >= 2 || g_Pitcher.TypeOfPitch == 2 || g_Pitcher.nonCaptainStarPitchTriggeredType == 2 ||
        g_Pitcher.nonCaptainStarPitchTriggeredType == 3) {
        cursed *= lbl_3_data_5F08.chargeCursedBall;
        control *= lbl_3_data_5F08.chargeCurveControl;
        curve *= lbl_3_data_5F08.chargeCurve;
    }
    if (g_Pitcher.nonCaptainStarPitchTriggeredType == 0 &&
        fn_3_6D564(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) < lbl_3_data_5EDC.threshold) {
        if (g_Pitcher.ChargePitchType != 0) {
            g_Pitcher.pitchSpeed = g_Pitcher.pitchSpeed * (lbl_3_rodata_1290 - lbl_3_rodata_1254 * lbl_3_data_5EDC.speedPct);
        } else if (g_Pitcher.TypeOfPitch != 2) {
            curve *= lbl_3_rodata_1290 - lbl_3_rodata_1254 * lbl_3_data_5EDC.curvePct;
        }
        control *= lbl_3_rodata_1290 - lbl_3_rodata_1254 * lbl_3_data_5EDC.curveControlPct;
        cursed *= lbl_3_rodata_1290 - lbl_3_rodata_1254 * lbl_3_data_5EDC.cursedBallPct;
    }
    if (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 3) {
        g_Pitcher.pitchSpeed = g_Minigame.minigamePitchSpeedAdjustment;
    }
    g_Pitcher.calced_cursedBall = cursed;
    g_Pitcher.calced_curveControl = control;
    g_Pitcher.calced_curve = curve;
}
#endif

// .text:0x0007310C size:0x49C mapped:0x806B21A0
void fn_3_7310C(void) {
    return;
}

// Force/advance runners after a walk (3) or other non-hit at-bat end. Same code as fn_3_735A8/fn_3_7372C;
// this inlined copy (declared r, i, stop) is what fn_3_738A8 expands, the standalone ones allocate differently.
static inline void advanceRunnersAfterWalk(void) {
    InMemRunnerType* r;
    int i;
    int stop = 0;
    if (g_Pitcher.strikeOutOrWalk == 3) {
        r = &g_Runners[1];
        for (i = 1; i < 4; i++) {
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                if (stop == 0) {
                    r->currentBase = i;
                    fn_3_89864(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                stop = 1;
            }
            r++;
        }
    } else {
        r = &g_Runners[1];
        for (i = 1; i < 4; i++) {
            if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 5) {
                break;
            }
            if (i == r->currentBase) {
                fn_3_89864(i, 1);
            }
            r++;
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x000735A8 size:0x124 mapped:0x806B263C
void fn_3_735A8(void) {
    int i;
    InMemRunnerType* r;
    int stop = 0;
    if (g_Pitcher.strikeOutOrWalk == 3) {
        r = &g_Runners[1];
        for (i = 1; i < 4; i++) {
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                if (stop == 0) {
                    r->currentBase = i;
                    fn_3_89864(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                stop = 1;
            }
            r++;
        }
    } else {
        r = &g_Runners[1];
        for (i = 1; i < 4; i++) {
            if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 5) {
                break;
            }
            if (i == r->currentBase) {
                fn_3_89864(i, 1);
            }
            r++;
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x000736CC size:0x4C mapped:0x806B2760
void fn_3_736CC(void) {
    int i;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.runnerIndexForEachOutThisPitch[i] == -1) {
            g_Strikes.runnerIndexForEachOutThisPitch[i] = 0;
            return;
        }
    }
}

// .text:0x00073718 size:0x14 mapped:0x806B27AC

void fn_3_73718(void) {
    g_Ball.postPitchResultCounter = -1;
}

// .text:0x0007372C size:0x124 mapped:0x806B27C0
void fn_3_7372C(void) {
    int i;
    InMemRunnerType* r;
    int stop = 0;
    if (g_Pitcher.strikeOutOrWalk == 3) {
        r = &g_Runners[1];
        for (i = 1; i < 4; i++) {
            if (r->runnerOnFieldOrOutOrScored == 1 || r->runnerOnFieldOrOutOrScored == 5) {
                if (stop == 0) {
                    r->currentBase = i;
                    fn_3_89864(i, 1);
                } else {
                    r->currentBase = r->startingBase_baseAchieved;
                    r->nextBase = (r->currentBase + 1) & 3;
                }
            } else {
                stop = 1;
            }
            r++;
        }
    } else {
        r = &g_Runners[1];
        for (i = 1; i < 4; i++) {
            if (r->runnerOnFieldOrOutOrScored != 1 && r->runnerOnFieldOrOutOrScored != 5) {
                break;
            }
            if (i == r->currentBase) {
                fn_3_89864(i, 1);
            }
            r++;
        }
    }
    g_Runners[0].currentBase = 1;
    g_Runners[0].nextBase = 2;
}

// .text:0x00073850 size:0x58 mapped:0x806B28E4
void fn_3_73850(void) {
    int i;
    g_Strikes.outs = g_Strikes.outs + 1;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.runnerIndexForEachOutThisPitch[i] == -1) {
            g_Strikes.runnerIndexForEachOutThisPitch[i] = 0;
            return;
        }
    }
}

// .text:0x000738A8 size:0x540 mapped:0x806B293C
// lbl_3_common_bss_37400, only the fields used here.
typedef struct Rep1200Bss37400View {
    /*0x00*/ u8 _00[0x42];
    /*0x42*/ s16 _42; // countdown
    /*0x44*/ u8 _44[2];
    /*0x46*/ u8 _46;
    /*0x47*/ u8 _47;
    /*0x48*/ u8 _48;
} Rep1200Bss37400View;
extern Rep1200Bss37400View lbl_3_common_bss_37400;
// lbl_3_common_bss_32220, only the fields used here.
typedef struct Rep1200Bss32220View {
    /*0x00*/ u8 _00[6];
    /*0x06*/ s16 _06;
} Rep1200Bss32220View;
extern Rep1200Bss32220View lbl_3_common_bss_32220;
extern void fn_3_164A74(void);
extern void changeScene(s32 scene, s32 state);
extern void fn_3_7BC20(void);
extern void fn_3_8C07C(void);
extern s32 fn_3_6F4E8(void);
// Pitcher state 5: the at-bat ended (strikeout / walk / hit by pitch); wait, then hand over.
void fn_3_738A8(void) {
    s32 frames = 0x78;
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter += 1;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Pitcher.framesSinceAtBatEnded < 0x7FFE) {
        g_Pitcher.framesSinceAtBatEnded += 1;
    } else {
        g_Pitcher.framesSinceAtBatEnded = 0x7FFF;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        return;
    }
    if (g_GameLogic.gameOverInd != 0) {
        frames = 0xC3;
    } else if (g_Batter.hitByPitch != 0) {
        frames = 0x5A;
    } else {
        if (g_Ball.postPitchResultCounter < 0x7FFE) {
            g_Ball.postPitchResultCounter += 1;
        } else {
            g_Ball.postPitchResultCounter = 0x7FFF;
        }
        if (fn_3_6F4E8() != 0) {
            return;
        }
    }
    if (g_Pitcher.framesSinceAtBatEnded == 1) {
        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400._46 != 0 && g_Stats.replayInd == 0) {
            fn_3_164A74();
            lbl_3_common_bss_37400._42 = 0xB4;
        }
        if ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && g_RunningLogic._10 == 4) {
            if (g_Scores._AD != 0) {
                if (g_Scores.inning >= g_Scores.maxInnings && g_Scores.team[0].runs[0] == g_Scores.team[1].runs[0]) {
                    fn_3_59918(0xD, 0);
                    g_GameLogic.gameOverInd = 1;
                } else if (g_Scores._C3[4] != 0) { // run-difference (mercy) limit
                    GameScoresTeam* sc = g_Scores.team;
                    if (sc[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] - sc[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0] + 1 >=
                        g_Scores._C3[4]) {
                        fn_3_59918(0x11, 0);
                        g_GameLogic.gameOverInd = 1;
                    }
                }
            }
            g_Pitcher.walkedInRunInd = 1;
        }
    }
    if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400._46 != 0 && g_Stats.replayInd == 0 &&
        lbl_3_common_bss_37400._48 == 0) {
        if (--lbl_3_common_bss_37400._42 == 0x78) {
            lbl_3_common_bss_32724._B4 = 1;
        }
        frames = 0x78;
    }
    if (g_Pitcher.framesSinceAtBatEnded == 1) {
        if (frames > 0x78) {
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 0x77;
        } else {
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = frames - 1;
        }
    }
    if (g_Pitcher.framesSinceAtBatEnded == frames - 0xB) {
        if (lbl_3_common_bss_32724._B1 == 0) {
            changeScene(3, 6);
        }
    } else if (g_Pitcher.framesSinceAtBatEnded == frames - 0x1F) {
        if (lbl_3_common_bss_32220._06 > 0x1D) {
            g_Pitcher.framesSinceAtBatEnded -= 1;
            return;
        }
        fn_3_7BC20();
        if (g_Stats._39 != 0) {
            lbl_3_common_bss_32724._B1 = 1;
        }
    } else if (g_Pitcher.framesSinceAtBatEnded >= frames) {
        g_GameLogic.hudLoadingRelated = 1;
        g_Ball.postPitchResultCounter = -1;
        g_Pitcher.pitcherActionState = 6;
        g_Pitcher.currentStateFrameCounter = 0;
        if (g_Pitcher.strikeOutOrWalk == 1) {
            fn_3_73850();
        } else if (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) {
            advanceRunnersAfterWalk();
        }
        if (g_Stats._39 != 0) {
            fn_3_8C07C();
        }
    }
}

// .text:0x00073DE8 size:0x144 mapped:0x806B2E7C
extern void fn_3_155288(void);
extern void fn_3_5A6D4(u8 status);
extern void fn_3_7CE90(void);
void fn_3_73DE8(void) {
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter += 1;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Ball.postPitchResultCounter < 0x7FFE) {
        g_Ball.postPitchResultCounter += 1;
    } else {
        g_Ball.postPitchResultCounter = 0x7FFF;
    }
    if (g_d_GameSettings.GameModeSelected == 7 &&
        (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 2 || g_Minigame.GameMode_MiniGame == 3)) {
        g_Pitcher.miniGameRelated = 1;
        if (g_Minigame.GameMode_MiniGame == 1) {
            fn_3_155288();
        }
    } else if (g_Pitcher.miniGameRelated == 0) {
        fn_3_703EC();
        return;
    }
    if (fn_3_6F4E8() == 0) {
        if ((g_d_GameSettings.GameModeSelected != 2 || g_Practice.guidedPracticeCompletionRelated == 0) &&
            g_Pitcher.currentStateFrameCounter > 0x4B) {
            g_GameLogic.playBatterWalkupAnimation = 0;
            fn_3_5A6D4(0);
        }
        fn_3_7CE90();
    }
}

// .text:0x00073F2C size:0x80 mapped:0x806B2FC0
void fn_3_73F2C(void) {
    if (g_Pitcher.pitchTotalTimeCounter < 0x7FFE) {
        g_Pitcher.pitchTotalTimeCounter += 1;
    } else {
        g_Pitcher.pitchTotalTimeCounter = 0x7FFF;
    }
    if (g_Ball.pitchHangtimeCounter < 0x7FFE) {
        g_Ball.pitchHangtimeCounter += 1;
    } else {
        g_Ball.pitchHangtimeCounter = 0x7FFF;
    }
    g_Pitcher.warioWaluStarAnimationStage = 0;
    fn_3_71248();
}

// .text:0x00073FAC size:0x124 mapped:0x806B3040
extern f32 lbl_3_data_5EB0[];
extern f32 lbl_3_data_4474[];
extern f32 lbl_3_data_2138C[];
void fn_3_73FAC(void) {
    g_Pitcher.eggBallBounceYHeight = g_Batter.batPosition2.y;
    g_Pitcher.pitchStartingPosition_AIMaxCurve =
        LinearInterpolateToNewRange(g_Pitcher.pitcher.x, lbl_3_data_4474[0], lbl_3_data_4474[1], lbl_3_data_5EB0[0], lbl_3_data_5EB0[1]);
    if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = lbl_3_rodata_1258;
    } else if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 0xA) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve = RandomF32_Game_Range(-lbl_3_data_5F5C[3], lbl_3_data_5F5C[3]);
        g_Pitcher.eggBallBounceYHeight = lbl_3_data_5F5C[0];
        g_Pitcher.frontOfPlateZ = RandomF32_Game_Range(lbl_3_data_5F5C[1], lbl_3_data_5F5C[2]);
    }
    if (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 3) {
        g_Pitcher.pitchStartingPosition_AIMaxCurve =
            RandomF32_Game_Range(-lbl_3_data_2138C[g_Minigame.soloMinigameDifficulty], lbl_3_data_2138C[g_Minigame.soloMinigameDifficulty]);
    }
}

// .text:0x000740D0 size:0x58 mapped:0x806B3164
void fn_3_740D0(void) {
    u8 v = g_Pitcher.nonCaptainStarPitch;
    g_Pitcher.nonCaptainStarPitchTriggeredType = v;
    switch (v) {
    case 1:
        g_Pitcher.specialPitchTypeCode = 0x10;
        break;
    case 2:
        g_Pitcher.specialPitchTypeCode = 0x11;
        break;
    case 3:
        g_Pitcher.specialPitchTypeCode = 0x12;
        break;
    }
}

// .text:0x00074128 size:0x99C mapped:0x806B31BC
void fn_3_74128(void) {
    return;
}

// .text:0x00074AC4 size:0x248 mapped:0x806B3B58
void fn_3_74AC4(void) {
    s32 i = g_GameLogic.teamFielding;
    InputStruct* c = &g_Controls[g_GameLogic.teams[i]];
    f32 add = lbl_3_rodata_1258;
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        c = &g_Practice.inputs[i];
    } else {
        MiniGameControlStruct* m = g_Minigame.minigameControlStruct;
        if (fn_3_107DB4(m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]) != 0) {
            c = &g_Minigame._1D7C[m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
        } else if (g_d_GameSettings.minigamesEnabled != 0) {
            c = &g_Controls[m->characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
        }
    }
    if (c->buttonInput & 0x40) {
        g_Pitcher.pitcherOffCenter = 1;
    }
    if (g_Pitcher.pitcherOffCenter != 0) {
        if (g_Pitcher.pitcher.x >= -lbl_3_data_4474[3] && g_Pitcher.pitcher.x <= lbl_3_data_4474[3]) {
            g_Pitcher.pitcherOffCenter = 0;
            g_Pitcher.pitcher.x = lbl_3_rodata_1258;
        } else if (g_Pitcher.pitcher.x < lbl_3_rodata_1258) {
            g_Pitcher.pitcher.x += lbl_3_data_4474[3];
        } else {
            g_Pitcher.pitcher.x -= lbl_3_data_4474[3];
        }
        return;
    }
    if (c->buttonInput & 1) {
        add = -lbl_3_data_4474[2];
    } else if (c->buttonInput & 2) {
        add = lbl_3_data_4474[2];
    }
    g_Pitcher.pitcher.x = g_Pitcher.pitcher.x + add;
    if (g_Pitcher.pitcher.x < lbl_3_data_4474[0]) {
        g_Pitcher.pitcher.x = lbl_3_data_4474[0];
    }
    if (g_Pitcher.pitcher.x > lbl_3_data_4474[1]) {
        g_Pitcher.pitcher.x = lbl_3_data_4474[1];
    }
}

// .text:0x00074D0C size:0x384 mapped:0x806B3DA0
// View of lbl_8036E548 (actor manager), only the fields used here.
typedef struct Rep1200ActorMgrView {
    /*0x0000*/ u8 _0000[0x2D46];
    /*0x2D46*/ u8 _2D46;
    /*0x2D47*/ u8 _2D47[0x2D52 - 0x2D47];
    /*0x2D52*/ u8 _2D52;
    /*0x2D53*/ u8 _2D53[0x2D5E - 0x2D53];
    /*0x2D5E*/ u8 _2D5E;
} Rep1200ActorMgrView;
extern Rep1200ActorMgrView lbl_8036E548;
extern void fn_3_1118B4(void);
extern void fn_3_15AD94(void);
extern void fn_3_215AC(void);
// Pitcher state 1 (pre-pitch): waits for the pitch button.
void fn_3_74D0C(void) {
    InputStruct* c = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    s8 idx;
    g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
    if (g_GameLogic.frameCountdownAtBeginningOfAtBatLockout != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
    } else if (g_Batter.beginningOfABAnimationOccuring != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
    } else if (g_UnkSound_32718._07 == 0xC) {
        g_Pitcher.currentStateFrameCounter = 0;
    } else if (g_d_GameSettings.GameModeSelected == 6 && g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd != 0) {
        g_Pitcher.currentStateFrameCounter = 0;
    } else if (lbl_8036E548._2D46 == 0 && lbl_8036E548._2D52 == 0 && lbl_8036E548._2D5E == 0 &&
               (g_d_GameSettings.exhibitionMatchInd != 0 || lbl_3_common_bss_32724._B3 == 0)) {
        if (g_Pitcher.pitchDeliveryAnimationPlaying != 0) {
            g_Pitcher.currentStateFrameCounter = 0;
        } else if ((g_GameLogic.secondaryGameMode != 0xD || g_Practice.hitVariablesSetIndicator != 0) &&
                   (g_GameLogic.secondaryGameMode != 0xE || g_Practice._1EC != 0)) {
            if (g_d_GameSettings.minigamesEnabled != 0) {
                if (g_Minigame.GameMode_MiniGame == 1) {
                    fn_3_1118B4();
                    return;
                }
                if (g_Minigame.GameMode_MiniGame == 3) {
                    fn_3_1118B4();
                    return;
                }
                idx = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
                c = &g_Controls[idx];
                if (fn_3_107DB4(idx) != 0) {
                    c = &g_Minigame._1D7C[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder]];
                }
                if (g_Pitcher.AIInd != 0) {
                    fn_3_215AC();
                    return;
                }
            } else {
                if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceLevel == 4) {
                    fn_3_15AD94();
                    return;
                }
                if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
                    c = &g_Practice.inputs[g_GameLogic.teamFielding];
                }
                if (fn_3_6F748() != 0) {
                    return;
                }
                if (g_Pitcher.AIInd != 0) {
                    fn_3_215AC();
                    return;
                }
            }
            fn_3_74AC4();
            if (c->newButtonInput & 0x100) {
                if (g_d_GameSettings.minigamesEnabled == 0 && (c->buttonInput & 0x20)) {
                    g_Pitcher.starPitchInd = 1;
                }
                if (g_Pitcher.starPitchInd == 0 && (c->buttonInput & 4)) {
                    g_Pitcher.TypeOfPitch = 2;
                } else {
                    g_Pitcher.framesAHeldForChargePitches = 1;
                }
                g_Pitcher.pitcherActionState = 2;
                g_Pitcher.currentStateFrameCounter = 0;
                g_Stats._38 = 1;
            }
        }
    }
}

// .text:0x00075090 size:0x34 mapped:0x806B4124
void fn_3_75090(void) {
    g_Pitcher.pitcherActionState = 1;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Ball.AtBat_Contact_BallPos.x = g_Pitcher.ballCurrentPosition.x;
    g_Ball.AtBat_Contact_BallPos.y = g_Pitcher.ballCurrentPosition.y;
    g_Ball.AtBat_Contact_BallPos.z = g_Pitcher.ballCurrentPosition.z;
}

// .text:0x000750C4 size:0x18 mapped:0x806B4158

void fn_3_750C4(u8 v) {
    g_Pitcher.pitcherActionState = v;
    g_Pitcher.currentStateFrameCounter = 0;
}

// .text:0x000750DC size:0xD8 mapped:0x806B4170
int fn_3_750DC(void) {
    s32 id = inMemRoster[g_GameLogic.teamFielding][g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]].stats.CharID;
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceType_2 != 4) {
        id = g_Pitcher.charID;
    }
    if (lbl_3_common_bss_32724._9C == 0) {
        lbl_803CBC3C._01 = 0;
        lbl_3_common_bss_32724._9C = 1;
    }
    if (lbl_3_common_bss_32724._9C == 1 && fn_8001C920(id)) {
        return 1;
    }
    return 0;
}

// .text:0x000751B4 size:0x234 mapped:0x806B4248
extern f32 lbl_3_data_450C[];
extern s16 lbl_3_data_8080[];
// NONMATCHING 77%: same instructions, different f-reg allocation and scheduling of the strike-zone loads (orig reads
// lbl_3_rodata_1250/1290 through addi+lfs 0, a..d in f9..f12)
#if NONMATCHING
void fn_3_751B4(void) {
    f32 h;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 cx;
    f32 cz;
    g_Pitcher.pitcherActionState = 0;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Ball.fielderWBallIndex = 0;
    g_Pitcher.pitchSpeedScaler = lbl_3_data_5F90[0];
    g_Pitcher.decelerationFactor = lbl_3_data_5F90[1];
    h = lbl_3_rodata_1250;
    a = lbl_3_data_5E98[0];
    b = lbl_3_data_5E98[1];
    c = lbl_3_data_5E98[2];
    d = lbl_3_data_5E98[3];
    cx = h * (a + b);
    cz = h * (c + d);
    g_Pitcher.centerOfStrikeZone.x = cx;
    g_Pitcher.centerOfStrikeZone.z = cz;
    g_Pitcher.strikeZoneLeft = a;
    g_Pitcher.strikeZoneRight = b;
    g_Pitcher.beginningOfStrikeCheckZ = c;
    g_Pitcher.endingOfStrikeCheckZ = d;
    g_Pitcher.ballCurrentPosition.x = lbl_3_data_450C[0];
    g_Pitcher.ballCurrentPosition.y = lbl_3_rodata_1290;
    g_Pitcher.ballCurrentPosition.z = lbl_3_data_450C[1];
    g_Pitcher.ballVelocity.x = lbl_3_rodata_1258;
    g_Pitcher.ballVelocity.y = lbl_3_rodata_1258;
    g_Pitcher.ballVelocity.z = lbl_3_rodata_1258;
    g_Pitcher.pitchStartingPosition_AIMaxCurve = cx;
    g_Pitcher.eggBallBounceYHeight = lbl_3_data_5E98[4];
    g_Pitcher.frontOfPlateZ = cz;
    g_Pitcher.pitchTotalTimeCounter = 0;
    g_Pitcher.strikeZoneProcessNumber = 0;
    g_Pitcher.frameBallCanStartBeingControlled = 0;
    g_Pitcher.pitchInAirInd = 0;
    g_Pitcher.calledStrikeInd = 0;
    g_Pitcher.strikeInd = 0;
    g_Pitcher.miniGameRelated = 0;
    g_Pitcher.pickOffLoc = -1;
    g_Pitcher.pitchDidntResultInLiveBallInd = 0;
    g_Pitcher.strikeOutOrWalk = 0;
    g_Pitcher.framesUntilPitchGetsToBatter = -1;
    g_Pitcher.pitchChargeUp = lbl_3_rodata_1258;
    g_Pitcher.pitchChargeUpAnimationProportion = lbl_3_rodata_1258;
    g_Pitcher.unknownFrameCounter = 0;
    g_Pitcher.ChargePitchType = 0;
    g_Pitcher.framesAHeldForChargePitches = 0;
    g_Pitcher.TypeOfPitch = 0;
    g_Pitcher.ballHaloTrainInd_unused = 0;
    g_Pitcher.overChargeInd = 0;
    g_Pitcher.starPitchInd = 0;
    g_Pitcher.starPitchType = 0;
    g_Pitcher.warioWaluStarAnimationStage = 0;
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_8080[0];
    g_Pitcher.warioWaluStarHasPlayedSound = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    g_Pitcher.peachDaisyAnimationHappened = 0;
    g_Pitcher.anyCurveInput = 0;
    g_Pitcher.bulletPitchFrameCounter = 0;
    g_Pitcher.bulletPitchStageCode = 0;
    g_Pitcher.eggBallBounceNumber = 0;
    g_Pitcher.framesSinceFirstEggBounce = 0;
    g_Pitcher.pitcherOffCenter = 0;
    g_Pitcher.nonCaptainStarPitchTriggeredType = 0;
    g_Pitcher.walkedInRunInd = 0;
    g_Pitcher.unused_pitcherIsFielder = 0;
    g_Pitcher.starPitchPositionAdjustment.x = lbl_3_rodata_1258;
    g_Pitcher.starPitchPositionAdjustment.y = lbl_3_rodata_1258;
    g_Pitcher.starPitchPositionAdjustment.z = lbl_3_rodata_1258;
    g_Pitcher.pitchWindUpCountDown = lbl_3_data_8080[1];
    g_Pitcher.curvePitchWindupFrames = lbl_3_data_8080[2];
    g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_8080[1];
    if (g_d_GameSettings.GameModeSelected == 2) {
        g_Pitcher.AIInd = g_Practice.aIEnabled;
    } else if (g_Minigame.GameMode_MiniGame == 1 || g_Minigame.GameMode_MiniGame == 3) {
        g_Pitcher.AIInd = 1;
    } else if (g_d_GameSettings.minigamesEnabled != 0) {
        g_Pitcher.AIInd = g_Minigame.minigameControlStruct[0].battingHandedness[g_Minigame.minigamePlayerSelectedOrder];
    } else {
        g_Pitcher.AIInd = g_GameLogic._140[g_GameLogic.awayTeamBattingInd_battingTeam];
    }
    lbl_3_common_bss_34C58._34 = 0;
}
#endif

// .text:0x000753E8 size:0x4C mapped:0x806B447C
void fn_3_753E8(int a) {
    g_Pitcher.pitcherActionState = 0;
    g_Pitcher.currentStateFrameCounter = 0;
    if (a == 0) {
        g_Pitcher.nPitchesThisAB = 0;
        g_Pitcher.nPickoffAttempts = 0;
    }
    g_Pitcher.pitcher.x = lbl_3_data_446C[0];
    g_Pitcher.pitcher.z = lbl_3_data_446C[1];
    g_Pitcher.pitchDeliveryAnimationPlaying = 0;
}

// .text:0x00075434 size:0x84 mapped:0x806B44C8
void fn_3_75434(void) {
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_Pitcher.pitcherActionState = 0;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Pitcher.nPitchesThisAB = 0;
    g_Pitcher.nPickoffAttempts = 0;
    g_Pitcher.pitcher.x = lbl_3_data_446C[0];
    g_Pitcher.pitcher.z = lbl_3_data_446C[1];
    g_Pitcher.pitchDeliveryAnimationPlaying = 0;
    if (g_Scores.inning == 1) {
        g_Pitcher.playStartOfGameAnimation = 1;
    }
}

// .text:0x000754B8 size:0xA8 mapped:0x806B454C
void fn_3_754B8(void) {
    f32 h;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    g_Pitcher.pitcherActionState = 0;
    g_Pitcher.currentStateFrameCounter = 0;
    g_Pitcher.pitchSpeedScaler = lbl_3_data_5F90[0];
    g_Pitcher.decelerationFactor = lbl_3_data_5F90[1];
    h = lbl_3_rodata_1250;
    a = lbl_3_data_5E98[0];
    b = lbl_3_data_5E98[1];
    c = lbl_3_data_5E98[2];
    d = lbl_3_data_5E98[3];
    {
        VecXZ* cz = &g_Pitcher.centerOfStrikeZone;
        cz->x = h * (a + b);
        cz->z = h * (c + d);
    }
    g_Pitcher.strikeZoneLeft = a;
    g_Pitcher.strikeZoneRight = b;
    g_Pitcher.beginningOfStrikeCheckZ = c;
    g_Pitcher.endingOfStrikeCheckZ = d;
    g_Pitcher.pitcher.x = lbl_3_data_446C[0];
    g_Pitcher.pitcher.z = lbl_3_data_446C[1];
    g_Pitcher.windupCountdownUntilBallReleased = 100;
    g_Pitcher.pitchWindUpCountDown = 100;
    g_Pitcher.curvePitchWindupFrames = 100;
    g_Pitcher.playStartOfGameAnimation = 1;
}

// .text:0x00075560 size:0x45C mapped:0x806B45F4
extern void fn_3_A83C(void);
// Pitcher per-frame update: dispatch on the action state.
void fn_3_75560(void) {
    if (fn_3_107DB4(g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder]) != 0) {
        g_Pitcher.AIInd = 0;
    }
    if (g_Pitcher.currentStateFrameCounter < 0x7FFE) {
        g_Pitcher.currentStateFrameCounter += 1;
    } else {
        g_Pitcher.currentStateFrameCounter = 0x7FFF;
    }
    fn_3_A83C();
    switch (g_Pitcher.pitcherActionState) {
    case 0:
        fn_3_75090();
        break;
    case 1:
        fn_3_74D0C();
        break;
    case 2:
        fn_3_74128();
        break;
    case 3:
        fn_3_73F2C();
        break;
    case 4:
        fn_3_73DE8();
        break;
    case 5:
        fn_3_738A8();
        break;
    case 6:
        fn_3_73718();
        break;
    case 7:
        fn_3_6FB98();
        break;
    }
}
