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
    volatile s32 cursor;
    s32 step;
} VecQueue;

void fn_80023EEC(VecQueue* queue, Vec* entries, s32 capacity);

u32 fn_80023D3C(void);

void fn_80023D44(u32 value);

#endif
