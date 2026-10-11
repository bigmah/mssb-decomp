#include "game/rep_3090.h"
#include "header_rep_data.h"
#include "Dolphin/mtxext.h"
#include "Dolphin/GX.h"

extern u8 lbl_80366158[];
extern Vec lbl_3_data_21004;
extern s32 lbl_3_data_20FC4[]; /* AnimKey stride per AnimTrack type */
extern s32 lbl_3_data_20FD0[]; /* number of Vec3 groups per AnimKey, per AnimTrack type */
extern f64 atan2(f64, f64);
extern f64 fabs(f64);
#ifdef __MWERKS__
#define FABSF(x) ((f32)__fabs(x))
#else
#define FABSF(x) ((f32)fabs(x))
#endif
extern const f32 lbl_3_rodata_3164;
extern const f32 lbl_3_rodata_3168;
extern const f32 lbl_3_rodata_316C;
/* Camera evaluation result (0x88 bytes): matrix plus the decomposed camera parameters. */
typedef struct CamMtx {
    /* 0x00 */ Mtx44 m;
    /* 0x40 */ f32 f40;
    /* 0x44 */ f32 f44;
    /* 0x48 */ f32 f48;
    /* 0x4C */ f32 f4C;
    /* 0x50 */ f32 f50;
    /* 0x54 */ f32 f54;
    /* 0x58 */ Vec pos;
    /* 0x64 */ Vec target;
    /* 0x70 */ Vec scale;
    /* 0x7C */ f32 rx;
    /* 0x80 */ f32 ry;
    /* 0x84 */ u8 type;
} CamMtx;
/* The original pools .data from lbl_3_data_1C0A8; the axis vectors sit at +0x4F44. Pad reproduces that offset. */
static u8 s_axpad[0x4F44] = {1};
static Vec s_axa = {0.0f, 1.0f, 0.0f};
static Vec s_axb = {0.0f, 0.0f, 1.0f};
static Vec s_axc = {0.0f, 0.0f, -1.0f};
extern Vec lbl_3_data_20FF8;
extern Vec lbl_3_data_20FEC;

extern u8* lbl_3_common_bss_DE94;
extern u8 g_GameLogic[];
extern u8* g_pCamera;
extern f32 fn_3_9FEA8(f32);
extern s16 fn_3_9FF04(f32);
extern f64 cos(f64);
extern f64 sin(f64);
extern u32 lbl_3_rodata_30EC[];
extern u8 g_Camera[];
extern s16 lbl_3_bss_B67A;
extern void* memset(void*, s32, u32);
extern void* memcpy(void*, const void*, u32);
extern const f32 lbl_3_rodata_30FC;
extern const f32 lbl_3_rodata_30F8;
extern const f32 lbl_3_rodata_3144;
extern const f32 lbl_3_rodata_3158;
extern const f32 lbl_3_rodata_3198;
extern const f32 lbl_3_rodata_311C;
extern const f32 lbl_3_rodata_3134;
extern const f32 lbl_3_rodata_315C;
extern const f64 lbl_3_rodata_3178;
extern const f32 lbl_3_rodata_3110;
extern const f32 lbl_3_rodata_314C;
extern u8 lbl_8036E548[];
extern void** fn_800111D8(void*);
extern void fn_800B2C44(void*, u16, Vec*);
extern u8* lbl_803CC1B8;
extern u8 g_Fielders[];
extern u8 g_Runners[];       /* InMemRunnerType[4], stride 0x154 */
extern u8 g_Ball[];          /* InMemBallType; starts with the ball position */
extern u8 g_Stats[];         /* g_Stats_s: 0x36 replayInd, 0x3C */
extern s32 lbl_3_data_3B4C[]; /* per-character joint index */
extern Vec lbl_3_data_1DB00[];
extern BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out);
extern u8 LoadModel(void*);
extern void fn_800B0A14_removeQueue(void*);
#pragma dont_inline on

/* TODO type: g_pCamera / lbl_3_common_bss_DE94 field accessors until the structs are typed. */
#define CAMF(off) (*(f32*)(g_pCamera + (off)))
#define DEF(off) (*(f32*)(lbl_3_common_bss_DE94 + (off)))
static inline void CamsResetUp(void);
static inline void CamApplyScriptFrame(void);
static inline void ZeroTbl(void);

// .text:0x000FC448 size:0x4F0 mapped:0x8073B4DC
// NONMATCHING 98%: fn_3_FC938's body run once per camera; saved-register numbering of `i` and the hoisted stack
// addresses stay rotated (see docs/patterns/unsolved.md).
#if NONMATCHING
void fn_3_FC448(void) {
    s32 i;
    u32* l;
    s32 n;
    for (i = 0; i < 2; i++) {
        lbl_3_common_bss_DE94 = g_Camera + i * 0x9BC + 0x120;
        n = 0;
        l = *(u32**)(g_pCamera + 0x1B4);
        while (*l != 0) {
            l++;
            n++;
        }
        *(s32*)(lbl_3_common_bss_DE94 + 0x120) = n;
        memcpy(*(void**)(lbl_3_common_bss_DE94 + 0x990), *(u8**)(g_pCamera + 0x1B4) + (*(u32**)(g_pCamera + 0x1B4))[*(s16*)(lbl_3_common_bss_DE94 + 0x940)], 0x8000);
        *(u32*)(lbl_3_common_bss_DE94 + 0x124) = 1;
        *(u32*)(lbl_3_common_bss_DE94 + 0x118) = 0;
        *(u32*)(lbl_3_common_bss_DE94 + 0x11C) = 0;
        *(u32*)(lbl_3_common_bss_DE94 + 0x928) = 0;
        ZeroTbl();
        CamsResetUp();
        fn_3_105C84(*(u8**)(lbl_3_common_bss_DE94 + 0x990));
        CamApplyScriptFrame();
        fn_3_101CC4();
    }
}
#endif

// .text:0x000FC938 size:0x500 mapped:0x8073B9CC
#pragma dont_inline off
static inline void ZeroTbl(void) {
    s32 j;
    for (j = 0; j < 0x200; j++) {
        *(u32*)(lbl_3_common_bss_DE94 + 0x128 + j * 4) = 0;
    }
}
void fn_3_FC938(void) {
    u32* l;
    s32 n;
    n = 0;
    l = *(u32**)(g_pCamera + 0x1B4);
    while (*l != 0) {
        l++;
        n++;
    }
    *(s32*)(lbl_3_common_bss_DE94 + 0x120) = n;
    memcpy(*(void**)(lbl_3_common_bss_DE94 + 0x990), *(u8**)(g_pCamera + 0x1B4) + (*(u32**)(g_pCamera + 0x1B4))[*(s16*)(lbl_3_common_bss_DE94 + 0x940)], 0x8000);
    *(u32*)(lbl_3_common_bss_DE94 + 0x124) = 1;
    *(u32*)(lbl_3_common_bss_DE94 + 0x118) = 0;
    *(u32*)(lbl_3_common_bss_DE94 + 0x11C) = 0;
    *(u32*)(lbl_3_common_bss_DE94 + 0x928) = 0;
    ZeroTbl();
    CamsResetUp();
    fn_3_105C84(*(u8**)(lbl_3_common_bss_DE94 + 0x990));
    CamApplyScriptFrame();
    fn_3_101CC4();
}
#pragma dont_inline on

// .text:0x000FCE38 size:0x74 mapped:0x8073BECC
// NONMATCHING 95%: only the out-of-line loop-2 preheader (slwi r6,r3,6 after the final blr, dead `b` left behind) differs
// (see docs/patterns/unsolved.md). Moves path index i so that path[i-1].t < t <= path[i].t.
#if NONMATCHING
s32 fn_3_FCE38(s32 i, f32 t) {
    u8* d = lbl_3_common_bss_DE94;
    s32 n = *(s32*)(d + 0x3C);
    while (i < n && t > (*(PathPt**)(d + 0x34))[i].t) {
        i++;
    }
    while (i > 0 && t <= (*(PathPt**)(d + 0x34))[i - 1].t) {
        i--;
    }
    return i;
}
#endif

// .text:0x000FCEAC size:0x4 mapped:0x8073BF40
void fn_3_FCEAC(void) {
    return;
}

// .text:0x000FCEB0 size:0x70 mapped:0x8073BF44
// NONMATCHING: loop preheader (lwz n; li off,0) is placed inline instead of after the final blr, and the dead `b`/`blr`
// are missing (see docs/patterns/unsolved.md). Returns the first path index with t <= path[i].t, or -1.
#if NONMATCHING
s32 fn_3_FCEB0(f32 t) {
    u8* d = lbl_3_common_bss_DE94;
    s32 i = 0;
    s32 n;
    if (t < 0.0) {
        return -1;
    }
    n = *(s32*)(d + 0x3C);
    while (i < n && t > (*(PathPt**)(d + 0x34))[i].t) {
        i++;
    }
    return i < n ? i : -1;
}
#endif

// .text:0x000FCF20 size:0x4 mapped:0x8073BFB4
void fn_3_FCF20(void) {
    return;
}

// .text:0x000FCF24 size:0x4E4 mapped:0x8073BFB8
// NONMATCHING 75%: indexing/addressing schedule differs (original uses indexed stfsx/lwzx forms).
// Builds the camera path: for each window of 4 keys, samples a cubic B-spline (mode 0) or Catmull-Rom (mode 1)
// into the PathPt array. Per-segment sample counts live in the table at +0x128.
#if NONMATCHING
void fn_3_FCF24(void) {
    s32 total = 0;
    s32 i;
    for (i = 0; i < *(s32*)(lbl_3_common_bss_DE94 + 0x20) - 3; i++) {
        SplineCtrl* c;
        s32 j;
        s32 k;
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 5; k++) {
                (*(SplineCtrl**)(lbl_3_common_bss_DE94 + 0x1C))[i + j].v[k] = (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[i + j].v[k];
            }
        }
        *(s32*)(lbl_3_common_bss_DE94 + 0x38) = ((s32*)(lbl_3_common_bss_DE94 + 0x128))[i];
        c = &(*(SplineCtrl**)(lbl_3_common_bss_DE94 + 0x1C))[i];
        if (c[1].v[0] == c[2].v[0] && c[2].v[0] == c[3].v[0] && c[1].v[1] == c[2].v[1] && c[2].v[1] == c[3].v[1] &&
            c[1].v[2] == c[2].v[2] && c[2].v[2] == c[3].v[2]) {
            ((s32*)(lbl_3_common_bss_DE94 + 0x128))[i] = 0;
            *(s32*)(lbl_3_common_bss_DE94 + 0x38) = 0;
        }
        for (j = 0; j < *(s32*)(lbl_3_common_bss_DE94 + 0x38); j++) {
            f32 t = (f32)j / (f32)*(s32*)(lbl_3_common_bss_DE94 + 0x38);
            f32 t2 = t * t;
            f32 t3 = t2 * t;
            f32* out = (f32*)&(*(PathPt**)(lbl_3_common_bss_DE94 + 0x34))[total];
            if (*(s32*)(lbl_3_common_bss_DE94 + 0x44) == 0) {
                f32 w0 = -1.0f * t3 + 3.0f * t2 - 3.0f * t + 1.0f;
                f32 w1 = 3.0f * t3 - 6.0f * t2 + 4.0f;
                f32 w2 = -3.0f * t3 + 3.0f * t2 + 3.0f * t + 1.0f;
                f32 w3 = t3;
                for (k = 0; k < 5; k++) {
                    c = &(*(SplineCtrl**)(lbl_3_common_bss_DE94 + 0x1C))[i];
                    out[k] = (w0 * c[0].v[k] + w1 * c[1].v[k] + w2 * c[2].v[k] + w3 * c[3].v[k]) / 6.0f;
                }
            } else {
                f32 w0 = -1.0f * t3 + 2.0f * t2 - t;
                f32 w1 = 3.0f * t3 - 5.0f * t2 + 2.0f;
                f32 w2 = -3.0f * t3 + 4.0f * t2 + t;
                f32 w3 = t3 - t2;
                for (k = 0; k < 5; k++) {
                    c = &(*(SplineCtrl**)(lbl_3_common_bss_DE94 + 0x1C))[i];
                    out[k] = (w0 * c[0].v[k] + w1 * c[1].v[k] + w2 * c[2].v[k] + w3 * c[3].v[k]) * 0.5f;
                }
            }
            total++;
        }
    }
    *(s32*)(lbl_3_common_bss_DE94 + 0x3C) = total;
}
#endif

// .text:0x000FD408 size:0xD4 mapped:0x8073C49C
void fn_3_FD408(u32 i, void* out, f32* uv) {
    u8* d = lbl_3_common_bss_DE94;
    if (*(u32*)(d + 0x3C) > i) {
        memcpy(out, &(*(PathPt**)(d + 0x34))[i], 12);
        uv[0] = (*(PathPt**)(d + 0x34))[i].u;
        uv[1] = (*(PathPt**)(d + 0x34))[i].v;
    } else {
        memcpy(out, &(*(PathPt**)(d + 0x34))[*(u32*)(d + 0x3C) - 1], 12);
        uv[0] = (*(PathPt**)(d + 0x34))[*(u32*)(d + 0x3C) - 1].u;
        uv[1] = (*(PathPt**)(d + 0x34))[*(u32*)(d + 0x3C) - 1].v;
    }
}

// .text:0x000FD4DC size:0x40 mapped:0x8073C570
void fn_3_FD4DC(void) {
    u8* p = lbl_3_common_bss_DE94;
    if ((*(u32*)(p + 0x118) >> 16) == 0) {
        *(u32*)(p + 0x20) = *(u32*)(p + 0x124);
    }
    fn_3_FCF24();
}

// .text:0x000FD51C size:0x8C mapped:0x8073C5B0
typedef struct { u32 a, b, c; } V3U;
typedef struct { u8 pad0[4]; u32 f4; u32 f8; V3U fC; u8 pad18[4]; u32 f1C; u32 f20; u32 f24; u32 f28; f32 f2C; u32 f30; u32 f34; u32 f38; u32 f3C; u32 f40; f32 f44; } CamSub;

void fn_3_FD51C(s32 i) {
    u8* c = g_Camera + i * 0x9BC;
    u8* p;
    V3U v = *(V3U*)lbl_3_rodata_30EC;
    *(u32*)(c + 0x140) = 0;
    *(u32*)(c + 0x144) = 0;
    p = c + 0x13C;
    *(V3U*)(p + 0xC) = v;
    *(u32*)(p + 0x1C) = 0;
    *(u32*)(p + 0x20) = 0;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
    *(f32*)(p + 0x2C) = 0.0f;
    *(u32*)(p + 0x30) = 0;
    *(u32*)(p + 0x34) = 0;
    *(u32*)(p + 0x38) = 0;
    *(u32*)(p + 0x3C) = 0;
    *(u32*)(p + 0x40) = 0;
    *(f32*)(p + 0x44) = 0.0f;
}

#pragma dont_inline off
static inline Vec MkVec(f32 x, f32 y, f32 z) {
    Vec v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}
static inline Vec CamStep(Vec a, Vec b, Vec c, f32 w0, f32 w1, f32 w2) {
    Vec dir;
    Vec sc;
    Vec e;
    f32 d;
    f32 t;
    PSVECSubtract(&a, &b, &dir);
    d = PSVECDistance(&a, &b);
    PSVECSubtract(&c, &b, &e);
    PSVECScale(&e, lbl_3_rodata_3144, &sc);
    t = w0 * (w2 - d) + w1 * (PSVECDotProduct(&sc, &dir) / d);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, t * lbl_3_rodata_3144, &dir);
    PSVECAdd(&a, &dir, &a);
    return a;
}
static inline void CamSubInit(CamSub* p, V3U* v) {
    p->f4 = 0;
    p->f8 = 0;
    p->fC = *v;
    p->f1C = 0;
    p->f20 = 0;
    p->f24 = 0;
    p->f28 = 0;
    p->f2C = 0.0f;
    p->f30 = 0;
    p->f34 = 0;
    p->f38 = 0;
    p->f3C = 0;
    p->f40 = 0;
    p->f44 = 0.0f;
}
static inline void CamSubInitUp(CamSub* p, Vec* v) {
    p->f4 = 0;
    p->f8 = 0;
    *(Vec*)&p->fC = *v;
    p->f1C = 0;
    p->f20 = 0;
    p->f24 = 0;
    p->f28 = 0;
    p->f2C = lbl_3_rodata_30F8;
    p->f30 = 0;
    p->f34 = 0;
    p->f38 = 0;
    p->f3C = 0;
    p->f40 = 0;
    p->f44 = lbl_3_rodata_30F8;
}
static inline void CamsResetUp(void) {
    s32 i;
    Vec v = {0.0f, 1.0f, 0.0f};
    for (i = 0; i < 2; i++) {
        CamSubInitUp((CamSub*)(g_Camera + i * 0x9BC + 0x13C), &v);
    }
}
static inline void CamApplyScriptFrame(void) {
    u8 m[0x88];
    u8 o[0x58];
    u8* p0c;
    u8* p18;
    Vec va;
    Vec vb;
    s32 b = *(s32*)(lbl_3_common_bss_DE94 + 0x118);
    s32 a = *(s32*)(lbl_3_common_bss_DE94 + 0x990);
    memset(m, 0, 0x88);
    *(f32*)(m + 0x3C) = lbl_3_rodata_30FC;
    *(f32*)(m + 0x28) = lbl_3_rodata_30FC;
    *(f32*)(m + 0x14) = lbl_3_rodata_30FC;
    *(f32*)(m + 0x00) = lbl_3_rodata_30FC;
    *(f32*)(m + 0x40) = lbl_3_rodata_30FC;
    fn_3_104B3C(a, b, 0, 0, m);
    memcpy(o, m + 0x58, 12);
    p0c = o + 0xC;
    memcpy(p0c, m + 0x64, 12);
    memcpy(o + 0x40, m + 0x70, 12);
    *(f32*)(o + 0x3C) = *(f32*)(m + 0x4C);
    p18 = o + 0x18;
    PSMTX44MultVec((f32(*)[4])m, &s_axa, (Vec*)p18);
    PSVECNormalize((Vec*)p18, (Vec*)p18);
    va = *(Vec*)(o + 0x24);
    PSMTX44MultVec((f32(*)[4])m, &s_axb, &va);
    PSVECNormalize(&va, &va);
    vb = *(Vec*)(o + 0x30);
    PSMTX44MultVec((f32(*)[4])m, &s_axc, &vb);
    PSVECNormalize(&vb, &vb);
    *(f32*)(o + 0x4C) = *(f32*)(m + 0x7C);
    *(f32*)(o + 0x50) = *(f32*)(m + 0x80);
    *(u8*)(o + 0x54) = *(u8*)(m + 0x84);
    memcpy(lbl_3_common_bss_DE94 + 0x64, o, 12);
    *(f32*)(lbl_3_common_bss_DE94 + 0xA0) = *(f32*)(o + 0x3C);
    *(f32*)(lbl_3_common_bss_DE94 + 0xA4) = *(f32*)(o + 0x4C);
    *(f32*)(lbl_3_common_bss_DE94 + 0xA8) = *(f32*)(o + 0x50);
    *(u8*)(lbl_3_common_bss_DE94 + 0x9A7) = *(u8*)(o + 0x54);
    memcpy(lbl_3_common_bss_DE94 + 0x88, p0c, 12);
    *(f32*)(g_pCamera + 0x2858) = *(f32*)(o + 0x0);
    *(f32*)(g_pCamera + 0x285C) = *(f32*)(o + 0x4);
    *(f32*)(g_pCamera + 0x2860) = *(f32*)(o + 0x8);
    *(f32*)(g_pCamera + 0x2870) = *(f32*)(o + 0x4C);
    *(f32*)(g_pCamera + 0x2874) = *(f32*)(o + 0x50);
    *(s16*)(g_pCamera + 0x289C) = fn_3_9FF04(fn_3_9FEA8(*(f32*)(g_pCamera + 0x2870)));
    *(s16*)(g_pCamera + 0x289C) = fn_3_9FF04(fn_3_9FEA8(*(f32*)(g_pCamera + 0x2870)));
    *(f32*)(g_pCamera + 0x2878) = lbl_3_rodata_30FC;
}
static inline void CamsReset(void) {
    s32 i;
    V3U v = *(V3U*)lbl_3_rodata_30EC;
    for (i = 0; i < 2; i++) {
        CamSubInit((CamSub*)(g_Camera + i * 0x9BC + 0x13C), &v);
    }
}
#pragma dont_inline on

// .text:0x000FD5A8 size:0xC8 mapped:0x8073C63C
void fn_3_FD5A8(void) {
    s32 i;
    V3U v = *(V3U*)lbl_3_rodata_30EC;
    for (i = 0; i < 2; i++) {
        u8* c = g_Camera + i * 0x9BC;
        u8* p;
        *(u32*)(c + 0x140) = 0;
        *(u32*)(c + 0x144) = 0;
        p = c + 0x13C;
        *(V3U*)(p + 0xC) = v;
        *(u32*)(p + 0x1C) = 0;
        *(u32*)(p + 0x20) = 0;
        *(u32*)(p + 0x24) = 0;
        *(u32*)(p + 0x28) = 0;
        *(f32*)(p + 0x2C) = 0.0f;
        *(u32*)(p + 0x30) = 0;
        *(u32*)(p + 0x34) = 0;
        *(u32*)(p + 0x38) = 0;
        *(u32*)(p + 0x3C) = 0;
        *(u32*)(p + 0x40) = 0;
        *(f32*)(p + 0x44) = 0.0f;
    }
}

// .text:0x000FD670 size:0x38C mapped:0x8073C704
// fn_3_105C28 is inlined here (result unused).
void fn_3_FD670(void) {
    u8* d;
    if (g_GameLogic[0x122] != 0) {
        return;
    }
    CamApplyScriptFrame();
    fn_3_1000D8();
    *(u32*)(lbl_3_common_bss_DE94 + 0x93C) = *(u32*)(lbl_3_common_bss_DE94 + 0x938);
    *(s16*)(lbl_3_common_bss_DE94 + 0x948) = *(s16*)(lbl_3_common_bss_DE94 + 0x946);
    *(s16*)(lbl_3_common_bss_DE94 + 0x942) = *(s16*)(lbl_3_common_bss_DE94 + 0x940);
    d = lbl_3_common_bss_DE94;
    switch (*(s16*)(d + 0x944)) {
    case 0:
        if (d[0x9AE] != 0) {
            if (((s32(*)(void))fn_3_FDB30)() != 0) {
                lbl_3_common_bss_DE94[0x9AE] = 0;
                lbl_3_common_bss_DE94[0x9AF] = 0;
                lbl_3_common_bss_DE94[0x9B0] = 0;
            }
        } else if (d[0x9AD] == 1) {
            fn_3_105C28(*(u8**)(d + 0x990), *(u32*)(d + 0x118));
            if (*(u32*)(d + 0x118) >= *(u32*)(d + 0x11C) - 1) {
                d[0x9AD] = 0;
            } else {
                *(u32*)(d + 0x118) += 0x10000;
            }
        }
        break;
    case 1:
        if (d[0x9AE] == 0) {
            *(s16*)(d + 0x944) = 0;
        }
        break;
    }
}

// .text:0x000FD9FC size:0x20 mapped:0x8073CA90
s32 fn_3_FD9FC(void) {
    return *(s32*)(lbl_3_common_bss_DE94 + 0x18) == 1;
}

typedef struct { u8 pad[0x218]; u8 f; u8 pad2[0x268 - 0x219]; } FDA1CT;

// .text:0x000FDA1C size:0x114 mapped:0x8073CAB0
void fn_3_FDA1C(void) {
    u8* p = lbl_803CC1B8;
    u16 i;
    u8* model;

    switch (*(s16*)(p + 0x22)) {
    case 0:
        *(s16*)(p + 0x22) = 1;
        break;
    case 1:
        i = *(u16*)(p + 0x1E);
        model = ((u8**)(lbl_8036E548 + 0x2C50))[i];
        if (((FDA1CT*)g_Fielders)[i].f == 0) {
            if (i < 9) {
                *(u16*)(p + 0x1E) = i + 1;
                *(s16*)(p + 0x22) = 0;
            } else {
                *(s16*)(p + 0x22) = 2;
            }
        } else if (model == NULL || LoadModel(model)) {
            if (*(u16*)(p + 0x1E) < 9) {
                *(u16*)(p + 0x1E) = *(u16*)(p + 0x1E) + 1;
                *(s16*)(p + 0x22) = 0;
            } else {
                *(s16*)(p + 0x22) = 2;
            }
        }
        break;
    case 2:
        model = *(u8**)(p + 0xC);
        *(s16*)(model + 0x10) = 1;
        fn_800B0A14_removeQueue(model);
        *(s16*)(p + 0x22) = 0;
        break;
    }
}

// .text:0x000FDB30 size:0x24E8 mapped:0x8073CBC4
void fn_3_FDB30(void) {
    return;
}

// .text:0x00100018 size:0x20 mapped:0x8073F0AC

s32 fn_3_100018(void) {
    return *(u8*)(lbl_3_common_bss_DE94 + 0x9B6) == 1;
}

// .text:0x00100038 size:0x44 mapped:0x8073F0CC
void fn_3_100038(void) {
    if (*(u32*)(lbl_3_common_bss_DE94 + 0x118) > *(u32*)(lbl_3_common_bss_DE94 + 0x11C)) {
        if (lbl_3_common_bss_DE94[0x9B1] == 0) {
            *(u32*)(lbl_3_common_bss_DE94 + 0x118) = *(u32*)(lbl_3_common_bss_DE94 + 0x11C);
        } else {
            *(u32*)(lbl_3_common_bss_DE94 + 0x118) = 0;
        }
    } else {
        *(u32*)(lbl_3_common_bss_DE94 + 0x118) += 0x10000;
    }
}

// .text:0x0010007C size:0x5C mapped:0x8073F110
s32 fn_3_10007C(void) {
    u8* p = lbl_3_common_bss_DE94;
    if (p[0x9AB] == 1) {
        if (*(s32*)(p + 0x14) != 0) {
            lbl_80366158[0x28] = 1;
            return 0;
        }
        lbl_80366158[0x28] = 0;
        return 1;
    }
    return 1;
}

// .text:0x001000D8 size:0x1BEC mapped:0x8073F16C
// NONMATCHING 90%: scored with fn_3_103C30/fn_3_103E7C/fn_3_1040D8 and the local helpers inlined (the original inlines
// them; nmverify flags those calls); remaining diff is register allocation/scheduling.
// Per-frame replay camera update: places the eye (g_pCamera+0x2840) and look-at (+0x284C) for the current mode
// (+0x9A8 ball-follow modes in +0x9A9, else script modes in +0x9A7), with optional smoothing (+0x9B4).
#if NONMATCHING
extern f32 game_atan2(f32 x, f32 y);
/* Rotates the camera eye about `pivot` by `rot`. */
static void CamOrbit(Mtx rot, const Vec* pivot) {
    Vec v;
    memcpy(&v, g_pCamera + 0x2840, 12);
    v.x = CAMF(0x2840) - pivot->x;
    v.y = CAMF(0x2844) - pivot->y;
    v.z = CAMF(0x2848) - pivot->z;
    PSMTXMultVec(rot, &v, &v);
    v.x = v.x + pivot->x;
    v.y = v.y + pivot->y;
    v.z = v.z + pivot->z;
    memcpy(g_pCamera + 0x2840, &v, 12);
}
static void CamEyeFromScript(void) {
    CAMF(0x2840) = CAMF(0x2858);
    CAMF(0x2844) = CAMF(0x285C);
    CAMF(0x2848) = CAMF(0x2860);
    if (CAMF(0x2844) < 0.1f) {
        CAMF(0x2844) = 0.1f;
    }
}
/* Look-at = `tgt` (smoothed by fn_3_103C30), then smooth the eye (fn_3_1040D8). */
static void CamSetTarget(Vec* tgt) {
    CAMF(0x284C) = tgt->x;
    CAMF(0x2850) = tgt->y;
    CAMF(0x2854) = tgt->z;
    fn_3_103C30(tgt);
    CAMF(0x284C) = tgt->x;
    CAMF(0x2850) = tgt->y;
    CAMF(0x2854) = tgt->z;
    fn_3_1040D8();
}
/* InMemBallType: 0x00 pos, 0x3C prev pos, 0x40.., 0x48, 0x54 */
#define BALLF(off) (*(f32*)(ball + (off)))
/* Ball-follow eye position for ball camera mode (+0x9A9). */
static void CamBallEye(void) {
    u8* ball = g_Ball;
    Mtx rot;
    f32 dz;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 t;
    switch (lbl_3_common_bss_DE94[0x9A9]) {
    case 0:
    case 1:
        DEF(0xA0) = 0.87266463f;
        CAMF(0x2840) = BALLF(0x0);
        CAMF(0x2844) = BALLF(0x4);
        CAMF(0x2848) = BALLF(0x8);
        break;
    case 2:
    case 3:
        DEF(0xA0) = 0.87266463f;
        CAMF(0x2840) = BALLF(0x48);
        CAMF(0x2844) = BALLF(0x4C);
        CAMF(0x2848) = BALLF(0x50);
        break;
    case 4:
        dz = BALLF(0x8) - CAMF(0x2860);
        if (dz < 0.0f) {
            dz = -BALLF(0x8) - CAMF(0x2860);
        }
        vz = BALLF(0x8) - BALLF(0x44);
        vx = BALLF(0x0) - BALLF(0x3C);
        vy = BALLF(0x4) - BALLF(0x40);
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        CAMF(0x2840) = (BALLF(0x0) + vx) - vx * t;
        CAMF(0x2844) = (BALLF(0x4) + vy) - vy * t;
        CAMF(0x2848) = (BALLF(0x8) + vz) - vz * t;
        break;
    case 6:
        dz = BALLF(0x8) - CAMF(0x2860);
        if (dz < 0.0f) {
            dz = -BALLF(0x8) - CAMF(0x2860);
        }
        vz = BALLF(0x8) - BALLF(0x44);
        vx = BALLF(0x0) - BALLF(0x3C);
        vy = BALLF(0x4) - BALLF(0x40);
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        CAMF(0x2840) = vx * t + (BALLF(0x0) - vx);
        CAMF(0x2844) = vy * t + (BALLF(0x4) - vy);
        CAMF(0x2848) = vz * t + (BALLF(0x8) - vz);
        break;
    case 5:
        dz = BALLF(0x8) - CAMF(0x2860);
        if (dz < 0.0f) {
            dz = -BALLF(0x8) - CAMF(0x2860);
        }
        vz = BALLF(0x8) - BALLF(0x44);
        vx = BALLF(0x0) - BALLF(0x3C);
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        CAMF(0x2840) = (BALLF(0x0) + vx) - vx * t;
        CAMF(0x2844) = BALLF(0x4);
        CAMF(0x2848) = (BALLF(0x8) + vz) - vz * t;
        break;
    case 7:
        dz = BALLF(0x8) - CAMF(0x2860);
        if (dz < 0.0f) {
            dz = -BALLF(0x8) - CAMF(0x2860);
        }
        vz = BALLF(0x8) - BALLF(0x44);
        vx = BALLF(0x0) - BALLF(0x3C);
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        CAMF(0x2840) = vx * t + (BALLF(0x0) - vx);
        CAMF(0x2844) = BALLF(0x4);
        CAMF(0x2848) = vz * t + (BALLF(0x8) - vz);
        break;
    case 8:
        CAMF(0x2840) = CAMF(0x2858);
        CAMF(0x2844) = CAMF(0x285C);
        CAMF(0x2848) = CAMF(0x2860);
        PSMTXRotRad(rot, 'Y', -fn_3_9FEA8(1.5707964f + game_atan2(BALLF(0x0) - BALLF(0x3C), BALLF(0x8) - BALLF(0x44))));
        CamOrbit(rot, (Vec*)ball);
        break;
    }
}
/* Ball-follow look-at target for ball camera mode (+0x9A9); modes > 8 leave *tgt unchanged. */
static void CamBallTarget(Vec* tgt) {
    u8* ball = g_Ball;
    switch (lbl_3_common_bss_DE94[0x9A9]) {
    case 0:
        tgt->x = BALLF(0x0) + (BALLF(0x0) - BALLF(0x3C));
        tgt->y = BALLF(0x4) + (BALLF(0x4) - BALLF(0x40));
        tgt->z = BALLF(0x8) + (BALLF(0x8) - BALLF(0x44));
        break;
    case 1:
        tgt->y = BALLF(0x4);
        tgt->x = BALLF(0x0) + (BALLF(0x0) - BALLF(0x3C));
        tgt->z = BALLF(0x8) + (BALLF(0x8) - BALLF(0x44));
        break;
    case 2:
        tgt->x = BALLF(0x54);
        tgt->y = BALLF(0x58);
        tgt->z = BALLF(0x5C);
        break;
    case 3:
        tgt->x = BALLF(0x54);
        tgt->y = BALLF(0x4C);
        tgt->z = BALLF(0x5C);
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        memcpy(tgt, lbl_3_common_bss_DE94 + 0x88, 12);
        fn_3_106270(tgt);
        break;
    }
}
/* Orbits the eye about the tracked actor (0-8 fielder, 9-12 runner, 13 ball) to face along its heading. */
static void CamOrbitTracked(s16 idx) {
    u8* ball = g_Ball;
    Mtx rot;
    if (idx < 9 && idx >= 0) {
        u8* fl = g_Fielders + idx * 0x268;
        PSMTXRotRad(rot, 'Y', -fn_3_9FEA8(1.5707964f + *(f32*)(fl + 0x48)));
        CamOrbit(rot, (Vec*)fl);
    } else if (idx < 13 && idx >= 0) {
        u8* rn = g_Runners + (idx - 9) * 0x154;
        PSMTXRotRad(rot, 'Y', fn_3_9FEA8(*(f32*)(rn + 0x30)));
        CamOrbit(rot, (Vec*)rn);
    } else if (idx == 13) {
        PSMTXRotRad(rot, 'Y', atan2(-(BALLF(0x3C) - BALLF(0x0)), -(BALLF(0x44) - BALLF(0x8))));
        CamOrbit(rot, (Vec*)ball);
    }
}
/* Look-at point 100 units from the script eye along (yaw, pitch) = ang. */
static void CamAngleTarget(f32* ang) {
    f32 cp;
    f32 cy;
    f32 sp;
    f32 cp2;
    f32 sy;
    cp = cos(ang[1]);
    cy = cos(ang[0]);
    sp = sin(ang[1]);
    cp2 = cos(ang[1]);
    sy = sin(ang[0]);
    CAMF(0x284C) = CAMF(0x2858) + 100.0f * cy * cp;
    CAMF(0x2850) = CAMF(0x285C) + 100.0f * sp;
    CAMF(0x2854) = CAMF(0x2860) + 100.0f * sy * cp2;
}
/* Reset the eye smoothing state to the current eye. */
static void CamInitEye(void) {
    DEF(0xAC) = CAMF(0x2840);
    DEF(0xB0) = CAMF(0x2844);
    DEF(0xB4) = CAMF(0x2848);
    DEF(0xB8) = 0.00001f + CAMF(0x2840);
    DEF(0xBC) = 0.00001f + CAMF(0x2844);
    DEF(0xC0) = 0.00001f + CAMF(0x2848);
}
/* Set the look-at to `tgt` and reset the look-at smoothing state to it. */
static void CamInitTarget(Vec* tgt) {
    CAMF(0x284C) = tgt->x;
    CAMF(0x2850) = tgt->y;
    CAMF(0x2854) = tgt->z;
    DEF(0xC4) = 0.00001f + CAMF(0x284C);
    DEF(0xC8) = 0.00001f + CAMF(0x2850);
    DEF(0xCC) = 0.00001f + CAMF(0x2854);
    DEF(0xD0) = 0.00002f + CAMF(0x284C);
    DEF(0xD4) = 0.00002f + CAMF(0x2850);
    DEF(0xD8) = 0.00002f + CAMF(0x2854);
}
void fn_3_1000D8(void) {
    s16 idx = *(s16*)(lbl_3_common_bss_DE94 + 0x946);
    Vec tgt;

    if (lbl_3_common_bss_DE94[0x9A8] == 0) {
        switch (lbl_3_common_bss_DE94[0x9A7]) {
        case 0:
        case 1: {
            f32 ang[2]; /* yaw, pitch */
            CamEyeFromScript();
            ang[0] = fn_3_9FEA8(CAMF(0x2870));
            ang[1] = fn_3_9FEA8(CAMF(0x2874));
            fn_3_103E7C(ang);
            CamAngleTarget(ang);
            fn_3_1040D8();
            break;
        }
        case 2:
            if (idx < 13 && idx >= 0 && *(s16*)(lbl_3_common_bss_DE94 + 0x950) <= 2) {
                fn_3_101CC4();
            }
            if (lbl_3_common_bss_DE94[0x9AA] == 0) {
                CamEyeFromScript();
                memcpy(&tgt, lbl_3_common_bss_DE94 + 0x88, 12);
                fn_3_106270(&tgt);
                CamSetTarget(&tgt);
            } else if (lbl_3_common_bss_DE94[0x9AA] == 1) {
                CamEyeFromScript();
                CamOrbitTracked(idx);
                memcpy(&tgt, lbl_3_common_bss_DE94 + 0x88, 12);
                fn_3_106270(&tgt);
                CamSetTarget(&tgt);
            }
            if (CAMF(0x2850) < 0.1f) {
                CAMF(0x2850) = 0.1f;
            }
            break;
        }
    } else {
        CamBallEye();
        if (CAMF(0x2844) < 1.0f) {
            CAMF(0x2844) = 1.0f;
        }
        CamBallTarget(&tgt);
        /* mode > 8 leaves tgt unset, as in the original. */
        CamSetTarget(&tgt);
        if (CAMF(0x2850) < 0.1f) {
            CAMF(0x2850) = 0.1f;
        }
    }
}
#endif

// .text:0x00101CC4 size:0x1F6C mapped:0x80740D58
// NONMATCHING 88% (scored with the helpers inlined; call sequence identical): same structure as fn_3_1000D8 (whose helpers it shares, and which the original inlines; nmverify flags
// those calls), but first resets the eye/look-at smoothing state (+0xAC..+0xD8) to the new camera.
#if NONMATCHING
void fn_3_101CC4(void) {
    s16 idx = *(s16*)(lbl_3_common_bss_DE94 + 0x946);
    Vec tgt;

    if (lbl_3_common_bss_DE94[0x9A8] == 0) {
        switch (lbl_3_common_bss_DE94[0x9A7]) {
        case 0:
        case 1: {
            f32 ang[2]; /* yaw, pitch */
            memcpy(g_pCamera + 0x2840, g_pCamera + 0x2858, 12);
            if (CAMF(0x2844) < 0.1f) {
                CAMF(0x2844) = 0.1f;
            }
            CamInitEye();
            ang[0] = fn_3_9FEA8(CAMF(0x2870));
            ang[1] = fn_3_9FEA8(CAMF(0x2874));
            DEF(0xC4) = ang[0];
            DEF(0xC8) = ang[1];
            DEF(0xCC) = 0.0f;
            DEF(0xD0) = 0.00001f + ang[0];
            DEF(0xD4) = 0.00001f + ang[1];
            DEF(0xD8) = 0.0f;
            fn_3_103E7C(ang);
            CamAngleTarget(ang);
            fn_3_1040D8();
            if (CAMF(0x2850) < 0.1f) {
                CAMF(0x2850) = 0.1f;
            }
            break;
        }
        case 2:
            if (lbl_3_common_bss_DE94[0x9AA] == 0) {
                CamEyeFromScript();
                CamInitEye();
                memcpy(&tgt, lbl_3_common_bss_DE94 + 0x88, 12);
                fn_3_106270(&tgt);
                CamInitTarget(&tgt);
                CamSetTarget(&tgt);
                if (CAMF(0x2850) < 0.1f) {
                    CAMF(0x2850) = 0.1f;
                }
            } else if (lbl_3_common_bss_DE94[0x9AA] == 1) {
                CamEyeFromScript();
                CamOrbitTracked(idx);
                memcpy(&tgt, lbl_3_common_bss_DE94 + 0x88, 12);
                fn_3_106270(&tgt);
                CamInitTarget(&tgt);
                CamSetTarget(&tgt);
                if (CAMF(0x2850) < 0.1f) {
                    CAMF(0x2850) = 0.1f;
                }
            }
            break;
        }
    } else {
        CamBallEye();
        if (CAMF(0x2844) < 1.0f) {
            CAMF(0x2844) = 1.0f;
        }
        CamInitEye();
        CamBallTarget(&tgt);
        /* ball modes > 8 leave tgt unset, as in the original. */
        CamInitTarget(&tgt);
        CamSetTarget(&tgt);
        if (CAMF(0x2850) < 0.1f) {
            CAMF(0x2850) = 0.1f;
        }
    }
}
#endif

// .text:0x00103C30 size:0x24C mapped:0x80742CC4
void fn_3_103C30(Vec* p) {
    if (lbl_3_common_bss_DE94[0x9B4] != 0) {
        Vec r;
        Vec ta;
        Vec tb;
        Vec tc;
        Vec junk;
        memcpy(&junk, p, 12);
        ta.x = *(f32*)(lbl_3_common_bss_DE94 + 0xD0);
        ta.y = *(f32*)(lbl_3_common_bss_DE94 + 0xD4);
        ta.z = *(f32*)(lbl_3_common_bss_DE94 + 0xD8);
        memcpy(&tb, p, 12);
        tc.x = *(f32*)(lbl_3_common_bss_DE94 + 0xC4);
        tc.y = *(f32*)(lbl_3_common_bss_DE94 + 0xC8);
        tc.z = *(f32*)(lbl_3_common_bss_DE94 + 0xCC);
        r = CamStep(ta, tb, tc, *(f32*)(lbl_3_common_bss_DE94 + 0x10C), *(f32*)(lbl_3_common_bss_DE94 + 0x110), *(f32*)(lbl_3_common_bss_DE94 + 0x114));
        *(f32*)(lbl_3_common_bss_DE94 + 0xC4) = p->x;
        *(f32*)(lbl_3_common_bss_DE94 + 0xC8) = p->y;
        *(f32*)(lbl_3_common_bss_DE94 + 0xCC) = p->z;
        *(f32*)(lbl_3_common_bss_DE94 + 0xD0) = r.x;
        *(f32*)(lbl_3_common_bss_DE94 + 0xD4) = r.y;
        *(f32*)(lbl_3_common_bss_DE94 + 0xD8) = r.z;
        p->x = r.x;
        p->y = r.y;
        p->z = r.z;
    }
}

// .text:0x00103E7C size:0x25C mapped:0x80742F10
void fn_3_103E7C(f32* p) {
    if (lbl_3_common_bss_DE94[0x9B4] != 0) {
        Vec r;
        Vec ta;
        Vec tb;
        Vec tc;
        p[0] = fn_3_9FEA8(p[0]);
        p[1] = fn_3_9FEA8(p[1]);
        ta.x = *(f32*)(lbl_3_common_bss_DE94 + 0xD0);
        ta.y = *(f32*)(lbl_3_common_bss_DE94 + 0xD4);
        ta.z = *(f32*)(lbl_3_common_bss_DE94 + 0xD8);
        tb.x = p[0];
        tb.y = p[1];
        tb.z = lbl_3_rodata_30F8;
        tc.x = *(f32*)(lbl_3_common_bss_DE94 + 0xC4);
        tc.y = *(f32*)(lbl_3_common_bss_DE94 + 0xC8);
        tc.z = *(f32*)(lbl_3_common_bss_DE94 + 0xCC);
        r = CamStep(ta, tb, tc, *(f32*)(lbl_3_common_bss_DE94 + 0x10C), *(f32*)(lbl_3_common_bss_DE94 + 0x110), *(f32*)(lbl_3_common_bss_DE94 + 0x114));
        *(f32*)(lbl_3_common_bss_DE94 + 0xC4) = p[0];
        *(f32*)(lbl_3_common_bss_DE94 + 0xC8) = p[1];
        *(f32*)(lbl_3_common_bss_DE94 + 0xCC) = lbl_3_rodata_30F8;
        *(f32*)(lbl_3_common_bss_DE94 + 0xD0) = r.x;
        *(f32*)(lbl_3_common_bss_DE94 + 0xD4) = r.y;
        *(f32*)(lbl_3_common_bss_DE94 + 0xD8) = r.z;
        p[0] = r.x;
        p[1] = r.y;
    }
}

// .text:0x001040D8 size:0x260 mapped:0x8074316C
void fn_3_1040D8(void) {
    if (lbl_3_common_bss_DE94[0x9B4] != 0) {
        Vec r;
        Vec ta;
        Vec tb;
        Vec tc;
        f32 bx = *(f32*)(g_pCamera + 0x2840);
        f32 by = *(f32*)(g_pCamera + 0x2844);
        f32 bz = *(f32*)(g_pCamera + 0x2848);
        ta.x = *(f32*)(lbl_3_common_bss_DE94 + 0xB8);
        ta.y = *(f32*)(lbl_3_common_bss_DE94 + 0xBC);
        ta.z = *(f32*)(lbl_3_common_bss_DE94 + 0xC0);
        tb.x = bx;
        tb.y = by;
        tb.z = bz;
        tc.x = *(f32*)(lbl_3_common_bss_DE94 + 0xAC);
        tc.y = *(f32*)(lbl_3_common_bss_DE94 + 0xB0);
        tc.z = *(f32*)(lbl_3_common_bss_DE94 + 0xB4);
        r = CamStep(ta, tb, tc, *(f32*)(lbl_3_common_bss_DE94 + 0x100), *(f32*)(lbl_3_common_bss_DE94 + 0x104), *(f32*)(lbl_3_common_bss_DE94 + 0x108));
        *(f32*)(g_pCamera + 0x2840) = r.x;
        *(f32*)(g_pCamera + 0x2844) = r.y;
        *(f32*)(g_pCamera + 0x2848) = r.z;
        *(f32*)(lbl_3_common_bss_DE94 + 0xB8) = r.x;
        *(f32*)(lbl_3_common_bss_DE94 + 0xBC) = r.y;
        *(f32*)(lbl_3_common_bss_DE94 + 0xC0) = r.z;
        *(f32*)(lbl_3_common_bss_DE94 + 0xAC) = bx;
        *(f32*)(lbl_3_common_bss_DE94 + 0xB0) = by;
        *(f32*)(lbl_3_common_bss_DE94 + 0xB4) = bz;
    }
}

// .text:0x00104338 size:0x270 mapped:0x807433CC
void fn_3_104338(void) {
    CamApplyScriptFrame();
}

// .text:0x001045A8 size:0x198 mapped:0x8074363C
void fn_3_1045A8(void) {
    f32 sinPitch;
    f32 cosYaw;
    f32 yaw;
    f32 pitch;
    f32 dist;
    f32 sinYaw;
    f32 dx, dy, dz;

    pitch = fn_3_9FEA8(CAMF(0x2874));
    dist = 20.0f * (f32)cos(pitch);
    sinPitch = (f32)sin(pitch);
    yaw = fn_3_9FEA8(CAMF(0x2870));
    cosYaw = (f32)cos(yaw);
    sinYaw = (f32)sin(yaw);
    dx = cosYaw * dist;
    dy = 20.0f * sinPitch;
    dz = sinYaw * dist;
    CAMF(0x2858) += cosYaw * CAMF(0x287C);
    CAMF(0x2860) += sinYaw * CAMF(0x287C);
    CAMF(0x2858) += sinYaw * CAMF(0x2880);
    CAMF(0x2860) -= cosYaw * CAMF(0x2880);
    CAMF(0x284C) = dx + CAMF(0x2858);
    CAMF(0x2850) = dy + CAMF(0x285C);
    CAMF(0x2854) = dz + CAMF(0x2860);
    CAMF(0x2840) = CAMF(0x2858);
    CAMF(0x2844) = CAMF(0x285C);
    CAMF(0x2848) = CAMF(0x2860);
    CAMF(0x287C) = 0.0f;
    CAMF(0x2880) = 0.0f;
}

// .text:0x00104740 size:0x1A0 mapped:0x807437D4
void fn_3_104740(void) {
    if (lbl_3_common_bss_DE94[0x9A7] == 2) {
        DEF(0xC4) = lbl_3_rodata_3158 + CAMF(0x284C);
        DEF(0xC8) = lbl_3_rodata_3158 + CAMF(0x2850);
        DEF(0xCC) = lbl_3_rodata_3158 + CAMF(0x2854);
        DEF(0xD0) = lbl_3_rodata_315C + CAMF(0x284C);
        DEF(0xD4) = lbl_3_rodata_315C + CAMF(0x2850);
        DEF(0xD8) = lbl_3_rodata_315C + CAMF(0x2854);
    } else {
        DEF(0xC4) = lbl_3_rodata_3158 + CAMF(0x2870);
        DEF(0xC8) = lbl_3_rodata_3158 + CAMF(0x2874);
        DEF(0xCC) = lbl_3_rodata_30F8;
        DEF(0xD0) = lbl_3_rodata_3158 + CAMF(0x2870);
        DEF(0xD4) = lbl_3_rodata_3158 + CAMF(0x2874);
        DEF(0xD8) = lbl_3_rodata_30F8;
    }
    DEF(0xAC) = CAMF(0x2840);
    DEF(0xB0) = CAMF(0x2844);
    DEF(0xB4) = CAMF(0x2848);
    DEF(0xB8) = lbl_3_rodata_3158 + CAMF(0x2840);
    DEF(0xBC) = lbl_3_rodata_3158 + CAMF(0x2844);
    DEF(0xC0) = lbl_3_rodata_3158 + CAMF(0x2848);
}

// .text:0x001048E0 size:0x15C mapped:0x80743974
void fn_3_1048E0(s32 a, s32 b, s32 c, s32 d, u8* out) {
    u8 m[0x88];
    Vec va;
    Vec vb;
    memset(m, 0, 0x88);
    {
        f32 v = lbl_3_rodata_30FC;
        *(f32*)(m + 0x3C) = v;
        *(f32*)(m + 0x28) = v;
        *(f32*)(m + 0x14) = v;
        *(f32*)(m + 0x00) = v;
        *(f32*)(m + 0x40) = v;
    }
    fn_3_104B3C(a, b, c, d, m);
    memcpy(out, m + 0x58, 12);
    memcpy(out + 0xC, m + 0x64, 12);
    memcpy(out + 0x40, m + 0x70, 12);
    *(f32*)(out + 0x3C) = *(f32*)(m + 0x4C);
    PSMTX44MultVec((f32(*)[4])m, &s_axa, (Vec*)(out + 0x18));
    PSVECNormalize((Vec*)(out + 0x18), (Vec*)(out + 0x18));
    va = *(Vec*)(out + 0x24);
    PSMTX44MultVec((f32(*)[4])m, &s_axb, &va);
    PSVECNormalize(&va, &va);
    vb = *(Vec*)(out + 0x30);
    PSMTX44MultVec((f32(*)[4])m, &s_axc, &vb);
    PSVECNormalize(&vb, &vb);
    *(f32*)(out + 0x4C) = *(f32*)(m + 0x7C);
    *(f32*)(out + 0x50) = *(f32*)(m + 0x80);
    *(u8*)(out + 0x54) = *(u8*)(m + 0x84);
}

// .text:0x00104A3C size:0x4C mapped:0x80743AD0
void fn_3_104A3C(void* dst, void* mtx) {
    PSMTX44MultVec(mtx, &lbl_3_data_21004, dst);
    PSVECNormalize(dst, dst);
}

// .text:0x00104A88 size:0x4C mapped:0x80743B1C
void fn_3_104A88(void* dst, void* mtx) {
    PSMTX44MultVec(mtx, &lbl_3_data_20FF8, dst);
    PSVECNormalize(dst, dst);
}

// .text:0x00104AD4 size:0x4C mapped:0x80743B68
void fn_3_104AD4(void* dst, void* mtx) {
    PSMTX44MultVec(mtx, &lbl_3_data_20FEC, dst);
    PSVECNormalize(dst, dst);
}

// .text:0x00104B20 size:0x1C mapped:0x80743BB4
// NONMATCHING: original = 3 grouped lfs (f2,f1,f0) then 3 stfs; ours interleaves lfs/stfs through f0 (see docs/patterns/unsolved.md).
// Copies the translation row (offset 0x30) of a 4x4 matrix into dst.
#if NONMATCHING
void fn_3_104B20(Vec* dst, Mtx44 src) {
    dst->x = src[3][0];
    dst->y = src[3][1];
    dst->z = src[3][2];
}
#endif

// .text:0x00104B3C size:0x990 mapped:0x80743BD0
// NONMATCHING 93%: register allocation and stack layout differ.
// Evaluates track `track` of the replay camera animation at `key` (frame << 16 | frac) into the camera matrix `m`:
// first its parent chain (up to `depth` levels), then interpolates the surrounding keys and appends
// translation * rotation * scale. Track type 2 is a look-at camera aimed at the position of track `target`.
#if NONMATCHING
void fn_3_104B3C(s32 a, s32 b, s32 c, s32 d, void* mp) {
    ReplayAnim* anim = (ReplayAnim*)a; /* TODO type: callers pass the animation pointer as s32 */
    u32 key = b;
    s16 track = c;
    u8 depth = d;
    CamMtx* m = mp;
    AnimTrack* trk = anim->tracks[track];
    u8* first = trk->keys;
    AnimKeyF* k;
    s32 stride;
    u16 count;
    u32 frame;
    u16 lo;
    Mtx44 rotY;
    Mtx44 rotX;
    Mtx44 tmp;
    Mtx44 S;
    Mtx44 R;
    Mtx44 T;
    Mtx44 I;
    AnimKeyF interp;
    CamMtx sub;
    Vec rot;    /* rot angles (types 0/1) or position (type 2) */
    Vec tgt;
    Vec right;
    Vec fwd;
    Vec up;
    Vec a0;
    Vec b0;

    if (trk->parent >= 0 && depth != 0) {
        fn_3_104B3C(a, key, trk->parent, (u8)(depth - 1), m);
    }
    count = trk->count;
    frame = key >> 16;
    stride = lbl_3_data_20FC4[trk->type];
    lo = key;
    k = (AnimKeyF*)(first + (count - 1) * stride);
    if (count != 1 && frame < k->frame) {
        AnimKeyF* cur = (AnimKeyF*)first;
        AnimKeyF* next = (AnimKeyF*)(first + stride);
        while ((u32)(next->frame << 16) <= key) {
            cur = next;
            next = (AnimKeyF*)((u8*)next + stride);
        }
        k = cur;
        if (cur->frame != frame || lo != 0) {
            f32 t = ((f32)(key - (cur->frame << 16)) / lbl_3_rodata_3164) / (f32)(next->frame - cur->frame);
            f32 omt = lbl_3_rodata_30FC - t;
            u32 n;
            Vec va;
            Vec vb;
            Vec vr;
            for (n = 0; n < (u32)lbl_3_data_20FD0[trk->type]; n++) {
                memcpy(&va, &next->f[n * 3], 12);
                memcpy(&vb, &cur->f[n * 3], 12);
                vr.x = va.x * t + vb.x * omt;
                vr.y = va.y * t + vb.y * omt;
                vr.z = va.z * t + vb.z * omt;
                memcpy(&interp.f[n * 3], &vr, 12);
            }
            k = &interp;
        }
    }

    PSMTX44Identity(I);
    switch (trk->type) {
    case 0:
        m->type = 0;
        PSMTX44Identity(T);
        T[3][0] = k->f[0];
        T[3][1] = lbl_3_rodata_3110 * k->f[1];
        T[3][2] = k->f[2];
        m->pos.x = k->f[0];
        m->pos.y = lbl_3_rodata_3110 * k->f[1];
        m->pos.z = k->f[2];
        m->rx = lbl_3_rodata_3110 * k->f[4] + lbl_3_rodata_314C;
        m->ry = k->f[3] - lbl_3_rodata_314C;
        rot.x = lbl_3_rodata_3110 * k->f[4] + lbl_3_rodata_314C;
        rot.y = k->f[3] - lbl_3_rodata_314C;
        rot.z = k->f[5];
        PSMTX44Identity(R);
        PSMTX44RotRad(rotX, 'X', rot.x);
        PSMTX44RotRad(rotY, 'Y', rot.y);
        PSMTX44Concat(R, rotX, R);
        PSMTX44Concat(R, rotY, R);
        PSMTX44Identity(S);
        S[0][0] = k->f[6];
        S[1][1] = k->f[7];
        S[2][2] = k->f[8];
        m->scale.x = k->f[6];
        m->scale.y = k->f[7];
        m->scale.z = k->f[8];
        if (trk->flags & 1) {
            m->f40 = m->f40 * k->f[9];
        } else {
            m->f40 = k->f[9];
        }
        m->f44 = k->f[10];
        if (m->f44 >= lbl_3_rodata_30F8) {
            while (FABSF(m->f44) > lbl_3_rodata_30FC) {
                m->f44 -= lbl_3_rodata_30FC;
            }
        } else {
            while (FABSF(m->f44) > lbl_3_rodata_30FC) {
                m->f44 += lbl_3_rodata_30FC;
            }
        }
        m->f48 = k->f[11];
        if (m->f48 >= lbl_3_rodata_30F8) {
            while (FABSF(m->f48) > lbl_3_rodata_30FC) {
                m->f48 -= lbl_3_rodata_30FC;
            }
        } else {
            while (FABSF(m->f48) > lbl_3_rodata_30FC) {
                m->f48 += lbl_3_rodata_30FC;
            }
        }
        break;
    case 1:
        m->type = 1;
        PSMTX44Identity(T);
        T[3][0] = k->f[0];
        T[3][1] = lbl_3_rodata_3110 * k->f[1];
        T[3][2] = k->f[2];
        m->pos.x = k->f[0];
        m->pos.y = lbl_3_rodata_3110 * k->f[1];
        m->pos.z = k->f[2];
        m->rx = lbl_3_rodata_3110 * k->f[4] + lbl_3_rodata_314C;
        m->ry = k->f[3] - lbl_3_rodata_314C;
        rot.x = k->f[3] - lbl_3_rodata_314C;
        rot.y = lbl_3_rodata_3110 * k->f[4] + lbl_3_rodata_314C;
        rot.z = k->f[5];
        PSMTX44Identity(R);
        PSMTX44RotRad(rotX, 'X', rot.x);
        PSMTX44RotRad(rotY, 'Y', rot.y);
        PSMTX44Concat(R, rotX, R);
        PSMTX44Concat(R, rotY, R);
        PSMTX44Identity(S);
        S[0][0] = k->f[6];
        S[1][1] = k->f[7];
        S[2][2] = k->f[8];
        m->scale.x = k->f[6];
        m->scale.y = k->f[7];
        m->scale.z = k->f[8];
        m->f4C = k->f[10];
        m->f50 = k->f[11];
        m->f54 = k->f[11];
        break;
    case 2: {
        f32 ang;
        m->type = 2;
        PSMTX44Identity(T);
        T[3][0] = k->f[0];
        T[3][1] = lbl_3_rodata_3110 * k->f[1];
        T[3][2] = k->f[2];
        rot.x = T[3][0];
        rot.y = T[3][1];
        rot.z = T[3][2];
        PSMTX44Identity(R);
        memset(&sub, 0, sizeof(CamMtx));
        sub.m[3][3] = lbl_3_rodata_30FC;
        sub.m[2][2] = lbl_3_rodata_30FC;
        sub.m[1][1] = lbl_3_rodata_30FC;
        sub.m[0][0] = lbl_3_rodata_30FC;
        sub.f40 = lbl_3_rodata_30FC;
        fn_3_104B3C(a, key, (s16)trk->target, 0xFF, &sub);
        m->target.x = tgt.x = sub.pos.x;
        m->target.y = tgt.y = sub.pos.y;
        m->target.z = tgt.z = sub.pos.z;
        if (lbl_3_common_bss_DE94[0x9B5] == 1) {
            PSVECSubtract(&rot, &tgt, &rot);
            fn_3_106270(&tgt);
            PSVECAdd(&tgt, &rot, &rot);
            memcpy(&m->pos, &rot, 12);
        } else {
            memcpy(&m->pos, &rot, 12);
        }
        PSVECSubtract(&m->target, &m->pos, &rot);
        m->rx = atan2(-rot.x, -rot.z);
        m->ry = atan2(-rot.z, -rot.y);
        fwd.x = R[1][0];
        fwd.y = R[1][1];
        fwd.z = R[1][2];
        a0.x = sub.m[3][0];
        a0.y = sub.m[3][1];
        a0.z = sub.m[3][2];
        b0.x = T[3][0];
        b0.y = T[3][1];
        b0.z = T[3][2];
        PSVECSubtract(&a0, &b0, &fwd);
        PSVECNormalize(&fwd, &fwd);
        R[1][0] = fwd.x;
        R[1][1] = fwd.y;
        R[1][2] = fwd.z;
        if (lbl_3_rodata_30F8 == fwd.x && lbl_3_rodata_30F8 == fwd.z) {
            rot.y = lbl_3_rodata_30F8;
            rot.x = lbl_3_rodata_30F8;
            rot.z = lbl_3_rodata_30FC;
        } else {
            rot.z = lbl_3_rodata_30F8;
            rot.x = lbl_3_rodata_30F8;
            rot.y = lbl_3_rodata_3110;
        }
        right.x = R[0][0];
        right.y = R[0][1];
        right.z = R[0][2];
        PSVECCrossProduct(&fwd, &rot, &right);
        PSVECNormalize(&right, &right);
        PSVECCrossProduct(&right, &fwd, &up);
        PSVECNormalize(&up, &up);
        R[0][0] = right.x;
        R[0][1] = right.y;
        R[0][2] = right.z;
        R[1][0] = fwd.x;
        R[1][1] = fwd.y;
        R[1][2] = fwd.z;
        R[2][0] = up.x;
        R[2][1] = up.y;
        R[2][2] = up.z;
        ang = k->f[3];
        if (ang >= lbl_3_rodata_30F8) {
            while (FABSF(ang) > lbl_3_rodata_316C) {
                ang -= lbl_3_rodata_3168;
            }
        } else {
            while (FABSF(ang) > lbl_3_rodata_316C) {
                ang += lbl_3_rodata_3168;
            }
        }
        PSMTX44RotRad(rotY, 'Y', -ang);
        PSMTX44Concat(I, rotY, tmp);
        PSMTX44Concat(R, tmp, R);
        PSMTX44Identity(S);
        S[0][0] = k->f[4];
        S[1][1] = k->f[5];
        S[2][2] = k->f[6];
        m->scale.x = k->f[4];
        m->scale.y = k->f[5];
        m->scale.z = k->f[6];
        m->f4C = k->f[8];
        m->f50 = k->f[9];
        m->f54 = k->f[9];
        break;
    }
    }
    PSMTX44Concat(m->m, T, m->m);
    PSMTX44Concat(m->m, R, m->m);
    PSMTX44Concat(m->m, S, m->m);
}
#endif

// .text:0x001054CC size:0x4 mapped:0x80744560
void fn_3_1054CC(void) {
    return;
}

/* TODO type: lbl_3_common_bss_DE94 should become a struct; these name its fields. */
typedef struct { u8 pad[0x124]; s32 n; s32 arr[0x200]; } Z1069;
#define RCAM_N (((Z1069*)lbl_3_common_bss_DE94)->n)
#define RCAM_TBL(i) (((Z1069*)lbl_3_common_bss_DE94)->arr[i])
#define RCAM_KEY(i) ((*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[i])
// .text:0x001054D0 size:0x540 mapped:0x80744564
// NONMATCHING 97.5%: table stores use addi+stwx instead of add+stw 0x128 (see docs/patterns/regalloc.md).
// If `key` (frame << 16 | frac) lands exactly on a key of track `track`, append that key to the camera spline key list
// (+0x9C) and store the frame count until the next key in the table at +0x128.
#if NONMATCHING
void fn_3_1054D0(ReplayAnim* anim, u32 key, s16 track) {
    u16 lo = key;
    u32 frame = key >> 16;
    u8 hit = 0;
    AnimTrack* trk = anim->tracks[track];
    u8* first = trk->keys;
    u16 count = trk->count;
    s32 stride = lbl_3_data_20FC4[trk->type];
    AnimKey* cur = (AnimKey*)(first + (count - 1) * stride);

    if (count == 1) {
        hit = 1;
        RCAM_TBL(RCAM_N) = cur->frame;
    } else if (frame <= cur->frame) {
        if (frame == cur->frame) {
            hit = 1;
            RCAM_TBL(RCAM_N) = cur->frame;
        } else {
            AnimKey* next;
            cur = (AnimKey*)first;
            next = (AnimKey*)(first + stride);
            while ((u32)(next->frame << 16) <= key) {
                cur = next;
                next = (AnimKey*)((u8*)next + stride);
            }
            if (cur->frame == frame && lo == 0) {
                hit = 1;
                RCAM_TBL(RCAM_N) = next->frame - cur->frame;
            }
        }
    }
    if (hit) {
        switch (trk->type) {
        case 0:
            if (*(s32*)(lbl_3_common_bss_DE94 + 0x124) == 1) {
                memcpy(&(*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[0], &cur->pos, 12);
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[1] *= lbl_3_rodata_3178;
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[4] = cur->a - lbl_3_rodata_314C;
                RCAM_TBL(0) = RCAM_TBL(RCAM_N);
            }
            memcpy(&RCAM_KEY(RCAM_N).v[0], &cur->pos, 12);
            RCAM_KEY(RCAM_N).v[1] *= lbl_3_rodata_3178;
            RCAM_KEY(RCAM_N).v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).v[4] = cur->a - lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).frame = frame;
            break;
        case 1:
            if (*(s32*)(lbl_3_common_bss_DE94 + 0x124) == 1) {
                memcpy(&(*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[0], &cur->pos, 12);
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[1] *= lbl_3_rodata_3178;
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[4] = cur->a - lbl_3_rodata_314C;
                RCAM_TBL(0) = RCAM_TBL(RCAM_N);
            }
            memcpy(&RCAM_KEY(RCAM_N).v[0], &cur->pos, 12);
            RCAM_KEY(RCAM_N).v[1] *= lbl_3_rodata_3178;
            RCAM_KEY(RCAM_N).v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).v[4] = cur->a - lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).frame = frame;
            break;
        case 2:
            if (*(s32*)(lbl_3_common_bss_DE94 + 0x124) == 1) {
                memcpy(&(*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[0], &cur->pos, 12);
                (*(SplineKey**)(lbl_3_common_bss_DE94 + 0x9C))[0].v[1] *= lbl_3_rodata_3178;
                RCAM_TBL(0) = RCAM_TBL(RCAM_N);
            }
            memcpy(&RCAM_KEY(RCAM_N).v[0], &cur->pos, 12);
            RCAM_KEY(RCAM_N).v[1] *= lbl_3_rodata_3178;
            RCAM_KEY(RCAM_N).frame = frame;
            break;
        }
        if (RCAM_N < 0x200) {
            RCAM_N += 1;
        }
    }
}
#endif

// .text:0x00105A10 size:0xBC mapped:0x80744AA4
void fn_3_105A10(f32* out, f32* a, f32* b, f32 t) {
    Quaternion r;
    Quaternion va;
    Quaternion vb;
    memcpy(&va, a, 12);
    memcpy(&vb, b, 12);
    r.x = va.x * t + vb.x * (lbl_3_rodata_30FC - t);
    r.y = va.y * t + vb.y * (lbl_3_rodata_30FC - t);
    r.z = va.z * t + vb.z * (lbl_3_rodata_30FC - t);
    memcpy(out, &r, 12);
}

// .text:0x00105ACC size:0x10C mapped:0x80744B60
// NONMATCHING: quaternion (x,y,z,w) -> rotation matrix; original keeps 2x/2z in f31/f30 (different FPR schedule).
#if NONMATCHING
void fn_3_105ACC(f32* q, Mtx out) {
    Mtx44 m;
    f32 x = q[0];
    f32 y = q[1];
    f32 z = q[2];
    f32 w = q[3];
    f32 x2 = x + x;
    f32 y2 = y + y;
    f32 z2 = z + z;
    f32 xx = x * x2;
    f32 yy = y * y2;
    f32 zz = z * z2;
    f32 xy = x * y2;
    f32 xz = x * z2;
    f32 wz = w * z2;
    f32 wy = w * y2;
    f32 yz = y * z2;
    f32 wx = w * x2;
    m[0][0] = lbl_3_rodata_30FC - (yy + zz);
    m[0][1] = xy + wz;
    m[0][2] = xz - wy;
    m[0][3] = lbl_3_rodata_30F8;
    m[1][0] = xy - wz;
    m[1][1] = lbl_3_rodata_30FC - (xx + zz);
    m[1][2] = yz + wx;
    m[1][3] = lbl_3_rodata_30F8;
    m[2][0] = xz + wy;
    m[2][1] = yz - wx;
    m[2][2] = lbl_3_rodata_30FC - (xx + yy);
    m[2][3] = lbl_3_rodata_30F8;
    m[3][0] = lbl_3_rodata_30F8;
    m[3][1] = lbl_3_rodata_30F8;
    m[3][2] = lbl_3_rodata_30F8;
    m[3][3] = lbl_3_rodata_30FC;
    memcpy(out, m, sizeof(Mtx));
}
#endif

// .text:0x00105BD8 size:0x50 mapped:0x80744C6C
void fn_3_105BD8(u8* p) {
    f32 v;
    memset(p, 0, 0x88);
    v = lbl_3_rodata_30FC;
    *(f32*)(p + 0x3C) = v;
    *(f32*)(p + 0x28) = v;
    *(f32*)(p + 0x14) = v;
    *(f32*)(p + 0x00) = v;
    *(f32*)(p + 0x40) = v;
}

// .text:0x00105C28 size:0x5C mapped:0x80744CBC
#pragma dont_inline off
u32 fn_3_105C28(u8* p, u32 key) {
    u16 hi;
    u32 res;
    u16 n;
    u16* tbl;
    u16* e;
    u32 lo;
    u16* last;
    res = 0;
    hi = key >> 16;
    tbl = *(u16**)(p + 8);
    lo = (u16)key;
    n = tbl[0];
    e = tbl + 2;
    do {
        last = e;
        if (e[0] == hi && lo == 0) {
            res = e[1];
        }
        if (*(e += 2) > hi) break;
        n--;
    } while (n != 0);
    return res | (last[1] << 16);
}
#pragma dont_inline on

// .text:0x00105C84 size:0x58 mapped:0x80744D18
#pragma dont_inline off
void fn_3_105C84(u8* p) {
    u32* a;
    s16 i;
    a = (u32*)(p + 8);
    *a += (u32)p;
    for (i = 0; i < *(s16*)(p + 6); i++) {
        a[i + 1] += (u32)p;
    }
    *(u32*)(lbl_3_common_bss_DE94 + 0x11C) = *(u16*)(p + 4) << 16;
}
#pragma dont_inline on

// .text:0x00105CDC size:0x124 mapped:0x80744D70
void fn_3_105CDC(void) {
    extern void fn_3_105E00(s16, s16, s32, s32);
    Vec* arr = *(Vec**)(lbl_3_common_bss_DE94 + 0x98);
    s32 i;
    for (i = 0; i < 1000; i++) {
        Vec* v = &arr[i];
        s32 x, z;
        if (-1000.0 == v->x || -1000.0 == v->y || -1000.0 == v->z) {
            continue;
        }
        x = (s32)v->x * 320 + 320;
        z = (s32)v->z * 224 + 224;
        if (i == 135) {
            i = 135;
        }
        if (i == 5) {
            i = 5;
        }
        fn_3_105E00(x / 50 + 150, -z / 50 + 400, 2, 2);
    }
}

// .text:0x00105E00 size:0x214 mapped:0x80744E94
extern const f32 lbl_3_rodata_3188;
extern const f32 lbl_3_rodata_318C;
extern const f32 lbl_3_rodata_3190;
void fn_3_105E00(s32 x, s32 y, s32 a, s32 b) {
    Mtx44 proj;
    Mtx mv;
    s16 x1 = x + a;
    s16 y1 = y + b;
    C_MTXOrtho(proj, lbl_3_rodata_30F8, lbl_3_rodata_3188, lbl_3_rodata_30F8, lbl_3_rodata_318C, lbl_3_rodata_30F8, lbl_3_rodata_3190);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mv);
    GXLoadPosMtxImm(mv, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGB, GX_RGBA8, 0);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2s16(x, y);
    GXColor4u8(0, 0xFF, 0, 0xC8);
    GXPosition2s16(x1, y);
    GXColor4u8(0, 0xFF, 0, 0xC8);
    GXPosition2s16(x1, y1);
    GXColor4u8(0, 0xFF, 0, 0xC8);
    GXPosition2s16(x, y1);
    GXColor4u8(0, 0xFF, 0, 0xC8);
}

// .text:0x00106014 size:0xC4 mapped:0x807450A8
void fn_3_106014(f32 x, f32 y, f32 z) {
    Vec* t = *(Vec**)(((u8**)&lbl_3_common_bss_DE94)[0] + 0x98);
    s16* n = &lbl_3_bss_B67A;
    s16 c;
    Vec* e;
    c = *n;
    if (c == 0) {
        t[*n].x = x;
        t[*n].y = y;
        t[*n].z = z;
        *n += 1;
        return;
    }
    e = (Vec*)((u8*)t + c * 0xC);
    if (x != e[-1].x && y != e[-1].y && z != e[-1].z) {
        t[c].x = x;
        t[*n].y = y;
        t[*n].z = z;
        if (*n < 1000) {
            *n += 1;
        }
    }
}

// .text:0x001060D8 size:0xA4 mapped:0x8074516C
void fn_3_1060D8(void) {
    u8* p = *(u8**)(((u8**)&lbl_3_common_bss_DE94)[0] + 0x98);
    s32 i;
    lbl_3_bss_B67A = 0;
    for (i = 0; i < 1000; i++) {
        *(f32*)(p + 0) = *(f32*)(p + 4) = *(f32*)(p + 8) = -1000.0f;
        p += 0xC;
    }
}

// .text:0x0010617C size:0xF4 mapped:0x80745210
s32 fn_3_10617C(s32 idx, s32 j, Vec* out) {
    u8* obj;
    Vec v;

    obj = ((u8**)(lbl_8036E548 + 0x2C50))[idx];
    if (obj == NULL) {
        return 0;
    }
    j = ((u16*)(obj + 0x162))[j];
    if (j == 0xFFFF) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        return 0;
    }
    fn_800B2C44(*fn_800111D8(obj), j, &v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    out->x += *(f32*)(obj + 0x34);
    out->y += *(f32*)(obj + 0x38);
    out->z += *(f32*)(obj + 0x3C);
    return 1;
}

// .text:0x00106270 size:0x71C mapped:0x80745304
// NONMATCHING 91%: original recomputes g_Fielders + idx*0x268 per use (offset in r30) and hoists g_Stats; ours keeps the pointer.
// Camera look-at target for the tracked actor (+0x946): 0-8 fielder, 9-12 runner, 13 ball, 14 keep, 15 last.
// The joint position (+0x938) is smoothed by holding it in +0xE8 for a few frames after the target changes.
#if NONMATCHING
void fn_3_106270(Vec* out) {
    s16 idx = *(s16*)(lbl_3_common_bss_DE94 + 0x946);
    Vec j;

    if (idx < 9 && idx >= 0) {
        u8* fl = g_Fielders + idx * 0x268;
        memcpy(out, fl, 12);
        if (*(s16*)(fl + 0x178) != -1) {
            if (((u8**)(lbl_8036E548 + 0x2C50))[idx] != NULL) {
                if (g_Stats[0x36] != 0 && g_Stats[0x3C] == 7) {
                    memset(out, 0, 12);
                    getAnimRelatedCoordinates(idx, 4, out);
                }
                if (*(s32*)(lbl_3_common_bss_DE94 + 0x938) == -1) {
                    *(s32*)(lbl_3_common_bss_DE94 + 0x938) = lbl_3_data_3B4C[*(s16*)(fl + 0x17A)];
                    *(s16*)(lbl_3_common_bss_DE94 + 0x950) = 0;
                }
                memset(&j, 0, 12);
                if (getAnimRelatedCoordinates(idx, *(s32*)(lbl_3_common_bss_DE94 + 0x938), &j) == 0) {
                    memset(&j, 0, 12);
                    getAnimRelatedCoordinates(idx, 4, &j);
                }
                if (lbl_3_common_bss_DE94[0x9B7] == 0) {
                    u8* d = lbl_3_common_bss_DE94;
                    if (*(s32*)(d + 0x938) != *(s32*)(d + 0x93C) || *(s16*)(d + 0x948) != *(s16*)(d + 0x946) ||
                        *(s16*)(d + 0x942) != *(s16*)(d + 0x940) || *(s16*)(d + 0x94E) != *(s16*)(fl + 0x17A)) {
                        *(s16*)(d + 0x950) = 0;
                    }
                    if (*(s16*)(lbl_3_common_bss_DE94 + 0x950) < 1) {
                        memcpy(lbl_3_common_bss_DE94 + 0xE8, &j, 12);
                        *(s16*)(lbl_3_common_bss_DE94 + 0x950) += 1;
                    } else {
                        memcpy(&j, lbl_3_common_bss_DE94 + 0xE8, 12);
                        if (*(s16*)(lbl_3_common_bss_DE94 + 0x950) < 3) {
                            *(s16*)(lbl_3_common_bss_DE94 + 0x950) += 1;
                        }
                    }
                } else {
                    memcpy(lbl_3_common_bss_DE94 + 0xE8, &j, 12);
                }
                if (g_Stats[0x36] != 0 && g_Stats[0x3C] == 7) {
                    out->y = lbl_3_rodata_3110 * out->y + *(f32*)(fl + 0xC) + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].y;
                    out->x += lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].x;
                    out->z += lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].z;
                } else {
                    out->y = lbl_3_rodata_3110 * j.y + *(f32*)(fl + 0xC) + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].y;
                    out->x = j.x + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].x;
                    out->z = j.z + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].z;
                }
            }
        } else {
            /* BUG (original): copies the bytes of the `out` pointer itself, not *out. */
            memcpy(lbl_3_common_bss_DE94 + 0xDC, &out, 12);
        }
        *(s16*)(lbl_3_common_bss_DE94 + 0x94E) = *(s16*)(fl + 0x17A);
    } else if (idx < 13 && idx >= 0) {
        u8* rn = g_Runners + (idx - 9) * 0x154;
        memcpy(out, rn, 12);
        if (*(s16*)(rn + 0xE0) != -1) {
            if (((u8**)(lbl_8036E548 + 0x2C50))[idx] != NULL) {
                u8* d;
                if (*(s32*)(lbl_3_common_bss_DE94 + 0x938) == -1) {
                    *(s32*)(lbl_3_common_bss_DE94 + 0x938) = lbl_3_data_3B4C[*(s16*)(rn + 0xE2)];
                    *(s16*)(lbl_3_common_bss_DE94 + 0x950) = 0;
                }
                memset(&j, 0, 12);
                if (getAnimRelatedCoordinates(idx, *(s32*)(lbl_3_common_bss_DE94 + 0x938), &j) == 0) {
                    memset(&j, 0, 12);
                    getAnimRelatedCoordinates(idx, 4, &j);
                }
                j.x -= ((Vec*)rn)->x;
                j.y -= ((Vec*)rn)->y;
                j.z -= ((Vec*)rn)->z;
                d = lbl_3_common_bss_DE94;
                if (*(s32*)(d + 0x938) != *(s32*)(d + 0x93C) || *(s16*)(d + 0x948) != *(s16*)(d + 0x946) ||
                    *(s16*)(d + 0x942) != *(s16*)(d + 0x940) || *(s16*)(d + 0x94E) != *(s16*)(rn + 0xE2)) {
                    *(s16*)(d + 0x950) = 0;
                }
                if (*(s16*)(lbl_3_common_bss_DE94 + 0x950) < 1) {
                    memcpy(lbl_3_common_bss_DE94 + 0xE8, &j, 12);
                    *(s16*)(lbl_3_common_bss_DE94 + 0x950) += 1;
                } else {
                    memcpy(&j, lbl_3_common_bss_DE94 + 0xE8, 12);
                    if (*(s16*)(lbl_3_common_bss_DE94 + 0x950) < 3) {
                        *(s16*)(lbl_3_common_bss_DE94 + 0x950) += 1;
                    }
                }
                out->y = lbl_3_rodata_3110 * j.y + out->y + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].y;
                out->x = out->x + j.x + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].x;
                out->z = out->z + j.z + lbl_3_data_1DB00[*(s16*)(lbl_3_common_bss_DE94 + 0x94C)].z;
            }
            *(s16*)(lbl_3_common_bss_DE94 + 0x94E) = *(s16*)(rn + 0xE2);
        }
        /* BUG (original): copies the bytes of the `out` pointer itself, not *out. */
        memcpy(lbl_3_common_bss_DE94 + 0xDC, &out, 12);
    } else if (idx == 13) {
        memcpy(out, &g_Ball, 12);
        memcpy(lbl_3_common_bss_DE94 + 0xDC, &g_Ball, 12);
    } else if (idx == 14) {
        memcpy(out, out, 12);
        memcpy(lbl_3_common_bss_DE94 + 0xDC, out, 12);
    } else if (idx == 15) {
        memcpy(out, lbl_3_common_bss_DE94 + 0xDC, 12);
    }
}
#endif

// .text:0x0010698C size:0x24 mapped:0x80745A20
s32 fn_3_10698C(u32* p) {
    s32 n = 0;
    while (*p != 0) {
        p++;
        n++;
    }
    return n;
}

// .text:0x001069B0 size:0x10 mapped:0x80745A44
void* fn_3_1069B0(s32* base, s32 idx) {
    return (u8*)base + base[idx];
}

// .text:0x001069C0 size:0x1E0 mapped:0x80745A54
void fn_3_1069C0(void) {
    s32 i;
    *(s32*)(lbl_3_common_bss_DE94 + 0x124) = 1;
    *(s32*)(lbl_3_common_bss_DE94 + 0x118) = 0;
    *(s32*)(lbl_3_common_bss_DE94 + 0x11C) = 0;
    *(s32*)(lbl_3_common_bss_DE94 + 0x928) = 0;
    for (i = 0; i < 0x200; i++) {
        ((Z1069*)lbl_3_common_bss_DE94)->arr[i] = 0;
    }
    CamsReset();
}

// .text:0x00106BA0 size:0x25C mapped:0x80745C34
void fn_3_106BA0(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        u8* c = g_Camera + i * 0x9BC;
        *(s32*)(c + 0x244) = 1;
        *(s32*)(c + 0x238) = 0;
        *(s32*)(c + 0x23C) = 0;
        *(s16*)(c + 0xA66) = 0xE;
        *(u8*)(c + 0xACE) = 0;
        *(u8*)(c + 0xAD1) = 0;
        *(u8*)(c + 0xACF) = 0;
        *(u8*)(c + 0xAD0) = 0;
        *(s32*)(c + 0xA4C) = 0;
        *(s32*)(c + 0xA48) = 0;
        *(u8*)(c + 0xAD2) = 0;
        *(u8*)(c + 0xAD4) = 0;
        *(u8*)(c + 0xAD3) = 0;
        *(u8*)(c + 0xAD5) = 0;
        *(u8*)(c + 0xAD6) = 0;
        *(u8*)(c + 0xAD7) = 0;
        *(f32*)(c + 0x1F0) = lbl_3_rodata_30F8;
        *(f32*)(c + 0x1F4) = lbl_3_rodata_30F8;
        *(f32*)(c + 0x1F8) = lbl_3_rodata_30F8;
        *(f32*)(c + 0x1E4) = lbl_3_rodata_30F8;
        *(f32*)(c + 0x1E8) = lbl_3_rodata_30F8;
        *(f32*)(c + 0x1EC) = lbl_3_rodata_30FC;
        *(f32*)(c + 0x1FC) = lbl_3_rodata_30FC;
        *(f32*)(c + 0x200) = lbl_3_rodata_30FC;
        *(f32*)(c + 0x204) = lbl_3_rodata_30FC;
        *(f32*)(c + 0x220) = lbl_3_rodata_3198;
        *(f32*)(c + 0x224) = lbl_3_rodata_311C;
        *(f32*)(c + 0x228) = lbl_3_rodata_3134;
        *(f32*)(c + 0x22C) = lbl_3_rodata_30FC;
        *(f32*)(c + 0x230) = lbl_3_rodata_311C;
        *(f32*)(c + 0x234) = lbl_3_rodata_3134;
        *(s16*)(c + 0xA6A) = 0;
        memset(c + 0x248, 0, 0x800);
        memcpy(c + 0x1D8, g_pCamera + 0x284C, 12);
    }
    g_pCamera[0x28A9] = 0;
    CamsReset();
}

// -inline deferred reads this at end of file: lets the GXFifo.h inlines (defined
// before the dont_inline on above) inline; functions defined under "on" do not.
#pragma dont_inline off
