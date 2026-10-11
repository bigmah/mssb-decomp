#include "menus/auto_00_0005597C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"
#include "menus/rep_0788.h"

extern u8* lbl_2_bss_1A824C[];
extern u8* lbl_2_bss_1A823C[];
extern u8 lbl_800EF808[];
extern s16 fn_2_53BC8(void*);
extern void fn_2_4E7EC(void);
extern void fn_8001F228(void);
extern s32 fn_80021410(void);

// .text:0x0005597C size:0xC4
s32 fn_2_5597C(void) {
    u8* menu = lbl_2_bss_1A824C[0];
    s32 n = *(s16*)(menu + 0x1976FE) + *(s16*)(menu + 0x1976FA);
    s32 r;
    if (n < 0x1A) {
        r = 0;
    } else if (n < 0x34) {
        r = 1;
    } else if (n < 0x6A) {
        r = 2;
    } else if (n < 0x8C) {
        r = 3;
    } else if (n < 0x91) {
        r = 4;
    } else if (n < 0xC1) {
        r = 5;
    } else if (n < 0xC3) {
        r = 6;
    } else if (n < 0xC4) {
        r = 7;
    } else if (n < 0xD2) {
        r = 8;
    } else if (n < 0xD5) {
        r = 9;
    } else {
        r = 10;
    }
    return r;
}

// .text:0x00055A40 size:0x94
void fn_2_55A40(void) {
    lbl_2_bss_1A824C[0][0x1972BC] = 1;
    fn_2_4E7EC();
    fn_8001F228();
    fn_80021410();
    fn_800ACFB0(*(void**)(lbl_800EF808 + 0x14)); // TODO type
    fn_80035B50(10);
    if (lbl_80366B18.tables[2] != NULL) {
        fn_800ACFB0(lbl_80366B18.tables[2]);
        lbl_80366B18.tables[2] = NULL;
    }
    lbl_2_bss_1A823C[0][0x34] = 0;
}

// .text:0x00055AD4 size:0x188
void fn_2_55AD4(void) {
    return;
}

// .text:0x00055C5C size:0x17C
void fn_2_55C5C(void) {
    return;
}

// .text:0x00055DD8 size:0x200
void fn_2_55DD8(void) {
    return;
}

// .text:0x00055FD8 size:0x188
void fn_2_55FD8(void) {
    return;
}

// .text:0x00056160 size:0x260
void fn_2_56160(void) {
    return;
}

// .text:0x000563C0 size:0x2C8
void fn_2_563C0(void) {
    return;
}

// .text:0x00056688 size:0x314
void fn_2_56688(void) {
    return;
}

// .text:0x0005699C size:0x298
void fn_2_5699C(void) {
    return;
}

// .text:0x00056C34 size:0x258
void fn_2_56C34(void) {
    return;
}

// .text:0x00056E8C size:0x258
void fn_2_56E8C(void) {
    return;
}

// .text:0x000570E4 size:0x1B0
void fn_2_570E4(void) {
    return;
}

// .text:0x00057294 size:0x2B8
void fn_2_57294(void) {
    return;
}

// .text:0x0005754C size:0x1D8
void fn_2_5754C(void) {
    return;
}

// .text:0x00057724 size:0x148
void fn_2_57724(void) {
    return;
}

// .text:0x0005786C size:0x148
void fn_2_5786C(void) {
    return;
}

// .text:0x000579B4 size:0x244
void fn_2_579B4(void) {
    return;
}

// .text:0x00057BF8 size:0x358
void fn_2_57BF8(void) {
    return;
}

// .text:0x00057F50 size:0x148
void fn_2_57F50(void) {
    return;
}

// .text:0x00058098 size:0x148
void fn_2_58098(void) {
    return;
}

// .text:0x000581E0 size:0x148
void fn_2_581E0(void) {
    return;
}

// .text:0x00058328 size:0x148
void fn_2_58328(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
        item->state = 0x26;
        break;
    case 1:
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// .text:0x00058470 size:0xA0
void fn_2_58470(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0:
        item->state = 0x26;
        break;
    case 2:
        item->state = 0x25;
        break;
    case 1:
    case 5:
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// .text:0x00058510 size:0x2C
void fn_2_58510(MenuTableContext* menu, MenuItemState* item) {
    lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
}

// .text:0x0005853C size:0x2BC
void fn_2_5853C(void) {
    return;
}

// .text:0x000587F8 size:0xFA4
void fn_2_587F8(void) {
    return;
}
