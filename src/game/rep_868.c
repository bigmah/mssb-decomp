#include "game/rep_868.h"
#define REP_HEADER_FN repHeader_868
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_0009CD90_text.h"
#include "game/rep_8C8.h"
#include "game/rep_940.h"
#include "game/rep_1838.h"
#include "static/GameSettings.h"

extern u8 lbl_3_data_1C30[]; // per fielder: chance (0-100) to set g_FieldingLogic._077[i]._1

// .text:0x0001DEB8 size:0x29C mapped:0x8065CF4C
// NONMATCHING 99%: one insn: `if (bases & 0x1000) runners = 1` is `mr r4,r6` (reusing the _48 = 1 constant) in the original, `li r4,1` here
#if NONMATCHING
void fn_3_1DEB8(void) {
    int runners = 0;
    int i;

    g_AiLogic.aIDifficultyMultiplierArray[0] = g_AiLogic._46 / 255.0f;
    g_AiLogic.aIDifficultyMultiplierArray[1] = g_AiLogic._47 / 255.0f;
    g_AiLogic._48 = 1;
    if (g_RunningLogic.occupiedBases & 0x1000) {
        runners = 1;
    }
    if (g_RunningLogic.occupiedBases & 0x100) {
        runners++;
    }
    if (g_Scores._AC >= 4 && g_Scores._AD != 0 && runners != 0 &&
        g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] + runners >
            g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
        g_AiLogic._48 = 4;
    } else {
        if (g_Scores._AC >= 3 && runners != 0) {
            s16 a = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0];
            s16 b = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
            if (a < b && a + runners >= b) {
                g_AiLogic._48 = 3;
                goto done;
            } else if (a == b) {
                g_AiLogic._48 = 2;
                goto done;
            }
        }
        if (g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] + 5 <
            g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
            g_AiLogic._48 = 0;
        }
    }
done:
    fn_3_21768();
    fn_3_20224();
    if (g_d_GameSettings.minigamesEnabled) {
        for (i = 0; i < 4; i++) {
            g_FieldingLogic._077[i]._1 = 0;
            g_FieldingLogic._077[i]._0 = 0;
            if (RandomInt_Game(100) < lbl_3_data_1C30[g_Fielders[g_Minigame.minigameFielderIndex[i]].aiLevel]) {
                g_FieldingLogic._077[i]._1 = 1;
            }
        }
    } else {
        g_FieldingLogic._077[0]._1 = 0;
        g_FieldingLogic._077[0]._0 = 0;
        if (RandomInt_Game(100) < lbl_3_data_1C30[g_Fielders[0].aiLevel]) {
            g_FieldingLogic._077[0]._1 = 1;
        }
    }
}
#endif
