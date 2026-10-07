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
extern void CTRLSetTranslation(void* c, f32 x, f32 y, f32 z);
extern void CTRLSetRotation(void* c, f32 x, f32 y, f32 z);

// .text:0x00116840 size:0x190 mapped:0x807558D4
void fn_3_116840(void) {
    return;
}

// .text:0x001169D0 size:0x168 mapped:0x80755A64
void fn_3_1169D0(void) {
    return;
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
void fn_3_117494(void) {
    return;
}

// .text:0x00117588 size:0x464 mapped:0x8075661C
void fn_3_117588(void) {
    return;
}

// .text:0x001179EC size:0xF8 mapped:0x80756A80
void fn_3_1179EC(void) {
    return;
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
void fn_3_117FC8(void) {
    return;
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
void fn_3_118164(void) {
    return;
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
void fn_3_1183FC(void) {
    return;
}

// .text:0x00118508 size:0x10C mapped:0x8075759C
void fn_3_118508(void) {
    return;
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
void fn_3_11887C(void) {
    return;
}

// .text:0x0011897C size:0x4C mapped:0x80757A10
void fn_3_11897C(void) {
    return;
}

// .text:0x001189C8 size:0x150 mapped:0x80757A5C
void fn_3_1189C8(void) {
    return;
}

// .text:0x00118B18 size:0x7A0 mapped:0x80757BAC
void fn_3_118B18(void) {
    return;
}

// .text:0x001192B8 size:0x1B0 mapped:0x8075834C
void fn_3_1192B8(void) {
    return;
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
void fn_3_119878(void) {
    return;
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
void fn_3_11A210(void) {
    return;
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
void fn_3_11A92C(u8* q, s32 n) {
    return;
}
#pragma dont_inline reset

// .text:0x0011AB2C size:0x140 mapped:0x80759BC0
void fn_3_11AB2C(void) {
    return;
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
    return;
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

