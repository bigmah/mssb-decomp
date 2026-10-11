#include "main/file_80091450.h"

// .text:0x80091450 size:0x10
TEXDescriptorPtr TEXGet(TEXPalettePtr pal, u32 id) {
    return &pal->descriptorArray[id];
}

// .text:0x80091460 size:0x18
void DSInitList(void) {
    return;
}

// .text:0x80091478 size:0x94
void DSInsertListObject(void) {
    return;
}

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
void DSInsertBranchBelow(void) {
    return;
}
