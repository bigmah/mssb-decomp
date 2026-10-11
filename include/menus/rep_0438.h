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
// Menus REL bss flags at 0x100B4.
typedef struct MenusBss100B4 {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1; // nonzero: team select input blocked
} MenusBss100B4;

extern MenusBss100B4 lbl_2_bss_100B4;
extern u16 lbl_2_bss_AE0; // frame counter, wraps at 60000
extern UnlockFlags lbl_80361B20;
extern u8 lbl_800FE930[2][6]; // captain character id per [lbl_80361B20._F4][F410._10]
extern u8 lbl_80108EC4[12];   // captain character ids, in preset order
extern u8 lbl_800FE5D4[];     // captain character ids (first 12 entries)
extern u8 lbl_803CBBC4[];

// main.dol globals only used here so far.
typedef struct Unk803CBCD8 {
    /*0x0*/ u8 _0[5];
    /*0x5*/ u8 _5;
    /*0x6*/ u8 _6[2];
} Unk803CBCD8; // size: 0x8

extern Unk803CBCD8 lbl_803CBCD8;

typedef struct Unk803CBD24 {
    /*0x0*/ u8 _0[4];
    /*0x4*/ u8 team; // team whose controller drives fn_8004CA6C
    /*0x5*/ u8 _5[7];
} Unk803CBD24; // size: 0xC

extern Unk803CBD24 lbl_803CBD24;

typedef struct Unk800E877C {
    /*0x00*/ u8 _00[0x30];
    /*0x30*/ s16 _30;
    /*0x32*/ s16 _32;
    /*0x34*/ u8 _34[4];
} Unk800E877C; // size: 0x38

extern Unk800E877C lbl_800E877C;

typedef struct Unk800EF808 {
    /*0x000*/ u8 _000[0x98];
    /*0x098*/ void* _098; // block freed with fn_800ACFB0
    /*0x09C*/ u8 _09C[0x39C - 0x9C];
} Unk800EF808; // size: 0x39C

extern Unk800EF808 lbl_800EF808;

extern struct CharModelTable lbl_8036E548; // type in main/file_800527C4.h

// main.dol functions whose headers clash with static/UnknownHomes_Static.h.
s32 fn_80021410(void);                 // main/file_80021308.h
void fn_80021AC0(s32 team, s32 arg1);  // main/file_80021308.h
void fn_80021AC4(void);                // main/file_80021308.h
void fn_80035CA4(s32 id);              // main/file_80034F50.h

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
