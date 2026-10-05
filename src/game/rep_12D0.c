#include "game/rep_12D0.h"
#include "header_rep_data.h"

extern u8 g_Strikes[];
extern u8 g_Ball[];
extern u8 g_FieldingLogic[];
extern u8 g_Runners[];
extern u8 lbl_3_common_bss_32A94[];

// .text:0x00077914 size:0xC60 mapped:0x806B69A8
void fn_3_77914(void) {
    return;
}

// .text:0x00078574 size:0x1BC mapped:0x806B7608
void fn_3_78574(void) {
    return;
}

// .text:0x00078730 size:0x394 mapped:0x806B77C4
void fn_3_78730(void) {
    return;
}

// .text:0x00078AC4 size:0x57C mapped:0x806B7B58
void fn_3_78AC4(void) {
    return;
}

// .text:0x00079040 size:0x2F8 mapped:0x806B80D4
void fn_3_79040(void) {
    return;
}

// .text:0x00079338 size:0xDC mapped:0x806B83CC
void fn_3_79338(void) {
    s32 i;
    if (*(s32*)(g_Strikes + 0xC) == 2) {
        return;
    }
    if (*(s32*)(g_Strikes + 8) >= 3) {
        return;
    }
    if (lbl_3_common_bss_32A94[0x24] == 0) {
        if (*(s16*)(g_Ball + 0x1B7A) == 3 || g_FieldingLogic[0x113] == 1) {
            if (g_Ball[0x1BBF] >= 2) {
                lbl_3_common_bss_32A94[0x24] = 2;
            }
        }
    } else if (lbl_3_common_bss_32A94[0x24] == 2) {
        if (*(s16*)(g_Ball + 0x1B7A) == 3) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i * 0x154 + 0x123] == 3) {
                    lbl_3_common_bss_32A94[0x24] = 1;
                }
            }
        }
    }
}

// .text:0x00079414 size:0x194 mapped:0x806B84A8
void fn_3_79414(void) {
    return;
}

// .text:0x000795A8 size:0x1C4 mapped:0x806B863C
void fn_3_795A8(void) {
    return;
}

