#ifndef __GAME_AUTO_00_001658F0_TEXT_H_
#define __GAME_AUTO_00_001658F0_TEXT_H_

#include "mssbTypes.h"

// One roster slot of the star-chance scout-flag tracker (see fn_3_16440C).
typedef struct StarChanceSlot {
    /*0x0*/ u8 achieved; // scoutFlagsAchieved when the chance started
    /*0x1*/ u8 target;   // scout flags needed
    /*0x2*/ u8 bonus;
    /*0x3*/ u8 active;
    /*0x4*/ u8 charID;
} StarChanceSlot; // size: 0x5

// Star chance state (lbl_3_common_bss_37400), only the fields used here.
typedef struct StarChanceState {
    /*0x00*/ u8 _00[9][2];
    /*0x12*/ StarChanceSlot slots[9];
    /*0x3F*/ u8 _3F;
    /*0x40*/ s16 humanPlayer;
    /*0x42*/ s16 _42;
    /*0x44*/ s16 runnerRosterID; // runner the chance is about (types 9-11)
    /*0x46*/ u8 type;            // 0: none, 1..12: which star chance
    /*0x47*/ u8 _47;
    /*0x48*/ u8 state;           // nonzero: a chance is in progress, 2: it ended
    /*0x49*/ u8 _49;
    /*0x4A*/ s8 retry;           // nonzero: use StarChanceOdds.retryChance
} StarChanceState;

// Star-chance odds per type (lbl_80109420), percent by challenge difficulty.
typedef struct StarChanceOdds {
    /*0x0*/ s8 chance[4];
    /*0x4*/ s8 retryChance[4];
    /*0x8*/ s8 _8;
    /*0x9*/ s8 bonus;
    /*0xA*/ u8 _A[3];
    /*0xD*/ s8 _D; // nonzero: a star-chance cutscene exists (fn_3_21F14)
    /*0xE*/ u8 _E;
} StarChanceOdds; // size: 0xF

void fn_3_1658F0(void);
void fn_3_165978(void);
void fn_3_16598C(void);
BOOL fn_3_1659A0(s32 type);
BOOL fn_3_165D24(void);
void fn_3_1663AC(void);

#endif
