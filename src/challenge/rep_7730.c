#include "challenge/rep_7730.h"

extern f32 lbl_1_bss_6BE4[4];

// .text:0x1DE5C size:0x4
void fn_1_1DE5C(void) {
}

// .text:0x1E28C size:0x4
void fn_1_1E28C(void) {
}

void fn_1_1DDE4(f32 value) {
    lbl_1_bss_6BE4[3] = value;
}

void fn_1_1DDF4(f32 value) {
    lbl_1_bss_6BE4[2] = value;
}

void fn_1_1DE04(f32 value) {
    lbl_1_bss_6BE4[1] = value;
}

void fn_1_1DE14(f32 value) {
    lbl_1_bss_6BE4[0] = value;
}

f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}
