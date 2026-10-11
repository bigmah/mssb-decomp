#ifndef __CHALLENGE_AUTO_00_00017EFC_TEXT_H_
#define __CHALLENGE_AUTO_00_00017EFC_TEXT_H_

#include "mssbTypes.h"

// Singly linked list node sorted by fn_1_17F28 (by `depth`, largest first).
typedef struct ChSortNode {
    /*0x0*/ struct ChSortNode* next;
    /*0x4*/ u8 _4[8];
    /*0xC*/ f32 depth;
} ChSortNode;

// Sort record: a node and its key.
typedef struct ChSortEntry {
    /*0x0*/ ChSortNode* node;
    /*0x4*/ f32 key;
} ChSortEntry;

s32 fn_1_17EFC(void* a, void* b);
ChSortNode* fn_1_17F28(ChSortNode* head, s32 count);
void fn_1_17FF0(void);
void fn_1_18174(void);

#endif
