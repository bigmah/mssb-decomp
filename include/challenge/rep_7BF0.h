#ifndef __REP_7BF0_CHALLENGE_H__
#define __REP_7BF0_CHALLENGE_H__

#include "mssbTypes.h"

typedef struct {
    u8 padding[0x10];
    s16 state;
} ChallengeQueueState;

typedef struct {
    u8 padding[0x0C];
    ChallengeQueueState* state;
    u8 padding10[5];
    s8 selection;
} ChallengeQueueEntry;

typedef struct {
    s32 scaledCamera[4];
    u8 padding[0x24];
    s32 cameraFlags;
    s8 simulationState;
    u8 stepRequested;
} ChallengeSimulationSettings;

typedef struct {
    u32 flags;
    const char* text;
    u8 padding08[0x1C];
    u32 selection;
    u8 padding28[4];
} ChallengeMenuItem;

typedef struct {
    void* data;
    s32 count;
    s32 capacity;
    s32 cursor;
    s32 selected;
    u32 flags;
    ChallengeMenuItem* items;
} ChallengeSimulationMenu;

void fn_1_289C0(u8* object);

void fn_1_29A48(void);

void fn_1_29414(u8* object);

void fn_1_2935C(void* camera);

s32 fn_1_289E0(ChallengeSimulationMenu* menu, u16 buttons);

void fn_1_2948C(u8* object);

void fn_1_28C34(ChallengeSimulationMenu* menu, s32 which, void* data);

s32 fn_1_28AE0(ChallengeSimulationMenu* menu);

#endif
