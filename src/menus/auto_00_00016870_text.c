#include "menus/auto_00_00016870_text.h"

extern u8 lbl_2_bss_100B8[];


// fn_2_16A34, size:0x14
u8 fn_2_16A34(s32 index) {
    u8* entry = lbl_2_bss_100B8 + index;
    return entry[0x46];
}
