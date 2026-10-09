#include "Unknown/auto_03_800B0A14_text.h"

extern u16 lbl_803CC1B0;
extern u16 lbl_803CC1B2;
extern u16 lbl_803CC1B4;
extern u8 lbl_80111300[];
extern u8* lbl_803CC1B8;

extern u8 lbl_803C7A24[];

// fn_800B0A14_removeQueue, size:0x48
void fn_800B0A14_removeQueue(void* unused) {
    if (lbl_803CC1B2 != 0) {
        u8* previous = *(u8**)(lbl_803CC1B8 + 4);
        *(u8**)(previous + 8) = *(u8**)(lbl_803CC1B8 + 8);
        previous = *(u8**)(lbl_803CC1B8 + 8);
        *(u8**)(previous + 4) = *(u8**)(lbl_803CC1B8 + 4);
        *(u32*)lbl_803CC1B8 = 0;
        lbl_803CC1B2--;
    }
}

// nop_function, size:0x4
void nop_function(void) {
}

// fn_800B0C80, size:0x34
void fn_800B0C80(void (*draw)(void)) {
    u8* node;
    s32 remaining;
    if (draw == NULL) {
        draw = nop_function;
    }
    remaining = 3;
    node = lbl_803C7A24;
    do {
        remaining--;
        *(void (**)(void))node = draw;
        node += 0x80;
    } while (remaining != 0);
}

// resetAllDrawingStructs, size:0x98
void resetAllDrawingStructs(void) {
    s32 remaining;
    u8* node;
    u32* slot;
    s32 count;
    node = lbl_803C7A24;
    remaining = 3;
    do {
        *(s32*)(node + 4) = 0;
        *(u8**)(node + 8) = node + 0x40;
        *(u8**)(node + 0xC) = lbl_80111300;
        *(u16*)(node + 0x10) = 0;
        *(u16*)(node + 0x12) = 0;
        *(u8**)(node + 0x44) = node;
        *(s32*)(node + 0x48) = 0;
        *(u8**)(node + 0x4C) = lbl_80111300;
        *(u16*)(node + 0x50) = 0;
        *(u16*)(node + 0x52) = 0xFFFF;
        node += 0x80;
    } while (--remaining != 0);
    slot = (u32*)(lbl_803C7A24 + 0x180);
    count = 0x3A;
    do {
        *slot = 0;
        slot += 0x10;
    } while (--count != 0);
    lbl_803CC1B2 = 0;
    lbl_803CC1B0 = 0;
    lbl_803CC1B4 = 5;
}

// fn_800B0A5C_insertQueue, size:0xD0
void* fn_800B0A5C_insertQueue(void* draw, u16 priority) {
    u8* node;
    u8* prev;
    u8* entry;
    u16 idx;
    s32 i;
    do {
        lbl_803CC1B4++;
        idx = lbl_803CC1B4 & 0x3F;
        lbl_803CC1B4 = idx;
    } while (*(u32*)(lbl_803C7A24 + idx * 0x40) != 0);
    node = lbl_803C7A24 + (lbl_803CC1B0 << 7);
    do {
        node = *(u8**)(node + 8);
    } while (*(u16*)(node + 0x12) < priority);
    prev = *(u8**)(node + 4);
    entry = lbl_803C7A24 + (idx << 6);
    *(u8**)(node + 4) = entry;
    *(u8**)(prev + 8) = entry;
    *(void**)entry = draw;
    *(u8**)(entry + 4) = prev;
    *(u8**)(entry + 8) = node;
    *(u8**)(entry + 0xC) = lbl_803CC1B8;
    *(u16*)(entry + 0x10) = 0;
    *(u16*)(entry + 0x12) = priority;
    *(s32*)(entry + 0x14) = 0;
    lbl_803CC1B2++;
    for (i = 0; i < 5; i++) {
        *(s32*)(entry + 0x1C + i * 8) = 0;
        *(s32*)(entry + 0x18 + i * 8) = 0;
    }
    return entry;
}
