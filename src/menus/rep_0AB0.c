#include "menus/rep_0AB0.h"
#include "game/UnknownHomes_Game.h"
#include "main/file_8000F150.h"
#include "main/file_8004207C.h"
#include "main/file_800527C4.h"
#include "main/file_800A7C08.h"
#include "main/file_800B0724.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/rep_0788.h"
#include "menus/auto_00_0005597C_text.h"

extern u32 sndFXStartEx(u16 fid, u8 vol, u8 pan, u8 studio);

extern MenuWorkBuf* lbl_2_bss_1A8234;
extern MenuSceneState* lbl_2_bss_1A823C;
extern MenuWorkBuf* lbl_2_bss_1A824C;
// lbl_803CC1B8 (SceneTask*, main/file_80069BDC.h) is the running menu task.
#define CUR_TASK ((MenuTask*)lbl_803CC1B8)
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
    return;
}

// .text:0x00059CF8 size:0x52C
void fn_2_59CF8(void) {
    return;
}

// .text:0x0005A224 size:0xC30
void fn_2_5A224(void) {
    return;
}

// .text:0x0005AE54 size:0xD0
void fn_2_5AE54(void) {
    MenuTask* task = CUR_TASK;
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
    MenuTask* task;
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
    return;
}

// .text:0x0005B7DC size:0xDDC
void fn_2_5B7DC(void) {
    return;
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
            MenuTask* parent = CUR_TASK->parent;
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
            MenuTask* parent = CUR_TASK->parent;
            parent->signal = 1;
            fn_800B0A14_removeQueue(parent);
            lbl_2_bss_1A823C->state = 0;
        }
        break;
    }
}

// .text:0x0005D26C size:0x9F0
void fn_2_5D26C(void) {
    return;
}

// .text:0x0005DC5C size:0x4A8
void fn_2_5DC5C(void) {
    MenuTask* task = CUR_TASK;
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
        MenuTask* parent = task->parent;
        parent->signal = 1;
        fn_800B0A14_removeQueue(parent);
        lbl_2_bss_1A823C->state = 0;
        break;
    }
    case 10: {
        MenuTask* child = fn_800B0A5C_insertQueue(fn_2_587F8, 2);
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
void fn_2_5E104(void) {
    return;
}
