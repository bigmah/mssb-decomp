#ifndef __GAME_rep_1770_H_
#define __GAME_rep_1770_H_

#include "mssbTypes.h"
#include "main/scene_task.h" // SCENE_TASK_VIEW_LINKS
#include "game/auto_00_00097144_text.h"

// Star-meter HUD task (fn_3_9A8A4 / fn_3_99E10): HudTask with the per-team star counts at 0x1C.
typedef struct StarHudTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ SCENE_TASK_VIEW_LINKS
    /*0x14*/ u16 baseIdx; // first slot in lbl_80371C30
    /*0x16*/ u16 _16;
    /*0x18*/ u16 timer;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 stars[2]; // stars currently shown per team
    /*0x20*/ u16 _20;
} StarHudTask;

void fn_3_993A8(void);
void fn_3_9976C(void);
void fn_3_99818(void);
void fn_3_99BDC(void);
void fn_3_99C88(void);
void fn_3_99CFC(void);
void fn_3_99E10(void);
void fn_3_9A8A4(void);
void fn_3_9B108(HudTask* task);
void fn_3_9B320(void);
void fn_3_9B7F4(void);
void fn_3_9BEE0(HudTask* task);
void fn_3_9C014(void);
void fn_3_9C28C(void);

#endif // !__GAME_rep_1770_H_
