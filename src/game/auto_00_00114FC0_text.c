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
