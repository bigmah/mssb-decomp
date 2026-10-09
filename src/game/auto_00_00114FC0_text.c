#include "game/auto_00_00114FC0_text.h"
#include "game/auto_00_0005985C_text.h"

extern u8 g_GameLogic[];
extern u8 g_Minigame[];
extern u8 g_Scores[];
extern u8 lbl_8036E548[];
extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern void fn_3_114A88(s32);
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

// fn_3_1158B0, size:0x48
void fn_3_1158B0(void) {
    if (*(s32*)g_Scores >= (s32)g_Scores[0xAA]) {
        fn_3_5A6D4(0xF);
        return;
    }
    fn_3_5A6D4(6);
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

// fn_3_115B5C, size:0x80
void fn_3_115B5C(void) {
    *(s32*)g_Scores += 1;
    g_Minigame[0x190C] = 0;
    fn_3_5A6D4(7);
    if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
        fn_3_10F550(4, 0);
    }
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
