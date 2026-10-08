#include "Unknown/auto_03_8004CC18_text.h"

extern u8 lbl_803C5F74[];

// fn_8004CC18, size:0x14
void fn_8004CC18(void) {
    *(u8*)(lbl_803C5F74 + 0x3) = 0x4;
}

// fn_8004CC2C, size:0x20
void fn_8004CC2C(void) {
    if (lbl_803C5F74[3] != 4) {
        lbl_803C5F74[3] = 3;
    }
}

// fn_8004CC4C, size:0x74
void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, s16 value) {
    u8* state = lbl_803C5F74;
    if (state[0] == 0) {
        state[1] = first;
        state[2] = third;
        state[3] = 0;
        state[4] = second;
        state[0x1E] = 0;
        *(s16*)(state + 6) = 0;
        *(s16*)(state + 0xE) = -1;
        *(s16*)(state + 8) = 0;
        *(s16*)(state + 0x10) = -1;
        *(s16*)(state + 0xA) = 0;
        *(s16*)(state + 0x12) = -1;
        *(s16*)(state + 0xC) = 0;
        *(s16*)(state + 0x14) = -1;
        state[0x1B] = 0;
        state[0x1C] = 0;
        if (selection >= 0) {
            state[0x1A] = selection;
            *(s16*)(state + 0x18) = value;
            return;
        }
        *(s8*)(state + 0x1A) = -1;
    }
}
