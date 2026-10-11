#ifndef __GAME_AUTO_00_0013C790_TEXT_H_
#define __GAME_AUTO_00_0013C790_TEXT_H_

#include "mssbTypes.h"

// This minigame's view of g_Minigame (overlays the per-minigame area at 0x1DBC).
typedef struct {
    /* 0x0000 */ u8 _0[0x1DC0];
    /* 0x1DC0 */ u8 flag[4]; // per player (g_Minigame + 0x1DC0)
} MG13C7View;

void fn_3_13C790(void);

#endif
