#ifndef __CHALLENGE_REP_0138_H__
#define __CHALLENGE_REP_0138_H__

#include "mssbTypes.h"

typedef struct ChallengeModelOffsets {
    u32 mainActor;
    u32 secondaryActor;
    u32 effects;
    u32 mainGeometry;
    u32 secondaryGeometry;
    u32 textures;
} ChallengeModelOffsets;

void fn_1_5540(void);

void fn_1_7848(void);

void fn_1_77EC(void* context);

void fn_1_54E0(void* matrix);

void fn_1_786C(void);

void fn_1_78E4(void);

void fn_1_7EF8(void);

void fn_1_7E04(f32 scale);

void fn_1_717C(ChallengeModelOffsets* model);

void fn_1_7280(void);

#endif
