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
    SortKeyEntry* arr;
    SortKeyEntry* q;
    SortListNode* n;

    arr = _OSAllocFromHeap(0x20, count << 3);
    q = arr;
    n = list;
    while (n != NULL) {
        q->node = n;
        q->key = n->key;
        q++;
        n = n->next;
    }
    fn_800246D4(fn_3_BA174, (u8*)arr, (u8*)arr, 8, count);
    list = arr[0].node;
    q = arr;
    while (--count != 0) {
        q->node->next = q[1].node;
        q++;
    }
    q->node->next = NULL;
    fn_800ACFB0(arr);
    return list;
}

// .text:0x000BA268 size:0x184 mapped:0x806F92FC
void fn_3_BA268(void) {
    GXSetZMode(1, 3, 1);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(0)->proj, 0);
}

// .text:0x000BA3EC size:0x14C mapped:0x806F9480
void fn_3_BA3EC(void) {
    return;
}

