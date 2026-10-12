// g_Minigame stays a byte array here (the matched code's register allocation depends on it); MG is
// its typed view.
#define g_Minigame g_Minigame_header_decl
#include "game/rep_37A8.h"
#undef g_Minigame
extern u8 g_Minigame[];
#define REP_HEADER_FN repHeader_37A8
#include "header_rep_inline.h"

#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"
#include "Dolphin/gx.h"
#include "main/file_80011640.h"
#include "main/file_80008E00.h"
#include "math.h"
extern const Vec lbl_3_rodata_3808;
extern const f32 lbl_3_rodata_382C;
extern const f32 lbl_3_rodata_3830;
extern const f32 lbl_3_rodata_3834;
extern const f32 lbl_3_rodata_3838;
extern const f32 lbl_3_rodata_385C;
extern const f64 lbl_3_rodata_3868;
extern void fn_800B993C(void);
extern u8 lbl_3_data_21278[];
extern void fn_3_10F550(s32, u8);
extern void fn_3_5A6D4(s32);
extern void changeScene(s32, s32);
extern void* memset(void*, s32, u32);
extern s16 RandomInt_Game_Range(s16, s16);
extern s16 lbl_3_data_21EAC[];
extern Vec lbl_3_data_21D34[4][3]; // held-object offsets per home slot
extern s8 lbl_3_data_266A4;
extern void DCFlushRange(void*, u32);
extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern s16 lbl_3_data_21E68[26]; // timings in frames
#define MG ((Mg37A8*)g_Minigame)
// Some matched functions need the original byte-array address arithmetic (`base + (i + offset)`,
// `base + i * stride`), which MG->field[i] / g_Fielders[i] reschedule. These keep it with named fields.
#define MG_B(field, i) (g_Minigame[(i) + (s32)OFFSET_OF(Mg37A8, field)]) // u8 field element
#define MG_BALL_USED(i) (g_Minigame[(i) * (s32)sizeof(MgBall) + (s32)OFFSET_OF(Mg37A8, ball[0].used)])
#define MG_H(field) ((s16*)(g_Minigame + (s32)OFFSET_OF(Mg37A8, field))) // s16 array field
#define FLD(i) ((InMemFielderType*)((u8*)g_Fielders + (i) * (s32)sizeof(InMemFielderType)))
typedef struct { s16 lo; s16 hi; } MgRange;
typedef struct { s16 lo; s16 hi; s16 lim; } MgWin;
extern MgWin lbl_3_data_21DC8[][2];
extern u8 lbl_3_data_21E10[];
extern f32 lbl_3_data_21D1C[4];
extern s16 lbl_3_data_21DC4[2];
extern s16 lbl_3_data_21E04[2];
extern f32 lbl_3_data_26698[3];
extern int random_fn_3_9EE24(int max);
extern f32 lbl_3_data_21D2C[2];
extern InMemFielderType g_Fielders[9];
extern s8 lbl_3_data_21EBC[];
extern s8 lbl_3_data_21EC0[];
extern int RandomInt_Game(int);
extern s16 lbl_3_data_7F10[];
extern Vec lbl_3_data_21B94[]; // home positions per player slot
extern void fn_3_118358(s32, f32*);
extern void fn_3_15730C(u32, f32, f32, f32);
extern void fn_3_157570(void);
extern void fn_3_DE4FC(void);
extern void fn_3_154214(void);
extern u32 fn_3_90064(s32 id);

// This unit's .bss (B7C0..B850) as statics, declared in reverse address order:
// a flashing 4x4 RGBA8 texture used by the TEV hook fn_3_141C8C.
static u8 lbl_3_bss_B800[0x50] ATTRIBUTE_ALIGN(32); // texel data (0x40 used)
static s32 lbl_3_bss_B7E4;                          // frame tick for the flash
static GXTexObj lbl_3_bss_B7C4;                     // texture object
static u8 lbl_3_bss_B7C1;                           // hook frame counter
static u8 lbl_3_bss_B7C0;

// .data 0x00026698..0x000266A8
f32 lbl_3_data_26698[3] = {0.5f, 0.0f, -0.5f};
s8 lbl_3_data_266A4 = -1;

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

    lbl_3_bss_B7E4 = lbl_3_bss_B7E4 + (lbl_80366158._28 == 0);
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


// NONMATCHING 90.9%: port is re-sign-extended at each use in the original (extsb x2) and the loop pointers get other registers
#if NONMATCHING
void fn_3_142284(void) {
    s32 dist[4];
    s32* d;
    InputStruct* pad;
    u8 port;
    s8 i;

    d = dist;
    i = 0;
    do {
        MgCpu* cpu = &MG->cpuIn.cpu[i];
        port = MG->port[i];
        if ((s8)port >= 0 && (s8)port < 4) {
            *d = fn_3_142570(i);
            if (MG->isCpu[i] != 0) {
                pad = &MG->cpuIn.pad[(s8)port];
                memset(pad, 0, sizeof(InputStruct));
                switch (cpu->state) {
                case 0:
                    if (*d >= 0) {
                        switch (RandomIndexFromWeights(lbl_3_data_21E9C[MG->cpuLevel[i]], 4)) {
                        case 0:
                            if (*d > LERPToNewRange_Float(MG->combo[i], 0, lbl_3_data_21E68[19], lbl_3_data_21E68[2],
                                                          lbl_3_data_21E68[3]) + 3) {
                                if (fn_3_1428F0(i, 0)) {
                                    cpu->state = 1;
                                }
                            } else {
                                pad->newButtonInput |= 4;
                                pad->buttonInput |= 4;
                                cpu->state = 2;
                            }
                            break;
                        case 1:
                            if (*d > lbl_3_data_21E68[2] + 3) {
                                if (fn_3_1428F0(i, 0)) {
                                    cpu->state = 1;
                                }
                            } else {
                                pad->newButtonInput |= 4;
                                pad->buttonInput |= 4;
                                cpu->state = 2;
                            }
                            break;
                        case 2:
                            pad->newButtonInput |= 4;
                            pad->buttonInput |= 4;
                            cpu->state = 2;
                            break;
                        case 3:
                            if (fn_3_1428F0(i, 1)) {
                                cpu->state = 1;
                            }
                            break;
                        }
                    } else {
                        if (fn_3_1428F0(i, 0)) {
                            cpu->state = 1;
                        }
                    }
                    break;
                case 1:
                    if (MG->aim[i] < 0) {
                        cpu->state = 0;
                    }
                    break;
                case 2:
                    pad->buttonInput |= 4;
                    if (MG->jump[i] != 1) {
                        cpu->state = 3;
                    }
                    break;
                case 3:
                    if (*d >= 0) {
                        pad->buttonInput |= 4;
                    } else {
                        cpu->state = 4;
                    }
                    break;
                case 4:
                    if (MG->jump[i] != 3) {
                        cpu->state = 0;
                    }
                    break;
                }
            }
        } else {
            *d = -1;
        }
        i++;
        d++;
    } while (i < 4);
}
#endif

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
// NONMATCHING 90.9%: one-register shift (r10->r9) throughout and the initial loop branch; logic matches
#if NONMATCHING
s32 fn_3_142570(s8 i) {
    InMemFielderType* f;
    MgBall* b;
    f32 reach;
    f32 dx;
    f32 dz;
    f32 d;
    f32 v;
    s32 best;
    s32 t;
    u8 found;
    s8 j;
    s16 lim;

    f = &g_Fielders[MG->fielder[i]];
    reach = lbl_3_data_21E24[2] + lbl_3_data_47BC[f->weight];
    best = 10000;
    found = 0;
    j = 0;
    do {
        b = &MG->ball[j];
        if (b->used != 0) {
            dz = f->pos.z - b->pos.z;
            dx = f->pos.x - b->pos.x;
            d = sqrt37A8(dx * dx + dz * dz);
            if (d < reach) {
                return 0;
            }
            dx /= d;
            dz /= d;
            v = sqrt37A8(b->vel.x * b->vel.x + b->vel.z * b->vel.z);
            if (dx * (b->vel.x / v) + dz * (b->vel.z / v) >= lbl_3_rodata_3858) {
                t = (d - reach) / v;
                if (t < best) {
                    best = t;
                }
                found = 1;
            }
        }
        j++;
    } while (j < 40);
    lim = lbl_3_data_21E68[23];
    for (j = 0; j < 50; j++) {
        if (MG->objState[j] == 6 && MG->objKind[j] == 5 && i == -1 - MG->objTarget[j]) {
            t = lim - MG->objTimer[j];
            if (t >= 0) {
                if (t < best) {
                    best = t;
                }
                found = 1;
            }
        }
    }
    if (found) {
        return best;
    }
    return -1;
}
#endif

// .text:0x001428F0 size:0x328 mapped:0x80781984


// CPU picks a target (or swings at nothing). Returns 1 if it acted this frame.
// NONMATCHING 91.1%: original keeps the bomb kind in an extra saved register (r23) and loads the RandomInt range with lhax
#if NONMATCHING
u8 fn_3_1428F0(s8 i, s32 force) {
    MgCpu* cpu;
    MgRunner* e;
    InputStruct* pad;
    s8 idx;
    u8 hit;
    s8 cnt;
    u8 pick;
    u8 port;
    u8 diff;
    s8 tgt;
    u8 kind;
    s8 k;

    idx = -1;
    cpu = &MG->cpuIn.cpu[i];
    hit = 0;
    cnt = 0;
    pick = cpu->_3;
    port = MG->port[i];
    diff = MG->cpuLevel[i];
    if (cpu->timer >= 0) {
        cpu->timer--;
    }
    tgt = MG->held[i][0];
    if (tgt < 0) {
        return 0;
    }
    e = MG->runner;
    for (k = 0; k < 3; k++, e++) {
        if (e->st == 2) {
            cnt++;
            if (MG->runner[(s8)pick].who == 4) {
                idx = k;
                break;
            }
        }
    }
    if (idx < 0 && cpu->timer >= 0 && (u8)force == 0) {
        return 0;
    }
    kind = MG->objKind[tgt];
    if (kind != 5 || (cnt != 0 && RandomInt_Game(100) >= lbl_3_data_21EC0[diff])) {
        if (cnt == 0) {
            return 0;
        }
        if (RandomInt_Game(100) < lbl_3_data_21EBC[diff]) {
            hit = 1;
        }
        if (!hit) {
            e = &MG->runner[(s8)pick];
            if (e->st == 2 && (kind == e->who || kind == 5 || e->who == 4)) {
                hit = 1;
            }
        }
        if (!hit) {
            e = MG->runner;
            for (k = 0; k < 3; k++, e++) {
                if (e->st == 2 && (kind == e->who || kind == 5 || e->who == 4)) {
                    pick = k;
                    hit = 1;
                    break;
                }
            }
        }
    }
    if (hit) {
        switch ((s8)pick) {
        case 0:
            pad = &MG->cpuIn.pad[(s8)port];
            pad->newButtonInput |= 0x102;
            pad->buttonInput |= 0x102;
            break;
        case 1:
            pad = &MG->cpuIn.pad[(s8)port];
            pad->newButtonInput |= 0x108;
            pad->buttonInput |= 0x108;
            break;
        case 2:
            pad = &MG->cpuIn.pad[(s8)port];
            pad->newButtonInput |= 0x101;
            pad->buttonInput |= 0x101;
            break;
        }
        cpu->_3 = pick;
    } else {
        pad = &MG->cpuIn.pad[(s8)port];
        pad->newButtonInput |= 0x200;
        pad->buttonInput |= 0x200;
    }
    cpu->timer = RandomInt_Game_Range(((MgRange*)lbl_3_data_21EAC)[diff].lo, ((MgRange*)lbl_3_data_21EAC)[diff].hi);
    return 1;
}
#endif

// .text:0x00142C18 size:0x90 mapped:0x80781CAC

// 97%: q/m saved registers swapped (r28/r29); this form matches the inlined copy in fn_3_146928
void fn_3_142C18(void) {
    MgCpu* q;
    s8 i;
    u8 idx;

    q = MG->cpuIn.cpu;
    memset(&MG->cpuIn, 0, sizeof(MgCpuArea));
    i = 0;
    do {
        idx = MG->cpuLevel[i];
        q->_3 = 1;
        q->timer = RandomInt_Game_Range(((MgRange*)lbl_3_data_21EAC)[idx].lo, ((MgRange*)lbl_3_data_21EAC)[idx].hi);
        i++;
        q++;
    } while (i < 4);
}

// .text:0x00142CA8 size:0x10C mapped:0x80781D3C
void fn_3_142CA8(void) {
    Mg37A8* m = MG;
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            m->score[i] += m->hitLog[i][j];
            m->hitLog[i][j] = 0;
        }
        MG->hitLogCount[i] = 0;
    }
}

// .text:0x00142DB4 size:0x31C mapped:0x80781E48
extern f32 lbl_3_data_21BC4[][12];

void fn_3_142DB4(s32 idx) {
    MgRunner* r = &MG->runner[idx];
    MgBall* b;
    s32 i;
    s16 ch;
    f32 h;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 k;

    for (i = 0; i < 40; i++) {
        if (MG->ball[i].used == 0) {
            break;
        }
    }
    if (i < 40) {
        b = &MG->ball[i];
        if (r->sel != 0) {
            b->pos.x = lbl_3_data_21BC4[idx][9];
            b->pos.y = lbl_3_data_21BC4[idx][10];
            b->pos.z = lbl_3_data_21BC4[idx][11];
        } else {
            b->pos.x = lbl_3_data_21BC4[idx][6];
            b->pos.y = lbl_3_data_21BC4[idx][7];
            b->pos.z = lbl_3_data_21BC4[idx][8];
        }
        b->_22 = r->player;
        ch = FLD(r->fielder)->charID;
        b->owner = r->player;
        k = MG_B(home, r->player);
        h = lbl_3_rodata_385C * ((f32)lbl_3_data_7F10[ch] * charSizeMultipliers[ch][0]);
        dx = lbl_3_data_21B94[k].x - b->pos.x;
        dy = lbl_3_data_21B94[k].y - b->pos.y;
        dz = lbl_3_data_21B94[k].z - b->pos.z;
        dy += lbl_3_data_21D2C[1] + h;
        b->vel.x = dx / (f32)lbl_3_data_21E68[22];
        b->vel.y = dy / (f32)lbl_3_data_21E68[22];
        b->vel.z = dz / (f32)lbl_3_data_21E68[22];
        b->_18 = lbl_3_rodata_3834;
        b->used = 2;
        b->timer = 0;
        fn_3_15730C(i, b->pos.x, -b->pos.y, b->pos.z);
    }
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
        if (MG_BALL_USED(i) == 0) {
            break;
        }
    }
    if (i < 40) {
        b = &MG->ball[i];
        fn_3_118358(hand, &b->pos.x);
        ch = FLD((s8)MG_B(fielder, p))->charID;
        k = MG_B(home, p);
        h = lbl_3_rodata_385C * ((f32)lbl_3_data_7F10[ch] * charSizeMultipliers[ch][0]);
        dx = lbl_3_data_21B94[k].x - b->pos.x;
        dy = lbl_3_data_21B94[k].y - b->pos.y;
        dz = lbl_3_data_21B94[k].z - b->pos.z;
        dy += lbl_3_data_21D2C[1] + h;
        b->vel.x = dx / (f32)lbl_3_data_21E68[21];
        b->vel.y = dy / (f32)lbl_3_data_21E68[21];
        b->vel.z = dz / (f32)lbl_3_data_21E68[21];
        b->used = 1;
        b->timer = 0;
        b->owner = p;
        fn_3_15730C(i, b->pos.x, -b->pos.y, b->pos.z);
    }
}

// .text:0x00143358 size:0x3BC mapped:0x807823EC
extern void fn_3_6C854(int, int);

// Moves ball i; a fielder whose player is idle catches it when in reach.
// NONMATCHING 97.3%: only the dir.x/dir.z/lbl_3_data_21E24[15] loads after PSVECNormalize are scheduled differently
#if NONMATCHING
void fn_3_143358(s32 i) {
    MgBall* b;
    InMemFielderType* f;
    s32 k;
    u8 fi;
    Vec dir;

    b = &MG->ball[i];
    b->timer++;
    if (b->timer > lbl_3_data_21E68[10]) {
        b->used = 0;
        return;
    }
    b->pos.x += b->vel.x;
    b->pos.y += b->vel.y;
    b->pos.z += b->vel.z;
    if (b->used == 2) {
        b->vel.y += b->_18;
    }
    if (b->pos.y < lbl_3_data_21E24[13]) {
        if (b->pos.z < lbl_3_rodata_3834) {
            if (b->used == 2) {
                MG->targeted[b->owner] = 0;
            }
            b->used = 0;
            return;
        }
        b->vel.y = -b->vel.y;
    }
    for (k = 0; k < 4; k++) {
        if ((s8)(fi = MG->fielder[k]) >= 0) {
            f = &g_Fielders[(s8)fi];
            if (MG->jump[k] == 0) {
                if (lbl_3_data_21E24[2] + lbl_3_data_47BC[f->weight] >
                    sqrt37A8((b->pos.x - f->pos.x) * (b->pos.x - f->pos.x) +
                             (b->pos.z - f->pos.z) * (b->pos.z - f->pos.z))) {
                    if (b->used == 2) {
                        MG->targeted[b->owner] = 0;
                    }
                    b->used = 0;
                    if (MG->stun[k] == 0) {
                        MG->stun[k] = 1;
                        MG->stunTimer[k] = lbl_3_data_21E68[14];
                        MG->combo[k] = 0;
                        dir.x = b->vel.x;
                        dir.y = lbl_3_rodata_3834;
                        dir.z = b->vel.z;
                        PSVECNormalize(&dir, &dir);
                        f->_038 = dir.x;
                        MG->knocked[k] = 1;
                        f->_03C = dir.z;
                        f->speed = lbl_3_data_21E24[15];
                        fn_3_6C854(MG->port[k], 2);
                        if (MG->hits[k] < 0xFFFE) {
                            MG->hits[k]++;
                        } else {
                            MG->hits[k] = 0xFF;
                        }
                    }
                    return;
                }
            }
        }
    }
}
#endif

// .text:0x00143714 size:0x5C mapped:0x807827A8
void fn_3_143714(void) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (MG->ball[i].used != 0) {
            ((void (*)(s32))fn_3_143358)(i);
        }
    }
}

// .text:0x00143770 size:0x27C mapped:0x80782804
// 98.4%: only preheader scheduling differs (addi r6 g_Minigame / stw -1 order) and loop-end addi order (r6,r8,r9);
// pa/pb pointer pair + local `Vec dir = {0,0,-1}` + x/r float temps are needed for the rest. Tried ~3000 decl/init/header permutations.
s32 fn_3_143770(u8* p) { // p: MgRunner (rep_3310 passes its own view)
    MgRunner* e = (MgRunner*)p;
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

    if (e->_2E == 0) {
        l1[0] = -1;
        l1[1] = -1;
        l1[2] = -1;
        l1[3] = -1;
        n1 = 0;
        n2 = 0;
        pa = l1;
        pb = l2;
        for (i = 0; i < 4; i++, pb++) {
            if (MG->stun[i] == 0) {
                if (MG->targeted[i] == 0) {
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
        e->player = l[random_fn_3_9EE24(*n)];
        e->fielder = MG->fielder[e->player];
        MG->targeted[e->player] = 1;
    } else {
        e->fielder = MG_B(fielder, e->queue[0]);
    }
    PSVECSubtract(&g_Fielders[e->fielder].pos, &e->pos, &d);
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
    e->_10 = -r;
    return 1;
}

// .text:0x001439EC size:0x5C0 mapped:0x80782A80
void fn_3_1439EC(s32 idx) {
    MgRunner* r = &MG->runner[idx];
    s32 k;

    if (r->sel != 0) {
        r->throwTimer++;
        if (r->throwTimer == 1) {
            r->_2E = 0;
        }
        if (r->throwTimer >= lbl_3_data_21E68[12]) {
            r->throwTimer = 0;
            for (k = 0; k < 4; k++) {
                fn_3_1430D0(idx, k);
                fn_3_90064(0x2DA);
            }
            r->_2E = 1;
        }
    } else if (r->_2E != 0) {
        r->queueTimer++;
        if (r->queueTimer == lbl_3_data_21E68[13]) {
            fn_3_1430D0(idx, r->queue[0]);
            r->fielder = -1;
            r->queue[0] = r->queue[1];
            r->queue[1] = r->queue[2];
            r->queue[2] = r->queue[3];
            r->queue[3] = -1;
            if (r->queue[0] < 0) {
                r->_2E = 0;
            }
            r->queueTimer = 0;
            fn_3_90064(0x2DA);
        }
    }
}

// .text:0x00143FAC size:0x80 mapped:0x80783040
void fn_3_143FAC(s32 x) {
    MgRunner* e = MG->runner;
    s32 i;
    if (MG->_1CA2 == 2) {
        for (i = 0; i < 3; i++) {
            if (e->st == 2) {
                e->st = 3;
                e->_1A = 0;
            }
            e++;
        }
    }
    ((void (*)(s32))fn_3_1439EC)(x);
}

// .text:0x0014402C size:0x210 mapped:0x807830C0
// ~84%: original keeps only idx*0x38 in r30 and re-adds g_Minigame after each call (the first base+off is consumed by lhau on +0x1C);
// here CSE keeps base+off in a saved reg (r30) for the s16/f32 stores. The byte-offset form (`*(s16*)(g_Minigame + off + 0x1C)`)
// got 85.7% (it reproduces the lhau); typed fields fold +0x1C into the lha. Decl order (cand,q,n,c,i,off) fixed the cand[] regs.
void fn_3_14402C(s32 idx) {
    s32 cand[4];
    u8* q;
    s32 n;
    s32* c;
    s32 i;
    s32 off;

#define MU(K) (((MgRunner*)(g_Minigame + off))->K)
    if (MG_B(turnOverStatus, 0) != 0) {
        return;
    }
    off = idx * 0x38;
    if (MU(_1C) < 0) {
        MU(_1C) = RandomInt_Game_Range(lbl_3_data_21DC4[0], lbl_3_data_21DC4[1]);
    } else if (MG_B(bossActive, 0) == 0 && MG_B(_1CA2, 0) == 0) {
        MU(_1C) = MU(_1C) - 1;
        if (MU(_1C) == 0) {
            n = 0;
            q = g_Minigame;
            c = cand;
            for (i = 0; i < 4; i++, q++) {
                if (q[(s32)OFFSET_OF(Mg37A8, kindUsed)] == 0) {
                    *c++ = i;
                    n++;
                }
            }
            MU(who) = cand[random_fn_3_9EE24(n)];
            MG->kindUsed[MU(who)] = 1;
            MU(_2D) = lbl_3_data_21E10[MU(who)];
            MU(_1C) = lbl_3_data_21E68[5];
            MU(_18) = 0;
            MU(_1A) = 0;
            MU(_1E) = 0;
            MU(st) = 1;
            MU(sel) = 0;
            MU(pos.y) = lbl_3_data_21D1C[1];
            MU(_22) = lbl_3_data_21E04[0] + RandomInt_Game_Range(lbl_3_data_21E04[0], lbl_3_data_21E04[1]);
            MU(_24) = MU(_22);
            MU(fielder) = -1;
            MU(_14) = lbl_3_rodata_3834;
            MU(_C) = lbl_3_rodata_3834;
            MU(_10) = lbl_3_data_26698[idx];
        }
    }
#undef MU
}

// .text:0x0014423C size:0x200 mapped:0x807832D0
void fn_3_14423C(void) {
    Mg37A8* g = MG;
    s32 lo;
    s32 hi;
    s32 n;
    MgRunner* p;
    if (g->turnOverStatus != 0) {
        return;
    }
    if (g->bossActive != 0) {
        if (g->runner[1].st == 2 && g->runner[1]._18 >= lbl_3_data_21DC8[g->difficulty][g->bossCount - 1].lim * 60) {
            g->runner[1].st = 3;
            g->runner[1]._2E = 0;
            g->runner[1]._1A = 0;
        }
        return;
    }
    if (g->bossCount >= 2) {
        return;
    }
    if (g->multiPlayerInd == 0) {
        lo = lbl_3_data_21DC8[g->difficulty][g->bossCount].lo * 60;
        hi = lbl_3_data_21DC8[g->difficulty][g->bossCount].hi * 60;
    } else {
        lo = lbl_3_data_21DC8[4][g->bossCount].lo * 60;
        hi = lbl_3_data_21DC8[4][g->bossCount].hi * 60;
    }
    if (MG->frame < lo || MG->frame > hi) {
        MG->_1CA2 = 0;
        return;
    }
    for (n = 0; n < 3; n++) {
        if (MG->runner[n].st != 0) {
            break;
        }
    }
    if (n < 3) {
        if (MG->_1CA2 == 0) {
            MG->_1CA2 = 2;
        }
        return;
    }
    p = &MG->runner[1];
    p->st = 1;
    p->sel = 1;
    p->who = 4;
    p->_2D = lbl_3_data_21E10[g->bossCount + 4];
    p->_18 = 0;
    p->_1A = 0;
    p->_1C = lbl_3_data_21E68[5];
    p->throwTimer = 0;
    p->_2E = 0;
    p->pos.y = lbl_3_data_21D1C[3];
    p->queue[0] = -1;
    p->queue[1] = -1;
    p->queue[2] = -1;
    p->queue[3] = -1;
    g->bossActive = 1;
    MG->_1CA2 = 0;
    g->bossCount++;
}

// .text:0x0014443C size:0x2E0 mapped:0x807834D0
void fn_3_14443C(void) {
    MgRunner* p;
    s32 i;
    Mg37A8* g;
    s16* tb;
    f32* v;
    s32 k;

    fn_3_14423C();
    g = MG;
    p = g->runner;
    tb = lbl_3_data_21E68;
    i = 0;
    do {
        if (p->_18 < 0x7FFE) {
            p->_18 = p->_18 + 1;
        } else {
            p->_18 = 0x7FFF;
        }
        if (p->_1A < 0x7FFE) {
            p->_1A = p->_1A + 1;
        } else {
            p->_1A = 0x7FFF;
        }
        if (p->_1E != 0) {
            if (p->_1E < 0x7FFE) {
                p->_1E = p->_1E + 1;
            } else {
                p->_1E = 0x7FFF;
            }
        }
        if (p->st == 0) {
            ((void (*)(s32))fn_3_14402C)(i);
        } else if (p->st == 1) {
            p->_1C -= 1;
            v = &lbl_3_data_21D1C[p->sel * 2];
            p->pos.y = (v[1] - v[0]) * ((f32)p->_1A / (f32)tb[5]) + lbl_3_data_21D1C[p->sel * 2];
            if (p->_1C <= 0) {
                p->st = 2;
                p->_1A = 0;
            }
        } else if (p->st == 2) {
            if (g->_1CA2 == 2) {
                MgRunner* e = g->runner;
                for (k = 0; k < 3; k++) {
                    if (e->st == 2) {
                        e->st = 3;
                        e->_1A = 0;
                    }
                    e++;
                }
            }
            ((void (*)(s32))fn_3_1439EC)(i);
        } else if (p->st == 3) {
            v = &lbl_3_data_21D1C[p->sel * 2];
            p->pos.y = (v[0] - v[1]) * ((f32)p->_1A / (f32)tb[6]) + v[0];
            if (p->_1A >= tb[6]) {
                p->st = 0;
                p->_1A = 0;
                MG->kindUsed[p->who] = 0;
                if (g->bossActive != 0) {
                    g->bossActive = 0;
                }
            }
        } else if (p->st == 4) {
            if (p->_1C != 0) {
                p->_1C -= 1;
            }
            if (p->_1A >= tb[8]) {
                p->st = 0;
                p->_1A = 0;
            }
        }
        i++;
        p++;
    } while (i < 3);
}

// .text:0x0014471C size:0x3C0 mapped:0x807837B0
extern u8 lbl_3_data_21E1C[];

// Object positions / velocities (50 used).
#define MG_OBJ_POS(n) (&MG->objPos[n])
#define MG_OBJ_VEL(n) (&MG->objVel[n])

// Player p releases the object it is holding: place it at the hand and aim it at the fielder's target.
// NONMATCHING 93.2%: original addresses pos/vel through g_Minigame + obj*0xC with an extra pointer to pos.z; register shifts
#if NONMATCHING
void fn_3_14471C(s32 p) {
    InMemFielderType* f;
    s32 port;
    u8 obj;
    Vec* pos;
    u8* st;
    f32 len;
    f32 k;
    s32 n;
    f32 t;
    Vec d;

    port = MG->port[p];
    obj = MG->heldObj[p];
    f = &g_Fielders[MG->fielder[p]];
    if (f->charID == 0x26) {
        getAnimRelatedCoordinates(port, 9, &d);
    } else if (f->handedness == 0) {
        getAnimRelatedCoordinates(port, 0x19, &d);
    } else {
        getAnimRelatedCoordinates(port, 0x13, &d);
    }
    pos = MG_OBJ_POS(obj);
    pos->x = d.x;
    pos->y = -d.y;
    pos->z = d.z;
    d.x = f->throwTarget.x - pos->x;
    d.y = f->throwTarget.y - pos->y;
    d.z = f->throwTarget.z - pos->z;
    st = &MG->objState[obj];
    if (*st == 4) {
        if (MG->objKind[obj] != 5) {
            len = sqrt37A8(d.x * d.x + d.z * d.z);
            if (p == 0 || p == 3) {
                k = lbl_3_data_21E24[8] / len;
            } else {
                k = lbl_3_data_21E24[9] / len;
            }
            MG_OBJ_VEL(obj)->x = d.x * k;
            MG_OBJ_VEL(obj)->z = d.z * k;
            MG_OBJ_VEL(obj)->y = lbl_3_data_21E24[10];
        } else {
            n = lbl_3_data_21E68[23] + 10;
            MG_OBJ_VEL(obj)->x = d.x / (f32)n;
            MG_OBJ_VEL(obj)->z = (f->throwTarget.z - pos->z) / (f32)n;
            MG_OBJ_VEL(obj)->y = -lbl_3_data_21E24[11] * (f32)n * lbl_3_rodata_382C;
        }
        *st = 6;
    } else {
        t = LERPToNewRange_Float(f->throwingArm, 0, 100, lbl_3_data_21E1C[0], lbl_3_data_21E1C[1]);
        MG_OBJ_VEL(obj)->x = d.x / t;
        MG_OBJ_VEL(obj)->y = d.y / t;
        MG_OBJ_VEL(obj)->z = d.z / t;
        *st = 5;
    }
    MG->objTimer[obj] = 0;
    if (MG->objKind[obj] == 5) {
        fn_3_90064(0x308);
    }
}
#endif

// .text:0x00144ADC size:0x1DC mapped:0x80783B70
void fn_3_144ADC(s32 p) {
    InputStruct* in = &g_Controls[MG->port[p]];
    f32 d;
    InMemFielderType* f = &g_Fielders[MG->fielder[p]];

    if (MG->isCpu[p] != 0) {
        in = &MG->cpuIn.pad[MG->port[p]];
    }
    if (MG_H(jumpTimer)[p] < 0x7FFE) {
        MG_H(jumpTimer)[p]++;
    } else {
        MG_H(jumpTimer)[p] = 0x7FFF;
    }
    switch (MG->jump[p]) {
    case 1:
        d = lbl_3_data_21D2C[0] - lbl_3_data_21D2C[1];
        f->height = d * ((f32)MG_H(jumpTimer)[p] / (f32)lbl_3_data_21E68[16]) + lbl_3_data_21D2C[1];
        if (MG_H(jumpTimer)[p] >= lbl_3_data_21E68[16]) {
            MG->jump[p] = 2;
            MG_H(jumpTimer)[p] = 0;
        }
        break;
    case 2:
        if (!(in->buttonInput & 4)) {
            MG->jump[p] = 3;
            MG_H(jumpTimer)[p] = 0;
        }
        break;
    case 3:
        d = lbl_3_data_21D2C[1] - lbl_3_data_21D2C[0];
        f->height = d * ((f32)MG_H(jumpTimer)[p] / (f32)lbl_3_data_21E68[16]) + lbl_3_data_21D2C[0];
        if (MG_H(jumpTimer)[p] >= lbl_3_data_21E68[16]) {
            MG->jump[p] = 0;
            MG_H(jumpTimer)[p] = 0;
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
// NONMATCHING 81.4%: register allocation (more saved regs) and compare/branch shapes of the stick decode differ
#if NONMATCHING
void fn_3_144CB8(void) {
    s8 others[4];
    s32 i;
    InMemFielderType* f;
    InputStruct* pad;
    s32 o;
    s32 a;
    s32 b;
    u8 t;
    s8 v;
    s32 d;
    f32* tgt;
    s8* q;

    for (i = 0; i < 4; i++) {
        if (MG->fielder[i] < 0) {
            continue;
        }
        f = &g_Fielders[MG->fielder[i]];
        pad = &g_Controls[MG->port[i]];
        if (MG->isCpu[i] != 0) {
            pad = &MG->cpuIn.pad[MG->port[i]];
        }
        if (MG->jump[i] != 0) {
            fn_3_144ADC(i);
        } else if (MG->stun[i] == 1) {
            MG->stunTimer[i]--;
            if (MG->stunTimer[i] <= 0) {
                MG->stun[i] = 2;
                MG->stunTimer[i] = lbl_3_data_21E68[15];
            } else {
                f->pos.x = f->_038 * lbl_3_data_21E24[14] + f->pos.x;
                f->pos.y = f->pos.y + f->speed;
                f->pos.z = f->_03C * lbl_3_data_21E24[14] + f->pos.z;
                f->speed = f->speed - lbl_3_data_21E24[16];
            }
            fn_3_1573AC((u8*)lbl_8036E548.active[i]);
        } else if (MG->stun[i] == 2) {
            if (MG->turnOverStatus == 0) {
                MG->stunTimer[i]--;
                if (MG->stunTimer[i] <= 0) {
                    tgt = &lbl_3_data_21B94[MG->home[i]].x;
                    MG->stun[i] = 0;
                    MG->jump[i] = 2;
                    f->pos.x = tgt[0];
                    f->pos.y = tgt[1];
                    f->pos.z = tgt[2];
                    f->height = lbl_3_data_21D2C[0];
                }
            }
        } else if (MG->throwFrame[i] >= 0) {
            MG->throwFrame[i]++;
            a = LERPToNewRange_Float(MG->combo[i], 0, lbl_3_data_21E68[19], lbl_3_data_21E68[2], lbl_3_data_21E68[3]);
            if (MG->throwFrame[i] == lbl_3_data_21E68[4]) {
                fn_3_14471C(i);
                MG->held[i][0] = -1;
            } else if (MG->throwFrame[i] >= a) {
                MG->throwFrame[i] = -1;
                MG->aim[i] = -1;
            }
        } else if (pad->newButtonInput & 0x200) {
            if (MG->turnOverStatus != 0) {
                continue;
            }
            MG->aim[i] = 3;
            goto aim;
        } else if (pad->newButtonInput & 0x100) {
            if (MG->turnOverStatus != 0) {
                continue;
            }
            if (pad->controlStickAngle >= 0xE00 || (pad->buttonInput & 2)) {
                MG->aim[i] = 0;
            } else if (pad->controlStickAngle >= 0xA00) {
                continue;
            } else if (pad->controlStickAngle >= 0x600 || (pad->buttonInput & 1)) {
                MG->aim[i] = 2;
            } else if (pad->controlStickAngle >= 0x200 || (pad->buttonInput & 8)) {
                MG->aim[i] = 1;
            } else if (pad->controlStickAngle >= 0 || (pad->buttonInput & 2)) {
                MG->aim[i] = 0;
            } else {
                continue;
            }
        aim:
            o = MG->held[i][0];
            if (MG->objKind[o] != 5 || MG->aim[i] != 3) {
                MG->objTarget[o] = MG->aim[i];
                tgt = lbl_3_data_21BC4[MG->objTarget[o]];
                f->throwTarget.x = tgt[3];
                f->throwTarget.y = tgt[4];
                f->throwTarget.z = tgt[5];
            } else {
                // Aim at another player, weighted towards the leaders.
                q = others;
                if (i != 0) {
                    *q++ = 0;
                }
                if (i != 1) {
                    *q++ = 1;
                }
                if (i != 2) {
                    *q++ = 2;
                }
                if (i != 3) {
                    *q = 3;
                }
                for (a = 0; a < 2; a++) {
                    for (b = a + 1; b < 3; b++) {
                        if (MG->score[others[a]] < MG->score[others[b]]) {
                            t = others[a];
                            others[a] = others[b];
                            others[b] = t;
                        }
                    }
                }
                v = rand() % 100;
                if ((v -= lbl_3_data_21E20[0]) < 0) {
                    v = others[0];
                } else if ((v -= lbl_3_data_21E20[1]) < 0) {
                    v = others[1];
                } else if ((v -= lbl_3_data_21E20[2]) < 0) {
                    v = others[2];
                }
                d = v - i;
                MG->objTarget[o] = -1 - v;
                tgt = &lbl_3_data_21B94[v].x;
                f->throwTarget.x = lbl_3_rodata_3870 * (s8)(__abs(d) / d) + tgt[0];
                f->throwTarget.y = lbl_3_rodata_3834;
                f->throwTarget.z = tgt[2];
            }
            MG->heldObj[i] = MG->held[i][0];
            MG->objState[o] = 3;
            MG->throwFrame[i] = 0;
            if (MG->aim[i] == 3) {
                MG->objState[o] = 4;
            }
            f->facing = game_atan2(f->throwTarget.x - f->pos.x, f->throwTarget.z - f->pos.z);
        } else if (pad->buttonInput & 4) {
            MG->jump[i] = 1;
            MG->jumpTimer[i] = 0;
            fn_3_90064(0x2DB);
        }
    }
}
#endif

// .text:0x001453BC size:0x714 mapped:0x80784450
extern void fn_3_147CFC(void* arg);
extern void fn_3_154238(s16 id);
extern void fn_3_1608F0(s32 kind, s32 value, s32 extra);
extern void fn_80062BE4(Vec* pos);
extern void* memcpy(void*, const void*, u32);
extern u8 lbl_3_data_21E18[][2];
extern Rep37A8Bss37400View lbl_3_common_bss_37400;
extern const f32 lbl_3_rodata_3878;

// Flight of a thrown object (idx): bombs (kind 5) blow up at their target player, others can hit a runner.
// NONMATCHING 87.5%: register allocation; structure and calls match
#if NONMATCHING
void fn_3_1453BC(s32 idx) {
    s16* timer;
    s8* thrower;
    s8 by;
    u8* st;
    Vec* pos;
    Vec* vel;
    s8 vic;
    InMemFielderType* f;
    Vec dir;
    s8 tgt;
    f32* t;
    f32 d;
    MgRunner* r;
    u8* kind;
    s8 dmg;
    s16 hp;
    s32 k;
    Vec c;

    timer = &MG->objTimer[idx];
    thrower = &MG->objOwner[idx];
    by = *thrower;
    if (*timer < 0x7FFE) {
        (*timer)++;
    } else {
        *timer = 0x7FFF;
    }
    st = &MG->objState[idx];
    if (*st == 6) {
        vel = &MG->objVel[idx];
        vel->y = vel->y + lbl_3_data_21E24[11];
        if (MG->objKind[idx] != 5) {
            vel->x = vel->x * lbl_3_data_21E24[12];
            vel->z = vel->z * lbl_3_data_21E24[12];
        } else if (*timer >= lbl_3_data_21E68[23]) {
            vic = -1 - MG->objTarget[idx];
            fn_3_147CFC(&MG->objPos[idx]);
            fn_3_90064(0x309);
            fn_3_154238(idx);
            if (MG->jump[vic] == 0 && MG->stun[vic] == 0) {
                MG->stun[vic] = 1;
                MG->stunTimer[vic] = lbl_3_data_21E68[14];
                MG->combo[vic] = 0;
                f = &g_Fielders[MG->fielder[vic]];
                dir.x = lbl_3_rodata_3834;
                dir.y = lbl_3_rodata_3834;
                dir.z = lbl_3_rodata_3878;
                PSVECNormalize(&dir, &dir);
                f->_038 = dir.x;
                MG->knocked[vic] = 1;
                f->_03C = dir.z;
                f->speed = lbl_3_data_21E24[15];
                fn_3_6C854(MG->port[vic], 2);
                if (MG->hits[vic] < 0xFFFE) {
                    MG->hits[vic]++;
                } else {
                    MG->hits[vic] = 0xFF;
                }
            }
            *st = 0;
            *timer = 0;
            return;
        }
    }
    pos = &MG->objPos[idx];
    vel = &MG->objVel[idx];
    pos->x = pos->x + vel->x;
    pos->y = pos->y + vel->y;
    pos->z = pos->z + vel->z;
    if (pos->y < lbl_3_rodata_3834) {
        *st = 0;
        *timer = 0;
        if (MG->objKind[idx] == 5) {
            fn_3_154238(idx);
        }
        return;
    }
    tgt = MG->objTarget[idx];
    if (tgt >= 0) {
        t = lbl_3_data_21BC4[tgt];
        d = sqrt37A8((pos->x - t[3]) * (pos->x - t[3]) + (pos->z - t[5]) * (pos->z - t[5]));
        r = &MG->runner[tgt];
        if (r->st == 2 && d < lbl_3_data_21E24[1]) {
            kind = &MG->objKind[idx];
            if (*kind == r->who || r->who == 4 || *kind == 5) {
                if (*kind == 5) {
                    dmg = lbl_3_data_21E68[24];
                } else {
                    dmg = 1;
                }
                memcpy(&c, pos, sizeof(Vec));
                c.y *= lbl_3_rodata_3878;
                if (*kind == 5) {
                    fn_3_147CFC(&c);
                    fn_3_154238(idx);
                } else {
                    fn_80062BE4(&c);
                }
                if (*kind == 5) {
                    fn_3_90064(0x309);
                } else {
                    fn_3_90064(0x2DC);
                }
                hp = r->_2D - dmg;
                if (hp <= 0) {
                    r->_2D = 0;
                } else {
                    r->_2D = hp;
                }
                MG->combo[by]++;
                MG->hitLog[by][MG->hitLogCount[by]] = dmg * lbl_3_data_21E18[r->sel][1];
                MG->hitLogCount[by]++;
                r->queue[0] = -1;
                r->queue[1] = -1;
                r->queue[2] = -1;
                r->queue[3] = -1;
                r->_2E = 0;
                if (r->_2D == 0) {
                    MG->hitLog[by][MG->hitLogCount[by]] = lbl_3_data_21E18[r->sel][0];
                    MG->hitLogCount[by]++;
                    if (r->who == 4) {
                        MG->bossActive = 0;
                        r->_2E = 0;
                    } else if (MG->_1CA2 != 0) {
                        MG->_1CA2 = 2;
                    }
                    r->_1C = lbl_3_data_21E68[8] - lbl_3_data_21E68[9];
                    r->_1A = 0;
                    r->st = 4;
                    MG->kindUsed[r->who] = 0;
                    if (g_d_GameSettings.exhibitionMatchInd == 0 && by == lbl_3_common_bss_37400.humanPlayer) {
                        fn_3_1608F0(5, r->who, 0);
                    }
                }
                r->_1E = 1;
            } else if ((r->_33 == 3 && r->_2E == 0) || r->_33 == 0) {
                if (r->_2E == 0) {
                    r->queueTimer = 0;
                }
                for (k = 0; k < 4; k++) {
                    if (r->queue[k] < 0) {
                        r->queue[k] = *thrower;
                        r->_2E = 1;
                        r->throwTimer = 0;
                        break;
                    }
                }
                MG->combo[by] = 0;
            }
            *st = 0;
            *timer = 0;
            return;
        }
    }
    if (*timer > lbl_3_data_21E68[0]) {
        *st = 0;
        *timer = 0;
        if (MG->objKind[idx] == 5) {
            fn_3_154238(idx);
        }
    }
}
#endif

// .text:0x00145AD0 size:0xC8 mapped:0x80784B64
// 97%: volatile regs allocated differently (k r7 vs r8); this form matches the inlined copy in fn_3_145EB8
// (the held[] / objPos[] element pointers must be formed as byte offsets from the shifted base).
void fn_3_145AD0(s32 p) {
    s8 t;
    s32 k;
    s8* m;
    u8* g;

    k = 0;
    t = MG->objOwner[p];
    m = (s8*)g_Minigame + t * 3;
    for (; k < 3; k++, m++) {
        if (m[(s32)OFFSET_OF(Mg37A8, held)] == p) {
            break;
        }
    }
    g = g_Minigame + p * 0xC;
    ((Vec*)(g + (s32)OFFSET_OF(Mg37A8, objPos)))->x = lbl_3_data_21D34[MG_B(home, t)][k].x;
    ((Vec*)(g + (s32)OFFSET_OF(Mg37A8, objPos)))->y = lbl_3_data_21D34[MG_B(home, t)][k].y;
    ((Vec*)(g + (s32)OFFSET_OF(Mg37A8, objPos)))->z = lbl_3_data_21D34[MG_B(home, t)][k].z;
}

// .text:0x00145B98 size:0x320 mapped:0x80784C2C
// Refill each active player's queue of 3 held objects (g_Minigame + 0x1C7E + p * 3) from free object slots.
// NONMATCHING 83.5%: original frame is 0x10 bigger and keeps queue pointers in other registers
#if NONMATCHING
void fn_3_145B98(void) {
    s32 list[4];
    u8 p;
    s32 s;
    s32 j;
    s32 n;
    s32 k;
    s32* lp;

    if (MG->turnOverStatus != 0) {
        return;
    }
    p = 0;
    do {
        if (MG->port[p] >= 0) {
            if (MG->held[p][2] < 0) {
                s = 0;
                do {
                    for (j = 0; j < 50; j++) {
                        if (MG->objState[j] == 0) {
                            MG->held[p][s] = j;
                            MG->objOwner[j] = p;
                            MG->objState[j] = 2;
                            MG->objTimer[j] = 0;
                            MG->objKind[j] = RandomInt_Game(4);
                            MG->_1C1A[j] = 0;
                            MG->_1C4C[j] = 0;
                            MG->thrown[p]++;
                            fn_3_145AD0(j);
                            break;
                        }
                    }
                    s++;
                } while (s < 3);
            } else if (MG->held[p][0] < 0) {
                MG->held[p][0] = MG->held[p][1];
                MG->held[p][1] = MG->held[p][2];
                for (j = 0; j < 50; j++) {
                    if (MG->objState[j] == 0) {
                        MG->held[p][2] = j;
                        MG->objOwner[j] = p;
                        MG->objState[j] = 2;
                        MG->objTimer[j] = 0;
                        MG->_1C1A[j] = 0;
                        MG->_1C4C[j] = 0;
                        MG->thrown[p]++;
                        if (MG->thrown[p] <= lbl_3_data_21E68[1]) {
                            lp = list;
                            n = 0;
                            for (k = 0; k < 4; k++) {
                                if (MG->kindUsed[k] == 1) {
                                    *lp++ = k;
                                    n++;
                                }
                            }
                            if (n == 0) {
                                MG->objKind[j] = RandomInt_Game(4);
                            } else {
                                MG->objKind[j] = list[RandomInt_Game(n)];
                            }
                        } else {
                            MG->objKind[j] = 5;
                            MG->thrown[p] = 0;
                        }
                        break;
                    }
                }
            }
        }
        p++;
    } while (p < 4);
}
#endif

// .text:0x00145EB8 size:0x13C mapped:0x80784F4C
void fn_3_145EB8(void) {
    s32 i;
    u8 v;

    ((void (*)(void))fn_3_145B98)();
    for (i = 0; i < 50; i++) {
        v = MG->objState[i];
        if (v == 5 || v == 6) {
            fn_3_1453BC(i);
        } else if (v == 2) {
            fn_3_145AD0(i);
        }
    }
}

// .text:0x00145FF4 size:0x1B0 mapped:0x80785088
void fn_3_145FF4(void) {
    u32 i;
    fn_3_157570();
    fn_3_DE4FC();
    if (MG->difficulty <= 2 && MG->multiPlayerInd == 0) {
        if (MG->_18E8[MG->_1908] == 1 && MG->_19A8 == 0) {
            MG->_1A37 = 1;
        } else {
            MG->_1A37 = 2;
        }
    }
    fn_3_5A6D4(0xE);
    for (i = 0; i < 50; i++) {
        MG->objState[i] = 0;
        MG->objOwner[i] = -1;
    }
    MG->_1B4C = 0x3C;
    for (i = 0; i < 3; i++) {
        ((void (*)(s32))fn_3_14402C)(i);
        MG->runner[i].st = 2;
        MG->runner[i]._1C = 1;
        MG->runner[i].sel = 0;
    }
    fn_3_154214();
}

// .text:0x001461A4 size:0x264 mapped:0x80785238
void fn_3_1461A4(void) {
    if (MG->turnOverStatus == 0) {
        if (MG->timeLeft == 0) {
            MG->turnOverStatus = 1;
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        return;
    }
    if (MG->turnOverStatus == 1) {
        MG->turnOverStatus = 2;
        g_GameLogic.CountdownUntilFade = lbl_3_data_21E68[17];
    }
    if (--g_GameLogic.CountdownUntilFade == 7) {
        changeScene(3, 6);
    }
    if (g_GameLogic.CountdownUntilFade <= 0) {
        fn_3_145FF4();
    }
}

// .text:0x00146408 size:0x520 mapped:0x8078549C
extern s32 fn_3_108854(void);
extern u16 lbl_3_data_81FC[];

// Per-frame update of the minigame.
// NONMATCHING 98.2%: inlined fn_3_142CA8 reloads g_Minigame instead of reusing r26 from the inlined fn_3_145EB8 loop
#if NONMATCHING
void fn_3_146408(void) {
    if (fn_3_108854() != 0) {
        return;
    }
    if (MG->turnOverStatus == 0) {
        MG->frame++;
    }
    if (MG->timeLeft != 0) {
        MG->timeLeft--;
        if (MG->timeLeft < 600 && MG->timeLeft != 0 && MG->timeLeft % 60 == 0) {
            fn_3_90064(lbl_3_data_81FC[0x28]);
        }
    }
    fn_3_145EB8();
    fn_3_14443C();
    fn_3_143714();
    fn_3_142284();
    fn_3_144CB8();
    fn_3_142CA8();
    fn_3_1461A4();
}
#endif

// .text:0x00146928 size:0xA4 mapped:0x807859BC
void fn_3_146928(void) {
    fn_3_142C18();
    changeScene(1, 6);
    fn_3_5A6D4(2);
}

// .text:0x001469CC size:0xC4 mapped:0x80785A60
void fn_3_1469CC(void) {
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

// .text:0x00146A90 size:0x730 mapped:0x80785B24
extern void fn_3_59A90(void);
extern void fn_3_591AC(void);
extern void fn_3_58870(void);
extern void fn_3_6E24C(int rosterID, int fielderIdx);
extern void fn_3_157588(int);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern GameScores g_Scores;
extern u8 lbl_3_data_2127C[][5];
extern u8 lbl_3_data_21E08[];
extern const f32 lbl_3_rodata_387C;

// Minigame init (first call), then the texture for the TEV hook.
// NONMATCHING 93.1%: store scheduling / register choice in the reset loops
#if NONMATCHING
void fn_3_146A90(void) {
    s32 i;
    s32 n;
    s32 j;
    u8 v;
    InMemFielderType* f;
    MgRunner* r;

    if (g_GameLogic._125 == 0) {
        fn_3_59A90();
        MG->frame = 0;
        MG->turnOverStatus = 0;
        g_GameLogic.secondaryGameMode = 7;
        MG->_1A37 = 0;
        for (i = 0; i < 4; i++) {
            MG->score[i] = 0;
            MG->lastScore[i] = 0;
            MG->points[i][0] = 0;
            MG->points[i][1] = 0;
            MG->order[i] = -1;
            MG->fielder[i] = -1;
            MG->_18FC[i] = -1;
            MG->_1900[i] = -1;
            MG->_18F0[i] = 0;
        }
        g_Scores.inning = 0;
        MG->_1A26 = 0;
        MG->_190C = 0;
        MG->_1904 = -1;
        MG->_1905 = -1;
        MG->frame = 0;
        if (MG->multiPlayerInd == 0) {
            v = lbl_3_data_2127C[MG->gameMode][MG->difficulty];
            MG->timeLeft = lbl_3_data_21E08[MG->difficulty] * 60;
            MG->cpuLevel[0] = v;
            MG->cpuLevel[1] = v;
            MG->cpuLevel[2] = v;
            MG->cpuLevel[3] = v;
        } else {
            if (MG->_1A3C != 0) {
                MG->cpuLevel[0] = lbl_3_data_2127C[7][0];
                MG->cpuLevel[1] = lbl_3_data_2127C[7][0];
                MG->cpuLevel[2] = lbl_3_data_2127C[7][0];
                MG->cpuLevel[3] = lbl_3_data_2127C[7][0];
            }
            MG->timeLeft = lbl_3_data_21E08[4] * 60;
        }
        fn_3_591AC();
        fn_3_58870();
        n = 0;
        for (i = 0; i < 4; i++) {
            if (MG->port[i] < 0) {
                continue;
            }
            MG->order[n] = i;
            MG->fielder[MG->order[n]] = n + 2;
            fn_3_6E24C(i, MG->fielder[MG->order[n]]);
            f = &g_Fielders[MG->fielder[MG->order[n]]];
            MG->held[i][0] = -1;
            MG->held[i][1] = -1;
            MG->held[i][2] = -1;
            MG->thrown[i] = 0;
            f->minigamePlayer = i;
            f->pos.x = lbl_3_data_21B94[n].x;
            MG->throwFrame[i] = -1;
            MG->aim[i] = -1;
            f->pos.y = lbl_3_data_21B94[n].y;
            MG->stun[i] = 0;
            f->pos.z = lbl_3_data_21B94[n].z;
            MG->combo[i] = 0;
            f->height = lbl_3_data_21D2C[1];
            MG->hitLogCount[i] = 0;
            f->_1D2 = 0;
            MG->jump[i] = 0;
            f->speed = lbl_3_rodata_3834;
            MG->home[i] = i;
            f->facing = lbl_3_rodata_387C;
            MG->hits[i] = 0;
            for (j = 0; j < 10; j++) {
                MG->hitLog[i][j] = 0;
            }
            MG->targeted[i] = 0;
            n++;
        }
        for (j = 0; j < 100; j++) {
            MG->objState[j] = 0;
            // the original clears 100 bytes from objOwner, running on into objTarget
            if (j < 50) {
                MG->objOwner[j] = -1;
            } else {
                MG->objTarget[j - 50] = -1;
            }
        }
        MG->_1B4C = 0x3C;
        fn_3_145B98();
        r = MG->runner;
        for (i = 0; i < 3; i++, r++) {
            r->st = 0;
            r->sel = 0;
            r->_2E = 0;
            r->_1A = 0;
            r->_1C = -1;
            r->_1E = 0;
            r->throwTimer = 0;
            r->_22 = 0;
            r->_33 = 0xFF;
            r->pos.x = lbl_3_data_21BC4[i][0];
            r->pos.y = lbl_3_data_21BC4[i][1];
            r->pos.z = lbl_3_data_21BC4[i][2];
            r->queue[0] = -1;
            r->queue[1] = -1;
            r->queue[2] = -1;
            r->queue[3] = -1;
        }
        MG->kindUsed[0] = 0;
        MG->kindUsed[1] = 0;
        MG->kindUsed[2] = 0;
        MG->kindUsed[3] = 0;
        MG->_1CA2 = 0;
        MG->bossActive = 0;
        MG->bossCount = 0;
        if (MG->multiPlayerInd == 0) {
            MG->_1B4E = RandomInt_Game_Range(lbl_3_data_21DC8[MG->difficulty][0].lo, lbl_3_data_21DC8[MG->difficulty][0].hi) * 60;
        } else {
            MG->_1B4E = RandomInt_Game_Range(lbl_3_data_21DC8[4][0].lo, lbl_3_data_21DC8[4][0].hi) * 60;
        }
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        for (j = 0; j < 40; j++) {
            MG->ball[j].used = 0;
        }
        fn_3_157588(0x28);
        g_GameLogic._125++;
    } else {
        fn_3_5A6D4(5);
    }
    fn_3_142088();
}
#endif
