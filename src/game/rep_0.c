#include "game/rep_0.h"
#include "Dolphin/stl.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1E08.h"


extern u8 lbl_3_bss_10[];
extern u8* lbl_3_bss_4;
extern u8 lbl_3_data_0[];
extern u8 lbl_80354720[];
extern u8 lbl_803C6CF8[];
extern s32 ARAMTransfer(void*, int, int, int);
extern void** lbl_803CC1B8;
#define PAD_BTN (*(u16*)((u8*)&lbl_803C77B8 + 4))

// .text:0x00000000 size:0x258
void maybeProcessTeamData(void) {
    s32 teams[2];
    u8* src;
    u8* e;
    s32 i, j, t;
    teams[0] = g_d_GameSettings.maybeHomeAway;
    teams[1] = g_d_GameSettings.maybeHomeAway2;
    switch (lbl_3_bss_10[0]) {
    case 0:
        lbl_3_bss_4 = (u8*)ARAMTransfer(lbl_3_data_0, 0, 1, 0);
        lbl_3_bss_10[0]++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            lbl_3_bss_10[0]++;
        }
        break;
    case 2:
        memcpy(&inMemRoster[0], lbl_3_bss_4 + teams[0] * 0x5A0, 0x5A0);
        memcpy(&inMemRoster[1], lbl_3_bss_4 + teams[1] * 0x5A0, 0x5A0);
        lbl_3_bss_10[0]++;
        break;
    case 3:
        for (t = 0; t < 2; t++) {
            src = lbl_3_bss_4 + teams[t] * 0x48 + 0x4380;
            for (i = 0; i < 9; i++) {
                e = lbl_80354720 + t * 0x24 + i * 4;
                e[0] = i;
                e[1] = 10;
                e[2] = 10;
                e[3] = 0;
                for (j = 0; j < 9; j++) {
                    if (i == src[j]) {
                        break;
                    }
                }
                if (j < 9) {
                    e[1] = j;
                    e[2] = src[j + 9];
                    e[3] = 1;
                }
            }
        }
        lbl_3_bss_10[0]++;
        break;
    }
}

// .text:0x00000258 size:0x20C
void fn_3_258(void) {
    u8 st = lbl_3_bss_10[3];
    u16 b;
    if (st == 0) {
        b = PAD_BTN;
        if ((b & 8) && lbl_3_bss_10[1] != 0) {
            lbl_3_bss_10[1]--;
        }
        if ((b & 4) && lbl_3_bss_10[1] < 1) {
            lbl_3_bss_10[1]++;
        }
        if (b & 0x100) {
            lbl_3_bss_10[3] = 1;
        }
    } else if (st == 1 && lbl_3_bss_10[1] == 0) {
        b = PAD_BTN;
        if ((b & 8) && lbl_3_bss_10[2] != 0) {
            lbl_3_bss_10[2]--;
        }
        if ((b & 4) && lbl_3_bss_10[2] < 3) {
            lbl_3_bss_10[2]++;
        }
        if (b & 0x100) {
            lbl_3_bss_10[3] = 3;
        }
        if (b & 0x200) {
            lbl_3_bss_10[3] = 0;
        }
    } else if (st == 1 && lbl_3_bss_10[1] == 1) {
        g_d_GameSettings.GameModeSelected = 2;
        *lbl_803CC1B8 = maybeProcessTeamData;
    } else if (st != 2) {
        if (st == 3) {
            b = PAD_BTN;
            if ((b & 1) && g_d_GameSettings.StadiumID != 0) {
                g_d_GameSettings.StadiumID--;
            }
            if ((b & 2) && g_d_GameSettings.StadiumID < 10) {
                g_d_GameSettings.StadiumID++;
            }
            if (b & 0x100) {
                lbl_3_bss_10[3] = 4;
            }
            if (b & 0x200) {
                lbl_3_bss_10[3] = 1;
            }
        } else if (st == 4) {
            g_d_GameSettings.GameModeSelected = 0;
            ((u8*)&g_d_GameSettings)[0x10] = lbl_3_bss_10[2];
            *lbl_803CC1B8 = maybeProcessTeamData;
        }
    }
}

extern void fn_800BF038(int);
extern void fn_3_C0824(void);
extern void fn_3_5AE9C(void);
extern void fn_80036C88(void*, void*);
extern void fn_800B0D28(void*);
extern void fn_8004B270(void);
extern u8 lbl_3_data_118[];

// .text:0x00000464 size:0x38
void _epilog(void) {
    g_d_GameSettings._55 = 0;
    fn_800BF038(0);
    fn_3_BF20C();
}

// .text:0x0000049C size:0x58
void _prolog(void) {
    u8* p;
    fn_800B0A5C_insertQueue(fn_3_5AE9C, 1);
    fn_3_C0824();
    p = lbl_3_data_118 + 0x5C;
    fn_80036C88(lbl_3_data_118, p);
    fn_800B0D28(p);
    fn_8004B270();
}
