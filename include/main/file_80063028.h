#ifndef __MAIN_FILE_80063028_H__
#define __MAIN_FILE_80063028_H__

#include "mssbTypes.h"
#include "C3/control.h"
#include "charPipeline/structures/Tree.h"
#include "charPipeline/structures/List.h"

struct DODisplayObj;
struct DODisplayData;
struct sHdr;
struct GameAnimPipe;
struct ActorLayout;

// MSSB's Control is 0x44 bytes (C3/control.h's Control is 0x3C).
typedef struct GameControl {
    /*0x00*/ Control base;
    /*0x3C*/ u8 pad3C[0x8];
} GameControl;

// MSSB's actor bone (layout differs from the SDK sBone in C3/skinning.h).
typedef struct GameBone {
    /*0x000*/ u16 boneID;
    /*0x002*/ u8 inheritanceFlag;
    /*0x003*/ u8 drawingPriority;
    /*0x004*/ DSBranch branch;
    /*0x014*/ struct DODisplayObj* dispObj;
    /*0x018*/ struct DODisplayObj* baseDispObj;
    /*0x01C*/ GameControl orientationCtrl;
    /*0x060*/ Control animCtrl;
    /*0x09C*/ u8 pad9C[0x8];
    /*0x0A4*/ Control blendCtrl;
    /*0x0E0*/ u8 padE0[0x8];
    /*0x0E8*/ struct GameAnimPipe* animPipe;
    /*0x0EC*/ MtxPtr forwardMtx;
    /*0x0F0*/ MtxPtr skinMtx;
    /*0x0F4*/ MtxPtr skinInvTransposeMtx;
    /*0x0F8*/ MtxPtr orientationInvMtx;
    /*0x0FC*/ DSLink drawPriorityLink;
    /*0x104*/ u8 pad104[0x30];
    /*0x134*/ u16 flags; // bits 0-1 blend curve, 2-4 copy anim translation x/y/z, 5 copy enabled
    /*0x136*/ u8 unk136;
    /*0x137*/ u8 rotAxis; // 1/2/3: extra 180 degree turn about X/Y/Z
    /*0x138*/ u8 pad138[0x8];
} GameBone; // size: 0x140

// Per-bone matrix override; returns nonzero when it built the matrix itself.
typedef s32 (*GameBoneCallback)(GameBone* bone, GameBone* target, Mtx m, f32 t);

// MSSB's actor (layout differs from the SDK Actor in C3/actor.h).
typedef struct GameActor {
    /*0x00*/ struct ActorLayout* layout;
    /*0x04*/ u16 actorID;
    /*0x06*/ u16 totalBones;
    /*0x08*/ DSTree hierarchy;
    /*0x10*/ struct DODisplayData* pal;
    /*0x14*/ struct DODisplayObj* skinObject;
    /*0x18*/ GameBone** boneArray;
    /*0x1C*/ GameControl worldControl;
    /*0x60*/ MtxPtr forwardMtxArray;
    /*0x64*/ MtxPtr skinMtxArray;
    /*0x68*/ MtxPtr skinInvTransposeMtxArray;
    /*0x6C*/ MtxPtr orientationInvMtxArray;
    /*0x70*/ DSList drawPriorityList;
    /*0x7C*/ struct sHdr* skHeader;
    /*0x80*/ u16 footBoneA;
    /*0x82*/ u16 footBoneB;
    /*0x84*/ u16 rootBone;
    /*0x86*/ u8 pad86[0x2];
    /*0x88*/ u16* boneRemap; // per-bone index of the bone whose animation drives it
    /*0x8C*/ f32 blend;
    /*0x90*/ f32 blendSpeed;
    /*0x94*/ GameBoneCallback boneCallback;
    /*0x98*/ u8 flags;
    /*0x99*/ u8 tickFlag;
    /*0x9A*/ u8 pad9A[0x6];
} GameActor; // size: 0xA0

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
