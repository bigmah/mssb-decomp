#ifndef __MENUS_REP_0FD8_H_
#define __MENUS_REP_0FD8_H_

#include "mssbTypes.h"

// Menus REL bss at 0x340234: state of the current menu screen (only the fields used here).
typedef struct MenuScreenState {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ u16 state;
    /*0x12*/ u8 _12[6];
    /*0x18*/ u16 subState;
} MenuScreenState;

void fn_2_8ED4C(void);
void fn_2_8EDC4(void);
void fn_2_8EEC8(void);

#endif
