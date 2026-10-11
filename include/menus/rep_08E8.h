#ifndef __MENUS_REP_08E8_H__
#define __MENUS_REP_08E8_H__

#include "mssbTypes.h"

// View of lbl_8036E548 (CharMgr in main/file_80011640.h; that header can't be
// included here), only the fields used by this unit.
typedef struct MenuCharActor {
    /*0x000*/ u8 _000[0x10];
    /*0x010*/ void* banks[7];
    /*0x02C*/ u8 _02C[0x27C - 0x2C];
} MenuCharActor; // size: 0x27C

typedef struct MenuCharMgr {
    /*0x0000*/ u8 _0000[0xAC];
    /*0x00AC*/ struct Light* lights[4];
    /*0x00BC*/ u8 _00BC[0xC04 - 0xBC];
    /*0x0C04*/ MenuCharActor actors[13];
    /*0x2C50*/ void* active[13];
    /*0x2C84*/ void* stadiumFiles;
    /*0x2C88*/ u8* bankBuf;
    /*0x2C8C*/ u8* fileBuf;
    /*0x2C90*/ u32 bankSize[5];
    /*0x2CA4*/ u8 _2CA4[0x2CEC - 0x2CA4];
    /*0x2CEC*/ u8* bankSets[4][5];
} MenuCharMgr;

#define MENU_CHARMGR (*(MenuCharMgr*)lbl_8036E548)

// Entry of the ARAM file table (19 per character).
typedef struct { u32 a; u32 size; u32 c; u32 d; } Entry08E8;

void fn_2_4A064(void);

void fn_2_474F8(void);

s16 fn_2_4A150(s16 angle);

s16 fn_2_4A310(s16 a, s16 b);

u16* fn_2_4A094(u16* destination, const u16* source);

s32 fn_2_4A068(const u16* string);

s32 fn_2_46D00(void);

void fn_2_481B8(void);

void fn_2_474FC(void);

void fn_2_4777C(void);

f32 fn_2_4A1E8(f32 x, f32 y);

s32 fn_2_4A2C4(f32 angle);

void fn_2_47AFC(void);

f32 fn_2_4A18C(f32 angle);

void fn_2_46D34(s32 delta);

void fn_2_489DC(void);

s32 fn_2_49EFC(const u16* string, u16 style);

void fn_2_46C88(s32 index);

void fn_2_48D54(void);

void fn_2_48D08(void);

s16 fn_2_4A234(f32 x, f32 y);

void fn_2_49E5C(s32 x, s32 y, s32 number, s32 flags, s32 digits, s32 style,
                s32 first, s32 second, s32 third);

void fn_2_49DB8(s32 x, s32 y, s32 number, s32 flags, s32 option, s32 digits,
                s32 style, s32 first, s32 second, s32 third);

void fn_2_48BE0(void);

s32 fn_2_4A0C4(const u16* a, const u16* b);

void fn_2_472C4(s16* sel, s16* scroll, s16 count, s16 page, s16 flags);

void fn_2_4AEE4(void);

void fn_2_47CFC(void);

void fn_2_487A0(void);

void fn_2_47FF8(void);

void fn_2_48A1C(void);

void fn_2_4906C(void);

void fn_2_477C0(void);

void fn_2_478F4(void);

u16* fn_2_49F7C(u16* string, s32 capacity, u16 character, s32 position);

void fn_2_4AB1C(void);

void fn_2_47540(void);

void fn_2_48DB4(void);

#endif
