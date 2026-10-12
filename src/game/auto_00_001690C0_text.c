#include "game/auto_00_001690C0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/stl.h"

extern u8 lbl_3_data_28908[12];
extern u8 lbl_3_data_28914[10];
extern Bss35154View lbl_3_common_bss_35154;

// One-shot scene task: resets lbl_3_data_28908 and clears bit 1 of each lbl_3_data_28914 entry.

// .text:0x00169150 size:0x2C mapped:0x807A81E4
void fn_3_169150(void) {
    fn_800B0A5C_insertQueue(fn_3_1690C0, 0);
}

// .text:0x001690C0 size:0x90 mapped:0x807A8154
void fn_3_1690C0(void) {
    s32 i;
    u8* p;
    void* q;

    memset(lbl_3_data_28908, 0, 9);
    // removeQueue ignores its argument; the original leaves whatever was last in r3.
    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    p = &lbl_3_data_28914[8];
    i = 8;
    do {
        *p-- &= 0xFD;
    } while (i-- != 0);
    fn_800B0A14_removeQueue(p);
}

