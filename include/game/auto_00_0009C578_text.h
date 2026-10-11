#ifndef __GAME_AUTO_00_0009C578_TEXT_H_
#define __GAME_AUTO_00_0009C578_TEXT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// lbl_80353A90 (main.dol .bss, 0x108 bytes): per-game line score / awards; only the fields used here.
typedef struct GameLineScore {
    /*0x00*/ u8 _00[0xF8];
    /*0xF8*/ s8 _F8; // pitcher when the lead was taken
    /*0xF9*/ s8 _F9; // runner that scored the winning run
    /*0xFA*/ s8 _FA; // batter on the winning play
    /*0xFB*/ s8 _FB;
    /*0xFC*/ s8 _FC; // team batting (or -1)
    /*0xFD*/ s8 _FD; // batter (or -1)
    /*0xFE*/ s8 _FE;
    /*0xFF*/ s8 _FF;
    /*0x100*/ s8 _100;
    /*0x101*/ u8 _101[0x108 - 0x101];
} GameLineScore; // size: 0x108

extern GameLineScore lbl_80353A90;

void fn_3_9C578(void);
void fn_3_9C794(void);

#endif
