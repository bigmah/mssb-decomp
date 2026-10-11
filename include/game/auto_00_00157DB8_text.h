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
    /*0x1C*/ s16 _1C;
    /*0x1E*/ s16 _1E;
    /*0x20*/ s16 _20;
} PracticeTask;

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
