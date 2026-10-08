#ifndef __UNKNOWN_AUTO_03_800B0A14_TEXT_H__
#define __UNKNOWN_AUTO_03_800B0A14_TEXT_H__

#include "mssbTypes.h"

typedef struct DrawingQueueNode {
    void (*draw)(void);
    struct DrawingQueueNode* previous;
    struct DrawingQueueNode* next;
} DrawingQueueNode;

void fn_800B0A14_removeQueue(void* unused);

void nop_function(void);

#endif
