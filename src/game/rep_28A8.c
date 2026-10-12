#include "game/rep_28A8.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_0009CD90_text.h"
#include "static/GameSettings.h"
#include "main/file_8001FE00.h"
#include "main/file_80011640.h"
#define REP_HEADER_FN repHeader_28A8
#include "header_rep_inline.h"
#include "musyx/musyx.h"
#include "math.h"
#include "main/file_80021308.h"
#include "game/auto_00_00097144_text.h"
extern SoundManager lbl_800EF808;

extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_58870(void);
extern void fn_3_1DEB8(void);
extern void fn_3_BF1AC(void);
extern void Set_803cb848(s32);
extern void fn_3_BF158(void);
extern void fn_3_AFD80(u8 state);
extern void fn_3_5A6D4(s32);
extern void fn_3_2EA24(void);
extern void fn_3_2E87C(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_1DD48(void);
extern void fn_3_75560(void);
extern void atBat_batter(void);
extern void fn_3_DF8D4(void);
extern void fn_3_15F998(void);
extern void fn_3_147DFC(void);
extern void fn_3_11CF84(void);
extern u8 lbl_803CBC3C;
extern u8 lbl_3_data_189AC[];
extern int fn_3_B7E10(f32, f32);
extern s16 lbl_3_data_18C48[];
extern int random_fn_3_9EE24(int);
extern s16 lbl_3_data_1899C[];
extern void changeScene(s32, s32);
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_5B408(void);
extern u8 lbl_800EFBA4[];
extern void fn_3_107E80(void);
extern s32 fn_3_5B380(u16 buttons);
extern void fn_8004CC18(void);
typedef struct { f32 a, b, c, d; } T18AC8;
extern T18AC8 lbl_3_data_18AC8[];
extern const f32 lbl_3_rodata_28FC;
extern const f32 lbl_3_rodata_2918;
extern const f32 lbl_3_rodata_291C;
extern const f32 lbl_3_rodata_2920;
extern const f32 lbl_3_rodata_2924;
extern const f32 lbl_3_rodata_2928;
extern const f32 lbl_3_rodata_292C;
extern int rand(void);
extern f32 RandomF32_Game_Range(f32, f32);
extern void getComponentsFromSAng(s16, f32*, f32*);
extern s32 fn_3_9FE6C_normalizeAngle(s16);
extern s32 fn_3_E5924(void);
extern void fn_3_59918(s32, s32);
extern void fn_3_A0F0(void);

extern void ballPhysica(void);
extern void fn_3_D8CD0(void);
extern void fn_3_D9868(void);
extern void fn_3_D9A30(void);
extern s32 fn_3_E8AC8(void);
void fn_3_DE308(s32 idx);
extern s16 lbl_3_data_49DC[];
extern void fn_3_2F484(void);
extern u16 lbl_3_data_81DC[]; // per stadium: crowd sound id base
typedef struct { u8 vol; u8 ctrl; } CrowdSnd;
extern CrowdSnd lbl_3_data_8404[]; // [stadium * 15 + sound]
extern CrowdSnd lbl_3_data_84B8[]; // [sound], GameModeSelected 6

// Same helper as in auto_00_000D8A10_text.c.
static inline void playCrowdSound(s32 n) {
    s32 stadium;
    u8 vol;
    SND_VOICEID voice;

    stadium = g_d_GameSettings.StadiumID; // StadiumID
    if (g_d_GameSettings.GameModeSelected == 6) { // GameModeSelected
        vol = lbl_3_data_84B8[n].vol;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].vol;
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + n, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].ctrl;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].ctrl;
    }
    sndFXCtrl(voice, 0x5B, vol);
}


// lbl_3_data_18AC8: per-level coin spawn areas, then catch radii and coin physics.
typedef struct {
    /* 0x00 */ T18AC8 areas[12];
    /* 0xC0 */ f32 catchRadius[5]; // by fielder size class (g_Fielders + 0x1C9)
    /* 0xD4 */ f32 gravity;
    /* 0xD8 */ f32 drag;
    /* 0xDC */ f32 bounce;
    /* 0xE0 */ f32 floorY;
} WallBallData;

extern s16 lbl_3_data_18BB0[]; // [level * 2]: coin lifetime in frames
extern u8 lbl_3_data_88DC;

static inline f32 coinDistToFielder(MiniGameStruct* mg, s32 i, s32 slot) {
    InMemFielderType* f = &g_Fielders[mg->minigameFielderIndex[slot]];
    f32 dx = mg->wallBall_coinCoordinates[i].x - f->pos.x;
    f32 dz = mg->wallBall_coinCoordinates[i].z - f->pos.z;
    f32 sx = dx * dx;
    f32 sz = dz * dz;
    return dolsqrtf2(sx + sz);
}

// NONMATCHING 83%: original reaches 18AC8/18BB0/18C48 via the pooled base lbl_3_data_188E8 and re-materialises g_Minigame bases (lbz/extsb/add vs our lbzx)
// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
#pragma pool_data off // each float constant is its own .rodata symbol in the original
#if NONMATCHING
void fn_3_D9EA0(void) {
    MiniGameStruct* mg = &g_Minigame;
    WallBallData* wb = (WallBallData*)lbl_3_data_18AC8;
    s32 i;

    if (mg->_1939 == 0) {
        return;
    }
    if (mg->wallBall_coinsVisibleFrameCounter < 0x7FFE) {
        mg->wallBall_coinsVisibleFrameCounter++;
    } else {
        mg->wallBall_coinsVisibleFrameCounter = 0x7FFF;
    }
    for (i = 0; i < 100; i++) {
        if (mg->wallBall_coinsVisibleInd[i] != 0) {
            if (mg->wallBall_coinsVisibleFrameCounter > lbl_3_data_18BB0[mg->_199E * 2]) {
                mg->wallBall_coinsVisibleInd[i] = 0;
            } else {
                mg->wallBall_coinVelocity[i].y -= wb->gravity;
                mg->wallBall_coinVelocity[i].x *= wb->drag;
                mg->wallBall_coinVelocity[i].y *= wb->drag;
                mg->wallBall_coinVelocity[i].z *= wb->drag;
                mg->wallBall_coinCoordinates[i].x += mg->wallBall_coinVelocity[i].x;
                mg->wallBall_coinCoordinates[i].y += mg->wallBall_coinVelocity[i].y;
                mg->wallBall_coinCoordinates[i].z += mg->wallBall_coinVelocity[i].z;
                if (mg->wallBall_coinCoordinates[i].y <= wb->floorY) {
                    mg->wallBall_coinCoordinates[i].y = wb->floorY;
                    mg->wallBall_coinVelocity[i].y = -mg->wallBall_coinVelocity[i].y;
                    mg->wallBall_coinVelocity[i].x *= wb->bounce;
                    mg->wallBall_coinVelocity[i].y *= wb->bounce;
                    mg->wallBall_coinVelocity[i].z *= wb->bounce;
                }
            }
        }
    }
    for (i = 0; i < 100; i++) {
        if (mg->wallBall_coinsVisibleInd[i] != 0) {
            f32 d0;
            f32 d1 = 999.9f;
            f32 d2 = 999.9f;
            s8 who;

            d0 = coinDistToFielder(mg, i, mg->minigameControlStruct[0].fieldOrder[0]);
            if (mg->minigameControlStruct[0].fieldOrder[1] >= 0) {
                d1 = coinDistToFielder(mg, i, mg->minigameControlStruct[0].fieldOrder[1]);
            }
            if (mg->minigameControlStruct[0].fieldOrder[2] >= 0) {
                d2 = coinDistToFielder(mg, i, mg->minigameControlStruct[0].fieldOrder[2]);
            }
            if (d0 < d2 && d0 < d1) {
                d1 = d0;
                who = mg->minigameControlStruct[0].fieldOrder[0];
            } else if (d1 < d2) {
                who = mg->minigameControlStruct[0].fieldOrder[1];
            } else {
                d1 = d2;
                who = mg->minigameControlStruct[0].fieldOrder[2];
            }
            if (d1 < wb->catchRadius[g_Fielders[mg->minigameFielderIndex[who]].weight]) {
                mg->wallBall_coinsVisibleInd[i] = 0;
                mg->miniGameCurrentPoints[who] += lbl_3_data_18C48[8] * mg->toyField_pointMultiplier;
                if (--mg->_1939 == 0 && mg->turnOverStatus == 0) {
                    mg->turnOverStatus = 1;
                }
                if (lbl_3_common_bss_34C58._30 == 0) {
                    playCrowdSound(0xC);
                    lbl_3_common_bss_34C58._30 = lbl_3_data_88DC;
                }
            }
        }
    }
    if (mg->wallBall_coinsVisibleFrameCounter > lbl_3_data_18BB0[mg->_199E * 2]) {
        if (mg->turnOverStatus == 0) {
            mg->turnOverStatus = 1;
        }
        if (mg->_1939 != 0) {
            mg->miniGameLatestPoints[mg->rosterID] = mg->_1939 * mg->toyField_pointMultiplier;
            mg->minigamePoints_current_Latest[mg->rosterID].current = mg->miniGameCurrentPoints[mg->rosterID];
            mg->minigamePoints_current_Latest[mg->rosterID].latest = mg->miniGameLatestPoints[mg->rosterID];
            mg->_1939 = 0;
        }
    }
}
#endif
#pragma pool_data reset

// NONMATCHING 99%: only GPR order of loop invariants differs (orig range=r29, t=r27; ours swapped); decl orders tried
// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
#if NONMATCHING
void fn_3_DA640(s32 n, s32 idx) {
    f32 maxr;
    f32 sx, sy;
    f32 r, rv;
    f32* t;
    f32* ty;
    s32 range;
    s32 i;
    g_Minigame._1939 = n;
    g_Minigame.panelHitInd = 1;
    g_Minigame.wallBall_coinsVisibleFrameCounter = 0;
    maxr = lbl_3_data_18AC8[idx].c;
    if (n >= 0x14) {
        maxr = lbl_3_data_18AC8[idx].d;
    }
    range = (s32)(lbl_3_rodata_2918 * maxr);
    t = &lbl_3_data_18AC8[idx].a;
    ty = &lbl_3_data_18AC8[idx].b;
    for (i = 0; i < n; i++) {
        s16 ang;
        g_Minigame.wallBall_coinsVisibleInd[i] = 1;
        g_Minigame.wallBall_coinCoordinates[i].y = lbl_3_rodata_291C;
        { s32 q = rand() % range; r = lbl_3_rodata_2920 * (f32)q; }
        { s32 q2 = rand() % 0x1000; ang = fn_3_9FE6C_normalizeAngle(q2); }
        getComponentsFromSAng(ang, &sx, &sy);
        g_Minigame.wallBall_coinCoordinates[i].x = sx * r + *t;
        g_Minigame.wallBall_coinCoordinates[i].z = sy * r + *ty;
        rv = RandomF32_Game_Range(lbl_3_rodata_28FC, lbl_3_rodata_2924);
        g_Minigame.wallBall_coinVelocity[i].x = sx * rv;
        g_Minigame.wallBall_coinVelocity[i].z = sy * rv;
        g_Minigame.wallBall_coinVelocity[i].y = RandomF32_Game_Range(lbl_3_rodata_2928, lbl_3_rodata_292C);
    }
}
#endif

// NONMATCHING 86%: original reaches 18BB8/189AC via the pooled base lbl_3_data_188E8; register allocation differs in the inlined fn_3_DE308/fn_3_DA640 copies
// .text:0x000DA834 size:0x1A0C mapped:0x807198C8
// Toy Field: per-frame handling of a ball result (g_Minigame + 0x1920).
#if NONMATCHING
void fn_3_DA834(void) {
    u8* bases = &g_Minigame._1914[0]; // [0] batter, [1..3] runners on 1st..3rd
    s8* order = (s8*)(&g_Minigame._191C[0]);
    s32 i;
    s32 j;

    if (g_Minigame.framesSincePanelHit < 0x7FFE) {
        g_Minigame.framesSincePanelHit += 1;
    } else {
        g_Minigame.framesSincePanelHit = 0x7FFF;
    }
    if (g_Minigame.framesSincePanelHit <= 1) {
        if (g_Minigame.toyFieldBallStateResult2 == 1 && g_Ball.maybebuntOn2Strikes == 0) {
            g_Minigame.turnOverStatus = 1;
            fn_3_DE308(11);
            return;
        }
        g_Minigame.panelHitInd = 1;
        if (g_Minigame.toyFieldBallStateResult2 >= 1 && g_Minigame.toyFieldBallStateResult2 <= 8) {
            g_Minigame.turnOverStatus = 1;
            switch (g_Minigame.toyFieldBallStateResult2) {
            case 1:
                fn_3_DE308(22);
                break;
            case 2:
                if (g_Pitcher.strikeOutOrWalk == 1 || g_Ball.maybebuntOn2Strikes != 0) {
                    fn_3_DE308(22);
                } else if (g_Minigame.toyFieldStateInd_collisionRelated == 0x71) {
                    fn_3_DE308(9);
                } else {
                    fn_3_DE308(10);
                }
                break;
            case 3:
                fn_3_DE308(0);
                break;
            case 4:
                fn_3_DE308(1);
                break;
            case 5:
                fn_3_DE308(2);
                break;
            case 6:
                if (g_Ball.deadBallReason == 1) {
                    fn_3_DE308(4);
                } else {
                    fn_3_DE308(3);
                }
                break;
            case 7:
                fn_3_DE308(23);
                break;
            case 8:
                fn_3_DE308(23);
                break;
            }
            if (g_Minigame.toyFieldBallStateResult2 >= 3 && g_Minigame.toyFieldBallStateResult2 <= 6) {
                playCrowdSound(0);
            }
            if (g_Minigame.toyFieldBallStateResult2 == 2 || g_Ball.maybebuntOn2Strikes != 0) {
                if (g_Ball.fielderWBallIndex >= 0) {
                    g_Minigame._19C6 = g_Fielders[g_Ball.fielderWBallIndex].minigamePlayer;
                } else {
                    g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
                }
            }
        } else {
            switch (g_Minigame.toyFieldBallStateResult2) {
            case 11:
                fn_3_D9A30();
                fn_3_D9868();
                g_Minigame.TF_framesSinceHittingPanel = 1;
                break;
            case 9:
            case 10:
                if (g_Minigame.lastKnownBallPosX < 0.0f) {
                    fn_3_DA640(30, 6);
                } else {
                    fn_3_DA640(30, 4);
                }
                g_Minigame.TF_framesSinceHittingPanel = 1;
                g_Minigame._199E = 0;
                break;
            default:
                g_Minigame.turnOverStatus = 1;
                break;
            }
        }
        if (g_Minigame.toyFieldBallStateResult2 >= 3 && g_Minigame.toyFieldBallStateResult2 <= 6) {
            // hit: every runner advances (1920 - 2) bases
            s32 n = g_Minigame.toyFieldBallStateResult2 - 2;
            for (i = 0; i < n; i++) {
                if (bases[3] != 0) {
                    g_Minigame._1921++;
                }
                for (j = 3; j > 0; j--) {
                    bases[j] = bases[j - 1];
                    bases[j - 1] = 0;
                }
            }
            for (i = 0; i < 4; i++) {
                if (order[i] >= 0) {
                    order[i] += n;
                    if (order[i] >= 4) {
                        order[i] = 4;
                    }
                }
            }
        }
        if (g_Minigame.toyFieldBallStateResult2 == 7 || g_Minigame.toyFieldBallStateResult2 == 8) {
            // walk: only forced runners advance
            s32 n;
            if (bases[3] != 0) {
                g_Minigame._1921++;
            }
            n = 1;
            if (bases[1] != 0) {
                n = 2;
                if (bases[2] != 0) {
                    n = 3;
                    if (bases[3] != 0) {
                        n = 4;
                    }
                }
            }
            for (j = n; j >= 1; j--) {
                bases[j] = bases[j - 1];
                bases[j - 1] = 0;
            }
            for (i = 0; i < 4; i++) {
                if (order[i] < 0) {
                    break;
                }
                order[i] += 1;
                if (order[i] >= 4) {
                    order[i] = 4;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (g_Ball.fielderWBallIndex >= 0 && g_Minigame.minigameFielderIndex[i] == g_Ball.fielderWBallIndex) {
                if (g_Ball.AtBat_ContactResult == 3) {
                    fn_3_DE308(0x14);
                } else {
                    fn_3_DE308(0x15);
                }
                break;
            }
        }
        g_Minigame.pointsTargetReachedInd = 1;
    } else {
        if (g_Minigame.toyFieldBallStateResult2 == 0xB) {
            switch (g_Minigame._1934) {
            case 1:
                break;
            case 0: {
                // slot machine reels: 0 spinning, 1 stopping, 2 stopped
                s16* tbl = (s16*)(lbl_3_data_189AC + 0xC);
                s16 firstStop = tbl[3];
                if (g_Minigame._18B8 < 0x7FFE) {
                    g_Minigame._18B8 += 1;
                } else {
                    g_Minigame._18B8 = 0x7FFF;
                }
                for (i = 0; i < 3; i++) {
                    u8 st = g_Minigame.reelStop[i];
                    if (st == 0) {
                        if (g_Minigame._18B8 > tbl[i * 2]) {
                            g_Minigame.reelStop[i] = 1;
                        }
                    } else if (st == 1) {
                        if (i == 0) {
                            if (g_Minigame._18B8 > firstStop) {
                                g_Minigame.reelStop[i] = 2;
                            }
                        } else if (i == 2) {
                            if (g_Minigame.reelSymbol[i + 2] == 3) {
                                g_Minigame.reelStop[i] = 2;
                            }
                        } else if (g_Minigame.reelSymbol[i + 2] >= 2) {
                            g_Minigame.reelStop[i] = 2;
                        }
                    }
                }
                break;
            }
            case 2:
                fn_3_D8CD0();
                g_Minigame._1934 = 3;
                break;
            default:
                if (g_Minigame._192D == 6) {
                    g_Minigame._19A6 = 3;
                    if (g_Minigame._18BA == 1) {
                        fn_3_E8AC8();
                    }
                }
                if (g_Minigame._18BA < 0x7FFE) {
                    g_Minigame._18BA += 1;
                } else {
                    g_Minigame._18BA = 0x7FFF;
                }
                break;
            }
        }
        if (g_Minigame.toyFieldBallStateResult2 == 9 || g_Minigame.toyFieldBallStateResult2 == 0xA) {
            fn_3_D9EA0();
        }
    }
}
#endif

// .text:0x000DC240 size:0x140 mapped:0x8071B2D4
void fn_3_DC240(void) {
    g_Minigame.toyFieldBallStateResult2 = g_Minigame.toyFieldBallStateResult;
    if (fn_3_E5924() != 0) {
        if (g_Minigame._19CF == 0) {
            g_Minigame.toyFieldBallStateResult2 = 0xC;
        }
        if (g_Minigame._19CF > 0x3C) {
            g_Minigame._19CE = 1;
            return;
        }
        if (g_Minigame._19CF < 0xFE) {
            g_Minigame._19CF = g_Minigame._19CF + 1;
            return;
        }
        g_Minigame._19CF = 0xFF;
        return;
    }
    if (g_Minigame.toyFieldBallStateResult2 == 2 || g_Ball.maybebuntOn2Strikes != 0) {
        if (g_Ball.maybebuntOn2Strikes == 0) {
            fn_3_59918(1, 0);
        }
        g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
        if (g_Ball.fielderWBallIndex >= 0) {
            g_Minigame._19C6 = g_Fielders[g_Ball.fielderWBallIndex].minigamePlayer;
        }
    } else {
        u8 st = g_Minigame.toyFieldBallStateResult2;
        if (st == 1) {
            fn_3_A0F0();
        } else if (st == 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x000DC380 size:0x224 mapped:0x8071B414
void fn_3_DC380(void) {
    if (g_Ball.framesSinceLastBounce == 0 && g_Ball.ballBounceState != 3) {
        s32 v = g_Ball.collisionCode;
        if (v >= 0x80) {
            v -= 0x80;
        }
        if (v >= 0x70 && v < 0x79) {
            g_Minigame.maybeTFCollisionResultState = lbl_3_data_189AC[v - 0x70];
        }
    }
    if (g_Ball.AtBat_ContactResult == -1) {
        g_Minigame.toyFieldBallStateResult = 1;
        return;
    }
    if (g_Minigame.toyFieldStateInd_collisionRelated != 0) {
        g_Minigame.toyFieldBallStateResult = lbl_3_data_189AC[g_Minigame.toyFieldStateInd_collisionRelated - 0x70];
        return;
    }
    if (g_Ball.deadBallReason != 0) {
        if (g_Ball.deadBallReason == 1) {
            g_Minigame.toyFieldBallStateResult = 6;
        } else if (g_Ball.deadBallReason == 3) {
            g_Minigame.toyFieldBallStateResult = 4;
        } else {
            g_Minigame.toyFieldBallStateResult = 1;
        }
        g_Minigame.turnOverStatus = 1;
    } else {
        if (g_Ball.AtBat_ContactResult == 0) {
            return;
        }
        if (g_Ball.ballState == 1) {
            InMemFielderType* f = &g_Fielders[g_Ball.fielderWBallIndex];
            if (f->_1EE != 0 || f->_1EC != 0) {
                return;
            }
        } else if (!(g_Ball.ballVelocity < 0.003f || g_Ball.groundRuleDoubleInd != 0 || g_Ball.ballStoppingCode1ReallySlow2Stopped == 2)) {
            return;
        }
        if (g_Ball.AtBat_ContactResult == 3) {
            g_Minigame.toyFieldBallStateResult = 2;
            return;
        }
        if (g_Minigame.maybeTFCollisionResultState == 0) {
            if (fn_3_B7E10(g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.z) != 0) {
                g_Minigame.toyFieldBallStateResult = 1;
            } else {
                g_Minigame.toyFieldBallStateResult = 2;
            }
        } else {
            g_Minigame.toyFieldBallStateResult = g_Minigame.maybeTFCollisionResultState;
        }
        g_Minigame.lastKnownBallPosX = g_Ball.AtBat_Contact_BallPos.x;
        g_Minigame.lastKnownBallPosZ = g_Ball.AtBat_Contact_BallPos.z;
        g_Minigame.TF_framesSinceHittingPanel = 1;
    }
}

// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void fn_3_DC5A4(void) {
    s32 r = fn_3_6C938(1, 0x100);
    if (r != 0) {
        lbl_3_common_bss_34C90.team = r - 1;
        if (lbl_3_common_bss_34C90.cursor == 2) {
            fn_3_5B408();
            lbl_3_common_bss_34C90.state = 9;
        } else {
            lbl_3_common_bss_34C90.state = 4;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }
    if (fn_3_6C938(1, 8) != 0) {
        u8 t = lbl_3_common_bss_34C90.cursor;
        if ((s8)t != 0) {
            lbl_3_common_bss_34C90.cursor = t - 1;
        } else {
            lbl_3_common_bss_34C90.cursor = 2;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }
    if (fn_3_6C938(1, 4) != 0) {
        lbl_3_common_bss_34C90.cursor++;
        if (lbl_3_common_bss_34C90.cursor >= 3) {
            lbl_3_common_bss_34C90.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void fn_3_DC6E8(void) {
    s32 started;
    if (lbl_3_common_bss_34C90._012 < 0x7FFE) {
        lbl_3_common_bss_34C90._012 = lbl_3_common_bss_34C90._012 + 1;
    } else {
        lbl_3_common_bss_34C90._012 = 0x7FFF;
    }
    switch (lbl_3_common_bss_34C90.state) {
    case 0:
        lbl_3_common_bss_34C90.cursor = 0;
        lbl_3_common_bss_34C90.layout = 0x12;
        lbl_3_common_bss_34C90.state = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90._012 = 0;
        lbl_3_common_bss_34C90.state = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90._012 >= 0x14) {
            lbl_3_common_bss_34C90.state = 3;
        }
        break;
    case 3:
        fn_3_DC5A4();
        lbl_3_common_bss_34C90._012 = 0;
        break;
    case 4:
        if (lbl_3_common_bss_34C90._012 >= 0x14) {
            changeScene(3, 6);
        }
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.state = 5;
        }
        break;
    case 5:
        lbl_8036E548._307A = 0;
        started = 0;
        lbl_3_common_bss_34C90.itemsState = 2;
        if (lbl_3_common_bss_34C90.cursor == 0) {
            fn_3_5A6D4(5);
            started = 1;
            g_Minigame._1A38 = 1;
        } else if (lbl_3_common_bss_34C90.cursor == 1) {
            g_Minigame._19DF = 0x1E;
            fn_3_5A6D4(0x1D);
            started = 1;
        }
        if (started != 0) {
            fn_3_DF8D4();
            fn_3_15F998();
            fn_3_147DFC();
            if (lbl_3_common_bss_34C90.cursor == 1) {
                fn_3_11CF84();
            }
        }
        break;
    case 9:
        switch (fn_3_5B380(g_Controls[lbl_3_common_bss_34C90.team].newButtonInput)) {
        case 1:
            fn_3_15F998();
            fn_3_147DFC();
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_3_common_bss_34C90.state = 10;
            break;
        case 2:
            lbl_3_common_bss_34C90.state = 3;
            break;
        }
        break;
    case 10:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.itemsState = 2;
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void fn_3_DCA68(void) {
    GamePauseState* p = &lbl_3_common_bss_34C90;
    u16 b = p->_006;
    if (b & 0x1000) {
        p->state = 4;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }
    if (b & 0x100) {
        if (p->cursor == 0) {
            p->state = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (p->cursor == 1) {
            p->state = 8;
            p->_1D4 = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (p->cursor == 2) {
            p->state = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (p->cursor == 3) {
            fn_3_5B408();
            lbl_3_common_bss_34C90.state = 9;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
    } else {
        if (b & 0x200) {
            if (p->cursor != 0) {
                p->cursor = 0;
            } else {
                p->state = 4;
            }
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (p->_008 & 8) {
            u8 t = p->cursor;
            if ((s8)t > 0) {
                p->cursor = t - 1;
            } else {
                p->cursor = 3;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            return;
        }
        if (p->_008 & 4) {
            u8 t = p->cursor + 1;
            p->cursor = t;
            if ((s8)t >= 4) {
                p->cursor = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void fn_3_DCC80(void) {
    if (lbl_3_common_bss_34C90._00C < 0x7FFE) {
        lbl_3_common_bss_34C90._00C++;
    } else {
        lbl_3_common_bss_34C90._00C = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90._012 < 0x7FFE) {
        lbl_3_common_bss_34C90._012 = lbl_3_common_bss_34C90._012 + 1;
    } else {
        lbl_3_common_bss_34C90._012 = 0x7FFF;
    }
    {
        lbl_803CBC3C = 1;
        lbl_3_common_bss_34C90._004 = g_Controls[lbl_3_common_bss_34C90.team].buttonInput;
        lbl_3_common_bss_34C90._006 = g_Controls[lbl_3_common_bss_34C90.team].newButtonInput;
        lbl_3_common_bss_34C90._008 = g_Controls[lbl_3_common_bss_34C90.team]._08;
    }
    switch (lbl_3_common_bss_34C90.state) {
    case 0:
        lbl_3_common_bss_34C90.cursor = 0;
        lbl_3_common_bss_34C90._1D5 = 0;
        lbl_3_common_bss_34C90.layout = 0x11;
        lbl_3_common_bss_34C90.state = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90._012 = 0;
        lbl_3_common_bss_34C90.state = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90._012 >= 0x14) {
            lbl_3_common_bss_34C90.state = 3;
        }
        break;
    case 3:
        fn_3_DCA68();
        lbl_3_common_bss_34C90._012 = 0;
        break;
    case 4:
        lbl_3_common_bss_34C90.itemsState = 1;
        lbl_3_common_bss_34C90.state = 5;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.itemsState == 3) {
            fn_3_5A6D4(1);
        }
        break;
    case 6:
        lbl_3_common_bss_34C90.itemsState = 1;
        lbl_3_common_bss_34C90.state = 7;
        break;
    case 7:
        if (lbl_3_common_bss_34C90.itemsState == 3) {
            lbl_3_common_bss_34C90._220 = 2;
            lbl_3_common_bss_34C90.state = 0;
            fn_3_5A6D4(0xD);
        }
        break;
    case 8:
        fn_3_107E80();
        break;
    case 9:
        switch (fn_3_5B380(lbl_3_common_bss_34C90._006)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_3_common_bss_34C90.state = 10;
            break;
        case 2:
            lbl_3_common_bss_34C90.state = 3;
            break;
        }
        break;
    case 10:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.itemsState = 2;
            g_d_GameSettings._13 = 1;
            fn_8004CC18();
            g_GameLogic.framesOfExitingToMenu = 1;
        }
        break;
    }
}

// .text:0x000DCED0 size:0x74 mapped:0x8071BF64
void fn_3_DCED0(void) {
    s16* p = &lbl_3_common_bss_34C90._00C;
    if (*p < 0x7FFE) {
        *p += 1;
    } else {
        *p = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (*p > 0x3C) {
        fn_3_AFD80(1);
        fn_3_5A6D4(0xB);
        return;
    }
    fn_3_2EA24();
}

// 21 diff lines: reg alloc (r3/r0 for s8 temp, lbl base order)
// .text:0x000DCF44 size:0xBC mapped:0x8071BFD8
void fn_3_DCF44(void) {
    s32 i;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0 && g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 && (g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[i]].newButtonInput & 0x1000)) {
            lbl_3_common_bss_34C90._1D5 = 1;
            lbl_3_common_bss_34C90.team = g_Minigame.minigameControlStruct[0].characterIndex[i];
            fn_3_AFD80(0);
            fn_3_59918(0xE, 0);
            return;
        }
    }
}

// .text:0x000DD000 size:0x1A8 mapped:0x8071C094
void fn_3_DD000(void) {
    GameControlsStruct* gl = &g_GameLogic;
    switch (gl->_125) {
    case 0:
        changeScene(1, 6);
        gl->_125 = 1;
        break;
    case 1:
        if (gl->FrameCountOfCurrentPitch > 0x708) {
            gl->_125 = 2;
            gl->FrameCountOfCurrentAtBat_Copy = 0;
        } else if (gl->FrameCountOfCurrentPitch > 0x12C && fn_3_6C938(1, 0x1100) != 0) {
            gl->_125 = 2;
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        }
        break;
    case 2:
        if (gl->FrameCountOfCurrentAtBat_Copy > 0x1E) {
            if (g_Minigame._190A != 0) {
                gl->_125 = 4;
            } else {
                gl->_125 = 3;
            }
        }
        break;
    case 3:
        lbl_3_common_bss_34C90.menu = 0;
        lbl_3_common_bss_34C90.state = 0;
        fn_3_5A6D4(0x22);
        break;
    case 4:
        changeScene(4, 6);
        if (lbl_8037169C._13 != 0) {
            gl->_125 = 0xA;
        }
        break;
    case 5:
        if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
            g_d_GameSettings._38 = 0;
        } else {
            g_d_GameSettings._38 = g_Minigame.minigameControlStruct[0]._1C[g_d_GameSettings._35];
        }
        g_GameLogic.framesOfExitingToMenu = 1;
        break;
    }
}

// .text:0x000DD1A8 size:0x1D4 mapped:0x8071C23C
void fn_3_DD1A8(void) {
    GameControlsStruct* gl = &g_GameLogic;
    s32 done;
    switch (gl->_125) {
    case 0: {
        if (g_Minigame.toyField_turnNumber == 0) {
            if (random_fn_3_9EE24(100) < lbl_3_data_18C48[7] || g_Minigame._1907 == 4) {
                s32 n = 0;
                int pl;
            loopA:
                pl = random_fn_3_9EE24(4);
                n++;
                g_Minigame.rosterID = pl;
                if (n < 100) {
                    if (g_Minigame.minigameControlStruct[0].battingHandedness[((s8)(u8)pl)] != 0) {
                        goto loopA;
                    }
                }
            } else {
                s32 n = 0;
                int pl;
            loopB:
                pl = random_fn_3_9EE24(4);
                n++;
                g_Minigame.rosterID = pl;
                if (n < 100) {
                    if (g_Minigame.minigameControlStruct[0].battingHandedness[((s8)(u8)pl)] == 0) {
                        goto loopB;
                    }
                }
            }
        }
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 1;
        break;
    }
    case 1: {
        s32 t = gl->FrameCountOfCurrentPitch;
        done = 0;
        if (t >= lbl_3_data_18C48[2]) {
            done = 1;
        } else if (gl->FrameCountOfCurrentAtBat_Copy >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100) != 0) {
            done = 1;
        }
        if (done != 0) {
            gl->_125 = 2;
            changeScene(3, 6);
        }
        break;
    }
    case 2:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(7);
        }
        break;
    }
}

// .text:0x000DD37C size:0x80 mapped:0x8071C410
void fn_3_DD37C(void) {
    if (g_Minigame._19CE != 0) {
        fn_3_FBD70();
        fn_3_FBD58();
    }
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_1DD48();
    if (g_Minigame.pointsTargetReachedInd == 0) {
        fn_3_2E87C();
        fn_3_5A6D4(0);
        return;
    }
    fn_3_5A6D4(8);
}

// NONMATCHING: original reaches lbl_3_data_1899C/18BB8/18C48 through the pooled base lbl_3_data_188E8 (data defined in this TU), so base registers and stmw differ
// .text:0x000DD3FC size:0x5A8 mapped:0x8071C490
#if NONMATCHING
void fn_3_DD3FC(void) {
    s16* timer = &g_GameLogic.CountdownUntilFade;
    s32 i;

    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        *timer = lbl_3_data_1899C[0];
        if (g_Minigame.toyFieldBallStateResult2 == 1 && g_Ball.maybebuntOn2Strikes == 0) {
            *timer = lbl_3_data_1899C[2];
        }
    }
    *timer -= 1;
    if (g_Minigame._19A0 != 0 && g_Minigame._19CE == 0 && *timer < lbl_3_data_1899C[1]) {
        *timer = lbl_3_data_1899C[1];
    }
    if (g_Minigame._1939 != 0 && *timer < lbl_3_data_1899C[1]) {
        *timer = lbl_3_data_1899C[1];
    }
    if (g_Minigame._19CE != 0 && g_Minigame._19CE < 3) {
        if (*timer <= lbl_3_data_1899C[1] - 0xA) {
            *timer += 1;
        }
        if (g_Minigame._19CE == 1) {
            fn_3_DE308(0xC);
            g_Minigame._19BA = 0;
            g_Minigame._19CE = 2;
            for (i = 0; i < 4; i++) {
                if (g_Minigame._1918[i] != 0) {
                    g_Minigame._1914[i] = 0;
                }
            }
            if (lbl_800EF808.unk398 == 1) {
                playCrowdSound(0x1A);
            }
        }
        if (g_Minigame._19BA < 0x7FFE) {
            g_Minigame._19BA += 1;
        } else {
            g_Minigame._19BA = 0x7FFF;
        }
        if (g_Minigame._19BA > lbl_3_data_18C48[3]) {
            g_Minigame._19CE = 3;
        }
    }
    if (g_Minigame.TF_ballDespawnedInd == 0 && g_Ball.fielderWBallIndex < 0 && g_Ball.deadBallReason == 0 && g_Ball.AtBat_ContactResult >= 0 &&
        *timer <= lbl_3_data_1899C[1] + lbl_3_data_49DC[0x16 / 2] - 0xA) {
        *timer += 1;
    }
    if (*timer == lbl_3_data_1899C[1] - 0xA) {
        u8 st = g_Minigame._19CD;
        if (st == 1 || st == 2 || (st != 3 && g_Minigame._1921 != 0)) {
            *timer += 1;
        } else if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns && g_Minigame.minigameControlStruct[0]._1C[(g_Minigame.rosterID)] == 1) {
            fn_3_59918(0xD, 0);
        } else if ((s32)(u8)g_Minigame.rosterID != g_Minigame._19C6) {
            if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
        if (g_Minigame._19BC < 0x7FFE) {
            g_Minigame._19BC += 1;
        } else {
            g_Minigame._19BC = 0x7FFF;
        }
    }
    if (*timer == 7) {
        changeScene(3, 6);
    }
    if (*timer <= 0) {
        if (g_Minigame._19CE != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
        }
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudLoadingRelated = 1;
        fn_3_1DD48();
        if (g_Minigame.pointsTargetReachedInd == 0) {
            fn_3_2E87C();
            fn_3_5A6D4(0);
            return;
        }
        fn_3_5A6D4(8);
    }
}
#endif

// .text:0x000DD9A4 size:0x3BC mapped:0x8071CA38
void fn_3_DD9A4(void) {
    if (g_Minigame.TF_framesSinceHittingPanel != 0 && g_Ball.fielderWBallIndex < 0) {
        if (g_Minigame.TF_framesSinceHittingPanel < lbl_3_data_18C48[6]) {
            g_Minigame.TF_framesSinceHittingPanel += 1;
        } else if (g_Minigame.TF_ballDespawnedInd == 0) {
            g_Minigame.TF_ballDespawnedInd = 1;
            playCrowdSound(0x15);
        }
    }
    ballPhysica();
    fn_3_2F484();
    if (g_Minigame._19CF != 0) {
        if (g_Minigame._19CE == 0) {
            fn_3_DC240();
        }
    } else if (g_Minigame.toyFieldBallStateResult != 0 && g_Minigame.toyFieldBallStateResult2 == 0) {
        fn_3_DC240();
    } else if (g_Minigame.toyFieldBallStateResult2 == 0) {
        fn_3_DC380();
    }
    if (g_Minigame.toyFieldBallStateResult2 != 0) {
        fn_3_DA834();
    }
    if (g_Minigame.turnOverStatus != 0) {
        fn_3_DD3FC();
    }
}

// .text:0x000DDD60 size:0x1BC mapped:0x8071CDF4
void fn_3_DDD60(void) {
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[0];
    }
    g_GameLogic.CountdownUntilFade -= 1;
    if (g_Minigame._19A0 != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
        g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
    }
    if (g_GameLogic.CountdownUntilFade == lbl_3_data_1899C[1] - 0xA) {
        if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns && g_Minigame.minigameControlStruct[0]._1C[(g_Minigame.rosterID)] == 1) {
            fn_3_59918(0xD, 0);
        } else if ((s32)(u8)g_Minigame.rosterID != g_Minigame._19C6) {
            if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
    }
    if (g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        if (g_Minigame._19CE != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
        }
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudLoadingRelated = 1;
        fn_3_1DD48();
        if (g_Minigame.pointsTargetReachedInd == 0) {
            fn_3_2E87C();
            fn_3_5A6D4(0);
            return;
        }
        fn_3_5A6D4(8);
    }
}

// .text:0x000DDF1C size:0x84 mapped:0x8071CFB0
void fn_3_DDF1C(void) {
    fn_3_6EBB4(g_Minigame.minigamePlayerSelectedOrder);
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_58870();
    fn_3_1DEB8();
    fn_3_BF1AC();
    Set_803cb848(1);
    fn_3_BF158();
    g_FieldingLogic._0AE = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
}

// .text:0x000DDFA0 size:0x368 mapped:0x8071D034
void fn_3_DDFA0(void) {
    if (g_Pitcher.pitchTotalTimeCounter <= 0 && lbl_3_common_bss_34C90._1D5 == 0) {
        fn_3_DCF44();
    }
    if (lbl_3_common_bss_34C90._1D5 != 0) {
        fn_3_DCED0();
        return;
    }
    fn_3_75560();
    atBat_batter();
    fn_3_2EA24();
    if (g_Minigame.toyFieldBallStateResult2 == 0 && g_Pitcher.strikeOutOrWalk != 0) {
        if (g_Pitcher.strikeOutOrWalk == 1) {
            g_Minigame.toyFieldBallStateResult2 = 2;
        } else if (g_Pitcher.strikeOutOrWalk == 2) {
            g_Minigame.toyFieldBallStateResult2 = 7;
        } else {
            g_Minigame.toyFieldBallStateResult2 = 8;
        }
    }
    if (g_Minigame.toyFieldBallStateResult2 != 0) {
        fn_3_DA834();
    }
    if (g_Minigame.turnOverStatus != 0) {
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[0];
        }
        g_GameLogic.CountdownUntilFade -= 1;
        if (g_Minigame._19A0 != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
            g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
        }
        if (g_GameLogic.CountdownUntilFade == lbl_3_data_1899C[1] - 0xA) {
            if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns && g_Minigame.minigameControlStruct[0]._1C[(g_Minigame.rosterID)] == 1) {
                fn_3_59918(0xD, 0);
            } else if ((s32)(u8)g_Minigame.rosterID != g_Minigame._19C6) {
                if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
                    fn_3_59918(0xD, 0);
                } else {
                    fn_3_59918(5, 0);
                }
            }
        }
        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(3, 6);
        }
        if (g_GameLogic.CountdownUntilFade <= 0) {
            if (g_Minigame._19CE != 0) {
                fn_3_FBD70();
                fn_3_FBD58();
            }
            g_GameLogic.pre_PostMiniGameInd = 1;
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            g_GameLogic.hudLoadingRelated = 1;
            fn_3_1DD48();
            if (g_Minigame.pointsTargetReachedInd == 0) {
                fn_3_2E87C();
                fn_3_5A6D4(0);
                return;
            }
            fn_3_5A6D4(8);
        }
    }
}

typedef struct { s16 a, b, c; } T18BB8;
extern T18BB8 lbl_3_data_18BB8[];



// .text:0x000DE308 size:0x1F4 mapped:0x8071D39C
void fn_3_DE308(s32 idx) {
    s32 i;

    if (idx == 0x14 || idx == 0x15) {
        s16* sc = &g_Minigame.miniGameLatestPoints[0];
        sc[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[idx].a;
        sc[g_Minigame.minigamePlayerSelectedOrder] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[idx].b;
        // byte-offset form: the original adds the index to g_Minigame before the field offset
        *(s16*)((u8*)&g_Minigame + g_Fielders[g_Ball.fielderWBallIndex].minigamePlayer * 2 + OFFSET_OF(MiniGameStruct, miniGameLatestPoints)) +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[idx].c;
    } else {
        s16* sc;
        s16 v2;
        sc = &g_Minigame.miniGameLatestPoints[0];
        sc[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[idx].a;
        v2 = lbl_3_data_18BB8[idx].c;
        sc[g_Minigame.minigamePlayerSelectedOrder] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[idx].b;
        sc[g_Minigame.minigameControlStruct[0].fieldOrder[1]] += g_Minigame.toyField_pointMultiplier * v2;
        sc[g_Minigame.minigameControlStruct[0].fieldOrder[2]] += g_Minigame.toyField_pointMultiplier * v2;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame.miniGameLatestPoints[i] != 0) {
            g_Minigame.minigamePoints_current_Latest[i].current = g_Minigame.miniGameCurrentPoints[i];
            g_Minigame.minigamePoints_current_Latest[i].latest = g_Minigame.miniGameLatestPoints[i];
        }
    }
}

// .text:0x000DE4FC size:0x114 mapped:0x8071D590
void fn_3_DE4FC(void) {
    s32 i;
    s32 j;
    s16 score;
    s32 rank;
    s32 n;

    g_Minigame.minigameControlStruct[0]._1C[0] = 0;
    g_Minigame.minigameControlStruct[0]._20[0] = 0;
    g_Minigame.minigameControlStruct[0]._1C[1] = 0;
    g_Minigame.minigameControlStruct[0]._20[1] = 0;
    g_Minigame.minigameControlStruct[0]._1C[2] = 0;
    g_Minigame.minigameControlStruct[0]._20[2] = 0;
    g_Minigame.minigameControlStruct[0]._1C[3] = 0;
    g_Minigame.minigameControlStruct[0]._20[3] = 0;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        rank = 1;
        score = g_Minigame.miniGameCurrentPoints[i];
        for (j = 0; j < g_Minigame.miniGameNumberOfParticipants; j++) {
            if (g_Minigame.miniGameCurrentPoints[j] > score) {
                rank++;
            }
        }
        g_Minigame.minigameControlStruct[0]._1C[i] = rank;
        g_Minigame.minigameControlStruct[0]._20[i] = rank;
    }
    for (n = 0; n < 4; n++) {
        if (g_Minigame.minigameControlStruct[0]._1C[n] > 1) {
            break;
        }
    }
    if (n >= 4 && g_Minigame.miniGameNumberOfParticipants > 1) {
        g_Minigame.challenge_minigame_haven_tWonYetIndicator = 1;
    } else {
        g_Minigame.challenge_minigame_haven_tWonYetIndicator = 0;
    }
}

// .text:0x000DE610 size:0x134 mapped:0x8071D6A4

void fn_3_DE610(void) {
    g_Minigame.panelHitInd = 0;
    if (g_Minigame._19A6 != 0) {
        g_Minigame._19A6--;
        if (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) {
            g_Minigame._19A6 = 3;
        }
    }
    g_Strikes.outs = 0;
    g_Strikes.storedOuts = 0;
    g_Minigame._19A5 = 1;
    if ((g_Minigame.rosterID != g_Minigame._19C6 || g_Minigame.minigameControlStruct[0]._1C[(g_Minigame.rosterID)] == 1) &&
        g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
        lbl_3_common_bss_34C90.state = 0;
        fn_3_5A6D4(0xE);
        return;
    }
    if (g_Minigame.toyField_turnNumber < g_Minigame.toyField_selectedTurns && (g_Minigame.toyField_turnNumber % 10) == 0) {
        fn_3_5A6D4(3);
        return;
    }
    fn_3_5A6D4(7);
}

extern void fn_3_6C0E0(void);
extern void fn_3_E67F4(void);

void fn_3_DE744(void) {
    s32 i;

    fn_3_DDF1C();
    fn_3_6C0E0();
    g_Runners[0].positionStored.x = g_Runners[0].position.x;
    g_Runners[0].positionStored.y = g_Runners[0].position.y;
    g_Runners[0].positionStored.z = g_Runners[0].position.z;
    g_Runners[0].unused_AIRelated = 1;
    g_Runners[0].battingHand = g_Batter.batterHand;
    g_Runners[0].batterStayInBattersBoxReason = 1;
    g_Runners[0].position.x = g_Batter.batterPos.x;
    g_Runners[0].position.y = 0.0f;
    g_Runners[0].position.z = g_Batter.batterPos.z;
    g_Runners[0].runningAngle = 3.1415927f;
    g_GameLogic.CountdownUntilFade = 10000;
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.outs = 0;
    g_Strikes.storedOuts = 0;
    g_Ball.totalFramesAtPlay = 0;
    lbl_3_common_bss_34C90._1D5 = 0;
    g_Scores._C5 = 0;
    g_Minigame.turnOverStatus = 0;
    g_Minigame.pointsTargetReachedInd = 0;
    g_Minigame.toyFieldBallStateResult2 = 0;
    g_Minigame.framesSincePanelHit = 0;
    g_Minigame._1921 = 0;
    g_Minigame._1914[0] = 1;
    g_Minigame.toyFieldStateInd_collisionRelated = 0;
    g_Minigame._1939 = 0;
    g_Minigame.panelHitInd = 0;
    g_Minigame._19A0 = 0;
    g_Minigame._1934 = 0;
    g_Minigame._18BA = 0;
    g_Minigame._19A3 = 0;
    g_Minigame.TF_framesSinceHittingPanel = 0;
    g_Minigame.TF_ballDespawnedInd = 0;
    g_Minigame._190E = 0;
    g_Minigame.maybeTFCollisionResultState = 0;
    g_Minigame.toyFieldBallStateResult = 0;
    g_Minigame._19BC = 0;
    g_Minigame._19D0 = 0;
    g_Minigame._19CD = 0;
    g_Minigame._19CF = 0;
    if (g_Minigame._19CE == 3) {
        fn_3_E67F4();
    }
    g_Minigame._19CE = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.minigamePoints_current_Latest[i].current = g_Minigame.miniGameCurrentPoints[i];
        g_Minigame.minigamePoints_current_Latest[i].latest = 0;
        g_Minigame.playerOrder[i] = -1;
    }
    for (i = 0; i < 100; i++) {
        g_Minigame.wallBall_coinsVisibleInd[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame._1914[i] != 0) {
            g_Minigame._191C[i] = i;
        } else {
            g_Minigame._191C[i] = -1;
        }
        g_Minigame._1918[i] = g_Minigame._1914[i];
    }
    g_FieldingLogic._10E = 0;
    g_FieldingLogic._0EE = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_FieldingLogic._0E4 = 0;
    g_RunningLogic._13 = 0;
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
}
