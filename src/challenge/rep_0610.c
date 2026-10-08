#include "challenge/rep_0610.h"

extern void* lbl_1_bss_3098[];
extern u8 lbl_1_bss_3215;
extern u8 lbl_1_bss_3214;
extern u8 lbl_1_bss_30B8;

// .text:0x163FC size:0x4
void fn_1_163FC(void) {
}

void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

void fn_1_D650(void) {
    lbl_1_bss_3214 = 1;
}

void fn_1_D67C(u8 value) {
    lbl_1_bss_3215 = value;
}

void fn_1_106B4(void) {
    lbl_1_bss_3098[0] = 0;
}
