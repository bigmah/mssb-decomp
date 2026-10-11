#include "game/auto_00_0006C854_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"

extern u8 lbl_3_data_60E4[6][2]; // rumble (duration, mode) per kind

// .text:0x0006C854 size:0xE4 mapped:0x806AB8E8
void fn_3_6C854(int team, int kind) {
    s32 i;

    if (lbl_80366158._1F != 0 && g_Stats.replayInd == 0) {
        if (g_d_GameSettings.minigamesEnabled) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[i] == team) {
                    if (g_Minigame.minigameControlStruct[0]
                            .battingHandedness[g_Minigame.minigameControlStruct[0].characterIndex[i]] != 0) {
                        return;
                    }
                    break;
                }
            }
        } else {
            team = g_GameLogic.teams[team];
        }
        fn_800A97EC(team, lbl_3_data_60E4[kind][0], lbl_3_data_60E4[kind][1]);
    }
}

// .text:0x0006C938 size:0x2F8 mapped:0x806AB9CC
void fn_3_6C938(void) {
    return;
}

// .text:0x0006CC30 size:0x158 mapped:0x806ABCC4
s32 fn_3_6CC30(s32 port, s32 kind, s32 mask) {
    s32 i;

    if (g_d_GameSettings.minigamesEnabled) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 &&
                g_Minigame.minigameControlStruct[0].characterIndex[i] == port) {
                goto check;
            }
        }
        return 0;
    } else {
        if (g_d_GameSettings._10 == 0 && port == 1) {
            return 0;
        }
        if (g_d_GameSettings._10 == 3 && port == 0) {
            return 0;
        }
    }
check:
    if (kind == 0) {
        if (mask & g_Controls[port].buttonInput) {
            return 1;
        }
    } else if (kind == 1) {
        if (mask & g_Controls[port].newButtonInput) {
            return 1;
        }
    } else {
        if (mask & g_Controls[port]._08) {
            return 1;
        }
    }
    return 0;
}
