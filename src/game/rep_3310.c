#include "game/rep_3310.h"
#include "game/rep_1D58.h"
#include "game/rep_1C0.h"
#include "header_rep_data.h"

extern f32 lbl_3_data_2262C;
extern f32 lbl_3_data_22650[];
extern u8 lbl_3_data_22670[];
extern u8 lbl_3_data_2265C[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_8036E548[];
extern u8 g_GameLogic[];
extern u8 g_Pitcher[];
extern u8 lbl_80366158[];
extern s16 lbl_3_data_217A4[];
extern void fn_3_90064(s32);
typedef struct Z90 { u8 pad[0x34]; u8* a; u8 pad2[0x90 - 0x38]; } Z90;
extern f32 lbl_3_data_21A48[];
extern void fn_8001D0D0(int, f32);
extern f32 shortAngleToRad(s16 ang);
extern u8 g_d_GameSettings[];
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern void fn_80035B50(int);
extern void fn_80018B38(void);
extern void fn_3_909B0(void);
extern void fn_3_9081C(void);
extern void fn_800BDC88(void* p, u16 a, u16 b, u32 c, s32 d, s32 e);
extern void fn_800BD548(void* p, s32 n, ...);
extern void fn_80034E20(void*, void*);
extern void* lbl_803CC1B8[];
extern u8 lbl_80371C30[];
extern u8 lbl_3_data_69D0[];
extern void fn_80024DB0(void*);
extern void* fn_80034CEC(void*);
extern void fn_800B0A14_removeQueue(void*);
extern void fn_80024FA4(void*, u32, void*, int);
extern void CTRLSetTranslation(void* c, f32 x, f32 y, f32 z);
extern void CTRLSetRotation(void* c, f32 x, f32 y, f32 z);

// .text:0x00116840 size:0x190 mapped:0x807558D4
void fn_3_116840(void) {
    return;
}

// .text:0x001169D0 size:0x168 mapped:0x80755A64
void fn_3_1169D0(void) {
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x275E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2416] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x252E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2646] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2786] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x289E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x29B6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x243E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2556] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x266E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x27AE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x28C6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x29DE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2466] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x257E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2696] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x27D6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x28EE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2A06] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x248E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x25A6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x26BE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x27FE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2916] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2A2E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x24B6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x25CE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x26E6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2826] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x293E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2A56] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x24DE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x25F6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x270E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x284E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2966] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2A7E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2506] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x261E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2736] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2876] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x298E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0x2AA6] = 0;
}

// .text:0x00116B38 size:0x3C mapped:0x80755BCC
extern u8 g_Minigame[];
extern u8 lbl_8036E548[];
extern u8 g_d_GameSettings[];
typedef struct { u8 pad[0x34]; void* p; u8 pad2[0x90 - 0x38]; } Ent90;
extern f32 fn_800B4A94(void* p);

typedef struct { u8 pad[0x26]; u8 f; u8 pad2[1]; } E28;
void fn_3_116B38(void) {
    s32 i = 2;
    if (g_Minigame[0x1A2A] == 3) {
        i = 0x1F;
    }
    ((E28*)*(u8**)(lbl_8036E548 + 0x2D94))[i].f = 0;
}

// .text:0x00116B74 size:0x8A8 mapped:0x80755C08
void fn_3_116B74(void) {
    return;
}

// .text:0x0011741C size:0x78 mapped:0x807564B0
void fn_3_11741C(s32 i) {
    u8* t = (*(Z90**)(lbl_8036E548 + 0x68))[i].a;
    s32 off;
    s32 k;
    s32 v = g_Minigame[0xCCE] == 1 ? 0 : 2;
    for (k = 0, off = 0; k < *(u16*)(t + 6); k++, off += 4) {
        u8* q = *(u8**)(*(u8**)(t + 0x18) + off);
        q = *(u8**)(q + 0x14);
        q = *(u8**)(q + 8);
        *(s16*)(*(u8**)(q + 0xC) + 0x20) = v;
    }
}

// .text:0x00117494 size:0xF4 mapped:0x80756528
extern const f32 lbl_3_rodata_33C0;
extern const f32 lbl_3_rodata_33C4;
extern const f32 lbl_3_rodata_33C8;

void fn_3_117494(void) {
    u8* g = g_Minigame;
    u8* p = *(u8**)(lbl_8036E548 + 0x2D94);
    p[0x252E] = 0;
    p[0xFEE] = 0;
    *(void**)(p + 0x2508) = NULL;
    if (g[0xCCE] != 0 && (*(s16*)(g + 0xCCC) > 0x3C || *(s16*)(g + 0xCCC) % 2 != 0)) {
        p[0x252E] = 1;
        *(void**)(p + 0x2508) = fn_3_11741C;
        *(f32*)(p + 0x250C) = *(f32*)(g + 0xCB0);
        *(f32*)(p + 0x2510) = -*(f32*)(g + 0xCB4);
        *(f32*)(p + 0x2514) = *(f32*)(g + 0xCB8);
        fn_8001D0D0(0xED, lbl_3_rodata_33C0);
        p[0xFEE] = 1;
        *(f32*)(p + 0xFCC) = *(f32*)(g + 0xCB0);
        *(f32*)(p + 0xFD0) = lbl_3_rodata_33C4;
        *(f32*)(p + 0xFD4) = *(f32*)(g + 0xCB8);
        fn_8001D0D0(0x65, lbl_3_rodata_33C8);
    }
}

// .text:0x00117588 size:0x464 mapped:0x8075661C
void fn_3_117588(void) {
    return;
}

// .text:0x001179EC size:0xF8 mapped:0x80756A80
extern const f32 lbl_3_rodata_33DC;

void fn_3_1179EC(void) {
    u8* e;
    f32* v;
    u32 i;
    for (i = 0; i < 4; i++) {
        e = *(u8**)(lbl_8036E548 + 0x2D94) + (i + 0xE9) * 0x28;
        v = (f32*)(g_Minigame + i * 0x40 + 0xBB0);
        e[0x26] = 0;
        *(void**)e = NULL;
        if (g_Minigame[i * 0x40 + 0xBED] != 0) {
            e[0x26] = 1;
            *(f32*)(e + 4) = v[0];
            *(f32*)(e + 8) = -v[1];
            *(f32*)(e + 0xC) = v[2];
            *(f32*)(e + 0x10) = lbl_3_rodata_33DC * v[6];
            *(f32*)(e + 0x14) = lbl_3_rodata_33DC * v[7];
            *(f32*)(e + 0x18) = lbl_3_rodata_33DC * v[8];
            fn_8001D0D0(i + 0xE9, lbl_3_rodata_33C0);
            *(void**)e = fn_3_117588;
        }
    }
}

// .text:0x00117AE4 size:0x94 mapped:0x80756B78
void fn_3_117AE4(void) {
    u8* p = *(u8**)(lbl_8036E548 + 0x2D94);
    f32 z = 0.0f;
    p[0x243E] = 1;
    *(f32*)(p + 0x241C) = lbl_3_data_21A48[0];
    *(f32*)(p + 0x2424) = lbl_3_data_21A48[2];
    *(f32*)(p + 0x2420) = z;
    *(f32*)(p + 0x2428) = z;
    *(f32*)(p + 0x2430) = z;
    *(f32*)(p + 0x242C) = shortAngleToRad(0x1000 - *(s16*)(g_Minigame + 0x1D64));
    fn_8001D0D0(0xE7, 3.0f);
}

// .text:0x00117B78 size:0x450 mapped:0x80756C0C
void fn_3_117B78(void) {
    return;
}

// .text:0x00117FC8 size:0xDC mapped:0x8075705C
extern const f32 lbl_3_rodata_33CC;
extern const f32 lbl_3_rodata_33D0;
extern const f32 lbl_3_rodata_33D4;
extern const f32 lbl_3_rodata_33D8;
extern f32 RandomF32_Game_Range(f32 a, f32 b);
extern f32 fn_3_9FEA8(f32 v);

void fn_3_117FC8(void) {
    u8* p = *(u8**)(lbl_8036E548 + 0x2D94);
    p[0x2466] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D94))[0xFEE] = 0;
    if (g_Minigame[0x72A] != 0) {
        p[0x2466] = 1;
        *(f32*)(p + 0x2444) = *(f32*)(g_Minigame + 0x6E8);
        *(f32*)(p + 0x2448) = -*(f32*)(g_Minigame + 0x6EC);
        *(f32*)(p + 0x244C) = *(f32*)(g_Minigame + 0x6F0);
        fn_8001D0D0(0xE8, lbl_3_rodata_33CC);
        if (*(s16*)(g_Minigame + 0x724) == 0) {
            *(f32*)(p + 0x2454) = RandomF32_Game_Range(lbl_3_rodata_33D0, lbl_3_rodata_33D4);
        } else {
            *(f32*)(p + 0x2454) = fn_3_9FEA8(lbl_3_rodata_33D8 + *(f32*)(p + 0x2454));
        }
        *(void**)(p + 0x2440) = fn_3_117B78;
    }
}

// .text:0x001180A4 size:0xC0 mapped:0x80757138
extern const f32 lbl_3_rodata_33AC;
extern const f32 lbl_3_rodata_33C4;
extern const f32 lbl_3_rodata_33F4;

void fn_3_1180A4(void) {
    u8* p = *(u8**)(lbl_8036E548 + 0x2D94);
    p[0xFC6] = 0;
    p[0x2416] = 0;
    if (g_Minigame[0xBAC] == 1) {
        p[0x2416] = 1;
        *(f32*)(p + 0x23F4) = *(f32*)(g_Minigame + 0xB6C);
        *(f32*)(p + 0x23F8) = -*(f32*)(g_Minigame + 0xB70);
        *(f32*)(p + 0x23FC) = *(f32*)(g_Minigame + 0xB74);
        *(f32*)(p + 0x2400) = lbl_3_rodata_33AC;
        *(f32*)(p + 0x2404) = lbl_3_rodata_33AC;
        *(f32*)(p + 0x2408) = lbl_3_rodata_33AC;
        p[0xFC6] = 1;
        *(s32*)(p + 0xFA0) = 0;
        *(f32*)(p + 0xFA4) = *(f32*)(g_Minigame + 0xB6C);
        *(f32*)(p + 0xFA8) = lbl_3_rodata_33C4;
        *(f32*)(p + 0xFAC) = *(f32*)(g_Minigame + 0xB74);
        fn_8001D0D0(0x64, lbl_3_rodata_33F4);
    }
}

// .text:0x00118164 size:0x1F4 mapped:0x807571F8
extern const f32 lbl_3_rodata_33F8;
extern const f32 lbl_3_rodata_33FC;
extern const f32 lbl_3_rodata_3400;
extern s16 lbl_3_data_21A04[];
void fn_3_118164(void) {
    u8* e1;
    u8* e2;
    s32 i;
    s32 j;
    for (i = 0; i < 0x64; i++) {
        j = i + 0x82;
        e1 = *(u8**)(lbl_8036E548 + 0x2D94) + j * 0x28;
        e1[0x26] = 0;
        e2 = *(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28;
        e2[0x26] = 0;
        if (g_Minigame[i + 0x193A] == 1 || g_Minigame[i + 0x193A] == 3) {
            e1[0x26] = 1;
            *(f32*)(e1 + 4) = *(f32*)(g_Minigame + i * 0xC + 0xCD0);
            *(f32*)(e1 + 8) = -*(f32*)(g_Minigame + i * 0xC + 0xCD4);
            *(f32*)(e1 + 0xC) = *(f32*)(g_Minigame + i * 0xC + 0xCD8);
            *(f32*)(e1 + 0x10) = lbl_3_rodata_33AC;
            *(f32*)(e1 + 0x18) = lbl_3_rodata_33AC;
            fn_8001D0D0(j, lbl_3_rodata_33F8);
            if (*(s16*)(g_Minigame + i * 2 + 0x17C8) <= 1) {
                *(f32*)(e1 + 0x14) = RandomF32_Game_Range(lbl_3_rodata_33D0, lbl_3_rodata_33D4);
            } else if (g_Minigame[i + 0x193A] == 1) {
                *(f32*)(e1 + 0x14) = fn_3_9FEA8(lbl_3_rodata_33FC + *(f32*)(e1 + 0x14));
            } else {
                *(f32*)(e1 + 0x14) = fn_3_9FEA8(lbl_3_rodata_33F4 + *(f32*)(e1 + 0x14));
            }
            e2[0x26] = 1;
            *(s32*)e2 = 0;
            *(f32*)(e2 + 4) = *(f32*)(g_Minigame + i * 0xC + 0xCD0);
            *(f32*)(e2 + 8) = lbl_3_rodata_33C4;
            *(f32*)(e2 + 0xC) = *(f32*)(g_Minigame + i * 0xC + 0xCD8);
            fn_8001D0D0(i, lbl_3_rodata_3400);
            if (*(s16*)(g_Minigame + i * 2 + 0x17C8) > lbl_3_data_21A04[3] - 0xB4 &&
                g_Minigame[i + 0x193A] == 1 && (*(u16*)(g_d_GameSettings + 4) & 1)) {
                e1[0x26] = 0;
                e2[0x26] = 0;
            }
            if (g_Minigame[i + 0x193A] == 3 && (*(u16*)(g_d_GameSettings + 4) & 1)) {
                e1[0x26] = 0;
                e2[0x26] = 0;
            }
        }
    }
}

// .text:0x00118358 size:0xA4 mapped:0x807573EC
extern void* memset(void* dst, int c, u32 n);
extern void PSMTXMultVec(void* m, void* src, void* dst);

void fn_3_118358(s32 i, f32* v) {
    u8* o = *(u8**)(*(u8**)(*(u8**)(*(u8**)(lbl_8036E548 + 0x68) + (i + 0x82) * 0x90 + 0x34) + 0x18) + 0x44);
    if (i < 0 || i > 2) {
        return;
    }
    if (v != NULL) {
        memset(v, 0, 0xC);
        PSMTXMultVec(*(void**)(o + 0xEC), v, v);
        v[1] *= -1.0f;
    }
}

// .text:0x001183FC size:0x10C mapped:0x80757490
extern f32 lbl_3_data_21B94[];
extern const f32 lbl_3_rodata_33AC;
extern f32 lbl_3_data_226DC;
void fn_3_1183FC(void) {
    s32 i;
    u8* e;
    for (i = 0; i < 4; i++) {
        e = *(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28;
        *(f32*)(e + 0x2584) = lbl_3_data_21B94[i * 3];
        *(f32*)(e + 0x2588) = -lbl_3_data_21B94[i * 3 + 1];
        *(f32*)(e + 0x258C) = lbl_3_data_21B94[i * 3 + 2];
        *(f32*)(e + 0x2588) = lbl_3_rodata_33AC;
        *(f32*)(e + 0x258C) = *(f32*)(e + 0x258C) - lbl_3_data_226DC;
        e[0x25A6] = 1;
    }
}

// .text:0x00118508 size:0x10C mapped:0x8075759C
void fn_3_118508(void) {
    u8* p = lbl_803CC1B8[0];
    u8* m;
    s32 i;
    if (g_GameLogic[0x11E] == 0xF) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    for (i = 0, m = g_Minigame; i < 0x28; m += 0x28, i++) {
        if (m[0xCE] == 0) {
            *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) + i) * 8) + 0x54) &= ~2;
        } else {
            *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) + i) * 8) + 0x54) |= 2;
            *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) + i) * 8) + 0x48) = *(f32*)(m + 0xA8);
            *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) + i) * 8) + 0x4C) = -*(f32*)(m + 0xAC);
            *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) + i) * 8) + 0x50) = *(f32*)(m + 0xB0);
        }
    }
}

// .text:0x00118614 size:0x138 mapped:0x807576A8
void fn_3_118614(void) {
    u8* p;
    s32 i;
    fn_80034E20(p = lbl_803CC1B8[0], lbl_3_data_69D0);
    for (i = 0; i < 0x28; i++) {
        *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(p + 0x14) + i) * 8) + 0x5C) = 0x20000;
    }
    *(void**)lbl_803CC1B8[0] = fn_3_118508;
}

// .text:0x0011874C size:0xD0 mapped:0x807577E0
extern f32 lbl_3_data_226D4[];
extern const f32 lbl_3_rodata_3408;
extern const f32 lbl_3_rodata_33E0;
extern void fn_8001D110(s32 i, f32 a, f32 b, f32 c);

void fn_3_11874C(void) {
    s32 i;
    if (g_GameLogic[0x121] == 8) {
        return;
    }
    for (i = 0; i < 0x28; i++) {
        u8* p = *(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28;
        f32* v = (f32*)(g_Minigame + i * 0x28 + 0xA8);
        p[0x26] = 0;
        *(s32*)p = 0;
        if (g_Minigame[i * 0x28 + 0xCE] != 0) {
            p[0x26] = 1;
            *(f32*)(p + 4) = v[0];
            *(f32*)(p + 0xC) = v[2];
            *(f32*)(p + 8) = lbl_3_rodata_3408;
            fn_8001D110(i, lbl_3_data_226D4[1], lbl_3_rodata_33E0, lbl_3_data_226D4[1]);
        }
    }
}

// .text:0x0011881C size:0x60 mapped:0x807578B0
void fn_3_11881C(void) {
    return;
}

// .text:0x0011887C size:0x100 mapped:0x80757910
extern f32 lbl_3_data_21B94[];
extern u8 lbl_3_data_21BC4[];
extern f32 lbl_3_data_226C4[];
extern const f32 lbl_3_rodata_33AC;

void fn_3_11887C(void) {
    u8* e;
    s32 i;
    f32* v;
    for (i = 0; i < 7; i++) {
        e = *(u8**)(lbl_8036E548 + 0x2D94) + (i + 0xE9) * 0x28;
        e[0x26] = 1;
        if (i < 4) {
            v = &lbl_3_data_21B94[i * 3];
            *(f32*)(e + 4) = v[0];
            *(f32*)(e + 8) = -v[1];
            *(f32*)(e + 0xC) = v[2];
            *(f32*)(e + 8) = lbl_3_rodata_33AC;
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[2], lbl_3_data_226C4[3], lbl_3_data_226C4[2]);
            *(void**)e = fn_3_11881C;
        } else {
            v = (f32*)(lbl_3_data_21BC4 + i * 0x30 - 0xC0);
            *(f32*)(e + 4) = v[0];
            *(f32*)(e + 8) = -v[1];
            *(f32*)(e + 0xC) = v[2];
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0]);
            *(void**)e = fn_3_11881C;
        }
    }
}

// .text:0x0011897C size:0x4C mapped:0x80757A10
void fn_3_11897C(s32 i) {
    return;
}

// .text:0x001189C8 size:0x150 mapped:0x80757A5C
extern f32 lbl_3_data_22694[];
extern s16 lbl_3_data_226AC[];
void fn_3_1189C8(s32 i, s32 a, s32 b, s32 d, u8 flag) {
    u8* m = g_Minigame + i * 0x38;
    u8* o = *(u8**)(lbl_8036E548 + 0x68) + (i + 0x82) * 0x90 + 0x34;
    f32 inv = lbl_3_rodata_33AC;
    u8 t;
    s32 x;
    if (d != 0) {
        inv = 1.0f / (f32)d;
    }
    x = *(s32*)(lbl_3_common_bss_32724 + 0x78);
    *(s32*)(o + 4) = x;
    *(s16*)(o + 0xE) = a;
    *(f32*)(o + 0x5C) = lbl_3_rodata_33AC;
    o[0x58] = 1;
    o[0x59] = (x != 0);
    o[0x5A] = (x != 0);
    *(f32*)(o + 0x60) = inv;
    *(f32*)(o + 0x54) = lbl_3_data_22694[a];
    o[0x5A] = 1;
    *(f32*)(o + 0x5C) = (f32)(b + lbl_3_data_226AC[a]);
    o[0x59] = 1;
    if (flag != 0) {
        o[0x5B] = 3;
    } else {
        o[0x5B] = 2;
    }
    m[0x33] = a;
    *(s16*)(m + 0x28) = b;
}

// .text:0x00118B18 size:0x7A0 mapped:0x80757BAC
void fn_3_118B18(void) {
    return;
}

// .text:0x001192B8 size:0x1B0 mapped:0x8075834C
extern s16 lbl_3_data_21E68[];
extern f32 lbl_3_data_22678[];
extern f32 lbl_3_data_22688[];
extern const f32 lbl_3_rodata_33E0;
void fn_3_1192B8(void) {
    u8* g;
    u8* e;
    s32 i;
    for (i = 0; i < 3; i++) {
        g = g_Minigame + i * 0x38;
        e = *(u8**)(lbl_8036E548 + 0x2D94) + (i + 0x82) * 0x28;
        e[0x26] = 0;
        if (g[0x2A] != 0) {
            e[0x26] = 1;
            *(f32*)(e + 4) = *(f32*)g;
            *(f32*)(e + 8) = -*(f32*)(g + 4);
            *(f32*)(e + 0xC) = *(f32*)(g + 8);
            if (g[0x2A] != 3) {
                fn_8001D0D0(i + 0x82, lbl_3_data_22678[g[0x2B]]);
            } else {
                f32 t = (f32)*(s16*)(g + 0x1A) / (f32)lbl_3_data_21E68[6];
                f32* q = &lbl_3_data_22678[g[0x2B]];
                f32 u = lbl_3_rodata_33E0 - t;
                fn_8001D0D0(i + 0x82, u * q[0] + q[2] * t);
            }
            if (g[0x2B] == 0) {
                *(f32*)(e + 0x14) = *(f32*)(g + 0x10);
                *(f32*)(e + 0x10) = lbl_3_rodata_33AC;
                *(f32*)(e + 0x18) = lbl_3_rodata_33AC;
            } else {
                *(f32*)(e + 0x14) = lbl_3_data_22688[i];
            }
            if (g[0x2A] == 4 && *(s16*)(g + 0x1C) <= 0 && (*(s16*)(g + 0x1A) & 1)) {
                e[0x26] = 0;
            }
            *(void**)e = fn_3_11897C;
            ((void (*)(s32))fn_3_118B18)(i);
        }
    }
}

// .text:0x00119468 size:0x44 mapped:0x807584FC
extern void fn_3_14225C(void);

typedef struct { u8 p[0x34]; u8* o; u8 q[0x58]; } E90;
void fn_3_119468(s32 i) {
    E90* arr = *(E90**)(lbl_8036E548 + 0x68);
    u8* o = arr[i].o;
    if (o[0x98] & 9) {
        fn_3_14225C();
    }
}

// .text:0x001194AC size:0x50 mapped:0x80758540
void fn_3_1194AC(void) {
    return;
}

// .text:0x001194FC size:0x358 mapped:0x80758590
void fn_3_1194FC(void) {
    return;
}

// .text:0x00119854 size:0x24 mapped:0x807588E8
f32 fn_3_119854(u8 i) {
    if (i > 2) {
        i = 2;
    }
    return lbl_3_data_22650[i];
}

// .text:0x00119878 size:0xBC mapped:0x8075890C
// 97%: same code, but p/g (r5/r6) and the lis temps (r3/r4) come out swapped in the prologue
extern const f32 lbl_3_rodata_3420;
void fn_3_119878(void) {
    u8* p = *(u8**)(lbl_8036E548 + 0x2D94);
    u8* g = g_Minigame;
    p[0x1A16] = 0;
    *(void**)(p + 0x19F0) = 0;
    if (g[0xCCE] != 0 &&
        (*(s16*)(g + 0xCCC) > 0x3C || *(s16*)(g + 0xCCC) % 2 != 0 ||
         g[0x1B19] == 2 || g[0x1B19] == 3)) {
        p[0x1A16] = 1;
        *(void**)(p + 0x19F0) = fn_3_11741C;
        *(f32*)(p + 0x19F4) = *(f32*)(g + 0xCB0);
        *(f32*)(p + 0x19F8) = -*(f32*)(g + 0xCB4);
        *(f32*)(p + 0x19FC) = *(f32*)(g + 0xCB8);
        fn_8001D0D0(0xA6, lbl_3_rodata_3420);
    }
}

// .text:0x00119934 size:0x300 mapped:0x807589C8
void fn_3_119934(void) {
    return;
}

// .text:0x00119C34 size:0x74 mapped:0x80758CC8
void fn_3_119C34(void) {
    u8* p = *(u8**)(lbl_8036E548 + 0x68);
    s32 v = *(s32*)(lbl_3_common_bss_32724 + 0x74);
    s8 t;
    *(s32*)(p + 0x11A8) = v;
    *(s16*)(p + 0x11B2) = 1;
    t = v != 0;
    *(f32*)(p + 0x1200) = 0.0f;
    *(u8*)(p + 0x11FC) = 1;
    *(u8*)(p + 0x11FD) = t;
    *(u8*)(p + 0x11FE) = t;
    *(f32*)(p + 0x1204) = 0.0f;
    *(f32*)(p + 0x11F8) = 1.0f;
    *(u8*)(p + 0x11FE) = 1;
    *(f32*)(p + 0x1200) = 0.0f;
    *(u8*)(p + 0x11FD) = 1;
    *(u8*)(p + 0x11FF) = 2;
}

// .text:0x00119CA8 size:0x80 mapped:0x80758D3C
void fn_3_119CA8(s32 i) {
    u8* p = *(u8**)(lbl_8036E548 + 0x68);
    u8* e = p + i * 0x90 + 0x34;
    s32 v = *(s32*)(lbl_3_common_bss_32724 + 0x74);
    s8 t;
    *(s32*)(e + 4) = v;
    *(s16*)(e + 0xE) = 0;
    t = v != 0;
    *(f32*)(e + 0x5C) = 0.0f;
    *(u8*)(e + 0x58) = 1;
    *(u8*)(e + 0x59) = t;
    *(u8*)(e + 0x5A) = t;
    *(f32*)(e + 0x60) = 0.0f;
    *(f32*)(e + 0x54) = 1.0f;
    *(u8*)(e + 0x5A) = 1;
    *(f32*)(e + 0x5C) = 0.0f;
    *(u8*)(e + 0x59) = 1;
    *(u8*)(e + 0x5B) = 2;
}

// .text:0x00119D28 size:0xC mapped:0x80758DBC
f32 fn_3_119D28(void) {
    return lbl_3_data_2262C;
}

// .text:0x00119D34 size:0xFC mapped:0x80758DC8
void fn_3_119D34(void) {
    u8* q = *(u8**)(lbl_8036E548 + 0x2D94) + 0x4D8;
    q[0x26] = 1;
    fn_3_11A92C(q, 0x1F);
    if (lbl_80366158[0x28] == 0 && g_GameLogic[0x11E] == 1 && *(s16*)(g_Pitcher + 0x11E) == lbl_3_data_217A4[7]) {
        {

        u8* p = *(u8**)(lbl_8036E548 + 0x68);
        s32 v = *(s32*)(lbl_3_common_bss_32724 + 0x74);
        s8 t;
        *(s32*)(p + 0x11A8) = v;
        *(s16*)(p + 0x11B2) = 1;
        t = v != 0;
        *(f32*)(p + 0x1200) = 0.0f;
        *(u8*)(p + 0x11FC) = 1;
        *(u8*)(p + 0x11FD) = t;
        *(u8*)(p + 0x11FE) = t;
        *(f32*)(p + 0x1204) = 0.0f;
        *(f32*)(p + 0x11F8) = 1.0f;
        *(u8*)(p + 0x11FE) = 1;
        *(f32*)(p + 0x1200) = 0.0f;
        *(u8*)(p + 0x11FD) = 1;
        *(u8*)(p + 0x11FF) = 2;
}
        fn_3_90064(0x2E6);
    }
}

// .text:0x00119E30 size:0xB0 mapped:0x80758EC4
void fn_3_119E30(void) {
    return;
}

// .text:0x00119EE0 size:0x8C mapped:0x80758F74
void fn_3_119EE0(void) {
    return;
}

// .text:0x00119F6C size:0x2A0 mapped:0x80759000
void fn_3_119F6C(void) {
    return;
}

// .text:0x0011A20C size:0x4 mapped:0x807592A0
void fn_3_11A20C(void) {
    return;
}

// .text:0x0011A210 size:0x140 mapped:0x807592A4
extern const f32 lbl_3_rodata_342C;
extern const f32 lbl_3_rodata_3430;
void fn_3_11A210(void) {
    u8* e1;
    u8* e2;
    u8* g;
    s32 i;
    for (i = 0; i < 100; i++) {
        e1 = *(u8**)(lbl_8036E548 + 0x2D94) + (i + 0x82) * 0x28;
        e1[0x26] = 0;
        *(void**)e1 = 0;
        e2 = *(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28;
        e2[0x26] = 0;
        *(void**)e2 = 0;
        if (g_Minigame[0x193A + i] != 0) {
            g = g_Minigame + i * 0xC;
            e1[0x26] = 1;
            *(f32*)(e1 + 4) = *(f32*)(g + 0xCD0);
            *(f32*)(e1 + 8) = -*(f32*)(g + 0xCD4);
            *(f32*)(e1 + 0xC) = *(f32*)(g + 0xCD8);
            fn_8001D0D0(i + 0x82, lbl_3_rodata_342C);
            if (*(s16*)(g_Minigame + 0x17C8 + i * 2) <= 1) {
                *(f32*)(e1 + 0x14) = RandomF32_Game_Range(lbl_3_rodata_33D0, lbl_3_rodata_33D4);
            } else {
                *(f32*)(e1 + 0x14) = fn_3_9FEA8(lbl_3_rodata_33FC + *(f32*)(e1 + 0x14));
            }
            e2[0x26] = 1;
            *(f32*)(e2 + 4) = *(f32*)(g + 0xCD0);
            *(f32*)(e2 + 8) = lbl_3_rodata_33C4;
            *(f32*)(e2 + 0xC) = *(f32*)(g + 0xCD8);
            fn_8001D0D0(i, lbl_3_rodata_3430);
        }
    }
}

// .text:0x0011A350 size:0x3C mapped:0x807593E4
u32 fn_3_11A350(int i) {
    Ent90* base = *(Ent90**)(lbl_8036E548 + 0x68);
    return fn_800B4A94(base[i].p);
}

// .text:0x0011A38C size:0x7C mapped:0x80759420
void fn_3_11A38C(s32 i, s16 h) {
    u8* p = *(u8**)(lbl_8036E548 + 0x68);
    u8* e = p + i * 0x90 + 0x34;
    s32 v = *(s32*)(lbl_3_common_bss_32724 + 0x70);
    s8 t;
    *(s32*)(e + 4) = v;
    *(s16*)(e + 0xE) = h;
    t = v != 0;
    *(f32*)(e + 0x5C) = 0.0f;
    *(u8*)(e + 0x58) = 1;
    *(u8*)(e + 0x59) = t;
    *(u8*)(e + 0x5A) = t;
    *(f32*)(e + 0x60) = 0.0f;
    *(f32*)(e + 0x54) = 1.0f;
    *(u8*)(e + 0x5A) = 1;
    *(f32*)(e + 0x5C) = 0.0f;
    *(u8*)(e + 0x59) = 1;
    *(u8*)(e + 0x5B) = 2;
}

// .text:0x0011A408 size:0x524 mapped:0x8075949C
void fn_3_11A408(void) {
    return;
}

// .text:0x0011A92C size:0x200 mapped:0x807599C0
#pragma dont_inline on
extern f32 lbl_3_data_22620[];
extern f32 lbl_3_data_21380[];
extern const f32 lbl_3_rodata_33E4;
extern const f32 lbl_3_rodata_3440;
extern const f64 lbl_3_rodata_3438;
extern void fn_80062C24(f32*);
extern void fn_3_14A90C(f32*);
extern void fn_3_14B9A0(s32, void*, s16, void*);
static f32 lbl_3_bss_B6BC;
void fn_3_11A92C(u8* q, s32 n) {
    f32 v[3];
    u8 t;
    u8 k;
    *(f32*)(q + 4) = lbl_3_data_22620[0];
    *(f32*)(q + 8) = lbl_3_data_22620[1];
    *(f32*)(q + 0xC) = lbl_3_data_22620[2];
    *(f32*)(q + 0x10) = lbl_3_rodata_33AC;
    *(f32*)(q + 0x14) = lbl_3_rodata_33AC;
    *(f32*)(q + 0x18) = lbl_3_rodata_33AC;
    fn_8001D0D0(n, lbl_3_data_2262C);
    if (g_Minigame[0x1A3B] == 0 && g_d_GameSettings[7] != 2) {
        t = g_Minigame[0x1A2A];
        if (t == 1) {
            if (g_Pitcher[0x13E] >= 3) {
                if (*(s16*)(g_Pitcher + 0x120) == 1 && g_Pitcher[0x13E] == 3) {
                    lbl_3_bss_B6BC = lbl_3_rodata_33CC;
                    v[0] = lbl_3_data_21380[0];
                    v[1] = -lbl_3_data_21380[1];
                    v[2] = lbl_3_data_21380[2] - lbl_3_rodata_33E4;
                    fn_80062C24(v);
                    fn_3_90064(0x2D6);
                }
                *(f32*)(q + 0xC) = *(f32*)(q + 0xC) + lbl_3_bss_B6BC;
                lbl_3_bss_B6BC = -((lbl_3_rodata_3438 * (*(f32*)(q + 0xC) - lbl_3_data_22620[2])) - lbl_3_bss_B6BC);
                return;
            }
        } else if (t == 3) {
            if (*(s16*)(g_Pitcher + 0x120) == 1) {
                k = g_Pitcher[0x13E];
                if (k == 1) {
                    fn_3_14B9A0(lbl_3_data_217A4[6] + lbl_3_data_217A4[7], lbl_3_data_22620, lbl_3_data_217A4[6], lbl_3_data_217A4);
                    fn_3_90064(0x30E);
                    return;
                } else if (k == 3) {
                    v[0] = lbl_3_data_21380[0];
                    v[1] = lbl_3_rodata_3440 + lbl_3_data_21380[1];
                    v[2] = lbl_3_data_21380[2] - lbl_3_rodata_33E4;
                    fn_3_14A90C(v);
                }
            }
        }
    }
}
#pragma dont_inline reset

// .text:0x0011AB2C size:0x140 mapped:0x80759BC0
typedef struct { u8 b : 1; u8 r : 7; } BF1;
void fn_3_11AB2C(void) {
    s32 n = 2;
    u8* e;
    u8* t;
    if (g_d_GameSettings[7] == 2) {
        n = 0;
    }
    e = *(u8**)(lbl_8036E548 + 0x2D94) + n * 0x28;
    if (e != NULL) {
        e[0x26] = 1;
        fn_3_11A92C(e, n);
        if (g_Pitcher[0x13E] >= 2 && lbl_80366158[0x28] == 0) {
            t = lbl_3_common_bss_32724 + 0x10;
            if (t != NULL) {
                ((BF1*)(lbl_3_common_bss_32724 + 0x21))->b = 1;
            }
            fn_80024DB0(t);
            fn_80024FA4(*(u8**)(lbl_8036E548 + 0x68) + n * 0x90 + 0x34, *(u32*)(lbl_3_common_bss_32724 + 0x30), t, -1);
        } else if (g_Pitcher[0x13E] < 2 && *(s16*)(lbl_3_common_bss_32724 + 0x1E) == 0) {
            *(u16*)(lbl_3_common_bss_32724 + 0x1C) = 0;
            *(f32*)(lbl_3_common_bss_32724 + 0x10) = *(u16*)(lbl_3_common_bss_32724 + 0x1C);
            *(s16*)(lbl_3_common_bss_32724 + 0x1E) = 1;
        }
    }
}

// .text:0x0011AC6C size:0xAF0 mapped:0x80759D00
void fn_3_11AC6C(void) {
    return;
}

// .text:0x0011B75C size:0x448 mapped:0x8075A7F0
void fn_3_11B75C(void) {
    return;
}

// .text:0x0011BBA4 size:0x488 mapped:0x8075AC38
void fn_3_11BBA4(void) {
    return;
}

// .text:0x0011C02C size:0x2A0 mapped:0x8075B0C0
void fn_3_11C02C(void) {
    return;
}

// .text:0x0011C2CC size:0x32C mapped:0x8075B360
void fn_3_11C2CC(void) {
    return;
}

// .text:0x0011C5F8 size:0x708 mapped:0x8075B68C
void fn_3_11C5F8(void) {
    return;
}

// .text:0x0011CD00 size:0x204 mapped:0x8075BD94
void fn_3_11CD00(void) {
    return;
}

// .text:0x0011CF04 size:0x80 mapped:0x8075BF98
void fn_3_11CF04(void) {
    if (g_d_GameSettings[7] != 6) {
        *(s16*)(lbl_8036E548 + 0x3078) = 0;
    }
    lbl_8036E548[0x307E] = 0;
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    fn_80035B50(0xD);
    fn_3_B95EC();
    fn_3_5E60();
    fn_80018B38();
    fn_3_909B0();
    fn_3_9081C();
    fn_80035B50(0x11);
}

// .text:0x0011CF84 size:0x22C mapped:0x8075C018
void fn_3_11CF84(void) {
    return;
}

// .text:0x0011D1B0 size:0x118 mapped:0x8075C244
void fn_3_11D1B0(void) {
    s32 i;
    switch (g_Minigame[0x1A2A]) {
    case 1:
        ((void (*)(void))fn_3_11CD00)();
        break;
    case 2:
        ((void (*)(void))fn_3_11C5F8)();
        break;
    case 3:
        ((void (*)(void))fn_3_11C2CC)();
        break;
    case 4:
        ((void (*)(void))fn_3_11C02C)();
        break;
    case 6:
        ((void (*)(void))fn_3_11BBA4)();
        break;
    case 5:
        ((void (*)(void))fn_3_11B75C)();
        break;
    }
    for (i = 0; i < *(u16*)(lbl_8036E548 + 0x3078); i++) {
        *(f32*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 4) = lbl_3_rodata_33AC;
        *(f32*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 8) = lbl_3_rodata_33AC;
        *(f32*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 0xC) = lbl_3_rodata_33AC;
        *(f32*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 0x10) = lbl_3_rodata_33AC;
        *(f32*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 0x14) = lbl_3_rodata_33AC;
        *(f32*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 0x18) = lbl_3_rodata_33AC;
        *(u8*)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28 + 0x26) = 0;
        *(void**)(*(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28) = NULL;
    }
}

// .text:0x0011D2C8 size:0xE4 mapped:0x8075C35C
void fn_3_11D2C8(s32 idx, s32 start, s32 count, s32 a, s32 b) {
    s32 k;
    for (k = start; k < start + count; k++) {
        fn_800BDC88(*(u8**)(lbl_8036E548 + 0x68), (u16)k, (u16)k, *(u32*)(lbl_8036E548 + idx * 0xC + 0x2DA0), a, b);
        fn_800BD548(*(u8**)(lbl_8036E548 + 0x68) + k * 0x90 + 0x34, 4, *(u32*)(lbl_8036E548 + 0xAC), *(u32*)(lbl_8036E548 + 0xB0), *(u32*)(lbl_8036E548 + 0xB4), *(u32*)(lbl_8036E548 + 0xB8));
        CTRLSetTranslation(*(u8**)(lbl_8036E548 + 0x68) + k * 0x90 + 0x44, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(*(u8**)(lbl_8036E548 + 0x68) + k * 0x90 + 0x44, 0.0f, 0.0f, 0.0f);
    }
}

