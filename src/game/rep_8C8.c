#include "game/rep_8C8.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1838.h"
#pragma dont_inline on
extern s32 fn_3_B0CF4(void);
extern u8 lbl_3_data_1ABC[];
extern u8 lbl_3_data_1AAC[];
extern u8 lbl_3_data_1AB0[];
extern f32 lbl_3_data_19CC[];
extern f32 lbl_3_data_19DC[];
extern f32 lbl_3_data_1A04[];
extern u8 lbl_3_data_1A24[];
extern u8 lbl_3_data_1A28[];
extern u8 lbl_3_data_1A3C[];
extern f32 lbl_3_data_4474[];

// .text:0x0001E4B8 size:0x26C mapped:0x8065D54C
void fn_3_1E4B8(void) {
    return;
}

// .text:0x0001E724 size:0xD0 mapped:0x8065D7B8
s32 fn_3_1E724(void) {
    if (*((u8*)&g_GameLogic + 0x121) == 0xD) {
        return fn_3_B0CF4() != 0;
    }
    if (*((u8*)&g_AiLogic + 0x58) != 1) {
        return 0;
    }
    if (*((u8*)&g_AiLogic + 0x65) != 0) {
        return 0;
    }
    if (*(s16*)((u8*)&g_Ball + 0x1B68) <= 0) {
        return 1;
    }
    if (*(s16*)((u8*)&g_Pitcher + 0x132) == *((u8*)&g_AiLogic + 0x5D)) {
        if (fn_3_1E7F4() == 0) {
            *((u8*)&g_AiLogic + 0x65) = 1;
            return 0;
        }
    }
    return 1;
}

// .text:0x0001E7F4 size:0x2B4 mapped:0x8065D888
s32 fn_3_1E7F4(void) {
    return 0;
}

// .text:0x0001EAA8 size:0x53C mapped:0x8065DB3C
void fn_3_1EAA8(void) {
    return;
}

// .text:0x0001EFE4 size:0x1E8 mapped:0x8065E078
void fn_3_1EFE4(void) {
    return;
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
    return;
}

// .text:0x0001F998 size:0x3F4 mapped:0x8065EA2C
void fn_3_1F998(void) {
    return;
}

// .text:0x0001FD8C size:0x1BC mapped:0x8065EE20
void batterAIControlled(void) {
    return;
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
    if (*(u8*)((u8*)&g_AiLogic + 0x6D) != 0xFF && RandomInt_Game(0x64) < (s32)lbl_3_data_1AAC[*(u8*)((u8*)&g_AiLogic + 0x55)]) {
        *(u8*)((u8*)&g_AiLogic + 0x5E) = *(u8*)((u8*)&g_AiLogic + 0x6D);
        return;
    }
    *(u8*)((u8*)&g_AiLogic + 0x5E) = RandomIndexFromWeights(lbl_3_data_1AB0 + *(u8*)((u8*)&g_Pitcher + 0x149) * 3, 3);
}

// .text:0x00020224 size:0x83C mapped:0x8065F2B8
void fn_3_20224(void) {
    return;
}
