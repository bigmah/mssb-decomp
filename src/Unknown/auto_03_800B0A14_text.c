#include "Unknown/auto_03_800B0A14_text.h"

extern u16 lbl_803CC1B2;
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
