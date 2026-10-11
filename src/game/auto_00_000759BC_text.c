#include "game/auto_00_000759BC_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1838.h"

extern LineScore lbl_80353A90;
extern BattingRecord lbl_803537E4[2][9];
extern PitchingRecord lbl_803535C8[2][9];
extern PitcherGameStat lbl_3_common_bss_32A38[2][9];
extern s8 lbl_3_common_bss_32888[2][100];
extern ScoresView g_Scores;
extern RunningLogicView g_RunningLogic;
extern FielderView g_Fielders[];
extern Bss37400View lbl_3_common_bss_37400;
extern Bss8034E9A0View lbl_8034E9A0;
extern MvpWeights lbl_3_data_60F8;
extern u8 lbl_80354768[];
extern u8 lbl_800E8558[];
extern void fn_3_161588(int, s16);
extern void fn_3_162D54(void);

// fn_3_76D08 updates its counters in place (no address temp).
#define STAT_INC_U8_FIELD(x) ((x) < 0xFE ? ((x) = (x) + 1) : ((x) = 0xFF))
#define STAT_INC_U16_FIELD(x) ((x) < 0xFFFE ? ((x) = (x) + 1) : ((x) = 0xFFFF))

// .text:0x000759BC size:0x7B8 mapped:0x806B4A50
void fn_3_759BC(void) {
    return;
}

// .text:0x00076174 size:0x3E4 mapped:0x806B5208
void fn_3_76174(void) {
    return;
}

// .text:0x00076558 size:0x544 mapped:0x806B55EC
void fn_3_76558(void) {
    return;
}

// .text:0x00076A9C size:0x1DC mapped:0x806B5B30
void fn_3_76A9C(void) {
    return;
}

// .text:0x00076C78 size:0x90 mapped:0x806B5D0C
// Logs a home run by the current batter.
void fn_3_76C78(void) {
    s32 i;

    for (i = 0; i < 50; i++) {
        if (lbl_80353A90._0A0[i] == -1) {
            if (g_GameLogic.teamBatting == 0) {
                lbl_80353A90._0A0[i] = g_Batter.rosterID;
            } else {
                lbl_80353A90._0A0[i] = (s8)g_Batter.rosterID + 9;
            }
            return;
        }
    }
}

// .text:0x00076D08 size:0xC0C mapped:0x806B5D9C
void fn_3_76D08(s32 batterSlot, s32 result, u8 detail, s32 rbi) {
    return;
}
