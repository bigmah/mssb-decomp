#ifndef __MENUS_REP_0840_H_
#define __MENUS_REP_0840_H_

#include "mssbTypes.h"

struct Task;

// Scene task (lbl_803CC1B8) running fn_2_3BD88.
typedef struct MenuSceneTask0840 {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ struct Task* parent;
    /*0x10*/ u8 _10[0x4];
    /*0x14*/ s16 timer;
    /*0x16*/ u8 _16[0x28 - 0x16];
    /*0x28*/ s8 state;
} MenuSceneTask0840;

void fn_2_3BD88(void);

#endif
