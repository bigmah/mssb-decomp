#ifndef __GAME_rep_37A8_H_
#define __GAME_rep_37A8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/UnknownHomes_Game.h"

// This minigame's view of the shared minigame area (g_Minigame; MiniGameStruct describes
// the fields common to all minigames).

// Thrown-ball slots at g_Minigame + 0xA8 (40 of them).
typedef struct MgBall {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec vel;
    /* 0x18 */ f32 _18;
    /* 0x1C */ s32 owner;
    /* 0x20 */ s16 timer;
    /* 0x22 */ s16 _22;
    /* 0x24 */ u8 _24[2];
    /* 0x26 */ u8 used;
    /* 0x27 */ u8 _27;
} MgBall; // size: 0x28

// Runner slots at g_Minigame + 0x0 (3 of them, 0x38 each).
typedef struct MgRunner {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 _C;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ s16 _18;
    /* 0x1A */ s16 _1A;
    /* 0x1C */ s16 _1C;
    /* 0x1E */ s16 _1E;
    /* 0x20 */ s16 throwTimer;
    /* 0x22 */ s16 _22;
    /* 0x24 */ s16 _24;
    /* 0x26 */ s16 queueTimer;
    /* 0x28 */ u8 _28[2];
    /* 0x2A */ u8 st;
    /* 0x2B */ u8 sel;
    /* 0x2C */ u8 who;
    /* 0x2D */ u8 _2D;
    /* 0x2E */ u8 _2E;
    /* 0x2F */ s8 queue[4];
    /* 0x33 */ u8 _33;
    /* 0x34 */ s8 fielder;
    /* 0x35 */ s8 player;
    /* 0x36 */ u8 _36[2];
} MgRunner; // size: 0x38

// CPU state per player at g_Minigame + 0x1DCC (see fn_3_142C18).
typedef struct MgCpu {
    /* 0x0 */ s16 timer;
    /* 0x2 */ s8 state;
    /* 0x3 */ u8 _3;
} MgCpu;

// Fake controller input for the CPU players and their AI state, cleared together (fn_3_142C18).
typedef struct MgCpuArea {
    /* 0x00 */ InputStruct pad[4]; // g_Minigame + 0x1D7C, per port
    /* 0x40 */ u8 _40[0x50 - 0x40];
    /* 0x50 */ MgCpu cpu[4]; // g_Minigame + 0x1DCC, per player
    /* 0x60 */ u8 _60[0x78 - 0x60];
} MgCpuArea; // size: 0x78

typedef struct Mg37A8 {
    /*0x0000*/ MgRunner runner[3];
    /*0x00A8*/ MgBall ball[40];
    /*0x06E8*/ u8 _06E8[0xCD0 - 0x6E8];
    /*0x0CD0*/ Vec objPos[100];
    /*0x1180*/ Vec objVel[100];
    /*0x1630*/ u8 _1630[0x17C0 - 0x1630];
    /*0x17C0*/ u32 frame;
    /*0x17C4*/ u32 timeLeft;
    /*0x17C8*/ s16 objTimer[100];
    /*0x1890*/ s16 score[4];
    /*0x1898*/ s16 lastScore[4];
    /*0x18A0*/ u8 _18A0[0x18BC - 0x18A0];
    /*0x18BC*/ s16 points[4][2];
    /*0x18CC*/ s8 port[4];
    /*0x18D0*/ u8 _18D0[8];
    /*0x18D8*/ u8 isCpu[4];
    /*0x18DC*/ u8 cpuLevel[4];
    /*0x18E0*/ u8 _18E0[8];
    /*0x18E8*/ u8 _18E8[4];
    /*0x18EC*/ u8 _18EC[4];
    /*0x18F0*/ u8 _18F0[4];
    /*0x18F4*/ s8 order[4];
    /*0x18F8*/ s8 fielder[4];
    /*0x18FC*/ s8 _18FC[4];
    /*0x1900*/ s8 _1900[4];
    /*0x1904*/ s8 _1904;
    /*0x1905*/ s8 _1905;
    /*0x1906*/ u8 _1906[2];
    /*0x1908*/ s8 _1908;
    /*0x1909*/ u8 multiPlayerInd;
    /*0x190A*/ u8 _190A;
    /*0x190B*/ u8 turnOverStatus;
    /*0x190C*/ u8 _190C;
    /*0x190D*/ u8 _190D[0x193A - 0x190D];
    /*0x193A*/ u8 objState[100];
    /*0x199E*/ u8 _199E[0x19A8 - 0x199E];
    /*0x19A8*/ u8 _19A8;
    /*0x19A9*/ u8 _19A9[0x1A26 - 0x19A9];
    /*0x1A26*/ s16 _1A26;
    /*0x1A28*/ u8 _1A28[2];
    /*0x1A2A*/ u8 gameMode;
    /*0x1A2B*/ u8 difficulty;
    /*0x1A2C*/ u8 _1A2C[0x1A37 - 0x1A2C];
    /*0x1A37*/ u8 _1A37;
    /*0x1A38*/ u8 _1A38[0x1A3C - 0x1A38];
    /*0x1A3C*/ u8 _1A3C;
    /*0x1A3D*/ u8 _1A3D[0x1B34 - 0x1A3D];
    /*0x1B34*/ s16 throwFrame[4]; // frames into the throw, -1: not throwing
    /*0x1B3C*/ s16 stunTimer[4];
    /*0x1B44*/ s16 jumpTimer[4];
    /*0x1B4C*/ s16 _1B4C;
    /*0x1B4E*/ s16 _1B4E;
    /*0x1B50*/ s16 combo[4];
    /*0x1B58*/ u8 hitLog[4][10];
    /*0x1B80*/ u8 hitLogCount[4];
    /*0x1B84*/ u8 objKind[50]; // 5: bomb
    /*0x1BB6*/ s8 objOwner[50];
    /*0x1BE8*/ s8 objTarget[50]; // runner index, or -1 - player for a bomb
    /*0x1C1A*/ u8 _1C1A[50];
    /*0x1C4C*/ u8 _1C4C[50];
    /*0x1C7E*/ s8 held[4][3]; // queue of held objects per player
    /*0x1C8A*/ u8 thrown[4];
    /*0x1C8E*/ u8 heldObj[4];
    /*0x1C92*/ s8 aim[4];
    /*0x1C96*/ u8 _1C96[4];
    /*0x1C9A*/ u8 stun[4];
    /*0x1C9E*/ u8 targeted[4];
    /*0x1CA2*/ u8 _1CA2;
    /*0x1CA3*/ u8 bossActive;
    /*0x1CA4*/ u8 bossCount;
    /*0x1CA5*/ u8 jump[4];
    /*0x1CA9*/ u8 kindUsed[4];
    /*0x1CAD*/ u8 home[4];
    /*0x1CB1*/ u8 hits[4];
    /*0x1CB5*/ u8 _1CB5[0x1D7C - 0x1CB5];
    /*0x1D7C*/ MgCpuArea cpuIn;
    /*0x1DF4*/ u8 knocked[4];
    /*0x1DF8*/ u8 _1DF8[0x1E2C - 0x1DF8];
} Mg37A8; // size: 0x1E2C

// lbl_3_common_bss_37400, only the fields used here.
typedef struct Rep37A8Bss37400View {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 humanPlayer;
} Rep37A8Bss37400View;

void fn_3_141C44(void);
struct DODisplayObj;
void fn_3_141C8C(struct DODisplayObj* dispObj, s32* stage, s32* coord, s32* map, u8* numTevStages, u8* numTexGens,
                 f32 (*camera)[4]);
void fn_3_141F30(void);
s32 fn_3_142030(s32, s32, s32);
void fn_3_142088(void);
void fn_3_14225C(void);
void fn_3_142284(void);
s32 fn_3_142570(s8 i);
u8 fn_3_1428F0(s8 i, s32 force);
void fn_3_142C18(void);
void fn_3_142CA8(void);
void fn_3_142DB4(s32 idx);
void fn_3_1430D0(s32 hand, s32 p);
void fn_3_143358(s32 i);
void fn_3_143714(void);
s32 fn_3_143770(u8* p);
void fn_3_1439EC(s32 idx);
void fn_3_143FAC(s32);
void fn_3_14402C(s32 idx);
void fn_3_14423C(void);
void fn_3_14443C(void);
void fn_3_14471C(s32 p);
void fn_3_144ADC(s32 p);
void fn_3_144CB8(void);
void fn_3_1453BC(s32 idx);
void fn_3_145AD0(s32 p);
void fn_3_145B98(void);
void fn_3_145EB8(void);
void fn_3_145FF4(void);
void fn_3_1461A4(void);
void fn_3_146408(void);
void fn_3_146928(void);
void fn_3_1469CC(void);
void fn_3_146A90(void);

#endif // !__GAME_rep_37A8_H_
