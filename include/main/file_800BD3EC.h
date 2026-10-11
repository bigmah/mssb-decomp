#ifndef __MAIN_FILE_800BD3EC_H__
#define __MAIN_FILE_800BD3EC_H__

#include "mssbTypes.h"
#include "C3/charPipeline.h"
#include "main/file_800BD8C4.h" // ActorObject


void LITAlloc(Light** light);
void fn_800BD478(GameActor** actor, ActorLayoutFile* layout);
void fn_800BD548(ActorObject* obj, u8 numLights, ...);
void fn_800BD670(ActorObjectTable* table, MtxPtr camera);

#endif
