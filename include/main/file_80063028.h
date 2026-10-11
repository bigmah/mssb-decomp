#ifndef __MAIN_FILE_80063028_H__
#define __MAIN_FILE_80063028_H__

#include "mssbTypes.h"
#include "C3/control.h"
#include "charPipeline/structures/List.h"

// MSSB's Control is 0x44 bytes (C3/control.h's Control is 0x3C).
typedef struct GameControl {
    /*0x00*/ Control base;
    /*0x3C*/ u8 pad3C[0x8];
} GameControl;

// MSSB's actor bone (layout differs from the SDK sBone in C3/skinning.h).
typedef struct GameBone {
    /*0x00*/ u16 boneID;
    /*0x02*/ u8 pad02[0x12];
    /*0x14*/ struct DODisplayObj* dispObj;
    /*0x18*/ struct DODisplayObj* defaultDispObj;
    /*0x1C*/ u8 pad1C[0x44];
    /*0x60*/ Control animCtrl;
    /*0x9C*/ u8 pad9C[0x8];
    /*0xA4*/ Control blendCtrl;
    /*0xE0*/ u8 padE0[0x54];
    /*0x134*/ u16 unk134;
    /*0x136*/ u8 unk136;
} GameBone;

// Per-bone matrix override; returns nonzero when it built the matrix itself.
typedef s32 (*GameBoneCallback)(GameBone* bone, GameBone* target, Mtx m, f32 t);

// MSSB's actor (layout differs from the SDK Actor in C3/actor.h).
typedef struct GameActor {
    /*0x00*/ u8 pad00[0x18];
    /*0x18*/ GameBone** boneArray;
    /*0x1C*/ u8 pad1C[0x44];
    /*0x60*/ Mtx* mtxArray;
    /*0x64*/ u8 pad64[0xC];
    /*0x70*/ DSList drawPriorityList;
    /*0x7C*/ u8 pad7C[0x4];
    /*0x80*/ s16 unk80;
    /*0x82*/ s16 unk82;
    /*0x84*/ s16 unk84;
    /*0x86*/ u8 pad86[0x2];
    /*0x88*/ s32 unk88;
    /*0x8C*/ u8 pad8C[0x4];
    /*0x90*/ f32 unk90;
    /*0x94*/ GameBoneCallback boneCallback;
} GameActor;

typedef struct PlayerVecSlot {
    /*0x00*/ Vec a;
    /*0x0C*/ Vec b;
    /*0x18*/ s32 unk18;
    /*0x1C*/ u8 unk1C;
    /*0x1D*/ u8 pad1D[3];
} PlayerVecSlot;

extern PlayerVecSlot lbl_802E4BC0[9];

void fn_80063028(Control* control, Mtx m, u32 flipFlags);
void fn_800633AC(Control* control, Mtx m, u32 flipFlags);
s32 fn_80063718(GameBone* bone, GameBone* target, Mtx m, f32 t);
s32 fn_800637BC(void* player, GameActor** actor);
s32 fn_800637D4(void);
s32 fn_800637DC(GameBone* bone, GameBone* target, Mtx m, f32 t);
s32 fn_800638B4(void* player, GameActor** actor);
void fn_800638CC(void);
void fn_80063958(s8 index);

#endif
