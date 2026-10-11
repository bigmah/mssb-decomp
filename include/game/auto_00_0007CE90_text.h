#ifndef __GAME_AUTO_00_0007CE90_TEXT_H_
#define __GAME_AUTO_00_0007CE90_TEXT_H_

#include "mssbTypes.h"

// g_Scores (size 0xC8), only the fields used here.
typedef struct ScoresTeam {
    /*0x00*/ s16 runs;
    /*0x02*/ u8 _02[0x24];
} ScoresTeam; // size: 0x26

typedef struct ScoresView {
    /*0x00*/ u8 _00[4];
    /*0x04*/ ScoresTeam team[2];
    /*0x50*/ u8 _50[0x50];
    /*0xA0*/ s16 _A0;
    /*0xA2*/ u8 _A2[0x20];
    /*0xC2*/ u8 _C2;
    /*0xC3*/ u8 _C3[5];
} ScoresView; // size: 0xC8

// g_RunningLogic (size 0x20), only the fields used here.
typedef struct RunningLogicView {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13[0x20 - 0x13];
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
