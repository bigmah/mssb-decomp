// Translation unit 0x0640: .text 0x19F2C..0x1A4C8, .data 0x2B78..0x2E40 (formerly part of
// the auto_00_000194BC_text split). Its .data starts with a debug-menu header copy, so it
// is a unit of its own after the options menu (rep_05F0); whether rep_0690/rep_06E0 hold
// some of these functions is unknown. Functions in reverse address order (-inline deferred).
#define REP_HEADER_FN repHeader_menus_0640
#include "header_rep_inline.h"
#include "menus/rep_0640.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "musyx/musyx.h"
#include "menus/auto_00_00000D08_text.h"

// .data: header statics (unreferenced copies), then the copy-clear colour.
#include "menus/debug_menu_data.h"

GXColor lbl_2_data_2E3C = {0, 0, 0, 0}; // EFB clear colour (fn_2_1A1B4)

extern u8* lbl_2_bss_1A823C[];
extern u8* lbl_2_bss_1A8248[];
extern u8* lbl_2_bss_1A824C[];
extern void fn_2_4AB1C(void);
extern s32 fn_2_46D00(void);
extern s32 lbl_2_bss_1598;
extern u8* lbl_803CC1B8[];
extern u8 lbl_8037169C[];
extern u8 lbl_8036E548[];
extern void* memset(void*, int, unsigned long);

// fn_2_1A420, size:0xA8
s32 fn_2_1A420(void) {
    s32 result = 0;
    if (*(s16*)(lbl_2_bss_1A823C[0] + 0x30) == 3) {
        fn_2_4AB1C();
        if (*(s8*)(lbl_2_bss_1A824C[0] + 0x197843) == 0) {
            if (lbl_2_bss_1A8248[0][0x441C] == 5) {
                if (fn_2_46D00() != 0) {
                    result = 1;
                }
            } else if (lbl_2_bss_1A8248[0][0x4426] & 0x20) {
                result = 1;
            }
        }
    }
    return !!result;
}

// fn_2_1A2AC, size:0x174
void fn_2_1A2AC(void) {
    u8* object = lbl_803CC1B8[0];
    switch (*(s8*)(object + 0x28)) {
    case 0:
        *(s8*)(lbl_2_bss_1A824C[0] + 0x19783E) = 0;
        changeScene(1, 6);
        object[0x28] = 1;
        break;
    case 1:
        if (lbl_8037169C[0x12] != 0) {
            object[0x28] = 2;
        }
        break;
    case 2: {
        u8* pad = (u8*)&lbl_803C77B8;
        pad += *(s8*)(lbl_2_bss_1A824C[0] + 0x197863) * 0x20;
        if (*(u16*)(pad + 2) & 0x100) {
            changeScene(3, 6);
            object[0x28] = 3;
        }
        break;
    }
    case 3:
        if (lbl_8037169C[0x13] != 0) {
            object[0x28] = 4;
        }
        break;
    case 4: {
        u8* queue = *(u8**)(object + 0xC);
        *(s16*)(queue + 0x10) = 1;
        fn_800B0A14_removeQueue(queue);
        object[0x28] = 0;
        break;
    }
    }
    if (lbl_2_bss_1A824C[0][0x19783F] == 1) {
        u8* queue = *(u8**)(lbl_803CC1B8[0] + 0xC);
        *(s16*)(queue + 0x10) = 1;
        fn_800B0A14_removeQueue(queue);
        object[0x28] = 0;
    }
}

// fn_2_1A1B4, size:0xF8
void fn_2_1A1B4(void) {
    u8* object = lbl_803CC1B8[0];
    switch (lbl_2_bss_1598) {
    case 0: {
        GXColor clear;
        fn_2_19F2C();
        *(s16*)(object + 0x10) = 0;
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

// fn_2_19F2C, size:0x288
void fn_2_19F2C(void) {
    s32 i;
    *(s32*)(lbl_8036E548 + 0) = 0;
    *(s32*)(lbl_8036E548 + 0x2D9C) = 0;
    for (i = 0; i < 0xB4; i++) {
        *(s32*)(lbl_8036E548 + 0x2DA0 + i * 4) = 0;
    }
    *(s32*)(lbl_8036E548 + 8) = 0;
    for (i = 0; i < 0x15; i++) {
        *(s32*)(lbl_8036E548 + 0xC + i * 4) = 0;
    }
    *(s32*)(lbl_8036E548 + 0x60) = 0;
    *(s32*)(lbl_8036E548 + 0x64) = 0;
    *(s32*)(lbl_8036E548 + 0x68) = 0;
    *(s32*)(lbl_8036E548 + 0x6C) = 0;
    *(s32*)(lbl_8036E548 + 0x70) = 0;
    *(s32*)(lbl_8036E548 + 0x74) = 0;
    *(s32*)(lbl_8036E548 + 0x78) = 0;
    *(s32*)(lbl_8036E548 + 0xAC) = 0;
    *(s32*)(lbl_8036E548 + 0xB0) = 0;
    *(s32*)(lbl_8036E548 + 0xB4) = 0;
    *(s32*)(lbl_8036E548 + 0xB8) = 0;
    for (i = 0; i < 0x15; i++) {
        *(s32*)(lbl_8036E548 + 0xBC + i * 4) = 0;
    }
    *(s32*)(lbl_8036E548 + 0x110) = 0;
    for (i = 0; i < 0xD; i++) {
        memset(lbl_8036E548 + 0xC04 + i * 0x27C, 0, 0x27C);
    }
    *(s32*)(lbl_8036E548 + 0x2C84) = 0;
    *(s32*)(lbl_8036E548 + 0x2C88) = 0;
    *(s32*)(lbl_8036E548 + 0x2C8C) = 0;
    for (i = 0; i < 0x10; i++) {
        *(s32*)(lbl_8036E548 + 0x2CAC + i * 4) = 0;
    }
    *(s32*)(lbl_8036E548 + 0x2D90) = 0;
    *(s32*)(lbl_8036E548 + 0x2D94) = 0;
    *(s32*)(lbl_8036E548 + 0x2D98) = 0;
    *(s32*)(lbl_8036E548 + 0x3070) = 0;
    *(s32*)(lbl_8036E548 + 0x3074) = 0;
}
