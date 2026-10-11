#include "game/auto_00_000DEB90_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0005985C_text.h"
#include "game/rep_1838.h"
#include <stdlib.h>

extern f32 lbl_3_data_18D98[];
extern u8 lbl_3_data_18944[]; // per minigame: number of participants - 1
extern u8 lbl_3_data_18980[]; // AI strength of each CPU player

// .text:0x000DEB90 size:0x47C mapped:0x8071DC24
void fn_3_DEB90(void) {
    return;
}

// .text:0x000DF00C size:0x250 mapped:0x8071E0A0
void fn_3_DF00C(void) {
    return;
}

// .text:0x000DF25C size:0x17C mapped:0x8071E2F0
void fn_3_DF25C(void) {
    return;
}

// .text:0x000DF3D8 size:0x230 mapped:0x8071E46C
void fn_3_DF3D8(void) {
    return;
}

// NONMATCHING 96%: only scheduling, the lbz of g_d_GameSettings._35 is hoisted above `li r0,0` / the DATA lis
// .text:0x000DF608 size:0xCC mapped:0x8071E69C
#if NONMATCHING
void fn_3_DF608(void) {
    u8* aiStrength = lbl_3_data_18980;
    s32 i;

    g_Minigame._19DA[g_d_GameSettings._35] = 0;
    for (i = 0; i < 4; i++) {
        if (g_d_GameSettings._35 != i) {
            g_Minigame.minigameControlStruct[0].aIStrength[i] = *aiStrength++;
        }
    }
    g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
    g_Minigame._1907 = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Scores.minigameRelated = 1;
}
#endif

// NONMATCHING 95%: inlines fn_3_DF608 (same scheduling issue); the tail g_d_GameSettings._35 load is also hoisted
// .text:0x000DF6D4 size:0x14C mapped:0x8071E768
void fn_3_DF6D4(void) {
    return;
}

// .text:0x000DF820 size:0xB4 mapped:0x8071E8B4
void fn_3_DF820(void) {
    s32 i;

    fn_3_10C81C();
    for (i = 0; i < 4; i++) {
        if (g_Minigame._19E8[i]._0 != g_Minigame._19E8[i]._2) {
            break;
        }
    }
    if (i >= 4) {
        fn_3_5A6D4(0x1D);
    }
}

// .text:0x000DF8D4 size:0x14C mapped:0x8071E968
void fn_3_DF8D4(void) {
    return;
}

// .text:0x000DFA20 size:0x18C mapped:0x8071EAB4
void fn_3_DFA20(void) {
    return;
}

// .text:0x000DFBAC size:0xABC mapped:0x8071EC40
void fn_3_DFBAC(void) {
    return;
}

// .text:0x000E0668 size:0xF0 mapped:0x8071F6FC
void fn_3_E0668(void) {
    return;
}

// .text:0x000E0758 size:0x84 mapped:0x8071F7EC
void fn_3_E0758(void) {
    MinigameCoinSprite* coin;
    s32 i;

    for (i = 0; i < 30; i++) {
        coin = &lbl_8036E548.trail2[i];
        fn_8001D0D0(i, lbl_3_data_18D98[0]);
        coin->angle = shortAngleToRad_Capped(rand() % 4096);
    }
}

// .text:0x000E07DC size:0xA04 mapped:0x8071F870
void fn_3_E07DC(void) {
    return;
}
