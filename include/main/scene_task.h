#ifndef __MAIN_SCENE_TASK_H__
#define __MAIN_SCENE_TASK_H__

#include "mssbTypes.h"

struct DrawNode; // main/file_80069BDC.h

// Loaded resource handle (freed with fn_800ACF14); data is the loaded file.
typedef struct ResHandle {
    /*0x0*/ void* data;
} ResHandle;

// Scene/task object (lbl_803CC1B8 is the current one). Tasks that own a run of sprite/layout
// objects in lbl_80371C30 keep its start and length in u14.
typedef struct SceneTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct SceneTask* prev; // draw-queue links (fn_800B0A5C_insertQueue)
    /*0x08*/ struct SceneTask* next;
    /*0x0C*/ struct SceneTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ union {
        ResHandle* res;
        struct {
            u16 objIdx;   // first object in lbl_80371C30
            u16 objCount; // number of objects
        };
        f32 rate; // per-frame step (menus fn_2_A70 volume fade)
    } u14;
    /*0x18*/ struct DrawNode* nodes;
    /*0x1C*/ void* player;
    /*0x20*/ void* work;
    /*0x24*/ void* buffer;
    /*0x28*/ void* res28;
    /*0x2C*/ u8 _2C[0x30 - 0x2C];
    /*0x30*/ u32 voice;
    /*0x34*/ s16 state;
    /*0x36*/ u16 _36;
    /*0x38*/ u8 _38;
    /*0x39*/ u8 _39;
    /*0x3A*/ u8 _3A;
    /*0x3B*/ u8 _3B;
    /*0x3C*/ s8 volStep;
} SceneTask;

// Owners of sprite (spani) and layout object runs are scene tasks.
typedef SceneTask SpaniOwner;
typedef SceneTask SpaniGroup;
typedef SceneTask LayoutOwner;

#endif
