#ifndef __CHALLENGE_REP_0000_H__
#define __CHALLENGE_REP_0000_H__

#include "mssbTypes.h"

void fn_1_0(void* bank, char* name);

typedef struct {
    u32 textures;
    u32 actor;
    u32 geometry;
    u32 skin;
    u32 extra;
} ChallengeModelHeader;

void fn_1_20(ChallengeModelHeader* model);
void fn_1_1B0(u32* table, s32 count);
void fn_1_568(void);
void fn_1_58C(void);
void fn_1_5E8(void);

#endif
