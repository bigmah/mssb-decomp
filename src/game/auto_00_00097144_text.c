#include "game/auto_00_00097144_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/stl.h"

extern s16 lbl_3_data_BE50[][4];  // TODO type: 8-byte entries, first field read here
extern u8 lbl_3_data_D648[];      // sprite descriptors for fn_80034E20
extern u8 lbl_3_data_D7A8[];
extern u8 lbl_3_data_D9E4[];
extern u8 lbl_3_data_DA50[];
extern u8 lbl_3_common_bss_37400[];

extern void fn_3_96CA4(void);
extern void fn_3_95970(void);
extern void fn_3_91A60(void);

// .text:0x00097144 size:0x15C mapped:0x806D61D8
void fn_3_97144(void) {
    BOOL started = FALSE;

    if (g_GameLogic.gameStatus == 3 || (u8)(g_GameLogic.gameStatus - 0x13) <= 4 || g_GameLogic.gameStatus == 0x18) {
        g_UnkSound_32718._02 = 0;
        g_UnkSound_32718._03 = 0;
        g_UnkSound_32718._04 = 0;
        g_UnkSound_32718._05 = 0;
        g_UnkSound_32718._06 = 0;
        return;
    }
    if (g_UnkSound_32718._07 == 0) {
        if (g_UnkSound_32718._02 != 0) {
            if (g_Stats.replayInd == 0) {
                started = TRUE;
                g_UnkSound_32718._07 = g_UnkSound_32718._02;
                g_UnkSound_32718._02 = g_UnkSound_32718._03;
                g_UnkSound_32718._03 = g_UnkSound_32718._04;
                g_UnkSound_32718._04 = g_UnkSound_32718._05;
                g_UnkSound_32718._05 = g_UnkSound_32718._06;
                g_UnkSound_32718._06 = 0;
                g_UnkSound_32718._00 = 0;
            }
            sndFXKeyOff(lbl_3_common_bss_34C58._1C);
        }
    } else {
        g_UnkSound_32718._00++;
        if (g_UnkSound_32718._02 != 0 && g_UnkSound_32718._00 < 0x3C) {
            g_UnkSound_32718._00 = 0x3C;
        }
    }
    if (lbl_3_data_BE50[g_UnkSound_32718._07][0] >= 0 && started) {
        fn_800B0A5C_insertQueue(fn_3_96CA4, 2);
    }
}

// .text:0x000972A0 size:0x28 mapped:0x806D6334
void fn_3_972A0(void* owner, s32 idx, s32 track, u32 frame) {
    fn_8003649C(owner, idx, track, 0x28, frame);
}

// .text:0x000972C8 size:0x124 mapped:0x806D635C
void fn_3_972C8(void) {
    lbl_3_common_bss_32724.hudOff = 1;
    if (g_d_GameSettings.GameModeSelected == 4) {
        fn_80069A98();
        fn_80035CA4(0x16);
    }
    if (g_d_GameSettings.GameModeSelected == 0 || g_d_GameSettings.GameModeSelected == 5 || g_d_GameSettings.GameModeSelected == 4) {
        fn_80035CA4(0x10);
        fn_80035CA4(0xF);
    }
    fn_80035CA4(2);
    fn_80035CA4(5);
    fn_80035CA4(4);
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_80035CA4(0x14);
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_80035CA4(0xE);
        }
        fn_80035CA4(3);
        fn_80035CA4(9);
        fn_80035CA4(0xD);
        fn_80035CA4(0x11);
    } else if (g_d_GameSettings.GameModeSelected == 2) {
        fn_80035CA4(0xB);
        fn_80035CA4(9);
    }
    if (lbl_3_common_bss_32724._D1 != 0) {
        fn_80035CA4(0xC);
    }
}

// .text:0x000973EC size:0x414 mapped:0x806D6480
void fn_3_973EC(void) {
    return;
}

// .text:0x00097800 size:0xDC mapped:0x806D6894
void fn_3_97800(void) {
    return;
}

// .text:0x000978DC size:0x410 mapped:0x806D6970
void fn_3_978DC(void) {
    return;
}

// .text:0x00097CEC size:0x33C mapped:0x806D6D80
void fn_3_97CEC(void) {
    return;
}

// .text:0x00098028 size:0x390 mapped:0x806D70BC
void fn_3_98028(void) {
    return;
}

// .text:0x000983B8 size:0x7C mapped:0x806D744C
void fn_3_983B8(void) {
    return;
}

// .text:0x00098434 size:0x518 mapped:0x806D74C8
void fn_3_98434(void) {
    return;
}

// .text:0x0009894C size:0x2D4 mapped:0x806D79E0
void fn_3_9894C(void) {
    return;
}

// .text:0x00098C20 size:0x1C0 mapped:0x806D7CB4
void fn_3_98C20(void) {
    return;
}

// .text:0x00098DE0 size:0xC8 mapped:0x806D7E74
void fn_3_98DE0(void) {
    return;
}

// .text:0x00098EA8 size:0x1BC mapped:0x806D7F3C
void fn_3_98EA8(void) {
    return;
}

// .text:0x00099064 size:0x344 mapped:0x806D80F8
void fn_3_99064(void) {
    return;
}
