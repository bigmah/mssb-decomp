#include "game/rep_AC8.h"
#include "game/rep_D0.h"
#include "header_rep_data.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"
extern s16 radToShortAngle(f32 v);

extern u8 g_Runners[];
extern f32 lbl_3_rodata_C50;
extern f32 lbl_3_rodata_B78;
extern f32 lbl_3_rodata_B68;
void fn_3_A0F0(void);
int fn_3_B7E10(f32 a, f32 b);
u32 fn_3_8FF5C(s32 id, f32 x, f32 y, f32 z);
void fn_3_16696C(void);
extern void fn_3_161588(int, s16);
void fn_3_59918(s32 x);
u32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);
unsigned long sndFXCtrl(u32 vid, u8 ctrl, u8 value);
extern u8 g_hitShorts[];
extern u8 g_UnkSound_32718[];
extern u8 lbl_3_common_bss_37400[];
extern u8 lbl_800E8558[];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
void fn_3_522E0(int i, int k, f32* outX, f32* outZ, f32* reach, f32 dx, f32 dz);
int fn_3_B7C2C(Vec* a, Vec* b);
s32 fn_3_BBBC(f32* out, s32 n, s32 step, f32 x, f32 z);
extern u8 lbl_3_data_4924[];
extern u8 lbl_3_data_490C[];
typedef struct { f32 a, b, c, d, e; } Ent14;
extern Ent14 lbl_3_data_47D0[];
extern f32 lbl_3_rodata_C54;
extern f32 lbl_3_rodata_C48;
extern u8 g_Strikes[];
extern u8 g_Ball[];
extern u8 g_Fielders[];
extern s16 lbl_3_data_1C3C[];
extern f32 lbl_3_data_450C[][2];
extern u8 lbl_3_data_4290[];
extern f32 lbl_3_rodata_B74;
extern f32 lbl_3_rodata_BA4;
int RandomInt_Game(int max);
extern u8 lbl_3_data_4900[][3];
extern u8 g_Pitcher[];
extern f32 lbl_3_rodata_BC4;
extern f32 lbl_3_rodata_BC8;
void fn_3_31C50(void);
BOOL checkFieldingStat(int, int, int);
f32 shortAngleToRad_Capped(s16);
extern f32 lbl_3_rodata_B90;
void fn_3_53F48(void);
extern f32 lbl_3_rodata_BB4;
extern f32 lbl_3_rodata_B64;
void getComponentsFromRad(f32 v, f32* x, f32* y);
extern u8 lbl_3_data_4714[][4][6];
extern f32 lbl_3_data_5FC4[];
void playSoundEffect(int);
extern f32 lbl_3_rodata_BCC;
/* lbl_3_data_3C40: per-state fielder action table (animation id, state handler) */
typedef struct {
    int anim;
    void (*fn)(int i);
} FielderActEntry;
/* lbl_3_bss_C8: per-pad stick-angle history (20 frames each) */
typedef struct {
    s16 unk0[2];
    s16 hist[4][20];
    s16 cur;
    s16 unkA6;
    s16 tmp[20];
} StickHistory;
extern StickHistory lbl_3_bss_C8;
extern f32 lbl_3_data_4794[];
extern int fn_3_B7CDC(f32, f32);
extern f32 lbl_3_data_5CDC[];
extern f32 lbl_3_data_5D08[];
extern s16 lbl_3_data_79B4[];
u8 fn_3_107D70(s8 i);
extern f32 lbl_3_rodata_BBC;
extern f32 lbl_3_rodata_B84;
extern f32 lbl_3_rodata_B88;
extern f32 lbl_3_rodata_B6C;
extern f32 lbl_3_rodata_BA8;
extern f32 lbl_3_rodata_BAC;
extern f32 lbl_3_rodata_BB0;
extern f32 lbl_3_rodata_BD0;
extern f32 lbl_3_data_1C44[];
extern s16 lbl_3_data_1C54[];
int RandomInt_Game_Range(int min, int max);
struct _VecXYZ;
f32 game_atan2(f32 x, f32 y);
extern f32 lbl_3_rodata_B68;
f32 fn_3_9EFD0(struct _VecXYZ* a, struct _VecXYZ* b, struct _VecXYZ* c, struct _VecXYZ* d);
extern u8 g_Batter[];
BOOL getAnimRelatedCoordinates(s32 index, s32 joint, Vec* out);
extern u8 lbl_3_common_bss_34C90[];
extern f32 lbl_3_rodata_B94;
extern f32 lbl_3_rodata_B98;
extern f32 lbl_3_rodata_B60;
void fn_3_1AE44(u8, u16, f32, f32, f32);
extern u8 lbl_3_data_4884[];
typedef struct { f32 a, b, c, d; } Ent16;
extern u8 lbl_8036E548[];
extern f32 lbl_3_rodata_B24;
extern void fn_3_1682AC(int, int);
extern f32 lbl_3_rodata_B20;
extern f32 lbl_3_rodata_B9C;
extern f32 lbl_3_rodata_B48;
extern u8 g_GameLogic[];
extern u8 g_Practice[];
extern u8 g_d_GameSettings[];
extern int fn_3_9FB8C(f32 x, f32 y);
extern int fn_3_9FCA4(s16 a, s16 b);
extern u8 g_FieldingLogic[];
extern u8 lbl_3_data_3C40[];
extern u8 lbl_3_data_4444[];
extern u8 g_RunningLogic[];
extern f64 atan2(f64, f64);
extern u8 lbl_3_data_4930[];
extern s16 lbl_3_data_49DC[];
extern u8 g_Minigame[];
extern f32 lbl_3_rodata_1498;
extern f32 lbl_3_rodata_BE4;
extern f32 lbl_3_rodata_B8C;
extern f32 lbl_3_rodata_B64;
extern f32 lbl_3_rodata_BB8;
extern f32 lbl_3_rodata_CBC;
extern f32 lbl_3_rodata_BDC;
extern f32 lbl_3_rodata_BA0;
extern s16 fn_3_9FCF8(s16, s16);
extern f32 fn_3_9CE0(f32, f32);
extern f32 lbl_3_rodata_BFC;
extern f32 lbl_3_rodata_B7C;
extern f32 lbl_3_rodata_BD8;
extern f32 lbl_3_rodata_C00;
extern s16 lbl_3_bss_170;
extern s16 lbl_3_bss_16C;
extern u8 g_Controls[];
extern s16 lbl_3_data_484C[];
extern f32 lbl_3_rodata_B70;
extern f32 lbl_3_rodata_C24;
extern int __float_nan[];
#define NAN (*(f32*)__float_nan)
int __abs(int);
#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif
f64 __frsqrte(f64);
extern f64 atan2(f64, f64);
extern f64 lbl_3_rodata_B30;
extern f64 lbl_3_rodata_B38;
extern f64 lbl_3_rodata_B40;
extern f32 lbl_3_rodata_C38;
extern f32 lbl_3_rodata_B80;
extern f32 lbl_3_data_18984[];
extern f32 g_AiLogic[];
extern void fn_3_58F58(int, f32*, f32*);
#define SQRT_L(x)                                                                                  \
    do {                                                                                           \
        if ((x) > 0.0f) {                                                                          \
            f64 xd = (f64)(x);                                                                     \
            f64 guess = __frsqrte(xd);                                                             \
            guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);            \
            guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);            \
            guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);            \
            (x) = (f32)(xd * guess);                                                               \
        } else if ((x) < lbl_3_rodata_B40) {                                                       \
            (x) = NAN;                                                                             \
        } else if (isnan(x)) {                                                                     \
            (x) = NAN;                                                                             \
        }                                                                                          \
    } while (0)
/* squared xz distance, written out so CW does not fuse it into fmadds */
#define DIST2_XZ(ax, az, bx, bz) (((ax) - (bx)) * ((ax) - (bx)) + ((az) - (bz)) * ((az) - (bz)))
#pragma dont_inline on
#pragma dont_inline off
static inline void SetFielderAct(int i, int state, int off) {
    u8* f = g_Fielders + i * 0x268;
    int d;
    if (i != -1) {
        d = *(int*)(lbl_3_data_3C40 + off);
        f[0x1D3] = state;
        if (d >= 0) {
            g_FieldingLogic[i + 0xF8] = d;
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
}
static inline void SetFielderAct2(int i, int val, int state) {
    u8* f = g_Fielders + i * 0x268;
    f[0x1D3] = state;
    if (val >= 0) {
        g_FieldingLogic[i + 0xF8] = val;
    }
    f[0x1D5] = 0;
    f[0x1D6] = 0;
    *(s16*)(f + 0x1A4) = 0;
    *(s16*)(f + 0x1AC) = 0;
    f[0x1FF] = 0;
}
#pragma dont_inline on

// .text:0x000251E4 size:0x1C0 mapped:0x80664278
extern void getComponentsFromSAng(s16 ang, f32* x, f32* y);
extern s16 fn_3_9FE6C_normalizeAngle(s16);
extern void fn_3_6C854(int, int);
extern f32 lbl_3_rodata_B18;
extern f32 lbl_3_rodata_B1C;
int fn_3_51798(int i, f32* out);
void fn_3_251E4(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 pos[3];
    int r;
    if (*(s16*)(f + 0x1BE) < 0x7FFE) {
        *(s16*)(f + 0x1BE) = *(s16*)(f + 0x1BE) + 1;
    } else {
        *(s16*)(f + 0x1BE) = 0x7FFF;
    }
    *(s16*)(f + 0x1C0) = *(s16*)(f + 0x1C0) - 1;
    if (f[0x210] == 1) {
        if (*(s16*)(f + 0x1C0) <= 0) {
            f[0x210] = 2;
            *(s16*)(f + 0x1BE) = 0;
            *(s16*)(f + 0x1C0) = lbl_3_data_49DC[0x22];
            return;
        }
        *(f32*)(f + 0x174) = *(f32*)(f + 0x174) * *(f32*)(lbl_3_data_4930 + 0x8C);
        *(f32*)(f + 0x50) = *(f32*)(f + 0x174);
        getComponentsFromSAng(*(s16*)(f + 0x1C2), (f32*)(f + 0x38), (f32*)(f + 0x3C));
        *(f32*)(f + 0x30) = *(f32*)(f + 0x38) * *(f32*)(f + 0x50);
        *(f32*)(f + 0x34) = *(f32*)(f + 0x3C) * *(f32*)(f + 0x50);
        r = fn_3_51798(i, pos);
        if (r != 0) {
            if (r == 2 && !(pos[0] > lbl_3_rodata_B18) && !(pos[0] < lbl_3_rodata_B1C)) {
                *(f32*)(f + 0x30) = pos[0] - *(f32*)f;
                *(f32*)(f + 0x34) = pos[2] - *(f32*)(f + 8);
                *(f32*)f = pos[0];
                *(f32*)(f + 8) = pos[2];
            } else {
                *(f32*)(f + 0x50) = lbl_3_rodata_B20;
                *(f32*)(f + 0x30) = lbl_3_rodata_B20;
                *(f32*)(f + 0x34) = lbl_3_rodata_B20;
            }
        } else {
            *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
            *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
        }
        *(f32*)(f + 0x14) = *(f32*)f;
        *(f32*)(f + 0x1C) = *(f32*)(f + 8);
        return;
    }
    if (*(s16*)(f + 0x1C0) <= 0) {
        f[0x210] = 0;
    }
}

// .text:0x000253A4 size:0x2A4 mapped:0x80664438
extern u32 fn_3_90220(s32 idx, s32 off);
extern void fn_3_A9354(int, int);
int fn_3_253A4(int i, s16 ang) {
    u8* f = g_Fielders + i * 0x268;
    if (f[0x207] != 0 || f[0x205] != 0 || f[0x25E] != 0) {
        return 0;
    }
    *(s16*)(f + 0x1C2) = ang;
    f[0x210] = 1;
    *(s16*)(f + 0x1BE) = 0;
    *(s16*)(f + 0x1C0) = lbl_3_data_49DC[0x21];
    *(f32*)(f + 0x174) = *(f32*)(lbl_3_data_4930 + 0x88);
    if (f[0x252] == 4 || f[0x252] == 5) {
        *(f32*)(f + 0x174) = lbl_3_rodata_B20;
    }
    if (f[0x207] != 0) {
        *(f32*)(f + 0x174) = lbl_3_rodata_B20;
    }
    if (g_d_GameSettings[0x11] != 0) {
        u8* m = g_Minigame + f[0x20D];
        if (m[0x18D8] == 0) {
            fn_3_6C854(*(s8*)(m + 0x18CC), 2);
        }
    } else if (g_GameLogic[*(int*)(g_GameLogic + 8) + 0x13E] == 0) {
        fn_3_6C854(*(int*)(g_GameLogic + 8), 2);
    }
    fn_3_90220(*(s16*)(f + 0x17A), 10);
    if (*(s16*)(g_Ball + 0x1B78) == i) {
        fn_3_A9354(i, 1);
        g_FieldingLogic[0x13B] = 1;
        g_FieldingLogic[0x111] = 0;
    }
    if (f[0x252] != 0) {
        if (g_d_GameSettings[7] != 6 && i != *(s16*)(g_FieldingLogic + 0xB0) && i != -1) {
            f[0x1D3] = 0xC;
            if (*(int*)(lbl_3_data_3C40 + 0x60) >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x60);
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
        f[0x252] = 0;
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        *(s16*)(f + 0x194) = 0;
        f[0x1E9] = 0;
        f[0x1DF] = 0;
        f[0x205] = 0;
        f[0x25E] = 0;
        if (f[0x1E8] != 0) {
            f[0x1E8] = 2;
        }
        if (*(s16*)(g_Ball + 0x1B78) >= 0 && g_Ball[0x1BF0] != 0) {
            g_Ball[0x1BF0] = 0;
            *(f32*)(g_Ball + 0) = *(f32*)(g_Ball + 0x1B38);
            *(f32*)(g_Ball + 4) = *(f32*)(g_Ball + 0x1B3C);
            *(f32*)(g_Ball + 8) = *(f32*)(g_Ball + 0x1B40);
        }
    }
    f[0x262] = 0;
    f[0x203] = 0;
    f[0x20F] = 0;
    f[0x1EE] = 0;
    g_Ball[0x1BF0] = 0;
    return 1;
}

// .text:0x00025648 size:0x1FC mapped:0x806646DC
void fn_3_25648(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 pos[3];
    int r;
    *(s16*)(f + 0x1BA) = *(s16*)(f + 0x1BA) - 1;
    if (*(s16*)(f + 0x1BA) <= 0) {
        f[0x20F] = 0;
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        *(f32*)(f + 0x30) = lbl_3_rodata_B20;
        *(f32*)(f + 0x34) = lbl_3_rodata_B20;
        return;
    }
    *(s16*)(f + 0x1B8) = *(s16*)(f + 0x1B8) + 1;
    *(s16*)(f + 0x1BC) = fn_3_9FE6C_normalizeAngle(*(s16*)(f + 0x1BC) + lbl_3_data_49DC[0x20]);
    *(f32*)(f + 0x50) = *(f32*)(lbl_3_data_4930 + 0x84);
    getComponentsFromSAng(*(s16*)(f + 0x1BC), (f32*)(f + 0x38), (f32*)(f + 0x3C));
    *(f32*)(f + 0x30) = *(f32*)(f + 0x38) * *(f32*)(f + 0x50);
    *(f32*)(f + 0x34) = *(f32*)(f + 0x3C) * *(f32*)(f + 0x50);
    r = fn_3_51798(i, pos);
    if (r != 0) {
        if (r == 2 && !(pos[0] > lbl_3_rodata_B18) && !(pos[0] < lbl_3_rodata_B1C)) {
            *(f32*)(f + 0x30) = pos[0] - *(f32*)f;
            *(f32*)(f + 0x34) = pos[2] - *(f32*)(f + 8);
            *(f32*)f = pos[0];
            *(f32*)(f + 8) = pos[2];
        } else {
            *(f32*)(f + 0x50) = lbl_3_rodata_B20;
            *(f32*)(f + 0x30) = lbl_3_rodata_B20;
            *(f32*)(f + 0x34) = lbl_3_rodata_B20;
        }
    } else {
        *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
        *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
    }
    *(f32*)(f + 0x14) = *(f32*)f;
    *(f32*)(f + 0x1C) = *(f32*)(f + 8);
    if (g_d_GameSettings[0x11] != 0) {
        u8* m = g_Minigame + f[0x20D];
        if (m[0x18D8] == 0) {
            fn_3_6C854(*(s8*)(m + 0x18CC), 0);
        }
    } else if (g_GameLogic[*(int*)(g_GameLogic + 8) + 0x13E] == 0) {
        fn_3_6C854(*(int*)(g_GameLogic + 8), 0);
    }
}

// .text:0x00025844 size:0x94 mapped:0x806648D8
void fn_3_25844(int i, int j) {
    u8* f = g_Fielders + i * 0x268;
    if (f[0x20F] == 0) {
        *(s16*)(f + 0x1BC) = radToShortAngle(*(f32*)(f + 0x48));
        f[0x20F] = 1;
        *(s16*)(f + 0x1B8) = 0;
        *(s16*)(f + 0x1BA) = lbl_3_data_49DC[j + 0x1D];
        f[0x252] = 0;
        f[0x203] = 0;
        f[0x205] = 0;
        f[0x207] = 0;
        f[0x1EE] = 0;
    }
}

// .text:0x000258D8 size:0x190 mapped:0x8066496C
// ~60%: type reg r7 vs r8, lfsx table access, float op order/scheduling differ
int fn_3_258D8(int i) {
    u8* f = g_Fielders + i * 0x268;
    int type;
    Ent16* t;
    int n;
    int k;
    f32 sc;
    if ((*(u8**)(g_FieldingLogic + 0x8C))[2] == 0) {
        return 0;
    }
    if (f[0x25A] != 0) {
        return 0;
    }
    type = f[0x1CC];
    f[0x203] = 1;
    *(f32*)(f + 0x15C) = lbl_3_rodata_B20;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            i = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            i = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    *(f32*)(f + 0x164) = ((Ent16*)lbl_3_data_4884)[type].a;
    t = &((Ent16*)lbl_3_data_4884)[type];
    sc = t->c;
    *(f32*)(f + 0x160) = *(f32*)(f + 0x38) * lbl_3_rodata_B24 * sc;
    *(f32*)(f + 0x168) = *(f32*)(f + 0x3C) * lbl_3_rodata_B24 * sc;
    k = (int)t->d;
    n = (int)(*(f32*)(f + 0x164) / t->b);
    *(s16*)(f + 0x1AE) = (n + n) + k + 2;
    *(s16*)(f + 0x1B0) = n + 1;
    f[0x204] = 0;
    if (type != 0) {
        fn_3_1682AC(((int*)lbl_8036E548)[i + 0xB14], 6);
    }
    (*(u8**)(g_FieldingLogic + 0x8C))[2] = 0;
    return 1;
}

// .text:0x00025A68 size:0x1D8 mapped:0x80664AFC
extern f32 lbl_3_rodata_B28[];
void fn_3_25A68(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 d;
    f32 pos[1];
    *(f32*)(f + 0x228) = *(f32*)(f + 0x228) * lbl_3_rodata_B28[0];
    *(f32*)(f + 0x230) = *(f32*)(f + 0x230) * lbl_3_rodata_B28[0];
    *(f32*)(f + 0x30) = *(f32*)(f + 0x228);
    *(f32*)(f + 0x34) = *(f32*)(f + 0x230);
    d = *(f32*)(f + 0x30) * *(f32*)(f + 0x30) + *(f32*)(f + 0x34) * *(f32*)(f + 0x34);
    SQRT_L(d);
    *(f32*)(f + 0x50) = d;
    if (fn_3_51798(i, pos) != 0) {
        *(f32*)f = *(f32*)(f + 0xD4);
        *(f32*)(f + 8) = *(f32*)(f + 0xD8);
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x30) = 0.0f;
        *(f32*)(f + 0x34) = 0.0f;
    } else {
        *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
        *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
    }
    *(f32*)(f + 0x14) = *(f32*)f;
    *(f32*)(f + 0x1C) = *(f32*)(f + 8);
    f[0x1F0] = 1;
}

// .text:0x00025C40 size:0x5A8 mapped:0x80664CD4
// NONMATCHING 88%: float register allocation and lhax/lfsu addressing of the pitch table / ball position differ
#if NONMATCHING
void fn_3_25C40(int i) {
    u8* f = g_Fielders + i * 0x268;
    int who = i;
    Vec v;
    f32 dx;
    f32 dz;
    f32 dy;
    f32 d;
    f32 t;
    s16 cnt;
    s16* tbl;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    if (g_Ball[0x1BF0] == 0) {
        if (f[0x252] == 3) {
            if (*(s16*)(f + 0x24C) > lbl_3_data_49DC[0x1A]) {
                return;
            }
            dz = *(f32*)(f + 0x224) - *(f32*)(f + 8);
            dx = *(f32*)(f + 0x21C) - *(f32*)f;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            tbl = lbl_3_data_79B4 + *(s16*)(f + 0x17A) * 8;
            t = lbl_3_rodata_B48 * tbl[4] / d;
            *(f32*)(g_Ball + 0x1B30) = lbl_3_rodata_B48 * tbl[7];
            dx *= t;
            dz *= t;
            *(f32*)(g_Ball + 0x1B2C) = *(f32*)f + dx;
            *(f32*)(g_Ball + 0x1B34) = *(f32*)(f + 8) + dz;
        } else {
            if (*(s16*)(f + 0x24C) > lbl_3_data_49DC[0x18]) {
                return;
            }
            dz = *(f32*)(f + 0x224) - *(f32*)(f + 8);
            dx = *(f32*)(f + 0x21C) - *(f32*)f;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            tbl = lbl_3_data_79B4 + *(s16*)(f + 0x17A) * 8;
            t = lbl_3_rodata_B48 * tbl[0] / d;
            dx *= t;
            dz *= t;
            *(f32*)(g_Ball + 0x1B2C) = *(f32*)f + dx;
            *(f32*)(g_Ball + 0x1B34) = *(f32*)(f + 8) + dz;
            *(f32*)(g_Ball + 0x1B30) = lbl_3_rodata_B48 * tbl[2];
        }
        *(f32*)(g_Ball + 0x1B38) = *(f32*)(g_Ball + 0);
        *(f32*)(g_Ball + 0x1B3C) = *(f32*)(g_Ball + 4);
        *(f32*)(g_Ball + 0x1B40) = *(f32*)(g_Ball + 8);
        g_Ball[0x1BF0] = *(s16*)(f + 0x24C);
        if (f[0x265] == 0 && f[0x252] == 3) {
            *(s16*)(f + 0x24C) = lbl_3_data_49DC[0x25];
            g_Ball[0x1BF0] = lbl_3_data_49DC[0x25];
        }
        g_Batter[0xA8] = 0;
    } else {
        if (f[0x265] != 0) {
            getAnimRelatedCoordinates(who, 0x42, &v);
            v.y = -v.y;
        } else if (f[0x252] == 3) {
            v.x = *(f32*)(g_Ball + 0x1B2C);
            v.y = *(f32*)(g_Ball + 0x1B30);
            v.z = *(f32*)(g_Ball + 0x1B34);
        } else if (f[0x1C7] == 0) {
            getAnimRelatedCoordinates(who, 0x4F, &v);
        } else {
            getAnimRelatedCoordinates(who, 0x4E, &v);
        }
        cnt = *(s16*)(f + 0x24C);
        t = (f32)cnt / (f32)g_Ball[0x1BF0];
        dy = *(f32*)(g_Ball + 4) - v.y;
        dx = *(f32*)(g_Ball + 0) - v.x;
        dz = *(f32*)(g_Ball + 8) - v.z;
        dy *= t;
        dx *= t;
        dz *= t;
        *(f32*)(g_Ball + 0x1B3C) = v.y + dy;
        *(f32*)(g_Ball + 0x1B38) = v.x + dx;
        *(f32*)(g_Ball + 0x1B40) = v.z + dz;
        if (cnt == 1) {
            g_Ball[0x1BF0] = 0;
        }
        g_Ball[0x1BEF] = 1;
    }
}
#endif

// .text:0x000261E8 size:0x47C mapped:0x8066527C
// NONMATCHING 98%: load order of 0x12C/0x148 in the height lerp and one f0/f1 swap
#if NONMATCHING
void fn_3_261E8(int i) {
    u8* f = g_Fielders + i * 0x268;
    Vec v;
    f32 n;
    f32 h;
    f32 d;
    int hit;
    s16 cnt = *(s16*)(f + 0x24C);
    if (f[0x252] == 4) {
        if (f[0x25C] != 0) {
            n = f[0x25C];
            *(f32*)(f + 0x228) = (*(f32*)(f + 0x128) - *(f32*)f) / n;
            *(f32*)(f + 0x230) = (*(f32*)(f + 0x130) - *(f32*)(f + 8)) / n;
            *(f32*)(f + 0x148) += (*(f32*)(f + 0x12C) - *(f32*)(f + 0x148)) / n;
            f[0x25C] = f[0x25C] - 1;
            if (f[0x25C] == 0) {
                fn_3_90220(*(s16*)(f + 0x17A), 0);
            }
        } else {
            n = cnt;
            *(f32*)(f + 0x228) = (*(f32*)(f + 0x134) - *(f32*)f) / n;
            *(f32*)(f + 0x230) = (*(f32*)(f + 0x13C) - *(f32*)(f + 8)) / n;
            h = (*(f32*)(f + 0x138) - *(f32*)(f + 0x148)) / n;
            *(f32*)(f + 0x164) = h;
            *(f32*)(f + 0x148) += h;
        }
    } else if (*(s16*)(f + 0x24E) <= 1) {
        *(f32*)(f + 0x228) = 0.0f;
        *(f32*)(f + 0x22C) = 0.0f;
        *(f32*)(f + 0x230) = 0.0f;
        if (f[0x252] == 3 || f[0x252] == 7 || f[0x252] == 8) {
            if (checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) != 0 && f[0x252] == 3 && f[0x25B] == 0) {
                *(f32*)(f + 0x228) = 0.0f;
                *(f32*)(f + 0x230) = 0.0f;
            } else {
                v.x = *(f32*)(f + 0x21C) - *(f32*)f;
                v.z = *(f32*)(f + 0x224) - *(f32*)(f + 8);
                *(f32*)(f + 0x228) = v.x / *(s16*)(f + 0x24C);
                *(f32*)(f + 0x230) = v.z / *(s16*)(f + 0x24C);
                if (f[0x252] == 7 || f[0x252] == 8) {
                    f[0x262] = lbl_3_data_49DC[0x15];
                }
            }
        }
    }
    if (checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) != 0 || f[0x265] != 0) {
        if (f[0x25B] == 0) {
            fn_3_25C40(i);
        }
    } else {
        *(f32*)(f + 0) = *(f32*)(f + 0) + *(f32*)(f + 0x228);
        *(f32*)(f + 4) = *(f32*)(f + 4) + *(f32*)(f + 0x22C);
        *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x230);
        *(f32*)(f + 0x30) = *(f32*)(f + 0x228);
        *(f32*)(f + 0x34) = *(f32*)(f + 0x230);
        d = *(f32*)(f + 0x30) * *(f32*)(f + 0x30) + *(f32*)(f + 0x34) * *(f32*)(f + 0x34);
        SQRT_L(d);
        *(f32*)(f + 0x50) = d;
    }
    hit = fn_3_51798(i, &v.x);
    if (hit == 1) {
        f[0x25B] = 1;
        g_Ball[0x1BF0] = 0;
    }
    if (hit != 0) {
        *(f32*)(f + 0) = *(f32*)(f + 0xD4);
        *(f32*)(f + 8) = *(f32*)(f + 0xD8);
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x30) = 0.0f;
        *(f32*)(f + 0x34) = 0.0f;
    }
    if (*(f32*)(f + 0x50) > 0.0f) {
        *(f32*)(f + 0x38) = *(f32*)(f + 0x30) / *(f32*)(f + 0x50);
        *(f32*)(f + 0x3C) = *(f32*)(f + 0x34) / *(f32*)(f + 0x50);
    } else {
        *(f32*)(f + 0x3C) = 0.0f;
        *(f32*)(f + 0x38) = 0.0f;
    }
}
#endif

// .text:0x00026664 size:0x410 mapped:0x806656F8
void fn_3_26664(int i) {
    int who = i;
    u8* f = g_Fielders + i * 0x268;
    int mode;
    int pct;
    f[0x258] = 0;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    if ((g_d_GameSettings[7] != 2 || *(s8*)(g_Practice + 0x1C2) < 0) && g_Ball[0x1BD8] == 0 && g_Ball[0x1BCC] == 0) {
        if (g_Ball[0x1BD6] < 5) {
            goto go;
        }
    }
    return;
go:
    if (checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 10) != 0) {
        fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 10);
        playSoundEffect(0x1A8);
        return;
    }
    mode = 0;
    if (g_d_GameSettings[7] == 6) {
        mode = 1;
    }
    if (g_Ball[0x1BE5] != 0) {
        if (f[0x259] != 0) {
            pct = lbl_3_data_4714[mode][f[0x1C8]][5];
        } else if (f[0x260] != 0) {
            pct = lbl_3_data_4714[mode][f[0x1C8]][4];
        } else if (f[0x254] == 0) {
            pct = lbl_3_data_4714[mode][f[0x1C8]][3];
        } else {
            pct = lbl_3_data_4714[mode][f[0x1C8]][4];
        }
        if (i == 0) {
            pct *= 2;
        }
        pct *= 10;
        if (g_d_GameSettings[8] == 0 && g_d_GameSettings[0x34] == *(int*)(g_GameLogic + 8) &&
            (*(s8*)(g_d_GameSettings + 0x3F) != 0 || *(s8*)(g_d_GameSettings + 0x4F) != 0)) {
            pct = pct * lbl_3_data_5FC4[6];
        }
        if (RandomInt_Game(1000) < pct) {
            f[0x258] = 3;
        } else {
            f[0x258] = 1;
        }
    } else {
        if (f[0x259] != 0) {
            pct = lbl_3_data_4714[mode][f[0x1C8]][2];
        } else if (f[0x260] != 0) {
            pct = lbl_3_data_4714[mode][f[0x1C8]][1];
        } else if (f[0x254] == 0) {
            pct = lbl_3_data_4714[mode][f[0x1C8]][0];
        } else {
            pct = lbl_3_data_4714[mode][f[0x1C8]][1];
        }
        pct *= 10;
        if (g_d_GameSettings[8] == 0 && g_d_GameSettings[0x34] == *(int*)(g_GameLogic + 8) &&
            (*(s8*)(g_d_GameSettings + 0x3F) != 0 || *(s8*)(g_d_GameSettings + 0x4F) != 0)) {
            pct = pct * lbl_3_data_5FC4[6];
        }
        if (RandomInt_Game(1000) < pct) {
            f[0x258] = 2;
        } else {
            f[0x258] = 0;
        }
    }
    g_Ball[0x1BE5] = 0;
}

// .text:0x00026A74 size:0xBD4 mapped:0x80665B08
// NONMATCHING 88%: the original inlines fn_3_27764 for the already-caught case; we call it (same behaviour); fn_3_59918 is called with its one declared argument (original also zeroes r4)
// nmverify: fn_3_27764 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_3_26A74(int i) {
    u8* f = g_Fielders + i * 0x268;
    u8* r;
    int k;
    int t;
    f32 d;
    f32 spd;
    int stadium;
    int vol;
    int pan;
    u32 vid;
    if (g_Ball[0x1BC9] == 1) {
        fn_3_27764(i);
        return;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 0 || (g_Ball[0x1BD6] == 0 && g_Ball[0x1BD7] == 0 && g_Ball[0x1BD8] == 1)) {
        if (*(s16*)(g_Ball + 0x1B7C) == -1) {
            if (fn_3_B7E10(*(f32*)g_Ball, *(f32*)(g_Ball + 8)) != 0) {
                *(s16*)(g_Ball + 0x1B7C) = 1;
            } else {
                *(s16*)(g_Ball + 0x1B7C) = 0;
            }
        }
        *(s16*)(g_Ball + 0x1B7A) = 3;
        if (g_FieldingLogic[0x108] != 0) {
            g_FieldingLogic[0x108] = 2;
        }
    } else if (*(s16*)(g_Ball + 0x1B7A) == 1) {
        if (g_Ball[0x1BC6] == 0 && fn_3_B7E10(*(f32*)g_Ball, *(f32*)(g_Ball + 8)) != 0) {
            fn_3_A0F0();
        } else {
            *(s16*)(g_Ball + 0x1B7A) = 2;
            if (g_FieldingLogic[0x108] != 0) {
                g_FieldingLogic[0x108] = 2;
            }
        }
        if (*(s16*)(g_Ball + 0x1B7C) == -1) {
            if (*(s16*)(g_Ball + 0x1B7A) == -1) {
                *(s16*)(g_Ball + 0x1B7C) = 1;
            } else {
                *(s16*)(g_Ball + 0x1B7C) = 0;
            }
        }
        if (g_Ball[0x1BC9] == 0 && *(s16*)(g_Ball + 0x1B7A) != -1 && g_FieldingLogic[0x108] == 0 &&
            *(s16*)(g_Ball + 0x1B5E) + 15 > *(s16*)(g_Ball + 0x1B66) && g_FieldingLogic[0x108] == 0 &&
            g_d_GameSettings[7] != 6) {
            fn_3_59918(4);
        }
    }
    if (f[0x252] == 2) {
        g_FieldingLogic[0x11F] = 1;
    } else {
        g_FieldingLogic[0x11F] = 0;
    }
    if (f[0x1D7] == 1) {
        fn_3_5372C(i);
        if (*(s16*)(g_FieldingLogic + *(s16*)(f + 0x18C) * 2 + 0xD0) == i &&
            g_FieldingLogic[*(s16*)(f + 0x18C) + 0x101] == 1) {
            *(s16*)(g_Ball + 0x1B86) = *(s16*)(f + 0x18C);
            for (k = 0, r = g_Runners; k < 4; k++, r += 0x154) {
                if (r[0x123] == 1) {
                    if (*(s16*)(f + 0x18C) == *(s16*)(r + 0xE6) && *(s16*)(r + 0xFA) < 120 &&
                        (r[0x128] != 2 || r[0x124] == *(s16*)(r + 0xE6))) {
                        fn_3_59918(2);
                    }
                } else if (r[0x123] == 3 && *(s16*)(f + 0x18C) == 0 && *(s16*)(r + 0xFA) < 60) {
                    fn_3_59918(2);
                }
            }
        }
    }
    g_FieldingLogic[0x114] = f[0x259];
    if (*(s8*)(g_FieldingLogic + 0x115) < 0) {
        g_FieldingLogic[0x115] = f[0x259];
    }
    if (g_Ball[0x1BD7] == 0) {
        if (*(f32*)(f + 0x118) == *(f32*)f && *(f32*)(f + 0x11C) == *(f32*)(f + 8)) {
            t = 1;
        } else {
            d = DIST2_XZ(*(f32*)(f + 0x118), *(f32*)(f + 0x11C), *(f32*)f, *(f32*)(f + 8));
            SQRT_L(d);
            spd = *(f32*)(f + 0x58);
            if (0.0f == spd) {
                spd = lbl_3_rodata_B60;
            }
            t = (f[0x1D1] >> 1) + (int)(d / spd);
        }
        if (*(s16*)(g_Ball + 0x1B66) - t < lbl_3_data_49DC[0x26]) {
            g_FieldingLogic[0x133] = 1;
        }
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 3 && g_Ball[0x1BD7] == 0) {
        if (f[0x252] == 4 || f[0x252] == 5) {
            g_FieldingLogic[0x133] = 2;
            g_UnkSound_32718[8] = 4;
            g_FieldingLogic[0x134] = i;
            if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(int*)(g_GameLogic + 8) &&
                *(s16*)(g_Ball + 0x1B7A) == 3) {
                fn_3_161588(2, *(s16*)(f + 0x178));
            }
        } else if (f[0x203] != 0) {
            if (*(f32*)(g_Ball + 4) > *(f32*)(f + 0xF4) + *(f32*)(lbl_3_data_4930 + 0x98)) {
                g_FieldingLogic[0x133] = 2;
                g_UnkSound_32718[8] = 4;
                g_FieldingLogic[0x134] = i;
                if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(int*)(g_GameLogic + 8) &&
                    *(s16*)(g_Ball + 0x1B7A) == 3) {
                    fn_3_161588(2, *(s16*)(f + 0x178));
                }
            }
        } else {
            if (g_FieldingLogic[0x133] == 1 && f[0x259] != 0) {
                g_FieldingLogic[0x133] = 2;
                g_UnkSound_32718[8] = 4;
                g_FieldingLogic[0x134] = i;
                if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(int*)(g_GameLogic + 8) &&
                    *(s16*)(g_Ball + 0x1B7A) == 3) {
                    fn_3_161588(2, *(s16*)(f + 0x178));
                }
            }
            if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(int*)(g_GameLogic + 8) &&
                *(s16*)(g_Ball + 0x1B7A) == 3 && f[0x259] == 2) {
                fn_3_161588(3, *(s16*)(f + 0x178));
            }
        }
    }
    if (g_Ball[0x1BE7] == 1 || g_Ball[0x1BE7] == 2) {
        f[0x1EF] = ((s16*)(g_hitShorts + 8))[g_Batter[0xA3]];
    }
    if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(int*)(g_GameLogic + 8) &&
        g_FieldingLogic[0x107] == 0) {
        if (g_Ball[0x1BD8] == 0) {
            fn_3_161588(1, *(s16*)(f + 0x178));
        }
        if (g_Ball[0x1BD8] != 0 && g_Ball[0x1BD7] == 0) {
            fn_3_161588(9, *(s16*)(f + 0x178));
        }
        if (f[0x252] == 6) {
            fn_3_161588(4, *(s16*)(f + 0x178));
        } else if (f[0x252] == 5) {
            fn_3_161588(5, *(s16*)(f + 0x178));
        }
    }
    SetFielderAct(i, 0xA, 0x50);
    *(s16*)(g_FieldingLogic + 0xB0) = -1;
    if (g_Ball[0x1BD7] < 0xFE) {
        g_Ball[0x1BD7] = g_Ball[0x1BD7] + 1;
    } else {
        g_Ball[0x1BD7] = 0xFF;
    }
    if (g_Ball[0x1BD8] < 0xFE) {
        g_Ball[0x1BD8] = g_Ball[0x1BD8] + 1;
    } else {
        g_Ball[0x1BD8] = 0xFF;
    }
    *(f32*)(g_Ball + 0) = *(f32*)(f + 0);
    *(f32*)(g_Ball + 4) = *(f32*)(f + 4);
    *(f32*)(g_Ball + 8) = *(f32*)(f + 8);
    *(f32*)(g_Ball + 0x318) = 0.0f;
    *(f32*)(g_Ball + 0x31C) = 0.0f;
    *(f32*)(g_Ball + 0x320) = 0.0f;
    *(f32*)(g_Ball + 0x324) = 0.0f;
    *(f32*)(g_Ball + 0x328) = 0.0f;
    *(f32*)(g_Ball + 0x32C) = 0.0f;
    g_Ball[0x1BC9] = 1;
    *(s16*)(g_Ball + 0x1B78) = i;
    *(s16*)(g_Ball + 0x1B7E) = i;
    *(s16*)(g_Ball + 0x1B8A) = -1;
    g_Ball[0x1BCA] = 0;
    g_Ball[0x1BE1] = 0;
    *(s16*)(g_Ball + 0x1B6E) = 0;
    g_Ball[0x1BE3] = 0;
    *(f32*)(g_Ball + 0x1A50) = *(f32*)(f + 0);
    *(f32*)(g_Ball + 0x1A54) = *(f32*)(f + 8);
    g_Ball[0x1BD6] = 0;
    g_Ball[0x1BC6] = 1;
    g_Ball[0x1BEB] = 0;
    g_Ball[0x1BF0] = 0;
    g_Ball[0x1BE4] = 0;
    if (*(s8*)(g_Ball + 0x1BDD) < 0) {
        g_Ball[0x1BDD] = g_Ball[0x1BBE];
    }
    if (*(s16*)(g_Ball + 0x1B8E) == -1) {
        *(s16*)(g_Ball + 0x1B8E) = i;
    }
    if (*(s16*)(g_Ball + 0x1B90) == -1) {
        *(s16*)(g_Ball + 0x1B90) = i;
    }
    f[0x252] = 0;
    *(f32*)(f + 0x50) = 0.0f;
    *(s16*)(f + 0x194) = 0;
    f[0x1E9] = 0;
    f[0x1DF] = 0;
    f[0x215] = 0;
    f[0x265] = 0;
    if (f[0x1E8] != 0) {
        f[0x1E8] = 2;
    }
    *(s16*)(g_FieldingLogic + 0xC4) = -1;
    *(s16*)(g_FieldingLogic + 0xCC) = -1;
    *(s16*)(g_FieldingLogic + 0xDE) = -1;
    *(s16*)(g_FieldingLogic + 0xDC) = *(s16*)(g_Ball + 0x1B86);
    *(s16*)(g_FieldingLogic + 0xE2) = -1;
    *(s16*)(g_FieldingLogic + 0xB0) = -1;
    *(s16*)(g_FieldingLogic + 0xB2) = -1;
    *(s16*)(g_FieldingLogic + 0xB4) = -1;
    g_FieldingLogic[0x12C] = 0;
    g_FieldingLogic[0x140] = 0;
    g_FieldingLogic[0x142] = 0;
    g_FieldingLogic[0x109] = 0;
    g_Batter[0xA8] = 0;
    g_Minigame[0x19C6] = f[0x20D];
    if (g_FieldingLogic[0x143] == 1) {
        g_FieldingLogic[0x143] = 2;
    }
    if (g_Ball[0x1BE7] != 0) {
        g_Ball[0x1BE7] = 0;
    }
    if (lbl_800E8558[*(s16*)(f + 0x17A) * 6 + 2] == 0x19) {
        fn_3_16696C();
    }
    fn_3_8FF5C(0x16C, *(f32*)g_Ball, *(f32*)(g_Ball + 4), *(f32*)(g_Ball + 8));
    if (g_d_GameSettings[7] == 6) {
        stadium = g_d_GameSettings[9];
        vol = g_d_GameSettings[7] == 6 ? lbl_3_data_84B8[0x2C] : lbl_3_data_8404[stadium * 0x1E + 0x2C];
        vid = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x16, vol, 0x3F, 0);
        pan = g_d_GameSettings[7] == 6 ? lbl_3_data_84B8[0x2D] : lbl_3_data_8404[stadium * 0x1E + 0x2D];
        sndFXCtrl(vid, 0x5B, pan);
    }
}
#endif

// .text:0x00027648 size:0xF0 mapped:0x806666DC
void fn_3_27648(void) {
    u8* f = g_Fielders;
    int i;
    for (i = 0; i < 9; i++) {
        if (f[0x252] != 0) {
            f[0x25B] = 1;
            g_Ball[0x1BF0] = 0;
        }
        f += 0x268;
    }
}

// .text:0x00027738 size:0x2C mapped:0x806667CC
extern u8 g_Fielders[];
extern s16 lbl_3_data_1C3C[];
extern f32 lbl_3_rodata_B94;
extern f32 lbl_3_rodata_B98;
extern f32 lbl_3_rodata_B60;
void fn_3_1AE44(u8, u16, f32, f32, f32);
extern int fn_3_9FB8C(f32 x, f32 y);
extern int fn_3_9FCA4(s16 a, s16 b);

void fn_3_27738(s32 i) {
    u8* f = g_Fielders + i * 0x268;
    f[0x25B] = 1;
    g_Ball[0x1BF0] = 0;
}

// .text:0x00027764 size:0xFC mapped:0x806667F8
void fn_3_27764(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (g_d_GameSettings[7] != 6 && i != *(s16*)(g_FieldingLogic + 0xB0) && i != -1) {
        f[0x1D3] = 0xC;
        if (*(int*)(lbl_3_data_3C40 + 0x60) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x60);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    f[0x252] = 0;
    *(f32*)(f + 0x50) = lbl_3_rodata_B20;
    *(s16*)(f + 0x194) = 0;
    f[0x1E9] = 0;
    f[0x1DF] = 0;
    f[0x205] = 0;
    f[0x25E] = 0;
    if (f[0x1E8] != 0) {
        f[0x1E8] = 2;
    }
    if (*(s16*)(g_Ball + 0x1B78) >= 0 && g_Ball[0x1BF0] != 0) {
        g_Ball[0x1BF0] = 0;
        *(f32*)(g_Ball + 0) = *(f32*)(g_Ball + 0x1B38);
        *(f32*)(g_Ball + 4) = *(f32*)(g_Ball + 0x1B3C);
        *(f32*)(g_Ball + 8) = *(f32*)(g_Ball + 0x1B40);
    }
}

// .text:0x00027860 size:0x508 mapped:0x806668F4
// NONMATCHING 65%: the original inlines fn_3_27764 in both cancel branches; we call it (same behaviour)
// nmverify: fn_3_27764 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_3_27860(int i) {
    u8* f = g_Fielders + i * 0x268;
    u8* m;
    f32 d;
    *(s16*)(f + 0x24C) = *(s16*)(f + 0x24C) - 1;
    *(s16*)(f + 0x24E) = *(s16*)(f + 0x24E) + 1;
    if (f[0x25B] != 0) {
        if (*(s16*)(f + 0x24C) <= 0) {
            f[0x252] = 0;
        }
    } else if (*(s16*)(g_Ball + 0x1B78) >= 0) {
        fn_3_27764(i);
    } else if (g_Ball[0x1BD1] != 0) {
        fn_3_27764(i);
    } else if (*(s16*)(f + 0x24C) > 0) {
        if (f[0x264] != 0) {
            d = DIST2_XZ(*(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C), *(f32*)f, *(f32*)(f + 8));
            SQRT_L(d);
            if (d < lbl_3_rodata_B64) {
                g_FieldingLogic[0x144] = 1;
            }
        }
    } else {
        (*(u8**)(g_FieldingLogic + 0x70))[0x1A] = 0;
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14) = -1;
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = -1;
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xE) = -1;
        if (g_Ball[0x1BE7] == 1 || g_Ball[0x1BE7] == 2) {
            f[0x258] = 4;
            fn_3_4DC14(i);
        } else if (f[0x258] == 2 || f[0x258] == 3) {
            fn_3_4DC14(i);
            if (g_d_GameSettings[0x11] != 0) {
                m = g_Minigame + f[0x20D];
                if (m[0x18D8] == 0) {
                    fn_3_6C854(*(s8*)(m + 0x18CC), 0);
                }
            } else if (g_GameLogic[*(int*)(g_GameLogic + 8) + 0x13E] == 0) {
                fn_3_6C854(*(int*)(g_GameLogic + 8), 0);
            }
        } else {
            fn_3_26A74(i);
            if (f[0x258] == 0 || f[0x258] == 1) {
                if (g_d_GameSettings[0x11] != 0) {
                    m = g_Minigame + f[0x20D];
                    if (m[0x18D8] == 0) {
                        fn_3_6C854(*(s8*)(m + 0x18CC), 0);
                    }
                } else if (g_GameLogic[*(int*)(g_GameLogic + 8) + 0x13E] == 0) {
                    fn_3_6C854(*(int*)(g_GameLogic + 8), 0);
                }
            }
        }
    }
}
#endif

// .text:0x00027D68 size:0x28C mapped:0x80666DFC
// NONMATCHING 92%: registers only; the loop-invariant height window lo/hi gets f5/f4 instead of f0/f1, shifting every float reg
#if NONMATCHING
int fn_3_27D68(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 h = *(f32*)(f + 0x148);
    f32 hi = lbl_3_rodata_B60 + (*(f32*)(f + 0xF4) + h);
    f32 lo = *(f32*)(f + 0xFC) + h;
    u8* pt = g_Ball + 0x10;
    int k;
    int n;
    f32 d;
    for (k = 1, n = 10; n != 0; pt += 16, k++, n--) {
        if (*(f32*)(pt + 0x360) < *(f32*)(f + 0x70) && *(f32*)(pt + 0x358) > lo && *(f32*)(pt + 0x358) < hi) {
            d = (*(f32*)f - *(f32*)(pt + 0x354)) * (*(f32*)f - *(f32*)(pt + 0x354)) +
                (*(f32*)(f + 8) - *(f32*)(pt + 0x35C)) * (*(f32*)(f + 8) - *(f32*)(pt + 0x35C));
            SQRT_L(d);
            if (d < *(f32*)(f + 0xE8)) {
                goto found;
            }
        }
    }
    return 0;
found:
    if (*(f32*)(g_Ball + k * 16 + 0x370) < *(f32*)(f + 0x70)) {
        k -= 2;
    } else if (*(f32*)(g_Ball + k * 16 + 0x380) < *(f32*)(f + 0x70)) {
        k -= 1;
    }
    if (k < 0) {
        k = 0;
    }
    *(s16*)(f + 0x24C) = k;
    *(s16*)(f + 0x24E) = 0;
    f[0x252] = 5;
    f[0x253] = 0;
    f[0x254] = 0;
    f[0x255] = 0;
    f[0x25B] = 0;
    f[0x259] = 0;
    f[0x25C] = 0;
    f[0x25D] = 0;
    f[0x25E] = 0;
    f[0x25F] = 0;
    f[0x264] = 0;
    f[0x260] = 0;
    if (k < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    g_Ball[0x1BF0] = 0;
    fn_3_1AE44(3, 0, *(f32*)(g_Ball + k * 16 + 0x354), *(f32*)(g_Ball + k * 16 + 0x358),
               *(f32*)(g_Ball + k * 16 + 0x35C));
    return 1;
}
#endif

// .text:0x00027FF4 size:0x230 mapped:0x80667088
// NONMATCHING 97%: f2/f5 swapped for fielder z and the 0x70 scale in the segment setup
#if NONMATCHING
int fn_3_27FF4(int i) {
    u8* f = g_Fielders + i * 0x268;
    VecSrcDst seg;
    CollisionStruct hit;
    f32 x, y, z;
    f32 d;
    if ((0.0f == *(f32*)(f + 0x38) && 0.0f == *(f32*)(f + 0x3C)) || *(s16*)(f + 0x19A) < 0) {
        return 0;
    }
    x = *(f32*)f;
    z = *(f32*)(f + 8);
    y = -*(f32*)(lbl_3_data_4930 + 0x74);
    seg.src.x = x;
    seg.dst.y = y;
    seg.src.y = y;
    seg.src.z = z;
    seg.dst.x = *(f32*)(f + 0x38) * *(f32*)(lbl_3_data_4930 + 0x70) + x;
    seg.dst.z = *(f32*)(f + 0x3C) * *(f32*)(lbl_3_data_4930 + 0x70) + z;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
        return 0;
    }
    f[0x207] = 1;
    *(s16*)(f + 0x1B4) = lbl_3_data_49DC[7];
    *(f32*)(f + 0x128) = hit.position.x;
    *(f32*)(f + 0x12C) = *(f32*)(lbl_3_data_4930 + 0x74);
    *(f32*)(f + 0x130) = hit.position.z;
    d = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    *(f32*)(f + 0x148) = 0.0f;
    SQRT_L(d);
    *(f32*)(f + 0x140) = hit.normal.x / d;
    *(f32*)(f + 0x144) = hit.normal.z / d;
    *(f32*)(f + 0x50) = 0.0f;
    return 1;
}
#endif

// .text:0x00028224 size:0xA84 mapped:0x806672B8
#define K4930(off) (*(f32*)(lbl_3_data_4930 + (off)))
#define BALLPT(n, off) (*(f32*)(g_Ball + (n) * 16 + (off)))
// NONMATCHING 80%: the original fully unrolls the two short search loops (11 and 5 steps) and keeps more in saved regs; logic and calls match
#if NONMATCHING
int fn_3_28224(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 height = *(f32*)(f + 0xF4);
    int k;
    int m;
    int j;
    f32 t0;
    f32 h;
    f32 d;
    f32 dx;
    f32 dz;
    f32 nx;
    f32 nz;
    VecSrcDst seg;
    CollisionStruct hit;
    if ((0.0f == *(f32*)(f + 0x38) && 0.0f == *(f32*)(f + 0x3C)) || *(s16*)(f + 0x19A) < 0) {
        return 0;
    }
    for (k = lbl_3_data_49DC[2] - 1; k < lbl_3_data_49DC[1]; k++) {
        if (BALLPT(k, 0x360) > *(f32*)(g_Ball + 0x19E0) - K4930(0x28)) {
            break;
        }
    }
    if (k < lbl_3_data_49DC[2]) {
        return 0;
    }
    if (BALLPT(k, 0x358) < K4930(0x20) + height) {
        return 0;
    }
    if (k < lbl_3_data_49DC[1] &&
        fn_3_9FCF8(fn_3_9FB8C(BALLPT(k, 0x354) - *(f32*)f, BALLPT(k, 0x35C) - *(f32*)(f + 8)), *(s16*)(f + 0x19A)) <= 0x300) {
        *(f32*)(f + 0x128) = BALLPT(k, 0x354);
        *(f32*)(f + 0x130) = BALLPT(k, 0x35C);
        *(f32*)(f + 0x12C) = K4930(0x14);
        d = DIST2_XZ(*(f32*)f, *(f32*)(f + 8), *(f32*)(f + 0x128), *(f32*)(f + 0x130));
        SQRT_L(d);
        if (!(d > K4930(0x10))) {
            dz = *(f32*)(f + 0x130) - *(f32*)(f + 8);
            dx = *(f32*)(f + 0x128) - *(f32*)f;
            seg.src.x = *(f32*)f;
            seg.src.z = *(f32*)(f + 8);
            seg.dst.y = -K4930(0x14);
            seg.src.y = -K4930(0x14);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            seg.dst.x = (dx / d) * K4930(0x10) + *(f32*)f;
            seg.dst.z = (dz / d) * K4930(0x10) + *(f32*)(f + 8);
            if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
                return 0;
            }
            /* step back to the first frame the ball is still within reach time-wise */
            t0 = BALLPT(k, 0x360) - K4930(0x30);
            for (m = k, j = 0; j < 11; j++, m--) {
                if (t0 < BALLPT(m, 0x360)) {
                    break;
                }
            }
            h = height + K4930(0x24);
            k = m;
            for (j = 0; j < 5; j++) {
                if (k < lbl_3_data_49DC[2]) {
                    break;
                }
                if (BALLPT(k, 0x358) > h && j != 0) {
                    k++;
                    break;
                }
                k--;
            }
            *(s16*)(f + 0x24C) = k;
            *(f32*)(f + 0x134) = BALLPT(k, 0x354);
            *(f32*)(f + 0x138) = BALLPT(k, 0x358) - lbl_3_rodata_B68;
            *(f32*)(f + 0x13C) = BALLPT(k, 0x35C);
            *(f32*)(f + 0x134) = (BALLPT(k, 0x354) / BALLPT(k, 0x360)) * K4930(0x30) + *(f32*)(f + 0x134);
            *(f32*)(f + 0x13C) = (BALLPT(k, 0x35C) / BALLPT(k, 0x360)) * K4930(0x30) + *(f32*)(f + 0x13C);
            *(f32*)(f + 0x140) = game_atan2(*(f32*)(f + 0x128) - *(f32*)f, *(f32*)(f + 0x130) - *(f32*)(f + 8));
            *(f32*)(f + 0x144) = game_atan2(-*(f32*)(f + 0x128), -*(f32*)(f + 0x130));
            *(f32*)(f + 0x148) = 0.0f;
            if (BALLPT(k, 0x358) > K4930(0x24) + *(f32*)(f + 0xF4)) {
                *(f32*)(f + 0x138) = K4930(0x24);
                *(s16*)(f + 0x24C) = k;
                *(s16*)(f + 0x24E) = 0;
                f[0x252] = 4;
                f[0x253] = 0;
                f[0x254] = 0;
                f[0x255] = 0;
                f[0x25B] = 1;
                f[0x259] = 0;
                f[0x25C] = 0;
                f[0x25D] = 0;
                f[0x25E] = 0;
                f[0x25F] = 0;
                f[0x264] = 0;
                f[0x260] = 0;
                if (k < *(s16*)(g_Ball + 0x1B60)) {
                    f[0x264] = 1;
                }
                f[0x259] = 3;
                g_Ball[0x1BF0] = 0;
            } else {
                *(f32*)(f + 0x138) = BALLPT(k, 0x358) - *(f32*)(f + 0xF4);
                *(s16*)(f + 0x24C) = k;
                *(s16*)(f + 0x24E) = 0;
                f[0x252] = 4;
                f[0x253] = 0;
                f[0x254] = 0;
                f[0x255] = 0;
                f[0x25B] = 0;
                f[0x259] = 0;
                f[0x25C] = 0;
                f[0x25D] = 0;
                f[0x25E] = 0;
                f[0x25F] = 0;
                f[0x264] = 0;
                f[0x260] = 0;
                if (k < *(s16*)(g_Ball + 0x1B60)) {
                    f[0x264] = 1;
                }
                f[0x259] = 3;
                g_Ball[0x1BF0] = 0;
            }
            f[0x25C] = lbl_3_data_49DC[3];
            fn_3_1AE44(2, 0, BALLPT(k, 0x354), BALLPT(k, 0x358), BALLPT(k, 0x35C));
            return 1;
        }
    }
    seg.src.x = *(f32*)f;
    seg.src.y = -K4930(0x14);
    seg.src.z = *(f32*)(f + 8);
    seg.dst.x = *(f32*)(f + 0x38) * K4930(0x10) + *(f32*)f;
    seg.dst.y = -K4930(0x14);
    seg.dst.z = *(f32*)(f + 0x3C) * K4930(0x10) + *(f32*)(f + 8);
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
        return 0;
    }
    *(f32*)(f + 0x128) = hit.position.x;
    *(f32*)(f + 0x130) = hit.position.z;
    *(f32*)(f + 0x12C) = K4930(0x14);
    d = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    SQRT_L(d);
    nx = hit.normal.x / d;
    nz = hit.normal.z / d;
    nx *= K4930(0x18);
    nz *= K4930(0x18);
    *(f32*)(f + 0x134) = *(f32*)(f + 0x128) + nx;
    *(f32*)(f + 0x138) = *(f32*)(f + 0x12C) + K4930(0x20);
    *(f32*)(f + 0x13C) = *(f32*)(f + 0x130) + nz;
    *(f32*)(f + 0x140) = game_atan2(*(f32*)(f + 0x128) - *(f32*)f, *(f32*)(f + 0x130) - *(f32*)(f + 8));
    *(f32*)(f + 0x144) = game_atan2(nx, nz);
    *(f32*)(f + 0x148) = 0.0f;
    *(s16*)(f + 0x24C) = k;
    *(s16*)(f + 0x24E) = 0;
    f[0x252] = 4;
    f[0x253] = 0;
    f[0x254] = 0;
    f[0x255] = 0;
    f[0x25B] = 1;
    f[0x259] = 0;
    f[0x25C] = 0;
    f[0x25D] = 0;
    f[0x25E] = 0;
    f[0x25F] = 0;
    f[0x264] = 0;
    f[0x260] = 0;
    if (k < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    f[0x259] = 3;
    g_Ball[0x1BF0] = 0;
    f[0x25C] = lbl_3_data_49DC[3];
    return 1;
}
#endif
#undef K4930
#undef BALLPT

// .text:0x00028CA8 size:0x14BC mapped:0x80667D3C
#define BALLPT(n, off) (*(f32*)(g_Ball + (n) * 16 + (off)))
/* Sets the fielder's catch state (252) and resets the per-catch flags. */
#define SET_CATCH(f, k, st, jump)                                                                                      \
    do {                                                                                                               \
        *(s16*)((f) + 0x24C) = (k);                                                                                    \
        *(s16*)((f) + 0x24E) = 0;                                                                                      \
        (f)[0x252] = (st);                                                                                             \
        (f)[0x253] = 0;                                                                                                \
        (f)[0x254] = 0;                                                                                                \
        (f)[0x255] = 0;                                                                                                \
        (f)[0x25B] = (jump);                                                                                           \
        (f)[0x259] = 0;                                                                                                \
        (f)[0x25C] = 0;                                                                                                \
        (f)[0x25D] = 0;                                                                                                \
        (f)[0x25E] = 0;                                                                                                \
        (f)[0x25F] = 0;                                                                                                \
        (f)[0x264] = 0;                                                                                                \
        (f)[0x260] = 0;                                                                                                \
    } while (0)
// NONMATCHING 80%: register allocation and table addressing (lhax) differ; fn_3_522E0 takes the dx/dz the original leaves in f1/f2 from the preceding distance calc
#if NONMATCHING
int fn_3_28CA8(int i) {
    u8* f = g_Fielders + i * 0x268;
    int who = i;
    int target = -1;
    int stat3;
    int stat8;
    int stat9;
    int k;
    int k0;
    int best;
    int j;
    int dbl;
    s16* tbl;
    f32* lim;
    f32 d;
    f32 dx;
    f32 dz;
    f32 vx;
    f32 vz;
    f32 t;
    f32 ox;
    f32 oz;
    f32 reach;
    f32 sp34[3];
    Vec mid;
    s16 a;
    s16 diff;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    stat3 = checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 3);
    stat8 = checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 8);
    stat9 = checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 9);
    tbl = (s16*)(lbl_3_data_4924 + stat3 * 6);
    lim = (f32*)(lbl_3_data_490C + stat3 * 12);
    if (*(f32*)(g_Ball + 0x19D4) >= lbl_3_rodata_B64 && *(s16*)(g_Ball + 0x1B7A) == 0) {
        /* line drive already in flight: try to snag it at the end of its path */
        if (*(s16*)(g_Ball + 0x1B60) > tbl[0]) {
            goto notCaught;
        }
        target = *(s16*)(g_Ball + 0x1B60) - 1;
        if (fn_3_B7CDC(BALLPT(target, 0x354), BALLPT(target, 0x35C)) != 0) {
            goto notCaught;
        }
        if (target < tbl[1]) {
            goto notCaught;
        }
        dz = *(f32*)(g_Ball + 0x34C) - *(f32*)(f + 8);
        dx = *(f32*)(g_Ball + 0x348) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        fn_3_522E0(i, target, &ox, &oz, &reach, dx, dz);
        if (i == *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14)) {
            reach *= *(f32*)(*(u8**)(g_FieldingLogic + 0x70) + 8);
        }
        if (d - reach <= 0.0f) {
            if (target > lbl_3_data_49DC[0xE]) {
                goto notCaught;
            }
            if (d / target < lbl_3_rodata_B6C) {
                goto notCaught;
            }
            goto dive;
        }
        if (d < reach * lim[0] + *(f32*)(f + 0x104)) {
            goto run;
        }
        if (d >= reach + *(f32*)(f + 0x104) + lim[1] || d - reach <= 0.0f ||
            *(f32*)(g_Ball + 4) < lbl_3_rodata_B64) {
            goto notCaught;
        }
        goto chase;
    }
    if (fn_3_9FCF8(*(s16*)(g_Ball + 0x1B80), *(s16*)(f + 0x180)) > 0x100) {
        goto notCaught;
    }
    if (lbl_3_rodata_B70 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x1A00)) {
        goto notCaught;
    }
    if (*(f32*)(g_Ball + 0x1A14) > lbl_3_rodata_B74) {
        k0 = fn_3_BBBC(sp34, tbl[0] + 15, 2, *(f32*)f, *(f32*)(f + 8));
        if (k0 < 0) {
            goto notCaught;
        }
        best = -1;
        if (k0 < 3) {
            k0 = 3;
        }
        for (k = k0, j = 0; j < 30 && k <= tbl[0]; j += 2, k += 2) {
            if (!(BALLPT(k, 0x358) > *(f32*)(f + 0x108))) {
                if (lbl_3_rodata_B64 + *(f32*)(f + 0x70) < BALLPT(k, 0x360) && *(f32*)(f + 0x7C) < lbl_3_rodata_B78) {
                    break;
                }
                dz = BALLPT(k, 0x35C) - *(f32*)(f + 8);
                dx = BALLPT(k, 0x354) - *(f32*)f;
                d = dx * dx + dz * dz;
                SQRT_L(d);
                fn_3_522E0(i, k, &ox, &oz, &reach, dx, dz);
                if (i == *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14)) {
                    reach *= *(f32*)(*(u8**)(g_FieldingLogic + 0x70) + 8);
                }
                if (d - reach <= 0.0f) {
                    k0 = k;
                    goto searchDive;
                }
                if (d < reach * lim[0] + *(f32*)(f + 0x104)) {
                    target = k;
                    goto run;
                }
                if (d < reach + *(f32*)(f + 0x104) + lim[1] && d - reach > 0.0f && best < 0) {
                    best = k;
                }
            }
        }
        if (best < 0) {
            goto notCaught;
        }
        target = best;
        goto chase;
    }
    for (k = tbl[1]; k < tbl[0]; k += 2) {
        if (BALLPT(k, 0x358) > *(f32*)(f + 0xF4)) {
            continue;
        }
        dz = BALLPT(k, 0x35C) - *(f32*)(f + 8);
        dx = BALLPT(k, 0x354) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        fn_3_522E0(i, k, &ox, &oz, &reach, dx, dz);
        if (i == *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14)) {
            reach *= *(f32*)(*(u8**)(g_FieldingLogic + 0x70) + 8);
        }
        if (d - reach <= 0.0f) {
            k0 = k;
            goto searchDive;
        }
        if (d < reach * lim[0] + *(f32*)(f + 0x104)) {
            target = k;
            goto run;
        }
    }
    goto notCaught;

run:
    /* reachable on foot: run to the catch point */
    if (f[0x1C5] != 0 && BALLPT(target, 0x360) < *(f32*)(f + 0x70)) {
        return 0;
    }
    if (fn_3_B7C2C((Vec*)f, (Vec*)(g_Ball + target * 16 + 0x354)) != 0) {
        goto chase;
    }
    if (stat9 != 0 || checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) != 0) {
        fn_3_26664(i);
        if (f[0x258] == 2) {
            goto chase;
        }
    } else if (fn_3_B7CDC(BALLPT(target, 0x354), BALLPT(target, 0x35C)) != 0) {
        goto chase;
    }
    SET_CATCH(f, target, 3, 0);
    if (target < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    g_Ball[0x1BF0] = 0;
    f[0x259] = 2;
    *(f32*)(f + 0x234) = BALLPT(target, 0x354);
    *(f32*)(f + 0x238) = BALLPT(target, 0x358);
    *(f32*)(f + 0x23C) = BALLPT(target, 0x35C);
    dz = *(f32*)(f + 0x23C) - *(f32*)(f + 8);
    dx = *(f32*)(f + 0x234) - *(f32*)f;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    reach = d - *(f32*)(f + 0x104);
    t = reach / d;
    if (t <= lbl_3_rodata_B7C) {
        t = lbl_3_rodata_B7C;
    }
    *(f32*)(f + 0x21C) = dx * t + *(f32*)f;
    *(f32*)(f + 0x224) = dz * t + *(f32*)(f + 8);
    *(f32*)(f + 0x140) = game_atan2(dx, dz);
    if (stat3 != 0) {
        fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 3);
        playSoundEffect(0x1A8);
    } else if (stat8 != 0) {
        fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 8);
        playSoundEffect(0x1A8);
    } else if (stat9 != 0) {
        f[0x265] = 1;
        fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 8);
        playSoundEffect(0x1A8);
    }
    dbl = 0;
    if (checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) != 0) {
        dbl = 1;
        playSoundEffect(0x1A8);
    }
    if (target < *(s16*)(g_Ball + 0x1B60) && g_Ball[0x1BD6] == 0) {
        if (stat8 != 0 || stat9 != 0 || dbl != 0) {
            mid.x = *(f32*)(f + 0x21C) + *(f32*)(f + 0x234);
            mid.y = *(f32*)(f + 0x220) + *(f32*)(f + 0x238);
            mid.z = *(f32*)(f + 0x224) + *(f32*)(f + 0x23C);
            mid.x = lbl_3_rodata_B80 * mid.x;
            mid.y = lbl_3_rodata_B80 * mid.y;
            mid.z = lbl_3_rodata_B80 * mid.z;
            fn_3_1AE44(1, target - 25, mid.x, mid.y, mid.z);
        } else {
            fn_3_1AE44(0, target - 25, *(f32*)(f + 0x234), *(f32*)(f + 0x238), *(f32*)(f + 0x23C));
        }
    }
    return 1;

notCaught:
    if (*(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14) != i) {
        return 0;
    }
chase:
    /* can't make the catch cleanly: head for the ball (or keep running) */
    if (f[0x1C5] != 0 && (*(u8**)(g_FieldingLogic + 0x8C))[3] != 0) {
        return 0;
    }
    if (target <= 0) {
        vz = *(f32*)(f + 0x3C);
        vx = *(f32*)(f + 0x38);
        d = vx * vx + vz * vz;
        SQRT_L(d);
        if (d <= 0.0f) {
            return 0;
        }
        SET_CATCH(f, tbl[2], 3, 1);
        if (tbl[2] < *(s16*)(g_Ball + 0x1B60)) {
            f[0x264] = 1;
        }
        f[0x259] = 2;
        target = tbl[2];
        g_Ball[0x1BF0] = 0;
    } else {
        if (target < tbl[2]) {
            target = tbl[2];
        }
        SET_CATCH(f, target, 3, 1);
        if (target < *(s16*)(g_Ball + 0x1B60)) {
            f[0x264] = 1;
        }
        f[0x259] = 2;
        g_Ball[0x1BF0] = 0;
        vz = BALLPT(target, 0x35C) - *(f32*)(f + 8);
        vx = BALLPT(target, 0x354) - *(f32*)f;
        d = vx * vx + vz * vz;
        SQRT_L(d);
    }
    vx = vx / d;
    vz = vz / d;
    fn_3_522E0(i, target, &ox, &oz, &reach, vx, vz);
    *(f32*)(f + 0x21C) = vx * reach + *(f32*)f;
    *(f32*)(f + 0x224) = vz * reach + *(f32*)(f + 8);
    *(f32*)(f + 0x140) = game_atan2(vx, vz);
    if (stat9 != 0) {
        f[0x265] = 1;
    }
    return 1;

searchDive:
    /* the ball passes right by: look back along the path for a diving catch */
    if (k0 > lbl_3_data_49DC[0xE]) {
        return 0;
    }
    for (target = k0; target > lbl_3_data_49DC[0xF]; target -= 2) {
        if (fn_3_B7CDC(BALLPT(target, 0x354), BALLPT(target, 0x35C)) != 0) {
            continue;
        }
        if (BALLPT(target, 0x358) > *(f32*)(f + 0xF4)) {
            continue;
        }
        dz = BALLPT(target, 0x35C) - *(f32*)(f + 8);
        dx = BALLPT(target, 0x354) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        fn_3_522E0(i, target, &ox, &oz, &reach, dx, dz);
        if (i == *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14)) {
            reach *= *(f32*)(*(u8**)(g_FieldingLogic + 0x70) + 8);
        }
        if (d / target < lbl_3_rodata_B6C) {
            continue;
        }
        goto dive;
    }
    return 0;

dive:
    SET_CATCH(f, target, 7, 0);
    f[0x260] = 1;
    if (target < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    g_Ball[0x1BF0] = 0;
    *(f32*)(f + 0x234) = BALLPT(target, 0x354);
    *(f32*)(f + 0x238) = BALLPT(target, 0x358);
    *(f32*)(f + 0x23C) = BALLPT(target, 0x35C);
    dz = *(f32*)(f + 0x23C) - *(f32*)(f + 8);
    dx = *(f32*)(f + 0x234) - *(f32*)f;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    reach = d - lbl_3_data_47D0[f[0x1CA]].e;
    t = reach / d;
    *(f32*)(f + 0x21C) = dx * t + *(f32*)f;
    *(f32*)(f + 0x224) = dz * t + *(f32*)(f + 8);
    f[0x261] = 0;
    a = fn_3_9FB8C(*(f32*)g_Ball - *(f32*)f, *(f32*)(g_Ball + 8) - *(f32*)(f + 8));
    diff = fn_3_9FCA4(a, fn_3_9FB8C(*(f32*)(f + 0x21C) - *(f32*)f, *(f32*)(f + 0x224) - *(f32*)(f + 8)));
    if (diff < -0x500 || diff > 0x500) {
        f[0x261] = 3;
    } else if (diff < -0x200) {
        f[0x261] = 1;
    } else if (diff > 0x200) {
        f[0x261] = 2;
    }
    return 1;
}
#endif
#undef SET_CATCH
#undef BALLPT

// .text:0x0002A164 size:0x124 mapped:0x806691F8
extern int fn_3_B7CDC(f32, f32);
int fn_3_2A164(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(f32*)(f + 0x74) > lbl_3_data_47D0[f[0x1CA]].c) {
        return 0;
    }
    if (*(f32*)(g_Ball + 4) < *(f32*)(f + 0x15C)) {
        return 0;
    }
    if (*(f32*)(g_Ball + 4) > *(f32*)(f + 0x15C) + *(f32*)(f + 0xF4)) {
        return 0;
    }
    if (fn_3_B7CDC(*(f32*)(g_Ball + 0), *(f32*)(g_Ball + 8)) != 0) {
        return 0;
    }
    *(s16*)(f + 0x24C) = 1;
    *(s16*)(f + 0x24E) = 0;
    f[0x252] = 6;
    f[0x253] = 0;
    f[0x254] = 0;
    f[0x255] = 0;
    f[0x25B] = 0;
    f[0x259] = 0;
    f[0x25C] = 0;
    f[0x25D] = 0;
    f[0x25E] = 0;
    f[0x25F] = 0;
    f[0x264] = 0;
    f[0x260] = 0;
    if (*(s16*)(g_Ball + 0x1B60) > 1) {
        f[0x264] = 1;
    }
    g_Ball[0x1BF0] = 0;
    return 1;
}

// .text:0x0002A288 size:0x414 mapped:0x8066931C
// NONMATCHING 50%: the original inlines fn_3_27FF4 for the type-1 wall check; we call it (same behaviour)
// nmverify: fn_3_27FF4 inlined on one side (calls match once expanded)
#if NONMATCHING
int fn_3_2A288(int i) {
    int who = i;
    u8* f = g_Fielders + i * 0x268;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    } else if (i != *(s16*)(g_FieldingLogic + 0xB0)) {
        return 0;
    }
    if (f[0x1C5] != 0 && (*(u8**)(g_FieldingLogic + 0x8C))[4] == 0) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == -1) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B66) < f[0x1D2] + 5) {
        return 0;
    }
    if (f[0x1C5] == 0) {
        if (f[0x1CB] == 2) {
            if (fn_3_28224(i) != 0) {
                (*(u8**)(g_FieldingLogic + 0x8C))[2] = 0;
                fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 1);
                return 1;
            }
        } else if (f[0x1CB] == 1) {
            if (fn_3_27FF4(i) != 0) {
                (*(u8**)(g_FieldingLogic + 0x8C))[2] = 0;
                return 1;
            }
        } else if (f[0x1CB] == 3) {
            if (fn_3_30214(i) != 0) {
                (*(u8**)(g_FieldingLogic + 0x8C))[2] = 0;
                fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 2);
                return 1;
            }
        }
    }
    if (fn_3_28CA8(i) != 0) {
        (*(u8**)(g_FieldingLogic + 0x8C))[2] = 0;
        return 1;
    }
    return 0;
}
#endif

// .text:0x0002A69C size:0x63C mapped:0x80669730
// NONMATCHING 80%: register allocation (original keeps the base-table offset and radius-table pointer in saved regs) and lfsx/lfsu addressing; tail is fn_3_2B5C0's body inlined
#if NONMATCHING
int fn_3_2A69C(int i) {
    s16 base = *(s16*)(g_FieldingLogic + 0xC4);
    u8* f = g_Fielders + i * 0x268;
    f32* bpos;
    f32 lim;
    f32 r;
    f32 dx;
    f32 dz;
    f32 d;
    f32 t;
    s16 a;
    s16 diff;
    if (base < 0 || base > 3) {
        return 0;
    }
    if (i != *(s16*)(g_Ball + 0x1B8A)) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B6C) <= 3) {
        return 0;
    }
    if (*(s16*)(f + 0x1A8) != 0) {
        return 0;
    }
    if (f[0x252] == 2) {
        return 0;
    }
    bpos = (f32*)(lbl_3_data_4444 + base * 8);
    if (!(fn_3_9CE0(bpos[0], bpos[1]) < *(f32*)(f + 0xE8))) {
        return 0;
    }
    if (*(s8*)(f + 0x1F5) == base) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B62) > lbl_3_data_49DC[0x13]) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B62) < lbl_3_data_49DC[0x14]) {
        return 0;
    }
    lim = lbl_3_rodata_B84 * *(f32*)(f + 0x58) * *(s16*)(g_Ball + 0x1B62);
    r = ((f32*)(f + 0xA8))[base] - lbl_3_data_47D0[f[0x1CA]].d;
    if (r - lim > lbl_3_rodata_B78) {
        return 0;
    }
    if (r < lim) {
        *(s16*)(f + 0x24C) = *(s16*)(g_Ball + 0x1B62);
        *(s16*)(f + 0x24E) = 0;
        f[0x252] = 8;
        f[0x253] = 0;
        f[0x254] = 0;
        f[0x255] = 0;
        f[0x25B] = 0;
        f[0x259] = 0;
        f[0x25C] = 0;
        f[0x25D] = 0;
        f[0x25E] = 0;
        f[0x25F] = 0;
        f[0x264] = 0;
        f[0x260] = 0;
        if (*(s16*)(g_Ball + 0x1B62) < *(s16*)(g_Ball + 0x1B60)) {
            f[0x264] = 1;
        }
        g_Ball[0x1BF0] = 0;
        *(f32*)(f + 0x234) = *(f32*)(g_Ball + *(s16*)(g_Ball + 0x1B62) * 16 + 0x354);
        *(f32*)(f + 0x238) = *(f32*)(g_Ball + *(s16*)(g_Ball + 0x1B62) * 16 + 0x358);
        *(f32*)(f + 0x23C) = *(f32*)(g_Ball + *(s16*)(g_Ball + 0x1B62) * 16 + 0x35C);
        dz = *(f32*)(f + 0x23C) - *(f32*)(f + 8);
        dx = *(f32*)(f + 0x234) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        r = d - lbl_3_data_47D0[f[0x1CA]].d;
        if (r / *(s16*)(g_Ball + 0x1B62) < lbl_3_rodata_B6C) {
            *(f32*)(f + 0x21C) = *(f32*)(f + 0x234);
            *(f32*)(f + 0x224) = *(f32*)(f + 0x23C);
        } else {
            t = r / d;
            *(f32*)(f + 0x21C) = dx * t + *(f32*)f;
            *(f32*)(f + 0x224) = dz * t + *(f32*)(f + 8);
        }
    } else {
        *(s16*)(f + 0x24C) = *(s16*)(g_Ball + 0x1B62);
        *(s16*)(f + 0x24E) = 0;
        f[0x252] = 8;
        f[0x253] = 0;
        f[0x254] = 0;
        f[0x255] = 0;
        f[0x25B] = 1;
        f[0x259] = 0;
        f[0x25C] = 0;
        f[0x25D] = 0;
        f[0x25E] = 0;
        f[0x25F] = 0;
        f[0x264] = 0;
        f[0x260] = 0;
        if (*(s16*)(g_Ball + 0x1B62) < *(s16*)(g_Ball + 0x1B60)) {
            f[0x264] = 1;
        }
        dz = bpos[1] - *(f32*)(f + 8);
        dx = bpos[0] - *(f32*)f;
        g_Ball[0x1BF0] = 0;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x21C) = lbl_3_rodata_B88 * (*(f32*)(f + 0x58) * (dx / d)) * *(s16*)(g_Ball + 0x1B62) + *(f32*)f;
        *(f32*)(f + 0x224) = lbl_3_rodata_B88 * (*(f32*)(f + 0x58) * (dz / d)) * *(s16*)(g_Ball + 0x1B62) + *(f32*)(f + 8);
    }
    f[0x261] = 0;
    a = fn_3_9FB8C(*(f32*)g_Ball - *(f32*)f, *(f32*)(g_Ball + 8) - *(f32*)(f + 8));
    diff = fn_3_9FCA4(a, fn_3_9FB8C(*(f32*)(f + 0x21C) - *(f32*)f, *(f32*)(f + 0x224) - *(f32*)(f + 8)));
    if (diff < -0x500 || diff > 0x500) {
        f[0x261] = 3;
    } else if (diff < -0x200) {
        f[0x261] = 1;
    } else if (diff > 0x200) {
        f[0x261] = 2;
    }
    return 1;
}
#endif

// .text:0x0002ACD8 size:0x90 mapped:0x80669D6C
int fn_3_2ACD8(int i, int j) {
    u8* f = g_Fielders + i * 0x268;
    if (j < 1) {
        return 0;
    }
    if (fn_3_2BB04(i) != 0) {
        return 1;
    }
    *(f32*)(f + 0x14) = *(f32*)(g_Ball + j * 16 + 0x354);
    *(f32*)(f + 0x1C) = *(f32*)(g_Ball + j * 16 + 0x35C);
    f[0x216] = 1;
    return 0;
}

// .text:0x0002AD68 size:0x858 mapped:0x80669DFC
// NONMATCHING 85%: the original inlines fn_3_2ACD8 for the short-fly case; we call it (same behaviour); loop/regalloc details differ
// nmverify: fn_3_2ACD8 inlined on one side (calls match once expanded)
#if NONMATCHING
int fn_3_2AD68(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 hmax = lbl_3_rodata_B84 * *(f32*)(f + 0xF4);
    s16 n = *(s16*)(g_Ball + 0x1B62);
    int k;
    int cnt;
    u8* pt;
    f32 d;
    f32 dx;
    f32 dz;
    s16 ang;
    s16 diff;
    Vec a;
    Vec b;
    Vec c;
    Vec out;
    if (*(s16*)(g_FieldingLogic + 0xC4) < 0) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B6C) <= 3) {
        return 0;
    }
    if (*(s16*)(f + 0x1A8) != 0) {
        return 0;
    }
    if (f[0x252] == 2) {
        return 0;
    }
    if (g_FieldingLogic[i + 0xF8] == 0xF) {
        if (g_FieldingLogic[0x13C] == 0) {
            return 0;
        }
        if (*(f32*)(f + 0x68) > *(f32*)(f + 0xE8)) {
            return 0;
        }
        for (k = lbl_3_data_49DC[0x17], pt = g_Ball + k * 16; k <= lbl_3_data_49DC[0x16]; k++, pt += 16) {
            if (!(*(f32*)(pt + 0x358) > *(f32*)(f + 0xF4))) {
                d = DIST2_XZ(*(f32*)(pt + 0x354), *(f32*)(pt + 0x35C), *(f32*)f, *(f32*)(f + 8));
                SQRT_L(d);
                if (d < *(f32*)(f + 0xE8)) {
                    break;
                }
            }
        }
        if (k > lbl_3_data_49DC[0x16]) {
            return 0;
        }
        goto hit;
    }
    if (i != *(s16*)(g_Ball + 0x1B8A)) {
        return 0;
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) <= 3) {
        f32* bpos = (f32*)(lbl_3_data_4444 + *(s16*)(g_FieldingLogic + 0xC4) * 8);
        if (fn_3_9CE0(bpos[0], bpos[1]) < *(f32*)(f + 0xE8)) {
            k = n - 1;
            if (k <= 2) {
                return 0;
            }
            if (k > lbl_3_data_49DC[0x18]) {
                return 0;
            }
            if (*(s8*)(f + 0x1F5) != *(s16*)(g_FieldingLogic + 0xC4) && k > lbl_3_data_49DC[0x1A]) {
                return 0;
            }
            for (cnt = 10, pt = g_Ball + k * 16; cnt != 0; cnt--, k--, pt -= 16) {
                if (*(f32*)(pt + 0x358) > hmax) {
                    k++;
                    break;
                }
                d = DIST2_XZ(*(f32*)(pt + 0x354), *(f32*)(pt + 0x35C), *(f32*)f, *(f32*)(f + 8));
                SQRT_L(d);
                if (d > lbl_3_data_4794[f[0x1C9]]) {
                    k++;
                    break;
                }
            }
            goto hit;
        }
        if (*(s16*)(g_Ball + 0x1B6C) <= 20) {
            return 0;
        }
        return fn_3_2ACD8(i, n - 2);
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) == 5 || *(s16*)(g_FieldingLogic + 0xC4) == 6) {
        for (k = lbl_3_data_49DC[0x17], pt = g_Ball + k * 16; k <= lbl_3_data_49DC[0x16]; k++, pt += 16) {
            if (!(*(f32*)(pt + 0x358) > *(f32*)(f + 0xF4))) {
                d = DIST2_XZ(*(f32*)(pt + 0x354), *(f32*)(pt + 0x35C), *(f32*)f, *(f32*)(f + 8));
                SQRT_L(d);
                if (d < *(f32*)(f + 0xE8)) {
                    break;
                }
            }
        }
        if (k > lbl_3_data_49DC[0x16]) {
            return 0;
        }
        goto hit;
    }
    return 0;
hit:
    *(s16*)(f + 0x24C) = k;
    *(s16*)(f + 0x24E) = 0;
    f[0x252] = 2;
    f[0x253] = 0;
    f[0x254] = 0;
    f[0x255] = 1;
    f[0x25B] = 0;
    f[0x259] = 0;
    f[0x25C] = 0;
    f[0x25D] = 0;
    f[0x25E] = 0;
    f[0x25F] = 0;
    f[0x264] = 0;
    f[0x260] = 0;
    if (k < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    g_Ball[0x1BF0] = 0;
    if (*(f32*)(g_Ball + k * 16 + 0x358) < *(f32*)(f + 0xFC)) {
        f[0x253] = 0;
    } else if (*(f32*)(g_Ball + k * 16 + 0x358) < *(f32*)(f + 0xF8)) {
        f[0x253] = 1;
    } else {
        f[0x253] = 2;
    }
    pt = g_Ball + k * 16;
    a.x = *(f32*)f;
    a.y = *(f32*)(f + 4);
    a.z = *(f32*)(f + 8);
    b.x = 0.0f;
    b.y = 0.0f;
    b.z = 0.0f;
    c.x = *(f32*)(pt + 0x354);
    c.z = *(f32*)(pt + 0x35C);
    c.y = 0.0f;
    if (fn_3_9EFD0((struct _VecXYZ*)&a, (struct _VecXYZ*)&b, (struct _VecXYZ*)&c, (struct _VecXYZ*)&out) >
        *(f32*)(f + 0xF0)) {
        dx = *(f32*)(pt + 0x354) - *(f32*)f;
        dz = *(f32*)(pt + 0x35C) - *(f32*)(f + 8);
        ang = fn_3_9FE6C_normalizeAngle(*(s16*)(g_Ball + 0x1B82) + 0x800);
        diff = fn_3_9FCA4(ang, fn_3_9FB8C(dx, dz));
        if (diff > 0) {
            f[0x254] = 2;
        } else {
            f[0x254] = 1;
        }
    }
    *(f32*)(f + 0x240) = *(f32*)(pt + 0x354) - *(f32*)g_Ball;
    *(f32*)(f + 0x244) = *(f32*)(pt + 0x35C) - *(f32*)(g_Ball + 8);
    return 1;
}
#endif

// .text:0x0002B5C0 size:0xD4 mapped:0x8066A654
void fn_3_2B5C0(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 a;
    s16 d;
    f[0x261] = 0;
    a = fn_3_9FB8C(*(f32*)g_Ball - *(f32*)f, *(f32*)(g_Ball + 8) - *(f32*)(f + 8));
    d = fn_3_9FCA4(a, fn_3_9FB8C(*(f32*)(f + 0x21C) - *(f32*)f, *(f32*)(f + 0x224) - *(f32*)(f + 8)));
    if (d < -0x500 || d > 0x500) {
        f[0x261] = 3;
    } else if (d < -0x200) {
        f[0x261] = 1;
    } else if (d > 0x200) {
        f[0x261] = 2;
    }
}

// .text:0x0002B694 size:0x470 mapped:0x8066A728
// NONMATCHING 90%: register allocation only (saved GPR/FPR assignment differs); the tail writes fn_3_2B5C0's body out as the original inlines it
#if NONMATCHING
int fn_3_2B694(int i) {
    u8* f = g_Fielders + i * 0x268;
    u8* pt;
    int k;
    f32 d;
    f32 spd;
    f32 dx;
    f32 dz;
    f32 r;
    f32 t;
    s16 a;
    s16 diff;
    if (0.0f == *(f32*)(f + 0x50) || *(s16*)(f + 0x19A) < 0) {
        return 0;
    }
    if (g_Ball[0x1BCC] != 0) {
        return 0;
    }
    if (g_Ball[0x1BD8] != 0) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 1) {
        if (fn_3_9FCF8(*(s16*)(f + 0x180), *(s16*)(f + 0x19A)) > 0x500) {
            return 0;
        }
    } else if (*(s16*)(g_Ball + 0x1B7A) == 0 && fn_3_9FCF8(*(s16*)(f + 0x180), *(s16*)(f + 0x19A)) > 0x500 &&
               lbl_3_rodata_B60 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x350)) {
        return 0;
    }
    spd = *(f32*)(f + 0x58);
    if (i == *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14)) {
        spd *= *(f32*)(*(u8**)(g_FieldingLogic + 0x70) + 8);
    }
    for (k = lbl_3_data_49DC[0x11], pt = g_Ball + k * 16; k <= lbl_3_data_49DC[0x10]; pt += 16, k++) {
        if (*(f32*)(pt + 0x358) > *(f32*)(f + 0xF8)) {
            continue;
        }
        dx = *(f32*)(pt + 0x354) - *(f32*)f;
        dz = *(f32*)(pt + 0x35C) - *(f32*)(f + 8);
        if (fn_3_9FCF8(fn_3_9FB8C(dx, dz), *(s16*)(f + 0x19A)) > lbl_3_data_49DC[0x12]) {
            continue;
        }
        d = dx * dx + dz * dz;
        SQRT_L(d);
        r = d - lbl_3_data_4794[f[0x1C9]];
        if ((int)(r / (spd * *(f32*)(lbl_3_data_4930 + 0x78))) + 1 > k) {
            continue;
        }
        if (r < *(f32*)(f + 0xE8)) {
            continue;
        }
        if (fn_3_B7CDC(*(f32*)(pt + 0x354), *(f32*)(pt + 0x35C)) != 0) {
            continue;
        }
        *(s16*)(f + 0x24C) = k;
        *(s16*)(f + 0x24E) = 0;
        f[0x252] = 7;
        f[0x253] = 0;
        f[0x254] = 0;
        f[0x255] = 0;
        f[0x25B] = 0;
        f[0x259] = 0;
        f[0x25C] = 0;
        f[0x25D] = 0;
        f[0x25E] = 0;
        f[0x25F] = 0;
        f[0x264] = 0;
        f[0x260] = 0;
        f[0x260] = 1;
        if (k < *(s16*)(g_Ball + 0x1B60)) {
            f[0x264] = 1;
        }
        t = r / d;
        g_Ball[0x1BF0] = 0;
        *(f32*)(f + 0x21C) = dx * t + *(f32*)f;
        *(f32*)(f + 0x224) = dz * t + *(f32*)(f + 8);
        f[0x261] = 0;
        a = fn_3_9FB8C(*(f32*)g_Ball - *(f32*)f, *(f32*)(g_Ball + 8) - *(f32*)(f + 8));
        diff = fn_3_9FCA4(a, fn_3_9FB8C(*(f32*)(f + 0x21C) - *(f32*)f, *(f32*)(f + 0x224) - *(f32*)(f + 8)));
        if (diff < -0x500 || diff > 0x500) {
            f[0x261] = 3;
        } else if (diff < -0x200) {
            f[0x261] = 1;
        } else if (diff > 0x200) {
            f[0x261] = 2;
        }
        return 1;
    }
    return 0;
}
#endif

// .text:0x0002BB04 size:0x734 mapped:0x8066AB98
// NONMATCHING 85%: register allocation and int->float conversion scheduling in the trajectory loops
#if NONMATCHING
int fn_3_2BB04(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 vz;
    f32 vx;
    f32 d;
    f32 dx;
    f32 dz;
    int dive = 1;
    int aimed = 0;
    int k;
    s16 diff;
    s16 ang;
    u8* pt;
    Vec a;
    Vec b;
    Vec c;
    Vec out;
    vz = *(f32*)(f + 0x44);
    vx = *(f32*)(f + 0x40);
    d = vx * vx + vz * vz;
    SQRT_L(d);
    if (0.0f != d) {
        vx = lbl_3_rodata_B24 * (vx / d);
        vz = lbl_3_rodata_B24 * (vz / d);
    }
    if (g_Ball[0x1BC9] == 3 || g_Ball[0x1BCC] != 0 || i == 1) {
        dive = 0;
    }
    if (g_Ball[0x1BD6] != 0) {
        if (g_Ball[0x1BC3] == 2) {
            if (*(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_B24) {
                dive = 0;
            }
        } else if (*(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_B7C) {
            dive = 0;
        }
    }
    if (dive != 0) {
        for (k = 1, pt = g_Ball + 0x10; k < lbl_3_data_49DC[0xB]; k++, pt += 0x10) {
            if (*(f32*)(pt + 0x358) < *(f32*)(f + 0xF4)) {
                dz = *(f32*)(pt + 0x35C) - (k * vz + *(f32*)(f + 8));
                dx = *(f32*)(pt + 0x354) - (k * vx + *(f32*)f);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                if (d < *(f32*)(f + 0xE8)) {
                    ang = fn_3_9FE6C_normalizeAngle(*(s16*)(g_Ball + 0x1B82) + 0x800);
                    diff = fn_3_9FCA4(ang, fn_3_9FB8C(dx, dz));
                    aimed = 1;
                    if (diff <= 0x400 && diff >= -0x400) {
                        goto hit;
                    }
                }
            }
        }
        return 0;
    }
    for (k = 1, pt = g_Ball + 0x10; k < lbl_3_data_49DC[0xB]; k++, pt += 0x10) {
        if (*(f32*)(pt + 0x358) < *(f32*)(f + 0xF4)) {
            dz = *(f32*)(pt + 0x35C) - (k * vz + *(f32*)(f + 8));
            dx = *(f32*)(pt + 0x354) - (k * vx + *(f32*)f);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (d < *(f32*)(f + 0xEC)) {
                goto hit;
            }
        }
    }
    return 0;
hit:
    *(s16*)(f + 0x24C) = k;
    *(s16*)(f + 0x24E) = 0;
    f[0x252] = 1;
    f[0x253] = 0;
    f[0x254] = 0;
    f[0x255] = dive;
    f[0x25B] = 0;
    f[0x259] = 0;
    f[0x25C] = 0;
    f[0x25D] = 0;
    f[0x25E] = 0;
    f[0x25F] = 0;
    f[0x264] = 0;
    f[0x260] = 0;
    if (k < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    g_Ball[0x1BF0] = 0;
    if (*(f32*)(g_Ball + k * 16 + 0x358) < *(f32*)(f + 0xFC)) {
        f[0x253] = 0;
    } else if (*(f32*)(g_Ball + k * 16 + 0x358) < *(f32*)(f + 0xF8)) {
        f[0x253] = 1;
    } else {
        f[0x253] = 2;
    }
    if (dive != 0 && aimed != 0) {
        a.x = *(f32*)f;
        a.y = *(f32*)(f + 4);
        a.z = *(f32*)(f + 8);
        b.x = 0.0f;
        b.y = 0.0f;
        b.z = 0.0f;
        c.x = *(f32*)(g_Ball + k * 16 + 0x354);
        c.z = *(f32*)(g_Ball + k * 16 + 0x35C);
        c.y = 0.0f;
        if (fn_3_9EFD0((struct _VecXYZ*)&a, (struct _VecXYZ*)&b, (struct _VecXYZ*)&c, (struct _VecXYZ*)&out) >
            *(f32*)(f + 0xF0)) {
            if (diff > 0) {
                f[0x254] = 2;
            } else {
                f[0x254] = 1;
            }
        }
    }
    dx = *(f32*)(g_Ball + k * 16 + 0x354) - *(f32*)g_Ball;
    dz = *(f32*)(g_Ball + k * 16 + 0x35C) - *(f32*)(g_Ball + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x240) = *(f32*)g_Ball;
        *(f32*)(f + 0x244) = *(f32*)(g_Ball + 8);
    } else {
        *(f32*)(f + 0x240) = dx;
        *(f32*)(f + 0x244) = dz;
    }
    return 1;
}
#endif

// .text:0x0002C238 size:0xB8 mapped:0x8066B2CC
void fn_3_2C238(int i, int a, int b, int c, int d) {
    u8* f = g_Fielders + i * 0x268;
    *(s16*)(f + 0x24C) = b;
    *(s16*)(f + 0x24E) = 0;
    f[0x252] = a;
    f[0x253] = 0;
    f[0x254] = 0;
    f[0x255] = d;
    f[0x25B] = c;
    f[0x259] = 0;
    f[0x25C] = 0;
    f[0x25D] = 0;
    f[0x25E] = 0;
    f[0x25F] = 0;
    f[0x264] = 0;
    f[0x260] = 0;
    if (a == 7) {
        f[0x260] = 1;
    }
    if (b < *(s16*)(g_Ball + 0x1B60)) {
        f[0x264] = 1;
    }
    switch (a) {
    case 3:
        f[0x259] = 2;
        break;
    case 4:
        f[0x259] = 3;
        break;
    }
    g_Ball[0x1BF0] = 0;
}

// .text:0x0002C2F0 size:0x3A8 mapped:0x8066B384
void fn_3_2C2F0(int i) {
    u8* f = g_Fielders + i * 0x268;
    int k;
    int idx;
    f32 half;
    f32 d;
    if (i != *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14) && g_Ball[0x1BEB] == 0 && *(s16*)(g_Ball + 0x1B7A) == 0) {
        half = lbl_3_rodata_B80 * *(f32*)(f + 0xF4);
        for (k = 0; k < 20; k++) {
            idx = *(s16*)(g_Ball + 0x1B60) - k;
            if (half < *(f32*)(g_Ball + idx * 16 + 0x358)) {
                k--;
                break;
            }
        }
        if (k < 20) {
            d = DIST2_XZ(*(f32*)(g_Ball + idx * 16 + 0x354), *(f32*)(g_Ball + idx * 16 + 0x35C), *(f32*)f,
                         *(f32*)(f + 8));
            SQRT_L(d);
            *(f32*)(f + 0x248) = d;
            if (*(f32*)(f + 0x248) < lbl_3_rodata_B64) {
                if (*(s16*)(f + 0x250) == 0 && *(s16*)(g_Ball + 0x1B60) < 45) {
                    if (*(s16*)(g_Ball + 0x1B60) > 30) {
                        if (f[0x257] != 0) {
                            if (*(f32*)(f + 0x248) < lbl_3_rodata_B8C) {
                                f[0x256] = 1;
                            }
                        } else if (*(f32*)(f + 0x248) < lbl_3_rodata_B78) {
                            f[0x256] = 1;
                        }
                    }
                } else {
                    f[0x256] = 1;
                }
                if (*(f32*)(f + 0x248) < *(f32*)(f + 0xE8)) {
                    g_FieldingLogic[0x144] = 1;
                }
            }
        }
    }
}

// .text:0x0002C698 size:0x548 mapped:0x8066B72C
// NONMATCHING 85%: the original inlines fn_3_2A164 for the jumping-catch check; we call it (same behaviour); some branch layout/regalloc differs
// nmverify: fn_3_2A164 inlined on one side (calls match once expanded)
#if NONMATCHING
void fn_3_2C698(int i) {
    int who = i;
    u8* f = g_Fielders + i * 0x268;
    int kind;
    if (g_GameLogic[0x121] == 7 || g_GameLogic[0x121] == 8) {
        return;
    }
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    if (g_d_GameSettings[7] == 6 && g_Minigame[0x19A4] != 0) {
        return;
    }
    if (!((g_GameLogic[0x121] > 1 && (g_d_GameSettings[7] != 2 || g_Practice[0x193] != 2) && g_GameLogic[0x14F] == 0) ||
          g_GameLogic[0x11E] == 2)) {
        return;
    }
    if (g_d_GameSettings[7] == 2 && i >= 1 &&
        (g_Practice[0x193] == 0 || g_Practice[0x193] == 1 || g_Practice[0x194] == 4 || g_Practice[0x194] == 5)) {
        return;
    }
    if (g_Ball[0x1BF0] != 0 || g_Ball[0x1BD1] != 0 || (*(s16*)(g_Ball + 0x1B66) < 20 && i == 1) || f[0x1EE] != 0 ||
        f[0x1EF] != 0 || f[0x20F] != 0 || f[0x207] != 0 || (i == 0 && f[0x1D2] + 5 > *(s16*)(g_Ball + 0x1B66)) ||
        g_Ball[0x1BD0] != 0 || g_Ball[0x1BC9] == 1 || f[0x210] != 0) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1BA0) != 0 &&
        (*(s16*)(g_Ball + 0x1BA0) < 30 || (*(s16*)(f + 0x19C) == 0 && *(s16*)(g_Ball + 0x1BA0) < 20))) {
        return;
    }
    if (f[0x1ED] != 0 || f[0x25A] != 0 || (f[0x211] != 0 && f[0x212] == 3) || g_Ball[0x1BF3] != 0) {
        return;
    }
    kind = *(int*)(g_Ball + 0x1B44) & 0x7F;
    if (kind == 7 || kind == 8) {
        return;
    }
    f[0x258] = 0;
    if (g_Ball[0x1BC9] == 2) {
        if (fn_3_2AD68(i) == 0) {
            fn_3_2A69C(i);
        }
    } else if (f[0x203] != 0) {
        fn_3_2A164(i);
    } else if (f[0x205] != 0) {
        fn_3_27D68(i);
    } else {
        if (fn_3_2BB04(i) == 0 && fn_3_2B694(i) == 0) {
            if ((*(u8**)(g_FieldingLogic + 0x8C))[2] == 0) {
                fn_3_2C2F0(i);
                return;
            }
            if (fn_3_2A288(i) == 0) {
                return;
            }
            (*(u8**)(g_FieldingLogic + 0x8C))[4] = 0;
        }
        if (f[0x265] == 0 && checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) == 0) {
            fn_3_26664(i);
        }
        if (f[0x258] == 1) {
            if (f[0x259] != 0) {
                f[0x1EE] = 0;
            } else {
                f[0x1EE] = *(f32*)(g_Ball + 0x1A58) * lbl_3_data_5CDC[3] * lbl_3_data_5D08[f[0x1C9]];
                if (f[0x1EE] < 3) {
                    f[0x1EE] = 3;
                }
                f[0x1EE] = f[0x1EE] + *(s16*)(f + 0x24C);
            }
        } else {
            f[0x1EE] = 0;
        }
        if (f[0x258] <= 1 && checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 7) != 0) {
            fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[who], 7);
            playSoundEffect(0x1A8);
        }
    }
}
#endif

// .text:0x0002CBE0 size:0x314 mapped:0x8066BC74
// NONMATCHING 95%: registers only; loop pointer/counter r28/r29 swapped and f3/f4 in the ball-position sqrt
#if NONMATCHING
int fn_3_2CBE0(int a) {
    int n = *(s8*)(g_Minigame + 0x18F8 + a);
    int i;
    u8* f;
    s16 hb;
    f32 sz;
    f32 z;
    f32 x;
    f32 d;
    f32 sx;
    g_Minigame[0x1922] = a;
    g_Minigame[0x1923] = n;
    f = g_Fielders + n * 0x268;
    fn_3_55EEC(n);
    if (*(s16*)(g_Minigame + 0x19BC) == 1 && *(f32*)(f + 0x70) > lbl_3_rodata_B90) {
        g_Minigame[0x19D0] = 1;
    }
    if (fn_3_53130(n) != 0) {
        if (g_Minigame[0x19D0] == 0) {
            return 0;
        }
    } else {
        if (g_Minigame[0x19D0] == 0) {
            return 0;
        }
        *(s16*)(f + 0x19E) = fn_3_9FE6C_normalizeAngle(*(s16*)(f + 0x180) + 0x800);
        *(f32*)(f + 0x48) = shortAngleToRad_Capped(*(s16*)(f + 0x19E));
        fn_3_3A584(n);
    }
    fn_3_55CC4(n);
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (g_d_GameSettings[0x11] == 0 || g_Minigame[0x1923] == i) {
            fn_3_54B58(i);
            *(f32*)(f + 0x7C) = fn_3_9CE0(*(f32*)f, *(f32*)(f + 8));
            if (0.0f == *(f32*)(f + 0x50)) {
                *(f32*)(f + 0x38) = 0.0f;
                *(f32*)(f + 0x3C) = 0.0f;
            } else {
                *(f32*)(f + 0x38) = *(f32*)(f + 0x30) / *(f32*)(f + 0x50);
                *(f32*)(f + 0x3C) = *(f32*)(f + 0x34) / *(f32*)(f + 0x50);
            }
            f[0x1EA] = 0;
            f[0x217] = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings[0x11] != 0) {
        fn_3_53F48();
    } else if ((hb = *(s16*)(g_Ball + 0x1B78)) >= 0) {
        x = *(f32*)(g_Fielders + hb * 0x268);
        z = ((f32*)(g_Fielders + 8))[hb * 0x9A];
        *(f32*)(g_Ball + 0) = x;
        *(f32*)(g_Ball + 4) = ((f32*)(g_Fielders + 4))[hb * 0x9A];
        *(f32*)(g_Ball + 8) = z;
        *(f32*)(g_Ball + 0x348) = x;
        *(f32*)(g_Ball + 0x34C) = z;
        sx = x * x;
        sz = z * z;
        d = sx + sz;
        SQRT_L(d);
        *(f32*)(g_Ball + 0x1A00) = d;
    }
    return 1;
}
#endif

// .text:0x0002CEF4 size:0x18C mapped:0x8066BF88
void fn_3_2CEF4(int i) {
    u8* f;
    f32 dx;
    f32 dz;
    f32 d;
    fn_3_2D47C(i);
    f = g_Fielders + i * 0x268;
    *(s16*)(f + 0x19E) = -1;
    dz = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
    dx = *(f32*)(f + 0x14) - *(f32*)f;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    if (d < lbl_3_rodata_B80) {
        *(f32*)(f + 0x68) = d;
        f[0x209] = 0;
    } else {
        *(s16*)(f + 0x19E) = fn_3_9FB8C(dx, dz);
        f[0x209] = 0;
    }
    fn_3_3A584(i);
}

// .text:0x0002D080 size:0x288 mapped:0x8066C114
// NONMATCHING 90%: constant-address hoisting in the prologue and float/int register allocation differ
#if NONMATCHING
int fn_3_2D080(int i) {
    f32 bestY = lbl_3_rodata_B94;
    int best = 9999;
    s16 lead = lbl_3_data_1C3C[1];
    u8* f = g_Fielders + i * 0x268;
    int saved = 0;
    int found = 0;
    int k = 0;
    f32* y;
    int t;
    f32 d;
    f32 spd;
    while (k < 360) {
        y = (f32*)(g_Ball + k * 16 + 0x358);
        if (*y > lbl_3_rodata_B98) {
            if (*y > lbl_3_rodata_B9C) {
                k += 10;
            } else if (*y > lbl_3_rodata_BA0) {
                k += 5;
            } else {
                k += 2;
            }
            continue;
        }
        if (*(f32*)(g_Ball + k * 16 + 0x354) == *(f32*)f && *(f32*)(g_Ball + k * 16 + 0x35C) == *(f32*)(f + 8)) {
            t = 1;
        } else {
            d = (*(f32*)(g_Ball + k * 16 + 0x354) - *(f32*)f) * (*(f32*)(g_Ball + k * 16 + 0x354) - *(f32*)f) +
                (*(f32*)(g_Ball + k * 16 + 0x35C) - *(f32*)(f + 8)) * (*(f32*)(g_Ball + k * 16 + 0x35C) - *(f32*)(f + 8));
            SQRT_L(d);
            spd = *(f32*)(f + 0x58);
            if (lbl_3_rodata_B20 == spd) {
                spd = lbl_3_rodata_B60;
            }
            t = (f[0x1D1] / 2) + (int)(d / spd);
        }
        if (t < k - lead) {
            if (!(*y < *(f32*)(f + 0xF4))) {
                if (found && bestY < *y) {
                    k = saved;
                    break;
                }
                bestY = *y;
                saved = k;
                found = 1;
            }
        } else if (found) {
            k = saved;
            break;
        }
        if (t > best && !found) {
            break;
        }
        best = t;
        k += 3;
    }
    if (k >= 360) {
        k = 359;
    }
    return k;
}
#endif

// .text:0x0002D308 size:0x174 mapped:0x8066C39C
// 95%: prologue scheduling only; original loads the 0.0f const (f0) before the sth/first fielder loads (tried local z = B20, f assigned late)
void fn_3_2D308(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    *(s16*)(f + 0x19E) = -1;
    dz = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
    dx = *(f32*)(f + 0x14) - *(f32*)f;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    if (d < lbl_3_rodata_B80) {
        *(f32*)(f + 0x68) = d;
        f[0x209] = 0;
        return;
    }
    *(s16*)(f + 0x19E) = fn_3_9FB8C(dx, dz);
    f[0x209] = 0;
}

// .text:0x0002D47C size:0x2EC mapped:0x8066C510
void fn_3_2D47C(int i) {
    u8* f = g_Fielders + i * 0x268;
    int hold = 0;
    int best;
    int k;
    f32 d;
    f32 bestD;
    if (g_Minigame[0x19A4] != 0 || *(s16*)(g_Ball + 0x1B78) >= 0 || g_Ball[0x1BD1] != 0) {
        hold = 1;
    }
    if (g_Minigame[0x1939] != 0 && hold != 0) {
        f[0x208] = 4;
    } else if (hold != 0) {
        *(f32*)(f + 0x14) = *(f32*)f;
        *(f32*)(f + 0x1C) = *(f32*)(f + 8);
        return;
    } else if (g_Ball[0x1BCC] != 0) {
        f[0x208] = 2;
    }
    if (f[0x208] == 1) {
        if (*(s16*)(g_Ball + 0x1B7A) == 1) {
            f[0x208] = 2;
        } else {
            *(f32*)(f + 0x14) = *(f32*)(g_Ball + 0x348);
            *(f32*)(f + 0x1C) = *(f32*)(g_Ball + 0x34C);
        }
    }
    if (f[0x208] == 2) {
        *(f32*)(f + 0x14) = *(f32*)g_Ball;
        *(f32*)(f + 0x1C) = *(f32*)(g_Ball + 8);
    }
    if (f[0x208] == 3) {
        int n = fn_3_2D080(i);
        *(f32*)(f + 0x14) = *(f32*)(g_Ball + n * 16 + 0x354);
        *(f32*)(f + 0x1C) = *(f32*)(g_Ball + n * 16 + 0x35C);
    }
    if (f[0x208] == 4) {
        best = -1;
        bestD = lbl_3_rodata_BA4;
        for (k = 0; k < 100; k++) {
            if (g_Minigame[0x193A + k] != 0) {
                d = DIST2_XZ(*(f32*)f, *(f32*)(f + 8), *(f32*)(g_Minigame + k * 12 + 0xCD0),
                             *(f32*)(g_Minigame + k * 12 + 0xCD8));
                SQRT_L(d);
                if (d < bestD) {
                    best = k;
                    bestD = d;
                }
            }
        }
        if (best >= 0) {
            *(f32*)(f + 0x14) = *(f32*)(g_Minigame + best * 12 + 0xCD0);
            *(f32*)(f + 0x1C) = *(f32*)(g_Minigame + best * 12 + 0xCD8);
        }
    }
}

// .text:0x0002D768 size:0x1C4 mapped:0x8066C7FC
void fn_3_2D768(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    if (f[0x208] == 0) {
        if (f[0x1DB] == 0) {
            f[0x208] = 1;
        } else {
            f[0x208] = 3;
        }
    }
    f[0x1D6] = 0;
    fn_3_2D47C(i);
    *(s16*)(f + 0x19E) = -1;
    dz = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
    dx = *(f32*)(f + 0x14) - *(f32*)f;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    if (d < lbl_3_rodata_B80) {
        *(f32*)(f + 0x68) = d;
        f[0x209] = 0;
    } else {
        *(s16*)(f + 0x19E) = fn_3_9FB8C(dx, dz);
        f[0x209] = 0;
    }
    fn_3_3A584(i);
}

// .text:0x0002D92C size:0x198 mapped:0x8066C9C0
void fn_3_2D92C(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    if (f[0x1EC] == 0) {
        fn_3_2D47C(i);
        *(s16*)(f + 0x19E) = -1;
        dz = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
        dx = *(f32*)(f + 0x14) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_rodata_B80) {
            *(f32*)(f + 0x68) = d;
            f[0x209] = 0;
        } else {
            *(s16*)(f + 0x19E) = fn_3_9FB8C(dx, dz);
            f[0x209] = 0;
        }
        fn_3_3A584(i);
    }
}

// .text:0x0002DAC4 size:0x230 mapped:0x8066CB58
void fn_3_2DAC4(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    if (f[0x1ED] == 0) {
        if (f[0x208] == 0) {
            if (f[0x1DB] == 0) {
                f[0x208] = 1;
            } else {
                f[0x208] = 3;
            }
        }
        f[0x1D6] = 0;
        fn_3_2D47C(i);
        *(s16*)(f + 0x19E) = -1;
        dz = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
        dx = *(f32*)(f + 0x14) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_rodata_B80) {
            *(f32*)(f + 0x68) = d;
            f[0x209] = 0;
        } else {
            *(s16*)(f + 0x19E) = fn_3_9FB8C(dx, dz);
            f[0x209] = 0;
        }
        fn_3_3A584(i);
    }
    if (*(s16*)(g_Minigame + 0x18AA) != 0) {
        SetFielderAct(i, 0x1C, 0xE0);
    }
}

// .text:0x0002DCF4 size:0xC0 mapped:0x8066CD88
void fn_3_2DCF4(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 n = *(s16*)(g_Ball + 0x1B66);
    if (n > 0 && n >= f[0x1D2]) {
        if (fn_3_53130(i) == 0) {
            fn_3_447C4(i);
            if (i != -1) {
                f[0x1D3] = 0x1B;
                if (*(int*)(lbl_3_data_3C40 + 0xD8) >= 0) {
                    g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0xD8);
                }
                f[0x1D5] = 0;
                f[0x1D6] = 0;
                *(s16*)(f + 0x1A4) = 0;
                *(s16*)(f + 0x1AC) = 0;
                f[0x1FF] = 0;
            }
        }
    }
}

// .text:0x0002DDB4 size:0x668 mapped:0x8066CE48
// NONMATCHING 80%: original re-materialises g_AiLogic per access (lis/addi/add) and uses lhau; we keep one base pointer
#if NONMATCHING
void fn_3_2DDB4(void) {
    u8 p = g_Minigame[0x1922];
    u8* ai = (u8*)g_AiLogic;
    u8* f = g_Fielders + g_Minigame[0x1923] * 0x268;
    f32 d;
    f32 k;
    f32 dx;
    f32 dz;
    if (*(s16*)(ai + p * 2 + 0x9C) < 0x7FFE) {
        *(s16*)(ai + p * 2 + 0x9C) = *(s16*)(ai + p * 2 + 0x9C) + 1;
    } else {
        *(s16*)(ai + p * 2 + 0x9C) = 0x7FFF;
    }
    if (ai[p + 0xB4] == 0) {
        if (ai[p + 0xB8] == 0) {
            d = *(f32*)f * *(f32*)f + *(f32*)(f + 8) * *(f32*)(f + 8);
            k = lbl_3_data_1C44[g_Batter[0x89]];
            SQRT_L(d);
            *(f32*)(ai + p * 8 + 0x7C) = (*(f32*)f / d) * k + *(f32*)f;
            *(f32*)(ai + p * 8 + 0x80) = (*(f32*)(f + 8) / d) * k + *(f32*)(f + 8);
            *(s16*)(ai + p * 2 + 0x9C) = 0;
            ai[p + 0xB8] = 1;
        } else if (ai[p + 0xB8] == 2) {
            if (f[0x1C8] == 2 || f[0x1C8] == 3) {
                ai[p + 0xB4] = 1;
                *(s16*)(ai + p * 2 + 0xAC) = *(s16*)(f + 0x180);
            } else {
                ai[p + 0xB4] = 2;
            }
            ai[p + 0xB8] = 0;
        }
    } else if (ai[p + 0xB4] == 1) {
        if (ai[p + 0xB8] == 0) {
            d = *(f32*)f * *(f32*)f + *(f32*)(f + 8) * *(f32*)(f + 8);
            SQRT_L(d);
            if (*(f32*)f < lbl_3_rodata_BA8) {
                *(s16*)(ai + p * 2 + 0xAC) = *(s16*)(f + 0x180) + RandomInt_Game(0x400) - 0x600;
            } else if (*(f32*)f > lbl_3_rodata_B70) {
                *(s16*)(ai + p * 2 + 0xAC) = *(s16*)(f + 0x180) + RandomInt_Game(0x400) + 0x200;
            } else if (d > lbl_3_rodata_BAC) {
                *(s16*)(ai + p * 2 + 0xAC) = RandomInt_Game(0x800) + *(s16*)(f + 0x180) + 0x400;
            } else if (d < lbl_3_rodata_BB0) {
                *(s16*)(ai + p * 2 + 0xAC) = RandomInt_Game(0x800) + *(s16*)(f + 0x180) - 0x400;
            } else if (RandomInt_Game(2) != 0) {
                *(s16*)(ai + p * 2 + 0xAC) = RandomInt_Game(0x400) + *(s16*)(ai + p * 2 + 0xAC) - 0x200;
            } else {
                *(s16*)(ai + p * 2 + 0xAC) = RandomInt_Game(0x1000);
            }
            *(s16*)(ai + p * 2 + 0xAC) = fn_3_9FE6C_normalizeAngle(*(s16*)(ai + p * 2 + 0xAC));
            *(s16*)(ai + p * 2 + 0xA4) = RandomInt_Game_Range(lbl_3_data_1C54[0], lbl_3_data_1C54[1]);
            *(s16*)(ai + p * 2 + 0x9C) = 0;
            ai[p + 0xB8] = 1;
        }
    }
    if (ai[p + 0xB8] == 1) {
        if (ai[p + 0xB4] == 1) {
            *(s16*)(g_Controls + p * 16) = *(s16*)(ai + p * 2 + 0xAC);
            if (*(s16*)(ai + p * 2 + 0x9C) >= *(s16*)(ai + p * 2 + 0xA4)) {
                ai[p + 0xB8] = 0;
            }
        } else {
            dz = *(f32*)(ai + p * 8 + 0x80) - *(f32*)(f + 8);
            dx = *(f32*)(ai + p * 8 + 0x7C) - *(f32*)f;
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (d < lbl_3_rodata_B80) {
                ai[p + 0xB8] = 2;
                return;
            }
            *(s16*)(g_Controls + p * 16) = fn_3_9FB8C(dx, dz);
        }
    }
}
#endif

// .text:0x0002E41C size:0x460 mapped:0x8066D4B0
// NONMATCHING 85%: bss base hoisting, history-fill loop guard and stfsx addressing of the pitcher copy differ; logic and calls match
#if NONMATCHING
void fn_3_2E41C(void) {
    int k;
    int i;
    int n;
    int pad;
    s16* hist;
    u8* in;
    u8* f;
    s16 v;
    u8 t;
    if (lbl_3_common_bss_34C90[0x1D5] != 0) {
        return;
    }
    if (g_Minigame[0x1A2A] == 2) {
        if (g_Minigame[0x1A7E] == 0) {
            n = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18F8);
            *(f32*)(g_Fielders + n * 0x268) = *(f32*)(g_Pitcher + 0x8C);
            *(f32*)(g_Fielders + n * 0x268 + 8) = *(f32*)(g_Pitcher + 0x90);
        }
        return;
    }
    for (k = 0; k < 4; k++) {
        if (*(s8*)(g_Minigame + 0x18F8 + k) > 0) {
            g_Minigame[0x1923] = g_Minigame[0x18F8 + k];
            g_Minigame[0x1922] = k;
            if (g_d_GameSettings[7] == 6 && g_Minigame[0x18D8 + k] != 0) {
                fn_3_2DDB4();
            }
            pad = *(s8*)(g_Minigame + 0x18CC + k);
            hist = lbl_3_bss_C8.hist[pad];
            in = g_Controls + pad * 0x10;
            for (i = 19; i > 0; i--) {
                lbl_3_bss_C8.tmp[i] = hist[i - 1];
            }
            lbl_3_bss_C8.tmp[0] = *(s16*)in;
            if (lbl_3_bss_C8.tmp[0] == -1) {
                for (i = 1; i < 20; i++) {
                    lbl_3_bss_C8.tmp[i] = -1;
                }
            }
            if (lbl_3_bss_C8.tmp[1] >= 0 && lbl_3_bss_C8.tmp[2] != 0) {
                lbl_3_bss_C8.cur = lbl_3_bss_C8.tmp[0];
            } else {
                lbl_3_bss_C8.cur = -1;
            }
            for (i = 0; i < 20; i++) {
                hist[i] = lbl_3_bss_C8.tmp[i];
            }
            *(u16*)(g_FieldingLogic + 0x148) = *(u16*)(in + 4);
            *(u16*)(g_FieldingLogic + 0x14A) = *(u16*)(in + 6);
            *(u16*)(g_FieldingLogic + 0x14C) = *(u16*)(in + 8);
            *(u8**)(g_FieldingLogic + 0x70) = g_FieldingLogic + k * 0x1C;
            *(u8**)(g_FieldingLogic + 0x8C) = g_FieldingLogic + k * 6 + 0x74;
            g_FieldingLogic[k * 6 + 0x76] = 0;
            v = lbl_3_bss_C8.tmp[0];
            f = g_Fielders + *(s8*)(g_Minigame + 0x18F8 + k) * 0x268;
            if (g_FieldingLogic[0x10E] != 0) {
                v = -1;
            }
            *(s16*)(f + 0x19E) = v;
            if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x144] == 0 && v >= 0 && *(s16*)(f + 0x1A0) > 10) {
                *(s16*)(g_FieldingLogic + 0xCC) = -1;
            }
            if (v >= 0) {
                t = (*(u8**)(g_FieldingLogic + 0x70))[0x1A];
                if (t != 3 && t != 4) {
                    if (*(u16*)(g_FieldingLogic + 0x14A) & 0x200) {
                        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = 0;
                    }
                    if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0 && g_Practice[0x1C5] != 0) {
                        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = 0;
                    }
                }
            }
            fn_3_3A584(*(s8*)(g_Minigame + 0x18F8 + k));
        }
    }
    if (g_d_GameSettings[0x11] != 0) {
        if (*(s8*)(g_Minigame + 0x1904) >= 0) {
            n = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18F8);
            *(f32*)(g_Fielders + n * 0x268) = *(f32*)(g_Pitcher + 0x8C);
            *(f32*)(g_Fielders + n * 0x268 + 8) = *(f32*)(g_Pitcher + 0x90);
        }
    } else {
        *(f32*)g_Fielders = *(f32*)(g_Pitcher + 0x8C);
        *(f32*)(g_Fielders + 8) = *(f32*)(g_Pitcher + 0x90);
    }
}
#endif

// .text:0x0002E87C size:0x1A8 mapped:0x8066D910
void fn_3_2E87C(void) {
    f32 spC;
    f32 sp8;
    u8* f;
    int i;
    u8 m;
    fn_3_58F58(0, &spC, &sp8);
    *(f32*)g_Fielders = spC;
    *(f32*)(g_Fielders + 8) = sp8;
    *(f32*)(g_Fielders + 0x14) = 0.0f;
    *(f32*)(g_Fielders + 0x18) = 0.0f;
    *(f32*)(g_Fielders + 0x1C) = 0.0f;
    *(f32*)(g_Fielders + 0x30) = 0.0f;
    *(f32*)(g_Fielders + 0x34) = 0.0f;
    *(f32*)(g_Fielders + 0x38) = 0.0f;
    m = g_Minigame[0x1906];
    if (m >= 4) {
        *(f32*)(g_Fielders + 0x738) = lbl_3_data_18984[2];
        *(f32*)(g_Fielders + 0x740) = lbl_3_data_18984[3];
    } else if (m >= 3) {
        *(f32*)(g_Fielders + 0x738) = lbl_3_data_18984[0];
        *(f32*)(g_Fielders + 0x740) = lbl_3_data_18984[1];
    }
    if (m >= 4) {
        *(f32*)(g_Fielders + 0x9A0) = lbl_3_data_18984[4];
        *(f32*)(g_Fielders + 0x9A8) = lbl_3_data_18984[5];
    }
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        *(f32*)(f + 0x14) = 0.0f;
        *(f32*)(f + 0x18) = 0.0f;
        *(f32*)(f + 0x1C) = 0.0f;
        *(f32*)(f + 0x30) = 0.0f;
        *(f32*)(f + 0x34) = 0.0f;
        *(f32*)(f + 0xD4) = *(f32*)(f + 0);
        *(f32*)(f + 0xD8) = *(f32*)(f + 8);
        *(f32*)(f + 0x50) = 0.0f;
        f[0x1D9] = 0;
        *(s8*)(f + 0x1F5) = -1;
        spC = -*(f32*)(f + 0);
        sp8 = -*(f32*)(f + 8);
        *(f32*)(f + 0x48) = atan2(sp8, spC);
    }
    ((u8*)g_AiLogic)[0xB4] = 0;
    ((u8*)g_AiLogic)[0xB8] = 0;
    ((u8*)g_AiLogic)[0xB5] = 0;
    ((u8*)g_AiLogic)[0xB9] = 0;
    ((u8*)g_AiLogic)[0xB6] = 0;
    ((u8*)g_AiLogic)[0xBA] = 0;
    ((u8*)g_AiLogic)[0xB7] = 0;
    ((u8*)g_AiLogic)[0xBB] = 0;
}

// .text:0x0002EA24 size:0x64 mapped:0x8066DAB8
void fn_3_2EA24(void) {
    int i;
    for (i = 0; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x18F8 + i) >= 0) {
            fn_3_55EEC(*(s8*)(g_Minigame + 0x18F8 + i));
        }
    }
    fn_3_2E41C();
    fn_3_313B0();
}

// .text:0x0002EA88 size:0x43C mapped:0x8066DB1C
// NONMATCHING 90%: register allocation (fielder pointer/loop regs, ball-position floats) and prologue scheduling
#if NONMATCHING
void fn_3_2EA88(int a) {
    s16* p = &lbl_3_bss_170 + 0x13;
    int n = *(s8*)(g_Minigame + a + 0x18F8);
    u8* f = g_Fielders + n * 0x268;
    int k;
    int i;
    s16 hb;
    f32 x;
    f32 z;
    f32 d;
    f32 sx;
    f32 sz;
    for (k = 0x13; k != 0; k--) {
        *p = -1;
        p--;
    }
    *(u16*)(g_FieldingLogic + 0x148) = 0;
    *(u16*)(g_FieldingLogic + 0x14A) = 0;
    *(u16*)(g_FieldingLogic + 0x14C) = 0;
    if (g_Minigame[0x1A2A] == 5) {
        if (f[0x1D3] == 0 || f[0x1D3] == 9) {
            SetFielderAct(n, 0xF, 0x78);
        }
    } else {
        if (*(s16*)(g_Ball + 0x1B66) <= 0) {
            return;
        }
        g_Minigame[0x1923] = n;
        g_Minigame[0x1922] = a;
        if (*(s16*)(g_Ball + 0x1B66) == 1) {
            fn_3_4FB34();
            fn_3_447C4(n);
            SetFielderAct(n, 0x1A, 0xD0);
            goto tail;
        }
    }
    fn_3_57BB4();
    fn_3_55EEC(n);
    ((FielderActEntry*)lbl_3_data_3C40)[g_Fielders[n * 0x268 + 0x1D3]].fn(n);
    fn_3_55CC4(n);
    if (*(s16*)(g_Minigame + 0x18AA) != 0) {
        SetFielderAct(n, 0x1C, 0xE0);
    }
tail:
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (g_d_GameSettings[0x11] == 0 || g_Minigame[0x1923] == i) {
            fn_3_54B58(i);
            *(f32*)(f + 0x7C) = fn_3_9CE0(*(f32*)f, *(f32*)(f + 8));
            if (0.0f == *(f32*)(f + 0x50)) {
                *(f32*)(f + 0x38) = 0.0f;
                *(f32*)(f + 0x3C) = 0.0f;
            } else {
                *(f32*)(f + 0x38) = *(f32*)(f + 0x30) / *(f32*)(f + 0x50);
                *(f32*)(f + 0x3C) = *(f32*)(f + 0x34) / *(f32*)(f + 0x50);
            }
            f[0x1EA] = 0;
            f[0x217] = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings[0x11] != 0) {
        fn_3_53F48();
    } else if ((hb = *(s16*)(g_Ball + 0x1B78)) >= 0) {
        x = *(f32*)(g_Fielders + hb * 0x268);
        z = ((f32*)(g_Fielders + 8))[hb * 0x9A];
        *(f32*)(g_Ball + 0) = x;
        *(f32*)(g_Ball + 4) = ((f32*)(g_Fielders + 4))[hb * 0x9A];
        *(f32*)(g_Ball + 8) = z;
        *(f32*)(g_Ball + 0x348) = x;
        *(f32*)(g_Ball + 0x34C) = z;
        sx = x * x;
        sz = z * z;
        d = sx + sz;
        SQRT_L(d);
        *(f32*)(g_Ball + 0x1A00) = d;
    }
}
#endif

// .text:0x0002EEC4 size:0x5C0 mapped:0x8066DF58
// NONMATCHING 85%: register allocation; fn_3_107D70 is declared u8 (its unit's header) but the original tests the full r3 (cmplwi)
#if NONMATCHING
void fn_3_2EEC4(int a) {
    u8* pads = g_Minigame + 0x18CC;
    int n = *(s8*)(g_Minigame + a + 0x18F8);
    u8* f;
    u8* in;
    s16* hist;
    int i;
    s16 hb;
    f32 x;
    f32 z;
    f32 d;
    f32 sx;
    f32 sz;
    g_Minigame[0x1922] = a;
    g_Minigame[0x1923] = n;
    f = g_Fielders + n * 0x268;
    in = g_Controls + *(s8*)(pads + (u8)a) * 0x10;
    if (fn_3_107D70(pads[(u8)a]) != 0) {
        in = g_Minigame + *(s8*)(pads + g_Minigame[0x1922]) * 0x10 + 0x1D7C;
    }
    hist = lbl_3_bss_C8.hist[*(s8*)(pads + g_Minigame[0x1922])];
    for (i = 19; i > 0; i--) {
        lbl_3_bss_C8.tmp[i] = hist[i - 1];
    }
    lbl_3_bss_C8.tmp[0] = *(s16*)in;
    if (lbl_3_bss_C8.tmp[0] == -1) {
        for (i = 1; i < 20; i++) {
            lbl_3_bss_C8.tmp[i] = -1;
        }
    }
    if (lbl_3_bss_C8.tmp[1] >= 0 && lbl_3_bss_C8.tmp[2] != 0) {
        lbl_3_bss_C8.cur = lbl_3_bss_C8.tmp[0];
    } else {
        lbl_3_bss_C8.cur = -1;
    }
    for (i = 0; i < 20; i++) {
        hist[i] = lbl_3_bss_C8.tmp[i];
    }
    *(u16*)(g_FieldingLogic + 0x148) = *(u16*)(in + 4);
    *(u16*)(g_FieldingLogic + 0x14A) = *(u16*)(in + 6);
    *(u16*)(g_FieldingLogic + 0x14C) = *(u16*)(in + 8);
    if (g_Minigame[0x1A2A] != 5 && (*(u16*)(g_FieldingLogic + 0x14A) & 0x100)) {
        (*(u8**)(g_FieldingLogic + 0x8C))[2] = 2;
        *(s16*)*(u8**)(g_FieldingLogic + 0x8C) = lbl_3_bss_C8.tmp[0];
    }
    if (g_Minigame[0x1A2A] == 5 || g_Minigame[0x1A2A] == 6) {
        if (f[0x1D3] == 0 || f[0x1D3] == 9) {
            SetFielderAct(n, 0xF, 0x78);
        }
    } else {
        if (*(s16*)(g_Ball + 0x1B66) <= 0) {
            return;
        }
        if (*(s16*)(g_Ball + 0x1B66) == 1) {
            SetFielderAct(n, 0xF, 0x78);
            goto tail;
        }
    }
    fn_3_51220();
    fn_3_55EEC(n);
    ((FielderActEntry*)lbl_3_data_3C40)[f[0x1D3]].fn(n);
    fn_3_55CC4(n);
tail:
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (g_d_GameSettings[0x11] == 0 || g_Minigame[0x1923] == i) {
            fn_3_54B58(i);
            *(f32*)(f + 0x7C) = fn_3_9CE0(*(f32*)f, *(f32*)(f + 8));
            if (0.0f == *(f32*)(f + 0x50)) {
                *(f32*)(f + 0x38) = 0.0f;
                *(f32*)(f + 0x3C) = 0.0f;
            } else {
                *(f32*)(f + 0x38) = *(f32*)(f + 0x30) / *(f32*)(f + 0x50);
                *(f32*)(f + 0x3C) = *(f32*)(f + 0x34) / *(f32*)(f + 0x50);
            }
            f[0x1EA] = 0;
            f[0x217] = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings[0x11] != 0) {
        fn_3_53F48();
    } else if ((hb = *(s16*)(g_Ball + 0x1B78)) >= 0) {
        x = *(f32*)(g_Fielders + hb * 0x268);
        z = ((f32*)(g_Fielders + 8))[hb * 0x9A];
        *(f32*)(g_Ball + 0) = x;
        *(f32*)(g_Ball + 4) = ((f32*)(g_Fielders + 4))[hb * 0x9A];
        *(f32*)(g_Ball + 8) = z;
        *(f32*)(g_Ball + 0x348) = x;
        *(f32*)(g_Ball + 0x34C) = z;
        sx = x * x;
        sz = z * z;
        d = sx + sz;
        SQRT_L(d);
        *(f32*)(g_Ball + 0x1A00) = d;
    }
}
#endif

// .text:0x0002F484 size:0xF0 mapped:0x8066E518
void fn_3_2F484(void) {
    int i;
    fn_3_58688();
    for (i = 0; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x18F8 + i) >= 0) {
            *(u8**)(g_FieldingLogic + 0x70) = g_FieldingLogic + i * 0x1C;
            *(u8**)(g_FieldingLogic + 0x8C) = g_FieldingLogic + i * 6 + 0x74;
            if (g_d_GameSettings[7] != 6 || *(s16*)(g_Minigame + 0x19BC) == 0 ||
                i != *(s8*)(g_Minigame + 0x19C6) || fn_3_2CBE0(i) == 0) {
                if (g_Minigame[0x18D8 + i] == 0) {
                    fn_3_2EEC4(i);
                } else if (g_Minigame[0x1A2A] == 6) {
                    fn_3_2EEC4(i);
                } else {
                    fn_3_2EA88(i);
                }
            }
        }
    }
}

// .text:0x0002F574 size:0x260 mapped:0x8066E608
void fn_3_2F574(int i) {
    Ent16* tbl = (Ent16*)lbl_3_data_4884;
    u8* f = g_Fielders + i * 0x268;
    int type = f[0x1CC];
    f32 pos[1];
    f32 d;
    f[0x204] = f[0x204] + 1;
    *(f32*)(f + 0x164) = *(f32*)(f + 0x164) - tbl[type].b;
    if (*(s16*)(f + 0x1AE) >= *(s16*)(f + 0x1B0) && *(f32*)(f + 0x164) < 0.0f) {
        *(f32*)(f + 0x164) = 0.0f;
    }
    *(f32*)(f + 0x15C) = *(f32*)(f + 0x15C) + *(f32*)(f + 0x164);
    *(s16*)(f + 0x1AE) = *(s16*)(f + 0x1AE) - 1;
    if (0.0f != *(f32*)(f + 0x160) || 0.0f != *(f32*)(f + 0x168)) {
        *(f32*)(f + 0x30) = *(f32*)(f + 0x160);
        *(f32*)(f + 0x34) = *(f32*)(f + 0x168);
        d = *(f32*)(f + 0x30) * *(f32*)(f + 0x30) + *(f32*)(f + 0x34) * *(f32*)(f + 0x34);
        SQRT_L(d);
        *(f32*)(f + 0x50) = d;
        if (fn_3_51798(i, pos) != 0) {
            *(f32*)(f + 0x160) = 0.0f;
            *(f32*)(f + 0x168) = 0.0f;
            *(f32*)(f + 0x30) = 0.0f;
            *(f32*)(f + 0x34) = 0.0f;
            *(f32*)(f + 0x50) = 0.0f;
        } else {
            *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
            *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
        }
    }
    *(f32*)(f + 0x14) = *(f32*)f;
    *(f32*)(f + 0x1C) = *(f32*)(f + 8);
    f[0x1F0] = 1;
    if (*(s16*)(f + 0x1AE) <= 0) {
        f[0x203] = 0;
        *(f32*)(f + 0x15C) = 0.0f;
        *(s16*)(f + 0x1A0) = 0;
    }
}

// .text:0x0002F7D4 size:0x150 mapped:0x8066E868
// NONMATCHING 80%: original addresses the jump table entry through two separately computed bases (lfsx + add); ours CSEs one
#if NONMATCHING
void fn_3_2F7D4(int i) {
    u8* f = g_Fielders + i * 0x268;
    int type = f[0x1CC];
    int n;
    int k;
    f[0x203] = 1;
    *(f32*)(f + 0x15C) = lbl_3_rodata_B20;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            i = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            i = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    *(f32*)(f + 0x164) = ((Ent16*)lbl_3_data_4884)[type].a;
    *(f32*)(f + 0x160) = *(f32*)(f + 0x38) * lbl_3_rodata_B24 * ((Ent16*)lbl_3_data_4884)[type].c;
    *(f32*)(f + 0x168) = *(f32*)(f + 0x3C) * lbl_3_rodata_B24 * ((Ent16*)lbl_3_data_4884)[type].c;
    k = (int)((Ent16*)lbl_3_data_4884)[type].d;
    n = (int)(*(f32*)(f + 0x164) / ((Ent16*)lbl_3_data_4884)[type].b);
    *(s16*)(f + 0x1B0) = n + 1;
    *(s16*)(f + 0x1AE) = n * 2 + k + 2;
    f[0x204] = 0;
    if (type != 0) {
        fn_3_1682AC(((int*)(lbl_8036E548 + 0x2C50))[i], 6);
    }
}
#endif

// .text:0x0002F924 size:0x278 mapped:0x8066E9B8
void fn_3_2F924(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 dh;
    f32 k;
    f32 h;
    if (f[0x207] == 1) {
        dx = *(f32*)(f + 0x128) - *(f32*)f;
        dz = *(f32*)(f + 0x130) - *(f32*)(f + 8);
        dh = *(f32*)(f + 0x12C) - *(f32*)(f + 0x148);
        if (*(s16*)(f + 0x1B4) > 1) {
            k = 1.0f / *(s16*)(f + 0x1B4);
        } else {
            k = 1.0f;
        }
        dx *= k;
        dz *= k;
        dh *= k;
        *(f32*)(f + 0x30) = dx;
        *(f32*)(f + 0x34) = dz;
        *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
        *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
        *(f32*)(f + 0x148) = *(f32*)(f + 0x148) + dh;
        *(s16*)(f + 0x1B4) = *(s16*)(f + 0x1B4) - 1;
        if (*(s16*)(f + 0x1B4) == 0) {
            f[0x207] = 2;
            *(s16*)(f + 0x1B4) = lbl_3_data_49DC[8];
            if (g_d_GameSettings[0x11] != 0) {
                u8* m = g_Minigame + f[0x20D];
                if (m[0x18D8] == 0) {
                    fn_3_6C854(*(s8*)(m + 0x18CC), 2);
                }
            } else if (g_GameLogic[*(int*)(g_GameLogic + 8) + 0x13E] == 0) {
                fn_3_6C854(*(int*)(g_GameLogic + 8), 2);
            }
            fn_3_90220(*(s16*)(f + 0x17A), 11);
        }
    } else if (f[0x207] == 2) {
        *(s16*)(f + 0x1B4) = *(s16*)(f + 0x1B4) - 1;
        if (*(s16*)(f + 0x1B4) == 0) {
            f[0x207] = 3;
            *(s16*)(f + 0x1B4) = lbl_3_data_49DC[9];
        }
    } else if (f[0x207] == 3) {
        h = *(f32*)(f + 0x148);
        *(f32*)(f + 0x148) = h - h / *(s16*)(f + 0x1B4);
        *(s16*)(f + 0x1B4) = *(s16*)(f + 0x1B4) - 1;
        if (*(s16*)(f + 0x1B4) == 0) {
            *(f32*)(f + 0x148) = 0.0f;
            f[0x207] = 4;
            *(s16*)(f + 0x1B4) = lbl_3_data_49DC[10];
        }
    } else if (f[0x207] == 4) {
        *(s16*)(f + 0x1B4) = *(s16*)(f + 0x1B4) - 1;
        if (*(s16*)(f + 0x1B4) == 0) {
            f[0x207] = 0;
        }
    }
}

// .text:0x0002FB9C size:0x390 mapped:0x8066EC30
// NONMATCHING 92%: the moved flag lives in r6 (initialised at entry) in the original, ours keeps it in r0; f-reg order in the side-step segment
#if NONMATCHING
void fn_3_2FB9C(int i) {
    int moved = 0;
    u8* f = g_Fielders + i * 0x268;
    f32 h = *(f32*)(f + 0x148);
    int dir;
    int side;
    f32 a;
    f32 cx;
    f32 cz;
    f32 y;
    f32 e;
    f32 lo;
    f32 hi;
    VecSrcDst seg;
    CollisionStruct hit;
    if (g_Ball[0x1BC9] == 1 || g_Ball[0x1BC9] == 2) {
        f[0x205] = 3;
        return;
    }
    if (*(u16*)(g_FieldingLogic + 0x14A) & 0x100) {
        f[0x205] = 3;
        return;
    }
    if (*(u16*)(g_FieldingLogic + 0x148) & 8) {
        dir = 1;
        h += *(f32*)(lbl_3_data_4930 + 0x64);
    } else if (*(u16*)(g_FieldingLogic + 0x148) & 4) {
        dir = 2;
        h -= *(f32*)(lbl_3_data_4930 + 0x64);
    } else {
        goto turn;
    }
    if (h <= 0.0f) {
        f[0x205] = 3;
        return;
    }
    y = -(h + *(f32*)(f + 0xF4));
    seg.dst.y = y;
    seg.src.y = y;
    seg.src.x = lbl_3_rodata_B64 * *(f32*)(f + 0x140) + *(f32*)f;
    seg.src.z = lbl_3_rodata_B64 * *(f32*)(f + 0x144) + *(f32*)(f + 8);
    seg.dst.x = *(f32*)f - lbl_3_rodata_B64 * *(f32*)(f + 0x140);
    seg.dst.z = *(f32*)(f + 8) - lbl_3_rodata_B64 * *(f32*)(f + 0x144);
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) == 2) {
        *(f32*)(f + 0x148) = h;
        moved = 1;
        f[0x206] = dir;
        goto done;
    }
turn:
    if (*(u16*)(g_FieldingLogic + 0x148) & 2) {
        side = 3;
        a = *(f32*)(f + 0x6C) - *(f32*)(lbl_3_data_4930 + 0x68);
    } else if (*(u16*)(g_FieldingLogic + 0x148) & 1) {
        side = 4;
        a = *(f32*)(f + 0x6C) + *(f32*)(lbl_3_data_4930 + 0x68);
    } else {
        return;
    }
    getComponentsFromRad(a, &cx, &cz);
    hi = lbl_3_rodata_B64 + *(f32*)(f + 0x70);
    lo = *(f32*)(f + 0x70) - lbl_3_rodata_B64;
    y = -(*(f32*)(f + 0x148) + *(f32*)(f + 0xF8));
    seg.src.x = cx * lo;
    seg.src.z = cz * lo;
    seg.dst.x = cx * hi;
    seg.dst.z = cz * hi;
    seg.dst.y = y;
    seg.src.y = y;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) == 2) {
        *(f32*)f = hit.position.x;
        *(f32*)(f + 8) = hit.position.z;
        if (side != 0) {
            f[0x206] = side;
        }
        moved = 1;
    } else {
        moved = 0;
    }
done:
    if (moved != 0) {
        e = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
        SQRT_L(e);
        *(f32*)(f + 0x140) = hit.normal.x / e;
        *(f32*)(f + 0x144) = hit.normal.z / e;
    }
}
#endif

// .text:0x0002FF2C size:0x18C mapped:0x8066EFC0
void fn_3_2FF2C(int i) {
    u8 st;
    u8* f = g_Fielders + i * 0x268;
    if (*(s16*)(f + 0x1B2) < 0x7FFE) {
        *(s16*)(f + 0x1B2) = *(s16*)(f + 0x1B2) + 1;
    } else {
        *(s16*)(f + 0x1B2) = 0x7FFF;
    }
    st = f[0x205];
    if (st == 5 && *(s16*)(f + 0x1B2) < lbl_3_data_49DC[6]) {
        return;
    }
    if (st == 3 || st == 5) {
        if (st == 3) {
            *(f32*)(f + 0x150) = *(f32*)(f + 0x140) * *(f32*)(lbl_3_data_4930 + 0x4C);
            *(f32*)(f + 0x158) = *(f32*)(f + 0x144) * *(f32*)(lbl_3_data_4930 + 0x4C);
            *(f32*)(f + 0x154) = *(f32*)(lbl_3_data_4930 + 0x54);
        } else {
            *(f32*)(f + 0x150) = *(f32*)(f + 0x140) * *(f32*)(lbl_3_data_4930 + 0x50);
            *(f32*)(f + 0x158) = *(f32*)(f + 0x144) * *(f32*)(lbl_3_data_4930 + 0x50);
            *(f32*)(f + 0x154) = *(f32*)(lbl_3_data_4930 + 0x58);
        }
        f[0x205] = f[0x205] + 1;
    } else {
        *(f32*)(f + 0x150) = *(f32*)(f + 0x150) * *(f32*)(lbl_3_data_4930 + 0x5C);
        *(f32*)(f + 0x158) = *(f32*)(f + 0x158) * *(f32*)(lbl_3_data_4930 + 0x5C);
        *(f32*)(f + 0x154) = *(f32*)(f + 0x154) + *(f32*)(lbl_3_data_4930 + 0x60);
    }
    *(f32*)f = *(f32*)f + *(f32*)(f + 0x150);
    *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x158);
    *(f32*)(f + 0x148) = *(f32*)(f + 0x148) + *(f32*)(f + 0x154);
    if (*(f32*)(f + 0x148) <= 0.0f) {
        *(f32*)(f + 0x148) = 0.0f;
        f[0x205] = 0;
        f[0x1FC] = 1;
    }
    *(f32*)(f + 0x30) = *(f32*)f - *(f32*)(f + 0xD4);
    *(f32*)(f + 0x34) = *(f32*)(f + 8) - *(f32*)(f + 0xD8);
}

// .text:0x000300B8 size:0x15C mapped:0x8066F14C
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    u8 pad0C[0x30 - 0xC];
    f32 vx;
    f32 vz;
    u8 pad38[0xD4 - 0x38];
    f32 px;
    f32 pz;
    u8 padDC[0x128 - 0xDC];
    f32 tx;
    u8 pad12C[4];
    f32 tz;
    u8 pad134[0x148 - 0x134];
    f32 h;
    u8 pad14C[0x154 - 0x14C];
    f32 hv;
    u8 pad158[0x1B2 - 0x158];
    s16 n;
    u8 pad1B4[0x205 - 0x1B4];
    u8 st;
    u8 flag;
    u8 pad207[0x268 - 0x207];
} Fld300B8;
void fn_3_300B8(int i) {
    Fld300B8* f = (Fld300B8*)g_Fielders + i;
    f->flag = 0;
    if (f->st == 1) {
        s16 n = f->n;
        f32 dx = (f->tx - f->x) / (f32)n;
        f32 dz = (f->tz - f->z) / (f32)n;
        f->x += dx;
        f->z += dz;
        f->hv = f->hv - *(f32*)(lbl_3_data_4930 + 0x48);
        f->h = f->h + f->hv;
        if (f->h < 0.0f) {
            f->h = 0.0f;
        }
        f->n = f->n - 1;
        if (f->n <= 0) {
            f->st = 2;
        }
    } else if (f->st == 2) {
        fn_3_2FB9C(i);
        f->n = 0;
    } else if (f->st >= 3) {
        fn_3_2FF2C(i);
        return;
    }
    f->vx = f->x - f->px;
    f->vz = f->z - f->pz;
}


// .text:0x00030214 size:0x350 mapped:0x8066F2A8
// NONMATCHING 90%: float register allocation/scheduling around the wall-normal block after checkCollision
#if NONMATCHING
int fn_3_30214(int i) {
    u8* f = g_Fielders + i * 0x268;
    VecSrcDst seg;
    CollisionStruct hit;
    f32 x, z;
    f32 dx;
    f32 dz;
    f32 d;
    f32 e;
    if ((0.0f == *(f32*)(f + 0x38) && 0.0f == *(f32*)(f + 0x3C)) || *(s16*)(f + 0x19A) < 0) {
        return 0;
    }
    x = *(f32*)f;
    z = *(f32*)(f + 8);
    seg.src.x = x;
    seg.dst.y = lbl_3_rodata_BB4;
    seg.src.y = lbl_3_rodata_BB4;
    seg.src.z = z;
    seg.dst.x = *(f32*)(f + 0x38) * *(f32*)(lbl_3_data_4930 + 0x3C) + x;
    seg.dst.z = *(f32*)(f + 0x3C) * *(f32*)(lbl_3_data_4930 + 0x3C) + z;
    if ((checkCollision(&seg, &hit, 0, 0) & 0x7F) != 2) {
        return 0;
    }
    f[0x205] = 1;
    dz = seg.dst.z - *(f32*)(f + 8);
    dx = seg.dst.x - *(f32*)f;
    d = dx * dx + dz * dz;
    SQRT_L(d);
    e = hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z;
    *(s16*)(f + 0x1B2) = (int)(d / *(f32*)(lbl_3_data_4930 + 0x40)) + 1;
    *(f32*)(f + 0x128) = hit.normal.x * *(f32*)(lbl_3_data_4930 + 0x6C) + hit.position.x;
    *(f32*)(f + 0x130) = hit.normal.z * *(f32*)(lbl_3_data_4930 + 0x6C) + hit.position.z;
    *(f32*)(f + 0x154) = *(f32*)(lbl_3_data_4930 + 0x44);
    *(f32*)(f + 0x148) = 0.0f;
    SQRT_L(e);
    *(f32*)(f + 0x140) = hit.normal.x / e;
    *(f32*)(f + 0x144) = hit.normal.z / e;
    *(f32*)(f + 0x50) = 0.0f;
    return 1;
}
#endif

// .text:0x00030564 size:0xB8 mapped:0x8066F5F8
int fn_3_30564(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (f[0x25E] == 3) {
        f32 k = *(f32*)(lbl_3_data_4930 + 0x38);
        *(f32*)(f + 0x150) = *(f32*)(f + 0x150) * k;
        *(f32*)(f + 0x158) = *(f32*)(f + 0x158) * k;
        *(f32*)(f + 0x0) = *(f32*)(f + 0x0) + *(f32*)(f + 0x150);
        *(f32*)(f + 0x8) = *(f32*)(f + 0x8) + *(f32*)(f + 0x158);
        *(f32*)(f + 0x14) = *(f32*)(f + 0x0);
        *(f32*)(f + 0x1C) = *(f32*)(f + 0x8);
        f[0x1F0] = 1;
    } else if (f[0x25E] == 4) {
        *(f32*)(f + 0x50) = lbl_3_rodata_1498;
        f[0x25F] = f[0x25F] - 1;
        if (f[0x25F] == 0) {
            f[0x25E] = 0;
        }
    }
    return 1;
}

// .text:0x0003061C size:0x29C mapped:0x8066F6B0
// NONMATCHING 85%: original keeps the 0.3 limit in f30 across the loop; ours keeps a table address instead (regalloc/hoisting)
#if NONMATCHING
void fn_3_3061C(void) {
    u8* f = g_Fielders;
    f32* home = lbl_3_data_450C[0];
    int i;
    f32 dx;
    f32 dz;
    f32 d;
    for (i = 0; i < 9; i++) {
        if (f[0x1F1] == 0) {
            f[0x1F1] = 1;
            *(f32*)f = *(f32*)(lbl_3_data_4290 + g_d_GameSettings[9] * 0x10 + (*(int*)(g_GameLogic + 0x10) ^ 1) * 8);
            *(f32*)(f + 4) = 0.0f;
            *(f32*)(f + 8) = *(f32*)(lbl_3_data_4290 + g_d_GameSettings[9] * 0x10 + (*(int*)(g_GameLogic + 0x10) ^ 1) * 8 + 4);
            *(f32*)(f + 0x14) = home[0];
            *(f32*)(f + 0x1C) = home[1];
            *(s16*)(f + 0x1A6) = RandomInt_Game(30);
        }
        dz = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
        dx = *(f32*)(f + 0x14) - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < lbl_3_rodata_BB8 || *(s16*)(f + 0x1A6) > *(u16*)(g_GameLogic + 0xFC)) {
            *(f32*)(f + 0x30) = 0.0f;
            *(f32*)(f + 0x34) = 0.0f;
            *(f32*)(f + 0x50) = 0.0f;
        } else {
            *(f32*)(f + 0x30) = lbl_3_rodata_B74 * (dx / d) - lbl_3_rodata_B48;
            *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
            *(f32*)(f + 0x34) = lbl_3_rodata_B74 * (dz / d) - lbl_3_rodata_B48;
            *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
            *(f32*)(f + 0x50) = lbl_3_rodata_B74;
        }
        home += 2;
        f += 0x268;
    }
    fn_3_313B0();
    g_FieldingLogic[0x118] = 0;
    *(s16*)(g_Ball + 0x1B66) = 100;
}
#endif

// .text:0x000308B8 size:0x1A0 mapped:0x8066F94C
void fn_3_308B8(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    *(f32*)(f + 0x14) = x;
    *(f32*)(f + 0x1C) = z;
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
        return;
    }
    *(f32*)(f + 0x64) = atan2(dz, dx);
    d = dx * dx + dz * dz;
    SQRT_L(d);
    *(f32*)(f + 0x68) = d;
    f[0x1D9] = 1;
}

// .text:0x00030A58 size:0x31C mapped:0x8066FAEC
void fn_3_30A58(void) {
    int i;
    u8* f;
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;
    f32 d;
    for (i = 2; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        fn_3_58F58(i, &x, &z);
        d = (*(f32*)f - x) * (*(f32*)f - x) + (*(f32*)(f + 8) - z) * (*(f32*)(f + 8) - z);
        SQRT_L(d);
        if (d < 0.1f) {
            x = *(f32*)f;
            z = *(f32*)(f + 8);
        }
        *(f32*)(f + 0x14) = x;
        *(f32*)(f + 0x1C) = z;
        dx = x - *(f32*)f;
        dz = z - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
            f[0x1D9] = 1;
        }
    }
}

// .text:0x00030D74 size:0x63C mapped:0x8066FE08
// NONMATCHING 88%: register allocation (loop pointers/counters, the x/z out-params' stack slots); first loop is fn_3_30A58's body inlined
#if NONMATCHING
void fn_3_30D74(void) {
    int i;
    u8* f;
    f32 x;
    f32 z;
    f32 dz;
    f32 dx;
    f32 d;
    int moving;
    if (lbl_3_common_bss_34C90[0x1D5] != 0) {
        return;
    }
    for (i = 2; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        fn_3_58F58(i, &x, &z);
        d = (*(f32*)f - x) * (*(f32*)f - x) + (*(f32*)(f + 8) - z) * (*(f32*)(f + 8) - z);
        SQRT_L(d);
        if (d < 0.1f) {
            x = *(f32*)f;
            z = *(f32*)(f + 8);
        }
        *(f32*)(f + 0x14) = x;
        *(f32*)(f + 0x1C) = z;
        dx = x - *(f32*)f;
        dz = z - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
            f[0x1D9] = 1;
        }
    }
    for (i = 2; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        moving = 0;
        if (*(f32*)(f + 0x68) > lbl_3_rodata_BBC) {
            moving = 1;
        } else if (*(f32*)(f + 0x50) >= lbl_3_rodata_B24 && *(f32*)(f + 0x68) > lbl_3_rodata_B7C) {
            moving = 1;
        }
        if (moving != 0) {
            if (*(s16*)(g_Pitcher + 0x11E) <= 0) {
                *(f32*)(f + 0x50) = lbl_3_rodata_B24;
            } else if (g_Batter[0x8F] >= 1 && g_Batter[0x8F] <= 3 && (i == 2 || i == 4)) {
                *(f32*)(f + 0x50) = *(f32*)(f + 0x50) + *(f32*)(f + 0x5C);
                if (*(f32*)(f + 0x50) > *(f32*)(f + 0x58)) {
                    *(f32*)(f + 0x50) = *(f32*)(f + 0x58);
                }
            } else if (((i == 3 && g_Batter[0x7B] == 0) || (i == 5 && g_Batter[0x7B] != 0)) && g_Runners[0x277] != 0 &&
                       g_Runners[0x2A1] != 0) {
                *(f32*)(f + 0x50) = *(f32*)(f + 0x50) + *(f32*)(f + 0x5C);
                if (*(f32*)(f + 0x50) > *(f32*)(f + 0x58)) {
                    *(f32*)(f + 0x50) = *(f32*)(f + 0x58);
                }
            } else if (*(s16*)(g_Pitcher + 0x11E) < 60) {
                *(s16*)(f + 0x17E) = 60 - *(s16*)(g_Pitcher + 0x11E);
                *(f32*)(f + 0x50) = *(f32*)(f + 0x68) / *(s16*)(f + 0x17E);
            } else {
                *(s16*)(f + 0x17E) = 0;
                *(f32*)(f + 0x50) = 0.0f;
            }
            *(f32*)(f + 0x68) = *(f32*)(f + 0x68) - *(f32*)(f + 0x50);
            if (*(f32*)(f + 0x50) <= 0.0f) {
                *(f32*)(f + 0x50) = 0.0f;
                *(s16*)(f + 0x17E) = -1;
            } else if (*(f32*)(f + 0x68) < 0.0f) {
                *(f32*)(f + 0x30) = *(f32*)(f + 0x14) - *(f32*)f;
                *(f32*)(f + 0x34) = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
                *(f32*)f = *(f32*)(f + 0x14);
                *(f32*)(f + 8) = *(f32*)(f + 0x1C);
                *(f32*)(f + 0x68) = 0.0f;
                *(s16*)(f + 0x17E) = 0;
            } else {
                *(f32*)(f + 0x30) = *(f32*)(f + 0x50) * (f32)cos(*(f32*)(f + 0x64));
                *(f32*)(f + 0x34) = *(f32*)(f + 0x50) * (f32)sin(*(f32*)(f + 0x64));
                *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
                *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
                *(s16*)(f + 0x17E) = *(f32*)(f + 0x68) / *(f32*)(f + 0x50);
            }
            f[0x1E3] = 0;
        } else {
            *(f32*)(f + 0x30) = *(f32*)(f + 0x14) - *(f32*)f;
            *(f32*)(f + 0x34) = *(f32*)(f + 0x1C) - *(f32*)(f + 8);
            *(f32*)f = *(f32*)(f + 0x14);
            *(f32*)(f + 8) = *(f32*)(f + 0x1C);
            *(f32*)(f + 0x68) = 0.0f;
            *(f32*)(f + 0x50) = 0.0f;
            f[0x1E3] = 1;
            *(s16*)(f + 0x17E) = -1;
        }
    }
    *(f32*)g_Fielders = *(f32*)(g_Pitcher + 0x8C);
    *(f32*)(g_Fielders + 8) = *(f32*)(g_Pitcher + 0x90);
}
#endif

// .text:0x000313B0 size:0x1E4 mapped:0x80670444
extern u8 lbl_3_common_bss_34C90[];
extern u8 g_Pitcher[];
extern f32 lbl_3_rodata_BC0;
extern void fn_3_53F48(void);
extern void fn_3_544B8(void);
void fn_3_313B0(void) {
    int i;
    u8* f;
    int k;
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (g_d_GameSettings[0x11] != 0) {
            for (k = 0; k < 4; k++) {
                if (*(s8*)(g_Minigame + 0x18F8 + k) == i) {
                    break;
                }
            }
            if (k >= 4) {
                continue;
            }
        }
        if (*(f32*)(f + 0x50) > 0.0f) {
            if (lbl_3_common_bss_34C90[0x1D5] == 0) {
                *(f32*)(f + 0x48) = atan2(*(f32*)(f + 0x34), *(f32*)(f + 0x30));
            }
        } else if (*(s16*)(g_Pitcher + 0x11E) <= 0 && g_Runners[0x277] == 1 && i == 2 && g_d_GameSettings[0x11] == 0) {
            *(f32*)(f + 0x48) = lbl_3_rodata_BC0;
        } else {
            *(f32*)(f + 0x48) = atan2(-*(f32*)(f + 8), -*(f32*)f);
        }
        if (0.0f != *(f32*)(f + 0x30) || 0.0f != *(f32*)(f + 0x34)) {
            *(f32*)(f + 0x64) = atan2(*(f32*)(f + 0x34), *(f32*)(f + 0x30));
            *(s16*)(f + 0x19A) = radToShortAngle(*(f32*)(f + 0x64));
        } else {
            *(f32*)(f + 0x64) = 0.0f;
            *(s16*)(f + 0x19A) = -1;
        }
        if (g_d_GameSettings[0x11] != 0) {
            g_Minigame[0x1923] = i;
            fn_3_544B8();
        }
    }
    if (g_d_GameSettings[0x11] != 0) {
        fn_3_53F48();
        return;
    }
    fn_3_544B8();
}

// .text:0x00031594 size:0xE4 mapped:0x80670628
void fn_3_31594(void) {
    u8* in;
    s16* p;
    int i;
    in = g_Controls + ((int*)(g_GameLogic + 0xEC))[*(int*)(g_GameLogic + 8)] * 0x10;
    p = &lbl_3_bss_170 + 0x13;
    for (i = 0x13; i != 0; i--) {
        p[0] = p[-1];
        p--;
    }
    if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0) {
        in = g_Practice + *(int*)(g_GameLogic + 8) * 0x10;
    }
    *(u16*)(g_FieldingLogic + 0x148) = *(u16*)(in + 4);
    *(u16*)(g_FieldingLogic + 0x14A) = *(u16*)(in + 6);
    *(u16*)(g_FieldingLogic + 0x14C) = *(u16*)(in + 8);
    for (i = 0; i < 9; i++) {
        fn_3_55EEC(i);
    }
    fn_3_30D74();
    fn_3_313B0();
}

// .text:0x00031678 size:0x3C4 mapped:0x8067070C
// NONMATCHING 90%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_31678(void) {
    int i;
    *(s16*)(g_Fielders + 0x18C) = 0;
    SetFielderAct(0, 1, 8);
    *(s16*)(g_FieldingLogic + 0xD0) = 0;
    if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142] != 0) {
        SetFielderAct(1, 0x12, 0x90);
    } else {
        SetFielderAct(1, 0xF, 0x78);
    }
    *(s16*)(g_Fielders + 2 * 0x268 + 0x18C) = 1;
    SetFielderAct(2, 1, 8);
    *(s16*)(g_FieldingLogic + 0xD2) = 2;
    *(s16*)(g_Fielders + 4 * 0x268 + 0x18C) = 3;
    SetFielderAct(4, 1, 8);
    *(s16*)(g_FieldingLogic + 0xD6) = 4;
    if ((f32)__abs(*(s16*)(g_Fielders + 3 * 0x268 + 0x182) - 0x400) < (f32)__abs(*(s16*)(g_Fielders + 5 * 0x268 + 0x182) - 0x400)) {
        *(s16*)(g_Fielders + 3 * 0x268 + 0x18C) = 2;
        SetFielderAct(3, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD4) = 3;
        SetFielderAct(5, 0, 0);
    } else {
        *(s16*)(g_Fielders + 5 * 0x268 + 0x18C) = 2;
        SetFielderAct(5, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD4) = 5;
        SetFielderAct(3, 0, 0);
    }
    for (i = 0; i < 9; i++) {
        if (*(s16*)(g_Fielders + i * 0x268 + 0x18C) >= 0 && *(s16*)(g_Fielders + i * 0x268 + 0x18C) <= 3) {
            g_Fielders[i * 0x268 + 0x1D7] = 1;
        }
    }
    fn_3_49F40(6, 5);
    fn_3_49F40(7, 1);
    fn_3_49F40(8, 4);
}
#endif

// .text:0x00031A3C size:0x214 mapped:0x80670AD0
extern f32 lbl_3_rodata_BC4;
extern f32 lbl_3_rodata_BC8;
void fn_3_31A3C(void) {
    int i;
    u8* f;
    int v;
    f32 d;
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (i == 1) {
            *(s16*)(f + 0x182) = 0x400;
        } else if (0.0f == *(f32*)f) {
            *(s16*)(f + 0x182) = 0x400;
        } else {
            v = (int)(lbl_3_rodata_BC4 * (f32)atan2(*(f32*)(f + 8), *(f32*)f) / lbl_3_rodata_BC8);
            if (v < 0) {
                v += 0x800;
            }
            *(s16*)(f + 0x182) = v;
        }
        d = *(f32*)f * *(f32*)f + *(f32*)(f + 8) * *(f32*)(f + 8);
        SQRT_L(d);
        *(f32*)(f + 0x70) = d;
    }
    fn_3_31678();
    *(f32*)(g_Ball + 0x324) = 0.0f;
    *(f32*)(g_Ball + 0x328) = 0.0f;
    *(f32*)(g_Ball + 0x32C) = 0.0f;
    g_Ball[0x1BC9] = 3;
    *(s16*)(g_Ball + 0x1B7A) = 2;
    *(s16*)(g_Ball + 0x1B7E) = -1;
    *(s16*)(g_Ball + 0x1B8A) = -1;
    g_Ball[0x1BCA] = 0;
    g_Ball[0x1BE1] = 0;
}

// .text:0x00031C50 size:0x440 mapped:0x80670CE4
// NONMATCHING 90%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_31C50(void) {
    int i;
    if (*(s16*)(g_Pitcher + 0x12E) == 5) {
        *(s16*)(g_Fielders + 0x18C) = 5;
        *(s16*)(g_FieldingLogic + 0xD8) = 0;
        SetFielderAct(0, 0xE, 0x70);
        *(s16*)(g_Fielders + 1 * 0x268 + 0x18C) = 0;
        SetFielderAct(1, 0xA, 0x50);
        *(s16*)(g_FieldingLogic + 0xD0) = 1;
    } else {
        SetFielderAct(0, 0xA, 0x50);
        *(s16*)(g_Fielders + 1 * 0x268 + 0x18C) = 0;
        SetFielderAct(1, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD0) = 1;
    }
    *(s16*)(g_Fielders + 2 * 0x268 + 0x18C) = 1;
    SetFielderAct(2, 1, 8);
    *(s16*)(g_FieldingLogic + 0xD2) = 2;
    *(s16*)(g_Fielders + 4 * 0x268 + 0x18C) = 3;
    SetFielderAct(4, 1, 8);
    *(s16*)(g_FieldingLogic + 0xD6) = 4;
    if ((f32)__abs(*(s16*)(g_Fielders + 3 * 0x268 + 0x182) - 0x400) < (f32)__abs(*(s16*)(g_Fielders + 5 * 0x268 + 0x182) - 0x400)) {
        *(s16*)(g_Fielders + 3 * 0x268 + 0x18C) = 2;
        SetFielderAct(3, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD4) = 3;
        SetFielderAct(5, 0, 0);
    } else {
        *(s16*)(g_Fielders + 5 * 0x268 + 0x18C) = 2;
        SetFielderAct(5, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD4) = 5;
        SetFielderAct(3, 0, 0);
    }
    for (i = 0; i < 9; i++) {
        if (*(s16*)(g_Fielders + i * 0x268 + 0x18C) >= 0 && *(s16*)(g_Fielders + i * 0x268 + 0x18C) <= 3) {
            g_Fielders[i * 0x268 + 0x1D7] = 1;
        }
    }
    fn_3_49F40(6, 5);
    fn_3_49F40(7, 1);
    fn_3_49F40(8, 4);
}
#endif

// .text:0x00032090 size:0x314 mapped:0x80671124
void fn_3_32090(void) {
    int i;
    u8* f;
    int v;
    f32 d;
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (i == 1) {
            *(s16*)(f + 0x182) = 0x400;
        } else if (0.0f == *(f32*)f) {
            *(s16*)(f + 0x182) = 0x400;
        } else {
            v = (int)(lbl_3_rodata_BC4 * (f32)atan2(*(f32*)(f + 8), *(f32*)f) / lbl_3_rodata_BC8);
            if (v < 0) {
                v += 0x800;
            }
            *(s16*)(f + 0x182) = v;
        }
        d = *(f32*)f * *(f32*)f + *(f32*)(f + 8) * *(f32*)(f + 8);
        SQRT_L(d);
        *(f32*)(f + 0x70) = d;
    }
    fn_3_31C50();
    *(f32*)(g_Ball + 0x318) = 0.0f;
    *(f32*)(g_Ball + 0x31C) = 0.0f;
    *(f32*)(g_Ball + 0x320) = 0.0f;
    *(f32*)(g_Ball + 0x324) = 0.0f;
    *(f32*)(g_Ball + 0x328) = 0.0f;
    *(f32*)(g_Ball + 0x32C) = 0.0f;
    g_Ball[0x1BC9] = 1;
    *(s16*)(g_Ball + 0x1B7A) = 2;
    *(s16*)(g_Ball + 0x1B7E) = 0;
    *(s16*)(g_Ball + 0x1B8A) = -1;
    g_Ball[0x1BCA] = 0;
    g_Ball[0x1BE1] = 0;
    if (g_FieldingLogic[0x107] == 1 || g_FieldingLogic[0x107] == 2) {
        g_Ball[0x1BD7] = 1;
    }
    if (*(s16*)(g_Pitcher + 0x12E) == 5) {
        *(f32*)(g_Ball + 0) = *(f32*)(g_Fielders + 0x268);
        *(f32*)(g_Ball + 4) = *(f32*)(g_Fielders + 0x26C);
        *(f32*)(g_Ball + 8) = *(f32*)(g_Fielders + 0x270);
        *(s16*)(g_Ball + 0x1B78) = 1;
        return;
    }
    *(f32*)(g_Ball + 0) = *(f32*)(g_Fielders + 0);
    *(f32*)(g_Ball + 4) = *(f32*)(g_Fielders + 4);
    *(f32*)(g_Ball + 8) = *(f32*)(g_Fielders + 8);
    *(s16*)(g_Ball + 0x1B78) = 0;
    if (*(s16*)(g_Pitcher + 0x12E) >= 1 && *(s16*)(g_Pitcher + 0x12E) <= 3) {
        *(s16*)(g_FieldingLogic + 0xC4) = *(s16*)(g_Pitcher + 0x12E);
    }
    v = checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(g_Fielders + 0x178), 5);
    g_Fielders[0x215] = lbl_3_data_4900[v][2];
}

// .text:0x000323A4 size:0x450 mapped:0x80671438
void fn_3_323A4(void) {
    s16 n;
    s16 t3;
    s16 t2;
    f32 d;
    if (g_Fielders[0x268 + 0x1DA] == 0) {
        if (g_Runners[0x51F] == 1 && g_Runners[0x533] == 1 && *(f32*)(g_Runners + 0x460) >= lbl_3_rodata_BCC &&
            (n = *(s16*)(g_Fielders + 0x268 + 0x186)) > 0) {
            d = *(f32*)(g_Ball + n * 16 + 0x354) * *(f32*)(g_Ball + n * 16 + 0x354) +
                *(f32*)(g_Ball + n * 16 + 0x35C) * *(f32*)(g_Ball + n * 16 + 0x35C);
            SQRT_L(d);
            if (d < lbl_3_rodata_B64) {
                *(s16*)(g_FieldingLogic + 0xB0) = 1;
                *(s16*)(g_FieldingLogic + 0xB2) = 0;
            } else {
                *(s16*)(g_FieldingLogic + 0xB0) = 0;
            }
        } else {
            *(s16*)(g_FieldingLogic + 0xB0) = 1;
            *(s16*)(g_FieldingLogic + 0xB2) = 0;
        }
    } else {
        *(s16*)(g_FieldingLogic + 0xB0) = 0;
    }
    if (*(s16*)(g_Ball + 0x1B9C) < 0x400) {
        t3 = *(s16*)(g_Fielders + 3 * 0x268 + 0x186);
        t2 = *(s16*)(g_Fielders + 2 * 0x268 + 0x186);
        if (t3 - 15 < t2) {
            if (*(s16*)(g_Fielders + 0x186) - t3 < 120) {
                *(s16*)(g_FieldingLogic + 0xB2) = 3;
            } else {
                goto def2;
            }
        } else if (*(f32*)(g_Ball + t2 * 16 + 0x35C) < ((f32*)lbl_3_data_4444)[3]) {
            if (*(s16*)(g_Fielders + 0x186) - t2 < 80) {
                *(s16*)(g_FieldingLogic + 0xB2) = 2;
            } else {
                goto def2;
            }
        } else if (*(s16*)(g_Fielders + 0x186) - t3 < 120) {
            *(s16*)(g_FieldingLogic + 0xB2) = 3;
        } else {
        def2:
            *(s16*)(g_FieldingLogic + 0xB2) = 2;
        }
    } else {
        t3 = *(s16*)(g_Fielders + 5 * 0x268 + 0x186);
        t2 = *(s16*)(g_Fielders + 4 * 0x268 + 0x186);
        if (t3 - 15 < t2) {
            if (*(s16*)(g_Fielders + 0x186) - t3 < 120) {
                *(s16*)(g_FieldingLogic + 0xB2) = 5;
            } else {
                goto def4;
            }
        } else if (*(f32*)(g_Ball + t2 * 16 + 0x35C) < ((f32*)lbl_3_data_4444)[3]) {
            if ((g_Runners[0x3CB] != 1 || t2 <= 0) && *(s16*)(g_Fielders + 0x186) - t2 < 80) {
                *(s16*)(g_FieldingLogic + 0xB2) = 4;
            } else {
                goto def4;
            }
        } else if (*(s16*)(g_Fielders + 0x186) - t3 < 120) {
            *(s16*)(g_FieldingLogic + 0xB2) = 5;
        } else {
        def4:
            *(s16*)(g_FieldingLogic + 0xB2) = 4;
        }
    }
    SetFielderAct(*(s16*)(g_FieldingLogic + 0xB0), 0x15, 0xA8);
    if (*(s16*)(g_FieldingLogic + 0xB2) >= 0) {
        SetFielderAct(*(s16*)(g_FieldingLogic + 0xB2), 0x16, 0xB0);
    }
}

// .text:0x000327F4 size:0x1C mapped:0x80671888

s32 fn_3_327F4(void) {
    return g_Ball[0x1BC4] == 1;
}

// .text:0x00032810 size:0x194 mapped:0x806718A4
// NONMATCHING 98%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_32810(void) {
    SetFielderAct(0, 0x15, 0xA8);
    *(s16*)(g_FieldingLogic + 0xB0) = 0;
    if (*(s16*)(g_Ball + 0x1B9C) < 0x400) {
        *(s16*)(g_FieldingLogic + 0xB2) = 3;
    } else {
        *(s16*)(g_FieldingLogic + 0xB2) = 5;
    }
    SetFielderAct(3, 0x16, 0xB0);
    SetFielderAct(5, 0x16, 0xB0);
    g_FieldingLogic[0x13A] = 1;
    SetFielderAct(7, 0x17, 0xB8);
    *(s16*)(g_FieldingLogic + 0xB4) = 7;
    g_FieldingLogic[0x139] = 1;
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

// .text:0x000329A4 size:0x6E4 mapped:0x80671A38
// NONMATCHING 90%: registers only; the known SetFielderAct table-value/state r0 swap (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_329A4(void) {
    s16 ang = *(s16*)(g_Ball + 0x1B9C);
    if (*(s16*)(g_Ball + 0x1B9A) >= 0x400 && *(s16*)(g_Ball + 0x1B9A) <= 0xC00) {
        ang += 0x800;
        if (ang > 0x1000) {
            ang -= 0x1000;
        }
    }
    if (ang >= 0xE00) {
        *(s16*)(g_FieldingLogic + 0xB0) = 1;
        SetFielderAct(2, 0x10, 0x80);
    } else if (ang >= 0xA00) {
        *(s16*)(g_FieldingLogic + 0xB0) = 1;
    } else if (ang >= 0x800) {
        *(s16*)(g_FieldingLogic + 0xB0) = 1;
        SetFielderAct(4, 0x10, 0x80);
    } else if (ang >= 0x400) {
        if (*(s16*)(g_Ball + 0x1B9A) < 0x40) {
            *(s16*)(g_FieldingLogic + 0xB0) = 4;
            SetFielderAct(6, 0x10, 0x80);
        } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_BA0) {
            *(s16*)(g_FieldingLogic + 0xB0) = 1;
            SetFielderAct(4, 0x10, 0x80);
            SetFielderAct(6, 0x10, 0x80);
        } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_B9C) {
            *(s16*)(g_FieldingLogic + 0xB0) = 4;
            SetFielderAct(5, 0x10, 0x80);
            SetFielderAct(6, 0x10, 0x80);
        } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_BD0) {
            *(s16*)(g_FieldingLogic + 0xB0) = 5;
            SetFielderAct(4, 0x10, 0x80);
            SetFielderAct(6, 0x10, 0x80);
        } else {
            *(s16*)(g_FieldingLogic + 0xB0) = 6;
            SetFielderAct(5, 0x10, 0x80);
        }
    } else if (*(s16*)(g_Ball + 0x1B9A) < 0x40) {
        *(s16*)(g_FieldingLogic + 0xB0) = 2;
        SetFielderAct(8, 0x10, 0x80);
    } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_BA0) {
        *(s16*)(g_FieldingLogic + 0xB0) = 1;
        SetFielderAct(2, 0x10, 0x80);
        SetFielderAct(8, 0x10, 0x80);
    } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_B9C) {
        *(s16*)(g_FieldingLogic + 0xB0) = 2;
        SetFielderAct(3, 0x10, 0x80);
        SetFielderAct(8, 0x10, 0x80);
    } else {
        /* note: the original has no else here, so the < 40 case is overwritten below */
        if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_BD0) {
            *(s16*)(g_FieldingLogic + 0xB0) = 3;
            SetFielderAct(2, 0x10, 0x80);
            SetFielderAct(8, 0x10, 0x80);
        }
        *(s16*)(g_FieldingLogic + 0xB0) = 8;
        SetFielderAct(3, 0x10, 0x80);
    }
    SetFielderAct(*(s16*)(g_FieldingLogic + 0xB0), 0x15, 0xA8);
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

// .text:0x00033088 size:0x3D0 mapped:0x8067211C
// NONMATCHING 94%: distance sums unfused (fmuls+fadds) in the original; g_Fielders base kept in r31 there
#if NONMATCHING
void fn_3_33088(void) {
    u8* c;
    s16 ang = fn_3_9FB8C(*(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
    s32 other = 6;
    u8* o;
    f32 dc;
    f32 dother;
    f32 dx;
    f32 dz;
    c = g_Fielders + 7 * 0x268;
    if (ang < *(s16*)(c + 0x182)) {
        other = 8;
    }
    o = g_Fielders + other * 0x268;
    if (c[0x1DD] == 1 && o[0x1DD] == 1) {
        if (c[0x1DB] == 0 && o[0x1DB] == 0 && *(s16*)(c + 0x186) == *(s16*)(o + 0x186)) {
            dx = ((f32*)(g_Ball + 0x354))[*(s16*)(c + 0x186) * 4] - *(f32*)c;
            dz = ((f32*)(g_Ball + 0x35C))[*(s16*)(c + 0x186) * 4] - *(f32*)(c + 8);
            dc = dx * dx + dz * dz;
            SQRT_L(dc);
            dx = ((f32*)(g_Ball + 0x354))[*(s16*)(o + 0x186) * 4] - *(f32*)o;
            dz = ((f32*)(g_Ball + 0x35C))[*(s16*)(o + 0x186) * 4] - *(f32*)(o + 8);
            dother = dx * dx + dz * dz;
            SQRT_L(dother);
            if (dc < dother) {
                *(s16*)(g_FieldingLogic + 0xB2) = 7;
            } else {
                *(s16*)(g_FieldingLogic + 0xB2) = other;
            }
        } else if (*(s16*)(c + 0x186) <= *(s16*)(o + 0x186)) {
            *(s16*)(g_FieldingLogic + 0xB2) = 7;
        } else {
            *(s16*)(g_FieldingLogic + 0xB2) = other;
        }
    } else if (c[0x1DD] == 1) {
        *(s16*)(g_FieldingLogic + 0xB2) = 7;
    } else if (o[0x1DD] == 1) {
        *(s16*)(g_FieldingLogic + 0xB2) = other;
    } else if (__abs(ang - *(s16*)(c + 0x182)) < __abs(ang - *(s16*)(o + 0x182)) + 0x60) {
        *(s16*)(g_FieldingLogic + 0xB2) = 7;
    } else {
        *(s16*)(g_FieldingLogic + 0xB2) = other;
    }
}
#endif

// .text:0x00033458 size:0x94 mapped:0x806724EC
void fn_3_33458(void) {
    u8* f;
    s16 i;
    fn_3_334EC(1);
    fn_3_33088();
    i = *(s16*)(g_FieldingLogic + 0xB2);
    f = g_Fielders + i * 0x268;
    if (i != -1) {
        f[0x1D3] = 0x16;
        if (*(int*)(lbl_3_data_3C40 + 0xB0) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0xB0);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

// .text:0x000334EC size:0x8B0 mapped:0x80672580
#define FLD_HANG(n) (*(s16*)(g_Fielders + (n) * 0x268 + 0x182))
// NONMATCHING 98%: distance sums unfused (fmuls+fadds) in the original; second-pick local typed s16 there; register numbering
#if NONMATCHING
void fn_3_334EC(int a) {
    s32 sel;
    s32 j;
    s32 w;
    s32 second;
    f32 best;
    f32 d;
    f32 dx;
    f32 dz;
    u8* f;
    if (g_Ball[0x1BC4] == 1) {
        fn_3_323A4();
    } else if (*(f32*)(g_Ball + 0x19D4) >= lbl_3_rodata_B64 && a == 0) {
        dx = *(f32*)g_Fielders - *(f32*)(g_Ball + 0x348);
        dz = *(f32*)(g_Fielders + 8) - *(f32*)(g_Ball + 0x34C);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        best = d + lbl_3_rodata_B78;
        sel = 0;
        f = g_Fielders + 0x268;
        for (j = 1; j < 6; j++, f += 0x268) {
            dx = *(f32*)f - *(f32*)(g_Ball + 0x348);
            dz = *(f32*)(f + 8) - *(f32*)(g_Ball + 0x34C);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (j == 3 || j == 5) {
                d -= lbl_3_rodata_B78;
            }
            if (d < best) {
                best = d;
                sel = j;
            }
        }
        *(s16*)(g_FieldingLogic + 0xB0) = sel;
        SetFielderAct(sel, 0x15, 0xA8);
        if ((*(s16*)(g_FieldingLogic + 0xB0) == 3 || *(s16*)(g_FieldingLogic + 0xB0) == 5) &&
            *(s16*)(g_Ball + 0x1B84) >= 0x3B8 && *(s16*)(g_Ball + 0x1B84) <= 0x448) {
            if (*(s16*)(g_FieldingLogic + 0xB0) == 3) {
                *(s16*)(g_FieldingLogic + 0xB2) = 5;
            } else {
                *(s16*)(g_FieldingLogic + 0xB2) = 3;
            }
            g_FieldingLogic[0x13A] = 1;
        }
    } else {
        w = 0x8C - *(s16*)(g_Ball + 0x1B9E);
        if (w < 0) {
            w = 0;
        }
        if (w > 0x40) {
            w = 0x40;
        }
        if (*(s16*)(g_Ball + 0x1B9C) >= 0x3A8 - w && *(s16*)(g_Ball + 0x1B9C) < w + 0x458 && a == 0) {
            *(s16*)(g_FieldingLogic + 0xB0) = 0;
            if (*(s16*)(g_Ball + 0x1B9C) < FLD_HANG(3) + (FLD_HANG(5) - FLD_HANG(3)) / 2) {
                *(s16*)(g_FieldingLogic + 0xB2) = 3;
            } else {
                *(s16*)(g_FieldingLogic + 0xB2) = 5;
            }
            if (*(s16*)(g_Ball + 0x1B84) >= 0x3B8 && *(s16*)(g_Ball + 0x1B84) <= 0x448) {
                g_FieldingLogic[0x13A] = 1;
                if (*(s16*)(g_FieldingLogic + 0xB2) == 3) {
                    SetFielderAct(5, 0x16, 0xB0);
                } else {
                    SetFielderAct(3, 0x16, 0xB0);
                }
            }
        } else if (*(s16*)(g_Ball + 0x1B9C) < FLD_HANG(2) + (FLD_HANG(3) - FLD_HANG(2)) / 7) {
            *(s16*)(g_FieldingLogic + 0xB0) = 2;
        } else if (*(s16*)(g_Ball + 0x1B9C) < FLD_HANG(2) + (FLD_HANG(3) - FLD_HANG(2)) * 2 / 5) {
            *(s16*)(g_FieldingLogic + 0xB0) = 2;
            *(s16*)(g_FieldingLogic + 0xB2) = 3;
            SetFielderAct(3, 0x16, 0xB0);
        } else if (*(s16*)(g_Ball + 0x1B9C) < FLD_HANG(3) + (FLD_HANG(5) - FLD_HANG(3)) / 2) {
            *(s16*)(g_FieldingLogic + 0xB0) = 3;
        } else if (*(s16*)(g_Ball + 0x1B9C) < FLD_HANG(5) + (FLD_HANG(4) - FLD_HANG(5)) * 3 / 5) {
            *(s16*)(g_FieldingLogic + 0xB0) = 5;
        } else if (*(s16*)(g_Ball + 0x1B9C) < FLD_HANG(4) - (FLD_HANG(4) - FLD_HANG(5)) / 5) {
            *(s16*)(g_FieldingLogic + 0xB0) = 4;
            *(s16*)(g_FieldingLogic + 0xB2) = 5;
            SetFielderAct(5, 0x16, 0xB0);
        } else {
            *(s16*)(g_FieldingLogic + 0xB0) = 4;
        }
    }
    SetFielderAct(*(s16*)(g_FieldingLogic + 0xB0), 0x15, 0xA8);
    if (a != 0) {
        return;
    }
    second = *(s16*)(g_FieldingLogic + 0xB2);
    if (second < 0) {
        fn_3_33088();
        SetFielderAct(*(s16*)(g_FieldingLogic + 0xB2), 0x16, 0xB0);
    } else {
        fn_3_33088();
        *(s16*)(g_FieldingLogic + 0xB4) = *(s16*)(g_FieldingLogic + 0xB2);
        *(s16*)(g_FieldingLogic + 0xB2) = second;
        SetFielderAct(second, 0x16, 0xB0);
        SetFielderAct(*(s16*)(g_FieldingLogic + 0xB4), 0x17, 0xB8);
        g_FieldingLogic[0x139] = 1;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif
#undef FLD_HANG

// .text:0x00033D9C size:0x34 mapped:0x80672E30
void fn_3_33D9C(void) {
    fn_3_49F40(6, 7);
    fn_3_49F40(8, 6);
}

extern f32 lbl_3_rodata_BD0;
extern f32 lbl_3_rodata_BD4;
// .text:0x00033DD0 size:0x418 mapped:0x80672E64
// NONMATCHING 97%: 10.0f const load scheduled after the operands in the s7==0 branch; *first=7 store order in the 0x1BBF branch
#if NONMATCHING
void fn_3_33DD0(s32* first, s32* second) {
    u8* fl = g_Fielders;
    s32 other = 6;
    s16 ang;
    u8* f;
    s32 s7;
    s32 so;
    s32 close;
    f32 d;
    *second = -1;
    ang = fn_3_9FB8C(*(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
    if (ang > *(s16*)(g_Fielders + 6 * 0x268 + 0x182)) {
        *first = 6;
        return;
    }
    if (ang < *(s16*)(g_Fielders + 8 * 0x268 + 0x182)) {
        *first = 8;
        return;
    }
    if (ang < *(s16*)(g_Fielders + 7 * 0x268 + 0x182)) {
        other = 8;
    }
    so = 10;
    f = g_Fielders + other * 0x268;
    s7 = 10;
    if (fl[7 * 0x268 + 0x1DB] == 0) {
        s7 = 0;
    } else if (fl[7 * 0x268 + 0x1DD] == 1) {
        s7 = 1;
    } else if (fl[7 * 0x268 + 0x1DD] == 2) {
        s7 = 2;
    } else if (fl[7 * 0x268 + 0x1DD] == 3) {
        s7 = 3;
    }
    if (f[0x1DB] == 0) {
        so = 0;
    } else if (f[0x1DD] == 1) {
        so = 1;
    } else if (f[0x1DD] == 2) {
        so = 2;
    } else if (f[0x1DD] == 3) {
        so = 3;
    }
    close = 0;
    if (*(f32*)(g_Ball + 0x19E0) > lbl_3_rodata_BD0) {
        d = *(f32*)(fl + 7 * 0x268 + 0x80) - *(f32*)(f + 0x80);
        if (d < lbl_3_rodata_B20) {
            d = -d;
        }
        if (d < lbl_3_rodata_BA0) {
            close = 1;
        }
    }
    if ((s7 == so && s7 < 10) || close != 0) {
        if (s7 == 0) {
            if (*(f32*)(fl + 7 * 0x268 + 0x80) <= *(f32*)(f + 0x80)) {
                *first = 7;
                if (*(f32*)(f + 0x80) - *(f32*)(fl + 7 * 0x268 + 0x80) < lbl_3_rodata_BA0) {
                    *second = other;
                }
            } else {
                *first = other;
                if (*(f32*)(fl + 7 * 0x268 + 0x80) - *(f32*)(f + 0x80) < lbl_3_rodata_BA0) {
                    *second = 7;
                }
            }
            return;
        }
        if (s7 == 1) {
            if (*(s16*)(fl + 7 * 0x268 + 0x186) <= *(s16*)(f + 0x186)) {
                *first = 7;
                if (*(s16*)(f + 0x186) - *(s16*)(fl + 7 * 0x268 + 0x186) < 0x2D) {
                    *second = other;
                }
            } else {
                *first = other;
                if (*(s16*)(fl + 7 * 0x268 + 0x186) - *(s16*)(f + 0x186) < 0x2D) {
                    *second = 7;
                }
            }
            return;
        }
    } else if (s7 < so) {
        if (s7 == 0) {
            *first = 7;
            if (so == 1 && *(s16*)(f + 0x186) - *(s16*)(fl + 7 * 0x268 + 0x186) < 0x1E) {
                *second = other;
            }
            return;
        }
        if (s7 == 1) {
            *first = 7;
            return;
        }
        if (so == 10) {
            *first = 7;
            return;
        }
    } else if (so < s7) {
        if (so == 0) {
            *first = other;
            if (s7 == 1 && *(s16*)(fl + 7 * 0x268 + 0x186) - *(s16*)(f + 0x186) < 0x1E) {
                *second = 7;
            }
            return;
        }
        if (so == 1) {
            *first = other;
            return;
        }
        if (s7 == 10) {
            *first = other;
            return;
        }
    }
    if (g_Ball[0x1BBF] >= 3) {
        d = *(f32*)(fl + 7 * 0x268 + 0x80) - *(f32*)(f + 0x80);
        if (d < lbl_3_rodata_B20) {
            *first = 7;
            if (d > lbl_3_rodata_BD4) {
                *second = other;
            }
        } else {
            *first = other;
            if (d < lbl_3_rodata_BA0) {
                *second = 7;
            }
        }
    } else if (__abs(ang - *(s16*)(fl + 7 * 0x268 + 0x182)) < __abs(ang - *(s16*)(f + 0x182)) + 0x40) {
        *first = 7;
        *second = other;
    } else {
        *first = other;
        *second = 7;
    }
}
#endif

// .text:0x000341E8 size:0x268 mapped:0x8067327C
// NONMATCHING 99%: SetFielderAct state/table regs r0/r4 swapped (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_341E8(void) {
    s32 first;
    s32 second;
    s16 ang;
    fn_3_33DD0(&first, &second);
    *(s16*)(g_FieldingLogic + 0xB0) = first;
    *(s16*)(g_FieldingLogic + 0xB2) = second;
    SetFielderAct((s16)first, 0x16, 0xB0);
    SetFielderAct(*(s16*)(g_FieldingLogic + 0xB2), 0x16, 0xB0);
    if (*(s16*)(g_FieldingLogic + 0xB2) >= 0) {
        g_FieldingLogic[0x139] = 1;
    } else {
        ang = fn_3_9FB8C(*(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
        if (*(s16*)(g_FieldingLogic + 0xB0) == 7) {
            if (ang < 0x400) {
                SetFielderAct(8, 0x18, 0xC0);
                *(s16*)(g_FieldingLogic + 0xBC) = 8;
            } else {
                SetFielderAct(6, 0x18, 0xC0);
                *(s16*)(g_FieldingLogic + 0xBC) = 6;
            }
        } else {
            SetFielderAct(7, 0x18, 0xC0);
            *(s16*)(g_FieldingLogic + 0xBC) = 7;
        }
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_33D9C();
}
#endif

// .text:0x00034450 size:0x5F0 mapped:0x806734E4
#pragma dont_inline off
/* same body as fn_3_33458, which the original inlines into fn_3_34450 */
static inline void PairPlayInline(void) {
    u8* f;
    s16 i;
    fn_3_334EC(1);
    fn_3_33088();
    i = *(s16*)(g_FieldingLogic + 0xB2);
    f = g_Fielders + i * 0x268;
    if (i != -1) {
        f[0x1D3] = 0x16;
        if (*(int*)(lbl_3_data_3C40 + 0xB0) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0xB0);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#pragma dont_inline on
// NONMATCHING 98%: loop-variable register order; one distance sum unfused in the original; calls fn_3_4F504/fn_3_4FB34 through casts until their prototypes gain the index arg
#if NONMATCHING
void fn_3_34450(void) {
    u8* f = g_Fielders;
    s64 mask = 0;
    s32 i = 0;
    s32 sh = 0;
    f32 d;
    f32 dx;
    f32 dz;
    s32 a;
    for (; i < 9; i++, sh += 3, f += 0x268) {
        if (i == 1) {
            *(s16*)(f + 0x182) = 0x400;
        } else if (lbl_3_rodata_B20 == *(f32*)f) {
            *(s16*)(f + 0x182) = 0x400;
        } else {
            a = (s32)(lbl_3_rodata_BC4 * (f32)atan2(*(f32*)(f + 8), *(f32*)f) / lbl_3_rodata_BC8);
            if (a < 0) {
                a += 0x800;
            }
            *(s16*)(f + 0x182) = a;
        }
        d = *(f32*)f * *(f32*)f + *(f32*)(f + 8) * *(f32*)(f + 8);
        SQRT_L(d);
        *(f32*)(f + 0x70) = d;
        dx = *(f32*)(g_Ball + 0x1A2C) - *(f32*)f;
        dz = *(f32*)(g_Ball + 0x1A30) - *(f32*)(f + 8);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x80) = d;
        /* TODO: fn_3_4F504 / fn_3_4FB34 take the fielder index; prototypes (other range) are still (void) */
        if (i == 1) {
            ((void (*)(int))fn_3_4F504)(1);
        } else {
            ((void (*)(int))fn_3_4FB34)(i);
        }
        if (f[0x1DD] == 1) {
            mask |= 4 << sh;
        } else if (f[0x1DD] == 2) {
            mask |= 2 << sh;
        } else if (f[0x1DD] == 3) {
            mask |= 1 << sh;
        }
    }
    if (g_d_GameSettings[7] == 2 && g_GameLogic[0x121] == 0xC) {
        SetFielderAct(0, 0x15, 0xA8);
        return;
    }
    if (g_Ball[0x1BCE] != 0) {
        fn_3_32810();
    } else if (g_Ball[0x1BC5] == 7 || g_Ball[0x1BC5] == 8) {
        fn_3_329A4();
    } else if ((mask & 0x3FFFF) == 0 || (g_Ball[0x1BBF] == 4 && *(f32*)(g_Ball + 0x19D4) > lbl_3_rodata_BD8)) {
        if (*(f32*)(g_Ball + 0x19D4) < lbl_3_rodata_B64) {
            PairPlayInline();
        } else {
            fn_3_341E8();
        }
    } else if ((mask & 0x2DB6D) != 0) {
        fn_3_334EC(0);
    } else if ((mask & 0x12480) != 0) {
        PairPlayInline();
    } else if ((mask & 2) != 0) {
        fn_3_334EC(0);
    }
    *(s16*)(g_FieldingLogic + 0xB8) = *(s16*)(g_FieldingLogic + 0xB2);
    *(s16*)(g_FieldingLogic + 0xBA) = *(s16*)(g_FieldingLogic + 0xB4);
}
#endif

// .text:0x00034A40 size:0x12E8 mapped:0x80673AD4
extern f32 lbl_3_rodata_B60;
extern f32 lbl_3_rodata_B48;
extern f32 lbl_3_rodata_BB0;
extern f32 lbl_3_rodata_BDC;
#pragma dont_inline off
/* point fielder f at (x, z): sets target, heading and remaining distance */
static inline void SetRunTargetInline(u8* f, f32 x, f32 z) {
    f32 dx;
    f32 dz;
    f32 d;
    *(f32*)(f + 0x14) = x;
    *(f32*)(f + 0x1C) = z;
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        *(f32*)(f + 0x68) = lbl_3_rodata_B20;
    } else {
        *(f32*)(f + 0x64) = (f32)atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}
#pragma dont_inline on
#pragma dont_inline off
/* frames for fielder f to reach (x, z) */
static inline s32 EtaToInline(u8* f, f32 x, f32 z) {
    f32 dx;
    f32 dz;
    f32 d;
    f32 sp;
    if (x == *(f32*)f && z == *(f32*)(f + 8)) {
        return 1;
    }
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    d = dx * dx + dz * dz;
    SQRT_L(d);
    sp = *(f32*)(f + 0x58);
    if (sp == lbl_3_rodata_B20) {
        sp = lbl_3_rodata_B60;
    }
    return (s32)((u32)f[0x1D1] >> 1) + (s32)(d / sp);
}
#pragma dont_inline on
extern f32 lbl_3_rodata_BE0;
// NONMATCHING 96%: f-reg numbering throughout; three distance sums unfused in the original; calls fn_3_526DC through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_34A40(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    s32 k;
    s32 t;
    if (*(s16*)(g_Ball + 0x1B78) >= 0 && *(s16*)(g_Ball + 0x1B78) != i) {
        if (*(f32*)(f + 0x50) == lbl_3_rodata_B20) {
            *(f32*)(f + 0x68) = lbl_3_rodata_B20;
            *(f32*)(f + 0x14) = *(f32*)f;
            *(f32*)(f + 0x18) = *(f32*)(f + 4);
            *(f32*)(f + 0x1C) = *(f32*)(f + 8);
            *(f32*)(f + 0x30) = lbl_3_rodata_B20;
            *(f32*)(f + 0x34) = lbl_3_rodata_B20;
        }
    } else {
        f[0x1D6] = 0;
        f[0x1EB] = 0;
        *(s16*)(f + 0x1A4) = 0;
        if (*(s16*)(g_Ball + 0x1B7E) >= 0 && !(*(s16*)(g_Ball + 0x1B7A) == 0 && g_Ball[0x1BC3] == 2)) {
            goto track;
        }
        if (*(s16*)(g_Ball + 0x1B7E) >= 0) {
            /* ground ball fielded on the infield: go to / cut off the ball */
            dx = *(f32*)(g_Ball + 0x19D8) - *(f32*)(g_Ball + 0x348);
            dz = *(f32*)(g_Ball + 0x19DC) - *(f32*)(g_Ball + 0x34C);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            if (*(f32*)(g_Ball + 0x1A14) > lbl_3_rodata_B20 || d > lbl_3_rodata_B9C) {
                if (*(f32*)(g_Ball + 0x350) < lbl_3_rodata_B78) {
                    f32 r = *(f32*)(f + 0x70);
                    if (r < lbl_3_rodata_B70) {
                        SetRunTargetInline(f, *(f32*)f, *(f32*)(f + 8));
                    } else {
                        SetRunTargetInline(f, lbl_3_rodata_B70 * (*(f32*)f / r), lbl_3_rodata_B70 * (*(f32*)(f + 8) / r));
                    }
                } else {
                    SetRunTargetInline(f,
                                       lbl_3_rodata_B70 * (*(f32*)(g_Ball + 0x348) / *(f32*)(g_Ball + 0x350)) +
                                           *(f32*)(g_Ball + 0x348),
                                       lbl_3_rodata_B70 * (*(f32*)(g_Ball + 0x34C) / *(f32*)(g_Ball + 0x350)) +
                                           *(f32*)(g_Ball + 0x34C));
                }
            } else {
                SetRunTargetInline(f, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
            }
            if (*(f32*)(f + 0x68) < lbl_3_rodata_BA0) {
                f[0x1D6] = 8;
            }
        } else if (*(s16*)(g_Ball + 0x1B7A) == 0) {
            /* ball on the ground, nobody assigned: chase the landing point or a later trajectory point */
            if (*(s16*)(g_Ball + 0x1B60) - EtaToInline(f, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C)) > 0xA) {
                SetRunTargetInline(f, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
            } else {
                for (k = 10; k <= 60; k += 10) {
                    if (k == 60) {
                        t = *(s16*)(g_Ball + 0x1B60) + k;
                        SetRunTargetInline(f, *(f32*)(g_Ball + t * 16 + 0x354), *(f32*)(g_Ball + t * 16 + 0x35C));
                        break;
                    }
                    t = *(s16*)(g_Ball + 0x1B60) + k;
                    if (t - EtaToInline(f, *(f32*)(g_Ball + t * 16 + 0x354), *(f32*)(g_Ball + t * 16 + 0x35C)) > 5) {
                        SetRunTargetInline(f, *(f32*)(g_Ball + t * 16 + 0x354), *(f32*)(g_Ball + t * 16 + 0x35C));
                        break;
                    }
                }
            }
            if (i <= 5) {
                if (*(f32*)(f + 0x80) < lbl_3_rodata_BA0) {
                    f[0x1D6] = 8;
                }
            } else if (*(s16*)(g_FieldingLogic + 0xB0) <= 5 &&
                       *(f32*)(g_Ball + 0x1A00) <
                           *(f32*)(g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268 + 0x70)) {
                if (*(f32*)(f + 0x80) < lbl_3_rodata_B64) {
                    f[0x1D6] = 8;
                }
            } else if (*(f32*)(f + 0x80) < lbl_3_rodata_BA0) {
                f[0x1D6] = 8;
            }
        } else {
            f32 near;
            f32 reach;
            f32 lead;
            f32 tx;
            f32 tz;
        track:
            /* ball in flight: lead the ball along its velocity */
            near = *(f32*)(f + 0x7C);
            reach = *(f32*)(f + 0x74);
            lead = lbl_3_rodata_B60 + ((near - lbl_3_rodata_B70) / lbl_3_rodata_BDC + (*(f32*)(g_Ball + 0x1A14) - lbl_3_rodata_BE0));
            tx = lead * (reach * *(f32*)(g_Ball + 0x1A18)) + *(f32*)g_Ball;
            tz = lead * (reach * *(f32*)(g_Ball + 0x1A1C)) + *(f32*)(g_Ball + 8);
            if (i >= 6 && *(f32*)(f + 0x70) < lbl_3_rodata_BB0) {
                tx = *(f32*)f;
                tz = *(f32*)(f + 8);
            }
            SetRunTargetInline(f, tx, tz);
            if (*(f32*)(f + 0x74) < lbl_3_rodata_B9C && near < lbl_3_rodata_B64) {
                if (lbl_3_bss_170 >= 0) {
                    s16 a = radToShortAngle(atan2(*(f32*)(g_Ball + 8) - *(f32*)(f + 8), *(f32*)g_Ball - *(f32*)f));
                    if (__abs(lbl_3_bss_170 - a) > 0x80) {
                        f[0x1D6] = 8;
                    }
                } else {
                    f[0x1D6] = 8;
                }
            }
        }
    }
    if (*(f32*)(f + 0x50) < lbl_3_rodata_B48 && f[0x1D6] == 8) {
        *(f32*)(f + 0x68) = lbl_3_rodata_B20;
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        *(f32*)(f + 0x14) = *(f32*)f;
        *(f32*)(f + 0x1C) = *(f32*)(f + 8);
        *(s16*)(f + 0x1A0) = 0;
        f[0x1D6] = 0;
    }
    /* TODO: fn_3_526DC takes the fielder index; its prototype (other range) is still (void) */
    ((void (*)(int))fn_3_526DC)(i);
    if (*(f32*)(f + 0x50) != lbl_3_rodata_B20) {
        *(s16*)(f + 0x17E) = *(f32*)(f + 0x68) / *(f32*)(f + 0x50);
    }
}
#endif

// .text:0x00035D28 size:0xF4 mapped:0x80674DBC
void fn_3_35D28(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(s16*)(g_Ball + 0x1B66) > 0 && fn_3_53130(i) == 0) {
        fn_3_34A40(i);
        fn_3_4207C(i);
        if (g_Ball[0x1BC9] != 0 && g_Ball[0x1BC9] != 3) {
            if (i != -1) {
                int v;
                f[0x1D3] = 12;
                v = *(int*)(lbl_3_data_3C40 + 0x60);
                if (v >= 0) {
                    g_FieldingLogic[i + 0xF8] = v;
                }
                f[0x1D5] = 0;
                f[0x1D6] = 0;
                *(s16*)(f + 0x1A4) = 0;
                *(s16*)(f + 0x1AC) = 0;
                f[0x1FF] = 0;
            }
            if (i <= 5) {
                f[0x1D5] = 3;
            } else {
                f[0x1D5] = 2;
            }
        }
    }
}

// .text:0x00035E1C size:0x3BC mapped:0x80674EB0
// NONMATCHING 79%: the original unrolls the 6-entry search loop by 3 (ctr=2); ours (s16 counter) is not unrolled, an s32 counter unrolls it fully
#if NONMATCHING
void fn_3_35E1C(void) {
    s32 a = -1;
    s32 mode = 0;
    s32 b = -1;
    s16 i;
    f32 dx;
    f32 dz;
    f32 d;
    if (g_Ball[0x1BBE] >= 3 && *(s16*)(g_FieldingLogic + 0xC4) == 0) {
        mode = 1;
    } else if (g_Ball[0x1BBE] <= 1) {
        mode = 2;
    }
    for (i = 0; i < 6; i++) {
        if (g_FieldingLogic[i + 0xF8] != 2 && i != *(s16*)(g_Ball + 0x1B94)) {
            if (a != -1) {
                b = i;
                break;
            }
            a = i;
        }
    }
    if (mode != 0 && a >= 0 && b >= 0) {
        if (!(*(f32*)(g_Fielders + a * 0x268 + 0xB8) < *(f32*)(g_Fielders + b * 0x268 + 0xB8))) {
            a = b;
        }
    } else {
        dx = *(f32*)(g_Ball + 0x19F8) - *(f32*)g_Ball;
        dz = *(f32*)(g_Ball + 0x19FC) - *(f32*)(g_Ball + 8);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < *(f32*)(g_Fielders + a * 0x268 + 0x74)) {
            a = -1;
        }
        if (d < *(f32*)(g_Fielders + b * 0x268 + 0x74)) {
            b = -1;
        }
        if (a < 0) {
            a = b;
            b = -1;
        }
        if (a < 0) {
            return;
        }
        if (b >= 0 && *(f32*)(g_Fielders + a * 0x268 + 0x7C) > *(f32*)(g_Fielders + b * 0x268 + 0x7C)) {
            a = b;
        }
    }
    if (a < 0) {
        return;
    }
    if (mode == 2) {
        if (*(f32*)(g_Fielders + a * 0x268 + 0x7C) > lbl_3_rodata_B68) {
            return;
        }
    } else if (mode == 0 && *(f32*)(g_Fielders + a * 0x268 + 0x7C) > lbl_3_rodata_B8C) {
        return;
    }
    SetFielderAct(a, 0x19, 0xC8);
    *(s16*)(g_FieldingLogic + 0xC2) = a;
}
#endif

#pragma dont_inline off
/* same body as fn_3_365D0, inlined into fn_3_361D8 */
static inline int Pick3Inline(int a, int b, int c, f32 x, f32 y) {
    int r = fn_3_36678(b, c, x, y, 1);
    if (r == -1) {
        return a;
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) < 0) {
        return fn_3_36678(a, r, x, y, 1);
    }
    return fn_3_36678(a, r, x, y, 0);
}
#pragma dont_inline on
extern f32 lbl_3_rodata_BA4;
// .text:0x000361D8 size:0x3F8 mapped:0x8067526C
// NONMATCHING 96%: zero-init of i0/i1/i2 is li x3 (orig li+mr+mr); inlined fn_3_365D0 tail keeps an extra mr
#if NONMATCHING
int fn_3_361D8(f32 x, f32 z) {
    f32 d3, d2, d1, d0;
    f32 d;
    s32 i3, i2, i1, i0;
    s32 a1, a2, a0, a3;
    s32 ang;
    u8* f;
    s32 i;
    s32 r;
    i2 = 0;
    d0 = d1 = d2 = d3 = lbl_3_rodata_BA4;
    f = g_Fielders;
    i0 = i1 = i2;
    i3 = 0;
    for (i = 0; i < 9; i++, f += 0x268) {
        f32 dx = *(f32*)f - x;
        f32 dz = *(f32*)(f + 8) - z;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        ang = (s16)fn_3_9FB8C(dx, dz);
        if (d0 > d) {
            d2 = d1;
            i2 = i1;
            d1 = d0;
            a2 = a1;
            i1 = i0;
            a1 = a0;
            d0 = d;
            i0 = i;
            a0 = ang;
        } else if (d1 > d) {
            d2 = d1;
            i2 = i1;
            d1 = d;
            a2 = a1;
            i1 = i;
            a1 = ang;
        } else if (d2 > d) {
            d3 = d2;
            i3 = i2;
            d2 = d;
            a3 = a2;
            i2 = i;
            a2 = ang;
        } else if (d3 > d) {
            d3 = d;
            i3 = i;
            a3 = ang;
        }
    }
    if (d3 - lbl_3_rodata_B70 < d2) {
        if (fn_3_9FCF8(a1, a2) < 0x180) {
            if (fn_3_9FCF8(a0, a3) > 0x200 && fn_3_9FCF8(a1, a3) > 0x200) {
                i2 = i3;
            }
        } else if (fn_3_9FCF8(a0, a2) < 0x180) {
            if (fn_3_9FCF8(a0, a3) > 0x200 && fn_3_9FCF8(a1, a3) > 0x200) {
                i2 = i3;
            }
        } else if (fn_3_9FCF8(a0, a1) < 0x180 && fn_3_9FCF8(a0, a3) > 0x200 && fn_3_9FCF8(a2, a3) > 0x200) {
            i1 = i2;
            i2 = i3;
        }
    }
    i0 = Pick3Inline(i0, i1, i2, x, z);
    return i0;
}
#endif

// .text:0x000365D0 size:0xA8 mapped:0x80675664
int fn_3_365D0(int a, int b, int c, f32 x, f32 y) {
    int r = fn_3_36678(b, c, x, y, 1);
    if (r == -1) {
        return a;
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) < 0) {
        return fn_3_36678(a, r, x, y, 1);
    }
    return fn_3_36678(a, r, x, y, 0);
}

// .text:0x00036678 size:0xA9C mapped:0x8067570C
extern f32 lbl_3_rodata_BE8;
extern f32 lbl_3_rodata_BEC;
extern f32 lbl_3_rodata_BF0;
extern f32 lbl_3_rodata_BF4;
extern f32 lbl_3_rodata_BBC;
// NONMATCHING 91%: fielder x/z read via lfsx in the original; dist sums are unfused fmuls+fadds there; f-reg numbering
#if NONMATCHING
int fn_3_36678(int a, int b, f32 x, f32 z, int mode) {
    u8* fa;
    u8* fb;
    s16 angA;
    s16 angB;
    s16 angDiff;
    f32 distA;
    f32 distB;
    f32 dx;
    f32 dz;
    s16 dA;
    s16 dB;
    if (lbl_3_bss_16C < 0) {
        return -1;
    }
    fa = g_Fielders + a * 0x268;
    fb = g_Fielders + b * 0x268;
    angA = radToShortAngle(atan2(z - *(f32*)(fa + 8), x - *(f32*)fa));
    angB = radToShortAngle(atan2(z - *(f32*)(fb + 8), x - *(f32*)fb));
    angDiff = fn_3_9FCF8(angA, angB);
    dx = *(f32*)fa - x;
    dz = *(f32*)(fa + 8) - z;
    distA = dx * dx + dz * dz;
    SQRT_L(distA);
    dx = *(f32*)fb - x;
    dz = *(f32*)(fb + 8) - z;
    distB = dx * dx + dz * dz;
    SQRT_L(distB);
    if (angDiff <= 0x100) {
        if (distA < distB) {
            return a;
        }
        return b;
    }
    if (mode < 2) {
        s32 sel;
        s32 d;
        if (*(s16*)(g_FieldingLogic + 0xB0) == a) {
            distA -= lbl_3_rodata_B78;
            if (distA < lbl_3_rodata_B20) {
                distA = lbl_3_rodata_B20;
            }
        } else if (*(s16*)(g_FieldingLogic + 0xB0) == b) {
            distB -= lbl_3_rodata_B78;
            if (distB < lbl_3_rodata_B20) {
                distB = lbl_3_rodata_B20;
            }
        }
        if ((&lbl_3_bss_170)[3] >= 0) {
            d = __abs((&lbl_3_bss_170)[0] - (&lbl_3_bss_170)[3]);
            if (d > 0x800) {
                d = 0x1000 - d;
            }
            if (d <= 0x400) {
                f32 home;
                f32 step;
                f32 lim;
                sel = -1;
                if (a == *(s16*)(g_FieldingLogic + 0xB0)) {
                    sel = a;
                }
                if (b == *(s16*)(g_FieldingLogic + 0xB0)) {
                    sel = b;
                }
                if (sel >= 0) {
                    u8* fs = g_Fielders + sel * 0x268;
                    f32 dSel;
                    f32 dTgt;
                    dx = *(f32*)fs - x;
                    dz = *(f32*)(fs + 8) - z;
                    dSel = dx * dx + dz * dz;
                    SQRT_L(dSel);
                    dx = *(f32*)(fs + 0xD4) - x;
                    dz = *(f32*)(fs + 0xD8) - z;
                    dTgt = dx * dx + dz * dz;
                    SQRT_L(dTgt);
                    if (dSel > dTgt) {
                        goto compare;
                    }
                }
                step = lbl_3_rodata_BE4;
                home = x * x + z * z;
                SQRT_L(home);
                if (home < lbl_3_rodata_BE8) {
                    step = lbl_3_rodata_B8C;
                } else if (home < lbl_3_rodata_BEC) {
                    step = lbl_3_rodata_B64;
                } else if (home < lbl_3_rodata_BF0) {
                    step = lbl_3_rodata_BF4;
                }
                lim = lbl_3_rodata_BD8;
                if (home < lbl_3_rodata_BEC) {
                    lim = lbl_3_rodata_B8C;
                } else if (home < lbl_3_rodata_BF0) {
                    lim = lbl_3_rodata_BBC * (home - lbl_3_rodata_BE8) + lbl_3_rodata_B8C;
                }
                if (a == *(s16*)(g_FieldingLogic + 0xB0)) {
                    if (distA > lim) {
                        distA -= step;
                    } else {
                        distA = lbl_3_rodata_B20;
                    }
                }
                /* the original compares and subtracts distA here, not distB */
                if (b == *(s16*)(g_FieldingLogic + 0xB0) && distA > lim) {
                    distB = distA - step;
                }
            }
        }
    }
compare:
    if (distB < distA) {
        f32 tf = distA;
        int ti = a;
        s16 ta = angA;
        distA = distB;
        a = b;
        angA = angB;
        distB = tf;
        b = ti;
        angB = ta;
    }
    if (mode < 3) {
        f32 gap;
        if (distA < lbl_3_rodata_B68) {
            return a;
        }
        gap = distB - distA;
        if (gap > lbl_3_rodata_B70) {
            if (gap > lbl_3_rodata_B9C && *(s16*)(g_Ball + 0x1B7A) == 1 && a >= 6) {
                return a;
            }
            if (g_Ball[0x1BC9] != 0 || *(s16*)(g_Ball + 0x1B7A) != 1) {
                return a;
            }
            if (a == 1 && gap > lbl_3_rodata_B9C) {
                return a;
            }
        }
        if (gap > lbl_3_rodata_BA0 && distA < lbl_3_rodata_BE4) {
            return a;
        }
        if (distA < lbl_3_rodata_B64 && distB < lbl_3_rodata_B64 && angDiff <= 0x400) {
            if (mode == 0) {
                return -1;
            }
            return a;
        }
        if (angDiff <= 0x200 && gap > lbl_3_rodata_B64 && distA < lbl_3_rodata_B70) {
            return a;
        }
    }
    dA = __abs(lbl_3_bss_16C - angA);
    dB = __abs(lbl_3_bss_16C - angB);
    if (dA > 0x800) {
        dA = 0x1000 - dA;
    }
    if (dB > 0x800) {
        dB = 0x1000 - dB;
    }
    if (__abs(dA - dB) <= 0x100) {
        return a;
    }
    if (dA > 0x400) {
        if (g_Ball[0x1BC9] == 0 && *(s16*)(g_Ball + 0x1B7A) == 1 && b == 1) {
            if (dB <= 0x200) {
                return b;
            }
        } else if (dB <= 0x400) {
            return b;
        }
        if (mode == 0) {
            return -1;
        }
    }
    if (dB > 0x400) {
        if (g_Ball[0x1BC9] == 0 && *(s16*)(g_Ball + 0x1B7A) == 1 && b == 1) {
            if (dA <= 0x200) {
                return a;
            }
        } else {
            return a;
        }
    }
    if (dA > dB) {
        return b;
    }
    return a;
}
#endif

// .text:0x00037114 size:0x2F8 mapped:0x806761A8
// NONMATCHING 98%: angA/fb share r29 in the original, ours uses r26 (one extra saved reg)
#if NONMATCHING
int fn_3_37114(int a, int b, int strict, f32 x, f32 z) {
    u8* fa = g_Fielders + a * 0x268;
    u8* fb = g_Fielders + b * 0x268;
    s32 cur = lbl_3_bss_16C;
    s16 angB;
    s16 angA;
    s16 da;
    s16 db;
    f32 dx;
    f32 dz;
    f32 d;
    if (cur < 0) {
        return -1;
    }
    dx = x - *(f32*)fa;
    dz = z - *(f32*)(fa + 8);
    /* distance computed but unused (the original keeps only the fcmpo) */
    d = dx * dx + dz * dz;
    SQRT_L(d);
    angA = fn_3_9FB8C(dx, dz);
    dx = x - *(f32*)fb;
    dz = z - *(f32*)(fb + 8);
    d = dx * dx + dz * dz;
    SQRT_L(d);
    angB = fn_3_9FB8C(dx, dz);
    if (strict != 0) {
        if (cur >= 0x580 && cur < 0xA80) {
            if (angA >= 0x580 && angA < 0xA80 && angB >= 0x580 && angB < 0xA80) {
                goto closer;
            }
            if (angA >= 0x580 && angA < 0xA80) {
                return a;
            }
            if (angB >= 0x580 && angB < 0xA80) {
                return b;
            }
        } else if (cur <= 0x280 && cur >= 0xD80) {
            if (!(angA >= 0x280 && angA < 0xD80) && !(angB >= 0x280 && angB < 0xD80)) {
                goto closer;
            }
            if (angA < 0x280 || angA >= 0xD80) {
                return a;
            }
            if (angB < 0x280 || angB >= 0xD80) {
                return b;
            }
        }
    } else if (cur >= 0x400 && cur < 0xC00) {
        if (!(angA >= 0x400 && angA < 0xC00 && angB >= 0x400 && angB < 0xC00)) {
            if (angA >= 0x400 && angA < 0xC00) {
                return a;
            }
            if (angB >= 0x400 && angB < 0xC00) {
                return b;
            }
        }
    } else if ((angA >= 0x400 && angA < 0xC00) || (angB >= 0x400 && angB < 0xC00)) {
        if (angA < 0x400 || angA >= 0xC00) {
            return a;
        }
        if (angB < 0x400 || angB >= 0xC00) {
            return b;
        }
    }
    if (strict != 0) {
        return -1;
    }
    da = fn_3_9FCF8(lbl_3_bss_16C, angA);
    db = fn_3_9FCF8(lbl_3_bss_16C, angB);
    if (__abs(da - db) > 0x100) {
        if (da > 0x400) {
            if (db > 0x400) {
                return -1;
            }
            return b;
        }
        if (db > 0x400) {
            if (da > 0x400) {
                return -1;
            }
            return a;
        }
    }
closer:
    if (angA < angB) {
        return a;
    }
    return b;
}
#endif

// .text:0x0003740C size:0x17C mapped:0x806764A0
void fn_3_3740C(void) {
    s16 ang;
    f32 mx = 0.0f;
    s32 best = 0x1000;
    s32 idx = -1;
    s32 i;
    if (g_Ball[0x1BC9] == 0 && *(s16*)(g_FieldingLogic + 0xB0) <= 5) {
        for (i = 0; i < 6; i++) {
            f32 v = *(f32*)(g_Fielders + i * 0x268 + 0x70);
            if (v > mx) {
                mx = v;
            }
        }
        if (5.0f + mx < *(f32*)(g_Ball + 0x1A00)) {
            ang = *(s16*)(g_Ball + 0x1B80);
            for (i = 6; i < 9; i++) {
                s32 d = __abs(ang - *(s16*)(g_Fielders + i * 0x268 + 0x180));
                if (best > d) {
                    best = d;
                    idx = i;
                }
            }
            *(s16*)(g_Ball + 0x1B80) = ang;
            if (i >= 0) {
                fn_3_38790(idx, 0);
            }
        }
    }
}

// .text:0x00037588 size:0x88 mapped:0x8067661C
void fn_3_37588(void) {
    if (*(f32*)(g_Ball + 0x1A14) > 0.17f) {
        fn_3_38790(fn_3_378B4(), 0);
        return;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 0 && *(u8*)(g_Ball + 0x1BC3) != 0) {
        fn_3_37610(*(s16*)(g_Ball + 0x1B60));
        return;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 0) {
        fn_3_37610(30);
        return;
    }
    fn_3_37610(30);
}

// .text:0x00037610 size:0x2A4 mapped:0x806766A4
// 98%: prologue lis order (BFC load) and f/ao regs r6/r9 swapped in the idx>=0 block
void fn_3_37610(int a) {
    f32 t;
    f32 best = lbl_3_rodata_BFC;
    s32 idx = -1;
    s32 i;
    f32 dx;
    f32 dz;
    f32 d;
    f32 a2;
    f32 b2;
    for (i = 0; i < 9; i++) {
        u8* f = g_Fielders + i * 0x268;
        t = *(f32*)(f + 0x74);
        if (t < 5.0f && f[0x20F] == 0 && t < best && (f[0x210] == 0 || !((0.05f * (f32) * (s16*)(f + 0x1C0) + t) > best))) {
            best = t;
            idx = i;
        }
    }
    if (idx >= 0) {
        u8* base = g_Fielders;
        int off = idx * 0x268;
        u8* f = base + off;
        if (!(*(f32*)(f + 0x74) < lbl_3_rodata_B64)) {
            dx = *(f32*)(g_Ball + a * 16 + 0x354) - *(f32*)(base + off);
            dz = *(f32*)(g_Ball + a * 16 + 0x35C) - *(f32*)(f + 8);
            a2 = dx * dx;
            b2 = dz * dz;
            d = a2 + b2;
            SQRT_L(d);
            if (d > lbl_3_rodata_B64) {
                idx = -1;
            }
        }
    }
    if (idx >= 0 && idx != *(s16*)(g_FieldingLogic + 0xB0) && *(s16*)(g_FieldingLogic + 0xB0) >= 0) {
        u8* g = g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
        if (*(f32*)(g + 0x74) < lbl_3_rodata_BD8 && g[0x20F] == 0) {
            idx = -1;
        }
    }
    fn_3_38790(idx >= 0 ? idx : fn_3_361D8(*(f32*)(g_Ball + a * 16 + 0x354), *(f32*)(g_Ball + a * 16 + 0x35C)), 0);
}

// .text:0x000378B4 size:0x74C mapped:0x80676948
#define FLD_ANG(n) (*(s16*)(g_Fielders + (n) * 0x268 + 0x180))
#define FLD_RNG(n) (*(f32*)(g_Fielders + (n) * 0x268 + 0x70))
// NONMATCHING 88%: original preloads r3=-1 and returns via bltlr/bgelr; ours materialises li r3,-1 per return; register numbering
#if NONMATCHING
s32 fn_3_378B4(void) {
    s16 cur = lbl_3_bss_170;
    s16 ang = *(s16*)(g_Ball + 0x1B80);
    s32 turn = 0x800;
    s32 mid;
    s32 w;
    if (cur >= 0 && (&lbl_3_bss_170)[3] >= 0) {
        turn = __abs(cur - (&lbl_3_bss_170)[3]);
        if (turn > 0x800) {
            turn = 0x1000 - turn;
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) == 0) {
        if (ang >= FLD_ANG(0) - 0x40 && ang < FLD_ANG(0) + 0x40 &&
            *(f32*)(g_Ball + 0x1A00) - FLD_RNG(0) < lbl_3_rodata_B78) {
            return 0;
        }
        if (ang < FLD_ANG(0)) {
            if (cur >= 0xF00 || (cur >= 0 && cur < 0x300)) {
                return 0;
            }
            if (cur >= 0xB00 && cur < 0xF00 && *(f32*)(g_Ball + 0x1A00) - FLD_RNG(0) < lbl_3_rodata_B78) {
                return 0;
            }
        } else {
            if (cur >= 0x500 && cur < 0x900) {
                return 0;
            }
            if (cur >= 0x900 && cur < 0xD00 && *(f32*)(g_Ball + 0x1A00) - FLD_RNG(0) < lbl_3_rodata_B78) {
                return 0;
            }
        }
    }
    if (__abs(FLD_ANG(2) - FLD_ANG(3)) < 0x40 &&
        ((*(s16*)(g_FieldingLogic + 0xB0) != 2 && *(s16*)(g_FieldingLogic + 0xB0) != 3) || turn >= 0x400)) {
        mid = (FLD_ANG(2) + FLD_ANG(3)) / 2;
        if (ang >= mid - 0x100 && ang < mid + 0x100) {
            if (FLD_RNG(2) < FLD_RNG(3)) {
                if (FLD_RNG(2) > *(f32*)(g_Ball + 0x1A00)) {
                    return 2;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(3) > *(f32*)(g_Ball + 0x1A00)) {
                    return 3;
                }
            } else {
                if (FLD_RNG(3) > *(f32*)(g_Ball + 0x1A00)) {
                    return 2;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(2) > *(f32*)(g_Ball + 0x1A00)) {
                    return 3;
                }
            }
        }
    }
    if (__abs(FLD_ANG(4) - FLD_ANG(5)) < 0x40 &&
        ((*(s16*)(g_FieldingLogic + 0xB0) != 4 && *(s16*)(g_FieldingLogic + 0xB0) != 5) || turn >= 0x400)) {
        mid = (FLD_ANG(4) + FLD_ANG(5)) / 2;
        if (ang >= mid - 0x100 && ang < mid + 0x100) {
            if (FLD_RNG(4) <= FLD_RNG(5)) {
                if (FLD_RNG(4) > *(f32*)(g_Ball + 0x1A00)) {
                    return 4;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(5) > *(f32*)(g_Ball + 0x1A00)) {
                    return 5;
                }
            } else {
                if (FLD_RNG(5) > *(f32*)(g_Ball + 0x1A00)) {
                    return 5;
                }
                if (lbl_3_rodata_B78 + FLD_RNG(4) > *(f32*)(g_Ball + 0x1A00)) {
                    return 4;
                }
            }
        }
    }
    if (ang < FLD_ANG(2) + 0x40) {
        if (*(s16*)(g_FieldingLogic + 0xB0) != 3 || turn >= 0x400) {
            return 2;
        }
        return -1;
    }
    if (ang >= FLD_ANG(4) - 0x40 && ang < 0x800) {
        if (*(s16*)(g_FieldingLogic + 0xB0) != 5 || turn >= 0x400) {
            return 4;
        }
        return -1;
    }
    w = 0;
    if (*(s16*)(g_FieldingLogic + 0xB0) == 3) {
        w = 0x20;
    }
    if (ang >= FLD_ANG(3) - (w + 0x40) && ang < w + FLD_ANG(3) + 0x40) {
        if (*(s16*)(g_FieldingLogic + 0xB0) == 2) {
            if (cur >= 0x500 && cur < 0x900) {
                return 2;
            }
            return 3;
        }
        if (*(s16*)(g_FieldingLogic + 0xB0) == 5 && *(s16*)(g_Fielders + 3 * 0x268 + 0x18C) == 2 && turn < 0x400) {
            return -1;
        }
        if (*(s16*)(g_FieldingLogic + 0xB0) == 5 && *(s16*)(g_Fielders + 3 * 0x268 + 0x18C) == 2 &&
            lbl_3_rodata_B64 + FLD_RNG(3) < *(f32*)(g_Ball + 0x1A00)) {
            return -1;
        }
        return 3;
    }
    w = 0;
    if (*(s16*)(g_FieldingLogic + 0xB0) == 2) {
        w = 0x20;
    }
    if (ang >= FLD_ANG(5) - (w + 0x40) && ang < w + FLD_ANG(5) + 0x40) {
        if (*(s16*)(g_FieldingLogic + 0xB0) == 4) {
            if ((cur >= 0 && cur < 0x300) || cur >= 0xF00) {
                return 4;
            }
            return 5;
        }
        if (*(s16*)(g_FieldingLogic + 0xB0) == 3 && *(s16*)(g_Fielders + 5 * 0x268 + 0x18C) == 2 && turn < 0x400) {
            return -1;
        }
        if (*(s16*)(g_FieldingLogic + 0xB0) == 3 && *(s16*)(g_Fielders + 5 * 0x268 + 0x18C) == 2 &&
            lbl_3_rodata_B64 + FLD_RNG(5) < *(f32*)(g_Ball + 0x1A00)) {
            return -1;
        }
        return 5;
    }
    if (ang >= FLD_ANG(2) && ang < FLD_ANG(3)) {
        if (cur >= 0x300 && cur < 0x700) {
            return 2;
        }
        if (cur >= 0x700 && cur < 0x900) {
            if (lbl_3_rodata_B64 + *(f32*)(g_Fielders + 2 * 0x268 + 8) > *(f32*)(g_Ball + 8)) {
                return 2;
            }
            return -1;
        }
        if (cur >= 0xD00 || (cur >= 0 && cur < 0x300)) {
            return 3;
        }
        return -1;
    }
    if (ang >= FLD_ANG(5) && ang < FLD_ANG(4)) {
        if (cur >= 0x100 && cur < 0x500) {
            return 4;
        }
        if (cur >= 0xF00 || (cur >= 0 && cur < 0x100)) {
            if (lbl_3_rodata_B64 + *(f32*)(g_Fielders + 4 * 0x268 + 8) > *(f32*)(g_Ball + 8)) {
                return 4;
            }
            return -1;
        }
        if (cur >= 0x500 && cur < 0xB00) {
            return 5;
        }
        return -1;
    }
    if (ang >= FLD_ANG(3) && ang < FLD_ANG(5)) {
        if (*(f32*)(g_Ball + 0x1A00) < lbl_3_rodata_B64 + FLD_RNG(0)) {
            if (ang < FLD_ANG(0)) {
                if (cur > 0xD00 || (cur >= 0 && cur < 0x100)) {
                    return 0;
                }
            } else if (cur >= 0x700 && cur < 0xB00) {
                return 0;
            }
        }
        if (cur >= 0x500 && cur < 0xB00) {
            return 3;
        }
        if (cur > 0xD00 || (cur >= 0 && cur < 0x300)) {
            return 5;
        }
        return -1;
    }
    return -1;
}
#endif
#undef FLD_ANG
#undef FLD_RNG

// .text:0x00038000 size:0x234 mapped:0x80677094
void fn_3_38000(void) {
    f32 t;
    f32 mx;
    s16 ang = *(s16*)(g_Ball + 0x1B80);
    f32 slack = lbl_3_rodata_B64;
    s32 k = 30;
    s32 mode = 0;
    s32 res;
    if (ang >= 0x800) {
        res = 1;
    } else {
        if (ang < 0x300 && (ang < *(s16*)(g_Fielders + 0x650) || fn_3_9FCF8(ang, *(s16*)(g_Fielders + 0x8B8)) >= 0x100)) {
            mode = 8;
            mx = *(f32*)(g_Fielders + 0x540);
        } else if (ang > 0x500 && (ang >= *(s16*)(g_Fielders + 0xB20) || fn_3_9FCF8(ang, *(s16*)(g_Fielders + 0xD88)) >= 0x100)) {
            mode = 6;
            mx = *(f32*)(g_Fielders + 0xA10);
        } else if (ang < *(s16*)(g_Fielders + 0x8B8)) {
            f32 a = *(f32*)(g_Fielders + 0x7A8);
            f32 b = *(f32*)(g_Fielders + 0x540);
            mx = a >= b ? a : b;
        } else if (ang >= *(s16*)(g_Fielders + 0xD88)) {
            f32 a = *(f32*)(g_Fielders + 0xC78);
            f32 b = *(f32*)(g_Fielders + 0xA10);
            mx = a >= b ? a : b;
        } else {
            f32 a = *(f32*)(g_Fielders + 0x7A8);
            f32 b = *(f32*)(g_Fielders + 0xC78);
            mx = a >= b ? a : b;
        }
        if (*(f32*)(g_Ball + 0x1A14) > lbl_3_rodata_BB8) {
            t = *(f32*)(g_Ball + 0x1A14) - lbl_3_rodata_BB8;
            slack = slack - lbl_3_rodata_BA0 * t;
            k = (s32)(lbl_3_rodata_BDC * t) + 30;
        }
        if (mx + slack > *(f32*)(g_Ball + 0x1A00)) {
            res = fn_3_378B4();
        } else {
            res = fn_3_361D8(*(f32*)(g_Ball + k * 16 + 0x354), *(f32*)(g_Ball + k * 16 + 0x35C));
            if (mode == 8 && res == 3) {
                res = 8;
            }
            if (mode == 6 && res == 5) {
                res = 6;
            }
        }
    }
    fn_3_38790(res, 0);
}

// .text:0x00038234 size:0xD0 mapped:0x806772C8
void fn_3_38234(void) {
    u8* b = g_Ball;
    if (b[0x1BC4] <= 4 || b[0x1BC4] == 7) {
        fn_3_38000();
        return;
    }
    if (*(f32*)(b + 0x19D4) > lbl_3_rodata_BE4) {
        fn_3_38304();
        return;
    }
    if (*(f32*)(b + 0x19D4) < lbl_3_rodata_B8C) {
        fn_3_38000();
        return;
    }
    if (*(f32*)(b + 0x1A48) > lbl_3_rodata_B64) {
        fn_3_38304();
        return;
    }
    if (*(f32*)(b + 0x1A00) < lbl_3_rodata_C00) {
        if (lbl_3_bss_170 >= 0x900 && lbl_3_bss_170 < 0xF00) {
            fn_3_38304();
            return;
        }
        fn_3_38000();
        return;
    }
    fn_3_38304();
}

// .text:0x00038304 size:0x48C mapped:0x80677398
extern f32 lbl_3_rodata_BB0;
extern f32 lbl_3_rodata_C04;
// NONMATCHING 92%: fielder 0x80 reads via lfsx in the original; empty-then branch shape; f-reg numbering
#if NONMATCHING
void fn_3_38304(void) {
    s32 r;
    s32 deep;
    if (*(s16*)(g_FieldingLogic + 0xB0) >= 0 &&
        *(f32*)(g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268 + 0x80) < lbl_3_rodata_B64) {
        return;
    }
    deep = 0;
    if (*(f32*)(g_Ball + 0x350) > lbl_3_rodata_BB0) {
        if (*(s16*)(g_FieldingLogic + 0xB0) >= 6) {
            deep = 1;
        } else {
            f32 reach = *(f32*)(g_Ball + 0x1A00) - lbl_3_rodata_B64;
            if (reach > *(f32*)(g_Fielders + 2 * 0x268 + 0x70) && reach > *(f32*)(g_Fielders + 3 * 0x268 + 0x70) &&
                reach > *(f32*)(g_Fielders + 4 * 0x268 + 0x70) && reach > *(f32*)(g_Fielders + 5 * 0x268 + 0x70)) {
                deep = 1;
            }
        }
    }
    if (*(f32*)(g_Ball + 0x350) > lbl_3_rodata_C04 || deep != 0) {
        s32 other;
        if (*(f32*)(g_Fielders + 6 * 0x268 + 0x80) < *(f32*)(g_Fielders + 8 * 0x268 + 0x80)) {
            if (*(f32*)(g_Fielders + 6 * 0x268 + 0x80) < *(f32*)(g_Fielders + 7 * 0x268 + 0x80)) {
                r = 6;
                other = 7;
            } else {
                r = 7;
                other = 6;
            }
        } else if (*(f32*)(g_Fielders + 8 * 0x268 + 0x80) < *(f32*)(g_Fielders + 7 * 0x268 + 0x80)) {
            r = 8;
            other = 7;
        } else {
            r = 7;
            other = 8;
        }
        if (!(lbl_3_rodata_B9C + *(f32*)(g_Fielders + r * 0x268 + 0x80) < *(f32*)(g_Fielders + other * 0x268 + 0x80))) {
            r = fn_3_36678(r, other, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C), 0);
        }
    } else {
        s32 i0 = -1;
        s32 i1 = -1;
        s32 i2 = -1;
        f32 d0 = lbl_3_rodata_BA4;
        f32 d1 = d0;
        f32 d2 = d0;
        u8* f = g_Fielders;
        s32 i;
        for (i = 0; i < 9; i++, f += 0x268) {
            f32 d = *(f32*)(f + 0x80);
            if (d0 > d) {
                d2 = d1;
                i2 = i1;
                d1 = d0;
                i1 = i0;
                d0 = d;
                i0 = i;
            } else if (d1 > d) {
                d2 = d1;
                i2 = i1;
                d1 = d;
                i1 = i;
            } else if (d2 > d) {
                d2 = d;
                i2 = i;
            }
        }
        if (*(f32*)(g_Ball + 0x350) > lbl_3_rodata_BD0) {
            if (d0 <= lbl_3_rodata_BD8 && i0 == *(s16*)(g_FieldingLogic + 0xB0)) {
                r = i0;
            } else if (d1 - d0 > lbl_3_rodata_B9C) {
                r = i0;
            } else if (d2 - d1 > lbl_3_rodata_B9C) {
                r = fn_3_36678(i0, i1, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C), 0);
            } else {
                r = Pick3Inline(i0, i1, i2, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
            }
        } else {
            r = Pick3Inline(i0, i1, i2, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
        }
    }
    fn_3_38790(r, 0);
}
#endif

#pragma dont_inline off
static inline void SetFielderActP(u8* f, int i, int state, int off) {
    int d;
    if (i != -1) {
        d = *(int*)(lbl_3_data_3C40 + off);
        f[0x1D3] = state;
        if (d >= 0) {
            g_FieldingLogic[i + 0xF8] = d;
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
}
#pragma dont_inline on

// .text:0x00038790 size:0x580 mapped:0x80677824
// NONMATCHING 98%: register allocation throughout; bss_170==0 early return emitted as beqlr; one mulli placement
#if NONMATCHING
void fn_3_38790(s32 a, s32 b) {
    s32 prev = *(s16*)(g_FieldingLogic + 0xB0);
    u8* f = g_Fielders + a * 0x268;
    s16 k;
    if (a < 0) {
        return;
    }
    if (a == prev) {
        return;
    }
    if (g_Ball[0x1BC9] == 0 && *(s16*)(g_Ball + 0x1B80) >= 0x3D8 && *(s16*)(g_Ball + 0x1B80) < 0x428) {
        if (prev == 3 && a == 5 && *(s16*)(f + 0x18C) == 2 && *(f32*)(f + 0x90) < lbl_3_rodata_BD8) {
            return;
        }
        if (prev == 5 && a == 3 && *(s16*)(f + 0x18C) == 2 && *(f32*)(f + 0x98) < lbl_3_rodata_BD8) {
            return;
        }
    }
    if (g_Ball[0x1BC9] == 0 && g_Ball[0x1BC4] <= 6 && a == 1) {
        if (lbl_3_bss_170 >= 0x800) {
            return;
        }
        if (lbl_3_bss_170 == 0) {
            return;
        }
    }
    *(s16*)(g_FieldingLogic + 0xB0) = a;
    if (b == 0) {
        SetFielderAct((s16)a, 0xF, 0x78);
    } else {
        SetFielderAct((s16)a, 0x15, 0xA8);
    }
    k = *(s16*)(f + 0x18C);
    if (k >= 0 && k <= 5) {
        if (k >= 0 && k <= 3) {
            if (((s16*)(g_FieldingLogic + 0xD0))[k] == a) {
                ((s16*)(g_FieldingLogic + 0xD0))[k] = -1;
                g_FieldingLogic[k + 0x101] = 0;
            }
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            if (f[0x1D3] == 1) {
                SetFielderActP(f, a, 12, 0x60);
            }
        } else if (k == 5) {
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            *(s16*)(g_FieldingLogic + 0xD8) = -1;
            g_FieldingLogic[0x105] = 0;
            if (f[0x1D3] == 14) {
                SetFielderActP(f, a, 12, 0x60);
            }
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) == *(s16*)(g_FieldingLogic + 0xBE)) {
        *(s16*)(g_FieldingLogic + 0xBE) = -1;
    }
    if (prev >= 0) {
        if (prev >= 6) {
            SetFielderAct(prev, 0x10, 0x80);
        } else if (g_Ball[0x1BC9] == 0) {
            u8* p = g_Fielders + prev * 0x268;
            if (*(f32*)(p + 0x70) > lbl_3_rodata_B78 + *(f32*)(f + 0x70)) {
                SetFielderAct(prev, 0x10, 0x80);
            } else if (*(s16*)(p + 0x18C) == 6) {
                SetFielderAct(prev, 0xB, 0x58);
            } else {
                SetFielderAct(prev, 0xC, 0x60);
                g_Fielders[prev * 0x268 + 0x1D5] = 4;
            }
        } else {
            SetFielderAct(prev, 0xC, 0x60);
            g_Fielders[prev * 0x268 + 0x1D5] = 4;
        }
    }
    if (*(s16*)(g_Ball + 0x1B66) < 0x1E) {
        *(s16*)(g_FieldingLogic + 0xDA) = 0x14;
    } else {
        *(s16*)(g_FieldingLogic + 0xDA) = 0x2D;
    }
}
#endif

// .text:0x00038D10 size:0x2E8 mapped:0x80677DA4
// NONMATCHING 99%: FieldingLogic+0xB0 reg r4/r5 swapped; SetFielderAct state/table regs (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_38D10(void) {
    int r;
    int i;
    f32 lim;
    f32 x;
    f32 z;
    if (*(s16*)(g_Ball + 0x1B7A) == 0 &&
        (*(s16*)(g_FieldingLogic + 0xB0) == 3 || *(s16*)(g_FieldingLogic + 0xB0) == 5)) {
        u8* f = g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
        if (*(f32*)(f + 0x80) < *(f32*)(f + 0xE8)) {
            r = *(s16*)(g_FieldingLogic + 0xB0);
            goto chosen;
        }
    }
    if ((g_Fielders[3 * 0x268 + 0x1DB] == 0 || g_Fielders[5 * 0x268 + 0x1DB] == 0) && *(s16*)(g_Ball + 0x1B7A) == 0) {
        x = *(f32*)(g_Ball + 0x348);
        z = *(f32*)(g_Ball + 0x34C);
    } else {
        lim = lbl_3_rodata_B80 * (*(f32*)(g_Fielders + 3 * 0x268 + 0x70) + *(f32*)(g_Fielders + 5 * 0x268 + 0x70));
        for (i = 1; i < 120; i += 3) {
            if (*(f32*)(g_Ball + i * 16 + 0x360) > lim) {
                break;
            }
        }
        x = *(f32*)(g_Ball + i * 16 + 0x354);
        z = *(f32*)(g_Ball + i * 16 + 0x35C);
    }
    r = fn_3_37114(3, 5, 1, x, z);
    if (r < 0) {
        if (g_Ball[0x1BBE] >= 2 && lbl_3_bss_16C > 0xA00 && lbl_3_bss_16C < 0xE00) {
            g_FieldingLogic[0x13A] = 0;
        }
    } else {
    chosen:
        if (r == 3) {
            fn_3_38790(3, 1);
            SetFielderAct(5, 12, 0x60);
        } else {
            fn_3_38790(5, 1);
            SetFielderAct(3, 12, 0x60);
        }
        g_FieldingLogic[0x13A] = 0;
    }
}
#endif

// .text:0x00038FF8 size:0x3B8 mapped:0x8067808C
extern f32 lbl_3_rodata_C08;
// NONMATCHING 97%: goto-target layout leaves the original's dead b instructions out; one mulli scheduled early
#if NONMATCHING
void fn_3_38FF8(void) {
    u8* f = g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
    f32 lim = *(f32*)(f + 0x70);
    s32 i;
    s32 r;
    for (i = 1; i < 60; i += 3) {
        if (*(f32*)(g_Ball + i * 16 + 0x360) > lim) {
            break;
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) != 1) {
        if (i <= 1) {
            goto keep_second;
        }
        if (*(f32*)(f + 0x7C) < lbl_3_rodata_C08) {
            if (lbl_3_bss_16C >= 0 &&
                fn_3_9FCF8(lbl_3_bss_16C, fn_3_9FB8C(*(f32*)g_Ball - *(f32*)f, *(f32*)(g_Ball + 8) - *(f32*)(f + 8))) < 0x100) {
                goto keep_first;
            }
            if (*(s16*)(g_FieldingLogic + 0xB0) >= 2 && *(s16*)(g_FieldingLogic + 0xB0) <= 5 &&
                (g_Ball[0x1BC4] == 2 || g_Ball[0x1BC4] == 3)) {
                goto keep_first;
            }
        }
    }
    if (g_Fielders[*(s16*)(g_FieldingLogic + 0xB0) * 0x268 + 0x1DB] == 0 ||
        g_Fielders[*(s16*)(g_FieldingLogic + 0xB2) * 0x268 + 0x1DB] == 0) {
        r = fn_3_36678(*(s16*)(g_FieldingLogic + 0xB0), *(s16*)(g_FieldingLogic + 0xB2), *(f32*)(g_Ball + 0x348),
                       *(f32*)(g_Ball + 0x34C), 3);
    } else {
        r = fn_3_36678(*(s16*)(g_FieldingLogic + 0xB0), *(s16*)(g_FieldingLogic + 0xB2), *(f32*)(g_Ball + i * 16 + 0x354),
                       *(f32*)(g_Ball + i * 16 + 0x35C), 3);
    }
    if (r >= 0) {
        if (r == *(s16*)(g_FieldingLogic + 0xB2)) {
            goto keep_second;
        }
        if (r == *(s16*)(g_FieldingLogic + 0xB0)) {
            goto keep_first;
        }
    }
    if (*(s16*)(g_Ball + 0x1B66) > 0x5A) {
        if (*(s16*)(g_Ball + 0x1B72) >= 0 ||
            ((f32*)(g_Fielders + 0x80))[*(s16*)(g_FieldingLogic + 0xB0) * 0x9A] <=
                ((f32*)(g_Fielders + 0x80))[*(s16*)(g_FieldingLogic + 0xB2) * 0x9A]) {
        keep_first:
            g_FieldingLogic[0x139] = 0;
            if (*(s16*)(g_FieldingLogic + 0xB0) == 0) {
                return;
            }
        } else {
        keep_second:
            if (g_FieldingLogic[0x13A] != 0 &&
                (*(s16*)(g_FieldingLogic + 0xB2) == 3 || *(s16*)(g_FieldingLogic + 0xB2) == 5)) {
                fn_3_38D10();
                if (g_FieldingLogic[0x13A] != 0) {
                    if (!(*(f32*)(g_Ball + 0x1A00) - lbl_3_rodata_B78 >
                          *(f32*)(g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268 + 0x70))) {
                        return;
                    }
                    fn_3_38790(*(s16*)(g_FieldingLogic + 0xB2), 1);
                }
            } else {
                fn_3_38790(*(s16*)(g_FieldingLogic + 0xB2), 1);
            }
        }
        g_FieldingLogic[0x139] = 0;
        *(s16*)(g_FieldingLogic + 0xB2) = *(s16*)(g_FieldingLogic + 0xB4);
        *(s16*)(g_FieldingLogic + 0xB4) = -1;
    }
}
#endif

// .text:0x000393B0 size:0x4A8 mapped:0x80678444
extern f32 lbl_3_rodata_B60;
extern f32 lbl_3_rodata_B74;
// NONMATCHING 95%: the original places the B2==r tail block at the function end; one mulli scheduled differently
#if NONMATCHING
void fn_3_393B0(void) {
    u8* base = g_Fielders;
    u8* f = base + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
    s32 i;
    s32 r;
    if (*(s16*)(g_Ball + 0x1B66) < 0x3C) {
        if (*(s16*)(g_FieldingLogic + 0xB0) == 3) {
            for (i = 2; i < 30; i += 2) {
                if (*(f32*)(g_Ball + i * 16 + 0x360) > *(f32*)(base + 2 * 0x268 + 0x70)) {
                    break;
                }
            }
            if (i < 30 && *(s16*)(g_Ball + 0x1B80) > *(s16*)(base + 2 * 0x268 + 0x180) &&
                *(s16*)(g_Ball + 0x1B80) < *(s16*)(f + 0x180) &&
                *(f32*)(base + 2 * 0x268 + 0x70) > lbl_3_rodata_B60 + *(f32*)(g_Ball + 0x1A00)) {
                if (fn_3_36678(2, 3, *(f32*)(g_Ball + i * 16 + 0x354), *(f32*)(g_Ball + i * 16 + 0x35C), 0) == 2) {
                    fn_3_38790(2, 0);
                    return;
                }
            }
        } else if (*(s16*)(g_FieldingLogic + 0xB0) == 5) {
            for (i = 2; i < 30; i += 2) {
                if (*(f32*)(g_Ball + i * 16 + 0x360) > *(f32*)(base + 4 * 0x268 + 0x70)) {
                    break;
                }
            }
            if (i < 30 && *(s16*)(g_Ball + 0x1B80) < *(s16*)(base + 4 * 0x268 + 0x180) &&
                *(s16*)(g_Ball + 0x1B80) > *(s16*)(f + 0x180) &&
                *(f32*)(base + 4 * 0x268 + 0x70) > lbl_3_rodata_B60 + *(f32*)(g_Ball + 0x1A00)) {
                if (fn_3_36678(4, 5, *(f32*)(g_Ball + i * 16 + 0x354), *(f32*)(g_Ball + i * 16 + 0x35C), 0) == 4) {
                    fn_3_38790(4, 0);
                    return;
                }
            }
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xB2) >= 0) {
        if (*(s16*)(g_FieldingLogic + 0xB0) <= 5 && *(s16*)(g_FieldingLogic + 0xB2) >= 6) {
            f32 px;
            f32 pz;
            r = -1;
            px = *(f32*)(g_Ball + 0x534);
            pz = *(f32*)(g_Ball + 0x53C);
            if (*(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_BBC || g_Ball[0x1BC9] == 3) {
                if (*(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_B24 && g_Ball[0x1BC9] == 0 && g_Ball[0x1BBE] <= 1 &&
                    *(f32*)(f + 0x70) > *(f32*)(g_Ball + 0x1A00) && *(f32*)(f + 0x7C) < lbl_3_rodata_B64) {
                    SetFielderAct(*(s16*)(g_FieldingLogic + 0xB2), 12, 0x60);
                    *(s16*)(g_FieldingLogic + 0xB2) = -1;
                }
                r = fn_3_36678(*(s16*)(g_FieldingLogic + 0xB0), *(s16*)(g_FieldingLogic + 0xB2),
                               px, pz, 0);
            } else if (lbl_3_rodata_B78 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x1A00)) {
                r = fn_3_36678(*(s16*)(g_FieldingLogic + 0xB0), *(s16*)(g_FieldingLogic + 0xB2),
                               px, pz, 0);
            }
            if (*(s16*)(g_FieldingLogic + 0xB2) != r) {
                return;
            }
            fn_3_38790(*(s16*)(g_FieldingLogic + 0xB2), 1);
            *(s16*)(g_FieldingLogic + 0xB2) = -1;
        }
    } else if ((*(s16*)(g_Ball + 0x1B7A) == 1 || *(s16*)(g_Ball + 0x1B7A) == -1 || g_Ball[0x1BC9] == 3) &&
               *(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_B74 &&
               *(f32*)(g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268 + 0x74) > lbl_3_rodata_BD8) {
        fn_3_37610(0x1E);
    }
}
#endif

// .text:0x00039858 size:0x56C mapped:0x806788EC
#pragma dont_inline off
/* SetFielderAct that also records the fielder in FieldingLogic+0xBC */
static inline void SetFielderActTag(int i, int state, int off) {
    u8* f = g_Fielders + i * 0x268;
    int d;
    if (i != -1) {
        d = *(int*)(lbl_3_data_3C40 + off);
        f[0x1D3] = state;
        if (d >= 0) {
            g_FieldingLogic[i + 0xF8] = d;
        }
        *(s16*)(g_FieldingLogic + 0xBC) = i;
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
}
#pragma dont_inline on
extern f32 lbl_3_data_4848;
// NONMATCHING 94%: early-return/goto block layout (the original moves the 38790 tail to the end); bss_170 read via addi+lha
#if NONMATCHING
void fn_3_39858(void) {
    s32 r = *(s16*)(g_FieldingLogic + 0xB0);
    u8* f = g_Fielders + r * 0x268;
    s16 cur;
    s32 k;
    f32 t;
    if (*(s16*)(g_FieldingLogic + 0xB2) < 0) {
        if (g_FieldingLogic[0x139] == 0 && *(s16*)(g_FieldingLogic + 0xDA) == 0) {
            fn_3_38304();
        }
        return;
    }
    if (r <= 5 && *(s16*)(g_FieldingLogic + 0xB2) >= 6) {
        if (g_Ball[0x1BC3] == 2 || g_Ball[0x1BC3] == 5) {
            if (*(s16*)(g_FieldingLogic + 0xB2) !=
                fn_3_36678(r, *(s16*)(g_FieldingLogic + 0xB2), *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C), 0)) {
                return;
            }
        } else if (!(lbl_3_rodata_B78 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x1A00))) {
            return;
        }
        fn_3_38790(*(s16*)(g_FieldingLogic + 0xB2), 1);
        *(s16*)(g_FieldingLogic + 0xB2) = -1;
        return;
    }
    if (g_FieldingLogic[0x139] == 0) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1B66) < lbl_3_data_484C[3]) {
        return;
    }
    cur = lbl_3_bss_170;
    if (cur < 0 || !(*(u16*)(g_FieldingLogic + 0x148) & 0x200)) {
        if (*(f32*)(g_Ball + 0x1A00) < (f32)lbl_3_data_484C[5]) {
            return;
        }
        t = *(f32*)(g_Ball + 0x350) - (f32)lbl_3_data_484C[7];
        if (t > (f32)lbl_3_data_484C[6]) {
            t = (f32)lbl_3_data_484C[6];
        }
        if (*(f32*)(g_Ball + 0x1A00) < t) {
            return;
        }
    }
    if (!(((f32*)(g_Fielders + 0x80))[r * 0x9A] < lbl_3_data_4848)) {
        if (((f32*)(g_Fielders + 0x80))[*(s16*)(g_FieldingLogic + 0xB2) * 0x9A] < lbl_3_data_4848) {
            r = *(s16*)(g_FieldingLogic + 0xB2);
        } else {
            if (*(s16*)(g_Ball + 0x1B66) < lbl_3_data_484C[4]) {
                if (cur <= 0) {
                    return;
                }
                for (k = 1; k < lbl_3_data_484C[8]; k++) {
                    if ((&lbl_3_bss_170)[k] <= 0 || fn_3_9FCF8(cur, (&lbl_3_bss_170)[k]) > 0x200) {
                        break;
                    }
                }
                if (k < lbl_3_data_484C[8]) {
                    return;
                }
            }
            r = fn_3_37114(*(s16*)(g_FieldingLogic + 0xB0), *(s16*)(g_FieldingLogic + 0xB2), 0,
                           lbl_3_rodata_B80 * (((f32*)(g_Fielders + 0x14))[*(s16*)(g_FieldingLogic + 0xB0) * 0x9A] +
                                               ((f32*)(g_Fielders + 0x14))[*(s16*)(g_FieldingLogic + 0xB2) * 0x9A]),
                           lbl_3_rodata_B80 * (((f32*)(g_Fielders + 0x1C))[*(s16*)(g_FieldingLogic + 0xB0) * 0x9A] +
                                               ((f32*)(g_Fielders + 0x1C))[*(s16*)(g_FieldingLogic + 0xB2) * 0x9A]));
        }
    }
    if (r < 0) {
        return;
    }
    if (r == *(s16*)(g_FieldingLogic + 0xB2)) {
        if (*(s16*)(g_FieldingLogic + 0xBC) < 0) {
            SetFielderActTag(*(s16*)(g_FieldingLogic + 0xB0), 0x18, 0xC0);
        } else {
            SetFielderAct(*(s16*)(g_FieldingLogic + 0xB0), 0xC, 0x60);
        }
        SetFielderAct(*(s16*)(g_FieldingLogic + 0xB2), 0x15, 0xA8);
        *(s16*)(g_FieldingLogic + 0xB0) = *(s16*)(g_FieldingLogic + 0xB2);
    } else {
        if (*(s16*)(g_FieldingLogic + 0xBC) < 0) {
            SetFielderActTag(*(s16*)(g_FieldingLogic + 0xB2), 0x18, 0xC0);
        } else {
            SetFielderAct(*(s16*)(g_FieldingLogic + 0xB2), 0xC, 0x60);
        }
        SetFielderAct(*(s16*)(g_FieldingLogic + 0xB0), 0x15, 0xA8);
    }
    *(s16*)(g_FieldingLogic + 0xB2) = -1;
    g_FieldingLogic[0x139] = 0;
}
#endif

// .text:0x00039DC4 size:0xEC mapped:0x80678E58
void fn_3_39DC4(void) {
    int i;
    u8* f;
    for (i = 0; i < 9; i++) {
        g_FieldingLogic[i + 0xF8] = 0;
        f = g_Fielders + i * 0x268;
        if (i != -1) {
            f[0x1D3] = 0;
            if (*(int*)lbl_3_data_3C40 >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)lbl_3_data_3C40;
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
        *(f32*)(f + 0x20) = 10000.0f;
        *(f32*)(f + 0x24) = 0.0f;
    }
    *(s16*)(g_FieldingLogic + 0xB0) = -1;
    *(s16*)(g_FieldingLogic + 0xB2) = -1;
    *(s16*)(g_FieldingLogic + 0xB4) = -1;
    *(s16*)(g_FieldingLogic + 0xBE) = -1;
    g_FieldingLogic[0x139] = 0;
    *(s16*)(g_FieldingLogic + 0xD0) = -1;
    g_FieldingLogic[0x101] = 0;
    *(s16*)(g_FieldingLogic + 0xD2) = -1;
    g_FieldingLogic[0x102] = 0;
    *(s16*)(g_FieldingLogic + 0xD4) = -1;
    g_FieldingLogic[0x103] = 0;
    *(s16*)(g_FieldingLogic + 0xD6) = -1;
    g_FieldingLogic[0x104] = 0;
    fn_3_37610(0x78);
}

// .text:0x00039EB0 size:0x34C mapped:0x80678F44
extern f32 lbl_3_rodata_C0C;
// NONMATCHING 86%: early returns vs the original's nested condition chain; fielder reset loop strength-reduced differently
#if NONMATCHING
void fn_3_39EB0(void) {
    s32 ready = 1;
    u8 st;
    s16 phase;
    s16 cur;
    s32 reset;
    s32 i;
    u8* f;
    if (g_d_GameSettings[7] == 2 && g_GameLogic[0x121] == 0xC) {
        return;
    }
    if (g_Ball[0x1BD1] != 0) {
        return;
    }
    st = g_Ball[0x1BC9];
    if (st == 1) {
        return;
    }
    phase = *(s16*)(g_Ball + 0x1B7A);
    if (phase == 0 && *(f32*)(g_Ball + 0x19D4) > lbl_3_rodata_BE4) {
        if (*(s16*)(g_Ball + 0x1B66) < lbl_3_data_49DC[0x29]) {
            return;
        }
    } else if (*(s16*)(g_Ball + 0x1B66) < lbl_3_data_49DC[0x2A]) {
        return;
    }
    if (st == 2 && *(s16*)(g_Ball + 0x1B62) > 0 && *(s16*)(g_Ball + 0x1B8A) >= 0) {
        if (*(s16*)(g_Ball + 0x1B6C) == 2 && *(s16*)(g_FieldingLogic + 0xC4) != 6) {
            fn_3_35E1C();
        }
        return;
    }
    if ((*(s16*)(g_FieldingLogic + 0xDA) = *(s16*)(g_FieldingLogic + 0xDA) - 1) > 0) {
        ready = 0;
    } else {
        *(s16*)(g_FieldingLogic + 0xDA) = 0;
    }
    if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142] == 0 && (*(u16*)(g_FieldingLogic + 0x148) & 0x40)) {
        return;
    }
    cur = *(s16*)(g_FieldingLogic + 0xB0);
    if (cur >= 0 && g_Fielders[cur * 0x268 + 0x205] != 0) {
        return;
    }
    if (ready == 0 || g_FieldingLogic[0x137] != 0 || g_Ball[0x1BF0] != 0) {
        return;
    }
    reset = 0;
    if (cur < 0 && st == 3) {
        reset = 1;
    }
    if (g_FieldingLogic[0x13B] != 0 || reset != 0) {
        f = g_Fielders;
        for (i = 0; i < 9; i++, f += 0x268) {
            g_FieldingLogic[i + 0xF8] = 0;
            SetFielderAct2(i, *(int*)lbl_3_data_3C40, 0);
            *(f32*)(f + 0x20) = lbl_3_rodata_C0C;
            *(f32*)(f + 0x24) = lbl_3_rodata_B20;
        }
        *(s16*)(g_FieldingLogic + 0xB0) = -1;
        *(s16*)(g_FieldingLogic + 0xB2) = -1;
        *(s16*)(g_FieldingLogic + 0xB4) = -1;
        *(s16*)(g_FieldingLogic + 0xBE) = -1;
        g_FieldingLogic[0x139] = 0;
        *(s16*)(g_FieldingLogic + 0xD0) = -1;
        g_FieldingLogic[0x101] = 0;
        *(s16*)(g_FieldingLogic + 0xD2) = -1;
        g_FieldingLogic[0x102] = 0;
        *(s16*)(g_FieldingLogic + 0xD4) = -1;
        g_FieldingLogic[0x103] = 0;
        *(s16*)(g_FieldingLogic + 0xD6) = -1;
        g_FieldingLogic[0x104] = 0;
        fn_3_37610(0x78);
        if (*(s16*)(g_FieldingLogic + 0xB0) >= 0) {
            g_FieldingLogic[0x13B] = 0;
        }
    } else if (*(s16*)(g_FieldingLogic + 0xB4) >= 0) {
        fn_3_38FF8();
    } else if (g_FieldingLogic[0x13A] != 0 && (cur == 3 || cur == 5)) {
        fn_3_38D10();
    } else if (phase == 0) {
        fn_3_39858();
    } else {
        fn_3_393B0();
    }
}
#endif

// .text:0x0003A1FC size:0x38 mapped:0x80679290
void fn_3_3A1FC(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(s16*)(f + 0x1B6) != 0) {
        *(f32*)(f + 0x50) = *(f32*)(f + 0x54);
    } else {
        *(f32*)(f + 0x50) = lbl_3_rodata_1498;
    }
}

// .text:0x0003A234 size:0x350 mapped:0x806792C8
extern f32 lbl_3_data_46F0;
extern f32 lbl_3_data_46F4;
extern u8 lbl_3_data_21A14[];
extern int checkFieldingStat(int, int, int);
// NONMATCHING 98%: extsh on the radToShortAngle results; 0x2C50 slot pointer reached via lwzu in the original
#if NONMATCHING
void fn_3_3A234(int i) {
    u8* f = g_Fielders + i * 0x268;
    s32 who = i;
    f32 cap = *(f32*)(f + 0x58);
    s16 rel;
    s32 n;
    s32 k;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    if (*(s16*)(f + 0x1A0) == 0) {
        s16 a = radToShortAngle(*(f32*)(f + 0x64));
        rel = fn_3_9FE6C_normalizeAngle(a - radToShortAngle(*(f32*)(f + 0x48)));
        if (rel < 0x200) {
            f[0x1F3] = 0;
        } else if (rel < 0x600) {
            f[0x1F3] = 3;
        } else if (rel < 0xA00) {
            f[0x1F3] = 1;
        } else if (rel < 0xE00) {
            f[0x1F3] = 2;
        } else {
            f[0x1F3] = 0;
        }
        if (f[0x1E3] != 1) {
            if (f[0x1F3] == 1) {
                f[0x1F3] = 5;
            } else {
                f[0x1F3] = 4;
            }
        }
    }
    if (f[0x1F3] == 4 || f[0x1F3] == 5) {
        *(f32*)(f + 0x50) = lbl_3_rodata_B80 * *(f32*)(f + 0x5C) + *(f32*)(f + 0x50);
    } else {
        *(f32*)(f + 0x50) = *(f32*)(f + 0x50) + *(f32*)(f + 0x5C);
    }
    n = f[0x217];
    for (k = 0; k < n; k++) {
        cap *= lbl_3_data_46F4;
    }
    if (*(f32*)(f + 0x50) > cap) {
        *(f32*)(f + 0x50) = cap;
    }
    if (*(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14) == i) {
        *(f32*)(f + 0x50) = *(f32*)(*(u8**)(g_FieldingLogic + 0x70) + 8) * cap;
    }
    if (*(s16*)(g_Ball + 0x1B78) == i && checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 0xB) != 0) {
        u8** slot = (u8**)(lbl_8036E548 + 0x2C50) + who;
        *(f32*)(f + 0x50) = *(f32*)(f + 0x50) * lbl_3_data_46F0;
        (*slot)[0x27A] = 1;
        if (*(s16*)(f + 0x1A0) == 1) {
            fn_3_1682AC(((int*)lbl_8036E548)[who + 0xB14], 0xB);
        }
    }
    if (g_Minigame[0x1A2A] == 6) {
        if (*(s8*)(g_Minigame + 0x1D6D) == f[0x20D]) {
            *(f32*)(f + 0x50) = *(f32*)(f + 0x50) * *(f32*)(lbl_3_data_21A14 + 0x18);
        }
        if (*(s8*)(g_Minigame + 0x1D74) == f[0x20D]) {
            *(f32*)(f + 0x50) = *(f32*)(f + 0x50) * **(f32**)(g_Minigame + 0x1D4C);
        }
    }
}
#endif

// .text:0x0003A584 size:0x574 mapped:0x80679618
#pragma dont_inline off
/* same body as fn_3_258D8, which the original inlines into fn_3_3A584 */
static inline int StartJumpInline(int i) {
    u8* f = g_Fielders + i * 0x268;
    int type;
    Ent16* t;
    int n;
    int k;
    f32 sc;
    if ((*(u8**)(g_FieldingLogic + 0x8C))[2] == 0) {
        return 0;
    }
    if (f[0x25A] != 0) {
        return 0;
    }
    type = f[0x1CC];
    f[0x203] = 1;
    *(f32*)(f + 0x15C) = lbl_3_rodata_B20;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            i = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            i = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    *(f32*)(f + 0x164) = ((Ent16*)lbl_3_data_4884)[type].a;
    t = &((Ent16*)lbl_3_data_4884)[type];
    sc = t->c;
    *(f32*)(f + 0x160) = *(f32*)(f + 0x38) * lbl_3_rodata_B24 * sc;
    *(f32*)(f + 0x168) = *(f32*)(f + 0x3C) * lbl_3_rodata_B24 * sc;
    k = (int)t->d;
    n = (int)(*(f32*)(f + 0x164) / t->b);
    *(s16*)(f + 0x1B0) = n + 1;
    *(s16*)(f + 0x1AE) = (n + n) + k + 2;
    f[0x204] = 0;
    if (type != 0) {
        fn_3_1682AC(((int*)lbl_8036E548)[i + 0xB14], 6);
    }
    (*(u8**)(g_FieldingLogic + 0x8C))[2] = 0;
    return 1;
}
#pragma dont_inline on
extern f32 shortAngleToRad_Capped(s16);
extern f64 cos(f64);
extern f64 sin(f64);
extern f32 lbl_3_rodata_B18;
extern f32 lbl_3_rodata_B1C;
// NONMATCHING 95%: inlined fn_3_258D8 body schedules its table reads differently (lfsx); 0x2C50 slot via lwzu; calls fn_3_261E8 through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_3A584(int i) {
    u8* f = g_Fielders + i * 0x268;
    s32 who = i;
    s32 stop = 0;
    s16 ang;
    u8* t;
    f32 spd;
    f32 pos[3];
    s32 r;
    if (g_d_GameSettings[0x11] != 0) {
        if (i == 0) {
            who = *(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1904) + 0x18CC);
        } else {
            who = *(s8*)(g_Minigame + i + 0x18F2);
        }
    }
    if (f[0x252] != 0) {
        /* TODO: fn_3_261E8 takes the fielder index; its prototype (other range) is still (void) */
        ((void (*)(int))fn_3_261E8)(i);
        *(s16*)(f + 0x1A2) = 0;
        goto done;
    }
    ang = *(s16*)(f + 0x19E);
    if (StartJumpInline(i) != 0) {
        goto done;
    }
    t = *(u8**)(g_FieldingLogic + 0x70);
    if (t[0x1A] == 4 && *(s16*)(t + 0x14) == i) {
        *(f32*)(f + 0x50) = *(f32*)(t + 8) * *(f32*)(f + 0x58);
        *(f32*)(f + 0x30) = *(f32*)t * *(f32*)(f + 0x50);
        *(f32*)(f + 0x34) = *(f32*)(t + 4) * *(f32*)(f + 0x50);
        goto move;
    }
    if (ang < 0) {
        if (*(s16*)(t + 0x14) == i) {
            *(f32*)(f + 0x50) = *(f32*)(t + 8) * *(f32*)(f + 0x58);
            if (*(s16*)(f + 0x1A2) < 0x7FFE) {
                *(s16*)(f + 0x1A2) = *(s16*)(f + 0x1A2) + 1;
            } else {
                *(s16*)(f + 0x1A2) = 0x7FFF;
            }
            goto run;
        }
        if (*(s16*)(f + 0x1B6) != 0) {
            *(f32*)(f + 0x50) = *(f32*)(f + 0x54);
        } else {
            *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        }
        if (*(f32*)(f + 0x50) > lbl_3_rodata_B20) {
            goto run;
        }
        f[0x1E3] = 1;
        goto done;
    }
    if (*(s16*)(f + 0x1A2) < 0x7FFE) {
        *(s16*)(f + 0x1A2) = *(s16*)(f + 0x1A2) + 1;
    } else {
        *(s16*)(f + 0x1A2) = 0x7FFF;
    }
    if (*(s16*)(g_Ball + 0x1B78) == i && *(s16*)(f + 0x1A2) <= lbl_3_data_49DC[0]) {
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        f[0x1E3] = 1;
    } else {
        *(f32*)(f + 0x64) = shortAngleToRad_Capped(ang);
        if (f[0x1E3] == 4 || f[0x1E3] == 1) {
            *(f32*)(f + 0xBC) = *(f32*)(f + 0x64);
            *(f32*)(f + 0xC0) = *(f32*)(f + 0x64);
            *(f32*)(f + 0xC4) = *(f32*)(f + 0x64);
            *(f32*)(f + 0xC8) = *(f32*)(f + 0x64);
            *(f32*)(f + 0xCC) = *(f32*)(f + 0x64);
        }
        fn_3_3A234(i);
        f[0x1E3] = 0;
        f[0x1E4] = 0;
    }
    if (!(*(f32*)(f + 0x50) > lbl_3_rodata_B20)) {
        goto done;
    }
run:
    spd = *(f32*)(f + 0x50);
    if (*(s16*)(g_Ball + 0x1B78) == i && checkFieldingStat(*(int*)(g_GameLogic + 8), *(s16*)(f + 0x178), 0xB) != 0) {
        u8** slot = (u8**)(lbl_8036E548 + 0x2C50) + who;
        spd *= lbl_3_data_46F0;
        (*slot)[0x27A] = 1;
        if (*(s16*)(f + 0x1A0) == 1) {
            fn_3_1682AC(((int*)lbl_8036E548)[who + 0xB14], 0xB);
        }
    }
    *(f32*)(f + 0x30) = spd * (f32)cos(*(f32*)(f + 0x64));
    *(f32*)(f + 0x34) = spd * (f32)sin(*(f32*)(f + 0x64));
move:
    r = fn_3_51798(i, pos);
    if (r == 1) {
        stop = 1;
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        *(f32*)(f + 0x30) = lbl_3_rodata_B20;
        *(f32*)(f + 0x34) = lbl_3_rodata_B20;
    } else if (r == 2) {
        if (pos[0] > lbl_3_rodata_B18 || pos[0] < lbl_3_rodata_B1C) {
            *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        } else {
            *(f32*)(f + 0x30) = lbl_3_rodata_B20;
            *(f32*)(f + 0x34) = lbl_3_rodata_B20;
            *(f32*)f = pos[0];
            *(f32*)(f + 8) = pos[2];
        }
        stop = 1;
    } else {
        *(f32*)f = *(f32*)f + *(f32*)(f + 0x30);
        *(f32*)(f + 8) = *(f32*)(f + 8) + *(f32*)(f + 0x34);
    }
    if (stop != 0) {
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xE) = 0;
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x10) = 0;
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x14) = -1;
        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0x16) = 0;
    }
done:
    *(f32*)(f + 0x14) = *(f32*)f;
    *(f32*)(f + 0x1C) = *(f32*)(f + 8);
    f[0x1F0] = 1;
}
#endif

// .text:0x0003AAF8 size:0xF8 mapped:0x80679B8C
void fn_3_3AAF8(int i) {
    u8* f;
    int v;
    u8* l;
    f = g_Fielders + i * 0x268;
    v = lbl_3_bss_170;
    l = g_FieldingLogic;
    if (l[0x10E] != 0) {
        v = -1;
    }
    *(s16*)(f + 0x19E) = v;
    if (g_GameLogic[*(s32*)(g_GameLogic + 0x10) + 0x144] == 0 && v >= 0 && *(s16*)(f + 0x1A0) > 0xA) {
        *(s16*)(g_FieldingLogic + 0xCC) = -1;
    }
    if (v >= 0) {
        u8* t = *(u8**)(g_FieldingLogic + 0x70);
        u8 k = t[0x1A];
        if (k != 3 && k != 4) {
            if (*(u16*)(g_FieldingLogic + 0x14A) & 0x200) {
                *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = 0;
            }
            if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0 && g_Practice[0x1C5] != 0) {
                *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = 0;
            }
        }
    }
}

// .text:0x0003ABF0 size:0xD0 mapped:0x80679C84
void fn_3_3ABF0(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 c = *(s16*)(g_FieldingLogic + 0xB0);
    u8* cf = g_Fielders + c * 0x268;
    u8* g;
    if (*(s16*)(g_Ball + 0x1B66) < lbl_3_data_484C[0]) {
        return;
    }
    if (g_FieldingLogic[0x139] != 0) {
        return;
    }
    if (!((cf[0x256] == 1 && ((f32*)(f + 0x84))[c] < lbl_3_rodata_B70) || (cf[0x252] != 0 && cf[0x25B] == 0))) {
        return;
    }
    g = g_Fielders;
    g += i * 0x268;
    *(f32*)(g + 0x14) = *(f32*)(f + 0x0);
    *(f32*)(g + 0x18) = *(f32*)(f + 0x4);
    *(f32*)(g + 0x1C) = *(f32*)(f + 0x8);
    *(f32*)(g + 0x30) = lbl_3_rodata_B20;
    *(f32*)(g + 0x34) = lbl_3_rodata_B20;
    *(f32*)(g + 0x50) = lbl_3_rodata_B20;
    *(f32*)(g + 0x68) = lbl_3_rodata_B20;
}

// .text:0x0003ACC0 size:0x174 mapped:0x80679D54
void fn_3_3ACC0(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(s16*)(g_Ball + 0x1B8E) < 0) {
        if (i == *(s16*)(g_FieldingLogic + 0xB0) && g_FieldingLogic[0x139] == 0 && *(s16*)(g_Ball + 0x1B66) >= lbl_3_data_484C[0]) {
            if (*(s16*)(g_Ball + 0x1B66) < lbl_3_data_484C[1] && (lbl_3_bss_170 < 0 || !(*(u16*)(g_FieldingLogic + 0x148) & 0x200)) &&
                (g_d_GameSettings[7] != 2 || *(s8*)(g_Practice + 0x1C2) < 0 || g_Practice[0x1C5] == 0)) {
                if ((f[0x201] == 0 || i < 6 || i > 8 || g_Ball[0x1BBE] != 0) && lbl_3_bss_16C >= 0) {
                    s16 t = *(s16*)(f + 0x19A);
                    if (t < 0) {
                        if (*(s16*)(g_Ball + 0x1B66) > f[0x1D2] + 3) {
                            goto blk;
                        }
                    } else {
                        if (fn_3_9FCF8(lbl_3_bss_16C, t) < lbl_3_data_484C[2]) {
                            goto blk;
                        }
                    }
                }
            } else {
                goto blk;
            }
        }
        return;
    } else {
    blk:
        f[0x1FF] = 2;
        f[0x201] = 0;
    }
}

// .text:0x0003AE34 size:0x53C mapped:0x80679EC8
// NONMATCHING 96%: fielder pointer kept in r29 vs r28; calls fn_3_261E8/fn_3_433E0 through casts until their prototypes gain the index arg
#if NONMATCHING
void fn_3_3AE34(int i) {
    s32 off = i * 0x268;
    u8* f = g_Fielders + off;
    s32 tgt;
    s16 k;
    if (*(s16*)(g_Ball + 0x1B66) <= 0) {
        return;
    }
    if (f[0x1FF] == 0) {
        f[0x201] = 0;
        if (*(s16*)(g_FieldingLogic + 0xB6) == i && i >= 6 && i <= 8) {
            f[0x201] = 1;
        }
        f[0x1FF] = 1;
    }
    if (g_d_GameSettings[7] == 2 && g_GameLogic[0x121] == 0xC) {
        return;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    case 1:
        break;
    default:
        if (f[0x1FF] == 1) {
            if (*(s16*)(g_Ball + 0x1B66) == f[0x1D2]) {
                fn_3_447C4(i);
            }
            if (f[0x252] != 0) {
                /* TODO: fn_3_261E8 / fn_3_433E0 take the fielder index; prototypes (other range) are still (void) */
                ((void (*)(int))fn_3_261E8)(i);
                *(s16*)(f + 0x1A2) = 0;
                f[0x1FF] = 2;
            } else {
                ((void (*)(int))fn_3_433E0)(i);
            }
            fn_3_3ACC0(i);
        } else {
            if (f[0x1FF] == 2) {
                g_FieldingLogic[0x139] = 0;
            }
            tgt = lbl_3_bss_170;
            if (g_FieldingLogic[0x10E] != 0) {
                tgt = -1;
            }
            *(s16*)(f + 0x19E) = tgt;
            if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x144] == 0 && tgt >= 0 && *(s16*)(f + 0x1A0) > 0xA) {
                *(s16*)(g_FieldingLogic + 0xCC) = -1;
            }
            if (tgt >= 0) {
                u8* t = *(u8**)(g_FieldingLogic + 0x70);
                if (t[0x1A] != 3 && t[0x1A] != 4) {
                    if (*(u16*)(g_FieldingLogic + 0x14A) & 0x200) {
                        *(s16*)(t + 0xC) = 0;
                    }
                    if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0 && g_Practice[0x1C5] != 0) {
                        *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = 0;
                    }
                }
            }
            fn_3_3A584(i);
        }
        break;
    }
    if (g_Ball[0x1BC9] != 0 && g_Ball[0x1BC9] != 3) {
        if (*(s16*)(f + 0x18C) == 6) {
            SetFielderAct(i, 0xB, 0x58);
        } else {
            SetFielderAct(i, 0xC, 0x60);
        }
        if (i <= 5) {
            f[0x1D5] = 3;
        } else {
            f[0x1D5] = 2;
        }
        *(s16*)(g_FieldingLogic + 0xB0) = -1;
    }
    k = *(s16*)(f + 0x18C);
    if (k >= 0 && k <= 3 && ((f32*)(f + 0xA8))[k] > lbl_3_rodata_B78) {
        if (k >= 0 && k <= 3) {
            if (((s16*)(g_FieldingLogic + 0xD0))[k] == i) {
                ((s16*)(g_FieldingLogic + 0xD0))[k] = -1;
                g_FieldingLogic[k + 0x101] = 0;
            }
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            if (f[0x1D3] == 1) {
                SetFielderActP(f, i, 12, 0x60);
            }
        } else if (k == 5) {
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            *(s16*)(g_FieldingLogic + 0xD8) = -1;
            g_FieldingLogic[0x105] = 0;
            if (f[0x1D3] == 14) {
                SetFielderActP(f, i, 12, 0x60);
            }
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) != i) {
        s16 cur = *(s16*)(g_FieldingLogic + 0xB0);
        u8* c = g_Fielders + cur * 0x268;
        if (*(s16*)(g_Ball + 0x1B66) >= lbl_3_data_484C[0] && g_FieldingLogic[0x139] == 0 &&
            ((c[0x256] == 1 && *(f32*)(f + cur * 4 + 0x84) < lbl_3_rodata_B70) || (c[0x252] != 0 && c[0x25B] == 0))) {
            u8* g = g_Fielders + off;
            *(f32*)(g + 0x14) = *(f32*)f;
            *(f32*)(g + 0x18) = *(f32*)(f + 4);
            *(f32*)(g + 0x1C) = *(f32*)(f + 8);
            *(f32*)(g + 0x30) = lbl_3_rodata_B20;
            *(f32*)(g + 0x34) = lbl_3_rodata_B20;
            *(f32*)(g + 0x50) = lbl_3_rodata_B20;
            *(f32*)(g + 0x68) = lbl_3_rodata_B20;
        }
    }
}
#endif

// .text:0x0003B370 size:0x3F4 mapped:0x8067A404
// NONMATCHING 99%: 1A2A==6 early return emitted as beq (orig bne+b); FieldingLogic+0xD0 compare operand order; r5/r6 swap
#if NONMATCHING
void fn_3_3B370(int i) {
    u8* f = g_Fielders + i * 0x268;
    s32 tgt;
    s16 k;
    if (g_Minigame[0x1A2A] != 5 && g_Minigame[0x1A2A] != 6 && *(s16*)(g_Ball + 0x1B66) <= 0) {
        return;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    case 1:
        break;
    default:
        tgt = lbl_3_bss_170;
        if (g_FieldingLogic[0x10E] != 0) {
            tgt = -1;
        }
        *(s16*)(f + 0x19E) = tgt;
        if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x144] == 0 && tgt >= 0 && *(s16*)(f + 0x1A0) > 0xA) {
            *(s16*)(g_FieldingLogic + 0xCC) = -1;
        }
        if (tgt >= 0) {
            u8* t = *(u8**)(g_FieldingLogic + 0x70);
            if (t[0x1A] != 3 && t[0x1A] != 4) {
                if (*(u16*)(g_FieldingLogic + 0x14A) & 0x200) {
                    *(s16*)(t + 0xC) = 0;
                }
                if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0 && g_Practice[0x1C5] != 0) {
                    *(s16*)(*(u8**)(g_FieldingLogic + 0x70) + 0xC) = 0;
                }
            }
        }
        fn_3_3A584(i);
        break;
    }
    if (g_Minigame[0x1A2A] != 5) {
        if (g_Minigame[0x1A2A] == 6) {
            return;
        }
        if (g_d_GameSettings[7] != 6) {
            if (g_Ball[0x1BC9] != 0 && g_Ball[0x1BC9] != 3) {
                if (*(s16*)(f + 0x18C) == 6) {
                    SetFielderAct(i, 0xB, 0x58);
                } else {
                    SetFielderAct(i, 0xC, 0x60);
                }
                if (i <= 5) {
                    f[0x1D5] = 3;
                } else {
                    f[0x1D5] = 2;
                }
                *(s16*)(g_FieldingLogic + 0xB0) = -1;
            }
            k = *(s16*)(f + 0x18C);
            if (k >= 0 && k <= 3 && ((f32*)(f + 0xA8))[k] > lbl_3_rodata_B78) {
                if (k >= 0 && k <= 3) {
                    if (i == ((s16*)(g_FieldingLogic + 0xD0))[k]) {
                        ((s16*)(g_FieldingLogic + 0xD0))[k] = -1;
                        g_FieldingLogic[k + 0x101] = 0;
                    }
                    *(s16*)(f + 0x18C) = -1;
                    f[0x1D7] = 0;
                    if (f[0x1D3] == 1) {
                        SetFielderActP(f, i, 12, 0x60);
                    }
                } else if (k == 5) {
                    *(s16*)(f + 0x18C) = -1;
                    f[0x1D7] = 0;
                    *(s16*)(g_FieldingLogic + 0xD8) = -1;
                    g_FieldingLogic[0x105] = 0;
                    if (f[0x1D3] == 14) {
                        SetFielderActP(f, i, 12, 0x60);
                    }
                }
            }
        }
    }
}
#endif

// .text:0x0003B764 size:0x238 mapped:0x8067A7F8
void fn_3_3B764(void) {
    u8* f = g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    f32 a2;
    f32 b2;
    if (*(s16*)(g_FieldingLogic + 0xC4) >= 0) {
        *(s16*)(g_Ball + 0x1B7E) = -1;
        return;
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) >= 0 && g_Ball[0x1BE3] == 0) {
        if (*(s16*)(g_Ball + 0x1B7A) == 0) {
            if (*(f32*)(f + 0x80) < lbl_3_rodata_B64) {
                *(s16*)(g_Ball + 0x1B7E) = *(s16*)(g_FieldingLogic + 0xB0);
            } else {
                *(s16*)(g_Ball + 0x1B7E) = -1;
            }
        } else {
            dx = *(f32*)f - *(f32*)(g_Ball + 0x364);
            dz = *(f32*)(f + 8) - *(f32*)(g_Ball + 0x36C);
            a2 = dx * dx;
            b2 = dz * dz;
            d = a2 + b2;
            SQRT_L(d);
            if (d <= *(f32*)(f + 0x74)) {
                if (fn_3_9CE0(*(f32*)f, *(f32*)(f + 8)) < *(f32*)(f + 0xE8)) {
                    *(s16*)(g_Ball + 0x1B7E) = *(s16*)(g_FieldingLogic + 0xB0);
                } else {
                    *(s16*)(g_Ball + 0x1B7E) = -1;
                }
            }
        }
        if (*(s16*)(g_Ball + 0x1B7E) >= 0) {
            g_Ball[0x1BCA] = 0;
            g_Ball[0x1BE1] = 0;
            *(s16*)(g_Ball + 0x1B8A) = -1;
        }
    }
}

// .text:0x0003B99C size:0x48 mapped:0x8067AA30
extern s16 lbl_3_bss_170;

void fn_3_3B99C(void) {
    if (g_Minigame[0x1A2A] == 5) {
        return;
    }
    if (!(*(u16*)(g_FieldingLogic + 0x14A) & 0x100)) {
        return;
    }
    (*(u8**)(g_FieldingLogic + 0x8C))[2] = 2;
    **(s16**)(g_FieldingLogic + 0x8C) = lbl_3_bss_170;
}

// .text:0x0003B9E4 size:0x46C mapped:0x8067AA78
extern void fn_3_A7EF8(void);
// NONMATCHING 93%: register allocation of the history/controls pointers; ball distance sum unfused in the original (fmuls+fadds); bss_170 re-addressed after fn_3_A7EF8
#if NONMATCHING
void fn_3_3B9E4(void) {
    u8* ctl;
    s16* hist;
    s32 k;
    s32 i;
    u8* f;
    *(s16*)(g_FieldingLogic + 0xB6) = *(s16*)(g_FieldingLogic + 0xB0);
    ctl = g_Controls + *(int*)(g_GameLogic + *(int*)(g_GameLogic + 8) * 4 + 0xEC) * 0x10;
    hist = &lbl_3_bss_170;
    for (k = 19; k > 0; k--) {
        hist[k] = hist[k - 1];
    }
    fn_3_A7EF8();
    if (g_d_GameSettings[7] == 2 && *(s8*)(g_Practice + 0x1C2) >= 0) {
        ctl = g_Practice + *(int*)(g_GameLogic + 8) * 0x10;
    }
    hist[0] = *(s16*)ctl;
    if (hist[0] == -1) {
        for (k = 1; k < 20; k++) {
            hist[k] = -1;
        }
    }
    if (hist[1] >= 0 && hist[2] >= 0) {
        lbl_3_bss_16C = hist[0];
    } else {
        lbl_3_bss_16C = -1;
    }
    *(u16*)(g_FieldingLogic + 0x148) = *(u16*)(ctl + 4);
    *(u16*)(g_FieldingLogic + 0x14A) = *(u16*)(ctl + 6);
    *(u16*)(g_FieldingLogic + 0x14C) = *(u16*)(ctl + 8);
    /* inlined fn_3_3B99C */
    if (g_Minigame[0x1A2A] != 5 && (*(u16*)(g_FieldingLogic + 0x14A) & 0x100)) {
        (*(u8**)(g_FieldingLogic + 0x8C))[2] = 2;
        **(s16**)(g_FieldingLogic + 0x8C) = lbl_3_bss_170;
    }
    if (*(s16*)(g_Ball + 0x1B66) <= 0) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1B66) == 1) {
        fn_3_34450();
    } else {
        if (*(s16*)(g_Ball + 0x1B66) > 3) {
            fn_3_39EB0();
        }
        fn_3_57144();
    }
    f = g_Fielders;
    for (i = 0; i < 9; i++, f += 0x268) {
        if (g_d_GameSettings[0x11] == 0 || g_Minigame[0x1923] == i) {
            fn_3_54B58(i);
            *(f32*)(f + 0x7C) = fn_3_9CE0(*(f32*)f, *(f32*)(f + 8));
            if (*(f32*)(f + 0x50) == lbl_3_rodata_B20) {
                *(f32*)(f + 0x38) = lbl_3_rodata_B20;
                *(f32*)(f + 0x3C) = lbl_3_rodata_B20;
            } else {
                *(f32*)(f + 0x38) = *(f32*)(f + 0x30) / *(f32*)(f + 0x50);
                *(f32*)(f + 0x3C) = *(f32*)(f + 0x34) / *(f32*)(f + 0x50);
            }
            f[0x1EA] = 0;
            f[0x217] = 0;
        }
    }
    fn_3_544B8();
    if (g_d_GameSettings[0x11] != 0) {
        fn_3_53F48();
    } else if (*(s16*)(g_Ball + 0x1B78) >= 0) {
        u8* h = g_Fielders + *(s16*)(g_Ball + 0x1B78) * 0x268;
        f32 x = *(f32*)h;
        f32 z = *(f32*)(h + 8);
        f32 d = x * x + z * z;
        *(f32*)g_Ball = x;
        *(f32*)(g_Ball + 4) = *(f32*)(h + 4);
        *(f32*)(g_Ball + 8) = z;
        *(f32*)(g_Ball + 0x348) = x;
        *(f32*)(g_Ball + 0x34C) = z;
        SQRT_L(d);
        *(f32*)(g_Ball + 0x1A00) = d;
    }
    if (g_Ball[0x1BC9] == 1) {
        *(s16*)(g_FieldingLogic + 0xB0) = *(s16*)(g_Ball + 0x1B78);
        g_FieldingLogic[0x139] = 0;
    } else if (g_Ball[0x1BC9] == 2 && *(s16*)(g_FieldingLogic + 0xC2) < 0) {
        *(s16*)(g_FieldingLogic + 0xB0) = -1;
    }
}
#endif

// .text:0x0003BE50 size:0x358 mapped:0x8067AEE4
// NONMATCHING 96%: f-reg numbering / 0.0 constant reuse; the second distance sum is unfused in the original; calls fn_3_526DC through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_3BE50(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 t;
    f32 px;
    f32 pz;
    f32 dx;
    f32 dz;
    f32 d;
    if (f[0x1EC] != 0) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1B6C) == 5 && *(f32*)(g_Ball + 0x1A14) != lbl_3_rodata_B20) {
        t = *(f32*)(f + 0x74) / *(f32*)(g_Ball + 0x1A14);
        px = *(f32*)(g_Ball + 0x318) * t + *(f32*)g_Ball;
        pz = *(f32*)(g_Ball + 0x320) * t + *(f32*)(g_Ball + 8);
        dx = *(f32*)f - px;
        dz = *(f32*)(f + 8) - pz;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d > *(f32*)(f + 0xE8)) {
            f[0x1E9] = 1;
            *(f32*)(f + 0x14) = px;
            *(f32*)(f + 0x1C) = pz;
            dx = px - *(f32*)f;
            dz = pz - *(f32*)(f + 8);
            if (dx == lbl_3_rodata_B20 && dz == lbl_3_rodata_B20) {
                *(f32*)(f + 0x50) = lbl_3_rodata_B20;
                *(f32*)(f + 0x68) = lbl_3_rodata_B20;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                *(f32*)(f + 0x68) = d;
            }
            f[0x1D9] = 1;
        }
    }
    /* TODO: fn_3_526DC takes the fielder index; its prototype (other range) is still (void) */
    ((void (*)(int))fn_3_526DC)(i);
    if (f[0x1E9] != 0 && *(f32*)(f + 0x50) == lbl_3_rodata_B20) {
        f[0x1E9] = 0;
    }
    if (*(s16*)(g_Ball + 0x1B8A) == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x0003C1A8 size:0x78 mapped:0x8067B23C
void fn_3_3C1A8(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (f[0x1EC] == 0 && fn_3_53130(i) == 0) {
        *(f32*)(f + 0x50) = lbl_3_rodata_1498;
        f[0x1E3] = 1;
        f[0x1D5] = 0;
        *(f32*)(f + 0x14) = *(f32*)(f + 0x0);
        *(f32*)(f + 0x1C) = *(f32*)(f + 0x8);
    }
}

// .text:0x0003C220 size:0x50 mapped:0x8067B2B4
void fn_3_3C220(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (fn_3_53130(i) == 0) {
        *(f32*)(f + 0x50) = lbl_3_rodata_1498;
        *(f32*)(f + 0x68) = lbl_3_rodata_1498;
    }
}

// .text:0x0003C270 size:0x214 mapped:0x8067B304
int fn_3_3C270(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    f32 d;
    f32 a2;
    f32 b2;
    *(s16*)(f + 0x18C) = 0xE;
    f[0x1D7] = 2;
    if (i != -1) {
        f[0x1D3] = 0xE;
        if (*(int*)(lbl_3_data_3C40 + 0x70) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x70);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    f[0x1D6] = 0xB;
    tx = *(f32*)(lbl_3_data_4444 + 0x20);
    tz = *(f32*)(lbl_3_data_4444 + 0x24);
    *(f32*)(f + 0x14) = tx;
    *(f32*)(f + 0x1C) = tz;
    dx = tx - *(f32*)f;
    dz = tz - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = (f32)atan2(dz, dx);
        a2 = dz * dz;
        d = dx * dx + a2;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
    return 1;
}

// .text:0x0003C484 size:0x110 mapped:0x8067B518
int fn_3_3C484(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(f32*)(f + 0xA8) < 5.0f) {
        *(s16*)(f + 0x18C) = 9;
    } else if (*(f32*)(f + 0xAC) < 5.0f) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    } else if (*(f32*)(f + 0xB0) < 5.0f) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    } else if (*(f32*)(f + 0xB4) < 5.0f) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    } else {
        return 0;
    }
    f[0x1D7] = 2;
    if (i != -1) {
        int v;
        f[0x1D3] = 0xE;
        v = *(int*)(lbl_3_data_3C40 + 0x70);
        if (v >= 0) {
            g_FieldingLogic[i + 0xF8] = v;
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    f[0x1D6] = 0xB;
    return 1;
}

// .text:0x0003C594 size:0x5F8 mapped:0x8067B628
#pragma dont_inline off
/* drop fielder i's base assignment (FieldingLogic+0xD0 slots / +0xD8) */
static inline void ReleaseBaseInline(u8* f, int i) {
    s16 k = *(s16*)(f + 0x18C);
    if (k >= 0) {
        if (k <= 3) {
            if (((s16*)(g_FieldingLogic + 0xD0))[k] == i) {
                ((s16*)(g_FieldingLogic + 0xD0))[k] = -1;
                g_FieldingLogic[k + 0x101] = 0;
            }
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            if (f[0x1D3] == 1) {
                SetFielderActP(f, i, 12, 0x60);
            }
        } else if (k == 5) {
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            *(s16*)(g_FieldingLogic + 0xD8) = -1;
            g_FieldingLogic[0x105] = 0;
            if (f[0x1D3] == 14) {
                SetFielderActP(f, i, 12, 0x60);
            }
        }
    }
}
#pragma dont_inline on
extern f32 lbl_3_rodata_C10;
extern f32 lbl_3_rodata_C14;
// NONMATCHING 77%: our loop hoists the float constants and indexes the base arrays (lhax/sthx) where the original strength-reduces FieldingLogic/fielder pointers
#if NONMATCHING
int fn_3_3C594(int i) {
    u8* f = g_Fielders + i * 0x268;
    s32 k;
    s32 owner;
    f32 me;
    f32 theirs;
    s16 holder = *(s16*)(g_Ball + 0x1B78);
    f32 dist = *(f32*)(g_Ball + 0x1A00);
    f32 spd = *(f32*)(g_Ball + 0x1A14);
    s16 ang = *(s16*)(g_Ball + 0x1B80);
    for (k = 0; k < 4; k++) {
        if (g_FieldingLogic[k + 0x101] != 0) {
            continue;
        }
        owner = ((s16*)(g_FieldingLogic + 0xD0))[k];
        if (holder == owner) {
            continue;
        }
        me = ((f32*)(f + 0xA8))[k];
        if (me < lbl_3_rodata_B60) {
            goto take;
        }
        theirs = ((f32*)(g_Fielders + owner * 0x268 + 0xA8))[k];
        if (!(me < theirs - lbl_3_rodata_B68)) {
            continue;
        }
        if (i != 0 || !(dist < lbl_3_rodata_C10) || !(spd < lbl_3_rodata_C14)) {
            goto take;
        }
        if (k == 1 && ang > 0x200 && ang < 0x400) {
            if (me < theirs - lbl_3_rodata_B64) {
                goto take;
            }
        } else if (k != 3 || ang <= 0x400 || ang >= 0x600 || me < theirs - lbl_3_rodata_B64) {
            goto take;
        }
    }
    owner = *(s16*)(g_FieldingLogic + 0xD8);
    if (g_FieldingLogic[0x105] == 0 && owner != -1 &&
        (*(f32*)(f + 0xB8) < lbl_3_rodata_B64 ||
         lbl_3_rodata_B78 + *(f32*)(f + 0xB8) < *(f32*)(g_Fielders + owner * 0x268 + 0xB8))) {
        goto take_cutoff;
    }
    return 0;
take:
    /* take base k from its current owner */
    if (*(s16*)(g_Ball + 0x1B8A) == owner) {
        *(s16*)(g_Ball + 0x1B8A) = i;
    }
    if (owner >= 0) {
        u8* o = g_Fielders + owner * 0x268;
        ReleaseBaseInline(o, owner);
        SetFielderAct(owner, 12, 0x60);
        g_Fielders[owner * 0x268 + 0x1D5] = 3;
    }
    *(s16*)(f + 0x18C) = k;
    f[0x1D7] = 1;
    SetFielderAct(i, 1, 8);
    ((s16*)(g_FieldingLogic + 0xD0))[k] = i;
    return 1;
take_cutoff:
    if (owner >= 0 && holder != owner) {
        u8* o = g_Fielders + owner * 0x268;
        ReleaseBaseInline(o, owner);
        SetFielderAct(owner, 12, 0x60);
        g_Fielders[owner * 0x268 + 0x1D5] = 4;
    }
    *(s16*)(f + 0x18C) = 5;
    f[0x1D7] = 2;
    SetFielderAct(i, 0xE, 0x70);
    *(s16*)(g_FieldingLogic + 0xD8) = i;
    return 1;
}
#endif

// .text:0x0003CB8C size:0x124 mapped:0x8067BC20
int fn_3_3CB8C(int i) {
    u8* f;
    if (*(s16*)(g_Ball + 0x1B7A) > 1) {
        return 0;
    }
    if (g_Ball[0x1BCC] != 0) {
        return 0;
    }
    if (*(s16*)(g_FieldingLogic + 0xBC) >= 0) {
        return 0;
    }
    if (*(s16*)(g_Ball + 0x1B7A) == 0) {
        if (g_Ball[0x1BBF] < 1 || i < 6) {
            goto fail;
        }
        if (*(s16*)(g_Ball + 0x1B84) < 0x380 && i == 6) {
            return 0;
        }
        if (*(s16*)(g_Ball + 0x1B84) > 0x480 && i == 8) {
            return 0;
        }
    } else {
        if (i < 6 || i != *(s16*)(g_FieldingLogic + 0xB8)) {
        fail:
            return 0;
        }
    }
    f = g_Fielders + i * 0x268;
    if (i != -1) {
        f[0x1D3] = 0x18;
        if (*(int*)(lbl_3_data_3C40 + 0xC0) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0xC0);
        }
        *(s16*)(g_FieldingLogic + 0xBC) = i;
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    *(s16*)(g_FieldingLogic + 0xBC) = i;
    return 1;
}

// .text:0x0003CCB0 size:0x654 mapped:0x8067BD44
#pragma dont_inline off
/* same bodies as fn_3_3C484 / fn_3_3C270, which the original inlines into fn_3_3CCB0 */
static inline int TakeNearBaseInline(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(f32*)(f + 0xA8) < 5.0f) {
        *(s16*)(f + 0x18C) = 9;
    } else if (*(f32*)(f + 0xAC) < 5.0f) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    } else if (*(f32*)(f + 0xB0) < 5.0f) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    } else if (*(f32*)(f + 0xB4) < 5.0f) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    } else {
        return 0;
    }
    f[0x1D7] = 2;
    if (i != -1) {
        int v;
        f[0x1D3] = 0xE;
        v = *(int*)(lbl_3_data_3C40 + 0x70);
        if (v >= 0) {
            g_FieldingLogic[i + 0xF8] = v;
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    f[0x1D6] = 0xB;
    return 1;
}
static inline int GoHomeInline(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    f32 d;
    f32 a2;
    f32 b2;
    *(s16*)(f + 0x18C) = 0xE;
    f[0x1D7] = 2;
    if (i != -1) {
        f[0x1D3] = 0xE;
        if (*(int*)(lbl_3_data_3C40 + 0x70) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x70);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    f[0x1D6] = 0xB;
    tx = *(f32*)(lbl_3_data_4444 + 0x20);
    tz = *(f32*)(lbl_3_data_4444 + 0x24);
    *(f32*)(f + 0x14) = tx;
    *(f32*)(f + 0x1C) = tz;
    dx = tx - *(f32*)f;
    dz = tz - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = (f32)atan2(dz, dx);
        a2 = dz * dz;
        d = dx * dx + a2;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
    return 1;
}
#pragma dont_inline on
extern f32 lbl_3_rodata_C18;
// NONMATCHING 92%: cover-decision branch layout (the original keeps a 0/1 result flag); f-reg numbering in the inlined fn_3_3C270 body
#if NONMATCHING
void fn_3_3CCB0(int i) {
    u8* f = g_Fielders + i * 0x268;
    s32 k;
    s32 cover;
    if (f[0x1EC] != 0 || fn_3_53130(i) != 0 || g_Ball[0x1BD1] != 0) {
        return;
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) == 5 && *(s16*)(f + 0x18C) == 5) {
        fn_3_3BE50(i);
        return;
    }
    if (i <= 5) {
        if (fn_3_3C594(i) != 0) {
            return;
        }
        if (TakeNearBaseInline(i) != 0) {
            return;
        }
    }
    for (k = 0; k < 4; k++) {
        if (i == ((s16*)(g_FieldingLogic + 0xD0))[k]) {
            *(s16*)(f + 0x18C) = k;
            SetFielderAct(i, 1, 8);
            return;
        }
    }
    if (i >= 6) {
        cover = 0;
        if (*(s16*)(g_Ball + 0x1B7A) > 1) {
        } else if (g_Ball[0x1BCC] != 0) {
        } else if (*(s16*)(g_FieldingLogic + 0xBC) >= 0) {
        } else if (*(s16*)(g_Ball + 0x1B7A) == 0) {
            if (g_Ball[0x1BBF] >= 1 && i >= 6 && !(*(s16*)(g_Ball + 0x1B84) < 0x380 && i == 6) &&
                !(*(s16*)(g_Ball + 0x1B84) > 0x480 && i == 8)) {
                cover = 1;
            }
        } else if (i >= 6 && i == *(s16*)(g_FieldingLogic + 0xB8)) {
            cover = 1;
        }
        if (cover != 0) {
            SetFielderActTag(i, 0x18, 0xC0);
            *(s16*)(g_FieldingLogic + 0xBC) = i;
            return;
        }
        if (*(s16*)(f + 0x18C) == 7) {
            goto go_home;
        }
        if (g_FieldingLogic[i + 0xF8] != 9) {
            *(s16*)(g_Fielders + i * 0x268 + 0x18C) = 7;
            SetFielderAct(i, 0xE, 0x70);
            f[0x1D6] = 0;
            *(s16*)(f + 0x190) = -1;
        }
        return;
    }
    if (*(f32*)(f + 0x70) > lbl_3_rodata_C18) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
        f[0x1D7] = 2;
        SetFielderAct(i, 0xE, 0x70);
        f[0x1D6] = 0xB;
        return;
    }
go_home:
    if (f[0x1DE] != 0) {
        GoHomeInline(i);
        return;
    }
    *(f32*)(f + 0x30) = lbl_3_rodata_B20;
    *(f32*)(f + 0x34) = lbl_3_rodata_B20;
    *(f32*)(f + 0x50) = lbl_3_rodata_B20;
}
#endif

// .text:0x0003D304 size:0x3A8 mapped:0x8067C398
extern void fn_3_9F79C(f32 a, f32 b, f32 c, f32* x, f32* y);
extern void fn_3_A96FC(int);
extern void fn_3_A9984(int);
extern u8 lbl_3_data_4290[];
extern u8 lbl_3_data_4300[];
extern u8 lbl_3_data_4348[];
// NONMATCHING 96%: table x reads via lfsx in the original; f30/f31 swapped; calls fn_3_2F574/fn_3_526DC through casts until their prototypes gain the index arg
#if NONMATCHING
void fn_3_3D304(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 tx;
    f32 tz;
    f32 ox;
    f32 oz;
    f32 dx;
    f32 dz;
    f32 d;
    s32 team;
    u8* home;
    if (f[0x20F] != 0) {
        g_FieldingLogic[0x111] = 0;
        return;
    }
    if (f[0x210] != 0) {
        fn_3_251E4(i);
        f[0x1EE] = 0;
        return;
    }
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (f[0x211] != 0) {
        fn_3_A96FC(i);
        return;
    }
    if (f[0x1EE] != 0) {
        fn_3_A9984(i);
        return;
    }
    if (f[0x1EF] != 0) {
        return;
    }
    if (f[0x203] != 0) {
        /* TODO: fn_3_2F574 takes the fielder index; its prototype (other range) is still (void) */
        ((void (*)(int))fn_3_2F574)(i);
        return;
    }
    if (*(s16*)(g_Ball + 0x1B78) == i && f[0x1EC] == 0) {
        *(s16*)(g_Ball + 0x1B78) = -1;
    }
    team = *(int*)(g_GameLogic + 8);
    home = lbl_3_data_4290 + g_d_GameSettings[9] * 0x10 + *(int*)(g_GameLogic + 0x10) * 8;
    tx = *(f32*)home;
    tz = *(f32*)(home + 4);
    if (*(s16*)(f + 0x178) != *(int*)(g_GameLogic + team * 4 + 0xF4)) {
        fn_3_9F79C(*(f32*)(lbl_3_data_4348 + g_d_GameSettings[9] * 8 + team * 4), *(f32*)(lbl_3_data_4300 + i * 8),
                   *(f32*)(lbl_3_data_4300 + i * 8 + 4), &ox, &oz);
        tx += ox;
        tz += oz;
    }
    f[0x1D6] = 0xD;
    *(f32*)(f + 0x14) = tx;
    *(f32*)(f + 0x1C) = tz;
    dx = tx - *(f32*)f;
    dz = tz - *(f32*)(f + 8);
    if (lbl_3_rodata_B20 == dx && lbl_3_rodata_B20 == dz) {
        *(f32*)(f + 0x50) = lbl_3_rodata_B20;
        *(f32*)(f + 0x68) = lbl_3_rodata_B20;
    } else {
        *(f32*)(f + 0x64) = (f32)atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
    /* TODO: fn_3_526DC takes the fielder index; its prototype (other range) is still (void) */
    ((void (*)(int))fn_3_526DC)(i);
    if (*(f32*)(f + 0x68) <= lbl_3_rodata_B80) {
        SetFielderAct(i, 0, 0);
        f[0x1FA] = 1;
    }
    if (i == *(s16*)(g_Ball + 0x1B78)) {
        *(s16*)(g_FieldingLogic + 0xC4) = -1;
    }
}
#endif

// .text:0x0003D6AC size:0x128 mapped:0x8067C740
void fn_3_3D6AC(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (fn_3_53130(i) == 0 && f[0x1EC] == 0) {
        *(f32*)(f + 0x50) = 0.0f;
        f[0x1E3] = 1;
        f[0x1D5] = 0;
        *(f32*)(f + 0x14) = *(f32*)(f + 0x0);
        *(f32*)(f + 0x1C) = *(f32*)(f + 0x8);
        if (g_Ball[0x1BC9] == 0) {
            if (i == 6) {
                if (*(s16*)(g_Ball + 0x1B80) >= 0x400) {
                    if (*(s16*)(g_Ball + 0x1B80) < 0xC00) {
                        goto body;
                    }
                }
            } else if (i != 8 || *(s16*)(g_Ball + 0x1B80) < 0x400 || *(s16*)(g_Ball + 0x1B80) >= 0xC00) {
                goto body;
            }
        } else {
        body:
            if (i != -1) {
                f[0x1D3] = 9;
                if (*(int*)(lbl_3_data_3C40 + 0x48) >= 0) {
                    g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x48);
                }
                f[0x1D5] = 0;
                f[0x1D6] = 0;
                *(s16*)(f + 0x1A4) = 0;
                *(s16*)(f + 0x1AC) = 0;
                f[0x1FF] = 0;
            }
        }
        f[0x1F0] = 1;
    }
}

// .text:0x0003D7D4 size:0x3A4 mapped:0x8067C868
int fn_3_3D7D4(int i) {
    u8* f = g_Fielders + i * 0x268;
    int r;
    int j;
    u8* p;
    if (*(f32*)f > lbl_3_rodata_B20) {
        if (*(f32*)(f + 0xB0) > *(f32*)(f + 0xAC)) {
            r = 0xA;
        } else {
            r = 0xB;
        }
    } else if (*(f32*)(f + 0xB0) > *(f32*)(f + 0xB4)) {
        r = 0xD;
    } else {
        r = 0xC;
    }
    if (r == 0xA) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p += 0x268) {
            if (j != i && *(s16*)(p + 0x18C) == 0xA) {
                r = 0xB;
            }
        }
    } else if (r == 0xB) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p += 0x268) {
            if (j != i && *(s16*)(p + 0x18C) == 0xA) {
                r = 0xC;
            }
        }
    } else if (r == 0xC) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p += 0x268) {
            if (j != i && *(s16*)(p + 0x18C) == 0xA) {
                r = 0xB;
            }
        }
    } else if (r == 0xD) {
        p = g_Fielders;
        for (j = 0; j < 6; j++, p += 0x268) {
            if (j != i && *(s16*)(p + 0x18C) == 0xA) {
                r = 0xC;
            }
        }
    }
    return r;
}

// .text:0x0003DB78 size:0x7D4 mapped:0x8067CC0C
extern void fn_3_A7C88(void);
extern u8 lbl_3_data_4484[];
extern u8 lbl_3_data_44B4[];
extern f32 lbl_3_rodata_C1C;
extern f32 lbl_3_rodata_C20;
// NONMATCHING 92%: register/f-reg numbering in the inlined run-target blocks; calls fn_3_526DC through a cast until its prototype gains the index arg
#if NONMATCHING
void fn_3_3DB78(int i) {
    s32 off = i * 0x268;
    u8* f = g_Fielders + off;
    s16 k;
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (g_Ball[0x1BCD] != 0 && i <= 1) {
        return;
    }
    k = *(s16*)(f + 0x18C);
    /* TODO: fn_3_526DC takes the fielder index; its prototype (other range) is still (void) */
    if (k == 5) {
        f32 xo;
        f32 zo;
        if (*(s16*)(g_FieldingLogic + 0xC4) == 5) {
            fn_3_3BE50(i);
            fn_3_A7C88();
            if (*(s16*)(g_Ball + 0x1B8A) == i) {
                fn_3_4E638();
            }
            return;
        }
        zo = lbl_3_rodata_B68;
        xo = zo;
        if (*(f32*)f < lbl_3_rodata_B20) {
            xo = lbl_3_rodata_C1C;
        }
        if (*(f32*)(f + 8) < *(f32*)(lbl_3_data_4444 + 0x24)) {
            zo = lbl_3_rodata_C1C;
        }
        if (g_FieldingLogic[0x105] != 0 && *(f32*)(f + 0x50) <= lbl_3_rodata_C20) {
            u8* g = g_Fielders + off;
            *(f32*)(g + 0x14) = *(f32*)f;
            *(f32*)(g + 0x18) = *(f32*)(f + 4);
            *(f32*)(g + 0x1C) = *(f32*)(f + 8);
            *(f32*)(g + 0x30) = lbl_3_rodata_B20;
            *(f32*)(g + 0x34) = lbl_3_rodata_B20;
            *(f32*)(g + 0x50) = lbl_3_rodata_B20;
            *(f32*)(g + 0x68) = lbl_3_rodata_B20;
            return;
        }
        SetRunTargetInline(f, *(f32*)(lbl_3_data_4444 + 0x20) + xo, *(f32*)(lbl_3_data_4444 + 0x24) + zo);
        ((void (*)(int))fn_3_526DC)(i);
        if (*(f32*)(f + 0x68) < lbl_3_rodata_B78) {
            g_FieldingLogic[0x105] = 1;
            *(f32*)(f + 0x68) = lbl_3_rodata_B20;
            f[0x1D6] = 8;
        } else {
            g_FieldingLogic[0x105] = 0;
            f[0x1D6] = 0xB;
        }
    } else if (k == 7) {
        SetRunTargetInline(f, *(f32*)(lbl_3_data_44B4 + i * 8 + 0x10), *(f32*)(lbl_3_data_44B4 + i * 8 + 0x14));
        ((void (*)(int))fn_3_526DC)(i);
        if (lbl_3_rodata_B20 == *(f32*)(f + 0x68)) {
            SetFielderAct(i, 0, 0);
        }
    } else if (k >= 8 && k <= 13) {
        SetRunTargetInline(f, *(f32*)(lbl_3_data_4484 + k * 8 - 0x40), *(f32*)(lbl_3_data_4484 + k * 8 - 0x3C));
        ((void (*)(int))fn_3_526DC)(i);
        if (lbl_3_rodata_B20 == *(f32*)(f + 0x68)) {
            SetFielderAct(i, 0, 0);
        }
    } else if (k == 14) {
        if (f[0x1DE] == 0) {
            SetFielderAct(i, 0, 0);
            *(s16*)(f + 0x18C) = -1;
            return;
        }
        ((void (*)(int))fn_3_526DC)(i);
    } else if (k == 15) {
        ((void (*)(int))fn_3_526DC)(i);
        if (lbl_3_rodata_B20 == *(f32*)(f + 0x68)) {
            SetFielderAct(i, 0, 0);
        }
    }
}
#endif

// .text:0x0003E34C size:0x11C mapped:0x8067D3E0
void fn_3_3E34C(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (*(s16*)(f + 0x19C) >= 1) {
        if (f[0x1C5] != 0) {
            if (i != -1) {
                f[0x1D3] = 0x12;
                if (*(int*)(lbl_3_data_3C40 + 0x90) >= 0) {
                    g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x90);
                }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
            }
        } else if (i != -1) {
            f[0x1D3] = 0;
            if (*(int*)lbl_3_data_3C40 >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)lbl_3_data_3C40;
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
    } else if (g_FieldingLogic[0x11C] != 0 && i != -1) {
        f[0x1D3] = 0;
        if (*(int*)lbl_3_data_3C40 >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)lbl_3_data_3C40;
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
}

// .text:0x0003E468 size:0x228 mapped:0x8067D4FC
void fn_3_3E468(void) {
    s32 i;
    int j;
    s32 k;
    int best;
    f32 min;
    u8* f;
    for (i = 0; i < 9; i++) {
        *(s16*)(g_Fielders + i * 0x268 + 0x18C) = -1;
        g_Fielders[i * 0x268 + 0x1D7] = 0;
    }
    for (k = 0; k < 5; k++) {
        *(s16*)(g_FieldingLogic + k * 2 + 0xD0) = -1;
        g_FieldingLogic[k + 0x101] = 0;
    }
    for (j = 0; j < 4; j++) {
        min = lbl_3_rodata_C24;
        for (k = 0; k < 6; k++) {
            if (g_FieldingLogic[k + 0xF8] == 0 && *(f32*)(g_Fielders + j * 4 + k * 0x268 + 0xA8) < min) {
                min = *(f32*)(g_Fielders + j * 4 + k * 0x268 + 0xA8);
                best = k;
            }
        }
        f = g_Fielders + best * 0x268;
        *(s16*)(f + 0x18C) = j;
        f[0x1D7] = 1;
        if (best != -1) {
            f[0x1D3] = 1;
            if (*(int*)(lbl_3_data_3C40 + 0x8) >= 0) {
                g_FieldingLogic[best + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x8);
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
        *(s16*)(g_FieldingLogic + j * 2 + 0xD0) = best;
    }
}

// .text:0x0003E690 size:0x4DC mapped:0x8067D724
// NONMATCHING 78%: sel/pick are uninitialised in the original (we zero them); per-base search loop unrolled differently; distance sum unfused there; calls fn_3_4EFC8 through a cast until its prototype gains (int, int)
#if NONMATCHING
void fn_3_3E690(void) {
    /* sel and pick start uninitialised in the original */
    s32 sel = 0;
    s32 best = 0x270F;
    u8* f = g_Fielders;
    s32 i;
    s32 k;
    s32 eta;
    s32 pick = 0;
    f32 bx = *(f32*)(g_Ball + 0x714);
    f32 bz = *(f32*)(g_Ball + 0x71C);
    u8 phase = g_Ball[0x1BBE];
    for (i = 0; i < 9; i++, f += 0x268) {
        if (bx == *(f32*)f && bz == *(f32*)(f + 8)) {
            eta = 1;
        } else {
            f32 dx = bx - *(f32*)f;
            f32 dz = bz - *(f32*)(f + 8);
            f32 d = dx * dx + dz * dz;
            f32 sp;
            SQRT_L(d);
            sp = *(f32*)(f + 0x58);
            if (lbl_3_rodata_B20 == sp) {
                sp = lbl_3_rodata_B60;
            }
            eta = (f[0x1D1] >> 1) + (s32)(d / sp);
        }
        if (f[0x1D3] == 2) {
            eta -= 0xF;
        }
        if (*(s16*)(f + 0x18C) >= 0 && *(s16*)(f + 0x18C) <= 3) {
            eta += 0x1E;
        }
        if (f[0x210] != 0) {
            eta += *(s16*)(f + 0x1C0);
        } else if (f[0x212] == 3) {
            eta += 0x5A;
        }
        if (f[0x20F] != 0) {
            eta += *(s16*)(f + 0x1BA);
        }
        if (phase >= 3 && i <= 5) {
            eta += 0x1E;
        }
        if (eta < best) {
            sel = i;
            best = eta;
        }
    }
    SetFielderAct(sel, 3, 0x18);
    /* TODO: fn_3_4EFC8 takes (fielder, int); its prototype (other range) is still (void) */
    ((void (*)(int, int))fn_3_4EFC8)(sel, 0);
    g_Fielders[sel * 0x268 + 0x1DC] = 4;
    for (i = 0; i < 9; i++) {
        *(s16*)(g_Fielders + i * 0x268 + 0x18C) = -1;
        g_Fielders[i * 0x268 + 0x1D7] = 0;
    }
    *(s16*)(g_FieldingLogic + 0xD0) = -1;
    g_FieldingLogic[0x101] = 0;
    *(s16*)(g_FieldingLogic + 0xD2) = -1;
    g_FieldingLogic[0x102] = 0;
    *(s16*)(g_FieldingLogic + 0xD4) = -1;
    g_FieldingLogic[0x103] = 0;
    *(s16*)(g_FieldingLogic + 0xD6) = -1;
    g_FieldingLogic[0x104] = 0;
    *(s16*)(g_FieldingLogic + 0xD8) = -1;
    g_FieldingLogic[0x105] = 0;
    for (k = 0; k < 4; k++) {
        f32 dmin = lbl_3_rodata_C24;
        for (i = 0; i < 6; i++) {
            if (g_FieldingLogic[i + 0xF8] == 0 && ((f32*)(g_Fielders + i * 0x268 + 0xA8))[k] < dmin) {
                dmin = ((f32*)(g_Fielders + i * 0x268 + 0xA8))[k];
                pick = i;
            }
        }
        *(s16*)(g_Fielders + pick * 0x268 + 0x18C) = k;
        g_Fielders[pick * 0x268 + 0x1D7] = 1;
        SetFielderAct(pick, 1, 8);
        ((s16*)(g_FieldingLogic + 0xD0))[k] = pick;
    }
    *(s16*)(g_FieldingLogic + 0xBE) = -1;
}
#endif

// .text:0x0003EB6C size:0x4C8 mapped:0x8067DC00
// NONMATCHING 77%: same shape as fn_3_3E690 (uninitialised sel/pick zeroed here, inner base search unrolled differently, unfused distance sum); calls fn_3_4EFC8 through a cast
#if NONMATCHING
void fn_3_3EB6C(void) {
    /* sel and pick start uninitialised in the original */
    s32 sel = 0;
    s32 best = 0x270F;
    u8* f = g_Fielders;
    s32 i;
    s32 k;
    s32 eta;
    s32 pick = 0;
    f32 bx = *(f32*)(g_Ball + 0x348);
    f32 bz = *(f32*)(g_Ball + 0x34C);
    u8 phase = g_Ball[0x1BBE];
    u8 caught = g_Ball[0x1BF1];
    for (i = 0; i < 9; i++, f += 0x268) {
        if (bx == *(f32*)f && bz == *(f32*)(f + 8)) {
            eta = 1;
        } else {
            f32 dx = bx - *(f32*)f;
            f32 dz = bz - *(f32*)(f + 8);
            f32 d = dx * dx + dz * dz;
            f32 sp;
            SQRT_L(d);
            sp = *(f32*)(f + 0x58);
            if (lbl_3_rodata_B20 == sp) {
                sp = lbl_3_rodata_B60;
            }
            eta = (f[0x1D1] >> 1) + (s32)(d / sp);
        }
        if (f[0x1D3] == 2) {
            eta -= 0xF;
        }
        if (*(s16*)(f + 0x18C) >= 0 && *(s16*)(f + 0x18C) <= 3) {
            eta += 0x1E;
        }
        if (caught == 0 && lbl_3_rodata_B64 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x350)) {
            eta += 0x1E;
        }
        if (phase >= 3 && i <= 5) {
            eta += 0xF;
        }
        if (eta < best) {
            sel = i;
            best = eta;
        }
    }
    SetFielderAct(sel, 3, 0x18);
    /* TODO: fn_3_4EFC8 takes (fielder, int); its prototype (other range) is still (void) */
    ((void (*)(int, int))fn_3_4EFC8)(sel, 0);
    g_Fielders[sel * 0x268 + 0x1DC] = 0;
    for (i = 0; i < 9; i++) {
        *(s16*)(g_Fielders + i * 0x268 + 0x18C) = -1;
        g_Fielders[i * 0x268 + 0x1D7] = 0;
    }
    *(s16*)(g_FieldingLogic + 0xD0) = -1;
    g_FieldingLogic[0x101] = 0;
    *(s16*)(g_FieldingLogic + 0xD2) = -1;
    g_FieldingLogic[0x102] = 0;
    *(s16*)(g_FieldingLogic + 0xD4) = -1;
    g_FieldingLogic[0x103] = 0;
    *(s16*)(g_FieldingLogic + 0xD6) = -1;
    g_FieldingLogic[0x104] = 0;
    *(s16*)(g_FieldingLogic + 0xD8) = -1;
    g_FieldingLogic[0x105] = 0;
    for (k = 0; k < 4; k++) {
        f32 dmin = lbl_3_rodata_C24;
        for (i = 0; i < 6; i++) {
            if (g_FieldingLogic[i + 0xF8] == 0 && ((f32*)(g_Fielders + i * 0x268 + 0xA8))[k] < dmin) {
                dmin = ((f32*)(g_Fielders + i * 0x268 + 0xA8))[k];
                pick = i;
            }
        }
        *(s16*)(g_Fielders + pick * 0x268 + 0x18C) = k;
        g_Fielders[pick * 0x268 + 0x1D7] = 1;
        SetFielderAct(pick, 1, 8);
        ((s16*)(g_FieldingLogic + 0xD0))[k] = pick;
    }
    *(s16*)(g_FieldingLogic + 0xBE) = -1;
}
#endif

// .text:0x0003F034 size:0xF0 mapped:0x8067E0C8
void fn_3_3F034(void) {
    int i;
    u8* f;
    for (i = 0; i < 9; i++) {
        g_FieldingLogic[i + 0xF8] = 0;
        f = g_Fielders + i * 0x268;
        if (i != -1) {
            f[0x1D3] = 0;
            if (*(int*)lbl_3_data_3C40 >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)lbl_3_data_3C40;
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
    }
    *(s16*)(g_FieldingLogic + 0xD0) = -1;
    g_FieldingLogic[0x101] = 0;
    *(s16*)(g_FieldingLogic + 0xD2) = -1;
    g_FieldingLogic[0x102] = 0;
    *(s16*)(g_FieldingLogic + 0xD4) = -1;
    g_FieldingLogic[0x103] = 0;
    *(s16*)(g_FieldingLogic + 0xD6) = -1;
    g_FieldingLogic[0x104] = 0;
    *(s16*)(g_FieldingLogic + 0xBC) = -1;
    *(s16*)(g_FieldingLogic + 0xBE) = -1;
    *(s16*)(g_FieldingLogic + 0xC2) = -1;
    if (*(s16*)(g_Ball + 0x1B7A) == 0 && *(s16*)(g_Ball + 0x1B5E) > 0x2D) {
        fn_3_3EB6C();
    } else {
        fn_3_3E690();
    }
}

// .text:0x0003F124 size:0x128 mapped:0x8067E1B8
void fn_3_3F124(void) {
    SetFielderAct(0, 0x14, 0xA0);
    if ((*(s16*)(g_Fielders + 0x8BA) + *(s16*)(g_Fielders + 0xD8A)) / 2 > *(s16*)(g_Ball + 0x1B9C)) {
        SetFielderAct(3, 3, 0x18);
    } else {
        SetFielderAct(5, 3, 0x18);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}

// .text:0x0003F24C size:0x514 mapped:0x8067E2E0
// NONMATCHING 98%: SetFielderAct state/table regs (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_3_3F24C(void) {
    s16 ang = *(s16*)(g_Ball + 0x1B9C);
    if (*(s16*)(g_Ball + 0x1B9A) >= 0x400 && *(s16*)(g_Ball + 0x1B9A) <= 0xC00) {
        ang += 0x800;
        if (ang > 0x1000) {
            ang -= 0x1000;
        }
    }
    if (ang > 0xA00 && ang < 0xE00) {
        SetFielderAct(1, 3, 0x18);
    } else if (ang >= 0xE00 || ang < 0x200) {
        if (*(s16*)(g_Ball + 0x1B9A) > 0x800) {
            SetFielderAct(2, 3, 0x18);
        } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_BA0) {
            SetFielderAct(1, 3, 0x18);
            SetFielderAct(2, 3, 0x18);
        } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_B9C) {
            SetFielderAct(2, 3, 0x18);
            SetFielderAct(3, 3, 0x18);
        } else {
            SetFielderAct(3, 3, 0x18);
            SetFielderAct(8, 3, 0x18);
        }
    } else if (*(s16*)(g_Ball + 0x1B9A) > 0x800) {
        SetFielderAct(4, 3, 0x18);
    } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_BA0) {
        SetFielderAct(1, 3, 0x18);
        SetFielderAct(4, 3, 0x18);
    } else if (*(f32*)(g_Ball + 0x34C) < lbl_3_rodata_B9C) {
        SetFielderAct(4, 3, 0x18);
        SetFielderAct(5, 3, 0x18);
    } else {
        SetFielderAct(5, 3, 0x18);
        SetFielderAct(6, 3, 0x18);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

extern f32 lbl_3_rodata_B60;
extern f32 lbl_3_rodata_C08;
extern f32 lbl_3_rodata_BA4;
extern f32 lbl_3_rodata_BCC;
extern f32 lbl_3_rodata_B90;
extern f32 lbl_3_rodata_BE4;
extern f32 lbl_3_rodata_C28;
extern f32 lbl_3_rodata_C2C;
extern f32 lbl_3_rodata_C30;
extern f32 lbl_3_rodata_C34;
extern f32 lbl_3_rodata_BD0;
extern f32 lbl_3_data_4780[];
extern f32 lbl_3_rodata_BF4;
extern f32 lbl_3_rodata_C58;
extern f32 lbl_3_rodata_C5C;
extern f32 lbl_3_rodata_C60;
extern f32 lbl_3_rodata_C3C;
extern f32 lbl_3_rodata_C40;
extern f32 lbl_3_rodata_B74;
extern f32 lbl_3_rodata_C44;
extern f32 lbl_3_rodata_C4C;
extern f32 lbl_3_rodata_BC4;
extern f32 lbl_3_rodata_BC8;
extern f32 lbl_3_rodata_B8C;
extern u8 g_Scores[];
extern int fn_3_B7D6C(f32 a, f32 b);
extern int fn_3_B7E10(f32 a, f32 b);
#define FLD(n) (g_Fielders + (n) * 0x268) // fielder n's 0x268-byte block
#define RUN(n) (g_Runners + (n) * 0x154)  // runner n's 0x154-byte block
extern u8 lbl_3_data_44B4[];
extern f32 lbl_3_rodata_BD4;
extern f32 lbl_3_rodata_BE8;
extern f32 lbl_3_rodata_C64;
extern f32 lbl_3_rodata_C68;
extern int fn_3_B7E44(s16 a, f32 y);
#pragma dont_inline off
// Inlined copy of fn_3_52560 (frames for fielder i to reach x/z); defined later in this file.
static inline int FramesToReachAC8(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 d;
    f32 spd;
    if (x == *(f32*)f && z == *(f32*)(f + 8)) {
        return 1;
    }
    d = (x - *(f32*)f) * (x - *(f32*)f) + (z - *(f32*)(f + 8)) * (z - *(f32*)(f + 8));
    SQRT_L(d);
    spd = *(f32*)(f + 0x58);
    return ((u32)f[0x1D1] >> 1) + (int)(d / (lbl_3_rodata_B20 == spd ? lbl_3_rodata_B60 : spd));
}
// Fielder i goes to cover its assigned base (0x18C), or relays/backs up.
static inline void FielderGoCoverAC8(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (f[0x1D7] == 1) {
        SetFielderAct(i, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD0 + *(s16*)(f + 0x18C) * 2) = i;
    } else if (*(s16*)(f + 0x18C) == 6) {
        SetFielderAct(i, 0xB, 0x58);
    } else {
        SetFielderAct(i, 0xC, 0x60);
        f[0x1D5] = 4;
    }
}
// Fielder i stops covering its base (0x18C), clearing the base's cover slot if it held it.
static inline void FielderReleaseCoverAC8(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 t = *(s16*)(f + 0x18C);
    if (t < 0) {
        return;
    }
    if (t <= 3) {
        if (*(s16*)(g_FieldingLogic + 0xD0 + t * 2) == i) {
            *(s16*)(g_FieldingLogic + 0xD0 + t * 2) = -1;
            g_FieldingLogic[t + 0x101] = 0;
        }
        *(s16*)(f + 0x18C) = -1;
        f[0x1D7] = 0;
        if (f[0x1D3] == 1) {
            SetFielderAct(i, 0xC, 0x60);
        }
    } else if (t == 5) {
        *(s16*)(f + 0x18C) = -1;
        f[0x1D7] = 0;
        *(s16*)(g_FieldingLogic + 0xD8) = -1;
        g_FieldingLogic[0x105] = 0;
        if (f[0x1D3] == 0xE) {
            SetFielderAct(i, 0xC, 0x60);
        }
    }
}
void fn_3_48480(int);
// After becoming the ball chaser, fielder i runs fn_3_48480 and gives up any base it was covering.
static inline void FielderTakeOverAC8(int i) {
    fn_3_48480(i);
    if (*(s16*)(g_FieldingLogic + 0xD8) != i && *(s16*)(g_Fielders + i * 0x268 + 0x18C) < 0) {
        return;
    }
    FielderReleaseCoverAC8(i);
}
// Same as SetTargetAC8 (defined later in this file).
static inline void SetTargetAC8b(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    *(f32*)(f + 0x14) = x;
    *(f32*)(f + 0x1C) = z;
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}
#pragma dont_inline on

// .text:0x0003F760 size:0x590 mapped:0x8067E7F4
// NONMATCHING 99.2%: registers only; the known SetFielderAct state/table-value r0/r3 swap (see docs/patterns rep_AC8 dead ends)
#if NONMATCHING
// Assign base-covering duties (state 3) to infielders at the start of a play.
void fn_3_3F760(void) {
    int a;
    int b;
    s16 t;
    f32 d;
    SetFielderAct(0, 3, 0x18);
    if (FLD(1)[0x1DA] == 0) {
        if (RUN(3)[0x123] == 1 && RUN(3)[0x137] == 1 && *(f32*)(RUN(3) + 0x64) >= lbl_3_rodata_BCC && (t = *(s16*)(FLD(1) + 0x186)) > 0) {
            d = *(f32*)(g_Ball + t * 0x10 + 0x354) * *(f32*)(g_Ball + t * 0x10 + 0x354) +
                *(f32*)(g_Ball + t * 0x10 + 0x35C) * *(f32*)(g_Ball + t * 0x10 + 0x35C);
            SQRT_L(d);
            if (d < lbl_3_rodata_B64) {
                SetFielderAct(1, 3, 0x18);
            }
        } else {
            SetFielderAct(1, 3, 0x18);
        }
    }
    if (*(s16*)(g_Ball + 0x1B9C) < 0x400) {
        if (FLD(2)[0x1DA] == 0) {
            a = *(s16*)(FLD(3) + 0x186);
            b = *(s16*)(FLD(2) + 0x186);
            if (a - 15 < b) {
                if (*(s16*)(FLD(0) + 0x186) - a < 0x78) {
                    SetFielderAct(3, 3, 0x18);
                }
            } else if (*(f32*)(g_Ball + b * 0x10 + 0x35C) < *(f32*)(lbl_3_data_4444 + 0xC)) {
                if (*(s16*)(FLD(0) + 0x186) - b < 0x50) {
                    SetFielderAct(2, 3, 0x18);
                }
            } else if (*(s16*)(FLD(0) + 0x186) - a < 0x78) {
                SetFielderAct(3, 3, 0x18);
            }
        } else if (FLD(3)[0x1DA] == 0) {
            if (*(s16*)(FLD(0) + 0x186) - *(s16*)(FLD(3) + 0x186) < 0x78) {
                SetFielderAct(3, 3, 0x18);
            }
        }
    } else {
        if (FLD(4)[0x1DA] == 0) {
            a = *(s16*)(FLD(5) + 0x186);
            b = *(s16*)(FLD(4) + 0x186);
            if (a - 15 < b) {
                if (*(s16*)(FLD(0) + 0x186) - a < 0x78) {
                    SetFielderAct(5, 3, 0x18);
                }
            } else if (*(f32*)(g_Ball + b * 0x10 + 0x35C) < *(f32*)(lbl_3_data_4444 + 0xC)) {
                if (RUN(2)[0x123] != 1 || (s16)b <= 0) {
                    if (*(s16*)(FLD(0) + 0x186) - b < 0x50) {
                        SetFielderAct(4, 3, 0x18);
                    }
                }
            } else if (*(s16*)(FLD(0) + 0x186) - a < 0x78) {
                SetFielderAct(5, 3, 0x18);
            }
        } else if (FLD(5)[0x1DA] == 0) {
            if (*(s16*)(FLD(0) + 0x186) - *(s16*)(FLD(5) + 0x186) < 0x78) {
                SetFielderAct(5, 3, 0x18);
            }
        }
    }
}
#endif

// .text:0x0003FCF0 size:0x5B8 mapped:0x8067ED84
// NONMATCHING 91.5%: registers (SetFielderAct swap) and block order around the 2/3-of-gap compares
#if NONMATCHING
// Split base-covering duties between infielders by the batted ball's angle
// (useBall: take the angle from the ball's current position instead of ball+0x1B9C).
void fn_3_3FCF0(int useBall) {
    int ang = *(s16*)(g_Ball + 0x1B9C);
    int a2, a3, a4, a5;
    int q;
    if (useBall != 0) {
        ang = (s16)fn_3_9FB8C(*(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x350));
    }
    a2 = *(s16*)(FLD(2) + 0x182);
    a3 = *(s16*)(FLD(3) + 0x182);
    a4 = *(s16*)(FLD(4) + 0x182);
    a5 = *(s16*)(FLD(5) + 0x182);
    if (FLD(0)[0x1DA] == 0 && *(f32*)(g_Ball + 0x350) < lbl_3_rodata_B90 && *(f32*)(g_Ball + 0x19D4) < lbl_3_rodata_BD8) {
        fn_3_3F760();
        return;
    }
    if (ang < a2 + (a3 - a2) / 5) {
        SetFielderAct(2, 3, 0x18);
        SetFielderAct(3, 3, 0x18);
    } else if (ang < (a2 + a3) / 2) {
        SetFielderAct(2, 3, 0x18);
        SetFielderAct(3, 3, 0x18);
    } else if (ang < a3 + (q = (a5 - a3) / 3)) {
        SetFielderAct(3, 3, 0x18);
        if (ang > *(s16*)(FLD(0) + 0x182) - 0x40) {
            SetFielderAct(0, 4, 0x20);
        }
    } else if (ang < a3 + q * 2) {
        SetFielderAct(0, 4, 0x20);
        if (__abs(ang - *(s16*)(FLD(3) + 0x182)) < __abs(ang - *(s16*)(FLD(5) + 0x182))) {
            SetFielderAct(3, 3, 0x18);
        } else {
            SetFielderAct(5, 3, 0x18);
        }
    } else if (ang < a5 + (q = (a4 - a5) / 3)) {
        SetFielderAct(5, 3, 0x18);
        if (ang < *(s16*)(FLD(0) + 0x182) + 0x40) {
            SetFielderAct(0, 4, 0x20);
        }
    } else if (ang < a5 + q * 2) {
        SetFielderAct(4, 3, 0x18);
        SetFielderAct(5, 3, 0x18);
    } else {
        SetFielderAct(4, 3, 0x18);
        SetFielderAct(5, 3, 0x18);
    }
}
#endif

// .text:0x000402A8 size:0x95C mapped:0x8067F33C
// NONMATCHING 95.6%: registers (SetFielderAct swap); orig keeps the infield mask and ball base in swapped saved regs
#if NONMATCHING
// Assign base-covering duties at the start of a play, by the ball's direction and which
// fielders are free (0x1DB == 0), then run the other per-play fielding setups.
void fn_3_402A8(void) {
    u32 mask = 0;
    u32 inf;
    int j;
    s16 ang;
    int a;
    f32 d3, d5, dx, dz;
    for (j = 0; j < 9; j++) {
        if (FLD(j)[0x1DB] == 0) {
            mask |= 1 << (j * 3);
        }
    }
    inf = mask & 0x9249;
    if ((inf != 0 && g_Ball[0x1BBF] <= 1 && *(f32*)(g_Ball + 0x19D4) >= lbl_3_rodata_BD8) ||
        ((FLD(0)[0x1DB] == 0 || FLD(1)[0x1DB] == 0) && *(f32*)(g_Ball + 0x350) < lbl_3_rodata_C28)) {
        ang = fn_3_9FB8C(*(f32*)(g_Ball + 0x1A2C), *(f32*)(g_Ball + 0x1A30));
        if (FLD(1)[0x1DB] == 0 && (*(f32*)(g_Ball + 0x350) < lbl_3_rodata_BE4 || (ang > 0xA00 && ang < 0xE00))) {
            SetFielderAct(1, 3, 0x18);
            goto done;
        }
        if ((*(f32*)(g_Ball + 0x350) < lbl_3_rodata_C2C && ang > 0x300 && ang < 0x500) ||
            (*(f32*)(g_Ball + 0x350) < lbl_3_rodata_C30 && ang > 0x300 && ang < 0x500 && (mask & 1)) ||
            (*(f32*)(g_Ball + 0x350) < lbl_3_rodata_C34 && ang > 0x200 && ang < 0x600)) {
            SetFielderAct(0, 3, 0x18);
            goto done;
        }
        if (ang < 0x2C0) {
            SetFielderAct(2, 3, 0x18);
            goto done;
        }
        if (ang < 0x400) {
            SetFielderAct(3, 3, 0x18);
            goto done;
        }
        if (ang < 0x540) {
            SetFielderAct(5, 3, 0x18);
            goto done;
        }
        if (ang < 0x800) {
            SetFielderAct(4, 3, 0x18);
            goto done;
        }
    }
    if (mask & 0x1240000) {
        fn_3_9FB8C(*(f32*)(g_Ball + 0x1A2C), *(f32*)(g_Ball + 0x1A30));
        a = *(s16*)(g_Ball + 0x1B9C);
        if (a < 0x3C0) {
            SetFielderAct(8, 3, 0x18);
            SetFielderAct(7, 3, 0x18);
            SetFielderAct(3, 3, 0x18);
        } else if (a > 0x440) {
            SetFielderAct(6, 3, 0x18);
            SetFielderAct(7, 3, 0x18);
            SetFielderAct(5, 3, 0x18);
        } else {
            SetFielderAct(6, 3, 0x18);
            SetFielderAct(7, 3, 0x18);
            SetFielderAct(8, 3, 0x18);
            dx = *(f32*)FLD(3) - *(f32*)(g_Ball + 0x1A2C);
            dz = *(f32*)(FLD(3) + 8) - *(f32*)(g_Ball + 0x1A30);
            dx = dx * dx;
            dz = dz * dz;
            d3 = dx + dz;
            SQRT_L(d3);
            dx = *(f32*)FLD(5) - *(f32*)(g_Ball + 0x1A2C);
            dz = *(f32*)(FLD(5) + 8) - *(f32*)(g_Ball + 0x1A30);
            dx = dx * dx;
            dz = dz * dz;
            d5 = dx + dz;
            SQRT_L(d5);
            if (g_Ball[0x1BBF] < 3 || !(*(f32*)(g_Ball + 0x19D4) >= lbl_3_rodata_BD8)) {
                if (d3 < d5) {
                    SetFielderAct(3, 3, 0x18);
                } else {
                    SetFielderAct(5, 3, 0x18);
                }
            }
        }
    } else {
        fn_3_3FCF0(inf);
    }
done:
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_4A124();
}
#endif

// .text:0x00040C04 size:0x150 mapped:0x8067FC98
// 98%: temp regs in the two tail blocks (orig li r4,3 / lwz r0 / g in r5; ours li r0 / lwz r5 / g r4); same issue as fn_3_3F124
void fn_3_40C04(void) {
    int i;
    for (i = 2; i < 6; i++) {
        if (g_Fielders[i * 0x268 + 0x1DD] == 2) {
            SetFielderAct(i, 3, 0x18);
            break;
        }
    }
    if (i == 2) {
        SetFielderAct(3, 3, 0x18);
    }
    if (i == 4) {
        SetFielderAct(5, 3, 0x18);
    }
    fn_3_40D88();
}

// .text:0x00040D54 size:0x34 mapped:0x8067FDE8
void fn_3_40D54(void) {
    fn_3_49F40(6, 7);
    fn_3_49F40(8, 6);
}

// .text:0x00040D88 size:0x424 mapped:0x8067FE1C
void fn_3_40D88(void) {
    if (g_Fielders[0x151B] == 0 && g_Fielders[0x104B] == 0) {
        SetFielderAct(6, 3, 0x18);
        SetFielderAct(7, 3, 0x18);
        SetFielderAct(8, 3, 0x18);
    } else if (g_Fielders[0x151B] == 0) {
        SetFielderAct(8, 3, 0x18);
        SetFielderAct(7, 3, 0x18);
    } else if (g_Fielders[0x104B] == 0) {
        SetFielderAct(6, 3, 0x18);
        SetFielderAct(7, 3, 0x18);
    } else if (g_Fielders[0x12B3] == 0) {
        SetFielderAct(6, 3, 0x18);
        SetFielderAct(7, 3, 0x18);
        SetFielderAct(8, 3, 0x18);
    } else if (*(s16*)(g_Fielders + 0x125A) > *(s16*)(g_Ball + 0x1B9C)) {
        SetFielderAct(8, 3, 0x18);
        SetFielderAct(7, 3, 0x18);
    } else {
        SetFielderAct(6, 3, 0x18);
        SetFielderAct(7, 3, 0x18);
    }
    fn_3_4C9C8();
    fn_3_47778();
    fn_3_40D54();
}

// .text:0x000411AC size:0x628 mapped:0x80680240
// NONMATCHING 99.9%: registers only: the SetFielderAct r0/r4 swap and f1/f2 for dx*dx
#if NONMATCHING
// Start-of-play fielding setup: per-fielder angle/distance bookkeeping, then pick
// the covering scheme (fn_3_402A8 / fn_3_40C04 / fn_3_40D88 / fn_3_3F24C).
void fn_3_411AC(void) {
    int sh;
    int j;
    s64 mask = 0;
    u8* f;
    int a;
    f32 d;
    f32 dx, dz;
    g_FieldingLogic[0x123] = 0;
    if (g_Scores[0xAA] <= *(int*)g_Scores && g_Scores[0xAD] != 0 && *(s16*)(g_Scores + 4) == *(s16*)(g_Scores + 0x2A) &&
        g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142] != 0 && *(int*)(g_Strikes + 0xC) <= 1 &&
        (*(s16*)(g_RunningLogic + 2) & 0x1000) && fn_3_B7E10(*(f32*)(g_Ball + 0x1A2C), *(f32*)(g_Ball + 0x1A30)) != 0 &&
        fn_3_B7D6C(*(f32*)(g_Ball + 0x1A2C), *(f32*)(g_Ball + 0x1A30)) == 0 && *(f32*)(g_Ball + 0x350) > lbl_3_rodata_C00) {
        g_FieldingLogic[0x123] = 1;
    }
    for (j = 0, sh = 0; j < 9; j++, sh += 3) {
        f = g_Fielders + j * 0x268;
        if (j == 1) {
            *(s16*)(f + 0x182) = 0x400;
        } else if (0.0f == *(f32*)f) {
            *(s16*)(f + 0x182) = 0x400;
        } else {
            a = lbl_3_rodata_BC4 * (f32)atan2(*(f32*)(f + 8), *(f32*)f) / lbl_3_rodata_BC8;
            if (a < 0) {
                a += 0x800;
            }
            *(s16*)(f + 0x182) = a;
        }
        d = *(f32*)f * *(f32*)f + *(f32*)(f + 8) * *(f32*)(f + 8);
        SQRT_L(d);
        *(f32*)(f + 0x70) = d;
        dx = *(f32*)(g_Ball + 0x1A2C) - *(f32*)f;
        dz = *(f32*)(g_Ball + 0x1A30) - *(f32*)(f + 8);
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        *(f32*)(f + 0x80) = d;
        if (j == 1) {
            ((void (*)(int))fn_3_4F504)(1);
        } else {
            ((void (*)(int))fn_3_4FB34)(j);
        }
        if (f[0x1DD] == 1) {
            mask |= 4 << sh;
        } else if (f[0x1DD] == 2) {
            mask |= 2 << sh;
        } else if (f[0x1DD] == 3) {
            mask |= 1 << sh;
        }
    }
    if (g_Ball[0x1BCE] != 0) {
        SetFielderAct(0, 0x14, 0xA0);
        if ((*(s16*)(FLD(3) + 0x182) + *(s16*)(FLD(5) + 0x182)) / 2 > *(s16*)(g_Ball + 0x1B9C)) {
            SetFielderAct(3, 3, 0x18);
        } else {
            SetFielderAct(5, 3, 0x18);
        }
        fn_3_4C9C8();
        fn_3_47778();
        fn_3_4A124();
    } else if (g_Ball[0x1BC5] == 7 || g_Ball[0x1BC5] == 8) {
        fn_3_3F24C();
    } else if ((mask & 0x3FFFF) == 0) {
        if (*(f32*)(g_Ball + 0x19D4) < lbl_3_rodata_B8C) {
            fn_3_402A8();
        } else {
            fn_3_40D88();
        }
    } else if (mask & 0x2DB6D) {
        fn_3_402A8();
    } else if (mask & 0x12480) {
        fn_3_40C04();
    } else if (mask & 2) {
        fn_3_402A8();
    }
}
#endif

// .text:0x000417D4 size:0x1A8 mapped:0x80680868
void fn_3_417D4(int i) {
    int off = i * 0x268;
    u8* f = g_Fielders + off;
    u8* g;
    f32 dx;
    f32 dz;
    f32 d;
    f32 a;
    f32 b;
    dx = *(f32*)(g_Ball + 0x3F4) - *(f32*)f;
    dz = *(f32*)(g_Ball + 0x3FC) - *(f32*)(f + 8);
    a = dx * dx;
    b = dz * dz;
    d = a + b;
    SQRT_L(d);
    if (d < lbl_3_rodata_C38 && f[0x1DD] == 2 && *(f32*)(g_Ball + 0x3F8) > *(f32*)(f + 0xF4)) {
        *(s16*)(f + 0x198) = 0;
        g = g_Fielders;
        g += off;
        *(f32*)(g + 0x14) = *(f32*)f;
        *(f32*)(g + 0x18) = *(f32*)(f + 4);
        *(f32*)(g + 0x1C) = *(f32*)(f + 8);
        *(f32*)(g + 0x30) = lbl_3_rodata_B20;
        *(f32*)(g + 0x34) = lbl_3_rodata_B20;
        *(f32*)(g + 0x50) = lbl_3_rodata_B20;
        *(f32*)(g + 0x68) = lbl_3_rodata_B20;
    }
}

// .text:0x0004197C size:0x3FC mapped:0x80680A10
// NONMATCHING 94.0%: register allocation and constant-load scheduling in the distance loop
#if NONMATCHING
// Pick the fielder closest to the ball's landing spot and send it after the ball.
// mode 1: a nearby fielder that is free takes it immediately.
void fn_3_4197C(int mode) {
    u8* f;
    f32 best;
    f32 d;
    f32 e;
    f32 dx, dz;
    int j;
    int idx;
    s16 t;
    best = lbl_3_rodata_BA4;
    for (j = 0; j < 9; j++) {
        f = g_Fielders + j * 0x268;
        dx = *(f32*)(g_Ball + 0x8F4) - *(f32*)f;
        dz = *(f32*)(g_Ball + 0x8FC) - *(f32*)(f + 8);
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        e = d;
        if (mode == 1 && *(s16*)(f + 0x19C) != 0 && f[0x1E0] != 1 && f[0x1E0] != 2 && d < lbl_3_rodata_B78) {
            SetFielderAct(j, 0x12, 0x90);
            fn_3_43038(j);
            return;
        }
        if (g_FieldingLogic[j + 0xF8] == 4) {
            e -= lbl_3_rodata_B78;
        }
        if (g_FieldingLogic[j + 0xF8] == 1) {
            if (best > e - lbl_3_rodata_B64) {
                best = e;
                idx = j;
            }
        } else if (best > e) {
            idx = j;
            best = e;
        }
    }
    f = g_Fielders + idx * 0x268;
    t = *(s16*)(f + 0x18C);
    if (t != 0) {
        if (t >= 0 && t <= 3) {
            if (*(s16*)(g_FieldingLogic + 0xD0 + t * 2) == idx) {
                *(s16*)(g_FieldingLogic + 0xD0 + t * 2) = -1;
                g_FieldingLogic[t + 0x101] = 0;
            }
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            if (f[0x1D3] == 1) {
                SetFielderAct(idx, 0xC, 0x60);
            }
        } else if (t == 5) {
            *(s16*)(f + 0x18C) = -1;
            f[0x1D7] = 0;
            *(s16*)(g_FieldingLogic + 0xD8) = -1;
            g_FieldingLogic[0x105] = 0;
            if (f[0x1D3] == 0xE) {
                SetFielderAct(idx, 0xC, 0x60);
            }
        }
    }
    SetFielderAct(idx, 0x12, 0x90);
    fn_3_43038(idx);
}
#endif

// .text:0x00041D78 size:0x304 mapped:0x80680E0C
// NONMATCHING 98.7%: second loop's counter/state registers swapped (orig inits counter with mr from busy)
#if NONMATCHING
// When no fielder is chasing the ball any more, pick one to go after it.
void fn_3_41D78(void) {
    int found = 0;
    int j;
    int busy;
    u8 st;
    f32 dx, dz, d, dx2, dz2;
    if (g_Ball[0x1BD1] == 0 && *(s16*)(g_Ball + 0x1B7A) != -1 && g_Ball[0x1BC9] != 1 && g_FieldingLogic[0x13F] == 0) {
        if (g_Ball[0x1BC9] == 2) {
            if (*(s16*)(g_Ball + 0x1B62) > 0 && *(s16*)(g_Ball + 0x1B8A) >= 0) {
                return;
            }
            dx = *(f32*)(g_Ball + 0x1A34) - *(f32*)g_Ball;
            dz = *(f32*)(g_Ball + 0x1A38) - *(f32*)(g_Ball + 8);
            dx2 = dx * dx;
            dz2 = dz * dz;
            d = dx2 + dz2;
            SQRT_L(d);
            if (!(d > lbl_3_rodata_B64 + *(f32*)(g_Ball + 0x1A4C))) {
                return;
            }
        }
        for (j = 0; j < 9; j++) {
            if (g_FieldingLogic[j + 0xF8] == 1 || g_FieldingLogic[j + 0xF8] == 7) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            fn_3_4197C(0);
            return;
        }
        busy = 0;
        for (j = 0; j < 9; j++) {
            st = g_Fielders[j * 0x268 + 0x1D3];
            if (st == 2 || (u8)(st - 3) <= 1 || st == 0x12) {
                busy = 1;
                break;
            }
        }
        if (busy == 0) {
            fn_3_4197C(0);
        }
    }
}
#endif

// .text:0x0004207C size:0x7D4 mapped:0x80681110
// NONMATCHING 98.8%: loop constant/pointer setup order and one early-return shape; registers
#if NONMATCHING
// Infielder i decides whether to cover a base, relay, or back up (after a hit).
void fn_3_4207C(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 t;
    int j;
    int k;
    u8* g;
    if (g_Ball[0x1BD1] != 0) {
        SetFielderAct(i, 0xC, 0x60);
        return;
    }
    if (i <= 5) {
        if (g_Ball[0x1BC9] == 3) {
            if (g_Ball[0x1BBE] > 2) {
                SetFielderAct(i, 0xB, 0x58);
            }
            return;
        }
        t = *(s16*)(g_Ball + 0x1B7A);
        if (t == 1 && lbl_3_rodata_B60 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x1A00)) {
            if (i == 0) {
                SetFielderAct(i, 9, 0x48);
                return;
            }
            if (i != 1) {
                if (g_Ball[0x1BBE] > 1) {
                    SetFielderAct(i, 0xB, 0x58);
                    return;
                }
                SetFielderAct(i, 0xC, 0x60);
                f[0x1D5] = 4;
                return;
            }
        }
        if (*(f32*)(g_Ball + 0x350) > lbl_3_rodata_BD0 && *(f32*)(f + 0x68) < lbl_3_rodata_BA0 && t == 0) {
            for (j = 6; j < 9; j++) {
                g = g_Fielders + j * 0x268;
                if (g[0x1DB] == 0 && *(s16*)(g + 0x17E) > 0 && *(s16*)(f + 0x17E) > *(s16*)(g + 0x17E) - 20) {
                    FielderGoCoverAC8(i);
                    return;
                }
            }
        }
        if (t == 0) {
            for (j = 0; j < 6; j++) {
                if (j != 1 && lbl_3_rodata_BA0 + *(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x1A00)) {
                    FielderGoCoverAC8(i);
                    return;
                }
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (j != i && g_FieldingLogic[j + 0xF8] == 1 && ((f32*)(f + 0x84))[j] < lbl_3_rodata_B78) {
            g = g_Fielders + j * 0x268;
            if (*(s16*)(f + 0x17E) < *(s16*)(g + 0x17E)) {
                g[0x1D6] = 9;
                f[0x1D6] = 0;
            } else {
                g[0x1D6] = 0;
                f[0x1D6] = 9;
            }
        }
    }
    k = *(s16*)(g_Ball + 0x1B7E);
    if (k == -1 || i == k) {
        return;
    }
    if (f[0x1D7] == 1) {
        SetFielderAct(i, 1, 8);
        *(s16*)(g_FieldingLogic + 0xD0 + *(s16*)(f + 0x18C) * 2) = i;
    } else if (*(s16*)(f + 0x18C) == 6) {
        SetFielderAct(i, 0xB, 0x58);
    } else if (i >= 6 || *(f32*)(f + 0x70) > *(f32*)(g_Fielders + k * 0x268 + 0x70)) {
        if (f[0x1C5] != 0) {
            SetFielderAct(i, 0xD, 0x68);
        } else {
            SetFielderAct(i, 0x10, 0x80);
        }
    } else {
        SetFielderAct(i, 0xC, 0x60);
    }
}
#endif

// .text:0x00042850 size:0x1B0 mapped:0x806818E4
void fn_3_42850(int i) {
    u8* f;
    f32 dz, d, bz, dx, bx, a2;
    bx = *(f32*)g_Ball;
    bz = *(f32*)(g_Ball + 8);
    f = g_Fielders + i * 0x268;
    *(f32*)(f + 0x14) = bx;
    *(f32*)(f + 0x1C) = bz;
    dx = bx - *(f32*)f;
    dz = bz - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = (f32)atan2(dz, dx);
        a2 = dz * dz;
        d = dx * dx + a2;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}

// .text:0x00042A00 size:0x1D0 mapped:0x80681A94
void fn_3_42A00(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dz;
    f32 dx;
    f32 d;
    u8* b;
    f32 bx;
    f32 bz;
    b = g_Ball;
    b += *(s16*)(f + 0x184) * 0x10;
    bx = *(f32*)(b + 0x354);
    bz = *(f32*)(b + 0x35C);
    *(f32*)(f + 0x14) = bx;
    *(f32*)(f + 0x1C) = bz;
    dx = bx - *(f32*)f;
    dz = bz - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
    if (*(s16*)(f + 0x184) <= 1) {
        f[0x1DC] = 5;
    }
}

// .text:0x00042BD0 size:0x10C mapped:0x80681C64
void fn_3_42BD0(int i) {
    u8* f = g_Fielders + i * 0x268;
    u8* o;
    int j;
    if (i >= 6 && g_Ball[0x1BC9] == 0) {
        if (*(f32*)(f + 0x70) < *(f32*)(g_Ball + 0x1A00)) {
            fn_3_43038(i);
            return;
        }
        for (j = 6; j < 9; j++) {
            o = g_Fielders + j * 0x268;
            if (j != i && o[0x1DC] == 3 && *(s16*)(o + 0x17E) <= *(s16*)(f + 0x17E) && *(s16*)(o + 0x17E) < 0x5A) {
                fn_3_43038(i);
                return;
            }
        }
    }
}

// .text:0x00042CDC size:0x35C mapped:0x80681D70
// Fielder i heads for where the ball will be in 5 frames, or a spot picked by fn_3_50DD8.
void fn_3_42CDC(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 x;
    f32 z;
    *(f32*)(f + 0x28) = lbl_3_rodata_B64 * *(f32*)(g_Ball + 0x19E4) + *(f32*)(g_Ball + 0x19D8);
    *(f32*)(f + 0x2C) = lbl_3_rodata_B64 * *(f32*)(g_Ball + 0x19E8) + *(f32*)(g_Ball + 0x19DC);
    if (*(s16*)(f + 0x18A) != 0) {
        f32 dz, dx, d;
        ((int (*)(int, f32*, f32*, int))fn_3_50DD8)(i, &x, &z, 1);
        *(f32*)(f + 0x14) = x;
        *(f32*)(f + 0x1C) = z;
        dx = x - *(f32*)f;
        dz = z - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
        }
        f[0x1D9] = 1;
        *(f32*)(f + 0x20) = x;
        *(f32*)(f + 0x24) = z;
    } else {
        f32 dz, dx, d, ox, oz;
        oz = *(f32*)(f + 0x2C);
        ox = *(f32*)(f + 0x28);
        *(f32*)(f + 0x14) = ox;
        *(f32*)(f + 0x1C) = oz;
        dx = ox - *(f32*)f;
        dz = oz - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
        }
        f[0x1D9] = 1;
    }
}

// .text:0x00043038 size:0x3A8 mapped:0x806820CC
// NONMATCHING 97.0%: float register allocation in the inlined fn_3_52560 distance code
#if NONMATCHING
// Send fielder i to the first point of the ball's flight (below catch height) it can reach in time.
void fn_3_43038(int i) {
    u8* f = g_Fielders + i * 0x268;
    int frames;
    int t;
    u8* b;
    f[0x1DC] = 4;
    frames = 0;
    t = 5;
    while (t <= 0x78) {
        b = g_Ball + t * 0x10;
        if (*(f32*)(b + 0x358) > lbl_3_rodata_C08) {
            t++;
            continue;
        }
        frames = FramesToReachAC8(i, *(f32*)(b + 0x354), *(f32*)(b + 0x35C));
        if (frames < t) {
            *(s16*)(f + 0x184) = t;
            goto found;
        }
        t += 5;
    }
    *(s16*)(f + 0x184) = 0x78;
found:
    b = g_Ball + *(s16*)(f + 0x184) * 0x10;
    SetTargetAC8b(i, *(f32*)(b + 0x354), *(f32*)(b + 0x35C));
    if (*(s16*)(f + 0x184) >= 0x78) {
        *(s16*)(f + 0x17E) = 0x78;
    } else {
        *(s16*)(f + 0x17E) = frames;
    }
}
#endif

// .text:0x000433E0 size:0x13E4 mapped:0x80682474
// NONMATCHING 94.4%: switch lowered as compare chain in a different order, lfsx trajectory loads, and set-target float registers
#if NONMATCHING
// Per-frame update of a fielder chasing the ball: pick the target by chase mode (0x1DC) and run there.
void fn_3_433E0(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 x;
    f32 z;
    f32 d, r, px, pz;
    int t;
    int n;
    if (*(s16*)(g_Ball + 0x1B8C) == 3) {
        fn_3_43038(i);
    }
    if (*(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_B7C && g_Ball[0x1BC9] != 0 && g_Ball[0x1BC9] != 1) {
        if (*(s16*)(g_Ball + 0x1B7A) != 0) {
            f[0x1DC] = 5;
        }
    } else if (*(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_B24 && g_Ball[0x1BBE] >= 3 && *(s16*)(g_Ball + 0x1B7A) >= 1 &&
               *(s16*)(g_Ball + 0x1B7A) <= 3 && f[0x1DC] != 4 && f[0x1DC] != 5) {
        fn_3_43038(i);
    } else if (g_FieldingLogic[0x107] == 3 && *(s16*)(g_Ball + 0x1B66) <= 0xB4 && i == 1 && f[0x1DC] != 4) {
        fn_3_43038(i);
    }
    if (g_Ball[0x1BF3] != 0) {
        // Ball already close to the ground near the fielder: step towards it.
        x = *(f32*)g_Ball - *(f32*)f;
        z = *(f32*)(g_Ball + 8) - *(f32*)(f + 8);
        {
            f32 a = x * x;
            f32 b = z * z;
            d = a + b;
            SQRT_L(d);
        }
        r = *(f32*)(lbl_3_data_4930 + 0x90);
        if (d < r) {
            f32 dz, dx, dd, ox, oz;
            oz = *(f32*)(f + 8);
            ox = *(f32*)f;
            *(f32*)(f + 0x14) = ox;
            *(f32*)(f + 0x1C) = oz;
            dx = ox - *(f32*)f;
            dz = oz - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                *(f32*)(f + 0x68) = dd;
            }
            f[0x1D9] = 1;
        } else {
            r = r - lbl_3_rodata_B60;
            x = r * (x / d) + *(f32*)f;
            z = r * (z / d) + *(f32*)(f + 8);
            SetTargetAC8b(i, x, z);
        }
    } else if (g_FieldingLogic[0x123] != 0) {
        // Ball heading over the fence: go to the wall below its path.
        t = *(s16*)(f + 0x184);
        if (t > 1) {
            px = *(f32*)(g_Ball + t * 0x10 + 0x354);
            pz = *(f32*)(g_Ball + t * 0x10 + 0x35C);
            d = px * px + pz * pz;
            SQRT_L(d);
            px = *(f32*)(g_Ball + *(s16*)(f + 0x184) * 0x10 + 0x354);
            pz = *(f32*)(g_Ball + *(s16*)(f + 0x184) * 0x10 + 0x35C);
            x = lbl_3_rodata_B80 * (px / d) + px;
            z = lbl_3_rodata_B80 * (pz / d) + pz;
            if (x < 0.0f) {
                x = x + lbl_3_rodata_BA0;
            } else {
                x = x - lbl_3_rodata_BA0;
            }
            z = z + lbl_3_rodata_BD8;
            SetTargetAC8b(i, x, z);
        }
    } else {
        switch (f[0x1DC]) {
        case 0:
            if (*(s16*)(f + 0x184) > 1) {
                if (*(s16*)(f + 0x18A) != 0) {
                    ((int (*)(int, f32*, f32*, int))fn_3_50DD8)(i, &x, &z, 1);
                    *(f32*)(f + 0x20) = x;
                    *(f32*)(f + 0x24) = z;
                } else {
                    t = *(s16*)(f + 0x184);
                    px = *(f32*)(g_Ball + t * 0x10 + 0x354);
                    pz = *(f32*)(g_Ball + t * 0x10 + 0x35C);
                    d = px * px + pz * pz;
                    SQRT_L(d);
                    px = *(f32*)(g_Ball + *(s16*)(f + 0x184) * 0x10 + 0x354);
                    pz = *(f32*)(g_Ball + *(s16*)(f + 0x184) * 0x10 + 0x35C);
                    x = lbl_3_rodata_B80 * (px / d) + px;
                    z = lbl_3_rodata_B80 * (pz / d) + pz;
                    if (g_Ball[0x1BEB] != 0) {
                        if (((u8*)g_AiLogic)[0x79] != 0) {
                            x = *(f32*)(g_Ball + 0x1B1C);
                            z = *(f32*)(g_Ball + 0x1B20);
                        } else {
                            x = *(f32*)(g_Ball + 0x348);
                            z = *(f32*)(g_Ball + 0x34C);
                        }
                    } else if (g_Ball[0x1BED] != 0) {
                        x = *(f32*)(g_Ball + 0x1B1C);
                        z = *(f32*)(g_Ball + 0x1B20);
                    }
                }
                SetTargetAC8b(i, x, z);
            } else {
                f[0x1DC] = 5;
            }
            if (i >= 6 && g_Ball[0x1BC9] == 0 && *(s16*)(f + 0x184) < -5) {
                fn_3_43038(i);
            }
            break;
        case 1:
            *(f32*)(f + 0x28) = *(f32*)(g_Ball + 0x19D8);
            *(f32*)(f + 0x2C) = *(f32*)(g_Ball + 0x19DC);
            if (*(s16*)(f + 0x18A) != 0) {
                ((int (*)(int, f32*, f32*, int))fn_3_50DD8)(i, &x, &z, 1);
                SetTargetAC8b(i, x, z);
                *(f32*)(f + 0x20) = x;
                *(f32*)(f + 0x24) = z;
            } else {
                f32 dz, dx, dd, ox, oz;
                oz = *(f32*)(f + 0x2C);
                ox = *(f32*)(f + 0x28);
                *(f32*)(f + 0x14) = ox;
                *(f32*)(f + 0x1C) = oz;
                dx = ox - *(f32*)f;
                dz = oz - *(f32*)(f + 8);
                if (0.0f == dx && 0.0f == dz) {
                    *(f32*)(f + 0x50) = 0.0f;
                    *(f32*)(f + 0x68) = 0.0f;
                } else {
                    *(f32*)(f + 0x64) = atan2(dz, dx);
                    dd = dx * dx + dz * dz;
                    SQRT_L(dd);
                    *(f32*)(f + 0x68) = dd;
                }
                f[0x1D9] = 1;
            }
            break;
        case 2:
            fn_3_42CDC(i);
            break;
        case 3:
            fn_3_42BD0(i);
            break;
        case 4:
            t = *(s16*)(f + 0x184);
            SetTargetAC8b(i, *(f32*)(g_Ball + t * 0x10 + 0x354), *(f32*)(g_Ball + t * 0x10 + 0x35C));
            if (*(s16*)(f + 0x184) <= 1) {
                f[0x1DC] = 5;
            }
            break;
        case 5:
            SetTargetAC8b(i, *(f32*)g_Ball, *(f32*)(g_Ball + 8));
            break;
        }
    }
    *(s16*)(f + 0x184) = *(s16*)(f + 0x184) - 1;
    ((void (*)(int))fn_3_526DC)(i);
    if (0.0f != *(f32*)(f + 0x50)) {
        *(s16*)(f + 0x17E) = *(f32*)(f + 0x68) / *(f32*)(f + 0x50);
    }
    if ((f[0x1DC] == 1 || f[0x1DC] == 2 || f[0x1DC] == 3) && *(s16*)(g_Ball + 0x1B7A) == 0) {
        n = FramesToReachAC8(i, *(f32*)(g_Ball + 0x348), *(f32*)(g_Ball + 0x34C));
        if (*(s16*)(g_Ball + 0x1B60) > n) {
            f[0x1DC] = 0;
            *(s16*)(f + 0x184) = *(s16*)(g_Ball + 0x1B60) - 2;
        }
    }
}
#endif

// .text:0x000447C4 size:0xBD0 mapped:0x80683858
// NONMATCHING 98.3%: float register choice in the set-target blocks and t*16 kept in r31 by orig for the traj[t+30] read
#if NONMATCHING
// Fielder i chases a batted ball: pick a target on the ball's path (or the throw line) and run there.
void fn_3_447C4(int i) {
    u8* f = g_Fielders + i * 0x268;
    int t;
    int mg = 0;
    u8* e;
    f32 px, pz, dP, dL, d, k;
    f32 x;
    f32 z;
    t = *(s16*)(f + 0x186) - *(s16*)(g_Ball + 0x1B66) + 1;
    if (t < 0) {
        t *= -1;
    }
    if (t >= 0x168) {
        t = 0x167;
    }
    e = g_Ball + t * 0x10;
    px = *(f32*)(e + 0x354);
    pz = *(f32*)(e + 0x35C);
    if (g_Ball[0x1BEB] != 0) {
        if (((u8*)g_AiLogic)[0x79] != 0) {
            px = *(f32*)(g_Ball + 0x1B1C);
            pz = *(f32*)(g_Ball + 0x1B20);
        } else {
            px = *(f32*)(g_Ball + 0x348);
            pz = *(f32*)(g_Ball + 0x34C);
        }
    } else if (g_Ball[0x1BED] != 0) {
        px = *(f32*)(g_Ball + 0x1B1C);
        pz = *(f32*)(g_Ball + 0x1B20);
    }
    if (g_d_GameSettings[0x11] != 0 && i >= 2) {
        mg = 1;
    }
    if (i >= 6 || mg != 0) {
        dP = px * px + pz * pz;
        SQRT_L(dP);
        if (g_Ball[0x1BC0] != 0 && g_Ball[0x1BF1] == 0) {
            {
                f32 a = *(f32*)(g_Ball + 0x19D8) * *(f32*)(g_Ball + 0x19D8);
                f32 b = *(f32*)(g_Ball + 0x19DC) * *(f32*)(g_Ball + 0x19DC);
                dL = a + b;
                SQRT_L(dL);
            }
            if (g_Ball[0x1BC1] >= 2) {
                x = *(f32*)f - *(f32*)(g_Ball + 0x19D8);
                z = *(f32*)(f + 8) - *(f32*)(g_Ball + 0x19DC);
                {
                    f32 a = x * x;
                    f32 b = z * z;
                    d = a + b;
                    SQRT_L(d);
                }
                k = lbl_3_rodata_B64 / d;
                x = x * k + *(f32*)(g_Ball + 0x19D8);
                z = z * k + *(f32*)(g_Ball + 0x19DC);
                *(f32*)(f + 0x28) = x;
                *(f32*)(f + 0x2C) = z;
                ((void (*)(int, f32*, f32*))fn_3_50C20)(i, &x, &z);
                f[0x1DC] = 2;
                goto tail;
            }
            if (dP > dL) {
                if (f[0x1DD] != 1 || (f[0x1C5] != 0 && f[0x1C4] >= 3)) {
                    x = lbl_3_rodata_B64 * *(f32*)(g_Ball + 0x19E4) + *(f32*)(g_Ball + 0x19D8);
                    z = lbl_3_rodata_B64 * *(f32*)(g_Ball + 0x19E8) + *(f32*)(g_Ball + 0x19DC);
                    *(f32*)(f + 0x28) = x;
                    *(f32*)(f + 0x2C) = z;
                    ((void (*)(int, f32*, f32*))fn_3_50C20)(i, &x, &z);
                    f[0x1DC] = 2;
                } else {
                    x = *(f32*)(g_Ball + 0x19D8);
                    z = *(f32*)(g_Ball + 0x19DC);
                    *(f32*)(f + 0x28) = x;
                    *(f32*)(f + 0x2C) = z;
                    ((void (*)(int, f32*, f32*))fn_3_50C20)(i, &x, &z);
                    f[0x1DC] = 1;
                }
                {
                    f32 dz, dx, dd;
                    *(f32*)(f + 0x14) = x;
                    *(f32*)(f + 0x1C) = z;
                    dx = x - *(f32*)f;
                    dz = z - *(f32*)(f + 8);
                    if (0.0f == dx && 0.0f == dz) {
                        *(f32*)(f + 0x50) = 0.0f;
                        *(f32*)(f + 0x68) = 0.0f;
                    } else {
                        *(f32*)(f + 0x64) = atan2(dz, dx);
                        dd = dx * dx + dz * dz;
                        SQRT_L(dd);
                        *(f32*)(f + 0x68) = dd;
                    }
                    f[0x1D9] = 1;
                }
                goto tail;
            }
        }
        if (f[0x1DD] == 3 || f[0x1DD] == 4) {
            if (fn_3_B7E44(*(s16*)(g_Ball + 0x1B80), dP) != 0) {
                x = lbl_3_rodata_B64 * *(f32*)(g_Ball + 0x19E4) + *(f32*)(g_Ball + 0x19D8);
                z = lbl_3_rodata_B64 * *(f32*)(g_Ball + 0x19E8) + *(f32*)(g_Ball + 0x19DC);
                *(f32*)(f + 0x28) = x;
                *(f32*)(f + 0x2C) = z;
                ((void (*)(int, f32*, f32*))fn_3_50C20)(i, &x, &z);
                f[0x1DC] = 2;
            } else {
                x = *(f32*)(g_Ball + t * 0x10 + 0x534);
                z = *(f32*)(g_Ball + t * 0x10 + 0x53C);
                *(f32*)(f + 0x28) = x;
                *(f32*)(f + 0x2C) = z;
                ((void (*)(int, f32*, f32*))fn_3_50C20)(i, &x, &z);
                f[0x1DC] = 3;
            }
            SetTargetAC8b(i, x, z);
            goto tail;
        }
    }
    d = px * px + pz * pz;
    SQRT_L(d);
    if (d <= lbl_3_rodata_B24) {
        x = px;
        z = pz;
    } else {
        x = lbl_3_rodata_B80 * (px / d) + px;
        z = lbl_3_rodata_B80 * (pz / d) + pz;
    }
    if (g_Ball[0x1BEB] == 0 && g_Ball[0x1BE7] != 9 && g_Ball[0x1BE7] != 10 && g_Ball[0x1BF1] == 0 && g_Ball[0x1BD8] == 0) {
        ((int (*)(int, f32*, f32*, int))fn_3_50DD8)(i, &x, &z, 0);
    }
    SetTargetAC8b(i, x, z);
    f[0x1DC] = 0;
tail:
    *(f32*)(f + 0x20) = *(f32*)(f + 0x14);
    *(f32*)(f + 0x24) = *(f32*)(f + 0x1C);
    ((void (*)(int))fn_3_526DC)(i);
    *(s16*)(f + 0x184) = t;
}
#endif

// .text:0x00045394 size:0x220 mapped:0x80684428
void fn_3_45394(int i) {
    u8* f = g_Fielders + i * 0x268;
    u8* gs;
    if (g_FieldingLogic[0x107] == 3 && *(s16*)(g_Ball + 0x1B66) < 0x91 && i == 1) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1B66) <= 0) {
        return;
    }
    if (f[0x1DF] != 0) {
        s16 t = *(s16*)(f + 0x194);
        if (t < 0x7FFE) {
            *(s16*)(f + 0x194) = t + 1;
        } else {
            *(s16*)(f + 0x194) = 0x7FFF;
        }
        if (*(s16*)(f + 0x194) < *(s16*)(f + 0x196)) {
            if (g_Ball[0x1BC9] == 1) {
                *(s16*)(f + 0x194) = *(s16*)(f + 0x196);
            }
            return;
        }
        *(s16*)(f + 0x194) = 0;
        f[0x1DF] = 0;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f[0x1ED] == 0) {
            ((void (*)(int))fn_3_433E0)(i);
        }
        gs = g_d_GameSettings;
        if (gs[0x11] == 0) {
            ((void (*)(int))fn_3_4207C)(i);
        }
        if (gs[0x11] != 0) {
            if (g_Ball[0x1BD1] != 0 && i != -1) {
                f[0x1D3] = 0xC;
                if (*(int*)(lbl_3_data_3C40 + 0x60) >= 0) {
                    g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x60);
                }
                f[0x1D5] = 0;
                f[0x1D6] = 0;
                *(s16*)(f + 0x1A4) = 0;
                *(s16*)(f + 0x1AC) = 0;
                f[0x1FF] = 0;
            }
            break;
        }
    case 1:
        if (g_Ball[0x1BD1] != 0) {
            if (i != -1) {
                f[0x1D3] = 0xC;
                if (*(int*)(lbl_3_data_3C40 + 0x60) >= 0) {
                    g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x60);
                }
                f[0x1D5] = 0;
                f[0x1D6] = 0;
                *(s16*)(f + 0x1A4) = 0;
                *(s16*)(f + 0x1AC) = 0;
                f[0x1FF] = 0;
            }
        } else {
            ((void (*)(int))fn_3_5372C)(i);
        }
        break;
    }
}

// .text:0x000455B4 size:0x2AC mapped:0x80684648
void fn_3_455B4(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 a, b, d, a2, b2;
    s16 n = *(s16*)(g_Ball + 0x1B66);
    if (n >= f[0x1D2]) {
        if (fn_3_53130(i) == 0) {
            fn_3_447C4(i);
            a = *(f32*)(f + 0x14);
            b = *(f32*)(f + 0x1C);
            a2 = a * a;
            b2 = b * b;
            d = a2 + b2;
            SQRT_L(d);
            if (d > lbl_3_rodata_B9C) {
                *(f32*)(g_Fielders + 0x14) = *(f32*)g_Fielders;
                *(f32*)(g_Fielders + 0x18) = *(f32*)(g_Fielders + 4);
                *(f32*)(g_Fielders + 0x1C) = *(f32*)(g_Fielders + 8);
                *(f32*)(g_Fielders + 0x30) = lbl_3_rodata_B20;
                *(f32*)(g_Fielders + 0x34) = lbl_3_rodata_B20;
                *(f32*)(g_Fielders + 0x50) = lbl_3_rodata_B20;
                *(f32*)(g_Fielders + 0x68) = lbl_3_rodata_B20;
                if (i != -1) {
                    f[0x1D3] = 9;
                    if (*(int*)(lbl_3_data_3C40 + 0x48) >= 0) {
                        g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x48);
                    }
                    f[0x1D5] = 0;
                    f[0x1D6] = 0;
                    *(s16*)(f + 0x1A4) = 0;
                    *(s16*)(f + 0x1AC) = 0;
                    f[0x1FF] = 0;
                }
            } else {
                fn_3_45394(i);
                if (f[0x1C5] != 0) {
                    if (i != -1) {
                        f[0x1D3] = 2;
                        if (*(int*)(lbl_3_data_3C40 + 0x10) >= 0) {
                            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x10);
                        }
                        f[0x1D5] = 0;
                        f[0x1D6] = 0;
                        *(s16*)(f + 0x1A4) = 0;
                        *(s16*)(f + 0x1AC) = 0;
                        f[0x1FF] = 0;
                    }
                } else if (i != -1) {
                    f[0x1D3] = 0x10;
                    if (*(int*)(lbl_3_data_3C40 + 0x80) >= 0) {
                        g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x80);
                    }
                    f[0x1D5] = 0;
                    f[0x1D6] = 0;
                    *(s16*)(f + 0x1A4) = 0;
                    *(s16*)(f + 0x1AC) = 0;
                    f[0x1FF] = 0;
                }
            }
        }
    }
}

// .text:0x00045860 size:0x11C mapped:0x806848F4
void fn_3_45860(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 n = *(s16*)(g_Ball + 0x1B66);
    if (n >= f[0x1D2]) {
        if (fn_3_53130(i) == 0) {
            fn_3_447C4(i);
            fn_3_45394(i);
            if (f[0x1C5] != 0) {
                if (i != -1) {
                    f[0x1D3] = 2;
                    if (*(int*)(lbl_3_data_3C40 + 0x10) >= 0) {
                        g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x10);
                    }
                    f[0x1D5] = 0;
                    f[0x1D6] = 0;
                    *(s16*)(f + 0x1A4) = 0;
                    *(s16*)(f + 0x1AC) = 0;
                    f[0x1FF] = 0;
                }
            } else if (i != -1) {
                f[0x1D3] = 0x10;
                if (*(int*)(lbl_3_data_3C40 + 0x80) >= 0) {
                    g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x80);
                }
                f[0x1D5] = 0;
                f[0x1D6] = 0;
                *(s16*)(f + 0x1A4) = 0;
                *(s16*)(f + 0x1AC) = 0;
                f[0x1FF] = 0;
            }
        }
    }
}

// .text:0x0004597C size:0x20C mapped:0x80684A10
#ifndef REP_AC8_VECXZ
#define REP_AC8_VECXZ
typedef struct _VecXZ {
    f32 x, z;
} VecXZ; // same as include/game/UnknownHomes_Game.h (not includable here: g_Ball is u8[] in this file)
#endif
extern int calculateLineIntersection(VecXZ* out, VecXZ* a, VecXZ* b);
// Move fielder i to the point on the ball's travel line closest to it.
void fn_3_4597C(int i) {
    u8* f = g_Fielders + i * 0x268;
    VecXZ out;
    VecXZ line[2];
    VecXZ perp[2];
    f32 dz, dx, d;
    f32 lx, lz, ox, oz;
    line[0].x = *(f32*)g_Ball;
    line[0].z = *(f32*)(g_Ball + 8);
    line[1].x = *(f32*)(g_Ball + 0x19F8);
    line[1].z = *(f32*)(g_Ball + 0x19FC);
    perp[0].x = *(f32*)f;
    perp[0].z = *(f32*)(f + 8);
    lx = line[1].x - line[0].x;
    lz = -(line[1].z - line[0].z);
    perp[1].x = perp[0].x + lz;
    perp[1].z = perp[0].z + lx;
    calculateLineIntersection(&out, line, perp);
    ox = out.x;
    oz = out.z;
    *(f32*)(f + 0x14) = ox;
    *(f32*)(f + 0x1C) = oz;
    dx = ox - *(f32*)f;
    dz = oz - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}

// .text:0x00045B88 size:0x310 mapped:0x80684C1C
// Fielder i runs to cut off the ball's travel line, then hands over to the normal chase.
void fn_3_45B88(int i) {
    u8* f = g_Fielders + i * 0x268;
    VecXZ out;
    VecXZ perp[2];
    VecXZ line[2];
    f32 dz, dx, d;
    f32 lx, lz;
    g_FieldingLogic[0x13C] = 0;
    if (f[0x1FF] == 0) {
        f[0x1FF] = 1;
        f[0x202] = 1;
        *(s16*)(g_FieldingLogic + 0xB0) = i;
        line[0].x = *(f32*)g_Ball;
        line[0].z = *(f32*)(g_Ball + 8);
        line[1].x = *(f32*)(g_Ball + 0x19F8);
        line[1].z = *(f32*)(g_Ball + 0x19FC);
        perp[0].x = *(f32*)f;
        perp[0].z = *(f32*)(f + 8);
        lx = line[1].x - line[0].x;
        lz = -(line[1].z - line[0].z);
        perp[1].x = perp[0].x + lz;
        perp[1].z = perp[0].z + lx;
        calculateLineIntersection(&out, line, perp);
        *(f32*)(f + 0x14) = out.x;
        *(f32*)(f + 0x1C) = out.z;
        dx = out.x - *(f32*)f;
        dz = out.z - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
        }
        f[0x1D9] = 1;
    }
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f[0x202] != 0) {
            ((void (*)(int))fn_3_526DC)(i);
            if (*(u16*)(g_FieldingLogic + 0x14A) & 0x100) {
                g_FieldingLogic[0x13C] = 1;
            }
        }
    case 1:
        if (g_Ball[0x1BC9] != 2) {
            *(s16*)(g_FieldingLogic + 0xC2) = -1;
            f[0x202] = 0;
            SetFielderAct(i, 9, 0x48);
        }
        break;
    }
}

// .text:0x00045E98 size:0x7F0 mapped:0x80684F2C
// NONMATCHING 86.7%: orig unrolls the 9-fielder relay-reset loop 3x (ours stays rolled) and keeps the candidate array in a pointer; logic follows the asm
#if NONMATCHING
// Pick a relay (cutoff) fielder between the ball chaser and the infield.
void fn_3_45E98(void) {
    int j;
    int k;
    int n;
    int ok = 0;
    int best;
    u8 st;
    u8* g;
    int cand[3];
    f32 bx, bz, d, bestD, px, pz;
    if (*(s16*)(g_FieldingLogic + 0xC0) != 0) {
        *(s16*)(g_FieldingLogic + 0xC0) -= 1;
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) == 6) {
        return;
    }
    if (*(s16*)(g_Ball + 0x1B78) == *(s16*)(g_FieldingLogic + 0xBE)) {
        *(s16*)(g_FieldingLogic + 0xBE) = -1;
    }
    if (*(s16*)(g_FieldingLogic + 0xBE) == -1) {
        if (*(s16*)(g_FieldingLogic + 0xC4) >= 0) {
            return;
        }
        for (j = 0; j < 9; j++) {
            if (*(s16*)(g_Fielders + j * 0x268 + 0x18C) == 6) {
                st = g_Fielders[j * 0x268 + 0x1D3];
                if (st == 2 || (u8)(st - 15) <= 1 || (u8)(st - 21) <= 2 || st == 12 || st == 0) {
                    *(s16*)(g_Fielders + j * 0x268 + 0x18C) = -1;
                } else {
                    return;
                }
            }
        }
        if (g_Ball[0x1BBE] >= 3) {
            ok = 1;
        } else {
            if (g_Ball[0x1BBE] <= 1) {
                return;
            }
            if (*(s16*)(g_Ball + 0x1B78) >= 0) {
                return;
            }
            if (g_Ball[0x1BC9] == 0 && g_Ball[0x1BBE] >= 2) {
                ok = 1;
            }
            for (j = 0; j < 6; j++) {
                if (g_FieldingLogic[j + 0xF8] == 1 || g_FieldingLogic[j + 0xF8] == 10) {
                    break;
                }
            }
            if (j == 6) {
                for (j = 6; j < 9; j++) {
                    if (g_FieldingLogic[j + 0xF8] == 1 || g_FieldingLogic[j + 0xF8] == 10) {
                        break;
                    }
                }
                if (j <= 8) {
                    ok = 1;
                }
            }
        }
        if (ok == 0 || *(s16*)(g_FieldingLogic + 0xC0) != 0) {
            return;
        }
        cand[0] = cand[1] = cand[2] = -1;
        n = 0;
        for (j = 2; j < 6; j++) {
            st = g_FieldingLogic[j + 0xF8];
            if ((st == 0 || st == 8 || st == 9) && (g_Fielders + j * 0x268)[0x1ED] == 0) {
                cand[n++] = j;
            }
            if (n == 3) {
                break;
            }
        }
        if (n <= 0) {
            return;
        }
        bx = lbl_3_rodata_BD0 * *(f32*)g_Ball / *(f32*)(g_Ball + 0x1A00);
        bz = lbl_3_rodata_BD0 * *(f32*)(g_Ball + 8) / *(f32*)(g_Ball + 0x1A00);
        bestD = 0.0f;
        best = cand[0];
        for (k = 0; k < 3; k++) {
            if (cand[k] < 0) {
                continue;
            }
            g = g_Fielders + cand[k] * 0x268;
            {
                f32 dx = *(f32*)g - bx;
                f32 dz = *(f32*)(g + 8) - bz;
                dx = dx * dx;
                dz = dz * dz;
                d = dx + dz;
                SQRT_L(d);
            }
            if (k == 0) {
                bestD = d;
            } else if (d < bestD) {
                bestD = d;
                best = cand[k];
            }
        }
        SetFielderAct(best, 0xB, 0x58);
        g_FieldingLogic[0x146] = lbl_3_data_49DC[0x2B];
        return;
    }
    if (g_FieldingLogic[0x146] != 0) {
        return;
    }
    k = *(s16*)(g_FieldingLogic + 0xBE);
    px = *(f32*)(g_Fielders + k * 0x268 + 0x14);
    pz = *(f32*)(g_Fielders + k * 0x268 + 0x1C);
    for (j = 2; j < 6; j++) {
        if (k == j) {
            continue;
        }
        st = g_FieldingLogic[j + 0xF8];
        g = g_Fielders + j * 0x268;
        if ((st == 0 || st == 8 || st == 9) && g[0x1ED] == 0) {
            {
                f32 dx = px - *(f32*)g;
                f32 dz = pz - *(f32*)(g + 8);
                dx = dx * dx;
                dz = dz * dz;
                d = dx + dz;
                SQRT_L(d);
            }
            if (d < *(f32*)(g_Fielders + *(s16*)(g_FieldingLogic + 0xBE) * 0x268 + 0x68)) {
                SetFielderAct(j, 0xB, 0x58);
                g_FieldingLogic[0x146] = lbl_3_data_49DC[0x2B];
                return;
            }
        }
    }
}
#endif

// .text:0x00046688 size:0x254 mapped:0x8068571C
int fn_3_46688(f32* x, f32* z) {
    u8* f = g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
    f32 dx, dz, d, t, a2, b2;
    if (*(s16*)(g_Ball + 0x1B78) >= 0) {
        *x = *(f32*)g_Ball;
        *z = *(f32*)(g_Ball + 8);
    } else if (g_Ball[0x1BC9] == 2) {
        *x = *(f32*)(g_Ball + 0x1A34);
        *z = *(f32*)(g_Ball + 0x1A3C);
    } else if (*(s16*)(g_Ball + 0x1B7E) >= 0) {
        *x = *(f32*)(g_Fielders + *(s16*)(g_Ball + 0x1B7E) * 0x268);
        *z = *(f32*)(g_Fielders + *(s16*)(g_Ball + 0x1B7E) * 0x268 + 8);
    } else if (*(s16*)(g_Ball + 0x1B7A) == 0) {
        *x = *(f32*)(g_Ball + 0x348);
        *z = *(f32*)(g_Ball + 0x34C);
    } else {
        dx = *(f32*)g_Ball - *(f32*)f;
        dz = *(f32*)(g_Ball + 8) - *(f32*)(f + 8);
        a2 = dx * dx;
        b2 = dz * dz;
        d = a2 + b2;
        SQRT_L(d);
        if (lbl_3_rodata_B20 == d) {
            *x = *(f32*)(g_Ball + 0x348);
            *z = *(f32*)(g_Ball + 0x34C);
        } else if (*(f32*)(g_Ball + 0x1A14) <= lbl_3_rodata_B48) {
            *x = *(f32*)g_Ball;
            *z = *(f32*)(g_Ball + 8);
        } else {
            t = d / *(f32*)(g_Ball + 0x1A14);
            *x = *(f32*)(g_Ball + 0x318) * t + *(f32*)g_Ball;
            *z = *(f32*)(g_Ball + 0x320) * t + *(f32*)(g_Ball + 8);
        }
    }
    return 1;
}

// .text:0x000468DC size:0x1E0 mapped:0x80685970
int fn_3_468DC(f32* x, f32* z) {
    if (*(s16*)(g_Ball + 0x1B78) >= 0) {
        *x = *(f32*)g_Ball;
        *z = *(f32*)(g_Ball + 8);
    } else if (*(s16*)(g_Ball + 0x1B7E) >= 0) {
        *x = *(f32*)(g_Fielders + *(s16*)(g_Ball + 0x1B7E) * 0x268 + 0x14);
        *z = *(f32*)(g_Fielders + *(s16*)(g_Ball + 0x1B7E) * 0x268 + 0x1C);
    } else if (g_FieldingLogic[0xFF] == 1) {
        if (g_FieldingLogic[0x100] == 1) {
            s16 a = *(s16*)(g_Fielders + 0x1256);
            if (a == -1 || *(s16*)(g_Fielders + 0x14BE) == -1) {
                return 0;
            }
            if (a < *(s16*)(g_Fielders + 0x14BE)) {
                *x = *(f32*)(g_Fielders + 0x10EC);
                *z = *(f32*)(g_Fielders + 0x10F4);
            } else {
                *x = *(f32*)(g_Fielders + 0x1354);
                *z = *(f32*)(g_Fielders + 0x135C);
            }
        } else if (g_FieldingLogic[0xFE] == 1) {
            s16 a = *(s16*)(g_Fielders + 0x1256);
            if (a == -1 || *(s16*)(g_Fielders + 0xFEE) == -1) {
                return 0;
            }
            if (a < *(s16*)(g_Fielders + 0xFEE)) {
                *x = *(f32*)(g_Fielders + 0x10EC);
                *z = *(f32*)(g_Fielders + 0x10F4);
            } else {
                *x = *(f32*)(g_Fielders + 0xE84);
                *z = *(f32*)(g_Fielders + 0xE8C);
            }
        } else {
            if (*(s16*)(g_Fielders + 0x1256) == -1) {
                return 0;
            }
            *x = *(f32*)(g_Fielders + 0x10EC);
            *z = *(f32*)(g_Fielders + 0x10F4);
        }
    } else if (g_FieldingLogic[0x100] == 1) {
        if (*(s16*)(g_Fielders + 0x14BE) == -1) {
            return 0;
        }
        *x = *(f32*)(g_Fielders + 0x1354);
        *z = *(f32*)(g_Fielders + 0x135C);
    } else {
        if (*(s16*)(g_Fielders + 0xFEE) == -1) {
            return 0;
        }
        *x = *(f32*)(g_Fielders + 0xE84);
        *z = *(f32*)(g_Fielders + 0xE8C);
    }
    return 1;
}

// .text:0x00046ABC size:0x34C mapped:0x80685B50
// NONMATCHING 97.7%: float register coloring of the predicted ball position (orig keeps x/z in f0/f7)
#if NONMATCHING
// Fielder i follows the batted ball along its path at its own reach distance (0x74).
void fn_3_46ABC(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 t, px, pz, ex, ez, e;
    f32 dz, dx, d;
    if (*(s16*)(g_Ball + 0x1B6C) == 5 && *(f32*)(g_Ball + 0x1A14) != 0.0f) {
        t = *(f32*)(f + 0x74) / *(f32*)(g_Ball + 0x1A14);
        px = *(f32*)(g_Ball + 0x318) * t + *(f32*)g_Ball;
        pz = *(f32*)(g_Ball + 0x320) * t + *(f32*)(g_Ball + 8);
        ex = *(f32*)f - px;
        ez = *(f32*)(f + 8) - pz;
        ex = ex * ex;
        ez = ez * ez;
        e = ex + ez;
        SQRT_L(e);
        if (e > *(f32*)(f + 0xE8)) {
            f[0x1E9] = 1;
            *(f32*)(f + 0x14) = px;
            *(f32*)(f + 0x1C) = pz;
            dx = px - *(f32*)f;
            dz = pz - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                *(f32*)(f + 0x68) = d;
            }
            f[0x1D9] = 1;
        }
    }
    ((void (*)(int))fn_3_526DC)(i);
    if (f[0x1E9] != 0 && *(f32*)(f + 0x50) == 0.0f) {
        f[0x1E9] = 0;
    }
    if (*(s16*)(g_Ball + 0x1B8A) == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x00046E08 size:0x820 mapped:0x80685E9C
#pragma opt_unroll_loops off
// NONMATCHING 97.2%: the 3-base loop is a pointer-compare loop here (orig uses ctr); float regs. Constants are block locals so stores through outX/outZ don't force reloads
#if NONMATCHING
// Where should fielder i stand to cover its base (0x18E)? Writes the spot to outX/outZ.
int fn_3_46E08(int i, f32* outX, f32* outZ) {
    u8* f = g_Fielders + i * 0x268;
    int inBase = 0;
    int j;
    s16 k;
    u8* g;
    f32 x;
    f32 z;
    f32 bx, bz, d, s;
    f32* b;
    f32 r5;
    if (f[0x1C5] != 0) {
        if (fn_3_468DC(&x, &z) == 0) {
            return 0;
        }
    } else {
        g = g_Fielders + *(s16*)(g_FieldingLogic + 0xB0) * 0x268;
        if (*(s16*)(g_Ball + 0x1B78) >= 0) {
            x = *(f32*)g_Ball;
            z = *(f32*)(g_Ball + 8);
        } else if (g_Ball[0x1BC9] == 2) {
            x = *(f32*)(g_Ball + 0x1A34);
            z = *(f32*)(g_Ball + 0x1A3C);
        } else if ((k = *(s16*)(g_Ball + 0x1B7E)) >= 0) {
            x = *(f32*)(g_Fielders + k * 0x268);
            z = ((f32*)(g_Fielders + 8))[k * 0x9A];
        } else if (*(s16*)(g_Ball + 0x1B7A) == 0) {
            x = *(f32*)(g_Ball + 0x348);
            z = *(f32*)(g_Ball + 0x34C);
        } else {
            f32 dx = *(f32*)g_Ball - *(f32*)g;
            f32 dz = *(f32*)(g_Ball + 8) - *(f32*)(g + 8);
            dx = dx * dx;
            dz = dz * dz;
            d = dx + dz;
            SQRT_L(d);
            if (0.0f == d) {
                x = *(f32*)(g_Ball + 0x348);
                z = *(f32*)(g_Ball + 0x34C);
            } else if (*(f32*)(g_Ball + 0x1A14) <= lbl_3_rodata_B48) {
                x = *(f32*)g_Ball;
                z = *(f32*)(g_Ball + 8);
            } else {
                d = d / *(f32*)(g_Ball + 0x1A14);
                x = *(f32*)(g_Ball + 0x318) * d + *(f32*)g_Ball;
                z = *(f32*)(g_Ball + 0x320) * d + *(f32*)(g_Ball + 8);
            }
        }
    }
    bx = *(f32*)(lbl_3_data_4444 + *(s16*)(f + 0x18E) * 8);
    bz = ((f32*)(lbl_3_data_4444 + 4))[*(s16*)(f + 0x18E) * 2];
    switch (*(s16*)(f + 0x18E)) {
    case 0: {
        f32 c = lbl_3_rodata_C3C;
        f32 m = lbl_3_rodata_B8C;
        f32 r;
        *outX = m * (x / c);
        *outZ = m * (z / c);
        d = *outX * *outX + *outZ * *outZ;
        SQRT_L(d);
        r = lbl_3_rodata_C40;
        if (d > r) {
            s = d / r;
            if (s > lbl_3_rodata_B60) {
                *outX = *outX / s;
                *outZ = *outZ / s;
            }
        }
        break;
    }
    case 1:
        {
            f32 kk = lbl_3_rodata_B80;
            *outX = (x - bx) * kk + bx;
            *outZ = (z - bz) * kk + bz;
        }
        break;
    case 2:
        {
            f32 kk = lbl_3_rodata_B74;
            *outX = (x - bx) * kk + bx;
            *outZ = (z - bz) * kk + bz;
        }
        break;
    case 3:
        if (*(s16*)(f + 0x180) < 0x480) {
            {
                f32 kk = lbl_3_rodata_B80;
                *outX = (x - bx) * kk + bx;
                *outZ = (z - bz) * kk + bz;
            }
        } else {
            {
                f32 kk = lbl_3_rodata_B78;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
        }
        break;
    case 4:
        {
            f32 kk = lbl_3_rodata_C08;
            *outX = bx + (x - bx) / kk;
            *outZ = bz + (z - bz) / kk;
        }
        break;
    }
    r5 = lbl_3_rodata_B64;
    for (b = (f32*)(lbl_3_data_4444 + 8); b < (f32*)(lbl_3_data_4444 + 0x20); b += 2) {
        if (*outZ > b[1] - r5 && *outZ < r5 + b[1] && *outX > b[0] - r5 && *outX < r5 + b[0]) {
            inBase = 1;
        }
    }
    if (inBase != 0) {
        switch (*(s16*)(f + 0x18E)) {
        case 0:
            {
                f32 kk = lbl_3_rodata_C44;
                *outX = x / kk;
                *outZ = z / kk;
            }
            break;
        case 1:
            {
                f32 kk = lbl_3_rodata_C48;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
            break;
        case 2:
            {
                f32 kk = lbl_3_rodata_C4C;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
            break;
        case 3:
            {
                f32 kk = lbl_3_rodata_C48;
                *outX = bx + (x - bx) / kk;
                *outZ = bz + (z - bz) / kk;
            }
            break;
        case 4:
            {
                f32 kk = lbl_3_rodata_B80;
                *outX = (x - bx) * kk + bx;
                *outZ = (z - bz) * kk + bz;
            }
            break;
        }
        return 1;
    }
    {
        f32 dx = *outX - *(f32*)(f + 0x14);
        f32 dz = *outZ - *(f32*)(f + 0x1C);
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
    }
    if (d < lbl_3_rodata_B64) {
        *outX = *(f32*)(f + 0x14);
        *outZ = *(f32*)(f + 0x1C);
    }
    return 1;
}
#endif
#pragma opt_unroll_loops reset

// .text:0x00047628 size:0x150 mapped:0x806866BC
#pragma opt_unroll_loops off
#pragma dont_inline off
// 99.8%: f0/f1 swapped between the hoisted 3.7f constant and runner+0x64 in the loop. Inlined into fn_3_480B8.
int fn_3_47628(void) {
    int i;
    u8* r;
    f32 v;
    for (i = 3; i >= 0; i--) {
        r = g_Runners + i * 0x154;
        if (r[0x123] == 1 && (!(*(f32*)(r + 0x64) >= lbl_3_rodata_C50) || r[0x137] != 1 || r[0x128] == 2)) {
            r = g_Runners + i * 0x154;
            v = *(f32*)(r + 0x64);
            if (v >= lbl_3_rodata_B78) {
                return 0;
            }
            if (r[0x128] == 2 && *(f32*)(r + 0x68) >= lbl_3_rodata_C38) {
                return r[0x124];
            }
            if (v >= lbl_3_rodata_B68) {
                if (v >= lbl_3_rodata_C54 && (g_Runners + i * 0x154)[0x137] == 1) {
                    return 0;
                }
                return 3;
            }
            if (v >= lbl_3_rodata_C48 && (g_Runners + i * 0x154)[0x137] == 1) {
                return 3;
            }
            return 2;
        }
    }
    return 4;
}
#pragma dont_inline on
#pragma opt_unroll_loops reset

// .text:0x00047778 size:0x940 mapped:0x8068680C
#define FL_STATE(n) g_FieldingLogic[0xF8 + (n)]
#define IS_CHASING(s) ((s) == 1 || (s) == 10 || (s) == 11)
// NONMATCHING 93.8%: registers (extra saved reg for s5) and the inlined set-target sqrt temp (f2 vs f4)
#if NONMATCHING
// On a steal/pickoff situation, assign who covers second (0x18C = 6) and where the pitcher backs up.
void fn_3_47778(void) {
    u8 v = g_Ball[0x1BC4];
    u8 s3;
    u8 s5;
    u8 s;
    int a;
    if (v != 5 && v != 6 && v != 8) {
        return;
    }
    s3 = FL_STATE(3);
    if (IS_CHASING(s3)) {
        if (*(s16*)(FLD(5) + 0x18C) != -1) {
            *(s16*)(FLD(3) + 0x18C) = 6;
            FLD(3)[0x1D7] = 2;
        } else {
            *(s16*)(FLD(5) + 0x18C) = 6;
            FLD(5)[0x1D7] = 2;
            if (FL_STATE(5) == 0) {
                SetFielderAct(5, 0xB, 0x58);
            }
        }
    } else if (s5 = FL_STATE(5), IS_CHASING(s5)) {
        if (*(s16*)(FLD(3) + 0x18C) != -1) {
            *(s16*)(FLD(5) + 0x18C) = 6;
            FLD(5)[0x1D7] = 2;
        } else {
            *(s16*)(FLD(3) + 0x18C) = 6;
            FLD(3)[0x1D7] = 2;
            if (s3 == 0) {
                SetFielderAct(3, 0xB, 0x58);
            }
        }
    } else if (*(s16*)(g_Ball + 0x1B9C) < 0x400) {
        if (*(s16*)(FLD(3) + 0x18C) == 1 && (s = FL_STATE(2), IS_CHASING(s))) {
            *(s16*)(FLD(2) + 0x18C) = 6;
            FLD(2)[0x1D7] = 2;
        } else {
            *(s16*)(FLD(3) + 0x18C) = 6;
            FLD(3)[0x1D7] = 2;
            if (s3 == 0) {
                SetFielderAct(3, 0xB, 0x58);
            }
        }
    } else {
        if (*(s16*)(FLD(5) + 0x18C) == 3 && (s = FL_STATE(4), IS_CHASING(s))) {
            *(s16*)(FLD(4) + 0x18C) = 6;
            FLD(4)[0x1D7] = 2;
        } else {
            *(s16*)(FLD(5) + 0x18C) = 6;
            FLD(5)[0x1D7] = 2;
            if (s5 == 0) {
                SetFielderAct(5, 0xB, 0x58);
            }
        }
    }
    if (FL_STATE(0) != 0) {
        return;
    }
    *(s16*)(FLD(0) + 0x18C) = 15;
    a = *(s16*)(g_Ball + 0x1B9C);
    if (a < 0x320) {
        SetTargetAC8b(0, lbl_3_rodata_BF4, lbl_3_rodata_C28);
    } else if (a < 0x400) {
        SetTargetAC8b(0, lbl_3_rodata_B78, lbl_3_rodata_C58);
    } else if (a < 0x4E0) {
        SetTargetAC8b(0, lbl_3_rodata_C5C, lbl_3_rodata_C58);
    } else {
        SetTargetAC8b(0, lbl_3_rodata_C60, lbl_3_rodata_C28);
    }
    SetFielderAct(0, 0xE, 0x70);
}
#endif
#undef FL_STATE
#undef IS_CHASING

// .text:0x000480B8 size:0x314 mapped:0x8068714C
// NONMATCHING 99.9%: f0/f1 swapped for the 3.7f constant vs runner+0x64 in the inlined fn_3_47628 loop (same issue as fn_3_47628)
#if NONMATCHING
// Fielder i covers the base the lead runner is heading for (fn_3_47628).
void fn_3_480B8(int i) {
    u8* f = g_Fielders + i * 0x268;
    int base;
    f32 x;
    f32 z;
    f32 dz, dx, d;
    base = fn_3_47628();
    if (base != -1) {
        *(s16*)(f + 0x18E) = base;
        if (((int (*)(int, f32*, f32*))fn_3_46E08)(i, &x, &z) != 0) {
            *(f32*)(f + 0x14) = x;
            *(f32*)(f + 0x1C) = z;
            dx = x - *(f32*)f;
            dz = z - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                *(f32*)(f + 0x68) = d;
            }
            f[0x1D9] = 1;
        }
    }
}
#endif

// .text:0x000483CC size:0xB4 mapped:0x80687460
void fn_3_483CC(int i) {
    u8* f = g_Fielders + i * 0x268;
    *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
    f[0x1D7] = 2;
    if (i != -1) {
        f[0x1D3] = 0xE;
        if (*(int*)(lbl_3_data_3C40 + 0x70) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x70);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    f[0x1D6] = 0;
    *(s16*)(g_FieldingLogic + 0xBE) = -1;
}

// .text:0x00048480 size:0x5D4 mapped:0x80687514
extern void fn_3_A7C88(void);
// NONMATCHING 50%: the original inlines fn_3_480B8 (lead-runner cover + set target); we call it (expected nmverify flag). The rest matches apart from registers
#if NONMATCHING
// Infielder i during a hit: cover the lead runner's base (fn_3_480B8), then react to the ball state.
void fn_3_48480(int i) {
    u8* f = g_Fielders + i * 0x268;
    u8 st;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (*(s16*)(g_FieldingLogic + 0xC4) == 6) {
            fn_3_46ABC(i);
            fn_3_A7C88();
        } else if (*(int*)(g_Strikes + 8) < 3) {
            fn_3_480B8(i);
            ((void (*)(int))fn_3_526DC)(i);
        }
        if (0.0f != *(f32*)(f + 0x50)) {
            *(s16*)(f + 0x17E) = *(f32*)(f + 0x68) / *(f32*)(f + 0x50);
        }
    case 1:
        break;
    }
    st = g_Ball[0x1BC9];
    if (st != 0 && *(s16*)(g_FieldingLogic + 0xC4) != 6 && g_Ball[0x1BBE] <= 1) {
        *(s16*)(f + 0x18C) = -1;
        f[0x1D7] = 0;
        SetFielderAct(i, 0xC, 0x60);
        *(s16*)(g_FieldingLogic + 0xBE) = -1;
    } else if (st == 1 &&
               ((f32*)(g_Fielders + *(s16*)(g_Ball + 0x1B78) * 0x268 + 0xA8))[*(s16*)(f + 0x18E)] < lbl_3_rodata_B70 &&
               *(s16*)(g_FieldingLogic + 0xC4) != 6) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
        f[0x1D7] = 2;
        SetFielderAct(i, 0xE, 0x70);
        f[0x1D6] = 0;
        *(s16*)(g_FieldingLogic + 0xBE) = -1;
        *(s16*)(g_FieldingLogic + 0xC0) = 0x5A;
    } else if (st == 2 && *(s16*)(g_FieldingLogic + 0xC4) != 6) {
        *(s16*)(f + 0x18C) = fn_3_3D7D4(i);
        f[0x1D7] = 2;
        SetFielderAct(i, 0xE, 0x70);
        f[0x1D6] = 0;
        *(s16*)(g_FieldingLogic + 0xBE) = -1;
    }
    if (*(s16*)(g_Ball + 0x1B8A) == i) {
        fn_3_4E638();
    }
}
#endif

// .text:0x00048A54 size:0xAA0 mapped:0x80687AE8
// NONMATCHING 98.6%: entry if-shape, lhau vs lha for the base-cover table, and float/int register swaps
#if NONMATCHING
// Fielder i takes over as the ball chaser (FieldingLogic+0xBE) when it can reach the ball sooner.
void fn_3_48A54(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 x;
    f32 z;
    f32 d;
    int k;
    u8* g;
    if (fn_3_53130(i) != 0 || f[0x252] != 0) {
        return;
    }
    *(s16*)(f + 0x18E) = fn_3_47628();
    if (*(s16*)(g_FieldingLogic + 0xBE) < 0) {
        if (((int (*)(int, f32*, f32*))fn_3_46E08)(i, &x, &z) == 0) {
            return;
        }
        {
            f32 dz, dx, dd;
            *(f32*)(f + 0x14) = x;
            *(f32*)(f + 0x1C) = z;
            dx = x - *(f32*)f;
            dz = z - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                *(f32*)(f + 0x68) = dd;
            }
            f[0x1D9] = 1;
        }
        *(s16*)(g_FieldingLogic + 0xBE) = i;
        SetFielderAct(i, 5, 0x28);
        FielderTakeOverAC8(i);
        return;
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) == 6) {
        SetFielderAct(i, 0xC, 0x60);
        (g_Fielders + i * 0x268)[0x1D5] = 4;
        return;
    }
    if (((int (*)(int, f32*, f32*))fn_3_46E08)(i, &x, &z) == 0) {
        return;
    }
    {
        f32 dx = x - *(f32*)f;
        f32 dz = z - *(f32*)(f + 8);
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
    }
    k = *(s16*)(g_FieldingLogic + 0xBE);
    if (d < *(f32*)(g_Fielders + k * 0x268 + 0x68)) {
        if (*(s16*)(g_Ball + 0x1B78) != k) {
            SetFielderAct(k, 0xC, 0x60);
            (g_Fielders + *(s16*)(g_FieldingLogic + 0xBE) * 0x268)[0x1D5] = 4;
        }
        g = g_Fielders + *(s16*)(g_FieldingLogic + 0xBE) * 0x268;
        *(s16*)(g + 0x18C) = -1;
        g[0x1D7] = 0;
        {
            f32 dx, dz, dd;
            *(f32*)(f + 0x14) = x;
            *(f32*)(f + 0x1C) = z;
            dx = x - *(f32*)f;
            dz = z - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                *(f32*)(f + 0x68) = dd;
            }
            f[0x1D9] = 1;
        }
        *(s16*)(g_FieldingLogic + 0xBE) = i;
        SetFielderAct(i, 5, 0x28);
        FielderTakeOverAC8(i);
    } else {
        SetFielderAct(i, 0xC, 0x60);
        (g_Fielders + i * 0x268)[0x1D5] = 4;
    }
}
#endif

// .text:0x000494F4 size:0x4D0 mapped:0x80688588
// NONMATCHING 96.7%: orig recomputes the fielder pointer (g_Fielders + saved i*0x268) for the stop block; float regs differ
#if NONMATCHING
// Fielder i closes in on the ball; stops (target = own position) once close enough.
void fn_3_494F4(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 dz, dx, d, r, tx, tz;
    if (g_Ball[0x1BF3] != 0) {
        dz = *(f32*)(g_Ball + 8) - *(f32*)(f + 8);
        dx = *(f32*)g_Ball - *(f32*)f;
        d = dx * dx + dz * dz;
        SQRT_L(d);
        if (d < *(f32*)(lbl_3_data_4930 + 0x94)) {
            goto stop;
        }
        dx = dx / d;
        dz = dz / d;
        r = *(f32*)(lbl_3_data_4930 + 0x90) - lbl_3_rodata_B60;
        tx = r * dx + *(f32*)f;
        tz = r * dz + *(f32*)(f + 8);
        SetTargetAC8b(i, tx, tz);
    }
    if (g_Ball[0x1BCC] != 0) {
        if (*(f32*)(f + 0x74) < *(f32*)(lbl_3_data_4930 + 4)) {
            goto stop;
        }
    } else {
        dx = *(f32*)g_Ball - *(f32*)(g_Ball + 0x19D8);
        dz = *(f32*)(g_Ball + 8) - *(f32*)(g_Ball + 0x19DC);
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        if (d < *(f32*)(lbl_3_data_4930 + 8) && *(f32*)(f + 0x7C) < *(f32*)(lbl_3_data_4930 + 0xC)) {
            goto stop;
        }
    }
    if (g_Ball[0x1BC3] == 2 && *(f32*)(f + 0x7C) < *(f32*)(lbl_3_data_4930 + 0xC)) {
        goto stop;
    }
    return;
stop:
    {
        u8* g = g_Fielders + i * 0x268;
        *(f32*)(g + 0x14) = *(f32*)f;
        *(f32*)(g + 0x18) = *(f32*)(f + 4);
        *(f32*)(g + 0x1C) = *(f32*)(f + 8);
        *(f32*)(g + 0x30) = 0.0f;
        *(f32*)(g + 0x34) = 0.0f;
        *(f32*)(g + 0x50) = 0.0f;
        *(f32*)(g + 0x68) = 0.0f;
    }
}
#endif

// .text:0x000499C4 size:0x254 mapped:0x80688A58
// Pick the spot (out x/z) where fielder i should go to meet the ball's flight path.
// NONMATCHING 98.8%: px/pz pointer setup uses mr+addi in the original (register coalescing); loop compare needs volatile to defeat CSE
#if NONMATCHING
void fn_3_499C4(int i, f32* out) {
    u8* f = g_Fielders + i * 0x268;
    int k;
    int res;
    int t;
    int j;
    f32* p;
    u8* b;
    f32* pz;
    f32* px;
    f32 y;
    f32 d;
    f32 s;
    f32 nx;
    f32 nz;
    k = *(s16*)(g_FieldingLogic + 0xB0);
    out[1] = 0.0f;
    if (*(s16*)(g_FieldingLogic + 0xB2) >= 0) {
        k = *(s16*)(g_FieldingLogic + 0xB2);
    }
    res = 0;
    t = *(s16*)(g_Fielders + k * 0x268 + 0x186) - *(s16*)(g_Ball + 0x1B66);
    if (t > 0) {
        p = (f32*)(g_Ball + t * 0x10 + 0x360);
        y = *p + *(f32*)lbl_3_data_4930;
        for (j = t + 1; j < 0x168; j += 3) {
            if (y < *(volatile f32*)p) {
                break;
            }
        }
        if (j < 0x168) {
            res = j;
        }
    }
    if (res == 0) {
        t = *(s16*)(f + 0x186) - *(s16*)(g_Ball + 0x1B66);
        if (t <= 0) {
            t = 0x5A;
        } else if (t >= 0x168) {
            t = 0x167;
        }
        b = g_Ball + t * 0x10;
        pz = (f32*)(b + 0x35C);
        px = (f32*)(b + 0x354);
        d = *(f32*)(b + 0x354) * *(f32*)(b + 0x354) + *(f32*)(b + 0x35C) * *(f32*)(b + 0x35C);
        SQRT_L(d);
        nx = *px / d;
        nz = *pz / d;
        s = d + *(f32*)lbl_3_data_4930;
        out[0] = nx * s;
        out[2] = nz * s;
        return;
    }
    b = g_Ball + res * 0x10;
    out[0] = *(f32*)(b + 0x354);
    out[2] = *(f32*)(b + 0x35C);
}
#endif


// .text:0x00049C18 size:0x290 mapped:0x80688CAC
void fn_3_49C18(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 out[3];
    f32 dz, dx, d, ox, oz;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f[0x1FF] == 0) {
            fn_3_499C4(i, out);
            ox = out[0];
            oz = out[2];
            *(f32*)(f + 0x14) = ox;
            *(f32*)(f + 0x1C) = oz;
            dx = ox - *(f32*)f;
            dz = oz - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                d = dx * dx + dz * dz;
                SQRT_L(d);
                *(f32*)(f + 0x68) = d;
            }
            f[0x1D9] = 1;
            f[0x1FF] = 1;
        }
        if (f[0x1FF] == 1) {
            ((void (*)(int))fn_3_526DC)(i);
            fn_3_494F4(i);
        }
    case 1:
        if (g_Ball[0x1BC9] != 0 && g_Ball[0x1BC9] != 3) {
            SetFielderAct(i, 0xC, 0x60);
            if (i <= 5) {
                f[0x1D6] = 7;
            } else {
                f[0x1D6] = 6;
            }
        }
        break;
    }
}

typedef struct { u8 b[0x268]; } FldT;

// .text:0x00049EA8 size:0x94 mapped:0x80688F3C
void fn_3_49EA8(int i) {
    u8* p;
    s32 off;
    u8* f;
    p = g_FieldingLogic + i;
    if (*(p += 0xF8) != 9) {
        off = i * 0x268;
        f = g_Fielders + off;
        *(s16*)(f + 0x18C) = 7;
        if (i != -1) {
            f[0x1D3] = 0xE;
            if (*(int*)(lbl_3_data_3C40 + 0x70) >= 0) {
                *p = *(int*)(lbl_3_data_3C40 + 0x70);
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
        ((FldT*)g_Fielders)[i].b[0x1D6] = 0;
        *(s16*)(((FldT*)g_Fielders)[i].b + 0x190) = -1;
    }
}

// .text:0x00049F3C size:0x4 mapped:0x80688FD0
void fn_3_49F3C(void) {
    return;
}

// .text:0x00049F40 size:0x1E4 mapped:0x80688FD4
typedef struct { u8 pad[0x190]; s16 x; u8 pad2[0x268 - 0x192]; } FS;
void fn_3_49F40(int i, int mode) {
    u8* f;
    if (g_FieldingLogic[i + 0xF8] != 0) {
        return;
    }
    f = g_Fielders + i * 0x268;
    f[0x1D4] = mode;
    if (mode == 0) {
        if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142] != 0) {
            if (i == -1) {
                return;
            }
            f[0x1D3] = 3;
            if (*(int*)(lbl_3_data_3C40 + 0x18) >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x18);
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
            return;
        }
        if (i == -1) {
            return;
        }
        f[0x1D3] = 0x18;
        if (*(int*)(lbl_3_data_3C40 + 0xC0) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0xC0);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
        *(s16*)(g_FieldingLogic + 0xBC) = i;
        return;
    }
    if (mode == 1) {
        if (i == -1) {
            return;
        }
        f[0x1D3] = 8;
        if (*(int*)(lbl_3_data_3C40 + 0x40) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x40);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
        return;
    }
    if (i != -1) {
        f[0x1D3] = 7;
        if (*(int*)(lbl_3_data_3C40 + 0x38) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x38);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
    if (mode == 2 || mode == 4) {
        ((FS*)g_Fielders)[i].x = 1;
    }
    if (mode == 3 || mode == 5) {
        ((FS*)g_Fielders)[i].x = 3;
    }
    if (mode == 6 || mode == 7) {
        ((FS*)g_Fielders)[i].x = 2;
    }
}

// .text:0x0004A124 size:0x2E4 mapped:0x806891B8
void fn_3_4A124(void) {
    int i;
    u8 st = g_Ball[0x1BC5];
    if (st == 5) {
        if (g_FieldingLogic[0xFA] == 1 || g_FieldingLogic[0xFA] == 0xA || g_FieldingLogic[0xFA] == 0xB) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 7);
            fn_3_49F40(7, 1);
            return;
        }
        if (g_FieldingLogic[0xFC] == 1 || g_FieldingLogic[0xFC] == 0xA || g_FieldingLogic[0xFC] == 0xB) {
            fn_3_49F40(6, 0);
            fn_3_49F40(7, 1);
            fn_3_49F40(8, 4);
            return;
        }
        fn_3_49F40(7, 0);
        if (*(s16*)(g_Ball + 0x1B9C) < 0x400) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 7);
            return;
        }
        fn_3_49F40(6, 0);
        fn_3_49F40(8, 4);
        return;
    } else if (st == 6) {
        fn_3_49F40(7, 0);
        if (*(s16*)(g_Ball + 0x1B9C) >= 0x3E0 && *(s16*)(g_Ball + 0x1B9C) < 0x420) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 0);
            return;
        }
        if (*(s16*)(g_Ball + 0x1B9C) < 0x400) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 7);
            return;
        }
        fn_3_49F40(6, 0);
        fn_3_49F40(8, 6);
        return;
    } else if (st == 7) {
        if (g_FieldingLogic[0xF9] != 1 && g_FieldingLogic[0xF9] != 0xA && g_FieldingLogic[0xF9] != 0xB) {
            fn_3_49F40(8, 0);
            fn_3_49F40(6, 1);
            fn_3_49F40(7, 1);
            return;
        }
        fn_3_49F40(6, 1);
        fn_3_49F40(7, 1);
        fn_3_49F40(8, 1);
        return;
    } else if (st == 8) {
        if (g_FieldingLogic[0xF9] != 1 && g_FieldingLogic[0xF9] != 0xA && g_FieldingLogic[0xF9] != 0xB) {
            fn_3_49F40(6, 0);
            fn_3_49F40(7, 1);
            fn_3_49F40(8, 1);
            return;
        }
        fn_3_49F40(6, 1);
        fn_3_49F40(7, 1);
        fn_3_49F40(8, 1);
        return;
    } else {
        fn_3_49F40(6, 1);
        fn_3_49F40(7, 1);
        fn_3_49F40(8, 4);
        i = 2;
        do {
            fn_3_49F40(i, 0);
            i += 1;
        } while (i < 6);
        return;
    }
}

// .text:0x0004A408 size:0x5A4 mapped:0x8068949C
// NONMATCHING 98.9%: sqrt temp register (f2 vs f4) in the inlined fn_3_52560; px/pz pointer split uses mr+addi in orig
#if NONMATCHING
// Pick where fielder i should go to field a ball in flight (out x/z): a point on the
// ball's trajectory it can reach in time.
void fn_3_4A408(int i, f32* outX, f32* outZ) {
    u8* f = g_Fielders + i * 0x268;
    u8* e;
    f32* px;
    f32* pz;
    f32 d, r, vx, vz;
    if (*(s16*)(g_Ball + 0x1B7A) == 0) {
        e = g_Ball + (*(s16*)(g_Ball + 0x1B60) + 30) * 0x10;
        px = (f32*)(e + 0x354);
        pz = (f32*)(e + 0x35C);
        if (FramesToReachAC8(i, *px, *pz) < *(s16*)(g_Ball + 0x1B60) + 30) {
            *outX = *px;
            *outZ = *pz;
        } else {
            *outX = *(f32*)(g_Ball + *(s16*)(g_Ball + 0x1B60) * 0x10 + 0x714);
            *outZ = *(f32*)(g_Ball + *(s16*)(g_Ball + 0x1B60) * 0x10 + 0x71C);
        }
        return;
    }
    if (fn_3_9CE0(*(f32*)f, *(f32*)(f + 8)) < lbl_3_rodata_B60) {
        SetFielderAct(i, 0xC, 0x60);
        f[0x1D5] = 3;
        return;
    }
    if (i >= 6) {
        d = *(f32*)(g_Ball + 0x714) * *(f32*)(g_Ball + 0x714) + *(f32*)(g_Ball + 0x71C) * *(f32*)(g_Ball + 0x71C);
        SQRT_L(d);
        r = lbl_3_rodata_C00 - d;
        if (r > 0.0f) {
            vx = *(f32*)(g_Ball + 0x1A18) * r;
            vz = *(f32*)(g_Ball + 0x1A1C) * r;
            *outX = vx + *(f32*)(g_Ball + 0x714);
            *outZ = vz + *(f32*)(g_Ball + 0x71C);
            return;
        }
    }
    if (FramesToReachAC8(i, *(f32*)(g_Ball + 0x534), *(f32*)(g_Ball + 0x53C)) < 30) {
        *outX = *(f32*)(g_Ball + 0x534);
        *outZ = *(f32*)(g_Ball + 0x53C);
    } else {
        *outX = *(f32*)(g_Ball + 0x714);
        *outZ = *(f32*)(g_Ball + 0x71C);
    }
}
#endif

// .text:0x0004A9AC size:0x77C mapped:0x80689A40
extern int fn_3_B7E44(s16 a, f32 y);
// NONMATCHING 98.2%: stack slot of the sqrt classify temp, fn_3_B7E44 arg load order, and the unrolled 9-fielder loop's pointer/regs
#if NONMATCHING
// Fielder i chases the ball (or covers the fielder at ball+0x1B7E), choosing a catch action by distance.
void fn_3_4A9AC(int i) {
    u8* f = g_Fielders + i * 0x268;
    int k = *(s16*)(g_Ball + 0x1B7E);
    int j;
    int r;
    f32 x;
    f32 z;
    f32 d;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (f[0x1C5] == 0) {
            fn_3_4A408(i, &x, &z);
        } else if (k == -1) {
            x = *(f32*)f;
            z = *(f32*)(f + 8);
        } else if (*(f32*)(f + 0x74) < lbl_3_rodata_B64) {
            x = *(f32*)f;
            z = *(f32*)(f + 8);
        } else if (g_Ball[0x1BC9] == 3) {
            x = lbl_3_rodata_BA0 * *(f32*)(g_Ball + 0x1A18) + *(f32*)g_Ball;
            z = lbl_3_rodata_BA0 * *(f32*)(g_Ball + 0x1A1C) + *(f32*)(g_Ball + 8);
        } else if (0.0f == *(f32*)(f + 0x50) && ((f32*)(f + 0x84))[k] < lbl_3_rodata_B70) {
            x = *(f32*)f;
            z = *(f32*)(f + 8);
        } else {
            u8* g = g_Fielders + k * 0x268;
            x = lbl_3_rodata_BA0 * *(f32*)(g_Ball + 0x1A18) + *(f32*)(g + 0x14);
            z = lbl_3_rodata_BA0 * *(f32*)(g_Ball + 0x1A1C) + *(f32*)(g + 0x1C);
        }
        {
            f32 dz, dx, dd;
            *(f32*)(f + 0x14) = x;
            *(f32*)(f + 0x1C) = z;
            dx = x - *(f32*)f;
            dz = z - *(f32*)(f + 8);
            if (0.0f == dx && 0.0f == dz) {
                *(f32*)(f + 0x50) = 0.0f;
                *(f32*)(f + 0x68) = 0.0f;
            } else {
                *(f32*)(f + 0x64) = atan2(dz, dx);
                dd = dx * dx + dz * dz;
                SQRT_L(dd);
                *(f32*)(f + 0x68) = dd;
            }
            f[0x1D9] = 1;
        }
        if (i >= 6) {
            if (k >= 6 && *(f32*)(f + 0x68) < lbl_3_rodata_B9C) {
                f[0x1D6] = 5;
            }
            if (*(f32*)(f + 0x68) < lbl_3_rodata_B70) {
                f[0x1D6] = 7;
            } else if (*(f32*)(f + 0x68) < lbl_3_rodata_B9C) {
                f[0x1D6] = 6;
            }
            r = fn_3_B7E44(*(s16*)(f + 0x180), *(f32*)(f + 0x70));
            if (r == 2) {
                f[0x1D6] = 8;
            }
            if (r == 1) {
                f[0x1D6] = 5;
            }
        } else if (k <= 5 && *(f32*)(f + 0x68) < lbl_3_rodata_BA0) {
            f[0x1D6] = 7;
        }
        for (j = 0; j < 9; j++) {
            if (j != i && ((f32*)(f + 0x84))[j] < lbl_3_rodata_B78) {
                f[0x1D6] = 9;
                break;
            }
        }
        ((void (*)(int))fn_3_526DC)(i);
    case 1:
        if (g_Ball[0x1BC9] != 0 && g_Ball[0x1BC9] != 3) {
            SetFielderAct(i, 0xC, 0x60);
            if (i <= 5) {
                f[0x1D6] = 7;
            } else {
                f[0x1D6] = 6;
            }
        }
        break;
    }
    if (*(s16*)(g_Ball + 0x1B7A) != 0 && ((f32*)(f + 0x84))[k] > lbl_3_rodata_B64 + *(f32*)(f + 0x74)) {
        f32 dx = *(f32*)(g_Ball + 0x3A4) - *(f32*)f;
        f32 dz = *(f32*)(g_Ball + 0x3AC) - *(f32*)(f + 8);
        dx = dx * dx;
        dz = dz * dz;
        d = dx + dz;
        SQRT_L(d);
        if (d < *(f32*)(f + 0x74) && f[0x1C5] != 0) {
            fn_3_43038(i);
            SetFielderAct(i, 0x12, 0x90);
            *(s16*)(g_Ball + 0x1B7E) = -1;
        }
    }
}
#endif

// .text:0x0004B128 size:0x3EC mapped:0x8068A1BC
// NONMATCHING 99.5%: sqrt temp gets f2 instead of f4 in the inlined set-target block
#if NONMATCHING
// Outfielder i lines up as cutoff man between the ball and the base it is thrown to.
void fn_3_4B128(int i) {
    f32 cx;
    f32 cz;
    f32 px;
    f32 pz;
    s16 ang;
    switch (fn_3_53130(i)) {
    case 2:
        return;
    default:
        if (*(s16*)(g_FieldingLogic + 0xC4) >= 1 && *(s16*)(g_FieldingLogic + 0xC4) <= 3 && *(s16*)(g_FieldingLogic + 0xE6) == 1 &&
            (*(s16*)(g_FieldingLogic + 0xC4) == 2 || i != 7)) {
            getComponentsFromSAng(fn_3_9FB8C(*(f32*)(g_Ball + 0x19EC) - *(f32*)g_Ball, *(f32*)(g_Ball + 0x19F4) - *(f32*)(g_Ball + 8)), &cx, &cz);
            px = lbl_3_rodata_B9C * cx + *(f32*)(lbl_3_data_4444 + *(s16*)(g_FieldingLogic + 0xC4) * 8);
            pz = lbl_3_rodata_B9C * cz + ((f32*)(lbl_3_data_4444 + 4))[*(s16*)(g_FieldingLogic + 0xC4) * 2];
            ang = fn_3_9FB8C(px, pz);
            if (ang <= 0x800 && ((ang < 0x300 && i == 8) || (ang > 0x500 && i == 6) || (ang < 0x400 && (i == 7 || i == 8)) ||
                                 (ang >= 0x400 && (i == 7 || i == 6)))) {
                if (pz < *(f32*)(lbl_3_data_4444 + 0xC)) {
                    if (px < 0.0f) {
                        px = lbl_3_rodata_C64;
                    } else {
                        px = lbl_3_rodata_C68;
                    }
                    pz = lbl_3_rodata_BE8;
                }
                SetTargetAC8b(i, px, pz);
            }
        }
        ((void (*)(int))fn_3_526DC)(i);
        if (*(f32*)(g_Fielders + i * 0x268 + 0x68) < lbl_3_rodata_B64) {
            SetFielderAct(i, 0xC, 0x60);
        } else if (g_Ball[0x1BD7] >= 2) {
            SetFielderAct(i, 0xC, 0x60);
        }
    case 1:
        break;
    }
}
#endif

// .text:0x0004B514 size:0x3BC mapped:0x8068A5A8
// NONMATCHING 98.2%: 0.0f load scheduled before the table load; f30/f31 swapped for the offset/dx
#if NONMATCHING
// Fielder i backs up: runs to its preset spot (lbl_3_data_44B4) or 20 units behind itself.
void fn_3_4B514(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 off = 0.0f;
    if (fn_3_53130(i) != 0) {
        return;
    }
    if (f[0x1D4] >= 2) {
        f32 dz, dx, d, ox, oz;
        ox = *(f32*)(lbl_3_data_44B4 + f[0x1D4] * 8);
        oz = ((f32*)(lbl_3_data_44B4 + 4))[f[0x1D4] * 2];
        *(f32*)(f + 0x14) = ox;
        *(f32*)(f + 0x1C) = oz;
        dx = ox - *(f32*)f;
        dz = oz - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
        }
        f[0x1D9] = 1;
    } else {
        f32 dz, dx, d, ox, oz;
        if (i == 6) {
            off = lbl_3_rodata_BA0;
        }
        if (i == 8) {
            off = lbl_3_rodata_BD4;
        }
        ox = *(f32*)f + off;
        oz = *(f32*)(f + 8) - lbl_3_rodata_B9C;
        *(f32*)(f + 0x14) = ox;
        *(f32*)(f + 0x1C) = oz;
        dx = ox - *(f32*)f;
        dz = oz - *(f32*)(f + 8);
        if (0.0f == dx && 0.0f == dz) {
            *(f32*)(f + 0x50) = 0.0f;
            *(f32*)(f + 0x68) = 0.0f;
        } else {
            *(f32*)(f + 0x64) = atan2(dz, dx);
            d = dx * dx + dz * dz;
            SQRT_L(d);
            *(f32*)(f + 0x68) = d;
        }
        f[0x1D9] = 1;
    }
    SetFielderAct(i, 6, 0x30);
}
#endif

// .text:0x0004B8D0 size:0x13C mapped:0x8068A964
void fn_3_4B8D0(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 k = *(s16*)(f + 0x18C);
    if (k >= 0) {
    if (k <= 3) {
        s16* p = (s16*)g_FieldingLogic + k;
        if (*(p += 0x68) == i) {
            *p = -1;
            g_FieldingLogic[0x101 + k] = 0;
        }
        *(s16*)(f + 0x18C) = -1;
        f[0x1D7] = 0;
        if (f[0x1D3] == 1 && i != -1) {
            f[0x1D3] = 0xC;
            if (*(int*)(lbl_3_data_3C40 + 0x60) >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x60);
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
    } else if (k == 5) {
        *(s16*)(g_FieldingLogic + 0xD8) = -1;
        g_FieldingLogic[0x105] = 0;
        *(s16*)(f + 0x18C) = -1;
        f[0x1D7] = 0;
        if (f[0x1D3] == 0xE && i != -1) {
            f[0x1D3] = 0xC;
            if (*(int*)(lbl_3_data_3C40 + 0x60) >= 0) {
                g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x60);
            }
            f[0x1D5] = 0;
            f[0x1D6] = 0;
            *(s16*)(f + 0x1A4) = 0;
            *(s16*)(f + 0x1AC) = 0;
            f[0x1FF] = 0;
        }
    }
    }
}

// .text:0x0004BA0C size:0xFBC mapped:0x8068AAA0
#define BASE_COVER(b) (*(s16*)(g_FieldingLogic + 0xD0 + (b) * 2)) // fielder covering base b (0-3), 4 = backup
#define BASE_DIST(f, b) (((f32*)((f) + 0xA8))[b])               // fielder f's distance to base b
// NONMATCHING 85.8%: register allocation over the whole function (orig keeps loop pointers in r7-r10/r12) and lfsx/lhax indexed loads; control flow follows the asm, including the original reading c1's distance for c2 in the backup pick
#if NONMATCHING
// Keep every base covered while runners are moving: release covers that are no longer
// needed, then give the first uncovered base (or a base needing help) to the nearest free fielder.
void fn_3_4BA0C(void) {
    int n;
    int b;
    int j;
    int k;
    int help = -1;
    int c0, c1, c2;
    int best;
    u8 s;
    u8* h;
    f32 d0, d1, d2;
    if (*(int*)(g_Strikes + 8) >= 3 || g_RunningLogic[0x10] == 0) {
        return;
    }
    for (n = 0; n < 4; n++) {
        if (BASE_COVER(n) == -1) {
            break;
        }
    }
    if (FLD(0)[0x1D8] == 1 && *(s16*)(FLD(0) + 0x18C) != 1 && *(s16*)(FLD(0) + 0x18C) != 3) {
        FLD(0)[0x1D8] = 0;
    }
    for (b = 0; b < 4; b++) {
        if (g_FieldingLogic[0x101 + b] != 0 || (k = BASE_COVER(b)) < 0) {
            continue;
        }
        s = g_FieldingLogic[0xF8 + k];
        if (s == 7) {
            if (b == *(s16*)(g_FieldingLogic + 0xCC)) {
                if (!(BASE_DIST(FLD(k), *(s16*)(g_FieldingLogic + 0xCC)) < lbl_3_rodata_B78)) {
                    FielderReleaseCoverAC8(k);
                }
            } else if (BASE_DIST(FLD(k), b) > lbl_3_rodata_C08) {
                FielderReleaseCoverAC8(k);
            }
        } else if (s == 1 || s == 10 || s == 11) {
            if (BASE_DIST(FLD(k), b) > lbl_3_rodata_B68) {
                FielderReleaseCoverAC8(k);
            }
        }
        if (s == 2 && BASE_DIST(FLD(BASE_COVER(b)), b) > lbl_3_rodata_B90 && help == -1) {
            help = b;
        }
    }
    c0 = c1 = c2 = -1;
    k = *(s16*)(g_FieldingLogic + 0xD8);
    for (j = 0; j < 6; j++) {
        if (FLD(j)[0x1ED] != 0) {
            continue;
        }
        s = g_FieldingLogic[0xF8 + j];
        if (s == 0 || s == 8 || s == 9 || (s == 9 && k == j)) {
            if (c0 == -1) {
                c0 = j;
            } else if (c1 == -1) {
                c1 = j;
            } else {
                c2 = j;
            }
        }
    }
    if (n < 4) {
        // An uncovered base: the ball holder takes it if close, else the nearest free fielder.
        k = *(s16*)(g_Ball + 0x1B78);
        if (k >= 0) {
            h = FLD(k);
            if (BASE_DIST(h, n) <= lbl_3_data_4780[h[0x1C9]]) {
                *(s16*)(h + 0x18C) = n;
                BASE_COVER(n) = k;
                h[0x1D7] = 1;
                g_FieldingLogic[0x101 + n] = 1;
                return;
            }
        }
        if (c0 == -1) {
            return;
        }
        {
            f32 bx = ((VecXZ*)lbl_3_data_4444)[n].x;
            f32 bz = ((VecXZ*)lbl_3_data_4444)[n].z;
            f32 dx, dz;
            d1 = d2 = lbl_3_rodata_BA4;
            dx = *(f32*)FLD(c0) - bx;
            dz = *(f32*)(FLD(c0) + 8) - bz;
            dx = dx * dx;
            dz = dz * dz;
            d0 = dx + dz;
            SQRT_L(d0);
            if (c1 >= 0) {
                dx = *(f32*)FLD(c1) - bx;
                dz = *(f32*)(FLD(c1) + 8) - bz;
                dx = dx * dx;
                dz = dz * dz;
                d1 = dx + dz;
                SQRT_L(d1);
            }
            if (c2 >= 0) {
                dx = *(f32*)FLD(c2) - bx;
                dz = *(f32*)(FLD(c2) + 8) - bz;
                dx = dx * dx;
                dz = dz * dz;
                d2 = dx + dz;
                SQRT_L(d2);
            }
        }
        best = c2;
        if (d0 < d1) {
            if (d0 < d2) {
                best = c0;
            }
        } else if (d1 < d2) {
            best = c1;
        }
        *(s16*)(FLD(best) + 0x18C) = n;
        FLD(best)[0x1D7] = 1;
        SetFielderAct(best, 1, 8);
        BASE_COVER(n) = best;
        if (*(s16*)(g_FieldingLogic + 0xD8) == best) {
            *(s16*)(g_FieldingLogic + 0xD8) = -1;
            g_FieldingLogic[0x105] = 0;
        }
        return;
    }
    if (help >= 0) {
        // The fielder covering base `help` is busy: hand the base to the nearest free fielder.
        best = -1;
        for (j = 0; j < 6; j++) {
            s = g_FieldingLogic[0xF8 + j];
            if ((s == 0 || s == 8 || s == 9) && BASE_DIST(FLD(j), help) < lbl_3_rodata_B9C) {
                if (best == -1) {
                    best = j;
                } else if (lbl_3_rodata_B78 + BASE_DIST(FLD(j), help) < BASE_DIST(FLD(best), help)) {
                    best = j;
                }
            }
        }
        if (best < 0) {
            return;
        }
        SetFielderAct(BASE_COVER(help), 0xC, 0x60);
        k = BASE_COVER(help);
        FLD(k)[0x1D5] = 3;
        FielderReleaseCoverAC8(k);
        *(s16*)(FLD(best) + 0x18C) = help;
        FLD(best)[0x1D7] = 1;
        SetFielderAct(best, 1, 8);
        BASE_COVER(help) = best;
        if (*(s16*)(g_FieldingLogic + 0xD8) == best) {
            *(s16*)(g_FieldingLogic + 0xD8) = -1;
            g_FieldingLogic[0x105] = 0;
        }
        return;
    }
    // All bases covered: pick a backup fielder (0x18C = 5) if there isn't one.
    k = *(s16*)(g_FieldingLogic + 0xD8);
    if (k != -1 && *(s16*)(FLD(k) + 0x18C) == 5) {
        return;
    }
    d1 = d2 = lbl_3_rodata_BA4;
    if (g_Ball[0x1BC9] == 0 && g_Ball[0x1BBE] <= 1) {
        return;
    }
    for (j = 0; j < 9; j++) {
        if (g_FieldingLogic[0xF8 + j] == 7) {
            if (BASE_DIST(FLD(j), 4) < lbl_3_rodata_BD8) {
                return;
            }
            break;
        }
    }
    if (c0 < 0) {
        return;
    }
    d0 = BASE_DIST(FLD(c0), 4);
    if (c1 >= 0) {
        d1 = BASE_DIST(FLD(c1), 4);
    }
    if (c2 >= 0) {
        d2 = BASE_DIST(FLD(c1), 4); // sic: the original reads c1 here too
    }
    best = c0;
    if (d0 < d1) {
        if (!(d0 < d2)) {
            best = c2;
        }
    } else if (d1 < d2) {
        best = c1;
    } else {
        best = c2;
    }
    *(s16*)(FLD(best) + 0x18C) = 5;
    FLD(best)[0x1D7] = 2;
    SetFielderAct(best, 0xE, 0x70);
    *(s16*)(g_FieldingLogic + 0xD8) = best;
}
#endif
#undef BASE_COVER
#undef BASE_DIST

// .text:0x0004C9C8 size:0x5E8 mapped:0x8068BA5C
void fn_3_4C9C8(void) {
    return;
}

// .text:0x0004CFB0 size:0x25C mapped:0x8068C044
#pragma dont_inline off
static inline void SetTargetAC8(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    *(f32*)(f + 0x14) = x;
    *(f32*)(f + 0x1C) = z;
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}
#pragma dont_inline on
void fn_3_4CFB0(void) {
    u8* f;
    int st = *(s16*)(g_Fielders + 0x18C);
    f32 x;
    f32 z;
    f32 d;
    f32 dz;
    f32 dx;
    if (st == 1) {
        d = *(f32*)(lbl_3_data_4444 + 0x8) - *(f32*)g_Fielders;
        if (d > 15.0f) {
            d = 15.0f;
        }
        x = *(f32*)(lbl_3_data_4444 + 0x8);
        d = d / lbl_3_rodata_B78;
        z = *(f32*)(lbl_3_data_4444 + 0xC) - d;
    } else if (st == 3) {
        d = *(f32*)g_Fielders - *(f32*)(lbl_3_data_4444 + 0x18);
        if (d > 15.0f) {
            d = 15.0f;
        }
        x = *(f32*)(lbl_3_data_4444 + 0x18);
        d = d / lbl_3_rodata_B78;
        z = *(f32*)(lbl_3_data_4444 + 0x1C) - d;
    } else {
        x = *(f32*)(lbl_3_data_4444 + st * 8);
        z = ((f32*)(lbl_3_data_4444 + 4))[st * 2];
    }
    f = g_Fielders;
    *(f32*)(f + 0x14) = x;
    *(f32*)(f + 0x1C) = z;
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}

// .text:0x0004D20C size:0x978 mapped:0x8068C2A0
void fn_3_4D20C(void) {
    return;
}

// .text:0x0004DB84 size:0x90 mapped:0x8068CC18
int fn_3_4DB84(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (0.0f == *(f32*)(g_Ball + 0x1A18) && 0.0f == *(f32*)(g_Ball + 0x1A1C)) {
        return 0;
    }
    if ((-(*(f32*)(g_Ball + 0x1A18) * *(f32*)(g_Ball + 0x0)) - *(f32*)(g_Ball + 0x1A1C) * *(f32*)(g_Ball + 0x8)) +
            (*(f32*)(g_Ball + 0x1A18) * *(f32*)(f + 0x0) + *(f32*)(g_Ball + 0x1A1C) * *(f32*)(f + 0x8)) >
        0.0f) {
        return 1;
    }
    return 0;
}

// .text:0x0004DC14 size:0x5A8 mapped:0x8068CCA8
void fn_3_4DC14(int i) {
    return;
}

// .text:0x0004E1BC size:0x47C mapped:0x8068D250
void fn_3_4E1BC(void) {
    return;
}

// .text:0x0004E638 size:0x58C mapped:0x8068D6CC
void fn_3_4E638(void) {
    return;
}

// .text:0x0004EBC4 size:0x404 mapped:0x8068DC58
void fn_3_4EBC4(void) {
    return;
}

// .text:0x0004EFC8 size:0x53C mapped:0x8068E05C
void fn_3_4EFC8(void) {
    return;
}

// .text:0x0004F504 size:0x630 mapped:0x8068E598
void fn_3_4F504(void) {
    return;
}

// .text:0x0004FB34 size:0xD64 mapped:0x8068EBC8
void fn_3_4FB34(void) {
    return;
}

// .text:0x00050898 size:0x388 mapped:0x8068F92C
void fn_3_50898(void) {
    return;
}

// .text:0x00050C20 size:0x1B8 mapped:0x8068FCB4
void fn_3_50C20(void) {
    return;
}

// .text:0x00050DD8 size:0x448 mapped:0x8068FE6C
void fn_3_50DD8(void) {
    return;
}

// .text:0x00051220 size:0x42C mapped:0x806902B4
void fn_3_51220(void) {
    return;
}

// .text:0x0005164C size:0x14C mapped:0x806906E0
#pragma fp_contract off
int fn_3_5164C(int i, f32* out) {
    u8* f = g_Fielders + i * 0x268;
    f32 x = *(f32*)f + *(f32*)(f + 0x30);
    f32 z = *(f32*)(f + 8) + *(f32*)(f + 0x34);
    int r = 0;
    f32 t;
    f32 lim;
    f32 nx;
    f32 zz;
    if (x > 0.0f) {
        if (x > z) {
            x = z + lbl_3_rodata_B80 * (x - z);
            z = x;
            r = 2;
        }
    } else {
        t = -x;
        if (t > z) {
            z += lbl_3_rodata_B80 * (t - z);
            x = -z;
            r = 2;
        }
    }
    lim = *(f32*)(lbl_3_data_4444 + 0x14);
    t = z - lim;
    if (!(t > x)) {
        nx = -x;
        if (!(t > nx)) {
            if (x > 0.0f) {
                zz = lim - z;
                x = zz + lbl_3_rodata_B80 * (x - zz);
                z = -x + lim;
                r = 2;
            } else {
                zz = lim - z;
                x = -zz - lbl_3_rodata_B80 * (nx - zz);
                z = x + lim;
                r = 2;
            }
        }
    }
    if (z <= *(f32*)(lbl_3_data_4444 + 0x10)) {
        return 1;
    }
    out[0] = x;
    out[2] = z;
    return r;
}
#pragma fp_contract reset

// .text:0x00051798 size:0x658 mapped:0x8069082C
int fn_3_51798(int i, f32* out) {
    return 0;
}

// .text:0x00051DF0 size:0x294 mapped:0x80690E84
void fn_3_51DF0(void) {
    return;
}

// .text:0x00052084 size:0x25C mapped:0x80691118
f32 fn_3_52084(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 d;
    f32 dx;
    f32 dz;
    f32 p;
    if (*(f32*)(f + 0x50) < 0.01f) {
        d = (*(f32*)f - x) * (*(f32*)f - x) + (*(f32*)(f + 8) - z) * (*(f32*)(f + 8) - z);
        SQRT_L(d);
        return d;
    }
    dz = z - *(f32*)(f + 8);
    dx = x - *(f32*)f;
    p = *(f32*)(f + 0x38) * dx + *(f32*)(f + 0x3C) * dz;
    d = (dx * dx + dz * dz) - p * p;
    if (d < 0.0f) {
        return 0.0f;
    }
    if (d > 0.0f) {
        f64 xd = (f64)d;
        f64 guess = __frsqrte(xd);
        guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);
        guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);
        guess = lbl_3_rodata_B30 * guess * (lbl_3_rodata_B38 - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (d < lbl_3_rodata_B40) {
        return NAN;
    } else if (isnan(d)) {
        return NAN;
    }
    return d;
}

// .text:0x000522E0 size:0x280 mapped:0x80691374
void fn_3_522E0(int i, int k, f32* outX, f32* outZ, f32* reach, f32 dx, f32 dz) {
    return;
}

// .text:0x00052560 size:0x17C mapped:0x806915F4
extern f32 lbl_3_rodata_B60;
void fn_3_1AE44(u8, u16, f32, f32, f32);
int fn_3_52560(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 d;
    f32 spd;
    if (x == *(f32*)f && z == *(f32*)(f + 8)) {
        return 1;
    }
    d = (x - *(f32*)f) * (x - *(f32*)f) + (z - *(f32*)(f + 8)) * (z - *(f32*)(f + 8));
    SQRT_L(d);
    spd = *(f32*)(f + 0x58);
    return ((u32)f[0x1D1] >> 1) + (int)(d / (lbl_3_rodata_B20 == spd ? lbl_3_rodata_B60 : spd));
}

// .text:0x000526DC size:0x870 mapped:0x80691770
void fn_3_526DC(void) {
    return;
}

// .text:0x00052F4C size:0x1A0 mapped:0x80691FE0
void fn_3_52F4C(int i, f32 x, f32 z) {
    u8* f = g_Fielders + i * 0x268;
    f32 dx;
    f32 dz;
    f32 d;
    *(f32*)(f + 0x14) = x;
    *(f32*)(f + 0x1C) = z;
    dx = x - *(f32*)f;
    dz = z - *(f32*)(f + 8);
    if (0.0f == dx && 0.0f == dz) {
        *(f32*)(f + 0x50) = 0.0f;
        *(f32*)(f + 0x68) = 0.0f;
    } else {
        *(f32*)(f + 0x64) = atan2(dz, dx);
        d = dx * dx + dz * dz;
        SQRT_L(d);
        *(f32*)(f + 0x68) = d;
    }
    f[0x1D9] = 1;
}

// .text:0x000530EC size:0x44 mapped:0x80692180
void fn_3_530EC(int i) {
    u8* f = g_Fielders + i * 0x268;
    *(f32*)(f + 0x14) = *(f32*)(f + 0x0);
    *(f32*)(f + 0x18) = *(f32*)(f + 0x4);
    *(f32*)(f + 0x1C) = *(f32*)(f + 0x8);
    *(f32*)(f + 0x30) = lbl_3_rodata_1498;
    *(f32*)(f + 0x34) = lbl_3_rodata_1498;
    *(f32*)(f + 0x50) = lbl_3_rodata_1498;
    *(f32*)(f + 0x68) = lbl_3_rodata_1498;
}

// .text:0x00053130 size:0x5FC mapped:0x806921C4
int fn_3_53130(int i) {
    return 0;
}

// .text:0x0005372C size:0x7BC mapped:0x806927C0
void fn_3_5372C(int i) {
    return;
}

// .text:0x00053EE8 size:0x60 mapped:0x80692F7C
void fn_3_53EE8(int i) {
    u8* f = g_Fielders + i * 0x268;
    if (i != -1) {
        f[0x1D3] = 0x13;
        if (*(int*)(lbl_3_data_3C40 + 0x98) >= 0) {
            g_FieldingLogic[i + 0xF8] = *(int*)(lbl_3_data_3C40 + 0x98);
        }
        f[0x1D5] = 0;
        f[0x1D6] = 0;
        *(s16*)(f + 0x1A4) = 0;
        *(s16*)(f + 0x1AC) = 0;
        f[0x1FF] = 0;
    }
}

// .text:0x00053F48 size:0x570 mapped:0x80692FDC
void fn_3_53F48(void) {
    return;
}

// .text:0x000544B8 size:0x448 mapped:0x8069354C
void fn_3_544B8(void) {
    return;
}

// .text:0x00054900 size:0x258 mapped:0x80693994
void fn_3_54900(int i) {
    u8* f = g_Fielders + i * 0x268;
    int m = *(s16*)(g_RunningLogic + 4);
    f32 x;
    f32 z;
    if (*(s8*)(f + 0x1F5) >= 0) {
        x = *(f32*)(lbl_3_data_4444 + 0x20);
        z = *(f32*)(lbl_3_data_4444 + 0x24);
    } else if (g_RunningLogic[0x10] == 0) {
        *(f32*)(f + 0x4C) = *(f32*)(f + 0x48);
        f[0x1F2] = 1;
        return;
    } else {
        if (*(s16*)(g_Ball + 0x1B7A) == 3) {
            m &= 0xFFF0;
        }
        switch (m) {
        case 0x1:
            x = *(f32*)(lbl_3_data_4444 + 0x8);
            z = *(f32*)(lbl_3_data_4444 + 0xC);
            break;
        case 0x10:
            x = 0.7f * *(f32*)(lbl_3_data_4444 + 0x10) + 0.3f * *(f32*)(lbl_3_data_4444 + 0x8);
            z = 0.7f * *(f32*)(lbl_3_data_4444 + 0x14) + 0.3f * *(f32*)(lbl_3_data_4444 + 0xC);
            break;
        case 0x100:
            x = 0.7f * *(f32*)(lbl_3_data_4444 + 0x18) + 0.3f * *(f32*)(lbl_3_data_4444 + 0x10);
            z = 0.7f * *(f32*)(lbl_3_data_4444 + 0x1C) + 0.3f * *(f32*)(lbl_3_data_4444 + 0x14);
            break;
        case 0x11:
            x = lbl_3_rodata_B80 * (*(f32*)(lbl_3_data_4444 + 0x8) + *(f32*)(lbl_3_data_4444 + 0x10));
            z = lbl_3_rodata_B80 * (*(f32*)(lbl_3_data_4444 + 0xC) + *(f32*)(lbl_3_data_4444 + 0x14));
            break;
        case 0x110:
            x = lbl_3_rodata_B80 * (*(f32*)(lbl_3_data_4444 + 0x10) + *(f32*)(lbl_3_data_4444 + 0x18));
            z = lbl_3_rodata_B80 * (*(f32*)(lbl_3_data_4444 + 0x14) + *(f32*)(lbl_3_data_4444 + 0x1C));
            break;
        case 0x111:
            x = 0.3f * *(f32*)(lbl_3_data_4444 + 0x18) + 0.7f * *(f32*)(lbl_3_data_4444 + 0x10);
            z = 0.3f * *(f32*)(lbl_3_data_4444 + 0x1C) + 0.7f * *(f32*)(lbl_3_data_4444 + 0x14);
            break;
        case 0x101:
            x = *(f32*)(lbl_3_data_4444 + 0x20);
            z = *(f32*)(lbl_3_data_4444 + 0x24);
            break;
        default:
            x = *(f32*)(lbl_3_data_4444 + 0x0);
            z = *(f32*)(lbl_3_data_4444 + 0x4);
            break;
        }
    }
    *(f32*)(f + 0x48) = atan2(z - *(f32*)(f + 8), x - *(f32*)f);
}

// .text:0x00054B58 size:0x818 mapped:0x80693BEC
void fn_3_54B58(int i) {
    return;
}

// .text:0x00055370 size:0x23C mapped:0x80694404
void fn_3_55370(void) {
    int i;
    u8* f;
    s16 v;
    f32 d;
    for (i = 0; i < 9; i++) {
        f = g_Fielders + i * 0x268;
        if (g_d_GameSettings[0x11] != 0 && g_Minigame[0x1923] != i) {
            continue;
        }
        fn_3_54B58(i);
        *(f32*)(f + 0x7C) = fn_3_9CE0(*(f32*)f, *(f32*)(f + 8));
        if (0.0f == *(f32*)(f + 0x50)) {
            *(f32*)(f + 0x38) = 0.0f;
            *(f32*)(f + 0x3C) = 0.0f;
        } else {
            *(f32*)(f + 0x38) = *(f32*)(f + 0x30) / *(f32*)(f + 0x50);
            *(f32*)(f + 0x3C) = *(f32*)(f + 0x34) / *(f32*)(f + 0x50);
        }
        f[0x1EA] = 0;
        f[0x217] = 0;

    }
    fn_3_544B8();
    if (g_d_GameSettings[0x11] != 0) {
        fn_3_53F48();
        return;
    }
    v = *(s16*)(g_Ball + 0x1B78);
    if (v >= 0) {
        *(f32*)(g_Ball + 0) = *(f32*)(g_Fielders + v * 0x268);
        *(f32*)(g_Ball + 4) = ((f32*)(g_Fielders + 4))[v * 0x9A];
        *(f32*)(g_Ball + 8) = ((f32*)(g_Fielders + 8))[v * 0x9A];
        *(f32*)(g_Ball + 0x348) = *(f32*)(g_Ball + 0);
        *(f32*)(g_Ball + 0x34C) = *(f32*)(g_Ball + 8);
        d = *(f32*)(g_Ball + 0) * *(f32*)(g_Ball + 0) + *(f32*)(g_Ball + 8) * *(f32*)(g_Ball + 8);
        SQRT_L(d);
        *(f32*)(g_Ball + 0x1A00) = d;
    }
}

// .text:0x000555AC size:0x164 mapped:0x80694640
extern f32 lbl_3_rodata_C18;
extern f32 lbl_3_rodata_C88;
extern f32 lbl_3_rodata_B90;
extern f32 lbl_3_rodata_CB8;
void fn_3_555AC(int i) {
    u8* f = g_Fielders + i * 0x268;
    f32 lo;
    f32 hi;
    f[0x1DE] = 0;
    if ((*(f32*)(f + 8)) > lbl_3_rodata_C18) {
        return;
    }
    if ((*(f32*)(f + 8)) < lbl_3_rodata_C88) {
        return;
    }
    if ((*(f32*)f) > lbl_3_rodata_B90) {
        return;
    }
    if ((*(f32*)f) < lbl_3_rodata_CB8) {
        return;
    }
    if ((*(f32*)(f + 8)) > *(f32*)(lbl_3_data_4444 + 0xC)) {
        lo = *(f32*)(lbl_3_data_4444 + 0x14) - lbl_3_rodata_B68;
        hi = lbl_3_rodata_B8C + *(f32*)(lbl_3_data_4444 + 0x14);
        if ((*(f32*)f) > lbl_3_rodata_B20) {
            if ((*(f32*)(f + 8)) > -(*(f32*)f) + lo && (*(f32*)(f + 8)) < -(*(f32*)f) + hi) {
                f[0x1DE] = 2;
            }
        } else {
            if ((*(f32*)(f + 8)) > (*(f32*)f) + lo && (*(f32*)(f + 8)) < (*(f32*)f) + hi) {
                f[0x1DE] = 3;
            }
        }
    } else {
        lo = *(f32*)(lbl_3_data_4444 + 4) - lbl_3_rodata_B8C;
        hi = lbl_3_rodata_B68 + *(f32*)(lbl_3_data_4444 + 4);
        if ((*(f32*)f) > lbl_3_rodata_B20) {
            if ((*(f32*)(f + 8)) > (*(f32*)f) + lo && (*(f32*)(f + 8)) < (*(f32*)f) + hi) {
                f[0x1DE] = 1;
            }
        } else {
            if ((*(f32*)(f + 8)) > -(*(f32*)f) + lo && (*(f32*)(f + 8)) < -(*(f32*)f) + hi) {
                f[0x1DE] = 4;
            }
        }
    }
}

// .text:0x00055710 size:0x208 mapped:0x806947A4
void fn_3_55710(int i) {
    u8* f = g_Fielders + i * 0x268;
    int sel = *(s8*)(f + 0x1F5);
    int k;
    u8* r;
    u8 t;
    if (g_FieldingLogic[0x116] != 0) {
        r = g_Runners;
        r += g_FieldingLogic[0x11B] * 0x154;
        if (*(s16*)(r + 0xE6) >= 0 || r[0x123] == 2) {
            g_FieldingLogic[0x116] = 0;
            *(s16*)(g_FieldingLogic + 0xEC) = 0;
        }
    } else {
        if (*(s8*)(g_FieldingLogic + 0x125) >= 0) {
            sel = *(s8*)(g_FieldingLogic + 0x125);
        }
        if (sel >= 0) {
            for (k = 3; k >= 0; k--) {
                r = g_Runners + k * 0x154;
                if (r[0x123] == 1 && *(s16*)(r + 0xEE) <= 0 && r[0x127] == sel && r[0x128] == 0 && *(s16*)(r + 0xE6) < 0) {
                    t = r[0x13A];
                    if (t != 0) {
                        if (t == 2) {
                            f[0x211] = 2;
                            f[0x212] = 0;
                            g_FieldingLogic[0x116] = 2;
                            *(s16*)(g_FieldingLogic + 0xEC) = 6;
                            g_FieldingLogic[0x111] = 7;
                            g_FieldingLogic[0x13F] = 2;
                            f[0x213] = k;
                            if (g_GameLogic[*(int*)(g_GameLogic + 8) + 0x13E] == 0) {
                                fn_3_6C854(*(int*)(g_GameLogic + 8), 2);
                            }
                        } else if (t == 3) {
                            f[0x211] = 1;
                            f[0x212] = 0;
                            g_FieldingLogic[0x116] = 1;
                            *(s16*)(g_FieldingLogic + 0xEC) = *(s16*)(r + 0x102);
                            g_FieldingLogic[0x111] = 6;
                            g_FieldingLogic[0x13F] = 1;
                            f[0x213] = k;
                        } else {
                            s16 v = *(s16*)(r + 0x102);
                            if (v < 6) {
                                g_FieldingLogic[0x116] = 2;
                                *(s16*)(g_FieldingLogic + 0xEC) = 6;
                            } else {
                                g_FieldingLogic[0x116] = 1;
                                *(s16*)(g_FieldingLogic + 0xEC) = v;
                            }
                        }
                        g_FieldingLogic[0x11B] = k;
                        return;
                    }
                }
            }
        }
    }
}

// .text:0x00055918 size:0x3AC mapped:0x806949AC
void fn_3_55918(void) {
    int i;
    u8* f;
    if (g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142] != 0) {
        fn_3_41D78();
    }
    if (*(s32*)(g_Strikes + 8) >= 3 && g_d_GameSettings[7] != 2) {
        for (i = 0; i < 9; i++) {
            f = g_Fielders + i * 0x268;
            if (f[0x1D3] != 0x11 && (*(s16*)(g_Ball + 0x1B78) != i || g_FieldingLogic[0x116] == 0) && f[0x200] == 0 && i != -1) {
                SetFielderAct2(i, *(int*)(lbl_3_data_3C40 + 0x88), 0x11);
            }
        }
    }
    if (g_Ball[0x1BDF] >= 1 && g_Ball[0x1BDF] <= 4) {
        for (i = 0; i < 9; i++) {
            if (i != -1) {
                SetFielderAct2(i, *(int*)(lbl_3_data_3C40 + 0), 0);
            }
        }
    } else if (g_Ball[0x1BD1] != 0) {
        for (i = 0; i < 9; i++) {
            f = g_Fielders + i * 0x268;
            if (((g_Ball[0x1BDF] >= 1 && g_Ball[0x1BDF] <= 4) || f[0x1D3] != 0xF || g_Ball[0x1BD1] == 0) && f[0x1D3] != 0xC && f[0x252] == 0 && i != -1) {
                SetFielderAct2(i, *(int*)(lbl_3_data_3C40 + 0x60), 0xC);
            }
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xC6) >= 0) {
        if (*(s16*)(g_FieldingLogic + 0xC8) < 0x7FFE) {
            *(s16*)(g_FieldingLogic + 0xC8) = *(s16*)(g_FieldingLogic + 0xC8) + 1;
        } else {
            *(s16*)(g_FieldingLogic + 0xC8) = 0x7FFF;
        }
        if (*(s16*)(g_FieldingLogic + 0xC8) > 0x1E) {
            *(s16*)(g_FieldingLogic + 0xC6) = -1;
            *(s16*)(g_FieldingLogic + 0xC8) = 0;
        }
    }
    if (*(s16*)(g_FieldingLogic + 0xC4) >= 0) {
        if (g_Ball[0x1BC9] == 2) {
            *(s16*)(g_FieldingLogic + 0xF0) = 0;
        } else if (*(s16*)(g_FieldingLogic + 0xF0) < 0x7FFE) {
            *(s16*)(g_FieldingLogic + 0xF0) = *(s16*)(g_FieldingLogic + 0xF0) + 1;
        } else {
            *(s16*)(g_FieldingLogic + 0xF0) = 0x7FFF;
        }
    } else {
        *(s16*)(g_FieldingLogic + 0xF0) = 0;
    }
    if (g_FieldingLogic[0x12B] != 0) {
        if (*(s16*)(g_Ball + 0x1B78) < 0) {
            g_FieldingLogic[0x12B] = 0;
        } else if (*(s8*)(g_Fielders + *(s16*)(g_Ball + 0x1B78) * 0x268 + 0x1F5) >= 0) {
            g_FieldingLogic[0x12B] = 0;
        } else {
            g_FieldingLogic[0x12B] = g_FieldingLogic[0x12B] - 1;
        }
    }
    for (i = 0; i < 9; i++) {
        *(s16*)(g_Fielders + i * 0x268 + 0x192) = 0xF;
    }
}

// .text:0x00055CC4 size:0x228 mapped:0x80694D58
void fn_3_55CC4(int i) {
    u8* f = g_Fielders + i * 0x268;
    s16 v;
    u8 a;
    u8 b;
    if (f[0x1E8] == 2 && *(s16*)(g_Ball + 0x1B78) != i) {
        f[0x1E8] = 0;
    }
    if (*(f32*)(f + 0x50) <= lbl_3_rodata_B20) {
        *(s16*)(f + 0x19A) = -1;
        *(s16*)(f + 0x1A0) = 0;
    } else {
        *(s16*)(f + 0x19A) = radToShortAngle(*(f32*)(f + 0x64));
        if (*(s16*)(f + 0x1A0) < 0x7FFE) {
            *(s16*)(f + 0x1A0) = *(s16*)(f + 0x1A0) + 1;
        } else {
            *(s16*)(f + 0x1A0) = 0x7FFF;
        }
    }
    v = *(s16*)(g_FieldingLogic + 0xDE);
    if (v >= 0 && f[0x1C6] == 0 && g_Runners[v * 0x154 + 0x123] != 1) {
        *(s16*)(g_FieldingLogic + 0xDE) = -1;
    }
    if (g_Ball[0x1BC9] == 1 || g_Ball[0x1BC9] == 2) {
        if (*(s16*)(g_FieldingLogic + 0xDC) >= 0 && *(s16*)(g_FieldingLogic + 0xCC) == 9) {
            v = *(s16*)(g_FieldingLogic + 0xDE);
            if (v >= 0) {
                if (((f32*)(g_Runners + 0x68))[v * 0x55] >= lbl_3_rodata_BB8 && ((f32*)(g_Runners + 0x68))[v * 0x55] <= lbl_3_rodata_CBC) {
                    *(s16*)(g_FieldingLogic + 0xF4) = v;
                }
            }
        }
        v = *(s16*)(g_FieldingLogic + 0xF4);
        if (v >= 0) {

            if (g_Runners[v * 0x154 + 0x123] != 1 || *(s16*)(g_Runners + v * 0x154 + 0xE6) >= 0) {
                *(s16*)(g_FieldingLogic + 0xF4) = -1;
            } else {
                a = g_Runners[v * 0x154 + 0x125];
                b = g_Runners[v * 0x154 + 0x126];
                if (*(s16*)(g_FieldingLogic + 0xC4) != -1 && *(s16*)(g_FieldingLogic + 0xC4) != a && *(s16*)(g_FieldingLogic + 0xC4) != b) {
                    *(s16*)(g_FieldingLogic + 0xF4) = -1;
                }
                if (*(s16*)(g_FieldingLogic + 0xCC) != -1 && *(s16*)(g_FieldingLogic + 0xCC) != 9 && *(s16*)(g_FieldingLogic + 0xCC) != a && *(s16*)(g_FieldingLogic + 0xCC) != b) {
                    *(s16*)(g_FieldingLogic + 0xF4) = -1;
                }
            }
        }
    }
}

// .text:0x00055EEC size:0x1258 mapped:0x80694F80
void fn_3_55EEC(int a) {
    return;
}

// .text:0x00057144 size:0x344 mapped:0x806961D8
void fn_3_57144(void) {
    return;
}

// .text:0x00057488 size:0x22C mapped:0x8069651C
void fn_3_57488(void) {
    s16 idx = *(s16*)(g_FieldingLogic + 0xB0);
    u8 mg = g_d_GameSettings[0x11];
    int k = idx;
    u8* f;
    f32 d;
    if (mg != 0) {
        k = g_Minigame[0x1923];
    }
    f = g_Fielders + k * 0x268;
    if (((u8*)g_AiLogic)[0x78] != 0) {
        goto set;
    }
    if (g_Ball[0x1BC9] == 3) {
        goto set;
    }
    if (g_Ball[0x1BC9] == 0) {
        if (g_Ball[0x1BCC] != 0 || g_Ball[0x1BDE] != 0) {
            goto set;
        }
        if (idx >= 6 || mg != 0) {
            d = *(f32*)(f + 0x20) * *(f32*)(f + 0x20) + *(f32*)(f + 0x24) * *(f32*)(f + 0x24);
            SQRT_L(d);
            if (d > lbl_3_rodata_BA0 && *(f32*)(g_Ball + 0x1A00) > d) {
                goto set;
            }
        }
    }
    if (*(f32*)(f + 0x20) > lbl_3_rodata_BFC) {
        fn_3_43038(*(s16*)(g_FieldingLogic + 0xB0));
        *(f32*)(f + 0x20) = *(f32*)(f + 0x14);
        *(f32*)(f + 0x24) = *(f32*)(f + 0x1C);
    }
    return;
set:
    ((u8*)g_AiLogic)[0x78] = 1;
    *(f32*)(f + 0x20) = *(f32*)(g_Ball + 0x444);
    *(f32*)(f + 0x24) = *(f32*)(g_Ball + 0x44C);
}

// .text:0x000576B4 size:0x360 mapped:0x80696748
void fn_3_576B4(int i) {
    return;
}

// .text:0x00057A14 size:0x1A0 mapped:0x80696AA8
extern f32 lbl_3_rodata_BA4;
void fn_3_57A14(void) {
    int first;
    int second;
    f32 d1;
    f32 d2;
    int i;
    if (*(s16*)(g_Ball + 0x1B78) >= 0) {
        *(s16*)(g_FieldingLogic + 0xB0) = *(s16*)(g_Ball + 0x1B78);
        return;
    }
    if (g_Ball[0x1BC9] == 2) {
        *(s16*)(g_FieldingLogic + 0xB0) = *(s16*)(g_Ball + 0x1B8A);
        return;
    }
    d1 = d2 = lbl_3_rodata_BA4;
    second = -1;
    first = -1;
    for (i = 1; i < 9; i++) {
        u8* f = g_Fielders + i * 0x268;
        if (f[0x1D3] == 2 || f[0x1D3] == 3) {
            if (*(f32*)(f + 0x7C) < d2) {
                if (*(f32*)(f + 0x7C) < d1) {
                    d2 = d1;
                    second = first;
                    d1 = *(f32*)(f + 0x7C);
                    first = i;
                } else {
                    d2 = *(f32*)(f + 0x7C);
                    second = i;
                }
            }
        }
    }
    if (first >= 0) {
        *(s16*)(g_FieldingLogic + 0xB0) = first;
    } else if (g_Fielders[0x1D3] == 2 || g_Fielders[0x1D3] == 3 || g_Fielders[0x1D3] == 4) {
        *(s16*)(g_FieldingLogic + 0xB0) = 0;
    }
    if (second >= 0) {
        *(s16*)(g_FieldingLogic + 0xB2) = second;
    }
    if (*(s16*)(g_FieldingLogic + 0xB0) >= 0) {
        fn_3_576B4(*(s16*)(g_FieldingLogic + 0xB0));
    }
}

// .text:0x00057BB4 size:0x804 mapped:0x80696C48
void fn_3_57BB4(void) {
    return;
}

// .text:0x000583B8 size:0x2D0 mapped:0x8069744C
void fn_3_583B8(void) {
    return;
}

// .text:0x00058688 size:0x1E8 mapped:0x8069771C
void fn_3_58688(void) {
    s32 i;
    *(s16*)(g_FieldingLogic + 0xCE) = *(s16*)(g_FieldingLogic + 0xCC);
    *(s16*)(g_FieldingLogic + 0xE0) = *(s16*)(g_FieldingLogic + 0xDE);
    if (g_Ball[0x1BE3] != 0) {
        g_Ball[0x1BE3]--;
    }
    for (i = 0; i < 9; i++) {
        g_Fielders[i * 0x268 + 0x1FC] = 0;
        g_Fielders[i * 0x268 + 0x257] = g_Fielders[i * 0x268 + 0x256];
        g_Fielders[i * 0x268 + 0x256] = 0;
        g_Fielders[i * 0x268 + 0x20C] = g_Fielders[i * 0x268 + 0x20B];
        g_Fielders[i * 0x268 + 0x20B] = 0;
        g_Fielders[i * 0x268 + 0x216] = 0;
        g_Fielders[i * 0x268 + 0x263] = 0;
    }
    if (*(s16*)(g_Ball + 0x1B66) == 1 || (*(s16*)(g_Ball + 0x1B66) == 0x65 && g_FieldingLogic[0x107] != 0)) {
        for (i = 0; i < 9; i++) {
            *(f32*)(g_Fielders + i * 0x268 + 0x118) = *(f32*)(g_Fielders + i * 0x268);
            *(f32*)(g_Fielders + i * 0x268 + 0x11C) = *(f32*)(g_Fielders + i * 0x268 + 8);
        }
    }
    g_FieldingLogic[0x76] = 0;
    g_FieldingLogic[0x7C] = 0;
    g_FieldingLogic[0x82] = 0;
    g_FieldingLogic[0x88] = 0;
    g_FieldingLogic[0x144] = 0;
    g_Ball[0x1BEF] = 0;
    g_Pitcher[0x176] = 0;
    if (g_FieldingLogic[0x146] != 0) {
        g_FieldingLogic[0x146]--;
    }
}

// .text:0x00058870 size:0x5E0 mapped:0x80697904
void fn_3_58870(void) {
    return;
}

// .text:0x00058E50 size:0x108 mapped:0x80697EE4
extern u8 lbl_3_data_46F8[];
extern void fn_3_6E24C(int, int);
void fn_3_58E50(void) {
    u8* m;
    int i;
    g_GameLogic[0x155] = 0;
    if (g_d_GameSettings[0x11] != 0) {
        m = g_Minigame;
        for (i = 0; i < 4; i++) {
            int v = m[0x18F4];
            if ((s8)v >= 0) {
                int idx = ((s8)v == (s8)g_Minigame[0x1904]) ? 0 : i + 2;
                u8* f;
                fn_3_6E24C((s8)v, idx);
                f = g_Fielders + idx * 0x268;
                if (idx == 0) {
                    f[0x1D2] = lbl_3_data_46F8[m[0x18D8] * 9];
                } else {
                    f[0x1D2] = lbl_3_data_46F8[m[0x18D8] * 9 + 7];
                }
            }
            m++;
        }
    }
}

// .text:0x00058F58 size:0x254 mapped:0x80697FEC
extern u8 g_Pitcher[];
extern u8 g_Runners[];
extern u8 g_Batter[];
extern f32 lbl_3_data_450C[][2];
extern f32 lbl_3_data_4554[][3][2];
extern f32 lbl_3_data_45B4[][2];
extern f32 lbl_3_data_45D4[][2];
// 99%: only reg swap (mulli/slwi dest r6/r7) in final table lookup
void fn_3_58F58(int n, f32* x, f32* z) {
    int flag = 0;
    int k;
    int sel;
    s16 p = *(s16*)(g_Pitcher + 0x11E);
    k = ((p > 0) ? 0 : -1) + 2;
    if (n <= 1) {
        *x = lbl_3_data_450C[n][0];
        *z = lbl_3_data_450C[n][1];
        return;
    }
    if (n <= 5) {
        u8 r = g_Runners[0x277];
        if (r != 0 && g_Runners[0x2A1] != 0 && *(s16*)(g_Ball + 0x1B68) > 0
            && g_Pitcher[0x155] < 15) {
            if (g_Batter[0x7B] == 0 && n == 3) {
                *x = *(f32*)(lbl_3_data_4444 + 0x10);
                *z = *(f32*)(lbl_3_data_4444 + 0x14);
                return;
            }
            if (g_Batter[0x7B] != 0 && n == 5) {
                *x = *(f32*)(lbl_3_data_4444 + 0x10);
                *z = *(f32*)(lbl_3_data_4444 + 0x14);
                return;
            }
        }
        sel = 0;
        if (p > 0x1E && (n == 2 || n == 4) && g_Batter[0x8F] >= 1 && g_Batter[0x8F] <= 3) {
            flag = 1;
        }
        if ((n == 2 && r == 1) || (n == 4 && g_Runners[0x51F] == 1)) {
            sel = k;
        }
        if (g_Runners[0x3CB] == 1) {
            if (n == 3 && g_Batter[0x7B] == 0) {
                sel = k;
                g_FieldingLogic[0x11E] = 0;
            }
            if (n == 5 && g_Batter[0x7B] == 1) {
                sel = k;
                g_FieldingLogic[0x11E] = 1;
            }
        }
        if (flag != 0) {
            *x = lbl_3_data_45B4[n - 2][0];
            *z = lbl_3_data_45B4[n - 2][1];
            return;
        }
        *x = lbl_3_data_4554[n - 2][sel][0];
        *z = lbl_3_data_4554[n - 2][sel][1];
        return;
    }
    *x = lbl_3_data_45D4[n - 6][0];
    *z = lbl_3_data_45D4[n - 6][1];
}

// .text:0x000591AC size:0x18C mapped:0x80698240
extern u8 g_Runners[];
void fn_3_591AC(void) {
    f32 spC;
    f32 sp8;
    u8* f2;
    int j;
    int i;
    for (i = 0; i < 9; i++) {
        f2 = g_Fielders + i * 0x268;
        if (g_GameLogic[0x12B] != 0) {
            fn_3_58F58(i, &spC, &sp8);
            *(f32*)(f2 + 0) = spC;
            *(f32*)(f2 + 8) = sp8;
        }
        *(f32*)(f2 + 0x14) = 0.0f;
        *(f32*)(f2 + 0x18) = 0.0f;
        *(f32*)(f2 + 0x1C) = 0.0f;
        *(f32*)(f2 + 0x30) = 0.0f;
        *(f32*)(f2 + 0x34) = 0.0f;
        *(f32*)(f2 + 0xD4) = *(f32*)(f2 + 0);
        *(f32*)(f2 + 0xD8) = *(f32*)(f2 + 8);
        *(f32*)(f2 + 0x50) = 0.0f;
        f2[0x1D9] = 0;
        *(s8*)(f2 + 0x1F5) = -1;
        f2[0x20F] = 0;
        spC = -*(f32*)(f2 + 0);
        sp8 = -*(f32*)(f2 + 8);
        *(f32*)(f2 + 0x48) = atan2(sp8, spC);
    }
    if (g_GameLogic[0x12B] != 0) {
        for (j = 0; j < 9; j++) {
            f2 = g_Fielders + j * 0x268;
            fn_3_58F58(j, (f32*)f2, (f32*)(f2 + 8));
            *(f32*)(f2 + 4) = 0.0f;
        }
    }
    if (g_Runners[0x277] == 1) {
        *(s16*)(g_Fielders + 0x65C) = 1;
        g_Fielders[0x6A7] = 1;
        g_Fielders[0x6C5] = 1;
        *(s16*)(g_FieldingLogic + 0xD2) = 2;
        g_FieldingLogic[0x102] = 1;
    }
}

// .text:0x00059338 size:0x28C mapped:0x806983CC
extern u8 lbl_3_data_470C[];
extern f32 g_AiLogic[];
// partial: logic complete, reg allocation differs (loop 1 temp/counter regs, loop 3/4 pointer regs)
void fn_3_59338(void) {
    int i;
    int j;
    u8* p;
    u8* f;
    u8* f2;
    u8* fb;
    for (i = 1; i < 10; i++) {
        s32* q = (s32*)(g_GameLogic + *(int*)(g_GameLogic + 0x10) * 0x50 + i * 8 + 0x40);
        s32 t = *q;
        if (t >= 0x14) {
            *q = t - 0x14;
        } else if (t >= 0xA) {
            *q = t - 0xA;
        }
    }
    p = g_GameLogic + *(int*)(g_GameLogic + 0x10) * 0x50;
    g_GameLogic[0x155] = j = 0;
    for (; j < 10; j++) {
        int b = *(int*)(p + 0x40);
        if (b <= 8) {
            fn_3_6E24C(*(int*)(p + 0x3C), b);
        }
        p += 8;
    }
    fb = g_Fielders;
    f = fb;
    for (i = 0; i < 9; i++) {
        u8 v = g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142];
        u8* row = lbl_3_data_46F8 + v * 9;
        int t;
        f[0x1D2] = row[i];
        if (v != 0) {
            t = lbl_3_data_470C[0] + (s32)((f32)(lbl_3_data_470C[1] - lbl_3_data_470C[0]) * g_AiLogic[*(int*)(g_GameLogic + 0xC)]);
            if (i <= 1) {
                f[0x1D2] += t / 2;
            } else {
                f[0x1D2] += t;
            }
        }
        f += 0x268;
    }
    f2 = fb;
    for (i = 0; i < 9; i++) {
        f2[0x1F1] = 0;
        f2[0x1E3] = 0;
        f2[0x1FA] = 0;
        f2[0x217] = 0;
        f2 += 0x268;
    }
}

// .text:0x000595C4 size:0x134 mapped:0x80698658
extern f32 lbl_3_rodata_CC4;
extern f32 lbl_3_rodata_B24;
extern f32 lbl_3_rodata_B60;
void fn_3_1AE44(u8, u16, f32, f32, f32);
void fn_3_595C4(void) {
    u8* fl;
    u8* f;
    int i;
    fn_3_58870();
    for (i = 0; i < 9; i++) {
        g_FieldingLogic[i + 0xF8] = 0;
        f = g_Fielders + i * 0x268;
        f[0x1CF] = 100;
        *(f32*)(f + 0x58) = lbl_3_rodata_CC4 * (f32)f[0x1CF] + lbl_3_rodata_B24;
        f[0x1CD] = 120;
        f[0x1D2] = 10;
        f[0x1D1] = 15;
        *(f32*)(f + 0x5C) = *(f32*)(f + 0x58) / (f32)f[0x1D1];
        f[0x1D3] = 0;
        f[0x1D9] = 0;
        f[0x1F1] = 0;
        f[0x1E3] = 0;
        f[0x219] = 1;
        *(s16*)(f + 0x178) = -1;
    }
    *(s16*)(g_FieldingLogic + 0xB0) = -1;
    *(f32*)(g_FieldingLogic + 8) = lbl_3_rodata_B60;
    *(f32*)(g_FieldingLogic + 8) = lbl_3_rodata_B60;
    *(f32*)(g_FieldingLogic + 8) = lbl_3_rodata_B60;
    *(s16*)(g_FieldingLogic + 0xB2) = -1;
    *(s16*)(g_FieldingLogic + 0xB4) = -1;
    *(s16*)(g_FieldingLogic + 0xB6) = -1;
    *(s16*)(g_FieldingLogic + 0xB8) = -1;
    *(s16*)(g_FieldingLogic + 0xBA) = -1;
    *(s16*)(g_FieldingLogic + 0xBE) = -1;
    g_FieldingLogic[0x136] = 1;
    g_FieldingLogic[0x137] = 0;
    *(u8**)(g_FieldingLogic + 0x70) = g_FieldingLogic;
    *(u8**)(g_FieldingLogic + 0x8C) = g_FieldingLogic + 0x74;
    *(f32*)(g_FieldingLogic + 8) = lbl_3_rodata_B60;
}

// .text:0x000596F8 size:0x164 mapped:0x8069878C
// partial: same logic as tail of fn_3_59338; only reg allocation/fmuls dest (f0 vs f1) differ
void fn_3_596F8(void) {
    int i;
    int j;
    u8* p;
    u8* f;
    g_GameLogic[0x155] = 0;
    p = g_GameLogic + *(int*)(g_GameLogic + 0x10) * 0x50;
    for (j = 0; j < 10; j++) {
        int b = *(int*)(p + j * 8 + 0x40);
        if (b <= 8) {
            fn_3_6E24C(*(int*)(p + j * 8 + 0x3C), b);
        }
    }
    for (i = 0; i < 9; i++) {
        u8 v = g_GameLogic[*(int*)(g_GameLogic + 0x10) + 0x142];
        u8* row = lbl_3_data_46F8 + v * 9;
        int t;
        f = g_Fielders + i * 0x268;
        f[0x1D2] = row[i];
        if (v != 0) {
            t = lbl_3_data_470C[0] + (s32)((f32)(lbl_3_data_470C[1] - lbl_3_data_470C[0]) * g_AiLogic[*(int*)(g_GameLogic + 0xC)]);
            if (i <= 1) {
                f[0x1D2] += t / 2;
            } else {
                f[0x1D2] += t;
            }
        }
    }
}


#pragma dont_inline off
