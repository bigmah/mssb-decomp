#ifndef __GAME_AUTO_00_00141A2C_TEXT_H_
#define __GAME_AUTO_00_00141A2C_TEXT_H_

#include "mssbTypes.h"

// Per-player slot in this minigame's area of g_Minigame (0x1DCC + i*8).
typedef struct {
    /* 0x0 */ s16 timer;
    /* 0x2 */ u8 _2[3];
    /* 0x5 */ u8 _5;
    /* 0x6 */ s8 _6; // 0x7F: none
    /* 0x7 */ s8 _7;
} MG141Slot;

// This minigame's view of g_Minigame (overlays the per-minigame area at 0x1DBC).
typedef struct {
    /* 0x0000 */ u8 _0[0x1DCC];
    /* 0x1DCC */ MG141Slot slot[4];
} MG141View;

void fn_3_141A2C(void);
void fn_3_141A30(void);

#endif
