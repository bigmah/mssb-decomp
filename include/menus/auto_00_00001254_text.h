#ifndef __AUTO_00_00001254_TEXT_MENUS_H__
#define __AUTO_00_00001254_TEXT_MENUS_H__

#include "mssbTypes.h"

// Character table entry (lbl_800E8558); CharTableEntry in main/file_8004C5F8.h,
// which declares fn_800506E8 with an s8 owner while menus calls it with an int.
typedef struct MenuCharEntry {
    /*0x0*/ u8 _0;
    /*0x1*/ u8 id;
    /*0x2*/ u8 lockId; // compared against lbl_803CB748[]
    /*0x3*/ u8 _3;
    /*0x4*/ u8 _4;
    /*0x5*/ u8 _5;
} MenuCharEntry;

// Per-port controller state (lbl_803C77B8); same layout as PadState in main/file_800A7C08.h,
// which can't be included next to UnknownHomes_Static.h.
typedef struct MenuPad {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u16 prev;
    /*0x08*/ s8 err;
    /*0x09*/ u8 _09[0x20 - 0x09];
} MenuPad;

u32 fn_2_1258(const void* base, u32 offset, s32 size);

s32 fn_2_35D0(u8 index);

void fn_2_6138(void);

void fn_2_1D54(s32* selection, u8 controller, s32 count);

s32 fn_2_112F4(void* menu, s32 item, s32 index, const u16* values, s16 value);

s32 fn_2_8780(s32 mode);

s32 fn_2_8794(s32 mode, s32 index);

s8 fn_2_57E8(s32 unused, s32 value);

void fn_2_EC34(void);

u32 fn_2_1554(void);

void fn_2_1328(u32* value, u16 increment);

void fn_2_12A0(s16* value, s32 increment);

void fn_2_12CC(u8* value, s32 increment);

void fn_2_12F8(u16* value, s32 increment);

void fn_2_1D28(void);

void fn_2_1254(void);

void fn_2_1DC4(void);

void fn_2_893C(void);

void fn_2_CCBC(void);

void fn_2_3204(void);

void fn_2_6098(s32 index);

void fn_2_1BAC(void);

s32 fn_2_60D4(u8 index);

s32 fn_2_148C(u16* p);

void fn_2_120D0(void);

void fn_2_7D44(void);

s32 fn_2_33BC(void);

s32 fn_2_A62C(void);

void fn_2_1216C(void);

void fn_2_1C34(u32 buttons);

typedef struct SortEntry {
    s32 key;
    s32 value;
} SortEntry;

void fn_2_1354(SortEntry* e, s32 n, s32 descending);

s32 fn_2_A50C(void);

void fn_2_EC54(s32 index);

s8 fn_2_C324(s32 id);

void fn_2_A040(s32 a, s32 b, u8 c, u8 d);

void fn_2_B508(void);

void fn_2_52CC(void);

void fn_2_86EC(void);

void fn_2_C698(u8 a, s32 b);

void fn_2_1DC8(void);

void fn_2_6484(void);

void fn_2_6608(void);

s32 fn_2_9F70(s8 team);

void fn_2_6784(void);

void fn_2_87A8(void);

s32 fn_2_14F8(s32 a, s32 b);

void fn_2_A1A0(s32 count, s32 team);

void fn_2_1A88(void);

void fn_2_348C(void);

void fn_2_102C8(u8 team);

void fn_2_5184(u8 team);

void fn_2_EAE0(void);

void fn_2_CCE0(u8 team);

#endif
