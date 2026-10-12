#ifndef __AUTO_00_00092394_TEXT_MENUS_H__
#define __AUTO_00_00092394_TEXT_MENUS_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"

void fn_2_923CC(struct MenuObject* object);

void fn_2_923D8(struct MenuObject* object);

void fn_2_924A4(struct MenuObject* object);

void fn_2_92394(struct MenuObject* object);

void fn_2_9246C(struct MenuObject* object);

void fn_2_92504(struct MenuObject* object);

void fn_2_9253C(struct MenuObject* object);

void fn_2_9257C(void);

void fn_2_92654(s32 index, u8 state);

void fn_2_924B0(struct MenuObject* object);

void fn_2_9267C(Vec* result, Vec* position, Vec* anchor, Vec* target,
               f32 step, f32 spring, f32 damping, f32 restDistance);

#endif
