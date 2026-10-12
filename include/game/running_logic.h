#ifndef __GAME_RUNNING_LOGIC_H__
#define __GAME_RUNNING_LOGIC_H__

#include "mssbTypes.h"

// g_RunningLogic (0x20 bytes).
typedef struct GameRunningLogic {
    /*0x00*/ s16 _00; // play-event flags (0x10, 0x1000, ...)
    /*0x02*/ s16 occupiedBases; // one nibble per base (0x1, 0x10, 0x100, 0x1000)
    /*0x04*/ s16 _04;
    /*0x06*/ u8 _06[0xE - 0x6];
    /*0x0E*/ s16 _0E;
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 _15; // runners on base
    /*0x16*/ u8 _16[0x20 - 0x16];
} GameRunningLogic; // size: 0x20

extern GameRunningLogic g_RunningLogic;

#endif
