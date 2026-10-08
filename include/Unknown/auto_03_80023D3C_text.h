#ifndef __UNKNOWN_AUTO_03_80023D3C_TEXT_H__
#define __UNKNOWN_AUTO_03_80023D3C_TEXT_H__

#include "mssbTypes.h"
#include "Dolphin/vec.h"

typedef struct VecQueue {
    Vec* entries;
    s32 capacity;
    s32 count;
    s32 head;
    s32 tail;
    s32 cursor;
    s32 step;
} VecQueue;

void fn_80023EEC(VecQueue* queue, Vec* entries, s32 capacity);

s32 fn_80023D4C(VecQueue* queue, Vec* result);

s32 fn_80023DFC(VecQueue* queue, Vec* result);

void fn_80023E48(VecQueue* queue, Vec* value);

u32 fn_80023D3C(void);

void fn_80023D44(u32 value);

s32 fn_80023D98(VecQueue* queue, Vec* result);

#endif
