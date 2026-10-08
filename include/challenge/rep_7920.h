#ifndef __REP_7920_CHALLENGE_H__
#define __REP_7920_CHALLENGE_H__

#include "mssbTypes.h"

void* fn_1_26BFC(u16* resource, s32 index);

typedef struct ChallengeAnimation {
    f32 position;
    f32 scale;
    s16 mode;
    s16 frame;
    s16 timer;
    s16 resourceIndex;
    u8 enabled;
    u8 active : 1;
    u8 horizontal : 2;
    u8 vertical : 2;
    u8 reserved : 3;
    u8 pad12[2];
    void* data;
    u16 first;
    u16 second;
    void* resource;
} ChallengeAnimation;

void fn_1_26B7C(ChallengeAnimation* animation);

#endif
