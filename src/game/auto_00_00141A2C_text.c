#include "game/auto_00_00141A2C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_36D8.h"
#include "game/rep_13B8.h"
#include "game/rep_1838.h"
#include "game/auto_00_0005985C_text.h"

typedef struct {
    /* 0x0 */ u8 first; // start delay base (frames)
    /* 0x1 */ u8 extra; // added to `first` before the minigame starts
} MG141Timing;

typedef struct {
    /* 0x0 */ s16 min;
    /* 0x2 */ s16 max;
} MG141Range16;

typedef struct {
    /* 0x0 */ s8 min;
    /* 0x1 */ s8 max;
} MG141Range8;

extern MG141Timing lbl_3_data_21278;
extern MG141Range8 lbl_3_data_21944[];  // per AI strength
extern MG141Range16 lbl_3_data_2194C[]; // per AI strength
extern s8 lbl_3_data_2197C[];           // per AI strength: chance (percent)
extern s8 lbl_3_data_21980[];           // per AI strength: minimum value

extern void fn_3_10F550(s8 a, s16 b);
extern void* memset(void* dst, int c, size_t n);

// .text:0x00141A2C size:0x4 mapped:0x80780AC0
void fn_3_141A2C(void) {
    return;
}

// .text:0x00141A30 size:0x214 mapped:0x80780AC4
// NONMATCHING 99%: loop counter i gets r29 instead of r26 (table bases shift down one); same as fn_3_1412BC in rep_36D8
#if NONMATCHING
void fn_3_141A30(void) {
    MG141Slot* slot;
    u8 str;
    s8 i;
    s8 lo;

    switch (g_GameLogic.gameStatus) {
    case 4:
        fn_3_1414AC();
        break;
    case 26:
        fn_3_7DD6C();
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
        slot = ((MG141View*)&g_Minigame)->slot;
        memset(g_Minigame._1D7C, 0, 0x78);
        i = 0;
        do {
            str = g_Minigame.minigameControlStruct[0].aIStrength[i];
            slot->timer = RandomInt_Game_Range(lbl_3_data_2194C[str].min, lbl_3_data_2194C[str].max);
            if (RandomInt_Game(100) < lbl_3_data_2197C[str]) {
                lo = lbl_3_data_21980[str];
                if (lo < 8) {
                    slot->_6 = RandomInt_Game_Range(lo, 8);
                } else {
                    slot->_6 = 8;
                }
            } else {
                slot->_6 = 0x7F;
            }
            slot->_5 = 2;
            slot->_7 = RandomInt_Game_Range(lbl_3_data_21944[str].min, lbl_3_data_21944[str].max);
            i++;
            slot++;
        } while (i < 4);
        changeScene(1, 6);
        fn_3_5A6D4(2);
        break;
    case 2:
        fn_3_140CE0();
        break;
    case 15:
        fn_3_1410F0();
        break;
    }
}
#endif
