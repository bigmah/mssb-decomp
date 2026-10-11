#include "game/rep_37A8.h"
#include "header_rep_data.h"

extern u8 g_Minigame[];

#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "main/file_80011640.h"
#include "math.h"
extern const Vec lbl_3_rodata_3808;
extern const f32 lbl_3_rodata_382C;
extern const f32 lbl_3_rodata_3830;
extern const f32 lbl_3_rodata_3834;
extern const f32 lbl_3_rodata_3838;
extern const f32 lbl_3_rodata_385C;
extern const f64 lbl_3_rodata_3868;
extern void fn_800B993C(void);
extern u8 g_GameLogic[];
extern u8 lbl_3_data_21278[];
extern void fn_3_10F550(s32, u8);
extern void fn_3_5A6D4(s32);
extern void changeScene(s32, s32);
extern void* memset(void*, s32, u32);
extern s16 RandomInt_Game_Range(s16, s16);
extern s16 lbl_3_data_21EAC[];
extern u8 lbl_3_data_21D34[];
extern u8 lbl_80366158[];
extern s8 lbl_3_data_266A4;
extern void DCFlushRange(void*, u32);
extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern u8 lbl_3_data_21E68[];
typedef struct { s16 lo; s16 hi; } MgRange;
typedef struct { s16 t; u8 b; u8 c; } MgSlot;
typedef struct { s16 lo; s16 hi; s16 lim; } MgWin;
extern MgWin lbl_3_data_21DC8[][2];
extern u8 lbl_3_data_21E10[];
extern u8 lbl_3_data_21D1C[];
extern u8 lbl_3_data_21DC4[];
extern u8 lbl_3_data_21E04[];
extern u8 lbl_3_data_26698[];
extern int random_fn_3_9EE24(int max);
extern u8 lbl_3_data_21D2C[];
extern u8 g_Fielders[];
extern s8 lbl_3_data_21EBC[];
extern s8 lbl_3_data_21EC0[];
extern int RandomInt_Game(int);
extern s16 lbl_3_data_7F10[];
extern Vec lbl_3_data_21B94[]; // home positions per player slot
extern f32 charSizeMultipliers[][2];
extern void fn_3_118358(s32, f32*);
extern void fn_3_15730C(u32, f32, f32, f32);
extern u8 g_Controls[];
extern void fn_3_157570(void);
extern void fn_3_DE4FC(void);
extern void fn_3_154214(void);
extern void fn_3_90064(s32 id);

// Thrown-ball slots at g_Minigame + 0xA8 (40 of them).
typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec vel;
    /* 0x18 */ f32 _18;
    /* 0x1C */ s32 owner;
    /* 0x20 */ s16 timer;
    /* 0x22 */ s16 _22;
    /* 0x24 */ u8 _24[2];
    /* 0x26 */ u8 used;
    /* 0x27 */ u8 _27;
} MgBall;
typedef struct { u8 pad0[0xA8]; MgBall ball[40]; } MgBallView;

// Runner slots at g_Minigame + 0x0 (3 of them, 0x38 each); see MgSpawn below.
typedef struct MgRunner {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 _C;
    /* 0x10 */ f32 _10;
    /* 0x14 */ f32 _14;
    /* 0x18 */ s16 _18;
    /* 0x1A */ s16 _1A;
    /* 0x1C */ s16 _1C;
    /* 0x1E */ s16 _1E;
    /* 0x20 */ s16 throwTimer;
    /* 0x22 */ s16 _22;
    /* 0x24 */ s16 _24;
    /* 0x26 */ s16 queueTimer;
    /* 0x28 */ u8 _28[2];
    /* 0x2A */ u8 st;
    /* 0x2B */ u8 sel;
    /* 0x2C */ u8 who;
    /* 0x2D */ u8 _2D;
    /* 0x2E */ u8 _2E;
    /* 0x2F */ s8 queue[4];
    /* 0x33 */ u8 _33;
    /* 0x34 */ s8 fielder;
    /* 0x35 */ s8 player;
    /* 0x36 */ u8 _36[2];
} MgRunner;

// CPU state per player at g_Minigame + 0x1DCC (see fn_3_142C18).
typedef struct {
    /* 0x0 */ s16 timer;
    /* 0x2 */ s8 state;
    /* 0x3 */ u8 _3;
} MgCpu;

// Fake controller input for CPU players at g_Minigame + 0x1D7C (16 bytes per port).
typedef struct {
    /* 0x0 */ s16 stickX;
    /* 0x2 */ u8 _2[2];
    /* 0x4 */ u16 held;
    /* 0x6 */ u16 trig;
    /* 0x8 */ u8 _8[8];
} MgPad;

// This unit's .bss (B7C0..B850) as statics, declared in reverse address order:
// a flashing 4x4 RGBA8 texture used by the TEV hook fn_3_141C8C.
static u8 lbl_3_bss_B800[0x50] ATTRIBUTE_ALIGN(32); // texel data (0x40 used)
static s32 lbl_3_bss_B7E4;                          // frame tick for the flash
static GXTexObj lbl_3_bss_B7C4;                     // texture object
static u8 lbl_3_bss_B7C1;                           // hook frame counter
static u8 lbl_3_bss_B7C0;

// .text:0x00141C44 size:0x48
void fn_3_141C44(void) {
    lbl_3_bss_B7C1++;
    if (lbl_3_bss_B7C1 >= 6) {
        lbl_3_bss_B7C1 = 0;
        fn_800B993C();
    }
}

// .text:0x00141C8C size:0x2A4 mapped:0x80780D20
// NONMATCHING 98.7%: in the inlined fn_3_141F30 the original loads the first texel through the loop
// pointer (addi r4,base,0x40; lbz 0(r4)) after the lbl_3_data_266A4 load; ours folds it to lbz 0x40(r31).
#if NONMATCHING
void fn_3_141C8C(struct DODisplayObj* dispObj, s32* stage, s32* coord, s32* map, u8* numTevStages, u8* numTexGens,
                 MtxPtr camera) {
    Mtx ident;
    Mtx scale;
    Mtx trans;

    fn_3_141F30();
    GXLoadTexObj(&lbl_3_bss_B7C4, *map);
    PSMTXIdentity(ident);
    PSMTXScale(scale, lbl_3_rodata_382C, lbl_3_rodata_3830, lbl_3_rodata_3834);
    PSMTXTrans(trans, lbl_3_rodata_382C, lbl_3_rodata_382C, lbl_3_rodata_3838);
    PSMTXConcat(trans, scale, scale);
    GXLoadTexMtxImm(ident, *map * 3 + 0x1E, 0);
    GXLoadTexMtxImm(scale, *map * 3 + 0x40, 0);
    GXSetTexCoordGen2(*coord, 0, 0, *map * 3 + 0x1E, 1, *map * 3 + 0x40);
    GXSetTevOrder(*stage, *coord, *map, 0xFF);
    GXSetTevColorIn(*stage, 0xF, 8, 9, 0);
    GXSetTevColorOp(*stage, 0, 0, 0, 1, 0);
    GXSetTevAlphaIn(*stage, 7, 7, 7, 0);
    GXSetTevAlphaOp(*stage, 0, 0, 0, 1, 0);
    (*stage)++;
    (*coord)++;
    (*map)++;
    (*numTevStages)++;
    (*numTexGens)++;
    fn_3_141C44();
}
#endif

// .text:0x00141F30 size:0x100 mapped:0x80780FC4
void fn_3_141F30(void) {
    s32 v;
    u8* p;
    s32 n;
    s32 i;

    lbl_3_bss_B7E4 = lbl_3_bss_B7E4 + (lbl_80366158[0x28] == 0);
    if (!(lbl_3_bss_B7E4 & 1)) {
        p = lbl_3_bss_B800;
        v = p[0];
        v += lbl_3_data_266A4 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 16; i != 0; i--) {
            *p = v;
            p += 2;
        }
        DCFlushRange(lbl_3_bss_B800, 0x40);
        n = v + lbl_3_data_266A4 * 2;
        if (n > 0xFF || n < 0) {
            lbl_3_data_266A4 *= -1;
        }
    }
}

// .text:0x00142030 size:0x58 mapped:0x807810C4
s32 fn_3_142030(s32 a, s32 b, s32 c) {
    return (b / 4) * 4 * c + (a / 4) * 4 * 4 + (b % 4) * 4 + a % 4;
}

// .text:0x00142088 size:0x1D4 mapped:0x8078111C
void fn_3_142088(void) {
    u32 i;
    s32 j;
    s32 w = 4;
    u8* p;
    u32 idx;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            idx = fn_3_142030(j, i, w) * 4;
            if (idx < 0x20) {
                p = lbl_3_bss_B800;
                p += idx;
                p[0] = p[2] = 0xFF;
                p[1] = p[3] = 0x96;
            } else {
                p = lbl_3_bss_B800;
                p += idx;
                p[0] = p[2] = 0;
                p[1] = p[3] = 0;
            }
        }
    }
    GXInitTexObj(&lbl_3_bss_B7C4, lbl_3_bss_B800, 4, 4, GX_TF_RGBA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXInitTexObjLOD(&lbl_3_bss_B7C4, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    lbl_3_data_266A4 = -1;
    lbl_3_bss_B7E4 = 0;
    lbl_3_bss_B7C1 = 0;
}

// .text:0x0014225C size:0x28 mapped:0x807812F0
void fn_3_14225C(void) {
    fn_800B9948(fn_3_141C8C);
}

// .text:0x00142284 size:0x2EC mapped:0x80781318
extern int RandomIndexFromWeights(u8* weights, int count);
s32 LERPToNewRange_Float(s32 value, s32 inMin, s32 inMax, s32 outMin, s32 outMax);
extern u8 lbl_3_data_21E9C[][4];


void fn_3_142284(void) {
    return;
}

// .text:0x00142570 size:0x380 mapped:0x80781604
extern f32 lbl_3_data_21E24[];
extern f32 lbl_3_data_47BC[];
extern const f64 lbl_3_rodata_3840;
extern const f64 lbl_3_rodata_3848;
extern const f64 lbl_3_rodata_3850;
extern const f32 lbl_3_rodata_3858;

static inline f32 sqrt37A8(f32 x) {
    if (x > lbl_3_rodata_3834) {
        double half = lbl_3_rodata_3840;
        double three = lbl_3_rodata_3848;
        double xd = (double)x;
        double guess = __frsqrte(xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        return (float)(xd * guess);
    } else if (x < lbl_3_rodata_3850)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}

// Frames until the nearest incoming ball reaches player i's fielder, 0 if one is already in reach, -1 if none.
s32 fn_3_142570(s8 i) {
    return 0;
}

// .text:0x001428F0 size:0x328 mapped:0x80781984


// CPU picks a target (or swings at nothing). Returns 1 if it acted this frame.
u8 fn_3_1428F0(s8 i, s32 force) {
    return 0;
}

// .text:0x00142C18 size:0x90 mapped:0x80781CAC

// 97%: q/m saved registers swapped (r28/r29); this form matches the inlined copy in fn_3_146928
void fn_3_142C18(void) {
    u8* q;
    s8 i;
    u8 idx;

    q = g_Minigame + 0x1DCC;
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    i = 0;
    do {
        idx = g_Minigame[0x18DC + i];
        q[3] = 1;
        *(s16*)q = RandomInt_Game_Range(((MgRange*)lbl_3_data_21EAC)[idx].lo, ((MgRange*)lbl_3_data_21EAC)[idx].hi);
        i++;
        q += 4;
    } while (i < 4);
}

// .text:0x00142CA8 size:0x10C mapped:0x80781D3C
typedef struct { u8 pad0[0x1890]; s16 a[4]; u8 pad1[0x1B58 - 0x1898]; u8 b[4][10]; } MgArr2;

void fn_3_142CA8(void) {
    MgArr2* m = (MgArr2*)g_Minigame;
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            m->a[i] += m->b[i][j];
            m->b[i][j] = 0;
        }
        g_Minigame[0x1B80 + i] = 0;
    }
}

// .text:0x00142DB4 size:0x31C mapped:0x80781E48
extern f32 lbl_3_data_21BC4[][12];

void fn_3_142DB4(s32 idx) {
    return;
}

// .text:0x001430D0 size:0x288 mapped:0x80782164

void fn_3_1430D0(s32 hand, s32 p) {
    MgBall* b;
    s32 i;
    s16 ch;
    f32 h;
    f32 dy;
    f32 dx;
    f32 dz;
    s32 k;

    for (i = 0; i < 40; i++) {
        if (g_Minigame[i * 0x28 + 0xCE] == 0) { // ball[i].used
            break;
        }
    }
    if (i < 40) {
        b = &((MgBallView*)g_Minigame)->ball[i];
        fn_3_118358(hand, &b->pos.x);
        ch = *(s16*)(g_Fielders + (s8)g_Minigame[p + 0x18F8] * 0x268 + 0x17A);
        k = g_Minigame[p + 0x1CAD];
        h = lbl_3_rodata_385C * ((f32)lbl_3_data_7F10[ch] * charSizeMultipliers[ch][0]);
        dx = lbl_3_data_21B94[k].x - b->pos.x;
        dy = lbl_3_data_21B94[k].y - b->pos.y;
        dz = lbl_3_data_21B94[k].z - b->pos.z;
        dy += ((f32*)lbl_3_data_21D2C)[1] + h;
        b->vel.x = dx / (f32)*(s16*)(lbl_3_data_21E68 + 0x2A);
        b->vel.y = dy / (f32)*(s16*)(lbl_3_data_21E68 + 0x2A);
        b->vel.z = dz / (f32)*(s16*)(lbl_3_data_21E68 + 0x2A);
        b->used = 1;
        b->timer = 0;
        b->owner = p;
        fn_3_15730C(i, b->pos.x, -b->pos.y, b->pos.z);
    }
}

// .text:0x00143358 size:0x3BC mapped:0x807823EC
extern void fn_3_6C854(int, int);

// Moves ball i; a fielder whose player is idle catches it when in reach.
void fn_3_143358(s32 i) {
    return;
}

// .text:0x00143714 size:0x5C mapped:0x807827A8
void fn_3_143714(void) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (g_Minigame[0xCE + i * 0x28] != 0) {
            ((void (*)(s32))fn_3_143358)(i);
        }
    }
}

// .text:0x00143770 size:0x27C mapped:0x80782804
// 98.4%: only preheader scheduling differs (addi r6 g_Minigame / stw -1 order) and loop-end addi order (r6,r8,r9);
// pa/pb pointer pair + local `Vec dir = {0,0,-1}` + x/r float temps are needed for the rest. Tried ~3000 decl/init/header permutations.
s32 fn_3_143770(u8* p) {
    s32 l1[4];
    s32 l2[4];
    Vec d;
    Vec dir = {0.0f, 0.0f, -1.0f};
    s32 n1;
    s32 n2;
    s32* pa;
    s32* pb;
    s32* l;
    s32* n;
    s32 i;
    f32 ang;
    f32 x;
    f32 r;

    if (p[0x2E] == 0) {
        l1[0] = -1;
        l1[1] = -1;
        l1[2] = -1;
        l1[3] = -1;
        n1 = 0;
        n2 = 0;
        pa = l1;
        pb = l2;
        for (i = 0; i < 4; i++, pb++) {
            if (g_Minigame[0x1C9A + i] == 0) {
                if (g_Minigame[0x1C9E + i] == 0) {
                    *pa++ = i;
                    n1++;
                }
                *pb = i;
                n2++;
            }
        }
        if (n1 == 0) {
            if (n2 == 0) {
                for (n2 = 0; n2 < 4; n2++) {
                    l2[n2] = n2;
                }
            }
            l = l2;
            n = &n2;
        } else {
            l = l1;
            n = &n1;
        }
        p[0x35] = l[random_fn_3_9EE24(*n)];
        p[0x34] = g_Minigame[*(s8*)(p + 0x35) + 0x18F8];
        g_Minigame[*(s8*)(p + 0x35) + 0x1C9E] = 1;
    } else {
        p[0x34] = g_Minigame[*(s8*)(p + 0x2F) + 0x18F8];
    }
    PSVECSubtract((Vec*)(g_Fielders + *(s8*)(p + 0x34) * 0x268), (Vec*)p, &d);
    d.y = lbl_3_rodata_3834;
    if (PSVECMag(&d)) {
        PSVECNormalize(&d, &d);
    }
    ang = acos(PSVECDotProduct(&d, &dir));
    x = d.x;
    r = ang;
    if (x < lbl_3_rodata_3834) {
        r = lbl_3_rodata_3868 - ang;
    }
    *(f32*)(p + 0x10) = -r;
    return 1;
}

// .text:0x001439EC size:0x5C0 mapped:0x80782A80
void fn_3_1439EC(s32 idx) {
    return;
}

// .text:0x00143FAC size:0x80 mapped:0x80783040
typedef struct { u8 pad0[0x1A]; s16 f1A; u8 pad1C[0x0E]; u8 st; u8 pad2B[0x0D]; } MgEnt;
void fn_3_143FAC(s32 x) {
    MgEnt *e = (MgEnt*)g_Minigame;
    s32 i;
    if (g_Minigame[0x1CA2] == 2) {
        for (i = 0; i < 3; i++) {
            if (e->st == 2) {
                e->st = 3;
                e->f1A = 0;
            }
            e++;
        }
    }
    ((void (*)(s32))fn_3_1439EC)(x);
}

// .text:0x0014402C size:0x210 mapped:0x807830C0
// 85.7%: original keeps only idx*0x38 in r30 and re-adds g_Minigame after each call (the first base+off is consumed by lhau on +0x1C);
// here CSE keeps base+off in a saved reg (r30) for the s16/f32 stores (u8 stores already re-add). Decl order (cand,q,n,c,i,off) fixed the cand[] regs.
void fn_3_14402C(s32 idx) {
    s32 cand[4];
    u8* q;
    s32 n;
    s32* c;
    s32 i;
    s32 off;

#define MU(K) (g_Minigame + off + (K))
    if (g_Minigame[0x190B] != 0) {
        return;
    }
    off = idx * 0x38;
    if (*(s16*)MU(0x1C) < 0) {
        *(s16*)MU(0x1C) = RandomInt_Game_Range(*(s16*)lbl_3_data_21DC4, *(s16*)(lbl_3_data_21DC4 + 2));
    } else if (g_Minigame[0x1CA3] == 0 && g_Minigame[0x1CA2] == 0) {
        *(s16*)MU(0x1C) = *(s16*)MU(0x1C) - 1;
        if (*(s16*)MU(0x1C) == 0) {
            n = 0;
            q = g_Minigame;
            c = cand;
            for (i = 0; i < 4; i++, q++) {
                if (q[0x1CA9] == 0) {
                    *c++ = i;
                    n++;
                }
            }
            *MU(0x2C) = cand[random_fn_3_9EE24(n)];
            g_Minigame[0x1CA9 + *MU(0x2C)] = 1;
            *MU(0x2D) = lbl_3_data_21E10[*MU(0x2C)];
            *(s16*)MU(0x1C) = *(s16*)(lbl_3_data_21E68 + 0xA);
            *(s16*)MU(0x18) = 0;
            *(s16*)MU(0x1A) = 0;
            *(s16*)MU(0x1E) = 0;
            *MU(0x2A) = 1;
            *MU(0x2B) = 0;
            *(f32*)MU(0x4) = *(f32*)(lbl_3_data_21D1C + 4);
            *(s16*)MU(0x22) = *(s16*)lbl_3_data_21E04 + RandomInt_Game_Range(*(s16*)lbl_3_data_21E04, *(s16*)(lbl_3_data_21E04 + 2));
            *(s16*)MU(0x24) = *(s16*)MU(0x22);
            *(s8*)MU(0x34) = -1;
            *(f32*)MU(0x14) = *(f32*)lbl_3_data_21D1C;
            *(f32*)MU(0xC) = *(f32*)lbl_3_data_21D1C;
            *(f32*)MU(0x10) = ((f32*)lbl_3_data_26698)[idx];
        }
    }
#undef MU
}

// .text:0x0014423C size:0x200 mapped:0x807832D0
void fn_3_14423C(void) {
    u8* g = g_Minigame;
    s32 lo;
    s32 hi;
    s32 n;
    u8* p;
    if (g[0x190B] != 0) {
        return;
    }
    if (g[0x1CA3] != 0) {
        if (g[0x62] == 2 && *(s16*)(g + 0x50) >= lbl_3_data_21DC8[g[0x1A2B]][g[0x1CA4] - 1].lim * 60) {
            g[0x62] = 3;
            g[0x66] = 0;
            *(s16*)(g + 0x52) = 0;
        }
        return;
    }
    if (g[0x1CA4] >= 2) {
        return;
    }
    if (g[0x1909] == 0) {
        lo = lbl_3_data_21DC8[g[0x1A2B]][g[0x1CA4]].lo * 60;
        hi = lbl_3_data_21DC8[g[0x1A2B]][g[0x1CA4]].hi * 60;
    } else {
        lo = lbl_3_data_21DC8[4][g[0x1CA4]].lo * 60;
        hi = lbl_3_data_21DC8[4][g[0x1CA4]].hi * 60;
    }
    if (*(u32*)(g_Minigame + 0x17C0) < lo || *(u32*)(g_Minigame + 0x17C0) > hi) {
        g_Minigame[0x1CA2] = 0;
        return;
    }
    for (n = 0; n < 3; n++) {
        if (g_Minigame[n * 0x38 + 0x2A] != 0) {
            break;
        }
    }
    if (n < 3) {
        if (g_Minigame[0x1CA2] == 0) {
            g_Minigame[0x1CA2] = 2;
        }
        return;
    }
    p = g_Minigame + 0x38;
    p[0x2A] = 1;
    p[0x2B] = 1;
    p[0x2C] = 4;
    p[0x2D] = lbl_3_data_21E10[g[0x1CA4] + 4];
    *(s16*)(p + 0x18) = 0;
    *(s16*)(p + 0x1A) = 0;
    *(s16*)(p + 0x1C) = *(s16*)(lbl_3_data_21E68 + 0xA);
    *(s16*)(p + 0x20) = 0;
    p[0x2E] = 0;
    *(f32*)(p + 0x4) = *(f32*)(lbl_3_data_21D1C + 0xC);
    ((s8*)p)[0x2F] = -1;
    ((s8*)p)[0x30] = -1;
    ((s8*)p)[0x31] = -1;
    ((s8*)p)[0x32] = -1;
    g[0x1CA3] = 1;
    g_Minigame[0x1CA2] = 0;
    g[0x1CA4]++;
}

// .text:0x0014443C size:0x2E0 mapped:0x807834D0
typedef struct { u8 pad0[4]; f32 x; u8 pad8[0x10]; s16 a18; s16 a1A; s16 a1C; s16 a1E; u8 pad20[0xA]; u8 st; u8 sel; u8 who; u8 pad2D[0xB]; } MgSpawn;

void fn_3_14443C(void) {
    MgSpawn* p;
    s32 i;
    u8* g;
    s16* tb;
    f32* v;
    s32 k;

    fn_3_14423C();
    g = g_Minigame;
    p = (MgSpawn*)g;
    tb = (s16*)lbl_3_data_21E68;
    i = 0;
    do {
        if (p->a18 < 0x7FFE) {
            p->a18 = p->a18 + 1;
        } else {
            p->a18 = 0x7FFF;
        }
        if (p->a1A < 0x7FFE) {
            p->a1A = p->a1A + 1;
        } else {
            p->a1A = 0x7FFF;
        }
        if (p->a1E != 0) {
            if (p->a1E < 0x7FFE) {
                p->a1E = p->a1E + 1;
            } else {
                p->a1E = 0x7FFF;
            }
        }
        if (p->st == 0) {
            ((void (*)(s32))fn_3_14402C)(i);
        } else if (p->st == 1) {
            p->a1C -= 1;
            v = (f32*)(lbl_3_data_21D1C + p->sel * 8);
            p->x = (v[1] - v[0]) * ((f32)p->a1A / (f32)tb[5]) + *(f32*)(lbl_3_data_21D1C + p->sel * 8);
            if (p->a1C <= 0) {
                p->st = 2;
                p->a1A = 0;
            }
        } else if (p->st == 2) {
            if (g[0x1CA2] == 2) {
                MgSpawn* e = (MgSpawn*)g;
                for (k = 0; k < 3; k++) {
                    if (e->st == 2) {
                        e->st = 3;
                        e->a1A = 0;
                    }
                    e++;
                }
            }
            ((void (*)(s32))fn_3_1439EC)(i);
        } else if (p->st == 3) {
            v = (f32*)(lbl_3_data_21D1C + p->sel * 8);
            p->x = (v[0] - v[1]) * ((f32)p->a1A / (f32)tb[6]) + v[0];
            if (p->a1A >= tb[6]) {
                p->st = 0;
                p->a1A = 0;
                g_Minigame[p->who + 0x1CA9] = 0;
                if (g[0x1CA3] != 0) {
                    g[0x1CA3] = 0;
                }
            }
        } else if (p->st == 4) {
            if (p->a1C != 0) {
                p->a1C -= 1;
            }
            if (p->a1A >= tb[8]) {
                p->st = 0;
                p->a1A = 0;
            }
        }
        i++;
        p++;
    } while (i < 3);
}

// .text:0x0014471C size:0x3C0 mapped:0x807837B0
extern u8 lbl_3_data_21E1C[];

// Object positions / velocities at g_Minigame + 0xCD0 / + 0x1180 (50 each).
#define MG_OBJ_POS(n) ((Vec*)(g_Minigame + 0xCD0) + (n))
#define MG_OBJ_VEL(n) ((Vec*)(g_Minigame + 0x1180) + (n))

// Player p releases the object it is holding: place it at the hand and aim it at the fielder's target.
void fn_3_14471C(s32 p) {
    return;
}

// .text:0x00144ADC size:0x1DC mapped:0x80783B70
void fn_3_144ADC(s32 p) {
    u8* in = g_Controls + (s8)g_Minigame[p + 0x18CC] * 16;
    f32 d;
    u8* f = g_Fielders + (s8)g_Minigame[p + 0x18F8] * 0x268;

    if (g_Minigame[p + 0x18D8] != 0) {
        in = g_Minigame + (s8)g_Minigame[p + 0x18CC] * 16 + 0x1D7C;
    }
    if (((s16*)(g_Minigame + 0x1B44))[p] < 0x7FFE) {
        ((s16*)(g_Minigame + 0x1B44))[p]++;
    } else {
        ((s16*)(g_Minigame + 0x1B44))[p] = 0x7FFF;
    }
    switch (g_Minigame[0x1CA5 + p]) {
    case 1:
        d = ((f32*)lbl_3_data_21D2C)[0] - ((f32*)lbl_3_data_21D2C)[1];
        *(f32*)(f+0xC) = d * ((f32)((s16*)(g_Minigame + 0x1B44))[p] / (f32)*(s16*)(lbl_3_data_21E68 + 0x20)) + ((f32*)lbl_3_data_21D2C)[1];
        if (((s16*)(g_Minigame + 0x1B44))[p] >= *(s16*)(lbl_3_data_21E68 + 0x20)) {
            g_Minigame[0x1CA5 + p] = 2;
            ((s16*)(g_Minigame + 0x1B44))[p] = 0;
        }
        break;
    case 2:
        if (!(*(u16*)(in + 4) & 4)) {
            g_Minigame[0x1CA5 + p] = 3;
            ((s16*)(g_Minigame + 0x1B44))[p] = 0;
        }
        break;
    case 3:
        d = ((f32*)lbl_3_data_21D2C)[1] - ((f32*)lbl_3_data_21D2C)[0];
        *(f32*)(f+0xC) = d * ((f32)((s16*)(g_Minigame + 0x1B44))[p] / (f32)*(s16*)(lbl_3_data_21E68 + 0x20)) + ((f32*)lbl_3_data_21D2C)[0];
        if (((s16*)(g_Minigame + 0x1B44))[p] >= *(s16*)(lbl_3_data_21E68 + 0x20)) {
            g_Minigame[0x1CA5 + p] = 0;
            ((s16*)(g_Minigame + 0x1B44))[p] = 0;
        }
        break;
    }
}

// .text:0x00144CB8 size:0x704 mapped:0x80783D4C
extern f32 game_atan2(f32 x, f32 y);
extern void fn_3_1573AC(u8* o);
extern int rand(void);
extern int __abs(int);
extern s8 lbl_3_data_21E20[];
extern const f64 lbl_3_rodata_3870;

// Per-player update: jump/catch animation, then aiming and throwing the held object.
void fn_3_144CB8(void) {
    return;
}

// .text:0x001453BC size:0x714 mapped:0x80784450
extern void fn_3_147CFC(void* arg);
extern void fn_3_154238(s16 id);
extern void fn_3_1608F0(s32 kind, s32 value, s32 extra);
extern void fn_80062BE4(Vec* pos);
extern void* memcpy(void*, const void*, u32);
extern u8 lbl_3_data_21E18[][2];
extern u8 lbl_3_common_bss_37400[];
extern const f32 lbl_3_rodata_3878;

// Flight of a thrown object (idx): bombs (kind 5) blow up at their target player, others can hit a runner.
void fn_3_1453BC(s32 idx) {
    return;
}

// .text:0x00145AD0 size:0xC8 mapped:0x80784B64
typedef struct { f32 x; f32 y; f32 z; } MgV3;

// 97%: volatile regs allocated differently (k r7 vs r8); this form matches the inlined copy in fn_3_145EB8.
// ((f32*)(g_Minigame + 0xCD0))[p * 3] stores match this function but break fn_3_145EB8.
void fn_3_145AD0(s32 p) {
    s8 t;
    s32 k;
    u8* m;
    u8* g;

    k = 0;
    t = *(s8*)(g_Minigame + p + 0x1BB6);
    m = g_Minigame + t * 3;
    for (; k < 3; k++, m++) {
        if (*(s8*)(m + 0x1C7E) == p) {
            break;
        }
    }
    g = g_Minigame + p * 0xC;
    *(f32*)(g + 0xCD0) = ((MgV3*)(lbl_3_data_21D34 + g_Minigame[t + 0x1CAD] * 0x24))[k].x;
    *(f32*)(g + 0xCD4) = ((MgV3*)(lbl_3_data_21D34 + g_Minigame[t + 0x1CAD] * 0x24))[k].y;
    *(f32*)(g + 0xCD8) = ((MgV3*)(lbl_3_data_21D34 + g_Minigame[t + 0x1CAD] * 0x24))[k].z;
}

// .text:0x00145B98 size:0x320 mapped:0x80784C2C
// Refill each active player's queue of 3 held objects (g_Minigame + 0x1C7E + p * 3) from free object slots.
void fn_3_145B98(void) {
    return;
}

// .text:0x00145EB8 size:0x13C mapped:0x80784F4C
void fn_3_145EB8(void) {
    s32 i;
    u8 v;

    ((void (*)(void))fn_3_145B98)();
    for (i = 0; i < 50; i++) {
        v = g_Minigame[i + 0x193A];
        if (v == 5 || v == 6) {
            fn_3_1453BC(i);
        } else if (v == 2) {
            fn_3_145AD0(i);
        }
    }
}

// .text:0x00145FF4 size:0x1B0 mapped:0x80785088
typedef struct { u8 pad0[0x1C]; s16 b; u8 pad1[0x2A - 0x1E]; u8 a; u8 c; u8 pad2[0x38 - 0x2C]; } MgPl38;
typedef struct { u8 pad0[0x193A]; u8 state[50]; u8 pad1[0x1BB6 - 0x193A - 50]; s8 slot[50]; } Mg145F;

void fn_3_145FF4(void) {
    u32 i;
    fn_3_157570();
    fn_3_DE4FC();
    if (g_Minigame[0x1A2B] <= 2 && g_Minigame[0x1909] == 0) {
        if (g_Minigame[0x18E8 + *(s8*)(g_Minigame + 0x1908)] == 1 && g_Minigame[0x19A8] == 0) {
            g_Minigame[0x1A37] = 1;
        } else {
            g_Minigame[0x1A37] = 2;
        }
    }
    fn_3_5A6D4(0xE);
    for (i = 0; i < 50; i++) {
        ((Mg145F*)g_Minigame)->state[i] = 0;
        ((Mg145F*)g_Minigame)->slot[i] = -1;
    }
    *(s16*)(g_Minigame + 0x1B4C) = 0x3C;
    for (i = 0; i < 3; i++) {
        ((void (*)(s32))fn_3_14402C)(i);
        ((MgPl38*)g_Minigame)[i].a = 2;
        ((MgPl38*)g_Minigame)[i].b = 1;
        ((MgPl38*)g_Minigame)[i].c = 0;
    }
    fn_3_154214();
}

// .text:0x001461A4 size:0x264 mapped:0x80785238
void fn_3_1461A4(void) {
    if (g_Minigame[0x190B] == 0) {
        if (*(u32*)(g_Minigame + 0x17C4) == 0) {
            g_Minigame[0x190B] = 1;
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        return;
    }
    if (g_Minigame[0x190B] == 1) {
        g_Minigame[0x190B] = 2;
        *(s16*)(g_GameLogic + 0x100) = *(s16*)(lbl_3_data_21E68 + 0x22);
    }
    if (--*(s16*)(g_GameLogic + 0x100) == 7) {
        changeScene(3, 6);
    }
    if (*(s16*)(g_GameLogic + 0x100) <= 0) {
        fn_3_145FF4();
    }
}

// .text:0x00146408 size:0x520 mapped:0x8078549C
extern s32 fn_3_108854(void);
extern u16 lbl_3_data_81FC[];

// Per-frame update of the minigame.
void fn_3_146408(void) {
    return;
}

// .text:0x00146928 size:0xA4 mapped:0x807859BC
void fn_3_146928(void) {
    fn_3_142C18();
    changeScene(1, 6);
    fn_3_5A6D4(2);
}

// .text:0x001469CC size:0xC4 mapped:0x80785A60
void fn_3_1469CC(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        *(s16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFE) > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00146A90 size:0x730 mapped:0x80785B24
extern void fn_3_59A90(void);
extern void fn_3_591AC(void);
extern void fn_3_58870(void);
extern void fn_3_6E24C(int rosterID, int fielderIdx);
extern void fn_3_157588(int);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern s32 g_Scores; // TODO type: first field (inning) of GameScores
extern u8 lbl_3_data_2127C[][5];
extern u8 lbl_3_data_21E08[];
extern const f32 lbl_3_rodata_387C;

// Minigame init (first call), then the texture for the TEV hook.
void fn_3_146A90(void) {
    return;
}

