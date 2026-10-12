#include "game/auto_00_00106DFC_text.h"

extern u8 g_Minigame[];
extern u8 g_Controls[];
extern u8 lbl_80366158[];
extern s32 fn_3_5B380(u16);
extern void fn_8004CC18(void);
extern u8 lbl_3_data_B060[];
extern void fn_800203E0(u8 scene, s8 variant);
extern void fn_3_10C81C(void);
extern void fn_3_E1370(int mode);
extern s32 fn_80016F7C(void);
extern s32 fn_3_90DD8(void);
extern void fn_8003A540(s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers(void);
extern void fn_3_1128EC(void);
extern u8 lbl_3_data_21270[];
extern u8 lbl_3_data_18918[];
extern u8 lbl_3_data_18C48[];
extern void fn_3_10952C(void);
extern void fn_3_5B368(void);
extern s32 fn_3_5B220(s32);
extern void fn_3_10EFAC(void);
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
extern u8 inMemRoster[];
extern u8 lbl_8034E9A0[];
extern u8 lbl_800E86F0[];
extern void fn_3_10BE7C(void);
extern u8 inMemRoster[];
extern void fn_80062A74(void);
extern void fn_80062A94(void);
extern void fn_3_10B27C(void);
// Raw input for the stat-total calculation (see include/main/file_80069BDC.h).
typedef struct StatInput {
    /*0x00*/ s16 vals[6];
    /*0x0C*/ u8 order[6];
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14[2];
} StatInput; // size: 0x16
extern void fn_8006C398(StatInput* in);
extern void fn_3_1079C8(u8*, s32);
extern u8 lbl_8034E9A0[];
extern u8 lbl_800E86F0[];
extern void* _OSAllocFromHeap(s32, s32);
extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern u32 fn_3_90064(s32 id);
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
extern void* memcpy(void*, const void*, unsigned long);
extern void* memcpy(void*, const void*, unsigned long);
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
extern s32 fn_3_6C938(s32, s32);
extern u8 lbl_3_common_bss_34C90[];
extern u8 lbl_3_data_2137C[];
extern u8 lbl_3_data_188FC[];
extern u8 lbl_3_data_188E8[];
extern u8 lbl_3_data_21268[];
extern u8 lbl_800EFBA4[];
extern u8 sndFXStartEx(s32, u8, u8, u8);
extern void fn_3_5B408(void);

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

// fn_3_106DFC, size:0x54
void fn_3_106DFC(void) {
    *(void**)(g_Camera + 0xAB0) = _OSAllocFromHeap(4, 0x8000);
    *(void**)(g_Camera + 0x146C) = _OSAllocFromHeap(4, 0x8000);
}

// fn_3_106E50, size:0x60
s32 fn_3_106E50(void) {
    if ((s32)lbl_803C6CF8[0x715] == 1) {
        *(void**)(g_Camera + 0x1B4) = ARAMTransfer(lbl_3_data_20FDC, 0, 0, 0);
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

// fn_3_10768C, size:0xF8
void fn_3_10768C(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        g_Minigame[0x1A2A] = g_Minigame[0x1E1C + g_Minigame[0x1E2A]++];
        changeScene(1, 6);
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(*(u8**)(g_Minigame + 0x1E04) + 0x1A) != 0) {
            changeScene(3, 6);
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic[0x125] = 3;
        }
        break;
    case 3:
        g_GameLogic[0x125] = 4;
        break;
    case 4:
        fn_3_5A6D4(0x21);
        break;
    }
}

// fn_3_107B9C, size:0x34
s32 fn_3_107B9C(u8* a, u8* b) {
    if ((g_Minigame + 0x1E26)[*b] != (g_Minigame + 0x1E26)[*a]) {
        return (g_Minigame + 0x1E26)[*b] - (g_Minigame + 0x1E26)[*a];
    }
    return *a - *b;
}

// fn_3_107BD0, size:0x34
s32 fn_3_107BD0(u8* a, u8* b) {
    if ((g_Minigame + 0x1E22)[*b] != (g_Minigame + 0x1E22)[*a]) {
        return (g_Minigame + 0x1E22)[*b] - (g_Minigame + 0x1E22)[*a];
    }
    return *a - *b;
}

// fn_3_107C04, size:0x3C
s32 fn_3_107C04(u8* a, u8* b) {
    if (((s16*)(g_Minigame + 0x1890))[*b] != ((s16*)(g_Minigame + 0x1890))[*a]) {
        return ((s16*)(g_Minigame + 0x1890))[*b] - ((s16*)(g_Minigame + 0x1890))[*a];
    }
    return *a - *b;
}

// fn_3_107D34, size:0x3C
typedef struct { s16 v; s16 pad; } S16x2;
s32 fn_3_107D34(u8* a, u8* b) {
    if (((S16x2*)(g_Minigame + 0x18BC))[*b].v != ((S16x2*)(g_Minigame + 0x18BC))[*a].v) {
        return ((S16x2*)(g_Minigame + 0x18BC))[*b].v - ((S16x2*)(g_Minigame + 0x18BC))[*a].v;
    }
    return *a - *b;
}

// fn_3_10F5BC, size:0xC8
void fn_3_10F5BC(void) {
    u32 t;
    if (*(s8*)(g_Minigame + 0x1A2C) >= 0) {
        lbl_8036E548[0x307E] = 0;
        fn_3_B95EC();
        fn_3_5E60();
    }
    *(s8*)(g_Minigame + 0x1A2C) = -1;
    t = lbl_3_data_18910[g_Minigame[0x1A2A]];
    lbl_3_data_228[0x10] = 0;
    g_d_GameSettings[9] = t;
    g_d_GameSettings[0xA] = 0;
    if (g_d_GameSettings[9] == 0 || g_d_GameSettings[9] == 4 || g_d_GameSettings[9] == 1 || g_d_GameSettings[9] == 3) {
        g_d_GameSettings[0xA] = 1;
    }
    fn_800B0A5C_insertQueue(manageStadiumLoading, 0);
}

// fn_3_107784, size:0x17C
void fn_3_107784(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
        g_Minigame[0x1A1E] = 0;
        if (g_Minigame[0x1A1C] == 0) {
            fn_800B0A5C_insertQueue((void*)fn_80062A94, 1);
        }
        break;
    case 1:
        changeScene(1, 6);
        *(s16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
        break;
    case 2:
        fn_3_10B27C();
        if (g_Minigame[0x1A1D] == 2) {
            g_GameLogic[0x125] = 5;
        } else if (g_Minigame[0x1A1D] != 0) {
            g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
        }
        break;
    case 3:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
        }
        break;
    case 4:
        fn_80062A74();
        g_Minigame[0x1A1C] = 0;
        fn_3_5A6D4(0x29);
        break;
    case 5:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic[0x125] = 6;
        }
        break;
    case 6:
        fn_3_5A6D4(0x1E);
        break;
    }
}

// fn_3_10C58C, size:0x218
void fn_3_10C58C(void) {
    s32 i;
    u8* r;
    *(s8*)(g_Minigame + 0x18CC) = -1;
    g_Minigame[0x18D8] = 0;
    g_Minigame[0x18D0] = 0xFF;
    *(s8*)(g_Minigame + 0x18CD) = -1;
    g_Minigame[0x18D9] = 0;
    g_Minigame[0x18D1] = 0xFF;
    *(s8*)(g_Minigame + 0x18CE) = -1;
    g_Minigame[0x18DA] = 0;
    g_Minigame[0x18D2] = 0xFF;
    *(s8*)(g_Minigame + 0x18CF) = -1;
    g_Minigame[0x18DB] = 0;
    g_Minigame[0x18D3] = 0xFF;
    g_Minigame[0x1906] = 0;
    g_Minigame[0x1907] = 0;
    fn_3_10BE7C();
    for (i = 0; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x19DA + i) >= 0) {
            r = inMemRoster + i * 0xA0;
            g_Minigame[0x18CC + g_Minigame[0x1906]] = i;
            g_Minigame[0x18D8 + g_Minigame[0x1906]] = g_Minigame[0x19DA + i];
            if (g_Minigame[0x18D8 + g_Minigame[0x1906]] == 0) {
                g_Minigame[0x1907]++;
            }
            memcpy(r, lbl_8034E9A0 + *(s8*)(g_Minigame + 0x19E8 + i * 9) * 0xA0, 0xA0);
            if (g_Minigame[0x18D4 + i] != 0) {
                r[0x28] += lbl_800E86F0[0];
                r[0x29] += lbl_800E86F0[1];
                r[0x2A] += lbl_800E86F0[2];
                r[0x2B] += lbl_800E86F0[3];
                r[0x2C] += lbl_800E86F0[4];
                r[0x2F] += lbl_800E86F0[5];
                r[0x30] += lbl_800E86F0[6];
                r[0x0] += lbl_800E86F0[7];
                r[0x1] += lbl_800E86F0[8];
                r[0x2] += lbl_800E86F0[9];
                r[0x3] += lbl_800E86F0[0xA];
                r[0x4] += lbl_800E86F0[0xB];
            }
            g_Minigame[0x18D0 + g_Minigame[0x1906]] = *(s16*)(r + 0x24);
            g_Minigame[0x1906]++;
        }
    }
}

// fn_3_10F1D4, size:0x204
void fn_3_10F1D4(void) {
    u8 s = g_GameLogic[0x125];
    u8 m;
    switch (s) {
    case 0:
        changeScene(6, 6);
        g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
        *(u16*)(g_GameLogic + 0xFE) = 0;
        lbl_8036E548[0x307E] = 0;
        g_Minigame[0x19E4] = 0;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x14) {
            g_GameLogic[0x125] = s + 1;
        }
        break;
    case 2:
        fn_3_10EFAC();
        *(u16*)(g_GameLogic + 0xFE) = 0;
        break;
    case 3:
        if (lbl_3_common_bss_32724[0xBB] == 0) {
            g_GameLogic[0x125] = s + 1;
        }
        break;
    case 4:
        m = g_Minigame[0x1A2A];
        if (m >= 1 && m <= 6) {
            if (g_Minigame[0x190A] != 0) {
                g_Minigame[0x19E4] = 0;
            } else {
                g_Minigame[0x19E4] = g_d_GameSettings[0x13 + m];
            }
        }
        fn_3_5A6D4(0x1E);
        break;
    case 5:
        {
        u8* cp = g_Controls;
        cp += lbl_80366158[0x27] * 0x10;
        switch (fn_3_5B380(*(u16*)(cp + 6))) {
        case 1:
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
            break;
        case 2:
            g_GameLogic[0x125] = 2;
            break;
        }
        }
        break;
    case 6:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            fn_80062A74();
            g_Minigame[0x1A1C] = 0;
            g_GameLogic[0x125] = g_GameLogic[0x125] + 1;
        }
        break;
    case 7:
        fn_8004CC18();
        g_GameLogic[0x122] = 1;
        break;
    }
}

// fn_3_10EFAC, size:0x228
void fn_3_10EFAC(void) {
    u8* c = g_Controls + lbl_80366158[0x27] * 0x10;
    u8 t;
    if (lbl_3_common_bss_32724[0xBB] == 0) {
        if (*(u16*)(c + 6) & 0x100) {
            t = lbl_3_data_21268[*(s8*)(g_Minigame + 0x19E1)];
            if (t == 6 && g_d_GameSettings[0x12] < 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (t == 7 && g_d_GameSettings[0x12] < 2) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else {
                g_GameLogic[0x125] = 3;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (*(u16*)(c + 6) & 0x200) {
            fn_3_5B408();
            g_GameLogic[0x125] = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (*(u16*)(c + 8) & 1) {
            if (*(s8*)(g_Minigame + 0x19E1) != 0) {
                g_Minigame[0x19E1]--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (*(u16*)(c + 8) & 2) {
            if (*(s8*)(g_Minigame + 0x19E1) < 6) {
                g_Minigame[0x19E1]++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
    g_Minigame[0x1A2A] = lbl_3_data_21268[*(s8*)(g_Minigame + 0x19E1)];
    if (g_Minigame[0x1A2A] == 7) {
        g_Minigame[0x1A3C] = 1;
    } else {
        g_Minigame[0x1A3C] = 0;
    }
    lbl_3_common_bss_32724[0xB9] = g_Minigame[0x19E1];
}

#pragma dont_inline off

// fn_3_1104A8, size:0x2C
void fn_3_1104A8(void) {
    s8 i = 0;
    do {
        i++;
        g_Minigame[0x1DBC + i - 1] = 0;
    } while (i < 4);
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

// fn_3_10F564, size:0x58
s32 fn_3_10F564(void) {
    if (*(s8*)(g_Minigame + 0x1A2C) == -1) {
        if (lbl_3_data_228[0x10] != 0) {
            *(s8*)(g_Minigame + 0x1A2C) = lbl_3_data_18910[g_Minigame[0x1A2A]];
            return 0;
        }
        return 1;
    }
    return 0;
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

// fn_3_10C450, size:0x13C
void fn_3_10C450(s32 a, s32 b) {
    u8* r = inMemRoster + a * 0xA0;
    memcpy(r, lbl_8034E9A0 + b * 0xA0, 0xA0);
    if (g_Minigame[0x18D4 + a] != 0) {
        r[0x28] += lbl_800E86F0[0];
        r[0x29] += lbl_800E86F0[1];
        r[0x2A] += lbl_800E86F0[2];
        r[0x2B] += lbl_800E86F0[3];
        r[0x2C] += lbl_800E86F0[4];
        r[0x2F] += lbl_800E86F0[5];
        r[0x30] += lbl_800E86F0[6];
        r[0x0] += lbl_800E86F0[7];
        r[0x1] += lbl_800E86F0[8];
        r[0x2] += lbl_800E86F0[9];
        r[0x3] += lbl_800E86F0[0xA];
        r[0x4] += lbl_800E86F0[0xB];
    }
}

// fn_3_10754C, size:0x140
typedef struct { u8 p[0x24]; s16 v; u8 q[0x7A]; } RosT;
void fn_3_10754C(StatInput* dst) {
    u8 buf[8];
    s32 i;
    u32 k;
    fn_8006C398(dst);
    if (g_Minigame[0x1A3C] != 0 && *(s8*)(g_Minigame + 0x1908) >= 0 && *(s8*)(g_Minigame + 0x1908) < 4) {
        i = 0;
        do {
            dst->vals[i] = *(s16*)(g_Minigame + 0x1E10 + i * 2);
            i++;
        } while ((u32)i < 6);
        i = 0;
        do {
            dst->order[i] = g_Minigame[0x1E1C + i];
            i++;
        } while ((u32)i < 6);
        fn_3_1079C8(buf, 1);
        k = 0;
        do {
            if (*(s8*)(g_Minigame + 0x1908) == buf[k * 2]) {
                dst->_12 = buf[k * 2 + 1];
            }
            k++;
        } while (k < g_Minigame[0x1906]);
        {
        RosT* r = (RosT*)inMemRoster;
        dst->_13 = g_Minigame[0x1E22 + *(s8*)(g_Minigame + 0x1908)];
        dst->_14[0] = r[*(s8*)(g_Minigame + 0x18CC + *(s8*)(g_Minigame + 0x1908))].v;
        }
    }
}

// fn_3_1070A4, size:0x188
static inline void fn_3_107078_inl(void) {
    if (g_Minigame[0x18E8 + *(s8*)(g_Minigame + 0x1908)] == 1) {
        g_Minigame[0x1A3F] = 1;
    }
}

void fn_3_1070A4(void) {
    u16 t;
    u8* m;
    switch (g_GameLogic[0x125]) {
    case 0:
        m = g_Minigame;
        m[0x1A3D] = m[0x1907];
        m[0x1A3E] = 1;
        lbl_3_common_bss_32724[0xB8] = 0;
        if (m[0x1907] == 1 && m[0x18E8 + *(s8*)(m + 0x1908)] == 1) {
            m[0x1A3F] = 1;
        }
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        changeScene(1, 6);
        t = *(u16*)(g_GameLogic + 0xFE);
        if (t == *(s16*)(lbl_3_data_2137C + 2)) {
            lbl_3_common_bss_32724[0xB8] = 1;
        }
        if (t > 300) {
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (fn_3_6C938(1, 0x1100) != 0) {
            g_GameLogic[0x125] = 6;
        }
        break;
    case 6:
        g_GameLogic[0x125] = 7;
        break;
    case 7:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x3C) {
            g_GameLogic[0x125] = 8;
        }
        break;
    case 8:
        lbl_3_common_bss_34C90[0x1D1] = 0;
        lbl_3_common_bss_34C90[0x1D2] = 0;
        if (g_Minigame[0x19E7] == 1) {
            fn_3_5A6D4(0x24);
        } else {
            fn_3_5A6D4(0x22);
        }
        break;
    }
}

// fn_3_108854, size:0x194
s32 fn_3_108854(void) {
    s32 i;
    s8 c;
    if (g_Minigame[0x190B] != 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        c = *(s8*)(g_Minigame + 0x18CC + i);
        if (c >= 0 && g_Minigame[0x18D8 + i] == 0 && (*(u16*)(g_Controls + c * 0x10 + 6) & 0x1000)) {
            goto found;
        }
    }
    return 0;
found:
    g_Minigame[0x1A3B] = 1;
    *(s32*)lbl_3_common_bss_34C90 = *(s8*)(g_Minigame + 0x18CC + i);
    *(s16*)(lbl_3_common_bss_34C90 + 0xA) = 0;
    if (g_d_GameSettings[8] == 0) {
        lbl_3_common_bss_34C90[0x1D0] = 0x10;
    } else if (g_Minigame[0x1A3C] != 0) {
        lbl_3_common_bss_34C90[0x1D0] = 0xD;
    } else {
        lbl_3_common_bss_34C90[0x1D0] = 9;
    }
    lbl_3_common_bss_34C90[0x1D2] = 0;
    lbl_3_common_bss_34C90[0x1DA] = 0;
    return 1;
}

// fn_3_1079C8, size:0x1D4
void fn_3_1079C8(u8* out, s32 mode) {
    u8 order[4];
    s16 vals[4];
    u32 i;

    i = 0;
    do {
        order[i] = i;
        i++;
    } while (i < g_Minigame[0x1906]);
    switch (mode) {
    case 0:
    default:
        fn_800246D4(fn_3_107C04, order, order, 1, g_Minigame[0x1906]);
        i = 0;
        do {
            vals[i] = *(s16*)(g_Minigame + 0x1890 + i * 2);
            i++;
        } while (i < g_Minigame[0x1906]);
        break;
    case 1:
        fn_800246D4(fn_3_107BD0, order, order, 1, g_Minigame[0x1906]);
        i = 0;
        do {
            vals[i] = g_Minigame[0x1E22 + i];
            i++;
        } while (i < g_Minigame[0x1906]);
        break;
    case 2:
        fn_800246D4(fn_3_107B9C, order, order, 1, g_Minigame[0x1906]);
        i = 0;
        do {
            vals[i] = g_Minigame[0x1E26 + i];
            i++;
        } while (i < g_Minigame[0x1906]);
        break;
    }
    out[0] = order[0];
    out[1] = 0;
    for (i = 1; i < g_Minigame[0x1906]; i++) {
        out[i * 2] = order[i];
        if (vals[order[i]] == vals[order[i - 1]]) {
            out[i * 2 + 1] = out[i * 2 - 1];
        } else {
            out[i * 2 + 1] = i;
        }
    }
}

// fn_3_109CE8, size:0xA0
static inline u8* fn_3_109D88_inl(void) {
    if (g_Minigame[0x1A3C] != 0) {
        return lbl_803616CC + 0x118;
    }
    if (g_Minigame[0x1A2A] != 0) {
        return lbl_803616CC + (g_Minigame[0x1A2A] - 1) * 0x28 + 0x28;
    }
    return lbl_803616CC;
}

#pragma opt_unroll_loops off
u32 fn_3_109CE8(RankEnt* p) {
    RankEnt* e;
    s32 v;
    u32 i;
    if (g_Minigame[0x1907] == 1) {
        e = (RankEnt*)fn_3_109D88_inl();
        v = p->score;
        i = 0;
        do {
            if (v > e[i].score || (v == e[i].score && p->sub > e[i].sub)) {
                break;
            }
            i++;
        } while (i < 5);
        return i;
    }
}
#pragma opt_unroll_loops reset

// fn_3_1089E8, size:0x26C
void fn_3_1089E8(void) {
    s32 n;
    s32 row;
    s32 r;
    s32 k;
    n = 5;
    row = lbl_3_common_bss_34C90[0x1D0] - 10;
    if (g_Minigame[0x1A3C] != 0) {
        if (g_Minigame[0x1E2A] >= 6) {
            n = 4;
        } else {
            n = 3;
        }
    } else if (lbl_3_common_bss_34C90[0x1D0] == 0xC) {
        n = 4;
    }
    r = fn_3_6C938(1, 0x100);
    if (r != 0) {
        if (g_Minigame[0x1A3C] != 0) {
            if (g_Minigame[0x1E2A] >= 6) {
                if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 3) {
                    lbl_3_common_bss_34C90[0x1D2] = 8;
                } else if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 1) {
                    lbl_3_common_bss_34C90[0x1D2] = 6;
                } else {
                    lbl_3_common_bss_34C90[0x1D2] = 6;
                }
            } else {
                k = lbl_3_common_bss_34C90[0x1DA];
                if (k == 2) {
                    lbl_3_common_bss_34C90[0x1D2] = 8;
                } else {
                    lbl_3_common_bss_34C90[0x1D2] = 6;
                }
            }
        } else {
            switch ((lbl_3_data_188FC + row * 5)[*(s8*)(lbl_3_common_bss_34C90 + 0x1DA)]) {
            case 4:
                lbl_3_common_bss_34C90[0x1D2] = 8;
                break;
            default:
                lbl_3_common_bss_34C90[0x1D2] = 6;
                break;
            }
        }
        *(s32*)lbl_3_common_bss_34C90 = r - 1;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        if (lbl_3_common_bss_34C90[0x1D2] == 8) {
            fn_3_5B408();
        }
    } else if (fn_3_6C938(2, 8) != 0) {
        if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 0) {
            lbl_3_common_bss_34C90[0x1DA] = n - 1;
        } else {
            lbl_3_common_bss_34C90[0x1DA]--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (fn_3_6C938(2, 4) != 0) {
        if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) < n - 1) {
            lbl_3_common_bss_34C90[0x1DA]++;
        } else {
            lbl_3_common_bss_34C90[0x1DA] = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_3_108230, size:0x284
void fn_3_108230(void) {
    s32 row;
    s32 n;
    u8* c;
    u8 v;
    row = 0;
    n = 6;
    c = g_Controls + *(s32*)lbl_3_common_bss_34C90 * 0x10;
    if (g_d_GameSettings[8] == 0) {
        row = 2;
        n = 4;
    } else if (g_Minigame[0x1A3C] != 0) {
        row = 1;
        n = 5;
    }
    if (*(u16*)(c + 6) & 0x1000) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        lbl_3_common_bss_34C90[0x1D2] = 4;
    } else if (*(u16*)(c + 6) & 0x100) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        switch ((lbl_3_data_188E8 + row * 6)[*(s8*)(lbl_3_common_bss_34C90 + 0x1DA)]) {
        case 0:
            lbl_3_common_bss_34C90[0x1D2] = 4;
            break;
        case 1:
            lbl_3_common_bss_34C90[0x1D2] = 0xC;
            break;
        case 3:
            lbl_3_common_bss_34C90[0x1D2] = 0xA;
            break;
        case 2:
            lbl_3_common_bss_34C90[0x1D2] = 0xB;
            break;
        case 4:
            lbl_3_common_bss_34C90[0x1D2] = 6;
            break;
        case 5:
            fn_3_5B408();
            lbl_3_common_bss_34C90[0x1D2] = 8;
            break;
        }
    } else if (*(u16*)(c + 6) & 0x200) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) != 0) {
            lbl_3_common_bss_34C90[0x1DA] = 0;
        } else {
            lbl_3_common_bss_34C90[0x1D2] = 4;
        }
    } else if (*(u16*)(c + 8) & 8) {
        if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 0) {
            lbl_3_common_bss_34C90[0x1DA] = n - 1;
        } else {
            lbl_3_common_bss_34C90[0x1DA]--;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (*(u16*)(c + 8) & 4) {
        lbl_3_common_bss_34C90[0x1DA]++;
        if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) >= n) {
            lbl_3_common_bss_34C90[0x1DA] = 0;
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_3_109254, size:0x2D8
void fn_3_109254(void) {
    u8* c = g_Controls + lbl_80366158[0x27] * 0x10;
    switch (g_GameLogic[0x125]) {
    case 0:
        fn_3_5B368();
        *(u16*)(g_GameLogic + 0xFE) = 0;
        if (g_Minigame[0x1907] == 1) {
            fn_3_10952C();
            if (g_Minigame[0x1A3C] != 0) {
                g_GameLogic[0x125] = 1;
            } else {
                g_GameLogic[0x125] = 5;
            }
        } else {
            g_GameLogic[0x125] = 5;
        }
        break;
    case 1:
        if (*(u16*)(*(u8**)(g_Minigame + 0x1E04) + 0x18) != 0) {
            *(u16*)(g_GameLogic + 0xFE) = 0x1E;
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (*(u16*)(g_GameLogic + 0xFE) >= 0x1E) {
            if ((*(u16*)(c + 4) & 0x10) && (*(u16*)(c + 4) & 0x800) && (*(u16*)(c + 4) & 0x200)) {
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                *(u16*)(g_GameLogic + 0xFE) = 0;
                g_GameLogic[0x125] = 3;
            } else if (*(u16*)(c + 6) & 0x1100) {
                *(u16*)(*(u8**)(g_Minigame + 0x1E04) + 0x1A) = 1;
                g_GameLogic[0x125] = 4;
            }
        }
        break;
    case 3:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x1E && (*(u16*)(c + 6) & 0x200)) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_GameLogic[0x125] = 2;
        }
        break;
    case 4:
        if (*(u8**)(g_Minigame + 0x1E04) == NULL) {
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_GameLogic[0x125] = 5;
        }
        break;
    case 5:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x14) {
            g_GameLogic[0x125] = 6;
        }
        break;
    case 6:
        if (*(u16*)(c + 6) & 0x1100) {
            g_GameLogic[0x125] = 7;
        }
        break;
    case 7:
        if (g_Minigame[0x1A44] != 0 || g_Minigame[0x1A45] != 0 || g_Minigame[0x1A43] != 0 || g_Minigame[0x1A46] != 0) {
            if (fn_3_5B220(1) != 0) {
                g_GameLogic[0x125] = 8;
                g_Minigame[0x1A46] = 0;
            }
        } else {
            g_GameLogic[0x125] = 8;
        }
        break;
    case 8:
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 9;
        break;
    case 9:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x14) {
            g_GameLogic[0x125] = 10;
        }
        break;
    case 10:
        lbl_3_common_bss_34C90[0x1D1] = 0;
        lbl_3_common_bss_34C90[0x1D2] = 0;
        fn_3_5A6D4(0x22);
        break;
    }
}

// fn_3_10AEF0, size:0x310
void fn_3_10AEF0(void) {
    s32 i;
    u8* m;
    switch (g_GameLogic[0x125]) {
    case 0:
        fn_800203E0(7, 0);
        g_Minigame[0x1A40] = 0;
        g_Minigame[0x19A7] = lbl_3_data_21270[g_Minigame[0x1A2A]];
        g_Minigame[0x1A3E] = 0;
        lbl_8036E548[0x307E] = 1;
        lbl_8036E548[0x2D8E] = 0;
        g_GameLogic[0x125] = 1;
        if (g_d_GameSettings[8] == 0) {
            g_d_GameSettings[0x36] = g_Minigame[0x18D0 + *(s8*)(g_Minigame + 0x1908)];
        }
        break;
    case 1:
        fn_3_10C81C();
        if (*(s8*)(g_Minigame + 0x1A0F) < 0) {
            fn_3_E1370(lbl_3_data_18918[g_Minigame[0x1A2A]]);
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (fn_80016F7C() != 0) {
            g_GameLogic[0x125] = 3;
            lbl_3_common_bss_34C58[0x2C] = 0;
        }
        break;
    case 3:
        if (fn_3_90DD8() != 0) {
            g_GameLogic[0x125] = 5;
        }
        break;
    case 5:
        g_GameLogic[0x125] = 6;
        break;
    case 6:
        if (lbl_8037169C[0x12] == 0) {
            return;
        }
        if (*(u16*)(g_GameLogic + 0xFC) >= *(s16*)(lbl_3_data_18C48 + 4) ||
            (*(u16*)(g_GameLogic + 0xFC) >= *(s16*)(lbl_3_data_18C48 + 2) && fn_3_6C938(2, 0x1100) != 0)) {
            g_GameLogic[0x125] = 7;
            changeScene(3, 6);
            fn_8003A540(0);
        }
        break;
    case 7:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic[0x125] = 8;
        }
        break;
    case 8:
        lbl_8036E548[0x307A] = 1;
        m = g_Minigame;
        m[0x1A38] = 0;
        m[0x1A39] = 0;
        for (i = 0; i < 4; i++) {
            if (*(s8*)(m + 0x18CC) >= 0) {
                m[0x18E0] = i;
            }
            m++;
        }
        if (g_GameLogic[0x121] == 3) {
            minigamesSetSomePointers();
            minigamesGXStuff();
            *(s16*)(g_Minigame + 0x18A6) = 0;
        }
        if (g_Minigame[0x1A2A] == 2) {
            fn_3_5A6D4(0x23);
        } else if (g_Minigame[0x1906] >= 2) {
            if (g_GameLogic[0x121] == 8) {
                fn_3_5A6D4(0x1A);
            } else {
                fn_3_5A6D4(0x23);
            }
        } else {
            fn_3_5A6D4(0x1A);
        }
        break;
    }
    if (g_GameLogic[0x121] == 3 && g_GameLogic[0x125] >= 3) {
        fn_3_1128EC();
    }
}

// fn_3_107E80, size:0x3B0
void fn_3_107E80(void) {
    u8* c = g_Controls + *(s32*)lbl_3_common_bss_34C90 * 0x10;
    s32 row;
    s8 (*t)[5];
    s32 k;
    switch (lbl_3_common_bss_34C90[0x1D4]) {
    case 0:
        if (lbl_3_common_bss_34C90[0x1D2] == 0xB || g_d_GameSettings[7] == 6) {
            g_Minigame[0x1A1E] = 1;
            g_Minigame[0x1A1F] = 0;
            g_Minigame[0x1A20] = 0;
            g_Minigame[0x1A22] = 0;
            if (g_Minigame[0x1909] != 0) {
                g_Minigame[0x1A20] = 2;
            } else if (g_Minigame[0x1A2B] == 3) {
                g_Minigame[0x1A20] = 1;
            }
            row = g_Minigame[0x1A2A];
            if (g_GameLogic[0x11E] == 0x28) {
                row = 7;
            }
            g_Minigame[0x1A21] = 0;
            t = (s8(*)[5])(lbl_3_data_B060 + row * 0xF);
            for (k = 0; k < 5; k++) {
                if (t[g_Minigame[0x1A20]][k] >= 0) {
                    g_Minigame[0x1A21]++;
                }
            }
        }
        lbl_3_common_bss_34C90[0x1D9] = 1;
        *(s16*)(lbl_3_common_bss_34C90 + 0x12) = 0;
        lbl_3_common_bss_34C90[0x1D4] = 1;
        break;
    case 1:
        if (lbl_3_common_bss_34C90[0x1D9] == 3) {
            lbl_3_common_bss_34C90[0x1D4] = 2;
        }
        break;
    case 2:
        lbl_3_common_bss_34C90[0x1D4] = 3;
        break;
    case 3:
        if (*(s16*)(lbl_3_common_bss_34C90 + 0x12) > 0x14) {
            lbl_3_common_bss_34C90[0x1D4] = 4;
        }
        break;
    case 4:
        if (lbl_3_common_bss_32724[0xC4] == 0) {
            if (*(u16*)(c + 6) & 0x200) {
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                *(s16*)(lbl_3_common_bss_34C90 + 0x12) = 0;
                lbl_3_common_bss_34C90[0x1D4] = 5;
            } else if (lbl_3_common_bss_34C90[0x1D2] == 0xB || (g_d_GameSettings[7] == 6 && g_GameLogic[0x11E] == 0xB)) {
                if (*(u16*)(c + 8) & 2) {
                    if (g_Minigame[0x1A1E] == g_Minigame[0x1A21]) {
                        g_Minigame[0x1A1E] = 1;
                    } else {
                        g_Minigame[0x1A1E]++;
                    }
                    g_Minigame[0x1A22] = 0;
                    g_Minigame[0x1A1F] = 0x14;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (*(u16*)(c + 8) & 1) {
                    if (g_Minigame[0x1A1E] == 1) {
                        g_Minigame[0x1A1E] = g_Minigame[0x1A21];
                    } else {
                        g_Minigame[0x1A1E]--;
                    }
                    g_Minigame[0x1A22] = 1;
                    g_Minigame[0x1A1F] = 0x14;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
        break;
    case 5:
        if (*(s16*)(lbl_3_common_bss_34C90 + 0x12) > 0x14) {
            *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
            lbl_3_common_bss_34C90[0x1D2] = 1;
        }
        break;
    }
}

extern u8 g_Pitcher[];
extern u8 g_Ball[];
extern void fn_3_110634(void);

#pragma dont_inline off

// NONMATCHING 90%: inlined fn_3_1104A8 loop picks i/ptr regs swapped, port re-extsb missing
#if NONMATCHING
// fn_3_1104D4, size:0x160
void fn_3_1104D4(void) {
    s8 i;
    s8 port;
    u8* pad;
    u8* p;
    u8* mg = g_Minigame;

    fn_3_1104A8();

    p = mg;
    i = 0;
    do {
        port = p[0x18CC];
        if (port >= 0 && port < 4 && i == (s8)g_Minigame[0x1905] && p[0x18D8] != 0) {
            pad = g_Minigame + port * 0x10;
            g_Minigame[0x1DBC + port] = 1;
            memset(pad + 0x1D7C, 0, 0x10);
            switch (g_Pitcher[0x13E]) {
            case 2:
                if (mg[0x1DD0] == 0) {
                    fn_3_110634();
                    mg[0x1DD0] = 1;
                }
                if (*(s16*)(g_Pitcher + 0x126) <= *(s16*)(mg + 0x1DCC)) {
                    *(u16*)(pad + 0x1D80) |= 0x100;
                }
                break;
            case 3:
                if (*(s16*)(g_Ball + 0x1B68) < *(s16*)(g_Pitcher + 0x122) - *(s16*)(mg + 0x1DCE)) {
                    *(u16*)(pad + 0x1D80) |= 0x100;
                }
                break;
            }
        }
        i++;
        p++;
    } while (i < 4);
}
#endif

extern void fn_3_8B318(s32);
extern s32 fn_3_90928(void);
extern void fn_800189E4(void);
extern s32 fn_80035838(void* aramAddr, u8 id);
extern u8 lbl_3_data_21EC8[];

// fn_3_10F3D8, size:0x178
void fn_3_10F3D8(void) {
    u8 s = g_GameLogic[0x125];
    switch (s) {
    case 0:
        fn_3_8B318(-1);
        fn_3_10C7A4();
        lbl_3_common_bss_34C58[0x2C] = 0;
        g_GameLogic[0x125]++;
    case 1:
        if (fn_3_90928() != 0) {
            g_GameLogic[0x125]++;
        }
        break;
    case 2:
        if (fn_80035838(lbl_3_data_21EC8 + 0x1D0, 9) != 0) {
            g_GameLogic[0x125]++;
        }
        break;
    case 3:
        if (g_d_GameSettings[7] == 7) {
            if (fn_80035838(lbl_3_data_21EC8 + 0xD0, 0x11) != 0) {
                g_GameLogic[0x125]++;
            }
        } else {
            g_GameLogic[0x125] = s + 1;
        }
        break;
    default:
        fn_800189E4();
        fn_800B0A5C_insertQueue(fn_80062A94, 1);
        g_Minigame[0x1A1C] = 1;
        fn_3_5A6D4(g_Minigame[0x19DF]);
        break;
    }
}

typedef struct {
    /*0x00*/ s16 resultCoins[3];
    /*0x06*/ s16 winMarginPercent;
    /*0x08*/ s16 lossMarginPercent;
    /*0x0A*/ s16 starPercent;
    /*0x0C*/ s16 _0C[3];
    /*0x12*/ s16 bjCoins[3];
    /*0x18*/ s16 bjPoints[3];
    /*0x1E*/ s16 _1E;
} CoinRewardTable; // size: 0x20
extern CoinRewardTable lbl_3_data_607C;
extern void fn_3_161078(void);

// fn_3_106ED4, size:0x1A4
void fn_3_106ED4(void) {
    s32 i;
    if (g_d_GameSettings[7] == 6) {
        if (g_Minigame[0x19A8] == 0) {
            if (g_Minigame[0x18E8 + g_d_GameSettings[0x35]] == 1) {
                *(s16*)(g_d_GameSettings + 0x30) += *(s16*)(g_Minigame + 0x1890 + g_d_GameSettings[0x35] * 2);
            } else {
                *(s16*)(g_d_GameSettings + 0x30) += lbl_3_data_607C._1E;
            }
        }
    } else if (g_Minigame[0x19A8] != 0) {
        *(s16*)(g_d_GameSettings + 0x30) += lbl_3_data_607C._0C[1];
    } else if (g_Minigame[0x18E8 + g_d_GameSettings[0x35]] == 1) {
        for (i = 0; i < 4; i++) {
            if (g_Minigame[0x18E8 + i] > 1) {
                break;
            }
        }
        *(s16*)(g_d_GameSettings + 0x30) += lbl_3_data_607C._0C[0];
    } else if (g_d_GameSettings[0x37] != 0) {
        *(s16*)(g_d_GameSettings + 0x30) += lbl_3_data_607C._0C[2];
    }
    for (i = 0; i < 4; i++) {
        *(s16*)(g_d_GameSettings + 0x20 + i * 4) = *(s16*)(g_Minigame + 0x1890 + i * 2);
        *(s16*)(g_d_GameSettings + 0x22 + i * 4) = g_Minigame[0x18E8 + i];
    }
    fn_3_161078();
}

extern void possiblyTransitionBlackScreen(void);
extern void fn_3_5BAC(void);
extern void fn_3_1658F0(void);
extern u8 g_Scores[];
extern u8 lbl_3_common_bss_37400[];

// NONMATCHING 99%: post-loop g_Minigame/lbl_3_common_bss_32724 address loads scheduled in swapped order, r6/r7 swap
#if NONMATCHING
// fn_3_10FBE4, size:0x1E4
void fn_3_10FBE4(void) {
    s32 i;
    u8 port;
    g_GameLogic[0x121] = 2;
    fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
    fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
    g_Scores[0xAA] = 5;
    g_Scores[0xAB] = 5;
    g_Minigame[0x19DF] = 0x1C;
    g_Minigame[0x19E1] = 0;
    g_Minigame[0x19E2] = 0;
    g_Minigame[0x19E3] = 0;
    g_Minigame[0x19E6] = 1;
    g_Minigame[0x19E7] = 1;
    g_Minigame[0x1A2A] = 1;
    g_Minigame[0x1A2B] = 0;
    *(s8*)(g_Minigame + 0x1A2C) = -1;
    *(s8*)(g_Minigame + 0x1A0C) = -1;
    g_Minigame[0x19A7] = 4;
    g_Minigame[0x1A3B] = 0;
    g_Minigame[0x1A3C] = 0;
    g_Minigame[0x1A3F] = 0;
    g_Minigame[0x190A] = 0;
    *(s8*)(g_Minigame + 0x1D6D) = -1;
    g_Minigame[0x1A40] = 1;
    g_Minigame[0x19A8] = 1;
    g_Minigame[0x19A9] = 0;
    g_Minigame[0x1A3D] = 0;
    g_Minigame[0x19E0] = 0;
    g_Minigame[0x1A38] = 0;
    g_Minigame[0x1A39] = 0;
    g_Minigame[0x1A46] = 0;
    g_Minigame[0x1A1C] = 0;
    for (i = 0; i < 4; i++) {
        *(s8*)(g_Minigame + 0x19DA + i) = -1;
        *(s8*)(g_Minigame + 0x19E8 + i * 9) = -1;
        *(s8*)(g_Minigame + 0x19EA + i * 9) = -1;
        *(s8*)(g_Minigame + 0x19EB + i * 9) = -1;
        g_Minigame[0x19EF + i * 9] = 0;
        g_Minigame[0x19F0 + i * 9] = 0;
        *(s8*)(g_Minigame + 0x1A0F + i) = -1;
        *(s16*)(g_Minigame + 0x19D2 + i * 2) = 0x14;
        g_Minigame[0x1A13 + i] = 0;
        g_Minigame[0x18DC + i] = 0;
        g_Minigame[0x18D4 + i] = 0;
    }
    lbl_3_common_bss_32724[0xB9] = 0;
    g_Minigame[0x1A1B] = 0;
    if (g_d_GameSettings[8] == 0) {
        g_Minigame[0x190A] = 1;
        port = g_d_GameSettings[0x35];
        g_Minigame[0x19DA + port] = port;
        *(s16*)(lbl_3_common_bss_37400 + 0x40) = port;
        g_Minigame[0x1A2A] = g_d_GameSettings[0x33];
        fn_3_1658F0();
        g_Minigame[0x19DF] = 0x1E;
        fn_3_5A6D4(0x1B);
    } else {
        fn_3_5A6D4(0x1B);
    }
}
#endif
extern s16 fn_8006C13C(StatInput* in);
extern s16 lbl_80109410[8];

// NONMATCHING 93%: original hoists g_Minigame+0x18CC / inMemRoster+0x24 into saved regs shared with the inlined fn_3_10754C
#if NONMATCHING
// fn_3_109DE0, size:0x23C
void fn_3_109DE0(RankEnt* out) {
    StatInput stat;
    s32 lim;
    memset(out, 0, sizeof(RankEnt));
    if (g_Minigame[0x1907] == 1) {
        {
        RosT* r = (RosT*)inMemRoster;
        out->charId = r[*(s8*)(g_Minigame + 0x18CC + *(s8*)(g_Minigame + 0x1908))].v;
        }
        if (g_Minigame[0x1A3C] != 0) {
            fn_3_10754C(&stat);
            out->score = fn_8006C13C(&stat);
            out->sub = 0;
            return;
        }
        out->score = *(s16*)(g_Minigame + 0x1890 + *(s8*)(g_Minigame + 0x1908) * 2);
        if (out->score > lbl_80109410[g_Minigame[0x1A2A]]) {
            out->score = lbl_80109410[g_Minigame[0x1A2A]];
        }
        switch (g_Minigame[0x1A2A]) {
        case 1:
            out->sub = *(s16*)(g_Minigame + 0x1A8E + *(s8*)(g_Minigame + 0x1908) * 2);
            if (out->sub > 999) {
                out->sub = 999;
            }
            break;
        default:
            out->sub = 0;
            break;
        }
    }
}
#endif


extern int random_fn_3_9EE24(int max);
extern u8 lbl_3_data_18944[];
extern u8 lbl_3_data_1894C[][7];
extern u8 lbl_3_data_18978[];

// NONMATCHING 92%: settings byte 0x36 should be sign-extended once up front, saved-reg numbering differs
#if NONMATCHING
// fn_3_10F684, size:0x298
void fn_3_10F684(void) {
    s32 picks[6];
    s32 i;
    s32 n;
    s32 slot;
    s32 r;
    s32 j;

    n = 0;
    g_Minigame[0x1A2A] = g_d_GameSettings[0x33];
    g_Minigame[0x19DA + g_d_GameSettings[0x35]] = 0;
    for (i = 0; i < 4; i++) {
        if (g_d_GameSettings[0x35] == i) {
            g_Minigame[0x19E8 + i * 9] = (s8)g_d_GameSettings[0x36];
            g_Minigame[0x19E9 + i * 9] = 1;
        } else {
            g_Minigame[0x19DA + i] = 1;
            n++;
            g_Minigame[0x18DC + i] = lbl_3_data_18978[g_d_GameSettings[0x37]];
            if (n >= lbl_3_data_18944[g_Minigame[0x1A2A]]) {
                break;
            }
        }
    }

    g_Minigame[0x1906] = lbl_3_data_18944[g_Minigame[0x1A2A]] + 1;
    g_Minigame[0x1907] = 1;
    g_Minigame[0x1909] = 1;
    g_Minigame[0x1A2B] = 0;
    for (j = 0; j < 6; j++) {
        picks[j] = lbl_3_data_1894C[g_Minigame[0x1A2A]][j + 1];
    }
    slot = 0;
    for (i = 0; i < lbl_3_data_18944[g_Minigame[0x1A2A]]; i++) {
        for (;;) {
            if ((s32)g_Minigame[0x19DA + slot] == 1) {
                break;
            }
            slot++;
        }
        r = random_fn_3_9EE24(lbl_3_data_1894C[g_Minigame[0x1A2A]][0] - i);
        for (j = 0; j < 6; j++) {
            if (picks[j] != 0xFF) {
                if (r == 0) {
                    g_Minigame[0x19E8 + slot * 9] = picks[j];
                    g_Minigame[0x19E9 + slot * 9] = 1;
                    slot++;
                    picks[j] = 0xFF;
                    break;
                }
                r--;
            }
        }
    }
}
#endif

// Rebuilds the minigame player list (0x18CC/0x18D0/0x18D8) and their rosters from the
// slot setup. The original inlines it into fn_3_10F91C/fn_3_10FDC8 and fn_3_10E60C.
static inline void buildMinigamePlayersInline(void) {
    s32 i;
    u8* mg;
    mg = g_Minigame;
    for (i = 0; i < 4; i++) {
        *(s8*)(mg + 0x18CC + i) = -1;
        mg[0x18D8 + i] = 0;
        mg[0x18D0 + i] = 0xFF;
    }
    mg[0x1906] = 0;
    mg[0x1907] = 0;
    fn_3_10BE7C();
    for (i = 0; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x19DA + i) >= 0) {
            g_Minigame[0x18CC + mg[0x1906]] = i;
            g_Minigame[0x18D8 + mg[0x1906]] = g_Minigame[0x19DA + i];
            if (g_Minigame[0x18D8 + mg[0x1906]] == 0) {
                mg[0x1907]++;
            }
            fn_3_10C450(i, *(s8*)(g_Minigame + 0x19E8 + i * 9));
            g_Minigame[0x18D0 + mg[0x1906]] = *(s16*)(inMemRoster + i * 0xA0 + 0x24);
            mg[0x1906]++;
        }
    }
}

// Body of fn_3_10F91C (sets up the minigame player slots and their rosters); the original
// inlines it into fn_3_10FDC8, so it lives in a static inline that both use.
static inline void setupMinigamePlayersInline(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        fn_3_10F684();
        lbl_3_common_bss_32724[0xD8] = 0;
        g_GameLogic[0x125]++;
        break;
    }
    buildMinigamePlayersInline();
    fn_3_5A6D4(0x21);
}

void fn_3_10F91C(void) {
    setupMinigamePlayersInline();
}

extern u8 lbl_3_data_21EC4[];
extern void fn_3_15F998(void);
extern void fn_3_147DFC(void);

// fn_3_10722C, size:0x320
void fn_3_10722C(void) {
    u8 buf[8];
    u32 i;
    u32 j;
    switch (g_GameLogic[0x125]) {
    case 0:
        i = 0;
        do {
            g_Minigame[0x1E26 + i] = g_Minigame[0x1E22 + i];
            i++;
        } while (i < g_Minigame[0x1906]);
        fn_3_1079C8(buf, 0);
        i = 0;
        do {
            g_Minigame[0x1E22 + buf[i * 2]] += lbl_3_data_21EC4[buf[i * 2 + 1]] * (g_Minigame[0x1E2A] >= 6U ? 2 : 1);
            i++;
        } while (i < g_Minigame[0x1906]);
        fn_3_1079C8(g_Minigame + 0x1E08, 1);
        if (g_Minigame[0x1907] == 1) {
            *(s16*)(g_Minigame + 0x1E0E + g_Minigame[0x1A2A] * 2) = *(s16*)(g_Minigame + 0x1890 + *(s8*)(g_Minigame + 0x1908) * 2);
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (i == g_Minigame[0x1E08 + j * 2]) {
                    g_Minigame[0x18E8 + i] = g_Minigame[0x1E09 + j * 2] + 1;
                }
            }
        }
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x78) {
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x708 || fn_3_6C938(1, 0x1100) != 0) {
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_GameLogic[0x125] = 3;
        }
        break;
    case 3:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x78) {
            g_GameLogic[0x125] = 4;
        }
        break;
    case 4:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x708 || fn_3_6C938(1, 0x1100) != 0) {
            g_GameLogic[0x125] = 5;
        }
        break;
    case 5:
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 6;
        if (g_Minigame[0x1E2A] >= 6) {
            changeScene(3, 6);
        }
        break;
    case 6:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x3C) {
            g_GameLogic[0x125] = 7;
        }
        break;
    case 7:
        if (g_Minigame[0x1E2A] >= 6) {
            fn_3_15F998();
            fn_3_147DFC();
            lbl_3_common_bss_34C58[0x31] = 0;
            fn_3_5A6D4(0x27);
        } else {
            lbl_3_common_bss_34C90[0x1D1] = 0;
            lbl_3_common_bss_34C90[0x1D2] = 0;
            fn_3_5A6D4(0x22);
        }
        break;
    }
}

extern void fn_3_6AB30(void);
extern void fn_3_11CF84(void);
extern u8 lbl_3_data_6104[8];
extern u8 starMissionCompletionTracker[];

static inline void satInc16(s16* p) {
    if (*p < 0x7FFE) {
        (*p)++;
    } else {
        *p = 0x7FFF;
    }
}

// fn_3_1084B4, size:0x3A0
void fn_3_1084B4(void) {
    lbl_80366158[0x28] = 1;
    satInc16((s16*)(lbl_3_common_bss_34C90 + 0xA));
    satInc16((s16*)(lbl_3_common_bss_34C90 + 0xC));
    satInc16((s16*)(lbl_3_common_bss_34C90 + 0x12));
    switch (lbl_3_common_bss_34C90[0x1D2]) {
    case 0:
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        lbl_3_common_bss_34C90[0x1D2] = 1;
        break;
    case 1:
        lbl_3_common_bss_34C90[0x1D2] = 3;
        break;
    case 2:
        if (*(s16*)(lbl_3_common_bss_34C90 + 0xC) > 0x14) {
            lbl_3_common_bss_34C90[0x1D2] = 3;
        }
        break;
    case 3:
        fn_3_108230();
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0x12) = 0;
        lbl_3_common_bss_34C90[0x1D4] = 0;
        break;
    case 4:
        lbl_3_common_bss_34C90[0x1D9] = 1;
        lbl_3_common_bss_34C90[0x1D2] = 5;
        break;
    case 5:
        if (lbl_3_common_bss_34C90[0x1D9] == 3) {
            g_Minigame[0x1A3B] = 0;
        }
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            lbl_3_common_bss_34C90[0x1D2] = 7;
        }
        break;
    case 7:
        lbl_8036E548[0x307A] = 0;
        g_Minigame[0x1A40] = 1;
        lbl_3_common_bss_34C90[0x1D9] = 2;
        g_Minigame[0x1A3B] = 0;
        fn_3_6AB30();
        fn_3_11CF84();
        g_Minigame[0x19DF] = 0x1C;
        fn_3_5A6D4(0x1D);
        break;
    case 8:
        switch (fn_3_5B380(((u16*)(g_Controls + 6))[*(s32*)lbl_3_common_bss_34C90 * 8])) {
        case 1:
            *(u16*)(g_GameLogic + 0xFE) = 0;
            lbl_3_common_bss_34C90[0x1D2] = 9;
            break;
        case 2:
            lbl_3_common_bss_34C90[0x1D2] = 3;
            break;
        }
        break;
    case 9:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
            if (g_d_GameSettings[8] == 0) {
                fn_800203E0(0xC, (s8)lbl_3_data_6104[starMissionCompletionTracker[0x441C]]);
            } else {
                changeScene(4, 6);
            }
        }
        if (lbl_8037169C[0x13] != 0) {
            g_Minigame[0x1A40] = 1;
            lbl_3_common_bss_34C90[0x1D9] = 2;
            g_Minigame[0x1A3B] = 0;
            g_d_GameSettings[0x13] = 1;
            fn_3_11CF84();
            fn_8004CC18();
            g_GameLogic[0x122] = 1;
        }
        break;
    case 10:
        fn_3_107E80();
        break;
    case 11:
        fn_3_107E80();
        break;
    case 12:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            lbl_3_common_bss_34C90[0x1D2] = 0xD;
        }
        break;
    case 13:
        g_Minigame[0x1A38] = 1;
        fn_3_11CF84();
        lbl_8036E548[0x307A] = 0;
        fn_3_6AB30();
        g_Minigame[0x1A40] = 1;
        lbl_3_common_bss_34C90[0x1D9] = 2;
        g_Minigame[0x1A3B] = 0;
        fn_3_5A6D4(4);
        break;
    }
}

extern void fn_80011B64(s32 index);
extern s32 fn_80016710(u8 kind, s32 index);

typedef struct {
    s32 port;
    s32 timer;
} PortTimer;

// NONMATCHING 93%: original passes the s8 kind to fn_80016710 sign-extended (no u8 prototype); saved-reg numbering and the else-branch base reloads differ
#if NONMATCHING
// fn_3_10C81C, size:0x404
void fn_3_10C81C(void) {
    PortTimer ents[4];
    s32 count;
    s32 n;
    s32 i;
    s32 j;
    s32 k;
    s32 done;
    s8 cur;
    s32 index;
    s8 a;

    count = 4;
    for (;;) {
        if (g_d_GameSettings[7] == 2) {
            count = 1;
        }
        n = 0;
        for (i = 0; i < count; i++) {
            ents[i].port = -1;
            if (*(s8*)(g_Minigame + 0x1A0C) != i) {
                a = g_Minigame[0x19E8 + i * 9];
                if (a != -1 && (a != *(s8*)(g_Minigame + 0x19EA + i * 9) || *(s8*)(g_Minigame + 0x19EC + i * 9) != g_Minigame[0x1A17 + i])) {
                    g_Minigame[0x19EF + i * 9] = 0;
                    if (*(u16*)(g_Minigame + 0x19D2 + i * 2) >= 0x14 || g_Minigame[0x19DE] == 4) {
                        ents[n].port = i;
                        ents[n].timer = *(u16*)(g_Minigame + 0x19D2 + i * 2);
                        n++;
                        g_Minigame[0x19ED + i * 9] = g_Minigame[0x1A17 + i];
                    }
                }
            }
        }
        for (i = 0; i < n - 1; i++) {
            for (j = i + 1; j < n; j++) {
                s32 t = ents[i].timer;
                if (t < ents[j].timer) {
                    s32 p = ents[i].port;
                    ents[i].port = ents[j].port;
                    ents[i].timer = ents[j].timer;
                    ents[j].port = p;
                    ents[j].timer = t;
                }
            }
        }
        *(s8*)(g_Minigame + 0x1A0F) = -1;
        *(s8*)(g_Minigame + 0x1A10) = -1;
        *(s8*)(g_Minigame + 0x1A11) = -1;
        *(s8*)(g_Minigame + 0x1A12) = -1;
        k = 0;
        if (*(s8*)(g_Minigame + 0x1A0C) >= 0) {
            g_Minigame[0x1A0F] = g_Minigame[0x1A0C];
            k = 1;
        }
        {
            u8* dst = g_Minigame + k;
            PortTimer* src = ents;
            for (i = n; i > 0; i--) {
                dst[0x1A0F] = src->port;
                src++;
                dst++;
            }
        }
        if (*(s8*)(g_Minigame + 0x1A0F) < 0) {
            break;
        }
        cur = g_Minigame[0x1A0F];
        index = cur;
        if (g_d_GameSettings[7] == 2) {
            index = 9;
        }
        if (g_Minigame[0x1A1B] == 0) {
            g_Minigame[0x1A1B] = 1;
            fn_80011B64(index);
        }
        if (*(s8*)(g_Minigame + 0x19EB + cur * 9) >= 0) {
            done = fn_80016710(*(s8*)(g_Minigame + 0x19EB + cur * 9), index);
        } else {
            done = fn_80016710(*(s8*)(g_Minigame + 0x19E8 + cur * 9), index);
        }
        if (done != 0) {
            g_Minigame[0x19EA + cur * 9] = g_Minigame[0x19EB + cur * 9];
            *(s8*)(g_Minigame + 0x19EB + cur * 9) = -1;
            lbl_8036E548[0x2D77] = 0;
            g_Minigame[0x19EC + cur * 9] = g_Minigame[0x19ED + cur * 9];
            *(s8*)(g_Minigame + 0x1A0C) = -1;
            *(s8*)(g_Minigame + 0x1A0F) = -1;
            g_Minigame[0x1A13 + cur] = 0;
            g_Minigame[0x1A1B] = 0;
            fn_3_E1370(3);
            continue;
        }
        if (*(s8*)(g_Minigame + 0x19EB + cur * 9) < 0) {
            g_Minigame[0x19EB + cur * 9] = g_Minigame[0x19E8 + cur * 9];
        }
        *(s8*)(g_Minigame + 0x19EA + cur * 9) = -1;
        g_Minigame[0x1A0C] = cur;
        break;
    }
    for (i = 0; i < 4; i++) {
        if (g_Minigame[0x1A13 + i] != 0 && *(s8*)(g_Minigame + 0x19E8 + i * 9) == *(s8*)(g_Minigame + 0x19EA + i * 9)) {
            g_Minigame[0x1A13 + i] = 0;
        }
    }
}
#endif

extern void fn_800189B8(void);
extern void fn_3_908E8(void);
extern s32 fn_3_90860(void);
extern s32 fn_3_90A18(void);
extern void fn_80018B74(void);
extern s32 fn_80020388(void);
extern void fn_3_BF070(void);

// fn_3_10B8D0, size:0x5AC
void fn_3_10B8D0(void) {
    s32 i;
    u32 t;
    switch (g_GameLogic[0x125]) {
    case 0:
        lbl_8036E548[0x307E] = 0;
        if (g_Minigame[0x1A3C] == 0 || g_Minigame[0x1E2A] <= 1) {
            if (g_Minigame[0x1A38] == 0) {
                fn_80062A74();
                fn_800189B8();
                if (g_d_GameSettings[7] == 7) {
                    fn_80035B50(0x11);
                }
                fn_80035B50(9);
                fn_3_908E8();
            }
        }
        g_Minigame[0x1A1C] = 0;
        g_Minigame[0x1A41] = 0;
        g_Minigame[0x1909] = 0;
        g_Minigame[0x19AA] = 0;
        *(s8*)(g_Minigame + 0x1908) = -1;
        g_Minigame[0x1A1D] = 0;
        g_Minigame[0x1A23] = 0;
        g_Minigame[0x1A24] = 2;
        g_Minigame[0x1A46] = 0;
        if (g_d_GameSettings[8] == 0) {
            g_Minigame[0x1A24] = 0;
        }
        g_d_GameSettings[0x3A] = g_Minigame[0x1A2B];
        lbl_8037169C[0x15] = 0;
        lbl_3_common_bss_34C58[0x2C] = 0;
        if (g_Minigame[0x1907] != 1 || g_Minigame[0x1A3C] != 0) {
            g_Minigame[0x1909] = 1;
            g_Minigame[0x1A2B] = 0;
        }
        if (g_Minigame[0x1907] == 1) {
            for (i = 0; i < 4; i++) {
                if (g_Minigame[0x18D8 + i] == 0) {
                    g_Minigame[0x1908] = i;
                    break;
                }
            }
        }
        if (g_d_GameSettings[7] == 6) {
            g_d_GameSettings[0x33] = 0;
        } else {
            g_d_GameSettings[0x33] = g_Minigame[0x1A2A];
        }
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125]++;
        if (g_Minigame[0x1A38] != 0 && g_Minigame[0x1A3C] == 0) {
            changeScene(1, 6);
            g_GameLogic[0x125] = 2;
        }
        break;
    case 1:
        if (fn_80035838(lbl_3_data_21EC8 + (g_Minigame[0x1A2A] + 6) * 0x10, 0x11) != 0) {
            changeScene(1, 6);
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_GameLogic[0x125]++;
        }
        break;
    case 2:
        if (g_Minigame[0x1A38] != 0 && g_Minigame[0x1A3C] == 0) {
            g_GameLogic[0x125] = 8;
        } else if (fn_3_90860() != 0) {
            lbl_3_common_bss_34C58[0x2C] = 0;
            g_GameLogic[0x125]++;
        }
        break;
    case 3:
        g_d_GameSettings[9] = lbl_3_data_18910[g_Minigame[0x1A2A]];
        if (fn_3_90A18() != 0) {
            g_GameLogic[0x125]++;
        }
        break;
    case 4:
        fn_80018B74();
        g_GameLogic[0x125]++;
    case 5:
        *(s8*)(g_Minigame + 0x1A2C) = -1;
        t = lbl_3_data_18910[g_Minigame[0x1A2A]];
        lbl_3_data_228[0x10] = 0;
        g_d_GameSettings[9] = t;
        g_d_GameSettings[0xA] = 0;
        if (g_d_GameSettings[9] == 0 || g_d_GameSettings[9] == 4 || g_d_GameSettings[9] == 1 || g_d_GameSettings[9] == 3) {
            g_d_GameSettings[0xA] = 1;
        }
        fn_800B0A5C_insertQueue(manageStadiumLoading, 0);
        g_GameLogic[0x125]++;
        break;
    case 6:
        if (fn_3_10F564() == 0) {
            g_GameLogic[0x125]++;
        }
        break;
    case 7:
        if (fn_80020388() != 0) {
            g_GameLogic[0x125]++;
        }
        break;
    case 8:
        if (g_Minigame[0x1A1D] != 0) {
            changeScene(3, 6);
            if (g_Minigame[0x1A1D] == 2) {
                g_GameLogic[0x125] = 10;
            } else {
                g_GameLogic[0x125] = 9;
            }
        }
        break;
    case 9:
        if (lbl_8037169C[0x13] != 0) {
            if (g_d_GameSettings[7] == 6) {
                g_Scores[0xAB] = g_Scores[0xAA] = g_Minigame[0x1A24] * 2 + 1;
                fn_3_5A6D4(5);
            } else {
                fn_3_5A6D4(4);
            }
            fn_3_BF070();
        }
        break;
    case 10:
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic[0x125] = 11;
        }
        break;
    case 11:
        g_Minigame[0x1A38] = 0;
        fn_3_10B200();
        break;
    }
    if (g_GameLogic[0x125] >= 2 && g_Minigame[0x1A1D] == 0) {
        fn_3_10B27C();
    }
}

extern u8 lbl_800E854C[12];
extern u8 lbl_3_data_609C[][6];
extern u8 lbl_3_data_212A4[][6];

// NONMATCHING 99%: assignment loop zero-inits k with li instead of copying i (one mr)
#if NONMATCHING
// fn_3_10BE7C, size:0x5D4
void fn_3_10BE7C(void) {
    s32 m;
    s32 n;
    s32 row;
    s32 k;
    s32 j;
    s32 pool[12];
    u8 mode;
    s32 taken[4];
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Minigame[0x18D8 + i] == 0 && *(s8*)(g_Minigame + 0x19DA + i) >= 0) {
            taken[i] = *(s8*)(g_Minigame + 0x19E8 + i * 9);
        } else {
            taken[i] = -1;
        }
    }

    if (g_d_GameSettings[7] == 6 && g_d_GameSettings[8] == 0) {
        for (i = 0; i < lbl_3_data_1894C[0][0]; i++) {
            pool[i] = lbl_3_data_1894C[0][i + 1];
        }
    } else if (g_Minigame[0x1A3C] != 0) {
        for (i = 0; i < 12; i++) {
            pool[i] = lbl_800E854C[i];
        }
        fn_3_9E078(pool, 12, 0);
    } else {
        mode = g_Minigame[0x1A2A];
        if ((mode == 1 || mode == 3) && *(s8*)(g_Minigame + 0x1908) >= 0) {
            return;
        }
        n = 6;
        if (g_d_GameSettings[8] == 0) {
            if (mode == 2) {
                row = g_Minigame[0x1A2B];
            } else if (mode == 4) {
                row = g_Minigame[0x1A2B] + 3;
            } else if (mode == 5) {
                row = g_Minigame[0x1A2B] + 6;
            } else if (mode == 6) {
                row = g_Minigame[0x1A2B] + 9;
            } else {
                row = 0;
            }
            n = 0;
            for (i = 0; i < 6; i++) {
                pool[i] = lbl_3_data_609C[row][i];
                if (pool[i] != 0xFF) {
                    n++;
                }
            }
        } else {
            if (mode == 2) {
                if (g_Minigame[0x1A2B] == 3) {
                    row = -1;
                } else {
                    row = g_Minigame[0x1A2B] + 1;
                }
            } else if (mode == 4) {
                row = g_Minigame[0x1A2B] + 5;
            } else if (mode == 5) {
                row = g_Minigame[0x1A2B] + 9;
            } else if (mode == 6) {
                row = g_Minigame[0x1A2B] + 0xD;
            } else {
                row = 0;
            }
            if (row < 0) {
                for (i = 0; i < 6; i++) {
                    pool[i] = -1;
                }
            } else {
                for (i = 0; i < 6; i++) {
                    pool[i] = lbl_3_data_212A4[row][i];
                }
            }
        }
        fn_3_9E078(pool, n, 0);
    }

    i = 0;
    k = 0;
    for (; i < 4; i++) {
        if (*(s8*)(g_Minigame + 0x19DA + i) != 0 && *(s8*)(g_Minigame + 0x19E9 + i * 9) == 0) {
            for (m = k; k < 6; k++, m++) {
                // skip characters already taken by a human slot
                for (j = 0; j < 4; j++) {
                    if (pool[m] == taken[j] && pool[m] >= 0) {
                        break;
                    }
                }
                if (j >= 4) {
                    break;
                }
            }
            g_Minigame[0x19E8 + i * 9] = pool[m];
            *(s16*)(g_Minigame + 0x19D2 + i * 2) = 0x14;
            g_Minigame[0x1A17 + i] = lbl_8034E9A0[pool[m] * 0xA0 + 0x26] * 2 + lbl_8034E9A0[pool[m] * 0xA0 + 0x27];
            k++;
        }
    }
}
#endif

extern u8 lbl_3_data_18920[][5];

// NONMATCHING 99%: in case 7 the original reuses the loop counter register as the zero for the 0x1A3D/0x1A3F/0x307E stores
#if NONMATCHING
// fn_3_108C54, size:0x600
void fn_3_108C54(void) {
    u32 i;
    s32 j;
    u8* src;

    satInc16((s16*)(lbl_3_common_bss_34C90 + 0xA));
    satInc16((s16*)(lbl_3_common_bss_34C90 + 0xC));
    satInc16((s16*)(lbl_3_common_bss_34C90 + 0x12));
    switch (lbl_3_common_bss_34C90[0x1D2]) {
    case 0:
        if (g_Minigame[0x1909] != 0 || g_d_GameSettings[0x13 + g_Minigame[0x1A2A]] == 0) {
            lbl_3_common_bss_34C90[0x1D0] = 0xC;
        } else if (g_Minigame[0x1A44] != 0) {
            lbl_3_common_bss_34C90[0x1D0] = 0xB;
        } else {
            lbl_3_common_bss_34C90[0x1D0] = 0xA;
        }
        if (g_Minigame[0x1A3C] != 0) {
            if (g_Minigame[0x1E2A] >= 6) {
                lbl_3_common_bss_34C90[0x1D0] = 0xF;
            } else {
                lbl_3_common_bss_34C90[0x1D0] = 0xE;
            }
        }
        *(s16*)(lbl_3_common_bss_34C90 + 0xA) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        lbl_3_common_bss_34C90[0x1DA] = 0;
        lbl_3_common_bss_34C90[0x1D2] = 1;
        break;
    case 1:
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        lbl_3_common_bss_34C90[0x1D2] = 2;
        break;
    case 2:
        if (*(s16*)(lbl_3_common_bss_34C90 + 0xC) >= 0x14) {
            lbl_3_common_bss_34C90[0x1D2] = 3;
        }
        break;
    case 3:
        fn_3_1089E8();
        *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
        *(s16*)(lbl_3_common_bss_34C90 + 0x12) = 0;
        break;
    case 6:
        changeScene(3, 6);
        if (lbl_8037169C[0x13] != 0) {
            lbl_3_common_bss_34C90[0x1D2] = 7;
        }
        break;
    case 7:
        if (g_Minigame[0x1A3C] != 0) {
            if (g_Minigame[0x1E2A] >= 6) {
                if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 0) {
                    g_Minigame[0x1A38] = 1;
                    memset(g_Minigame + 0x1E04, 0, 0x28);
                    i = 0;
                    g_Minigame[0x1A3D] = 0;
                    g_Minigame[0x1A3F] = 0;
                    lbl_8036E548[0x307E] = 0;
                    do {
                        g_Minigame[0x1E1C + i] = i + 1;
                        i++;
                    } while (i < 6);
                    fn_3_9DC18(g_Minigame + 0x1E1C, 6, 0);
                    fn_3_5A6D4(0x28);
                    fn_3_5A6D4(0x29);
                } else if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 1) {
                    g_Minigame[0x19DF] = 0x1E;
                    fn_3_5A6D4(0x1D);
                } else {
                    g_Minigame[0x19DF] = 0x1C;
                    fn_3_5A6D4(0x1D);
                }
                fn_3_FBD70();
                fn_3_FBD58();
            } else if (*(s8*)(lbl_3_common_bss_34C90 + 0x1DA) == 0) {
                fn_3_5A6D4(0x29);
            } else {
                fn_3_5A6D4(0x1D);
            }
        } else {
            switch ((lbl_3_data_188FC + lbl_3_common_bss_34C90[0x1D0] * 5 - 50)[*(s8*)(lbl_3_common_bss_34C90 + 0x1DA)]) {
            case 0:
                g_Minigame[0x1A38] = 1;
                fn_3_5A6D4(4);
                break;
            case 1:
                g_Minigame[0x19DF] = 0x1E;
                fn_3_5A6D4(0x1D);
                break;
            case 2:
                g_Minigame[0x19DF] = 0x1E;
                g_Minigame[0x19E0] = 1;
                fn_3_5A6D4(0x1D);
                break;
            case 3:
                g_Minigame[0x19DF] = 0x1C;
                fn_3_5A6D4(0x1D);
                break;
            case 5:
                g_Minigame[0x1A38] = 1;
                g_Minigame[0x1A2B]++;
                g_Minigame[0x1A39] = 1;
                fn_3_5A6D4(0x21);
                break;
            }
        }
        fn_3_11CF84();
        if (g_Minigame[0x1A39] != 0) {
            fn_3_10BE7C();
            g_Minigame[0x1906] = lbl_3_data_18920[g_Minigame[0x1A2A]][g_Minigame[0x1A2B]];
            for (j = 0; j < 4; j++) {
                if (g_Minigame[0x18D8 + j] != 0) {
                    if (g_Minigame[0x1906] == 1) {
                        *(s8*)(g_Minigame + 0x18CC + j) = -1;
                    } else {
                        src = lbl_8034E9A0 + *(s8*)(g_Minigame + 0x19E8 + *(s8*)(g_Minigame + 0x18CC + j) * 9) * 0xA0;
                        memcpy(inMemRoster + *(s8*)(g_Minigame + 0x18CC + j) * 0xA0, src, 0xA0);
                        g_Minigame[0x1A17 + j] = src[0x26] * 2 + src[0x27];
                        g_Minigame[0x18D0 + j] = *(s16*)(inMemRoster + *(s8*)(g_Minigame + 0x18CC + j) * 0xA0 + 0x24);
                    }
                }
            }
        }
        g_Minigame[0x1A40] = 1;
        g_Minigame[0x19A9] = 0;
        fn_3_15F998();
        fn_3_147DFC();
        lbl_8036E548[0x307A] = 0;
        lbl_3_common_bss_34C90[0x1D9] = 2;
        break;
    case 8:
        switch (fn_3_5B380(((u16*)(g_Controls + 6))[*(s32*)lbl_3_common_bss_34C90 * 8])) {
        case 1:
            *(u16*)(g_GameLogic + 0xFE) = 0;
            lbl_3_common_bss_34C90[0x1D2] = 9;
            break;
        case 2:
            lbl_3_common_bss_34C90[0x1D2] = 3;
            break;
        }
        break;
    case 9:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
            changeScene(4, 6);
        }
        if (lbl_8037169C[0x13] != 0) {
            g_Minigame[0x1A40] = 1;
            lbl_3_common_bss_34C90[0x1D9] = 2;
            fn_3_15F998();
            fn_3_147DFC();
            fn_3_11CF84();
            fn_8004CC18();
            g_GameLogic[0x122] = 1;
        }
        break;
    }
}
#endif

// fn_3_10B27C, size:0x654
void fn_3_10B27C(void) {
    s32 row;
    s8 (*t)[5];
    s32 k;

    if (*(u16*)(g_GameLogic + 0xFE) == 1) {
        g_Minigame[0x1A1E] = 0;
        g_Minigame[0x1A1F] = 0;
        g_Minigame[0x1A20] = 0;
        g_Minigame[0x1A22] = 0;
        if (g_Minigame[0x1909] != 0) {
            g_Minigame[0x1A20] = 2;
        } else if (g_Minigame[0x1A2B] == 3) {
            g_Minigame[0x1A20] = 1;
        }
        row = g_Minigame[0x1A2A];
        if (g_GameLogic[0x11E] == 0x28) {
            row = 7;
        }
        g_Minigame[0x1A21] = 0;
        t = (s8(*)[5])(lbl_3_data_B060 + row * 0xF);
        for (k = 0; k < 5; k++) {
            if (t[g_Minigame[0x1A20]][k] >= 0) {
                g_Minigame[0x1A21]++;
            }
        }
    }
    if (lbl_8037169C[0x12] == 0) {
        return;
    }
    if (g_Minigame[0x1A1F] != 0) {
        g_Minigame[0x1A1F]--;
        return;
    }
    if (g_Minigame[0x1A1E] == 0) {
        if (fn_3_6C938(1, 0x200) != 0) {
            if (g_Minigame[0x1A3C] == 0 || g_GameLogic[0x11E] == 0x28) {
                g_Minigame[0x1A1D] = 2;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        } else if ((g_GameLogic[0x125] >= 8 || g_GameLogic[0x11E] == 0x28) && fn_3_6C938(1, 0x100) != 0) {
            if (g_d_GameSettings[7] == 6) {
                if (g_Minigame[0x1A23] == 0) {
                    g_Minigame[0x1A1D] = 1;
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
            } else {
                g_Minigame[0x1A1D] = 1;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            }
        } else if (fn_3_6C938(2, 0x20) != 0) {
            g_Minigame[0x1A1E] = 1;
            g_Minigame[0x1A22] = 0;
            g_Minigame[0x1A1F] = 0x1E;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (g_d_GameSettings[7] == 6 && g_d_GameSettings[8] != 0) {
            if (fn_3_6C938(2, 8) != 0 && g_Minigame[0x1A23] == 1) {
                g_Minigame[0x1A23] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (fn_3_6C938(2, 4) != 0 && g_Minigame[0x1A23] == 0) {
                g_Minigame[0x1A23] = 1;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (g_Minigame[0x1A23] == 1) {
                if (fn_3_6C938(2, 1) != 0) {
                    if (g_Minigame[0x1A24] == 0) {
                        g_Minigame[0x1A24] = 4;
                    } else {
                        g_Minigame[0x1A24]--;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                } else if (fn_3_6C938(2, 2) != 0) {
                    if (g_Minigame[0x1A24] == 4) {
                        g_Minigame[0x1A24] = 0;
                    } else {
                        g_Minigame[0x1A24]++;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else {
        if ((g_GameLogic[0x125] >= 8 || g_GameLogic[0x11E] == 0x28) && fn_3_6C938(0, 0x100) != 0) {
            g_Minigame[0x1A1D] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (fn_3_6C938(2, 0x220) != 0) {
            g_Minigame[0x1A1E] = 0;
            g_Minigame[0x1A22] = 0;
            g_Minigame[0x1A1F] = 0x1E;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (g_Minigame[0x1A21] > 1) {
            if (fn_3_6C938(2, 2) != 0) {
                if (g_Minigame[0x1A1E] == g_Minigame[0x1A21]) {
                    g_Minigame[0x1A1E] = 1;
                } else {
                    g_Minigame[0x1A1E]++;
                }
                g_Minigame[0x1A22] = 0;
                g_Minigame[0x1A1F] = 0x14;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            } else if (fn_3_6C938(2, 1) != 0) {
                if (g_Minigame[0x1A1E] == 1) {
                    g_Minigame[0x1A1E] = g_Minigame[0x1A21];
                } else {
                    g_Minigame[0x1A1E]--;
                }
                g_Minigame[0x1A22] = 1;
                g_Minigame[0x1A1F] = 0x14;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    }
}

extern void fn_3_112BD8(void);
extern void fn_3_1160BC(void);
extern void fn_3_1324E8(void);
extern void fn_3_141A30(void);
extern void fn_3_1471C4(void);
extern void fn_3_13C468(void);
extern void fn_3_10E60C(void);
extern void fn_3_10A0A0(void);

// fn_3_10FDC8, size:0x6E0
void fn_3_10FDC8(void) {
    s32 order[4];
    s32 i;
    u8 m;

    if (g_Minigame[0x1A3B] != 0) {
        fn_3_1084B4();
        return;
    }
    g_GameLogic[0x12D] = 0;
    g_GameLogic[0x12E] = 0;
    satInc16((s16*)(g_Ball + 0x1B64));
    switch (g_GameLogic[0x11E]) {
    case 27:
        fn_3_10FB74();
        break;
    case 28:
        fn_3_10F1D4();
        break;
    case 29:
        fn_3_10F3D8();
        break;
    case 30:
        fn_3_10E60C();
        break;
    case 33:
        fn_3_10B8D0();
        break;
    case 5:
        fn_3_10AEF0();
        break;
    case 35:
        for (i = 0; i < 4; i++) {
            order[i] = -1;
        }
        for (i = 0; i < 4; i++) {
            if (*(s8*)(g_Minigame + 0x18CC + i) >= 0) {
                order[i] = i;
            }
        }
        fn_3_9E078(order, g_Minigame[0x1906], 0);
        for (i = 0; i < 4; i++) {
            g_Minigame[0x18E0 + i] = order[i];
        }
        fn_3_5A6D4(0x1A);
        break;
    case 14:
        fn_3_10A0A0();
        break;
    case 36:
        fn_3_109254();
        break;
    case 34:
        fn_3_108C54();
        break;
    case 38:
        fn_3_10722C();
        break;
    case 40:
        fn_3_107784();
        break;
    case 41:
        switch (g_GameLogic[0x125]) {
        case 0:
            g_Minigame[0x1A2A] = g_Minigame[0x1E1C + g_Minigame[0x1E2A]++];
            changeScene(1, 6);
            g_GameLogic[0x125] = 1;
            break;
        case 1:
            // TODO type: pointer field at g_Minigame+0x1E04
            if (*(u16*)(*(u8**)(g_Minigame + 0x1E04) + 0x1A) != 0) {
                changeScene(3, 6);
                g_GameLogic[0x125] = 2;
            }
            break;
        case 2:
            if (lbl_8037169C[0x13] != 0) {
                g_GameLogic[0x125] = 3;
            }
            break;
        case 3:
            g_GameLogic[0x125] = 4;
            break;
        case 4:
            fn_3_5A6D4(0x21);
            break;
        }
        break;
    case 39:
        fn_3_1070A4();
        break;
    case 37:
        setupMinigamePlayersInline();
        break;
    default:
        m = g_Minigame[0x1A2A];
        if (m == 1) {
            fn_3_112BD8();
        } else if (m == 2) {
            fn_3_1160BC();
        } else if (m == 3) {
            fn_3_1324E8();
        } else if (m == 4) {
            fn_3_141A30();
        } else if (m == 5) {
            fn_3_1471C4();
        } else if (m == 6) {
            fn_3_13C468();
        }
        if (*(u32*)(g_Minigame + 0x17C4) == 0x258) {
            fn_3_90064(0x2FD);
        }
        break;
    }
}

extern u8 lbl_800E8558[];

// NONMATCHING 90%: inlines fn_3_109DE0 (itself NONMATCHING; differences are inside that inline: base hoisting)
#if NONMATCHING
// fn_3_10952C, size:0x7BC
void fn_3_10952C(void) {
    RankEnt score;
    StatInput cur;
    StatInput* best;
    RankEnt* tbl;
    u32 rank;
    u32 i;
    u8 chara;
    s16 bestTotal;

    g_Minigame[0x1E03] = 5;
    if (g_Minigame[0x1907] != 1) {
        return;
    }
    if (!(g_Minigame[0x1A3C] != 0 || (g_Minigame[0x1A2A] != 4 && g_Minigame[0x1A2A] != 5 && g_Minigame[0x1A2A] != 6) ||
          g_Minigame[0x18E8 + *(s8*)(g_Minigame + 0x1908)] == 1)) {
        return;
    }
    fn_3_109DE0(&score);
    rank = fn_3_109CE8(&score);
    g_Minigame[0x1E03] = rank;
    if (rank < 5) {
        tbl = (RankEnt*)fn_3_109D88_inl();
        for (i = 4; i > rank; i--) {
            memcpy(&tbl[i], &tbl[i - 1], sizeof(RankEnt));
        }
        memcpy(&tbl[rank], &score, sizeof(RankEnt));
        g_Minigame[0x1A43] = rank + 1;
    }
    if (g_Minigame[0x1A3C] != 0) {
        fn_3_10754C(&cur);
        chara = lbl_800E8558[cur._14[0] * 6 + 2];
        best = (StatInput*)(lbl_803616CC + chara * 0x16 + 0x140);
        bestTotal = fn_8006C13C(best);
        if (fn_8006C13C(&cur) > bestTotal) {
            fn_3_10754C(best);
            g_Minigame[0x1A46] = 1;
        } else {
            bestTotal = fn_8006C13C(best);
            if (fn_8006C13C(&cur) == bestTotal && cur._12 < best->_12) {
                fn_3_10754C(best);
                g_Minigame[0x1A46] = 1;
            }
        }
        if (3 - *(s8*)(lbl_803616CC + chara + 0x400) > cur._12) {
            lbl_803616CC[chara + 0x400] = 3 - cur._12;
            g_Minigame[0x1A46] = 1;
        }
    }
}
#endif

extern void fn_80050FE8(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4, s32 lockMode);
extern void fn_8004FDA0(s32 id);
extern void fn_80050138(s32 byId, s32 entry0, s32 entry1, s32 entry2, s32 entry3, s32 any);
extern s16 fn_80050760(s32 p, s32 unused, s32 pressed, u16 dirs, s32 mode);
extern void fn_800506E8(s8 owner, s32 entry, s32 set);
extern void fn_3_972C8(void);
extern void fn_3_60768(void);
extern u8 lbl_803C6714[];
extern void fn_3_10CC20(void);

// NONMATCHING 95%: saved-reg numbering of the loop walkers; original passes the u8 port to fn_800506E8 without extsb (no s8 prototype)
#if NONMATCHING
// fn_3_10E60C, size:0x9A0
void fn_3_10E60C(void) {
    s32 i;
    s32 j;
    u8 port;
    u8 state;

    if (g_GameLogic[0x125] <= 2) {
        for (i = 0; i < 4; i++) {
            g_Minigame[0x19F0 + i * 9] = g_Minigame[0x19EF + i * 9];
            g_Minigame[0x19EF + i * 9] = 1;
        }
    }
    switch (g_GameLogic[0x125]) {
    case 0:
        for (i = 0; i < 4; i++) {
            if ((s32)g_Minigame[0x19DA + i] == 1) {
                *(s8*)(g_Minigame + 0x19DA + i) = -1;
            }
            g_Minigame[0x18DC + i] = 0;
            g_Minigame[0x1A13 + i] = 1;
        }
        if (g_Minigame[0x190A] != 0) {
            fn_80050FE8(1, 1, 1, 1, 1, 0);
            for (i = 0; i < 0x36; i++) {
                if ((s32)starMissionCompletionTracker[0x31 + i * 0x34] != 1) {
                    fn_8004FDA0(i);
                }
            }
            g_Minigame[0x19E8 + *(s16*)(lbl_3_common_bss_37400 + 0x40) * 9] = g_d_GameSettings[0x36];
        } else {
            fn_80050FE8(1, 1, 1, 1, 1, 1);
            for (i = 0; i < 4; i++) {
                if (*(s8*)(g_Minigame + 0x19DA + i) < 0) {
                    *(s8*)(g_Minigame + 0x19E8 + i * 9) = -1;
                }
            }
        }
        // remove duplicate character picks
        for (i = 0; i < 3; i++) {
            if (*(s8*)(g_Minigame + 0x19E8 + i * 9) >= 0) {
                for (j = i + 1; j < 4; j++) {
                    if (*(s8*)(g_Minigame + 0x19E8 + i * 9) == *(s8*)(g_Minigame + 0x19E8 + j * 9)) {
                        *(s8*)(g_Minigame + 0x19E8 + j * 9) = -3;
                    }
                }
            }
        }
        fn_80050138(1, *(s8*)(g_Minigame + 0x19E8), *(s8*)(g_Minigame + 0x19F1), *(s8*)(g_Minigame + 0x19FA),
                    *(s8*)(g_Minigame + 0x1A03), 1);
        for (i = 0; i < 4; i++) {
            g_Minigame[0x19E9 + i * 9] = 0;
            *(s16*)(g_Minigame + 0x19D2 + i * 2) = 0x14;
        }
        lbl_8036E548[0x307E] = 0;
        lbl_8036E548[0x2D77] = 0;
        lbl_8036E548[0x307A] = 5;
        *(s16*)(g_Minigame + 0x18A2) = -1;
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_Minigame[0x19DE] = 0;
        g_Minigame[0x19E2] = 0;
        g_Minigame[0x19E3] = 0;
        if (g_Minigame[0x1A1C] == 0) {
            fn_800B0A5C_insertQueue(fn_80062A94, 1);
        }
        changeScene(1, 6);
        g_GameLogic[0x125]++;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFE) == 1) {
            for (i = 0; i < 4; i++) {
                if (*(s8*)(g_Minigame + 0x19DA + i) == 0) {
                    g_Minigame[0x19E8 + i * 9] = fn_80050760(i, 0, 0, 0, 0);
                    g_Minigame[0x19EE + i * 9] = 0;
                    g_Minigame[0x1A17 + i] = lbl_8034E9A0[*(s8*)(g_Minigame + 0x19E8 + i * 9) * 0xA0 + 0x26] * 2 +
                                             lbl_8034E9A0[*(s8*)(g_Minigame + 0x19E8 + i * 9) * 0xA0 + 0x27];
                    g_Minigame[0x18D4 + i] = 0;
                }
            }
            changeScene(1, 6);
        }
        if (*(u16*)(g_GameLogic + 0xFE) > 0x1E) {
            g_Minigame[0x19DE] = 0;
            if (g_Minigame[0x19E0] != 0) {
                g_Minigame[0x19DE] = 5;
                g_Minigame[0x19E0] = 0;
                port = lbl_80366158[0x27];
                g_Minigame[0x19E9 + port * 9] = 1;
                fn_800506E8(port, *(s8*)(g_Minigame + 0x19E8 + port * 9), 1);
            }
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_GameLogic[0x125]++;
        }
        break;
    case 2:
        fn_3_10CC20();
        break;
    case 3:
        if (g_d_GameSettings[7] == 6) {
            if (*(u16*)(g_GameLogic + 0xFE) > 0x14) {
                switch (fn_3_5B380(((u16*)(g_Controls + 6))[lbl_80366158[0x27] * 8])) {
                case 1:
                    g_GameLogic[0x125] = 4;
                    *(u16*)(g_GameLogic + 0xFE) = 0;
                    break;
                case 2:
                    g_GameLogic[0x125] = 2;
                    break;
                }
            }
            return;
        }
        g_GameLogic[0x125] = 4;
        *(u16*)(g_GameLogic + 0xFE) = 0;
        break;
    case 4:
        if (*(s8*)(g_Minigame + 0x1A0C) == -1) {
            if (g_d_GameSettings[7] == 6) {
                if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
                    changeScene(4, 6);
                }
                if (lbl_8037169C[0x13] != 0) {
                    g_GameLogic[0x125] = 5;
                }
            } else if (*(u16*)(g_GameLogic + 0xFE) >= 0xF) {
                fn_3_5A6D4(0x1C);
            }
        }
        lbl_8036E548[0x307A] = 0;
        break;
    case 5:
        fn_3_972C8();
        fn_8004CC18();
        g_GameLogic[0x122] = 1;
        break;
    case 6:
        if (*(s8*)(g_Minigame + 0x1A0F) < 0) {
            for (i = 0; i < 4; i++) {
                if (*(s8*)(g_Minigame + 0x19EF + i * 9) == 0 && *(s8*)(g_Minigame + 0x19E9 + i * 9) != 0) {
                    break;
                }
            }
            if (i >= 4) {
                changeScene(3, 6);
                if (g_Minigame[0x1A3C] == 0) {
                    lbl_803C6714[6] = 6;
                    g_Minigame[0x1A1C] = 0;
                }
            }
        }
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic[0x125] = 7;
        }
        break;
    case 7:
        fn_3_60768();
        buildMinigamePlayersInline();
        lbl_8036E548[0x307A] = 0;
        g_Minigame[0x1A1D] = 0;
        if (g_Minigame[0x1A3C] != 0) {
            memset(g_Minigame + 0x1E04, 0, 0x28);
            i = 0;
            g_Minigame[0x1A3D] = 0;
            g_Minigame[0x1A3F] = 0;
            lbl_8036E548[0x307E] = 0;
            do {
                g_Minigame[0x1E1C + i] = i + 1;
                i++;
            } while ((u32)i < 6);
            fn_3_9DC18(g_Minigame + 0x1E1C, 6, 0);
            fn_3_5A6D4(0x28);
        } else {
            fn_3_5A6D4(0x21);
        }
        break;
    }
    state = g_GameLogic[0x125];
    if (state == 3 || state == 4) {
        g_Minigame[0x19EF] = 0;
        g_Minigame[0x19F8] = 0;
        g_Minigame[0x1A01] = 0;
        g_Minigame[0x1A0A] = 0;
    }
    if (state >= 2) {
        fn_3_10C81C();
    }
}
#endif

extern void fn_8004CC4C(u8 first, u8 second, u8 third, s32 selection, u16 value);
extern void fn_8004D0F0(void);
extern void fn_8004CC2C(void);
extern void fn_3_8C07C(void);
extern void fn_3_8FC0C(void);
extern u8 lbl_803C5F74[]; // TODO type: ConfirmDialog (main/file_8004C5F8.h), [3] = state

// NONMATCHING 93%: inlines fn_3_109DE0 (itself NONMATCHING; remaining differences are inside that inline)
#if NONMATCHING
// fn_3_10A0A0, size:0xCA8
void fn_3_10A0A0(void) {
    RankEnt score;
    u32 rank;
    s32 ok;
    s32 i;
    u8 m;
    u8 v;
    u8* p;

    switch (g_GameLogic[0x125]) {
    case 0:
        lbl_3_common_bss_32724[0xB8] = 0;
        g_Minigame[0x19A9] = 1;
        g_Minigame[0x19AA] = 0;
        g_Minigame[0x1A44] = 0;
        g_Minigame[0x1A45] = 0;
        g_Minigame[0x1A43] = 0;
        g_Minigame[0x1A3D] = 0;
        if (g_d_GameSettings[8] == 0) {
            fn_3_106ED4();
        } else if (g_Minigame[0x1A2B] == 3 || g_d_GameSettings[7] == 6) {
            ok = 1;
            if (g_d_GameSettings[7] == 6) {
                if (*(s8*)(g_Minigame + 0x1908) < 0) {
                    ok = 0;
                }
            } else {
                m = g_Minigame[0x1A2A];
                if ((m == 2 || m == 4 || m == 5 || m == 6) && g_Minigame[0x18E8 + *(s8*)(g_Minigame + 0x1908)] > 1) {
                    ok = 0;
                }
            }
            if (ok != 0) {
                fn_3_109DE0(&score);
                rank = fn_3_109CE8(&score);
                if (rank >= 5) {
                    g_Minigame[0x1A43] = 0;
                } else {
                    g_Minigame[0x1A43] = rank + 1;
                    g_Minigame[0x19AA] = 1;
                }
            }
        } else if (g_Minigame[0x1A37] == 1 && g_d_GameSettings[8] != 0 && g_Minigame[0x1A2A] >= 1 && g_Minigame[0x1A2A] <= 6) {
            p = &g_d_GameSettings[0x13 + g_Minigame[0x1A2A]];
            if (*p == g_Minigame[0x1A2B]) {
                g_Minigame[0x1A44] = 1;
                (*p)++;
                for (i = 0; i < 6; i++) {
                    if (g_d_GameSettings[0x14 + i] < 3) {
                        break;
                    }
                }
                if (i >= 6) {
                    g_Minigame[0x1A45] = 2;
                    g_d_GameSettings[0x12] = 2;
                }
            }
        }
        fn_3_8C07C();
        fn_3_5B368();
        changeScene(1, 6);
        *(u16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        g_Minigame[0x19A9] = 2;
        *(u16*)(g_GameLogic + 0xFE) = 0;
        if (g_Minigame[0x1A37] == 0) {
            fn_3_8FC0C();
        }
        g_GameLogic[0x125] = 2;
        break;
    case 2:
        if (*(u16*)(g_GameLogic + 0xFE) == *(s16*)(lbl_3_data_2137C + 2)) {
            lbl_3_common_bss_32724[0xB8] = 1;
        }
        if (g_Minigame[0x1A44] == 1) {
            if (*(u16*)(g_GameLogic + 0xFC) > 0x12C) {
                g_GameLogic[0x125] = 5;
                *(u16*)(g_GameLogic + 0xFE) = 0;
            }
        } else if (g_Minigame[0x1A45] != 0) {
            if (*(u16*)(g_GameLogic + 0xFC) > 0x12C) {
                g_GameLogic[0x125] = 6;
                *(u16*)(g_GameLogic + 0xFE) = 0;
            }
        } else if (*(u16*)(g_GameLogic + 0xFC) > 0x12C) {
            if (g_d_GameSettings[8] == 0) {
                if (*(u16*)(g_GameLogic + 0xFC) > 0x1A4) {
                    g_GameLogic[0x125] = 3;
                }
            } else if (g_Minigame[0x1A2A] == 1 && g_Minigame[0x1A2B] == 3 && fn_3_6C938(0, 0x10) != 0 &&
                       fn_3_6C938(0, 0x800) != 0 && fn_3_6C938(0, 0x200) != 0) {
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                *(u16*)(g_GameLogic + 0xFE) = 0;
                g_GameLogic[0x125] = 7;
            } else if (fn_3_6C938(1, 0x1100) != 0) {
                g_GameLogic[0x125] = 3;
            }
        }
        break;
    case 7:
        if (*(u16*)(g_GameLogic + 0xFE) > 0x1E && fn_3_6C938(1, 0x200) != 0) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            *(u16*)(g_GameLogic + 0xFC) = 0x10E;
            g_GameLogic[0x125] = 2;
        }
        break;
    case 5:
        if (*(u16*)(g_GameLogic + 0xFE) == 1) {
            v = g_d_GameSettings[0x13 + g_Minigame[0x1A2A]];
            fn_8004CC4C(9, 0, v - 1, 0, v + 0x8C);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
            *(s16*)(g_GameLogic + 0x116) = 0;
            fn_3_90064(0x301);
        } else if (*(u16*)(g_GameLogic + 0xFE) > 0x96) {
            if (fn_3_6C938(1, 0x1100) != 0) {
                fn_8004CC2C();
                *(s16*)(g_GameLogic + 0x116) = 1;
            } else if (*(s16*)(g_GameLogic + 0x116) != 0 && lbl_803C5F74[3] == 4) {
                if (g_Minigame[0x1A45] != 0) {
                    *(u16*)(g_GameLogic + 0xFE) = 0;
                    g_GameLogic[0x125] = 6;
                } else {
                    g_GameLogic[0x125] = 3;
                }
            }
        }
        break;
    case 6:
        if (*(u16*)(g_GameLogic + 0xFE) == 1) {
            fn_8004CC4C(9, 0, 4, 0, 0x91);
            fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
            *(s16*)(g_GameLogic + 0x116) = 0;
        } else if (*(u16*)(g_GameLogic + 0xFE) > 0x96) {
            if (fn_3_6C938(1, 0x1100) != 0) {
                fn_8004CC2C();
                *(s16*)(g_GameLogic + 0x116) = 1;
            } else if (*(s16*)(g_GameLogic + 0x116) != 0 && lbl_803C5F74[3] == 4) {
                *(u16*)(g_GameLogic + 0xFE) = 0;
                g_GameLogic[0x125] = 3;
            }
        }
        break;
    case 3:
        if (g_Minigame[0x1A44] != 0 || g_Minigame[0x1A45] != 0) {
            if (fn_3_5B220(1) != 0) {
                g_GameLogic[0x125] = 4;
            }
        } else {
            g_GameLogic[0x125] = 4;
        }
        break;
    case 4:
        if (g_Minigame[0x190A] != 0) {
            g_GameLogic[0x125] = 9;
        } else {
            g_GameLogic[0x125] = 8;
        }
        fn_3_8FC0C();
        break;
    case 8:
        if (g_d_GameSettings[7] == 6) {
            lbl_3_common_bss_34C90[0x1D2] = 0;
            if (*(s8*)(g_Minigame + 0x1908) >= 0) {
                fn_3_5A6D4(0x24);
            } else {
                fn_3_5A6D4(0x22);
            }
        } else if (g_Minigame[0x1909] == 0 && g_Minigame[0x1A3C] == 0 && g_Minigame[0x1A2B] == 3) {
            fn_3_5A6D4(0x24);
        } else {
            lbl_3_common_bss_34C90[0x1D1] = 0;
            lbl_3_common_bss_34C90[0x1D2] = 0;
            if (g_Minigame[0x1A3C] != 0) {
                fn_3_5A6D4(0x26);
            } else {
                fn_3_5A6D4(0x22);
            }
        }
        break;
    case 9:
        fn_800203E0(0xC, (s8)lbl_3_data_6104[starMissionCompletionTracker[0x441C]]);
        if (lbl_8037169C[0x13] != 0) {
            g_GameLogic[0x125] = 10;
        }
        break;
    case 10:
        m = g_Minigame[0x1A2A];
        if (m == 1 || m == 3) {
            if (g_Minigame[0x1A37] != 0) {
                g_d_GameSettings[0x38] = 1;
            } else {
                g_d_GameSettings[0x38] = 0;
            }
        } else if (g_Minigame[0x19A8] != 0) {
            g_d_GameSettings[0x38] = 0;
        } else {
            g_d_GameSettings[0x38] = g_Minigame[0x18E8 + g_d_GameSettings[0x35]];
        }
        fn_3_15F998();
        fn_3_147DFC();
        fn_3_11CF84();
        g_GameLogic[0x122] = 1;
        break;
    }
    fn_3_10A01C();
}
#endif

extern s32 fn_8004FD64(s32 player);
extern s32 fn_8004FDE8(s32 p, s32 q);
extern u32 fn_800628D4(s32 kind);
extern u8 lbl_80361B20[];  // TODO type: save-data flags block (main/file_8004C5F8.h)
extern u8 lbl_803C6028[];  // TODO type: RosterSelect (main/file_8004C5F8.h)

// One controller entry in g_Controls (stride 0x10).
typedef struct {
    /*0x0*/ u8 _0[4];
    /*0x4*/ u16 held;
    /*0x6*/ u16 pressed;
    /*0x8*/ u16 repeat;
    /*0xA*/ u8 _A[6];
} MgPad; // size: 0x10

static inline void satIncU16(u16* p) {
    if (*p < 0xFFFE) {
        (*p)++;
    } else {
        *p = 0xFFFF;
    }
}

static inline u8 charSkinCount(s8 c) {
    return lbl_8034E9A0[c * 0xA0 + 0x26] * 2 + lbl_8034E9A0[c * 0xA0 + 0x27];
}

// Clears the character picked by slot k (unlocking it in the roster) if it was taken.
static inline void releaseSlotChar(s32 k) {
    if (*(s8*)(g_Minigame + 0x19E8 + k * 9) >= 0) {
        if ((s32)g_Minigame[0x19E9 + k * 9] == 1) {
            fn_800506E8(k, *(s8*)(g_Minigame + 0x19E8 + k * 9), 0);
        }
        if (*(s8*)(g_Minigame + 0x19EA + k * 9) != -1) {
            *(s8*)(g_Minigame + 0x19E8 + k * 9) = -1;
            *(s8*)(g_Minigame + 0x19EA + k * 9) = -1;
            g_Minigame[0x1A13 + k] = 1;
            g_Minigame[0x19E9 + k * 9] = 0;
        }
    }
}

// NONMATCHING 92%: original calls fn_800506E8/fn_80050760 without the s8/s16 prototypes (no extsb/extsh), plus regalloc
#if NONMATCHING
// fn_3_10CC20, size:0x19EC
void fn_3_10CC20(void) {
    s8 slotChar[4];
    u8 used[12];
    MgPad* pads;
    MgPad* pad;
    s32 i;
    s32 j;
    s32 k;
    s32 changed;
    s32 ready;
    s32 n;
    s32 r;
    u8 port;
    u8 maxSel;
    u8 t;
    u8 s;
    s8 c;
    s8 old;
    s16 sel;

    port = lbl_80366158[0x27];
    maxSel = g_d_GameSettings[0x13 + g_Minigame[0x1A2A]];
    pads = (MgPad*)g_Controls;
    pad = &pads[port];
    if (g_Minigame[0x190A] != 0) {
        maxSel = 2;
    }
    s = g_Minigame[0x19DE];
    if (s == 0) {
        changed = 0;
        for (i = 0; i < 4; i++) {
            lbl_803C6028[0x74 + i] = 0;
            slotChar[i] = -1;
            if (*(s8*)(g_Minigame + 0x19DA + i) == 0) {
                if (i != port && *(s8*)(g_Minigame + 0x19E9 + i * 9) == 0 && (pads[i].pressed & 0x200) &&
                    lbl_803C6028[0x92] != 0) {
                    *(s8*)(g_Minigame + 0x19DA + i) = -1;
                    g_Minigame[0x19E7]--;
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                }
            } else if (i == port) {
                g_Minigame[0x19DA + i] = 0;
                changed = 1;
                slotChar[i] = -3;
            } else if (g_Minigame[0x190A] == 0 && (pads[i].pressed & 0x100)) {
                g_Minigame[0x19DA + i] = 0;
                changed = 1;
                slotChar[i] = -3;
                g_Minigame[0x19E7]++;
            }
        }
        if (changed != 0) {
            fn_80050138(0, slotChar[0], slotChar[1], slotChar[2], slotChar[3], 0);
        }

        ready = 0;
        for (i = 0; i < 4; i++) {
            pad = &pads[i];
            if (*(s8*)(g_Minigame + 0x19DA + i) != 0) {
                continue;
            }
            satIncU16((u16*)(g_Minigame + 0x19D2 + i * 2));
            if (slotChar[i] == -3) {
                // newly joined: put the cursor on a default character
                g_Minigame[0x19E8 + i * 9] = fn_80050760(i, 0, 0, 0, 0);
                g_Minigame[0x19EF + i * 9] = 0;
                g_Minigame[0x1A17 + i] = charSkinCount(*(s8*)(g_Minigame + 0x19E8 + i * 9));
                g_Minigame[0x18D4 + i] = 0;
                if (g_d_GameSettings[8] == 0 &&
                    starMissionCompletionTracker[0x43D6 + *(s8*)(g_Minigame + 0x19E8 + i * 9)] != 0) {
                    g_Minigame[0x18D4 + i] = 0;
                }
                if (i != port) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                }
            } else if (*(s8*)(g_Minigame + 0x19E9 + i * 9) != 0) {
                // character locked in
                if (!(pad->pressed & 0x200)) {
                    ready++;
                } else {
                    if (lbl_803C6028[0x92] == 0) {
                        continue;
                    }
                    g_Minigame[0x19E9 + i * 9] = 0;
                    fn_800506E8(i, *(s8*)(g_Minigame + 0x19E8 + i * 9), 0);
                    fn_80050760(i, 0, 0, 0, 0);
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    for (j = 0; j < 4; j++) {
                        if (i != j && *(s8*)(g_Minigame + 0x19DA + j) == 0) {
                            c = fn_8004FDE8(i, j);
                            if (c >= -1) {
                                g_Minigame[0x19E8 + j * 9] = c;
                            }
                        }
                    }
                }
            } else {
                if ((pad->pressed & 0x100) && *(s8*)(g_Minigame + 0x19E8 + i * 9) >= 0 &&
                    *(u16*)(g_GameLogic + 0xFE) > 0x1E) {
                    if (*(s8*)(g_Minigame + 0x19EE + i * 9) != 0) {
                        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                        goto browse;
                    }
                    if (*(s8*)(lbl_803C6028 + 0x7F + i) < 0 &&
                        *(s8*)(g_Minigame + 0x19E8 + i * 9) == *(s8*)(g_Minigame + 0x19EA + i * 9) &&
                        *(s8*)(g_Minigame + 0x19EC + i * 9) == *(s8*)(g_Minigame + 0x19ED + i * 9) &&
                        *(s8*)(g_Minigame + 0x19EF + i * 9) != 0 && *(s8*)(g_Minigame + 0x19F0 + i * 9) != 0) {
                        g_Minigame[0x19E9 + i * 9] = 1;
                        fn_800506E8(i, *(s8*)(g_Minigame + 0x19E8 + i * 9), 1);
                        fn_800628D4(*(s8*)(g_Minigame + 0x19E8 + i * 9));
                    }
                } else if ((pad->pressed & 0x200) && g_d_GameSettings[8] != 0) {
                    if (lbl_803C6028[0x92] == 0) {
                        continue;
                    }
                    if (*(s8*)(lbl_803C6028 + 0x7F + i) < 0) {
                        *(u16*)(g_GameLogic + 0xFE) = 0;
                        g_GameLogic[0x125] = 3;
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                        return;
                    }
                } else {
                browse:
                    old = g_Minigame[0x19E8 + i * 9];
                    r = fn_80050760(i, pad->held, pad->pressed, pad->repeat, 0);
                    if (r >= 0) {
                        g_Minigame[0x19E8 + i * 9] = r;
                        if (old != *(s8*)(g_Minigame + 0x19E8 + i * 9)) {
                            *(u16*)(g_Minigame + 0x19D2 + i * 2) = 0;
                            g_Minigame[0x1A17 + i] = charSkinCount(*(s8*)(g_Minigame + 0x19E8 + i * 9));
                            g_Minigame[0x18D4 + i] = 0;
                            if (g_d_GameSettings[8] == 0 &&
                                starMissionCompletionTracker[0x43D6 + *(s8*)(g_Minigame + 0x19E8 + i * 9)] != 0) {
                                g_Minigame[0x18D4 + i] = 0;
                            }
                        }
                        g_Minigame[0x19EE + i * 9] = 0;
                    } else {
                        g_Minigame[0x19E8 + i * 9] = fn_8004FD64(i);
                        g_Minigame[0x19EE + i * 9] = 1;
                        g_Minigame[0x19EF + i * 9] = 0;
                    }
                }
            }
            // Z: cycle the costume
            if (*(s8*)(g_Minigame + 0x19EE + i * 9) == 0 && *(s8*)(g_Minigame + 0x19E9 + i * 9) == 0 &&
                (pad->pressed & 0x400)) {
                *(u16*)(g_Minigame + 0x19D2 + i * 2) = 0;
                g_Minigame[0x1A17 + i]++;
                if (g_Minigame[0x1A17 + i] > 3) {
                    g_Minigame[0x1A17 + i] = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            if (g_Minigame[0x190A] != 0) {
                if (starMissionCompletionTracker[0x43D6 + *(s8*)(g_Minigame + 0x19E8 + i * 9)] != 0) {
                    g_Minigame[0x18D4 + i] = 1;
                } else {
                    g_Minigame[0x18D4 + i] = 0;
                }
            } else if (lbl_80361B20[*(s8*)(g_Minigame + 0x19E8 + i * 9)] != 0 && (pad->pressed & 0x800)) {
                g_Minigame[0x18D4 + i] ^= 1;
                if (g_Minigame[0x18D4 + i] != 0) {
                    sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                } else {
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                }
            }
        }

        n = g_Minigame[0x19E7];
        if ((u8)ready >= n) {
            *(u16*)(g_GameLogic + 0xFE) = 0;
            g_Minigame[0x19DE] = 2;
            g_Minigame[0x19E6] = n;
            if (g_Minigame[0x1A3C] != 0) {
                if (n == 4) {
                    g_Minigame[0x19DE] = 7;
                } else {
                    g_Minigame[0x19DE] = 6;
                }
                g_Minigame[0x19E6] = 4;
            } else if (n == 1 && g_d_GameSettings[7] != 6) {
                g_Minigame[0x19DE] = 5;
            } else if (n == 4) {
                g_Minigame[0x19DE] = 7;
            } else if (g_d_GameSettings[7] == 6 && g_d_GameSettings[8] != 0) {
                g_Minigame[0x19DE] = 2;
                g_Minigame[0x19E6] = lbl_3_data_18920[g_Minigame[0x1A2A]][4];
            } else {
                t = lbl_3_data_18920[g_Minigame[0x1A2A]][4];
                if (n >= t) {
                    g_Minigame[0x19DE] = 1;
                    if (g_Minigame[0x19E7] >= t) {
                        g_Minigame[0x1A0D] = 0;
                    } else {
                        g_Minigame[0x1A0D] = t - g_Minigame[0x19E7];
                    }
                    g_Minigame[0x1A0E] = 4 - g_Minigame[0x19E7];
                    g_Minigame[0x19E3] = g_Minigame[0x1A0D];
                } else {
                    g_Minigame[0x19E6] = t;
                    g_Minigame[0x19DE] = 2;
                }
            }
        }
    } else if (s == 1) {
        if (pad->pressed & 0x100) {
            if (*(s8*)(g_Minigame + 0x19E3) != 0) {
                g_Minigame[0x19DE] = 2;
                g_Minigame[0x19E6] = g_Minigame[0x19E3] + g_Minigame[0x19E7];
            } else {
                g_Minigame[0x19DE] = 7;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (pad->pressed & 0x200) {
            g_Minigame[0x19E9 + port * 9] = 0;
            fn_800506E8(port, *(s8*)(g_Minigame + 0x19E8 + port * 9), 0);
            g_Minigame[0x19DE] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else if (pad->repeat & 8) {
            if (*(s8*)(g_Minigame + 0x19E3) > g_Minigame[0x1A0D]) {
                g_Minigame[0x19E3]--;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (pad->repeat & 4) {
            if (*(s8*)(g_Minigame + 0x19E3) < g_Minigame[0x1A0E]) {
                g_Minigame[0x19E3]++;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (s == 2 || s == 6) {
        // fill the remaining slots with CPU players
        n = g_Minigame[0x19E6] - g_Minigame[0x19E7];
        for (i = 0; i < 4; i++) {
            if (n == 0) {
                break;
            }
            if (*(s8*)(g_Minigame + 0x19DA + i) == -1) {
                g_Minigame[0x19DA + i] = 1;
                n--;
                *(s8*)(g_Minigame + 0x19E8 + i * 9) = -1;
                *(s8*)(g_Minigame + 0x19EA + i * 9) = -1;
                lbl_803C6028[0x74 + i] = 1;
            }
        }
        if (g_d_GameSettings[7] == 6 && g_d_GameSettings[8] == 0) {
            g_Minigame[0x19DE] = 8;
        } else if (g_Minigame[0x19E7] == 1 && g_d_GameSettings[7] != 6) {
            g_Minigame[0x19DE] = 8;
        } else {
            g_Minigame[0x19DE] = 3;
        }
        *(u16*)(g_GameLogic + 0xFE) = 0;
    } else if (s == 3) {
        if (*(u16*)(g_GameLogic + 0xFE) == 1) {
            if (*(s16*)(g_Minigame + 0x18A2) >= 0) {
                *(s16*)(g_Minigame + 0x18A2) = -1;
            } else {
                // give each CPU slot a random character not already taken
                for (k = 0; k < 12; k++) {
                    used[k] = 0;
                }
                n = 12;
                for (i = 0; i < 4; i++) {
                    slotChar[i] = -1;
                    if (*(s8*)(g_Minigame + 0x19E9 + i * 9) != 0) {
                        c = g_Minigame[0x19E8 + i * 9];
                        for (k = 0; k < 12; k++) {
                            if (c == lbl_800E854C[k]) {
                                used[k] = 1;
                                n--;
                            }
                        }
                        g_Minigame[0x19E8 + i * 9] = c;
                    }
                }
                for (i = 0; i < 4; i++) {
                    if ((s32)g_Minigame[0x19DA + i] == 1 && *(s8*)(g_Minigame + 0x19E9 + i * 9) == 0) {
                        r = random_fn_3_9EE24(n);
                        for (k = 0; k < 12; k++) {
                            if (used[k] == 0) {
                                if (r == 0) {
                                    slotChar[i] = lbl_800E854C[k];
                                    fn_80050138(1, slotChar[0], slotChar[1], slotChar[2], slotChar[3], 0);
                                    g_Minigame[0x19E8 + i * 9] = slotChar[i];
                                    g_Minigame[0x1A17 + i] = charSkinCount(slotChar[i]);
                                    g_Minigame[0x18D4 + i] = 0;
                                    break;
                                }
                                r--;
                            }
                        }
                        break;
                    }
                }
            }
        } else if (*(u16*)(g_GameLogic + 0xFE) > 0x2D) {
            // the main player sets up the first CPU slot that is not locked in
            for (i = 0; i < 4; i++) {
                if ((s32)g_Minigame[0x19DA + i] != 1 || (s32)g_Minigame[0x19E9 + i * 9] == 1) {
                    continue;
                }
                satIncU16((u16*)(g_Minigame + 0x19D2 + i * 2));
                if ((pad->pressed & 0x100) && *(s8*)(g_Minigame + 0x19E8 + i * 9) >= 0 &&
                    *(s8*)(g_Minigame + 0x19EE + i * 9) == 0) {
                    if (*(s8*)(lbl_803C6028 + 0x7F + i) < 0 &&
                        *(s8*)(g_Minigame + 0x19E8 + i * 9) == *(s8*)(g_Minigame + 0x19EA + i * 9) &&
                        *(s8*)(g_Minigame + 0x19EC + i * 9) == *(s8*)(g_Minigame + 0x19ED + i * 9) &&
                        *(s8*)(g_Minigame + 0x19EF + i * 9) != 0 && *(s8*)(g_Minigame + 0x19F0 + i * 9) != 0) {
                        g_Minigame[0x19DE] = 4;
                        *(s16*)(g_Minigame + 0x18A2) = i;
                        g_Minigame[0x19E9 + i * 9] = 1;
                        *(u16*)(g_GameLogic + 0xFE) = 0;
                        fn_800506E8(i, *(s8*)(g_Minigame + 0x19E8 + i * 9), 1);
                        fn_800628D4(*(s8*)(g_Minigame + 0x19E8 + i * 9));
                    }
                } else {
                    old = g_Minigame[0x19E8 + i * 9];
                    r = fn_80050760(i, pad->held, pad->pressed, pad->repeat, 0);
                    if (r >= 0) {
                        g_Minigame[0x19E8 + i * 9] = r;
                        if (old != *(s8*)(g_Minigame + 0x19E8 + i * 9)) {
                            *(u16*)(g_Minigame + 0x19D2 + i * 2) = 0;
                            g_Minigame[0x1A17 + i] = charSkinCount(*(s8*)(g_Minigame + 0x19E8 + i * 9));
                            g_Minigame[0x18D4 + i] = 0;
                        }
                        g_Minigame[0x19EE + i * 9] = 0;
                    } else {
                        g_Minigame[0x19EE + i * 9] = 1;
                        g_Minigame[0x19EF + i * 9] = 0;
                    }
                }
                if ((pad->pressed & 0x400) && *(s8*)(g_Minigame + 0x19EE + i * 9) == 0) {
                    *(u16*)(g_Minigame + 0x19D2 + i * 2) = 0;
                    g_Minigame[0x1A17 + i]++;
                    if (g_Minigame[0x1A17 + i] > 3) {
                        g_Minigame[0x1A17 + i] = 0;
                    }
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
                if (lbl_80361B20[*(s8*)(g_Minigame + 0x19E8 + i * 9)] != 0 && (pad->pressed & 0x800)) {
                    g_Minigame[0x18D4 + i] ^= 1;
                    if (g_Minigame[0x18D4 + i] != 0) {
                        sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                    } else {
                        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    }
                }
                break;
            }
            if (i >= 4) {
                g_Minigame[0x19DE] = 7;
                *(u16*)(g_GameLogic + 0xFE) = 0;
            } else {
                // B on a human pad: step back
                for (j = 0; j < 4; j++) {
                    if (*(s8*)(g_Minigame + 0x19DA + j) != 0 || !(pads[j].pressed & 0x200)) {
                        continue;
                    }
                    *(s8*)(lbl_803C6028 + 0x7F + i) = -1;
                    if (j == port) {
                        for (k = 3; k >= 0; k--) {
                            if ((s32)g_Minigame[0x19DA + k] == 1) {
                                if (*(s8*)(g_Minigame + 0x19E9 + k * 9) != 0) {
                                    fn_800506E8(k, *(s8*)(g_Minigame + 0x19E8 + k * 9), 0);
                                    g_Minigame[0x19E9 + k * 9] = 0;
                                    break;
                                }
                                if (*(s8*)(g_Minigame + 0x19EA + k * 9) != -1 ||
                                    *(s8*)(g_Minigame + 0x19EB + k * 9) != -1) {
                                    *(s8*)(g_Minigame + 0x19E8 + k * 9) = -1;
                                    *(s8*)(g_Minigame + 0x19EA + k * 9) = -1;
                                    g_Minigame[0x19EF + k * 9] = 0;
                                    g_Minigame[0x1A13 + k] = 1;
                                }
                            }
                        }
                        if (k < 0) {
                            for (k = 3; k >= 0; k--) {
                                if ((s32)g_Minigame[0x19DA + k] == 1) {
                                    if (*(s8*)(g_Minigame + 0x19E8 + k * 9) >= 0) {
                                        if (*(s8*)(g_Minigame + 0x19EA + k * 9) == -1) {
                                            g_Minigame[0x19EC + k * 9] = 1;
                                        } else {
                                            *(s8*)(g_Minigame + 0x19E8 + k * 9) = -1;
                                            *(s8*)(g_Minigame + 0x19EA + k * 9) = -1;
                                            g_Minigame[0x1A13 + k] = 1;
                                            g_Minigame[0x19E9 + k * 9] = 0;
                                        }
                                    }
                                    *(s8*)(g_Minigame + 0x19DA + k) = -1;
                                }
                            }
                            fn_800506E8(j, *(s8*)(g_Minigame + 0x19E8 + j * 9), 0);
                            g_Minigame[0x19DE] = 0;
                            g_Minigame[0x19E9 + j * 9] = 0;
                        }
                    } else {
                        fn_800506E8(j, *(s8*)(g_Minigame + 0x19E8 + j * 9), 0);
                        g_Minigame[0x19DE] = 0;
                        g_Minigame[0x19E9 + j * 9] = 0;
                        for (k = 0; k < 4; k++) {
                            if ((s32)g_Minigame[0x19DA + k] == 1) {
                                releaseSlotChar(k);
                                *(s8*)(g_Minigame + 0x19DA + k) = -1;
                            }
                        }
                    }
                    sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                    return;
                }
            }
        }
    } else if (s == 4) {
        if (*(u16*)(g_GameLogic + 0xFE) > 0x28) {
            if (pad->pressed & 0x100) {
                *(s16*)(g_Minigame + 0x18A2) = -1;
                g_Minigame[0x19DE] = 3;
                *(u16*)(g_GameLogic + 0xFE) = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad->pressed & 0x200) {
                sel = *(s16*)(g_Minigame + 0x18A2);
                fn_800506E8(sel, *(s8*)(g_Minigame + 0x19E8 + sel * 9), 0);
                *(u16*)(g_GameLogic + 0xFE) = 0;
                g_Minigame[0x19E9 + *(s16*)(g_Minigame + 0x18A2) * 9] = 0;
                g_Minigame[0x19DE] = 3;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            } else if (pad->repeat & 8) {
                if (g_Minigame[0x18DC + *(s16*)(g_Minigame + 0x18A2)] != 0) {
                    g_Minigame[0x18DC + *(s16*)(g_Minigame + 0x18A2)]--;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (pad->repeat & 4) {
                if (g_Minigame[0x18DC + *(s16*)(g_Minigame + 0x18A2)] < 3) {
                    g_Minigame[0x18DC + *(s16*)(g_Minigame + 0x18A2)]++;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
        }
    } else if (s == 5) {
        for (i = 0; i < 4; i++) {
            if (*(s8*)(g_Minigame + 0x19DA + i) >= 0 && *(s8*)(g_Minigame + 0x19E9 + i * 9) != 0) {
                satIncU16((u16*)(g_Minigame + 0x19D2 + i * 2));
            }
        }
        if (*(u16*)(g_GameLogic + 0xFE) > 0x1E) {
            if (pad->pressed & 0x100) {
                g_Minigame[0x19DE] = 6;
                g_Minigame[0x1A2B] = g_Minigame[0x19E4];
                *(u16*)(g_GameLogic + 0xFE) = 0;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            } else if (pad->pressed & 0x200) {
                g_Minigame[0x19E9 + port * 9] = 0;
                fn_800506E8(port, *(s8*)(g_Minigame + 0x19E8 + port * 9), 0);
                g_Minigame[0x19DE] = 0;
                *(u16*)(g_GameLogic + 0xFE) = 0;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            } else if (pad->repeat & 1) {
                if (*(s8*)(g_Minigame + 0x19E4) > 0) {
                    g_Minigame[0x19E4]--;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            } else if (pad->repeat & 2) {
                if (*(s8*)(g_Minigame + 0x19E4) < maxSel) {
                    g_Minigame[0x19E4]++;
                    sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
                }
            }
            g_Minigame[0x19E6] = lbl_3_data_18920[g_Minigame[0x1A2A]][*(s8*)(g_Minigame + 0x19E4)];
        }
    } else if (*(u16*)(g_GameLogic + 0xFE) > 0x5A) {
        g_GameLogic[0x125] = 6;
        *(u16*)(g_GameLogic + 0xFE) = 0;
    }

    // START on an unused pad drops all CPU players and lets that pad join (versus mode only)
    s = g_Minigame[0x19DE];
    if (g_d_GameSettings[8] != 0 && (s == 1 || (s >= 2 && s <= 4) || s == 5) && *(u16*)(g_GameLogic + 0xFE) >= 0x1E) {
        slotChar[0] = -1;
        slotChar[1] = -1;
        slotChar[2] = -1;
        slotChar[3] = -1;
        for (i = 0; i < 4; i++) {
            slotChar[i] = -1;
            if (*(s8*)(g_Minigame + 0x19DA + i) != 0 && (pads[i].pressed & 0x100)) {
                releaseSlotChar(i);
                g_Minigame[0x19DA + i] = 0;
                *(s8*)(g_Minigame + 0x19E8 + i * 9) = -1;
                *(s8*)(g_Minigame + 0x19EA + i * 9) = -1;
                slotChar[i] = -3;
                break;
            }
        }
        if (i < 4) {
            for (k = 0; k < 4; k++) {
                if ((s32)g_Minigame[0x19DA + k] == 1) {
                    releaseSlotChar(k);
                    *(s8*)(g_Minigame + 0x19DA + k) = -1;
                }
            }
            fn_80050138(0, slotChar[0], slotChar[1], slotChar[2], slotChar[3], 0);
            g_Minigame[0x19E7]++;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            g_Minigame[0x19DE] = 0;
        }
    }
}
#endif
