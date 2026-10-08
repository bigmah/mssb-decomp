#include "game/rep_3520.h"
#include "game/rep_1838.h"
#include "game/rep_540.h"
#include "game/rep_AC8.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#include "header_rep_data.h"
#include "stl/math.h"
#pragma dont_inline on


#include "static/UnknownHomes_Static.h"
extern u8 lbl_3_data_21AF0[];
extern f32 lbl_3_rodata_35D0;
extern f32 lbl_3_data_21A48[];
extern f32 lbl_3_rodata_35D8;
extern f32 lbl_3_rodata_3620;
extern f32 lbl_3_rodata_35DC;
extern f32 lbl_3_rodata_3638;
extern s16 lbl_3_data_21A3C[];
extern s16 lbl_3_data_21A04[];
extern s16 lbl_3_data_21A44;
extern u8 lbl_3_data_21B20[];
extern f32 lbl_3_data_21AF4;
extern f64 lbl_3_rodata_3668;
extern f64 lbl_3_rodata_35E0;
extern f32 lbl_3_rodata_365C;
extern void fn_800528B4(void);
extern int rand();
extern void fn_3_90064(s32);
extern f32 lbl_3_data_21A64;
extern s16 lbl_3_data_21A90[];
typedef struct { f32 x, y, z; u8 pad[0x268 - 12]; } FS;
extern FS g_Fielders[];
extern s16 lbl_3_data_21B8C[];
extern u8 lbl_3_data_219B8[];
extern u8 lbl_3_data_21278[];
extern void fn_3_10F550(s32, u8);
extern void fn_3_5A6D4(s32);
extern void changeScene(s32, s32);
extern s8 lbl_3_data_21B88[];
extern f32 lbl_3_rodata_35FC;
extern f32 lbl_3_rodata_3600;
extern f32 lbl_3_rodata_363C;
extern f32 lbl_3_rodata_35C4[];
extern f32 lbl_3_rodata_35B8[];
extern s16 lbl_3_data_21A60;
extern f32 lbl_3_rodata_3644;

extern u8 lbl_80366158[];
extern s8 lbl_3_data_26580;
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
static u8 s_buf[0x40];
static u8 s_pad[0x18];
static u8 s_tex[0x20];
static s32 s_cnt;
static s16 lbl_3_bss_B702;
static u8 s_B700;

// .text:0x00132EDC size:0x208
void fn_3_132EDC(s32 unused, s32* stage, s32* coord, s32* map, u8* c1, u8* c2) {
    s32 v;
    s32 i;
    s_cnt += (lbl_80366158[0x28] == 0);
    if ((s_cnt & 1) == 0) {
        {
            u8* r = s_buf;
            v = r[fn_800247E4(0, 0, 4, 4)];
        }
        v += lbl_3_data_26580 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            s_buf[i] = v;
        }
        DCFlushRange(s_buf, 0x40);
        if (v + lbl_3_data_26580 * 2 > 0xFF || v + lbl_3_data_26580 * 2 < 0) {
            lbl_3_data_26580 *= -1;
        }
    }
    GXLoadTexObj(s_tex, *map);
    GXSetTexCoordGen2(*coord, 1, 4, 0x3C, 0, 0x7D);
    GXSetTevOrder(*stage, *coord, *map, 0xFF);
    GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
    GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
    GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    *stage += 1;
    *coord += 1;
    *map += 1;
    *c1 += 1;
    *c2 += 1;
}

// .text:0x001330E4 size:0x11C
void fn_3_1330E4(void) {
    s32 v;
    s32 i;
    s_cnt += (lbl_80366158[0x28] == 0);
    if ((s_cnt & 1) == 0) {
        v = s_buf[fn_800247E4(0, 0, 4, 4)];
        v += lbl_3_data_26580 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 0; i < 32; i += 2) {
            s_buf[i] = v;
        }
        DCFlushRange(s_buf, 0x40);
        if (v + lbl_3_data_26580 * 2 > 0xFF || v + lbl_3_data_26580 * 2 < 0) {
            lbl_3_data_26580 *= -1;
        }
    }
}

// .text:0x00133200 size:0x120 mapped:0x80772294
void fn_3_133200(void) {
    u32 i;
    u32 j;
    u32 idx;
    u8* p;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_800247E4(j, i, 4, 4);
            if (idx < 0x20) {
                p = s_buf;
                p += idx;
                p[2] = 0xFF;
                p[0] = 0xFF;
                p[3] = 0x96;
                p[1] = 0x96;
            } else {
                p = s_buf;
                p += idx;
                p[2] = 0x96;
                p[0] = 0x96;
                p[3] = 0x96;
                p[1] = 0x96;
            }
        }
    }
    GXInitTexObj(s_tex, s_buf, 4, 4, 6, 1, 1, 0);
    GXInitTexObjLOD(s_tex, 1, 1, 0, 0, 0, 0.0f, 0.0f, 0.0f);
    lbl_3_data_26580 = -1;
    s_cnt = 0;
}

// .text:0x00133320 size:0x2C mapped:0x807723B4
#define G8 ((u8*)&g_Minigame)

#pragma opt_unroll_loops off
void fn_3_133320(void) {
    s8 i = 0;
    do {
        G8[0x1DC8 + i] = 0;
        i++;
    } while (i < 4);
}
#pragma opt_unroll_loops reset

// .text:0x0013334C size:0x1170 mapped:0x807723E0
void fn_3_13334C(void) {
    return;
}

// .text:0x001344BC size:0xF0 mapped:0x80773550
// ~99%: r6/r7 swap (g_Fielders base reg) only
int fn_3_1344BC(int a, int b) {
    u8* tbl = G8 + 0x18F8;
    u8* fz = (u8*)g_Fielders + 8;
    int ib = (s8)tbl[b] * 0x268;
    int ia = (s8)tbl[a] * 0x268;
    f32 dxb = *(f32*)((u8*)g_Fielders + ib) - lbl_3_data_21A48[0];
    f32 dzb = *(f32*)(fz + ib) - lbl_3_data_21A48[2];
    f32 angA = atan2(*(f32*)(fz + ia) - lbl_3_data_21A48[2], *(f32*)((u8*)g_Fielders + ia) - lbl_3_data_21A48[0]);
    s16 sb = radToShortAngle(atan2(dzb, dxb));
    s16 sa = radToShortAngle(angA);
    return fn_3_9FCA4(sa, sb) >= 0;
}

// .text:0x001345AC size:0xAC mapped:0x80773640
s16 fn_3_1345AC(s16 a, s16 b, s32 c) {
    s16 d;
    if (a < 0 || b < 0) {
        return b;
    }
    d = fn_3_9FCA4(b, a) / lbl_3_data_21B8C[c];
    if (d == 0 || (((d >> 31) ^ d) - (d >> 31)) > 0x5DC) {
        return b;
    }
    return fn_3_9FE6C_normalizeAngle(a + d);
}

// .text:0x00134658 size:0x2B0 mapped:0x807736EC
void fn_3_134658(void) {
    return;
}

// .text:0x00134908 size:0x10 mapped:0x8077399C
s32 fn_3_134908(s16* a, s16* b) {
    return b[2] - a[2];
}

// .text:0x00134918 size:0x24 mapped:0x807739AC
s32 fn_3_134918(f32* a, f32* b) {
    if (*a < *b) {
        return -1;
    }
    return *a > *b;
}

// .text:0x0013493C size:0x344 mapped:0x807739D0
void fn_3_13493C(void) {
    return;
}

// .text:0x00134C80 size:0xCC mapped:0x80773D14
int fn_3_134C80(u32 a, u32 b, u32 c, f32 x, f32 y) {
    if (G8[0x1D72] != 0 && a != (s8)G8[0x1D6D] && (c == ((b + 1) & 3) || c == ((b + 2) & 3))) {
        return 1;
    }
    return !!fn_3_134D4C(lbl_3_data_21A48[0], lbl_3_data_21A48[2], lbl_3_rodata_3620,
                         g_Fielders[(s8)G8[a + 0x18F8]].x, g_Fielders[(s8)G8[a + 0x18F8]].z, x, y);
}

// .text:0x00134D4C size:0x370 mapped:0x80773DE0
int fn_3_134D4C(f32 ax, f32 az, f32 r, f32 bx, f32 bz, f32 x, f32 y) {
    return 0;
}

// .text:0x001350BC size:0x400 mapped:0x80774150
void fn_3_1350BC(void) {
    return;
}

// .text:0x001354BC size:0x64 mapped:0x80774550
int fn_3_1354BC(int idx, f32 x, f32 y) {
    int r = 0;
    f64 ax = fabs(((f32*)(G8 + 0xBB0))[idx * 16] - x);
    f64 ay = fabs(((f32*)(G8 + 0xBB8))[idx * 16] - y);
    f32 fx = ax;
    f32 fy = ay;
    if (fx <= lbl_3_rodata_35D8 && fy <= lbl_3_rodata_35DC) {
        r = 1;
    }
    return r;
}

// .text:0x00135520 size:0xE0 mapped:0x807745B4
int fn_3_135520(f32 x, f32 y, f32 r) {
    if (x >= lbl_3_rodata_35D0) {
        if (y >= lbl_3_rodata_35D0) {
            if (y <= r) {
                return 1;
            }
            if (x <= r) {
                return 2;
            }
        } else {
            if (x <= r) {
                return 1;
            }
            if (y >= -r) {
                return 2;
            }
        }
    } else {
        if (y >= lbl_3_rodata_35D0) {
            if (x >= -r) {
                return 1;
            }
            if (y <= r) {
                return 2;
            }
        } else {
            if (y >= -r) {
                return 1;
            }
            if (x >= -r) {
                return 2;
            }
        }
    }
    return 0;
}

// .text:0x00135600 size:0x4C mapped:0x80774694
void fn_3_135600(f32* outX, f32* outY, f32 x, f32 y) {
    f32* d = lbl_3_data_21A48;
    u8* g = G8;
    f32 dy = y - d[2];
    f32 dx = x - d[0];
    *outX = dx * *(f32*)&g[0x1DF0] - dy * *(f32*)&g[0x1DEC];
    *outY = dx * *(f32*)&g[0x1DEC] + dy * *(f32*)&g[0x1DF0];
}

// .text:0x0013564C size:0x4C mapped:0x807746E0
int fn_3_13564C(f32 x, f32 y) {
    if (x >= lbl_3_rodata_35D0) {
        if (y >= lbl_3_rodata_35D0) {
            return 0;
        }
        return 3;
    }
    if (y >= lbl_3_rodata_35D0) {
        return 1;
    }
    return 2;
}

// .text:0x00135698 size:0x60 mapped:0x8077472C
int fn_3_135698(u8* a, u8* b) {
    u8 fa = a[0x11];
    if (fa != 0 && b[0x11] == 0) {
        return -1;
    }
    if (fa == 0 && b[0x11] != 0) {
        return 1;
    }
    {
        if (*(f32*)a < *(f32*)b) {
            return -1;
        }
        return *(f32*)a > *(f32*)b;
    }
}

// 99%: only g_Minigame base reg materialization (addi r0 + mr) differs; same as fn_3_13BB30
// .text:0x001356F8 size:0xAC mapped:0x8077478C
void fn_3_1356F8(void) {
    u8* q = G8 + 0x1DCC;
    u8* g;
    f32 v;
    u8 st;
    u32 i;
    memset(G8 + 0x1D7C, 0, 0x78);
    g = G8;
    for (i = 0; i < 4; i++) {
        st = g[0x18DC];
        *(s16*)(q + 4) = -1;
        if (RandomInt_Game(100) < (s8)lbl_3_data_21B88[st]) {
            v = lbl_3_rodata_35FC;
        } else {
            v = lbl_3_rodata_3600;
        }
        *(f32*)q = v;
        q += 8;
    }
}

// .text:0x001357A4 size:0x98 mapped:0x80774838
void fn_3_1357A4(f32* out, Vec* dir) {
    Vec base = *(Vec*)lbl_3_rodata_35C4;
    Vec v;
    if (out == NULL || dir == NULL) {
        return;
    }
    PSVECNormalize(dir, &v);
    PSVECScale(&v, lbl_3_rodata_363C, &v);
    out[0] = base.x + v.x;
    out[2] = base.z + v.z;
}

// .text:0x0013583C size:0xE8 mapped:0x807748D0
void fn_3_13583C(f32* out) {
    Vec c = *(Vec*)lbl_3_rodata_35B8;
    Vec d;
    if (out != NULL) {
        PSVECSubtract((Vec*)out, &c, &d);
        d.y = lbl_3_rodata_35D0;
        if (PSVECMag(&d) <= lbl_3_rodata_363C) {
            Vec v;
            Vec base = *(Vec*)lbl_3_rodata_35C4;
            if (out != NULL) {
                PSVECNormalize(&d, &v);
                PSVECScale(&v, lbl_3_rodata_363C, &v);
                out[0] = base.x + v.x;
                out[2] = base.z + v.z;
            }
        }
    }
}

// .text:0x00135924 size:0x140 mapped:0x807749B8
void fn_3_135924(void) {
    u32 i;
    for (i = 0; i < 100; i++) {
        if (G8[0x193A + i] == 1) {
            if (((f32*)(G8 + i * 12 + 0xCD0))[1] < lbl_3_rodata_35FC) {
                Vec d;
                Vec c = *(Vec*)lbl_3_rodata_35B8;
                if ((f32*)(G8 + i * 12 + 0xCD0) != NULL) {
                    PSVECSubtract((Vec*)(G8 + i * 12 + 0xCD0), &c, &d);
                    d.y = lbl_3_rodata_35D0;
                    if (PSVECMag(&d) <= lbl_3_rodata_363C) {
                        Vec v;
                        Vec base = *(Vec*)lbl_3_rodata_35C4;
                        if ((f32*)(G8 + i * 12 + 0xCD0) != NULL) {
                            PSVECNormalize(&d, &v);
                            PSVECScale(&v, lbl_3_rodata_363C, &v);
                            ((f32*)(G8 + i * 12 + 0xCD0))[0] = base.x + v.x;
                            ((f32*)(G8 + i * 12 + 0xCD0))[2] = base.z + v.z;
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00135A64 size:0x1B4 mapped:0x80774AF8
extern f32 lbl_3_rodata_3640;
extern f32 lbl_3_data_219AC[];
extern f32 lbl_3_data_21A54[];
extern f32 lbl_3_data_47BC[];
// 98%: g_Minigame base lands in r5 then mr r27 (orig addi r27 directly); a/b loop incr order differs
void fn_3_135A64(void) {
    u8* b;
    u8* a;
    s32 t;
    u8* p;
    s32 j;
    f32 d;
    u8* q;
    u8* g = G8;
    s16 ang;
    u8* f;
    s32 i;
    if (g[0x190B] == 0 && !(*(f32*)(g + 0x1D48) < lbl_3_rodata_3640)) {
        p = g;
        q = g;
        for (i = 0; i < 4; p += 1, q += 2, i++) {
            t = p[0x18F8];
            if ((s8)t < 0 || i == (s8)g[0x1D6D] || p[0x1D6E] != 0) {
                continue;
            }
            f = (u8*)g_Fielders + (s8)t * 0x268;
            if (f[0x203] != 0 && f[0x204] > 3) {
                continue;
            }
            ang = ((int (*)(f32, f32))fn_3_9FB8C)(*(f32*)f - lbl_3_data_219AC[0], *(f32*)(f + 8) - lbl_3_data_219AC[2]);
            a = g;
            b = g;
            for (j = 0; j < 4; a += 0x18, j++, b += 2) {
                if (fn_3_9FCF8(ang, *(s16*)(b + 0x1D64)) > 0x200) {
                    continue;
                }
                d = fn_3_9EFD0((VecXYZ*)(a + 0x1CE8), (VecXYZ*)(a + 0x1CF4), (VecXYZ*)f, 0);
                if (d < lbl_3_data_21A54[2] + lbl_3_data_47BC[f[0x1C9]] && d >= lbl_3_rodata_35D0) {
                    fn_3_1360BC(i);
                    p[0x1D6E] = 3;
                    *(s16*)(q + 0x1D5A) = 0;
                    fn_3_25844(*(s8*)(p + 0x18F8), 2);
                    fn_3_6C854(*(s8*)(p + 0x18CC), 2);
                    break;
                }
            }
        }
    }
}

// .text:0x00135C18 size:0x220 mapped:0x80774CAC
extern void fn_3_156548(u32, f32, f32, f32);
extern void fn_3_15730C(u32, f32, f32, f32);
// 97%: structure and float regs match; int saved regs (gp/ge/ep/i/k/n) and prologue lis order differ
void fn_3_135C18(void) {
    u8* e;
    f32 spC;
    s32 i = 0;
    f32* sz;
    f32 lo;
    u8* ep;
    u8* ge = G8;
    f32* sx;
    s32 k;
    u8* gp;
    f32 mid;
    f32 step;
    f32 v;
    f32 sp8;
    s32 n;
    f32 zero = lbl_3_rodata_35D0;
    ep = G8;
    n = 0;
    gp = G8;
    lo = *(f32*)(G8 + 0x1D48) * lbl_3_data_21A54[1] - lbl_3_data_21A54[0];
    step = (lbl_3_data_21A54[1] - lbl_3_data_21A54[0]) / (f32)(&lbl_3_data_21A60)[1];
    mid = lo + lbl_3_data_21A54[0];
    do {
        getComponentsFromSAng(*(s16*)(gp + 0x1D64), &spC, &sp8);
        v = lo;
        e = ep;
        sx = (f32*)(ge + 0x1CE8);
        sz = (f32*)(ge + 0x1CF0);
        k = 0;
        *(f32*)(ge + 0x1CE8) = spC * lbl_3_data_21A54[0] + lbl_3_data_21A48[0];
        *(f32*)(ge + 0x1CF0) = sp8 * lbl_3_data_21A54[0] + lbl_3_data_21A48[2];
        *(f32*)(ge + 0x1CF4) = spC * mid + lbl_3_data_21A48[0];
        *(f32*)(ge + 0x1CFC) = sp8 * mid + lbl_3_data_21A48[2];
        spC = (*(f32*)(ge + 0x1CF4) - *(f32*)(ge + 0x1CE8)) / lo;
        sp8 = (*(f32*)(ge + 0x1CFC) - *(f32*)(ge + 0x1CF0)) / lo;
        for (; k < (&lbl_3_data_21A60)[1]; k++, e += 0x28, ep += 0x28, n++) {
            *(f32*)(e + 0xA8) = spC * v + sx[0];
            *(f32*)(e + 0xB0) = sp8 * v + sz[0];
            if (v < zero) {
                e[0xCE] = 0;
            } else {
                v -= step;
                if (e[0xCE] != 0) {
                    fn_3_156548(n, *(f32*)(e + 0xA8), -*(f32*)(e + 0xAC), *(f32*)(e + 0xB0));
                } else {
                    fn_3_15730C(n, *(f32*)(e + 0xA8), -*(f32*)(e + 0xAC), *(f32*)(e + 0xB0));
                    e[0xCE] = 1;
                }
            }
        }
        i++;
        ge += 0x18;
        gp += 2;
    } while (i < 4);
}

// .text:0x00135E38 size:0x60 mapped:0x80774ECC
void fn_3_135E38(void) {
    s32 t;
    fn_3_135C18();
    t = lbl_3_data_21A3C[G8[0x1D73] * 2 - 1] * 0x3C;
    if (t == *(u32*)&G8[0x17C0]) {
        G8[0x1D72] = 3;
        *(s16*)&G8[0x1D62] = 0;
    }
}

// .text:0x00135E98 size:0xB4 mapped:0x80774F2C
void fn_3_135E98(void) {
    s16 t = *(s16*)&G8[0x1D62] + 1;
    *(s16*)&G8[0x1D62] = t;
    *(f32*)&G8[0x1D48] = lbl_3_rodata_3644 - (f32)t / (f32)lbl_3_data_21A60;
    fn_3_135C18();
    if (*(s16*)&G8[0x1D62] >= lbl_3_data_21A60) {
        G8[0x1D72] = 0;
    }
}

// .text:0x00135F4C size:0xA8 mapped:0x80774FE0
void fn_3_135F4C(void) {
    s16 t = *(s16*)&G8[0x1D62] + 1;
    *(s16*)&G8[0x1D62] = t;
    *(f32*)&G8[0x1D48] = (f32)t / (f32)lbl_3_data_21A60;
    fn_3_135C18();
    if (*(s16*)&G8[0x1D62] >= lbl_3_data_21A60) {
        G8[0x1D72] = 2;
    }
}

// .text:0x00135FF4 size:0x54 mapped:0x80775088
void fn_3_135FF4(void) {
    u8 i = G8[0x1D73];
    u32 t = *(s16*)((u8*)lbl_3_data_21A3C + i * 4) * 0x3C;
    if (t == *(u32*)&G8[0x17C0]) {
        G8[0x1D72] = 1;
        *(s16*)&G8[0x1D62] = 0;
        *(f32*)&G8[0x1D48] = lbl_3_rodata_35D0;
        G8[0x1D73] = G8[0x1D73] + 1;
    }
}

// .text:0x00136048 size:0x74 mapped:0x807750DC
void fn_3_136048(void) {
    s32 i;
    s16* a = (s16*)&g_Minigame;
    for (i = 0; i < 4; i++) {
        a[0xEB2 + i] += lbl_3_data_21A44;
        a[0xEB2 + i] = fn_3_9FE6C_normalizeAngle(a[0xEB2 + i]);
    }
}

// .text:0x001360BC size:0x164 mapped:0x80775150
void fn_3_1360BC(int p) {
    s16* pts;
    int n;
    u8* f;
    int i;
    int k;
    f = (u8*)g_Fielders + (s8)G8[0x18F8 + p] * 0x268;
    G8[0x1DF4 + p] = 1;
    pts = (s16*)(G8 + 0x1890) + p;
    n = *(s16*)((u8*)lbl_3_data_21B20 + 6);
    if (*pts < n) {
        n = *pts;
    }
    if (n != 0) {
        for (i = 0, k = 0; i < 0x32; i++) {
            if (G8[0x193A + i] == 0) {
                *(f32*)(G8 + i * 12 + 0xCD0) = *(f32*)(f + 0);
                *(f32*)(G8 + i * 12 + 0xCD4) = *(f32*)(f + 4);
                *(f32*)(G8 + i * 12 + 0xCD8) = *(f32*)(f + 8);
                *(f32*)(G8 + i * 12 + 0xCD4) = *(f32*)(f + 0x16C);
                *(f32*)(G8 + i * 12 + 0x1184) = *(f32*)(lbl_3_data_219B8 + 0x48);
                getComponentsFromSAng(random_fn_3_9EE24(0x1000), (f32*)(G8 + i * 12 + 0x1180), (f32*)(G8 + i * 12 + 0x1188));
                {
                    f32 r = RandomF32_Game_Range(*(f32*)(lbl_3_data_219B8 + 0x40), *(f32*)(lbl_3_data_219B8 + 0x44));
                    k++;
                    *(f32*)(G8 + i * 12 + 0x1180) *= r;
                    *(f32*)(G8 + i * 12 + 0x1188) *= r;
                }
                G8[0x193A + i] = 1;
                ((s16*)G8)[0xBE4 + i] = 0;
                G8[0x1D6C]++;
                if (k >= n) {
                    break;
                }
            }
        }
        fn_3_90064(0x2E8);
        *pts -= n;
    }
}

// .text:0x00136220 size:0x66C mapped:0x807752B4
void fn_3_136220(void) {
    return;
}

// .text:0x0013688C size:0x468 mapped:0x80775920
void fn_3_13688C(void) {
    return;
}

// .text:0x00136CF4 size:0x1B0 mapped:0x80775D88
extern f32 lbl_3_data_21AF8[];
extern s16 lbl_3_data_21B10[];
extern u8 lbl_3_data_21B16;
extern f32 lbl_3_rodata_3658;
extern f32 lbl_3_rodata_3660;
extern void fn_800115C8();
// 99.5%: only the first block differs (pu extsb lands in r4, orig lbz r3 / extsb r5 / lha r4); rest matches
void fn_3_136CF4(u8* o) {
    u8* g = G8;
    s32 pu;
    s16 t;
    f32 ang;
    pu = (s8)g[0x1D74];
    if (pu != -1) {
        t = *(s16*)(g + 0x1D58) - 1;
        *(s16*)(g + 0x1D58) = t;
        if (t <= 0) {
            if ((s8)g[0x1D6D] != pu) {
                fn_800115C8();
            }
            ((s8*)g)[0x1D74] = -1;
        }
    } else {
        *(s16*)(o + 0x1C) -= 1;
        if (*(s16*)(o + 0x1C) <= 0) {
            if ((s8)(rand() % 100 - lbl_3_data_21B16) < 0) {
                o[0x1E] = 1;
            } else {
                o[0x1E] = 2;
            }
            *(f32*)o = lbl_3_data_219AC[0];
            *(f32*)(o + 4) = lbl_3_data_219AC[1];
            *(f32*)(o + 8) = lbl_3_data_219AC[2];
            *(f32*)(o + 0x10) = lbl_3_data_21AF8[0];
            ang = lbl_3_rodata_3660 * (lbl_3_rodata_3658 * ((f32)rand() / lbl_3_rodata_365C));
            *(f32*)(o + 0xC) = lbl_3_data_21AF8[1] * (f32)cos(ang);
            *(f32*)(o + 0x14) = lbl_3_data_21AF8[1] * (f32)sin(ang);
            *(s16*)(o + 0x1C) = lbl_3_data_21B10[1];
        }
    }
}

// .text:0x00136EA4 size:0x1FC mapped:0x80775F38
// 99%: same pu/extsb register block as fn_3_136CF4 differs (r4/r5 vs orig r5/r3)
void fn_3_136EA4(void) {
    u8* g = G8;
    s32 pu;
    s16 t;
    f32 ang;
    if (g[0x190B] != 0) {
        ((s8*)g)[0x1D74] = -1;
        g[0xCCE] = 0;
    } else if (g[0xCCE] != 0) {
        ((void (*)(u8*))fn_3_13688C)(g + 0xCB0);
    } else {
        pu = (s8)g[0x1D74];
        if (pu != -1) {
            t = *(s16*)(g + 0x1D58) - 1;
            *(s16*)(g + 0x1D58) = t;
            if (t <= 0) {
                if ((s8)g[0x1D6D] != pu) {
                    fn_800115C8();
                }
                ((s8*)g)[0x1D74] = -1;
            }
        } else {
            *(s16*)(g + 0xCCC) -= 1;
            if (*(s16*)(g + 0xCCC) <= 0) {
                if ((s8)(rand() % 100 - lbl_3_data_21B16) < 0) {
                    g[0xCCE] = 1;
                } else {
                    g[0xCCE] = 2;
                }
                *(f32*)(G8 + 0xCB0) = lbl_3_data_219AC[0];
                *(f32*)(G8 + 0xCB4) = lbl_3_data_219AC[1];
                *(f32*)(G8 + 0xCB8) = lbl_3_data_219AC[2];
                *(f32*)(G8 + 0xCC0) = lbl_3_data_21AF8[0];
                ang = lbl_3_rodata_3660 * (lbl_3_rodata_3658 * ((f32)rand() / lbl_3_rodata_365C));
                *(f32*)(G8 + 0xCBC) = lbl_3_data_21AF8[1] * (f32)cos(ang);
                *(f32*)(G8 + 0xCC4) = lbl_3_data_21AF8[1] * (f32)sin(ang);
                *(s16*)(g + 0xCCC) = lbl_3_data_21B10[1];
            }
        }
    }
}

// .text:0x001370A0 size:0x148 mapped:0x80776134
void fn_3_1370A0(u8* o) {
    Vec sp8;
    Mtx m;
    memset(&sp8, 0, sizeof(Vec));
    sp8.y = lbl_3_data_21AF4 * (lbl_3_rodata_3668 * ((f64)((f32)rand() / lbl_3_rodata_365C) - lbl_3_rodata_35E0));
    PSMTXInverse((f32(*)[4])(o + 0x40), m);
    PSMTXMultVecSR(m, &sp8, &sp8);
    *(f32*)(o + 0x70) += sp8.x;
    *(f32*)(o + 0x74) += sp8.y;
    *(f32*)(o + 0x78) += sp8.z;
    *(f32*)(o + 0x7C) += sp8.x;
    *(f32*)(o + 0x80) += sp8.y;
    *(f32*)(o + 0x84) += sp8.z;
    lbl_3_bss_B702--;
    if (lbl_3_bss_B702 <= 0) {
        lbl_3_bss_B702 = 0;
        fn_800528B4();
    }
}

// .text:0x001371E8 size:0x3C mapped:0x8077627C
void fn_3_1371E8(void) {
    lbl_3_bss_B702 = *(s16*)lbl_3_data_21AF0;
    fn_800528AC((fn_800528AC_parameter)fn_3_1370A0);
}

// .text:0x00137224 size:0x1BC mapped:0x807762B8
void fn_3_137224(void) {
    return;
}

// .text:0x001373E0 size:0x5C0 mapped:0x80776474
void fn_3_1373E0(void) {
    return;
}

// .text:0x001379A0 size:0x170 mapped:0x80776A34
void fn_3_1379A0(void) {
    return;
}

// .text:0x00137B10 size:0x1E8 mapped:0x80776BA4
u8 fn_3_137B10(u8* o) {
    return 0;
}

// .text:0x00137CF8 size:0xEC mapped:0x80776D8C
void fn_3_137CF8(u8* o) {
    u32 t;
    s16* row;
    int lo;
    PSVECAdd((Vec*)o, (Vec*)(o + 0xC), (Vec*)o);
    if (fn_3_137B10(o) == 0 && *(f32*)(o + 4) >= lbl_3_data_21A64) {
        t = *(u32*)&G8[0x17C0] / 60 / 20;
        if (t > 3) {
            t = 3;
        }
        o[0x3D] = 0;
        *(s16*)(o + 0x3A) = 0;
        row = lbl_3_data_21A90 + G8[0x1A2B] * 8;
        lo = row[t * 2];
        t = random_fn_3_9EE24((row[t * 2 + 1] - lo) * 60);
        *(s16*)(o + 0x38) = t + lo * 60;
    }
}

// .text:0x00137DE4 size:0x130 mapped:0x80776E78
void fn_3_137DE4(u8* o) {
    u32 t;
    s16* row;
    int lo;
    PSVECAdd((Vec*)o, (Vec*)(o + 0xC), (Vec*)o);
    PSVECAdd((Vec*)(o + 0x18), (Vec*)(o + 0x24), (Vec*)(o + 0x18));
    if (*(s16*)(o + 0x3A) < 0x7FFE) {
        (*(s16*)(o + 0x3A))++;
    } else {
        *(s16*)(o + 0x3A) = 0x7FFF;
    }
    if ((f32) * (s16*)(o + 0x3A) >= (&lbl_3_data_21A64)[7]) {
        t = *(u32*)&G8[0x17C0] / 60 / 20;
        if (t > 3) {
            t = 3;
        }
        o[0x3D] = 0;
        *(s16*)(o + 0x3A) = 0;
        row = lbl_3_data_21A90 + G8[0x1A2B] * 8;
        lo = row[t * 2];
        t = random_fn_3_9EE24((row[t * 2 + 1] - lo) * 60);
        *(s16*)(o + 0x38) = t + lo * 60;
    }
}

// .text:0x00137F14 size:0x118 mapped:0x80776FA8
void fn_3_137F14(u8* o) {
    if (G8[0x72A] != 0) {
        *(f32*)(o + 0x10) = (&lbl_3_data_21A64)[5];
        o[0x3D] = 5;
        *(s16*)(o + 0x3A) = 0;
    } else {
        if (o[0x3E] != 0) {
            o[0x3F]++;
            if (o[0x3F] >= 10) {
                fn_3_90064(0x303);
                o[0x3E] = 0;
            }
        }
        if (*(s16*)(o + 0x3A) < 0x7FFE) {
            (*(s16*)(o + 0x3A))++;
        } else {
            *(s16*)(o + 0x3A) = 0x7FFF;
        }
        if (fn_3_137B10(o) == 0 && (f32) * (s16*)(o + 0x3A) >= (&lbl_3_data_21A64)[6]) {
            *(f32*)(o + 0x10) = (&lbl_3_data_21A64)[5];
            o[0x3D] = 5;
            *(s16*)(o + 0x3A) = 0;
        }
    }
}

// .text:0x0013802C size:0x2B4 mapped:0x807770C0
void fn_3_13802C(void) {
    return;
}

// .text:0x001382E0 size:0x168 mapped:0x80777374
void fn_3_1382E0(void) {
    return;
}

// .text:0x00138448 size:0x6C mapped:0x807774DC
void fn_3_138448(u8* a) {
    if (G8[0x72A] == 0) {
        s16* t = (s16*)(a + 0x3A);
        if (*t < 0x7FFE) {
            *t += 1;
        } else {
            *t = 0x7FFF;
        }
        if (*(s16*)(a + 0x3A) >= *(s16*)(a + 0x38)) {
            a[0x3E] = 0;
            fn_3_1384B4();
        }
    }
}

// .text:0x001384B4 size:0x5F0 mapped:0x80777548
void fn_3_1384B4(void) {
    return;
}

// .text:0x00138AA4 size:0x71C mapped:0x80777B38
void fn_3_138AA4(void) {
    return;
}

// .text:0x001391C0 size:0x540 mapped:0x80778254
void fn_3_1391C0(void) {
    return;
}

// .text:0x00139700 size:0x4C mapped:0x80778794
void fn_3_139700(void) {
    u8* m = G8;
    if (m[0xBAC] != 0) {
        if (m[0x190B] != 0) {
            m[0xBAC] = 0;
            return;
        }
        fn_3_1391C0();
    }
}

// .text:0x0013974C size:0xBC mapped:0x807787E0
void fn_3_13974C(void) {
    u32 i;
    for (i = 0; i < 100; i++) {
        if (G8[0x193A + i] == 3) {
            ((s16*)G8)[0xBE4 + i]++;
            PSVECAdd((Vec*)(G8 + i * 12 + 0xCD0), (Vec*)(G8 + i * 12 + 0x1180), (Vec*)(G8 + i * 12 + 0xCD0));
            *(f32*)(G8 + i * 12 + 0x1184) += *(f32*)(lbl_3_data_219B8 + 0x2C);
            if (*(f32*)(G8 + i * 12 + 0x1184) < lbl_3_rodata_35D0) {
                G8[0x193A + i] = 0;
                G8[0x1D6C]--;
            }
        }
    }
}

// .text:0x00139808 size:0x498 mapped:0x8077889C
void fn_3_139808(void) {
    return;
}

// .text:0x00139CA0 size:0x2E4 mapped:0x80778D34
void fn_3_139CA0(void) {
    return;
}

// .text:0x00139F84 size:0xC4 mapped:0x80779018
void fn_3_139F84(void) {
    u32 i;
    u8* a;
    s16* b;
    u8* c;
    fn_3_139CA0();
    fn_3_139808();
    a = G8;
    b = (s16*)G8;
    c = G8;
    for (i = 0; i < 100; i++) {
        if (a[0x193A] == 3) {
            b[0xBE4]++;
            PSVECAdd((Vec*)(c + 0xCD0), (Vec*)(c + 0x1180), (Vec*)(c + 0xCD0));
            *(f32*)(c + 0x1184) += *(f32*)(lbl_3_data_219B8 + 0x2C);
            if (*(f32*)(c + 0x1184) < lbl_3_rodata_35D0) {
                a[0x193A] = 0;
                G8[0x1D6C]--;
            }
        }
        a++;
        b++;
        c += 12;
    }
}

// .text:0x0013A048 size:0x64 mapped:0x807790DC
void fn_3_13A048(int i, int j) {
    s16* arr = (s16*)(G8 + 0x1890);
    s16 v = arr[j];
    s16 c = lbl_3_data_21A04[7];
    if (v < c) {
        arr[i] += v;
        arr[j] = 0;
    } else {
        arr[i] += c;
        arr[j] -= c;
    }
}

// .text:0x0013A0AC size:0x678 mapped:0x80779140
void fn_3_13A0AC(void) {
    return;
}

// .text:0x0013A724 size:0x178 mapped:0x807797B8
void fn_3_13A724(void) {
    return;
}

// .text:0x0013A89C size:0x1DC mapped:0x80779930
void fn_3_13A89C(void) {
    return;
}

// .text:0x0013AA78 size:0x23C mapped:0x80779B0C
void fn_3_13AA78(void) {
    return;
}

// .text:0x0013ACB4 size:0x10C mapped:0x80779D48
void fn_3_13ACB4(void) {
    return;
}

// .text:0x0013ADC0 size:0x5C mapped:0x80779E54
void fn_3_13ADC0(f32* out, f32* a, f32* b) {
    f32 d = (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
    d = d * lbl_3_rodata_3638;
    out[0] = a[0] - d * b[0];
    out[1] = a[1] - d * b[1];
    out[2] = a[2] - d * b[2];
}

// .text:0x0013AE1C size:0x1C8 mapped:0x80779EB0
void fn_3_13AE1C(void) {
    return;
}

// .text:0x0013AFE4 size:0x2A0 mapped:0x8077A078
void fn_3_13AFE4(void) {
    return;
}

// .text:0x0013B284 size:0x740 mapped:0x8077A318
void fn_3_13B284(void) {
    return;
}

// .text:0x0013B9C4 size:0x16C mapped:0x8077AA58
void fn_3_13B9C4(void) {
    return;
}

// 99%: only g_Minigame base reg materialization (addi r0 + mr) differs; same as fn_3_1356F8
// .text:0x0013BB30 size:0xC4 mapped:0x8077ABC4
void fn_3_13BB30(void) {
    u32 i;
    u8 st;
    u8* q;
    u8* g;
    f32 v;
    fn_3_F1DC();
    q = G8 + 0x1DCC;
    memset(g_Minigame._1D7C, 0, 0x78);
    g = G8;
    for (i = 0; i < 4; i++) {
        st = g[0x18DC];
        *(s16*)(q + 4) = -1;
        if (RandomInt_Game(100) < (s8)lbl_3_data_21B88[st]) {
            v = lbl_3_rodata_35FC;
        } else {
            v = lbl_3_rodata_3600;
        }
        *(f32*)q = v;
        q += 8;
        g++;
    }
    changeScene(1, 6);
    fn_3_5A6D4(2);
}

// .text:0x0013BBF4 size:0xC4 mapped:0x8077AC88
void fn_3_13BBF4(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        g_GameLogic._125 = 1;
        break;
    case 1:
        if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x0013BCB8 size:0x7AC mapped:0x8077AD4C
void fn_3_13BCB8(void) {
    return;
}

// .text:0x0013C464 size:0x4 mapped:0x8077B4F8
void fn_3_13C464(void) {
    return;
}

// .text:0x0013C468 size:0x328 mapped:0x8077B4FC
void fn_3_13C468(void) {
    return;
}

