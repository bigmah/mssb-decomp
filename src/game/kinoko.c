#include "game/kinoko.h"
#include "header_rep_data.h"
#include "Dolphin/GX/GXFifo.h"
#include "static/GameSettings.h"
#pragma dont_inline on

typedef struct {
    u8* buf;
    void* tex;
    s32 cnt;
} KinokoCtl;
extern KinokoCtl lbl_3_bss_BA00;
extern s32 lbl_3_bss_BA08[];
extern u8 lbl_80366158[];
extern s8 lbl_3_data_2A330;
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void DCFlushRange(void*, u32);

extern void GXLoadTexObj(void*, s32);
extern void GXSetTexCoordGen2(s32, s32, s32, s32, s32, s32);
extern void GXSetTevOrder(s32, s32, s32, s32);
extern void GXSetTevColorIn(s32, s32, s32, s32, s32);
extern void GXSetTevColorOp(s32, s32, s32, s32, s32, s32);
extern void GXSetTevAlphaIn(s32, s32, s32, s32, s32);
extern void GXSetTevAlphaOp(s32, s32, s32, s32, s32, s32);

extern void GXInitTexObj(void*, void*, s32, s32, s32, s32, s32, s32);
extern void GXInitTexObjLOD(void*, s32, s32, f32, f32, f32, s32, s32, s32);
extern void GXSetZMode(s32, s32, s32);
extern void GXSetBlendMode(s32, s32, s32, s32);
extern void GXSetCullMode(s32);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(s32, s32);
extern void GXSetVtxAttrFmt(s32, s32, s32, s32, s32);
extern void GXSetChanCtrl(s32, s32, s32, s32, s32, s32, s32);
extern void GXSetNumChans(s32);
extern void GXSetNumTexGens(s32);
extern void GXSetNumTevStages(s32);
extern void GXSetTevOp(s32, s32);
extern void GXLoadPosMtxImm(void*, s32);
extern void GXSetCurrentMtx(s32);
extern void GXSetProjection(void*, s32);
extern s32 fn_8005268C(void);
extern u8* fn_80052768_getCamera(s32);

// .text:0x0016917C size:0x2C0
void fn_3_16917C(s32 unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2) {
    KinokoCtl* c = &lbl_3_bss_BA00;
    s32 v;
    s32 i;
    s32 t;
    c->cnt += (lbl_80366158[0x28] == 0);
    if ((c->cnt & 1) == 0) {
        v = c->buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_2A330 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            c->buf[i] = v;
        }
        DCFlushRange(c->buf, 4);
        t = v + lbl_3_data_2A330 * 2;
        if (t > 0xFF || t < 0) {
            lbl_3_data_2A330 *= -1;
        }
    }
    GXLoadTexObj(c->tex, *map);
    GXSetTexCoordGen2(*coord, 1, 4, 0x3C, 0, 0x7D);
    GXSetTevOrder(*stage, *coord, *map, 0xFF);
    if (c->buf == (u8*)c + 0xA0) {
        GXSetTevColorIn(*stage, 0, 8, 9, 0xF);
        GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
        GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    } else {
        GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
        GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
        GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
        GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    }
    *stage += 1;
    *coord += 1;
    *map += 1;
    *c1 += 1;
    *c2 += 1;
}

// .text:0x0016943C size:0x164
void fn_3_16943C(void) {
    s32 v;
    s32 i;
    s32 t;
    lbl_3_bss_BA08[0] += (lbl_80366158[0x28] == 0);
    if ((lbl_3_bss_BA08[0] & 1) == 0) {
        v = lbl_3_bss_BA00.buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_2A330 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            lbl_3_bss_BA00.buf[i] = v;
        }
        DCFlushRange(lbl_3_bss_BA00.buf, 4);
        t = v + lbl_3_data_2A330 * 2;
        if (t > 0xFF || t < 0) {
            lbl_3_data_2A330 *= -1;
        }
    }
}

// .text:0x001695A0 size:0x4
void fn_3_1695A0(void) {
}

extern void fn_80011604(s32, void*);

// .text:0x001695A4 size:0x5C
void fn_3_1695A4(s32 a, u8 flag) {
    u8* p = (u8*)&lbl_3_bss_BA00;
    if (flag == 0) {
        *(u8**)p = p + 0xA0;
        *(u8**)(p + 4) = p + 0x2C;
    } else {
        *(u8**)p = p + 0x60;
        *(u8**)(p + 4) = p + 0xC;
    }
    fn_80011604(a, fn_3_16917C);
}

// The ribbon state (6 ribbons of 25 segments of 0x2C bytes, stride 0x44C; +0x19D4 frame counter,
// +0x19DC character id, +0x19DD enabled), the colour table and the two draw nodes. Defined here:
// the original addresses them through one pooled base.
u8 lbl_3_data_28928[0x19E0] = { 0 };
u8 lbl_3_data_2A308[6][4] = {
    { 0xFF, 0x00, 0x00, 0xC8 }, { 0xFF, 0xFF, 0x00, 0xC8 }, { 0x00, 0xFF, 0x00, 0xC8 },
    { 0x00, 0xFF, 0xFF, 0xC8 }, { 0x00, 0x00, 0xFF, 0xC8 }, { 0xFF, 0x00, 0xFF, 0xC8 },
};
typedef struct KinokoNode {
    /*0x0*/ u32 link; // set by fn_800A7D4C
    /*0x4*/ void (*draw)(void);
} KinokoNode;
KinokoNode lbl_3_data_2A320[2] = {
    { 0, fn_3_169984 },
    { 0, fn_3_169984 },
};
s8 lbl_3_data_2A330 = -1; // ribbon sway direction (+1/-1)
typedef struct {
    void* p[8];
    f32 v[3];
    u8 flag;
    u8 pad[3];
} RibEnt;
extern RibEnt lbl_3_bss_BAE0[];
extern void PSVECAdd(void*, void*, void*);
extern void PSVECScale(void*, void*, f32);
extern f32 PSVECMag(void*);
extern void PSVECNormalize(void*, void*);
extern void PSVECSubtract(void*, void*, void*);
extern void PSVECCrossProduct(void*, void*, void*);
extern void* memcpy(void*, void*, u32);
extern void fn_3_16A07C(void);
extern void PSMTXCopy(void* src, void* dst);
extern void PSMTXMultVec(void* m, void* src, void* dst);
extern void GXBegin(s32 type, s32 fmt, u16 n);
extern f32 lbl_3_rodata_402C; // -1.0f
extern void* memset(void*, s32, u32);
extern void* fn_800B0A5C_insertQueue(void*, s32);

// .text:0x0016C394 size:0x7C
void fn_3_16C394(s8 a) {
    memset(lbl_3_data_28928, 0, 0x19E0);
    memset(lbl_3_bss_BAE0, 0, 0x1BF0);
    lbl_3_data_28928[0x19DC] = a;
    lbl_3_data_28928[0x19DD] = 1;
    *(s32*)(lbl_3_data_28928 + 0x19D4) = 1;
    fn_3_16B884();
    fn_800B0A5C_insertQueue(fn_3_16A07C, 0);
}

extern char lbl_3_rodata_4050[];
extern char lbl_3_rodata_405C[];
extern s32 fn_8001B728(s32, s32, void*);
extern void OSPanic(const char*, int, const char*, ...);

// .text:0x0016B488 size:0x12C
void fn_3_16B488(void* out, s8 id) {
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(out, 0, 0xC);
    if (fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], id, out) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x1E, out);
            break;
        case 32:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x22, out);
            break;
        case 7:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 5, out);
            break;
        case 18:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x13, out);
            break;
        case 24:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x19, out);
            break;
        }
    }
}

// .text:0x00169600 size:0x204
void fn_3_169600(void) {
    u8* base = (u8*)&lbl_3_bss_BA00;
    u32 i;
    u32 j;
    u32 idx;
    u8* p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = base + 0xA0;
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0x9B;
                p[1] = 0x9B;
            } else {
                p = base + 0xA0;
                p += idx;
                p[2] = 0;
                p[0] = 0;
                p[3] = 0xFF;
                p[1] = 0xFF;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = base + 0x60;
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0;
                p[1] = 0;
            } else {
                p = base + 0x60;
                p += idx;
                p[2] = 0x9B;
                p[0] = 0x9B;
                p[3] = 0xFF;
                p[1] = 0xFF;
            }
        }
    }
    GXInitTexObj(base + 0x2C, base + 0xA0, 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(base + 0x2C, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    GXInitTexObj(base + 0xC, base + 0x60, 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(base + 0xC, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    lbl_3_data_2A330 = -1;
    *(s32*)(base + 8) = 0;
}

// .text:0x00169804 size:0x180
void fn_3_169804(void) {
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 1, 0);
    GXSetCullMode(2);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOp(0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C()) + 0x40, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C()), 0);
}

// .text:0x00169984 size:0x37C mapped:0x807A8A18
// One entry of the back-to-front sort of the mushroom ribbon quads.
typedef struct RibSortEnt {
    f32 depth;
    u32 idx;
} RibSortEnt;

// Draws the ribbon quads sorted by view-space depth.
// NONMATCHING 97%: loop counters/pointers get different saved registers (r27/r28/r30 rotated)
#if NONMATCHING
void fn_3_169984(void) {
    RibSortEnt swap;
    f32 viewPos[3];
    f32 view[3][4];
    RibSortEnt list[149];
    RibSortEnt* sorted;
    RibSortEnt* front;
    RibSortEnt* back;
    RibSortEnt* a;
    RibSortEnt* b;
    RibEnt* e;
    u32 i;
    u32 j;
    f32 noDepth;

    PSMTXCopy(fn_80052768_getCamera(fn_8005268C()) + 0x40, view);
    sorted = list;
    noDepth = lbl_3_rodata_402C;
    e = lbl_3_bss_BAE0;
    back = &list[148];
    front = sorted;
    for (i = 0; i < 149; i++) {
        if (e->flag == 0) {
            back->idx = i;
            back->depth = noDepth;
            back--;
        } else {
            PSMTXMultVec(view, e->v, viewPos);
            front->depth = viewPos[2];
            front->idx = i;
            front++;
        }
        e++;
    }
    a = sorted;
    for (i = 0; i < 148; i++) {
        for (j = i + 1, b = &list[j]; j < 149; j++) {
            if (a->depth > b->depth) {
                memcpy(&swap, a, sizeof(RibSortEnt));
                memcpy(a, b, sizeof(RibSortEnt));
                memcpy(b, &swap, sizeof(RibSortEnt));
            }
            b++;
        }
        a++;
    }

    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 1, 0);
    GXSetCullMode(2);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(0, 0xF, 0xF, 0xF, 0xA);
    GXSetTevAlphaIn(0, 7, 7, 7, 5);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetTevOp(0, 4);
    GXSetTevColorOp(0, 0, 0, 0, 0, 0);
    GXSetTevAlphaOp(0, 0, 0, 0, 0, 0);
    GXLoadPosMtxImm(fn_80052768_getCamera(fn_8005268C()) + 0x40, 0);
    GXSetCurrentMtx(0);
    GXSetProjection(fn_80052768_getCamera(fn_8005268C()), 0);

    for (i = 0; i < 149; i++) {
        e = &lbl_3_bss_BAE0[sorted->idx];
        if (e->flag != 0) {
            GXBegin(0x80, 0, 4);
            {
                f32* q = e->p[0];
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
            }
            GXWGFifo.u32 = *(u32*)e->p[1];
            {
                f32* q = e->p[2];
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
            }
            GXWGFifo.u32 = *(u32*)e->p[3];
            {
                f32* q = e->p[4];
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
            }
            GXWGFifo.u32 = *(u32*)e->p[5];
            {
                f32* q = e->p[6];
                f32 z = q[2];
                f32 y = q[1];
                f32 x = q[0];
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
            }
            GXWGFifo.u32 = *(u32*)e->p[7];
        }
        sorted++;
    }
}
#endif

// .text:0x00169D00 size:0x170
void fn_3_169D00(u8* base, u32* cnt) {
    u8* p = base + 0x420;
    u8* q;
    u32 i = 0x18;
    while (i != 0 && *cnt < 0x95) {
        if (p[0x2A] != 0) {
            q = base + (i - 1) * 0x2C;
            PSVECAdd(p, q, lbl_3_bss_BAE0[*cnt].v);
            PSVECScale(lbl_3_bss_BAE0[*cnt].v, lbl_3_bss_BAE0[*cnt].v, 0.5f);
            lbl_3_bss_BAE0[*cnt].p[0] = q + 0xC;
            lbl_3_bss_BAE0[*cnt].p[1] = q + 0x24;
            lbl_3_bss_BAE0[*cnt].p[2] = q + 0x18;
            lbl_3_bss_BAE0[*cnt].p[3] = q + 0x24;
            lbl_3_bss_BAE0[*cnt].p[4] = p + 0x18;
            lbl_3_bss_BAE0[*cnt].p[5] = p + 0x24;
            lbl_3_bss_BAE0[*cnt].p[6] = p + 0xC;
            lbl_3_bss_BAE0[*cnt].p[7] = p + 0x24;
            lbl_3_bss_BAE0[*cnt].flag = 1;
            *cnt += 1;
        }
        p -= 0x2C;
        i--;
    }
}

extern f32 lbl_3_rodata_4028;
extern f32 lbl_3_rodata_402C;
extern f32 lbl_3_rodata_4034;
extern f32 lbl_3_rodata_4038;
extern f32 lbl_3_rodata_403C;

// .text:0x00169E70 size:0x20C
void fn_3_169E70(u8* base) {
    f32 a[3];
    f32 b[3];
    f32 c[3];
    f32 d[3];
    f32 e[3];
    u8* cam = fn_80052768_getCamera(0);
    u8* p = base;
    u32 i = 0;
    f32 m;
    do {
        if (p[0x2A] != 0) {
            a[0] = *(f32*)(cam + 0x60);
            a[1] = *(f32*)(cam + 0x64);
            a[2] = *(f32*)(cam + 0x68);
            m = PSVECMag(a);
            if (m == lbl_3_rodata_4028) {
                a[0] = lbl_3_rodata_4028;
                a[1] = lbl_3_rodata_4028;
                a[2] = lbl_3_rodata_4034;
            } else {
                PSVECNormalize(a, a);
            }
            if (i == 0) {
                memcpy(b, p, 0xC);
            } else {
                memcpy(b, base + (i - 1) * 0x2C, 0xC);
            }
            if (i == 0x18) {
                memcpy(c, p, 0xC);
            } else {
                memcpy(c, base + (i + 1) * 0x2C, 0xC);
            }
            PSVECSubtract(b, c, d);
            m = PSVECMag(d);
            if (m == lbl_3_rodata_4028) {
                d[2] = lbl_3_rodata_4028;
                d[1] = lbl_3_rodata_4028;
                d[0] = lbl_3_rodata_4034;
            }
            PSVECNormalize(d, d);
            PSVECCrossProduct(d, a, e);
            m = PSVECMag(e);
            if (m == lbl_3_rodata_4028) {
                e[2] = lbl_3_rodata_4028;
                e[1] = lbl_3_rodata_4028;
                e[0] = lbl_3_rodata_402C;
            }
            PSVECNormalize(e, e);
            PSVECScale(e, p + 0xC, lbl_3_rodata_4038);
            PSVECScale(e, p + 0x18, lbl_3_rodata_403C);
            PSVECAdd(p + 0xC, p, p + 0xC);
            PSVECAdd(p + 0x18, p, p + 0x18);
        }
        i++;
        p += 0x2C;
    } while (i < 0x19);
}

// The original inlines fn_3_16B5B4 and copies of fn_3_169D00 into fn_3_16A07C and fn_3_16B884:
// inlining stays on from here to the end of the file (deferred inlining reads the final state).
#pragma dont_inline off
// .text:0x0016A07C size:0x140C mapped:0x807A9110
extern u8 lbl_803CBBC0; // index of the display list buffer in use
extern void fn_800A7D4C(s32 list, void* node);
extern void fn_800B0A14_removeQueue(void*);

// fn_800B0A14_removeQueue ignores its argument. Some callers pass nothing: r3 is
// whatever the previous call left (e.g. right after fn_80034CEC). The matching
// build calls it through a (void) cast there; the port passes NULL.
#ifndef REMOVE_QUEUE_NOARG
#if NONMATCHING
#define REMOVE_QUEUE_NOARG() fn_800B0A14_removeQueue(NULL)
#else
#define REMOVE_QUEUE_NOARG() ((void (*)(void))fn_800B0A14_removeQueue)()
#endif
#endif
extern u8 g_Minigame[];
#define KINOKO_RIBBON(r) (lbl_3_data_28928 + (r) * 0x44C)   // 6 ribbons of 25 segments (0x2C each)
#define KINOKO_TICK (*(s32*)(lbl_3_data_28928 + 0x19D4))

// Advances a ribbon colour index (0..5).
#define KINOKO_NEXT_COLOR(c)      \
    do {                          \
        v = ++(c);                \
        if (v >= 6) {             \
            (c) = v - 6;          \
        }                         \
    } while (0)

// Inline copy of fn_3_169D00 (the original expands it once per ribbon in fn_3_16A07C).
static inline void fn_3_169D00_inline(u8* base, u32* cnt) {
    u8* p = base + 0x420;
    u8* q;
    u32 i = 0x18;
    while (i != 0 && *cnt < 0x95) {
        if (p[0x2A] != 0) {
            q = base + (i - 1) * 0x2C;
            PSVECAdd(p, q, lbl_3_bss_BAE0[*cnt].v);
            PSVECScale(lbl_3_bss_BAE0[*cnt].v, lbl_3_bss_BAE0[*cnt].v, 0.5f);
            lbl_3_bss_BAE0[*cnt].p[0] = q + 0xC;
            lbl_3_bss_BAE0[*cnt].p[1] = q + 0x24;
            lbl_3_bss_BAE0[*cnt].p[2] = q + 0x18;
            lbl_3_bss_BAE0[*cnt].p[3] = q + 0x24;
            lbl_3_bss_BAE0[*cnt].p[4] = p + 0x18;
            lbl_3_bss_BAE0[*cnt].p[5] = p + 0x24;
            lbl_3_bss_BAE0[*cnt].p[6] = p + 0xC;
            lbl_3_bss_BAE0[*cnt].p[7] = p + 0x24;
            lbl_3_bss_BAE0[*cnt].flag = 1;
            *cnt += 1;
        }
        p -= 0x2C;
        i--;
    }
}

// Per-frame task of the mushroom ribbon effect: trails the ribbon segments,
// cycles their colours, rebuilds the quad list and queues the draw.
// NONMATCHING 97%: register allocation; the original also keeps the ribbon pointers of the
// fn_3_169E70 calls in saved registers and reuses them in the inlined fn_3_169D00 loops.
#if NONMATCHING
void fn_3_16A07C(void) {
    u8* dst;
    u8* src;
    u32 i;
    u32 count;
    u8 alpha;
    u8 v;

    if (g_d_GameSettings._55 != 0 || g_Minigame[0x1A40] != 0) { // TODO type: g_Minigame._1A40
        REMOVE_QUEUE_NOARG(); // removes the running task
        memset(lbl_3_data_28928, 0, 0x19E0);
        return;
    }
    if (*(s8*)(g_Minigame + 0x1D74) == -1 || lbl_3_data_28928[0x19DD] == 0) { // TODO type: g_Minigame.playerIDWithPowerup[0]
        REMOVE_QUEUE_NOARG();
        memset(lbl_3_data_28928, 0, 0x19E0);
        return;
    }

    if (lbl_80366158[0x28] == 0) {
        KINOKO_TICK++;
        dst = lbl_3_data_28928 + 24 * 0x2C;
        for (i = 24; i != 0; i--) {
            alpha = (24 - i) * 8;
            src = lbl_3_data_28928 + (i - 1) * 0x2C;
            memcpy(dst, src, 0x2C);
            dst[0x27] = alpha;
            memcpy(dst + 0x44C, src + 0x44C, 0x2C);
            dst[0x44C + 0x27] = alpha;
            memcpy(dst + 0x898, src + 0x898, 0x2C);
            dst[0x898 + 0x27] = alpha;
            memcpy(dst + 0xCE4, src + 0xCE4, 0x2C);
            dst[0xCE4 + 0x27] = alpha;
            memcpy(dst + 0x1130, src + 0x1130, 0x2C);
            dst[0x1130 + 0x27] = alpha;
            memcpy(dst + 0x157C, src + 0x157C, 0x2C);
            dst[0x157C + 0x27] = alpha;
            dst -= 0x2C;
        }
        if (KINOKO_TICK % 5 == 0) {
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(0)[0x28]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(0)[0x29]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(1)[0x28]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(1)[0x29]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(2)[0x28]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(2)[0x29]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(3)[0x28]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(3)[0x29]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(4)[0x28]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(4)[0x29]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(5)[0x28]);
            KINOKO_NEXT_COLOR(KINOKO_RIBBON(5)[0x29]);
        }
        fn_3_16B5B4(KINOKO_RIBBON(0), 0x1C, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(1), 0x20, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(2), 4, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(3), 7, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(4), 0x12, KINOKO_TICK % 5);
        fn_3_16B5B4(KINOKO_RIBBON(5), 0x18, KINOKO_TICK % 5);
    }

    fn_3_169E70(KINOKO_RIBBON(0));
    fn_3_169E70(KINOKO_RIBBON(1));
    fn_3_169E70(KINOKO_RIBBON(2));
    fn_3_169E70(KINOKO_RIBBON(3));
    fn_3_169E70(KINOKO_RIBBON(4));
    fn_3_169E70(KINOKO_RIBBON(5));
    count = 0;
    memset(lbl_3_bss_BAE0, 0, 0x1BF0);
    fn_3_169D00_inline(KINOKO_RIBBON(0), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(1), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(2), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(3), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(4), &count);
    fn_3_169D00_inline(KINOKO_RIBBON(5), &count);
    fn_800A7D4C(1, &lbl_3_data_2A320[lbl_803CBBC0]);
}
#endif

extern const f32 lbl_3_rodata_4040;
extern const f64 lbl_3_rodata_4048;

// .text:0x0016B5B4 size:0x2D0 mapped:0x807AA648
void fn_3_16B5B4(u8* out, s8 id, int t) {
    f64 k1;
    f32 k = (f32)t / lbl_3_rodata_4040;
    k1 = lbl_3_rodata_4048 - k;
    out[0x24] = k1 * lbl_3_data_2A308[out[0x28]][0] + k * lbl_3_data_2A308[out[0x29]][0];
    out[0x25] = k1 * lbl_3_data_2A308[out[0x28]][1] + k * lbl_3_data_2A308[out[0x29]][1];
    out[0x26] = k1 * lbl_3_data_2A308[out[0x28]][2] + k * lbl_3_data_2A308[out[0x29]][2];
    out[0x27] = k1 * lbl_3_data_2A308[out[0x28]][3] + k * lbl_3_data_2A308[out[0x29]][3];
    out[0x2A] = 1;
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(out, 0, 0xC);
    if (fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], id, out) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x1E, out);
            break;
        case 32:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x22, out);
            break;
        case 7:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 5, out);
            break;
        case 18:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x13, out);
            break;
        case 24:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x19, out);
            break;
        }
    }
}

// Inline copy of fn_3_16B5B4 for fn_3_16B884 (the original inlines it there with t = 0; the 5.0f
// literal lets k fold to a 0.0f constant).
static inline void fn_3_16B5B4_inline(u8* out, s8 id, int t) {
    f64 k1;
    f32 k = (f32)t / 5.0f;
    k1 = lbl_3_rodata_4048 - k;
    out[0x24] = k1 * lbl_3_data_2A308[out[0x28]][0] + k * lbl_3_data_2A308[out[0x29]][0];
    out[0x25] = k1 * lbl_3_data_2A308[out[0x28]][1] + k * lbl_3_data_2A308[out[0x29]][1];
    out[0x26] = k1 * lbl_3_data_2A308[out[0x28]][2] + k * lbl_3_data_2A308[out[0x29]][2];
    out[0x27] = k1 * lbl_3_data_2A308[out[0x28]][3] + k * lbl_3_data_2A308[out[0x29]][3];
    out[0x2A] = 1;
    if (out == NULL) {
        OSPanic(lbl_3_rodata_4050, 0x11C, lbl_3_rodata_405C);
    }
    memset(out, 0, 0xC);
    if (fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], id, out) == 0) {
        switch (id) {
        case 28:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x1E, out);
            break;
        case 32:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x22, out);
            break;
        case 7:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 5, out);
            break;
        case 18:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x13, out);
            break;
        case 24:
            fn_8001B728(((s8*)lbl_3_data_28928)[0x19DC], 0x19, out);
            break;
        }
    }
}

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
// Resets the six mushroom ribbons: each ribbon is 25 segments of 0x2C bytes
// (stride 0x44C); segment +0x24 is the RGBA colour, +0x27 its alpha,
// +0x28/+0x29 the from/to colour indices into lbl_3_data_2A308.
// NONMATCHING 72%: the original computes 1.0 - k once (f31) for all six inlined copies and re-reads
// the stored from/to indices with clrlslwi; register allocation differs throughout.
#if NONMATCHING
void fn_3_16B884(void) {
    u8* src;
    u8* dst;
    u32 i;
    u8 alpha;

    lbl_3_data_28928[0x28] = 0;
    lbl_3_data_28928[0x29] = 1;
    fn_3_16B5B4_inline(lbl_3_data_28928, 0x1C, 0);
    lbl_3_data_28928[0x44C + 0x28] = 1;
    lbl_3_data_28928[0x44C + 0x29] = 2;
    fn_3_16B5B4_inline(lbl_3_data_28928 + 0x44C, 0x20, 0);
    lbl_3_data_28928[0x898 + 0x28] = 2;
    lbl_3_data_28928[0x898 + 0x29] = 3;
    fn_3_16B5B4_inline(lbl_3_data_28928 + 0x898, 4, 0);
    lbl_3_data_28928[0xCE4 + 0x28] = 3;
    lbl_3_data_28928[0xCE4 + 0x29] = 4;
    fn_3_16B5B4_inline(lbl_3_data_28928 + 0xCE4, 7, 0);
    lbl_3_data_28928[0x1130 + 0x28] = 4;
    lbl_3_data_28928[0x1130 + 0x29] = 5;
    fn_3_16B5B4_inline(lbl_3_data_28928 + 0x1130, 0x12, 0);
    lbl_3_data_28928[0x157C + 0x28] = 5;
    lbl_3_data_28928[0x157C + 0x29] = 0;
    fn_3_16B5B4_inline(lbl_3_data_28928 + 0x157C, 0x18, 0);

    dst = lbl_3_data_28928 + 0x2C;
    for (i = 1; i < 25; i++) {
        alpha = (24 - i) * 8;
        src = lbl_3_data_28928 + (i - 1) * 0x2C;
        memcpy(dst, src, 0x2C);
        dst[0x27] = alpha;
        memcpy(dst + 0x44C, src + 0x44C, 0x2C);
        dst[0x44C + 0x27] = alpha;
        memcpy(dst + 0x898, src + 0x898, 0x2C);
        dst[0x898 + 0x27] = alpha;
        memcpy(dst + 0xCE4, src + 0xCE4, 0x2C);
        dst[0xCE4 + 0x27] = alpha;
        memcpy(dst + 0x1130, src + 0x1130, 0x2C);
        dst[0x1130 + 0x27] = alpha;
        memcpy(dst + 0x157C, src + 0x157C, 0x2C);
        dst[0x157C + 0x27] = alpha;
        dst += 0x2C;
    }
}
#endif

