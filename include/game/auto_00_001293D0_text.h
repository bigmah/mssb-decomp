#ifndef __AUTO_00_001293D0_TEXT_GAME_H__
#define __AUTO_00_001293D0_TEXT_GAME_H__

#include "mssbTypes.h"
#include "main/file_8000F150.h" // LayoutSlot

// HUD task (queue item in lbl_803CC1B8 while one of this unit's HUD updaters runs).
typedef struct HudTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x10];
    /*0x14*/ u16 baseIdx; // first sprite in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ s16 timer;
    /*0x1A*/ s16 _1A;
    /*0x1C*/ u16 state;
    /*0x1E*/ u16 _1E;
    /*0x20*/ s16 _20;
    /*0x22*/ s16 _22;
} HudTask;

void fn_3_12DB54(void);
void fn_3_12E808(void);
u32 fn_3_12DD88(void);
void fn_3_1293D0(void);
void fn_3_12C514(void);
void fn_3_12C5CC(void);
void fn_3_129F48(void);
void fn_3_12C684(void);
void fn_3_129458(void);
void fn_3_12E83C(void);
void fn_3_12C74C(void);
void fn_3_12C868(void);
void fn_3_12C984(void);
void fn_3_12C3F0(void);
void fn_3_12BFE8(void);
void fn_3_12C1AC(void);
void fn_3_129C88(void);
void fn_3_129FF8(void);
void fn_3_12BB64(void);

#endif
