// One-time fixups of game data that is defined as raw big-endian bytes.
//
// Some objects are declared `u8[]` in the game sources (so they are defined
// or generated as the original bytes) but read through wider types. The ones
// listed here hold file-load records (AssetLoadInstructions: four u32 words
// each) that ARAMTransfer/fn_80035838 read; their words are byte-swapped once
// at startup, before the game runs. Retyping the declarations (so
// port/tools/gen_data.py emits native values) would make these unnecessary.
#include <stddef.h>
#include <stdint.h>

#include "port/endian.h"

#define REGION(sym, off, len)       \
    extern uint8_t sym[];           \
    static void fix_##sym(void) { swap32_array(sym + (off), (len) / 4); }

// menus.rel .data
REGION(lbl_2_data_180, 0x2C4, 0x100)
REGION(lbl_2_data_720, 0x5F4, 0x100)
REGION(lbl_2_data_130C, 0x8, 0x100)
REGION(lbl_2_data_2B3A4, 0x38, 0x100)
REGION(lbl_2_data_2E02C, 0x1C0, 0x100)
REGION(lbl_2_data_1326C, 0, 0x70)
REGION(lbl_2_data_1F884, 0, 0x10)
REGION(lbl_2_data_1F894, 0, 0x10)
REGION(lbl_2_data_1FF84, 0, 0x10)
REGION(lbl_2_data_1FF94, 0, 0x20)
// game.rel .data
REGION(lbl_3_data_21EC8, 0, 0x3E0)
REGION(lbl_3_data_F538, 0, 0x3E0)
REGION(lbl_3_data_10598, 0, 0x3E0)
REGION(lbl_3_data_10578, 0, 0x20)
// main.dol .data
REGION(lbl_800F73A8, 0, 0x10)

void port_data_fixups(void)
{
    static int done;
    if (done)
        return;
    done = 1;
    fix_lbl_2_data_180();
    fix_lbl_2_data_720();
    fix_lbl_2_data_130C();
    fix_lbl_2_data_2B3A4();
    fix_lbl_2_data_2E02C();
    fix_lbl_2_data_1326C();
    fix_lbl_2_data_1F884();
    fix_lbl_2_data_1F894();
    fix_lbl_2_data_1FF84();
    fix_lbl_2_data_1FF94();
    fix_lbl_3_data_21EC8();
    fix_lbl_3_data_F538();
    fix_lbl_3_data_10598();
    fix_lbl_3_data_10578();
    fix_lbl_800F73A8();
}
