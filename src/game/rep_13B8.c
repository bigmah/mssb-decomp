#include "game/rep_13B8.h"
#include "header_rep_data.h"
#include "math.h"
extern f32 lbl_3_data_4A34[];
extern int fn_3_A6810(f32, f32, f32, f32);
extern s16 lbl_3_data_1C88[];
extern u8 lbl_3_data_4B58[];
extern int fn_3_52560(int, f32, f32);
extern f32 lbl_3_data_4444[];
extern s16 lbl_3_data_21904[];
extern u8 lbl_3_data_218BC[];
extern const f32 lbl_3_rodata_1430;
extern const f32 lbl_3_rodata_14BC;
extern const f32 lbl_3_rodata_1438;
extern const f32 lbl_3_rodata_1440;
extern const f32 lbl_3_rodata_144C;
extern const f32 lbl_3_rodata_1450;
extern const f32 lbl_3_rodata_1454;
extern const f32 lbl_3_rodata_1458;
extern const f32 lbl_3_rodata_145C;
extern s16 lbl_3_data_4C54[];
extern s16 lbl_3_data_4B90[];
extern f32 lbl_3_data_4C44[];
typedef struct { f32 x, z; } P2;
typedef struct { u8 b[0x154]; } RunnerT;

extern f32 lbl_3_rodata_1498;
extern const f32 lbl_3_rodata_1408;
extern const f32 lbl_3_rodata_140C;
extern const f32 lbl_3_rodata_1410;
extern const f32 lbl_3_rodata_1414;
typedef struct { f32 x, z; } XZ13B8;
extern f32 lbl_3_data_4444[];
extern XZ13B8 lbl_3_data_4A54[2][13];
extern void running_roundBasePosition(f32 frame, XZ13B8* outPos, XZ13B8* points, int count);
extern const f64 lbl_3_rodata_1488;
extern const f64 lbl_3_rodata_14E8;
extern const f32 lbl_3_rodata_14F0;
extern const f32 lbl_3_rodata_14F4;
extern f32 fn_3_9FEA8(f32);
extern const f32 lbl_3_rodata_143C;
extern f32 lbl_3_data_4B44;
extern s16 lbl_3_data_4B48[];
extern const f32 lbl_3_rodata_1470;
extern const f32 lbl_3_rodata_1484;
extern u8 lbl_3_data_7760[];
extern const f32 lbl_3_rodata_1490;

#pragma dont_inline on

extern u8 inMemRoster[];
extern u8 g_GameLogic[];

extern u8 g_Scores[];

extern u8 g_Batter[];
extern u8 g_Runners[];
extern u8 g_Ball[];
extern u8 g_Fielders[];
extern u8 g_d_GameSettings[];
extern u8 lbl_3_common_bss_37400[];
extern void fn_3_161588(int, s16);
extern u8 g_FieldingLogic[];
extern u8 g_UnkSound_32718[];
extern const f32 lbl_3_rodata_14F8;
extern void fn_3_59918(s32, s32);
extern void fn_3_5C74C(s32);
extern void fn_3_5D094(s32);
extern void fn_3_6D964(int, int);
extern int g_Strikes[];
extern u8 g_Practice[];
extern u8 g_Controls[];
extern u32 fn_3_107DF8(u8);
extern u8 g_AiLogic[];
extern s16 lbl_3_data_1C58[];
extern int RandomInt_Game(int);
extern u8 g_Pitcher[];
extern u8 g_RunningLogic[];
extern u8 g_Minigame[];

// .text:0x0007D79C size:0x184 mapped:0x806BC830
void fn_3_7D79C(int i) {
    u8* r = g_Runners + i * 0x154;
    if (*(s16*)(r + 0x108) <= 0) {
        XZ13B8 pos;
        int idx;
        int count;
        f32 dist = *(f32*)(r + 0x64);
        f32 frame = *(f32*)(r + 0x68);
        if (dist < lbl_3_rodata_1408) {
            idx = 0;
            count = 4;
        } else if (dist < lbl_3_rodata_140C) {
            idx = 3;
            count = 4;
        } else if (dist < lbl_3_rodata_1410) {
            idx = 6;
            count = 4;
        } else if (g_GameLogic[0x121] == 6) {
            idx = 9;
            count = 4;
        } else {
            idx = 9;
            count = 3;
        }
        running_roundBasePosition(frame, &pos, &lbl_3_data_4A54[g_GameLogic[0x121] == 6][idx], count);
        *(f32*)(r + 0x0) = pos.x;
        *(f32*)(r + 0x8) = pos.z;
        *(f32*)(r + 0x4) = lbl_3_rodata_1414;
        *(f32*)(r + 0x18) = lbl_3_rodata_1414;
        *(f32*)(r + 0x20) = lbl_3_rodata_1414;
    }
    if (*(s16*)(r + 0x108) < 0x7FFE) {
        *(s16*)(r + 0x108) += 1;
    } else {
        *(s16*)(r + 0x108) = 0x7FFF;
    }
    if (*(s16*)(r + 0x108) >= lbl_3_data_21904[2]) {
        g_Minigame[*(s8*)(g_Minigame + i + 0x18FC) + 0x1B15] = 0;
    }
}

// .text:0x0007D920 size:0xBC mapped:0x806BC9B4
void fn_3_7D920(int i) {
    u8* r = g_Runners + i * 0x154;
    s8 k = *(s8*)(g_Minigame + i + 0x18FC);
    if (g_Minigame[k + 0x1B15] == 2) {
        if (g_Minigame[0x1B19] == 0) {
            g_Minigame[k + 0x1B15] = 3;
            *(s16*)(r + 0x108) = 0;
        }
        return;
    }
    if (*(s16*)(r + 0x108) < lbl_3_data_21904[1]) {
        *(f32*)(r + 0x0) += *(f32*)(r + 0x18);
        *(f32*)(r + 0x8) += *(f32*)(r + 0x20);
    } else {
        g_Minigame[k + 0x1B15] = 2;
    }
    if (*(s16*)(r + 0x108) < 0x7FFE) {
        *(s16*)(r + 0x108) += 1;
    } else {
        *(s16*)(r + 0x108) = 0x7FFF;
    }
}

extern const f64 lbl_3_rodata_1418;
extern const f64 lbl_3_rodata_1420;
extern const f64 lbl_3_rodata_1428;
extern const f32 lbl_3_rodata_1414;

// .text:0x0007D9DC size:0x154 mapped:0x806BCA70
static inline float sqrt13B8(float x) {
    if (x > lbl_3_rodata_1414) {
        double half = lbl_3_rodata_1418;
        double three = lbl_3_rodata_1420;
        double xd = (double)x;
        double guess = __frsqrte(xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        guess = half * guess * (three - guess * guess * xd);
        return (float)(xd * guess);
    } else if (x < lbl_3_rodata_1428)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}


void fn_3_7D9DC(int i) {
    u8* r = g_Runners + i * 0x154;
    f32 m = sqrt13B8(*(f32*)(g_Minigame + 0x1AEC) * *(f32*)(g_Minigame + 0x1AEC) + *(f32*)(g_Minigame + 0x1AF4) * *(f32*)(g_Minigame + 0x1AF4));
    f32 k = ((f32*)lbl_3_data_218BC)[7];
    *(f32*)(r + 0x18) = k * (*(f32*)(g_Minigame + 0x1AEC) / m);
    *(f32*)(r + 0x20) = k * (*(f32*)(g_Minigame + 0x1AF4) / m);
    *(s16*)(r + 0x108) = 0;
}

// .text:0x0007DB30 size:0x1F4 mapped:0x806BCBC4
void fn_3_7DB30(int i) {
    u8* r;
    u8 k;
    u8* c;
    u8 t;
    u16 b;
    k = g_Minigame[i + 0x18FC];
    c = g_Controls + (s8)k * 16;
    r = g_Runners + i * 0x154;
    if (fn_3_107DF8(k)) {
        c = g_Minigame + (s8)g_Minigame[i + 0x18FC] * 16 + 0x1D7C;
    }
    t = r[0x137];
    if (t == 3) {
        u8 u = r[0x136];
        if (u == 2 || u == 1) {
            b = *(u16*)(c + 6);
            if (b & 0x400) {
                if (*(s16*)(r + 0xE0) >= 0) {
                    r[0x135] = 3;
                }
            } else if (b & 0x800) {
                if (*(s16*)(r + 0xE0) >= 0) {
                    r[0x135] = 1;
                }
            }
        } else if (*(u16*)(c + 6) & 0x800) {
            if (*(s16*)(r + 0xE0) >= 0) {
                r[0x135] = 2;
            }
        }
    } else if (t == 1) {
        u8 u = r[0x136];
        if (u == 2 || u == 3) {
            b = *(u16*)(c + 6);
            if (b & 0x400) {
                if (*(s16*)(r + 0xE0) >= 0) {
                    r[0x135] = 3;
                }
            } else if (b & 0x800) {
                if (*(s16*)(r + 0xE0) >= 0) {
                    r[0x135] = 1;
                }
            }
        } else if (*(u16*)(c + 6) & 0x400) {
            if (*(s16*)(r + 0xE0) >= 0) {
                r[0x135] = 2;
            }
        }
    } else {
        b = *(u16*)(c + 4);
        if (b & 0x800) {
            if (*(s16*)(r + 0xE0) >= 0) {
                r[0x135] = 1;
            }
        } else if (b & 0x400) {
            if (*(s16*)(r + 0xE0) >= 0) {
                r[0x135] = 3;
            }
        }
    }
    if (*(u16*)(c + 6) & 0xF00) {
        r[0x149] = 1;
    }
}

// .text:0x0007DD24 size:0x48 mapped:0x806BCDB8
void fn_3_7DD24(int a) {
    if (g_GameLogic[0x11E] == 2 && g_Minigame[0x190B] == 0) {
        fn_3_7DB30(a);
    }
}

// .text:0x0007DD6C size:0x550 mapped:0x806BCE00
void fn_3_7DD6C(void) {
    return;
}

// .text:0x0007E2BC size:0x7AC mapped:0x806BD350
void fn_3_7E2BC(void) {
    return;
}

// .text:0x0007EA68 size:0x16C mapped:0x806BDAFC
void fn_3_7EA68(void) {
    u8* c = g_Controls + *(s32*)(g_GameLogic + *(s32*)(g_GameLogic + 4) * 4 + 0xEC) * 16;
    if (g_Pitcher[0x13E] == 1 || g_Pitcher[0x13E] == 2 || g_Pitcher[0x13E] == 3) {
        s16 v;
        if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0) {
            c = g_Practice + *(s32*)(g_GameLogic + 4) * 16;
        }
        if (!(*(u16*)(c + 6) & 0x800)) {
            return;
        }
        v = *(s16*)c;
        if (v < 0) {
            int k;
            for (k = 1; k < 4; k++) {
                if (g_Runners[k * 0x154 + 0x123] != 0 && g_Runners[k * 0x154 + 0x14E] == 0) {
                    g_Runners[k * 0x154 + 0x14E] = 1;
                }
            }
        } else {
            if (v >= 0x1C0 && v <= 0x640) {
                g_Runners[0x2A2] = 1;
            }
            if (*(s16*)c >= 0x5C0 && *(s16*)c <= 0xA40) {
                g_Runners[0x3F6] = 1;
            }
            if (*(s16*)c >= 0x9C0 && *(s16*)c <= 0xE40) {
                g_Runners[0x54A] = 1;
            }
        }
    }
}

// .text:0x0007EBD4 size:0x128 mapped:0x806BDC68
void fn_3_7EBD4(int i) {
    u8* r = g_Runners + i * 0x154;
    if (g_GameLogic[0x11E] == 1) {
        return;
    }
    if (r[0x123] == 2) {
        if (r[0x145] != 0) {
            return;
        }
        if (r[0x13A] != 0) {
            if (r[0x13C] == 3) {
                r[0x13A] = 0;
                r[0x13C] = 0;
            } else {
                return;
            }
        }
        if (*(s16*)(r + 0xEE) == 2) {
            u8 c = r[0x140];
            if (c != 0) {
                if (c == 3) {
                    r[0x13E] = 0;
                    r[0x140] = 0;
                } else {
                    return;
                }
            } else {
                if (!(*(f32*)(r + 0x68) < lbl_3_rodata_1430)) {
                    if (r[0x137] != 2) {
                        return;
                    }
                }
            }
        }
        r[0x145] = 1;
        r[0x146] = 0;
        r[0x140] = 0;
    } else {
        if (g_Strikes[2] < 3) {
            return;
        }
        if (r[0x13A] != 0) {
            if (r[0x13C] == 3) {
                r[0x13A] = 0;
                r[0x13C] = 0;
            } else {
                return;
            }
        }
        r[0x145] = 1;
        r[0x146] = 0;
    }
}

// .text:0x0007ECFC size:0x5DC mapped:0x806BDD90
void fn_3_7ECFC(int i) {
    return;
}

// .text:0x0007F2D8 size:0x1BC mapped:0x806BE36C
int fn_3_7F2D8(void) {
    u8* r = g_Runners;
    f32 dist;
    s16 s;
    if (r[0x13A] == 0 && r[0x13F] == 0) {
        if (r[0x140] != 0) {
            return 1;
        }
        s = *(s16*)(g_Ball + 0x1B7A);
        if (s != 3) {
            dist = *(f32*)(r + 0x64);
            if (dist < lbl_3_rodata_1450) {
                goto fail;
            }
            if (s == 0 && r[0x277] == 1) {
                if (*(s16*)(r + 0x23A) == 1) {
                    goto fail;
                }
                if (g_Ball[0x1BBF] <= 2 && *(f32*)(r + 0x1B8) < lbl_3_rodata_1454) {
                    goto fail;
                }
            }
            if (s == 0 && *(f32*)(g_Ball + 0x19D4) > lbl_3_rodata_1438) {
                goto set;
            }
            if (g_Ball[0x1BBE] <= 1) {
                goto fail;
            }
            if (g_Ball[0x1BBE] <= 2 && *(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_1458) {
                goto fail;
            }
            s = *(s16*)(g_Ball + 0x1B78);
            if (s >= 0 && *(f32*)(g_Ball + 0x1A08) < lbl_3_rodata_144C) {
                goto fail;
            }
            if (s == 8 && dist <= lbl_3_rodata_145C) {
                goto fail;
            }
            if (*(s16*)(g_FieldingLogic + 0xC4) == 1 && g_Ball[0x1BC9] == 2 && *(s16*)(r + 0xEA) + 0x1E > *(s16*)(g_Ball + 0x1B62)) {
                goto fail;
            }
set:
            r[0x13F] = 1;
        }
    }
    if (r[0x13E] == 1) {
        r[0x13E] = 0;
    }
    return 0;
fail:
    r[0x13E] = 1;
    if (*(f32*)(r + 0x64) > lbl_3_rodata_1430) {
        r[0x140] = 1;
    }
    return 1;
}

// .text:0x0007F494 size:0x530 mapped:0x806BE528
void fn_3_7F494(int i) {
    return;
}

// .text:0x0007F9C4 size:0xB4 mapped:0x806BEA58
void fn_3_7F9C4(int i) {
    u8* r = g_Runners + i * 0x154;
    if (r[0x145] != 0) {
        r[0x13E] = 0;
        r[0x13A] = 0;
        return;
    }
    fn_3_7ECFC(i);
    fn_3_7F494(i);
    if (g_GameLogic[0x121] != 6) {
        if (i == 0 && r[0x126] == 1) {
            fn_3_7F2D8();
        } else if (r[0x13E] == 1) {
            r[0x13E] = 0;
        }
        fn_3_7EBD4(i);
    }
}

// .text:0x0007FA78 size:0x318 mapped:0x806BEB0C
int fn_3_7FA78(int i) {
    u8* r = g_Runners + i * 0x154;
    u8 gm;
    u8 fl;
    s16 b66;
    s16 f0;
    s16 f2;
    gm = g_GameLogic[0x121];
    if (gm == 6) {
        if (g_Minigame[0x190B] != 0) {
            return 2;
        }
        if (g_Minigame[0x1B19] == 2 || g_Minigame[0x1B19] == 3) {
            return 2;
        }
        return 0;
    }
    if (gm != 0xE) {
        b66 = *(s16*)(g_Ball + 0x1B66);
        if (b66 <= 0) {
            return 0;
        }
        fl = g_FieldingLogic[0x107];
        if (fl == 1) {
            if (i != 0 && r[0x137] == 2 && r[0x135] == 0 && *(s16*)(g_Ball + 0x1B70) == lbl_3_data_4C54[4]) {
                return 3;
            }
        } else if (fl == 2 && i != 0 && r[0x137] == 2 && r[0x135] == 0 && *(s16*)(g_Ball + 0x1B70) == lbl_3_data_4C54[4]) {
            return 3;
        }
        if (i == 0) {
            if (*(f32*)(r + 0x64) < lbl_3_rodata_1408 && *(s16*)(r + 0xEE) == 1 && g_FieldingLogic[0x108] == 0 && fl == 0) {
                return 1;
            }
        } else if (r[0x133] == 1) {
            return 1;
        }
        if (g_Ball[0x1BD1] == 1) {
            return 1;
        }
        if (b66 == 5) {
            return 1;
        }
    }
    f0 = *(s16*)(r + 0xF0);
    if (f0 & 4) {
        u8 a = r[0x137];
        if (a == 1) {
            return 2;
        }
        if (r[0x136] == 1 && a == 2) {
            return 2;
        }
    } else if (f0 & 1) {
        if ((r[0x13E] != 1 || r[0x140] == 0) && r[0x137] == 1) {
            return 2;
        }
        if (r[0x136] == 1) {
            return 2;
        }
    } else if (f0 & 2) {
        if (r[0x137] == 3) {
            return 2;
        }
        if (r[0x136] == 3) {
            return 2;
        }
    } else {
        f2 = *(s16*)(r + 0xF2);
        if (f2 & 4) {
            if ((f0 & 1) == 0 && *(s16*)(g_Ball + 0x1B66) > 0 && (r[0x137] == 2 || r[0x136] == 2) && r[0x128] == 0) {
                return 1;
            }
        } else if ((f2 & 8) && (f0 & 2) == 0 && (r[0x137] == 2 || r[0x136] == 2)) {
            return 3;
        }
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 3 && r[0x128] == 2) {
        return 3;
    }
    return 0;
}

// .text:0x0007FD90 size:0x118 mapped:0x806BEE24
void fn_3_7FD90(int i) {
    u8* r = g_Runners + i * 0x154;
    int v;
    if ((r[0x145] == 0 || r[0x146] == 0) && r[0x13A] == 0) {
        if (*(s16*)(r + 0x112) >= lbl_3_data_4C54[3] || (r[0x137] != 1 && r[0x137] != 3)) {
            u8 s = r[0x135];
            if (s != 0) {
                if (g_GameLogic[0x121] == 6) {
                    if (r[0x123] == 1) {
                        r[0x136] = s;
                    }
                } else {
                    if ((i != 0 || r[0x126] != 1) && r[0x123] == 1) {
                        r[0x136] = s;
                    }
                    if (r[0x136] == 3 && r[0x128] != 3 && *(s16*)(r + 0xE6) >= 0) {
                        r[0x136] = 0;
                    }
                }
            }
        }
        v = ((int (*)(void))fn_3_7FA78)();
        if (v != 0) {
            r[0x136] = v;
        }
    }
}

// .text:0x0007FEA8 size:0x2C mapped:0x806BEF3C
void fn_3_7FEA8(s32 i, s32 v) {
    u8* r = g_Runners + i * 0x154;
    if (*(s16*)(r + 0xE0) < 0) {
        return;
    }
    if (v == 0) {
        return;
    }
    r[0x135] = v;
}

// .text:0x0007FED4 size:0xFC mapped:0x806BEF68
void fn_3_7FED4(f32* out, f32 dist, f32 frame) {
    XZ13B8 pos;
    int idx;
    int count;
    if (dist < lbl_3_rodata_1408) {
        idx = 0;
        count = 4;
    } else if (dist < lbl_3_rodata_140C) {
        idx = 3;
        count = 4;
    } else if (dist < lbl_3_rodata_1410) {
        idx = 6;
        count = 4;
    } else if (g_GameLogic[0x121] == 6) {
        idx = 9;
        count = 4;
    } else {
        idx = 9;
        count = 3;
    }
    running_roundBasePosition(frame, &pos, &lbl_3_data_4A54[g_GameLogic[0x121] == 6][idx], count);
    out[0] = pos.x;
    out[2] = pos.z;
    out[1] = lbl_3_rodata_1414;
}

// .text:0x0007FFD0 size:0x58 mapped:0x806BF064
#pragma fp_contract off
void fn_3_7FFD0(f32* out, int a, int b, f32 t) {
    f32* T = lbl_3_data_4A34;
    f32 d[2];
    d[0] = T[b * 2] - T[a * 2];
    d[1] = T[b * 2 + 1] - T[a * 2 + 1];
    d[0] *= t;
    d[1] *= t;
    out[0] = d[0] + T[a * 2];
    out[2] = d[1] + T[a * 2 + 1];
    out[1] = 0.0f;
}
#pragma fp_contract on

// .text:0x00080028 size:0x109C mapped:0x806BF0BC
void fn_3_80028(void) {
    return;
}

// .text:0x000810C4 size:0xCC mapped:0x806C0158
void fn_3_810C4(int idx, int base) {
    RunnerT* r = &((RunnerT*)g_Runners)[idx];
    int next = (base + 1) & 3;
    if (g_GameLogic[0x121] == 6) {
        u8* e = lbl_3_data_4B58;
        e += base * 0xC;
        *(f32*)(r->b + 0x30) = *(f32*)(e + 8);
        *(f32*)(r->b + 0x68) = 0.0f;
    } else {
        *(f32*)(r->b + 0x68) = *(f32*)(r->b + 0x54);
    }
    *(f32*)(r->b + 0x64) = *(f32*)(r->b + 0x68) + base;
    *(s16*)(r->b + 0xE6) = base;
    *(f32*)(r->b + 0x3C) = lbl_3_data_4A34[base * 2];
    *(f32*)(r->b + 0x44) = lbl_3_data_4A34[base * 2 + 1];
    *(f32*)(r->b + 0x48) = lbl_3_data_4A34[next * 2];
    *(f32*)(r->b + 0x50) = lbl_3_data_4A34[next * 2 + 1];
}

// .text:0x00081190 size:0x928 mapped:0x806C0224
void fn_3_81190(void) {
    return;
}

// .text:0x00081AB8 size:0x34 mapped:0x806C0B4C
void fn_3_81AB8(int i) {
    u8* r = g_Runners + i * 0x154;
    r[0x137] = 2;
    r[0x136] = 2;
    *(f32*)(r + 0x84) = lbl_3_rodata_1498;
    *(f32*)(r + 0xA4) = lbl_3_rodata_1498;
    *(f32*)(r + 0xB0) = lbl_3_rodata_1498;
}

// .text:0x00081AEC size:0xDC mapped:0x806C0B80
void fn_3_81AEC(int i) {
    u8* r = g_Runners + i * 0x154;
    s16 n;
    f32 v;
    if (*(s16*)(r + 0x10C) < 0x7FFE) {
        *(s16*)(r + 0x10C) = *(s16*)(r + 0x10C) + 1;
    } else {
        *(s16*)(r + 0x10C) = 0x7FFF;
    }
    n = *(s16*)(r + 0x10E);
    if (n <= 0) {
        r[0x133] = 2;
        *(f32*)(r + 0xA4) = lbl_3_rodata_1498;
    } else {
        v = *(f32*)(r + 0xBC) + *(f32*)(r + 0x54);
        v -= *(f32*)(r + 0x68);
        v /= (f32)n;
        *(f32*)(r + 0xA4) = v;
        *(f32*)(r + 0x68) = *(f32*)(r + 0x68) + v;
        *(f32*)(r + 0x64) = (f32)r[0x124] + *(f32*)(r + 0x68);
        *(s16*)(r + 0x10E) = *(s16*)(r + 0x10E) - 1;
    }
}

// .text:0x00081BC8 size:0x2E4 mapped:0x806C0C5C
// 95%: only first block differs - orig hoists the 1468/4B44 const loads and stw 0x4330 above the sth 0x106 store
int fn_3_81BC8(int i) {
    u8* r = g_Runners + i * 0x154;
    if (r[0x135] == 1) {
        r[0x136] = 1;
        r[0x142] = 0;
        return 0;
    }
    if (r[0x142] == 1) {
        s16 t;
        r[0x142] = 2;
        *(s16*)(r + 0x104) = 0;
        *(s16*)(r + 0x106) = lbl_3_data_4B48[0];
        r[0x137] = 5;
        t = *(s16*)(r + 0x106);
        *(f32*)(r + 0xB4) = lbl_3_data_4B44 / (f32)((t + 1) * (t / 2));
    }
    if (r[0x142] == 2) {
        s16 t;
        *(s16*)(r + 0x104) = *(s16*)(r + 0x104) + 1;
        *(s16*)(r + 0x106) = *(s16*)(r + 0x106) - 1;
        t = *(s16*)(r + 0x106);
        if (t < 0) {
            r[0x142] = 3;
            *(s16*)(r + 0x104) = 0;
            *(s16*)(r + 0x106) = lbl_3_data_4B48[1];
            *(f32*)(r + 0xB4) = (*(f32*)(r + 0x54) - *(f32*)(r + 0x68)) / (f32) * (s16*)(r + 0x106);
        } else {
            *(f32*)(r + 0xA4) = *(f32*)(r + 0xB4) * (f32)t;
        }
    }
    if (r[0x142] == 3) {
        *(s16*)(r + 0x104) = *(s16*)(r + 0x104) + 1;
        *(s16*)(r + 0x106) = *(s16*)(r + 0x106) - 1;
        if (*(s16*)(r + 0x106) < 0) {
            s32 nx;
            s32 k;
            r[0x142] = 0;
            r[0x137] = 2;
            r[0x136] = 2;
            *(f32*)(r + 0x84) = lbl_3_rodata_1414;
            *(f32*)(r + 0xA4) = lbl_3_rodata_1414;
            *(f32*)(r + 0xB0) = lbl_3_rodata_1414;
            k = r[0x125];
            nx = (k + 1) & 3;
            if (g_GameLogic[0x121] == 6) {
                u8* e = lbl_3_data_4B58;
                e += k * 0xC;
                *(f32*)(r + 0x30) = *(f32*)(e + 8);
                *(f32*)(r + 0x68) = lbl_3_rodata_1414;
            } else {
                *(f32*)(r + 0x68) = *(f32*)(r + 0x54);
            }
            *(f32*)(r + 0x64) = *(f32*)(r + 0x68) + (f32)k;
            *(s16*)(r + 0xE6) = k;
            {
                u8* t0 = (u8*)lbl_3_data_4A34;
                u8* t1 = t0 + 4;
                *(f32*)(r + 0x3C) = *(f32*)(t0 + k * 8);
                *(f32*)(r + 0x44) = *(f32*)(t1 + k * 8);
                *(f32*)(r + 0x48) = *(f32*)(t0 + nx * 8);
                *(f32*)(r + 0x50) = *(f32*)(t1 + nx * 8);
            }
        } else {
            *(f32*)(r + 0xA4) = *(f32*)(r + 0xB4);
            r[0x139] = 0;
        }
    }
    *(f32*)(r + 0x64) = *(f32*)(r + 0x64) + *(f32*)(r + 0xA4);
    *(f32*)(r + 0x68) = *(f32*)(r + 0x68) + *(f32*)(r + 0xA4);
    *(f32*)(r + 0x5C) = *(f32*)(r + 0x68) - *(f32*)(r + 0x54);
    *(f32*)(r + 0x60) = (lbl_3_rodata_1408 - *(f32*)(r + 0x68)) - *(f32*)(r + 0x58);
    return 1;
}

// .text:0x00081EAC size:0x508 mapped:0x806C0F40
void fn_3_81EAC(void) {
    return;
}

// .text:0x000823B4 size:0x2BC mapped:0x806C1448
void fn_3_823B4(int i) {
    u8* r = g_Runners + i * 0x154;
    *(s16*)(r + 0x100) = *(s16*)(r + 0x100) + 1;
    *(s16*)(r + 0x102) = *(s16*)(r + 0x102) - 1;
    if (r[0x13C] == 1) {
        f32 t;
        s16 n;
        if (r[0x13B] != 0) {
            n = *(s16*)(r + 0x102);
            t = (lbl_3_rodata_1408 - *(f32*)(r + 0x58)) - *(f32*)(r + 0x68);
            if (n <= 0) {
                *(f32*)(r + 0xA4) = lbl_3_rodata_1484 + t;
            } else {
                *(f32*)(r + 0xA4) = t / (f32)(n + 1);
            }
        } else {
            n = *(s16*)(r + 0x102);
            t = *(f32*)(r + 0x68) - *(f32*)(r + 0x54);
            if (n <= 0) {
                *(f32*)(r + 0xA4) = -t - lbl_3_rodata_1484;
            } else {
                *(f32*)(r + 0xA4) = -t / (f32)(n + 1);
            }
        }
        if (*(s16*)(r + 0x102) <= 0) {
            *(s16*)(r + 0x100) = 0;
            *(s16*)(r + 0x102) = lbl_3_data_7760[*(s16*)(r + 0xE2) * 5 + 3];
            r[0x13C] = 2;
            *(f32*)(r + 0xA4) = lbl_3_rodata_1414;
            *(f32*)(r + 0x64) = (f32)r[0x127];
            *(f32*)(r + 0x68) = lbl_3_rodata_1414;
            if (r[0x127] == 0) {
                *(f32*)(r + 0x64) = lbl_3_rodata_1470;
            }
            if (r[0x123] == 2) {
                r[0x13C] = 3;
            }
        }
    } else if (r[0x13C] == 2) {
        *(f32*)(r + 0x84) = lbl_3_rodata_1414;
        *(f32*)(r + 0xA4) = lbl_3_rodata_1414;
        if (*(s16*)(r + 0x102) <= 0) {
            s32 nx;
            s16 k;
            r[0x13A] = 0;
            r[0x13C] = 0;
            if (*(s16*)(r + 0xE6) >= 0) {
                r[0x137] = 2;
                r[0x136] = 2;
                *(f32*)(r + 0x84) = lbl_3_rodata_1414;
                *(f32*)(r + 0xA4) = lbl_3_rodata_1414;
                *(f32*)(r + 0xB0) = lbl_3_rodata_1414;
                k = *(s16*)(r + 0xE6);
                nx = (k + 1) & 3;
                if (g_GameLogic[0x121] == 6) {
                    {
                        u8* e = lbl_3_data_4B58;
                        e += k * 0xC;
                        *(f32*)(r + 0x30) = *(f32*)(e + 8);
                    }
                    *(f32*)(r + 0x68) = lbl_3_rodata_1414;
                } else {
                    *(f32*)(r + 0x68) = *(f32*)(r + 0x54);
                }
                *(f32*)(r + 0x64) = *(f32*)(r + 0x68) + (f32)k;
                *(s16*)(r + 0xE6) = k;
                {
                    u8* t0 = (u8*)lbl_3_data_4A34;
                    u8* t1 = t0 + 4;
                    *(f32*)(r + 0x3C) = *(f32*)(t0 + k * 8);
                    *(f32*)(r + 0x44) = *(f32*)(t1 + k * 8);
                    *(f32*)(r + 0x48) = *(f32*)(t0 + nx * 8);
                    *(f32*)(r + 0x50) = *(f32*)(t1 + nx * 8);
                }
                *(s16*)(r + 0x112) = 1;
            }
        }
    }
}

// .text:0x00082670 size:0x910 mapped:0x806C1704
void fn_3_82670(void) {
    return;
}

// .text:0x00082F80 size:0xFC mapped:0x806C2014
// 98%: block 2 loads r+0xA4 into f1 then fmr f5 (original lfs f5 directly, compares f5)
void fn_3_82F80(int i, s16* b, s16* a) {
    u8* r = g_Runners + i * 0x154;
    s32 n = 0;
    s32 q;
    f32 step;
    f32 lim;
    f32 rem;
    f32 v;
    f32 s;
    f32 step2;
    f32 nl;
    f32 lim2;
    f32 rem2;
    f32 s2;
    rem = *(f32*)(r + 0x60);
    if (rem > lbl_3_rodata_1414) {
        s = *(f32*)(r + 0xA4);
        lim = *(f32*)(r + 0xA8);
        if (s < lim) {
            v = s;
            step = *(f32*)(r + 0xAC);
            do {
                v += step;
                n++;
                if (v > lim) {
                    rem -= lim;
                    break;
                }
                rem -= v;
            } while (!(rem < lbl_3_rodata_1414));
        }
        n += (s32)(rem / lim) + 1;
    }
    *a = n;
    n = 0;
    rem2 = *(f32*)(r + 0x5C);
    if (rem2 > lbl_3_rodata_1414) {
        lim2 = *(f32*)(r + 0xA8);
        s2 = *(f32*)(r + 0xA4);
        nl = -lim2;
        if (s2 > nl) {
            step2 = *(f32*)(r + 0xAC);
            do {
                s2 -= step2;
                n++;
                if (s2 < nl) {
                    rem2 -= lim2;
                    break;
                }
                rem2 -= s2;
            } while (!(rem2 < lbl_3_rodata_1414));
        }
        n += (s32)(rem2 / lim2) + 1;
    }
    *b = n;
}

// .text:0x0008307C size:0x370 mapped:0x806C2110
void fn_3_8307C(int i) {
    u8* r = g_Runners + i * 0x154;
    if ((r[0x145] != 1 || r[0x146] == 0) && g_Pitcher[0x13E] != 6) {
        s32 k;
        s32 nx;
        f32 a;
        f32 b;
        f32 dx;
        f32 dz;
        k = (s32) * (f32*)(r + 0x64);
        *(f32*)(r + 0x40) = lbl_3_rodata_1414;
        *(f32*)(r + 0x4C) = lbl_3_rodata_1414;
        nx = (k + 1) % 4;
        if (g_GameLogic[0x121] == 6) {
            *(f32*)(r + 0x3C) = lbl_3_data_4A34[k * 2];
            *(f32*)(r + 0x44) = lbl_3_data_4A34[k * 2 + 1];
        } else if (k + 1 == 1) {
            *(f32*)(r + 0x3C) = *(f32*)(g_Batter + 0);
            *(f32*)(r + 0x44) = *(f32*)(g_Batter + 4);
        } else {
            *(f32*)(r + 0x3C) = lbl_3_data_4A34[k * 2];
            *(f32*)(r + 0x44) = lbl_3_data_4A34[k * 2 + 1];
        }
        *(f32*)(r + 0x48) = lbl_3_data_4A34[nx * 2];
        *(f32*)(r + 0x50) = lbl_3_data_4A34[nx * 2 + 1];
        a = sqrt13B8((*(f32*)(r + 0x3C) - *(f32*)(r + 0)) * (*(f32*)(r + 0x3C) - *(f32*)(r + 0)) + (*(f32*)(r + 0x44) - *(f32*)(r + 8)) * (*(f32*)(r + 0x44) - *(f32*)(r + 8)));
        b = sqrt13B8((*(f32*)(r + 0x48) - *(f32*)(r + 0)) * (*(f32*)(r + 0x48) - *(f32*)(r + 0)) + (*(f32*)(r + 0x50) - *(f32*)(r + 8)) * (*(f32*)(r + 0x50) - *(f32*)(r + 8)));
        *(f32*)(r + 0x6C) = a + b;
        *(f32*)(r + 0x70) = a / (a + b);
        *(f32*)(r + 0x74) = a;
        *(f32*)(r + 0x78) = b;
        r[0x125] = k;
        r[0x126] = nx;
        fn_3_82F80(i, (s16*)(r + 0xEC), (s16*)(r + 0xEA));
    }
}

// .text:0x000833EC size:0x1C4 mapped:0x806C2480
void fn_3_833EC(int i) {
    u8* r;
    int v;
    ((void (*)(int))fn_3_8307C)(i);
    r = g_Runners + i * 0x154;
    if ((r[0x145] == 0 || r[0x146] == 0) && r[0x13A] == 0) {
        if (*(s16*)(r + 0x112) >= lbl_3_data_4C54[3] || (r[0x137] != 1 && r[0x137] != 3)) {
            u8 s = r[0x135];
            if (s != 0) {
                if (g_GameLogic[0x121] == 6) {
                    if (r[0x123] == 1) {
                        r[0x136] = s;
                    }
                } else {
                    if ((i != 0 || r[0x126] != 1) && r[0x123] == 1) {
                        r[0x136] = s;
                    }
                    if (r[0x136] == 3 && r[0x128] != 3 && *(s16*)(r + 0xE6) >= 0) {
                        r[0x136] = 0;
                    }
                }
            }
        }
        v = ((int (*)(int))fn_3_7FA78)(i);
        if (v != 0) {
            r[0x136] = v;
        }
    }
    if (r[0x145] != 0) {
        r[0x13E] = 0;
        r[0x13A] = 0;
    } else {
        fn_3_7ECFC(i);
        fn_3_7F494(i);
        if (g_GameLogic[0x121] != 6) {
            if (i == 0 && r[0x126] == 1) {
                fn_3_7F2D8();
            } else if (r[0x13E] == 1) {
                r[0x13E] = 0;
            }
            fn_3_7EBD4(i);
        }
    }
    ((void (*)(int))fn_3_82670)(i);
    ((void (*)(int))fn_3_81190)(i);
    ((void (*)(int))fn_3_80028)(i);
    ((void (*)(int))fn_3_8307C)(i);
}

// .text:0x000835B0 size:0x164 mapped:0x806C2644
// 99.5%: 12 diff lines, post-RandomInt_Game table temps (r0/r4/r5 allocation of idx*8 + DATA base)
void fn_3_835B0(void) {
    u8* ai;
    s32* t;
    s32 k;
    if (g_GameLogic[*(s32*)(g_GameLogic + 0xC) + 0x13E] == 0) {
        if (*(u16*)(g_Controls + *(s32*)(g_GameLogic + *(s32*)(g_GameLogic + 4) * 4 + 0xEC) * 16 + 6) & 0xF00) {
            g_Runners[0x149] = 1;
            g_Runners[0x29D] = 1;
            g_Runners[0x3F1] = 1;
            g_Runners[0x545] = 1;
        }
    } else {
        ai = g_AiLogic;
        if (*(s16*)(ai + 0x44) > 0) {
            t = (s32*)(g_GameLogic + 0x14);
            if (*(s16*)(g_Ball + 0x1B66) >= lbl_3_data_1C58[t[*(s32*)(g_GameLogic + 0xC)] * 4]) {
                if (ai[0x77] != 0) {
                    ai[0x77] = ai[0x77] - 1;
                    return;
                }
                if (RandomInt_Game(0x64) < *(s16*)((u8*)lbl_3_data_1C58 + (k = t[*(s32*)(g_GameLogic + 0xC)] * 8) + 6)) {
                    g_Runners[0x149] = 1;
                    g_Runners[0x29D] = 1;
                    g_Runners[0x3F1] = 1;
                    g_Runners[0x545] = 1;
                    *(s16*)(ai + 0x44) = *(s16*)(ai + 0x44) - 1;
                }
                ai[0x77] = *(s16*)((u8*)lbl_3_data_1C58 + k + 4);
            }
        }
    }
}

// .text:0x00083714 size:0xAAC mapped:0x806C27A8
void fn_3_83714(void) {
    return;
}

// .text:0x000841C0 size:0x124 mapped:0x806C3254
int fn_3_841C0(int i, int j) {
    u8* r = g_Runners + i * 0x154;
    int v;
    int k;
    if (*(s16*)(r + 0xEE) == 1) {
        return 1;
    }
    k = r[0x126];
    v = j + fn_3_A6810(((f32*)(g_Ball + 0x354))[j * 4], ((f32*)(g_Ball + 0x35C))[j * 4], lbl_3_data_4444[k * 2], lbl_3_data_4444[k * 2 + 1]);
    v += 0x2D;
    if (*(s32*)(g_GameLogic + *(s32*)(g_GameLogic + 0x10) * 4 + 0x14) >= 3) {
        v -= 0x1E;
    } else {
        v += lbl_3_data_1C88[*(s32*)(g_GameLogic + *(s32*)(g_GameLogic + 0xC) * 4 + 0xE4)];
    }
    if (g_Ball[0x1BBE] <= 1) {
        if (v - 0x14 > *(s16*)(r + 0xEA)) {
            return 1;
        }
    } else if (v > *(s16*)(r + 0xEA)) {
        return 1;
    }
    return -1;
}

// .text:0x000842E4 size:0x3E4 mapped:0x806C3378
void fn_3_842E4(void) {
    return;
}

// .text:0x000846C8 size:0x408 mapped:0x806C375C
void fn_3_846C8(void) {
    return;
}

// .text:0x00084AD0 size:0x5A4 mapped:0x806C3B64
void fn_3_84AD0(void) {
    return;
}

// .text:0x00085074 size:0x6D0 mapped:0x806C4108
void fn_3_85074(void) {
    return;
}

// .text:0x00085744 size:0xFC mapped:0x806C47D8
void fn_3_85744(int i) {
    u8* r = g_Runners + i * 0x154;
    if (*(f32*)(r + 0x64) > lbl_3_rodata_1488) {
        return;
    }
    if (*(f32*)(r + 0x38) < lbl_3_rodata_143C && g_Ball[0x1BC9] == 3) {
        r[0x12B] = 0;
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) == 5 || *(s16*)(g_FieldingLogic + 0xC4) == 6 ||
        *(s16*)(g_FieldingLogic + 0xC4) == r[0x125]) {
        if (*(f32*)(r + 0x68) >= lbl_3_rodata_1490 && r[0x137] == 1 && g_Ball[0x1BBE] <= 3) {
            r[0x12B] = 0;
        }
    }
    if (*(s16*)(r + 0xE6) >= 0 && r[0x13E] == 2) {
        r[0x12B] = 1;
        if (lbl_3_rodata_1498 == *(f32*)(r + 0x84)) {
            r[0x12B] = 0;
        }
    }
}

// .text:0x00085840 size:0x230 mapped:0x806C48D4
// 97%: logic matches; register roles differ (arr copied to r10 and bc4 lands in r5; original keeps arr in r5, bc4 in r11, temp r10)
int fn_3_85840(int i, int b, int* arr) {
    u8 bc9;
    u8* r;
    s16 b7a;
    u8 sf;
    u8 bc4;
    u8* self;
    int j;
    self = g_Runners + i * 0x154;
    sf = self[0x126];
    if ((s32)sf == 0) {
        return 0;
    }
    j = i + 1;
    r = g_Runners + j * 0x154;
    arr += j;
    bc9 = g_Ball[0x1BC9];
    b7a = *(s16*)(g_Ball + 0x1B7A);
    bc4 = g_Ball[0x1BC4];
    for (; j < 4; j++, r += 0x154, arr++) {
        u8 t;
        u8 u;
        if (r[0x123] == 1) {
            t = r[0x125];
            if (t == self[0x125]) {
                if (r[0x13E] == 2 && r[0x142] == 3) {
                    return 1;
                }
                u = r[0x137];
                if (u == 3) {
                    return 1;
                }
                if (u == 2 && *(f32*)(r + 0x64) - *(f32*)(self + 0x64) < (*(f32*)&lbl_3_rodata_1440)) {
                    return 2;
                }
                if (bc9 != 0) {
                    return 1;
                }
                if (i == 0 && b7a == 0) {
                    f32 f = *(f32*)(self + 0x64);
                    if (f > (*(f32*)&lbl_3_rodata_1408) && b <= 3 && *(f32*)(r + 0x64) < f) {
                        return 2;
                    }
                }
            }
            if (t == sf) {
                if (b7a == 0) {
                    if (bc4 <= 4 && *(f32*)(r + 0x68) < (*(f32*)&lbl_3_rodata_1450)) {
                        if (*(s16*)(self + 0xEE) == 1 && b > 3) {
                            return 0;
                        }
                        u = r[0x137];
                        if (u == 3 || u == 2) {
                            return 1;
                        }
                    }
                } else if (*(f32*)(r + 0x68) < (*(f32*)&lbl_3_rodata_1450) && arr[0] <= 0) {
                    u = r[0x137];
                    if (u == 2 || u == 3 || (u == 1 && r[0x136] == 3)) {
                        return 1;
                    }
                    if (r[0x13E] == 2 && r[0x142] >= 2) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

// .text:0x00085A70 size:0x1D4 mapped:0x806C4B04
int fn_3_85A70(int i) {
    u8* r = g_Runners + i * 0x154;
    int a;
    int b;
    int y1;
    int y2;
    int st;
    u8 k;
    int w;
    int s2;
    int res;
    s16 e;
    s16 g;
    st = *(s16*)(g_FieldingLogic + 0xCC);
    if (st == 9 && *(s16*)(g_FieldingLogic + 0xDE) != i) {
        return -2;
    }
    if (*(s16*)(r + 0xE6) >= 0) {
        return -2;
    }
    a = r[0x126];
    b = r[0x125];
    if (a == *(s16*)(g_FieldingLogic + 0xDC) && (st == b || st == 9)) {
        return -1;
    }
    if (b == *(s16*)(g_FieldingLogic + 0xDC) && (st == a || st == 9)) {
        return 1;
    }
    y1 = fn_3_52560(*(s16*)(g_Ball + 0x1B78), lbl_3_data_4444[a * 2], lbl_3_data_4444[a * 2 + 1]);
    y2 = fn_3_52560(*(s16*)(g_Ball + 0x1B78), lbl_3_data_4444[b * 2], lbl_3_data_4444[b * 2 + 1]);
    e = *(s16*)(r + 0xEA);
    g = *(s16*)(r + 0xEC);
    s2 = *(s16*)(g_FieldingLogic + 0xCC);
    if (s2 == 9) {
        k = r[0x137];
        if (k == 1 || k == 2) {
            if (e < y1) {
                return 1;
            }
            return -1;
        }
        res = 1;
        if (g < y2) {
            res = -1;
        }
        return res;
    }
    if (*(f32*)(r + 0x38) > 20.0f) {
        return -2;
    }
    k = r[0x137];
    w = r[0x125];
    if (k == 1 || k == 2) {
        w = r[0x126];
    }
    if (w != s2) {
        return -2;
    }
    if (k == 1) {
        res = -1;
        if (e <= y1) {
            res = 1;
        }
        return res;
    }
    res = 1;
    if (g <= y2) {
        res = -1;
    }
    return res;
}

// .text:0x00085C44 size:0x6C mapped:0x806C4CD8
#pragma dont_inline off
static inline void h85C44(u8* r, s32 i, s32 d) {
    if (r[0x13E] == 1 && r[0x140] >= 2 && d != 1) {
        return;
    }
    if (d == -1) {
        if (r[0x124] == *(s16*)(r + 0xE6)) {
            d = 0;
        }
    }
    fn_3_85EF4(i, d);
}

void fn_3_85C44(s32 i, s32 d) {
    u8* r = g_Runners + i * 0x154;
    if (r[0x13E] == 1 && r[0x140] >= 2 && d != 1) {
        return;
    }
    if (d == -1) {
        if (r[0x124] == *(s16*)(r + 0xE6)) {
            d = 0;
        }
    }
    fn_3_85EF4(i, d);
}

// .text:0x00085CB0 size:0x244 mapped:0x806C4D44
void fn_3_85CB0(void) {
    u8* r;
    u8* q;
    int j;
    int i;
    if (*(s16*)(g_Ball + 0x1B68) <= 0x1E && g_Pitcher[0x13E] == 2) {
        if (g_Strikes[2] == 2 && ((u8*)g_Strikes)[0x20] == 0x23) {
            for (i = 1, r = g_Runners + 0x154; i <= 3; i++, r += 0x154) {
                if (r[0x123] == 0) {
                    break;
                }
                if (*(s16*)(g_Pitcher + 0x11E) >= g_AiLogic[0x76]) {
                    h85C44(r, i, 1);
                }
            }
        } else if (g_AiLogic[0x75] != 0) {
            for (j = 1, q = g_Runners + 0x154; j <= 2; j++, q += 0x154) {
                if (*(s16*)(g_Pitcher + 0x11E) >= g_AiLogic[0x76]) {
                    if (q[0x14E] == 0) {
                        if (g_AiLogic[0x76] < lbl_3_data_4B90[2]) {
                            q[0x14E] = 3;
                        } else {
                            q[0x14E] = 2;
                        }
                        q[0x133] = 0;
                    }
                    h85C44(q, j, 1);
                }
            }
        } else if (g_AiLogic[0x74] == 2 && *(s16*)(g_Pitcher + 0x11E) >= g_AiLogic[0x76]) {
            fn_3_85C44(3, 1);
        }
    }
}
#pragma dont_inline on

// .text:0x00085EF4 size:0x158 mapped:0x806C4F88
void fn_3_85EF4(s32 i, s32 d) {
    s16 e;
    u8 t;
    u8* r = g_Runners + i * 0x154;
    if (r[0x123] != 1) {
        return;
    }
    if (r[0x128] == 2 && d != -1) {
        return;
    }
    if (r[0x13A] != 0 && r[0x13C] != 0) {
        if (r[0x13B] == 1) {
            r[0x127] = r[0x126];
            return;
        }
        r[0x127] = r[0x125];
        return;
    }
    if (d == 1) {
        r[0x127] = r[0x126];
    }
    if (d == -1) {
        t = r[0x125];
        if (t == 0) {
            return;
        }
        if (r[0x137] == 1 && *(s16*)(r + 0xE6) >= 0 && r[0x128] == 0) {
            if (r[0x13E] == 1) {
                return;
            }
            r[0x137] = 2;
            return;
        } else {
            e = *(s16*)(r + 0xE6);
            if (e >= 0) {
                if (e == 1) {
                    return;
                }
                if (i == 0) {
                    return;
                }
                if (r[0x128] == 0) {
                    return;
                }
                r[0x127] = (e + 3) & 3;
            } else {
                r[0x127] = t;
            }
        }
    }
    if (d == 0 && i == 0 && r[0x125] == 0) {
        return;
    }
    if (d == 0) {
        r[0x135] = 2;
        return;
    }
    if (d == 1) {
        r[0x135] = 1;
        return;
    }
    r[0x135] = 3;
}

// .text:0x0008604C size:0xCC mapped:0x806C50E0
int fn_3_8604C(int* out) {
    int i;
    int best;
    int j;
    int t;
    best = 9999;
    for (i = 0; i < 9; i++) {
        if (g_FieldingLogic[i + 0xF8] == 1 || g_FieldingLogic[i + 0xF8] == 0xA || g_FieldingLogic[i + 0xF8] == 0xB) {
            for (j = 1; j < 0x78; j += 5) {
                t = fn_3_52560(i, *(f32*)(g_Ball + j * 0x10 + 0x354), *(f32*)(g_Ball + j * 0x10 + 0x35C));
                if (t < j + 0xF) {
                    break;
                }
            }
            if (j >= 0x78) {
                if (best >= 0x78) {
                    best = 0x78;
                }
            } else if (best > t) {
                best = t;
                *out = i;
            }
        }
    }
    return best;
}

// .text:0x00086118 size:0x684 mapped:0x806C51AC
void fn_3_86118(void) {
    return;
}

// .text:0x0008679C size:0x660 mapped:0x806C5830
void fn_3_8679C(void) {
    return;
}

// .text:0x00086DFC size:0xFC mapped:0x806C5E90
void fn_3_86DFC(void) {
    u8* r = g_Runners;
    int i;
    for (i = 0; i < 4; i++) {
        if (r[0x123] != 0) {
            if (g_FieldingLogic[0x107] == 1 && r[0x14E] != 0 && *(s16*)(r + 0xE0) >= 0) {
                r[0x135] = 1;
            }
            r[0x14E] = 0;
        }
        r += 0x154;
    }
}

// .text:0x00086EF8 size:0x1B4 mapped:0x806C5F8C
// 99%: body matches; only d1/base/lo register numbering differs (r7/r8 swapped) around the data[1]/data[0] range check
void fn_3_86EF8(void) {
    int i;
    int j;
    int all;
    s16 pt;
    u8* r;
    for (i = 1; i < 4; i++) {
        r = g_Runners + i * 0x154;
        if (r[0x123] != 0 && r[0x14E] != 0) {
            if (r[0x14F] < 0xFE) {
                r[0x14F] = r[0x14F] + 1;
            } else {
                r[0x14F] = 0xFF;
            }
            pt = *(s16*)(g_Pitcher + 0x11E);
            if (pt > 0 && r[0x14E] == 1) {
                if (pt == lbl_3_data_4B90[2]) {
                    u8 t = r[0x14F];
                    s32 lo = lbl_3_data_4B90[2] - lbl_3_data_4B90[1];
                    s32 hi = lbl_3_data_4B90[2] - lbl_3_data_4B90[0];
                    if (t >= lo && t <= hi) {
                        r[0x14E] = 3;
                        r[0x133] = 0;
                        if (*(s16*)(r + 0xE0) >= 0) {
                            r[0x135] = 1;
                        }
                    }
                } else if (pt >= lbl_3_data_4B90[3]) {
                    r[0x14E] = 2;
                    r[0x133] = 0;
                    if (*(s16*)(r + 0xE0) >= 0) {
                        r[0x135] = 1;
                    }
                }
            }
            if (r[0x123] == 1 && r[0x137] == 1 && r[0x14D] == 0) {
                all = 1;
                for (j = 1; j < i; j++) {
                    if (g_Runners[j * 0x154 + 0x123] == 0) {
                        all = 0;
                    }
                }
                if (all != 0) {
                    r[0x14D] = i + 1;
                } else {
                    r[0x14D] = 1;
                }
            }
            if (r[0x14D] != 0) {
                if (*(s16*)(r + 0x116) < 0x7FFE) {
                    *(s16*)(r + 0x116) = *(s16*)(r + 0x116) + 1;
                } else {
                    *(s16*)(r + 0x116) = 0x7FFF;
                }
            }
        }
    }
}

// .text:0x000870AC size:0x110 mapped:0x806C6140
void fn_3_870AC(void) {
    u8* r;
    g_Runners[0x130] = 0;
    g_Runners[0x284] = 0;
    g_Runners[0x3D8] = 0;
    g_Runners[0x52C] = 0;
    if ((g_FieldingLogic[0x111] == 2 || g_FieldingLogic[0x111] == 4) && *(s16*)(g_FieldingLogic + 0xE8) >= 0) {
        r = g_Runners + *(s16*)(g_FieldingLogic + 0xE8) * 0x154;
        if (r[0x123] == 1) {
            r[0x130] = 1;
        }
        if (*(s16*)(g_FieldingLogic + 0xEC) < 5 && r[0x13A] != 0) {
            r[0x130] = 2;
        }
        if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
            {
                u8* f;
                f = g_Fielders;
                f += *(s16*)(g_Ball + 0x1B78) * 0x268;
                fn_3_161588(6, *(s16*)(f + 0x178));
            }
        }
    }
}

// .text:0x000871BC size:0x110 mapped:0x806C6250
// ~90%: body matches; prologue base-register order and hoisted lha/lfs scheduling differ (tried ~200 decl/init/loop-form variants)
void fn_3_871BC(void) {
    int n;
    f32 c1 = lbl_3_data_4C44[1];
    f32 c2 = lbl_3_data_4C44[2];
    f32 c3 = lbl_3_data_4C44[3];
    s16 a = lbl_3_data_4C54[10];
    s16 b = lbl_3_data_4C54[11];
    s16 mx = lbl_3_data_4C54[9];
    for (n = 0; n < 4; n++) {
        u8* r = g_Runners + n * 0x154;
        if (r[0x123] == 1) {
            s32 d = 0;
            f32 t;
            if (*(f32*)(r + 0x84) >= lbl_3_rodata_1498) {
                d = a;
            }
            if (r[0x147] != 0) {
                d += b;
            }
            if (d != 0) {
                *(s16*)(r + 0xF6) = *(s16*)(r + 0xF6) - d;
                if (*(s16*)(r + 0xF6) < 0) {
                    *(s16*)(r + 0xF6) = 0;
                }
            }
            t = 1.0f - (f32)*(s16*)(r + 0xF6) / (f32)mx;
            *(f32*)(r + 0xD4) = 1.0f - c1 * t;
            *(f32*)(r + 0xD8) = 1.0f - c2 * t;
            *(f32*)(r + 0xDC) = 1.0f - c3 * t;
        }
    }
}

// .text:0x000872CC size:0x158 mapped:0x806C6360
void fn_3_872CC(void) {
    int n;
    for (n = 0; n < 4; n++) {
        u8* r = g_Runners + n * 0x154;
        if (r[0x123] != 0) {
            *(s16*)(r + 0xE8) = *(s16*)(r + 0xE6);
            *(f32*)(r + 0xC) = *(f32*)(r + 0x0);
            *(f32*)(r + 0x10) = *(f32*)(r + 0x4);
            *(f32*)(r + 0x14) = *(f32*)(r + 0x8);
            *(f32*)(r + 0x24) = *(f32*)(r + 0x18);
            *(f32*)(r + 0x28) = *(f32*)(r + 0x1C);
            *(f32*)(r + 0x2C) = *(f32*)(r + 0x20);
            *(f32*)(r + 0x7C) = *(f32*)(r + 0x64);
            *(f32*)(r + 0x80) = *(f32*)(r + 0x68);
            r[0x135] = 0;
            r[0x149] = 0;
            if (*(s16*)(g_Ball + 0x1B7A) == 3 && g_Strikes[3] < 2 && r[0x128] == 1) {
                r[0x128] = 2;
                if (*(s16*)(r + 0xE6) == r[0x124]) {
                    r[0x128] = 0;
                }
            }
            if (r[0x150] != 0) {
                r[0x150] = r[0x150] - 1;
                if (r[0x150] == 0) {
                    r[0x151] = 0;
                }
            }
            if (g_GameLogic[0x11E] == 2) {
                r[0x133] = 0;
            }
        }
    }
    if (*(s16*)(g_Ball + 0x1B66) == 1 && *(f32*)(g_Ball + 0x19D4) >= lbl_3_rodata_14BC && g_Ball[0x1BBF] >= 2) {
        g_RunningLogic[0x14] = 10;
    }
}

// .text:0x00087424 size:0x3F8 mapped:0x806C64B8
// 97%: only prologue load order differs (orig loads 4C54 table first: lha 0x14,0x16,0x12 then lfs 4C44; ours starts with 4C44 base)
void fn_3_87424(void) {
    u8* q;
    s16 t;
    u8* f;
    int off;
    s16 a;
    s16 b86;
    int ri;
    int i;
    u8* r;
    s32 d;
    f32 p;
    s16 h1;
    s16 h2;
    s16 h3;
    f32 c1;
    f32 c2;
    f32 c3;
    fn_3_872CC();
    if (g_GameLogic[0x121] != 6 && g_GameLogic[0x121] != 0xE) {
        b86 = *(s16*)(g_Ball + 0x1B86);
        if (b86 >= 0 && (a = *(s16*)(g_Ball + 0x1B7A)) >= 0 && a != 3 && g_Fielders[*(s16*)(g_Ball + 0x1B78) * 0x268 + 0x1E7] == 0) {
            ri = (b86 + 3) & 3;
            off = ri * 0x154;
            q = g_Runners + off;
            if (*(s16*)(q += 0xEE) == 1) {
                fn_3_88D88(ri);
                *(s16*)q = 2;
                g_Runners[off + 0x12C] = 2;
                if (*(s16*)(g_Ball + 0x1B92) < 0) {
                    t = *(s16*)(g_Ball + 0x1B94);
                    if (t < 0) {
                        *(s16*)(g_Ball + 0x1B92) = *(s16*)(g_Ball + 0x1B78);
                    } else {
                        *(s16*)(g_Ball + 0x1B92) = t;
                        if (g_FieldingLogic[0x141] != 0 && g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
                            f = g_Fielders;
                            f += t * 0x268;
                            fn_3_161588(8, *(s16*)(f + 0x178));
                        }
                        if ((s8)g_FieldingLogic[0x115] > 0 && g_FieldingLogic[0x133] != 0) {
                            g_UnkSound_32718[8] = 4;
                            t = *(s16*)(g_Ball + 0x1B90);
                            g_FieldingLogic[0x134] = t;
                            if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
                                f = g_Fielders;
                                f += t * 0x268;
                                fn_3_161588(2, *(s16*)(f + 0x178));
                            }
                        }
                    }
                }
            }
        }
        h1 = lbl_3_data_4C54[10];
        h2 = lbl_3_data_4C54[11];
        c1 = lbl_3_data_4C44[1];
        c2 = lbl_3_data_4C44[2];
        c3 = lbl_3_data_4C44[3];
        h3 = lbl_3_data_4C54[9];
        for (i = 0; i < 4; i++) {
            r = g_Runners + i * 0x154;
            if (r[0x123] == 1) {
                d = 0;
                if (*(f32*)(r + 0x84) >= lbl_3_rodata_1498) {
                    d = h1;
                }
                if (r[0x147] != 0) {
                    d += h2;
                }
                if (d != 0) {
                    *(s16*)(r + 0xF6) = *(s16*)(r + 0xF6) - d;
                    if (*(s16*)(r + 0xF6) < 0) {
                        *(s16*)(r + 0xF6) = 0;
                    }
                }
                p = lbl_3_rodata_1408 - (f32) * (s16*)(r + 0xF6) / (f32)h3;
                *(f32*)(r + 0xD4) = lbl_3_rodata_1408 - c1 * p;
                *(f32*)(r + 0xD8) = lbl_3_rodata_1408 - c2 * p;
                *(f32*)(r + 0xDC) = lbl_3_rodata_1408 - c3 * p;
            }
        }
        g_Runners[0x130] = 0;
        g_Runners[0x284] = 0;
        g_Runners[0x3D8] = 0;
        g_Runners[0x52C] = 0;
        if (g_FieldingLogic[0x111] == 2 || g_FieldingLogic[0x111] == 4) {
            s16 fi = *(s16*)(g_FieldingLogic + 0xE8);
            if (fi >= 0) {
                q = g_Runners + fi * 0x154;
                if (q[0x123] == 1) {
                    q[0x130] = 1;
                }
                if (*(s16*)(g_FieldingLogic + 0xEC) < 5 && q[0x13A] != 0) {
                    q[0x130] = 2;
                }
                if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
                    f = g_Fielders;
                    f += *(s16*)(g_Ball + 0x1B78) * 0x268;
                    fn_3_161588(6, *(s16*)(f + 0x178));
                }
            }
        }
    }
}

// .text:0x0008781C size:0x2CC mapped:0x806C68B0
void fn_3_8781C(void) {
    return;
}

// .text:0x00087AE8 size:0x1E0 mapped:0x806C6B7C
void fn_3_87AE8(void) {
    u8* r = g_Runners;
    s16 b;
    r[0x129] = 0;
    if (g_GameLogic[0x121] != 6) {
        if (g_Minigame[0x1A2A] == 3) {
            r[0x129] = 1;
        } else if ((b = *(s16*)(g_Ball + 0x1B66)) < 0) {
            r[0x129] = 1;
        } else if (g_FieldingLogic[0x107] == 1 || g_FieldingLogic[0x107] == 2 || g_FieldingLogic[0x107] == 3) {
            if (g_Strikes[2] < 3) {
                r[0x129] = 1;
            }
        } else if (r[0x12C] == 0 || r[0x123] != 2) {
            if (b < r[0x122]) {
                r[0x129] = 2;
            } else if (g_Batter[0x94] == 4 && b < 0x5A) {
                r[0x129] = 2;
            } else if (g_Batter[0x94] == 3 || g_Batter[0x94] == 6) {
                r[0x129] = 3;
            }
        }
    }
    *(f32*)(g_Runners + 0x18) = *(f32*)(g_Runners + 0x0) - *(f32*)(g_Runners + 0xC);
    *(f32*)(g_Runners + 0x1C) = *(f32*)(g_Runners + 0x4) - *(f32*)(g_Runners + 0x10);
    *(f32*)(g_Runners + 0x20) = *(f32*)(g_Runners + 0x8) - *(f32*)(g_Runners + 0x14);
    *(f32*)(g_Runners + 0x16C) = *(f32*)(g_Runners + 0x154) - *(f32*)(g_Runners + 0x160);
    *(f32*)(g_Runners + 0x170) = *(f32*)(g_Runners + 0x158) - *(f32*)(g_Runners + 0x164);
    *(f32*)(g_Runners + 0x174) = *(f32*)(g_Runners + 0x15C) - *(f32*)(g_Runners + 0x168);
    *(f32*)(g_Runners + 0x2C0) = *(f32*)(g_Runners + 0x2A8) - *(f32*)(g_Runners + 0x2B4);
    *(f32*)(g_Runners + 0x2C4) = *(f32*)(g_Runners + 0x2AC) - *(f32*)(g_Runners + 0x2B8);
    *(f32*)(g_Runners + 0x2C8) = *(f32*)(g_Runners + 0x2B0) - *(f32*)(g_Runners + 0x2BC);
    *(f32*)(g_Runners + 0x414) = *(f32*)(g_Runners + 0x3FC) - *(f32*)(g_Runners + 0x408);
    *(f32*)(g_Runners + 0x418) = *(f32*)(g_Runners + 0x400) - *(f32*)(g_Runners + 0x40C);
    *(f32*)(g_Runners + 0x41C) = *(f32*)(g_Runners + 0x404) - *(f32*)(g_Runners + 0x410);
}

// .text:0x00087CC8 size:0x1B8 mapped:0x806C6D5C
void fn_3_87CC8(void) {
    int i;
    for (i = 0; i < 4; i++) {
        u8* r = g_Runners + i * 0x154;
        if (r[0x123] != 0) {
            f32 v;
            atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x1C));
            if (g_Minigame[*(s8*)(g_Minigame + 0x18FC + i) + 0x1B15] == 1) {
                v = fn_3_9FEA8((f32)(lbl_3_rodata_14E8 + atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20))));
            } else if (r[0x137] != 0 && r[0x137] != 2) {
                if (lbl_3_rodata_1414 == *(f32*)(r + 0x18) && lbl_3_rodata_1414 == *(f32*)(r + 0x20)) {
                    v = (f32)atan2(-*(f32*)(r + 0x24), -*(f32*)(r + 0x2C));
                    if (r[0x148] == 1 && r[0x137] == 1 && *(f32*)(r + 0x94) > lbl_3_rodata_1414) {
                        v = fn_3_9FEA8(lbl_3_rodata_14F0 + v);
                    }
                } else {
                    v = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20));
                }
            } else if (lbl_3_rodata_1414 == *(f32*)(r + 0x68)) {
                v = *(f32*)(lbl_3_data_4B58 + r[0x125] * 0xC + 8);
            } else {
                v = *(f32*)(lbl_3_data_4B58 + r[0x125] * 0xC);
            }
            *(f32*)(r + 0x30) = v;
            *(f32*)(r + 0x34) = v;
        }
    }
}

// .text:0x00087E80 size:0x3A8 mapped:0x806C6F14
void fn_3_87E80(void) {
    int i;
    for (i = 0; i < 4; i++) {
        u8* r = g_Runners + i * 0x154;
        if (r[0x123] != 0) {
            f32 v = *(f32*)(r + 0x30);
            f32 ang = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x1C));
            if (g_GameLogic[0x121] != 6) {
                if (i == 0 && (r[0x129] == 1 || (g_Pitcher[0x14E] == 1 && g_FieldingLogic[0x107] != 4))) {
                    v = lbl_3_rodata_14F0;
                } else if (i == 0 && g_Batter[0x94] != 0 && r[0x129] != 0) {
                    if (*(f32*)(r + 0x84) >= lbl_3_rodata_14F4) {
                        v = ang;
                    } else {
                        v = lbl_3_rodata_14F0;
                    }
                } else if (i == 0 && (g_FieldingLogic[0x107] == 1 || g_FieldingLogic[0x107] == 2) && g_Strikes[2] < 3) {
                    v = lbl_3_rodata_14F0;
                } else if (r[0x13A] != 0) {
                    if (r[0x13C] == 2 && *(s16*)(r + 0x102) <= 1) {
                        v = *(f32*)(lbl_3_data_4B58 + *(s16*)(r + 0xE6) * 0xC);
                    }
                } else if (r[0x140] >= 2) {
                    v = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20));
                } else if (r[0x13E] == 2 && *(s16*)(r + 0xE6) >= 0) {
                    v = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20));
                } else if (r[0x133] == 1) {
                    v = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20));
                } else if (r[0x145] != 0) {
                    if (r[0x145] == 2 && *(s16*)(r + 0x114) != 0) {
                        v = *(f32*)(r + 0x30);
                    } else if (lbl_3_rodata_1414 == *(f32*)(r + 0x18)) {
                        v = *(f32*)(r + 0x30);
                    } else {
                        v = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20));
                    }
                } else {
                    goto blk37;
                }
            } else {
            blk37:
                if (r[0x137] != 0 && r[0x137] != 2) {
                    if (r[0x133] == 2) {
                        v = *(f32*)(lbl_3_data_4B58 + r[0x125] * 0xC);
                    } else if (lbl_3_rodata_1414 == *(f32*)(r + 0x18) && lbl_3_rodata_1414 == *(f32*)(r + 0x20)) {
                        v = (f32)atan2(-*(f32*)(r + 0x24), -*(f32*)(r + 0x2C));
                        if (r[0x148] == 1 && r[0x137] == 1 && *(f32*)(r + 0x94) > lbl_3_rodata_1414) {
                            v = fn_3_9FEA8(lbl_3_rodata_14F0 + v);
                        }
                    } else {
                        v = (f32)atan2(-*(f32*)(r + 0x18), -*(f32*)(r + 0x20));
                    }
                } else {
                    v = *(f32*)(lbl_3_data_4B58 + r[0x125] * 0xC);
                }
            }
            *(f32*)(r + 0x30) = v;
            if (g_Ball[0x1BBE] != 0) {
                v = (f32)atan2(-(*(f32*)g_Ball - *(f32*)(r + 0)), -(*(f32*)(g_Ball + 8) - *(f32*)(r + 8)));
            }
            *(f32*)(r + 0x34) = v;
        }
    }
}

// .text:0x00088228 size:0x1E0 mapped:0x806C72BC
void fn_3_88228(void) {
    u8* q;
    s16 t;
    u8* f;
    int off;
    s16 a;
    s16 b86 = *(s16*)(g_Ball + 0x1B86);
    int ri;
    if (b86 >= 0 && (a = *(s16*)(g_Ball + 0x1B7A)) >= 0 && a != 3 && g_Fielders[*(s16*)(g_Ball + 0x1B78) * 0x268 + 0x1E7] == 0) {
        ri = (b86 + 3) & 3;
        off = ri * 0x154;
        q = g_Runners + off;
        if (*(s16*)(q += 0xEE) == 1) {
            fn_3_88D88(ri);
            *(s16*)q = 2;
            g_Runners[off + 0x12C] = 2;
            if (*(s16*)(g_Ball + 0x1B92) < 0) {
                t = *(s16*)(g_Ball + 0x1B94);
                if (t < 0) {
                    *(s16*)(g_Ball + 0x1B92) = *(s16*)(g_Ball + 0x1B78);
                } else {
                    *(s16*)(g_Ball + 0x1B92) = t;
                    if (g_FieldingLogic[0x141] != 0 && g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
                        f = g_Fielders;
                        f += t * 0x268;
                        fn_3_161588(8, *(s16*)(f + 0x178));
                    }
                    if ((s8)g_FieldingLogic[0x115] > 0 && g_FieldingLogic[0x133] != 0) {
                        g_UnkSound_32718[8] = 4;
                        t = *(s16*)(g_Ball + 0x1B90);
                        g_FieldingLogic[0x134] = t;
                        if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
                            f = g_Fielders;
                            f += t * 0x268;
                            fn_3_161588(2, *(s16*)(f + 0x178));
                        }
                    }
                }
            }
        }
    }
}

// .text:0x00088408 size:0x5F4 mapped:0x806C749C
void fn_3_88408(void) {
    return;
}

// .text:0x000889FC size:0x11C mapped:0x806C7A90
// 99%: only load order differs (lha of g_Ball+0x1B7A hoisted last instead of first)
void fn_3_889FC(void) {
    int i;

    for (i = 0; i < 4; i++) {
        s16 a = *(s16*)(g_Ball + 0x1B7A);
        if (g_Runners[i * 0x154 + 0x123] == 1) {
            if ((a == 3 || g_FieldingLogic[0x108] == 2) && g_Ball[0x1BBF] <= 1) {
                g_Runners[i * 0x154 + 0x132] = 0;
            } else if (g_Ball[0x1BBE] <= 1 && g_Ball[0x1BC9] != 0 && (u16)a > 1) {
                u8 t = g_Runners[i * 0x154 + 0x125];
                if (t != 0 && t < 3) {
                    g_Runners[i * 0x154 + 0x132] = 0;
                }
            }
        }
    }
}

// .text:0x00088B18 size:0x10C mapped:0x806C7BAC
void fn_3_88B18(void) {
    int i;
    u8* r;
    s16 t;
    int m;
    m = 0;
    if (g_FieldingLogic[0x107] != 0 && g_FieldingLogic[0x107] != 4) {
        m = 1;
    }
    r = g_Runners;
    for (i = 0; i < 4; i++, r += 0x154) {
        if (*(s16*)(r + 0xEE) == 2) {
            m = 2;
        } else {
            *(s16*)(r + 0xEE) = 0;
            if (*(s16*)(g_Ball + 0x1B7A) >= 0 && g_FieldingLogic[0x108] == 0) {
                if (m != 0) {
                    if (r[0x123] == 0) {
                        m = 1;
                    }
                    if (m == 2 && r[0x124] == r[0x125]) {
                        *(s16*)(r + 0xEE) = -1;
                    }
                } else if (r[0x123] == 1) {
                    t = *(s16*)(r + 0xE6);
                    if ((t < 0 || t != ((r[0x124] + 1) & 3)) && r[0x124] == r[0x125]) {
                        *(s16*)(r + 0xEE) = 1;
                    }
                } else {
                    m = 1;
                }
            }
        }
    }
}

// .text:0x00088C24 size:0x164 mapped:0x806C7CB8
// 90%: same hoisted-lha order issue as fn_3_889FC
void fn_3_88C24(void) {
    int i;
    fn_3_87AE8();
    if (g_GameLogic[0x121] == 6) {
        fn_3_87CC8();
    } else {
        fn_3_88408();
        fn_3_88B18();
        for (i = 0; i < 4; i++) {
            if (g_Runners[i * 0x154 + 0x123] == 1) {
                if ((*(s16*)(g_Ball + 0x1B7A) == 3 || g_FieldingLogic[0x108] == 2) && g_Ball[0x1BBF] <= 1) {
                    g_Runners[i * 0x154 + 0x132] = 0;
                } else if (g_Ball[0x1BBE] <= 1 && g_Ball[0x1BC9] != 0 && (u16) * (s16*)(g_Ball + 0x1B7A) > 1) {
                    u8 t = g_Runners[i * 0x154 + 0x125];
                    if (t != 0 && t < 3) {
                        g_Runners[i * 0x154 + 0x132] = 0;
                    }
                }
            }
        }
        fn_3_87E80();
    }
    fn_3_8781C();
}

// .text:0x00088D88 size:0x210 mapped:0x806C7E1C
// 98%: only r4/r5 swap between g_Strikes[2] value and idx*0x154 in the prologue
void fn_3_88D88(int idx) {
    u8* r = g_Runners;
    int k;
    r += idx * 0x154;
    if (g_Strikes[2] < 3 && g_GameLogic[0x127] == 0 && r[0x123] == 1) {
        if (g_GameLogic[0x14F] == 0) {
            g_Strikes[2] = g_Strikes[2] + 1;
        } else if ((g_Practice[0x193] == 2 && g_Practice[0x194] == 1) || g_Practice[0x194] == 7 || g_Practice[0x194] == 6) {
            g_Strikes[2]++;
        }
        if (g_Ball[0x1BCF] != 0 && g_Strikes[0] >= 3) {
            fn_3_59918(0x16, 0);
        } else if (*(f32*)(r + 0x64) >= lbl_3_rodata_14F8 && *(s16*)(g_Ball + 0x1B86) == 0) {
            fn_3_59918(1, 1);
        } else {
            fn_3_59918(1, 0);
        }
        {
            s16* p = (s16*)g_Strikes;
            for (k = 0; k < 3; p++, k++) {
                if (p[12] == -1) {
                    ((s16*)((u8*)g_Strikes + 0x18))[k] = idx;
                    break;
                }
            }
        }
        if (g_Strikes[2] == 3) {
            if (*(s16*)(r + 0xEE) == 1) {
                g_Strikes[4] = 1;
            } else {
                fn_3_5C74C(1);
            }
            fn_3_5D094(0);
            if (g_GameLogic[0x127] != 0) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
        r[0x123] = 2;
    }
}

// .text:0x00088F98 size:0x90 mapped:0x806C802C
void fn_3_88F98(void) {
    int i;
    RunnerT* rs = (RunnerT*)g_Runners;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            fn_3_85EF4(i, 1);
        }
        if (i == 0) {
            rs[i].b[0x12A] = 1;
        } else {
            rs[i].b[0x12A] = 0;
            if (g_Strikes[3] < 2) {
                rs[i].b[0x128] = 1;
            } else {
                rs[i].b[0x128] = 0;
            }
        }
    }
}

// .text:0x00089028 size:0xF4 mapped:0x806C80BC
void fn_3_89028(void) {
    int i;
    for (i = 0; i < 4; i++) {
        ((RunnerT*)g_Runners)[i].b[0x133] = 0;
    }
    for (i = 1; i < 4; i++) {
        ((RunnerT*)g_Runners)[i].b[0x12A] = 0;
        ((RunnerT*)g_Runners)[i].b[0x128] = 0;
        if (((RunnerT*)g_Runners)[i].b[0x123] == 1) {
            fn_3_85EF4(i, 1);
        }
    }
    if (g_Strikes[1] >= 4) {
        g_Runners[0x123] = 5;
    } else if (g_FieldingLogic[0x107] == 4) {
        g_Runners[0x123] = 1;
        fn_3_85EF4(0, 1);
    } else {
        g_Runners[0x123] = 4;
    }
}

// .text:0x0008911C size:0x20 mapped:0x806C81B0
void fn_3_8911C(void) {
    g_Runners[0x133] = 0;
    g_Runners[0x287] = 0;
    g_Runners[0x3DB] = 0;
    g_Runners[0x52F] = 0;
}

// .text:0x0008913C size:0x728 mapped:0x806C81D0
void fn_3_8913C(void) {
    return;
}

// .text:0x00089864 size:0x58 mapped:0x806C88F8
void fn_3_89864(s32 i, s32 d) {
    u8* r = g_Runners + i * 0x154;
    r[0x125] += d;
    r[0x126] = (r[0x125] + 1) & 3;
    if (r[0x125] < 4) {
        return;
    }
    r[0x123] = 3;
    *(s16*)(g_Scores + 0x9C) += 1;
}

// .text:0x000898BC size:0x58 mapped:0x806C8950
void fn_3_898BC(s32 i, s32 j) {
    u8* r = g_Runners + i * 0x154;
    *(s16*)(r + 0xE0) = j;
    r[0x11C] = inMemRoster[*(s32*)(g_GameLogic + 4) * 0x5A0 + j * 0xA0 + 0x26];
    if (r[0x11C] == 2) {
        r[0x11C] = 0;
    }
}

// .text:0x00089914 size:0xA8 mapped:0x806C89A8
void fn_3_89914(s32 a, s32 b) {
    u8* ra = g_Runners + a * 0x154;
    u8* rb = g_Runners + b * 0x154;
    if (a >= 0 && a <= 3) {
        if (*(u8*)(g_GameLogic + 0x121) == 0xF && a == 0) {
            *(s16*)(rb + 0xE0) = *(u8*)(g_Practice + 0x1EF);
        } else {
            *(s16*)(rb + 0xE0) = *(s16*)(ra + 0xE0);
            *(u8*)(rb + 0x11C) = *(u8*)(ra + 0x11C);
            *(u8*)(rb + 0x131) = *(u8*)(ra + 0x131);
            *(s16*)(rb + 0xFC) = *(s16*)(ra + 0xFC);
        }
        { u8* q = g_RunningLogic; q += a * 2; *(s16*)(q + 6) = b; }
        return;
    }
    *(s16*)(rb + 0xE0) = -1;
    *(u8*)(rb + 0x131) = 0;
    *(s16*)(rb + 0xFC) = -1;
}

// .text:0x000899BC size:0x81C mapped:0x806C8A50
void fn_3_899BC(void) {
    return;
}

// .text:0x0008A1D8 size:0x178 mapped:0x806C926C
// ~98%: loop regs match now; prologue differs (original loads the 0.0f via addi+lfs 0(r4) and copies i to r3 for the 0x133 stores)
void fn_3_8A1D8(void) {
    u8* r;
    int i;
    P2* p;
    for (i = 0, r = g_Runners, p = (P2*)lbl_3_data_4A34; i < 4; i++, r += 0x154, p++) {
        *(f32*)(r + 0x0) = p->x;
        *(f32*)(r + 0x8) = p->z;
        *(f32*)(r + 0x18) = 0.0f;
        *(f32*)(r + 0x1C) = 0.0f;
        *(f32*)(r + 0x20) = 0.0f;
        r[0x124] = i;
        r[0x125] = i;
        r[0x126] = (i + 1) & 3;
        *(s16*)(r + 0xE6) = i;
        r[0x127] = 0xFF;
        r[0x133] = 0;
    }
    if (g_GameLogic[0x121] != 0xC) {
        for (i = 1; i < 4; i++) {
            u8* r = g_Runners + i * 0x154;
            if (*(s16*)(r + 0xE0) >= 0) {
                fn_3_6D964(*(s16*)(r + 0xE0), i);
            } else {
                r[0x123] = 0;
            }
        }
    }
    {
        int a = *(int*)(g_GameLogic + 0xC);
        fn_3_6D964(*(int*)(g_GameLogic + a * 0x50 + *(int*)(g_GameLogic + a * 4 + 0xDC) * 8 + 0x3C), 0);
    }
}

// .text:0x0008A350 size:0x178 mapped:0x806C93E4
// ~97%: loop 1 regs now match (u32 a/b); loop 2 differs: extra `mr r8,r4` for the runner pointer, table/i regs (r5/r6 vs r6/r4) and lis order.
// Tried: index-form loop 2 / inlining fn_3_8A4E4 gets regs but folds offsets (no addi r8 between unrolled iterations); ~300 variants.
void fn_3_8A350(void) {
    int i;
    u8* r;
    f32* p;
    u8* q;
    u32 a = g_d_GameSettings[7];
    u32 b = g_d_GameSettings[0x39];
    for (i = 1; i < 4; i++) {
        r = g_Runners + i * 0x154;
        if (a != 5 || b != 1 || *(s16*)(r + 0xE0) < 0) {
            *(s16*)(r + 0xE0) = -1;
            r[0x11C] = 0;
            r[0x131] = 0;
            *(s16*)(r + 0xFC) = -1;
        }
    }
    g_RunningLogic[0x15] = 0;
    p = lbl_3_data_4A34;
    q = g_Runners;
    for (i = 0; i < 4; i++, q += 0x154, p += 2) {
        *(f32*)(q + 0x0) = p[0];
        *(f32*)(q + 0x8) = p[1];
        *(f32*)(q + 0x18) = 0.0f;
        *(f32*)(q + 0x1C) = 0.0f;
        *(f32*)(q + 0x20) = 0.0f;
        q[0x124] = i;
        q[0x125] = i;
        q[0x126] = (i + 1) & 3;
        *(s16*)(q + 0xE6) = i;
        q[0x127] = 0xFF;
        q[0x133] = 0;
    }
}

// .text:0x0008A4C8 size:0x1C mapped:0x806C955C

void fn_3_8A4C8(void) {
    *(f32*)g_Runners = *(f32*)g_Batter;
    *(f32*)(g_Runners + 8) = *(f32*)(g_Batter + 4);
}

// .text:0x0008A4E4 size:0xC0 mapped:0x806C9578
void fn_3_8A4E4(void) {
    int i;
    for (i = 0; i < 4; i++) {
        u8* r = ((RunnerT*)g_Runners)[i].b;
        *(f32*)(r + 0x0) = ((P2*)lbl_3_data_4A34)[i].x;
        *(f32*)(r + 0x8) = ((P2*)lbl_3_data_4A34)[i].z;
        *(f32*)(r + 0x18) = 0.0f;
        *(f32*)(r + 0x1C) = 0.0f;
        *(f32*)(r + 0x20) = 0.0f;
        r[0x124] = i;
        r[0x125] = i;
        r[0x126] = (i + 1) & 3;
        *(s16*)(r + 0xE6) = i;
        r[0x127] = 0xFF;
        r[0x133] = 0;
    }
}

// .text:0x0008A5A4 size:0x74 mapped:0x806C9638
void fn_3_8A5A4(void) {
    s8 i;
    for (i = 0; i < 4; i++) {
        u8* r = g_Runners + i * 0x154;
        *(s16*)(r + 0xE0) = -1;
        r[0x121] = 10;
        r[0x122] = 30;
        *(f32*)(r + 0xBC) = lbl_3_rodata_1498;
        r[0x14C] = 0;
    }
}

// .text:0x0008A618 size:0x19C mapped:0x806C96AC
// ~98%: shape matches; only regs of hoisted constants/temps differ (orig: temp r3, m r4, 1->r0, 0->r6; ours: temp r4, m r6, 1->r3, 0->r0). ~100 variants tried.
void fn_3_8A618(void) {
    int i;
    u8* r;
    u8 m;
    if ((g_GameLogic[0x11E] != 2 || *(u16*)(g_GameLogic + 0xFC) >= *(u8*)(g_RunningLogic + 0x14) || g_GameLogic[0x121] == 0xE ||
         g_FieldingLogic[0x107] != 0) &&
        g_FieldingLogic[0x10E] == 0) {
        if (g_GameLogic[*(int*)(g_GameLogic + 0xC) + 0x148] == 0) {
            fn_3_7E2BC();
        } else {
            fn_3_83714();
        }
        m = g_FieldingLogic[0x107];
        r = g_Runners;
        for (i = 0; i < 4; i++, r += 0x154) {
            if (r[0x123] != 0) {
                if (m == 1 && r[0x14E] != 0 && *(s16*)(r + 0xE0) >= 0) {
                    r[0x135] = 1;
                }
                r[0x14E] = 0;
            }
        }
    }
}

// .text:0x0008A7B4 size:0x1A4 mapped:0x806C9848
void fn_3_8A7B4(void) {
    int i;
    u8* c;
    u8 p;
    int idx;
    if (g_GameLogic[*(int*)(g_GameLogic + 0xC) + 0x148] != 0) {
        fn_3_85CB0();
    } else {
        idx = *(int*)(g_GameLogic + 4);
        c = g_Controls + *(int*)(g_GameLogic + idx * 4 + 0xEC) * 16;
        p = g_Pitcher[0x13E];
        if (!(p != 1 && p != 2 && p != 3)) {
            if (g_d_GameSettings[7] == 2 && (s8)g_Practice[0x1C2] >= 0) {
                c = g_Practice + idx * 16;
            }
            if (*(u16*)(c + 6) & 0x800) {
                if (*(s16*)c < 0) {
                    for (i = 1; i < 4; i++) {
                        if (g_Runners[i * 0x154 + 0x123] != 0 && g_Runners[i * 0x154 + 0x14E] == 0) {
                            g_Runners[i * 0x154 + 0x14E] = 1;
                        }
                    }
                } else {
                    if (*(s16*)c >= 0x1C0 && *(s16*)c <= 0x640) {
                        g_Runners[0x2A2] = 1;
                    }
                    if (*(s16*)c >= 0x5C0 && *(s16*)c <= 0xA40) {
                        g_Runners[0x3F6] = 1;
                    }
                    if (*(s16*)c >= 0x9C0 && *(s16*)c <= 0xE40) {
                        g_Runners[0x54A] = 1;
                    }
                }
            }
        }
    }
    fn_3_86EF8();
}

// .text:0x0008A958 size:0x73C mapped:0x806C99EC
void fn_3_8A958(void) {
    return;
}

#pragma dont_inline off
