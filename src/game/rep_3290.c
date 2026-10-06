#include "game/rep_3290.h"
#include "header_rep_data.h"

extern void* memset(void*, s32, u32);

extern u8 g_Minigame[];
extern f32 lbl_3_data_21634[];
extern f32 lbl_3_data_219B8[];
extern s16 lbl_3_data_2167C[];
extern f32 lbl_3_data_21674;
typedef struct { f32 x, y, z; } Vec3_3290;
typedef struct { u8 pad0[0x18]; Vec3_3290 vel; } PitcherVel_3290;
extern PitcherVel_3290 g_Pitcher;
typedef struct { u8 pad0[0x28]; u8 s28; u8 pad29; u8 s2a; u8 pad2b; } MgEnt_3290;

extern void fn_3_1500C8(void);
#pragma dont_inline on

// .text:0x001133C4 size:0x338 mapped:0x80752458
void fn_3_1133C4(void) {
    return;
}

// .text:0x001136FC size:0x220 mapped:0x80752790
void fn_3_1136FC(void) {
    return;
}

// .text:0x0011391C size:0x34 mapped:0x807529B0
void fn_3_11391C(void) {
    memset(g_Minigame + 0x1D7C, 0, 0x78);
}

// .text:0x00113950 size:0xF8 mapped:0x807529E4
void fn_3_113950(void) {
    u8* p6 = g_Minigame;
    s16* p7 = (s16*)g_Minigame;
    f32* p8 = (f32*)g_Minigame;
    f32 g = lbl_3_data_21634[2];
    f32 fl = lbl_3_data_219B8[0xE];
    f32 bn = lbl_3_data_21634[3];
    f32 dm = lbl_3_data_21634[4];
    s16 mx = lbl_3_data_2167C[4];
    s32 i;
    for (i = 0; i < 100; i++, p6++, p7++, p8 += 3) {
        if (p6[0x193A] != 0) {
            p7[0xBE4] = p7[0xBE4] + 1;
            p8[0x334] = p8[0x334] + p8[0x460];
            p8[0x335] = p8[0x335] + p8[0x461];
            p8[0x336] = p8[0x336] + p8[0x462];
            p8[0x461] = p8[0x461] - g;
            if (p8[0x335] < fl) {
                p8[0x335] = fl;
                p8[0x461] = -p8[0x461] * bn;
                p8[0x460] = p8[0x460] * dm;
                p8[0x462] = p8[0x462] * dm;
            }
            if (p7[0xBE4] > mx) {
                p6[0x193A] = 0;
            }
        }
    }
}

// .text:0x00113A48 size:0x2D8 mapped:0x80752ADC
void fn_3_113A48(void) {
    return;
}

// .text:0x00113D20 size:0x1A0 mapped:0x80752DB4
void fn_3_113D20(void) {
    return;
}

// .text:0x00113EC0 size:0x54 mapped:0x80752F54
void fn_3_113EC0(void) {
    g_Pitcher.vel.z = -g_Pitcher.vel.z;
    g_Pitcher.vel.x *= lbl_3_data_21674;
    g_Pitcher.vel.y *= lbl_3_data_21674;
    g_Minigame[0x1A81] = 1;
    g_Pitcher.vel.z *= lbl_3_data_21674;
}

// .text:0x00113F14 size:0x2F0 mapped:0x80752FA8
void fn_3_113F14(void) {
    return;
}

// .text:0x00114204 size:0x180 mapped:0x80753298
void fn_3_114204(void) {
    return;
}

// .text:0x00114384 size:0x634 mapped:0x80753418
void fn_3_114384(void) {
    return;
}

// .text:0x001149B8 size:0x74 mapped:0x80753A4C
typedef struct { u8 pad[0x72C]; MgEnt_3290 e[1]; } MgBase_3290;
int fn_3_1149B8(u8* a, u8* b) {
    u8* pa = (u8*)&g_Minigame + *a * 0x2C;
    u8* ea = pa + 0x72C;
    u8 sa = pa[0x754];
    u8* eb = (u8*)&g_Minigame + *b * 0x2C;
    eb += 0x72C;
    if (sa == 3 && eb[0x28] != 3) {
        return -1;
    }
    if (sa != 3 && eb[0x28] == 3) {
        return 1;
    }
    return ea[0x2A] - eb[0x2A];
}

// .text:0x00114A2C size:0x5C mapped:0x80753AC0
void fn_3_114A2C(void) {
    u8 v = g_Minigame[0x1A7F];
    if (v == 0) {
        fn_3_114384();
        fn_3_1500C8();
    } else if (v == 1) {
        fn_3_114204();
    } else if (v == 2) {
        fn_3_113F14();
        fn_3_113D20();
    }
}

// .text:0x00114A88 size:0x538 mapped:0x80753B1C
void fn_3_114A88(void) {
    return;
}

