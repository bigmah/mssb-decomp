#ifndef __REP_7BF0_CHALLENGE_H__
#define __REP_7BF0_CHALLENGE_H__

#include "mssbTypes.h"
#include "Dolphin/GX/GXTypes.h"
#include "main/file_80037054.h"
#include "challenge/rep_7978.h"

typedef struct {
    u8 padding[0x10];
    s16 state;
} ChallengeQueueState;

typedef struct {
    void (*func)(void);
#ifdef TARGET_PC
    void* padding04[2]; // prev, next
    ChallengeQueueState* state; // parent
    u8 padding10[4];
    void* _u14align[0]; // SceneTask.u14 is 8-byte aligned on PC
#else
    u8 padding04[0x08];
    ChallengeQueueState* state;
    u8 padding10[4];
#endif
    u8 menuOpen; // 0x14
    s8 selection;
} ChallengeQueueEntry;

// Rigid-body test settings; all s32 values are fixed point (value * 100000).
typedef struct {
    /*0x00*/ s32 scaledCamera[4]; // fn_80037768 len, frac, radius, mass
    /*0x10*/ s32 unk50;           // RigidBody.unk50
    /*0x14*/ s32 height;          // start position y
    /*0x18*/ s32 angle;           // start rotation about x, degrees
    /*0x1C*/ s32 vel[3];
    /*0x28*/ s32 angVel[3];
    /*0x34*/ s32 cameraFlags;     // fn_80037768 steps
    /*0x38*/ s8 simulationState;  // 0: reset, 1: step, 2: run
    /*0x39*/ s8 stepRequested;
} ChallengeSimulationSettings; // size: 0x3C

struct ChallengeSimulationMenu;
typedef s32 (*ChMenuFunc)(struct ChallengeSimulationMenu* menu, u16 buttons);

// Same layout as DebugMenuItem (main/debug_menu.h).
typedef struct {
    /*0x00*/ u32 flags; // item type
    /*0x04*/ const char* text;
    /*0x08*/ s32 min;
    /*0x0C*/ s32 max;
    /*0x10*/ s32 step[3];
    /*0x1C*/ s32* value;
    /*0x20*/ u32 mask;
    /*0x24*/ s32 selection;
    /*0x28*/ ChMenuFunc func;
} ChallengeMenuItem;

typedef struct ChallengeSimulationMenu {
    void* data;
    s32 count;
    s32 capacity;
    s32 cursor;
    s32 selected;
    u32 flags;
    ChallengeMenuItem* items;
} ChallengeSimulationMenu;

void fn_1_289C0(ChallengeDebugCamera* camera);

void fn_1_29A48(void);

void fn_1_29414(ChallengeQueueEntry* task);

void fn_1_2935C(RigidBody* body);

s32 fn_1_289E0(ChallengeSimulationMenu* menu, u16 buttons);

void fn_1_2948C(ChallengeQueueEntry* task);

void fn_1_28C34(ChallengeSimulationMenu* menu, s32 which, void* data);

s32 fn_1_28AE0(ChallengeSimulationMenu* menu, u16 buttons);

void fn_1_2858C(ChallengeDebugCamera* camera, u16 held, u16 pressed, u16 repeated, ChallengeDebugPad* pad);

void fn_1_28CE8(ChallengeQueueEntry* task);

void fn_1_2905C(void);

void fn_1_295E8(void);

void fn_1_29A9C(void);

#endif
