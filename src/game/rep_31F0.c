#include "game/rep_31F0.h"
#include "header_rep_data.h"

#include "musyx/musyx.h"
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
extern void fn_8003A540(s32, u8*);
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
void fn_3_110634(void) {
    return;
}

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
void fn_3_110AD4(void) {
    return;
}

// .text:0x00111038 size:0x198 mapped:0x807500CC
void fn_3_111038(void) {
    return;
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
    fn_8003A540(0, g_GameLogic);
    if (g_Minigame[0x1912] == 1) {
        fn_3_5A6D4(8);
        return;
    }
    fn_3_5A6D4(0);
}

// .text:0x001112B4 size:0x484 mapped:0x80750348
void fn_3_1112B4(void) {
    return;
}

// .text:0x00111738 size:0x17C mapped:0x807507CC
void fn_3_111738(void) {
    return;
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
void fn_3_111C5C(void) {
    return;
}

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
void fn_3_112230(void) {
    return;
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
void fn_3_112610(void) {
    return;
}

// .text:0x001128E8 size:0x4 mapped:0x8075197C
void fn_3_1128E8(void) {
    return;
}

// .text:0x001128EC size:0x2EC mapped:0x80751980
void fn_3_1128EC(void) {
    return;
}

// .text:0x00112BD8 size:0x7C0 mapped:0x80751C6C
void fn_3_112BD8(void) {
    return;
}

