#include "game/rep_1770.h"
#include "header_rep_data.h"

#include "static/UnknownHomes_Static.h"
extern u8 lbl_3_common_bss_32724[];

extern u8 lbl_3_data_D258[];
extern u8 g_Minigame[];

extern u8* lbl_803CC1B8;
extern u8 lbl_80371C30[];
extern void fn_80034E20(void*, void*);
extern u8 lbl_3_data_D378[];
extern u8 g_Batter[];

// .text:0x000993A8 size:0x3C4 mapped:0x806D843C
void fn_3_993A8(void) {
    return;
}

// .text:0x0009976C size:0xAC mapped:0x806D8800
void fn_3_9976C(void) {
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_D378);
    if (g_Batter[0x7B] != 0) {
        *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) << 3)) + 0x5C) = 0;
    } else {
        *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) << 3)) + 0x5C) = 0x10000;
    }
    *(s16*)(p + 0x1C) = 0;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_3_993A8;
}

// .text:0x00099818 size:0x3C4 mapped:0x806D88AC
void fn_3_99818(void) {
    return;
}

// .text:0x00099BDC size:0xAC mapped:0x806D8C70
void fn_3_99BDC(void) {
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_D258);
    if (g_Minigame[0x1A2A] == 2) {
        *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) << 3)) + 0x5C) = 0x30000;
    } else {
        *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) << 3)) + 0x5C) = 0x20000;
    }
    *(s16*)(p + 0x1C) = 0;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_3_99818;
}

// .text:0x00099C88 size:0x74 mapped:0x806D8D1C
void fn_3_99C88(void) {
    u8* p = lbl_803CC1B8;
    u8 v;
    if (lbl_3_common_bss_32724[0x96] == 0 && (v = lbl_3_common_bss_32724[0xA7]) != 0) {
        u32* o = *(u32**)(lbl_80371C30 + *(u16*)(p + 0x14) * 8);
        u32 w = o[0x58 / 4];
        w = v | (w & ~0xFF);
        o[0x58 / 4] = w;
    } else {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x00099CFC size:0x114 mapped:0x806D8D90
void fn_3_99CFC(void) {
    return;
}

// .text:0x00099E10 size:0xA94 mapped:0x806D8EA4
void fn_3_99E10(void) {
    return;
}

// .text:0x0009A8A4 size:0x864 mapped:0x806D9938
void fn_3_9A8A4(void) {
    return;
}

// .text:0x0009B108 size:0x218 mapped:0x806DA19C
void fn_3_9B108(void) {
    return;
}

// .text:0x0009B320 size:0x4D4 mapped:0x806DA3B4
void fn_3_9B320(void) {
    return;
}

// .text:0x0009B7F4 size:0x6EC mapped:0x806DA888
void fn_3_9B7F4(void) {
    return;
}

// .text:0x0009BEE0 size:0x134 mapped:0x806DAF74
void fn_3_9BEE0(void) {
    return;
}

// .text:0x0009C014 size:0x278 mapped:0x806DB0A8
void fn_3_9C014(void) {
    return;
}

// .text:0x0009C28C size:0x2EC mapped:0x806DB320
void fn_3_9C28C(void) {
    return;
}

