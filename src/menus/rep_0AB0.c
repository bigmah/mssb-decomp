#include "menus/rep_0AB0.h"
#include <string.h>
#include "game/UnknownHomes_Game.h"
#include "main/file_8000F150.h"
#include "main/file_8004207C.h"
#include "main/file_800527C4.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/rep_0788.h"
#include "menus/auto_00_0005597C_text.h"
#include "menus/auto_00_00013BA4_text.h"
#include "menus/rep_08E8.h"
#include "menus/rep_0B08.h"
#include "menus/rep_10C0.h"
#include "menus/auto_00_00071EC4_text.h"
#include "menus/auto_00_0008E6A4_text.h"
#include "menus/auto_00_00094854_text.h"
#include "menus/auto_00_00092394_text.h"
#include "menus/rep_1028.h"
#include "Dolphin/GX/GXPixel.h"
#include "static/GameSettings.h"

extern u32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);

extern MenuWorkBuf* lbl_2_bss_1A8234;
extern MenuSceneState* lbl_2_bss_1A823C;
extern MenuWorkBuf* lbl_2_bss_1A824C;
extern UnlockFlags* lbl_2_bss_1A8244;
extern MenuSaveView* lbl_2_bss_1A8248;
extern s8 lbl_2_bss_A168;
extern MenuSaveProgress lbl_80354768;
extern MenuCharMgr lbl_8036E548;
extern s32 lbl_2_data_35A0[]; // per character id
extern s16 lbl_2_data_296B8[6 * 6]; // character grid: id per [row * 6 + column]
extern u8 lbl_800E869C[]; // grid id -> character id
extern s8 lbl_2_bss_A169;
extern void fn_2_93C64(void);
extern void fn_2_5EB78(void); // menus/auto_00_0005E84C_text.h (clashes over lbl_803CC1B8)
extern void fn_2_5ED3C(void);
extern void fn_2_68E68(void);
extern void fn_2_8AEE0(void);
extern void fn_2_8DFB0(void);
extern void fn_8001F228(void);
extern MenuCharMgr* lbl_2_bss_340140;
extern MenuCharLayout* lbl_2_bss_1A8240;
extern MenuWorkBuf lbl_2_bss_1A8250;
extern MenuDrawArea* lbl_2_bss_1A8230;
extern void* lbl_2_bss_3401BC;
extern u8 lbl_2_bss_3401C0[];
extern UnlockFlags lbl_80361B20;
extern MenuCharLayout lbl_803616CC;
extern MenuSceneState lbl_800E877C;
extern s16 lbl_2_data_20C48[]; // group order for MenuWorkBuf.groups
extern void fn_2_71F60(void);
extern void fn_2_9257C(void);
extern void fn_80035B50(int id);
extern void fn_800ACFB0(void* block);
extern void fn_2_11A0(u16 value);
extern u8 lbl_2_bss_33FBF0[]; // per actor
// lbl_803CC1B8 (SceneTask*, main/file_80069BDC.h) is the running menu task.
#define CUR_TASK ((MenuScreenTask*)lbl_803CC1B8)
extern InitEntry lbl_2_data_20C68[];
extern InitEntry lbl_2_data_268A8[];
extern MenuDef lbl_800FEF70[];
extern u8 lbl_800EFBA4[]; // sound effect volumes

// Declared as an array (not static/UnknownHomes_Static.h's lbl_803C77B8_s) so pad
// lookups schedule like the original.
extern PadState lbl_803C77B8[4];
#define MENU_PADS lbl_803C77B8
#define MENU_PAD (MENU_PADS[lbl_2_bss_1A824C->port])

// .text:0x0005979C size:0x55C
void fn_2_5979C(void) {
    MenuScreenTask* task = CUR_TASK;
    s32 i;
    switch (task->step) {
    case 0:
        lbl_2_bss_1A824C->subSelection = 0;
        lbl_2_bss_1A824C->selection = 0;
        task->step = 1;
        break;
    case 1:
        fn_2_1FFC4(4);
        for (i = 0; i < 4; i++) {
            fn_2_1FF10(i);
            switch (i) {
            case 0:
                if (lbl_2_bss_1A824C->selection == i &&
                    ((MENU_PAD.down & 0x100) || MENU_PADS[0].sticks.substickY > 0x32)) {
                    task->step = 4;
                }
                break;
            case 1:
                if (lbl_2_bss_1A824C->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A824C->_19784A = 1;
                    lbl_2_bss_1A824C->_197846 = 0;
                    lbl_2_bss_1A824C->_197845 = 1;
                    lbl_2_bss_A169 = 1;
                    task->step = 2;
                }
                break;
            case 2:
                if (lbl_2_bss_1A824C->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A824C->_19784A = 1;
                    lbl_2_bss_1A824C->_197846 = 2;
                    task->step = 3;
                }
                break;
            case 3:
                if (lbl_2_bss_1A824C->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A8244->_F4 ^= 1;
                    fn_2_5EB78();
                }
                break;
            case 4:
                break;
            }
        }
        if ((MENU_PAD.down & 0x200) || MENU_PADS[0].sticks.substickY > 0x32) {
            task->step = 4;
        }
        break;
    case 2:
        fn_2_1FF14(1);
        for (i = 0; i < 1; i++) {
            fn_2_1FF0C(i);
            switch (i) {
            case 0:
                if (lbl_2_bss_1A824C->subSelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 0x200) {
                        lbl_2_bss_1A824C->_19784A = 0;
                        lbl_2_bss_1A824C->_197846 = 0;
                        lbl_2_bss_1A824C->subSelection = 0;
                        lbl_2_bss_1A824C->_197845 = 0;
                        task->step = 1;
                    } else if (down & 0x100) {
                        lbl_2_bss_A169 ^= 1;
                    } else if (down & 0x1000) {
                        fn_2_93C64();
                    }
                    if (lbl_2_bss_A169 != 0) {
                        fn_2_489DC();
                    }
                }
                break;
            }
        }
        break;
    case 3:
        fn_2_1FF14(1);
        for (i = 0; i < 1; i++) {
            fn_2_1FF0C(i);
            switch (i) {
            case 0:
                if (lbl_2_bss_1A824C->subSelection == i) {
                    PadState* pad = &MENU_PAD;
                    u16 down = pad->down;
                    if (down & 0x200) {
                        lbl_2_bss_1A824C->_19784A = 0;
                        lbl_2_bss_1A824C->_197846 = 0;
                        lbl_2_bss_1A824C->subSelection = 0;
                        task->step = 1;
                    } else if ((down & 0x40) && (pad->held & 0x100)) {
                        lbl_2_bss_1A824C->modelIndex = (lbl_2_bss_1A824C->modelIndex + 28) % 29;
                    } else if ((down & 0x20) && (pad->held & 0x100)) {
                        lbl_2_bss_1A824C->modelIndex = (lbl_2_bss_1A824C->modelIndex + 1) % 29;
                    } else {
                        u16 repeat = pad->repeat;
                        if (repeat & 0x800) {
                            lbl_2_bss_1A8248->modelParams[lbl_2_bss_1A824C->modelIndex].value -= 0.1f;
                        } else if (repeat & 0x400) {
                            lbl_2_bss_1A8248->modelParams[lbl_2_bss_1A824C->modelIndex].value += 0.1f;
                        }
                    }
                }
                break;
            }
        }
        break;
    case 4: {
        MenuScreenTask* parent = task->parent;
        parent->signal = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
    }
}

// .text:0x00059CF8 size:0x52C
void fn_2_59CF8(void) {
    MenuScreenTask* task = CUR_TASK;
    MenuSaveProgress* save = &lbl_80354768;
    s32 i;
    s32 j;
    switch (task->step) {
    case 0:
        lbl_2_bss_1A824C->subSelection = 0;
        lbl_2_bss_1A824C->selection = 0;
        task->step = 1;
        break;
    case 1:
        fn_2_1FFC4(3);
        for (i = 0; i < 3; i++) {
            fn_2_1FF10(i);
            switch (i) {
            case 0:
                if (lbl_2_bss_1A824C->selection == i &&
                    ((MENU_PAD.down & 0x100) || MENU_PADS[0].sticks.substickY > 0x32)) {
                    task->step = 3;
                }
                break;
            case 1:
                if (lbl_2_bss_1A824C->selection == i && (MENU_PAD.down & 0x102)) {
                    lbl_2_bss_1A824C->_19784A = 1;
                    lbl_2_bss_1A824C->_197846 = 0;
                    lbl_2_bss_1A824C->_197845 = 1;
                    lbl_2_bss_A168 = 1;
                    task->step = 2;
                }
                break;
            case 2:
                if (lbl_2_bss_1A824C->selection == i && (MENU_PAD.down & 3)) {
                    if (save->unlocked[0] == 0) {
                        for (j = 0; j < 0x36; j++) {
                            save->unlocked[j] = 1;
                        }
                    } else if (save->unlocked[0] == 1) {
                        for (j = 0; j < 0x36; j++) {
                            save->unlocked[j] = 0;
                        }
                    }
                }
                break;
            }
        }
        if ((MENU_PAD.down & 0x200) || MENU_PADS[0].sticks.substickY > 0x32) {
            task->step = 3;
        }
        break;
    case 2:
        fn_2_1FF14(1);
        for (i = 0; i < 1; i++) {
            fn_2_1FF0C(i);
            switch (i) {
            case 0:
                if (lbl_2_bss_1A824C->subSelection == i) {
                    u16 down = MENU_PAD.down;
                    if (down & 0x200) {
                        lbl_2_bss_1A824C->_19784A = 0;
                        lbl_2_bss_1A824C->_197846 = 0;
                        lbl_2_bss_1A824C->subSelection = 0;
                        lbl_2_bss_1A824C->_197845 = 0;
                        task->step = 1;
                    } else if (down & 0x100) {
                        lbl_2_bss_A168 ^= 1;
                    } else if (down & 0x1000) {
                        fn_2_93C64();
                    }
                    if (lbl_2_bss_A168 != 0) {
                        fn_2_489DC();
                    }
                }
                break;
            }
        }
        break;
    case 3: {
        MenuScreenTask* parent = task->parent;
        parent->signal = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
    }
}

// .text:0x0005A224 size:0xC30
void fn_2_5A224(void) {
    MenuSaveProgress* save = &lbl_80354768;
    MenuScreenTask* task = CUR_TASK;
    switch (lbl_2_bss_1A823C->state) {
    case 0:
        lbl_2_bss_1A824C->_197848 = 2;
        lbl_2_bss_1A8234->layerFlags[1][9] = 1;
        lbl_8034E978.menu = 0x54;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x54].track;
        lbl_2_bss_1A823C->state = 1;
        break;
    case 1:
        lbl_2_bss_1A824C->charId = 0;
        lbl_2_bss_1A824C->gridX = 1;
        lbl_2_bss_1A824C->gridY = 0;
        fn_2_94854(lbl_2_data_35A0[lbl_2_bss_1A824C->charId] + 2);
        fn_2_9461C(-1);
        fn_2_94604(0);
        fn_2_93C64();
        lbl_2_bss_1A823C->state = 2;
        break;
    case 2: {
        u16 down;
        if (MENU_PAD.repeat & 1) {
            lbl_2_bss_1A824C->gridX--;
            if (lbl_2_bss_1A824C->gridX == 0 && (lbl_2_bss_1A824C->gridY == 0 || lbl_2_bss_1A824C->gridY == 5)) {
                lbl_2_bss_1A824C->gridX = 4;
            } else if (lbl_2_bss_1A824C->gridX < 0) {
                lbl_2_bss_1A824C->gridX = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (MENU_PAD.repeat & 2) {
            lbl_2_bss_1A824C->gridX++;
            if (lbl_2_bss_1A824C->gridX == 5 && (lbl_2_bss_1A824C->gridY == 0 || lbl_2_bss_1A824C->gridY == 5)) {
                lbl_2_bss_1A824C->gridX = 1;
            } else if (lbl_2_bss_1A824C->gridX > 5) {
                lbl_2_bss_1A824C->gridX = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        if (MENU_PAD.repeat & 8) {
            lbl_2_bss_1A824C->gridY--;
            if (lbl_2_bss_1A824C->gridY == 0 && (lbl_2_bss_1A824C->gridX == 0 || lbl_2_bss_1A824C->gridX == 5)) {
                lbl_2_bss_1A824C->gridY = 4;
            } else if (lbl_2_bss_1A824C->gridY < 0) {
                lbl_2_bss_1A824C->gridY = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (MENU_PAD.repeat & 4) {
            lbl_2_bss_1A824C->gridY++;
            if (lbl_2_bss_1A824C->gridY == 5 && (lbl_2_bss_1A824C->gridX == 0 || lbl_2_bss_1A824C->gridX == 5)) {
                lbl_2_bss_1A824C->gridY = 1;
            } else if (lbl_2_bss_1A824C->gridY > 5) {
                lbl_2_bss_1A824C->gridY = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        lbl_2_bss_1A824C->charId = lbl_2_data_296B8[lbl_2_bss_1A824C->gridX + lbl_2_bss_1A824C->gridY * 6];
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (save->unlocked[lbl_800E869C[lbl_2_bss_1A824C->charId]] != 0) {
                lbl_2_bss_1A8234->timer = 0x10;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                lbl_2_bss_1A823C->state = 13;
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (down & 0x200) {
            lbl_2_bss_1A824C->tab = 0;
            lbl_2_bss_1A823C->state = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 5:
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 6;
        break;
    case 6:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 7;
        }
        break;
    case 7: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (lbl_2_bss_1A824C->tab == 0) {
                lbl_2_bss_1A823C->state = 11;
            } else {
                lbl_2_bss_1A823C->state = 8;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 22;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 8:
        lbl_2_bss_1A8234->layerFlags[8][9] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x24;
        lbl_2_bss_1A823C->state = 9;
        break;
    case 9:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 10;
        }
        break;
    case 10:
        lbl_2_bss_1A8234->layerFlags[3][2] = 1;
        switch (lbl_2_bss_1A824C->tab) {
        case 0:
            lbl_2_bss_1A824C->mode = 5;
            lbl_2_bss_1A823C->state = 11;
            break;
        case 1:
            lbl_2_bss_1A824C->mode = 0;
            CUR_TASK->func = fn_2_5D26C;
            break;
        case 2:
            lbl_2_bss_1A824C->mode = 2;
            CUR_TASK->func = fn_2_5C5B8;
            break;
        case 3:
            lbl_2_bss_1A824C->mode = 3;
            CUR_TASK->func = fn_2_5AFB0;
            break;
        }
        lbl_2_bss_1A823C->state = 0;
        break;
    case 11:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 12;
        break;
    case 12:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 13:
        lbl_2_bss_1A823C->state = 14;
        break;
    case 14: {
        MenuScreenTask* child;
        lbl_2_bss_1A824C->_197746 = 1;
        child = fn_800B0A5C_insertQueue(fn_2_8E6A4, 2);
        child->step = 0;
        child->arg = lbl_2_bss_1A824C->charId;
        task->signal = 0;
        lbl_2_bss_1A823C->state = 15;
        break;
    }
    case 15:
        if (task->signal == 1) {
            lbl_2_bss_1A823C->state = 16;
        }
        break;
    case 16:
        lbl_2_bss_1A8234->timer = 0x14;
        lbl_2_bss_1A8234->layerFlags[1][10] = 1;
        fn_2_94854(lbl_2_data_35A0[lbl_2_bss_1A824C->charId] + 2);
        lbl_2_bss_1A823C->state = 17;
        break;
    case 17:
        if (lbl_2_bss_1A8234->timer == 0x10) {
            fn_2_72054(0, 0x11);
        }
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 18;
        }
        break;
    case 18: {
        u16 down = MENU_PAD.down;
        if (down & 0x100) {
            lbl_2_bss_1A8234->timer = 0x14;
            lbl_2_bss_1A8234->layerFlags[8][10] = 1;
            fn_2_72054(0, 0x12);
            lbl_2_bss_1A823C->state = 19;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A8234->timer = 0x14;
            lbl_2_bss_1A8234->layerFlags[8][10] = 1;
            fn_2_72054(0, 0x12);
            lbl_2_bss_1A823C->state = 19;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 19:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            fn_2_4E7EC();
            lbl_2_bss_1A823C->state = 20;
        }
        break;
    case 20:
        lbl_2_bss_1A823C->state = 21;
        break;
    case 21:
        fn_2_4E7EC();
        lbl_2_bss_1A823C->state = 2;
        break;
    case 22:
        changeScene(3, 6);
        lbl_2_bss_1A8234->layerFlags[8][9] = 1;
        lbl_2_bss_1A8234->layerFlags[8][2] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x24;
        lbl_2_bss_1A823C->state = 23;
        break;
    case 23:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            MenuScreenTask* parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    case 24: {
        MenuScreenTask* child = fn_800B0A5C_insertQueue(fn_2_59CF8, 2);
        child->step = 0;
        task->signal = 0;
        lbl_2_bss_1A823C->state = 25;
        break;
    }
    case 25:
        if (task->signal == 1) {
            lbl_2_bss_1A823C->state = 18;
        }
        break;
    }
    if (lbl_8036E548._307A == 2) {
        fn_2_68E68();
        fn_2_47FF8();
        fn_2_47CFC();
    }
    GXSetZCompLoc(0);
}

// .text:0x0005AE54 size:0xD0
void fn_2_5AE54(void) {
    MenuScreenTask* task = CUR_TASK;
    switch ((s32)task->state) {
    case 1:
        break;
    case 0:
        fn_2_4E878(task, lbl_2_data_20C68);
        task->state = 1;
        task->timer = 0;
        break;
    }
    fn_2_53F88((s32)task); // TODO type: fn_2_53F88 takes the task
    fn_2_54120();
    if (lbl_2_bss_1A8234->done != 0) {
        fn_2_53DF8((u8*)task);
        fn_8000F8F4((LayoutGroup*)task);
        fn_8000FE54();
        fn_800B0A14_removeQueue(fn_2_4E858(task));
        task->state = 0;
        task->subState = 0;
        lbl_2_bss_1A8234->done = 0;
    }
}

// .text:0x0005AF24 size:0x8C
void fn_2_5AF24(void) {
    MenuScreenTask* task;
    lbl_8034E978.menu = 0x53;
    fn_800B0A5C_insertQueue(fn_80053FE8, 0);
    task = fn_800B0A5C_insertQueue(fn_2_5AE54, 0);
    task->state = 0;
    task->subState = 0;
    fn_2_54354(lbl_2_data_268A8, 0x2E0);
    lbl_2_bss_1A8234->layerFlags[0][0] = 1;
    lbl_2_bss_1A8234->layerFlags[0][1] = 1;
}

// .text:0x0005AFB0 size:0x82C
void fn_2_5AFB0(void) {
    switch (lbl_2_bss_1A823C->state) {
    case 0:
        lbl_2_bss_1A8234->layerFlags[1][7] = 1;
        lbl_8034E978.menu = 0x59;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x59].track;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A824C->listCursor = 0;
        lbl_2_bss_1A8234->layerFlags[1][8] = 1;
        lbl_2_bss_1A824C->listCount = 7;
        lbl_2_bss_1A823C->state = 1;
        break;
    case 1:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 2: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 1) {
            lbl_2_bss_1A824C->listCursor =
                (lbl_2_bss_1A824C->listCount - 1 + lbl_2_bss_1A824C->listCursor) % lbl_2_bss_1A824C->listCount;
            lbl_2_bss_1A8234->layerFlags[6][7] = 1;
            lbl_2_bss_1A8234->layerFlags[6][8] = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            lbl_2_bss_1A823C->state = 3;
            break;
        }
        if (repeat & 2) {
            lbl_2_bss_1A824C->listCursor = (lbl_2_bss_1A824C->listCursor + 1) % lbl_2_bss_1A824C->listCount;
            lbl_2_bss_1A8234->layerFlags[6][7] = 1;
            lbl_2_bss_1A8234->layerFlags[6][8] = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            lbl_2_bss_1A823C->state = 3;
            break;
        }
        down = MENU_PAD.down;
        if (down & 0x40) {
            lbl_2_bss_1A824C->mode = 4;
            lbl_2_bss_1A823C->state = 5;
            lbl_2_bss_1A8234->layerFlags[11][2] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x20) {
            lbl_2_bss_1A824C->mode = 4;
            lbl_2_bss_1A823C->state = 5;
            lbl_2_bss_1A8234->layerFlags[12][2] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A824C->tab = 0;
            lbl_2_bss_1A823C->state = 7;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 3:
        lbl_2_bss_1A823C->state = 4;
        break;
    case 4:
        lbl_2_bss_1A823C->state = 2;
        break;
    case 5:
        lbl_2_bss_1A8234->layerFlags[8][7] = 1;
        lbl_2_bss_1A8234->layerFlags[8][8] = 1;
        lbl_2_bss_1A823C->state = 6;
        break;
    case 6:
        CUR_TASK->func = fn_2_5B7DC;
        lbl_2_bss_1A823C->state = 0;
        break;
    case 7:
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 8;
        break;
    case 8:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 9;
        }
        break;
    case 9: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (lbl_2_bss_1A824C->tab == 3) {
                lbl_2_bss_1A823C->state = 13;
            } else {
                lbl_2_bss_1A823C->state = 10;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 15;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 10:
        lbl_2_bss_1A8234->layerFlags[8][7] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][8] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 11;
        break;
    case 11:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 12;
        }
        break;
    case 12:
        lbl_2_bss_1A8234->layerFlags[3][2] = 1;
        switch (lbl_2_bss_1A824C->tab) {
        case 0:
            lbl_2_bss_1A824C->mode = 5;
            CUR_TASK->func = fn_2_5A224;
            break;
        case 1:
            lbl_2_bss_1A824C->mode = 0;
            CUR_TASK->func = fn_2_5D26C;
            break;
        case 2:
            lbl_2_bss_1A824C->mode = 2;
            CUR_TASK->func = fn_2_5C5B8;
            break;
        case 3:
            lbl_2_bss_1A824C->mode = 4;
            lbl_2_bss_1A823C->state = 13;
            break;
        }
        lbl_2_bss_1A823C->state = 0;
        break;
    case 13:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 14;
        break;
    case 14:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 15:
        changeScene(3, 6);
        lbl_2_bss_1A8234->layerFlags[8][7] = 1;
        lbl_2_bss_1A8234->layerFlags[8][8] = 1;
        lbl_2_bss_1A8234->layerFlags[8][2] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 16;
        break;
    case 16:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            MenuScreenTask* parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    }
}

// .text:0x0005B7DC size:0xDDC
void fn_2_5B7DC(void) {
    s32 id;
    switch (lbl_2_bss_1A823C->state) {
    case 0:
        lbl_2_bss_1A824C->charId = 0;
        lbl_2_bss_1A824C->gridX = 1;
        lbl_2_bss_1A824C->gridY = 0;
        lbl_2_bss_1A8234->layerFlags[1][5] = 1;
        lbl_8034E978.menu = 0x58;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x58].track;
        lbl_2_bss_1A823C->state = 1;
        break;
    case 1:
        lbl_2_bss_1A823C->state = 2;
        break;
    case 2: {
        u16 down;
        if (MENU_PAD.repeat & 1) {
            lbl_2_bss_1A824C->gridX--;
            if (lbl_2_bss_1A824C->gridX == 0 && (lbl_2_bss_1A824C->gridY == 0 || lbl_2_bss_1A824C->gridY == 5)) {
                lbl_2_bss_1A824C->gridX = 4;
            } else if (lbl_2_bss_1A824C->gridX < 0) {
                lbl_2_bss_1A824C->gridX = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (MENU_PAD.repeat & 2) {
            lbl_2_bss_1A824C->gridX++;
            if (lbl_2_bss_1A824C->gridX == 5 && (lbl_2_bss_1A824C->gridY == 0 || lbl_2_bss_1A824C->gridY == 5)) {
                lbl_2_bss_1A824C->gridX = 1;
            } else if (lbl_2_bss_1A824C->gridX > 5) {
                lbl_2_bss_1A824C->gridX = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        if (MENU_PAD.repeat & 8) {
            lbl_2_bss_1A824C->gridY--;
            if (lbl_2_bss_1A824C->gridY == 0 && (lbl_2_bss_1A824C->gridX == 0 || lbl_2_bss_1A824C->gridX == 5)) {
                lbl_2_bss_1A824C->gridY = 4;
            } else if (lbl_2_bss_1A824C->gridY < 0) {
                lbl_2_bss_1A824C->gridY = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (MENU_PAD.repeat & 4) {
            lbl_2_bss_1A824C->gridY++;
            if (lbl_2_bss_1A824C->gridY == 5 && (lbl_2_bss_1A824C->gridX == 0 || lbl_2_bss_1A824C->gridX == 5)) {
                lbl_2_bss_1A824C->gridY = 1;
            } else if (lbl_2_bss_1A824C->gridY > 5) {
                lbl_2_bss_1A824C->gridY = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        lbl_2_bss_1A824C->charId = lbl_2_data_296B8[lbl_2_bss_1A824C->gridX + lbl_2_bss_1A824C->gridY * 6];
        down = MENU_PAD.down;
        if (down & 0x40) {
            lbl_2_bss_1A824C->mode = 3;
            lbl_2_bss_1A823C->state = 3;
            lbl_2_bss_1A8234->layerFlags[11][2] = 1;
            lbl_2_bss_1A8234->layerFlags[8][5] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x20) {
            lbl_2_bss_1A824C->mode = 3;
            lbl_2_bss_1A823C->state = 3;
            lbl_2_bss_1A8234->layerFlags[12][2] = 1;
            lbl_2_bss_1A8234->layerFlags[8][5] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x100) {
            if ((s32)lbl_2_bss_1A8240->stats[lbl_2_bss_1A824C->charId]._13 > 0) {
                lbl_2_bss_1A8234->timer = 10;
                lbl_2_bss_1A8234->layerFlags[1][12] = 1;
                id = lbl_2_bss_1A824C->charId;
                lbl_2_bss_1A824C->statIn.vals[0] = lbl_2_bss_1A8240->stats[id].vals[0];
                lbl_2_bss_1A824C->statIn.order[0] = lbl_2_bss_1A8240->stats[id].order[0];
                lbl_2_bss_1A824C->statIn.vals[1] = lbl_2_bss_1A8240->stats[id].vals[1];
                lbl_2_bss_1A824C->statIn.order[1] = lbl_2_bss_1A8240->stats[id].order[1];
                lbl_2_bss_1A824C->statIn.vals[2] = lbl_2_bss_1A8240->stats[id].vals[2];
                lbl_2_bss_1A824C->statIn.order[2] = lbl_2_bss_1A8240->stats[id].order[2];
                lbl_2_bss_1A824C->statIn.vals[3] = lbl_2_bss_1A8240->stats[id].vals[3];
                lbl_2_bss_1A824C->statIn.order[3] = lbl_2_bss_1A8240->stats[id].order[3];
                lbl_2_bss_1A824C->statIn.vals[4] = lbl_2_bss_1A8240->stats[id].vals[4];
                lbl_2_bss_1A824C->statIn.order[4] = lbl_2_bss_1A8240->stats[id].order[4];
                lbl_2_bss_1A824C->statIn.vals[5] = lbl_2_bss_1A8240->stats[id].vals[5];
                lbl_2_bss_1A824C->statIn.order[5] = lbl_2_bss_1A8240->stats[id].order[5];
                lbl_2_bss_1A824C->statIn._13 = lbl_2_bss_1A8240->stats[id]._13;
                lbl_2_bss_1A824C->statIn._14[0] = lbl_2_bss_1A8240->stats[id]._14[0];
                lbl_2_bss_1A824C->statIn._12 = lbl_2_bss_1A8240->stats[id]._12;
                fn_8006C2B4(&lbl_2_bss_1A824C->statOut, &lbl_2_bss_1A824C->statIn);
                memcpy(&lbl_2_bss_1A824C->statInCopy, &lbl_2_bss_1A824C->statIn, sizeof(StatInput));
                memcpy(&lbl_2_bss_1A824C->statOutCopy, &lbl_2_bss_1A824C->statOut, sizeof(StatOutput));
                lbl_2_bss_1A824C->statIn.vals[0] = lbl_2_bss_1A824C->statInCopy.vals[0];
                lbl_2_bss_1A824C->statIn.vals[1] = lbl_2_bss_1A824C->statInCopy.vals[1];
                lbl_2_bss_1A824C->statIn.vals[2] = lbl_2_bss_1A824C->statInCopy.vals[3];
                lbl_2_bss_1A824C->statIn.vals[3] = lbl_2_bss_1A824C->statInCopy.vals[4];
                lbl_2_bss_1A824C->statIn.vals[4] = lbl_2_bss_1A824C->statInCopy.vals[2];
                lbl_2_bss_1A824C->statIn.vals[5] = lbl_2_bss_1A824C->statInCopy.vals[5];
                lbl_2_bss_1A824C->statOut.vals[0] = lbl_2_bss_1A824C->statOutCopy.vals[0];
                lbl_2_bss_1A824C->statOut.vals[1] = lbl_2_bss_1A824C->statOutCopy.vals[1];
                lbl_2_bss_1A824C->statOut.vals[2] = lbl_2_bss_1A824C->statOutCopy.vals[3];
                lbl_2_bss_1A824C->statOut.vals[3] = lbl_2_bss_1A824C->statOutCopy.vals[4];
                lbl_2_bss_1A824C->statOut.vals[4] = lbl_2_bss_1A824C->statOutCopy.vals[2];
                lbl_2_bss_1A824C->statOut.vals[5] = lbl_2_bss_1A824C->statOutCopy.vals[5];
                lbl_2_bss_1A823C->state = 13;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (down & 0x200) {
            lbl_2_bss_1A824C->tab = 0;
            lbl_2_bss_1A823C->state = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 3:
        lbl_2_bss_1A823C->state = 4;
        lbl_2_bss_1A8234->timer = 0x24;
        break;
    case 4:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            CUR_TASK->func = fn_2_5AFB0;
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    case 5:
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 6;
        break;
    case 6:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 7;
        }
        break;
    case 7: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (lbl_2_bss_1A824C->tab == 3) {
                lbl_2_bss_1A823C->state = 11;
            } else {
                lbl_2_bss_1A823C->state = 8;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 17;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 8:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][5] = 1;
        lbl_2_bss_1A8234->timer = 0x24;
        lbl_2_bss_1A823C->state = 9;
        break;
    case 9:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 10;
        }
        break;
    case 10:
        lbl_2_bss_1A8234->layerFlags[3][2] = 1;
        switch (lbl_2_bss_1A824C->tab) {
        case 0:
            lbl_2_bss_1A824C->mode = 5;
            CUR_TASK->func = fn_2_5A224;
            break;
        case 1:
            lbl_2_bss_1A824C->mode = 0;
            CUR_TASK->func = fn_2_5D26C;
            break;
        case 2:
            lbl_2_bss_1A824C->mode = 2;
            CUR_TASK->func = fn_2_5C5B8;
            break;
        case 3:
            lbl_2_bss_1A824C->mode = 4;
            lbl_2_bss_1A823C->state = 11;
            break;
        }
        lbl_2_bss_1A823C->state = 0;
        break;
    case 11:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 12;
        break;
    case 12:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 13:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 14;
        }
        break;
    case 14: {
        u16 down = MENU_PAD.down;
        if (down & 0x100) {
            lbl_2_bss_1A8234->timer = 4;
            lbl_2_bss_1A8234->layerFlags[8][12] = 1;
            lbl_2_bss_1A823C->state = 15;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A8234->timer = 4;
            lbl_2_bss_1A8234->layerFlags[8][12] = 1;
            lbl_2_bss_1A823C->state = 15;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 15:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 17:
        changeScene(3, 6);
        lbl_2_bss_1A8234->layerFlags[8][5] = 1;
        lbl_2_bss_1A8234->layerFlags[8][2] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x24;
        lbl_2_bss_1A823C->state = 18;
        break;
    case 18:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            MenuScreenTask* parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    }
}

// .text:0x0005C5B8 size:0x5A4
void fn_2_5C5B8(void) {
    switch (lbl_2_bss_1A823C->state) {
    case 0:
        lbl_2_bss_1A8234->layerFlags[1][6] = 1;
        lbl_8034E978.menu = 0x57;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x57].track;
        lbl_2_bss_1A823C->state = 1;
        break;
    case 1:
        lbl_2_bss_1A824C->listCursor = 0;
        lbl_2_bss_1A823C->state = 2;
        break;
    case 2: {
        if (MENU_PAD.down & 0x200) {
            lbl_2_bss_1A824C->tab = 0;
            lbl_2_bss_1A823C->state = 5;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 5:
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 6;
        break;
    case 6:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 7;
        }
        break;
    case 7: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (lbl_2_bss_1A824C->tab == 2) {
                lbl_2_bss_1A823C->state = 11;
            } else {
                lbl_2_bss_1A823C->state = 8;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 13;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 8:
        lbl_2_bss_1A8234->layerFlags[8][6] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 9;
        break;
    case 9:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 10;
        }
        break;
    case 10:
        lbl_2_bss_1A8234->layerFlags[3][2] = 1;
        switch (lbl_2_bss_1A824C->tab) {
        case 0:
            lbl_2_bss_1A824C->mode = 5;
            CUR_TASK->func = fn_2_5A224;
            break;
        case 1:
            lbl_2_bss_1A824C->mode = 0;
            CUR_TASK->func = fn_2_5D26C;
            break;
        case 2:
            lbl_2_bss_1A824C->mode = 2;
            lbl_2_bss_1A823C->state = 11;
            break;
        case 3:
            lbl_2_bss_1A824C->mode = 3;
            CUR_TASK->func = fn_2_5AFB0;
            break;
        }
        lbl_2_bss_1A823C->state = 0;
        break;
    case 11:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 12;
        break;
    case 12:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 13:
        changeScene(3, 6);
        lbl_2_bss_1A8234->layerFlags[8][6] = 1;
        lbl_2_bss_1A8234->layerFlags[8][2] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 14;
        break;
    case 14:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            MenuScreenTask* parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    }
}

// .text:0x0005CB5C size:0x710
void fn_2_5CB5C(void) {
    switch (lbl_2_bss_1A823C->state) {
    case 0:
        lbl_2_bss_1A8234->layerFlags[1][11] = 1;
        lbl_8034E978.menu = 0x56;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x56].track;
        lbl_2_bss_1A823C->state = 2;
        break;
    case 1:
        lbl_2_bss_1A8234->layerFlags[1][11] = 1;
        lbl_8034E978.menu = 0x56;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x56].track;
        lbl_2_bss_1A823C->state = 2;
        break;
    case 2:
        lbl_2_bss_1A824C->_197702 = 0;
        lbl_2_bss_1A823C->state = 3;
        break;
    case 3: {
        u16 down = MENU_PAD.down;
        if (down & 0x40) {
            lbl_2_bss_1A824C->mode = 0;
            lbl_2_bss_1A823C->state = 5;
            lbl_2_bss_1A8234->layerFlags[8][11] = 1;
            lbl_2_bss_1A8234->layerFlags[11][2] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x20) {
            lbl_2_bss_1A8234->layerFlags[8][11] = 1;
            lbl_2_bss_1A824C->mode = 0;
            lbl_2_bss_1A823C->state = 5;
            lbl_2_bss_1A8234->layerFlags[12][2] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A824C->tab = 0;
            lbl_2_bss_1A823C->state = 7;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 4:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 3;
        }
        break;
    case 5:
        lbl_2_bss_1A823C->state = 6;
        break;
    case 6:
        CUR_TASK->func = fn_2_5D26C;
        lbl_2_bss_1A823C->state = 5;
        break;
    case 7:
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        lbl_2_bss_1A8234->timer = 0x32;
        lbl_2_bss_1A823C->state = 8;
        break;
    case 8:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 9;
        }
        break;
    case 9: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (lbl_2_bss_1A824C->tab == 1) {
                lbl_2_bss_1A823C->state = 13;
            } else {
                lbl_2_bss_1A823C->state = 10;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 15;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 10:
        lbl_2_bss_1A8234->layerFlags[8][11] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x32;
        lbl_2_bss_1A823C->state = 11;
        break;
    case 11:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 12;
        }
        break;
    case 12:
        lbl_2_bss_1A8234->layerFlags[3][2] = 1;
        switch (lbl_2_bss_1A824C->tab) {
        case 0:
            lbl_2_bss_1A824C->mode = 5;
            CUR_TASK->func = fn_2_5A224;
            break;
        case 2:
            lbl_2_bss_1A824C->mode = 2;
            CUR_TASK->func = fn_2_5C5B8;
            break;
        case 3:
            lbl_2_bss_1A824C->mode = 3;
            CUR_TASK->func = fn_2_5AFB0;
            break;
        }
        lbl_2_bss_1A823C->state = 0;
        break;
    case 13:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 14;
        break;
    case 14:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 3;
        }
        break;
    case 15:
        changeScene(3, 6);
        lbl_2_bss_1A8234->layerFlags[8][11] = 1;
        lbl_2_bss_1A8234->layerFlags[8][2] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x32;
        lbl_2_bss_1A823C->state = 16;
        break;
    case 16:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            MenuScreenTask* parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    }
}

// .text:0x0005D26C size:0x9F0
void fn_2_5D26C(void) {
    MenuScreenTask* task = CUR_TASK;
    s32 i;
    switch (lbl_2_bss_1A823C->state) {
    case 0: {
        MenuScreenTask* child;
        fn_8001F228();
        lbl_2_bss_1A824C->_197848 = 2;
        lbl_2_bss_1A824C->_197702 = 0;
        child = fn_800B0A5C_insertQueue(fn_2_8DFB0, 2);
        child->step = 0;
        child->arg = 0;
        task->signal = 0;
        lbl_2_bss_1A823C->state = 1;
        break;
    }
    case 1:
        if (task->signal == 1) {
            fn_2_94854(1);
            fn_2_9461C(-1);
            fn_2_94604(0);
            fn_2_93C64();
            lbl_2_bss_1A823C->state = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A823C->state = 3;
        break;
    case 3:
        lbl_2_bss_1A823C->state = 4;
        break;
    case 4:
        lbl_2_bss_1A8234->layerFlags[1][3] = 1;
        lbl_8034E978.menu = 0x55;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x55].track;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 8;
        break;
    case 5: {
        MenuScreenTask* child;
        lbl_2_bss_1A824C->_197702 = 0;
        child = fn_800B0A5C_insertQueue(fn_2_8DFB0, 2);
        child->step = 0;
        child->arg = 0;
        task->signal = 0;
        lbl_2_bss_1A823C->state = 6;
        break;
    }
    case 6:
        if (task->signal == 1) {
            fn_2_94854(1);
            fn_2_9461C(-1);
            fn_2_94604(0);
            fn_2_93C64();
            lbl_2_bss_1A823C->state = 7;
        }
        break;
    case 7:
        lbl_2_bss_1A8234->layerFlags[1][3] = 1;
        lbl_8034E978.menu = 0x55;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x55].track;
        lbl_2_bss_1A8234->timer = 0x12;
        lbl_2_bss_1A823C->state = 8;
        break;
    case 8:
        if (lbl_2_bss_1A8234->timer == 0xE) {
            for (i = 0; i < lbl_2_bss_340140->_3078; i++) {
                if (lbl_2_bss_33FBF0[i] == 1) {
                    fn_2_903A8(i);
                    fn_2_92654(i, 0xD);
                }
            }
        }
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 9;
        }
        break;
    case 9: {
        u16 down = MENU_PAD.down;
        if (down & 0x40) {
            lbl_2_bss_1A824C->mode = 6;
            lbl_2_bss_1A823C->state = 10;
            lbl_2_bss_1A8234->layerFlags[11][2] = 1;
            lbl_2_bss_1A8234->layerFlags[8][3] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x20) {
            lbl_2_bss_1A824C->mode = 6;
            lbl_2_bss_1A823C->state = 10;
            lbl_2_bss_1A8234->layerFlags[12][2] = 1;
            lbl_2_bss_1A8234->layerFlags[8][3] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A824C->tab = 0;
            lbl_2_bss_1A823C->state = 12;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 10:
        for (i = 0; i < lbl_2_bss_340140->_3078; i++) {
            fn_2_92654(i, 0);
        }
        lbl_2_bss_1A823C->state = 11;
        break;
    case 11:
        fn_2_4E7EC();
        CUR_TASK->func = fn_2_5CB5C;
        lbl_2_bss_1A823C->state = 1;
        break;
    case 12:
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 13;
        break;
    case 13:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 14;
        }
        break;
    case 14: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            if (lbl_2_bss_1A824C->tab == 1) {
                lbl_2_bss_1A823C->state = 18;
            } else {
                lbl_2_bss_1A823C->state = 15;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 20;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 15:
        lbl_2_bss_1A8234->layerFlags[8][3] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        for (i = 0; i < lbl_2_bss_340140->_3078; i++) {
            fn_2_92654(i, 0);
        }
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 16;
        break;
    case 16:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            fn_2_4E7EC();
            lbl_2_bss_1A823C->state = 17;
        }
        break;
    case 17:
        lbl_2_bss_1A8234->layerFlags[3][2] = 1;
        switch (lbl_2_bss_1A824C->tab) {
        case 0:
            lbl_2_bss_1A824C->mode = 5;
            CUR_TASK->func = fn_2_5A224;
            break;
        case 2:
            lbl_2_bss_1A824C->mode = 2;
            CUR_TASK->func = fn_2_5C5B8;
            break;
        case 3:
            lbl_2_bss_1A824C->mode = 3;
            CUR_TASK->func = fn_2_5AFB0;
            break;
        }
        lbl_2_bss_1A823C->state = 0;
        break;
    case 18:
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 19;
        break;
    case 19:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 9;
        }
        break;
    case 20:
        changeScene(3, 6);
        for (i = 0; i < lbl_2_bss_340140->_3078; i++) {
            fn_2_92654(i, 0);
        }
        lbl_2_bss_1A8234->layerFlags[8][2] = 1;
        lbl_2_bss_1A8234->layerFlags[8][3] = 1;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 21;
        break;
    case 21:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            MenuScreenTask* parent;
            fn_2_4E7EC();
            parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    case 22: {
        MenuScreenTask* child = fn_800B0A5C_insertQueue(fn_2_5979C, 2);
        child->step = 0;
        task->signal = 0;
        lbl_2_bss_1A823C->state = 23;
        break;
    }
    case 23:
        if (task->signal == 1) {
            lbl_2_bss_1A823C->state = 9;
        }
        break;
    }
    if (lbl_2_bss_340140->_307A == 3) {
        fn_2_8FD14();
        fn_2_8AEE0();
        fn_2_47FF8();
        fn_2_47CFC();
    }
}

// .text:0x0005DC5C size:0x4A8
void fn_2_5DC5C(void) {
    MenuScreenTask* task = CUR_TASK;
    switch (lbl_2_bss_1A823C->state) {
    case 0:
        lbl_8034E978.menu = 0x53;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0x53].track;
        lbl_2_bss_1A823C->state = 1;
        break;
    case 1:
        lbl_2_bss_1A8234->layerFlags[1][0] = 1;
        lbl_2_bss_1A8234->layerFlags[1][1] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 2;
        break;
    case 2:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A823C->state = 3;
        }
        break;
    case 3: {
        u16 repeat = MENU_PAD.repeat;
        u16 down;
        if (repeat & 8) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 3) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (repeat & 4) {
            lbl_2_bss_1A824C->tab = (lbl_2_bss_1A824C->tab + 1) % 4;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        down = MENU_PAD.down;
        if (down & 0x100) {
            lbl_2_bss_1A823C->state = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (down & 0x200) {
            lbl_2_bss_1A823C->state = 6;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    }
    case 4:
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 5;
        break;
    case 5:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            lbl_2_bss_1A8234->layerFlags[1][2] = 1;
            switch (lbl_2_bss_1A824C->tab) {
            case 0:
                lbl_2_bss_1A824C->mode = 5;
                CUR_TASK->func = fn_2_5A224;
                break;
            case 1:
                lbl_2_bss_1A824C->mode = 0;
                CUR_TASK->func = fn_2_5D26C;
                break;
            case 2:
                lbl_2_bss_1A824C->mode = 2;
                CUR_TASK->func = fn_2_5C5B8;
                break;
            case 3:
                lbl_2_bss_1A824C->mode = 3;
                CUR_TASK->func = fn_2_5AFB0;
                break;
            }
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    case 6:
        lbl_2_bss_1A8234->layerFlags[8][0] = 1;
        lbl_2_bss_1A8234->layerFlags[8][1] = 1;
        lbl_2_bss_1A8234->timer = 0x10;
        lbl_2_bss_1A823C->state = 7;
        break;
    case 7:
        if (lbl_2_bss_1A8234->timer-- == 0) {
            changeScene(3, 6);
            lbl_2_bss_1A823C->state = 8;
        }
        break;
    case 8:
        if (lbl_8037169C._13 != 0) {
            lbl_2_bss_1A823C->state = 9;
        }
        break;
    case 9: {
        MenuScreenTask* parent = task->parent;
        parent->signal = 1;
        fn_800B0A14_removeQueue(parent);
        lbl_2_bss_1A823C->state = 0;
        break;
    }
    case 10: {
        MenuScreenTask* child = fn_800B0A5C_insertQueue(fn_2_587F8, 2);
        child->step = 0;
        task->signal = 0;
        lbl_2_bss_1A823C->state = 11;
        break;
    }
    case 11:
        if (task->signal == 1) {
            lbl_2_bss_1A823C->state = 3;
        }
        break;
    }
}

// .text:0x0005E104 size:0x748
// NONMATCHING 93%: same code; register allocation differs and the original reloads lbl_2_bss_1A8230/1A824C in steps 7/8 instead of reusing the values stored at the top
#if NONMATCHING
void fn_2_5E104(void) {
    MenuScreenTask* task;
    s32 i;
    s32 j;
    CharSelWork* sel = &lbl_8034E9A0;

    lbl_2_bss_1A824C = &lbl_2_bss_1A8250;
    lbl_2_bss_1A8248 = (MenuSaveView*)starMissionCompletionTracker;
    task = CUR_TASK;
    lbl_2_bss_1A8244 = &lbl_80361B20;
    lbl_2_bss_1A8240 = &lbl_803616CC;
    lbl_2_bss_1A823C = &lbl_800E877C;
    lbl_2_bss_1A8234 = &lbl_2_bss_1A8250;
    lbl_2_bss_1A8230 = &lbl_2_bss_1A8250.drawArea;
    lbl_2_bss_340140 = &lbl_8036E548;
    lbl_2_bss_3401BC = lbl_2_bss_3401C0;
    switch (lbl_803CBBCC->step) {
    case 0:
        fn_8001F228();
        memset(&lbl_2_bss_1A8250, 0, sizeof(MenuWorkBuf));
        fn_2_54474();
        lbl_803CBBCC->step = 1;
        fn_2_5EB78();
        for (i = 0; i < 7; i++) {
            if (i == 6) {
                lbl_2_bss_1A824C->groups[i][0].id = lbl_2_bss_1A8240->tail[0].id;
                lbl_2_bss_1A824C->groups[i][0].x = lbl_2_bss_1A8240->tail[0].x;
                lbl_2_bss_1A824C->groups[i][0].y = lbl_2_bss_1A8240->tail[0].y;
                lbl_2_bss_1A824C->groups[i][1].id = lbl_2_bss_1A8240->tail[1].id;
                lbl_2_bss_1A824C->groups[i][1].x = lbl_2_bss_1A8240->tail[1].x;
                lbl_2_bss_1A824C->groups[i][1].y = lbl_2_bss_1A8240->tail[1].y;
                lbl_2_bss_1A824C->groups[i][2].id = lbl_2_bss_1A8240->tail[2].id;
                lbl_2_bss_1A824C->groups[i][2].x = lbl_2_bss_1A8240->tail[2].x;
                lbl_2_bss_1A824C->groups[i][2].y = lbl_2_bss_1A8240->tail[2].y;
                lbl_2_bss_1A824C->groups[i][3].id = lbl_2_bss_1A8240->tail[3].id;
                lbl_2_bss_1A824C->groups[i][3].x = lbl_2_bss_1A8240->tail[3].x;
                lbl_2_bss_1A824C->groups[i][3].y = lbl_2_bss_1A8240->tail[3].y;
                lbl_2_bss_1A824C->groups[i][4].id = lbl_2_bss_1A8240->tail[4].id;
                lbl_2_bss_1A824C->groups[i][4].x = lbl_2_bss_1A8240->tail[4].x;
                lbl_2_bss_1A824C->groups[i][4].y = lbl_2_bss_1A8240->tail[4].y;
            } else {
                for (j = 0; j < 5; j++) {
                    lbl_2_bss_1A824C->groups[i][j].id = lbl_2_bss_1A8240->groups[lbl_2_data_20C48[i]][j].id;
                    lbl_2_bss_1A824C->groups[i][j].x = lbl_2_bss_1A8240->groups[lbl_2_data_20C48[i]][j].x;
                    lbl_2_bss_1A824C->groups[i][j].y = lbl_2_bss_1A8240->groups[lbl_2_data_20C48[i]][j].y;
                }
            }
        }
        lbl_2_bss_1A824C->head[0].id = lbl_2_bss_1A8240->head[0].id;
        lbl_2_bss_1A824C->head[0].y = lbl_2_bss_1A8240->head[0].y;
        lbl_2_bss_1A824C->head[1].id = lbl_2_bss_1A8240->head[1].id;
        lbl_2_bss_1A824C->head[1].y = lbl_2_bss_1A8240->head[1].y;
        lbl_2_bss_1A824C->head[2].id = lbl_2_bss_1A8240->head[2].id;
        lbl_2_bss_1A824C->head[2].y = lbl_2_bss_1A8240->head[2].y;
        lbl_2_bss_1A824C->head[3].id = lbl_2_bss_1A8240->head[3].id;
        lbl_2_bss_1A824C->head[3].y = lbl_2_bss_1A8240->head[3].y;
        lbl_2_bss_1A824C->head[4].id = lbl_2_bss_1A8240->head[4].id;
        lbl_2_bss_1A824C->head[4].y = lbl_2_bss_1A8240->head[4].y;
        g_d_GameSettings.StadiumID = 0;
        lbl_2_bss_1A824C->port = sel->teamPort[0];
        fn_8000F4B8(0, -1, -1, -1);
        lbl_2_bss_1A823C->state = 0;
        break;
    case 1: {
        MenuScreenTask* child = fn_800B0A5C_insertQueue(fn_2_5ED3C, 2);
        child->step = 0;
        task->signal = 0;
        lbl_803CBBCC->step = 2;
        break;
    }
    case 2:
        if (task->signal == 1) {
            lbl_803CBBCC->step = 3;
        }
        break;
    case 3: {
        Vec pos;
        lbl_2_bss_1A8250.done = 0;
        fn_2_5AF24();
        fn_2_6ACF4();
        fn_800B0A5C_insertQueue(fn_2_71F60, 2);
        pos.z = 0.0f;
        pos.y = 0.0f;
        pos.x = 0.0f;
        fn_2_6AB3C(0, &pos, 0.0f);
        fn_2_72054(0, 0);
        fn_2_904A8();
        fn_800B0A5C_insertQueue(fn_2_9257C, 2);
        for (i = 0; i < lbl_2_bss_340140->_3078; i++) {
            fn_2_903A8(i);
            fn_2_92654(i, 0);
        }
        fn_800B0A5C_insertQueue(fn_2_5DC5C, 2);
        task->signal = 0;
        lbl_2_bss_1A824C->mode = 0;
        lbl_2_bss_1A824C->_197732 = 0;
        lbl_803CBBCC->step = 4;
        break;
    }
    case 4:
        lbl_803CBBCC->step = 5;
        break;
    case 5:
        changeScene(1, 6);
        lbl_803CBBCC->step = 6;
        break;
    case 6:
        if (lbl_8037169C.done != 0) {
            lbl_803CBBCC->step = 7;
        }
        break;
    case 7:
        if (task->signal == 1) {
            lbl_8034E978._05 = 1;
            lbl_2_bss_1A8250.done = 1;
            lbl_2_bss_1A8230->_32A86 = 1;
            lbl_803CBBCC->step = 8;
        }
        break;
    case 8:
        lbl_2_bss_1A8250._1972BC = 1;
        lbl_2_bss_1A824C->_1972C0 = 1;
        fn_8001F228();
        fn_80035B50(10);
        if (lbl_80366B18.tables[2] != NULL) {
            fn_800ACFB0(lbl_80366B18.tables[2]);
            lbl_80366B18.tables[2] = NULL;
        }
        lbl_2_bss_1A823C->_34 = 0;
        lbl_803CBBCC->step = 0;
        fn_2_11A0(5);
        lbl_2_bss_1A823C->state = 0;
        break;
    }
}
#endif
