#include "main/file_80091450.h"

// .text:0x80091450 size:0x10
TEXDescriptorPtr TEXGet(TEXPalettePtr pal, u32 id) {
    return &pal->descriptorArray[id];
}

// .text:0x80091460 size:0x18
// NONMATCHING 67%: same instructions, subf scheduled before the first stw
#if NONMATCHING
void DSInitList(DSListPtr list, Ptr obj, DSLinkPtr link) {
    list->Head = NULL;
    list->Tail = NULL;
    list->Offset = (u8*)link - (u8*)obj;
}
#endif

// .text:0x80091478 size:0x94
// NONMATCHING 86%: cursor+Offset folded into lwzx/stwx instead of a shared add
#if NONMATCHING
void DSInsertListObject(DSListPtr list, Ptr cursor, Ptr obj) {
    DSLinkPtr link = (DSLinkPtr)(obj + list->Offset);
    DSLinkPtr cursorLink;
    DSLinkPtr prevLink;

    if (list->Head) {
        if (!cursor) {
            ((DSLinkPtr)(list->Tail + list->Offset))->Next = obj;
            link->Prev = list->Tail;
            link->Next = NULL;
            list->Tail = obj;
            return;
        }
        cursorLink = (DSLinkPtr)(cursor + list->Offset);
        if (cursor == list->Head) {
            list->Head = obj;
            link->Next = cursor;
            cursorLink->Prev = obj;
            return;
        }
        prevLink = (DSLinkPtr)(cursorLink->Prev + list->Offset);
        link->Next = cursor;
        link->Prev = cursorLink->Prev;
        cursorLink->Prev = obj;
        prevLink->Next = obj;
        return;
    }
    list->Tail = obj;
    list->Head = obj;
    link->Prev = NULL;
    link->Next = NULL;
}
#endif

// .text:0x8009150C size:0x50
s8 Strcmp(char* str1, char* str2) {
    for (;;) {
        if (*str1 < *str2) {
            return 1;
        }
        if (*str1 > *str2) {
            return -1;
        }
        str1++;
        str2++;
        if (*str1 == '\0' || *str2 == '\0') {
            return 0;
        }
    }
}

// .text:0x8009155C size:0x14
#pragma scheduling off
void DSInitTree(DSTreePtr tree, Ptr obj, DSBranchPtr branch) {
    tree->Root = NULL;
    tree->Offset = (u8*)branch - (u8*)obj;
}
#pragma scheduling reset

// .text:0x80091570 size:0x98
void DSInsertBranchBelow(DSTreePtr tree, Ptr cursor, Ptr obj) {
    DSBranchPtr branch = (DSBranchPtr)(obj + tree->Offset);
    DSBranchPtr cursorBranch;
    Ptr sibling = NULL;

    if (cursor) {
        cursorBranch = (DSBranchPtr)(cursor + tree->Offset);
        if (cursorBranch->Children) {
            sibling = cursorBranch->Children;
        } else {
            cursorBranch->Children = obj;
        }
    } else {
        if (tree->Root) {
            sibling = tree->Root;
        } else {
            tree->Root = obj;
        }
    }

    if (sibling) {
        while (((DSBranchPtr)(sibling + tree->Offset))->Next) {
            sibling = ((DSBranchPtr)(sibling + tree->Offset))->Next;
        }
        ((DSBranchPtr)(sibling + tree->Offset))->Next = obj;
        branch->Prev = sibling;
    } else {
        branch->Prev = NULL;
    }
    branch->Next = NULL;
    branch->Parent = cursor;
}
