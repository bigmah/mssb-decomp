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
void fn_3_1471C4(void) {
    return;
}

// .text:0x00147358 size:0x24 mapped:0x807863EC
void fn_3_147358(void) {
    pitchingMachinePitching(0x26);
}
