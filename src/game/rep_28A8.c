#include "game/rep_28A8.h"
#include "header_rep_data.h"
#include "musyx/musyx.h"
#include "math.h"

extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_58870(void);
extern void fn_3_1DEB8(void);
extern void fn_3_BF1AC(void);
extern void Set_803cb848(s32);
extern void fn_3_BF158(void);
extern void fn_3_AFD80(u8 state);
extern void fn_3_5A6D4(s32);
extern void fn_3_2EA24(void);
extern void fn_3_2E87C(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_1DD48(void*);
extern void fn_3_75560(void);
extern void atBat_batter(void);
extern u8 g_Pitcher[];
extern u8 lbl_8036E548[];
extern void fn_3_DF8D4(void);
extern void fn_3_15F998(void);
extern void fn_3_147DFC(void);
extern void fn_3_11CF84(void);
extern struct { s32 w0; u16 w4; u16 w6; u16 w8; u8 pad[2]; s16 n; u8 pad0[4]; s16 w12; u8 pad1[0x1D0 - 0x14]; u8 b1D0; u8 pad2; u8 b1D2; u8 pad3[2]; u8 b1D5; u8 pad4[3]; u8 b1D9; s8 b1DA; u8 pad5[0x220 - 0x1DB]; u8 b220; } lbl_3_common_bss_34C90;
extern u8 lbl_803CBC3C;
extern u8 g_Minigame[];
extern u8 g_Ball[];
extern u8 lbl_3_data_189AC[];
extern int fn_3_B7E10(f32, f32);
extern u8 g_d_GameSettings[];
extern u8 lbl_3_data_18C48[];
extern u8 lbl_8037169C[];
extern int random_fn_3_9EE24(int);
extern u8 lbl_3_data_1899C[];
extern void changeScene(s32, s32);
#define B34C90 ((u8*)&lbl_3_common_bss_34C90)
typedef struct { s32 a; u8 pad[0x1CE]; u8 b1D2; u8 pad2[7]; s8 b1DA; } SB;
typedef struct { u8 pad[0x18D8]; u8 f18D8[4]; } SM;
typedef struct { u8 p0[6]; u16 b6; u16 b8; u8 pad[0x1D2 - 0xA]; u8 b1D2; u8 pad1; u8 b1D4; u8 pad2[5]; s8 b1DA; } SC;
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_5B408(void);
extern u8 lbl_800EFBA4[];
extern u8 g_Controls[];
typedef struct { s32 a; u16 b4; u16 b6; u16 b8; u8 pad0[2]; s16 c; u8 pad1[4]; s16 d12; u8 pad2[0x1D0 - 0x14]; u8 b1D0; u8 pad3; u8 b1D2; u8 pad4[2]; u8 b1D5; u8 pad5[3]; u8 b1D9; u8 b1DA; u8 pad6[0x220 - 0x1DB]; u8 b220; } SD;
typedef struct { u8 p0[4]; u16 b4; u16 b6; u16 b8; u8 p1[6]; } CT;
#define L34 ((SD*)&lbl_3_common_bss_34C90)
extern void fn_3_107E80(void);
extern s32 fn_3_5B380(u16 buttons);
extern void fn_8004CC18(void);
typedef struct { f32 x, y, z; } V3X;
typedef struct { u8 pad0[0xCD0]; V3X pos[8]; u8 pad1[0x1180 - 0xD30]; V3X vel[8]; u8 pad2[0x17C8 - 0x11E0]; s16 f17C8; u8 pad3[0x1939 - 0x17CA]; u8 cnt; u8 flags[8]; u8 pad4[0x199F - 0x1942]; u8 f199F; } MGF;
typedef struct { f32 a, b, c, d; } T18AC8;
extern T18AC8 lbl_3_data_18AC8[];
extern const f32 lbl_3_rodata_28FC;
extern const f32 lbl_3_rodata_2918;
extern const f32 lbl_3_rodata_291C;
extern const f32 lbl_3_rodata_2920;
extern const f32 lbl_3_rodata_2924;
extern const f32 lbl_3_rodata_2928;
extern const f32 lbl_3_rodata_292C;
extern int rand(void);
extern f32 RandomF32_Game_Range(f32, f32);
extern void getComponentsFromSAng(s16, f32*, f32*);
extern s32 fn_3_9FE6C_normalizeAngle(s16);
typedef struct { u8 pad[0x18CC]; s8 a[12]; u8 b[4]; u8 pad2[0x1906 - 0x18DC]; u8 n; } SMX;
typedef struct { s32 a; u8 pad[0x1D1]; u8 b1D5; } SLB;
extern u8 g_Fielders[];
extern s32 fn_3_E5924(void);
extern void fn_3_59918(s32, s32);
extern void fn_3_A0F0(void);
extern u8 g_GameLogic[];
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];

extern void ballPhysica(void);
extern void fn_3_D8CD0(void);
extern void fn_3_D9868(void);
extern void fn_3_D9A30(void);
extern s32 fn_3_E8AC8(void);
void fn_3_DE308(s32 idx);
extern s16 lbl_3_data_49DC[];
extern u8 lbl_800EF808[]; // TODO type: options block (0x398: sound setting)
extern void fn_3_2F484(void);
extern u16 lbl_3_data_81DC[]; // per stadium: crowd sound id base
typedef struct { u8 vol; u8 ctrl; } CrowdSnd;
extern CrowdSnd lbl_3_data_8404[]; // [stadium * 15 + sound]
extern CrowdSnd lbl_3_data_84B8[]; // [sound], GameModeSelected 6

// Same helper as in auto_00_000D8A10_text.c.
static inline void playCrowdSound(s32 n) {
    s32 stadium;
    u8 vol;
    SND_VOICEID voice;

    stadium = g_d_GameSettings[9]; // StadiumID
    if (g_d_GameSettings[7] == 6) { // GameModeSelected
        vol = lbl_3_data_84B8[n].vol;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].vol;
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + n, vol, 0x3F, 0);
    if (g_d_GameSettings[7] == 6) {
        vol = lbl_3_data_84B8[n].ctrl;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].ctrl;
    }
    sndFXCtrl(voice, 0x5B, vol);
}

// Wall Ball coin state in g_Minigame.
typedef struct {
    /* 0x0000 */ u8 pad0[0xCD0];
    /* 0x0CD0 */ V3X coinPos[30];
    /* 0x0E38 */ u8 pad1[0x1180 - 0xE38];
    /* 0x1180 */ V3X coinVel[30];
    /* 0x12E8 */ u8 pad2[0x17C8 - 0x12E8];
    /* 0x17C8 */ s16 coinFrames;
    /* 0x17CA */ u8 pad3[0x1890 - 0x17CA];
    /* 0x1890 */ s16 points[4];
    /* 0x1898 */ s16 latestPoints[4];
    /* 0x18A0 */ u8 pad4[0x18BC - 0x18A0];
    /* 0x18BC */ s16 out[4][2];
    /* 0x18CC */ u8 pad5[0x18F4 - 0x18CC];
    /* 0x18F4 */ s8 fielderSlot[4];
    /* 0x18F8 */ s8 fielderIndex[4];
    /* 0x18FC */ u8 pad6[0x1905 - 0x18FC];
    /* 0x1905 */ s8 rosterID;
    /* 0x1906 */ u8 pad7[0x190B - 0x1906];
    /* 0x190B */ u8 turnOverStatus;
    /* 0x190C */ u8 pad8[0x1939 - 0x190C];
    /* 0x1939 */ u8 coinsLeft;
    /* 0x193A */ u8 coinVisible[100];
    /* 0x199E */ u8 level;
    /* 0x199F */ u8 pad9[0x19CB - 0x199F];
    /* 0x19CB */ u8 multiplier;
} WallBallMG;

// lbl_3_data_18AC8: per-level coin spawn areas, then catch radii and coin physics.
typedef struct {
    /* 0x00 */ T18AC8 areas[12];
    /* 0xC0 */ f32 catchRadius[5]; // by fielder size class (g_Fielders + 0x1C9)
    /* 0xD4 */ f32 gravity;
    /* 0xD8 */ f32 drag;
    /* 0xDC */ f32 bounce;
    /* 0xE0 */ f32 floorY;
} WallBallData;

extern s16 lbl_3_data_18BB0[]; // [level * 2]: coin lifetime in frames
extern u8 lbl_3_common_bss_34C58[]; // TODO type: sound state (0x30: coin sound cooldown)
extern u8 lbl_3_data_88DC;

static inline f32 coinDistToFielder(WallBallMG* mg, s32 i, s32 slot) {
    u8* f = g_Fielders + mg->fielderIndex[slot] * 0x268;
    f32 dx = mg->coinPos[i].x - *(f32*)(f + 0x0);
    f32 dz = mg->coinPos[i].z - *(f32*)(f + 0x8);
    f32 sx = dx * dx;
    f32 sz = dz * dz;
    return dolsqrtf2(sx + sz);
}

// NONMATCHING 82%: original reaches 18AC8/18BB0/18C48 via the pooled base lbl_3_data_188E8 and re-materialises g_Minigame bases (lbz/extsb/add vs our lbzx)
// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
#if NONMATCHING
void fn_3_D9EA0(void) {
    WallBallMG* mg = (WallBallMG*)g_Minigame;
    WallBallData* wb = (WallBallData*)lbl_3_data_18AC8;
    s32 i;

    if (mg->coinsLeft == 0) {
        return;
    }
    if (mg->coinFrames < 0x7FFE) {
        mg->coinFrames++;
    } else {
        mg->coinFrames = 0x7FFF;
    }
    for (i = 0; i < 100; i++) {
        if (mg->coinVisible[i] != 0) {
            if (mg->coinFrames > lbl_3_data_18BB0[mg->level * 2]) {
                mg->coinVisible[i] = 0;
            } else {
                mg->coinVel[i].y -= wb->gravity;
                mg->coinVel[i].x *= wb->drag;
                mg->coinVel[i].y *= wb->drag;
                mg->coinVel[i].z *= wb->drag;
                mg->coinPos[i].x += mg->coinVel[i].x;
                mg->coinPos[i].y += mg->coinVel[i].y;
                mg->coinPos[i].z += mg->coinVel[i].z;
                if (mg->coinPos[i].y <= wb->floorY) {
                    mg->coinPos[i].y = wb->floorY;
                    mg->coinVel[i].y = -mg->coinVel[i].y;
                    mg->coinVel[i].x *= wb->bounce;
                    mg->coinVel[i].y *= wb->bounce;
                    mg->coinVel[i].z *= wb->bounce;
                }
            }
        }
    }
    for (i = 0; i < 100; i++) {
        if (mg->coinVisible[i] != 0) {
            f32 d0;
            f32 d1 = 999.9f;
            f32 d2 = 999.9f;
            s8 who;

            d0 = coinDistToFielder(mg, i, mg->fielderSlot[0]);
            if (mg->fielderSlot[1] >= 0) {
                d1 = coinDistToFielder(mg, i, mg->fielderSlot[1]);
            }
            if (mg->fielderSlot[2] >= 0) {
                d2 = coinDistToFielder(mg, i, mg->fielderSlot[2]);
            }
            if (d0 < d2 && d0 < d1) {
                d1 = d0;
                who = mg->fielderSlot[0];
            } else if (d1 < d2) {
                who = mg->fielderSlot[1];
            } else {
                d1 = d2;
                who = mg->fielderSlot[2];
            }
            if (d1 < wb->catchRadius[g_Fielders[mg->fielderIndex[who] * 0x268 + 0x1C9]]) {
                mg->coinVisible[i] = 0;
                mg->points[who] += *(s16*)(lbl_3_data_18C48 + 0x10) * mg->multiplier;
                if (--mg->coinsLeft == 0 && mg->turnOverStatus == 0) {
                    mg->turnOverStatus = 1;
                }
                if (lbl_3_common_bss_34C58[0x30] == 0) {
                    playCrowdSound(0xC);
                    lbl_3_common_bss_34C58[0x30] = lbl_3_data_88DC;
                }
            }
        }
    }
    if (mg->coinFrames > lbl_3_data_18BB0[mg->level * 2]) {
        if (mg->turnOverStatus == 0) {
            mg->turnOverStatus = 1;
        }
        if (mg->coinsLeft != 0) {
            mg->latestPoints[mg->rosterID] = mg->coinsLeft * mg->multiplier;
            mg->out[mg->rosterID][0] = mg->points[mg->rosterID];
            mg->out[mg->rosterID][1] = mg->latestPoints[mg->rosterID];
            mg->coinsLeft = 0;
        }
    }
}
#endif

// NONMATCHING 99%: only GPR order of loop invariants differs (orig range=r29, t=r27; ours swapped); decl orders tried
// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
#if NONMATCHING
void fn_3_DA640(s32 n, s32 idx) {
    f32 maxr;
    f32 sx, sy;
    f32 r, rv;
    f32* t;
    f32* ty;
    s32 range;
    s32 i;
    *(u8*)(g_Minigame + 0x1939) = n;
    *(u8*)(g_Minigame + 0x199F) = 1;
    *(s16*)(g_Minigame + 0x17C8) = 0;
    maxr = lbl_3_data_18AC8[idx].c;
    if (n >= 0x14) {
        maxr = lbl_3_data_18AC8[idx].d;
    }
    range = (s32)(lbl_3_rodata_2918 * maxr);
    t = &lbl_3_data_18AC8[idx].a;
    ty = &lbl_3_data_18AC8[idx].b;
    for (i = 0; i < n; i++) {
        s16 ang;
        g_Minigame[0x193A + i] = 1;
        *(f32*)(g_Minigame + i * 0xC + 0xCD4) = lbl_3_rodata_291C;
        { s32 q = rand() % range; r = lbl_3_rodata_2920 * (f32)q; }
        { s32 q2 = rand() % 0x1000; ang = fn_3_9FE6C_normalizeAngle(q2); }
        getComponentsFromSAng(ang, &sx, &sy);
        *(f32*)(g_Minigame + i * 0xC + 0xCD0) = sx * r + *t;
        *(f32*)(g_Minigame + i * 0xC + 0xCD8) = sy * r + *ty;
        rv = RandomF32_Game_Range(lbl_3_rodata_28FC, lbl_3_rodata_2924);
        *(f32*)(g_Minigame + i * 0xC + 0x1180) = sx * rv;
        *(f32*)(g_Minigame + i * 0xC + 0x1188) = sy * rv;
        *(f32*)(g_Minigame + i * 0xC + 0x1184) = RandomF32_Game_Range(lbl_3_rodata_2928, lbl_3_rodata_292C);
    }
}
#endif

// NONMATCHING 86%: original reaches 18BB8/189AC via the pooled base lbl_3_data_188E8; register allocation differs in the inlined fn_3_DE308/fn_3_DA640 copies
// .text:0x000DA834 size:0x1A0C mapped:0x807198C8
// Toy Field: per-frame handling of a ball result (g_Minigame + 0x1920).
#if NONMATCHING
void fn_3_DA834(void) {
    u8* bases = g_Minigame + 0x1914; // [0] batter, [1..3] runners on 1st..3rd
    s8* order = (s8*)(g_Minigame + 0x191C);
    s32 i;
    s32 j;

    if (*(s16*)(g_Minigame + 0x18AA) < 0x7FFE) {
        *(s16*)(g_Minigame + 0x18AA) += 1;
    } else {
        *(s16*)(g_Minigame + 0x18AA) = 0x7FFF;
    }
    if (*(s16*)(g_Minigame + 0x18AA) <= 1) {
        if (g_Minigame[0x1920] == 1 && g_Ball[0x1BD3] == 0) {
            g_Minigame[0x190B] = 1;
            fn_3_DE308(11);
            return;
        }
        g_Minigame[0x199F] = 1;
        if (g_Minigame[0x1920] >= 1 && g_Minigame[0x1920] <= 8) {
            g_Minigame[0x190B] = 1;
            switch (g_Minigame[0x1920]) {
            case 1:
                fn_3_DE308(22);
                break;
            case 2:
                if (g_Pitcher[0x14E] == 1 || g_Ball[0x1BD3] != 0) {
                    fn_3_DE308(22);
                } else if (g_Minigame[0x1926] == 0x71) {
                    fn_3_DE308(9);
                } else {
                    fn_3_DE308(10);
                }
                break;
            case 3:
                fn_3_DE308(0);
                break;
            case 4:
                fn_3_DE308(1);
                break;
            case 5:
                fn_3_DE308(2);
                break;
            case 6:
                if (g_Ball[0x1BD1] == 1) {
                    fn_3_DE308(4);
                } else {
                    fn_3_DE308(3);
                }
                break;
            case 7:
                fn_3_DE308(23);
                break;
            case 8:
                fn_3_DE308(23);
                break;
            }
            if (g_Minigame[0x1920] >= 3 && g_Minigame[0x1920] <= 6) {
                playCrowdSound(0);
            }
            if (g_Minigame[0x1920] == 2 || g_Ball[0x1BD3] != 0) {
                if (*(s16*)(g_Ball + 0x1B78) >= 0) {
                    g_Minigame[0x19C6] = g_Fielders[*(s16*)(g_Ball + 0x1B78) * 0x268 + 0x20D];
                } else {
                    g_Minigame[0x19C6] = g_Minigame[0x1904];
                }
            }
        } else {
            switch (g_Minigame[0x1920]) {
            case 11:
                fn_3_D9A30();
                fn_3_D9868();
                *(s16*)(g_Minigame + 0x19B8) = 1;
                break;
            case 9:
            case 10:
                if (*(f32*)(g_Minigame + 0x19AC) < 0.0f) {
                    fn_3_DA640(30, 6);
                } else {
                    fn_3_DA640(30, 4);
                }
                *(s16*)(g_Minigame + 0x19B8) = 1;
                g_Minigame[0x199E] = 0;
                break;
            default:
                g_Minigame[0x190B] = 1;
                break;
            }
        }
        if (g_Minigame[0x1920] >= 3 && g_Minigame[0x1920] <= 6) {
            // hit: every runner advances (1920 - 2) bases
            s32 n = g_Minigame[0x1920] - 2;
            for (i = 0; i < n; i++) {
                if (bases[3] != 0) {
                    g_Minigame[0x1921]++;
                }
                for (j = 3; j > 0; j--) {
                    bases[j] = bases[j - 1];
                    bases[j - 1] = 0;
                }
            }
            for (i = 0; i < 4; i++) {
                if (order[i] >= 0) {
                    order[i] += n;
                    if (order[i] >= 4) {
                        order[i] = 4;
                    }
                }
            }
        }
        if (g_Minigame[0x1920] == 7 || g_Minigame[0x1920] == 8) {
            // walk: only forced runners advance
            s32 n;
            if (bases[3] != 0) {
                g_Minigame[0x1921]++;
            }
            n = 1;
            if (bases[1] != 0) {
                n = 2;
                if (bases[2] != 0) {
                    n = 3;
                    if (bases[3] != 0) {
                        n = 4;
                    }
                }
            }
            for (j = n; j >= 1; j--) {
                bases[j] = bases[j - 1];
                bases[j - 1] = 0;
            }
            for (i = 0; i < 4; i++) {
                if (order[i] < 0) {
                    break;
                }
                order[i] += 1;
                if (order[i] >= 4) {
                    order[i] = 4;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (*(s16*)(g_Ball + 0x1B78) >= 0 && ((s8*)g_Minigame)[0x18F8 + i] == *(s16*)(g_Ball + 0x1B78)) {
                if (*(s16*)(g_Ball + 0x1B7A) == 3) {
                    fn_3_DE308(0x14);
                } else {
                    fn_3_DE308(0x15);
                }
                break;
            }
        }
        g_Minigame[0x1912] = 1;
    } else {
        if (g_Minigame[0x1920] == 0xB) {
            switch (g_Minigame[0x1934]) {
            case 1:
                break;
            case 0: {
                // slot machine reels: 0 spinning, 1 stopping, 2 stopped
                s16* tbl = (s16*)(lbl_3_data_189AC + 0xC);
                s16 firstStop = tbl[3];
                if (*(s16*)(g_Minigame + 0x18B8) < 0x7FFE) {
                    *(s16*)(g_Minigame + 0x18B8) += 1;
                } else {
                    *(s16*)(g_Minigame + 0x18B8) = 0x7FFF;
                }
                for (i = 0; i < 3; i++) {
                    u8 st = g_Minigame[0x1927 + i];
                    if (st == 0) {
                        if (*(s16*)(g_Minigame + 0x18B8) > tbl[i * 2]) {
                            g_Minigame[0x1927 + i] = 1;
                        }
                    } else if (st == 1) {
                        if (i == 0) {
                            if (*(s16*)(g_Minigame + 0x18B8) > firstStop) {
                                g_Minigame[0x1927 + i] = 2;
                            }
                        } else if (i == 2) {
                            if (g_Minigame[0x1930 + i] == 3) {
                                g_Minigame[0x1927 + i] = 2;
                            }
                        } else if (g_Minigame[0x1930 + i] >= 2) {
                            g_Minigame[0x1927 + i] = 2;
                        }
                    }
                }
                break;
            }
            case 2:
                fn_3_D8CD0();
                g_Minigame[0x1934] = 3;
                break;
            default:
                if (g_Minigame[0x192D] == 6) {
                    g_Minigame[0x19A6] = 3;
                    if (*(s16*)(g_Minigame + 0x18BA) == 1) {
                        fn_3_E8AC8();
                    }
                }
                if (*(s16*)(g_Minigame + 0x18BA) < 0x7FFE) {
                    *(s16*)(g_Minigame + 0x18BA) += 1;
                } else {
                    *(s16*)(g_Minigame + 0x18BA) = 0x7FFF;
                }
                break;
            }
        }
        if (g_Minigame[0x1920] == 9 || g_Minigame[0x1920] == 0xA) {
            fn_3_D9EA0();
        }
    }
}
#endif

// .text:0x000DC240 size:0x140 mapped:0x8071B2D4
void fn_3_DC240(void) {
    g_Minigame[0x1920] = g_Minigame[0x19C9];
    if (fn_3_E5924() != 0) {
        if (g_Minigame[0x19CF] == 0) {
            g_Minigame[0x1920] = 0xC;
        }
        if (g_Minigame[0x19CF] > 0x3C) {
            g_Minigame[0x19CE] = 1;
            return;
        }
        if (g_Minigame[0x19CF] < 0xFE) {
            g_Minigame[0x19CF] = g_Minigame[0x19CF] + 1;
            return;
        }
        g_Minigame[0x19CF] = 0xFF;
        return;
    }
    if (g_Minigame[0x1920] == 2 || g_Ball[0x1BD3] != 0) {
        if (g_Ball[0x1BD3] == 0) {
            fn_3_59918(1, 0);
        }
        g_Minigame[0x19C6] = g_Minigame[0x1904];
        if (*(s16*)(g_Ball + 0x1B78) >= 0) {
            g_Minigame[0x19C6] = g_Fielders[*(s16*)(g_Ball + 0x1B78) * 0x268 + 0x20D];
        }
    } else {
        u8 st = g_Minigame[0x1920];
        if (st == 1) {
            fn_3_A0F0();
        } else if (st == 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x000DC380 size:0x224 mapped:0x8071B414
void fn_3_DC380(void) {
    if (*(s16*)(g_Ball + 0x1B74) == 0 && *(s16*)(g_Ball + 0x1B8C) != 3) {
        s32 v = *(s32*)(g_Ball + 0x1B44);
        if (v >= 0x80) {
            v -= 0x80;
        }
        if (v >= 0x70 && v < 0x79) {
            g_Minigame[0x19C8] = lbl_3_data_189AC[v - 0x70];
        }
    }
    if (*(s16*)(g_Ball + 0x1B7A) == -1) {
        g_Minigame[0x19C9] = 1;
        return;
    }
    if (g_Minigame[0x1926] != 0) {
        g_Minigame[0x19C9] = lbl_3_data_189AC[g_Minigame[0x1926] - 0x70];
        return;
    }
    if (g_Ball[0x1BD1] != 0) {
        if (g_Ball[0x1BD1] == 1) {
            g_Minigame[0x19C9] = 6;
        } else if (g_Ball[0x1BD1] == 3) {
            g_Minigame[0x19C9] = 4;
        } else {
            g_Minigame[0x19C9] = 1;
        }
        g_Minigame[0x190B] = 1;
    } else {
        if (*(s16*)(g_Ball + 0x1B7A) == 0) {
            return;
        }
        if (g_Ball[0x1BC9] == 1) {
            u8* f = g_Fielders + *(s16*)(g_Ball + 0x1B78) * 0x268;
            if (f[0x1EE] != 0 || f[0x1EC] != 0) {
                return;
            }
        } else if (!(*(f32*)(g_Ball + 0x1A14) < 0.003f || g_Ball[0x1BD0] != 0 || g_Ball[0x1BDE] == 2)) {
            return;
        }
        if (*(s16*)(g_Ball + 0x1B7A) == 3) {
            g_Minigame[0x19C9] = 2;
            return;
        }
        if (g_Minigame[0x19C8] == 0) {
            if (fn_3_B7E10(*(f32*)g_Ball, *(f32*)(g_Ball + 8)) != 0) {
                g_Minigame[0x19C9] = 1;
            } else {
                g_Minigame[0x19C9] = 2;
            }
        } else {
            g_Minigame[0x19C9] = g_Minigame[0x19C8];
        }
        *(f32*)(g_Minigame + 0x19AC) = *(f32*)g_Ball;
        *(f32*)(g_Minigame + 0x19B0) = *(f32*)(g_Ball + 8);
        *(s16*)(g_Minigame + 0x19B8) = 1;
    }
}

// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void fn_3_DC5A4(void) {
    s32 r = fn_3_6C938(1, 0x100);
    if (r != 0) {
        lbl_3_common_bss_34C90.w0 = r - 1;
        if (lbl_3_common_bss_34C90.b1DA == 2) {
            fn_3_5B408();
            lbl_3_common_bss_34C90.b1D2 = 9;
        } else {
            lbl_3_common_bss_34C90.b1D2 = 4;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }
    if (fn_3_6C938(1, 8) != 0) {
        u8 t = lbl_3_common_bss_34C90.b1DA;
        if ((s8)t != 0) {
            lbl_3_common_bss_34C90.b1DA = t - 1;
        } else {
            lbl_3_common_bss_34C90.b1DA = 2;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }
    if (fn_3_6C938(1, 4) != 0) {
        lbl_3_common_bss_34C90.b1DA++;
        if (lbl_3_common_bss_34C90.b1DA >= 3) {
            lbl_3_common_bss_34C90.b1DA = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void fn_3_DC6E8(void) {
    s32 started;
    if (lbl_3_common_bss_34C90.w12 < 0x7FFE) {
        lbl_3_common_bss_34C90.w12 = lbl_3_common_bss_34C90.w12 + 1;
    } else {
        lbl_3_common_bss_34C90.w12 = 0x7FFF;
    }
    switch (lbl_3_common_bss_34C90.b1D2) {
    case 0:
        lbl_3_common_bss_34C90.b1DA = 0;
        lbl_3_common_bss_34C90.b1D0 = 0x12;
        lbl_3_common_bss_34C90.b1D2 = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90.w12 = 0;
        lbl_3_common_bss_34C90.b1D2 = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90.w12 >= 0x14) {
            lbl_3_common_bss_34C90.b1D2 = 3;
        }
        break;
    case 3:
        fn_3_DC5A4();
        lbl_3_common_bss_34C90.w12 = 0;
        break;
    case 4:
        if (lbl_3_common_bss_34C90.w12 >= 0x14) {
            changeScene(3, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            lbl_3_common_bss_34C90.b1D2 = 5;
        }
        break;
    case 5:
        lbl_8036E548[0x307A] = 0;
        started = 0;
        lbl_3_common_bss_34C90.b1D9 = 2;
        if (lbl_3_common_bss_34C90.b1DA == 0) {
            fn_3_5A6D4(5);
            started = 1;
            g_Minigame[0x1A38] = 1;
        } else if (lbl_3_common_bss_34C90.b1DA == 1) {
            g_Minigame[0x19DF] = 0x1E;
            fn_3_5A6D4(0x1D);
            started = 1;
        }
        if (started != 0) {
            fn_3_DF8D4();
            fn_3_15F998();
            fn_3_147DFC();
            if (lbl_3_common_bss_34C90.b1DA == 1) {
                fn_3_11CF84();
            }
        }
        break;
    case 9:
        switch (fn_3_5B380(((u16*)(g_Controls + 6))[lbl_3_common_bss_34C90.w0 * 8])) {
        case 1:
            fn_3_15F998();
            fn_3_147DFC();
            *(u16*)(g_GameLogic + 0xFE) = 0;
            lbl_3_common_bss_34C90.b1D2 = 10;
            break;
        case 2:
            lbl_3_common_bss_34C90.b1D2 = 3;
            break;
        }
        break;
    case 10:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            lbl_3_common_bss_34C90.b1D9 = 2;
            fn_8004CC18();
            g_GameLogic[0x122] = 1;
        }
        break;
    }
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void fn_3_DCA68(void) {
    SC* p = (SC*)&lbl_3_common_bss_34C90;
    u16 b = p->b6;
    if (b & 0x1000) {
        p->b1D2 = 4;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }
    if (b & 0x100) {
        if (p->b1DA == 0) {
            p->b1D2 = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (p->b1DA == 1) {
            p->b1D2 = 8;
            p->b1D4 = 0;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (p->b1DA == 2) {
            p->b1D2 = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
        if (p->b1DA == 3) {
            fn_3_5B408();
            ((SC*)&lbl_3_common_bss_34C90)->b1D2 = 9;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            return;
        }
    } else {
        if (b & 0x200) {
            if (p->b1DA != 0) {
                p->b1DA = 0;
            } else {
                p->b1D2 = 4;
            }
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            return;
        }
        if (p->b8 & 8) {
            u8 t = p->b1DA;
            if ((s8)t > 0) {
                p->b1DA = t - 1;
            } else {
                p->b1DA = 3;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            return;
        }
        if (p->b8 & 4) {
            u8 t = p->b1DA + 1;
            p->b1DA = t;
            if ((s8)t >= 4) {
                p->b1DA = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    }
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void fn_3_DCC80(void) {
    if (lbl_3_common_bss_34C90.n < 0x7FFE) {
        lbl_3_common_bss_34C90.n++;
    } else {
        lbl_3_common_bss_34C90.n = 0x7FFF;
    }
    if (lbl_3_common_bss_34C90.w12 < 0x7FFE) {
        lbl_3_common_bss_34C90.w12 = lbl_3_common_bss_34C90.w12 + 1;
    } else {
        lbl_3_common_bss_34C90.w12 = 0x7FFF;
    }
    {
        lbl_803CBC3C = 1;
        lbl_3_common_bss_34C90.w4 = ((u16*)(g_Controls + 4))[lbl_3_common_bss_34C90.w0 * 8];
        lbl_3_common_bss_34C90.w6 = ((u16*)(g_Controls + 6))[lbl_3_common_bss_34C90.w0 * 8];
        lbl_3_common_bss_34C90.w8 = ((u16*)(g_Controls + 8))[lbl_3_common_bss_34C90.w0 * 8];
    }
    switch (lbl_3_common_bss_34C90.b1D2) {
    case 0:
        lbl_3_common_bss_34C90.b1DA = 0;
        lbl_3_common_bss_34C90.b1D5 = 0;
        lbl_3_common_bss_34C90.b1D0 = 0x11;
        lbl_3_common_bss_34C90.b1D2 = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90.w12 = 0;
        lbl_3_common_bss_34C90.b1D2 = 2;
        break;
    case 2:
        if (lbl_3_common_bss_34C90.w12 >= 0x14) {
            lbl_3_common_bss_34C90.b1D2 = 3;
        }
        break;
    case 3:
        fn_3_DCA68();
        lbl_3_common_bss_34C90.w12 = 0;
        break;
    case 4:
        lbl_3_common_bss_34C90.b1D9 = 1;
        lbl_3_common_bss_34C90.b1D2 = 5;
        break;
    case 5:
        if (lbl_3_common_bss_34C90.b1D9 == 3) {
            fn_3_5A6D4(1);
        }
        break;
    case 6:
        lbl_3_common_bss_34C90.b1D9 = 1;
        lbl_3_common_bss_34C90.b1D2 = 7;
        break;
    case 7:
        if (lbl_3_common_bss_34C90.b1D9 == 3) {
            lbl_3_common_bss_34C90.b220 = 2;
            lbl_3_common_bss_34C90.b1D2 = 0;
            fn_3_5A6D4(0xD);
        }
        break;
    case 8:
        fn_3_107E80();
        break;
    case 9:
        switch (fn_3_5B380(lbl_3_common_bss_34C90.w6)) {
        case 1:
            *(u16*)(g_GameLogic + 0xFE) = 0;
            lbl_3_common_bss_34C90.b1D2 = 10;
            break;
        case 2:
            lbl_3_common_bss_34C90.b1D2 = 3;
            break;
        }
        break;
    case 10:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            lbl_3_common_bss_34C90.b1D9 = 2;
            g_d_GameSettings[0x13] = 1;
            fn_8004CC18();
            g_GameLogic[0x122] = 1;
        }
        break;
    }
}

// .text:0x000DCED0 size:0x74 mapped:0x8071BF64
void fn_3_DCED0(void) {
    s16* p = &lbl_3_common_bss_34C90.n;
    if (*p < 0x7FFE) {
        *p += 1;
    } else {
        *p = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (*p > 0x3C) {
        fn_3_AFD80(1);
        fn_3_5A6D4(0xB);
        return;
    }
    fn_3_2EA24();
}

// 21 diff lines: reg alloc (r3/r0 for s8 temp, lbl base order)
// .text:0x000DCF44 size:0xBC mapped:0x8071BFD8
void fn_3_DCF44(void) {
    s32 i;
    for (i = 0; i < ((SMX*)g_Minigame)->n; i++) {
        if (((SMX*)g_Minigame)->a[i] >= 0 && ((SMX*)g_Minigame)->b[i] == 0 && (*(u16*)(g_Controls + ((SMX*)g_Minigame)->a[i] * 0x10 + 6) & 0x1000)) {
            lbl_3_common_bss_34C90.b1D5 = 1;
            ((SLB*)&lbl_3_common_bss_34C90)->a = ((SMX*)g_Minigame)->a[i];
            fn_3_AFD80(0);
            fn_3_59918(0xE, 0);
            return;
        }
    }
}

// .text:0x000DD000 size:0x1A8 mapped:0x8071C094
void fn_3_DD000(void) {
    u8* gl = g_GameLogic;
    switch (gl[0x125]) {
    case 0:
        changeScene(1, 6);
        gl[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(gl + 0xFC) > 0x708) {
            gl[0x125] = 2;
            *(s16*)(gl + 0xFE) = 0;
        } else if (*(u16*)(gl + 0xFC) > 0x12C && fn_3_6C938(1, 0x1100) != 0) {
            gl[0x125] = 2;
            *(s16*)(g_GameLogic + 0xFE) = 0;
        }
        break;
    case 2:
        if (*(u16*)(gl + 0xFE) > 0x1E) {
            if (g_Minigame[0x190A] != 0) {
                gl[0x125] = 4;
            } else {
                gl[0x125] = 3;
            }
        }
        break;
    case 3:
        ((u8*)&lbl_3_common_bss_34C90)[0x1D1] = 0;
        ((u8*)&lbl_3_common_bss_34C90)[0x1D2] = 0;
        fn_3_5A6D4(0x22);
        break;
    case 4:
        changeScene(4, 6);
        if (lbl_8037169C[0x13] != 0) {
            gl[0x125] = 0xA;
        }
        break;
    case 5:
        if (g_Minigame[0x19A8] != 0) {
            g_d_GameSettings[0x38] = 0;
        } else {
            g_d_GameSettings[0x38] = g_Minigame[g_d_GameSettings[0x35] + 0x18E8];
        }
        g_GameLogic[0x122] = 1;
        break;
    }
}

// .text:0x000DD1A8 size:0x1D4 mapped:0x8071C23C
void fn_3_DD1A8(void) {
    u8* gl = g_GameLogic;
    s32 done;
    switch (gl[0x125]) {
    case 0: {
        if (*(s16*)(g_Minigame + 0x19B6) == 0) {
            if (random_fn_3_9EE24(100) < *(s16*)(lbl_3_data_18C48 + 0xE) || g_Minigame[0x1907] == 4) {
                s32 n = 0;
                int pl;
            loopA:
                pl = random_fn_3_9EE24(4);
                n++;
                *(s8*)(g_Minigame + 0x1905) = pl;
                if (n < 100) {
                    if (((SM*)g_Minigame)->f18D8[(s8)(u8)pl] != 0) {
                        goto loopA;
                    }
                }
            } else {
                s32 n = 0;
                int pl;
            loopB:
                pl = random_fn_3_9EE24(4);
                n++;
                *(s8*)(g_Minigame + 0x1905) = pl;
                if (n < 100) {
                    if (((SM*)g_Minigame)->f18D8[(s8)(u8)pl] == 0) {
                        goto loopB;
                    }
                }
            }
        }
        changeScene(1, 6);
        *(s16*)(g_GameLogic + 0xFE) = 0;
        gl[0x125] = 1;
        break;
    }
    case 1: {
        s32 t = *(u16*)(gl + 0xFC);
        done = 0;
        if (t >= *(s16*)(lbl_3_data_18C48 + 4)) {
            done = 1;
        } else if (*(u16*)(gl + 0xFE) >= *(s16*)(lbl_3_data_18C48 + 2) && fn_3_6C938(1, 0x1100) != 0) {
            done = 1;
        }
        if (done != 0) {
            gl[0x125] = 2;
            changeScene(3, 6);
        }
        break;
    }
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(7);
        }
        break;
    }
}

// .text:0x000DD37C size:0x80 mapped:0x8071C410
void fn_3_DD37C(void) {
    if (g_Minigame[0x19CE] != 0) {
        fn_3_FBD70();
        fn_3_FBD58();
    }
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    fn_3_1DD48(g_GameLogic);
    if (g_Minigame[0x1912] == 0) {
        fn_3_2E87C();
        fn_3_5A6D4(0);
        return;
    }
    fn_3_5A6D4(8);
}

// NONMATCHING: original reaches lbl_3_data_1899C/18BB8/18C48 through the pooled base lbl_3_data_188E8 (data defined in this TU), so base registers and stmw differ
// .text:0x000DD3FC size:0x5A8 mapped:0x8071C490
#if NONMATCHING
void fn_3_DD3FC(void) {
    s16* timer = (s16*)(g_GameLogic + 0x100);
    s32 i;

    if (g_Minigame[0x190B] == 1) {
        g_Minigame[0x190B] = 2;
        *timer = *(s16*)lbl_3_data_1899C;
        if (g_Minigame[0x1920] == 1 && g_Ball[0x1BD3] == 0) {
            *timer = *(s16*)(lbl_3_data_1899C + 4);
        }
    }
    *timer -= 1;
    if (g_Minigame[0x19A0] != 0 && g_Minigame[0x19CE] == 0 && *timer < *(s16*)(lbl_3_data_1899C + 2)) {
        *timer = *(s16*)(lbl_3_data_1899C + 2);
    }
    if (g_Minigame[0x1939] != 0 && *timer < *(s16*)(lbl_3_data_1899C + 2)) {
        *timer = *(s16*)(lbl_3_data_1899C + 2);
    }
    if (g_Minigame[0x19CE] != 0 && g_Minigame[0x19CE] < 3) {
        if (*timer <= *(s16*)(lbl_3_data_1899C + 2) - 0xA) {
            *timer += 1;
        }
        if (g_Minigame[0x19CE] == 1) {
            fn_3_DE308(0xC);
            *(s16*)(g_Minigame + 0x19BA) = 0;
            g_Minigame[0x19CE] = 2;
            for (i = 0; i < 4; i++) {
                if (g_Minigame[0x1918 + i] != 0) {
                    g_Minigame[0x1914 + i] = 0;
                }
            }
            if (lbl_800EF808[0x398] == 1) {
                playCrowdSound(0x1A);
            }
        }
        if (*(s16*)(g_Minigame + 0x19BA) < 0x7FFE) {
            *(s16*)(g_Minigame + 0x19BA) += 1;
        } else {
            *(s16*)(g_Minigame + 0x19BA) = 0x7FFF;
        }
        if (*(s16*)(g_Minigame + 0x19BA) > *(s16*)(lbl_3_data_18C48 + 6)) {
            g_Minigame[0x19CE] = 3;
        }
    }
    if (g_Minigame[0x19A4] == 0 && *(s16*)(g_Ball + 0x1B78) < 0 && g_Ball[0x1BD1] == 0 && *(s16*)(g_Ball + 0x1B7A) >= 0 &&
        *timer <= *(s16*)(lbl_3_data_1899C + 2) + lbl_3_data_49DC[0x16 / 2] - 0xA) {
        *timer += 1;
    }
    if (*timer == *(s16*)(lbl_3_data_1899C + 2) - 0xA) {
        u8 st = g_Minigame[0x19CD];
        if (st == 1 || st == 2 || (st != 3 && g_Minigame[0x1921] != 0)) {
            *timer += 1;
        } else if (*(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4) && g_Minigame[(s8)g_Minigame[0x1905] + 0x18E8] == 1) {
            fn_3_59918(0xD, 0);
        } else if ((s32)g_Minigame[0x1905] != (s8)g_Minigame[0x19C6]) {
            if (*(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4)) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
        if (*(s16*)(g_Minigame + 0x19BC) < 0x7FFE) {
            *(s16*)(g_Minigame + 0x19BC) += 1;
        } else {
            *(s16*)(g_Minigame + 0x19BC) = 0x7FFF;
        }
    }
    if (*timer == 7) {
        changeScene(3, 6);
    }
    if (*timer <= 0) {
        if (g_Minigame[0x19CE] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
        }
        g_GameLogic[0x12B] = 1;
        g_GameLogic[0x12C] = 1;
        g_GameLogic[0x12E] = 1;
        fn_3_1DD48(g_GameLogic);
        if (g_Minigame[0x1912] == 0) {
            fn_3_2E87C();
            fn_3_5A6D4(0);
            return;
        }
        fn_3_5A6D4(8);
    }
}
#endif

// .text:0x000DD9A4 size:0x3BC mapped:0x8071CA38
void fn_3_DD9A4(void) {
    if (*(s16*)(g_Minigame + 0x19B8) != 0 && *(s16*)(g_Ball + 0x1B78) < 0) {
        if (*(s16*)(g_Minigame + 0x19B8) < *(s16*)(lbl_3_data_18C48 + 0xC)) {
            *(s16*)(g_Minigame + 0x19B8) += 1;
        } else if (g_Minigame[0x19A4] == 0) {
            g_Minigame[0x19A4] = 1;
            playCrowdSound(0x15);
        }
    }
    ballPhysica();
    fn_3_2F484();
    if (g_Minigame[0x19CF] != 0) {
        if (g_Minigame[0x19CE] == 0) {
            fn_3_DC240();
        }
    } else if (g_Minigame[0x19C9] != 0 && g_Minigame[0x1920] == 0) {
        fn_3_DC240();
    } else if (g_Minigame[0x1920] == 0) {
        fn_3_DC380();
    }
    if (g_Minigame[0x1920] != 0) {
        fn_3_DA834();
    }
    if (g_Minigame[0x190B] != 0) {
        fn_3_DD3FC();
    }
}

// .text:0x000DDD60 size:0x1BC mapped:0x8071CDF4
void fn_3_DDD60(void) {
    if (g_Minigame[0x190B] == 1) {
        g_Minigame[0x190B] = 2;
        *(s16*)(g_GameLogic + 0x100) = *(s16*)lbl_3_data_1899C;
    }
    *(s16*)(g_GameLogic + 0x100) -= 1;
    if (g_Minigame[0x19A0] != 0 && *(s16*)(g_GameLogic + 0x100) < *(s16*)(lbl_3_data_1899C + 2)) {
        *(s16*)(g_GameLogic + 0x100) = *(s16*)(lbl_3_data_1899C + 2);
    }
    if (*(s16*)(g_GameLogic + 0x100) == *(s16*)(lbl_3_data_1899C + 2) - 0xA) {
        if (*(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4) && g_Minigame[(s8)g_Minigame[0x1905] + 0x18E8] == 1) {
            fn_3_59918(0xD, 0);
        } else if ((s32)g_Minigame[0x1905] != (s8)g_Minigame[0x19C6]) {
            if (*(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4)) {
                fn_3_59918(0xD, 0);
            } else {
                fn_3_59918(5, 0);
            }
        }
    }
    if (*(s16*)(g_GameLogic + 0x100) == 7) {
        changeScene(3, 6);
    }
    if (*(s16*)(g_GameLogic + 0x100) <= 0) {
        if (g_Minigame[0x19CE] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
        }
        g_GameLogic[0x12B] = 1;
        g_GameLogic[0x12C] = 1;
        g_GameLogic[0x12E] = 1;
        fn_3_1DD48(g_GameLogic);
        if (g_Minigame[0x1912] == 0) {
            fn_3_2E87C();
            fn_3_5A6D4(0);
            return;
        }
        fn_3_5A6D4(8);
    }
}

// .text:0x000DDF1C size:0x84 mapped:0x8071CFB0
void fn_3_DDF1C(void) {
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_58870();
    fn_3_1DEB8();
    fn_3_BF1AC();
    Set_803cb848(1);
    fn_3_BF158();
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    g_GameLogic[0x126] = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
}

// .text:0x000DDFA0 size:0x368 mapped:0x8071D034
void fn_3_DDFA0(void) {
    if (*(s16*)(g_Pitcher + 0x11E) <= 0 && lbl_3_common_bss_34C90.b1D5 == 0) {
        fn_3_DCF44();
    }
    if (lbl_3_common_bss_34C90.b1D5 != 0) {
        fn_3_DCED0();
        return;
    }
    fn_3_75560();
    atBat_batter();
    fn_3_2EA24();
    if (g_Minigame[0x1920] == 0 && g_Pitcher[0x14E] != 0) {
        if (g_Pitcher[0x14E] == 1) {
            g_Minigame[0x1920] = 2;
        } else if (g_Pitcher[0x14E] == 2) {
            g_Minigame[0x1920] = 7;
        } else {
            g_Minigame[0x1920] = 8;
        }
    }
    if (g_Minigame[0x1920] != 0) {
        fn_3_DA834();
    }
    if (g_Minigame[0x190B] != 0) {
        if (g_Minigame[0x190B] == 1) {
            g_Minigame[0x190B] = 2;
            *(s16*)(g_GameLogic + 0x100) = *(s16*)lbl_3_data_1899C;
        }
        *(s16*)(g_GameLogic + 0x100) -= 1;
        if (g_Minigame[0x19A0] != 0 && *(s16*)(g_GameLogic + 0x100) < *(s16*)(lbl_3_data_1899C + 2)) {
            *(s16*)(g_GameLogic + 0x100) = *(s16*)(lbl_3_data_1899C + 2);
        }
        if (*(s16*)(g_GameLogic + 0x100) == *(s16*)(lbl_3_data_1899C + 2) - 0xA) {
            if (*(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4) && g_Minigame[(s8)g_Minigame[0x1905] + 0x18E8] == 1) {
                fn_3_59918(0xD, 0);
            } else if ((s32)g_Minigame[0x1905] != (s8)g_Minigame[0x19C6]) {
                if (*(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4)) {
                    fn_3_59918(0xD, 0);
                } else {
                    fn_3_59918(5, 0);
                }
            }
        }
        if (*(s16*)(g_GameLogic + 0x100) == 7) {
            changeScene(3, 6);
        }
        if (*(s16*)(g_GameLogic + 0x100) <= 0) {
            if (g_Minigame[0x19CE] != 0) {
                fn_3_FBD70();
                fn_3_FBD58();
            }
            g_GameLogic[0x12B] = 1;
            g_GameLogic[0x12C] = 1;
            g_GameLogic[0x12E] = 1;
            fn_3_1DD48(g_GameLogic);
            if (g_Minigame[0x1912] == 0) {
                fn_3_2E87C();
                fn_3_5A6D4(0);
                return;
            }
            fn_3_5A6D4(8);
        }
    }
}

typedef struct { s16 a, b, c; } T18BB8;
extern T18BB8 lbl_3_data_18BB8[];

typedef struct {
    /* 0x0000 */ u8 pad0[0x1890];
    /* 0x1890 */ s16 a[4];
    /* 0x1898 */ s16 score[4];
    /* 0x18A0 */ u8 pad1[0x1C];
    /* 0x18BC */ s16 out[4][2];
} T28A8;

#define MG ((T28A8*)g_Minigame)

// .text:0x000DE308 size:0x1F4 mapped:0x8071D39C
void fn_3_DE308(s32 idx) {
    s32 i;

    if (idx == 0x14 || idx == 0x15) {
        s16* sc = (s16*)(g_Minigame + 0x1898);
        sc[(s8)g_Minigame[0x1905]] += g_Minigame[0x19CB] * lbl_3_data_18BB8[idx].a;
        sc[(s8)g_Minigame[0x1904]] += g_Minigame[0x19CB] * lbl_3_data_18BB8[idx].b;
        *(s16*)(g_Minigame + g_Fielders[*(s16*)(g_Ball + 0x1B78) * 0x268 + 0x20D] * 2 + 0x1898) +=
            g_Minigame[0x19CB] * lbl_3_data_18BB8[idx].c;
    } else {
        s16* sc;
        s16 v2;
        sc = (s16*)(g_Minigame + 0x1898);
        sc[(s8)g_Minigame[0x1905]] += g_Minigame[0x19CB] * lbl_3_data_18BB8[idx].a;
        v2 = lbl_3_data_18BB8[idx].c;
        sc[(s8)g_Minigame[0x1904]] += g_Minigame[0x19CB] * lbl_3_data_18BB8[idx].b;
        sc[(s8)g_Minigame[0x18F5]] += g_Minigame[0x19CB] * v2;
        sc[(s8)g_Minigame[0x18F6]] += g_Minigame[0x19CB] * v2;
    }
    for (i = 0; i < 4; i++) {
        if (MG->score[i] != 0) {
            MG->out[i][0] = MG->a[i];
            MG->out[i][1] = MG->score[i];
        }
    }
}

// .text:0x000DE4FC size:0x114 mapped:0x8071D590
void fn_3_DE4FC(void) {
    s32 i;
    s32 j;
    s16 score;
    s32 rank;
    s32 n;

    g_Minigame[0x18E8] = 0;
    g_Minigame[0x18EC] = 0;
    g_Minigame[0x18E9] = 0;
    g_Minigame[0x18ED] = 0;
    g_Minigame[0x18EA] = 0;
    g_Minigame[0x18EE] = 0;
    g_Minigame[0x18EB] = 0;
    g_Minigame[0x18EF] = 0;
    for (i = 0; i < g_Minigame[0x1906]; i++) {
        rank = 1;
        score = *(s16*)(g_Minigame + 0x1890 + i * 2);
        for (j = 0; j < g_Minigame[0x1906]; j++) {
            if (*(s16*)(g_Minigame + 0x1890 + j * 2) > score) {
                rank++;
            }
        }
        g_Minigame[0x18E8 + i] = rank;
        g_Minigame[0x18EC + i] = rank;
    }
    for (n = 0; n < 4; n++) {
        if (g_Minigame[0x18E8 + n] > 1) {
            break;
        }
    }
    if (n >= 4 && g_Minigame[0x1906] > 1) {
        g_Minigame[0x19A8] = 1;
    } else {
        g_Minigame[0x19A8] = 0;
    }
}

// .text:0x000DE610 size:0x134 mapped:0x8071D6A4
extern u8 g_Pitcher[];
extern s32 g_Strikes[];

void fn_3_DE610(void) {
    g_Minigame[0x199F] = 0;
    if (g_Minigame[0x19A6] != 0) {
        g_Minigame[0x19A6]--;
        if (g_Pitcher[0x14E] == 2 || g_Pitcher[0x14E] == 3) {
            g_Minigame[0x19A6] = 3;
        }
    }
    g_Strikes[2] = 0;
    g_Strikes[3] = 0;
    g_Minigame[0x19A5] = 1;
    if (((s8)g_Minigame[0x1905] != (s8)g_Minigame[0x19C6] || g_Minigame[0x18E8 + (s8)g_Minigame[0x1905]] == 1) &&
        *(s16*)(g_Minigame + 0x19B6) >= *(s16*)(g_Minigame + 0x19B4)) {
        lbl_3_common_bss_34C90.b1D2 = 0;
        fn_3_5A6D4(0xE);
        return;
    }
    if (*(s16*)(g_Minigame + 0x19B6) < *(s16*)(g_Minigame + 0x19B4) && (*(s16*)(g_Minigame + 0x19B6) % 10) == 0) {
        fn_3_5A6D4(3);
        return;
    }
    fn_3_5A6D4(7);
}

// .text:0x000DE744 size:0x44C mapped:0x8071D7D8
typedef struct { u8 pad[0x1914]; u8 active[4]; u8 active2[4]; s8 slot[4]; } SMQ;
extern u8 g_Runners[];
extern u8 g_Batter[];
extern u8 g_Scores[];
extern u8 g_RunningLogic[];
extern void fn_3_6C0E0(void);
extern void fn_3_E67F4(void);

void fn_3_DE744(void) {
    s32 i;

    fn_3_DDF1C();
    fn_3_6C0E0();
    *(f32*)(g_Runners + 0xC) = *(f32*)(g_Runners + 0x0);
    *(f32*)(g_Runners + 0x10) = *(f32*)(g_Runners + 0x4);
    *(f32*)(g_Runners + 0x14) = *(f32*)(g_Runners + 0x8);
    g_Runners[0x12A] = 1;
    g_Runners[0x11C] = g_Batter[0x7B];
    g_Runners[0x129] = 1;
    *(f32*)(g_Runners + 0x0) = *(f32*)(g_Batter + 0x0);
    *(f32*)(g_Runners + 0x4) = 0.0f;
    *(f32*)(g_Runners + 0x8) = *(f32*)(g_Batter + 0x4);
    *(f32*)(g_Runners + 0x30) = 3.1415927f;
    *(s16*)(g_GameLogic + 0x100) = 10000;
    g_Strikes[3] = g_Strikes[2];
    g_Strikes[2] = 0;
    g_Strikes[3] = 0;
    *(s16*)(g_Ball + 0x1B64) = 0;
    lbl_3_common_bss_34C90.b1D5 = 0;
    g_Scores[0xC5] = 0;
    g_Minigame[0x190B] = 0;
    g_Minigame[0x1912] = 0;
    g_Minigame[0x1920] = 0;
    *(s16*)(g_Minigame + 0x18AA) = 0;
    g_Minigame[0x1921] = 0;
    g_Minigame[0x1914] = 1;
    g_Minigame[0x1926] = 0;
    g_Minigame[0x1939] = 0;
    g_Minigame[0x199F] = 0;
    g_Minigame[0x19A0] = 0;
    g_Minigame[0x1934] = 0;
    *(s16*)(g_Minigame + 0x18BA) = 0;
    g_Minigame[0x19A3] = 0;
    *(s16*)(g_Minigame + 0x19B8) = 0;
    g_Minigame[0x19A4] = 0;
    g_Minigame[0x190E] = 0;
    g_Minigame[0x19C8] = 0;
    g_Minigame[0x19C9] = 0;
    *(s16*)(g_Minigame + 0x19BC) = 0;
    g_Minigame[0x19D0] = 0;
    g_Minigame[0x19CD] = 0;
    g_Minigame[0x19CF] = 0;
    if (g_Minigame[0x19CE] == 3) {
        fn_3_E67F4();
    }
    g_Minigame[0x19CE] = 0;
    for (i = 0; i < 4; i++) {
        MG->out[i][0] = MG->a[i];
        MG->out[i][1] = 0;
        ((s8*)g_Minigame)[0x1935 + i] = -1;
    }
    for (i = 0; i < 100; i++) {
        g_Minigame[0x193A + i] = 0;
    }
    for (i = 0; i < 4; i++) {
        if (((SMQ*)g_Minigame)->active[i] != 0) {
            ((SMQ*)g_Minigame)->slot[i] = i;
        } else {
            ((SMQ*)g_Minigame)->slot[i] = -1;
        }
        ((SMQ*)g_Minigame)->active2[i] = ((SMQ*)g_Minigame)->active[i];
    }
    g_FieldingLogic[0x10E] = 0;
    *(s16*)(g_FieldingLogic + 0xEE) = 0;
    g_FieldingLogic[0x10F] = 0;
    g_FieldingLogic[0x110] = 0;
    g_FieldingLogic[0x128] = 0;
    g_FieldingLogic[0x129] = 0;
    *(s16*)(g_FieldingLogic + 0xE4) = 0;
    g_RunningLogic[0x13] = 0;
    if (g_GameLogic[0x12B] != 0) {
        g_GameLogic[0x12C] = 1;
        g_GameLogic[0x12D] = 1;
    } else {
        g_GameLogic[0x12C] = 0;
    }
    g_GameLogic[0x12B] = 0;
    changeScene(1, 6);
    fn_3_5A6D4(1);
}
