#ifndef __GAME_BURSTPARAMS_H_
#define __GAME_BURSTPARAMS_H_

#include "types.h"

// Parameter block of fn_8002C2D0 (particle burst; values are fixed point, 1/100000; prm[11] is an RGBA colour).
// _00 is filled in at run time.
typedef struct BurstParams {
    /* 0x00 */ u32 _00;
    /* 0x04 */ s32 prm[15];
} BurstParams; // size 0x40

#endif
