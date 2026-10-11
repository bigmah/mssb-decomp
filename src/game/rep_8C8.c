#include "game/rep_8C8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0009CD90_text.h"
#include "game/auto_00_000E587C_text.h"
#include "static/GameSettings.h"
#pragma dont_inline on
extern s32 fn_3_B0CF4(void);
extern void fn_3_B0D2C(void);
extern u8 lbl_3_data_19C4[];

extern u8 lbl_3_data_1ABC[];
extern u8 lbl_3_data_1C90[];
extern u8 lbl_3_data_1C98[];
extern f32 lbl_3_data_1D10[];
extern s16 lbl_3_data_4B90[];
extern u8 lbl_3_data_1ADC[];
extern u8 lbl_3_data_1AEC[];
extern u8 lbl_3_data_1B4C[];
extern u8 lbl_3_data_1AAC[];
extern u8 lbl_3_data_1AB0[];
extern f32 lbl_3_data_19CC[];
extern f32 lbl_3_data_19DC[];
extern f32 lbl_3_data_1A04[];
extern f32 lbl_3_data_1A0C[]; // [0] max box-move speed, [1] acceleration
extern u8 lbl_3_data_1A24[];
extern u8 lbl_3_data_1A28[];
extern u8 lbl_3_data_1A3C[];
extern f32 lbl_3_data_4474[];
extern u8 lbl_3_data_1A40[];
extern u8 lbl_3_data_193C[]; // batter difficulty per AI difficulty setting
extern u8 lbl_3_data_1944[]; // star-swing odds: [situation][difficulty][stars] (6 per difficulty)
extern u8 lbl_3_data_198C[]; // [difficulty][count][star-swing %, swing %]
extern u8 lbl_3_data_19B4[];
extern u8 lbl_3_data_1A14[];
extern u8 lbl_3_data_1A20[];
extern u8 lbl_3_data_1C08[]; // batter Z position range [bunt][min, max]
extern u8 lbl_3_data_1C0C[];
extern u8 lbl_3_data_1C10[];
extern u8 lbl_3_data_1B50[]; // swing-timing jitter weights: [difficulty][2][9]
extern u8 lbl_3_data_1B98[];
extern s8 lbl_3_data_1BA8[];
extern s8 lbl_3_data_1BAC[]; // [early/late][difficulty][min, max]
extern s8 lbl_3_data_1BBC[];
extern s8 lbl_3_data_1BC4[];
extern s8 lbl_3_data_1BCC[];
extern u8 lbl_3_data_1BD4[];
extern u8 lbl_3_data_1BD8[];
extern u8 lbl_3_data_1BE4[];
extern u8 lbl_3_data_1BF0[];
extern u8 lbl_3_data_1A58[];
extern f32 lbl_3_data_1A88[];
extern f32 lbl_3_data_1AA8;
extern f32 lbl_3_data_5EB8;

// .text:0x0001E4B8 size:0x26C mapped:0x8065D54C
void fn_3_1E4B8(void) {
    u32 d;
    s32 n;
    s32 ri;
    f32 chance;
    u8 sp;
    s32 rr;
    s16 fl;
    g_AiLogic.batterAIStealIndicator = 0;
    rr = RandomInt_Game(100);
    d = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
    if (rr < lbl_3_data_1C90[d]) {
        g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[2] - 1;
    } else {
        g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[3] - 1;
    }
    n = g_Pitcher.nPitchesThisAB;
    if (n > 2) {
        n = 2;
    }
    fl = g_RunningLogic.occupiedBases;
    if (fl & 0x100) {
        if (fl & 0x1000) {
            return;
        }
        ri = 2;
        chance = (lbl_3_data_1C98 + d * 12 + n * 4 + g_Runners[2].characterClass)[0x3C];
    } else if (fl & 0x10) {
        ri = 1;
        chance = (lbl_3_data_1C98 + d * 12 + n * 4 + g_Runners[1].characterClass)[0x3C];
    } else {
        return;
    }
    chance *= lbl_3_data_1D10[g_Batter.characterClass];
    if (g_Strikes.balls == 3) {
        chance *= lbl_3_data_1D10[4];
    }
    sp = g_Runners[ri].speed;
    if (sp >= 0x32) {
        chance *= lbl_3_data_1D10[5] * (f32)((sp - 0x32) / 10) + 1.0f;
    }
    if (RandomInt_Game(100) < (s32)chance) {
        g_AiLogic.batterAIStealIndicator = 1;
    }
}

// .text:0x0001E724 size:0xD0 mapped:0x8065D7B8
s32 fn_3_1E724(void) {
    if (g_GameLogic.secondaryGameMode == 0xD) {
        return fn_3_B0CF4() != 0;
    }
    if (g_AiLogic.batterAIBuntInd != 1) {
        return 0;
    }
    if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
        return 0;
    }
    if (g_Ball.pitchHangtimeCounter <= 0) {
        return 1;
    }
    if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition) {
        if (fn_3_1E7F4() == 0) {
            g_AiLogic.aISwingDecisionRelated_noSwingOverride = 1;
            return 0;
        }
    }
    return 1;
}

// .text:0x0001E7F4 size:0x2B4 mapped:0x8065D888
s32 fn_3_1E7F4(void) {
    s32 k;
    s32 zone;
    s32 chance;
    u8 t;
    t = g_Pitcher.starPitchType;
    if (t == 3 || t == 4) {
        k = 0;
    } else if (t == 11 || t == 12) {
        k = 0;
    } else if (t == 1 || t == 2) {
        k = 0;
    } else {
        for (zone = 0; zone < 4; zone++) {
            if (g_Pitcher.pitchXPosition < lbl_3_data_19CC[zone]) {
                break;
            }
        }
        if (g_Batter.batterHand != 0) {
            zone = 4 - zone;
        }
        if (zone == 1 || zone == 3) {
            k = 1;
        } else if (zone == 2) {
            k = 0;
        } else {
            k = 2;
        }
        if (g_AiLogic.batterAIBuntInd != 1) {
            if (g_AiLogic.aIBatterTrackingCode != 0 || k == 0 || g_AiLogic.lastPitchBallLocZone == zone) {
                if (g_AiLogic.batterAISwingEarly1OrLate2 == 0) {
                    chance = (lbl_3_data_1ADC + g_AiLogic.aIBatterDifficulty)[4];
                } else {
                    chance = (lbl_3_data_1ADC + g_AiLogic.aIBatterDifficulty)[0xC];
                }
            } else {
                if (g_AiLogic.batterAISwingEarly1OrLate2 == 0) {
                    chance = (lbl_3_data_1ADC + g_AiLogic.aIBatterDifficulty)[0];
                } else {
                    chance = (lbl_3_data_1ADC + g_AiLogic.aIBatterDifficulty)[8];
                }
            }
            if (RandomInt_Game(100) >= chance) {
                return 0;
            }
        }
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        k = (lbl_3_data_1AEC + k * 16 + g_Batter.characterClass * 4 + g_AiLogic.aIBatterDifficulty)[0x30];
    } else {
        k = (lbl_3_data_1AEC + k * 16 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty];
    }
    chance = k;
    if (g_AiLogic.batterAIBuntInd == 1) {
        chance += lbl_3_data_1B4C[0];
    } else if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 2) {
        chance += lbl_3_data_1B4C[1];
    }
    return RandomInt_Game(100) < chance;
}

// .text:0x0001EAA8 size:0x53C mapped:0x8065DB3C
void fn_3_1EAA8(void) {
    int jitter;
    int late;
    int r;
    u8 frame;
    s8* range;
    int f1;
    int f2;

    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 3) {
        return;
    }
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 0) {
        jitter = RandomIndexFromWeights(lbl_3_data_1B50 + g_AiLogic.aIBatterDifficulty * 0x12, 9);
        late = 0;
    } else {
        jitter = RandomIndexFromWeights(lbl_3_data_1B50 + g_AiLogic.aIBatterDifficulty * 0x12 + 9, 9);
        late = 1;
    }
    frame = g_Pitcher.framesUntilBallReachesBatterZ + g_Ball.pitchHangtimeCounter - swingSoundFrame[late][1];
    g_AiLogic.frameToStartSwing = frame;
    g_AiLogic.aIDesiredFrameToSwing = frame;
    jitter += frame;
    g_AiLogic.frameToStartSwing = jitter - 4;
    if ((g_Pitcher.starPitchType == 7 || g_Pitcher.starPitchType == 8) && RandomInt_Game(100) >= lbl_3_data_1BD4[g_AiLogic.aIBatterDifficulty]) {
        g_AiLogic.frameToStartSwing += g_Pitcher.bulletPitchLoopFrames;
    }
    if (g_Pitcher.starPitchType == 1 || g_Pitcher.starPitchType == 2) {
        r = RandomInt_Game_Range(lbl_3_data_1BC4[g_AiLogic.aIBatterDifficulty * 2], lbl_3_data_1BC4[g_AiLogic.aIBatterDifficulty * 2 + 1]);
        if (r > 5) {
            r = 5;
        }
        g_AiLogic.frameToStartSwing += r;
    } else if (g_Pitcher.starPitchType == 11 || g_Pitcher.starPitchType == 12) {
        g_AiLogic.frameToStartSwing += RandomInt_Game_Range(lbl_3_data_1BBC[g_AiLogic.aIBatterDifficulty * 2], lbl_3_data_1BBC[g_AiLogic.aIBatterDifficulty * 2 + 1]);
    } else if (g_Pitcher.starPitchType == 9 || g_Pitcher.starPitchType == 10) {
        g_AiLogic.frameToStartSwing += RandomInt_Game_Range(lbl_3_data_1BCC[g_AiLogic.aIBatterDifficulty * 2], lbl_3_data_1BCC[g_AiLogic.aIBatterDifficulty * 2 + 1]);
    } else if (g_AiLogic.batterAISwingEarly1OrLate2 == 0) {
        if (RandomInt_Game(100) < (lbl_3_data_1B98 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty]) {
            g_AiLogic.frameToStartSwing += lbl_3_data_1BA8[g_AiLogic.aIBatterDifficulty];
        }
    } else {
        range = lbl_3_data_1BAC + (g_AiLogic.batterAISwingEarly1OrLate2 != 1) * 8;
        g_AiLogic.frameToStartSwing += RandomInt_Game_Range(range[g_AiLogic.aIBatterDifficulty * 2], range[g_AiLogic.aIBatterDifficulty * 2 + 1]);
    }
    g_AiLogic.batterAILeftRightInput = RandomIndexFromWeights(lbl_3_data_1BD8 + g_Batter.characterClass * 3, 3);
    if (g_d_GameSettings.GameModeSelected == 6) {
        f1 = g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[1]];
        f2 = g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[2]];
        if (g_Fielders[f1].x < 0.0f && g_Fielders[f2].x < 0.0f) {
            if (g_Batter.batterHand != 0) {
                g_AiLogic.batterAILeftRightInput = 0;
            } else {
                g_AiLogic.batterAILeftRightInput = 2;
            }
        } else if (g_Fielders[f1].x > 0.0f && g_Fielders[f2].x > 0.0f) {
            if (g_Batter.batterHand != 0) {
                g_AiLogic.batterAILeftRightInput = 2;
            } else {
                g_AiLogic.batterAILeftRightInput = 0;
            }
        } else {
            r = fn_3_E587C();
            if (r >= 4) {
                if (g_Batter.batterHand != 0) {
                    g_AiLogic.batterAILeftRightInput = 0;
                } else {
                    g_AiLogic.batterAILeftRightInput = 2;
                }
            } else if (r != 3 && r >= 0) {
                if (g_Batter.batterHand != 0) {
                    g_AiLogic.batterAILeftRightInput = 2;
                } else {
                    g_AiLogic.batterAILeftRightInput = 0;
                }
            }
        }
    } else if (g_Strikes.outs <= 1 && (g_RunningLogic.occupiedBases & 0x1000) && g_AiLogic.aIBatterDifficulty >= 1) {
        if (g_Batter.characterClass == 1) {
            g_AiLogic.batterAIUpDownInput = RandomIndexFromWeights(lbl_3_data_1BF0 + g_AiLogic.aIBatterDifficulty * 3, 3);
        } else {
            g_AiLogic.batterAIUpDownInput = RandomIndexFromWeights(lbl_3_data_1BF0 + g_AiLogic.aIBatterDifficulty * 3 + 0xC, 3);
        }
    } else {
        g_AiLogic.batterAIUpDownInput = RandomIndexFromWeights(lbl_3_data_1BE4 + g_Batter.characterClass * 3, 3);
    }
}

// .text:0x0001EFE4 size:0x1E8 mapped:0x8065E078
s32 fn_3_1EFE4(void) {
    s32 v;
    s32 t;
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 3) {
        return 0;
    }
    if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 1) {
        if (g_AiLogic._70 != 0 && g_AiLogic.lastPitchType != 0xFF) {
            s16 windup = // TODO type: windup frames per pitch type at 0x126..0x12A
                ((s16*)&g_Pitcher.windupCountdownUntilBallReleased)[2 - g_AiLogic.lastPitchType];
            v = windup + g_AiLogic.lastPitchFramesUntilPitchGetsToBatter;
            v -= lbl_3_data_19C4[4];
        } else {
            v = g_Pitcher.curvePitchWindupFrames + 0x14;
        }
        t = v - g_Pitcher.pitchTotalTimeCounter;
        t -= g_Batter.frameFullyCharged;
        if (t <= 0 || g_Pitcher.windupCountdownUntilBallReleased < 8) {
            g_Batter.chargeStatus = 1;
            g_Batter.hitGeneralType = 1;
        }
    }
    if (g_Ball.pitchHangtimeCounter <= 0) {
        return 0;
    }
    if (g_AiLogic.batterAISwingInd != 0) {
        return 0;
    }
    if (g_GameLogic.secondaryGameMode == 0xD) {
        fn_3_B0D2C();
    } else {
        if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
            return 0;
        }
        if (g_Ball.pitchHangtimeCounter == 1) {
            fn_3_1EAA8();
        }
        if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition && fn_3_1E7F4() == 0) {
            g_AiLogic.someNotAISwingInd = 1;
        }
        if (g_Ball.pitchHangtimeCounter == g_AiLogic.frameToStartSwing + 1 && g_AiLogic.frameToStartSwing != 0 && g_AiLogic.someNotAISwingInd == 0) {
            g_AiLogic.batterAISwingInd = 1;
        }
    }
    return g_AiLogic.batterAISwingInd != 0;
}

// .text:0x0001F1CC size:0x184 mapped:0x8065E260
void fn_3_1F1CC(void) {
    f32 r;
    if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 3) {
        g_AiLogic.batterAIDesiredXPosInBox = g_AiLogic.boxHorizontalPoint;
        return;
    }
    if (g_Batter.characterClass == 2) {
        if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch != 1) {
            if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 2 && g_AiLogic._6B != 0) {
                g_AiLogic._6B -= 1;
                return;
            }
            g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[0], lbl_3_data_19DC[9]);
            r = RandomF32_Game_Range(lbl_3_data_1A04[1], lbl_3_data_1A04[0] + lbl_3_data_1A04[0]);
            if (RandomInt_Game(2) != 0) {
                g_AiLogic.batterAIDesiredXPosInBox += r;
            } else {
                g_AiLogic.batterAIDesiredXPosInBox -= r;
            }
            if (g_AiLogic.batterAIDesiredXPosInBox < -lbl_3_data_1A04[0]) {
                g_AiLogic.batterAIDesiredXPosInBox = -lbl_3_data_1A04[0];
            } else if (g_AiLogic.batterAIDesiredXPosInBox > lbl_3_data_1A04[0]) {
                g_AiLogic.batterAIDesiredXPosInBox = lbl_3_data_1A04[0];
            }
            g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
            g_AiLogic._6B = RandomInt_Game(0x2D) + 0xF;
        }
    } else if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 0) {
        g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAIInd9PrincessStarHit * 2 + 2], lbl_3_data_19DC[g_AiLogic.batterAIInd9PrincessStarHit * 2 + 3]);
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
    }
}

// .text:0x0001F350 size:0x128 mapped:0x8065E3E4
void fn_3_1F350(void) {
    if (g_Pitcher.windupCountdownUntilBallReleased == lbl_3_data_1A3C[g_AiLogic.aIBatterDifficulty]) {
        if (g_AiLogic.lastPitchBallLocZone != 0xFF && RandomInt_Game(100) < lbl_3_data_1A24[g_Batter.characterClass]) {
            g_AiLogic.batterAI_GuessedPitchLocZone = g_AiLogic.lastPitchBallLocZone;
            if (g_AiLogic.batterAI_GuessedPitchLocZone == 0) {
                g_AiLogic.batterAI_GuessedPitchLocZone = 1;
            } else if (g_AiLogic.batterAI_GuessedPitchLocZone == 4) {
                g_AiLogic.batterAI_GuessedPitchLocZone = 3;
            }
        } else {
            g_AiLogic.batterAI_GuessedPitchLocZone = RandomIndexFromWeights(lbl_3_data_1A28 + g_Batter.characterClass * 5, 5);
        }
        g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone * 2], lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone * 2 + 1]);
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
    }
}

// .text:0x0001F478 size:0x520 mapped:0x8065E50C
void fn_3_1F478(void) {
    BOOL centered = FALSE;
    int chance;
    int mound;
    f32 step;
    f32 th;
    f32 lo;
    f32 x;

    if (g_Ball.pitchHangtimeCounter < g_AiLogic.batterAIInd8_FrameBtwn10And16) {
        if (g_Pitcher.windupCountdownUntilBallReleased == lbl_3_data_1A3C[g_AiLogic.aIBatterDifficulty]) {
            if (g_AiLogic.lastPitchBallLocZone != 0xFF && RandomInt_Game(100) < lbl_3_data_1A24[g_Batter.characterClass]) {
                g_AiLogic.batterAI_GuessedPitchLocZone = g_AiLogic.lastPitchBallLocZone;
                if (g_AiLogic.batterAI_GuessedPitchLocZone == 0) {
                    g_AiLogic.batterAI_GuessedPitchLocZone = 1;
                } else if (g_AiLogic.batterAI_GuessedPitchLocZone == 4) {
                    g_AiLogic.batterAI_GuessedPitchLocZone = 3;
                }
            } else {
                g_AiLogic.batterAI_GuessedPitchLocZone = RandomIndexFromWeights(lbl_3_data_1A28 + g_Batter.characterClass * 5, 5);
            }
            g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone * 2], lbl_3_data_19DC[g_AiLogic.batterAI_GuessedPitchLocZone * 2 + 1]);
            g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
        }
    } else if (g_Ball.pitchHangtimeCounter == g_AiLogic.batterAIInd8_FrameBtwn10And16) {
        if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
            g_AiLogic._73 = RandomInt_Game(2);
            chance = lbl_3_data_1A40[g_AiLogic.aIBatterDifficulty + 0x14];
        } else if (g_Pitcher.starPitchType == 11 || g_Pitcher.starPitchType == 12) {
            g_AiLogic.batterAITrackBallPoorlyOffset = RandomF32_Game_Range(-lbl_3_data_1AA8, lbl_3_data_1AA8);
            g_AiLogic.aIBatterTrackingCode = 2;
            return;
        } else if (g_Pitcher.pitchXPosition2 >= lbl_3_data_19CC[1] && g_Pitcher.pitchXPosition2 < lbl_3_data_19CC[2]) {
            centered = TRUE;
            chance = lbl_3_data_1A40[g_AiLogic.aIBatterDifficulty + 0x10];
        } else {
            chance = (lbl_3_data_1A40 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty];
        }
        if (RandomInt_Game(100) < chance) {
            lo = lbl_3_data_4474[0];
            step = (lbl_3_data_4474[1] - lo) / 5.0f;
            th = lo + step;
            for (mound = 0; mound < 4; mound++) {
                if (g_Pitcher.pitcher.x < th) {
                    break;
                }
                th += step;
            }
            if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
                chance = (lbl_3_data_1A58 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty];
            } else if (centered) {
                chance = (lbl_3_data_1A58 + g_Batter.characterClass * 4 + g_AiLogic.aIBatterDifficulty)[0x20];
            } else if (g_AiLogic.lastPitchMoundZone == mound) {
                chance = (lbl_3_data_1A58 + g_Batter.characterClass * 4 + g_AiLogic.aIBatterDifficulty)[0x10];
            } else {
                chance = (lbl_3_data_1A58 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty];
            }
            if (RandomInt_Game(100) < chance) {
                g_AiLogic.batterAITrackBallPoorlyOffset = RandomF32_Game_Range(lbl_3_data_1A88[g_AiLogic.aIBatterDifficulty * 2], lbl_3_data_1A88[g_AiLogic.aIBatterDifficulty * 2 + 1]);
                if (RandomInt_Game(2) != 0) {
                    g_AiLogic.batterAITrackBallPoorlyOffset = -g_AiLogic.batterAITrackBallPoorlyOffset;
                }
                g_AiLogic.aIBatterTrackingCode = 1;
            } else {
                g_AiLogic.aIBatterTrackingCode = 2;
                g_AiLogic.batterAITrackBallPoorlyOffset = 0.0f;
            }
        }
    } else if (g_AiLogic.aIBatterTrackingCode != 0) {
        if (g_Pitcher.starPitchType == 11 || g_Pitcher.starPitchType == 12) {
            g_AiLogic.batterAIDesiredXPosInBox = g_AiLogic.batterAITrackBallPoorlyOffset;
            return;
        }
        x = g_Pitcher.pitchXPosition;
        if (g_Pitcher.starPitchType == 3 || g_Pitcher.starPitchType == 4) {
            if (g_Pitcher.warioWaluStarPitchRightLeft == 0) {
                x += lbl_3_data_5EB8;
            } else {
                x -= lbl_3_data_5EB8;
            }
            if (g_AiLogic._73 == 0) {
                x = -x;
            }
        }
        if (g_Batter.batterHand != 0) {
            g_AiLogic.batterAIDesiredXPosInBox = -x - g_AiLogic.batterAITrackBallPoorlyOffset;
        } else {
            g_AiLogic.batterAIDesiredXPosInBox = x + g_AiLogic.batterAITrackBallPoorlyOffset;
        }
    }
}

// .text:0x0001F998 size:0x3F4 mapped:0x8065EA2C
void fn_3_1F998(void) {
    BatterReachStruct* reach = &BatterHitbox[g_Batter.charID];
    f32* speed = lbl_3_data_1A0C;
    f32 r;
    f32 x;

    if (g_GameLogic.secondaryGameMode == 0xD) {
        return;
    }
    if (g_Pitcher.windupCountdownUntilBallReleased <= lbl_3_data_1A3C[g_AiLogic.aIBatterDifficulty]) {
        fn_3_1F478();
    } else if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 3) {
        g_AiLogic.batterAIDesiredXPosInBox = g_AiLogic.boxHorizontalPoint;
    } else if (g_Batter.characterClass == 2) {
        if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch != 1) {
            if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 2 && g_AiLogic._6B != 0) {
                g_AiLogic._6B -= 1;
            } else {
                g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[0], lbl_3_data_19DC[9]);
                r = RandomF32_Game_Range(lbl_3_data_1A04[1], lbl_3_data_1A04[0] + lbl_3_data_1A04[0]);
                if (RandomInt_Game(2) != 0) {
                    g_AiLogic.batterAIDesiredXPosInBox += r;
                } else {
                    g_AiLogic.batterAIDesiredXPosInBox -= r;
                }
                if (g_AiLogic.batterAIDesiredXPosInBox < -lbl_3_data_1A04[0]) {
                    g_AiLogic.batterAIDesiredXPosInBox = -lbl_3_data_1A04[0];
                } else if (g_AiLogic.batterAIDesiredXPosInBox > lbl_3_data_1A04[0]) {
                    g_AiLogic.batterAIDesiredXPosInBox = lbl_3_data_1A04[0];
                }
                g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
                g_AiLogic._6B = RandomInt_Game(0x2D) + 0xF;
            }
        }
    } else if (g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch == 0) {
        g_AiLogic.batterAIDesiredXPosInBox = RandomF32_Game_Range(lbl_3_data_19DC[g_AiLogic.batterAIInd9PrincessStarHit * 2 + 2], lbl_3_data_19DC[g_AiLogic.batterAIInd9PrincessStarHit * 2 + 3]);
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 1;
    }

    if (g_AiLogic.batterAIDesiredXPosInBox < g_AiLogic.boxHorizontalPoint) {
        g_AiLogic.batterAIBoxPosXVelo -= speed[1];
        if (g_AiLogic.batterAIBoxPosXVelo < -speed[0]) {
            g_AiLogic.batterAIBoxPosXVelo = -speed[0];
        }
        g_AiLogic.boxHorizontalPoint += g_AiLogic.batterAIBoxPosXVelo;
        if (g_AiLogic.batterAIDesiredXPosInBox > g_AiLogic.boxHorizontalPoint) {
            g_AiLogic.boxHorizontalPoint = g_AiLogic.batterAIDesiredXPosInBox;
        }
    } else if (g_AiLogic.batterAIDesiredXPosInBox > g_AiLogic.boxHorizontalPoint) {
        g_AiLogic.batterAIBoxPosXVelo += speed[1];
        if (g_AiLogic.batterAIBoxPosXVelo > speed[0]) {
            g_AiLogic.batterAIBoxPosXVelo = speed[0];
        }
        g_AiLogic.boxHorizontalPoint += g_AiLogic.batterAIBoxPosXVelo;
        if (g_AiLogic.batterAIDesiredXPosInBox < g_AiLogic.boxHorizontalPoint) {
            g_AiLogic.boxHorizontalPoint = g_AiLogic.batterAIDesiredXPosInBox;
        }
    } else {
        g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 2;
        g_AiLogic.batterAIBoxPosXVelo = 0.0f;
    }
    if (g_AiLogic.boxHorizontalPoint < reach->HorizontalRangeNear) {
        g_AiLogic.boxHorizontalPoint = reach->HorizontalRangeNear;
    }
    if (g_AiLogic.boxHorizontalPoint > reach->HorizontalRangeFar) {
        g_AiLogic.boxHorizontalPoint = reach->HorizontalRangeFar;
    }

    if (g_AiLogic.batterAIDesiredZPosInBox < g_AiLogic.boxVerticalPoint) {
        g_AiLogic.batterAIBoxPosZVelo -= speed[1];
        if (g_AiLogic.batterAIBoxPosZVelo < -speed[0]) {
            g_AiLogic.batterAIBoxPosZVelo = -speed[0];
        }
        g_AiLogic.boxVerticalPoint += g_AiLogic.batterAIBoxPosZVelo;
        if (g_AiLogic.batterAIDesiredZPosInBox > g_AiLogic.boxVerticalPoint) {
            g_AiLogic.boxVerticalPoint = g_AiLogic.batterAIDesiredZPosInBox;
        }
    } else if (g_AiLogic.batterAIDesiredZPosInBox > g_AiLogic.boxVerticalPoint) {
        g_AiLogic.batterAIBoxPosZVelo += speed[1];
        if (g_AiLogic.batterAIBoxPosZVelo > speed[0]) {
            g_AiLogic.batterAIBoxPosZVelo = speed[0];
        }
        g_AiLogic.boxVerticalPoint += g_AiLogic.batterAIBoxPosZVelo;
        if (g_AiLogic.batterAIDesiredZPosInBox < g_AiLogic.boxVerticalPoint) {
            g_AiLogic.boxVerticalPoint = g_AiLogic.batterAIDesiredZPosInBox;
        }
    } else {
        g_AiLogic.batterAIBoxPosZVelo = 0.0f;
    }
    if (g_AiLogic.boxVerticalPoint < reach->VerticalRangeFront) {
        g_AiLogic.boxVerticalPoint = reach->VerticalRangeFront;
    }
    if (g_AiLogic.boxVerticalPoint > reach->VerticalRangeBack) {
        g_AiLogic.boxVerticalPoint = reach->VerticalRangeBack;
    }

    {
        f32 v;
        f32 h;
        h = g_AiLogic.boxHorizontalPoint;
        v = g_AiLogic.boxVerticalPoint;
        x = h + reach->batOffsetFromBatterX;
        g_Batter.batPosition2.x = h;
        g_Batter.batPosition2.z = v;
        g_Batter.batterPos.x = x;
        g_Batter.batterPos.z = v + reach->batOffsetFromBatterZ;
    }
    if (g_Batter.batterHand != 0) {
        g_Batter.batterPos.x = -x;
    }
}

// .text:0x0001FD8C size:0x1BC mapped:0x8065EE20
void batterAIControlled(void) {
    s32 r;
    if (g_Batter.swingInd == 0 && g_Batter.buntStatus == 0) {
        if (fn_3_1EFE4() != 0) {
            g_Batter.swingInd = 1;
            g_Batter.framesSinceStartOfSwing = 0;
        }
    }
    if (g_Batter.swingInd == 0 && g_Batter.buntStatus != 3) {
        fn_3_1F998();
    }
    if (g_Batter.swingInd == 0 && g_Batter.buntStatus != 3 && g_Batter.buntStatus != 6) {
        if (g_GameLogic.secondaryGameMode == 0xD) {
            if (fn_3_B0CF4() != 0) {
                r = 1;
            } else {
                r = 0;
            }
        } else if (g_AiLogic.batterAIBuntInd != 1) {
            r = 0;
        } else if (g_AiLogic.aISwingDecisionRelated_noSwingOverride != 0) {
            r = 0;
        } else if (g_Ball.pitchHangtimeCounter <= 0) {
            r = 1;
        } else if (g_Pitcher.framesUntilBallReachesBatterZ == g_AiLogic.batterAIZPosition && fn_3_1E7F4() == 0) {
            r = 0;
            g_AiLogic.aISwingDecisionRelated_noSwingOverride = 1;
        } else {
            r = 1;
        }
        if (r != 0) {
            g_Batter.isBunting = 1;
            g_Batter.hitGeneralType = 3;
            if (g_Batter.buntStatus == 0) {
                g_Batter.buntStatus = 1;
                g_Batter.framesBuntHeld = 0;
            }
        } else {
            g_Batter.isBunting = 0;
        }
    }
}

// .text:0x0001FF48 size:0x11C mapped:0x8065EFDC
void fn_3_1FF48(void) {
    int zone;
    int mound;
    f32 step;
    f32 th;
    f32 lo;
    if (g_Pitcher.starPitchType != 0) {
        return;
    }
    g_AiLogic.lastPitchFramesUntilPitchGetsToBatter = g_Pitcher.framesUntilPitchGetsToBatter;
    g_AiLogic.lastPitchType = g_Pitcher.TypeOfPitch;
    for (zone = 0; zone < 4; zone++) {
        if (g_Pitcher.pitchXPosition < lbl_3_data_19CC[zone]) {
            break;
        }
    }
    if (g_Batter.batterHand != 0) {
        zone = 4 - zone;
    }
    g_AiLogic.lastPitchBallLocZone = zone;
    lo = lbl_3_data_4474[0];
    step = (lbl_3_data_4474[1] - lo) / 5.0f;
    th = lo + step;
    for (mound = 0; mound < 4; mound++) {
        if (g_Pitcher.pitcher.x < th) {
            break;
        }
        th += step;
    }
    g_AiLogic.lastPitchMoundZone = mound;
}

// .text:0x00020064 size:0x124 mapped:0x8065F0F8
void fn_3_20064(void) {
    u8 t;
    g_AiLogic.batterAITrackBallPoorlyOffset = 0.0f;
    if (g_Pitcher.starPitchType == 0) {
        t = g_Pitcher.TypeOfPitch;
        if (t == 0) {
            g_AiLogic.batterAISwingEarly1OrLate2 = 0;
        } else if (g_AiLogic.batterAIPitchGuessed != t) {
            if (t == 1) {
                if (RandomInt_Game(0x64) < (s32)(lbl_3_data_1ABC + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty]) {
                    g_AiLogic.batterAISwingEarly1OrLate2 = 0;
                } else {
                    g_AiLogic.batterAISwingEarly1OrLate2 = 1;
                }
            } else {
                if (RandomInt_Game(0x64) < (s32)(lbl_3_data_1ABC + g_Batter.characterClass * 4 + g_AiLogic.aIBatterDifficulty)[0x10]) {
                    g_AiLogic.batterAISwingEarly1OrLate2 = 0;
                } else {
                    g_AiLogic.batterAISwingEarly1OrLate2 = 2;
                }
            }
        } else {
            g_AiLogic.batterAISwingEarly1OrLate2 = 0;
        }
    }
}

// .text:0x00020188 size:0x9C mapped:0x8065F21C
void fn_3_20188(void) {
    if (g_AiLogic.lastPitchType != 0xFF && RandomInt_Game(0x64) < (s32)lbl_3_data_1AAC[g_AiLogic.aIBatterDifficulty]) {
        g_AiLogic.batterAIPitchGuessed = g_AiLogic.lastPitchType;
        return;
    }
    g_AiLogic.batterAIPitchGuessed = RandomIndexFromWeights(lbl_3_data_1AB0 + g_Pitcher.charClass * 3, 3);
}

// .text:0x00020224 size:0x83C mapped:0x8065F2B8
// NONMATCHING 96.8%: g_GameLogic/g_AiLogic base registers r29/r30 swapped, and the batterAIZPosition block is scheduled differently
#if NONMATCHING
void fn_3_20224(void) {
    int situation;
    int r;
    int count;
    u8* odds;
    u32 d;
    s32 n;
    s32 ri;
    f32 chance;
    u8 sp;
    int bunt;
    u8 lo;
    s16 fl;

    if (g_Batter.aiControlledInd != 0) {
        if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceType_2 != 4) {
            g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 0;
            g_AiLogic.batterAIInd9PrincessStarHit = 1;
            g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 3;
        } else {
            g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 0;
            g_AiLogic.aIBatterDifficulty = lbl_3_data_193C[g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam]];
            if (g_d_GameSettings.minigamesEnabled == 0 && g_GameLogic.freeFieldingPracticeInd == 0) {
                if (g_AiLogic.batterAIABStrat < 0) {
                    g_AiLogic.batterAIABStrat = 0;
                    if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] != 0) {
                        situation = -1;
                        if (g_Scores.inning >= g_Scores.maxInnings && g_Strikes.outs == 2 && g_Scores._A6 != 0) {
                            situation = 0;
                        } else if ((g_RunningLogic._00 & 0x1000) || g_RunningLogic._10 >= 3) {
                            situation = 1;
                        } else if (g_Scores._AC >= 2 && g_Scores._A6 <= 1 && g_AiLogic.starRelated[g_GameLogic.homeTeamBattingInd_fieldingTeam] == 0) {
                            situation = 2;
                        }
                        if (situation >= 0 && RandomInt_Game(100) < (lbl_3_data_1944 + situation * 0x18 + g_AiLogic.aIBatterDifficulty * 6)[g_GameLogic.TeamStars[g_GameLogic.teamBatting]]) {
                            g_AiLogic.batterAIABStrat = 1;
                        }
                    }
                }
                if (g_AiLogic.batterAIABStrat != 0) {
                    r = RandomInt_Game(100);
                    if (g_Pitcher.nPitchesThisAB == 0) {
                        count = 0;
                    } else if (g_Pitcher.nPitchesThisAB >= 6) {
                        count = 4;
                    } else if (g_Strikes.strikes == 0) {
                        count = 1;
                    } else if (g_Strikes.strikes == 1) {
                        count = 2;
                    } else {
                        count = 3;
                    }
                    odds = lbl_3_data_198C + g_AiLogic.aIBatterDifficulty * 10;
                    if (r < odds[count * 2]) {
                        g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 2;
                    } else if (r - odds[count * 2] < odds[count * 2 + 1]) {
                        g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 0;
                    } else {
                        g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 3;
                    }
                }
            }
            if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 2) {
                g_Batter.isStarSwing = 1;
            } else {
                g_Batter.isStarSwing = 0;
            }
            if (g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch == 0) {
                g_AiLogic._70 = 0;
                if (RandomInt_Game(100) < (lbl_3_data_19B4 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty]) {
                    g_AiLogic.batterAIPotentialSwingTypeForCurrentPitch = 1;
                    if (g_AiLogic.lastPitchFramesUntilPitchGetsToBatter != 0 && RandomInt_Game(100) < lbl_3_data_19C4[g_AiLogic.aIBatterDifficulty]) {
                        g_AiLogic._70 = 1;
                    }
                }
            }
            if (g_AiLogic.batterAIBuntPossibility != 0) {
                g_AiLogic.batterAIBuntPossibility = 0;
                g_AiLogic.batterAIBuntInd = 0;
                if (g_Scores._A6 <= 2 && g_Scores._AC >= 2 && g_Strikes.outs <= 1 &&
                    (g_RunningLogic.occupiedBases == 0x11 || g_RunningLogic.occupiedBases == 0x111) &&
                    RandomInt_Game(100) < (lbl_3_data_1C10 + g_Batter.characterClass * 4)[g_AiLogic.aIBatterDifficulty]) {
                    g_AiLogic.batterAIBuntInd = 1;
                }
            }

            // inlined fn_3_1E4B8
            g_AiLogic.batterAIStealIndicator = 0;
            r = RandomInt_Game(100);
            d = g_GameLogic.AIDifficulty0Special3Weak[g_GameLogic.homeTeamBattingInd_fieldingTeam];
            if (r < lbl_3_data_1C90[d]) {
                g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[2] - 1;
            } else {
                g_AiLogic.batterAIStealingStartFrame = lbl_3_data_4B90[3] - 1;
            }
            n = g_Pitcher.nPitchesThisAB;
            if (n > 2) {
                n = 2;
            }
            fl = g_RunningLogic.occupiedBases;
            if (fl & 0x100) {
                if (fl & 0x1000) {
                    goto steal_done;
                }
                ri = 2;
                chance = (lbl_3_data_1C98 + d * 12 + n * 4 + g_Runners[2].characterClass)[0x3C];
            } else if (fl & 0x10) {
                ri = 1;
                chance = (lbl_3_data_1C98 + d * 12 + n * 4 + g_Runners[1].characterClass)[0x3C];
            } else {
                goto steal_done;
            }
            chance *= lbl_3_data_1D10[g_Batter.characterClass];
            if (g_Strikes.balls == 3) {
                chance *= lbl_3_data_1D10[4];
            }
            sp = g_Runners[ri].speed;
            if (sp >= 0x32) {
                chance *= lbl_3_data_1D10[5] * (f32)((sp - 0x32) / 10) + 1.0f;
            }
            if (RandomInt_Game(100) < (s32)chance) {
                g_AiLogic.batterAIStealIndicator = 1;
            }
        steal_done:
            bunt = 0;
            if (g_AiLogic.batterAIBuntInd == 1) {
                bunt = 1;
            }
            lo = lbl_3_data_1C08[bunt * 2];
            g_AiLogic.batterAIZPosition = (s32)((lbl_3_data_1C08[bunt * 2 + 1] - lo) * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]) + lo;
            g_AiLogic.batterAIInd8_FrameBtwn10And16 = lbl_3_data_1C0C[0] + (s32)((lbl_3_data_1C0C[1] - lbl_3_data_1C0C[0]) * g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.homeTeamBattingInd_fieldingTeam]);
            g_AiLogic.batterAIInd9PrincessStarHit = RandomIndexFromWeights(lbl_3_data_1A14 + g_Batter.characterClass * 3, 3);
            g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 0;
            if (RandomInt_Game(100) < lbl_3_data_1A20[g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 3;
            }
            if (g_d_GameSettings.GameModeSelected == 6) {
                g_AiLogic.batterAIInd10_relatedToBoxPosPrePitch = 3;
            }
            // inlined fn_3_20188
            if (g_AiLogic.lastPitchType != 0xFF && RandomInt_Game(100) < lbl_3_data_1AAC[g_AiLogic.aIBatterDifficulty]) {
                g_AiLogic.batterAIPitchGuessed = g_AiLogic.lastPitchType;
            } else {
                g_AiLogic.batterAIPitchGuessed = RandomIndexFromWeights(lbl_3_data_1AB0 + g_Pitcher.charClass * 3, 3);
            }
        }
    }
    g_AiLogic.batterAISwingInd = 0;
    g_AiLogic.batterAIBoxPosXVelo = 0.0f;
    g_AiLogic.batterAIBoxPosZVelo = 0.0f;
    g_AiLogic.someNotAISwingInd = 0;
    g_AiLogic.aISwingDecisionRelated_noSwingOverride = 0;
    g_AiLogic.aIBatterTrackingCode = 0;
    g_AiLogic.batterAISwingEarly1OrLate2 = 0;
}
#endif
