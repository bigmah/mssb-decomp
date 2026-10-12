#include "game/UnknownHomes_Game.h" // g_pCamera, g_Camera, g_Ball, g_Runners, g_Stats, lbl_3_common_bss_DE94, ...
#include "static/GameSettings.h"
#include "main/file_80011640.h" // CharMgr lbl_8036E548
#include "main/file_80008E00.h" // lbl_80366158
#include "main/file_80069BDC.h" // SceneTask lbl_803CC1B8
#include "game/rep_1188.h"      // InMemFielderView
#include "game/auto_00_000249E8_text.h" // SceneWork, SceneActorSetup
#include "game/auto_00_00097144_text.h" // GameHudFlags lbl_3_common_bss_32724
#include "main/file_8001FE00.h" // SceneFade lbl_8037169C
#include "game/rep_3090.h"
#define REP_HEADER_FN repHeader_3090
#include "header_rep_inline.h"
#include "Dolphin/mtxext.h"
#include "Dolphin/GX.h"

extern Vec lbl_3_data_21004;
extern s32 lbl_3_data_20FC4[]; /* ReplayAnimKey stride per ReplayAnimTrack type */
extern s32 lbl_3_data_20FD0[]; /* number of Vec3 groups per ReplayAnimKey, per ReplayAnimTrack type */
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

extern f32 fn_3_9FEA8(f32);
extern s16 fn_3_9FF04(f32);
extern f64 cos(f64);
extern f64 sin(f64);
extern V3U lbl_3_rodata_30EC; /* (0, 1, 0) */
// .bss (laid out last-defined-first)
static u8 lbl_3_bss_B67C[0x1C]; // unused
static s16 lbl_3_bss_B67A;
static u8 lbl_3_bss_B678[0x2]; // unused
extern void* memset(void*, int, size_t);
extern void* memcpy(void*, const void*, size_t);
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
extern void fn_800B2C44(void*, u16, Vec*);
extern InMemFielderView g_Fielders[9];
extern s32 lbl_3_data_3B4C[]; /* per-character joint index */
extern Vec lbl_3_data_1DB00[];
extern BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out);
extern void fn_800B0A14_removeQueue(void*);
#pragma dont_inline on

/* The replay camera view being updated (one of g_Camera.views[]). */
#define CAMV (lbl_3_common_bss_DE94._0000)
/* The camera shifted by i views, so that ->views[0] is cam->views[i]. Some functions address the
   views from the camera base this way. */
#define CAM_SHIFTED(cam, i) ((inMemCamera*)((ReplayCamView*)(cam) + (i)))
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
        CAMV = &g_Camera.views[i];
        n = 0;
        l = g_pCamera->views[0].animList;
        while (*l != 0) {
            l++;
            n++;
        }
        CAMV->nAnims = n;
        memcpy(CAMV->animData, (u8*)g_pCamera->views[0].animList + g_pCamera->views[0].animList[CAMV->anim], 0x8000);
        CAMV->nSplineKeys = 1;
        CAMV->frame = 0;
        CAMV->frameEnd = 0;
        CAMV->_0928 = 0;
        ZeroTbl();
        CamsResetUp();
        fn_3_105C84(CAMV->animData);
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
        CAMV->segLen[j] = 0;
    }
}
void fn_3_FC938(void) {
    u32* l;
    s32 n;
    n = 0;
    l = g_pCamera->views[0].animList;
    while (*l != 0) {
        l++;
        n++;
    }
    CAMV->nAnims = n;
    memcpy(CAMV->animData, (u8*)g_pCamera->views[0].animList + g_pCamera->views[0].animList[CAMV->anim], 0x8000);
    CAMV->nSplineKeys = 1;
    CAMV->frame = 0;
    CAMV->frameEnd = 0;
    CAMV->_0928 = 0;
    ZeroTbl();
    CamsResetUp();
    fn_3_105C84(CAMV->animData);
    CamApplyScriptFrame();
    fn_3_101CC4();
}
#pragma dont_inline on

// .text:0x000FCE38 size:0x74 mapped:0x8073BECC
// NONMATCHING 95%: only the out-of-line loop-2 preheader (slwi r6,r3,6 after the final blr, dead `b` left behind) differs
// (see docs/patterns/unsolved.md). Moves path index i so that path[i-1].t < t <= path[i].t.
#if NONMATCHING
s32 fn_3_FCE38(s32 i, f32 t) {
    ReplayCamView* d = CAMV;
    s32 n = d->path.nPts;
    while (i < n && t > (d->path.pts)[i].t) {
        i++;
    }
    while (i > 0 && t <= (d->path.pts)[i - 1].t) {
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
    ReplayCamView* d = CAMV;
    s32 i = 0;
    s32 n;
    if (t < 0.0) {
        return -1;
    }
    n = d->path.nPts;
    while (i < n && t > (d->path.pts)[i].t) {
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
    for (i = 0; i < CAMV->path.nKeys - 3; i++) {
        SplineCtrl* c;
        s32 j;
        s32 k;
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 5; k++) {
                (CAMV->path.ctrl)[i + j].v[k] = (CAMV->keys)[i + j].v[k];
            }
        }
        CAMV->path.segSamples = CAMV->segLen[i];
        c = &(CAMV->path.ctrl)[i];
        if (c[1].v[0] == c[2].v[0] && c[2].v[0] == c[3].v[0] && c[1].v[1] == c[2].v[1] && c[2].v[1] == c[3].v[1] &&
            c[1].v[2] == c[2].v[2] && c[2].v[2] == c[3].v[2]) {
            CAMV->segLen[i] = 0;
            CAMV->path.segSamples = 0;
        }
        for (j = 0; j < CAMV->path.segSamples; j++) {
            f32 t = (f32)j / (f32)CAMV->path.segSamples;
            f32 t2 = t * t;
            f32 t3 = t2 * t;
            f32* out = (f32*)&(CAMV->path.pts)[total];
            if (CAMV->path.mode == 0) {
                f32 w0 = -1.0f * t3 + 3.0f * t2 - 3.0f * t + 1.0f;
                f32 w1 = 3.0f * t3 - 6.0f * t2 + 4.0f;
                f32 w2 = -3.0f * t3 + 3.0f * t2 + 3.0f * t + 1.0f;
                f32 w3 = t3;
                for (k = 0; k < 5; k++) {
                    c = &(CAMV->path.ctrl)[i];
                    out[k] = (w0 * c[0].v[k] + w1 * c[1].v[k] + w2 * c[2].v[k] + w3 * c[3].v[k]) / 6.0f;
                }
            } else {
                f32 w0 = -1.0f * t3 + 2.0f * t2 - t;
                f32 w1 = 3.0f * t3 - 5.0f * t2 + 2.0f;
                f32 w2 = -3.0f * t3 + 4.0f * t2 + t;
                f32 w3 = t3 - t2;
                for (k = 0; k < 5; k++) {
                    c = &(CAMV->path.ctrl)[i];
                    out[k] = (w0 * c[0].v[k] + w1 * c[1].v[k] + w2 * c[2].v[k] + w3 * c[3].v[k]) * 0.5f;
                }
            }
            total++;
        }
    }
    CAMV->path.nPts = total;
}
#endif

// .text:0x000FD408 size:0xD4 mapped:0x8073C49C
void fn_3_FD408(u32 i, void* out, f32* uv) {
    ReplayCamView* d = CAMV;
    if (d->path.nPts > i) {
        memcpy(out, &(d->path.pts)[i], 12);
        uv[0] = (d->path.pts)[i].u;
        uv[1] = (d->path.pts)[i].v;
    } else {
        memcpy(out, &(d->path.pts)[d->path.nPts - 1], 12);
        uv[0] = (d->path.pts)[d->path.nPts - 1].u;
        uv[1] = (d->path.pts)[d->path.nPts - 1].v;
    }
}

// .text:0x000FD4DC size:0x40 mapped:0x8073C570
void fn_3_FD4DC(void) {
    ReplayCamView* d = CAMV;
    if ((d->frame >> 16) == 0) {
        d->path.nKeys = d->nSplineKeys;
    }
    fn_3_FCF24();
}

// .text:0x000FD51C size:0x8C mapped:0x8073C5B0
void fn_3_FD51C(s32 i) {
    inMemCamera* c = CAM_SHIFTED(&g_Camera, i);
    ReplayCamPath* p;
    V3U v = lbl_3_rodata_30EC;
    c->views[0].path.nKeys = 0;
    c->views[0].path._08 = 0;
    p = &c->views[0].path;
    p->up.w = v;
    p->segSamples = 0;
    p->nPts = 0;
    p->_24 = 0;
    p->mode = 0;
    p->_2C = 0.0f;
    p->_30 = 0;
    p->_34 = 0;
    p->_38 = 0;
    p->_3C = 0;
    p->_40 = 0;
    p->_44 = 0.0f;
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
static inline void CamSubInit(ReplayCamPath* p, V3U* v) {
    p->nKeys = 0;
    p->_08 = 0;
    p->up.w = *v;
    p->segSamples = 0;
    p->nPts = 0;
    p->_24 = 0;
    p->mode = 0;
    p->_2C = 0.0f;
    p->_30 = 0;
    p->_34 = 0;
    p->_38 = 0;
    p->_3C = 0;
    p->_40 = 0;
    p->_44 = 0.0f;
}
static inline void CamSubInitUp(ReplayCamPath* p, Vec* v) {
    p->nKeys = 0;
    p->_08 = 0;
    p->up.v = *v;
    p->segSamples = 0;
    p->nPts = 0;
    p->_24 = 0;
    p->mode = 0;
    p->_2C = lbl_3_rodata_30F8;
    p->_30 = 0;
    p->_34 = 0;
    p->_38 = 0;
    p->_3C = 0;
    p->_40 = 0;
    p->_44 = lbl_3_rodata_30F8;
}
static inline void CamsResetUp(void) {
    s32 i;
    Vec v = {0.0f, 1.0f, 0.0f};
    for (i = 0; i < 2; i++) {
        CamSubInitUp(&g_Camera.views[i].path, &v);
    }
}
static inline void CamApplyScriptFrame(void) {
    CamMtx m;
    CamFrame o;
    Vec* p0c;
    Vec* p18;
    Vec va;
    Vec vb;
    s32 b = CAMV->frame;
    ReplayAnim* a = CAMV->animData;
    memset(&m, 0, sizeof(CamMtx));
    m.m[3][3] = lbl_3_rodata_30FC;
    m.m[2][2] = lbl_3_rodata_30FC;
    m.m[1][1] = lbl_3_rodata_30FC;
    m.m[0][0] = lbl_3_rodata_30FC;
    m.f40 = lbl_3_rodata_30FC;
    fn_3_104B3C(a, b, 0, 0, &m);
    memcpy(&o.pos, &m.pos, 12);
    p0c = &o.target;
    memcpy(p0c, &m.target, 12);
    memcpy(&o.scale, &m.scale, 12);
    o.fov = m.f4C;
    p18 = &o.up;
    PSMTX44MultVec(m.m, &s_axa, p18);
    PSVECNormalize(p18, p18);
    va = o.fwd;
    PSMTX44MultVec(m.m, &s_axb, &va);
    PSVECNormalize(&va, &va);
    vb = o.back;
    PSMTX44MultVec(m.m, &s_axc, &vb);
    PSVECNormalize(&vb, &vb);
    o.rx = m.rx;
    o.ry = m.ry;
    o.type = m.type;
    memcpy(&CAMV->eye, &o.pos, 12);
    CAMV->_00A0 = o.fov;
    CAMV->rx = o.rx;
    CAMV->ry = o.ry;
    CAMV->type = o.type;
    memcpy(&CAMV->target, p0c, 12);
    g_pCamera->_2858.x = o.pos.x;
    g_pCamera->_2858.y = o.pos.y;
    g_pCamera->_2858.z = o.pos.z;
    g_pCamera->_2870 = o.rx;
    g_pCamera->_2874 = o.ry;
    g_pCamera->_289C = fn_3_9FF04(fn_3_9FEA8(g_pCamera->_2870));
    g_pCamera->_289C = fn_3_9FF04(fn_3_9FEA8(g_pCamera->_2870));
    g_pCamera->_2878 = lbl_3_rodata_30FC;
}
static inline void CamsReset(void) {
    s32 i;
    V3U v = lbl_3_rodata_30EC;
    for (i = 0; i < 2; i++) {
        CamSubInit(&CAM_SHIFTED(&g_Camera, i)->views[0].path, &v);
    }
}
#pragma dont_inline on

// .text:0x000FD5A8 size:0xC8 mapped:0x8073C63C
void fn_3_FD5A8(void) {
    s32 i;
    V3U v = lbl_3_rodata_30EC;
    for (i = 0; i < 2; i++) {
        ReplayCamPath* p;
        g_Camera.views[i].path.nKeys = 0;
        g_Camera.views[i].path._08 = 0;
        p = &g_Camera.views[i].path;
        p->up.w = v;
        p->segSamples = 0;
        p->nPts = 0;
        p->_24 = 0;
        p->mode = 0;
        p->_2C = 0.0f;
        p->_30 = 0;
        p->_34 = 0;
        p->_38 = 0;
        p->_3C = 0;
        p->_40 = 0;
        p->_44 = 0.0f;
    }
}

// .text:0x000FD670 size:0x38C mapped:0x8073C704
// fn_3_105C28 is inlined here (result unused).
void fn_3_FD670(void) {
    ReplayCamView* d;
    if (g_GameLogic.framesOfExitingToMenu != 0) {
        return;
    }
    CamApplyScriptFrame();
    fn_3_1000D8();
    CAMV->jointPrev = CAMV->joint;
    CAMV->trackPrev = CAMV->track;
    CAMV->animPrev = CAMV->anim;
    d = CAMV;
    switch (d->_0944) {
    case 0:
        if (d->_09AE != 0) {
            if (fn_3_FDB30() != 0) {
                CAMV->_09AE = 0;
                CAMV->_09AF = 0;
                CAMV->_09B0 = 0;
            }
        } else if (d->_09AD == 1) {
            fn_3_105C28(d->animData, d->frame);
            if (d->frame >= d->frameEnd - 1) {
                d->_09AD = 0;
            } else {
                d->frame += 0x10000;
            }
        }
        break;
    case 1:
        if (d->_09AE == 0) {
            d->_0944 = 0;
        }
        break;
    }
}

// .text:0x000FD9FC size:0x20 mapped:0x8073CA90
s32 fn_3_FD9FC(void) {
    return CAMV->_0018 == 1;
}

// .text:0x000FDA1C size:0x114 mapped:0x8073CAB0
void fn_3_FDA1C(void) {
    ModelLoadTask* p = (ModelLoadTask*)lbl_803CC1B8;
    u16 i;
    CharActor* model;
    SceneTask* parent;

    switch (p->state) {
    case 0:
        p->state = 1;
        break;
    case 1:
        i = p->idx;
        model = lbl_8036E548.active[i];
        if (((InMemFielderView*)g_Fielders)[i].opponentIdx == 0) {
            if (i < 9) {
                p->idx = i + 1;
                p->state = 0;
            } else {
                p->state = 2;
            }
        } else if (model == NULL || LoadModel(model)) {
            if (p->idx < 9) {
                p->idx = p->idx + 1;
                p->state = 0;
            } else {
                p->state = 2;
            }
        }
        break;
    case 2:
        parent = p->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        p->state = 0;
        break;
    }
}

// .text:0x000FDB30 size:0x24E8 mapped:0x8073CBC4
// NONMATCHING 76% (scored with fn_3_100038/SetCamAnim/FindTeamActor inlined as in the original; call sequence identical):
// addressing modes, unrolled actor loops and register allocation differ. The original reaches the script tables through
// the pooled .data base lbl_3_data_1C0A8 (+0x18D8, +0x238C, +0x30E4, +0x3148, +0x3220, +0x32F8, +0x4D64).
// Replay camera script interpreter. The script (s32 words at *(s32**)(d + 0)) is run until a command waits for a
// frame; returns 1 when the script ends (command 2), else 0. "Tick" (fn_3_100038, inlined in the original) advances
// the camera animation frame. d + 0x4/0xC/0x10 hold a loop (0x43/0x44), d + 0x8/0x14 wait counters.
#if NONMATCHING
extern SceneWork* lbl_3_common_bss_1323C;
extern s32* lbl_3_data_20E0C[];        /* script table (pooled at lbl_3_data_1C0A8 + 0x4D64) */
extern s32* lbl_3_data_1D980[];        /* camera animation lists (lbl_3_data_1C0A8 + 0x18D8) */
extern ScenePlacement lbl_3_data_1F18C[]; /* (+0x30E4) */
extern f32 lbl_3_data_1F1F0[];         /* per character kind (+0x3148) */
extern f32 lbl_3_data_1F2C8[];         /* per character kind (+0x3220) */
extern SceneActorSetup lbl_3_data_1E434[]; /* (+0x238C) */
extern f32 lbl_3_data_1F3A0[];         /* per star mission (+0x32F8) */
extern s32 lbl_3_data_37AC[];
extern s32 lbl_3_data_3888[];
extern s32 lbl_3_data_3964[];
extern s32 lbl_3_data_3A40[];
extern s32 lbl_3_data_3B1C[];
extern s32 lbl_3_data_3B34[];
extern int random_fn_3_9EE24(int max);
extern void fn_80052798(s32 count);
extern void fn_3_24ADC(s32 idx, s32 queued);
extern void fn_3_249E8(s32 idx);
extern void fn_3_7BC0C(void);
extern void fn_3_7BBF8(void);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority);
extern void fn_3_21C90(void);
extern void fn_3_21DE4(void);
extern void fn_3_21C7C(s32 idx, s32 value);
extern s32 fn_3_2281C(s32 i);
extern s32 fn_3_2273C(void);
extern void fn_3_BBBC4(void);
extern void fn_3_BA150(void);
extern void fn_80011358(s32 index, s32 kind);
extern void fn_3_219CC(void);
extern void changeScene(s32 scene, s32 state);
extern void fn_8001CA40(u8 stadium);

#define SCR (d->script)
#define SCENE lbl_3_common_bss_1323C
#define ACTOR(i) (lbl_8036E548.active[i])
#define FRAME (g_Stats.playFrameCounter)
#define CAM_SEL (&CAM_SHIFTED(g_pCamera, g_pCamera->_28A8)->views[0])

/* Tick, then continue once the play frame equals the event frame `field` of the view plus the argument. */
#define WAIT_EVENT(field) \
    fn_3_100038(); \
    p = SCR; \
    if (FRAME == CAMV->field + p[1]) { \
        SCR = p + 2; \
        continue; \
    } \
    return 0

/* Index (0-8) of the last actor on the human team's captain's team. */
static s16 FindTeamActor(void) {
    s16 found = 0;
    s16 i;
    for (i = 0; i < 9; i++) {
        if (g_GameLogic.Team_CaptainRosterLoc[g_d_GameSettings.humanTeamNumber] == (s8)ACTOR(i)->roster) {
            found = i;
        }
    }
    return found;
}

static void SetCamAnim(s16 anim) {
    CAMV->anim = anim;
    CAMV->frame = 0;
    fn_3_FC938();
}

s32 fn_3_FDB30(void) {
    SceneTask* task = lbl_803CC1B8;
    ReplayCamView* d = CAMV;
    u8 starIdx = gChallengeState._441C;
    u8 starKind = gChallengeState._4415;
    s32* p;

    g_pCamera->views[0]._0952 += 1;
    if (g_pCamera->views[0]._0952 == 10000) {
        g_pCamera->views[0]._0952 = 0;
    }
    if (d->_0008 != 0) {
        d->_0008 -= 1;
        fn_3_100038();
        return 0;
    }
    if (d->_0014 != 0) {
        d->_0014 -= 1;
        fn_3_100038();
        return 0;
    }

    for (;;) {
        p = SCR;
        switch (p[0]) {
        case 0x01: {
            ReplayCamView* c = CAM_SEL;
            c->_0118 = 0;
            c->frameEnd = 0;
            c->track = 0xE;
            c->eyeW[0] = 9.0f;
            c->eyeW[1] = 2.0f;
            c->eyeW[2] = 0.001f;
            c->tgtW[0] = 9.0f;
            c->tgtW[1] = 2.0f;
            c->tgtW[2] = 0.001f;
            c->rand = random_fn_3_9EE24(0x10000);
            c->_0988 = 0;
            c->_09B2 = 0;
            c->smooth = 0;
            c->_09B3 = 0;
            c->lookAtMode = 0;
            c->orbit = 0;
            c->ballCam = 0;
            c->joint = -1;
            c->jointPrev = c->joint;
            c->offsetIdx = 0;
            c->_09B9 = 0;
            c->_09B7 = 0;
            c->_0018 = 0;
            g_pCamera->views[0]._0952 = 0;
            SCR += 1;
            continue;
        }
        case 0x02:
            if (g_Stats.replayInd != 0) {
                g_Stats._39 = 5;
            } else if (SCENE->mode == 2) {
                s16 v = SCENE->_23E - 0x5C;
                if (SCENE->_23C < v) {
                    SCENE->_23C = v;
                }
            } else {
                s16 v = SCENE->_23E - 8;
                if (SCENE->_23C < v) {
                    SCENE->_23C = v;
                }
            }
            CAM_SEL->_09B9 = 0;
            fn_80052798(1);
            lbl_3_common_bss_32724._AD = 0;
            d->_0018 = 1;
            return 1;
        case 0x03:
            fn_3_100038();
            d->_0008 = SCR[1];
            SCR += 2;
            return 0;
        case 0x62:
            fn_3_100038();
            d->_0008 = SCR[1];
            SCR += 2;
            return 0;
        case 0x04:
            if (CAMV->frame > CAMV->frameEnd) {
                SCR = p + 1;
                continue;
            }
            CAMV->frame += 0x10000;
            return 0;
        case 0x05:
            SetCamAnim(p[1]);
            SCR += 2;
            continue;
        case 0x26:
            SetCamAnim(g_Batter.batterHand == 1 ? p[1] : p[2]);
            SCR += 3;
            continue;
        case 0x25:
            SetCamAnim(CAMV->_0986 > 1000 ? p[1] : p[2]);
            SCR += 3;
            continue;
        case 0x06:
            CAMV->orbit = 0;
            CAMV->lookAtMode = 0;
            CAMV->track = SCR[1];
            SCR += 2;
            continue;
        case 0x1E:
            CAMV->orbit = 0;
            CAMV->lookAtMode = 1;
            CAMV->track = SCR[1];
            SCR += 2;
            continue;
        case 0x1F:
            CAMV->orbit = 1;
            CAMV->lookAtMode = 1;
            CAMV->track = SCR[1];
            SCR += 2;
            continue;
        case 0x18:
            CAMV->orbit = 0;
            CAMV->track = 9;
            SCR += 1;
            continue;
        case 0x21:
            CAMV->orbit = 0;
            CAMV->lookAtMode = 1;
            CAMV->track = lbl_3_common_bss_32A94.plays[0].fielder;
            SCR += 1;
            continue;
        case 0x07:
            CAMV->loop = p[1];
            SCR += 2;
            continue;
        case 0x08:
            CAMV->_09B2 = p[1];
            SCR += 2;
            continue;
        case 0x09:
            CAMV->smooth = p[1];
            SCR += 2;
            continue;
        case 0x0A:
            CAMV->_09B3 = p[1];
            SCR += 2;
            continue;
        case 0x0B:
            CAMV->lookAtMode = p[1];
            SCR += 2;
            continue;
        case 0x0C:
            CAMV->eyeW[0] = (f32)p[1] / 1000.0f;
            CAMV->eyeW[1] = (f32)SCR[2] / 1000.0f;
            CAMV->eyeW[2] = (f32)SCR[3] / 1000.0f;
            SCR += 4;
            continue;
        case 0x0D:
            CAMV->tgtW[0] = (f32)p[1] / 1000.0f;
            CAMV->tgtW[1] = (f32)SCR[2] / 1000.0f;
            CAMV->tgtW[2] = (f32)SCR[3] / 1000.0f;
            SCR += 4;
            continue;
        case 0x0E: {
            s32* list = lbl_3_data_1D980[p[1]];
            SetCamAnim(list[random_fn_3_9EE24(p[2])]);
            SCR += 3;
            continue;
        }
        case 0x23: {
            s32* list = CAMV->_0986 > 1000 ? lbl_3_data_1D980[p[1]] : lbl_3_data_1D980[p[2]];
            SetCamAnim(list[random_fn_3_9EE24(p[3])]);
            SCR += 4;
            continue;
        }
        case 0x24: {
            s32* list = g_Batter.batterHand == 1 ? lbl_3_data_1D980[p[1]] : lbl_3_data_1D980[p[2]];
            SetCamAnim(list[random_fn_3_9EE24(p[3])]);
            SCR += 4;
            continue;
        }
        /* Wait until the play frame reaches a recorded event frame (+0x954..) plus an offset. */
        case 0x0F:
            WAIT_EVENT(_0954);
        case 0x10:
            WAIT_EVENT(_0956);
        case 0x11:
            WAIT_EVENT(_0958);
        case 0x12:
            WAIT_EVENT(_095A);
        case 0x13:
            WAIT_EVENT(_095E);
        case 0x14:
            WAIT_EVENT(_0960);
        case 0x15:
            WAIT_EVENT(_0962);
        case 0x1A:
            WAIT_EVENT(_0974);
        case 0x1B:
            WAIT_EVENT(_0976);
        case 0x22:
            WAIT_EVENT(_097C);
        case 0x3C:
            WAIT_EVENT(_0984);
        case 0x16:
            fn_3_100038();
            p = SCR;
            if (FRAME == CAMV->_099B[p[1]] + p[2]) {
                SCR = p + 3;
                continue;
            }
            return 0;
        case 0x17:
            fn_3_100038();
            d->_0014 = SCR[1];
            SCR += 2;
            return 0;
        case 0x19: {
            u8 k;
            fn_3_100038();
            p = SCR;
            k = CAMV->_099F;
            if (FRAME == CAMV->_096C[k] + p[1]) {
                SCR = p + 2;
                continue;
            }
            if (k == 3) {
                SCR = p + 2;
                continue;
            }
            return 0;
        }
        case 0x4C:
            CAMV->orbit = 0;
            CAMV->lookAtMode = 0;
            if (CAMV->_099F == 1) {
                CAMV->track = 10;
            } else {
                CAMV->track = 11;
            }
            SCR += 1;
            continue;
        case 0x1C:
            SCR = p + 4;
            return 0;
        case 0x1D:
            if (CAMV->_099F == 3) {
                SCR = lbl_3_data_20E0C[p[1]];
            } else {
                SCR = p + 2;
            }
            continue;
        case 0x20:
            if (CAMV->_0962 != 0) {
                SCR = lbl_3_data_20E0C[p[1]];
            } else {
                SCR = p + 2;
            }
            continue;
        case 0x27:
            g_pCamera->views[0]._0952 = 0;
            SCENE->_23E = SCR[1];
            SCR += 2;
            continue;
        case 0x28:
            fn_3_24ADC(p[1], 0);
            SCR += 2;
            continue;
        case 0x64:
            fn_3_24ADC(p[1], 1);
            SCR += 2;
            continue;
        case 0x3E:
            if (g_Batter.batterHand == 1) {
                fn_3_24ADC(p[1], 0);
                SCR += 3;
            } else {
                fn_3_24ADC(p[2], 0);
                SCR += 3;
            }
            continue;
        case 0x29:
            fn_3_100038();
            if (SCENE->_23E - 1 == SCENE->_23C) {
                if (g_pCamera->views[0]._098A == 0) {
                    g_pCamera->views[0]._098A = 1;
                    g_pCamera->views[0]._098E = 2;
                    fn_800B0A5C_insertQueue((void*)fn_3_21DE4, 6);
                }
                SCR += 1;
                continue;
            }
            return 0;
        case 0x2A:
            fn_3_7BC0C();
            SCR += 1;
            continue;
        case 0x2B:
            fn_3_7BBF8();
            SCR += 1;
            continue;
        case 0x2C:
            SCR = p + 2;
            continue;
        case 0x46: {
            ScenePlacement* rec = &lbl_3_data_1F18C[SCR[1]];
            SceneActorState* st;
            SCENE->_27F = 1;
            st = &SCENE->actors[rec->actor];
            st->arrived = 0;
            st->moving = 1;
            st->speed = rec->speed;
            memcpy(&st->pos, &rec->pos, 12);
            SCR += 2;
            continue;
        }
        case 0x63: {
            ScenePlacement* rec;
            SceneActorState* st;
            CharActor* actor;
            SCENE->_27F = 2;
            rec = &lbl_3_data_1F18C[SCR[1]];
            actor = ACTOR(rec->actor);
            st = &SCENE->actors[rec->actor];
            st->arrived = 0;
            st->moving = 1;
            st->speed = lbl_3_data_1F1F0[actor->kind];
            memcpy(&st->pos, &rec->pos, 12);
            SCR += 2;
            continue;
        }
        case 0x66: {
            ScenePlacement* rec;
            CharActor* actor;
            SCENE->_27F = 3;
            rec = &lbl_3_data_1F18C[SCR[1]];
            actor = ACTOR(rec->actor);
            if (actor != NULL) {
                SceneActorState* st = &SCENE->actors[rec->actor];
                f32 n;
                st->arrived = 0;
                st->moving = 1;
                memcpy(&st->pos, &rec->pos, 12);
                st->_18 = 0.3f + FABSF(PSVECDistance(&st->pos, &actor->pos));
                n = actor->_068 / 2;
                if (0.0f == n) {
                    n = 1.0f;
                }
                st->speed = st->_18 / n;
                st->_20 = n;
                st->_1C = lbl_3_data_1F2C8[actor->kind];
            }
            SCR += 2;
            continue;
        }
        case 0x2D:
            SCR = lbl_3_data_20E0C[p[1]];
            continue;
        case 0x2E:
            CAMV->rand = random_fn_3_9EE24(0x10000);
            SCR += 1;
            continue;
        case 0x2F:
            SetCamAnim(lbl_3_data_1D980[p[1] + CAMV->rand % p[2]][p[3]]);
            SCR += 4;
            continue;
        case 0x30:
            if (g_pCamera->views[0]._0988 == 0) {
                g_pCamera->views[0]._0988 = 1;
                g_pCamera->views[0]._098C = SCR[1];
                fn_800B0A5C_insertQueue((void*)fn_3_21C90, 6);
            }
            SCR += 2;
            continue;
        case 0x68:
            if (g_pCamera->views[0]._098A == 0) {
                g_pCamera->views[0]._098A = 1;
                g_pCamera->views[0]._098E = SCR[1];
                fn_800B0A5C_insertQueue((void*)fn_3_21DE4, 6);
            }
            SCR += 2;
            continue;
        case 0x31: {
            s32 base = g_Batter.batterHand == 1 ? p[1] : p[2];
            SetCamAnim(lbl_3_data_1D980[base + CAMV->rand % p[3]][p[4]]);
            SCR += 5;
            continue;
        }
        case 0x32:
            fn_3_100038();
            if (CAMV->frame > 0x30000 && fn_3_2281C(SCR[1]) != 0) {
                SCR += 2;
                continue;
            }
            return 0;
        case 0x4D:
            fn_3_100038();
            if (CAMV->frame > 0x30000 && fn_3_2273C() != 0) { /* the original passes SCR[1] (unused) */
                SCR += 2;
                continue;
            }
            return 0;
        case 0x33:
            fn_3_21C7C(p[1], p[2]);
            SCR += 3;
            continue;
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
            CAMV->ballCam = p[1];
            CAMV->track = 13;
            CAMV->smooth = 0;
            switch (SCR[0]) {
            case 0x34: CAMV->ballMode = 0; break;
            case 0x35: CAMV->ballMode = 1; break;
            case 0x36: CAMV->ballMode = 2; break;
            case 0x37: CAMV->ballMode = 3; break;
            }
            SCR += 2;
            continue;
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3D:
            CAMV->orbit = 0;
            CAMV->lookAtMode = 1;
            CAMV->track = 13;
            CAMV->ballCam = SCR[1];
            CAMV->track = 13;
            switch (SCR[0]) {
            case 0x38: CAMV->ballMode = 4; break;
            case 0x39: CAMV->ballMode = 5; break;
            case 0x3A: CAMV->ballMode = 6; break;
            case 0x3B: CAMV->ballMode = 7; break;
            case 0x3D: CAMV->ballMode = 8; break;
            }
            SCR += 2;
            continue;
        case 0x3F: {
            s16 idx = CAMV->track;
            if (idx < 9 && idx >= 0) {
                CAMV->joint = lbl_3_data_3B4C[g_Fielders[idx].charID];
            } else if (idx < 13 && idx >= 0) {
                CAMV->joint = lbl_3_data_3B4C[g_Runners[idx - 9].charID];
            }
            SCR += 2;
            continue;
        }
        case 0x57:
            CAMV->joint = lbl_3_data_3B4C[g_Fielders[p[1]].charID];
            SCR += 2;
            continue;
        case 0x40:
            CAMV->_09B9 = p[1];
            if (CAMV->_09B9 == 1) {
                fn_80052798(2);
                lbl_3_common_bss_32724._AD = 1;
            } else {
                fn_80052798(1);
                lbl_3_common_bss_32724._AD = 0;
            }
            SCR += 2;
            continue;
        case 0x41:
        case 0x42: {
            s32 a;
            s32 b;
            CAMV->_09B9 = 1;
            if (SCR[2] >= 0) {
                fn_80052798(2);
                lbl_3_common_bss_32724._AD = 1;
            } else {
                fn_80052798(1);
                lbl_3_common_bss_32724._AD = 0;
            }
            p = SCR;
            if (p[0] == 0x41) {
                a = p[1];
                b = p[2];
            } else if (g_Batter.batterHand == 1) {
                a = p[1];
                b = p[2];
            } else {
                a = p[3];
                b = p[4];
            }
            /* Start the two-view script pair: view 1 runs script b, view 0 runs script a. */
            g_pCamera->views[1]._09AB = 1;
            g_pCamera->views[1]._09AC = 1;
            g_pCamera->views[1]._09AF = 1;
            g_pCamera->views[1]._09B0 = 1;
            g_pCamera->views[1]._0018 = 0;
            g_pCamera->views[1]._0008 = 0;
            g_pCamera->views[1]._0014 = 0;
            g_pCamera->views[1]._092C = b;
            g_pCamera->views[1]._09AE = 1;
            g_pCamera->views[1]._0118 = 0;
            g_pCamera->views[1]._0944 = 0;
            g_pCamera->views[1].script = lbl_3_data_20E0C[b];
            g_pCamera->views[0].script = lbl_3_data_20E0C[a];
            g_pCamera->_28A9 = 1;
            return 0;
        }
        case 0x43:
            d->loopCount = p[1];
            d->loopIter = 0;
            d->loopStart = SCR + 2;
            SCR += 2;
            continue;
        case 0x44:
            if (d->loopCount == -1) {
                SCR = d->loopStart;
            } else if (d->loopIter == d->loopCount) {
                SCR = p + 1;
            } else {
                d->loopIter += 1;
                SCR = d->loopStart;
            }
            continue;
        case 0x45: {
            s32 n;
            fn_3_100038();
            p = SCR;
            n = p[1];
            if (ACTOR(n) == NULL) {
                SCR = p + 2;
                continue;
            }
            if (SCENE->actors[n].arrived == 1) {
                SCENE->_27F = 0;
                SCR += 2;
                continue;
            }
            return 0;
        }
        case 0x47:
            if (g_Ball.landingSpotZoneAwayFromHome <= 1) {
                SCR = lbl_3_data_20E0C[p[1]];
            } else {
                SCR = p + 2;
            }
            continue;
        case 0x48:
            if (g_GameLogic.Team_CaptainRosterLoc[g_d_GameSettings.humanTeamNumber] == (s8)ACTOR(lbl_3_data_1E434[p[1]].actor)->roster) {
                fn_3_24ADC(p[1], 0);
                SCR += 3;
            } else {
                fn_3_24ADC(p[2], 0);
                SCR += 3;
            }
            continue;
        case 0x49:
            CAMV->orbit = 0;
            CAMV->lookAtMode = 0;
            CAMV->track = FindTeamActor();
            SCR += 1;
            continue;
        case 0x4A:
            SCR = p + 1;
            continue;
        case 0x4B:
            fn_3_249E8(p[1]);
            SCR += 2;
            continue;
        case 0x4E:
            CAMV->_09B7 = p[1];
            SCR += 2;
            continue;
        case 0x4F:
            fn_3_BBBC4();
            SCR += 1;
            continue;
        case 0x50:
            fn_3_BA150();
            SCR += 1;
            continue;
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54: {
            s16 charId = g_Runners[0].charID; /* batter-runner */
            s16 anim;
            switch (p[0]) {
            case 0x51: anim = lbl_3_data_37AC[charId]; break;
            case 0x52: anim = lbl_3_data_3888[charId]; break;
            case 0x53: anim = lbl_3_data_3964[charId]; break;
            case 0x54: anim = lbl_3_data_3A40[charId]; break;
            default: anim = 0; break;
            }
            SetCamAnim(anim);
            SCR += 1;
            continue;
        }
        case 0x55:
        case 0x56: {
            s8 kind = 0;
            s32 i;
            s32 sel;
            for (i = 0; i < 9; i++) {
                CharActor* a = ACTOR(i);
                if (g_GameLogic.Team_CaptainRosterLoc[g_d_GameSettings.humanTeamNumber] == (s8)a->roster) {
                    kind = a->kind;
                }
            }
            switch (kind) {
            case 0: sel = 0; break;
            case 4: sel = 1; break;
            case 10: sel = 2; break;
            case 2: sel = 3; break;
            case 6: sel = 4; break;
            case 9: sel = 5; break;
            default: sel = 0; break;
            }
            SetCamAnim(p[0] == 0x55 ? lbl_3_data_3B1C[sel] : lbl_3_data_3B34[sel]);
            SCR += 1;
            continue;
        }
        case 0x58:
            fn_80011358(FindTeamActor(), starKind);
            SCR += 1;
            continue;
        case 0x59:
            fn_80011358(FindTeamActor(), 4);
            SCR += 1;
            continue;
        case 0x5A:
            fn_3_219CC();
            SCR += 1;
            continue;
        case 0x5B: {
            ModelLoadTask* t = fn_800B0A5C_insertQueue((void*)fn_3_FDA1C, 4);
            task->_10 = 0;
            t->state = 0;
            t->idx = 0;
            SCR += 1;
            continue;
        }
        case 0x5C:
            if (task->_10 == 1) {
                SCR = p + 1;
            }
            return 0;
        case 0x5D:
            changeScene(1, 6);
            SCR += 1;
            continue;
        case 0x5E:
            SCR = p + 1;
            continue;
        case 0x5F:
            fn_3_100038();
            changeScene(3, 6);
            SCR += 1;
            continue;
        case 0x60:
            if (lbl_8037169C._13 != 0) {
                SCR = p + 1;
            }
            return 0;
        case 0x61: {
            s32 i;
            for (i = 0; i < 9; i++) {
                fn_3_21C7C(i, SCR[1]);
            }
            SCR += 2;
            return 0;
        }
        case 0x65:
            fn_3_100038();
            p = SCR;
            if (p[1] <= g_pCamera->views[0]._0952) {
                SCR = p + 2;
                continue;
            }
            return 0;
        case 0x67:
            fn_3_100038();
            SCENE->_25A += 1;
            if ((f32)SCENE->_25A >= 2.0f * lbl_3_data_1F3A0[starIdx]) {
                SCR += 1;
                continue;
            }
            return 0;
        case 0x69:
            SCENE->_280 = p[1];
            SCR += 2;
            continue;
        case 0x6A:
            fn_8001CA40(p[1]);
            SCR += 2;
            continue;
        default:
            return 0;
        }
    }
}
#undef WAIT_EVENT
#undef SCR
#undef SCENE
#undef ACTOR
#undef FRAME
#undef CAM_SEL
#endif

// .text:0x00100018 size:0x20 mapped:0x8073F0AC

s32 fn_3_100018(void) {
    return CAMV->_09B6 == 1;
}

// .text:0x00100038 size:0x44 mapped:0x8073F0CC
void fn_3_100038(void) {
    if (CAMV->frame > CAMV->frameEnd) {
        if (CAMV->loop == 0) {
            CAMV->frame = CAMV->frameEnd;
        } else {
            CAMV->frame = 0;
        }
    } else {
        CAMV->frame += 0x10000;
    }
}

// .text:0x0010007C size:0x5C mapped:0x8073F110
s32 fn_3_10007C(void) {
    ReplayCamView* d = CAMV;
    if (d->_09AB == 1) {
        if (d->_0014 != 0) {
            lbl_80366158._28 = 1;
            return 0;
        }
        lbl_80366158._28 = 0;
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
    memcpy(&v, &g_pCamera->_2840, 12);
    v.x = g_pCamera->_2840.x - pivot->x;
    v.y = g_pCamera->_2840.y - pivot->y;
    v.z = g_pCamera->_2840.z - pivot->z;
    PSMTXMultVec(rot, &v, &v);
    v.x = v.x + pivot->x;
    v.y = v.y + pivot->y;
    v.z = v.z + pivot->z;
    memcpy(&g_pCamera->_2840, &v, 12);
}
static void CamEyeFromScript(void) {
    g_pCamera->_2840.x = g_pCamera->_2858.x;
    g_pCamera->_2840.y = g_pCamera->_2858.y;
    g_pCamera->_2840.z = g_pCamera->_2858.z;
    if (g_pCamera->_2840.y < 0.1f) {
        g_pCamera->_2840.y = 0.1f;
    }
}
/* Look-at = `tgt` (smoothed by fn_3_103C30), then smooth the eye (fn_3_1040D8). */
static void CamSetTarget(Vec* tgt) {
    g_pCamera->_284C.x = tgt->x;
    g_pCamera->_284C.y = tgt->y;
    g_pCamera->_284C.z = tgt->z;
    fn_3_103C30(tgt);
    g_pCamera->_284C.x = tgt->x;
    g_pCamera->_284C.y = tgt->y;
    g_pCamera->_284C.z = tgt->z;
    fn_3_1040D8();
}
/* Ball-follow eye position for ball camera mode (+0x9A9). */
static void CamBallEye(void) {
    InMemBallType* ball = &g_Ball;
    Mtx rot;
    f32 dz;
    f32 vx;
    f32 vy;
    f32 vz;
    f32 t;
    switch (CAMV->ballMode) {
    case 0:
    case 1:
        CAMV->_00A0 = 0.87266463f;
        g_pCamera->_2840.x = ball->AtBat_Contact_BallPos.x;
        g_pCamera->_2840.y = ball->AtBat_Contact_BallPos.y;
        g_pCamera->_2840.z = ball->AtBat_Contact_BallPos.z;
        break;
    case 2:
    case 3:
        CAMV->_00A0 = 0.87266463f;
        g_pCamera->_2840.x = ball->pastCoordinates[1].x;
        g_pCamera->_2840.y = ball->pastCoordinates[1].y;
        g_pCamera->_2840.z = ball->pastCoordinates[1].z;
        break;
    case 4:
        dz = ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        if (dz < 0.0f) {
            dz = -ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        }
        vz = ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z;
        vx = ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x;
        vy = ball->AtBat_Contact_BallPos.y - ball->pastCoordinates[0].y;
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        g_pCamera->_2840.x = (ball->AtBat_Contact_BallPos.x + vx) - vx * t;
        g_pCamera->_2840.y = (ball->AtBat_Contact_BallPos.y + vy) - vy * t;
        g_pCamera->_2840.z = (ball->AtBat_Contact_BallPos.z + vz) - vz * t;
        break;
    case 6:
        dz = ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        if (dz < 0.0f) {
            dz = -ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        }
        vz = ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z;
        vx = ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x;
        vy = ball->AtBat_Contact_BallPos.y - ball->pastCoordinates[0].y;
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        g_pCamera->_2840.x = vx * t + (ball->AtBat_Contact_BallPos.x - vx);
        g_pCamera->_2840.y = vy * t + (ball->AtBat_Contact_BallPos.y - vy);
        g_pCamera->_2840.z = vz * t + (ball->AtBat_Contact_BallPos.z - vz);
        break;
    case 5:
        dz = ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        if (dz < 0.0f) {
            dz = -ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        }
        vz = ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z;
        vx = ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x;
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        g_pCamera->_2840.x = (ball->AtBat_Contact_BallPos.x + vx) - vx * t;
        g_pCamera->_2840.y = ball->AtBat_Contact_BallPos.y;
        g_pCamera->_2840.z = (ball->AtBat_Contact_BallPos.z + vz) - vz * t;
        break;
    case 7:
        dz = ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        if (dz < 0.0f) {
            dz = -ball->AtBat_Contact_BallPos.z - g_pCamera->_2858.z;
        }
        vz = ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z;
        vx = ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x;
        if (0.0f == vz) {
            vz = 0.0001f;
        }
        t = dz / vz;
        g_pCamera->_2840.x = vx * t + (ball->AtBat_Contact_BallPos.x - vx);
        g_pCamera->_2840.y = ball->AtBat_Contact_BallPos.y;
        g_pCamera->_2840.z = vz * t + (ball->AtBat_Contact_BallPos.z - vz);
        break;
    case 8:
        g_pCamera->_2840.x = g_pCamera->_2858.x;
        g_pCamera->_2840.y = g_pCamera->_2858.y;
        g_pCamera->_2840.z = g_pCamera->_2858.z;
        PSMTXRotRad(rot, 'Y', -fn_3_9FEA8(1.5707964f + game_atan2(ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x, ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z)));
        CamOrbit(rot, &ball->AtBat_Contact_BallPos);
        break;
    }
}
/* Ball-follow look-at target for ball camera mode (+0x9A9); modes > 8 leave *tgt unchanged. */
static void CamBallTarget(Vec* tgt) {
    InMemBallType* ball = &g_Ball;
    switch (CAMV->ballMode) {
    case 0:
        tgt->x = ball->AtBat_Contact_BallPos.x + (ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x);
        tgt->y = ball->AtBat_Contact_BallPos.y + (ball->AtBat_Contact_BallPos.y - ball->pastCoordinates[0].y);
        tgt->z = ball->AtBat_Contact_BallPos.z + (ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z);
        break;
    case 1:
        tgt->y = ball->AtBat_Contact_BallPos.y;
        tgt->x = ball->AtBat_Contact_BallPos.x + (ball->AtBat_Contact_BallPos.x - ball->pastCoordinates[0].x);
        tgt->z = ball->AtBat_Contact_BallPos.z + (ball->AtBat_Contact_BallPos.z - ball->pastCoordinates[0].z);
        break;
    case 2:
        tgt->x = ball->pastCoordinates[2].x;
        tgt->y = ball->pastCoordinates[2].y;
        tgt->z = ball->pastCoordinates[2].z;
        break;
    case 3:
        tgt->x = ball->pastCoordinates[2].x;
        tgt->y = ball->pastCoordinates[1].y;
        tgt->z = ball->pastCoordinates[2].z;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        memcpy(tgt, &CAMV->target, 12);
        fn_3_106270(tgt);
        break;
    }
}
/* Orbits the eye about the tracked actor (0-8 fielder, 9-12 runner, 13 ball) to face along its heading. */
static void CamOrbitTracked(s16 idx) {
    InMemBallType* ball = &g_Ball;
    Mtx rot;
    if (idx < 9 && idx >= 0) {
        InMemFielderView* fl = &g_Fielders[idx];
        PSMTXRotRad(rot, 'Y', -fn_3_9FEA8(1.5707964f + fl->_048));
        CamOrbit(rot, &fl->pos);
    } else if (idx < 13 && idx >= 0) {
        InMemRunnerType* rn = &g_Runners[idx - 9];
        PSMTXRotRad(rot, 'Y', fn_3_9FEA8(rn->runningAngle));
        CamOrbit(rot, &rn->position);
    } else if (idx == 13) {
        PSMTXRotRad(rot, 'Y', atan2(-(ball->pastCoordinates[0].x - ball->AtBat_Contact_BallPos.x), -(ball->pastCoordinates[0].z - ball->AtBat_Contact_BallPos.z)));
        CamOrbit(rot, &ball->AtBat_Contact_BallPos);
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
    g_pCamera->_284C.x = g_pCamera->_2858.x + 100.0f * cy * cp;
    g_pCamera->_284C.y = g_pCamera->_2858.y + 100.0f * sp;
    g_pCamera->_284C.z = g_pCamera->_2858.z + 100.0f * sy * cp2;
}
/* Reset the eye smoothing state to the current eye. */
static void CamInitEye(void) {
    CAMV->eyePrev.x = g_pCamera->_2840.x;
    CAMV->eyePrev.y = g_pCamera->_2840.y;
    CAMV->eyePrev.z = g_pCamera->_2840.z;
    CAMV->eyeSmooth.x = 0.00001f + g_pCamera->_2840.x;
    CAMV->eyeSmooth.y = 0.00001f + g_pCamera->_2840.y;
    CAMV->eyeSmooth.z = 0.00001f + g_pCamera->_2840.z;
}
/* Set the look-at to `tgt` and reset the look-at smoothing state to it. */
static void CamInitTarget(Vec* tgt) {
    g_pCamera->_284C.x = tgt->x;
    g_pCamera->_284C.y = tgt->y;
    g_pCamera->_284C.z = tgt->z;
    CAMV->tgtPrev.x = 0.00001f + g_pCamera->_284C.x;
    CAMV->tgtPrev.y = 0.00001f + g_pCamera->_284C.y;
    CAMV->tgtPrev.z = 0.00001f + g_pCamera->_284C.z;
    CAMV->tgtSmooth.x = 0.00002f + g_pCamera->_284C.x;
    CAMV->tgtSmooth.y = 0.00002f + g_pCamera->_284C.y;
    CAMV->tgtSmooth.z = 0.00002f + g_pCamera->_284C.z;
}
void fn_3_1000D8(void) {
    s16 idx = CAMV->track;
    Vec tgt;

    if (CAMV->ballCam == 0) {
        switch (CAMV->type) {
        case 0:
        case 1: {
            f32 ang[2]; /* yaw, pitch */
            CamEyeFromScript();
            ang[0] = fn_3_9FEA8(g_pCamera->_2870);
            ang[1] = fn_3_9FEA8(g_pCamera->_2874);
            fn_3_103E7C(ang);
            CamAngleTarget(ang);
            fn_3_1040D8();
            break;
        }
        case 2:
            if (idx < 13 && idx >= 0 && CAMV->hold <= 2) {
                fn_3_101CC4();
            }
            if (CAMV->orbit == 0) {
                CamEyeFromScript();
                memcpy(&tgt, &CAMV->target, 12);
                fn_3_106270(&tgt);
                CamSetTarget(&tgt);
            } else if (CAMV->orbit == 1) {
                CamEyeFromScript();
                CamOrbitTracked(idx);
                memcpy(&tgt, &CAMV->target, 12);
                fn_3_106270(&tgt);
                CamSetTarget(&tgt);
            }
            if (g_pCamera->_284C.y < 0.1f) {
                g_pCamera->_284C.y = 0.1f;
            }
            break;
        }
    } else {
        CamBallEye();
        if (g_pCamera->_2840.y < 1.0f) {
            g_pCamera->_2840.y = 1.0f;
        }
        CamBallTarget(&tgt);
        /* mode > 8 leaves tgt unset, as in the original. */
        CamSetTarget(&tgt);
        if (g_pCamera->_284C.y < 0.1f) {
            g_pCamera->_284C.y = 0.1f;
        }
    }
}
#endif

// .text:0x00101CC4 size:0x1F6C mapped:0x80740D58
// NONMATCHING 88% (scored with the helpers inlined; call sequence identical): same structure as fn_3_1000D8 (whose helpers it shares, and which the original inlines; nmverify flags
// those calls), but first resets the eye/look-at smoothing state (+0xAC..+0xD8) to the new camera.
#if NONMATCHING
void fn_3_101CC4(void) {
    s16 idx = CAMV->track;
    Vec tgt;

    if (CAMV->ballCam == 0) {
        switch (CAMV->type) {
        case 0:
        case 1: {
            f32 ang[2]; /* yaw, pitch */
            memcpy(&g_pCamera->_2840, &g_pCamera->_2858, 12);
            if (g_pCamera->_2840.y < 0.1f) {
                g_pCamera->_2840.y = 0.1f;
            }
            CamInitEye();
            ang[0] = fn_3_9FEA8(g_pCamera->_2870);
            ang[1] = fn_3_9FEA8(g_pCamera->_2874);
            CAMV->tgtPrev.x = ang[0];
            CAMV->tgtPrev.y = ang[1];
            CAMV->tgtPrev.z = 0.0f;
            CAMV->tgtSmooth.x = 0.00001f + ang[0];
            CAMV->tgtSmooth.y = 0.00001f + ang[1];
            CAMV->tgtSmooth.z = 0.0f;
            fn_3_103E7C(ang);
            CamAngleTarget(ang);
            fn_3_1040D8();
            if (g_pCamera->_284C.y < 0.1f) {
                g_pCamera->_284C.y = 0.1f;
            }
            break;
        }
        case 2:
            if (CAMV->orbit == 0) {
                CamEyeFromScript();
                CamInitEye();
                memcpy(&tgt, &CAMV->target, 12);
                fn_3_106270(&tgt);
                CamInitTarget(&tgt);
                CamSetTarget(&tgt);
                if (g_pCamera->_284C.y < 0.1f) {
                    g_pCamera->_284C.y = 0.1f;
                }
            } else if (CAMV->orbit == 1) {
                CamEyeFromScript();
                CamOrbitTracked(idx);
                memcpy(&tgt, &CAMV->target, 12);
                fn_3_106270(&tgt);
                CamInitTarget(&tgt);
                CamSetTarget(&tgt);
                if (g_pCamera->_284C.y < 0.1f) {
                    g_pCamera->_284C.y = 0.1f;
                }
            }
            break;
        }
    } else {
        CamBallEye();
        if (g_pCamera->_2840.y < 1.0f) {
            g_pCamera->_2840.y = 1.0f;
        }
        CamInitEye();
        CamBallTarget(&tgt);
        /* ball modes > 8 leave tgt unset, as in the original. */
        CamInitTarget(&tgt);
        CamSetTarget(&tgt);
        if (g_pCamera->_284C.y < 0.1f) {
            g_pCamera->_284C.y = 0.1f;
        }
    }
}
#endif

// .text:0x00103C30 size:0x24C mapped:0x80742CC4
void fn_3_103C30(Vec* p) {
    if (CAMV->smooth != 0) {
        Vec r;
        Vec ta;
        Vec tb;
        Vec tc;
        Vec junk;
        memcpy(&junk, p, 12);
        ta.x = CAMV->tgtSmooth.x;
        ta.y = CAMV->tgtSmooth.y;
        ta.z = CAMV->tgtSmooth.z;
        memcpy(&tb, p, 12);
        tc.x = CAMV->tgtPrev.x;
        tc.y = CAMV->tgtPrev.y;
        tc.z = CAMV->tgtPrev.z;
        r = CamStep(ta, tb, tc, CAMV->tgtW[0], CAMV->tgtW[1], CAMV->tgtW[2]);
        CAMV->tgtPrev.x = p->x;
        CAMV->tgtPrev.y = p->y;
        CAMV->tgtPrev.z = p->z;
        CAMV->tgtSmooth.x = r.x;
        CAMV->tgtSmooth.y = r.y;
        CAMV->tgtSmooth.z = r.z;
        p->x = r.x;
        p->y = r.y;
        p->z = r.z;
    }
}

// .text:0x00103E7C size:0x25C mapped:0x80742F10
void fn_3_103E7C(f32* p) {
    if (CAMV->smooth != 0) {
        Vec r;
        Vec ta;
        Vec tb;
        Vec tc;
        p[0] = fn_3_9FEA8(p[0]);
        p[1] = fn_3_9FEA8(p[1]);
        ta.x = CAMV->tgtSmooth.x;
        ta.y = CAMV->tgtSmooth.y;
        ta.z = CAMV->tgtSmooth.z;
        tb.x = p[0];
        tb.y = p[1];
        tb.z = lbl_3_rodata_30F8;
        tc.x = CAMV->tgtPrev.x;
        tc.y = CAMV->tgtPrev.y;
        tc.z = CAMV->tgtPrev.z;
        r = CamStep(ta, tb, tc, CAMV->tgtW[0], CAMV->tgtW[1], CAMV->tgtW[2]);
        CAMV->tgtPrev.x = p[0];
        CAMV->tgtPrev.y = p[1];
        CAMV->tgtPrev.z = lbl_3_rodata_30F8;
        CAMV->tgtSmooth.x = r.x;
        CAMV->tgtSmooth.y = r.y;
        CAMV->tgtSmooth.z = r.z;
        p[0] = r.x;
        p[1] = r.y;
    }
}

// .text:0x001040D8 size:0x260 mapped:0x8074316C
void fn_3_1040D8(void) {
    if (CAMV->smooth != 0) {
        Vec r;
        Vec ta;
        Vec tb;
        Vec tc;
        f32 bx = g_pCamera->_2840.x;
        f32 by = g_pCamera->_2840.y;
        f32 bz = g_pCamera->_2840.z;
        ta.x = CAMV->eyeSmooth.x;
        ta.y = CAMV->eyeSmooth.y;
        ta.z = CAMV->eyeSmooth.z;
        tb.x = bx;
        tb.y = by;
        tb.z = bz;
        tc.x = CAMV->eyePrev.x;
        tc.y = CAMV->eyePrev.y;
        tc.z = CAMV->eyePrev.z;
        r = CamStep(ta, tb, tc, CAMV->eyeW[0], CAMV->eyeW[1], CAMV->eyeW[2]);
        g_pCamera->_2840.x = r.x;
        g_pCamera->_2840.y = r.y;
        g_pCamera->_2840.z = r.z;
        CAMV->eyeSmooth.x = r.x;
        CAMV->eyeSmooth.y = r.y;
        CAMV->eyeSmooth.z = r.z;
        CAMV->eyePrev.x = bx;
        CAMV->eyePrev.y = by;
        CAMV->eyePrev.z = bz;
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

    pitch = fn_3_9FEA8(g_pCamera->_2874);
    dist = 20.0f * (f32)cos(pitch);
    sinPitch = (f32)sin(pitch);
    yaw = fn_3_9FEA8(g_pCamera->_2870);
    cosYaw = (f32)cos(yaw);
    sinYaw = (f32)sin(yaw);
    dx = cosYaw * dist;
    dy = 20.0f * sinPitch;
    dz = sinYaw * dist;
    g_pCamera->_2858.x += cosYaw * g_pCamera->_287C;
    g_pCamera->_2858.z += sinYaw * g_pCamera->_287C;
    g_pCamera->_2858.x += sinYaw * g_pCamera->_2880;
    g_pCamera->_2858.z -= cosYaw * g_pCamera->_2880;
    g_pCamera->_284C.x = dx + g_pCamera->_2858.x;
    g_pCamera->_284C.y = dy + g_pCamera->_2858.y;
    g_pCamera->_284C.z = dz + g_pCamera->_2858.z;
    g_pCamera->_2840.x = g_pCamera->_2858.x;
    g_pCamera->_2840.y = g_pCamera->_2858.y;
    g_pCamera->_2840.z = g_pCamera->_2858.z;
    g_pCamera->_287C = 0.0f;
    g_pCamera->_2880 = 0.0f;
}

// .text:0x00104740 size:0x1A0 mapped:0x807437D4
void fn_3_104740(void) {
    if (CAMV->type == 2) {
        CAMV->tgtPrev.x = lbl_3_rodata_3158 + g_pCamera->_284C.x;
        CAMV->tgtPrev.y = lbl_3_rodata_3158 + g_pCamera->_284C.y;
        CAMV->tgtPrev.z = lbl_3_rodata_3158 + g_pCamera->_284C.z;
        CAMV->tgtSmooth.x = lbl_3_rodata_315C + g_pCamera->_284C.x;
        CAMV->tgtSmooth.y = lbl_3_rodata_315C + g_pCamera->_284C.y;
        CAMV->tgtSmooth.z = lbl_3_rodata_315C + g_pCamera->_284C.z;
    } else {
        CAMV->tgtPrev.x = lbl_3_rodata_3158 + g_pCamera->_2870;
        CAMV->tgtPrev.y = lbl_3_rodata_3158 + g_pCamera->_2874;
        CAMV->tgtPrev.z = lbl_3_rodata_30F8;
        CAMV->tgtSmooth.x = lbl_3_rodata_3158 + g_pCamera->_2870;
        CAMV->tgtSmooth.y = lbl_3_rodata_3158 + g_pCamera->_2874;
        CAMV->tgtSmooth.z = lbl_3_rodata_30F8;
    }
    CAMV->eyePrev.x = g_pCamera->_2840.x;
    CAMV->eyePrev.y = g_pCamera->_2840.y;
    CAMV->eyePrev.z = g_pCamera->_2840.z;
    CAMV->eyeSmooth.x = lbl_3_rodata_3158 + g_pCamera->_2840.x;
    CAMV->eyeSmooth.y = lbl_3_rodata_3158 + g_pCamera->_2840.y;
    CAMV->eyeSmooth.z = lbl_3_rodata_3158 + g_pCamera->_2840.z;
}

// .text:0x001048E0 size:0x15C mapped:0x80743974
void fn_3_1048E0(ReplayAnim* a, s32 b, s32 c, s32 d, CamFrame* out) {
    CamMtx m;
    Vec va;
    Vec vb;
    memset(&m, 0, sizeof(CamMtx));
    {
        f32 v = lbl_3_rodata_30FC;
        m.m[3][3] = v;
        m.m[2][2] = v;
        m.m[1][1] = v;
        m.m[0][0] = v;
        m.f40 = v;
    }
    fn_3_104B3C(a, b, c, d, &m);
    memcpy(&out->pos, &m.pos, 12);
    memcpy(&out->target, &m.target, 12);
    memcpy(&out->scale, &m.scale, 12);
    out->fov = m.f4C;
    PSMTX44MultVec(m.m, &s_axa, &out->up);
    PSVECNormalize(&out->up, &out->up);
    va = out->fwd;
    PSMTX44MultVec(m.m, &s_axb, &va);
    PSVECNormalize(&va, &va);
    vb = out->back;
    PSMTX44MultVec(m.m, &s_axc, &vb);
    PSVECNormalize(&vb, &vb);
    out->rx = m.rx;
    out->ry = m.ry;
    out->type = m.type;
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
void fn_3_104B3C(ReplayAnim* anim, s32 b, s32 c, s32 d, CamMtx* m) {
    u32 key = b;
    s16 track = c;
    u8 depth = d;
    ReplayAnimTrack* trk = anim->tracks[track];
    u8* first = trk->keys;
    ReplayAnimKeyF* k;
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
    ReplayAnimKeyF interp;
    CamMtx sub;
    Vec rot;    /* rot angles (types 0/1) or position (type 2) */
    Vec tgt;
    Vec right;
    Vec fwd;
    Vec up;
    Vec a0;
    Vec b0;

    if (trk->parent >= 0 && depth != 0) {
        fn_3_104B3C(anim, key, trk->parent, (u8)(depth - 1), m);
    }
    count = trk->count;
    frame = key >> 16;
    stride = lbl_3_data_20FC4[trk->type];
    lo = key;
    k = (ReplayAnimKeyF*)(first + (count - 1) * stride);
    if (count != 1 && frame < k->frame) {
        ReplayAnimKeyF* cur = (ReplayAnimKeyF*)first;
        ReplayAnimKeyF* next = (ReplayAnimKeyF*)(first + stride);
        while ((u32)(next->frame << 16) <= key) {
            cur = next;
            next = (ReplayAnimKeyF*)((u8*)next + stride);
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
        fn_3_104B3C(anim, key, (s16)trk->target, 0xFF, &sub);
        m->target.x = tgt.x = sub.pos.x;
        m->target.y = tgt.y = sub.pos.y;
        m->target.z = tgt.z = sub.pos.z;
        if (CAMV->lookAtMode == 1) {
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

#define RCAM_N (CAMV->nSplineKeys)
#define RCAM_TBL(i) (CAMV->segLen[i])
#define RCAM_KEY(i) (CAMV->keys[i])
// .text:0x001054D0 size:0x540 mapped:0x80744564
// NONMATCHING 97.5%: table stores use addi+stwx instead of add+stw 0x128 (see docs/patterns/regalloc.md).
// If `key` (frame << 16 | frac) lands exactly on a key of track `track`, append that key to the camera spline key list
// (+0x9C) and store the frame count until the next key in the table at +0x128.
#if NONMATCHING
void fn_3_1054D0(ReplayAnim* anim, u32 key, s16 track) {
    u16 lo = key;
    u32 frame = key >> 16;
    u8 hit = 0;
    ReplayAnimTrack* trk = anim->tracks[track];
    u8* first = trk->keys;
    u16 count = trk->count;
    s32 stride = lbl_3_data_20FC4[trk->type];
    ReplayAnimKey* cur = (ReplayAnimKey*)(first + (count - 1) * stride);

    if (count == 1) {
        hit = 1;
        RCAM_TBL(RCAM_N) = cur->frame;
    } else if (frame <= cur->frame) {
        if (frame == cur->frame) {
            hit = 1;
            RCAM_TBL(RCAM_N) = cur->frame;
        } else {
            ReplayAnimKey* next;
            cur = (ReplayAnimKey*)first;
            next = (ReplayAnimKey*)(first + stride);
            while ((u32)(next->frame << 16) <= key) {
                cur = next;
                next = (ReplayAnimKey*)((u8*)next + stride);
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
            if (CAMV->nSplineKeys == 1) {
                memcpy(&(CAMV->keys)[0].v[0], &cur->pos, 12);
                (CAMV->keys)[0].v[1] *= lbl_3_rodata_3178;
                (CAMV->keys)[0].v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
                (CAMV->keys)[0].v[4] = cur->a - lbl_3_rodata_314C;
                RCAM_TBL(0) = RCAM_TBL(RCAM_N);
            }
            memcpy(&RCAM_KEY(RCAM_N).v[0], &cur->pos, 12);
            RCAM_KEY(RCAM_N).v[1] *= lbl_3_rodata_3178;
            RCAM_KEY(RCAM_N).v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).v[4] = cur->a - lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).frame = frame;
            break;
        case 1:
            if (CAMV->nSplineKeys == 1) {
                memcpy(&(CAMV->keys)[0].v[0], &cur->pos, 12);
                (CAMV->keys)[0].v[1] *= lbl_3_rodata_3178;
                (CAMV->keys)[0].v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
                (CAMV->keys)[0].v[4] = cur->a - lbl_3_rodata_314C;
                RCAM_TBL(0) = RCAM_TBL(RCAM_N);
            }
            memcpy(&RCAM_KEY(RCAM_N).v[0], &cur->pos, 12);
            RCAM_KEY(RCAM_N).v[1] *= lbl_3_rodata_3178;
            RCAM_KEY(RCAM_N).v[3] = lbl_3_rodata_3110 * cur->b + lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).v[4] = cur->a - lbl_3_rodata_314C;
            RCAM_KEY(RCAM_N).frame = frame;
            break;
        case 2:
            if (CAMV->nSplineKeys == 1) {
                memcpy(&(CAMV->keys)[0].v[0], &cur->pos, 12);
                (CAMV->keys)[0].v[1] *= lbl_3_rodata_3178;
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
void fn_3_105BD8(CamMtx* p) {
    f32 v;
    memset(p, 0, sizeof(CamMtx));
    v = lbl_3_rodata_30FC;
    p->m[3][3] = v;
    p->m[2][2] = v;
    p->m[1][1] = v;
    p->m[0][0] = v;
    p->f40 = v;
}

// .text:0x00105C28 size:0x5C mapped:0x80744CBC
#pragma dont_inline off
u32 fn_3_105C28(ReplayAnim* p, u32 key) {
    u16 hi;
    u32 res;
    u16 n;
    u16* tbl;
    u16* e;
    u32 lo;
    u16* last;
    res = 0;
    hi = key >> 16;
    tbl = p->frameTbl;
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
/* Relocates the animation in place: frameTbl and tracks[] hold offsets from the file start. */
void fn_3_105C84(ReplayAnim* p) {
    u32* a;
    s16 i;
    a = (u32*)&p->frameTbl; /* TODO(port): frameTbl/tracks[] hold 32-bit file offsets relocated in place */
    *a += PTR_TO_U32(p);
    for (i = 0; i < p->numTracks; i++) {
        a[i + 1] += PTR_TO_U32(p);
    }
    CAMV->frameEnd = p->numFrames << 16;
}
#pragma dont_inline on

// .text:0x00105CDC size:0x124 mapped:0x80744D70
void fn_3_105CDC(void) {
    Vec* arr = CAMV->dbgPts;
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
#if NONMATCHING
        fn_3_105E00((s16)(x / 50 + 150), (s16)(-z / 50 + 400), 2, 2);
#else
        // The original prototype took s16 coordinates (same PPC ABI); keeps the extsh scheduling.
        ((void (*)(s16, s16, s32, s32))fn_3_105E00)(x / 50 + 150, -z / 50 + 400, 2, 2);
#endif
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
    Vec* t = CAMV->dbgPts;
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
    Vec* p = CAMV->dbgPts;
    s32 i;
    lbl_3_bss_B67A = 0;
    for (i = 0; i < 1000; i++) {
        p->x = p->y = p->z = -1000.0f;
        p++;
    }
}

// .text:0x0010617C size:0xF4 mapped:0x80745210
s32 fn_3_10617C(s32 idx, s32 j, Vec* out) {
    CharActor* obj;
    Vec v;

    obj = lbl_8036E548.active[idx];
    if (obj == NULL) {
        return 0;
    }
    j = obj->jointIdx[j];
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
    out->x += obj->pos.x;
    out->y += obj->pos.y;
    out->z += obj->pos.z;
    return 1;
}

// .text:0x00106270 size:0x71C mapped:0x80745304
// NONMATCHING 91%: original recomputes g_Fielders + idx*0x268 per use (offset in r30) and hoists g_Stats; ours keeps the pointer.
// Camera look-at target for the tracked actor (+0x946): 0-8 fielder, 9-12 runner, 13 ball, 14 keep, 15 last.
// The joint position (+0x938) is smoothed by holding it in +0xE8 for a few frames after the target changes.
#if NONMATCHING
void fn_3_106270(Vec* out) {
    s16 idx = CAMV->track;
    Vec j;

    if (idx < 9 && idx >= 0) {
        InMemFielderView* fl = &g_Fielders[idx];
        memcpy(out, &fl->pos, 12);
        if (fl->rosterID != -1) {
            if (lbl_8036E548.active[idx] != NULL) {
                if (g_Stats.replayInd != 0 && g_Stats._3C == 7) {
                    memset(out, 0, 12);
                    getAnimRelatedCoordinates(idx, 4, out);
                }
                if (CAMV->joint == -1) {
                    CAMV->joint = lbl_3_data_3B4C[fl->charID];
                    CAMV->hold = 0;
                }
                memset(&j, 0, 12);
                if (getAnimRelatedCoordinates(idx, CAMV->joint, &j) == 0) {
                    memset(&j, 0, 12);
                    getAnimRelatedCoordinates(idx, 4, &j);
                }
                if (CAMV->_09B7 == 0) {
                    ReplayCamView* d = CAMV;
                    if (d->joint != d->jointPrev || d->trackPrev != d->track ||
                        d->animPrev != d->anim || d->charPrev != fl->charID) {
                        d->hold = 0;
                    }
                    if (CAMV->hold < 1) {
                        memcpy(&CAMV->jointHold, &j, 12);
                        CAMV->hold += 1;
                    } else {
                        memcpy(&j, &CAMV->jointHold, 12);
                        if (CAMV->hold < 3) {
                            CAMV->hold += 1;
                        }
                    }
                } else {
                    memcpy(&CAMV->jointHold, &j, 12);
                }
                if (g_Stats.replayInd != 0 && g_Stats._3C == 7) {
                    out->y = lbl_3_rodata_3110 * out->y + fl->_00C + lbl_3_data_1DB00[CAMV->offsetIdx].y;
                    out->x += lbl_3_data_1DB00[CAMV->offsetIdx].x;
                    out->z += lbl_3_data_1DB00[CAMV->offsetIdx].z;
                } else {
                    out->y = lbl_3_rodata_3110 * j.y + fl->_00C + lbl_3_data_1DB00[CAMV->offsetIdx].y;
                    out->x = j.x + lbl_3_data_1DB00[CAMV->offsetIdx].x;
                    out->z = j.z + lbl_3_data_1DB00[CAMV->offsetIdx].z;
                }
            }
        } else {
            /* BUG (original): copies the bytes of the `out` pointer itself, not *out. */
            memcpy(&CAMV->lastTarget, &out, 12);
        }
        CAMV->charPrev = fl->charID;
    } else if (idx < 13 && idx >= 0) {
        InMemRunnerType* rn = &g_Runners[idx - 9];
        memcpy(out, &rn->position, 12);
        if (rn->rosterID != -1) {
            if (lbl_8036E548.active[idx] != NULL) {
                ReplayCamView* d;
                if (CAMV->joint == -1) {
                    CAMV->joint = lbl_3_data_3B4C[rn->charID];
                    CAMV->hold = 0;
                }
                memset(&j, 0, 12);
                if (getAnimRelatedCoordinates(idx, CAMV->joint, &j) == 0) {
                    memset(&j, 0, 12);
                    getAnimRelatedCoordinates(idx, 4, &j);
                }
                j.x -= rn->position.x;
                j.y -= rn->position.y;
                j.z -= rn->position.z;
                d = CAMV;
                if (d->joint != d->jointPrev || d->trackPrev != d->track ||
                    d->animPrev != d->anim || d->charPrev != rn->charID) {
                    d->hold = 0;
                }
                if (CAMV->hold < 1) {
                    memcpy(&CAMV->jointHold, &j, 12);
                    CAMV->hold += 1;
                } else {
                    memcpy(&j, &CAMV->jointHold, 12);
                    if (CAMV->hold < 3) {
                        CAMV->hold += 1;
                    }
                }
                out->y = lbl_3_rodata_3110 * j.y + out->y + lbl_3_data_1DB00[CAMV->offsetIdx].y;
                out->x = out->x + j.x + lbl_3_data_1DB00[CAMV->offsetIdx].x;
                out->z = out->z + j.z + lbl_3_data_1DB00[CAMV->offsetIdx].z;
            }
            CAMV->charPrev = rn->charID;
        }
        /* BUG (original): copies the bytes of the `out` pointer itself, not *out. */
        memcpy(&CAMV->lastTarget, &out, 12);
    } else if (idx == 13) {
        memcpy(out, &g_Ball.AtBat_Contact_BallPos, 12);
        memcpy(&CAMV->lastTarget, &g_Ball.AtBat_Contact_BallPos, 12);
    } else if (idx == 14) {
        memcpy(out, out, 12);
        memcpy(&CAMV->lastTarget, out, 12);
    } else if (idx == 15) {
        memcpy(out, &CAMV->lastTarget, 12);
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
    CAMV->nSplineKeys = 1;
    CAMV->frame = 0;
    CAMV->frameEnd = 0;
    CAMV->_0928 = 0;
    for (i = 0; i < 0x200; i++) {
        CAMV->segLen[i] = 0;
    }
    CamsReset();
}

// .text:0x00106BA0 size:0x25C mapped:0x80745C34
void fn_3_106BA0(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        inMemCamera* c = CAM_SHIFTED(&g_Camera, i);
        c->views[0].nSplineKeys = 1;
        c->views[0]._0118 = 0;
        c->views[0].frameEnd = 0;
        c->views[0].track = 0xE;
        c->views[0]._09AE = 0;
        c->views[0].loop = 0;
        c->views[0]._09AF = 0;
        c->views[0]._09B0 = 0;
        c->views[0]._092C = 0;
        c->views[0]._0928 = 0;
        c->views[0]._09B2 = 0;
        c->views[0].smooth = 0;
        c->views[0]._09B3 = 0;
        c->views[0].lookAtMode = 0;
        c->views[0]._09B6 = 0;
        c->views[0]._09B7 = 0;
        c->views[0].tgtSmooth.x = lbl_3_rodata_30F8;
        c->views[0].tgtSmooth.y = lbl_3_rodata_30F8;
        c->views[0].tgtSmooth.z = lbl_3_rodata_30F8;
        c->views[0].tgtPrev.x = lbl_3_rodata_30F8;
        c->views[0].tgtPrev.y = lbl_3_rodata_30F8;
        c->views[0].tgtPrev.z = lbl_3_rodata_30FC;
        c->views[0].lastTarget.x = lbl_3_rodata_30FC;
        c->views[0].lastTarget.y = lbl_3_rodata_30FC;
        c->views[0].lastTarget.z = lbl_3_rodata_30FC;
        c->views[0].eyeW[0] = lbl_3_rodata_3198;
        c->views[0].eyeW[1] = lbl_3_rodata_311C;
        c->views[0].eyeW[2] = lbl_3_rodata_3134;
        c->views[0].tgtW[0] = lbl_3_rodata_30FC;
        c->views[0].tgtW[1] = lbl_3_rodata_311C;
        c->views[0].tgtW[2] = lbl_3_rodata_3134;
        c->views[0]._094A = 0;
        memset(c->views[0].segLen, 0, sizeof(c->views[0].segLen));
        memcpy(&c->views[0].eyeSmooth, &g_pCamera->_284C, 12);
    }
    g_pCamera->_28A9 = 0;
    CamsReset();
}

// -inline deferred reads this at end of file: lets the GXFifo.h inlines (defined
// before the dont_inline on above) inline; functions defined under "on" do not.
#pragma dont_inline off
