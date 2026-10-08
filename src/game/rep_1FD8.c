#include "game/rep_1FD8.h"
#include "header_rep_data.h"

#include "static/UnknownHomes_Static.h"
#include "Dolphin/vec.h"
#include "Dolphin/mtxext.h"
typedef struct C4724P {
    struct C4724P* next;
    f32 x, y, z;
    f32 vx, vy, vz;
    f32 f1C, f20, f24;
    u8 pad28[0x38 - 0x28];
    f32 f38, f3C;
    u8 a40, a41, a42;
    u8 a43;
    u8 pad44[4];
    s16 s48;
    s16 s4A;
    u8 pad4C[1];
    u8 f4D;
    u8 f4E;
    u8 f4F;
    u8 f50;
} C4724P;
typedef struct { u8 pad0[0xC]; C4724P* head; s32 f10; u16 f14; u8 pad16[2]; Vec* f18; u8 pad1C[4]; void* f20; s32 f24; } C4724Hdr;
extern const u8 lbl_3_rodata_2028[];
extern const f32 lbl_3_rodata_20FC;
extern const f64 lbl_3_rodata_2100;
extern const f64 lbl_3_rodata_2110;
extern const f64 lbl_3_rodata_2120;
extern const f32 lbl_3_rodata_2108;
extern const f32 lbl_3_rodata_20D4;
extern const f32 lbl_3_rodata_2158;
extern const f32 lbl_3_rodata_215C;
extern const f32 lbl_3_rodata_2160[];
extern const f32 lbl_3_rodata_2164;
extern const f32 lbl_3_rodata_2128;
extern f64 sin(f64);
extern f64 cos(f64);
extern const f64 lbl_3_rodata_2118;
extern const f64 lbl_3_rodata_2130;
extern const f64 lbl_3_rodata_2140;
extern const f32 lbl_3_rodata_2138;
extern void fn_3_C2644(void);
extern const f32 lbl_3_rodata_213C;
extern u8 lbl_3_bss_9D81;
extern u32 lbl_3_bss_9D8C;
extern const f32 lbl_3_rodata_214C;
extern void fn_800528B4(void);
extern int rand(void);
extern void CTRLBuildMatrix(void*);
extern void CTRLSetTranslation(void*, f32, f32, f32);
extern u8* lbl_3_bss_9D98;
extern u8* lbl_3_common_bss_350E4[];
extern void fn_3_B8184(void);
extern void fn_3_B828C(void*);
extern void fn_800BF058(void*);
extern void fn_800BDF70(void*);
extern u32 lbl_3_bss_9D84;
extern u32 fn_80033A24(void*, int, int, int, int, u8);

extern u32 lbl_3_bss_9D9C;
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern u16 lbl_3_data_81DC[];
extern u32 sndFXStartEx(int, u8, u8, u8);
extern void sndFXCtrl(int, int, u8);
extern u8 g_Ball[];
extern const f32 lbl_3_rodata_20F4;
extern const f32 lbl_3_rodata_20F8;
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int, int);
extern void GXSetVtxAttrFmt(int, int, int, int, int);
extern void GXSetChanCtrl(int, int, int, int, int, int, int);
extern void GXSetNumChans(int);
extern void GXSetNumTexGens(int);
extern void GXSetCullMode(int);
extern void GXSetProjection(void*, int);
extern void GXLoadPosMtxImm(void*, int);
extern void GXSetCurrentMtx(int);
extern void GXSetNumTevStages(int);
extern void GXSetTevOrder(int, int, int, int);
extern void GXSetTevColorIn(int, int, int, int, int);
extern void GXSetTevColorOp(int, int, int, int, int, int);
extern void GXSetTevAlphaIn(int, int, int, int, int);
extern void GXSetTevAlphaOp(int, int, int, int, int, int);
extern void fn_8005268C(void);
extern u8* fn_80052734(void);
extern Vec lbl_3_rodata_2080;
extern f32 lbl_3_rodata_2178;
extern void* memset(void*, int, u32);
extern s32 fn_8001B728(s32, s32, void*);
extern void fn_3_25844(u32, int);
extern u8 g_GameLogic[];
extern u8 g_Minigame[];
extern u8* lbl_803CC1B8;
extern u32 lbl_3_bss_9D94;
typedef struct DspObj2 DspObj2;
struct DspObj2 {
    u8 pad0[0x14];
    void* w14;
    u8 pad18[0x4C];
    void* w64;
    void* w68;
    u8 pad6C[8];
    DspObj2* child;
    u8 pad78[4];
    void* w7C;
    u8 pad80[0x6C];
    void* wEC;
    u8 padF0[0x10];
    DspObj2* next;
};
extern void DOSetWorldMatrix(void*, void*);
extern void DOVARenderSkin(void*, void*, void*, void*, int, int);
extern void fn_8003A8A0();
extern u32 lbl_3_bss_9D88;
extern u16 lbl_3_data_177F0;
typedef struct Rep1FD8Ent {
    u8 pad0[8];
    Mtx m;
    void* w38;
} Rep1FD8Ent;
extern Rep1FD8Ent lbl_3_data_17804[];
extern u8 lbl_803CBBC0[];
extern Vec lbl_3_bss_9DE8[];
extern u8 lbl_3_bss_9E48[];
extern u8* lbl_3_bss_9E50[];
extern u8 lbl_80371C30[];
extern void fn_800528C0(f32, f32, f32, s16*, s16*);
extern u32 lbl_3_bss_9D90;
extern void fn_800A7D4C(int, Rep1FD8Ent*);
extern u8 lbl_800E8754[];
extern Vec lbl_80367318;
extern void fn_80023B90(void*, Vec*);
extern u8 lbl_800F7478[];
extern u8 lbl_3_data_177F8[];
extern s32 lbl_3_data_177F4;
extern u8 lbl_803C5090[];
extern u8 lbl_8036E548[];
extern void fn_800BEBCC(int, Vec*);
extern const f32 lbl_3_rodata_20F0;
extern void CTRLGetTranslation(void*, f32*, f32*, f32*);
extern void fn_3_CB7E8(f32, f32, f32);
extern f32 lbl_3_rodata_2150;

void fn_3_C1964(void) {
    lbl_3_bss_9D9C = 1;
}

void fn_3_C1974(u8* a) {
    u8* p = fn_800B0A5C_insertQueue(fn_3_C2644, 4);
    *(s16*)(p + 0x10) = 0;
    lbl_3_bss_9D98 = a + 0x3C4;
    lbl_3_bss_9D9C = 0;
}

// .text:0x000C19C8 size:0x250 mapped:0x80700A5C
// ~19 diff lines: orig keeps (shifted + 0x1FFF) in r27 before the 2nd rand(), and indexes the u16 store as sthx (r29+0x20, not folded into the induction var)
extern void fn_3_B7FC8(s32, s32);
extern s16 lbl_3_data_17880[];
void fn_3_C19C8(void) {
    s32 i;
    s32 a;
    s32 r;
    s32 t;
    u8* o;
    if (lbl_3_bss_9D90 == 0) {
        lbl_3_bss_9D90 = (u32)fn_800B0A5C_insertQueue(fn_3_C2244, 5);
    }
    if (*(s16*)(lbl_803CC1B8 + 0x10) != 0x136) {
        fn_3_B7FC8(lbl_3_data_81DC[g_d_GameSettings.StadiumID] + 6, 8);
    }
    *(u8*)(lbl_3_bss_9D90 + 0x2A) = 0xFF;
    *(u8*)(lbl_3_bss_9D90 + 0x29) = 2;
    r = rand() % 3;
    *(f32*)(lbl_3_bss_9D90 + 0x14) = lbl_3_data_17880[r * 3];
    *(f32*)(lbl_3_bss_9D90 + 0x18) = lbl_3_data_17880[r * 3 + 1];
    *(f32*)(lbl_3_bss_9D90 + 0x1C) = lbl_3_data_17880[r * 3 + 2];
    *(u8*)(lbl_3_bss_9D90 + 0x24) = 10 - rand() % 20;
    i = 2;
    while (i-- != 0) {
        a = (0x1FFF - rand() * 0x3FFF / 0x7FFF) >> (1 - i);
        a += 0x1FFF;
        t = rand() * a / 0x7FFF;
        o = (u8*)lbl_3_bss_9D90;
        *(u16*)&o[i * 2 + 0x20] = t;
        o = (u8*)lbl_3_bss_9D90;
        o[0x25 + i] = o[0x24] + 2 - rand() % 2;
        t = rand() % 2 + 1;
        o = (u8*)lbl_3_bss_9D90;
        o[0x27 + i] = t;
    }
}

// .text:0x000C1C18 size:0x62C mapped:0x80700CAC
void fn_3_C1C18(void) {
    return;
}

// .text:0x000C2244 size:0xCC mapped:0x807012D8
void fn_3_C2244(void) {
    u8* p = lbl_803CC1B8;
    if (*(s32*)&lbl_3_bss_9D9C != 0) {
        lbl_3_bss_9D90 = 0;
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (p[0x2A] != 0) {
        fn_800A7D4C(1, &lbl_3_data_17804[lbl_803CBBC0[0]]);
        PSMTXCopy((MtxPtr)((u8*)fn_80052768_getCamera(0) + 0x40), lbl_3_data_17804[lbl_803CBBC0[0]].m);
        lbl_3_data_17804[lbl_803CBBC0[0]].w38 = p;
    }
}

// .text:0x000C2310 size:0xD0 mapped:0x807013A4
void fn_3_C2310(void* pp, void* cam) {
    Mtx m2;
    Mtx m;
    DspObj2* o;
    DspObj2* n;
    ((void (*)(u32, void*))CTRLBuildMatrix)(lbl_3_bss_9D94, m);
    PSMTXConcat((f32 (*)[4])cam, m, m2);
    o = *(DspObj2**)pp;
    n = o->child;
    if (o->w14 != 0) {
        if (o->w7C != 0) {
            fn_8003A8A0(o->w14, m2, 1);
        } else {
            DOVARenderSkin(o->w14, m2, o->w64, o->w68, 0, 0);
        }
    }
    while (n != 0) {
        if (n->w14 != 0) {
            DOSetWorldMatrix(n->w14, n->wEC);
            fn_8003A8A0(n->w14, m2, 0);
        }
        n = n->next;
    }
}

// .text:0x000C23E0 size:0xC0 mapped:0x80701474
void fn_3_C23E0(void) {
    u8* c;
    int i;
    u8** base;
    fn_800BF058(fn_3_B8184);
    base = lbl_3_common_bss_350E4;
    for (i = 0; i < *(int*)((u8*)base + 0x30); i++) {
        c = *base + i * 0xE8;
        fn_3_B828C(c);
        if (i >= 1 && i < 11) {
            if ((c[0x90] >> 7) & 1) {
                if (*(u8**)(c + 0x74) != 0) {
                    (*(u8**)*(u8**)(c + 0x74))[0x98] = c[0x93] | 6;
                    fn_800BDF70(*(u8**)(c + 0x74));
                }
            }
        }
    }
}

// .text:0x000C24A0 size:0x1A4 mapped:0x80701534
void fn_3_C24A0(void) {
    Vec n;
    Vec d;
    u8 a;
    u8* q;
    *(s16*)(lbl_803CC1B8 + 0x10) -= 1;
    if (*(s16*)(lbl_803CC1B8 + 0x10) == 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        fn_80023B90(lbl_800F7478 + g_d_GameSettings._54 * 0x2C, &lbl_80367318);
        q = *(u8**)(lbl_8036E548 + 4);
        if (q != NULL) {
            *(u16*)(q + *(u32*)(q + 0x14) + 0x60) = 2;
        }
    } else {
        s16 t = *(s16*)(lbl_803CC1B8 + 0x10);
        if (t < 12) {
            a = (t << 7) / 12;
        } else {
            a = 0x80;
        }
        fn_80023B90(lbl_3_data_177F8, &lbl_80367318);
        q = *(u8**)(lbl_8036E548 + 4);
        if (q != NULL) {
            *(u16*)(q + *(u32*)(q + 0x14) + 0x60) = 3;
        }
        lbl_803C5090[0x1D] = 0xB;
        *(f32*)lbl_803C5090 = lbl_3_rodata_20F0;
        *(u16*)(lbl_803C5090 + 0x14) = 0x1C0;
        lbl_803C5090[0x17] = a;
        lbl_803C5090[0x19] = lbl_3_data_177F4;
        lbl_803C5090[0x18] = 1;
    }
    n.x = -lbl_80367318.x;
    n.y = -lbl_80367318.y;
    n.z = -lbl_80367318.z;
    PSVECNormalize(&n, &n);
    d = n;
    fn_800BEBCC(0, &d);
}

// .text:0x000C2644 size:0x330 mapped:0x807016D8
void fn_3_C2644(void) {
    return;
}

// .text:0x000C2974 size:0x18 mapped:0x80701A08
extern u8 lbl_3_bss_9DE7;
extern u8 lbl_3_bss_9D82;

void fn_3_C2974(void) {
    lbl_3_bss_9DE7 = 1;
    lbl_3_bss_9D82 = 1;
}

// .text:0x000C298C size:0x114 mapped:0x80701A20
void fn_3_C298C(void) {
    u8* e = lbl_803CC1B8;
    u32 i;
    if (g_d_GameSettings.GameModeSelected == 7) {
        if (g_GameLogic[0x11E] == 0xB || g_GameLogic[0x11E] >= 0x22) {
            if (g_Minigame[0x1A40] != 0 && g_Minigame[0x1A38] == 0) {
                ((void (*)(void))fn_800B0A14_removeQueue)();
            }
        }
    } else if (g_GameLogic[0x128] != 0 || g_d_GameSettings.__0x20padding[1] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
    i = 0;
    do {
        u8* o = *(u8**)(e + 0x14);
        if (o == NULL || *(u32*)(o + 8) == 0) {
            u32 r = fn_80033A24(fn_3_C30F0, 0x80, 0, 0x15, 1, 0);
            *(u32*)(e + 0x14) = r;
            r = *(u32*)(e + 0x14);
            if (r != 0) {
                fn_3_C366C(r, i);
            }
        }
        i++;
        e += 4;
    } while (i < 6);
}

// 48-line diff, all f-reg numbering (orig: w=f29 lo=f30 h/hi=f31; ours w=f30 h=f29 lo=f31)
// .text:0x000C2AA0 size:0x1E0 mapped:0x80701B34
u8 fn_3_C2AA0(Vec* pos, f32 w, f32 h) {
    Vec out;
    f32 hw;
    f32 hh;
    Vec v[4];
    u8* m;
    u32 i;
    u32 t;
    f32 z;
    f32 x;
    f32 y;
    u8 acc;
    u8 f;
    acc = 0;
    fn_8005268C();
    m = fn_80052734();
    PSMTXMultVec((f32(*)[4])(m + 0x40), pos, pos);
    z = pos->z;
    if (z > lbl_3_rodata_20F4 || z < lbl_3_rodata_20F8) {
        return 0;
    }
    x = pos->x;
    y = pos->y;
    hw = w * lbl_3_rodata_20D4;
    hh = h * lbl_3_rodata_20D4;
    v[0].z = v[1].z = v[2].z = v[3].z = z;
    v[0].x = v[3].x = x - hw;
    v[1].x = v[2].x = x + hw;
    v[0].y = v[1].y = y - hh;
    v[2].y = v[3].y = y + hh;
    for (i = 0; i < 4; i++) {
        PSMTX44MultVec((f32(*)[4])m, &v[i], &out);
        f = (out.x < lbl_3_rodata_20F4);
        f |= (out.x > lbl_3_rodata_20F0) << 1;
        f |= (out.y < lbl_3_rodata_20F4) << 2;
        f |= (out.y > lbl_3_rodata_20F0) << 3;
        if (f == 0) {
            return 1;
        }
        acc &= f;
    }
    t = acc & 3;
    if (t == 1 || t == 2) {
        return 0;
    }
    t = acc & 0xC;
    if (t == 4 || t == 8) {
        return 0;
    }
    return 1;
}

// .text:0x000C2C80 size:0x25C mapped:0x80701D14
void fn_3_C2C80(void* pv, u8* h) {
    C4724P* p = pv;
    f32 a;
    s16 t;
    a = lbl_3_rodata_20FC * (f32)(rand() % 360);
    p->vx = lbl_3_rodata_2100 * (f32)cos(a);
    p->vz = lbl_3_rodata_2100 * (f32)sin(a);
    p->vy = lbl_3_rodata_2108;
    p->f1C = lbl_3_rodata_20D4;
    p->f1C = p->f1C + (f64)((u32)rand() % 2500) / lbl_3_rodata_2110;
    p->f38 = p->f1C;
    p->f3C = lbl_3_rodata_2118 * p->f1C;
    p->f20 = (f64)(rand() % 101) / lbl_3_rodata_2120;
    t = rand() % 24 + 0x48;
    p->s4A = t;
    p->f4F = t;
    p->x = *(f32*)(h + 0x18);
    p->y = *(f32*)(h + 0x1C);
    p->z = *(f32*)(h + 0x20);
    p->a40 = lbl_3_rodata_2028[0];
    p->a41 = lbl_3_rodata_2028[1];
    p->a42 = lbl_3_rodata_2028[2];
    p->f24 = lbl_3_rodata_2128;
    p->a43 = lbl_3_rodata_2128;
    p->s4A = p->f4F;
    p->s48 = 0;
}

// 60-line diff: orig hoists the 2118/2138/213C const loads up into the first fmadd; ours loads them later (f-reg numbering shifts)
// .text:0x000C2EDC size:0x214 mapped:0x80701F70
void fn_3_C2EDC(void* pv) {
    C4724P* p = pv;
    p->f38 = p->f20 * (lbl_3_rodata_2130 * p->f1C / p->f4F) + p->f38;
    p->f3C = p->f20 * (lbl_3_rodata_2118 * p->f1C / p->f4F) + p->f3C;
    p->f24 = p->f24 + (lbl_3_rodata_2138 / p->f4F);
    if (p->f24 < lbl_3_rodata_213C) {
        p->f24 = lbl_3_rodata_213C;
    }
    p->a43 = p->f24;
    p->a40 = lbl_3_rodata_2028[0] * (p->a43 / lbl_3_rodata_2140);
    p->a41 = lbl_3_rodata_2028[1] * (p->a43 / lbl_3_rodata_2140);
    p->a42 = lbl_3_rodata_2028[2] * (p->a43 / lbl_3_rodata_2140);
    p->x += p->vx;
    p->y -= p->vy;
    p->z += p->vz;
    p->s4A -= 1;
}

// .text:0x000C30F0 size:0x57C mapped:0x80702184
void fn_3_C30F0(void) {
    return;
}

// .text:0x000C366C size:0x35C mapped:0x80702700
#pragma dont_inline on
void fn_3_C366C(u32 a, u8 b) {
    return;
}
#pragma dont_inline reset

// .text:0x000C39C8 size:0x70 mapped:0x80702A5C
void fn_3_C39C8(void) {
    u32 i = 0;
    do {
        u32 r = fn_80033A24(fn_3_C30F0, 0x80, 0, 0x15, 1, 0);
        if (r != 0) {
            fn_3_C366C(r, i);
        }
        i++;
    } while (i < 6);
}

// .text:0x000C3A38 size:0x1F4 mapped:0x80702ACC
void fn_3_C3A38(u8* obj) {
    Vec v;
    Mtx m;
    if (g_GameLogic[0x11E] != 2 || obj == NULL) {
        lbl_3_bss_9D8C = 0;
        lbl_3_bss_9D81 = 0;
        fn_800528B4();
        return;
    }
    if (lbl_3_bss_9D81 != 0) {
        lbl_3_bss_9D8C = 0x3C;
        lbl_3_bss_9D81 = 0;
    }
    if (lbl_3_bss_9D8C != 0) {
        v.x = (f32)(rand() % 20 - 10) / lbl_3_rodata_214C;
        v.y = (f32)(rand() % 20 - 10) / lbl_3_rodata_214C;
        v.z = lbl_3_rodata_213C;
        PSMTXInverse((MtxPtr)((u8*)fn_80052768_getCamera(0) + 0x40), m);
        PSMTXMultVecSR(m, &v, &v);
        *(f32*)(obj + 0x70) += v.x;
        *(f32*)(obj + 0x74) += v.y;
        *(f32*)(obj + 0x78) += v.z;
        *(f32*)(obj + 0x7C) += v.x;
        *(f32*)(obj + 0x80) += v.y;
        *(f32*)(obj + 0x84) += v.z;
        lbl_3_bss_9D8C -= 1;
    }
}

// .text:0x000C3C2C size:0x268 mapped:0x80702CC0
typedef struct {
    u8 pad0[0x67];
    u8 f67;
    Vec pos[8];
    u8 state[8];
    u8* fD0;
} C3C2CBss;
extern C3C2CBss lbl_3_bss_9D80;
#define C3C2C_SLOT(o, i) (((u8**)lbl_80371C30)[(*(u16*)((o) + 0x14) + (i)) * 2])
void fn_3_C3C2C(void) {
    C3C2CBss* g = &lbl_3_bss_9D80;
    u8* st = g->state;
    Vec* pv = g->pos;
    u8* e = lbl_803CC1B8;
    s32 i;
    for (i = 0; i < 8; i++, st++, pv++) {
        switch (*st) {
        case 1: {
            s16 y1, x1;
            fn_800528C0(pv->x, pv->y, pv->z, &x1, &y1);
            *(f32*)(C3C2C_SLOT(g->fD0, i) + 0x48) = x1;
            *(f32*)(C3C2C_SLOT(g->fD0, i) + 0x4C) = y1;
            *(f32*)(C3C2C_SLOT(g->fD0, i) + 0x50) = 0.0f;
            *(u32*)(C3C2C_SLOT(e, i) + 0x5C) = 0;
            *(u32*)(C3C2C_SLOT(e, i) + 0x54) |= 2;
            *st = 2;
            break;
        }
        case 2: {
            s16 y2, x2;
            fn_800528C0(pv->x, pv->y, pv->z, &x2, &y2);
            *(f32*)(C3C2C_SLOT(g->fD0, i) + 0x48) = x2;
            *(f32*)(C3C2C_SLOT(g->fD0, i) + 0x4C) = y2;
            *(f32*)(C3C2C_SLOT(g->fD0, i) + 0x50) = 0.0f;
            if ((C3C2C_SLOT(e, i)[0x69] == 2) ? 1 : 0) {
                *(u32*)(C3C2C_SLOT(e, i) + 0x54) &= ~2;
                *st = 0;
            }
            break;
        }
        }
    }
    if (g->f67 != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        fn_80034CEC(g->fD0);
        g->f67 = 0;
    }
}

// .text:0x000C3E94 size:0xDC mapped:0x80702F28
void fn_3_C3E94(f32* pos, s32 idx) {
    s16 x;
    s16 y;
    fn_800528C0(pos[0], pos[1], pos[2], &x, &y);
    *(f32*)(((u8**)lbl_80371C30)[(*(u16*)(lbl_3_bss_9E50[0] + 0x14) + idx) * 2] + 0x48) = x;
    *(f32*)(((u8**)lbl_80371C30)[(*(u16*)(lbl_3_bss_9E50[0] + 0x14) + idx) * 2] + 0x4C) = y;
    *(f32*)(((u8**)lbl_80371C30)[(*(u16*)(lbl_3_bss_9E50[0] + 0x14) + idx) * 2] + 0x50) = 0.0f;
}

// .text:0x000C3F70 size:0xF8 mapped:0x80703004
void fn_3_C3F70(u8* a) {
    u8* t = **(u8***)(a + 0x74);
    u8* q;
    u32 i;
    u32 j;
    u8* e;
    if (lbl_3_bss_9D88++ > 4) {
        if (++lbl_3_data_177F0 > 0x13) {
            lbl_3_data_177F0 = 4;
        }
        lbl_3_bss_9D88 = 0;
    }
    if (lbl_3_bss_9D88 != 0) {
        return;
    }
    for (i = 0; i < *(u16*)(t + 6); i++) {
        e = ((u8**)*(u8**)(t + 0x18))[i];
        e = *(u8**)(e + 0x14);
        if (e != NULL) {
            q = *(u8**)(*(u8**)(e + 0x10) + 4);
            for (j = 0; j < *(u16*)(*(u8**)(e + 0x10) + 8); j++) {
                if (q[0] == 1) {
                    *(u32*)(q + 4) = *(u32*)(q + 4) & ~0x1FFF;
                    *(u32*)(q + 4) = *(u32*)(q + 4) | lbl_3_data_177F0;
                }
                q += 0x10;
            }
        }
    }
}

// .text:0x000C4068 size:0x84 mapped:0x807030FC
void fn_3_C4068(u8* a) {
    u8* p = **(u8***)(a + 0x74);
    u32 n;
    u32 v;
    u16 t;
    p = *(u8**)(p + 0x18);
    p = *(u8**)(p + 4);
    p = *(u8**)(p + 0x14);
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 4);
    n = lbl_3_bss_9D84;
    t = *(u32*)(p + 4) & 0x1FFF;
    lbl_3_bss_9D84 = n + 1;
    v = t;
    if (n > 4) {
        v = t + 1;
        if ((u16)v > 0x13) {
            v = 4;
        }
        lbl_3_bss_9D84 = 0;
    }
    *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
    *(u32*)(p + 4) = *(u32*)(p + 4) | (u16)v;
}

// .text:0x000C40EC size:0x60 mapped:0x80703180
void fn_3_C40EC(u8* a) {
    u8* p = **(u8***)(a + 0x74);
    p = *(u8**)(p + 0x18);
    p = *(u8**)(p + 4);
    p = *(u8**)(p + 0x14);
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 4);
    if (a[0xA9] != 6) {
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        *(u32*)(p + 4) = *(u32*)(p + 4) | 0x19;
    } else {
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        *(u32*)(p + 4) = *(u32*)(p + 4) | 0x1A;
    }
}

// .text:0x000C414C size:0x158 mapped:0x807031E0
void fn_3_C414C(int idx) {
    u8 hit = 0;
    Vec t;
    u8* c = *(u8**)&lbl_3_common_bss_350E4 + idx * 0xE8;
    CTRLGetTranslation(c, &t.x, &t.y, &t.z);
    if (*(s16*)(g_Ball + 0x1B7A) != 2) {
        if (c[0xA9] == 5 && lbl_800E8754[4] != 0) {
            fn_3_CB7E8(t.x, t.y - lbl_3_rodata_2150, t.z);
            hit = 1;
            c[0xA9] = 6;
        } else if (c[0xA9] == 4 && lbl_800E8754[4] != 0) {
            fn_3_CB7E8(t.x, t.y, t.z - lbl_3_rodata_2150);
            hit = 1;
            c[0xA9] = 6;
        }
    }
    if (hit) {
        int i = g_Ball[0x1BE5] ? 7 : 6;
        lbl_3_bss_9E48[i] = 1;
        lbl_3_bss_9DE8[i].x = ((Vec*)g_Ball)->x;
        lbl_3_bss_9DE8[i].y = -((Vec*)g_Ball)->y;
        lbl_3_bss_9DE8[i].z = ((Vec*)g_Ball)->z;
    }
}

// .text:0x000C42A4 size:0x1A8 mapped:0x80703338
typedef struct { u8 pad[0x78]; u32 f78; u8 pad2[0xE8 - 0x7C]; } C42A4Ctl;
typedef struct { C42A4Ctl* arr; u8 pad0[0x3C - 4]; u32* p3C; u16* p40; u32* p44; u8* p48; } C42A4Bss;
typedef struct { u8 pad[0x10]; u8 f10; u8 f11; u8 f12; u8 f13; } C42A4Ent;
extern u8 lbl_3_bss_9DE0[];
extern u8 lbl_3_data_17704[];
extern f32 lbl_3_rodata_2154;
extern void fn_3_B8414(void*, void*);
extern void fn_3_B8464(void*, void*);
extern void fn_3_B8574(void);
void fn_3_C42A4(s32* a, s32* b) {
    Mtx m;
    C42A4Bss* g;
    C42A4Ent* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    C42A4Ctl* c;
    s32 idx;
    g = (C42A4Bss*)lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = (C42A4Ent*)lbl_3_data_17704;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->f10 != 7) {
                if ((((u8*)((C42A4Bss*)lbl_3_common_bss_350E4)->arr)[(j + lbl_3_bss_9DE0[0]) * 0xE8 + 0x90] >> 6) & 1) {
                    idx = j + lbl_3_bss_9DE0[0];
                    *(s32*)((u8*)g->p44 + off) = idx;
                    off += 4;
                    g->p3C[*a] += 1;
                    c = &((C42A4Bss*)lbl_3_common_bss_350E4)->arr[j + lbl_3_bss_9DE0[0]];
                    ((void (*)(void*, void*))CTRLBuildMatrix)(c, m);
                    fn_3_B8464(m, (void*)c->f78);
                    m[1][3] = m[1][3] * lbl_3_rodata_2154;
                    fn_3_B8464(m, (void*)c->f78);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C444C size:0x2D8 mapped:0x807034E0
void fn_3_C444C(void* hv, u8* b) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    f32 px = *(f32*)(b + 0x9C);
    f32 py = *(f32*)(b + 0xA0);
    f32 pz = *(f32*)(b + 0xA4);
    u32 i = 0;
    f32 a;
    f32 c;
    f32 k;
    while (p != NULL) {
        p->x = px;
        p->y = py;
        p->z = pz;
        a = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
        c = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
        k = lbl_3_rodata_20D4 - (f32)(rand() % 3) / lbl_3_rodata_2160[0];
        p->vx = k * cos(a) * cos(c);
        p->vy = -k * sin(a);
        p->vz = k * sin(a) * cos(c);
        p->f38 = p->f3C = lbl_3_rodata_2164;
        p->s48 = i / 6;
        i++;
        p->f4D = 0x1B;
        p->f4E = 0;
        p->a43 = 0xFF;
        p->a42 = 0xFF;
        p->a41 = 0xFF;
        p->a40 = 0xFF;
        p->s4A = 1;
        p = p->next;
    }
}

extern u8 lbl_80366158[];
extern void fn_80033620(void);
extern void fn_8003403C(f32, f32);
extern void fn_80033CC8(void*, s32);
extern void GXSetZMode(int, int, int);
extern void GXSetBlendMode(int, int, int, int);
extern const f32 lbl_3_rodata_2168[];
extern const f32 lbl_3_rodata_21A4;
extern const f32 lbl_3_rodata_21AC;
extern s32 lbl_3_bss_9F0C;
extern u8 lbl_3_data_17514[];
extern const f32 lbl_3_rodata_21A8;
extern f64 pow(f64, f64);
// 97%: only f-reg numbering of hoisted consts (213C should be f1, loaded after first fadds); const externs help
// .text:0x000C4724 size:0x1AC mapped:0x807037B8
u32 fn_3_C4724(void* hv) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    u32 n = 0;
    f32 k;
    f32 c;
    fn_80033620();
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    do {
        if (p->s48 != 0) {
            p->s48 -= (lbl_80366158[0x28] == 0);
        } else if (p->s4A != 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->f10);
            if (lbl_80366158[0x28] == 0) {
                k = lbl_3_rodata_2168[0];
                c = lbl_3_rodata_213C;
                p->x += p->vx;
                p->y += p->vy;
                p->z += p->vz;
                p->f38 -= k;
                p->f3C -= k;
                p->a43 -= 0xF;
                if (p->f38 <= c || p->f3C <= c) {
                    p->s4A = 0;
                }
            }
            n++;
        }
        p = p->next;
    } while (p != NULL && n < (h->f14 & 0xFFF));
    h->f24 -= (lbl_80366158[0x28] == 0);
    if (h->f24 == 0) {
        return 1;
    }
    return 0;
}

// 99%: only the x/y load order of the src->pos copy (we load y before x)
// .text:0x000C48D0 size:0x2B0 mapped:0x80703964
void fn_3_C48D0(void* hv, Vec* src) {
    C4724Hdr* h;
    C4724P* p;
    u32 i;
    f32 a;
    f32 c;
    f32 k;
    f32 x;
    f32 y;
    f32 z;
    h = hv;
    p = h->head;
    i = 0;
    while (p != NULL) {
        x = ((volatile f32*)src)[0];
        y = ((volatile f32*)src)[1];
        p->x = x;
        z = ((volatile f32*)src)[2];
        p->y = y;
        p->z = z;
        a = lbl_3_rodata_2158 * (f32)(rand() % 181) / lbl_3_rodata_215C;
        c = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
        k = lbl_3_rodata_20D4 - (f32)(rand() % 3) / lbl_3_rodata_2160[0];
        p->vx = k * cos(a) * cos(c);
        p->vy = -k * sin(a);
        p->vz = k * sin(a) * cos(c);
        p->f38 = p->f3C = lbl_3_rodata_2164;
        p->s48 = i / 6;
        i++;
        p->f4D = 0x1B;
        p->f4E = 0;
        p->a43 = 0xFF;
        p->a42 = 0xFF;
        p->a41 = 0xFF;
        p->a40 = 0xFF;
        p->s4A = 1;
        p = p->next;
    }
}

// .text:0x000C4B80 size:0x174 mapped:0x80703C14
void fn_3_C4B80(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    fn_8005268C();
    GXSetProjection(fn_80052734(), 0);
    fn_8005268C();
    GXLoadPosMtxImm(fn_80052734() + 0x40, 0);
    GXSetCurrentMtx(0);
}

// .text:0x000C4CF4 size:0x20C mapped:0x80703D88
void fn_3_C4CF4(void* hv, u8 type) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    fn_8005268C();
    GXSetProjection(fn_80052734(), 0);
    fn_8005268C();
    GXLoadPosMtxImm(fn_80052734() + 0x40, 0);
    GXSetCurrentMtx(0);
    while (p != NULL) {
        if (p->s48 <= 0 && p->s4A > 0 && type == p->f50) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->f10);
        }
        p = p->next;
    }
}

extern int rand(void);
extern const f32 lbl_3_rodata_2160[];
extern const f32 lbl_3_rodata_216C;
extern f64 sin(f64);
extern f64 cos(f64);
extern const f32 lbl_3_rodata_2158;
extern const f32 lbl_3_rodata_215C;
extern const f32 lbl_3_rodata_2170[];
extern const f32 lbl_3_rodata_2174;
typedef struct { u8 pad0[0x20]; void* f20; } C4F00H;
#define C4F00_SPAWN() \
    do { \
        r = (f32)(15 - rand() % 31) / lbl_3_rodata_2160[0]; \
        a = lbl_3_rodata_2158 * (f32)(rand() % 361) / lbl_3_rodata_215C; \
        t.x = r * cos(a); \
        t.z = r * sin(a); \
        t.y = lbl_3_rodata_216C; \
        ((void (*)(void*, void*))CTRLBuildMatrix)(*(void**)((u8*)h + 0x20), m); \
        PSMTXMultVec(m, &t, (Vec*)&p->x); \
    } while (0)
// .text:0x000C4F00 size:0x404 mapped:0x80703F94
s32 fn_3_C4F00(void* hv) {
    C4724Hdr* h = hv;
    C4724P* p;
    Vec t;
    Mtx m;
    f32 a;
    f32 k;
    f32 c;
    f32 r;
    fn_80033620();
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    p = h->head;
    do {
        if (p->s48 != 0) {
            p->s48 -= (lbl_80366158[0x28] == 0);
            if (p->s48 == 0) {
                C4F00_SPAWN();
            }
        } else if (p->s4A != 0 && lbl_80366158[0x28] == 0) {
            if (p->f4F == 0) {
                p->a43 += 0xF;
                k = lbl_3_rodata_2170[0];
                p->f38 += k;
                p->f3C += k;
                if (p->f38 >= lbl_3_rodata_2174 || p->f3C >= lbl_3_rodata_2174) {
                    p->f4F = 1;
                }
            } else {
                p->a43 -= 0xF;
                k = lbl_3_rodata_2170[0];
                p->f38 -= k;
                p->f3C -= k;
                if (p->f38 <= lbl_3_rodata_213C || p->f3C <= lbl_3_rodata_213C) {
                    p->s4A = 0;
                }
            }
        }
        if (p->s4A == 0) {
            p->f38 = p->f3C = lbl_3_rodata_213C;
            p->s4A = 1;
            p->f4F = 0;
            p->s48 = 0;
            C4F00_SPAWN();
            p->a43 = 0;
        }
        p = p->next;
    } while (p != NULL);
    return 0;
}

// .text:0x000C5304 size:0x1CC mapped:0x80704398
void fn_3_C5304(void* hv, u8* b) {
    C4724Hdr* h = hv;
    C4724P* p = h->head;
    s16 i = 0;
    h->f18 = (Vec*)(b + 0x9C);
    h->f20 = b;
    while (p != NULL) {
        p->f38 = p->f3C = lbl_3_rodata_213C;
        p->s48 = i;
        i += 4;
        p->f4D = 0x15;
        p->f4E = 0;
        p->a42 = 0xFF;
        p->a41 = 0xFF;
        p->a40 = 0xFF;
        p->a43 = 0;
        p->s4A = 1;
        p->f4F = 0;
        if (p->s48 == 0) {
            p->x = h->f18->x + (f32)(15 - rand() % 31) / lbl_3_rodata_2160[0];
            p->y = lbl_3_rodata_216C + h->f18->y;
            p->z = h->f18->z + (f32)(15 - rand() % 31) / lbl_3_rodata_2160[0];
        } else {
            p->x = p->y = p->z = lbl_3_rodata_213C;
        }
        p = p->next;
    }
}

// .text:0x000C54D0 size:0x218 mapped:0x80704564
void fn_3_C54D0(u8* a) {
    C4724Hdr* h = fn_800339F0(0, (u8)(a[0xA8] + 0x2A));
    C4724P* p;
    if (h == NULL) {
        return;
    }
    p = h->head;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    fn_8005268C();
    GXSetProjection(fn_80052734(), 0);
    fn_8005268C();
    GXLoadPosMtxImm(fn_80052734() + 0x40, 0);
    GXSetCurrentMtx(0);
    while (p != NULL) {
        if (p->s48 <= 0 && p->s4A > 0 && p->f50 == 1) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->f10);
        }
        p = p->next;
    }
}

// .text:0x000C56E8 size:0x294 mapped:0x8070477C
void fn_3_C56E8(u8* a) {
    Vec v1;
    Vec v2;
    C4724Hdr* h;
    C4724P* p;
    fn_8005268C();
    PSMTXMultVec((MtxPtr)(fn_80052734() + 0x40), (Vec*)(a + 0x9C), &v1);
    h = fn_800339F0(0, (u8)(a[0xA8] + 0x2A));
    if (h == NULL) {
        return;
    }
    for (p = h->head; p != NULL; p = p->next) {
        fn_8005268C();
        PSMTXMultVec((MtxPtr)(fn_80052734() + 0x40), (Vec*)&p->x, &v2);
        if (v1.z >= v2.z) {
            p->f50 = 0;
        } else {
            p->f50 = 1;
        }
    }
    p = h->head;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxDesc(0xD, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetVtxAttrFmt(0, 0xD, 1, 4, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(0);
    GXSetTevColorIn(0, 0xF, 0xA, 8, 0xF);
    GXSetTevAlphaIn(0, 7, 5, 4, 7);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    fn_8005268C();
    GXSetProjection(fn_80052734(), 0);
    fn_8005268C();
    GXLoadPosMtxImm(fn_80052734() + 0x40, 0);
    GXSetCurrentMtx(0);
    while (p != NULL) {
        if (p->s48 <= 0 && p->s4A > 0 && p->f50 == 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->f10);
        }
        p = p->next;
    }
}

// .text:0x000C597C size:0x364 mapped:0x80704A10
typedef struct {
    u8 pad0[0x90];
    u8 b90_7 : 1;
    u8 b90_rest : 7;
    u8 pad91[0x9C - 0x91];
    f32 px, py, pz;
    u8 fA8;
    u8 padA9[0xBD - 0xA9];
    u8 fBD;
} C597CEnt;
void fn_3_C597C(s32 idx) {
    f32 k;
    u32 i;
    f32 px;
    C4724Hdr* h;
    f32 py;
    C4724P* p;
    f32 pz;
    f32 a;
    f32 c;
    C597CEnt* e;
    e = (C597CEnt*)(*(u8**)&lbl_3_common_bss_350E4 + idx * 0xE8);
    pitchingMachinePitching((u8)(e->fA8 + 0x2A));
    h = (C4724Hdr*)fn_80033A24(fn_3_C4724, 0x80, 0, 0x18, 1, (u8)(e->fA8 + 0x34));
    if (h != NULL) {
        p = h->head;
        px = e->px;
        py = e->py;
        pz = e->pz;
        i = 0;
        while (p != NULL) {
            p->x = px;
            p->y = py;
            p->z = pz;
            a = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
            c = lbl_3_rodata_2158 * (f32)(rand() % 360) / lbl_3_rodata_215C;
            k = lbl_3_rodata_20D4 - (f32)(rand() % 3) / lbl_3_rodata_2160[0];
            p->vx = k * cos(a) * cos(c);
            p->vy = -k * sin(a);
            p->vz = k * sin(a) * cos(c);
            p->f38 = p->f3C = lbl_3_rodata_2164;
            p->s48 = i / 6;
            i++;
            p->f4D = 0x1B;
            p->f4E = 0;
            p->a43 = 0xFF;
            p->a42 = 0xFF;
            p->a41 = 0xFF;
            p->a40 = 0xFF;
            p->s4A = 1;
            p = p->next;
        }
        h->f10 = lbl_3_bss_9F0C;
        h->f24 = 0x1E;
    }
    e->fBD = 2;
    e->b90_7 = 0;
    e->py = lbl_3_rodata_2160[0];
}

// .text:0x000C5CE0 size:0xFC mapped:0x80704D74
u32 fn_3_C5CE0(u8* a) {
    Vec pos = lbl_3_rodata_2080;
    Vec d;
    u32 i;
    f32 lim;
    if (g_GameLogic[0x11E] == 2 && g_GameLogic[0x138] != 0) {
        return 0;
    }
    i = 0;
    lim = lbl_3_rodata_2178;
    do {
        memset(&pos, 0, 0xC);
        fn_8001B728(i, 4, &pos);
        PSVECSubtract(&pos, (Vec*)(a + 0x9C), &d);
        if (PSVECMag(&d) <= lim) {
            fn_3_25844(i, 1);
            return 1;
        }
        i++;
    } while (i < 9);
    return 0;
}

// .text:0x000C5DDC size:0x480 mapped:0x80704E70
void fn_3_C5DDC(void) {
    return;
}

// .text:0x000C625C size:0x174 mapped:0x807052F0
u32 fn_3_C625C(u8* a) {
    Vec pos = *(Vec*)(a + 0x9C);
    Vec d;
    u32 stad;
    u8 v;
    u32 h;
    if (g_Ball[0x1BC9] == 1) {
        return 0;
    }
    if ((g_Ball[0x1BE8] == 0xB) | (g_Ball[0x1BE8] == 0xC)) {
        return 0;
    }
    pos.y *= lbl_3_rodata_20F4;
    PSVECSubtract((Vec*)g_Ball, &pos, &d);
    if (PSVECMag(&d) <= lbl_3_rodata_2178) {
        stad = g_d_GameSettings.StadiumID;
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[4];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 4];
        }
        h = sndFXStartEx((u16)(lbl_3_data_81DC[stad] + 2), v, 0x3F, 0);
        if (g_d_GameSettings.GameModeSelected == 6) {
            v = lbl_3_data_84B8[5];
        } else {
            v = lbl_3_data_8404[stad * 0x1E + 5];
        }
        sndFXCtrl(h, 0x5B, v);
        return 1;
    }
    return 0;
}

// .text:0x000C63D0 size:0xDFC mapped:0x80705464
void fn_3_C63D0(void) {
    return;
}

// .text:0x000C71CC size:0x278 mapped:0x80706260
typedef struct { u8 d[0x44]; } C71CCCopy;
typedef struct { f32 x, y, z; u8 pad[4]; u8 f10; u8 pad11; u8 f12; u8 pad13[5]; } C71CCEnt;
extern C71CCEnt lbl_3_data_175FC[];
extern f32 lbl_3_data_175F0[];
extern const f64 lbl_3_rodata_2190;
extern const f32 lbl_3_rodata_2198;
extern const f32 lbl_3_rodata_219C;
extern const f32 lbl_3_rodata_21A0;
void fn_3_C71CC(s32* a, s32* b) {
    u32 v;
    C71CCEnt* e;
    f64 D;
    C42A4Bss* g;
    f32 y;
    s32 off;
    Mtx m;
    f32 d;
    C42A4Ctl* c;
    s32 k;
    s32 j;
    C71CCCopy t;
    g = (C42A4Bss*)lbl_3_common_bss_350E4;
    D = lbl_3_rodata_2190 * lbl_3_rodata_2198 + lbl_3_rodata_219C;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = lbl_3_data_175FC;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->f10 != 7) {
                if ((((u8*)((C42A4Bss*)lbl_3_common_bss_350E4)->arr)[(*b) * 0xE8 + 0x90] >> 6) & 1) {
                    *(s32*)((u8*)g->p44 + off) = *b;
                    g->p3C[*a] += 1;
                    c = &((C42A4Bss*)lbl_3_common_bss_350E4)->arr[*b];
                    off += 4;
                    t = *(C71CCCopy*)c;
                    ((void (*)(void*, void*))CTRLBuildMatrix)(c, m);
                    fn_3_B8464(m, (void*)c->f78);
                    y = (f32)D;
                    d = lbl_3_data_175F0[2] * lbl_3_rodata_21A0;
                    CTRLSetTranslation(&t, d + e->x, y + e->y, d + e->z);
                    ((void (*)(void*, void*))CTRLBuildMatrix)(&t, m);
                    fn_3_B8464(m, (void*)c->f78);
                    CTRLSetTranslation(&t, e->x - d, y + e->y, e->z - d);
                    ((void (*)(void*, void*))CTRLBuildMatrix)(&t, m);
                    fn_3_B8464(m, (void*)c->f78);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C7444 size:0x58 mapped:0x807064D8
void fn_3_C7444(u8* a) {
    u8* p = **(u8***)(a + 0x74);
    p = *(u8**)(p + 0x18);
    p = *(u8**)(p + 0x34);
    p = *(u8**)(p + 0x14);
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 4);
    switch (*(s8*)(a + 0xB0)) {
    case 0:
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        *(u32*)(p + 4) = *(u32*)(p + 4) | 2;
        break;
    default:
        *(u32*)(p + 4) = *(u32*)(p + 4) & ~0x1FFF;
        break;
    }
}

// .text:0x000C749C size:0x11C mapped:0x80706530
void fn_3_C749C(void) {
    s32 i;
    s32 stad;
    u8 v;
    u32 h;
    i = g_Ball[0x1BE5] ? 3 : 2;
    lbl_3_bss_9E48[i] = 1;
    lbl_3_bss_9DE8[i].x = ((Vec*)g_Ball)->x;
    lbl_3_bss_9DE8[i].y = -((Vec*)g_Ball)->y;
    lbl_3_bss_9DE8[i].z = ((Vec*)g_Ball)->z;
    stad = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[8];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 8];
    }
    h = sndFXStartEx((u16)(lbl_3_data_81DC[stad] + 4), v, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        v = lbl_3_data_84B8[9];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + 9];
    }
    sndFXCtrl(h, 0x5B, v);
}

// .text:0x000C75B8 size:0x1F4 mapped:0x8070664C
u32 fn_3_C75B8(void* hv) {
    C4724Hdr* h = hv;
    C4724P* p;
    s32 n = -h->f24;
    fn_80033620();
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    p = h->head;
    do {
        if (p->s48 != 0) {
            p->s48 -= (lbl_80366158[0x28] == 0);
        } else if (p->s4A != 0) {
            fn_8003403C(p->f38, p->f3C);
            fn_80033CC8(p, h->f10);
            if (lbl_80366158[0x28] == 0) {
                if (p->f38 < p->f1C) {
                    p->f38 += p->f1C / lbl_3_rodata_21A4;
                    p->f3C += p->f1C / lbl_3_rodata_21A4;
                }
                p->x += p->vx;
                p->z += p->vz;
                p->y = (p->vy + h->f18->y) - 5.0 * pow(2.0, (f64)n);
                if (30 - h->f24 >= 16) {
                    p->a43 = (f32)p->a43 - lbl_3_rodata_21A8;
                }
            }
        }
        p = p->next;
    } while (p != NULL);
    h->f24 -= (lbl_80366158[0x28] == 0);
    return !h->f24;
}

// 99%: only 'fmuls f0,f25,f0' operand order (we emit f0,f25); const-left source order changes the hoisted-const layout instead
// .text:0x000C77AC size:0x260 mapped:0x80706840
void fn_3_C77AC(void* hv, u8* b) {
    u32 ang;
    C4724P* p;
    C4724Hdr* h = hv;
    f32 a, fa;
    u32 i;
    p = h->head;
    h->f18 = (Vec*)(b + 0x9C);
    h->f20 = b;
    h->f10 = lbl_3_bss_9F0C;
    h->f24 = 30;
    i = 0;
    ang = 0;
    while (p != NULL) {
        p->f38 = p->f3C = lbl_3_rodata_213C;
        p->f1C = lbl_3_rodata_21AC - (f32)(rand() % 3);
        fa = (f32)ang + *(f32*)(lbl_3_data_17514 + b[0xA8] * 0x14 + 0xC);
        a = (fa * lbl_3_rodata_2158) / lbl_3_rodata_215C;
        p->vx = 0.3499999940395355 * cos(a);
        p->vy = (f32)-(rand() % 3);
        p->vz = 0.3499999940395355 * sin(a);
        ang += 30;
        p->x = h->f18->x;
        p->z = h->f18->z;
        p->s48 = i >> 2;
        i++;
        p->f4D = 0x1C;
        p->f4E = 0;
        p->a42 = 0x7F;
        p->a41 = 0x7F;
        p->a40 = 0x7F;
        p->a43 = 0x99;
        p->s4A = 1;
        p = p->next;
    }
}

// .text:0x000C7A0C size:0x650 mapped:0x80706AA0
void fn_3_C7A0C(void) {
    return;
}

typedef struct { u32 w[17]; } C42A4Cpy;
extern u8 lbl_3_bss_9DE4[];
extern u8 lbl_3_data_17514[];
extern f32 lbl_3_rodata_21E0;
extern void CTRLSetTranslation(void*, f32, f32, f32);
// .text:0x000C805C size:0x1E0 mapped:0x807070F0
void fn_3_C805C(s32* a, s32* b) {
    Mtx m;
    C42A4Cpy cpy;
    C42A4Bss* g;
    C42A4Ent* e;
    s32 off;
    s32 k;
    s32 j;
    u32 v;
    C42A4Ctl* c;
    s32 idx;
    g = (C42A4Bss*)lbl_3_common_bss_350E4;
    for (k = 0; k < 5; k++) {
        v = (u16)(g->p40[*a - 1] + g->p3C[*a - 1]);
        g->p40[*a] = v;
        ((void (*)(void))fn_3_B8574)();
        e = (C42A4Ent*)lbl_3_data_17514;
        off = v * 4;
        for (j = 0; j < 10; e++, j++) {
            if (k == e->f12 && e->f10 != 7) {
                if ((((u8*)((C42A4Bss*)lbl_3_common_bss_350E4)->arr)[(j + lbl_3_bss_9DE4[0]) * 0xE8 + 0x90] >> 6) & 1) {
                    idx = j + lbl_3_bss_9DE4[0];
                    *(s32*)((u8*)g->p44 + off) = idx;
                    g->p3C[*a] += 1;
                    c = &((C42A4Bss*)lbl_3_common_bss_350E4)->arr[j + lbl_3_bss_9DE4[0]];
                    off += 4;
                    cpy = *(C42A4Cpy*)c;
                    ((void (*)(void*, void*))CTRLBuildMatrix)(c, m);
                    fn_3_B8464(m, (void*)c->f78);
                    CTRLSetTranslation(&cpy, ((f32*)e)[0], lbl_3_rodata_21E0, ((f32*)e)[2]);
                    ((void (*)(void*, void*))CTRLBuildMatrix)(&cpy, m);
                    fn_3_B8464(m, (void*)c->f78);
                    *b += 1;
                }
            }
        }
        if (g->p3C[*a] != 0) {
            fn_3_B8414(g->p48 + *a * 0x18, g->p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000C823C size:0x78 mapped:0x807072D0
typedef struct { u8 _0[0x78]; s32 f78; u8 _7C[0xA9 - 0x7C]; u8 fA9; u8 _AA[0xE8 - 0xAA]; } C823CEnt;
s32 fn_3_C823C(s32 idx, f32* out) {
    C823CEnt* p = *(C823CEnt**)&lbl_3_common_bss_350E4 + idx;
    CTRLBuildMatrix(p);
    if (p->fA9 == 5) {
        out[7] = -0.002f;
    }
    return (*(C823CEnt**)&lbl_3_common_bss_350E4 + idx)->f78;
}

// .text:0x000C82B4 size:0x39C mapped:0x80707348
void fn_3_C82B4(void) {
    return;
}

// .text:0x000C8650 size:0xD2C mapped:0x807076E4
void fn_3_C8650(void) {
    return;
}

