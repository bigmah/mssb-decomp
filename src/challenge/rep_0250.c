#include "challenge/rep_0250.h"

extern void fn_1_973C(void* object);
extern void fn_1_9380(void* object);
#include "static/UnknownHomes_Static.h"
extern void fn_1_8F34(void* object);
extern u8* lbl_803CC1B8[];
extern u8 lbl_1_bss_2FAA;
extern u8 lbl_1_bss_2FB9;
extern void* fn_80034CEC(void*);

// .text:0x96D0 size:0x4
void fn_1_96D0(void) {
}

void fn_1_90B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_8F34, 2);
}

void fn_1_96A4(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_9380, 2);
}

void fn_1_97B8(void) {
    fn_800B0A5C_insertQueue((void*)fn_1_973C, 2);
}

// .text:0x96D4 size:0x68
void fn_1_96D4(void) {
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if ((lbl_803C77B8._02 & 1) || (lbl_803C77B8._02 & 2)) {
        fn_800B0A14_removeQueue(fn_80034CEC(queue));
    }
    lbl_1_bss_2FB9 = lbl_1_bss_2FAA;
}
