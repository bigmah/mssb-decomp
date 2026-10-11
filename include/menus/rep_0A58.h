#ifndef __MENUS_REP_0A58_H_
#define __MENUS_REP_0A58_H_

#include "mssbTypes.h"

// View of one lbl_803C77B8 controller entry (PadState in main/file_800A7C08.h).
typedef struct Menu0A58Pad {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u8 _06[0xC - 0x6];
    /*0x0C*/ u8 kind; // 0xC: held buttons also count as repeats
    /*0x0D*/ u8 _0D[0x20 - 0xD];
} Menu0A58Pad;

// Scene task (lbl_803CC1B8 / fn_800B0A5C_insertQueue result), only the fields used here.
typedef struct MenuSceneTask0A58 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s16 _10; // set to 1 by the child task when it is done
    /*0x12*/ u8 _12[0x1C - 0x12];
    /*0x1C*/ s16 _1C;
    /*0x1E*/ s16 _1E;
    /*0x20*/ u8 _20[0x28 - 0x20];
    /*0x28*/ u8 _28;
} MenuSceneTask0A58;

// Menu draw slot (lbl_2_bss_1A8234[0], [rows][864]); MenuDrawEntry in auto_00_0004B1AC_text.c.
typedef struct MenuDrawEntry0A58 {
    /*0x00*/ void* draw;
    /*0x04*/ u8 _04[0x4];
    /*0x08*/ s16 column;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 row;
    /*0x0E*/ s16 _0E;
    /*0x10*/ s16 _10;
    /*0x12*/ u8 _12[0x18 - 0x12];
} MenuDrawEntry0A58; // size: 0x18

// Initial draw slot table (lbl_2_data_1F8F0 + 0xCE4, 43 entries).
typedef struct Menu0A58Seed {
    /*0x00*/ void* draw;
    /*0x04*/ s16 column;
    /*0x06*/ s16 _06;
    /*0x08*/ s16 row;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 _0C;
    /*0x0E*/ u8 _0E[0x2];
} Menu0A58Seed; // size: 0x10

void fn_2_54BB0(void);

#endif
