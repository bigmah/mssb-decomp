#ifndef __MENUS_AUTO_00_0008E6A4_TEXT_H_
#define __MENUS_AUTO_00_0008E6A4_TEXT_H_

#include "mssbTypes.h"

// Loader task run from the queue (lbl_803CC1B8); only the fields used here.
typedef struct MenuLoadTask {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ struct MenuLoadTask* parent;
    /*0x10*/ s16 _10; // parent: set to 1 when the load finishes
    /*0x12*/ u8 _12[2];
    /*0x14*/ s16 count; // actors transferred so far
    /*0x16*/ s16 kind;  // index into the ARAM file tables
    /*0x18*/ u8 _18[0x28 - 0x18];
    /*0x28*/ s8 step;
} MenuLoadTask;

// One character actor in lbl_8036E548 (stride 0x27C).
typedef struct MenuActor {
    /*0x000*/ u8 _000[8];
    /*0x008*/ s32 aram; // ARAMTransfer handle of the model file
    /*0x00C*/ u8 _00C[0x252 - 0xC];
    /*0x252*/ u8 _252;
    /*0x253*/ u8 _253;
    /*0x254*/ u8 _254;
    /*0x255*/ u8 _255;
    /*0x256*/ u8 _256[0x27C - 0x256];
} MenuActor; // size: 0x27C

// View of lbl_8036E548 as used by the menus loaders (lbl_2_bss_340140 points at it).
typedef struct MenuActorMgr {
    /*0x0000*/ u8 _0000[0xC04];
    /*0x0C04*/ MenuActor actors[13];
    /*0x2C50*/ MenuActor* active[13];
    /*0x2C84*/ u8 _2C84[0x307A - 0x2C84];
    /*0x307A*/ u8 _307A;
} MenuActorMgr;

// Menus REL bss at 0x340234: state of the current menu screen (only the fields used here).
typedef struct MenuScreenState {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ u16 state;
    /*0x12*/ u8 _12[6];
    /*0x18*/ u16 subState;
} MenuScreenState;

void fn_2_8E6A4(void);
void fn_2_8E8A4(void);
void fn_2_8EA80(void);
void fn_2_8ED4C(void);
void fn_2_8EDC4(void);
void fn_2_8EEC8(void);

#endif
