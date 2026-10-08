#include "game/rep_3880.h"
#include "header_rep_data.h"

extern u8 lbl_3_data_26C94[];
extern const f32 lbl_3_rodata_39F8;
extern const f32 lbl_3_rodata_39F4;
extern const f64 lbl_3_rodata_39E8;
extern s32 lbl_3_data_26D00[];
extern void fn_8003403C(f32, f32);
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_data_26D5C[];
extern u8 lbl_3_data_21770[];
extern u8 lbl_3_data_26E9C[];
extern void* fn_800337CC(void*, int, int, void*);
extern s8 lbl_3_bss_B85C[];
extern void fn_80033794(void*);
extern u8 lbl_3_data_26BDC[];
extern u8 lbl_3_data_26BEC[];
extern f32 lbl_3_rodata_3A18;
extern f32 fn_3_119854(u8 i);

extern u8 lbl_8036E548[];
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#include "C3/control.h"


extern u8 g_Minigame[];
extern u8 lbl_3_data_26E00[];
extern const Vec lbl_3_rodata_3908;
extern f32 fn_3_119D28(void);
extern u8 lbl_3_data_26CB8[];
extern s32 fn_8001B728(s32, s32, void*);
extern int rand(void);
extern void* fn_80033A24(void*, int, int, int, int, int);
extern u8 lbl_3_data_26E24[];
extern u8 lbl_3_data_26C3C[];
extern u8 lbl_3_bss_B894[];
extern const f32 lbl_3_rodata_3930;
extern const f32 lbl_3_rodata_39B8;
extern const f64 lbl_3_rodata_39C8;
extern u8 lbl_80366158[];
extern u8 lbl_3_data_26E40[];
extern void fn_80033620(void);
extern void fn_80033F64(f32, f32, f32);
extern void fn_80033CC8(void*, void*);
extern u8 lbl_3_data_26D50[];
extern u8 lbl_3_data_26CD0[];
extern const f32 lbl_3_rodata_39E0;
extern f32 shortAngleToRad(s16);
extern u8 lbl_3_data_26E7C[];
extern u8 lbl_3_data_26D88[];
extern u8 lbl_3_data_26DC4[];
extern void* fn_80031F34(void*, u32);
extern void fn_8003403C(f32, f32);
extern const f32 lbl_3_rodata_3970;
extern const f32 lbl_3_rodata_39C4;
extern const f64 lbl_3_rodata_3990;
extern const f64 lbl_3_rodata_3968;
extern const f64 lbl_3_rodata_39D8;
extern const f64 lbl_3_rodata_3978;
extern f64 cos(f64);
extern f64 sin(f64);
extern f32 lbl_3_bss_B860[];
extern const f32 lbl_3_rodata_39A8;
extern f32 lbl_3_rodata_392C;
extern f32 lbl_3_rodata_3A00;
extern const Vec lbl_3_rodata_38DC;
extern const f32 lbl_3_rodata_3A04;
extern const f32 lbl_3_rodata_3948;
extern void fn_8005268C(void);
extern u8* fn_80052734(void);
extern f64 acos(f64);
extern const Vec lbl_3_rodata_3914;
extern u8 lbl_3_data_26BFC[];
extern void* memcpy(void*, const void*, unsigned long);
extern void fn_3_11F4B4(s32 idx, s32 flag);
extern u8 lbl_3_data_26C1C[];
extern const f32 lbl_3_rodata_3934[];
typedef struct { f32 x, y, z; } V3B;
extern u8* lbl_3_bss_B850;
extern void* memset(void*, int, unsigned long);
#pragma dont_inline on

typedef struct {
    u8 pad0[0xC];
    u8* head;
    u8 pad[0x14 - 0x10];
    u16 hi : 4;
    u16 cnt : 12;
} H154238;

// .text:0x0014737C size:0x3FC mapped:0x80786410
void fn_3_14737C(void) {
    return;
}

// .text:0x00147778 size:0x488 mapped:0x8078680C
void fn_3_147778(void* n, void* a) {
    return;
}

// .text:0x00147C00 size:0xFC mapped:0x80786C94
void fn_3_147C00(void* arg) {
    u8 buf[0x5C];
    u8* h = fn_800339F0(0, 0x26);
    u8* n;
    u8* p;
    H154238* hh;
    if (h != NULL) {
        n = fn_800337CC(buf, *(int*)(lbl_3_data_26E9C + 8) + *(int*)(lbl_3_data_26E9C + 0x30), 1, lbl_3_data_26E9C);
        if (n != NULL) {
            fn_3_147778(n, arg);
            p = *(u8**)(h + 0xC);
            while (*(u8**)p != NULL) {
                p = *(u8**)p;
            }
            *(u8**)p = *(u8**)(n + 0xC);
            ((H154238*)h)->cnt += ((H154238*)n)->cnt;
        }
    } else {
        n = fn_80033A24(fn_3_14737C, 0x80, 0, *(int*)(lbl_3_data_26E9C + 8) + *(int*)(lbl_3_data_26E9C + 0x30), 1, 0x26);
        if (n != NULL) {
            fn_3_147778(n, arg);
        }
    }
}

// .text:0x00147CFC size:0x100 mapped:0x80786D90
void fn_3_147CFC(void* arg) {
    u8 buf[0x5C];
    u8* h;
    u8* n;
    u8* p;
    if (arg == NULL) {
        return;
    }
    h = fn_800339F0(0, 0x26);
    if (h != NULL) {
        n = fn_800337CC(buf, *(int*)(lbl_3_data_26E9C + 8) + *(int*)(lbl_3_data_26E9C + 0x30), 1, lbl_3_data_26E9C);
        if (n != NULL) {
            fn_3_147778(n, arg);
            p = *(u8**)(h + 0xC);
            while (*(u8**)p != NULL) {
                p = *(u8**)p;
            }
            *(u8**)p = *(u8**)(n + 0xC);
            ((H154238*)h)->cnt += ((H154238*)n)->cnt;
        }
    } else {
        n = fn_80033A24(fn_3_14737C, 0x80, 0, *(int*)(lbl_3_data_26E9C + 8) + *(int*)(lbl_3_data_26E9C + 0x30), 1, 0x26);
        if (n != NULL) {
            fn_3_147778(n, arg);
        }
    }
}

// .text:0x00147DFC size:0x24 mapped:0x80786E90
void fn_3_147DFC(void) {
    pitchingMachinePitching(0x25);
}

// .text:0x00147E20 size:0x174 mapped:0x80786EB4
void fn_3_147E20(void) {
    GXSetZMode(1, 3, 1);
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
    GXLoadPosMtxImm((void*)((u8*)fn_80052768_getCamera(0) + 0x40), 0);
    GXSetCurrentMtx(0);
}

// .text:0x00147F94 size:0x14C mapped:0x80787028
void fn_3_147F94(void) {
    GXSetZMode(1, 7, 1);
    GXSetBlendMode(1, 4, 5, 0);
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
}

// 96%: orig reads vertices 2-3 of the 2nd quad via lfsu (r4 = base+0xc); we fold to base-relative lfs; also li r3,1 scheduling
// .text:0x001480E0 size:0x174 mapped:0x80787174
void fn_3_1480E0(u8* o) {
    f32* v;
    GXSetCullMode(2);
    GXBegin(0x80, 0, 4);
    v = (f32*)lbl_3_bss_B860;
    GXWGFifo.f32 = v[0];
    GXWGFifo.f32 = v[1];
    GXWGFifo.f32 = v[2];
    GXWGFifo.u32 = *(u32*)(o + 0x40);
    GXWGFifo.f32 = v[3];
    GXWGFifo.f32 = v[4];
    GXWGFifo.f32 = v[5];
    GXWGFifo.u32 = *(u32*)(o + 0x40);
    GXWGFifo.f32 = v[6];
    GXWGFifo.f32 = v[7];
    GXWGFifo.f32 = v[8];
    GXWGFifo.u32 = *(u32*)(o + 0x40);
    GXWGFifo.f32 = v[9];
    GXWGFifo.f32 = v[10];
    GXWGFifo.f32 = v[11];
    GXWGFifo.u32 = *(u32*)(o + 0x40);
    GXSetCullMode(1);
    GXBegin(0x80, 0, 4);
    {
    f32* p = v + 3;
    GXWGFifo.f32 = v[0];
    GXWGFifo.f32 = v[1];
    GXWGFifo.f32 = v[2];
    GXWGFifo.u32 = *(u32*)(o + 0x44);
    GXWGFifo.f32 = v[3];
    GXWGFifo.f32 = v[4];
    GXWGFifo.f32 = v[5];
    GXWGFifo.u32 = *(u32*)(o + 0x44);
    GXWGFifo.f32 = p[3];
    GXWGFifo.f32 = p[4];
    GXWGFifo.f32 = p[5];
    GXWGFifo.u32 = *(u32*)(o + 0x44);
    GXWGFifo.f32 = p[6];
    GXWGFifo.f32 = p[7];
    GXWGFifo.f32 = p[8];
    GXWGFifo.u32 = *(u32*)(o + 0x44);
    }
}

// .text:0x00148254 size:0x180 mapped:0x807872E8
void fn_3_148254(u8* a, u8* b) {
    Control c;
    Mtx m;
    Vec v;
    f32 hx;
    f32 hy;
    u8* t;
    f32 h = *(f32*)(b + 0x3C);
    hx = *(f32*)(b + 0x38);
    hx *= lbl_3_rodata_39A8;
    hy = h * lbl_3_rodata_39A8;
    t = ((u8**)(lbl_8036E548 + 0x2C50))[(s8)a[0x18]];
    lbl_3_bss_B860[3] = hx;
    lbl_3_bss_B860[0] = -hx;
    lbl_3_bss_B860[1] = -hy;
    lbl_3_bss_B860[4] = -hy;
    lbl_3_bss_B860[6] = hx;
    lbl_3_bss_B860[7] = hy;
    lbl_3_bss_B860[9] = -hx;
    lbl_3_bss_B860[10] = hy;
    PSMTXInverse((void*)((u8*)fn_80052768_getCamera(0) + 0x40), m);
    m[2][1] = lbl_3_rodata_3934[0];
    m[1][2] = lbl_3_rodata_3934[0];
    m[1][0] = lbl_3_rodata_3934[0];
    m[0][1] = lbl_3_rodata_3934[0];
    m[1][1] = lbl_3_rodata_392C;
    v.x = *(f32*)(b + 4);
    v.y = *(f32*)(b + 8);
    v.z = *(f32*)(b + 0xC);
    PSMTXMultVecSR(m, &v, &v);
    c.type = 0;
    CTRLSetRotation(&c, *(f32*)(b + 0x1C), *(f32*)(b + 0x20), *(f32*)(b + 0x24));
    CTRLSetTranslation(&c, *(f32*)(t + 0x34) + v.x, -*(f32*)(t + 0x38) + v.y, *(f32*)(t + 0x3C) + v.z);
    CTRLBuildMatrix(&c, m);
    PSMTXConcat((void*)((u8*)fn_80052768_getCamera(0) + 0x40), m, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
}

// .text:0x001483D4 size:0x48 mapped:0x80787468
u8 fn_3_1483D4(void) {
    return rand() % 5 == 0;
}

// .text:0x0014841C size:0xAD4 mapped:0x807874B0
void fn_3_14841C(void) {
    return;
}

// .text:0x00148EF0 size:0xE0 mapped:0x80787F84
void fn_3_148EF0(u8* o, f32 ang) {
    f32 s;
    f32 a;
    f32 c;
    a = lbl_3_rodata_39B8 * ang;
    s = (f32)sin(a);
    c = (f32)cos(a);
    *(f32*)(o + 0x10) = s * (f32)*(s32*)(lbl_3_data_26E7C + 4) / lbl_3_rodata_3930;
    *(f32*)(o + 0x14) = c * (f32)*(s32*)(lbl_3_data_26E7C + 4) / lbl_3_rodata_3930;
    *(f32*)(o + 0x18) = 0.0f;
}

// .text:0x00148FD0 size:0x370 mapped:0x80788064
void fn_3_148FD0(void) {
    return;
}

// .text:0x00149340 size:0x41C mapped:0x807883D4
void fn_3_149340(void) {
    return;
}

// .text:0x0014975C size:0x44C mapped:0x807887F0
void fn_3_14975C(void) {
    return;
}

// .text:0x00149BA8 size:0x4C8 mapped:0x80788C3C
void fn_3_149BA8(void) {
    return;
}

// .text:0x0014A070 size:0xF4 mapped:0x80789104
void fn_3_14A070(s32* src, s32 n) {
    u32 i;
    lbl_3_bss_B85C[0] = -1;
    lbl_3_bss_B85C[1] = -1;
    lbl_3_bss_B85C[2] = -1;
    lbl_3_bss_B85C[3] = -1;
    if (n > 4 || n == 0 || src == NULL) { return; }
    for (i = 0; i < (u32)n; i++) { lbl_3_bss_B85C[i] = src[i]; }
}

// .text:0x0014A164 size:0x24 mapped:0x807891F8
void fn_3_14A164(void) {
    pitchingMachinePitching(0x24);
}

// 99%: only the flag base addr is addi r3 (orig: lis/addi r4 before stmw); computing delta after df in the else branch fixed the float regs
// .text:0x0014A188 size:0x1F4 mapped:0x8078921C
u32 fn_3_14A188(u8* o) {
    u8* p;
    u8* d;
    s32 a;
    s32 alive = 0;
    s32 delta;
    f32 df;
    f32 q;
    s32 s;
    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    fn_80033620();
    p = *(u8**)(o + 0xC);
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    d = lbl_3_data_26E40;
    do {
        if (*(s16*)(p + 0x4A) != 0) {
            a = p[0x43];
            fn_80033F64(*(f32*)(p + 0x38), *(f32*)(p + 0x3C), *(f32*)(p + 0x10));
            fn_80033CC8(p, *(void**)(o + 0x10));
            if (*(s32*)(d + 8) - *(s16*)(p + 0x4A) < *(s32*)(d + 0x10)) {
                df = (*(f32*)(p + 0x18) - (f32)*(s32*)(d + 0x14) / lbl_3_rodata_3930) / (f32)*(s32*)(d + 0x10);
                delta = (*(s32*)(d + 0x28) - *(s32*)(d + 0x24)) / *(s32*)(d + 0x10);
            } else {
                s = *(s32*)(d + 8) - *(s32*)(d + 0x10);
                q = (f32)*(s32*)(d + 0x20) / lbl_3_rodata_3930;
                df = q + *(f32*)(p + 0x18);
                df /= (f32)s;
                delta = (*(s32*)(d + 0x2C) - *(s32*)(d + 0x28)) / s;
            }
            a += delta;
            if (a < 0) {
                a = 0;
            }
            if (a > 0xFF) {
                a = 0xFF;
            }
            p[0x43] = a;
            *(f32*)(p + 0x38) = *(f32*)(p + 0x38) + df;
            *(f32*)(p + 0x3C) = *(f32*)(p + 0x38);
            *(f32*)(p + 0x10) = *(f32*)(p + 0x10) + *(f32*)(p + 0x14);
            if ((*(s16*)(p + 0x4A) = *(s16*)(p + 0x4A) - 1) != 0) {
                alive++;
            }
        }
        p = *(u8**)p;
    } while (p != NULL);
    return alive == 0;
}

// .text:0x0014A37C size:0x2B0 mapped:0x80789410
void fn_3_14A37C(u8* o, f32* v) {
    u8* p;
    u8* d;
    s32 i;
    f32 ang;
    f32 c;
    *(s32*)(o + 0x10) = *(s32*)(lbl_3_common_bss_32724 + 0x6C);
    p = *(u8**)(o + 0xC);
    d = lbl_3_data_26E40;
    i = 0;
    do {
        p[0x4D] = *(s32*)d;
        p[0x4E] = 0;
        *(s16*)(p + 0x4A) = *(s32*)(d + 8);
        *(s16*)(p + 0x48) = 0;
        *(f32*)(p + 4) = v[0];
        *(f32*)(p + 8) = -v[1];
        *(f32*)(p + 0xC) = v[2];
        ang = (f32)(u32)(0x168 / *(s32*)(d + 4) * i);
        ang = lbl_3_rodata_39B8 * ang;
        c = (f32)cos(ang);
        *(f32*)(p + 4) = *(f32*)(p + 4) + (f32)*(s32*)(d + 0xC) * c / lbl_3_rodata_3930;
        c = (f32)sin(ang);
        *(f32*)(p + 8) = *(f32*)(p + 8) + (f32)*(s32*)(d + 0xC) * c / lbl_3_rodata_3930;
        *(f32*)(p + 0x38) = *(f32*)(p + 0x3C) = (f32)*(s32*)(d + 0x14) / lbl_3_rodata_3930;
        p[0x42] = 0xFF;
        p[0x41] = 0xFF;
        p[0x40] = 0xFF;
        p[0x43] = *(s32*)(d + 0x24);
        *(f32*)(p + 0x10) = lbl_3_rodata_3934[0];
        *(f32*)(p + 0x14) = (f32)(*(s32*)(d + 0x30) - rand() % *(s32*)(d + 0x34));
        *(f32*)(p + 0x14) = *(f32*)(p + 0x14) / lbl_3_rodata_3930;
        *(f32*)(p + 0x14) = *(f32*)(p + 0x14) * (f32)(-(rand() % 2 * 2) + 1);
        *(f32*)(p + 0x18) = (f32)(*(s32*)(d + 0x18) - rand() % *(s32*)(d + 0x1C));
        *(f32*)(p + 0x18) = *(f32*)(p + 0x18) / lbl_3_rodata_3930;
        i++;
        p = *(u8**)p;
    } while (p != NULL);
}

// .text:0x0014A62C size:0x2E0 mapped:0x807896C0
void fn_3_14A62C(void) {
    return;
}

// .text:0x0014A90C size:0x310 mapped:0x807899A0
void fn_3_14A90C(void) {
    return;
}

// .text:0x0014AC1C size:0x24 mapped:0x80789CB0
void fn_3_14AC1C(void) {
    pitchingMachinePitching(0x23);
}

// .text:0x0014AC40 size:0x608 mapped:0x80789CD4
void fn_3_14AC40(void) {
    return;
}

// .text:0x0014B248 size:0x1AC mapped:0x8078A2DC
void fn_3_14B248(u8* a, u8* b) {
    f32 c;
    f32 sn;
    f32 ang;
    f32 r;
    f32 d;
    f32 px;
    f32 py;
    d = (f32)*(s32*)(lbl_3_data_26E24 + 0xC) / lbl_3_rodata_3930;
    *(f32*)(b + 0x3C) = d;
    *(f32*)(b + 0x38) = d;
    b[0x43] = *(s32*)(lbl_3_data_26E24 + 0x14);
    ang = lbl_3_rodata_39B8 * (f32)(rand() % 360);
    r = (f32)((f64)((u32)rand() % 200) / lbl_3_rodata_39C8);
    c = (f32)cos(ang);
    px = r * c;
    sn = (f32)sin(ang);
    py = r * sn;
    *(f32*)(b + 4) = *(f32*)(a + 0x24) + px;
    *(f32*)(b + 8) = *(f32*)(a + 0x28) + py;
    *(f32*)(b + 0xC) = *(f32*)(a + 0x2C) + lbl_3_rodata_3934[0];
    *(s16*)(b + 0x4A) = *(s32*)(lbl_3_data_26E24 + 4);
}

// .text:0x0014B3F4 size:0x148 mapped:0x8078A488
void fn_3_14B3F4(u8* a) {
    f32* p;
    f32* q;
    f32 t;
    f32 s;
    s32 d = *(s16*)(a + 0x34) - *(s16*)(a + 0x36);
    f32 len = *(f32*)(a + 0x30);
    if ((f32)d < len) {
        p = (f32*)lbl_3_data_26E00;
        q = (f32*)(lbl_3_data_26E00 + 0xC);
        t = (f32)d / len;
    } else {
        p = (f32*)(lbl_3_data_26E00 + 0xC);
        q = (f32*)(lbl_3_data_26E00 + 0x18);
        t = (f32)d / ((f32)*(s16*)(a + 0x34) - len);
    }
    s = fn_3_119D28();
    *(f32*)(a + 0x24) = s * (p[0] * (1.0f - t) + q[0] * t) + *(f32*)(a + 0x18);
    *(f32*)(a + 0x28) = s * (p[1] * (1.0f - t) + q[1] * t) + *(f32*)(a + 0x1C);
    *(f32*)(a + 0x2C) = s * (p[2] * (1.0f - t) + q[2] * t) + *(f32*)(a + 0x20);
}

// .text:0x0014B53C size:0x3F0 mapped:0x8078A5D0
void fn_3_14B53C(void* p, u32 a, u32 b) {
    return;
}

// .text:0x0014B92C size:0x74 mapped:0x8078A9C0
void fn_3_14B92C(u32 a, u32 b) {
    void* p = fn_80033A24(fn_3_14AC40, 0x80, 0, *(int*)(lbl_3_data_26E24 + 8), 1, 0x23);
    if (p != 0) {
        fn_3_14B53C(p, a, b);
    }
}

// .text:0x0014B9A0 size:0x50 mapped:0x8078AA34
void fn_3_14B9A0(u32 a, u32 b) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame[0x1A2A] == 3 && b != 0) {
        fn_3_14B92C(a, b);
    }
}

// .text:0x0014B9F0 size:0x50 mapped:0x8078AA84
void fn_3_14B9F0(void) {
    u8* p = fn_800339F0(0, 0x22);
    if (p != NULL) {
        p = *(u8**)(p + 0xC);
        do {
            *(s16*)(p + 0x4A) = 0;
            p = *(u8**)p;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x22);
}

// .text:0x0014BA40 size:0x270 mapped:0x8078AAD4
u32 fn_3_14BA40(u8* o) {
    s32 s;
    u8* d;
    u8* p;
    u8** pp;
    u8* first;
    u8* prev;
    s32 t26;
    s32 n;
    s32 a;
    s32 t23;
    u8* q;
    u8* t;
    s32 delta;
    f32 df;
    n = 0;
    if (lbl_80366158[0x28] != 0) {
        return 0;
    }
    t = fn_80031F34(*(void**)(o + 0xC), ((H154238*)o)->cnt);
    *(u8**)(o + 0xC) = t;
    p = t;
    pp = (u8**)(o + 0xC);
    prev = NULL;
    first = NULL;
    GXSetZMode(1, 3, 0);
    GXSetBlendMode(1, 4, 5, 0);
    do {
        if (*(s16*)(p + 0x4A) != 0) {
            if (p[0x4F] == 0) {
                d = lbl_3_data_26D88;
            } else {
                d = lbl_3_data_26DC4;
            }
            t23 = *(s32*)(d + 8);
            t26 = *(s32*)(d + 0xC);
            fn_8003403C(*(f32*)(p + 0x38), *(f32*)(p + 0x3C));
            fn_80033CC8(p, *(void**)(o + 0x10));
            a = p[0x43];
            if (t23 - *(s16*)(p + 0x4A) < t26) {
                df = (f32)((*(s32*)(d + 0x14) - *(s32*)(d + 0x10)) / t26) / lbl_3_rodata_3930;
                delta = (*(s32*)(d + 0x2C) - *(s32*)(d + 0x28)) / t26;
            } else {
                s = t23 - t26;
                df = (f32)((*(s32*)(d + 0x18) - *(s32*)(d + 0x14)) / s) / lbl_3_rodata_3930;
                delta = (*(s32*)(d + 0x30) - *(s32*)(d + 0x2C)) / s;
            }
            a += delta;
            if (a > 0xFF) {
                a = 0xFF;
            }
            if (a < 0) {
                a = 0;
            }
            p[0x43] = a;
            *(f32*)(p + 0x38) = *(f32*)(p + 0x38) + df;
            *(f32*)(p + 0x3C) = *(f32*)(p + 0x38);
            *(s16*)(p + 0x4A) -= 1;
            if (*(s16*)(p + 0x4A) == 0) {
                *pp = *(u8**)p;
                if (prev != NULL) {
                    *(u8**)prev = p;
                } else {
                    first = p;
                }
                prev = p;
                *(u8**)p = NULL;
                ((H154238*)o)->cnt--;
            } else {
                pp = (u8**)p;
                n++;
            }
        }
        p = *pp;
    } while (p != NULL);
    if (first != NULL) {
        q = first;
        do {
            q[0x4C] = 0;
            *(s16*)(q + 0x48) = 0;
            q = *(u8**)q;
        } while (q != NULL);
        fn_80033794(first);
    }
    return n == 0;
}

// .text:0x0014BCB0 size:0x21C mapped:0x8078AD44
void fn_3_14BCB0(u8* o, f32* v, u8 flag) {
    u8* p;
    u8* d;
    u32 n;
    f32 t;
    f32 ang;
    f32 s;
    f32 c;
    f32 r;
    f64 u;
    *(s32*)(o + 0x10) = *(s32*)(lbl_3_common_bss_32724 + 0x6C);
    n = 0;
    p = *(u8**)(o + 0xC);
    d = (flag != 0) ? lbl_3_data_26DC4 : lbl_3_data_26D88;
    do {
        if (*(s16*)(p + 0x4A) == 0) {
            p[0x4D] = *(s32*)d;
            p[0x4E] = 0;
            *(s16*)(p + 0x4A) = *(s32*)(d + 8);
            *(f32*)(p + 0x38) = *(f32*)(p + 0x3C) = (f32)*(s32*)(d + 0x10) / lbl_3_rodata_3930;
            p[0x43] = *(s32*)(d + 0x28);
            p[0x40] = *(s32*)(d + 0x1C);
            p[0x41] = *(s32*)(d + 0x20);
            p[0x42] = *(s32*)(d + 0x24);
            t = (f32)rand() / lbl_3_rodata_3970;
            u = (f64)t - lbl_3_rodata_3968;
            u = lbl_3_rodata_3990 * u;
            r = lbl_3_rodata_39C4 * u;
            ang = lbl_3_rodata_39B8 * (f32)(360.0 / (f64)*(s32*)(d + 4) * (f64)n);
            c = (f32)cos(ang);
            *(f32*)(p + 4) = r * c + v[0];
            s = (f32)sin(ang);
            n++;
            *(f32*)(p + 8) = (f32)((f64)(v[1] - r * s) - lbl_3_rodata_3978);
            *(f32*)(p + 0xC) = v[2];
            p[0x4F] = flag;
        }
        p = *(u8**)p;
    } while (p != NULL && n < *(u32*)(lbl_3_data_26D88 + 4));
}

// .text:0x0014BECC size:0x47C mapped:0x8078AF60
void fn_3_14BECC(u32 a, u32 b) {
    return;
}

// .text:0x0014C348 size:0x50 mapped:0x8078B3DC
void fn_3_14C348(u32 a, u32 b) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame[0x1A2A] == 2 && a != 0) {
        fn_3_14BECC(a, b);
    }
}

// .text:0x0014C398 size:0x24 mapped:0x8078B42C
void fn_3_14C398(void) {
    pitchingMachinePitching(0x21);
}

// .text:0x0014C3BC size:0x10C mapped:0x8078B450
void fn_3_14C3BC(u8* o) {
    Vec v;
    Mtx m;
    PSVECScale((Vec*)lbl_3_data_26D50, lbl_3_rodata_39E0, &v);
    PSMTXRotRad(m, 'Y', shortAngleToRad(*(s16*)(g_Minigame + 0x1AF8)));
    PSMTXMultVec(m, &v, &v);
    *(f32*)(o + 4) = *(f32*)(g_Minigame + 0x1AE0) + v.x + (f32)*(s32*)(lbl_3_data_26D5C + 0x14) / 100000.0f * lbl_3_rodata_39A8;
    *(f32*)(o + 8) = v.y - ((f32)*(s32*)(lbl_3_data_26D5C + 0x14) / 100000.0f * lbl_3_rodata_39A8 + *(f32*)(g_Minigame + 0x1AE4));
    *(f32*)(o + 0xC) = *(f32*)(g_Minigame + 0x1AE8) + v.z;
}

// .text:0x0014C4C8 size:0x2D4 mapped:0x8078B55C
void fn_3_14C4C8(void) {
    return;
}

// .text:0x0014C79C size:0x94 mapped:0x8078B830
void fn_3_14C79C(u8* a) {
    u8* p;
    f32 f;
    *(u32*)(a + 0x10) = *(u32*)(lbl_3_common_bss_32724 + 0x6C);
    p = *(u8**)(a + 0xC);
    p[0x4D] = *(u32*)lbl_3_data_26D5C;
    p[0x4E] = 0;
    *(s16*)(p + 0x4A) = *(s32*)(lbl_3_data_26D5C + 8);
    f = *(s32*)(lbl_3_data_26D5C + 0x10) / 100000.0f;
    *(f32*)(p + 0x3C) = f;
    *(f32*)(p + 0x38) = f;
    p[0x43] = *(s32*)(lbl_3_data_26D5C + 0x1C);
    p[0x42] = 0xFF;
    p[0x41] = 0xFF;
    p[0x40] = 0xFF;
}

// .text:0x0014C830 size:0xD4 mapped:0x8078B8C4
void fn_3_14C830(void) {
    u8* a = fn_80033A24(fn_3_14C4C8, 0x80, 0, *(int*)(lbl_3_data_26D5C + 4), 1, 0xA);
    u8* p;
    f32 f;
    if (a != NULL) {
        *(u32*)(a + 0x10) = *(u32*)(lbl_3_common_bss_32724 + 0x6C);
        p = *(u8**)(a + 0xC);
        p[0x4D] = *(u32*)lbl_3_data_26D5C;
        p[0x4E] = 0;
        *(s16*)(p + 0x4A) = *(s32*)(lbl_3_data_26D5C + 8);
        f = *(s32*)(lbl_3_data_26D5C + 0x10) / 100000.0f;
        *(f32*)(p + 0x3C) = f;
        *(f32*)(p + 0x38) = f;
        p[0x43] = *(s32*)(lbl_3_data_26D5C + 0x1C);
        p[0x42] = 0xFF;
        p[0x41] = 0xFF;
        p[0x40] = 0xFF;
    }
}

// .text:0x0014C904 size:0xFC mapped:0x8078B998
void fn_3_14C904(void) {
    u8* a;
    u8* p;
    f32 f;
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame[0x1A2A] == 4) {
        a = fn_80033A24(fn_3_14C4C8, 0x80, 0, *(int*)(lbl_3_data_26D5C + 4), 1, 0xA);
        if (a != NULL) {
            *(u32*)(a + 0x10) = *(u32*)(lbl_3_common_bss_32724 + 0x6C);
            p = *(u8**)(a + 0xC);
            p[0x4D] = *(u32*)lbl_3_data_26D5C;
            p[0x4E] = 0;
            *(s16*)(p + 0x4A) = *(s32*)(lbl_3_data_26D5C + 8);
            f = *(s32*)(lbl_3_data_26D5C + 0x10) / 100000.0f;
            *(f32*)(p + 0x3C) = f;
            *(f32*)(p + 0x38) = f;
            p[0x43] = *(s32*)(lbl_3_data_26D5C + 0x1C);
            p[0x42] = 0xFF;
            p[0x41] = 0xFF;
            p[0x40] = 0xFF;
        }
    }
}

// .text:0x0014CA00 size:0x98 mapped:0x8078BA94
void fn_3_14CA00(void) {
    u32 i = 0;
    do {
        u8* h = (u8*)fn_800339F0(0, 0x20);
        if (h != 0) {
            u8* n = *(u8**)(h + 0xC);
            do {
                if (n[0x45] == (s8)i) {
                    n[0x44] = 0;
                    n[0x45] = 0xFF;
                    *(s16*)(n + 0x4A) = 0;
                    n[0x4C] = 0;
                }
                n = *(u8**)n;
            } while (n != 0);
        }
        i++;
    } while (i < 0xF);
    pitchingMachinePitching(0x20);
}

// .text:0x0014CA98 size:0x1C mapped:0x8078BB2C
void fn_3_14CA98(u8* p) {
    p[0x44] = 0;
    p[0x45] = 0xFF;
    *(s16*)(p + 0x4A) = 0;
    p[0x4C] = 0;
}

// .text:0x0014CAB4 size:0x74 mapped:0x8078BB48
void fn_3_14CAB4(s8 a) {
    u8* p = fn_800339F0(0, 0x20);
    if (p != NULL) {
        u8* q = *(u8**)(p + 0xC);
        do {
            if (q[0x45] == a) {
                q[0x44] = 0;
                q[0x45] = 0xFF;
                *(s16*)(q + 0x4A) = 0;
                q[0x4C] = 0;
            }
            q = *(u8**)q;
        } while (q != NULL);
    }
}

// .text:0x0014CB28 size:0x8C mapped:0x8078BBBC
void fn_3_14CB28(s8 a) {
    u8* p; s32 id;
    if (a >= 0xF || a < 0) {
        return;
    }
    p = fn_800339F0(0, 0x20);
    if (p != NULL) {
        p = *(u8**)(p + 0xC);
        id = a;
        do {
            if (p[0x45] == id) {
                p[0x44] = 0;
                p[0x45] = 0xFF;
                *(s16*)(p + 0x4A) = 0;
                p[0x4C] = 0;
            }
            p = *(u8**)p;
        } while (p != NULL);
    }
}

// .text:0x0014CBB4 size:0x18C mapped:0x8078BC48
void fn_3_14CBB4(u8* a, u8* o) {
    s32 delta;
    f32 df;
    s32 c;
    GXSetBlendMode(1, 4, 5, 0);
    fn_8003403C(*(f32*)(o + 0x38), *(f32*)(o + 0x3C));
    fn_80033CC8(o, *(void**)(a + 0x10));
    c = o[0x43];
    if (-*(s16*)(o + 0x48) < lbl_3_data_26D00[10]) {
        df = ((f32)lbl_3_data_26D00[12] / lbl_3_rodata_3930) / (f32)lbl_3_data_26D00[10];
        delta = lbl_3_data_26D00[15] / lbl_3_data_26D00[10];
    } else {
        df = ((f32)(lbl_3_data_26D00[13] - lbl_3_data_26D00[12]) / lbl_3_rodata_3930) / (f32)(lbl_3_data_26D00[18] - lbl_3_data_26D00[10]);
        delta = (lbl_3_data_26D00[16] - lbl_3_data_26D00[15]) / (lbl_3_data_26D00[18] - lbl_3_data_26D00[10]);
    }
    c += delta;
    if (c > 0xFF) {
        c = 0xFF;
    } else if (c < 0) {
        c = 0;
    }
    o[0x43] = c;
    o[0x40] = o[0x41] = o[0x42] = o[0x43];
    *(f32*)(o + 0x38) = *(f32*)(o + 0x38) + df;
    *(f32*)(o + 0x3C) = *(f32*)(o + 0x38);
}

// .text:0x0014CD40 size:0x18C mapped:0x8078BDD4
void fn_3_14CD40(u8* a, u8* o) {
    s32 delta;
    f32 df;
    s32 c;
    GXSetBlendMode(1, 1, 1, 0);
    fn_8003403C(*(f32*)(o + 0x38), *(f32*)(o + 0x3C));
    fn_80033CC8(o, *(void**)(a + 0x10));
    c = o[0x43];
    if (-*(s16*)(o + 0x48) < lbl_3_data_26D00[3]) {
        df = ((f32)lbl_3_data_26D00[5] / lbl_3_rodata_3930) / (f32)lbl_3_data_26D00[3];
        delta = lbl_3_data_26D00[8] / lbl_3_data_26D00[3];
    } else {
        df = ((f32)(lbl_3_data_26D00[6] - lbl_3_data_26D00[5]) / lbl_3_rodata_3930) / (f32)(lbl_3_data_26D00[17] - lbl_3_data_26D00[3]);
        delta = (lbl_3_data_26D00[9] - lbl_3_data_26D00[8]) / (lbl_3_data_26D00[17] - lbl_3_data_26D00[3]);
    }
    c += delta;
    if (c > 0xFF) {
        c = 0xFF;
    } else if (c < 0) {
        c = 0;
    }
    o[0x43] = c;
    o[0x40] = o[0x41] = o[0x42] = o[0x43];
    *(f32*)(o + 0x38) = *(f32*)(o + 0x38) + df;
    *(f32*)(o + 0x3C) = *(f32*)(o + 0x38);
}

// .text:0x0014CECC size:0x3F4 mapped:0x8078BF60
void fn_3_14CECC(void) {
    return;
}

// .text:0x0014D2C0 size:0x58 mapped:0x8078C354
void fn_3_14D2C0(u8* p) {
    u8** arr = *(u8***)(*(u8**)(lbl_8036E548 + 0x68) + (p[0x45] + 0x10) * 0x90 + 0x34);
    u8* e;
    arr = *(u8***)((u8*)arr + 0x18);
    e = arr[p[0x46]];
    *(f32*)(p + 4) = *(f32*)(*(u8**)(e + 0xEC) + 0xC);
    *(f32*)(p + 8) = *(f32*)(*(u8**)(e + 0xEC) + 0x1C);
    *(f32*)(p + 0xC) = *(f32*)(*(u8**)(e + 0xEC) + 0x2C);
}

// .text:0x0014D318 size:0x134 mapped:0x8078C3AC
void fn_3_14D318(u8* a) {
    f32* q = (f32*)(g_Minigame + a[0x45] * 0x34 + 0x860);
    f32* d = (f32*)lbl_3_data_21770; f32 h = 0.5f;
    *(f32*)(a + 4) = q[0];
    *(f32*)(a + 8) = -(d[3] * h + q[1]);
    *(f32*)(a + 0xC) = q[2];
    *(f32*)(a + 4) = *(f32*)(a + 4) + (rand() % 100 - 50) / 100.0;
    *(f32*)(a + 8) = *(f32*)(a + 8) + (rand() % 100 - 50) / 100.0;
}

// .text:0x0014D44C size:0x288 mapped:0x8078C4E0
void fn_3_14D44C(u8* a, u32 kind0) {
    u8 kind = kind0;
    u8* p = *(u8**)(a + 0xC);
    s32 n = 0;
    do {
        if (p[0x44] == 0 && *(s16*)(p + 0x4A) == 0) {
            if (n < 3) {
                f32* d = (f32*)lbl_3_data_21770;
                f32* q;
                f32 h = 0.5f;
                p[0x44] = 1;
                p[0x45] = kind;
                p[0x46] = 0xFF;
                p[0x4D] = lbl_3_data_26D00[0];
                *(f32*)(p + 0x38) = *(f32*)(p + 0x3C) = (f32)lbl_3_data_26D00[4];
                p[0x43] = lbl_3_data_26D00[7];
                q = (f32*)(g_Minigame + p[0x45] * 0x34 + 0x860);
                *(f32*)(p + 4) = q[0];
                *(f32*)(p + 8) = -(d[3] * h + q[1]);
                *(f32*)(p + 0xC) = q[2];
                *(f32*)(p + 4) = *(f32*)(p + 4) + (rand() % 100 - 50) / 100.0;
                *(f32*)(p + 8) = *(f32*)(p + 8) + (rand() % 100 - 50) / 100.0;
                *(s16*)(p + 0x4A) = lbl_3_data_26D00[17];
                *(s16*)(p + 0x48) = 0;
            } else {
                p[0x44] = 2;
                p[0x45] = kind;
                p[0x46] = (n - 3) / 5;
                p[0x4D] = lbl_3_data_26D00[1];
                *(f32*)(p + 0x38) = *(f32*)(p + 0x3C) = (f32)lbl_3_data_26D00[11];
                p[0x43] = lbl_3_data_26D00[14];
                *(s16*)(p + 0x48) = (n - 3) % 5 * 4 + 1;
                *(s16*)(p + 0x4A) = lbl_3_data_26D00[18];
            }
            n++;
            p[0x40] = p[0x41] = p[0x42] = 0xFF;
        }
        p = *(u8**)p;
    } while (p != NULL && n < 0x2B);
}

// .text:0x0014D6D4 size:0x3C mapped:0x8078C768

void fn_3_14D6D4(u8* p) {
    *(u32*)(p + 0x10) = *(u32*)(lbl_3_common_bss_32724 + 0x6C);
    p = *(u8**)(p + 0xC);
    do {
        p[0x46] = 0;
        p[0x45] = 0;
        p[0x44] = 0;
        *(s16*)(p + 0x4A) = 0;
        p[0x4E] = 0;
        p = *(u8**)p;
    } while (p != NULL);
}

// .text:0x0014D710 size:0x570 mapped:0x8078C7A4
void fn_3_14D710(s8 a) {
    return;
}

// .text:0x0014DC80 size:0x60 mapped:0x8078CD14
void fn_3_14DC80(s8 a) {
    if (g_d_GameSettings.GameModeSelected != 7 || g_Minigame[0x1A2A] != 3 || a >= 0xF || a < 0) {
        return;
    }
    fn_3_14D710(a);
}

// .text:0x0014DCE0 size:0x24 mapped:0x8078CD74
void fn_3_14DCE0(void) {
    pitchingMachinePitching(0x1F);
}

// .text:0x0014DD04 size:0x268 mapped:0x8078CD98
u32 fn_3_14DD04(u8* o) {
    u8* t;
    u8* d;
    u8* p;
    u8** pp;
    u8* prev;
    s32 n;
    s32 a;
    s32 t8;
    s32 delta;
    f32 df;
    n = 0;
    t = fn_80031F34(*(void**)(o + 0xC), ((H154238*)o)->cnt);
    *(u8**)(o + 0xC) = t;
    p = t;
    pp = (u8**)(o + 0xC);
    prev = NULL;
    GXSetZMode(1, 3, 1);
    GXSetBlendMode(1, 4, 6, 0);
    d = lbl_3_data_26CD0;
    do {
        if (*(s16*)(p + 0x4A) != 0) {
            fn_8003403C(*(f32*)(p + 0x38), *(f32*)(p + 0x3C));
            fn_80033CC8(p, *(void**)(o + 0x10));
            *(f32*)(p + 8) = *(f32*)(p + 8) - *(f32*)(p + 0x14);
            *(f32*)(p + 0x14) = *(f32*)(p + 0x14) - (f32)*(s32*)(d + 0x28) / lbl_3_rodata_3930;
            a = p[0x43];
            t8 = *(s32*)(d + 8);
            if (t8 / *(s16*)(p + 0x4A) < 2) {
                df = *(f32*)(p + 0x1C) * ((f32)(*(s32*)(d + 0x10) - *(s32*)(d + 0xC)) / lbl_3_rodata_3930 / (f32)(t8 / 2));
                delta = (*(s32*)(d + 0x1C) - *(s32*)(d + 0x18)) / (t8 / 2);
            } else {
                df = *(f32*)(p + 0x1C) * ((f32)(*(s32*)(d + 0x14) - *(s32*)(d + 0x10)) / lbl_3_rodata_3930 / (f32)(t8 / 2));
                delta = (*(s32*)(d + 0x20) - *(s32*)(d + 0x1C)) / (t8 / 2);
            }
            a += delta;
            *(f32*)(p + 0x38) = *(f32*)(p + 0x38) + df;
            *(f32*)(p + 0x3C) = *(f32*)(p + 0x38);
            if (a < 0) {
                a = 0;
            } else if (a > 0xFF) {
                a = 0xFF;
            }
            p[0x43] = a;
            *(s16*)(p + 0x4A) -= 1;
            if (*(s16*)(p + 0x4A) == 0) {
                *pp = *(u8**)p;
                if (prev != NULL) {
                    *(u8**)prev = p;
                }
                prev = p;
                *(u8**)p = NULL;
                ((H154238*)o)->cnt--;
            } else {
                pp = (u8**)p;
                n++;
            }
        }
        p = *pp;
    } while (p != NULL);
    return n == 0;
}

// .text:0x0014DF6C size:0x2C8 mapped:0x8078D000
void fn_3_14DF6C(void) {
    return;
}

// .text:0x0014E234 size:0x58C mapped:0x8078D2C8
void fn_3_14E234(u32 a) {
    return;
}

// .text:0x0014E7C0 size:0x50 mapped:0x8078D854
void fn_3_14E7C0(u32 a) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame[0x1A2A] == 6 && a != 0) {
        fn_3_14E234(a);
    }
}

// .text:0x0014E810 size:0x84 mapped:0x8078D8A4
void fn_3_14E810(void) {
    u32 i = 0;
    do {
        u8* p = fn_800339F0(0, 0x1E);
        if (p != NULL) {
            u8* q = *(u8**)(p + 0xC);
            s32 v = (s8)i + 1;
            do {
                if (q[0x4C] == v) {
                    *(s16*)(q + 0x4A) = 0;
                }
                q = *(u8**)q;
            } while (q != NULL);
        }
        i++;
    } while (i < 4);
    pitchingMachinePitching(0x1E);
}

// .text:0x0014E894 size:0x8C mapped:0x8078D928
// 99%: orig has `li r30,0; mr r31,r30` for zero store reg (li r31 instead)
void fn_3_14E894(void) {
    u32 i = 0;
    s16 z = 0;
    do {
        s8 k = i;
        u8* p = fn_800339F0(0, 0x1E);
        if (p != NULL) {
            u8* q = *(u8**)(p + 0xC);
            s32 v = k + 1;
            do {
                if (q[0x4C] == v) {
                    *(s16*)(q + 0x4A) = z;
                }
                q = *(u8**)q;
            } while (q != NULL);
        }
        i++;
    } while (i < 4);
    pitchingMachinePitching(0x1E);
}

// .text:0x0014E920 size:0x68 mapped:0x8078D9B4
void fn_3_14E920(s8 a) {
    u8* p = fn_800339F0(0, 0x1E);
    if (p != NULL) {
        u8* q = *(u8**)(p + 0xC);
        s32 v = a + 1;
        do {
            if (q[0x4C] == v) {
                *(s16*)(q + 0x4A) = 0;
            }
            q = *(u8**)q;
        } while (q != NULL);
    }
}

// .text:0x0014E988 size:0x68 mapped:0x8078DA1C
void fn_3_14E988(s8 a) {
    u8* p = fn_800339F0(0, 0x1E);
    if (p != NULL) {
        u8* q = *(u8**)(p + 0xC);
        s32 v = a + 1;
        do {
            if (q[0x4C] == v) {
                *(s16*)(q + 0x4A) = 0;
            }
            q = *(u8**)q;
        } while (q != NULL);
    }
}

// .text:0x0014E9F0 size:0x104 mapped:0x8078DA84
void fn_3_14E9F0(u8* a) {
    Vec v;
    if (a[0x4C] < 5) {
        u8 k = lbl_3_data_26CB8[(u32)rand() % 23];
        v.z = 0.0f;
        v.y = 0.0f;
        v.x = 0.0f;
        if (fn_8001B728(a[0x4C] - 1, k, &v) == 0) {
            memset(&v, 0, 0xC);
            fn_8001B728(a[0x4C] - 1, 4, &v);
        }
    } else {
        v.x = *(f32*)(g_Minigame + 0x6E8);
        v.y = -*(f32*)(g_Minigame + 0x6EC);
        v.z = *(f32*)(g_Minigame + 0x6F0);
    }
    *(f32*)(a + 4) += v.x;
    *(f32*)(a + 8) += v.y;
    *(f32*)(a + 0xC) += v.z;
}

// .text:0x0014EAF4 size:0x230 mapped:0x8078DB88
void fn_3_14EAF4(u8* o) {
    Vec v = lbl_3_rodata_3914;
    Vec w;
    if (o[0x4C] == 5) {
        v.x += (f32)(rand() % 10000 - 5000) / lbl_3_rodata_39F4;
        v.y += (f32)(rand() % 10000 - 5000) / lbl_3_rodata_39F4;
        *(f32*)(o + 4) = v.x;
        *(f32*)(o + 8) = v.y - lbl_3_rodata_39A8;
        *(f32*)(o + 0xC) = v.z;
    } else {
        *(f32*)(o + 0xC) = lbl_3_rodata_3934[0];
        *(f32*)(o + 8) = lbl_3_rodata_3934[0];
        *(f32*)(o + 4) = lbl_3_rodata_3934[0];
    }
    if (o[0x4C] < 5) {
        u8 k = lbl_3_data_26CB8[(u32)rand() % 23];
        w.z = 0.0f;
        w.y = 0.0f;
        w.x = 0.0f;
        if (fn_8001B728(o[0x4C] - 1, k, &w) == 0) {
            memset(&w, 0, 0xC);
            fn_8001B728(o[0x4C] - 1, 4, &w);
        }
    } else {
        w.x = *(f32*)(g_Minigame + 0x6E8);
        w.y = -*(f32*)(g_Minigame + 0x6EC);
        w.z = *(f32*)(g_Minigame + 0x6F0);
    }
    *(f32*)(o + 4) += w.x;
    *(f32*)(o + 8) += w.y;
    *(f32*)(o + 0xC) += w.z;
}

// .text:0x0014ED24 size:0x6A8 mapped:0x8078DDB8
void fn_3_14ED24(void) {
    return;
}

// .text:0x0014F3CC size:0x178 mapped:0x8078E460
void fn_3_14F3CC(u8* o) {
    Vec v = lbl_3_rodata_3908;
    f32 off;
    s16 r1, r2;
    if (o[0x4C] < 5) {
        off = lbl_3_rodata_39F8;
    } else {
        off = lbl_3_rodata_39A8;
    }
    r1 = o[0x4C] < 5 ? 20000 : 10000;
    r2 = o[0x4C] < 5 ? 20000 : 10000;
    v.x += (f32)(rand() % r1 - r1 / 2) / lbl_3_rodata_39F4;
    v.y += (f32)(rand() % r2 - r2 / 2) / lbl_3_rodata_39F4;
    *(f32*)(o + 4) = v.x;
    *(f32*)(o + 8) = v.y - off;
    *(f32*)(o + 0xC) = v.z;
}

// .text:0x0014F544 size:0x60 mapped:0x8078E5D8
void fn_3_14F544(u8* a) {
    f32 f;
    *(s16*)(a + 0x4A) = *(s32*)(lbl_3_data_26C94 + 0x1C);
    a[0x43] = *(s32*)(lbl_3_data_26C94 + 0x14);
    f = *(s32*)(lbl_3_data_26C94 + 8) / 100000.0f;
    *(f32*)(a + 0x3C) = f;
    *(f32*)(a + 0x38) = f;
}

// .text:0x0014F5A4 size:0x32C mapped:0x8078E638
void fn_3_14F5A4(void) {
    return;
}

// .text:0x0014F8D0 size:0x60 mapped:0x8078E964
void fn_3_14F8D0(u8* a) {
    u8* p;
    u32 i = 0;
    *(u32*)(a + 0x10) = *(u32*)(lbl_3_common_bss_32724 + 0x6C);
    p = *(u8**)(a + 0xC);
    do {
        p[0x4F] = 0;
        p[0x4D] = *(u32*)lbl_3_data_26C94;
        p[0x4E] = 0;
        p[0x4C] = i / 18 + 1;
        i++;
        p = *(u8**)p;
    } while (p != NULL);
}

// .text:0x0014F930 size:0x6E0 mapped:0x8078E9C4
void fn_3_14F930(s8 a) {
    return;
}

// .text:0x00150010 size:0x60 mapped:0x8078F0A4
void fn_3_150010(s8 a) {
    if (g_d_GameSettings.GameModeSelected != 7 || g_Minigame[0x1A2A] != 6 || a > 4 || a < 0) { return; }
    fn_3_14F930(a);
}

// .text:0x00150070 size:0x58 mapped:0x8078F104
void fn_3_150070(void) {
    u8* p = fn_800339F0(0, 0x1D);
    if (p != NULL) {
        p = *(u8**)(p + 0xC);
        do {
            *(s16*)(p + 0x4A) = 0;
            *(s16*)(p + 0x48) = 0;
            p[0x4C] = 0;
            p = *(u8**)p;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x001500C8 size:0x58 mapped:0x8078F15C
void fn_3_1500C8(void) {
    u8* p = fn_800339F0(0, 0x1D);
    if (p != NULL) {
        p = *(u8**)(p + 0xC);
        do {
            *(s16*)(p + 0x4A) = 0;
            *(s16*)(p + 0x48) = 0;
            p[0x4C] = 0;
            p = *(u8**)p;
        } while (p != NULL);
    }
    pitchingMachinePitching(0x1D);
}

// .text:0x00150120 size:0x3CC mapped:0x8078F1B4
void fn_3_150120(void) {
    return;
}

// .text:0x001504EC size:0x454 mapped:0x8078F580
void fn_3_1504EC(void) {
    return;
}

// .text:0x00150940 size:0x444 mapped:0x8078F9D4
void fn_3_150940(void) {
    return;
}

// .text:0x00150D84 size:0x2E4 mapped:0x8078FE18
void fn_3_150D84(void) {
    return;
}

// .text:0x00151068 size:0x19C mapped:0x807900FC
void fn_3_151068(u8* a, u8* o) {
    Mtx m;
    u8* obj;
    u8* mp;
    u8* t;
    f32 x, y, z;
    s32* d = (s32*)lbl_3_data_26C3C;
    *(s16*)(o + 0x4A) = d[6];
    obj = (*(u8***)(*(u8**)(*(u8**)(a + 0x18))+0x18))[d[7]];
    PSMTXIdentity(m);
    mp = *(u8**)(obj + 0xEC);
    x = *(f32*)(mp + 0xC);
    y = *(f32*)(mp + 0x1C);
    z = *(f32*)(mp + 0x2C);
    x += (f64)(rand() % 100 - 50) / lbl_3_rodata_39E8;
    y += (f64)(rand() % 150 - 75) / lbl_3_rodata_39E8;
    *(f32*)(o + 4) = x;
    *(f32*)(o + 8) = y;
    *(f32*)(o + 0xC) = z;
    *(f32*)(o + 0x3C) = *(f32*)(o + 0x38) = *(s32*)(lbl_3_data_26C3C + 8);
    o[0x43] = *(s32*)(lbl_3_data_26C3C + 0x10);
}

// .text:0x00151204 size:0x490 mapped:0x80790298
void fn_3_151204(void* p, u32 a, u32 b) {
    return;
}

// .text:0x00151694 size:0x7C mapped:0x80790728
void fn_3_151694(u32 a, u32 b) {
    void* p = fn_80033A24(fn_3_150940, 0x80, 0, *(int*)(lbl_3_data_26C3C + 4) + *(int*)(lbl_3_data_26C3C + 0x24), 1, 0x1D);
    if (p != 0) {
        fn_3_151204(p, a, b);
    }
}

// .text:0x00151710 size:0x50 mapped:0x807907A4
void fn_3_151710(u32 a, u32 b) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame[0x1A2A] == 2 && a != 0) {
        fn_3_151694(a, b);
    }
}

// .text:0x00151760 size:0x38 mapped:0x807907F4
void fn_3_151760(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x00151798 size:0x38 mapped:0x8079082C
void fn_3_151798(void) {
    memset(lbl_3_bss_B894, 0, 0xF);
    pitchingMachinePitching(0x1C);
}

// .text:0x001517D0 size:0x228 mapped:0x80790864
void fn_3_1517D0(u8* a, u8* o) {
    return;
}

// .text:0x001519F8 size:0x1B4 mapped:0x80790A8C
void fn_3_1519F8(u8* a, u8* o) {
    Vec v;
    Vec dir;
    Vec ref;
    f32 mag;
    u8* tbl;
    fn_3_1517D0(o, a);
    if (lbl_80366158[0x28] != 0) {
        return;
    }
    PSVECAdd((Vec*)(o + 4), (Vec*)(o + 0x10), (Vec*)(o + 4));
    memcpy(&v, o + 4, 0xC);
    tbl = lbl_3_data_26C1C + 4;
    v.x = *(f32*)(lbl_3_data_26C1C + o[0x44] * 8) - v.x;
    v.y = *(f32*)(tbl + o[0x44] * 8) - v.y;
    v.z = lbl_3_rodata_3934[0];
    PSVECNormalize(&v, &dir);
    mag = PSVECMag(&v);
    PSVECScale(&dir, lbl_3_rodata_3A00 * (lbl_3_rodata_392C / (mag * mag)), &v);
    PSVECAdd((Vec*)(o + 0x10), &v, (Vec*)(o + 0x10));
    ref.x = *(f32*)(lbl_3_data_26C1C + o[0x44] * 8);
    ref.y = *(f32*)(tbl + o[0x44] * 8);
    ref.z = lbl_3_rodata_3934[0];
    PSVECNormalize(&ref, &ref);
    if (PSVECDotProduct(&dir, &ref) < lbl_3_rodata_3934[0] || mag == lbl_3_rodata_3934[0]) {
        *(s16*)(o + 0x4A) = 0;
    }
    if (*(s16*)(o + 0x4A) == 0 && o[0x45] != 0) {
        fn_3_11F4B4(o[0x44], o[0x4D] == 1);
        o[0x45] = 0;
    }
}

// .text:0x00151BAC size:0x1C0 mapped:0x80790C40
void fn_3_151BAC(u8* a, u8* o) {
    s32 c;
    s32 delta;
    s32 half;
    f32 df;
    f32 r;
    fn_8003403C(*(f32*)(o + 0x38), *(f32*)(o + 0x3C));
    fn_80033CC8(o, *(void**)(a + 0x10));
    if (o[0x4D] != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    c = o[0x43];
    if (*(s32*)(lbl_3_data_26BFC + 0xC) / *(s16*)(o + 0x4A) < 2) {
        half = *(s32*)(lbl_3_data_26BFC + 0xC) / 2;
        delta = *(s32*)(lbl_3_data_26BDC + 8) / half;
        df = (f32)*(s32*)(lbl_3_data_26BFC + 4) * r / lbl_3_rodata_3930 / (f32)half;
    } else {
        half = *(s32*)(lbl_3_data_26BFC + 0xC) / 2;
        delta = -*(s32*)(lbl_3_data_26BDC + 8) / half;
        df = -((f32)*(s32*)(lbl_3_data_26BFC + 4) * r / lbl_3_rodata_3930) / (f32)half;
    }
    c += delta;
    if (c < 0) {
        c = 0;
    } else if (c > 0xFF) {
        c = 0xFF;
    }
    o[0x43] = c;
    *(f32*)(o + 0x38) = *(f32*)(o + 0x38) + df;
    *(f32*)(o + 0x3C) = *(f32*)(o + 0x38);
    PSVECAdd((Vec*)(o + 4), (Vec*)(o + 0x10), (Vec*)(o + 4));
    *(s16*)(o + 0x4A) -= 1;
}

// .text:0x00151D6C size:0x1C0 mapped:0x80790E00
void fn_3_151D6C(u8* a, u8* o) {
    s32 c;
    s32 delta;
    s32 half;
    f32 df;
    f32 r;
    fn_8003403C(*(f32*)(o + 0x38), *(f32*)(o + 0x3C));
    fn_80033CC8(o, *(void**)(a + 0x10));
    if (o[0x4D] != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    c = o[0x43];
    if (*(s32*)(lbl_3_data_26BEC + 0xC) / *(s16*)(o + 0x4A) < 2) {
        half = *(s32*)(lbl_3_data_26BEC + 0xC) / 2;
        delta = *(s32*)(lbl_3_data_26BDC + 8) / half;
        df = (f32)*(s32*)(lbl_3_data_26BEC + 4) * r / lbl_3_rodata_3930 / (f32)half;
    } else {
        half = *(s32*)(lbl_3_data_26BEC + 0xC) / 2;
        delta = -*(s32*)(lbl_3_data_26BDC + 8) / half;
        df = -((f32)*(s32*)(lbl_3_data_26BEC + 4) * r / lbl_3_rodata_3930) / (f32)half;
    }
    c += delta;
    if (c < 0) {
        c = 0;
    } else if (c > 0xFF) {
        c = 0xFF;
    }
    o[0x43] = c;
    *(f32*)(o + 0x38) = *(f32*)(o + 0x38) + df;
    *(f32*)(o + 0x3C) = *(f32*)(o + 0x38);
    PSVECAdd((Vec*)(o + 4), (Vec*)(o + 0x10), (Vec*)(o + 4));
    *(s16*)(o + 0x4A) -= 1;
}

// .text:0x00151F2C size:0x5BC mapped:0x80790FC0
void fn_3_151F2C(void) {
    return;
}

// .text:0x001524E8 size:0x2AC mapped:0x8079157C
void fn_3_1524E8(void) {
    return;
}

// .text:0x00152794 size:0x320 mapped:0x80791828
void fn_3_152794(void) {
    return;
}

// .text:0x00152AB4 size:0x6F0 mapped:0x80791B48
void fn_3_152AB4(void) {
    return;
}

// .text:0x001531A4 size:0x31C mapped:0x80792238
void fn_3_1531A4(void) {
    return;
}

// .text:0x001534C0 size:0x1E8 mapped:0x80792554
void fn_3_1534C0(u8* o) {
    Mtx m;
    Vec up;
    Vec axis;
    Vec dir;
    Vec off;
    f32 ang;
    f32 r;
    u8* cam;
    fn_8005268C();
    cam = fn_80052734();
    if (o[0x4D] != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    up = lbl_3_rodata_38DC;
    off.x = lbl_3_rodata_3934[0];
    off.y = lbl_3_rodata_3934[0];
    off.z = lbl_3_rodata_3A04 * r;
    PSVECSubtract((Vec*)(cam + 0x70), (Vec*)(o + 0x1C), &dir);
    PSVECNormalize(&dir, &dir);
    ang = (f32)acos(PSVECDotProduct(&up, &dir));
    PSVECCrossProduct(&up, &dir, &axis);
    if (lbl_3_rodata_3934[0] == PSVECMag(&axis)) {
        axis.x = lbl_3_rodata_3934[0];
        axis.z = lbl_3_rodata_3934[0];
        axis.y = lbl_3_rodata_3948;
    }
    PSMTXRotAxisRad(m, &axis, ang);
    PSMTXMultVec(m, &off, &off);
    *(f32*)(o + 4) = *(f32*)(o + 0x1C) + off.x;
    *(f32*)(o + 8) = *(f32*)(o + 0x20) + off.y;
    *(f32*)(o + 0xC) = *(f32*)(o + 0x24) + off.z;
    *(f32*)(o + 0x38) = *(f32*)(o + 0x3C) = (f32)*(s32*)lbl_3_data_26BEC;
    o[0x4C] = 1;
    *(s16*)(o + 0x4A) = *(s32*)(lbl_3_data_26BEC + 0xC);
    *(f32*)(o + 0x10) = *(f32*)(o + 0x18) = lbl_3_rodata_3934[0];
    *(f32*)(o + 0x14) = (f32)*(s32*)(lbl_3_data_26BEC + 8) / lbl_3_rodata_3930;
}

// .text:0x001536A8 size:0x7E4 mapped:0x8079273C
void fn_3_1536A8(u8* obj, u8 mode) {
    return;
}

// .text:0x00153E8C size:0x100 mapped:0x80792F20
void fn_3_153E8C(u8* obj, f32* pos, u8 b, u8 c, u8 d) {
    f32 r;
    *(s16*)(obj + 0x48) = (d != 0) * *(s32*)(lbl_3_data_26BEC + 0xC) + (s32)(d * *(s32*)(lbl_3_data_26BDC + 0xC)) / *(s32*)lbl_3_data_26BDC;
    obj[0x4D] = c == 4;
    obj[0x4E] = 0;
    obj[0x4F] = b;
    obj[0x42] = 0xFF;
    obj[0x41] = 0xFF;
    obj[0x40] = 0xFF;
    obj[0x43] = *(s32*)(lbl_3_data_26BDC + 4);
    *(f32*)(obj + 0x1C) = pos[0];
    if (obj[0x4D] != 0) {
        r = fn_3_119854(2);
    } else {
        r = fn_3_119854(0);
    }
    *(f32*)(obj + 0x20) = -pos[1] - lbl_3_rodata_3A18 * r;
    *(f32*)(obj + 0x24) = pos[2];
    obj[0x45] = 0;
    obj[0x44] = 0;
}

// .text:0x00153F8C size:0x158 mapped:0x80793020
void fn_3_153F8C(void* h, u32 a, u32 b, u32 c) {
    f32* pos;
    f32 r;
    u8 flag;
    u8* q;
    u8 i;
    i = 0;
    q = *(u8**)((u8*)h + 0xC);
    pos = (f32*)c;
    *(s32*)((u8*)h + 0x10) = *(s32*)(lbl_3_common_bss_32724 + 0x6C);
    do {
        if (*(s16*)(q + 0x4A) == 0) {
            flag = i != 0;
            *(s16*)(q + 0x48) = flag * *(s32*)(lbl_3_data_26BEC + 0xC) + (s32)(i * *(s32*)(lbl_3_data_26BDC + 0xC)) / *(s32*)lbl_3_data_26BDC;
            q[0x4D] = (u8)b == 4;
            q[0x4E] = 0;
            q[0x4F] = a;
            q[0x42] = 0xFF;
            q[0x41] = 0xFF;
            q[0x40] = 0xFF;
            q[0x43] = *(s32*)(lbl_3_data_26BDC + 4);
            *(f32*)(q + 0x1C) = pos[0];
            if (q[0x4D] != 0) {
                r = fn_3_119854(2);
            } else {
                r = fn_3_119854(0);
            }
            *(f32*)(q + 0x20) = -pos[1] - lbl_3_rodata_3A18 * r;
            *(f32*)(q + 0x24) = pos[2];
            q[0x45] = 0;
            q[0x44] = 0;
            fn_3_1536A8(q, flag + 1);
            i++;
        }
        q = *(u8**)q;
    } while (q != NULL && i < *(s32*)lbl_3_data_26BDC);
}

// .text:0x001540E4 size:0xE0 mapped:0x80793178
void fn_3_1540E4(u32 a, u32 b, u32 c) {
    u8* p;
    u8* h = fn_800339F0(0, 0x1C);
    if (h != NULL) {
        fn_3_153F8C(h, a, b, c);
        return;
    }
    h = fn_80033A24(fn_3_151F2C, 0x80, 0, *(int*)lbl_3_data_26BDC * 0xF, 1, 0x1C);
    if (h != NULL) {
        p = *(u8**)(h + 0xC);
        do {
            *(s16*)(p + 0x4A) = 0;
            p[0x4C] = 0;
            p[0x4F] = 0xFF;
            p = *(u8**)p;
        } while (p != NULL);
        fn_3_153F8C(h, a, b, c);
        memset(lbl_3_bss_B894, 0, 0xF);
    }
}

// .text:0x001541C4 size:0x50 mapped:0x80793258
void fn_3_1541C4(u32 a, u32 b, u32 c) {
    if (g_d_GameSettings.GameModeSelected == 7 && g_Minigame[0x1A2A] == 4 && c != 0) {
        fn_3_1540E4(a, b, c);
    }
}

// .text:0x00154214 size:0x24 mapped:0x807932A8
void fn_3_154214(void) {
    pitchingMachinePitching(0x27);
}

// .text:0x00154238 size:0xBC mapped:0x807932CC

void fn_3_154238(s16 id) {
    u8* p;
    u8** link;
    u8* first;
    u8* last;
    H154238* h = fn_800339F0(0, 0x27);
    if (h != NULL) {
        p = h->head;
        link = &h->head;
        last = NULL;
        first = NULL;
        do {
            if (*(s16*)(p + 0x18) == id) {
                *link = *(u8**)p;
                if (last != NULL) {
                    *(u8**)last = p;
                } else {
                    first = p;
                }
                *(u8**)p = NULL;
                last = p;
                h->cnt--;
            } else {
                link = (u8**)p;
            }
            p = *link;
        } while (p != NULL);
        if (first != NULL) {
            fn_80033794(first);
        }
    }
}

// .text:0x001542F4 size:0x6FC mapped:0x80793388
void fn_3_1542F4(void) {
    return;
}

// .text:0x001549F0 size:0x28C mapped:0x80793A84
void fn_3_1549F0(void) {
    return;
}

// .text:0x00154C7C size:0x5A0 mapped:0x80793D10
void fn_3_154C7C(u32 a, u32 b, u32 c) {
    return;
}

// .text:0x0015521C size:0x48 mapped:0x807942B0
void fn_3_15521C(u32 a, u32 b, u32 c) {
    if (g_d_GameSettings.GameModeSelected != 7 || b == 0 || c == 0) {
        return;
    }
    fn_3_154C7C(a, b, c);
}

// .text:0x00155264 size:0x24 mapped:0x807942F8
void fn_3_155264(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x00155288 size:0x24 mapped:0x8079431C
void fn_3_155288(void) {
    pitchingMachinePitching(0x1B);
}

// .text:0x001552AC size:0x738 mapped:0x80794340
void fn_3_1552AC(void) {
    return;
}

// .text:0x001559E4 size:0x244 mapped:0x80794A78
void fn_3_1559E4(void) {
    return;
}

// .text:0x00155C28 size:0x2E0 mapped:0x80794CBC
void fn_3_155C28(void) {
    return;
}

// .text:0x00155F08 size:0x310 mapped:0x80794F9C
void fn_3_155F08(void) {
    return;
}

// .text:0x00156218 size:0x330 mapped:0x807952AC
void fn_3_156218(void) {
    return;
}

// .text:0x00156548 size:0x428 mapped:0x807955DC
void fn_3_156548(void) {
    return;
}

// .text:0x00156970 size:0x394 mapped:0x80795A04
void fn_3_156970(void) {
    return;
}

// .text:0x00156D04 size:0x608 mapped:0x80795D98
void fn_3_156D04(void) {
    return;
}

// .text:0x0015730C size:0xA0 mapped:0x807963A0
void fn_3_15730C(u32 n, f32 x, f32 y, f32 z) {
    u8* p = ((u8**)&lbl_3_bss_B850)[0];
    f32* v;
    if (p != NULL) {
        p = *(u8**)(p + 0xC);
        while (n >= 7) {
            p = *(u8**)p;
            n -= 7;
        }
        v = (f32*)(p + n * 0xC + 4);
    } else {
        v = NULL;
    }
    if (v != NULL) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }
}

// .text:0x001573AC size:0x1C4 mapped:0x80796440
void fn_3_1573AC(void) {
    return;
}

// .text:0x00157570 size:0x18 mapped:0x80796604
extern u8* lbl_3_bss_B850;

void fn_3_157570(void) {
    lbl_3_bss_B850[0x18] = 1;
}

// .text:0x00157588 size:0x68 mapped:0x8079661C
void fn_3_157588(int n) {
    u8* p = fn_80033A24(fn_3_15767C, 0x80, 0, (n + 6) / 7, 1, 0x28);
    lbl_3_bss_B850 = p;
    p[0x18] = 0;
}

// .text:0x001575F0 size:0x8C mapped:0x80796684
void* fn_3_1575F0(u32 n) {
    u8* p = ((u8**)&lbl_3_bss_B850)[0];
    if (p != NULL) {
        p = *(u8**)(p + 0xC);
        while (n >= 7) {
            p = *(u8**)p;
            n -= 7;
        }
        return p + n * 0xC + 4;
    }
    return NULL;
}

// .text:0x0015767C size:0x27C mapped:0x80796710
void fn_3_15767C(void) {
    return;
}

// .text:0x001578F8 size:0x24 mapped:0x8079698C
void fn_3_1578F8(void) {
    pitchingMachinePitching(0x16);
}

// .text:0x0015791C size:0x1A8 mapped:0x807969B0
void fn_3_15791C(void) {
    return;
}

// .text:0x00157AC4 size:0x2F4 mapped:0x80796B58
void fn_3_157AC4(void) {
    return;
}


#pragma dont_inline off
