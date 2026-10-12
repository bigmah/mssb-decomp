#include "menus/auto_00_00033E70_text.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "menus/auto_00_0003C03C_text.h"
#include "menus/auto_00_0004B1AC_text.h"
#include "menus/rep_0788.h"
#include "main/file_8000F150.h"
#include "main/file_8001FE00.h"
#include "main/menu_globals.h"
#include "main/file_800527C4.h"
extern s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize);

extern void fn_2_4E7EC(void);
extern void fn_2_4E824(void);
extern MenuProgress* lbl_2_bss_1A8244;
extern MenuCtx* lbl_2_bss_1A8248;
extern s16 fn_2_53BC8(void*);
extern MenuData* lbl_2_bss_1A8234;
extern MenuData* lbl_2_bss_1A824C;
extern MenuScreenTask* lbl_803CC1B8;
extern void fn_800B0A14_removeQueue(void*);
extern s32 fn_2_45A84();
extern void fn_2_90428(s32);
extern void fn_2_92654(s32, u8);
extern u8 fn_8006862C(s32, s32);
extern void fn_80036134(void*, s32, s32, s32);
extern s16 lbl_2_data_C924[3][12]; // rep_0788.c
extern s16 lbl_2_data_C8F8[6];
extern s16 lbl_2_data_C904[16];

// fn_2_37430, size:0x2C
void fn_2_37430(MenuTask* a, MenuItemState* b) {
    LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
    p->flags &= ~2;
}

// fn_2_3745C, size:0x4
void fn_2_3745C(void) {
}

// fn_2_37D70, size:0x4
void fn_2_37D70(void) {
}

// fn_2_37D74, size:0x4
void fn_2_37D74(void) {
}

// fn_2_37D78, size:0x4
void fn_2_37D78(void) {
}

// fn_2_37D7C, size:0x4
void fn_2_37D7C(void) {
}

// fn_2_37D80, size:0x4
void fn_2_37D80(void) {
}

// fn_2_37D84, size:0x4
void fn_2_37D84(void) {
}

// fn_2_37D88, size:0x4
void fn_2_37D88(void) {
}

// fn_2_37D8C, size:0x4
void fn_2_37D8C(void) {
}

// fn_2_37D90, size:0x4
void fn_2_37D90(void) {
}

// fn_2_37D94, size:0x4
void fn_2_37D94(void) {
}

// fn_2_38EA8, size:0xA0
void fn_2_38EA8(void) {
    lbl_2_bss_1A8248->_4416 = lbl_2_bss_1A8248->_4415;
    lbl_2_bss_1A8244->_E4[lbl_2_bss_1A8248->_4415] = 1;
    if (lbl_2_bss_1A8248->_4415 < 3) {
        // The original offsets the whole block by the stadium, then reads the
        // per-stadium byte tables at fixed offsets (all-u8 struct, so portable).
        MenuProgress* e = (MenuProgress*)((u8*)lbl_2_bss_1A8244 + lbl_2_bss_1A8248->_441C);
        if (e->_E8[0] == 0) {
            e->_E8[0] = 1;
        }
        lbl_2_bss_1A8248->_4415 = lbl_2_bss_1A8248->_4415 + 1;
        e = (MenuProgress*)((u8*)lbl_2_bss_1A8244 + lbl_2_bss_1A8248->_441C);
        e->_DE[0] = e->_DE[0] + 1;
    }
}

// fn_2_372AC, size:0xB0
void fn_2_372AC(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0:
        b->state = 0x26;
        break;
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x25;
        break;
    }
    case 0x25:
        break;
    }
}

// fn_2_3735C, size:0xD4
void fn_2_3735C(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2:
        b->state = 0x25;
        break;
    case 1:
    case 5:
    case 8:
    case 0x24:
    case 0x25:
        break;
    }
}

// fn_2_380B0, size:0xF8
void fn_2_380B0(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        p->counter = 0x15;
        lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_381A8, size:0xF8
void fn_2_381A8(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        p->counter = 0x15;
        lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_35754, size:0x10C
void fn_2_35754(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        b->state = 0x25;
        break;
    }
    case 1:
    case 5:
    case 0x25:
        break;
    }
}

// fn_2_35DB4, size:0x10C
void fn_2_35DB4(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        b->state = 0x25;
        break;
    }
    case 1:
    case 5:
    case 0x25:
        break;
    }
}

// fn_2_34F6C, size:0x11C
void fn_2_34F6C(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        b->state = 0x25;
        break;
    }
    case 5: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_38C14, size:0x130
void fn_2_38C14(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        p->counter = 0x14;
        p->step = 2;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            lbl_2_bss_1A824C->_19782C = 1;
            p->counter = 0x14;
            p->step = 2;
        }
        break;
    }
    case 2: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->counter = 0x14;
            p->step = 3;
        }
        break;
    }
    case 3:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_38D44, size:0x164
void fn_2_38D44(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        if (fn_2_45A84() == 1) {
            p->counter = 1;
            p->step = 1;
        } else {
            p->step = 4;
        }
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        lbl_2_bss_1A8234->layerFlags[1][54] = 1;
        p->counter = 0x5A;
        p->step = 3;
        break;
    case 3: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            lbl_2_bss_1A8234->layerFlags[8][54] = 1;
            p->step = 4;
        }
        break;
    }
    case 4:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_37D98, size:0x16C
void fn_2_37D98(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        changeScene(1, 6);
        p->counter = 0x26AE;
        p->arg = 0;
        lbl_2_bss_1A8234->layerFlags[1][1] = 1;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        p->arg = p->arg + 1;
        break;
    }
    case 2:
        if (fn_8006862C(0x1A4, 0) == 0) {
            p->step = 3;
        }
        break;
    case 3:
        changeScene(3, 6);
        p->step = 4;
        break;
    case 4:
        if (lbl_8037169C._13 != 0) {
            q = p->parent;
            q->signal = 1;
            fn_800B0A14_removeQueue(q);
            p->step = 0;
        }
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_37F04, size:0x1AC
void fn_2_37F04(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    GameInitVariables* gs = &g_d_GameSettings;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        if (lbl_2_bss_1A8248->_444B != -1) {
            p->counter = 0x14;
            p->step = 1;
        } else {
            p->step = 4;
        }
        break;
    case 1: {
        s16 t;
        if (p->counter == 4) {
            fn_80062890(0x43);
        }
        t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        gs->challengeCaptainStarBought[lbl_2_bss_1A8248->_444B] = 0;
        lbl_2_bss_1A8248->_444C = -1;
        lbl_2_bss_1A8248->_444B = -1;
        lbl_2_bss_1A8234->layerFlags[7][46] = 1;
        p->counter = 0x3C;
        p->step = 3;
        break;
    case 3: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 4;
        }
        break;
    }
    case 4:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_3BC24, size:0x164
void fn_2_3BC24(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        lbl_2_bss_1A8248->_442A = 1;
        p->counter = 0x3C;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            fn_2_90428(0x19);
            fn_2_92654(0x19, 8);
            fn_2_90428(0x1A);
            fn_2_92654(0x1A, 1);
            fn_2_90428(0x1B);
            fn_2_92654(0x1B, 2);
            fn_80062890(0x42);
            p->counter = 0xB4;
            p->step = 2;
        }
        break;
    }
    case 2: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 3;
        }
        break;
    }
    case 3:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_35088, size:0x1B4
void fn_2_35088(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34060, size:0x1B4
void fn_2_34060(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34524, size:0x1B4
void fn_2_34524(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34844, size:0x1B4
void fn_2_34844(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_35860, size:0x1B4
void fn_2_35860(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_35EC0, size:0x1B4
void fn_2_35EC0(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_3697C, size:0x1B4
void fn_2_3697C(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_36F44, size:0x1B4
void fn_2_36F44(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_370F8, size:0x1B4
void fn_2_370F8(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    }
    case 7: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    }
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_346D8, size:0x16C
void fn_2_346D8(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        b->state = 0x25;
        break;
    }
    case 5:
        b->timer = 0x29;
        b->state = 6;
        break;
    case 6:
        if ((b->timer)-- <= 0) {
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
            lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34214, size:0x188
void fn_2_34214(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        b->timer = 0x29;
        b->state = 6;
        break;
    case 6:
        if ((b->timer)-- <= 0) {
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
            lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_3439C, size:0x188
void fn_2_3439C(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        b->timer = 0x29;
        b->state = 6;
        break;
    case 6:
        if ((b->timer)-- <= 0) {
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
            lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_34BCC, size:0x1E0
void fn_2_34BCC(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p;
        lbl_80371C30[a->baseIdx + b->offset].obj->_5C = 0;
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        b->timer = 3;
        b->state = 6;
        break;
    case 6:
        if ((b->timer)-- <= 0) {
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
            lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_349F8, size:0x1D4
void fn_2_349F8(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p;
        lbl_80371C30[a->baseIdx + b->offset].obj->_5C = 0;
        fn_800363D8(a, b->offset, 1, 0xCD, lbl_2_bss_1A8248->_4415 - 1);
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        b->timer = 3;
        b->state = 6;
        break;
    case 6:
        if ((b->timer)-- <= 0) {
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
            lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        }
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_36074, size:0x190
void fn_2_36074(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p;
        lbl_80371C30[a->baseIdx + b->offset].obj->_5C = 0;
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    }
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        b->state = 6;
        break;
    case 6:
        lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}


// fn_2_36204, size:0x1C4
void fn_2_36204(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2:
        if (lbl_2_bss_1A824C->_1972AC[b->index] == 3) {
            LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
            p->flags |= 2;
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        }
        b->state = 0x25;
        break;
    case 5:
        if (lbl_2_bss_1A824C->_1972AC[b->index] == 3) {
            lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        }
        b->state = 6;
        break;
    case 6:
        lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}


// fn_2_36590, size:0x1C0
void fn_2_36590(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        fn_80036134(a, 0x12, lbl_2_bss_1A824C->_1972B0, b->offset);
        b->state = 0x25;
        break;
    }
    case 0x25:
        fn_80036134(a, 0x12, lbl_2_bss_1A824C->_1972B0, b->offset);
        break;
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        b->state = 6;
        break;
    case 6:
        lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        break;
    case 1:
        break;
    }
}


// fn_2_363C8, size:0x1C8
void fn_2_363C8(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        fn_80036134(a, 0x293, lbl_2_bss_1A824C->_1972B0 + 1, b->offset);
        b->state = 0x25;
        break;
    }
    case 0x25:
        fn_80036134(a, 0x293, lbl_2_bss_1A824C->_1972B0 + 1, b->offset);
        break;
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        b->state = 6;
        break;
    case 6:
        lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        break;
    case 1:
        break;
    }
}


// fn_2_36B30, size:0x1E4
void fn_2_36B30(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 0x25;
        break;
    case 0x25:
        if (lbl_2_bss_1A824C->_197298[b->index] != 0) {
            lbl_80371C30[a->baseIdx + b->offset].obj->flags |= 2;
        } else {
            lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        }
        break;
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 0;
        b->state = 6;
        break;
    case 6:
        lbl_80371C30[a->baseIdx + b->offset].obj->flags &= ~2;
        break;
    case 1:
        break;
    }
}



// fn_2_3523C, size:0x1C0
void fn_2_3523C(MenuTask* a, MenuItemState* b) {
    LayoutObj* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->unk12 = 0xFF;
        b->unk14 = fn_8000F988((LayoutGroup*)a, b->offset, b->unk10, 4, 0x312, 0);
        b->state = 0x26;
        break;
    }
    case 2: {
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80366B18.entries[b->unk14].hAlign = 1;
        b->state = 3;
        break;
    }
    case 3:
        b->state = 0x25;
        break;
    case 0x25:
        b->state = 0x25;
        break;
    case 5: {
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    }
    p = lbl_80371C30[a->baseIdx + b->offset].obj;
    p->color = b->unk12 | (p->color & 0xFFFFFF00);
}

// fn_2_34D70, size:0x1FC
void fn_2_34D70(MenuTask* a, MenuItemState* b) {
    LayoutObj* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->unk12 = 0xFF;
        b->unk14 = fn_8000F988((LayoutGroup*)a, b->offset, b->unk10, 4, 0x306, 0);
        b->state = 0x26;
        break;
    }
    case 2: {
        fn_8000FE08(b->unk14, 4, lbl_2_bss_1A8248->_4415 + 0x305);
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80366B18.entries[b->unk14].hAlign = 1;
        b->state = 3;
        break;
    }
    case 3:
        b->state = 0x25;
        break;
    case 0x25:
        b->state = 0x25;
        break;
    case 5: {
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 1:
    case 4:
        break;
    }
    lbl_80366B18.entries[b->unk14].hAlign = 1;
    p = lbl_80371C30[a->baseIdx + b->offset].obj;
    p->color = b->unk12 | (p->color & 0xFFFFFF00);
}

// fn_2_33E70, size:0x1F0
void fn_2_33E70(MenuTask* a, MenuItemState* b) {
    LayoutObj* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    case 2:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        fn_800363D8(a, b->offset, 1, 0x2E, lbl_2_data_C924[b->index][lbl_2_bss_1A824C->_19785B]);
        break;
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    case 7:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    case 1:
    case 0x25:
        break;
    }
}

// fn_2_36D04, size:0x240
void fn_2_36D04(MenuTask* a, MenuItemState* b) {
    LayoutObj* p;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    case 2:
        lbl_80371C30[a->baseIdx + b->offset].obj->_5C = 0xF0000;
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 3;
        break;
    case 3:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) >= lbl_2_data_C8F8[b->unk10]) {
            p->_68 = 0;
            b->state = 0x25;
        }
        break;
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_5C = lbl_2_data_C8F8[b->unk10] << 16;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 6;
        break;
    case 6:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) >= lbl_2_data_C904[b->unk10]) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    case 7:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    case 1:
    case 4:
    case 0x25:
        break;
    }
}

// fn_2_36750, size:0x22C
void fn_2_36750(MenuTask* a, MenuItemState* b) {
    LayoutObj* p;
    s16 v;
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        b->state = 0x26;
        break;
    case 2:
        if (b->index == 0) {
            v = lbl_2_bss_1A824C->_1972AA;
            if (v != 0xA) {
                fn_800363D8(a, b->offset, 1, 0x54, v);
            }
        } else {
            fn_800363D8(a, b->offset, 1, 0x54, lbl_2_bss_1A8248->_441C);
        }
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags |= 2;
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 1;
        b->state = 3;
        break;
    case 3:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) >= 0x15) {
            p->_68 = 0;
            b->state = 0x25;
        }
        break;
    case 5:
        lbl_80371C30[a->baseIdx + b->offset].obj->_68 = 4;
        b->state = 6;
        break;
    case 6:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        if ((p->_5C >> 16) == 0) {
            p->_68 = 0;
            b->state = 7;
        }
        break;
    case 7:
        p = lbl_80371C30[a->baseIdx + b->offset].obj;
        p->flags &= ~2;
        break;
    case 1:
    case 4:
    case 0x25:
        break;
    }
}

typedef struct Fn37460Data {
    u8 skipped;
    u8 pad1[3];
    s32 size;
    void* alt;
    void* buf;
    void* heap;
} Fn37460Data;

static Fn37460Data lbl_2_bss_15A0;
extern u8 lbl_2_data_12180[];
extern u8 lbl_2_data_12170[];
extern void* _OSAllocFromHeap(s32, s32);
extern void* memset(void*, int, u32);
extern void* fn_80009018(void* heap);
extern void fn_800AD070(void);
extern void fn_800AD500(void*, void*);
extern s32 fn_800AD6BC(void*);
extern s32 fn_800AD780(void*);
extern void fn_800AD95C(void*, s32);
extern void fn_800AD9F4(void*);
extern s32 fn_800ADAFC(void);
extern s32 fn_800ADB04(void*, void*, s32, s32);
extern void fn_800ADBFC(void);
extern void fn_800ADC40(void*, s32);

// fn_2_37460, size:0x1D0
void fn_2_37460(void) {
    Fn37460Data* d = &lbl_2_bss_15A0;
    MenuScreenTask* o = lbl_803CC1B8;
    void* p;
    s32 sz;
    switch ((s8)o->step) {
    case 0:
        fn_2_4E824();
        p = _OSAllocFromHeap(0x20, 0x1C0);
        d->heap = p;
        memset(p, 0, 0x1C0);
        d->size = 0x400000;
        p = _OSAllocFromHeap(0x20, 0x400000);
        d->alt = p;
        fn_800ADC40(p, d->size);
        o->step++;
        return;
    case 1:
        if (fn_800ADB04(lbl_2_data_12180, d->heap, 1, 0) != 0) {
            fn_80009018(d->heap);
            o->step++;
        }
        break;
    case 2:
        if (fn_800ADAFC() != 0) {
            sz = fn_800AD6BC(d->heap);
            p = _OSAllocFromHeap(0x20, sz);
            d->buf = p;
            fn_800AD500(d->heap, p);
            fn_800AD95C(d->heap, 1);
            o->step++;
            return;
        }
        break;
    case 3:
        fn_800AD070();
        if (fn_800AD780(d->heap) != 0) {
            o->step++;
            return;
        }
        break;
    case 4:
        if (fn_800AD780(d->heap) != 0) {
            fn_80009018(NULL);
            fn_800AD9F4(d->heap);
            fn_800ADBFC();
            o->step++;
            return;
        }
        break;
    case 5:
        fn_2_4E7EC();
        p = lbl_803CC1B8->parent;
        ((MenuScreenTask*)p)->signal = 1;
        fn_800B0A14_removeQueue(p);
        o->step = 0;
        return;
    }
}

// fn_2_38A40, size:0x1D4
void fn_2_38A40(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        lbl_2_bss_1A8248->_44F2 = 3;
        p->counter = 0xF;
        if (lbl_2_bss_1A824C->_19729C != 0) {
            lbl_2_bss_1A8234->layerFlags[1][2] = 1;
            lbl_2_bss_1A8234->layerFlags[1][3] = 1;
            lbl_2_bss_1A8234->layerFlags[1][4] = 1;
        }
        if (lbl_2_bss_1A824C->_19729E != 0) {
            lbl_2_bss_1A8234->layerFlags[1][8] = 1;
            lbl_2_bss_1A8234->layerFlags[1][9] = 1;
        }
        if ((s8)lbl_2_bss_1A824C->_1978FA == 0) {
            lbl_2_bss_1A824C->_1976A8 = fn_80062890(0x11);
        }
        lbl_2_bss_1A824C->_1978FA = 0;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

extern void fn_2_4A6E8(void);

// fn_2_3BA40, size:0x1E4
void fn_2_3BA40(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* e;
    switch (p->step) {
    case 0:
        p->counter = 0x3C;
        fn_2_4A6E8();
        lbl_2_bss_1A8234->layerFlags[1][31] = 1;
        lbl_2_bss_1A8234->layerFlags[1][32] = 1;
        lbl_2_bss_1A8234->layerFlags[1][33] = 1;
        lbl_2_bss_1A8234->layerFlags[1][34] = 1;
        lbl_2_bss_1A8234->layerFlags[1][35] = 1;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        e = (MenuPad*)&lbl_803C77B8;
        e += lbl_2_bss_1A824C->port;
        if (e->down & 0x300) {
            p->counter = 0x32;
            lbl_2_bss_1A8234->layerFlags[8][31] = 1;
            lbl_2_bss_1A8234->layerFlags[8][32] = 1;
            lbl_2_bss_1A8234->layerFlags[8][33] = 1;
            lbl_2_bss_1A8234->layerFlags[8][34] = 1;
            lbl_2_bss_1A8234->layerFlags[8][35] = 1;
            p->step = 3;
        }
        break;
    case 3: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 4;
        }
        break;
    }
    case 4:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_38824, size:0x21C
void fn_2_38824(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        p->counter = 0xA;
        if (p->timer == 1) {
            p->timer = 0;
            switch (lbl_2_bss_1A824C->_1972AC[0]) {
            case 0:
                lbl_2_bss_1A8234->layerFlags[1][5] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234->layerFlags[1][6] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234->layerFlags[1][7] = 1;
                break;
            }
        }
        if (p->_1A == 1) {
            p->_1A = 0;
            switch (lbl_2_bss_1A824C->_1972AC[1]) {
            case 0:
                lbl_2_bss_1A8234->layerFlags[1][10] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234->layerFlags[1][11] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234->layerFlags[1][12] = 1;
                break;
            }
        }
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_382A0, size:0x298
void fn_2_382A0(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    s16 m;
    switch (p->step) {
    case 0:
        p->counter = 5;
        m = p->arg;
        if ((m == 0 || m == 2) && lbl_2_bss_1A824C->_1972A4 != 0) {
            switch (lbl_2_bss_1A824C->_1972AC[0]) {
            case 0:
                lbl_2_bss_1A8234->layerFlags[8][5] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234->layerFlags[8][6] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234->layerFlags[8][7] = 1;
                break;
            }
        }
        m = p->arg;
        if ((m == 1 || m == 2) && lbl_2_bss_1A824C->_1972A6 != 0) {
            switch (lbl_2_bss_1A824C->_1972AC[1]) {
            case 0:
                lbl_2_bss_1A8234->layerFlags[8][10] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234->layerFlags[8][11] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234->layerFlags[8][12] = 1;
                break;
            }
        }
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        m = p->arg;
        if (m == 0 || m == 2) {
            lbl_2_bss_1A824C->_1972A4 = 0;
        }
        m = p->arg;
        if (m == 1 || m == 2) {
            lbl_2_bss_1A824C->_1972A6 = 0;
        }
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_38538, size:0x2EC
void fn_2_38538(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    switch (p->step) {
    case 0:
        p->counter = 0x1E;
        if (lbl_2_bss_1A824C->_19729C != 0) {
            lbl_2_bss_1A8234->layerFlags[8][2] = 1;
            lbl_2_bss_1A8234->layerFlags[8][3] = 1;
            lbl_2_bss_1A8234->layerFlags[8][4] = 1;
        }
        if (lbl_2_bss_1A824C->_1972A4 != 0) {
            switch (lbl_2_bss_1A824C->_1972AC[0]) {
            case 0:
                lbl_2_bss_1A8234->layerFlags[8][5] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234->layerFlags[8][6] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234->layerFlags[8][7] = 1;
                break;
            }
        }
        if (lbl_2_bss_1A824C->_19729E != 0) {
            lbl_2_bss_1A8234->layerFlags[8][8] = 1;
            lbl_2_bss_1A8234->layerFlags[8][9] = 1;
        }
        if (lbl_2_bss_1A824C->_1972A6 != 0) {
            switch (lbl_2_bss_1A824C->_1972AC[1]) {
            case 0:
                lbl_2_bss_1A8234->layerFlags[8][10] = 1;
                break;
            case 1:
                lbl_2_bss_1A8234->layerFlags[8][11] = 1;
                break;
            case 2:
            case 3:
                lbl_2_bss_1A8234->layerFlags[8][12] = 1;
                break;
            }
        }
        lbl_2_bss_1A824C->_1976A8 = fn_80062890(0x11);
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        lbl_2_bss_1A8248->_44F2 = 0;
        lbl_2_bss_1A824C->_1972A6 = 0;
        lbl_2_bss_1A824C->_1972A4 = 0;
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

#define FN353FC_ENT(a, b) lbl_80371C30[(a)->baseIdx + (b)->offset].obj

// fn_2_353FC, size:0x358
void fn_2_353FC(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = FN353FC_ENT(a, b);
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2:
        FN353FC_ENT(a, b)->flags |= 2;
        FN353FC_ENT(a, b)->_5C = 0;
        FN353FC_ENT(a, b)->_68 = 1;
        b->state = 3;
        break;
    case 3:
        if ((FN353FC_ENT(a, b)->_5C >> 16) >= 5) {
            b->state = 0x25;
        }
        break;
    case 0x25:
        if (lbl_2_bss_1A824C->_1976DA == 0) {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) <= 5) {
                p->_5C = 0x50000;
                FN353FC_ENT(a, b)->_68 = 0;
            } else {
                p->_68 = 4;
            }
        } else {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) >= 0xA) {
                p->_5C = 0xA0000;
                FN353FC_ENT(a, b)->_68 = 0;
            } else {
                p->_68 = 1;
            }
        }
        break;
    case 5:
        if (lbl_2_bss_1A824C->_1976DA == 0) {
            FN353FC_ENT(a, b)->_68 = 4;
        } else {
            FN353FC_ENT(a, b)->_68 = 1;
        }
        b->state = 6;
        break;
    case 6:
        if (lbl_2_bss_1A824C->_1976DA == 0) {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) == 0) {
                p->_68 = 0;
                b->state = 7;
            }
        } else {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) >= 0xF) {
                p->_68 = 0;
                b->state = 7;
            }
        }
        break;
    case 7:
        FN353FC_ENT(a, b)->flags &= ~2;
        break;
    }
}

// fn_2_35A14, size:0x3A0
void fn_2_35A14(MenuTask* a, MenuItemState* b) {
    s16 r = fn_2_53BC8(b);
    if (r != -1) {
        b->state = r;
    }
    switch (b->state) {
    case 0: {
        LayoutObj* p = FN353FC_ENT(a, b);
        p->flags &= ~2;
        b->state = 0x26;
        break;
    }
    case 2:
        fn_800363D8(a, b->offset, 1, 0xCF, b->unk10);
        FN353FC_ENT(a, b)->flags |= 2;
        FN353FC_ENT(a, b)->_5C = 0;
        FN353FC_ENT(a, b)->_68 = 1;
        b->state = 3;
        break;
    case 3: {
        LayoutObj* p = FN353FC_ENT(a, b);
        if ((p->_5C >> 16) >= 3) {
            p->_5C = 0x30000;
            FN353FC_ENT(a, b)->_68 = 0;
            b->state = 0x25;
        }
        break;
    }
    case 0x25:
        if (lbl_2_bss_1A824C->_1976D8 == b->index) {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) >= 8) {
                p->_5C = 0x80000;
                FN353FC_ENT(a, b)->_68 = 0;
            } else {
                p->_68 = 1;
            }
        } else {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) <= 3) {
                p->_5C = 0x30000;
                FN353FC_ENT(a, b)->_68 = 0;
            } else {
                p->_68 = 4;
            }
        }
        break;
    case 5:
        if (lbl_2_bss_1A824C->_1976D8 == b->index) {
            FN353FC_ENT(a, b)->_68 = 1;
        } else {
            FN353FC_ENT(a, b)->_68 = 4;
        }
        b->state = 6;
        break;
    case 6:
        if (lbl_2_bss_1A824C->_1976D8 == b->index) {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) >= 0xB) {
                p->_68 = 0;
                b->state = 7;
            }
        } else {
            LayoutObj* p = FN353FC_ENT(a, b);
            if ((p->_5C >> 16) == 0) {
                p->_68 = 0;
                b->state = 7;
            }
        }
        break;
    case 7:
        FN353FC_ENT(a, b)->flags &= ~2;
        break;
    }
}

// fn_2_38F48, size:0x26C
void fn_2_38F48(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* e;
    s32 last;
    switch (p->step) {
    case 0:
        last = 0;
        if (lbl_2_bss_1A8244->_E4[lbl_2_bss_1A8248->_4415] == 0 && lbl_2_bss_1A8248->_4415 < 3) {
            last = 1;
        }
        fn_2_38EA8();
        if (last) {
            p->counter = 0x12;
            lbl_2_bss_1A8234->layerFlags[1][5] = 1;
            fn_80062890(0x38);
            p->step = 1;
        } else {
            p->step = 4;
        }
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        e = (MenuPad*)&lbl_803C77B8;
        e += lbl_2_bss_1A824C->port;
        if (e->down & 0x100) {
            p->counter = 0x12;
            lbl_2_bss_1A8234->layerFlags[8][5] = 1;
            p->step = 3;
        }
        break;
    case 3: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 4;
        }
        break;
    }
    case 4:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}

// fn_2_391B4, size:0x254
void fn_2_391B4(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    u16 btn;
    switch (p->step) {
    case 0:
        p->counter = 0x1E;
        lbl_2_bss_1A824C->_1976E0 = 0;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        btn = MENUPAD_U16(repeat, lbl_2_bss_1A824C->port);
        if ((btn & 1) && lbl_2_bss_1A824C->_1976E0 == 1) {
            lbl_2_bss_1A824C->_1976E0 = 0;
        } else if ((btn & 2) && lbl_2_bss_1A824C->_1976E0 == 0) {
            lbl_2_bss_1A824C->_1976E0 = 1;
        }
        btn = MENUPAD_U16(down, lbl_2_bss_1A824C->port);
        if (btn & 0x100) {
            p->step = 3;
        } else if (btn & 0x200) {
            if (lbl_2_bss_1A824C->_1976E0 == 0) {
                lbl_2_bss_1A824C->_1976E0 = 1;
            } else {
                p->step = 3;
            }
        }
        if (p->arg == 0) {
            fn_8000FF04(4, 0x2E0, 0x64, 0xC8, 9, -1, 0);
        } else {
            fn_8000FF04(4, lbl_2_bss_1A8248->_4420 + 0x2ED, 0x64, 0xC8, 9, -1, 0);
        }
        break;
    case 3:
        p->counter = 0x10;
        p->step = 4;
        break;
    case 4: {
        if ((p->counter)-- == 0) {
            if (lbl_2_bss_1A824C->_1976E0 == 0) {
                q = lbl_803CC1B8->parent;
                q->signal = 1;
            } else {
                q = lbl_803CC1B8->parent;
                q->signal = 2;
            }
            fn_800B0A14_removeQueue(q);
            p->step = 0;
        }
        break;
    }
    }
}

// fn_2_397AC, size:0x214
void fn_2_397AC(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    u16 btn;
    switch (p->step) {
    case 0:
        p->counter = 0x1E;
        lbl_2_bss_1A824C->_1976DC = 0;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        btn = MENUPAD_U16(repeat, lbl_2_bss_1A824C->port);
        if ((btn & 1) && lbl_2_bss_1A824C->_1976DC == 1) {
            lbl_2_bss_1A824C->_1976DC = 0;
        } else if ((btn & 2) && lbl_2_bss_1A824C->_1976DC == 0) {
            lbl_2_bss_1A824C->_1976DC = 1;
        }
        btn = MENUPAD_U16(down, lbl_2_bss_1A824C->port);
        if (btn & 0x100) {
            p->step = 3;
        } else if (btn & 0x200) {
            if (lbl_2_bss_1A824C->_1976DC == 0) {
                lbl_2_bss_1A824C->_1976DC = 1;
            } else {
                p->step = 3;
            }
        }
        fn_8000FF04(4, 0x2DF, 0x64, 0xC8, 9, -1, 0);
        break;
    case 3:
        p->counter = 0x10;
        p->step = 4;
        break;
    case 4: {
        if ((p->counter)-- == 0) {
            if (lbl_2_bss_1A824C->_1976DC == 0) {
                q = lbl_803CC1B8->parent;
                q->signal = 1;
            } else {
                q = lbl_803CC1B8->parent;
                q->signal = 2;
            }
            fn_800B0A14_removeQueue(q);
            p->step = 0;
        }
        break;
    }
    }
}

// Subtitle cue: shown from frame `start` until frame `end`.
typedef struct MovieCue {
    s32 start;
    s32 end;
    s32 text;
} MovieCue;

extern MovieCue lbl_2_data_34E0[2][8];
extern void fn_800AD830(void*);
extern s32 fn_800AED24(void);

#define MOVIE_FRAME (lbl_2_bss_1A824C->_1976B0)
#define MOVIE_TICK (lbl_2_bss_1A824C->_1976B4)
#define MOVIE_CUE (lbl_2_bss_1A824C->_1976B8)
#define MOVIE_CUE_ON (lbl_2_bss_1A824C->_1976BC)

// fn_2_37630, size:0x3A0
void fn_2_37630(void) {
    Fn37460Data* d = &lbl_2_bss_15A0;
    MenuScreenTask* o = lbl_803CC1B8;
    void* p;
    s32 sz;
    switch ((s8)o->step) {
    case 0:
        MOVIE_FRAME = 0;
        MOVIE_TICK = 0;
        MOVIE_CUE = 0;
        MOVIE_CUE_ON = 0;
        fn_2_4E824();
        p = _OSAllocFromHeap(0x20, 0x1C0);
        d->heap = p;
        memset(p, 0, 0x1C0);
        d->size = 0x400000;
        p = _OSAllocFromHeap(0x20, 0x400000);
        d->alt = p;
        fn_800ADC40(p, d->size);
        o->step++;
        return;
    case 1:
        if (fn_800ADB04(lbl_2_data_12170, d->heap, 1, 0) != 0) {
            fn_80009018(d->heap);
            o->step++;
        }
        break;
    case 2:
        if (fn_800ADAFC() != 0) {
            sz = fn_800AD6BC(d->heap);
            p = _OSAllocFromHeap(0x20, sz);
            d->buf = p;
            fn_800AD500(d->heap, p);
            fn_800AD95C(d->heap, 1);
            o->step++;
            return;
        }
        break;
    case 3: {
        MenuPad* e = (MenuPad*)&lbl_803C77B8;
        e += lbl_2_bss_1A824C->port;
        if (e->down & 0x1000) {
            d->skipped = 1;
            fn_800AD830(d->heap);
            o->step++;
            return;
        }
        MOVIE_TICK++;
        fn_800AD070();
        if (fn_800AED24() == 1) {
            s32 sel;
            MOVIE_FRAME++;
            sel = lbl_2_bss_1A8248->_441C == 5;
            if (MOVIE_FRAME == lbl_2_data_34E0[sel][MOVIE_CUE].start && MOVIE_CUE_ON == 0 &&
                lbl_2_data_34E0[sel][MOVIE_CUE].start != -1) {
                lbl_2_bss_1A824C->_19774C = lbl_2_data_34E0[sel][MOVIE_CUE].text;
                MOVIE_CUE_ON = 1;
                lbl_2_bss_1A8234->layerFlags[1][4] = 1;
            } else if (MOVIE_FRAME == lbl_2_data_34E0[sel][MOVIE_CUE].end && MOVIE_CUE_ON == 1 &&
                       lbl_2_data_34E0[sel][MOVIE_CUE].start != -1) {
                lbl_2_bss_1A8234->layerFlags[8][4] = 1;
                MOVIE_CUE++;
                MOVIE_CUE_ON = 0;
            }
        }
        if (fn_800AD780(d->heap) != 0) {
            o->step++;
            return;
        }
        break;
    }
    case 4:
        if (fn_800AD780(d->heap) != 0) {
            fn_80009018(NULL);
            fn_800AD9F4(d->heap);
            fn_800ADBFC();
            o->step++;
            return;
        }
        break;
    case 5:
        fn_2_4E7EC();
        p = lbl_803CC1B8->parent;
        ((MenuScreenTask*)p)->signal = 1;
        fn_800B0A14_removeQueue(p);
        o->step = 0;
        return;
    }
}

extern MenuDrawArea* lbl_2_bss_1A8230;
extern GXColor lbl_2_data_12270;
extern void fn_2_54474(void);
extern BOOL fn_80068514(u32 frames, u8 target);
extern void fn_8006877C(u8 track);
extern void fn_800A86B4(s32 cmd);

// fn_2_379D0, size:0x3A0
void fn_2_379D0(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        if (fn_2_4EABC() == 1) {
            o->step = 1;
        }
        break;
    case 1: {
        GXColor clear = lbl_2_data_12270;
        GXSetCopyClear(clear, 0xFFFFFF);
        changeScene(1, 6);
        fn_2_515DC(4);
        lbl_2_bss_1A8234->done = 0;
        lbl_2_bss_1A8230->_32A86 = 0;
        fn_2_54474();
        fn_2_245C8();
        lbl_2_bss_1A824C->_1976E4 = 0x168;
        lbl_2_bss_15A0.skipped = 0;
        o->step = 2;
        break;
    }
    case 2:
        o->step = 3;
        break;
    case 3:
        if (lbl_8037169C.done != 0) {
            q = fn_800B0A5C_insertQueue(fn_2_37630, 2);
            q->step = 0;
            o->signal = 0;
            o->step = 4;
        }
        break;
    case 4:
        if (o->signal != 0) {
            if (lbl_2_bss_15A0.skipped) {
                changeScene(3, 6);
                lbl_2_bss_1A8234->layerFlags[8][4] = 1;
                lbl_2_bss_1A8234->layerFlags[8][5] = 1;
                lbl_2_bss_1A8234->layerFlags[8][1] = 1;
                lbl_2_bss_1A8234->layerFlags[8][3] = 1;
                o->step = 7;
            } else {
                fn_8006877C(0xB);
                if (lbl_2_bss_1A8248->_441C == 5) {
                    fn_2_422FC(1);
                } else {
                    fn_2_422FC(0);
                }
                q = fn_800B0A5C_insertQueue(fn_2_42388, 2);
                q->step = 0;
                o->signal = 0;
                o->step = 5;
            }
        }
        break;
    case 5: {
        BOOL fading = fn_80068514(0x78, 0x7F);
        if (o->signal == 1) {
            lbl_2_bss_1A824C->_19783F = 0;
            changeScene(3, 6);
            lbl_2_bss_1A8234->layerFlags[8][4] = 1;
            lbl_2_bss_1A8234->layerFlags[8][5] = 1;
            lbl_2_bss_1A8234->layerFlags[8][1] = 1;
            lbl_2_bss_1A8234->layerFlags[8][3] = 1;
            o->step = 6;
        }
        if ((MENUPAD_U16(down, lbl_2_bss_1A824C->port) & 0x1000) && (u8)fading == 0) {
            lbl_2_bss_1A824C->_19783F = 1;
        }
        break;
    }
    case 6:
        if (fn_8006862C(0x78, 0) == 0) {
            o->step = 7;
        }
        break;
    case 7:
        if (lbl_8037169C._13 != 0) {
            GXColor clear;
            fn_800A86B4(3);
            clear = lbl_2_data_12270;
            GXSetCopyClear(clear, 0xFFFFFF);
            lbl_2_bss_1A8234->done = 1;
            lbl_2_bss_1A8230->_32A86 = 1;
            o->step = 8;
        }
        break;
    case 8:
        fn_2_4E8E0();
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

extern u8 lbl_800EFBA4[];
extern int sndFXStartEx(int, int, int, int);

// fn_2_39408, size:0x3A4
void fn_2_39408(void) {
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    u16 btn;
    switch (p->step) {
    case 0:
        switch (lbl_2_bss_1A824C->_1972B6) {
        case 0:
            lbl_2_bss_1A8234->layerFlags[1][36] = 1;
            break;
        case 1:
            lbl_2_bss_1A8234->layerFlags[1][37] = 1;
            break;
        case 2:
            lbl_2_bss_1A8234->layerFlags[1][38] = 1;
            break;
        }
        p->counter = 0xA;
        p->arg = 0;
        lbl_2_bss_1A824C->_1976DE = lbl_2_bss_1A824C->_1972B7;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        btn = MENUPAD_U16(repeat, lbl_2_bss_1A824C->port);
        if ((btn & 1) && lbl_2_bss_1A824C->_1976DE == 1) {
            lbl_2_bss_1A824C->_1976DE = 0;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if ((btn & 2) && lbl_2_bss_1A824C->_1976DE == 0) {
            lbl_2_bss_1A824C->_1976DE = 1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = MENUPAD_U16(down, lbl_2_bss_1A824C->port);
        if (btn & 0x100) {
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p->step = 3;
        } else if (btn & 0x200) {
            if (lbl_2_bss_1A824C->_1976DE == 0) {
                lbl_2_bss_1A824C->_1976DE = 1;
            } else {
                p->arg = 1;
                p->step = 3;
            }
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 3:
        switch (lbl_2_bss_1A824C->_1972B6) {
        case 0:
            lbl_2_bss_1A8234->layerFlags[8][36] = 1;
            break;
        case 1:
            lbl_2_bss_1A8234->layerFlags[8][37] = 1;
            break;
        case 2:
            lbl_2_bss_1A8234->layerFlags[8][38] = 1;
            break;
        }
        p->counter = 0xA;
        p->step = 4;
        break;
    case 4:
        if ((p->counter)-- == 0) {
            if (lbl_2_bss_1A824C->_1976DE == 0) {
                q = lbl_803CC1B8->parent;
                q->signal = 1;
            } else if (p->arg == 0) {
                q = lbl_803CC1B8->parent;
                q->signal = 2;
            } else {
                q = lbl_803CC1B8->parent;
                q->signal = 3;
            }
            fn_800B0A14_removeQueue(q);
            p->step = 0;
        }
        break;
    }
}

// Grid layouts for the selection cursor: highest column and row index.
typedef struct GridSize {
    s16 maxCol;
    s16 maxRow;
} GridSize;

extern GridSize lbl_2_data_122A8[4];

#define GRID_COL (lbl_2_bss_1A824C->_19770C)
#define GRID_ROW (lbl_2_bss_1A824C->_19770E)
#define GRID_SEL (lbl_2_bss_1A824C->_197710)
#define GRID_PREV (lbl_2_bss_1A824C->_197712)
#define GRID_LAYOUT (lbl_2_bss_1A824C->_197714)

// fn_2_3A8FC, size:0x60C
// NONMATCHING 99.7%: r30/r31 swapped between the task pointer and the pad pointer (see docs/patterns/regalloc.md)
#if NONMATCHING
void fn_2_3A8FC(void) {
    u8* repeat;
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    u16 btn;
    s32 pad;
    switch (p->step) {
    case 0:
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            lbl_2_bss_1A8234->layerFlags[1][53] = 1;
        } else {
            lbl_2_bss_1A8234->layerFlags[1][7] = 1;
        }
        p->counter = 0xC;
        p->step = 1;
        break;
    case 1: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 2;
        }
        break;
    }
    case 2:
        repeat = (u8*)&((MenuPad*)&lbl_803C77B8)->repeat;
        btn = *(u16*)(repeat + lbl_2_bss_1A824C->port * sizeof(MenuPad));
        if (btn & 1) {
            GRID_PREV = GRID_SEL;
            GRID_COL--;
            if (GRID_COL < 0) {
                GRID_COL = lbl_2_data_122A8[GRID_LAYOUT].maxCol;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 2) {
            GRID_PREV = GRID_SEL;
            GRID_COL++;
            if (GRID_COL > lbl_2_data_122A8[GRID_LAYOUT].maxCol) {
                GRID_COL = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = *(u16*)(repeat + lbl_2_bss_1A824C->port * sizeof(MenuPad));
        if (btn & 8) {
            if (lbl_2_data_122A8[GRID_LAYOUT].maxRow != 0) {
                GRID_PREV = GRID_SEL;
                GRID_ROW--;
                if (GRID_ROW < 0) {
                    GRID_ROW = lbl_2_data_122A8[GRID_LAYOUT].maxRow;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        } else if (btn & 4) {
            if (lbl_2_data_122A8[GRID_LAYOUT].maxRow != 0) {
                GRID_PREV = GRID_SEL;
                GRID_ROW++;
                if (GRID_ROW > lbl_2_data_122A8[GRID_LAYOUT].maxRow) {
                    GRID_ROW = 0;
                }
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
        GRID_SEL = GRID_COL + GRID_ROW * (lbl_2_data_122A8[GRID_LAYOUT].maxCol + 1);
        pad = lbl_2_bss_1A824C->port * sizeof(MenuPad);
        btn = *(u16*)(repeat + pad);
        if ((btn & 8) || (btn & 4)) {
            if (lbl_2_data_122A8[GRID_LAYOUT].maxRow == 0) {
                goto check_confirm;
            }
            if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                lbl_2_bss_1A8234->layerFlags[3][53] = 1;
            } else {
                lbl_2_bss_1A8234->layerFlags[3][7] = 1;
            }
            p->step = 3;
        } else if ((btn & 1) || (btn & 2)) {
            if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                lbl_2_bss_1A8234->layerFlags[3][53] = 1;
            } else {
                lbl_2_bss_1A8234->layerFlags[3][7] = 1;
            }
            p->step = 3;
        } else {
        check_confirm:
            btn = *(u16*)((u8*)&((MenuPad*)&lbl_803C77B8)->down + pad);
            if (btn & 0x100) {
                if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                    lbl_2_bss_1A8234->layerFlags[8][53] = 1;
                } else {
                    lbl_2_bss_1A8234->layerFlags[8][7] = 1;
                }
                p->counter = 0xC;
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                p->step = 4;
            } else if (btn & 0x200) {
                if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                    lbl_2_bss_1A8234->layerFlags[8][53] = 1;
                } else {
                    lbl_2_bss_1A8234->layerFlags[8][7] = 1;
                }
                p->counter = 0xC;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
                p->step = 4;
            }
        }
        break;
    case 3:
        p->step = 2;
        break;
    case 4: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 5;
        }
        break;
    }
    case 5:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}
#endif

extern s16 lbl_2_data_373C[20];
extern s16 lbl_2_data_296B8[36];
extern u8 lbl_800E869C[];
typedef struct Unk8010B42C {
    u8 _00[0xC];
    s16 gridLayout[1]; // TODO type: indexed by fn_2_44F14
} Unk8010B42C;
extern Unk8010B42C lbl_8010B42C;
extern MenuDef lbl_800FEF70[];
extern void fn_80053FE8(void);
extern s32 fn_8006C79C(u8);

#define PICK_ID (lbl_2_bss_1A824C->_197706)
#define PICK_COL (lbl_2_bss_1A824C->_197708)
#define PICK_ROW (lbl_2_bss_1A824C->_19770A)

// fn_2_3AF08, size:0xB38
// NONMATCHING 98%: r30/r31 swapped (task vs pad pointer), dead `cmpwi 0x14` before the loop, lbl_8010B42C+0xC lhax folded
#if NONMATCHING
void fn_2_3AF08(void) {
    u8* repeat;
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    u16 btn;
    s32 i;
    s32 n;
    switch (p->step) {
    case 0:
        n = 0;
        for (i = 0; i < 20; i++) {
            if ((s8)lbl_2_bss_1A8248->_43C2[i] == 1 && lbl_2_data_373C[i] == 0) {
                lbl_2_bss_1A824C->_1978B3[n++] = 1;
            }
        }
        changeScene(3, 6);
        p->step = 1;
        break;
    case 1:
        if (lbl_8037169C._13 != 0) {
            p->step = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A824C->_197730 = 6;
        lbl_2_bss_1A8248->_44F2 = 2;
        PICK_ID = 0;
        PICK_COL = 1;
        PICK_ROW = 0;
        lbl_2_bss_1A8234->layerFlags[1][49] = 1;
        lbl_2_bss_1A8234->layerFlags[1][52] = 1;
        lbl_8034E978._03 = lbl_2_bss_1A8248->_4415;
        fn_800B0A5C_insertQueue(fn_80053FE8, 0);
        lbl_8034E978.menu = 0xE;
        lbl_8034E978.menu = 0xE;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0xE].track;
        changeScene(1, 6);
        p->step = 3;
        break;
    case 3:
        (p->counter)--;
        if (lbl_8037169C.done != 0) {
            p->step = 4;
        }
        break;
    case 4:
        p->counter = 0x28;
        lbl_2_bss_1A8234->layerFlags[1][50] = 1;
        p->step = 5;
        break;
    case 5: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t <= 0) {
            p->step = 6;
        }
        break;
    }
    case 6:
        repeat = (u8*)&((MenuPad*)&lbl_803C77B8)->repeat;
        btn = *(u16*)(repeat + lbl_2_bss_1A824C->port * sizeof(MenuPad));
        if (btn & 1) {
            PICK_COL--;
            if (PICK_COL == 0 && (PICK_ROW == 0 || PICK_ROW == 5)) {
                PICK_COL = 4;
            } else if (PICK_COL < 0) {
                PICK_COL = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 2) {
            PICK_COL++;
            if (PICK_COL == 5 && (PICK_ROW == 0 || PICK_ROW == 5)) {
                PICK_COL = 1;
            } else if (PICK_COL > 5) {
                PICK_COL = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = *(u16*)(repeat + lbl_2_bss_1A824C->port * sizeof(MenuPad));
        if (btn & 8) {
            PICK_ROW--;
            if (PICK_ROW == 0 && (PICK_COL == 0 || PICK_COL == 5)) {
                PICK_ROW = 4;
            } else if (PICK_ROW < 0) {
                PICK_ROW = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 4) {
            PICK_ROW++;
            if (PICK_ROW == 5 && (PICK_COL == 0 || PICK_COL == 5)) {
                PICK_ROW = 1;
            } else if (PICK_ROW > 5) {
                PICK_ROW = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        PICK_ID = lbl_2_data_296B8[PICK_COL + PICK_ROW * 6];
        btn = MENUPAD_U16(down, lbl_2_bss_1A824C->port);
        if (btn & 0x40) {
            lbl_2_bss_1A824C->_197730 = 1;
            lbl_2_bss_1A8234->layerFlags[11][52] = 1;
            lbl_2_bss_1A8234->layerFlags[8][50] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p->counter = 0x32;
            p->step = 7;
        } else if (btn & 0x20) {
            lbl_2_bss_1A824C->_197730 = 1;
            lbl_2_bss_1A8234->layerFlags[12][52] = 1;
            lbl_2_bss_1A8234->layerFlags[8][50] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p->counter = 0x32;
            p->step = 7;
        } else if (btn & 0x100) {
            if (fn_8006C79C(lbl_800E869C[PICK_ID]) == 1) {
                GRID_PREV = 0;
                GRID_SEL = 0;
                GRID_COL = 0;
                GRID_ROW = 0;
                GRID_LAYOUT = lbl_8010B42C.gridLayout[fn_2_44F14(lbl_800E869C[PICK_ID])];
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                p->step = 8;
            } else {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            }
        } else if (btn & 0x200) {
            lbl_2_bss_1A8234->layerFlags[8][50] = 1;
            p->counter = 0x28;
            p->step = 0xE;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        }
        break;
    case 7: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 0xA;
        }
        break;
    }
    case 8:
        q = fn_800B0A5C_insertQueue(fn_2_3A8FC, 2);
        q->step = 0;
        p->signal = 0;
        p->step = 9;
        break;
    case 9:
        if (p->signal == 1) {
            p->step = 6;
        }
        break;
    case 10:
        p->counter = 0x1E;
        lbl_8034E978.menu = 0xF;
        lbl_8034E978.prevTrack = lbl_8034E978.track;
        lbl_8034E978.track = lbl_800FEF70[0xF].track;
        lbl_2_bss_1A8234->layerFlags[1][51] = 1;
        p->step = 0xB;
        break;
    case 11: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t <= 0) {
            p->step = 0xC;
        }
        break;
    }
    case 12:
        btn = MENUPAD_U16(down, lbl_2_bss_1A824C->port);
        if (btn & 0x40) {
            lbl_2_bss_1A824C->_197730 = 6;
            lbl_2_bss_1A8234->layerFlags[11][52] = 1;
            lbl_2_bss_1A8234->layerFlags[8][51] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p->counter = 0x1E;
            lbl_8034E978.menu = 0xE;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0xE].track;
            p->step = 0xD;
        } else if (btn & 0x20) {
            lbl_2_bss_1A824C->_197730 = 6;
            lbl_2_bss_1A8234->layerFlags[12][52] = 1;
            lbl_2_bss_1A8234->layerFlags[8][51] = 1;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p->counter = 0x1E;
            lbl_8034E978.menu = 0xE;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0xE].track;
            p->step = 0xD;
        } else if (btn & 0x200) {
            lbl_2_bss_1A8234->layerFlags[8][51] = 1;
            p->counter = 0x1E;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            p->step = 0xE;
        }
        break;
    case 13: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 4;
        }
        break;
    }
    case 14: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            changeScene(3, 6);
            p->step = 0xF;
        }
        break;
    }
    case 15:
        if (lbl_8037169C._13 != 0) {
            p->step = 0x10;
        }
        break;
    case 16:
        lbl_2_bss_1A8248->_44F2 = 0;
        lbl_8034E978._26 = 1;
        lbl_2_bss_1A8234->layerFlags[8][49] = 1;
        lbl_2_bss_1A8234->layerFlags[8][52] = 1;
        p->counter = 0x32;
        changeScene(1, 6);
        p->step = 0x11;
        break;
    case 17:
        (p->counter)--;
        if (lbl_8037169C.done != 0) {
            p->step = 0x12;
        }
        break;
    case 18:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}
#endif

extern s16 lbl_2_data_29700[36];
extern void fn_2_72054(s32 index, s8 value);

// Switch the menu screen: remember the current track and take the new menu's track.
#define SET_MENU_SCREEN(m)                                         \
    do {                                                           \
        lbl_8034E978.menu = (m);                                   \
        lbl_8034E978.prevTrack = lbl_8034E978.track;               \
        lbl_8034E978.track = lbl_800FEF70[m].track;                \
    } while (0)

// fn_2_399C0, size:0xF3C
// NONMATCHING 98%: r30/r31 swapped, &g_d_GameSettings hoisted to r31 in the original, lbl_8010B42C+0xC lhax folded
#if NONMATCHING
void fn_2_399C0(void) {
    u8* repeat;
    MenuScreenTask* p = lbl_803CC1B8;
    MenuScreenTask* q;
    u16 btn;
    s32 pad;
    s32 i;
    switch (p->step) {
    case 0:
        fn_2_45204();
        fn_2_45A84();
        for (i = 0; i < 54; i++) {
            if ((s8)lbl_2_bss_1A8248->_444D[i] == 1) {
                lbl_2_bss_1A824C->_1978F8 = 1;
            }
            if ((s8)lbl_2_bss_1A8248->_44B9[i] == 1) {
                lbl_2_bss_1A824C->_1978F9 = 1;
            }
        }
        if (lbl_2_bss_1A824C->_1978F7 == 2) {
            p->step = 0x11;
        } else {
            changeScene(3, 6);
            p->step = 1;
        }
        break;
    case 1:
        if (lbl_8037169C._13 != 0) {
            p->step = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A8248->_44F2 = 2;
        lbl_2_bss_1A824C->_1978F6 = 0;
        PICK_ID = 0;
        PICK_COL = 1;
        PICK_ROW = 0;
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            lbl_2_bss_1A8234->layerFlags[1][55] = 1;
            lbl_2_bss_1A8234->layerFlags[1][56] = 1;
        } else {
            lbl_2_bss_1A8234->layerFlags[1][8] = 1;
            lbl_2_bss_1A8234->layerFlags[1][9] = 1;
        }
        if (lbl_2_bss_1A824C->_1978F7 == 0) {
            lbl_2_bss_1A824C->_1978F6 = 0;
        } else {
            lbl_2_bss_1A824C->_1978F6 = 1;
        }
        changeScene(1, 6);
        p->step = 3;
        break;
    case 3:
        (p->counter)--;
        if (lbl_8037169C.done != 0) {
            p->step = 4;
        }
        break;
    case 4:
        p->counter = 0x28;
        if (lbl_2_bss_1A824C->_1978F7 == 0) {
            lbl_8034E978._03 = lbl_2_bss_1A8248->_4415;
            fn_800B0A5C_insertQueue(fn_80053FE8, 0);
            if (lbl_2_bss_1A824C->_1978F8 == 1) {
                if (lbl_2_bss_1A824C->_197843 == 0) {
                    if (g_d_GameSettings.someChallengeModeFlag == 1) {
                        SET_MENU_SCREEN(0x28);
                    } else {
                        SET_MENU_SCREEN(0x27);
                    }
                }
                fn_80062890(0x39);
            } else if (lbl_2_bss_1A824C->_197843 == 0) {
                SET_MENU_SCREEN(0x29);
            } else if (lbl_2_bss_1A824C->_197843 == 1) {
                SET_MENU_SCREEN(0x2A);
            } else {
                SET_MENU_SCREEN(0x2A);
            }
            lbl_2_bss_1A824C->_1978F6 = 0;
        } else {
            lbl_8034E978._03 = lbl_2_bss_1A8248->_4415;
            fn_800B0A5C_insertQueue(fn_80053FE8, 0);
            if (lbl_2_bss_1A824C->_1978F9 == 1) {
                SET_MENU_SCREEN(0x2B);
                fn_80062890(0x3F);
            } else {
                SET_MENU_SCREEN(0x2C);
            }
            if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                lbl_2_bss_1A8234->layerFlags[1][59] = 1;
                lbl_2_bss_1A8234->layerFlags[3][56] = 1;
            } else {
                lbl_2_bss_1A8234->layerFlags[1][12] = 1;
                lbl_2_bss_1A8234->layerFlags[3][9] = 1;
            }
            lbl_2_bss_1A824C->_1978F6 = 1;
        }
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            lbl_2_bss_1A8234->layerFlags[1][58] = 1;
        } else {
            lbl_2_bss_1A8234->layerFlags[1][11] = 1;
        }
        p->step = 5;
        break;
    case 5: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t <= 0) {
            if (lbl_2_bss_1A824C->_1978F7 == 0) {
                p->step = 6;
            } else {
                p->step = 8;
            }
        }
        break;
    }
    case 6:
        if (MENUPAD_U16(down, lbl_2_bss_1A824C->port) & 0x100) {
            p->counter = 0xA;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            p->step = 7;
        }
        break;
    case 7: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            lbl_2_bss_1A824C->_1978F6 = 1;
            if (lbl_2_bss_1A824C->_1978F9 == 1) {
                SET_MENU_SCREEN(0x2B);
                fn_80062890(0x3F);
            } else {
                SET_MENU_SCREEN(0x2C);
            }
            if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                lbl_2_bss_1A8234->layerFlags[1][59] = 1;
                lbl_2_bss_1A8234->layerFlags[3][56] = 1;
                lbl_2_bss_1A8234->layerFlags[3][58] = 1;
            } else {
                lbl_2_bss_1A8234->layerFlags[1][12] = 1;
                lbl_2_bss_1A8234->layerFlags[3][9] = 1;
                lbl_2_bss_1A8234->layerFlags[3][11] = 1;
            }
            p->step = 8;
        }
        break;
    }
    case 8:
        repeat = (u8*)&((MenuPad*)&lbl_803C77B8)->repeat;
        btn = *(u16*)(repeat + lbl_2_bss_1A824C->port * sizeof(MenuPad));
        if (btn & 1) {
            PICK_COL--;
            if (PICK_COL == 0 && PICK_ROW == 0) {
                PICK_COL = 5;
            } else if (PICK_COL == 0 && PICK_ROW == 5) {
                PICK_COL = 4;
            } else if (PICK_COL < 0) {
                PICK_COL = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 2) {
            PICK_COL++;
            if (PICK_COL == 6 && PICK_ROW == 0) {
                PICK_COL = 1;
            } else if (PICK_COL == 5 && PICK_ROW == 5) {
                PICK_COL = 1;
            } else if (PICK_COL > 5) {
                PICK_COL = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        btn = *(u16*)(repeat + lbl_2_bss_1A824C->port * sizeof(MenuPad));
        if (btn & 8) {
            PICK_ROW--;
            if (PICK_ROW == 0 && PICK_COL == 0) {
                PICK_ROW = 4;
            } else if (PICK_ROW < 0 && PICK_COL == 5) {
                PICK_ROW = 4;
            } else if (PICK_ROW < 0) {
                PICK_ROW = 5;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        } else if (btn & 4) {
            PICK_ROW++;
            if (PICK_ROW == 5 && PICK_COL == 0) {
                PICK_ROW = 1;
            } else if (PICK_ROW == 5 && PICK_COL == 5) {
                PICK_ROW = 0;
            } else if (PICK_ROW > 5) {
                PICK_ROW = 0;
            }
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
        PICK_ID = lbl_2_data_29700[PICK_COL + PICK_ROW * 6];
        pad = lbl_2_bss_1A824C->port * sizeof(MenuPad);
        btn = *(u16*)(repeat + pad);
        if ((btn & 8) || (btn & 4) || (btn & 1) || (btn & 2)) {
            if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                lbl_2_bss_1A8234->layerFlags[6][59] = 1;
            } else {
                lbl_2_bss_1A8234->layerFlags[6][12] = 1;
            }
            p->step = 9;
        } else {
            btn = *(u16*)((u8*)&((MenuPad*)&lbl_803C77B8)->down + pad);
            if (btn & 0x100) {
                if (PICK_ROW == 0 && PICK_COL == 5) {
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    p->step = 0xC;
                } else if (fn_8006C79C(lbl_800E869C[PICK_ID]) == 1) {
                    GRID_PREV = 0;
                    GRID_SEL = 0;
                    GRID_COL = 0;
                    GRID_ROW = 0;
                    GRID_LAYOUT = lbl_8010B42C.gridLayout[fn_2_44F14(lbl_800E869C[PICK_ID])];
                    sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                    p->step = 0xA;
                } else {
                    sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                }
            } else if ((btn & 0x200) && (PICK_ROW != 0 || PICK_COL != 5)) {
                PICK_ROW = 0;
                PICK_COL = 5;
                PICK_ID = lbl_2_data_29700[PICK_COL + PICK_ROW * 6];
                if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
                    lbl_2_bss_1A8234->layerFlags[6][59] = 1;
                } else {
                    lbl_2_bss_1A8234->layerFlags[6][12] = 1;
                }
                p->step = 9;
                sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            }
        }
        break;
    case 9:
        p->step = 8;
        break;
    case 10:
        q = fn_800B0A5C_insertQueue(fn_2_3A8FC, 2);
        q->step = 0;
        p->signal = 0;
        p->step = 0xB;
        break;
    case 11:
        if (p->signal == 1) {
            p->step = 8;
        }
        break;
    case 12:
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            lbl_2_bss_1A8234->layerFlags[8][59] = 1;
            lbl_2_bss_1A8234->layerFlags[8][58] = 1;
            p->counter = 0x28;
            p->step = 0xD;
        } else {
            p->counter = 0xA;
            p->step = 0x12;
        }
        break;
    case 13: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            changeScene(3, 6);
            p->step = 0xE;
        }
        break;
    }
    case 14:
        if (lbl_8037169C._13 != 0) {
            p->step = 0xF;
        }
        break;
    case 15:
        lbl_8034E978._26 = 1;
        lbl_2_bss_1A8248->_44F2 = 0;
        if ((s8)lbl_2_bss_1A8248->_44F4 == 0) {
            lbl_2_bss_1A8234->layerFlags[8][55] = 1;
            lbl_2_bss_1A8234->layerFlags[8][56] = 1;
            p->counter = 0x32;
        } else {
            p->counter = 1;
        }
        changeScene(1, 6);
        fn_2_72054(0, 4);
        p->step = 0x10;
        break;
    case 16:
        (p->counter)--;
        if (lbl_8037169C.done != 0) {
            p->step = 0x11;
        }
        break;
    case 17:
        q = p->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
        break;
    case 18: {
        s16 t = p->counter;
        p->counter = t - 1;
        if (t == 0) {
            p->step = 0x11;
        }
        break;
    }
    }
    if (lbl_2_bss_1A824C->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        p->step = 0;
    }
}
#endif
