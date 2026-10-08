#include "game/rep_28A8.h"
#include "header_rep_data.h"

extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_58870(void);
extern void fn_3_1DEB8(void);
extern void fn_3_BF1AC(void);
extern void Set_803cb848(s32);
extern void fn_3_BF158(void);
extern void fn_3_AFD80(s32);
extern void fn_3_5A6D4(s32);
extern void fn_3_2EA24(void);
extern void fn_3_2E87C(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_1DD48(void*);
extern struct { u8 pad[0xC]; s16 n; u8 pad2[0x1C4]; u8 b1D2; } lbl_3_common_bss_34C90;
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
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_5B408(void);
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern u8 lbl_800EFBA4[];
extern u8 g_Controls[];
extern u8 g_Fielders[];
extern s32 fn_3_E5924(void);
extern void fn_3_59918(s32, s32);
extern void fn_3_A0F0(void);
extern u8 g_GameLogic[];
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];

// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
void fn_3_D9EA0(void) {
    return;
}

// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
void fn_3_DA640(void) {
    return;
}

// .text:0x000DA834 size:0x1A0C mapped:0x807198C8
void fn_3_DA834(void) {
    return;
}

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

// 98%: orig schedules lbz 0x1da before stw 0x0 (subi in r5, not r0)
// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void fn_3_DC5A4(void) {
    s32 r = fn_3_6C938(1, 0x100);
    if (r != 0) {
        SB* p = (SB*)&lbl_3_common_bss_34C90;
        s32 n = r - 1;
        p->a = n;
        if (p->b1DA == 2) {
            fn_3_5B408();
            p = (SB*)&lbl_3_common_bss_34C90;
            p->b1D2 = 9;
        } else {
            p->b1D2 = 4;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        return;
    }
    if (fn_3_6C938(1, 8) != 0) {
        SB* p = (SB*)&lbl_3_common_bss_34C90;
        u8 t = p->b1DA;
        if ((s8)t != 0) {
            p->b1DA = t - 1;
        } else {
            p->b1DA = 2;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        return;
    }
    if (fn_3_6C938(1, 4) != 0) {
        SB* p = (SB*)&lbl_3_common_bss_34C90;
        u8 t = p->b1DA + 1;
        p->b1DA = t;
        if ((s8)t >= 3) {
            p->b1DA = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void fn_3_DC6E8(void) {
    return;
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void fn_3_DCA68(void) {
    return;
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void fn_3_DCC80(void) {
    return;
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
    for (i = 0; i < g_Minigame[0x1906]; i++) {
        u8 pl = g_Minigame[0x18CC + i];
        if ((s8)pl >= 0 && g_Minigame[0x18D8 + i] == 0 && (*(u16*)(g_Controls + (s8)pl * 0x10 + 6) & 0x1000)) {
            *(u8*)((u8*)&lbl_3_common_bss_34C90 + 0x1D5) = 1;
            *(s32*)&lbl_3_common_bss_34C90 = (s8)g_Minigame[0x18CC + i];
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

// .text:0x000DD3FC size:0x5A8 mapped:0x8071C490
void fn_3_DD3FC(void) {
    return;
}

// .text:0x000DD9A4 size:0x3BC mapped:0x8071CA38
void fn_3_DD9A4(void) {
    return;
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
    return;
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
void fn_3_DE744(void) {
    return;
}

