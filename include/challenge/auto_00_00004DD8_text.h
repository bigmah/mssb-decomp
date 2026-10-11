#ifndef __CHALLENGE_AUTO_00_00004DD8_TEXT_H_
#define __CHALLENGE_AUTO_00_00004DD8_TEXT_H_

#include "mssbTypes.h"

// Model viewer state (lbl_1_common_bss_472B4, size 0x3C0; rep_0138 accesses it by offset).
typedef struct ChViewer {
    /*0x000*/ u8 _000[0x224];
    /*0x224*/ u32* effects; // relocated effect table (effectCount + 1 entries)
    /*0x228*/ s16 effectCount;
    /*0x22A*/ s16 animCount;
    /*0x22C*/ u8 _22C[2];
    /*0x22E*/ s16 anim; // selected animation, -1 = none
    /*0x230*/ u8 _230[0x3C0 - 0x230];
} ChViewer;

extern ChViewer lbl_1_common_bss_472B4;

void fn_1_4DD8(u16* file);

#endif
