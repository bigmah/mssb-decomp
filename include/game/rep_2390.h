#ifndef __GAME_rep_2390_H_
#define __GAME_rep_2390_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"
#include "main/file_80024184.h" // TexArchive

// View of lbl_3_common_bss_35154, only the fields used here.
typedef struct Rep2390Bss35154 {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ TexArchive* tex; // particle textures
    /*0x008*/ u8 _008[0x440 - 0x8];
    /*0x440*/ Vec ballPos[2]; // [0]: this frame, [1]: previous frame
} Rep2390Bss35154;

void fn_3_CB3AC(void);
void fn_3_CB538(s32 mode);

#endif // !__GAME_rep_2390_H_
