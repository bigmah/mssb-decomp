#ifndef __MAIN_FILE_800B0724_H__
#define __MAIN_FILE_800B0724_H__

#include "mssbTypes.h"
#include "main/file_80063028.h"

void fn_800B0934(void);

typedef struct DrawingQueueNode {
    void (*draw)(void);
    struct DrawingQueueNode* previous;
    struct DrawingQueueNode* next;
} DrawingQueueNode;

void fn_800B0A14_removeQueue(void* unused);

void nop_function(void);

void fn_800B0C80(void (*draw)(void));

void resetAllDrawingStructs(void);

void* fn_800B0A5C_insertQueue(void* draw, u16 priority);

void fn_800B0D28(void* value);

void fn_800B0D38(s32 index, s32 value);

void fn_800B117C(u8 value);

void fn_800B2160(u8 value);

s32 fn_800B216C(u8 flag, u32 mode, u8 index);

void fn_800B21A8(s32 mode);

void fn_800B2B4C(GameActor* actor, f32 value);void fn_800B2B54(GameActor* actor, u16 bone, u8 value);

void Set_FUN_800b2b6c(GameActor* actor, s32 value);void fn_800B2B74(GameActor* actor, u16 bone);

#endif
