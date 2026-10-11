#ifndef __GAME_AUTO_00_001471C0_TEXT_H_
#define __GAME_AUTO_00_001471C0_TEXT_H_

#include "mssbTypes.h"

// Per-player slot in this minigame's view of g_Minigame._1DBC.
typedef struct {
    /* 0x0 */ s16 timer;
    /* 0x2 */ u8 _2;
    /* 0x3 */ u8 active;
} MG1471Slot;

typedef struct {
    /* 0x00 */ u8 _00[0x10];
    /* 0x10 */ MG1471Slot slot[4]; // g_Minigame + 0x1DCC
} MG1471View;

void fn_3_1471C0(void);
void fn_3_1471C4(void);
void fn_3_147358(void);

#endif
