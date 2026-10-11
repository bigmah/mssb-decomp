#include "game/auto_00_0006D4A0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// Character roster of the select screen (CharSelectState.roster in main/file_800639BC.h),
// viewed here as a flat array indexed by character id.
extern CharacterStats lbl_8034E9A0[];
extern f32 lbl_3_data_5FC4[];

// .text:0x0006D4A0 size:0xC4 mapped:0x806AC534
void fn_3_6D4A0(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_Controls[i].controlStickAngle = 0;
        g_Controls[i].controlStickMagnitude = 0;
        g_Controls[i].buttonInput = 0;
        g_Controls[i].newButtonInput = 0;
        g_Controls[i]._08 = 0;
        g_Controls[i].right_left = 0;
        g_Controls[i].up_down = 0;
        g_Controls[i].rightTriggerDistance = 0;
        g_Controls[i].leftTriggerDistance = 0;
    }
    fn_800A97D0(0x10, 0x1E);
}

// .text:0x0006D564 size:0xA0 mapped:0x806AC5F8
u16 fn_3_6D564(s32 team, s32 idx, s32 delta) {
    if (g_d_GameSettings.GameModeSelected == 0 || g_d_GameSettings.GameModeSelected == 5) {
        if (delta < 0 && lbl_803535C8[team][idx].stamina < -delta) {
            lbl_803535C8[team][idx].stamina = 0;
        } else {
            lbl_803535C8[team][idx].stamina += delta;
        }
    }
    return lbl_803535C8[team][idx].stamina;
}

// .text:0x0006D604 size:0x54 mapped:0x806AC698
BOOL checkFieldingStat(int team, int idx, E(int, FIELDING_ABILITY) ability) {
    if (g_d_GameSettings.minigamesEnabled) {
        team = 0;
    }
    if (inMemRoster[team][idx].stats.FieldingStats & (1 << ability)) {
        return TRUE;
    }
    return FALSE;
}

// .text:0x0006D658 size:0x7C mapped:0x806AC6EC
// NONMATCHING 90%: the roster index mulli/addi is scheduled around the GameSettings load differently
#if NONMATCHING
s32 fn_3_6D658(s32 team, s32 charId, s32 otherId) {
    s32 chem = ((u8*)&lbl_8034E9A0[charId].chemistry)[otherId];

    if (!g_d_GameSettings.exhibitionMatchInd && g_d_GameSettings.humanTeamNumber == team &&
        (s8)g_d_GameSettings.challengeCaptainStarBought[5] != 0) {
        chem += (s32)lbl_3_data_5FC4[10];
    }
    if (chem > 100) {
        chem = 100;
    }
    return chem;
}
#endif
