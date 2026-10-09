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
