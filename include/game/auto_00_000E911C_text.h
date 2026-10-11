#ifndef __GAME_AUTO_00_000E911C_TEXT_H_
#define __GAME_AUTO_00_000E911C_TEXT_H_

#include "mssbTypes.h"

// Minigame results-board task (queue item in lbl_803CC1B8 while fn_3_E911C runs).
typedef struct ResultsTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x10];
    /*0x14*/ u16 baseIdx; // first sprite in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 mode;    // set by the creator (fn_3_EDD10)
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 kind;
    /*0x20*/ u16 round;
    /*0x22*/ u16 timer;
    /*0x24*/ u16 score[4];
    /*0x2C*/ u16 bonus[4];
    /*0x34*/ u8 cursor;
    /*0x35*/ u8 spins;
} ResultsTask;

// Entry filled by fn_3_1079C8: a player and its placing.
typedef struct ResultsOrder {
    /*0x0*/ u8 player;
    /*0x1*/ u8 rank;
} ResultsOrder;

void fn_3_E911C(void);

#endif
