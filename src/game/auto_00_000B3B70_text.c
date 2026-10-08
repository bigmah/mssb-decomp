#include "game/auto_00_000B3B70_text.h"
#include "game/UnknownHomes_Game.h"

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
