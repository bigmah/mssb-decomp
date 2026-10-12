#ifndef __GAME_rep_3290_H_
#define __GAME_rep_3290_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/UnknownHomes_Game.h" // VecXZ


// Target-board entity at g_Minigame + 0x72C + i * 0x2C (7 of them).
typedef struct {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec home;
    /*0x18*/ Vec vel; // vel.x: swing angle, vel.y: swing speed, vel.z: damping
    /*0x24*/ s16 width;
    /*0x26*/ s16 timer;
    /*0x28*/ u8 state;
    /*0x29*/ u8 type;
    /*0x2A*/ u8 slot;
    /*0x2B*/ u8 pad2b;
} MgEnt_3290; // size: 0x2C

// Fake controller input for a CPU port (g_Minigame + 0x1D7C, 16 bytes per port).
typedef struct {
    /*0x0*/ s16 stickAngle;
    /*0x2*/ s16 stickMagnitude;
    /*0x4*/ u16 held;
    /*0x6*/ u16 trig;
    /*0x8*/ u8 _8[8];
} MgPad_3290;

// CPU input and AI state, cleared together (fn_3_11391C).
typedef struct {
    /*0x00*/ MgPad_3290 pad[4];
    /*0x40*/ u8 _40[0x48 - 0x40];
    /*0x48*/ u8 active[4]; // per port: driven by the CPU this frame
    /*0x4C*/ u8 _4C[4];
    /*0x50*/ s16 target;   // pitch power the CPU aims for
    /*0x52*/ u8 plan;      // 0: aim at the note block, 1: none, 2: in range, 3: Bowser wall
    /*0x53*/ s8 state;
    /*0x54*/ s8 timer;
    /*0x55*/ u8 _55[0x78 - 0x55];
} MgCpu_3290; // size: 0x78

// Wall Ball: this unit's view of g_Minigame (see also WallBallView, MiniGameStruct).
typedef struct {
    /*0x0000*/ u8 _0000[0x72C];
    /*0x072C*/ MgEnt_3290 wall[7];
    /*0x0860*/ u8 _0860[0xCD0 - 0x860];
    /*0x0CD0*/ Vec coinPos[100];
    /*0x1180*/ Vec coinVel[100];
    /*0x1630*/ u8 _1630[0x17C8 - 0x1630];
    /*0x17C8*/ s16 coinFrames[100];
    /*0x1890*/ s16 currentPoints[4];
    /*0x1898*/ s16 latestPoints[4];
    /*0x18A0*/ u8 _18A0[0x18CC - 0x18A0];
    /*0x18CC*/ s8 port[4];
    /*0x18D0*/ u8 _18D0[8];
    /*0x18D8*/ u8 isCpu[4];
    /*0x18DC*/ u8 aIStrength[4];
    /*0x18E0*/ s8 turnOrder[4];
    /*0x18E4*/ u8 _18E4[0x18F8 - 0x18E4];
    /*0x18F8*/ s8 fielder[4];
    /*0x18FC*/ u8 _18FC[0x1904 - 0x18FC];
    /*0x1904*/ s8 currentPlayer;
    /*0x1905*/ s8 rosterID;
    /*0x1906*/ u8 numParticipants;
    /*0x1907*/ u8 _1907[2];
    /*0x1909*/ u8 multiPlayerInd;
    /*0x190A*/ u8 _190A[2];
    /*0x190C*/ u8 turnNumberWithinRound;
    /*0x190D*/ u8 _190D[0x193A - 0x190D];
    /*0x193A*/ u8 coinVisible[100];
    /*0x199E*/ u8 _199E[0x1A2B - 0x199E];
    /*0x1A2B*/ u8 difficulty;
    /*0x1A2C*/ u8 _1A2C;
    /*0x1A2D*/ u8 turnCounter;
    /*0x1A2E*/ u8 _1A2E[0x1A3C - 0x1A2E];
    /*0x1A3C*/ u8 _1A3C;
    /*0x1A3D*/ u8 _1A3D[0x1A48 - 0x1A3D];
    /*0x1A48*/ f32 pitcherX;
    /*0x1A4C*/ f32 pitcherZ;
    /*0x1A50*/ VecXZ target[4]; // walk-to targets of the 4 fielders
    /*0x1A70*/ s16 rotationCounter;
    /*0x1A72*/ s16 _1A72;
    /*0x1A74*/ s16 pitchPower;
    /*0x1A76*/ s16 powerRemaining;
    /*0x1A78*/ u8 _1A78[4];
    /*0x1A7C*/ u8 specialWall[2]; // slot of the type-2 target, this round and the last
    /*0x1A7E*/ u8 rotateInd;
    /*0x1A7F*/ u8 phase;
    /*0x1A80*/ u8 _1A80;
    /*0x1A81*/ u8 ballStopped;
    /*0x1A82*/ u8 wallOrder[7];
    /*0x1A89*/ u8 hitNoteBlock;
    /*0x1A8A*/ u8 hitBowserWall;
    /*0x1A8B*/ s8 _1A8B;
    /*0x1A8C*/ u8 _1A8C[0x1D7C - 0x1A8C];
    /*0x1D7C*/ MgCpu_3290 cpu;
    /*0x1DF4*/ u8 _1DF4[0x1E2C - 0x1DF4];
} Mg3290; // size: 0x1E2C

void fn_3_1133C4(void);
void fn_3_1136FC(void);
void fn_3_11391C(void);
void fn_3_113950(void);
void fn_3_113A48(void);
void fn_3_113D20(void);
void fn_3_113EC0(void);
void fn_3_113F14(void);
void fn_3_114204(void);
void fn_3_114384(void);
s32 fn_3_1149B8(void* a, void* b);
void fn_3_114A2C(void);
void fn_3_114A88(s32 init);

#endif // !__GAME_rep_3290_H_
