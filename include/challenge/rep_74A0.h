#ifndef __CHALLENGE_REP_74A0_H__
#define __CHALLENGE_REP_74A0_H__

#include "mssbTypes.h"
#include "C3/geoPalette.h"

typedef struct ChallengeDrawActor {
    u8 padding[6];
    u16 boneCount;
    u8 padding08[0x0C];
    struct DODisplayObj* display;
    u8 padding18[0x5C];
    struct ChallengeDrawActor* children;
    u8 padding78[0x74];
    MtxPtr worldMatrix;
    u8 paddingF0[0x10];
    struct ChallengeDrawActor* next;
} ChallengeDrawActor;

typedef struct ChallengeActorDrawing {
    ChallengeDrawActor* actor;
    u8 padding[4];
    void (*prepare)(struct ChallengeActorDrawing*);
} ChallengeActorDrawing;

typedef struct {
    ChallengeActorDrawing drawing;
    u8 padding0C[0x60];
    u8 visible;
    u8 padding6D[0x23];
} ChallengeDrawNode;

typedef struct {
    u16 count;
    u8 padding[0x32];
    ChallengeDrawNode nodes[1];
} ChallengeDrawCollection;

typedef struct {
    u8 padding[0x10];
    f32 x;
    f32 y;
    f32 z;
} ChallengeOrbitPosition;

typedef struct {
    u16 selectedBone;
    u8 selectedActor;
    u8 padding03[0x189];
    Mtx matrix;
} ChallengeBoneSelection;

typedef struct {
    void (*update)(u8*);
    u8 padding[0x0C];
    u16 state;
    u8 padding12[2];
    u8 actorIndex; // viewer: selected actor in lbl_8036E548
    s8 menu;
} ChallengeRosterQueue;

// Debug viewer camera (lbl_1_bss_6B7C).
typedef struct ChallengeCamera {
    /*0x00*/ Mtx view;
    /*0x30*/ u16 rotX;
    /*0x32*/ u16 rotY;
    /*0x34*/ f32 panX;
    /*0x38*/ f32 panY;
    /*0x3C*/ Vec target;
    /*0x48*/ Vec pos;
    /*0x54*/ u8 pad54[8];
} ChallengeCamera;

// View of a controller entry in lbl_803C77B8 (PadState in main/file_800A7C08.h,
// which can't be included next to UnknownHomes_Static.h).
typedef struct ChallengePad {
    u8 pad00[0x10];
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
    u8 triggerL;
    u8 triggerR;
} ChallengePad;

// View of an actor entry in lbl_8036E548 (+0xC04, stride 0x27C).
typedef struct ChallengeViewerActor {
    u8 pad00[0x34];
    Vec pos;
    Vec rot;
    u8 pad4C[0x27C - 0x4C];
} ChallengeViewerActor;

void fn_1_1D10C(void);

void fn_1_1D0E8(u8* object);

void fn_1_1D450(u8* object);

s32 fn_1_19D1C(u8 value);

void fn_1_1D470(void);

void fn_1_1A1EC(ChallengeActorDrawing* drawing, s32 mode);

void fn_1_18E04(ChallengeOrbitPosition* position, f32 degrees);

void fn_1_1A290(ChallengeDrawCollection* collection, s32 mode);

void fn_1_1A774(void);

void fn_1_1D514(void);

void fn_1_1B038(void);

void fn_1_1ADA4(void);

void fn_1_1B424(void);

void fn_1_1B6BC(void);

void fn_1_1B0FC(void);

void fn_1_1B2C8(void);

#endif
