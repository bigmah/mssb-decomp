#include "game/rep_0.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1E08.h"


extern u8 lbl_3_bss_10[];
extern void** lbl_803CC1B8;
#define PAD_BTN (*(u16*)((u8*)&lbl_803C77B8 + 4))

// .text:0x00000000 size:0x258
void maybeProcessTeamData(void) {
    return;
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
