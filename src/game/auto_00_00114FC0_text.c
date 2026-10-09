#include "game/auto_00_00114FC0_text.h"
#include "game/auto_00_0005985C_text.h"

extern u8 g_GameLogic[];
extern u8 g_Minigame[];
extern u8 g_Scores[];
extern u8 lbl_8036E548[];
extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern void fn_3_114A88(s32);
extern void changeScene(s32, s32);
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern s16 lbl_3_data_18C48[];
extern u8 lbl_8037169C[];
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern u8 g_Batter[];
extern u8 lbl_3_data_21BC4[];
extern f32 lbl_3_data_226C4[];
extern void fn_3_11881C(void);
extern void fn_8001D110(s32 i, f32 a, f32 b, f32 c);
extern u8 g_Ball[];
extern f32 maybeInitialBatPos[];
extern s16 lbl_3_data_2167C;
extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void fn_3_58870(void);
extern void fn_3_DE4FC(void);
extern void fn_3_10F550(s32, s32);
extern void Set_803cb848(s32);
extern void* memset(void*, s32, u32);
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];

#pragma dont_inline on

// fn_3_114FC0, size:0x6C
void fn_3_114FC0(void) {
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    g_Minigame[0x190C]++;
    if (g_Minigame[0x190C] >= g_Minigame[0x1906]) {
        fn_3_5A6D4(0x19);
        return;
    }
    fn_3_5A6D4(7);
}

// fn_3_11502C, size:0xDC
void fn_3_11502C(void) {
    if (g_Minigame[0x190B] == 1) {
        g_Minigame[0x190B] = 2;
        *(s16*)(g_GameLogic + 0x100) = lbl_3_data_2167C;
    }
    *(s16*)(g_GameLogic + 0x100) -= 1;
    if (*(s16*)(g_GameLogic + 0x100) == 7) {
        changeScene(3, 6);
    }
    if (*(s16*)(g_GameLogic + 0x100) <= 0) {
        g_GameLogic[0x12B] = 1;
        g_GameLogic[0x12C] = 1;
        g_GameLogic[0x12E] = 1;
        g_Minigame[0x190C]++;
        if (g_Minigame[0x190C] >= g_Minigame[0x1906]) {
            fn_3_5A6D4(0x19);
            return;
        }
        fn_3_5A6D4(7);
    }
}

// fn_3_115738, size:0xF0
void fn_3_115738(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        changeScene(1, 6);
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFC) >= lbl_3_data_18C48[2] ||
            (*(u16*)(g_GameLogic + 0xFC) >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic[0x125] = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// fn_3_115828, size:0x88
void fn_3_115828(void) {
    fn_3_DE4FC();
    if (g_Minigame[0x1A2B] <= 2 && g_Minigame[0x1909] == 0) {
        if (g_Minigame[*(s8*)(g_Minigame + 0x1908) + 0x18E8] == 1 && g_Minigame[0x19A8] == 0) {
            g_Minigame[0x1A37] = 1;
        } else {
            g_Minigame[0x1A37] = 2;
        }
    }
    fn_3_5A6D4(0xE);
}

// fn_3_1158B0, size:0x48
void fn_3_1158B0(void) {
    if (*(s32*)g_Scores >= (s32)g_Scores[0xAA]) {
        fn_3_5A6D4(0xF);
        return;
    }
    fn_3_5A6D4(6);
}

// fn_3_1158F8, size:0x80
void fn_3_1158F8(void) {
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    fn_3_F1DC();
    fn_3_751B4();
    fn_3_58870();
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    Set_803cb848(1);
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
}

// fn_3_115978, size:0x13C
void fn_3_115978(void) {
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    fn_3_F1DC();
    fn_3_751B4();
    fn_3_58870();
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    Set_803cb848(1);
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
    g_Minigame[0x190B] = 0;
    g_Minigame[0x1A81] = 0;
    *(s16*)(g_Minigame + 0x1A72) = 0;
    *(s16*)(g_Minigame + 0x1A74) = 0;
    *(s16*)(g_Minigame + 0x1A76) = 0;
    g_Minigame[0x1A89] = 0;
    g_Minigame[0x1A8A] = 0;
    ((s8*)g_Minigame)[0x1A8B] = -1;
    *(s16*)(g_Ball + 0x1B64) = 0;
    if (g_Minigame[0x1A2D] == 0) {
        if (g_GameLogic[0x12B] != 0) {
            g_GameLogic[0x12C] = 1;
            g_GameLogic[0x12D] = 1;
        } else {
            g_GameLogic[0x12C] = 0;
        }
        g_GameLogic[0x12B] = 0;
    } else if (g_Minigame[0x1A2B] != 3) {
        *(s16*)(g_Minigame + 0x1A70) = 0;
        g_Minigame[0x1A7E] = 1;
        fn_3_114A88(0);
    } else {
        g_GameLogic[0x12C] = 0;
    }
    changeScene(1, 6);
    fn_3_5A6D4(1);
}

// fn_3_115AB4, size:0xA8
void fn_3_115AB4(void) {
 u8 t;
t = g_Minigame[g_Minigame[0x190C] + 0x18E0]; g_Minigame[0x1904] = t;
g_GameLogic[0x12B] = 1;
*(s16*)(g_Minigame + 0x1898) = 0; *(s16*)(g_Minigame + 0x189A) = 0; *(s16*)(g_Minigame + 0x189C) = 0; *(s16*)(g_Minigame + 0x189E) = 0;
    fn_3_F578();
    fn_3_753E8(0);
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    *(f32*)(g_Batter + 0x4C) = maybeInitialBatPos[0];
    *(f32*)(g_Batter + 0x50) = maybeInitialBatPos[1];
    *(f32*)(g_Batter + 0x54) = maybeInitialBatPos[2];
    fn_3_5A6D4(0);
}

// fn_3_115B5C, size:0x80
void fn_3_115B5C(void) {
    *(s32*)g_Scores += 1;
    g_Minigame[0x190C] = 0;
    fn_3_5A6D4(7);
    if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
        fn_3_10F550(4, 0);
    }
}

// fn_3_115BDC, size:0x48
void fn_3_115BDC(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_114A88(1);
    fn_3_5A6D4(6);
}

// fn_3_1160B8, size:0x4
void fn_3_1160B8(void) {
}

// fn_3_11669C, size:0x30
void fn_3_11669C(void) {
    u8* p = lbl_8036E548;
    (*(u8**)(p + 0x2D94))[0x25A6] = 0;
    (*(u8**)(p + 0x2D94))[0x25CE] = 0;
    (*(u8**)(p + 0x2D94))[0x25F6] = 0;
    (*(u8**)(p + 0x2D94))[0x261E] = 0;
}

// fn_3_1166CC, size:0xC0
void fn_3_1166CC(void) {
    u32 i;
    for (i = 0; i < 40; i++) {
        u8* p = *(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28;
        p[0x26] = 0;
        *(s32*)p = 0;
    }
}

// fn_3_11678C, size:0xB4
void fn_3_11678C(void) {
    u8* e;
    s32 i;
    f32* v;
    for (i = 0; i < 7; i++) {
        e = *(u8**)(lbl_8036E548 + 0x2D94) + (i + 0xE9) * 0x28;
        e[0x26] = 0;
        if (i >= 4) {
            e[0x26] = 1;
            v = (f32*)(lbl_3_data_21BC4 + i * 0x30 - 0xC0);
            *(f32*)(e + 4) = v[0];
            *(f32*)(e + 8) = -v[1];
            *(f32*)(e + 0xC) = v[2];
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0]);
            *(void**)e = fn_3_11881C;
        }
    }
}
