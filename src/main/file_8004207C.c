#include "main/file_8004207C.h"

// .text:0x8004207C size:0x51C
void capApplicationFunction(void) {
    return;
}

// .text:0x80042598 size:0x144
void fn_80042598(void) {
    return;
}

// .text:0x800426DC size:0x514
void transferStatsToInMemRoster(void) {
    return;
}

// .text:0x80042BF0 size:0x54
void randRange_FUN_80042bf0(void) {
    return;
}

// .text:0x80042C44 size:0xF4
void sndFXRelated(void) {
    return;
}

// .text:0x80042D38 size:0x30
void fn_80042D38(void) {
    return;
}

// .text:0x80042D68 size:0x40
void fn_80042D68(void) {
    return;
}

// .text:0x80042DA8 size:0x40
void fn_80042DA8(void) {
    return;
}

// .text:0x80042DE8 size:0x5A4
void challengeStarMenu(void) {
    return;
}

// .text:0x8004338C size:0x4F4
void starMenuCursor(void) {
    return;
}

// .text:0x80043880 size:0x1418
void fn_80043880(void) {
    return;
}

// .text:0x80044C98 size:0x14E4
void fn_80044C98(void) {
    return;
}

// .text:0x8004617C size:0x1078
void fn_8004617C(void) {
    return;
}

// .text:0x800471F4 size:0xAEC
void fn_800471F4(void) {
    return;
}

// .text:0x80047CE0 size:0x304
void fn_80047CE0(void) {
    return;
}

// .text:0x80047FE4 size:0x6FC
void pauseMenuSelection(void) {
    return;
}

// .text:0x800486E0 size:0x84
void fn_800486E0(void) {
    return;
}

// .text:0x80048764 size:0xBC
void fn_80048764(void) {
    return;
}

// .text:0x80048820 size:0x3CC
void fn_80048820(void) {
    return;
}

extern u32 lbl_803CBCE8;

// fn_80048BEC, size:0x28
void fn_80048BEC(s32* limits) {
    s32 count = limits[1] < limits[2] ? limits[1] : limits[2];
    while (count > 0) {
        count--;
    }
}

// fn_80048C14, size:0x8
void fn_80048C14(u32 value) {
    lbl_803CBCE8 = value;
}

// fn_80048C1C, size:0xC
void fn_80048C1C(void) {
    if (lbl_803CBCE8 != 0) {
        return;
    }
}

// .text:0x80048C28 size:0x124
void fn_80048C28(void) {
    return;
}

// .text:0x80048D4C size:0xB4
void fn_80048D4C(void) {
    return;
}

// .text:0x80048E00 size:0xA8
void fn_80048E00(void) {
    return;
}

DECL_SECT(".sdata") extern void* lbl_803CB83C[3];

// fn_80048EA8, size:0x10
void* fn_80048EA8(s32 index) {
    return lbl_803CB83C[index];
}

// .text:0x80048EB8 size:0x368
void startGameRelated(void) {
    return;
}

// .text:0x80049220 size:0x2AC
void fn_80049220(void) {
    return;
}

// .text:0x800494CC size:0x3AC
void fn_800494CC(void) {
    return;
}

// .text:0x80049878 size:0x408
void possiblyTransferDataBetweenDifferentRels(void) {
    return;
}

// .text:0x80049C80 size:0xBC
void fn_80049C80(void) {
    return;
}

// .text:0x80049D3C size:0x50
void fn_80049D3C(void) {
    return;
}

// .text:0x80049D8C size:0x370
void fn_80049D8C(void) {
    return;
}

// .text:0x8004A0FC size:0xC0
void fn_8004A0FC(void) {
    return;
}

// .text:0x8004A1BC size:0x100
void fn_8004A1BC(void) {
    return;
}

// .text:0x8004A2BC size:0x6C
void fn_8004A2BC(void) {
    return;
}

// .text:0x8004A328 size:0x24
void fn_8004A328(void) {
    return;
}

// .text:0x8004A34C size:0x26C
void fn_8004A34C(void) {
    return;
}

// .text:0x8004A5B8 size:0x218
void fn_8004A5B8(void) {
    return;
}

// .text:0x8004A7D0 size:0x210
void fn_8004A7D0(void) {
    return;
}

// .text:0x8004A9E0 size:0x1F8
void fn_8004A9E0(void) {
    return;
}

extern s32 lbl_803CBCFC;
extern s32 lbl_803CBD00;

extern s32 lbl_803CB848;

// Set_803cb848, size:0x8
void Set_803cb848(s32 value) {
    lbl_803CB848 = value;
}

// fn_8004ABE0, size:0x8
s32 fn_8004ABE0(void) {
    return lbl_803CBCFC;
}

// fn_8004ABE8, size:0x18
s32 fn_8004ABE8(s32 clear) {
    s32 value = lbl_803CBD00;
    if (clear != 0) {
        lbl_803CBD00 = 0;
    }
    return value;
}

// .text:0x8004AC00 size:0xC4
void fn_8004AC00(void) {
    return;
}

extern u32 lbl_803CBD08;

extern u32 lbl_803CBD04;

// fn_8004ACC4, size:0x18
u32 fn_8004ACC4(s32 clear) {
    u32 value = lbl_803CBD04;
    if (clear != 0) {
        lbl_803CBD04 = 0;
    }
    return value;
}

// fn_8004ACDC, size:0x18
u32 fn_8004ACDC(s32 clear) {
    u32 value = lbl_803CBD08;
    if (clear != 0) {
        lbl_803CBD08 = 0;
    }
    return value;
}

// .text:0x8004ACF4 size:0x60
void fn_8004ACF4(void) {
    return;
}

// .text:0x8004AD54 size:0xC4
void fn_8004AD54(void) {
    return;
}

// .text:0x8004AE18 size:0x190
void fn_8004AE18(void) {
    return;
}

// .text:0x8004AFA8 size:0x210
void fn_8004AFA8(void) {
    return;
}

extern u32 lbl_803CBD0C;

// fn_8004B1B8, size:0x8
void fn_8004B1B8(u32 value) {
    lbl_803CBD0C = value;
}

// .text:0x8004B1C0 size:0x48
void fn_8004B1C0(void) {
    return;
}

// .text:0x8004B208 size:0x68
void fn_8004B208(void) {
    return;
}

extern u32 lbl_803CBD04;

extern u32 lbl_803CBD08;

extern u32 lbl_803CBD0C;

// fn_8004B270, size:0x14
void fn_8004B270(void) {
    lbl_803CBD0C = 0;
    lbl_803CBD08 = 0;
    lbl_803CBD04 = 0;
}
