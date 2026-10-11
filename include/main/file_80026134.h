#ifndef __MAIN_FILE_80026134_H__
#define __MAIN_FILE_80026134_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"

// The game's Control is 0x44 bytes; C3/control.h's Control is smaller.
typedef struct JointCtrl {
    Control c;
    u8 pad[0x44 - sizeof(Control)];
} JointCtrl;

typedef struct ModelJoint {
    /*0x00*/ u8 unk0[0xC];
    /*0x0C*/ struct ModelJoint* parent;
    /*0x10*/ u8 unk10[0x60 - 0x10];
    /*0x60*/ JointCtrl ctrl;
    /*0xA4*/ u8 unkA4[0xEC - 0xA4];
    /*0xEC*/ MtxPtr worldMtx;
} ModelJoint;

typedef struct Model {
    /*0x00*/ u8 unk0[0x18];
    /*0x18*/ ModelJoint** joints;
} Model;

typedef struct ModelSlot {
    /*0x00*/ u8 unk0[0x34];
    /*0x34*/ Model* model;
    /*0x38*/ u8 unk38[0x90 - 0x38];
} ModelSlot;

typedef struct LookActor {
    /*0x000*/ u8 unk0[0x174];
    /*0x174*/ u16 headJoint;
    /*0x176*/ u8 unk176[0x255 - 0x176];
    /*0x255*/ s8 modelIdx;
    /*0x256*/ u8 unk256[0x27C - 0x256];
} LookActor;

// lbl_8036E548 (size 0x3154), only the fields used here.
typedef struct ActorManager {
    /*0x0000*/ u8 unk0[0x60];
    /*0x0060*/ ModelSlot* modelSlots;
    /*0x0064*/ u8 unk64[0xC04 - 0x64];
    /*0x0C04*/ LookActor actors[13];
    /*0x2C50*/ LookActor* actorOverride[13];
} ActorManager;

void fn_80026134(s32 idx, Vec* target);

#endif
