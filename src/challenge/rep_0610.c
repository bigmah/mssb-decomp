#include "challenge/rep_0610.h"

extern u8 lbl_1_bss_3216[];
extern void fn_1_1496C(u8* object);
#include "static/UnknownHomes_Static.h"
extern void fn_1_10560(void* object);
extern void* lbl_1_bss_3098[];
extern u8 lbl_1_bss_3215[];
extern u8 lbl_1_bss_3214[];
extern u8 lbl_1_bss_30B8;

// .text:0x163FC size:0x4
void fn_1_163FC(void) {
}

void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

void fn_1_D650(void) {
    lbl_1_bss_3214[0] = 1;
}

void fn_1_D67C(u8 value) {
    lbl_1_bss_3215[0] = value;
}

void fn_1_106B4(void) {
    lbl_1_bss_3098[0] = 0;
}

void* fn_1_106A4(void) {
    return lbl_1_bss_3098[0];
}

void fn_1_10670(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_10560, 11);
    *(s16*)(object + 0x10) = 0;
}

void fn_1_176EC(u8* object) {
    fn_1_1496C(object);
}

u8 fn_1_D638(void) {
    u8 flag = lbl_1_bss_3214[0];
    lbl_1_bss_3214[0] = 0;
    return flag;
}

s32 fn_1_D660(void) {
    return lbl_1_bss_3215[0] != 0;
}

void fn_1_D688(void) {
    lbl_1_bss_3216[0]++;
    if (lbl_1_bss_3216[0] == 3) lbl_1_bss_3216[0] = 0;
}
