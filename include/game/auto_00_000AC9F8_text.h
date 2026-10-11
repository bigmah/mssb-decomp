#ifndef __AUTO_00_000AC9F8_TEXT_GAME_H__
#define __AUTO_00_000AC9F8_TEXT_GAME_H__

#include "mssbTypes.h"

// Pause / substitution menu state (lbl_3_common_bss_34C90, size 0x264).
typedef struct PauseMenuState {
    /*0x000*/ s32 team; // roster index of the team being edited
    /*0x004*/ u16 heldButtons;
    /*0x006*/ u16 newButtons;
    /*0x008*/ u16 repeatButtons;
    /*0x00A*/ s16 _0A;
    /*0x00C*/ s16 frames;
    /*0x00E*/ s16 _0E;
    /*0x010*/ s16 _10;
    /*0x012*/ s16 subFrames;
    /*0x014*/ u8 _14[0x1D0 - 0x14];
    /*0x1D0*/ u8 menuType;
    /*0x1D1*/ u8 state;
    /*0x1D2*/ u8 subState;
    /*0x1D3*/ u8 _1D3;
    /*0x1D4*/ u8 _1D4;
    /*0x1D5*/ u8 active;
    /*0x1D6*/ u8 _1D6;
    /*0x1D7*/ u8 _1D7;
    /*0x1D8*/ u8 openedByBattingTeam;
    /*0x1D9*/ u8 _1D9;
    /*0x1DA*/ s8 cursor;
    /*0x1DB*/ u8 _1DB[2];
    /*0x1DD*/ u8 _1DD[0x201 - 0x1DD];
    /*0x201*/ u8 _201;
    /*0x202*/ u8 requestOpen[2];
    /*0x204*/ u8 _204[2];
    /*0x206*/ s8 inputCooldown;
    /*0x207*/ u8 _207[2];
    /*0x209*/ u8 _209[0x221 - 0x209];
    /*0x221*/ u8 optionCursor;
    /*0x222*/ u8 optionCount;
    /*0x223*/ u8 _223[0x23F - 0x223];
    /*0x23F*/ u8 _23F[2];
    /*0x241*/ u8 _241;
    /*0x242*/ s16 positions[9];
    /*0x254*/ s16 _254;
    /*0x256*/ s16 _256;
    /*0x258*/ s16 _258;
    /*0x25A*/ s16 _25A;
    /*0x25C*/ s16 _25C;
    /*0x25E*/ s16 _25E;
    /*0x260*/ u8 positionsChanged;
    /*0x261*/ u8 _261[3];
} PauseMenuState; // size: 0x264

extern PauseMenuState lbl_3_common_bss_34C90;

// A menu's option list: number of options, then option ids.
typedef struct MenuOptionList {
    /*0x0*/ u8 count;
    /*0x1*/ u8 items[7];
} MenuOptionList; // size: 0x8

void fn_3_AFDA4(void);

void fn_3_AFD80(u8 state);

void fn_3_B0A88(void);

void fn_3_B3A28(void);

void fn_3_B1DA4(s32 level, u8 value);

void fn_3_B3288(void);

s32 fn_3_AFD48(s16 value);

s32 fn_3_B0CF4(void);

void fn_3_B0D7C(void);

void fn_3_B0D78(void);

void fn_3_B0D2C(void);

void fn_3_B1BCC(void);

void fn_3_B025C(void);

void fn_3_AFDC0(void);

void fn_3_B0DB0(void);

void fn_3_B1120(void);

void fn_3_B116C(void);

void fn_3_B274C(void);

void fn_3_B1C14(void);

void fn_3_B0AAC(void);

void fn_3_B01E0(void);

void fn_3_B03F0(void);

s32 fn_3_B254C(void);

void fn_3_B27A4(void);

void fn_3_ACD38(void);

void fn_3_AD164(s32 arg);

void fn_3_AD3BC(void);

void fn_3_AD8CC(void);

void fn_3_AC9F8(void);

void fn_3_ACAF8(void);

void fn_3_B3620(void);

void fn_3_B056C(void);

void fn_3_AF10C(void);

void fn_3_B0E00(void);

void fn_3_AE900(void);

void fn_3_B2AA0(void);

#endif
