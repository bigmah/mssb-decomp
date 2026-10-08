#ifndef __MENUS_REP_0B08_H__
#define __MENUS_REP_0B08_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"

typedef struct {
    u8 padding[0x80];
    s32 index;
    u8 padding84[8];
    f32 progress;
    u8 padding90[4];
    s16 state;
} MenuFadeState;

void fn_2_71A38(u8* object);

void fn_2_70588(u8* object);

void fn_2_704A0(u8* object);

void fn_2_70494(u8* object);

void fn_2_7045C(u8* object);

void fn_2_6FE34(u8* object);

void fn_2_6F6F4(u8* object);

void fn_2_6E880(u8* object);

void fn_2_6E848(u8* object);

void fn_2_6D840(u8* object);

void fn_2_6D748(u8* object);

void fn_2_6D710(u8* object);

void fn_2_6D4E8(u8* object);

void fn_2_6D4B0(u8* object);

void fn_2_6D288(u8* object);

void fn_2_6D250(u8* object);

void fn_2_6D078(u8* object);

void fn_2_6D040(u8* object);

void fn_2_6CB78(u8* object);

void fn_2_6C97C(u8* object);

void fn_2_6C970(u8* object);

void fn_2_6C938(u8* object);

void fn_2_6C28C(u8* object);

void fn_2_6BF88(u8* object);

void fn_2_6BDD4(u8* object);

void fn_2_6BD9C(u8* object);

void fn_2_6BC00(u8* object);

void fn_2_6BBC8(u8* object);

void fn_2_6BA18(u8* object);

void fn_2_6B4C4(u8* object);

void fn_2_6ACF0(void);

void fn_2_6AAB8(void);

void fn_2_6C2C4(void);

void fn_2_68638(s32 index, s8 value);

void fn_2_68654(s32 index, s8 value);

void fn_2_686D0(s32 index, s8 value);

void fn_2_68D90(s32 index, s8 value);

void fn_2_68F08(s32 index, s8 value);

void fn_2_6AF80(s32 index, s8 value);

s32 fn_2_68670(s32 index);

s32 fn_2_68690(s32 index);

s32 fn_2_686B0(s32 index);

void fn_2_6BAAC(u8* object);

void fn_2_6F72C(u8* object);

void fn_2_6BFC0(u8* object);

void fn_2_6C2E8(u8* object);

void fn_2_6BA50(u8* object);

void fn_2_6BB7C(u8* object);

void fn_2_6C120(u8* object);

s32 fn_2_6AF9C(s32 index);

s32 fn_2_6AFD4(s32 index);

void fn_2_68DAC(s32 index, void* result);

void fn_2_696D4(s32 index);

void fn_2_68DE8(s32 index, Vec* result);

void fn_2_6AABC(s32 index, const Vec* position);

void fn_2_6A5A8(s32 index);

f32 fn_2_68940(s32 from, s32 to);

f32 fn_2_688A4(s32 index, s32 location);

void fn_2_6BDE0(MenuFadeState* fade);

void fn_2_6BC0C(MenuFadeState* fade);

void fn_2_6BAD8(MenuFadeState* fade);

s32 fn_2_686EC(s32 from, s32 to);

s16 fn_2_689CC(s32 index);

void fn_2_68F24(s32 index, s32 animation);

void fn_2_6AB3C(s32 index, const Vec* position, f32 heading);

void fn_2_6832C(void);

void fn_2_683EC(void);

#endif
