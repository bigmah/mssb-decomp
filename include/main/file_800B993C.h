#ifndef __MAIN_FILE_800B993C_H__
#define __MAIN_FILE_800B993C_H__

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

struct DODisplayObj;

// Final user TEV hook run by the display-object renderer (main/file_800B9974.c).
typedef void (*DOTevHook)(struct DODisplayObj* dispObj, s32* stage, s32* coord, s32* map, u8* numTevStages,
                          u8* numTexGens, MtxPtr camera);
// Extra TEV pass after fn_800B9AB0.
typedef void (*DOTevPass)(s32 stage, s32 a, s32 b, s32 coord, s32 map);

extern DOTevHook lbl_803CC200;
extern DOTevPass lbl_803CC1F4;

void fn_800B993C(void);

void fn_800B9948(DOTevHook hook);

void fn_800B996C(DOTevPass pass);

void fn_800B9950(u32 mask, f32 first, f32 second);

#endif
