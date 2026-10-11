#include "game/auto_00_000BA150_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"

extern void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);
extern void* _OSAllocFromHeap(s32 align, s32 size);
extern void fn_800ACFB0(void* block);

// .text:0x000BA150 size:0x24 mapped:0x806F91E4
void fn_3_BA150(void) {
    pitchingMachinePitching(0x19);
}

// .text:0x000BA174 size:0x2C mapped:0x806F9208
s32 fn_3_BA174(void* key, void* elem) {
    SortKeyEntry* a = key;
    SortKeyEntry* b = elem;
    if (a->key < b->key) {
        return 1;
    }
    if (a->key > b->key) {
        return -1;
    }
    return 0;
}

// .text:0x000BA1A0 size:0xC8 mapped:0x806F9234
SortListNode* fn_3_BA1A0(SortListNode* list, s32 count) {
    return 0;
}

// .text:0x000BA268 size:0x184 mapped:0x806F92FC
void fn_3_BA268(void) {
    return;
}

// .text:0x000BA3EC size:0x14C mapped:0x806F9480
void fn_3_BA3EC(void) {
    return;
}

