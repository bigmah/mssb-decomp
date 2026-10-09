#include "challenge/rep_0250.h"


extern void fn_1_9380(void* object);
#include "static/UnknownHomes_Static.h"
extern void fn_1_8F34(void* object);
extern u8* lbl_803CC1B8[];
extern u8 lbl_1_bss_2FAA;
extern u8 lbl_1_bss_2FB9;
extern void* fn_80034CEC(void*);
extern u8 lbl_1_data_B88[];
extern u8* lbl_80371C30[];
extern void fn_80034E20(void*, void*);
extern u8 lbl_1_data_CC8[];
extern u16 lbl_1_bss_2FAC;
extern u8* lbl_1_bss_2FCC;
extern s16* fn_80035F20(u8, s32, u16, s16);
extern void fn_80035ED0(s32);
extern void fn_80035EEC(s32, s32);
extern u8 lbl_1_bss_2FA8[];

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

// .text:0x973C size:0x7C
void fn_1_973C(void* object) {
    u8* queue = *(u8**)lbl_803CC1B8;
    fn_80034E20(queue, lbl_1_data_B88);
    *(u8*)(lbl_80371C30[*(u16*)(queue + 0x14) * 2] + 0x66) = lbl_1_bss_2FAA;
    *(u16*)(queue + 0x18) = 0;
    **(void***)lbl_803CC1B8 = (void*)fn_1_96D4;
}

// .text:0x8CD4 size:0x78
void fn_1_8CD4(void) {
    s16* result = fn_80035F20(lbl_1_data_CC8[0x14], 1, lbl_1_bss_2FAC, (s16)(lbl_1_bss_2FAC + 2));
    *(f32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2] + 0x48) = result[0x14 / 2];
    *(f32*)(lbl_80371C30[*(u16*)(lbl_1_bss_2FCC + 0x14) * 2] + 0x4C) = result[0x16 / 2];
    fn_80035ED0(1);
    lbl_1_bss_2FAC += 1;
    if (lbl_1_bss_2FAC > 3) {
        lbl_1_bss_2FAC = 0;
    }
}

// .text:0x9290 size:0xF0
void fn_1_9290(void) {
    u8* b = lbl_1_bss_2FA8;
    u8* queue = *(u8**)lbl_803CC1B8;
    *(u16*)(queue + 0x18) += 1;
    if (b[7] == 0) {
        fn_80035EEC(3, 0);
        fn_80035EEC(7, 1);
        fn_80035ED0(2);
    } else if (b[7] == 1) {
        fn_80035EEC(0xB, 0);
        fn_80035EEC(0xF, 1);
        fn_80035EEC(0x13, 2);
    } else {
        fn_80035ED0(2);
        fn_80035ED0(3);
    }
    if (b[0x11] != (s8)b[2]) {
        fn_800B0A14_removeQueue(fn_80034CEC(queue));
    }
    if (lbl_803C77B8._02 & 0x200) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}
