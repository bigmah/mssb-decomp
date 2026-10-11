#ifndef __GAME_AUTO_00_0007CE90_TEXT_H_
#define __GAME_AUTO_00_0007CE90_TEXT_H_

#include "mssbTypes.h"

// g_Scores (size 0xC8), only the fields used here. Per-team bytes are indexed by team.
typedef struct ScoresView {
    /*0x00*/ s32 inning;
    /*0x04*/ s16 runs[2][19]; // [team][0] total, [team][n] inning n
    /*0x50*/ s16 hits[2][19];
    /*0x9C*/ s16 _9C;
    /*0x9E*/ s16 _9E;
    /*0xA0*/ s16 _A0;
    /*0xA2*/ s16 _A2;
    /*0xA4*/ s16 result; // 0/1: that team won, 2: tie
    /*0xA6*/ u8 _A6[2];
    /*0xA8*/ u8 _A8[2]; // errors per team
    /*0xAA*/ u8 _AA;
    /*0xAB*/ u8 _AB[4];
    /*0xAF*/ s8 _AF[2]; // pitcher slots
    /*0xB1*/ s8 _B1[2];
    /*0xB3*/ s8 _B3[2];
    /*0xB5*/ s8 _B5[2];
    /*0xB7*/ s8 _B7[2];
    /*0xB9*/ u8 _B9[2];
    /*0xBB*/ u8 _BB[2];
    /*0xBD*/ u8 _BD[5];
    /*0xC2*/ u8 _C2;
    /*0xC3*/ u8 _C3[5];
} ScoresView; // size: 0xC8

// g_RunningLogic (size 0x20), only the fields used here.
typedef struct RunningLogicView {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14;
    /*0x15*/ u8 _15; // runners on base
    /*0x16*/ u8 _16[0x20 - 0x16];
} RunningLogicView; // size: 0x20

// lbl_8036E548 (character actor manager), only the fields used here.
typedef struct ReplayActorView {
    /*0x00*/ u8 _00[0x68];
    /*0x68*/ s16 _68;
} ReplayActorView;

typedef struct ReplayActorMgrView {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ ReplayActorView* active[13];
} ReplayActorMgrView;

// lbl_8037169C (scene fade, SceneFade in main/file_8001FE00.h), only the fields used here.
typedef struct ReplayFadeView {
    /*0x00*/ u8 _00[0x13];
    /*0x13*/ u8 done;
} ReplayFadeView;

void fn_3_7CE90(void);
void fn_3_7CF88(void);
void fn_3_7D2E0(void);
void fn_3_7D39C(void);
void fn_3_7D458(void);
void fn_3_7D780(void);

#endif
