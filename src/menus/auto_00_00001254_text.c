#include "menus/auto_00_00001254_text.h"

// fn_2_8780, size:0x14
s32 fn_2_8780(s32 mode) {
    if (mode != 0) {
        return 0x13;
    }
    return 9;
}

// fn_2_8794, size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}
