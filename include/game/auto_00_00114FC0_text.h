#ifndef __AUTO_00_00114FC0_TEXT_GAME_H__
#define __AUTO_00_00114FC0_TEXT_GAME_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Wall Ball minigame: the parts of g_Minigame (MiniGameStruct) used by this unit.
// This file declares g_Minigame as bytes, so it reaches the fields through this view.
typedef struct WallBallBumper {
    /*0x00*/ u8 _00;
    /*0x01*/ u8 _01;
    /*0x02*/ u8 id;
    /*0x03*/ u8 _03[0x2C - 0x3];
} WallBallBumper; // size: 0x2C

typedef struct WallBallView {
    /*0x0000*/ u8 _0000[0x754];
    /*0x0754*/ WallBallBumper bumper[7];
    /*0x0888*/ u8 _0888[0xCD0 - 0x888];
    /*0x0CD0*/ Vec coinPos[100];
    /*0x1180*/ Vec coinVel[100];
    /*0x1630*/ u8 _1630[0x17C0 - 0x1630];
    /*0x17C0*/ s32 _17C0;
    /*0x17C4*/ u8 _17C4[4];
    /*0x17C8*/ s16 coinFrames[100];
    /*0x1890*/ s16 currentPoints[4];
    /*0x1898*/ s16 latestPoints[4];
    /*0x18A0*/ u8 _18A0[0x18BC - 0x18A0];
    /*0x18BC*/ s16 pointsPair[4][2];
    /*0x18CC*/ s8 characterIndex[4];
    /*0x18D0*/ u8 _18D0[0x18DC - 0x18D0];
    /*0x18DC*/ u8 aIStrength[4];
    /*0x18E0*/ u8 turnOrder[4]; // player index per turn
    /*0x18E4*/ u8 _18E4[0x18F0 - 0x18E4];
    /*0x18F0*/ u8 _18F0[4];
    /*0x18F4*/ s8 slotPlayer[4]; // player per fielder slot
    /*0x18F8*/ s8 playerSlot[4]; // fielder index per player
    /*0x18FC*/ s8 _18FC[4];
    /*0x1900*/ s8 _1900[4];
    /*0x1904*/ s8 currentPlayer;
    /*0x1905*/ s8 rosterID;
    /*0x1906*/ u8 numParticipants;
    /*0x1907*/ u8 _1907;
    /*0x1908*/ s8 _1908;
    /*0x1909*/ u8 multiPlayerInd;
    /*0x190A*/ u8 _190A;
    /*0x190B*/ u8 turnOverStatus;
    /*0x190C*/ u8 turnNumberWithinRound;
    /*0x190D*/ u8 _190D[0x193A - 0x190D];
    /*0x193A*/ u8 coinVisible[100];
    /*0x199E*/ u8 _199E[0x1A26 - 0x199E];
    /*0x1A26*/ s16 pointsReqToWin;
    /*0x1A28*/ u8 _1A28[2];
    /*0x1A2A*/ u8 gameMode;
    /*0x1A2B*/ u8 difficulty;
    /*0x1A2C*/ u8 _1A2C;
    /*0x1A2D*/ u8 turnCounter;
    /*0x1A2E*/ u8 _1A2E[0x1A37 - 0x1A2E];
    /*0x1A37*/ u8 _1A37;
    /*0x1A38*/ u8 _1A38[0x1A3C - 0x1A38];
    /*0x1A3C*/ u8 _1A3C;
    /*0x1A3D*/ u8 _1A3D[0x1A48 - 0x1A3D];
    /*0x1A48*/ f32 pitcherX;
    /*0x1A4C*/ f32 pitcherZ;
    /*0x1A50*/ u8 _1A50[0x1A70 - 0x1A50];
    /*0x1A70*/ s16 _1A70;
    /*0x1A72*/ s16 frames; // frames since the pitch, saturates at 0x7FFF
    /*0x1A74*/ s16 _1A74;
    /*0x1A76*/ s16 _1A76;
    /*0x1A78*/ s16 _1A78;
    /*0x1A7A*/ s16 bonus;
    /*0x1A7C*/ u8 _1A7C[2];
    /*0x1A7E*/ u8 _1A7E;
    /*0x1A7F*/ u8 phase;
    /*0x1A80*/ u8 _1A80;
    /*0x1A81*/ u8 counting;
    /*0x1A82*/ u8 bumperOrder[7];
    /*0x1A89*/ u8 _1A89;
    /*0x1A8A*/ u8 _1A8A;
    /*0x1A8B*/ s8 _1A8B;
    /*0x1A8C*/ u8 _1A8C;
} WallBallView;

// The parts of g_Scores used here.
typedef struct WallBallScoresView {
    /*0x00*/ s32 round;
    /*0x04*/ u8 _04[0xAA - 0x4];
    /*0xAA*/ u8 lastRound;
} WallBallScoresView;

// The parts of g_Pitcher used here.
typedef struct WallBallPitcherView {
    /*0x000*/ u8 _000[0x6C];
    /*0x06C*/ f32 x;
    /*0x070*/ f32 z;
    /*0x074*/ u8 _074[0x120 - 0x74];
    /*0x120*/ s16 currentStateFrameCounter;
    /*0x122*/ u8 _122[0x13E - 0x122];
    /*0x13E*/ u8 pitcherActionState;
} WallBallPitcherView;

// One g_Fielders entry (size 0x268), only the fields used here.
typedef struct WallBallFielderView {
    /*0x000*/ u8 _000[0x20D];
    /*0x20D*/ s8 rosterID;
    /*0x20E*/ u8 _20E[0x268 - 0x20E];
} WallBallFielderView;

// Ball physics constants (lbl_3_data_21634).
typedef struct WallBallCoinPhysics {
    /*0x00*/ f32 _00[2];
    /*0x08*/ f32 gravity;
    /*0x0C*/ f32 bounce;
    /*0x10*/ f32 friction;
} WallBallCoinPhysics;

void fn_3_114FC0(void);
void fn_3_11502C(void);
void fn_3_115108(void);
void fn_3_115540(void);
void fn_3_115738(void);
void fn_3_115828(void);
void fn_3_1158B0(void);
void fn_3_1158F8(void);
void fn_3_115978(void);
void fn_3_115AB4(void);
void fn_3_115B5C(void);
void fn_3_115BDC(void);
void fn_3_115C24(void);
void fn_3_1160B8(void);
void fn_3_1160BC(void);
void fn_3_11669C(void);
void fn_3_1166CC(void);
void fn_3_11678C(void);

#endif
