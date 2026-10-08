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

#pragma dont_inline on

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
