#ifndef __AUTO_00_00090754_TEXT_GAME_H__
#define __AUTO_00_00090754_TEXT_GAME_H__

#include "mssbTypes.h"
#include "main/scene_task.h" // SCENE_TASK_VIEW_HEAD

void fn_3_90754(u8* p, s8 a, s8 b);

s32 fn_3_90764(u8* state);

s32 fn_3_90798(u8* state);

void fn_3_9081C(void);

s32 fn_3_90860(void);

void fn_3_908E8(void);

s32 fn_3_90928(void);

void fn_3_909B0(void);

s32 fn_3_90A18(void);

void fn_3_90AB0(s32 a);

s32 fn_3_91064(u8* state);

s32 fn_3_910AC(u8* state);

// Scene task that shows the outs lamps (fn_3_911A8); a SceneTask (main/scene_task.h)
// with its own words after 0x18.
typedef struct OutsDisplayTask {
#ifdef TARGET_PC
    SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    u8 _14[4];
#else
    /*0x00*/ u8 _00[0x18]; // SceneTask head
#endif
    /*0x18*/ u16 frames;
    /*0x1A*/ u16 _1A;
    /*0x1C*/ u16 outs; // outs currently lit
} OutsDisplayTask;

void fn_3_910F4(OutsDisplayTask* p);

void fn_3_911A8(void);

s32 fn_3_90C14(s32 a);

s32 fn_3_90B14(s32 a, s32 b);

void fn_3_90CB0(void);

s32 fn_3_90F48(u8* state);

s32 fn_3_90DD8(void);

#endif
