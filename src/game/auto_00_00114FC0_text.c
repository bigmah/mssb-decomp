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

