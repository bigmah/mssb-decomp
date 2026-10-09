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

