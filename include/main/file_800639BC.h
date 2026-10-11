#ifndef __MAIN_FILE_800639BC_H__
#define __MAIN_FILE_800639BC_H__

#include "mssbTypes.h"

// Character-select / team-setup state at 0x8034E9A0 (size 0x4C28).
// Only the fields used so far are named.
typedef struct CharSelectState {
    /*0x0000*/ u8 _0000[0x46E0];
    /*0x46E0*/ s32 captain[2]; // captain character id per team
    /*0x46E8*/ u8 _46E8[0x46F8 - 0x46E8];
    /*0x46F8*/ u8 ports[2];
    /*0x46FA*/ u8 _46FA[0x4709 - 0x46FA];
    /*0x4709*/ s8 captainSlot[2]; // roster slot of the captain per team
    /*0x470B*/ u8 _470B[0x48AE - 0x470B];
    /*0x48AE*/ u8 _48AE;
    /*0x48AF*/ u8 _48AF[0x4C28 - 0x48AF];
} CharSelectState; // size: 0x4C28

extern CharSelectState lbl_8034E9A0;

void fn_80069A68(void);
void fn_80069A98(void);
void fn_80069AD4(void);
void fn_80069B08(void);
BOOL fn_80069B68(void);
s32 translateStarPitchHitIndex(u8 pitch);
u8 translateStarPitch(u8 star);
u8 translateStarSwing(u8 star);
u8 fn_80064918(s16 charId);
void fn_8006496C(void);

#endif
