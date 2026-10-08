#include "Unknown/auto_03_8001E460_text.h"

extern void* lbl_803CB7AC[2];

extern u8 lbl_803CBBC0;

// fn_8001E460, size:0x14
void fn_8001E460(void* value) {
    lbl_803CB7AC[lbl_803CBBC0] = value;
}

// fn_8001E474, size:0x14
void fn_8001E474(void) {
    lbl_803CB7AC[0] = 0;
    lbl_803CB7AC[1] = 0;
}
