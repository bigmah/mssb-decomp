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
} ChallengeQueueEntry;

typedef struct {
    s32 scaledCamera[4];
    u8 padding[0x24];
    s32 cameraFlags;
    s8 simulationState;
    u8 stepRequested;
} ChallengeSimulationSettings;

void fn_1_289C0(u8* object);

void fn_1_29A48(void);

void fn_1_29414(u8* object);

void fn_1_2935C(void* camera);

#endif
