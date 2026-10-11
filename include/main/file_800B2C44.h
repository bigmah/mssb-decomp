#ifndef __MAIN_FILE_800B2C44_H__
#define __MAIN_FILE_800B2C44_H__

#include "mssbTypes.h"
#include "stdarg.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "main/file_800B4A44.h"
#include "C3/geoPalette.h"
#include "C3/skinning.h"

// Static (non-animated) model drawn by fn_800B472C.
typedef struct StaticModel {
    /*0x00*/ u8 pad00[0x8];
    /*0x08*/ Mtx world;
    /*0x38*/ Mtx camera;
    /*0x68*/ ActorLayout* layout;
} StaticModel;

void fn_800B2C44(GameActor* actor, u16 bone, Vec* pos);
void fn_800B2C88(GameActor* actor, u16 bone, Mtx m);
void ACTSort(GameActor* actor);
void fn_800B2D5C(GameActor* actor);
void fn_800B2DD0(GameActor* actor, GameBone* bone);
void fn_800B313C(GameActor* actor);
void fn_800B34B4(GameActor* actor, GameBone* bone, Mtx world);
void f_BuildBoneSkinOrientationMatrix(GameBone* bone, Mtx parent);
void fn_800B3A78(GameActor* actor, Mtx camera, u8 numLights, ...);
u8 fn_800B3C04(s32 viewIndex, GameActor* actor, Mtx camera);
void fn_800B3F20(GameActor* actor);
s32 fn_800B4048(GameActor** actor, ActorLayout* layout, u16 actorID);
void fn_800B4084(GameBone* parent, ActorBone* layoutBone, GameActor* actor, u16* boneIndex, GameBone* boneMem);
void fn_800B4278(GameActor* actor);
GameActor* fn_800B43A0(ActorLayout* layout);
void fn_800B4724(GameActor* actor, sHdr* skHeader);
void fn_800B472C(StaticModel* model);
void haveActLayoutPointToGeoHeader(ActorLayout* layout, DODisplayData* geoPalette);
void LoadActorLayout(ActorLayout* layout);
void fn_800B49E4(ActorLayout* layout);

#endif
