#include "game/rep_3290.h"
#include "header_rep_data.h"
#include "stl/math.h"

extern void* memset(void*, s32, u32);

extern u8 g_Minigame[];
extern s16 lbl_3_data_21654[];
extern u8 lbl_3_data_21694[];
extern u8 lbl_3_data_216B0[];
extern u8 lbl_3_data_216B8[];
extern s32 RandomInt_Game(s32);
extern s32 RandomInt_Game_Range(s32, s32);
extern f32 lbl_3_data_21634[];
extern f32 lbl_3_data_219B8[];
extern s16 lbl_3_data_2167C[];
extern f32 lbl_3_data_21674;
typedef struct { f32 x, y, z; } Vec3_3290;
typedef struct { u8 pad0[0x18]; Vec3_3290 vel; } PitcherVel_3290;
extern PitcherVel_3290 g_Pitcher;
typedef struct { u8 pad0[0x28]; u8 s28; u8 pad29; u8 s2a; u8 pad2b; } MgEnt_3290;

extern void fn_3_1500C8(void);
extern f32 lbl_3_data_215C8[];
extern f32 lbl_3_data_21688[];
extern void fn_8004C108(f32*, s32);
extern void fn_3_90064(s32);
#pragma dont_inline on

// .text:0x001133C4 size:0x338 mapped:0x80752458
void fn_3_1133C4(void) {
    return;
}

// .text:0x001136FC size:0x220 mapped:0x80752790
void fn_3_1136FC(void) {
    u8* p;
    u8 d;
    s8 i;
    s16 lo;
    u8* g;
    s16 hi;
    s8 k;
    g = g_Minigame;
    i = 0;
    lo = 0;
    hi = 0x7FFF;
    p = g;
    k = 0;
    d = g[(s8)g[0x1904] + 0x18DC];
    do {
        u8* e = g + p[0x1A82] * 0x2C;
        lo += *(s16*)(e + 0x750);
        if (e[0x755] == 2) {
            k = i;
            i++;
            break;
        }
        i++;
        p++;
    } while (i < 7);
    if (i < 7) {
        s16 w = *(s16*)(g_Minigame + g_Minigame[0x1A82 + i] * 0x2C + 0x750);
        hi = lo + w - 1;
    }
    if (RandomInt_Game(0x64) < (s8)(lbl_3_data_21694 + d * 7)[k]) {
        s8* q = (s8*)lbl_3_data_216B0 + d * 2;
        s16 r = RandomInt_Game_Range(*(s8*)(lbl_3_data_216B0 + d * 2), q[1]);
        lo += r;
        hi += r;
    }
    if (lo <= lbl_3_data_21654[2] && lbl_3_data_21654[2] <= hi) {
        g[0x1DCE] = 0;
    } else if (lo <= lbl_3_data_21654[3] && lbl_3_data_21654[3] <= hi) {
        g[0x1DCE] = 3;
    } else if (hi >= lbl_3_data_21654[0] && lo <= lbl_3_data_21654[1]) {
        g[0x1DCE] = 2;
        if (lo < lbl_3_data_21654[0]) {
            lo = lbl_3_data_21654[0];
        }
        if (hi > lbl_3_data_21654[1]) {
            hi = lbl_3_data_21654[1];
        }
        *(s16*)(g + 0x1DCC) = RandomInt_Game_Range(lo, hi);
    } else {
        g[0x1DCE] = 1;
    }
    if (g[0x1DCE] == 0 && RandomInt_Game(0x64) < (s8)lbl_3_data_216B8[d]) {
        g[0x1DCE] = 1;
    }
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
    u8* p;
    f32* e;
    int i;
    s8 flag;
    f32 a;
    f32 n;
    s8 dir;
    p = g_Minigame;
    flag = 0;
    for (i = 0; i < 7; i++) {
        p = g_Minigame + i * 0x2C;
        e = (f32*)(p + 0x72C);
        a = e[6];
        if (a != 0.0f || e[7] != 0.0f) {
            e[6] = e[7] * cos(a) + e[6];
            n = e[6];
            if (n >= 0.0f) {
                dir = -1;
            } else {
                dir = 1;
            }
            if (a < n) {
                if (a < 0.0f && n >= 0.0f) {
                    flag = 1;
                }
            } else if (a > 0.0f) {
                if (n <= 0.0f) {
                    flag = 1;
                }
            }
            if (flag) {
                e[7] = e[7] * lbl_3_data_21688[2];
                if (fabs(e[7]) < e[8] * lbl_3_data_21688[2]) {
                    e[8] = 0.0f;
                    e[7] = 0.0f;
                    e[6] = 0.0f;
                }
                flag = 0;
            }
            e[7] = dir * e[8] + e[7];
        }
    }
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
int fn_3_1149B8(u8* a, u8* b) {
    MgEnt_3290* ea = (MgEnt_3290*)(g_Minigame + 0x72C + *a * 0x2C);
    MgEnt_3290* eb = (MgEnt_3290*)(g_Minigame + 0x72C + *b * 0x2C);
    if (ea->s28 == 3 && eb->s28 != 3) {
        return -1;
    }
    if (ea->s28 != 3 && eb->s28 == 3) {
        return 1;
    }
    return ea->s2a - eb->s2a;
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

