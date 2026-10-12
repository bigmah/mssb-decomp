#include "game/rep_31F0.h"
#include "header_rep_data.h"

#include "musyx/musyx.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"
#include "game/rep_1E08.h"
extern u8 lbl_800EFBA4[];

extern void setInMemBatterConstants(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_8913C(void);
extern void fn_3_58870(void);
extern void fn_3_BF1AC(void);
extern void Set_803cb848(s32);
extern void* memset(void*, s32, u32);
extern u8 g_Minigame[];
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];

extern void fn_3_5A6D4(s32);
extern u8 g_Runners[];
extern u8 g_Ball[];
extern u8 lbl_3_common_bss_32220[];
extern f32 lbl_3_rodata_3268;
extern f32 lbl_3_rodata_324C;
extern f32 lbl_3_rodata_3250;
extern f32 lbl_3_rodata_3254;
extern f32 shortAngleToRad(s16);
extern u8 g_Scores[];
extern void fn_3_10AD48(void);
extern void fn_3_10F550(s32, s32);
extern u8 lbl_3_common_bss_32724[];
extern u8 g_GameLogic[];
extern void fn_8003A540(u32 value);
extern void fn_3_DE4FC(void);
extern void fn_3_155288(void);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern int rand();
extern u8 lbl_3_data_21448[];
extern u8 lbl_3_data_217A4[];
extern u8 lbl_3_data_2139C[];
extern u8 lbl_3_data_213A4[];
extern u8 g_Pitcher[];
extern int RandomIndexFromWeights(u8* weights, int count);
extern void fn_3_750C4(u8);
extern u8 lbl_3_data_21448[];
extern u8 g_Pitcher[];
extern void changeScene(s32, s32);
extern u8 lbl_3_data_18C48[];
extern u8 lbl_8037169C[];
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void changeScene(s32, s32);

// .text:0x00110634 size:0x3D0 mapped:0x8074F6C8
extern s32 fn_3_9E368(s32* weights, s32 n);
extern int RandomInt_Game_Range(int min, int max);
extern u8 g_Batter[];
extern s16 g_hitShorts[];
extern u8 swingSoundFrame[2][4];
extern u8 lbl_3_data_21488[][3];
extern s8 lbl_3_data_214A0[][3][2];
extern s8 lbl_3_data_214B8[][3];
extern s8 lbl_3_data_214C4[][3];
extern s8 lbl_3_data_214D0[][3];
extern s8 lbl_3_data_214DC[][3];
extern s8 lbl_3_data_214E8[][3];
extern s8 lbl_3_data_214F4[][3];

// NONMATCHING 92%: the first weight loop hoists g_Minigame+0x1ACC (lbzx) and allocates the table walkers differently
#if NONMATCHING
static inline void calcWeights_31F0(s32* w, u8* base, s8* streak, s8* special, s8* bonus) {
    s8 i = 0;
    u8 streakCnt = (g_Minigame + 0x1ACC)[*(s8*)(g_Minigame + 0x1905) * 2];
    do {
        w[i] = base[i];
        w[i] += streakCnt * streak[i];
        if (g_Minigame[0x1DF6] != 0) {
            w[i] += special[i];
        } else if (g_Minigame[0x1AD5] != 0) {
            w[i] += bonus[i];
        }
        if (w[i] < 0) {
            w[i] = 0;
        }
        i++;
    } while (i < 3);
}

void fn_3_110634(void) {
    s32 zone[3];
    s32 timing[3];
    s32 k;
    s16 frame;
    u8* mg = g_Minigame;
    u8 type = mg[0x18DC + *(s8*)(mg + 0x1905)];
    calcWeights_31F0(zone, lbl_3_data_21488[type], lbl_3_data_214B8[type], lbl_3_data_214E8[type], lbl_3_data_214D0[type]);
    calcWeights_31F0(timing, lbl_3_data_21488[type], lbl_3_data_214C4[type], lbl_3_data_214F4[type], lbl_3_data_214DC[type]);
    frame = g_hitShorts[1];
    switch (fn_3_9E368(zone, 3)) {
    case 0:
    default:
        frame = frame + RandomInt_Game_Range(3, *(s16*)(g_Batter + 0x70) - 3);
        break;
    case 1:
        frame = *(s16*)(g_Batter + 0x70) +
                (RandomInt_Game_Range(3, *(s16*)(g_Batter + 0x72) - *(s16*)(g_Batter + 0x70) - 3) + frame);
        break;
    case 2:
        frame = *(s16*)(g_Batter + 0x72) + (RandomInt_Game_Range(3, g_hitShorts[0]) + frame);
        break;
    }
    k = fn_3_9E368(timing, 3);
    *(s16*)(mg + 0x1DCE) =
        swingSoundFrame[1][k] + RandomInt_Game_Range(lbl_3_data_214A0[type][k][0], lbl_3_data_214A0[type][k][1]);
    *(s16*)(mg + 0x1DCC) = frame - (fn_3_110A38() - *(s16*)(mg + 0x1DCE));
    if (*(s16*)(mg + 0x1DCC) < g_hitShorts[1] + 1) {
        *(s16*)(mg + 0x1DCC) = g_hitShorts[1] + 1;
    }
}
#endif

// .text:0x00110A04 size:0x34 mapped:0x8074FA98
void fn_3_110A04(void) {
    memset(g_Minigame + 0x1D7C, 0, 0x78);
}

// .text:0x00110A38 size:0x9C mapped:0x8074FACC
s32 fn_3_110A38(void) {
    if (g_Pitcher[0x164] != 0) {
        switch (g_Pitcher[0x165]) {
        case 1:
            return 20;
        }
        return 20;
    }
    return (s32)(lbl_3_rodata_3250 * ((f32)g_Minigame[0x1ACA] - lbl_3_rodata_3254) + lbl_3_rodata_324C);
}

// .text:0x00110AD4 size:0x564 mapped:0x8074FB68
extern s16 fn_3_9FB8C(f32 x, f32 y);
extern void getComponentsFromSAng(s16 ang, f32* x, f32* y);
extern camera_803c639c_s* fn_80052768_getCamera(int index);
extern u8 lbl_3_data_213E0[4];
extern f32 lbl_3_data_21438[];

// g_Minigame +0x1AA0: last 10 hit results per roster slot
typedef struct { u8 pad[0x1AA0]; u8 hist[4][10]; } MgHist_31F0;

// Arms the first free slot of the 10 explosion timers at g_Minigame+0x1A96.
static inline void startBombTimer_31F0(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        if (g_Minigame[0x1A96 + i] == 0) {
            g_Minigame[0x1A96 + i] = *(s16*)(lbl_3_data_21448 + 0x10);
            return;
        }
    }
}

void fn_3_110AD4(void) {
    f32 cosB;
    Vec v;
    s32 i;
    s32 angA;
    s32 angB;
    u8* mg = g_Minigame;
    if (mg[0x1AD4] == 0) {
        for (i = 9; i > 0; i--) {
            (g_Minigame + *(s8*)(g_Minigame + 0x1905) * 10)[i + 0x1AA0] = (g_Minigame + *(s8*)(g_Minigame + 0x1905) * 10)[i + 0x1A9F];
        }
        ((MgHist_31F0*)g_Minigame)->hist[*(s8*)(mg + 0x1905)][0] = g_Minigame[0x1AD6];
        v.x = *(f32*)(g_Ball + 0x0);
        v.y = -*(f32*)(g_Ball + 0x4);
        v.z = *(f32*)(g_Ball + 0x8);
        *(s16*)(g_Minigame + 0x18A2) = fn_3_9FB8C(v.x, v.z);
        *(s16*)(g_Minigame + 0x18A4) = fn_3_9FB8C(*(f32*)(g_Ball + 0x1A00), -v.y);
        if (g_Pitcher[0x164] != 0) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(0, 3), 1);
        } else if (g_Minigame[0x1AD5] != 0) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, 13, 1);
        } else {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(8, 12), 1);
        }
        mg[0x1AD4] = 1;
        g_Minigame[0x1DF7] = 1;
        *(u16*)(g_Minigame + 0x18A0) = 1;
        *(s16*)(g_Minigame + 0x18A6) = RandomInt_Game_Range(lbl_3_data_213E0[0], lbl_3_data_213E0[1]);
        if (g_Pitcher[0x164] != 0) {
            *(s16*)(g_Minigame + 0x18A8) = 0;
        } else if (g_Minigame[0x1ACC + *(s8*)(mg + 0x1905) * 2] <= 1 || g_Minigame[0x1AD5] != 0) {
            *(s16*)(g_Minigame + 0x18A8) = 1;
            g_Minigame[0x1DF8] = 1;
        } else {
            *(s16*)(g_Minigame + 0x18A8) = 0;
        }
        fn_3_155288();
        startBombTimer_31F0();
    } else if (*(s16*)(mg + 0x18A8) == 0 && --*(s16*)(mg + 0x18A6) <= 0) {
        angA = rand() % *(s16*)(lbl_3_data_21448 + 0xA);
        if (rand() & 1) {
            angA = -angA;
        }
        angA += *(s16*)(g_Minigame + 0x18A2);
        angB = rand() % *(s16*)(lbl_3_data_21448 + 0xC);
        if (rand() & 1) {
            angB = -angB;
        }
        angB += *(s16*)(g_Minigame + 0x18A4);
        getComponentsFromSAng(angA, &v.x, &v.z);
        getComponentsFromSAng(angB, &cosB, &v.y);
        v.x *= lbl_3_data_21438[3];
        v.z *= lbl_3_data_21438[3];
        v.y = v.y / cosB;
        v.y = v.y * -lbl_3_data_21438[3];
        if (g_Pitcher[0x164] != 0) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(0, 3), 1);
        } else if (*(u16*)(g_Minigame + 0x18A0) & 1) {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(4, 7), 1);
        } else {
            fn_3_BC6D8(&v, &fn_80052768_getCamera(0)->eye, RandomInt_Game_Range(8, 12), 1);
        }
        *(s16*)(mg + 0x18A6) = RandomInt_Game_Range(lbl_3_data_213E0[2], lbl_3_data_213E0[3]);
        *(u16*)(g_Minigame + 0x18A0) += 1;
        if (g_Pitcher[0x164] != 0) {
            if (*(u16*)(g_Minigame + 0x18A0) >= 10) {
                *(s16*)(mg + 0x18A8) = 1;
                g_Minigame[0x1DF8] = 1;
            }
        } else if (*(u16*)(g_Minigame + 0x18A0) >= g_Minigame[0x1ACC + *(s8*)(g_Minigame + 0x1905) * 2] ||
                   *(u16*)(g_Minigame + 0x18A0) >= *(s16*)(lbl_3_data_21448 + 0xE)) {
            *(s16*)(mg + 0x18A8) = 1;
            g_Minigame[0x1DF8] = 1;
        }
        startBombTimer_31F0();
    }
}

extern u8 g_d_GameSettings[];
extern u8 lbl_3_common_bss_37400[];
extern u8 lbl_3_data_213EC[];
extern void fn_3_1608F0(s32, s32, u8);

// g_Minigame: Bomb-omb Derby fields
typedef struct {
    u8 pad0[0x1890];
    s16 curPoints[4];
    s16 latestPoints[4];
    u8 pad1[0x1905 - 0x18A0];
    s8 rosterID;
    u8 pad2[0x1A8E - 0x1906];
    s16 hitPower[4];
    u8 pad3[0x1ACC - 0x1A96];
    u8 hrStreak[8];
    u8 pad4;
    u8 kingBomb;
} MgBOD;

// .text:0x00111038 size:0x198 mapped:0x807500CC
void fn_3_111038(void) {
    MgBOD* mg = (MgBOD*)g_Minigame;
    s16 dist = *(s16*)(g_Ball + 0x1B9E);
    u8 cnt;
    s32 off;
    f32 f;
    (g_Minigame + 0x1ACC)[mg->rosterID * 2]++;
    if (mg->hitPower[mg->rosterID] < dist) {
        mg->hitPower[mg->rosterID] = dist;
    }
    f = dist;
    off = mg->rosterID * 2;
    cnt = (g_Minigame + 0x1ACC)[off];
    if (cnt > 1) {
        f += *(s16*)(lbl_3_data_213EC + 0x10) * cnt;
    }
    if (((MgBOD*)g_Minigame)->kingBomb != 0) {
        f += *(s16*)(lbl_3_data_213EC + 0xE);
    }
    *(s16*)((u8*)((MgBOD*)g_Minigame)->latestPoints + off) = f;
    ((MgBOD*)g_Minigame)->curPoints[mg->rosterID] += (s16)f;
    if (g_d_GameSettings[8] == 0 && mg->rosterID == *(s16*)(lbl_3_common_bss_37400 + 0x40)) {
        fn_3_1608F0(0, f, ((MgBOD*)g_Minigame)->kingBomb);
    }
}

// .text:0x001111D0 size:0x80 mapped:0x80750264
void fn_3_1111D0(void) {
    s32 a;
    u8* r = g_Runners;
    if (lbl_3_common_bss_32220[8] == 4) {
        a = *(s16*)(g_Ball + 0x1B9C);
        if (a < 0x200) {
            a = 0x200;
        }
        if (a > 0x600) {
            a = 0x600;
        }
        *(f32*)(r + 0x30) = -shortAngleToRad(a) - lbl_3_rodata_3268;
    }
}

// .text:0x00111250 size:0x64 mapped:0x807502E4
void fn_3_111250(void) {
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    fn_8003A540(0);
    if (g_Minigame[0x1912] == 1) {
        fn_3_5A6D4(8);
        return;
    }
    fn_3_5A6D4(0);
}

// .text:0x001112B4 size:0x484 mapped:0x80750348
void fn_3_1112B4(void) {
    u8* mg = g_Minigame;
    u8 st = mg[0x190B];
    u8 bd;
    if (st == 0) {
        if (g_Ball[0x1BD6] != 0) {
            *(s16*)(g_GameLogic + 0x100) = *(s16*)(lbl_3_data_21448 + 2);
            mg[0x190B] = 1;
            mg[0x1ACC + *(s8*)(mg + 0x1905) * 2] = 0;
        } else {
            bd = g_Ball[0x1BD1];
            if (bd != 0) {
                if (bd == 1) {
                    *(s16*)(g_GameLogic + 0x100) = *(s16*)(lbl_3_data_21448 + 4);
                    mg[0x1ACB]++;
                    fn_3_111038();
                } else {
                    *(s16*)(g_GameLogic + 0x100) = *(s16*)(lbl_3_data_21448 + 4);
                    mg[0x1ACC + *(s8*)(mg + 0x1905) * 2] = 0;
                }
                mg[0x190B] = 1;
            }
        }
    } else {
        if (st == 1) {
            mg[0x190B] = 2;
            if (mg[0x1909] == 0 && mg[0x1A2B] <= 2 &&
                ((MgBOD*)g_Minigame)->curPoints[((MgBOD*)g_Minigame)->rosterID] >= *(s16*)(g_Minigame + 0x1A26)) {
                mg[0x1912] = 1;
                mg[0x1A37] = 1;
                mg[0x19A8] = 0;
                fn_3_10F550(1, *(s16*)(lbl_3_data_21448 + 0x12));
            } else if (g_Minigame[0x1A2D] >= g_Minigame[0x1A2F]) {
                if (mg[0x1909] == 0 && g_Minigame[0x1A2B] == 3 && g_Ball[0x1BD1] == 1 && g_Minigame[0x1A2D] < 20) {
                    if (g_Minigame[0x1ACC + *(s8*)(g_Minigame + 0x1905) * 2] < g_Minigame[0x1A2D]) {
                        g_Minigame[0x1912] = 1;
                    }
                } else {
                    g_Minigame[0x1912] = 1;
                }
            }
        }
        if (*(s16*)(g_Minigame + 0x18A8) != 0 && g_Minigame[0x1A42] == 0) {
            *(s16*)(g_GameLogic + 0x100) -= 1;
            if (g_Minigame[0x1912] != 0 &&
                (g_Minigame[0x1909] == 0 ||
                 (g_Minigame[0x1909] != 0 && g_Minigame[0x190C] + 1 >= g_Minigame[0x1906] && *(s32*)g_Scores >= g_Scores[0xAA])) &&
                g_Minigame[0x1A37] == 0 && *(s16*)(g_GameLogic + 0x100) == 0x43) {
                sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
            }
            if (*(s16*)(g_GameLogic + 0x100) == 7) {
                changeScene(3, 6);
            }
            if (*(s16*)(g_GameLogic + 0x100) <= 0) {
                fn_3_111250();
            }
        }
    }
}

// .text:0x00111738 size:0x17C mapped:0x807507CC
extern void ballPhysica(void);
extern void fn_3_6C854(s32, s32);
extern void fn_3_8F21C(void);

// g_Minigame +0x18CC: minigameControlStruct[0].characterIndex[]
typedef struct { u8 pad[0x18CC]; s8 characterIndex[0x40]; } MgCI;

void fn_3_111738(void) {
    s32 i;
    ballPhysica();
    fn_3_1111D0();
    if (g_Ball[0x1BEE] != 0 && g_Ball[0x1BD1] == 1 &&
        (*(f32*)(g_Ball + 0x1A00) > lbl_3_data_21438[3] || g_Minigame[0x1AD4] != 0)) {
        ((void (*)(void))fn_3_110AD4)();
        g_Minigame[0x1AD7] = 1;
    }
    for (i = 0; i < 10; i++) {
        if (g_Minigame[0x1A96 + i] != 0) {
            g_Minigame[0x1A96 + i]--;
            if (g_Minigame[0x1A96 + i] == 0) {
                fn_3_6C854(((MgCI*)g_Minigame)->characterIndex[*(s8*)(g_Minigame + 0x1905)], 0);
            }
        }
    }
    if (g_Ball[0x1BD1] == 2) {
        g_Minigame[0x1AD7] = 1;
    }
    fn_3_8F21C();
    ((void (*)(void))fn_3_1112B4)();
}

// .text:0x001118B4 size:0x1D4 mapped:0x80750948
void fn_3_1118B4(void) {
    s32 lim = *(s16*)(lbl_3_data_21448 + 6);
    u8 flag = 1;
    s32 sel;
    u8 mode = g_Minigame[0x1A2A];
    s32 isMode3 = mode == 3;
    s32 k;
    if (isMode3) {
        lim = *(s16*)(lbl_3_data_217A4 + 0xC);
    }
    if (!isMode3) {
        flag = g_Minigame[0x1DF4];
    }
    if (*(s16*)(g_Pitcher + 0x120) > lim && flag != 0) {
        if (g_Minigame[0x1A2A] == 3) {
            g_Minigame[0x1ACA] = *(s16*)(lbl_3_data_217A4 + 0x12);
        } else if ((sel = g_Minigame[0x1DF5]) < 3) {
            if (sel < 2) {
                k = sel * 2;
                k += RandomIndexFromWeights(lbl_3_data_213A4 + g_Minigame[0x1AC9] * 5 + k, 2);
            } else {
                k = 4;
            }
            g_Minigame[0x1ACA] = lbl_3_data_2139C[k] + rand() % 7 - 3;
        } else if (sel == 3) {
            g_Minigame[0x1AD5] = 1;
            k = RandomIndexFromWeights(lbl_3_data_213A4 + g_Minigame[0x1AC9] * 5, 5);
            g_Minigame[0x1ACA] = lbl_3_data_2139C[k] + rand() % 7 - 3;
        } else {
            g_Pitcher[0x164] = 1;
            g_Pitcher[0x165] = 1;
        }
        fn_3_750C4(2);
    }
}

// .text:0x00111A88 size:0x3C mapped:0x80750B1C
void fn_3_111A88(void) {
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    fn_3_5A6D4(8);
}

// .text:0x00111AC4 size:0x198 mapped:0x80750B58
void fn_3_111AC4(void) {
    u8* mg = g_Minigame;
    u8 st = mg[0x190B];
    if (st == 0) {
        if (g_Pitcher[0x13E] == 4) {
            if (mg[0x1A2D] >= mg[0x1A2F]) {
                mg[0x190B] = 1;
                mg[0x1912] = 1;
            }
            g_Minigame[*(s8*)(g_Minigame + 0x1905) * 2 + 0x1ACC] = 0;
            fn_3_155288();
        }
    } else {
        if (st == 1) {
            mg[0x190B] = 2;
            *(s16*)(g_GameLogic + 0x100) = *(s16*)lbl_3_data_21448;
        }
        *(s16*)(g_GameLogic + 0x100) -= 1;
        if (g_Minigame[0x1912] != 0 &&
            (g_Minigame[0x1909] == 0 ||
             (g_Minigame[0x1909] != 0 && g_Minigame[0x190C] + 1 >= g_Minigame[0x1906] && *(s32*)g_Scores >= g_Scores[0xAA])) &&
            g_Minigame[0x1A37] == 0 && *(s16*)(g_GameLogic + 0x100) == 0x43) {
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        }
        if (*(s16*)(g_GameLogic + 0x100) == 7) {
            changeScene(3, 6);
        }
        if (*(s16*)(g_GameLogic + 0x100) <= 0) {
            g_GameLogic[0x12B] = 1;
            g_GameLogic[0x12C] = 1;
            g_GameLogic[0x12E] = 1;
            fn_3_5A6D4(8);
        }
    }
}

// .text:0x00111C5C size:0x324 mapped:0x80750CF0
extern s32 fn_3_108854(void);
extern void fn_3_75560(void);
extern void atBat_batter(void);
extern void fn_3_2EA24(void);
extern void fn_3_8A958(void);

static inline void clearHitFlags_31F0(void) {
    s8 i = 0;
    do {
        g_Minigame[0x1DBC + i] = 0;
        i++;
    } while (i < 4);
}

// NONMATCHING 97%: the inlined fn_3_111AC4 tail reuses a different g_Minigame base; one extsb is CSE'd
#if NONMATCHING
void fn_3_111C5C(void) {
    u8* e;
    u8 ci;
    s8 i;
    if (g_Minigame[0x190B] == 0) {
        if (fn_3_108854() != 0) {
            return;
        }
        fn_3_75560();
        clearHitFlags_31F0();
        i = 0;
        do {
            ci = g_Minigame[0x18CC + i];
            if ((s8)ci >= 0 && (s8)ci < 4 && i == *(s8*)(g_Minigame + 0x1905) && g_Minigame[0x18D8 + i] != 0) {
                e = g_Minigame + (s8)ci * 0x10;
                g_Minigame[0x1DBC + (s8)ci] = 1;
                memset(e + 0x1D7C, 0, 0x10);
                switch (g_Pitcher[0x13E]) {
                case 2:
                    if (g_Minigame[0x1DD0] == 0) {
                        ((void (*)(void))fn_3_110634)(); // a call in the original (not inlined)
                        g_Minigame[0x1DD0] = 1;
                    }
                    if (*(s16*)(g_Pitcher + 0x126) <= *(s16*)(g_Minigame + 0x1DCC)) {
                        *(u16*)(e + 0x1D80) |= 0x100;
                    }
                    break;
                case 3:
                    if (*(s16*)(g_Ball + 0x1B68) < *(s16*)(g_Pitcher + 0x122) - *(s16*)(g_Minigame + 0x1DCE)) {
                        *(u16*)(e + 0x1D80) |= 0x100;
                    }
                    break;
                }
            }
            i++;
        } while (i < 4);
        atBat_batter();
        clearHitFlags_31F0();
        fn_3_2EA24();
        fn_3_8A958();
    }
    fn_3_111AC4();
}
#endif

// .text:0x00111F80 size:0xF0 mapped:0x80751014
void fn_3_111F80(void) {
    u8* gl = g_GameLogic;
    switch (gl[0x125]) {
    case 0:
        changeScene(1, 6);
        gl[0x125] = 1;
        break;
    case 1: {
        s32 t = *(u16*)(gl + 0xFC);
        if (t >= *(s16*)(lbl_3_data_18C48 + 4) ||
            (t >= *(s16*)(lbl_3_data_18C48 + 2) && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            gl[0x125] = 2;
        }
        break;
    }
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            gl[0x125] = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// .text:0x00112070 size:0x70 mapped:0x80751104
void fn_3_112070(void) {
    fn_3_DE4FC();
    fn_3_5A6D4(14);
    *(s16*)(g_Minigame + 0x18A6) = rand() % 30 + 15;
    fn_3_155288();
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
}

// .text:0x001120E0 size:0x48 mapped:0x80751174
extern u8 g_Scores[];

void fn_3_1120E0(void) {
    if (*(s32*)g_Scores >= g_Scores[0xAA]) {
        fn_3_5A6D4(0xF);
    } else {
        fn_3_5A6D4(6);
    }
}

// .text:0x00112128 size:0x7C mapped:0x807511BC
void fn_3_112128(void) {
    g_Minigame[0x190C] += 1;
    if (g_Minigame[0x1909] == 0) {
        fn_3_5A6D4(0xF);
    } else if (g_Minigame[0x190C] >= g_Minigame[0x1906]) {
        fn_3_5A6D4(0x19);
    } else {
        fn_3_5A6D4(7);
    }
    lbl_3_common_bss_32724[0xB7] = 1;
}

// .text:0x001121A4 size:0x8C mapped:0x80751238
void fn_3_1121A4(void) {
    setInMemBatterConstants(*(s8*)(g_Minigame + 0x1905));
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    fn_3_BF1AC();
    Set_803cb848(1);
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
}

// .text:0x00112230 size:0x220 mapped:0x807512C4
extern void fn_3_8FC0C(void);
extern u8 lbl_3_data_213D4[];
extern u8 lbl_3_data_213DC[];

void fn_3_112230(void) {
    s32 i;
    s32 n;
    fn_3_1121A4();
    g_Minigame[0x190B] = 0;
    g_Minigame[0x1AC8] = 0;
    g_Minigame[0x1AD4] = 0;
    *(s16*)(g_Minigame + 0x18A8) = 1;
    g_Minigame[0x1AD5] = 0;
    g_Minigame[0x1AD7] = 0;
    for (i = 0; i < 10; i++) {
        g_Minigame[0x1A96 + i] = 0;
    }
    *(s16*)(g_Ball + 0x1B64) = 0;
    g_FieldingLogic[0x110] = 0;
    *(s16*)(g_Pitcher + 0x126) = *(s16*)(lbl_3_data_21448 + 8);
    if (g_GameLogic[0x12B] != 0) {
        g_GameLogic[0x12C] = 1;
        g_GameLogic[0x12D] = 1;
    } else {
        g_GameLogic[0x12C] = 0;
    }
    g_GameLogic[0x12B] = 0;
    if (g_Minigame[0x1906] > 1) {
        g_Minigame[0x1AC9] = lbl_3_data_213DC[*(s32*)g_Scores - 1];
    } else if (g_Minigame[0x1A2B] == 3) {
        n = g_Minigame[0x1A2D] / 5;
        if (n > 4) {
            n = 4;
        }
        g_Minigame[0x1AC9] = n;
    } else if (g_Minigame[0x1A2D] < 5) {
        g_Minigame[0x1AC9] = lbl_3_data_213D4[g_Minigame[0x1A2B] * 2];
    } else {
        g_Minigame[0x1AC9] = lbl_3_data_213D4[g_Minigame[0x1A2B] * 2 + 1];
    }
    minigamesSetSomePointers();
    minigamesGXStuff();
    minigamesSetSomePointers2();
    fn_3_8FC0C();
    changeScene(1, 6);
    fn_3_5A6D4(1);
}

// .text:0x00112450 size:0x108 mapped:0x807514E4
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern void fn_3_6EBB4(s32);
extern void setBatterContactConstants(void);
extern s32 someAnimationIndFunction(void);
extern u8 lbl_803CBC3C[];
extern u8 lbl_3_common_bss_32234[];

void fn_3_112450(void) {
    u8* gl = g_GameLogic;
    u8* mg;
    switch (gl[0x125]) {
    case 0:
        mg = g_Minigame;
        mg[0x1905] = mg[0x18E0 + mg[0x190C]];
        gl[0x12B] = 1;
        mg[0x1A2D] = 0;
        mg[0x1912] = 0;
        mg[0x1ACB] = 0;
        fn_3_F578();
        fn_3_753E8(0);
        fn_3_6EBB4(-1);
        setBatterContactConstants();
        setInMemBatterConstants(*(s8*)(mg + 0x1905));
        lbl_803CBC3C[2] = 0;
        gl[0x125] += 1;
        break;
    case 1:
        if (someAnimationIndFunction() != 0) {
            lbl_3_common_bss_32234[1] = 1;
            gl[0x125] += 1;
        }
        break;
    default:
        lbl_3_common_bss_32724[0xB6] = 1;
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00112558 size:0x78 mapped:0x807515EC
void fn_3_112558(void) {
    *(s32*)g_Scores += 1;
    g_Minigame[0x190C] = 0;
    if (g_Minigame[0x1909] == 0) {
        fn_3_5A6D4(7);
        return;
    }
    if (*(s32*)g_Scores == 1) {
        fn_3_10AD48();
    }
    fn_3_5A6D4(7);
    fn_3_10F550(4, 0);
}

// .text:0x001125D0 size:0x40 mapped:0x80751664
void fn_3_1125D0(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_5A6D4(6);
}

// .text:0x00112610 size:0x2D8 mapped:0x807516A4
extern void fn_3_59A90(void);
extern int RandomInt_Game_Range(int min, int max);
extern u8 lbl_3_data_2127C[];
extern u8 lbl_3_data_213E4[];
typedef struct { s16 count; s16 time; } MgModeParam_31F0;
extern MgModeParam_31F0 lbl_3_data_21400[];

// NONMATCHING 96%: scheduling of the mode-table loads and zero/base register picks in the reset loop
#if NONMATCHING
void fn_3_112610(void) {
    u8* gl = g_GameLogic;
    u8* mg;
    s32 i;
    u8 c;
    if (gl[0x125] == 0) {
        fn_3_59A90();
        g_GameLogic[0x121] = 3;
        *(s32*)(g_Minigame + 0x17C0) = 0;
        for (i = 0; i < 4; i++) {
            *(s16*)(g_Minigame + 0x1890 + i * 2) = 0;
            *(s16*)(g_Minigame + 0x1898 + i * 2) = 0;
            *(s16*)(g_Minigame + 0x18BC + i * 4) = 0;
            *(s16*)(g_Minigame + 0x18BE + i * 4) = 0;
            ((s8*)g_Minigame)[0x18F4 + i] = -1;
            ((s8*)g_Minigame)[0x18FC + i] = -1;
            ((s8*)g_Minigame)[0x1900 + i] = -1;
            ((s8*)g_Minigame)[0x18F0 + i] = 1;
            ((s8*)g_Minigame)[0x18F8 + i] = -1;
            *(s16*)(g_Minigame + 0x1A8E + i * 2) = 0;
            g_Minigame[0x1ACC + i * 2] = 0;
            g_Minigame[0x1ACD + i * 2] = 0;
        }
        mg = g_Minigame;
        *(s32*)g_Scores = 0;
        mg[0x190C] = 0;
        *(s16*)(mg + 0x1A26) = 0;
        mg[0x1A37] = 0;
        ((s8*)mg)[0x1904] = -1;
        ((s8*)mg)[0x1905] = -1;
        *(s32*)(g_Minigame + 0x17C0) = 0;
        mg[0x1AD5] = 0;
        mg[0x1AD6] = 0;
        *(s16*)(mg + 0x18A0) = 0;
        *(s16*)(mg + 0x18A2) = 0;
        *(s16*)(mg + 0x18A4) = 0;
        *(s16*)(mg + 0x18A6) = 30;
        *(s16*)(mg + 0x18A8) = 0;
        if (mg[0x1909] == 0) {
            g_Scores[0xAA] = 1;
            mg[0x1A2F] = lbl_3_data_21400[mg[0x1A2B]].count;
            c = (lbl_3_data_2127C + mg[0x1A2A] * 5)[mg[0x1A2B]];
            *(s16*)(mg + 0x1A26) = lbl_3_data_21400[mg[0x1A2B]].time;
            mg[0x18DC] = c;
            mg[0x18DD] = c;
            mg[0x18DE] = c;
            mg[0x18DF] = c;
        } else {
            if (mg[0x1A3C] != 0) {
                mg[0x18DC] = lbl_3_data_2127C[0x23];
                mg[0x18DD] = lbl_3_data_2127C[0x23];
                mg[0x18DE] = lbl_3_data_2127C[0x23];
                mg[0x18DF] = lbl_3_data_2127C[0x23];
            }
            g_Scores[0xAA] = lbl_3_data_213E4[(g_Minigame[0x1906] - 2) * 2];
            g_Minigame[0x1A2F] = lbl_3_data_213E4[(g_Minigame[0x1906] - 2) * 2 + 1];
        }
        if (mg[0x1909] == 0 && g_Minigame[0x1A3C] == 0) {
            if (g_Minigame[0x1909] == 0 && g_Minigame[0x1A3C] == 0 && g_Minigame[0x1A2B] == 3) {
                g_Minigame[0x1AD8] = 9;
            } else {
                g_Minigame[0x1AD8] = RandomInt_Game_Range(4, 9);
            }
            g_Minigame[0x1AD9] = 1;
        } else if (g_Minigame[0x1A3C] != 0) {
            g_Minigame[0x1AD8] = RandomInt_Game_Range(0, 2);
            g_Minigame[0x1AD9] = RandomInt_Game_Range(2, 3);
        } else {
            g_Minigame[0x1AD8] = 9;
            g_Minigame[0x1AD9] = 1;
        }
        gl[0x125]++;
    } else {
        fn_3_5A6D4(5);
    }
}
#endif

// .text:0x001128E8 size:0x4 mapped:0x8075197C
void fn_3_1128E8(void) {
    return;
}

// .text:0x001128EC size:0x2EC mapped:0x80751980
// View returned by fn_80052734: only the fields used here.
typedef struct {
    u8 pad0[0x40];
    Mtx view;   // 0x40
    Vec pos;    // 0x70
    Vec target; // 0x7C
} CamView_31F0;

void* fn_80052734(s32 index);
void fn_8003414C(Mtx view);

// .bss (laid out last-defined-first)
static u8 lbl_3_bss_B69A[0x1E]; // unused
static u8 lbl_3_bss_B699;
static u8 lbl_3_bss_B698[0x1]; // unused
extern const f32 lbl_3_rodata_326C; // 200.0f
extern const f32 lbl_3_rodata_3274; // 250.0f
extern const f32 lbl_3_rodata_3278; // 100.0f
extern const f32 lbl_3_rodata_327C; // 0.0f
extern const f32 lbl_3_rodata_3280; // -55.0f
extern const f32 lbl_3_rodata_3284; // -10.0f
extern const f32 lbl_3_rodata_3288; // 32767.0f

void fn_3_1128EC(void) {
    CamView_31F0* cam = fn_80052734(0);
    Vec pos;
    Vec dir;
    Vec ofs;
    Mtx inv;
    u8 idx;
    if (*(s16*)(g_Minigame + 0x18A6) <= 0) {
        pos = cam->pos;
        dir = cam->target;
        PSVECSubtract(&dir, &pos, &dir);
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, lbl_3_rodata_326C, &dir);
        PSVECAdd(&pos, &dir, &dir);
        if (dir.y > 55.0f) {
            dir.y = 55.0f;
        }
        PSMTXInverse(cam->view, inv);
        ofs.x = (rand() % 10000 - 5000) / lbl_3_rodata_3274;
        ofs.y = (rand() % 1000 - 500) / lbl_3_rodata_3278;
        ofs.z = lbl_3_rodata_327C;
        PSMTXMultVecSR(inv, &ofs, &ofs);
        PSVECAdd(&dir, &ofs, &dir);
        if (dir.y > lbl_3_rodata_3280) {
            dir.y = lbl_3_rodata_3284 * ((f32)rand() / lbl_3_rodata_3288) + lbl_3_rodata_3280;
        }
        if (lbl_3_bss_B699 != 0) {
            idx = rand() % 5 + 8;
        } else {
            idx = rand() % 4 + 4;
        }
        fn_3_BC6D8(&dir, &cam->pos, idx, 0);
        lbl_3_bss_B699 = !lbl_3_bss_B699;
        *(s16*)(g_Minigame + 0x18A6) = rand() % 60 + 60;
    } else {
        *(s16*)(g_Minigame + 0x18A6) -= 1;
    }
    fn_8003414C(cam->view);
}

// The original expands fn_3_111C5C into fn_3_112BD8. CW only does that with a larger inline size
// limit (with -inline deferred, the value in effect at the end of the file counts) and only from a
// copy that is always visible (fn_3_111C5C itself is NONMATCHING).
#pragma inline_max_size(100000)
// Inline copy of fn_3_111C5C.
static inline void fn_3_111C5C_inline(void) {
    u8* e;
    u8 ci;
    s8 i;
    if (g_Minigame[0x190B] == 0) {
        if (fn_3_108854() != 0) {
            return;
        }
        fn_3_75560();
        clearHitFlags_31F0();
        i = 0;
        do {
            ci = g_Minigame[0x18CC + i];
            if ((s8)ci >= 0 && (s8)ci < 4 && i == *(s8*)(g_Minigame + 0x1905) && g_Minigame[0x18D8 + i] != 0) {
                e = g_Minigame + (s8)ci * 0x10;
                g_Minigame[0x1DBC + (s8)ci] = 1;
                memset(e + 0x1D7C, 0, 0x10);
                switch (g_Pitcher[0x13E]) {
                case 2:
                    if (g_Minigame[0x1DD0] == 0) {
                        ((void (*)(void))fn_3_110634)(); // a call in the original (not inlined)
                        g_Minigame[0x1DD0] = 1;
                    }
                    if (*(s16*)(g_Pitcher + 0x126) <= *(s16*)(g_Minigame + 0x1DCC)) {
                        *(u16*)(e + 0x1D80) |= 0x100;
                    }
                    break;
                case 3:
                    if (*(s16*)(g_Ball + 0x1B68) < *(s16*)(g_Pitcher + 0x122) - *(s16*)(g_Minigame + 0x1DCE)) {
                        *(u16*)(e + 0x1D80) |= 0x100;
                    }
                    break;
                }
            }
            i++;
        } while (i < 4);
        atBat_batter();
        clearHitFlags_31F0();
        fn_3_2EA24();
        fn_3_8A958();
    }
    fn_3_111AC4();
}

// .text:0x00112BD8 size:0x7C0 mapped:0x80751C6C
// Bomb-omb Derby state machine: dispatches on the game state (g_GameLogic+0x11E).
// NONMATCHING 99%: register allocation in the inlined fn_3_111C5C copy (as in fn_3_111C5C itself).
#if NONMATCHING
void fn_3_112BD8(void) {
    switch (g_GameLogic[0x11E]) {
    case 4:
        fn_3_112610();
        break;
    case 26:
        fn_3_1125D0();
        break;
    case 6:
        fn_3_112558();
        break;
    case 7:
        fn_3_112450();
        break;
    case 0:
        fn_3_112230();
        break;
    case 1:
        fn_3_111C5C_inline();
        break;
    case 2:
        fn_3_111738();
        break;
    case 8:
        fn_3_112128();
        break;
    case 25:
        fn_3_1120E0();
        break;
    case 3:
        fn_3_111F80();
        break;
    case 15:
        fn_3_112070();
        break;
    }
}
#endif

