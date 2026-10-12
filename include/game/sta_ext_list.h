#ifndef __GAME_STA_EXT_LIST_H_
#define __GAME_STA_EXT_LIST_H_

#include "mssbTypes.h"

// Animated texture tiles: lbl_3_common_bss_350E4.anim[] (sta_c4 fn_3_FA58C sets them up,
// rep_1C0 fn_3_5C68 blits a tile of p0 into texture p4 when an entry's timer runs out).
typedef struct StaExtList {
    /*0x00*/ void* p0;      // TexImage* tile source: stadium file + 0x60 / + 0xA0
    /*0x04*/ void* p4;      // TexImage* destination: stadium file + 0x40 / + 0x80
    /*0x08*/ void* p8;      // lbl_3_data_10F88 / lbl_3_data_11008
    /*0x0C*/ void* pC;      // lbl_3_data_10F7C / lbl_3_data_10F84
    /*0x10*/ u8* entries;   // count entries of 3 bytes
    /*0x14*/ u16 count;
    /*0x16*/ u16 nChoices;  // range of the random third byte
    /*0x18*/ u16 n18;
} StaExtList; // size: 0x1C

#endif // !__GAME_STA_EXT_LIST_H_
