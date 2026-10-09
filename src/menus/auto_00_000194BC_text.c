#include "menus/auto_00_000194BC_text.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "musyx/musyx.h"

extern u8 lbl_2_bss_1033C[];
extern u8 lbl_800EF808[];
extern u8 lbl_80366158[];
extern u8 lbl_800E8754[];
extern void fn_80021204(void);
extern s32 fn_8003AE70(s32 selector);

// fn_2_194BC, size:0x2C
void fn_2_194BC(u8* object) {
    void* p = *(void**)(object + 0x70);
    if (p != NULL) {
        fn_800B9AA8(p);
    }
}

// fn_2_194E8, size:0x38
void fn_2_194E8(void) {
    fn_80021204();
    lbl_800E8754[0x25] = lbl_80366158[0x1F];
}

// fn_2_19554, size:0x84
s8 fn_2_19554(void) {
    s32 result = 0;
    if (lbl_800EF808[0x398] != fn_8003AE70(0) || lbl_800EF808[0x397] != fn_8003AE70(1) || lbl_80366158[0x1F] != fn_8003AE70(2)) {
        result = 1;
    }
    return result;
}

// fn_2_195D8, size:0x4
void fn_2_195D8(void) {
}

extern u8* lbl_2_bss_1A823C[];
extern u8* lbl_2_bss_1A8248[];
extern u8* lbl_2_bss_1A824C[];
extern void fn_2_4AB1C(void);
extern s32 fn_2_46D00(void);
extern s32 lbl_2_bss_1598;
extern GXColor lbl_2_data_2E3C;
extern u8* lbl_803CC1B8[];
extern void fn_2_11A0(s32);
extern void fn_2_19F2C(void);

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
