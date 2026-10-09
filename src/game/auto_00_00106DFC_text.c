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
extern void* memset(void*, int, unsigned long);
extern void fn_3_9DC18(void*, s32, s32);
extern void manageStadiumLoading(void);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern s32 fn_3_107D34(u8*, u8*);
extern void fn_3_9E078(s32*, s32, s32);
extern u8 lbl_8037169C[];
extern void changeScene(s32, s32);
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

// fn_3_10C7A4, size:0x78
void fn_3_10C7A4(void) {
    s32 i;
    fn_8001CA40(0);
    for (i = 0; i < 4; i++) {
        fn_80011BE4(i);
        g_Minigame[0x19E9 + i * 9] = 0;
        *(s8*)(g_Minigame + 0x19EA + i * 9) = -1;
    }
}

// fn_3_10B200, size:0x7C
void fn_3_10B200(void) {
    if (g_d_GameSettings[7] != 6) {
        *(s16*)(lbl_8036E548 + 0x3078) = 0;
    }
    fn_80035B50(0xD);
    fn_3_B95EC();
    fn_3_5E60();
    fn_80018B38();
    fn_3_909B0();
    fn_3_9081C();
    fn_80035B50(0x11);
    g_Minigame[0x19DF] = 0x1E;
    fn_3_5A6D4(0x1D);
}

// fn_3_10A01C, size:0x84
void fn_3_10A01C(void) {
    u8 m = g_Minigame[0x1A2A];
    if (m == 1) {
        fn_3_1128E8();
    } else if (m == 2) {
        fn_3_1160B8();
    } else if (m == 3) {
        fn_3_1323CC();
    } else if (m == 4) {
        fn_3_141A2C();
    } else if (m == 5) {
        fn_3_1471C0();
    } else if (m == 6) {
        fn_3_13C464();
    }
}

// fn_3_107D70, size:0x44
u8 fn_3_107D70(s8 i) {
    if (g_d_GameSettings[7] == 7 && i >= 0 && i < 4) {
        return g_Minigame[0x1DC8 + i];
    }
    return 0;
}

// fn_3_107DB4, size:0x44
u8 fn_3_107DB4(s8 i) {
    if (g_d_GameSettings[7] == 7 && i >= 0 && i < 4) {
        return g_Minigame[0x1DC4 + i];
    }
    return 0;
}

// fn_3_107DF8, size:0x44
u8 fn_3_107DF8(s8 i) {
    if (g_d_GameSettings[7] == 7 && i >= 0 && i < 4) {
        return g_Minigame[0x1DC0 + i];
    }
    return 0;
}

// minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased, size:0x44
u8 minigame_checkIfAIInputIs_Algorithmic_Or_ControllerBased(s8 i) {
    if (g_d_GameSettings[7] == 7 && i >= 0 && i < 4) {
        return g_Minigame[0x1DBC + i];
    }
    return 0;
}

// fn_3_107C40, size:0x48
s32 fn_3_107C40(void) {
    u32 n = g_Minigame[0x1906];
    s16 v = *(s16*)(g_Minigame + 0x1890);
    u32 i;
    for (i = 1; i < n; i++) {
        if (*(s16*)(g_Minigame + 0x1890 + i * 2) != v) {
            return 0;
        }
    }
    return 1;
}

// fn_3_107C88, size:0x48
s32 fn_3_107C88(void) {
    u32 n = g_Minigame[0x1906];
    s16 v = *(s16*)(g_Minigame + 0x18BC);
    u32 i;
    for (i = 1; i < n; i++) {
        if (*(s16*)(g_Minigame + 0x18BC + i * 4) != v) {
            return 0;
        }
    }
    return 1;
}

// fn_3_107CD0, size:0x64
u8 fn_3_107CD0(void) {
    u8 arr[4];
    u8* p = arr;
    u32 i = 0;
    do {
        *p = i;
        i++;
        p++;
    } while (i < g_Minigame[0x1906]);
    fn_800246D4(fn_3_107D34, arr, arr, 1, g_Minigame[0x1906]);
    return arr[0];
}

// fn_3_1078F8, size:0x90
void fn_3_1078F8(void) {
    u32 i;
    u8* p;
    memset(g_Minigame + 0x1E04, 0, 0x28);
    g_Minigame[0x1A3D] = 0;
    g_Minigame[0x1A3F] = 0;
    lbl_8036E548[0x307E] = 0;
    p = g_Minigame;
    i = 0;
    do {
        p[0x1E1C] = i + 1;
        i++;
        p++;
    } while (i < 6);
    fn_3_9DC18(g_Minigame + 0x1E1C, 6, 0);
    fn_3_5A6D4(0x28);
}

// fn_3_10AD48, size:0xD0
void fn_3_10AD48(void) {
    s32 arr[4];
    s32 i;
    for (i = 0; i < 4; i++) {
        arr[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x18CC + i) >= 0) {
            arr[i] = i;
        }
    }
    fn_3_9E078(arr, g_Minigame[0x1906], 0);
    for (i = 0; i < 4; i++) {
        g_Minigame[0x18E0 + i] = arr[i];
    }
}

// fn_3_10AE18, size:0xD8
void fn_3_10AE18(void) {
    s32 arr[4];
    s32 i;
    for (i = 0; i < 4; i++) {
        arr[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x18CC + i) >= 0) {
            arr[i] = i;
        }
    }
    fn_3_9E078(arr, g_Minigame[0x1906], 0);
    for (i = 0; i < 4; i++) {
        g_Minigame[0x18E0 + i] = arr[i];
    }
    fn_3_5A6D4(0x1A);
}
