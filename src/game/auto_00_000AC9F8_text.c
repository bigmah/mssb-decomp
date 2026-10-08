#include "game/auto_00_000AC9F8_text.h"
#include "game/UnknownHomes_Game.h"

#include "game/auto_00_000B3B70_text.h"

extern u8 lbl_3_common_bss_34C90[];

// fn_3_AFDA4, size:0x1C
void fn_3_AFDA4(void) {
    lbl_3_common_bss_34C90[0x1D5] = 0;
    lbl_3_common_bss_34C90[0x1D6] = 0;
    lbl_3_common_bss_34C90[0x1D7] = 0;
}

// fn_3_AFD80, size:0x24
void fn_3_AFD80(u8 state) {
    lbl_3_common_bss_34C90[0x1D1] = state;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0xE) = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0x10) = 0;
}

// fn_3_B0A88, size:0x24
void fn_3_B0A88(void) {
    fn_3_B3C78(0);
}
