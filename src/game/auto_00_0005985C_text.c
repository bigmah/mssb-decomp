#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern s32 fn_80022B68(void);
extern void fn_3_7CE90(void);
extern void fn_3_77914(void);
extern void fn_3_899BC(void);
extern void fn_3_9E7D4(s32);
extern void fn_8006C9D8(void);
extern void fn_3_BF158(void);
extern void fn_3_BF1AC(void);
extern void fn_3_90CB0(void);
extern void fn_3_B95EC(void);
extern void fn_8001E474(void);
extern void fn_3_BC224(void);
extern void fn_3_972C8(void);
extern void fn_8001F228(void);
extern void fn_3_902FC(void);
extern void fn_3_8C07C(void);
extern void fn_3_90434(void);
extern void fn_3_5A6FC(void);
extern void fn_3_6011C(void);
extern void fn_3_FF4C(void);
extern void fn_3_6D304(void);
extern void fn_3_7D458(void);
extern void fn_3_668BC(void);
extern void fn_3_B482C(void);
extern void fn_3_DFBAC(void);
extern void fn_3_10FDC8(void);
extern void fn_3_66140(void);
extern void fn_3_664FC(void);
extern void fn_3_BBF94(void);
extern void fn_3_B93CC(void);
extern void fn_8003BF54(s32, s32, s32, s32, s32, s32, s32, s32, u8);
extern u8 lbl_80366158[];
extern u8 lbl_8036E548[];
extern void fn_3_6C13C(void*, void*);
extern void fn_3_16598C(void);
extern u8 g_RunningLogic[];
extern void fn_800A7568(void);
extern u8 lbl_8037169C[];
extern u8 lbl_803C6CF8[];
extern void starMissionRelated2(void);
extern u8 lbl_3_common_bss_37400[];

extern u8 g_Fielders[];
extern u8 lbl_3_data_3C40[];

extern void fn_80017D28(void* allocation);

extern void fn_3_58688(void);
extern void fn_3_583B8(void);
extern void fn_3_3B9E4(void);
extern void fn_3_736CC(void);
extern void fn_3_735A8(void);
extern void fn_8001AAA4(void);
extern void fn_3_6AEC0(void);
extern u8* lbl_803CC1B8;
extern void ballPhysica(void);
extern void fn_3_8A958(void);
extern void fn_3_5DD30(void);
extern void fn_3_5C74C(s32);
extern void fn_3_5E2C4(void);
extern void fn_3_79ACC(void);
extern void fn_3_5D094(s32);
extern void possiblyTransitionBlackScreen(void);
extern void fn_3_5BAC(void);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_8913C(void);
extern void fn_3_58870(void);
extern void fn_3_1DEB8(void);
extern void Set_803cb848(s32);
extern void fn_3_6EBB4(s32);
extern void fn_3_8A1D8(void*);
extern void fn_3_6C108(void);
extern void fn_3_6B870(void);
extern s32 fn_3_6BA64(void);
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_803CBC3C[];
extern void fn_3_6D4A0(void);
extern void fn_3_5A87C(void*);
extern void fn_3_DFA20(void);
extern void fn_3_10FBE4(void);
extern void fn_3_6C150(void*);
extern void fn_3_8F1C8(void);
extern void fn_3_5B0C4(void);
extern u8 g_Scores[];
extern void fn_3_32090(void*, void*);
extern void fn_3_8911C(void);
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_75434(void);
extern void fn_3_59338(void);
extern void fn_3_7B130(void);
extern void fn_3_22850(void);

#pragma dont_inline on

// fn_3_5D51C, size:0xCC
void fn_3_5D51C(void) {
    u8* scores = g_Scores;
    if (scores[0xAD] == 0) {
        scores[0xAD] = 1;
    } else {
        scores[0xAD] = 0;
        *(s32*)scores += 1;
    }
    g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
    g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
    g_GameLogic.teamBatting ^= 1;
    g_GameLogic.teamFielding ^= 1;
    ((u8*)&g_GameLogic)[0x131] = 0;
    ((u8*)&g_GameLogic)[0x132] = 0;
    *(s16*)(g_Scores + 0xA0) = *(s16*)(g_Scores + scores[0xAD] * 0x26 + 4);
    fn_3_5A684();
    fn_3_8A350();
    fn_3_F7B8();
    fn_3_75434();
    fn_3_59338();
    fn_3_7B130();
    fn_3_22850();
}

// fn_3_5C69C, size:0xB0
void fn_3_5C69C(s32 type) {
    g_Ball.framesSinceHit = 100;
    g_Ball.framesSincePickOff = 0;
    g_FieldingLogic._107 = type + 1;
    g_FieldingLogic.throwSpeedType = 3;
    fn_3_5A6D4(2);
    *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
    fn_3_32090(&g_Pitcher, &g_FieldingLogic);
    fn_3_8911C();
    if (g_Strikes.balls >= 4) {
        g_Runners[0].runnerOnFieldOrOutOrScored = 5;
    } else {
        g_Runners[0].runnerOnFieldOrOutOrScored = 4;
    }
}

// fn_3_5D9F8, size:0xA4
void fn_3_5D9F8(void) {
    if (g_Stats.replayInd == 0) {
        g_Pitcher._15C = 0;
        if (g_d_GameSettings.GameModeSelected == 4 && g_Scores[0xAD] == 0) {
            g_GameLogic.framesOfExitingToMenu = 1;
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            fn_3_5A6D4(9);
        } else {
            fn_3_5A6D4(3);
        }
    }
}

// fn_3_5C530, size:0x98
s32 fn_3_5C530(s32 inning) {
    u8 finalInning = g_Scores[0xAA];
    if (inning > finalInning) {
        return 5;
    }
    if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores[0xAD] != 0) {
            return 4;
        }
        return 0;
    }
    if (inning == finalInning) {
        return 4;
    }
    if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
        return 3;
    }
    if (inning >= 4) {
        return 2;
    }
    return 1;
}

// fn_3_5AE0C, size:0x90
void fn_3_5AE0C(void) {
    fn_3_6D4A0();
    unkSimulationRelatedStruct._08 = 0;
    unkSimulationRelatedStruct._07 = 0;
    fn_3_5A87C(&unkSimulationRelatedStruct);
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_3_DFA20();
    } else if (g_d_GameSettings.GameModeSelected == 7) {
        fn_3_10FBE4();
    }
    g_Minigame._19AB = 0;
    fn_3_6C150(&g_Minigame);
    fn_3_8F1C8();
    *(void (**)(void))((u8**)&lbl_803CC1B8)[0] = fn_3_5B0C4;
}

// fn_3_5CD24, size:0x90
void fn_3_5CD24(void) {
    GameControlsStruct* game = &g_GameLogic;
    if (game->_125 == 0) {
        lbl_3_common_bss_32724[0x9A] = 0;
        fn_3_8A1D8(lbl_3_common_bss_32724);
        fn_3_6C108();
        fn_3_6B870();
        game->_125++;
    } else if (game->_125 == 1) {
        if (fn_3_6BA64() != 0) {
            lbl_803CBC3C[2] = 0;
            fn_3_5A6D4(0);
        }
    }
}

// fn_3_5F720, size:0x88
void fn_3_5F720(void) {
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    fn_3_1DEB8();
    Set_803cb848(1);
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
}

// fn_3_5FE88, size:0x88
void fn_3_5FE88(void) {
    GameControlsStruct* game = &g_GameLogic;
    switch ((s32)game->_125) {
    case 0:
        fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
        game->_125 = 1;
        break;
    case 1:
        fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
        game->_125 = 2;
        break;
    default:
        fn_3_5A6D4(5);
        break;
    }
}

// fn_3_5EDD8, size:0x80
void fn_3_5EDD8(void) {
    ballPhysica();
    fn_3_598D0();
    fn_3_8A958();
    if (g_Ball.deadBallReason != 0) {
        fn_3_5DD30();
    }
    fn_3_5C74C(0);
    fn_3_5E2C4();
    if (g_GameLogic.freeFieldingPracticeInd == 0) {
        fn_3_79ACC();
        if (g_Strikes.outs >= 3) {
            fn_3_5D094(0);
        }
    }
}

// fn_3_59BCC, size:0x60
s32 fn_3_59BCC(s32 stage) {
    u8* queue = lbl_803CC1B8;
    if (stage < 1) {
        return 0;
    }
    if (stage == 1) {
        fn_8001AAA4();
    }
    if (*(s16*)(queue + 0x10) != 0) {
        fn_3_6AEC0();
        return 1;
    }
    return 0;
}

// fn_3_5DCE0, size:0x50
s32 fn_3_5DCE0(void) {
    s32 handled = 0;
    if (g_Pitcher.strikeOutOrWalk == 1) {
        fn_3_736CC();
        handled = 1;
    } else if (g_Pitcher.strikeOutOrWalk == 2) {
        fn_3_735A8();
        handled = 1;
    }
    return handled;
}

// fn_3_5985C, size:0x74
void fn_3_5985C(s32 arg0, s32 arg1) {
    s32 v;
    u8* fielder = g_Fielders + arg0 * 0x268;
    if (arg0 == -1) {
        return;
    }
    fielder[0x1D3] = arg1;
    v = *(s32*)(lbl_3_data_3C40 + arg1 * 8);
    if (v >= 0) {
        *((u8*)&g_FieldingLogic + 0xF8 + arg0) = v;
    }
    fielder[0x1D5] = 0;
    fielder[0x1D6] = 0;
    *(s16*)(fielder + 0x1A4) = 0;
    *(s16*)(fielder + 0x1AC) = 0;
    fielder[0x1FF] = 0;
    if (arg1 == 0x18) {
        *(s16*)((u8*)&g_FieldingLogic + 0xBC) = arg0;
    }
}

// fn_3_598D0, size:0x48
void fn_3_598D0(void) {
    fn_3_58688();
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        fn_3_583B8();
    } else {
        fn_3_3B9E4();
    }
}

// fn_3_5B408, size:0x14
void fn_3_5B408(void) {
    g_GameLogic.frame_exitMenuShowing = 0;
}

// fn_3_5B368, size:0x18
void fn_3_5B368(void) {
    g_GameLogic.frames_memoryCardWriteOnMVP = 0;
    g_GameLogic.endGameStage = 0;
}

// fn_3_5A684, size:0x1C
void fn_3_5A684(void) {
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes.outs = 0;
    g_Strikes.forcedOutToEndInningInd = 0;
}

// fn_3_59AC0, size:0x24
void fn_3_59AC0(s32 unused1, s32 unused2, void* allocation) {
    fn_80017D28(allocation);
}

// fn_3_59A90, size:0x30
void fn_3_59A90(void) {
    g_UnkSound_32718._02 = 0;
    g_UnkSound_32718._03 = 0;
    g_UnkSound_32718._04 = 0;
    g_UnkSound_32718._05 = 0;
    g_UnkSound_32718._06 = 0;
    g_UnkSound_32718._00 = 0;
    g_UnkSound_32718._07 = 0;
    g_UnkSound_32718._08 = 0;
}

// fn_3_59AE4, size:0x3C
s32 fn_3_59AE4(void) {
    if (g_d_GameSettings.GameModeSelected == 6) {
        return fn_80022B68();
    }
    return 1;
}

// fn_3_5A6D4, size:0x28
void fn_3_5A6D4(u8 status) {
    s8 previous;
    GameControlsStruct* game = &g_GameLogic;
    previous = game->gameStatus;
    game->FrameCountOfCurrentPitch = 0;
    game->gameStatus_prev = previous;
    game->gameStatus = status;
    game->FrameCountOfCurrentAtBat_Copy = 0;
    game->_125 = 0;
}

// fn_3_5ED98, size:0x40
void fn_3_5ED98(void) {
    fn_3_5A6D4(2);
    *(s16*)((u8*)&g_FieldingLogic + 0xAE) = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
}

// fn_3_5A6A0, size:0x34
void fn_3_5A6A0(s32 a, s32 b, s32 c, s32 d) {
    GameControlsStruct* g = &g_GameLogic;
    g->homeTeamBattingInd_fieldingTeam = a;
    g->awayTeamBattingInd_battingTeam = a ^ 1;
    *(s32*)g = b;
    g->teamBatting = b ^ a;
    g->teamFielding = g->teamBatting ^ 1;
    *(s32*)((u8*)g + 0x1C) = c;
    *(s32*)((u8*)g + 0x20) = d;
}

// fn_3_5CFD0, size:0xC4
void fn_3_5CFD0(void) {
    u8* t = (u8*)starMissionCompletionTracker;
    s32 a = t[0x441C];
    s32 b = t[0x441E];
    if (g_d_GameSettings.exhibitionMatchInd == 0 && *(s16*)(g_Scores + 0xA4) <= 1 &&
        (*(s16*)(g_Scores + 0xA4) ^ (*(s32*)&g_GameLogic == *(s16*)(lbl_3_common_bss_37400 + 0x40))) != 0) {
        if ((t[0x4422] >= 4 && b == 5) || (t[0x4422] >= 5 && *(s8*)(t + 0x44EF) == 1 && a == 5)) {
            g_GameLogic.playOverFadeOutStarted = 0;
        }
        starMissionRelated2();
    }
}

// fn_3_5C5C8, size:0xD4
void fn_3_5C5C8(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        u8 st = g_Runners[i].runnerOnFieldOrOutOrScored;
        if (st == 1 || st == 3 || st == 4) {
            *(s16*)(g_Scores + 0x9C) += 1;
            g_Runners[i].runnerOnFieldOrOutOrScored = 3;
        }
    }
}

// fn_3_5C418, size:0x118
void fn_3_5C418(void) {
    s32 inScene = 0;
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2 || (u8)(g_GameLogic.gameStatus - 0x13) <= 3 ||
        g_GameLogic.gameStatus == 7) {
        inScene = 1;
    }
    if (unkSimulationRelatedStruct._08 == 0) {
        if (lbl_803C77B8._02 & 0x1000) {
            unkSimulationRelatedStruct._08 = 1;
        }
    } else {
        if (inScene != 0) {
            changeScene(3, 6);
        }
        if (lbl_8037169C[0x13] != 0 && inScene != 0) {
            if ((s32)lbl_803C6CF8[0x715] == 1) {
                lbl_3_common_bss_32724[0x96] = 1;
                g_GameLogic.framesOfExitingToMenu = 1;
                return;
            }
            if (unkSimulationRelatedStruct._09 == 0) {
                fn_800A7568();
                unkSimulationRelatedStruct._09 = 1;
            }
        }
    }
}

// fn_3_5D3FC, size:0x120
void fn_3_5D3FC(void) {
    s32 stage;
    GameInitVariables* gs = &g_d_GameSettings;
    s32 inning;
    u8 finalInning;
    ((u8*)&g_GameLogic)[0x135] = 0;
    ((u8*)&g_GameLogic)[0x136] = 0;
    g_RunningLogic[0x11] = 0;
    g_RunningLogic[0x13] = 0;
    *(s16*)(g_RunningLogic + 2) = 0;
    inning = *(s32*)g_Scores;
    finalInning = g_Scores[0xAA];
    if (inning > finalInning) {
        stage = 5;
    } else if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores[0xAD] != 0) {
            stage = 4;
        } else {
            stage = 0;
        }
    } else if (inning == finalInning) {
        stage = 4;
    } else if ((finalInning == 9 && inning >= 7) || (finalInning == 7 && inning >= 6)) {
        stage = 3;
    } else if (inning >= 4) {
        stage = 2;
    } else {
        stage = 1;
    }
    g_Scores[0xAC] = stage;
    g_Scores[0xC1] = 0;
    g_Scores[0xC6] = 0;
    lbl_3_common_bss_37400[0x48] = 0;
    fn_3_6C13C(lbl_3_common_bss_37400, g_Scores);
    if (gs->exhibitionMatchInd == 0) {
        fn_3_16598C();
    }
}

// fn_3_5B220, size:0x148
s32 fn_3_5B220(s32 arg) {
    if (g_GameLogic.frames_memoryCardWriteOnMVP < 0x7FFE) {
        g_GameLogic.frames_memoryCardWriteOnMVP += 1;
    } else {
        g_GameLogic.frames_memoryCardWriteOnMVP = 0x7FFF;
    }
    switch ((s32)g_GameLogic.endGameStage) {
    case 0:
        if (arg == 1 && g_Minigame._1A3C == 0 && g_Minigame._1A44 == 0 && g_Minigame._1A45 == 0 && g_Minigame._1A43 == 0) {
            return 1;
        }
        fn_8003BF54(lbl_80366158[0x27], 0, 0, 1, 0, 4, 5, 0, 0);
        g_GameLogic.endGameStage += 1;
        break;
    case 1: {
        s16 v = ((s16*)*(u8**)&lbl_803CC1B8)[8];
        if (v == 1 || (u16)(v - 0xB) <= 1U || v == 7) {
            g_GameLogic.endGameStage += 1;
        }
        break;
    }
    default:
        return 1;
    }
    return 0;
}

// fn_3_5ACA0, size:0x16C
void fn_3_5ACA0(void) {
    GameInitVariables* gs;
    if (g_GameLogic.framesOfExitingToMenu != 0) {
        fn_3_5A6FC();
        return;
    }
    if (g_GameLogic.FrameCountOfCurrentPitch < 0xFFFE) {
        g_GameLogic.FrameCountOfCurrentPitch += 1;
    } else {
        g_GameLogic.FrameCountOfCurrentPitch = 0xFFFF;
    }
    if (g_GameLogic.FrameCountOfCurrentAtBat_Copy < 0xFFFE) {
        g_GameLogic.FrameCountOfCurrentAtBat_Copy += 1;
    } else {
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0xFFFF;
    }
    fn_3_FF4C();
    fn_3_6D304();
    gs = &g_d_GameSettings;
    if (gs->GameModeSelected != 6 && gs->GameModeSelected != 7) {
        fn_3_7D458();
    }
    fn_3_668BC();
    if (gs->GameModeSelected == 2) {
        fn_3_B482C();
    } else if (gs->GameModeSelected == 6) {
        fn_3_DFBAC();
    } else if (gs->GameModeSelected == 7) {
        fn_3_10FDC8();
    } else if (g_GameLogic.secondaryGameMode == 0) {
        fn_3_6011C();
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_66140();
    } else {
        fn_3_664FC();
    }
    fn_3_BBF94();
    if (lbl_8036E548[0x3088] != 0) {
        fn_3_B93CC();
    }
    if (gs->GameModeSelected == 4 && lbl_80366158[0x2A] == 0) {
        lbl_80366158[0x2A] = 1;
    }
}

// fn_3_59918, size:0x178
void fn_3_59918(s32 x) {
    u8 gs;
    s32 i;
    if (g_Stats.replayInd != 0) {
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 1 && g_Ball.deadBallReason != 2) {
        return;
    }
    gs = g_d_GameSettings.GameModeSelected;
    if (gs == 2 && (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6)) {
        if (x == 5) {
            return;
        }
    } else if (gs == 2 && g_Practice._186 != 0) {
        return;
    }
    if (gs == 6 && x == 5) {
        if (lbl_3_common_bss_32724[0xD3] != 0) {
            return;
        }
        lbl_3_common_bss_32724[0xD3] = 1;
    }
    if (g_GameLogic.playOver != 0) {
        return;
    }
    if (g_Scores[0xC5] != 0) {
        return;
    }
    if (x == 4) {
        if (g_Scores[0xC4] != 0) {
            return;
        }
        g_Scores[0xC4] = 1;
    }
    if (x == 0xD || x == 0x11) {
        if (g_Scores[0xC5] != 0) {
            return;
        }
        g_Scores[0xC5] = 1;
        g_GameLogic.gameOverInd = 1;
    }
    for (i = 0; i < 5; i++) {
        if (((u8*)&g_UnkSound_32718)[i + 2] == 0) {
            ((u8*)&g_UnkSound_32718)[i + 2] = x;
            return;
        }
    }
}

// fn_3_5A6FC, size:0x180
void fn_3_5A6FC(void) {
    switch ((s32)g_GameLogic.framesOfExitingToMenu) {
    case 1:
        if (g_d_GameSettings.GameModeSelected == 5 && g_d_GameSettings.bJMatchInd == 1) {
            g_d_GameSettings.home_AwaySetting ^= 1;
        }
        fn_3_BF1AC();
        lbl_3_common_bss_32724[0x96] = 1;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            fn_3_90CB0();
            if (g_d_GameSettings.GameModeSelected != 6) {
                fn_3_B95EC();
            }
        } else {
            fn_3_B95EC();
        }
        fn_8001E474();
        fn_3_BC224();
        fn_3_972C8();
        fn_8001F228();
        fn_3_902FC();
        fn_3_8C07C();
        g_GameLogic.framesOfExitingToMenu += 1;
        g_d_GameSettings._55 = 1;
        return;
    case 2:
        g_GameLogic.framesOfExitingToMenu += 1;
        return;
    case 29:
        fn_3_90434();
        g_GameLogic.framesOfExitingToMenu += 1;
        return;
    case 30:
        if (g_GameLogic._128 != 0) {
            lbl_80366158[0x1C] = 2;
        } else {
            lbl_80366158[0x1C] = 1;
        }
        g_d_GameSettings.minigamesEnabled = 0;
        return;
    default:
        g_GameLogic.framesOfExitingToMenu += 1;
        return;
    }
}

// fn_3_5EE58, size:0x194
void fn_3_5EE58(void) {
    if (g_Stats.replayInd == 0) {
        fn_3_7CE90();
        fn_3_77914();
        g_GameLogic.playOverInd = 0;
        if (g_GameLogic.freeFieldingPracticeInd != 0) {
            fn_3_899BC();
            fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            if (g_d_GameSettings.exhibitionMatchInd == 0 &&
                (*(s32*)&g_GameLogic ^ (*(s16*)(g_Scores + 0xA4) == g_d_GameSettings.humanTeamNumber)) != 0) {
                fn_8006C9D8();
            }
        } else if (g_Strikes.outs >= 3) {
            if (g_FieldingLogic._107 < 1U || g_FieldingLogic._107 > 3U || g_Strikes.balls >= 4) {
                fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
            }
            if (g_d_GameSettings.GameModeSelected == 2 && (g_Practice.practiceLevel == 7 || g_Practice.practiceLevel == 6)) {
                fn_3_899BC();
            }
        } else {
            fn_3_899BC();
            fn_3_9E7D4(g_GameLogic.homeTeamBattingInd_fieldingTeam);
        }
        fn_3_5A6D4(8);
        if (g_GameLogic.secondaryGameMode == 0 && ((u8*)&g_Stats)[0x39] == 1) {
            ((u8*)&g_Stats)[0x39] = 2;
        }
        fn_3_BF1AC();
        fn_3_BF158();
    }
}
