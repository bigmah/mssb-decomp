#include "game/auto_00_000E587C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_data_196B4[]; // 7 hit flags (see sta_c6.c)

// .text:0x000E587C size:0xA8 mapped:0x80724910
// Returns the index of the only set flag, or -1 if zero or several are set.
s32 fn_3_E587C(void) {
    s32 i;
    s32 count = 0;
    s32 last;

    for (i = 0; i < 7; i++) {
        if (lbl_3_data_196B4[i] != 0) {
            last = i;
            count++;
        }
    }
    if (count != 1) {
        return -1;
    }
    return last;
}

// .text:0x000E5924 size:0x90 mapped:0x807249B8
// Returns 1 if all 7 flags are set.
s32 fn_3_E5924(void) {
    return 0;
}
