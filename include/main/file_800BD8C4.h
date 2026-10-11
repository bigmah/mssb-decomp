#ifndef __MAIN_FILE_800BD8C4_H__
#define __MAIN_FILE_800BD8C4_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Game-side actor instance (partial; compare C3 Actor).
typedef struct ActorInst {
    /* 0x00 */ u8 pad0[0x18];
    /* 0x18 */ struct sBone** boneArray;
    /* 0x1C */ u8 worldControl[0x44];
    /* 0x60 */ u8 pad60[0x38];
    /* 0x98 */ u8 flags98;  // low 2 bits = fn_800B3C04 result
    /* 0x99 */ u8 unk99;
} ActorInst;

typedef void (*ActorObjectCallback)(void);

// One 0x90-byte slot of an ActorObjectTable.
typedef struct ActorObject {
    /* 0x00 */ ActorInst* actor;
    /* 0x04 */ void* animBank;
    /* 0x08 */ ActorObjectCallback callback;
    /* 0x0C */ u16 id;
    /* 0x0E */ u16 seqNum;
    /* 0x10 */ u8 worldControl[0x44];  // copied to actor->worldControl
    /* 0x54 */ f32 unk54;               // passed to fn_800B4C04
    /* 0x58 */ u8 setAnimation;
    /* 0x59 */ u8 setTime;
    /* 0x5A */ u8 setSpeed;
    /* 0x5B */ u8 visFlags;             // bit1 = apply, bit0 = value
    /* 0x5C */ f32 time;
    /* 0x60 */ f32 speed;
    /* 0x64 */ u16 unk64;
    /* 0x66 */ u16 unk66;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ u8 animateBones;
    /* 0x6D */ u8 numLights;
    /* 0x6E */ u8 pad6E[2];
    /* 0x70 */ void* lights[8];      // passed to fn_800B3A78 (ACTRender-like)
} ActorObject;

typedef struct ActorObjectTable {
    /* 0x00 */ u16 count;
    /* 0x04 */ Mtx mtx;
    /* 0x34 */ ActorObject objects[1];  // count entries
} ActorObjectTable;

void fn_800BD8C4(ActorObjectTable* table, s32 arg1);
void fn_800BDA24(ActorObject* obj);
void fn_800BDA94(ActorObject* obj, MtxPtr camera);
void fn_800BDC88(ActorObjectTable* table, u16 index, u16 id, void* layout, void* animBank, s32 arg5);
ActorObjectTable* ActorObjectInitTable(u16 count);
void fn_800BDE8C(u32 value);

#endif
