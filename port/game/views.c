// Accessors for fields of global structs that some units can't reach through
// the real struct (their headers clash) and whose GameCube-offset views are
// wrong on PC.
#include "main/file_80021308.h" // SoundManager

extern SoundManager lbl_800EF808;

// SoundManager.unk39A[0]: roster slot whose sound bank is being loaded
// (game/auto_00_0005985C_text.c).
u8* port_sound_load_index(void) {
    return &lbl_800EF808.unk39A[0];
}

// MSSB_TRACE_GAME=1: print the game-flow state when it changes.
#include "game/UnknownHomes_Game.h"
#include <stdlib.h>
#include "static/GameSettings.h"
extern GameScores g_Scores;
void port_trace_game(void) {
    static int enabled = -1;
    static int last[7] = {-1, -1, -1, -1, -1, -1, -1};
    int now[7];
    if (enabled < 0) {
        enabled = getenv("MSSB_TRACE_GAME") != NULL;
    }
    if (!enabled) {
        return;
    }
    now[0] = g_GameLogic.gameStatus;
    now[1] = g_GameLogic._125;
    now[2] = g_Pitcher.pitcherActionState;
    now[3] = g_d_GameSettings._06;
    now[4] = g_Scores.inning;
    now[5] = g_GameLogic.teamBatting;
    now[6] = g_Strikes.outs;
    if (memcmp(now, last, sizeof(now)) != 0) {
        memcpy(last, now, sizeof(now));
        fprintf(stderr, "[game] status %d load %d pitcher %d mode %d pitchframe %d | inning %d batting %d outs %d balls %d strikes %d runs %d-%d\n",
                now[0], now[1], now[2], now[3], g_GameLogic.FrameCountOfCurrentPitch, now[4], now[5], now[6], g_Strikes.balls,
                g_Strikes.strikes, g_Scores.team[0].runs[0], g_Scores.team[1].runs[0]);
    }
}
