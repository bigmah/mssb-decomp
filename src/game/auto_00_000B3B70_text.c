#include "game/auto_00_000B3B70_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

#pragma dont_inline on

extern u8 lbl_3_common_bss_34C90[];

extern void fn_3_1DD48(void);
extern void fn_3_5A6D4(u8);

extern u8 lbl_8036E548[];
extern void fn_3_6AEC0(void);
extern void fn_3_8F1C8(void);
extern void fn_3_59338(void);

extern void fn_3_8B318(s32);
extern void fn_3_B6994(void);
extern void fn_3_B6440(void);
extern s32 fn_3_B254C(void);
extern void fn_3_B1DA4(s32, u8);
extern void fn_3_5F720(void);
extern void fn_3_6C0E0(void);
extern u8 g_RunningLogic[];
extern u8 lbl_3_data_FAF4[][4];
extern void fn_3_B5818(void);
extern void fn_3_B51E4(void);
extern void fn_3_B4C40(void);



// fn_3_B5D78, size:0x104
void fn_3_B5D78(void) {
    if (g_Practice.returnToPracticeMenuState != 0) {
        switch ((s32)g_Practice.returnToPracticeMenuState) {
        case 1:
            fn_3_8B318(-1);
            g_Practice.returnToPracticeMenuState = 2;
            lbl_3_common_bss_34C58._2C = 0;
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 1;
            /* fallthrough */
        case 2:
            g_Practice.returnToPracticeMenuState = 3;
            return;
        default:
            fn_800B0A5C_insertQueue((void*)fn_80062A94, 1);
            g_Practice.returnToPracticeMenuState = 0;
            return;
        }
    } else {
        if ((*(u16*)&g_Practice.practiceMenu_framesOnCurrMenuScreen) < 0xFFFEU) {
            (*(u16*)&g_Practice.practiceMenu_framesOnCurrMenuScreen)++;
        } else {
            (*(u16*)&g_Practice.practiceMenu_framesOnCurrMenuScreen) = 0xFFFF;
        }
        switch ((s32)g_Practice.practiceType_1) {
        case 0:
            fn_3_B5818();
            break;
        case 1: case 2: case 3: case 4: case 5:
            fn_3_B51E4();
            break;
        case 6:
            fn_3_B4C40();
            break;
        }
    }
}

// fn_3_B5E7C, size:0x100
void fn_3_B5E7C(void) {
    if (g_Practice.practiceType_2 != 4 && g_Pitcher.pitcherActionState == 4) {
        switch ((s32)g_Practice.practiceLevel) {
        case 0:
            g_Practice.guidedPracticeCounter++;
            break;
        case 1:
            if (g_Pitcher.ChargePitchType >= 2U) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        case 2:
            if (g_Pitcher.TypeOfPitch == 2) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        case 3:
            if (g_Pitcher.starPitchType != 0) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        }
        if (g_Practice.guidedPracticeCounter >= lbl_3_data_FAF4[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
            g_Practice.guidedPracticeCompletionRelated = 1;
        }
        g_Practice.guidedPracticeCompletionRelated2 = 1;
    }
}

// fn_3_B6C9C, size:0xE4
void fn_3_B6C9C(void) {
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator == 0) {
            *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
            goto done;
        }
        goto timer;
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored == 3) {
        g_Practice.guidedPracticeCompletionRelated = 1;
    }
    goto done;
timer:
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) < 0x7FFE) {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) += 1;
    } else {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0x7FFF;
    }
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) >= 60) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        fn_3_1DD48();
        fn_3_5A6D4(7);
        return;
    }
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) == 54) {
        changeScene(3, 6);
    }
done:
    return;
}

// fn_3_B60F0, size:0xD0
void fn_3_B60F0(void) {
    fn_3_5F720();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes * 16);
    g_Strikes.allForcedRunnersReachedTheirBaseInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._10E = 0;
    *(s16*)((u8*)&g_FieldingLogic + 0xEE) = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_RunningLogic[0x13] = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
    fn_3_6C0E0();
}


// fn_3_B6BA4, size:0xAC
void fn_3_B6BA4(void) {
    switch ((s32)g_Practice.tutorialState) {
    case 0:
        fn_3_B6994();
        break;
    case 1:
        fn_3_B6440();
        break;
    case 2:
        if (fn_3_B254C() == 0) {
            fn_3_B6440();
        } else {
            fn_3_B1DA4(g_Practice.practiceLevel, 0);
            fn_3_5A6D4(7);
        }
        break;
    case 3:
        fn_3_B6440();
        break;
    }
    g_GameLogic.TeamStars[1] = 5;
    g_GameLogic.TeamStars[0] = 5;
}

// fn_3_B5CB4, size:0x98
void fn_3_B5CB4(void) {
    PracticeStruct* practice = &g_Practice;
    switch ((s32)practice->returnToPracticeMenuState) {
    case 1:
        fn_3_8B318(-1);
        practice->returnToPracticeMenuState = 2;
        lbl_3_common_bss_34C58._2C = 0;
        lbl_3_common_bss_34C58._2A = 1;
        lbl_3_common_bss_34C58._24 = 1;
        /* fallthrough */
    case 2:
        practice->returnToPracticeMenuState = 3;
        break;
    default:
        fn_800B0A5C_insertQueue((void*)fn_80062A94, 1);
        practice->returnToPracticeMenuState = 0;
        break;
    }
}

// fn_3_B3B70, size:0x60
void fn_3_B3B70(void) {
    g_GameLogic.freeFieldingPracticeInd = 0;
    g_Practice.instructionNumber = -1;
    g_Practice.transitioningIndicator = 0;
    lbl_8036E548[0x307E] = 1;
    lbl_8036E548[0x307A] = 1;
    fn_3_6AEC0();
    fn_3_8F1C8();
    fn_3_59338();
}

// fn_3_B6C50, size:0x4C
void fn_3_B6C50(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}

// fn_3_B7794, size:0x48
void fn_3_B7794(void) {
    ((u8*)&g_Practice)[0x1E8] = 1;
    ((u8*)&g_Practice)[0x1E9] = 1;
    ((u8*)&g_Practice)[0x1EA] = 0;
    ((u8*)&g_Practice)[0x1EB] = 0;
    ((u8*)&g_Practice)[0x1E7] = 0;
    fn_3_B3C78(0);
}

// fn_3_B3C64, size:0x14
void fn_3_B3C64(void) {
    g_GameLogic.framesOfExitingToMenu = 1;
}

// fn_3_B3C78, size:0x1C
void fn_3_B3C78(u8 state) {
    g_Practice.practiceState = 0;
    g_Practice.tutorialState = state;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
}

// fn_3_B3C94, size:0x18
void fn_3_B3C94(u8 state) {
    g_Practice.practiceState = state;
    g_Practice.framesInCurrTransitionState = 0;
}

// fn_3_B3CAC, size:0x28
void fn_3_B3CAC(u8 mode) {
    g_GameLogic.secondaryGameMode = mode;
    g_Practice.totalFrames = 0;
    g_Practice.framesInCurrTransitionState = 0;
    g_Practice.practiceState = 0;
}

// fn_3_B777C, size:0x18
void fn_3_B777C(u8 state) {
    *((u8*)&g_Practice + 0x1E5) = state;
    g_Practice.maybeCommandData[2] = 0;
}

// fn_3_B5D4C, size:0x2C
void fn_3_B5D4C(u8 type) {
    g_Practice.practiceType_1 = type;
    g_Practice.practiceState = 0;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    g_Practice.practiceMenu_framesOnCurrMenuScreen = 0;
    g_Practice.framesInCurrTransitionState = 0;
}

// fn_3_B6B70, size:0x34
void fn_3_B6B70(void) {
    *((u8*)&g_Practice + 0x1DB) = 0;
    fn_3_B3C78(0);
}

// fn_3_B6E98, size:0xD4
void fn_3_B6E98(void) {
    fn_3_5F720();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes * 16);
    g_Strikes.allForcedRunnersReachedTheirBaseInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._10E = 0;
    *(s16*)((u8*)&g_FieldingLogic + 0xEE) = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_RunningLogic[0x13] = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    ((u8*)&g_Practice)[0x1EC] = 0;
    ((u8*)&g_Practice)[0x1ED] = 0;
    changeScene(1, 6);
    fn_3_5A6D4(2);
    fn_3_6C0E0();
}

extern s32 fn_3_B32B8(void);
extern void fn_3_8A958(void);

// fn_3_B6D80, size:0x118
void fn_3_B6D80(void) {
    if (g_Practice.instructionNumber < 0 && fn_3_B32B8() != 0) {
        return;
    }
    fn_3_8A958();
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator == 0) {
            *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
            goto done;
        }
        goto timer;
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored == 3) {
        g_Practice.guidedPracticeCompletionRelated = 1;
    }
    goto done;
timer:
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) < 0x7FFE) {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) += 1;
    } else {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0x7FFF;
    }
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) >= 60) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        fn_3_1DD48();
        fn_3_5A6D4(7);
        return;
    }
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) == 54) {
        changeScene(3, 6);
    }
done:
    return;
}

extern void fn_3_8A4E4(void);
extern void fn_3_6C108(void);
extern void fn_3_6714C(s32);

// fn_3_B6F6C, size:0x110
void fn_3_B6F6C(void) {
    fn_3_8A4E4();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_5F720();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes * 16);
    g_Strikes.allForcedRunnersReachedTheirBaseInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._10E = 0;
    *(s16*)((u8*)&g_FieldingLogic + 0xEE) = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_RunningLogic[0x13] = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    ((u8*)&g_Practice)[0x1EC] = 0;
    ((u8*)&g_Practice)[0x1ED] = 0;
    changeScene(1, 6);
    fn_3_5A6D4(2);
    fn_3_6C0E0();
    fn_3_6714C(0);
}

extern void fn_3_F578(void);
extern void setBatterContactConstants(void);
extern void fn_3_8A350(void);
extern void fn_3_8A1D8(void);
extern void fn_3_58E50(void);
extern void fn_3_58870(void);
extern void fn_3_1E154(void);
extern void fn_3_59A90(void);
extern void fn_3_753E8(s32);

// fn_3_B61C0, size:0x160
void fn_3_B61C0(void) {
    fn_3_F578();
    fn_3_753E8(0);
    setBatterContactConstants();
    fn_3_8A350();
    fn_3_8A1D8();
    fn_3_58E50();
    fn_3_58870();
    fn_3_1E154();
    fn_3_59A90();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    fn_3_5F720();
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + (g_Strikes.strikes * 16);
    g_Strikes.allForcedRunnersReachedTheirBaseInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._10E = 0;
    *(s16*)((u8*)&g_FieldingLogic + 0xEE) = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_RunningLogic[0x13] = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
    fn_3_6C0E0();
    fn_3_6714C(0);
}

extern void fn_3_75560(void);
extern void atBat_batter(void);
extern void fn_3_31594(void);

// fn_3_B5F7C, size:0x174
void fn_3_B5F7C(void) {
    if (g_Practice.instructionNumber < 0 && fn_3_B32B8() != 0) {
        return;
    }
    fn_3_75560();
    if (g_Practice.__0x1e1padding[4] != 0) {
        atBat_batter();
        fn_3_8A958();
    }
    fn_3_31594();
    if (g_Practice.instructionNumber < 0 && g_Practice.guidedPracticeCompletionRelated2 == 0 && g_Practice.practiceType_2 != 4 && g_Pitcher.pitcherActionState == 4) {
        switch ((s32)g_Practice.practiceLevel) {
        case 0:
            g_Practice.guidedPracticeCounter++;
            break;
        case 1:
            if (g_Pitcher.ChargePitchType >= 2U) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        case 2:
            if (g_Pitcher.TypeOfPitch == 2) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        case 3:
            if (g_Pitcher.starPitchType != 0) {
                g_Practice.guidedPracticeCounter++;
            }
            break;
        }
        if (g_Practice.guidedPracticeCounter >= lbl_3_data_FAF4[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
            g_Practice.guidedPracticeCompletionRelated = 1;
        }
        g_Practice.guidedPracticeCompletionRelated2 = 1;
    }
}
