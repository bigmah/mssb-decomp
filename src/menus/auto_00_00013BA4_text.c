#include "menus/auto_00_00013BA4_text.h"
#include "main/file_8004207C.h"
#include "static/GameSettings.h"

extern DebugMenuState lbl_2_bss_100B8;
extern UnlockFlags lbl_80361B20;

// .text:0x00013BA4 size:0xFC
// Page 4: toggle one of the four flags at lbl_80361B20+0xE4.
void fn_2_13BA4(PortInput* in) {
    u16 repeat = in->repeat;
    if (repeat & 8) {
        lbl_2_bss_100B8.flagSel--;
        if ((s8)lbl_2_bss_100B8.flagSel < 0) {
            lbl_2_bss_100B8.flagSel = 3;
        }
    } else if (repeat & 4) {
        lbl_2_bss_100B8.flagSel++;
        if ((s8)lbl_2_bss_100B8.flagSel == 4) {
            lbl_2_bss_100B8.flagSel = 0;
        }
    } else if (repeat & 1) {
        lbl_80361B20.flagsE4[(s8)lbl_2_bss_100B8.flagSel] ^= 1;
    } else if (repeat & 2) {
        lbl_80361B20.flagsE4[(s8)lbl_2_bss_100B8.flagSel] ^= 1;
    } else if (in->pressed & 0x200) {
        lbl_2_bss_100B8.flagSel = 0;
        lbl_2_bss_100B8.page = 0;
    }
}

// .text:0x00013CA0 size:0xD0
// Page 3: toggle lbl_80361B20._F5.
void fn_2_13CA0(PortInput* in) {
    return;
}

// .text:0x00013D70 size:0x2FC
// Page 2: toggle unlock flags; 0x800 sets all, 0x400 clears all.
void fn_2_13D70(PortInput* in) {
    return;
}

// .text:0x0001406C size:0xF8
// Page 1: toggle g_d_GameSettings._1A entries.
void fn_2_1406C(PortInput* in) {
    return;
}

// .text:0x00014164 size:0xBC
// Top menu: pick a page (1..4).
void fn_2_14164(PortInput* in) {
    return;
}

// .text:0x00014220 size:0x354
void fn_2_14220(PortInput* in) {
    return;
}
