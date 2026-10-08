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
extern void fn_3_AFD80(s32, void*);
extern void fn_3_5A6D4(s32);
extern void fn_3_2EA24(void);
extern void fn_3_2E87C(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_1DD48(void*);
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
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern u8 lbl_800EFBA4[];
extern u8 g_Controls[];
typedef struct { s32 a; u16 b4; u16 b6; u16 b8; u8 pad0[2]; s16 c; u8 pad1[4]; s16 d12; u8 pad2[0x1D0 - 0x14]; u8 b1D0; u8 pad3; u8 b1D2; u8 pad4[2]; u8 b1D5; u8 pad5[3]; u8 b1D9; u8 b1DA; u8 pad6[0x220 - 0x1DB]; u8 b220; } SD;
typedef struct { u8 p0[4]; u16 b4; u16 b6; u16 b8; u8 p1[6]; } CT;
#define L34 ((SD*)&lbl_3_common_bss_34C90)
extern void fn_3_107E80(void);
extern s32 fn_3_5B380(void);
extern void fn_8004CC18();
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

// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
void fn_3_D9EA0(void) {
    return;
}

// ~95%: only GPR order of loop-invariants differs (orig range=r29,t+4=r28,t=r27; ours t=r29,t+4=r28,range=r27)
// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
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
    return;
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

// ~94%: g_Controls copy block gets r3/r5 swapped (orig lis r5 lbl_803CBC3C, lwz r3), and final li r5,2 / stb 0x1d9 ordering differs
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
        u8* c = g_Controls + lbl_3_common_bss_34C90.w0 * 0x10;
        lbl_803CBC3C = 1;
        lbl_3_common_bss_34C90.w4 = *(u16*)(c + 4);
        lbl_3_common_bss_34C90.w6 = *(u16*)(c + 6);
        lbl_3_common_bss_34C90.w8 = *(u16*)(c + 8);
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
        switch (fn_3_5B380()) {
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
            fn_8004CC18(g_d_GameSettings, &lbl_3_common_bss_34C90, 2);
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
        ((void (*)(s32))fn_3_AFD80)(1);
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
            fn_3_AFD80(0, &lbl_3_common_bss_34C90);
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
