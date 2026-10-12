#ifndef __MENUS_DEBUG_MENU_DATA_H__
#define __MENUS_DEBUG_MENU_DATA_H__

#include "mssbTypes.h"

// Debug-menu strings and tables. They are file-scope statics of a header that many
// menus units include, so each of those units has its own (unreferenced) copy at the
// start of its .data, as in the original (0x2C2 bytes, 18 copies in menus.rel).
// Include this before the unit's own .data definitions.

static char debugBatOrderNames[4][0x20] = {"BAT FIRST", "BAT LAST", "FL", "PC"};
static char debugHandNames[4][4] = {"RR", "RL", "LR", "LL"}; // batting/throwing hand
static char debugOnOffNames[2][0x20] = {"OFF", "ON"};
static char debugMenuNames[5][0x20] = {
    "SELECT DEBUG MENU", "HIDE CHARA SET", "STAR PLAYER SET", "KOOPA STA FLAG SET", "CHALLE LEVEL FREE SET",
};
static char debugPlayerNames[8][0x20] = {
    "1P >", "COM1>", "2P >", "COM2>", "3P >", "COM3>", "4P >", "COM4>",
};
static u32 debugColors[8] = {0xFF0F, 0x880F, 0x0FFF, 0x088F, 0xF0FF, 0x808F, 0xF00F, 0x800F}; // RGBA4
static u16 debugOrder[12] = {0, 4, 10, 6, 2, 9, 1, 5, 11, 17, 3, 19};
static u8 debugPermutations[2][13] = {
    {0, 2, 6, 8, 4, 10, 1, 3, 7, 5, 9, 11, 0},
    {0, 6, 2, 8, 4, 10, 5, 11, 3, 9, 1, 7, 0},
};

#endif
