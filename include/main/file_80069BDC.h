#ifndef __MAIN_FILE_80069BDC_H__
#define __MAIN_FILE_80069BDC_H__

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"

// Game texture descriptor (consumed by SetDisplayStateTexture).
typedef struct TexDesc {
    /*0x00*/ void* image;
    /*0x04*/ void* palette;
    /*0x08*/ u16 height;
    /*0x0A*/ u16 width;
    /*0x0C*/ u8 _0C[0x20 - 0x0C];
} TexDesc; // size: 0x20

// Texture set used by the logo/warning screens: a count word followed by descriptors.
typedef struct TexSet {
    /*0x00*/ u32 count;
    /*0x04*/ TexDesc tex[1];
} TexSet;

// Display-list node passed to fn_800A7D4C (two per task, indexed by lbl_803CBBC0).
typedef struct DrawNode {
    /*0x00*/ void* next;
    /*0x04*/ void (*draw)(struct DrawNode* node);
    /*0x08*/ s32 kind;
    /*0x0C*/ TexSet* texSet;
    /*0x10*/ s32 texIdx;
    /*0x14*/ s32 texIdx2;
    /*0x18*/ f32 alpha;
    /*0x1C*/ f32 alpha2;
} DrawNode; // size: 0x20

// Loaded resource handle (freed with fn_800ACF14); data is the loaded file.
typedef struct ResHandle {
    /*0x0*/ void* data;
} ResHandle;

// Scene/task object pointed to by lbl_803CC1B8.
typedef struct SceneTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct SceneTask* prev; // draw-queue links (fn_800B0A5C_insertQueue)
    /*0x08*/ struct SceneTask* next;
    /*0x0C*/ struct SceneTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ union {
        ResHandle* res;
        u16 objIdx;  // index into lbl_80371C30 (child tasks)
    } u14;
    /*0x18*/ DrawNode* nodes;
    /*0x1C*/ void* player;
    /*0x20*/ void* work;
    /*0x24*/ void* buffer;
    /*0x28*/ void* res28;
    /*0x2C*/ u8 _2C[0x30 - 0x2C];
    /*0x30*/ u32 voice;
    /*0x34*/ s16 state;
    /*0x36*/ u16 _36;
    /*0x38*/ u8 _38;
    /*0x39*/ u8 _39;
    /*0x3A*/ u8 _3A;
    /*0x3B*/ u8 _3B;
    /*0x3C*/ s8 volStep;
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

// Saved challenge-mode team member (character id, field positions, handedness).
typedef struct ChallengeTeamEntry {
    /*0x0*/ s16 id;
    /*0x2*/ u8 pos[2];
    /*0x4*/ s8 hand; // FieldingArm * 2 + BattingStance
    /*0x5*/ u8 _5;
} ChallengeTeamEntry; // size: 0x6

// Challenge-mode save state; starMissionCompletionTracker (size 0x4508) starts with this.
typedef struct ChallengeState {
    /*0x0000*/ ChallengeTrackingStruct trackers[54];
    /*0x0AF8*/ u8 _AF8[0x1606 - 0xAF8];
    /*0x1606*/ s8 _1606;
    /*0x1607*/ u8 _1607[0x40B8 - 0x1607];
    /*0x40B8*/ ChallengeTeamEntry teams[9]; // ids must be unique
    /*0x40EE*/ u8 _40EE[0x43BC - 0x40EE];
    /*0x43BC*/ s16 _43BC; // 0..1000
    /*0x43BE*/ u8 _43BE[0x4415 - 0x43BE];
    /*0x4415*/ u8 _4415;
    /*0x4416*/ u8 _4416[0x441B - 0x4416];
    /*0x441B*/ u8 _441B;
    /*0x441C*/ u8 _441C;
    /*0x441D*/ u8 _441D;
    /*0x441E*/ u8 _441E;
    /*0x441F*/ u8 _441F;
    /*0x4420*/ u8 _4420[2];
    /*0x4422*/ u8 _4422;
    /*0x4423*/ u8 _4423[0x4445 - 0x4423];
    /*0x4445*/ u8 _4445; // nonzero: the team is already set up
    /*0x4446*/ u8 _4446[0x444D - 0x4446];
    /*0x444D*/ u8 _444D[54];
} ChallengeState;

// What ChallengeTrackingStruct.scoutFlagPointer points to.
typedef struct ScoutFlagTable {
    /*0x0*/ u8 _0[4];
    /*0x4*/ s8 flags[8][6];
} ScoutFlagTable;

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

void fn_80069BDC(TexSet* set, s32 idx, f32 alpha, s32 idx2, f32 alpha2);
void fn_8006A194(TexSet* set, s32 idx, f32 alpha);
void fn_8006A500(TexSet* set, s32 idx, f32 alpha);
void fn_8006A824(TexSet* set, s32 idx, f32 alpha);
void fn_8006AC24(DrawNode* node);
void fn_8006AF6C(void);
void fn_8006AF9C(void);
void fn_8006B230(void);
void fn_8006B668(void);
void fn_8006B78C(void);
void fn_8006BB60(void);
void fn_8006BE00(void);
void fn_8006C088(s32 alt);
void fn_8006C0D0(void);
u8 fn_8006C100(s16 value);
s16 fn_8006C13C(StatInput* in);
void fn_8006C2B4(StatOutput* out, StatInput* in);
s16 fn_8006C268(StatOutput* stats);
void fn_8006C398(StatInput* in);

void fn_8006C3F0(AnimEventCallback cb);
void fn_8006C3F8(void* obj, f32 frame, s32 a, s32 b);
void fn_8006C43C(AnimEventCallback cb);
void fn_8006C444(void* obj, f32 frame, s32 a, s32 b);
void fn_8006C488(void);

#endif
