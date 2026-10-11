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
extern void fn_8001B5EC(s32 index, s32 enable);
extern int fn_3_B7CDC(f32 a, f32 b);
extern int fn_3_B7E10(f32 a, f32 b);
extern f32 charSizeMultipliers[][2];
extern s16 lbl_3_data_7F10[];
extern f32 lbl_3_data_476C[];
extern const f32 lbl_3_rodata_E78;
extern BOOL checkFieldingStat(int, int, int);
extern void fn_8004AE18(s32 idx);
extern u8 lbl_3_data_7F0C;
extern s32 g_Strikes[];
extern u8 lbl_80353A90[];
extern u8 lbl_3_common_bss_32234[];
extern u32 fn_3_90150(s32 a, s32 b);
extern u8 lbl_800E8558[];
extern u8 lbl_3_data_7760[];
extern void playSoundEffect(int);
extern const f32 lbl_3_rodata_E88;
extern const f32 lbl_3_rodata_E8C;
extern const f32 lbl_3_rodata_E90;
// Fielder animation timing table (0x70 bytes).
typedef struct {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ u8 u10;
    /*0x11*/ u8 _11[0x40 - 0x11];
    /*0x40*/ u8 u40[2];
    /*0x42*/ u8 _42[0x54 - 0x42];
    /*0x54*/ s16 anims[3][3];
    /*0x66*/ u8 _66[2];
    /*0x68*/ u8 u68;
    /*0x69*/ u8 _69[3];
    /*0x6C*/ s16 windup[2];
} E08AnimTable;
extern E08AnimTable lbl_3_data_65F0;
extern const f32 lbl_3_rodata_E7C;
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
// NONMATCHING 97%: r29/r30 (anim/a) and f1-f4 swapped (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_3_60A98(s32 a, u8* o) {
    u8* f;
    s16 anim;
    u8* e;
    f32 dx;
    f32 dz;
    f32 d;
    f32 sx;
    f32 sz;
    e = g_UnkAnimation_31EAC + a * 0x54;
    f = g_Fielders + a * 0x268;
    if (o == NULL) {
        return;
    }
    anim = *(s16*)(o + 0x62); // original reads this before the NULL check
    if (*(f32*)(f + 0xA8) < lbl_3_rodata_E78 && fn_3_B7E10(*(f32*)(f + 0), *(f32*)(f + 8)) == 0) {
        return;
    }
    dz = *(f32*)(f + 8) - *(f32*)(e + 0x18);
    dx = *(f32*)(f + 0) - *(f32*)(e + 0x10);
    d = sqrt_E08(dx * dx + dz * dz);
    if (d <= lbl_3_rodata_E58) {
        return;
    }
    sx = dx / d;
    sz = dz / d;
    if (anim == 0x1A || anim == 0x1B) {
        s16 c = *(s16*)(f + 0x17A);
        f32 m = lbl_3_rodata_E7C * (f32)(lbl_3_data_7F10[c] + 0x1E) * charSizeMultipliers[c][0];
        sx *= m;
        sz *= m;
    } else {
        f32 m = lbl_3_data_476C[f[0x1C9]];
        sx *= m;
        sz *= m;
    }
    if (fn_3_B7CDC(sx + *(f32*)(f + 0), sz + *(f32*)(f + 8)) != 0) {
        fn_3_60804(a, 0);
        if (g_d_GameSettings[0x11] != 0) {
            if (a == 0) {
                u8* m = g_Minigame;
                m += *(s8*)(m + 0x1904);
                a = *(s8*)(m + 0x18CC);
            } else {
                a = *(s8*)(g_Minigame + a + 0x18F2);
            }
        }
        fn_8001B5EC(a, 0);
        *(f32*)(f + 0) = *(f32*)(f + 0xD4);
        *(f32*)(f + 8) = *(f32*)(f + 0xD8);
        f[0x1FB] = 0;
    }
}
#endif

// .text:0x00060D80 size:0x110 mapped:0x8069FE14
s32 fn_3_60D80(s32 a) {
    u8* e;
    s32 k;
    s16 anim;
    s16 st;
    e = g_UnkAnimation_31EAC + a * 0x54;
    k = *(s8*)(g_Minigame + a + 0x18F2);
    anim = *(s16*)(((u8**)(lbl_8036E548 + 0x2C50))[k] + 0x62);
    st = *(s16*)(g_Minigame + k * 2 + 0x1B34);
    if (st < 0) {
        if (anim == 0x1D || anim == 0x1F) {
            AnimateCharacter(k, 0, 1, 3, 0, 0, e[0x40], -1);
        }
        return 0;
    }
    if (st == 0) {
        s32 c = g_Minigame[k + 0x1C92];
        if (c == 3) {
            AnimateCharacter(k, 0x1F, 0, 3, 0, 0, e[0x40], -1);
        } else {
            AnimateCharacter(k, 0x1D, 0, 3, 0, 0, e[0x40], -1);
        }
    }
    return 1;
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
// NONMATCHING 92%: original reads the 65F0 table rows through addi base pointers; e/o regs swapped
#if NONMATCHING
u32 fn_3_61544(s32 a) {
    s32 anim = -1;
    s32 k = a;
    u8* f = g_Fielders + a * 0x268;
    u8* e = g_UnkAnimation_31EAC + a * 0x54;
    E08AnimTable* tbl = &lbl_3_data_65F0;
    s32 delay = 0;
    u8* o;
    s32 v;
    u8 t;
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
    if (e[0x43] != 0) {
        return 0;
    }
    if (e[0x4F] == 0) {
        if (f[0x20F] != 0) {
            return 0;
        }
        if (f[0x210] != 0) {
            return 0;
        }
        if (f[0x207] != 0) {
            return 0;
        }
        if (e[0x4C] != 0) {
        (*(s16*)(e + 0x4A))--;
        t = e[0x4C];
        if (t == 1 || t == 2) {
            s16 cur = *(s16*)(e + 0x4A);
            s16 lim = tbl->windup[0];
            if (cur <= lim) {
                t = f[0x254];
                if (t == 0) {
                    anim = tbl->anims[0][e[0x4E]];
                } else if ((t == 1 && f[0x1C7] == 0) || (t == 2 && f[0x1C7] != 0)) {
                    anim = tbl->anims[1][e[0x4E]];
                } else {
                    anim = tbl->anims[2][e[0x4E]];
                }
                delay = lim - cur;
            }
        } else if (t == 7 || t == 8) {
            t = f[0x261];
            if (t == 1) {
                if (e[0x40] != 0) {
                    v = 0xE;
                } else {
                    v = 0xD;
                }
            } else if (t == 2) {
                if (e[0x40] != 0) {
                    v = 0xD;
                } else {
                    v = 0xE;
                }
            } else {
                v = 0xC;
            }
            AnimateCharacter(k, v, 1, 1, 0, 0, e[0x40], -1);
            e[0x46] = v;
            e[0x4F] = 1;
            return 1;
        } else if (t == 3) {
            s16 cur = *(s16*)(e + 0x4A);
            s16 lim = tbl->windup[1];
            if (cur <= lim) {
                delay = lim - cur;
                anim = 0x1B;
            }
        } else if (t == 4) {
            AnimateCharacter(k, 0x26, 0, 1, 0, (s16)(lbl_3_data_7F0C - f[0x25C]), e[0x40], -1);
            e[0x46] = 0x26;
            e[0x4F] = 1;
            return 1;
        } else if (t == 5) {
            anim = 0x29;
            delay = tbl->u10 - *(s16*)(e + 0x4A);
        }
        if (anim >= 0 && delay >= 0) {
            AnimateCharacter(k, anim, 0, 1, 0, (s16)delay, e[0x40], -1);
            e[0x46] = anim;
            e[0x4F] = 1;
            e[0x50] = tbl->u68;
            return 1;
        }
        }
        return 0;
    }
    if (f[0x20F] == 0) {
        if (f[0x200] != 0) {
            o[0x26F] = 1;
            if (g_d_GameSettings[0x11] != 0) {
                fn_8004AE18(f[0x20D]);
            } else {
                fn_8004AE18(a);
            }
        }
        if (e[0x50] != 0) {
            e[0x50]--;
        }
        (*(s16*)(e + 0x4A))--;
        if (e[0x46] == 0x26) {
            if (f[0x25C] == 1) {
                AnimateCharacter(k, 0x28, 0, 1, 0, 0, e[0x40], 0);
            }
            if (f[0x25E] != 4) {
                return 1;
            }
            goto reset;
        }
        if (*(s16*)(e + 0x4A) == 1 && (f[0x258] != 1 || f[0x252] != 1)) {
            t = e[0x4C];
            if (t != 7 && t != 8 && *(s16*)(o + 0x62) != 0x29) {
                if (f[0x258] == 3 && t != 3) {
                    AnimateCharacter(k, 0x1C, 0, 1, 1, 0, e[0x40], 10);
                    fn_3_60804(a, 1);
                } else {
                    fn_3_60804(a, 1);
                }
            }
        }
        if (*(s16*)(o + 0x62) == 0x1B && *(s16*)(g_Ball + 0x1B6E) >= tbl->u40[0] &&
            *(s16*)(g_Ball + 0x1B6E) <= tbl->u40[1] &&
            checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) == 0 &&
            checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 8) == 0 &&
            checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 9) == 0 &&
            (*(s16*)(g_FieldingLogic + 0xC4) >= 0 || *(s16*)(g_FieldingLogic + 0xC6) >= 0) && e[0x42] != 0) {
            AnimateCharacter(k, 0x1A, 0, 1, 1, 0, e[0x40], -1);
            fn_3_60804(a, 1);
        }
        t = e[0x4C];
        if (t == 7 || t == 8) {
            if (f[0x262] == 0 && f[0x252] == 0 && f[0x1EE] == 0) {
                AnimateCharacter(k, 0, 0, 1, 1, 0, e[0x40], -1);
                goto reset;
            }
            return 1;
        }
        if (*(s16*)(o + 0x68) > 1) {
            return 1;
        }
    }
reset:
    e[0x4C] = 0;
    e[0x4F] = 0;
    e[0x47] = 0;
    e[0x46] = 0;
    e[0x50] = 0;
    fn_3_60804(a, 0);
    return 0;
}
#endif

// .text:0x00061B64 size:0xDA0 mapped:0x806A0BF8
// NONMATCHING 87%: the original inlines fn_3_60D80 and fn_3_61148 here (calls kept for clarity)
#if NONMATCHING
void fn_3_61B64(s32 i) {
    s32 k = i;
    u8* e = g_UnkAnimation_31EAC + i * 0x54;
    u8* f = g_Fielders + i * 0x268;
    u8** actors;
    u8* o;
    s16 anim;
    s32 v;
    s32 last;
    f32 spd;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            u8* m = g_Minigame;
            m += *(s8*)(m + 0x1904);
            k = *(s8*)(m + 0x18CC);
        } else {
            k = *(s8*)(g_Minigame + f[0x20D] + 0x18CC);
        }
    }
    actors = (u8**)(lbl_8036E548 + 0x2C50);
    o = actors[k];
    if (o == NULL) {
        return;
    }
    anim = *(s16*)(o + 0x62);
    if (*(s16*)(g_UnkThrowing_31ACC + 0xC) == i && *(s16*)(g_Ball + 0x1B78) == i) {
        o[0x274] = 1;
    }
    if (g_Minigame[0x1A2A] == 2) {
        goto check_state;
    }
    if (g_Minigame[0x1A2A] == 5) {
        u8 t = g_Minigame[f[0x20D] + 0x1C9A];
        if (t == 1) {
            if (anim != 0x24) {
                fn_3_90220(*(s16*)(f + 0x17A), 10);
            }
            AnimateCharacter(k, 0x24, 1, 1, 0, 0, 0, -1);
            e[0x43] = 0;
            goto done;
        }
        if (t == 2) {
            AnimateCharacter(k, 0, 1, 1, 0, 0, 0, -1);
            goto done;
        }
        if (fn_3_60D80(i) != 0) {
            goto done;
        }
    }
    if (g_Minigame[0x1A2A] == 6 && g_Minigame[f[0x20D] + 0x1D6E] == 2) {
        if (anim != 0x24 && anim != 0x25) {
            fn_3_90220(*(s16*)(f + 0x17A), 10);
            AnimateCharacter(k, 0x24, 0, 1, 0, 0, 0, -1);
            QueueCharacterAnimation(k, 0x25, 0, 0, 0, 0, 0);
        }
        goto done;
    }
    if (f[0x210] != 0) {
        if (f[0x210] == 1) {
            if (*(s16*)(f + 0x1BE) == 1) {
                fn_3_60804(i, 0);
                if (anim != 0x24) {
                    fn_3_90220(*(s16*)(f + 0x17A), 10);
                }
                AnimateCharacter(k, 0x24, 0, 1, 0, 0, e[0x40], -1);
            }
        } else {
            if (*(s16*)(f + 0x1BE) == 1) {
                AnimateCharacter(k, 0x25, 0, 1, 1, 0, e[0x40], 0);
                fn_3_60804(i, 1);
            }
            if (*(s16*)(f + 0x1C0) == 1) {
                AnimateCharacter(k, 0, 1, 1, 0, 0, e[0x40], -1);
                fn_3_60804(i, 0);
            }
        }
        e[0x43] = 0;
        goto done;
    }
    if (fn_3_61544(i) != 0) {
        if (fn_3_61228(i) == 0) {
            fn_3_60E90(i);
        }
        goto done;
    }
    if (f[0x20F] != 0) {
        if (*(s16*)(f + 0x1B8) == 0) {
            fn_3_60804(i, 0);
        }
        AnimateCharacter(k, 0x10, 1, 1, 0, 0, e[0x40], 0);
        if (anim != 0x10) {
            fn_3_90220(*(s16*)(f + 0x17A), 11);
        }
        e[0x43] = 0;
        goto done;
    }
    if (*(s16*)(g_UnkThrowing_31ACC + 0xC) == i) {
        if (fn_3_61228(i) != 0 || fn_3_60E90(i) != 0) {
            goto done;
        }
        if (f[0x205] >= 3) {
            AnimateCharacter(k, 0x27, 0, 1, 0, 0, e[0x40], -1);
        } else {
            spd = *(f32*)(e + 0);
            if (spd > lbl_3_rodata_E88) {
                if (g_Strikes[2] >= 3 && f[0x1D6] == 0xD) {
                    AnimateCharacter(k, 7, 1, 1, 0, 0, e[0x40], -1);
                } else if (*(s16*)(g_Ball + 0x1B78) == i && *(f32*)(f + 0xB8) < lbl_3_rodata_E8C) {
                    if (anim == 5) {
                        AnimateCharacter(k, 0x22, 1, 2, 0, 0, e[0x40], -1);
                    } else {
                        AnimateCharacter(k, 0x22, 1, 1, 0, 0, e[0x40], -1);
                    }
                } else if (spd > lbl_3_rodata_E90) {
                    if (anim == 0x22) {
                        AnimateCharacter(k, 5, 1, 2, 0, 0, e[0x40], -1);
                    } else {
                        AnimateCharacter(k, 5, 1, 1, 0, 0, e[0x40], -1);
                    }
                } else {
                    AnimateCharacter(k, 7, 1, 1, 0, 0, e[0x40], -1);
                }
            } else {
                AnimateCharacter(k, 1, 1, 1, 1, 0, e[0x40], -1);
            }
        }
        goto done;
    }
    e[0x44] = 0;
    if (fn_3_61148(i) != 0) {
        goto done;
    }
check_state:
    if (f[0x211] != 0 && f[0x212] == 3) {
        if (*(s16*)(g_FieldingLogic + 0xF6) <= 1) {
            fn_3_60804(k, 0);
            e[0x44] = 0;
            e[0x51] = 0;
        }
        goto done;
    }
    if (f[0x203] != 0) {
        AnimateCharacter(k, 0x26, 0, 1, 0, 0, e[0x40], -1);
        goto done;
    }
    if (f[0x207] != 0) {
        if (f[0x207] == 1) {
            AnimateCharacter(k, 0x26, 0, 1, 0, 0, e[0x40], -1);
        } else if (f[0x207] == 2) {
            AnimateCharacter(k, 0x28, 0, 1, 1, 0, e[0x40], -1);
            o[0x26F] = 1;
        } else if (f[0x207] == 3) {
            if (*(s16*)(f + 0x1B4) == 1) {
                fn_3_60804(k, 1);
            }
        } else if (f[0x207] == 4) {
            o[0x26F] = 0;
            if (*(s16*)(f + 0x1B4) == 1) {
                AnimateCharacter(k, 0, 1, 1, 0, 0, e[0x40], -1);
                fn_3_60804(k, 0);
            }
        }
        goto done;
    }
    if (f[0x205] != 0) {
        if (f[0x205] == 1) {
            AnimateCharacter(k, 0x26, 0, 1, 0, 0, e[0x40], -1);
        } else if (f[0x205] == 2) {
            if (f[0x206] != 0) {
                v = 0x2A;
                if (f[0x206] == 3) {
                    v = 0x2B;
                } else if (f[0x206] == 4) {
                    v = 0x2C;
                }
                if (anim == 0x2A || anim == 0x2B || anim == 0x2C) {
                    AnimateCharacter(k, v, 1, 2, 1, 0, e[0x40], -1);
                } else {
                    AnimateCharacter(k, v, 1, 1, 1, 0, e[0x40], -1);
                }
            } else if (anim == 0x2A) {
                AnimateCharacter(k, 0x28, 1, 2, 1, 0, e[0x40], -1);
            } else {
                AnimateCharacter(k, 0x28, 1, 1, 1, 0, e[0x40], 0);
            }
        } else if (f[0x205] >= 3) {
            AnimateCharacter(k, 0x27, 0, 1, 0, 0, e[0x40], -1);
        }
        goto done;
    }
    spd = *(f32*)(e + 0);
    if (spd > lbl_3_rodata_E7C) {
        if (f[0x256] != 0) {
            s16 ang = radToShortAngle(*(f32*)(f + 0x48));
            s16 d = fn_3_9FCA4(ang, fn_3_9FB8C(*(f32*)(f + 0x30), *(f32*)(f + 0x34)));
            v = 8; // the original leaves this unset when f[0x256] != 1
            if (f[0x256] == 1) {
                v = 8;
                if (d < -0x600 || d > 0x600) {
                    v = 9;
                } else if (d > 0x200) {
                    if (e[0x40] == 0) {
                        v = 0xA;
                    } else {
                        v = 0xB;
                    }
                } else if (d < -0x200) {
                    if (e[0x40] == 0) {
                        v = 0xB;
                    } else {
                        v = 0xA;
                    }
                }
            }
            AnimateCharacter(k, v, 1, 1, 0, 0, e[0x40], -1);
        } else if (f[0x1CB] == 1 && anim == 0x28) {
            AnimateCharacter(k, 2, 1, 2, 1, 0, e[0x40], -1);
            f[0x20A] = 1;
        } else if (spd > lbl_3_rodata_E90) {
            AnimateCharacter(k, 5, 1, 1, 0, 0, e[0x40], -1);
        } else {
            AnimateCharacter(k, 7, 1, 1, 0, 0, e[0x40], -1);
        }
        goto done;
    }
    if (g_Minigame[0x1A2A] == 2 && anim >= 0x3F && anim < 0x4B) {
        return;
    }
    v = 2;
    if (e[0x41] == 1) {
        v = 0;
    }
    if (anim == 0x24 || anim == 0x25) {
        if (anim == 0x25) {
            AnimateCharacter(k, 0, 1, 2, 1, 0, e[0x40], -1);
        }
    } else if (e[0x45] != 0) {
        AnimateCharacter(k, 3, 1, 1, 0, 0, e[0x40], -1);
    } else if (f[0x1CB] == 1 && anim == 0x28) {
        AnimateCharacter(k, v, 1, 2, 1, 0, e[0x40], -1);
        f[0x20A] = 1;
    } else if (anim == 0xF) {
        AnimateCharacter(k, v, 1, 2, 1, 0, e[0x40], -1);
    } else if (i == 1 && *(s16*)(g_Ball + 0x1B66) < 0x78) {
        if (*(s16*)(g_Ball + 0x1B66) == 0x1E) {
            AnimateCharacter(k, 0x3E, 0, 1, 1, 0, e[0x40], -1);
        }
    } else if (anim == 0x3E) {
        AnimateCharacter(k, v, 1, 2, 1, 0, e[0x40], -1);
    } else {
        last = -1;
        if (anim == 0x40 || anim == 0x42 || anim == 0x49 || anim == 0x4A) {
            last = 0;
        }
        AnimateCharacter(k, v, 1, 1, 1, 0, e[0x40], last);
    }
done:
    if (e[0x42] != 0) {
        *(f32*)(o + 0x34) = *(f32*)(e + 0x10);
        *(f32*)(o + 0x3C) = *(f32*)(e + 0x18);
        e[0x42] = 1;
    } else {
        e[0x42] = 0;
    }
    if (f[0x1CB] == 1 && anim == 0x28 && (*(s16*)(o + 0x68) <= 1 || o[0x25E] == 1)) {
        fn_3_60804(k, 0);
    }
}
#endif

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
// NONMATCHING 99%: c/o register swap and scheduling in the prologue (anim init added for safety)
#if NONMATCHING
void fn_3_631AC(s32 a) {
    s32 anim;
    s32 k;
    u8** actors;
    u8* o;
    u8* r;
    u8* c;
    s32 flag;
    u8 t;
    r = g_Runners + a * 0x154;
    k = a + 9;
    c = lbl_3_common_bss_321A0 + (a << 5);
    actors = (u8**)(lbl_8036E548 + 0x2C50);
    o = actors[k];
    if (g_d_GameSettings[0x11] != 0) {
        k = *(s8*)(g_Minigame + a + 0x18FC);
        o = actors[k];
    }
    anim = -1; // the original leaves this unset when there is no actor
    if (o != NULL) {
        anim = *(s16*)(o + 0x62);
    }
    switch (c[0x1B]) {
    case 0:
        return;
    case 2:
        flag = 0;
        t = lbl_800E8558[*(s16*)(r + 0xE2) * 6 + 2];
        if (t == 0xE || t == 0x14 || t == 0x1A || t == 0x1E) {
            flag = 1;
        }
        if (r[0x137] == 1 && *(s16*)(r + 0xEA) < 0xA && g_GameLogic[0x121] != 6 && flag != 0) {
            AnimateCharacter(k, 0x2E, 0, 1, 0, (s16)(*(s16*)(lbl_3_data_7870 + *(s16*)(r + 0xE2) * 6 + 4) - 0xA), 0, -1);
        } else if (anim == 0x31) {
            AnimateCharacter(k, 0x2D, 1, 2, 0, 0, 0, -1);
        } else {
            AnimateCharacter(k, 0x2D, 1, 1, 0, 0, 0, -1);
        }
        break;
    case 3:
        if (g_Minigame[0x1A2A] != 0) {
            AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, -1);
        } else if (lbl_800E8558[*(s16*)(r + 0xE2) * 6 + 2] == 0xC) {
            AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, -1);
        } else {
            AnimateCharacter(k, 0x38, 1, 1, 1, 0, 0, -1);
        }
        break;
    case 4:
        AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, -1);
        break;
    case 5:
        if (r[0x137] == 3) {
            AnimateCharacter(k, 0x30, 0, 1, 0, 0x14, 1, -1);
        } else {
            AnimateCharacter(k, 0x30, 0, 1, 0, 0x14, 0, -1);
        }
        break;
    case 7:
        if (r[0x138] == 3) {
            AnimateCharacter(k, 0x31, 0, 1, 0, 0, 1, 0);
        } else {
            AnimateCharacter(k, 0x31, 0, 1, 0, 0, 0, 0);
        }
        break;
    case 8:
        if (r[0x13C] == 1) {
            if (*(s16*)(r + 0x100) == 1) {
                if (r[0x13A] == 2) {
                    AnimateCharacter(k, 0x33, 0, 1, 1, (s16)(lbl_3_data_7760[*(s16*)(r + 0xE2) * 5 + 2] - *(s16*)(r + 0x102)), 1, -1);
                } else if (r[0x13A] == 3) {
                    AnimateCharacter(k, 0x33, 0, 1, 1, (s16)(lbl_3_data_7760[*(s16*)(r + 0xE2) * 5 + 2] - *(s16*)(r + 0x102)), 1, -1);
                } else if (r[0x13B] != 0 && r[0x126] != 0) {
                    AnimateCharacter(k, 0x32, 0, 1, 1, (s16)(lbl_3_data_7760[*(s16*)(r + 0xE2) * 5 + 2] - *(s16*)(r + 0x102)), 1, -1);
                } else {
                    AnimateCharacter(k, 0x34, 0, 1, 1, (s16)(lbl_3_data_7760[*(s16*)(r + 0xE2) * 5 + 4] - *(s16*)(r + 0x102)), 0, -1);
                }
                if (g_GameLogic[0x11E] == 2) {
                    playSoundEffect(0x171);
                }
            }
        } else if (r[0x13C] == 2) {
            if (*(s16*)(r + 0x102) == 1) {
                AnimateCharacter(k, 0x38, 1, 1, 1, 0, 0, 0);
            }
        }
        break;
    case 9:
        AnimateCharacter(k, 0x2D, 1, 1, 0, 0, 0, -1);
        break;
    case 10:
        AnimateCharacter(k, 0x2F, 1, 1, 0, 0, 0, -1);
        break;
    case 11:
        AnimateCharacter(k, 0x30, 1, 1, 0, 0, 0, -1);
        break;
    case 12:
        AnimateCharacter(k, 0x2F, 1, 1, 0, 0, 0, -1);
        break;
    case 13:
        AnimateCharacter(k, 0x2D, 1, 1, 0, 0, 0, -1);
        break;
    case 14:
        if (*(s16*)(r + 0x114) == 0 && lbl_3_rodata_E58 != *(f32*)(r + 0x18)) {
            AnimateCharacter(k, 0x2D, 1, 1, 0, 0, 0, -1);
        }
        break;
    case 15:
        AnimateCharacter(k, 0x35, 0, 1, 0, (s16)(*(s16*)(lbl_3_data_7870 + *(s16*)(r + 0xE2) * 6 + 2) - *(s16*)(r + 0x10E)), 0, -1);
        break;
    case 16:
        AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, 0);
        break;
    case 17:
        if (anim != 0x24) {
            fn_3_90220(*(s16*)(r + 0xE2), 10);
        }
        AnimateCharacter(k, 0x24, 0, 1, 1, 0, 0, 0x14);
        break;
    }
}
#endif

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
// NONMATCHING 86%: loop shapes/unrolling and bss addressing differ
#if NONMATCHING
void fn_3_657E4(void) {
    s32 doit = 0;
    s32 j;
    s32 k;
    s32 found;
    u8 flag;
    s32 snd;
    u8* res = lbl_3_common_bss_32234 + 2;
    if (g_GameLogic[0x11E] == 0xE) {
        if (g_d_GameSettings[0x11] != 0 && g_GameLogic[0x125] == 1) {
            doit = 1;
        }
        if (g_d_GameSettings[0x11] == 0 && g_GameLogic[0x125] == 3) {
            doit = 1;
        }
    }
    if (g_GameLogic[0x11E] == 0x27 && g_GameLogic[0x125] == 0) {
        doit = 1;
    }
    if (doit != 0) {
        if (g_d_GameSettings[0x11] == 0) {
            if (lbl_80353A90[0x104] == 2) {
                res[0] = 1;
            } else if (lbl_80353A90[0x104] == 3) {
                res[0] = 2;
            } else {
                res[0] = 0;
            }
        } else if (g_GameLogic[0x11E] == 0x27 && g_Minigame[0x1A3D] == 1) {
            s8 me = g_Minigame[0x1908];
            found = 0;
            for (j = 0; j < 4; j++) {
                if (g_Minigame[0x1E08 + j * 2] == me && g_Minigame[0x1E09 + j * 2] == 0) {
                    found = 1;
                    break;
                }
            }
            if (g_Minigame[0x1E09] == 0 && g_Minigame[0x1E0B] == 0 && g_Minigame[0x1E0D] == 0 && g_Minigame[0x1E0F] == 0) {
                res[me] = 2;
            } else if (found != 0) {
                res[me] = 0;
            } else {
                res[me] = 1;
            }
        } else if (g_Minigame[0x1906] == 1) {
            for (j = 0; j < 4; j++) {
                if (*(s8*)(g_Minigame + 0x18CC + j) >= 0) {
                    if (g_Minigame[0x1A2B] == 3) {
                        if (g_Minigame[0x19AA] != 0) {
                            res[j] = 0;
                        } else {
                            res[j] = 1;
                        }
                    } else if (g_Minigame[0x1A37] == 1) {
                        res[j] = 0;
                    } else {
                        res[j] = 1;
                    }
                }
            }
        } else {
            for (j = 0; j < 4; j++) {
                if (*(s8*)(g_Minigame + 0x18CC + j) >= 0) {
                    if (g_Minigame[0x19A8] != 0) {
                        res[j] = 2;
                    } else if (g_Minigame[0x18E8 + j] == 1) {
                        res[j] = 0;
                    } else {
                        res[j] = 1;
                    }
                }
            }
        }
    }
    if ((g_d_GameSettings[0x11] == 0 && g_GameLogic[0x125] < 4) || (g_d_GameSettings[0x11] != 0 && g_Minigame[0x19A9] <= 1)) {
        for (j = 0; j < 4; j++) {
            if (g_d_GameSettings[0x11] == 0) {
                k = 9;
            } else {
                k = *(s8*)(g_Minigame + 0x18CC + j);
                if (k < 0) {
                    continue;
                }
            }
            if (g_d_GameSettings[0x11] == 0) {
                flag = 1;
            } else {
                s8 c = *(s8*)(g_Minigame + 0x19EC + j * 9);
                if (c == 0 || c == 2) {
                    flag = 1;
                } else {
                    flag = 0;
                }
            }
            if (res[j] == 0) {
                AnimateCharacter(k, 0x69, 1, 1, 1, 0, flag, 0);
            } else if (res[j] == 1) {
                AnimateCharacter(k, 0x6F, 1, 1, 1, 0, flag, 0);
            } else {
                AnimateCharacter(k, 0x72, 1, 1, 1, 0, flag, 0);
            }
            if (g_d_GameSettings[0x11] == 0) {
                break;
            }
        }
    } else if ((g_d_GameSettings[0x11] == 0 && g_GameLogic[0x125] == 4 && *(u16*)(g_GameLogic + 0xFE) == 1) ||
               (g_d_GameSettings[0x11] != 0 && g_Minigame[0x19A9] == 2) ||
               (g_GameLogic[0x11E] == 0x27 && g_GameLogic[0x125] == 0)) {
        g_Minigame[0x19A9] = 3;
        for (j = 0; j < 4; j++) {
            if (g_d_GameSettings[0x11] == 0) {
                k = 9;
            } else {
                k = *(s8*)(g_Minigame + 0x18CC + j);
                if (k < 0) {
                    continue;
                }
            }
            if (g_GameLogic[0x11E] == 0x27 && *(s8*)(g_Minigame + 0x1908) >= 0 && *(s8*)(g_Minigame + 0x1908) != j) {
                continue;
            }
            if (g_d_GameSettings[0x11] == 0) {
                flag = 1;
                snd = *(s8*)(lbl_80353A90 + 0x103);
            } else {
                s8 c = *(s8*)(g_Minigame + 0x19EC + j * 9);
                if (c == 0 || c == 2) {
                    snd = g_Minigame[0x18D0 + j];
                    flag = 1;
                } else {
                    flag = 0;
                    snd = g_Minigame[0x18D0 + j];
                }
            }
            if (res[j] == 0) {
                AnimateCharacter(k, 0x6D, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(k, 0x6B, 1, 1, 0, flag, -1);
                fn_3_90220(snd, 7);
            } else if (res[j] == 1) {
                AnimateCharacter(k, 0x70, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(k, 0x71, 1, 1, 0, flag, -1);
                if (g_Minigame[0x1906] > 1) {
                    fn_3_90150(snd, 9);
                } else {
                    fn_3_90220(snd, 9);
                }
            } else {
                AnimateCharacter(k, 0x73, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(k, 0x74, 1, 1, 0, flag, -1);
            }
            if (g_d_GameSettings[0x11] == 0) {
                break;
            }
        }
    }
}
#endif

// .text:0x00065FE0 size:0x160 mapped:0x806A5074
void fn_3_65FE0(void) {
    int flag;
    int idx;
    s8 c;
    u8* o;
    int i;
    for (i = 0; i < 4; i++) {
        idx = i;
        o = ((u8**)lbl_8036E548)[i + 0x2C50 / 4];
        flag = 0;
        if (g_d_GameSettings[7] == 2) {
            idx = 9;
            o = ((u8**)lbl_8036E548)[0x2C74 / 4];
        }
        if (o != NULL) {
            c = *(s8*)(g_Minigame + i * 9 + 0x19EC);
            if (c == 0 || c == 2) {
                flag = 1;
            }
            if (*(s8*)(g_Minigame + i * 9 + 0x19EA) < 0) {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            } else if (*(s8*)(g_Minigame + i * 9 + 0x19E9) != 0) {
                if (*(s16*)(o + 0x62) == 0x69) {
                    AnimateCharacter(idx, 0x6A, 0, 1, 1, 0, flag, 0);
                    QueueCharacterAnimation(idx, 0x6B, 1, 1, 0, flag, -1);
                }
            } else {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            }
            if (g_d_GameSettings[7] == 2) {
                break;
            }
        }
    }
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
void fn_3_6714C(s32 player) {
    return;
}


#pragma dont_inline off
