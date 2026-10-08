#ifndef __CHALLENGE_REP_74A0_H__
#define __CHALLENGE_REP_74A0_H__

#include "mssbTypes.h"

typedef struct {
    void (*update)(u8*);
    u8 padding[0x0C];
    u16 state;
    u8 padding12[3];
    s8 menu;
} ChallengeRosterQueue;

void fn_1_1D10C(void);

void fn_1_1D0E8(u8* object);

void fn_1_1D450(u8* object);

s32 fn_1_19D1C(u8 value);

void fn_1_1D470(void);

#endif
