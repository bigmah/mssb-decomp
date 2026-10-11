#include "game/auto_00_0001E154_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0001D86C_text.h"
#include "game/auto_00_00020A60_text.h"
#include "game/rep_940.h"
#include "game/rep_1838.h"

// Batting order per team (see OrderEntry in main/file_8004207C.h).
typedef struct BattingOrderEntry {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1;
    /*0x2*/ s8 slot;
    /*0x3*/ u8 _3;
} BattingOrderEntry;
extern BattingOrderEntry lbl_80354720[2][9];

extern u8 lbl_3_data_1C10[8][4]; // bunt chance (%) by batter class and AI level

// .text:0x0001E154 size:0x24 mapped:0x8065D1E8
void fn_3_1E154(void) {
    fn_3_219A0();
    fn_3_20A60();
}

// .text:0x0001E178 size:0x1B0 mapped:0x8065D20C
void fn_3_1E178(void) {
    s32 i;
    s32 t;

    fn_3_20AB0();
    for (i = 0; i < 10; i++) {
        lbl_3_common_bss_34C90.savedOrder[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0] =
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][0];
        lbl_3_common_bss_34C90.savedOrder[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][1] =
            g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][i][1];
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            lbl_3_common_bss_34C90.orderByte[t][i] = lbl_80354720[t][i]._3;
        }
    }
}

// .text:0x0001E328 size:0xC4 mapped:0x8065D3BC
void fn_3_1E328(void) {
    g_AiLogic._46 = (s32)(g_GameLogic.AIDifficulty0Special3Weak[0] * 0xFF) / 4;
    g_AiLogic._47 = (s32)(g_GameLogic.AIDifficulty0Special3Weak[1] * 0xFF) / 4;
    fn_3_20AE0();
    lbl_3_common_bss_34C90.changed[0] = 0;
    lbl_3_common_bss_34C90.changed[1] = 0;
    lbl_3_common_bss_34C90._21C[0] = 0;
    lbl_3_common_bss_34C90._21C[1] = 0;
    if (g_GameLogic._13E[g_GameLogic.homeTeamInd] != 0) {
        g_GameLogic.runnerAIInd[0] = 1;
    }
    if (g_GameLogic._13E[g_GameLogic.homeTeamInd ^ 1] != 0) {
        g_GameLogic.runnerAIInd[1] = 1;
    }
    g_AiLogic.aIPitchDesiredEndingLocIndex = 0xFF;
}

// .text:0x0001E3EC size:0xCC mapped:0x8065D480
void fn_3_1E3EC(void) {
    g_AiLogic.batterAIBuntPossibility = 0;
    g_AiLogic.batterAIBuntInd = 0;
    if (g_Scores._A6 <= 2 && g_Scores.inning >= 2 && g_Strikes.outs <= 1 &&
        (g_RunningLogic.runnerBits == 0x11 || g_RunningLogic.runnerBits == 0x111) &&
        RandomInt_Game(100) < lbl_3_data_1C10[g_Batter.characterClass][g_AiLogic.aIBatterDifficulty]) {
        g_AiLogic.batterAIBuntInd = 1;
    }
}
