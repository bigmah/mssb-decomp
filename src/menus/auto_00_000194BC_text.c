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
extern u8 lbl_8037169C[];
extern void initializeUnknown(void);
extern void fn_80021228(u8);
extern void fn_80062A74(void);
extern void fn_800A97EC(s32, u32, u8);

// fn_2_195DC, size:0x19C
void fn_2_195DC(void) {
    u8* menu = lbl_2_bss_1033C;
    switch (*(s16*)(menu + 2)) {
    case 0:
        if (*(s8*)(menu + 6) != 0 && lbl_800EF808[0x398] == 0) {
            initializeUnknown();
            fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
        } else if (*(s8*)(menu + 6) == 0 && lbl_800EF808[0x398] != 0) {
            fn_80062A74();
        }
        lbl_800EF808[0x398] = menu[6];
        lbl_2_bss_1033C[0xD] = menu[6];
        break;
    case 1:
        if (*(s8*)(menu + 7) != lbl_800EF808[0x396]) {
            fn_80062A74();
            if (*(s8*)(menu + 7) == 1) {
                lbl_800EF808[0x396] = 1;
            } else if (*(s8*)(menu + 7) == 0) {
                lbl_800EF808[0x396] = 0;
            } else {
                lbl_800EF808[0x396] = 2;
            }
            fn_80021228(lbl_800EF808[0x396]);
            fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
            lbl_800EF808[0x396] = menu[7];
        }
        break;
    case 2:
        if (*(s8*)(menu + 8) != 0) {
            lbl_80366158[0x1F] = 1;
            fn_800A97EC(0, 0x32, 1);
        } else {
            lbl_80366158[0x1F] = 0;
        }
        break;
    }
    lbl_2_bss_1033C[0xB] = 0;
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
