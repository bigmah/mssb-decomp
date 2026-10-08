#include "game/rep_E08.h"
#include "header_rep_data.h"
#include "math.h"

#pragma dont_inline on

extern u8 g_Fielders[];
extern u8 g_Runners[];
extern u8 g_Minigame[];
extern u8 g_GameLogic[];
extern u8 lbl_3_data_7870[];
extern u8 lbl_3_common_bss_321A0[];

extern u8 g_Ball[];
extern u8 g_FieldingLogic[];
extern u8 g_Pitcher[];
extern u8 g_UnkThrowing_31ACC[];
extern u8 g_d_GameSettings[];
extern u8 lbl_8036E548[];
extern u8 g_UnkAnimation_31EAC[];
extern int fn_3_9FB8C(f32 x, f32 y);
extern int fn_3_9FCA4(s16 a, s16 b);
extern int radToShortAngle(f32 v);
extern u8 lbl_3_data_7E34[];
extern u8 lbl_3_data_7D24[];
extern f32 shortAngleToRad_Capped(s16 a);
extern u32 fn_3_90220(s32 idx, s32 off);
extern int getAnimRelatedCoordinates(int, int, f32*);
extern void fn_8001B4D8(void);
extern const f32 lbl_3_rodata_E58;
extern const f64 lbl_3_rodata_E60;
extern const f64 lbl_3_rodata_E68;
extern const f64 lbl_3_rodata_E70;
static inline f32 sqrt_E08(f32 x) {
    if (x > lbl_3_rodata_E58) {
        f64 h = lbl_3_rodata_E60;
        f64 th = lbl_3_rodata_E68;
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = h * guess * (th - guess * guess * xd);
        guess = h * guess * (th - guess * guess * xd);
        guess = h * guess * (th - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (x < lbl_3_rodata_E70)
        return NAN;
    else if (isnan(x))
        return NAN;
    else
        return x;
}
extern void AnimateCharacter(int, int, int, int, int, int, u8, int);
extern void QueueCharacterAnimation(int, int, int, int, int, u8, int);

// .text:0x00060768 size:0x9C mapped:0x8069F7FC
void fn_3_60768(void) {
    int i;
    for (i = 0; i < 4; i++) {
        u8* e = *(u8**)(lbl_8036E548 + 0x60) + i * 0x90;
        *(s32*)(e + 0x38) = 0;
        *(s16*)(e + 0x42) = 0;
        *(f32*)(e + 0x90) = 0.0f;
        e[0x8C] = 1;
        e[0x8D] = 0;
        e[0x8E] = 0;
        *(f32*)(e + 0x94) = 0.0f;
    }
}

// .text:0x00060804 size:0x294 mapped:0x8069F898
void fn_3_60804(s32 a, s32 b) {
    s32 k = a;
    u8* e = g_UnkAnimation_31EAC + a * 0x54;
    u8* f = g_Fielders + a * 0x268;
    u8* o;
    if (g_d_GameSettings[0x11] != 0) {
        if (a == 0) {
            u8* m = g_Minigame;
            m += *(s8*)(m + 0x1904);
            k = *(s8*)(m + 0x18CC);
        } else {
            k = *(s8*)(g_Minigame + a + 0x18F2);
        }
    }
    o = ((u8**)(lbl_8036E548 + 0x2C50))[k];
    if (o != NULL) {
        if (b == 0) {
            if (e[0x42] == 1) {
                f32 d;
                e[0x42] = 0;
                getAnimRelatedCoordinates(k, 4, (f32*)(e + 0x2C));
                *(f32*)(f + 0x30) = *(f32*)(e + 0x2C) - *(f32*)(f + 0);
                *(f32*)(f + 0x34) = *(f32*)(e + 0x34) - *(f32*)(f + 8);
                d = sqrt_E08(*(f32*)(f + 0x30) * *(f32*)(f + 0x30) + *(f32*)(f + 0x34) * *(f32*)(f + 0x34));
                *(f32*)(f + 0x50) = d;
                *(f32*)(f + 0) = *(f32*)(e + 0x2C);
                *(f32*)(f + 8) = *(f32*)(e + 0x34);
                e[0x48] = 1;
            }
        } else {
            if (e[0x42] == 0) {
                fn_8001B4D8();
                if (e[0x48] == 1) {
                    *(f32*)(e + 0x10) = *(f32*)(e + 0x2C);
                    *(f32*)(e + 0x18) = *(f32*)(e + 0x34);
                } else {
                    *(f32*)(e + 0x10) = *(f32*)(o + 0x34);
                    *(f32*)(e + 0x18) = *(f32*)(o + 0x3C);
                }
                e[0x42] = 1;
            } else {
                f32 v[3];
                getAnimRelatedCoordinates(k, 4, v);
                *(f32*)(e + 0x10) = *(f32*)(o + 0x34) = v[0];
                *(f32*)(e + 0x18) = *(f32*)(o + 0x3C) = v[2];
            }
        }
    }
}

// .text:0x00060A98 size:0x2E8 mapped:0x8069FB2C
void fn_3_60A98(void) {
    return;
}

// .text:0x00060D80 size:0x110 mapped:0x8069FE14
void fn_3_60D80(void) {
    return;
}

// .text:0x00060E90 size:0x2B8 mapped:0x8069FF24
u32 fn_3_60E90(s32 a) {
    s32 k = a;
    u8* e = g_UnkAnimation_31EAC + a * 0x54;
    u8 st;
    u8* o;
    u8* f = g_Fielders + a * 0x268;
    s16 oa;
    if (g_d_GameSettings[0x11] != 0) {
        if (a == 0) {
            u8* m = g_Minigame;
            m += *(s8*)(m + 0x1904);
            k = *(s8*)(m + 0x18CC);
        } else {
            k = *(s8*)(g_Minigame + a + 0x18F2);
        }
    }
    st = e[0x51];
    o = ((u8**)(lbl_8036E548 + 0x2C50))[k];
    oa = *(s16*)(o + 0x62);
    if (st != 9 && *(s16*)(g_Ball + 0x1B78) != a) {
        e[0x44] = 0;
        return 0;
    }
    if (st == 9) {
        return 1;
    }
    if (e[0x44] != 0 && g_UnkThrowing_31ACC[0x10] == 0) {
        if (st == 8 && f[0x212] == 3) {
            if (oa != 0x24) {
                fn_3_90220(*(s16*)(f + 0x17A), 10);
            }
            e[0x51] = 9;
            AnimateCharacter(k, 0x24, 0, 1, 0, 0, e[0x40], 0);
            QueueCharacterAnimation(k, 0x25, 0, 1, 0, e[0x40], 0);
            fn_3_60804(a, 0);
            return 1;
        }
        if (*(s16*)(o + 0x68) <= 0) {
            e[0x44] = 0;
            e[0x51] = 0;
            fn_3_60804(a, 0);
            return 0;
        }
        return 1;
    }
    if (st == 0 || st == 4) {
        goto clear;
    }
    if (st == 8) {
        s32 x = (s8)o[0x252] * 4;
        if (lbl_3_data_7E34[x + 1] - *(s16*)(g_FieldingLogic + 0xF6) < 0) {
            goto clear;
        }
        AnimateCharacter(k, 0x23, 0, 1, 1, lbl_3_data_7E34[x], e[0x40], -1);
        e[0x44] = 1;
    } else {
        AnimateCharacter(k, 0x21, 0, 1, 0, lbl_3_data_7E34[(s8)o[0x252] * 4], e[0x40], -1);
        e[0x44] = 1;
    }
    fn_3_60804(a, 0);
    return 1;
clear:
    e[0x44] = 0;
    return 0;
}

// .text:0x00061148 size:0xE0 mapped:0x806A01DC
u32 fn_3_61148(s32 i) {
    u8* e = g_UnkAnimation_31EAC + i * 0x54;
    s32 k = i;
    u8* o;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            u8* m = g_Minigame;
            m += *(s8*)(m + 0x1904);
            k = *(s8*)(m + 0x18CC);
        } else {
            k = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    o = ((u8**)(lbl_8036E548 + 0x2C50))[k];
    if (o == NULL) {
        return 0;
    }
    if (e[0x43] != 0) {
        if (*(s16*)(o + 0x68) <= 0) {
            e[0x43] = 0;
            fn_3_60804(i, 0);
            return 0;
        }
        return 1;
    }
    return 0;
}

// .text:0x00061228 size:0x31C mapped:0x806A02BC
u32 fn_3_61228(s32 a) {
    s16 t;
    u8* tb;
    s32 oa;
    u8* o;
    s32 k = a;
    u8* e = g_UnkAnimation_31EAC + a * 0x54;
    u8* thr = g_UnkThrowing_31ACC;
    u8* f = g_Fielders + a * 0x268;
    s32 vv = 0x1D;
    s32 flag = 0;
    u8* fl = g_FieldingLogic;
    s16 ang;
    s32 adj;
    s16 d;
    if (g_d_GameSettings[0x11] != 0) {
        if (a == 0) {
            u8* m = g_Minigame;
            m += *(s8*)(m + 0x1904);
            k = *(s8*)(m + 0x18CC);
        } else {
            k = *(s8*)(g_Minigame + a + 0x18F2);
        }
    }
    o = ((u8**)(lbl_8036E548 + 0x2C50))[k];
    if (o == NULL) {
        return 0;
    }
    if (*(s16*)(thr + 0xC) != a) {
        return 0;
    }
    if (e[0x43] != 0) {
        if (f[0x1D3] == 0x11) {
            e[0x43] = 0;
            fn_3_60804(a, 0);
            return 0;
        }
        t = *(s16*)(o + 0x6A);
        if (t > 0 && *(s16*)(o + 0x68) <= 0) {
            e[0x43] = 0;
            fn_3_60804(a, 0);
            return 0;
        }
        tb = lbl_3_data_7D24 + (s8)o[0x252] * 5;
        oa = *(s16*)(o + 0x62);
        if (t >= *(u8*)(oa - 0x1D + tb)) {
            fl[0x10A] = 1;
        }
        return 1;
    }
    if (f[0x215] != 0) {
        return 0;
    }
    if (thr[0xE] != 0) {
        switch (thr[0xE]) {
        case 2:
            vv = 0x1E;
            break;
        case 3:
            vv = 0x1F;
            break;
        case 4:
            vv = 0x1D;
            break;
        case 5:
            vv = 0x1D;
            break;
        case 6:
            vv = 0x1D;
            break;
        case 7:
            vv = 0x1D;
            flag = 1;
            break;
        }
        if (flag != 0) {
            ang = radToShortAngle(*(f32*)(f + 0x48));
            d = fn_3_9FCA4(ang, fn_3_9FB8C(*(f32*)(thr + 0) - *(f32*)(f + 0), *(f32*)(thr + 8) - *(f32*)(f + 8)));
            adj = -d;
            if (d < -0x600 || d > 0x600) {
                if (d < -0x600) {
                    adj = -0x800 - d;
                } else {
                    adj = 0x800 - d;
                }
            } else if (d > 0x200) {
                adj = 0x400 - d;
            } else if (d < -0x200) {
                adj = -0x400 - d;
            }
            *(f32*)(f + 0x48) = shortAngleToRad_Capped((s16)(ang + adj));
        }
        AnimateCharacter(k, vv, 0, 1, 1, 0, e[0x40], -1);
        thr[0xF] = vv;
        e[0x43] = 1;
        if (flag != 0) {
            e[0x43] = 2;
        }
        e[0x4C] = 0;
        e[0x4F] = 0;
        e[0x47] = 0;
        e[0x46] = 0;
        e[0x50] = 0;
        fn_3_60804(a, 1);
        return 1;
    }
    return 0;
}

// .text:0x00061544 size:0x620 mapped:0x806A05D8
void fn_3_61544(void) {
    return;
}

// .text:0x00061B64 size:0xDA0 mapped:0x806A0BF8
void fn_3_61B64(s32 i) {
    return;
}

// .text:0x00062904 size:0x24C mapped:0x806A1998
void fn_3_62904(void) {
    int i;
    u8* p;
    s16 bs;
    u8* a;
    u8* f;
    u8 v;
    s16 ang;
    s16 d;
    if (g_d_GameSettings[0x11] != 0) {
        return;
    }
    p = g_Fielders;
    for (i = 0; i < 9; p += 0x268, i++) {
        if (p[0x211] != 0) {
            if (g_Fielders[i * 0x268 + 0x211] != 0) {
                u8* q = (u8*)((u32)g_UnkAnimation_31EAC + 0x51 + i * 0x54);
                if (*q != 8 && *q != 9) {
                    *q = 8;
                }
            }
            break;
        }
    }
    bs = *(s16*)(g_Ball + 0x1B78);
    if (bs < 0 || g_FieldingLogic[0x111] == 0) {
        return;
    }
    f = g_Fielders + bs * 0x268;
    a = g_UnkAnimation_31EAC + bs * 0x54;
    if (g_FieldingLogic[0x135] != 0) {
        *(s16*)(f + 0x1AA) = 0;
    }
    g_UnkThrowing_31ACC[0x10] = g_FieldingLogic[0x135];
    if (g_FieldingLogic[0x111] == 1) {
        v = 1;
        if (*(s16*)(g_FieldingLogic + 0xE8) >= 0) {
            ang = fn_3_9FB8C(*(f32*)(g_FieldingLogic + 0x90) - *(f32*)(f + 0), *(f32*)(g_FieldingLogic + 0x98) - *(f32*)(f + 8));
            d = fn_3_9FCA4(ang, radToShortAngle(*(f32*)(f + 0x48)));
            if (d < -0x280) {
                v = 2;
            } else if (d > 0x280) {
                v = 3;
            }
        }
        a[0x51] = v;
    } else if (g_FieldingLogic[0x111] == 2) {
        a[0x51] = 4;
    } else if (g_FieldingLogic[0x111] == 5) {
        s16 ri;
        v = 5;
        ri = *(s16*)(g_FieldingLogic + 0xE8);
        if (ri >= 0) {
            u8* r = g_Runners + ri * 0x154;
            ang = fn_3_9FB8C(*(f32*)(r + 0) - *(f32*)(f + 0), *(f32*)(r + 8) - *(f32*)(f + 8));
            d = fn_3_9FCA4(ang, radToShortAngle(*(f32*)(f + 0x48)));
            if (d < -0x1C0) {
                v = 7;
            } else if (d > 0x1C0) {
                v = 6;
            }
        }
        a[0x51] = v;
    }
}

// .text:0x00062B50 size:0x158 mapped:0x806A1BE4
#define BALL_S (*(s16*)(g_Ball + 0x1B78))
#define FL_C4 (*(s16*)(g_FieldingLogic + 0xC4))
#define THR_E (g_UnkThrowing_31ACC[0xE])
void fn_3_62B50(void) {
    s16 bs = BALL_S;
    if (bs < 0) {
        THR_E = 0;
        return;
    }
    if (FL_C4 < 0) {
        THR_E = 0;
        return;
    }
    if (THR_E == 0) {
        g_FieldingLogic[0x10A] = 0;
        *(f32*)(g_UnkThrowing_31ACC + 0) = *(f32*)(g_Ball + 0x19EC);
        *(f32*)(g_UnkThrowing_31ACC + 4) = *(f32*)(g_Ball + 0x19F0);
        *(f32*)(g_UnkThrowing_31ACC + 8) = *(f32*)(g_Ball + 0x19F4);
        if (g_FieldingLogic[0x107] == 1 && bs == 0 && (FL_C4 == 1 || FL_C4 == 2 || FL_C4 == 3) &&
            *(s16*)(g_Pitcher + 0x12E) != 4 && *(s16*)(g_Pitcher + 0x12E) != -1) {
            THR_E = 7;
            return;
        }
        if (g_FieldingLogic[0x106] == 8) {
            THR_E = 3;
        } else if (g_FieldingLogic[0x106] == 9) {
            THR_E = 4;
        } else if (g_FieldingLogic[0x106] == 10) {
            if (bs == 3) {
                THR_E = 5;
            } else {
                THR_E = 6;
            }
        } else if (g_FieldingLogic[0x109] != 0) {
            THR_E = 2;
        } else {
            THR_E = 1;
        }
    }
}

// .text:0x00062CA8 size:0x9C mapped:0x806A1D3C
void fn_3_62CA8(int i) {
    u8 t;
    u8* o;
    u8* f;
    u8* a = g_UnkAnimation_31EAC + i * 0x54;
    f = g_Fielders + i * 0x268;
    o = ((u8**)(lbl_8036E548 + 0x2C50))[i];
    if (a[0x4C] == 0) {
        t = f[0x252];
        a[0x4C] = t;
        *(s16*)(a + 0x4A) = *(s16*)(f + 0x24C);
        if (t == 1 || t == 2) {
            a[0x4E] = f[0x253];
        }
        if (a[0x4C] != 0) {
            a[0x4D] = a[0x4C];
        }
    }
    if (o != NULL && *(s16*)(o + 0x62) == 0x24) {
        a[0x4C] = 0;
        a[0x4F] = 0;
    }
}

// .text:0x00062D44 size:0xC0 mapped:0x806A1DD8
void fn_3_62D44(s32 i) {
    u8 t;
    u8* f = g_Fielders + i * 0x268;
    u8* e = g_UnkAnimation_31EAC + i * 0x54;
    t = f[0x1E5];
    e[0x41] = 0;
    if (t == 2) {
        e[0x41] = 1;
    } else if (t == 3) {
        e[0x41] = 2;
    }
    if (f[0x256] != 0 && *(s16*)(g_Ball + 0x1B7A) == 0 && *(f32*)(f + 0x248) < *(f32*)(f + 0xE8) &&
        *(s16*)(g_Ball + 0x1B60) < 0x78 && *(f32*)(g_Ball + 0x19D4) > 5.0f && g_FieldingLogic[0x144] != 0) {
        e[0x45] = 1;
    }
}

// .text:0x00062E04 size:0x24 mapped:0x806A1E98
void fn_3_62E04(s32 i) {
    u8* e = g_UnkAnimation_31EAC + i * 0x54;
    *(s16*)(e + 0x3A) = *(s16*)(e + 0x38);
    *(s16*)(e + 0x38) = 0;
}

// .text:0x00062E28 size:0x48 mapped:0x806A1EBC
void fn_3_62E28(void) {
    AnimateCharacter(1, 0x3D, 1, 1, 1, 0, g_Fielders[0x42F], 0);
}

// .text:0x00062E70 size:0x33C mapped:0x806A1F04
void fn_3_62E70(void) {
    s32 i;
    s32 j;
    s16 bs;
    *(s16*)(g_UnkThrowing_31ACC + 0xC) = *(s16*)(g_Ball + 0x1B78);
    bs = *(s16*)(g_UnkThrowing_31ACC + 0xC);
    if (bs >= 0 && g_Fielders[bs * 0x268 + 0x203] != 0) {
        *(s16*)(g_UnkThrowing_31ACC + 0xC) = -1;
    }
    if (g_Minigame[0x1A2A] == 0) {
        fn_3_62B50();
        fn_3_62904();
    }
    for (i = 0; i < 9; i++) {
        u8* f = g_Fielders + i * 0x268;
        u8* e = g_UnkAnimation_31EAC + i * 0x54;
        u8* o;
        u8 t;
        e[0x40] = f[0x1C7];
        if (g_d_GameSettings[0x11] != 0) {
            for (j = 0; j < 4; j++) {
                if (*(s8*)(g_Minigame + j + 0x18F8) == i) {
                    break;
                }
            }
            if (j >= 4) {
                continue;
            }
        }
        if (g_Minigame[0x1A2A] == 2 && *(s8*)(f + 0x20D) == *(s8*)(g_Minigame + 0x1904) && g_Minigame[0x1A7E] == 0) {
            continue;
        }
        if (i == 0) {
            t = g_GameLogic[0x11E];
            if (t == 1) {
                continue;
            }
            if (t == 0) {
                continue;
            }
            if (t == 2 && g_FieldingLogic[0x117] != 0) {
                continue;
            }
            if (t == 0xB || t == 0x16) {
                continue;
            }
        }
        if (i == 1 && (g_GameLogic[0x11E] == 1 || g_GameLogic[0x11E] == 0 || g_GameLogic[0x11E] == 0xB)) {
            AnimateCharacter(1, 0x3D, 1, 1, 1, 0, g_Fielders[0x42F], 0);
            continue;
        }
        *(f32*)e = *(f32*)(f + 0x50);
        e[0x45] = 0;
        o = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
        if (e[0x4C] == 0) {
            t = f[0x252];
            e[0x4C] = t;
            *(s16*)(e + 0x4A) = *(s16*)(f + 0x24C);
            if (t == 1 || t == 2) {
                e[0x4E] = f[0x253];
            }
            if (e[0x4C] != 0) {
                e[0x4D] = e[0x4C];
            }
        }
        if (o != NULL && *(s16*)(o + 0x62) == 0x24) {
            e[0x4C] = 0;
            e[0x4F] = 0;
        }
        t = f[0x1E5];
        *(s16*)(e + 0x3A) = *(s16*)(e + 0x38);
        *(s16*)(e + 0x38) = 0;
        e[0x41] = 0;
        if (t == 2) {
            e[0x41] = 1;
        } else if (t == 3) {
            e[0x41] = 2;
        }
        if (f[0x256] != 0 && *(s16*)(g_Ball + 0x1B7A) == 0 && *(f32*)(f + 0x248) < *(f32*)(f + 0xE8) &&
            *(s16*)(g_Ball + 0x1B60) < 0x78 && *(f32*)(g_Ball + 0x19D4) > 5.0f && g_FieldingLogic[0x144] != 0) {
            e[0x45] = 1;
        }
        fn_3_61B64(i);
    }
}

// .text:0x000631AC size:0x6C8 mapped:0x806A2240
void fn_3_631AC(s32 a) {
    return;
}

// .text:0x00063874 size:0x1C4 mapped:0x806A2908
void fn_3_63874(s32 a) {
    u8* r = g_Runners + a * 0x154;
    u8* c = lbl_3_common_bss_321A0 + (a << 5);
    u8 t;
    if (g_GameLogic[0x121] == 6 && g_Minigame[a + 0x1B15] == 1) {
        c[0x1B] = 0x11;
        return;
    }
    if (r[0x129] != 0) {
        c[0x1B] = 1;
        return;
    }
    if (r[0x13A] != 0) {
        c[0x1B] = 8;
        return;
    }
    t = r[0x140];
    if (t >= 2) {
        if (t == 2) {
            c[0x1B] = 9;
            return;
        }
        c[0x1B] = 0xA;
        return;
    }
    t = r[0x142];
    if (t >= 2) {
        if (t == 2) {
            c[0x1B] = 0xB;
            return;
        }
        c[0x1B] = 0xC;
        return;
    }
    t = r[0x145];
    if (t == 1) {
        c[0x1B] = 0xD;
        return;
    }
    if (t != 0) {
        c[0x1B] = 0xE;
        return;
    }
    t = r[0x133];
    if (t == 1) {
        c[0x1B] = 0xF;
        return;
    }
    if (t == 2) {
        c[0x1B] = 0x10;
        return;
    }
    if (r[0x147] != 0) {
        c[0x1B] = 5;
        return;
    }
    t = r[0x137];
    if (t == 1 || t == 3) {
        if (r[0x148] != 0 && *(s16*)(r + 0x112) < *(s16*)(lbl_3_data_7870 + *(s16*)(r + 0xE2) * 6)) {
            c[0x1B] = 7;
            return;
        }
        c[0x1B] = 2;
        return;
    }
    if (*(s16*)(r + 0xE6) >= 0) {
        c[0x1B] = 3;
        return;
    }
    c[0x1B] = 4;
}

// .text:0x00063A38 size:0xC0 mapped:0x806A2ACC
typedef struct { u8 d[0x154]; } E08Run;
typedef struct { u8 d[0x20]; } E08C;
void fn_3_63A38(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        u8* r = ((E08Run*)g_Runners)[i].d;
        u8* c = ((E08C*)lbl_3_common_bss_321A0)[i].d;
        c[0x1C] = c[0x1B];
        if (g_d_GameSettings[0x11] == 0 || (s8)g_Minigame[0x18FC + i] >= 0) {
            if (r[0x123] == 0) {
                c[0x1B] = 0;
            } else {
                c[0x1B] = 3;
                *(f32*)c = *(f32*)(r + 0x84);
                c[0x1D] = r[0x137];
                fn_3_63874(i);
                fn_3_631AC(i);
            }
        }
    }
}

// .text:0x00063AF8 size:0x10E4 mapped:0x806A2B8C
void fn_3_63AF8(void) {
    return;
}

// .text:0x00064BDC size:0xC08 mapped:0x806A3C70
void fn_3_64BDC(void) {
    return;
}

// .text:0x000657E4 size:0x7FC mapped:0x806A4878
void fn_3_657E4(void) {
    return;
}

// .text:0x00065FE0 size:0x160 mapped:0x806A5074
void fn_3_65FE0(void) {
    return;
}

// .text:0x00066140 size:0x3BC mapped:0x806A51D4
void fn_3_66140(void) {
    return;
}

// .text:0x000664FC size:0x3C0 mapped:0x806A5590
void fn_3_664FC(void) {
    return;
}

// .text:0x000668BC size:0x874 mapped:0x806A5950
void fn_3_668BC(void) {
    return;
}

// .text:0x00067130 size:0x1C mapped:0x806A61C4
extern u8 lbl_3_common_bss_32220[];

void fn_3_67130(void) {
    lbl_3_common_bss_32220[8] = 0;
    lbl_3_common_bss_32220[0xB] = 0;
    *(s16*)(lbl_3_common_bss_32220 + 4) = 0;
}

// .text:0x0006714C size:0x394 mapped:0x806A61E0
void fn_3_6714C(void) {
    return;
}


#pragma dont_inline off
