#ifndef __GAME_AUTO_00_0015C5F4_TEXT_H_
#define __GAME_AUTO_00_0015C5F4_TEXT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_00097144_text.h" // LayoutSlot lbl_80371C30, GameHudFlags, GamePauseState
#include "game/auto_00_0009C578_text.h" // GameLineScore lbl_80353A90
#include "main/file_80069BDC.h"         // SceneTask lbl_803CC1B8
#include "main/SpaniDesc.h"

// Scorebook / result-banner task (lbl_803CC1B8 while one of this unit's tasks runs).
typedef struct ScoreBookTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x14 - 0x4];
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;   // frames in the current state (saturates at 0xFFFF)
    /*0x1A*/ u16 state;   // fn_3_15DB44 state; frame counter in fn_3_15F088
    /*0x1C*/ u16 team;    // displayed team (xor g_GameLogic._000 gives the team index)
    /*0x1E*/ u16 page;    // 0: batting stats, 1: pitching stats
    /*0x20*/ u16 scroll;  // first batting-order row shown
} ScoreBookTask;

#define SB_TASK ((ScoreBookTask*)lbl_803CC1B8)
#define SB_OBJ(task, i) (lbl_80371C30[(task)->baseIdx + (i)].obj)

// Batting order per team (lbl_80354720).
typedef struct ScoreOrderEntry {
    /*0x0*/ u8 _0;
    /*0x1*/ s8 row; // batting-order position
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
} ScoreOrderEntry;

extern ScoreOrderEntry lbl_80354720[2][9];

// Per-player batting stats (lbl_803537E4[2][9], 0x26 bytes each).
typedef struct BatterRecord {
    /*0x00*/ u8 _00[0x4];
    /*0x04*/ u8 atBats;
    /*0x05*/ u8 hits;
    /*0x06*/ u8 _06[0x9 - 0x6];
    /*0x09*/ u8 _09;
    /*0x0A*/ u8 _0A[0x10 - 0xA];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13[0x23 - 0x13];
    /*0x23*/ u8 _23; // shown on the pitching page
    /*0x24*/ u8 _24;
    /*0x25*/ u8 _25;
} BatterRecord; // size: 0x26

extern BatterRecord lbl_803537E4[2][9];

// Per-player pitching stats (lbl_803535C8[2][9], 0x1E bytes each).
typedef struct PitcherRecord {
    /*0x00*/ u16 _00; // nonzero once the player has pitched
    /*0x02*/ u16 _02;
    /*0x04*/ u16 earnedRuns;
    /*0x06*/ u8 _06[0xA - 0x6];
    /*0x0A*/ u16 _0A;
    /*0x0C*/ u8 _0C[0x1A - 0xC];
    /*0x1A*/ u8 outs;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ u8 _1C;
    /*0x1D*/ u8 _1D;
} PitcherRecord; // size: 0x1E

extern PitcherRecord lbl_803535C8[2][9];

// Sprite descriptor tables handed to fn_80034E20.
extern SpaniDesc lbl_3_data_273E0[2];
extern SpaniDesc lbl_3_data_27420[6];
extern SpaniDesc lbl_3_data_274E0[59];
extern SpaniDesc lbl_3_data_27C54[2];

extern u8 lbl_3_data_F430[][2];    // per captain: logo frames
extern u8 lbl_3_data_27C40[2][6];  // column-header frames per page
extern u8 lbl_3_data_27C4C[8];     // per-row reveal delay (frames)


extern void fn_800362F0(void* owner, s32 idx);
extern void fn_3_91FC4(void);

void fn_3_15C5F4(void);
void fn_3_15C638(void);
void fn_3_15C6E4(ScoreBookTask* task, s32 idx, s32 value, s32 format);
void fn_3_15D1D8(ScoreBookTask* task);
void fn_3_15DB44(void);
void fn_3_15EE2C(void);
void fn_3_15F088(void);
void fn_3_15F220(void);
void fn_3_15F380(void);
void fn_3_15F3C4(void);
void fn_3_15F410(void);

#endif
