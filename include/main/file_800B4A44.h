#ifndef __MAIN_FILE_800B4A44_H__
#define __MAIN_FILE_800B4A44_H__

#include "mssbTypes.h"
#include "C3/unktypes.h"
#include "C3/anim.h"
#include "C3/actor.h"
#include "main/file_80063028.h"

// MSSB's animation pipe (layout differs from the SDK ANIMPipe in C3/anim.h).
typedef struct GameAnimPipe {
    /*0x00*/ f32 time;
    /*0x04*/ f32 prevTime;
    /*0x08*/ f32 speed;
    /*0x0C*/ struct ANIMAnimTrack* currentTrack;
    /*0x10*/ Control* control;
    /*0x14*/ u16 frameIndex;
    /*0x16*/ u8 replaceHierarchyCtrl;
    /*0x17*/ u8 forward; // 1: time runs forward, else backward
    /*0x18*/ u8 loop;
    /*0x19*/ u8 pad19[0x3];
} GameAnimPipe;

f32 fn_800B4A44(GameActor* actor, u16 boneIndex);
f32 fn_800B4A94(GameActor* actor);
void fn_800B4AFC(GameActor* actor, u8 loop);
void AnimateActorBones(GameActor* actor);
void fn_800B4BC8(GameActor* actor, u8 forward);
void fn_800B4C04(GameActor* actor, f32 speed);
f32 fn_800B4C40(GameActor* actor);
void fn_800B4CA0(GameActor* actor, f32 time);
void fn_800B4CDC(GameActor* actor);

#endif
