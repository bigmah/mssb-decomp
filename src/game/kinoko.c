#include "game/kinoko.h"
#include "header_rep_data.h"
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

extern u8 lbl_3_data_28928[];
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
void fn_3_169984(void) {
    return;
}

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

// .text:0x0016A07C size:0x140C mapped:0x807A9110
void fn_3_16A07C(void) {
    return;
}

extern const f32 lbl_3_rodata_4040;
extern const f64 lbl_3_rodata_4048;
extern u8 lbl_3_data_2A308[][4];

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

// .text:0x0016B884 size:0xB10 mapped:0x807AA918
void fn_3_16B884(void) {
    return;
}

