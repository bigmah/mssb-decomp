#ifndef __GAME_AUTO_00_00167CC4_TEXT_H_
#define __GAME_AUTO_00_00167CC4_TEXT_H_

#include "mssbTypes.h"
#include "main/scene_task.h" // SCENE_TASK_VIEW_HEAD
#include "main/file_80011640.h" // CharActor

// Sparkle-effect scene task (the SceneTask slot from fn_800B0A5C_insertQueue), only the fields used here.
typedef struct SparkleTask {
    /*0x00*/ SCENE_TASK_VIEW_HEAD // SceneTask head (main/scene_task.h)
    /*0x14*/ CharActor* actor;
    /*0x18*/ s16 _18;
    /*0x1A*/ s8 kind; // fn_3_1682AC kind
    /*0x1B*/ u8 done; // sparkles spawned
} SparkleTask;

void fn_3_167CC4(void);
void fn_3_167D4C(void);
void fn_3_167F14(void);
void fn_3_1680D4(void);
void fn_3_1682AC(CharActor* actor, s8 kind);

#endif
