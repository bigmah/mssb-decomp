#ifndef __GAME_AUTO_00_0001D86C_TEXT_H_
#define __GAME_AUTO_00_0001D86C_TEXT_H_

#include "mssbTypes.h"

// One batting-order slot: [0] = value at the start of the inning, [1] = current value.
typedef struct LineupSlot {
    /*0x0*/ s16 roster[2];   // roster index of the player
    /*0x4*/ s16 position[2]; // fielding position (0 = pitcher)
} LineupSlot; // size: 0x8

// Fielding-change work area (lbl_3_common_bss_34C90, only the fields used here).
typedef struct FieldingChangeWork {
    /*0x000*/ u8 _000[0x14];
    /*0x014*/ LineupSlot lineup[2][10]; // per team, slot 0 is the pitcher
    /*0x0B4*/ u8 _0B4[0x168 - 0xB4];
    /*0x168*/ s16 savedOrder[2][10][2]; // per team: copy of GameControlsStruct.battingOrderAndPositionMapping
    /*0x1B8*/ u8 _1B8[0x202 - 0x1B8];
    /*0x202*/ u8 changed[2]; // per team: the pitcher was replaced
    /*0x204*/ u8 _204[0x20A - 0x204];
    /*0x20A*/ u8 orderByte[2][9]; // per team: lbl_80354720[team][i]._3
    /*0x21C*/ u8 _21C[2];
    /*0x21E*/ u8 _21E[0x264 - 0x21E];
} FieldingChangeWork; // size: 0x264

extern FieldingChangeWork lbl_3_common_bss_34C90;

typedef struct ScoreTeam {
    /*0x00*/ s16 runs;
    /*0x02*/ u8 _02[0x26 - 0x2];
} ScoreTeam; // size: 0x26

// Scoreboard (g_Scores, only the fields used here).
typedef struct ScoreStruct {
    /*0x00*/ u8 _00[4];
    /*0x04*/ ScoreTeam team[2];
    /*0x50*/ u8 _50[0xA6 - 0x50];
    /*0xA6*/ s16 _A6;
    /*0xA8*/ u8 _A8[0xAC - 0xA8];
    /*0xAC*/ u8 inning;
    /*0xAD*/ u8 _AD; // nonzero in the bottom half
    /*0xAE*/ u8 _AE[0xC8 - 0xAE];
} ScoreStruct; // size: 0xC8

extern ScoreStruct g_Scores;

// Base-running state (g_RunningLogic, only the fields used here).
typedef struct RunningLogicStruct {
    /*0x00*/ s16 _00;
    /*0x02*/ s16 runnerBits; // one nibble per base; 0x100 = 2nd, 0x1000 = 3rd
    /*0x04*/ u8 _04[0x20 - 0x4];
} RunningLogicStruct; // size: 0x20

extern RunningLogicStruct g_RunningLogic;

s32 fn_3_1D86C(void);
void fn_3_1DB5C(void);
void fn_3_1DC30(void);
void fn_3_1DD48(void);
void fn_3_1DD68(void);

#endif
