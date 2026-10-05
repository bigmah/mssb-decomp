#include "game/rep_1B70.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"

#define GL(off) (((u8 *)&g_GameLogic)[off])

// .text:0x000B3A4C size:0x124 mapped:0x806F2AE0
void fn_3_B3A4C(void) {
    GL(0x12D) = 1;
    g_Practice.instructionNumber = -1;
    g_Practice._1C7 = 0;
    g_Practice.guidedPracticeCompletionRelated = 0;
    g_Practice.guidedPracticeCounter = 0;
    g_Practice._186 = 0;
    g_Practice.frames_sinceMovedToFromMenu = 0;
    g_Practice.practiceState = 0;
    g_Practice.tutorialState = 3;
    g_Practice.framesSincePracticeMenuDefaultTransition = 0;
    GL(0x13E) = 0;
    GL(0x140) = 0;
    GL(0x146) = 0;
    GL(0x142) = 0;
    GL(0x144) = 0;
    GL(0x148) = 0;
    GL(0x13F) = 0;
    GL(0x141) = 0;
    GL(0x147) = 0;
    GL(0x143) = 0;
    GL(0x145) = 0;
    GL(0x149) = 0;
    switch (g_Practice.practiceType_2) {
    case 3:
        break;
    case 1:
        g_Practice.aIEnabled = 1;
        GL(0x141) = 1;
        GL(0x140) = 1;
        break;
    case 2:
        g_Practice.aIEnabled = 1;
        g_Practice.practiceBatterHandedness = 1;
        GL(0x141) = 1;
        GL(0x140) = 1;
        GL(0x147) = 1;
        GL(0x146) = 1;
        GL(0x149) = 1;
        GL(0x148) = 1;
        break;
    case 4:
        if (g_Practice.practiceLevel == 4) {
            g_Practice.aIEnabled = 1;
            g_Practice.practiceBatterHandedness = 0;
            g_Practice.aIEnabled = 1;
            GL(0x141) = 1;
            GL(0x140) = 1;
        } else if (g_Practice.practiceLevel == 5) {
            g_Practice.aIEnabled = 0;
            g_Practice.practiceBatterHandedness = 1;
        }
        break;
    }
    g_Pitcher.pitcher.x = 0.0f;
}
