#include "challenge/rep_02A8.h"


#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"

extern s32 lbl_800EF808[];

extern u8 lbl_1_bss_2FDB[];
extern u8 lbl_1_data_1884[];
extern u8 lbl_1_data_1CA0[];
extern u8 lbl_1_data_17A4[];

static inline s32 SoundOptionValue(s32 index) {
    return lbl_800EF808[index + 1];
}

// fn_1_A8B4, size:0x54
s32 fn_1_A8B4(void) {
    s32 index = lbl_1_data_1CA0[0];
    fn_80021518(lbl_1_data_17A4[index], SoundOptionValue(index + 5));
    return 0;
}

// fn_1_A7E4, size:0x54
s32 fn_1_A7E4(void) {
    s32 index = lbl_1_bss_2FDB[0];
    fn_80021518(lbl_1_data_1884[index], SoundOptionValue(index + 0x2A));
    return 0;
}

// .text:0xA714 size:0x4
void fn_1_A714(void) {
}

// fn_1_A77C, size:0x34
s32 fn_1_A77C(void) {
    fn_80021518(0x31, lbl_800EF808[0x2A]);
    return 0;
}

// fn_1_A7B0, size:0x34
s32 fn_1_A7B0(void) {
    fn_80021518(0x33, lbl_800EF808[0x32]);
    return 0;
}

// fn_1_A880, size:0x34
s32 fn_1_A880(void) {
    fn_80021518(0x1C, lbl_800EF808[0x2]);
    return 0;
}

// fn_1_A838, size:0x48
s32 fn_1_A838(void) {
    fn_80021518(0x1C, lbl_800EF808[4]);
    fn_80021518(0x36, lbl_800EF808[4]);
    return 0;
}

// fn_1_BEF4, size:0x40
void fn_1_BEF4(s16 voice) {
    sndFXKeyOff(voice);
    sndFXCtrl(voice, 7, 0);
}
