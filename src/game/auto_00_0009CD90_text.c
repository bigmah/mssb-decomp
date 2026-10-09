#include "game/auto_00_0009CD90_text.h"

extern u8 g_Ball[];
extern u8 g_Strikes[];
typedef struct { u8 pad0[0xEE]; s16 s16_EE; u8 pad1[0x154 - 0xF0]; } RunnerT;
extern u8 g_Runners[];
extern u8 g_FieldingLogic[];

extern u8 lbl_3_common_bss_32A94[];
extern u8 g_RunningLogic[];
extern u8 g_Pitcher[];
extern u8 g_Batter[];
extern u8 g_d_GameSettings[];
extern u8 starMissionCompletionTracker[];
extern u8 lbl_80361B20[];
extern u8 g_GameLogic[];

// fn_3_9DBE4, size:0x34
void fn_3_9DBE4(void) {
    lbl_3_common_bss_32A94[0x7D] = 0;
    lbl_3_common_bss_32A94[0x7F] = 0;
    lbl_3_common_bss_32A94[0x81] = 0;
    lbl_3_common_bss_32A94[0x82] = 0;
    lbl_3_common_bss_32A94[0x84] = 0;
    lbl_3_common_bss_32A94[0x85] = 0;
    lbl_3_common_bss_32A94[0x87] = 0;
    lbl_3_common_bss_32A94[0x88] = 0;
    lbl_3_common_bss_32A94[0x8A] = 0;
}

// fn_3_9D550, size:0x44
void fn_3_9D550(void) {
    if (g_Ball[0x1BCF] != 0 && *(s32*)g_Strikes >= 3) {
        *(s16*)lbl_3_common_bss_32A94 = 0x27;
        return;
    }
    *(s16*)lbl_3_common_bss_32A94 = 0x2C;
}

// fn_3_9D594, size:0x6C
void fn_3_9D594(void) {
    switch (g_RunningLogic[0x12]) {
    case 4:
        *(s16*)lbl_3_common_bss_32A94 = 1;
        return;
    case 3:
        *(s16*)lbl_3_common_bss_32A94 = 2;
        return;
    case 2:
        *(s16*)lbl_3_common_bss_32A94 = 3;
        return;
    default:
        *(s16*)lbl_3_common_bss_32A94 = 4;
        return;
    }
}

// fn_3_9DB5C, size:0x88
void fn_3_9DB5C(void) {
    s16* h = (s16*)lbl_3_common_bss_32A94;
    s32 i;
    for (i = 7; i > 3; i--) h[i] = h[i - 1];
    h[3] = h[0];
    h[0] = 0;
    h[1] = 0;
    h[2] = 0;
    ((s8*)lbl_3_common_bss_32A94)[0x10] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x11] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x12] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x13] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x14] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x15] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x16] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x17] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x18] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x19] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x1A] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x1B] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x1C] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x1D] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x1E] = -1;
    ((s8*)lbl_3_common_bss_32A94)[0x1F] = -1;
}

// fn_3_9D600, size:0xA4
void fn_3_9D600(void) {
    if (g_Pitcher[0x14E] == 1) {
        if (g_Batter[0x90] != 0) {
            *(s16*)(lbl_3_common_bss_32A94 + 2) = 0x26;
            return;
        }
        if (g_Batter[0x99] != 0) {
            *(s16*)(lbl_3_common_bss_32A94 + 2) = 0x24;
            return;
        }
        *(s16*)(lbl_3_common_bss_32A94 + 2) = 0x25;
    } else if (g_Pitcher[0x14E] == 2) {
        *(s16*)(lbl_3_common_bss_32A94 + 2) = 0x2A;
    } else if (g_Pitcher[0x14E] == 3) {
        *(s16*)lbl_3_common_bss_32A94 = 0x2B;
    }
}

// fn_3_9EA1C, size:0xC8
s32 fn_3_9EA1C(s32 idx) {
    s32 i;
    for (i = 1; i < 10; i++) {
        if (*(s32*)(g_GameLogic + idx * 0x50 + i * 8 + 0x40) % 10 == 9) {
            return 1;
        }
    }
    return 0;
}

// fn_3_9CD90, size:0xE8
void fn_3_9CD90(void) {
    s16* c = (s16*)lbl_3_common_bss_32A94;
    s32 i;
    if (c[1] == 0) {
        if (*(s32*)(g_Strikes + 0x14) == 3) {
            c[0] = 0x10;
            return;
        }
        if (g_Runners[0x123] == 2) {
            if (*(s16*)(g_Ball + 0x1B7A) == 3 || g_FieldingLogic[0x108] == 2) {
                if (*(s16*)(g_Ball + 0x1B9A) > 0xA0) {
                    c[1] = 0x12;
                } else {
                    c[1] = 0x13;
                }
            } else {
                c[1] = 0x15;
            }
        }
        for (i = 1; i < 4; i++) {
            if (((RunnerT*)g_Runners)[i].s16_EE == 2) {
                c[1] = 0x15;
            }
        }
    }
}

// fn_3_9E834, size:0x1E8
s32 fn_3_9E834(void) {
    s32 i;
    if (g_d_GameSettings[8] == 0) {
        for (i = 0; i < 54; i++) {
            if (starMissionCompletionTracker[0x43D6 + i] != 0) {
                return 1;
            }
        }
    } else {
        for (i = 0; i < 54; i++) {
            if (lbl_80361B20[i] != 0) {
                return 1;
            }
        }
    }
    return 0;
}
