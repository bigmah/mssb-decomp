#ifndef __MAIN_MENU_GLOBALS_H__
#define __MAIN_MENU_GLOBALS_H__

// Menu globals in main.dol that don't depend on the conflicting
// lbl_8034E9A0 views (CharSelWork / CharSelectState), so any unit can include this.

#include "mssbTypes.h"

// Scene/menu flow state (lbl_803CBBCC points at it).
typedef struct SceneFlow {
    /*0x00*/ u16 _00;
    /*0x02*/ u16 scene;
    /*0x04*/ u16 step;
    /*0x06*/ u16 prevScene;
    /*0x08*/ u16 prevStep;
    /*0x0A*/ u16 _0A;
    /*0x0C*/ u16 padHeld[2];
    /*0x10*/ u8 _10;
} SceneFlow;

extern SceneFlow* lbl_803CBBCC;

// Menu input/transition state (lbl_803C66B0, only the fields used here).
typedef struct TutorialSteps {
    /*0x00*/ u8 steps[14][6]; // per tutorial step: [0] shared, [1 + port] per-port state
    /*0x54*/ u8 _54;
    /*0x55*/ u8 active[4]; // per port: tutorial text box busy
    /*0x59*/ u8 portOf[4]; // controller port of player i
    /*0x5D*/ u8 step[7];   // current tutorial step per port
} TutorialSteps; // size: 0x64

extern TutorialSteps lbl_803C66B0;

typedef struct Unk803C5EA4 {
    /*0x00*/ u8 _00[5];
    /*0x05*/ u8 _05;
    /*0x06*/ u8 _06[0xF - 0x6];
    /*0x0F*/ u8 _0F;
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12[0x36 - 0x12];
    /*0x36*/ u8 _36;
    /*0x37*/ u8 prevMode;
    /*0x38*/ u8 mode;
    /*0x39*/ u8 _39[3];
} Unk803C5EA4; // size: 0x3C

extern Unk803C5EA4 lbl_803C5EA4;

#endif
