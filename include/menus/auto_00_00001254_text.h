#ifndef __AUTO_00_00001254_TEXT_MENUS_H__
#define __AUTO_00_00001254_TEXT_MENUS_H__

#include "mssbTypes.h"
#include "menus/menu_work.h"
#include "game/character_stats.h"

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

// Field-by-field copy of a CharacterStats (inMemRoster[2][9], the CharSelectState roster at
// lbl_8034E9A0), in the order the menu code copies it.
#define MENU_COPY_CHAR_STATS(dst, src)                                      \
    do {                                                                    \
        memcpy(&(dst)->stats, &(src)->stats, 0x1E);                         \
        (dst)->stats.CharID = (src)->stats.CharID;                          \
        (dst)->stats.FieldingArm = (src)->stats.FieldingArm;                \
        (dst)->stats.BattingStance = (src)->stats.BattingStance;            \
        memcpy(&(dst)->stats.SlapContactSize, &(src)->stats.SlapContactSize, 2);\
        memcpy(&(dst)->stats.SlapHitPower, &(src)->stats.SlapHitPower, 2);  \
        (dst)->stats.BuntingContactSize = (src)->stats.BuntingContactSize;  \
        (dst)->stats.HitTrajectoryPushPull = (src)->stats.HitTrajectoryPushPull;\
        (dst)->stats.HitTrajectoryHighLow = (src)->stats.HitTrajectoryHighLow;\
        (dst)->stats.Speed = (src)->stats.Speed;                            \
        (dst)->stats.ThrowingArm = (src)->stats.ThrowingArm;                \
        (dst)->stats.CharacterClass = (src)->stats.CharacterClass;          \
        (dst)->stats.Weight = (src)->stats.Weight;                          \
        (dst)->stats.Captain = (src)->stats.Captain;                        \
        (dst)->stats.CaptainStarHitPitch = (src)->stats.CaptainStarHitPitch;\
        memcpy(&(dst)->stats.NonCaptainStarSwing, &(src)->stats.NonCaptainStarSwing, 2);\
        (dst)->stats.FieldingStats = (src)->stats.FieldingStats;            \
        memcpy(&(dst)->stats.BattingStatBar, &(src)->stats.BattingStatBar, 4);\
        memcpy((dst)->chem, (src)->chem, sizeof(ChemistryTable));           \
        (dst)->BytesAfterChemistry[0] = (src)->BytesAfterChemistry[0];      \
        (dst)->UnusedShorts[0] = (src)->UnusedShorts[0];                    \
        (dst)->UnusedShorts[1] = (src)->UnusedShorts[1];                    \
        (dst)->UnusedShorts[2] = (src)->UnusedShorts[2];                    \
        (dst)->UnusedShorts[3] = (src)->UnusedShorts[3];                    \
        (dst)->UnusedShorts[4] = (src)->UnusedShorts[4];                    \
        (dst)->UnusedShorts[5] = (src)->UnusedShorts[5];                    \
        (dst)->UnusedShorts[6] = (src)->UnusedShorts[6];                    \
        (dst)->UnusedShorts[7] = (src)->UnusedShorts[7];                    \
        (dst)->UnusedShorts[8] = (src)->UnusedShorts[8];                    \
        (dst)->UnusedShorts[9] = (src)->UnusedShorts[9];                    \
        (dst)->UnusedShorts[10] = (src)->UnusedShorts[10];                  \
        (dst)->UnusedShorts[11] = (src)->UnusedShorts[11];                  \
        (dst)->UnusedShorts[12] = (src)->UnusedShorts[12];                  \
        (dst)->UnusedShorts[13] = (src)->UnusedShorts[13];                  \
        (dst)->UnusedShorts[14] = (src)->UnusedShorts[14];                  \
        (dst)->UnusedShorts[15] = (src)->UnusedShorts[15];                  \
        (dst)->UnusedShorts[16] = (src)->UnusedShorts[16];                  \
        (dst)->UnusedShorts[17] = (src)->UnusedShorts[17];                  \
        (dst)->UnusedShorts[18] = (src)->UnusedShorts[18];                  \
        (dst)->UnusedShorts[19] = (src)->UnusedShorts[19];                  \
        (dst)->UnusedShorts[20] = (src)->UnusedShorts[20];                  \
    } while (0)

// Copy of the held/down/repeat words of one pad in CharSelectState (0x472C).
typedef struct MenuButtons {
    u16 held;
    u16 down;
    u16 repeat;
} MenuButtons;

u32 fn_2_1258(const void* base, u32 offset, s32 size);

u8 fn_2_35D0(u8 index);

void fn_2_6138(void);

void fn_2_1D54(s32* selection, u8 controller, s32 count);

s32 fn_2_112F4(void* menu, s32 item, s32 index, const u16* values, s16 value);

s32 fn_2_8780(s32 mode);

s32 fn_2_8794(s32 mode, s32 index);

s8 fn_2_57E8(s32 unused, s32 value);

void fn_2_EC34(void);

u32 fn_2_1554(void);

s32 fn_2_14F8(s32 lo, s32 hi); // random integer in [lo, hi]

void fn_2_1A88(void);

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

void fn_2_A288(void);

void fn_2_1800(void);

void fn_2_1578(void);

void fn_2_2D1C(void);

void fn_2_A6E0(void);

void fn_2_B66C(void);

void fn_2_AEE8(void);

void fn_2_11340(u8 team);

void fn_2_BF90(void);

void fn_2_5444(u8 team);

void fn_2_1F30(void);

void fn_2_27E0(void);

void fn_2_57F0(u8 team, u16 held, u16 pressed, u16 repeat);

void fn_2_DFAC(u8 team);

void fn_2_CE44(u8 team);

s32 fn_2_ED94(u8 team, u16 held, u16 pressed, s32 dirs);

void fn_2_9ACC(u16 team);

void fn_2_95D8(void);

void fn_2_B920(void);

void fn_2_11698(void);

void fn_2_4970(u8 team, s32 empty);

void fn_2_8CF8(u16 team);

#endif
