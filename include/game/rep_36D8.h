#ifndef __GAME_rep_36D8_H_
#define __GAME_rep_36D8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"

// One g_Runners entry (InMemRunnerType, size 0x154), only the fields used here.
// This unit declares g_Runners as bytes, so it reaches the fields through this view.
typedef struct RepRunnerView {
    /*0x000*/ Vec pos;
    /*0x00C*/ u8 _00C[0x18 - 0xC];
    /*0x018*/ Vec _018; // movement direction
    /*0x024*/ u8 _024[0x64 - 0x24];
    /*0x064*/ f32 fractionalBasesRan;
    /*0x068*/ u8 _068[0xE2 - 0x68];
    /*0x0E2*/ s16 _0E2;
    /*0x0E4*/ u8 _0E4[0x11A - 0xE4];
    /*0x11A*/ u8 _11A;
    /*0x11B*/ u8 _11B[0x123 - 0x11B];
    /*0x123*/ u8 _123;
    /*0x124*/ u8 _124[0x133 - 0x124];
    /*0x133*/ u8 _133;
    /*0x134*/ u8 _134[0x137 - 0x134];
    /*0x137*/ u8 runningDirectionCode;
    /*0x138*/ u8 _138[0x152 - 0x138];
    /*0x152*/ s8 _152; // player slot
    /*0x153*/ u8 _153;
} RepRunnerView;

// Target that moves along the base path (g_Minigame + 0xCB0).
typedef struct RepTarget {
    /*0x00*/ Vec pos;
    /*0x0C*/ Vec vel;
    /*0x18*/ f32 bases; // position along the base path, 0..4
    /*0x1C*/ s16 timer;
    /*0x1E*/ u8 active;
} RepTarget;

// This minigame's view of g_Minigame. This unit declares g_Minigame as bytes,
// so new code reaches the fields through this view (REP_MG).
typedef struct RepMinigameView {
    /*0x0000*/ u8 _0000[0xCB0];
    /*0x0CB0*/ RepTarget target;
    /*0x0CD0*/ Vec coinPos[100];
    /*0x1180*/ Vec coinVel[100];
    /*0x1630*/ f32 itemBases[15]; // item position along the base path
    /*0x166C*/ u8 _166C[0x17C0 - 0x166C];
    /*0x17C0*/ u32 _17C0; // frames played
    /*0x17C4*/ u32 _17C4; // frames left
    /*0x17C8*/ s16 coinFrames[100];
    /*0x1890*/ s16 points[4];
    /*0x1898*/ s16 latestPoints[4];
    /*0x18A0*/ u8 _18A0[2];
    /*0x18A2*/ s16 _18A2; // frames
    /*0x18A4*/ s16 _18A4; // frames
    /*0x18A6*/ u8 _18A6[0x18BC - 0x18A6];
    /*0x18BC*/ s16 pointsPair[4][2];
    /*0x18CC*/ s8 characterIndex[4];
    /*0x18D0*/ u8 _18D0[0x18D8 - 0x18D0];
    /*0x18D8*/ u8 _18D8[4]; // per player
    /*0x18DC*/ u8 aiStrength[4];
    /*0x18E0*/ u8 _18E0[0x18F0 - 0x18E0];
    /*0x18F0*/ u8 _18F0[4];
    /*0x18F4*/ s8 slotPlayer[4];
    /*0x18F8*/ s8 playerSlot[4];
    /*0x18FC*/ s8 _18FC[4]; // per runner slot; < 0: none
    /*0x1900*/ s8 _1900[4]; // per runner slot; < 0: none
    /*0x1904*/ s8 currentPlayer;
    /*0x1905*/ s8 rosterID;
    /*0x1906*/ u8 numParticipants;
    /*0x1907*/ u8 _1907[2];
    /*0x1909*/ u8 multiPlayerInd;
    /*0x190A*/ u8 _190A;
    /*0x190B*/ u8 turnOverStatus;
    /*0x190C*/ u8 _190C[0x193A - 0x190C];
    /*0x193A*/ u8 itemState[100]; // items: 1..6 = type on the field, +100 once collected
    /*0x199E*/ u8 _199E[0x1A26 - 0x199E];
    /*0x1A26*/ s16 pointsReqToWin;
    /*0x1A28*/ u8 _1A28[2];
    /*0x1A2A*/ u8 gameMode;
    /*0x1A2B*/ u8 difficulty;
    /*0x1A2C*/ u8 _1A2C[0x1A37 - 0x1A2C];
    /*0x1A37*/ u8 _1A37;
    /*0x1A38*/ u8 _1A38[2];
    /*0x1A3A*/ u8 _1A3A; // 0..2, raised as time passes
    /*0x1A3B*/ u8 _1A3B;
    /*0x1A3C*/ u8 _1A3C;
    /*0x1A3D*/ u8 _1A3D[0x1AE0 - 0x1A3D];
    /*0x1AE0*/ Vec ballPos;
    /*0x1AEC*/ Vec ballVel;
    /*0x1AF8*/ s16 _1AF8;
    /*0x1AFA*/ s16 frames; // frames in the current phase, saturates at 0x7FFF
    /*0x1AFC*/ s16 _1AFC;
    /*0x1AFE*/ s16 _1AFE[4]; // per runner slot: frames spent running
    /*0x1B06*/ s16 _1B06;
    /*0x1B08*/ s16 _1B08[6];
    /*0x1B14*/ u8 _1B14;
    /*0x1B15*/ u8 _1B15[4]; // per player
    /*0x1B19*/ u8 phase;
    /*0x1B1A*/ u8 _1B1A[6]; // per item type: 0 = spawn, 1 = respawn delay, else scoring kind + 2
    /*0x1B20*/ union {
        u8 pos[15]; // searched by fn_3_13E3A4
        struct {
            u8 _0[6];
            s8 pair[4][2]; // 0x1B26: item type index, -1: none
            u8 _E;
        } it;
    } _1B20;
    /*0x1B2F*/ u8 _1B2F[4]; // per runner slot; 0xFF: none
    /*0x1B33*/ u8 _1B33;
    /*0x1B34*/ u8 _1B34[0x1D58 - 0x1B34];
    /*0x1D58*/ s16 _1D58;
    /*0x1D5A*/ u8 _1D5A[0x1D74 - 0x1D5A];
    /*0x1D74*/ s8 _1D74; // -1: none
    /*0x1D75*/ u8 _1D75[0x1DC0 - 0x1D75];
    /*0x1DC0*/ u8 _1DC0[4];
    /*0x1DC4*/ u8 _1DC4[0x1E00 - 0x1DC4];
    /*0x1E00*/ u8 _1E00;
} RepMinigameView;

// View of lbl_3_common_bss_37400, only the fields used here.
typedef struct RepBss37400View {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 humanPlayer;
} RepBss37400View;

// View of g_Ball, only the fields used here.
typedef struct RepBallView {
    /*0x00*/ Vec pos;
} RepBallView;

// View of g_GameLogic, only the fields used here.
typedef struct RepGameLogicView {
    /*0x000*/ u8 _000[0xFE];
    /*0x0FE*/ u16 _0FE;
    /*0x100*/ s16 _100;
    /*0x102*/ u8 _102[0x121 - 0x102];
    /*0x121*/ u8 _121;
    /*0x122*/ u8 _122[3];
    /*0x125*/ u8 _125; // init step
} RepGameLogicView;

void fn_3_13C7BC(void);
u32 fn_3_13D578(s8 a);
s32 fn_3_13D5E8(void* a, void* b);
f32 fn_3_13D618(s8 idx, f32 ang, s8* dir);
s32 fn_3_13DA20(void* a, void* b);
f32 fn_3_13DA50(s8 idx, f32 ang, s8* dir);
void fn_3_13DC48(s8 idx, f32 ang, f32* out1, f32* out2);
f32 fn_3_13DDE0(f32 a, f32 b, u8 mode);
void fn_3_13DEA4(void);
void fn_3_13DFBC(camera_803c639c_s* cam);
void fn_3_13E174(u8 a);
void fn_3_13E21C(RepTarget* t);
void fn_3_13E3A4(RepTarget* t);
void fn_3_13E670(void);
void fn_3_13E6D4(void);
void fn_3_13E7D4(s32 p);
void fn_3_13EA30(void);
void fn_3_13EC44(s32 type);
void fn_3_13F484(void);
void fn_3_13F6C8(void);
void fn_3_13F7E4(void);
void fn_3_13F8C4(void);
void fn_3_13FC24(void);
void fn_3_140284(void);
void fn_3_140484(void);
void fn_3_1405D8(void);
void fn_3_1406F4(void);
void fn_3_1409AC(void);
void fn_3_140BCC(void);
void fn_3_140CE0(void);
void fn_3_1410F0(void);
void fn_3_1412BC(void);
void fn_3_1413E4(void);
void fn_3_1414AC(void);

#endif // !__GAME_rep_36D8_H_
