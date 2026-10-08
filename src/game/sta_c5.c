#include "game/sta_c5.h"
#include "header_rep_data.h"
#include "Dolphin/os.h"
extern u8 lbl_3_common_bss_350E4[];
extern u8 g_Ball[];
extern u8 g_GameLogic[];
extern u8 g_d_GameSettings[];
extern u8 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 g_FieldingLogic[];
extern u8 lbl_3_data_84B8[];
extern u32 sndFXStartEx(int, u8, u8, u8);
extern void sndFXCtrl(int, int, u8);
extern void fn_3_65A8(void);
extern void fn_3_27648(void);
extern void fn_3_8B890(s32);
extern void fn_3_8BA60(s32, s32, s32);
extern s32 fn_3_8BBC4(s32, s32, s32, s32);
typedef struct { u8 pad[0x78]; s32 w78; u8 pad2[0xE8 - 0x7C]; } StadObj78;
extern char lbl_3_rodata_2DB8[];
extern char lbl_3_rodata_2F10[];
#pragma dont_inline on
#include "C3/control.h"
#include "Dolphin/vec.h"
#include "C3/geoPalette.h"
typedef struct { Vec v; f32 pad[2]; } V14;
extern V14 lbl_3_data_1B884[];
typedef struct { f32 a, b, c, d, e, f; } T18;
extern T18 lbl_3_data_1B9A4[];
extern f32 lbl_3_rodata_2D5C;
extern f32 lbl_3_rodata_2D68;
extern char lbl_3_rodata_2DC4[];
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void* fn_3_B9534(u32, u32, void*);
extern int rand(void);
extern s8 lbl_3_bss_AF18[];
extern u8* lbl_3_bss_B118[];
extern void* memset(void*, s32, u32);
extern f32 lbl_3_rodata_2D50;
extern f32 lbl_3_rodata_2EE8;
extern f32 lbl_3_rodata_2DEC;
extern f32 lbl_3_rodata_2DDC;
extern f32 lbl_3_rodata_2E88;
extern f64 sin(f64);
extern f32 lbl_3_rodata_2D74;
extern f32 lbl_3_rodata_2DF0;
extern u8 lbl_800E8754[];
extern void fn_3_CB7E8(f32, f32, f32);
extern char lbl_3_rodata_2D38[];
extern f64 lbl_3_rodata_2DD0;
extern f32 lbl_3_rodata_2D54;
extern f32 lbl_3_rodata_2DD8;
extern u8 lbl_3_data_1B820[];
extern u8 fn_800527C4(void*);
extern void fn_80064430(void*, s32, f32, f32);
extern f64 acos(f64);
extern f64 lbl_3_rodata_2DE0;
extern f32 lbl_3_rodata_2D70;
extern f32 lbl_3_rodata_2DE8;
extern f64 cos(f64);
extern u8 lbl_803C5090[];
extern void fn_8003A144(u8*, u8*);
extern s32 fn_80039AB4(void);
extern void SetDisplayStateTexture(s32, s32, s32);
extern s32 fn_8005268C(void);
extern u8* fn_80052734(s32);
extern u8 lbl_8036E548[];
extern u8 lbl_3_bss_B219[];
extern u8 lbl_3_bss_B55C[];
extern u8 lbl_3_bss_B218[];
extern u8 lbl_3_bss_B21A;
extern void fn_3_B8414(void* a, void* b);
extern void fn_3_B8464(void* mtx, void* obj);
extern void fn_800B4CA0(void*, f32);
extern void AnimateActorBones(void*);
extern u8 lbl_3_bss_AEE0[];
extern u8 lbl_803CBBC0[];
extern u8 lbl_3_data_1BA5C[];
extern void fn_800BDA24(s32);
extern void fn_800B0A14_removeQueue();
extern void fn_800A7D4C();
typedef struct { f32 a, b, c; } V3w;
extern u32 lbl_3_bss_B154[];
extern void fn_3_B97DC(void*, u32);

void fn_3_EDFAC(void) {
    u8* st = lbl_3_bss_AEE0;
    if (g_GameLogic[0x11E] != 0x21) {
        if (g_GameLogic[0x11E] == 0xB) {
            if (st[0x27C] == 0) {
                fn_3_8B890(*(s32*)(st + 0x1C));
                fn_3_8B890(*(s32*)(st + 0x18));
                st[0x27C] = 1;
            }
        } else {
            if (st[0x27C] != 0) {
                *(s32*)(st + 0x1C) = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings[9]] + 6, 0, 0, 4);
                *(s32*)(st + 0x18) = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings[9]] + 7, 0, 0, 5);
                st[0x27C] = 0;
                return;
            }
            fn_3_8BA60(*(s32*)(st + 0x1C), 0, 0);
            fn_3_8BA60(*(s32*)(st + 0x18), 0, 0);
        }
    }
}

s32 fn_3_EE0BC(u32 v) {
    switch ((v >> 4) & 0xF) {
    case 0:
    case 1:
        return 1;
    case 2:
    case 3:
        return 2;
    case 4:
        return 4;
    default:
        return 0;
    }
}
#include "Dolphin/GX/GXPixel.h"

// .text:0x000EE100 size:0x288 mapped:0x8072D194
void fn_3_EE100(void) {
    return;
}

// .text:0x000EE388 size:0x2F4 mapped:0x8072D41C
void fn_3_EE388(void) {
    return;
}

// .text:0x000EE67C size:0x2F0 mapped:0x8072D710
void fn_3_EE67C(void) {
    return;
}

// .text:0x000EE96C size:0x228 mapped:0x8072DA00
void fn_3_EE96C(void) {
    return;
}

// .text:0x000EEB94 size:0x160 mapped:0x8072DC28
void fn_3_EEB94(void) {
    u32 i, j;
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            s32 idx = fn_800247E4(j, i, 0x10, 2);
            s32 a = lbl_3_bss_B118[0][idx];
            s32 b = lbl_3_bss_B118[0][idx + 1];
            a += lbl_3_bss_AF18[idx] * (rand() % 14 + 8);
            b += lbl_3_bss_AF18[idx + 1] * (rand() % 14 + 8);
            if (a >= 0xE3) {
                a--;
                lbl_3_bss_AF18[idx] = -1;
            } else if (a <= 0x1B) {
                a++;
                lbl_3_bss_AF18[idx] = 1;
            }
            if (b >= 0xE3) {
                b--;
                lbl_3_bss_AF18[idx + 1] = -1;
            } else if (b <= 0x1B) {
                b++;
                lbl_3_bss_AF18[idx + 1] = 1;
            }
            lbl_3_bss_B118[0][idx] = a;
            lbl_3_bss_B118[0][idx + 1] = b;
        }
    }
}

// 97%: only the GXSetIndTexMtx matrix stores differ (orig: first store via r30+0x23c, rest via pointer r4+4..0x14)
// .text:0x000EECF4 size:0x148 mapped:0x8072DD88
void fn_3_EECF4(void) {
    typedef struct { u8 pad0[0x38]; u8 a38[0x200]; u8* tex; f32 m[2][3]; u8 a254[1]; } S;
    S* s = (S*)lbl_3_bss_AEE0;
    u32 i, j;
    f32 (*m)[3] = (f32(*)[3])(lbl_3_bss_AEE0 + 0x23C);
    s->m[0][0] = lbl_3_rodata_2D68;
    m[0][1] = lbl_3_rodata_2D5C;
    m[0][2] = lbl_3_rodata_2D5C;
    m[1][0] = lbl_3_rodata_2D5C;
    m[1][1] = lbl_3_rodata_2D68;
    m[1][2] = lbl_3_rodata_2D5C;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    s->tex = (u8*)fn_3_B9534(0x10, 0x10, s->a254);
    if (s->tex == NULL) {
        OSPanic(lbl_3_rodata_2DB8, 0x1028, lbl_3_rodata_2DC4);
    }
    for (i = 0; i < 0x10; i++) {
        for (j = 0; j < 0x10; j++) {
            s32 idx = fn_800247E4(j, i, 0x10, 2);
            s->tex[idx] = (u8)(rand() % 200) + 0x1B;
            s->tex[idx + 1] = (u8)(rand() % 200) + 0x1B;
        }
    }
    memset(s->a38, 1, 0x200);
}

// .text:0x000EEE3C size:0xE8 mapped:0x8072DED0
void fn_3_EEE3C(void) {
    u8* b = *(u8**)lbl_3_bss_B55C;
    u8* o = *(u8**)b;
    Vec v;
    lbl_803C5090[0x1D] = 1;
    fn_8003A144(lbl_803C5090, b);
    SetDisplayStateTexture(fn_80039AB4(), 0, 0);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    o = *(u8**)(o + 0x74);
    while (o != NULL) {
        v.x = *(f32*)(*(u8**)(o + 0xEC) + 0xC);
        v.y = *(f32*)(*(u8**)(o + 0xEC) + 0x1C);
        v.z = *(f32*)(*(u8**)(o + 0xEC) + 0x2C);
        ((void (*)(Vec*))fn_3_EE96C)(&v);
        if (*(u8**)(o + 0x14) != NULL) {
            DOSetWorldMatrix(*(struct DODisplayObj**)(o + 0x14), *(MtxPtr*)(o + 0xEC));
            ((void (*)(u8*, u8*))fn_3_EE67C)(*(u8**)(o + 0x14), fn_80052734(fn_8005268C()) + 0x40);
        }
        o = *(u8**)(o + 0x100);
        GXSetTevDirect(0);
    }
}

// .text:0x000EEF24 size:0x80 mapped:0x8072DFB8
void fn_3_EEF24(void) {
    if (lbl_8036E548[0x3088] == 0) {
        fn_800B0A14_removeQueue(lbl_8036E548);
        return;
    }
    if (lbl_8036E548[0x307E] != 0) {
        fn_800BDA24(*(s32*)lbl_3_bss_B55C);
        fn_3_EE388();
        fn_3_EEB94();
        fn_800A7D4C(1, lbl_3_data_1BA5C + lbl_803CBBC0[0] * 8);
    }
}

// .text:0x000EEFA4 size:0x2C mapped:0x8072E038
void fn_3_EEFA4(void) {
    GXSetZMode(1, 3, 0);
}

// .text:0x000EEFD0 size:0x4 mapped:0x8072E064
void fn_3_EEFD0(void) {
    return;
}

// .text:0x000F13F8 size:0x50 mapped:0x8073048C
#pragma dont_inline off
void fn_3_F13F8(u8* p) {
    u8* o = **(u8***)(p + 0x74);
    u32 i;
    for (i = 0; i < *(u16*)(o + 6); i++) {
        u8* e = (*(u8***)(o + 0x18))[i];
        e[0x60] = 0;
        e[0xA4] = 0;
    }
    (*(u8**)(p + 0x74))[0x58] = 0;
}
#pragma dont_inline on

// 99%: only scheduling of the stfs 0xB8 / li r6,0 / li r0,4 at the join differs (inlined fn_3_F13F8 matches)
// .text:0x000EEFD4 size:0x244 mapped:0x8072E068
void fn_3_EEFD4(s32 idx) {
    Vec d;
    Vec ref;
    u8* e = *(u8**)lbl_3_common_bss_350E4 + idx * 0xE8;
    ref = *(Vec*)lbl_3_rodata_2D38;
    if (e[0xC6] < 3) {
        f32 t;
        f32 ang;
        u32 stad;
        u32 h;
        u8 v;
        d.x = *(f32*)(g_Ball + 0x318);
        d.y = lbl_3_rodata_2D5C;
        d.z = *(f32*)(g_Ball + 0x320);
        PSVECNormalize(&d, &d);
        t = (f32)acos(PSVECDotProduct(&ref, &d));
        ang = t;
        if (d.z < lbl_3_rodata_2D5C) {
            ang = lbl_3_rodata_2DD0 - t;
        }
        *(f32*)(e + 0xB8) = ang;
        *(f32*)(e + 0xBC) = lbl_3_rodata_2D54;
        e[0xC6] = 4;
        fn_3_F13F8(e);
        if (*(s16*)(g_Ball + 0x1B7A) != 2 && lbl_800E8754[4] != 0) {
            Vec t;
            CTRLGetTranslation((Control*)e, &t.x, &t.y, &t.z);
            fn_3_CB7E8(t.x, t.y - lbl_3_rodata_2DD8, t.z);
            e[0xC8] = 1;
        }
        stad = g_d_GameSettings[9];
        if (g_d_GameSettings[7] == 6) {
            v = lbl_3_data_84B8[0x12];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x12];
        }
        h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 9), v, 0x3F, 0);
        if (g_d_GameSettings[7] == 6) {
            v = lbl_3_data_84B8[0x13];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x13];
        }
        sndFXCtrl(h, 0x5B, v);
        fn_3_27648();
        g_FieldingLogic[0x13B] = 1;
    }
}

// .text:0x000EF218 size:0x4 mapped:0x8072E2AC
void fn_3_EF218(void) {
    return;
}

// .text:0x000EF21C size:0x1B8 mapped:0x8072E2B0
void fn_3_EF21C(u8* p) {
    u8* d = lbl_3_data_1B820;
    if (g_GameLogic[0x11E] == 2 && fn_800527C4(p + 0xA0) != 0) {
        switch (p[0xC6]) {
        case 0:
            if (p[0xC7] % *(s32*)(d + 0x154) == 0) {
                fn_80064430(p + 0xA0, 0, *(f32*)(d + 0x160), lbl_3_rodata_2D5C);
                return;
            }
            break;
        case 1:
            if (p[0xC7] % *(s32*)(d + 0x158) == 0) {
                fn_80064430(p + 0xA0, 0, *(f32*)(d + 0x164), lbl_3_rodata_2D5C);
                return;
            }
            break;
        case 2:
            if (p[0xC7] % *(s32*)(d + 0x15C) == 0) {
                u32 stad;
                u32 h;
                u8 v;
                fn_80064430(p + 0xA0, 1, *(f32*)(d + 0x168), *(f32*)(d + 0x174));
                stad = g_d_GameSettings[9];
                if (g_d_GameSettings[7] == 6) {
                    v = lbl_3_data_84B8[0x10];
                } else {
                    v = lbl_3_data_8404[stad * 0x1E + 0x10];
                }
                h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 8), v, 0x3F, 0);
                if (g_d_GameSettings[7] == 6) {
                    v = lbl_3_data_84B8[0x11];
                } else {
                    v = lbl_3_data_8404[stad * 0x1E + 0x11];
                }
                sndFXCtrl(h, 0x5B, v);
            }
            break;
        }
    }
}

// .text:0x000EF3D4 size:0x34 mapped:0x8072E468
void fn_3_EF3D4(u8* p, u8 idx) {
    fn_3_B97DC(*(void**)(p + 0x74), lbl_3_bss_B154[idx]);
}

// .text:0x000EF408 size:0x154 mapped:0x8072E49C
void fn_3_EF408(u8* p) {
    Vec a;
    Vec b;
    Vec c;
    f32 ang;
    f32 d;
    a.x = lbl_3_data_1B9A4[p[0x9C]].a - *(f32*)(p + 0xA0);
    a.y = lbl_3_rodata_2D5C;
    a.z = lbl_3_data_1B9A4[p[0x9C]].c - *(f32*)(p + 0xA8);
    PSVECNormalize(&a, &a);
    ang = -(lbl_3_rodata_2DDC * *(f32*)(p + 0xAC));
    b.x = (f32)cos(ang);
    b.y = lbl_3_rodata_2D5C;
    b.z = (f32)sin(ang);
    PSVECNormalize(&b, &b);
    d = PSVECDotProduct(&a, &b);
    if (d < lbl_3_rodata_2DE0) {
        d = lbl_3_rodata_2D70;
    }
    *(f32*)(p + 0xB4) = lbl_3_rodata_2DE8 * (f32)acos(d);
    PSVECCrossProduct(&a, &b, &c);
    if (c.y < lbl_3_rodata_2D5C) {
        *(s8*)(p + 0xC4) = 1;
    } else {
        *(s8*)(p + 0xC4) = -1;
    }
    p[0xC6] = 0;
}

// .text:0x000EF55C size:0x258 mapped:0x8072E5F0
void fn_3_EF55C(void) {
    return;
}

// .text:0x000EF7B4 size:0x4C mapped:0x8072E848
u32 fn_3_EF7B4(V3i v, s32 x) {
    return ((u8 (*)(V3i, s32))fn_3_EF55C)(v, x) != 0;
}

// .text:0x000EF800 size:0x90 mapped:0x8072E894
void fn_3_EF800(u8* p) {
    typedef struct { u8 pad[0x90]; u8 f : 1; u8 rest : 7; } FObj;
    if (p[0xC7] == 0) {
        CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA0), lbl_3_rodata_2DEC, *(f32*)(p + 0xA8));
        return;
    }
    if (p[0xC7] % 6 == 0) {
        ((FObj*)p)->f = 0;
    } else {
        ((FObj*)p)->f = 1;
    }
    p[0xC7]--;
}

// .text:0x000EF890 size:0xA0 mapped:0x8072E924
void fn_3_EF890(u8* p) {
    fn_3_F13F8(p);
    CTRLSetScale((Control*)p, 2.0f, 0.1f, 2.0f);
    p[0xC6] = 6;
    p[0xC7] = 0x4B;
}

// .text:0x000EF930 size:0x224 mapped:0x8072E9C4
void fn_3_EF930(void) {
    return;
}

// .text:0x000EFB54 size:0x630 mapped:0x8072EBE8
void fn_3_EFB54(u8* p) {
    return;
}

// .text:0x000F0184 size:0xA0 mapped:0x8072F218
void fn_3_F0184(void) {
    u32 i;
    if (lbl_3_bss_AEE0[8] != 0) {
        fn_800B0A14_removeQueue();
        lbl_3_bss_AEE0[8] = 0;
        return;
    }
    for (i = 0; i < lbl_3_bss_AEE0[0x33C]; i++) {
        u8* e = *(u8**)lbl_3_common_bss_350E4 + (i + lbl_3_bss_AEE0[0x33B]) * 0xE8;
        if (e != NULL && e[0xC6] == 3) {
            fn_3_EFB54(e);
        }
    }
}

// .text:0x000F0224 size:0x608 mapped:0x8072F2B8
void fn_3_F0224(void) {
    return;
}

// .text:0x000F082C size:0x778 mapped:0x8072F8C0
void fn_3_F082C(void) {
    return;
}

// .text:0x000F0FA4 size:0x454 mapped:0x80730038
void fn_3_F0FA4(void) {
    return;
}


// .text:0x000F1448 size:0xD0 mapped:0x807304DC
void fn_3_F1448(u8* p) {
    *(f32*)(p + 0xA0) = lbl_3_data_1B9A4[p[0x9C]].a;
    *(f32*)(p + 0xA4) = lbl_3_data_1B9A4[p[0x9C]].b;
    *(f32*)(p + 0xA8) = lbl_3_data_1B9A4[p[0x9C]].c;
    *(f32*)(p + 0xAC) = -lbl_3_data_1B9A4[p[0x9C]].d;
    p[0] = 0;
    CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA0), -*(f32*)(p + 0xA4), *(f32*)(p + 0xA8));
    CTRLSetRotation((Control*)p, 0.0f, *(f32*)(p + 0xAC), 0.0f);
    CTRLSetScale((Control*)p, lbl_3_rodata_2D50, lbl_3_rodata_2D50, lbl_3_rodata_2D50);
}

// .text:0x000F1518 size:0x15C mapped:0x807305AC
void fn_3_F1518(void) {
    return;
}

// .text:0x000F1674 size:0xDC mapped:0x80730708
void fn_3_F1674(void) {
    u32 stad = g_d_GameSettings[9];
    u8 v;
    u32 h;
    if (g_d_GameSettings[7] == 6) {
        v = lbl_3_data_84B8[10];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 10];
    }
    h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 5), v, 0x3F, 0);
    if (g_d_GameSettings[7] == 6) {
        v = lbl_3_data_84B8[11];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 11];
    }
    sndFXCtrl(h, 0x5B, v);
    fn_3_65A8();
    fn_3_27648();
    g_FieldingLogic[0x13B] = 1;
}

// .text:0x000F1750 size:0x154 mapped:0x807307E4
void fn_3_F1750(void) {
    return;
}

// .text:0x000F18A4 size:0x98 mapped:0x80730938
void fn_3_F18A4(u8* p) {
    u8* o = *(u8**)(lbl_8036E548 + 0x6C) + lbl_3_bss_B218[0] * 0x90 + 0x34;
    *(u8**)(p + 0x74) = o;
    *(f32*)(o + 0x5C) = 0.0f;
    o[0x59] = 1;
    fn_800B4CA0(*(void**)o, *(f32*)(o + 0x5C));
    *(f32*)(p + 0xB4) += 180.0;
    AnimateActorBones(*(void**)o);
}

// .text:0x000F193C size:0x4F0 mapped:0x807309D0
void fn_3_F193C(void) {
    return;
}

// .text:0x000F1E2C size:0x4D0 mapped:0x80730EC0
void fn_3_F1E2C(void) {
    return;
}

// .text:0x000F22FC size:0x14C mapped:0x80731390
void fn_3_F22FC(void) {
    return;
}

// .text:0x000F2448 size:0x2DC mapped:0x807314DC
void fn_3_F2448(void) {
    return;
}

// .text:0x000F2724 size:0x214 mapped:0x807317B8
void fn_3_F2724(void) {
    return;
}

// .text:0x000F2938 size:0x6C4 mapped:0x807319CC
void fn_3_F2938(void) {
    return;
}

// .text:0x000F2FFC size:0x1E4 mapped:0x80732090
void fn_3_F2FFC(void) {
    return;
}

// .text:0x000F31E0 size:0x5DC mapped:0x80732274
void fn_3_F31E0(void) {
    return;
}

// .text:0x000F37BC size:0x118 mapped:0x80732850
u32 fn_3_F37BC(u32 n, u32 k) {
    u32 r = 1;
    u32 i;
    for (i = 1; i <= k; i++) {
        r = r * (n - i + 1) / i;
    }
    return r;
}

// .text:0x000F38D4 size:0x130 mapped:0x80732968
void fn_3_F38D4(void) {
    return;
}

// .text:0x000F3A04 size:0x58 mapped:0x80732A98
void fn_3_F3A04(u8* p) {
    u32 i;
    u16 n = *(u16*)(*(u8**)(*(u8**)(p + 0x74)) + 6);
    for (i = 0; i < n; i++) {
    }
}

// .text:0x000F3A5C size:0x84 mapped:0x80732AF0
void fn_3_F3A5C(u8* p, f32 x, f32 y, f32 z, f32 r) {
    *(f32*)(p + 0xA0) = x;
    *(f32*)(p + 0xA4) = y;
    *(f32*)(p + 0xA8) = z;
    *(f32*)(p + 0xB4) = r;
    p[0] = 0;
    CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA0), -*(f32*)(p + 0xA4), *(f32*)(p + 0xA8));
    CTRLSetRotation((Control*)p, 0.0f, r, 0.0f);
}

// .text:0x000F3AE0 size:0xD0 mapped:0x80732B74
void fn_3_F3AE0(u8* p) {
    f32 rot, x, z;
    *(f32*)(p + 0xAC) = lbl_3_data_1B884[p[0x9C]].v.x;
    *(f32*)(p + 0xB0) = lbl_3_data_1B884[p[0x9C]].v.z;
    z = *(f32*)(p + 0xB0);
    x = *(f32*)(p + 0xAC);
    rot = -lbl_3_data_1B884[p[0x9C]].pad[0];
    *(f32*)(p + 0xA0) = x;
    *(f32*)(p + 0xA4) = 10.0f;
    *(f32*)(p + 0xA8) = z;
    *(f32*)(p + 0xB4) = rot;
    p[0] = 0;
    CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA0), -*(f32*)(p + 0xA4), *(f32*)(p + 0xA8));
    CTRLSetRotation((Control*)p, 0.0f, rot, 0.0f);
}

// .text:0x000F3BB0 size:0x120 mapped:0x80732C44
void fn_3_F3BB0(u8* p) {
    typedef struct { u8 pad[0x90]; u8 f : 1; u8 rest : 7; } FObj;
    f32 rot, x, z;
    *(f32*)(p + 0xAC) = lbl_3_data_1B884[p[0x9C]].v.x;
    *(f32*)(p + 0xB0) = lbl_3_data_1B884[p[0x9C]].v.z;
    z = *(f32*)(p + 0xB0);
    x = *(f32*)(p + 0xAC);
    rot = -lbl_3_data_1B884[p[0x9C]].pad[0];
    *(f32*)(p + 0xA0) = x;
    *(f32*)(p + 0xA4) = 10.0f;
    *(f32*)(p + 0xA8) = z;
    *(f32*)(p + 0xB4) = rot;
    p[0] = 0;
    CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA0), -*(f32*)(p + 0xA4), *(f32*)(p + 0xA8));
    CTRLSetRotation((Control*)p, 0.0f, rot, 0.0f);
    p[0xC1] = 0;
    ((FObj*)p)->f = 1;
    *(u8**)(p + 0x74) = *(u8**)(lbl_8036E548 + 0x6C) + (lbl_3_bss_B219[0] + p[0x9C]) * 0x90 + 0x34;
    p[0xC4] = 0;
    p[0x99] = 1;
}

// .text:0x000F3CD0 size:0x22C mapped:0x80732D64
void fn_3_F3CD0(void) {
    return;
}

// .text:0x000F3EFC size:0x3A4 mapped:0x80732F90
void fn_3_F3EFC(void) {
    return;
}

// .text:0x000F42A0 size:0x3CC mapped:0x80733334
void fn_3_F42A0(void) {
    return;
}

// .text:0x000F466C size:0x30 mapped:0x80733700
extern void fn_3_27648(void);

void fn_3_F466C(void) {
    fn_3_27648();
    g_FieldingLogic[0x13B] = 1;
}

// .text:0x000F469C size:0x4 mapped:0x80733730
void fn_3_F469C(void) {
    return;
}

// .text:0x000F46A0 size:0x500 mapped:0x80733734
void fn_3_F46A0(void) {
    return;
}

// .text:0x000F4BA0 size:0xAC mapped:0x80733C34
void fn_3_F4BA0(u8* p) {
    Vec tgt;
    Vec d;
    PSVECAdd((Vec*)(p + 0xA8), (Vec*)(p + 0xB4), (Vec*)(p + 0xA8));
    CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA8), -*(f32*)(p + 0xAC), *(f32*)(p + 0xB0));
    tgt.x = lbl_3_data_1B884[p[0x9C]].v.x;
    tgt.y = lbl_3_data_1B884[p[0x9C]].v.y;
    tgt.z = lbl_3_data_1B884[p[0x9C]].v.z;
    PSVECSubtract(&tgt, (Vec*)(p + 0xA8), &d);
    *(f32*)(p + 0xB4) = 0.2f * d.x;
    *(f32*)(p + 0xBC) = 0.2f * d.z;
}

// .text:0x000F4C4C size:0xB4 mapped:0x80733CE0
void fn_3_F4C4C(u8* p) {
    f32 a = -*(f32*)(p + 0xC0);
    f32 c;
    a = lbl_3_rodata_2DDC * a;
    *(f32*)(p + 0xB4) = lbl_3_rodata_2E88 * (f32)sin(a);
    *(f32*)(p + 0xB8) = 0.0f;
    c = cos(a);
    *(f32*)(p + 0xBC) = lbl_3_rodata_2E88 * -c;
    PSVECScale((Vec*)(p + 0xB4), -1.0f, (Vec*)(p + 0xB4));
}

// .text:0x000F4D00 size:0xAC mapped:0x80733D94
void fn_3_F4D00(u8* p) {
    Vec d;
    Vec tgt;
    PSVECAdd((Vec*)(p + 0xA8), (Vec*)(p + 0xB4), (Vec*)(p + 0xA8));
    CTRLSetTranslation((Control*)p, *(f32*)(p + 0xA8), -*(f32*)(p + 0xAC), *(f32*)(p + 0xB0));
    tgt.x = lbl_3_data_1B884[p[0x9C]].v.x;
    tgt.y = lbl_3_data_1B884[p[0x9C]].v.y;
    tgt.z = lbl_3_data_1B884[p[0x9C]].v.z;
    PSVECSubtract(&tgt, (Vec*)(p + 0xA8), &d);
    *(f32*)(p + 0xB4) = 0.2f * d.x;
    *(f32*)(p + 0xBC) = 0.2f * d.z;
}

// .text:0x000F4DAC size:0x210 mapped:0x80733E40
void fn_3_F4DAC(void) {
    return;
}

// .text:0x000F4FBC size:0x710 mapped:0x80734050
void fn_3_F4FBC(void) {
    return;
}

// .text:0x000F56CC size:0x564 mapped:0x80734760
void fn_3_F56CC(void) {
    return;
}

// .text:0x000F5C30 size:0x248 mapped:0x80734CC4
void fn_3_F5C30(void) {
    return;
}

// .text:0x000F5E78 size:0x84 mapped:0x80734F0C
s32 fn_3_F5E78(u8 id) {
    u32 n = *(u32*)(lbl_3_common_bss_350E4 + 0x30);
    u8* e = *(u8**)(lbl_3_common_bss_350E4 + 0x14) + n * 8;
    for (; n != 0; e -= 8, n--) {
        if (id == *(s32*)(e - 4)) {
            return n - 1;
        }
    }
    OSPanic(lbl_3_rodata_2DB8, 0x637, lbl_3_rodata_2F10);
    return 0;
}

// .text:0x000F5EFC size:0x2C mapped:0x80734F90
s32 fn_3_F5EFC(u32* a, u32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x000F5F28 size:0x24 mapped:0x80734FBC
s32 fn_3_F5F28(f32* a, f32* b) {
    f32 x = *a;
    f32 y = *b;
    if (x < y) {
        return -1;
    }
    return x > y;
}

// .text:0x000F5F4C size:0x138 mapped:0x80734FE0
void fn_3_F5F4C(void) {
    return;
}

// .text:0x000F6084 size:0x480 mapped:0x80735118
void fn_3_F6084(void) {
    return;
}

// .text:0x000F6504 size:0xC4 mapped:0x80735598
s32 fn_3_F6504(s32 idx, s32 arg) {
    u8* c = *(u8**)lbl_3_common_bss_350E4 + idx * 0xE8;
    u8 t = c[0x9D];
    void* m = (void*)arg;
    if (t == 2) {
        if (c[0xC6] < 3 && g_Ball[0x1BC9] != 1) {
            CTRLBuildMatrix((Control*)c, m);
        } else {
            return 0;
        }
    } else if (t == 0) {
        if (c[0xC1] == 2) return 0;
        if (*(s16*)(g_Ball + 0x1B7A) >= 2) return 0;
        CTRLBuildMatrix((Control*)c, m);
    } else {
        CTRLBuildMatrix((Control*)c, m);
    }
    return ((StadObj78**)lbl_3_common_bss_350E4)[0][idx].w78;
}

// .text:0x000F65C8 size:0x100 mapped:0x8073565C
void fn_3_F65C8(s32* n) {
    struct { Control c; u8 pad[0x14]; } c;
    Mtx m;
    u16 k;
    StadObj78* so = &((StadObj78**)lbl_3_common_bss_350E4)[0][lbl_3_bss_B21A];
    void* o;
    k = (*(u16**)(lbl_3_common_bss_350E4 + 0x40))[*n - 1] + (*(s32**)(lbl_3_common_bss_350E4 + 0x3C))[*n - 1];
    (*(u16**)(lbl_3_common_bss_350E4 + 0x40))[*n] = k;
    (*(u32**)(lbl_3_common_bss_350E4 + 0x44))[k] = lbl_3_bss_B21A;
    (*(s32**)(lbl_3_common_bss_350E4 + 0x3C))[*n]++;
    o = (void*)so->w78;
    c.c.type = 0;
    CTRLBuildMatrix(&c.c, m);
    fn_3_B8464(m, o);
    fn_3_B8414(*(u8**)(lbl_3_common_bss_350E4 + 0x48) + *n * 0x18, *(u8**)(lbl_3_common_bss_350E4 + 0x48) + (*n * 2 + 1) * 0xC);
    (*n)++;
}

// .text:0x000F66C8 size:0x270 mapped:0x8073575C
void fn_3_F66C8(void) {
    return;
}

// .text:0x000F6938 size:0x15C mapped:0x807359CC
void fn_3_F6938(void) {
    return;
}

// .text:0x000F6A94 size:0x1CC mapped:0x80735B28
void fn_3_F6A94(void) {
    return;
}

// .text:0x000F6C60 size:0x36C mapped:0x80735CF4
void fn_3_F6C60(void) {
    return;
}

// .text:0x000F6FCC size:0x10 mapped:0x80736060
extern u8 lbl_3_bss_AEE8;

void fn_3_F6FCC(void) {
    lbl_3_bss_AEE8 = 1;
}

// .text:0x000F6FDC size:0x1468 mapped:0x80736070
void fn_3_F6FDC(void) {
    return;
}


#pragma dont_inline off
