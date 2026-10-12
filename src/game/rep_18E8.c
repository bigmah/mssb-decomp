#include "game/rep_18E8.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "game/rep_1838.h"
#include "game/rep_AC8.h"
#include "game/rep_D0.h"
#include "game/auto_00_0005985C_text.h"
#include "main/file_8004207C.h"
#include "main/file_80011640.h"
#include "game/auto_00_00167CC4_text.h"
#include "game/auto_00_0006D4A0_text.h"
#include "game/rep_1188.h"
#include "game/rep_540.h"
#include "game/rep_12D0.h"
#include "main/file_80024184.h"
#include "header_rep_data.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/math_api.h"

extern GameScores g_Scores;

// Views of other units' globals, with only the fields used here.
// g_Fielders entry (stride 0x268); only the fields used here.
typedef struct RepFielder {
    /*0x000*/ VecXYZ pos;
    /*0x00C*/ u8 _00C[0x14 - 0xC];
    /*0x014*/ VecXYZ dest; // destination
    /*0x020*/ u8 _020[0x30 - 0x20];
    /*0x030*/ f32 velX;
    /*0x034*/ f32 velZ;
    /*0x038*/ f32 _038; // previous velocity x?
    /*0x03C*/ f32 _03C; // previous velocity z?
    /*0x040*/ u8 _040[0x48 - 0x40];
    /*0x048*/ f32 facing;
    /*0x04C*/ u8 _04C[0x50 - 0x4C];
    /*0x050*/ f32 speed;
    /*0x054*/ u8 _054[0x58 - 0x54];
    /*0x058*/ f32 maxSpeed;
    /*0x05C*/ u8 _05C[0x68 - 0x5C];
    /*0x068*/ f32 distToDest;
    /*0x06C*/ u8 _06C[0x70 - 0x6C];
    /*0x070*/ f32 _070;
    /*0x074*/ u8 _074[0x84 - 0x74];
    /*0x084*/ f32 distToFielder[9];
    /*0x0A8*/ f32 distToBase[4];
    /*0x0B8*/ f32 _0B8;
    /*0x0BC*/ u8 _0BC[0xF4 - 0xBC];
    /*0x0F4*/ f32 catchHeight;
    /*0x0F8*/ u8 _0F8[0x10C - 0xF8];
    /*0x10C*/ VecXYZ throwTarget;
    /*0x118*/ u8 _118[0x120 - 0x118];
    /*0x120*/ f32 _120;
    /*0x124*/ f32 _124;
    /*0x128*/ u8 _128[0x174 - 0x128];
    /*0x174*/ f32 _174;
    /*0x178*/ s16 rosterID;
    /*0x17A*/ s16 _17A; // action id (lbl_3_data_7E34 index)
    /*0x17C*/ s16 _17C;
    /*0x17E*/ s16 framesToDest;
    /*0x180*/ u8 _180[0x18C - 0x180];
    /*0x18C*/ s16 coveringBase;
    /*0x18E*/ u8 _18E[0x192 - 0x18E];
    /*0x192*/ s16 _192;
    /*0x194*/ s16 throwTimer;
    /*0x196*/ s16 _196;
    /*0x198*/ u8 _198[0x1A0 - 0x198];
    /*0x1A0*/ s16 _1A0;
    /*0x1A2*/ u8 _1A2[0x1AC - 0x1A2];
    /*0x1AC*/ s16 _1AC;
    /*0x1AE*/ u8 _1AE[0x1C2 - 0x1AE];
    /*0x1C2*/ s16 _1C2; // angle
    /*0x1C4*/ u8 _1C4; // throw skill?
    /*0x1C5*/ u8 _1C5;
    /*0x1C6*/ u8 _1C6;
    /*0x1C7*/ u8 _1C7[0x1C9 - 0x1C7];
    /*0x1C9*/ u8 _1C9; // lbl_3_data_4780 index
    /*0x1CA*/ u8 _1CA[0x1CD - 0x1CA];
    /*0x1CD*/ u8 _1CD; // speed-related stat
    /*0x1CE*/ u8 _1CE;
    /*0x1CF*/ u8 _1CF[0x1D2 - 0x1CF];
    /*0x1D2*/ u8 _1D2;
    /*0x1D3*/ u8 _1D3[0x1D7 - 0x1D3];
    /*0x1D7*/ u8 _1D7;
    /*0x1D8*/ u8 _1D8[0x1DF - 0x1D8];
    /*0x1DF*/ u8 throwing;
    /*0x1E0*/ u8 _1E0;
    /*0x1E1*/ u8 _1E1;
    /*0x1E2*/ u8 _1E2;
    /*0x1E3*/ u8 _1E3;
    /*0x1E4*/ u8 _1E4;
    /*0x1E5*/ u8 _1E5[0x1EC - 0x1E5];
    /*0x1EC*/ u8 _1EC;
    /*0x1ED*/ u8 _1ED;
    /*0x1EE*/ u8 _1EE;
    /*0x1EF*/ u8 _1EF;
    /*0x1F0*/ u8 _1F0[0x1F5 - 0x1F0];
    /*0x1F5*/ s8 _1F5; // base
    /*0x1F6*/ u8 _1F6;
    /*0x1F7*/ s8 _1F7;
    /*0x1F8*/ u8 _1F8;
    /*0x1F9*/ u8 _1F9[0x200 - 0x1F9];
    /*0x200*/ u8 _200;
    /*0x201*/ u8 _201[0x203 - 0x201];
    /*0x203*/ u8 _203;
    /*0x204*/ u8 _204;
    /*0x205*/ u8 _205;
    /*0x206*/ u8 _206[0x20D - 0x206];
    /*0x20D*/ u8 minigamePlayer;
    /*0x20E*/ u8 _20E;
    /*0x20F*/ u8 _20F;
    /*0x210*/ u8 _210;
    /*0x211*/ u8 _211;
    /*0x212*/ u8 _212; // state
    /*0x213*/ u8 _213; // runner index
    /*0x214*/ u8 _214; // lbl_3_data_4860 index
    /*0x215*/ u8 _215;
    /*0x216*/ u8 _216[0x25A - 0x216];
    /*0x25A*/ u8 _25A;
    /*0x25B*/ u8 _25B[0x25E - 0x25B];
    /*0x25E*/ u8 _25E;
    /*0x25F*/ u8 _25F[0x262 - 0x25F];
    /*0x262*/ u8 _262;
    /*0x263*/ u8 _263[0x268 - 0x263];
} RepFielder; // size: 0x268

extern RepFielder g_Fielders[9];

// g_RunningLogic (0x20 bytes); only the fields used here.
typedef struct RepRunningLogic {
    /*0x00*/ s16 _00; // one nibble per base
    /*0x02*/ s16 _02;
    /*0x04*/ s16 _04; // one nibble per base
    /*0x06*/ u8 _06[0x10 - 0x6];
    /*0x10*/ u8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13[0x20 - 0x13];
} RepRunningLogic;

extern RepRunningLogic g_RunningLogic;

// lbl_3_common_bss_37400, only the fields used here.
typedef struct RepBss37400 {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ s16 _40; // team whose stats feed fn_3_161588
} RepBss37400;

extern RepBss37400 lbl_3_common_bss_37400;

#pragma dont_inline on
extern int __float_nan[];
#define NAN (*(f32*)__float_nan)
f64 __frsqrte(f64);
extern u8 lbl_3_data_4744[];
extern u8 lbl_3_data_475C;
extern s16 lbl_3_data_49DC[]; // fielding tuning values
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
extern const f32 lbl_3_rodata_19C4;
extern const f32 lbl_3_rodata_19C8;
extern u8 lbl_3_data_4710[2]; // AI reaction delay range
extern s16 lbl_3_data_4638[2]; // chemistry thresholds (good, bad)
extern u8 lbl_3_data_4908[2];  // bad-chemistry miss chance range
extern void fn_3_161588(int, s16);
// from game/m_sound.h (which conflicts with UnknownHomes_Game.h over playSoundEffect)
u32 fn_3_8FF5C(s32 id, f32 x, f32 y, f32 z);
u32 fn_3_90220(s32 idx, s32 off);
extern const f32 lbl_3_rodata_1A14;
extern const f32 lbl_3_rodata_1A44;
extern const f32 lbl_3_rodata_1A48;
extern const f32 lbl_3_rodata_1A5C;
extern const f32 lbl_3_rodata_1A60;
extern const f32 lbl_3_rodata_1A64;
extern const f32 lbl_3_rodata_1A68;
extern const f32 lbl_3_rodata_1A6C;
extern const f32 lbl_3_rodata_1A70;
extern const f32 lbl_3_rodata_1A74;
extern const f32 lbl_3_rodata_1A78;
extern f32 lbl_3_data_4760[3]; // throw tuning: lift, speed factors
extern const f32 lbl_3_rodata_1A1C;
extern const f32 lbl_3_rodata_1A20;
extern const f32 lbl_3_rodata_1A24;
extern const f32 lbl_3_rodata_1A28;
extern const f32 lbl_3_rodata_1A3C;
extern const f32 lbl_3_rodata_19A8;
extern const f32 lbl_3_rodata_1A58;
extern const f32 lbl_3_rodata_1A18;
extern f32 lbl_3_data_4780[]; // per fielder class: covering distance
extern const f32 lbl_3_rodata_19A4;
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
// AI fielder fi holding the ball: decide where to throw (g_FieldingLogic._0C4) or which
// base to run to (_0CC). The per-situation predicates (fn_3_A1D04 .. fn_3_A3C00, fn_3_AB554)
// are inlined into this function in the original.
// NONMATCHING 38%: the original inlines the situation predicates (fn_3_A1D04, fn_3_A1DA0, fn_3_A1F3C, fn_3_A295C, fn_3_A2B6C, fn_3_A2C9C, fn_3_A2DDC, fn_3_A2FD8, fn_3_A31E8, fn_3_A32B8, fn_3_A37BC, fn_3_A384C, fn_3_A3B30, fn_3_A3C00, fn_3_AB554); here they are called. Decision order follows the asm
#if NONMATCHING
void fn_3_A009C(s32 fi) {
    s32 lockout;
    RepFielder* f;
    s32 limit;
    s32 i;
    s32 lead;
    s32 b;
    InMemRunnerType* r;
    s16 target;
    s16 cover;

    lockout = 0;
    f = &g_Fielders[fi];
    if (g_FieldingLogic._130 != 0) {
        if (g_RunningLogic._10 == 0) {
            if (g_Ball.ballZoneAwayFromHome < 2) {
                return;
            }
            g_FieldingLogic._0C4 = 6;
        }
    } else {
        limit = lbl_3_data_4710[0] + (s32)((f32)(lbl_3_data_4710[1] - lbl_3_data_4710[0]) *
                                          g_AiLogic.aIDifficultyMultiplierArray[g_GameLogic.awayTeamBattingInd_battingTeam]);
        if (g_Ball.numberOfThrowsDuringPlay <= 1 && g_Ball.timeSinceBallPickedUp < limit &&
            g_Ball.numberOfThrowsDuringPlay <= 1 &&
            (g_FieldingLogic._107 != 2 || fi != 1 || g_Ball.framesSinceHit >= 200)) {
            // AI reaction delay
            g_FieldingLogic._0C4 = -1;
            g_FieldingLogic._0CC = -1;
            return;
        }
        if (g_FieldingLogic._116 != 0) {
            return;
        }
        if (g_Strikes.outs >= 3 || g_Ball.AtBat_ContactResult == -1 || g_Ball.deadBallReason != 0) {
            g_FieldingLogic._0C4 = -1;
            g_FieldingLogic._0CC = -1;
            return;
        }
        if (g_RunningLogic._10 == 0 && g_Ball.timeSinceBallPickedUp < 0x3C) {
            g_FieldingLogic._0C4 = -1;
            g_FieldingLogic._0CC = -1;
            return;
        }
    }

    // gather the situation
    lbl_3_bss_1820 = 0;
    lbl_3_bss_1804 = 0;
    lbl_3_bss_1818 = 0;
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].forceOutCd == 1) {
            lbl_3_bss_1804 |= 1 << (i * 4);
        }
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            lbl_3_bss_1820++;
        }
    }
    if (g_FieldingLogic._10D != 0) {
        f->_192 = 0x2D;
    }
    fn_3_A3B30();
    fn_3_A4A10();
    fn_3_A3C00();
    fn_3_A384C();
    lead = fn_3_A1D04();

    // decide
    if ((g_Ball.ballZoneAwayFromHome == 4 || (g_Ball.ballZoneAwayFromHome == 3 && fi >= 6)) &&
        g_FieldingLogic._0BE >= 0 && g_FieldingLogic._0BE != fi) {
        // deep ball with a cutoff man available
        if (fn_3_A222C() || fn_3_A3374()) {
            goto decided;
        }
        if (!fn_3_A1DA0()) {
            g_FieldingLogic._0C4 = 6;
            g_FieldingLogic._0CC = -1;
            g_FieldingLogic._0DE = -1;
        }
        goto decided;
    }
    if (g_Strikes.outs == 2) {
        if (g_Runners[1].forceOutCd == 1 && lbl_3_bss_1858[1] <= 2) {
            if (f->_1C4 <= 1 && lbl_3_bss_1858[1] <= 0) {
                lockout = 1;
            }
            if (fn_3_A37BC() && fn_3_A46A0(lbl_3_bss_1808[1])) {
                goto decided;
            }
        }
        if ((lbl_3_bss_1824 & 1) && lbl_3_bss_1858[0] <= 6) {
            if (lbl_3_bss_1858[0] >= 4) {
                for (b = 1; b <= 3; b++) {
                    r = &g_Runners[b];
                    if (r->runnerOnFieldOrOutOrScored == 1 && (r->runningDirectionCode == 1 || r->runningDirectionCode == 2) &&
                        b == r->currentBase && f->distToBase[r->nextBase] < lbl_3_rodata_199C &&
                        lbl_3_bss_1858[lbl_3_bss_1808[b]] <= 3 && r->distanceFromBall < lbl_3_rodata_1994 &&
                        fn_3_A46A0(lbl_3_bss_1808[b])) {
                        goto decided;
                    }
                }
            }
            if (f->_1C4 <= 1 && lbl_3_bss_1858[0] <= 0) {
                lockout = 1;
            }
            fn_3_A46A0(lbl_3_bss_1808[0]);
            goto decided;
        }
    }
    if (lbl_3_bss_1824 == 0x1) {
        if (f->_1C4 <= 1 && lbl_3_bss_1858[0] <= 0) {
            lockout = 1;
        }
        if (lbl_3_bss_1858[0] <= 6 && fn_3_A46A0(lbl_3_bss_1808[0])) {
            goto decided;
        }
    }
    if (lbl_3_bss_181C == 3 && fn_3_A32B8()) {
        goto decided;
    }
    if (lbl_3_bss_181C == 2 && fn_3_A31E8()) {
        goto decided;
    }
    if (lbl_3_bss_1824 == 0x1000 && lbl_3_bss_1858[lbl_3_bss_1808[3]] <= 6 && fn_3_A46A0(lbl_3_bss_1808[3])) {
        goto decided;
    }
    if (lbl_3_bss_1824 == 0x100 && lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 6 && fn_3_A46A0(lbl_3_bss_1808[2])) {
        goto decided;
    }
    if (lbl_3_bss_1824 == 0x10 && lbl_3_bss_1858[lbl_3_bss_1808[1]] <= 5 &&
        g_Runners[lbl_3_bss_1808[1]].overrunBaseStage == 0 && fn_3_A46A0(lbl_3_bss_1808[1])) {
        goto decided;
    }
    if (lbl_3_bss_1824 == 0x1111 && fn_3_A2FD8()) {
        goto decided;
    }
    if (lbl_3_bss_1824 == 0x1011 && fn_3_A2DDC()) {
        goto decided;
    }
    if ((lbl_3_bss_1824 == 0x111 || lbl_3_bss_1824 == 0x11) && fn_3_A2C9C()) {
        goto decided;
    }
    if ((lbl_3_bss_1824 == 0x1001 || lbl_3_bss_1824 == 0x1101) && fn_3_A2B6C()) {
        goto decided;
    }
    if (lbl_3_bss_1824 == 0x101 && fn_3_A295C()) {
        goto decided;
    }
    if ((lbl_3_bss_1824 & 1) && g_Ball.ballZoneAwayFromHome <= 1) {
        if ((s8)g_Ball.ballZoneWhenCaught <= 1) {
            if (lbl_3_bss_1858[0] <= 6 && fn_3_A46A0(lbl_3_bss_1808[0])) {
                goto decided;
            }
        } else if (lbl_3_bss_1858[0] <= 4 && fn_3_A46A0(lbl_3_bss_1808[0])) {
            goto decided;
        }
    }
    if (fn_3_A2404() || fn_3_A25C4()) {
        goto decided;
    }
    if ((lbl_3_bss_1824 & 1) && lbl_3_bss_1858[0] <= 6 && fn_3_A46A0(lbl_3_bss_1808[0])) {
        goto decided;
    }
    if ((lbl_3_bss_1824 & 0x1000) && fn_3_A1F3C()) {
        goto decided;
    }
    if (g_Ball.ballZoneAwayFromHome >= 2 && fn_3_A2048()) {
        goto decided;
    }
    if (lead >= 0) {
        fn_3_A46A0(lead);
        goto decided;
    }
    // otherwise go after the lead runner caught off base
    for (i = 3; i >= 0; i--) {
        r = &g_Runners[i];
        if (r->runnerOnFieldOrOutOrScored == 1 && r->baseStandingOn < 0 && r->runningDirectionCode == 2) {
            fn_3_A46A0(i);
            break;
        }
    }

decided:
    target = g_FieldingLogic._0C4;
    if (target >= 0 && target <= 3) {
        cover = g_FieldingLogic._0D0[target];
        if (cover >= 0 && (g_Fielders[cover]._20F != 0 || g_Fielders[cover]._210 != 0 || g_Fielders[cover]._211 != 0)) {
            // the covering fielder is busy: run there instead
            g_FieldingLogic._0C4 = -1;
            g_FieldingLogic._0CC = target;
        }
    }
    if (g_RunningLogic._12 > 1 && g_Strikes.storedOuts <= 1 && (lbl_3_bss_1824 & 1) && g_Ball.ballZoneAwayFromHome <= 1 &&
        (s8)g_Ball.ballZoneWhenCaught <= 1 && g_FieldingLogic._0C4 == 1 && lbl_3_bss_1858[0] <= 2) {
        if (g_Runners[2].runnerOnFieldOrOutOrScored == 1 &&
            (g_Runners[2].runningDirectionCode == 1 || g_Runners[2].runningDirectionCode == 2) &&
            g_Runners[2].fractionalBasesRan <= lbl_3_rodata_19C4 && g_Runners[2].baseStandingOn < 0) {
            g_FieldingLogic._0C4 = -1;
        }
        if (g_Runners[3].runnerOnFieldOrOutOrScored == 1 &&
            (g_Runners[3].runningDirectionCode == 1 || g_Runners[3].runningDirectionCode == 2) &&
            g_Runners[3].fractionalBasesRan <= lbl_3_rodata_19C8 && g_Runners[3].baseStandingOn < 0) {
            g_FieldingLogic._0C4 = -1;
        }
    }
    if (lockout && g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3 && f->_1E0 == 1) {
        g_FieldingLogic._0C4 = -1;
    }
    if (g_FieldingLogic._0C4 == 6) {
        if (g_FieldingLogic._0BE < 0) {
            g_FieldingLogic._0C4 = -1;
        } else if (g_FieldingLogic._0BE == fi) {
            g_FieldingLogic._0C4 = -1;
        } else {
            if (lbl_3_rodata_1994 + g_Fielders[g_FieldingLogic._0BE]._0B8 > f->_0B8) {
                g_FieldingLogic._0C4 = -1;
            }
            if (f->distToFielder[g_FieldingLogic._0BE] < lbl_3_rodata_1994) {
                g_FieldingLogic._0C4 = -1;
            }
        }
    }
    if (f->_1ED == 0) {
        if (g_FieldingLogic._0CC >= 0) {
            if (g_Ball.numberOfThrowsDuringPlay == 1 && g_Ball.timeSinceBallPickedUp < 0x2D && g_FieldingLogic._114 != 0) {
                g_FieldingLogic._0CC = -1;
            } else {
                fn_3_A3CC0();
            }
        }
    } else {
        g_FieldingLogic._0CC = -1;
    }
    fn_3_AB554();
}
#endif

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
            fn_3_A41E8(3);
            return 1;
        } else if (m & 0x100) {
            fn_3_A41E8(3);
            return 1;
        } else if (m & 0x10) {
            fn_3_A41E8(2);
            return 1;
        }
        return 0;
    } else if (ball > 0x400) {
        if (m & 0x1000) {
            fn_3_A41E8(3);
            return 1;
        } else if ((m & 0x100) && !(m & 0x1000)) {
            fn_3_A41E8(2);
            return 1;
        }
        return 0;
    } else {
        if (m & 0x1000) {
            if (!(m & 0x10) || (m & 0x100)) {
                fn_3_A41E8(0);
                return 1;
            }
        } else if (m & 0x100) {
            fn_3_A41E8(3);
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
// NONMATCHING 98.5%: the load of rodata_19A0 is scheduled later than in the original
#if NONMATCHING
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
        if (lbl_3_bss_1858[lbl_3_bss_1808[2]] <= 4 && g_Strikes.outs == g_Strikes.storedOuts) {
            if (r->percentTowardsNextBase > lbl_3_rodata_19A0 && fn_3_A46A0(lbl_3_bss_1808[2])) {
                return 1;
            }
            if ((lbl_3_bss_1800 & 0x10) && r->percentTowardsNextBase > lbl_3_rodata_19BC && fn_3_A46A0(lbl_3_bss_1808[2])) {
                return 1;
            }
        }
    }
    return 0;
}
#endif

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
// NONMATCHING 97%: scheduling only (the original loads rodata_1998 before the ball position)
#if NONMATCHING
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
#endif

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
    s16 me;
    RepFielder* f;
    s16 other;
    s32 prev;
    s16 base;
    s32 i;
    InMemRunnerType* r;

    me = g_Ball.fielderWBallIndex;
    f = &g_Fielders[me];
    if (f->_1D7 == 1) {
        base = f->coveringBase;
        if (g_FieldingLogic._0CC != base) {
            f->coveringBase = -1;
            g_FieldingLogic._0D0[base] = -1;
            g_FieldingLogic._101[base] = 0;
            f->_1D7 = 0;
        }
    }
    g_FieldingLogic._11D = 0;
    if (g_FieldingLogic._0CC >= 0 && g_FieldingLogic._0CC <= 3) {
        other = g_FieldingLogic._0D0[g_FieldingLogic._0CC];
        if (other != me && f->distToBase[g_FieldingLogic._0CC] < lbl_3_rodata_199C) {
            prev = other;
            if (prev >= 0) {
                fn_3_5985C(prev, 9);
                g_Fielders[prev].coveringBase = -1;
            }
            f->coveringBase = g_FieldingLogic._0CC;
            f->_1D7 = 1;
            g_FieldingLogic._0D0[f->coveringBase] = me;
        }
        base = f->coveringBase;
        if (base >= 0) {
            if (f->distToDest < lbl_3_data_4780[f->_1C9]) {
                g_FieldingLogic._101[base] = 1;
            } else {
                g_FieldingLogic._101[base] = 0;
            }
        }
        g_FieldingLogic._11D = 1;
        for (i = 0; i < 4; i++) {
            if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
                if (g_Runners[i].forceOutCd == 1 && g_FieldingLogic._0CC == g_Runners[i].nextBase) {
                    g_FieldingLogic._11D = 2;
                    break;
                } else if (g_Runners[i].tagUpInd == 2 && g_FieldingLogic._0CC == i) {
                    g_FieldingLogic._11D = 2;
                    break;
                }
            }
        }
    }
    if (g_FieldingLogic._0CC == 9) {
        // inlined fn_3_A4158
        r = &g_Runners[g_FieldingLogic._0DE];
        if (r->runningDirectionCode == 2) {
            fn_3_52F4C(g_Ball.fielderWBallIndex, r->position.x, r->position.z);
        } else {
            f32 d = r->distanceFromBall;
            fn_3_52F4C(g_Ball.fielderWBallIndex, 2.0f * (r->velocity.x * d) + r->position.x,
                       2.0f * (r->velocity.y * d) + r->position.z);
        }
        base = g_Runners[g_FieldingLogic._0DE].baseStandingOn;
        if (base >= 0) {
            if (f->distToBase[g_FieldingLogic._0CC] < lbl_3_rodata_199C) {
                prev = g_FieldingLogic._0D0[base];
                if (prev >= 0) {
                    fn_3_5985C(prev, 9);
                    g_Fielders[prev].coveringBase = -1;
                }
                f->coveringBase = base;
                f->_1D7 = 1;
                g_FieldingLogic._0D0[f->coveringBase] = me;
            }
            base = f->coveringBase;
            if (base >= 0) {
                if (f->distToDest < lbl_3_data_4780[f->_1C9]) {
                    g_FieldingLogic._101[base] = 1;
                    g_FieldingLogic._0CC = -1;
                } else {
                    g_FieldingLogic._101[base] = 0;
                }
            }
            g_FieldingLogic._11D = 1;
        }
    }
    if (f->speed > lbl_3_rodata_1A18) {
        f->framesToDest = f->distToDest / f->speed;
    }
    fn_3_526DC(g_Ball.fielderWBallIndex);
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
// NONMATCHING 98.9%: base-coordinate loads and float temps scheduled differently; fn_3_A6ABC and fn_3_AABF8 are inlined
#if NONMATCHING
void fn_3_A41E8(s32 base) {
    s16 cover;
    RepFielder* f;
    s32 cut;
    f32 dz;
    s32 throwFrames;
    f32 d;
    f32 step;
    f32 a;
    f32 b;
    s32 n;
    f32 ballDist;
    s32 frames;
    f32 dx;
    s16 coverFrames;

    f = &g_Fielders[g_Ball.fielderWBallIndex];
    cover = g_FieldingLogic._0D0[base];
    if (base == 5) {
        // inlined fn_3_AABF8
        if (g_FieldingLogic._0D8 == -1) {
            cut = 0;
        } else if (g_FieldingLogic.playerAtMoundCutoffLocation != 1) {
            cut = 0;
        } else if (g_Fielders[g_FieldingLogic._0D8].coveringBase != 5) {
            cut = 0;
        } else if (f->_0B8 < lbl_3_rodata_19F0) {
            cut = 0;
        } else {
            cut = 1;
        }
        if (cut) {
            g_FieldingLogic._0CC = -1;
            g_FieldingLogic._0C4 = 5;
            return;
        }
        if (g_Ball.ballZoneAwayFromHome >= 3 && g_FieldingLogic._0BE >= 0 &&
            g_FieldingLogic._0BE != g_Ball.fielderWBallIndex) {
            g_FieldingLogic._0CC = -1;
            g_FieldingLogic._0C4 = 6;
            return;
        }
        g_FieldingLogic._0CC = -1;
        g_FieldingLogic._0C4 = -1;
        return;
    }
    // inlined fn_3_A6ABC(base x, z)
    dx = lbl_3_data_4444[base * 2] - f->pos.x;
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    dz = lbl_3_data_4444[base * 2 + 1] - f->pos.z;
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
    throwFrames = fn_3_52560(g_Ball.fielderWBallIndex, lbl_3_data_4444[base * 2], lbl_3_data_4444[base * 2 + 1]);
    if (cover == g_Ball.fielderWBallIndex || cover == -1 || ballDist < lbl_3_rodata_199C) {
        g_FieldingLogic._0CC = base;
        g_FieldingLogic._0C4 = -1;
        return;
    }
    coverFrames = g_Fielders[cover].framesToDest;
    if (throwFrames < coverFrames + 5) {
        g_FieldingLogic._0CC = base;
        g_FieldingLogic._0C4 = -1;
        return;
    }
    if (frames < coverFrames) {
        g_FieldingLogic._0CC = base;
        g_FieldingLogic._0C4 = -1;
        return;
    }
    g_FieldingLogic._0CC = -1;
    g_FieldingLogic._0C4 = base;
}
#endif

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
// NONMATCHING 95%: fn_3_A53DC (with fn_3_A6ABC) inlined through a static-inline copy of its body; register allocation and
// a few scheduling differences remain
#if NONMATCHING
static inline void InlA53DC(s32 i) {
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

void fn_3_A4A10(void) {
    s32 i;
    InMemRunnerType* r;
    s32 margin;

    for (i = 0; i < 4; i++) {
        r = &g_Runners[i];
        lbl_3_bss_1848[i] = 0;
        lbl_3_bss_1838[i] = -1;
        lbl_3_bss_1828[i] = -1;
        lbl_3_bss_17FC[i] = 0;
        if (r->runnerOnFieldOrOutOrScored == 1) {
            if (r->tagUpInd == 2) {
                fn_3_A4F50(i);
            } else if (r->baseStandingOn != -1 && r->forceOutCd <= 0) {
                InlA53DC(i);
            } else if (r->overrunBaseStage == 0) {
                if (r->forceOutCd == 1) {
                    fn_3_A5704(i);
                } else {
                    fn_3_A5B4C(i);
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        r = &g_Runners[i];
        lbl_3_bss_1858[i] = 9;
        if (r->runnerOnFieldOrOutOrScored == 1 &&
            (r->baseStandingOn == -1 || r->tagUpInd == 2 || r->forceOutCd > 0 || lbl_3_bss_1828[i] == 0)) {
            margin = lbl_3_bss_1848[i];
            if (margin >= 0x5A) {
                lbl_3_bss_1858[i] = 8;
            } else if (margin >= 0x1E) {
                lbl_3_bss_1858[i] = 7;
            } else if (margin >= 0xF) {
                lbl_3_bss_1858[i] = 6;
            } else if (margin >= 8) {
                lbl_3_bss_1858[i] = 5;
            } else if (margin >= -8) {
                lbl_3_bss_1858[i] = 4;
            } else if (margin >= -0xF) {
                lbl_3_bss_1858[i] = 3;
            } else if (margin >= -0x1E) {
                lbl_3_bss_1858[i] = 2;
            } else if (margin >= -0x2D) {
                lbl_3_bss_1858[i] = 1;
            } else {
                lbl_3_bss_1858[i] = 0;
            }
            if (g_FieldingLogic._107 == 2) {
                lbl_3_bss_1858[i] -= 2;
                if (lbl_3_bss_1858[i] < 2) {
                    lbl_3_bss_1858[i] = 0;
                } else {
                    lbl_3_bss_1858[i] -= 2;
                }
            }
        }
    }
}
#endif

// .text:0x000A4F50 size:0x48C mapped:0x806E3FE4
// NONMATCHING 90.6%: register allocation and scheduling differ; fn_3_A6ABC is inlined
#if NONMATCHING
void fn_3_A4F50(s32 i) {
    RepFielder* f;
    InMemRunnerType* r;
    s32 base;
    f32 tx;
    f32 tz;
    f32 dz;
    f32 dx;
    s16 cover;
    f32 step;
    f32 a;
    f32 b;
    s32 n;
    f32 ballDist;
    s32 frames;
    s32 throwFrames;
    s32 runnerFrames;
    f32 d;
    s16 coverFrames;

    f = &g_Fielders[g_Ball.fielderWBallIndex];
    r = &g_Runners[i];
    base = r->startingBase_baseAchieved;
    // inlined fn_3_A6ABC(base x, z)
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    tx = lbl_3_data_4444[base * 2];
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
    frames = f->_192 + (n + 0x14) + lbl_3_data_1C40;
    throwFrames = fn_3_52560(g_Ball.fielderWBallIndex, tx, tz);
    if (r->currentBase == r->startingBase_baseAchieved) {
        runnerFrames = r->framesToPreviousBase;
    } else {
        runnerFrames = r->framesToPreviousBase + 0xB4;
    }
    if (cover == g_Ball.fielderWBallIndex || cover == -1 || ballDist < lbl_3_rodata_19A4 ||
        ((coverFrames = g_Fielders[cover].framesToDest) < 0 && g_FieldingLogic._101[base] == 0) ||
        g_Ball.framesSinceHit < 0x46) {
        lbl_3_bss_1838[i] = base;
        lbl_3_bss_1828[i] = -1;
        lbl_3_bss_1848[i] = throwFrames - runnerFrames;
        return;
    }
    if (throwFrames < coverFrames + 5) {
        lbl_3_bss_1838[i] = base;
        lbl_3_bss_1828[i] = -1;
        lbl_3_bss_1848[i] = throwFrames - runnerFrames;
        return;
    }
    if (frames < coverFrames || (coverFrames < 0 && g_Fielders[cover]._1D2 <= g_Ball.framesSinceHit)) {
        lbl_3_bss_1828[i] = base + 10;
        lbl_3_bss_1838[i] = -1;
        lbl_3_bss_1848[i] = coverFrames - runnerFrames;
        return;
    }
    lbl_3_bss_1828[i] = base;
    lbl_3_bss_1838[i] = -1;
    lbl_3_bss_1848[i] = frames - runnerFrames;
}
#endif

// .text:0x000A53DC size:0x328 mapped:0x806E4470
// NONMATCHING 90%: instruction scheduling and register allocation differ; body (with fn_3_A6ABC inlined) is InlA53DC above, shared with fn_3_A4A10
#if NONMATCHING
void fn_3_A53DC(s32 i) {
    InlA53DC(i);
}
#endif

// .text:0x000A5704 size:0x448 mapped:0x806E4798
// NONMATCHING 87%: register allocation and scheduling differ; fn_3_A6ABC is inlined
#if NONMATCHING
void fn_3_A5704(s32 i) {
    RepFielder* f;
    InMemRunnerType* r;
    RepFielder* c;
    s32 base;
    f32 b;
    f32 step;
    s16 cover;
    f32 dx;
    f32 d;
    f32 tz;
    f32 a;
    f32 tx;
    s32 n;
    f32 ballDist;
    s32 frames;
    s32 throwFrames;
    s16 runnerFrames;
    f32 dz;
    s16 coverFrames;

    f = &g_Fielders[g_Ball.fielderWBallIndex];
    r = &g_Runners[i];
    base = r->nextBase;
    // inlined fn_3_A6ABC(next base x, z)
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    tx = lbl_3_data_4444[base * 2];
    tz = lbl_3_data_4444[base * 2 + 1];
    dx = tx - f->pos.x;
    runnerFrames = r->framesToNextBase;
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
    frames = f->_192 + n + lbl_3_data_1C40;
    throwFrames = fn_3_52560(g_Ball.fielderWBallIndex, tx, tz);
    if (cover == g_Ball.fielderWBallIndex || cover == -1 || ballDist < lbl_3_rodata_199C ||
        (c = &g_Fielders[cover], c->_1E2 != 0) ||
        ((coverFrames = c->framesToDest) < 0 && g_FieldingLogic._101[base] == 0)) {
        lbl_3_bss_1838[i] = base;
        lbl_3_bss_1828[i] = -1;
        lbl_3_bss_1848[i] = throwFrames - runnerFrames;
        return;
    }
    if (throwFrames < coverFrames + 5) {
        lbl_3_bss_1838[i] = base;
        lbl_3_bss_1828[i] = -1;
        lbl_3_bss_1848[i] = throwFrames - runnerFrames;
        return;
    }
    if (frames + 5 < coverFrames) {
        lbl_3_bss_1828[i] = base + 10;
        lbl_3_bss_1838[i] = -1;
        lbl_3_bss_1848[i] = coverFrames - runnerFrames;
        return;
    }
    lbl_3_bss_1828[i] = base;
    lbl_3_bss_1838[i] = -1;
    lbl_3_bss_1848[i] = frames - runnerFrames;
}
#endif

// .text:0x000A5B4C size:0x898 mapped:0x806E4BE0
// Sets runner i's plan: base to throw to, base to cover, frame margin.
#define SET_PLAN(i, thr, cov, margin)                                                              \
    do {                                                                                           \
        lbl_3_bss_1838[i] = (cov);                                                                 \
        lbl_3_bss_1828[i] = (thr);                                                                 \
        lbl_3_bss_1848[i] = (margin);                                                              \
    } while (0)
#define SET_PLAN_V(i, thr, cov, margin)                                                            \
    do {                                                                                           \
        lbl_3_bss_1848[i] = (margin);                                                              \
        lbl_3_bss_1828[i] = (thr);                                                                 \
        lbl_3_bss_1838[i] = (cov);                                                                 \
    } while (0)

void fn_3_A5B4C(s32 i) {
    InMemRunnerType* r;
    s32 cur;
    s32 next;
    f32 distNext;
    u8 dir;
    f32 pct;
    s32 ballDist;
    f32 distCur;
    f32 nextBallDist;
    f32 curBallDist;
    s32 v;
    s32 toward;
    s32 thr;
    s32 cov;

    r = &g_Runners[i];
    cur = r->currentBase;
    next = r->nextBase;
    nextBallDist = g_Ball.ballDistanceFromBase[next];
    curBallDist = g_Ball.ballDistanceFromBase[cur];
    toward = 0;
    distNext = r->distToNextBase;
    distCur = r->distToCurrentBase;
    ballDist = r->distanceFromBall;
    if (nextBallDist + curBallDist < lbl_3_rodata_1A1C && r->actionCode == 0) {
        lbl_3_bss_17FC[i] = 1;
        if (nextBallDist < distNext) {
            toward = 1;
        } else if (curBallDist < distCur) {
            toward = -1;
        }
        dir = r->runningDirectionCode;
        if (dir == 1) {
            if (r->restrictedMovementCodes & 1) {
                SET_PLAN(i, -1, 9, 0);
                return;
            }
            if (toward == 1) {
                if (g_Ball.baseBallAndFielderAreOn == next &&
                    ((distNext < lbl_3_rodata_1A20 && dir == 1 && r->nextDirectionBeingProcessed == 0) ||
                     r->actionCode != 0)) {
                    lbl_3_bss_1848[i] = -0x32;
                    lbl_3_bss_1838[i] = next;
                    lbl_3_bss_1828[i] = -1;
                    return;
                }
                SET_PLAN(i, -1, 9, -0xF);
                return;
            }
            v = fn_3_A63E4(i, 1, &thr, &cov) - 10;
            if (g_Ball.numberOfThrowsDuringPlay <= 3 && g_FieldingLogic._0CC == -1 && v >= -0x2D) {
                SET_PLAN_V(i, thr, cov, v);
                return;
            }
            if (r->percentTowardsNextBase > lbl_3_rodata_1A24 || v >= -0xF) {
                SET_PLAN_V(i, thr, cov, v);
                return;
            }
            SET_PLAN(i, -1, 9, 0);
            return;
        }
        if (dir == 3) {
            if (r->restrictedMovementCodes & 2) {
                SET_PLAN(i, -1, 9, 0);
                return;
            }
            if (toward == -1) {
                if (g_Ball.baseBallAndFielderAreOn == cur && distCur < lbl_3_rodata_1A20 && dir == 3 &&
                    r->nextDirectionBeingProcessed == 0) {
                    lbl_3_bss_1848[i] = -0x32;
                    lbl_3_bss_1838[i] = cur;
                    lbl_3_bss_1828[i] = -1;
                    return;
                }
                SET_PLAN(i, -1, 9, -0xF);
                return;
            }
            v = fn_3_A63E4(i, 0, &thr, &cov) - 10;
            pct = r->percentTowardsNextBase;
            if (pct < lbl_3_rodata_19A0 || v >= -8) {
                SET_PLAN_V(i, thr, cov, v);
                return;
            }
            if (pct < lbl_3_rodata_19B4 && v >= -8 &&
                (r->nextDirectionBeingProcessed == 0 || r->runningDirectionCode != 2)) {
                SET_PLAN_V(i, thr, cov, v);
                return;
            }
            SET_PLAN(i, -1, 9, 0);
            return;
        }
        SET_PLAN(i, -1, 9, 0);
        return;
    }
    dir = r->runningDirectionCode;
    if (dir == 1) {
        if (r->percentTowardsNextBase < lbl_3_rodata_19AC) {
            if (nextBallDist < lbl_3_rodata_19F0) {
                SET_PLAN(i, -1, 9, -0xF);
                return;
            }
            if (curBallDist < lbl_3_rodata_19F0) {
                if ((f32)ballDist > lbl_3_rodata_1994) {
                    v = fn_3_A63E4(i, 0, &thr, &cov);
                    SET_PLAN_V(i, thr, cov, v);
                }
                return;
            }
        }
        v = fn_3_A63E4(i, 1, &thr, &cov);
        v += lbl_3_data_1C40;
        if (v < -0x2D) {
            if ((f32)ballDist < lbl_3_rodata_1A0C) {
                SET_PLAN(i, -1, 9, -0xF);
                return;
            }
            if (nextBallDist > lbl_3_rodata_19F0) {
                SET_PLAN_V(i, thr, cov, v);
                return;
            }
            if (nextBallDist < distNext) {
                SET_PLAN(i, -1, 9, -0x1E);
                return;
            }
            SET_PLAN_V(i, thr, cov, v);
            return;
        }
        SET_PLAN_V(i, thr, cov, v);
        return;
    } else if (dir == 3) {
        v = fn_3_A63E4(i, 0, &thr, &cov);
        v += lbl_3_data_1C40;
        if (v < -0x1E) {
            if (curBallDist > lbl_3_rodata_19F0) {
                SET_PLAN_V(i, thr, cov, v);
                return;
            }
            if (curBallDist < distCur) {
                SET_PLAN(i, -1, 9, -0x1E);
                return;
            }
            SET_PLAN_V(i, thr, cov, v);
            return;
        }
        if (r->percentTowardsNextBase >= lbl_3_rodata_1A28) {
            SET_PLAN_V(i, thr, cov, v);
            return;
        }
        SET_PLAN_V(i, thr, cov, v);
        return;
    } else if (dir == 2) {
        if (r->baseStandingOn < 0) {
            if (nextBallDist < lbl_3_rodata_19F0) {
                SET_PLAN(i, -1, 9, -0xF);
                return;
            }
            v = fn_3_A63E4(i, 1, &thr, &cov);
            v += lbl_3_data_1C40;
            lbl_3_bss_1828[i] = thr;
            lbl_3_bss_1848[i] = v;
            lbl_3_bss_1838[i] = cov;
        }
    }
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
// NONMATCHING 86%: register allocation differs and the first runner loop uses a ctr loop in the original
#if NONMATCHING
void fn_3_A7040(s32 fi) {
    RepFielder* f;
    s8 base;
    s32 i;
    InMemRunnerType* r;
    f32 runAng;
    f32 d;
    f32 bd;
    s32 near;
    s32 kind;
    s32 b;

    g_FieldingLogic._111 = 0;
    f = &g_Fielders[fi];
    base = -1;
    g_FieldingLogic._0E8 = -1;
    if (g_Strikes.outs < 3 && g_Ball.ballState == BALL_STATE_HELD && g_Ball.fielderWBallIndex >= 0 &&
        g_FieldingLogic._124 == 0) {
        if (f->_1F5 >= 0) {
            base = f->_1F5;
        }
        if (f->distToBase[0] <= lbl_3_rodata_1968) {
            base = 0;
        } else if (f->distToBase[1] <= lbl_3_rodata_1968) {
            base = 1;
        } else if (f->distToBase[2] <= lbl_3_rodata_1968) {
            base = 2;
        } else if (f->distToBase[3] <= lbl_3_rodata_1968) {
            base = 3;
        }
        if (base >= 0) {
            for (i = 3; i >= 0; i--) {
                r = &g_Runners[i];
                if ((g_Pitcher.strikeOutOrWalk != 2 || r->furthestBaseForcedToGoToOnWalk <= r->currentBase) &&
                    r->runnerOnFieldOrOutOrScored == 1) {
                    if (base == r->baseStandingOn_Stored && r->baseStandingOn < 0 && g_Ball.timeSinceBallPickedUp > 0xF &&
                        r->position.x < lbl_3_rodata_1A38) {
                        g_FieldingLogic._111 = 5;
                        g_FieldingLogic._0E8 = i;
                        g_FieldingLogic._112 = 1;
                        g_FieldingLogic._0EC = 1;
                        g_FieldingLogic._124 = 0xF;
                        g_FieldingLogic._135 = 1;
                        goto found;
                    }
                    if (base == r->baseRunningTowards) {
                        if ((r->forceOutCd == 1 && r->nextBase == base) || r->forceOutType_unsed != 0) {
                            break;
                        }
                        if (r->actionCode != 0) {
                            if (r->actionFrames_countDown < 6) {
                                g_FieldingLogic._111 = 1;
                                g_FieldingLogic._0E8 = i;
                                g_FieldingLogic._112 = 1;
                                g_FieldingLogic._124 = 0xF;
                                g_FieldingLogic._125 = base;
                                g_FieldingLogic._135 = 1;
                                if (g_FieldingLogic._0DE >= 0) {
                                    g_FieldingLogic._0DE = i;
                                }
                                goto found;
                            }
                        } else if (r->tagUpInd == 2 && r->distanceFromBall < lbl_3_rodata_1A3C &&
                                   g_Ball.timeSinceBallPickedUp > 0xF) {
                            if (r->baseStandingOn == base && i != r->baseStandingOn) {
                                g_FieldingLogic._111 = 5;
                            } else {
                                g_FieldingLogic._111 = 2;
                            }
                            g_FieldingLogic._0E8 = i;
                            g_FieldingLogic._112 = 1;
                            g_FieldingLogic._0EC = 1;
                            g_FieldingLogic._124 = 0xF;
                            g_FieldingLogic._135 = 1;
                            goto found;
                        }
                    }
                }
            }
        }
        if (g_Ball.timeSinceBallPickedUp > 0xF) {
            for (i = 3; i >= 0; i--) {
                r = &g_Runners[i];
                if (r->runnerOnFieldOrOutOrScored != 1 ||
                    (f->coveringBase >= 0 && r->forceOutCd == 1 && r->nextBase == base)) {
                    continue;
                }
                runAng = game_atan2(r->velocity.x, r->velocity.z);
                if (fn_3_9FC1C(game_atan2(f->pos.x - r->position.x, f->pos.z - r->position.z), runAng) < 0x100 &&
                    r->baseStandingOn < 0) {
                    if ((r->baseStandingOn < 0 || r->tagUpInd == 2) && r->distanceFromBall - f->speed < lbl_3_rodata_1A3C) {
                        g_FieldingLogic._111 = 2;
                        g_FieldingLogic._0E8 = i;
                        g_FieldingLogic._112 = 1;
                        g_FieldingLogic._0EC = 1;
                        g_FieldingLogic._124 = 0xF;
                        g_FieldingLogic._135 = 1;
                        if (g_FieldingLogic._0DE >= 0) {
                            g_FieldingLogic._0DE = i;
                        }
                        goto found;
                    }
                    continue;
                }
                d = r->distanceFromBall;
                near = 0;
                if (d < lbl_3_rodata_1994) {
                    if (r->baseStandingOn < 0) {
                        near = 1;
                    } else {
                        if (r->runningDirectionCode == 1 && r->distToCurrentBase > lbl_3_rodata_19A8) {
                            near = 1;
                        }
                        if (r->forceOutCd == 1 && r->baseStandingOn == r->startingBase_baseAchieved) {
                            near = 1;
                        }
                    }
                }
                if (near) {
                    kind = 0;
                    if (r->forceOutCd == 1 && r->baseStandingOn == r->startingBase_baseAchieved && d < lbl_3_rodata_1A3C) {
                        kind = 2;
                    } else if ((g_FieldingLogic._0CC < 0 || g_FieldingLogic._0CC > 3 ||
                                (bd = f->distToBase[g_FieldingLogic._0CC], !(bd < lbl_3_rodata_198C) &&
                                 (!(bd < lbl_3_rodata_1994) || (r->forceOutCd == 0 && r->tagUpInd != 2)))) &&
                               d < lbl_3_rodata_1A3C) {
                        kind = 1;
                    }
                    if (kind) {
                        g_FieldingLogic._111 = 2;
                        g_FieldingLogic._0E8 = i;
                        g_FieldingLogic._112 = 1;
                        g_FieldingLogic._0EC = 1;
                        g_FieldingLogic._124 = 0xF;
                        g_FieldingLogic._135 = 1;
                        if (g_FieldingLogic._0DE >= 0) {
                            g_FieldingLogic._0DE = i;
                        }
                        goto found;
                    }
                }
            }
        }
        if (g_FieldingLogic._111 == 2 && f->speed == lbl_3_rodata_193C) {
            g_FieldingLogic._111 = 5;
        }
    }
    return;
found:
    r = &g_Runners[g_FieldingLogic._0E8];
    if (r->actionCode != 0) {
        if (r->runningDirectionCode == 1) {
            b = g_Runners[g_FieldingLogic._0E8].currentBase;
            g_FieldingLogic._090.x = lbl_3_data_4444[b * 2];
            g_FieldingLogic._090.y = lbl_3_rodata_193C;
            g_FieldingLogic._090.z = lbl_3_data_4444[b * 2 + 1];
            return;
        }
        b = g_Runners[g_FieldingLogic._0E8].nextBase;
        g_FieldingLogic._090.x = lbl_3_data_4444[b * 2];
        g_FieldingLogic._090.y = lbl_3_rodata_193C;
        g_FieldingLogic._090.z = lbl_3_data_4444[b * 2 + 1];
        return;
    }
    g_FieldingLogic._090.x = g_Runners[g_FieldingLogic._0E8].position.x;
    g_FieldingLogic._090.y = r->position.y;
    g_FieldingLogic._090.z = r->position.z;
}
#endif

// .text:0x000A76B4 size:0x5D4 mapped:0x806E6748
// NONMATCHING 99%: scratch registers differ (g_Ball base, input pointer, stick angle); fn_3_AB554 is inlined
#if NONMATCHING
void fn_3_A76B4(void) {
    s32 fi;
    RepFielder* f;
    InputStruct* in;
    s16 prevBase;
    u16 btn;
    s16 ang;
    s16 t;

    fi = g_Ball.fielderWBallIndex;
    prevBase = g_FieldingLogic._0CC;
    in = &g_Controls[g_GameLogic.teams[g_GameLogic.teamFielding]];
    f = &g_Fielders[fi];
    if (g_FieldingLogic._10E == 0 && g_Ball.deadBallReason == 0 && g_FieldingLogic._12B == 0 && g_Strikes.outs < 3) {
        g_FieldingLogic._13D = 0;
        g_FieldingLogic._130 = 0;
        if (g_FieldingLogic._0C6 >= 0) {
            g_FieldingLogic._0C4 = g_FieldingLogic._0C6;
            g_FieldingLogic._0C6 = -1;
            g_FieldingLogic._0C8 = 0;
            if (g_FieldingLogic._0C4 == 8) {
                g_FieldingLogic._130 = 1;
            }
        } else {
            if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.instructionNumber >= 0) {
                in = &g_Practice.inputs[g_GameLogic.teamFielding];
            } else if (g_d_GameSettings.minigamesEnabled != 0) {
                fi = g_Minigame.minigameRelatedIndex;
                in = &g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[g_Minigame._1922]];
            }
            if (g_d_GameSettings.GameModeSelected != 6) {
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
                btn = in->buttonInput;
                if ((btn & 0x100) && g_FieldingLogic._145 <= lbl_3_data_49DC[0x50 / 2]) {
                    if (in->newButtonInput & 0x100) {
                        if (btn & 0x40) {
                            g_FieldingLogic._0C4 = 6;
                        } else {
                            ang = in->controlStickAngle;
                            if (ang >= 0xE00 || (btn & 2)) {
                                g_FieldingLogic._0C4 = 1;
                            } else if (ang >= 0xA00 || (btn & 4)) {
                                g_FieldingLogic._0C4 = 0;
                            } else if (ang >= 0x600 || (btn & 1)) {
                                g_FieldingLogic._0C4 = 3;
                            } else if (ang >= 0x200 || (btn & 8)) {
                                g_FieldingLogic._0C4 = 2;
                            } else if (ang >= 0 || (btn & 2)) {
                                g_FieldingLogic._0C4 = 1;
                            } else {
                                g_FieldingLogic._145 = 1;
                            }
                        }
                    } else if (g_FieldingLogic._145 >= lbl_3_data_49DC[0x50 / 2]) {
                        g_FieldingLogic._130 = 1;
                    }
                    if (g_FieldingLogic._130 != 0) {
                        g_FieldingLogic._12D = 1;
                    } else if (g_FieldingLogic._12F <= lbl_3_data_475C && g_d_GameSettings.minigamesEnabled == 0 &&
                               g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) {
                        g_FieldingLogic._12D = 0;
                        g_FieldingLogic._13D = 1;
                    } else {
                        g_FieldingLogic._12D = 1;
                    }
                    goto done_input;
                }
            }
            if (g_FieldingLogic._136 == 0) {
                if (in->newButtonInput & 0x200) {
                    ang = in->controlStickAngle;
                    if (ang >= 0xE00 || (in->buttonInput & 2)) {
                        g_FieldingLogic._0CC = 1;
                    } else if (ang >= 0xA00 || (in->buttonInput & 4)) {
                        g_FieldingLogic._0CC = 0;
                    } else if (ang >= 0x600 || (in->buttonInput & 1)) {
                        g_FieldingLogic._0CC = 3;
                    } else if (ang >= 0x200 || (in->buttonInput & 8)) {
                        g_FieldingLogic._0CC = 2;
                    } else if (ang >= 0 || (in->buttonInput & 2)) {
                        g_FieldingLogic._0CC = 1;
                    }
                }
            } else {
                fn_3_3AAF8(fi);
                fn_3_3A584(fi);
            }
        }
done_input:
        if (g_FieldingLogic._130 != 0) {
            g_FieldingLogic._0CC = -1;
            g_FieldingLogic._0C4 = -1;
            fn_3_A009C(fi);
        }
        if ((g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) || g_FieldingLogic._0C4 == 5 || g_FieldingLogic._0C4 == 6) {
            g_FieldingLogic._145 = 0;
        } else {
            g_FieldingLogic._0C4 = -1;
        }
        if (g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3 && f->distToBase[g_FieldingLogic._0C4] <= lbl_3_rodata_199C) {
            g_FieldingLogic._0CC = g_FieldingLogic._0C4;
            g_FieldingLogic._0C4 = -1;
        }
        if (g_FieldingLogic._0C4 == 6 && g_FieldingLogic._0BE < 0) {
            g_FieldingLogic._0C4 = -1;
        }
        if (g_FieldingLogic._12A != 0 && g_FieldingLogic._0CC >= 0) {
            g_FieldingLogic._0CC = prevBase;
        }
        if (prevBase != g_FieldingLogic._0CC && g_FieldingLogic._0CC >= 0) {
            g_FieldingLogic._0E2 = -1;
            g_FieldingLogic._0DE = -1;
            g_FieldingLogic._0DC = g_Ball.baseBallAndFielderAreOn;
            f->_1A0 = 0;
            g_FieldingLogic._12A = 0x1E;
        }
        // inlined fn_3_AB554
        if (g_FieldingLogic._10D != 0) {
            t = g_Ball.timeSinceBallPickedUp;
            if (t >= 0 && t < 0x28) {
                if (g_FieldingLogic._0C4 >= 0) {
                    g_FieldingLogic._10C = 1;
                    g_FieldingLogic._10D = 0;
                }
            } else {
                g_FieldingLogic._10D = 0;
            }
        }
    }
}
#endif

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
    } else if (g_FieldingLogic._145 >= lbl_3_data_49DC[0x50 / 2]) {
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
// NONMATCHING 98.9%: idx/prev/runner registers differ (r8/r7/r6 vs r7/r6/r7)
#if NONMATCHING
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
#endif

// .text:0x000A85C8 size:0x40C mapped:0x806E765C
// NONMATCHING 92.5%: float register allocation in the inlined fn_3_A6ABC body differs
#if NONMATCHING
#pragma dont_inline off
// fn_3_A89D4 inlines this whole body; CW needs a raised inline limit for that
#pragma inline_max_size(600)
static inline void InlA85C8(f32 dist) {
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

void fn_3_A85C8(f32 dist) {
    InlA85C8(dist);
}
#pragma dont_inline on
#endif

// .text:0x000A89D4 size:0x980 mapped:0x806E7A68
// Chooses g_FieldingLogic.throwSpeedType for the current throw.
// NONMATCHING 90%: fn_3_A85C8 (with fn_3_A6ABC) inlined as its tail via InlA85C8; register allocation differs
#if NONMATCHING
void fn_3_A89D4(void) {
    RepFielder* f;
    f32 dx;
    f32 dz;
    f32 a;
    f32 b;
    f32 dist;
    f32 pred;
    s32 i;
    InMemRunnerType* r;

    f = &g_Fielders[g_Ball.fielderWBallIndex];
    dx = f->pos.x - g_Ball.throwDestination.x;
    dz = f->pos.z - g_Ball.throwDestination.z;
    g_FieldingLogic.throwSpeedType = 3;
    g_FieldingLogic._109 = 0;
    g_FieldingLogic._10B = 0;
    a = dx * dx;
    b = dz * dz;
    dist = a + b;
    g_FieldingLogic._0E6 = 0;
    SQRT_L(dist);
    if (g_FieldingLogic._119 != 0) {
        g_FieldingLogic.throwSpeedType = 9;
        return;
    }
    if (g_Runners[1].runnerOnFieldOrOutOrScored != 0 && g_Runners[1].actionCode != 0 &&
        g_Runners[1].fractionalBasesRan >= lbl_3_rodata_1A3C && g_Runners[1].fractionalBasesRan <= lbl_3_rodata_1A14 &&
        g_FieldingLogic._0C4 == 1 && g_Ball.baseBallAndFielderAreOn == 2) {
        g_FieldingLogic.throwSpeedType = 10;
        return;
    }
    if (dist > lbl_3_rodata_19E8 || (g_Ball.ballZoneAwayFromHome >= 3 && dist > lbl_3_rodata_19B8)) {
        g_FieldingLogic._109 = 1;
    }
    if (g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) {
        if (f->_1E0 == 1 && g_Ball.timeSinceBallPickedUp < 0x2D) {
            dx = (2.0f * f->_038 + f->pos.x) - g_Ball.throwDestination.x;
            dz = (2.0f * f->_03C + f->pos.z) - g_Ball.throwDestination.z;
            a = dx * dx;
            b = dz * dz;
            pred = a + b;
            SQRT_L(pred);
            if (pred < lbl_3_rodata_1A20) {
                g_FieldingLogic.throwSpeedType = 8;
                return;
            }
        } else {
            if (dist < lbl_3_rodata_1A44) {
                g_FieldingLogic.throwSpeedType = 8;
                return;
            }
            if (dist < lbl_3_rodata_1A48 && g_Fielders[g_FieldingLogic._0D0[g_FieldingLogic._0C4]].framesToDest > 0x1E) {
                g_FieldingLogic.throwSpeedType = 8;
                return;
            }
        }
    }
    if (g_Ball.ballZoneAwayFromHome <= 2) {
        // count runners up to the first one still in danger
        for (i = 0; i < 4; i++) {
            r = &g_Runners[i];
            if (r->runnerOnFieldOrOutOrScored == 1) {
                if (r->forceOutCd == 1 || r->tagUpInd == 2 || r->overrunBaseStage >= 3) {
                    break;
                }
                if (r->percentTowardsNextBase <= lbl_3_rodata_19BC && r->runningDirectionCode == 1) {
                    break;
                }
                if (r->percentTowardsNextBase >= lbl_3_rodata_19BC && r->percentTowardsNextBase <= lbl_3_rodata_1968) {
                    break;
                }
            }
        }
        if (i >= 4) {
            if (dist < lbl_3_rodata_1A0C) {
                g_FieldingLogic.throwSpeedType = 7;
                return;
            }
            g_FieldingLogic.throwSpeedType = 5;
            return;
        }
    }
    if (g_Ball.AtBat_ContactResult == -1) {
        if (dist > lbl_3_rodata_1964) {
            g_FieldingLogic.throwSpeedType = 4;
            return;
        }
        g_FieldingLogic.throwSpeedType = 5;
        return;
    }
    if (dist < lbl_3_rodata_19F0 && g_FieldingLogic.throwSpeedType < 5) {
        g_FieldingLogic.throwSpeedType = 5;
        return;
    }
    if (g_Ball.ballZoneAwayFromHome >= 3) {
        if (g_Ball.AtBat_ContactResult != 3 && g_Runners[0].runnerOnFieldOrOutOrScored == 1 &&
            g_Runners[0].fractionalBasesRan < lbl_3_rodata_1958 && g_FieldingLogic._0C4 == 1) {
            g_FieldingLogic.throwSpeedType = 3;
        }
        return;
    }
    InlA85C8(dist);
}
#endif

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
// Per-frame update for fielder fi while the play is live.
// NONMATCHING 61%: the original inlines fn_3_A6D48, fn_3_A8338, fn_3_AABF8, fn_3_AAA3C and fn_3_A9C74; here they are called. Control flow matches
#if NONMATCHING
void fn_3_A9D20(s32 fi) {
    s32 handled;
    RepFielder* f;
    s16 other;
    f32 d;

    handled = 0;
    f = &g_Fielders[fi];
    if (g_FieldingLogic._12A != 0) {
        g_FieldingLogic._12A--;
    }
    if (f->_20F != 0) {
        if (g_Ball.fielderWBallIndex == fi) {
            fn_3_A9354(fi, 2);
            g_FieldingLogic._13B = 1;
            g_FieldingLogic._111 = 0;
            return;
        }
        fn_3_25648(fi);
        return;
    }
    if (f->_210 != 0) {
        fn_3_251E4(fi);
        f->_1EE = 0;
        return;
    }
    if (f->_211 != 0) {
        fn_3_A96FC(fi);
        goto after;
    }
    if (f->_1EE != 0) {
        fn_3_A9984(fi);
        goto after;
    }
    if (f->_1EF != 0) {
        goto after;
    }
    if (f->_203 != 0) {
        fn_3_2F574(fi);
        goto after;
    }
    if (f->_262 != 0) {
        fn_3_25A68(fi);
        goto input;
    }
    if (f->_25A == 2 && f->_1ED != 0) {
        goto input;
    }
    if (f->_25E != 0) {
        if (f->_25E >= 3) {
            fn_3_30564(fi);
        }
        goto check;
    }
    if (f->_205 != 0) {
        if (f->_205 < 5) {
            f->_205 = 5;
        }
        fn_3_2FF2C(fi);
        goto check;
    }
    if (f->_1EC != 0 &&
        (g_FieldingLogic._11F == 0 || (g_Ball.timeSinceBallPickedUp > 0 && g_Ball.timeSinceBallPickedUp < 0xF))) {
        goto input;
    }
    if (g_FieldingLogic._111 != 0) {
        fn_3_A6E98(fi);
        return;
    }
    if (f->throwing != 0) {
        // wind-up of a throw already released
        if (f->throwTimer < 0x7FFE) {
            f->throwTimer++;
        } else {
            f->throwTimer = 0x7FFF;
        }
        if (f->throwTimer < f->_196) {
            if (g_Ball.ballState == BALL_STATE_HELD) {
                f->throwTimer = f->_196;
            }
            return;
        }
        if (f->_1D7 == 1) {
            other = g_FieldingLogic._0D0[f->coveringBase];
            if (other != fi && other >= 0) {
                fn_3_5985C(other, 9);
            }
            fn_3_5985C(fi, 1);
            g_FieldingLogic._0D0[f->coveringBase] = fi;
        } else {
            fn_3_5985C(fi, 9);
        }
        f->throwTimer = 0;
        f->throwing = 0;
        return;
    }
    fn_3_A6D48();
    if (g_FieldingLogic._0C4 < 0) {
        // no throw chosen yet
        if (f->_1C6 != 0) {
            fn_3_A009C(fi);
        } else if (g_FieldingLogic._116 == 0) {
            fn_3_A76B4();
            if (g_FieldingLogic._0CC >= 0) {
                fn_3_A8338(fi);
            } else {
                g_FieldingLogic._0E2 = -1;
            }
        }
        d = f->velX * f->velX + f->velZ * f->velZ;
        SQRT_L(d);
        f->speed = d;
        if (g_FieldingLogic._0C4 == f->coveringBase && g_FieldingLogic._0D0[f->coveringBase] == fi) {
            g_FieldingLogic._0C4 = -1;
        }
        if (g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) {
            f->throwTarget.x = lbl_3_data_4444[g_FieldingLogic._0C4 * 2];
            f->throwTarget.y = lbl_3_rodata_193C;
            g_Ball.throwDestination.x = f->throwTarget.x;
            g_Ball.throwDestination.y = f->throwTarget.y;
            g_Ball.throwDestination.z = lbl_3_data_4444[g_FieldingLogic._0C4 * 2 + 1];
            f->throwTarget.z = g_Ball.throwDestination.z;
        } else if (g_FieldingLogic._0C4 == 6) {
            if (g_FieldingLogic._0BE != fi) {
                f->throwTarget.x = g_Fielders[g_FieldingLogic._0BE].pos.x;
                f->throwTarget.y = lbl_3_rodata_193C;
                g_Ball.throwDestination.x = f->throwTarget.x;
                g_Ball.throwDestination.y = f->throwTarget.y;
                g_Ball.throwDestination.z = g_Fielders[g_FieldingLogic._0BE].pos.z;
                f->throwTarget.z = g_Ball.throwDestination.z;
            } else {
                g_FieldingLogic._0C4 = -1;
            }
        } else if (g_FieldingLogic._0C4 == 5) {
            if (fn_3_AABF8()) {
                f->throwTarget.x = lbl_3_data_4444[8];
                f->throwTarget.y = lbl_3_rodata_193C;
                g_Ball.throwDestination.x = f->throwTarget.x;
                g_Ball.throwDestination.y = f->throwTarget.y;
                g_Ball.throwDestination.z = lbl_3_data_4444[9];
                f->throwTarget.z = g_Ball.throwDestination.z;
            } else {
                g_FieldingLogic._0C4 = -1;
            }
        }
        g_FieldingLogic._119 = 0;
        fn_3_AAA3C(fi);
        if (g_FieldingLogic._0C4 >= 0) {
            g_FieldingLogic._0CC = -1;
            fn_3_A89D4();
            fn_3_79040();
        }
        fn_3_A9C74(fi);
        goto check;
    }
    if (f->_215 != 0) {
        f->_215--;
        return;
    }
    d = f->velX * f->velX + f->velZ * f->velZ;
    SQRT_L(d);
    f->speed = d;
    if (g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) {
        f->throwTarget.x = lbl_3_data_4444[g_FieldingLogic._0C4 * 2];
        f->throwTarget.y = lbl_3_rodata_193C;
        g_Ball.throwDestination.x = f->throwTarget.x;
        g_Ball.throwDestination.y = f->throwTarget.y;
        g_Ball.throwDestination.z = lbl_3_data_4444[g_FieldingLogic._0C4 * 2 + 1];
        f->throwTarget.z = g_Ball.throwDestination.z;
    }
    g_FieldingLogic._0E6++;
    if (g_FieldingLogic._10A == 0) {
        return;
    }
    fn_3_ABDD0(fi);
    f->throwing = 1;
    g_FieldingLogic._10A = 0;
    f->throwTimer = 0;
    g_FieldingLogic._111 = 0;
    g_FieldingLogic._112 = 0;
    goto check;
input:
    fn_3_A7C88();
    handled = 1;
    g_FieldingLogic._0C8 = 0;
check:
    if (g_Ball.fielderWBallIndex == fi && g_FieldingLogic._0C4 < 0 && handled == 0) {
        fn_3_A7040(fi);
    }
after:
    fn_3_5372C(fi);
    g_Ball.baseBallAndFielderAreOn = -1;
    if (g_Ball.fielderWBallIndex >= 0 && f->_1F5 >= 0) {
        g_Ball.baseBallAndFielderAreOn = f->_1F5;
        if (g_FieldingLogic._0CC == f->_1F5) {
            g_FieldingLogic._0CC = -1;
        }
    }
    if (f->throwing != 0) {
        if (f->throwTimer < 0x7FFE) {
            f->throwTimer++;
        } else {
            f->throwTimer = 0x7FFF;
        }
        if (f->throwTimer < f->_196) {
            if (g_Ball.ballState == BALL_STATE_HELD) {
                f->throwTimer = f->_196;
            }
        } else {
            fn_3_5985C(fi, 0xF);
            f->throwTimer = 0;
            f->throwing = 0;
        }
    }
}
#endif

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
// NONMATCHING 95.5%: float register allocation differs and one branch in the length/sqrt sequence; fn_3_A6ABC is inlined
#if NONMATCHING
void fn_3_AAFF0(f32* x, f32* z) {
    RepFielder* f;
    s32 n;
    f32 dz;
    f32 a;
    f32 d;
    f32 step;
    f32 dx;
    f32 len;
    RepFielder* t;
    f32 vz;
    f32 vx;
    f32 sq;
    f32 b;
    f32 speed;

    // inlined fn_3_A6ABC(receiver x, z)
    f = &g_Fielders[g_Ball.fielderWBallIndex];
    t = &g_Fielders[g_FieldingLogic._0BE];
    dx = t->pos.x - f->pos.x;
    step = (f32)f->_1CD / lbl_3_rodata_1938;
    dz = t->pos.z - f->pos.z;
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
    if (t->framesToDest < n - 5) {
        *x = t->dest.x;
        *z = t->dest.z;
    } else {
        vz = t->dest.z - t->pos.z;
        vx = t->dest.x - t->pos.x;
        sq = vx * vx + vz * vz;
        len = sq;
        SQRT_L(len);
        if (len == lbl_3_rodata_193C) {
            sq = lbl_3_rodata_1958;
        } else {
            SQRT_L(sq);
        }
        if (sq <= lbl_3_rodata_1980) {
            sq = lbl_3_rodata_1980;
        }
        n -= 10;
        speed = lbl_3_rodata_1A58 * t->maxSpeed;
        *x = (vx / sq) * speed * (f32)n + t->pos.x;
        *z = (vz / sq) * speed * (f32)n + t->pos.z;
    }
    g_Ball.fielderBeingThrownTo = g_FieldingLogic._0BE;
}
#endif

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
// Searches for a throw angle that makes the ball reach the throw target at a catchable height.
// NONMATCHING 96.8%: float register allocation differs (the original keeps 0.0f in f31 across the search loop)
#if NONMATCHING
void fn_3_AB5B0(s32 maxFrames, f32* outAngle, f32* speedPtr) {
    f32 drag;
    f32 x;
    f32 best;
    s32 result;
    f32 spd;
    s32 prev;
    f32 over;
    f32 maxH;
    f32 t;
    f32 dx;
    f32 dz;
    f32 prevBestAng;
    f32 bestAng;
    f32 dist;
    f32 angle;
    f32 b;
    f32 a;
    f32 step;
    s32 iter;
    s32 retries;
    f32 vx;
    f32 vy;
    f32 lift;
    f32 y;
    f32 minH;
    s32 frames;

    drag = lbl_3_rodata_1958 - (f32)g_Ball.airResistance / lbl_3_rodata_1A60;
    spd = *speedPtr;
    g_FieldingLogic._141 = 0;
    best = lbl_3_rodata_1A5C;
    result = 0;
    lift = lbl_3_rodata_193C;
    prev = 0;
    minH = lbl_3_rodata_19A0;
    if (checkFieldingStat(g_GameLogic.teamFielding, g_Fielders[g_Ball.fielderWBallIndex].rosterID, 4)) {
        if (g_FieldingLogic._0C4 == 0) {
            if (g_RunningLogic._04 & 0x1000) {
                g_FieldingLogic._140 = 1;
                g_FieldingLogic._141 = 1;
                playSoundEffect(0x1A8);
            }
        } else if (g_FieldingLogic._0C4 == 0 && (g_RunningLogic._04 & 0x1100)) {
            g_FieldingLogic._140 = 1;
            g_FieldingLogic._141 = 1;
            playSoundEffect(0x1A8);
        }
    }
    maxH = g_Fielders[g_FieldingLogic._0D0[g_FieldingLogic._0C4]].catchHeight - lbl_3_rodata_19A0;
    t = lbl_3_rodata_19B0 * maxH;
    if (lbl_3_rodata_19A0 < t) {
        minH = t;
    }
    dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    a = dx * dx;
    b = dz * dz;
    dist = a + b;
    SQRT_L(dist);
    angle = lbl_3_rodata_193C;
    bestAng = angle;
    step = lbl_3_rodata_1A64;
    if (g_FieldingLogic.throwSpeedType <= 6) {
        if (g_FieldingLogic._12D == 0) {
            if (g_FieldingLogic.throwSpeedType != 0) {
                g_FieldingLogic.throwSpeedType--;
            }
        } else if (g_FieldingLogic._12D == 2 && g_FieldingLogic.throwSpeedType < 6) {
            g_FieldingLogic.throwSpeedType++;
        }
    }
    switch (g_FieldingLogic.throwSpeedType) {
    case 0:
        spd *= lbl_3_rodata_1970;
        break;
    case 1:
        spd *= lbl_3_rodata_19EC;
        break;
    case 2:
        spd *= lbl_3_rodata_1A34;
        break;
    case 4:
        spd *= lbl_3_rodata_1A58;
        break;
    case 5:
        spd *= lbl_3_rodata_1968;
        break;
    case 6:
        spd *= lbl_3_rodata_1990;
        break;
    case 7:
        spd = lbl_3_rodata_197C;
        if (dist < lbl_3_rodata_19F0) {
            spd = lbl_3_rodata_19B4;
        } else if (dist < lbl_3_rodata_1A0C) {
            spd = lbl_3_rodata_1A68;
        }
        break;
    case 8:
        angle = lbl_3_rodata_1A24;
        spd = lbl_3_rodata_19AC;
        bestAng = angle;
        break;
    case 9:
        spd = lbl_3_rodata_1A6C;
        break;
    }
    if (g_FieldingLogic._13D != 0) {
        lift = lbl_3_data_4760[0];
        if (g_FieldingLogic._107 == 2 && g_Ball.fielderWBallIndex == 1 && g_Ball.framesSinceHit <= 0x82) {
            spd *= lbl_3_data_4760[1];
        }
    }
    if (g_FieldingLogic._140 != 0) {
        spd *= lbl_3_data_4760[2];
    }
    iter = 0;
    retries = 0;
    do {
        // simulate the throw at this angle
        vx = spd * (f32)cos(angle);
        vy = spd * (f32)sin(angle);
        y = g_Ball.AtBat_Contact_BallPos.y;
        x = lbl_3_rodata_193C;
        for (frames = 0; frames < 900;) {
            frames++;
            vx *= drag;
            vy = (vy - g_Ball.physicsSubstruct.gravity + lift) * drag;
            x += vx;
            y += vy;
            if (x > dist) {
                if (y < minH) {
                    result = 2;
                } else if (y < maxH) {
                    result = 3;
                } else {
                    result = 4;
                }
                break;
            }
            if (y < lbl_3_rodata_193C) {
                result = 1;
                break;
            }
        }
        if (frames < maxFrames && retries < 5 && result != 1) {
            // too slow: aim higher with less speed
            angle += step;
            g_FieldingLogic._140 = 0;
            retries++;
            spd *= lbl_3_rodata_1A58;
            g_FieldingLogic._141 = 0;
            continue;
        }
        if (result == 1) {
            // lands short
            if (prev >= 2) {
                break;
            }
            over = x - dist;
            if (over > best) {
                bestAng = angle;
                best = over;
                angle += step;
            } else {
                angle = lbl_3_rodata_19B0 * (bestAng + angle);
            }
        } else if (result == 2) {
            // arrives too low
            if (prev <= 1) {
                bestAng = angle;
                angle += step;
                step *= lbl_3_rodata_1A70;
            } else if (prev == 4) {
                t = prevBestAng + angle;
                bestAng = angle;
                step *= lbl_3_rodata_1A70;
                angle = lbl_3_rodata_19B0 * t;
            } else {
                if (!(y > best)) {
                    break;
                }
                bestAng = angle;
                angle += step;
            }
            best = y;
        } else if (result == 3) {
            // catchable
            bestAng = angle;
            break;
        } else if (result == 4) {
            // arrives too high
            if (prev <= 2) {
                bestAng = angle;
                if (iter == 0) {
                    angle -= step;
                } else {
                    angle = lbl_3_rodata_19B0 * (prevBestAng + angle);
                }
            } else {
                if (!(y < best)) {
                    break;
                }
                bestAng = angle;
                angle -= step;
                step *= lbl_3_rodata_1A70;
            }
            best = y;
        }
        prevBestAng = bestAng;
        prev = result;
    } while (++iter < 12);
    if (result == 1) {
        over = dist - x;
        if (over > lbl_3_rodata_1A74 && over < lbl_3_rodata_1A38 && g_FieldingLogic._0C4 == 0 &&
            g_Ball.ballAngleFromHome > 0x3B8 && g_Ball.ballAngleFromHome < 0x448) {
            bestAng += lbl_3_rodata_1A78;
        }
        frames = 600;
    }
    *outAngle = bestAng;
    *speedPtr = spd;
    g_Ball.framesUntilThrowReachesDest = frames;
    g_Ball.throwTimeEstimatesCompleteInd = 0;
    if (g_FieldingLogic._140 != 0) {
        fn_3_1682AC(lbl_8036E548.active[g_Ball.fielderWBallIndex], 4);
    }
}
#endif

// .text:0x000ABDD0 size:0xC28 mapped:0x806EAE64
// Releases the throw by fielder fi toward the chosen target.
// NONMATCHING 66%: the original inlines fn_3_AAC84 (with fn_3_A6ABC) for the default target; here it is called
#if NONMATCHING
void fn_3_ABDD0(s32 fi) {
    RepFielder* f;
    s16 cover;
    s32 rating;
    s32 limit;
    s32 rnd;
    f32 tx;
    f32 tz;
    f32 dx;
    f32 dz;
    f32 a;
    f32 b;
    f32 d;
    s16 ang;
    s32 spread;
    f32 angle;
    f32 speed;
    f32 horiz;
    s32 i;

    f = &g_Fielders[fi];
    g_FieldingLogic._13E = 0;
    g_Ball.IsAntichemistryThrow = 0;
    g_Ball.AtBat_Contact_BallPos.x = f->pos.x + g_Ball.offsetWhilePickedUpHistory[0].x;
    g_Ball.AtBat_Contact_BallPos.y = f->pos.y + g_Ball.offsetWhilePickedUpHistory[0].y;
    g_Ball.AtBat_Contact_BallPos.z = f->pos.z + g_Ball.offsetWhilePickedUpHistory[0].z;
    g_Ball.offsetWhilePickedUpHistory[0].x = lbl_3_rodata_193C;
    g_Ball.offsetWhilePickedUpHistory[0].y = lbl_3_rodata_193C;
    g_Ball.offsetWhilePickedUpHistory[0].z = lbl_3_rodata_193C;
    if (g_FieldingLogic._0C4 >= 0 && g_FieldingLogic._0C4 <= 3) {
        cover = g_FieldingLogic._0D0[g_FieldingLogic._0C4];
        tx = lbl_3_data_4444[g_FieldingLogic._0C4 * 2];
        tz = lbl_3_data_4444[g_FieldingLogic._0C4 * 2 + 1];
        g_Ball.fielderBeingThrownTo = cover;
        rating = fn_3_6D658(g_GameLogic.teamFielding, g_Fielders[fi]._17A, g_Fielders[cover]._17A);
        if (rating >= lbl_3_data_4638[0] && g_FieldingLogic._0C4 == g_Fielders[g_Ball.fielderBeingThrownTo]._1F5) {
            g_FieldingLogic._13E = 1;
        }
        if (rating < lbl_3_data_4638[1]) {
            // bad chemistry: the throw may go off target
            limit = LERPToNewRange_Float(rating, 0, 100, lbl_3_data_4908[0], lbl_3_data_4908[1]);
            rnd = RandomInt_Game(100);
            if ((g_d_GameSettings.GameModeSelected != 2 || g_Practice.instructionNumber < 0) && rnd < limit) {
                dx = tx - g_Ball.AtBat_Contact_BallPos.x;
                dz = tz - g_Ball.AtBat_Contact_BallPos.z;
                g_Ball.IsAntichemistryThrow = 1;
                a = dx * dx;
                b = dz * dz;
                d = a + b;
                SQRT_L(d);
                ang = fn_3_9FB8C(dx, dz);
                spread = RandomInt_Game_Range(lbl_3_data_49DC[0x46 / 2], lbl_3_data_49DC[0x48 / 2]);
                if (RandomInt_Game(2) != 0) {
                    ang = ang + spread;
                } else {
                    ang = ang - spread;
                }
                getComponentsFromSAng(ang, &dx, &dz);
                dx *= d;
                dz *= d;
                tx = g_Ball.AtBat_Contact_BallPos.x + dx;
                tz = g_Ball.AtBat_Contact_BallPos.z + dz;
            }
        }
    } else if (g_FieldingLogic._0C4 == 6 && g_FieldingLogic._0BE >= 0 && g_FieldingLogic._0BE != fi) {
        fn_3_AAFF0(&tx, &tz);
    } else {
        fn_3_AAC84(&tx, &tz);
    }
    g_Ball.throwTarget.x = tx;
    g_Ball.throwTarget.z = tz;
    rating = fn_3_6E1D4(f->_1CE);
    if (g_FieldingLogic._10B != 0) {
        if (g_FieldingLogic._0E6 > 0x3C) {
            g_FieldingLogic.throwSpeedType -= 2;
        } else if (g_FieldingLogic._0E6 > 0x28) {
            g_FieldingLogic.throwSpeedType -= 1;
        }
        g_FieldingLogic._10B = 0;
    }
    if (g_FieldingLogic._13E != 0) {
        // good chemistry: faster throw
        if (g_FieldingLogic.throwSpeedType != 0 && g_FieldingLogic.throwSpeedType <= 3) {
            g_FieldingLogic.throwSpeedType -= 1;
            playSoundEffect(0x1AB);
        } else {
            g_FieldingLogic._13E = 2;
        }
        if (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_37400._40 == g_GameLogic.teamFielding) {
            fn_3_161588(7, f->rosterID);
        }
    }
    speed = (f32)rating / lbl_3_rodata_1938;
    if (g_FieldingLogic._0C4 == 6 || g_FieldingLogic._0C4 == 5) {
        fn_3_AB5B0(0, &angle, &speed);
    } else {
        fn_3_AB5B0(g_Fielders[g_FieldingLogic._0D0[g_FieldingLogic._0C4]].framesToDest, &angle, &speed);
    }
    g_Ball.physicsSubstruct.velocity.y = speed * (f32)sin(angle);
    horiz = speed * (f32)cos(angle);
    dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    angle = atan2(dz, dx);
    g_Ball.physicsSubstruct.velocity.x = horiz * (f32)cos(angle);
    g_Ball.physicsSubstruct.velocity.z = horiz * (f32)sin(angle);
    if (g_Ball.numThrowsDuringPlay < 0xFE) {
        g_Ball.numThrowsDuringPlay++;
    } else {
        g_Ball.numThrowsDuringPlay = 0xFF;
    }
    dx = g_Ball.throwTarget.x - g_Ball.AtBat_Contact_BallPos.x;
    dz = g_Ball.throwTarget.z - g_Ball.AtBat_Contact_BallPos.z;
    f->speed = lbl_3_rodata_193C;
    f->_196 = 0x3C;
    d = dx * dx + dz * dz;
    f->_1E3 = 1;
    g_Ball.framesSinceThrowStarted = 0;
    g_Ball.ballState = BALL_STATE_THROWN;
    g_Ball.fielderWBallIndex = -1;
    g_Ball.baseBallAndFielderAreOn = -1;
    g_Ball.ballIsLooseInd_unused = 0;
    g_Ball.fielderAboutToGetBall_hasBall = -1;
    g_Ball.thrownBallHasHitGround = 0;
    g_Ball.throwingFielder = fi;
    g_Ball.matchFramesAndBallAngle.framesSinceLastThrow = g_Ball.timeSinceBallPickedUp;
    g_Ball.timeSinceBallPickedUp = -1;
    g_Ball.ballZoneFromHomeAtStartOfThrow = g_Ball.ballZoneAwayFromHome;
    g_Ball.throwStartingLocation.x = g_Ball.AtBat_Contact_BallPos.x;
    g_Ball.throwStartingLocation.z = g_Ball.AtBat_Contact_BallPos.z;
    g_Ball.ballIsRollingIndicator = 0;
    g_FieldingLogic._11A = 0;
    g_FieldingLogic._11D = 0;
    f->_1E4 = 0;
    g_Pitcher.pickOffLoc = -1;
    g_FieldingLogic._0CA = g_FieldingLogic._0C4;
    g_FieldingLogic._124 = 0;
    g_FieldingLogic._125 = -1;
    g_FieldingLogic._12A = 0;
    g_FieldingLogic._0C6 = -1;
    SQRT_L(d);
    g_Ball.throwDistance = d;
    if (g_FieldingLogic._0BE == fi) {
        g_FieldingLogic._0BE = -1;
    }
    for (i = 0; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1) {
            g_Runners[i].baseReachedAtTimeOfThrow = g_Runners[i].currentBase;
        } else {
            g_Runners[i].baseReachedAtTimeOfThrow = -1;
        }
    }
    fn_3_A970(1);
    if (g_FieldingLogic.throwSpeedType <= 2 && g_FieldingLogic._12D == 0) {
        fn_3_8FF5C(0x16E, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
    } else {
        fn_3_8FF5C(0x16D, g_Ball.AtBat_Contact_BallPos.x, g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
    }
    fn_3_78574(fi);
    if (g_FieldingLogic._13E != 0) {
        fn_3_90220(f->_17A, 0);
    }
    if (g_Ball.IsAntichemistryThrow != 0) {
        fn_3_90220(f->_17A, 10);
    } else {
        fn_3_90220(f->_17A, 5);
    }
}
#endif


#pragma dont_inline off
