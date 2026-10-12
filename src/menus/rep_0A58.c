#include "menus/rep_0A58.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_8004207C.h"
#include "main/file_800527C4.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/auto_00_0005597C_text.h"
#include "menus/auto_00_00094854_text.h"
#include "menus/auto_00_00000D08_text.h"
#include "menus/rep_10C0.h"
#include "menus/rep_0B08.h"
#include "Dolphin/GX.h"
#include "string.h"
#include "musyx/musyx.h"

extern MenuCtx* lbl_2_bss_1A8248[];
extern MenuData* lbl_2_bss_1A824C[];
extern MenuProgress* lbl_2_bss_1A8244[];
extern MenuFlags* lbl_2_bss_1A823C[];
extern MenuData* lbl_2_bss_1A8234[];
extern MenuDrawArea* lbl_2_bss_1A8230[];
extern MenuData lbl_2_bss_1A8250;
extern MenuProgress lbl_80361B20;
extern MenuFlags lbl_800E877C;
extern u8 lbl_8036E548[];
extern u8 lbl_800EFBA4[];
extern u8 lbl_800EF808[];
extern MenuDef lbl_800FEF70[];
extern Menu0A58Seed lbl_2_data_1F8F0[];
extern const f32 lbl_2_rodata_AA8;

extern void fn_2_549B4(void);
extern void fn_2_5389C(void);
extern void fn_2_71F60(void);
extern void fn_2_93C64(void);
extern void fn_2_68E68(void);
extern void fn_2_47FF8(void);
extern void fn_2_47CFC(void);
extern void fn_2_46D94(s16* sel, s16* scroll, s16 count, s16 page, u32 flags);
extern void fn_8001F228(void);
extern s32 fn_80021410(void);

#define MENU_PAD(port) (&((Menu0A58Pad*)&lbl_803C77B8)[(port)])

// .text:0x00054BB0 size:0xDCC
// Scene main loop of this menu (state in lbl_803CBBCC->step).
// NONMATCHING 83%: global base registers/scheduling in the prologue, the 43-entry draw-slot copy loop
// (original keeps a ctr loop without unrolling; a for loop unrolls, so it is a do/while here),
// and lhax/lwzu addressing forms of the work-area reads.
#if NONMATCHING
void fn_2_54BB0(void) {
    MenuSceneTask0A58* task;
    Menu0A58Pad* pad;
    Menu0A58Seed* seed;
    MenuDrawEntry0A58* entry;
    Vec position;
    u16 down;
    s32 i;
    s16 v;
    s16 n;

    lbl_2_bss_1A8248[0] = (MenuCtx*)starMissionCompletionTracker;
    lbl_2_bss_1A824C[0] = &lbl_2_bss_1A8250;
    lbl_2_bss_1A8244[0] = &lbl_80361B20;
    lbl_2_bss_1A823C[0] = &lbl_800E877C;
    lbl_2_bss_1A8234[0] = &lbl_2_bss_1A8250;
    task = (MenuSceneTask0A58*)lbl_803CC1B8;
    lbl_2_bss_1A8230[0] = &lbl_2_bss_1A8250.drawArea;

    pad = MENU_PAD(lbl_2_bss_1A8250.port);
    if (pad->kind == 0xC) {
        pad->repeat |= pad->held;
    }

    switch (lbl_803CBBCC->step) {
    case 0:
        memset(&lbl_2_bss_1A8250, 0, 0x1978FC);
        fn_2_54474();
        lbl_2_bss_1A824C[0]->_197848 = 1;
        fn_2_94854(0);
        fn_2_9461C(-1);
        fn_2_94604(0);
        fn_2_93C64();
        g_d_GameSettings.StadiumID = 0;
        lbl_2_bss_1A824C[0]->port = lbl_8034E9A0.teamPort[0];
        ((MenuSceneTask0A58*)fn_800B0A5C_insertQueue(fn_2_549B4, 2))->_28 = 0;
        task->_10 = 0;
        fn_8000F4B8(0, -1, -1, -1);
        lbl_803CBBCC->step = 1;
        break;
    case 1:
        if (task->_10 == 1) {
            lbl_803CBBCC->step = 2;
        }
        break;
    case 2:
        fn_800B0A5C_insertQueue(fn_8006295C, 2);
        changeScene(1, 6);
        fn_2_6ACF4();
        fn_800B0A5C_insertQueue(fn_2_71F60, 2);
        position.z = lbl_2_rodata_AA8;
        position.y = lbl_2_rodata_AA8;
        position.x = lbl_2_rodata_AA8;
        fn_2_6AB3C(0, &position, lbl_2_rodata_AA8);
        fn_2_72054(0, 0);
        (lbl_2_bss_1A8234[0]->done) = 0;
        lbl_8034E978.menu = 0x5C;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x5C].track;
        fn_800B0A5C_insertQueue(fn_80053FE8, 0);
        task = fn_800B0A5C_insertQueue(fn_2_5389C, 0);
        task->_1C = 0;
        task->_1E = 0;
        seed = (Menu0A58Seed*)((u8*)lbl_2_data_1F8F0 + 0xCE4); // TODO type
        i = 43;
        do {
            entry = &lbl_2_bss_1A8234[0]->cells[seed->row][seed->column];
            entry->draw = seed->draw;
            entry->column = seed->column;
            entry->_0A = seed->_06;
            entry->row = seed->row;
            entry->_0E = seed->_0A;
            entry->_10 = seed->_0C;
            seed++;
        } while (--i != 0);
        (lbl_2_bss_1A8234[0]->layerFlags[0][0]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[0][1]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[0][2]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[0][3]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[0][6]) = 1;
        (lbl_2_bss_1A824C[0]->_1976F6) = 0;
        (lbl_2_bss_1A824C[0]->_1976F4) = 0;
        lbl_803CBBCC->step = 3;
        break;
    case 3:
        if (lbl_8037169C.done) {
            (lbl_2_bss_1A8234[0]->layerFlags[1][0]) = 1;
            (lbl_2_bss_1A8234[0]->layerFlags[1][1]) = 1;
            (lbl_2_bss_1A8234[0]->layerFlags[1][2]) = 1;
            lbl_2_bss_1A8234[0]->timer = 0x10;
            lbl_803CBBCC->step = 4;
        }
        break;
    case 4:
        v = (lbl_2_bss_1A8234[0]->timer)--;
        if (v == 0) {
            (lbl_2_bss_1A8234[0]->layerFlags[1][4]) = 1;
            lbl_803CBBCC->step = 5;
        }
        break;
    case 5:
        pad = MENU_PAD(lbl_2_bss_1A8250.port);
        if (pad->repeat == 1) {
            (lbl_2_bss_1A824C[0]->_1976F6) = (lbl_2_bss_1A824C[0]->_1976F4);
            (lbl_2_bss_1A824C[0]->_1976F4) = ((lbl_2_bss_1A824C[0]->_1976F4) + 10) % 11;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (pad->repeat == 2) {
            (lbl_2_bss_1A824C[0]->_1976F6) = (lbl_2_bss_1A824C[0]->_1976F4);
            (lbl_2_bss_1A824C[0]->_1976F4) = ((lbl_2_bss_1A824C[0]->_1976F4) + 1) % 11;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD((s8)(u8)lbl_2_bss_1A824C[0]->port)->down;
        if (down & 0x100) {
            lbl_803CBBCC->step = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_803CBBCC->step = 8;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 6:
        (lbl_2_bss_1A8234[0]->layerFlags[8][1]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][2]) = 1;
        lbl_803CBBCC->step = 7;
        lbl_2_bss_1A8234[0]->timer = 0x10;
        break;
    case 7:
        v = (lbl_2_bss_1A8234[0]->timer)--;
        if (v == 0) {
            lbl_803CBBCC->step = 9;
        }
        break;
    case 8:
        lbl_2_bss_1A8234[0]->timer = 0x14;
        (lbl_2_bss_1A8234[0]->layerFlags[8][0]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][1]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][2]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][4]) = 1;
        lbl_8034E978._05 = 1;
        lbl_803CBBCC->step = 0x10;
        break;
    case 9:
        fn_2_72054(0, 0x11);
        (lbl_2_bss_1A824C[0]->_19772E) = 0xE7;
        n = ((s16*)((u8*)lbl_2_data_1F8F0 + 0x664))[(lbl_2_bss_1A824C[0]->_1976F4)]; // TODO type
        (lbl_2_bss_1A824C[0]->_197700) = n;
        (lbl_2_bss_1A824C[0]->_1976FE) = n;
        (lbl_2_bss_1A824C[0]->_1976FC) = 0;
        (lbl_2_bss_1A824C[0]->_1976FA) = 0;
        lbl_2_bss_1A824C[0]->_197822 = 0;
        (lbl_2_bss_1A8234[0]->layerFlags[1][1]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[1][3]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[1][6]) = 1;
        lbl_2_bss_1A8234[0]->timer = 0x10;
        lbl_803CBBCC->step = 0xA;
        break;
    case 10:
        v = (lbl_2_bss_1A8234[0]->timer)--;
        if (v == 0) {
            (lbl_2_bss_1A8234[0]->layerFlags[1][5]) = 1;
            lbl_803CBBCC->step = 0xC;
        }
        break;
    case 12:
        pad = MENU_PAD(lbl_2_bss_1A8250.port);
        if (pad->repeat == 1) {
            (lbl_2_bss_1A824C[0]->_1976F6) = (lbl_2_bss_1A824C[0]->_1976F4);
            (lbl_2_bss_1A824C[0]->_1976F4) = ((lbl_2_bss_1A824C[0]->_1976F4) + 10) % 11;
            (lbl_2_bss_1A824C[0]->_197700) = (lbl_2_bss_1A824C[0]->_1976FE);
            (lbl_2_bss_1A824C[0]->_1976FC) = (lbl_2_bss_1A824C[0]->_1976FA);
            (lbl_2_bss_1A824C[0]->_1976FE) = ((s16*)((u8*)lbl_2_data_1F8F0 + 0x664))[(lbl_2_bss_1A824C[0]->_1976F4)];
            (lbl_2_bss_1A824C[0]->_1976FA) = 0;
            lbl_2_bss_1A824C[0]->_197822 = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            (lbl_2_bss_1A8234[0]->layerFlags[3][6]) = 1;
            lbl_803CBBCC->step = 0xF;
        } else if (pad->repeat == 2) {
            (lbl_2_bss_1A824C[0]->_1976F6) = (lbl_2_bss_1A824C[0]->_1976F4);
            (lbl_2_bss_1A824C[0]->_1976F4) = ((lbl_2_bss_1A824C[0]->_1976F4) + 1) % 11;
            (lbl_2_bss_1A824C[0]->_197700) = (lbl_2_bss_1A824C[0]->_1976FE);
            (lbl_2_bss_1A824C[0]->_1976FC) = (lbl_2_bss_1A824C[0]->_1976FA);
            (lbl_2_bss_1A824C[0]->_1976FE) = ((s16*)((u8*)lbl_2_data_1F8F0 + 0x664))[(lbl_2_bss_1A824C[0]->_1976F4)];
            (lbl_2_bss_1A824C[0]->_1976FA) = 0;
            lbl_2_bss_1A824C[0]->_197822 = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            (lbl_2_bss_1A8234[0]->layerFlags[3][6]) = 1;
            lbl_803CBBCC->step = 0xF;
        } else if (pad->repeat == 8 || pad->repeat == 4) {
            (lbl_2_bss_1A824C[0]->_197700) = (lbl_2_bss_1A824C[0]->_1976FE);
            (lbl_2_bss_1A824C[0]->_1976FC) = (lbl_2_bss_1A824C[0]->_1976FA);
            fn_2_46D94(&(lbl_2_bss_1A824C[0]->_1976FA), &(lbl_2_bss_1A824C[0]->_1976FE), (lbl_2_bss_1A824C[0]->_19772E), 5, 9);
            (lbl_2_bss_1A824C[0]->_1976F4) = fn_2_5597C();
            lbl_2_bss_1A824C[0]->_197822 = 0;
            (lbl_2_bss_1A8234[0]->layerFlags[3][6]) = 1;
            lbl_803CBBCC->step = 0xF;
        } else {
            down = pad->down;
            if ((down & 0x100) &&
                (n = ((s16*)((u8*)lbl_2_data_1F8F0 + 0x494))[(lbl_2_bss_1A824C[0]->_1976FA) + (lbl_2_bss_1A824C[0]->_1976FE)]) >= 2) {
                *(u8*)&lbl_2_bss_1A8250._197822 = ((s8)lbl_2_bss_1A8250._197822 + 1) % n;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                (lbl_2_bss_1A8234[0]->layerFlags[6][6]) = 1;
            } else if (down & 0x200) {
                lbl_803CBBCC->step = 0xD;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        }
        break;
    case 13:
        (lbl_2_bss_1A8234[0]->layerFlags[8][1]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][3]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][5]) = 1;
        (lbl_2_bss_1A8234[0]->layerFlags[8][6]) = 1;
        fn_2_72054(0, 0x12);
        lbl_2_bss_1A8234[0]->timer = 0x10;
        lbl_803CBBCC->step = 0xE;
        break;
    case 14:
        v = (lbl_2_bss_1A8234[0]->timer)--;
        if (v == 0) {
            (lbl_2_bss_1A8234[0]->layerFlags[1][1]) = 1;
            (lbl_2_bss_1A8234[0]->layerFlags[1][2]) = 1;
            lbl_2_bss_1A8234[0]->timer = 0x10;
            lbl_803CBBCC->step = 4;
        }
        break;
    case 15:
        lbl_803CBBCC->step = 0xC;
        break;
    case 16:
        v = (lbl_2_bss_1A8234[0]->timer)--;
        if (v == 0) {
            fn_80062948();
            changeScene(3, 6);
            lbl_803CBBCC->step = 0x11;
        }
        break;
    case 17:
        if (lbl_8037169C._13) {
            lbl_8036E548[0x307A] = 0;
            (lbl_2_bss_1A8234[0]->done) = 1;
            lbl_2_bss_1A8230[0]->_32A86 = 1;
            lbl_803CBBCC->step = 0x12;
        }
        break;
    case 18:
        lbl_2_bss_1A8250._1972BC = 1;
        fn_2_4E7EC();
        fn_8001F228();
        fn_80021410();
        fn_800ACFB0(*(void**)(lbl_800EF808 + 0x14)); // TODO type
        fn_80035B50(0xA);
        if (lbl_80366B18.tables[2] != NULL) {
            fn_800ACFB0(lbl_80366B18.tables[2]);
            lbl_80366B18.tables[2] = NULL;
        }
        lbl_2_bss_1A823C[0]->_34 = 0;
        fn_2_11A0(5);
        break;
    case 19:
        ((MenuSceneTask0A58*)fn_800B0A5C_insertQueue(fn_2_535B0, 2))->_28 = 0;
        task->_10 = 0;
        lbl_803CBBCC->step = 0x14;
        break;
    case 20:
        if (task->_10 == 1) {
            lbl_803CBBCC->step = 0xC;
        }
        break;
    }
    if (lbl_8036E548[0x307A] == 2) {
        if (lbl_2_bss_1A8248[0]->_44F2 != 4) {
            fn_2_68E68();
        }
        fn_2_47FF8();
        if (lbl_2_bss_1A8248[0]->_44F2 != 4) {
            fn_2_47CFC();
        }
    }
    GXSetZCompLoc(GX_FALSE);
}
#endif
