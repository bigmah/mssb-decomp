#include "game/auto_00_000EA340_text.h"
#include "static/UnknownHomes_Static.h"

typedef struct {
    u8* p;
    s32 pad;
} QEnt;

extern u8 lbl_3_common_bss_32724[];
extern u8 g_GameLogic[];
extern u8 lbl_80371C30[];
typedef struct {
    void* fn;
    u8 pad[0x10];
    u16 u14;
    u16 u16_;
    u16 u18;
    u16 u1A;
    u16 u1C;
} QObj;
extern u8* lbl_803CC1B8;
extern u8 lbl_3_data_8EC4[];
extern u8 lbl_3_data_900C[];
extern u8 inMemRoster[];
extern void fn_3_E9D30(void);
extern u8 g_UnkSound_32718[];
extern u8 lbl_800EF808[];
extern u8 lbl_3_data_19830[];
extern u8 g_Ball[];
extern u8 g_Pitcher[];
extern u8 lbl_3_common_bss_34C90[];
extern void fn_3_9C28C(void);
extern void fn_3_9894C(void);
extern void fn_3_98DE0(void);
extern void fn_3_EA8FC(void);
extern void fn_3_EB6E0(void);
extern void fn_3_129458(void);
extern void fn_3_9143C(void);
extern void fn_3_96914(void);
extern void fn_3_97144(void*);
extern void fn_3_EAEF4(void);
extern void fn_3_EDA3C(void);
extern void fn_3_1254F8(void);
extern void fn_3_126604(void);
extern void fn_3_1274B4(void);
extern void fn_3_128B90(void);
extern void fn_3_E911C(void);
extern u8 lbl_3_data_8FCC[];
extern u8 lbl_3_data_8F64[];
extern u16 lbl_3_data_8FC4[];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern void sndFXCtrl(int, int, u8);
extern s32 sndFXStartEx(u16, u8, u8, u8);
extern u8 lbl_3_data_8F24[];
extern u8 lbl_3_data_8E68[];
extern u8 lbl_3_data_8EA8[];
extern u8 g_Minigame[];
extern void fn_80034E20(void*, void*);
extern void fn_3_ED2F4(void);
extern void fn_3_ED0F4(void);
extern void fn_3_EC014(void);
extern void fn_3_ED6E0(void);


// fn_3_EBFD4, size:0x40
s32 fn_3_EBFD4(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic[0x11E] == 2 || g_GameLogic[0x11E] == 8) {
        return 1;
    }
    return 0;
}

// fn_3_EB684, size:0x5C
s32 fn_3_EB684(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || lbl_3_common_bss_32724[0xB7] != 0) {
        return 1;
    }
    if (g_GameLogic[0x11E] != 1 && g_GameLogic[0x11E] != 2 && g_GameLogic[0x11E] != 0xB) {
        return 1;
    }
    return 0;
}

// fn_3_ED244, size:0x64
void fn_3_ED244(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || ((QEnt*)lbl_80371C30)[*(u16*)(p + 0x14)].p[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED2A8, size:0x4C
void fn_3_ED2A8(void) {
    fn_80034E20(lbl_803CC1B8, lbl_3_data_8FCC);
    *(void**)lbl_803CC1B8 = fn_3_ED244;
}

// fn_3_ED490, size:0x6C
void fn_3_ED490(void) {
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_8F24);
    g_Minigame[0x19CC] = 1;
    *(u16*)(p + 0x1C) = 0;
    *(void**)lbl_803CC1B8 = fn_3_ED2F4;
}

// fn_3_ED4FC, size:0x78
void fn_3_ED4FC(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || g_GameLogic[0x12E] != 0 || g_GameLogic[0x11E] == 3 || g_GameLogic[0x11E] == 0xE || g_GameLogic[0x121] == 0xA) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED784, size:0x94
void fn_3_ED784(void) {
    u8* p = lbl_803CC1B8;
    if (g_Minigame[0x1920] == 0xB) {
        *(void**)p = fn_3_EC014;
    } else {
        s32 v = ((s16*)lbl_3_data_8EA8)[g_Minigame[0x1920]];
        if (v < 0) {
            fn_800B0A14_removeQueue(p);
        } else {
            *(s16*)(lbl_3_data_8E68 + 2) = (s16)v;
            fn_80034E20(p, lbl_3_data_8E68);
            *(void**)lbl_803CC1B8 = fn_3_ED6E0;
        }
    }
}

// fn_3_ED058, size:0x9C
void fn_3_ED058(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    p->u18++;
    if (lbl_3_common_bss_32724[0x96] != 0 || (g_GameLogic[0x11E] != 2 && g_GameLogic[0x11E] != 1) || ((QEnt*)lbl_80371C30)[p->u14].p[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        g_Minigame[0x19CD] = 3;
    }
}

// fn_3_ED6E0, size:0xA4
void fn_3_ED6E0(void) {
    u8* p = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] != 0 || ((QEnt*)lbl_80371C30)[*(u16*)(p + 0x14)].p[0x69] == 2 || g_GameLogic[0x11E] == 8) {
        if (g_Minigame[0x1921] != 0) {
            fn_800B0A5C_insertQueue(fn_3_ED0F4, 2);
        }
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// fn_3_ED574, size:0x16C
void fn_3_ED574(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    s32 v;
    fn_80034E20(p, lbl_3_data_8EC4);
    fn_800363D8(p, 1, 6, 0x4A, *(s16*)(g_Minigame + 0x19B4) % 10);
    fn_800363D8(p, 1, 5, 0x4A, *(s16*)(g_Minigame + 0x19B4) / 10);
    v = *(s16*)(g_Minigame + 0x19B6);
    if (v > *(s16*)(g_Minigame + 0x19B4)) {
        v = *(s16*)(g_Minigame + 0x19B4);
    }
    fn_800363D8(p, 1, 2, 0x4A, v % 10);
    if (v >= 10) {
        fn_800363D8(p, 1, 1, 0x4A, v / 10);
    } else {
        fn_800363D8(p, 1, 1, 0x4A, 10);
    }
    *(void**)lbl_803CC1B8 = fn_3_ED4FC;
}

// fn_3_ED2F4, size:0x19C
void fn_3_ED2F4(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u32 stadium;
    u8 v;
    s32 v2;
    if (lbl_3_common_bss_32724[0x96] == 0) {
        if (g_UnkSound_32718[7] == 0) {
            ((QEnt*)lbl_80371C30)[p->u14].p[0x68] = 1;
            if (p->u1C == 0) {
                if (lbl_800EF808[0x398] == 1) {
                    stadium = g_d_GameSettings.StadiumID;
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        v = lbl_3_data_84B8[0x36];
                    } else {
                        v = lbl_3_data_8404[stadium * 0x1E + 0x36];
                    }
                    v2 = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x1B, v, 0x3F, 0);
                    if (g_d_GameSettings.GameModeSelected == 6) {
                        v = lbl_3_data_84B8[0x37];
                    } else {
                        v = lbl_3_data_8404[stadium * 0x1E + 0x37];
                    }
                    sndFXCtrl(v2, 0x5B, v);
                }
                p->u1C = 1;
            }
        } else {
            ((QEnt*)lbl_80371C30)[p->u14].p[0x68] = 0;
        }
        if (((QEnt*)lbl_80371C30)[p->u14].p[0x69] == 2) {
            goto remove;
        }
    } else {
remove:
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        g_Minigame[0x19CC] = 0;
    }
}

// fn_3_ECBB0, size:0x198
void fn_3_ECBB0(void) {
    QObj* p = (QObj*)lbl_803CC1B8;
    u8* q = g_Minigame + 0x1DF4;
    u32 j;
    s32 n;
    if (lbl_3_common_bss_32724[0x96] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    if (g_GameLogic[0x11E] == 8) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        return;
    }
    switch (p->u1C) {
    case 0:
        fn_80034E20(p, lbl_3_data_19830);
        *(s32*)(((QEnt*)lbl_80371C30)[p->u14 + 1].p + 0x5C) = 0xA0000;
        j = 0;
        do {
            n = p->u14 + j;
            j++;
            *(u32*)(*(u8**)(lbl_80371C30 + (n + 2) * 8) + 0x54) &= ~2;
        } while (j < 4);
        n = p->u14 + (s8)g_Minigame[0x1935];
        *(u32*)(*(u8**)(lbl_80371C30 + (n + 2) * 8) + 0x54) |= 2;
        n = p->u14 + (s8)g_Minigame[0x1936];
        *(u32*)(*(u8**)(lbl_80371C30 + (n + 2) * 8) + 0x54) |= 2;
        q[(s8)g_Minigame[0x1935]] = 1;
        q[(s8)g_Minigame[0x1936]] = 1;
        p->u1C = 1;
        break;
    case 1:
        g_Minigame[0x1934] = 2;
        p->u1C = 2;
        break;
    case 2:
        break;
    }
}

// fn_3_ED818, size:0x224
void fn_3_ED818(void) {
    if (g_GameLogic[0x12D] != 0 && lbl_3_common_bss_32724[0xA5] == 0) {
        lbl_3_common_bss_32724[0xA5] = 1;
        lbl_3_common_bss_32724[0xA6] = 0;
        lbl_3_common_bss_32724[0xA7] = 0xFF;
        fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
        ((QObj*)fn_800B0A5C_insertQueue(fn_3_EA8FC, 2))->u18 = 0;
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
    }
    if (*(s16*)(g_Ball + 0x1B64) == 0xF && g_Minigame[0x19CC] == 0 && g_Minigame[0x19CB] > 1 && g_Pitcher[0x159] == 0) {
        fn_800B0A5C_insertQueue(fn_3_ED490, 2);
    }
    if (lbl_3_common_bss_32724[0xA5] != 0 && lbl_3_common_bss_32724[0xA6] < 0xFF) {
        if (lbl_3_common_bss_32724[0xA6] < 0xF0) {
            lbl_3_common_bss_32724[0xA6] = lbl_3_common_bss_32724[0xA6] + 0x10;
        } else {
            lbl_3_common_bss_32724[0xA6] = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724[0xA7] != 0 && lbl_3_common_bss_32724[0xA7] < 0xFF) {
        if (lbl_3_common_bss_32724[0xA7] <= 0x10) {
            lbl_3_common_bss_32724[0xA7] = 0;
            lbl_3_common_bss_32724[0xA5] = 0;
        } else {
            lbl_3_common_bss_32724[0xA7] = lbl_3_common_bss_32724[0xA7] - 0x10;
        }
    } else if (lbl_3_common_bss_32724[0xA5] != 0) {
        if (g_GameLogic[0x11E] == 8) {
            lbl_3_common_bss_32724[0xA7] = 0;
            lbl_3_common_bss_32724[0xA5] = 0;
        } else if (g_GameLogic[0x11E] != 1 && g_GameLogic[0x11E] != 0 && g_GameLogic[0x11E] != 0xB && g_GameLogic[0x11E] != 0xD) {
            lbl_3_common_bss_32724[0xA7] = 0xF0;
        }
    }
    if (g_GameLogic[0x11E] == 0xB && lbl_3_common_bss_34C90[0x1D2] == 1) {
        fn_800B0A5C_insertQueue(fn_3_9894C, 2);
        if (lbl_3_common_bss_32724[0xAA] == 0) {
            fn_800B0A5C_insertQueue(fn_3_98DE0, 2);
        }
    }
}

