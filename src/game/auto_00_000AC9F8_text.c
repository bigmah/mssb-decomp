#include "game/auto_00_000AC9F8_text.h"
#include "game/UnknownHomes_Game.h"

#include "game/auto_00_000B3B70_text.h"

extern u8 lbl_3_common_bss_34C90[];

// fn_3_AFDA4, size:0x1C
void fn_3_AFDA4(void) {
    lbl_3_common_bss_34C90[0x1D5] = 0;
    lbl_3_common_bss_34C90[0x1D6] = 0;
    lbl_3_common_bss_34C90[0x1D7] = 0;
}

// fn_3_AFD80, size:0x24
void fn_3_AFD80(u8 state) {
    lbl_3_common_bss_34C90[0x1D1] = state;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0xC) = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0xE) = 0;
    *(s16*)(lbl_3_common_bss_34C90 + 0x10) = 0;
}

// fn_3_B0A88, size:0x24
void fn_3_B0A88(void) {
    fn_3_B3C78(0);
}

// fn_3_B3A28, size:0x24
void fn_3_B3A28(void) {
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    lbl_3_common_bss_34C90[0x1DA] = 0;
}

// fn_3_B1DA4, size:0x2C
void fn_3_B1DA4(u8 level, u8 value) {
    g_Practice.loadingGuidedPractice = 1;
    g_Practice._1D5 = 0;
    g_Practice.practiceLevel_2 = level;
    *((u8*)&g_Practice + 0x1D7) = value;
    *((u8*)&g_Practice + 0x1D8) = 0;
    g_Practice._188 = 0;
}

// fn_3_B3288, size:0x30
void fn_3_B3288(void) {
    g_Practice.pauseMenuLoading = 0;
    *((u8*)&g_Practice + 0x19F) = 1;
    g_Practice.frames_onPauseScreen = 0;
    lbl_3_common_bss_34C90[0x1D2] = 0;
    lbl_3_common_bss_34C90[0x1DA] = 0;
}

// fn_3_AFD48, size:0x38
s32 fn_3_AFD48(s16 value) {
    if (*(s8*)(lbl_3_common_bss_34C90 + 0x206) <= 0) {
        *(s16*)(lbl_3_common_bss_34C90 + 4) = value;
        *(s16*)(lbl_3_common_bss_34C90 + 6) = value;
        *(s16*)(lbl_3_common_bss_34C90 + 8) = value;
        lbl_3_common_bss_34C90[0x206] = 13;
        return 1;
    }
    return 0;
}

// fn_3_B0CF4, size:0x38
s32 fn_3_B0CF4(void) {
    if (g_Practice.aiBuntIndicator == 0) return 0;
    return g_Ball.pitchHangtimeCounter > 0;
}
