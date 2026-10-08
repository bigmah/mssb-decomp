#include "Unknown/auto_03_800A8864_text.h"

extern u8 lbl_803CC135;

extern u8 lbl_803CC134;

// fn_800A8864, size:0x14
u16 fn_800A8864(void) {
    u16 value = lbl_803CC135;
    value = (value << 8) | lbl_803CC134;
    return value;
}
