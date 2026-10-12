#include "challenge/auto_00_00001538_text.h"
#include "challenge/rep_0000.h"
#include "challenge/rep_0010.h"
#include "challenge/auto_00_000085A8_text.h"
#include "challenge/auto_00_00026AF8_text.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80008E00.h"
#include "Unknown/File_0x800a64e0.h"
extern u8 lbl_803C6CF8[]; // TODO type: ARAMLoader (main/file_800A6870.h); idle at 0x715

extern void fn_800A7D4C(s32 list, void* node);
extern u8 lbl_803CBBC0; // frame buffer index (0/1)

// Test entry points (other challenge units).
extern void fn_1_66C4(void);
extern void fn_1_17D90(void);
extern void fn_1_28200(void);
extern void fn_1_1D514(void);
extern void fn_1_A2E4(void);
extern void fn_1_24778(void);
extern void fn_1_2852C(void);
extern void fn_1_29A9C(void);

// Texture viewer task (fn_1_1634 -> fn_1_15CC -> fn_1_1538).
typedef struct ChTexViewTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ s32* file;         // loaded file; word 0 is the offset of the texture archive
    /*0x18*/ ChTexArchive* tex; // inside file
} ChTexViewTask;

extern s32 lbl_1_bss_0; // texture shown by the viewer
extern ChDrawNode lbl_1_data_298[2];

// lbl_1_data_0 (0xA8 bytes): ARAM files of the challenge menu, the viewer's draw nodes and colour mode.
// The original addresses all four through one .data base.
// AssetLoadInstructions words (the stadium archive table, as lbl_3_data_10ACC in game).
static u32 ch_files[7][4] = {
    0x0000040B, 0x40022EF0, 0x07684800, 0x00016B18,
    0x0000040B, 0x40020260, 0x0769B800, 0x00012864,
    0x0000040B, 0x4002FDC0, 0x076AE800, 0x000207F8,
    0x0000040B, 0x40024E2C, 0x076CF000, 0x000159AC,
    0x0000040B, 0x4001CB88, 0x076E5000, 0x0000EE60,
    0x0000040B, 0x40035BD0, 0x076F4000, 0x000257FC,
    0x0000040B, 0x400397CC, 0x07719800, 0x00023FF4,
};
static ChTexDrawNode ch_nodes[2] = {{NULL, fn_1_1240}, {NULL, fn_1_1240}}; // per frame buffer
static u32 ch_mode = 2; // ChTexDrawNode.mode
static GXColor ch_color = {0xFF, 0xFF, 0xFF, 0xFF};

// .text:0x00001538 size:0x94
// Queues this frame's texture draw node.
void fn_1_1538(void) {
    ChTexViewTask* task = lbl_803CC1B8;

    fn_800A7D4C(0, &ch_nodes[lbl_803CBBC0]);
    ch_nodes[lbl_803CBBC0].tex = task->tex;
    ch_nodes[lbl_803CBBC0].texIdx = lbl_1_bss_0;
    ch_nodes[lbl_803CBBC0].mode = ch_mode;
    ch_nodes[lbl_803CBBC0].color = ch_color;
}

// .text:0x000015CC size:0x68
void fn_1_15CC(void) {
    ChTexViewTask* task = lbl_803CC1B8;

    if ((s32)lbl_803C6CF8[0x715] == 1) {
        task->tex = (ChTexArchive*)((u8*)task->file + *task->file);
        convertTextureHeader(task->tex);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1538;
    }
}

// .text:0x00001634 size:0x6C
void fn_1_1634(void) {
    if ((s32)lbl_803C6CF8[0x715] == 1) {
        ((ChTexViewTask*)lbl_803CC1B8)->file = (s32*)ARAMTransfer(ch_files[3], 0, 0, 0);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_15CC;
    }
}

// .text:0x000016A0 size:0x2A8
// Test menu: up/down picks a test, A starts it, Z quits.
void fn_1_16A0(void) {
    ChMenuTask* task = lbl_803CC1B8;

    if (lbl_803C77B8._04 == 8) {
        if (--task->cursor < 0) {
            task->cursor = 9;
        }
    } else if (lbl_803C77B8._04 == 4) {
        if (++task->cursor >= 10) {
            task->cursor = 0;
        }
    } else if (lbl_803C77B8._02 == 0x100) {
        switch ((u8)task->cursor) {
        case 0:
            fn_800B0A5C_insertQueue(fn_1_66C4, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 1:
            fn_800B0A5C_insertQueue(fn_1_8B90, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 2:
            fn_800B0A5C_insertQueue(fn_1_17D90, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 3:
            fn_800B0A5C_insertQueue(fn_1_28200, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 4:
            fn_800B0A5C_insertQueue(fn_1_1D514, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 5:
            fn_800B0A5C_insertQueue(fn_1_26AF8, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 6:
            fn_800B0A5C_insertQueue(fn_1_A2E4, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 7:
            fn_800B0A5C_insertQueue(fn_1_24778, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 8:
            fn_800B0A5C_insertQueue(fn_1_2852C, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 9:
            fn_800B0A5C_insertQueue(fn_1_29A9C, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            break;
        }
    } else if (lbl_803C77B8._02 == 0x1000) {
        task->h.parent->result = 1;
    } else if ((lbl_803C77B8._00 & 0xA00) == 0xA00) {
        task->h.func = fn_1_58C;
    }
}

// .text:0x00001948 size:0x24
// Waits for the running test to finish.
void fn_1_1948(void) {
    ChTaskHeader* task = lbl_803CC1B8;

    if (task->result != 0) {
        task->func = fn_1_11D0;
    }
}

// .text:0x0000196C size:0x40
void fn_1_196C(void) {
    fn_800A7D4C(0, &lbl_1_data_298[lbl_803CBBC0]);
}
