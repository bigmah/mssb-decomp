#include "game/rep_3E58.h"
#include "header_rep_data.h"

#include "static/UnknownHomes_Static.h"
extern void fn_3_16689C(void);
extern void fn_3_16699C(void);
#pragma dont_inline on
extern u8 g_Ball[];
extern u8 g_GameLogic[];
extern u8 g_Minigame[];
extern u8 lbl_3_common_bss_35154[];
extern u8* lbl_803CC1B8;
extern u8 lbl_3_data_28508[];
extern s32 lbl_803CBD0C;
extern s32 fn_8001B728(s32, s32, void*);
extern void fn_80026998(void*);
extern int rand(void);
extern void* memset(void*, int, u32);
extern void* memcpy(void*, const void*, u32);

// .text:0x001666B0 size:0x1EC mapped:0x807A5744
void fn_3_1666B0(void) {
    return;
}

// .text:0x0016689C size:0xD0 mapped:0x807A5930
void fn_3_16689C(void) {
    u8* s = (u8*)&g_d_GameSettings;
    if (s[0x55] != 0 || lbl_3_common_bss_35154[0x479] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (g_GameLogic[0x11E] != 2 || g_GameLogic[0x122] != 0 || *(s16*)(g_Ball + 0x1B78) < 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (s[7] == 6 && g_Minigame[0x19A4] != 0) {
        fn_800B0A14_removeQueue(g_Minigame);
        return;
    }
    if (g_Ball[0x1BC9] != 1) {
        fn_800B0A14_removeQueue(g_Ball);
        return;
    }
    fn_3_16699C();
}

// .text:0x0016696C size:0x30 mapped:0x807A5A00
void fn_3_16696C(void) {
    fn_800B0A5C_insertQueue(fn_3_16689C, 0xFFFA);
}

// .text:0x0016699C size:0x294 mapped:0x807A5A30
void fn_3_16699C(void) {
    return;
}

// .text:0x00166C30 size:0x110 mapped:0x807A5CC4
void fn_3_166C30(u8* obj, s8 id) {
    u8 v[0xC];
    u8 buf[0x50];
    memset(v, 0, 0xC);
    memcpy(buf, lbl_3_data_28508, 0x50);
    *(s32*)buf = lbl_803CBD0C;
    if (fn_8001B728(*(s8*)(obj + 0x254), id, v) == 0) {
        memset(v, 0, 0xC);
        fn_8001B728(*(s8*)(obj + 0x254), 4, v);
    }
    memcpy(buf + 0x40, v, 0xC);
    buf[0x4C] = rand() % 256;
    buf[0x4D] = rand() % 256;
    buf[0x4E] = rand() % 256;
    fn_80026998(buf);
}

// .text:0x00166D40 size:0xC4 mapped:0x807A5DD4
void fn_3_166D40(void) {
    u8* st = lbl_803CC1B8;
    void* v = &g_d_GameSettings;
    u8* o;
    s16 c;
    if (*((u8*)&g_d_GameSettings + 0x55) != 0 || (v = lbl_3_common_bss_35154, lbl_3_common_bss_35154[0x479] != 0)) {
        fn_800B0A14_removeQueue(v);
        return;
    }
    if (g_GameLogic[0x11E] != 2) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    o = *(u8**)(st + 0x14);
    c = *(s16*)(o + 0x62);
    if (c == 0x1B || c == 0x1A) {
        o = g_Ball;
        if (g_Ball[0x1BC9] == 0) {
            fn_3_16699C();
            st[0x1B] = 1;
            return;
        }
    }
    if (st[0x1B] != 0) {
        fn_800B0A14_removeQueue(o);
    }
}

// .text:0x00166E04 size:0x1C8 mapped:0x807A5E98
void fn_3_166E04(void) {
    return;
}

// .text:0x00166FCC size:0x1AC mapped:0x807A6060
void fn_3_166FCC(void) {
    return;
}

// .text:0x00167178 size:0x358 mapped:0x807A620C
void fn_3_167178(void) {
    return;
}

// .text:0x001674D0 size:0x3D8 mapped:0x807A6564
void fn_3_1674D0(void) {
    return;
}

// .text:0x001678A8 size:0x41C mapped:0x807A693C
void fn_3_1678A8(void) {
    return;
}

