#include "game/rep_2308.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1F58.h"
#include "game/rep_3AE8.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_8036E548[];
extern u8 lbl_3_common_bss_35154[];
extern f32 lbl_3_rodata_2388;
extern f32 lbl_3_rodata_2378;
extern f32 lbl_3_rodata_235C;
extern f64 lbl_3_rodata_2380;
extern u8 lbl_3_data_17D08[];
extern u8 lbl_3_data_17D10[];
#include "Dolphin/mtx.h"
#include "stl/fdlibm.h"
extern void* memcpy(void*, const void*, u32);

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
    Vec a;
    Vec b;
    Vec c;
    u8* q;
    s32 n;
    s32 i;
    u8** slot;
    q = fn_800B0A5C_insertQueue(fn_3_CAE00, 1);
    *(u16*)(q + 0x30) = 0;
    q[0x33] = g_Pitcher.rosterID;
    memcpy(&a, &g_Pitcher, 0xC);
    memcpy(&b, &g_Pitcher.ballVelocity, 0xC);
    memcpy(&c, &g_Pitcher.pitchCurveVeloV1, 0xC);
    n = *(s32*)(lbl_3_data_17D08 + 4);
    while (n-- != 0) {
        ((void (*)(Vec*, Vec*, Vec*, int))fn_3_15C024)(&a, &b, &c, 0);
    }
    *(f32*)(q + 0x14) = a.x;
    *(f32*)(q + 0x18) = -a.y;
    *(f32*)(q + 0x1C) = a.z;
    a.x = a.x - g_Pitcher.ballCurrentPosition.x;
    a.y = a.y - g_Pitcher.ballCurrentPosition.y;
    a.z = a.z - g_Pitcher.ballCurrentPosition.z;
    a.y = -a.y;
    PSVECNormalize(&a, &a);
    b.x = lbl_3_rodata_2378; b.y = 0.0f; b.z = 0.0f;
    PSVECCrossProduct(&b, &a, (Vec*)(q + 0x20));
    *(f32*)(q + 0x2C) = acos(PSVECDotProduct(&b, &a)) / 2.0;
    if (PSVECMag((Vec*)(q + 0x20))) {
        PSVECNormalize((Vec*)(q + 0x20), (Vec*)(q + 0x20));
        PSVECScale((Vec*)(q + 0x20), sin(*(f32*)(q + 0x2C)), (Vec*)(q + 0x20));
    }
    *(f32*)(q + 0x2C) = cos(*(f32*)(q + 0x2C));
    q[0x34] = i = 0;
    slot = (u8**)lbl_3_data_17D10;
    for (; i < 2; slot++, i++) {
        if (*slot == 0) {
            ((u8**)lbl_3_data_17D10)[i] = q;
            q[0x32] = i;
            break;
        }
    }
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

