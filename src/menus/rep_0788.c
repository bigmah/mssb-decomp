#include "menus/rep_0788.h"
#include "Dolphin/gx.h"

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
extern u8* lbl_2_bss_1A8248[];
extern u8 lbl_8036E548[];
extern void fn_2_68E68(void);
extern void fn_2_8FD14(void);
extern void fn_2_8AEE0(void);
extern void fn_2_47FF8(void);
extern void fn_2_47CFC(void);

// fn_2_2025C, size:0xCC
void fn_2_2025C(void) {
    u8* menu = lbl_2_bss_1A8248[0];
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
            if (lbl_2_bss_1A8248[0][0x44F2] != 4) {
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
    u8* menu = lbl_2_bss_1A8248[0];
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
            (u32)lbl_2_bss_1A8248[0][0x441C] << 16;
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
            (u32)lbl_2_bss_1A8248[0][0x441C] << 16;
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
        if ((s32)lbl_2_bss_1A8248[0][0x43C2 + item->index] == 1) {
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
        fn_800363D8(menu, item->offset, 1, 0x83, lbl_2_data_38C0[lbl_2_bss_1A8248[0][0x441C]]);
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
        item->unk14 = fn_8000F988(menu, item->offset, item->unk10, 4, lbl_2_bss_1A8248[0][0x441C] + 0x30C, 0);
        item->state = 38;
        break;
    }
    case 2: {
        u8* object;
        ((void (*)(s16, s32, s32))fn_8000FE08)(item->unk14, 4, lbl_2_bss_1A8248[0][0x441C] + 0x30C);
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
        fn_800363D8(menu, item->offset, 1, 6, lbl_2_bss_1A8248[0][0x4415]);
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
        if ((s32)lbl_2_bss_1A8248[0][item->index + 0x43C2] == 1) {
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
        if ((s32)lbl_2_bss_1A8248[0][item->index + 0x43C2] == 1) {
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
        if ((s32)lbl_2_bss_1A8248[0][item->index + 0x43C2] == 1) {
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
            if (lbl_2_bss_1A8248[0][0x4446] != 0) {
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

extern u8 lbl_80109AE8[];

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
        if (*(s16*)(lbl_80109AE8 + *(s16*)(ctx + 0x7706) * 0x64 + index * 10) != -1) {
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
        if ((s8)lbl_2_bss_1A8248[0][0x444B] == -1) {
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
        if ((s8)lbl_2_bss_1A8248[0][0x444C] == -1) {
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
        s32 value = (s8)lbl_2_bss_1A8248[0][0x444B];
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
        fn_800363D8(menu, item->offset, 4, 0x64, *(s8*)(lbl_2_bss_1A8248[0] + 0x444B));
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
        if ((s32)lbl_2_bss_1A8248[0][index + sel + 0x43C2] == 1) {
            s32 k = index + sel;
            if (lbl_2_data_373C[k] == 0) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else if (*(s8*)(lbl_2_bss_1A8248[0] + 0x444B) == k) {
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
        if ((s32)lbl_2_bss_1A8248[0][index + sel + 0x43C2] == 1) {
            s32 k = index + sel;
            if (lbl_2_data_373C[k] == 0) {
                u8* object = lbl_80371C30[menu->firstIndex + item->offset].object;
                *(u32*)(object + 0x54) |= 2;
                lbl_80371C30[menu->firstIndex + item->offset].object[0x68] = 1;
            } else if (*(s8*)(lbl_2_bss_1A8248[0] + 0x444B) == k) {
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
        s32 flag = lbl_2_bss_1A8248[0][id + 0x43D6];
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
        s32 flag = lbl_2_bss_1A8248[0][id + 0x43D6];
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
