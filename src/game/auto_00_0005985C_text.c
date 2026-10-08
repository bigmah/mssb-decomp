#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern s32 fn_80022B68(void);

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

#pragma dont_inline on

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
