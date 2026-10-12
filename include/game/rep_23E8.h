#ifndef __GAME_rep_23E8_H_
#define __GAME_rep_23E8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// lbl_3_common_bss_35154 (stadium-effect state), only the fields used here: the stadium star
// that floats up after it is collected.
typedef struct Rep23E8Bss35154 {
    /*0x000*/ u8 _000[0x3AC];
    /*0x3AC*/ u32 flags;
    /*0x3B0*/ u8 _3B0[0x3E8 - 0x3B0];
    /*0x3E8*/ Vec starPos;
    /*0x3F4*/ Vec starRot;
    /*0x400*/ u8 _400[0x404 - 0x400];
    /*0x404*/ s16 starTimer;
    /*0x406*/ u8 _406[0x40A - 0x406];
    /*0x40A*/ u8 starActive;
    /*0x40B*/ u8 _40B[0x479 - 0x40B];
    /*0x479*/ u8 disabled;
} Rep23E8Bss35154;

void fn_3_CB738(void);
void fn_3_CB7D4(void);
void fn_3_CB7E8(f32 x, f32 y, f32 z);

#endif // !__GAME_rep_23E8_H_
