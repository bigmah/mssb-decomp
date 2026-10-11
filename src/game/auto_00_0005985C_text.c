#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"
#include "main/file_8004207C.h"
#include "main/file_80069BDC.h"

extern s32 fn_80022B68(void);
// From main/file_80021308.h (not includable here: its sound prototypes clash
// with include/static/UnknownHomes_Static.h).
typedef struct DiskFileEntry {
    /* 0x0 */ u32 offset;
    /* 0x4 */ u32 sizeFlags;
    /* 0x8 */ u32 aramOffset;
    /* 0xC */ u32 unkC;
} DiskFileEntry; // size: 0x10
typedef void (*AramQueueCallback)(DiskFileEntry* entry, void* dst, void* user);
extern s32 fn_80022CB4(DiskFileEntry* entry, void* dst, s32 mode, u32 aramAddr, AramQueueCallback callback, void* user);
extern DiskFileEntry lbl_800F1D78[];
extern DiskFileEntry lbl_3_data_3D70;
extern u8 lbl_3_data_3D80[0x430];
extern void fn_800216F8(u8 group, s32 (*callback)(void));
extern s32 fn_3_91064(void);
extern s32 fn_3_90798(void);
extern s32 fn_3_90928(void);
extern void fn_3_906FC(void);
extern void manageLoadingState(void);
extern void fn_8001CE74(void);
extern void fn_3_B42A8(void);
extern void fn_8001A3FC(s32 arg);
extern void fn_80019A60(void);
extern s32 fn_3_1665E4(void);
extern s32 fn_3_106E50(void);
extern void fn_3_106DFC(void);

// View of lbl_8036E548 (CharMgr in main/file_80011640.h, which can't be
// included here next to main/file_8004207C.h: their fn_80024D2C prototypes clash).
typedef struct {
    /*0x000*/ u8 _000[0xC];
    /*0x00C*/ void** _0C;
    /*0x010*/ u8 _010[0x252 - 0x10];
    /*0x252*/ s8 kind;
    /*0x253*/ u8 _253[0x27C - 0x253];
} CharActorView; // size: 0x27C

typedef struct {
    /*0x0000*/ u8 _0000[0x6C];
    /*0x006C*/ void* slots6C;
    /*0x0070*/ u8 _0070[0xC04 - 0x70];
    /*0x0C04*/ CharActorView actors[13];
    /*0x2C50*/ u8 _2C50[0x2D3C - 0x2C50];
    /*0x2D3C*/ struct {
        void* buffer;
        u32 size;
        s16 id;
        u8 state;
    } preload[3];
    /*0x2D60*/ u8 _2D60[0x2D7D - 0x2D60];
    /*0x2D7D*/ u8 _2D7D;
    /*0x2D7E*/ u8 _2D7E[0x307A - 0x2D7E];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B;
    /*0x307C*/ u8 _307C;
    /*0x307D*/ u8 _307D;
    /*0x307E*/ u8 _307E;
    /*0x307F*/ u8 _307F[0x3088 - 0x307F];
    /*0x3088*/ u8 _3088;
    /*0x3089*/ u8 _3089[0x3154 - 0x3089];
} CharMgrView; // size: 0x3154
extern CharMgrView lbl_8036E548;
extern void fn_3_1E178(void);
extern void fn_3_7AFE4(void);
extern void setBatterContactConstants(void);
extern void fn_3_AFDA4(void);
extern void fn_3_1E154(void);
extern s32 fn_3_B32B8(void);
extern void fn_3_AFB64(void);
extern void fn_3_AFA64(void);
extern void fn_3_75560(void);
extern void atBat_batter(void);
extern void fn_3_31594(void);
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
extern u8 lbl_3_common_bss_34C90[];
extern void fn_3_6C13C(void*, void*);
extern void fn_3_16598C(void);
extern u8 g_RunningLogic[];
extern void fn_800A7568(void);
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
extern ScoresStruct g_Scores;
extern void fn_3_32090(void*, void*);
extern void fn_3_8911C(void);
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_75434(void);
extern void fn_3_59338(void);
extern void fn_3_7B130(void);
extern void fn_3_22850(void);
extern int __abs(int);
extern u32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);
extern u8 lbl_800EFBA4[]; // menu sound volumes
extern void fn_3_7AF68(void);
extern void fn_3_9DB5C(void);
extern void fn_3_6C0E0(void);
extern void fn_3_67130(void);
extern void fn_3_8FC0C(void);
extern void fn_3_76558(void);
extern void* memset(void*, int, unsigned long);
extern void sndVolume(u8 volume, u16 time, u8 volGroup);
extern void fn_3_59F40(void);
extern void fn_3_59C2C(void);
extern void fn_3_5A28C(void);
extern s32 fn_3_6C938(s32, s32);
extern s32 fn_3_FD9FC(void);
extern void fn_3_90328(s32 vol);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern s16 fn_3_6BD6C(void);
extern u8 lbl_3_data_6104[8];
extern void fn_3_6EF1C(void);
extern void fn_3_754B8(void);
extern void initializeInMemBatter(void);
extern void fn_3_FBA8(void);
extern void fn_3_595C4(void);
extern void fn_3_8A5A4(void);
extern void fn_3_1E328(void);
extern void fn_3_7B308(void);
extern void fn_3_9DBE4(void);
extern void fn_3_7D780(void);
extern void fn_3_8FF18(void);
extern void fn_3_250FC(void);
extern void fn_3_8BE8C(void);
extern void initializeUnknown(void);
extern s32 fn_8004CA6C(u16 buttons);
extern s32 fn_3_10007C(void);
extern void fn_3_E19E8(void);
extern void fn_3_6C1D8(void);
extern void fn_3_1663AC(void);
extern void fn_3_1CE90(void);
extern void fn_3_8DA80(void);

typedef struct {
    /*0x00*/ s32 simulatedFrames; // frames the game logic actually ran
    /*0x04*/ s32 totalFrames;
    /*0x08*/ s32 randomInt1; // copy of g_Ball.StaticRandomInt1
    /*0x0C*/ s32 randomInt2; // copy of g_Ball.StaticRandomInt2
    /*0x10*/ u8 _10;
} FrameCounters; // size: 0x14
extern FrameCounters lbl_3_data_228;

typedef struct {
    /*0x00*/ s16 resultCoins[3]; // indexed by result: 0 win, 1 tie, 2 loss
    /*0x06*/ s16 winMarginPercent;
    /*0x08*/ s16 lossMarginPercent;
    /*0x0A*/ s16 starPercent;
    /*0x0C*/ s16 _0C[3];
    /*0x12*/ s16 bjCoins[3];
    /*0x18*/ s16 bjPoints[3];
    /*0x1E*/ s16 _1E;
} CoinRewardTable; // size: 0x20
extern CoinRewardTable lbl_3_data_607C;
extern void fn_8004CC2C(void);

#pragma dont_inline on

// fn_3_5D51C, size:0xCC
void fn_3_5D51C(void) {
    ScoresStruct* scores = &g_Scores;
    if (scores->bottomHalf == 0) {
        scores->bottomHalf = 1;
    } else {
        scores->bottomHalf = 0;
        scores->inning += 1;
    }
    g_GameLogic.homeTeamBattingInd_fieldingTeam ^= 1;
    g_GameLogic.awayTeamBattingInd_battingTeam ^= 1;
    g_GameLogic.teamBatting ^= 1;
    g_GameLogic.teamFielding ^= 1;
    ((u8*)&g_GameLogic)[0x131] = 0;
    ((u8*)&g_GameLogic)[0x132] = 0;
    g_Scores._A0 = g_Scores.runs[scores->bottomHalf][0];
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
    g_FieldingLogic._0AE = 0;
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
        if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
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
    u8 finalInning = g_Scores.finalInning;
    if (inning > finalInning) {
        return 5;
    }
    if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores.bottomHalf != 0) {
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
    lbl_803CC1B8->func = fn_3_5B0C4;
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
    g_FieldingLogic._0AE = 0;
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
    SceneTask* queue = lbl_803CC1B8;
    if (stage < 1) {
        return 0;
    }
    if (stage == 1) {
        fn_8001AAA4();
    }
    if (queue->_10 != 0) {
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
        g_FieldingLogic._0F8[arg0] = v;
    }
    fielder[0x1D5] = 0;
    fielder[0x1D6] = 0;
    *(s16*)(fielder + 0x1A4) = 0;
    *(s16*)(fielder + 0x1AC) = 0;
    fielder[0x1FF] = 0;
    if (arg1 == 0x18) {
        g_FieldingLogic._0BC = arg0;
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
void fn_3_59AC0(DiskFileEntry* entry, void* dst, void* allocation) {
    fn_80017D28(allocation);
}

// fn_3_59B20, size:0xAC
void fn_3_59B20(void) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 0; i < 4; i++) {
            CharActorView* actor = &lbl_8036E548.actors[i];
            fn_80022CB4(&lbl_800F1D78[actor->kind * 0x13 + 1], actor->_0C, 0, 0, fn_3_59AC0, actor);
        }
    }
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
    g_FieldingLogic._0AE = 0;
    g_Pitcher.peachDaisyStarAnimationOn = 0;
}

// fn_3_5A6A0, size:0x34
void fn_3_5A6A0(s32 a, s32 b, s32 c, s32 d) {
    GameControlsStruct* g = &g_GameLogic;
    g->homeTeamBattingInd_fieldingTeam = a;
    g->awayTeamBattingInd_battingTeam = a ^ 1;
    g->_000 = b;
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
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Scores.winningTeam <= 1 &&
        (g_Scores.winningTeam ^ (g_GameLogic._000 == *(s16*)(lbl_3_common_bss_37400 + 0x40))) != 0) {
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
            g_Scores._9C += 1;
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
        if (lbl_8037169C._13 != 0 && inScene != 0) {
            if ((s32)lbl_803C6CF8._715 == 1) {
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
    inning = g_Scores.inning;
    finalInning = g_Scores.finalInning;
    if (inning > finalInning) {
        stage = 5;
    } else if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores.bottomHalf != 0) {
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
    g_Scores.inningStage = stage;
    g_Scores._C1 = 0;
    g_Scores._C6 = 0;
    lbl_3_common_bss_37400[0x48] = 0;
    fn_3_6C13C(lbl_3_common_bss_37400, &g_Scores);
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
        fn_8003BF54(lbl_80366158._27, 0, 0, 1, 0, 4, 5, 0, 0);
        g_GameLogic.endGameStage += 1;
        break;
    case 1: {
        s16 v = lbl_803CC1B8->_10;
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
    if (lbl_8036E548._3088 != 0) {
        fn_3_B93CC();
    }
    if (gs->GameModeSelected == 4 && lbl_80366158._2A == 0) {
        lbl_80366158._2A = 1;
    }
}

// fn_3_59918, size:0x178
void fn_3_59918(s32 x, s32 unused) {
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
    if (g_Scores._C5 != 0) {
        return;
    }
    if (x == 4) {
        if (g_Scores._C4 != 0) {
            return;
        }
        g_Scores._C4 = 1;
    }
    if (x == 0xD || x == 0x11) {
        if (g_Scores._C5 != 0) {
            return;
        }
        g_Scores._C5 = 1;
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
            lbl_80366158._1C = 2;
        } else {
            lbl_80366158._1C = 1;
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
                (g_GameLogic._000 ^ (g_Scores.winningTeam == g_d_GameSettings.humanTeamNumber)) != 0) {
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

// fn_3_5EFEC, size:0x168
void fn_3_5EFEC(void) {
    GameControlsStruct* game = &g_GameLogic;
    if (game->freeFieldingPracticeInd != 0) {
        if (fn_3_B32B8() != 0 || g_Practice.pauseMenuLoading != 0) {
            return;
        }
    } else {
        fn_3_AFB64();
        if (lbl_3_common_bss_34C90[0x1D5] != 0) {
            fn_3_AFA64();
            return;
        }
    }
    if (g_GameLogic.frameCountdownAtBeginningOfAtBatLockout != 0) {
        g_GameLogic.frameCountdownAtBeginningOfAtBatLockout -= 1;
    }
    fn_3_75560();
    atBat_batter();
    fn_3_31594();
    fn_3_8A958();
    fn_3_5C74C(0);
    if (game->freeFieldingPracticeInd == 0 && (g_Strikes.outs >= 3 || (g_Strikes.storedOuts == 2 && g_Pitcher.strikeOutOrWalk == 1)) &&
        g_GameLogic.EventTriggers_EndOfGame == 0) {
        fn_3_5D094(0);
        if (g_GameLogic.EventTriggers_EndOfGame != 0) {
            fn_3_59918(0xD, 0);
        } else if (g_Scores._C3 == 0) {
            fn_3_59918(5, 0);
            g_Scores._C3 = 1;
        }
    }
    if (g_Pitcher.pitcherActionState == 6) {
        fn_3_5EE58();
    }
}

// fn_3_5F7A8, size:0x188
void fn_3_5F7A8(void) {
    s32 stage;
    GameInitVariables* gs = &g_d_GameSettings;
    s32 inning;
    u8 finalInning;
    ((u8*)&g_GameLogic)[0x135] = 0;
    ((u8*)&g_GameLogic)[0x136] = 0;
    g_RunningLogic[0x11] = 0;
    g_RunningLogic[0x13] = 0;
    *(s16*)(g_RunningLogic + 2) = 0;
    inning = g_Scores.inning;
    finalInning = g_Scores.finalInning;
    if (inning > finalInning) {
        stage = 5;
    } else if (finalInning <= 3U) {
        if (finalInning == inning && g_Scores.bottomHalf != 0) {
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
    g_Scores.inningStage = stage;
    g_Scores._C1 = 0;
    g_Scores._C6 = 0;
    lbl_3_common_bss_37400[0x48] = 0;
    fn_3_6C13C(lbl_3_common_bss_37400, &g_Scores);
    if (gs->exhibitionMatchInd == 0) {
        fn_3_16598C();
    }
    fn_3_5A684();
    fn_3_75434();
    fn_3_59338();
    fn_3_8A350();
    fn_3_1E178();
    fn_3_AFDA4();
    ((void (*)(void))fn_3_6C13C)();
    fn_3_7B130();
    setBatterContactConstants();
    ((void (*)(void))fn_3_8A1D8)();
    fn_3_7AFE4();
    fn_3_1E154();
    fn_3_6C108();
    g_Strikes.strikes = 0;
    g_Strikes.balls = 0;
    g_Strikes._1E = -1;
    g_Strikes.stateRelated = 0;
    g_GameLogic.frameCountdownAtBeginningOfAtBatLockout = 0x5A;
    ((u8*)&g_GameLogic)[0x13D] = 0;
}

// fn_3_5B380, size:0x88
s32 fn_3_5B380(void) {
    u16 buttons; // never set in the original: the call reads whatever is in r3
    if (g_GameLogic.frame_exitMenuShowing < 0x7FFE) {
        g_GameLogic.frame_exitMenuShowing += 1;
    } else {
        g_GameLogic.frame_exitMenuShowing = 0x7FFF;
    }
    if (g_GameLogic.frame_exitMenuShowing > 0x14) {
        s32 choice = fn_8004CA6C(buttons);
        if (choice == 1) {
            return 1;
        } else if (choice == 2) {
            fn_8004CC2C();
        } else if (choice == 4) {
            return 2;
        }
    }
    return 0;
}

// fn_3_5B0C4, size:0x15C
void fn_3_5B0C4(void) {
    g_d_GameSettings.FrameCountWhileNotAtMainMenu++;
    lbl_80366158._28 = 0;
    lbl_80366158._28 = 0;
    fn_3_10007C();
    if (unkSimulationRelatedStruct._05 != 0) {
        if (unkSimulationRelatedStruct._06 == 0) {
            unkSimulationRelatedStruct._05 = 0;
        } else {
            unkSimulationRelatedStruct._06 -= 1;
            *lbl_803CBC3C = 1;
            goto skip;
        }
    }
    if (g_GameLogic.PauseSimulationFrameCount != 0) {
        if (--g_GameLogic.PauseSimulationFrameCount != 0) {
            lbl_80366158._28 = 1;
        } else {
            lbl_80366158._28 = 0;
        }
    }
    if (lbl_80366158._28 == 0) {
        lbl_3_data_228.simulatedFrames += 1;
        fn_3_5ACA0();
    }
skip:
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_E19E8();
    } else {
        fn_3_6C1D8();
        if (g_d_GameSettings.GameModeSelected == 2) {
            fn_3_1663AC();
        }
    }
    fn_3_1CE90();
    fn_3_8DA80();
    lbl_3_data_228.randomInt1 = g_Ball.StaticRandomInt1;
    lbl_3_data_228.randomInt2 = g_Ball.StaticRandomInt2;
    lbl_3_data_228.totalFrames += 1;
}

// fn_3_5B41C, size:0x184
void fn_3_5B41C(void) {
    s32 result = 2;
    s32 margin;
    if (g_Scores.winningTeam == 2) {
        result = 1;
    } else if (g_Scores.winningTeam == g_GameLogic._000) {
        result = 0;
    }
    if (g_d_GameSettings.bJMatchInd == 0) {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C.resultCoins[result];
        margin = __abs(g_Scores.runs[g_GameLogic._000][0] - g_Scores.runs[g_GameLogic._000 ^ 1][0]);
        if (result == 0) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += margin * lbl_3_data_607C.winMarginPercent / 100;
        } else if (result == 2) {
            g_d_GameSettings.challengeMinigame_baseCoinsEarned += margin * lbl_3_data_607C.lossMarginPercent / 100;
        }
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += g_GameLogic.TeamStars[0] * lbl_3_data_607C.starPercent / 100;
    } else {
        g_d_GameSettings.challengeMinigame_baseCoinsEarned += lbl_3_data_607C.bjCoins[result];
        g_d_GameSettings.bJMatchRelated += lbl_3_data_607C.bjPoints[result];
    }
}

// fn_3_5FF10, size:0x20C
void fn_3_5FF10(void) {
    s32 i;
    fn_3_6EF1C();
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
    g_GameLogic.TeamStars[0] = lbl_8034E9A0._470F[0];
    g_GameLogic.TeamStars[1] = lbl_8034E9A0._470F[1];
    if (lbl_800E8754._04 == 0) {
        g_GameLogic.TeamStars[0] = 0;
        g_GameLogic.TeamStars[1] = 0;
    }
    g_GameLogic.IsStarChance = 0;
    g_GameLogic.freeFieldingPracticeInd = 0;
    g_GameLogic.gameOverInd = 0;
    g_GameLogic.scoutFlag_VsScreenInd = 0;
    g_GameLogic.playBatterWalkupAnimation = 0;
    g_Scores.winningTeam = -1;
    g_Scores._AE = 0;
    g_Scores.inning = 1;
    g_Scores.bottomHalf = 0;
    g_Scores._C6 = 0;
    for (i = 0; i < 19; i++) {
        g_Scores.runs[0][i] = 0;
        g_Scores.runs[1][i] = 0;
        g_Scores._50[0][i] = 0;
        g_Scores._50[1][i] = 0;
    }
    for (i = 0; i < 2; i++) {
        g_Scores._A8[i] = 0;
        g_Scores._B3[i] = -1;
        g_Scores._B5[i] = -1;
        g_Scores._B7[i] = -1;
        g_Scores._B9[i] = 0;
        g_Scores._AF[i] = g_GameLogic.battingOrderAndPositionMapping[i][0][0];
        g_Scores._BB[i] = 1;
        g_Scores._BD[i] = 1;
    }
    fn_3_5A6D4(4);
    fn_3_754B8();
    initializeInMemBatter();
    fn_3_FBA8();
    fn_3_595C4();
    fn_3_8A5A4();
    fn_3_1E328();
    fn_3_7B308();
    fn_3_9DBE4();
    fn_3_7D780();
    fn_3_8FF18();
    fn_3_250FC();
    fn_3_8BE8C();
    initializeUnknown();
}

// fn_3_5CDB4, size:0x21C
void fn_3_5CDB4(void) {
    GameControlsStruct* game = &g_GameLogic;
    switch (game->_125) {
    case 0:
        changeScene(1, 6);
        g_GameLogic.scoreBook_teamDisplayed = 0;
        lbl_3_common_bss_32724[0x9B] = 0;
        lbl_3_common_bss_32724[0x9A] = 0;
        game->_125 = 1;
        break;
    case 1:
        if ((s8)game->playOverFadeOutStarted < 0 || game->scoreBook_teamDisplayed != 0) {
            if (g_GameLogic.FrameCountOfCurrentPitch >= 40 && fn_3_6C938(1, 0x1300) != 0) {
                game->_125 = 2;
            }
            if (fn_3_FD9FC() != 0) {
                game->_125 = 2;
            }
        }
        break;
    case 2:
        if (g_d_GameSettings.exhibitionMatchInd == 0 && g_d_GameSettings.bJMatchInd == 1) {
            fn_800203E0(0xC, (s8)lbl_3_data_6104[gChallengeState._441C]);
        } else {
            changeScene(3, 6);
        }
        fn_3_90328(-1);
        game->_125 = 3;
        break;
    case 3:
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            game->_125 = 4;
        }
        break;
    case 4:
        if ((s8)game->playOverFadeOutStarted >= 0) {
            fn_3_5A6D4(0xE);
            fn_3_8C07C();
        } else if (g_d_GameSettings.exhibitionMatchInd == 0 && g_d_GameSettings.bJMatchInd == 1) {
            game->_125 = 5;
        } else {
            fn_3_5A6D4(0xE);
            fn_3_8C07C();
        }
        break;
    case 5:
        fn_3_8C07C();
        game->_125 = 6;
        break;
    case 6:
        game->_128 = 1;
        game->framesOfExitingToMenu = 1;
        break;
    }
    game = &g_GameLogic;
    if ((s8)game->playOverFadeOutStarted >= 0 && game->scoreBook_teamDisplayed == 0) {
        game->teamFielding = (s8)game->playOverFadeOutStarted;
        game->scoreBook_teamDisplayed = fn_3_6BD6C();
    }
}

// fn_3_5DD30, size:0x224
// NONMATCHING 89%: register allocation only (walk-off loop counters, case 3 tail scheduling)
#if NONMATCHING
void fn_3_5DD30(void) {
    s32 homeRuns;
    s32 i;
    s32 scored = 0;
    if (g_Ball.deadBallRBIsAddedInd != 0) {
        return;
    }
    if (g_Ball.deadBallReason == 3) {
        if (g_Runners[2].runnerOnFieldOrOutOrScored != 0) {
            scored = 1;
            g_Runners[2].scoredOnGRD = 1;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored != 0) {
            scored++;
            g_Runners[3].scoredOnGRD = 1;
        }
        if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf != 0 &&
            g_Scores.runs[0][0] == g_Scores._9E && scored == 2) {
            scored = 1;
            g_Runners[2].scoredOnGRD = 0;
        }
        g_Ball.deadBallRBIsAddedInd = 1;
        lbl_3_common_bss_32A94._26 = scored;
        g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning] = g_Scores._9E;
        g_Scores._9C = scored;
        if (g_Ball.AtBat_ContactResult == 0) {
            g_Ball.AtBat_ContactResult = 1;
        }
    } else if (g_Ball.deadBallReason == 4) {
        homeRuns = g_Scores.runs[1][0];
        for (i = 3; i >= 0; i--) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && (i >= 2 || g_Runners[i].baseReachedAtTimeOfThrow >= 2)) {
                g_Runners[i].scoredOnGRD = 1;
                homeRuns++;
                scored++;
            }
            if (g_Scores.inning >= g_Scores.finalInning && g_Scores.bottomHalf != 0 && g_Scores.runs[0][0] < homeRuns) {
                break;
            }
        }
        g_Scores._9C = scored;
        g_Ball.deadBallRBIsAddedInd = 1;
        lbl_3_common_bss_32A94._26 = scored;
        if (g_Ball.AtBat_ContactResult == 0) {
            g_Ball.AtBat_ContactResult = 1;
        }
    }
}
#endif

// fn_3_5AE9C, size:0x228
void fn_3_5AE9C(void) {
    changeScene(4, 0);
    g_GameLogic.framesOfExitingToMenu = 0;
    unkSimulationRelatedStruct._04 = 0;
    unkSimulationRelatedStruct._09 = 0;
    lbl_8036E548._307E = 0;
    g_d_GameSettings.minigamesEnabled = 0;
    g_d_GameSettings._13 = 0;
    g_d_GameSettings.someChallengeModeFlag = 0;
    lbl_8036E548._307A = 0;
    lbl_8036E548.slots6C = NULL;
    lbl_8036E548._307C = 0;
    lbl_8036E548._307D = 0;
    lbl_3_common_bss_32724[0xA4] = 0;
    g_d_GameSettings._55 = 0;
    g_d_GameSettings.challengeMinigame_baseCoinsEarned = 0;
    g_d_GameSettings.bJMatchRelated = 0;
    lbl_8036E548.preload[0].id = -1;
    lbl_8036E548.preload[1].id = -1;
    lbl_8036E548.preload[2].id = -1;
    g_GameLogic.teams[0] = g_d_GameSettings.PlayerPorts[0];
    g_GameLogic.teams[1] = g_d_GameSettings.PlayerPorts[1] % 4;
    g_GameLogic.logo[0].ID = lbl_8034E9A0._470D[g_d_GameSettings.home_AwaySetting];
    g_GameLogic.logo[1].ID = lbl_8034E9A0._470D[g_d_GameSettings.home_AwaySetting ^ 1];
    g_GameLogic.logo[0].variationID = g_GameLogic.logo[0].ID % 4;
    g_GameLogic.logo[1].variationID = g_GameLogic.logo[1].ID % 4;
    g_GameLogic.logo[0].captain = g_GameLogic.logo[0].ID / 4;
    g_GameLogic.logo[1].captain = g_GameLogic.logo[1].ID / 4;
    g_Scores._C7 = lbl_800E8754._05;
    if (g_d_GameSettings.GameModeSelected == 6 || g_d_GameSettings.GameModeSelected == 7) {
        g_d_GameSettings.minigamesEnabled = 1;
    }
    memset(&g_Minigame, 0, 0x1E2C);
    g_Minigame.GameMode_MiniGame = 0;
    sndVolume(0x7F, 0xA, 0xFF);
    if (g_d_GameSettings.GameModeSelected == 6 || g_d_GameSettings.GameModeSelected == 7) {
        lbl_8036E548._2D7D = 0;
        lbl_3_common_bss_32724[0xD7] = 0;
        lbl_803CC1B8->func = fn_3_59F40;
    } else if (g_d_GameSettings.GameModeSelected == 2) {
        lbl_803CC1B8->func = fn_3_59C2C;
    } else {
        lbl_803CC1B8->func = fn_3_5A28C;
    }
}

// fn_3_5DA9C, size:0x244
void fn_3_5DA9C(void) {
    fn_3_6B870();
    if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (g_d_GameSettings.exhibitionMatchInd == 0 &&
            (g_GameLogic._000 ^ (g_Scores.winningTeam == g_d_GameSettings.humanTeamNumber)) != 0 &&
            (g_d_GameSettings.bJMatchInd != 1 ||
             (g_GameLogic._000 ^ (g_Scores.winningTeam != g_d_GameSettings.humanTeamNumber)) == 0)) {
            fn_8006C9D8();
        }
        fn_3_76558();
    }
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    g_GameLogic.playOverInd = 0;
    g_Scores._C1 = g_Scores.runs[g_GameLogic.homeTeamBattingInd_fieldingTeam][0] - g_Scores._A0;
    g_Pitcher._15D = 0;
    if (g_d_GameSettings.GameModeSelected == 4 &&
        (lbl_3_data_228.simulatedFrames >= 0x2A30U || unkSimulationRelatedStruct._08 != 0)) {
        g_GameLogic.framesOfExitingToMenu = 1;
    } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
        if (g_Stats.replayInd == 0) { // inlined fn_3_5D9F8
            g_Pitcher._15C = 0;
            if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
                g_GameLogic.framesOfExitingToMenu = 1;
            } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                fn_3_5A6D4(9);
            } else {
                fn_3_5A6D4(3);
            }
        }
    } else if (g_Strikes.outs >= 3) {
        if (g_Stats.replayInd == 0) { // inlined fn_3_5D9F8
            g_Pitcher._15C = 0;
            if (g_d_GameSettings.GameModeSelected == 4 && g_Scores.bottomHalf == 0) {
                g_GameLogic.framesOfExitingToMenu = 1;
            } else if (g_GameLogic.EventTriggers_EndOfGame != 0) {
                fn_3_5A6D4(9);
            } else {
                fn_3_5A6D4(3);
            }
        }
    } else {
        fn_3_5A6D4(7);
    }
}

// fn_3_5F154, size:0x2A8
// NONMATCHING 99%: register allocation only (g_Scores base r8 vs r7 in the inlined fn_3_5F720 block)
#if NONMATCHING
void fn_3_5F154(void) {
    s32 diff;
    // inlined fn_3_5F720
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    fn_3_1DEB8();
    Set_803cb848(1);
    fn_3_6EBB4(g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.awayTeamBattingInd_battingTeam][0][0]);
    g_FieldingLogic._0AE = 0;
    g_GameLogic.homeRunWordAnimationCompletedInd = 0;
    unkSimulationRelatedStruct._05 = 0;
    unkSimulationRelatedStruct._06 = 4;
    g_Scores._9C = 0;
    g_Scores._9E = g_Scores.runs[g_Scores.bottomHalf][g_Scores.inning];
    g_Scores._A2 = g_Scores._A0;
    g_GameLogic._12F = 0;
    g_GameLogic._123 = 0;
    g_GameLogic.CountdownUntilFade = 999;
    g_GameLogic.PauseSimulationFrameCount = 0;
    g_GameLogic.playOver = 0;
    g_GameLogic.walkOffWinInd = 0;
    g_GameLogic.stadiumStarObtained = 0;
    g_Scores._A0 = g_Scores.runs[g_Scores.bottomHalf][0];
    g_Scores._C2 = 0;
    g_Scores._C4 = 0;
    g_Scores._C5 = 0;
    diff = g_Scores.runs[0][0] - g_Scores.runs[1][0];
    if (diff < -0x8000) {
        diff = -0x8000;
    }
    if (diff > 0x7FFF) {
        diff = 0x7FFF;
    }
    g_Scores._A6 = __abs(diff);
    g_Strikes.storedOuts = g_Strikes.outs;
    g_Strikes.runnerIndexForEachOutThisPitch[0] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[1] = -1;
    g_Strikes.runnerIndexForEachOutThisPitch[2] = -1;
    g_Strikes.GameControls_StrikeBallBitVector = g_Strikes.balls + g_Strikes.strikes * 16;
    g_Strikes.allForcedRunnersReachedTheirBaseInd = 0;
    g_Ball.totalFramesAtPlay = 0;
    g_FieldingLogic._10E = 0;
    g_FieldingLogic._0EE = 0;
    g_FieldingLogic._10F = 0;
    g_FieldingLogic._110 = 0;
    g_FieldingLogic._128 = 0;
    g_FieldingLogic._129 = 0;
    g_FieldingLogic._0E4 = 0;
    g_RunningLogic[0x13] = 0;
    lbl_3_common_bss_34C90[0x1D5] = 0;
    g_Practice._1B0 = 0;
    if (g_GameLogic.pre_PostMiniGameInd != 0) {
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_GameLogic.hudElementLoadingInd = 1;
        changeScene(1, 6);
    } else {
        g_GameLogic.minigameLastTurnSuccessInd = 0;
    }
    g_GameLogic.pre_PostMiniGameInd = 0;
    fn_3_5A6D4(1);
    if (g_GameLogic.playOverInd != 0) {
        g_GameLogic.playOverInd -= 1;
    }
    if (g_GameLogic.freeFieldingPracticeInd == 0 && g_GameLogic.EventTriggers_GameHasStarted == 0) {
        fn_3_59918(0xC, 0);
        g_GameLogic.EventTriggers_GameHasStarted = 1;
    }
    fn_3_7AF68();
    fn_3_9DB5C();
    fn_3_6C0E0();
    fn_3_67130();
    fn_3_8FC0C();
    if (lbl_3_common_bss_34C58._2A != 0) {
        lbl_3_common_bss_34C58._2A = 2;
        lbl_3_common_bss_34C58._24 = 120;
    }
}
#endif

// fn_3_5BA2C, size:0x314
void fn_3_5BA2C(void) {
    InputStruct* input = &g_Controls[lbl_80366158._27];
    if (lbl_3_common_bss_34C90[0x1D8] == 0) {
        if (input->newButtonInput & 0x100) {
            if ((s8)lbl_3_common_bss_34C90[0x1DA] == 0) {
                g_GameLogic._125 = 9;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else {
                lbl_3_common_bss_32724[0xCE] = 1;
                g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
                g_GameLogic._125 = 8;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (input->newButtonInput & 2) {
            if ((s8)lbl_3_common_bss_34C90[0x1DA] == 0) {
                lbl_3_common_bss_34C90[0x1DA] = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & 1) {
            if ((s32)lbl_3_common_bss_34C90[0x1DA] == 1) {
                lbl_3_common_bss_34C90[0x1DA] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (lbl_3_common_bss_32724[0xD2] == 0) {
        if (input->newButtonInput & 0x200) {
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 8;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if ((input->newButtonInput & 0x20) || (input->newButtonInput & 0x40)) {
            if (input->newButtonInput & 0x40) {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 0;
            } else {
                g_GameLogic.scoreBook_logoFadeDirectionLeft_Right = 1;
            }
            g_GameLogic.scoreBook_teamDisplayed ^= 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (input->newButtonInput & 2) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 0) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->newButtonInput & 1) {
            if (g_GameLogic.scoreBook_batter_pitcherStatsDisplayed == 1) {
                g_GameLogic.scoreBook_batter_pitcherStatsDisplayed = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & 8) {
            if (g_GameLogic.scoreBook_scrollIndex != 0) {
                g_GameLogic.scoreBook_scrollIndex--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (input->buttonInput & 4) {
            if (g_GameLogic.scoreBook_scrollIndex < 4) {
                g_GameLogic.scoreBook_scrollIndex++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

// fn_3_59C2C, size:0x314
void fn_3_59C2C(void) {
    SceneTask* task = lbl_803CC1B8;
    switch (unkSimulationRelatedStruct._04) {
    case 0:
        task->_10 = 0;
        fn_800216F8(3, fn_3_91064);
        unkSimulationRelatedStruct._04++;
        break;
    case 1:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 2:
        fn_800216F8(g_d_GameSettings.StadiumID + 0x27, fn_3_90798);
        unkSimulationRelatedStruct._04++;
        break;
    case 3:
        if (task->_10 != 0) {
            task->_10 = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 4:
        lbl_3_data_228._10 = 0;
        fn_800B0A5C_insertQueue(manageLoadingState, 0);
        unkSimulationRelatedStruct._04++;
        break;
    case 5:
        if (lbl_3_data_228._10 == 1) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 6:
        if (fn_80035838(lbl_3_data_3D80, 2) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 7:
        if (fn_80035838(lbl_3_data_3D80 + 0xE0, 0xB) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 8:
        if (fn_80035838(lbl_3_data_3D80 + 0x1D0, 9) != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 9:
        lbl_3_common_bss_34C58._00 = ARAMTransfer(&lbl_3_data_3D70, 0, 0, 0); // TODO type: pointer in u32
        unkSimulationRelatedStruct._04++;
        break;
    case 10:
        if ((s32)lbl_803C6CF8._715 == 1) {
            fn_3_906FC();
            lbl_3_common_bss_34C58._2C = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 11:
        if (fn_3_90928() != 0) {
            lbl_3_common_bss_34C58._2C = 0;
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 12:
        fn_8001CE74();
        fn_3_B42A8();
        fn_8001A3FC(2);
        lbl_8036E548._2D7D = 0;
        fn_80019A60();
        unkSimulationRelatedStruct._04++;
        break;
    case 13:
        if (lbl_8036E548._2D7D != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 14:
        if (fn_3_1665E4() != 0) {
            unkSimulationRelatedStruct._04++;
        }
        break;
    case 15:
        fn_3_106E50();
        unkSimulationRelatedStruct._04++;
        break;
    case 16:
        if ((s32)lbl_803C6CF8._715 == 1) {
            fn_3_106DFC();
            unkSimulationRelatedStruct._04++;
        }
        break;
    default:
        task->func = fn_3_5AE0C;
        break;
    }
}
