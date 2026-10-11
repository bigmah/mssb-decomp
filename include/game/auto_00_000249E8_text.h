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
    /*0x048*/ u8 _048[0x257 - 0x48];
    /*0x257*/ s8 team;
    /*0x258*/ u8 _258[0x25D - 0x258];
    /*0x25D*/ u8 _25D;
    /*0x25E*/ u8 _25E[0x279 - 0x25E];
    /*0x279*/ u8 flags;
} GameActorView;

// Actor manager lbl_8036E548 (see ActorManager in main/file_80026134.h).
typedef struct ActorMgrView {
    /*0x0000*/ u8 _0000[0x2C50];
    /*0x2C50*/ GameActorView* actors[13]; // 0-8 fielders, 9-12 batter and runners
} ActorMgrView;
extern ActorMgrView lbl_8036E548;

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
extern FielderView g_Fielders[];

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
    /*0x10*/ u8 _10[0x2C - 0x10];
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
    /*0x260*/ u8 _260;
    /*0x261*/ u8 animSet[13];
    /*0x26E*/ u8 posSet[13];
    /*0x27B*/ u8 _27B;
    /*0x27C*/ u8 _27C;
    /*0x27D*/ u8 _27D;
    /*0x27E*/ s8 busy;
    /*0x27F*/ u8 _27F;
    /*0x280*/ u8 _280;
} SceneWork;
extern SceneWork* lbl_3_common_bss_1323C;

void fn_3_249E8(s32 idx);
void fn_3_24ADC(s32 idx, s32 queued);
void fn_3_24DBC(s32 mode);
void fn_3_24EA0(void);
void fn_3_24F20(void);
void fn_3_24F24(s32 mode);
void fn_3_250FC(void);

#endif
