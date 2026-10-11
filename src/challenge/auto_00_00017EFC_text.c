#include "challenge/auto_00_00017EFC_text.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"

extern void* _OSAllocFromHeap(s32 align, s32 size);
extern void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);

// .text:0x00017EFC size:0x2C
// Sort comparator for ChSortEntry: descending key.
s32 fn_1_17EFC(void* a, void* b) {
    if (((ChSortEntry*)a)->key < ((ChSortEntry*)b)->key) {
        return 1;
    }
    if (((ChSortEntry*)a)->key > ((ChSortEntry*)b)->key) {
        return -1;
    }
    return 0;
}

// .text:0x00017F28 size:0xC8
// Sorts a list of `count` (> 0) nodes by depth, back to front, and returns the new head.
ChSortNode* fn_1_17F28(ChSortNode* head, s32 count) {
    ChSortEntry* entries;
    ChSortEntry* e;
    ChSortNode* node;

    entries = _OSAllocFromHeap(0x20, count * sizeof(ChSortEntry));
    for (e = entries, node = head; node != NULL; node = node->next, e++) {
        e->node = node;
        e->key = node->depth;
    }
    fn_800246D4(fn_1_17EFC, (u8*)entries, (u8*)entries, sizeof(ChSortEntry), count);
    head = entries[0].node;
    e = entries;
    while (--count != 0) {
        e->node->next = e[1].node;
        e++;
    }
    e->node->next = NULL;
    fn_800ACFB0(entries);
    return head;
}

