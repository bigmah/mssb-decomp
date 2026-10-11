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

// Controller input as latched by the menus (one per port).
typedef struct PortInput {
    /*0x0*/ u16 held;
    /*0x2*/ u16 pressed;
    /*0x4*/ u16 repeat;
} PortInput;

// Pause/star menu work area inside lbl_803297E0 (only the fields used here).
typedef struct MenuWork {
    /*0x0000*/ PortInput input[4]; // used instead of lbl_8034E9A0.input while paused in game
    /*0x0018*/ u8 swap[2][2];        // per team: last swapped slots (from, to)
    /*0x001C*/ u8 _001C[0xCF38 - 0x1C];
    /*0xCF38*/ u16 _CF38;
    /*0xCF3A*/ s8 _CF3A;
    /*0xCF3B*/ u8 _CF3B;
    /*0xCF3C*/ u8 _CF3C[2];
    /*0xCF3E*/ u8 _CF3E[2];
    /*0xCF40*/ u8 _CF40;
    /*0xCF41*/ u8 _CF41;
    /*0xCF42*/ u8 _CF42;
    /*0xCF43*/ u8 _CF43;
    /*0xCF44*/ u8 _CF44;
    /*0xCF45*/ u8 _CF45;
    /*0xCF46*/ s8 slot[2]; // selected batting order slot (1-based) per team
    /*0xCF48*/ s8 _CF48[2];
    /*0xCF4A*/ s8 _CF4A[2];
    /*0xCF4C*/ u8 _CF4C[2];
    /*0xCF4E*/ u8 _CF4E[2];
    /*0xCF50*/ u8 _CF50[2];
    /*0xCF52*/ u8 _CF52[2];
    /*0xCF54*/ u8 _CF54[2];
    /*0xCF56*/ u8 _CF56[2];
    /*0xCF58*/ u8 _CF58[2];
    /*0xCF5A*/ u8 _CF5A;
    /*0xCF5B*/ u8 ready[2]; // per port, two-player tutorial sync
    /*0xCF5D*/ u8 _CF5D;
    /*0xCF5E*/ u8 _CF5E;
    /*0xCF5F*/ u8 _CF5F;
    /*0xCF60*/ u8 _CF60;
    /*0xCF61*/ u8 _CF61[2];
    /*0xCF63*/ u8 _CF63[2];
    /*0xCF65*/ u8 _CF65[2];
    /*0xCF67*/ u8 _CF67[2];
    /*0xCF69*/ u8 _CF69;
    /*0xCF6A*/ u8 _CF6A;
    /*0xCF6B*/ u8 _CF6B;
    /*0xCF6C*/ u8 _CF6C;
    /*0xCF6D*/ u8 _CF6D;
    /*0xCF6E*/ u8 _CF6E;
    /*0xCF6F*/ u8 _CF6F;
    /*0xCF70*/ u8 _CF70;
    /*0xCF71*/ u8 _CF71;
    /*0xCF72*/ u8 _CF72;
    /*0xCF73*/ u8 pauseShown;
    /*0xCF74*/ u8 _CF74;
    /*0xCF75*/ s8 starCursor;
    /*0xCF76*/ s8 prevStarCursor;
    /*0xCF77*/ u8 _CF77;
    /*0xCF78*/ u16 _CF78;
    /*0xCF7A*/ u8 nameText; // text entries of the star/mission panel
    /*0xCF7B*/ u8 descText;
    /*0xCF7C*/ u8 missionText;
    /*0xCF7D*/ u8 _CF7D;
    /*0xCF7E*/ u8 scoutSub;
    /*0xCF7F*/ u8 scoutDone;
    /*0xCF80*/ s8 scoutTotal[9]; // scout flags per player
    /*0xCF89*/ s8 scoutGot[9];
    /*0xCF92*/ u8 _CF92;
    /*0xCF93*/ u8 missionShown;
    /*0xCF94*/ u8 menuDone;
    /*0xCF95*/ s8 prevSlotCursor;
    /*0xCF96*/ s8 slotCursor;
    /*0xCF97*/ s8 prevStarCursor2;
    /*0xCF98*/ s8 starCursor2;
    /*0xCF99*/ u8 _CF99;
    /*0xCF9A*/ u8 _CF9A;
    /*0xCF9B*/ u8 _CF9B;
    /*0xCF9C*/ s16 _CF9C;
    /*0xCF9E*/ u8 _CF9E[2];
    /*0xCFA0*/ u8 _CFA0;
    /*0xCFA1*/ u8 _CFA1;
    /*0xCFA2*/ u8 _CFA2[2];
} MenuWork;


extern MenuWork lbl_803297E0;

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

// Message box with optional voice (lbl_803C50E8 is the shared one).
typedef struct MsgBox {
    /*0x00*/ u8 _00[3];
    /*0x03*/ u8 port;
    /*0x04*/ u8 _04;
    /*0x05*/ u8 _05[0x3E - 0x05];
    /*0x3E*/ u8 state;
    /*0x3F*/ u8 msgId;
    /*0x40*/ s8 _40;
    /*0x41*/ s8 _41;
    /*0x42*/ u8 _42[2];
    /*0x44*/ u8 done;
    /*0x45*/ u8 result;
    /*0x46*/ u8 cancel;
    /*0x47*/ u8 _47;
    /*0x48*/ u8 loopStop;
    /*0x49*/ u8 looping;
    /*0x4A*/ u16 loopMsg;
    /*0x4C*/ u8 kind;
    /*0x4D*/ u8 arg;
    /*0x4E*/ u8 _4E;
    /*0x4F*/ u8 _4F;
    /*0x50*/ u16 msg;
    /*0x52*/ u8 _52;
    /*0x53*/ u8 _53[0x5C - 0x53];
} MsgBox; // size: 0x5C

extern MsgBox lbl_803C50E8;

#endif
