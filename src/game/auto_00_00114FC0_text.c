#include "game/auto_00_00114FC0_text.h"
#include "game/auto_00_0005985C_text.h"
#include "game/auto_00_00113398_text.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_0009CD90_text.h"
#include "static/GameSettings.h"
#include "main/file_80011640.h"
#include "main/file_8001FE00.h"

extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern void fn_3_114A88(s32);
extern void changeScene(s32, s32);
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern s16 lbl_3_data_18C48[];
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern u8 lbl_3_data_21BC4[];
extern f32 lbl_3_data_226C4[];
extern void fn_3_11881C(s32 i);
extern void fn_8001D110(s32 i, f32 a, f32 b, f32 c);
extern s16 lbl_3_data_2167C[]; // [0] turn-over delay, [2] frame limit, [4] coin lifetime
extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void fn_3_58870(void);
extern void fn_3_DE4FC(void);
extern void fn_3_10F550(s32, s32);
extern void Set_803cb848(s32);
extern void* memset(void*, s32, u32);
extern u8 lbl_3_common_bss_32234[];
extern u8 lbl_3_common_bss_37400[];
extern WallBallCoinPhysics lbl_3_data_21634;
extern f32 lbl_3_data_219B8[];      // [14]: coin floor height
extern s16 lbl_3_data_21654[];      // [10]: bonus points per hit
extern u8 lbl_3_data_21671;         // max rounds
extern s16 lbl_3_data_21672;        // last-round point multiplier
extern u8 lbl_3_data_2127C[][5];    // AI strength per [game mode][difficulty]
extern u8 lbl_3_data_2166C[];       // rounds per difficulty
extern s32 fn_3_108854(void);
extern void fn_3_1133C4(void);
extern void fn_3_113A48(void);
extern void fn_3_113D20(void);
extern void fn_3_113F14(void);
extern void fn_3_114204(void);
extern void fn_3_114384(void);
extern void fn_3_1500C8(void);
extern void fn_3_2EA24(void);
extern void fn_3_75560(void);
extern void fn_3_1608F0(s32 type, s32 value, s32 flag);
extern void fn_3_59A90(void);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern void fn_3_F8ABC(void);



// fn_3_114FC0, size:0x6C
void fn_3_114FC0(void) {
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    g_Minigame.turnNumberWithinRound++;
    if (g_Minigame.turnNumberWithinRound >= g_Minigame.miniGameNumberOfParticipants) {
        fn_3_5A6D4(0x19);
        return;
    }
    fn_3_5A6D4(7);
}

// fn_3_11502C, size:0xDC
void fn_3_11502C(void) {
    if (g_Minigame.turnOverStatus == 1) {
        g_Minigame.turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_2167C[0];
    }
    g_GameLogic.CountdownUntilFade -= 1;
    if (g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudLoadingRelated = 1;
        g_Minigame.turnNumberWithinRound++;
        if (g_Minigame.turnNumberWithinRound >= g_Minigame.miniGameNumberOfParticipants) {
            fn_3_5A6D4(0x19);
            return;
        }
        fn_3_5A6D4(7);
    }
}

// Same as fn_3_113398 (inlined here).
static inline void WallBall_ClearFlags(void) {
    s8 i;

    i = 0;
    do {
        ((MG1133View*)&g_Minigame)->flag[i] = 0;
        i++;
    } while (i < 4);
}

static inline void WallBall_UpdateCoins(void) {
    s32 c;
    s16 lifetime;
    f32 friction;
    f32 bounce;
    f32 floorY;
    f32 gravity;

    gravity = lbl_3_data_21634.gravity;
    floorY = lbl_3_data_219B8[14];
    bounce = lbl_3_data_21634.bounce;
    friction = lbl_3_data_21634.friction;
    lifetime = lbl_3_data_2167C[4];

    for (c = 0; c < 100; c++) {
        if (g_Minigame.wallBall_coinsVisibleInd[c] != 0) {
            g_Minigame.wallBall_coinFrames[c]++;
            g_Minigame.wallBall_coinCoordinates[c].x += g_Minigame.wallBall_coinVelocity[c].x;
            g_Minigame.wallBall_coinCoordinates[c].y += g_Minigame.wallBall_coinVelocity[c].y;
            g_Minigame.wallBall_coinCoordinates[c].z += g_Minigame.wallBall_coinVelocity[c].z;
            g_Minigame.wallBall_coinVelocity[c].y -= gravity;
            if (g_Minigame.wallBall_coinCoordinates[c].y < floorY) {
                g_Minigame.wallBall_coinCoordinates[c].y = floorY;
                g_Minigame.wallBall_coinVelocity[c].y = -g_Minigame.wallBall_coinVelocity[c].y * bounce;
                g_Minigame.wallBall_coinVelocity[c].x *= friction;
                g_Minigame.wallBall_coinVelocity[c].z *= friction;
            }
            if (g_Minigame.wallBall_coinFrames[c] > lifetime) {
                g_Minigame.wallBall_coinsVisibleInd[c] = 0;
            }
        }
    }
}

// fn_3_115108, size:0x438
// End of a Wall Ball turn: award points, advance the turn and the round.
// NONMATCHING 98%: &currentPoints[player] is kept as a pointer (extra addi) and two scratch regs swap at the turn update
#if NONMATCHING
void fn_3_115108(void) {
    s32 points;
    s16 mult;
    s16 half;
    s32 share;
    s16 i;
    s32 over;
    u8 turn;

    over = 0;
    if (g_Pitcher.pitcherActionState == 4) {
        if (g_Pitcher.currentStateFrameCounter > 0x4A) {
            over = 1;
        } else if (g_Minigame.soloMinigameDifficulty == 3 && g_Pitcher.currentStateFrameCounter == 0x4A) {
            g_Minigame._1A8C[0] = 1;
        }
    } else if (g_Minigame.postBallStoppedCounter > lbl_3_data_2167C[2]) {
        over = 1;
    } else if (g_Minigame.soloMinigameDifficulty == 3 && g_Minigame.postBallStoppedCounter == lbl_3_data_2167C[2]) {
        g_Minigame._1A8C[0] = 1;
    }
    if (over == 0) {
        return;
    }

    if (g_Minigame.wallBall_hitBowserWall == 0) {
        mult = 1;
        if ((g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0 || g_Minigame.soloMinigameDifficulty != 3) && g_Scores.inning == g_Scores.maxInnings) {
            mult = lbl_3_data_21672;
        }
        if (g_Minigame.wallBall_hitNoteBlock == 1) {
            points = g_Minigame.wallBall_UnknownAlways0 + lbl_3_data_21654[10] * mult;
            g_Minigame.miniGameCurrentPoints[g_Minigame.minigamePlayerSelectedOrder] += points;
            g_Minigame.wallBall_UnknownAlways0 = 0;
        } else {
            points = g_Minigame.miniGameLatestPoints[g_Minigame.minigamePlayerSelectedOrder] * mult;
            g_Minigame.miniGameCurrentPoints[g_Minigame.minigamePlayerSelectedOrder] += points;
        }
    } else {
        points = 0;
        if (g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0 || g_Minigame.soloMinigameDifficulty != 3) {
            half = g_Minigame.miniGameCurrentPoints[g_Minigame.minigamePlayerSelectedOrder] / 2;
            g_Minigame.miniGameCurrentPoints[g_Minigame.minigamePlayerSelectedOrder] -= half;
            share = half / 3;
            for (i = 0; i < 4; i++) {
                if (i != g_Minigame.minigamePlayerSelectedOrder) {
                    g_Minigame.miniGameCurrentPoints[i] += share;
                }
            }
            points = -half;
        }
    }
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Minigame.minigamePlayerSelectedOrder == *(s16*)(lbl_3_common_bss_37400 + 0x40)) { // TODO type
        fn_3_1608F0(1, points, g_Minigame.wallBall_hitNoteBlock);
    }

    turn = g_Minigame.turnNumberWithinRound + 1;
    g_Minigame.wallBallSomeXPos = g_Pitcher.pitcherCoord.x;
    g_Minigame.wallBallSomeZPos = g_Pitcher.pitcherCoord.z;
    g_Minigame.turnNumberWithinRound = turn;
    if (turn >= g_Minigame.miniGameNumberOfParticipants) {
        g_Minigame.turnNumberWithinRound = turn - g_Minigame.miniGameNumberOfParticipants;
        g_Scores.inning++;
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == 3) {
            g_Scores.inning--;
            if (g_Minigame.wallBall_hitNoteBlock == 1) {
                if (g_Scores.maxInnings < lbl_3_data_21671) {
                    g_Scores.maxInnings++;
                }
            } else {
                g_Scores.maxInnings--;
                if (g_Minigame.wallBall_hitBowserWall != 0) {
                    for (i = 0; i < 1; i++) {
                        if (g_Scores.maxInnings == 0) {
                            break;
                        }
                        g_Scores.maxInnings--;
                    }
                }
            }
        }
    }
    fn_3_1500C8();
    if (g_Scores.inning > g_Scores.maxInnings) {
        sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        fn_3_5A6D4(0xF);
        return;
    }
    g_Minigame.wallBallGameState = 0;
    fn_3_5A6D4(7);
    if ((g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0 || g_Minigame.soloMinigameDifficulty != 3) && g_Minigame.turnNumberWithinRound == 0) {
        fn_3_10F550(4, 0);
    }
}
#endif

// fn_3_115540, size:0x1F8
// Per-frame update while the ball is in play: phase logic and the coin physics.
// NONMATCHING 91%: coin loop: g_Minigame base is materialised after the constant tables, walker regs shifted by one
#if NONMATCHING
void fn_3_115540(void) {
    if (fn_3_108854() != 0) {
        return;
    }
    if (g_Minigame.wallBallRotatePitchersInd != 0) {
        fn_3_114A88(0);
    } else if (g_Minigame.wallBallGameState == 2) {
        fn_3_1133C4();
        fn_3_75560();
        WallBall_ClearFlags();
        fn_3_113A48();
    }
    if (g_Minigame.ballStoppedBreakingWallsInd != 0) {
        if (g_Minigame.postBallStoppedCounter < 0x7FFE) {
            g_Minigame.postBallStoppedCounter++;
        } else {
            g_Minigame.postBallStoppedCounter = 0x7FFF;
        }
    }
    fn_3_2EA24();
    if (g_Minigame.wallBallGameState == 0) {
        fn_3_114384();
        fn_3_1500C8();
    } else if (g_Minigame.wallBallGameState == 1) {
        fn_3_114204();
    } else if (g_Minigame.wallBallGameState == 2) {
        fn_3_113F14();
        fn_3_113D20();
    }
    WallBall_UpdateCoins();
    fn_3_115108();
}
#endif

// fn_3_115738, size:0xF0
void fn_3_115738(void) {
    switch (g_GameLogic._125) {
    case 0:
        changeScene(1, 6);
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[2] ||
            (g_GameLogic.FrameCountOfCurrentPitch >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// fn_3_115828, size:0x88
void fn_3_115828(void) {
    fn_3_DE4FC();
    if (g_Minigame.soloMinigameDifficulty <= 2 && g_Minigame.multiPlayerInd == 0) {
        if (g_Minigame.minigameControlStruct[0]._1C[g_Minigame._1908] == 1 && g_Minigame.challenge_minigame_haven_tWonYetIndicator == 0) {
            g_Minigame._1A37 = 1;
        } else {
            g_Minigame._1A37 = 2;
        }
    }
    fn_3_5A6D4(0xE);
}

// fn_3_1158B0, size:0x48
void fn_3_1158B0(void) {
    if (g_Scores.inning >= (s32)g_Scores.maxInnings) {
        fn_3_5A6D4(0xF);
        return;
    }
    fn_3_5A6D4(6);
}

// fn_3_1158F8, size:0x80
void fn_3_1158F8(void) {
    fn_3_6EBB4(g_Minigame.minigamePlayerSelectedOrder);
    fn_3_F1DC();
    fn_3_751B4();
    fn_3_58870();
    memset(&g_Minigame._1D7C[0], 0, 0x78);
    Set_803cb848(1);
    g_FieldingLogic._0AE = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
}

// fn_3_115978, size:0x13C
void fn_3_115978(void) {
    fn_3_1158F8();
    g_Minigame.turnOverStatus = 0;
    g_Minigame.ballStoppedBreakingWallsInd = 0;
    g_Minigame.postBallStoppedCounter = 0;
    g_Minigame.wallBallPitchPower = 0;
    g_Minigame.wallBallPitchPowerRemaining = 0;
    g_Minigame.wallBall_hitNoteBlock = 0;
    g_Minigame.wallBall_hitBowserWall = 0;
    g_Minigame._1A8B = -1;
    g_Ball.totalFramesAtPlay = 0;
    if (g_Minigame.miniGameTurnCounter == 0) {
        if (g_GameLogic.pre_PostMiniGameInd != 0) {
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            g_GameLogic.hudElementLoadingInd = 1;
        } else {
            g_GameLogic.minigameLastTurnSuccessInd = 0;
        }
        g_GameLogic.pre_PostMiniGameInd = 0;
    } else if (g_Minigame.soloMinigameDifficulty != 3) {
        g_Minigame.wallBallPitcherRotationCounter = 0;
        g_Minigame.wallBallRotatePitchersInd = 1;
        fn_3_114A88(0);
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    changeScene(1, 6);
    fn_3_5A6D4(1);
}

// fn_3_115AB4, size:0xA8
void fn_3_115AB4(void) {
 u8 t;
t = g_Minigame.minigameControlStruct[0].turnOrder[g_Minigame.turnNumberWithinRound]; g_Minigame.minigamePlayerSelectedOrder = t;
g_GameLogic.pre_PostMiniGameInd = 1;
g_Minigame.miniGameLatestPoints[0] = 0; g_Minigame.miniGameLatestPoints[1] = 0; g_Minigame.miniGameLatestPoints[2] = 0; g_Minigame.miniGameLatestPoints[3] = 0;
    fn_3_F578();
    fn_3_753E8(0);
    fn_3_6EBB4(g_Minigame.minigamePlayerSelectedOrder);
    g_Batter.batPosition2.x = maybeInitialBatPos.x;
    g_Batter.batPosition2.y = maybeInitialBatPos.y;
    g_Batter.batPosition2.z = maybeInitialBatPos.z;
    fn_3_5A6D4(0);
}

// fn_3_115B5C, size:0x80
void fn_3_115B5C(void) {
    g_Scores.inning += 1;
    g_Minigame.turnNumberWithinRound = 0;
    fn_3_5A6D4(7);
    if (g_Minigame.multiPlayerInd != 0 || g_Minigame._1A3C != 0 || g_Minigame.soloMinigameDifficulty != 3) {
        fn_3_10F550(4, 0);
    }
}

// fn_3_115BDC, size:0x48
void fn_3_115BDC(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_114A88(1);
    fn_3_5A6D4(6);
}

// fn_3_115C24, size:0x494
// Wall Ball setup.
// NONMATCHING 87%: g_Minigame stays in r30 across the calls (original reloads it into r7), fielder index not strength-reduced in the original
#if NONMATCHING
void fn_3_115C24(void) {
    s32 i;
    s32 n;
    u8 strength;

    if (g_GameLogic._125 == 0) {
        fn_3_59A90();
        g_GameLogic.secondaryGameMode = 4;
        for (i = 0; i < 4; i++) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
            g_Minigame.miniGameLatestPoints[i] = 0;
            g_Minigame.minigamePoints_current_Latest[i].current = 0;
            g_Minigame.minigamePoints_current_Latest[i].latest = 0;
            g_Minigame.minigameControlStruct[0].fieldOrder[i] = -1;
            g_Minigame.minigameFielderIndex[i] = -1;
            g_Minigame._18FC[i] = -1;
            g_Minigame._1900[i] = -1;
            g_Minigame.minigameControlStruct[0]._24[i] = 0;
        }
        g_Scores.inning = 0;
        g_Minigame.turnNumberWithinRound = 0;
        g_Minigame.pointsReqToWin_challenge = 0;
        g_Minigame.rosterID = -1;
        g_Minigame._17C0 = 0;
        g_Minigame._1A37 = 0;
        g_Minigame.miniGameTurnCounter = 0;
        if (g_Minigame.multiPlayerInd == 0) {
            strength = lbl_3_data_2127C[g_Minigame.GameMode_MiniGame][g_Minigame.soloMinigameDifficulty];
            g_Scores.maxInnings = lbl_3_data_2166C[g_Minigame.soloMinigameDifficulty];
            for (i = 0; i < 4; i++) {
                g_Minigame.minigameControlStruct[0].aIStrength[i] = strength;
            }
        } else {
            if (g_Minigame._1A3C != 0) {
                for (i = 0; i < 4; i++) {
                    g_Minigame.minigameControlStruct[0].aIStrength[i] = lbl_3_data_2127C[7][0];
                }
            }
            g_Scores.maxInnings = lbl_3_data_2166C[4];
        }
        n = 0;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0) {
                g_Minigame.minigameControlStruct[0].fieldOrder[n] = i;
                g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[n]] = n + 2;
                g_Minigame.minigameControlStruct[0].turnOrder[n] = i;
                g_Fielders[(n + 2)].minigamePlayer = i;
                n++;
            }
        }
        fn_3_58870();
        fn_3_114A88(1);
        for (i = 0; i < 7; i++) {
            ((WallBallView*)&g_Minigame)->bumper[i]._00 = 0;
            ((WallBallView*)&g_Minigame)->bumper[i].id = i;
            g_Minigame.wallIndexTracker[i] = i;
        }
        g_Minigame.wallBallGameState = 0;
        g_Minigame._1A80 = 0;
        g_Minigame._1A78 = 0;
        for (i = 0; i < 2; i++) {
            ((WallBallView*)&g_Minigame)->_1A7C[i] = (i & 1) ? 0 : 6;
        }
        g_Minigame.wallBallPitcherRotationCounter = 0;
        g_Minigame.wallBallRotatePitchersInd = 0;
        g_Minigame.wallBall_hitNoteBlock = 0;
        g_Minigame.wallBall_hitBowserWall = 0;
        g_Minigame._1A8B = -1;
        g_Minigame.wallBall_UnknownAlways0 = 0;
        g_Minigame._1A8C[0] = 0;
        for (i = 0; i < 100; i++) {
            g_Minigame.wallBall_coinsVisibleInd[i] = 0;
        }
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        fn_3_F8ABC();
        g_GameLogic._125++;
    } else {
        lbl_3_common_bss_32234[1] = 1;
        fn_3_5A6D4(5);
    }
}
#endif

// fn_3_1160B8, size:0x4
void fn_3_1160B8(void) {
}

#if !NONMATCHING
// Switch jump tables of fn_3_1160BC; mwcc emits them itself once the function matches.
void* jumptable_3_data_22580[27] = {
    (u8*)fn_3_1160BC + 0x160, (u8*)fn_3_1160BC + 0x284, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x494,
    (u8*)fn_3_1160BC + 0x40, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x78, (u8*)fn_3_1160BC + 0xE0,
    (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8,
    (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x55C,
    (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8,
    (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x5C8,
    (u8*)fn_3_1160BC + 0x5C8, (u8*)fn_3_1160BC + 0x464, (u8*)fn_3_1160BC + 0x48,
};
#endif

// fn_3_1160BC, size:0x5E0
// Wall Ball state dispatcher.
// NONMATCHING 97%: inlines the same-file state handlers; differences are those of fn_3_115540 (inlined)
#if NONMATCHING
void fn_3_1160BC(void) {
    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_115C24();
        break;
    case 26:
        fn_3_115BDC();
        break;
    case 6:
        fn_3_115B5C();
        break;
    case 7:
        fn_3_115AB4();
        break;
    case 0:
        fn_3_115978();
        break;
    case 1:
        fn_3_115540();
        break;
    case 25:
        fn_3_1158B0();
        break;
    case 3:
        fn_3_115738();
        break;
    case 15:
        fn_3_115828();
        break;
    }
}
#endif

// fn_3_11669C, size:0x30
void fn_3_11669C(void) {
    lbl_8036E548.trail2[0xF0]._26 = 0;
    lbl_8036E548.trail2[0xF1]._26 = 0;
    lbl_8036E548.trail2[0xF2]._26 = 0;
    lbl_8036E548.trail2[0xF3]._26 = 0;
}

// fn_3_1166CC, size:0xC0
void fn_3_1166CC(void) {
    u32 i;
    for (i = 0; i < 40; i++) {
        u8* p = ((u8*)lbl_8036E548.trail2) + i * 0x28;
        p[0x26] = 0;
        *(s32*)p = 0;
    }
}

// fn_3_11678C, size:0xB4
void fn_3_11678C(void) {
    CharTrail* e;
    s32 i;
    f32* v;
    for (i = 0; i < 7; i++) {
        e = &lbl_8036E548.trail2[i + 0xE9];
        e->_26 = 0;
        if (i >= 4) {
            e->_26 = 1;
            v = (f32*)(lbl_3_data_21BC4 + i * 0x30 - 0xC0);
            e->_04[0] = v[0];
            e->_04[1] = -v[1];
            e->_04[2] = v[2];
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0]);
            e->draw = (void (*)(void))fn_3_11881C;
        }
    }
}
