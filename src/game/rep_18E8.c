#include "game/rep_18E8.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/rep_1838.h"
#include "game/rep_AC8.h"
#include "game/rep_D0.h"
#include "game/auto_00_0005985C_text.h"
#include "main/file_8004207C.h"
#include "header_rep_data.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"

#pragma dont_inline on
extern int __float_nan[];
#define NAN (*(f32*)__float_nan)
f64 __frsqrte(f64);
extern u8 lbl_3_data_4744[];
extern u8 lbl_3_data_475C;
extern u8 lbl_3_data_49DC[];
extern const f64 lbl_3_rodata_1940;
extern const f64 lbl_3_rodata_1948;
extern const f64 lbl_3_rodata_1950;
extern const f32 lbl_3_rodata_195C;
extern const f32 lbl_3_rodata_1958;
extern const f32 lbl_3_rodata_1970;
extern const f32 lbl_3_rodata_1974;
extern const f32 lbl_3_rodata_19EC;
extern const f32 lbl_3_rodata_1A08;
extern const f32 lbl_3_rodata_1A2C;
extern const f32 lbl_3_rodata_1A30;
extern const f32 lbl_3_rodata_1A34;
#define SQRT_L(x)                                                                                  \
    do {                                                                                           \
        if ((x) > lbl_3_rodata_193C) {                                                             \
            f64 xd = (f64)(x);                                                                     \
            f64 guess = __frsqrte(xd);                                                             \
            guess = lbl_3_rodata_1940 * guess * (lbl_3_rodata_1948 - guess * guess * xd);          \
            guess = lbl_3_rodata_1940 * guess * (lbl_3_rodata_1948 - guess * guess * xd);          \
            guess = lbl_3_rodata_1940 * guess * (lbl_3_rodata_1948 - guess * guess * xd);          \
            (x) = (f32)(xd * guess);                                                               \
        } else if ((x) < lbl_3_rodata_1950) {                                                      \
            (x) = NAN;                                                                             \
        } else if (isnan(x)) {                                                                     \
            (x) = NAN;                                                                             \
        }                                                                                          \
    } while (0)

extern f32 lbl_3_data_4444[]; // base coordinates, (x, z) per base
typedef struct { s16 a; s16 b; s16 c; } Tbl6;
typedef struct { u8 pad0[2]; u8 b; u8 c; } Tbl4;
extern Tbl6 lbl_3_data_4860[];
extern f32 lbl_3_data_4878[];
extern s16 lbl_3_data_4880;
extern Tbl4 lbl_3_data_7E34[];
extern u8 lbl_3_data_4900[];
extern u8 lbl_3_data_1C38[2];
extern s16 lbl_3_data_1C40; // AI chance range (min, max)
extern f32 lbl_3_rodata_196C;
extern f32 lbl_3_rodata_1980;
extern f32 lbl_3_rodata_1984;
extern f32 lbl_3_rodata_1988;
extern f32 lbl_3_rodata_1990;
extern const f32 lbl_3_rodata_199C;
extern const f32 lbl_3_rodata_19E0;
extern const f32 lbl_3_rodata_19E4;
extern f32 lbl_3_rodata_19E8;
extern f32 lbl_3_rodata_19A0;
extern f32 lbl_3_rodata_19AC;
extern f32 lbl_3_rodata_19B4;
extern f32 lbl_3_rodata_19BC;
extern f32 lbl_3_rodata_1A0C;
extern f32 lbl_3_rodata_1A10;
extern f32 lbl_3_rodata_198C;
extern f32 lbl_3_rodata_19F0;
extern f32 lbl_3_rodata_1994;
extern f32 lbl_3_rodata_1998;
extern f32 lbl_3_rodata_19B8;
extern f32 lbl_3_rodata_1978;
extern f32 lbl_3_rodata_193C;
static s32 lbl_3_bss_1858[42];
static s32 lbl_3_bss_1848[4]; // per runner: frame margin
static s32 lbl_3_bss_1838[4]; // per runner: base to cover
static s32 lbl_3_bss_1828[4];
static u32 lbl_3_bss_1824;
static s32 lbl_3_bss_1820;
static s32 lbl_3_bss_181C;
static s32 lbl_3_bss_1818;
static s32 lbl_3_bss_1808[4];
static u32 lbl_3_bss_1804;
static u32 lbl_3_bss_1800;
static u8 lbl_3_bss_17FC[4];
static s32 lbl_3_bss_17F8;
extern f32 lbl_3_rodata_19B0;
extern const f32 lbl_3_rodata_1938;
extern const f32 lbl_3_rodata_197C;
extern const f32 lbl_3_rodata_19F4;
extern const f32 lbl_3_rodata_19F8;
extern const f32 lbl_3_rodata_19FC;
extern const f32 lbl_3_rodata_1A00;
extern const f32 lbl_3_rodata_1A04;
extern const f32 lbl_3_rodata_1960;
extern const f32 lbl_3_rodata_1964;
extern const f32 lbl_3_rodata_1968;
extern const f32 lbl_3_rodata_1A38;
extern const f32 lbl_3_rodata_1A40;

// Frames for the fielder holding the ball to reach (x, z). Same body as fn_3_A6ABC, which the
// original inlines into several callers in this file.
#pragma dont_inline off
static inline s32 ballFielderFramesTo(f32 x, f32 z) {
    RepFielder* f;
    f32 dz;
    f32 dx;
    f32 d;
    f32 step;
    f32 a;
    f32 b;
    s32 n;

    f = &g_Fielders[g_Ball.fielderWBallIndex];
    dx = x - f->pos.x;
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    dz = z - f->pos.z;
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (lbl_3_rodata_193C == step) {
        step = lbl_3_rodata_1958;
    }
    if (d > lbl_3_rodata_195C) {
        n = (s32)(lbl_3_rodata_1960 * d / step);
    } else if (d > lbl_3_rodata_1964) {
        n = (s32)(d / step);
    } else {
        n = (s32)(lbl_3_rodata_1968 * d / step);
    }
    if (d > lbl_3_rodata_196C) {
        n = (s32)((f32)n * lbl_3_rodata_1970) + 0x1E;
    } else if (d > lbl_3_rodata_1974) {
        n = (s32)((f32)n * lbl_3_rodata_1960) + 0x1E;
    }
    return n;
}
#pragma dont_inline on

// .text:0x000A009C size:0x1C68 mapped:0x806DF130
void fn_3_A009C(void) {
    return;
}

// .text:0x000A1D04 size:0x9C mapped:0x806E0D98
s32 fn_3_A1D04(void) {
    f32 prev = lbl_3_rodata_1978;
    s32 prevIdx;
    InMemRunnerType* r = &g_Runners[3];
    s32 i;
    for (i = 3; i >= 0; r--, i--) {
        if (r->runnerOnFieldOrOutOrScored == 1) {
            f32 cur = r->fractionalBasesRan;
            f32 d = cur - prev;
            if (d < lbl_3_rodata_193C) {
                d = -d;
            }
            if (d < 0.35f) {
                if (g_Runners[prevIdx].baseStandingOn < 0) {
                    return prevIdx;
                }
                return i;
            }
            prev = cur;
            prevIdx = i;
        }
    }
    return -1;
}

// .text:0x000A1DA0 size:0x19C mapped:0x806E0E34
int fn_3_A1DA0(void) {
    RepFielder* f = &g_Fielders[g_Ball.fielderWBallIndex];
    if (f->_070 > -(lbl_3_rodata_1980 * (f32)(100 - f->_1CE) - lbl_3_rodata_196C)) {
        return 0;
    }
    if (!(g_Runners[3].runnerOnFieldOrOutOrScored == 1 && g_Runners[3].fractionalBasesRan < lbl_3_rodata_1984 &&
          (g_Runners[3].runningDirectionCode == 2 || g_Runners[3].runningDirectionCode == 1))) {
        if (!(g_Runners[2].runnerOnFieldOrOutOrScored == 1 && g_Runners[2].fractionalBasesRan > lbl_3_rodata_1988 &&
              g_Runners[2].fractionalBasesRan <= lbl_3_rodata_1984 && g_Runners[3].runningDirectionCode == 1 &&
              g_Runners[2].tagUpInd == 0)) {
            return 0;
        }
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored == 1) {
        if (g_Runners[1].tagUpInd != 0) {
            if (g_Runners[1].fractionalBasesRan > lbl_3_rodata_198C) {
                return 0;
            }
        } else if (g_Runners[1].forceOutCd == 1 && g_Runners[1].fractionalBasesRan <= lbl_3_rodata_1990) {
            return 0;
        }
    }
    g_FieldingLogic._0C4 = 0;
    g_FieldingLogic._0CC = -1;
    g_FieldingLogic._0DE = -1;
    return 1;
}

// .text:0x000A1F3C size:0x10C mapped:0x806E0FD0
int fn_3_A1F3C(void) {
    s32 idx;
    s32 i;
    if (g_Ball.ballZoneAwayFromHome >= 3) {
        return 0;
    }
    idx = lbl_3_bss_1808[3];
    if (idx < 0 || idx > 3) {
        return 0;
    }
    if (lbl_3_bss_1858[idx] >= 7) {
        return 0;
    }
    if (g_Runners[idx].tagUpInd != 0) {
        return 0;
    }
    if (idx >= 1) {
        for (i = idx - 1; i >= 0; i--) {
            f32 p = g_Runners[i].percentTowardsNextBase;
            if (p > 0.15f && p < 0.85f) {
                return 0;
            }
        }
    }
    if (fn_3_A46A0(idx)) {
        return 1;
    }
    return 0;
}

// .text:0x000A2048 size:0x1E4 mapped:0x806E10DC
#pragma opt_loop_invariants off
int fn_3_A2048(void) {
    s32 i;
    s32 m = 0;
    s16 ball;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored == 1) {
            f32 f = r->fractionalBasesRan;
            if (f < lbl_3_rodata_19E0) {
                m |= 0x10;
            } else if (f < lbl_3_rodata_19E4) {
                m |= 0x100;
            } else if (f <= lbl_3_rodata_199C) {
                m |= 0x1000;
            }
        }
    }
    ball = g_Ball.ballAngleFromHome;
    if (ball > 0x500) {
        if (m & 0x1000) {
            ((void (*)(int))fn_3_A41E8)(3);
            return 1;
        } else if (m & 0x100) {
            ((void (*)(int))fn_3_A41E8)(3);
            return 1;
        } else if (m & 0x10) {
            ((void (*)(int))fn_3_A41E8)(2);
            return 1;
        }
        return 0;
    } else if (ball > 0x400) {
        if (m & 0x1000) {
            ((void (*)(int))fn_3_A41E8)(3);
            return 1;
        } else if ((m & 0x100) && !(m & 0x1000)) {
            ((void (*)(int))fn_3_A41E8)(2);
            return 1;
        }
        return 0;
    } else {
        if (m & 0x1000) {
            if (!(m & 0x10) || (m & 0x100)) {
                ((void (*)(int))fn_3_A41E8)(0);
                return 1;
            }
        } else if (m & 0x100) {
            ((void (*)(int))fn_3_A41E8)(3);
            return 1;
        }
        return 0;
    }
}
#pragma opt_loop_invariants reset

// .text:0x000A222C size:0x1D8 mapped:0x806E12C0
int fn_3_A222C(void) {
    s32 order[3];
    s32 i;
    if (g_Ball.AtBat_ContactResult != 3) {
        return 0;
    }
    if (lbl_3_bss_1820 == 0) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[1] < g_Ball.ballDistanceFromBase[3]) {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 2;
            order[1] = 3;
            order[2] = 1;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 3;
            order[1] = 2;
            order[2] = 1;
        } else {
            order[0] = 3;
            order[1] = 1;
            order[2] = 2;
        }
    }
    for (i = 0; i < 3; i++) {
        s32 idx = order[i];
        if (g_Runners[idx].runnerOnFieldOrOutOrScored == 1 && g_Runners[idx].tagUpInd == 2 && lbl_3_bss_1858[idx] <= 4 && g_Ball.ballDistanceFromBase[idx] < lbl_3_rodata_19E8) {
            if (fn_3_A46A0(idx)) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x000A2404 size:0x1C0 mapped:0x806E1498
int fn_3_A2404(void) {
    s32 order[3];
    s32 i;
    if (g_Ball.AtBat_ContactResult != 3) {
        return 0;
    }
    if (lbl_3_bss_1820 == 0) {
        return 0;
    }
    if (g_Ball.ballDistanceFromBase[1] < g_Ball.ballDistanceFromBase[3]) {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else {
        if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[3]) {
            order[0] = 2;
            order[1] = 3;
            order[2] = 1;
        } else if (g_Ball.ballDistanceFromBase[2] < g_Ball.ballDistanceFromBase[1]) {
            order[0] = 3;
            order[1] = 2;
            order[2] = 1;
        } else {
            order[0] = 3;
            order[1] = 1;
            order[2] = 2;
        }
    }
    for (i = 0; i < 3; i++) {
        s32 idx = order[i];
        if (g_Runners[idx].runnerOnFieldOrOutOrScored == 1 && g_Runners[idx].tagUpInd == 2 && lbl_3_bss_1858[idx] <= 4) {
            if (fn_3_A46A0(idx)) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x000A25C4 size:0x398 mapped:0x806E1658
int fn_3_A25C4(void) {
    s32 idx;
    s32 base;
    s32 cut;

    idx = lbl_3_bss_1808[3];
    if (idx >= 0 && lbl_3_bss_1858[idx] <= 5) {
        if ((g_Runners[idx].percentTowardsNextBase > 0.2f ||
             (g_Runners[idx].baseStandingOn == -1 && g_Ball.baseBallAndFielderAreOn == 3)) &&
            fn_3_A46A0(idx)) {
            base = 3;
            goto found;
        }
        if (lbl_3_bss_1800 & 0x1000) {
            idx = lbl_3_bss_1808[3];
            if (g_Runners[idx].percentTowardsNextBase > 0.15f && fn_3_A46A0(idx)) {
                base = 3;
                goto found;
            }
        }
    }
    idx = lbl_3_bss_1808[2];
    if (idx >= 0 && lbl_3_bss_1858[idx] <= 5) {
        if ((g_Runners[idx].percentTowardsNextBase > 0.2f ||
             (g_Runners[idx].baseStandingOn == -1 && g_Ball.baseBallAndFielderAreOn == 2)) &&
            fn_3_A46A0(idx)) {
            base = 2;
            goto found;
        }
        if (lbl_3_bss_1800 & 0x100) {
            idx = lbl_3_bss_1808[2];
            if (g_Runners[idx].percentTowardsNextBase >= 0.15f && fn_3_A46A0(idx)) {
                base = 2;
                goto found;
            }
        }
    }
    idx = lbl_3_bss_1808[1];
    if (idx >= 0 && lbl_3_bss_1858[idx] <= 5) {
        if ((g_Runners[idx].percentTowardsNextBase > 0.2f ||
             (g_Runners[idx].baseStandingOn == -1 && g_Ball.baseBallAndFielderAreOn == 1)) &&
            fn_3_A46A0(idx)) {
            base = 1;
            goto found;
        }
        if (lbl_3_bss_1800 & 0x10) {
            idx = lbl_3_bss_1808[1];
            if (g_Runners[idx].percentTowardsNextBase > 0.15f && fn_3_A46A0(idx)) {
                base = 1;
                goto found;
            }
        }
    }
    return 0;
found:
    if (g_Ball.ballDistanceFromBase[0] < 3.0f && g_FieldingLogic._0C4 == 2 && lbl_3_bss_1808[3] >= 0 && base == 1 &&
        g_Runners[lbl_3_bss_1808[base]].fractionalBasesRan <= 1.2f) {
        // inlined fn_3_AABF8
        if (g_FieldingLogic._0D8 == -1) {
            cut = 0;
        } else if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
            cut = 0;
        } else if (g_Fielders[g_FieldingLogic._0D8].coveringBase != 5) {
            cut = 0;
        } else if (g_Fielders[g_Ball.fielderWBallIndex]._0B8 < lbl_3_rodata_19F0) {
            cut = 0;
        } else {
            cut = 1;
        }
        if (cut) {
            g_FieldingLogic._0CC = -1;
            g_FieldingLogic._0C4 = 5;
        }
    }
    return 1;
}

// .text:0x000A295C size:0x210 mapped:0x806E19F0
// 98.4%: only scheduling differs (lfs of rodata_19A0 comes after lwz sel[2], original before stw r29)
int fn_3_A295C(void) {
    f32 c = lbl_3_rodata_19A0;
    InMemRunnerType* r = &g_Runners[lbl_3_bss_1808[2]];
    s32 t;
    if (r->percentTowardsNextBase > c && lbl_3_bss_1858[lbl_3_bss_1808[2]] < 3 && g_Ball.ballZoneAwayFromHome <= 1 && r->percentTowardsNextBase <= lbl_3_rodata_19AC && (!(r->percentTowardsNextBase >= lbl_3_rodata_19AC) || r->runningDirectionCode != 1) && (lbl_3_bss_1824 & 1) && g_Ball.ballAngleFromHome > 0x1C0 && g_Ball.ballAngleFromHome < 0x300 && r->percentTowardsNextBase <= lbl_3_rodata_19B4 && lbl_3_bss_1858[lbl_3_bss_1808[0]] <= 3 && fn_3_A46A0(lbl_3_bss_1808[0])) {
        return 1;
    }
    if (g_Ball.ballAngleFromHome >= 0x380 && g_Ball.ballAngleFromHome < 0x640 && g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.AtBat_Contact_BallPos.z > lbl_3_rodata_19B8 + g_Ball.AtBat_Contact_BallPos.x) {
        t = 1;
    } else {
        t = 0;
    }
    if (t) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 4 && g_Strikes.outs == g_Strikes.storedOuts && r->percentTowardsNextBase > lbl_3_rodata_19A0 && fn_3_A46A0(lbl_3_bss_1808[2])) {
            return 1;
        }
    }
    if ((lbl_3_bss_1800 & 0x10) && r->percentTowardsNextBase > lbl_3_rodata_19BC && fn_3_A46A0(lbl_3_bss_1808[2])) {
        return 1;
    }
    return 0;
}

// .text:0x000A2B6C size:0x130 mapped:0x806E1C00
int fn_3_A2B6C(void) {
    s32 idx;
    s16 fl;
    RepFielder* fp;
    idx = lbl_3_bss_1808[3];
    if (g_Runners[idx].percentTowardsNextBase >= 0.25f) {
        if (lbl_3_bss_1858[idx] <= 3 && fn_3_A46A0(idx)) {
            return 1;
        }
        if (lbl_3_bss_1800 & 0x6000) {
            idx = lbl_3_bss_1808[3];
            if (lbl_3_bss_1858[idx] <= 4) {
                fl = g_FieldingLogic._0D0[3];
                if (fl >= 0) {
                    fp = g_Fielders; fp += fl;
                    if (!(fp->distToBase[3] > 4.0f)) {
                        if (!(g_Runners[idx].percentTowardsNextBase < lbl_3_rodata_19B0) || lbl_3_bss_17FC[3] != 0) {
                            if (fn_3_A46A0(idx)) {
                                return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

// .text:0x000A2C9C size:0x140 mapped:0x806E1D30
int fn_3_A2C9C(void) {
    s32 v;
    if ((lbl_3_bss_1824 & 0x100) && g_Ball.ballDistanceFromBase[3] < 5.0f) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 2 && fn_3_A46A0(lbl_3_bss_1808[2])) {
            return 1;
        }
    }
    if (lbl_3_bss_1818 != 0 && fn_3_A46A0(lbl_3_bss_1808[1])) {
        return 1;
    }
    v = lbl_3_bss_1858[lbl_3_bss_1808[1]];
    if (v <= 4 && g_Strikes.outs == g_Strikes.storedOuts) {
        if (g_Ball.ballDistanceFromBase[1] < 2.5f && v <= 2 && fn_3_A46A0(lbl_3_bss_1808[0])) {
            return 1;
        }
        if (fn_3_A46A0(lbl_3_bss_1808[1])) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A2DDC size:0x1FC mapped:0x806E1E70
int fn_3_A2DDC(void) {
    s16 fl;
    RepFielder* fp;
    if (lbl_3_bss_1818 != 0 && fn_3_A46A0(lbl_3_bss_1808[1])) {
        return 1;
    }
    if (g_Ball.ballDistanceFromBase[0] <= g_Ball.ballDistanceFromBase[2]) {
        if (lbl_3_bss_1800 & 0x1000) {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 3 && fn_3_A46A0(lbl_3_bss_1808[3])) {
                return 1;
            }
        }
        if (lbl_3_bss_1800 & 0x6000) {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 4) {
                fl = g_FieldingLogic._0D0[3];
                if (fl < 0 || (fp = g_Fielders, fp += fl, fp->distToBase[3] > 4.0f)) {
                    if (lbl_3_bss_1858[lbl_3_bss_1808[1]] == 3 && fn_3_A46A0(lbl_3_bss_1808[1])) {
                        return 1;
                    }
                }
                if (fn_3_A46A0(lbl_3_bss_1808[3])) {
                    return 1;
                }
            }
        }
        if (lbl_3_bss_1858[lbl_3_bss_1808[1]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[1])) {
            return 1;
        }
    } else {
        if (lbl_3_bss_1858[lbl_3_bss_1808[1]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[1])) {
            return 1;
        }
        if (lbl_3_bss_1800 & 0x1000) {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 3 && fn_3_A46A0(lbl_3_bss_1808[3])) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x000A2FD8 size:0x210 mapped:0x806E206C
// 97%: only scheduling differs (original loads rodata_1998 before lfsu g_Ball and z after the fadds)
int fn_3_A2FD8(void) {
    s32 t;
    f32 x = ((f32*)&g_Ball.AtBat_Contact_BallPos)[0];
    f32 c = lbl_3_rodata_1998;
    f32 z = ((f32*)&g_Ball.AtBat_Contact_BallPos)[2];
    if (z < c + x && z < c - x) {
        t = 1;
    } else {
        t = 0;
    }
    if (t) {
        if (lbl_3_bss_181C >= 1) {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[3])) {
                return 1;
            }
        } else {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 3 && fn_3_A46A0(lbl_3_bss_1808[3])) {
                return 1;
            }
        }
    }
    if (lbl_3_bss_181C <= 1 && g_Ball.ballDistanceFromBase[3] < lbl_3_rodata_1994) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 2 && fn_3_A46A0(lbl_3_bss_1808[2])) {
            return 1;
        }
    }
    if (g_Ball.ballDistanceFromBase[0] <= g_Ball.ballDistanceFromBase[2]) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[3])) {
            return 1;
        }
        if (lbl_3_bss_1858[lbl_3_bss_1808[1]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[1])) {
            return 1;
        }
    } else {
        if (lbl_3_bss_1858[lbl_3_bss_1808[1]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[1])) {
            return 1;
        }
        if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 4 && fn_3_A46A0(lbl_3_bss_1808[3])) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A31E8 size:0xD0 mapped:0x806E227C
int fn_3_A31E8(void) {
    s32 idx;
    if (!(lbl_3_bss_1824 & 0x1000)) {
        return 0;
    }
    if (lbl_3_bss_1804 & 0x1000) {
        if (fn_3_A46A0(lbl_3_bss_1808[3])) {
            return 1;
        }
    }
    if (lbl_3_bss_1800 & 0x1000) {
        idx = lbl_3_bss_1808[3];
        if (g_Runners[idx].percentTowardsNextBase >= 0.2f && lbl_3_bss_1858[idx] <= 6) {
            if (fn_3_A46A0(idx)) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x000A32B8 size:0xBC mapped:0x806E234C
int fn_3_A32B8(void) {
    s32 idx;
    if (!(lbl_3_bss_1824 & 0x1000)) {
        return 0;
    }
    if (lbl_3_bss_1804 & 0x1000) {
        if (fn_3_A46A0(lbl_3_bss_1808[3])) {
            return 1;
        }
    }
    if (lbl_3_bss_1800 & 0x1000) {
        idx = lbl_3_bss_1808[3];
        if (g_Runners[idx].percentTowardsNextBase >= 0.2f) {
            if (fn_3_A46A0(idx)) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x000A3374 size:0x348 mapped:0x806E2408
// NONMATCHING 99.7%: float registers swapped in the distance-limit compare
#if NONMATCHING
int fn_3_A3374(void) {
    RepFielder* f = &g_Fielders[g_Ball.fielderWBallIndex];
    s32 idx;

    if (lbl_3_bss_1824 & 0x1000) {
        if (!(lbl_3_bss_1824 & 0xFFF) && g_Ball.AtBat_ContactResult == 3 && g_Ball.timeSinceBallPickedUp < 0x1E) {
            f32 limit = 0.35f * (f32)f->_1CE + 69.0f;
            if (g_Ball.ballDistanceFromBase[0] >= 62.0f && g_Ball.ballDistanceFromBase[0] <= limit &&
                g_Runners[3].tagUpInd == 0) {
                if (g_Runners[3].runningDirectionCode == 1 && fn_3_A46A0(lbl_3_bss_1808[3])) {
                    return 1;
                }
                return 1;
            }
        }
        if (lbl_3_bss_1800 & 0x1000) {
            if (lbl_3_bss_181C == 3) {
                if (g_Ball.ballDistanceFromBase[0] < 75.0f) {
                    idx = lbl_3_bss_1808[3];
                    if (lbl_3_bss_1858[idx] <= 7 && fn_3_A46A0(idx)) {
                        return 1;
                    }
                }
                return 0;
            }
            if (lbl_3_bss_181C == 2) {
                if (g_Ball.ballDistanceFromBase[0] < 75.0f) {
                    idx = lbl_3_bss_1808[3];
                    if (lbl_3_bss_1858[idx] <= 6 && fn_3_A46A0(idx)) {
                        return 1;
                    }
                }
                return 0;
            }
            if (g_Ball.ballDistanceFromBase[0] < 68.0f) {
                if (lbl_3_bss_1824 & 0x110) {
                    return 0;
                }
                idx = lbl_3_bss_1808[3];
                if (lbl_3_bss_1858[idx] <= 4 && fn_3_A46A0(idx)) {
                    return 1;
                }
            }
        }
    }
    if ((lbl_3_bss_1824 & 0x100) && g_Ball.ballDistanceFromBase[3] < 65.0f && (lbl_3_bss_1800 & 0x100)) {
        if (!(lbl_3_bss_1824 & 0x10)) {
            idx = lbl_3_bss_1808[2];
            if (lbl_3_bss_1858[idx] <= 5 && fn_3_A46A0(idx)) {
                return 1;
            }
        } else if (!(lbl_3_bss_1800 & 0x60)) {
            idx = lbl_3_bss_1808[2];
            if (lbl_3_bss_1858[idx] <= 4 && fn_3_A46A0(idx)) {
                return 1;
            }
        }
    }
    if ((lbl_3_bss_1824 & 0x10) && g_Ball.ballDistanceFromBase[2] < 50.0f && (lbl_3_bss_1800 & 0x10) &&
        !(lbl_3_bss_1824 & 0x1000)) {
        idx = lbl_3_bss_1808[1];
        if (lbl_3_bss_1858[idx] <= 5 && fn_3_A46A0(idx)) {
            return 1;
        }
    }
    return 0;
}
#endif

// .text:0x000A36BC size:0x70 mapped:0x806E2750
int fn_3_A36BC(void) {
    f32 z = ((f32*)&g_Ball.AtBat_Contact_BallPos)[2];
    f32 x;
    if (z < lbl_3_rodata_1A0C && z > lbl_3_rodata_1A10) {
        x = ((f32*)&g_Ball.AtBat_Contact_BallPos)[0];
        if (z < lbl_3_rodata_198C + x && z > x - lbl_3_rodata_198C && x > g_Runners[0].position.x) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A372C size:0x3C mapped:0x806E27C0
// Indexing the position as an f32 array is needed for the register allocation to match.
int fn_3_A372C(void) {
    f32 x = ((f32*)&g_Ball.AtBat_Contact_BallPos)[0];
    f32 z = ((f32*)&g_Ball.AtBat_Contact_BallPos)[2];
    if (z < lbl_3_rodata_1998 + x && z < lbl_3_rodata_1998 - x) {
        return 1;
    }
    return 0;
}

// .text:0x000A3768 size:0x54 mapped:0x806E27FC
int fn_3_A3768(void) {
    s16 v = g_Ball.ballAngleFromHome;
    if (v >= 0x380 && v < 0x640 && g_Ball.ballZoneAwayFromHome <= 1 && g_Ball.AtBat_Contact_BallPos.z > lbl_3_rodata_19B8 + g_Ball.AtBat_Contact_BallPos.x) {
        return 1;
    }
    return 0;
}

// .text:0x000A37BC size:0x90 mapped:0x806E2850
int fn_3_A37BC(void) {
    InMemBallType* b = &g_Ball;
    s16 v = b->ballAngleFromHome;
    if (v < 0x398) {
        return 0;
    }
    if (b->ballDistanceFromBase[2] < lbl_3_rodata_1994) {
        return 1;
    }
    if (v < 0x400) {
        if (b->AtBat_Contact_BallPos.z + b->AtBat_Contact_BallPos.x > lbl_3_rodata_1998) {
            return 1;
        }
    } else if (b->AtBat_Contact_BallPos.z - b->AtBat_Contact_BallPos.x > lbl_3_rodata_1998) {
        return 1;
    }
    return 0;
}

// .text:0x000A384C size:0x2E4 mapped:0x806E28E0
void fn_3_A384C(void) {
    RepFielder* f;
    f32 dz;
    f32 dx;
    f32 d;
    f32 step;
    f32 a;
    f32 b;
    s32 n;

    if ((lbl_3_bss_1824 & 0x11) && lbl_3_bss_1858[lbl_3_bss_1808[1]] <= 4) {
        f = &g_Fielders[g_Ball.fielderWBallIndex];
        step = (f32)f->_1CD / lbl_3_rodata_1938;
        dx = lbl_3_data_4444[4] - f->pos.x;
        dz = lbl_3_data_4444[5] - f->pos.z;
        a = dx * dx;
        b = dz * dz;
        d = a + b;
        SQRT_L(d);
        if (lbl_3_rodata_193C == step) {
            step = lbl_3_rodata_1958;
        }
        if (d > lbl_3_rodata_195C) {
            n = (s32)(lbl_3_rodata_1960 * d / step);
        } else if (d > lbl_3_rodata_1964) {
            n = (s32)(d / step);
        } else {
            n = (s32)(lbl_3_rodata_1968 * d / step);
        }
        if (d > lbl_3_rodata_196C) {
            n = (s32)((f32)n * lbl_3_rodata_1970);
            n += 0x1E;
        } else if (d > lbl_3_rodata_1974) {
            n = (s32)((f32)n * lbl_3_rodata_1960);
            n += 0x1E;
        }
        if (n + 0x32 < g_Runners[0].framesToNextBase) {
            lbl_3_bss_1818 = 1;
        }
    }
}

// .text:0x000A3B30 size:0xD0 mapped:0x806E2BC4
void fn_3_A3B30(void) {
    s32 diff;
    diff = g_Scores.team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] - g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
    lbl_3_bss_181C = 0;
    if (g_Scores.inning >= g_Scores.maxInnings && g_Scores._AD != 0 && diff == 0) {
        lbl_3_bss_181C = 3;
        return;
    }
    if (g_Scores.inning >= g_Scores.maxInnings - 1 && diff <= 1 && diff >= -1) {
        lbl_3_bss_181C = 2;
        return;
    }
    if (g_Scores.inning >= g_Scores.maxInnings - 4 && diff <= 1 && diff >= -3) {
        lbl_3_bss_181C = 1;
    }
}

// .text:0x000A3C00 size:0xC0 mapped:0x806E2C94
void fn_3_A3C00(void) {
    s32 i;
    lbl_3_bss_1800 = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_3_bss_1808[i] >= 0) {
            u8 v = g_Runners[lbl_3_bss_1808[i]].runningDirectionCode;
            if (v == 1) {
                lbl_3_bss_1800 |= 1 << (i * 4);
            } else if (v == 3) {
                lbl_3_bss_1800 |= 2 << (i * 4);
            } else if (v == 2) {
                lbl_3_bss_1800 |= 4 << (i * 4);
            }
        }
    }
}

// .text:0x000A3CC0 size:0x498 mapped:0x806E2D54
void fn_3_A3CC0(void) {
    return;
}

// .text:0x000A4158 size:0x90 mapped:0x806E31EC
void fn_3_A4158(int i) {
    InMemRunnerType* r = &g_Runners[i];
    if (r->runningDirectionCode == 2) {
        fn_3_52F4C(g_Ball.fielderWBallIndex, r->position.x, r->position.z);
    } else {
        f32 s = r->distanceFromBall;
        f32 a = r->velocity.x * s;
        f32 b = r->velocity.y * s;
        fn_3_52F4C(g_Ball.fielderWBallIndex, 2.0f * a + r->position.x, 2.0f * b + r->position.z);
    }
}

// .text:0x000A41E8 size:0x4B8 mapped:0x806E327C
void fn_3_A41E8(void) {
    return;
}

// .text:0x000A46A0 size:0x370 mapped:0x806E3734
// NONMATCHING 99.3%: r27/r28 swapped (runner pointer vs i*4), fn_3_A36BC and fn_3_A4158 are inlined
#if NONMATCHING
int fn_3_A46A0(s32 i) {
    InMemRunnerType* r = &g_Runners[i];
    RepFielder* f = &g_Fielders[g_Ball.fielderWBallIndex];
    s32 base;
    s32 chance;

    if (i < 0) {
        g_FieldingLogic._0CC = -1;
        g_FieldingLogic._0C4 = -1;
        return 0;
    }
    if (i == 0 && r->currentBase == 0 && f->_1ED == 0) {
        s32 near; // inlined fn_3_A36BC
        f32 z = ((f32*)&g_Ball.AtBat_Contact_BallPos)[2];
        f32 x;
        if (z < 15.0f && z > 8.0f && (x = ((f32*)&g_Ball.AtBat_Contact_BallPos)[0], z < 1.5f + x) &&
            z > x - 1.5f && x > g_Runners[0].position.x) {
            near = 1;
        } else {
            near = 0;
        }
        if (!near) {
            goto normal;
        }
        g_FieldingLogic._0DE = i;
        g_FieldingLogic._0CC = 9;
        g_FieldingLogic._0C4 = -1;
        fn_3_52F4C(g_Ball.fielderWBallIndex, r->position.x, r->position.z);
        return 1;
    }
normal:
    base = lbl_3_bss_1838[i];
    if (base >= 0) {
        if (f->_1ED != 0) {
            g_FieldingLogic._0CC = -1;
            g_FieldingLogic._0DE = -1;
            return 1;
        }
        if (g_FieldingLogic._0CC != base) {
            g_FieldingLogic._0CC = base;
            if ((s16)base == 9) {
                if (g_FieldingLogic._130 != 0 && g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] == 0) {
                    g_FieldingLogic._0CC = -1;
                } else {
                    g_FieldingLogic._0DE = i;
                }
            }
            if (g_FieldingLogic._0CC != 9) {
                fn_3_52F4C(g_Ball.fielderWBallIndex, lbl_3_data_4444[g_FieldingLogic._0CC * 2],
                           lbl_3_data_4444[g_FieldingLogic._0CC * 2 + 1]);
            }
        }
        if (g_FieldingLogic._0CC == 9) {
            // inlined fn_3_A4158
            if (r->runningDirectionCode == 2) {
                fn_3_52F4C(g_Ball.fielderWBallIndex, r->position.x, r->position.z);
            } else {
                f32 d = r->distanceFromBall;
                fn_3_52F4C(g_Ball.fielderWBallIndex, 2.0f * (r->velocity.x * d) + r->position.x,
                           2.0f * (r->velocity.y * d) + r->position.z);
            }
        }
    } else {
        g_FieldingLogic._0CC = -1;
        g_FieldingLogic._0DE = -1;
    }
    base = lbl_3_bss_1828[i];
    if (base >= 10) {
        g_FieldingLogic._0C4 = -1;
        return 1;
    }
    g_FieldingLogic._0C4 = base;
    g_FieldingLogic._12D = 1;
    if (lbl_3_bss_1858[i] >= 4) {
        chance = lbl_3_data_1C38[0] + (s32)((f32)(lbl_3_data_1C38[1] - lbl_3_data_1C38[0]) *
                                            g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.awayTeamBattingInd_battingTeam]);
        if (chance < RandomInt_Game(100)) {
            g_FieldingLogic._12D = 0;
        }
    }
    if (g_FieldingLogic._0C4 == -1 && g_FieldingLogic._0CC == -1) {
        return 0;
    }
    return 1;
}
#endif

// .text:0x000A4A10 size:0x540 mapped:0x806E3AA4
void fn_3_A4A10(void) {
    return;
}

// .text:0x000A4F50 size:0x48C mapped:0x806E3FE4
void fn_3_A4F50(void) {
    return;
}

// .text:0x000A53DC size:0x328 mapped:0x806E4470
// NONMATCHING 87.5%: instruction scheduling and register allocation differ; fn_3_A6ABC is inlined
#if NONMATCHING
void fn_3_A53DC(s32 i) {
    InMemRunnerType* r = &g_Runners[i];
    RepFielder* f = &g_Fielders[g_Ball.fielderWBallIndex];
    f32 a;
    f32 dx;
    f32 d;
    f32 step;
    f32 dz;
    f32 b;
    s32 n;

    if (i == 3 && r->baseStandingOn == 3 && g_RunningLogic._00 == 0x1000 && g_Ball.ballZoneAwayFromHome >= 4 &&
        g_Ball.AtBat_ContactResult == 3) {
        // inlined fn_3_A6ABC(home x, home z)
        dx = lbl_3_data_4444[0] - f->pos.x;
        step = (f32)f->_1CD / lbl_3_rodata_1938;
        dz = lbl_3_data_4444[1] - f->pos.z;
        a = dx * dx;
        b = dz * dz;
        d = a + b;
        SQRT_L(d);
        if (lbl_3_rodata_193C == step) {
            step = lbl_3_rodata_1958;
        }
        if (d > lbl_3_rodata_195C) {
            n = (s32)(lbl_3_rodata_1960 * d / step);
        } else if (d > lbl_3_rodata_1964) {
            n = (s32)(d / step);
        } else {
            n = (s32)(lbl_3_rodata_1968 * d / step);
        }
        if (d > lbl_3_rodata_196C) {
            n = (s32)((f32)n * lbl_3_rodata_1970) + 0x1E;
        } else if (d > lbl_3_rodata_1974) {
            n = (s32)((f32)n * lbl_3_rodata_1960) + 0x1E;
        }
        lbl_3_bss_1828[i] = 0;
        lbl_3_bss_1838[i] = -1;
        lbl_3_bss_1848[i] = f->_192 + n + lbl_3_data_1C40 - r->framesToNextBase;
    }
}
#endif

// .text:0x000A5704 size:0x448 mapped:0x806E4798
void fn_3_A5704(void) {
    return;
}

// .text:0x000A5B4C size:0x898 mapped:0x806E4BE0
void fn_3_A5B4C(void) {
    return;
}

// .text:0x000A63E4 size:0x404 mapped:0x806E5478
// NONMATCHING 91%: float register allocation and constant-load scheduling differ; fn_3_A6ABC is inlined
#if NONMATCHING
s32 fn_3_A63E4(s32 i, s32 useNext, s32* throwBase, s32* coverBase) {
    InMemRunnerType* r = &g_Runners[i];
    RepFielder* f = &g_Fielders[g_Ball.fielderWBallIndex];
    s32 runnerFrames;
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    f32 b;
    f32 step;
    f32 a;
    f32 d;
    s32 frames;
    s32 n;
    s32 base;
    s32 throwFrames;
    s16 cover;
    s16 coverFrames;
    f32 ballDist;

    if (useNext == 0) {
        runnerFrames = r->framesToPreviousBase;
        base = r->currentBase;
    } else {
        runnerFrames = r->framesToNextBase;
        base = r->nextBase;
    }
    // inlined fn_3_A6ABC(base x, base z)
    tx = lbl_3_data_4444[base * 2];
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    tz = lbl_3_data_4444[base * 2 + 1];
    dx = tx - f->pos.x;
    dz = tz - f->pos.z;
    cover = g_FieldingLogic._0D0[base];
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (lbl_3_rodata_193C == step) {
        step = lbl_3_rodata_1958;
    }
    if (d > lbl_3_rodata_195C) {
        n = (s32)(lbl_3_rodata_1960 * d / step);
    } else if (d > lbl_3_rodata_1964) {
        n = (s32)(d / step);
    } else {
        n = (s32)(lbl_3_rodata_1968 * d / step);
    }
    if (d > lbl_3_rodata_196C) {
        n = (s32)((f32)n * lbl_3_rodata_1970) + 0x1E;
    } else if (d > lbl_3_rodata_1974) {
        n = (s32)((f32)n * lbl_3_rodata_1960) + 0x1E;
    }
    ballDist = g_Ball.ballDistanceFromBase[base];
    frames = f->_192 + n;
    if (ballDist > lbl_3_rodata_195C && ballDist < lbl_3_rodata_1974 && (base == 0 || base == 3)) {
        frames -= 0x2D;
    }
    throwFrames = fn_3_52560(g_Ball.fielderWBallIndex, tx, tz);
    if (cover == g_Ball.fielderWBallIndex || cover == -1 || ballDist < lbl_3_rodata_199C) {
        *throwBase = -1;
        *coverBase = base;
        return runnerFrames - throwFrames;
    }
    coverFrames = g_Fielders[cover].framesToDest;
    if (throwFrames < coverFrames + 5) {
        *throwBase = -1;
        *coverBase = base;
        return runnerFrames - throwFrames;
    }
    if (frames < coverFrames) {
        *throwBase = base + 10;
        *coverBase = -1;
        return runnerFrames - g_Fielders[cover].framesToDest;
    }
    *throwBase = base;
    *coverBase = -1;
    return runnerFrames - frames;
}
#endif

// .text:0x000A67E8 size:0x28 mapped:0x806E587C

void fn_3_A67E8(s32 i) {
    lbl_3_bss_1838[i] = 9;
    lbl_3_bss_1828[i] = -1;
}

// .text:0x000A6810 size:0x2AC mapped:0x806E58A4
#pragma dont_inline off
s32 fn_3_A6810(f32 x1, f32 z1, f32 x2, f32 z2) {
    f32 dz;
    f32 dx;
    f32 d;
    f32 step;
    f32 a;
    f32 b;
    f32 div;
    s32 n;

    dx = x2 - x1;
    dz = z2 - z1;
    step = (f32)lbl_3_data_4744[0xA] / lbl_3_rodata_1A2C;
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (lbl_3_rodata_193C == step) {
        div = lbl_3_rodata_1958;
    } else {
        div = step;
    }
    n = (s32)(d / div);
    if (d > lbl_3_rodata_196C) {
        n = (s32)((f32)n * lbl_3_rodata_1A30) + 0x1E;
    } else if (d > lbl_3_rodata_1974) {
        n = (s32)((f32)n * lbl_3_rodata_1970) + 0x1E;
    } else if (d > lbl_3_rodata_195C) {
        n = (s32)((f32)n * lbl_3_rodata_19EC) + 0x1E;
    } else if (d > lbl_3_rodata_1A08) {
        n = (s32)((f32)n * lbl_3_rodata_1A34);
    }
    return n;
}
#pragma dont_inline on

// .text:0x000A6ABC size:0x28C mapped:0x806E5B50
s32 fn_3_A6ABC(f32 x, f32 z) {
    RepFielder* f;
    f32 dz;
    f32 dx;
    f32 d;
    f32 step;
    f32 a;
    f32 b;
    f32 div;
    s32 n;

    f = &g_Fielders[g_Ball.fielderWBallIndex];
    dx = x - f->pos.x;
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    dz = z - f->pos.z;
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (lbl_3_rodata_193C == step) {
        div = lbl_3_rodata_1958;
    } else {
        div = step;
    }
    if (d > lbl_3_rodata_195C) {
        n = (s32)(lbl_3_rodata_1960 * d / div);
    } else if (d > lbl_3_rodata_1964) {
        n = (s32)(d / div);
    } else {
        n = (s32)(lbl_3_rodata_1968 * d / div);
    }
    if (d > lbl_3_rodata_196C) {
        n = (s32)((f32)n * lbl_3_rodata_1970) + 0x1E;
    } else if (d > lbl_3_rodata_1974) {
        n = (s32)((f32)n * lbl_3_rodata_1960) + 0x1E;
    }
    return n;
}

// .text:0x000A6D48 size:0x150 mapped:0x806E5DDC
void fn_3_A6D48(void) {
    s32 i;
    lbl_3_bss_1824 = 0;
    lbl_3_bss_1808[0] = -1;
    lbl_3_bss_1808[1] = -1;
    lbl_3_bss_1808[2] = -1;
    lbl_3_bss_1808[3] = -1;
    for (i = 3; i >= 0; i--) {
        InMemRunnerType* r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored == 1) {
            s32 b = r->currentBase;
            lbl_3_bss_1824 |= 1 << ((s32)r->fractionalBasesRan * 4);
            if (lbl_3_bss_1808[b] < 0 || g_Runners[lbl_3_bss_1808[b]].baseStandingOn >= 0) {
                lbl_3_bss_1808[b] = i;
            }
        }
    }
}

// .text:0x000A6E98 size:0x1A8 mapped:0x806E5F2C
void fn_3_A6E98(s32 fielder) {
    g_FieldingLogic_s* p;
    g_FieldingLogic_s* fl;
    InMemRunnerType* r;
    s8 s;
    u8 st;

    p = &g_FieldingLogic;
    if (p->_0EC > 0) {
        p->_0EC -= 1;
    }
    if (g_FieldingLogic._125 >= 0) {
        s = g_FieldingLogic._125;
        g_Ball.baseBallAndFielderAreOn = s;
        if (g_FieldingLogic._0CC == s) {
            g_FieldingLogic._0CC = -1;
        }
    }
    if (p->_0EC <= 0) {
        g_FieldingLogic._112 = 2;
    }
    fl = &g_FieldingLogic;
    st = fl->_111;
    if (st == 2 && fl->_112 == 1) {
        s16 k = fl->_0E8;
        fn_3_52F4C(fielder, g_Runners[k].position.x, g_Runners[k].position.z);
        if (g_FieldingLogic._0CC == 9) {
            g_FieldingLogic._0DE = fl->_0E8;
        }
        fn_3_A3CC0();
    } else if (st == 1) {
        s16 i = g_FieldingLogic._0E8;
        if (i >= 0) {
            r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == 1) {
                if (r->baseStandingOn >= 0) {
                    fl->_111 = 0;
                } else if (r->actionCode == 0 && (r->runningDirectionCode == 1 || r->runningDirectionCode == 3)) {
                    fl->_111 = 0;
                }
            } else {
                fl->_111 = 0;
            }
        } else {
            fl->_111 = 0;
        }
        if (g_FieldingLogic._0DE >= 0) {
            g_FieldingLogic._0DE = -1;
            g_FieldingLogic._0CC = -1;
        }
    }
}

// .text:0x000A7040 size:0x674 mapped:0x806E60D4
void fn_3_A7040(void) {
    return;
}

// .text:0x000A76B4 size:0x5D4 mapped:0x806E6748
void fn_3_A76B4(void) {
    return;
}

// .text:0x000A7C88 size:0x270 mapped:0x806E6D1C
void fn_3_A7C88(void) {
    InputStruct* in;
    u16 b4;
    s16 v;

    in = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    if (g_d_GameSettings.GameModeSelected == 6) {
        return;
    }
    if (g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        in = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (g_d_GameSettings.minigamesEnabled != 0) {
        in = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1922]];
    }
    if (!(in->buttonInput & 0x100)) {
        g_FieldingLogic._145 = 0;
    }
    if (g_FieldingLogic._145 != 0) {
        if (g_FieldingLogic._145 < 0xFE) {
            g_FieldingLogic._145++;
        } else {
            g_FieldingLogic._145 = 0xFF;
        }
    }
    b4 = in->buttonInput;
    if (!(b4 & 0x100)) {
        return;
    }
    if (in->newButtonInput & 0x100) {
        if (b4 & 0x40) {
            g_FieldingLogic._0C6 = 6;
        } else {
            v = in->controlStickAngle;
            if (v >= 0xE00) {
                g_FieldingLogic._0C6 = 1;
            } else if (v >= 0xA00) {
                g_FieldingLogic._0C6 = 0;
            } else if (v >= 0x600) {
                g_FieldingLogic._0C6 = 3;
            } else if (v >= 0x200) {
                g_FieldingLogic._0C6 = 2;
            } else if (v >= 0) {
                g_FieldingLogic._0C6 = 1;
            } else {
                g_FieldingLogic._145 = 1;
            }
        }
    } else if (g_FieldingLogic._145 >= *(s16*)(lbl_3_data_49DC + 0x50)) {
        if (g_FieldingLogic._0C2 >= 0) {
            return;
        }
        g_FieldingLogic._0C6 = 8;
    }
    g_FieldingLogic._0C8 = 0;
    if (g_FieldingLogic._0C6 == 8) {
        g_FieldingLogic._12D = 1;
        return;
    }
    if (g_FieldingLogic._12F <= lbl_3_data_475C && g_d_GameSettings.minigamesEnabled == 0) {
        g_FieldingLogic._12D = 0;
        return;
    }
    g_FieldingLogic._12D = 1;
}

// .text:0x000A7EF8 size:0x17C mapped:0x806E6F8C
void fn_3_A7EF8(void) {
    InputStruct* in;
    s16 v;
    u8 prev;

    in = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
        in = &g_Practice.inputs[g_GameLogic.teamFielding];
    } else if (g_d_GameSettings.minigamesEnabled != 0) {
        in = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1922]];
    }
    v = in->controlStickAngle;
    prev = g_FieldingLogic._12E;
    if (v >= 0xE00) {
        g_FieldingLogic._12E = 2;
    } else if (v >= 0xA00) {
        g_FieldingLogic._12E = 3;
    } else if (v >= 0x600) {
        g_FieldingLogic._12E = 4;
    } else if (v >= 0x200) {
        g_FieldingLogic._12E = 1;
    } else if (v >= 0) {
        g_FieldingLogic._12E = 2;
    } else {
        g_FieldingLogic._12E = 0;
    }
    if (g_FieldingLogic._12E == 0) {
        g_FieldingLogic._12F = 0;
        return;
    }
    if (g_FieldingLogic._12E == prev) {
        if (g_FieldingLogic._12F < 0xFE) {
            g_FieldingLogic._12F++;
            return;
        }
        g_FieldingLogic._12F = 0xFF;
        return;
    }
    g_FieldingLogic._12F = 1;
}

// .text:0x000A8074 size:0x2C4 mapped:0x806E7108
void fn_3_A8074(s32 idx) {
    s16 dc;
    s32 sel;
    s16 cc;
    s32 fwd;
    RepFielder* f;
    s16 res;

    s32 d;
    s32 i;
    sel = -1;
    f = &g_Fielders[idx];
    fwd = 0;
    res = -1;
    dc = g_FieldingLogic._0DC;
    if (dc < 0) {
        g_FieldingLogic._0DE = -1;
        return;
    }
    cc = g_FieldingLogic._0CC;
    d = cc - dc;
    if (d == 1 || d == -3) {
        sel = dc;
    } else if (d == -1 || d == 3) {
        sel = cc;
    }
    if (sel >= 0) {
        if (cc > dc || (cc == 0 && dc == 3)) {
            fwd = 1;
        }
        if (fwd != 0) {
            for (i = 0; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && sel == g_Runners[i].currentBase && g_Runners[i].baseStandingOn < 0 && f->distToBase[cc] > g_Runners[i].distToNextBase) {
                    res = i;
                    break;
                }
            }
        } else {
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && sel == g_Runners[i].currentBase && g_Runners[i].baseStandingOn < 0 && f->distToBase[cc] > g_Runners[i].distToCurrentBase) {
                    res = i;
                    break;
                }
            }
        }
    }
    g_FieldingLogic._0DE = res;
}

// .text:0x000A8338 size:0x140 mapped:0x806E73CC
void fn_3_A8338(s32 idx) {
    g_FieldingLogic_s* fl;
    s16 sel;
    RepFielder* fp;
    fl = &g_FieldingLogic;
    sel = fl->_0CC;
    fp = &g_Fielders[idx];
    if (sel >= 0 && sel <= 3 && fp->_1F5 == sel) {
        fl->_0CC = -1;
        return;
    }
    if (g_FieldingLogic._0E2 == -1) {
        s16 r = g_FieldingLogic._0DE;
        if (r >= 0 && g_Runners[r].runnerOnFieldOrOutOrScored != 1) {
            g_FieldingLogic._0DE = -1;
            fl->_0CC = -1;
            return;
        }
        g_FieldingLogic._0E2 = sel;
        fn_3_A8074(idx);
    }
    sel = fl->_0CC;
    if (sel >= 0 && sel <= 3) {
        s16 rr = g_FieldingLogic._0DE;
        if (rr == -1) {
            fn_3_52F4C(g_Ball.fielderWBallIndex, lbl_3_data_4444[sel * 2], lbl_3_data_4444[sel * 2 + 1]);
        } else {
            f32 x = g_Runners[rr].position.x;
            fn_3_52F4C(g_Ball.fielderWBallIndex, x, g_Runners[rr].position.z);
        }
    }
    fn_3_A3CC0();
}

// .text:0x000A8478 size:0x150 mapped:0x806E750C
// ~95%: logic and block layout match; only regs differ (idx r8/prev r7/tmp r6 vs orig r7/r6/r7) and ec/ea load order in the final add
s32 fn_3_A8478(s32* out0, s32* out1) {
    u8 dir;
    s32 prev;
    s32 idx;
    InMemRunnerType* r;

    idx = g_FieldingLogic._0C4;
    if (idx >= 4 || (s16)idx < 0) {
        return 0;
    }
    if (g_Ball.AtBat_ContactResult == 3) {
        r = &g_Runners[idx];
        if (r->runnerOnFieldOrOutOrScored == 1 && r->tagUpInd == 2) {
            *out0 = idx;
            goto cur;
        }
    }
    prev = idx == 0 ? 3 : idx - 1;
    r = &g_Runners[prev];
    if (r->runnerOnFieldOrOutOrScored == 1 && r->forceOutCd == 1) {
        *out0 = prev;
        goto tail;
    }
    return 0;
cur:
    if (r->currentBase == idx) {
        dir = r->runningDirectionCode;
        if (dir == 3 || dir == 2) {
            *out1 = r->framesToPreviousBase;
        } else if ((dir == 1 && r->nextDirectionBeingProcessed == 3) || (dir == 3 && r->nextDirectionBeingProcessed == 1)) {
            *out1 = r->framesToPreviousBase + 0x14;
        } else {
            *out1 = r->framesToPreviousBase + 0x32;
        }
    } else {
        *out1 = r->framesToNextBase + r->framesToPreviousBase + r->framesToPreviousBase;
    }
    return 1;
tail:
    *out1 = r->framesToNextBase;
    return 1;
}

// .text:0x000A85C8 size:0x40C mapped:0x806E765C
// NONMATCHING 92.5%: float register allocation in the inlined fn_3_A6ABC body differs
#if NONMATCHING
#pragma dont_inline off
void fn_3_A85C8(f32 dist) {
    s32 target;
    s32 runnerFrames;
    s32 i;
    s32 runners;
    s32 n;

    runners = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            runners++;
        }
    }
    if (fn_3_A8478(&target, &runnerFrames) == 0) {
        if (dist < lbl_3_rodata_1A0C) {
            g_FieldingLogic.throwSpeedType = 7;
            return;
        }
        if (dist < lbl_3_rodata_1A38 && g_FieldingLogic.throwSpeedType < 5) {
            g_FieldingLogic.throwSpeedType = 5;
        }
    } else {
        n = ballFielderFramesTo(g_Ball.throwDestination.x, g_Ball.throwDestination.z);
        if ((g_Strikes.outs >= 2 || runners == 1) && n + 0x14 - runnerFrames < -0x1E &&
            g_Ball.numberOfThrowsDuringPlay <= 1) {
            g_FieldingLogic.throwSpeedType = 4;
            if (dist > lbl_3_rodata_1964) {
                g_FieldingLogic.throwSpeedType = 3;
            } else if (dist < lbl_3_rodata_1A40) {
                g_FieldingLogic.throwSpeedType = 6;
            }
            g_FieldingLogic._10B = 1;
        }
    }
}
#pragma dont_inline on
#endif

// .text:0x000A89D4 size:0x980 mapped:0x806E7A68
void fn_3_A89D4(void) {
    return;
}

// .text:0x000A9354 size:0x3A8 mapped:0x806E83E8
void fn_3_A9354(int fi, int mode) {
    RepFielder* f = &g_Fielders[fi];
    VecSrcDst ray;
    CollisionStruct hit;
    u32 type;
    s32 ang;
    f32 cx;
    f32 cz;
    f32 speed;
    s32 i;

    if (g_Ball.fielderWBallIndex != fi) {
        return;
    }
    g_Ball.AtBat_Contact_BallPos.x = f->pos.x + g_Ball.offsetWhilePickedUpHistory[0].x;
    g_Ball.AtBat_Contact_BallPos.y = f->pos.y + g_Ball.offsetWhilePickedUpHistory[0].y;
    g_Ball.AtBat_Contact_BallPos.z = f->pos.z + g_Ball.offsetWhilePickedUpHistory[0].z;
    ray.src.x = g_Ball.AtBat_Contact_BallPos.x;
    ray.src.y = lbl_3_rodata_1978;
    ray.src.z = g_Ball.AtBat_Contact_BallPos.z;
    ray.dst.x = g_Ball.AtBat_Contact_BallPos.x;
    ray.dst.y = lbl_3_rodata_1994;
    ray.dst.z = g_Ball.AtBat_Contact_BallPos.z;
    if (g_d_GameSettings.GameModeSelected == 6) {
        type = checkCollision(&ray, &hit, 2, 0);
    } else {
        type = checkCollision(&ray, &hit, 1, 0);
    }
    type &= 0x7F;
    if (!(type == 1 || type == 6 || type == 9 || type == 10)) {
        g_Ball.AtBat_Contact_BallPos.y = f->pos.y;
        g_Ball.AtBat_Contact_BallPos.x = f->pos.x;
        g_Ball.AtBat_Contact_BallPos.z = f->pos.z;
        g_Ball.AtBat_Contact_BallPos.y = g_Ball.offsetWhilePickedUpHistory[0].y;
    }
    if (g_Ball.AtBat_Contact_BallPos.y < 0.5f) {
        g_Ball.AtBat_Contact_BallPos.y = 0.5f;
    }
    if (mode == 0) {
        ang = RandomInt_Game_Range(lbl_3_data_4860[f->_214].a, lbl_3_data_4860[f->_214].b);
    } else if (mode == 1) {
        ang = f->_1C2;
    } else {
        ang = fn_3_9FE6C_normalizeAngle(g_Ball.ballAngleFromHome + 0x800);
    }
    getComponentsFromSAng(ang, &cx, &cz);
    g_Ball.physicsSubstruct.velocity.y = 0.0001f * (f32)RandomInt_Game(300) + 0.02f;
    speed = 0.0001f * (f32)RandomInt_Game(200) + 0.05f;
    g_Ball.physicsSubstruct.velocity.x = cx * speed;
    g_Ball.physicsSubstruct.velocity.z = cz * speed;
    g_Ball.framesSinceThrowStarted = 0;
    g_Ball.ballState = BALL_STATE_LOOSE;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.thrownBallHasHitGround = 0;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = g_Ball.timeSinceBallPickedUp;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.ballIsRollingIndicator = 0;
    g_Ball.groundRuleDoubleInd = 0;
    g_FieldingLogic._124 = 0;
    g_FieldingLogic._125 = -1;
    g_FieldingLogic._12A = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            if (g_Runners[i].tagUpInd == 2) {
                g_Runners[i].baseReachedAtTimeOfThrow = g_Runners[i].startingBase_baseAchieved;
            } else {
                g_Runners[i].baseReachedAtTimeOfThrow = g_Runners[i].currentBase;
            }
        } else {
            g_Runners[i].baseReachedAtTimeOfThrow = -1;
        }
    }
}

// .text:0x000A96FC size:0x288 mapped:0x806E8790
// NONMATCHING 88%: saved-register assignment differs (fi/fielder/g_FieldingLogic in r30/r31/r29 vs r29/r30/r31) and minor scheduling
#if NONMATCHING
void fn_3_A96FC(int fi) {
    RepFielder* f = &g_Fielders[fi];
    InMemRunnerType* r = &g_Runners[f->_213];
    u8 state = f->_212;
    s16 base;
    f32 cx;
    f32 cz;

    if (state == 0) {
        f->_212 = 1;
        g_FieldingLogic._0F6 = r->actionFrames_countDown - 1;
        return;
    }
    if (state == 1) {
        if (--g_FieldingLogic._0F6 <= 0) {
            if (f->_211 == 1) {
                f->_212 = 2;
                g_FieldingLogic._0F6 = lbl_3_data_4880;
                return;
            }
            f->_212 = 3;
            f->_174 = lbl_3_data_4878[0];
            g_FieldingLogic._0F6 = lbl_3_data_7E34[f->_17A].b;
            f->_1C2 = lbl_3_data_4860[f->_1F7].c;
        }
    } else {
        Tbl4* t = &lbl_3_data_7E34[f->_17A];
        if (t->b - t->c == --g_FieldingLogic._0F6 && state == 3) {
            fn_3_A9354(fi, 0);
            g_FieldingLogic._13B = 1;
            g_FieldingLogic._111 = 0;
        }
        if (f->_212 == 3) {
            getComponentsFromSAng(f->_1C2, &cx, &cz);
            f->_174 = f->_174 * lbl_3_data_4878[1];
            f->velX = cx * f->_174;
            f->velZ = cz * f->_174;
            f->speed = f->_174;
            f->pos.x += f->velX;
            f->pos.z += f->velZ;
        }
        if (g_FieldingLogic._0F6 <= 0) {
            if (f->_212 == 3) {
                fn_3_5985C(fi, 9);
                base = f->coveringBase;
                f->coveringBase = -1;
                g_FieldingLogic._0D0[base] = -1;
                g_FieldingLogic._101[base] = 0;
                f->_1D7 = 0;
                if (g_Ball.fielderWBallIndex == -1) {
                    g_FieldingLogic._13B = 1;
                }
            }
            f->_212 = 0;
            f->_211 = 0;
        }
    }
}
#endif

// .text:0x000A9984 size:0x2F0 mapped:0x806E8A18
void fn_3_A9984(int fi) {
    RepFielder* f = &g_Fielders[fi];
    f32 sp8;
    f32 v[3];
    f32 d;

    if (f->_1AC == 0) {
        f32 ax, az;
        if (f->_1EE <= 1) {
            f->_200 = 0;
            return;
        }
        v[0] = g_Ball.pastCoordinates[2].x - g_Ball.pastCoordinates[3].x;
        v[1] = g_Ball.pastCoordinates[2].y - g_Ball.pastCoordinates[3].y;
        v[2] = g_Ball.pastCoordinates[2].z - g_Ball.pastCoordinates[3].z;
        f->_120 = lbl_3_rodata_1990 * v[0];
        f->_124 = lbl_3_rodata_1990 * v[2];
        f->_200 = 1;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            fn_8004AFA8(f->minigamePlayer);
        } else {
            fn_8004AFA8(fi);
        }
    } else {
        f32 r = (f32)(f->_1EE - 1) / (f32)f->_1EE;
        f->_120 = f->_120 * r;
        f->_124 = f->_124 * r;
        if (f->_1EE <= 1) {
            f->_200 = 0;
        }
        if (f->_1AC > 0) {
            if (g_d_GameSettings.minigamesEnabled != 0) {
                fn_8004AE18(f->minigamePlayer);
            } else {
                fn_8004AE18(fi);
            }
        }
    }
    f->velX = f->_120;
    f->velZ = f->_124;
    d = f->velX * f->velX + f->velZ * f->velZ;
    SQRT_L(d);
    f->speed = d;
    if (fn_3_51798(fi, v)) {
        f->_120 = lbl_3_rodata_193C;
        f->_124 = lbl_3_rodata_193C;
        f->velX = lbl_3_rodata_193C;
        f->velZ = lbl_3_rodata_193C;
        f->speed = lbl_3_rodata_193C;
        return;
    }
    f->pos.x = f->pos.x + f->velX;
    f->pos.z = f->pos.z + f->velZ;
}

// .text:0x000A9C74 size:0xAC mapped:0x806E8D08
void fn_3_A9C74(int i) {
    RepFielder* f = &g_Fielders[i];
    int r = checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 5);
    if (f->_1F8 >= 3) {
        f->_215 = lbl_3_data_4900[r * 3 + 1];
    } else {
        f->_215 = lbl_3_data_4900[r * 3];
    }
    if (r != 0 && g_FieldingLogic._0C4 >= 0) {
        playSoundEffect(0x1A8);
    }
}

// .text:0x000A9D20 size:0xD1C mapped:0x806E8DB4
void fn_3_A9D20(void) {
    return;
}

// .text:0x000AAA3C size:0x1BC mapped:0x806E9AD0
void fn_3_AAA3C(int idx) {
    RepFielder* f = &g_Fielders[idx];
    s16 ce = g_FieldingLogic._0CE;
    s16 c4;
    if (ce < 0) {
        return;
    }
    c4 = g_FieldingLogic._0C4;
    if (c4 < 0 || c4 > 3) {
        return;
    }
    if (f->distToBase[c4] > lbl_3_rodata_19F0 && g_FieldingLogic._0DC < 0) {
        return;
    }
    if (c4 == ce) {
        if (g_FieldingLogic._0E0 >= 0 && g_FieldingLogic._0E0 <= 3) {
            if (g_FieldingLogic._0DC == g_Runners[g_FieldingLogic._0E0].nextBase || g_FieldingLogic._0DC == g_Runners[g_FieldingLogic._0E0].currentBase) {
                g_FieldingLogic._119 = 1;
            }
        }
    }
    if (g_FieldingLogic._0CE == 9) {
        if (g_FieldingLogic._0E0 >= 0 && g_FieldingLogic._0E0 <= 3) {
            InMemRunnerType* r = &g_Runners[g_FieldingLogic._0E0];
            if (r->runnerOnFieldOrOutOrScored == 1 && g_FieldingLogic._0C4 == r->baseRunningTowards) {
                g_FieldingLogic._119 = 1;
            }
        }
    }
    if (g_FieldingLogic._119 != 0) {
        if (g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) {
            s32 o = g_FieldingLogic._0C4;
            f32 a = game_atan2(lbl_3_data_4444[o*2] - f->pos.x, lbl_3_data_4444[o*2+1] - f->pos.z);
            if (fn_3_9FC1C(a, f->facing) > 0x40) {
                g_FieldingLogic._119 = 0;
            }
        }
    }
}

// .text:0x000AABF8 size:0x8C mapped:0x806E9C8C
int fn_3_AABF8(void) {
    s16 idx = g_FieldingLogic._0D8;
    if (idx == -1) {
        return 0;
    }
    if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
        return 0;
    }
    if (g_Fielders[idx].coveringBase != 5) {
        return 0;
    }
    return !(g_Fielders[g_Ball.fielderWBallIndex]._0B8 < lbl_3_rodata_19F0);
}

// .text:0x000AAC84 size:0x36C mapped:0x806E9D18
// NONMATCHING 89%: receiver position loads use lfsx/lfsu in the original, register allocation differs; fn_3_A6ABC is inlined
#if NONMATCHING
void fn_3_AAC84(f32* x, f32* z) {
    RepFielder* f;
    RepFielder* t;
    s32 idx;
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    f32 d;
    f32 step;
    f32 a;
    f32 b;
    s32 n;

    idx = g_FieldingLogic._0D8;
    if (idx < 0) {
        *x = lbl_3_data_4444[8];
        *z = lbl_3_data_4444[9];
        g_Ball.ballIsLooseInd_unused = 1;
        g_Ball.fielderBeingThrownTo = -1;
        return;
    }
    // inlined fn_3_A6ABC(receiver x, receiver z)
    tx = g_Fielders[idx].pos.x;
    tz = g_Fielders[idx].pos.z;
    f = &g_Fielders[g_Ball.fielderWBallIndex];
    dx = tx - f->pos.x;
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    dz = tz - f->pos.z;
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (lbl_3_rodata_193C == step) {
        step = lbl_3_rodata_1958;
    }
    if (d > lbl_3_rodata_195C) {
        n = (s32)(lbl_3_rodata_1960 * d / step);
    } else if (d > lbl_3_rodata_1964) {
        n = (s32)(d / step);
    } else {
        n = (s32)(lbl_3_rodata_1968 * d / step);
    }
    if (d > lbl_3_rodata_196C) {
        n = (s32)((f32)n * lbl_3_rodata_1970) + 0x1E;
    } else if (d > lbl_3_rodata_1974) {
        n = (s32)((f32)n * lbl_3_rodata_1960) + 0x1E;
    }
    n -= 10;
    t = &g_Fielders[idx];
    if (t->framesToDest < n) {
        *x = t->dest.x;
        *z = t->dest.z;
    } else {
        *x = (f32)n * t->velX + g_Fielders[idx].pos.x;
        *z = (f32)n * t->velZ + g_Fielders[idx].pos.z;
    }
    g_Ball.fielderBeingThrownTo = idx;
}
#endif

// .text:0x000AAFF0 size:0x564 mapped:0x806EA084
void fn_3_AAFF0(void) {
    return;
}

// .text:0x000AB554 size:0x5C mapped:0x806EA5E8
void fn_3_AB554(void) {
    s16 v;
    if (g_FieldingLogic._10D == 0) {
        return;
    }
    v = g_Ball.timeSinceBallPickedUp;
    if (v >= 0 && v < 0x28) {
        if (g_FieldingLogic._0C4 < 0) {
            return;
        }
        g_FieldingLogic._10C = 1;
        g_FieldingLogic._10D = 0;
    } else {
        g_FieldingLogic._10D = 0;
    }
}

// .text:0x000AB5B0 size:0x820 mapped:0x806EA644
void fn_3_AB5B0(void) {
    return;
}

// .text:0x000ABDD0 size:0xC28 mapped:0x806EAE64
void fn_3_ABDD0(void) {
    return;
}


#pragma dont_inline off
