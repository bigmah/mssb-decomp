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
