#ifndef __MAIN_FILE_800B4A44_H__
#define __MAIN_FILE_800B4A44_H__

#include "mssbTypes.h"
#include "C3/unktypes.h"
#include "C3/anim.h"
#include "C3/actor.h"
#include "main/file_80063028.h"

// GameBone::animPipe is a struct ANIMPipe (MSSB layout, C3/anim.h).

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
