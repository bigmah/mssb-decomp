#ifndef __CHALLENGE_REP_74A0_H__
#define __CHALLENGE_REP_74A0_H__

#include "mssbTypes.h"
#include "C3/geoPalette.h"

typedef struct ChallengeDrawActor {
    u8 padding[0x14];
    struct DODisplayObj* display;
    u8 padding18[0x5C];
    struct ChallengeDrawActor* children;
    u8 padding78[0x74];
    MtxPtr worldMatrix;
    u8 paddingF0[0x10];
    struct ChallengeDrawActor* next;
} ChallengeDrawActor;

typedef struct {
    ChallengeDrawActor* actor;
    u8 padding[4];
    void (*prepare)(void);
} ChallengeActorDrawing;

typedef struct {
    u8 padding[0x10];
    f32 x;
    f32 y;
    f32 z;
} ChallengeOrbitPosition;

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

void fn_1_1A1EC(ChallengeActorDrawing* drawing, s32 mode);

void fn_1_18E04(ChallengeOrbitPosition* position, f32 degrees);

#endif
