#include "menus/rep_01A0.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80069BDC.h"
#include "musyx/musyx.h"

// Menu music voice and its fade-out state.
extern SND_VOICEID lbl_2_data_134; // SND_ID_ERROR when not playing
extern f32 lbl_2_bss_18;           // current volume
extern u8 lbl_2_bss_1C;            // nonzero while a fade task is queued

// .text:0x00000A70 size:0xC8
void fn_2_A70(u16 frames) {
    SceneTask* task;

    if (lbl_2_bss_1C == 0 && lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
        task = fn_800B0A5C_insertQueue(fn_2_B38, 0x8000);
        if (frames == 0) {
            frames = 1;
        }
        task->u14.rate = -lbl_2_bss_18 / frames;
        lbl_2_bss_1C = 1;
    }
}

// .text:0x00000B38 size:0xE0
void fn_2_B38(void) {
    lbl_2_bss_18 += lbl_803CC1B8->u14.rate;
    if (lbl_2_bss_18 < 0.0f) {
        lbl_2_bss_18 = 0.0f;
    }
    sndFXCtrl(lbl_2_data_134, 7, lbl_2_bss_18);
    if (0.0f == lbl_2_bss_18) {
        lbl_2_bss_1C = 0;
        if (lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
            sndFXKeyOff(lbl_2_data_134);
            lbl_2_data_134 = SND_ID_ERROR;
        }
#if NONMATCHING
        fn_800B0A14_removeQueue(NULL); // the argument is unused
#else
        ((void (*)(void))fn_800B0A14_removeQueue)(); // original passes a stale r3
#endif
    }
}

// .text:0x00000C18 size:0x5C
void fn_2_C18(void) {
    if (lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
        sndFXKeyOff(lbl_2_data_134);
        lbl_2_data_134 = SND_ID_ERROR;
    }
}

// .text:0x00000C74 size:0x94
void fn_2_C74(u8 volume) {
    if (lbl_2_data_134 != SND_ID_ERROR && sndFXCheck(lbl_2_data_134) == lbl_2_data_134) {
        sndFXCtrl(lbl_2_data_134, 7, volume);
    } else {
        lbl_2_bss_18 = volume;
    }
}
