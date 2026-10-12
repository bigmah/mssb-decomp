#ifndef __MAIN_CHARSEL_STATE_H__
#define __MAIN_CHARSEL_STATE_H__

// CharSelectState on its own, for units whose other declarations clash with
// main/file_800639BC.h (which declares lbl_8034E9A0 with this type).

#include "mssbTypes.h"
#include "game/UnknownHomes_Game.h"
#include "main/menu_globals.h"

// Character-select / team-setup state at 0x8034E9A0 (size 0x4C28).
// Only the fields used so far are named.
typedef struct CharSelectState {
    /*0x0000*/ CharacterStats roster[6][9]; // stats of every character, indexed [id / 9][id % 9]
    /*0x21C0*/ u8 _21C0[0x4380 - 0x21C0];
    /*0x4380*/ u8 presets[12][0x48]; // [n][0..8]: roster indices of a preset team
    /*0x46E0*/ s32 captain[2]; // captain character id per team
    /*0x46E8*/ u8* heapMarkA[2]; // saved lbl_803C7898 lo/hi (fn_2_129AC)
    /*0x46F0*/ u8* heapMarkB[2]; // saved lbl_803C7898 lo/hi (fn_2_12988)
    /*0x46F8*/ u8 ports[2];
    /*0x46FA*/ u8 _46FA[0x46FC - 0x46FA];
    /*0x46FC*/ s8 _46FC[4];
    /*0x4700*/ u8 _4700;
    /*0x4701*/ u8 _4701;
    /*0x4702*/ u8 _4702;
    /*0x4703*/ u8 _4703;
    /*0x4704*/ u8 _4704;
    /*0x4705*/ u8 _4705;
    /*0x4706*/ u8 _4706;
    /*0x4707*/ u8 _4707;
    /*0x4708*/ u8 _4708;
    /*0x4709*/ s8 captainSlot[2]; // roster slot of the captain per team
    /*0x470B*/ u8 _470B;
    /*0x470C*/ u8 _470C;
    /*0x470D*/ s8 captainVariant[2]; // captain costume/colour index (fn_800678CC)
    /*0x470F*/ s8 teamRating[2]; // 0-5, from the average of fn_800670A0
    /*0x4711*/ u8 _4711;
    /*0x4712*/ u8 _4712;
    /*0x4713*/ u8 _4713;
    /*0x4714*/ u8 _4714[0x4728 - 0x4714];
    /*0x4728*/ u8 _4728;
    /*0x4729*/ u8 _4729;
    /*0x472A*/ u8 _472A;
    /*0x472B*/ u8 _472B;
    /*0x472C*/ PortInput input[4];
    /*0x4744*/ u8 _4744[0x4754 - 0x4744];
    /*0x4754*/ u8 _4754;
    /*0x4755*/ u8 _4755;
    /*0x4756*/ u8 _4756;
    /*0x4757*/ u8 charFlag[0x36]; // per character id
    /*0x478D*/ u8 chemOrder[2][0x36]; // character ids sorted by chemistry with the captain
    /*0x47F9*/ s8 chemPartners[2][9][9]; // per player: ids of teammates with good chemistry, sorted
    /*0x489B*/ u8 _489B[0x48AD - 0x489B];
    /*0x48AD*/ u8 _48AD;
    /*0x48AE*/ u8 _48AE;
    /*0x48AF*/ u8 _48AF;
    /*0x48B0*/ u8 _48B0;
    /*0x48B1*/ u8 _48B1;
    /*0x48B2*/ u8 _48B2;
    /*0x48B3*/ u8 _48B3;
    /*0x48B4*/ u8 _48B4;
    /*0x48B5*/ u8 _48B5[0x4C28 - 0x48B5];
} CharSelectState; // size: 0x4C28

#endif
