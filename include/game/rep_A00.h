#ifndef __GAME_rep_A00_H_
#define __GAME_rep_A00_H_

#include "mssbTypes.h"

// Screen-fade task (lbl_803CC1B8 while fn_3_21C90 / fn_3_21DE4 run); only the fields used here.
typedef struct FadeTask {
    /*0x00*/ u8 _00[0x1E];
    /*0x1E*/ u16 frame;
    /*0x20*/ u16 alpha;
    /*0x22*/ s16 state; // fn_3_21AA8 wait task
} FadeTask;

#ifdef TARGET_PC
#include "main/aramloader.h" // ARAMLoader lbl_803C6CF8 (holds pointers)
typedef ARAMLoader ARAMLoaderView;
#else
// View of the DVD/ARAM loader lbl_803C6CF8 (ARAMLoader in main/file_800A6870.h).
typedef struct ARAMLoaderView {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ volatile u8 idle;
} ARAMLoaderView;
#endif

// lbl_3_data_7F7C entry (indexed by lbl_800E8558[char]._2); only the fields used here.
typedef struct CharVoiceAnim {
    /*0x0*/ s16 anim;  // batter animation frame that triggers the voice (fn_3_23CEC)
    /*0x2*/ u8 _2[2];
    /*0x4*/ s16 anim2; // same for fn_3_240F8
    /*0x6*/ s16 sceneFrame; // scene frame for the captain's voice (fn_3_22C20)
} CharVoiceAnim; // size: 0x8

void fn_3_21C90(void);
void fn_3_21DE4(void);
s32 fn_3_21F14(void);
s32 fn_3_2273C(void);
s32 fn_3_2281C(s32 i);
void fn_3_22850(void);
void fn_3_22944(void);
void fn_3_22948(void);
s32 fn_3_22A20(void);
s32 fn_3_22ABC(void);
void fn_3_22C10(void);
void fn_3_22C20(void);
void fn_3_230D4(void);
void fn_3_234BC(void);
void fn_3_23890(void);
void fn_3_23CEC(void);
void fn_3_240F8(void);
void fn_3_24598(void);
void fn_3_24630(void);
void fn_3_24708(void);

#endif // !__GAME_rep_A00_H_
