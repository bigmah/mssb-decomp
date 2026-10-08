#include "game/rep_1200.h"
#include "header_rep_data.h"
#include "math.h"

extern u8 g_Pitcher[];
extern u8 g_Minigame[];
extern u8 g_GameLogic[];
extern s32 g_Scores;
extern void fn_3_6EBB4(s32);
extern u8 g_Ball[];
typedef struct {
    int strikes, balls, outs, storedOuts, f10, f14;
    s16 runner[3];
    s16 f1E;
    u8 f20, f21;
} StrikesT;
extern StrikesT g_Strikes;
extern f32 lbl_3_data_446C[];
extern const f32 lbl_3_rodata_1250;
extern const f32 lbl_3_rodata_1258;
extern const f32 lbl_3_rodata_12A8;
extern u8 g_Runners[];
extern void fn_3_5C69C(int);
extern u8 g_d_GameSettings[];
extern u8 g_Practice[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_803CBC3C[];
extern int fn_8001C920(s16);
extern void fn_3_89864(s32 i, s32 d);
typedef struct {
    u8 pad0[0x24];
    s16 charID;
    u8 pad26[0xA0 - 0x26];
} RosterEntry;
extern RosterEntry inMemRoster[2][9];
extern f32 lbl_3_data_5E98[];
extern f32 lbl_3_data_5F90[];

// .text:0x0006F6CC size:0x7C mapped:0x806AE760
int fn_3_6F6CC(void) {
    int i;
    u8* r = g_Runners + 0x154;
    for (i = 0; i < 3; i++) {
        if (r[0x123] == 1 && *(f32*)(r + 0x68) > 0.5f) {
            *(s16*)(g_Pitcher + 0x12E) = 4;
            fn_3_5C69C(0);
            return 1;
        }
        r += 0x154;
    }
    return 0;
}

// .text:0x0006F748 size:0x2E0 mapped:0x806AE7DC
void fn_3_6F748(void) {
    return;
}

// .text:0x0006FA28 size:0x170 mapped:0x806AEABC
extern const f32 lbl_3_rodata_1254;
extern void fn_3_DBD0(f32 z, f32 y, f32 x);
extern f32 lbl_3_data_4388[][5];
// 6FA28 and 6FB98 share this block (inlined). Both are ~55 diff lines: only f-reg/GPR allocation differs
// (orig vy=f4/vx=f6, newY=f2, post-call Ball base r6; table lookup uses r4 base + r0 offset). 6FB98's tail matches.
static inline void ballStep(void) {
    f32* p;
    f32 v;
    f32 vy;
    if (*(s16*)(g_Ball + 0x1B68) < 0x7FFE) {
        *(s16*)(g_Ball + 0x1B68) += 1;
    } else {
        *(s16*)(g_Ball + 0x1B68) = 0x7FFF;
    }
    if (*(s16*)(g_Pitcher + 0x11E) < 0x7FFE) {
        *(s16*)(g_Pitcher + 0x11E) += 1;
    } else {
        *(s16*)(g_Pitcher + 0x11E) = 0x7FFF;
    }
    *(f32*)(g_Ball + 0x3C) = *(f32*)(g_Ball + 0);
    *(f32*)(g_Ball + 0x40) = *(f32*)(g_Ball + 4);
    *(f32*)(g_Ball + 0x44) = *(f32*)(g_Ball + 8);
    *(f32*)(g_Ball + 0x31C) = *(f32*)(g_Ball + 0x31C) - *(f32*)(g_Ball + 0x330);
    fn_3_DBD0(*(f32*)(g_Ball + 8), *(f32*)(g_Ball + 4), *(f32*)(g_Ball + 0));
    *(f32*)(g_Ball + 4) = *(f32*)(g_Ball + 4) + *(f32*)(g_Ball + 0x31C);
    *(f32*)(g_Ball + 0) = *(f32*)(g_Ball + 0) + *(f32*)(g_Ball + 0x318);
    *(f32*)(g_Ball + 8) = *(f32*)(g_Ball + 8) + *(f32*)(g_Ball + 0x320);
    if (*(f32*)(g_Ball + 4) < *(f32*)(g_Ball + 0x1A28)) {
        p = lbl_3_data_4388[g_d_GameSettings[9]];
        vy = *(f32*)(g_Ball + 0x31C);
        v = vy * -(vy * lbl_3_rodata_1250 - p[1]);
        *(f32*)(g_Ball + 0x31C) = v;
        *(f32*)(g_Ball + 0x31C) = -v;
        if (*(f32*)(g_Ball + 0x31C) < lbl_3_rodata_1254) {
            *(f32*)(g_Ball + 0x318) = *(f32*)(g_Ball + 0x318) * p[4];
            *(f32*)(g_Ball + 0x320) = *(f32*)(g_Ball + 0x320) * p[4];
        } else {
            *(f32*)(g_Ball + 0x318) = *(f32*)(g_Ball + 0x318) * p[3];
            *(f32*)(g_Ball + 0x320) = *(f32*)(g_Ball + 0x320) * p[3];
        }
        *(f32*)(g_Ball + 4) = *(f32*)(g_Ball + 0x1A28);
    }
}
void fn_3_6FA28(void) {
    ballStep();
}

// .text:0x0006FB98 size:0x208 mapped:0x806AEC2C
extern u8 g_Stats[];
extern void fn_3_59918(s32, s32);
extern u32 playSoundEffect(s32);
void fn_3_6FB98(void) {
    u8* q;
    ballStep();
    {
    u8* pp = g_Pitcher;
    if (*(s16*)(pp + 0x120) == 10) {
        fn_3_59918(0xB, 0);
        g_Pitcher[0x13E] = 5;
        *(s16*)(pp + 0x120) = 0;
        if (g_GameLogic[0x14C] == 1) {
            q = g_GameLogic + *(s32*)(g_GameLogic + 4);
            if (*(q += 0x14A) < 5) {
                *q += 1;
                if (g_Stats[0x36] == 0) {
                    playSoundEffect(0x19D);
                }
            }
            g_GameLogic[0x14C] = 3;
        }
    }
    }
}

// .text:0x0006FDA0 size:0x224 mapped:0x806AEE34
extern const f32 lbl_3_rodata_1254;
extern const f32 lbl_3_rodata_1278;
extern const f64 lbl_3_rodata_1260;
extern const f64 lbl_3_rodata_1268;
extern const f64 lbl_3_rodata_1270;
static inline f32 sqrt_ext(f32 x) {
    if (x > 0.0f) {
        f64 h = lbl_3_rodata_1260;
        f64 th = lbl_3_rodata_1268;
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = h * guess * (th - guess * guess * xd);
        guess = h * guess * (th - guess * guess * xd);
        guess = h * guess * (th - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (x < lbl_3_rodata_1270)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}
extern s16 fn_3_9FB8C(f32 x, f32 y);
extern void getComponentsFromSAng(s16 ang, f32* x, f32* y);
void fn_3_6FDA0(void) {
    s16 ang;
    f32 a;
    f32 b;
    f32 mag;
    f32 k;
    f32 t;
    s32 off = *(s32*)(g_Ball + 0x1B4C) % 257 - 0x80;
    ang = fn_3_9FB8C(*(f32*)(g_Pitcher + 0x18), -*(f32*)(g_Pitcher + 0x20));
    getComponentsFromSAng(ang + off, &a, &b);
    t = lbl_3_rodata_1254 * (f32)(*(s32*)(g_Ball + 0x1B50) % 10);
    mag = sqrt_ext(*(f32*)(g_Pitcher + 0x18) * *(f32*)(g_Pitcher + 0x18) + *(f32*)(g_Pitcher + 0x20) * *(f32*)(g_Pitcher + 0x20));
    k = lbl_3_rodata_1278 + t;
    *(f32*)(g_Ball + 0x318) = k * (a * mag);
    *(f32*)(g_Ball + 0x320) = k * (b * mag);
    *(f32*)(g_Ball + 0x31C) = lbl_3_rodata_1258;
}

// .text:0x0006FFC4 size:0x2BC mapped:0x806AF058
void fn_3_6FFC4(void) {
    return;
}

// .text:0x00070280 size:0x16C mapped:0x806AF314
extern u8 g_Batter[];
extern u8 lbl_800E8558[];
extern u8 lbl_3_data_76FC[];
extern const f32 lbl_3_rodata_1288;
void fn_3_70280(void) {
    s32 k;
    s32 x;
    s32 y;
    s32 hit = 0;
    if ((g_GameLogic[0x121] != 0xB || g_Practice[0x1DB] != 0) && g_Minigame[0x1A2A] != 2 &&
        *(s16*)(g_Batter + 0x66) <= 0 && g_Pitcher[0x156] == 0) {
        x = (s32)(lbl_3_rodata_1288 * (*(f32*)(g_Pitcher + 0) - *(f32*)(g_Batter + 0)));
        y = (s32)(lbl_3_rodata_1288 * (*(f32*)(g_Pitcher + 8) - *(f32*)(g_Batter + 4)));
        if (g_Batter[0x7B] != 0) {
            x = -x;
        }
        k = lbl_800E8558[*(s16*)(g_Batter + 0x62) * 6 + 2] * 3;
        if (y <= lbl_3_data_76FC[k]) {
            if ((f32)y >= lbl_3_rodata_1258) {
                if (x <= lbl_3_data_76FC[k + 1] && x >= -lbl_3_data_76FC[k + 2]) {
                    hit = 1;
                }
            }
        }
        if (hit != 0) {
            g_Batter[0x93] = 1;
        }
    }
}

// .text:0x000703EC size:0x294 mapped:0x806AF480
extern u8 swingSoundFrame[];
extern u8 g_Stats[];
extern void fn_3_59918(s32, s32);
extern void fn_3_7A154(s32);
extern void fn_3_1DD48(void);
extern u32 playSoundEffect(s32);
void fn_3_703EC(void) {
    u8* p;
    s16 fr = *(s16*)(g_Batter + 0x66);
    if (fr <= 0 || fr >= swingSoundFrame[1] || g_Batter[0x95] != 0) {
        g_Pitcher[0x158] = 1;
        if (g_Pitcher[0x157] != 0) {
            if (++g_Strikes.strikes >= 3) {
                g_Pitcher[0x14E] = 1;
                *(s16*)(g_Pitcher + 0x130) = 0;
                g_Pitcher[0x13E] = 5;
                *(s16*)(g_Pitcher + 0x120) = 0;
                fn_3_59918(0x10, 0);
                if (g_GameLogic[0x14C] == 1) {
                    u8* sc;
                    if ((*(s32*)&g_Scores < ((u8*)&g_Scores)[0xAA] || ((u8*)&g_Scores)[0xAD] == 0 || g_Strikes.outs < 2 ||
                         !(*(s16*)((sc = (u8*)&g_Scores + 4) + *(s32*)(g_GameLogic + 0x10) * 0x26) > *(s16*)(sc + *(s32*)(g_GameLogic + 0xC) * 0x26))) &&
                        (*(s32*)&g_Scores < ((u8*)&g_Scores)[0xAB] || ((u8*)&g_Scores)[0xAD] == 0 || g_Strikes.outs < 2)) {
                        p = (u8*)((u32)g_GameLogic + 0x14A + *(s32*)(g_GameLogic + 8));
                        if (*p < 5) {
                            (*p)++;
                            if (g_Stats[0x36] == 0) {
                                playSoundEffect(0x19D);
                            }
                        }
                    }
                    g_GameLogic[0x14C] = 2;
                }
                if (g_d_GameSettings[7] == 6) {
                    g_Minigame[0x19C6] = g_Minigame[0x1904];
                }
            } else {
                fn_3_59918(8, 0);
            }
        } else {
            if (++g_Strikes.balls >= 4) {
                g_Pitcher[0x14E] = 2;
                *(s16*)(g_Pitcher + 0x130) = 0;
                g_Pitcher[0x13E] = 5;
                *(s16*)(g_Pitcher + 0x120) = 0;
                fn_3_59918(0xA, 0);
                if (g_GameLogic[0x14C] == 1) {
                    p = (u8*)((u32)g_GameLogic + 0x14A + *(s32*)(g_GameLogic + 4));
                    if (*p < 5) {
                        (*p)++;
                        if (g_Stats[0x36] == 0) {
                            playSoundEffect(0x19D);
                        }
                    }
                    g_GameLogic[0x14C] = 3;
                }
            } else {
                fn_3_59918(9, 0);
            }
        }
        fn_3_7A154(0);
        fn_3_1DD48();
    }
}

// .text:0x00070680 size:0x38 mapped:0x806AF714
int fn_3_70680(f32 v) {
    if (v >= *(f32*)(g_Pitcher + 0x7C) && v <= *(f32*)(g_Pitcher + 0x80)) {
        return 1;
    }
    return 0;
}

// .text:0x000706B8 size:0xB0 mapped:0x806AF74C
void fn_3_706B8(int idx) {
    f32 t;
    f32 x;
    f32 y;
    if (g_Minigame[0x1A2A] != 2) {
        t = (*(f32*)(g_Pitcher + 0x84 + idx * 4) - *(f32*)(g_Pitcher + 8)) / (*(f32*)(g_Pitcher + 0x14) - *(f32*)(g_Pitcher + 8));
        x = t * (*(f32*)(g_Pitcher + 0xC) - *(f32*)(g_Pitcher + 0)) + *(f32*)(g_Pitcher + 0);
        y = t * (*(f32*)(g_Pitcher + 0x10) - *(f32*)(g_Pitcher + 4)) + *(f32*)(g_Pitcher + 4);
        *(f32*)(g_Pitcher + 0x54) = x;
        *(f32*)(g_Pitcher + 0x58) = y;
        if (fn_3_70680(x)) {
            g_Pitcher[0x156] = 1;
            g_Pitcher[0x157] = 1;
        }
    }
}

// .text:0x00070768 size:0xD0 mapped:0x806AF7FC
// near-match (13 diff lines): only the trailing lerp differs (orig computes z-pz before z-target and does not fuse px + dx*t into fmadds); ~1000 variants tried
extern const f32 lbl_3_rodata_128C;
extern const f32 lbl_3_rodata_1290;
int fn_3_70768(f32* out, int flag, f32 target) {
    int n = 0;
    f32 z = *(f32*)(g_Pitcher + 8);
    f32 x = *(f32*)(g_Pitcher + 0);
    f32 vx = *(f32*)(g_Pitcher + 0x18);
    f32 vy = *(f32*)(g_Pitcher + 0x1C);
    f32 vz = *(f32*)(g_Pitcher + 0x20);
    f32 add = *(f32*)(g_Pitcher + 0x5C);
    f32 px, pz;
    f32 fl, bo, dr;
    f32 t;
    if (z < target) {
        return 0;
    }
    fl = *(f32*)(g_Pitcher + 0xB0);
    bo = *(f32*)(g_Pitcher + 0xB4);
    dr = *(f32*)(g_Pitcher + 0xBC);
    do {
        px = x;
        pz = z;
        n++;
        if (z <= fl) {
            f32 nvz = vz - vz * bo;
            if (nvz < lbl_3_rodata_128C) {
                vz = nvz;
                vx = vx - vx * bo;
                vy = vy - vy * bo;
            }
        }
        vx *= dr;
        vz *= dr;
        vy *= dr;
        x += vx;
        z += vz;
        if (flag != 0) {
            x += add;
        }
    } while (!(z < target));
    {
        f32 dz = z - pz;
        f32 num = z - target;
        f32 dx = x - px;
        *out = px + dx * (lbl_3_rodata_1290 - num / dz);
    }
    return n;
}

// .text:0x00070838 size:0x17C mapped:0x806AF8CC
extern f32 lbl_3_data_5F5C[];
extern u8 lbl_3_data_5F7C[];
extern int RandomInt_Game_Range(int min, int max);
extern f32 RandomF32_Game_Range(f32 a, f32 b);
void fn_3_70838(void) {
    f32 d;
    f32 dx;
    f32 dy;
    u8 v;
    if (g_Pitcher[0x171] == 0) {
        *(f32*)(g_Pitcher + 0x24) = RandomF32_Game_Range(-lbl_3_data_5F5C[6], lbl_3_data_5F5C[6]);
        *(f32*)(g_Pitcher + 0x28) = lbl_3_data_5F5C[0];
        *(f32*)(g_Pitcher + 0x108) = RandomF32_Game_Range(lbl_3_data_5F5C[4], lbl_3_data_5F5C[5]);
        *(f32*)(g_Pitcher + 0x2C) = lbl_3_rodata_1250 * (*(f32*)(g_Pitcher + 0x108) + *(f32*)(g_Pitcher + 0x2C));
    } else {
        *(f32*)(g_Pitcher + 0x24) = RandomF32_Game_Range(-lbl_3_data_5F5C[7], lbl_3_data_5F5C[7]);
        *(f32*)(g_Pitcher + 0x28) = lbl_3_data_5F5C[0];
        *(f32*)(g_Pitcher + 0x2C) = *(f32*)(g_Pitcher + 0x78);
    }
    v = RandomInt_Game_Range(*(s16*)((u8*)lbl_3_data_5F7C + 8), *(s16*)((u8*)lbl_3_data_5F7C + 0xA));
    dx = *(f32*)(g_Pitcher + 0x24) - *(f32*)(g_Pitcher + 0);
    dy = *(f32*)(g_Pitcher + 0x28) - *(f32*)(g_Pitcher + 4);
    d = *(f32*)(g_Pitcher + 8) - *(f32*)(g_Pitcher + 0x2C);
    g_Pitcher[0x14A] = v;
    g_Pitcher[0x171] = g_Pitcher[0x171] + 1;
    *(f32*)(g_Pitcher + 0x20) = -((f32)v / *(f32*)(g_Pitcher + 0xAC));
    *(s16*)(g_Pitcher + 0x138) = 0;
    *(f32*)(g_Pitcher + 0x18) = -((dx * *(f32*)(g_Pitcher + 0x20)) / d);
    *(f32*)(g_Pitcher + 0x1C) = -((dy * *(f32*)(g_Pitcher + 0x20)) / d);
}

// .text:0x000709B4 size:0x138 mapped:0x806AFA48
extern u8 lbl_3_data_5F50[];
extern const f32 lbl_3_rodata_12A0;
extern const f32 lbl_3_rodata_12A4;
extern void getComponentsFromRad(f32 v, f32* x, f32* y);
void fn_3_709B4(void) {
    f32 c;
    f32 s;
    f32 a;
    f32 t;
    u8 n = g_Pitcher[0x16C] + 1;
    g_Pitcher[0x16C] = n;
    if (n >= g_Pitcher[0x16D]) {
        g_Pitcher[0x16B] = 2;
        return;
    }
    a = (f32)n / (f32)g_Pitcher[0x16D];
    a = a * lbl_3_rodata_12A0;
    a = a + lbl_3_rodata_12A4;
    getComponentsFromRad(a, &c, &s);
    t = lbl_3_rodata_1254 * (f32)lbl_3_data_5F50[g_Pitcher[0x165] * 5 - 0x1F];
    *(f32*)(g_Pitcher + 0xEC) = c * t + t;
    *(f32*)(g_Pitcher + 0xF0) = s * t;
    *(f32*)(g_Pitcher + 0xE8) = lbl_3_rodata_1258;
    *(f32*)(g_Pitcher + 0x100) = a;
}

// .text:0x00070AEC size:0xA8 mapped:0x806AFB80
void fn_3_70AEC(void) {
    f32 t;
    if (g_Pitcher[0x153] != 0) {
        *(f32*)(g_Pitcher + 0xD4) = lbl_3_rodata_1258;
        return;
    }
    t = *(s16*)(g_Ball + 0x1B68) - *(s16*)(g_Pitcher + 0x122) * lbl_3_rodata_1250;
    *(f32*)(g_Pitcher + 0xD4) = *(f32*)(g_Pitcher + 0xCC) - (t * (*(f32*)(g_Pitcher + 0xD0) * t)) / lbl_3_rodata_12A8;
}

// .text:0x00070B94 size:0x360 mapped:0x806AFC28
void fn_3_70B94(void) {
    return;
}

// .text:0x00070EF4 size:0x354 mapped:0x806AFF88
void fn_3_70EF4(void) {
    return;
}

#pragma dont_inline on
// .text:0x00071248 size:0x1520 mapped:0x806B02DC
void fn_3_71248(void) {
    return;
}
#pragma dont_inline reset

// .text:0x00072768 size:0x540 mapped:0x806B17FC
void fn_3_72768(void) {
    return;
}

// .text:0x00072CA8 size:0x464 mapped:0x806B1D3C
void fn_3_72CA8(void) {
    return;
}

// .text:0x0007310C size:0x49C mapped:0x806B21A0
void fn_3_7310C(void) {
    return;
}

// .text:0x000735A8 size:0x124 mapped:0x806B263C
void fn_3_735A8(void) {
    int i;
    u8* r;
    int stop = 0;
    if (g_Pitcher[0x14E] == 3) {
        r = g_Runners + 0x154;
        for (i = 1; i < 4; i++) {
            if (r[0x123] == 1 || r[0x123] == 5) {
                if (stop == 0) {
                    r[0x125] = i;
                    fn_3_89864(i, 1);
                } else {
                    r[0x125] = r[0x124];
                    r[0x126] = (r[0x125] + 1) & 3;
                }
            } else {
                stop = 1;
            }
            r += 0x154;
        }
    } else {
        r = g_Runners + 0x154;
        for (i = 1; i < 4; i++) {
            if (r[0x123] != 1 && r[0x123] != 5) {
                break;
            }
            if (i == r[0x125]) {
                fn_3_89864(i, 1);
            }
            r += 0x154;
        }
    }
    g_Runners[0x125] = 1;
    g_Runners[0x126] = 2;
}

// .text:0x000736CC size:0x4C mapped:0x806B2760
void fn_3_736CC(void) {
    int i;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.runner[i] == -1) {
            g_Strikes.runner[i] = 0;
            return;
        }
    }
}

// .text:0x00073718 size:0x14 mapped:0x806B27AC

void fn_3_73718(void) {
    *(s16*)(g_Ball + 0x1B6A) = -1;
}

// .text:0x0007372C size:0x124 mapped:0x806B27C0
void fn_3_7372C(void) {
    int i;
    u8* r;
    int stop = 0;
    if (g_Pitcher[0x14E] == 3) {
        r = g_Runners + 0x154;
        for (i = 1; i < 4; i++) {
            if (r[0x123] == 1 || r[0x123] == 5) {
                if (stop == 0) {
                    r[0x125] = i;
                    fn_3_89864(i, 1);
                } else {
                    r[0x125] = r[0x124];
                    r[0x126] = (r[0x125] + 1) & 3;
                }
            } else {
                stop = 1;
            }
            r += 0x154;
        }
    } else {
        r = g_Runners + 0x154;
        for (i = 1; i < 4; i++) {
            if (r[0x123] != 1 && r[0x123] != 5) {
                break;
            }
            if (i == r[0x125]) {
                fn_3_89864(i, 1);
            }
            r += 0x154;
        }
    }
    g_Runners[0x125] = 1;
    g_Runners[0x126] = 2;
}

// .text:0x00073850 size:0x58 mapped:0x806B28E4
void fn_3_73850(void) {
    int i;
    g_Strikes.outs = g_Strikes.outs + 1;
    for (i = 0; i < 3; i++) {
        if (g_Strikes.runner[i] == -1) {
            g_Strikes.runner[i] = 0;
            return;
        }
    }
}

// .text:0x000738A8 size:0x540 mapped:0x806B293C
void fn_3_738A8(void) {
    return;
}

// .text:0x00073DE8 size:0x144 mapped:0x806B2E7C
extern void fn_3_155288(void);
extern int fn_3_6F4E8(void);
extern void fn_3_5A6D4(int);
extern void fn_3_7CE90(void);
void fn_3_73DE8(void) {
    if (*(s16*)(g_Pitcher + 0x11E) < 0x7FFE) {
        *(s16*)(g_Pitcher + 0x11E) += 1;
    } else {
        *(s16*)(g_Pitcher + 0x11E) = 0x7FFF;
    }
    if (*(s16*)(g_Ball + 0x1B6A) < 0x7FFE) {
        *(s16*)(g_Ball + 0x1B6A) += 1;
    } else {
        *(s16*)(g_Ball + 0x1B6A) = 0x7FFF;
    }
    if (g_d_GameSettings[7] == 7 && (g_Minigame[0x1A2A] == 1 || g_Minigame[0x1A2A] == 2 || g_Minigame[0x1A2A] == 3)) {
        g_Pitcher[0x158] = 1;
        if (g_Minigame[0x1A2A] == 1) {
            fn_3_155288();
        }
    } else if (g_Pitcher[0x158] == 0) {
        fn_3_703EC();
        return;
    }
    if (fn_3_6F4E8() == 0) {
        if ((g_d_GameSettings[7] != 2 || g_Practice[0x1C8] == 0) && *(s16*)(g_Pitcher + 0x120) > 0x4B) {
            g_GameLogic[0x12A] = 0;
            fn_3_5A6D4(0);
        }
        fn_3_7CE90();
    }
}

// .text:0x00073F2C size:0x80 mapped:0x806B2FC0
void fn_3_73F2C(void) {
    if (*(s16*)(g_Pitcher + 0x11E) < 0x7FFE) {
        *(s16*)(g_Pitcher + 0x11E) += 1;
    } else {
        *(s16*)(g_Pitcher + 0x11E) = 0x7FFF;
    }
    if (*(s16*)(g_Ball + 0x1B68) < 0x7FFE) {
        *(s16*)(g_Ball + 0x1B68) += 1;
    } else {
        *(s16*)(g_Ball + 0x1B68) = 0x7FFF;
    }
    g_Pitcher[0x166] = 0;
    fn_3_71248();
}

// .text:0x00073FAC size:0x124 mapped:0x806B3040
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);
extern f32 lbl_3_data_5EB0[];
extern f32 lbl_3_data_4474[];
extern f32 lbl_3_data_2138C[];
void fn_3_73FAC(void) {
    *(f32*)(g_Pitcher + 0x28) = *(f32*)(g_Batter + 0x50);
    *(f32*)(g_Pitcher + 0x24) = LinearInterpolateToNewRange(*(f32*)(g_Pitcher + 0x8C), lbl_3_data_4474[0], lbl_3_data_4474[1], lbl_3_data_5EB0[0], lbl_3_data_5EB0[1]);
    if (g_Pitcher[0x165] == 3 || g_Pitcher[0x165] == 4) {
        *(f32*)(g_Pitcher + 0x24) = lbl_3_rodata_1258;
    } else if (g_Pitcher[0x165] == 9 || g_Pitcher[0x165] == 0xA) {
        *(f32*)(g_Pitcher + 0x24) = RandomF32_Game_Range(-lbl_3_data_5F5C[3], lbl_3_data_5F5C[3]);
        *(f32*)(g_Pitcher + 0x28) = lbl_3_data_5F5C[0];
        *(f32*)(g_Pitcher + 0x2C) = RandomF32_Game_Range(lbl_3_data_5F5C[1], lbl_3_data_5F5C[2]);
    }
    if (g_Minigame[0x1A2A] == 1 || g_Minigame[0x1A2A] == 3) {
        *(f32*)(g_Pitcher + 0x24) = RandomF32_Game_Range(-lbl_3_data_2138C[g_Minigame[0x1A2B]], lbl_3_data_2138C[g_Minigame[0x1A2B]]);
    }
}

// .text:0x000740D0 size:0x58 mapped:0x806B3164
void fn_3_740D0(void) {
    u8 v = g_Pitcher[0x148];
    g_Pitcher[0x174] = v;
    switch (v) {
    case 1:
        g_Pitcher[0x150] = 0x10;
        break;
    case 2:
        g_Pitcher[0x150] = 0x11;
        break;
    case 3:
        g_Pitcher[0x150] = 0x12;
        break;
    }
}

// .text:0x00074128 size:0x99C mapped:0x806B31BC
void fn_3_74128(void) {
    return;
}

// .text:0x00074AC4 size:0x248 mapped:0x806B3B58
extern u8 g_Controls[];
extern u32 fn_3_107DB4(u8);
void fn_3_74AC4(void) {
    s32 i = *(s32*)(g_GameLogic + 8);
    u8* c = g_Controls + *(s32*)(g_GameLogic + i * 4 + 0xEC) * 16;
    f32 add = lbl_3_rodata_1258;
    if (g_d_GameSettings[7] == 2 && (s8)g_Practice[0x1C2] >= 0) {
        c = g_Practice + i * 16;
    } else {
        u8* m = g_Minigame + 0x18CC;
        if (fn_3_107DB4(m[(s8)g_Minigame[0x1904]]) != 0) {
            c = g_Minigame + (s8)m[(s8)g_Minigame[0x1904]] * 16 + 0x1D7C;
        } else if (g_d_GameSettings[0x11] != 0) {
            c = g_Controls + (s8)m[(s8)g_Minigame[0x1904]] * 16;
        }
    }
    if (*(u16*)(c + 4) & 0x40) {
        g_Pitcher[0x172] = 1;
    }
    if (g_Pitcher[0x172] != 0) {
        if (*(f32*)(g_Pitcher + 0x8C) >= -lbl_3_data_4474[3] && *(f32*)(g_Pitcher + 0x8C) <= lbl_3_data_4474[3]) {
            g_Pitcher[0x172] = 0;
            *(f32*)(g_Pitcher + 0x8C) = lbl_3_rodata_1258;
        } else if (*(f32*)(g_Pitcher + 0x8C) < lbl_3_rodata_1258) {
            *(f32*)(g_Pitcher + 0x8C) += lbl_3_data_4474[3];
        } else {
            *(f32*)(g_Pitcher + 0x8C) -= lbl_3_data_4474[3];
        }
        return;
    }
    if (*(u16*)(c + 4) & 1) {
        add = -lbl_3_data_4474[2];
    } else if (*(u16*)(c + 4) & 2) {
        add = lbl_3_data_4474[2];
    }
    *(f32*)(g_Pitcher + 0x8C) = *(f32*)(g_Pitcher + 0x8C) + add;
    if (*(f32*)(g_Pitcher + 0x8C) < lbl_3_data_4474[0]) {
        *(f32*)(g_Pitcher + 0x8C) = lbl_3_data_4474[0];
    }
    if (*(f32*)(g_Pitcher + 0x8C) > lbl_3_data_4474[1]) {
        *(f32*)(g_Pitcher + 0x8C) = lbl_3_data_4474[1];
    }
}

// .text:0x00074D0C size:0x384 mapped:0x806B3DA0
void fn_3_74D0C(void) {
    return;
}

// .text:0x00075090 size:0x34 mapped:0x806B4124
void fn_3_75090(void) {
    g_Pitcher[0x13E] = 1;
    *(s16*)(g_Pitcher + 0x120) = 0;
    *(f32*)(g_Ball + 0) = *(f32*)(g_Pitcher + 0);
    *(f32*)(g_Ball + 4) = *(f32*)(g_Pitcher + 4);
    *(f32*)(g_Ball + 8) = *(f32*)(g_Pitcher + 8);
}

// .text:0x000750C4 size:0x18 mapped:0x806B4158

void fn_3_750C4(u8 v) {
    g_Pitcher[0x13E] = v;
    *(s16*)(g_Pitcher + 0x120) = 0;
}

// .text:0x000750DC size:0xD8 mapped:0x806B4170
int fn_3_750DC(void) {
    s16 id = inMemRoster[*(s32*)(g_GameLogic + 8)][*(s32*)(g_GameLogic + *(s32*)(g_GameLogic + 0x10) * 0x50 + 0x3C)].charID;
    if (g_d_GameSettings[7] == 2 && g_Practice[0x193] != 4) {
        id = *(s16*)(g_Pitcher + 0x11A);
    }
    if (lbl_3_common_bss_32724[0x9C] == 0) {
        lbl_803CBC3C[1] = 0;
        lbl_3_common_bss_32724[0x9C] = 1;
    }
    if (lbl_3_common_bss_32724[0x9C] == 1 && fn_8001C920(id)) {
        return 1;
    }
    return 0;
}

// .text:0x000751B4 size:0x234 mapped:0x806B4248
void fn_3_751B4(void) {
    return;
}

// .text:0x000753E8 size:0x4C mapped:0x806B447C
void fn_3_753E8(int a) {
    g_Pitcher[0x13E] = 0;
    *(s16*)(g_Pitcher + 0x120) = 0;
    if (a == 0) {
        g_Pitcher[0x159] = 0;
        g_Pitcher[0x15A] = 0;
    }
    *(f32*)(g_Pitcher + 0x8C) = lbl_3_data_446C[0];
    *(f32*)(g_Pitcher + 0x90) = lbl_3_data_446C[1];
    g_Pitcher[0x15E] = 0;
}

// .text:0x00075434 size:0x84 mapped:0x806B44C8
void fn_3_75434(void) {
    fn_3_6EBB4(*(s32*)(g_GameLogic + *(s32*)(g_GameLogic + 0x10) * 0x50 + 0x3C));
    g_Pitcher[0x13E] = 0;
    *(s16*)(g_Pitcher + 0x120) = 0;
    g_Pitcher[0x159] = 0;
    g_Pitcher[0x15A] = 0;
    *(f32*)(g_Pitcher + 0x8C) = lbl_3_data_446C[0];
    *(f32*)(g_Pitcher + 0x90) = lbl_3_data_446C[1];
    g_Pitcher[0x15E] = 0;
    if (g_Scores == 1) {
        g_Pitcher[0x173] = 1;
    }
}

// .text:0x000754B8 size:0xA8 mapped:0x806B454C
void fn_3_754B8(void) {
    f32 h;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    g_Pitcher[0x13E] = 0;
    *(s16*)(g_Pitcher + 0x120) = 0;
    *(f32*)(g_Pitcher + 0xAC) = lbl_3_data_5F90[0];
    *(f32*)(g_Pitcher + 0xBC) = lbl_3_data_5F90[1];
    h = lbl_3_rodata_1250;
    a = lbl_3_data_5E98[0];
    b = lbl_3_data_5E98[1];
    c = lbl_3_data_5E98[2];
    d = lbl_3_data_5E98[3];
    *(f32*)(g_Pitcher + 0x74) = h * (a + b);
    *(f32*)(g_Pitcher + 0x78) = h * (c + d);
    *(f32*)(g_Pitcher + 0x7C) = a;
    *(f32*)(g_Pitcher + 0x80) = b;
    *(f32*)(g_Pitcher + 0x84) = c;
    *(f32*)(g_Pitcher + 0x88) = d;
    *(f32*)(g_Pitcher + 0x8C) = lbl_3_data_446C[0];
    *(f32*)(g_Pitcher + 0x90) = lbl_3_data_446C[1];
    *(s16*)(g_Pitcher + 0x126) = 100;
    *(s16*)(g_Pitcher + 0x128) = 100;
    *(s16*)(g_Pitcher + 0x12A) = 100;
    g_Pitcher[0x173] = 1;
}

// .text:0x00075560 size:0x45C mapped:0x806B45F4
void fn_3_75560(void) {
    return;
}

