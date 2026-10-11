#ifndef __MENUS_AUTO_00_00013BA4_TEXT_H_
#define __MENUS_AUTO_00_00013BA4_TEXT_H_

#include "mssbTypes.h"

struct PortInput;

// Debug options menu state (lbl_2_bss_100B8).
typedef struct DebugMenuState {
    /*0x00*/ u8 _00[0x46];
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
    /*0xF4*/ u8 _F4; // toggled by fn_2_5979C
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
