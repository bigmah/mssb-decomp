#include "game/auto_00_0013C790_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0013C790 size:0x2C mapped:0x8077B824
void fn_3_13C790(void) {
    s8 i;

    i = 0;
    do {
        ((MG13C7View*)&g_Minigame)->flag[i] = 0;
        i++;
    } while (i < 4);
}

