#ifndef __GAME_rep_21F8_H_
#define __GAME_rep_21F8_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "game/rep_1E08.h" // SprAnimElem

// Stadium-intro logo being shown (lbl_3_bss_9F20).
typedef struct Rep21F8Logo {
    /*0x00*/ u8 logo; // index into lbl_3_data_17B04
    /*0x01*/ u8 _01[3];
    /*0x04*/ f32 pos[3];
    /*0x10*/ f32 time;
} Rep21F8Logo; // size: 0x14

// View of lbl_3_common_bss_35154, only the fields used here.
typedef struct Rep21F8Bss35154 {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ void* tex; // effect texture archive
} Rep21F8Bss35154;

int fn_3_C937C(void);
f32 fn_3_C9590(SprAnimElem* o, s32 k, MtxPtr m, f32 t);
void fn_3_C9734(void);

#endif // !__GAME_rep_21F8_H_
