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

