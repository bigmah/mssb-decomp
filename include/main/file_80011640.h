#ifndef __MAIN_FILE_80011640_H__
#define __MAIN_FILE_80011640_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"

// model.c: character models, their parts data and animation state.

typedef struct CharJoint {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ void* _14;
    /*0x18*/ u8 _18[0xEC - 0x18];
    /*0xEC*/ MtxPtr worldMtx;
} CharJoint;

typedef struct CharModel {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u16 jointCount;
    /*0x08*/ u8 _08[0x10];
    /*0x18*/ CharJoint** joints;
} CharModel;

// One loaded model and its root control.
typedef struct CharSlot {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ CharModel* model;
    /*0x38*/ u8 _38[0xC];
    /*0x44*/ Control ctrl;
    /*0x78*/ u8 _78[0x90 - 0x78];
} CharSlot; // size: 0x90

// Character parts data: a file table plus a model slot.
typedef struct CharPart {
    /*0x00*/ void** files;
    /*0x04*/ void* _04;
    /*0x08*/ void* _08;
    /*0x0C*/ void* _0C;
    /*0x10*/ u8 _10[0x20];
    /*0x30*/ void* _30;
    /*0x34*/ u8 _34[0x28];
    /*0x5C*/ s8 _5C;
    /*0x5D*/ u8 _5D[0x3];
    /*0x60*/ u8 slot;
    /*0x61*/ s8 _61;
    /*0x62*/ u8 _62[0x2];
} CharPart; // size: 0x64

typedef struct CharParts {
    /*0x00*/ CharPart part[2];
    /*0xC8*/ u8 _C8[0x8];
    /*0xD0*/ s8 _D0;
    /*0xD1*/ s8 _D1;
    /*0xD2*/ u8 _D2[0x2];
} CharParts; // size: 0xD4

typedef struct CharActor {
    /*0x000*/ CharModel* model;
    /*0x004*/ u8 _004[0x28];
    /*0x02C*/ CharPart* part;
    /*0x030*/ CharParts* parts;
    /*0x034*/ u8 _034[0x254 - 0x34];
    /*0x254*/ s8 index;
    /*0x255*/ s8 modelIndex;
    /*0x256*/ u8 _256[0x6];
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 _25D[0x27C - 0x25D];
} CharActor; // size: 0x27C

// lbl_8036E548
typedef struct CharMgr {
    /*0x0000*/ u8 _0000[0xC04];
    /*0x0C04*/ CharActor actors[13];
    /*0x2C50*/ CharActor* active[13];
    /*0x2C84*/ u8 _2C84[0x2D6A - 0x2C84];
    /*0x2D6A*/ s8 _2D6A[13];
    /*0x2D77*/ u8 _2D77[0x308C - 0x2D77];
    /*0x308C*/ void (*callback)(void);
    /*0x3090*/ u8 _3090[0x3154 - 0x3090];
} CharMgr; // size: 0x3154

extern CharMgr lbl_8036E548;

void fn_80011640(Mtx a, Mtx out);
void fn_800116DC(CharActor* actor, Mtx m, u16 joint);
void fn_800117CC(Mtx src, Mtx m, Mtx dst);
MtxPtr fn_800118AC(Mtx m, Mtx out);
void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011B64(s32 index);
void fn_80011BE4(s32 index);

void fn_8001B200(void);

void fn_8001B214(void (*callback)(void));

void fn_8001E460(void* value);

void fn_8001E474(void);

#endif
