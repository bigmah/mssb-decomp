#ifndef __GAME_AUTO_00_000BA150_TEXT_H_
#define __GAME_AUTO_00_000BA150_TEXT_H_

#include "mssbTypes.h"

// Particle-style linked list node sorted by fn_3_BA1A0 (only the link and sort key are known).
typedef struct SortListNode {
    struct SortListNode* next; // 0x00
    u8 pad4[0xC - 0x4];
    f32 key; // 0x0C
} SortListNode;

typedef struct SortKeyEntry {
    SortListNode* node;
    f32 key;
} SortKeyEntry;

void fn_3_BA150(void);
s32 fn_3_BA174(void* key, void* elem);
SortListNode* fn_3_BA1A0(SortListNode* list, s32 count);
void fn_3_BA268(void);
void fn_3_BA3EC(void);

#endif
