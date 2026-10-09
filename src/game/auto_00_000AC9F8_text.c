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
extern void fn_3_5F720(void);
extern void fn_3_6EBB4(s32);
extern void fn_3_6E24C(s32, s32);
extern void fn_3_6D964(s32, s32);
extern void setInMemBatterConstants(int rosterID);
extern s32 fn_3_6BA64(void);
extern s32 fn_3_B3CD4(void);
extern void fn_3_B4124(s32, s32, s32, u8);
extern void fn_80011BE4(s32);
extern void* lbl_3_data_FDE4[];
extern u8 lbl_3_data_10598[];
extern void fn_3_5B408(void);
extern u8 lbl_3_data_FAE8[];
extern u8 lbl_3_data_FAF4[][4];
extern s16 lbl_3_data_FB04;
extern void fn_3_6E24C(s32, s32);
extern void fn_3_6D964(s32, s32);
extern void setInMemBatterConstants(int rosterID);
extern s32 fn_3_6BA64(void);
extern s32 fn_3_B3CD4(void);
extern void fn_3_B27A4(void);
extern void fn_80011BE4(s32);
extern void* lbl_3_data_101E0[];
extern int random_fn_3_9EE24(int max);
extern s16 lbl_3_data_FB08[][3];
extern s16 lbl_3_data_FB44[][3];
extern s16 lbl_3_data_FB80[][3];
extern s16 lbl_3_data_FBBC[][3];
extern s16 lbl_3_data_FBF8;
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern u8 lbl_800E8754[];
extern void fn_3_59918(s32, s32);
extern u8 lbl_8036E548[];
extern s32 fn_8001C588(s16);
extern s16 lbl_3_data_FC1C[];
extern void fn_3_6C0E0(void);
extern u8 g_RunningLogic[];
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
extern void fn_3_B27A4(void);
extern void fn_3_B1DD0(void);
extern void fn_3_6EBB4(s32);
extern u8 lbl_80366158[];
extern u8 lbl_8037169C[];
extern u8 lbl_80354720[];
extern u8 lbl_80354768[];
extern u8 lbl_800EFBA4[];
extern u8 sndFXStartEx(s32, u8, u8, u8);
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_803CBC3C;
extern void fn_3_BF1AC(void);
extern void fn_3_BF158(void);
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

// fn_3_AFA64, size:0x100
void fn_3_AFA64(void) {
    if (*(s16*)(lbl_3_common_bss_34C90 + 0xC) < 0x7FFE) {
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) += 1;
    } else {
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (*(s16*)(lbl_3_common_bss_34C90 + 0xC) > 0x3C) {
        if (lbl_3_common_bss_34C90[0x1D8] == 0) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                lbl_3_common_bss_34C90[0x1D0] = 2;
            } else {
                lbl_3_common_bss_34C90[0x1D0] = 0;
            }
        } else if (g_d_GameSettings.exhibitionMatchInd == 0) {
            lbl_3_common_bss_34C90[0x1D0] = 3;
        } else {
            lbl_3_common_bss_34C90[0x1D0] = 1;
        }
        lbl_3_common_bss_34C90[0x1D1] = 1;
        lbl_3_common_bss_34C90[0x1D2] = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0xE) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0x10) = 0;
        fn_3_5A6D4(0xB);
        fn_3_BF1AC();
        fn_3_BF158();
        return;
    }
    fn_3_31594();
    fn_3_8A958();
}

// fn_3_AC9F8, size:0x100
void fn_3_AC9F8(void) {
    if (lbl_3_common_bss_32724[0xC3] == 0) {
        if (*(u16*)(lbl_3_common_bss_34C90 + 6) & 0x200) {
            lbl_3_common_bss_34C90[0x1D2] = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected != 6) {
            if ((*(u16*)(lbl_3_common_bss_34C90 + 8) & 1) && lbl_3_common_bss_34C90[0x221] != 0) {
                lbl_3_common_bss_34C90[0x221] -= 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                return;
            }
            if ((*(u16*)(lbl_3_common_bss_34C90 + 8) & 2) && lbl_3_common_bss_34C90[0x221] < lbl_3_common_bss_34C90[0x222] - 1) {
                lbl_3_common_bss_34C90[0x221] += 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

// fn_3_B0464, size:0x108
s32 fn_3_B0464(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return 0;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return 0;
    }
    if (g_UnkSound_32718._07 != 0) {
        return 0;
    }
    g_Practice._186 += 1;
    if (g_Practice._186 > 0x96) {
        u8 (*t)[4] = (u8(*)[4])((u8*)&g_Practice + 0x1B2);
        if (t[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            ((u8*)&g_Practice)[0x1B1] = 1;
            t[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            (lbl_80354768 + 0x10000 + g_Practice.practiceType_2 * 4 + g_Practice.practiceLevel)[-0x30B2] = 1;
        }
        g_Practice._1C7 = 1;
        fn_3_B3A28();
        fn_3_B1DA4(g_Practice.practiceLevel + 4, 1);
        return 1;
    }
    return 0;
}

// fn_3_AEFF8, size:0x114
void fn_3_AEFF8(void) {
    s32 i;
    *(s16*)(lbl_3_common_bss_34C90 + 0x254) = -1;
    *(s16*)(lbl_3_common_bss_34C90 + 0x258) = -1;
    *(s16*)(lbl_3_common_bss_34C90 + 0x256) = -1;
    *(s16*)(lbl_3_common_bss_34C90 + 0x25A) = -1;
    for (i = 0; i < 9; i++) {
        if (*(s8*)(lbl_80354720 + *(s32*)lbl_3_common_bss_34C90 * 0x24 + i * 4 + 2) == 0) {
            *(s16*)(lbl_3_common_bss_34C90 + 0x25C) = i;
        }
        if (*(s8*)(lbl_80354720 + *(s32*)lbl_3_common_bss_34C90 * 0x24 + i * 4 + 2) == 1) {
            *(s16*)(lbl_3_common_bss_34C90 + 0x25E) = i;
        }
    }

}

// fn_3_B2630, size:0x11C
void fn_3_B2630(void) {
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    if (g_Practice.framesOnAllInstructions < 0x7FFE) {
        g_Practice.framesOnAllInstructions += 1;
    } else {
        g_Practice.framesOnAllInstructions = 0x7FFF;
    }
    if (g_Practice.instructionComplete_readyToAdvance == 0 && g_Practice.allInstructionsComplete == 0) {
        if (g_Practice.framesOnCurrInstruction < 0x7FFE) {
            g_Practice.framesOnCurrInstruction += 1;
        } else {
            g_Practice.framesOnCurrInstruction = 0x7FFF;
        }
    }
    if (g_Practice.tutorialState == 1 && (c->newButtonInput & 0x1000)) {
        if (g_Practice.tutorialState != 2) {
            g_Practice.practiceState = 0;
            g_Practice.tutorialState = 2;
            g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        }
    } else if (g_Practice.allInstructionsComplete != 0) {
        if ((c->newButtonInput & 0x100) && g_Practice.tutorialState != 2) {
            g_Practice.practiceState = 0;
            g_Practice.tutorialState = 2;
            g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        }
    } else {
        fn_3_B1DD0();
    }
}

// fn_3_AD2A0, size:0x11C
void fn_3_AD2A0(void) {
    s32 i;
    s32 j;
    s32 first = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0];
    for (i = 0; i < 9; i++) {
        for (j = 1; j < 10; j++) {
            if (i == g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][j][0]) {
                s32 v;
                if (g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][j][1] !=
                    *(s16*)(lbl_3_common_bss_34C90 + 0x242 + i * 2)) {
                    lbl_3_common_bss_34C90[0x260] = 1;
                }
                v = *(s16*)(lbl_3_common_bss_34C90 + 0x242 + i * 2);
                g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][j][1] = v;
                if (v == 0) {
                    g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0] = i;
                    if (first != g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]) {
                        g_GameLogic.playOverInd = 1;
                    }
                }
            }
        }
    }
    fn_3_596F8();
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
}

// fn_3_B1470, size:0x108
s32 fn_3_B1470(void) {
    if (g_Practice.pauseMenuLoading != 0) {
        return 0;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        return 0;
    }
    if (g_UnkSound_32718._07 != 0) {
        return 0;
    }
    g_Practice._186 += 1;
    if (g_Practice._186 > 0x96) {
        u8 (*t)[4] = (u8(*)[4])((u8*)&g_Practice + 0x1B2);
        if (t[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            ((u8*)&g_Practice)[0x1B1] = 1;
            t[g_Practice.practiceType_2][g_Practice.practiceLevel] = 1;
            (lbl_80354768 + 0x10000 + g_Practice.practiceType_2 * 4 + g_Practice.practiceLevel)[-0x30B2] = 1;
        }
        g_Practice._1C7 = 1;
        fn_3_B3A28();
        fn_3_B1DA4(g_Practice.practiceLevel + 8, 1);
        return 1;
    }
    return 0;
}

#pragma dont_inline off
// fn_3_B11D0, size:0x128
void fn_3_B11D0(void) {
    fn_3_5F720();
    g_Pitcher.handedness = g_Fielders[0x1C7];
    g_Pitcher.curveBallSpeed = 0x7D;
    g_Pitcher.fastBallSpeed = 0x91;
    g_Pitcher.cursedBallStat = 0x64;
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
    g_Practice.hitVariablesSetIndicator = 0;
    ((u8*)&g_Practice)[0x1E4] = 0;
    g_Practice._1CB = 0;
    g_Strikes.outs = 0;
    *(s16*)((u8*)&g_Practice + 0x152) = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
    fn_3_6C0E0();
}
#pragma dont_inline on

// fn_3_B02A8, size:0x148
void fn_3_B02A8(void) {
    fn_3_5F720();
    if (g_Practice.practiceLevel == 4) {
        g_Pitcher.windupCountdownUntilBallReleased = lbl_3_data_FC1C[1];
    }
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
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.guidedPracticeCompletionRelated2 = 0;
    ((u8*)&g_Practice)[0x1B0] = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
    fn_3_6C0E0();
    if (lbl_3_common_bss_34C58._2A != 0) {
        lbl_3_common_bss_34C58._2A = 2;
        lbl_3_common_bss_34C58._24 = 0x78;
    }
}

// fn_3_B12F8, size:0x178
void fn_3_B12F8(void) {
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
    fn_3_B11D0();
    fn_3_6714C(0);
}

// fn_3_AF428, size:0x17C
void fn_3_AF428(void) {
    if (*(s16*)(lbl_3_common_bss_34C90 + 0x254) >= 0) {
        if (*(s16*)(lbl_3_common_bss_34C90 + 0x25C) == *(s16*)(lbl_3_common_bss_34C90 + 0x254)) {
            *(s16*)(lbl_3_common_bss_34C90 + 0x254) = -1;
            return;
        }
        if (*(s16*)(lbl_3_common_bss_34C90 + 0x258) < 0) {
            *(s16*)(lbl_3_common_bss_34C90 + 0x258) = *(s16*)(lbl_3_common_bss_34C90 + 0x254);
            lbl_3_common_bss_32724[0x9C] = 0;
            *(s32*)((u8*)&g_GameLogic + g_GameLogic.awayTeamBattingInd_battingTeam * 0x50 + 0x3C) =
                *(s8*)(lbl_80354720 + *(s32*)lbl_3_common_bss_34C90 * 0x24 + *(s16*)(lbl_3_common_bss_34C90 + 0x254) * 4);
            fn_3_750DC();
            return;
        }
        if (fn_3_750DC() != 0) {
            s16 v = *(s16*)(lbl_3_common_bss_34C90 + 0x258);
            *(s16*)(lbl_3_common_bss_34C90 + 0x254) = -1;
            *(s16*)(lbl_3_common_bss_34C90 + 0x25C) = v;
            *(s16*)(lbl_3_common_bss_34C90 + 0x258) = -1;
        }
    } else if (*(s16*)(lbl_3_common_bss_34C90 + 0x256) >= 0) {
        if (*(s16*)(lbl_3_common_bss_34C90 + 0x25E) == *(s16*)(lbl_3_common_bss_34C90 + 0x25A)) {
            *(s16*)(lbl_3_common_bss_34C90 + 0x256) = -1;
            *(s16*)(lbl_3_common_bss_34C90 + 0x25A) = -1;
            return;
        }
        if (*(s16*)(lbl_3_common_bss_34C90 + 0x25A) < 0) {
            *(s16*)(lbl_3_common_bss_34C90 + 0x25A) = *(s16*)(lbl_3_common_bss_34C90 + 0x256);
            ((u8*)&lbl_803CBC3C)[3] = 0;
            return;
        }
        if (fn_8001C588(inMemRoster[*(s32*)lbl_3_common_bss_34C90][*(s8*)(lbl_80354720 + *(s32*)lbl_3_common_bss_34C90 * 0x24 + *(s16*)(lbl_3_common_bss_34C90 + 0x256) * 4)].stats.CharID) != 0) {
            s16 v = *(s16*)(lbl_3_common_bss_34C90 + 0x25A);
            *(s16*)(lbl_3_common_bss_34C90 + 0x256) = -1;
            *(s16*)(lbl_3_common_bss_34C90 + 0x25E) = v;
            *(s16*)(lbl_3_common_bss_34C90 + 0x25A) = -1;
        }
    }
}

// fn_3_B32B8, size:0x190
s32 fn_3_B32B8(void) {
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    if (lbl_8036E548[0x2D46] != 0) {
        return 0;
    }
    if (lbl_8036E548[0x2D52] != 0) {
        return 0;
    }
    if (g_Practice._186 != 0 || g_Practice.guidedPracticeCompletionRelated != 0) {
        return 0;
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0x1E || lbl_8037169C[0x10] != 0) {
        return 0;
    }
    if (g_Practice.pauseMenuLoading != 0) {
        lbl_80366158[0x28] = 1;
        g_Practice.frames_sinceTimeCalled += 1;
        if (g_Practice.frames_sinceTimeCalled >= 0x3C) {
            g_Practice.pauseMenuLoading = 0;
            ((u8*)&g_Practice)[0x19F] = 1;
            g_Practice.frames_onPauseScreen = 0;
            lbl_3_common_bss_34C90[0x1D2] = 0;
            lbl_3_common_bss_34C90[0x1DA] = 0;
        }
        return 1;
    }
    if (g_Practice.practiceType_2 == 4 && g_Pitcher.pitchTotalTimeCounter > 0) {
        return 0;
    }
    if (c->newButtonInput & 0x1000) {
        lbl_80366158[0x28] = 1;
        fn_3_59918(0xE, 0);
        g_Practice.pauseMenuLoading = 1;
        g_Practice.frames_sinceTimeCalled = 0;
        return 1;
    }
    return 0;
}

// fn_3_AE770, size:0x190
void fn_3_AE770(void) {
    s32 i;
    if (*(s16*)(lbl_3_common_bss_34C90 + 0xC) <= 1) {
        ((u8*)&lbl_803CBC3C)[2] = 0;
        fn_80035B50(0x13);
    }
    fn_3_753E8(1);
    setBatterContactConstants();
    for (i = 0; i < 2; i++) {
        if (((u8*)&g_GameLogic)[0x13E + i] == 0) {
            if (lbl_800E8754[g_GameLogic.teams[i] * 7 + 9] != 0) {
                ((u8*)&g_GameLogic)[(*(s32*)&g_GameLogic ^ i) + 0x148] = 1;
            } else {
                ((u8*)&g_GameLogic)[(*(s32*)&g_GameLogic ^ i) + 0x148] = 0;
            }
            if (lbl_800E8754[g_GameLogic.teams[i] * 7 + 0xA] != 0) {
                ((u8*)&g_GameLogic)[(*(s32*)&g_GameLogic ^ i) + 0x142] = 1;
                ((u8*)&g_GameLogic)[(*(s32*)&g_GameLogic ^ i) + 0x144] = 1;
            } else {
                ((u8*)&g_GameLogic)[(*(s32*)&g_GameLogic ^ i) + 0x142] = 0;
                ((u8*)&g_GameLogic)[(*(s32*)&g_GameLogic ^ i) + 0x144] = 0;
            }
        }
    }
    fn_3_FBD70();
    fn_3_FBD58();
    lbl_8036E548[0x307E] = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    changeScene(1, 6);
    fn_3_5A6D4(0);
}

// fn_3_B0B5C, size:0x198
void fn_3_B0B5C(void) {
    if (g_Practice.hitVariablesSetIndicator == 0) {
        g_Practice._152 += 1;
        if (g_Practice._152 >= lbl_3_data_FBF8) {
            if (g_Practice.practiceLevel == 0) {
                s32 k = random_fn_3_9EE24(10);
                g_Ball.Hit_HorizontalPower = lbl_3_data_FB08[k][0];
                g_Ball.Hit_VerticalAngle = lbl_3_data_FB08[k][1];
                g_Ball.Hit_HorizontalAngle = lbl_3_data_FB08[k][2];
            } else if (g_Practice.practiceLevel == 1) {
                s32 k = random_fn_3_9EE24(10);
                g_Ball.Hit_HorizontalPower = lbl_3_data_FB44[k][0];
                g_Ball.Hit_VerticalAngle = lbl_3_data_FB44[k][1];
                g_Ball.Hit_HorizontalAngle = lbl_3_data_FB44[k][2];
            } else if (g_Practice.practiceLevel == 2) {
                s32 k = random_fn_3_9EE24(10);
                g_Ball.Hit_HorizontalPower = lbl_3_data_FB80[k][0];
                g_Ball.Hit_VerticalAngle = lbl_3_data_FB80[k][1];
                g_Ball.Hit_HorizontalAngle = lbl_3_data_FB80[k][2];
            } else if (g_Practice.practiceLevel == 3) {
                s32 k = random_fn_3_9EE24(10);
                g_Ball.Hit_HorizontalPower = lbl_3_data_FBBC[k][0];
                g_Ball.Hit_VerticalAngle = lbl_3_data_FBBC[k][1];
                g_Ball.Hit_HorizontalAngle = lbl_3_data_FBBC[k][2];
            }
            g_Practice.hitVariablesSetIndicator = 1;
            if (g_Practice.maybeCommandData[0] < 0x7FFE) {
                g_Practice.maybeCommandData[0] += 1;
            } else {
                g_Practice.maybeCommandData[0] = 0x7FFF;
            }
        }
    }
}

// fn_3_B1A30, size:0x19C
void fn_3_B1A30(void) {
    switch (g_Practice.practiceState) {
    case 0: {
        s32 i;
        lbl_8036E548[0x307D] = 0;
        fn_3_6EBB4(0);
        fn_3_8A350();
        for (i = 0; i < 9; i++) {
            fn_3_6E24C(i, i);
        }
        setInMemBatterConstants(0);
        fn_3_6D964(0, 0);
        *(s32*)((u8*)&g_GameLogic + 0xDC) = 1;
        *(s32*)((u8*)&g_GameLogic + 0xE0) = 1;
        lbl_3_common_bss_32724[0x9A] = 0;
        lbl_3_common_bss_32724[0x9C] = 0;
        ((u8*)&lbl_803CBC3C)[2] = 0;
        ((u8*)&g_Practice)[0x1A1] = 1;
        ((u8*)&g_Practice)[0x1A2] = 1;
        ((u8*)&g_Practice)[0x1D9] = 0;
        fn_80011BE4(9);
        fn_3_B3C94(1);
        break;
    }
    case 1:
        if (fn_3_6BA64() != 0) {
            fn_3_B3C94(2);
        }
        break;
    case 2:
        if (fn_3_750DC() != 0) {
            fn_3_B3C94(3);
        }
        break;
    case 3:
        if (someAnimationIndFunction() != 0) {
            fn_3_B3C94(4);
        }
        break;
    case 4:
        if (fn_3_B3CD4() != 0) {
            fn_3_B3C94(7);
        }
        break;
    case 7:
        fn_3_B3B70();
        fn_3_B27A4();
        g_Practice.commandList = lbl_3_data_101E0[g_Practice.practiceLevel];
        changeScene(1, 6);
        fn_3_5A6D4(7);
        fn_3_B3C78(1);
        break;
    }
}

// fn_3_B003C, size:0x1A4
void fn_3_B003C(void) {
    if (g_Practice.practiceType_2 != 4 && g_Practice.guidedPracticeCompletionRelated2 == 0) {
        if (g_Ball.deadBallReason != 0) {
            if (g_Ball.framesOnGroundUntilPickedUp == 0 && ((u8*)&g_Practice)[0x1B0] == 0 &&
                *(s16*)((u8*)&g_Ball + 0x1BA4) < lbl_3_data_FB04) {
                return;
            }
            goto count;
        }
        if (g_Ball.framesSinceBallHitGroundOrWasCaught >= lbl_3_data_FB04) {
        count:
            switch (g_Practice.practiceLevel) {
            case 0:
                if (g_Batter.hitGeneralType != 3) {
                    g_Practice.guidedPracticeCounter += 1;
                }
                break;
            case 1:
                if (g_Batter.hitGeneralType == 1 || (g_Batter.hitGeneralType == 2 && g_Batter.moonShotInd != 0)) {
                    g_Practice.guidedPracticeCounter += 1;
                }
                break;
            case 2:
                if (g_Batter.hitGeneralType == 3) {
                    g_Practice.guidedPracticeCounter += 1;
                }
                break;
            case 3:
                if (g_Batter.hitGeneralType == 2 && g_Batter.moonShotInd == 0) {
                    g_Practice.guidedPracticeCounter += 1;
                }
                break;
            }
            if (g_Practice.guidedPracticeCounter >= lbl_3_data_FAF4[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
                g_Practice.guidedPracticeCompletionRelated = 1;
            }
            g_Practice.guidedPracticeCompletionRelated2 = 1;
        }
    }
}

// fn_3_B3448, size:0x1D8
u8 fn_3_B3448(void) {
    s32 row;
    InputStruct* c;
    u16 b;
    u8 r;
    row = 0;
    c = &g_Controls[g_Practice.homeAway];
    if (g_Practice.practiceLevel == 3) {
        row = 1;
    }
    if (c->newButtonInput & 0x100) {
        r = g_Practice.currentMessageDoneTyping;
        if (r != 0) {
            switch ((lbl_3_data_FAE8 + row * 5)[*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) + 1]) {
            case 0:
                lbl_3_common_bss_34C90[0x1D2] = 10;
                break;
            case 1:
                lbl_3_common_bss_34C90[0x1D2] = 4;
                break;
            case 2:
                lbl_3_common_bss_34C90[0x1D2] = 6;
                break;
            case 3:
                fn_3_5B408();
                lbl_3_common_bss_34C90[0x1D2] = 12;
                break;
            }
            r = sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
    } else {
        b = *(u16*)((u8*)c + 8);
        if (b & 4) {
            lbl_3_common_bss_34C90[0x1DA]++;
            if ((s8)lbl_3_common_bss_34C90[0x1DA] >= (s32)lbl_3_data_FAE8[row * 5]) {
                lbl_3_common_bss_34C90[0x1DA] = 0;
            }
            r = sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            r = b & 8;
            if (r != 0) {
                lbl_3_common_bss_34C90[0x1DA]--;
                if ((s8)lbl_3_common_bss_34C90[0x1DA] < 0) {
                    lbl_3_common_bss_34C90[0x1DA] = lbl_3_data_FAE8[row * 5] - 1;
                }
                r = sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    return r;
}

// fn_3_AFB64, size:0x1E4
void fn_3_AFB64(void) {
    u8* u;
    if (lbl_8036E548[0x2D46] == 0 && lbl_8036E548[0x2D52] == 0 && lbl_8036E548[0x2D5E] == 0 &&
        (g_d_GameSettings.exhibitionMatchInd != 0 || lbl_3_common_bss_32724[0xB3] == 0) &&
        g_Pitcher.pitchTotalTimeCounter <= 0 && lbl_3_common_bss_34C90[0x1D5] == 0 && g_Pitcher.pitcherActionState != 2) {
        lbl_3_common_bss_34C90[0x201] = 0;
        if ((lbl_3_common_bss_34C90 + 0x202)[g_GameLogic.teamFielding] != 0) {
            lbl_3_common_bss_34C90[0x1D8] = 0;
            (lbl_3_common_bss_34C90 + 0x202)[g_GameLogic.teamFielding] = 0;
            lbl_3_common_bss_34C90[0x204 + g_GameLogic.teamFielding] = 0;
            goto start;
        }
        if ((lbl_3_common_bss_34C90 + 0x202)[g_GameLogic.teamBatting] != 0) {
            lbl_3_common_bss_34C90[0x1D8] = 1;
            (lbl_3_common_bss_34C90 + 0x202)[g_GameLogic.teamBatting] = 0;
            lbl_3_common_bss_34C90[0x204 + g_GameLogic.teamBatting] = 0;
            goto start;
        }
        u = (u8*)&g_GameLogic + 0x13E;
        if (u[g_GameLogic.teamFielding] == 0 &&
            (g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]].newButtonInput & 0x1000)) {
            lbl_3_common_bss_34C90[0x1D8] = 0;
            goto start;
        }
        if (u[g_GameLogic.teamBatting] == 0 &&
            (g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]].newButtonInput & 0x1000)) {
            lbl_3_common_bss_34C90[0x1D8] = 1;
            goto start;
        }
        return;
    start:
        lbl_3_common_bss_34C90[0x1D5] = 1;
        lbl_3_common_bss_34C90[0x1D1] = 0;
        lbl_3_common_bss_34C90[0x1D2] = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0xE) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0x10) = 0;
        fn_3_59918(0xE, 0);
        lbl_3_common_bss_34C58._2A = 1;
        lbl_3_common_bss_34C58._24 = 0x3B;
    }
}

// fn_3_B28A8, size:0x1F8
void fn_3_B28A8(void) {
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    switch (lbl_3_common_bss_34C90[0x1D3]) {
    case 0:
        lbl_3_common_bss_34C90[0x221] = 1;
        lbl_3_common_bss_34C90[0x222] = 3;
        lbl_3_common_bss_34C90[0x1D9] = 1;
        lbl_3_common_bss_34C90[0x1D3] = 1;
        break;
    case 1:
        if (fn_80035838(lbl_3_data_10598 + 0x20, 0x13) != 0) {
            lbl_3_common_bss_34C90[0x1D3] = 2;
        }
        break;
    case 2:
        if (lbl_3_common_bss_34C90[0x1D9] == 3) {
            lbl_3_common_bss_34C90[0x1D3] = 3;
        }
        break;
    case 3:
        lbl_3_common_bss_34C90[0x1D3] = 4;
        break;
    case 4:
        if (lbl_3_common_bss_32724[0xC3] == 0) {
            lbl_3_common_bss_34C90[0x1D3] = 5;
        }
        break;
    case 5:
        if (lbl_3_common_bss_32724[0xC3] == 0) {
            if (c->newButtonInput & 0x200) {
                lbl_3_common_bss_34C90[0x1D3] = 6;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                return;
            }
            if ((*(u16*)((u8*)c + 8) & 1) && lbl_3_common_bss_34C90[0x221] != 0) {
                lbl_3_common_bss_34C90[0x221] -= 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                return;
            }
            if ((*(u16*)((u8*)c + 8) & 2) && lbl_3_common_bss_34C90[0x221] < lbl_3_common_bss_34C90[0x222] - 1) {
                lbl_3_common_bss_34C90[0x221] += 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        break;
    case 6:
        lbl_3_common_bss_34C90[0x1D3] = 7;
        break;
    case 7:
        if (lbl_3_common_bss_32724[0xC3] == 0) {
            fn_80035B50(0x13);
            lbl_3_common_bss_34C90[0x1D2] = 0;
        }
        break;
    }
}

// fn_3_B0874, size:0x218
void fn_3_B0874(void) {
    switch (g_Practice.practiceState) {
    case 0:
        lbl_8036E548[0x307D] = 0;
        fn_3_8A350();
        if (g_Practice.practiceType_2 == 4) {
            fn_3_B4124(1, 0, ((s8*)((u8*)&g_Minigame + 0x19E8))[g_Practice.homeAway * 9], ((u8*)&g_Minigame)[g_Practice.homeAway + 0x1A17]);
            setInMemBatterConstants(0);
            fn_3_6D964(0, 0);
        } else {
            fn_3_6EBB4(0);
            fn_3_6E24C(0, 0);
            setInMemBatterConstants(0);
            fn_3_6D964(0, 0);
        }
        *(s32*)((u8*)&g_GameLogic + 0xDC) = 1;
        *(s32*)((u8*)&g_GameLogic + 0xE0) = 1;
        lbl_3_common_bss_32724[0x9A] = 0;
        lbl_3_common_bss_32724[0x9C] = 0;
        ((u8*)&lbl_803CBC3C)[2] = 0;
        ((u8*)&g_Practice)[0x1D9] = 0;
        fn_80011BE4(9);
        fn_3_B3C94(1);
        break;
    case 1:
        if (fn_3_6BA64() != 0) {
            fn_3_B3C94(2);
        }
        break;
    case 2:
        if (g_Practice.practiceType_2 == 4) {
            fn_3_B3C94(3);
        } else if (fn_3_750DC() != 0) {
            fn_3_B3C94(3);
        }
        break;
    case 3:
        if (someAnimationIndFunction() != 0) {
            fn_3_B3C94(4);
        }
        break;
    case 4:
        if (fn_3_B3CD4() != 0) {
            fn_3_B3C94(7);
        }
        break;
    case 7:
        fn_3_B3B70();
        if (g_Practice.practiceType_2 == 4) {
            fn_3_B3A4C();
            fn_3_B3C78(3);
        } else {
            fn_3_B27A4();
            g_Practice.commandList = lbl_3_data_FDE4[g_Practice.practiceLevel];
            fn_3_B3C78(1);
        }
        changeScene(1, 6);
        fn_3_5A6D4(7);
        break;
    }
}

// fn_3_AFE0C, size:0x230
void fn_3_AFE0C(void) {
    s16 t;
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    t = 0x78;
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator != 0) {
            t = 0x3C;
            goto count;
        }
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
        return;
    }
    if (g_Ball.AtBat_ContactResult == 0) {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
        return;
    }
    if (g_Practice.guidedPracticeCompletionRelated != 0) {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
        return;
    }
    if (g_Ball.deadBallReason == 1) {
        if (((u8*)&g_Practice)[0x1B0] == 0) {
            if (c->newButtonInput & 0x1100) {
                ((u8*)&g_Practice)[0x1B0] = 1;
            }
            t = 0x12C;
        } else {
            t = 0x2D;
        }
        lbl_3_common_bss_34C58._2A = 1;
        lbl_3_common_bss_34C58._24 = 0x1E;
    } else if (g_Ball.framesSinceHit > 0xB4) {
        t = 0x78;
    }
count:
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) < 0x7FFE) {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) += 1;
    } else {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0x7FFF;
    }
    if (g_GameLogic.framePlayEnd > t && *(s16*)((u8*)&g_FieldingLogic + 0xAE) > t - 0x5A) {
        *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
        *(s16*)((u8*)&g_FieldingLogic + 0xEE) = 0;
    }
    if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) >= t) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        fn_3_1DD48();
        fn_3_5A6D4(7);
    } else if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) >= t - 6) {
        changeScene(3, 6);
    } else if (*(s16*)((u8*)&g_FieldingLogic + 0xAE) == t - 0x1E) {
        g_FieldingLogic._10E = 1;
        *(s16*)((u8*)&g_FieldingLogic + 0xEE) = 1;
    }
    g_GameLogic.framePlayEnd = t;
    g_GameLogic.CountdownUntilFade = t - *(s16*)((u8*)&g_FieldingLogic + 0xAE);
}

#pragma dont_inline off
