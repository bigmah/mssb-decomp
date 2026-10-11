#include "menus/rep_0788.h"
#include "Dolphin/gx.h"
#include "main/file_80024184.h"
#include "game/UnknownHomes_Game.h"
#include "menus/auto_00_0005E84C_text.h"
#include "menus/rep_08E8.h"
#include "menus/auto_00_0001B1BC_text.h"
#include "menus/auto_00_00094854_text.h"
#include "menus/rep_10C0.h"
#include "menus/auto_00_00092394_text.h"
#include "menus/rep_1028.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/rep_0B08.h"

#include "static/UnknownHomes_Static.h"
#include "static/UnknownHomes_Static.h"
#include "static/UnknownHomes_Static.h"
#include "static/UnknownHomes_Static.h"
extern void fn_2_242FC(void);
extern void fn_2_54234(void* data, s32 id);
extern u8 lbl_2_data_104EC[];

extern void fn_2_2416C(void);
extern u8 lbl_2_data_1073C[];
extern void fn_2_54354(void* data, s32 id);

extern void fn_2_24238(void);
extern u8 lbl_2_data_105FC[];
extern void fn_2_54354(void* data, s32 id);

extern void fn_2_243BC(void);
extern u8 lbl_2_data_F0EC[];
extern void fn_2_54354(void* data, s32 id);

extern void fn_2_24488(void);
extern u8 lbl_2_data_9FC8[];
extern void fn_2_54354(void* data, s32 id);

typedef struct { u8* object; s32 _04; } MenuTableEntry;
extern MenuTableEntry lbl_80371C30[];
extern u8* lbl_2_bss_1A824C[];
extern s16 lbl_2_data_3D30[][4];
extern u8* lbl_803CC1B8[];
extern u8* lbl_2_bss_1A8248;
extern u8 lbl_8036E548[];
extern void fn_2_68E68(void);
extern void fn_2_8FD14(void);
extern void fn_2_8AEE0(void);
extern void fn_2_47FF8(void);
extern void fn_2_47CFC(void);

// fn_2_2025C, size:0xCC
void fn_2_2025C(void) {
    u8* menu = lbl_2_bss_1A8248;
    if (menu[0x44F2] == 2) {
        lbl_8036E548[0x307A] = 0;
    } else if (lbl_2_bss_1A824C[0][0x1978F3] != 0) {
        lbl_8036E548[0x307A] = 4;
    }
    if (lbl_8036E548[0x307A] == 4) {
        if (menu[0x44F2] != 3) {
            if (menu[0x44F2] != 4) {
                fn_2_68E68();
            }
            fn_2_8FD14();
            fn_2_8AEE0();
            fn_2_47FF8();
            if (lbl_2_bss_1A8248[0x44F2] != 4) {
                fn_2_47CFC();
            }
        }
    }
    GXSetZCompLoc(GX_FALSE);
}
extern u8* lbl_2_bss_1A8230[];
extern u8 lbl_2_data_1048C[];
extern void fn_2_4E878(void*, void*);
extern void* fn_2_4E858(void*);
extern void fn_2_53F04(void*);
extern void fn_2_5400C(void);
extern void fn_2_53CEC(void*);

// fn_2_2A21C, size:0x11C
void fn_2_2A21C(MenuTableContext* menu, MenuItemState* item) {
    fn_2_2E17C(menu, item);
}

// fn_2_24728, size:0xD8
s32 fn_2_24728(s32 character) {
    u8* menu = lbl_2_bss_1A8248;
    s32 index;
    u8* record;

    for (index = 0; index < 51; index++) {
        record = menu + index * 10;
        if (record[0x40F1] == 0 && record[0x40F2] == 1 &&
            (s32)record[0x40F5] == character && menu[character + 0x4431] == 1) {
            return 1;
        }
    }
    return 0;
}

// fn_2_26774, size:0xF0
void fn_2_26774(MenuTableContext* menu, MenuItemState* item) {
    fn_2_32C64(menu, item);
}

// fn_2_26684, size:0xF0
void fn_2_26684(MenuTableContext* menu, MenuItemState* item) {
    fn_2_32C64(menu, item);
}
extern s16 fn_2_53BC8(void*);

// fn_2_32C64, size:0xF0
void fn_2_32C64(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_242FC, size:0xC0
void fn_2_242FC(void) {
    MenuQueueState* queue = (MenuQueueState*)lbl_803CC1B8[0];
    switch ((s32)queue->stateB) {
    case 1:
        break;
    case 0:
        fn_2_4E878(queue, lbl_2_data_1048C);
        queue->stateB = 1;
        queue->timerB = 0;
        break;
    }
    fn_2_53F04(queue);
    fn_2_5400C();
    if (lbl_2_bss_1A8230[0][0x32A86] != 0) {
        fn_2_53CEC(queue);
        fn_800B0A14_removeQueue(fn_2_4E858(queue));
        queue->stateB = 0;
        lbl_2_bss_1A8230[0][0x32A86] = 0;
    }
}

#define MENU_INPUT_CONTEXT ((MenuInputContext*)lbl_2_bss_1A824C[0])

// fn_2_1FFC4, size:0xB0
void fn_2_1FFC4(s32 count) {
    u16* repeat = (u16*)((u8*)&lbl_803C77B8 + 4);
    if (repeat[MENU_INPUT_CONTEXT->port * 16] & 8) {
        MENU_INPUT_CONTEXT->selection--;
        if (MENU_INPUT_CONTEXT->selection < 0) {
            MENU_INPUT_CONTEXT->selection = count - 1;
        }
    }
    if (repeat[MENU_INPUT_CONTEXT->port * 16] & 4) {
        MENU_INPUT_CONTEXT->selection++;
        if (MENU_INPUT_CONTEXT->selection >= count) {
            MENU_INPUT_CONTEXT->selection = 0;
        }
    }
}

// .text:0x24724 size:0x4
void fn_2_24724(void) {
}

// .text:0x20258 size:0x4
void fn_2_20258(void) {
}

// .text:0x1FF10 size:0x4
void fn_2_1FF10(void) {
}

// .text:0x1FF0C size:0x4
void fn_2_1FF0C(void) {
}

void fn_2_24EB0(s16 value) {
    *(s16*)(lbl_803CC1B8[0] + 0x10) = value;
}

s16 fn_2_24E9C(void) {
    return *(s16*)(lbl_803CC1B8[0] + 0x10);
}

s16 fn_2_201E4(s16 row, s16 column) {
    if (column < 0) return -1;
    return lbl_2_data_3D30[row][column];
}

void fn_2_20218(void) {
    lbl_2_bss_1A824C[0][0x19782B] = 0;
    lbl_2_bss_1A824C[0][0x19782C] = 0;
    lbl_2_bss_1A824C[0][0x19782A] = 0;
    lbl_2_bss_1A824C[0][0x197832] = 0;
}

void fn_2_272BC(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

void fn_2_25D6C(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

void fn_2_25A1C(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

void fn_2_25850(u8* menu, u8* item) {
    u8* object = lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)(item + 0xE)].object;
    *(u32*)(object + 0x54) &= ~2;
}

// fn_2_246E0, size:0x44
void fn_2_246E0(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_24488, 2);
    *(s16*)(object + 0x1C) = 0;
    fn_2_54354(lbl_2_data_9FC8, 0x293);
}

// fn_2_2469C, size:0x44
void fn_2_2469C(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_243BC, 2);
    *(s16*)(object + 0x1C) = 0;
    fn_2_54354(lbl_2_data_F0EC, 0x13A);
}

// fn_2_2460C, size:0x44
void fn_2_2460C(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_24238, 2);
    *(s16*)(object + 0x1C) = 0;
    fn_2_54354(lbl_2_data_105FC, 0x2);
}

// fn_2_245C8, size:0x44
void fn_2_245C8(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_2416C, 2);
    *(s16*)(object + 0x1C) = 0;
    fn_2_54354(lbl_2_data_1073C, 0x8);
}

// fn_2_24650, size:0x4C
void fn_2_24650(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_2_242FC, 2);
    *(s16*)(object + 0x1C) = 0;
    *(s16*)(object + 0x1E) = 0;
    fn_2_54234(lbl_2_data_104EC, 2);
}

// fn_2_1FF14, size:0xB0
void fn_2_1FF14(s32 count) {
    u16* repeat = (u16*)((u8*)&lbl_803C77B8 + 4);
    if (repeat[MENU_INPUT_CONTEXT->port * 16] & 8) {
        MENU_INPUT_CONTEXT->secondarySelection--;
        if (MENU_INPUT_CONTEXT->secondarySelection < 0) {
            MENU_INPUT_CONTEXT->secondarySelection = count - 1;
        }
    }
    if (repeat[MENU_INPUT_CONTEXT->port * 16] & 4) {
        MENU_INPUT_CONTEXT->secondarySelection++;
        if (MENU_INPUT_CONTEXT->secondarySelection >= count) {
            MENU_INPUT_CONTEXT->secondarySelection = 0;
        }
    }
}

extern u8* lbl_2_bss_1A8234[];
extern u8 lbl_2_data_1059C[];
extern void fn_2_53F88(void*);
extern void fn_2_54120(void);
extern void fn_2_53DF8(void*);
extern void fn_8000FE54(void);

// fn_2_20074, size:0x70
s32 fn_2_20074(void) {
    u16 v = *(u16*)((u8*)&lbl_803C77B8 + ((s8)lbl_2_bss_1A824C[0][0x197863] << 5));
    s32 r;
    if (v & 0x8) {
        r = 0;
    } else if (v & 0x4) {
        r = 1;
    } else if (v & 0x1) {
        r = 2;
    } else if (v & 0x2) {
        r = 3;
    } else {
        r = -1;
    }
    return r;
}

// fn_2_24238, size:0xC4
void fn_2_24238(void) {
    MenuQueueState* queue = (MenuQueueState*)lbl_803CC1B8[0];
    switch ((s32)queue->stateA) {
    case 1:
        break;
    case 0:
        fn_2_4E878(queue, lbl_2_data_1059C);
        queue->stateA = 1;
        queue->timerA = 0;
        break;
    }
    fn_2_53F88(queue);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0][0x162992] != 0) {
        fn_8000FE54();
        fn_2_53DF8(queue);
        fn_800B0A14_removeQueue(fn_2_4E858(queue));
        queue->stateA = 0;
        lbl_2_bss_1A8234[0][0x162992] = 0;
    }
}

extern u8 lbl_2_data_C96C[];
extern void fn_8000F8F4(void*);

// fn_2_243BC, size:0xCC
void fn_2_243BC(void) {
    MenuQueueState* queue = (MenuQueueState*)lbl_803CC1B8[0];
    switch ((s32)queue->stateA) {
    case 1:
        break;
    case 0:
        fn_2_4E878(queue, lbl_2_data_C96C);
        queue->stateA = 1;
        queue->timerA = 0;
        break;
    }
    fn_2_53F88(queue);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0][0x162992] != 0) {
        fn_8000FE54();
        fn_2_53DF8(queue);
        fn_8000F8F4(queue);
        fn_800B0A14_removeQueue(fn_2_4E858(queue));
        queue->stateA = 0;
        lbl_2_bss_1A8234[0][0x162992] = 0;
    }
}

extern u8 lbl_2_data_1061C[];

// fn_2_2416C, size:0xCC
void fn_2_2416C(void) {
    MenuQueueState* queue = (MenuQueueState*)lbl_803CC1B8[0];
    switch ((s32)queue->stateA) {
    case 1:
        break;
    case 0:
        fn_2_4E878(queue, lbl_2_data_1061C);
        queue->stateA = 1;
        queue->timerA = 0;
        break;
    }
    fn_2_53F88(queue);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0][0x162992] != 0) {
        fn_8000FE54();
        fn_2_53DF8(queue);
        fn_8000F8F4(queue);
        fn_800B0A14_removeQueue(fn_2_4E858(queue));
        queue->stateA = 0;
        lbl_2_bss_1A8234[0][0x162992] = 0;
    }
}

// fn_2_327D4, size:0xF0
void fn_2_327D4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_33614, size:0x10C
void fn_2_33614(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_25D98, size:0x118
void fn_2_25D98(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            (u32)lbl_2_bss_1A8248[0x441C] << 16;
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_2E17C, size:0x11C
void fn_2_2E17C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2D508, size:0x138
void fn_2_2D508(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

extern u8 lbl_2_data_4C68[];

// fn_2_24488, size:0x140
void fn_2_24488(void) {
    MenuQueueState* queue = (MenuQueueState*)lbl_803CC1B8[0];
    switch ((s32)queue->stateA) {
    case 0:
        fn_2_4E878(queue, lbl_2_data_4C68);
        queue->stateA = 1;
        queue->timerA = 0;
        break;
    case 1:
        if ((s32)lbl_2_bss_1A824C[0][0x1978FB] == 1) {
            lbl_2_bss_1A8234[0][0x16268A] = 1;
            lbl_2_bss_1A8234[0][0x162874] = 0;
        } else {
            lbl_2_bss_1A8234[0][0x162874] = 1;
            lbl_2_bss_1A8234[0][0x16268A] = 0;
        }
        break;
    }
    fn_2_53F88(queue);
    fn_2_54120();
    if (lbl_2_bss_1A8234[0][0x162992] != 0) {
        fn_8000FE54();
        fn_2_53DF8(queue);
        fn_8000F8F4(queue);
        fn_800B0A14_removeQueue(fn_2_4E858(queue));
        queue->stateA = 0;
        lbl_2_bss_1A8234[0][0x162992] = 0;
    }
}

// fn_2_322E4, size:0x150
void fn_2_322E4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 3;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_31A90, size:0x150
void fn_2_31A90(MenuTableContext* menu, MenuItemState* item) {
    fn_2_322E4(menu, item);
}

// fn_2_27D8C, size:0x150
void fn_2_27D8C(MenuTableContext* menu, MenuItemState* item) {
    fn_2_322E4(menu, item);
}

// fn_2_2DE78, size:0x150
void fn_2_2DE78(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 40;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_29F18, size:0x150
void fn_2_29F18(MenuTableContext* menu, MenuItemState* item) {
    fn_2_2DE78(menu, item);
}

// fn_2_2C378, size:0x16C
void fn_2_2C378(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2835C, size:0x154
void fn_2_2835C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_26170, size:0x160
void fn_2_26170(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        MenuInputContext* frames = MENU_INPUT_CONTEXT;
        s16 frame = frames->frameSetA[item->index];
        if (frame != -1) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = (s32)frame << 16;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_26010, size:0x160
void fn_2_26010(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        MenuInputContext* frames = MENU_INPUT_CONTEXT;
        s16 frame = frames->frameSetC[item->index];
        if (frame != -1) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = (s32)frame << 16;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_25EB0, size:0x160
void fn_2_25EB0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        MenuInputContext* frames = MENU_INPUT_CONTEXT;
        s16 frame = frames->frameSetB[item->index];
        if (frame != -1) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = (s32)frame << 16;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_28224, size:0x138
void fn_2_28224(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_26F80, size:0x138
void fn_2_26F80(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            (u32)lbl_2_bss_1A8248[0x441C] << 16;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 37;
        /* fallthrough */
    }
    case 5:
    case 37:
    case 1:
        return;
    }
}

// fn_2_253B0, size:0x174
void fn_2_253B0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

extern const f32 lbl_2_rodata_7E4[];

// fn_2_2E44C, size:0x17C
void fn_2_2E44C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        *(f32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x48) = lbl_2_rodata_7E4[0];
        *(f32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x4C) = 0.0f;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_31F50, size:0x188
void fn_2_31F50(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 3;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_316F8, size:0x188
void fn_2_316F8(MenuTableContext* menu, MenuItemState* item) {
    fn_2_31F50(menu, item);
}

// fn_2_279F4, size:0x188
void fn_2_279F4(MenuTableContext* menu, MenuItemState* item) {
    fn_2_31F50(menu, item);
}

// fn_2_28D24, size:0x17C
void fn_2_28D24(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 37: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        return;
    }
    case 5:
        item->timer = 40;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 1:
        return;
    }
}

// fn_2_2BDA4, size:0x17C
void fn_2_2BDA4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            (s32)*(s16*)(lbl_2_bss_1A824C[0] + 0x197714) << 16;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2AEDC, size:0x188
void fn_2_2AEDC(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            (s32)*(s16*)(lbl_2_bss_1A824C[0] + 0x197706) << 16;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 7;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_24EC4, size:0x18C
void fn_2_24EC4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19774E) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_28090, size:0x194
void fn_2_28090(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 8:
    case 2: {
        u8* object;
        if (lbl_2_bss_1A824C[0][0x1978F6] == 0) {
            fn_800363D8(menu, item->offset, 1, 0x41, 7);
        } else {
            fn_800363D8(menu, item->offset, 1, 0x41, 8);
        }
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x50000;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2CA30, size:0x19C
void fn_2_2CA30(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2:
        if ((s32)lbl_2_bss_1A8248[0x43C2 + item->index] == 1) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        return;
    case 5:
        item->timer = 30;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2577C, size:0xD4
void fn_2_2577C(u8* a, u8* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        *(s16*)(b + 4) = r;
    }
    switch (*(s16*)(b + 4)) {
    case 0: {
        u8* object = lbl_80371C30[*(u16*)(a + 0x14) + *(s16*)(b + 0xE)].object;
        *(u32*)(object + 0x54) &= ~2;
        *(s16*)(b + 4) = 0x26;
        break;
    }
    case 2:
        *(s16*)(b + 4) = 0x25;
        break;
    case 1:
    case 5:
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// fn_2_2587C, size:0x1A0
void fn_2_2587C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        item->state = 37;
        return;
    }
    case 5:
        item->state = 6;
        return;
    case 6:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 7;
        return;
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

extern s16 fn_8000F988(void*, s16, u16, s32, s32, s32);
extern void fn_8000FE08(s16, s32, s16);
extern u8 lbl_80366B18[];

// fn_2_25050, size:0x1B0
void fn_2_25050(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x399, 0);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        fn_8000FE08(item->unk14, 4, *(s16*)(lbl_2_bss_1A824C[0] + 0x19774C));
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 3;
        return;
    }
    case 3:
        item->state = 37;
        return;
    case 37:
        item->state = 37;
        return;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 4:
    case 1:
        return;
    }
}

// fn_2_25200, size:0x1B0
void fn_2_25200(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x399, 0);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        fn_8000FE08(item->unk14, 4, *(s16*)(lbl_2_bss_1A824C[0] + 0x19774C));
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 3;
        return;
    }
    case 3:
        item->state = 37;
        return;
    case 37:
        item->state = 37;
        return;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 4:
    case 1:
        return;
    }
}

// fn_2_33720, size:0x1B4
void fn_2_33720(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_32D54, size:0x1B4
void fn_2_32D54(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_328C4, size:0x1B4
void fn_2_328C4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_32434, size:0x1B4
void fn_2_32434(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_31BE0, size:0x1B4
void fn_2_31BE0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_31384, size:0x1B4
void fn_2_31384(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_3109C, size:0x1B4
void fn_2_3109C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2E298, size:0x1B4
void fn_2_2E298(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2DFC8, size:0x1B4
void fn_2_2DFC8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2CDA4, size:0x1B4
void fn_2_2CDA4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2C4E4, size:0x1B4
void fn_2_2C4E4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2A068, size:0x1B4
void fn_2_2A068(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_28794, size:0x1B4
void fn_2_28794(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_27EDC, size:0x1B4
void fn_2_27EDC(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

typedef struct { u8 pad0[0x197726]; s16 k; u8 pad1[0x19789F - 0x197728]; u8 arr[1]; } MenuSel;

// fn_2_30C4C, size:0x134
void fn_2_30C4C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 17:
        item->state = 37;
        return;
    case 5:
        item->timer = 14;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2FBCC, size:0x134
void fn_2_2FBCC(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 17:
        item->state = 37;
        return;
    case 5:
        item->timer = 25;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_31250, size:0x134
void fn_2_31250(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 17:
        item->state = 37;
        return;
    case 5:
        item->timer = 14;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2FA7C, size:0x150
void fn_2_2FA7C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 17:
        item->state = 37;
        return;
    case 5:
        item->timer = 25;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2FD00, size:0x150
void fn_2_2FD00(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 17:
        item->state = 37;
        return;
    case 5:
        item->timer = 14;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_30D80, size:0x178
void fn_2_30D80(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2:
    case 17: {
        u8* object;
        MenuSel* ctx = (MenuSel*)lbl_2_bss_1A824C[0];
        s32 value = 0x14;
        s16 k = ctx->k;
        if ((s8)ctx->arr[item->index + k] != 2) {
            value = k;
        }
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = value << 16;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 14;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_20CB0, size:0x58
s32 fn_2_20CB0(u32 index) {
    s32 result = 0;
    switch (index) {
    case 0:
        result = 0;
        break;
    case 4:
        result = 1;
        break;
    case 10:
        result = 2;
        break;
    case 2:
        result = 3;
        break;
    case 6:
        result = 4;
        break;
    case 9:
        result = 5;
        break;
    }
    return result;
}

// fn_2_2B064, size:0x1EC
void fn_2_2B064(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        object[0x68] = 4;
        item->timer = 9;
        item->state = 6;
        return;
    }
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0 || item->timer-- <= 0) {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        return;
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2B250, size:0x1EC
void fn_2_2B250(MenuTableContext* menu, MenuItemState* item) {
    fn_2_2B064(menu, item);
}

// fn_2_2CF58, size:0x17C
void fn_2_2CF58(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 8:
        item->timer = 1;
        item->state++;
        return;
    case 9:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            item->state = 37;
        }
        return;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        return;
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_272E8, size:0x1B4
void fn_2_272E8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        object[0x68] = 4;
        item->state = 6;
        return;
    }
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        return;
    }
    case 37:
    case 1:
        return;
    }
}

extern u8 lbl_800E869C[];
extern void determineIfMissionDescriptionIsShown(s32 index);

// fn_2_2AD30, size:0x1AC
void fn_2_2AD30(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        determineIfMissionDescriptionIsShown(lbl_800E869C[*(s16*)(lbl_2_bss_1A824C[0] + 0x197706)]);
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            *(s16*)(lbl_2_bss_1A824C[0] + 0x197706) << 16;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 7;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern void fn_8000FD9C(s16, s32, s32);

// fn_2_2749C, size:0x1C4
void fn_2_2749C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x1C7, 0);
        fn_8000FD9C(item->unk14, 1, 0);
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A2) = item->unk14;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 4, *(s32*)(lbl_2_bss_1A824C[0] + 0x196FBC));
        item->state = 37;
        break;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 37:
    case 1:
        break;
    }
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

// fn_2_27660, size:0x1C4
void fn_2_27660(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x1C7, 0);
        fn_8000FD9C(item->unk14, 1, 0);
        *(s16*)(lbl_2_bss_1A824C[0] + 0x1972A0) = item->unk14;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 4, *(s32*)(lbl_2_bss_1A824C[0] + 0x196FB8));
        item->state = 37;
        break;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 37:
    case 1:
        break;
    }
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

// fn_2_32A78, size:0x1EC
void fn_2_32A78(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x30A, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        fn_8000FE08(item->unk14, 4, 0x30A);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        item->state = 3;
        break;
    }
    case 3:
        item->state = 37;
        break;
    case 37:
        item->state = 37;
        break;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

// fn_2_325E8, size:0x1EC
void fn_2_325E8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x30B, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        fn_8000FE08(item->unk14, 4, 0x30B);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        item->state = 3;
        break;
    }
    case 3:
        item->state = 37;
        break;
    case 37:
        item->state = 37;
        break;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

// fn_2_27B7C, size:0x1EC
void fn_2_27B7C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x35C, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        u8* p = lbl_2_bss_1A824C[0] + 0x190000;
        p += (s8)p[0x78F0];
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 4, (s8)p[0x78DB] + 0x35C);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        item->state = 3;
        break;
    }
    case 3:
        item->state = 37;
        break;
    case 37:
        item->state = 37;
        break;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}


// fn_2_31880, size:0x1EC
void fn_2_31880(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x316, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        u8* p = lbl_2_bss_1A824C[0] + 0x190000;
        p += (s8)p[0x7867];
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 4, (s8)p[0x7868] + 0x316);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        item->state = 3;
        break;
    }
    case 3:
        item->state = 37;
        break;
    case 37:
        item->state = 37;
        break;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}


extern void fn_800363D8(void*, s32, s32, s32, s32);
extern s16 lbl_2_data_38C0[];

// fn_2_31D94, size:0x1BC
void fn_2_31D94(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        fn_800363D8(menu, item->offset, 1, 0x83, lbl_2_data_38C0[lbl_2_bss_1A8248[0x441C]]);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 3;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

// fn_2_31538, size:0x1BC
void fn_2_31538(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        u8* p = lbl_2_bss_1A824C[0] + 0x190000;
        p += (s8)p[0x7867];
        fn_800363D8(menu, item->offset, 1, 0x83, ((s8*)p)[0x7868]);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 3;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern s16 lbl_2_data_3714[];

// fn_2_27824, size:0x1BC
void fn_2_27824(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        u8* p = lbl_2_bss_1A824C[0] + 0x190000;
        p += (s8)p[0x78F0];
        fn_800363D8(menu, item->offset, 1, 0x83, lbl_2_data_3714[((s8*)p)[0x78DB]]);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 3;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

// fn_2_320D8, size:0x1EC
void fn_2_320D8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, lbl_2_bss_1A8248[0x441C] + 0x30C, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 4, lbl_2_bss_1A8248[0x441C] + 0x30C);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        item->state = 3;
        break;
    }
    case 3:
        item->state = 37;
        break;
    case 37:
        item->state = 37;
        break;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}


// fn_2_2F8A4, size:0x1B4
void fn_2_2F8A4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        fn_800363D8(menu, item->offset, 1, 6, lbl_2_bss_1A8248[0x4415]);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        object[0x68] = 4;
        item->state = 6;
        return;
    }
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        return;
    }
    case 37:
    case 1:
        return;
    }
}

extern u8 lbl_800E869C[];
extern void determineIfMissionDescriptionIsShown(s32 index);


// fn_2_2CBCC, size:0x1D8
void fn_2_2CBCC(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        if ((s32)lbl_2_bss_1A8248[item->index + 0x43C2] == 1) {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x68;
        } else {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x67;
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 30;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern s32 fn_8006C79C(s32);

// fn_2_2DCA8, size:0x1D8
void fn_2_2DCA8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
        if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        } else {
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x10000;
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 40;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern u8 lbl_8034E9A0[];
extern void* memcpy(void* dest, const void* src, u32 n);

// fn_2_2C1A8, size:0x1D8
void fn_2_2C1A8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        s32 v = lbl_800E869C[*(s16*)(lbl_2_bss_1A824C[0] + 0x197706)];
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            (u32)lbl_8034E9A0[v / 9 * 0x5A0 + v % 9 * 0xA0 + 0x31] << 16;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern s32 fn_8006C79C(s32);


// fn_2_2C698, size:0x1D8
void fn_2_2C698(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        if ((s32)lbl_2_bss_1A8248[item->index + 0x43C2] == 1) {
            u8* object;
            fn_800363D8(menu, item->offset, 1, 0x6C, item->index);
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 30;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern s32 fn_8006C79C(s32);


// fn_2_2C860, size:0x1D8
void fn_2_2C860(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 38;
        return;
    }
    case 2: {
        if ((s32)lbl_2_bss_1A8248[item->index + 0x43C2] == 1) {
            u8* object;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = item->index << 16;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 30;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        return;
    case 37:
    case 1:
        return;
    }
}

extern s32 fn_8006C79C(s32);


// fn_2_2E5C8, size:0x208
void fn_2_2E5C8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 3;
        return;
    }
    case 3:
        if (*(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) >> 16 >= 200) {
            if (lbl_2_bss_1A8248[0x4446] != 0) {
                lbl_2_bss_1A8234[0][0x16267A] = 1;
            }
            item->state = 4;
        }
        /* fallthrough */
    case 4: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if (*(u32*)(object + 0x5C) >> 16 >= 260) {
            object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 37;
        }
        return;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_2F710, size:0x194
void fn_2_2F710(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        break;
    }
    case 17:
        item->state = 37;
        break;
    case 5: {
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        break;
    }
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_30EF8, size:0x1A4
void fn_2_30EF8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
    case 17: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        break;
    }
    case 5: {
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        break;
    }
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_306D8, size:0x1BC
void fn_2_306D8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object;
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        s32 sum = item->index;
        sum += *(s16*)(ctx + 0x772A);
        fn_800363D8(menu, item->offset, 1, 0x65, (s8)ctx[sum + 0x789F] == 2 ? 0x14 : sum);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 17: {
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        s32 sum = item->index;
        sum += *(s16*)(ctx + 0x772A);
        fn_800363D8(menu, item->offset, 1, 0x65, (s8)ctx[sum + 0x789F] == 2 ? 0x14 : sum);
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 14;
        item->state = 6;
        return;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        /* fallthrough */
    }
    case 37:
    case 1:
        return;
    }
}

// fn_2_270B8, size:0x204
void fn_2_270B8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 3;
        break;
    }
    case 3: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xDC) {
            object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 5: {
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x14A0000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 6;
        break;
    }
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x140) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

extern StarMission lbl_80109AE8[][10];

// fn_2_2B43C, size:0x204
void fn_2_2B43C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
    case 8: {
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        s32 index = item->index;
        if (lbl_80109AE8[*(s16*)(ctx + 0x7706)][index].type != -1) {
            if (*(s16*)(ctx + 0x7710) == index) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x5C) = 0;
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}

// fn_2_2FE50, size:0x258
void fn_2_2FE50(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197728) == item->index) {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        break;
    }
    case 17: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197728) == item->index) {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 14;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}

// fn_2_26864, size:0x290
void fn_2_26864(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        item->timer = 250;
        item->state = 3;
        break;
    }
    case 3: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 37;
        }
        break;
    }
    case 37: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x78) {
            *(u32*)(object + 0x5C) = 0x320000;
        }
        break;
    }
    case 17:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x780000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 18;
        break;
    case 18: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x82) {
            object[0x68] = 0;
            item->state = 19;
        }
        break;
    }
    case 19: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    }
}

// fn_2_300BC, size:0x2D4
void fn_2_300BC(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197728) == item->index) {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        break;
    }
    case 17: {
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197728) == item->index) {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) >= 10) {
                *(u32*)(object + 0x5C) = 0;
            }
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        }
        item->state = 18;
        break;
    }
    case 18: {
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197728) != item->index) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) == 0) {
                *(u32*)(object + 0x5C) = 0;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        }
        break;
    }
    case 5:
        item->timer = 14;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}

// fn_2_284B0, size:0x2D4
void fn_2_284B0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 37;
        break;
    }
    case 17: {
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706) == item->unk10) {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 37;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) >= 10) {
                *(u32*)(object + 0x5C) = 0xA0000;
            }
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
            item->state = 18;
        }
        break;
    }
    case 18: {
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706) != item->unk10) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) == 0) {
                *(u32*)(object + 0x5C) = 0;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                item->state = 37;
            }
        }
        break;
    }
    case 5:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0xA0000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_26C70, size:0x2F8
void fn_2_26C70(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 3;
        break;
    }
    case 3: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0xDC) {
            *(u32*)(lbl_2_bss_1A824C[0] + 0x1976A8) = fn_80062890(13);
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x12C) {
            *(u32*)(object + 0x5C) = 0x12C0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 17:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x12C0000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 18;
        break;
    case 18: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x15E) {
            *(u32*)(object + 0x5C) = 0x15E0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 5:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x15E0000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x140) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_28948, size:0x3C8
void fn_2_28948(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* ctx;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        ctx = lbl_2_bss_1A824C[0] + 0x190000;
        if (ctx[0x78F6] == 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        } else if (*(s16*)(ctx + 0x7706) == item->unk10) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    }
    case 8: {
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706) == item->unk10) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    }
    case 37: {
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        if (ctx[0x78F6] == 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        } else if (*(s16*)(ctx + 0x7706) == item->unk10) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        break;
    }
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x54) &= ~2U;
        }
        break;
    }
    }
}

// fn_2_2E7D0, size:0x40C
void fn_2_2E7D0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
        if ((s8)lbl_2_bss_1A8248[0x444B] == -1) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 3;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 37;
        }
        break;
    case 3: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xE) {
            *(u32*)(object + 0x5C) = 0xE0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 8:
        if ((s8)lbl_2_bss_1A8248[0x444C] == -1) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0xF0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 9;
        } else {
            item->state = 37;
        }
        break;
    case 9: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x19) {
            *(u32*)(object + 0x5C) = 0x190000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 20:
        item->timer = 30;
        item->state = 21;
        break;
    case 21: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 22;
        }
        break;
    }
    case 22: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xE) {
            *(u32*)(object + 0x5C) = 0xE0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_2EBE4, size:0x3E0
void fn_2_2EBE4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        s32 value = (s8)lbl_2_bss_1A8248[0x444B];
        if (value == -1) {
            item->state = 37;
        } else {
            u8* object;
            fn_800363D8(menu, item->offset, 4, 0x64, value);
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 3;
        }
        break;
    }
    case 3: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xA) {
            *(u32*)(object + 0x5C) = 0xA0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 8: {
        u8* object;
        fn_800363D8(menu, item->offset, 4, 0x64, *(s8*)(lbl_2_bss_1A8248 + 0x444B));
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0xB0000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 9;
        break;
    }
    case 9: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x15) {
            *(u32*)(object + 0x5C) = 0xA0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 20:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0x160000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 21;
        break;
    case 21: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x2D) {
            *(u32*)(object + 0x5C) = 0;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 22;
        }
        break;
    }
    case 22: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 37;
        break;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

extern s16 lbl_2_data_373C[];

// fn_2_30894, size:0x3A4
void fn_2_30894(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        s16 index = item->index;
        s16 sel = *(s16*)(lbl_2_bss_1A824C[0] + 0x19772A);
        if ((s32)lbl_2_bss_1A8248[index + sel + 0x43C2] == 1) {
            s32 k = index + sel;
            if (lbl_2_data_373C[k] == 0) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else if (*(s8*)(lbl_2_bss_1A8248 + 0x444B) == k) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        break;
    }
    case 8:
    case 17: {
        s16 index = item->index;
        s16 sel = *(s16*)(lbl_2_bss_1A824C[0] + 0x19772A);
        if ((s32)lbl_2_bss_1A8248[index + sel + 0x43C2] == 1) {
            s32 k = index + sel;
            if (lbl_2_data_373C[k] == 0) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else if (*(s8*)(lbl_2_bss_1A8248 + 0x444B) == k) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 14;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}

// fn_2_2D8C4, size:0x1E4
void fn_2_2D8C4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8 id = lbl_800E869C[item->unk10];
        s32 flag = lbl_2_bss_1A8248[id + 0x43D6];
        if (fn_8006C79C(id) != 0) {
            if (flag == 1) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
    case 1:
        break;
    }
}

// fn_2_2DAA8, size:0x200
void fn_2_2DAA8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8 id = lbl_800E869C[item->unk10];
        s32 flag = lbl_2_bss_1A8248[id + 0x43D6];
        if (fn_8006C79C(id) != 0) {
            if (flag == 1) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
    case 1:
        break;
    }
}

// fn_2_32F08, size:0x2BC
void fn_2_32F08(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0xFF;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, 0x2E0, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        switch (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972B4)) {
        case 0:
            fn_8000FE08(item->unk14, 4, 0x2E0);
            break;
        case 1:
            fn_8000FE08(item->unk14, 4, 0x2E1);
            break;
        case 2:
            fn_8000FE08(item->unk14, 4, 0x2E2);
            break;
        case 3:
            fn_8000FE08(item->unk14, 4, 0x357);
            break;
        case 4:
            fn_8000FE08(item->unk14, 4, 0x2DE);
            break;
        case 5:
            fn_8000FE08(item->unk14, 4, 0x312);
            break;
        case 6:
            fn_8000FE08(item->unk14, 4, 0x313);
            break;
        case 7:
            fn_8000FE08(item->unk14, 4, 0x314);
            break;
        case 8:
            fn_8000FE08(item->unk14, 4, 0x315);
            break;
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
        item->state = 3;
        break;
    }
    case 3:
        item->state = 37;
        break;
    case 37:
        item->state = 37;
        break;
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

// fn_2_2D640, size:0x1D4
void fn_2_2D640(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706) == item->unk10) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    case 37:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706) == item->unk10) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        break;
    case 5:
        item->timer = 0x28;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    }
}

// fn_2_2AA8C, size:0x2A4
void fn_2_2AA8C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 0, 8, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 0, lbl_800E869C[*(s16*)(lbl_2_bss_1A824C[0] + 0x197706)] + 8);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 3;
        break;
    }
    case 3: {
        s32 v = item->unk12;
        item->unk12 = v + (0xFF - v) / 4;
        item->unk12 = item->unk12 + 1;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 37;
        }
        break;
    }
    case 37:
        item->state = 37;
        break;
    case 5:
        item->timer = 9;
        item->state = 6;
        break;
    case 6: {
        s32 v = item->unk12;
        item->unk12 = v + (-v) / 4;
        item->unk12 = item->unk12 - 1;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        if (item->unk12 <= 0 || item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 7;
        }
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 0;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

extern s32 fn_2_44F14(u8 index);
extern s32 fn_8006CDC0(u8 index);
extern s16 lbl_8010B3E8[];
extern s16 lbl_8010B444[][11];

// fn_2_2A77C, size:0x2D4
void fn_2_2A77C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 0, lbl_8010B3E8[0], 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        u8 id = lbl_800E869C[*(s16*)(lbl_2_bss_1A824C[0] + 0x197706)];
        s32 row = fn_2_44F14(id);
        s32 col = fn_8006CDC0(id);
        s32 a = lbl_8010B444[row][col];
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 0, a + lbl_8010B3E8[*(s16*)(lbl_2_bss_1A824C[0] + 0x197706)]);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 3;
        break;
    }
    case 3: {
        s32 v = item->unk12;
        item->unk12 = v + (0xFF - v) / 4;
        item->unk12 = item->unk12 + 1;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 37;
        }
        break;
    }
    case 37:
        item->state = 37;
        break;
    case 5:
        item->timer = 9;
        item->state = 6;
        break;
    case 6: {
        s32 v = item->unk12;
        item->unk12 = v + (-v) / 4;
        item->unk12 = item->unk12 - 1;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        if (item->unk12 <= 0 || item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 7;
        }
        break;
    }
    case 4:
    case 1:
        break;
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 0;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}

extern s16 lbl_2_data_107BC[];

// fn_2_25524, size:0x254
void fn_2_25524(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19774E) = 0;
        if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197857) == item->index) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 3;
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 37;
        }
        break;
    case 3:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19774E) += 1;
        if ((*(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) >> 16) >=
            (u32)lbl_2_data_107BC[item->index]) {
            lbl_2_bss_1A824C[0][0x197859] = 1;
            item->state = 37;
        }
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 4:
    case 1:
    case 37:
        break;
    }
}

// fn_2_2D0D4, size:0x434
void fn_2_2D0D4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0x50000;
        fn_800363D8(menu, item->offset, 1, 0x41, *(s16*)(lbl_2_bss_1A824C[0] + 0x197730));
        item->state = 37;
        break;
    }
    case 30: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0x50000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 31;
        break;
    }
    case 31: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            fn_800363D8(menu, item->offset, 1, 0x41, *(s16*)(lbl_2_bss_1A824C[0] + 0x197730));
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x5C) = 0xA0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
            item->state = 32;
        }
        break;
    }
    case 32: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) <= 5) {
            *(u32*)(object + 0x5C) = 0x50000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 38;
        }
        break;
    }
    case 33: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0x50000;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 34;
        break;
    }
    case 34: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 10) {
            fn_800363D8(menu, item->offset, 1, 0x41, *(s16*)(lbl_2_bss_1A824C[0] + 0x197730));
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x5C) = 0;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 35;
        }
        break;
    }
    case 35: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 5) {
            *(u32*)(object + 0x5C) = 0x50000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 38;
        }
        break;
    }
    case 8: {
        u8* object;
        fn_800363D8(menu, item->offset, 1, 0x41, *(s16*)(lbl_2_bss_1A824C[0] + 0x197730));
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0x50000;
        item->state = 38;
        break;
    }
    case 5: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0x50000;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_331C8, size:0x474
void fn_2_331C8(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x5C) = 0;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        } else {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x5C) = 0xF0000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        }
        item->state = 3;
        break;
    }
    case 3:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) >= 5) {
                *(u32*)(object + 0x5C) = 0x50000;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                item->state = 37;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) <= 10) {
                *(u32*)(object + 0x5C) = 0xA0000;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                item->state = 37;
            }
        }
        break;
    case 37:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) <= 5) {
                *(u32*)(object + 0x5C) = 0x50000;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            } else {
                object[0x68] = 4;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) >= 10) {
                *(u32*)(object + 0x5C) = 0xA0000;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            } else {
                object[0x68] = 1;
            }
        }
        break;
    case 5:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        } else {
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        }
        item->state = 6;
        break;
    case 6:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x1976DE) == 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) == 0) {
                object[0x68] = 0;
                item->state = 7;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            if ((*(u32*)(object + 0x5C) >> 16) >= 15) {
                object[0x68] = 0;
                item->state = 7;
            }
        }
        break;
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    }
}

// fn_2_2EFCC, size:0x594
void fn_2_2EFCC(MenuTableContext* menu, MenuItemState* item) {
    s32 digit;
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->index) {
    case 0:
        digit = *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) / 100;
        break;
    case 1:
        digit = *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) / 10 % 10;
        break;
    case 2:
        digit = *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) % 10;
        break;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x5C) = 0;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197734) = *(s16*)(lbl_2_bss_1A8248 + 0x43BC);
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) = *(s16*)(lbl_2_bss_1A824C[0] + 0x19773C) = *(s16*)(lbl_2_bss_1A8248 + 0x43BC);
        switch (item->index) {
        case 0:
            digit = *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) / 100;
            break;
        case 1:
            digit = *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) / 10 % 10;
            break;
        case 2:
            digit = *(s16*)(lbl_2_bss_1A824C[0] + 0x197736) % 10;
            break;
        }
        fn_800363D8(menu, item->offset, 1, 0xD, digit);
        item->state = 3;
        break;
    }
    case 3: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0x15) {
            object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 17:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197736) != *(s16*)(lbl_2_bss_1A824C[0] + 0x19773C)) {
            fn_800363D8(menu, item->offset, 1, 0xD, digit);
            item->state = 18;
        } else {
            item->state = 37;
        }
        break;
    case 18:
        item->state = 37;
        break;
    case 20:
        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x197736) != *(s16*)(lbl_2_bss_1A824C[0] + 0x19773C)) {
            fn_800363D8(menu, item->offset, 1, 0xD, digit);
            item->state = 21;
        } else {
            item->state = 37;
        }
        break;
    case 21:
        item->state = 37;
        break;
    case 30:
    case 33:
        switch (item->index) {
        case 0:
            digit = *(s16*)(lbl_2_bss_1A8248 + 0x43BC) / 100;
            break;
        case 1:
            digit = *(s16*)(lbl_2_bss_1A8248 + 0x43BC) / 10 % 10;
            break;
        case 2:
            digit = *(s16*)(lbl_2_bss_1A8248 + 0x43BC) % 10;
            break;
        }
        fn_800363D8(menu, item->offset, 1, 0xD, digit);
        item->state = 37;
        break;
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

// fn_2_29884, size:0x69C
void fn_2_29884(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        if (lbl_2_bss_1A824C[0][0x1978F6] == 0) {
            if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
                s32 flag = (lbl_2_bss_1A8248 + lbl_800E869C[item->unk10])[0x444D];
                if (flag == 1) {
                    *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2E;
                    fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                    object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x5C) = 0;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
                } else {
                    *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2D;
                    fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                    object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x5C) = 0;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                }
            } else {
                *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2D;
                fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x5C) = 0x10000;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
                s32 flag = (lbl_2_bss_1A8248 + lbl_800E869C[item->unk10])[0x44B9];
                if (flag == 1) {
                    *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2E;
                    fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                    object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x5C) = 0;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
                } else {
                    *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2D;
                    fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                    object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x5C) = 0;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                }
            } else {
                *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2D;
                fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x5C) = 0x10000;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        }
        item->state = 37;
        break;
    }
    case 8: {
        u8* object;
        if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
            s32 flag = (lbl_2_bss_1A8248 + lbl_800E869C[item->unk10])[0x44B9];
            if (flag == 1) {
                *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2E;
                fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x5C) = 0;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2D;
                fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x5C) = 0;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2D;
            fn_800363D8(menu, item->offset, 1, 0x43, item->unk10);
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x5C) = 0x10000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 0x28;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    case 37:
        break;
    }
}

extern s16 lbl_2_data_2E44[][4];
int rand(void);

// fn_2_200E4, size:0x100
s32 fn_2_200E4(void) {
    s32 level;

    if ((lbl_2_bss_1A8248 + *(s16*)(lbl_2_bss_1A8248 + 0x16C0) * 10)[0x40F6] == 1) {
        return 0;
    }
    if ((lbl_2_bss_1A8248 + *(s16*)(lbl_2_bss_1A8248 + 0x16C0) * 10)[0x40F0] == 5) {
        return 0;
    }
    level = lbl_2_bss_1A8248[0x442B];
    if (level > 3) {
        level = 3;
    }
    if (lbl_2_data_2E44[lbl_2_bss_1A8248[0x4415]][level] >= rand() % 100 &&
        lbl_2_bss_1A8248[0x441C] != 5) {
        if (lbl_2_bss_1A8248[0x4422] == 0) {
            return 0;
        }
        if (lbl_2_bss_1A8248[0x442B] < 3) {
            lbl_2_bss_1A8248[0x442B]++;
        }
        return 1;
    }
    return 0;
}

// fn_2_26AF4, size:0x17C
void fn_2_26AF4(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        item->timer = 0xDC;
        item->state = 3;
        return;
    }
    case 3:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 37;
        }
    case 1:
    case 37:
    case 5:
    default:
        return;
    }
}

extern u8 lbl_803CB8F0[];

// fn_2_2F544, size:0x1CC
// NONMATCHING 99%: loop pointer and hoisted global swap r4/r6
#if NONMATCHING
void fn_2_2F544(MenuTableContext* menu, MenuItemState* item) {
    s16 list[9];
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        s16* out = list;
        u8* entry = lbl_2_bss_1A8248;
        u8* object;
        s16 value;
        s16 i;
        for (i = 0; i < 9; i++) {
            value = *(s16*)(entry + 0x40B8);
            if (value != lbl_803CB8F0[lbl_2_bss_1A8248[0x441C]]) {
                *out++ = value;
            }
            entry += 6;
        }
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = list[item->index] << 16;
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 0x19;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
    case 37:
    case 1:
        return;
    }
}
#endif

// fn_2_2B654, size:0x230
// NONMATCHING 99%: (row*0x34+9)+index*2 summed in a different order before the lbzx
#if NONMATCHING
void fn_2_2B654(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        s32 index = item->index;
        s32 row = *(s16*)(lbl_2_bss_1A824C[0] + 0x197706);
        u8* object;
        if (lbl_80109AE8[row][index].type != -1) {
            if (((s8(*)[0x34])lbl_2_bss_1A8248)[lbl_800E869C[row]][9 + index * 2] < 0) {
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
            }
        } else {
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        item->state = 37;
        return;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        return;
    case 6:
        if (item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
    case 37:
    case 1:
        return;
    }
}
#endif

// fn_2_2BB34, size:0x270
// NONMATCHING 99%: (row*0x34+9)+index*2 summed in a different order before the lbzx
#if NONMATCHING
void fn_2_2BB34(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        s32 index = item->index;
        s32 row = *(s16*)(lbl_2_bss_1A824C[0] + 0x197706);
        u8* object;
        if (lbl_80109AE8[row][index].type != -1) {
            if (((s8(*)[0x34])lbl_2_bss_1A8248)[lbl_800E869C[row]][9 + index * 2] < 0) {
                fn_800363D8(menu, item->offset, 1, 0x5A, 1);
            } else {
                fn_800363D8(menu, item->offset, 1, 0x5A, 0);
            }
        } else {
            fn_800363D8(menu, item->offset, 1, 0x5A, 0);
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
    }
    case 37:
    case 1:
        return;
    }
}
#endif

// fn_2_2BF20, size:0x288
void fn_2_2BF20(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
    case 8: {
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        s32 row = *(s16*)(ctx + 0x7706);
        if (lbl_80109AE8[row][item->index].type != -1) {
            s32 first;
            s32 second;
            s16 firstValue;
            u8* record;
            first = *(s16*)(ctx + 0x7710);
            record = lbl_2_bss_1A8248 + lbl_800E869C[row] * 0x34;
            firstValue = record[9 + first * 2];
            if ((s8)firstValue < 0 && (s8)record[9 + (second = *(s16*)(ctx + 0x7712)) * 2] < 0 &&
                first != second) {
            } else if ((s8)firstValue < 0) {
                u8* object;
                *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
                object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}

// fn_2_2B884, size:0x2B0
// NONMATCHING 99%: (row*0x34+9)+index*2 summed in a different order before the lbzx
#if NONMATCHING
void fn_2_2B884(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
    case 8: {
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        s32 row = *(s16*)(ctx + 0x7706);
        s32 index = item->index;
        if (lbl_80109AE8[row][index].type != -1) {
            if (((s8(*)[0x34])lbl_2_bss_1A8248)[lbl_800E869C[row]][9 + index * 2] < 0) {
                if (*(s16*)(ctx + 0x7710) == index) {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) |= 2;
                    *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
                } else {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) &= ~2U;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                }
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 9;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}
#endif

extern s16 fn_2_53AA4(void* item);
extern s16 lbl_2_data_1050C[4][6];
extern s16 lbl_2_data_1053C[4][6];
extern s16 lbl_2_data_1056C[4][6];

// fn_2_25A48, size:0x324
// NONMATCHING 99%: case 0 schedules li r0,0x26 one slot later
#if NONMATCHING
void fn_2_25A48(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53AA4(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object;
        *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) =
            lbl_2_data_1050C[lbl_2_bss_1A8248[0x4415]][lbl_2_bss_1A8248[0x441C]];
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        item->timer = 30;
        item->state = 3;
        break;
    }
    case 3: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 4;
        }
        break;
    }
    case 4: {
        if ((*(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) >> 16) >= lbl_2_data_1053C[lbl_2_bss_1A8248[0x4415]][lbl_2_bss_1A8248[0x441C]]) {
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = lbl_2_data_1053C[lbl_2_bss_1A8248[0x4415]][lbl_2_bss_1A8248[0x441C]] << 16;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            item->state = 37;
        }
        break;
    }
    case 5:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) =
            lbl_2_data_1056C[lbl_2_bss_1A8248[0x4415]][lbl_2_bss_1A8248[0x441C]] << 16;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        item->state = 6;
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xA1) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}
#endif

extern s16 lbl_2_data_3764[][4];

// fn_2_3039C, size:0x33C
void fn_2_3039C(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        s16 value = lbl_2_data_3764[item->index + *(s16*)(lbl_2_bss_1A824C[0] + 0x19772A)][lbl_2_bss_1A8248[0x4415]];
        u8* object;
        fn_800363D8(menu, item->offset, 1, 0x66, value / 100 % 10);
        fn_800363D8(menu, item->offset, 2, 0x66, value / 10 % 10);
        fn_800363D8(menu, item->offset, 3, 0x66, value % 10);
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 37;
        break;
    }
    case 8:
    case 17: {
        s16 value = lbl_2_data_3764[item->index + *(s16*)(lbl_2_bss_1A824C[0] + 0x19772A)][lbl_2_bss_1A8248[0x4415]];
        fn_800363D8(menu, item->offset, 1, 0x66, value / 100 % 10);
        fn_800363D8(menu, item->offset, 2, 0x66, value / 10 % 10);
        fn_800363D8(menu, item->offset, 3, 0x66, value % 10);
        item->state = 37;
        break;
    }
    case 5:
        item->timer = 14;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}

extern u8* lbl_2_bss_1A8244[];

static inline s32 fn_2_262D0_canAdvance(void) {
    s32 result = 0;
    if (lbl_2_bss_1A8244[0][0xE4 + lbl_2_bss_1A8248[0x4415]] == 0 && lbl_2_bss_1A8248[0x4415] < 3) {
        result = 1;
    }
    return result;
}

// fn_2_262D0, size:0x3B4
void fn_2_262D0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        item->state = 3;
        break;
    }
    case 17:
        if (fn_2_262D0_canAdvance()) {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 7;
            item->timer = 0x8C;
            item->state = 18;
        } else {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 8;
            item->timer = 0x8C;
            item->state = 18;
        }
        break;
    case 18: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) |= 2;
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 19;
        }
        break;
    }
    case 19: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xA0) {
            *(u32*)(object + 0x5C) = 0x410000;
        }
        break;
    }
    case 5:
        if (fn_2_262D0_canAdvance()) {
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0xA00000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 6;
        } else {
            *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0xA00000;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            item->state = 6;
        }
        break;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) >= 0xB4) {
            object[0x68] = 0;
            item->state = 7;
        }
        break;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        break;
    }
    case 37:
        break;
    }
}

extern s32 fn_2_44E2C(s32 ch);

#if NONMATCHING
static inline void fn_2_28EA0_showIfChanged(MenuTableContext* menu, MenuItemState* item) {
    u8 id = lbl_800E869C[item->unk10];
    s32 flag = (s8)lbl_2_bss_1A8248[0x44B9 + id];
    s32 current = fn_8006CDC0(id);
    s32 saved = fn_2_44E2C(id);
    if (flag == 1 && current != saved) {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
    } else {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
    }
}

// fn_2_28EA0, size:0x3CC
// NONMATCHING 98%: id/flag registers r27/r28 swapped in the inlined helper
void fn_2_28EA0(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        if (lbl_2_bss_1A824C[0][0x1978F6] == 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        } else if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
            fn_2_28EA0_showIfChanged(menu, item);
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    case 8:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        fn_2_28EA0_showIfChanged(menu, item);
        item->state = 37;
        break;
    case 5:
        item->timer = 0x28;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}
#endif

// lbl_8010A768[row][10] entries, parallel to lbl_80109AE8.
typedef struct MissionText {
    /* 0x0 */ s16 textId;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 pad4[6];
} MissionText;

extern MissionText lbl_8010A768[][10];

// fn_2_2A338, size:0x444
// NONMATCHING 96%: case 2 prologue scheduling/registers differ (lbl_2_bss_1A824C loaded via addi;lwz 0)
#if NONMATCHING
void fn_2_2A338(MenuTableContext* menu, MenuItemState* item) {
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->unk12 = 0;
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 0, lbl_8010A768[0][0].textId, 0);
        item->state = 38;
        break;
    }
    case 2:
    case 8: {
        u8* ctx = lbl_2_bss_1A824C[0] + 0x190000;
        s32 row = *(s16*)(ctx + 0x7706);
        s32 sel = *(s16*)(ctx + 0x7710);
        s16 textId = lbl_8010A768[row][sel].textId;
        s16 check = lbl_8010A768[row][sel].unk2;
        s16 flags = lbl_80109AE8[row][sel].flags;
        s16 minLevel = lbl_80109AE8[row][sel].minLevel;
        u8* record = lbl_2_bss_1A8248 + lbl_800E869C[row] * 0x34;
        u8* object;
        if (check != -1 && (s8)record[sel * 2 + 0xA] == 0) {
            u8 level = lbl_2_bss_1A8248[0x4415];
            if (level < minLevel) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else if ((flags & 2) && level < 1) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else if ((flags & 4) && level < 2) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else if ((flags & 8) && level < 3) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else {
                fn_8000FE08(item->unk14, 0, 0x1C5);
            }
        } else if (check != -1 && (s32)record[sel * 2 + 0xA] == 1 && (s8)record[sel * 2 + 9] == 0) {
            u8 level = lbl_2_bss_1A8248[0x4415];
            if (level < minLevel) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else if ((flags & 2) && level < 1) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else if ((flags & 4) && level < 2) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else if ((flags & 8) && level < 3) {
                fn_8000FE08(item->unk14, 0, 0x1C6);
            } else {
                fn_8000FE08(item->unk14, 0, textId);
            }
        } else {
            fn_8000FE08(item->unk14, 0, textId);
        }
        object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        item->state = 3;
        break;
    }
    case 3: {
        s32 v = item->unk12;
        item->unk12 = v + (0xFF - v) / 4;
        item->unk12 = item->unk12 + 1;
        if (item->unk12 > 0xFF) {
            item->unk12 = 0xFF;
        }
        if (item->unk12 >= 0xFF) {
            item->state = 37;
        }
        break;
    }
    case 37:
        item->state = 37;
        break;
    case 5:
        item->timer = 9;
        item->state = 6;
        break;
    case 6: {
        s32 v = item->unk12;
        item->unk12 = v + (-v) / 4;
        item->unk12 = item->unk12 - 1;
        if (item->unk12 < 0) {
            item->unk12 = 0;
        }
        if (item->unk12 <= 0 || item->timer-- <= 0) {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            item->state = 7;
        }
        break;
    }
    }
    lbl_80366B18[item->unk14 * 0x38 + 0x2F] = 1;
    {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x58) = (u32)item->unk12 | (*(u32*)(object + 0x58) & ~0xFFU);
    }
}
#endif

extern u8 lbl_8034E9A0[];
extern void* memcpy(void* dest, const void* src, u32 n);
extern u8 lbl_2_data_3F98[][0x1FE];
extern u8 lbl_2_data_3F60[][9];
extern s16 lbl_2_data_3EC8[];
extern u8 lbl_2_data_2E40[];
extern void fn_2_6AE08(void);
extern void fn_2_90538(void);
extern void fn_2_46ADC(void);
extern void fn_2_45978(void);
extern void fn_2_42EB0(void);
extern void fn_2_432EC(void);

static inline u8 fn_2_20328_mode(void) {
    u8 mode = 0;
    switch (*(s32*)(lbl_8034E9A0 + 0x46E0)) { // TODO type: CharSelectState.captain[0]
    case 0:
        mode = 0;
        break;
    case 4:
        mode = 1;
        break;
    case 10:
        mode = 2;
        break;
    case 2:
        mode = 3;
        break;
    case 6:
        mode = 4;
        break;
    case 9:
        mode = 5;
        break;
    }
    return mode;
}

// fn_2_20328, size:0x4D4
void fn_2_20328(void) {
    u8 mode = fn_2_20328_mode();
    u8 level;
    s32 i;

    lbl_2_bss_1A8248[0x441C] = mode;
    level = lbl_8034E9A0[0x4711];
    lbl_2_bss_1A8248[0x4416] = level;
    lbl_2_bss_1A8248[0x4415] = level;
    lbl_2_bss_1A8248[0x441D] = lbl_803CB8F0[lbl_2_bss_1A8248[0x441C]];
    memcpy(lbl_2_bss_1A8248 + 0x40EE, lbl_2_data_3F98[lbl_2_bss_1A8248[0x441C]], 0x1FE);
    memcpy(lbl_2_bss_1A8248 + 0x440C, lbl_2_data_3F60[lbl_2_bss_1A8248[0x441C]], 9);
    fn_2_6AE08();
    *(s16*)(lbl_2_bss_1A8248 + 0x16C2) = lbl_2_data_3EC8[lbl_2_bss_1A8248[0x441C]];
    *(s16*)(lbl_2_bss_1A8248 + 0x16C0) = lbl_2_data_3EC8[lbl_2_bss_1A8248[0x441C]];
    *(s16*)(lbl_2_bss_1A8248 + 0x16BE) = lbl_2_data_3EC8[lbl_2_bss_1A8248[0x441C]];
    *(s16*)(lbl_2_bss_1A8248 + 0x1798) = -1;
    *(s16*)(lbl_2_bss_1A8248 + 0x1796) = -1;
    fn_2_90538();
    lbl_2_bss_1A8248[0x4418] = lbl_2_data_2E40[lbl_2_bss_1A8248[0x4415]];
    lbl_2_bss_1A8248[0x4419] = lbl_2_data_2E40[lbl_2_bss_1A8248[0x4415]];
    *(s16*)(lbl_2_bss_1A8248 + 0x43BC) = 0;
    *(s16*)(lbl_2_bss_1A8248 + 0x43BE) = 0;
    lbl_2_bss_1A8248[0x4422] = 0;
    lbl_2_bss_1A8248[0x4423] = 0;
    lbl_2_bss_1A8248[0x4424] = 0;
    lbl_2_bss_1A8248[0x4426] = 0;
    lbl_2_bss_1A8248[0x4427] = 0;
    lbl_2_bss_1A8248[0x4428] = 0;
    lbl_2_bss_1A8248[0x4449] = 0;
    if (lbl_2_bss_1A8248[0x441C] == 5) {
        lbl_2_bss_1A8248[0x4439] = 0;
    } else {
        lbl_2_bss_1A8248[0x4439] = 1;
    }
    lbl_2_bss_1A8248[0x441A] = 0;
    lbl_2_bss_1A8248[0x444A] = 0;
    lbl_2_bss_1A8248[0x4446] = 0;
    lbl_2_bss_1A8248[0x4447] = 0;
    lbl_2_bss_1A8248[0x44EF] = 0;
    lbl_2_bss_1A8248[0x44F0] = 0;
    lbl_2_bss_1A8248[0x44F4] = 0;
    lbl_2_bss_1A8248[0x442A] = 0;
    *(s8*)(lbl_2_bss_1A8248 + 0x444C) = -1;
    *(s8*)(lbl_2_bss_1A8248 + 0x444B) = -1;
    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A8248[0x43C2 + i] = lbl_2_bss_1A8248[0x15F1 + i];
    }
    lbl_2_bss_1A8248[0x442B] = 0;
    lbl_2_bss_1A8248[0x442F] = 0;
    lbl_2_bss_1A8248[0x442C] = 0;
    lbl_2_bss_1A8248[0x442D] = 0;
    lbl_2_bss_1A8248[0x442E] = 0;
    lbl_2_bss_1A8248[0x4438] = 0;
    lbl_2_bss_1A8248[0x4445] = 1;
    *(s32*)(lbl_2_bss_1A8248 + 0x42EC) = 0;
    lbl_2_bss_1A8248[0x4431] = 0;
    lbl_2_bss_1A8248[0x4432] = 0;
    lbl_2_bss_1A8248[0x4433] = 0;
    lbl_2_bss_1A8248[0x4434] = 0;
    lbl_2_bss_1A8248[0x4435] = 0;
    fn_2_46ADC();
    fn_2_45978();
    for (i = 0; i < 9; i++) {
        *(s16*)(lbl_2_bss_1A8248 + 0x40B8 + i * 6) = inMemRoster[0][i].stats.CharID;
    }
    lbl_2_bss_1A8248[0x44F6] = 0;
    lbl_2_bss_1A8248[0x44F7] = 0;
    fn_2_42EB0();
    fn_2_432EC();
    lbl_2_bss_1A8248[0x44F8] = 3;
    lbl_2_bss_1A8248[0x44F9] = 3;
    lbl_2_bss_1A8248[0x44FA] = 3;
    lbl_2_bss_1A8248[0x44FB] = 3;
    lbl_2_bss_1A8248[0x44FC] = 3;
    lbl_2_bss_1A8248[0x44FD] = 3;
    lbl_2_bss_1A8248[0x44FE] = 0;
    lbl_2_bss_1A8248[0x44FF] = 0;
    lbl_2_bss_1A8248[0x4500] = 0;
    lbl_2_bss_1A8248[0x4501] = 0;
    lbl_2_bss_1A8248[0x4502] = 0;
    lbl_2_bss_1A8248[0x4503] = 0;
    lbl_2_bss_1A8248[0x4504] = 0;
    lbl_2_bss_1A8248[0x4505] = 0;
}

extern void fn_2_467FC(void);
extern void fn_2_45810(void);

// fn_2_207FC, size:0x4B4
void fn_2_207FC(void) {
    u8 mode = fn_2_20328_mode();
    u8 level;
    s32 i;

    lbl_2_bss_1A8248[0x441C] = mode;
    level = lbl_8034E9A0[0x4711];
    lbl_2_bss_1A8248[0x4416] = level;
    lbl_2_bss_1A8248[0x4415] = level;
    lbl_2_bss_1A8248[0x441D] = lbl_803CB8F0[lbl_2_bss_1A8248[0x441C]];
    memcpy(lbl_2_bss_1A8248 + 0x40EE, lbl_2_data_3F98[lbl_2_bss_1A8248[0x441C]], 0x1FE);
    memcpy(lbl_2_bss_1A8248 + 0x440C, lbl_2_data_3F60[lbl_2_bss_1A8248[0x441C]], 9);
    fn_2_6AE08();
    *(s16*)(lbl_2_bss_1A8248 + 0x16C2) = lbl_2_data_3EC8[lbl_2_bss_1A8248[0x441C]];
    *(s16*)(lbl_2_bss_1A8248 + 0x16C0) = lbl_2_data_3EC8[lbl_2_bss_1A8248[0x441C]];
    *(s16*)(lbl_2_bss_1A8248 + 0x16BE) = lbl_2_data_3EC8[lbl_2_bss_1A8248[0x441C]];
    *(s16*)(lbl_2_bss_1A8248 + 0x1798) = -1;
    *(s16*)(lbl_2_bss_1A8248 + 0x1796) = -1;
    fn_2_90538();
    lbl_2_bss_1A8248[0x4418] = lbl_2_data_2E40[0];
    lbl_2_bss_1A8248[0x4419] = lbl_2_data_2E40[0];
    *(s16*)(lbl_2_bss_1A8248 + 0x43BC) = 0;
    *(s16*)(lbl_2_bss_1A8248 + 0x43BE) = 0;
    lbl_2_bss_1A8248[0x4422] = 0;
    lbl_2_bss_1A8248[0x4423] = 0;
    lbl_2_bss_1A8248[0x4424] = 0;
    lbl_2_bss_1A8248[0x4425] = 0;
    lbl_2_bss_1A8248[0x4426] = 0;
    lbl_2_bss_1A8248[0x4427] = 0;
    lbl_2_bss_1A8248[0x4428] = 0;
    lbl_2_bss_1A8248[0x4449] = 0;
    if (lbl_2_bss_1A8248[0x441C] == 5) {
        lbl_2_bss_1A8248[0x4439] = 0;
    } else {
        lbl_2_bss_1A8248[0x4439] = 1;
    }
    lbl_2_bss_1A8248[0x441A] = 0;
    lbl_2_bss_1A8248[0x444A] = 0;
    lbl_2_bss_1A8248[0x4446] = 0;
    lbl_2_bss_1A8248[0x4447] = 0;
    lbl_2_bss_1A8248[0x44EF] = 0;
    lbl_2_bss_1A8248[0x44F0] = 0;
    lbl_2_bss_1A8248[0x44F4] = 0;
    lbl_2_bss_1A8248[0x442A] = 0;
    *(s8*)(lbl_2_bss_1A8248 + 0x444C) = -1;
    *(s8*)(lbl_2_bss_1A8248 + 0x444B) = -1;
    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A8248[0x43C2 + i] = 0;
    }
    lbl_2_bss_1A8248[0x442B] = 0;
    lbl_2_bss_1A8248[0x442F] = 0;
    lbl_2_bss_1A8248[0x442C] = 0;
    lbl_2_bss_1A8248[0x442D] = 0;
    lbl_2_bss_1A8248[0x442E] = 0;
    lbl_2_bss_1A8248[0x4438] = 0;
    lbl_2_bss_1A8248[0x4445] = 1;
    *(s32*)(lbl_2_bss_1A8248 + 0x42EC) = 0;
    lbl_2_bss_1A8248[0x4431] = 0;
    lbl_2_bss_1A8248[0x4432] = 0;
    lbl_2_bss_1A8248[0x4433] = 0;
    lbl_2_bss_1A8248[0x4434] = 0;
    lbl_2_bss_1A8248[0x4435] = 0;
    fn_2_46ADC();
    fn_2_467FC();
    fn_2_45978();
    fn_2_45810();
    for (i = 0; i < 9; i++) {
        *(s16*)(lbl_2_bss_1A8248 + 0x40B8 + i * 6) = inMemRoster[0][i].stats.CharID;
    }
    lbl_2_bss_1A8248[0x44F6] = 0;
    lbl_2_bss_1A8248[0x44F7] = 0;
    lbl_2_bss_1A8248[0x44F8] = 3;
    lbl_2_bss_1A8248[0x44F9] = 3;
    lbl_2_bss_1A8248[0x44FA] = 3;
    lbl_2_bss_1A8248[0x44FB] = 3;
    lbl_2_bss_1A8248[0x44FC] = 3;
    lbl_2_bss_1A8248[0x44FD] = 3;
    lbl_2_bss_1A8248[0x44FE] = 0;
    lbl_2_bss_1A8248[0x44FF] = 0;
    lbl_2_bss_1A8248[0x4500] = 0;
    lbl_2_bss_1A8248[0x4501] = 0;
    lbl_2_bss_1A8248[0x4502] = 0;
    lbl_2_bss_1A8248[0x4503] = 0;
    lbl_2_bss_1A8248[0x4504] = 0;
    lbl_2_bss_1A8248[0x4505] = 0;
}

struct SpaniOwner;
void fn_80036270(struct SpaniOwner* owner, s32 idx, u32 track, u32 frame, s16* outX, s16* outY);

// fn_2_338D4, size:0x59C
// NONMATCHING 99%: 'kind == 3' digit branches compile to beq instead of bne; b
#if NONMATCHING
void fn_2_338D4(MenuTableContext* menu, MenuItemState* item) {
    s16 track;
    s16 value;
    s16 magnitude;
    s16 kind;
    s16 state;
    kind = item->unk10 >> 4;
    track = item->unk10 & 0xF;
    state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        return;
    }
    case 2: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) |= 2;
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
        switch (kind) {
        case 0:
            value = *(s16*)(lbl_2_bss_1A824C[0] + 0x197766);
            magnitude = __abs(*(s16*)(lbl_2_bss_1A824C[0] + 0x197766));
            break;
        case 1:
            value = *(s16*)(lbl_2_bss_1A824C[0] + 0x197768);
            magnitude = __abs(*(s16*)(lbl_2_bss_1A824C[0] + 0x197768));
            break;
        case 2:
            value = *(s16*)(lbl_2_bss_1A824C[0] + 0x19776A);
            magnitude = __abs(*(s16*)(lbl_2_bss_1A824C[0] + 0x19776A));
            break;
        case 3:
            value = *(s16*)(lbl_2_bss_1A824C[0] + 0x19776C);
            magnitude = __abs(*(s16*)(lbl_2_bss_1A824C[0] + 0x19776C));
            break;
        }
        if (magnitude == 10000) {
            fn_800363D8(menu, item->offset, 1, 0x2C, 0x17);
        } else {
            switch (item->index) {
            case 0: {
                s16 digit = magnitude % 10;
                fn_800363D8(menu, item->offset, 1, 0x2C, kind == 3 ? digit : (s16)(digit + 0xC));
                break;
            }
            case 1: {
                s16 digit = magnitude / 10 % 10;
                if (magnitude < 10) {
                    digit = 0x17;
                } else if (kind != 3) {
                    digit = digit + 0xC;
                }
                fn_800363D8(menu, item->offset, 1, 0x2C, digit);
                break;
            }
            case 2: {
                s16 digit = magnitude / 100 % 10;
                if (magnitude < 100) {
                    digit = 0x17;
                } else if (kind != 3) {
                    digit = digit + 0xC;
                }
                fn_800363D8(menu, item->offset, 1, 0x2C, digit);
                break;
            }
            case 3: {
                s16 sign;
                s16 x0, y0, x1, y1;
                s16 width;
                if (value < 0) {
                    if (kind == 3) {
                        sign = 0xB;
                    } else {
                        sign = 0x16;
                    }
                } else if (value > 0) {
                    if (kind == 3) {
                        sign = 0xA;
                    } else {
                        sign = 0x17;
                    }
                } else {
                    sign = 0x17;
                }
                fn_800363D8(menu, item->offset, 1, 0x2C, sign);
                fn_80036270((struct SpaniOwner*)menu, 0x280, 0, 0, &x0, &y0);
                fn_80036270((struct SpaniOwner*)menu, 0x280, 2, 0, &x0, &y0);
                fn_80036270((struct SpaniOwner*)menu, 0x280, 1, 0, &x1, &y1);
                width = __abs(x1 - x0);
                fn_80036270((struct SpaniOwner*)menu, 0x280, track, 0, &x0, &y0);
                if (magnitude == 0) {
                    x0 = 0;
                } else if (magnitude < 10) {
                    x0 = width * 2;
                } else if (magnitude < 100) {
                    x0 = width;
                } else {
                    x0 = 0;
                }
                *(f32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x48) = x0;
                break;
            }
            }
        }
        item->state = 37;
        return;
    }
    case 5:
        lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 4;
        item->state = 6;
        return;
    case 6: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        if ((*(u32*)(object + 0x5C) >> 16) == 0) {
            object[0x68] = 0;
            item->state = 7;
        }
        return;
    }
    case 7: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
    }
    case 37:
    case 1:
        return;
    }
}
#endif

// fn_2_2926C, size:0x618
// NONMATCHING 99%: flag byte is not sign-extended (only compared with 0/1, so same behaviour)
#if NONMATCHING
void fn_2_2926C(MenuTableContext* menu, MenuItemState* item) {
    s32 flag;
    u8 id;
    s32 current;
    s32 saved;
    s16 state = fn_2_53BC8(item);
    if (state != -1) {
        item->state = state;
    }
    switch (item->state) {
    case 0: {
        u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
        *(u32*)(object + 0x54) &= ~2U;
        item->state = 38;
        break;
    }
    case 2:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        if (lbl_2_bss_1A824C[0][0x1978F6] == 0) {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2C;
            if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
                if ((s32)lbl_2_bss_1A8248[0x444D + lbl_800E869C[item->unk10]] == 1) {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) |= 2;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
                } else {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) &= ~2U;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                }
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2F;
            if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
                id = lbl_800E869C[item->unk10];
                flag = lbl_2_bss_1A8248[0x44B9 + id];
                current = fn_8006CDC0(id);
                saved = fn_2_44E2C(id);
                if (flag == 1 && current == saved) {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) |= 2;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
                } else if (flag == 0 && current == saved) {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) |= 2;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                } else {
                    u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                    *(u32*)(object + 0x54) &= ~2U;
                    lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
                }
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        }
        item->state = 37;
        break;
    case 8:
        *(u32*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x5C) = 0;
        *(s16*)(lbl_80371C30[menu->firstIndex + item->offset].object + 0x64) = 0x2F;
        if (fn_8006C79C(lbl_800E869C[item->unk10]) == 1) {
            id = lbl_800E869C[item->unk10];
            flag = lbl_2_bss_1A8248[0x44B9 + id];
            current = fn_8006CDC0(id);
            saved = fn_2_44E2C(id);
            if (flag == 1 && current == saved) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else if (flag == 0 && current == saved) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            } else {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) &= ~2U;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            }
        } else {
            u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
        }
        item->state = 37;
        break;
    case 5:
        item->timer = 0x28;
        item->state = 6;
        break;
    case 6: {
        s16 previous = item->timer;
        item->timer = previous - 1;
        if (previous <= 0) {
            u8* object;
            lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 0;
            object = lbl_80371C30[menu->firstIndex + item->offset].object;
            *(u32*)(object + 0x54) &= ~2U;
        }
        break;
    }
    case 37:
        break;
    }
}
#endif

extern u8* lbl_2_bss_1A823C[];
extern const Vec lbl_2_data_2EA4[];
extern s16 lbl_2_data_3ED4[];
extern s16 lbl_2_data_3EE0[];
extern s16 lbl_2_data_3EEC[];
extern s16 lbl_2_data_3EF0[];
extern s32 fn_2_4C3D8(s32 index);
extern void fn_2_93C64(void);
extern void fn_2_71F60(void);
extern void fn_2_9257C(void);

// fn_2_24800, size:0x69C
// NONMATCHING 97%: loop pointer setup scheduled differently, fn_2_689CC result copied through r0
#if NONMATCHING
void fn_2_24800(void) {
    Vec position;
    s16* location;
    s16* target;
    s32 offset;
    s32 i;
    s16 scene;

    fn_2_6ACF4();
    fn_800B0A5C_insertQueue(fn_2_71F60, 2);
    if (*(s16*)(lbl_2_bss_1A823C[0] + 0x30) == 5) {
        fn_2_72054(0, 8);
    } else {
        fn_2_72054(0, 4);
    }
    scene = *(s16*)(lbl_2_bss_1A823C[0] + 0x30);
    if (scene == 0) {
        fn_2_6ABFC(0, fn_2_4C3D8(lbl_2_bss_1A8248[0x441C]));
    } else if (scene != 4) {
        if (lbl_2_bss_1A8248[0x441C] == 3 && lbl_2_bss_1A8248[0x441E] == 1 &&
            *(s16*)(lbl_2_bss_1A8248 + 0x16C2) == 0xB && scene == 3) {
            memcpy(&position, &lbl_2_data_2EA4[*(s16*)(lbl_2_bss_1A8248 + 0x16C2)], sizeof(Vec));
            position.x += 0.3f;
            position.z -= 0.3f;
            fn_2_6AABC(0, &position);
        } else {
            fn_2_6ABFC(0, *(s16*)(lbl_2_bss_1A8248 + 0x16C2));
        }
    }
    scene = *(s16*)(lbl_2_bss_1A823C[0] + 0x30);
    if (scene == 4) {
        fn_2_72054(1, 3);
    } else if (scene == 8 || scene == 1) {
        if (lbl_2_bss_1A8248[0x442F] == 1) {
            s16 location = fn_2_689CC(1);
            *(s16*)(lbl_2_bss_1A8248 + 0x179A) = location;
            *(s16*)(lbl_2_bss_1A8248 + 0x1798) = location;
            *(s16*)(lbl_2_bss_1A8248 + 0x1796) = location;
            fn_2_6ABFC(1, location);
            fn_2_72054(1, 6);
            lbl_2_bss_1A8248[0x442F] = 1;
        }
    } else if (lbl_2_bss_1A8248[0x441C] == 5) {
        fn_2_72054(1, 0);
    } else {
        s32 pick;
        fn_2_68DAC(0, &position);
        pick = rand() % 2;
        if (position.x > 0.0f) {
            fn_2_6ABFC(1, lbl_2_data_3EEC[pick]);
            *(s16*)(lbl_2_bss_1A8248 + 0x179A) = lbl_2_data_3EEC[pick];
        } else {
            fn_2_6ABFC(1, lbl_2_data_3EF0[pick]);
            *(s16*)(lbl_2_bss_1A8248 + 0x179A) = lbl_2_data_3EF0[pick];
        }
        fn_2_72054(1, 6);
        lbl_2_bss_1A8248[0x442F] = 1;
    }
    {
        lbl_2_bss_1A824C[0][0x19782A] = 1;
        lbl_2_bss_1A824C[0][0x19782B] = 1;
        lbl_2_bss_1A824C[0][0x197832] = 1;
        for (i = 0, offset = 0, location = lbl_2_data_3ED4, target = lbl_2_data_3EE0; i < 5; i++) {
            lbl_2_bss_1A824C[0][0x19782D + i] = 1;
            if (*(s16*)(lbl_2_bss_1A823C[0] + 0x30) == 0) {
                fn_2_6ABFC(i + 2, *location);
                *(s16*)(lbl_2_bss_1A8248 + offset + 0x1872) = *location;
            }
            if (lbl_2_bss_1A824C[0][0x19782D + i] == 1) {
                if (*(s16*)(lbl_2_bss_1A823C[0] + 0x30) == 5 && lbl_2_bss_1A8248[0x4420] == i) {
                    fn_2_72054(i + 2, 8);
                    if (*(s16*)(lbl_2_bss_1A8248 + 0x16C2) == *target) {
                        fn_2_6ABFC(i + 2, *location);
                    }
                } else {
                    fn_2_72054(i + 2, 7);
                    fn_2_686D0(i + 2, 0);
                }
            } else {
                fn_2_72054(i + 2, 0);
            }
            offset += 0xD8;
            target++;
            location++;
        }
    }
    for (i = 0; i < 6; i++) {
        fn_2_6ABFC(i + 7, 0);
    }
    fn_2_904A8();
    fn_800B0A5C_insertQueue(fn_2_9257C, 2);
    fn_2_90428(0);
    fn_2_92654(0, 1);
    for (i = 0; i < 6; i++) {
        fn_2_90428(i + 1);
        if (lbl_2_bss_1A8248[0x440C + i] == 1) {
            fn_2_92654(i + 1, 2);
        }
    }
    fn_2_90428(7);
    if (lbl_2_bss_1A8248[0x440E] == 1) {
        fn_2_92654(7, 2);
    }
    if (lbl_2_bss_1A8248[0x4439] == 1) {
        fn_2_90428(8);
        fn_2_92654(8, 2);
    }
    for (i = 0; i < 6; i++) {
        fn_2_90428(i + 10);
        fn_2_90428(i + 16);
        if ((lbl_2_bss_1A8248[fn_2_4C3D8(i) * 10 + 0x40F1] == 2 || lbl_2_bss_1A8248[fn_2_4C3D8(i) * 10 + 0x40F1] == 3) &&
            lbl_2_bss_1A8248[0x441C] != i) {
            fn_2_92654(i + 10, 2);
        }
    }
    fn_2_90428(0x16);
    fn_2_92654(0x16, 2);
    fn_2_90428(0x17);
    fn_2_92654(0x17, 1);
    if (lbl_2_bss_1A8248[0x4446] == 0 && lbl_2_bss_1A8248[0x441C] != 5) {
        fn_2_90428(0x18);
        fn_2_92654(0x18, 2);
    }
    if (lbl_2_bss_1A8248[0x442A] == 1) {
        fn_2_90428(0x19);
        fn_2_92654(0x19, 1);
        fn_2_90428(0x1A);
        fn_2_92654(0x1A, 1);
        fn_2_90428(0x1B);
        fn_2_92654(0x1B, 2);
    }
    fn_2_94854(0xB);
    fn_2_9461C(0);
    fn_2_94604(1);
    fn_2_94634(1);
    fn_2_93C64();
    lbl_2_bss_1A8248[0x44F3] = 1;
    switch (*(s16*)(lbl_2_bss_1A823C[0] + 0x30)) {
    case 0:
        lbl_2_bss_1A8248[0x441B] = 1;
        break;
    }
}
#endif

// One controller entry of lbl_803C77B8 (PadState in main/file_800A7C08.h,
// which can't be included next to UnknownHomes_Static.h).
typedef struct MenuPad {
    /* 0x00 */ u16 held;
    /* 0x02 */ u16 down;
    /* 0x04 */ u16 repeat;
    /* 0x06 */ u8 pad06[0xA];
    /* 0x10 */ s8 stickX;
    /* 0x11 */ s8 stickY;
    /* 0x12 */ s8 substickX;
    /* 0x13 */ s8 substickY;
    /* 0x14 */ u8 pad14[0xC];
} MenuPad; // size: 0x20

#define MENU_PAD (((MenuPad*)&lbl_803C77B8)[(s8)lbl_2_bss_1A824C[0][0x197863]])

extern void fn_2_46C2C(s32 unused, Vec* src);
extern void fn_2_3F66C(void);
extern void fn_2_3FA14(void);

// Debug menu: unlock every character of one team.
static inline void fn_2_1D440_unlockTeam(s32 team) {
    s32 i;
    for (i = 0; i < 51; i++) {
        u8* record = lbl_2_bss_1A8248 + i * 10;
        if (record[0x40F0] == team && (record[0x40F1] == 1 || record[0x40F1] == 0)) {
            if (lbl_2_bss_1A8248[0x441C] == 5) {
                if (record[0x40F2] == 1) {
                    record[0x40F1] = 3;
                } else {
                    record[0x40F1] = 0;
                }
            } else {
                record[0x40F1] = 0;
            }
        }
    }
    lbl_2_bss_1A8248[0x440C + team] = 1;
    if (!(lbl_2_bss_1A8248[0x4428] & (1 << team))) {
        lbl_2_bss_1A8248[0x4423]++;
        lbl_2_bss_1A8248[0x4428] |= 1 << team;
    }
}

// fn_2_1D440, size:0x2ACC
// NONMATCHING 98%: register allocation and a few compare forms (cmpw vs cmpwi) differ
#if NONMATCHING
void fn_2_1D440(void) {
    u8* queue = lbl_803CC1B8[0];
    s32 i;

    switch (*(s8*)(queue + 0x28)) {
    case 0:
        MENU_INPUT_CONTEXT->secondarySelection = 0;
        MENU_INPUT_CONTEXT->selection = 0;
        queue[0x28] = 1;
        break;
    case 1:
        fn_2_1FFC4(19);
        for (i = 0; i < 19; i++) {
            switch (i) {
            case 0:
                if (MENU_INPUT_CONTEXT->selection == i && ((MENU_PAD.down & 0x100) || MENU_PAD.substickY > 0x32)) {
                    queue[0x28] = 13;
                }
                break;
            case 1:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 repeat = MENU_PAD.repeat;
                    if (repeat & 1) {
                        if (*(s16*)(lbl_2_bss_1A8248 + 0x43BC) > 0) {
                            fn_80062890(0x37);
                            fn_2_46D34(-1);
                        } else {
                            fn_80062890(0x37);
                            *(s16*)(lbl_2_bss_1A8248 + 0x43BC) = 999;
                        }
                        lbl_2_bss_1A8234[0][0x162933] = 1;
                    } else if (repeat & 2) {
                        if (*(s16*)(lbl_2_bss_1A8248 + 0x43BC) < 999) {
                            fn_80062890(0x37);
                            fn_2_46D34(1);
                        } else {
                            fn_80062890(0x37);
                            *(s16*)(lbl_2_bss_1A8248 + 0x43BC) = 0;
                        }
                        lbl_2_bss_1A8234[0][0x162979] = 1;
                    } else if (repeat & 0x40) {
                        fn_80062890(0x37);
                        *(s16*)(lbl_2_bss_1A8248 + 0x43BC) = 0;
                    } else if (repeat & 0x20) {
                        fn_80062890(0x37);
                        *(s16*)(lbl_2_bss_1A8248 + 0x43BC) = 999;
                    }
                }
                break;
            case 2:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 3)) {
                    lbl_2_bss_1A8248[0x44F2] ^= 1;
                }
                break;
            case 3:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 repeat = MENU_PAD.repeat;
                    if (repeat & 1) {
                        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) > 0) {
                            (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C))--;
                        } else {
                            *(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) = 999;
                        }
                    } else if (repeat & 2) {
                        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) < 999) {
                            (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C))++;
                        } else {
                            *(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) = 0;
                        }
                    } else if (repeat & 0x40) {
                        *(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) = 0;
                    } else if (repeat & 0x20) {
                        *(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) = 999;
                    }
                    if ((MENU_PAD.repeat & 0x100) && *(s16*)(lbl_2_bss_1A824C[0] + 0x19773E) == 0) {
                        fn_2_46D34(*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C));
                        ((u8*)fn_800B0A5C_insertQueue(fn_2_3FA14, 2))[0x28] = 0;
                        *(s16*)(queue + 0x10) = 0;
                        *(s16*)(lbl_2_bss_1A824C[0] + 0x19773E) = 1;
                    }
                }
                break;
            case 4:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 repeat = MENU_PAD.repeat;
                    if (repeat & 1) {
                        // NOTE: the original tests and decrements 0x19779C here but
                        // increments 0x19779E below.
                        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) > 0) {
                            (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C))--;
                        } else {
                            *(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) = 999;
                        }
                    } else if (repeat & 2) {
                        if (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779C) < 999) {
                            (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779E))++;
                        } else {
                            *(s16*)(lbl_2_bss_1A824C[0] + 0x19779E) = 0;
                        }
                    } else if (repeat & 0x40) {
                        *(s16*)(lbl_2_bss_1A824C[0] + 0x19779E) = 0;
                    } else if (repeat & 0x20) {
                        *(s16*)(lbl_2_bss_1A824C[0] + 0x19779E) = 999;
                    }
                    if ((MENU_PAD.repeat & 0x100) && *(s16*)(lbl_2_bss_1A824C[0] + 0x19773E) == 0) {
                        fn_2_46D34(-*(s16*)(lbl_2_bss_1A824C[0] + 0x19779E));
                        if (*(s16*)(lbl_2_bss_1A8248 + 0x43BE) > 0) {
                            ((u8*)fn_800B0A5C_insertQueue(fn_2_3F66C, 2))[0x28] = 0;
                            *(s16*)(queue + 0x10) = 0;
                        }
                        *(s16*)(lbl_2_bss_1A824C[0] + 0x19773E) = 1;
                    }
                }
                break;
            case 5:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    queue[0x28] = 2;
                }
                break;
            case 6:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    queue[0x28] = 3;
                }
                break;
            case 7:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A824C[0][0x19784A] = 1;
                    lbl_2_bss_1A824C[0][0x197846] = 1;
                    lbl_2_bss_1A824C[0][0x197847] = 0;
                    queue[0x28] = 4;
                }
                break;
            case 8:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A824C[0][0x19784A] = 1;
                    lbl_2_bss_1A824C[0][0x197846] = 0;
                    lbl_2_bss_1A824C[0][0x197845] = 1;
                    queue[0x28] = 5;
                }
                break;
            case 9:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A824C[0][0x19784A] = 1;
                    lbl_2_bss_1A824C[0][0x197846] = 2;
                    queue[0x28] = 6;
                }
                break;
            case 10:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    queue[0x28] = 7;
                }
                break;
            case 11:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x103)) {
                    s32 j;
                    lbl_2_bss_1A8248[0x441A] = 1;
                    lbl_2_bss_1A8248[0x4439] = 0;
                    *(s16*)(lbl_2_bss_1A8248 + 0x16C2) = lbl_2_data_3EC8[5];
                    fn_2_6ABFC(0, *(s16*)(lbl_2_bss_1A8248 + 0x16C2));
                    for (j = 0; j < 5; j++) {
                        fn_2_1C714(j);
                    }
                }
                break;
            case 12:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x4415] = (lbl_2_bss_1A8248[0x4415] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x4415] = (lbl_2_bss_1A8248[0x4415] + 1) % 4;
                    }
                }
                break;
            case 13:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 0x103) {
                        fn_2_683EC();
                    } else if (down & 0x400) {
                        fn_2_68308();
                    } else if (down & 0x800) {
                        fn_2_6832C();
                    }
                }
                break;
            case 14:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 repeat = MENU_PAD.repeat;
                    if (repeat & 0x800) {
                        lbl_2_bss_1A824C[0][0x19785C] = ((s8)lbl_2_bss_1A824C[0][0x19785C] + 1) % 2;
                    } else if (repeat & 0x400) {
                        lbl_2_bss_1A824C[0][0x19785C] = ((s8)lbl_2_bss_1A824C[0][0x19785C] + 1) % 2;
                    }
                    if (MENU_PAD.down & 0x100) {
                        Vec zero;
                        zero.z = 0.0f;
                        zero.y = 0.0f;
                        zero.x = 0.0f;
                        fn_2_46C2C(0, &zero);
                    }
                }
                break;
            case 15:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    queue[0x28] = 9;
                }
                break;
            case 16:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    queue[0x28] = 11;
                }
                break;
            case 17:
                if (MENU_INPUT_CONTEXT->selection == i && (MENU_PAD.down & 0x102)) {
                    s32 j;
                    for (j = 0; j < 20; j++) {
                        lbl_2_bss_1A8248[0x43C2 + j] = 1;
                    }
                }
                break;
            case 18:
                if (MENU_INPUT_CONTEXT->selection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x44F8] = 0;
                        lbl_2_bss_1A8248[0x44F9] = 0;
                        lbl_2_bss_1A8248[0x44FA] = 0;
                        lbl_2_bss_1A8248[0x44FB] = 0;
                        lbl_2_bss_1A8248[0x44FC] = 0;
                        lbl_2_bss_1A8248[0x44FD] = 0;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x44F8] = 3;
                        lbl_2_bss_1A8248[0x44F9] = 3;
                        lbl_2_bss_1A8248[0x44FA] = 3;
                        lbl_2_bss_1A8248[0x44FB] = 3;
                        lbl_2_bss_1A8248[0x44FC] = 3;
                        lbl_2_bss_1A8248[0x44FD] = 3;
                    }
                }
                break;
            }
        }
        if ((MENU_PAD.down & 0x200) || MENU_PAD.substickY > 0x32) {
            queue[0x28] = 13;
        }
        break;
    case 2:
        fn_2_1FF14(7);
        for (i = 0; i < 7; i++) {
            switch (i) {
            case 0:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x300)) {
                    MENU_INPUT_CONTEXT->secondarySelection = 0;
                    queue[0x28] = 1;
                }
                break;
            case 1:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1C714(0);
                }
                break;
            case 2:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1C714(1);
                }
                break;
            case 3:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1C714(2);
                }
                break;
            case 4:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1C714(3);
                }
                break;
            case 5:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1C714(4);
                }
                break;
            case 6:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1C714(5);
                }
                break;
            }
        }
        if (MENU_PAD.down & 0x201) {
            MENU_INPUT_CONTEXT->secondarySelection = 0;
            queue[0x28] = 1;
        } else if (MENU_PAD.substickY > 0x32) {
            queue[0x28] = 13;
        }
        break;
    case 3:
        fn_2_1FF14(6);
        for (i = 0; i < 6; i++) {
            switch (i) {
            case 0:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x300)) {
                    MENU_INPUT_CONTEXT->secondarySelection = 0;
                    queue[0x28] = 1;
                }
                break;
            case 1:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1D440_unlockTeam(0);
                }
                break;
            case 2:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1D440_unlockTeam(1);
                }
                break;
            case 3:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1D440_unlockTeam(2);
                }
                break;
            case 4:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1D440_unlockTeam(3);
                }
                break;
            case 5:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x100)) {
                    fn_2_1D440_unlockTeam(4);
                }
                break;
            }
        }
        if (MENU_PAD.down & 0x60) {
            fn_2_1D440_unlockTeam(0);
            fn_2_1D440_unlockTeam(1);
            fn_2_1D440_unlockTeam(2);
            fn_2_1D440_unlockTeam(3);
            fn_2_1D440_unlockTeam(4);
        }
        if (MENU_PAD.down & 0x201) {
            MENU_INPUT_CONTEXT->secondarySelection = 0;
            queue[0x28] = 1;
        } else if (MENU_PAD.substickY > 0x32) {
            queue[0x28] = 13;
        }
        break;
    case 4:
        fn_2_1FF14(1);
        if (MENU_INPUT_CONTEXT->secondarySelection == 0) {
            if (MENU_PAD.down & 0x10) {
                lbl_2_bss_1A824C[0][0x197847] ^= 1;
            }
            if (MENU_PAD.down & 0x200) {
                lbl_2_bss_1A824C[0][0x19784A] = 0;
                lbl_2_bss_1A824C[0][0x197846] = 0;
                MENU_INPUT_CONTEXT->secondarySelection = 0;
                lbl_2_bss_1A824C[0][0x197847] = 0;
                fn_2_6ABFC(0, *(s16*)(lbl_2_bss_1A8248 + 0x16C2));
                queue[0x28] = 1;
            }
            if (MENU_PAD.down & 0x100) {
                Vec position;
                fn_2_68DAC(0, &position);
                (*(s16*)(lbl_2_bss_1A824C[0] + 0x19779A))++;
            }
            if (MENU_PAD.down & 0x1000) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x19779A) = 0;
            }
        }
        break;
    case 5:
        fn_2_1FF14(1);
        if (MENU_INPUT_CONTEXT->secondarySelection == 0) {
            MenuPad* pad = &MENU_PAD;
            u16 down = pad->down;
            if ((down & 1) && (pad->held & 0x100)) {
                lbl_2_bss_1A824C[0][0x197849] = (lbl_2_bss_1A824C[0][0x197849] + 19) % 20;
            } else if ((down & 2) && (pad->held & 0x100)) {
                lbl_2_bss_1A824C[0][0x197849] = (lbl_2_bss_1A824C[0][0x197849] + 1) % 20;
            }
            down = MENU_PAD.down;
            if (down & 0x200) {
                lbl_2_bss_1A824C[0][0x19784A] = 0;
                lbl_2_bss_1A824C[0][0x197846] = 0;
                MENU_INPUT_CONTEXT->secondarySelection = 0;
                lbl_2_bss_1A824C[0][0x197845] = 0;
                queue[0x28] = 1;
            } else if (down & 0x1000) {
                fn_2_93C64();
            }
        }
        break;
    case 6:
        fn_2_1FF14(1);
        if (MENU_INPUT_CONTEXT->secondarySelection == 0) {
            MenuPad* pad = &MENU_PAD;
            u16 down = pad->down;
            u16 repeat;
            if (down & 0x200) {
                lbl_2_bss_1A824C[0][0x19784A] = 0;
                lbl_2_bss_1A824C[0][0x197846] = 0;
                MENU_INPUT_CONTEXT->secondarySelection = 0;
                fn_2_6ABFC(0, *(s16*)(lbl_2_bss_1A8248 + 0x16C2));
                queue[0x28] = 1;
            } else if ((down & 0x40) && (pad->held & 0x100)) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x1972BE) = (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972BE) + 28) % 29;
            } else if ((down & 0x20) && (pad->held & 0x100)) {
                *(s16*)(lbl_2_bss_1A824C[0] + 0x1972BE) = (*(s16*)(lbl_2_bss_1A824C[0] + 0x1972BE) + 1) % 29;
            } else {
                repeat = pad->repeat;
                if (repeat & 0x800) {
                    *(f32*)(lbl_2_bss_1A8248 + *(s16*)(lbl_2_bss_1A824C[0] + 0x1972BE) * 0xBC + 0x2208) -= 0.1f;
                } else if (repeat & 0x400) {
                    *(f32*)(lbl_2_bss_1A8248 + *(s16*)(lbl_2_bss_1A824C[0] + 0x1972BE) * 0xBC + 0x2208) += 0.1f;
                }
            }
        }
        break;
    case 7:
        fn_2_1FF14(12);
        for (i = 0; i < 12; i++) {
            switch (i) {
            case 0:
                if (MENU_INPUT_CONTEXT->secondarySelection == i && (MENU_PAD.down & 0x301)) {
                    queue[0x28] = 1;
                }
                break;
            case 1:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x443B] = ((s8)lbl_2_bss_1A8248[0x443B] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x443B] = ((s8)lbl_2_bss_1A8248[0x443B] + 1) % 4;
                    }
                }
                break;
            case 2:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x443C] = ((s8)lbl_2_bss_1A8248[0x443C] + 1) % 2;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x443C] = ((s8)lbl_2_bss_1A8248[0x443C] + 1) % 2;
                    }
                }
                break;
            case 3:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x443D] = ((s8)lbl_2_bss_1A8248[0x443D] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x443D] = ((s8)lbl_2_bss_1A8248[0x443D] + 1) % 4;
                    }
                }
                break;
            case 4:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x443E] = ((s8)lbl_2_bss_1A8248[0x443E] + 1) % 2;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x443E] = ((s8)lbl_2_bss_1A8248[0x443E] + 1) % 2;
                    }
                }
                break;
            case 5:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x443F] = ((s8)lbl_2_bss_1A8248[0x443F] + 2) % 3;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x443F] = ((s8)lbl_2_bss_1A8248[0x443F] + 1) % 3;
                    }
                }
                break;
            case 6:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x4437] = ((s8)lbl_2_bss_1A8248[0x4437] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x4437] = ((s8)lbl_2_bss_1A8248[0x4437] + 1) % 4;
                    }
                }
                break;
            case 7:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x4440] = ((s8)lbl_2_bss_1A8248[0x4440] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x4440] = ((s8)lbl_2_bss_1A8248[0x4440] + 1) % 4;
                    }
                }
                break;
            case 8:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x4441] = ((s8)lbl_2_bss_1A8248[0x4441] + 1) % 2;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x4441] = ((s8)lbl_2_bss_1A8248[0x4441] + 1) % 2;
                    }
                }
                break;
            case 9:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x4442] = ((s8)lbl_2_bss_1A8248[0x4442] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x4442] = ((s8)lbl_2_bss_1A8248[0x4442] + 1) % 4;
                    }
                }
                break;
            case 10:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x4443] = ((s8)lbl_2_bss_1A8248[0x4443] + 1) % 2;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x4443] = ((s8)lbl_2_bss_1A8248[0x4443] + 1) % 2;
                    }
                }
                break;
            case 11:
                if (MENU_INPUT_CONTEXT->secondarySelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 1) {
                        lbl_2_bss_1A8248[0x443A] = (lbl_2_bss_1A8248[0x443A] + 3) % 4;
                    } else if (down & 2) {
                        lbl_2_bss_1A8248[0x443A] = (lbl_2_bss_1A8248[0x443A] + 1) % 4;
                    }
                }
                break;
            }
        }
        if (MENU_PAD.down & 0x300) {
            MENU_INPUT_CONTEXT->secondarySelection = 0;
            queue[0x28] = 1;
        } else if (MENU_PAD.substickY > 0x32) {
            queue[0x28] = 13;
        }
        break;
    case 9:
        ((u8*)fn_800B0A5C_insertQueue(fn_2_1CF94, 2))[0x28] = 0;
        *(s16*)(queue + 0x10) = 0;
        queue[0x28] = 10;
        break;
    case 10:
        if (*(s16*)(queue + 0x10) == 1) {
            queue[0x28] = 1;
        }
        break;
    case 11:
        ((u8*)fn_800B0A5C_insertQueue(fn_2_1C860, 2))[0x28] = 0;
        *(s16*)(queue + 0x10) = 0;
        queue[0x28] = 12;
        break;
    case 12:
        if (*(s16*)(queue + 0x10) == 1) {
            queue[0x28] = 1;
        }
        break;
    case 13: {
        u8* parent = *(u8**)(queue + 0xC);
        *(s16*)(parent + 0x10) = 1;
        fn_800B0A14_removeQueue(parent);
        queue[0x28] = 0;
        break;
    }
    }
}
#endif
