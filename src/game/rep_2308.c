#include "game/rep_2308.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1F58.h"
#include "static/UnknownHomes_Static.h"

// .text:0x000CABF0 size:0x210 mapped:0x80709C84
void fn_3_CABF0(void) {
    return;
}

// .text:0x000CAE00 size:0x19C mapped:0x80709E94
void fn_3_CAE00(void) {
    return;
}

// .text:0x000CAF9C size:0x214 mapped:0x8070A030
void fn_3_CAF9C(void) {
    return;
}

// .text:0x000CB1B0 size:0x84 mapped:0x8070A244
void fn_3_CB1B0(void) {
    return;
}

// .text:0x000CB234 size:0x50 mapped:0x8070A2C8
void fn_3_CB234(int a, int b) {
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        ((void (*)(int, int))fn_3_C11CC)(a, b);
    }
}

// .text:0x000CB284 size:0xC0 mapped:0x8070A318
void fn_3_CB284(void) {
    return;
}

