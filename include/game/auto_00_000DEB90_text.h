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
    /*0x0000*/ u8 _0000[0x2D8E];
    /*0x2D8E*/ u8 _2D8E;
    /*0x2D8F*/ u8 _2D8F[0x2D94 - 0x2D8F];
    /*0x2D94*/ MinigameCoinSprite* trail2; // [30]
    /*0x2D98*/ u8 _2D98[0x307A - 0x2D98];
    /*0x307A*/ u8 _307A;
    /*0x307B*/ u8 _307B[3];
    /*0x307E*/ u8 _307E;
} MinigameCharMgrView;

extern MinigameCharMgrView lbl_8036E548;

// Per-difficulty coin timing table (lbl_3_data_18BB0).
typedef struct MinigameCoinTiming {
    /*0x0*/ s16 _0;
    /*0x2*/ s16 blinkStart; // coins blink once the visible counter passes this
} MinigameCoinTiming;

// View of g_Scores, only the fields used here.
typedef struct MinigameScoresView {
    /*0x00*/ s32 inning;
    /*0x04*/ u8 _04[0xAA - 0x4];
    /*0xAA*/ u8 minigameRelated;
    /*0xAB*/ u8 _AB;
    /*0xAC*/ u8 _AC;
} MinigameScoresView;

extern MinigameScoresView g_Scores;

// View of lbl_3_common_bss_32724, only the fields used here.
typedef struct MinigameBss32724View {
    /*0x00*/ u8 _00[0xD5];
    /*0xD5*/ u8 _D5;
} MinigameBss32724View;

extern MinigameBss32724View lbl_3_common_bss_32724;

// View of lbl_3_common_bss_32234, only the fields used here.
typedef struct MinigameBss32234View {
    /*0x00*/ u8 _00;
    /*0x01*/ u8 _01;
} MinigameBss32234View;

extern MinigameBss32234View lbl_3_common_bss_32234;

// View of lbl_803CBC3C, only the fields used here.
typedef struct MinigameCBC3CView {
    /*0x00*/ u8 _00[2];
    /*0x02*/ u8 _02;
} MinigameCBC3CView;

extern MinigameCBC3CView lbl_803CBC3C;

// View of one g_Fielders entry, only the fields used here.
typedef struct MinigameFielderView {
    /*0x000*/ u8 _000[0x20D];
    /*0x20D*/ s8 rosterID;
    /*0x20E*/ u8 _20E[0x268 - 0x20E];
} MinigameFielderView; // size: 0x268

extern MinigameFielderView g_Fielders[];

void fn_3_59918(s32 x, s32 unused);

// View of lbl_3_common_bss_37400, only the fields used here.
typedef struct MinigameBss37400View {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 humanPlayer;
} MinigameBss37400View;

extern MinigameBss37400View lbl_3_common_bss_37400;

void fn_8001D0D0(s32 index, f32 scale);
void fn_800203E0(u8 scene, s8 variant);
s32 fn_80016F7C(void);
s32 fn_3_6C938(s32 a, s32 b);
void fn_3_59B20(void);

// View of lbl_8037169C (SceneFade in main/file_8001FE00.h), only the fields used here.
typedef struct MinigameSceneFadeView {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ u8 done;
    /*0x13*/ u8 _13;
} MinigameSceneFadeView;

extern MinigameSceneFadeView lbl_8037169C;

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
