#ifndef __MENUS_REP_0438_H_
#define __MENUS_REP_0438_H_

#include "mssbTypes.h"
#include "menus/auto_00_00013BA4_text.h"

extern DebugMenuState lbl_2_bss_100B8;

// Menus REL bss block at 0xF410 (size 0x58, only the fields used here).
typedef struct MenusBssF410 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s32 _10[2]; // per team
    /*0x18*/ u8 _18[0x54 - 0x18];
    /*0x54*/ u32 _54;
} MenusBssF410; // size: 0x58

extern MenusBssF410 lbl_2_bss_F410;
extern u8 lbl_2_bss_100B4;
extern u16 lbl_2_bss_AE0;
extern UnlockFlags lbl_80361B20;
extern u8 lbl_800FE930[2][6]; // captain character id per [lbl_80361B20._F4][F410._10]
extern u8 lbl_80108EC4[12];   // captain character ids, in preset order
extern u8 lbl_800FE5D4[];     // captain character ids (first 12 entries)
extern u8 lbl_803CBBC4[]; // frame counter, wraps at 60000

void fn_2_12238(void);
void fn_2_123CC(void);
void fn_2_12988(void);
void fn_2_129AC(void);
void fn_2_129D0(void);
void fn_2_12A70(void);
void fn_2_12B60(void);
void fn_2_12C34(void);
void fn_2_12CD8(void);
void fn_2_12F88(void);

#endif
