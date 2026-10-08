#include "game/rep_18E8.h"
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

extern u8 g_Ball[];
extern f32 lbl_3_data_4444[];
extern f32 game_atan2(f32, f32);
extern s16 fn_3_9FC1C(f32, f32);
extern u8 g_FieldingLogic[];
extern u8 g_Controls[];
extern u8 g_Practice[];
extern u8 g_Minigame[];
extern u8 g_d_GameSettings[];
typedef struct {
    u8 pad000[0x1F5];
    s8 unk1F5;
    u8 pad1F6[0x268 - 0x1F6];
} FielderT;
typedef struct {
    /*0x000*/ f32 x;
    /*0x004*/ u8 pad004[0x64 - 0x4];
    /*0x064*/ f32 fractionalBasesRan;
    /*0x068*/ f32 percentTowardsNextBase;
    /*0x06C*/ u8 pad06C[0xE6 - 0x6C];
    /*0x0E6*/ s16 unkE6;
    /*0x0E8*/ u8 pad0E8[0x123 - 0xE8];
    /*0x123*/ u8 status;
    /*0x124*/ u8 pad124;
    /*0x125*/ u8 unk125;
    /*0x126*/ u8 unk126;
    /*0x127*/ u8 unk127;
    /*0x128*/ u8 unk128;
    /*0x129*/ u8 pad129[0x137 - 0x129];
    /*0x137*/ u8 unk137;
    /*0x138*/ u8 pad138[0x154 - 0x138];
} RunnerT;
extern RunnerT g_Runners[];
extern u8 g_Fielders[];
extern s32 g_Strikes[];
extern void fn_3_52F4C(s16, f32, f32);
extern u8 g_GameLogic[];
extern u8 g_Scores[];
extern u8 lbl_3_data_4900[];
extern int checkFieldingStat(int, int, int);
extern void playSoundEffect(int);
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
static s32 lbl_3_bss_1838[8];
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

// .text:0x000A009C size:0x1C68 mapped:0x806DF130
void fn_3_A009C(void) {
    return;
}

// .text:0x000A1D04 size:0x9C mapped:0x806E0D98
s32 fn_3_A1D04(void) {
    f32 prev = lbl_3_rodata_1978;
    s32 prevIdx;
    RunnerT* r = &g_Runners[3];
    s32 i;
    for (i = 3; i >= 0; r--, i--) {
        if (r->status == 1) {
            f32 cur = r->fractionalBasesRan;
            f32 d = cur - prev;
            if (d < lbl_3_rodata_193C) {
                d = -d;
            }
            if (d < 0.35f) {
                if (g_Runners[prevIdx].unkE6 < 0) {
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
    u8* f = g_Fielders + *(s16*)(g_Ball + 0x1B78) * 0x268;
    u8* r;
    if (*(f32*)(f + 0x70) > -(lbl_3_rodata_1980 * (f32)(100 - f[0x1CE]) - lbl_3_rodata_196C)) {
        return 0;
    }
    r = (u8*)g_Runners;
    if (!(r[0x51F] == 1 && *(f32*)(r + 0x460) < lbl_3_rodata_1984 && (r[0x533] == 2 || r[0x533] == 1))) {
        r = (u8*)g_Runners;
        if (!(r[0x3CB] == 1 && *(f32*)(r + 0x30C) > lbl_3_rodata_1988 && *(f32*)(r + 0x30C) <= lbl_3_rodata_1984 && r[0x533] == 1 && r[0x3D0] == 0)) {
            return 0;
        }
    }
    r = (u8*)g_Runners;
    if (r[0x277] == 1) {
        if (r[0x27C] != 0) {
            if (*(f32*)(r + 0x1B8) > lbl_3_rodata_198C) {
                return 0;
            }
        } else if (*(s16*)(r + 0x242) == 1 && *(f32*)(r + 0x1B8) <= lbl_3_rodata_1990) {
            return 0;
        }
    }
    *(s16*)(g_FieldingLogic + 0xC4) = 0;
    *(s16*)(g_FieldingLogic + 0xCC) = -1;
    *(s16*)(g_FieldingLogic + 0xDE) = -1;
    return 1;
}

// .text:0x000A1F3C size:0x10C mapped:0x806E0FD0
int fn_3_A1F3C(void) {
    s32 idx;
    s32 i;
    if (g_Ball[0x1BBE] >= 3) {
        return 0;
    }
    idx = lbl_3_bss_1808[3];
    if (idx < 0 || idx > 3) {
        return 0;
    }
    if (lbl_3_bss_1858[idx] >= 7) {
        return 0;
    }
    if (g_Runners[idx].unk128 != 0) {
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
        RunnerT* r = &g_Runners[i];
        if (r->status == 1) {
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
    ball = *(s16*)(g_Ball + 0x1B80);
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
    if (*(s16*)(g_Ball + 0x1B7A) != 3) {
        return 0;
    }
    if (lbl_3_bss_1820 == 0) {
        return 0;
    }
    if (*(f32*)(g_Ball + 0x1A08) < *(f32*)(g_Ball + 0x1A10)) {
        if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A08)) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A10)) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else {
        if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A10)) {
            order[0] = 2;
            order[1] = 3;
            order[2] = 1;
        } else if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A08)) {
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
        if (g_Runners[idx].status == 1 && g_Runners[idx].unk128 == 2 && lbl_3_bss_1858[idx] <= 4 && *(f32*)(g_Ball + 0x1A04 + idx * 4) < lbl_3_rodata_19E8) {
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
    if (*(s16*)(g_Ball + 0x1B7A) != 3) {
        return 0;
    }
    if (lbl_3_bss_1820 == 0) {
        return 0;
    }
    if (*(f32*)(g_Ball + 0x1A08) < *(f32*)(g_Ball + 0x1A10)) {
        if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A08)) {
            order[0] = 2;
            order[1] = 1;
            order[2] = 3;
        } else if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A10)) {
            order[0] = 1;
            order[1] = 2;
            order[2] = 3;
        } else {
            order[0] = 1;
            order[1] = 3;
            order[2] = 2;
        }
    } else {
        if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A10)) {
            order[0] = 2;
            order[1] = 3;
            order[2] = 1;
        } else if (*(f32*)(g_Ball + 0x1A0C) < *(f32*)(g_Ball + 0x1A08)) {
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
        if (g_Runners[idx].status == 1 && g_Runners[idx].unk128 == 2 && lbl_3_bss_1858[idx] <= 4) {
            if (fn_3_A46A0(idx)) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x000A25C4 size:0x398 mapped:0x806E1658
void fn_3_A25C4(void) {
    return;
}

// .text:0x000A295C size:0x210 mapped:0x806E19F0
// 98.4%: only scheduling differs (lfs of rodata_19A0 comes after lwz sel[2], original before stw r29)
int fn_3_A295C(void) {
    f32 c = lbl_3_rodata_19A0;
    RunnerT* r = &g_Runners[lbl_3_bss_1808[2]];
    s32 t;
    if (r->percentTowardsNextBase > c && lbl_3_bss_1858[lbl_3_bss_1808[2]] < 3 && g_Ball[0x1BBE] <= 1 && r->percentTowardsNextBase <= lbl_3_rodata_19AC && (!(r->percentTowardsNextBase >= lbl_3_rodata_19AC) || r->unk137 != 1) && (lbl_3_bss_1824 & 1) && *(s16*)(g_Ball + 0x1B80) > 0x1C0 && *(s16*)(g_Ball + 0x1B80) < 0x300 && r->percentTowardsNextBase <= lbl_3_rodata_19B4 && lbl_3_bss_1858[lbl_3_bss_1808[0]] <= 3 && fn_3_A46A0(lbl_3_bss_1808[0])) {
        return 1;
    }
    if (*(s16*)(g_Ball + 0x1B80) >= 0x380 && *(s16*)(g_Ball + 0x1B80) < 0x640 && g_Ball[0x1BBE] <= 1 && *(f32*)(g_Ball + 8) > lbl_3_rodata_19B8 + *(f32*)g_Ball) {
        t = 1;
    } else {
        t = 0;
    }
    if (t) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 4 && g_Strikes[2] == g_Strikes[3] && r->percentTowardsNextBase > lbl_3_rodata_19A0 && fn_3_A46A0(lbl_3_bss_1808[2])) {
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
    u8* fp;
    idx = lbl_3_bss_1808[3];
    if (g_Runners[idx].percentTowardsNextBase >= 0.25f) {
        if (lbl_3_bss_1858[idx] <= 3 && fn_3_A46A0(idx)) {
            return 1;
        }
        if (lbl_3_bss_1800 & 0x6000) {
            idx = lbl_3_bss_1808[3];
            if (lbl_3_bss_1858[idx] <= 4) {
                fl = *(s16*)(g_FieldingLogic + 0xD6);
                if (fl >= 0) {
                    fp = g_Fielders; fp += fl * 0x268;
                    if (!(*(f32*)(fp + 0xB4) > 4.0f)) {
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
    if ((lbl_3_bss_1824 & 0x100) && *(f32*)(g_Ball + 0x1A10) < 5.0f) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 2 && fn_3_A46A0(lbl_3_bss_1808[2])) {
            return 1;
        }
    }
    if (lbl_3_bss_1818 != 0 && fn_3_A46A0(lbl_3_bss_1808[1])) {
        return 1;
    }
    v = lbl_3_bss_1858[lbl_3_bss_1808[1]];
    if (v <= 4 && g_Strikes[2] == g_Strikes[3]) {
        if (*(f32*)(g_Ball + 0x1A08) < 2.5f && v <= 2 && fn_3_A46A0(lbl_3_bss_1808[0])) {
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
    u8* fp;
    if (lbl_3_bss_1818 != 0 && fn_3_A46A0(lbl_3_bss_1808[1])) {
        return 1;
    }
    if (*(f32*)(g_Ball + 0x1A04) <= *(f32*)(g_Ball + 0x1A0C)) {
        if (lbl_3_bss_1800 & 0x1000) {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 3 && fn_3_A46A0(lbl_3_bss_1808[3])) {
                return 1;
            }
        }
        if (lbl_3_bss_1800 & 0x6000) {
            if (lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 4) {
                fl = *(s16*)(g_FieldingLogic + 0xD6);
                if (fl < 0 || (fp = g_Fielders, fp += fl * 0x268, *(f32*)(fp + 0xB4) > 4.0f)) {
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
    f32 x = *(f32*)g_Ball;
    f32 c = lbl_3_rodata_1998;
    f32 z = *(f32*)(g_Ball + 8);
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
    if (lbl_3_bss_181C <= 1 && *(f32*)(g_Ball + 0x1A10) < lbl_3_rodata_1994) {
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 2 && fn_3_A46A0(lbl_3_bss_1808[2])) {
            return 1;
        }
    }
    if (*(f32*)(g_Ball + 0x1A04) <= *(f32*)(g_Ball + 0x1A0C)) {
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
void fn_3_A3374(void) {
    return;
}

// .text:0x000A36BC size:0x70 mapped:0x806E2750
int fn_3_A36BC(void) {
    f32 z = *(f32*)(g_Ball + 8);
    f32 x;
    if (z < lbl_3_rodata_1A0C && z > lbl_3_rodata_1A10) {
        x = *(f32*)(g_Ball + 0);
        if (z < lbl_3_rodata_198C + x && z > x - lbl_3_rodata_198C && x > g_Runners[0].x) {
            return 1;
        }
    }
    return 0;
}

// .text:0x000A372C size:0x3C mapped:0x806E27C0
int fn_3_A372C(void) {
    f32 x = *(f32*)(g_Ball + 0);
    f32 z = *(f32*)(g_Ball + 8);
    if (z < lbl_3_rodata_1998 + x && z < lbl_3_rodata_1998 - x) {
        return 1;
    }
    return 0;
}

// .text:0x000A3768 size:0x54 mapped:0x806E27FC
int fn_3_A3768(void) {
    s16 v = *(s16*)(g_Ball + 0x1B80);
    if (v >= 0x380 && v < 0x640 && g_Ball[0x1BBE] <= 1 && *(f32*)(g_Ball + 8) > lbl_3_rodata_19B8 + *(f32*)(g_Ball + 0)) {
        return 1;
    }
    return 0;
}

// .text:0x000A37BC size:0x90 mapped:0x806E2850
int fn_3_A37BC(void) {
    u8* b = g_Ball;
    s16 v = *(s16*)(b + 0x1B80);
    if (v < 0x398) {
        return 0;
    }
    if (*(f32*)(b + 0x1A0C) < lbl_3_rodata_1994) {
        return 1;
    }
    if (v < 0x400) {
        if (*(f32*)(b + 8) + *(f32*)(b + 0) > lbl_3_rodata_1998) {
            return 1;
        }
    } else if (*(f32*)(b + 8) - *(f32*)(b + 0) > lbl_3_rodata_1998) {
        return 1;
    }
    return 0;
}

// .text:0x000A384C size:0x2E4 mapped:0x806E28E0
void fn_3_A384C(void) {
    return;
}

// .text:0x000A3B30 size:0xD0 mapped:0x806E2BC4
void fn_3_A3B30(void) {
    s32 diff;
    diff = *(s16*)((u8*)((s16*)(g_Scores + 4)) + *(s32*)(g_GameLogic + 0xC) * 0x26) - *(s16*)((u8*)((s16*)(g_Scores + 4)) + *(s32*)(g_GameLogic + 0x10) * 0x26);
    lbl_3_bss_181C = 0;
    if (*(s32*)g_Scores >= g_Scores[0xAA] && g_Scores[0xAD] != 0 && diff == 0) {
        lbl_3_bss_181C = 3;
        return;
    }
    if (*(s32*)g_Scores >= g_Scores[0xAA] - 1 && diff <= 1 && diff >= -1) {
        lbl_3_bss_181C = 2;
        return;
    }
    if (*(s32*)g_Scores >= g_Scores[0xAA] - 4 && diff <= 1 && diff >= -3) {
        lbl_3_bss_181C = 1;
    }
}

// .text:0x000A3C00 size:0xC0 mapped:0x806E2C94
void fn_3_A3C00(void) {
    s32 i;
    lbl_3_bss_1800 = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_3_bss_1808[i] >= 0) {
            u8 v = g_Runners[lbl_3_bss_1808[i]].unk137;
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
    u8* r = (u8*)&g_Runners + i * 0x154;
    if (r[0x137] == 2) {
        fn_3_52F4C(*(s16*)(g_Ball + 0x1B78), *(f32*)(r + 0), *(f32*)(r + 8));
    } else {
        f32 s = *(f32*)(r + 0x38);
        f32 a = *(f32*)(r + 0x18) * s;
        f32 b = *(f32*)(r + 0x1C) * s;
        fn_3_52F4C(*(s16*)(g_Ball + 0x1B78), 2.0f * a + *(f32*)(r + 0), 2.0f * b + *(f32*)(r + 8));
    }
}

// .text:0x000A41E8 size:0x4B8 mapped:0x806E327C
void fn_3_A41E8(void) {
    return;
}

// .text:0x000A46A0 size:0x370 mapped:0x806E3734
int fn_3_A46A0(s32 i) {
    return 0;
}

// .text:0x000A4A10 size:0x540 mapped:0x806E3AA4
void fn_3_A4A10(void) {
    return;
}

// .text:0x000A4F50 size:0x48C mapped:0x806E3FE4
void fn_3_A4F50(void) {
    return;
}

// .text:0x000A53DC size:0x328 mapped:0x806E4470
void fn_3_A53DC(void) {
    return;
}

// .text:0x000A5704 size:0x448 mapped:0x806E4798
void fn_3_A5704(void) {
    return;
}

// .text:0x000A5B4C size:0x898 mapped:0x806E4BE0
void fn_3_A5B4C(void) {
    return;
}

// .text:0x000A63E4 size:0x404 mapped:0x806E5478
void fn_3_A63E4(void) {
    return;
}

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
void fn_3_A6ABC(void) {
    return;
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
        RunnerT* r = &g_Runners[i];
        if (r->status == 1) {
            s32 b = r->unk125;
            lbl_3_bss_1824 |= 1 << ((s32)r->fractionalBasesRan * 4);
            if (lbl_3_bss_1808[b] < 0 || g_Runners[lbl_3_bss_1808[b]].unkE6 >= 0) {
                lbl_3_bss_1808[b] = i;
            }
        }
    }
}

// .text:0x000A6E98 size:0x1A8 mapped:0x806E5F2C
void fn_3_A6E98(s16 a) {
    u8* p;
    u8* fl;
    u8* r;
    s8 s;
    u8 st;

    p = g_FieldingLogic;
    if (*(s16*)(p + 0xEC) > 0) {
        *(s16*)(p + 0xEC) -= 1;
    }
    if (*(s8*)(g_FieldingLogic + 0x125) >= 0) {
        s = *(s8*)(g_FieldingLogic + 0x125);
        *(s16*)(g_Ball + 0x1B86) = s;
        if (*(s16*)(g_FieldingLogic + 0xCC) == s) {
            *(s16*)(g_FieldingLogic + 0xCC) = -1;
        }
    }
    if (*(s16*)(p + 0xEC) <= 0) {
        g_FieldingLogic[0x112] = 2;
    }
    fl = g_FieldingLogic;
    st = fl[0x111];
    if (st == 2 && fl[0x112] == 1) {
        s16 k = *(s16*)(fl + 0xE8);
        fn_3_52F4C(a, *(f32*)((u8*)g_Runners + k * 0x154), *(f32*)((u8*)&g_Runners[k] + 8));
        if (*(s16*)(g_FieldingLogic + 0xCC) == 9) {
            *(s16*)(g_FieldingLogic + 0xDE) = *(s16*)(fl + 0xE8);
        }
        fn_3_A3CC0();
    } else if (st == 1) {
        s16 i = *(s16*)(g_FieldingLogic + 0xE8);
        if (i >= 0) {
            r = (u8*)g_Runners + i * 0x154;
            if (r[0x123] == 1) {
                if (*(s16*)(r + 0xE6) >= 0) {
                    fl[0x111] = 0;
                } else if (r[0x13A] == 0 && (r[0x137] == 1 || r[0x137] == 3)) {
                    fl[0x111] = 0;
                }
            } else {
                fl[0x111] = 0;
            }
        } else {
            fl[0x111] = 0;
        }
        if (*(s16*)(g_FieldingLogic + 0xDE) >= 0) {
            *(s16*)(g_FieldingLogic + 0xDE) = -1;
            *(s16*)(g_FieldingLogic + 0xCC) = -1;
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
    u8* in;
    u16 b4;
    s16 v;

    in = g_Controls + *(int*)(g_GameLogic + *(int*)(g_GameLogic + 8) * 4 + 0xEC) * 16;
    if (g_d_GameSettings[7] == 6) {
        return;
    }
    if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x144] != 0) {
        return;
    }
    if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0) {
        in = g_Practice + *(int*)(g_GameLogic + 8) * 16;
    } else if (g_d_GameSettings[0x11] != 0) {
        in = g_Controls + *(s8*)(g_Minigame + g_Minigame[0x1922] + 0x18CC) * 16;
    }
    if (!(*(u16*)(in + 4) & 0x100)) {
        g_FieldingLogic[0x145] = 0;
    }
    if (g_FieldingLogic[0x145] != 0) {
        if (g_FieldingLogic[0x145] < 0xFE) {
            g_FieldingLogic[0x145]++;
        } else {
            g_FieldingLogic[0x145] = 0xFF;
        }
    }
    b4 = *(u16*)(in + 4);
    if (!(b4 & 0x100)) {
        return;
    }
    if (*(u16*)(in + 6) & 0x100) {
        if (b4 & 0x40) {
            *(s16*)(g_FieldingLogic + 0xC6) = 6;
        } else {
            v = *(s16*)in;
            if (v >= 0xE00) {
                *(s16*)(g_FieldingLogic + 0xC6) = 1;
            } else if (v >= 0xA00) {
                *(s16*)(g_FieldingLogic + 0xC6) = 0;
            } else if (v >= 0x600) {
                *(s16*)(g_FieldingLogic + 0xC6) = 3;
            } else if (v >= 0x200) {
                *(s16*)(g_FieldingLogic + 0xC6) = 2;
            } else if (v >= 0) {
                *(s16*)(g_FieldingLogic + 0xC6) = 1;
            } else {
                g_FieldingLogic[0x145] = 1;
            }
        }
    } else if (g_FieldingLogic[0x145] >= *(s16*)(lbl_3_data_49DC + 0x50)) {
        if (*(s16*)(g_FieldingLogic + 0xC2) >= 0) {
            return;
        }
        *(s16*)(g_FieldingLogic + 0xC6) = 8;
    }
    *(s16*)(g_FieldingLogic + 0xC8) = 0;
    if (*(s16*)(g_FieldingLogic + 0xC6) == 8) {
        g_FieldingLogic[0x12D] = 1;
        return;
    }
    if (g_FieldingLogic[0x12F] <= lbl_3_data_475C && g_d_GameSettings[0x11] == 0) {
        g_FieldingLogic[0x12D] = 0;
        return;
    }
    g_FieldingLogic[0x12D] = 1;
}

// .text:0x000A7EF8 size:0x17C mapped:0x806E6F8C
void fn_3_A7EF8(void) {
    u8* in;
    s16 v;
    u8 prev;

    in = g_Controls + *(int*)(g_GameLogic + *(int*)(g_GameLogic + 8) * 4 + 0xEC) * 16;
    if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0) {
        in = g_Practice + *(int*)(g_GameLogic + 8) * 16;
    } else if (g_d_GameSettings[0x11] != 0) {
        in = g_Controls + *(s8*)(g_Minigame + g_Minigame[0x1922] + 0x18CC) * 16;
    }
    v = *(s16*)in;
    prev = g_FieldingLogic[0x12E];
    if (v >= 0xE00) {
        g_FieldingLogic[0x12E] = 2;
    } else if (v >= 0xA00) {
        g_FieldingLogic[0x12E] = 3;
    } else if (v >= 0x600) {
        g_FieldingLogic[0x12E] = 4;
    } else if (v >= 0x200) {
        g_FieldingLogic[0x12E] = 1;
    } else if (v >= 0) {
        g_FieldingLogic[0x12E] = 2;
    } else {
        g_FieldingLogic[0x12E] = 0;
    }
    if (g_FieldingLogic[0x12E] == 0) {
        g_FieldingLogic[0x12F] = 0;
        return;
    }
    if (g_FieldingLogic[0x12E] == prev) {
        if (g_FieldingLogic[0x12F] < 0xFE) {
            g_FieldingLogic[0x12F]++;
            return;
        }
        g_FieldingLogic[0x12F] = 0xFF;
        return;
    }
    g_FieldingLogic[0x12F] = 1;
}

// .text:0x000A8074 size:0x2C4 mapped:0x806E7108
void fn_3_A8074(s32 idx) {
    s16 dc;
    s32 sel;
    s16 cc;
    s32 fwd;
    u8* f;
    s16 res;

    s32 d;
    s32 i;
    sel = -1;
    f = g_Fielders + idx * 0x268;
    fwd = 0;
    res = -1;
    dc = *(s16*)(g_FieldingLogic + 0xDC);
    if (dc < 0) {
        *(s16*)(g_FieldingLogic + 0xDE) = -1;
        return;
    }
    cc = *(s16*)(g_FieldingLogic + 0xCC);
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
                if (g_Runners[i].status == 1 && sel == g_Runners[i].unk125 && g_Runners[i].unkE6 < 0 && *(f32*)(f + cc * 4 + 0xA8) > *(f32*)((u8*)&g_Runners[i] + 0x78)) {
                    res = i;
                    break;
                }
            }
        } else {
            for (i = 3; i >= 0; i--) {
                if (g_Runners[i].status == 1 && sel == g_Runners[i].unk125 && g_Runners[i].unkE6 < 0 && *(f32*)(f + cc * 4 + 0xA8) > *(f32*)((u8*)&g_Runners[i] + 0x74)) {
                    res = i;
                    break;
                }
            }
        }
    }
    *(s16*)(g_FieldingLogic + 0xDE) = res;
}

// .text:0x000A8338 size:0x140 mapped:0x806E73CC
void fn_3_A8338(s32 idx) {
    u8* fl;
    s16 sel;
    FielderT* fp;
    fl = g_FieldingLogic;
    sel = *(s16*)(fl + 0xCC);
    fp = &((FielderT*)g_Fielders)[idx];
    if (sel >= 0 && sel <= 3 && fp->unk1F5 == sel) {
        *(s16*)(fl + 0xCC) = -1;
        return;
    }
    if (*(s16*)(g_FieldingLogic + 0xE2) == -1) {
        s16 r = *(s16*)(g_FieldingLogic + 0xDE);
        if (r >= 0 && g_Runners[r].status != 1) {
            *(s16*)(g_FieldingLogic + 0xDE) = -1;
            *(s16*)(fl + 0xCC) = -1;
            return;
        }
        *(s16*)(g_FieldingLogic + 0xE2) = sel;
        fn_3_A8074(idx);
    }
    sel = *(s16*)(fl + 0xCC);
    if (sel >= 0 && sel <= 3) {
        s16 rr = *(s16*)(g_FieldingLogic + 0xDE);
        if (rr == -1) {
            fn_3_52F4C(*(s16*)(g_Ball + 0x1B78), lbl_3_data_4444[sel * 2], lbl_3_data_4444[sel * 2 + 1]);
        } else {
            f32 x = *(f32*)((u8*)g_Runners + rr * 0x154);
            fn_3_52F4C(*(s16*)(g_Ball + 0x1B78), x, *(f32*)((u8*)&g_Runners[rr] + 8));
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
    u8* r;

    idx = *(s16*)(g_FieldingLogic + 0xC4);
    if (idx >= 4 || (s16)idx < 0) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 3) {
        r = (u8*)g_Runners + idx * 0x154;
        if (r[0x123] == 1 && r[0x128] == 2) {
            *out0 = idx;
            goto cur;
        }
    }
    prev = idx == 0 ? 3 : idx - 1;
    r = (u8*)g_Runners + prev * 0x154;
    if (r[0x123] == 1 && *(s16*)(r + 0xEE) == 1) {
        *out0 = prev;
        goto tail;
    }
    return 0;
cur:
    if (r[0x125] == idx) {
        dir = r[0x137];
        if (dir == 3 || dir == 2) {
            *out1 = *(s16*)(r + 0xEC);
        } else if ((dir == 1 && r[0x136] == 3) || (dir == 3 && r[0x136] == 1)) {
            *out1 = *(s16*)(r + 0xEC) + 0x14;
        } else {
            *out1 = *(s16*)(r + 0xEC) + 0x32;
        }
    } else {
        *out1 = *(s16*)(r + 0xEA) + *(s16*)(r + 0xEC) + *(s16*)(r + 0xEC);
    }
    return 1;
tail:
    *out1 = *(s16*)(r + 0xEA);
    return 1;
}

// .text:0x000A85C8 size:0x40C mapped:0x806E765C
void fn_3_A85C8(void) {
    return;
}

// .text:0x000A89D4 size:0x980 mapped:0x806E7A68
void fn_3_A89D4(void) {
    return;
}

// .text:0x000A9354 size:0x3A8 mapped:0x806E83E8
void fn_3_A9354(void) {
    return;
}

// .text:0x000A96FC size:0x288 mapped:0x806E8790
void fn_3_A96FC(void) {
    return;
}

// .text:0x000A9984 size:0x2F0 mapped:0x806E8A18
void fn_3_A9984(void) {
    return;
}

// .text:0x000A9C74 size:0xAC mapped:0x806E8D08
void fn_3_A9C74(int i) {
    u8* f = g_Fielders + i * 0x268;
    int r = checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 5);
    if (f[0x1F8] >= 3) {
        f[0x215] = lbl_3_data_4900[r * 3 + 1];
    } else {
        f[0x215] = lbl_3_data_4900[r * 3];
    }
    if (r != 0 && *(s16*)(g_FieldingLogic + 0xC4) >= 0) {
        playSoundEffect(0x1A8);
    }
}

// .text:0x000A9D20 size:0xD1C mapped:0x806E8DB4
void fn_3_A9D20(void) {
    return;
}

// .text:0x000AAA3C size:0x1BC mapped:0x806E9AD0
void fn_3_AAA3C(int idx) {
    u8* f = g_Fielders + idx * 0x268;
    u8* e;
    s16 ce = *(s16*)(g_FieldingLogic + 0xCE);
    s16 c4;
    if (ce < 0) {
        return;
    }
    c4 = *(s16*)(g_FieldingLogic + 0xC4);
    if (c4 < 0 || c4 > 3) {
        return;
    }
    e = f;
    e += c4 * 4;
    if (*(f32*)(e + 0xA8) > lbl_3_rodata_19F0 && *(s16*)(g_FieldingLogic + 0xDC) < 0) {
        return;
    }
    if (c4 == ce) {
        if (*(s16*)(g_FieldingLogic + 0xE0) >= 0 && *(s16*)(g_FieldingLogic + 0xE0) <= 3) {
            if (*(s16*)(g_FieldingLogic + 0xDC) == g_Runners[*(s16*)(g_FieldingLogic + 0xE0)].unk126 || *(s16*)(g_FieldingLogic + 0xDC) == g_Runners[*(s16*)(g_FieldingLogic + 0xE0)].unk125) {
                g_FieldingLogic[0x119] = 1;
            }
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xCE) == 9) {
        if (*(s16*)(g_FieldingLogic + 0xE0) >= 0 && *(s16*)(g_FieldingLogic + 0xE0) <= 3) {
            u8* r = (u8*)g_Runners + *(s16*)(g_FieldingLogic + 0xE0) * 0x154;
            if (r[0x123] == 1 && *(s16*)(g_FieldingLogic + 0xC4) == r[0x127]) {
                g_FieldingLogic[0x119] = 1;
            }
        }
    }
    if (g_FieldingLogic[0x119] != 0) {
        if (*(s16*)(g_FieldingLogic + 0xC4) >= 0 && *(s16*)(g_FieldingLogic + 0xC4) <= 3) {
            s32 o = *(s16*)(g_FieldingLogic + 0xC4);
            f32 a = game_atan2(lbl_3_data_4444[o*2] - *(f32*)f, lbl_3_data_4444[o*2+1] - *(f32*)(f + 8));
            if (fn_3_9FC1C(a, *(f32*)(f + 0x48)) > 0x40) {
                g_FieldingLogic[0x119] = 0;
            }
        }
    }
}

// .text:0x000AABF8 size:0x8C mapped:0x806E9C8C
int fn_3_AABF8(void) {
    s16 idx = *(s16*)(g_FieldingLogic + 0xD8);
    if (idx == -1) {
        return 0;
    }
    if (g_FieldingLogic[0x105] != 1) {
        return 0;
    }
    if (*(s16*)(g_Fielders + idx * 0x268 + 0x18C) != 5) {
        return 0;
    }
    return !(*(f32*)(g_Fielders + *(s16*)(g_Ball + 0x1B78) * 0x268 + 0xB8) < lbl_3_rodata_19F0);
}

// .text:0x000AAC84 size:0x36C mapped:0x806E9D18
void fn_3_AAC84(void) {
    return;
}

// .text:0x000AAFF0 size:0x564 mapped:0x806EA084
void fn_3_AAFF0(void) {
    return;
}

// .text:0x000AB554 size:0x5C mapped:0x806EA5E8
void fn_3_AB554(void) {
    s16 v;
    if (g_FieldingLogic[0x10D] == 0) {
        return;
    }
    v = *(s16*)(g_Ball + 0x1B6E);
    if (v >= 0 && v < 0x28) {
        if (*(s16*)(g_FieldingLogic + 0xC4) < 0) {
            return;
        }
        g_FieldingLogic[0x10C] = 1;
        g_FieldingLogic[0x10D] = 0;
    } else {
        g_FieldingLogic[0x10D] = 0;
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
