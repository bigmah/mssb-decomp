#ifndef __MENUS_AUTO_00_0005E84C_TEXT_H_
#define __MENUS_AUTO_00_0005E84C_TEXT_H_

#include "mssbTypes.h"
#include "main/file_8000F150.h"
#include "main/file_80034F50.h"
#include "main/file_80011640.h"
#include "main/file_800A6870.h"
#include "static/GameSettings.h"
#include "menus/menu_work.h"

extern MenuData* lbl_2_bss_1A824C;
extern MenuCtx* lbl_2_bss_1A8248;
extern MenuFlags* lbl_2_bss_1A823C;
extern MenuRecords* lbl_2_bss_1A8240;
extern MenuProgress* lbl_2_bss_1A8244;

s16 fn_2_53BC8(void* item);

extern s16 lbl_2_data_2E80[][3];
extern u8 lbl_2_data_20BF0[];
extern s16 lbl_2_data_20C38[];
extern s16 lbl_2_data_20C48[];
extern s16 lbl_2_data_20C58[];
extern AssetLoadInstructions lbl_2_data_20C00;

extern MenuTask* lbl_803CC1B8;

// StatOutput (main/file_80069BDC.h, which can't be included next to the
// headers above): s16 vals[6]; s16 _C; s16 _E.
struct StatOutput;
u8 fn_8006C100(s16 value);
s16 fn_8006C268(struct StatOutput* stats);


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
void fn_2_5F458(MenuTask* task, MenuItem* item);
void fn_2_5FDC4(MenuTask* task, MenuItem* item);
void fn_2_60084(MenuTask* task, MenuItem* item);
void fn_2_6020C(MenuTask* task, MenuItem* item);
void fn_2_60394(MenuTask* task, MenuItem* item);
void fn_2_6051C(MenuTask* task, MenuItem* item);
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
void fn_2_62D18(MenuTask* task, MenuItem* item);
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
void fn_2_648CC(MenuTask* task, MenuItem* item);
void fn_2_64C50(MenuTask* task, MenuItem* item);
void fn_2_64E20(MenuTask* task, MenuItem* item);
void fn_2_650A4(MenuTask* task, MenuItem* item);
void fn_2_65258(MenuTask* task, MenuItem* item);
void fn_2_653D4(MenuTask* task, MenuItem* item);
void fn_2_65648(MenuTask* task, MenuItem* item);
void fn_2_65850(MenuTask* task, MenuItem* item);
void fn_2_65A00(MenuTask* task, MenuItem* item);
void fn_2_65C84(MenuTask* task, MenuItem* item);
void fn_2_65E50(MenuTask* task, MenuItem* item);
void fn_2_66038(MenuTask* task, MenuItem* item);
void fn_2_66188(MenuTask* task, MenuItem* item);
void fn_2_6633C(MenuTask* task, MenuItem* item);
void fn_2_665C0(MenuTask* task, MenuItem* item);
void fn_2_6675C(MenuTask* task, MenuItem* item);
void fn_2_66884(MenuTask* task, MenuItem* item);
void fn_2_66AEC(MenuTask* task, MenuItem* item);
void fn_2_66CC4(MenuTask* task, MenuItem* item);
void fn_2_66E14(MenuTask* task, MenuItem* item);
void fn_2_66FC8(MenuTask* task, MenuItem* item);
void fn_2_671DC(MenuTask* task, MenuItem* item);
void fn_2_67390(MenuTask* task, MenuItem* item);
void fn_2_67588(MenuTask* task, MenuItem* item);
void fn_2_67780(MenuTask* task, MenuItem* item);
void fn_2_67B94(MenuTask* task, MenuItem* item);
void fn_2_67D48(MenuTask* task, MenuItem* item);
void fn_2_67FEC(MenuTask* task, MenuItem* item);
void fn_2_681A0(MenuTask* task, MenuItem* item);
void fn_2_68234(MenuTask* task, MenuItem* item);
void fn_2_68260(MenuTask* task);
void fn_2_68308(void);

#endif
