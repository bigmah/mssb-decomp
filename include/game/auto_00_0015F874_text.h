#ifndef __GAME_AUTO_00_0015F874_TEXT_H_
#define __GAME_AUTO_00_0015F874_TEXT_H_

#include "mssbTypes.h"
#include "Dolphin/mtx.h"

// Screen-fade state (lbl_3_common_bss_35154); only the fields used by this unit.
typedef struct FadeState {
    /*0x000*/ u8 _000[0x468];
    /*0x468*/ s32 level;     // current fade amount (0..FadeParams.scale)
    /*0x46C*/ u8 _46C[4];
    /*0x470*/ u8 active;
    /*0x471*/ u8 done;
    /*0x472*/ u8 count;      // number of entries in ids
    /*0x473*/ u8 ids[6];
    /*0x479*/ u8 disabled;
} FadeState;

extern FadeState lbl_3_common_bss_35154;

// lbl_3_data_27F10: fade timing.
typedef struct FadeParams {
    /*0x0*/ s32 scale;    // final fade level
    /*0x4*/ s32 duration; // frames
} FadeParams;

extern FadeParams lbl_3_data_27F10;

// Pooled data starting at lbl_3_data_27EC0 (reached through one base register in
// fn_3_15F874; the fields below lie past that symbol, inside lbl_3_data_27F10).
typedef struct FadeDrawData {
    /*0x000*/ u8 _000[0x244];
    /*0x244*/ Mtx44 proj;
    /*0x284*/ u8 _284[0x2A0 - 0x284];
    /*0x2A0*/ u8 displayList[0x20];
    /*0x2C0*/ f32 posA[4][3];
    /*0x2F0*/ u8 _2F0[0x10];
    /*0x300*/ f32 posB[4][3];
} FadeDrawData;

extern FadeDrawData lbl_3_data_27EC0;

void fn_3_15F874(s32 useB);
void fn_3_15F998(void);
void fn_3_15F9AC(void);
void fn_3_15F9C0(void);
void fn_3_15FA58(s32 n, s32* ids);

#endif
