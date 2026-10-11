#ifndef __GAME_AUTO_00_000D8A10_TEXT_H_
#define __GAME_AUTO_00_000D8A10_TEXT_H_

#include "mssbTypes.h"

// Per-stadium crowd sound settings (lbl_3_data_8404, 0x1E bytes each).
typedef struct MinigameStadiumSound {
    /*0x00*/ u8 _00[0x16];
    /*0x16*/ u8 vol;
    /*0x17*/ u8 ctrl;
    /*0x18*/ u8 _18[0x1E - 0x18];
} MinigameStadiumSound; // size: 0x1E

void fn_3_1079C8(u8* out, s32 mode);

void fn_3_D8A10(void);
void fn_3_D8CD0(void);
void fn_3_D9868(void);
void fn_3_D9A30(void);

#endif
