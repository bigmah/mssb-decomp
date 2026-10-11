#ifndef __GAME_AUTO_00_0016C410_TEXT_H_
#define __GAME_AUTO_00_0016C410_TEXT_H_

#include "mssbTypes.h"

// Per-stadium sound-effect mix (lbl_3_data_8404[stadium][sound], lbl_3_data_84B8[sound] in minigames).
typedef struct StadiumSfxMix {
    /*0x0*/ u8 vol;
    /*0x1*/ u8 ctrl5B; // value for sndFXCtrl controller 0x5B
} StadiumSfxMix;

void fn_3_16C410(u8 alt);

#endif
