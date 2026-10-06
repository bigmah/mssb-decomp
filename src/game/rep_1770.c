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
extern u8 lbl_3_data_D4F8[];
extern u8 g_Pitcher[];
extern void playSoundEffect(int);
extern u8 g_Batter[];
extern s32 g_Strikes[];
extern void fn_8003649C(void*, s32, s32, s32, s32);

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
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_D4F8);
    if (!(g_Batter[0xAB] & 1)) {
        u8* e = lbl_80371C30;
        u32* o;
        e += *(u16*)(p + 0x14) << 3;
        o = *(u32**)(e + 0x18);
        o[0x54 / 4] &= ~2;
    }
    if (!(g_Batter[0xAB] & 2)) {
        u8* e = lbl_80371C30;
        u32* o;
        e += *(u16*)(p + 0x14) << 3;
        o = *(u32**)(e + 0x10);
        o[0x54 / 4] &= ~2;
    }
    if (!(g_Batter[0xAB] & 4)) {
        u8* e = lbl_80371C30;
        u32* o;
        e += *(u16*)(p + 0x14) << 3;
        o = *(u32**)(e + 0x8);
        o[0x54 / 4] &= ~2;
    }
    if (g_Pitcher[0x159] == 0 && g_Pitcher[0x15A] == 0) {
        playSoundEffect(0x1AB);
    }
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_3_99C88;
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
void fn_3_9BEE0(u8* p) {
    s32 target = g_Strikes[2];
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        target = g_Minigame[0x190D] - g_Minigame[0x1910];
    }
    for (i = 0; i < 7; i++) {
        s32 state = 3;
        if (g_d_GameSettings.GameModeSelected == 6 && i >= 5) {
            break;
        }
        if (i < 2) {
            if (*(u16*)(p + 0x1C) == g_Strikes[0]) {
                continue;
            }
            if (g_Strikes[0] >= i + 1) {
                state = 0;
            }
        } else if (i < 5) {
            if (*(u16*)(p + 0x1E) == g_Strikes[1]) {
                continue;
            }
            if (g_Strikes[1] >= i - 1) {
                state = 1;
            }
        } else {
            if (*(u16*)(p + 0x20) == target) {
                continue;
            }
            if (target >= i - 4) {
                state = 2;
            }
        }
        fn_8003649C(p, i + 1, i + 1, 0x107, state);
    }
    *(u16*)(p + 0x1C) = g_Strikes[0];
    *(u16*)(p + 0x1E) = g_Strikes[1];
    *(u16*)(p + 0x20) = target;
}

// .text:0x0009C014 size:0x278 mapped:0x806DB0A8
void fn_3_9C014(void) {
    return;
}

// .text:0x0009C28C size:0x2EC mapped:0x806DB320
void fn_3_9C28C(void) {
    return;
}

