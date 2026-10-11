#ifndef __GAME_AUTO_00_0006D4A0_TEXT_H_
#define __GAME_AUTO_00_0006D4A0_TEXT_H_

#include "mssbTypes.h"

// Per-player in-game record at lbl_803535C8 (2 teams x 9 players, 0x1E each).
typedef struct PlayerGameRecord {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ u16 stamina;
    /*0x12*/ u8 _12[0x1E - 0x12];
} PlayerGameRecord; // size: 0x1E

extern PlayerGameRecord lbl_803535C8[2][9];

void fn_3_6D4A0(void);
s32 fn_3_6D564(s32 team, s32 idx, s32 delta);
s32 fn_3_6D658(s32 team, s32 charId, s32 otherId);

#endif
