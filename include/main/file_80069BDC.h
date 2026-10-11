#ifndef __MAIN_FILE_80069BDC_H__
#define __MAIN_FILE_80069BDC_H__

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// Scene/task object pointed to by lbl_803CC1B8.
typedef struct SceneTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x10 - 0x04];
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ u8 _14[0x34 - 0x14];
    /*0x34*/ s16 state;
    /*0x36*/ s16 _36;
    /*0x38*/ s16 _38;
    /*0x3A*/ u8 _3A;
    /*0x3B*/ u8 _3B;
} SceneTask;

extern SceneTask* lbl_803CC1B8;

// Raw input for the stat-total calculation (cleared with memset size 0x16).
typedef struct StatInput {
    /*0x00*/ s16 vals[6];
    /*0x0C*/ u8 order[6]; // 1-based indices into vals
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14[2];
} StatInput; // size: 0x16

typedef struct StatOutput {
    /*0x00*/ s16 vals[6];
    /*0x0C*/ s16 _C;
    /*0x0E*/ s16 _E;
} StatOutput; // size: 0x10

// Challenge-mode save state; starMissionCompletionTracker (size 0x4508) starts with this.
typedef struct ChallengeState {
    /*0x0000*/ ChallengeTrackingStruct trackers[54];
    /*0x0AF8*/ u8 _AF8[0x4415 - 0xAF8];
    /*0x4415*/ u8 _4415;
    /*0x4416*/ u8 _4416[0x441C - 0x4416];
    /*0x441C*/ u8 _441C;
    /*0x441D*/ u8 _441D;
    /*0x441E*/ u8 _441E;
    /*0x441F*/ u8 _441F;
    /*0x4420*/ u8 _4420[2];
    /*0x4422*/ u8 _4422;
    /*0x4423*/ u8 _4423[0x444D - 0x4423];
    /*0x444D*/ u8 _444D[54];
} ChallengeState;

#define gChallengeState (*(ChallengeState*)starMissionCompletionTracker)

typedef struct ChallengeTeamInfo {
    /*0x0*/ u8 _0[2];
    /*0x2*/ u8 _2;
    /*0x3*/ u8 hasMissions;
    /*0x4*/ u8 _4[2];
} ChallengeTeamInfo; // size: 0x6

extern ChallengeTeamInfo lbl_800E8558[54];

// Event callbacks registered by the game module (see fn_3_16892C).
typedef void (*AnimEventCallback)(void* obj, f32 frame, s32 a, s32 b);

void fn_8006C3F0(AnimEventCallback cb);
void fn_8006C3F8(void* obj, f32 frame, s32 a, s32 b);
void fn_8006C43C(AnimEventCallback cb);
void fn_8006C444(void* obj, f32 frame, s32 a, s32 b);
void fn_8006C488(void);

#endif
