#ifndef __MENUS_AUTO_00_0005597C_TEXT_H_
#define __MENUS_AUTO_00_0005597C_TEXT_H_

#include "mssbTypes.h"
#include "menus/rep_0788.h"
#include "main/file_80069BDC.h"

// 8-byte record (value + two shorts) used by the menu save tables.
typedef struct MenuRec {
    /*0x0*/ s32 a;
    /*0x4*/ s16 b;
    /*0x6*/ s16 c;
} MenuRec;

typedef struct MenuRecSet {
    /*0x00*/ MenuRec head[5];
    /*0x28*/ MenuRec groups[7][5];
} MenuRecSet; // size: 0x140

// Data pointed to by lbl_2_bss_1A8240 (only the parts used here).
typedef struct MenuSaveData {
    /*0x000*/ MenuRecSet recs;
    /*0x140*/ StatInput stats[32];
    /*0x400*/ s8 vals[32];
} MenuSaveData;

// The scene task in lbl_803CC1B8 is a MenuTask (menus/menu_work.h).

s32 fn_2_5597C(void);
void fn_2_55A40(void);
void fn_2_55AD4(MenuTableContext* menu, MenuItemState* item);
void fn_2_55C5C(MenuTableContext* menu, MenuItemState* item);
void fn_2_55DD8(MenuTableContext* menu, MenuItemState* item);
void fn_2_55FD8(MenuTableContext* menu, MenuItemState* item);
void fn_2_56160(MenuTableContext* menu, MenuItemState* item);
void fn_2_563C0(MenuTableContext* menu, MenuItemState* item);
void fn_2_56688(MenuTableContext* menu, MenuItemState* item);
void fn_2_5699C(MenuTableContext* menu, MenuItemState* item);
void fn_2_56C34(MenuTableContext* menu, MenuItemState* item);
void fn_2_56E8C(MenuTableContext* menu, MenuItemState* item);
void fn_2_570E4(MenuTableContext* menu, MenuItemState* item);
void fn_2_57294(MenuTableContext* menu, MenuItemState* item);
void fn_2_5754C(MenuTableContext* menu, MenuItemState* item);
void fn_2_57724(MenuTableContext* menu, MenuItemState* item);
void fn_2_5786C(MenuTableContext* menu, MenuItemState* item);
void fn_2_579B4(MenuTableContext* menu, MenuItemState* item);
void fn_2_57BF8(MenuTableContext* menu, MenuItemState* item);
void fn_2_57F50(MenuTableContext* menu, MenuItemState* item);
void fn_2_58098(MenuTableContext* menu, MenuItemState* item);
void fn_2_581E0(MenuTableContext* menu, MenuItemState* item);
void fn_2_58328(MenuTableContext* menu, MenuItemState* item);
void fn_2_58470(MenuTableContext* menu, MenuItemState* item);
void fn_2_58510(MenuTableContext* menu, MenuItemState* item);
void fn_2_5853C(void);
void fn_2_587F8(void);

#endif
