#ifndef __MENUS_REP_1028_H__
#define __MENUS_REP_1028_H__

#include "mssbTypes.h"

typedef struct {
    u8 _00[0x90];
    s16 state;
} MenuStateObject;

typedef void (*MenuStateCallback)(MenuStateObject* object);

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

#endif
