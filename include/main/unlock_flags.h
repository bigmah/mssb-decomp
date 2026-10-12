#ifndef __MAIN_UNLOCK_FLAGS_H__
#define __MAIN_UNLOCK_FLAGS_H__

#include "mssbTypes.h"

// Save-data flags block (lbl_80361B20, main.dol).
typedef struct UnlockFlags {
    /*0x00*/ u8 unlocked[0x36];
    /*0x36*/ u8 _36[0xE4 - 0x36];
    /*0xE4*/ u8 flagsE4[4];
    /*0xE8*/ u8 _E8[0xF4 - 0xE8];
    /*0xF4*/ u8 _F4; // row of lbl_800FE930; toggled by fn_2_5979C
    /*0xF5*/ u8 _F5;
    /*0xF6*/ u8 saveSlot; // selected challenge save slot
    /*0xF7*/ u8 _F7;
} UnlockFlags; // size: 0xF8

#endif
