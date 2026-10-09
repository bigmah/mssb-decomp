#ifndef __MENUS_REP_0DE0_H__
#define __MENUS_REP_0DE0_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"

typedef struct {
    void (*draw)(s32);
    Vec position;
    Vec rotation;
    u8 padding1C[0x0C];
} MenuDrawState;

typedef struct {
    u8 padding[0xAC];
    void* lights[3];
    u8 paddingB8[0x2CDC];
    MenuDrawState* states;
    u8 padding2D98[0x2E0];
    u16 count;
} MenuDrawWorld;

void fn_2_87114(void);

void fn_2_870D4(f32 value);

void fn_2_869B4(void);

void fn_2_86A0C(void);

#endif
