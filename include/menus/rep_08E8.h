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

// lbl_80353A90: per-game line score (main.dol .bss, size 0x108).
typedef struct MenuLineScore {
    /*0x00*/ u8 _00[0x8];
    /*0x08*/ u16 scores[4][19]; // [0] total, [1..] per inning; rows 0/1 and 2/3 per team
    /*0xA0*/ s8 _A0[30];
    /*0xBE*/ u8 _BE[0xF0 - 0xBE];
    /*0xF0*/ u8 _F0[2]; // per team
    /*0xF2*/ u8 result; // 0: team 0 ahead, 1: team 1 ahead, 2: tie
    /*0xF3*/ u8 _F3[0xF6 - 0xF3];
    /*0xF6*/ u8 innings;
    /*0xF7*/ u8 _F7[0x108 - 0xF7];
} MenuLineScore;

extern MenuLineScore lbl_80353A90;

// lbl_803537E4: [2 teams][9] records, 0x26 bytes each (only fields used here).
typedef struct MenuRosterRecord {
    /*0x00*/ u8 _00[0x4];
    /*0x04*/ s8 _04;
    /*0x05*/ s8 _05;
    /*0x06*/ u8 _06[0x10 - 0x6];
    /*0x10*/ s8 _10;
    /*0x11*/ u8 _11;
    /*0x12*/ s8 _12;
    /*0x13*/ u8 _13[0x18 - 0x13];
    /*0x18*/ s8 _18;
    /*0x19*/ u8 _19[0x26 - 0x19];
} MenuRosterRecord;

extern MenuRosterRecord lbl_803537E4[2][9];

// lbl_803535C8: [2 teams][9] records, 0x1E bytes each (only fields used here).
typedef struct MenuFieldRecord {
    /*0x00*/ u8 _00[0x2];
    /*0x02*/ s16 _02;
    /*0x04*/ u8 _04[0xA - 0x4];
    /*0x0A*/ s16 _0A;
    /*0x0C*/ u8 _0C[0x1A - 0xC];
    /*0x1A*/ s8 _1A;
    /*0x1B*/ u8 _1B;
    /*0x1C*/ s8 _1C;
    /*0x1D*/ u8 _1D;
} MenuFieldRecord;

extern MenuFieldRecord lbl_803535C8[2][9];

// lbl_8034E9A0 + 0x4908: three 4-byte slots.
typedef struct MenuSlot4908 {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 _1_hi : 5;
    /*0x1*/ u8 _1_lo : 3;
    /*0x2*/ u8 _2;
    /*0x3*/ u8 _3;
} MenuSlot4908;

// lbl_8034E9A0 (character/team select work area), only the fields used here.
typedef struct MenuSelectState {
    /*0x0000*/ u8 _0000[0x4908];
    /*0x4908*/ MenuSlot4908 _4908[3];
} MenuSelectState;

extern MenuSelectState lbl_8034E9A0;

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

void fn_2_4A340(void);

#endif
