#ifndef __MENUS_AUTO_00_0005E84C_TEXT_H_
#define __MENUS_AUTO_00_0005E84C_TEXT_H_

#include "mssbTypes.h"
#include "main/file_8000F150.h"
#include "main/file_80034F50.h"
#include "main/file_80011640.h"
#include "main/file_800A6870.h"
#include "static/GameSettings.h"

// Menu task (queue item) that owns a run of sprites in lbl_80371C30 starting
// at baseIdx. Only the fields used here.
typedef struct MenuTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ u8 _04[0x8];
    /*0x0C*/ struct MenuTask* parent;
    /*0x10*/ s16 _10;
    /*0x12*/ u16 priority;
    /*0x14*/ u16 baseIdx;
    /*0x16*/ u16 count;
    /*0x18*/ u8 _18[0x28 - 0x18];
    /*0x28*/ s8 step;
    /*0x29*/ u8 _29[0x80 - 0x29];
    /*0x80*/ s32 _80;
} MenuTask;

// One animated element of a menu task; func is called every frame with the
// owning task. state is driven by fn_2_53BC8's events.
typedef struct MenuItem {
    /*0x00*/ void (*func)(MenuTask* task, struct MenuItem* item);
    /*0x04*/ s16 state;
    /*0x06*/ s16 timer;
    /*0x08*/ s16 _08;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 key;    // event slot for fn_2_53BC8
    /*0x0E*/ s16 sprite; // index relative to task->baseIdx
    /*0x10*/ s16 _10;
    /*0x12*/ s16 _12;
    /*0x14*/ s16 _14;
} MenuItem;

#define MENU_SPRITE(task, item) (lbl_80371C30[(task)->baseIdx + (item)->sprite].obj)

// High-score style record: a value and two tags.
typedef struct MenuRecord {
    /*0x0*/ s32 value;
    /*0x4*/ s16 _4;
    /*0x6*/ s16 _6;
} MenuRecord; // size: 0x8

// Large menus work area (lbl_2_bss_1A824C points at it); only the fields used here.
typedef struct MenuData {
    /*0x000000*/ u8 _000000[0x1972BC];
    /*0x1972BC*/ u8 _1972BC;
    /*0x1972BD*/ u8 _1972BD[3];
    /*0x1972C0*/ u8 _1972C0;
    /*0x1972C1*/ u8 _1972C1[3];
    /*0x1972C4*/ MenuRecord records[8][5];
    /*0x197404*/ s16 _197404;
    /*0x197406*/ u8 _197406[0x197416 - 0x197406];
    /*0x197416*/ u8 _197416;
    /*0x197417*/ u8 _197417;
    /*0x197418*/ u8 _197418;
    /*0x197419*/ u8 _197419[0x197430 - 0x197419];
    /*0x197430*/ s16 stats[8]; // a StatOutput
    /*0x197440*/ u8 _197440[0x1976FA - 0x197440];
    /*0x1976FA*/ s16 _1976FA;
    /*0x1976FC*/ u8 _1976FC[2];
    /*0x1976FE*/ s16 _1976FE;
    /*0x197700*/ u8 _197700[6];
    /*0x197706*/ s16 _197706; // character (index into lbl_800E869C)
    /*0x197708*/ u8 _197708[0x197730 - 0x197708];
    /*0x197730*/ s16 _197730;
    /*0x197732*/ u8 _197732[0x197862 - 0x197732];
    /*0x197862*/ u8 _197862;
} MenuData;

extern MenuData* lbl_2_bss_1A824C;

// Menus state (lbl_2_bss_1A8248 points at it); only the fields used here.
typedef struct MenuState {
    /*0x0000*/ u8 _0000[0x177C];
    /*0x177C*/ s16 _177C;
    /*0x177E*/ u8 _177E[0x17AB - 0x177E];
    /*0x17AB*/ u8 _17AB;
    /*0x17AC*/ u8 _17AC[0x441C - 0x17AC];
    /*0x441C*/ u8 _441C;
    /*0x441D*/ u8 _441D[0x442F - 0x441D];
    /*0x442F*/ u8 _442F;
} MenuState;

extern MenuState* lbl_2_bss_1A8248;

s16 fn_2_53BC8(void* item);

extern s16 lbl_2_data_2E80[][3];
extern u8 lbl_2_data_20BF0[];
extern AssetLoadInstructions lbl_2_data_20C00;

extern MenuTask* lbl_803CC1B8;

// StatOutput (main/file_80069BDC.h, which can't be included next to the
// headers above): s16 vals[6]; s16 _C; s16 _E.
struct StatOutput;
u8 fn_8006C100(s16 value);
s16 fn_8006C268(struct StatOutput* stats);


// lbl_2_bss_1A823C points at this; only the fields used here.
typedef struct MenuFlags {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ u8 _34;
} MenuFlags;

extern MenuFlags* lbl_2_bss_1A823C;

typedef struct MenuCharRecord {
    /*0x00*/ u8 _00[0x13];
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14[2];
} MenuCharRecord; // size: 0x16

// Saved record tables (lbl_2_bss_1A8240 points at them): 8 lists of 5.
typedef struct MenuRecords {
    /*0x000*/ MenuRecord lists[8][5];
    /*0x140*/ MenuCharRecord chars[32];
    /*0x400*/ u8 _400[1]; // indexed by character
} MenuRecords;

extern MenuRecords* lbl_2_bss_1A8240;

// lbl_2_bss_1A8244 points at this; only the fields used here.
typedef struct MenuProgress {
    /*0x00*/ u8 _00[0xC6]; // indexed by lbl_800E869C[character]
    /*0xC6*/ u8 _C6[5][4];
} MenuProgress;

extern MenuProgress* lbl_2_bss_1A8244;

typedef struct MenuFlags4 {
    u8 b[4];
} MenuFlags4;

extern MenuFlags4 lbl_2_bss_33FBF0;
extern u8 lbl_2_bss_33FBF5;

extern u8 lbl_800E869C[];

// Same layout as SaveProgress (main/file_8003A688.h), which can't be included
// next to the headers above.
typedef struct MenuSaveProgress {
    /*0x0000*/ u8 challenge[3][0x4508];
    /*0xCF18*/ u8 _CF18[0x36]; // indexed by lbl_800E869C[character]
} MenuSaveProgress;

extern MenuSaveProgress lbl_80354768;

void fn_800ACFB0(void* block);

void fn_800B0A14_removeQueue(void* unused);

u32 fn_80062890(s32 index);

void fn_2_5E84C(void);
void fn_2_5EB78(void);
void fn_2_5ED3C(void);
void fn_2_5EE34(void);
void fn_2_5EEBC(MenuTask* task, MenuItem* item);
void fn_2_5F08C(MenuTask* task, MenuItem* item);
void fn_2_5F2A8(MenuTask* task, MenuItem* item);
void fn_2_5F458(void);
void fn_2_5FDC4(void);
void fn_2_60084(MenuTask* task, MenuItem* item);
void fn_2_6020C(MenuTask* task, MenuItem* item);
void fn_2_60394(MenuTask* task, MenuItem* item);
void fn_2_6051C(void);
void fn_2_607DC(MenuTask* task, MenuItem* item);
void fn_2_60968(MenuTask* task, MenuItem* item);
void fn_2_60AF0(MenuTask* task, MenuItem* item);
void fn_2_60C78(MenuTask* task, MenuItem* item);
void fn_2_60DF4(MenuTask* task, MenuItem* item);
void fn_2_60F7C(MenuTask* task, MenuItem* item);
void fn_2_61104(MenuTask* task, MenuItem* item);
void fn_2_612A8(MenuTask* task, MenuItem* item);
void fn_2_61468(MenuTask* task, MenuItem* item);
void fn_2_61644(MenuTask* task, MenuItem* item);
void fn_2_61794(MenuTask* task, MenuItem* item);
void fn_2_61948(MenuTask* task, MenuItem* item);
void fn_2_61B6C(MenuTask* task, MenuItem* item);
void fn_2_61D90(MenuTask* task, MenuItem* item);
void fn_2_61F5C(MenuTask* task, MenuItem* item);
void fn_2_62110(MenuTask* task, MenuItem* item);
void fn_2_623AC(MenuTask* task, MenuItem* item);
void fn_2_625B0(MenuTask* task, MenuItem* item);
void fn_2_627F4(MenuTask* task, MenuItem* item);
void fn_2_62A38(MenuTask* task, MenuItem* item);
void fn_2_62D18(void);
void fn_2_63570(MenuTask* task, MenuItem* item);
void fn_2_636A4(MenuTask* task, MenuItem* item);
void fn_2_63874(MenuTask* task, MenuItem* item);
void fn_2_63A64(MenuTask* task, MenuItem* item);
void fn_2_63BEC(MenuTask* task, MenuItem* item);
void fn_2_63DBC(MenuTask* task, MenuItem* item);
void fn_2_63F58(MenuTask* task, MenuItem* item);
void fn_2_64128(MenuTask* task, MenuItem* item);
void fn_2_642F8(MenuTask* task, MenuItem* item);
void fn_2_6452C(MenuTask* task, MenuItem* item);
void fn_2_646FC(MenuTask* task, MenuItem* item);
void fn_2_648CC(void);
void fn_2_64C50(MenuTask* task, MenuItem* item);
void fn_2_64E20(void);
void fn_2_650A4(MenuTask* task, MenuItem* item);
void fn_2_65258(MenuTask* task, MenuItem* item);
void fn_2_653D4(void);
void fn_2_65648(void);
void fn_2_65850(MenuTask* task, MenuItem* item);
void fn_2_65A00(void);
void fn_2_65C84(MenuTask* task, MenuItem* item);
void fn_2_65E50(MenuTask* task, MenuItem* item);
void fn_2_66038(MenuTask* task, MenuItem* item);
void fn_2_66188(MenuTask* task, MenuItem* item);
void fn_2_6633C(void);
void fn_2_665C0(MenuTask* task, MenuItem* item);
void fn_2_6675C(MenuTask* task, MenuItem* item);
void fn_2_66884(void);
void fn_2_66AEC(MenuTask* task, MenuItem* item);
void fn_2_66CC4(MenuTask* task, MenuItem* item);
void fn_2_66E14(MenuTask* task, MenuItem* item);
void fn_2_66FC8(void);
void fn_2_671DC(MenuTask* task, MenuItem* item);
void fn_2_67390(void);
void fn_2_67588(void);
void fn_2_67780(void);
void fn_2_67B94(MenuTask* task, MenuItem* item);
void fn_2_67D48(void);
void fn_2_67FEC(MenuTask* task, MenuItem* item);
void fn_2_681A0(MenuTask* task, MenuItem* item);
void fn_2_68234(MenuTask* task, MenuItem* item);
void fn_2_68260(MenuTask* task);
void fn_2_68308(void);

#endif
