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
static inline u32 binomIn(u32 n, u32 k) {
    u32 r = 1;
    u32 i;
    for (i = 1; i <= k; i++) {
        r = r * (n - i + 1) / i;
    }
    return r;
}
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
extern void* memcpy(void*, void*, u32);
extern f32 lbl_3_rodata_2D50;
extern f32 lbl_3_rodata_2EE8;
extern f32 lbl_3_rodata_2DEC;
extern const f32 lbl_3_rodata_2DDC;
extern f32 lbl_3_rodata_2E88;
extern f64 sin(f64);
extern f32 lbl_3_bss_AF04[];
extern f32 lbl_3_rodata_2D58;
extern u8 lbl_3_data_1BA70[];
extern u8 lbl_3_data_1B824[];
extern f64 __fabs(f64);
extern u8* fn_80052768_getCamera(int);
extern char lbl_3_rodata_2D44[];
extern f32 lbl_3_rodata_2D50;
extern f32 lbl_3_rodata_2DA0;
extern f32 lbl_3_rodata_2DA4;
extern f64 lbl_3_rodata_2DA8;
extern f32 lbl_3_rodata_2DB0;
extern f32 lbl_3_rodata_2DB4;
extern void DCFlushRange(void*, u32);
extern f32 lbl_3_rodata_2D74;
extern f32 lbl_3_rodata_2DF0;
extern u8 lbl_800E8754[];
extern void fn_3_CB7E8(f32, f32, f32);
extern char lbl_3_rodata_2D38[];
extern f64 lbl_3_rodata_2DD0;
extern const f32 lbl_3_rodata_2D54;
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
extern void fn_3_B8574(void);
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

// 70%: matrix setup is right; instruction scheduling of the first PSMTXCopy/scale block and const load forms differ
// .text:0x000EE100 size:0x288 mapped:0x8072D194
void fn_3_EE100(u8* obj, f32 (*mtx)[4]) {
    Mtx b;
    Mtx a;
    Mtx c;
    Mtx44 d;
    GXColor col;
    f32 f31;
    f32 f9;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, col);
    GXSetNumChans(1);
    f31 = lbl_3_bss_AF04[0];
    PSMTXCopy((f32(*)[4])(obj + 0x18), a);
    PSMTXCopy(mtx, b);
    f9 = 1.0f + f31;
    b[0][3] += ((f32*)lbl_3_data_1BA70)[0];
    b[0][0] *= f9;
    b[0][1] *= f9;
    b[1][3] += ((f32*)lbl_3_data_1BA70)[1];
    b[0][2] *= f9;
    b[1][0] *= f9;
    b[1][1] *= f9;
    b[1][2] *= f9;
    PSMTXConcat(b, a, a);
    PSMTXIdentity(c);
    PSMTX44Copy((f32(*)[4])fn_80052734(fn_8005268C()), d);
    c[0][0] = d[0][0];
    c[0][2] = d[0][2];
    c[1][1] = d[1][1];
    c[1][2] = d[1][2];
    c[2][2] = d[3][2];
    PSMTXConcat(c, a, a);
    PSMTXIdentity(c);
    c[0][0] = lbl_3_rodata_2D54;
    c[0][2] = lbl_3_rodata_2D54;
    c[1][1] = lbl_3_rodata_2D58;
    c[1][2] = lbl_3_rodata_2D54;
    c[2][2] = lbl_3_rodata_2D50;
    c[2][3] = lbl_3_rodata_2D5C;
    c[1][3] = lbl_3_rodata_2D5C;
    c[0][3] = lbl_3_rodata_2D5C;
    PSMTXConcat(c, a, a);
    GXLoadTexMtxImm(a, 0x1E, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_POS, 0x1E, 0, 0x7D);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
}

// .text:0x000EE388 size:0x2F4 mapped:0x8072D41C
void fn_3_EE388(void) {
    return;
}

// .text:0x000EE67C size:0x2F0 mapped:0x8072D710
void fn_3_EE67C(void) {
    return;
}

// 90%: mtx stores: orig does first via base+0x23c and the second via a separate pointer reg (r3+0x10); const load order/addi forms differ
// .text:0x000EE96C size:0x228 mapped:0x8072DA00
void fn_3_EE96C(u8* pos) {
    Mtx m;
    Vec t;
    u8* st = lbl_3_bss_AEE0;
    Vec ref = *(Vec*)lbl_3_rodata_2D44;
    f32* mp;
    u8* cam;
    f32 mag;
    f32 clamp;
    f32 dist;
    f32 sc;
    s32 s0;
    s32 s1;
    cam = fn_80052768_getCamera(fn_8005268C());
    PSVECSubtract((Vec*)(cam + 0x70), (Vec*)(cam + 0x7C), &t);
    mag = PSVECMag(&t);
    if (mag != lbl_3_rodata_2D5C) {
        PSVECNormalize(&t, &t);
    } else {
        t.y = lbl_3_rodata_2D5C;
        t.x = lbl_3_rodata_2D5C;
        t.z = lbl_3_rodata_2D50;
    }
    acos(PSVECDotProduct(&t, &ref));
    PSVECSubtract((Vec*)(cam + 0x70), (Vec*)pos, &t);
    clamp = PSVECMag(&t);
    dist = clamp;
    if (clamp < lbl_3_rodata_2DA0) {
        clamp = lbl_3_rodata_2DA0;
    }
    PSMTXCopy((f32(*)[4])(cam + 0x40), m);
    sc = lbl_3_rodata_2DA4 / clamp;
    ((struct { u8 pad[0x23C]; f32 m[2][3]; }*)st)->m[0][0] = sc;
    ((struct { u8 pad[0x23C]; f32 m[2][3]; }*)st)->m[1][1] = sc * (f32)(lbl_3_rodata_2DA8 - __fabs(lbl_3_rodata_2D54 * (ref.y * m[1][1])));
    if (dist < lbl_3_rodata_2DB0) {
        s0 = 4;
        s1 = 4;
    } else if (dist < lbl_3_rodata_2DB4) {
        s0 = 3;
        s1 = 3;
    } else {
        s0 = 2;
        s1 = 2;
    }
    *(u32*)(st + 0x14) = 0;
    DCFlushRange(*(void**)(st + 0x238), 0x200);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])(st + 0x23C), 2);
    GXLoadTexObj((GXTexObj*)(st + 0x254), GX_TEXMAP7);
    GXSetIndTexOrder(GX_IND_TEX_STAGE_0, GX_TEXCOORD0, GX_TEXMAP7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(GX_IND_TEX_STAGE_0, s0, s1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_IND_TEX_STAGE_0, 1, 0, GX_ITM_0);
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

// 99%: only the position of stfs f2,0xB8 relative to the inlined fn_3_F13F8 zero-reg movs differs (one slot late)
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
        {
            f32 half = lbl_3_rodata_2D54;
            *(f32*)(e + 0xB8) = ang;
            *(f32*)(e + 0xBC) = half;
        }
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

// 60%: two box-edge loops; lfsx/addi index pattern and per-loop register numbering differ
// .text:0x000EF55C size:0x258 mapped:0x8072E5F0
u32 fn_3_EF55C(Vec p, u8 idx) {
    u8 a[4] = {1, 3, 0, 2};
    u8 b[4] = {0, 1, 2, 3};
    Vec v28;
    Vec v1c;
    Vec v10;
    u8* t;
    u32 i;
    u8* q;
    s8 sgn;
    f32 z = lbl_3_rodata_2D5C;
    if (p.y > z) {
        return 1;
    }
    t = lbl_3_data_1B824 + idx * 32;
    q = a;
    for (i = 0, sgn = -1; i < 2; i++, q += 2, sgn += 2) {
        u32 c0 = q[0] * 8;
        u32 c1 = q[1] * 8;
        f32 x0 = *(f32*)(t + c0);
        f32 x1 = *(f32*)(t + c1);
        f32 z0 = *(f32*)(t + (c0 + 4));
        f32 z1 = *(f32*)(t + (c1 + 4));
        v1c.y = z;
        v28.x = p.x - x0;
        v28.z = p.z - z0;
        v1c.x = x1 - x0;
        v1c.z = z1 - z0;
        v28.y = z;
        PSVECNormalize(&v28, &v28);
        PSVECNormalize(&v1c, &v1c);
        PSVECCrossProduct(&v1c, &v28, &v10);
        if (v10.y * (f32)sgn < z) {
            return 1;
        }
    }
    z = z;
    q = b;
    for (i = 0, sgn = -1; i < 2; i++, q += 2, sgn += 2) {
        u32 c0 = q[0] * 8;
        u32 c1 = q[1] * 8;
        f32 x0 = *(f32*)(t + c0);
        f32 x1 = *(f32*)(t + c1);
        f32 z0 = *(f32*)(t + (c0 + 4));
        f32 z1 = *(f32*)(t + (c1 + 4));
        v1c.y = z;
        v28.x = p.x - x0;
        v28.z = p.z - z0;
        v1c.x = x1 - x0;
        v1c.z = z1 - z0;
        v28.y = z;
        PSVECNormalize(&v28, &v28);
        PSVECNormalize(&v1c, &v1c);
        PSVECCrossProduct(&v1c, &v28, &v10);
        if (v10.y * (f32)sgn < z) {
            return 1;
        }
    }
    return 0;
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

struct StadCtlA {
    Control c;
    u8 pad34[0x74 - 0x3C];
    u8** obj;
    u8 pad78[0x90 - 0x78];
    u8 fl90_hi : 1;
    u8 fl90_lo : 7;
    u8 pad91[8];
    u8 f99;
    u8 pad9A[2];
    u8 idx;
    u8 pad9D[3];
    f32 xa0, ya4, za8, xac, zb0, rb4;
    u8 padB8[0xC0 - 0xB8];
    u8 fc0;
    s8 fc1;
    u8 padC2[2];
    u8 fc4;
    u8 fc5;
    u8 fc6;
    u8 fc7;
};
typedef struct StadCtlA StadCtlA;

// .text:0x000F1518 size:0x15C mapped:0x807305AC
extern u32 lbl_3_bss_B154[];
void fn_3_F1518(StadCtlA* p) {
    p->fc5 = ((u8*)&lbl_3_data_1B9A4[0].f)[p->idx * 0x18];
    p->fc6 = 1;
    p->fc7 = 0;
    p->fc1 = -1;
    if (!p->fl90_hi) {
        p->fl90_hi = 1;
    }
    p->f99 = 1;
    p->zb0 = 0.0f;
    p->xa0 = lbl_3_data_1B9A4[p->idx].a;
    p->ya4 = lbl_3_data_1B9A4[p->idx].b;
    p->za8 = lbl_3_data_1B9A4[p->idx].c;
    p->xac = -lbl_3_data_1B9A4[p->idx].d;
    p->c.type = 0;
    CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
    CTRLSetRotation(&p->c, 0.0f, p->xac, 0.0f);
    CTRLSetScale(&p->c, 1.0f, 1.0f, 1.0f);
    fn_3_B97DC(p->obj, lbl_3_bss_B154[0]);
    ((u8*)p->obj)[0x58] = 1;
    p->fc0 = 0;
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
extern f32 fn_800B4A94(void*);
extern const f32 lbl_3_rodata_2E30;
void fn_3_F1750(StadCtlA* p) {
    u8** o = p->obj;
    f32 r;
    f32 x;
    f32 z;
    if (!fn_800B4A94(*o)) {
        p->xac = lbl_3_data_1B884[p->idx].v.x;
        p->zb0 = lbl_3_data_1B884[p->idx].v.z;
        z = p->zb0;
        x = p->xac;
        r = -lbl_3_data_1B884[p->idx].pad[0];
        p->xa0 = x;
        p->ya4 = lbl_3_rodata_2E30;
        p->za8 = z;
        p->rb4 = r;
        p->c.type = 0;
        CTRLSetTranslation(&p->c, p->xa0, -p->ya4, p->za8);
        CTRLSetRotation(&p->c, 0.0f, r, 0.0f);
        p->fc1 = 0;
        p->fl90_hi = 1;
        p->obj = (u8**)(*(u8**)(lbl_8036E548 + 0x6C) + (lbl_3_bss_B219[0] + p->idx) * 0x90 + 0x34);
        p->fc4 = 0;
        p->f99 = 1;
        return;
    }
    AnimateActorBones(*o);
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
extern void fn_3_253A4(s8, s16);
extern s16 fn_3_9FB8C(f32, f32);
extern u8 g_Fielders[];
extern u8 lbl_3_bss_B21B;
extern u8 lbl_3_bss_B21C;
extern const f32 lbl_3_rodata_2E40;
extern const f32 lbl_3_rodata_2D54;
typedef struct {
    u8 p0[0xAC];
    f32 a;
    f32 p1[2];
    f32 b8;
    f32 bc;
    u8 p2;
    s8 c1;
    u8 p3[4];
    u8 c6;
    u8 p4[0xE8 - 0xC7];
} StObjE8;
void fn_3_F22FC(u8* p, s32 idx) {
    Vec d;
    s8 id = idx;
    u8* f = g_Fielders + id * 0x268;
    u8* cnt;
    StObjE8* o;
    u32 i;
    PSVECSubtract((Vec*)f, (Vec*)(p + 0xA0), &d);
    d.y = lbl_3_rodata_2D5C;
    PSVECNormalize(&d, &d);
    fn_3_253A4(id, (s16)fn_3_9FB8C(d.x, d.z));
    fn_800527C4(p + 0xA0);
    cnt = f + 0x217;
    for (i = 0; i < lbl_3_bss_B21C; i++) {
        o = (StObjE8*)(*(u8**)lbl_3_common_bss_350E4) + (lbl_3_bss_B21B + i);
        if (o->c6 == 3 && o->c1 == (s8)idx) {
            o->b8 = lbl_3_rodata_2DDC * (-o->a - lbl_3_rodata_2E40);
            o->c6 = 4;
            o->bc = lbl_3_rodata_2D54;
            (*cnt)--;
        }
    }
}


// .text:0x000F2448 size:0x2DC mapped:0x807314DC
void fn_3_F2448(void) {
    return;
}

// .text:0x000F2724 size:0x214 mapped:0x807317B8
extern f64 __fabs(f64);
extern const f64 lbl_3_rodata_2E58;
extern const f64 lbl_3_rodata_2E60;
void fn_3_F2724(u8* p, u8* q) {
    Vec d;
    f32 c;
    f32 s;
    f32 s2;
    f32 c2;
    f32 az;
    f32 ax;
    f64 ta;
    f64 tb;
    sin(-(lbl_3_rodata_2DDC * *(f32*)(p + 0xB4)));
    cos(-(lbl_3_rodata_2DDC * *(f32*)(p + 0xB4)));
    PSVECSubtract((Vec*)(q + 0xA0), (Vec*)(p + 0xA0), &d);
    d.y = lbl_3_rodata_2D5C;
    c = (f32)cos(-(lbl_3_rodata_2DDC * *(f32*)(p + 0xB4)));
    s = (f32)sin(-(lbl_3_rodata_2DDC * *(f32*)(p + 0xB4)));
    s2 = (f32)sin(-(lbl_3_rodata_2DDC * *(f32*)(p + 0xB4)));
    c2 = (f32)cos(-(lbl_3_rodata_2DDC * *(f32*)(p + 0xB4)));
    ta = __fabs(d.x * c + d.z * s);
    tb = __fabs(d.x * -s2 + d.z * c2);
    ax = ta;
    az = tb;
    if (ax <= lbl_3_rodata_2E58 && az <= lbl_3_rodata_2E60) {
        u32 stad;
        u8 v;
        u32 h;
        q[0xC6] = 5;
        stad = g_d_GameSettings[9];
        if (g_d_GameSettings[7] == 6) {
            v = lbl_3_data_84B8[0x16];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x16];
        }
        h = sndFXStartEx((u16)(((u16*)lbl_3_data_81DC)[stad] + 0xB), v, 0x3F, 0);
        if (g_d_GameSettings[7] == 6) {
            v = lbl_3_data_84B8[0x17];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 0x17];
        }
        sndFXCtrl(h, 0x5B, v);
    }
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
static u32 lbl_3_bss_B244[7];
void fn_3_F38D4(void) {
    u32 i;
    for (i = 0; i < 7; i++) {
        lbl_3_bss_B244[i] = binomIn(6, i);
    }
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
void fn_3_F5F4C(Mtx m) {
    extern const f32 lbl_3_rodata_2E30, lbl_3_rodata_2F2C, lbl_3_rodata_2F30, lbl_3_rodata_2F34;
    Vec v;
    u8* g;
    s32 off;
    u32 i;
    memcpy(&v, g_Ball, 0xC);
    PSMTXMultVec(m, &v, &v);
    g = lbl_3_common_bss_350E4;
    for (i = 0, off = 0; i < *(u32*)(g + 0x30); off += 8, i++) {
        f32* e = (f32*)(*(u8**)(g + 0x14) + off);
        u8* o = *(u8**)g + ((s32*)e)[1] * 0xE8;
        if ((o[0x90] >> 7) & 1) {
            if (o[0x9D] == 1) {
                e[0] = lbl_3_rodata_2D50;
            } else {
                f32 d = e[0];
                f32 lo = lbl_3_rodata_2D74 + v.z;
                if (d < lo) {
                    e[0] = lbl_3_rodata_2D50;
                } else if (d > lbl_3_rodata_2E30 + v.z) {
                    e[0] = lbl_3_rodata_2F2C;
                } else {
                    { f32 t = d - lo; e[0] = lbl_3_rodata_2DA8 - lbl_3_rodata_2F30 * (t * lbl_3_rodata_2F34); }
                }
            }
        }
    }
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
void fn_3_F6938(s32* n) {
    struct { Control c; u8 pad[0x8]; } c;
    Mtx m;
    s32 i;
    s32 idx;
    u16 k;
    u8* e;
    void* o;
    extern u8 lbl_3_bss_B21F;
    extern u8 lbl_3_bss_B220[];
    extern f32 lbl_3_rodata_2F40[];
    for (i = 0; i < lbl_3_bss_B220[0]; i++) {
        k = (*(u16**)(lbl_3_common_bss_350E4 + 0x40))[*n - 1] + (*(s32**)(lbl_3_common_bss_350E4 + 0x3C))[*n - 1];
        (*(u16**)(lbl_3_common_bss_350E4 + 0x40))[*n] = k;
        idx = lbl_3_bss_B21F + i;
        (*(u32**)(lbl_3_common_bss_350E4 + 0x44))[k] = idx;
        (*(s32**)(lbl_3_common_bss_350E4 + 0x3C))[*n]++;
        e = *(u8**)lbl_3_common_bss_350E4 + idx * 0xE8;
        o = (void*)*(s32*)(e + 0x78);
        c.c.type = 0;
        CTRLSetTranslation(&c.c, lbl_3_data_1B884[e[0x9C]].v.x, -lbl_3_data_1B884[e[0x9C]].v.y, lbl_3_data_1B884[e[0x9C]].v.z);
        CTRLSetScale(&c.c, lbl_3_rodata_2F40[0], lbl_3_rodata_2F40[0], lbl_3_rodata_2F40[0]);
        CTRLBuildMatrix(&c.c, m);
        fn_3_B8574();
        fn_3_B8464(m, o);
        fn_3_B8414(*(u8**)(lbl_3_common_bss_350E4 + 0x48) + *n * 0x18, *(u8**)(lbl_3_common_bss_350E4 + 0x48) + (*n * 2 + 1) * 0xC);
        (*n)++;
    }
}

// .text:0x000F6A94 size:0x1CC mapped:0x80735B28
void fn_3_F6A94(s32* n) {
    struct { Control c; u8 pad[4]; } c;
    Mtx m;
    s32 i;
    u16 k;
    u32 off;
    void* o;
    extern u8 lbl_3_bss_B21D[];
    extern u8 lbl_3_bss_B21E[];
    extern f32 lbl_3_rodata_2F44[];
    extern f32 lbl_3_rodata_2F48[];
    extern f32 lbl_3_rodata_2F4C[];
    extern f32 lbl_3_rodata_2F50[];
    extern f32 lbl_3_rodata_2F54[];
    k = (*(u16**)(lbl_3_common_bss_350E4 + 0x40))[*n - 1] + (*(s32**)(lbl_3_common_bss_350E4 + 0x3C))[*n - 1];
    (*(u16**)(lbl_3_common_bss_350E4 + 0x40))[*n] = k;
    off = k * 4;
    for (i = 0; i < lbl_3_bss_B21E[0]; i++) {
        *(u32*)(*(u8**)(lbl_3_common_bss_350E4 + 0x44) + off) = lbl_3_bss_B21D[0] + i;
        off += 4;
        (*(s32**)(lbl_3_common_bss_350E4 + 0x3C))[*n]++;
    }
    fn_3_B8574();
    o = (void*)((StadObj78**)lbl_3_common_bss_350E4)[0][lbl_3_bss_B21D[0]].w78;
    c.c.type = 0;
    CTRLSetTranslation(&c.c, lbl_3_rodata_2F44[0], ((f32*)&lbl_3_rodata_2D5C)[0], lbl_3_rodata_2F48[0]);
    CTRLBuildMatrix(&c.c, m);
    fn_3_B8464(m, o);
    c.c.type = 0;
    CTRLSetTranslation(&c.c, lbl_3_rodata_2F4C[0], lbl_3_rodata_2F50[0], lbl_3_rodata_2F54[0]);
    CTRLBuildMatrix(&c.c, m);
    fn_3_B8464(m, o);
    if ((*(u32**)(lbl_3_common_bss_350E4 + 0x3C))[*n] != 0) {
        fn_3_B8414(*(u8**)(lbl_3_common_bss_350E4 + 0x48) + *n * 0x18, *(u8**)(lbl_3_common_bss_350E4 + 0x48) + (*n * 2 + 1) * 0xC);
        (*n)++;
    }
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
