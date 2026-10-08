#include "Unknown/auto_03_800637BC_text.h"

extern void fn_80063718(void);

// fn_800637BC, size:0x18
s32 fn_800637BC(s32 unused, void** object) {
    *(void (**)(void))((u8*)*object + 0x94) = fn_80063718;
    return 0;
}

// fn_800637D4, size:0x8
s32 fn_800637D4(void) {
    return 0;
}
