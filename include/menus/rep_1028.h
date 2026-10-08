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

#endif
