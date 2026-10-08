#include "Unknown/auto_03_800213F4_text.h"

extern u8* lbl_803CBC40;

// fn_800213F4, size:0x4
void fn_800213F4(void) {
}

// fn_800213F8, size:0x18
void* fn_800213F8(u32 size) {
    void* result = lbl_803CBC40;
    lbl_803CBC40 += (size + 31) & ~31;
    return result;
}
