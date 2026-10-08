#include "menus/rep_0DE0.h"


extern u8* lbl_2_bss_1A8248[];

// .text:0x87114 size:0x4
void fn_2_87114(void) {
}

// fn_2_870D4, size:0x40
void fn_2_870D4(f32 value) {
    if (value) {
        lbl_2_bss_1A8248[0][0x307A] = 3;
    } else {
        lbl_2_bss_1A8248[0][0x307A] = 0;
    }
}
