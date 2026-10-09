#include "game/auto_00_0009CD90_text.h"

typedef struct { u8 pad[0xDC]; s32 a[4]; } GL;
extern u8 g_Ball[];
extern s32 g_Strikes;
extern u8 g_d_GameSettings[];
extern u8 g_GameLogic[];
extern u8 lbl_3_common_bss_32A94[];

// fn_3_9DBE4, size:0x34
void fn_3_9DBE4(void) {
    lbl_3_common_bss_32A94[0x7D] = 0;
    lbl_3_common_bss_32A94[0x7F] = 0;
    lbl_3_common_bss_32A94[0x81] = 0;
    lbl_3_common_bss_32A94[0x82] = 0;
    lbl_3_common_bss_32A94[0x84] = 0;
    lbl_3_common_bss_32A94[0x85] = 0;
    lbl_3_common_bss_32A94[0x87] = 0;
    lbl_3_common_bss_32A94[0x88] = 0;
    lbl_3_common_bss_32A94[0x8A] = 0;
}
