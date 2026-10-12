#include "game/rep_0.h"
#include "Dolphin/stl.h"
#include "game/UnknownHomes_Game.h"
#define REP_HEADER_FN repHeader_0
#include "header_rep_inline.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1E08.h"

// ARAM load instruction (AssetLoadInstructions words: compression, size, disk offset,
// compressed size) for the team/roster file read by maybeProcessTeamData.
u32 lbl_3_data_0[4] = {0, 0x46E0, 0x06CF8800, 0x46E0};

// Unreferenced debug stadium names (22 bytes each).
char debugStadiumNames[12][22] = {
    "Yokohama Stadium    ",
    "Tokyo Dome          ",
    "Nagoya Dome         ",
    "Kousien Stadium     ",
    "Hirosima Stadium    ",
    "Jingu Stadium       ",
    "Green Stadium Kobe  ",
    "Osaka Dome          ",
    "Seibu Dome          ",
    "Fukuoka Dome        ",
    "Chiba Marine Stadium",
    "Sapporo Dome        ",
};

// fn_80036C88 source (23 sizes) and output buffer, see _prolog.
s32 lbl_3_data_118[2][23] = {
    {0x1040, 0, 0, 0x1880, 0x1C40, 0x65A0, 0x6B20, 0x2E40, 0, 0xFA0, 0, 0, 0, 0x940, 0x1000, 0x560, 0xBE0},
};

// .bss statics are laid out last-declared-first.
static u8 lbl_3_bss_10[8]; // [0] load step, [1] menu row, [2] option, [3] menu state
static u32 lbl_3_bss_8[2]; // unused
static u8* lbl_3_bss_4;    // team/roster file loaded from ARAM
static u32 lbl_3_bss_0;    // unused
extern u8 lbl_80354720[];
#include "main/aramloader.h" // lbl_803C6CF8
extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern void** lbl_803CC1B8;
#define PAD_BTN (*(u16*)((u8*)&lbl_803C77B8 + 4))

extern void fn_800BF038(void (*callback)(Mtx view, s32 arg));
extern void fn_3_C0824(void);
extern void fn_3_5AE9C(void);
extern s32 fn_80036C88(void*, void*);
extern void fn_800B0D28(void*);
extern void fn_8004B270(void);

// .text:0x0000049C size:0x58
void _prolog(void) {
    s32* p;
    fn_800B0A5C_insertQueue(fn_3_5AE9C, 1);
    fn_3_C0824();
    p = lbl_3_data_118[1];
    fn_80036C88(lbl_3_data_118[0], p);
    fn_800B0D28(p);
    fn_8004B270();
}

// .text:0x00000464 size:0x38
void _epilog(void) {
    g_d_GameSettings._55 = 0;
    fn_800BF038(NULL);
    fn_3_BF20C();
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
        if ((s32)lbl_803C6CF8.idle == 1) {
            lbl_3_bss_10[0]++;
        }
        break;
    case 2:
#ifdef TARGET_PC
        port_swap_char_stats(lbl_3_bss_4, 54);
#endif
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

