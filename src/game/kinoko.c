#include "game/kinoko.h"
#include "header_rep_data.h"
#pragma dont_inline on

// .text:0x001695A0 size:0x4
void fn_3_1695A0(void) {
}

extern u8 lbl_3_bss_BA00[];
extern void fn_80011604(s32, void*);
extern void fn_3_16917C(void);

// .text:0x001695A4 size:0x5C
void fn_3_1695A4(s32 a, u8 flag) {
    u8* p = lbl_3_bss_BA00;
    if (flag == 0) {
        *(u8**)p = p + 0xA0;
        *(u8**)(p + 4) = p + 0x2C;
    } else {
        *(u8**)p = p + 0x60;
        *(u8**)(p + 4) = p + 0xC;
    }
    fn_80011604(a, fn_3_16917C);
}

extern u8 lbl_3_data_28928[];
extern u8 lbl_3_bss_BAE0[];
extern void fn_3_16A07C(void);
extern void* memset(void*, s32, u32);
extern void* fn_800B0A5C_insertQueue(void*, s32);

// .text:0x0016C394 size:0x7C
void fn_3_16C394(s8 a) {
    memset(lbl_3_data_28928, 0, 0x19E0);
    memset(lbl_3_bss_BAE0, 0, 0x1BF0);
    lbl_3_data_28928[0x19DC] = a;
    lbl_3_data_28928[0x19DD] = 1;
    *(s32*)(lbl_3_data_28928 + 0x19D4) = 1;
    fn_3_16B884();
    fn_800B0A5C_insertQueue(fn_3_16A07C, 0);
}

// .text:0x00169600 size:0x204 mapped:0x807A8694
void fn_3_169600(void) {
    return;
}

// .text:0x00169804 size:0x180 mapped:0x807A8898
void fn_3_169804(void) {
    return;
}

// .text:0x00169984 size:0x37C mapped:0x807A8A18
void fn_3_169984(void) {
    return;
}

// .text:0x00169D00 size:0x170 mapped:0x807A8D94
void fn_3_169D00(void) {
    return;
}

// .text:0x00169E70 size:0x20C mapped:0x807A8F04
void fn_3_169E70(void) {
    return;
}

// .text:0x0016A07C size:0x140C mapped:0x807A9110
void fn_3_16A07C(void) {
    return;
}

// .text:0x0016B488 size:0x12C mapped:0x807AA51C
void fn_3_16B488(void) {
    return;
}

// .text:0x0016B5B4 size:0x2D0 mapped:0x807AA648
void fn_3_16B5B4(void) {
    return;
}

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
void fn_3_16B884(void) {
    return;
}

