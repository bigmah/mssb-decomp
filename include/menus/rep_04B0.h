#ifndef __MENUS_REP_04B0_H_
#define __MENUS_REP_04B0_H_

#include "mssbTypes.h"

// Team/captain select screen: player join, captain cursor, menu camera.

struct PortInput;

void fn_2_14574(struct PortInput* in);
void fn_2_14790(void);
void fn_2_14BB8(u8 index, s32 mode);
void fn_2_14CA0(u8 player, struct PortInput* in);
void fn_2_14FB8(s32 player);
void fn_2_150D0(u8 index);
s32 fn_2_15104(s32 cur, s32 prev, u8 index, u8 value);
void fn_2_151BC(u8 player);
void fn_2_1560C(u8 player);
void fn_2_15A90(s32* value, u8 port, s32 max);
void fn_2_15AFC(s32 port, s32 held, s32 pressed, u16 repeat);
void fn_2_15E80(u8 port);
void fn_2_1641C(void);
void fn_2_16460(void);
void fn_2_16664(void);
void fn_2_166CC(void);
void fn_2_16724(void);

#endif
