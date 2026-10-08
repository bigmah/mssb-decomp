#ifndef __MENUS_REP_1028_H__
#define __MENUS_REP_1028_H__

#include "mssbTypes.h"

typedef struct {
    u8 _00[0x90];
    s16 state;
} MenuStateObject;

typedef void (*MenuStateCallback)(MenuStateObject* object);

void fn_2_90428(s32 index);

void fn_2_91C08(MenuStateObject* object);
void fn_2_91B38(MenuStateObject* object);
void fn_2_91AE4(MenuStateObject* object);
void fn_2_9197C(MenuStateObject* object);
void fn_2_918A4(MenuStateObject* object);
void fn_2_916C0(MenuStateObject* object);
void fn_2_91450(MenuStateObject* object);
void fn_2_911E0(MenuStateObject* object);
void fn_2_90DAC(MenuStateObject* object);
void fn_2_90BD0(MenuStateObject* object);

void fn_2_918DC(MenuStateObject* object);

void fn_2_9177C(MenuStateObject* object);

void fn_2_9150C(MenuStateObject* object);

void fn_2_9129C(MenuStateObject* object);

void fn_2_90C08(MenuStateObject* object);

void fn_2_90AB0(MenuStateObject* object);

void fn_2_90940(MenuStateObject* object);

void fn_2_90934(MenuStateObject* object);

void fn_2_9082C(MenuStateObject* object);

void fn_2_9061C(MenuStateObject* object);

void fn_2_909F4(MenuStateObject* object);

void fn_2_908FC(MenuStateObject* object);

void fn_2_907F4(MenuStateObject* object);


void fn_2_90E98(u8* object);

void fn_2_90C14(u8* object);

void fn_2_90838(u8* object);

void fn_2_8F758(s32 index, u8 value);

void fn_2_8F73C(s32 index, u8 value);

u8 fn_2_8F720(s32 index);

void fn_2_90628(u8* object);

void fn_2_8F688(void);

void fn_2_8F640(void);

void fn_2_8F774(s32 index);

void fn_2_916F8(u8* object);

void fn_2_91488(u8* object);

void fn_2_91218(u8* object);

void fn_2_90A2C(u8* object);

void fn_2_9033C(s32 index, const void* position, f32 value);

void fn_2_8F7B0(s32 index, s16 type);

void fn_2_8F838(s32 index, s16 type);

void fn_2_8F8C0(s32 index, s16 type);

void fn_2_8F948(s32 index, s16 type);

void fn_2_8F9D0(s32 index, s16 type);

void fn_2_8FA58(s32 index, s16 type);

void fn_2_8FAE0(s32 index, s16 type);

#endif
