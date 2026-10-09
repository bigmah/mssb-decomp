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

// fn_3_10F550, size:0x14
void fn_3_10F550(s8 a, s16 b) {
    g_Minigame[0x1A41] = a;
    *(s16*)(g_Minigame + 0x1A28) = b;
}

// fn_3_1104A8, size:0x2C
void fn_3_1104A8(void) {
    s8 i = 0;
    do {
        i++;
        g_Minigame[0x1DBC + i - 1] = 0;
    } while (i < 4);
}

// fn_3_106DFC, size:0x54
void fn_3_106DFC(void) {
    *(void**)(g_Camera + 0xAB0) = _OSAllocFromHeap(4, 0x8000);
    *(void**)(g_Camera + 0x146C) = _OSAllocFromHeap(4, 0x8000);
}

// fn_3_106E50, size:0x60
s32 fn_3_106E50(void) {
    if ((s32)lbl_803C6CF8[0x715] == 1) {
        *(s32*)(g_Camera + 0x1B4) = ARAMTransfer(lbl_3_data_20FDC, 0, 0, 0);
        return 1;
    }
    return 0;
}

// fn_3_107988, size:0x40
s32 fn_3_107988(u32 v) {
    u32 i;
    u32 n = g_Minigame[0x1E2A] - 1;
    for (i = 0; i < n; i++) {
        if (g_Minigame[0x1E1C + i] == v) {
            return 1;
        }
    }
    return 0;
}

// fn_3_109D88, size:0x58
u8* fn_3_109D88(void) {
    if (g_Minigame[0x1A3C] != 0) {
        return lbl_803616CC + 0x118;
    }
    if (g_Minigame[0x1A2A] != 0) {
        return lbl_803616CC + (g_Minigame[0x1A2A] - 1) * 0x28 + 0x28;
    }
    return lbl_803616CC;
}

// fn_3_10FB74, size:0x70
void fn_3_10FB74(void) {
    u8 s = g_GameLogic[0x125];
    switch (s) {
    case 0:
        lbl_3_common_bss_32724[0xD8] = 0;
        lbl_3_common_bss_34C58[0x2C] = 0;
        g_GameLogic[0x125] = s + 1;
        break;
    }
    lbl_8036E548[0x307A] = 0;
    fn_3_5A6D4(0x1D);
}
