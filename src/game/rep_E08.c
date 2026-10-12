#include "game/rep_E08.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#define CHARANIM_REL_PROTOTYPES
#include "main/file_80011640.h"
#include "main/file_80069BDC.h"
#include "game/auto_00_0009C578_text.h"
#include "game/auto_00_000249E8_text.h"
#include "main/file_800BD8C4.h"
#define REP_HEADER_FN repHeader_E08
#include "header_rep_inline.h"
#include "math.h"
#include "game/rep_D0.h"

#pragma dont_inline on

extern InMemFielderType g_Fielders[9];
extern RunnerAnimState lbl_3_common_bss_321A0[4];
extern ThrowState g_UnkThrowing_31ACC[];
extern FielderAnimState g_UnkAnimation_31EAC[];
extern GameBss32220 lbl_3_common_bss_32220;
extern GameBss32230 lbl_3_common_bss_32230;
extern GameBss32234 lbl_3_common_bss_32234;

extern s16 lbl_3_data_7870[][3]; // per character

extern int fn_3_9FB8C(f32 x, f32 y);
extern int fn_3_9FCA4(s16 a, s16 b);
extern int radToShortAngle(f32 v);
extern u8 lbl_3_data_7E34[];
extern u8 lbl_3_data_7D24[];
extern f32 shortAngleToRad_Capped(s16 a);
extern u32 fn_3_90220(s32 idx, s32 off);
extern void fn_8001B4D8(s32 index, s32 enable);
extern void fn_8001C528(void);
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
extern void** fn_800111D8(void* actor);
extern f32 fn_800B4A44(void* actor, u16 boneIndex);
extern s32 fn_8001B35C(s32 index, s32 kind);
extern u8 lbl_803CBC3C[];
extern SceneWork* lbl_3_common_bss_1323C;
extern void fn_3_22C10(void);
extern s16 lbl_3_data_5EDC[];
extern s32 fn_3_6D564(s32 team, s32 idx, s32 delta);
extern const f32 lbl_3_rodata_E98;
extern const f32 lbl_3_rodata_E9C;
extern u32 fn_3_90150(s32 a, s32 b);
extern u8 lbl_3_data_7760[];
extern u32 playSoundEffect(s32);
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
        ActorObject* e = &lbl_8036E548.slots->objects[i];
        e->animBank = NULL;
        e->seqNum = 0;
        e->time = 0.0f;
        e->setAnimation = 1;
        e->setTime = 0;
        e->setSpeed = 0;
        e->speed = 0.0f;
    }
}

// .text:0x00060804 size:0x294 mapped:0x8069F898
void fn_3_60804(s32 a, s32 b) {
    s32 k = a;
    FielderAnimState* e = &g_UnkAnimation_31EAC[a];
    InMemFielderType* f = &g_Fielders[a];
    CharActor* o;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (a == 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            k = g_Minigame.minigameControlStruct[0].fieldOrder[a - 2];
        }
    }
    o = lbl_8036E548.active[k];
    if (o != NULL) {
        if (b == 0) {
            if (e->_42 == 1) {
                f32 d;
                e->_42 = 0;
                getAnimRelatedCoordinates(k, 4, &e->_2C);
                f->velX = e->_2C.x - f->pos.x;
                f->velZ = e->_2C.z - f->pos.z;
                d = sqrt_E08(f->velX * f->velX + f->velZ * f->velZ);
                f->speed = d;
                f->pos.x = e->_2C.x;
                f->pos.z = e->_2C.z;
                e->_48 = 1;
            }
        } else {
            if (e->_42 == 0) {
                fn_8001B4D8(k, b);
                if (e->_48 == 1) {
                    e->_10 = e->_2C.x;
                    e->_18 = e->_2C.z;
                } else {
                    e->_10 = o->pos.x;
                    e->_18 = o->pos.z;
                }
                e->_42 = 1;
            } else {
                f32 v[3];
                getAnimRelatedCoordinates(k, 4, (Vec*)v);
                e->_10 = o->pos.x = v[0];
                e->_18 = o->pos.z = v[2];
            }
        }
    }
}

// .text:0x00060A98 size:0x2E8 mapped:0x8069FB2C
// NONMATCHING 97%: r29/r30 (anim/a) and f1-f4 swapped (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_3_60A98(s32 a, CharActor* o) {
    InMemFielderType* f;
    s16 anim;
    FielderAnimState* e;
    f32 dx;
    f32 dz;
    f32 d;
    f32 sx;
    f32 sz;
    e = &g_UnkAnimation_31EAC[a];
    f = &g_Fielders[a];
    if (o == NULL) {
        return;
    }
    anim = o->anim[0]; // original reads this before the NULL check
    if (f->distToBase[0] < lbl_3_rodata_E78 && fn_3_B7E10(f->pos.x, f->pos.z) == 0) {
        return;
    }
    dz = f->pos.z - e->_18;
    dx = f->pos.x - e->_10;
    d = sqrt_E08(dx * dx + dz * dz);
    if (d <= lbl_3_rodata_E58) {
        return;
    }
    sx = dx / d;
    sz = dz / d;
    if (anim == 0x1A || anim == 0x1B) {
        s16 c = f->charID;
        f32 m = lbl_3_rodata_E7C * (f32)(lbl_3_data_7F10[c] + 0x1E) * charSizeMultipliers[c][0];
        sx *= m;
        sz *= m;
    } else {
        f32 m = lbl_3_data_476C[f->weight];
        sx *= m;
        sz *= m;
    }
    if (fn_3_B7CDC(sx + f->pos.x, sz + f->pos.z) != 0) {
        fn_3_60804(a, 0);
        if (g_d_GameSettings.minigamesEnabled != 0) {
            if (a == 0) {
                a = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
            } else {
                a = g_Minigame.minigameControlStruct[0].fieldOrder[a - 2];
            }
        }
        fn_8001B5EC(a, 0);
        f->pos.x = f->_0D4;
        f->pos.z = f->_0D8;
        f->_1F9[2] = 0;
    }
}
#endif

// .text:0x00060D80 size:0x110 mapped:0x8069FE14
s32 fn_3_60D80(s32 a) {
    FielderAnimState* e;
    s32 k;
    s16 anim;
    s16 st;
    e = &g_UnkAnimation_31EAC[a];
    k = g_Minigame.minigameControlStruct[0].fieldOrder[a - 2];
    anim = lbl_8036E548.active[k]->anim[0];
    st = g_Minigame._1B34[k];
    if (st < 0) {
        if (anim == 0x1D || anim == 0x1F) {
            AnimateCharacter(k, 0, 1, 3, 0, 0, e->_40, -1);
        }
        return 0;
    }
    if (st == 0) {
        s32 c = g_Minigame._1C92[k];
        if (c == 3) {
            AnimateCharacter(k, 0x1F, 0, 3, 0, 0, e->_40, -1);
        } else {
            AnimateCharacter(k, 0x1D, 0, 3, 0, 0, e->_40, -1);
        }
    }
    return 1;
}

// .text:0x00060E90 size:0x2B8 mapped:0x8069FF24
u32 fn_3_60E90(s32 a) {
    s32 k = a;
    FielderAnimState* e = &g_UnkAnimation_31EAC[a];
    u8 st;
    CharActor* o;
    InMemFielderType* f = &g_Fielders[a];
    s16 oa;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (a == 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            k = g_Minigame.minigameControlStruct[0].fieldOrder[a - 2];
        }
    }
    st = e->_51;
    o = lbl_8036E548.active[k];
    oa = o->anim[0];
    if (st != 9 && g_Ball.fielderWBallIndex != a) {
        e->_44 = 0;
        return 0;
    }
    if (st == 9) {
        return 1;
    }
    if (e->_44 != 0 && g_UnkThrowing_31ACC[0]._10[0] == 0) {
        if (st == 8 && f->_212 == 3) {
            if (oa != 0x24) {
                fn_3_90220(f->charID, 10);
            }
            e->_51 = 9;
            AnimateCharacter(k, 0x24, 0, 1, 0, 0, e->_40, 0);
            QueueCharacterAnimation(k, 0x25, 0, 1, 0, e->_40, 0);
            fn_3_60804(a, 0);
            return 1;
        }
        if (o->_068 <= 0) {
            e->_44 = 0;
            e->_51 = 0;
            fn_3_60804(a, 0);
            return 0;
        }
        return 1;
    }
    if (st == 0 || st == 4) {
        goto clear;
    }
    if (st == 8) {
        s32 x = (s8)(u8)o->kind * 4;
        if (lbl_3_data_7E34[x + 1] - g_FieldingLogic._0F6 < 0) {
            goto clear;
        }
        AnimateCharacter(k, 0x23, 0, 1, 1, lbl_3_data_7E34[x], e->_40, -1);
        e->_44 = 1;
    } else {
        AnimateCharacter(k, 0x21, 0, 1, 0, lbl_3_data_7E34[(s8)(u8)o->kind * 4], e->_40, -1);
        e->_44 = 1;
    }
    fn_3_60804(a, 0);
    return 1;
clear:
    e->_44 = 0;
    return 0;
}

// .text:0x00061148 size:0xE0 mapped:0x806A01DC
u32 fn_3_61148(s32 i) {
    FielderAnimState* e = &g_UnkAnimation_31EAC[i];
    s32 k = i;
    CharActor* o;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            k = g_Minigame.minigameControlStruct[0].fieldOrder[i - 2];
        }
    }
    o = lbl_8036E548.active[k];
    if (o == NULL) {
        return 0;
    }
    if (e->_43 != 0) {
        if (o->_068 <= 0) {
            e->_43 = 0;
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
    CharActor* o;
    s32 k = a;
    FielderAnimState* e = &g_UnkAnimation_31EAC[a];
    ThrowState* thr = g_UnkThrowing_31ACC;
    InMemFielderType* f = &g_Fielders[a];
    s32 vv = 0x1D;
    s32 flag = 0;
    g_FieldingLogic_s* fl = &g_FieldingLogic;
    s16 ang;
    s32 adj;
    s16 d;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (a == 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            k = g_Minigame.minigameControlStruct[0].fieldOrder[a - 2];
        }
    }
    o = lbl_8036E548.active[k];
    if (o == NULL) {
        return 0;
    }
    if (thr->_0C != a) {
        return 0;
    }
    if (e->_43 != 0) {
        if (f->_1D3[0] == 0x11) {
            e->_43 = 0;
            fn_3_60804(a, 0);
            return 0;
        }
        t = o->_06A[0];
        if (t > 0 && o->_068 <= 0) {
            e->_43 = 0;
            fn_3_60804(a, 0);
            return 0;
        }
        tb = lbl_3_data_7D24 + (s8)(u8)o->kind * 5;
        oa = o->anim[0];
        if (t >= *(u8*)(oa - 0x1D + tb)) {
            fl->_10A = 1;
        }
        return 1;
    }
    if (f->_215 != 0) {
        return 0;
    }
    if (thr->_0E != 0) {
        switch (thr->_0E) {
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
            ang = radToShortAngle(f->facing);
            d = fn_3_9FCA4(ang, fn_3_9FB8C(thr->_00 - f->pos.x, thr->_08 - f->pos.z));
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
            f->facing = shortAngleToRad_Capped((s16)(ang + adj));
        }
        AnimateCharacter(k, vv, 0, 1, 1, 0, e->_40, -1);
        thr->_0F = vv;
        e->_43 = 1;
        if (flag != 0) {
            e->_43 = 2;
        }
        e->_4C = 0;
        e->_4F = 0;
        e->_47 = 0;
        e->_46 = 0;
        e->_50 = 0;
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
    InMemFielderType* f = &g_Fielders[a];
    FielderAnimState* e = &g_UnkAnimation_31EAC[a];
    E08AnimTable* tbl = &lbl_3_data_65F0;
    s32 delay = 0;
    CharActor* o;
    s32 v;
    u8 t;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (a == 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            k = g_Minigame.minigameControlStruct[0].fieldOrder[a - 2];
        }
    }
    o = lbl_8036E548.active[k];
    if (e->_43 != 0) {
        return 0;
    }
    if (e->_4F == 0) {
        if (f->_20F != 0) {
            return 0;
        }
        if (f->knockback != 0) {
            return 0;
        }
        if (f->_206[1] != 0) {
            return 0;
        }
        if (e->_4C != 0) {
        (e->_4A)--;
        t = e->_4C;
        if (t == 1 || t == 2) {
            s16 cur = e->_4A;
            s16 lim = tbl->windup[0];
            if (cur <= lim) {
                t = f->_24E[6];
                if (t == 0) {
                    anim = tbl->anims[0][e->_4E];
                } else if ((t == 1 && f->handedness == 0) || (t == 2 && f->handedness != 0)) {
                    anim = tbl->anims[1][e->_4E];
                } else {
                    anim = tbl->anims[2][e->_4E];
                }
                delay = lim - cur;
            }
        } else if (t == 7 || t == 8) {
            t = f->_25F[2];
            if (t == 1) {
                if (e->_40 != 0) {
                    v = 0xE;
                } else {
                    v = 0xD;
                }
            } else if (t == 2) {
                if (e->_40 != 0) {
                    v = 0xD;
                } else {
                    v = 0xE;
                }
            } else {
                v = 0xC;
            }
            AnimateCharacter(k, v, 1, 1, 0, 0, e->_40, -1);
            e->_46 = v;
            e->_4F = 1;
            return 1;
        } else if (t == 3) {
            s16 cur = e->_4A;
            s16 lim = tbl->windup[1];
            if (cur <= lim) {
                delay = lim - cur;
                anim = 0x1B;
            }
        } else if (t == 4) {
            AnimateCharacter(k, 0x26, 0, 1, 0, (s16)(lbl_3_data_7F0C - f->_25B[1]), e->_40, -1);
            e->_46 = 0x26;
            e->_4F = 1;
            return 1;
        } else if (t == 5) {
            anim = 0x29;
            delay = tbl->u10 - e->_4A;
        }
        if (anim >= 0 && delay >= 0) {
            AnimateCharacter(k, anim, 0, 1, 0, (s16)delay, e->_40, -1);
            e->_46 = anim;
            e->_4F = 1;
            e->_50 = tbl->u68;
            return 1;
        }
        }
        return 0;
    }
    if (f->_20F == 0) {
        if (f->_200 != 0) {
            o->_26F = 1;
            if (g_d_GameSettings.minigamesEnabled != 0) {
                fn_8004AE18(f->minigamePlayer);
            } else {
                fn_8004AE18(a);
            }
        }
        if (e->_50 != 0) {
            e->_50--;
        }
        (e->_4A)--;
        if (e->_46 == 0x26) {
            if (f->_25B[1] == 1) {
                AnimateCharacter(k, 0x28, 0, 1, 0, 0, e->_40, 0);
            }
            if (f->_25E != 4) {
                return 1;
            }
            goto reset;
        }
        if (e->_4A == 1 && (f->_24E[10] != 1 || f->_24E[4] != 1)) {
            t = e->_4C;
            if (t != 7 && t != 8 && o->anim[0] != 0x29) {
                if (f->_24E[10] == 3 && t != 3) {
                    AnimateCharacter(k, 0x1C, 0, 1, 1, 0, e->_40, 10);
                    fn_3_60804(a, 1);
                } else {
                    fn_3_60804(a, 1);
                }
            }
        }
        if (o->anim[0] == 0x1B && g_Ball.timeSinceBallPickedUp >= tbl->u40[0] &&
            g_Ball.timeSinceBallPickedUp <= tbl->u40[1] &&
            checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 7) == 0 &&
            checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 8) == 0 &&
            checkFieldingStat(g_GameLogic.teamFielding, f->rosterID, 9) == 0 &&
            (g_FieldingLogic._0C4 >= 0 || g_FieldingLogic._0C6 >= 0) && e->_42 != 0) {
            AnimateCharacter(k, 0x1A, 0, 1, 1, 0, e->_40, -1);
            fn_3_60804(a, 1);
        }
        t = e->_4C;
        if (t == 7 || t == 8) {
            if (f->_262 == 0 && f->_24E[4] == 0 && f->_1EE == 0) {
                AnimateCharacter(k, 0, 0, 1, 1, 0, e->_40, -1);
                goto reset;
            }
            return 1;
        }
        if (o->_068 > 1) {
            return 1;
        }
    }
reset:
    e->_4C = 0;
    e->_4F = 0;
    e->_47 = 0;
    e->_46 = 0;
    e->_50 = 0;
    fn_3_60804(a, 0);
    return 0;
}
#endif

// .text:0x00061B64 size:0xDA0 mapped:0x806A0BF8
// NONMATCHING 87%: the original inlines fn_3_60D80 and fn_3_61148 here (calls kept for clarity)
#if NONMATCHING
void fn_3_61B64(s32 i) {
    s32 k = i;
    FielderAnimState* e = &g_UnkAnimation_31EAC[i];
    InMemFielderType* f = &g_Fielders[i];
    CharActor** actors;
    CharActor* o;
    s16 anim;
    s32 v;
    s32 last;
    f32 spd;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (i == 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
        } else {
            k = g_Minigame.minigameControlStruct[0].characterIndex[f->minigamePlayer];
        }
    }
    actors = &lbl_8036E548.active[0];
    o = actors[k];
    if (o == NULL) {
        return;
    }
    anim = o->anim[0];
    if (g_UnkThrowing_31ACC[0]._0C == i && g_Ball.fielderWBallIndex == i) {
        o->_274 = 1;
    }
    if (g_Minigame.GameMode_MiniGame == 2) {
        goto check_state;
    }
    if (g_Minigame.GameMode_MiniGame == 5) {
        u8 t = g_Minigame._1C9A[f->minigamePlayer];
        if (t == 1) {
            if (anim != 0x24) {
                fn_3_90220(f->charID, 10);
            }
            AnimateCharacter(k, 0x24, 1, 1, 0, 0, 0, -1);
            e->_43 = 0;
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
    if (g_Minigame.GameMode_MiniGame == 6 && g_Minigame.starDashStunType[f->minigamePlayer] == 2) {
        if (anim != 0x24 && anim != 0x25) {
            fn_3_90220(f->charID, 10);
            AnimateCharacter(k, 0x24, 0, 1, 0, 0, 0, -1);
            QueueCharacterAnimation(k, 0x25, 0, 0, 0, 0, 0);
        }
        goto done;
    }
    if (f->knockback != 0) {
        if (f->knockback == 1) {
            if (f->_1BE == 1) {
                fn_3_60804(i, 0);
                if (anim != 0x24) {
                    fn_3_90220(f->charID, 10);
                }
                AnimateCharacter(k, 0x24, 0, 1, 0, 0, e->_40, -1);
            }
        } else {
            if (f->_1BE == 1) {
                AnimateCharacter(k, 0x25, 0, 1, 1, 0, e->_40, 0);
                fn_3_60804(i, 1);
            }
            if (f->_1C0 == 1) {
                AnimateCharacter(k, 0, 1, 1, 0, 0, e->_40, -1);
                fn_3_60804(i, 0);
            }
        }
        e->_43 = 0;
        goto done;
    }
    if (fn_3_61544(i) != 0) {
        if (fn_3_61228(i) == 0) {
            fn_3_60E90(i);
        }
        goto done;
    }
    if (f->_20F != 0) {
        if (f->_1B8 == 0) {
            fn_3_60804(i, 0);
        }
        AnimateCharacter(k, 0x10, 1, 1, 0, 0, e->_40, 0);
        if (anim != 0x10) {
            fn_3_90220(f->charID, 11);
        }
        e->_43 = 0;
        goto done;
    }
    if (g_UnkThrowing_31ACC[0]._0C == i) {
        if (fn_3_61228(i) != 0 || fn_3_60E90(i) != 0) {
            goto done;
        }
        if (f->_205 >= 3) {
            AnimateCharacter(k, 0x27, 0, 1, 0, 0, e->_40, -1);
        } else {
            spd = e->_00;
            if (spd > lbl_3_rodata_E88) {
                if (g_Strikes.outs >= 3 && f->_1D3[3] == 0xD) {
                    AnimateCharacter(k, 7, 1, 1, 0, 0, e->_40, -1);
                } else if (g_Ball.fielderWBallIndex == i && f->_0B8 < lbl_3_rodata_E8C) {
                    if (anim == 5) {
                        AnimateCharacter(k, 0x22, 1, 2, 0, 0, e->_40, -1);
                    } else {
                        AnimateCharacter(k, 0x22, 1, 1, 0, 0, e->_40, -1);
                    }
                } else if (spd > lbl_3_rodata_E90) {
                    if (anim == 0x22) {
                        AnimateCharacter(k, 5, 1, 2, 0, 0, e->_40, -1);
                    } else {
                        AnimateCharacter(k, 5, 1, 1, 0, 0, e->_40, -1);
                    }
                } else {
                    AnimateCharacter(k, 7, 1, 1, 0, 0, e->_40, -1);
                }
            } else {
                AnimateCharacter(k, 1, 1, 1, 1, 0, e->_40, -1);
            }
        }
        goto done;
    }
    e->_44 = 0;
    if (fn_3_61148(i) != 0) {
        goto done;
    }
check_state:
    if (f->_211 != 0 && f->_212 == 3) {
        if (g_FieldingLogic._0F6 <= 1) {
            fn_3_60804(k, 0);
            e->_44 = 0;
            e->_51 = 0;
        }
        goto done;
    }
    if (f->_203 != 0) {
        AnimateCharacter(k, 0x26, 0, 1, 0, 0, e->_40, -1);
        goto done;
    }
    if (f->_206[1] != 0) {
        if (f->_206[1] == 1) {
            AnimateCharacter(k, 0x26, 0, 1, 0, 0, e->_40, -1);
        } else if (f->_206[1] == 2) {
            AnimateCharacter(k, 0x28, 0, 1, 1, 0, e->_40, -1);
            o->_26F = 1;
        } else if (f->_206[1] == 3) {
            if (f->_1B4 == 1) {
                fn_3_60804(k, 1);
            }
        } else if (f->_206[1] == 4) {
            o->_26F = 0;
            if (f->_1B4 == 1) {
                AnimateCharacter(k, 0, 1, 1, 0, 0, e->_40, -1);
                fn_3_60804(k, 0);
            }
        }
        goto done;
    }
    if (f->_205 != 0) {
        if (f->_205 == 1) {
            AnimateCharacter(k, 0x26, 0, 1, 0, 0, e->_40, -1);
        } else if (f->_205 == 2) {
            if (f->_206[0] != 0) {
                v = 0x2A;
                if (f->_206[0] == 3) {
                    v = 0x2B;
                } else if (f->_206[0] == 4) {
                    v = 0x2C;
                }
                if (anim == 0x2A || anim == 0x2B || anim == 0x2C) {
                    AnimateCharacter(k, v, 1, 2, 1, 0, e->_40, -1);
                } else {
                    AnimateCharacter(k, v, 1, 1, 1, 0, e->_40, -1);
                }
            } else if (anim == 0x2A) {
                AnimateCharacter(k, 0x28, 1, 2, 1, 0, e->_40, -1);
            } else {
                AnimateCharacter(k, 0x28, 1, 1, 1, 0, e->_40, 0);
            }
        } else if (f->_205 >= 3) {
            AnimateCharacter(k, 0x27, 0, 1, 0, 0, e->_40, -1);
        }
        goto done;
    }
    spd = e->_00;
    if (spd > lbl_3_rodata_E7C) {
        if (f->_24E[8] != 0) {
            s16 ang = radToShortAngle(f->facing);
            s16 d = fn_3_9FCA4(ang, fn_3_9FB8C(f->velX, f->velZ));
            v = 8; // the original leaves this unset when f[0x256] != 1
            if (f->_24E[8] == 1) {
                v = 8;
                if (d < -0x600 || d > 0x600) {
                    v = 9;
                } else if (d > 0x200) {
                    if (e->_40 == 0) {
                        v = 0xA;
                    } else {
                        v = 0xB;
                    }
                } else if (d < -0x200) {
                    if (e->_40 == 0) {
                        v = 0xB;
                    } else {
                        v = 0xA;
                    }
                }
            }
            AnimateCharacter(k, v, 1, 1, 0, 0, e->_40, -1);
        } else if (f->wallAbility == 1 && anim == 0x28) {
            AnimateCharacter(k, 2, 1, 2, 1, 0, e->_40, -1);
            f->_20A = 1;
        } else if (spd > lbl_3_rodata_E90) {
            AnimateCharacter(k, 5, 1, 1, 0, 0, e->_40, -1);
        } else {
            AnimateCharacter(k, 7, 1, 1, 0, 0, e->_40, -1);
        }
        goto done;
    }
    if (g_Minigame.GameMode_MiniGame == 2 && anim >= 0x3F && anim < 0x4B) {
        return;
    }
    v = 2;
    if (e->_41 == 1) {
        v = 0;
    }
    if (anim == 0x24 || anim == 0x25) {
        if (anim == 0x25) {
            AnimateCharacter(k, 0, 1, 2, 1, 0, e->_40, -1);
        }
    } else if (e->_45 != 0) {
        AnimateCharacter(k, 3, 1, 1, 0, 0, e->_40, -1);
    } else if (f->wallAbility == 1 && anim == 0x28) {
        AnimateCharacter(k, v, 1, 2, 1, 0, e->_40, -1);
        f->_20A = 1;
    } else if (anim == 0xF) {
        AnimateCharacter(k, v, 1, 2, 1, 0, e->_40, -1);
    } else if (i == 1 && g_Ball.framesSinceHit < 0x78) {
        if (g_Ball.framesSinceHit == 0x1E) {
            AnimateCharacter(k, 0x3E, 0, 1, 1, 0, e->_40, -1);
        }
    } else if (anim == 0x3E) {
        AnimateCharacter(k, v, 1, 2, 1, 0, e->_40, -1);
    } else {
        last = -1;
        if (anim == 0x40 || anim == 0x42 || anim == 0x49 || anim == 0x4A) {
            last = 0;
        }
        AnimateCharacter(k, v, 1, 1, 1, 0, e->_40, last);
    }
done:
    if (e->_42 != 0) {
        o->pos.x = e->_10;
        o->pos.z = e->_18;
        e->_42 = 1;
    } else {
        e->_42 = 0;
    }
    if (f->wallAbility == 1 && anim == 0x28 && (o->_068 <= 1 || o->mode[1] == 1)) {
        fn_3_60804(k, 0);
    }
}
#endif

// .text:0x00062904 size:0x24C mapped:0x806A1998
void fn_3_62904(void) {
    int i;
    InMemFielderType* p;
    s16 bs;
    FielderAnimState* a;
    InMemFielderType* f;
    u8 v;
    s16 ang;
    s16 d;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        return;
    }
    p = g_Fielders;
    for (i = 0; i < 9; p++, i++) {
        if (p->_211 != 0) {
            if (g_Fielders[i]._211 != 0) {
#ifdef __MWERKS__
                // &g_UnkAnimation_31EAC[i]._51; integer address math keeps the original register allocation
                u8* q = (u8*)((u32)g_UnkAnimation_31EAC + 0x51 + i * 0x54);
#else
                u8* q = &g_UnkAnimation_31EAC[i]._51;
#endif
                if (*q != 8 && *q != 9) {
                    *q = 8;
                }
            }
            break;
        }
    }
    bs = g_Ball.fielderWBallIndex;
    if (bs < 0 || g_FieldingLogic._111 == 0) {
        return;
    }
    f = &g_Fielders[bs];
    a = &g_UnkAnimation_31EAC[bs];
    if (g_FieldingLogic._135 != 0) {
        f->_1AA = 0;
    }
    g_UnkThrowing_31ACC[0]._10[0] = g_FieldingLogic._135;
    if (g_FieldingLogic._111 == 1) {
        v = 1;
        if (g_FieldingLogic._0E8 >= 0) {
            ang = fn_3_9FB8C(g_FieldingLogic._090.x - f->pos.x, g_FieldingLogic._090.z - f->pos.z);
            d = fn_3_9FCA4(ang, radToShortAngle(f->facing));
            if (d < -0x280) {
                v = 2;
            } else if (d > 0x280) {
                v = 3;
            }
        }
        a->_51 = v;
    } else if (g_FieldingLogic._111 == 2) {
        a->_51 = 4;
    } else if (g_FieldingLogic._111 == 5) {
        s16 ri;
        v = 5;
        ri = g_FieldingLogic._0E8;
        if (ri >= 0) {
            InMemRunnerType* r = &g_Runners[ri];
            ang = fn_3_9FB8C(r->position.x - f->pos.x, r->position.z - f->pos.z);
            d = fn_3_9FCA4(ang, radToShortAngle(f->facing));
            if (d < -0x1C0) {
                v = 7;
            } else if (d > 0x1C0) {
                v = 6;
            }
        }
        a->_51 = v;
    }
}

// .text:0x00062B50 size:0x158 mapped:0x806A1BE4
#define BALL_S (g_Ball.fielderWBallIndex)
#define FL_C4 (g_FieldingLogic._0C4)
#define THR_E (g_UnkThrowing_31ACC[0]._0E)
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
        g_FieldingLogic._10A = 0;
        g_UnkThrowing_31ACC[0]._00 = g_Ball.throwDestination.x;
        g_UnkThrowing_31ACC[0]._04 = g_Ball.throwDestination.y;
        g_UnkThrowing_31ACC[0]._08 = g_Ball.throwDestination.z;
        if (g_FieldingLogic._107 == 1 && bs == 0 && (FL_C4 == 1 || FL_C4 == 2 || FL_C4 == 3) &&
            g_Pitcher.pickOffLoc != 4 && g_Pitcher.pickOffLoc != -1) {
            THR_E = 7;
            return;
        }
        if (g_FieldingLogic.throwSpeedType == 8) {
            THR_E = 3;
        } else if (g_FieldingLogic.throwSpeedType == 9) {
            THR_E = 4;
        } else if (g_FieldingLogic.throwSpeedType == 10) {
            if (bs == 3) {
                THR_E = 5;
            } else {
                THR_E = 6;
            }
        } else if (g_FieldingLogic._109 != 0) {
            THR_E = 2;
        } else {
            THR_E = 1;
        }
    }
}

// .text:0x00062CA8 size:0x9C mapped:0x806A1D3C
void fn_3_62CA8(int i) {
    u8 t;
    CharActor* o;
    InMemFielderType* f;
    FielderAnimState* a = &g_UnkAnimation_31EAC[i];
    f = &g_Fielders[i];
    o = lbl_8036E548.active[i];
    if (a->_4C == 0) {
        t = f->_24E[4];
        a->_4C = t;
        a->_4A = f->_24C;
        if (t == 1 || t == 2) {
            a->_4E = f->_24E[5];
        }
        if (a->_4C != 0) {
            a->_4D = a->_4C;
        }
    }
    if (o != NULL && o->anim[0] == 0x24) {
        a->_4C = 0;
        a->_4F = 0;
    }
}

// .text:0x00062D44 size:0xC0 mapped:0x806A1DD8
void fn_3_62D44(s32 i) {
    u8 t;
    InMemFielderType* f = &g_Fielders[i];
    FielderAnimState* e = &g_UnkAnimation_31EAC[i];
    t = f->_1E5;
    e->_41 = 0;
    if (t == 2) {
        e->_41 = 1;
    } else if (t == 3) {
        e->_41 = 2;
    }
    if (f->_24E[8] != 0 && g_Ball.AtBat_ContactResult == 0 && f->_248 < f->reach[0] &&
        g_Ball.framesUntilBallHitsGround < 0x78 && g_Ball.maxYOfHit > 5.0f && g_FieldingLogic._144 != 0) {
        e->_45 = 1;
    }
}

// .text:0x00062E04 size:0x24 mapped:0x806A1E98
void fn_3_62E04(s32 i) {
    FielderAnimState* e = &g_UnkAnimation_31EAC[i];
    e->_3A = e->_38;
    e->_38 = 0;
}

// .text:0x00062E28 size:0x48 mapped:0x806A1EBC
void fn_3_62E28(void) {
    AnimateCharacter(1, 0x3D, 1, 1, 1, 0, g_Fielders[1].handedness, 0);
}

// .text:0x00062E70 size:0x33C mapped:0x806A1F04
void fn_3_62E70(void) {
    s32 i;
    s32 j;
    s16 bs;
    g_UnkThrowing_31ACC[0]._0C = g_Ball.fielderWBallIndex;
    bs = g_UnkThrowing_31ACC[0]._0C;
    if (bs >= 0 && g_Fielders[bs]._203 != 0) {
        g_UnkThrowing_31ACC[0]._0C = -1;
    }
    if (g_Minigame.GameMode_MiniGame == 0) {
        fn_3_62B50();
        fn_3_62904();
    }
    for (i = 0; i < 9; i++) {
        InMemFielderType* f = &g_Fielders[i];
        FielderAnimState* e = &g_UnkAnimation_31EAC[i];
        CharActor* o;
        u8 t;
        e->_40 = f->handedness;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameFielderIndex[j] == i) {
                    break;
                }
            }
            if (j >= 4) {
                continue;
            }
        }
        if (g_Minigame.GameMode_MiniGame == 2 && (s8)f->minigamePlayer == g_Minigame.minigamePlayerSelectedOrder && g_Minigame.wallBallRotatePitchersInd == 0) {
            continue;
        }
        if (i == 0) {
            t = g_GameLogic.gameStatus;
            if (t == 1) {
                continue;
            }
            if (t == 0) {
                continue;
            }
            if (t == 2 && g_FieldingLogic._117 != 0) {
                continue;
            }
            if (t == 0xB || t == 0x16) {
                continue;
            }
        }
        if (i == 1 && (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0 || g_GameLogic.gameStatus == 0xB)) {
            AnimateCharacter(1, 0x3D, 1, 1, 1, 0, g_Fielders[1].handedness, 0);
            continue;
        }
        e->_00 = f->speed;
        e->_45 = 0;
        o = lbl_8036E548.active[i];
        if (e->_4C == 0) {
            t = f->_24E[4];
            e->_4C = t;
            e->_4A = f->_24C;
            if (t == 1 || t == 2) {
                e->_4E = f->_24E[5];
            }
            if (e->_4C != 0) {
                e->_4D = e->_4C;
            }
        }
        if (o != NULL && o->anim[0] == 0x24) {
            e->_4C = 0;
            e->_4F = 0;
        }
        t = f->_1E5;
        e->_3A = e->_38;
        e->_38 = 0;
        e->_41 = 0;
        if (t == 2) {
            e->_41 = 1;
        } else if (t == 3) {
            e->_41 = 2;
        }
        if (f->_24E[8] != 0 && g_Ball.AtBat_ContactResult == 0 && f->_248 < f->reach[0] &&
            g_Ball.framesUntilBallHitsGround < 0x78 && g_Ball.maxYOfHit > 5.0f && g_FieldingLogic._144 != 0) {
            e->_45 = 1;
        }
        fn_3_61B64(i);
    }
}

#if !NONMATCHING
// Switch jump tables of fn_3_631AC; mwcc emits them itself once the function matches.
void* jumptable_3_data_67BC[18] = {
    (u8*)fn_3_631AC + 0xA8, (u8*)fn_3_631AC + 0x6B4, (u8*)fn_3_631AC + 0xAC, (u8*)fn_3_631AC + 0x1B4,
    (u8*)fn_3_631AC + 0x260, (u8*)fn_3_631AC + 0x288, (u8*)fn_3_631AC + 0x6B4, (u8*)fn_3_631AC + 0x2E4,
    (u8*)fn_3_631AC + 0x340, (u8*)fn_3_631AC + 0x4FC, (u8*)fn_3_631AC + 0x524, (u8*)fn_3_631AC + 0x54C,
    (u8*)fn_3_631AC + 0x574, (u8*)fn_3_631AC + 0x59C, (u8*)fn_3_631AC + 0x5C4, (u8*)fn_3_631AC + 0x60C,
    (u8*)fn_3_631AC + 0x654, (u8*)fn_3_631AC + 0x67C,
};
#endif

// .text:0x000631AC size:0x6C8 mapped:0x806A2240
// NONMATCHING 99%: c/o register swap and scheduling in the prologue (anim init added for safety)
#if NONMATCHING
void fn_3_631AC(s32 a) {
    s32 anim;
    s32 k;
    CharActor** actors;
    CharActor* o;
    InMemRunnerType* r;
    RunnerAnimState* c;
    s32 flag;
    u8 t;
    r = &g_Runners[a];
    k = a + 9;
    c = &lbl_3_common_bss_321A0[a];
    actors = &lbl_8036E548.active[0];
    o = actors[k];
    if (g_d_GameSettings.minigamesEnabled != 0) {
        k = g_Minigame._18FC[a];
        o = actors[k];
    }
    anim = -1; // the original leaves this unset when there is no actor
    if (o != NULL) {
        anim = o->anim[0];
    }
    switch (c->_1B) {
    case 0:
        return;
    case 2:
        flag = 0;
        t = lbl_800E8558[r->charID]._2;
        if (t == 0xE || t == 0x14 || t == 0x1A || t == 0x1E) {
            flag = 1;
        }
        if (r->runningDirectionCode == 1 && r->framesToNextBase < 0xA && g_GameLogic.secondaryGameMode != 6 && flag != 0) {
            AnimateCharacter(k, 0x2E, 0, 1, 0, (s16)(lbl_3_data_7870[r->charID][2] - 0xA), 0, -1);
        } else if (anim == 0x31) {
            AnimateCharacter(k, 0x2D, 1, 2, 0, 0, 0, -1);
        } else {
            AnimateCharacter(k, 0x2D, 1, 1, 0, 0, 0, -1);
        }
        break;
    case 3:
        if (g_Minigame.GameMode_MiniGame != 0) {
            AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, -1);
        } else if (lbl_800E8558[r->charID]._2 == 0xC) {
            AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, -1);
        } else {
            AnimateCharacter(k, 0x38, 1, 1, 1, 0, 0, -1);
        }
        break;
    case 4:
        AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, -1);
        break;
    case 5:
        if (r->runningDirectionCode == 3) {
            AnimateCharacter(k, 0x30, 0, 1, 0, 0x14, 1, -1);
        } else {
            AnimateCharacter(k, 0x30, 0, 1, 0, 0x14, 0, -1);
        }
        break;
    case 7:
        if (r->runnerDirectionCode_stored == 3) {
            AnimateCharacter(k, 0x31, 0, 1, 0, 0, 1, 0);
        } else {
            AnimateCharacter(k, 0x31, 0, 1, 0, 0, 0, 0);
        }
        break;
    case 8:
        if (r->actionStage == 1) {
            if (r->actionFrames_countUp == 1) {
                if (r->actionCode == 2) {
                    AnimateCharacter(k, 0x33, 0, 1, 1, (s16)(lbl_3_data_7760[r->charID * 5 + 2] - r->actionFrames_countDown), 1, -1);
                } else if (r->actionCode == 3) {
                    AnimateCharacter(k, 0x33, 0, 1, 1, (s16)(lbl_3_data_7760[r->charID * 5 + 2] - r->actionFrames_countDown), 1, -1);
                } else if (r->actionInForwardDirectionInd != 0 && r->nextBase != 0) {
                    AnimateCharacter(k, 0x32, 0, 1, 1, (s16)(lbl_3_data_7760[r->charID * 5 + 2] - r->actionFrames_countDown), 1, -1);
                } else {
                    AnimateCharacter(k, 0x34, 0, 1, 1, (s16)(lbl_3_data_7760[r->charID * 5 + 4] - r->actionFrames_countDown), 0, -1);
                }
                if (g_GameLogic.gameStatus == 2) {
                    playSoundEffect(0x171);
                }
            }
        } else if (r->actionStage == 2) {
            if (r->actionFrames_countDown == 1) {
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
        if (r->slideHomeFrames_CountDown == 0 && lbl_3_rodata_E58 != r->velocity.x) {
            AnimateCharacter(k, 0x2D, 1, 1, 0, 0, 0, -1);
        }
        break;
    case 15:
        AnimateCharacter(k, 0x35, 0, 1, 0, (s16)(lbl_3_data_7870[r->charID][1] - r->leadOffTotalFrameCountDown), 0, -1);
        break;
    case 16:
        AnimateCharacter(k, 0x39, 1, 1, 1, 0, 0, 0);
        break;
    case 17:
        if (anim != 0x24) {
            fn_3_90220(r->charID, 10);
        }
        AnimateCharacter(k, 0x24, 0, 1, 1, 0, 0, 0x14);
        break;
    }
}
#endif

// .text:0x00063874 size:0x1C4 mapped:0x806A2908
void fn_3_63874(s32 a) {
    InMemRunnerType* r = &g_Runners[a];
    RunnerAnimState* c = &lbl_3_common_bss_321A0[a];
    u8 t;
    if (g_GameLogic.secondaryGameMode == 6 && g_Minigame._1B15[a] == 1) {
        c->_1B = 0x11;
        return;
    }
    if (r->batterStayInBattersBoxReason != 0) {
        c->_1B = 1;
        return;
    }
    if (r->actionCode != 0) {
        c->_1B = 8;
        return;
    }
    t = r->overRun1BStage;
    if (t >= 2) {
        if (t == 2) {
            c->_1B = 9;
            return;
        }
        c->_1B = 0xA;
        return;
    }
    t = r->overrunBaseStage;
    if (t >= 2) {
        if (t == 2) {
            c->_1B = 0xB;
            return;
        }
        c->_1B = 0xC;
        return;
    }
    t = r->runningToDugoutInd;
    if (t == 1) {
        c->_1B = 0xD;
        return;
    }
    if (t != 0) {
        c->_1B = 0xE;
        return;
    }
    t = r->leadOffStatus;
    if (t == 1) {
        c->_1B = 0xF;
        return;
    }
    if (t == 2) {
        c->_1B = 0x10;
        return;
    }
    if (r->turnaroundCode != 0) {
        c->_1B = 5;
        return;
    }
    t = r->runningDirectionCode;
    if (t == 1 || t == 3) {
        if (r->turningAroundInd != 0 && r->framesSinceLastDirectionChange < lbl_3_data_7870[r->charID][0]) {
            c->_1B = 7;
            return;
        }
        c->_1B = 2;
        return;
    }
    if (r->baseStandingOn >= 0) {
        c->_1B = 3;
        return;
    }
    c->_1B = 4;
}

// .text:0x00063A38 size:0xC0 mapped:0x806A2ACC
void fn_3_63A38(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        RunnerAnimState* c = &lbl_3_common_bss_321A0[i];
        c->_1C = c->_1B;
        if (g_d_GameSettings.minigamesEnabled == 0 || (s8)(u8)g_Minigame._18FC[i] >= 0) {
            if (r->runnerOnFieldOrOutOrScored == 0) {
                c->_1B = 0;
            } else {
                c->_1B = 3;
                c->_00 = r->groundVelocity[0];
                c->_1D = r->runningDirectionCode;
                fn_3_63874(i);
                fn_3_631AC(i);
            }
        }
    }
}

// .text:0x00063AF8 size:0x10E4 mapped:0x806A2B8C
// NONMATCHING 94%: register allocation and branch layout differ
#if NONMATCHING
#define E08_IDLE (lbl_3_common_bss_32220._00)
#define E08_B4 (lbl_3_common_bss_32220._04)
void fn_3_63AF8(void) {
    s32 k = 9;
    u8 inv = g_Batter.batterHand ^ 1;
    CharActor* o;
    GameBss32220* st = &lbl_3_common_bss_32220;
    s16 anim;
    s32 flag;
    s32 shoot;
    if (lbl_8036E548._307D != 0) {
        return;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (g_Minigame.rosterID < 0) {
            return;
        }
        k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID];
    }
    o = lbl_8036E548.active[k];
    if (o == NULL) {
        return;
    }
    anim = o->anim[0];
    if ((anim == 0x5D || anim == 0x5E || anim == 0x5F || anim == 0x60) && o->_06A[0] == 1) {
        fn_3_90220(o->kind, 10);
    }
    anim = o->anim[0];
    if (anim == 0x52 || anim == 0x65) {
        st->_08 = 4;
    }
    if (st->_08 != 0) {
        goto done;
    }
    if (g_FieldingLogic._107 == 1 || g_FieldingLogic._107 == 2 || g_FieldingLogic._107 == 3) {
        if (g_Strikes.outs < 3) {
            AnimateCharacter(k, 0x65, 1, 1, 1, 0, inv, 10);
        }
        goto done;
    }
    if (lbl_3_common_bss_32234._00 == 0) {
        if (g_Runners[0].batterStayInBattersBoxReason == 0) {
            goto done;
        }
        if (g_Runners[0].batterStayInBattersBoxReason >= 2) {
            if (st->_09 == 0) {
                switch (g_Batter.hitTrajectory) {
                case 2:
                    st->_09 = 1;
                    break;
                case 5:
                    if (g_Ball.framesSinceHit >= 5) {
                        st->_09 = 1;
                    }
                    break;
                case 6:
                    AnimateCharacter(k, 0x64, 0, 2, 1, 0, inv, -1);
                    st->_09 = 1;
                    break;
                case 3:
                    AnimateCharacter(k, 0x63, 0, 2, 1, 0, inv, -1);
                    st->_09 = 1;
                    break;
                case 4:
                    AnimateCharacter(k, 0x51, 0, 2, 1, 8, inv, 0);
                    QueueCharacterAnimation(k, 0x52, 1, 1, 0, inv, -1);
                    st->_09 = 1;
                    break;
                }
            }
            goto done;
        }
    }
    if (lbl_3_common_bss_32234._00 != 0) {
        flag = 0;
        if (g_d_GameSettings.GameModeSelected != 2) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                if (g_Minigame._19A5 != 0) {
                    flag = 1;
                    g_Minigame._19A5 = 0;
                }
            } else if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0 && g_GameLogic.playBatterWalkupAnimation == 1) {
                flag = 1;
            }
        }
        if (g_GameLogic.scoutFlag_VsScreenInd != 0) {
            flag = 0;
        }
        if (flag != 0) {
            AnimateCharacter(k, 0x67, 0, 1, 1, 0, inv, 0);
            QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, 0);
        } else {
            AnimateCharacter(k, 0x4B, 1, 2, 1, 0, inv, 0);
            st->_09 = 0;
            E08_IDLE = 0;
        }
        goto done;
    }

    // idle / taunt
    if ((g_Ball.totalFramesAtPlay == 3 || g_GameLogic.gameStatus == 0) && g_Batter.swingInd == 0 && g_Batter.buntStatus == 0) {
        AnimateCharacter(k, 0x4B, 1, 2, 1, 0, inv, 10);
        st->_09 = 0;
        E08_IDLE = 0;
    }
    if (g_Pitcher.pitchTotalTimeCounter == 0) {
        if (g_Batter.swingInd != 0 || g_Batter.buntStatus != 0) {
            E08_IDLE = 0;
        }
        if (g_d_GameSettings.GameModeSelected != 2 && g_d_GameSettings.GameModeSelected != 7) {
            s16 n = 0x7FFF;
            if (E08_IDLE < 0x7FFE) {
                n = E08_IDLE + 1;
            }
            E08_IDLE = n;
            if (n > 0x258 && g_Batter.chargeStatus == 0 && g_Ball.StaticRandomInt1 % 120 == 0) {
                E08_IDLE = 0;
                AnimateCharacter(k, 0x66, 0, 2, 1, 0, inv, -1);
                QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, 0xF);
            }
        }
    }

    // bunt / stance
    if (g_Batter.chargeStatus != 0 && g_Batter.swingInd == 0) {
        if (g_Pitcher.pitcherActionState != 5) {
            if (g_Batter.chargeStatus == 3) {
                anim = o->anim[0];
                if (anim != 0x58 && anim != 0x68 && anim != 0x4B) {
                    if (anim == 0x55) {
                        AnimateCharacter(k, 0x58, 1, 1, 1, 0, inv, 0x14);
                        QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, 0xC);
                    } else {
                        AnimateCharacter(k, 0x68, 0, 1, 1, 0, inv, 0x14);
                        QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, 0xC);
                    }
                }
            } else if (g_Batter.chargeStatus == 1 && g_Batter.chargeFrames == 1) {
                if (o->anim[0] == 0x4B) {
                    AnimateCharacter(k, 0x4C, 0, 3, 1, g_Batter.chargeFrames, inv, 0x14);
                } else {
                    AnimateCharacter(k, 0x4C, 0, 3, 1, g_Batter.chargeFrames, inv, 0);
                }
                QueueCharacterAnimation(k, 0x55, 1, 1, 0, inv, 0xC);
            }
        }
    } else if (st->_0B != 0) {
        if (g_Pitcher.pitcherActionState == 4 && g_Ball.postPitchResultCounter >= 3) {
            st->_0B = 0;
            if (o->anim[0] == 0x55) {
                AnimateCharacter(k, 0x58, 0, 1, 1, 0, inv, 0x14);
                QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, -1);
            } else {
                AnimateCharacter(k, 0x68, 0, 1, 1, 0, inv, 0x14);
                QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, 0xC);
            }
        } else {
            E08_B4++;
        }
    } else if (g_Pitcher.pitcherActionState == 2 && g_Batter.buntStatus == 0 && g_Batter.swingInd == 0 && g_Pitcher.windupCountdownUntilBallReleased <= 8) {
        AnimateCharacter(k, 0x57, 0, 3, 1, 0, inv, 0x14);
        QueueCharacterAnimation(k, 0x56, 1, 1, 0, inv, 0);
        st->_0B = 1;
        E08_B4 = 0;
    }

    // swing results
    if (g_Batter.buntStatus != 0) {
        st->_0B = 0;
        if (g_Pitcher.strikeOutOrWalk != 2) {
            if (g_Batter.missedBuntStatus == 1) {
                AnimateCharacter(k, 0x5C, 0, 1, 1, 0, inv, -1);
                QueueCharacterAnimation(k, 0x4B, 1, 1, 0, inv, 10);
            } else if (g_Batter.buntStatus == 1) {
                if (g_Pitcher.framesUntilUnhittable > 5 && g_Pitcher.framesUntilUnhittable < 0xF) {
                    AnimateCharacter(k, 0x59, 0, 1, 1, 5, inv, -1);
                    goto runners;
                }
                AnimateCharacter(k, 0x59, 0, 1, 1, 0, inv, -1);
            } else if (g_Batter.buntStatus == 2) {
                AnimateCharacter(k, 0x5A, 0, 2, 1, 0, inv, -1);
            } else if (g_Batter.buntStatus == 4 && g_Pitcher.pitcherActionState != 4 && g_Pitcher.pitcherActionState != 5) {
                AnimateCharacter(k, 0x5B, 0, 1, 1, 0, inv, -1);
            } else if (g_Batter.buntStatus == 4 && g_Pitcher.pitcherActionState == 4) {
                AnimateCharacter(k, 0x4B, 1, 2, 1, 0, inv, 0xF);
            } else if ((g_Batter.buntStatus == 5 || g_Batter.buntStatus == 7) && o->anim[0] != 0x4B) {
                AnimateCharacter(k, 0x5B, 0, 1, 1, 0, inv, -1);
            }
        }
        if (o->anim[0] == 0x5B && o->anim[1] != 0x4B && o->_06A[0] > 0 && g_Batter.buntStatus != 1 && st->_0B == 0) {
            AnimateCharacter(k, 0x4B, 1, 2, 1, 0, inv, 0xF);
        }
    } else if (g_Batter.swingInd != 0) {
        st->_0B = 0;
        if (g_Batter.framesSinceStartOfSwing == 1) {
            if (g_Batter.swingMissThatWasHittable != 0) {
                st->_0C = g_Pitcher.framesUntilBallReachesBatterZ - 6;
            } else {
                st->_0C = 0;
            }
            st->_0D = 0;
        }
        if (st->_0C <= 0 && st->_0D == 0) {
            if (g_Batter.hitGeneralType == 0) {
                AnimateCharacter(k, 0x4D, 0, 1, 1, (s16)-st->_0C, inv, 2);
                QueueCharacterAnimation(k, 0x50, 0, 1, 0, inv, 0);
            } else {
                AnimateCharacter(k, 0x53, 0, 1, 1, (s16)-st->_0C, inv, 2);
                QueueCharacterAnimation(k, 0x54, 0, 1, 0, inv, 0);
            }
            st->_0D = 1;
        } else {
            st->_0C--;
        }
        anim = o->anim[0];
        if (anim == 0x50 || anim == 0x54) {
            s16 next = o->anim[1];
            if (next != 0x4E && next != 0x4F && o->_06A[0] > 0) {
                if (anim == 0x54) {
                    AnimateCharacter(k, 0x4F, 0, 2, 1, 0, inv, -1);
                } else {
                    AnimateCharacter(k, 0x4E, 0, 2, 1, 0, inv, -1);
                }
            }
        }
        anim = o->anim[0];
        if ((anim == 0x4E || anim == 0x4F) && o->anim[1] != 0x4B && o->_06A[0] > 0 && st->_0B == 0) {
            AnimateCharacter(k, 0x4B, 1, 2, 1, 0, inv, 10);
        }
    }

runners:
    flag = 0;
    if (g_Runners[1].runnerOnFieldOrOutOrScored == 1 && g_Runners[1].furthestBaseForcedToGoToOnWalk != 0) {
        flag = 1;
    }
    if (g_Runners[2].runnerOnFieldOrOutOrScored == 1 && g_Runners[2].furthestBaseForcedToGoToOnWalk != 0) {
        flag = 1;
    }
    if (g_Runners[3].runnerOnFieldOrOutOrScored == 1 && g_Runners[3].furthestBaseForcedToGoToOnWalk != 0) {
        flag = 1;
    }
    if (g_Batter.hitByPitch != 0) {
        if (st->_08 == 0 || st->_08 == 5) {
            AnimateCharacter(k, 0x62, 0, 1, 1, 0, inv, -1);
            st->_08 = 3;
            fn_3_90220(g_Batter.charID, 10);
        }
        goto done;
    }
    shoot = 0;
    if (g_Pitcher.pitcherActionState == 5) {
        shoot = 1;
    } else if (g_Strikes.GameControls_StrikeBallBitVector >= 0x20 && g_Batter.missSwingOrBunt == 1 &&
               (o->anim[0] == 0x4D || o->anim[0] == 0x53) && o->_068 == 1 &&
               g_Batter.contactMadeInd == 0) {
        shoot = 1;
    }
    if (g_Pitcher.strikeOutOrWalk == 2) {
        if (flag != 0) {
            if (g_Ball.framesSinceHit > 0) {
                AnimateCharacter(k, 0x66, 0, 1, 1, 0, inv, -1);
            }
        } else if (g_Batter.buntStatus == 4) {
            AnimateCharacter(k, 0x61, 0, 1, 1, 0, inv, 0);
        } else {
            AnimateCharacter(k, 0x61, 0, 1, 1, 0, inv, 0);
        }
    } else if (shoot != 0 && st->_08 == 0) {
        if (g_Batter.buntStatus == 4) {
            AnimateCharacter(k, 0x5F, 0, 1, 1, 0, inv, -1);
            st->_08 = 1;
        } else {
            anim = o->anim[0];
            if (anim == 0x4D || anim == 0x53) {
                if (flag != 0 && g_Strikes.storedOuts < 2) {
                    AnimateCharacter(k, 0x5E, 0, 2, 1, 0, inv, -1);
                    QueueCharacterAnimation(k, 0x66, 1, 1, 0, inv, -1);
                } else if (anim == 0x53) {
                    AnimateCharacter(k, 0x60, 0, 2, 1, 0, inv, -1);
                } else {
                    AnimateCharacter(k, 0x5E, 0, 2, 1, 0, inv, -1);
                }
                st->_08 = 1;
            } else if (anim == 0x4B || anim == 0x4C || (anim >= 0x55 && anim <= 0x58) || anim == 0x68) {
                AnimateCharacter(k, 0x5F, 0, 1, 1, 0, inv, -1);
                st->_08 = 1;
            } else if (anim == 0x4E || anim == 0x4F) {
                AnimateCharacter(k, 0x5F, 0, 2, 1, 0, inv, -1);
                st->_08 = 1;
            }
        }
    }
done:
    o->_273 = 1;
}
#undef E08_IDLE
#undef E08_B4
#endif

// .text:0x00064BDC size:0xC08 mapped:0x806A3C70
// NONMATCHING 90%: register allocation and branch layout differ. Like the original, the later
// branches read the actor without re-checking it for NULL.
#if NONMATCHING
static inline BOOL fn_3_64BDC_isSpecialChar(s8 c) {
    return c == 3 || c == 0xE || c == 0x25 || c == 0x26 || lbl_800E8558[c]._2 == 0x17;
}

void fn_3_64BDC(void) {
    s32 k = 0;
    u8 inv = 0;
    CharActor* o;
    GameBss32230* st = &lbl_3_common_bss_32230;
    u8 mode;
    s32 taunt;
    s32 next;
    if (g_Pitcher.handedness != 0) {
        inv = 1;
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (g_Minigame.minigamePlayerSelectedOrder < 0) {
            return;
        }
        k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
    }
    o = lbl_8036E548.active[k];
    if (o != NULL) {
        if (o->anim[0] == 0x44 && o->_06A[0] == 1) {
            fn_3_90220(o->kind, 4);
        } else if (o->anim[0] == 0x45 && o->_06A[0] == 1) {
            fn_3_90220(o->kind, 3);
        }
    }
    mode = g_GameLogic.gameStatus;
    if (mode != 0 && mode != 1 && mode != 2 && mode != 0x16 && !(g_Minigame.GameMode_MiniGame == 2 && mode == 7) &&
        !(mode == 0xB && lbl_3_common_bss_32234._00 != 0)) {
        if (g_d_GameSettings.minigamesEnabled != 0 && mode == 0x1A) {
            AnimateCharacter(k, 0x3F, 1, 2, 1, 0, inv, -1);
            st->_02 = 1;
        } else {
            st->_02 = 0;
        }
        return;
    }
    if (g_GameLogic.secondaryGameMode == 0xB && g_Practice.instructionNumber < 0 && g_Practice._1C7 != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceLevel == 4) {
        return;
    }
    if (g_FieldingLogic._107 != 0) {
        st->_02 = 0;
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 2) {
        if (g_Minigame.wallBallRotatePitchersInd != 0) {
            return;
        }
        k = g_Minigame.minigamePlayerSelectedOrder;
    }
    if (lbl_3_common_bss_32234._00 != 0) {
        // between pitches
        taunt = 0;
        if (g_d_GameSettings.GameModeSelected != 2 && g_d_GameSettings.minigamesEnabled == 0) {
            if (g_Pitcher.playStartOfGameAnimation != 0) {
                g_Pitcher.playStartOfGameAnimation = 0;
                taunt = 1;
                if (fn_3_6D564(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) < lbl_3_data_5EDC[3]) {
                    taunt = 2;
                }
            } else if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0 &&
                       fn_3_6D564(g_GameLogic.teamFielding, g_Pitcher.rosterID, 0) < lbl_3_data_5EDC[3]) {
                taunt = 2;
            }
        }
        if (taunt == 2) {
            AnimateCharacter(k, 0x46, 0, 1, 1, 0, inv, 0);
            QueueCharacterAnimation(k, 0x3F, 1, 1, 0, inv, -1);
        } else if (taunt == 1) {
            AnimateCharacter(k, 0x48, 0, 1, 1, 0, inv, 0);
            QueueCharacterAnimation(k, 0x3F, 1, 1, 0, inv, -1);
        } else {
            AnimateCharacter(k, 0x3F, 1, 1, 1, 0, inv, 0);
            st->_02 = 1;
        }
        return;
    }
    if (g_Pitcher.pitchTotalTimeCounter == 0) {
        // idle on the mound
        if (st->_02 != 1 && !(g_GameLogic.secondaryGameMode == 0xB && g_Practice.instructionNumber < 0 && g_Practice.guidedPracticeCompletionRelated != 0) &&
            o->anim[1] != 0x41 && o->anim[1] != 0x43) {
            if (g_Minigame.GameMode_MiniGame == 2) {
                if (g_Minigame.soloMinigameDifficulty != 3) {
                    AnimateCharacter(k, 0x3F, 1, 1, 1, 0, inv, 0xC);
                } else if (g_Minigame.miniGameTurnCounter == 0) {
                    AnimateCharacter(k, 0x3F, 1, 1, 1, 0, inv, 0xC);
                } else {
                    AnimateCharacter(k, 0x3F, 1, 2, 1, 0, inv, 0xC);
                }
            } else {
                AnimateCharacter(k, 0x3F, 1, 2, 1, 0, inv, 0xC);
            }
        }
        st->_02 = 1;
        if (g_d_GameSettings.GameModeSelected != 2 && g_d_GameSettings.GameModeSelected != 6 && g_d_GameSettings.GameModeSelected != 7) {
            s16 n = 0x7FFF;
            if (st->_00 < 0x7FFE) {
                n = st->_00 + 1;
            }
            st->_00 = n;
            if (n > 0x244 && g_Ball.StaticRandomInt1 % 120 == 0) {
                st->_00 = 0;
                AnimateCharacter(k, 0x47, 0, 2, 1, 0, inv, -1);
                QueueCharacterAnimation(k, 0x3F, 1, 1, 0, inv, 0xC);
            }
        }
        return;
    }
    st->_00 = 0;
    if (g_Pitcher.pitchTotalTimeCounter == 1) {
        // wind-up start
        next = 1;
        if (g_Pitcher.ChargePitchType >= 1 || g_Pitcher.TypeOfPitch != 0) {
            AnimateCharacter(k, 0x40, 0, 1, 1, 0, inv, -1);
            next = 0;
            g_Pitcher.windupCountdownUntilBallReleased = g_Pitcher.pitchWindUpCountDown;
        } else {
            AnimateCharacter(k, 0x42, 0, 1, 1, 0, inv, -1);
            g_Pitcher.windupCountdownUntilBallReleased = g_Pitcher.curvePitchWindupFrames;
        }
        if (o->kind == 0xB || o->kind == 0x1B) {
            next = 0;
        }
        if (fn_3_64BDC_isSpecialChar(o->kind)) {
            QueueCharacterAnimation(k, 0x3F, 1, 1, 0, inv, 0xC);
        } else {
            QueueCharacterAnimation(k, next + 0x49, 1, 1, 0, inv, -1);
        }
        st->_02 = 2;
        return;
    }
    if (g_Minigame.GameMode_MiniGame == 2 && g_Minigame.soloMinigameDifficulty == 3) {
        if (g_Minigame._1A8C[0] != 0) {
            if (o->anim[0] == 0x40) {
                AnimateCharacter(k, 0x41, 0, 1, 1, 0, inv, -1);
            } else {
                AnimateCharacter(k, 0x43, 0, 1, 1, 0, inv, -1);
            }
            QueueCharacterAnimation(k, 0x3F, 1, 1, 0, inv, 0xC);
            st->_02 = 3;
            g_Minigame._1A8C[0] = 0;
        }
        return;
    }
    if (g_Pitcher.pitcherActionState == 4 && g_Ball.postPitchResultCounter > 1 && st->_02 != 3) {
        // release
        if (g_Minigame.GameMode_MiniGame == 2 && g_Minigame.soloMinigameDifficulty != 3) {
            return;
        }
        if (g_GameLogic.secondaryGameMode == 0xB && g_Practice.instructionNumber < 0 && g_Practice.guidedPracticeCompletionRelated != 0) {
            if (st->_02 != 4) {
                AnimateCharacter(k, 0x44, 0, 2, 1, 0, inv, -1);
            }
            st->_02 = 4;
            return;
        }
        if (g_Pitcher.miniGameRelated == 0) {
            return;
        }
        if (fn_3_64BDC_isSpecialChar(o->kind)) {
            AnimateCharacter(k, 0x3F, 1, 2, 1, 0, inv, 0xC);
            st->_02 = 3;
            return;
        }
        {
            s16 anim = o->anim[0];
            u8 speed;
            if (anim == 0x40 || anim == 0x42) {
                speed = 2;
            } else {
                speed = 1;
            }
            if (anim == 0x40 || anim == 0x49) {
                AnimateCharacter(k, 0x41, 0, speed, 1, 0, inv, 0xC);
            } else {
                AnimateCharacter(k, 0x43, 0, speed, 1, 0, inv, 0xC);
            }
        }
        QueueCharacterAnimation(k, 0x3F, 1, 1, 0, inv, 0xC);
        st->_02 = 3;
        return;
    }
    if (g_Pitcher.pitcherActionState != 5) {
        return;
    }
    if (!((g_Pitcher.strikeOutOrWalk == 1 && st->_02 != 4) || ((g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) && st->_02 != 5))) {
        return;
    }
    if (o->_068 != 0 && o->anim[0] != 0x49 && o->anim[0] != 0x4A) {
        return;
    }
    if (g_Pitcher.strikeOutOrWalk == 1) {
        if (lbl_800E8558[o->kind]._2 == 0xB) {
            AnimateCharacter(k, 0x44, 0, 1, 1, 0, inv, 0);
        } else {
            AnimateCharacter(k, 0x44, 0, 1, 1, 0, inv, -1);
        }
        st->_02 = 4;
    } else {
        AnimateCharacter(k, 0x45, 0, 1, 1, 0, inv, -1);
        st->_02 = 5;
    }
    {
        f32 x = g_UnkAnimation_31EAC[0]._2C.x;
        f32 z = g_UnkAnimation_31EAC[0]._2C.z;
        VecSrcDst ray;
        CollisionStruct hit;
        g_Pitcher.pitcher.x = x;
        g_Pitcher.pitcher.z = z;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            InMemFielderType* f = &g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame.minigamePlayerSelectedOrder]];
            f->pos.x = x;
            f->pos.z = z;
        } else {
            g_Fielders[0].pos.x = x;
            g_Fielders[0].pos.z = z;
        }
        ray.src.x = g_Fielders[0].pos.x;
        ray.src.y = lbl_3_rodata_E98;
        ray.src.z = g_Fielders[0].pos.z;
        ray.dst.x = g_Fielders[0].pos.x;
        ray.dst.y = lbl_3_rodata_E9C;
        ray.dst.z = g_Fielders[0].pos.z;
        checkCollision(&ray, &hit, 0, 0);
        g_Fielders[0].height = -hit.position.y;
        g_Fielders[0]._010 = -hit.position.y;
    }
}
#endif

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
    u8* res = &lbl_3_common_bss_32234.result[0];
    if (g_GameLogic.gameStatus == 0xE) {
        if (g_d_GameSettings.minigamesEnabled != 0 && g_GameLogic._125 == 1) {
            doit = 1;
        }
        if (g_d_GameSettings.minigamesEnabled == 0 && g_GameLogic._125 == 3) {
            doit = 1;
        }
    }
    if (g_GameLogic.gameStatus == 0x27 && g_GameLogic._125 == 0) {
        doit = 1;
    }
    if (doit != 0) {
        if (g_d_GameSettings.minigamesEnabled == 0) {
            if (lbl_80353A90._104 == 2) {
                res[0] = 1;
            } else if (lbl_80353A90._104 == 3) {
                res[0] = 2;
            } else {
                res[0] = 0;
            }
        } else if (g_GameLogic.gameStatus == 0x27 && g_Minigame._1A3D == 1) {
            s8 me = (u8)g_Minigame._1908;
            found = 0;
            for (j = 0; j < 4; j++) {
                if (g_Minigame.resultSlot[j].player == me && g_Minigame.resultSlot[j].taken == 0) {
                    found = 1;
                    break;
                }
            }
            if (g_Minigame.resultSlot[0].taken == 0 && g_Minigame.resultSlot[1].taken == 0 && g_Minigame.resultSlot[2].taken == 0 && g_Minigame.resultSlot[3].taken == 0) {
                res[me] = 2;
            } else if (found != 0) {
                res[me] = 0;
            } else {
                res[me] = 1;
            }
        } else if (g_Minigame.miniGameNumberOfParticipants == 1) {
            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[j] >= 0) {
                    if (g_Minigame.soloMinigameDifficulty == 3) {
                        if (g_Minigame._19AA != 0) {
                            res[j] = 0;
                        } else {
                            res[j] = 1;
                        }
                    } else if (g_Minigame._1A37 == 1) {
                        res[j] = 0;
                    } else {
                        res[j] = 1;
                    }
                }
            }
        } else {
            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[j] >= 0) {
                    if (g_Minigame.challenge_minigame_haven_tWonYetIndicator != 0) {
                        res[j] = 2;
                    } else if (g_Minigame.minigameControlStruct[0]._1C[j] == 1) {
                        res[j] = 0;
                    } else {
                        res[j] = 1;
                    }
                }
            }
        }
    }
    if ((g_d_GameSettings.minigamesEnabled == 0 && g_GameLogic._125 < 4) || (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame._19A9 <= 1)) {
        for (j = 0; j < 4; j++) {
            if (g_d_GameSettings.minigamesEnabled == 0) {
                k = 9;
            } else {
                k = g_Minigame.minigameControlStruct[0].characterIndex[j];
                if (k < 0) {
                    continue;
                }
            }
            if (g_d_GameSettings.minigamesEnabled == 0) {
                flag = 1;
            } else {
                s8 c = (s8)g_Minigame._19E8[j]._4;
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
            if (g_d_GameSettings.minigamesEnabled == 0) {
                break;
            }
        }
    } else if ((g_d_GameSettings.minigamesEnabled == 0 && g_GameLogic._125 == 4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) ||
               (g_d_GameSettings.minigamesEnabled != 0 && g_Minigame._19A9 == 2) ||
               (g_GameLogic.gameStatus == 0x27 && g_GameLogic._125 == 0)) {
        g_Minigame._19A9 = 3;
        for (j = 0; j < 4; j++) {
            if (g_d_GameSettings.minigamesEnabled == 0) {
                k = 9;
            } else {
                k = g_Minigame.minigameControlStruct[0].characterIndex[j];
                if (k < 0) {
                    continue;
                }
            }
            if (g_GameLogic.gameStatus == 0x27 && g_Minigame._1908 >= 0 && g_Minigame._1908 != j) {
                continue;
            }
            if (g_d_GameSettings.minigamesEnabled == 0) {
                flag = 1;
                snd = (s8)lbl_80353A90._101[2];
            } else {
                s8 c = (s8)g_Minigame._19E8[j]._4;
                if (c == 0 || c == 2) {
                    snd = g_Minigame.minigameControlStruct[0].charID[j];
                    flag = 1;
                } else {
                    flag = 0;
                    snd = g_Minigame.minigameControlStruct[0].charID[j];
                }
            }
            if (res[j] == 0) {
                AnimateCharacter(k, 0x6D, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(k, 0x6B, 1, 1, 0, flag, -1);
                fn_3_90220(snd, 7);
            } else if (res[j] == 1) {
                AnimateCharacter(k, 0x70, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(k, 0x71, 1, 1, 0, flag, -1);
                if (g_Minigame.miniGameNumberOfParticipants > 1) {
                    fn_3_90150(snd, 9);
                } else {
                    fn_3_90220(snd, 9);
                }
            } else {
                AnimateCharacter(k, 0x73, 0, 1, 1, 0, flag, -1);
                QueueCharacterAnimation(k, 0x74, 1, 1, 0, flag, -1);
            }
            if (g_d_GameSettings.minigamesEnabled == 0) {
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
    CharActor* o;
    int i;
    for (i = 0; i < 4; i++) {
        idx = i;
        o = lbl_8036E548.active[i];
        flag = 0;
        if (g_d_GameSettings.GameModeSelected == 2) {
            idx = 9;
            o = lbl_8036E548.active[9];
        }
        if (o != NULL) {
            c = *(s8*)&g_Minigame._19E8[i]._4; // read as signed
            if (c == 0 || c == 2) {
                flag = 1;
            }
            if (g_Minigame._19E8[i]._2 < 0) {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            } else if ((s8)g_Minigame._19E8[i]._1 != 0) {
                if (o->anim[0] == 0x69) {
                    AnimateCharacter(idx, 0x6A, 0, 1, 1, 0, flag, 0);
                    QueueCharacterAnimation(idx, 0x6B, 1, 1, 0, flag, -1);
                }
            } else {
                AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
            }
            if (g_d_GameSettings.GameModeSelected == 2) {
                break;
            }
        }
    }
}

// .text:0x00066140 size:0x3BC mapped:0x806A51D4
// NONMATCHING 93%: register allocation; fn_3_65FE0 and fn_3_63A38 written out inline, as in the original
#if NONMATCHING
void fn_3_66140(void) {
    s32 i;
    u8 mode;
    for (i = 0; i < 9; i++) {
        g_UnkAnimation_31EAC[i]._48 = 0;
    }
    mode = g_GameLogic.gameStatus;
    if (g_Minigame._19A9 != 0 || mode == 0x22 || mode == 0x26 || mode == 0x27) {
        fn_3_657E4();
        return;
    }
    if (mode >= 0x1B && mode <= 0x29) {
        {
            int flag;
            int idx;
            s8 c;
            CharActor* o;
            for (i = 0; i < 4; i++) {
                idx = i;
                o = lbl_8036E548.active[i];
                flag = 0;
                if (g_d_GameSettings.GameModeSelected == 2) {
                    idx = 9;
                    o = lbl_8036E548.active[9];
                }
                if (o != NULL) {
                    c = *(s8*)&g_Minigame._19E8[i]._4; // read as signed
                    if (c == 0 || c == 2) {
                        flag = 1;
                    }
                    if (g_Minigame._19E8[i]._2 < 0) {
                        AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
                    } else if ((s8)g_Minigame._19E8[i]._1 != 0) {
                        if (o->anim[0] == 0x69) {
                            AnimateCharacter(idx, 0x6A, 0, 1, 1, 0, flag, 0);
                            QueueCharacterAnimation(idx, 0x6B, 1, 1, 0, flag, -1);
                        }
                    } else {
                        AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
                    }
                    if (g_d_GameSettings.GameModeSelected == 2) {
                        break;
                    }
                }
            }
        }
        return;
    }
    if ((mode >= 3 && mode <= 7) || g_GameLogic.secondaryGameMode == 0xA || g_GameLogic.secondaryGameMode == 0x12 || g_GameLogic.secondaryGameMode == 0xF) {
        if (!(g_Minigame.GameMode_MiniGame == 2 && mode == 7)) {
            for (i = 0; i < 4; i++) {
                AnimateCharacter(i, 2, 1, 1, 0, 0, 0, 0);
            }
            return;
        }
    }
    if (lbl_803CBC3C[0] != 0) {
        return;
    }
    if (lbl_3_common_bss_32234._01 != 0) {
        fn_3_6714C(0);
        lbl_3_common_bss_32234._01 = 0;
        return;
    }
    if (g_GameLogic.minigameLastTurnSuccessInd != 0 && g_Ball.totalFramesAtPlay == 0) {
        if (!(g_Minigame.GameMode_MiniGame == 2 && g_Minigame.soloMinigameDifficulty == 3)) {
            fn_3_6714C(0);
            return;
        }
    }
    lbl_3_common_bss_32234._00 = 0;
    fn_3_64BDC();
    fn_3_63AF8();
    fn_3_62E70();
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        RunnerAnimState* c = &lbl_3_common_bss_321A0[i];
        c->_1C = c->_1B;
        if (g_d_GameSettings.minigamesEnabled == 0 || (s8)(u8)g_Minigame._18FC[i] >= 0) {
            if (r->runnerOnFieldOrOutOrScored == 0) {
                c->_1B = 0;
            } else {
                c->_1B = 3;
                c->_00 = r->groundVelocity[0];
                c->_1D = r->runningDirectionCode;
                fn_3_63874(i);
                fn_3_631AC(i);
            }
        }
    }
}
#endif

// .text:0x000664FC size:0x3C0 mapped:0x806A5590
// NONMATCHING 96%: register allocation; fn_3_65FE0 and fn_3_63A38 written out inline, as in the original
#if NONMATCHING
void fn_3_664FC(void) {
    s32 i;
    u8 mode;
    for (i = 0; i < 9; i++) {
        g_UnkAnimation_31EAC[i]._48 = 0;
    }
    mode = g_GameLogic.gameStatus;
    if (mode == 0xB || (mode >= 3 && mode <= 5) || g_GameLogic.secondaryGameMode == 0xA || g_GameLogic.secondaryGameMode == 0x12 ||
        (g_d_GameSettings.GameModeSelected == 2 && g_Practice.tutorialState == 0)) {
        if (g_d_GameSettings.GameModeSelected == 2 && g_GameLogic.secondaryGameMode == 0xA && g_Practice.practiceType_1 == 6) {
            {
                int flag;
                int idx;
                s8 c;
                CharActor* o;
                for (i = 0; i < 4; i++) {
                    idx = i;
                    o = lbl_8036E548.active[i];
                    flag = 0;
                    if (g_d_GameSettings.GameModeSelected == 2) {
                        idx = 9;
                        o = lbl_8036E548.active[9];
                    }
                    if (o != NULL) {
                        c = *(s8*)&g_Minigame._19E8[i]._4; // read as signed
                        if (c == 0 || c == 2) {
                            flag = 1;
                        }
                        if (g_Minigame._19E8[i]._2 < 0) {
                            AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
                        } else if ((s8)g_Minigame._19E8[i]._1 != 0) {
                            if (o->anim[0] == 0x69) {
                                AnimateCharacter(idx, 0x6A, 0, 1, 1, 0, flag, 0);
                                QueueCharacterAnimation(idx, 0x6B, 1, 1, 0, flag, -1);
                            }
                        } else {
                            AnimateCharacter(idx, 0x69, 1, 1, 1, 0, flag, 0);
                        }
                        if (g_d_GameSettings.GameModeSelected == 2) {
                            break;
                        }
                    }
                }
            }
        } else {
            for (i = 0; i < 13; i++) {
                AnimateCharacter(i, 2, 1, 1, 0, 0, 0, 0);
            }
        }
        return;
    }
    if (mode == 0xE) {
        if (g_GameLogic._125 > 2) {
            fn_3_657E4();
        }
        return;
    }
    if (lbl_3_common_bss_1323C->_25C != 0) {
        fn_3_22C10();
        return;
    }
    if (lbl_3_common_bss_32234._01 != 0) {
        fn_3_6714C(0);
        lbl_3_common_bss_32234._01 = 0;
        return;
    }
    if (g_GameLogic.minigameLastTurnSuccessInd != 0 && g_Ball.totalFramesAtPlay == 0) {
        fn_3_6714C(0);
        return;
    }
    lbl_3_common_bss_32234._00 = 0;
    fn_3_64BDC();
    fn_3_63AF8();
    fn_3_62E70();
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        RunnerAnimState* c = &lbl_3_common_bss_321A0[i];
        c->_1C = c->_1B;
        if (g_d_GameSettings.minigamesEnabled == 0 || (s8)(u8)g_Minigame._18FC[i] >= 0) {
            if (r->runnerOnFieldOrOutOrScored == 0) {
                c->_1B = 0;
            } else {
                c->_1B = 3;
                c->_00 = r->groundVelocity[0];
                c->_1D = r->runningDirectionCode;
                fn_3_63874(i);
                fn_3_631AC(i);
            }
        }
    }
}
#endif

// .text:0x000668BC size:0x874 mapped:0x806A5950
// NONMATCHING 89%: register allocation and loop addressing differ
#if NONMATCHING
void fn_3_668BC(void) {
    s32 i;
    s32 j;
    s32 k;
    CharActor** actors = &lbl_8036E548.active[0];
    CharActor* o;
    FielderAnimState* e;
    InMemFielderType* f;
    s16 anim;
    if (g_GameLogic.gameStatus == 3 || g_GameLogic.gameStatus == 5) {
        return;
    }
    for (i = 0; i < 13; i++) {
        lbl_8036E548.actors[i]._274 = 0;
    }
    if (g_d_GameSettings.minigamesEnabled != 0 &&
        ((g_GameLogic.gameStatus >= 0x1B && g_GameLogic.gameStatus <= 0x21) || g_GameLogic.gameStatus == 5)) {
        return;
    }

    // remaining frames of each actor's current animation
    for (i = 0; i < 13; i++) {
        o = actors[i];
        if (o != NULL && o->mode[0] != 0) {
            f32 len = lbl_3_rodata_E9C;
            u16 bone;
            if (o != NULL) {
                bone = o->jointIdx[4];
            } else {
                bone = 0xFFFF;
            }
            if (bone != 0xFFFF) {
                len = fn_800B4A44(*fn_800111D8(o), bone);
            }
            o->_068 = len / o->_04C;
        }
    }
    if (g_Stats.replayInd != 0 && g_Stats.playFrameCounter == 1 && actors[9] != NULL && g_Stats._34 != 0) {
        actors[9]->_068 = g_Stats._34 - 1;
        actors[9]->_070 = g_Stats._34 - 1;
    }

    // fielders
    f = g_Fielders;
    e = g_UnkAnimation_31EAC;
    for (i = 0; i < 9; i++, e++, f++) {
        j = 0;
        k = i;
        e->_1C = e->_10;
        o = actors[i];
        f->_20A = 0;
        e->_20 = e->_14;
        e->_24 = e->_18;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            for (j = 0; j < 4; j++) {
                if (g_Minigame.minigameFielderIndex[j] == i) {
                    break;
                }
            }
            if (j >= 4) {
                continue;
            }
            k = g_Minigame.minigameControlStruct[0].characterIndex[j];
            o = actors[j];
        }
        if (e->_50 != 0) {
            f->_1EC = 1;
        } else {
            f->_1EC = 0;
        }
        if (e->_4F != 0 && f->_24C <= 1) {
            f->_1ED = 1;
        } else {
            f->_1ED = 0;
        }
        if (o != NULL) {
            if (e->_42 != 0) {
                getAnimRelatedCoordinates(k, 4, &e->_2C);
                f->velX = e->_2C.x - f->pos.x;
                f->velZ = e->_2C.z - f->pos.z;
                f->speed = sqrt_E08(f->velX * f->velX + f->velZ * f->velZ);
                f->pos.x = e->_2C.x;
                f->pos.z = e->_2C.z;
                f->_1F9[2] = 1;
                fn_3_60A98(i, o);
            } else {
                f->_1F9[2] = 0;
                if (f->speed > f->maxSpeed) {
                    f->speed = f->maxSpeed;
                }
            }
        }
        f->_1F9[0] = e->_43;
        f->_25A = 0;
        if (e->_4F != 0 && e->_4D != 0) {
            if (e->_4D == 3) {
                f->_25A = 2;
            } else if (e->_4D < 3 && e->_4D >= 1) {
                f->_25A = 1;
            }
        }
        if (e->_44 != 0) {
            f->_1FD = 1;
            if (f->_1AA < 0x7FFE) {
                f->_1AA = f->_1AA + 1;
            } else {
                f->_1AA = 0x7FFF;
            }
        } else {
            f->_1FD = 0;
            f->_1AA = 0;
        }
        if (o != NULL && o->anim[0] == 0xF) {
            f->_1FE = 1;
        } else {
            f->_1FE = 0;
        }
        e->_3C = fn_8001B35C(k, 1);
        e->_3E = fn_8001B35C(k, 0);
    }

    // pitcher
    if (g_FieldingLogic._117 != 0) {
        k = 0;
        o = actors[0];
        if (g_d_GameSettings.minigamesEnabled != 0) {
            k = g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.minigamePlayerSelectedOrder];
            o = actors[k];
        }
        getAnimRelatedCoordinates(k, 4, &g_UnkAnimation_31EAC[0]._2C);
        g_Pitcher.pitcherCoord.x = g_UnkAnimation_31EAC[0]._2C.x;
        g_Pitcher.pitcherCoord.z = g_UnkAnimation_31EAC[0]._2C.z;
        if (o != NULL) {
            anim = o->anim[0];
            if (anim == 0x40 || anim == 0x42 || (anim == 0x41 && o->_068 < 0x1E) ||
                (anim == 0x43 && o->_068 < 0x1E)) {
                g_Pitcher.pitchDeliveryAnimationPlaying = 1;
            } else {
                g_Pitcher.pitchDeliveryAnimationPlaying = 0;
            }
        } else {
            g_Pitcher.pitchDeliveryAnimationPlaying = 0;
        }
    }

    // batter
    if (lbl_8036E548._307D != 0) {
        return;
    }
    o = actors[9];
    if (g_d_GameSettings.minigamesEnabled != 0) {
        o = &lbl_8036E548.actors[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame.rosterID]];
    }
    if (lbl_3_common_bss_32220._08 == 0) {
        if (o != NULL && (o->anim[0] == 0x4B || o->anim[0] == 0x66)) {
            g_Batter.noSwingAnimationInd = 1;
        } else {
            g_Batter.noSwingAnimationInd = 0;
        }
    }
    if (o == NULL) {
        return;
    }
    if (o->anim[0] == 0x67) {
        g_Batter.beginningOfABAnimationOccuring = 1;
    } else {
        g_Batter.beginningOfABAnimationOccuring = 0;
    }
    if (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 2) {
        switch (o->anim[0]) {
        case 0x4D:
            lbl_3_common_bss_32220.state = 1;
            (lbl_3_common_bss_32220._02)++;
            break;
        case 0x53:
            lbl_3_common_bss_32220.state = 2;
            (lbl_3_common_bss_32220._02)++;
            break;
        case 0x50:
            lbl_3_common_bss_32220.state = 3;
            (lbl_3_common_bss_32220._02)++;
            break;
        case 0x54:
            lbl_3_common_bss_32220.state = 4;
            (lbl_3_common_bss_32220._02)++;
            break;
        default:
            if (lbl_3_common_bss_32220.state != 0) {
                if (lbl_3_common_bss_32220.state == 9) {
                    lbl_3_common_bss_32220.state = 0;
                } else {
                    lbl_3_common_bss_32220.state = 9;
                    lbl_3_common_bss_32220._02 = 0;
                }
            }
            break;
        }
    }
    anim = o->anim[0];
    if (anim == 0x5E || anim == 0x5F || anim == 0x60 || anim == 0x61 || anim == 0x62) {
        lbl_3_common_bss_32220._06 = o->_068;
    }
}
#endif

// .text:0x00067130 size:0x1C mapped:0x806A61C4

void fn_3_67130(void) {
    lbl_3_common_bss_32220._08 = 0;
    lbl_3_common_bss_32220._0B = 0;
    lbl_3_common_bss_32220._04 = 0;
}

// .text:0x0006714C size:0x394 mapped:0x806A61E0
// NONMATCHING 96%: register allocation only (fn_3_67130 and fn_3_63A38 are written out inline, as in the original)
#if NONMATCHING
void fn_3_6714C(s32 player) {
    s32 i;
    s32 k;
    FielderAnimState* e;
    CharActor* o;
    fn_8001C528();
    e = g_UnkAnimation_31EAC;
    lbl_3_common_bss_32230._00 = 0;
    lbl_3_common_bss_32220._06 = 0;
    lbl_3_common_bss_32220._09 = 0;
    lbl_3_common_bss_32220._00 = 0;
    lbl_3_common_bss_32220.state = 0;
    lbl_3_common_bss_32220._0D = 0;
    g_UnkThrowing_31ACC[0]._0E = 0;
    g_UnkThrowing_31ACC[1]._0E = 0;
    g_UnkThrowing_31ACC[2]._0E = 0;
    g_UnkThrowing_31ACC[3]._0E = 0;
    for (i = 0; i < 9; i++, e++) {
        k = i;
        if (g_d_GameSettings.minigamesEnabled != 0) {
            for (k = 0; k < 4; k++) {
                if (g_Minigame.minigameFielderIndex[k] == i) {
                    break;
                }
            }
            if (k >= 4) {
                continue;
            }
        }
        e->_38 = 0;
        e->_3A = 0;
        e->_42 = 0;
        o = lbl_8036E548.active[k];
        e->_43 = 0;
        e->_44 = 0;
        e->_46 = 0;
        e->_47 = 0;
        e->_4C = 0;
        e->_4F = 0;
        e->_50 = 0;
        e->_51 = 0;
        e->_00 = lbl_3_rodata_E58;
        if (o != NULL && (o == NULL || o->parts == NULL)) {
            fn_3_60804(i, 0);
        }
    }
    if (lbl_8036E548._307D == 0) {
        for (i = 0; i < 4; i++) {
            if (g_d_GameSettings.minigamesEnabled == 0 || (i == 0 && g_Minigame.rosterID >= 0) ||
                g_Minigame._18FC[i] >= 0) {
                RunnerAnimState* c = &lbl_3_common_bss_321A0[i];
                c->_10 = -1;
                c->_18 = 0;
                c->_19 = 0;
                c->_16 = 0;
            }
        }
    }
    lbl_3_common_bss_32220._08 = 0;
    lbl_3_common_bss_32220._0B = 0;
    lbl_3_common_bss_32220._04 = 0;
    if (player == 0) {
        lbl_3_common_bss_32234._00 = 1;
        fn_3_64BDC();
        fn_3_63AF8();
    }
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_3_62E70();
        return;
    }
    fn_3_62E70();
    for (i = 0; i < 4; i++) {
        InMemRunnerType* r = &g_Runners[i];
        RunnerAnimState* c = &lbl_3_common_bss_321A0[i];
        c->_1C = c->_1B;
        if (g_d_GameSettings.minigamesEnabled == 0 || (s8)(u8)g_Minigame._18FC[i] >= 0) {
            if (r->runnerOnFieldOrOutOrScored == 0) {
                c->_1B = 0;
            } else {
                c->_1B = 3;
                c->_00 = r->groundVelocity[0];
                c->_1D = r->runningDirectionCode;
                fn_3_63874(i);
                fn_3_631AC(i);
            }
        }
    }
}
#endif


#pragma dont_inline off

// Animation tables: lbl_3_data_65F0 (this file) and lbl_3_data_6660 (read by rep_2390).
// .data 0x000065F0..0x00006804
E08AnimTable lbl_3_data_65F0 = {
    {4, 4, 4, 4, 4, 4, 4, 4, 4, 20, 5, 5, 5, 15, 15, 0},
    8,
    {
        0, 0, 0, 20, 20, 20, 60, 60, 60, 40, 40, 40, 40, 40, 40, 40,
        40, 40, 80, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
        20, 20, 20, 20, 20, 20, 0, 5, 5, 5, 15, 5, 5, 5, 0,
    },
    {10, 30},
    {0, 0, 0, 48, 0, 50, 0, 50, 0, 80, 0, 80, 0, 25, 0, 37, 0, 37},
    {{19, 18, 17}, {25, 24, 23}, {22, 21, 20}},
    {0, 0},
    20,
    {0, 0, 0},
    {5, 20},
};
u16 lbl_3_data_6660[174] = {
    22, 16, 23, 17, 24, 18, 25, 19,
    26, 20, 27, 21, 32, 28, 33, 29,
    34, 30, 35, 31, 38, 37, 40, 39,
    61, 60, 65535, 0, 74, 75, 65535, 0,
    47, 52, 48, 53, 49, 54, 50, 55,
    51, 56, 65535, 0, 65, 71, 66, 72,
    67, 73, 68, 74, 69, 75, 70, 76,
    65535, 0, 47, 52, 65535, 0, 0, 1,
    2, 3, 4, 5, 6, 7, 8, 9,
    14, 15, 13, 12, 11, 10, 22, 23,
    24, 25, 26, 27, 16, 17, 18, 19,
    20, 21, 32, 33, 34, 35, 28, 29,
    30, 31, 36, 38, 37, 40, 39, 41,
    42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57,
    58, 59, 61, 60, 0, 0, 0, 0,
    0, 0, 0, 0, 1, 515, 1029, 1543,
    2057, 2571, 3085, 14, 3856, 4370, 4884, 5398,
    5888, 0, 0, 0, 0, 0, 0, 0,
    0, 256, 0, 0, 256, 0, 257, 257,
    0, 0, 0, 0, 1, 0, 0, 257,
    0, 0, 0, 0, 257, 0,
};

