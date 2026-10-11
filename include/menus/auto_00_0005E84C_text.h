#ifndef __MENUS_AUTO_00_0005E84C_TEXT_H_
#define __MENUS_AUTO_00_0005E84C_TEXT_H_

#include "mssbTypes.h"
#include "main/file_8000F150.h"
#include "main/file_80034F50.h"

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

s16 fn_2_53BC8(void* item);

void fn_2_5E84C(void);
void fn_2_5EB78(void);
void fn_2_5ED3C(void);
void fn_2_5EE34(void);
void fn_2_5EEBC(void);
void fn_2_5F08C(void);
void fn_2_5F2A8(void);
void fn_2_5F458(void);
void fn_2_5FDC4(void);
void fn_2_60084(MenuTask* task, MenuItem* item);
void fn_2_6020C(MenuTask* task, MenuItem* item);
void fn_2_60394(MenuTask* task, MenuItem* item);
void fn_2_6051C(void);
void fn_2_607DC(void);
void fn_2_60968(MenuTask* task, MenuItem* item);
void fn_2_60AF0(MenuTask* task, MenuItem* item);
void fn_2_60C78(void);
void fn_2_60DF4(MenuTask* task, MenuItem* item);
void fn_2_60F7C(MenuTask* task, MenuItem* item);
void fn_2_61104(void);
void fn_2_612A8(void);
void fn_2_61468(void);
void fn_2_61644(void);
void fn_2_61794(MenuTask* task, MenuItem* item);
void fn_2_61948(void);
void fn_2_61B6C(void);
void fn_2_61D90(void);
void fn_2_61F5C(MenuTask* task, MenuItem* item);
void fn_2_62110(void);
void fn_2_623AC(void);
void fn_2_625B0(void);
void fn_2_627F4(void);
void fn_2_62A38(void);
void fn_2_62D18(void);
void fn_2_63570(void);
void fn_2_636A4(MenuTask* task, MenuItem* item);
void fn_2_63874(void);
void fn_2_63A64(void);
void fn_2_63BEC(MenuTask* task, MenuItem* item);
void fn_2_63DBC(void);
void fn_2_63F58(MenuTask* task, MenuItem* item);
void fn_2_64128(MenuTask* task, MenuItem* item);
void fn_2_642F8(void);
void fn_2_6452C(MenuTask* task, MenuItem* item);
void fn_2_646FC(MenuTask* task, MenuItem* item);
void fn_2_648CC(void);
void fn_2_64C50(MenuTask* task, MenuItem* item);
void fn_2_64E20(void);
void fn_2_650A4(MenuTask* task, MenuItem* item);
void fn_2_65258(void);
void fn_2_653D4(void);
void fn_2_65648(void);
void fn_2_65850(void);
void fn_2_65A00(void);
void fn_2_65C84(void);
void fn_2_65E50(void);
void fn_2_66038(void);
void fn_2_66188(MenuTask* task, MenuItem* item);
void fn_2_6633C(void);
void fn_2_665C0(void);
void fn_2_6675C(void);
void fn_2_66884(void);
void fn_2_66AEC(void);
void fn_2_66CC4(void);
void fn_2_66E14(MenuTask* task, MenuItem* item);
void fn_2_66FC8(void);
void fn_2_671DC(MenuTask* task, MenuItem* item);
void fn_2_67390(void);
void fn_2_67588(void);
void fn_2_67780(void);
void fn_2_67B94(MenuTask* task, MenuItem* item);
void fn_2_67D48(void);
void fn_2_67FEC(MenuTask* task, MenuItem* item);
void fn_2_681A0(void);
void fn_2_68234(void);
void fn_2_68260(void);
void fn_2_68308(void);

#endif
