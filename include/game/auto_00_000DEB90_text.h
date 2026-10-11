#ifndef __GAME_AUTO_00_000DEB90_TEXT_H_
#define __GAME_AUTO_00_000DEB90_TEXT_H_

#include "mssbTypes.h"

// One coin sprite in lbl_8036E548.trail2 (CharTrail in main/file_80011640.h).
typedef struct MinigameCoinSprite {
    /*0x00*/ void (*draw)(void);
    /*0x04*/ f32 x;
    /*0x08*/ f32 y;
    /*0x0C*/ f32 z;
    /*0x10*/ f32 _10;
    /*0x14*/ f32 angle;
    /*0x18*/ u8 _18[0x26 - 0x18];
    /*0x26*/ u8 visible;
    /*0x27*/ u8 _27;
} MinigameCoinSprite; // size: 0x28

// View of lbl_8036E548 (CharMgr in main/file_80011640.h), only the fields used here.
typedef struct MinigameCharMgrView {
    /*0x0000*/ u8 _0000[0x2D94];
    /*0x2D94*/ MinigameCoinSprite* trail2; // [30]
} MinigameCharMgrView;

extern MinigameCharMgrView lbl_8036E548;

void fn_8001D0D0(s32 index, f32 scale);

void fn_3_10C81C(void);

void fn_3_DEB90(void);
void fn_3_DF00C(void);
void fn_3_DF25C(void);
void fn_3_DF3D8(void);
void fn_3_DF608(void);
void fn_3_DF6D4(void);
void fn_3_DF820(void);
void fn_3_DF8D4(void);
void fn_3_DFA20(void);
void fn_3_DFBAC(void);
void fn_3_E0668(void);
void fn_3_E0758(void);
void fn_3_E07DC(void);

#endif
