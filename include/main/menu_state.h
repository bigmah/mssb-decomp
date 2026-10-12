#ifndef __MAIN_MENU_STATE_H__
#define __MAIN_MENU_STATE_H__

// Split out of main/menu_globals.h for units whose other headers clash with it.

#include "mssbTypes.h"

// lbl_8034E978: current menu screen.
typedef struct MenuState {
    /*0x00*/ u8 menu;
    /*0x01*/ u8 prevMenu;
    /*0x02*/ u8 prev03;
    /*0x03*/ u8 _03;
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06;
    /*0x07*/ u8 _07;
    /*0x08*/ u8 track; // from MenuDef.track of the current menu
    /*0x09*/ u8 prevTrack;
    /*0x0A*/ s8 text[10]; // text entries for the menu description
    /*0x14*/ u8 textCount;
    /*0x15*/ u8 textCur;
    /*0x16*/ u8 textDone[10]; // 0xFF: free
    /*0x20*/ u8 descState;
    /*0x21*/ u8 _21[2];
    /*0x23*/ u8 _23;
    /*0x24*/ u8 _24;
    /*0x25*/ u8 _25;
    /*0x26*/ u8 _26;
    /*0x27*/ u8 _27;
} MenuState; // size: 0x28

extern MenuState lbl_8034E978;

#endif
