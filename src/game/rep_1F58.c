#include "game/rep_1F58.h"
#include "header_rep_data.h"
#include "Dolphin/mtx.h"

extern u8 lbl_3_common_bss_35154[];
extern void* fn_800B0A5C_insertQueue(void*, s32);
// .bss (laid out last-defined-first)
u8 lbl_3_bss_9D40[0x40];
u8 lbl_3_bss_9D20[0x20];
extern u8* lbl_803CC1B8;
extern u8 lbl_8036E548[];
extern u8 lbl_803CBBC0;
typedef struct { void* next; void (*draw)(u8* a); f32 a, b, c; s32 x; } E18_1F58;
typedef struct { E18_1F58 e[2]; } E30_1F58;
extern u8 lbl_80366158[];
extern void fn_800A7D4C(int, void*);
extern void fn_800B0A14_removeQueue(void*);
extern f32 lbl_3_rodata_1FA8;
extern void fn_80027918(u8, f32);
extern f32 lbl_3_rodata_1FAC;
extern f32 lbl_3_rodata_1FC0;
extern f64 lbl_3_rodata_1FC8;
extern f32 lbl_3_rodata_1FD4;
extern const f32 lbl_3_rodata_1FD0;
extern f64 sin(f64);
typedef struct { s32 v; s32 w; } T8_1F58;
// Mirrors main/file_800263FC.h (that header clashes with this file's GX externs).
typedef struct ParticleParamsAttract {
    /* 0x00 */ void* tex;
    /* 0x04 */ s32 texIndex;
    /* 0x08 */ s32 count;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20[8];
} ParticleParamsAttract;
extern BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out); // main/file_80011640.h
extern void fn_80027674(Vec* center, Vec* target, ParticleParamsAttract* prm, u8 type, f32 radius);
void fn_3_C095C(u8* a);
// .data lbl_3_data_17248..17508: separate objects that the code reaches through one pooled base.
static u8 lbl_3_data_17248[4] = {80, 80, 0, 0};                         // aura alpha per slot
static f32 lbl_3_data_1724C[3] = {18.849556f, 18.849556f, 37.699112f};  // pulse speed per slot
static u8 lbl_3_data_17258[2][3] = {{255, 247, 136}, {255, 247, 136}};  // aura colour per slot
E32_1F58 lbl_3_data_17260[2] = {{-1}, {-1}};
static s32 lbl_3_data_172A0 = 250000; // particle radius, fixed point (/100000)
s32 lbl_3_data_172A4 = 150000;        // unused
s32 lbl_3_data_172A8 = 4;             // unused
static ParticleParamsAttract lbl_3_data_172AC = {NULL, 3, 30, 8000, 10, 20, 1, 15, {99000, 99800, -500, -899, 255, 20, 10, -1}};
// Per character: aura height (v) and size (w), fixed point (/100000).
static T8_1F58 lbl_3_data_172EC[0x36] = {
    {129999, 250000},
    {129999, 250000},
    {150000, 270000},
    {80000, 250000},
    {150000, 250000},
    {150000, 250000},
    {129999, 250000},
    {60000, 250000},
    {60000, 250000},
    {150000, 280000},
    {150000, 259999},
    {150000, 259999},
    {100000, 250000},
    {50000, 250000},
    {150000, 250000},
    {60000, 250000},
    {60000, 250000},
    {120000, 250000},
    {70000, 250000},
    {100000, 250000},
    {129999, 250000},
    {150000, 259999},
    {150000, 259999},
    {150000, 259999},
    {100000, 250000},
    {100000, 250000},
    {100000, 250000},
    {150000, 250000},
    {60000, 250000},
    {60000, 250000},
    {60000, 250000},
    {60000, 250000},
    {60000, 250000},
    {100000, 250000},
    {100000, 250000},
    {100000, 250000},
    {100000, 250000},
    {150000, 250000},
    {129999, 290000},
    {80000, 250000},
    {60000, 250000},
    {60000, 250000},
    {100000, 250000},
    {129999, 250000},
    {60000, 250000},
    {60000, 250000},
    {60000, 250000},
    {60000, 250000},
    {100000, 250000},
    {100000, 250000},
    {100000, 250000},
    {100000, 250000},
    {150000, 250000},
    {150000, 250000},
};
static f32 lbl_3_data_1749C = 95.0f;
static u8* lbl_3_data_174A0[2] = {NULL, NULL}; // the two tracking tasks
static E30_1F58 lbl_3_data_174A8[2] = {
    {{{NULL, fn_3_C095C}, {NULL, fn_3_C095C}}},
    {{{NULL, fn_3_C095C}, {NULL, fn_3_C095C}}},
};
extern s32 fn_8005268C(void);
extern u8* fn_80052734(s32);
extern s32 fn_80024DB0(void*);
extern void fn_80024FA4(void*, void*, void*, s32);
extern void fn_800B4CA0(void*, f32);
extern void fn_800B4C04(void*, f32);
extern void fn_800BDA24(void*);
extern void fn_800BDA94(void*, void*);
struct CharActor;
extern struct CharActor* fn_80011570(void); // main/file_8000F150.h
extern void* memset(void*, s32, u32);
extern void GXLoadTexObj(void*, s32);
extern void GXLoadTexMtxImm(void*, s32, s32);
extern void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
extern void GXSetTevOrder(s32, s32, s32, s32);
extern void GXSetTevColorIn(s32, s32, s32, s32, s32);
extern void GXSetTevColorOp(s32, s32, s32, s32, s32, s32);
extern void GXSetTevAlphaIn(s32, s32, s32, s32, s32);
extern void GXSetTevAlphaOp(s32, s32, s32, s32, s32, s32);
extern void* memcpy(void*, const void*, u32);
extern void DCStoreRange(void*, u32);
extern void GXInitTexObj(void* obj, void* img, u16 w, u16 h, int fmt, int ws, int wt, int mip);
extern void GXInitTexObjLOD(void* obj, int minF, int maxF, f32 minLOD, f32 maxLOD, f32 bias, int biasClamp, int edgeLOD, int maxAniso);

// .text:0x000C0854 size:0x108 mapped:0x806FF8E8
// 99.5%: only regalloc differs (original: k in r0, -1 in r5, sthx offset in r4; ours offset r0, -1 r4, k r5). ~290 variants tried (k type/order, store forms, ternary/else shapes).
void fn_3_C0854(void) {
    s32 i;
    s32 j;
    s16 v;
    s16* q;
    s32 k;
    u8* t;
    for (i = 0; i < 2; i++) {
        if (lbl_3_data_174A0[i] != NULL) {
            lbl_3_data_174A0[i][0x20] = 1;
        }
        v = lbl_3_data_17260[i].id;
        if (v >= 0) {
            j = 1;
            do {
                if (v == lbl_3_data_17260[j].id) {
                    break;
                }
            } while (j-- != 0);
            if (j >= 0) {
                t = ((u8**)lbl_8036E548)[v + 0x2C50 / 4];
                if (t != NULL) {
                    *(s32*)(t + 0x5C) = 0;
                }
                lbl_3_data_17260[j].id = -1;
                k = 0x18;
                if (j != 0) {
                    k = 0x17;
                }
                fn_80027918(k, lbl_3_rodata_1FA8);
            }
        }
    }
}

// .text:0x000C095C size:0x17C mapped:0x806FF9F0
void fn_3_C095C(u8* a) {
    Mtx m;
    void* args[2];
    void* objs[2];
    void** r;
    s32 i;
    u8* o;
    f32 zero;
    r = (void**)(*(u8**)(lbl_3_common_bss_35154 + 0x10) + 0x34);
    args[0] = *(void**)(lbl_3_common_bss_35154 + 0x40);
    objs[0] = lbl_3_common_bss_35154 + 0x20;
    args[1] = *(void**)(lbl_3_common_bss_35154 + 0x9C);
    objs[1] = lbl_3_common_bss_35154 + 0x7C;
    PSMTXTrans(m, *(f32*)(a + 8), *(f32*)(a + 0xC), *(f32*)(a + 0x10));
    PSMTXConcat((f32(*)[4])(fn_80052734(fn_8005268C()) + 0x40), m, m);
    zero = lbl_3_rodata_1FA8;
    i = 1;
    do {
        o = objs[i];
        *(f32*)o = zero;
        *(s16*)(o + 0xC) = 0;
        *(f32*)(o + 4) = (f32) * (u32*)(a + 0x14);
        fn_80024DB0(o);
        fn_80024FA4(r, args[i], objs[i], -1);
    } while (i-- != 0);
    ((u8*)*r)[0x99] = 1;
    fn_800B4CA0(*r, (f32) * (u32*)(a + 0x14));
    fn_800B4C04(*r, lbl_3_rodata_1FAC);
    fn_800BDA24(r);
    ((u8*)*r)[0x98] = 0xFF;
    fn_800BDA94(r, m);
}

// .text:0x000C0AD8 size:0x174 mapped:0x806FFB6C
void fn_3_C0AD8(void) {
    u8* o = lbl_803CC1B8;
    u8* t = ((u8**)(lbl_8036E548 + 0x2C50))[*(s32*)(o + 0x1C)];
    if (o[0x20] == 0 && t != NULL) {
        fn_800A7D4C(0, &lbl_3_data_174A8[*(s32*)(o + 0x18)].e[lbl_803CBBC0]);
        lbl_3_data_174A8[*(s32*)(o + 0x18)].e[lbl_803CBBC0].x = *(s32*)(o + 0x14);
        lbl_3_data_174A8[*(s32*)(o + 0x18)].e[lbl_803CBBC0].a = *(f32*)(t + 0x34);
        lbl_3_data_174A8[*(s32*)(o + 0x18)].e[lbl_803CBBC0].b = *(f32*)(t + 0x38);
        lbl_3_data_174A8[*(s32*)(o + 0x18)].e[lbl_803CBBC0].c = *(f32*)(t + 0x3C);
        if (lbl_80366158[0x28] == 0) {
            *(s32*)(o + 0x14) += 1;
        }
    } else {
        ((u8**)lbl_3_data_174A0)[*(s32*)(o + 0x18)] = 0;
        fn_800B0A14_removeQueue(lbl_3_data_174A0);
    }
    if (*(u32*)(o + 0x14) >= *(u16*)(lbl_3_common_bss_35154 + 0x38)) {
        ((u8**)lbl_3_data_174A0)[*(s32*)(o + 0x18)] = 0;
        fn_800B0A14_removeQueue(lbl_3_data_174A0);
    }
}

// .text:0x000C0C4C size:0x9C mapped:0x806FFCE0
void fn_3_C0C4C(s32 i) {
    u8* p = fn_800B0A5C_insertQueue(fn_3_C0AD8, 1);
    *(s32*)(p + 0x14) = 0;
    *(s32*)(p + 0x1C) = lbl_3_data_17260[i].id;
    p[0x20] = 0;
    for (i = 0; i < 2; i++) {
        if (lbl_3_data_174A0[i] == 0) {
            lbl_3_data_174A0[i] = p;
            *(s32*)(p + 0x18) = i;
            break;
        }
    }
}

// .text:0x000C0CE8 size:0x28 mapped:0x806FFD7C
void fn_3_C0CE8(u8 v, f32 x, f32 y, f32 z) {
    *(f32*)(lbl_3_common_bss_35154 + 0x434) = x;
    *(f32*)(lbl_3_common_bss_35154 + 0x438) = y;
    *(f32*)(lbl_3_common_bss_35154 + 0x43C) = z;
    lbl_3_common_bss_35154[0x467] = v;
    *(u32*)(lbl_3_common_bss_35154 + 0x3AC) |= 0x100;
}

// .text:0x000C0D10 size:0xC8 mapped:0x806FFDA4
void fn_3_C0D10(s32 i, u8 v1, u8 v2, u8 v3, u8 v4) {
    s32 o = i * 16;
    s32 o2;
    u8* q;
    lbl_3_bss_9D40[o] = v4;
    lbl_3_bss_9D40[1 + o] = v1;
    *(u16*)&lbl_3_bss_9D40[o + 2] = *(u16*)&lbl_3_bss_9D40[o];
    *(u32*)&lbl_3_bss_9D40[o + 4] = *(u32*)&lbl_3_bss_9D40[o];
    memcpy(&lbl_3_bss_9D40[o + 8], &lbl_3_bss_9D40[o], 8);
    o2 = o + 0x20;
    q = lbl_3_bss_9D40 + o2;
    *q = v2;
    lbl_3_bss_9D40[1 + o2] = v3;
    *(u16*)&lbl_3_bss_9D40[o + 0x22] = *(u16*)q;
    *(u32*)&lbl_3_bss_9D40[o + 0x24] = *(u32*)q;
    memcpy(&lbl_3_bss_9D40[o + 0x28], q, 8);
    DCStoreRange(lbl_3_bss_9D40, 0x40);
}

// .text:0x000C0DD8 size:0x1B4 mapped:0x806FFE6C
void fn_3_C0DD8(s32 unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2) {
    f32 m[12];
    s32 k;
    s16* q;
    s32 a = *(s8*)((u8*)fn_80011570() + 0x254); // TODO type: CharActor.index
    k = 1;
    q = &lbl_3_data_17260[1].id;
    do {
        if (a == *q) {
            break;
        }
        q -= 0x10;
    } while (k-- != 0);
    if (k < 0) {
        return;
    }
    GXLoadTexObj(lbl_3_bss_9D20, *map);
    memset(m, 0, 0x30);
    m[3] = lbl_3_rodata_1FA8;
    m[7] = (f32)k;
    GXLoadTexMtxImm(m, *map * 3 + 0x1E, 1);
    GXSetTexCoordGen2(*coord, 1, 4, *map * 3 + 0x1E, 0, 0x7D);
    GXSetTevOrder(*stage, *coord, *map, 4);
    GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
    GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
    GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    *stage += 1;
    *map += 1;
    *c2 += 1;
    *c1 += 1;
}

// .text:0x000C0F8C size:0x78 mapped:0x80700020
void fn_3_C0F8C(void) {
    GXInitTexObj(lbl_3_bss_9D20, lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
    GXInitTexObjLOD(lbl_3_bss_9D20, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
}

// .text:0x000C1004 size:0x1C8 mapped:0x80700098
// 99.4%: only regalloc differs (original: j in r31, inlined fn_3_C0D10 offset in r29; ours swapped). Decl order, jj copy, C0D10 types did not change it.
void fn_3_C1004(void) {
    s32 j;
    s16* q;
    u8* a = *(u8**)&lbl_803CC1B8;
    u8 id = a[0x14];
    u8* t = ((u8**)(lbl_8036E548 + 0x2C50))[id];
    s32 k;
    j = 1;
    q = &lbl_3_data_17260[1].id;
    do {
        if (id == *q) {
            break;
        }
        q -= 0x10;
    } while (j-- != 0);
    if (j >= 0) {
        if (--a[0x16] == 0) {
            if (t != NULL) {
                *(s32*)(t + 0x5C) = 0;
            }
            lbl_3_data_17260[j].id = -1;
            fn_800B0A14_removeQueue(lbl_3_data_17260);
        }
        fn_3_C0D10(j, lbl_3_data_17258[j][0], lbl_3_data_17258[j][1], lbl_3_data_17258[j][2], (a[0x15] * a[0x16]) / 10);
        k = 0x18;
        if (j != 0) {
            k = 0x17;
        }
        fn_80027918(k, (f32)a[0x16] / lbl_3_rodata_1FC0);
    }
}

// .text:0x000C11CC size:0x178 mapped:0x80700260
void fn_3_C11CC(s32 who, s32 a) {
    s32 j;
    s16* q;
    u8* o;
    s32 k;
    j = 1;
    q = &lbl_3_data_17260[1].id;
    do {
        if (who == *q) {
            break;
        }
        q -= 0x10;
    } while (j-- != 0);
    if (j >= 0) {
        if (a != 0) {
            u8* t = ((u8**)(lbl_8036E548 + 0x2C50))[who];
            if (t != NULL) {
                *(s32*)(t + 0x5C) = 0;
            }
            lbl_3_data_17260[j].id = -1;
            k = 0x18;
            if (j != 0) {
                k = 0x17;
            }
            fn_80027918(k, lbl_3_rodata_1FA8);
        } else {
            o = fn_800B0A5C_insertQueue(fn_3_C1004, *(u16*)(*(u8**)&lbl_803CC1B8 + 0x12));
            o[0x14] = who;
            {
                o[0x15] = lbl_3_data_17248[j] * (0.5 * sin(lbl_3_data_1724C[j] * lbl_3_data_17260[j].x / lbl_3_rodata_1FD0) + 0.5);
            }
            o[0x16] = 10;
        }
    }
}

// .text:0x000C1344 size:0x42C mapped:0x807003D8
extern f64 lbl_3_rodata_1FB0;
extern f64 lbl_3_rodata_1FB8;
// NONMATCHING 75%: statement order around the burst (k / delay reload) and register allocation
#if NONMATCHING
void fn_3_C1344(s32 who, s32 track, f32 t, f32 t2) {
    u8* actor;
    E32_1F58* e;
    s16* q;
    s32 j;
    s32 i;
    s32 k;
    u8* o;
    if (lbl_80366158[0x28] != 0) {
        return;
    }
    actor = ((u8**)(lbl_8036E548 + 0x2C50))[who];
    if (actor == NULL) {
        return;
    }
    j = 1;
    q = &lbl_3_data_17260[1].id;
    do {
        if (who == *q) {
            break;
        }
        q -= 0x10;
    } while (j-- != 0);
    if (j < 0) {
        return;
    }
    e = &lbl_3_data_17260[j];
    getAnimRelatedCoordinates(who, 4, (Vec*)e->v);
    if (t > lbl_3_rodata_1FA8 && t < lbl_3_data_1749C) {
        if (lbl_3_data_17260[j].s2-- == 0) {
            lbl_3_data_17260[j].s2 = lbl_3_data_172AC.unk1C;
            k = 0x18;
            if (j != 0) {
                k = 0x17;
            }
            fn_80027674((Vec*)e->p, (Vec*)e->v, &lbl_3_data_172AC, k, (f32)lbl_3_data_172A0 / lbl_3_rodata_1FD4);
            *(void**)(actor + 0x5C) = fn_3_C0DD8; // TODO type: CharActor draw hook
        }
    }
    sin(t * lbl_3_data_1724C[j] / lbl_3_rodata_1FD0);
    if (t < lbl_3_rodata_1FD0) {
        fn_3_C0D10(j, lbl_3_data_17258[j][0], lbl_3_data_17258[j][1], lbl_3_data_17258[j][2],
                   (lbl_3_rodata_1FC8 * sin(t * lbl_3_data_1724C[j] / lbl_3_rodata_1FD0) + lbl_3_rodata_1FC8) * lbl_3_data_17248[j]);
        lbl_3_data_17260[j].x = t;
    } else {
        fn_3_C0D10(j, lbl_3_data_17258[j][0], lbl_3_data_17258[j][1], lbl_3_data_17258[j][2],
                   (lbl_3_rodata_1FC8 * sin(t2 * lbl_3_data_1724C[j] / lbl_3_rodata_1FD0) + lbl_3_rodata_1FC8) * lbl_3_data_17248[j]);
        lbl_3_data_17260[j].x = t2;
    }
    if (track != 0 && lbl_3_common_bss_35154[0x477 + j] == 0) {
        lbl_3_common_bss_35154[0x477 + j] = 1;
        o = fn_800B0A5C_insertQueue(fn_3_C0AD8, 1);
        *(s32*)(o + 0x14) = 0;
        *(s32*)(o + 0x1C) = e->id;
        o[0x20] = 0;
        for (i = 0; i < 2; i++) {
            if (lbl_3_data_174A0[i] == NULL) {
                lbl_3_data_174A0[i] = o;
                *(s32*)(o + 0x18) = i;
                break;
            }
        }
    }
}
#endif

// .text:0x000C1770 size:0x1C0 mapped:0x80700804
// NONMATCHING 99.5%: j and the slot offset j << 5 get swapped saved registers (r30/r29)
#if NONMATCHING
void fn_3_C1770(s32 who) {
    u8* t = ((u8**)(lbl_8036E548 + 0x2C50))[who];
    s32 j;
    s16* q;
    s32 k;
    if (t != NULL) {
        j = 1;
        q = &lbl_3_data_17260[1].id;
        do {
            if (*q == -1) {
                break;
            }
            q -= 0x10;
        } while (j-- != 0);
        if (j >= 0) {
            lbl_3_data_172AC.tex = *(void**)(lbl_3_common_bss_35154 + 4);
            lbl_3_data_17260[j].id = who;
            lbl_3_data_17260[j].p[0] = *(f32*)(t + 0x34);
            lbl_3_data_17260[j].p[2] = *(f32*)(t + 0x3C);
            lbl_3_data_17260[j].p[1] = -((f32)lbl_3_data_172EC[(s8)t[0x252]].v / lbl_3_rodata_1FD4);
            memcpy(lbl_3_data_17260[j].v, lbl_3_data_17260[j].p, 0xC);
            lbl_3_data_17260[j].s2 = 0;
            k = 0x18;
            if (j != 0) {
                k = 0x17;
            }
            fn_80027918(k, lbl_3_rodata_1FA8);
            GXInitTexObj(lbl_3_bss_9D20, lbl_3_bss_9D40, 4, 4, 6, 0, 0, 0);
            GXInitTexObjLOD(lbl_3_bss_9D20, 1, 1, 0.0f, 0.0f, 0.0f, 0, 0, 0);
            lbl_3_common_bss_35154[0x477 + j] = 0;
        }
    }
}
#endif
