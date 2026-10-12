#ifndef __REP_0F60_MENUS_H__
#define __REP_0F60_MENUS_H__

#include "mssbTypes.h"
#include "menus/menu_asset.h"
#include "main/file_80024D2C.h"
#include "Dolphin/mtx.h"

#include "main/file_800BD8C4.h" // ActorObject

void fn_2_8D24C(ActorObject* object);

void fn_2_8B118(f32 value);

s32 fn_2_8CC88(s32 index);

void fn_2_8CCAC(s32 index, u8 value);

void fn_2_8CCCC(s32 index, s32 a, s32 b, u8 mode, s32 c, s32 d, s32 e, s32 f);

void fn_2_8DC00(void);

void fn_2_8C724(void);

void fn_2_8DB14(void);

void fn_2_8C80C(s32 res, s32 first, s32 count, void* anim, void* skin);

void fn_2_8D9DC(s32 mode);

void fn_2_8B2C0(void);

void fn_2_8E478(void);

void fn_2_8DCD8(void);

void fn_2_8CD58(s32 index, s32 anim, u8 loop, u8 face, s16 time, u8 eyes, u8 frames);

void fn_2_8C910(void);

void fn_2_8DFB0(void);

void fn_2_8B158(void);

void fn_2_8D270(u8 index);

void fn_2_8B418(void);

void fn_2_8E6A4(void);
void fn_2_8E8A4(void);
void fn_2_8EA80(void);

#endif
