#include "menus/rep_10C0.h"

extern u8* lbl_2_bss_1A8248[];


// fn_2_9461C, size:0x18
void fn_2_9461C(s16 value) {
    *(s16*)(lbl_2_bss_1A8248[0] + 0x19774A) = value;
}
