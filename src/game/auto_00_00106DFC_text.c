#include "game/auto_00_00106DFC_text.h"

extern u8 g_Minigame[];
extern u8 g_d_GameSettings[];
extern u8 g_GameLogic[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_common_bss_34C58[];
extern u8 lbl_8036E548[];
extern u8 g_Camera[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_3_data_20FDC[];
extern u8 lbl_3_data_228[];
extern u8 lbl_3_data_18910[];
extern u8 lbl_803616CC[];
extern void* _OSAllocFromHeap(s32, s32);
extern s32 ARAMTransfer(void*, int, int, int);
extern void fn_3_90064(s32);
extern void fn_3_5A6D4(s32);
extern void fn_3_5E60(void);
extern void fn_3_B95EC(void);
extern void fn_3_909B0(void);
extern void fn_3_9081C(void);
extern void fn_80035B50(int);
extern void fn_80018B38(void);
extern void fn_8001CA40(s32);
extern void fn_80011BE4(s32);
extern void fn_800246D4(void*, void*, void*, s32, s32);
extern void fn_3_1128E8(void);
extern void fn_3_1160B8(void);
extern void fn_3_1323CC(void);
extern void fn_3_141A2C(void);
extern void fn_3_1471C0(void);
extern void fn_3_13C464(void);

#pragma dont_inline on

// fn_3_106EB0, size:0x24
void fn_3_106EB0(void) {
    fn_3_90064(0x30B);
}

// fn_3_107078, size:0x2C
void fn_3_107078(void) {
    if (g_Minigame[0x18E8 + *(s8*)(g_Minigame + 0x1908)] == 1) {
        g_Minigame[0x1A3F] = 1;
    }
}
