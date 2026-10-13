#include "game/auto_00_000AC9F8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/game_batter.h"
#include "game/rep_1200.h"
#include "game/rep_13B8.h"
#include "game/rep_AC8.h"
#include "game/rep_720.h"
#include "game/rep_F80.h"
extern s32 fn_3_6BD6C(void); // auto_00_0006B4C8_text.h declares it void, but it returns a flag
#include "game/auto_00_0005985C_text.h"
#include "main/file_8004207C.h"
#include "main/file_80069BDC.h"
extern void fn_80011A60(void); // main/file_80011640.h conflicts with file_8004207C.h
extern void fn_3_8C07C(void); // game/m_sound.h conflicts with UnknownHomes_Static.h
extern void fn_8004CC18(void); // main/file_8004C5F8.h conflicts with file_8004207C.h

extern s32 fn_3_B32B8(void);
extern void fn_3_1DD48(void);
extern void fn_3_5F720(void);
extern void fn_3_6EBB4(s32);
extern void fn_3_6E24C(s32, s32);
extern void fn_3_6D964(s32, s32);
extern void setInMemBatterConstants(int rosterID);
extern s32 fn_3_6BA64(void);
extern s32 fn_3_B3CD4(void);
extern void fn_3_B4124(s32 team, s32 slot, s32 charId, s32 handedness);
extern void fn_80011BE4(s32);
extern s16* lbl_3_data_FDE4[];
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
extern void fn_80011BE4(s32);
extern s16* lbl_3_data_101E0[];
extern int random_fn_3_9EE24(int max);
extern s16 lbl_3_data_FB08[][3];
extern s16 lbl_3_data_FB44[][3];
extern s16 lbl_3_data_FB80[][3];
extern s16 lbl_3_data_FBBC[][3];
extern s16 lbl_3_data_FBF8[];
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_59918(s32, s32);
extern u8 lbl_8036E548[];
// Bytes of lbl_8036E548 (CharMgr) by GameCube offset; on PC through the
// real struct (port/game/views.c).
#ifdef TARGET_PC
u8* port_charmgr_byte(u32 gcOffset);
#define CHARMGR_U8(off) (*port_charmgr_byte(off))
#else
#define CHARMGR_U8(off) lbl_8036E548[off]
#endif
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
extern void fn_3_B1DD0(void);
extern void fn_3_6EBB4(s32);
extern u8 lbl_80366158[];
#ifdef TARGET_PC // the struct holds pointers: reach the byte through it (port/game/views.c)
u8* port_80366158_byte(u32 gcOffset);
#define LBL_80366158_U8(off) (*port_80366158_byte(off))
#else
#define LBL_80366158_U8(off) lbl_80366158[off]
#endif
extern u8 lbl_80354768[];
extern u8 lbl_800EFBA4[];
extern u8 sndFXStartEx(s32, u8, u8, u8);
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_803CBC3C;
extern void fn_3_BF1AC(void);
extern void fn_3_BF158(void);
extern s16 lbl_3_data_104B8[][2][3];

#pragma dont_inline on

extern s32 fn_3_5B220(s32);
extern u8 lbl_3_data_FACC[];

extern u8 g_Fielders[];

#include "game/auto_00_000B3B70_text.h"


// fn_3_AFDA4, size:0x1C
void fn_3_AFDA4(void) {
    lbl_3_common_bss_34C90.active = 0;
    lbl_3_common_bss_34C90._1D6 = 0;
    lbl_3_common_bss_34C90._1D7 = 0;
}

#pragma dont_inline off
// fn_3_AFD80, size:0x24
void fn_3_AFD80(u8 state) {
    lbl_3_common_bss_34C90.state = state;
    lbl_3_common_bss_34C90.subState = 0;
    lbl_3_common_bss_34C90.frames = 0;
    lbl_3_common_bss_34C90._0E = 0;
    lbl_3_common_bss_34C90._10 = 0;
}
#pragma dont_inline on

// fn_3_B0A88, size:0x24
void fn_3_B0A88(void) {
    fn_3_B3C78(0);
}

// fn_3_B3A28, size:0x24
void fn_3_B3A28(void) {
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90.subState = 0;
    lbl_3_common_bss_34C90.cursor = 0;
}

// fn_3_B1DA4, size:0x2C
void fn_3_B1DA4(s32 level, u8 value) {
    g_Practice.loadingGuidedPractice = 1;
    g_Practice._1D5 = 0;
    g_Practice.practiceLevel_2 = level;
    g_Practice._1D7 = value;
    g_Practice._1D8 = 0;
    g_Practice._188 = 0;
}

// fn_3_B3288, size:0x30
void fn_3_B3288(void) {
    g_Practice.pauseMenuLoading = 0;
    g_Practice._19F = 1;
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90.subState = 0;
    lbl_3_common_bss_34C90.cursor = 0;
}

// fn_3_AFD48, size:0x38
s32 fn_3_AFD48(s16 value) {
    if (lbl_3_common_bss_34C90.inputCooldown <= 0) {
        lbl_3_common_bss_34C90.heldButtons = value;
        lbl_3_common_bss_34C90.newButtons = value;
        lbl_3_common_bss_34C90.repeatButtons = value;
        lbl_3_common_bss_34C90.inputCooldown = 13;
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
    g_Practice._1DD = 0;
    g_Practice._1DE = 0;
    g_Practice._1DF = 0;
    g_Practice._1E0 = 0;
    g_Practice._1E2 = 0;
    g_Practice.maybeCommandData[0] = 0;
    fn_3_B3C78(0);
}

#pragma dont_inline off
// fn_3_B025C, size:0x4C
void fn_3_B025C(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        fn_3_75560();
        atBat_batter();
        fn_3_8A958();
        fn_3_31594();
    }
}
#pragma dont_inline on

// fn_3_AFDC0, size:0x4C
void fn_3_AFDC0(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}

#pragma dont_inline off
// fn_3_B0DB0, size:0x50
void fn_3_B0DB0(void) {
    g_Practice.allowPlayToEndIndicator = 0;
    g_GameLogic.pre_PostMiniGameInd = 1;
    g_GameLogic.minigameLastTurnSuccessInd = 1;
    g_GameLogic.hudLoadingRelated = 1;
    fn_3_1DD48();
    fn_3_5A6D4(7);
}
#pragma dont_inline on

#pragma dont_inline off
// fn_3_B1120, size:0x4C
void fn_3_B1120(void) {
    if (g_Practice.instructionNumber >= 0 || fn_3_B32B8() == 0) {
        ballPhysica();
        fn_3_598D0();
        fn_3_8A958();
        fn_3_B0E00();
    }
}
#pragma dont_inline on

#pragma dont_inline off
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
#pragma dont_inline on

#pragma dont_inline off
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
#pragma dont_inline on

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

#pragma dont_inline off
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
#pragma dont_inline on

#pragma dont_inline off
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
#pragma dont_inline on

// fn_3_B254C, size:0xE4
s32 fn_3_B254C(void) {
    if (g_Practice.transitioningIndicator == 0) {
        LBL_80366158_U8(0x28) = 1;
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
            if (lbl_8037169C._13 != 0) {
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
        n = g_Practice._1D8 + 1;
        g_Practice._1D8 = n;
        if (n >= 3 || lbl_3_data_104B8[g_Practice.practiceLevel_2][g_Practice._1D7][n] < 0) {
            g_Practice.loadingGuidedPractice = 0;
        }
    }
    return 1;
}

// fn_3_AFA64, size:0x100
void fn_3_AFA64(void) {
    if (lbl_3_common_bss_34C90.frames < 0x7FFE) {
        lbl_3_common_bss_34C90.frames += 1;
    } else {
        lbl_3_common_bss_34C90.frames = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (lbl_3_common_bss_34C90.frames > 0x3C) {
        if (lbl_3_common_bss_34C90.openedByBattingTeam == 0) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                lbl_3_common_bss_34C90.menuType = 2;
            } else {
                lbl_3_common_bss_34C90.menuType = 0;
            }
        } else if (g_d_GameSettings.exhibitionMatchInd == 0) {
            lbl_3_common_bss_34C90.menuType = 3;
        } else {
            lbl_3_common_bss_34C90.menuType = 1;
        }
        lbl_3_common_bss_34C90.state = 1;
        lbl_3_common_bss_34C90.subState = 0;
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90._0E = 0;
        lbl_3_common_bss_34C90._10 = 0;
        fn_3_5A6D4(0xB);
        fn_3_BF1AC();
        fn_3_BF158();
        return;
    }
    fn_3_31594();
    fn_3_8A958();
}

#pragma dont_inline off
// fn_3_AC9F8, size:0x100
void fn_3_AC9F8(void) {
    if (lbl_3_common_bss_32724[0xC3] == 0) {
        if (lbl_3_common_bss_34C90.newButtons & 0x200) {
            lbl_3_common_bss_34C90.subState = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (g_d_GameSettings.GameModeSelected != 6) {
            if ((lbl_3_common_bss_34C90.repeatButtons & 1) && lbl_3_common_bss_34C90.optionCursor != 0) {
                lbl_3_common_bss_34C90.optionCursor -= 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                return;
            }
            if ((lbl_3_common_bss_34C90.repeatButtons & 2) && lbl_3_common_bss_34C90.optionCursor < lbl_3_common_bss_34C90.optionCount - 1) {
                lbl_3_common_bss_34C90.optionCursor += 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}
#pragma dont_inline on

#pragma dont_inline off
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
        u8 (*t)[4] = g_Practice.levelCleared;
        if (t[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice._1B1 = 1;
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
#pragma dont_inline on

#pragma dont_inline off
// fn_3_AEFF8, size:0x114
void fn_3_AEFF8(void) {
    s32 i;
    lbl_3_common_bss_34C90._254 = -1;
    lbl_3_common_bss_34C90._258 = -1;
    lbl_3_common_bss_34C90._256 = -1;
    lbl_3_common_bss_34C90._25A = -1;
    for (i = 0; i < 9; i++) {
        if (lbl_80354720[lbl_3_common_bss_34C90.team][i].slot == 0) {
            lbl_3_common_bss_34C90._25C = i;
        }
        if (lbl_80354720[lbl_3_common_bss_34C90.team][i].slot == 1) {
            lbl_3_common_bss_34C90._25E = i;
        }
    }

}
#pragma dont_inline on

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

#pragma dont_inline off
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
                    lbl_3_common_bss_34C90.positions[i]) {
                    lbl_3_common_bss_34C90.positionsChanged = 1;
                }
                v = lbl_3_common_bss_34C90.positions[i];
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
#pragma dont_inline on

#pragma dont_inline off
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
        u8 (*t)[4] = g_Practice.levelCleared;
        if (t[g_Practice.practiceType_2][g_Practice.practiceLevel] == 0) {
            g_Practice._1B1 = 1;
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
#pragma dont_inline on

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
    g_FieldingLogic._0EE = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_RunningLogic[0x13] = 0;
    g_GameLogic.pre_PostMiniGameInd = 0;
    g_GameLogic.minigameLastTurnSuccessInd = 0;
    g_Practice.hitVariablesSetIndicator = 0;
    g_Practice._1E4 = 0;
    g_Practice._1CB = 0;
    g_Strikes.outs = 0;
    g_Practice._152 = 0;
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
    g_FieldingLogic._0EE = 0;
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
    g_Practice._1B0 = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
    fn_3_6C0E0();
    if (lbl_3_common_bss_34C58._2A != 0) {
        lbl_3_common_bss_34C58._2A = 2;
        lbl_3_common_bss_34C58._24 = 0x78;
    }
}

#pragma dont_inline off
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
#pragma dont_inline on

#pragma dont_inline off
// fn_3_AF428, size:0x17C
void fn_3_AF428(void) {
    if (lbl_3_common_bss_34C90._254 >= 0) {
        if (lbl_3_common_bss_34C90._25C == lbl_3_common_bss_34C90._254) {
            lbl_3_common_bss_34C90._254 = -1;
        } else if (lbl_3_common_bss_34C90._258 < 0) {
            lbl_3_common_bss_34C90._258 = lbl_3_common_bss_34C90._254;
            lbl_3_common_bss_32724[0x9C] = 0;
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0] =
                (s8)lbl_80354720[lbl_3_common_bss_34C90.team][lbl_3_common_bss_34C90._254]._0;
            fn_3_750DC();
        } else if (fn_3_750DC() != 0) {
            s16 v = lbl_3_common_bss_34C90._258;
            lbl_3_common_bss_34C90._254 = -1;
            lbl_3_common_bss_34C90._25C = v;
            lbl_3_common_bss_34C90._258 = -1;
        }
    } else if (lbl_3_common_bss_34C90._256 >= 0) {
        if (lbl_3_common_bss_34C90._25E == lbl_3_common_bss_34C90._25A) {
            lbl_3_common_bss_34C90._256 = -1;
            lbl_3_common_bss_34C90._25A = -1;
        } else if (lbl_3_common_bss_34C90._25A < 0) {
            lbl_3_common_bss_34C90._25A = lbl_3_common_bss_34C90._256;
            ((u8*)&lbl_803CBC3C)[3] = 0;
        } else if (fn_8001C588(inMemRoster[lbl_3_common_bss_34C90.team][(s8)lbl_80354720[lbl_3_common_bss_34C90.team][lbl_3_common_bss_34C90._256]._0].stats.CharID) != 0) {
            s16 v = lbl_3_common_bss_34C90._25A;
            lbl_3_common_bss_34C90._256 = -1;
            lbl_3_common_bss_34C90._25E = v;
            lbl_3_common_bss_34C90._25A = -1;
        }
    }
}
#pragma dont_inline on

// fn_3_B32B8, size:0x190
s32 fn_3_B32B8(void) {
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    if (CHARMGR_U8(0x2D46) != 0) {
        return 0;
    }
    if (CHARMGR_U8(0x2D52) != 0) {
        return 0;
    }
    if (g_Practice._186 != 0 || g_Practice.guidedPracticeCompletionRelated != 0) {
        return 0;
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0x1E || lbl_8037169C.state != 0) {
        return 0;
    }
    if (g_Practice.pauseMenuLoading != 0) {
        LBL_80366158_U8(0x28) = 1;
        g_Practice.frames_sinceTimeCalled += 1;
        if (g_Practice.frames_sinceTimeCalled >= 0x3C) {
            g_Practice.pauseMenuLoading = 0;
            g_Practice._19F = 1;
            g_Practice.frames_onPauseScreen = 0;
            lbl_3_common_bss_34C90.subState = 0;
            lbl_3_common_bss_34C90.cursor = 0;
        }
        return 1;
    }
    if (g_Practice.practiceType_2 == 4 && g_Pitcher.pitchTotalTimeCounter > 0) {
        return 0;
    }
    if (c->newButtonInput & 0x1000) {
        LBL_80366158_U8(0x28) = 1;
        fn_3_59918(0xE, 0);
        g_Practice.pauseMenuLoading = 1;
        g_Practice.frames_sinceTimeCalled = 0;
        return 1;
    }
    return 0;
}

#pragma dont_inline off
// fn_3_AE770, size:0x190
void fn_3_AE770(void) {
    s32 i;
    if (lbl_3_common_bss_34C90.frames <= 1) {
        ((u8*)&lbl_803CBC3C)[2] = 0;
        fn_80035B50(0x13);
    }
    fn_3_753E8(1);
    setBatterContactConstants();
    for (i = 0; i < 2; i++) {
        if (g_GameLogic._13E[i] == 0) {
            if (lbl_800E8754.port[g_GameLogic.teams[i]]._2 != 0) {
                g_GameLogic.battingAIInd[g_GameLogic._000 ^ i] = 1;
            } else {
                g_GameLogic.battingAIInd[g_GameLogic._000 ^ i] = 0;
            }
            if (lbl_800E8754.port[g_GameLogic.teams[i]]._3 != 0) {
                g_GameLogic.teamAIInd[g_GameLogic._000 ^ i] = 1;
                g_GameLogic.autoFielding[g_GameLogic._000 ^ i] = 1;
            } else {
                g_GameLogic.teamAIInd[g_GameLogic._000 ^ i] = 0;
                g_GameLogic.autoFielding[g_GameLogic._000 ^ i] = 0;
            }
        }
    }
    fn_3_FBD70();
    fn_3_FBD58();
    CHARMGR_U8(0x307E) = 1;
    g_GameLogic.pre_PostMiniGameInd = 1;
    changeScene(1, 6);
    fn_3_5A6D4(0);
}
#pragma dont_inline on

// The tables it reads (0xFAA8..) belong to the second TU in this gap, so the original addresses them
// as externs, not through this file's pooled .data base.
#pragma pool_data off
// fn_3_B0B5C, size:0x198
void fn_3_B0B5C(void) {
    if (g_Practice.hitVariablesSetIndicator == 0) {
        g_Practice._152 += 1;
        if (g_Practice._152 >= lbl_3_data_FBF8[0]) {
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
#pragma pool_data reset

// fn_3_B1A30, size:0x19C
void fn_3_B1A30(void) {
    switch (g_Practice.practiceState) {
    case 0: {
        s32 i;
        CHARMGR_U8(0x307D) = 0;
        fn_3_6EBB4(0);
        fn_3_8A350();
        for (i = 0; i < 9; i++) {
            fn_3_6E24C(i, i);
        }
        setInMemBatterConstants(0);
        fn_3_6D964(0, 0);
        g_GameLogic.currentBatterPerTeam[0] = 1;
        g_GameLogic.currentBatterPerTeam[1] = 1;
        lbl_3_common_bss_32724[0x9A] = 0;
        lbl_3_common_bss_32724[0x9C] = 0;
        ((u8*)&lbl_803CBC3C)[2] = 0;
        g_Practice.aIEnabled = 1;
        g_Practice.practiceBatterHandedness = 1;
        g_Practice._1D9 = 0;
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
            if (g_Ball.framesOnGroundUntilPickedUp == 0 && g_Practice._1B0 == 0 &&
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
            switch ((lbl_3_data_FAE8 + row * 5)[lbl_3_common_bss_34C90.cursor + 1]) {
            case 0:
                lbl_3_common_bss_34C90.subState = 10;
                break;
            case 1:
                lbl_3_common_bss_34C90.subState = 4;
                break;
            case 2:
                lbl_3_common_bss_34C90.subState = 6;
                break;
            case 3:
                fn_3_5B408();
                lbl_3_common_bss_34C90.subState = 12;
                break;
            }
            r = sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        }
    } else {
        b = c->_08;
        if (b & 4) {
            lbl_3_common_bss_34C90.cursor++;
            if ((s8)lbl_3_common_bss_34C90.cursor >= (s32)lbl_3_data_FAE8[row * 5]) {
                lbl_3_common_bss_34C90.cursor = 0;
            }
            r = sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else {
            r = b & 8;
            if (r != 0) {
                lbl_3_common_bss_34C90.cursor--;
                if ((s8)lbl_3_common_bss_34C90.cursor < 0) {
                    lbl_3_common_bss_34C90.cursor = lbl_3_data_FAE8[row * 5] - 1;
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
    if (CHARMGR_U8(0x2D46) == 0 && CHARMGR_U8(0x2D52) == 0 && CHARMGR_U8(0x2D5E) == 0 &&
        (g_d_GameSettings.exhibitionMatchInd != 0 || lbl_3_common_bss_32724[0xB3] == 0) &&
        g_Pitcher.pitchTotalTimeCounter <= 0 && lbl_3_common_bss_34C90.active == 0 && g_Pitcher.pitcherActionState != 2) {
        lbl_3_common_bss_34C90._201 = 0;
        if (lbl_3_common_bss_34C90.requestOpen[g_GameLogic.teamFielding] != 0) {
            lbl_3_common_bss_34C90.openedByBattingTeam = 0;
            lbl_3_common_bss_34C90.requestOpen[g_GameLogic.teamFielding] = 0;
            lbl_3_common_bss_34C90._204[g_GameLogic.teamFielding] = 0;
            goto start;
        }
        if (lbl_3_common_bss_34C90.requestOpen[g_GameLogic.teamBatting] != 0) {
            lbl_3_common_bss_34C90.openedByBattingTeam = 1;
            lbl_3_common_bss_34C90.requestOpen[g_GameLogic.teamBatting] = 0;
            lbl_3_common_bss_34C90._204[g_GameLogic.teamBatting] = 0;
            goto start;
        }
        u = g_GameLogic._13E;
        if (u[g_GameLogic.teamFielding] == 0 &&
            (g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]].newButtonInput & 0x1000)) {
            lbl_3_common_bss_34C90.openedByBattingTeam = 0;
            goto start;
        }
        if (u[g_GameLogic.teamBatting] == 0 &&
            (g_Controls[g_GameLogic.teams[g_GameLogic.teamBatting]].newButtonInput & 0x1000)) {
            lbl_3_common_bss_34C90.openedByBattingTeam = 1;
            goto start;
        }
        return;
    start:
        lbl_3_common_bss_34C90.active = 1;
        lbl_3_common_bss_34C90.state = 0;
        lbl_3_common_bss_34C90.subState = 0;
        lbl_3_common_bss_34C90.frames = 0;
        lbl_3_common_bss_34C90._0E = 0;
        lbl_3_common_bss_34C90._10 = 0;
        fn_3_59918(0xE, 0);
        lbl_3_common_bss_34C58._2A = 1;
        lbl_3_common_bss_34C58._24 = 0x3B;
    }
}

// fn_3_B28A8, size:0x1F8
void fn_3_B28A8(void) {
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    switch (lbl_3_common_bss_34C90._1D3) {
    case 0:
        lbl_3_common_bss_34C90.optionCursor = 1;
        lbl_3_common_bss_34C90.optionCount = 3;
        lbl_3_common_bss_34C90._1D9 = 1;
        lbl_3_common_bss_34C90._1D3 = 1;
        break;
    case 1:
        if (fn_80035838(lbl_3_data_10598 + 0x20, 0x13) != 0) {
            lbl_3_common_bss_34C90._1D3 = 2;
        }
        break;
    case 2:
        if (lbl_3_common_bss_34C90._1D9 == 3) {
            lbl_3_common_bss_34C90._1D3 = 3;
        }
        break;
    case 3:
        lbl_3_common_bss_34C90._1D3 = 4;
        break;
    case 4:
        if (lbl_3_common_bss_32724[0xC3] == 0) {
            lbl_3_common_bss_34C90._1D3 = 5;
        }
        break;
    case 5:
        if (lbl_3_common_bss_32724[0xC3] == 0) {
            if (c->newButtonInput & 0x200) {
                lbl_3_common_bss_34C90._1D3 = 6;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                return;
            }
            if ((c->_08 & 1) && lbl_3_common_bss_34C90.optionCursor != 0) {
                lbl_3_common_bss_34C90.optionCursor -= 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                return;
            }
            if ((c->_08 & 2) && lbl_3_common_bss_34C90.optionCursor < lbl_3_common_bss_34C90.optionCount - 1) {
                lbl_3_common_bss_34C90.optionCursor += 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        break;
    case 6:
        lbl_3_common_bss_34C90._1D3 = 7;
        break;
    case 7:
        if (lbl_3_common_bss_32724[0xC3] == 0) {
            fn_80035B50(0x13);
            lbl_3_common_bss_34C90.subState = 0;
        }
        break;
    }
}

// fn_3_B0874, size:0x218
void fn_3_B0874(void) {
    switch (g_Practice.practiceState) {
    case 0:
        CHARMGR_U8(0x307D) = 0;
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
        g_GameLogic.currentBatterPerTeam[0] = 1;
        g_GameLogic.currentBatterPerTeam[1] = 1;
        lbl_3_common_bss_32724[0x9A] = 0;
        lbl_3_common_bss_32724[0x9C] = 0;
        ((u8*)&lbl_803CBC3C)[2] = 0;
        g_Practice._1D9 = 0;
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
        g_FieldingLogic._0AE = 0;
        return;
    }
    if (g_Ball.AtBat_ContactResult == 0) {
        g_FieldingLogic._0AE = 0;
        return;
    }
    if (g_Practice.guidedPracticeCompletionRelated != 0) {
        g_FieldingLogic._0AE = 0;
        return;
    }
    if (g_Ball.deadBallReason == 1) {
        if (g_Practice._1B0 == 0) {
            if (c->newButtonInput & 0x1100) {
                g_Practice._1B0 = 1;
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
    if (g_FieldingLogic._0AE < 0x7FFE) {
        g_FieldingLogic._0AE += 1;
    } else {
        g_FieldingLogic._0AE = 0x7FFF;
    }
    if (g_GameLogic.framePlayEnd > t && g_FieldingLogic._0AE > t - 0x5A) {
        g_FieldingLogic._0AE = 0;
        g_FieldingLogic._0EE = 0;
    }
    if (g_FieldingLogic._0AE >= t) {
        g_Practice.allowPlayToEndIndicator = 0;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        fn_3_1DD48();
        fn_3_5A6D4(7);
    } else if (g_FieldingLogic._0AE >= t - 6) {
        changeScene(3, 6);
    } else if (g_FieldingLogic._0AE == t - 0x1E) {
        g_FieldingLogic._10E = 1;
        g_FieldingLogic._0EE = 1;
    }
    g_GameLogic.framePlayEnd = t;
    g_GameLogic.CountdownUntilFade = t - g_FieldingLogic._0AE;
}

#pragma dont_inline off

// fn_3_B27A4, size:0x104
void fn_3_B27A4(void) {
    s32 i;
    g_Practice.framesOnAllInstructions = 0;
    g_Practice._164 = 0;
    g_Practice.framesOnCurrInstruction = 0;
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.lakituTextIndex_stored = -1;
    g_Practice.diagramTextChannelIndex = -1;
    g_Practice.diagramTitleTextIndex_stored = -1;
    g_Practice.cpuCommandDuration = 0;
    g_Practice.instructionNumber = 0;
    g_Practice.currentMessageDoneTyping = 0;
    g_Practice.commandIndex = 0;
    g_Practice.allInstructionsComplete = 0;
    g_Practice.instructionComplete_readyToAdvance = 0;
    g_Practice.allowPlayToEndIndicator = 0;
    g_Practice._1C7 = 0;
    g_Practice.guidedPracticeCompletionRelated = 0;
    g_Practice.guidedPracticeCounter = 0;
    g_Practice.maybeControlFlag1 = 0;
    g_Practice.maybeControlFlag2 = 0;
    g_Practice.practice_runner_countInputForMashing = 0;
    g_Practice.practice_fielding_enableSprinting = 0;
    g_Practice._1C6 = 0;
    g_Practice.textRelatedIndicator = 0;
    g_Practice.maybePreviousInput[0] = 0;
    g_Practice.maybePreviousInput[1] = 0;
    g_Practice.cpu_inputDuration[0] = 0;
    g_Practice.cpu_inputDuration[1] = 0;
    g_Practice._186 = 0;
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_GameLogic._140[0] = g_GameLogic._140[1] = 0;
    g_GameLogic.batterHandedness[0] = g_GameLogic.batterHandedness[1] = 0;
    g_GameLogic.teamAIInd[0] = g_GameLogic.teamAIInd[1] = 0;
    g_GameLogic.autoFielding[0] = g_GameLogic.autoFielding[1] = 0;
    g_GameLogic.battingAIInd[0] = g_GameLogic.battingAIInd[1] = 0;
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

// fn_3_AD164, size:0x13C
void fn_3_AD164(s32 arg) {
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        lbl_3_common_bss_34C90._23F[lbl_3_common_bss_34C90.team] = 0;
        if (g_GameLogic._13E[lbl_3_common_bss_34C90.team ^ 1] == 0) {
            lbl_3_common_bss_34C90._23F[lbl_3_common_bss_34C90.team ^ 1] = 1;
        } else {
            lbl_3_common_bss_34C90._23F[lbl_3_common_bss_34C90.team ^ 1] = -1;
        }
        lbl_3_common_bss_34C90.subState = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 3;
        }
        break;
    case 3:
        fn_3_ACD38();
        break;
    case 4:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 5;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 6;
        }
        break;
    case 6:
        if (arg == 0) {
            fn_3_AFD80(2);
        } else {
            fn_3_AFD80(9);
        }
        break;
    }
}

// fn_3_AD8CC, size:0x170
void fn_3_AD8CC(void) {
    u8 state;
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        state = lbl_3_common_bss_34C90.state;
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_803297E0._CFA2[lbl_3_common_bss_34C90.team] = state != 4;
        if (state == 14 || state == 7) {
            lbl_803297E0._CFA2[lbl_3_common_bss_34C90.team] = 2;
        } else if (state == 15 || state == 8) {
            lbl_803297E0._CFA2[lbl_3_common_bss_34C90.team] = 3;
        }
        lbl_3_common_bss_34C90.subState = 2;
        break;
    case 1:
        break;
    case 2:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 3;
        break;
    case 3:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 4;
        }
        break;
    case 4:
        fn_3_AD3BC();
        break;
    case 5:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 6;
        break;
    case 6:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            if (lbl_3_common_bss_34C90.state == 11 || lbl_3_common_bss_34C90.state == 14 ||
                lbl_3_common_bss_34C90.state == 15) {
                fn_3_AFD80(9);
            } else {
                fn_3_AFD80(2);
            }
        }
        break;
    }
}

// fn_3_ACAF8, size:0x240
void fn_3_ACAF8(void) {
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.optionCursor = 1;
        lbl_3_common_bss_34C90.optionCount = 3;
        lbl_3_common_bss_34C90.subState = 2;
        break;
    case 1:
        break;
    case 2:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 3;
        break;
    case 3:
        changeScene(1, 6);
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 4;
        }
        break;
    case 4:
        fn_3_AC9F8();
        lbl_3_common_bss_34C90.subFrames = 0;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.subFrames > 20 && lbl_3_common_bss_32724[0xC3] == 0) {
            lbl_3_common_bss_34C90.subState = 6;
        }
        break;
    case 6:
        if (g_d_GameSettings.GameModeSelected == 6) {
            lbl_3_common_bss_34C90.subState = 0;
            fn_3_5A6D4(0xB);
        } else if (lbl_3_common_bss_34C90.openedByBattingTeam == 0) {
            fn_3_AFD80(2);
        } else {
            fn_3_AFD80(9);
        }
        break;
    }
}

// fn_3_B056C, size:0x308
void fn_3_B056C(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    if (g_Practice._1C7 != 0) {
        fn_3_B3620();
        return;
    }
    if (fn_3_B1CB0() != 0) {
        return;
    }
    if (g_Practice.instructionNumber >= 0) {
        fn_3_B2630();
        if (g_Practice.readyToMoveToNextInstruction != 0) {
            return;
        }
        if (g_Practice.tutorialState == 2) {
            return;
        }
    } else if (fn_3_B0464() != 0) {
        return;
    }
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay += 1;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu += 1;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_B02A8();
        break;
    case 1:
        fn_3_B025C();
        break;
    case 2:
        fn_3_B01E0();
        break;
    case 7:
        fn_3_B03F0();
        break;
    }
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
}

extern u8 lbl_3_data_F538[];

// fn_3_AF10C, size:0x31C
void fn_3_AF10C(void) {
    if (lbl_3_common_bss_34C90.frames <= 1) {
        if (lbl_3_common_bss_34C90.openedByBattingTeam == 0) {
            lbl_3_common_bss_34C90.team = g_GameLogic.teamFielding;
            if (g_GameLogic._131[g_GameLogic.teamFielding] < 0xFE) {
                g_GameLogic._131[g_GameLogic.teamFielding] += 1;
            } else {
                g_GameLogic._131[g_GameLogic.teamFielding] = 0xFF;
            }
            if (g_GameLogic._133[g_GameLogic.teamFielding] < 0xFE) {
                g_GameLogic._133[g_GameLogic.teamFielding] += 1;
            } else {
                g_GameLogic._133[g_GameLogic.teamFielding] = 0xFF;
            }
        } else {
            lbl_3_common_bss_34C90.team = g_GameLogic.teamBatting;
            if (g_GameLogic._131[g_GameLogic.teamBatting] < 0xFE) {
                g_GameLogic._131[g_GameLogic.teamBatting] += 1;
            } else {
                g_GameLogic._131[g_GameLogic.teamBatting] = 0xFF;
            }
            if (g_GameLogic._133[g_GameLogic.teamBatting] < 0xFE) {
                g_GameLogic._133[g_GameLogic.teamBatting] += 1;
            } else {
                g_GameLogic._133[g_GameLogic.teamBatting] = 0xFF;
            }
        }
        fn_3_AEFF8();
        lbl_3_common_bss_34C90.cursor = 0;
        lbl_3_common_bss_34C90.inputCooldown = 13;
        lbl_3_common_bss_34C90._201 = 0;
        lbl_3_common_bss_34C90._207[0] = 0;
        lbl_3_common_bss_34C90._207[1] = 0;
        if (g_GameLogic._13E[lbl_3_common_bss_34C90.team] != 0) {
            lbl_3_common_bss_34C90._201 = 1;
        }
        lbl_3_common_bss_34C90._1DB[0] = 0;
        lbl_3_common_bss_34C90._1DB[1] = 0;
        if (g_GameLogic.playBatterWalkupAnimation != 0) {
            g_GameLogic.playBatterWalkupAnimation = 2;
        }
        fn_3_15F94();
    } else if (fn_80035838(lbl_3_data_F538 + 0x20, 0x13) != 0) {
        if (lbl_3_common_bss_34C90.openedByBattingTeam == 0) {
            fn_3_AFD80(2);
        } else {
            fn_3_AFD80(9);
        }
    }
}

// fn_3_B0E00, size:0x320
void fn_3_B0E00(void) {
    s16 limit = 7;
    if (g_Practice.instructionNumber >= 0) {
        if (g_Practice.allowPlayToEndIndicator != 0) {
            limit = 0x3C;
        } else {
            g_FieldingLogic._0AE = 0;
            return;
        }
    } else if (g_Practice._1E4 != 2) {
        if (g_Practice.practiceLevel == 0) {
            if (g_Ball.numThrowsDuringPlay != 0) {
                limit = lbl_3_data_FBF8[1];
                if (g_Practice._1E4 == 0) {
                    g_Practice._1E4 = 1;
                    g_Practice.guidedPracticeCounter += 1;
                }
            }
        } else if (g_Practice.practiceLevel == 1) {
            if (g_Strikes.outs != 0 || g_Practice._1E4 == 1) {
                limit = lbl_3_data_FBF8[2];
                if (g_Practice._1E4 == 0) {
                    g_Practice._1E4 = 1;
                    g_Practice.guidedPracticeCounter += 1;
                }
            }
            if (g_Runners[0].currentBase >= 1 && g_Ball.AtBat_ContactResult != 0) {
                limit = lbl_3_data_FBF8[2];
                if (g_Practice._1E4 == 0) {
                    g_Practice._1E4 = 1;
                }
            }
        } else if (g_Practice.practiceLevel == 2) {
            if (g_Ball.numberOfThrowsDuringPlay != 0) {
                limit = lbl_3_data_FBF8[3];
                if (g_Practice._1E4 == 0) {
                    if (g_Practice._1CB != 0) {
                        g_Practice.guidedPracticeCounter += 1;
                    }
                    g_Practice._1E4 = 1;
                }
            } else if (g_Ball.framesSinceHit >= lbl_3_data_FBF8[4]) {
                g_Practice._1E4 = 2;
            }
        } else if (g_Practice.practiceLevel == 3) {
            if (g_Ball.numberOfThrowsDuringPlay != 0) {
                limit = lbl_3_data_FBF8[5];
                if (g_Practice._1E4 == 0) {
                    if (g_FieldingLogic._114 == 2) {
                        g_Practice.guidedPracticeCounter += 1;
                    }
                    g_Practice._1E4 = 1;
                }
            } else if (g_Ball.framesSinceBallHitGroundOrWasCaught >= lbl_3_data_FBF8[6]) {
                g_Practice._1E4 = 2;
            }
        }
        if (g_Practice.guidedPracticeCounter >= lbl_3_data_FAF4[g_Practice.practiceType_2][g_Practice.practiceLevel]) {
            g_Practice.guidedPracticeCompletionRelated = 1;
        }
        if (g_Practice._1E4 == 0) {
            return;
        }
    }
    if (g_FieldingLogic._0AE < 0x7FFE) {
        g_FieldingLogic._0AE += 1;
    } else {
        g_FieldingLogic._0AE = 0x7FFF;
    }
    if (g_Practice.guidedPracticeCompletionRelated == 0) {
        if (g_FieldingLogic._0AE >= limit) {
            fn_3_B0DB0();
        } else if (g_FieldingLogic._0AE == limit - 6) {
            changeScene(3, 6);
        }
    }
}

extern MenuOptionList lbl_3_data_F918[2][2];

// fn_3_AE900, size:0x350
void fn_3_AE900(void) {
    s32 i;
    s32 row = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        row = 1;
    }
    if (lbl_3_common_bss_34C90.newButtons & 0x1000) {
        for (i = 1; i < 7; i++) {
            if (lbl_3_data_F918[row][1].items[i - 1] == 0) {
                lbl_3_common_bss_34C90.cursor = i - 1;
                break;
            }
        }
        lbl_3_common_bss_34C90.subState = 3;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.newButtons & 0x100) {
        switch (lbl_3_data_F918[row][1].items[lbl_3_common_bss_34C90.cursor]) {
        case 6:
            fn_3_5B408();
            lbl_3_common_bss_34C90.subState = 7;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            break;
        case 1:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 2:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 3:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 4:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 5:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        default:
            lbl_3_common_bss_34C90.subState = 3;
            break;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.newButtons & 0x200) {
        if (lbl_3_data_F918[row][1].items[lbl_3_common_bss_34C90.cursor] != 0) {
            for (i = 1; i < 7; i++) {
                if (lbl_3_data_F918[row][1].items[i - 1] == 0) {
                    lbl_3_common_bss_34C90.cursor = i - 1;
                    break;
                }
            }
        } else {
            lbl_3_common_bss_34C90.subState = 3;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.repeatButtons & 8) {
        if (lbl_3_common_bss_34C90.cursor == 0) {
            lbl_3_common_bss_34C90.cursor = lbl_3_data_F918[row][1].count - 1;
        } else {
            lbl_3_common_bss_34C90.cursor--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.repeatButtons & 4) {
        lbl_3_common_bss_34C90.cursor++;
        if (lbl_3_common_bss_34C90.cursor >= lbl_3_data_F918[row][1].count) {
            lbl_3_common_bss_34C90.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_3_B2AA0, size:0x380
void fn_3_B2AA0(void) {
    s32 count = 5;
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    if (lbl_3_common_bss_34C90.menuType == 6) {
        count = 5;
    } else if (lbl_3_common_bss_34C90.menuType == 5) {
        count = 4;
    }
    if (c->newButtonInput & 0x1000) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        lbl_3_common_bss_34C90.subState = 4;
    } else if (c->newButtonInput & 0x100) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        if (lbl_3_common_bss_34C90.menuType == 6) {
            switch (lbl_3_common_bss_34C90.cursor) {
            case 0:
                lbl_3_common_bss_34C90.subState = 4;
                break;
            case 1:
                lbl_3_common_bss_34C90._1D3 = 0;
                lbl_3_common_bss_34C90.subState = 3;
                break;
            case 2:
                lbl_3_common_bss_34C90.subState = 8;
                break;
            case 3:
                lbl_3_common_bss_34C90.subState = 6;
                break;
            case 4:
                fn_3_5B408();
                lbl_3_common_bss_34C90.subFrames = 0;
                lbl_3_common_bss_34C90.subState = 12;
                break;
            }
        } else if (lbl_3_common_bss_34C90.menuType == 5) {
            switch (lbl_3_common_bss_34C90.cursor) {
            case 0:
                lbl_3_common_bss_34C90.subState = 4;
                break;
            case 1:
                lbl_3_common_bss_34C90._1D3 = 0;
                lbl_3_common_bss_34C90.subState = 3;
                break;
            case 2:
                lbl_3_common_bss_34C90.subState = 6;
                break;
            case 3:
                fn_3_5B408();
                lbl_3_common_bss_34C90.subFrames = 0;
                lbl_3_common_bss_34C90.subState = 12;
                break;
            }
        } else {
            switch (lbl_3_common_bss_34C90.cursor) {
            case 0:
                lbl_3_common_bss_34C90.subState = 4;
                break;
            case 1:
                lbl_3_common_bss_34C90._1D3 = 0;
                lbl_3_common_bss_34C90.subState = 3;
                break;
            case 2:
                lbl_3_common_bss_34C90.subState = 10;
                break;
            case 3:
                lbl_3_common_bss_34C90.subState = 6;
                break;
            case 4:
                fn_3_5B408();
                lbl_3_common_bss_34C90.subFrames = 0;
                lbl_3_common_bss_34C90.subState = 12;
                break;
            }
        }
    } else if (c->newButtonInput & 0x200) {
        if (lbl_3_common_bss_34C90.cursor != 0) {
            lbl_3_common_bss_34C90.cursor = 0;
        } else {
            lbl_3_common_bss_34C90.subState = 4;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (c->_08 & 4) {
        lbl_3_common_bss_34C90.cursor++;
        if (lbl_3_common_bss_34C90.cursor >= count) {
            lbl_3_common_bss_34C90.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (c->_08 & 8) {
        lbl_3_common_bss_34C90.cursor--;
        if (lbl_3_common_bss_34C90.cursor < 0) {
            lbl_3_common_bss_34C90.cursor = count - 1;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

extern u8 lbl_3_data_6104[]; // s8 values; read as u8 then cast (matches)

// fn_3_AEC50, size:0x3A8
void fn_3_AEC50(void) {
    s32 row = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        row = 1;
    }
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 1;
        if (lbl_3_common_bss_34C58._2A != 0) {
            lbl_3_common_bss_34C58._2A = 2;
            lbl_3_common_bss_34C58._24 = 0x78;
        }
        break;
    case 1:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 2;
        }
        break;
    case 2:
        fn_3_AE900();
        lbl_3_common_bss_34C90.subFrames = 0;
        break;
    case 3:
        if (lbl_3_common_bss_34C90.subFrames == 1) {
            changeScene(3, 6);
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 5;
        }
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 4;
        }
        break;
    case 4:
        switch (lbl_3_data_F918[row][1].items[lbl_3_common_bss_34C90.cursor]) {
        case 0:
            fn_3_AFD80(10);
            break;
        }
        lbl_3_common_bss_34C90._1D9 = 2;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 6;
        }
        break;
    case 6:
        switch (lbl_3_data_F918[row][1].items[lbl_3_common_bss_34C90.cursor]) {
        case 3:
            fn_3_AFD80(11);
            break;
        case 5:
            lbl_3_common_bss_34C90._220 = 0;
            fn_3_AFD80(13);
            break;
        case 4:
            fn_3_AFD80(12);
            break;
        case 1:
            fn_3_AFD80(14);
            break;
        case 2:
            fn_3_AFD80(15);
            break;
        }
        break;
    case 7:
        switch (fn_3_5B380(lbl_3_common_bss_34C90.newButtons)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_3_common_bss_34C90.subState = 8;
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 2;
            break;
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                if (g_d_GameSettings.bJMatchInd == 1) {
                    fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
                } else {
                    fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441E]);
                }
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C._13 != 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
            lbl_3_common_bss_34C90._1D9 = 2;
            g_d_GameSettings._13 = 1;
            fn_80035B50(0x13);
            fn_8004CC18();
        }
        break;
    }
}

// fn_3_B3620, size:0x408
void fn_3_B3620(void) {
    LBL_80366158_U8(0x28) = 1;
    if (g_Practice.frames_onPauseScreen < 0x7FFE) {
        g_Practice.frames_onPauseScreen += 1;
    } else {
        g_Practice.frames_onPauseScreen = 0x7FFF;
    }
    if (g_Practice.frames_onPauseScreen2 < 0x7FFE) {
        g_Practice.frames_onPauseScreen2 += 1;
    } else {
        g_Practice.frames_onPauseScreen2 = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90._0A < 0x7FFE) {
        lbl_3_common_bss_34C90._0A += 1;
    } else {
        lbl_3_common_bss_34C90._0A = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90.frames < 0x7FFE) {
        lbl_3_common_bss_34C90.frames += 1;
    } else {
        lbl_3_common_bss_34C90.frames = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90.subFrames < 0x7FFE) {
        lbl_3_common_bss_34C90.subFrames += 1;
    } else {
        lbl_3_common_bss_34C90.subFrames = 0x7FFF;
    }
    if (g_Practice._188 < 0x7FFE) {
        g_Practice._188 += 1;
    } else {
        g_Practice._188 = 0x7FFF;
    }
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        if (g_Practice.practiceLevel == lbl_3_data_FACC[g_Practice.practiceType_2 * 5] - 1) {
            lbl_3_common_bss_34C90.menuType = 8;
        } else {
            lbl_3_common_bss_34C90.menuType = 7;
        }
        lbl_3_common_bss_34C90.team = g_Practice.homeAway;
        g_Practice.frames_onPauseScreen2 = 0;
        lbl_3_common_bss_34C90.subState = 1;
        break;
    case 1:
        if (g_Practice.frames_onPauseScreen2 > 30) {
            lbl_3_common_bss_34C90.subState = 2;
        }
        break;
    case 2:
        fn_3_B3448();
        lbl_3_common_bss_34C90.subFrames = 0;
        break;
    case 4:
    case 10:
        changeScene(3, 6);
        lbl_3_common_bss_34C90.subState++;
        break;
    case 5:
    case 11:
        if (lbl_8037169C._13 != 0) {
            g_Practice.loadingGuidedPractice = 0;
            lbl_3_common_bss_34C90._1D9 = 2;
            g_Practice._19F = 0;
            CHARMGR_U8(0x307D) = 0;
            if (lbl_3_common_bss_34C90.subState == 11) {
                g_Practice.practiceState = 0;
                g_Practice.practiceLevel++;
                g_Practice.tutorialState = 0;
                g_Practice.framesSincePracticeMenuDefaultTransition = 0;
            } else {
                g_Practice.practiceState = 0;
                g_Practice.transitioningIndicator = 1;
                g_Practice.tutorialState = 2;
                g_Practice.framesSincePracticeMenuDefaultTransition = 0;
            }
        }
        break;
    case 6:
        changeScene(3, 6);
        lbl_3_common_bss_34C90.subState = 7;
        break;
    case 7:
        if (lbl_8037169C._13 != 0) {
            g_Practice.loadingGuidedPractice = 0;
            lbl_3_common_bss_34C90._1D9 = 2;
            g_Practice._19F = 0;
            CHARMGR_U8(0x307D) = 0;
            CHARMGR_U8(0x307E) = 0;
            fn_3_B5D4C(0);
            g_Practice.returnToPracticeMenuState = 1;
            g_GameLogic.secondaryGameMode = 10;
            g_Practice.totalFrames = 0;
            g_Practice.framesInCurrTransitionState = 0;
            g_Practice.practiceState = 0;
            fn_80011A60();
            fn_3_8C07C();
        }
        break;
    case 12:
        switch (fn_3_5B380(g_Controls[lbl_3_common_bss_34C90.team].newButtonInput)) {
        case 1:
            if (g_Practice._1B1 != 0) {
                fn_8004CC18();
                fn_3_5B368();
            } else {
                changeScene(3, 6);
            }
            lbl_3_common_bss_34C90.subState = 13;
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 2;
            break;
        }
        break;
    case 13:
        if (g_Practice._1B1 != 0) {
            if (fn_3_5B220(3) != 0) {
                changeScene(3, 6);
                g_Practice._1B1 = 0;
            }
        } else if (lbl_8037169C._13 != 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
            lbl_3_common_bss_34C90._1D9 = 2;
            fn_8004CC18();
        }
        break;
    }
}

// fn_3_ACD38, size:0x42C
void fn_3_ACD38(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        u32 port = g_GameLogic.teams[i];
        InputStruct* c = &g_Controls[port];
        if (g_GameLogic._13E[i] != 0) {
            continue;
        }
        if (c->newButtonInput & 0x100) {
            if (lbl_3_common_bss_34C90._23F[i] == 0) {
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                lbl_3_common_bss_34C90.subState = 4;
            }
        } else if (c->_08 & 8) {
            if (lbl_3_common_bss_34C90._23F[i] == 0) {
                lbl_3_common_bss_34C90._23F[i] = 4;
            } else if (lbl_3_common_bss_34C90._23F[i] == 1) {
                if (i == lbl_3_common_bss_34C90.team) {
                    lbl_3_common_bss_34C90._23F[i] = 0;
                } else {
                    lbl_3_common_bss_34C90._23F[i] = 4;
                }
            } else {
                lbl_3_common_bss_34C90._23F[i]--;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (c->_08 & 4) {
            if (lbl_3_common_bss_34C90._23F[i] == 4) {
                if (i == lbl_3_common_bss_34C90.team) {
                    lbl_3_common_bss_34C90._23F[i] = 0;
                } else {
                    lbl_3_common_bss_34C90._23F[i] = 1;
                }
            } else {
                lbl_3_common_bss_34C90._23F[i]++;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (c->_08 & 2) {
            if (lbl_3_common_bss_34C90._23F[i] != 0) {
                switch (lbl_3_common_bss_34C90._23F[i]) {
                case 1:
                    if (lbl_800E8754.port[port]._6 == 0) {
                        lbl_800E8754.port[port]._6 = 1;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                case 2:
                    if (lbl_800E8754.port[port]._3 == 0) {
                        lbl_800E8754.port[port]._3 = 1;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                case 3:
                    if (lbl_800E8754.port[port]._2 == 0) {
                        lbl_800E8754.port[port]._2 = 1;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                case 4:
                    if (lbl_800E8754.port[port]._4 == 1) {
                        lbl_800E8754.port[port]._4 = 0;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                }
            }
        } else if (c->_08 & 1) {
            if (lbl_3_common_bss_34C90._23F[i] != 0) {
                switch (lbl_3_common_bss_34C90._23F[i]) {
                case 1:
                    if (lbl_800E8754.port[port]._6 != 0) {
                        lbl_800E8754.port[port]._6 = 0;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                case 2:
                    if (lbl_800E8754.port[port]._3 != 0) {
                        lbl_800E8754.port[port]._3 = 0;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                case 3:
                    if (lbl_800E8754.port[port]._2 != 0) {
                        lbl_800E8754.port[port]._2 = 0;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                case 4:
                    if (lbl_800E8754.port[port]._4 == 0) {
                        lbl_800E8754.port[port]._4 = 1;
                        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                    }
                    break;
                }
            }
        }
    }
}

// fn_3_AE334, size:0x43C
void fn_3_AE334(void) {
    s32 i;
    s32 row = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        row = 1;
    }
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        for (i = 0; i < 9; i++) {
            lbl_3_common_bss_34C90.positions[i] = lbl_80354720[lbl_3_common_bss_34C90.team][i].slot;
        }
        lbl_3_common_bss_34C90.subFrames = 0;
        lbl_3_common_bss_34C90.subState = 1;
        lbl_3_common_bss_34C90.positionsChanged = 0;
        if (lbl_3_common_bss_34C58._2A != 0) {
            lbl_3_common_bss_34C58._2A = 2;
            lbl_3_common_bss_34C58._24 = 0x78;
        }
        break;
    case 1:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 2;
        }
        break;
    case 2:
        fn_3_ADEDC();
        lbl_3_common_bss_34C90.subFrames = 0;
        break;
    case 3:
        if (lbl_3_common_bss_34C90.subFrames == 1) {
            changeScene(3, 6);
            lbl_3_common_bss_34C58._2A = 1;
            lbl_3_common_bss_34C58._24 = 5;
        }
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 4;
        }
        break;
    case 4:
        switch (lbl_3_data_F918[row][0].items[lbl_3_common_bss_34C90.cursor]) {
        case 0:
            fn_3_AFD80(3);
            break;
        }
        lbl_3_common_bss_34C90._1D9 = 2;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.subFrames > 20) {
            lbl_3_common_bss_34C90.subState = 6;
        }
        break;
    case 6:
        switch (lbl_3_data_F918[row][0].items[lbl_3_common_bss_34C90.cursor]) {
        case 3:
            fn_3_AFD80(4);
            break;
        case 5:
            lbl_3_common_bss_34C90._220 = 1;
            fn_3_AFD80(6);
            break;
        case 4:
            fn_3_AFD80(5);
            break;
        case 1:
            fn_3_AFD80(7);
            break;
        case 2:
            fn_3_AFD80(8);
            break;
        }
        break;
    case 7:
        switch (fn_3_5B380(lbl_3_common_bss_34C90.newButtons)) {
        case 1:
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            lbl_3_common_bss_34C90.subState = 8;
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 2;
            break;
        }
        break;
    case 8:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > 0x2D) {
            if (g_d_GameSettings.exhibitionMatchInd == 0) {
                if (g_d_GameSettings.bJMatchInd == 1) {
                    fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
                } else {
                    fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441E]);
                }
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C._13 != 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
            lbl_3_common_bss_34C90._1D9 = 2;
            g_d_GameSettings._13 = 1;
            fn_80035B50(0x13);
            fn_8004CC18();
        }
        break;
    }
}

// fn_3_ADEDC, size:0x458
void fn_3_ADEDC(void) {
    s32 i;
    s32 row = 0;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        row = 1;
    }
    if (lbl_3_common_bss_34C90._201 != 0) {
        if (lbl_3_common_bss_34C90._204[g_GameLogic.teamFielding] != 0) {
            if (lbl_3_data_F918[row][0].items[lbl_3_common_bss_34C90.cursor] == 0) {
                if (lbl_3_common_bss_34C90.inputCooldown <= 0) {
                    lbl_3_common_bss_34C90.heldButtons = 256;
                lbl_3_common_bss_34C90.newButtons = 256;
                lbl_3_common_bss_34C90.repeatButtons = 256;
                lbl_3_common_bss_34C90.inputCooldown = 13;
                }
            } else if (lbl_3_common_bss_34C90.inputCooldown <= 0) {
                lbl_3_common_bss_34C90.heldButtons = 8;
                lbl_3_common_bss_34C90.newButtons = 8;
                lbl_3_common_bss_34C90.repeatButtons = 8;
                lbl_3_common_bss_34C90.inputCooldown = 13;
            }
        } else if (lbl_3_data_F918[row][0].items[lbl_3_common_bss_34C90.cursor] == 3) {
            if (lbl_3_common_bss_34C90.inputCooldown <= 0) {
                lbl_3_common_bss_34C90.heldButtons = 256;
                lbl_3_common_bss_34C90.newButtons = 256;
                lbl_3_common_bss_34C90.repeatButtons = 256;
                lbl_3_common_bss_34C90.inputCooldown = 13;
            }
        } else if (lbl_3_common_bss_34C90.inputCooldown <= 0) {
            lbl_3_common_bss_34C90.heldButtons = 4;
                lbl_3_common_bss_34C90.newButtons = 4;
                lbl_3_common_bss_34C90.repeatButtons = 4;
                lbl_3_common_bss_34C90.inputCooldown = 13;
        }
    }
    if (lbl_3_common_bss_34C90.newButtons & 0x1000) {
        for (i = 1; i < 7; i++) {
            if (lbl_3_data_F918[row][0].items[i - 1] == 0) {
                lbl_3_common_bss_34C90.cursor = i - 1;
                break;
            }
        }
        lbl_3_common_bss_34C90.subState = 3;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.newButtons & 0x100) {
        switch (lbl_3_data_F918[row][0].items[lbl_3_common_bss_34C90.cursor]) {
        case 6:
            fn_3_5B408();
            lbl_3_common_bss_34C90.subState = 7;
            break;
        case 1:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 2:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 4:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 3:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        case 5:
            lbl_3_common_bss_34C90._1D9 = 1;
            lbl_3_common_bss_34C90.subFrames = 0;
            lbl_3_common_bss_34C90.subState = 5;
            break;
        default:
            lbl_3_common_bss_34C90.subState = 3;
            break;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.newButtons & 0x200) {
        if (lbl_3_data_F918[row][0].items[lbl_3_common_bss_34C90.cursor] != 0) {
            for (i = 1; i < 7; i++) {
                if (lbl_3_data_F918[row][0].items[i - 1] == 0) {
                    lbl_3_common_bss_34C90.cursor = i - 1;
                    break;
                }
            }
        } else {
            lbl_3_common_bss_34C90.subState = 3;
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.repeatButtons & 8) {
        if (lbl_3_common_bss_34C90.cursor == 0) {
            lbl_3_common_bss_34C90.cursor = lbl_3_data_F918[row][0].count - 1;
        } else {
            lbl_3_common_bss_34C90.cursor--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (lbl_3_common_bss_34C90.repeatButtons & 4) {
        lbl_3_common_bss_34C90.cursor++;
        if (lbl_3_common_bss_34C90.cursor >= lbl_3_data_F918[row][0].count) {
            lbl_3_common_bss_34C90.cursor = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_3_B2E20, size:0x464
void fn_3_B2E20(void) {
    s32 i;
    LBL_80366158_U8(0x28) = 1;
    if (g_Practice.frames_onPauseScreen < 0x7FFE) {
        g_Practice.frames_onPauseScreen += 1;
    } else {
        g_Practice.frames_onPauseScreen = 0x7FFF;
    }
    if (g_Practice.frames_onPauseScreen2 < 0x7FFE) {
        g_Practice.frames_onPauseScreen2 += 1;
    } else {
        g_Practice.frames_onPauseScreen2 = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90._0A < 0x7FFE) {
        lbl_3_common_bss_34C90._0A += 1;
    } else {
        lbl_3_common_bss_34C90._0A = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90.frames < 0x7FFE) {
        lbl_3_common_bss_34C90.frames += 1;
    } else {
        lbl_3_common_bss_34C90.frames = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90.subFrames < 0x7FFE) {
        lbl_3_common_bss_34C90.subFrames += 1;
    } else {
        lbl_3_common_bss_34C90.subFrames = 0x7FFF;
    }
    switch (lbl_3_common_bss_34C90.subState) {
    case 0:
        if (g_Practice.practiceType_2 == 4) {
            lbl_3_common_bss_34C90.menuType = 6;
        } else if (g_Practice.practiceLevel == lbl_3_data_FACC[g_Practice.practiceType_2 * 5] - 1) {
            lbl_3_common_bss_34C90.menuType = 5;
        } else {
            lbl_3_common_bss_34C90.menuType = 4;
        }
        g_Practice.frames_onPauseScreen2 = 0;
        lbl_3_common_bss_34C90.subState = 1;
        break;
    case 1:
        if (g_Practice.frames_onPauseScreen2 > 30) {
            lbl_3_common_bss_34C90.subState = 2;
        }
        break;
    case 2:
        fn_3_B2AA0();
        break;
    case 3:
        fn_3_B28A8();
        break;
    case 4:
        lbl_3_common_bss_34C90._1D9 = 1;
        g_Practice.frames_onPauseScreen2 = 0;
        lbl_3_common_bss_34C90.subState = 5;
        break;
    case 5:
        if (g_Practice.frames_onPauseScreen2 > 30) {
            g_Practice._19F = 0;
        }
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 7;
        }
        break;
    case 7:
    case 9:
        if (g_GameLogic.secondaryGameMode == 15 || g_GameLogic.secondaryGameMode == 16) {
            for (i = 0; i < 4; i++) {
                fn_80011BE4(i + 9);
            }
        }
        lbl_3_common_bss_34C90._1D9 = 2;
        g_Practice._19F = 0;
        CHARMGR_U8(0x307D) = 0;
        CHARMGR_U8(0x307E) = 0;
        if (lbl_3_common_bss_34C90.subState == 9) {
            fn_3_B5D4C(6);
        } else {
            fn_3_B5D4C(0);
        }
        g_Practice.returnToPracticeMenuState = 1;
        g_GameLogic.secondaryGameMode = 10;
        g_Practice.totalFrames = 0;
        g_Practice.framesInCurrTransitionState = 0;
        g_Practice.practiceState = 0;
        fn_80011A60();
        fn_3_6AB30();
        fn_3_8C07C();
        break;
    case 8:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 9;
        }
        break;
    case 10:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            lbl_3_common_bss_34C90.subState = 11;
        }
        break;
    case 11:
        lbl_3_common_bss_34C90._1D9 = 2;
        g_Practice._19F = 0;
        CHARMGR_U8(0x307D) = 0;
        g_Practice.practiceLevel++;
        g_Practice.practiceState = 0;
        g_Practice.tutorialState = 0;
        g_Practice.framesSincePracticeMenuDefaultTransition = 0;
        break;
    case 12:
        switch (fn_3_5B380(g_Controls[lbl_3_common_bss_34C90.team].newButtonInput)) {
        case 1:
            lbl_3_common_bss_34C90.subState = 13;
            if (g_Practice._1B1 != 0) {
                fn_8004CC18();
                fn_3_5B368();
            } else {
                changeScene(4, 6);
            }
            break;
        case 2:
            lbl_3_common_bss_34C90.subState = 2;
            break;
        }
        break;
    case 13:
        if (g_Practice._1B1 != 0) {
            if (fn_3_5B220(3) != 0) {
                changeScene(3, 6);
                g_Practice._1B1 = 0;
            }
        } else if (lbl_8037169C._13 != 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
            lbl_3_common_bss_34C90._1D9 = 2;
            fn_8004CC18();
        }
        break;
    }
}

// fn_3_AF5A4, size:0x4C0
void fn_3_AF5A4(void) {
    if (lbl_3_common_bss_34C90.frames < 0x7FFE) {
        lbl_3_common_bss_34C90.frames += 1;
    } else {
        lbl_3_common_bss_34C90.frames = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90.subFrames < 0x7FFE) {
        lbl_3_common_bss_34C90.subFrames += 1;
    } else {
        lbl_3_common_bss_34C90.subFrames = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (lbl_3_common_bss_34C90._201 != 0) {
        lbl_3_common_bss_34C90.heldButtons = 0;
        lbl_3_common_bss_34C90.newButtons = 0;
        lbl_3_common_bss_34C90.repeatButtons = 0;
        lbl_3_common_bss_34C90.inputCooldown--;
        if (lbl_3_common_bss_34C90.inputCooldown < 0) {
            lbl_3_common_bss_34C90.inputCooldown = 12;
        }
    } else {
        lbl_3_common_bss_34C90.heldButtons = g_Controls[g_GameLogic.teams[lbl_3_common_bss_34C90.team]].buttonInput;
        lbl_3_common_bss_34C90.newButtons = g_Controls[g_GameLogic.teams[lbl_3_common_bss_34C90.team]].newButtonInput;
        lbl_3_common_bss_34C90.repeatButtons = g_Controls[g_GameLogic.teams[lbl_3_common_bss_34C90.team]]._08;
    }
    switch (lbl_3_common_bss_34C90.state) {
    case 0:
        break;
    case 1:
        fn_3_AF10C();
        break;
    case 2:
        fn_3_AE334();
        break;
    case 3:
        fn_3_ADA3C();
        break;
    case 4:
    case 7:
    case 8:
        fn_3_AD8CC();
        break;
    case 5:
        fn_3_AD164(0);
        break;
    case 6:
        fn_3_ACAF8();
        break;
    case 9:
        fn_3_AEC50();
        break;
    case 10:
        fn_3_AE770();
        break;
    case 11:
    case 14:
    case 15:
        fn_3_AD8CC();
        break;
    case 12:
        fn_3_AD164(1);
        break;
    case 13:
        fn_3_ACAF8();
        break;
    }
}

// NONMATCHING 99.6%: the original inlines fn_3_AF428 here (it won't auto-inline for us);
// pasting its body gives 99.6%, only the final "all swaps done" check's branch shape differs.
// nmverify: the fn_3_AF428 call vs its inlined fn_3_750DC/fn_8001C588 calls is expected.
// fn_3_ADA3C, size:0x4A0
#if NONMATCHING
void fn_3_ADA3C(void) {
    s32 i;
    if (lbl_3_common_bss_34C90.subState == 0) {
        fn_80035B50(0x13);
        fn_3_AD2A0();
        lbl_3_common_bss_32724[0x9B] = 0;
        lbl_3_common_bss_34C90.subState++;
    } else if (lbl_3_common_bss_34C90.subState == 1) {
        if (lbl_3_common_bss_34C90.positionsChanged == 0) {
            lbl_3_common_bss_34C90.subState++;
        } else if (fn_3_6BD6C() != 0) {
            lbl_3_common_bss_34C90.subState++;
        }
    } else if (lbl_3_common_bss_34C90.subState == 2) {
        fn_3_AF428();
        if (lbl_3_common_bss_34C90._254 < 0 && lbl_3_common_bss_34C90._258 < 0 &&
            lbl_3_common_bss_34C90._256 < 0) {
            if (lbl_3_common_bss_34C90._25A >= 0) {
                return;
            }
            lbl_3_common_bss_34C90.subState++;
        }
    } else {
        fn_3_753E8(1);
        setBatterContactConstants();
        fn_3_FBD70();
        fn_3_FBD58();
        CHARMGR_U8(0x307E) = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        for (i = 0; i < 2; i++) {
            if (g_GameLogic._13E[i] == 0) {
                if (lbl_800E8754.port[g_GameLogic.teams[i]]._2 != 0) {
                    g_GameLogic.battingAIInd[g_GameLogic._000 ^ i] = 1;
                } else {
                    g_GameLogic.battingAIInd[g_GameLogic._000 ^ i] = 0;
                }
                if (lbl_800E8754.port[g_GameLogic.teams[i]]._3 != 0) {
                    g_GameLogic.teamAIInd[g_GameLogic._000 ^ i] = 1;
                    g_GameLogic.autoFielding[g_GameLogic._000 ^ i] = 1;
                } else {
                    g_GameLogic.teamAIInd[g_GameLogic._000 ^ i] = 0;
                    g_GameLogic.autoFielding[g_GameLogic._000 ^ i] = 0;
                }
            }
        }
        changeScene(1, 6);
        if (g_GameLogic.playOverInd != 0) {
            fn_3_5A6D4(0x16);
        } else {
            fn_3_5A6D4(0);
        }
    }
}
#endif

// fn_3_B1578, size:0x4B8
void fn_3_B1578(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay += 1;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice._1C7 != 0) {
        fn_3_B3620();
        return;
    }
    if (fn_3_B1CB0() != 0) {
        return;
    }
    if (g_Practice.instructionNumber >= 0) {
        fn_3_B2630();
        if (g_Practice.readyToMoveToNextInstruction != 0) {
            return;
        }
        if (g_Practice.tutorialState == 2) {
            return;
        }
    } else if (fn_3_B1470() != 0) {
        return;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu += 1;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_B11D0();
        break;
    case 1:
        fn_3_B116C();
        break;
    case 2:
        fn_3_B1120();
        break;
    case 7:
        fn_3_B12F8();
        break;
    }
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
}

// fn_3_AD3BC, size:0x510
void fn_3_AD3BC(void) {
    s32 i;
    u8 state;
    if (lbl_3_common_bss_34C90._201 != 0) {
        // CPU-controlled team: drive the menu with scripted inputs
        u16 btn = 0;
        if (lbl_3_common_bss_34C90.inputCooldown <= 0) {
            u8 step = lbl_3_common_bss_34C90._207[0];
            switch (step) {
            case 0:
                btn = 4;
                if (++lbl_3_common_bss_34C90._207[1] >= 3) {
                    lbl_3_common_bss_34C90._207[1] = 0;
                    lbl_3_common_bss_34C90._207[0] = step + 1;
                }
                break;
            case 1:
                lbl_3_common_bss_34C90._207[1] = 0;
                btn = 0x100;
                lbl_3_common_bss_34C90._207[0] = step + 1;
                break;
            case 2:
                if (++lbl_3_common_bss_34C90._207[1] >= 2) {
                    lbl_3_common_bss_34C90._207[1] = 0;
                    lbl_3_common_bss_34C90._207[0] = step + 1;
                }
                break;
            case 3: {
                s16 v; // always set: every lineup has a pitcher (position 0)
                for (i = 1; i < 10; i++) {
                    if (lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i][1] == 0) {
                        v = lbl_3_common_bss_34C90.lineup[g_GameLogic.teamFielding][i][0];
                        break;
                    }
                }
                if (lbl_3_common_bss_34C90._207[1] == 0) {
                    if (v == 1) {
                        btn = 4;
                        lbl_3_common_bss_34C90._207[0]++;
                    } else if (v == 3 || v == 5 || v == 7) {
                        btn = 8;
                        if (v == 5) {
                            lbl_3_common_bss_34C90._207[0]++;
                        }
                    } else if (v == 2 || v == 8) {
                        btn = 2;
                        if (v == 2) {
                            lbl_3_common_bss_34C90._207[0]++;
                        }
                    } else {
                        btn = 1;
                        if (v == 4) {
                            lbl_3_common_bss_34C90._207[0]++;
                        }
                    }
                    lbl_3_common_bss_34C90._207[1]++;
                } else {
                    btn = 8;
                    if (v == 3) {
                        btn = 2;
                    }
                    lbl_3_common_bss_34C90._207[0]++;
                }
                break;
            }
            case 4:
                lbl_3_common_bss_34C90._207[1] = 0;
                btn = 0x100;
                lbl_3_common_bss_34C90._207[0] = step + 1;
                break;
            case 5:
                if (++lbl_3_common_bss_34C90._207[1] >= 2) {
                    lbl_3_common_bss_34C90._207[1] = 0;
                    btn = 0x200;
                    lbl_3_common_bss_34C90._207[0] = step + 1;
                }
                break;
            case 6:
                if (++lbl_3_common_bss_34C90._207[1] >= 2) {
                    btn = 0x100;
                    lbl_3_common_bss_34C90._204[g_GameLogic.teamFielding] = 1;
                }
                break;
            }
        }
        for (i = 0; i < 4; i++) {
            if (i == lbl_3_common_bss_34C90.team) {
                lbl_803297E0.input[i].held = btn;
                lbl_803297E0.input[i].pressed = btn;
                lbl_803297E0.input[i].repeat = btn;
            } else {
                lbl_803297E0.input[i].held = 0;
                lbl_803297E0.input[i].pressed = 0;
                lbl_803297E0.input[i].repeat = 0;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (i == lbl_3_common_bss_34C90.team) {
                lbl_803297E0.input[i].held = g_Controls[g_GameLogic.teams[lbl_3_common_bss_34C90.team]].buttonInput;
                lbl_803297E0.input[i].pressed = g_Controls[g_GameLogic.teams[lbl_3_common_bss_34C90.team]].newButtonInput;
                lbl_803297E0.input[i].repeat = g_Controls[g_GameLogic.teams[lbl_3_common_bss_34C90.team]]._08;
            } else {
                lbl_803297E0.input[i].held = 0;
                lbl_803297E0.input[i].pressed = 0;
                lbl_803297E0.input[i].repeat = 0;
            }
        }
    }
    state = lbl_3_common_bss_34C90.state;
    if (state == 4 || state == 11 || state == 14 || state == 7 || state == 8 || state == 15) {
        if (lbl_803297E0._CF42 != 0) {
            lbl_3_common_bss_34C90.subState = 5;
            if (lbl_3_common_bss_34C90.state == 4) {
                for (i = 0; i < 9; i++) {
                    if (lbl_3_common_bss_34C90.positions[i] != lbl_80354720[lbl_3_common_bss_34C90.team][i].slot) {
                        if (lbl_80354720[lbl_3_common_bss_34C90.team][i].slot == 0) {
                            lbl_3_common_bss_34C90._254 = i;
                        } else if (lbl_80354720[lbl_3_common_bss_34C90.team][i].slot == 1) {
                            lbl_3_common_bss_34C90._256 = i;
                        }
                        lbl_3_common_bss_34C90.positions[i] = lbl_80354720[lbl_3_common_bss_34C90.team][i].slot;
                    }
                }
            }
        }
    }
}

// NONMATCHING 97.4%: same instructions; only register allocation in the first loop
// (i in r8 instead of r3) and the saved-register count/frame size differ.
// fn_3_B1DD0, size:0x77C
#if NONMATCHING
void fn_3_B1DD0(void) {
    s16 i;
    s16 team;
    s16 type;
    s16 cmd;
    s16* list;
    s32 batting;
    s32 fielding;
    InputStruct* c = &g_Controls[g_Practice.homeAway];
    g_Practice.inputs[0].newButtonInput = 0;
    g_Practice.inputs[1].newButtonInput = 0;
    if (g_Practice.instructionComplete_readyToAdvance != 0) {
        if (g_Practice.currentMessageDoneTyping != 0 && (c->newButtonInput & 0x100)) {
            g_Practice.instructionComplete_readyToAdvance = 0;
            g_Practice.framesOnCurrInstruction = 0;
            g_Practice.currentMessageDoneTyping = 0;
            g_Practice.instructionNumber++;
        }
        if (g_Practice.instructionComplete_readyToAdvance == 1) {
            LBL_80366158_U8(0x28) = 1;
        }
        g_Practice.readyToMoveToNextInstruction = 1;
        return;
    }
    if (g_Practice.maybeInputResetCountdown != 0 && --g_Practice.maybeInputResetCountdown != 0) {
        g_Practice.readyToMoveToNextInstruction = 1;
        LBL_80366158_U8(0x28) = 1;
        return;
    }
    fn_3_B274C();
    for (i = 0; i < 2; i++) {
        if (g_Practice.cpu_inputDuration[i] != 0) {
            g_Practice.cpu_inputDuration[i]--;
            if (g_Practice.cpu_inputDuration[i] != 0) {
                g_Practice.inputs[i].buttonInput = g_Practice.maybePreviousInput[i];
                {
                    // point the stick along the held d-pad buttons
                    u16 b = g_Practice.inputs[i].buttonInput;
                    s32 up = b & 2;
                    s32 right;
                    s32 down;
                    s32 left;
                    if (up && (b & 8)) {
                        g_Practice.inputs[i].controlStickAngle = 0x200;
                    } else if ((right = b & 8) && (b & 1)) {
                        g_Practice.inputs[i].controlStickAngle = 0x600;
                    } else if ((down = b & 1) && (b & 4)) {
                        g_Practice.inputs[i].controlStickAngle = 0xA00;
                    } else if ((left = b & 4) && up) {
                        g_Practice.inputs[i].controlStickAngle = 0xE00;
                    } else if (up) {
                        g_Practice.inputs[i].controlStickAngle = 0;
                    } else if (right) {
                        g_Practice.inputs[i].controlStickAngle = 0x400;
                    } else if (down) {
                        g_Practice.inputs[i].controlStickAngle = 0x800;
                    } else if (left) {
                        g_Practice.inputs[i].controlStickAngle = 0xC00;
                    }
                    if (g_Practice.inputs[i].controlStickAngle >= 0) {
                        g_Practice.inputs[i].controlStickMagnitude = 0x40;
                    }
                }
            }
        }
    }
    if (g_Practice.cpuCommandDuration != 0 && --g_Practice.cpuCommandDuration != 0) {
        return;
    }
    batting = g_GameLogic.teamBatting;
    list = g_Practice.commandList;
    fielding = g_GameLogic.teamFielding;
    for (;;) {
        cmd = list[g_Practice.commandIndex];
        type = cmd & 0xFF00;
        switch (type) {
        case 0x100:
            g_Practice.commandIndex++;
            g_Practice.cpuCommandDuration = list[g_Practice.commandIndex] & 0xFFF;
            g_Practice.commandIndex++;
            return;
        case 0x200:
            g_Practice.commandIndex++;
            g_Practice.maybeInputResetCountdown = list[g_Practice.commandIndex] & 0xFFF;
            g_Practice.commandIndex++;
            return;
        case 0x300:
            g_Practice.instructionComplete_readyToAdvance = 1;
            g_Practice.commandIndex++;
            return;
        case 0x400:
            g_Practice.instructionComplete_readyToAdvance = 2;
            g_Practice.commandIndex++;
            return;
        case 0x1100:
        case 0x1300:
            team = fielding;
            if (type == 0x1100) {
                team = batting;
            }
            g_Practice.commandIndex++;
            g_Practice.inputs[team].newButtonInput |= list[g_Practice.commandIndex] & 0xFFF;
            break;
        case 0x1200:
        case 0x1400:
            team = fielding;
            if (type == 0x1200) {
                team = batting;
            }
            g_Practice.commandIndex++;
            g_Practice.maybePreviousInput[team] = list[g_Practice.commandIndex];
            g_Practice.inputs[team].buttonInput |= g_Practice.maybePreviousInput[team];
            g_Practice.inputs[team].newButtonInput |= g_Practice.maybePreviousInput[team];
            g_Practice.commandIndex++;
            {
                // point the stick along the held d-pad buttons
                u16 b = g_Practice.inputs[team].buttonInput;
                s32 up = b & 2;
                s32 right;
                s32 down;
                s32 left;
                if (up && (b & 8)) {
                    g_Practice.inputs[team].controlStickAngle = 0x200;
                } else if ((right = b & 8) && (b & 1)) {
                    g_Practice.inputs[team].controlStickAngle = 0x600;
                } else if ((down = b & 1) && (b & 4)) {
                    g_Practice.inputs[team].controlStickAngle = 0xA00;
                } else if ((left = b & 4) && up) {
                    g_Practice.inputs[team].controlStickAngle = 0xE00;
                } else if (up) {
                    g_Practice.inputs[team].controlStickAngle = 0;
                } else if (right) {
                    g_Practice.inputs[team].controlStickAngle = 0x400;
                } else if (down) {
                    g_Practice.inputs[team].controlStickAngle = 0x800;
                } else if (left) {
                    g_Practice.inputs[team].controlStickAngle = 0xC00;
                }
                if (g_Practice.inputs[team].controlStickAngle >= 0) {
                    g_Practice.inputs[team].controlStickMagnitude = 0x40;
                }
            }
            g_Practice.cpu_inputDuration[team] = list[g_Practice.commandIndex] & 0xFFF;
            break;
        case 0x1500:
            g_Practice.practice_runner_countInputForMashing = 1;
            break;
        case 0x1600:
            g_Practice.practice_runner_countInputForMashing = 0;
            break;
        case 0x1700:
            g_Practice.practice_fielding_enableSprinting = 1;
            break;
        case 0x1800:
            g_Practice.practice_fielding_enableSprinting = 0;
            break;
        case 0x2100:
            g_Practice.commandIndex++;
            g_Practice.lakituTextIndex = list[g_Practice.commandIndex] & 0xFFF;
            break;
        case 0x2200:
            g_Practice.commandIndex++;
            g_Practice.diagramTitleTextIndex = list[g_Practice.commandIndex] & 0xFFF;
            break;
        case 0x2300:
            g_Practice.diagramTitleTextIndex = 0;
            break;
        case 0x3100:
            g_Practice.allowPlayToEndIndicator = 1;
            break;
        case 0x3200:
            g_Practice.commandIndex++;
            g_Practice.practice_hitHorizontalPower = list[g_Practice.commandIndex];
            g_Practice.commandIndex++;
            g_Practice.practice_hitVerticalAngle = list[g_Practice.commandIndex];
            g_Practice.commandIndex++;
            g_Practice.practice_hitHorizontalAngle = list[g_Practice.commandIndex];
            break;
        case 0x3300:
            g_Practice._1C6 = cmd;
            g_Practice._1C6++;
            break;
        case 0x4100:
            g_Practice.maybeControlFlag1 = 0;
            g_Practice.maybeControlFlag2 = 0;
            break;
        case 0x4200:
            g_Practice.maybeControlFlag1 = cmd;
            break;
        case 0x4300:
            g_Practice.maybeControlFlag2 = cmd;
            break;
        case 0x4800:
            g_Practice.textRelatedIndicator = 0;
            break;
        case 0x4900:
            g_Practice.textRelatedIndicator = 1;
            break;
        case 0x5100:
            g_Camera._2819 = 1;
            g_Camera._2810 = (u8)cmd;
            break;
        case 0x5200:
            g_Camera._2819 = 2;
            break;
        case 0x7F00:
            g_Practice.allInstructionsComplete = 1;
            LBL_80366158_U8(0x28) = 1;
            return;
        }
        g_Practice.commandIndex++;
    }
}
#endif

// .data 0xF538-0x10A08. The gap 0xAC9F8-0xB3A4C holds two TUs (two sets of jump tables, each
// after its own copy of the 0x3E0 file table F538/10598); kept together with that text here.
// .data 0x0000F538..0x00010A08
u8 lbl_3_data_F538[992] = {
    0, 0, 4, 11, 64, 19, 118, 76, 26, 99, 80, 0, 0, 7, 219, 72,
    0, 0, 4, 11, 64, 3, 227, 220, 26, 107, 48, 0, 0, 2, 20, 32,
    0, 0, 4, 11, 64, 2, 236, 16, 26, 109, 72, 0, 0, 1, 49, 8,
    0, 0, 4, 11, 64, 14, 114, 192, 26, 110, 128, 0, 0, 6, 7, 104,
    0, 0, 4, 11, 64, 4, 148, 4, 26, 116, 136, 0, 0, 2, 14, 52,
    0, 0, 4, 11, 64, 7, 106, 224, 24, 237, 112, 0, 0, 3, 107, 200,
    0, 0, 4, 11, 64, 16, 253, 112, 26, 118, 152, 0, 0, 5, 226, 132,
    0, 0, 4, 11, 64, 13, 183, 56, 26, 124, 128, 0, 0, 4, 154, 180,
    0, 0, 4, 11, 64, 14, 152, 100, 26, 129, 32, 0, 0, 5, 157, 192,
    0, 0, 4, 11, 64, 11, 119, 24, 26, 134, 192, 0, 0, 5, 2, 136,
    0, 0, 4, 11, 64, 13, 135, 252, 26, 139, 200, 0, 0, 4, 123, 196,
    0, 0, 4, 11, 64, 13, 100, 60, 26, 144, 72, 0, 0, 4, 227, 172,
    0, 0, 4, 11, 64, 13, 92, 124, 26, 149, 48, 0, 0, 4, 141, 156,
    0, 0, 4, 11, 64, 11, 118, 124, 26, 153, 192, 0, 0, 4, 117, 24,
    0, 0, 4, 11, 64, 4, 65, 248, 26, 158, 56, 0, 0, 1, 170, 132,
    0, 0, 4, 11, 64, 16, 101, 104, 26, 159, 232, 0, 0, 6, 140, 16,
    0, 0, 4, 11, 64, 16, 229, 160, 14, 151, 168, 0, 0, 9, 188, 172,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 161, 104, 0, 0, 0, 214, 196,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 162, 64, 0, 0, 0, 201, 68,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 163, 16, 0, 0, 0, 231, 0,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 163, 248, 0, 0, 0, 214, 76,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 164, 208, 0, 0, 0, 201, 0,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 165, 160, 0, 0, 0, 207, 252,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 166, 112, 0, 0, 0, 215, 32,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 167, 72, 0, 0, 0, 214, 204,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 168, 32, 0, 0, 0, 210, 28,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 168, 248, 0, 0, 0, 208, 188,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 169, 208, 0, 0, 0, 181, 68,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 170, 136, 0, 0, 0, 196, 248,
    0, 0, 4, 11, 64, 10, 223, 252, 24, 174, 232, 0, 0, 4, 186, 176,
    0, 0, 4, 11, 64, 55, 207, 92, 24, 179, 168, 0, 0, 32, 138, 240,
    0, 0, 4, 11, 64, 0, 168, 32, 24, 237, 56, 0, 0, 0, 55, 88,
    0, 0, 4, 11, 64, 17, 236, 36, 24, 240, 224, 0, 0, 13, 136, 24,
    0, 0, 4, 11, 64, 1, 147, 232, 25, 27, 136, 0, 0, 0, 137, 216,
    0, 0, 4, 11, 64, 6, 200, 80, 6, 201, 96, 0, 0, 2, 200, 132,
    0, 0, 4, 11, 64, 5, 177, 120, 6, 204, 48, 0, 0, 3, 85, 92,
    0, 0, 4, 11, 64, 30, 177, 116, 24, 212, 56, 0, 0, 15, 178, 32,
    0, 0, 4, 11, 64, 1, 237, 96, 26, 166, 120, 0, 0, 0, 207, 240,
    0, 0, 4, 11, 64, 0, 191, 48, 26, 167, 72, 0, 0, 0, 38, 224,
    0, 0, 4, 11, 64, 0, 52, 152, 26, 167, 112, 0, 0, 0, 14, 40,
    0, 0, 4, 11, 64, 0, 189, 224, 26, 167, 128, 0, 0, 0, 36, 244,
    0, 0, 4, 11, 64, 0, 96, 136, 26, 167, 168, 0, 0, 0, 18, 144,
    0, 0, 4, 11, 64, 0, 73, 240, 26, 167, 192, 0, 0, 0, 24, 244,
    0, 0, 4, 11, 64, 0, 94, 204, 26, 167, 224, 0, 0, 0, 29, 56,
    0, 0, 4, 11, 64, 0, 38, 112, 26, 168, 0, 0, 0, 0, 11, 232,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 168, 16, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 170, 152, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 173, 32, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 175, 168, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 178, 48, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 180, 184, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 183, 64, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 185, 200, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 188, 80, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 190, 216, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 193, 96, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 195, 232, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 198, 112, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 200, 248, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 203, 128, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 206, 8, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 208, 144, 0, 0, 2, 130, 64,
};
MenuOptionList lbl_3_data_F918[2][2] = {
    {{5, {0, 3, 4, 5, 6, 0, 0}}, {4, {0, 4, 5, 6, 0, 0, 0}}},
    {{7, {0, 1, 2, 3, 4, 5, 6}}, {6, {0, 1, 2, 4, 5, 6, 0}}},
};
u8 lbl_3_data_FAA8[28] = {
    0, 13, 29, 30, 31, 32, 24, 25, 26, 1, 21, 22, 20, 23, 43, 44,
    16, 45, 6, 4, 0, 9, 2, 5, 10, 11, 1, 0,
};
u8 lbl_3_data_FAC4[8] = {0, 1, 2, 3, 4, 0, 0, 0};
u8 lbl_3_data_FACC[28] = {4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 4, 5, 6, 7, 0, 0, 0};
u8 lbl_3_data_FAE8[12] = {4, 0, 1, 2, 3, 3, 1, 2, 3, 0, 0, 0};
u8 lbl_3_data_FAF4[4][4] = {{5, 5, 5, 5}, {5, 5, 5, 5}, {3, 3, 3, 3}, {5, 5, 5, 5}};
s16 lbl_3_data_FB04 = 90;
u8 lbl_3_data_FB06[2] = {0}; // alignment padding (unused)
s16 lbl_3_data_FB08[10][3] = {
    {100, 40, 1000},
    {100, 80, 1300},
    {100, 70, 800},
    {100, 50, 870},
    {100, 60, 940},
    {100, 20, 1100},
    {100, 30, 1170},
    {100, 60, 1240},
    {100, 70, 1310},
    {100, 50, 1390},
};
s16 lbl_3_data_FB44[10][3] = {
    {130, 400, 1000},
    {100, 80, 1300},
    {130, 400, 800},
    {100, 50, 870},
    {130, 400, 940},
    {130, 400, 750},
    {100, 50, 1170},
    {130, 400, 1240},
    {100, 70, 1310},
    {130, 400, 1090},
};
s16 lbl_3_data_FB80[10][3] = {
    {160, 250, 600},
    {130, 200, 650},
    {160, 250, 800},
    {160, 300, 900},
    {160, 250, 1100},
    {160, 250, 1200},
    {160, 250, 1250},
    {160, 250, 1300},
    {160, 250, 1350},
    {160, 250, 1400},
};
s16 lbl_3_data_FBBC[10][3] = {
    {160, 280, 750},
    {125, 370, 640},
    {155, 280, 1250},
    {150, 300, 910},
    {155, 250, 1100},
    {130, 350, 1100},
    {140, 250, 1250},
    {140, 280, 1220},
    {125, 365, 1350},
    {150, 240, 1400},
};
s16 lbl_3_data_FBF8[8] = {60, 120, 90, 120, 300, 90, 120, 0};
u8 lbl_3_data_FC08[4][4] = {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 1}};
u8 lbl_3_data_FC18[4] = {1, 0, 6, 10};
s16 lbl_3_data_FC1C[1] = {90};
s16 lbl_3_data_FC1E = 90; // unreferenced
extern s16 lbl_3_data_FC30[];
extern s16 lbl_3_data_FCE8[];
extern s16 lbl_3_data_FD54[];
extern s16 lbl_3_data_FD90[];
s16* lbl_3_data_FC20[4] = {lbl_3_data_FC30, lbl_3_data_FCE8, lbl_3_data_FD54, lbl_3_data_FD90}; // practice scripts by level
s16 lbl_3_data_FC30[92] = {
    8448, -20453, 256, -32738, 1024, 8448, -20452, 8704,
    -20376, 18688, 16897, 17153, 20736, 256, -28612, 5120,
    2, -32758, 256, -32708, 5120, 1, -32753, 256,
    -32708, 5120, 2, -32763, 1024, 20992, 16640, 8960,
    8448, -20451, 8704, -20375, 16898, 17154, 256, -32738,
    4864, 256, 256, -32538, 1024, 8960, 16640, 8448,
    -20450, 8704, -20374, 16897, 17155, 256, -32738, 4864,
    256, 256, -32678, 5120, 2, -32668, 256, -32628,
    1024, 8960, 16640, 8448, -20449, 8704, -20373, 16897,
    17156, 256, -32738, 4864, 256, 256, -32678, 5120,
    1, -32668, 256, -32618, 1024, 18432, 8960, 16640,
    8448, -20448, 32512, 0,
}; // script
s16 lbl_3_data_FCE8[54] = {
    8448, -20447, 256, -32738, 1024, 8448, -20446, 8704,
    -20372, 18688, 16898, 17157, 5120, 256, -32668, 256,
    -32698, 768, 8960, 16640, 8448, -20445, 8704, -20371,
    16898, 17158, 4864, 256, 256, -32548, 1024, 8960,
    16640, 8448, -20444, 8704, -20371, 16898, 17158, 5120,
    256, -32653, 256, -32670, 256, -32558, 1024, 18432,
    8960, 16640, 8448, -20443, 32512, 0,
}; // script
s16 lbl_3_data_FD54[30] = {
    8448, -20442, 256, -32738, 1024, 8448, -20441, 256,
    -32738, 1024, 8448, -20440, 18688, 8704, -20370, 16903,
    17159, 5120, 260, -32758, 256, -32538, 1024, 18432,
    8960, 16640, 8448, -20439, 32512, 0,
}; // script
s16 lbl_3_data_FD90[42] = {
    8448, -20438, 256, -32738, 1024, 8448, -20437, 256,
    -32738, 1024, 8448, -20436, 256, -32738, 1024, 8448,
    -20435, 256, -32738, 1024, 8448, -20434, 18688, 8704,
    -20369, 16904, 17160, 5120, 32, -32758, 4864, 256,
    256, -32588, 1024, 18432, 8960, 16640, 8448, -20433,
    32512, 0,
}; // script
extern s16 lbl_3_data_FDF4[];
extern s16 lbl_3_data_FE88[];
extern s16 lbl_3_data_FF28[];
extern s16 lbl_3_data_FFB0[];
s16 *lbl_3_data_FDE4[4] = {lbl_3_data_FDF4, lbl_3_data_FE88, lbl_3_data_FF28, lbl_3_data_FFB0};
s16 lbl_3_data_FDF4[74] = {
    8448, -20432, 256, -32738, 1024, 8448, -20431, 18688,
    8704, -20368, 16897, 17161, 256, -28612, 4608, 8,
    -32758, 256, -32748, 4608, 2, -32758, 256, -32748,
    4608, 4, -32753, 256, -32748, 4608, 1, -32753,
    256, -32748, 4608, 8, -32758, 256, -32748, 4608,
    2, -32763, 256, -32762, 1024, 8960, 16640, 8448,
    -20430, 8704, -20367, 16898, 17154, 256, -32708, 4864,
    256, 13056, 12800, 150, 150, 1190, 256, -32548,
    1024, 12544, 8960, 16640, 256, -32708, 8448, -20425,
    18432, 32512,
}; // script
s16 lbl_3_data_FE88[80] = {
    8448, -20424, 256, -32738, 1024, 8448, -20423, 18688,
    8704, -20362, 16898, 17157, 256, -32748, 4608, 256,
    -32520, 256, -32698, 768, 8960, 16640, 8448, -20422,
    8704, -20361, 16898, 17158, 256, -32708, 4864, 256,
    13057, 12800, 152, 100, 1192, 256, -32548, 1024,
    12544, 8960, 16640, 256, -32708, 8448, -20421, 8704,
    -20361, 16898, 17158, 256, -32748, 4864, 256, 256,
    -32748, 4608, 256, -32468, 256, -32678, 13057, 12800,
    155, 400, 1181, 256, -32498, 1024, 12544, 8960,
    16640, 256, -32708, 8448, -20420, 18432, 32512, 0,
}; // script
s16 lbl_3_data_FF28[68] = {
    8448, -20419, 256, -32738, 1024, 8448, -20418, 18688,
    8704, -20360, 16899, 17165, 256, -32748, 4608, 512,
    -31768, 256, -32708, 768, 8960, 16640, 8448, -20417,
    8704, -20359, 16897, 17161, 256, -32748, 4864, 256,
    256, -32758, 4608, 513, -32758, 256, -32758, 4608,
    514, -32753, 256, -32753, 4608, 513, -32765, 256,
    -32765, 4608, 512, -32568, 12800, 50, 4039, 560,
    256, -32548, 1024, 12544, 8960, 16640, 256, -32708,
    8448, -20416, 18432, 32512,
}; // script
s16 lbl_3_data_FFB0[48] = {
    8448, -20415, 256, -32738, 1024, 8448, -20414, 256,
    -32738, 1024, 8448, -20413, 256, -32738, 1024, 8448,
    -20412, 256, -32738, 1024, 8448, -20411, 18688, 8704,
    -20358, 16904, 17160, 4864, 256, 256, -32658, 13058,
    12800, 195, 60, 1192, 256, -32588, 1024, 12544,
    8960, 16640, 256, -32708, 8448, -20410, 18432, 32512,
}; // script
extern s16 lbl_3_data_10020[];
extern s16 lbl_3_data_100B0[];
extern s16 lbl_3_data_100E4[];
extern s16 lbl_3_data_10174[];
void *lbl_3_data_10010[4] = {
    (void*)lbl_3_data_10020,
    (void*)lbl_3_data_100B0,
    (void*)lbl_3_data_100E4,
    (void*)lbl_3_data_10174,
};
s16 lbl_3_data_10020[72] = {
    8448, -20409, 256, -32738, 1024, 8448, -20408, 18688,
    8704, -20357, 16901, 17167, 4608, 2048, -32767, 256,
    -32648, 4608, 1024, -32767, 256, -32738, 1024, 8960,
    8448, -20407, 8704, -20356, 16900, 17168, 4608, 1024,
    -32767, 256, -32618, 1024, 8960, 8448, -20406, 8704,
    -20355, 16905, 17169, 256, -32748, 4608, 2048, -32767,
    256, -32648, 4608, 1024, -32767, 256, -32708, 4608,
    1024, -32767, 256, -32708, 4608, 2048, -32767, 256,
    -32728, 1024, 18432, 8960, 16640, 8448, -20405, 32512,
}; // script
s16 lbl_3_data_100B0[26] = {
    8448, -20404, 256, -32738, 1024, 8448, -20403, 18688,
    8704, -20354, 16899, 17170, 4608, 2048, -32767, 5376,
    256, -32568, 1024, 18432, 8960, 16640, 8448, -20402,
    32512, 0,
}; // script
s16 lbl_3_data_100E4[72] = {
    8448, -20401, 256, -32738, 1024, 8448, -20400, 18688,
    8704, -20353, 16901, 17167, 4608, 2048, -32767, 256,
    -32648, 4608, 1024, -32767, 256, -32728, 1024, 8960,
    8448, -20399, 8704, -20352, 16900, 17168, 4608, 1024,
    -32767, 256, -32618, 1024, 8960, 8448, -20398, 8704,
    -20351, 16905, 17169, 256, -32748, 4608, 2048, -32767,
    256, -32648, 4608, 1024, -32767, 256, -32708, 4608,
    1024, -32767, 256, -32708, 4608, 2048, -32767, 256,
    -32718, 1024, 18432, 8960, 16640, 8448, -20405, 32512,
}; // script
s16 lbl_3_data_10174[54] = {
    8448, -20396, 256, -32738, 1024, 8448, -20395, 18688,
    8704, -20350, 16897, 17177, 256, -32738, 1024, 8448,
    -20394, 4608, 2052, -32648, 256, -32648, 4608, 1024,
    -32767, 256, -32708, 4608, 2049, -32648, 256, -32648,
    4608, 1024, -32767, 256, -32708, 4608, 2056, -32648,
    256, -32648, 4608, 1024, -32767, 256, -32738, 1024,
    18432, 8960, 16640, 8448, -20393, 32512,
}; // script
extern s16 lbl_3_data_101F0[];
extern s16 lbl_3_data_102A8[];
extern s16 lbl_3_data_10318[];
extern s16 lbl_3_data_10368[];
s16 *lbl_3_data_101E0[4] = {lbl_3_data_101F0, lbl_3_data_102A8, lbl_3_data_10318, lbl_3_data_10368};
s16 lbl_3_data_101F0[92] = {
    8448, -20392, 256, -32738, 1024, 8448, -20391, 18688,
    8704, -20349, 16897, 17161, 256, -28612, 4864, 256,
    256, -32651, 4608, 256, -32760, 12800, 100, 80,
    1250, 256, -32668, 768, 8960, 8448, -20390, 8704,
    -20348, 16898, 17176, 256, -32748, 5120, 258, -32767,
    256, -32618, 768, 12544, 8960, 16640, 256, -28612,
    8448, -20389, 8704, -20347, 16903, 17177, 256, -28612,
    4864, 256, 256, -32651, 4608, 256, -32760, 12800,
    140, 140, 800, 256, -32668, 5120, 264, -32766,
    256, -32728, 5120, 257, -32766, 256, -32693, 5120,
    258, -32766, 256, -32608, 768, 18432, 8960, 16640,
    8448, -20388, 32512, 0,
}; // script
s16 lbl_3_data_102A8[56] = {
    8448, -20387, 256, -32738, 1024, 8448, -20386, 256,
    -28612, 4864, 256, 256, -32651, 4608, 256, -32760,
    12800, 110, 60, 1200, 256, -32678, 5120, 256,
    -32648, 256, -32658, 1024, 12544, 256, -28612, 8448,
    -20385, 256, -32648, 4864, 256, 256, -32651, 4608,
    256, -32760, 12800, 130, 400, 750, 256, -32588,
    1024, 12544, 256, -28612, 8448, -20383, 32512, 0,
}; // script
s16 lbl_3_data_10318[40] = {
    8448, -20382, 256, -32738, 1024, 8448, -20381, 18688,
    8704, -20346, 16899, 17170, 256, -32708, 4864, 256,
    256, -32651, 4608, 256, -32760, 12800, 165, 248,
    1240, 256, -32708, 5120, 8, -32608, 5888, 256,
    -32558, 1024, 18432, 8960, 16640, 8448, -20380, 32512,
}; // script
s16 lbl_3_data_10368[40] = {
    8448, -20379, 256, -32738, 1024, 8448, -20378, 18688,
    8704, -20345, 16903, 17179, 256, -32718, 4864, 256,
    256, -32651, 4608, 256, -32760, 12800, 143, 305,
    925, 256, -32658, 5120, 258, -32758, 256, -32648,
    1024, 18432, 8960, 16640, 8448, -20377, 32512, 0,
}; // script
s16 lbl_3_data_103B8[128] = {
    1, 104, 2, 105, 3, 106, 4, 107,
    5, 108, 6, 109, 0, 0, 0, 0,
    7, 110, 0, 0, 0, 0, 0, 0,
    8, 111, 0, 0, 0, 0, 0, 0,
    9, 112, 10, 113, 0, 0, 0, 0,
    11, 118, 12, 119, 0, 0, 0, 0,
    13, 120, 0, 0, 0, 0, 0, 0,
    14, 122, 0, 0, 0, 0, 0, 0,
    23, 131, 25, 133, 24, 132, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    26, 134, 0, 0, 0, 0, 0, 0,
    27, 135, 0, 0, 0, 0, 0, 0,
    15, 123, 16, 124, 17, 125, 0, 0,
    18, 126, 0, 0, 0, 0, 0, 0,
    19, 127, 20, 128, 21, 129, 0, 0,
    25, 130, 0, 0, 0, 0, 0, 0,
}; // PracticeMsgEntry[][4][4] (auto 157DB8)
s16 lbl_3_data_104B8[16][2][3] = {
    {{136, -1, -1}, {137, -1, -1}},
    {{138, -1, -1}, {139, -1, -1}},
    {{140, -1, -1}, {141, -1, -1}},
    {{142, -1, -1}, {143, -1, -1}},
    {{144, -1, -1}, {145, -1, -1}},
    {{146, -1, -1}, {147, -1, -1}},
    {{148, -1, -1}, {149, -1, -1}},
    {{150, -1, -1}, {151, -1, -1}},
    {{160, -1, -1}, {161, -1, -1}},
    {{162, -1, -1}, {163, -1, -1}},
    {{164, -1, -1}, {165, -1, -1}},
    {{166, -1, -1}, {167, -1, -1}},
    {{152, -1, -1}, {153, -1, -1}},
    {{154, -1, -1}, {155, -1, -1}},
    {{156, -1, -1}, {157, -1, -1}},
    {{158, -1, -1}, {159, -1, -1}},
};
u8 lbl_3_data_10578[32] = {
    0, 0, 0, 0, 0, 0, 60, 152, 8, 242, 16, 0, 0, 0, 60, 152,
    0, 0, 4, 11, 64, 0, 235, 188, 8, 242, 80, 0, 0, 0, 149, 112,
};
u8 lbl_3_data_10598[992] = {
    0, 0, 4, 11, 64, 19, 118, 76, 26, 99, 80, 0, 0, 7, 219, 72,
    0, 0, 4, 11, 64, 3, 227, 220, 26, 107, 48, 0, 0, 2, 20, 32,
    0, 0, 4, 11, 64, 2, 236, 16, 26, 109, 72, 0, 0, 1, 49, 8,
    0, 0, 4, 11, 64, 14, 114, 192, 26, 110, 128, 0, 0, 6, 7, 104,
    0, 0, 4, 11, 64, 4, 148, 4, 26, 116, 136, 0, 0, 2, 14, 52,
    0, 0, 4, 11, 64, 7, 106, 224, 24, 237, 112, 0, 0, 3, 107, 200,
    0, 0, 4, 11, 64, 16, 253, 112, 26, 118, 152, 0, 0, 5, 226, 132,
    0, 0, 4, 11, 64, 13, 183, 56, 26, 124, 128, 0, 0, 4, 154, 180,
    0, 0, 4, 11, 64, 14, 152, 100, 26, 129, 32, 0, 0, 5, 157, 192,
    0, 0, 4, 11, 64, 11, 119, 24, 26, 134, 192, 0, 0, 5, 2, 136,
    0, 0, 4, 11, 64, 13, 135, 252, 26, 139, 200, 0, 0, 4, 123, 196,
    0, 0, 4, 11, 64, 13, 100, 60, 26, 144, 72, 0, 0, 4, 227, 172,
    0, 0, 4, 11, 64, 13, 92, 124, 26, 149, 48, 0, 0, 4, 141, 156,
    0, 0, 4, 11, 64, 11, 118, 124, 26, 153, 192, 0, 0, 4, 117, 24,
    0, 0, 4, 11, 64, 4, 65, 248, 26, 158, 56, 0, 0, 1, 170, 132,
    0, 0, 4, 11, 64, 16, 101, 104, 26, 159, 232, 0, 0, 6, 140, 16,
    0, 0, 4, 11, 64, 16, 229, 160, 14, 151, 168, 0, 0, 9, 188, 172,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 161, 104, 0, 0, 0, 214, 196,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 162, 64, 0, 0, 0, 201, 68,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 163, 16, 0, 0, 0, 231, 0,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 163, 248, 0, 0, 0, 214, 76,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 164, 208, 0, 0, 0, 201, 0,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 165, 160, 0, 0, 0, 207, 252,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 166, 112, 0, 0, 0, 215, 32,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 167, 72, 0, 0, 0, 214, 204,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 168, 32, 0, 0, 0, 210, 28,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 168, 248, 0, 0, 0, 208, 188,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 169, 208, 0, 0, 0, 181, 68,
    0, 0, 4, 11, 64, 1, 105, 128, 14, 170, 136, 0, 0, 0, 196, 248,
    0, 0, 4, 11, 64, 10, 223, 252, 24, 174, 232, 0, 0, 4, 186, 176,
    0, 0, 4, 11, 64, 55, 207, 92, 24, 179, 168, 0, 0, 32, 138, 240,
    0, 0, 4, 11, 64, 0, 168, 32, 24, 237, 56, 0, 0, 0, 55, 88,
    0, 0, 4, 11, 64, 17, 236, 36, 24, 240, 224, 0, 0, 13, 136, 24,
    0, 0, 4, 11, 64, 1, 147, 232, 25, 27, 136, 0, 0, 0, 137, 216,
    0, 0, 4, 11, 64, 6, 200, 80, 6, 201, 96, 0, 0, 2, 200, 132,
    0, 0, 4, 11, 64, 5, 177, 120, 6, 204, 48, 0, 0, 3, 85, 92,
    0, 0, 4, 11, 64, 30, 177, 116, 24, 212, 56, 0, 0, 15, 178, 32,
    0, 0, 4, 11, 64, 1, 237, 96, 26, 166, 120, 0, 0, 0, 207, 240,
    0, 0, 4, 11, 64, 0, 191, 48, 26, 167, 72, 0, 0, 0, 38, 224,
    0, 0, 4, 11, 64, 0, 52, 152, 26, 167, 112, 0, 0, 0, 14, 40,
    0, 0, 4, 11, 64, 0, 189, 224, 26, 167, 128, 0, 0, 0, 36, 244,
    0, 0, 4, 11, 64, 0, 96, 136, 26, 167, 168, 0, 0, 0, 18, 144,
    0, 0, 4, 11, 64, 0, 73, 240, 26, 167, 192, 0, 0, 0, 24, 244,
    0, 0, 4, 11, 64, 0, 94, 204, 26, 167, 224, 0, 0, 0, 29, 56,
    0, 0, 4, 11, 64, 0, 38, 112, 26, 168, 0, 0, 0, 0, 11, 232,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 168, 16, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 170, 152, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 173, 32, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 175, 168, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 178, 48, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 180, 184, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 183, 64, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 185, 200, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 188, 80, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 190, 216, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 193, 96, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 195, 232, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 198, 112, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 200, 248, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 203, 128, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 206, 8, 0, 0, 2, 130, 64,
    0, 0, 0, 0, 0, 2, 130, 64, 26, 208, 144, 0, 0, 2, 130, 64,
};

