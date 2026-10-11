#ifndef __CHALLENGE_REP_74A0_H__
#define __CHALLENGE_REP_74A0_H__

#include "mssbTypes.h"
#include "C3/geoPalette.h"
#include "C3/control.h"

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
    // (ActorObject in include/main/file_800BD8C4.h)
    /*0x00*/ ChallengeActorDrawing drawing;
    /*0x0C*/ u8 padding0C[4];
    /*0x10*/ Control worldControl;
    /*0x4C*/ u8 padding4C[8];
    /*0x54*/ f32 scale;
    /*0x58*/ u8 padding58[2];
    /*0x5A*/ u8 setSpeed;
    /*0x5B*/ u8 padding5B[0x11];
    /*0x6C*/ u8 visible; // animateBones in ActorObject
    /*0x6D*/ u8 padding6D[0x23];
} ChallengeDrawNode;

typedef struct {
    u16 count;
    u8 padding[0x32];
    ChallengeDrawNode nodes[1];
} ChallengeDrawCollection;

typedef struct {
    u16 selectedBone;
    u8 selectedActor;
    u8 _03;
    u8 _04;
    u8 _05;
    u8 matAlpha; // material colour for fn_1_19D60, stored a, b, g, r
    u8 matBlue;
    u8 matGreen;
    u8 matRed;
    u8 padding0A[0x182];
    Mtx matrix; // lbl_1_bss_6B7C (camera view)
} ChallengeBoneSelection;

typedef struct {
    void (*update)(u8*);
    u8 padding[0x0C];
    s16 state;
    u8 padding12[2];
    u8 actorIndex; // viewer: selected actor in lbl_8036E548
    s8 menu;
    u8 viewMode; // 1 = show all actors
    u8 _17;
    u8 _18;
} ChallengeRosterQueue;

// One falling confetti piece (linked list, drawn by fn_1_182C0).
typedef union ChallengeConfettiColor {
    u32 rgba;
    GXColor c;
} ChallengeConfettiColor;

typedef struct ChallengeConfetti {
    /*0x00*/ struct ChallengeConfetti* next;
    /*0x04*/ Vec pos; // x/y in screen units (-1..1), z = depth scale
    /*0x10*/ Vec vel;
    /*0x1C*/ Vec rot;
    /*0x28*/ Vec rotVel;
    /*0x34*/ u8 pad34[4];
    /*0x38*/ f32 width;
    /*0x3C*/ f32 height;
    /*0x40*/ ChallengeConfettiColor front;
    /*0x44*/ ChallengeConfettiColor back;
    /*0x48*/ s16 delay;
    /*0x4A*/ s16 index;
} ChallengeConfetti;

// Texture bank (lbl_1_bss_6AAC entries): like DOTexBank but with a 16-bit count.
typedef struct ChallengeTexBank {
    u16 count;
    u16 pad02;
    DOTexInfo tex[1]; // variable length
} ChallengeTexBank;

// Depth-sort entry used by fn_1_1857C.
typedef struct ChallengeConfettiSort {
    ChallengeConfetti* piece;
    f32 depth;
} ChallengeConfettiSort;

// Task that owns the confetti list.
typedef struct ChallengeConfettiTask {
    /*0x00*/ u8 pad00[0xC];
    /*0x0C*/ ChallengeConfetti* pieces;
    /*0x10*/ u8 pad10[4];
    /*0x14*/ u16 count; // low 12 bits
} ChallengeConfettiTask;

// Confetti settings (lbl_1_data_FB24).
typedef struct ChallengeConfettiConfig {
    s32 count;
    s32 speed; // / 100000
    s32 spin;  // / 100000
    s32 width; // / 100000
    s32 height; // / 100000
    s32 colorMin;
} ChallengeConfettiConfig;

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
    u8 pad00[8];
    void* model; // loaded by fn_1_1CBE4
    u8 pad0C[0x34 - 0xC];
    Vec pos;
    Vec rot;
    f32 scale;
    u8 pad50[0x27C - 0x50];
} ChallengeViewerActor;

// View of lbl_8036E548 (global actor manager, cf. ActorManager in main/file_80026134.h).
typedef struct ChallengeActorMgr {
    /*0x000*/ u8 pad000[0x60];
    /*0x060*/ ChallengeDrawCollection* collection;
    /*0x064*/ u8 pad064[0xAC - 0x64];
    /*0x0AC*/ struct Light* lights[3];
    /*0x0B8*/ u8 pad0B8[0xC04 - 0xB8];
    /*0xC04*/ ChallengeViewerActor actors[24];
} ChallengeActorMgr;

void fn_1_1D10C(void);

void fn_1_1D0E8(u8* object);

void fn_1_1D450(u8* object);

s32 fn_1_19D1C(u8 value);

void fn_1_1D470(void);

void fn_1_1A1EC(ChallengeActorDrawing* drawing, MtxPtr camera);

void fn_1_1A3B4(void);

void fn_1_1A850(MtxPtr bone, MtxPtr camera, u8 r, u8 g, u8 b, u8 a);

void fn_1_1D110(void);

void fn_1_1CBE4(u8* object);

void fn_1_18E04(struct ChallengeConfetti* piece, f32 degrees);

void fn_1_1A290(ChallengeDrawCollection* collection, MtxPtr camera);

void fn_1_19D60(struct DODisplayObj* dispObj, MtxPtr camera);

void fn_1_1A774(void);

void fn_1_1D514(void);

void fn_1_1B038(void);

void fn_1_182C0(ChallengeConfetti* piece);

void fn_1_18EE4(ChallengeConfetti* piece);

void fn_1_191DC(ChallengeConfettiTask* task);

s32 fn_1_1857C(ChallengeConfettiTask* task);

void fn_1_1957C(void);

void fn_1_1994C(void);

void fn_1_1ADA4(void);

void fn_1_1B424(void);

void fn_1_1B6BC(void);

void fn_1_1B0FC(void);

void fn_1_1B2C8(void);

#endif
