#include "game/auto_00_001471C0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_37A8.h"
#include "game/rep_1838.h"
#include "game/auto_00_0005985C_text.h"
extern void fn_3_10F550(s8 a, s16 b);

typedef struct {
    /* 0x0 */ u8 first;  // start delay base (frames)
    /* 0x1 */ u8 extra;  // added to `first` before the minigame starts
} MG1471Timing;

typedef struct {
    /* 0x0 */ s16 min;
    /* 0x2 */ s16 max;
} MG1471Range;

extern MG1471Timing lbl_3_data_21278;
extern MG1471Range lbl_3_data_21EAC[]; // per AI strength

extern void* memset(void* dst, int c, u32 n);

// .text:0x001471C0 size:0x4 mapped:0x80786254
void fn_3_1471C0(void) {
    return;
}

// .text:0x001471C4 size:0x194 mapped:0x80786258
// NONMATCHING 99%: loop counter i and the aIStrength pointer swap r27/r29 (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_3_1471C4(void) {
    MG1471View* view;
    MG1471Slot* slot;
    s8 i;

    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_146A90();
        break;
    case 26:
        switch (g_GameLogic._125) {
        case 0:
            fn_3_10F550(2, lbl_3_data_21278.first);
            changeScene(1, 6);
            g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
            g_GameLogic._125 = 1;
            break;
        case 1:
            if (g_GameLogic.FrameCountOfCurrentAtBat_Copy > lbl_3_data_21278.first + lbl_3_data_21278.extra) {
                g_GameLogic._125 = 2;
            }
            break;
        case 2:
            fn_3_5A6D4(0);
            break;
        }
        break;
    case 0:
        view = (MG1471View*)g_Minigame._1DBC;
        slot = view->slot;
        memset(g_Minigame._1D7C, 0, 0x78);
        i = 0;
        do {
            u8 str = g_Minigame.minigameControlStruct[0].aIStrength[i];
            slot[i].active = 1;
            slot[i].timer = RandomInt_Game_Range(lbl_3_data_21EAC[str].min, lbl_3_data_21EAC[str].max);
            i++;
        } while (i < 4);
        changeScene(1, 6);
        fn_3_5A6D4(2);
        break;
    case 2:
        fn_3_146408();
        break;
    }
}
#endif

// .text:0x00147358 size:0x24 mapped:0x807863EC
void fn_3_147358(void) {
    pitchingMachinePitching(0x26);
}
