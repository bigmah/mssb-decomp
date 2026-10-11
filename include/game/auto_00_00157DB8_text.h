#ifndef __AUTO_00_00157DB8_TEXT_GAME_H__
#define __AUTO_00_00157DB8_TEXT_GAME_H__

#include "mssbTypes.h"

// Practice/tutorial HUD task: the queue item lbl_803CC1B8 points at while one of
// this unit's HUD callbacks runs. Owns a run of sprites in lbl_80371C30.
typedef struct PracticeTask {
    /*0x00*/ void (*callback)(void);
    /*0x04*/ u8 _04[0x10];
    /*0x14*/ u16 baseIdx; // first sprite in lbl_80371C30
    /*0x16*/ u16 count;
    /*0x18*/ s16 _18;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 text; // lbl_80366B18 entry
    /*0x20*/ s16 _20;
} PracticeTask;

// View of lbl_3_common_bss_32724 (practice HUD flags), only the fields used here.
typedef struct PracticeHudBss {
    /*0x00*/ u8 _00[0x96 - 0x00];
    /*0x96*/ u8 _96;
    /*0x97*/ u8 _97[0x9C - 0x97];
    /*0x9C*/ u8 _9C;
    /*0x9D*/ u8 _9D[0xA5 - 0x9D];
    /*0xA5*/ u8 _A5;
    /*0xA6*/ u8 _A6;
    /*0xA7*/ u8 _A7;
    /*0xA8*/ u8 _A8[0xAA - 0xA8];
    /*0xAA*/ u8 _AA;
    /*0xAB*/ u8 _AB[0xBC - 0xAB];
    /*0xBC*/ u8 _BC;
    /*0xBD*/ u8 _BD[0xC0 - 0xBD];
    /*0xC0*/ u8 _C0;
    /*0xC1*/ u8 _C1;
    /*0xC2*/ u8 _C2;
    /*0xC3*/ u8 _C3[0xC6 - 0xC3];
    /*0xC6*/ u8 _C6;
    /*0xC7*/ u8 _C7;
    /*0xC8*/ u8 _C8[0xD9 - 0xC8];
    /*0xD9*/ u8 _D9;
} PracticeHudBss;

// View of lbl_3_common_bss_34C90 (practice tutorial state), only the fields used here.
typedef struct PracticeTutorBss {
    /*0x000*/ u8 _000[0x1D2];
    /*0x1D2*/ u8 _1D2;
    /*0x1D3*/ u8 _1D3;
    /*0x1D4*/ u8 _1D4;
    /*0x1D5*/ u8 _1D5;
} PracticeTutorBss;

void fn_3_157DB8(s32 arg0);
void fn_3_1580AC(void);
void fn_3_1581FC(void);
void fn_3_158264(PracticeTask* o);
void fn_3_1589C4(void);
void fn_3_1590C8(void);
void fn_3_159590(void);
void fn_3_15AD94(void);
void fn_3_15ADD4(void);
void fn_3_15AF78(void);
void fn_3_15B610(void);
void fn_3_15B0D8(void);
void fn_3_15AE34(void);
void fn_3_157E28(void);
void fn_3_15810C(void);
void fn_3_1583AC(void);
void fn_3_1586B0(void);
void fn_3_158B64(void);
void fn_3_158FE4(void);
void fn_3_159114(void);
void fn_3_1595F4(void);
void fn_3_1599B8(void);
void fn_3_159D50(void);
void fn_3_15A244(void);
void fn_3_15A448(void);
void fn_3_15A75C(void);
void fn_3_15A9F4(void);
void fn_3_15B204(void);
void fn_3_15B494(void);

#endif
