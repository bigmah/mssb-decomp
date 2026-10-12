#include "game/auto_00_00113398_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// .text:0x00113398 size:0x2C mapped:0x8075242C
void fn_3_113398(void) {
    s8 i;

    i = 0;
    do {
        ((MG1133View*)&g_Minigame)->flag[i] = 0;
        i++;
    } while (i < 4);
}

