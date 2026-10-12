// Translation unit 0x11C0: .text 0x94854..0x96D94 (formerly the auto_00_00094854_text split).
#define REP_HEADER_FN repHeader_menus_11C0
#include "header_rep_inline.h"
#include "menus/auto_00_00094854_text.h"

extern void fn_80034E20(void* object, void* data);

#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"
#include "main/menu_globals.h"
#include "main/file_800527C4.h"
#include "menus/menu_work.h"
#include "menus/rep_05F0.h"
#include "menus/menu_asset.h"

// .data 0x30918..0x312A4: header statics (unreferenced copies), then the sprite
// layouts for fn_80034E20.
#include "menus/debug_menu_data.h"
#include "menus/option_names_data.h"
#include "menus/field_position_data.h"

// Sprite layout (fn_80034E20).
MenuSpriteDesc lbl_2_data_30D04[39] = {
    {0, 0xB, 0.0f, 0.0f, -1, 0, 0x14, {0, 0xFF}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x12, 0.0f, 0.0f, -1, 1, 0x14, {0, 0xFF}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 9, 0.0f, 0.0f, -1, 1, 0x13, {0, 1}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x13, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xFF}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x14, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xFF}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xA, 0.0f, 0.0f, -1, 1, 0x14, {0, 0}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0xD, 0.0f, 0.0f, -1, 0, 0x14, {0, 0}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xD, 0.0f, 0.0f, -1, 0, 0x14, {0, 0}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xD, 0.0f, 0.0f, -1, 0, 0x14, {0, 0}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xC, 0.0f, 0.0f, -1, 1, 0x13, {0, 6}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 0xC, 0.0f, 0.0f, -1, 1, 0x13, {0, 7}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0xC, 0.0f, 0.0f, -1, 1, 0x13, {0, 8}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xF, 0.0f, 0.0f, -1, 1, 0x13, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xF, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xF, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0xE, 0.0f, 0.0f, -1, 1, 0x12, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 0xE, 0.0f, 0.0f, -1, 1, 0x12, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 0xE, 0.0f, 0.0f, -1, 1, 0x12, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 6},
    {0, 0x1A, 0.0f, 0.0f, -1, 1, 0x13, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 0x1A, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 0x1A, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 5},
    {0, 0x10, 0.0f, 0.0f, -1, 1, 0x13, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 0x10, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 0x10, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 4},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 0x15, 0.0f, 0.0f, -1, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 7, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 7, {0, 9}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 2},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 0x13, {0, 0xA}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 3},
    {0, 0x1C, 0.0f, 0.0f, -0x100, 1, 0x13, {0, 0xB}, 0x12, {0, 0, 0}, 0.0f, 0, 1, 1},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, {0, 0}, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};
// Sprite layout (fn_80034E20).
MenuSpriteDesc lbl_2_data_311E4[6] = {
    {0, 0x12D, 0.0f, 0.0f, -1, 1, 0x16, {0, 0xFF}, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x12D, 0.0f, 0.0f, -1, 0, 0x16, {0, 0xFF}, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x12B, 0.0f, 0.0f, -1, 1, 0x16, {0, 0}, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x12B, 0.0f, 0.0f, -1, 0, 0x16, {0, 1}, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {0, 0x12E, 0.0f, 0.0f, -1, 1, 0x15, {0, 0xFF}, 1, {0, 0, 0}, 0.0f, 0, 1, 0},
    {3, 0, 0.0f, 0.0f, 0, 0, 0, {0, 0}, 0, {0, 0, 0}, 0.0f, 0, 0, 0},
};

extern void* lbl_803CC1B8[];

extern void fn_80062674(s32 index);

extern MenuData* lbl_2_bss_1A824C[];
extern MenuDef lbl_800FEF70[];
extern void fn_80053FE8(void);
extern void fn_2_96AD4(void);
extern s32 fn_80042DA8(void*, s32, s32);
extern s32 fn_800626EC(s32 index);
static inline void tally94(MenuTask* o, s32 id, s32 f, s32* total, s32* hits) {
    *total += 1;
    *hits += fn_80042DA8(o, id, f) != 0;
}
#define ENT94(o, k, i) MENU_SLOT_OBJ(lbl_80371C30, (k) + (o)->baseIdx + (i))
extern void fn_2_96698(void);
extern void fn_2_96118(MenuTask* object);
extern void fn_2_95654(MenuTask* object);
extern void fn_2_94A8C(MenuTask* object);
#define R94(o, k) MENU_SLOT_OBJ(&lbl_80371C30[k], (o)->baseIdx)
#define D94(o, k) ((&lbl_80371C30[k])[(o)->baseIdx].obj)
#define E94(o, k, i) MENU_SLOT_OBJ(lbl_80371C30, (k) + (o)->baseIdx + (i))
#define S94 (lbl_2_bss_1033C.cursor)
#define F58_SET(p) ((p)->color = ((p)->color & ~0xFFU) | 0xFF)
#define F58_CLR(p) ((p)->color = (p)->color & ~0xFFU)

// fn_2_96D20, size:0x74
void fn_2_96D20(void) {
    fn_800B0A5C_insertQueue(fn_80053FE8, 0x3000);
    lbl_8034E978.menu = 0x5B;
    lbl_8034E978.prevTrack = lbl_8034E978.track;
    lbl_8034E978.track = lbl_800FEF70[0x5B].track;
    fn_800B0A5C_insertQueue(fn_2_948B8, 0x3000);
    fn_800B0A5C_insertQueue(fn_2_96AD4, 0x3000);
}

// fn_2_96AD4, size:0x24C
void fn_2_96AD4(void) {
    MenuTask* object = (MenuTask*)lbl_803CC1B8[0];
    s32 i;
    fn_80034E20(object, lbl_2_data_30D04);
    for (i = 0; i < 3; i++) {
        fn_800363D8(object, i + 0xF, 1, 0, i);
        fn_800363D8(object, i + 0xF, 2, 0, i);
        fn_800363D8(object, i + 0x15, 1, 1, i);
        fn_800363D8(object, i + 0x15, 2, 1, i);
        switch (i) {
        case 0:
            fn_800363D8(object, 0x18, 1, 2, 0);
            fn_800363D8(object, 0x19, 1, 2, 1);
            break;
        case 1:
            fn_800363D8(object, 0x1A, 1, 2, 3);
            fn_800363D8(object, 0x1B, 1, 2, 2);
            fn_800363D8(object, 0x1C, 1, 2, 4);
            break;
        case 2:
            fn_800363D8(object, 0x1D, 1, 2, 0);
            fn_800363D8(object, 0x1E, 1, 2, 1);
            break;
        }
    }
    fn_800363D8(object, 4, 1, 3, 0);
    fn_800363D8(object, 3, 1, 4, 0);
    if (lbl_2_bss_1033C.rumble == 0) {
        MENU_SLOT_OBJ(lbl_80371C30, 0x10 + object->baseIdx + i)->_5C = 0;
        (&lbl_80371C30[16])[object->baseIdx].obj->_68 = 0;
        (&lbl_80371C30[19])[object->baseIdx].obj->_64 = 0x1B;
        (&lbl_80371C30[22])[object->baseIdx].obj->_64 = 0x11;
    }
    ((MenuTask*)lbl_803CC1B8[0])->func = fn_2_96698;
}

// fn_2_96698, size:0x43C
void fn_2_96698(void) {
    MenuTask* object = (MenuTask*)lbl_803CC1B8[0];
    switch (lbl_803C66B0.step[0]) {
    case 0x59:
        fn_2_96118(object);
        fn_2_95FE0(object);
        break;
    case 0x5A:
        fn_2_95F3C(object);
        fn_2_95E80(object);
        break;
    case 0x5B:
        if (lbl_2_bss_1033C.editing != 0) {
            fn_2_95654(object);
            fn_2_95604();
        } else {
            fn_2_95B78(object);
            fn_2_95B28();
        }
        break;
    case 0x5C:
        fn_2_94A8C(object);
        fn_2_9493C(object);
        break;
    }
    if (lbl_2_bss_1033C._0E != 0) {
        lbl_2_bss_1033C._0E = 0;
        fn_80034CEC(object);
        REMOVE_QUEUE_NOARG();
    }
}

// fn_2_96118, size:0x580
void fn_2_96118(MenuTask* object) {
    s32 i;
    s32 j;
    if ((lbl_803C66B0.steps[13][1] == 0) ? 1 : 0) {
        i = 0;
        MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx)->_68 = 1;
        do {
            if (i == lbl_2_bss_1033C.cursor) {
                E94(object, 0xF, i)->_5C = 0;
                E94(object, 0xF, i)->_68 = 1;
                E94(object, 0x12, i)->_5C = 0;
                E94(object, 0x12, i)->_68 = 1;
            } else if (lbl_2_bss_1033C.rumble != 0 || i != 1) {
                E94(object, 0xF, i)->_5C = 0;
                E94(object, 0xF, i)->_68 = 0;
                E94(object, 0x12, i)->_5C = 0;
                E94(object, 0x12, i)->_68 = 0;
                E94(object, 6, i)->_5C = 0;
                E94(object, 6, i)->_68 = 1;
            }
            switch (i) {
            case 0:
                D94(object, 24)->_5C = 0;
                D94(object, 25)->_5C = 0;
                if (lbl_2_bss_1033C.rumble != 0) {
                    D94(object, 24)->_64 = 0x18;
                    D94(object, 25)->_64 = 0x15;
                    D94(object, 24)->_68 = 0;
                    D94(object, 25)->_68 = 0;
                } else {
                    D94(object, 24)->_64 = 0x15;
                    D94(object, 25)->_64 = 0x18;
                    D94(object, 24)->_68 = 0;
                    D94(object, 25)->_68 = 0;
                }
                break;
            case 1:
                for (j = 0; j < 3; j++) {
                    E94(object, 0x1A, j)->_5C = 0;
                    if (lbl_2_bss_1033C.rumble != 0) {
                        if (lbl_2_bss_1033C.sound == j) {
                            E94(object, 0x1A, j)->_64 = 0x18;
                            E94(object, 0x1A, j)->_68 = 0;
                        } else {
                            E94(object, 0x1A, j)->_64 = 0x15;
                            E94(object, 0x1A, j)->_68 = 0;
                        }
                    } else {
                        D94(object, 7)->_68 = 1;
                        if (lbl_2_bss_1033C.sound == j) {
                            E94(object, 0x1A, j)->_64 = 0x19;
                        } else {
                            E94(object, 0x1A, j)->_64 = 0x17;
                        }
                        E94(object, 0x1A, j)->_68 = 1;
                    }
                }
                break;
            case 2:
                D94(object, 29)->_5C = 0;
                D94(object, 30)->_5C = 0;
                if (lbl_2_bss_1033C.option2 != 0) {
                    D94(object, 29)->_64 = 0x18;
                    D94(object, 30)->_64 = 0x15;
                    D94(object, 29)->_68 = 0;
                    D94(object, 30)->_68 = 0;
                } else {
                    D94(object, 29)->_64 = 0x15;
                    D94(object, 30)->_64 = 0x18;
                    D94(object, 29)->_68 = 0;
                    D94(object, 30)->_68 = 0;
                }
                break;
            }
            E94(object, 0xC, i)->color = E94(object, 0xC, i)->color & ~0xFFU;
            E94(object, 0x15, i)->_5C = 0;
            E94(object, 0x15, i)->_68 = 0;
            i++;
        } while (i < 3);
        fn_800626EC(0);
        lbl_803C66B0.steps[13][1] = 1;
    }
}

// fn_2_95FE0, size:0x138
void fn_2_95FE0(MenuTask* object) {
    s32 hits;
    s32 total;
    s32 i;
    if ((lbl_803C66B0.steps[13][1] == 1) ? 1 : 0) {
        hits = 0;
        total = 0;
        tally94(object, 0, 0xF, &total, &hits);
        for (i = 0; i < 3; i++) {
            if (i != lbl_2_bss_1033C.cursor) {
                tally94(object, i + 6, 0xF, &total, &hits);
            }
        }
        if (hits == total) {
            changeScene(1, 6);
            MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx + 6)->color = (MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx + 6)->color & ~0xFFU) | 0xFF;
            MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx + 7)->color = (MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx + 7)->color & ~0xFFU) | 0xFF;
            MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx + 8)->color = (MENU_SLOT_OBJ(lbl_80371C30, object->baseIdx + 8)->color & ~0xFFU) | 0xFF;
            fn_80062674(0);
            lbl_803C66B0.steps[13][1] = 2;
        }
    }
}

// fn_2_95F3C, size:0xA4
void fn_2_95F3C(MenuTask* object) {
    if ((lbl_803C66B0.steps[13][1] == 0) ? 1 : 0) {
        lbl_80371C30[object->baseIdx].obj->_68 = 4;
        lbl_80371C30[object->baseIdx + 1].obj->_68 = 4;
        lbl_80371C30[object->baseIdx + 3].obj->_68 = 4;
        lbl_80371C30[object->baseIdx + 4].obj->_68 = 4;
        fn_800626EC(0);
        lbl_803C66B0.steps[13][1] = 1;
    }
}

// fn_2_95E80, size:0xBC
void fn_2_95E80(MenuTask* object) {
    u8 flag;
    if ((lbl_803C66B0.steps[13][1] == 1) ? 1 : 0) {
        flag = fn_80042DA8(object, 0, 0) != 0;
        if ((lbl_80371C30[object->baseIdx].obj->_5C >> 16) == 3) {
            changeScene(3, 6);
        }
        if ((s32)flag == 1) {
            lbl_2_bss_1033C._0E = 1;
            fn_80062674(0);
            lbl_803C66B0.steps[13][1] = 2;
        }
    }
}

// fn_2_95B78, size:0x2C4
void fn_2_95B78(MenuTask* object) {
    s32 i;
    if ((lbl_803C66B0.steps[13][1] == 0) ? 1 : 0) {
        for (i = 0; i < 3; i++) {
            if (i == lbl_2_bss_1033C.cursor) {
                ENT94(object, 0xF, i)->_5C = 0;
                ENT94(object, 0xF, i)->_68 = 1;
                ENT94(object, 0x12, i)->_5C = 0;
                ENT94(object, 0x12, i)->_68 = 1;
                ENT94(object, 6, i)->_68 = 4;
            } else if (i == lbl_2_bss_1033C.prevCursor) {
                ENT94(object, 0xF, i)->_5C = 0xA0000;
                ENT94(object, 0xF, i)->_68 = 4;
                ENT94(object, 0x12, i)->_5C = 0xA0000;
                ENT94(object, 0x12, i)->_68 = 4;
                ENT94(object, 6, i)->_68 = 1;
            } else if (lbl_2_bss_1033C.rumble != 0 || i != 1) {
                ENT94(object, 0xF, i)->_5C = 0;
                ENT94(object, 0xF, i)->_68 = 0;
                ENT94(object, 0x12, i)->_5C = 0;
                ENT94(object, 0x12, i)->_68 = 0;
                ENT94(object, 6, i)->_5C = 0xF0000;
                ENT94(object, 6, i)->_68 = 0;
            }
        }
        MENU_SLOT_OBJ(&lbl_80371C30[3], object->baseIdx)->_5C = 0;
        fn_800363D8(object, 3, 1, 4, lbl_2_bss_1033C.cursor);
        MENU_SLOT_OBJ(&lbl_80371C30[3], object->baseIdx)->_68 = 1;
        MENU_SLOT_OBJ(&lbl_80371C30[4], object->baseIdx)->_5C = 0;
        fn_800363D8(object, 4, 1, 3, lbl_2_bss_1033C.cursor);
        MENU_SLOT_OBJ(&lbl_80371C30[4], object->baseIdx)->_68 = 1;
        fn_800626EC(0);
        lbl_803C66B0.steps[13][1] = 1;
    }
}

// fn_2_95B28, size:0x50
void fn_2_95B28(void) {
    if ((lbl_803C66B0.steps[13][1] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0.steps[13][1] = 2;
    }
}

// fn_2_95654, size:0x4D4
void fn_2_95654(MenuTask* object) {
    s32 i;
    if ((lbl_803C66B0.steps[13][1] == 0) ? 1 : 0) {
        switch (lbl_2_bss_1033C.cursor) {
        case 0:
            R94(object, 24)->_64 = 0x15;
            R94(object, 25)->_64 = 0x15;
            if (lbl_2_bss_1033C.rumble != 0) {
                R94(object, 24)->_5C = 0;
                R94(object, 25)->_5C = 0xF0000;
                R94(object, 24)->_68 = 1;
                R94(object, 25)->_68 = 4;
                D94(object, 31)->color = (D94(object, 31)->color & ~0xFFU) | 0xFF;
                D94(object, 32)->color = D94(object, 32)->color & ~0xFFU;
            } else {
                R94(object, 24)->_5C = 0xF0000;
                R94(object, 25)->_5C = 0;
                R94(object, 24)->_68 = 4;
                R94(object, 25)->_68 = 1;
                D94(object, 31)->color = D94(object, 31)->color & ~0xFFU;
                D94(object, 32)->color = (D94(object, 32)->color & ~0xFFU) | 0xFF;
            }
            break;
        case 1:
            D94(object, 26)->_64 = 0x15;
            D94(object, 27)->_64 = 0x15;
            D94(object, 28)->_64 = 0x15;
            for (i = 0; i < 3; i++) {
                if (lbl_2_bss_1033C.rumble != 0) {
                    if (lbl_2_bss_1033C.sound == i) {
                        MENU_SLOT_OBJ(lbl_80371C30, 0x1A + object->baseIdx + i)->_5C = 0;
                        MENU_SLOT_OBJ(lbl_80371C30, 0x1A + object->baseIdx + i)->_68 = 1;
                        MENU_SLOT_OBJ(lbl_80371C30, 0x21 + object->baseIdx + i)->color = (MENU_SLOT_OBJ(lbl_80371C30, 0x21 + object->baseIdx + i)->color & ~0xFFU) | 0xFF;
                    } else {
                        if (lbl_2_bss_1033C.prevSound == i) {
                            MENU_SLOT_OBJ(lbl_80371C30, 0x1A + object->baseIdx + i)->_5C = 0xF0000;
                            MENU_SLOT_OBJ(lbl_80371C30, 0x1A + object->baseIdx + i)->_68 = 4;
                        } else {
                            MENU_SLOT_OBJ(lbl_80371C30, 0x1A + object->baseIdx + i)->_5C = 0;
                            MENU_SLOT_OBJ(lbl_80371C30, 0x1A + object->baseIdx + i)->_68 = 0;
                        }
                        MENU_SLOT_OBJ(lbl_80371C30, 0x21 + object->baseIdx + i)->color = MENU_SLOT_OBJ(lbl_80371C30, 0x21 + object->baseIdx + i)->color & ~0xFFU;
                    }
                }
            }
            break;
        case 2:
            R94(object, 29)->_64 = 0x15;
            R94(object, 30)->_64 = 0x15;
            if (lbl_2_bss_1033C.option2 != 0) {
                R94(object, 29)->_5C = 0;
                R94(object, 30)->_5C = 0xF0000;
                R94(object, 29)->_68 = 1;
                R94(object, 30)->_68 = 4;
                D94(object, 36)->color = (D94(object, 36)->color & ~0xFFU) | 0xFF;
                D94(object, 37)->color = D94(object, 37)->color & ~0xFFU;
            } else {
                R94(object, 29)->_5C = 0xF0000;
                R94(object, 30)->_5C = 0;
                R94(object, 29)->_68 = 4;
                R94(object, 30)->_68 = 1;
                D94(object, 36)->color = D94(object, 36)->color & ~0xFFU;
                D94(object, 37)->color = (D94(object, 37)->color & ~0xFFU) | 0xFF;
            }
            break;
        }
        fn_800626EC(0);
        lbl_803C66B0.steps[13][1] = 1;
    }
}

// fn_2_95604, size:0x50
void fn_2_95604(void) {
    if ((lbl_803C66B0.steps[13][1] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0.steps[13][1] = 2;
    }
}

// fn_2_94A8C, size:0xB78
void fn_2_94A8C(MenuTask* object) {
    s32 i;
    if ((lbl_803C66B0.steps[13][1] == 0) ? 1 : 0) {
        if (lbl_2_bss_1033C.editing != 0) {
            switch (S94) {
            case 0:
                R94(object, 24)->_5C = 0;
                R94(object, 25)->_5C = 0;
                if (lbl_2_bss_1033C.rumble != 0) {
                    R94(object, 24)->_64 = 0x18;
                    R94(object, 25)->_64 = 0x15;
                    R94(object, 24)->_68 = 1;
                    R94(object, 25)->_68 = 0;
                    F58_SET(D94(object, 31));
                } else {
                    R94(object, 24)->_64 = 0x15;
                    R94(object, 25)->_64 = 0x18;
                    R94(object, 24)->_68 = 0;
                    R94(object, 25)->_68 = 1;
                    F58_SET(D94(object, 32));
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    E94(object, 0x1A, i)->_5C = 0;
                    if (lbl_2_bss_1033C.sound == i) {
                        E94(object, 0x1A, i)->_64 = 0x18;
                        E94(object, 0x1A, i)->_68 = 1;
                        F58_SET(E94(object, 0x21, i));
                    } else {
                        E94(object, 0x1A, i)->_64 = 0x15;
                        E94(object, 0x1A, i)->_68 = 0;
                    }
                }
                break;
            case 2:
                R94(object, 29)->_5C = 0;
                R94(object, 30)->_5C = 0;
                if (lbl_2_bss_1033C.option2 != 0) {
                    R94(object, 29)->_64 = 0x18;
                    R94(object, 30)->_64 = 0x15;
                    R94(object, 29)->_68 = 1;
                    R94(object, 30)->_68 = 0;
                    F58_SET(D94(object, 36));
                } else {
                    R94(object, 29)->_64 = 0x15;
                    R94(object, 30)->_64 = 0x18;
                    R94(object, 29)->_68 = 0;
                    R94(object, 30)->_68 = 1;
                    F58_SET(D94(object, 37));
                }
                break;
            }
            E94(object, 0x12, S94)->_5C = 0xA0000;
            E94(object, 0x12, S94)->_68 = 4;
            E94(object, 0xF, S94)->_5C = 0xA0000;
            E94(object, 0xF, S94)->_68 = 4;
            F58_SET(E94(object, 0xC, S94));
            E94(object, 0x15, S94)->_5C = 0;
            E94(object, 0x15, S94)->_68 = 1;
        } else {
            switch (S94) {
            case 0:
                i = 0;
                R94(object, 24)->_5C = 0;
                R94(object, 25)->_5C = 0;
                if (lbl_2_bss_1033C.rumble != 0) {
                    R94(object, 7)->_5C = 0xF0000;
                    R94(object, 7)->_68 = 0;
                    R94(object, 24)->_64 = 0x18;
                    R94(object, 25)->_64 = 0x15;
                    R94(object, 24)->_68 = 0;
                    R94(object, 25)->_68 = 0;
                    F58_CLR(D94(object, 31));
                    F58_CLR(D94(object, 32));
                    for (; i < 3; i++) {
                        E94(object, 0x1A, i)->_5C = 0;
                        if (lbl_2_bss_1033C.sound == i) {
                            E94(object, 0x1A, i)->_64 = 0x19;
                        } else {
                            E94(object, 0x1A, i)->_64 = 0x17;
                        }
                        E94(object, 0x1A, i)->_68 = 4;
                    }
                    R94(object, 22)->_64 = 0x11;
                    R94(object, 22)->_68 = 4;
                    R94(object, 19)->_64 = 0x1B;
                    R94(object, 19)->_68 = 4;
                } else {
                    D94(object, 7)->_68 = 1;
                    R94(object, 24)->_64 = 0x15;
                    R94(object, 25)->_64 = 0x18;
                    R94(object, 24)->_68 = 0;
                    R94(object, 25)->_68 = 0;
                    F58_CLR(D94(object, 31));
                    F58_CLR(D94(object, 32));
                    for (; i < 3; i++) {
                        if (lbl_2_bss_1033C.sound == i) {
                            E94(object, 0x1A, i)->_64 = 0x19;
                        } else {
                            E94(object, 0x1A, i)->_64 = 0x17;
                        }
                        E94(object, 0x1A, i)->_68 = 1;
                    }
                    R94(object, 22)->_64 = 0x11;
                    R94(object, 22)->_68 = 1;
                    R94(object, 19)->_64 = 0x1B;
                    R94(object, 19)->_68 = 1;
                }
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    E94(object, 0x1A, i)->_5C = 0;
                    if (lbl_2_bss_1033C.sound == i) {
                        E94(object, 0x1A, i)->_64 = 0x18;
                        E94(object, 0x1A, i)->_68 = 0;
                        F58_CLR(D94(object, 33));
                        F58_CLR(D94(object, 34));
                        F58_CLR(D94(object, 35));
                    } else {
                        E94(object, 0x1A, i)->_64 = 0x15;
                        E94(object, 0x1A, i)->_68 = 0;
                    }
                }
                break;
            case 2:
                R94(object, 29)->_5C = 0;
                R94(object, 30)->_5C = 0;
                if (lbl_2_bss_1033C.option2 != 0) {
                    R94(object, 29)->_64 = 0x18;
                    R94(object, 30)->_64 = 0x15;
                    R94(object, 29)->_68 = 0;
                    R94(object, 30)->_68 = 0;
                    F58_CLR(D94(object, 36));
                    F58_CLR(D94(object, 37));
                } else {
                    R94(object, 29)->_64 = 0x15;
                    R94(object, 30)->_64 = 0x18;
                    R94(object, 29)->_68 = 0;
                    R94(object, 30)->_68 = 0;
                    F58_CLR(D94(object, 36));
                    F58_CLR(D94(object, 37));
                }
                break;
            }
            E94(object, 0x12, S94)->_5C = 0;
            E94(object, 0x12, S94)->_68 = 1;
            E94(object, 0xF, S94)->_5C = 0;
            E94(object, 0xF, S94)->_68 = 1;
            F58_CLR(E94(object, 0xC, S94));
            E94(object, 0x15, S94)->_5C = 0xA0000;
            E94(object, 0x15, S94)->_68 = 4;
        }
        fn_800626EC(0);
        lbl_803C66B0.steps[13][1] = 1;
    }
}

// fn_2_9493C, size:0x150
void fn_2_9493C(MenuTask* object) {
    s32 a;
    s32 b;
    if ((lbl_803C66B0.steps[13][1] == 1) ? 1 : 0) {
        a = 0;
        b = 0;
        if (lbl_2_bss_1033C.rumble != 0 && lbl_2_bss_1033C.cursor == 0 && lbl_2_bss_1033C.editing == 0) {
            tally94(object, 0x13, 0, &b, &a);
        }
        if (a == b) {
            if (lbl_2_bss_1033C.rumble != 0 && lbl_2_bss_1033C.cursor == 0 && lbl_2_bss_1033C.editing == 0) {
                MENU_SLOT_OBJ(&lbl_80371C30[19], object->baseIdx)->_5C = 0;
                MENU_SLOT_OBJ(&lbl_80371C30[22], object->baseIdx)->_5C = 0;
                MENU_SLOT_OBJ(&lbl_80371C30[19], object->baseIdx)->_64 = 0x1A;
                MENU_SLOT_OBJ(&lbl_80371C30[22], object->baseIdx)->_64 = 0x10;
            }
            fn_80062674(0);
            lbl_803C66B0.steps[13][1] = 2;
        }
    }
}

// fn_2_948B8, size:0x84
void fn_2_948B8(void) {
    MenuTask* object = (MenuTask*)lbl_803CC1B8[0];
    lbl_2_bss_1033C._0F = 0;
    fn_80034E20(object, lbl_2_data_311E4);
    lbl_80371C30[object->baseIdx].obj->_5C = 0x280000;
    ((MenuTask*)lbl_803CC1B8[0])->func = fn_2_9486C;
}

// fn_2_9486C, size:0x4C
void fn_2_9486C(void) {
    void* object = lbl_803CC1B8[0];
    if (lbl_2_bss_1033C._0F != 0) {
        lbl_2_bss_1033C._0F = 0;
        fn_80034CEC(object);
        REMOVE_QUEUE_NOARG();
    }
}

// fn_2_94854, size:0x18
void fn_2_94854(s32 value) {
    lbl_2_bss_1A824C[0]->_197849 = value;
}
