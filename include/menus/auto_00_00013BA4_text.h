#ifndef __MENUS_AUTO_00_00013BA4_TEXT_H_
#define __MENUS_AUTO_00_00013BA4_TEXT_H_

#include "mssbTypes.h"

struct PortInput;

// Menu state (lbl_2_bss_100B8); the debug options menu uses 0x46..0x51.
typedef struct DebugMenuState {
    /*0x00*/ u8 _00[4];  // per team counter (fn_2_15104)
    /*0x04*/ u8 _04[8];
    /*0x0C*/ s32 _0C;
    /*0x10*/ u8 _10[2];  // per team
    /*0x12*/ u8 _12[2];  // per team: captain needs reload (fn_2_12A70)
    /*0x14*/ u8 _14[4];
    /*0x18*/ u8 _18[4];
    /*0x1C*/ u8 _1C[4];
    /*0x20*/ u8 _20;
    /*0x21*/ s8 _21[2];
    /*0x23*/ s8 _23[2];
    /*0x25*/ u8 _25[0x2D - 0x25];
    /*0x2D*/ u8 _2D; // used length of _14/_1C
    /*0x2E*/ u8 _2E[2];
    /*0x30*/ u8 _30[2];
    /*0x32*/ u8 _32[0x40 - 0x32];
    /*0x40*/ u8 _40[2]; // per team
    /*0x42*/ u8 _42[4];
    /*0x46*/ u8 _46[5]; // see fn_2_16A34
    /*0x4B*/ s8 _4B;
    /*0x4C*/ u8 settingSel; // page 1: index into g_d_GameSettings._1A
    /*0x4D*/ u8 unlockSel;  // page 2: index into lbl_80361B20.unlocked
    /*0x4E*/ u8 _4E;        // page 3 cursor
    /*0x4F*/ u8 flagSel;    // page 4: index into lbl_80361B20.flagsE4
    /*0x50*/ s8 page;       // 0: top menu
    /*0x51*/ u8 cursor;     // top-menu cursor (1..4)
    /*0x52*/ u8 _52[2];
} DebugMenuState; // size: 0x54

// Save-data flags block (lbl_80361B20, main.dol).
typedef struct UnlockFlags {
    /*0x00*/ u8 unlocked[0x36];
    /*0x36*/ u8 _36[0xE4 - 0x36];
    /*0xE4*/ u8 flagsE4[4];
    /*0xE8*/ u8 _E8[0xF4 - 0xE8];
    /*0xF4*/ u8 _F4; // row of lbl_800FE930; toggled by fn_2_5979C
    /*0xF5*/ u8 _F5;
    /*0xF6*/ u8 _F6[2];
} UnlockFlags; // size: 0xF8

void fn_2_13BA4(struct PortInput* in);
void fn_2_13CA0(struct PortInput* in);
void fn_2_13D70(struct PortInput* in);
void fn_2_1406C(struct PortInput* in);
void fn_2_14164(struct PortInput* in);
void fn_2_14220(struct PortInput* in);

#endif
