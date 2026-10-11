#ifndef __MAIN_FILE_80022DAC_H__
#define __MAIN_FILE_80022DAC_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtx.h"
#include "C3/actor.h"
#include "C3/geoPalette.h"

typedef struct VecQueue {
    Vec* entries;
    s32 capacity;
    s32 count;
    s32 head;
    s32 tail;
    s32 cursor;
    s32 step;
} VecQueue;

// Actor/bone/display object setup ("objinit.c"): MSSB's variant of the
// Dolphin SDK character pipeline structures in C3/.

// Bone orientation control. MSSB's is 8 bytes bigger than the SDK Control.
typedef struct MControl {
    /* 0x00 */ Control ctrl;
    /* 0x3C */ u8 unk3C[8];
} MControl; // size: 0x44

// Display object layout in a geometry palette (SDK DODisplayLayout plus colors).
typedef struct MDisplayLayout {
    /* 0x00 */ PositionData* positionData;
    /* 0x04 */ ColorData* colorData;
    /* 0x08 */ TextureData* textureData;
    /* 0x0C */ LightingData* lightingData;
    /* 0x10 */ DisplayData* displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ u32 unk18;
    /* 0x1C */ GXColor colors[6];
} MDisplayLayout;

typedef struct MDisplayObj {
    /* 0x00 */ PositionData* positionData;
    /* 0x04 */ ColorData* colorData;
    /* 0x08 */ TextureData* textureData;
    /* 0x0C */ LightingData* lightingData;
    /* 0x10 */ DisplayData* displayData;
    /* 0x14 */ u8 numTextureChannels;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 visibility;
    /* 0x17 */ u8 pad17;
    /* 0x18 */ Mtx worldMatrix;
    /* 0x48 */ u32 unk48;
    /* 0x4C */ void* shaderFunc;
    /* 0x50 */ void* shaderData;
    /* 0x54 */ GXColor colors[6];
    /* 0x6C */ u8 unk6C[0x14];
} MDisplayObj; // size: 0x80 (allocated as 0x80 bytes followed by the copied headers)

// Layout of one bone in an actor layout (SDK ActorBone with an MSSB control).
typedef struct MBoneLayout {
    /* 0x00 */ MControl* orientationCtrl;
    /* 0x04 */ DSBranch branch; // Next sibling at 0x8, Children at 0x10
    /* 0x14 */ u16 geoFileID;
    /* 0x16 */ u16 boneID;
    /* 0x18 */ u8 inheritanceFlag;
    /* 0x19 */ u8 drawingPriority;
    /* 0x1A */ u16 pad16;
} MBoneLayout;

typedef struct MActorLayout {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ u32 hierarchyOffset;
    /* 0x0C */ MBoneLayout* hierarchyRoot;
    /* 0x10 */ DODisplayData* pal;
    /* 0x14 */ u16 skinFileID; // 0xFFFF: no skin
    /* 0x16 */ u16 pad16;
} MActorLayout;

// Per-bone animation state, 0x20 bytes allocated after the display objects.
typedef struct MBoneAnim {
    /* 0x00 */ f32 time;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 speed;
    /* 0x0C */ void* track;
    /* 0x10 */ void* unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
} MBoneAnim;

typedef struct MBone {
    /* 0x000 */ u16 boneID;
    /* 0x002 */ u8 inheritanceFlag;
    /* 0x003 */ u8 drawingPriority;
    /* 0x004 */ DSBranch branch; // Next sibling at 0x8, Children at 0x10
    /* 0x014 */ MDisplayObj* dispObj;
    /* 0x018 */ MDisplayObj* drawObj;
    /* 0x01C */ MControl orientationCtrl;
    /* 0x060 */ u8 unk60;
    /* 0x061 */ u8 unk61[0x43];
    /* 0x0A4 */ u8 unkA4;
    /* 0x0A5 */ u8 unkA5[0x43];
    /* 0x0E8 */ MBoneAnim* anim;
    /* 0x0EC */ MtxPtr forwardMtx;
    /* 0x0F0 */ MtxPtr skinMtx;
    /* 0x0F4 */ MtxPtr skinInvTransposeMtx;
    /* 0x0F8 */ MtxPtr orientationInvMtx;
    /* 0x0FC */ DSLink drawPriorityLink;
    /* 0x104 */ u8 unk104[0x30];
    /* 0x134 */ u16 unk134;
    /* 0x136 */ u8 unk136;
    /* 0x137 */ u8 unk137;
    /* 0x138 */ u8 unk138[8];
} MBone; // size: 0x140

typedef struct MActor {
    /* 0x00 */ MActorLayout* layout;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ DODisplayData* pal;
    /* 0x14 */ MDisplayObj* skinObject;
    /* 0x18 */ MBone** boneArray;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D[0x43];
    /* 0x60 */ Mtx* forwardMtxArray;
    /* 0x64 */ Mtx* skinMtxArray;
    /* 0x68 */ Mtx* skinInvTransposeMtxArray;
    /* 0x6C */ Mtx* orientationInvMtxArray;
    /* 0x70 */ DSList drawPriorityList;
    /* 0x7C */ u32 unk7C;
    /* 0x80 */ u16 unk80;
    /* 0x82 */ u16 unk82;
    /* 0x84 */ u16 unk84;
    /* 0x88 */ u32 unk88;
    /* 0x8C */ f32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u32 unk94;
    /* 0x98 */ u8 unk98;
    /* 0x99 */ u8 unk99;
    /* 0x9A */ u8 unk9A[6];
} MActor; // size: 0xA0, followed by the bone/matrix arrays

// One actor slot in an ActorObjectInitTable() table.
typedef struct ActorSlot {
    /* 0x00 */ MActor* actor;
    /* 0x04 */ u32 anim;
    /* 0x08 */ u32 unk8;
    /* 0x0C */ s16 id;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8 unk10[0x44];
    /* 0x54 */ f32 speed;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 unk5A;
    /* 0x5B */ u8 unk5B[5];
    /* 0x60 */ f32 unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ u32 unk68;
    /* 0x6C */ u8 unk6C;
    /* 0x6D */ u8 unk6D;
    /* 0x6E */ u8 unk6E[2];
    /* 0x70 */ u32 unk70[8];
} ActorSlot; // size: 0x90

typedef struct ActorSlotTable {
    /* 0x00 */ u16 count;
    /* 0x04 */ Mtx mtx;
    /* 0x34 */ ActorSlot slots[1]; // [count]
} ActorSlotTable;

// Stadium light placement (lbl_800F7478 rows).
typedef struct StadiumLight {
    /* 0x0 */ u16 height;
    /* 0x2 */ u16 yaw;
    /* 0x4 */ u16 pitch;
    /* 0x6 */ u8 r;
    /* 0x7 */ u8 g;
    /* 0x8 */ u8 b;
} StadiumLight; // size: 0xA

typedef struct StadiumLightPos {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
    /* 0xC */ u8 r;
    /* 0xD */ u8 g;
    /* 0xE */ u8 b;
    /* 0xF */ u8 a;
} StadiumLightPos;

// GX texture image as used by fn_80023F0C.
typedef struct TexImage {
    /* 0x00 */ u8* data;
    /* 0x04 */ void* tlut;
    /* 0x08 */ u16 height;
    /* 0x0A */ u16 width;
    /* 0x0C */ u8 unkC[0xB];
    /* 0x17 */ u8 format;
} TexImage;

u8* fn_80023078(MDisplayObj* dispObj, MDisplayLayout* layout, u8* buffer);

void fn_80023EEC(VecQueue* queue, Vec* entries, s32 capacity);

s32 fn_80023D4C(VecQueue* queue, Vec* result);

s32 fn_80023DFC(VecQueue* queue, Vec* result);

void fn_80023E48(VecQueue* queue, Vec* value);

u32 fn_80023D3C(void);

void fn_80023D44(u32 value);

s32 fn_80023D98(VecQueue* queue, Vec* result);

#endif
