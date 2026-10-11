#include "menus/auto_00_0005E84C_text.h"

// .text:0x0005E84C size:0x32C
void fn_2_5E84C(void) {
    return;
}

// .text:0x0005EB78 size:0x1C4
// NONMATCHING 97%: lbl_2_bss_1A8244 is loaded one slot early and lands in r8 instead of r4
#if NONMATCHING
void fn_2_5EB78(void) {
    MenuFlags4 flags;
    u8* flag;
    s32 i;
    MenuProgress* progress;
    s32 j;

    lbl_2_bss_33FBF5 = 0;
    flags.b[0] = 0;
    flags.b[1] = 0;
    flags.b[2] = 0;
    flags.b[3] = 0;
    flag = flags.b;
    progress = lbl_2_bss_1A8244;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            if (progress->_C6[j][i] != 0) {
                *flag = 1;
            }
        }
        flag++;
    }
    lbl_2_bss_33FBF0.b[0] = flags.b[0];
    lbl_2_bss_33FBF0.b[1] = flags.b[1];
    lbl_2_bss_33FBF0.b[2] = flags.b[2];
    lbl_2_bss_33FBF0.b[3] = flags.b[3];
    if ((s32)lbl_2_bss_1A824C->_197862 == 1) {
        lbl_2_bss_1A8240->lists[0][0].value = 9999;
        lbl_2_bss_1A8240->lists[0][1].value = 123;
        lbl_2_bss_1A8240->lists[0][2].value = 45;
        lbl_2_bss_1A8240->lists[0][3].value = 6;
        lbl_2_bss_1A8240->lists[0][4].value = 0;
        lbl_2_bss_1A8240->lists[0][0]._6 = 0;
        lbl_2_bss_1A8240->lists[0][1]._6 = 1;
        lbl_2_bss_1A8240->lists[0][2]._6 = 2;
        lbl_2_bss_1A8240->lists[0][3]._6 = 3;
        lbl_2_bss_1A8240->lists[0][4]._6 = 4;
        lbl_2_bss_1A8240->lists[1][0].value = 9876;
        lbl_2_bss_1A8240->lists[1][1].value = 543;
        lbl_2_bss_1A8240->lists[1][2].value = 21;
        lbl_2_bss_1A8240->lists[1][3].value = 1;
        lbl_2_bss_1A8240->lists[1][4].value = 0;
        lbl_2_bss_1A8240->lists[1][0]._6 = 0;
        lbl_2_bss_1A8240->lists[1][1]._6 = 1;
        lbl_2_bss_1A8240->lists[1][2]._6 = 2;
        lbl_2_bss_1A8240->lists[1][3]._6 = 3;
        lbl_2_bss_1A8240->lists[1][4]._6 = 4;
    }
}
#endif

// .text:0x0005ED3C size:0xF8
// NONMATCHING 98%: the original called fn_80035838 without its u8 return prototype (cmpwi, no clrlwi.)
#if NONMATCHING
void fn_2_5ED3C(void) {
    MenuTask* task = lbl_803CC1B8;
    MenuTask* parent;
    switch (task->step) {
    case 0:
        lbl_80366B18.tables[2] = ARAMTransfer(&lbl_2_data_20C00, NULL, 1, 0);
        task->step = 1;
        break;
    case 1:
        if ((s32)(u8)lbl_803C6CF8.idle == 1) {
            fn_800111B4(lbl_80366B18.tables[2]);
            task->step = 2;
        }
        break;
    case 2:
        if (fn_80035838(lbl_2_data_20BF0, 10) != 0) {
            task->step = 3;
        }
        break;
    case 3:
        parent = task->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif

// .text:0x0005EE34 size:0x88
void fn_2_5EE34(void) {
    lbl_2_bss_1A824C->_1972BC = 1;
    lbl_2_bss_1A824C->_1972C0 = 1;
    fn_8001F228();
    fn_80035B50(10);
    if (lbl_80366B18.tables[2] != NULL) {
        fn_800ACFB0(lbl_80366B18.tables[2]);
        lbl_80366B18.tables[2] = NULL;
    }
    lbl_2_bss_1A823C->_34 = 0;
}

// .text:0x0005EEBC size:0x1D0
void fn_2_5EEBC(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 0;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) >= 10) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x0005F08C size:0x21C
void fn_2_5F08C(MenuTask* task, MenuItem* item) {
    s32 value;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        value = lbl_2_bss_1A824C->_197417;
        fn_800363D8((SpaniOwner*)task, item->sprite, 1, 6, value % 10);
        fn_800363D8((SpaniOwner*)task, item->sprite, 2, 6, (value / 10) % 10);
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x0005F2A8 size:0x1B0
void fn_2_5F2A8(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        fn_800363D8((SpaniOwner*)task, item->sprite, 1, 0x71, lbl_2_bss_1A824C->_197416);
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x0005F458 size:0x96C
void fn_2_5F458(void) {
    return;
}

// .text:0x0005FDC4 size:0x2C0
void fn_2_5FDC4(void) {
    return;
}

// .text:0x00060084 size:0x188
void fn_2_60084(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x0006020C size:0x188
void fn_2_6020C(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00060394 size:0x188
void fn_2_60394(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x0006051C size:0x2C0
void fn_2_6051C(void) {
    return;
}

// .text:0x000607DC size:0x18C
void fn_2_607DC(MenuTask* task, MenuItem* item) {
    s32 total;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        total = fn_8006C268((struct StatOutput*)lbl_2_bss_1A824C->stats);
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = fn_8006C100(total) << 16;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00060968 size:0x188
void fn_2_60968(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00060AF0 size:0x188
void fn_2_60AF0(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00060C78 size:0x17C
void fn_2_60C78(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = lbl_2_bss_1A824C->_197418 << 16;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00060DF4 size:0x188
void fn_2_60DF4(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00060F7C size:0x188
void fn_2_60F7C(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 10;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061104 size:0x1A4
void fn_2_61104(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        if ((s32)lbl_2_bss_1A8244->_00[lbl_800E869C[item->_10]] == 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        }
        item->state = 0x25;
        break;
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x000612A8 size:0x1C0
void fn_2_612A8(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        if ((s32)lbl_2_bss_1A8244->_00[lbl_800E869C[item->_10]] == 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        item->state = 0x25;
        break;
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061468 size:0x1DC
void fn_2_61468(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        fn_800363D8((SpaniOwner*)task, item->sprite, 1, 0x43, item->_10);
        if ((s32)lbl_2_bss_1A8244->_00[lbl_800E869C[item->_10]] == 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0x10000;
        }
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061644 size:0x150
void fn_2_61644(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061794 size:0x1B4
void fn_2_61794(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061948 size:0x224
void fn_2_61948(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        if (lbl_2_bss_33FBF0.b[item->_0A] == 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
            item->state = 0x25;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
            item->state = 0x25;
        }
        break;
    case 5:
        if (lbl_2_bss_33FBF0.b[item->_0A] == 1) {
            item->state = 7;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
            item->state = 6;
        }
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061B6C size:0x224
void fn_2_61B6C(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        if (lbl_2_bss_33FBF0.b[item->_0A] == 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
            item->state = 0x25;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
            item->state = 0x25;
        }
        break;
    case 5:
        if (lbl_2_bss_33FBF0.b[item->_0A] == 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
            item->state = 6;
        } else {
            item->state = 7;
        }
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061D90 size:0x1CC
void fn_2_61D90(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        fn_800363D8((SpaniOwner*)task, item->sprite, 1, 0x5F, item->_0A);
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00061F5C size:0x1B4
void fn_2_61F5C(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00062110 size:0x29C
void fn_2_62110(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    GameInitVariables* settings = &g_d_GameSettings;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
    case 0x11:
        if (lbl_2_bss_1A824C->_1976FA == 5 && settings->_12 == 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        } else if (lbl_2_bss_1A824C->_1976FA == 6 && settings->_12 <= 1) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
            lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        } else {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 10 << 16;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 0x25:
        break;
    }
}

// .text:0x000623AC size:0x204
void fn_2_623AC(void) {
    return;
}

// .text:0x000625B0 size:0x244
void fn_2_625B0(void) {
    return;
}

// .text:0x000627F4 size:0x244
void fn_2_627F4(void) {
    return;
}

// .text:0x00062A38 size:0x2E0
void fn_2_62A38(void) {
    return;
}

// .text:0x00062D18 size:0x858
void fn_2_62D18(void) {
    return;
}

// .text:0x00063570 size:0x134
void fn_2_63570(void) {
    return;
}

// .text:0x000636A4 size:0x1D0
void fn_2_636A4(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00063874 size:0x1F0
void fn_2_63874(void) {
    return;
}

// .text:0x00063A64 size:0x188
void fn_2_63A64(void) {
    return;
}

// .text:0x00063BEC size:0x1D0
void fn_2_63BEC(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00063DBC size:0x19C
void fn_2_63DBC(void) {
    return;
}

// .text:0x00063F58 size:0x1D0
void fn_2_63F58(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00064128 size:0x1D0
void fn_2_64128(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x000642F8 size:0x234
void fn_2_642F8(void) {
    return;
}

// .text:0x0006452C size:0x1D0
void fn_2_6452C(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x000646FC size:0x1D0
void fn_2_646FC(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x000648CC size:0x384
void fn_2_648CC(void) {
    return;
}

// .text:0x00064C50 size:0x1D0
void fn_2_64C50(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_5C = 0;
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00064E20 size:0x284
void fn_2_64E20(void) {
    return;
}

// .text:0x000650A4 size:0x1B4
void fn_2_650A4(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00065258 size:0x17C
void fn_2_65258(void) {
    return;
}

// .text:0x000653D4 size:0x274
void fn_2_653D4(void) {
    return;
}

// .text:0x00065648 size:0x208
void fn_2_65648(void) {
    return;
}

// .text:0x00065850 size:0x1B0
void fn_2_65850(void) {
    return;
}

// .text:0x00065A00 size:0x284
void fn_2_65A00(void) {
    return;
}

// .text:0x00065C84 size:0x1CC
void fn_2_65C84(void) {
    return;
}

// .text:0x00065E50 size:0x1E8
void fn_2_65E50(void) {
    return;
}

// .text:0x00066038 size:0x150
void fn_2_66038(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00066188 size:0x1B4
void fn_2_66188(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x0006633C size:0x284
void fn_2_6633C(void) {
    return;
}

// .text:0x000665C0 size:0x19C
void fn_2_665C0(void) {
    return;
}

// .text:0x0006675C size:0x128
void fn_2_6675C(void) {
    return;
}

// .text:0x00066884 size:0x268
void fn_2_66884(void) {
    return;
}

// .text:0x00066AEC size:0x1D8
void fn_2_66AEC(void) {
    return;
}

// .text:0x00066CC4 size:0x150
void fn_2_66CC4(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        item->state = 0x25;
        break;
    case 5:
        item->timer = 40;
        item->state = 6;
        break;
    case 6:
        if (item->timer-- <= 0) {
            lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00066E14 size:0x1B4
void fn_2_66E14(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00066FC8 size:0x214
void fn_2_66FC8(void) {
    return;
}

// .text:0x000671DC size:0x1B4
void fn_2_671DC(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00067390 size:0x1F8
void fn_2_67390(void) {
    return;
}

// .text:0x00067588 size:0x1F8
void fn_2_67588(void) {
    return;
}

// .text:0x00067780 size:0x414
void fn_2_67780(void) {
    return;
}

// .text:0x00067B94 size:0x1B4
void fn_2_67B94(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x00067D48 size:0x2A4
void fn_2_67D48(void) {
    return;
}

// .text:0x00067FEC size:0x1B4
void fn_2_67FEC(MenuTask* task, MenuItem* item) {
    LayoutObj* obj;
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        item->state = 0x26;
        break;
    case 2:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags |= 2;
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 1;
        item->state = 0x25;
        break;
    case 5:
        lbl_80371C30[task->baseIdx + item->sprite].obj->_68 = 4;
        item->state = 6;
        break;
    case 6:
        obj = lbl_80371C30[task->baseIdx + item->sprite].obj;
        if ((obj->_5C >> 16) == 0) {
            obj->_68 = 0;
            item->state = 7;
        }
        break;
    case 7:
        lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// .text:0x000681A0 size:0x94
void fn_2_681A0(MenuTask* task, MenuItem* item) {
    s16 ev = fn_2_53BC8(item);
    if (ev != -1) {
        item->state = ev;
    }
    switch (item->state) {
    case 0:
        item->state = 0x26;
        break;
    case 2:
        item->state = 0x25;
        break;
    case 1:
    case 5:
    case 0x25:
        break;
    }
}

// .text:0x00068234 size:0x2C
void fn_2_68234(MenuTask* task, MenuItem* item) {
    lbl_80371C30[task->baseIdx + item->sprite].obj->flags &= ~2;
}

// .text:0x00068260 size:0xA8
void fn_2_68260(MenuTask* task) {
    CharActor* actor;
    u8 idx = lbl_2_bss_1A8248->_441C;
    s32 base = lbl_2_data_2E80[idx][0] * 2;
    s32 animA = base - lbl_2_data_2E80[idx][2] * 2;
    s32 animB = base - lbl_2_data_2E80[idx][1] * 2;
    if (task->_80 == 0) {
        actor = &lbl_8036E548.actors[0];
        if (actor != NULL && (actor->_068 == animA || actor->_068 == animB)) {
            if (idx == 5) {
                fn_80062890(1);
            } else {
                fn_80062890(0);
            }
        }
    }
}

// .text:0x00068308 size:0x24
// NONMATCHING 89%: original keeps the pointer across the stb/sth pair but reloads it before the last store
#if NONMATCHING
void fn_2_68308(void) {
    lbl_2_bss_1A8248->_17AB = 0;
    lbl_2_bss_1A8248->_177C = 0;
    lbl_2_bss_1A8248->_442F = 0;
}
#endif
