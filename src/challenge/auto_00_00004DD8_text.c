#include "challenge/auto_00_00004DD8_text.h"

// .text:0x00004DD8 size:0xC0
// Registers an effect file: a s16 count, then count + 1 file-relative offsets at +4,
// which are relocated in place.
void fn_1_4DD8(u16* file) {
    s32 i;
    u32* table;

#ifdef TARGET_PC
    // Swap the count and the offset table; the effects themselves are
    // swapped where they are parsed. TODO(port): effect contents.
    swap16_inplace(file);
    port_swap_offset_table(file + 2, (u32)((s16)file[0] + 1));
#endif
    lbl_1_common_bss_472B4.effectCount = file[0];
    lbl_1_common_bss_472B4.effects = (u32*)(file + 2);
    table = (u32*)(file + 2);
    for (i = (s16)file[0]; i >= 0; i--) {
        *table++ += PTR_TO_U32(file);
    }
}
