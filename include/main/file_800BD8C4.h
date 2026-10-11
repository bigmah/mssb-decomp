#ifndef __MAIN_FILE_800BD8C4_H__
#define __MAIN_FILE_800BD8C4_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80063028.h" // GameActor, GameControl

struct sHdr;
struct ActorLayout;
struct ActorObject;

// Called before an object is drawn (fn_800BDA94).
typedef void (*ActorObjectCallback)(struct ActorObject* obj);

// One 0x90-byte slot of an ActorObjectTable: an actor, its animation request
// and the lights passed to its render call (fn_800B3A78).
typedef struct ActorObject {
    /* 0x00 */ GameActor* actor;
    /* 0x04 */ void* animBank;
    /* 0x08 */ ActorObjectCallback callback;
    /* 0x0C */ u16 id;
    /* 0x0E */ u16 seqNum;
    /* 0x10 */ GameControl worldControl; // copied to actor->worldControl
    /* 0x54 */ f32 unk54;                // passed to fn_800B4C04
    /* 0x58 */ u8 setAnimation;
    /* 0x59 */ u8 setTime;
    /* 0x5A */ u8 setSpeed;
    /* 0x5B */ u8 visFlags;              // bit1 = apply, bit0 = value
    /* 0x5C */ f32 time;
    /* 0x60 */ f32 speed;
    /* 0x64 */ u16 unk64;                // fn_800B2BFC bone A
    /* 0x66 */ u16 unk66;                // fn_800B2BFC bone B
    /* 0x68 */ u16* boneRemap;           // Set_FUN_800b2b6c
    /* 0x6C */ u8 animateBones;          // also "visible" for fn_800BD670
    /* 0x6D */ u8 numLights;
    /* 0x6E */ u8 pad6E[2];
    /* 0x70 */ void* lights[8];          // passed to fn_800B3A78 (ACTRender-like)
} ActorObject; // size: 0x90

typedef struct ActorObjectTable {
    /* 0x00 */ u16 count;
    /* 0x04 */ Mtx mtx;
    /* 0x34 */ ActorObject objects[1];  // count entries
} ActorObjectTable;

void fn_800BD8C4(ActorObjectTable* table, MtxPtr camera);
void fn_800BDA24(ActorObject* obj);
void fn_800BDA94(ActorObject* obj, MtxPtr camera);
void fn_800BDC88(ActorObjectTable* table, u16 index, u16 id, struct ActorLayout* layout, void* animBank, struct sHdr* skHeader);
ActorObjectTable* ActorObjectInitTable(u16 count);
void fn_800BDE8C(u32 value);

#endif
