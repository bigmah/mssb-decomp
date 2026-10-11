#include "menus/auto_00_0005597C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"
#include "menus/rep_0788.h"
#include "main/file_80069BDC.h"
#include <string.h>

extern u8* lbl_2_bss_1A824C[];
extern u8* lbl_2_bss_1A823C[];
extern u8* lbl_2_bss_1A8240[];
extern u8 lbl_800EF808[];
extern s16 lbl_2_data_1FD84[];
extern s16 lbl_2_data_1FBB4[];
extern s16 fn_2_53BC8(void*);
struct SpaniOwner;
void fn_80036134(struct SpaniOwner* owner, s32 srcIdx, u32 track, s32 dstIdx);
s32 fn_80036214(struct SpaniOwner* owner, s32 idx, u32 track, u32 frame);
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
void fn_2_55AD4(MenuTableContext* menu, MenuItemState* item) {
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
    case 8:
    case 0x11:
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] > 1) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = *(s8*)(lbl_2_bss_1A824C[0] + 0x197822) << 16;
        }
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        }
        break;
    case 0x25:
        break;
    }
}

// .text:0x00055C5C size:0x17C
void fn_2_55C5C(MenuTableContext* menu, MenuItemState* item) {
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
    case 8:
    case 0x11:
    {
        s16 count = lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)];
        if (count > 1) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = (count - 1) << 16;
        }
    }
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        }
        break;
    case 0x25:
        break;
    }
}

// .text:0x00055DD8 size:0x200
void fn_2_55DD8(MenuTableContext* menu, MenuItemState* item) {
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
    case 8:
    case 0x11:
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] > 1) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        }
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
        item->state = 6;
        break;
    case 6: {
        LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    }
    case 7:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        break;
    case 0x25:
        break;
    }
}

// .text:0x00055FD8 size:0x188
void fn_2_55FD8(MenuTableContext* menu, MenuItemState* item) {
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
    case 8:
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] > 1) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        }
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        }
        break;
    case 0x25:
        break;
    }
}

// .text:0x00056160 size:0x260
void fn_2_56160(MenuTableContext* menu, MenuItemState* item) {
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
    case 8:
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] > 1) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
        }
        item->state = 0x25;
        break;
    case 5:
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] > 1) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
            item->state = 6;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        }
        break;
    case 6: {
        LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    }
    case 7:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        break;
    case 0x25:
        break;
    }
}

// .text:0x000563C0 size:0x2C8
void fn_2_563C0(MenuTableContext* menu, MenuItemState* item) {
    s16 msg;
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    msg = *(s8*)(lbl_2_bss_1A824C[0] + 0x197822) +
          lbl_2_data_1FBB4[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA)];
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->unk12 = 0;
        item->unk14 = fn_8000F988((LayoutGroup*)menu, item->offset, item->unk10, 2, lbl_2_data_1FBB4[0], 0);
        item->state = 0x26;
        break;
    case 2:
        fn_8000FE08(item->unk14, 2, msg);
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        fn_8000FE08(item->unk14, 2, msg);
        item->state = 3;
        break;
    case 3:
        item->unk12 += (0xFF - item->unk12) / 4;
        item->unk12++;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 0x25;
        }
        break;
    case 0x25:
        fn_8000FE08(item->unk14, 2, msg);
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 6;
        break;
    case 6:
        item->unk12 += (0 - item->unk12) / 4;
        item->unk12--;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        break;
    case 1:
    case 4:
        break;
    }
    lbl_80366B18.entries[item->unk14].hAlign = 0;
    lbl_80366B18.entries[item->unk14].vAlign = 1;
    lbl_80371C30[menu->firstIndex + item->offset].obj->color =
        (lbl_80371C30[menu->firstIndex + item->offset].obj->color & ~0xFF) | item->unk12;
}

// .text:0x00056688 size:0x314
void fn_2_56688(MenuTableContext* menu, MenuItemState* item) {
    s16 msg;
    u32 color;
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    msg = (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE) + item->index) % *(s16*)(lbl_2_bss_1A824C[0] + 0x19772E);
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->unk12 = 0;
        item->unk14 = fn_8000F988((LayoutGroup*)menu, item->offset, item->unk10, 2, 0, 1);
        item->state = 0x26;
        break;
    case 2:
        fn_8000FE08(item->unk14, 2, msg);
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        fn_8000FE08(item->unk14, 2, msg);
        item->state = 3;
        break;
    case 3:
        item->unk12 += (0xFF - item->unk12) / 4;
        item->unk12++;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 0x25;
        }
        break;
    case 0x25:
        fn_8000FE08(item->unk14, 2, msg);
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 6;
        break;
    case 6:
        item->unk12 += (0 - item->unk12) / 4;
        item->unk12--;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        break;
    case 1:
    case 4:
        break;
    }
    if (item->index == *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA)) {
        color = fn_80036214((struct SpaniOwner*)menu, 0x25, 0, 1);
    } else {
        color = fn_80036214((struct SpaniOwner*)menu, 0x26, 0, 0);
    }
    lbl_80371C30[menu->firstIndex + item->offset].obj->color =
        (lbl_80371C30[menu->firstIndex + item->offset].obj->color & 0xFF) | (color & ~0xFF);
    lbl_80366B18.entries[item->unk14].hAlign = 0;
    lbl_80371C30[menu->firstIndex + item->offset].obj->color =
        (lbl_80371C30[menu->firstIndex + item->offset].obj->color & ~0xFF) | item->unk12;
}

// .text:0x0005699C size:0x298
void fn_2_5699C(MenuTableContext* menu, MenuItemState* item) {
    s16 msg;
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    msg = *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA);
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->unk12 = 0;
        item->unk14 = fn_8000F988((LayoutGroup*)menu, item->offset, item->unk10, 2, 0, 0);
        item->state = 0x26;
        break;
    case 2:
        fn_8000FE08(item->unk14, 2, msg);
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        fn_8000FE08(item->unk14, 2, msg);
        item->state = 3;
        break;
    case 3:
        item->unk12 += (0xFF - item->unk12) / 4;
        item->unk12++;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 0x25;
        }
        break;
    case 0x25:
        fn_8000FE08(item->unk14, 2, msg);
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 6;
        break;
    case 6:
        item->unk12 += (0 - item->unk12) / 4;
        item->unk12--;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        break;
    case 1:
    case 4:
        break;
    }
    lbl_80366B18.entries[item->unk14].hAlign = 1;
    lbl_80371C30[menu->firstIndex + item->offset].obj->color =
        (lbl_80371C30[menu->firstIndex + item->offset].obj->color & ~0xFF) | item->unk12;
}

// .text:0x00056C34 size:0x258
void fn_2_56C34(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->unk12 = 0;
        item->unk14 = fn_8000F988((LayoutGroup*)menu, item->offset, item->unk10, 2, 0x213, 0);
        item->state = 0x26;
        break;
    case 2:
        fn_8000FE08(item->unk14, 2, item->index + 0x213);
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        item->state = 3;
        break;
    case 3:
        item->unk12 += (0xFF - item->unk12) / 4;
        item->unk12++;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 0x25;
        }
        break;
    case 0x25:
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 6;
        break;
    case 6:
        item->unk12 += (0 - item->unk12) / 4;
        item->unk12--;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        break;
    case 1:
    case 4:
        break;
    }
    lbl_80366B18.entries[item->unk14].hAlign = 1;
    lbl_80371C30[menu->firstIndex + item->offset].obj->color =
        (lbl_80371C30[menu->firstIndex + item->offset].obj->color & ~0xFF) | item->unk12;
}

// .text:0x00056E8C size:0x258
void fn_2_56E8C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->unk12 = 0;
        item->unk14 = fn_8000F988((LayoutGroup*)menu, item->offset, item->unk10, 2, 0x215, 0);
        item->state = 0x26;
        break;
    case 2:
        fn_8000FE08(item->unk14, 2, item->index + 0x215);
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        item->state = 3;
        break;
    case 3:
        item->unk12 += (0xFF - item->unk12) / 4;
        item->unk12++;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 0x25;
        }
        break;
    case 0x25:
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 6;
        break;
    case 6:
        item->unk12 += (0 - item->unk12) / 4;
        item->unk12--;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        break;
    case 1:
    case 4:
        break;
    }
    lbl_80366B18.entries[item->unk14].hAlign = 1;
    lbl_80371C30[menu->firstIndex + item->offset].obj->color =
        (lbl_80371C30[menu->firstIndex + item->offset].obj->color & ~0xFF) | item->unk12;
}

// .text:0x000570E4 size:0x1B0
void fn_2_570E4(MenuTableContext* menu, MenuItemState* item) {
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
        lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        fn_80036134((struct SpaniOwner*)menu, 0x1C, *(s16*)(lbl_2_bss_1A824C[0] + 0x1976F4), 0x1A);
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 0x25:
        fn_80036134((struct SpaniOwner*)menu, 0x1C, *(s16*)(lbl_2_bss_1A824C[0] + 0x1976F4), 0x1A);
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1:
        break;
    }
}

// .text:0x00057294 size:0x2B8
void fn_2_57294(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        fn_80036134((struct SpaniOwner*)menu, 0x1B, item->index, item->index + 0xF);
        lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
        fn_800363D8(menu, item->offset, 1, 0x15, item->index);
        item->timer = item->index;
        item->state = 0x26;
        break;
    case 2:
        if (item->timer-- <= 0) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
            item->state = 3;
        }
        break;
    case 3: {
        LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
        if ((obj->_5C >> 16) >= 5) {
            obj->_68 = 0;
            item->state = 0x25;
        }
        break;
    }
    case 0x25:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976F4) == item->index) {
            LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
            if ((obj->_5C >> 16) >= 0xF) {
                obj->_5C = 0xF << 16;
            } else {
                obj->_68 = 1;
            }
        } else {
            LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
            if ((obj->_5C >> 16) <= 5) {
                obj->_5C = 5 << 16;
            } else {
                obj->_68 = 4;
            }
        }
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
        item->state = 0x26;
        break;
    case 1:
    case 4:
        break;
    }
}

// .text:0x0005754C size:0x1D8
void fn_2_5754C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        fn_80036134((struct SpaniOwner*)menu, 0x1D, *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA), 0xE);
        lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 0x25:
        fn_80036134((struct SpaniOwner*)menu, 0x1D, *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA), 0xE);
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1:
    case 4:
        break;
    }
}

// .text:0x00057724 size:0x148
void fn_2_57724(MenuTableContext* menu, MenuItemState* item) {
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

// .text:0x0005786C size:0x148
void fn_2_5786C(MenuTableContext* menu, MenuItemState* item) {
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

// .text:0x000579B4 size:0x244
void fn_2_579B4(MenuTableContext* menu, MenuItemState* item) {
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
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] >= 2) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        }
        item->state = 0x25;
        break;
    case 0x25:
        if (lbl_2_data_1FD84[*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) + *(s16*)(lbl_2_bss_1A824C[0] + 0x1976FE)] >= 2) {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags |= 2;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        }
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 1:
        break;
    }
}

// .text:0x00057BF8 size:0x358
void fn_2_57BF8(MenuTableContext* menu, MenuItemState* item) {
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
        lbl_80371C30[menu->firstIndex + item->offset].obj->_5C = 0;
        fn_80036134((struct SpaniOwner*)menu, 0x1E, item->index, item->index + 5);
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
        item->state = 3;
        break;
    case 3:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) == item->index) {
            LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
            if ((obj->_5C >> 16) >= 0x14) {
                obj->_5C = 0x14 << 16;
                lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 0;
                item->state = 0x25;
            }
        } else {
            LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
            if ((obj->_5C >> 16) >= 0xA) {
                obj->_5C = 0xA << 16;
                lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 0;
                item->state = 0x25;
            }
        }
        break;
    case 0x25:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976FA) == item->index) {
            LayoutObj* obj;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 1;
            obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
            if ((obj->_5C >> 16) >= 0x14) {
                obj->_5C = 0x14 << 16;
            }
        } else {
            LayoutObj* obj;
            lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
            obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
            if ((obj->_5C >> 16) <= 0xA) {
                obj->_5C = 0xA << 16;
            }
        }
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].obj->_68 = 4;
        item->state = 6;
        break;
    case 6: {
        LayoutObj* obj = lbl_80371C30[menu->firstIndex + item->offset].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_5C = 0;
        }
        break;
    }
    case 1:
    case 4:
        break;
    }
}

// .text:0x00057F50 size:0x148
void fn_2_57F50(MenuTableContext* menu, MenuItemState* item) {
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

// .text:0x00058098 size:0x148
void fn_2_58098(MenuTableContext* menu, MenuItemState* item) {
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

// .text:0x000581E0 size:0x148
void fn_2_581E0(MenuTableContext* menu, MenuItemState* item) {
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
// Menu work area stat block: current input/output and saved copies.
#define MENU_STAT_IN ((StatInput*)(lbl_2_bss_1A824C[0] + 0x197404))
#define MENU_STAT_IN_COPY ((StatInput*)(lbl_2_bss_1A824C[0] + 0x19741A))
#define MENU_STAT_OUT ((StatOutput*)(lbl_2_bss_1A824C[0] + 0x197430))
#define MENU_STAT_OUT_COPY ((StatOutput*)(lbl_2_bss_1A824C[0] + 0x197440))

void fn_2_5853C(void) {
    s32 idx = *(s16*)(lbl_2_bss_1A824C[0] + 0x197706);
#define SRC (((StatInput*)(lbl_2_bss_1A8240[0] + 0x140))[idx])
    MENU_STAT_IN->vals[0] = SRC.vals[0];
    MENU_STAT_IN->order[0] = SRC.order[0];
    MENU_STAT_IN->vals[1] = SRC.vals[1];
    MENU_STAT_IN->order[1] = SRC.order[1];
    MENU_STAT_IN->vals[2] = SRC.vals[2];
    MENU_STAT_IN->order[2] = SRC.order[2];
    MENU_STAT_IN->vals[3] = SRC.vals[3];
    MENU_STAT_IN->order[3] = SRC.order[3];
    MENU_STAT_IN->vals[4] = SRC.vals[4];
    MENU_STAT_IN->order[4] = SRC.order[4];
    MENU_STAT_IN->vals[5] = SRC.vals[5];
    MENU_STAT_IN->order[5] = SRC.order[5];
    MENU_STAT_IN->_13 = SRC._13;
    MENU_STAT_IN->_14[0] = SRC._14[0];
    MENU_STAT_IN->_12 = SRC._12;
#undef SRC
    fn_8006C2B4(MENU_STAT_OUT, MENU_STAT_IN);
    memcpy(MENU_STAT_IN_COPY, MENU_STAT_IN, sizeof(StatInput));
    memcpy(MENU_STAT_OUT_COPY, MENU_STAT_OUT, sizeof(StatOutput));
    MENU_STAT_IN->vals[0] = MENU_STAT_IN_COPY->vals[0];
    MENU_STAT_IN->vals[1] = MENU_STAT_IN_COPY->vals[1];
    MENU_STAT_IN->vals[2] = MENU_STAT_IN_COPY->vals[3];
    MENU_STAT_IN->vals[3] = MENU_STAT_IN_COPY->vals[4];
    MENU_STAT_IN->vals[4] = MENU_STAT_IN_COPY->vals[2];
    MENU_STAT_IN->vals[5] = MENU_STAT_IN_COPY->vals[5];
    MENU_STAT_OUT->vals[0] = MENU_STAT_OUT_COPY->vals[0];
    MENU_STAT_OUT->vals[1] = MENU_STAT_OUT_COPY->vals[1];
    MENU_STAT_OUT->vals[2] = MENU_STAT_OUT_COPY->vals[3];
    MENU_STAT_OUT->vals[3] = MENU_STAT_OUT_COPY->vals[4];
    MENU_STAT_OUT->vals[4] = MENU_STAT_OUT_COPY->vals[2];
    MENU_STAT_OUT->vals[5] = MENU_STAT_OUT_COPY->vals[5];
}

// .text:0x000587F8 size:0xFA4
void fn_2_587F8(void) {
    return;
}
