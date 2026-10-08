#include "Unknown/auto_03_800AFFB0_text.h"

extern u8 lbl_803C79D4[];

extern u32 lbl_803C7A00[9];

// fn_800AFFC0, size:0x48
void fn_800AFFC0(u32 count) {
    u32* state = lbl_803C7A00;
    u32 position = state[4] + count;
    state[4] = position;
    if (position >= state[3]) {
        state[4] = position - state[6];
    }
    state[7] -= count;
    state[8] += count;
}

// fn_800AFFB0, size:0x10
u8 fn_800AFFB0(void) {
    return *(u8*)(lbl_803C79D4 + 0x28);
}
