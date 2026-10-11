#include "game/auto_00_000C0810_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// Stadium effect state (lbl_3_common_bss_35154); only the field used here.
typedef struct C0810State {
    u8 pad0[0x479];
    u8 flag479; // 0x479
} C0810State;

extern C0810State lbl_3_common_bss_35154;

// .text:0x000C0810 size:0x14 mapped:0x806FF8A4
void fn_3_C0810(void) {
    lbl_3_common_bss_35154.flag479 = 0;
}

// .text:0x000C0824 size:0x30 mapped:0x806FF8B8
void fn_3_C0824(void) {
    return;
}

