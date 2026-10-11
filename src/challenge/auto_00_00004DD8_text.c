#include "challenge/auto_00_00004DD8_text.h"

// .text:0x00004DD8 size:0xC0
// Registers an effect file: a s16 count, then count + 1 file-relative offsets at +4,
// which are relocated in place.
void fn_1_4DD8(u16* file) {
    s32 i;
    u32* table;

    lbl_1_common_bss_472B4.effectCount = file[0];
    lbl_1_common_bss_472B4.effects = (u32*)(file + 2);
    table = (u32*)(file + 2);
    for (i = (s16)file[0]; i >= 0; i--) {
        // TODO port: file offsets are 32-bit; turning them into pointers needs a wider table
        *table++ += (u32)file;
    }
}
