#include "game/auto_00_0009143C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1610.h"
#include "game/rep_16B8.h"

extern u8 lbl_3_common_bss_32724[];
void fn_3_EA340(void);

// .text:0x0009143C size:0xE4 mapped:0x806D04D0
void fn_3_9143C(void) {
    if (g_GameLogic.gameStatus == 2 && lbl_3_common_bss_32724[0x97] == 0) {
        lbl_3_common_bss_32724[0x97] = 1;
        if (g_d_GameSettings.GameModeSelected != 6) {
            fn_800B0A5C_insertQueue(fn_3_912B4, 2);
        }
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_800B0A5C_insertQueue(fn_3_EA340, 2);
        }
    }
    if (g_d_GameSettings.GameModeSelected != 2 && lbl_3_common_bss_32724[0x99] != 0) {
        if (lbl_3_common_bss_32724[0x98] == 0) {
            fn_800B0A5C_insertQueue(fn_3_93D5C, 2);
            return;
        }
        lbl_3_common_bss_32724[0x98] = 2;
    }
}
