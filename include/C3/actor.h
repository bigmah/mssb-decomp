#ifndef _DOLPHIN_CP_ACTOR_H_
#define _DOLPHIN_CP_ACTOR_H_

#include "C3/control.h"
#include "charPipeline/structures/Tree.h"
#include "charPipeline/structures/List.h"

struct GameActor;
struct GameBone;
struct ANIMAnimTrack;

typedef struct DODisplayData *DODisplayDataPtr;
typedef struct sBone sBone;
typedef struct sHdr sHdr;
typedef struct ANIMBank ANIMBank;

typedef struct ActorLayout {
    /* 0x00 */ u32 versionNumber;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ union {
        char * geoPaletteName;
        DODisplayDataPtr geoPalette; // MSSB: set by haveActLayoutPointToGeoHeader
    };
    /* 0x14 */ u16 skinFileID;
    /* 0x16 */ u16 pad16;
    /* 0x18 */ u32 userDataSize;
    /* 0x1C */ char * userData;
} ActorLayout;

typedef struct ActorBone {
    /* 0x00 */ Control * orientationCtrl;
    /* 0x04 */ DSBranch branch;
    /* 0x14 */ u16 geoFileID;
    /* 0x16 */ u16 boneID;
    /* 0x18 */ u8 inheritanceFlag;
    /* 0x19 */ u8 drawingPriority;
    /* 0x1A */ u16 flags; // MSSB: static-layout render flags (bit 0 z-always, bits 1-2 blend mode)
} ActorBone;

// An actor layout file: the header followed by its bone array.
typedef struct ActorLayoutFile {
    /* 0x00 */ ActorLayout header;
    /* 0x20 */ ActorBone bones[1]; // really header.totalBones entries
} ActorLayoutFile;

typedef struct {
    /* 0x00 */ ActorLayout *layout;
    /* 0x04 */ u16 actorID;
    /* 0x06 */ u16 totalBones;
    /* 0x08 */ DSTree hierarchy;
    /* 0x10 */ DODisplayDataPtr pal;
    /* 0x14 */ struct DODisplayObj *skinObject;
    /* 0x18 */ sBone **boneArray;
    /* 0x1C */ Control worldControl;
    /* 0x50 */ MtxPtr forwardMtxArray;
    /* 0x54 */ MtxPtr skinMtxArray;
    /* 0x58 */ MtxPtr skinInvTransposeMtxArray;
    /* 0x5C */ MtxPtr orientationInvMtxArray;
    /* 0x60 */ DSList drawPriorityList;
    /* 0x6C */ sHdr * skHeader;
} Actor;

// actor.c
void ACTGet(Actor **actor, char *name);
void ACTRelease(Actor **actor);
void ACTRender(Actor *actor, MtxPtr camera, u8 numLights, ...);
void ACTHide(Actor *actor);
void ACTShow(Actor *actor);
void ACTBuildMatrices(Actor *actor);
Control *ACTGetControl(Actor *actor);
void ACTSetInheritance(Actor *actor, u8 inheritanceFlag);
void ACTSetAmbientPercentage(Actor *actor, f32 percent);
void ACTSort(struct GameActor *actor);
void ACTSetEffectsShader(Actor *actor, char *shaderFunc, char *data);
u32 ACTGetUserDataSize(Actor *actor);
char *ACTGetUserData(Actor *actor);

// actorAnim.c
void ACTSetAnimation(struct GameActor *actor, ANIMBank *animBank, char *sequenceName, u16 seqNum, f32 time, f32 blendSpeed);
void ACTSetTime(Actor *actor, f32 time);
void ACTSetSpeed(Actor *actor, f32 speed);
void ACTTick(Actor *actor);

// boneAnim.c
void ACTSetBoneTime(sBone *bone, f32 time);
void ACTSetBoneSpeed(sBone *bone, f32 speed);
void ACTTickBone(sBone *bone);
// MSSB signature: bone is a GameBone (main/file_80063028.h); blend keeps the previous pose in blendCtrl.
void ACTSetBoneTrack(struct GameBone *bone, struct ANIMAnimTrack *track, f32 time, s32 blend);

#endif // _DOLPHIN_CP_ACTOR_H_
