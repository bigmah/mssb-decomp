#include "game/auto_00_000AC9F8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/game_batter.h"
#include "game/rep_1200.h"
#include "game/rep_13B8.h"
#include "game/rep_AC8.h"
#include "game/auto_00_0005985C_text.h"

extern s32 fn_3_B32B8(void);
extern void fn_3_1DD48(void);
extern void ballPhysica(void);
extern void fn_3_598D0(void);
extern void fn_3_B0E00(void);
extern void fn_3_B0B5C(void);
extern void fn_3_B1A30(void);
extern void fn_3_B1578(void);
extern s32 fn_3_B254C(void);
extern void fn_3_B0874(void);
extern void fn_3_B056C(void);
extern void fn_3_AFE0C(void);
extern void fn_3_B003C(void);
extern void fn_3_F578(void);
extern void fn_3_1E154(void);
extern void fn_3_6C108(void);
extern void fn_3_B02A8(void);
extern void fn_3_6714C(s32 player);
extern void fn_3_B3A4C(void);
extern u8 lbl_80366158[];
extern u8 lbl_8037169C[];
extern s16 lbl_3_data_104B8[];

#pragma dont_inline on

extern u8 g_Fielders[];

#include "game/auto_00_000B3B70_text.h"

extern u8 lbl_3_common_bss_34C90[];

// fn_3_AFDA4, size:0x1C
void fn_3_AFDA4(void) {
    lbl_3_common_bss_34C90[0x1D5] = 0;
    lbl_3_common_bss_34C90[0x1D6] = 0;
    lbl_3_common_bss_34C90[0x1D7] = 0;
}

// fn_3_AFD80, size:0x24
void fn_3_AFD80(u8 state) {
    lbl_3_common_bss_34C90[0x1D1] = state;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0xE) = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0x10) = 0;
}

// fn_3_B0A88, size:0x24
void fn_3_B0A88(void) {
    fn_3_B3C78(0);
}

// fn_3_B3A28, size:0x24
void fn_3_B3A28(void) {
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    lbl_3_common_bss_34C90[0x1DA] = 0;
}

// fn_3_B1DA4, size:0x2C
void fn_3_B1DA4(s32 level, u8 value) {
    g_Practice.loadingGuidedPractice = 1;
    g_Practice._1D5 = 0;
    g_Practice.practiceLevel_2 = level;
    *((u8*)&g_Practice + 0x1D7) = value;
    *((u8*)&g_Practice + 0x1D8) = 0;
    g_Practice._188 = 0;
}

// fn_3_B3288, size:0x30
void fn_3_B3288(void) {
    g_Practice.pauseMenuLoading = 0;
    *((u8*)&g_Practice + 0x19F) = 1;
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    lbl_3_common_bss_34C90[0x1DA] = 0;
}

// fn_3_AFD48, size:0x38
s32 fn_3_AFD48(s16 value) {
    if (*(s8*)(lbl_3_common_bss_34C90 + 0x206) <= 0) {
        *(s16*)(lbl_3_common_bss_34C90 + 4) = value;
        *(s16*)(lbl_3_common_bss_34C90 + 6) = value;
        *(s16*)(lbl_3_common_bss_34C90 + 8) = value;
        lbl_3_common_bss_34C90[0x206] = 13;
        return 1;
    }
    return 0;
}

// fn_3_B0CF4, size:0x38
s32 fn_3_B0CF4(void) {
    if (g_Practice.aiBuntIndicator == 0) return 0;
    return g_Ball.pitchHangtimeCounter > 0;
}

// fn_3_B0D7C, size:0x34
void fn_3_B0D7C(void) {
    g_Pitcher.handedness = g_Fielders[0x1C7];
    g_Pitcher.curveBallSpeed = 0x7D;
    g_Pitcher.fastBallSpeed = 0x91;
    g_Pitcher.cursedBallStat = 0x64;
}

// fn_3_B0D78, size:0x4
void fn_3_B0D78(void) {
}

// fn_3_B0D2C, size:0x4C
void fn_3_B0D2C(void) {
    if (g_Practice.aiBuntIndicator == 0 &&
        g_Pitcher.framesUntilUnhittable + 1 == swingSoundFrame[0][1]) {
        g_AiLogic.batterAISwingInd = 1;
    }
}

// fn_3_B1BCC, size:0x48
void fn_3_B1BCC(void) {
    u8* practice = (u8*)&g_Practice;
    practice[0x1DD] = 0;
    practice[0x1DE] = 0;
    practice[0x1DF] = 0;
    practice[0x1E0] = 0;
    g_Practice._1E2 = 0;
    g_Practice.maybeCommandData[0] = 0;
    fn_3_B3C78(0);
}

// fn_3_B025C, size:0x4C
void fn_3_B025C(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        fn_3_75560();
        atBat_batter();
        fn_3_8A958();
        fn_3_31594();
    }
}

// fn_3_AFDC0, size:0x4C
void fn_3_AFDC0(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}

// fn_3_B0DB0, size:0x50
void fn_3_B0DB0(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}

// fn_3_B1120, size:0x4C
void fn_3_B1120(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        ballPhysica();
        fn_3_598D0();
        fn_3_8A958();
        fn_3_B0E00();
    }
}

// fn_3_B116C, size:0x64
void fn_3_B116C(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        if (g_Practice.hitVariablesSetIndicator == 0) {
            fn_3_B0B5C();
        }
        fn_3_75560();
        atBat_batter();
        fn_3_8A958();
        fn_3_31594();
    }
}

// fn_3_B274C, size:0x58
void fn_3_B274C(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        g_Practice.inputs[i].controlStickAngle = -1;
        g_Practice.inputs[i].controlStickMagnitude = 0;
        g_Practice.inputs[i].buttonInput = 0;
        g_Practice.inputs[i].newButtonInput = 0;
        g_Practice.inputs[i]._08 = 0;
        g_Practice.inputs[i].right_left = 0;
        g_Practice.inputs[i].up_down = 0;
        g_Practice.inputs[i].rightTriggerDistance = 0;
        g_Practice.inputs[i].leftTriggerDistance = 0;
    }
}

// fn_3_B1C14, size:0x9C
void fn_3_B1C14(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_B1A30();
        break;
    case 1:
        fn_3_B1578();
        break;
    case 2:
        if (fn_3_B254C() == 0) {
            fn_3_B1578();
        } else {
            fn_3_B1DA4(g_Practice.practiceLevel + 8, 0);
            fn_3_5A6D4(7);
        }
        break;
    case 3:
        fn_3_B1578();
        break;
    }
}

// fn_3_B0AAC, size:0xB0
void fn_3_B0AAC(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_B0874();
        break;
    case 1:
        fn_3_B056C();
        break;
    case 2:
        if (fn_3_B254C() == 0) {
            fn_3_B056C();
        } else {
            fn_3_B1DA4(g_Practice.practiceLevel + 4, 0);
            fn_3_5A6D4(7);
        }
        break;
    case 3:
        fn_3_B056C();
        break;
    }
    g_GameLogic.TeamStars[1] = 5;
    g_GameLogic.TeamStars[0] = 5;
}

// fn_3_B01E0, size:0x7C
void fn_3_B01E0(void) {
    ballPhysica();
    fn_3_598D0();
    if (g_Ball.framesSinceHit == 60) {
        *(f32*)(g_Fielders + 0) = g_Pitcher.pitcherCoord.x;
        *(f32*)(g_Fielders + 8) = g_Pitcher.pitcherCoord.z;
    }
    fn_3_AFE0C();
    if (g_Practice.instructionNumber < 0 &&
        g_Practice.guidedPracticeCompletionRelated2 == 0) {
        fn_3_B003C();
    }
}

// fn_3_B03F0, size:0x74
void fn_3_B03F0(void) {
    fn_3_F578();
    fn_3_753E8(0);
    setBatterContactConstants();
    fn_3_8A1D8();
    fn_3_58E50();
    fn_3_1E154();
    fn_3_59A90();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_GameLogic._125 = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_B02A8();
    fn_3_6714C(0);
}

// fn_3_B254C, size:0xE4
s32 fn_3_B254C(void) {
    if (g_Practice.transitioningIndicator == 0) {
        lbl_80366158[0x28] = 1;
        switch (g_Practice.practiceState) {
        case 0:
            g_Practice.framesInCurrTransitionState = 0;
            g_Practice.practiceState++;
            break;
        case 1:
            if (*(u16*)&g_Practice.framesInCurrTransitionState > 30) {
                changeScene(3, 6);
                g_Practice.practiceState++;
            }
            break;
        case 2:
            if (lbl_8037169C[0x13] != 0) {
                g_Practice.practiceState++;
            }
            break;
        case 3:
            goto complete;
        }
        goto pending;
    }
complete:
    minigamesSetSomePointers();
    fn_3_B3A4C();
    return 1;
pending:
    return 0;
}

// fn_3_B1CB0, size:0xF4
s32 fn_3_B1CB0(void) {
    u8 n;
    InputStruct* c = &g_Controls[g_Practice._192];
    if (g_Practice.loadingGuidedPractice == 0) {
        return 0;
    }
    if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2) {
        return 0;
    }
    if (g_Practice._188 < 0x7FFE) {
        g_Practice._188 += 1;
    } else {
        g_Practice._188 = 0x7FFF;
    }
    if (g_Practice._188 > 0x5A && (c->newButtonInput & 0x1100)) {
        u8* pr = (u8*)&g_Practice;
        n = pr[0x1D8] + 1;
        pr[0x1D8] = n;
        if (n >= 3 || *(s16*)((u8*)lbl_3_data_104B8 + pr[0x1D6] * 0xC + pr[0x1D7] * 6 + n * 2) < 0) {
            g_Practice.loadingGuidedPractice = 0;
        }
    }
    return 1;
}
