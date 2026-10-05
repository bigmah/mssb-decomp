#include "game/rep_2308.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1F58.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_8036E548[];
extern u8 lbl_3_common_bss_35154[];
extern f32 lbl_3_rodata_2388;

// .text:0x000CABF0 size:0x210 mapped:0x80709C84
void fn_3_CABF0(void) {
    return;
}

// .text:0x000CAE00 size:0x19C mapped:0x80709E94
extern u8* lbl_803CC1B8;
extern u8 lbl_803CBBC0;
extern u8 lbl_80366158[];
extern u8 lbl_3_data_17D10[];
extern void fn_800A7D4C(int, void*);

typedef struct {
    u32 a, b, c, d;
} Q2308;
typedef struct {
    u8 pad0[8];
    f32 f8, fC, f10;
    Q2308 q14;
    u32 w24;
} E2308;
typedef struct {
    E2308 e[2];
} R2308;
extern R2308 lbl_3_data_17D18[];

void fn_3_CAE00(void) {
    u8* p = lbl_803CC1B8;
    u8* t = ((u8**)(lbl_8036E548 + 0x2C50))[p[0x33]];
    if (p[0x34] == 0 && t != 0) {
        fn_800A7D4C(0, &lbl_3_data_17D18[p[0x32]].e[lbl_803CBBC0]);
        lbl_3_data_17D18[p[0x32]].e[lbl_803CBBC0].w24 = *(u16*)(p + 0x30);
        lbl_3_data_17D18[p[0x32]].e[lbl_803CBBC0].f8 = *(f32*)(p + 0x14);
        lbl_3_data_17D18[p[0x32]].e[lbl_803CBBC0].fC = *(f32*)(p + 0x18);
        lbl_3_data_17D18[p[0x32]].e[lbl_803CBBC0].f10 = *(f32*)(p + 0x1C);
        {
            E2308* e = &lbl_3_data_17D18[p[0x32]].e[lbl_803CBBC0];
            e->q14 = *(Q2308*)(p + 0x20);
        }
        if (lbl_80366158[0x28] == 0) {
            *(u16*)(p + 0x30) += 1;
        }
    } else {
        *(u32*)(lbl_3_data_17D10 + p[0x32] * 4) = 0;
        fn_800B0A14_removeQueue(lbl_3_data_17D10);
    }
    if (*(u16*)(p + 0x30) >= *(u16*)(lbl_3_common_bss_35154 + 0xF0)) {
        *(u32*)(lbl_3_data_17D10 + p[0x32] * 4) = 0;
        fn_800B0A14_removeQueue(lbl_3_data_17D10);
    }
}

// .text:0x000CAF9C size:0x214 mapped:0x8070A030
void fn_3_CAF9C(void) {
    return;
}

// .text:0x000CB1B0 size:0x84 mapped:0x8070A244
void fn_3_CB1B0(int a, u8 b, int c) {
    u8* p;
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        if (c == 0x23) {
            lbl_3_common_bss_35154[0x467] = b;
            p = ((u8**)(lbl_8036E548 + 0x2C50))[a];
            *(f32*)(lbl_3_common_bss_35154 + 0x428) = *(f32*)(p + 0x34);
            *(f32*)(lbl_3_common_bss_35154 + 0x42C) = -*(f32*)(p + 0x38);
            *(f32*)(lbl_3_common_bss_35154 + 0x430) = *(f32*)(p + 0x3C);
            *(u32*)(lbl_3_common_bss_35154 + 0x3AC) |= 0x10;
        }
    }
}

// .text:0x000CB234 size:0x50 mapped:0x8070A2C8
void fn_3_CB234(int a, int b) {
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        ((void (*)(int, int))fn_3_C11CC)(a, b);
    }
}

// .text:0x000CB284 size:0xC0 mapped:0x8070A318
void fn_3_CB284(int a, int c, f32 f) {
    u8* p;
    u8* b;
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        b = lbl_3_common_bss_35154;
        if ((s8)b[0x467] != 0 && c == 0x23) {
            p = ((u8**)(lbl_8036E548 + 0x2C50))[a];
            *(f32*)(b + 0x428) = *(f32*)(p + 0x34);
            *(f32*)(b + 0x42C) = -*(f32*)(p + 0x38);
            *(f32*)(b + 0x430) = *(f32*)(p + 0x3C);
            *(u32*)(b + 0x3AC) |= 0x10;
        }
        ((void (*)(int, int, f32, f32))fn_3_C1344)(a, c == 0x1E, lbl_3_rodata_2388 * f, lbl_3_rodata_2388);
    }
}

