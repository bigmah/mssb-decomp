#include "menus/auto_00_0003C03C_text.h"
#include "string.h"
#include "Dolphin/vec.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "menus/menu_work.h"
#include "main/file_8000F150.h"
#include "main/file_80011640.h"
#include "main/menu_globals.h"

extern MenuCtx* lbl_2_bss_1A8248[];
extern MenuData* lbl_2_bss_1A824C[];
extern u8 lbl_803CB8F0[];
extern u8 lbl_2_data_3CC8[];
extern u32 lbl_803CBD0C[];
extern u32* lbl_2_data_13374[];
extern void fn_80031CA4(Vec*, u32*);
static u8 lbl_2_bss_15B8[0x4000]; // current message script (copied from lbl_2_data_12C0C)
// Message scripts, one per lbl_2_data_12C0C entry (u32 command words).
// PORT: fn_2_422FC copies 0x4000 bytes from a script start (reads past its end).
u32 lbl_2_data_124A8[44] = {
    1, 0x42, 1, 0x43, 0x42, 2, 0x44, 0x64, 0x3F, 0x39E, 0x44, 0x14A, 0x40, 0x44, 0x2BC, 0x3F,
    0x39F, 0x43, 0x40, 0x45, 3, 0x50, 0x41, 0x3A0, 3, 0x50, 0x55, 3, 1, 0x41, 0x3A1, 3, 0x50, 0x55,
    3, 1, 0x41, 0x3A2, 3, 0x78, 0x55, 3, 1, 2,
};
u32 lbl_2_data_12558[48] = {
    1, 0x42, 1, 0x43, 0x42, 2, 0x44, 0x64, 0x3F, 0x3A8, 0x44, 0x14A, 0x40, 0x44, 0x2BC, 3, 0x50,
    0x3F, 0x3A9, 3, 0x50, 0x43, 0x40, 0x45, 3, 0x50, 0x41, 0x3AA, 3, 0x3C, 0x55, 3, 1, 0x41, 0x3AB,
    3, 0x3C, 0x55, 3, 1, 0x41, 0x3AC, 3, 0x3C, 0x55, 3, 1, 2,
};
u32 lbl_2_data_12618[4] = {1, 0x1B, 6, 2};
u32 lbl_2_data_12628[4] = {1, 0x1E, 6, 2};
u32 lbl_2_data_12638[2] = {1, 2};
u32 lbl_2_data_12640[18] = {1, 9, 0xA, 0x1C, 6, 0x31, 0x32, 0x56, 0x57, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x4A, 2};
u32 lbl_2_data_12688[18] = {1, 9, 0xA, 0x1C, 6, 0x31, 0x32, 0x60, 0x61, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x4A, 2};
u32 lbl_2_data_126D0[14] = {1, 0x1D, 6, 0x33, 0x34, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x4A, 2};
u32 lbl_2_data_12708[14] = {1, 0x48, 6, 0x35, 0x36, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x4A, 2};
u32 lbl_2_data_12740[17] = {1, 0x1F, 6, 0x13, 0x14, 0x6B, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x15, 0x16, 0x4B, 2};
u32 lbl_2_data_12784[16] = {1, 0x20, 6, 0x13, 0x14, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x15, 0x16, 0x4B, 2};
u32 lbl_2_data_127C4[16] = {1, 0x49, 6, 0x13, 0x14, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x6C, 0x6D, 0x15, 0x16, 0x4B, 2};
u32 lbl_2_data_12804[14] = {1, 0x2B, 0x2C, 0x46, 0x47, 0x21, 0x22, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x4C, 2};
u32 lbl_2_data_1283C[14] = {1, 0x2D, 0x2E, 0x46, 0x47, 0x23, 0x24, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x4C, 2};
u32 lbl_2_data_12874[12] = {1, 0x2F, 0x30, 0x46, 0x47, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x4C, 2};
u32 lbl_2_data_128A4[14] = {1, 0x31, 0x32, 0x46, 0x47, 0x21, 0x22, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x4D, 2};
u32 lbl_2_data_128DC[14] = {1, 0x33, 0x34, 0x46, 0x47, 0x23, 0x24, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x4D, 2};
u32 lbl_2_data_12914[14] = {1, 0x35, 0x36, 0x46, 0x47, 0x23, 0x24, 0x6A, 0x68, 0x69, 0x58, 0x59, 0x4D, 2};
u32 lbl_2_data_1294C[5] = {1, 5, 0x233, 6, 2};
u32 lbl_2_data_12960[5] = {1, 5, 0x240, 6, 2};
u32 lbl_2_data_12974[5] = {1, 5, 0x241, 6, 2};
u32 lbl_2_data_12988[5] = {1, 5, 0x242, 6, 2};
u32 lbl_2_data_1299C[5] = {1, 5, 0x243, 6, 2};
u32 lbl_2_data_129B0[5] = {1, 5, 0x244, 6, 2};
u32 lbl_2_data_129C4[5] = {1, 5, 0x245, 6, 2};
u32 lbl_2_data_129D8[5] = {1, 5, 0x246, 6, 2};
u32 lbl_2_data_129EC[5] = {1, 5, 0x247, 6, 2};
u32 lbl_2_data_12A00[5] = {1, 5, 0x248, 6, 2};
u32 lbl_2_data_12A14[5] = {1, 5, 0x249, 6, 2};
u32 lbl_2_data_12A28[5] = {1, 5, 0x24A, 6, 2};
u32 lbl_2_data_12A3C[5] = {1, 5, 0x24B, 6, 2};
u32 lbl_2_data_12A50[5] = {1, 5, 0x24C, 6, 2};
u32 lbl_2_data_12A64[5] = {1, 5, 0x24D, 6, 2};
u32 lbl_2_data_12A78[5] = {1, 5, 0x24E, 6, 2};
u32 lbl_2_data_12A8C[5] = {1, 5, 0x24F, 6, 2};
u32 lbl_2_data_12AA0[5] = {1, 5, 0x250, 6, 2};
u32 lbl_2_data_12AB4[5] = {1, 5, 0x251, 6, 2};
u32 lbl_2_data_12AC8[5] = {1, 5, 0x252, 6, 2};
u32 lbl_2_data_12ADC[5] = {1, 5, 0x253, 6, 2};
u32 lbl_2_data_12AF0[5] = {1, 5, 0x254, 6, 2};
u32 lbl_2_data_12B04[5] = {1, 5, 0x255, 6, 2};
u32 lbl_2_data_12B18[5] = {1, 5, 0x256, 6, 2};
u32 lbl_2_data_12B2C[5] = {1, 5, 0x257, 6, 2};
u32 lbl_2_data_12B40[5] = {1, 5, 0x258, 6, 2};
u32 lbl_2_data_12B54[5] = {1, 5, 0x25D, 6, 2};
u32 lbl_2_data_12B68[5] = {1, 5, 0x25F, 6, 2};
u32 lbl_2_data_12B7C[5] = {1, 5, 0x260, 6, 2};
u32 lbl_2_data_12B90[4] = {1, 0x29, 0x2A, 2};
u32 lbl_2_data_12BA0[5] = {1, 5, 0x261, 6, 2};
u32 lbl_2_data_12BB4[4] = {1, 0x5E, 0x5F, 2};
u32 lbl_2_data_12BC4[2] = {1, 2};
u32 lbl_2_data_12BCC[4] = {1, 0x54, 6, 2};
u32 lbl_2_data_12BDC[4] = {1, 0x62, 0x63, 2};
u32 lbl_2_data_12BEC[4] = {1, 0x64, 0x65, 2};
u32 lbl_2_data_12BFC[4] = {1, 0x66, 0x67, 2};
u32* lbl_2_data_12C0C[55] = {
    lbl_2_data_124A8, lbl_2_data_12558, lbl_2_data_12618, lbl_2_data_12628, lbl_2_data_12638, lbl_2_data_12640,
    lbl_2_data_12688, lbl_2_data_126D0, lbl_2_data_12708, lbl_2_data_12740, lbl_2_data_12784, lbl_2_data_127C4,
    lbl_2_data_12804, lbl_2_data_1283C, lbl_2_data_12874, lbl_2_data_128A4, lbl_2_data_128DC, lbl_2_data_12914,
    lbl_2_data_1294C, lbl_2_data_12960, lbl_2_data_12974, lbl_2_data_12988, lbl_2_data_1299C, lbl_2_data_129B0,
    lbl_2_data_129C4, lbl_2_data_129D8, lbl_2_data_129EC, lbl_2_data_12A00, lbl_2_data_12A14, lbl_2_data_12A28,
    lbl_2_data_12A3C, lbl_2_data_12A50, lbl_2_data_12A64, lbl_2_data_12A78, lbl_2_data_12A8C, lbl_2_data_12AA0,
    lbl_2_data_12AB4, lbl_2_data_12AC8, lbl_2_data_12ADC, lbl_2_data_12AF0, lbl_2_data_12B04, lbl_2_data_12B18,
    lbl_2_data_12B2C, lbl_2_data_12B40, lbl_2_data_12B54, lbl_2_data_12B68, lbl_2_data_12B7C, lbl_2_data_12B90,
    lbl_2_data_12BA0, lbl_2_data_12BB4, lbl_2_data_12BC4, lbl_2_data_12BCC, lbl_2_data_12BDC, lbl_2_data_12BEC,
    lbl_2_data_12BFC,
};

extern void* lbl_2_data_12CE8[];
extern MenuScreenTask* lbl_803CC1B8;
extern u8 lbl_803C6CF8[];
extern u8 lbl_2_data_12298[];
extern void fn_2_94854(u8);
extern void fn_2_9461C(s32);
extern void fn_2_94604(u8);
extern void fn_2_94634(u8);
extern MenuData* lbl_2_bss_1A8234[];
extern MenuDrawArea* lbl_2_bss_1A8230[];
extern void fn_2_20218(void);
extern void fn_2_1BF50(void);
extern MenuProgress* lbl_2_bss_1A8244[];
extern MenuFlags* lbl_2_bss_1A823C[];
extern BOOL fn_8006C79C(s32 idx);
extern BOOL fn_8006C5CC(void);
extern BOOL fn_80068514(u32 frames, u8 target);
extern BOOL fn_8006862C(u32 frames, u8 target);
extern void fn_2_1C41C(void);
extern void fn_2_1C490(void);
extern void fn_2_8F758(s32 index, u8 value);
typedef struct {
    u8 b[0x1C];
} Rec1C;
extern Rec1C lbl_80109420[];
extern u8 lbl_801094E4[];
extern s32 fn_8006CDC0(s32);
extern u8 lbl_800E8558[];
extern u8 lbl_80109AE8[];
extern u8 lbl_8010A768[];
extern s32 fn_2_40CB8(void);
extern void fn_2_90428(s32);
extern void fn_2_92654(s32, u8);
extern u8 lbl_2_data_3198[];
extern void fn_2_1BFD0(void);
extern void fn_2_72054(s32, s8);
extern void fn_2_44504(void);
extern void fn_2_45354(void);
extern void fn_2_450E4(void);
extern void fn_2_42490(void);
extern int sndFXStartEx(int, int, int, int);
extern u8 lbl_800EFBA4[];
extern void fn_8006877C(s32);
extern s16 lbl_2_data_1056C[4][6]; // rep_0788.c
extern u8 lbl_2_data_3CE8[];
extern u8 lbl_2_data_3C40[];
extern s32 fn_2_8CC88(s32);

typedef MenuSortEntry SortEnt;

// fn_2_42474, size:0x1C
void fn_2_42474(void) {
    MenuData* menu = lbl_2_bss_1A824C[0];
    menu->_1976E4 = 0x78;
}

// fn_2_44F14, size:0x20
s32 fn_2_44F14(s32 index) {
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    MenuRosterEntry* entry = &menu->chars[index];
    return entry->_05;
}

// fn_2_44F34, size:0x30
s32 fn_2_44F34(s32 index) {
    return ((MenuRosterEntry*)((u8*)lbl_2_bss_1A8248[0] + index * sizeof(MenuRosterEntry)))->_05 <= 3;
}

// fn_2_46418, size:0x274
void fn_2_46418(void) {
    s32 i;
    memcpy(lbl_2_bss_1A8248[0]->chars, lbl_2_bss_1A8248[0]->charsBackup, sizeof(lbl_2_bss_1A8248[0]->chars));
    for (i = 0; i < 54; i++) {
        lbl_2_bss_1A8248[0]->chars[i]._07 = 0;
        lbl_2_bss_1A8248[0]->chars[i].value = 0;
        lbl_2_bss_1A8248[0]->chars[i]._08 = 0;
        lbl_2_bss_1A8248[0]->chars[i]._31 = 0;
    }
    lbl_2_bss_1A8248[0]->_442A = lbl_2_bss_1A8248[0]->_15F0;
}

// fn_2_4668C, size:0x20
void fn_2_4668C(s32 index) {
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    MenuRosterEntry* entry = &menu->chars[index];
    entry->_31 = 1;
}

// fn_2_45938, size:0x40
s32 fn_2_45938(s32 index) {
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    return (s8)((MenuRosterEntry*)((u8*)menu + lbl_803CB8F0[menu->slots[index]._5] * sizeof(MenuRosterEntry)))->_31 == 0;
}

// fn_2_460EC, size:0x4
void fn_2_460EC(u8 unused) {
    return;
}

// fn_2_460F0, size:0x4
void fn_2_460F0(void) {
    return;
}

// fn_2_460F4, size:0x4
void fn_2_460F4(void) {
    return;
}

// fn_2_46C24, size:0x8
s32 fn_2_46C24(void) {
    return 0;
}

// fn_2_46C2C, size:0x5C
void fn_2_46C2C(s32 unused, Vec* src) {
    Vec position;
    position.x = src->x;
    position.y = src->y;
    position.z = src->z;
    *lbl_2_data_13374[0] = lbl_803CBD0C[0];
    fn_80031CA4(&position, lbl_2_data_13374[0]);
}

// fn_2_422FC, size:0x8C
void fn_2_422FC(s32 index) {
    lbl_2_bss_1A824C[0]->_197694 = 0;
    lbl_2_bss_1A824C[0]->_19768C = 0;
    lbl_2_bss_1A824C[0]->_197690 = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12C0C[index], 0x4000);
    lbl_2_bss_1A824C[0]->scriptPc = (u32*)lbl_2_bss_15B8;
}

// fn_2_42270, size:0x8C
void fn_2_42270(s32 index) {
    lbl_2_bss_1A824C[0]->_197694 = 0;
    lbl_2_bss_1A824C[0]->_19768C = 0;
    lbl_2_bss_1A824C[0]->_197690 = 0;
    memcpy(lbl_2_bss_15B8, lbl_2_data_12CE8[index], 0x4000);
    lbl_2_bss_1A824C[0]->scriptPc = (u32*)lbl_2_bss_15B8;
}

// fn_2_44238, size:0xB0
s32 fn_2_44238(s32 value) {
    s32 count = 0;
    s32 i;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        if (menu->order[i].charId == value) count++;
    }
    return count != 0;
}

// fn_2_44184, size:0xB4
void fn_2_44184(void) {
    s32 count = 0;
    s32 i;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        if (menu->order[i].charId == 12) count++;
    }
    if (count == 0) {
        menu->_44F7 = 1;
    }
}

// fn_2_442E8, size:0x80
s32 fn_2_442E8(void) {
    s32 i;
    s32 count = 0;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        s32 a = menu->order[i].charId;
        if (a == 0 || a == 1) count++;
    }
    return count == 2;
}

// fn_2_44368, size:0xAC
s32 fn_2_44368(void) {
    s32 i;
    s32 count = 0;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 9; i++) {
        s32 a = menu->order[i].charId;
        if (a == 13 || a == 29 || a == 30 || a == 31 || a == 32) count++;
    }
    return count >= 5;
}

// fn_2_42638, size:0xD0
void fn_2_42638(void) {
    s32 i;
    u8* d;
    u8* s;
    for (i = 0; i < 20; i++) {
        d = lbl_2_bss_1A824C[0]->_1978C7;
        s = lbl_2_bss_1A8248[0]->_43C2;
        d[i] = s[i];
    }
}

// fn_2_467FC, size:0xE0
void fn_2_467FC(void) {
    MenuRosterEntry* entry;
    s32 i;
    for (i = 0; i < 54; i++) {
        entry = &lbl_2_bss_1A8248[0]->chars[i];
        if (entry->_04 == (s32)lbl_2_bss_1A8248[0]->_441C && entry->_05 <= 3) {
            entry->_31 = 1;
        } else {
            entry->_31 = 0;
        }
    }
}

// fn_2_45978, size:0x10C
void fn_2_45978(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        MenuRosterEntry* entry = &lbl_2_bss_1A8248[0]->chars[i];
        entry->_07 = (u8)entry->value;
        for (j = 0; j < 10; j++) {
            entry->savedMissions[j].state = entry->missions[j].state;
            entry->savedMissions[j].shown = entry->missions[j].shown;
        }
        lbl_2_bss_1A8248[0]->_444D[i] = 0;
        lbl_2_bss_1A8248[0]->_4483[i] = 0;
        lbl_2_bss_1A8248[0]->_44B9[i] = 0;
    }
}

// fn_2_409CC, size:0xD0
void fn_2_409CC(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        lbl_80366B18.tables[4] = ARAMTransfer(lbl_2_data_12298, 0, 1, 0);
        o->step = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(lbl_80366B18.tables[4]);
            o->step = 2;
        }
        break;
    case 2:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_3C03C, size:0x12C
void fn_2_3C03C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            fn_2_94854(0xB);
            fn_2_9461C(0);
            fn_2_94604(1);
            fn_2_94634(1);
            o->counter = 0x14;
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3E7EC, size:0x12C
void fn_2_3E7EC(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 0xA);
            fn_2_72054(lbl_2_bss_1A8248[0]->_441E, 9);
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3E918, size:0x12C
void fn_2_3E918(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 0xB);
            fn_2_72054(lbl_2_bss_1A8248[0]->_441E, 0xB);
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3EBA8, size:0x118
void fn_2_3EBA8(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 0xA);
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3ECC0, size:0x118
void fn_2_3ECC0(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 0xA);
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3EDD8, size:0x118
void fn_2_3EDD8(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 9);
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3EEF0, size:0x114
void fn_2_3EEF0(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 0xB);
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3F188, size:0x114
void fn_2_3F188(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x3C;
            fn_2_72054(0, 9);
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3F44C, size:0x110
void fn_2_3F44C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 0x28;
        if (lbl_2_bss_1A8248[0]->_4418 != 0) {
            fn_80062890(8);
            o->step = 1;
        } else {
            o->step = 2;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3F55C, size:0x110
void fn_2_3F55C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 0x28;
        if (lbl_2_bss_1A8248[0]->_4418 < 5) {
            fn_80062890(7);
            o->step = 1;
        } else {
            o->step = 2;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_4078C, size:0x130
void fn_2_4078C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* p;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_19783E = 0;
        o->step = 1;
        break;
    case 1:
        p = (MenuPad*)&lbl_803C77B8;
        p += lbl_2_bss_1A824C[0]->port;
        if (p->down & 0x100) {
            o->step = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A824C[0]->_19783E = 1;
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_408BC, size:0x110
void fn_2_408BC(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        o->counter = 0x3C;
        lbl_2_bss_1A824C[0]->_19782C = 1;
        fn_2_72054(1, 0xD);
        fn_80062890(9);
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_40A9C, size:0xF4
void fn_2_40A9C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_1978F3 = 0;
        o->step = 1;
        break;
    case 1:
        lbl_8036E548._307A = 0;
        fn_2_20218();
        lbl_2_bss_1A8234[0]->done = 1;
        lbl_2_bss_1A8230[0]->_32A86 = 1;
        o->step = 2;
        break;
    case 2:
        fn_2_1BF50();
        o->step = 3;
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_40B90, size:0x128
void fn_2_40B90(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_1978F3 = 0;
        o->step = 1;
        break;
    case 1:
        lbl_8036E548._307A = 0;
        fn_2_20218();
        lbl_2_bss_1A8234[0]->done = 1;
        lbl_2_bss_1A8230[0]->_32A86 = 1;
        o->step = 2;
        break;
    case 2:
        o->step = 3;
        break;
    case 3:
        fn_2_1BFD0();
        o->step = 4;
        break;
    case 4:
        lbl_8034E978._26 = 1;
        o->step = 5;
        break;
    case 5:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
}

// fn_2_3DF28, size:0x130
void fn_2_3DF28(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* p;
    switch ((s8)o->step) {
    case 0:
        o->counter = 0x14;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        p = (MenuPad*)&lbl_803C77B8;
        p += lbl_2_bss_1A824C[0]->port;
        if (p->down & 0x300) {
            o->counter = 0x32;
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3C168, size:0x284
void fn_2_3C168(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    s16 v;
    s32 i;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            v = *(s16*)(lbl_2_data_3CE8 + lbl_2_bss_1A8248[0]->_441C * 0xC + lbl_2_bss_1A8248[0]->_4422 * 2 + 2);
            ((s8**)lbl_2_bss_1A824C)[0][0x197851] = -1;
            if (*(s16*)(lbl_2_data_3CE8 + lbl_2_bss_1A8248[0]->_441C * 0xC + lbl_2_bss_1A8248[0]->_4422 * 2) != 5) {
                for (i = 0; i < 51; i++) {
                    if (v == lbl_2_bss_1A8248[0]->slots[i]._2 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1) {
                        ((s8**)lbl_2_bss_1A824C)[0][0x197851] = v;
                    }
                }
            }
            if (lbl_2_bss_1A824C[0]->_197851 != -1) {
                fn_2_94854(0xB);
                fn_2_9461C(lbl_2_bss_1A824C[0]->_197851 + 7);
                fn_2_94604(1);
                fn_2_94634(1);
                o->counter = 0x3C;
                o->step = 2;
            } else {
                o->step = 3;
            }
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3C3EC, size:0x150
void fn_2_3C3EC(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    u8* t;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            t = (u8*)lbl_2_bss_1A8248[0] + lbl_2_bss_1A8248[0]->_4420;
            if (t[offsetof(MenuCtx, _4431)] == 0) {
                t[offsetof(MenuCtx, _4431)] = 1;
                o->counter = 0x3C;
                fn_2_72054(lbl_2_bss_1A8248[0]->_441E, 0xF);
                o->step = 2;
            } else {
                o->step = 3;
            }
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3C53C, size:0x294
void fn_2_3C53C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* e;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_1978F0 = 0;
        fn_2_42490();
        if ((s8)lbl_2_bss_1A824C[0]->_1978EF > 0) {
            o->counter = 1;
            o->step = 1;
        } else {
            o->step = 7;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A8234[0]->layerFlags[1][60] = 1;
        fn_80062890(0x38);
        o->counter = 10;
        o->step = 3;
        break;
    case 3:
        if ((o->counter)-- == 0) {
            o->step = 4;
        }
        break;
    case 4:
        e = (MenuPad*)&lbl_803C77B8;
        e += lbl_2_bss_1A824C[0]->port;
        if (e->down & 0x100) {
            lbl_2_bss_1A8234[0]->layerFlags[8][60] = 1;
            o->counter = 10;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            o->step = 5;
        } else if (e->down & 0x200) {
            lbl_2_bss_1A8234[0]->layerFlags[8][60] = 1;
            o->counter = 10;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            o->step = 5;
        }
        break;
    case 5:
        if ((o->counter)-- == 0) {
            lbl_2_bss_1A824C[0]->_1978F0++;
            if (lbl_2_bss_1A824C[0]->_1978F0 == (s8)lbl_2_bss_1A824C[0]->_1978EF) {
                o->step = 7;
            } else {
                o->step = 2;
            }
        }
        break;
    case 7:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3D5C4, size:0x2A8
void fn_2_3D5C4(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* e;
    switch ((s8)o->step) {
    case 0:
        ((void (*)(void))fn_2_45354)();
        lbl_2_bss_1A824C[0]->_197867 = 0;
        o->counter = 1;
        if (lbl_2_bss_1A824C[0]->_197866 == 0) {
            o->step = 6;
        } else {
            o->step = 1;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        if ((s8)lbl_2_bss_1A8248[0]->_44F4 != 0) {
            lbl_2_bss_1A8234[0]->layerFlags[1][4] = 1;
        } else {
            lbl_2_bss_1A8234[0]->layerFlags[1][42] = 1;
        }
        o->counter = 0xC;
        fn_80062890(0x38);
        o->step = 3;
        break;
    case 3:
        if ((o->counter)-- == 0) {
            o->step = 4;
        }
        break;
    case 4:
        e = (MenuPad*)&lbl_803C77B8;
        e += lbl_2_bss_1A824C[0]->port;
        if (e->down & 0x300) {
            if ((s8)lbl_2_bss_1A8248[0]->_44F4 != 0) {
                lbl_2_bss_1A8234[0]->layerFlags[8][4] = 1;
            } else {
                lbl_2_bss_1A8234[0]->layerFlags[8][42] = 1;
            }
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
            o->counter = 0xC;
            o->step = 5;
        }
        break;
    case 5:
        lbl_2_bss_1A824C[0]->_197867++;
        if (lbl_2_bss_1A824C[0]->_197866 <= lbl_2_bss_1A824C[0]->_197867) {
            o->step = 6;
        } else {
            o->step = 2;
        }
        break;
    case 6:
        ((void (*)(void))fn_2_450E4)();
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3D878, size:0x24C
void fn_2_3D878(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        fn_2_44504();
        lbl_2_bss_1A8234[0]->layerFlags[1][6] = 1;
        o->counter = 0x12C;
        o->step = 1;
        break;
    case 1:
        if (o->counter == 0x118) {
            fn_80062890(0x44);
        }
        if ((o->counter)-- == 0) {
            o->counter = 0x64;
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            lbl_2_bss_1A8234[0]->layerFlags[6][6] = 1;
            lbl_2_bss_1A8230[0]->_32A04[1][1] = 1;
            o->counter = lbl_2_data_1056C[lbl_2_bss_1A8248[0]->_4415][lbl_2_bss_1A8248[0]->_441C];
            o->step = 3;
        }
        break;
    case 3:
        if (o->counter == 0x32) {
            fn_80062890(((s32*)lbl_2_data_3C40)[lbl_2_bss_1A8248[0]->_441C]);
        }
        if (o->counter == 0x32) {
            fn_8006877C(0xC);
        }
        if ((o->counter)-- == 0) {
            o->counter = 0xB4;
            o->step = 4;
        }
        break;
    case 4:
        if ((o->counter)-- == 0) {
            o->counter = 0x32;
            o->step = 5;
        }
        break;
    case 5:
        if ((o->counter)-- == 0) {
            o->step = 6;
        }
        break;
    case 6:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3DAB8, size:0x1A8
void fn_2_3DAB8(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    u8* gsb = (u8*)&g_d_GameSettings;
    MenuScreenTask* q;
    u8* gs;
    MenuPad* e;
    switch ((s8)o->step) {
    case 0:
        gs = gsb + lbl_2_data_3CC8[lbl_2_bss_1A8248[0]->_441C];
        if (*(gs += 0x1A) == 0) {
            *gs = 1;
            lbl_2_bss_1A8234[0]->layerFlags[1][3] = 1;
            o->counter = 0x10;
            fn_80062890(0x38);
            o->step = 1;
        } else {
            o->step = 3;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        e = (MenuPad*)&lbl_803C77B8;
        e += lbl_2_bss_1A824C[0]->port;
        if (e->down & 0x300) {
            lbl_2_bss_1A8234[0]->layerFlags[8][3] = 1;
            o->counter = 0x10;
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3DC60, size:0x164
void fn_2_3DC60(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* p;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A8234[0]->layerFlags[1][1] = 1;
        o->counter = 0x10;
        fn_80062890(0x38);
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        p = (MenuPad*)&lbl_803C77B8;
        p += lbl_2_bss_1A824C[0]->port;
        if (p->down & 0x300) {
            lbl_2_bss_1A8234[0]->layerFlags[8][1] = 1;
            o->counter = 0x10;
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3DDC4, size:0x164
void fn_2_3DDC4(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuPad* p;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A8234[0]->layerFlags[1][2] = 1;
        o->counter = 0x10;
        fn_80062890(0x38);
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        p = (MenuPad*)&lbl_803C77B8;
        p += lbl_2_bss_1A824C[0]->port;
        if (p->down & 0x300) {
            lbl_2_bss_1A8234[0]->layerFlags[8][2] = 1;
            o->counter = 0x10;
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3EA44, size:0x164
void fn_2_3EA44(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuCtx* m;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x168;
            fn_2_72054(0, 9);
            fn_2_72054(lbl_2_bss_1A8248[0]->_441E, 0xA);
            o->step = 2;
        }
        break;
    case 2:
        if (fn_2_8CC88(0) != 0) {
            o->step = 3;
        }
        break;
    case 3:
        m = lbl_2_bss_1A8248[0];
        if (m->_441C == 5) {
            m->slots[m->entries[0].locationIndex]._3 = 3;
        }
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3F004, size:0x184
void fn_2_3F004(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    MenuCtx* m;
    u8 k;
    switch ((s8)o->step) {
    case 0:
        o->counter = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->counter = 0x50;
            fn_2_72054(0, 0xA);
            o->step = 2;
        }
        break;
    case 2:
        m = lbl_2_bss_1A8248[0];
        k = m->_441C;
        if ((k == 3 && m->_441E == 1 && m->entries[0].locationIndex == 0xB) ||
            (k == 3 && m->_441E == 5 && m->entries[0].locationIndex == 0x2A)) {
            if ((o->counter)-- == 0) {
                o->step = 3;
            }
        } else if (fn_2_8CC88(0) != 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3F29C, size:0x1B0
void fn_2_3F29C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A8234[0]->layerFlags[6][17] = 1;
        o->counter = 0xA;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            lbl_2_bss_1A8248[0]->_4439 = 0;
            fn_2_92654(8, 0);
            fn_2_90428(9);
            fn_2_92654(9, 0xB);
            ((void (*)(s32, Vec*))fn_2_46C2C)(0, (Vec*)(lbl_2_data_3198 + 0xB4));
            lbl_2_bss_1A8248[0]->_441A = 0;
            lbl_2_bss_1A8248[0]->slots[41]._6 = 0;
            fn_80062890(5);
            o->counter = 0x50;
            o->step = 2;
        }
        break;
    case 2:
        if (o->counter == 0x46) {
            ((void (*)(s32, Vec*))fn_2_46C2C)(0, (Vec*)(lbl_2_data_3198 + 0xB4));
        }
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_4041C, size:0x198
// NONMATCHING 95%: only scheduling of the three lis DATA@ha in case 0 differs
#if NONMATCHING
void fn_2_4041C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        if (((s32 (*)(s32))fn_2_45938)(lbl_2_bss_1A8248[0]->entries[0].locationIndex) == 0) {
            o->counter = 0xB4;
            lbl_2_bss_1A8248[0]->slots[lbl_2_bss_1A8248[0]->entries[0].locationIndex]._3 = 2;
            lbl_2_bss_1A824C[0]->_197854 = lbl_2_bss_1A8248[0]->slots[lbl_2_bss_1A8248[0]->entries[0].locationIndex]._5;
            lbl_2_bss_1A8234[0]->layerFlags[6][25] = 1;
            fn_80062890(3);
            o->step = 1;
        } else {
            o->step = 2;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        lbl_2_bss_1A8248[0]->slots[lbl_2_bss_1A8248[0]->entries[0].locationIndex]._3 = 3;
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}
#endif

// fn_2_405B4, size:0x1D8
void fn_2_405B4(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        if (((s32 (*)(s32))fn_2_45938)(lbl_2_bss_1A8248[0]->entries[0].locationIndex) == 0) {
            o->counter = 0xB4;
            lbl_2_bss_1A8248[0]->slots[lbl_2_bss_1A8248[0]->entries[0].locationIndex]._3 = 2;
            lbl_2_bss_1A824C[0]->_197854 = lbl_2_bss_1A8248[0]->slots[lbl_2_bss_1A8248[0]->entries[0].locationIndex]._5;
            fn_2_90428(lbl_2_bss_1A824C[0]->_197854 + 0xA);
            fn_2_90428(lbl_2_bss_1A824C[0]->_197854 + 0x10);
            fn_2_92654(lbl_2_bss_1A824C[0]->_197854 + 0xA, 0xC);
            lbl_2_bss_1A8234[0]->layerFlags[6][25] = 1;
            o->step = 1;
        } else {
            o->step = 2;
        }
        break;
    case 1:
        if (o->counter == 0x96) {
            fn_80062890(0x41);
        }
        if ((o->counter)-- == 0) {
            o->step = 2;
        }
        break;
    case 2:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_42388, size:0xEC
void fn_2_42388(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        lbl_2_bss_1A824C[0]->_1976E4 = 0x78;
        o->step = 1;
        break;
    case 1:
        if (fn_2_40CB8() != 0) {
            o->step = 2;
        }
        break;
    case 2:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_42EB0, size:0x118
void fn_2_42EB0(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    u8* m;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s8)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row;
                    s32 v;
                    s32 t;
                    s32 a;
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    v = *(s16*)(lbl_80109AE8 + row + j * 10);
                    t = *(s16*)(lbl_8010A768 + row + j * 10 + 2);
                    a = *(s16*)(lbl_8010A768 + row + j * 10 + 4);
                    if (t != -1 && (s8)e->missions[j].shown == 0 && t == 0x12 &&
                        lbl_2_bss_1A8248[0]->_4415 >= a && lbl_2_bss_1A8248[0]->_442A == 1) {
                        e->missions[j].shown = 1;
                    }
                    if (v != -1 && e->missions[j].state < 0) {
                        e->missions[j].shown = 1;
                    }
                }
            }
        }
    }
}

// fn_2_432EC, size:0x118
void fn_2_432EC(void) {
    s32 i;
    s32 j;
    s32 row;
    s32 v;
    s16 t;
    s16 a;
    s16 b;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s8)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    v = *(s16*)(lbl_80109AE8 + row + j * 10);
                    t = *(s16*)(lbl_8010A768 + row + j * 10 + 2);
                    a = *(s16*)(lbl_8010A768 + row + j * 10 + 4);
                    b = *(s16*)(lbl_8010A768 + row + j * 10 + 6);
                    if (v != -1 && e->missions[j].state < 0) {
                        e->missions[j].shown = 1;
                    }
                    if (t == 1 && fn_8006CDC0(i) >= a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                        e->missions[j].shown = 1;
                    }
                }
            }
        }
    }
}

// fn_2_44E2C, size:0xE8
s32 fn_2_44E2C(s32 ch) {
    s32 n;
    s32 j;
    u8* mi = lbl_800E8558 + ch * 6;
    u8 row;
    u8* p;
    if (mi[3] == 1) {
        n = 0;
        p = mi + 2;
        row = *p;
        for (j = 0; j < 10; j++) {
            if (*(s16*)(lbl_80109AE8 + row * 0x64 + j * 10) != -1) {
                n++;
            }
        }
        *p = row;
        return n;
    }
    return 0;
}

// fn_2_44414, size:0xF0
void fn_2_44414(void* arr) {
    SortEnt* a = arr;
    SortEnt tmp;
    s32 i;
    s32 j;
    for (i = 1; i < 55; i++) {
        tmp = a[i];
        a[0] = tmp;
        j = i - 1;
        while (tmp.k < a[j].k) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = tmp;
    }
}

// fn_2_45D38, size:0x110
void fn_2_45D38(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        MenuRosterEntry* entry = &lbl_2_bss_1A8248[0]->chars[i];
        entry->value = entry->_07;
    }
}

// fn_2_45FDC, size:0x110
void fn_2_45FDC(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        MenuRosterEntry* entry = &lbl_2_bss_1A8248[0]->chars[i];
        entry->_07 = (u8)entry->value;
    }
}

// fn_2_45BA4, size:0x194
void fn_2_45BA4(void) {
    s32 j;
    s32 i;
    MenuRosterEntry* entry;
    for (i = 0; i < 54; i++) {
        entry = &lbl_2_bss_1A8248[0]->chars[i];
        for (j = 0; j < 10; j++) {
            entry->missions[j].state = entry->savedMissions[j].state;
            entry->missions[j].shown = entry->savedMissions[j].shown;
        }
    }
}

// fn_2_45E48, size:0x194
void fn_2_45E48(void) {
    s32 j;
    s32 i;
    MenuRosterEntry* entry;
    for (i = 0; i < 54; i++) {
        entry = &lbl_2_bss_1A8248[0]->chars[i];
        for (j = 0; j < 10; j++) {
            entry->savedMissions[j].state = entry->missions[j].state;
            entry->savedMissions[j].shown = entry->missions[j].shown;
        }
    }
}

// fn_2_45A84, size:0x120
s32 fn_2_45A84(void) {
    s32 i;
    s32 j;
    s32 flag;
    MenuRosterEntry* entry;
    flag = 0;
    for (i = 0; i < 54; i++) {
        entry = &lbl_2_bss_1A8248[0]->chars[i];
        for (j = 0; j < 10; j++) {
            if (entry->savedMissions[j].state >= 0 && entry->missions[j].state < 0) {
                flag = 1;
                lbl_2_bss_1A8248[0]->_44B9[i] = 1;
            }
        }
    }
    return flag == 1;
}

// fn_2_45354, size:0x194
void fn_2_45354(void) {
    s32 i;
    lbl_2_bss_1A824C[0]->_197866 = 0;
    for (i = 0; i < 54; i++) {
        lbl_2_bss_1A824C[0]->_197868[i] = -1;
    }
    for (i = 0; i < 54; i++) {
        if ((s8)lbl_2_bss_1A8248[0]->_4483[i] == 1) {
            lbl_2_bss_1A824C[0]->_197868[lbl_2_bss_1A824C[0]->_197866] = i;
            lbl_2_bss_1A824C[0]->_197866++;
        }
    }
}

// fn_2_45810, size:0x128
void fn_2_45810(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        lbl_2_bss_1A8248[0]->_43D6[i] = 0;
    }
}

// fn_2_45204, size:0x150
// NONMATCHING 96%: extra mr r30,r0 for the strength-reduced table pointer (see docs/patterns/unsolved.md)
#if NONMATCHING
void fn_2_45204(void) {
    s32 i;
    s32 n;
    s32 cnt;
    s32 j;
    u8* mi;
    u8 row;
    u8* m;
    mi = lbl_800E8558;
    for (i = 0; i < 54; i++, mi += 6) {
        n = fn_8006CDC0(i);
        if (mi[3] == 1) {
            cnt = 0;
            row = mi[2];
            for (j = 0; j < 10; j++) {
                if (*(s16*)(lbl_80109AE8 + row * 0x64 + j * 10) != -1) {
                    cnt++;
                }
            }
            mi[2] = row;
        } else {
            cnt = 0;
        }
        if (n == cnt && cnt != 0) {
            if (lbl_2_bss_1A8248[0]->_43D6[i] == 0) {
                lbl_2_bss_1A8248[0]->_4483[i] = 1;
            }
        }
    }
}
#endif

// fn_2_466AC, size:0x150
void fn_2_466AC(void) {
    s32 i;
    s32 j;
    s32 row;
    s16 v;
    s32 t;
    s16 a;
    s16 b;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        e = &lbl_2_bss_1A8248[0]->chars[i];
        for (j = 0; j < 10; j++) {
            row = lbl_800E8558[i * 6 + 2] * 0x64;
            v = *(s16*)(lbl_80109AE8 + row + j * 10);
            t = *(s16*)(lbl_8010A768 + row + j * 10 + 2);
            a = *(s16*)(lbl_8010A768 + row + j * 10 + 4);
            b = *(s16*)(lbl_8010A768 + row + j * 10 + 6);
            if (t == 0) {
                e->missions[j].shown = 1;
            }
            if (t == 1) {
                if (fn_8006CDC0(i) >= a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                    e->missions[j].shown = 1;
                } else {
                    e->missions[j].shown = 0;
                }
            }
            if (t == 0x13 && lbl_2_bss_1A8248[0]->_441C == a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                e->missions[j].shown = 1;
            }
            if (v != -1 && e->missions[j].state < 0) {
                e->missions[j].shown = 1;
            }
        }
    }
}

// fn_2_42FC8, size:0x12C
void fn_2_42FC8(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s8)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row;
                    s16 v;
                    s16 t;
                    s16 a;
                    s16 b;
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    v = *(s16*)(lbl_80109AE8 + row + j * 10);
                    t = *(s16*)(lbl_8010A768 + row + j * 10 + 2);
                    a = *(s16*)(lbl_8010A768 + row + j * 10 + 4);
                    b = *(s16*)(lbl_8010A768 + row + j * 10 + 6);
                    if (t != -1 && (s8)e->missions[j].shown == 0 && t == 1 &&
                        fn_8006CDC0(i) >= a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                        e->missions[j].shown = 1;
                    }
                    if (v != -1 && e->missions[j].state < 0) {
                        e->missions[j].shown = 1;
                    }
                }
            }
        }
    }
}

// fn_2_46ADC, size:0x148
void fn_2_46ADC(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        e = &lbl_2_bss_1A8248[0]->chars[i];
        e->limits = (s8*)(lbl_801094E4 + i * 0x1C);
        e->_04 = e->limits[0];
        e->_05 = e->limits[1];
        e->_07 = 0;
        e->value = 0;
        e->_08 = 0;
        for (j = 0; j < 10; j++) {
            e->missions[j].state = e->savedMissions[j].state = 0;
            e->missions[j].shown = e->savedMissions[j].shown = 0;
        }
        if (e->_04 == (s32)lbl_2_bss_1A8248[0]->_441C && e->_05 <= 3) {
            e->_31 = 1;
        } else {
            e->_31 = 0;
        }
    }
}

// fn_2_450E4, size:0x120
void fn_2_450E4(void) {
    s32 t;
    s32 k;
    s32 m;
    for (k = 0; k < lbl_2_bss_1A824C[0]->_197866; k++) {
        t = lbl_2_bss_1A824C[0]->_197868[k];
        lbl_2_bss_1A8248[0]->_43D6[t] = 1;
        for (m = 0; m < 54; m++) {
            s32 q = lbl_800E8558[m * 6 + 1];
            if (q == t) {
                lbl_2_bss_1A8248[0]->_43D6[m] = 1;
            }
        }
    }
}

// fn_2_44F64, size:0x180
void fn_2_44F64(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        lbl_2_bss_1A8244[0]->_00[i] |= lbl_2_bss_1A8248[0]->_43D6[i];
    }
}

// fn_2_44014, size:0x170
void fn_2_44014(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s8)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row;
                    s16 t;
                    s16 c;
                    s16 b;
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    t = *(s16*)(lbl_80109AE8 + row + j * 10);
                    c = *(s16*)(lbl_80109AE8 + row + j * 10 + 2);
                    b = *(s16*)(lbl_80109AE8 + row + j * 10 + 6);
                    if (t != -1 && e->missions[j].state == 0 && t == 0x3A &&
                        (s8)lbl_2_bss_1A8248[0]->_43C2[c] == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                        e->missions[j].state = -2;
                    }
                }
            }
        }
    }
}

// fn_2_43E8C, size:0x188
void fn_2_43E8C(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s8)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row;
                    s16 t;
                    s16 b;
                    row = lbl_800E8558[i * 6 + 2] * 0x64;
                    t = *(s16*)(lbl_80109AE8 + row + j * 10);
                    b = *(s16*)(lbl_80109AE8 + row + j * 10 + 6);
                    if (t != -1 && e->missions[j].state == 0 && t == 0x3B &&
                        lbl_2_bss_1A824C[0]->_1978F4 == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                        e->missions[j].state = -2;
                    }
                }
            }
        }
    }
    lbl_2_bss_1A824C[0]->_1978F4 = 0;
}

// fn_2_43404, size:0x188
void fn_2_43404(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s8)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    u8* p = lbl_80109AE8 + lbl_800E8558[i * 6 + 2] * 0x64 + j * 10;
                    s32 t = *(s16*)p;
                    s32 c = *(s16*)(p + 2);
                    s32 b = *(s16*)(p + 6);
                    s32 d = *(s16*)(p + 8);
                    if (t != -1 && e->missions[j].state == 0 && t == 0x46 &&
                        lbl_2_bss_1A8248[0]->_441C == c &&
                        lbl_2_bss_1A8248[0]->_43BC >= d * 0x64 &&
                        lbl_2_bss_1A8248[0]->_4415 >= b) {
                        e->missions[j].state = -2;
                    }
                }
            }
        }
    }
}
void fn_2_468DC(void) {
    s32 i;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        e = &lbl_2_bss_1A8248[0]->chars[i];
        e->limits = (s8*)(lbl_801094E4 + i * 0x1C);
        e->_04 = e->limits[0];
        e->_05 = e->limits[1];
    }
}

extern s16 lbl_2_data_36EC[];

#pragma dont_inline on
// fn_2_42490, size:0x1A8
void fn_2_42490(void) {
    s32 i;
    s32 n;
    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A824C[0]->_1978DB[i] = 0;
    }
    n = 0;
    for (i = 0; i < 20; i++) {
        if ((s8)lbl_2_bss_1A824C[0]->_1978C7[i] == 0 && (s8)lbl_2_bss_1A8248[0]->_43C2[i] == 1 &&
            lbl_2_data_36EC[i] == 1) {
            lbl_2_bss_1A824C[0]->_1978DB[n++] = i;
        }
    }
    lbl_2_bss_1A824C[0]->_1978EF = n;
}
#pragma dont_inline reset

static inline s32 fn_2_countPlayer(MenuCtx* m, s32 id) {
    s32 k;
    s32 cnt = 0;
    for (k = 0; k < 9; k++) {
        if (m->order[k].charId == id) {
            cnt++;
        }
    }
    return cnt;
}

static inline s32 fn_2_hasPlayer(MenuCtx* m, s32 id) {
    s32 k;
    s32 cnt = 0;
    for (k = 0; k < 9; k++) {
        if (m->order[k].charId == id) {
            cnt++;
        }
    }
    return cnt != 0;
}

// fn_2_430F4, size:0x1F8
// NONMATCHING 93%: type/a/b/t should live in r28-r31; ours keeps type in a volatile reg
#if NONMATCHING
void fn_2_430F4(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s32)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row = lbl_800E8558[i * 6 + 2] * 0x64;
                    s32 t = *(s16*)(lbl_80109AE8 + row + j * 10);
                    u8* p = lbl_8010A768 + row + j * 10;
                    s32 type = *(s16*)(p + 2);
                    s32 a = *(s16*)(p + 4);
                    s32 b = *(s16*)(p + 6);
                    if (type != -1 && (s8)e->missions[j].shown == 0) {
                        switch (type) {
                        case 2:
                            if (lbl_2_bss_1A8248[0]->_4415 >= a) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 21:
                            if (fn_2_hasPlayer(lbl_2_bss_1A8248[0], a) == 1 &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        }
                    }
                    if (t != -1 && e->missions[j].state < 0) {
                        e->missions[j].shown = 1;
                    }
                }
            }
        }
    }
}
#endif

// fn_2_42BE8, size:0x2C8
void fn_2_42BE8(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s32)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row = lbl_800E8558[i * 6 + 2] * 0x64;
                    s32 t = *(s16*)(lbl_80109AE8 + row + j * 10);
                    u8* p = lbl_8010A768 + row + j * 10;
                    s32 type = *(s16*)(p + 2);
                    s32 a = *(s16*)(p + 4);
                    s32 b = *(s16*)(p + 6);
                    s32 c = *(s16*)(p + 8);
                    if (type != -1 && (s8)e->missions[j].shown == 0) {
                        switch (type) {
                        case 1:
                            if (fn_8006CDC0(i) >= a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 22:
                            if (fn_8006C79C(a) == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 24:
                            if (lbl_2_bss_1A8248[0]->_4426 != 0 && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 25:
                            if ((lbl_2_bss_1A8248[0]->_4426 & (1 << b)) && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= c) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 26:
                            if (fn_2_hasPlayer(lbl_2_bss_1A8248[0], a) == 1 &&
                                lbl_2_bss_1A8248[0]->_441E == b && lbl_2_bss_1A8248[0]->_4415 >= c) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        }
                    }
                    if (t != -1 && e->missions[j].state < 0) {
                        e->missions[j].shown = 1;
                    }
                }
            }
        }
    }
}

// fn_2_460F8, size:0x320
void fn_2_460F8(void) {
    s32 i;
    for (i = 0; i < 54; i++) {
        lbl_2_bss_1A8248[0]->chars[i]._07 = 0;
        lbl_2_bss_1A8248[0]->chars[i].value = 0;
        lbl_2_bss_1A8248[0]->chars[i]._08 = 0;
        lbl_2_bss_1A8248[0]->chars[i]._31 = 0;
    }
    memcpy(lbl_2_bss_1A8248[0]->charsBackup, lbl_2_bss_1A8248[0]->chars, sizeof(lbl_2_bss_1A8248[0]->chars));
    lbl_2_bss_1A8248[0]->_15F0 = lbl_2_bss_1A8248[0]->_442A;
    for (i = 0; i < 20; i++) {
        if ((s8)lbl_2_bss_1A8248[0]->_15F1[i] == 0) {
            lbl_2_bss_1A8248[0]->_15F1[i] = lbl_2_bss_1A8248[0]->_43C2[i];
        }
    }
}

// fn_2_454E8, size:0x328
// NONMATCHING 99%: addi r0,lbl_800E8558@l; mr (see docs/patterns/unsolved.md) and i/base reg swap
#if NONMATCHING
void fn_2_454E8(void) {
    s32 i;
    s32 n;
    s32 cnt;
    s32 j;
    s32 k;
    u8* mi;
    u8 row;
    u8* base;
    for (i = 0; i < 54; i++) {
        lbl_2_bss_1A8248[0]->_43D6[i] = 0;
    }
    base = lbl_800E8558;
    mi = base;
    for (i = 0; i < 54; i++, mi += 6) {
        n = fn_8006CDC0(i);
        if (mi[3] == 1) {
            cnt = 0;
            row = mi[2];
            for (j = 0; j < 10; j++) {
                if (*(s16*)(lbl_80109AE8 + row * 0x64 + j * 10) != -1) {
                    cnt++;
                }
            }
            mi[2] = row;
        } else {
            cnt = 0;
        }
        if (n == cnt && cnt != 0) {
            lbl_2_bss_1A8248[0]->_43D6[i] = 1;
            for (k = 0; k < 54; k++) {
                if (i == base[k * 6 + 1]) {
                    lbl_2_bss_1A8248[0]->_43D6[k] = 1;
                }
            }
        }
    }
}
#endif

// fn_2_3E058, size:0x334
void fn_2_3E058(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        fn_2_1C490();
        o->counter = 0x1E;
        if (lbl_2_bss_1A8248[0]->_4422 >= 5 && lbl_2_bss_1A8248[0]->_4447 == 0 &&
            lbl_2_bss_1A8248[0]->_441C == 5) {
            lbl_2_bss_1A8248[0]->_4447 = 1;
            o->step = 1;
        } else {
            o->step = 14;
        }
        break;
    case 1:
        if ((u8)fn_8006862C(0x78, 0) == 0) {
            lbl_2_bss_1A8248[0]->_44F2 = 4;
            fn_2_94854(0xB);
            fn_2_9461C(0xC);
            fn_2_94604(1);
            fn_2_94634(1);
            o->counter = 0x3C;
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        lbl_2_bss_1A8234[0]->layerFlags[1][47] = 1;
        o->counter = 0xC8;
        o->step = 4;
        break;
    case 4:
        if ((o->counter)-- == 0) {
            o->step = 5;
        }
        break;
    case 5:
        o->counter = 0xBC;
        o->step = 6;
        break;
    case 6:
        if ((o->counter)-- == 0) {
            o->step = 7;
        }
        break;
    case 7:
        if ((u8)fn_80068514(0x78, 0x7F) == 0) {
            o->step = 12;
        }
        break;
    case 12:
        fn_2_94854(0xB);
        fn_2_9461C(0);
        fn_2_94604(1);
        fn_2_94634(1);
        o->counter = 0x3C;
        o->step = 13;
        break;
    case 13:
        if ((o->counter)-- == 0) {
            lbl_2_bss_1A8248[0]->_44F2 = 0;
            o->step = 14;
        }
        break;
    case 14:
        fn_2_1C41C();
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    (o->arg)++;
    if (o->arg == 0xA6) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3A);
    } else if (o->arg == 0xF6) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3B);
    } else if (o->arg == 0x146) {
    } else if (o->arg == 0x10A) {
    } else if (o->arg == 0x16E) {
    } else if (o->arg == 0x13C) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3C);
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}


static inline u16 fn_2_padHeld(void) {
    MenuPad* e = (MenuPad*)&lbl_803C77B8;
    e += lbl_2_bss_1A824C[0]->port;
    return e->down;
}

// fn_2_3F66C, size:0x3A8
void fn_2_3F66C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        (lbl_2_bss_1A824C[0]->_197740) = 0;
        (lbl_2_bss_1A824C[0]->_197734) = lbl_2_bss_1A8248[0]->_43BC;
        (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_19773C) = lbl_2_bss_1A8248[0]->_43BE;
        (lbl_2_bss_1A824C[0]->_19773A) = 0;
        (lbl_2_bss_1A824C[0]->_197738) = (lbl_2_bss_1A824C[0]->_197734) + ((lbl_2_bss_1A824C[0]->_197736) - (lbl_2_bss_1A824C[0]->_197734)) / 2;
        o->step = 1;
        break;
    case 1:
        (lbl_2_bss_1A824C[0]->_19773A) *= 2;
        if ((lbl_2_bss_1A824C[0]->_19773A) == 0) {
            (lbl_2_bss_1A824C[0]->_19773A)++;
        }
        (lbl_2_bss_1A824C[0]->_197736) -= (lbl_2_bss_1A824C[0]->_19773A);
        (lbl_2_bss_1A824C[0]->_19773A)++;
        lbl_2_bss_1A8234[0]->layerFlags[7][45] = 1;
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x37);
        if ((lbl_2_bss_1A824C[0]->_197736) <= (lbl_2_bss_1A824C[0]->_197734)) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
            o->step = 4;
        } else if ((lbl_2_bss_1A824C[0]->_197736) <= (lbl_2_bss_1A824C[0]->_197738)) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197738);
            o->step = 2;
        }
        if (fn_2_padHeld() & 0x100) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
            o->step = 4;
        }
        break;
    case 2:
        (lbl_2_bss_1A824C[0]->_197736) += ((lbl_2_bss_1A824C[0]->_197734) - (lbl_2_bss_1A824C[0]->_197736)) / 20;
        (lbl_2_bss_1A824C[0]->_197736)--;
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x37);
        lbl_2_bss_1A8234[0]->layerFlags[7][45] = 1;
        if ((lbl_2_bss_1A824C[0]->_197736) <= (lbl_2_bss_1A824C[0]->_197734)) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
            o->step = 4;
        } else if (fn_2_padHeld() & 0x100) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
            o->step = 4;
        }
        break;
    case 3:
        break;
    case 4:
        o->counter = 10;
        o->step = 5;
        break;
    case 5:
        if ((o->counter)-- == 0) {
            (lbl_2_bss_1A824C[0]->_197740) = 1;
            (lbl_2_bss_1A824C[0]->_19773E) = 0;
            q = lbl_803CC1B8->parent;
            q->signal = 1;
            fn_800B0A14_removeQueue(q);
            o->step = 0;
        }
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_3FA14, size:0x3CC
void fn_2_3FA14(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        (lbl_2_bss_1A824C[0]->_197740) = 0;
        (lbl_2_bss_1A824C[0]->_197734) = lbl_2_bss_1A8248[0]->_43BC;
        (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_19773C) = lbl_2_bss_1A8248[0]->_43BE;
        (lbl_2_bss_1A824C[0]->_19773A) = 0;
        (lbl_2_bss_1A824C[0]->_197738) = (lbl_2_bss_1A824C[0]->_197734) / 2;
        o->step = 1;
        break;
    case 1:
        (lbl_2_bss_1A824C[0]->_19773A) *= 2;
        if ((lbl_2_bss_1A824C[0]->_19773A) == 0) {
            (lbl_2_bss_1A824C[0]->_19773A)++;
        }
        (lbl_2_bss_1A824C[0]->_197736) += (lbl_2_bss_1A824C[0]->_19773A);
        (lbl_2_bss_1A824C[0]->_19773A)++;
        lbl_2_bss_1A8234[0]->layerFlags[6][45] = 1;
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x37);
        if ((lbl_2_bss_1A824C[0]->_197736) >= (lbl_2_bss_1A824C[0]->_197738) || (lbl_2_bss_1A824C[0]->_197736) >= (lbl_2_bss_1A824C[0]->_197734)) {
            if ((lbl_2_bss_1A824C[0]->_197736) >= (lbl_2_bss_1A824C[0]->_197734)) {
                (lbl_2_bss_1A824C[0]->_197736) -= (lbl_2_bss_1A824C[0]->_19773A);
                if ((lbl_2_bss_1A824C[0]->_197736) < 1) {
                    (lbl_2_bss_1A824C[0]->_197736) = 1;
                }
            }
            o->step = 2;
        }
        if (fn_2_padHeld() & 0x100) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
            o->step = 4;
        }
        break;
    case 2:
        if ((lbl_2_bss_1A824C[0]->_197736) >= (lbl_2_bss_1A824C[0]->_197734)) {
            (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
            o->step = 4;
        } else {
            (lbl_2_bss_1A824C[0]->_197736) += ((lbl_2_bss_1A824C[0]->_197734) - (lbl_2_bss_1A824C[0]->_197736)) / 20;
            (lbl_2_bss_1A824C[0]->_197736)++;
            lbl_2_bss_1A8234[0]->layerFlags[6][45] = 1;
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x37);
            if (fn_2_padHeld() & 0x100) {
                (lbl_2_bss_1A824C[0]->_197736) = (lbl_2_bss_1A824C[0]->_197734);
                o->step = 4;
            }
        }
        break;
    case 3:
        break;
    case 4:
        o->counter = 10;
        o->step = 5;
        break;
    case 5:
        if ((o->counter)-- == 0) {
            (lbl_2_bss_1A824C[0]->_197740) = 1;
            (lbl_2_bss_1A824C[0]->_19773E) = 0;
            q = lbl_803CC1B8->parent;
            q->signal = 1;
            fn_800B0A14_removeQueue(q);
            o->step = 0;
        }
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

// fn_2_4358C, size:0x444
// NONMATCHING 98%: case 0x49 reloads lbl_2_bss_1A8248 via addi+lwz; dead 2-step counter in the 0x42 loop
#if NONMATCHING
void fn_2_4358C(void) {
    s32 cnt;
    s32 k;
    MenuRosterEntry* e;
    s32 i;
    s32 j;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s32)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    u8* p = lbl_80109AE8 + lbl_800E8558[i * 6 + 2] * 0x64 + j * 10;
                    s32 t = *(s16*)p;
                    s32 c = *(s16*)(p + 2);
                    s32 b = *(s16*)(p + 6);
                    if (t == -1 || e->missions[j].state != 0) {
                        continue;
                    }
                    if (lbl_2_bss_1A823C[0]->mode == 3) {
                        switch (t) {
                        case 0x49:
                            if (lbl_2_bss_1A824C[0]->_197843 == 0 && lbl_2_bss_1A8248[0]->_441E == c &&
                                lbl_2_bss_1A8248[0]->_4415 >= b &&
                                fn_2_countPlayer(lbl_2_bss_1A8248[0], i) > 0) {
                                e->missions[j].state = -2;
                            }
                            break;
                        case 0x42:
                            cnt = 0;
                            for (k = 0; k < 9; k++) {
                                if (lbl_2_bss_1A8248[0]->order[k].charId == 0xC &&
                                    lbl_2_bss_1A8248[0]->_4415 >= b) {
                                    cnt++;
                                }
                            }
                            if (cnt == 0) {
                                lbl_2_bss_1A8248[0]->_44F7 = 1;
                            }
                            break;
                        }
                    } else if (lbl_2_bss_1A823C[0]->mode == 5) {
                        if (t == 0x41 && lbl_2_bss_1A824C[0]->_197843 == 0 && g_d_GameSettings._36 == i &&
                            lbl_2_bss_1A8248[0]->_4415 >= b) {
                            if (!(e->_08 & (1 << lbl_2_bss_1A8248[0]->_4420))) {
                                e->_08 |= (1 << lbl_2_bss_1A8248[0]->_4420);
                            }
                            if (e->_08 == 0x1F) {
                                e->missions[j].state = -2;
                            }
                        }
                    } else if (lbl_2_bss_1A823C[0]->mode == 4) {
                        if (t == 0x48 && lbl_2_bss_1A824C[0]->_197843 == 0 &&
                            lbl_2_bss_1A8248[0]->_4415 >= b && fn_8006C79C(0x13) == 0 &&
                            fn_2_countPlayer(lbl_2_bss_1A8248[0], i) > 0) {
                            e->missions[j].state = -2;
                        }
                    }
                    if (t == 0x47 && fn_8006C5CC() == 1 && lbl_2_bss_1A8248[0]->_4415 >= b &&
                        c == lbl_2_bss_1A8248[0]->_441C) {
                        e->missions[j].state = -2;
                    }
                }
            }
        }
    }
}
#endif

// fn_2_3E38C, size:0x460
void fn_2_3E38C(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    switch ((s8)o->step) {
    case 0:
        fn_2_1C490();
        o->counter = 0x1E;
        if (lbl_2_bss_1A8248[0]->_4422 >= 4 && lbl_2_bss_1A8248[0]->_4446 == 0 &&
            lbl_2_bss_1A8248[0]->_441C != 5) {
            lbl_2_bss_1A8248[0]->_4446 = 1;
            o->step = 1;
        } else {
            o->step = 14;
        }
        break;
    case 1:
        if ((u8)fn_8006862C(0x78, 0) == 0) {
            lbl_2_bss_1A8248[0]->_44F2 = 4;
            fn_2_94854(0xB);
            fn_2_9461C(0xC);
            fn_2_94604(1);
            fn_2_94634(1);
            o->counter = 0x3C;
            o->step = 2;
            fn_2_8F758(0x18, 2);
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            o->step = 3;
        }
        break;
    case 3:
        lbl_2_bss_1A8234[0]->layerFlags[1][47] = 1;
        o->counter = 0xC8;
        o->step = 4;
        break;
    case 4:
        if ((o->counter)-- == 0) {
            o->step = 5;
        }
        break;
    case 5:
        o->counter = 8;
        o->step = 6;
        break;
    case 6:
        if ((o->counter)-- == 0) {
            o->step = 7;
        }
        break;
    case 7:
        lbl_2_bss_1A8248[0]->_4439 = 0;
        fn_2_92654(8, 0);
        fn_2_90428(9);
        fn_2_92654(9, 0xB);
        ((void (*)(s32, Vec*))fn_2_46C2C)(0, (Vec*)(lbl_2_data_3198 + 0xB4));
        lbl_2_bss_1A8248[0]->_441A = 0;
        lbl_2_bss_1A8248[0]->slots[41]._6 = 0;
        fn_80062890(5);
        o->counter = 0x50;
        o->step = 8;
        break;
    case 8:
        if (o->counter == 0x46) {
            ((void (*)(s32, Vec*))fn_2_46C2C)(0, (Vec*)(lbl_2_data_3198 + 0xB4));
        }
        if ((o->counter)-- == 0) {
            o->step = 9;
        }
        break;
    case 9:
        fn_2_92654(0x18, 0xF);
        o->counter = 0xC8;
        o->step = 10;
        break;
    case 10:
        if ((o->counter)-- == 0) {
            o->step = 11;
        }
        break;
    case 11:
        if ((u8)fn_80068514(0x78, 0x7F) == 0) {
            o->step = 12;
        }
        break;
    case 12:
        fn_2_94854(0xB);
        fn_2_9461C(0);
        fn_2_94604(1);
        fn_2_94634(1);
        o->counter = 0x3C;
        o->step = 13;
        break;
    case 13:
        if ((o->counter)-- == 0) {
            lbl_2_bss_1A8248[0]->_44F2 = 0;
            o->step = 14;
        }
        break;
    case 14:
        fn_2_1C41C();
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    (o->arg)++;
    if (o->arg == 0xA6) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3A);
    } else if (o->arg == 0xF6) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3B);
    } else if (o->arg == 0x146) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3E);
    } else if (o->arg == 0x150) {
    } else if (o->arg == 0x204) {
    } else if (o->arg == 0x13C) {
        lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0x3C);
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

static inline s32 fn_2_countSpecial(MenuCtx* m) {
    s32 k;
    s32 cnt = 0;
    for (k = 0; k < 9; k++) {
        s32 v = m->order[k].charId;
        if (v == 0xD || (u32)(v - 0x1D) <= 2 || v == 0x20) {
            cnt++;
        }
    }
    return cnt >= 5;
}

static inline s32 fn_2_countLow(MenuCtx* m) {
    s32 k;
    s32 cnt = 0;
    for (k = 0; k < 9; k++) {
        s32 v = m->order[k].charId;
        if (v == 0 || v == 1) {
            cnt++;
        }
    }
    return cnt == 2;
}

// fn_2_439D0, size:0x4BC
void fn_2_439D0(void) {
    s32 i;
    s32 j;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s32)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    u8* p = lbl_80109AE8 + lbl_800E8558[i * 6 + 2] * 0x64 + j * 10;
                    s32 t = *(s16*)p;
                    s32 c = *(s16*)(p + 2);
                    s32 a = *(s16*)(p + 4);
                    s32 b = *(s16*)(p + 6);
                    if (t == -1 || e->missions[j].state != 0) {
                        continue;
                    }
                    switch (t) {
                    case 0x3D:
                        if (lbl_2_bss_1A8248[0]->_441C == a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x3C:
                        if (lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x45:
                        if (lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x42:
                        if ((s8)lbl_2_bss_1A8248[0]->_44F7 == 0) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x3E:
                        if (fn_2_countSpecial(lbl_2_bss_1A8248[0]) == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x3F:
                        if (lbl_2_bss_1A8248[0]->_441C == c && (s8)lbl_2_bss_1A8248[0]->_44F6 == 0 &&
                            lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x40:
                        if (fn_2_countLow(lbl_2_bss_1A8248[0]) == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x43:
                        if (fn_2_hasPlayer(lbl_2_bss_1A8248[0], i) == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    case 0x44:
                        if (fn_2_hasPlayer(lbl_2_bss_1A8248[0], i) == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                            e->missions[j].state = -2;
                        }
                        break;
                    }
                }
            }
        }
    }
}

// fn_2_42708, size:0x4E0
void fn_2_42708(void) {
    s32 i;
    s32 j;
    s32 r;
    MenuRosterEntry* e;
    for (i = 0; i < 54; i++) {
        if (lbl_800E8558[i * 6 + 3] == 1) {
            e = &lbl_2_bss_1A8248[0]->chars[i];
            if ((s32)e->_31 == 1) {
                for (j = 0; j < 10; j++) {
                    s32 row = lbl_800E8558[i * 6 + 2] * 0x64;
                    s32 t = *(s16*)(lbl_80109AE8 + row + j * 10);
                    u8* p = lbl_8010A768 + row + j * 10;
                    s32 type = *(s16*)(p + 2);
                    s32 a = *(s16*)(p + 4);
                    s32 b = *(s16*)(p + 6);
                    s32 c = *(s16*)(p + 8);
                    if (type != -1 && (s8)e->missions[j].shown == 0) {
                        switch (type) {
                        case 1:
                            if (fn_8006CDC0(i) >= a && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 3:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 1) && lbl_2_bss_1A8248[0]->_4415 >= a) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 4:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 2) && lbl_2_bss_1A8248[0]->_4415 >= a) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 5:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 4) && lbl_2_bss_1A8248[0]->_4415 >= a) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 6:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 8) && lbl_2_bss_1A8248[0]->_4415 >= a) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 7:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 16) && lbl_2_bss_1A8248[0]->_4415 >= a) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 8:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 1) && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 9:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 2) && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 10:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 4) && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 11:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 8) && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 12:
                            if ((lbl_2_bss_1A8248[0]->_4428 & 16) && lbl_2_bss_1A8248[0]->_441C == a &&
                                lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 13:
                            r = fn_8006C79C(i);
                            if ((lbl_2_bss_1A8248[0]->_4428 & 1) && r == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 14:
                            r = fn_8006C79C(i);
                            if ((lbl_2_bss_1A8248[0]->_4428 & 2) && r == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 15:
                            r = fn_8006C79C(i);
                            if ((lbl_2_bss_1A8248[0]->_4428 & 4) && r == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 16:
                            r = fn_8006C79C(i);
                            if ((lbl_2_bss_1A8248[0]->_4428 & 8) && r == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 17:
                            r = fn_8006C79C(i);
                            if ((lbl_2_bss_1A8248[0]->_4428 & 16) && r == 1 && lbl_2_bss_1A8248[0]->_4415 >= b) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        case 20:
                            if (lbl_2_bss_1A8248[0]->_441C == a && lbl_2_bss_1A8248[0]->_43BC >= b &&
                                lbl_2_bss_1A8248[0]->_4415 >= c) {
                                e->missions[j].shown = 1;
                            }
                            break;
                        }
                    }
                    if (t != -1 && e->missions[j].state < 0) {
                        e->missions[j].shown = 1;
                    }
                }
            }
        }
    }
}

extern s16 lbl_2_data_373C[];
extern s32 fn_8006C6C4(void);

// fn_2_3C7DC, size:0x558
void fn_2_3C7DC(void) {
    s32 i;
    for (i = 0; i < 20; i++) {
        lbl_2_bss_1A824C[0]->_19789F[i] = 0;
    }
    fn_8006C6C4();
    for (i = 0; i < 20; i++) {
        if (lbl_2_data_373C[i] == 1) {
            if (i == 5 && lbl_2_bss_1A8248[0]->_442C == 0) {
                lbl_2_bss_1A824C[0]->_19789F[i] = 2;
            } else if (i == 19) {
                if ((s8)lbl_2_bss_1A8248[0]->_43C2[0] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[1] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[2] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[3] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[4] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[5] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[6] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[7] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[8] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[9] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[10] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[11] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[12] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[13] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[14] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[15] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[16] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[17] == 0 ||
                    (s8)lbl_2_bss_1A8248[0]->_43C2[18] == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
            }
        } else if (lbl_2_data_373C[i] == 0 && (s8)lbl_2_bss_1A8248[0]->_43C2[i] == 1) {
            lbl_2_bss_1A824C[0]->_19789F[i] = 1;
        } else if (lbl_2_data_373C[i] == 0 && (s8)lbl_2_bss_1A8248[0]->_43C2[i] == 0) {
            switch (i) {
            case 6:
                if (fn_8006C79C(0) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 8:
                if (fn_8006C79C(4) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 10:
                if (fn_8006C79C(0xA) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 12:
                if (fn_8006C79C(6) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 14:
                if (fn_8006C79C(2) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 16:
                if (fn_8006C79C(9) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 7:
                if (fn_8006C79C(1) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 9:
                if (fn_8006C79C(5) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 11:
                if (fn_8006C79C(0xB) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 13:
                if (fn_8006C79C(0x11) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 15:
                if (fn_8006C79C(3) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 17:
                if (fn_8006C79C(0x13) == 0) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            case 18:
                if (lbl_2_bss_1A8248[0]->_4428 != 0x1F) {
                    lbl_2_bss_1A824C[0]->_19789F[i] = 2;
                }
                break;
            }
        }
    }
}

// fn_2_3FDE0, size:0x63C
void fn_2_3FDE0(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    s16 v;
    s32 i;
    switch ((s8)o->step) {
    case 0:
        o->counter = 0x46;
        v = *(s16*)(lbl_2_data_3CE8 + lbl_2_bss_1A8248[0]->_441C * 0xC + lbl_2_bss_1A8248[0]->_4422 * 2 + 2);
        ((s8**)lbl_2_bss_1A824C)[0][0x197851] = -1;
        if (*(s16*)(lbl_2_data_3CE8 + lbl_2_bss_1A8248[0]->_441C * 0xC + lbl_2_bss_1A8248[0]->_4422 * 2) != 5) {
            for (i = 0; i < 51; i++) {
                if (v == lbl_2_bss_1A8248[0]->slots[i]._2 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1) {
                    lbl_2_bss_1A8248[0]->slots[i]._3 = 0;
                    ((s8**)lbl_2_bss_1A824C)[0][0x197851] = v;
                }
            }
        }
        if (lbl_2_bss_1A824C[0]->_197851 != -1) {
            lbl_2_bss_1A8248[0]->_440C[lbl_2_bss_1A824C[0]->_197851] = 1;
            switch (lbl_2_bss_1A8248[0]->_441C) {
            case 0:
                if ((s32)(u8)lbl_2_bss_1A824C[0]->_197851 == 3) {
                    for (i = 0; i < 51; i++) {
                        if ((lbl_2_bss_1A8248[0]->slots[i]._2 == 6 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1) ||
                            (lbl_2_bss_1A8248[0]->slots[i]._2 == 8 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1)) {
                            lbl_2_bss_1A8248[0]->slots[i]._3 = 0;
                        }
                    }
                }
                break;
            case 1:
                if ((s32)(u8)lbl_2_bss_1A824C[0]->_197851 == 3) {
                    for (i = 0; i < 51; i++) {
                        if ((lbl_2_bss_1A8248[0]->slots[i]._2 == 6 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1) ||
                            (lbl_2_bss_1A8248[0]->slots[i]._2 == 8 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1)) {
                            lbl_2_bss_1A8248[0]->slots[i]._3 = 0;
                        }
                    }
                }
                break;
            case 2:
                if ((s32)(u8)lbl_2_bss_1A824C[0]->_197851 == 1) {
                    for (i = 0; i < 51; i++) {
                        if ((lbl_2_bss_1A8248[0]->slots[i]._2 == 6 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1) ||
                            (lbl_2_bss_1A8248[0]->slots[i]._2 == 7 && lbl_2_bss_1A8248[0]->slots[i]._3 == 1)) {
                            lbl_2_bss_1A8248[0]->slots[i]._3 = 0;
                        }
                    }
                }
                break;
            case 3:
                break;
            }
            lbl_2_bss_1A8234[0]->layerFlags[3][15] = 1;
            fn_80062890(4);
            o->step = 1;
        } else {
            o->step = 4;
        }
        break;
    case 1:
        if ((o->counter)-- == 0) {
            fn_2_92654(lbl_2_bss_1A824C[0]->_197851 + 1, 7);
            if ((s32)(u8)lbl_2_bss_1A824C[0]->_197851 == 2) {
                fn_2_92654(7, 7);
            }
            o->counter = 0x3C;
            o->step = 2;
        }
        break;
    case 2:
        if ((o->counter)-- == 0) {
            if ((s32)(u8)lbl_2_bss_1A824C[0]->_197851 == 5) {
                lbl_2_bss_1A8234[0]->layerFlags[3][17] = 1;
                o->counter = 0x10;
                o->step = 3;
            } else {
                o->step = 4;
            }
        }
        break;
    case 3:
        if ((o->counter)-- == 0) {
            lbl_2_bss_1A8248[0]->_441A = 1;
            o->step = 4;
        }
        break;
    case 4:
        q = o->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

extern s16 lbl_2_data_3764[][4];
extern void fn_2_50B0C(s32 id, s32 arg);
extern void fn_2_50CC0(s16 value);
extern void fn_2_46D94(s16* sel, s16* scroll, s16 count, s16 page, u32 flags);
extern void fn_2_46D34(s32 delta);
extern void fn_2_38538(void);

static inline void fn_2_3CD34_showDesc(void) {
    s32 idx = (lbl_2_bss_1A824C[0]->_197726);
    if ((s32)lbl_2_bss_1A824C[0]->_19789F[idx] == 2) {
        fn_2_50B0C(0x26C, 0);
    } else {
        fn_2_50B0C((s16)(idx + 0x26D), 0);
    }
}

// fn_2_3CD34, size:0x890
void fn_2_3CD34(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    MenuScreenTask* q;
    u8* t;
    u16 btn;
    s32 idx;
    s32 v;
    switch ((s8)o->step) {
    case 0:
        ((void (*)(void))fn_2_42638)();
        ((void (*)(void))fn_2_45E48)();
        ((void (*)(void))fn_2_3C7DC)();
        (lbl_2_bss_1A824C[0]->_197726) = 0;
        (lbl_2_bss_1A824C[0]->_19772A) = 0;
        (lbl_2_bss_1A824C[0]->_197728) = 0;
        (lbl_2_bss_1A824C[0]->_19772C) = 0x14;
        o->counter = 0x12;
        lbl_2_bss_1A8234[0]->layerFlags[1][43] = 1;
        o->step = 1;
        break;
    case 1:
        if ((o->counter)-- == 0) {
            fn_2_3CD34_showDesc();
            o->step = 2;
        }
        break;
    case 2:
        t = (u8*)&lbl_803C77B8;
        t += lbl_2_bss_1A824C[0]->port * sizeof(MenuPad);
        if (((MenuPad*)t)->repeat == 8 || ((MenuPad*)t)->repeat == 4) {
            lbl_2_bss_1A8234[0]->layerFlags[6][43] = 1;
            fn_2_46D94(&(lbl_2_bss_1A824C[0]->_197728), &(lbl_2_bss_1A824C[0]->_19772A), (lbl_2_bss_1A824C[0]->_19772C), 6, 9);
            (lbl_2_bss_1A824C[0]->_197726) = (lbl_2_bss_1A824C[0]->_197728) + (lbl_2_bss_1A824C[0]->_19772A);
            fn_2_3CD34_showDesc();
            o->step = 3;
            break;
        }
        (lbl_2_bss_1A824C[0]->_197726) = (lbl_2_bss_1A824C[0]->_197728) + (lbl_2_bss_1A824C[0]->_19772A);
        btn = ((MenuPad*)&lbl_803C77B8)[lbl_2_bss_1A824C[0]->port].down;
        if (btn & 0x100) {
            idx = (lbl_2_bss_1A824C[0]->_197726);
            v = lbl_2_bss_1A824C[0]->_19789F[idx];
            if ((s8)v == 2) {
                fn_2_50B0C(0x267, 0);
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if ((s8)v == 1) {
                fn_2_50B0C(0x269, 0);
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if ((s8)v == 0 &&
                       lbl_2_data_3764[idx][lbl_2_bss_1A8248[0]->_4415] > lbl_2_bss_1A8248[0]->_43BC) {
                fn_2_50B0C(0x268, 0);
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (lbl_2_bss_1A8248[0]->_444B == idx && lbl_2_data_373C[idx] == 1) {
                fn_2_50B0C(0x269, 0);
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else {
                o->step = 7;
            }
        } else if (btn & 0x200) {
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            lbl_2_bss_1A8234[0]->layerFlags[8][43] = 1;
            o->step = 9;
        }
        break;
    case 7:
        if (lbl_2_bss_1A8248[0]->_444B == -1 || lbl_2_data_373C[(lbl_2_bss_1A824C[0]->_197726)] == 0) {
            fn_2_50CC0(0x264);
        } else {
            fn_2_50CC0(0x265);
        }
        o->signal = 0;
        o->step = 8;
        break;
    case 8:
        if (o->signal == 1 && (lbl_2_bss_1A824C[0]->_1972B0) == 0) {
            lbl_2_bss_1A8234[0]->layerFlags[3][43] = 1;
            fn_2_50B0C(0x26A, 0);
            if (lbl_2_data_373C[(lbl_2_bss_1A824C[0]->_197726)] == 1) {
                lbl_2_bss_1A8234[0]->layerFlags[3][46] = 1;
                lbl_2_bss_1A8248[0]->_444A = 1;
                lbl_2_bss_1A8248[0]->_444B = (lbl_2_bss_1A824C[0]->_197726);
            }
            lbl_2_bss_1A8248[0]->_43C2[(lbl_2_bss_1A824C[0]->_197726)] = 1;
            ((void (*)(void))fn_2_3C7DC)();
            if ((lbl_2_bss_1A824C[0]->_197726) == 0x12) {
                lbl_2_bss_1A824C[0]->_19789E = 1;
            }
            lbl_2_bss_1A824C[0]->_1978F4 = 1;
            lbl_2_bss_1A824C[0]->_1978F5 = (lbl_2_bss_1A824C[0]->_197726);
            lbl_2_bss_1A824C[0]->_1976A8 = fn_80062890(0xC);
            o->counter = 0x10;
            o->step = 4;
        } else if (o->signal == 1 && (lbl_2_bss_1A824C[0]->_1972B0) == 1) {
            fn_2_3CD34_showDesc();
            o->step = 2;
        }
        break;
    case 3:
        o->step = 2;
        break;
    case 4:
        if ((o->counter)-- == 0) {
            o->step = 5;
        }
        break;
    case 5:
        fn_2_46D34(-lbl_2_data_3764[(lbl_2_bss_1A824C[0]->_197726)][lbl_2_bss_1A8248[0]->_4415]);
        if (lbl_2_bss_1A8248[0]->_43BE > 0) {
            t = fn_800B0A5C_insertQueue(fn_2_3F66C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
        } else {
            o->signal = 1;
        }
        o->step = 6;
        break;
    case 6:
        if (o->signal == 1) {
            if (lbl_2_data_373C[(lbl_2_bss_1A824C[0]->_197726)] == 1) {
                lbl_2_bss_1A8248[0]->_444C = (u8)lbl_2_bss_1A8248[0]->_444B;
            }
            o->step = 2;
        }
        break;
    case 9:
        ((void (*)(void))fn_2_44014)();
        ((void (*)(void))fn_2_43E8C)();
        ((void (*)(void))fn_2_432EC)();
        fn_2_50CC0(0x26B);
        o->signal = 0;
        o->step = 10;
        break;
    case 10:
        if (o->signal == 1) {
            lbl_2_bss_1A8234[0]->layerFlags[8][2] = 1;
            lbl_2_bss_1A8234[0]->layerFlags[8][3] = 1;
            lbl_2_bss_1A8234[0]->layerFlags[8][4] = 1;
            (lbl_2_bss_1A824C[0]->_1972AC[0]) = 0;
            lbl_2_bss_1A824C[0]->_1972B9 = 0;
            lbl_2_bss_1A8234[0]->layerFlags[8][14] = 1;
            lbl_2_bss_1A8234[0]->layerFlags[8][61] = 1;
            lbl_2_bss_1A8234[0]->layerFlags[8][62] = 1;
            t = fn_800B0A5C_insertQueue(fn_2_38538, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            o->step = 11;
        }
        break;
    case 11:
        if (o->signal == 1) {
            t = fn_800B0A5C_insertQueue(fn_2_3C53C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            o->step = 12;
        }
        break;
    case 12:
        if (o->signal == 1) {
            q = o->parent;
            q->signal = 1;
            fn_800B0A14_removeQueue(q);
            o->step = 0;
        }
        break;
    }
    if (lbl_2_bss_1A824C[0]->_19783F == 1) {
        q = lbl_803CC1B8->parent;
        q->signal = 1;
        fn_800B0A14_removeQueue(q);
        o->step = 0;
    }
}

#define ROSTER_LIST(i) (lbl_2_bss_1A824C[0]->frameSetA[i])
#define ROSTER_B(i) (lbl_2_bss_1A824C[0]->frameSetB[i])
#define ROSTER_C(i) (lbl_2_bss_1A824C[0]->frameSetC[i])
#define ROSTER_SORT(i) (lbl_2_bss_1A824C[0]->sortList[i])
#define CHAR_INFO(id) ((u8*)lbl_2_bss_1A8248[0]->chars[(id)].limits)

// fn_2_44504, size:0x928
// NONMATCHING 95%: register allocation and loop scheduling differ; structure and calls match
#if NONMATCHING
void fn_2_44504(void) {
    s32 i;
    s32 k;
    s32 n;
    s32 cnt;
    s32 c;
    s32 id;
    SortEnt tmp;
    for (i = 0; i < 54; i++) {
        ROSTER_LIST(i) = 10000;
    }
    for (k = 0; k < 5; k++) {
        ROSTER_B(k) = -1;
        ROSTER_C(k) = -1;
    }
    n = fn_8006C6C4();
    cnt = 0;
    for (i = 0; i < 54; i++) {
        MenuCtx* m = lbl_2_bss_1A8248[0];
        if ((s32)m->chars[i]._31 == 1 && i != lbl_803CB8F0[m->_441C]) {
            ROSTER_LIST(cnt++) = i;
        }
    }
    c = 0;
    for (k = 0; k < 9; k++) {
        if (n + c < 32) {
            id = lbl_2_bss_1A8248[0]->order[k].charId;
            if (lbl_2_bss_1A8248[0]->chars[id]._05 == 4) {
                ROSTER_LIST(cnt++) = id;
                c++;
            }
        }
    }
    c = 0;
    for (i = 0; i < cnt; i++) {
        id = ROSTER_LIST(i);
        if (id != 10000 && (s32)CHAR_INFO(id)[2] == 4) {
            ROSTER_C(c++) = id;
            ROSTER_LIST(i) = 10000;
        }
    }
    if (n >= 10) {
        c = 0;
        for (i = 0; i < cnt; i++) {
            id = ROSTER_LIST(i);
            if (id != 10000 && (s32)CHAR_INFO(id)[3] == 1) {
                ROSTER_B(c++) = id;
                ROSTER_LIST(i) = 10000;
            }
        }
    }
    for (i = 0; i < 55; i++) {
        ROSTER_SORT(i).k = 10000;
        ROSTER_SORT(i).v = 10000;
    }
    for (i = 0; i < cnt + 1; i++) {
        id = ROSTER_LIST(i);
        if (id != 10000) {
            ROSTER_SORT(i + 1).k = (s8)CHAR_INFO(id)[2];
            ROSTER_SORT(i + 1).v = ROSTER_LIST(i);
        } else {
            ROSTER_SORT(i + 1).k = 10000;
            ROSTER_SORT(i + 1).v = 10000;
        }
    }
    {
        SortEnt* s = &ROSTER_SORT(0);
        for (i = 1; i < 55; i++) {
            tmp = s[i];
            s[0] = tmp;
            for (k = i - 1; tmp.k < s[k].k; k--) {
                s[k + 1] = s[k];
            }
            s[k + 1] = tmp;
        }
    }
    for (i = 0; i < 54; i++) {
        ROSTER_LIST(i) = -1;
    }
    c = 0;
    for (i = 0; i < 54; i++) {
        if (ROSTER_SORT(i + 1).v != 10000) {
            ROSTER_LIST(c++) = ROSTER_SORT(i + 1).v;
        }
    }
    for (k = 0; k < 5; k++) {
        if (ROSTER_C(k) == 0x26) {
            s16 t = ROSTER_C(2);
            ROSTER_C(2) = 0x26;
            ROSTER_C(k) = t;
        }
    }
}
#endif

extern void fn_2_6AF80(s32 index, s8 value);
extern s32 fn_2_6AFD4(s32 index);
extern void fn_2_38A40(void);
extern void fn_2_3BA40(void);
extern void fn_2_3BD88(void);
extern void fn_2_3BC24(void);
extern void fn_2_399C0(void);
extern void fn_2_37F04(void);

#define SCRIPT_PC (lbl_2_bss_1A824C[0]->scriptPc)

// fn_2_40CB8, size:0x15B8
// Menu script interpreter: runs opcodes at SCRIPT_PC until one yields.
// Returns 1 when the script ends (opcode 2).
s32 fn_2_40CB8(void) {
    MenuScreenTask* o = lbl_803CC1B8;
    u32* pc;
    u8* t;
    s32 id;
    if ((lbl_2_bss_1A824C[0]->_19768C) != 0) {
        (lbl_2_bss_1A824C[0]->_19768C)--;
        return 0;
    }
    for (;;) {
        pc = SCRIPT_PC;
        switch (*pc) {
        case 1:
            (lbl_2_bss_1A824C[0]->_197694) = 0;
            SCRIPT_PC++;
            continue;
        case 2:
            (lbl_2_bss_1A824C[0]->_197694) = 1;
            return 1;
        case 3:
            (lbl_2_bss_1A824C[0]->_19768C) = pc[1];
            SCRIPT_PC += 2;
            break;
        case 5:
            fn_2_50CC0((s16)pc[1]);
            o->signal = 0;
            SCRIPT_PC += 2;
            continue;
        case 27:
            if ((s8)lbl_2_bss_1A8248[0]->_44EF == 0) {
                s32 who = lbl_2_bss_1A8248[0]->_441E;
                if (!(lbl_2_bss_1A8248[0]->_4427 & (1 << who))) {
                    id = who + lbl_2_bss_1A8248[0]->_441C * 6 + 0x4B;
                } else if (!(lbl_2_bss_1A8248[0]->_4426 & (1 << who))) {
                    id = who + lbl_2_bss_1A8248[0]->_441C * 6 + 0x93;
                } else if ((s8)lbl_2_bss_1A8248[0]->_44FE[who] == 0) {
                    id = who + lbl_2_bss_1A8248[0]->_441C * 6 + 3;
                } else {
                    id = who + lbl_2_bss_1A8248[0]->_441C * 6 + 0x93;
                }
            } else if ((s8)lbl_2_bss_1A8248[0]->_44F0 == 0) {
                id = 0x22C;
            } else {
                id = 0x22D;
            }
            fn_2_50CC0((s16)(id));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 28:
            if (((s32 (*)(s32))fn_2_45938)(lbl_2_bss_1A8248[0]->entries[0].locationIndex) == 1) {
                id = lbl_2_bss_1A8248[0]->_441E + lbl_2_bss_1A8248[0]->_441C * 6 + 0x124;
            } else {
                id = lbl_2_bss_1A8248[0]->_441E + lbl_2_bss_1A8248[0]->_441C * 6 + 0x148;
            }
            fn_2_50CC0((s16)(id));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 72:
            if ((s8)lbl_2_bss_1A8248[0]->_44EF == 0) {
                id = lbl_2_bss_1A8248[0]->_441E + lbl_2_bss_1A8248[0]->_441C * 6 + 0x190;
            } else {
                id = 0x232;
            }
            fn_2_50CC0((s16)(id));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 29:
            if ((s8)lbl_2_bss_1A8248[0]->_44EF == 0) {
                id = lbl_2_bss_1A8248[0]->_441E + lbl_2_bss_1A8248[0]->_441C * 6 + 0x16C;
            } else {
                id = 0x231;
            }
            fn_2_50CC0((s16)(id));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 30:
            if ((s8)lbl_2_bss_1A8248[0]->_44FE[6] == 0) {
                id = lbl_2_bss_1A8248[0]->_441C + lbl_2_bss_1A8248[0]->_442C * 6 + 0x1B4;
            } else {
                id = lbl_2_bss_1A8248[0]->_441C + lbl_2_bss_1A8248[0]->_442D * 6 + 0x1CC;
            }
            fn_2_50CC0((s16)(id));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 31:
            fn_2_50CC0((s16)(lbl_2_bss_1A8248[0]->_441C + lbl_2_bss_1A8248[0]->_442C * 6 + 0x1E4));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 32:
            fn_2_50CC0((s16)(lbl_2_bss_1A8248[0]->_441C + lbl_2_bss_1A8248[0]->_442D * 6 + 0x1FC));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 73:
            fn_2_50CC0((s16)(lbl_2_bss_1A8248[0]->_441C + lbl_2_bss_1A8248[0]->_442E * 6 + 0x214));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 6:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 7:
            lbl_2_bss_1A824C[0]->_19783D = 1;
            if (lbl_2_bss_1A823C[0]->mode == 4) {
                fn_2_72054(0, 0xC);
                lbl_2_bss_1A8248[0]->entries[0].targetLocation = lbl_2_bss_1A8248[0]->entries[0]._AE;
            } else {
                fn_2_6AF80(0, 1);
            }
            SCRIPT_PC++;
            continue;
        case 8:
            if (fn_2_6AFD4(0) == 1) {
                SCRIPT_PC++;
            }
            break;
        case 9:
            t = fn_800B0A5C_insertQueue(fn_2_405B4, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 10:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 15:
            t = fn_800B0A5C_insertQueue(fn_2_4041C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 16:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 11:
            SCRIPT_PC++;
            continue;
        case 12:
            SCRIPT_PC++;
            break;
        case 13:
            SCRIPT_PC++;
            continue;
        case 14:
            SCRIPT_PC++;
            break;
        case 33:
            if (lbl_2_bss_1A8248[0]->_43BE < 999) {
                t = fn_800B0A5C_insertQueue(fn_2_3FA14, 2);
                ((MenuScreenTask*)t)->step = 0;
                o->signal = 0;
            } else {
                (lbl_2_bss_1A824C[0]->_197740) = 1;
                o->signal = 1;
            }
            SCRIPT_PC++;
            continue;
        case 34:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 35:
            if (lbl_2_bss_1A8248[0]->_43BE > 0) {
                t = fn_800B0A5C_insertQueue(fn_2_3F66C, 2);
                ((MenuScreenTask*)t)->step = 0;
                o->signal = 0;
            } else {
                (lbl_2_bss_1A824C[0]->_197740) = 1;
                o->signal = 1;
            }
            SCRIPT_PC++;
            continue;
        case 36:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 37:
            t = fn_800B0A5C_insertQueue(fn_2_3F55C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 38:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 39:
            t = fn_800B0A5C_insertQueue(fn_2_3F44C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 40:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 17:
            t = fn_800B0A5C_insertQueue(fn_2_3FDE0, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 18:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 19:
            fn_2_72054(1, 0xE);
            SCRIPT_PC++;
            continue;
        case 20:
            if (fn_2_6AFD4(1) == 1) {
                SCRIPT_PC++;
            }
            break;
        case 107:
            if ((lbl_2_bss_1A824C[0]->_197740) == 1) {
                (lbl_2_bss_1A824C[0]->_197740) = 0;
                SCRIPT_PC++;
            }
            break;
        case 21:
            fn_2_72054(0, 2);
            SCRIPT_PC++;
            continue;
        case 22:
            if (fn_2_6AFD4(0) == 1) {
                SCRIPT_PC++;
            }
            break;
        case 23:
            t = fn_800B0A5C_insertQueue(fn_2_38A40, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            (lbl_2_bss_1A824C[0]->_197688) = *SCRIPT_PC;
            *SCRIPT_PC = 24;
            continue;
        case 24:
            if (o->signal == 1) {
                *pc = (lbl_2_bss_1A824C[0]->_197688);
                SCRIPT_PC++;
            }
            break;
        case 25:
            lbl_2_bss_1A824C[0]->_197844 = 2;
            lbl_2_bss_1A8234[0]->layerFlags[8][61] = 1;
            lbl_2_bss_1A8234[0]->layerFlags[8][62] = 1;
            t = fn_800B0A5C_insertQueue(fn_2_38538, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            (lbl_2_bss_1A824C[0]->_197688) = *SCRIPT_PC;
            *SCRIPT_PC = 26;
            continue;
        case 26:
            if (o->signal == 1) {
                *pc = (lbl_2_bss_1A824C[0]->_197688);
                SCRIPT_PC++;
            }
            break;
        case 41:
            t = fn_800B0A5C_insertQueue(fn_2_3F29C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            (lbl_2_bss_1A824C[0]->_197688) = *SCRIPT_PC;
            SCRIPT_PC++;
            continue;
        case 42:
            if (o->signal == 1) {
                *pc = (lbl_2_bss_1A824C[0]->_197688);
                SCRIPT_PC++;
            }
            break;
        case 43:
            t = fn_800B0A5C_insertQueue(fn_2_3EA44, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 44:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 45:
            t = fn_800B0A5C_insertQueue(fn_2_3E7EC, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 46:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 47:
            t = fn_800B0A5C_insertQueue(fn_2_3E918, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 48:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 49:
            t = fn_800B0A5C_insertQueue(fn_2_3F188, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 50:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 51:
            t = fn_800B0A5C_insertQueue(fn_2_3F004, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 52:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 53:
            t = fn_800B0A5C_insertQueue(fn_2_3EEF0, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 54:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 55:
            t = fn_800B0A5C_insertQueue(fn_2_3EDD8, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 56:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 57:
            t = fn_800B0A5C_insertQueue(fn_2_3ECC0, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 58:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 59:
            t = fn_800B0A5C_insertQueue(fn_2_3EBA8, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 60:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 61:
            t = fn_800B0A5C_insertQueue(fn_2_408BC, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 62:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 63:
            (lbl_2_bss_1A824C[0]->_19774C) = pc[1];
            lbl_2_bss_1A8234[0]->layerFlags[1][4] = 1;
            SCRIPT_PC += 2;
            continue;
        case 65:
            (lbl_2_bss_1A824C[0]->_19774C) = pc[1];
            lbl_2_bss_1A8234[0]->layerFlags[1][5] = 1;
            SCRIPT_PC += 2;
            continue;
        case 64:
            lbl_2_bss_1A8234[0]->layerFlags[8][4] = 1;
            SCRIPT_PC++;
            continue;
        case 85:
            lbl_2_bss_1A8234[0]->layerFlags[8][5] = 1;
            SCRIPT_PC++;
            continue;
        case 66:
            lbl_2_bss_1A824C[0]->_197859 = 0;
            lbl_2_bss_1A824C[0]->_197857 = SCRIPT_PC[1];
            lbl_2_bss_1A8234[0]->layerFlags[1][1] = 1;
            o->signal = 0;
            SCRIPT_PC += 2;
            continue;
        case 67:
            if (lbl_2_bss_1A824C[0]->_197859 == 1) {
                SCRIPT_PC++;
            }
            break;
        case 68:
            if ((lbl_2_bss_1A824C[0]->_19774E) == (s32)pc[1]) {
                SCRIPT_PC += 2;
            }
            break;
        case 69:
            lbl_2_bss_1A8234[0]->layerFlags[1][3] = 1;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 70:
            t = fn_800B0A5C_insertQueue(fn_2_3BA40, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 71:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 74:
            fn_2_72054(0, 3);
            SCRIPT_PC++;
            continue;
        case 75:
            fn_2_72054(0, 3);
            SCRIPT_PC++;
            continue;
        case 76:
            fn_2_72054(0, 3);
            fn_2_72054(lbl_2_bss_1A8248[0]->_441E, 7);
            SCRIPT_PC++;
            continue;
        case 77:
            fn_2_72054(0, 3);
            SCRIPT_PC++;
            continue;
        case 78:
            t = fn_800B0A5C_insertQueue(fn_2_3C3EC, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 79:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 80:
            t = fn_800B0A5C_insertQueue(fn_2_3C168, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 81:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 82:
            t = fn_800B0A5C_insertQueue(fn_2_3C03C, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 83:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 84:
            fn_2_50CC0((s16)(lbl_2_bss_1A8248[0]->_441C + 0x23A));
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 86:
            t = fn_800B0A5C_insertQueue(fn_2_3E38C, 2);
            ((MenuScreenTask*)t)->step = 0;
            *(s16*)(t + 0x16) = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 87:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 96:
            t = fn_800B0A5C_insertQueue(fn_2_3E058, 2);
            ((MenuScreenTask*)t)->step = 0;
            *(s16*)(t + 0x16) = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 97:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 88:
            t = fn_800B0A5C_insertQueue(fn_2_3D5C4, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 89:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 90:
            t = fn_800B0A5C_insertQueue(fn_2_3DF28, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 91:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 94:
            t = fn_800B0A5C_insertQueue(fn_2_3CD34, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 95:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 98:
            t = fn_800B0A5C_insertQueue(fn_2_3BD88, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 99:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 100:
            t = fn_800B0A5C_insertQueue(fn_2_3BD88, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 101:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 102:
            t = fn_800B0A5C_insertQueue(fn_2_3BC24, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 103:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 104:
            t = fn_800B0A5C_insertQueue(fn_2_399C0, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 105:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        case 106:
            ((void (*)(void))fn_2_43404)();
            ((void (*)(void))fn_2_42708)();
            ((void (*)(void))fn_2_432EC)();
            SCRIPT_PC++;
            continue;
        case 108:
            t = fn_800B0A5C_insertQueue(fn_2_37F04, 2);
            ((MenuScreenTask*)t)->step = 0;
            o->signal = 0;
            SCRIPT_PC++;
            continue;
        case 109:
            if (o->signal == 1) {
                SCRIPT_PC++;
            }
            break;
        }
        break;
    }
    return 0;
}

void* lbl_2_data_12CE8[1] = {(void*)&lbl_2_data_12558};
