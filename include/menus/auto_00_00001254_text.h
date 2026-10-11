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

// Character stats entry (0xA0 bytes): inMemRoster[2][9] and the CharSelectState roster at
// lbl_8034E9A0. Field layout as copied by the menu code (see CharacterStats).
typedef struct MenuCharStats {
    /*0x00*/ u8 a[0x1E];
    /*0x1E*/ u8 pad1E[2];
    /*0x20*/ u32 w20;
    /*0x24*/ s16 h24; // character id
    /*0x26*/ u8 b26;
    /*0x27*/ u8 b27;
    /*0x28*/ u8 c28[2];
    /*0x2A*/ u8 c2A[2];
    /*0x2C*/ u8 b2C;
    /*0x2D*/ u8 b2D;
    /*0x2E*/ u8 b2E;
    /*0x2F*/ u8 b2F;
    /*0x30*/ u8 b30;
    /*0x31*/ u8 b31;
    /*0x32*/ u8 b32;
    /*0x33*/ u8 b33;
    /*0x34*/ u8 b34;
    /*0x35*/ u8 c35[2];
    /*0x37*/ u8 c37[4];
    /*0x3B*/ u8 chem[0x36];
    /*0x71*/ u8 b71;
    /*0x72*/ u8 pad72[2];
    /*0x74*/ u16 us[21];
} MenuCharStats; // size: 0xA0

#define MENU_COPY_CHAR_STATS(dst, src)              \
    do {                                            \
        memcpy((dst)->a, (src)->a, 0x1E);           \
        (dst)->h24 = (src)->h24;                    \
        (dst)->b26 = (src)->b26;                    \
        (dst)->b27 = (src)->b27;                    \
        memcpy((dst)->c28, (src)->c28, 2);          \
        memcpy((dst)->c2A, (src)->c2A, 2);          \
        (dst)->b2C = (src)->b2C;                    \
        (dst)->b2D = (src)->b2D;                    \
        (dst)->b2E = (src)->b2E;                    \
        (dst)->b2F = (src)->b2F;                    \
        (dst)->b30 = (src)->b30;                    \
        (dst)->b31 = (src)->b31;                    \
        (dst)->b32 = (src)->b32;                    \
        (dst)->b33 = (src)->b33;                    \
        (dst)->b34 = (src)->b34;                    \
        memcpy((dst)->c35, (src)->c35, 2);          \
        (dst)->w20 = (src)->w20;                    \
        memcpy((dst)->c37, (src)->c37, 4);          \
        memcpy((dst)->chem, (src)->chem, 0x36);     \
        (dst)->b71 = (src)->b71;                    \
        (dst)->us[0] = (src)->us[0];                \
        (dst)->us[1] = (src)->us[1];                \
        (dst)->us[2] = (src)->us[2];                \
        (dst)->us[3] = (src)->us[3];                \
        (dst)->us[4] = (src)->us[4];                \
        (dst)->us[5] = (src)->us[5];                \
        (dst)->us[6] = (src)->us[6];                \
        (dst)->us[7] = (src)->us[7];                \
        (dst)->us[8] = (src)->us[8];                \
        (dst)->us[9] = (src)->us[9];                \
        (dst)->us[10] = (src)->us[10];              \
        (dst)->us[11] = (src)->us[11];              \
        (dst)->us[12] = (src)->us[12];              \
        (dst)->us[13] = (src)->us[13];              \
        (dst)->us[14] = (src)->us[14];              \
        (dst)->us[15] = (src)->us[15];              \
        (dst)->us[16] = (src)->us[16];              \
        (dst)->us[17] = (src)->us[17];              \
        (dst)->us[18] = (src)->us[18];              \
        (dst)->us[19] = (src)->us[19];              \
        (dst)->us[20] = (src)->us[20];              \
    } while (0)

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

void fn_2_323C(void);

void fn_2_B324(void);

void fn_2_FAA0(s32 team);

void fn_2_C484(s32 owner, s16 id);

void fn_2_11EA8(void);

void fn_2_ABC0(u8 team);

void fn_2_FCB4(u8 team);

void fn_2_F200(u8 team);

void fn_2_6D3C(void);

void fn_2_61A0(void);

void fn_2_110B0(void);

void fn_2_8940(void);

void fn_2_2FC0(u8 mode, s32 b, s32 c);

void fn_2_6AF4(void);

void fn_2_CA60(u8 slot, s32 team);

void fn_2_6884(void);

void fn_2_C7DC(u8 slot, s32 team);

#endif
