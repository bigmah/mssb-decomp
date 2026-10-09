#include "game/auto_00_001293D0_text.h"
#include "game/rep_3448.h"
#include "static/UnknownHomes_Static.h"

extern u8 g_Minigame[];
extern u8 g_GameLogic[];
extern u8* lbl_803CC1B8;
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_80371C30[];
extern u8 lbl_3_data_9FB4[];
extern void fn_80034E20(void*, void*);
extern void fn_8004CC2C(void);
extern void fn_8004D0F0(void);
extern void fn_3_11E7C4(void);
extern void fn_3_11E364(void);
extern void fn_3_129C88(void);
extern void fn_3_129FF8(void);
extern void fn_3_12C1AC(void);
extern void fn_3_EB6E0(void);
extern void fn_3_97144(void);
extern void fn_3_99BDC(void);
extern u8 lbl_3_data_9ECC[];
extern u8 lbl_3_data_9208[];
extern u8 lbl_3_data_92C8[];
extern u8 g_Practice[];
extern void fn_3_12BB64(void);
extern u8 lbl_3_data_92D4[];
extern u8 lbl_3_data_21268[];
extern u8 lbl_3_common_bss_37400[];
extern u8 lbl_3_data_217A4[];
extern void fn_3_1608F0(s32, s32, u8);
extern void fn_3_11D780(void);
extern void fn_3_EA454(void);
extern u8 lbl_3_common_bss_34C90[];
extern void* memset(void*, s32, u32);

// fn_3_12DB54, size:0x2C
void fn_3_12DB54(void) {
    s8 i;
    i = 0;
    do {
        g_Minigame[i + 0x1DBC] = 0;
        i++;
    } while (i < 4);
}

// fn_3_12E808, size:0x34
void fn_3_12E808(void) {
    memset(g_Minigame + 0x1D7C, 0, 0x78);
}

// fn_3_12DD88, size:0x44
u32 fn_3_12DD88(void) {
    u32 i = 0;
    do {
        if (g_Minigame[i * 0x34 + 0x890] != 2) {
            break;
        }
        i++;
    } while (i < 0xF);
    return i >= 0xF;
}

// fn_3_1293D0, size:0x88
void fn_3_1293D0(void) {
    if (g_GameLogic[0x125] == 0) {
        fn_800B0A5C_insertQueue(fn_3_129370, 2);
    }
    if (g_GameLogic[0x125] == 5 && *(u16*)(g_GameLogic + 0xFE) == 1) {
        fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
    }
    if (g_GameLogic[0x125] == 6) {
        fn_8004CC2C();
    }
}

// fn_3_12C514, size:0xB8
void fn_3_12C514(void) {
    if (g_GameLogic[0x11E] == 0x1A && g_GameLogic[0x125] == 0) {
        memset(g_Minigame + 0x1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11E364, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_12C5CC, size:0xB8
void fn_3_12C5CC(void) {
    if (g_GameLogic[0x11E] == 0x1A && g_GameLogic[0x125] == 0) {
        memset(g_Minigame + 0x1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11E7C4, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_129F48, size:0xB0
void fn_3_129F48(void) {
    u8* q = lbl_803CC1B8;
    fn_80034E20(q, lbl_3_data_9FB4);
    *(s16*)(q + 0x1C) = 0;
    if (lbl_3_common_bss_32724[0xBF] != 0) {
        *(u32*)(((u8**)lbl_80371C30)[*(u16*)(q + 0x14) * 2] + 0x5C) = 0x160000;
        *(s16*)(q + 0x1C) = 2;
    }
    *(s16*)(q + 0x18) = 0;
    *(s16*)(q + 0x1A) = 0;
    lbl_3_common_bss_32724[0xBE] = 1;
    *(void (**)(void))((u8**)&lbl_803CC1B8)[0] = fn_3_129C88;
}

// fn_3_12C684, size:0xC8
void fn_3_12C684(void) {
    if (g_GameLogic[0x11E] == 0x1A && g_GameLogic[0x125] == 0) {
        memset(g_Minigame + 0x1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_11EC28, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11F02C, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_129458, size:0x104
void fn_3_129458(void) {
    if (g_GameLogic[0x11E] == 0xE && g_GameLogic[0x125] == 1) {
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        if (g_Minigame[0x1A2A] == 1 && g_Minigame[0x1909] == 0 && g_Minigame[0x1A3C] == 0 && g_Minigame[0x1A2B] == 3) {
            fn_800B0A5C_insertQueue(fn_3_11D780, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_EA454, 2);
        fn_800B0A5C_insertQueue(fn_3_129370, 2);
    }
    if (g_GameLogic[0x11E] == 0x22 && (lbl_3_common_bss_34C90[0x1D2] == 7 || g_GameLogic[0x122] != 0)) {
        lbl_3_common_bss_32724[0xB7] = 1;
    }
}

// fn_3_12E83C, size:0xC0
void fn_3_12E83C(void) {
    s32 v;
    u8* g = g_Minigame;
    u8 k = g[0x1ADD];
    if (k <= 1) {
        v = *(s16*)(lbl_3_data_217A4 + 0xA) * k;
    } else {
        v = k * ((k - 1) * *(s16*)(lbl_3_data_217A4 + 0xA));
    }
    *(s16*)(g_Minigame + (s8)g_Minigame[0x1905] * 2 + 0x1890) += v;
    *(s16*)(g_Minigame + 0x1DF4) = v;
    if (g_d_GameSettings.exhibitionMatchInd == 0 && (s8)g_Minigame[0x1905] == *(s16*)(lbl_3_common_bss_37400 + 0x40)) {
        fn_3_1608F0(2, v, g[0x1ADD]);
    }
}

// fn_3_12C74C, size:0x11C
void fn_3_12C74C(void) {
    if (lbl_3_common_bss_32724[0xB6] != 0) {
        memset(g_Minigame + 0x1DF4, 0, 0xE);
        if (g_Minigame[0x1909] == 0) {
            fn_800B0A5C_insertQueue(fn_3_11F508, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_11F778, 2);
        fn_800B0A5C_insertQueue(fn_3_11FA58, 2);
        fn_800B0A5C_insertQueue(fn_3_11FDB0, 2);
        if (g_Minigame[0x1909] != 0) {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124738, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_12C868, size:0x11C
void fn_3_12C868(void) {
    if (g_GameLogic[0x11E] == 0x1A) {
        memset(g_Minigame + 0x1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_12026C, 2);
        fn_800B0A5C_insertQueue(fn_3_12089C, 2);
        if (g_Minigame[0x1909] == 0 && g_Minigame[0x1A3C] == 0 && g_Minigame[0x1A2B] == 3) {
            fn_800B0A5C_insertQueue(fn_3_120FF8, 2);
        } else {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
            fn_800B0A5C_insertQueue(fn_3_123990, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_121304, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
        fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
    }
}

// fn_3_12C984, size:0x10C
void fn_3_12C984(void) {
    if (lbl_3_common_bss_32724[0xB6] != 0) {
        memset(g_Minigame + 0x1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_121908, 2);
        if (g_Minigame[0x1909] != 0) {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124738, 2);
        fn_800B0A5C_insertQueue(fn_3_1226D4, 2);
        fn_800B0A5C_insertQueue(fn_3_122334, 2);
        fn_800B0A5C_insertQueue(fn_3_1235B8, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
    fn_3_97144();
}

// fn_3_12C3F0, size:0x124
void fn_3_12C3F0(void) {
    u8* q = lbl_803CC1B8;
    u8* t;
    u16 v;
    fn_80034E20(q, lbl_3_data_9208);
    lbl_3_common_bss_32724[0xD9] = 1;
    if (g_d_GameSettings.GameModeSelected == 7) {
        if (g_GameLogic[0x11E] == 0x1C || g_GameLogic[0x11E] == 0x1B || g_GameLogic[0x11E] == 0x1D) {
            v = *(u16*)lbl_3_data_92C8;
        } else {
            v = *(u16*)(lbl_3_data_92C8 + 2);
        }
    } else if (g_Practice[0x198] == 6) {
        v = *(u16*)(lbl_3_data_92C8 + 8);
    } else {
        v = *(u16*)(lbl_3_data_92C8 + 6);
    }
    t = lbl_80371C30 + 8;
    *(u16*)(((u8**)t)[*(u16*)(q + 0x14) * 2] + 0x64) = v;
    *(u32*)(((u8**)t)[*(u16*)(q + 0x14) * 2] + 0x5C) = 0x280000;
    *(u16*)(q + 0x1C) = v;
    *(u16*)(q + 0x1E) = 0;
    *(void (**)(void))((u8**)&lbl_803CC1B8)[0] = fn_3_12C1AC;
}

// fn_3_12BFE8, size:0x1C4
void fn_3_12BFE8(void) {
    u8* q = lbl_803CC1B8;
    fn_80034E20(q, lbl_3_data_92D4);
    if (g_d_GameSettings.GameModeSelected != 2) {
        if (g_d_GameSettings.GameModeSelected == 6) {
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x28) + 0x54) &= ~2;
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x30) + 0x54) &= ~2;
        } else {
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x28) + 0x54) &= ~2;
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x30) + 0x54) &= ~2;
        }
    }
    lbl_3_common_bss_32724[0xBC] = 1;
    if (g_d_GameSettings.GameModeSelected == 2) {
        *(s16*)(q + 0x20) = g_Practice[0x193];
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x18) + 0x64) = 0x5F;
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x20) + 0x64) = 0x5C;
    } else {
        *(s16*)(q + 0x20) = lbl_3_data_21268[(s8)g_Minigame[0x19E1]];
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x18) + 0x64) = 0x5E;
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 0x20) + 0x64) = 0x5B;
    }
    *(s16*)(q + 0x1A) = 0;
    *(s16*)(q + 0x1C) = 0;
    *(s16*)(q + 0x22) = 0;
    *(void (**)(void))((u8**)&lbl_803CC1B8)[0] = fn_3_12BB64;
}
