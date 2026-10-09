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
