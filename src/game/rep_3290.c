#include "game/rep_3290.h"
#include "header_rep_data.h"
#include "stl/math.h"

extern void* memset(void*, s32, u32);

extern u8 g_Minigame[];
extern s16 lbl_3_data_21654[];
extern u8 lbl_3_data_21694[];
extern u8 lbl_3_data_216B0[];
extern u8 lbl_3_data_216B8[];
extern s32 RandomInt_Game(s32);
extern s32 RandomInt_Game_Range(s32, s32);
extern f32 lbl_3_data_21634[];
extern f32 lbl_3_data_219B8[];
extern s16 lbl_3_data_2167C[];
extern f32 lbl_3_data_21674[];
typedef struct { f32 x, y, z; } Vec3_3290;
typedef struct {
    u8 pad0[0x18];
    Vec3_3290 vel;          // 0x18
    u8 pad24[0xE0 - 0x24];
    f32 pitchChargeUp;      // 0xE0
    u8 padE4[0x126 - 0xE4];
    s16 windupCountdownUntilBallReleased; // 0x126
    s16 pitchWindUpCountDown;             // 0x128
    u8 pad12A[0x15F - 0x12A];
    u8 ChargePitchType;     // 0x15F
    u8 framesAHeldForChargePitches; // 0x160
} PitcherVel_3290;
extern PitcherVel_3290 g_Pitcher;
// Target-board entity at g_Minigame + 0x72C + i * 0x2C (7 of them).
typedef struct {
    Vec3_3290 pos;  // 0x00
    Vec3_3290 home; // 0x0C
    Vec3_3290 vel;  // 0x18
    s16 width;      // 0x24
    s16 timer;      // 0x26
    u8 state;       // 0x28
    u8 type;        // 0x29
    u8 slot;        // 0x2A
    u8 pad2b;
} MgEnt_3290;

extern void fn_3_1500C8(void);
extern f32 lbl_3_data_215C8[];
extern f32 lbl_3_data_21688[];
extern void fn_8004C108(f32*, s32);
extern void fn_3_90064(s32);
#pragma dont_inline on

// .text:0x001133C4 size:0x338 mapped:0x80752458
extern s16 lbl_3_data_5F3C[4];
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

// NONMATCHING 98%: the main loop walker is not shared with the clear loop's base; one extsb is CSE'd
#if NONMATCHING
void fn_3_1133C4(void) {
    u8* e;
    u8 ci;
    s8 i;
    i = 0;
    do {
        g_Minigame[0x1DC4 + i] = 0;
        i++;
    } while (i < 4);
    i = 0;
    do {
        ci = g_Minigame[0x18CC + i];
        if ((s8)ci >= 0 && (s8)ci < 4 && i == *(s8*)(g_Minigame + 0x1904) && g_Minigame[0x18D8 + i] != 0) {
            e = g_Minigame + (s8)ci * 0x10;
            g_Minigame[0x1DC4 + (s8)ci] = 1;
            memset(e + 0x1D7C, 0, 0x10);
            switch (*(s8*)(g_Minigame + 0x1DCF)) {
            case 0:
                fn_3_1136FC();
                g_Minigame[0x1DD0] = 60;
                g_Minigame[0x1DCF] = 1;
                break;
            case 1:
                if (--*(s8*)(g_Minigame + 0x1DD0) <= 0) {
                    switch (g_Minigame[0x1DCE]) {
                    case 0:
                        g_Minigame[0x1DCF] = 2;
                        break;
                    case 1:
                        g_Minigame[0x1DCF] = 4;
                        break;
                    case 2:
                        g_Minigame[0x1DCF] = 6;
                        break;
                    case 3:
                    default:
                        g_Minigame[0x1DCF] = 8;
                        break;
                    }
                }
                break;
            case 2:
                *(u16*)(e + 0x1D82) |= 0x100;
                *(u16*)(e + 0x1D80) |= 0x100;
                g_Minigame[0x1DCF] = 3;
                break;
            case 3:
                if (g_Pitcher.windupCountdownUntilBallReleased < lbl_3_data_5F3C[2]) {
                    g_Minigame[0x1DCF] = 9;
                } else {
                    *(u16*)(e + 0x1D80) |= 0x100;
                }
                break;
            case 4:
                *(u16*)(e + 0x1D82) |= 0x100;
                *(u16*)(e + 0x1D80) |= 0x100;
                g_Minigame[0x1DCF] = 5;
                break;
            case 5:
                *(u16*)(e + 0x1D80) |= 0x100;
                break;
            case 6:
                *(u16*)(e + 0x1D82) |= 0x100;
                *(u16*)(e + 0x1D80) |= 0x100;
                g_Minigame[0x1DCF] = 7;
                break;
            case 7:
                if (g_Pitcher.framesAHeldForChargePitches == 0 &&
                    (s16)LinearInterpolateToNewRange(1.0f - (f32)g_Pitcher.windupCountdownUntilBallReleased /
                                                                (f32)g_Pitcher.pitchWindUpCountDown,
                                                     0.0f, 1.0f, lbl_3_data_21654[0], lbl_3_data_21654[1]) >=
                        *(s16*)(g_Minigame + 0x1DCC)) {
                    g_Minigame[0x1DCF] = 9;
                } else {
                    *(u16*)(e + 0x1D80) |= 0x100;
                }
                break;
            case 8:
                *(u16*)(e + 0x1D82) |= 0x100;
                *(u16*)(e + 0x1D80) |= 0x100;
                g_Minigame[0x1DCF] = 9;
                break;
            case 9:
                break;
            }
        }
        i++;
    } while (i < 4);
}
#endif

// .text:0x001136FC size:0x220 mapped:0x80752790
void fn_3_1136FC(void) {
    u8* p;
    u8 d;
    s8 i;
    s16 lo;
    u8* g;
    s16 hi;
    s8 k;
    g = g_Minigame;
    i = 0;
    lo = 0;
    hi = 0x7FFF;
    p = g;
    k = 0;
    d = g[(s8)g[0x1904] + 0x18DC];
    do {
        u8* e = g + p[0x1A82] * 0x2C;
        lo += *(s16*)(e + 0x750);
        if (e[0x755] == 2) {
            k = i;
            i++;
            break;
        }
        i++;
        p++;
    } while (i < 7);
    if (i < 7) {
        s16 w = *(s16*)(g_Minigame + g_Minigame[0x1A82 + i] * 0x2C + 0x750);
        hi = lo + w - 1;
    }
    if (RandomInt_Game(0x64) < (s8)(lbl_3_data_21694 + d * 7)[k]) {
        s8* q = (s8*)lbl_3_data_216B0 + d * 2;
        s16 r = RandomInt_Game_Range(*(s8*)(lbl_3_data_216B0 + d * 2), q[1]);
        lo += r;
        hi += r;
    }
    if (lo <= lbl_3_data_21654[2] && lbl_3_data_21654[2] <= hi) {
        g[0x1DCE] = 0;
    } else if (lo <= lbl_3_data_21654[3] && lbl_3_data_21654[3] <= hi) {
        g[0x1DCE] = 3;
    } else if (hi >= lbl_3_data_21654[0] && lo <= lbl_3_data_21654[1]) {
        g[0x1DCE] = 2;
        if (lo < lbl_3_data_21654[0]) {
            lo = lbl_3_data_21654[0];
        }
        if (hi > lbl_3_data_21654[1]) {
            hi = lbl_3_data_21654[1];
        }
        *(s16*)(g + 0x1DCC) = RandomInt_Game_Range(lo, hi);
    } else {
        g[0x1DCE] = 1;
    }
    if (g[0x1DCE] == 0 && RandomInt_Game(0x64) < (s8)lbl_3_data_216B8[d]) {
        g[0x1DCE] = 1;
    }
}

// .text:0x0011391C size:0x34 mapped:0x807529B0
void fn_3_11391C(void) {
    memset(g_Minigame + 0x1D7C, 0, 0x78);
}

// .text:0x00113950 size:0xF8 mapped:0x807529E4
void fn_3_113950(void) {
    u8* p6 = g_Minigame;
    s16* p7 = (s16*)g_Minigame;
    f32* p8 = (f32*)g_Minigame;
    f32 g = lbl_3_data_21634[2];
    f32 fl = lbl_3_data_219B8[0xE];
    f32 bn = lbl_3_data_21634[3];
    f32 dm = lbl_3_data_21634[4];
    s16 mx = lbl_3_data_2167C[4];
    s32 i;
    for (i = 0; i < 100; i++, p6++, p7++, p8 += 3) {
        if (p6[0x193A] != 0) {
            p7[0xBE4] = p7[0xBE4] + 1;
            p8[0x334] = p8[0x334] + p8[0x460];
            p8[0x335] = p8[0x335] + p8[0x461];
            p8[0x336] = p8[0x336] + p8[0x462];
            p8[0x461] = p8[0x461] - g;
            if (p8[0x335] < fl) {
                p8[0x335] = fl;
                p8[0x461] = -p8[0x461] * bn;
                p8[0x460] = p8[0x460] * dm;
                p8[0x462] = p8[0x462] * dm;
            }
            if (p7[0xBE4] > mx) {
                p6[0x193A] = 0;
            }
        }
    }
}

// .text:0x00113A48 size:0x2D8 mapped:0x80752ADC
extern u8 g_Ball[];
extern f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax);

void fn_3_113A48(void) {
    u8* p;
    s32 i;
    s32 sum;
    s16 rem;
    if (*(s16*)(g_Ball + 0x1B68) == 1) {
        *(s16*)(g_Minigame + 0x1A74) = lbl_3_data_21654[3];
        if (g_Pitcher.ChargePitchType == 3) {
            *(s16*)(g_Minigame + 0x1A74) = lbl_3_data_21654[2];
        } else if (g_Pitcher.ChargePitchType >= 2) {
            *(s16*)(g_Minigame + 0x1A74) = LinearInterpolateToNewRange(g_Pitcher.pitchChargeUp, 0.0f, 1.0f,
                                                                       lbl_3_data_21654[0], lbl_3_data_21654[1]);
        }
        *(s16*)(g_Minigame + 0x1A76) = *(s16*)(g_Minigame + 0x1A74);
        sum = 0;
        p = g_Minigame;
        i = 0;
        do {
            u8* e = g_Minigame + p[0x1A82] * 0x2C;
            sum += *(s16*)(e + 0x750);
            if (e[0x755] == 2) {
                i++;
                break;
            }
            i++;
            p++;
        } while (i < 7);
        if (*(s16*)(g_Minigame + 0x1A74) >= sum) {
            if (i < 7) {
                if (*(s16*)(g_Minigame + 0x1A74) <= sum + *(s16*)(g_Minigame + g_Minigame[0x1A82 + i] * 0x2C + 0x750) - 1) {
                    g_Minigame[0x1A89] = 1;
                }
            } else {
                g_Minigame[0x1A89] = 1;
            }
        }
        if (g_Minigame[0x1A89] != 1) {
            rem = *(s16*)(g_Minigame + 0x1A74);
            for (i = 0; i < 7; i++) {
                rem -= *(s16*)(g_Minigame + g_Minigame[0x1A82 + i] * 0x2C + 0x750);
                if (rem < 0) {
                    break;
                }
            }
            i--;
            if (i >= 0 && g_Minigame[g_Minigame[0x1A82 + i] * 0x2C + 0x755] == 1) {
                g_Minigame[0x1A8B] = i;
                g_Minigame[0x1A8A] = 1;
            }
        }
    }
}

// .text:0x00113D20 size:0x1A0 mapped:0x80752DB4
void fn_3_113D20(void) {
    u8* p;
    f32* e;
    int i;
    s8 flag;
    f32 a;
    f32 n;
    s8 dir;
    p = g_Minigame;
    flag = 0;
    for (i = 0; i < 7; i++) {
        p = g_Minigame + i * 0x2C;
        e = (f32*)(p + 0x72C);
        a = e[6];
        if (a != 0.0f || e[7] != 0.0f) {
            e[6] = e[7] * cos(a) + e[6];
            n = e[6];
            if (n >= 0.0f) {
                dir = -1;
            } else {
                dir = 1;
            }
            if (a < n) {
                if (a < 0.0f && n >= 0.0f) {
                    flag = 1;
                }
            } else if (a > 0.0f) {
                if (n <= 0.0f) {
                    flag = 1;
                }
            }
            if (flag) {
                e[7] = e[7] * lbl_3_data_21688[2];
                if (fabs(e[7]) < e[8] * lbl_3_data_21688[2]) {
                    e[8] = 0.0f;
                    e[7] = 0.0f;
                    e[6] = 0.0f;
                }
                flag = 0;
            }
            e[7] = dir * e[8] + e[7];
        }
    }
}

// .text:0x00113EC0 size:0x54 mapped:0x80752F54
void fn_3_113EC0(void) {
    g_Pitcher.vel.z = -g_Pitcher.vel.z;
    g_Pitcher.vel.x *= lbl_3_data_21674[0];
    g_Pitcher.vel.y *= lbl_3_data_21674[0];
    g_Minigame[0x1A81] = 1;
    g_Pitcher.vel.z *= lbl_3_data_21674[0];
}

// .text:0x00113F14 size:0x2F0 mapped:0x80752FA8
extern int rand(void);
extern void fn_3_6C854(int team, int kind);
extern u32 lbl_3_data_21648[];
extern Vec3_3290 lbl_3_data_215E0[];

void fn_3_113F14(void) {
    s32 i;
    u8* e;
    s32 j;
    u8 hit;
    u8 cnt;
    f32 ang;
    f32 y;
    if (*(s16*)(g_Ball + 0x1B68) >= 1) {
        hit = g_Minigame[0x1A81];
        y = *(f32*)(g_Ball + 0x8) - *(f32*)(g_Ball + 0x1A28) - lbl_3_data_21674[1];
        for (i = 0; i < 7; i++) {
            e = g_Minigame + i * 0x2C + 0x72C;
            if (e[0x28] == 3 && y <= *(f32*)(e + 0x8) && hit == 0) {
                *(s16*)(e + 0x24) -= *(s16*)(g_Minigame + 0x1A76);
                if (*(s16*)(e + 0x24) <= 0) {
                    *(s16*)(g_Minigame + 0x1A76) = -*(s16*)(e + 0x24);
                    e[0x28] = 4;
                    *(s16*)(g_Minigame + 0x1898 + *(s8*)(g_Minigame + 0x1904) * 2) += lbl_3_data_21654[7 + e[0x29]];
                    cnt = lbl_3_data_21648[e[0x29]];
                    for (j = 0; j < 100; j++) {
                        if (g_Minigame[0x193A + j] == 0) {
                            *(s16*)(g_Minigame + 0x17C8 + j * 2) = 0;
                            g_Minigame[0x193A + j] = 1;
                            *(f32*)(g_Minigame + 0xCD0 + j * 12) = lbl_3_data_215E0[e[0x2A]].x;
                            *(f32*)(g_Minigame + 0xCD4 + j * 12) = lbl_3_data_215E0[e[0x2A]].y;
                            *(f32*)(g_Minigame + 0xCD8 + j * 12) = lbl_3_data_215E0[e[0x2A]].z;
                            ang = 0.017453292f * (rand() % 180);
                            *(f32*)(g_Minigame + 0x1180 + j * 12) = lbl_3_data_21634[1] * (f32)cos(ang);
                            *(f32*)(g_Minigame + 0x1188 + j * 12) = lbl_3_data_21634[1] * (f32)sin(ang);
                            *(f32*)(g_Minigame + 0x1184 + j * 12) = lbl_3_data_21634[0];
                            if (--cnt == 0) {
                                break;
                            }
                        }
                    }
                    fn_3_6C854(((s8*)(g_Minigame + 0x18CC))[*(s8*)(g_Minigame + 0x1904)], 0);
                } else {
                    *(f32*)(e + 0x18) = 0.0f;
                    *(f32*)(e + 0x1C) = lbl_3_data_21688[0];
                    *(f32*)(e + 0x20) = lbl_3_data_21688[1];
                    fn_3_90064(0x2E1);
                    g_Pitcher.vel.z = -g_Pitcher.vel.z;
                    g_Pitcher.vel.x *= lbl_3_data_21674[0];
                    g_Pitcher.vel.y *= lbl_3_data_21674[0];
                    g_Minigame[0x1A81] = 1;
                    g_Pitcher.vel.z *= lbl_3_data_21674[0];
                }
                return;
            }
        }
    }
}

// .text:0x00114204 size:0x180 mapped:0x80753298
void fn_3_114204(void) {
    int cnt;
    int i;
    u8* p;
    f32* e;
    cnt = 0;
    for (i = 0; i < 7; i++) {
        p = g_Minigame + i * 0x2C;
        e = (f32*)(p + 0x72C);
        if (((u8*)e)[0x28] == 2) {
            e[0] += lbl_3_data_215C8[3];
            e[1] += lbl_3_data_215C8[4];
            e[2] += lbl_3_data_215C8[5];
            if (e[2] >= e[5]) {
                e[2] = e[5];
                *(u8*)(e + 10) = 3;
            }
            cnt++;
        }
    }
    if (cnt == 0) {
        for (i = 0; i < 7; i++) {
            p = g_Minigame + i * 0x2C;
            e = (f32*)(p + 0x72C);
            if (((u8*)e)[0x28] == 1) {
                e[0] += lbl_3_data_215C8[0];
                e[1] += lbl_3_data_215C8[1];
                e[2] += lbl_3_data_215C8[2];
                if (e[1] <= e[4]) {
                    e[1] = e[4];
                    *(u8*)(e + 10) = 3;
                    fn_8004C108(e + 3, 1);
                    fn_3_90064(0x2F4);
                }
                cnt++;
            }
        }
        if (cnt == 0) {
            g_Minigame[0x1A7F] = 2;
        }
    }
}

// .text:0x00114384 size:0x634 mapped:0x80753418
extern void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);
extern Vec3_3290 lbl_3_data_21520[14];
extern u8 g_Scores[];

#define MG_ENT_3290(idx) ((MgEnt_3290*)(g_Minigame + (idx) * 0x2C + 0x72C))

// NONMATCHING 95%: saved-register numbering (list base not kept in r28) and one lwzx/lwz in the removal loop
#if NONMATCHING
// Sets up a new round of targets: sorts the order list, places them and picks the special ones.
void fn_3_114384(void) {
    s32 maxNormal;
    u32 i;
    u32 j;
    u32 placed;
    u32 k;
    u32 last;
    s32 m;
    u8 n;
    u8 pick;
    MgEnt_3290* e;
    u8 cand[8];
    u32 counts[3];
    u32 list[7];

    if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
        switch (*(s32*)g_Scores) {
        case 1:
            maxNormal = 1;
            break;
        case 2:
            maxNormal = 2;
            break;
        default:
            maxNormal = 3;
            break;
        }
    } else if (g_Minigame[0x1A2D] < 6) {
        maxNormal = 1;
    } else if (g_Minigame[0x1A2D] < 11) {
        maxNormal = 2;
    } else if (g_Minigame[0x1A2D] < 16) {
        maxNormal = 3;
    } else {
        maxNormal = 4;
    }
    fn_800246D4(fn_3_1149B8, g_Minigame + 0x1A82, g_Minigame + 0x1A82, 1, 7);
    i = 0;
    do {
        MG_ENT_3290(g_Minigame[0x1A82 + i])->slot = i;
        i++;
    } while (i < 7);
    i = 0;
    do {
        counts[i] = 0;
        i++;
    } while (i < 3);
    placed = 0;
    i = 0;
    do {
        e = MG_ENT_3290(g_Minigame[0x1A82 + i]);
        if (e->state == 3) {
            placed++;
            counts[e->type]++;
        }
        i++;
    } while (i < 7);
    i = 0;
    do {
        e = MG_ENT_3290(g_Minigame[0x1A82 + i]);
        e->home.x = lbl_3_data_21520[e->slot].x;
        e->home.y = lbl_3_data_21520[e->slot].y;
        e->home.z = lbl_3_data_21520[e->slot].z;
        if (i < placed) {
            e->state = 2;
        } else {
            e->pos.x = e->home.x;
            e->pos.y = e->home.y;
            e->pos.z = e->home.z;
            e->pos.x += lbl_3_data_21520[e->slot + 7].x;
            e->pos.y += lbl_3_data_21520[e->slot + 7].y;
            e->pos.z += lbl_3_data_21520[e->slot + 7].z;
            e->state = 1;
            e->type = 1;
            counts[e->type]++;
            e->width = lbl_3_data_21654[4 + e->type];
        }
        e->timer = 0;
        e->vel.x = 0.0f;
        e->vel.y = 0.0f;
        e->vel.z = 0.0f;
        i++;
    } while (i < 7);
    if (placed < 7) {
        if (counts[2] == 0) {
            // place one type-2 target, avoiding the last two slots that had one
            n = 0;
            for (j = placed; j < 7; j++) {
                k = 0;
                do {
                    if (j == g_Minigame[0x1A7C + k]) {
                        break;
                    }
                    k++;
                } while (k < 2);
                if (k >= 2) {
                    cand[n++] = j;
                }
            }
            if (n != 0) {
                pick = cand[RandomInt_Game(n)];
            } else {
                pick = RandomInt_Game_Range(placed, 6);
            }
            counts[1]--;
            e = MG_ENT_3290((g_Minigame + 0x1A82)[pick]);
            e->type = 2;
            e->width = lbl_3_data_21654[4 + e->type];
        }
        if (counts[1] > maxNormal) {
            // turn surplus type-1 targets into type 0, never next to a type-2 one
            m = 0;
            for (j = placed; j < 7; j++) {
                if (MG_ENT_3290(g_Minigame[0x1A82 + j])->type != 2 &&
                    (j == 0 || MG_ENT_3290(g_Minigame[0x1A81 + j])->type != 2) &&
                    (j == 6 || maxNormal <= 1 || MG_ENT_3290(g_Minigame[0x1A83 + j])->type != 2)) {
                    list[m] = j;
                    m++;
                }
            }
            if (m != 0) {
                while (counts[1] > maxNormal) {
                    k = RandomInt_Game(m);
                    last = m - 1;
                    counts[1]--;
                    e = MG_ENT_3290(g_Minigame[0x1A82 + list[k]]);
                    e->type = 0;
                    e->width = lbl_3_data_21654[4 + e->type];
                    for (j = k; j < last; j++) {
                        list[j] = list[j + 1];
                    }
                    if (--m <= 0) {
                        break;
                    }
                }
            }
        }
    }
    i = 0;
    do {
        g_Minigame[0x1A7D + i] = g_Minigame[0x1A7C + i];
        i++;
    } while (i < 1);
    i = 0;
    do {
        if (MG_ENT_3290(g_Minigame[0x1A82 + i])->type == 2) {
            g_Minigame[0x1A7C] = i;
            break;
        }
        i++;
    } while (i < 7);
    g_Minigame[0x1A7F] = 1;
    g_Minigame[0x1A80] = 7;
}
#endif

// .text:0x001149B8 size:0x74 mapped:0x80753A4C
s32 fn_3_1149B8(void* a, void* b) {
    MgEnt_3290* ea = (MgEnt_3290*)(g_Minigame + 0x72C + *(u8*)a * 0x2C);
    MgEnt_3290* eb = (MgEnt_3290*)(g_Minigame + 0x72C + *(u8*)b * 0x2C);
    if (ea->state == 3 && eb->state != 3) {
        return -1;
    }
    if (ea->state != 3 && eb->state == 3) {
        return 1;
    }
    return ea->slot - eb->slot;
}

// .text:0x00114A2C size:0x5C mapped:0x80753AC0
void fn_3_114A2C(void) {
    u8 v = g_Minigame[0x1A7F];
    if (v == 0) {
        fn_3_114384();
        fn_3_1500C8();
    } else if (v == 1) {
        fn_3_114204();
    } else if (v == 2) {
        fn_3_113F14();
        fn_3_113D20();
    }
}

// .text:0x00114A88 size:0x538 mapped:0x80753B1C
// g_Fielders entry (stride 0x268): only the fields used here.
typedef struct {
    Vec3_3290 pos;      // 0x00
    u8 pad0C[0x30 - 0x0C];
    f32 velX;           // 0x30
    f32 velZ;           // 0x34
    f32 dirX;           // 0x38
    f32 dirZ;           // 0x3C
    u8 pad40[0x50 - 0x40];
    f32 speed;          // 0x50
    u8 pad54[0x268 - 0x54];
} Fielder_3290;
extern Fielder_3290 g_Fielders[];
typedef struct { f32 x, z; } V2_3290;
extern V2_3290 lbl_3_data_450C;
extern V2_3290 lbl_3_data_21500[];

// g_Minigame +0x1A50: walk-to targets of the 4 fielders (x, z)
typedef struct { u8 pad[0x1A50]; V2_3290 target[4]; } MgTargets_3290;

// NONMATCHING 88%: float constants (incl. the inlined dolsqrtf2's) get pooled behind one base register
#if NONMATCHING
// Moves the fielders to their next positions over lbl_3_data_2167C[1] frames; init snaps them.
void fn_3_114A88(s32 init) {
    s32 i;
    s32 d;
    f32 inv;
    f32 dx;
    f32 dz;
    Fielder_3290* f;
    if (++*(s16*)(g_Minigame + 0x1A70) == 1 || init != 0) {
        if (g_Minigame[0x1A2B] != 3 || g_Minigame[0x1909] != 0) {
            f = &g_Fielders[*(s8*)(g_Minigame + 0x18F8 + *(s8*)(g_Minigame + 0x18E0 + (g_Minigame[0x190C] + 3) % 4))];
            f->pos.x = *(f32*)(g_Minigame + 0x1A48);
            f->pos.z = *(f32*)(g_Minigame + 0x1A4C);
        }
        for (i = 0; i < 4; i++) {
            if (*(s8*)(g_Minigame + 0x18CC + i) >= 0) {
                d = i - g_Minigame[0x190C];
                if (d < 0) {
                    d += g_Minigame[0x1906];
                }
                if (d == 0) {
                    ((MgTargets_3290*)g_Minigame)->target[*(s8*)(g_Minigame + 0x18E0 + i)].x = lbl_3_data_450C.x;
                    ((MgTargets_3290*)g_Minigame)->target[*(s8*)(g_Minigame + 0x18E0 + i)].z = lbl_3_data_450C.z;
                } else {
                    ((MgTargets_3290*)g_Minigame)->target[*(s8*)(g_Minigame + 0x18E0 + i)].x = lbl_3_data_21500[d].x;
                    ((MgTargets_3290*)g_Minigame)->target[*(s8*)(g_Minigame + 0x18E0 + i)].z = lbl_3_data_21500[d].z;
                }
            }
        }
        if (init != 0) {
            for (i = 0; i < g_Minigame[0x1906]; i++) {
                f = &g_Fielders[*(s8*)(g_Minigame + 0x18F8 + i)];
                f->pos.x = ((MgTargets_3290*)g_Minigame)->target[i].x;
                f->pos.y = 0.0f;
                f->pos.z = ((MgTargets_3290*)g_Minigame)->target[i].z;
            }
            return;
        }
    }
    if (*(s16*)(g_Minigame + 0x1A70) >= lbl_3_data_2167C[1]) {
        g_Minigame[0x1A7E] = 0;
        for (i = 0; i < 4; i++) {
            if (*(s8*)(g_Minigame + 0x18CC + i) >= 0) {
                g_Fielders[*(s8*)(g_Minigame + 0x18F8 + i)].speed = 0.0f;
            }
        }
    } else {
        inv = 1.0f / (lbl_3_data_2167C[1] - *(s16*)(g_Minigame + 0x1A70));
        for (i = 0; i < 4; i++) {
            if (*(s8*)(g_Minigame + 0x18CC + i) >= 0) {
                f = &g_Fielders[*(s8*)(g_Minigame + 0x18F8 + i)];
                dx = (((MgTargets_3290*)g_Minigame)->target[i].x - f->pos.x) * inv;
                dz = (((MgTargets_3290*)g_Minigame)->target[i].z - f->pos.z) * inv;
                f->velX = dx;
                f->velZ = dz;
                f->pos.x += dx;
                f->pos.z += dz;
                f->speed = dolsqrtf2(dx * dx + dz * dz);
                if (f->speed > 0.0f) {
                    f->dirX = dx / f->speed;
                    f->dirZ = dx / f->speed; // sic: original divides dx for both
                }
            }
        }
    }
}
#endif


#pragma dont_inline off
