#ifndef __GAME_AUTO_00_000249E8_TEXT_H_
#define __GAME_AUTO_00_000249E8_TEXT_H_

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// Character actor (entries of lbl_8036E548.actors, cf. CharActor in main/file_80011640.h).
typedef struct GameActorView {
    /*0x000*/ u8 _000[0x34];
    /*0x034*/ VecXYZ pos;
    /*0x040*/ f32 _040;
    /*0x044*/ f32 rotY;
    /*0x048*/ u8 _048[0x68 - 0x48];
    /*0x068*/ s16 _068; // animation frames left? (0 = done)
    /*0x06A*/ u8 _06A[0x252 - 0x6A];
    /*0x252*/ s8 kind; // character id
    /*0x253*/ u8 _253[0x257 - 0x253];
    /*0x257*/ s8 team;
    /*0x258*/ u8 _258[0x25D - 0x258];
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E[0x279 - 0x25E];
    /*0x279*/ u8 flags;
    /*0x27A*/ u8 _27A[0x27C - 0x27A];
} GameActorView; // size: 0x27C

typedef struct StadiumPartView {
    /*0x00*/ u8 active;
    /*0x01*/ u8 _01[0x28 - 0x1];
} StadiumPartView; // size: 0x28

// Stadium object (lbl_8036E548.stadium, only the fields used here).
typedef struct StadiumObjView {
    /*0x000*/ u8 _000[0xC6];
    /*0x0C6*/ u8 _0C6;
    /*0x0C7*/ u8 _0C7[0x2CE - 0xC7];
    /*0x2CE*/ StadiumPartView parts[4];
} StadiumObjView;

// Actor manager lbl_8036E548 (see ActorManager in main/file_80026134.h).
typedef struct ActorMgrView {
    /*0x0000*/ u8 _0000[0xC04];
    /*0x0C04*/ GameActorView storage[13];
    /*0x2C50*/ GameActorView* actors[13]; // 0-8 fielders, 9-12 batter and runners
    /*0x2C84*/ u8 _2C84[0x2D77 - 0x2C84];
    /*0x2D77*/ u8 _2D77;
    /*0x2D78*/ u8 _2D78[2];
    /*0x2D7A*/ u8 _2D7A; // runner load counter (fn_3_6BA64)
    /*0x2D7B*/ u8 _2D7B;
    /*0x2D7C*/ u8 _2D7C;
    /*0x2D7D*/ u8 _2D7D[0x2D90 - 0x2D7D];
    /*0x2D90*/ StadiumObjView* stadium;
} ActorMgrView;

// Fielder (g_Fielders, stride 0x268; only the fields used here).
typedef struct FielderView {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ u8 _00C[0x48 - 0xC];
    /*0x048*/ f32 rotY;
    /*0x04C*/ u8 _04C[0x1C7 - 0x4C];
    /*0x1C7*/ u8 _1C7;
    /*0x1C8*/ u8 _1C8[0x218 - 0x1C8];
    /*0x218*/ u8 opponentIdx; // 0 for the human team's own players, else 1..n
    /*0x219*/ u8 _219[0x268 - 0x219];
} FielderView; // size: 0x268

// One entry of a cutscene actor-placement table (lbl_3_data_1E434, lbl_3_data_1F090, lbl_3_data_1D28).
typedef struct SceneActorSetup {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ s16 anim;
    /*0x12*/ s16 animArg;
    /*0x14*/ u8 actor; // actor slot, or for lbl_3_data_1F090 the fielder opponentIdx
    /*0x15*/ u8 _15;
    /*0x16*/ u8 animA;
    /*0x17*/ u8 animMode;
    /*0x18*/ u8 animB;
    /*0x19*/ u8 keepPos;
    /*0x1A*/ u8 _1A[2];
} SceneActorSetup; // size: 0x1C

typedef struct SceneActorState {
    /*0x00*/ VecXYZ pos;
    /*0x0C*/ f32 rotY;
    /*0x10*/ f32 targetRotY; // facing toward the destination
    /*0x14*/ f32 speed;      // forward step per frame
    /*0x18*/ u8 _18[0x1C - 0x18];
    /*0x1C*/ f32 _1C; // compared with the actor's _068
    /*0x20*/ u8 _20[0x28 - 0x20];
    /*0x28*/ u8 arrived;
    /*0x29*/ u8 moving;
    /*0x2A*/ u8 _2A[0x2C - 0x2A];
} SceneActorState; // size: 0x2C

// Cutscene work area pointed to by lbl_3_common_bss_1323C (only the fields used here).
typedef struct SceneWork {
    /*0x000*/ SceneActorState actors[13];
    /*0x23C*/ s16 _23C;
    /*0x23E*/ s16 _23E;
    /*0x240*/ s16 actorSetup[13]; // table entry per actor, -1 = none
    /*0x25A*/ s16 _25A;
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 mode;
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F;
    /*0x260*/ s8 _260; // index into lbl_3_data_1F74 (scene to start)
    /*0x261*/ u8 animSet[13];
    /*0x26E*/ u8 posSet[13];
    /*0x27B*/ s8 _27B;
    /*0x27C*/ u8 _27C;
    /*0x27D*/ u8 _27D;
    /*0x27E*/ s8 busy;
    /*0x27F*/ u8 _27F;
    /*0x280*/ u8 _280;
} SceneWork;

// lbl_3_data_2398 entry.
// A scripted scene event and the game situation that triggers it (fn_3_21F14); -1 = don't care.
typedef struct Unk2398Entry {
    /*0x00*/ s32 inning;      // compared with g_Scores._AC (4: 4 or later)
    /*0x04*/ s32 _04;
    /*0x08*/ s32 outs;
    /*0x0C*/ s32 runner[3];   // 1: base occupied, 0: base empty
    /*0x18*/ s32 situation;   // fn_3_22ABC result (-1 none, 1, 2), 0 = none
    /*0x1C*/ s32 leading;     // fn_3_22A20 result
    /*0x20*/ s32 captainDuel; // 1: batter/pitcher are the two captains with a pair-table entry
    /*0x24*/ s32 once;        // nonzero: only plays while _34[0] is clear
    /*0x28*/ s32 _28;
    /*0x2C*/ s32 _2C;
    /*0x30*/ s32 _30;         // copied to SceneWork._27B when played
    /*0x34*/ s32 _34[3];      // played flags
} Unk2398Entry; // size: 0x40

// Effect/state block lbl_3_common_bss_32724 (size 0x124, only the fields used here).
typedef struct Unk32724 {
    /*0x00*/ u8 _00[0x90];
    /*0x90*/ s16 _90;
    /*0x92*/ u8 _92[0x9A - 0x92];
    /*0x9A*/ u8 _9A; // load step (fn_3_6B4C8, fn_3_6B5D8, fn_3_6BA64)
    /*0x9B*/ u8 _9B;
    /*0x9C*/ u8 _9C[2];
    /*0x9E*/ s16 _9E; // character ids
    /*0xA0*/ s16 _A0;
    /*0xA2*/ s16 _A2;
    /*0xA4*/ u8 _A4[0xAE - 0xA4];
    /*0xAE*/ u8 _AE; // set when a captain-duel scene event plays
    /*0xAF*/ s8 _AF; // pitcher roster id for it
    /*0xB0*/ u8 _B0;
    /*0xB1*/ u8 _B1; // set once the scene skip point is reached (fn_3_23890)
    /*0xB2*/ u8 _B2[0xC8 - 0xB2];
    /*0xC8*/ u8 _C8;
    /*0xC9*/ u8 _C9;
    /*0xCA*/ u8 _CA;
    /*0xCB*/ u8 _CB[0xD4 - 0xCB];
    /*0xD4*/ u8 _D4;
    /*0xD5*/ u8 _D5[0x124 - 0xD5];
} Unk32724; // size: 0x124

void fn_3_249E8(s32 idx);
void fn_3_24ADC(s32 idx, s32 queued);
void fn_3_24DBC(s32 mode);
void fn_3_24EA0(void);
void fn_3_24F20(void);
void fn_3_24F24(s32 mode);
void fn_3_250FC(void);

#endif
