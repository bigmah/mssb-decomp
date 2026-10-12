// Translation unit 0x0640: .text 0x19F2C..0x1A4C8, .data 0x2B78..0x2E40 (formerly part of
// the auto_00_000194BC_text split). Its .data starts with a debug-menu header copy, so it
// is a unit of its own after the options menu (rep_05F0); whether rep_0690/rep_06E0 hold
// some of these functions is unknown. Functions in reverse address order (-inline deferred).
#define REP_HEADER_FN repHeader_menus_0640
#include "header_rep_inline.h"
#include "menus/menu_work.h"
#include "main/file_80011640.h"
#include "menus/rep_0640.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "musyx/musyx.h"
#include "menus/auto_00_00000D08_text.h"

// .data: header statics (unreferenced copies), then the copy-clear colour.
#include "menus/debug_menu_data.h"

GXColor lbl_2_data_2E3C = {0, 0, 0, 0}; // EFB clear colour (fn_2_1A1B4)

extern MenuFlags* lbl_2_bss_1A823C[];
extern MenuCtx* lbl_2_bss_1A8248[];
extern MenuData* lbl_2_bss_1A824C[];
extern void fn_2_4AB1C(void);
extern s32 fn_2_46D00(void);
extern s32 lbl_2_bss_1598;
extern u8* lbl_803CC1B8[];
extern u8 lbl_8037169C[];
extern void* memset(void*, int, unsigned long);

// fn_2_1A420, size:0xA8
s32 fn_2_1A420(void) {
    s32 result = 0;
    if (lbl_2_bss_1A823C[0]->mode == 3) {
        fn_2_4AB1C();
        if (lbl_2_bss_1A824C[0]->_197843 == 0) {
            if (lbl_2_bss_1A8248[0]->_441C == 5) {
                if (fn_2_46D00() != 0) {
                    result = 1;
                }
            } else if (lbl_2_bss_1A8248[0]->_4426 & 0x20) {
                result = 1;
            }
        }
    }
    return !!result;
}

// fn_2_1A2AC, size:0x174
void fn_2_1A2AC(void) {
    MenuScreenTask* object = (MenuScreenTask*)lbl_803CC1B8[0];
    switch (object->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_19783E = 0;
        changeScene(1, 6);
        object->step = 1;
        break;
    case 1:
        if (lbl_8037169C[0x12] != 0) {
            object->step = 2;
        }
        break;
    case 2: {
        u8* pad = (u8*)&lbl_803C77B8;
        pad += lbl_2_bss_1A824C[0]->port * 0x20;
        if (*(u16*)(pad + 2) & 0x100) {
            changeScene(3, 6);
            object->step = 3;
        }
        break;
    }
    case 3:
        if (lbl_8037169C[0x13] != 0) {
            object->step = 4;
        }
        break;
    case 4: {
        MenuScreenTask* queue = object->parent;
        queue->signal = 1;
        fn_800B0A14_removeQueue(queue);
        object->step = 0;
        break;
    }
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        MenuScreenTask* queue = ((MenuScreenTask*)lbl_803CC1B8[0])->parent;
        queue->signal = 1;
        fn_800B0A14_removeQueue(queue);
        object->step = 0;
    }
}

// fn_2_1A1B4, size:0xF8
void fn_2_1A1B4(void) {
    MenuScreenTask* object = (MenuScreenTask*)lbl_803CC1B8[0];
    switch (lbl_2_bss_1598) {
    case 0: {
        GXColor clear;
        fn_2_19F2C();
        object->signal = 0;
        clear = lbl_2_data_2E3C;
        GXSetCopyClear(clear, 0xFFFFFF);
        lbl_2_bss_1598 = 1;
        break;
    }
    case 1:
        sndVolume(0x7F, 10, 0xFF);
        lbl_2_bss_1598 = 4;
        break;
    case 2:
        lbl_2_bss_1598 = 4;
        break;
    case 4:
        changeScene(3, 6);
        if (g_d_GameSettings.GameModeSelected != 5) {
            fn_2_11A0(5);
        } else {
            fn_2_11A0(0x10);
        }
        break;
    }
}

// Words from CharMgr.trailLayout up to _3070 (layout/geo/tex pointers of the loaded models).
enum { CHARMGR_RES_WORDS = (offsetof(CharMgr, _3070) - offsetof(CharMgr, trailLayout)) / 4 };

// fn_2_19F2C, size:0x288
void fn_2_19F2C(void) {
    s32 i;
    lbl_8036E548._0000 = 0;
    lbl_8036E548.trailFile = 0;
    for (i = 0; i < CHARMGR_RES_WORDS; i++) {
        *(u32*)((u8*)&lbl_8036E548 + offsetof(CharMgr, trailLayout) + i * 4) = 0;
    }
    lbl_8036E548._0004[1] = 0;
    for (i = 0; i < 0x15; i++) {
        lbl_8036E548._000C[i] = 0;
    }
    lbl_8036E548.slots = 0;
    lbl_8036E548.slots64 = 0;
    lbl_8036E548.slots68 = 0;
    lbl_8036E548.slots6C = 0;
    lbl_8036E548._0070 = 0;
    lbl_8036E548._0074 = 0;
    lbl_8036E548._0078 = 0;
    lbl_8036E548.lights[0] = 0;
    lbl_8036E548.lights[1] = 0;
    lbl_8036E548.lights[2] = 0;
    lbl_8036E548.lights[3] = 0;
    for (i = 0; i < 0x15; i++) {
        lbl_8036E548._00BC[i] = 0;
    }
    lbl_8036E548._0110 = 0;
    for (i = 0; i < 0xD; i++) {
        memset(&lbl_8036E548.actors[i], 0, sizeof(CharActor));
    }
    lbl_8036E548.stadiumFiles = 0;
    lbl_8036E548._2C88 = 0;
    lbl_8036E548.fileBuf = 0;
    for (i = 0; i < 0x10; i++) {
        lbl_8036E548.animBufs[i] = 0;
    }
    lbl_8036E548.trail = 0;
    lbl_8036E548.trail2 = 0;
    lbl_8036E548._2D98 = 0;
    lbl_8036E548._3070 = 0;
    lbl_8036E548._3074 = 0;
}
