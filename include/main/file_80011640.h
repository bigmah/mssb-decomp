#ifndef __MAIN_FILE_80011640_H__
#define __MAIN_FILE_80011640_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"
#include "main/file_80024D2C.h"

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
    /*0x1C*/ u8 _1C[0x98 - 0x1C];
    /*0x98*/ u8 flags;
} CharModel;

// One loaded model and its root control.
typedef struct CharSlot {
    /*0x00*/ CharModel* model;
    /*0x04*/ u8 _04[0xC];
    /*0x10*/ Control ctrl;
    /*0x4C*/ u8 _4C[0x68 - 0x10 - sizeof(Control)];
    /*0x68*/ void* _68;
    /*0x6C*/ u8 _6C;
    /*0x6D*/ u8 _6D[0x90 - 0x6D];
} CharSlot; // size: 0x90

typedef struct CharSlotList {
    /*0x00*/ u16 count;
    /*0x02*/ u8 _02[0x32];
    /*0x34*/ CharSlot slots[1];
} CharSlotList;

// Character parts data: a file table plus a shape animation player.
typedef struct CharPart {
    /*0x00*/ void** files;
    /*0x04*/ ShapeAnimPlayer player; // player.curIdx at 0x5C
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
    /*0x034*/ u8 _034[0x60 - 0x34];
    // Animation requests: [0] current, [1] next (AnimateCharacter),
    // [2] queued (QueueCharacterAnimation).
    /*0x060*/ s16 _060;
    /*0x062*/ s16 anim[3];
    /*0x068*/ s16 _068;
    /*0x06A*/ s16 _06A[3];
    /*0x070*/ u8 _070[0x2];
    /*0x072*/ u8 _072[0x254 - 0x72];
    /*0x254*/ s8 index;
    /*0x255*/ s8 modelIndex;
    /*0x256*/ u8 _256[0x6];
    /*0x25C*/ u8 _25C;
    /*0x25D*/ u8 mode[2];
    /*0x25F*/ u8 _25F[3];
    /*0x262*/ u8 _262[3];
    /*0x265*/ u8 _265[3];
    /*0x268*/ u8 _268;
    /*0x269*/ u8 _269[3];
    /*0x26C*/ u8 _26C[3];
    /*0x26F*/ u8 _26F;
    /*0x270*/ u8 _270[0x27C - 0x270];
} CharActor; // size: 0x27C

// lbl_8036E548
typedef struct CharMgr {
    /*0x0000*/ u8 _0000[0x60];
    /*0x0060*/ CharSlotList* slots;
    /*0x0064*/ CharSlotList* slots64;
    /*0x0068*/ CharSlotList* slots68;
    /*0x006C*/ u8 _006C[0x13C - 0x6C];
    /*0x013C*/ CharSlotList* partSlots;
    /*0x0140*/ CharParts partsPool[13];
    /*0x0C04*/ CharActor actors[13];
    /*0x2C50*/ CharActor* active[13];
    /*0x2C84*/ u8 _2C84[0x4];
    /*0x2C88*/ void* _2C88;
    /*0x2C8C*/ u8 _2C8C[0x2D68 - 0x2C8C];
    /*0x2D68*/ s16 _2D68;
    /*0x2D6A*/ s8 _2D6A[13];
    /*0x2D77*/ u8 state;
    /*0x2D78*/ u8 _2D78[0x3082 - 0x2D78];
    /*0x3082*/ u8 _3082;
    /*0x3083*/ u8 _3083[0x308C - 0x3083];
    /*0x308C*/ void (*callback)(void);
    /*0x3090*/ u8 _3090[0x3154 - 0x3090];
} CharMgr; // size: 0x3154

extern CharMgr lbl_8036E548;
extern CharActor lbl_8036C4FC[13]; // backup of lbl_8036E548.actors

// Object handed to fn_8001FDD4 (the fn_80017814 load callback).
typedef struct CharLoadObj {
    /*0x00*/ u8 _00[0x70];
    /*0x70*/ void* _70;
} CharLoadObj;

// Task object (lbl_803CC1B8) running fn_800177B4.
typedef struct CharLoadTask {
    /*0x00*/ u8 _00[0x14];
    /*0x14*/ u8 state;
    /*0x15*/ u8 index;
    /*0x16*/ u8 kind;
    /*0x17*/ u8 _17[0x2];
    /*0x19*/ u8 team;
    /*0x1A*/ u8 roster;
    /*0x1B*/ s8 _1B;
    /*0x1C*/ u8 actor;
    /*0x1D*/ u8 _1D;
} CharLoadTask;

// Drawing-queue task returned by fn_800B0A5C_insertQueue.
typedef struct CharQueueTask {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ struct CharQueueTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u8 _12[0x2];
    /*0x14*/ u8 _14;
} CharQueueTask;

void fn_80011640(Mtx a, Mtx out);
void fn_800116DC(CharActor* actor, Mtx m, u16 joint);
void fn_800117CC(Mtx src, Mtx m, Mtx dst);
MtxPtr fn_800118AC(Mtx m, Mtx out);
void fn_8001196C(void);
void fn_80011A60(void);
void fn_80011B64(s32 index);
void fn_80011BE4(s32 index);

void fn_8001AAF0(void);
void fn_800189B8(void);
void fn_8001FDD4(CharLoadObj* obj);
void fn_8001B2D0(void);
void fn_8001D110(s32 index, f32 x, f32 y, f32 z);
void fn_8001D148(s32 index, f32 x, f32 y, f32 z);
void fn_80018B38(void);
void fn_8001D0D0(s32 index, f32 scale);
void fn_8001AAA4(void);
void fn_8001B308(s32 index, s32 enable);
void fn_8001D074(s32 index, s32 enable);
void fn_800177B4(void);
void fn_8001C528(void);
void QueueCharacterAnimation(s32 index, s32 anim, s32 a, s32 b, s32 c, s32 d, s32 e);
void AnimateCharacter(s32 index, s32 anim, s32 a, u8 mode, s32 b, s32 c, s32 d, s32 e);
s32 fn_8001758C(u8* state, s32 actor, u8 kind, u8 team, u8 roster, s8 arg5, u8 index, u8 arg7);
void challengeMapRelated(void);

void fn_8001B200(void);

void fn_8001B214(void (*callback)(void));

void fn_8001E460(void* value);

void fn_8001E474(void);

#endif
