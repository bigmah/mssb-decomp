#include "menus/auto_00_0008E6A4_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8004207C.h"
#include "main/file_800527C4.h"
#include "main/file_80069BDC.h"
#include "main/file_80008E00.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/auto_00_00000D08_text.h"
#include "menus/auto_00_00094854_text.h"
#include "menus/rep_10C0.h"
#include "menus/menu_asset.h"
#include "Dolphin/os.h"
extern u8 lbl_803C6CF8[]; // TODO type: ARAMLoader (main/file_800A6870.h); idle at 0x715

// Functions of other menus units without a header prototype yet.
extern void fn_2_2FC0(u8, s32, s32);
extern void fn_2_8D270(u8 a);
extern void fn_2_8DCD8(void);
extern void fn_2_48DB4(void);
extern void fn_2_93C64(void);
extern void fn_8003F23C(void); // main/file_8003A688.h

extern MenuActorMgr* lbl_2_bss_340140;
extern void* lbl_2_bss_3401BC;
extern u8 lbl_2_bss_3401C0[0x74];
extern MenuScreenState lbl_2_bss_340234;
extern SceneTask* lbl_2_bss_B2C0; // confirm dialog task (fn_8006C0D0)
extern u8* lbl_2_bss_1A824C[];
extern u8* lbl_2_bss_1A8248[];
extern MenuActorMgr lbl_8036E548;
extern u8 lbl_800E869C[0x20];
extern u8 lbl_2_data_3CD0[0x10];

// TODO type: lbl_2_bss_1A824C[0] work area
#define MENU_ACTOR_COUNT (*(s16*)(lbl_2_bss_1A824C[0] + 0x197746))
#define MENU_STADIUM (*(s16*)(lbl_2_bss_1A824C[0] + 0x197706))

// .text:0x0008E6A4 size:0x200
// NONMATCHING 93.8%: actor loop induction registers rotated (i/actor/offset; docs/patterns/loops.md)
#if NONMATCHING
void fn_2_8E6A4(void) {
    s32 i;
    MenuLoadTask* parent;
    MenuLoadTask* task = (MenuLoadTask*)lbl_803CC1B8;

    switch (task->step) {
    case 0:
        lbl_2_bss_340140 = &lbl_8036E548;
        task->count = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        task->step = 1;
        break;
    case 1:
        lbl_2_bss_340140->actors[task->count].aram =
            ARAMTransfer(&lbl_2_data_2FA60[lbl_2_data_2FDC0[task->kind]], 0, 0, 0);
        task->count++;
        task->step = 2;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            task->step = 5;
        }
        break;
    case 5:
        for (i = 0; i < MENU_ACTOR_COUNT; i++) {
            lbl_2_bss_340140->active[i] = &lbl_8036E548.actors[i];
            lbl_2_bss_340140->active[i]->_255 = i;
            lbl_2_bss_340140->active[i]->_254 = i;
            lbl_2_bss_340140->active[i]->_252 = lbl_800E869C[MENU_STADIUM];
            fn_2_8D270(i);
        }
        task->step = 6;
        break;
    case 6:
        lbl_2_bss_340140->_307A = 2;
        parent = ((MenuLoadTask*)lbl_803CC1B8)->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif

// .text:0x0008E8A4 size:0x1DC
// NONMATCHING 92.3%: actor loop induction registers rotated (i/actor/offset; docs/patterns/loops.md)
#if NONMATCHING
void fn_2_8E8A4(void) {
    s32 i;
    MenuLoadTask* parent;
    MenuLoadTask* task = (MenuLoadTask*)lbl_803CC1B8;

    switch (task->step) {
    case 0:
        lbl_2_bss_340140 = &lbl_8036E548;
        task->count = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        task->step = 1;
        break;
    case 1:
        lbl_2_bss_340140->actors[task->count].aram = ARAMTransfer(&lbl_2_data_2F990[task->kind], 0, 0, 0);
        task->count++;
        task->step = 2;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            task->step = 5;
        }
        break;
    case 5:
        for (i = 0; i < MENU_ACTOR_COUNT; i++) {
            lbl_2_bss_340140->active[i] = &lbl_8036E548.actors[i];
            lbl_2_bss_340140->active[i]->_255 = i;
            lbl_2_bss_340140->active[i]->_254 = i;
            lbl_2_bss_340140->active[i]->_252 = 0x1C;
            fn_2_8D270(i);
        }
        task->step = 6;
        break;
    case 6:
        lbl_2_bss_340140->_307A = 2;
        parent = ((MenuLoadTask*)lbl_803CC1B8)->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif

// .text:0x0008EA80 size:0x2CC
// NONMATCHING 95.7%: actor loop induction registers rotated (i/actor/offset; docs/patterns/loops.md)
#if NONMATCHING
void fn_2_8EA80(void) {
    s32 i;
    MenuLoadTask* parent;
    MenuLoadTask* task = (MenuLoadTask*)lbl_803CC1B8;

    switch (task->step) {
    case 0:
        lbl_2_bss_340140 = &lbl_8036E548;
        lbl_2_bss_3401BC = lbl_2_bss_3401C0;
        task->count = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        task->step = 1;
        break;
    case 1:
        // TODO type: lbl_2_bss_1A8248[0] + 0x441C is the selected stadium/file index
        lbl_2_bss_340140->actors[task->count].aram =
            ARAMTransfer(&lbl_2_data_2F990[lbl_2_bss_1A8248[0][0x441C]], 0, 0, 0);
        task->count++;
        task->step = 2;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            task->step = 3;
        }
        break;
    case 3:
        lbl_2_bss_340140->actors[task->count].aram = ARAMTransfer(&lbl_2_data_2F990[task->count + 5], 0, 0, 0);
        task->count++;
        task->step = 4;
        break;
    case 4:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            if (task->count == MENU_ACTOR_COUNT) {
                task->step = 5;
            } else {
                task->step = 3;
            }
        }
        break;
    case 5:
        for (i = 0; i < MENU_ACTOR_COUNT; i++) {
            lbl_2_bss_340140->active[i] = &lbl_8036E548.actors[i];
            lbl_2_bss_340140->active[i]->_255 = i;
            lbl_2_bss_340140->active[i]->_254 = i;
            lbl_2_bss_340140->active[i]->_252 = lbl_2_data_3CD0[i];
            fn_2_8D270(i);
        }
        task->step = 6;
        break;
    case 6:
        task->step = 7;
        break;
    case 7:
        fn_2_94854(0xB);
        fn_2_9461C(0);
        fn_2_94604(0);
        fn_2_94634(1);
        fn_2_93C64();
        lbl_2_bss_340140->_307A = 2;
        parent = ((MenuLoadTask*)lbl_803CC1B8)->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif
