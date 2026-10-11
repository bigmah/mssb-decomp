#ifndef __CHALLENGE_AUTO_00_000085A8_TEXT_H_
#define __CHALLENGE_AUTO_00_000085A8_TEXT_H_

#include "mssbTypes.h"

// Sound test state (lbl_1_common_bss_47674).
typedef struct ChSoundTest {
    /*0x00*/ s32 step;    // fn_1_8B90
    /*0x04*/ s32 menuSel; // 0: fn_1_9AB0, 1: fn_1_88D0
    /*0x08*/ s32 sel;     // 0..2
    /*0x0C*/ u8 loadStep; // fn_1_88D0
    /*0x0D*/ u8 request;  // 1: start, 2: change (handled by fn_1_86E4)
    /*0x0E*/ u8 started;
    /*0x0F*/ u8 cur;
    /*0x10*/ u8 prev;
    /*0x11*/ u8 _11[0x24 - 0x11];
} ChSoundTest; // size: 0x24

extern ChSoundTest lbl_1_common_bss_47674;

// lbl_1_common_bss_47698 (also cleared inline in rep_0250).
typedef struct ChSoundTestList {
    /*0x00*/ s16 count;
    /*0x02*/ u8 slots[11];
} ChSoundTestList;

extern ChSoundTestList lbl_1_common_bss_47698;

void fn_1_85A8(void);
void fn_1_8624(void);
void fn_1_86BC(void);
void fn_1_86E4(void);
void fn_1_8770(void);
void fn_1_88CC(void);
void fn_1_88D0(void);
void fn_1_8A90(void);
void fn_1_8B8C(void);
void fn_1_8B90(void);
void fn_1_8C9C(void);

#endif
