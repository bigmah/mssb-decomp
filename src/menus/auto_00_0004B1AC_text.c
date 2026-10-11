#include "menus/auto_00_0004B1AC_text.h"

#include <string.h>
#include "Dolphin/GX.h"
extern void fn_2_4906C(void);

extern void fn_8003BF54(u8 a, u8 b, u8 slot, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h);

extern void fn_2_52690(void);
extern u8 lbl_8034E9A0[];

#include "static/UnknownHomes_Static.h"
#include "main/file_8000F150.h"

extern u32 lbl_803C7898[];
extern void fn_80034E20(void* object, void* data);

extern u8* lbl_2_bss_1A824C[];

extern void fn_2_89F70(void);

extern u8 lbl_2_data_1323C[];

extern u8 lbl_2_data_1324C[];

extern u8 lbl_2_data_1325C[];

extern u8 lbl_2_data_1326C[];

extern u8 lbl_2_data_132DC[];

extern s16 lbl_2_data_3EC8[];

extern s16 lbl_2_data_3ED4[];

extern u8* lbl_2_bss_1A8244;

extern u8* lbl_2_bss_1A8248[];

extern u8 lbl_8036E548[];
extern void fn_2_68E68(void);
extern void fn_2_47FF8(void);
extern void fn_2_47CFC(void);

typedef struct MenuDrawEntry MenuDrawEntry;
struct MenuDrawEntry {
    /*0x00*/ void (*draw)(s32 context, MenuDrawEntry* entry);
    /*0x04*/ s16 _04;
    /*0x06*/ s16 _06;
    /*0x08*/ s16 _08;
    /*0x0A*/ s16 _0A;
    /*0x0C*/ s16 _0C;
    /*0x0E*/ s16 _0E; // layout object index
    /*0x10*/ s16 _10;
    /*0x12*/ s16 _12;
    /*0x14*/ s16 _14;
    /*0x16*/ u8 _16[2];
}; // size: 0x18
extern u8* lbl_2_bss_1A8234[];
extern u8* lbl_2_bss_1A8230[];

// fn_2_53F04, size:0x84
void fn_2_53F04(s32 context) {
    s32 row;
    s32 column;
    for (row = 0; row < 10; row++) {
        for (column = 0; column < 864; column++) {
            MenuDrawEntry* entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8230[0])[row][column];
            if (entry->draw != NULL) {
                entry->draw(context, entry);
            }
        }
    }
}

// fn_2_53F88, size:0x84
void fn_2_53F88(s32 context) {
    s32 row;
    s32 column;
    for (row = 0; row < 70; row++) {
        for (column = 0; column < 864; column++) {
            MenuDrawEntry* entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8234[0])[row][column];
            if (entry->draw != NULL) {
                entry->draw(context, entry);
            }
        }
    }
}

// fn_2_54B38, size:0x74
void fn_2_54B38(void) {
    if (lbl_8036E548[0x307A] == 2) {
        if (lbl_2_bss_1A8248[0][0x44F2] != 4) {
            fn_2_68E68();
        }
        fn_2_47FF8();
        if (lbl_2_bss_1A8248[0][0x44F2] != 4) {
            fn_2_47CFC();
        }
    }
    GXSetZCompLoc(GX_FALSE);
}

// fn_2_4C36C, size:0x58
void fn_2_4C36C(void) {
    lbl_2_bss_1A8248[0][0x4424] = 1;
    lbl_2_bss_1A8248[0][0x4425] = 1;
    lbl_2_bss_1A8248[0][0x441B] = 0;
    {
        u8* entry = lbl_2_bss_1A8244 + lbl_2_bss_1A8248[0][0x441C] * 4;
        entry += lbl_2_bss_1A8248[0][0x4415];
        entry[0xC6] = 1;
    }
    lbl_2_bss_1A8248[0][0x1606] = 1;
}

// fn_2_4C314, size:0x58
void fn_2_4C314(void) {
    u8* menu = lbl_2_bss_1A8244;
    u8 complete = 1;
    s32 i;
    s32 j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 3; j++) {
            if (menu[0xC6 + i * 4 + j] == 0) {
                complete = 0;
            }
        }
    }
    menu[0xF4] = complete;
}


// fn_2_4C3C4, size:0x14
s16 fn_2_4C3C4(s32 index) {
    return lbl_2_data_3ED4[index];
}

// fn_2_4C3D8, size:0x14
s16 fn_2_4C3D8(s32 index) {
    return lbl_2_data_3EC8[index];
}

// fn_2_4E898, size:0x24
void fn_2_4E898(void) {
    fn_80035B50(0x17);
}

// fn_2_4E8BC, size:0x24
void fn_2_4E8BC(void) {
    fn_80035B50(0x18);
}

// fn_2_4E8E0, size:0x24
void fn_2_4E8E0(void) {
    fn_80035B50(0x17);
}

// fn_2_4E904, size:0x24
void fn_2_4E904(void) {
    fn_80035B50(0xC);
}

// fn_2_4E928, size:0x24
void fn_2_4E928(void) {
    fn_80035B50(0x15);
}

// fn_2_4E94C, size:0x24
void fn_2_4E94C(void) {
    fn_80035B50(0x8);
}

// fn_2_4E970, size:0x38
s32 fn_2_4E970(void) {
    return fn_80035838(lbl_2_data_132DC, 0x17) != 0;
}

// fn_2_4EABC, size:0x38
s32 fn_2_4EABC(void) {
    return fn_80035838(lbl_2_data_1326C, 0x17) != 0;
}

// fn_2_4EAF4, size:0x38
s32 fn_2_4EAF4(void) {
    return fn_80035838(lbl_2_data_1325C, 0xC) != 0;
}

// fn_2_4EB2C, size:0x38
s32 fn_2_4EB2C(void) {
    return fn_80035838(lbl_2_data_1324C, 0x15) != 0;
}

// fn_2_4EB64, size:0x38
s32 fn_2_4EB64(void) {
    return fn_80035838(lbl_2_data_1323C, 0x8) != 0;
}

// fn_2_4E858, size:0x20
#pragma dont_inline on
void* fn_2_4E858(void* object) {
    return fn_80034CEC(object);
}
#pragma dont_inline reset

// fn_2_512B8, size:0x8
s32 fn_2_512B8(void) {
    return 0;
}

// fn_2_519F0, size:0x2C
void* fn_2_519F0(void) {
    return fn_800B0A5C_insertQueue((void*)fn_2_89F70, 0x3000);
}

// fn_2_54874, size:0x1C
void fn_2_54874(void) {
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197754) = 0;
}

// fn_2_54848, size:0x2C
void fn_2_54848(void) {
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197754) = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197752) = 10;
}

// fn_2_4E7EC, size:0x38
void fn_2_4E7EC(void) {
    u8* data = lbl_2_bss_1A824C[0];
    fn_800AD054(*(void**)(data + 0x195424), *(void**)(data + 0x195428));
}

// fn_2_4E824, size:0x34
void fn_2_4E824(void) {
    *(u32*)(lbl_2_bss_1A824C[0] + 0x195424) = lbl_803C7898[1];
    *(u32*)(lbl_2_bss_1A824C[0] + 0x195428) = lbl_803C7898[2];
}

// fn_2_54BAC, size:0x4
void fn_2_54BAC(void) {
    return;
}

// fn_2_54844, size:0x4
void fn_2_54844(void) {
    return;
}

// fn_2_5268C, size:0x4
void fn_2_5268C(void) {
    return;
}

// fn_2_51568, size:0x4
void fn_2_51568(void) {
    return;
}

// fn_2_5146C, size:0x4
void fn_2_5146C(void) {
    return;
}

// fn_2_513E4, size:0x4
void fn_2_513E4(void) {
    return;
}

// fn_2_513E0, size:0x4
void fn_2_513E0(void) {
    return;
}

// fn_2_513DC, size:0x4
void fn_2_513DC(void) {
    return;
}

// fn_2_51358, size:0x4
void fn_2_51358(void) {
    return;
}

// fn_2_512B4, size:0x4
void fn_2_512B4(void) {
    return;
}

// fn_2_5118C, size:0x4
void fn_2_5118C(void) {
    return;
}

// fn_2_4E878, size:0x20
#pragma dont_inline on
void fn_2_4E878(void* object, void* data) {
    fn_80034E20(object, data);
}
#pragma dont_inline reset

// fn_2_52648, size:0x44
void fn_2_52648(s32 priority) {
    fn_800B0A5C_insertQueue((void*)fn_2_52690, priority);
    lbl_8034E9A0[0x472B] = g_d_GameSettings._06;
}

// fn_2_4E7A4, size:0x48
void fn_2_4E7A4(void) {
    fn_8003BF54(0, 0, 0, 1, 1, 4, 1, 3, 0);
}

// fn_2_515DC, size:0x60
void fn_2_515DC(u8 mode) {
    memset(lbl_2_bss_1A824C[0] + 0x19542C, 0, 0x1E90);
    lbl_2_bss_1A824C[0][0x1972B8] = mode;
    fn_2_4906C();
}


// fn_2_5156C, size:0x70
u16* fn_2_5156C(s32 index, u16 font) {
    if (font == 0) {
        u8* menu = *(u8**)&lbl_2_bss_1A824C;
        return lbl_80366B18.tables[menu[0x1972B8]]->msgs[index]; // TODO type
    }
    {
        u8* menu = *(u8**)&lbl_2_bss_1A824C;
        return lbl_80366B18.tables[menu[0x1972B8]]->msgs[index]; // TODO type
    }
}

extern u16 lbl_2_bss_9600[];
extern u16 lbl_2_bss_9608[][0x100];

// fn_2_50E5C, size:0xC4
void fn_2_50E5C(s32 channel) {
    s32 i;
    lbl_2_bss_9600[channel] = 0;
    for (i = 0; i < 0x100; i++) {
        lbl_2_bss_9608[channel][i] = 0;
    }
}

extern void fn_2_509A4(void);

// fn_2_50CC0, size:0x80
void fn_2_50CC0(s16 value) {
    s16 zero = 0;
    u8* q;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD6) = value;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCC) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCA) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729E) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729C) = zero;
    q = fn_800B0A5C_insertQueue((void*)fn_2_509A4, 4);
    q[0x28] = 0;
}

extern u8* lbl_803CBBCC[];
extern u8 lbl_8034E978[];
extern u8 lbl_800FEF70[];
extern void fn_80053FE8(void);
extern void fn_2_82DE8(void);
extern void fn_2_8ABFC(void);

// fn_2_52198, size:0xC8
typedef struct { u8 pad[8]; u16 f8; u8 pad2[6]; } Row10;
void fn_2_52198(void) {
    u16 state = *(u16*)(lbl_803CBBCC[0] + 6);
    s32 sel;
    if (state == 5 || state == 0x10) {
        fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0);
        fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
    }
    if (lbl_8034E9A0[0x4756] == 0) {
        sel = 0xB;
    } else {
        sel = 0x10;
        lbl_8034E978[3] = lbl_8034E9A0[0x4711];
    }
    { Row10* r = (Row10*)lbl_800FEF70; lbl_8034E978[0] = sel; lbl_8034E978[9] = lbl_8034E978[8]; lbl_8034E978[8] = r[sel].f8; }
    fn_800B0A5C_insertQueue((void*)fn_2_8ABFC, 0x3000);
}

extern u8 lbl_2_bss_5600[];
extern void* lbl_2_data_1E99C[];
extern s16 fn_2_4EB9C(void);

// fn_2_50BF4, size:0xCC
void fn_2_50BF4(s16 id) {
    s16 zero = 0;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD4) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD2) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD6) = id;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCC) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCA) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729E) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729C) = zero;
    memcpy(lbl_2_bss_5600, lbl_2_data_1E99C[*(s16*)(lbl_2_bss_1A824C[0] + 0x196FD6)], 0x4000);
    *(u8**)(lbl_2_bss_1A824C[0] + 0x196F1C) = lbl_2_bss_5600;
    fn_2_4EB9C();
}

// fn_2_50B0C, size:0xE8
void fn_2_50B0C(s32 id, s32 arg) {
    s16 zero = 0;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD4) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD2) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD6) = (s16)id;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x196F34) = (s16)arg;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x196F30) = (s16)arg;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCC) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCA) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729E) = zero;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729C) = zero;
    memcpy(lbl_2_bss_5600, lbl_2_data_1E99C[*(s16*)(lbl_2_bss_1A824C[0] + 0x196FD6)], 0x4000);
    *(u8**)(lbl_2_bss_1A824C[0] + 0x196F1C) = lbl_2_bss_5600;
    fn_2_4EB9C();
}

extern u16 lbl_2_bss_9604[];
extern u16 lbl_2_bss_9A08[][0x100];

// fn_2_510A8, size:0xE4
void fn_2_510A8(void) {
    s32 i = 0;
    lbl_2_bss_9604[1] = 0;
    lbl_2_bss_9604[0] = 0;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCC) = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCA) = 1;
    for (; i < 0x100; i++) {
        lbl_2_bss_9A08[0][i] = 0;
        lbl_2_bss_9A08[1][i] = 0;
    }
}

extern u8 lbl_2_data_12EA8[];

// fn_2_4E9A8, size:0x114
s32 fn_2_4E9A8(void) {
    u8* d = lbl_2_data_12EA8;
    switch (lbl_2_bss_1A8248[0][0x441C]) {
    case 0:
        if (fn_80035838(d + 0x3D4, 0x18) == 0) {
            return 0;
        }
        break;
    case 1:
        if (fn_80035838(d + 0x3E4, 0x18) == 0) {
            return 0;
        }
        break;
    case 2:
        if (fn_80035838(d + 0x3F4, 0x18) == 0) {
            return 0;
        }
        break;
    case 3:
        if (fn_80035838(d + 0x404, 0x18) == 0) {
            return 0;
        }
        break;
    case 4:
        if (fn_80035838(d + 0x414, 0x18) == 0) {
            return 0;
        }
        break;
    case 5:
        if (fn_80035838(d + 0x424, 0x18) == 0) {
            return 0;
        }
        break;
    }
    return 1;
}

extern InitEntry lbl_2_data_205D4[];
extern void fn_2_5389C(void);

// fn_2_54890, size:0x124
void fn_2_54890(void) {
    u8* q;
    s32 i;
    InitEntry* e;
    lbl_8034E978[0] = 0x5C;
    lbl_8034E978[9] = lbl_8034E978[8];
    lbl_8034E978[8] = ((Row10*)lbl_800FEF70)[0x5C].f8;
    fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0);
    q = fn_800B0A5C_insertQueue((void*)fn_2_5389C, 0);
    *(s16*)(q + 0x1C) = 0;
    *(s16*)(q + 0x1E) = 0;
    for (i = 0; i < 0x2B; i++) {
        u8* p;
        e = &lbl_2_data_205D4[i];
        p = (u8*)lbl_2_bss_1A8234[0] + e->f8 * 0x5100 + e->f4 * 0x18;
        *(s32*)p = e->w0;
        *(s16*)(p + 8) = e->f4;
        *(s16*)(p + 0xA) = e->f6;
        *(s16*)(p + 0xC) = e->f8;
        *(s16*)(p + 0xE) = e->fA;
        *(s16*)(p + 0x10) = e->fC;
    }
    ((u8*)lbl_2_bss_1A8234[0] + 0x160000)[0x2604] = 1;
    ((u8*)lbl_2_bss_1A8234[0] + 0x160000)[0x2605] = 1;
    ((u8*)lbl_2_bss_1A8234[0] + 0x160000)[0x2606] = 1;
    ((u8*)lbl_2_bss_1A8234[0] + 0x160000)[0x2607] = 1;
    ((u8*)lbl_2_bss_1A8234[0] + 0x160000)[0x260A] = 1;
}

// fn_2_5400C, size:0x114
void fn_2_5400C(void) {
    s32 i;
    for (i = 0; i < 10; i++) {
        lbl_2_bss_1A8230[0][i + 0x32A04] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A0E] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A18] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A22] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A2C] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A36] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A40] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A4A] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A54] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A5E] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A68] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A72] = 0;
        lbl_2_bss_1A8230[0][i + 0x32A7C] = 0;
    }
}

// fn_2_51190, size:0x124
void fn_2_51190(s32 a, s32 b) {
    s32 i = 0;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FE0) = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FE4) = 1;
    for (; i < 0xA8; i++) {
        ((s16*)lbl_2_bss_1A824C[0])[i + 0xCB7F4] = 0;
    }
    *(s32*)(lbl_2_bss_1A824C[0] + 0x196FB8) = a;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x196F30) = b;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FCA) = 0;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197298) = 0;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x19729C) = 0;
}

// fn_2_50898, size:0x10C
void fn_2_50898(s32 a) {
    s32 i = 0;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x196FB8) = a;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FE0) = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FE4) = 1;
    for (; i < 0xA8; i++) {
        ((s16*)lbl_2_bss_1A824C[0])[i + 0xCB7F4] = 0;
    }
    *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD2) = 1;
    *(s32*)(lbl_2_bss_1A824C[0] + 0x196F30) = 1;
    *(s16*)(lbl_2_bss_1A824C[0] + 0x197298) = 0;
}

// fn_2_54120, size:0x114
void fn_2_54120(void) {
    s32 i;
    for (i = 0; i < 0x46; i++) {
        lbl_2_bss_1A8234[0][i + 0x162604] = 0;
        lbl_2_bss_1A8234[0][i + 0x16264A] = 0;
        lbl_2_bss_1A8234[0][i + 0x162690] = 0;
        lbl_2_bss_1A8234[0][i + 0x1626D6] = 0;
        lbl_2_bss_1A8234[0][i + 0x16271C] = 0;
        lbl_2_bss_1A8234[0][i + 0x162762] = 0;
        lbl_2_bss_1A8234[0][i + 0x1627A8] = 0;
        lbl_2_bss_1A8234[0][i + 0x1627EE] = 0;
        lbl_2_bss_1A8234[0][i + 0x162834] = 0;
        lbl_2_bss_1A8234[0][i + 0x16287A] = 0;
        lbl_2_bss_1A8234[0][i + 0x1628C0] = 0;
        lbl_2_bss_1A8234[0][i + 0x162906] = 0;
        lbl_2_bss_1A8234[0][i + 0x16294C] = 0;
    }
}

// fn_2_54234, size:0x120
void fn_2_54234(InitEntry* entries, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        u8* p = lbl_2_bss_1A8230[0] + entries[i].f8 * 0x5100 + entries[i].f4 * 0x18;
        *(s32*)p = entries[i].w0;
        *(s16*)(p + 8) = entries[i].f4;
        *(s16*)(p + 0xA) = entries[i].f6;
        *(s16*)(p + 0xC) = entries[i].f8;
        *(s16*)(p + 0xE) = entries[i].fA;
        *(s16*)(p + 0x10) = entries[i].fC;
    }
}

// fn_2_54354, size:0x120
void fn_2_54354(InitEntry* entries, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        u8* p = lbl_2_bss_1A8234[0] + entries[i].f8 * 0x5100 + entries[i].f4 * 0x18;
        *(s32*)p = entries[i].w0;
        *(s16*)(p + 8) = entries[i].f4;
        *(s16*)(p + 0xA) = entries[i].f6;
        *(s16*)(p + 0xC) = entries[i].f8;
        *(s16*)(p + 0xE) = entries[i].fA;
        *(s16*)(p + 0x10) = entries[i].fC;
    }
}


// fn_2_53CEC, size:0x10C
void fn_2_53CEC(u8* menu) {
    MenuDrawEntry* entry;
    s32 row;
    s32 column;
    for (row = 0; row < 10; row++) {
        for (column = 0; column < 864; column++) {
            entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8230[0])[row][column];
            if (entry->draw != NULL) {
                lbl_80371C30[*(u16*)(menu + 0x14) + entry->_0E].obj->_68 = 0;
                lbl_80371C30[*(u16*)(menu + 0x14) + entry->_0E].obj->flags &= ~2;
            }
        }
    }
}

// fn_2_53DF8, size:0x10C
void fn_2_53DF8(u8* menu) {
    MenuDrawEntry* entry;
    s32 row;
    s32 column;
    for (row = 0; row < 70; row++) {
        for (column = 0; column < 864; column++) {
            entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8234[0])[row][column];
            if (entry->draw != NULL) {
                lbl_80371C30[*(u16*)(menu + 0x14) + entry->_0E].obj->_68 = 0;
                lbl_80371C30[*(u16*)(menu + 0x14) + entry->_0E].obj->flags &= ~2;
            }
        }
    }
}

extern void fn_2_4B2D0(void);
extern void starMissionRelated2(void);

// fn_2_4B1AC, size:0x124
void fn_2_4B1AC(void) {
    s32 mode; s16 old; u8* m; s32 step;
    fn_2_4B2D0();
    mode = lbl_2_bss_1A824C[0][0x197843];
    if ((s8)mode == 0) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197778) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = 0;
    } else if ((s8)mode == 1) {
        m = *(u8**)&lbl_2_bss_1A8248;
        old = *(s16*)(m + 0x43BC);
        if (old == 1) {
            step = -1;
        } else {
            step = -old / 2;
        }
        *(s16*)(m + 0x43BE) = old;
        *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) + step;
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) > 0x3E7) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0x3E7;
        }
        if (*(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) < 0) {
            *(s16*)(lbl_2_bss_1A8248[0] + 0x43BC) = 0;
        }
        *(s16*)(lbl_2_bss_1A824C[0] + 0x19777A) = step;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = step;
    } else if ((s8)mode == 2) {
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197796) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197798) = 0;
    }
    starMissionRelated2();
}

typedef struct {
    u16 w0;
    u16 state;
    u8 pad4;
    u8 b5;
    u8 b6;
    u8 options[6]; // 0x7: which of the 6 menu options are selectable
    u8 bD;
    u8 bE;
    s8 bF;
    s8 b10;
    u8 pad11;
    u16 w12;
    u8 b14;
    u8 b15;
    u8 b16;
    u8 b17;
    u8 pad18;
    u8 b19;
    u8 b1A;
    u8 pad1B;
    s32 w1C;
    u8 pad20;
    u8 b21;
    u8 b22;
    u8 pad23;
} Bss33FBCC;
extern Bss33FBCC lbl_2_bss_33FBCC;
extern u16 lbl_2_bss_9E08;
extern void fn_2_89F70(void);
extern void fn_2_51890(void);
extern void fn_2_51A1C(void);
extern void fn_2_51C58(void);

// fn_2_520A4, size:0xF4
void fn_2_520A4(void) {
    switch (lbl_2_bss_33FBCC.state) {
    case 0:
        fn_2_51890();
        fn_800B0A5C_insertQueue((void*)fn_2_89F70, 0x3000);
        lbl_2_bss_33FBCC.b22 = 0x51;
        lbl_2_bss_33FBCC.state = 1;
        break;
    case 1:
        if (lbl_2_bss_33FBCC.b22 != 0x51) {
            fn_2_51C58();
        }
        break;
    case 2:
        lbl_2_bss_33FBCC.b22 = 0x52;
        lbl_2_bss_33FBCC.bE = 1;
        lbl_2_bss_33FBCC.state = 0;
        lbl_2_bss_9E08 = 0xA;
        break;
    case 3:
        lbl_2_bss_33FBCC.b22 = 0x52;
        lbl_2_bss_9E08 = 5;
        lbl_2_bss_33FBCC.bE = 1;
        lbl_2_bss_33FBCC.state = 0;
        break;
    case 4:
        fn_2_51A1C();
        break;
    }
}

typedef struct {
    u8 pad[0x50];
    s32 w50;
    u32 w54;
} BssF410;
extern BssF410 lbl_2_bss_F410;
extern u8 lbl_80361B20[];
typedef struct {
    u8 b[0x4508];
} MenuSlot;
extern MenuSlot lbl_80354768[];

// fn_2_51890, size:0x160
void fn_2_51890(void) {
    if ((s8)lbl_80354768[lbl_80361B20[0xF6]].b[0x1606] != 0) {
        if (lbl_80354768[lbl_8034E9A0[0x4754]].b[0x441B] != 0) {
            lbl_2_bss_F410.w54 = 1;
            lbl_2_bss_33FBCC.b5 = 3;
            lbl_2_bss_33FBCC.options[0] = 0;
            lbl_2_bss_33FBCC.options[1] = 1;
            lbl_2_bss_33FBCC.options[2] = 1;
            lbl_2_bss_33FBCC.options[3] = 1;
            lbl_2_bss_33FBCC.options[4] = 1;
            lbl_2_bss_33FBCC.options[5] = 1;
        } else {
            lbl_2_bss_F410.w54 = 2;
            lbl_2_bss_33FBCC.b5 = 2;
            lbl_2_bss_33FBCC.options[0] = 0;
            lbl_2_bss_33FBCC.options[1] = 0;
            lbl_2_bss_33FBCC.options[2] = 1;
            lbl_2_bss_33FBCC.options[3] = 1;
            lbl_2_bss_33FBCC.options[4] = 1;
            lbl_2_bss_33FBCC.options[5] = 1;
        }
    } else {
        if (lbl_80354768[lbl_8034E9A0[0x4754]].b[0x441B] != 0) {
            lbl_2_bss_F410.w54 = 1;
            lbl_2_bss_33FBCC.b5 = 1;
            lbl_2_bss_33FBCC.options[0] = 0;
            lbl_2_bss_33FBCC.options[1] = 1;
            lbl_2_bss_33FBCC.options[2] = 0;
            lbl_2_bss_33FBCC.options[3] = 1;
            lbl_2_bss_33FBCC.options[4] = 1;
            lbl_2_bss_33FBCC.options[5] = 1;
        } else {
            lbl_2_bss_F410.w54 = 0;
            lbl_2_bss_33FBCC.b5 = 0;
            lbl_2_bss_33FBCC.options[0] = 1;
            lbl_2_bss_33FBCC.options[1] = 0;
            lbl_2_bss_33FBCC.options[2] = 0;
            lbl_2_bss_33FBCC.options[3] = 0;
            lbl_2_bss_33FBCC.options[4] = 0;
            lbl_2_bss_33FBCC.options[5] = 1;
        }
    }
}

extern u16 lbl_2_data_1F3B0[];
extern s32 lbl_2_data_1F3E0[];
extern s32 lbl_2_data_1F3E8[];

static u16 s_dst[2][0x100];
static u16 s_src[2][0x100];
static u16 s_cnt1[2];
static u16 s_cnt0[2];
static u8 s_buf[0x4000];
static s32 s_c[2];
static s32 s_b[2];
static s32 s_a[2];

// fn_2_5135C, size:0x80
void fn_2_5135C(u8* obj, s32 i) {
    if (*(u16*)(obj + 0x10) % lbl_2_data_1F3B0[i] == 1) {
        s_b[i] = lbl_2_data_1F3E0[i];
        s_a[i] = lbl_2_data_1F3E8[i];
        s_c[i] = ((s32*)(lbl_2_bss_1A824C[0] + 0x1954AC))[i];
    }
}

// fn_2_50D40, size:0x74
void fn_2_50D40(s32 ch) {
    u16 v;
    u16* src;
    if (s_cnt1[ch] != 0) {
        s_cnt1[ch]--;
    }
    src = s_src[ch];
    do {
        s32 k = s_cnt1[ch];
        v = *src++;
        s_cnt1[ch]++;
        s_dst[ch][k] = v;
        if (s_cnt1[ch] == 0x100) {
            return;
        }
    } while (!((v & 0x4000) && !(v & 0x3FFF)));
}

// fn_2_50DB4, size:0xA8
void fn_2_50DB4(s32 ch, s32 idx, u16* src) {
    u8* menu = *(u8**)&lbl_2_bss_1A824C;
    MsgTable* table = lbl_80366B18.tables[menu[0x1972B8]];
    u16 v;
    u16** q = table->msgs;
    if (lbl_2_bss_9600[ch] != 0) {
        lbl_2_bss_9600[ch]--;
    }
    src = (idx == -1) ? src : q[idx];
    do {
        s32 k = lbl_2_bss_9600[ch];
        v = *src++;
        lbl_2_bss_9600[ch]++;
        lbl_2_bss_9608[ch][k] = v;
        if (lbl_2_bss_9600[ch] == 0x100) {
            return;
        }
    } while (!((v & 0x4000) && !(v & 0x3FFF)));
}

// fn_2_50F20, size:0xA8
void fn_2_50F20(s32 ch, s32 idx, u16* src) {
    u8* menu = *(u8**)&lbl_2_bss_1A824C;
    MsgTable* table = lbl_80366B18.tables[menu[0x1972B8]];
    u16 v;
    u16** q = table->msgs;
    if (lbl_2_bss_9604[ch] != 0) {
        lbl_2_bss_9604[ch]--;
    }
    src = (idx == -1) ? src : q[idx];
    do {
        s32 k = lbl_2_bss_9604[ch];
        v = *src++;
        lbl_2_bss_9604[ch]++;
        lbl_2_bss_9A08[ch][k] = v;
        if (lbl_2_bss_9604[ch] == 0x100) {
            return;
        }
    } while (!((v & 0x4000) && !(v & 0x3FFF)));
}

// fn_2_50FC8, size:0xE0
void fn_2_50FC8(s32 ch) {
    s32 i = 0;
    lbl_2_bss_9604[ch] = 0;
    ((s16*)(lbl_2_bss_1A824C[0] + 0x196FCA))[ch] = 1;
    for (; i < 0x100; i++) {
        lbl_2_bss_9A08[ch][i] = 0;
    }
}

// fn_2_53BC8
s16 fn_2_53BC8(u8* obj) {
    s16 off = *(s16*)(obj + 0xC);
    s32 r = -1;
    if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x2604] != 0) {
        r = 0;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x264a] != 0) {
        r = 2;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x2834] != 0) {
        r = 5;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x2690] != 0) {
        r = 23;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x26d6] != 0) {
        r = 8;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x271c] != 0) {
        r = 11;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x2762] != 0) {
        r = 14;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x27a8] != 0) {
        r = 17;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x27ee] != 0) {
        r = 20;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x287a] != 0) {
        r = 24;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x28c0] != 0) {
        r = 27;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x2906] != 0) {
        r = 30;
    }
    else if ((lbl_2_bss_1A8234[0] + 0x160000)[off + 0x294c] != 0) {
        r = 33;
    }
    return r;
}

// fn_2_53AA4, size:0x124
s16 fn_2_53AA4(u8* obj) {
    s16 off = *(s16*)(obj + 0xC);
    s32 r = -1;
    if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a04] != 0) {
        r = 0;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a0e] != 0) {
        r = 2;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a54] != 0) {
        r = 5;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a18] != 0) {
        r = 23;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a22] != 0) {
        r = 8;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a2c] != 0) {
        r = 11;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a36] != 0) {
        r = 14;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a40] != 0) {
        r = 17;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a4a] != 0) {
        r = 20;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a5e] != 0) {
        r = 24;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a68] != 0) {
        r = 27;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a72] != 0) {
        r = 30;
    }
    else if ((lbl_2_bss_1A8230[0] + 0x30000)[off + 0x2a7c] != 0) {
        r = 33;
    }
    return r;
}

extern s16 lbl_2_data_373C[];

// fn_2_4C6A8, size:0x174
void fn_2_4C6A8(void) {
    s32 i;
    GameInitVariables* g = &g_d_GameSettings;
    s8 idx;
    i = 0;
    for (; i < 0x14; i++) {
        g->challengeCaptainStarBought[i] = 0;
    }
    for (i = 0; i < 0x14; i++) {
        if (lbl_2_data_373C[i] == 0 && (s8)lbl_2_bss_1A8248[0][0x43C2 + i] != 0) {
            g->challengeCaptainStarBought[i] = 1;
        }
    }
    idx = lbl_2_bss_1A8248[0][0x444B];
    if (idx != -1) {
        g->challengeCaptainStarBought[idx] = 1;
    }
}

// fn_2_4C81C, size:0x1A8
void fn_2_4C81C(void) {
    g_d_GameSettings.GameModeSelected = 6;
    g_d_GameSettings.exhibitionMatchInd = 0;
    g_d_GameSettings._36 = lbl_2_bss_1A8248[0][0x441D];
    g_d_GameSettings.bJMatchInd = 0;
    g_d_GameSettings.home_AwaySetting = 0;
    g_d_GameSettings.challengeDifficulty = lbl_2_bss_1A8248[0][0x4415];
    g_d_GameSettings.bJMatchRelated = lbl_2_bss_1A8248[0][0x4418];
    fn_2_4C6A8();
}

// fn_2_4CB94, size:0x19C
void fn_2_4CB94(void) {
    g_d_GameSettings.GameModeSelected = 6;
    g_d_GameSettings.exhibitionMatchInd = 0;
    g_d_GameSettings._36 = lbl_2_bss_1A8248[0][0x441D];
    g_d_GameSettings.bJMatchInd = 1;
    g_d_GameSettings.bJMatchRelated = lbl_2_bss_1A8248[0][0x4418];
    fn_2_4C6A8();
}

extern u8 lbl_2_data_2E64[];

// fn_2_4C9C4, size:0x1D0
void fn_2_4C9C4(void) {
    u8* d = lbl_2_bss_1A8248[0];
    g_d_GameSettings.GameModeSelected = 7;
    g_d_GameSettings.exhibitionMatchInd = 0;
    g_d_GameSettings._33 = lbl_2_data_2E64[d[0x4420]];
    g_d_GameSettings._35 = 0;
    g_d_GameSettings._36 = d[0x441D];
    g_d_GameSettings.challengeDifficulty = d[0x4415];
    g_d_GameSettings.bJMatchRelated = d[0x4418];
    g_d_GameSettings._3A = (*(volatile u8**)&lbl_2_bss_1A824C)[0x1978F1];
    fn_2_4C6A8();
}

// fn_2_4CD30, size:0x1B0
void fn_2_4CD30(void) {
    g_d_GameSettings.GameModeSelected = 7;
    g_d_GameSettings.exhibitionMatchInd = 0;
    g_d_GameSettings._33 = 6;
    g_d_GameSettings._35 = 0;
    g_d_GameSettings._36 = lbl_2_bss_1A8248[0][0x441D];
    g_d_GameSettings.challengeDifficulty = lbl_2_bss_1A8248[0][0x4415];
    g_d_GameSettings.bJMatchInd = 1;
    g_d_GameSettings.bJMatchRelated = lbl_2_bss_1A8248[0][0x4418];
    fn_2_4C6A8();
}

extern int rand();

extern u8 lbl_2_data_3CC0[];

// fn_2_4CEE0, size:0x2B4
void fn_2_4CEE0(void) {
    GameInitVariables* g = &g_d_GameSettings;
    u8* m;
    u32 v;
    g->exhibitionMatchInd = 0;
    g->bJMatchInd = 1;
    g_d_GameSettings.home_AwaySetting = rand() % 2;
    g_d_GameSettings.bJMatchRelated = lbl_2_bss_1A8248[0][0x4418];
    g_d_GameSettings.challengeDifficulty = lbl_2_bss_1A8248[0][0x4415];
    fn_2_4C6A8();
    m = lbl_2_bss_1A8248[0];
    v = m[*(s16*)(m + 0x16C2) * 10 + 0x40F0];
    if (v >= 6) {
        if (*(s16*)(m + 0x16C0) == 3) {
            if (v == 0) {
                g->StadiumID = 0;
                g->miniGameStadiumIndicator = 0;
            } else if (v == 1) {
                g->StadiumID = 1;
                g->miniGameStadiumIndicator = 0;
            } else {
                g->StadiumID = 4;
                g->miniGameStadiumIndicator = 0;
            }
        } else if (v == 2) {
            g->StadiumID = 2;
            g->miniGameStadiumIndicator = 0;
        } else if (v == 3) {
            g->StadiumID = 3;
            g->miniGameStadiumIndicator = 0;
        } else {
            g->StadiumID = 5;
            g->miniGameStadiumIndicator = 0;
        }
    } else {
        g->miniGameStadiumIndicator = 0;
        g->StadiumID = lbl_2_data_3CC0[v];
    }
}

// fn_2_4D194, size:0x1E4
void fn_2_4D194(void) {
    GameInitVariables* g = &g_d_GameSettings;
    u8* d = *(u8**)&lbl_2_bss_1A8248;
    u8 s;
    g->exhibitionMatchInd = 0;
    g->bJMatchInd = 0;
    g->miniGameStadiumIndicator = 0;
    g->challengeDifficulty = d[0x4415];
    if ((s32)d[0x44EF] == 1) {
        g->home_AwaySetting = 0;
        g->StadiumID = 1;
    } else {
        s = lbl_2_data_3CC0[d[0x441E]];
        g->home_AwaySetting = 0;
        g->StadiumID = s;
    }
    g->bJMatchRelated = (*(volatile u8**)&lbl_2_bss_1A8248)[0x4418];
    fn_2_4C6A8();
}

extern u8* lbl_803CC1B8[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_2_data_1FF84[];
extern u8 lbl_2_data_1FF94[];
extern void fn_800216F8(s32, void*);
extern void fn_800627C4(void);
extern void fn_2_8E8A4(void);

// fn_2_549B4, size:0x184
void fn_2_549B4(void) {
    u8* o = lbl_803CC1B8[0];
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        lbl_80366B18.tables[2] = (MsgTable*)ARAMTransfer(lbl_2_data_1FF94, 0, 1, 0);
        o[0x28] = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(lbl_80366B18.tables[2]);
            o[0x28] = 2;
        }
        break;
    case 2:
        if (fn_80035838(lbl_2_data_1FF84, 10) != 0) {
            o[0x28] = 3;
        }
        break;
    case 3:
        *(s16*)(o + 0x10) = 0;
        fn_800216F8(4, fn_800627C4);
        o[0x28] = 4;
        break;
    case 4:
        if (*(s16*)(o + 0x10) != 0) {
            *(s16*)(o + 0x10) = 0;
            o[0x28] = 5;
        }
        break;
    case 5:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x197746) = 1;
        q = fn_800B0A5C_insertQueue(fn_2_8E8A4, 2);
        q[0x28] = 0;
        *(s16*)(q + 0x16) = 0xC;
        *(s16*)(o + 0x10) = 0;
        o[0x28] = 6;
        break;
    case 6:
        if (*(s16*)(o + 0x10) == 1) {
            q = *(u8**)(o + 0xC);
            *(s16*)(q + 0x10) = 1;
            fn_800B0A14_removeQueue(q);
            o[0x28] = 0;
        }
        break;
    }
}

// fn_2_509A4, size:0x168
void fn_2_509A4(void) {
    u8* o = lbl_803CC1B8[0];
    switch ((s8)o[0x28]) {
    case 0:
        *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD4) = 0;
        *(s16*)(lbl_2_bss_1A824C[0] + 0x196FD2) = 0;
        memcpy(lbl_2_bss_5600, lbl_2_data_1E99C[*(s16*)(lbl_2_bss_1A824C[0] + 0x196FD6)], 0x4000);
        *(u8**)(lbl_2_bss_1A824C[0] + 0x196F1C) = lbl_2_bss_5600;
        o[0x28]++;
    case 1:
        {
            s16 r = fn_2_4EB9C();
            if (r != 0) {
                switch (r) {
                case 1: {
                    u8* q = *(u8**)(*(u8**)&lbl_803CC1B8[0] + 0xC);
                    *(s16*)(q + 0x10) = 1;
                    fn_800B0A14_removeQueue(q);
                    break;
                }
                default: {
                    u8* q = *(u8**)(*(u8**)&lbl_803CC1B8[0] + 0xC);
                    *(s16*)(q + 0x10) = 1;
                    fn_800B0A14_removeQueue(q);
                    break;
                }
                }
                o[0x28] = 0;
            }
        }
        break;
    case 2:
        break;
    }
    if (*(u8*)(*(u8**)&lbl_2_bss_1A824C + 0x19783F) == 1) {
        u8* q = *(u8**)(*(u8**)&lbl_803CC1B8[0] + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
    }
}

extern u8 lbl_2_data_1F884[];
extern u8 lbl_2_data_1F894[];
extern s16 lbl_800E877C[];
extern u8 lbl_803C50E8[];
extern void fn_80042D38(u16 scene);

// fn_2_53408, size:0x1A8
void fn_2_53408(void) {
    switch (lbl_2_bss_33FBCC.w0) {
    case 0:
        if (fn_80035838(lbl_2_data_1F884, 8) != 0) {
            lbl_2_bss_33FBCC.bD = 0;
            if (*(u16*)(lbl_803CBBCC[0] + 6) == 0x10) {
                lbl_2_bss_33FBCC.w0 = 1;
                lbl_8034E9A0[0x4756] = 1;
            } else {
                lbl_2_bss_33FBCC.w0 = 2;
            }
            {
                s16* s = lbl_800E877C;
                if (s[0x18] == 0xA && lbl_803C50E8[0x47] != 0) {
                    s16* m2;
                    changeScene(6, 6);
                    changeScene(3, 6);
                    fn_80035B50(8);
                    m2 = lbl_800E877C;
                    s[0x18] = 9;
                    m2[0x19] = 0;
                    fn_80042D38(5);
                    lbl_2_bss_33FBCC.w0 = 0;
                    *(s32*)((u8*)&lbl_2_bss_F410 + 0x50) = 0;
                    lbl_2_bss_9E08 = 0;
                    lbl_803C50E8[0x52] = 0;
                }
            }
        }
        break;
    case 1:
        if (fn_80035838(lbl_2_data_1F894, 6) != 0) {
            lbl_2_bss_33FBCC.w0 = 2;
        }
        break;
    case 2:
        fn_800B0A5C_insertQueue((void*)fn_2_52690, 0x2000);
        lbl_8034E9A0[0x472B] = g_d_GameSettings._06;
        lbl_2_bss_33FBCC.w0 = lbl_2_bss_33FBCC.w0 + 1;
        break;
    case 3:
        break;
    }
}

extern u8 lbl_2_data_1FFB4[];
extern void fn_8000FE54(void);

// fn_2_5389C, size:0x208
void fn_2_5389C(void) {
    u8* o = *(u8**)&lbl_803CC1B8;
    s32 i;
    switch (*(u16*)(o + 0x1C)) {
    case 0:
        fn_2_4E878(o, lbl_2_data_1FFB4);
        *(u16*)(o + 0x1C) = 1;
        *(u16*)(o + 0x18) = 0;
        break;
    case 1:
        break;
    }
    fn_2_53F88((s32)o);
    for (i = 0; i < 0x46; i++) {
        lbl_2_bss_1A8234[0][0x162604 + i] = 0;
        lbl_2_bss_1A8234[0][0x16264A + i] = 0;
        lbl_2_bss_1A8234[0][0x162690 + i] = 0;
        lbl_2_bss_1A8234[0][0x1626D6 + i] = 0;
        lbl_2_bss_1A8234[0][0x16271C + i] = 0;
        lbl_2_bss_1A8234[0][0x162762 + i] = 0;
        lbl_2_bss_1A8234[0][0x1627A8 + i] = 0;
        lbl_2_bss_1A8234[0][0x1627EE + i] = 0;
        lbl_2_bss_1A8234[0][0x162834 + i] = 0;
        lbl_2_bss_1A8234[0][0x16287A + i] = 0;
        lbl_2_bss_1A8234[0][0x1628C0 + i] = 0;
        lbl_2_bss_1A8234[0][0x162906 + i] = 0;
        lbl_2_bss_1A8234[0][0x16294C + i] = 0;
    }
    if (lbl_2_bss_1A8234[0][0x162992] != 0) {
        fn_8000F8F4((LayoutGroup*)o);
        fn_8000FE54();
        fn_800B0A14_removeQueue(fn_2_4E858(o));
        *(u16*)(o + 0x1C) = 0;
        *(u16*)(o + 0x1E) = 0;
        lbl_2_bss_1A8234[0][0x162992] = 0;
    }
}

extern u8 lbl_2_bss_33FB4C[];
extern void fn_8004A34C(void*, s32, s32, s32, s32);
extern s32 fn_8004CA6C(u16);
extern void fn_8004CC2C(void);
extern void fn_2_460EC(u8);

// fn_2_51A1C, size:0x23C
void fn_2_51A1C(void) {
    switch (lbl_2_bss_33FBCC.w12) {
    case 0:
        if (lbl_2_bss_33FBCC.b14 == 0) {
            fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x2E, 0, 0);
        } else {
            fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x2F, 0, 0);
        }
        lbl_2_bss_33FBCC.w12 = 1;
        break;
    case 1:
        lbl_2_bss_33FBCC.w12 = 2;
        break;
    case 2:
        switch (fn_8004CA6C(*(u16*)(lbl_8034E9A0 + 0x472E))) {
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            if (++lbl_2_bss_33FBCC.b14 == 2) {
                fn_2_460EC(lbl_8034E9A0[0x4754]);
                fn_8003BF54(0, 0, 0, 0, 1, 5, 3, lbl_8034E9A0[0x4754], 3);
                lbl_803C50E8[0x52] = 4;
                *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
                lbl_2_bss_33FBCC.b14 = 0;
                lbl_2_bss_33FBCC.w12 = 3;
            } else {
                lbl_2_bss_33FBCC.w12 = 0;
            }
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            lbl_2_bss_33FBCC.b22 = 0x52;
            lbl_2_bss_33FBCC.bE = 1;
            lbl_2_bss_33FBCC.bF = -1;
            lbl_2_bss_33FBCC.w12 = 0;
            lbl_2_bss_33FBCC.b14 = 0;
            lbl_2_bss_9E08 = 5;
            break;
        case 0:
            break;
        }
        break;
    case 3:
        if (*(s16*)(lbl_803CC1B8[0] + 0x10) != 0) {
            lbl_2_bss_33FBCC.b17 = 0x50;
            lbl_2_bss_33FBCC.b22 = 0x52;
            lbl_2_bss_33FBCC.bE = 1;
            lbl_2_bss_33FBCC.bF = -1;
            lbl_2_bss_33FBCC.w12 = 0;
            lbl_2_bss_33FBCC.b14 = 0;
            lbl_2_bss_9E08 = 5;
        }
        break;
    }
}

typedef struct {
    u8 a[0x1E];
    u8 pad1E[2];
    u32 w20;
    s16 h24;
    u8 b26;
    u8 b27;
    u8 c28[2];
    u8 c2A[2];
    u8 b2C;
    u8 b2D;
    u8 b2E;
    u8 b2F;
    u8 b30;
    u8 b31;
    u8 b32;
    u8 b33;
    u8 b34;
    u8 c35[2];
    u8 c37[4];
    u8 chem[0x36];
    u8 b71;
    u8 pad72[2];
    u16 us[21];
} MCharStats;

extern MCharStats inMemRoster[2][9];
extern u8 starMissionCompletionTracker[];
extern u8 lbl_803C6724[];
extern u8 lbl_80354720[];
extern void fn_800678CC(s32);

// fn_2_5163C, size:0x254
void fn_2_5163C(void) {
    MCharStats* src;
    s32 i;
    s8 sel;
    *(u32*)(lbl_8034E9A0 + 0x46E0) = starMissionCompletionTracker[0x441D];
    for (i = 0; i < 9; i++) {
        lbl_803C6724[i + 2] = *(s16*)(starMissionCompletionTracker + i * 6 + 0x40B8);
        sel = *(s8*)(lbl_803C6724 + i + 2);
        src = (MCharStats*)(lbl_8034E9A0 + sel / 9 * 0x5A0 + sel % 9 * 0xA0);
        memcpy(inMemRoster[0][i].a, src->a, 0x1E);
        inMemRoster[0][i].h24 = src->h24;
        inMemRoster[0][i].b26 = src->b26;
        inMemRoster[0][i].b27 = src->b27;
        memcpy(inMemRoster[0][i].c28, src->c28, 2);
        memcpy(inMemRoster[0][i].c2A, src->c2A, 2);
        inMemRoster[0][i].b2C = src->b2C;
        inMemRoster[0][i].b2D = src->b2D;
        inMemRoster[0][i].b2E = src->b2E;
        inMemRoster[0][i].b2F = src->b2F;
        inMemRoster[0][i].b30 = src->b30;
        inMemRoster[0][i].b31 = src->b31;
        inMemRoster[0][i].b32 = src->b32;
        inMemRoster[0][i].b33 = src->b33;
        inMemRoster[0][i].b34 = src->b34;
        memcpy(inMemRoster[0][i].c35, src->c35, 2);
        inMemRoster[0][i].w20 = src->w20;
        memcpy(inMemRoster[0][i].c37, src->c37, 4);
        memcpy(inMemRoster[0][i].chem, src->chem, 0x36);
        inMemRoster[0][i].b71 = src->b71;
        inMemRoster[0][i].us[0] = src->us[0];
        inMemRoster[0][i].us[1] = src->us[1];
        inMemRoster[0][i].us[2] = src->us[2];
        inMemRoster[0][i].us[3] = src->us[3];
        inMemRoster[0][i].us[4] = src->us[4];
        inMemRoster[0][i].us[5] = src->us[5];
        inMemRoster[0][i].us[6] = src->us[6];
        inMemRoster[0][i].us[7] = src->us[7];
        inMemRoster[0][i].us[8] = src->us[8];
        inMemRoster[0][i].us[9] = src->us[9];
        inMemRoster[0][i].us[10] = src->us[10];
        inMemRoster[0][i].us[11] = src->us[11];
        inMemRoster[0][i].us[12] = src->us[12];
        inMemRoster[0][i].us[13] = src->us[13];
        inMemRoster[0][i].us[14] = src->us[14];
        inMemRoster[0][i].us[15] = src->us[15];
        inMemRoster[0][i].us[16] = src->us[16];
        inMemRoster[0][i].us[17] = src->us[17];
        inMemRoster[0][i].us[18] = src->us[18];
        inMemRoster[0][i].us[19] = src->us[19];
        inMemRoster[0][i].us[20] = src->us[20];
        lbl_80354720[i * 4 + 1] = i;
        lbl_80354720[i * 4] = i;
        lbl_803C6724[i + 0x14] = starMissionCompletionTracker[i * 6 + 0x40BB];
        lbl_80354720[i * 4 + 2] = starMissionCompletionTracker[i * 6 + 0x40BB];
    }
    fn_800678CC(0);
}

extern u8 lbl_80361C18[];

// fn_2_4C3EC, size:0x2BC
void fn_2_4C3EC(void) {
    s32 flags[6];
    s32* fp;
    s32 j;
    u8* t;
    s32 k;
    s32 i;
    t = lbl_80361C18;
    flags[0] = 0;
    flags[1] = 0;
    flags[2] = 0;
    flags[3] = 0;
    flags[4] = 0;
    flags[5] = 0;
    fp = flags;
    for (i = 0; i < 0x36; i++) {
        t[i] = 0;
    }
    for (k = 0; k < 6; k++) {
        if (*fp != 0) {
            for (j = 0; j < 9; j++) {
                t[lbl_8034E9A0[k * 0x48 + 0x4380 + j]] = 1;
            }
        }
        fp++;
    }
    for (i = 0; i < 0x36; i++) {
        u8* e = lbl_2_bss_1A8248[0] + i * 0x34;
        if ((s8)e[5] <= 3) {
            if (*(s8*)(e + 0x31) == 1) {
                t[i] = 1;
            }
        }
    }
}

extern u16 lbl_2_data_1F3A0[];

// Menu text control codes: a u16 with bit 0x4000 set is a control code
// (low 14 bits); otherwise bit 0x8000 marks a full-width glyph.
#define MENU_TEXT_CTRL 0x4000
#define MENU_TEXT_WIDE 0x8000

// Text line state inside the big menu work buffer (lbl_2_bss_1A824C[0]).
typedef struct MenuTextState {
    /*0x000000*/ u8 _000000[0x1954AC];
    /*0x1954AC*/ u16* lines[(0x197294 - 0x1954AC) / 4];
    /*0x197294*/ s16 lineCount[1];
} MenuTextState;

// fn_2_512C0, size:0x98
// NONMATCHING 95%: original has a second dead `b` after the switch dispatch and no trailing `blr` after the loop (see docs/patterns/inlining.md "No trailing epilogue")
#if NONMATCHING
void fn_2_512C0(s32 index) {
    u16* str = (*(MenuTextState**)&lbl_2_bss_1A824C)->lines[index];
    u16 c;
    while (1) {
        c = *str++;
        if (c & MENU_TEXT_CTRL) {
            switch (c & 0x3FFF) {
            case 0:
                return;
            case 4:
            default:
                break;
            }
            (*(MenuTextState**)&lbl_2_bss_1A824C)->lineCount[index]++;
        } else {
            (*(MenuTextState**)&lbl_2_bss_1A824C)->lineCount[index]++;
        }
    }
}
#endif

// fn_2_513E8, size:0x84
// NONMATCHING 97%: only an extra dead trailing `blr` after the infinite loop (see docs/patterns/inlining.md "No trailing epilogue")
#if NONMATCHING
s32 fn_2_513E8(u16* str, u16 font) {
    u16 c;
    u16 width = 0;
    while (1) {
        c = *str++;
        if (c & MENU_TEXT_CTRL) {
            switch (c & 0x3FFF) {
            case 2:
                width += (u32)lbl_2_data_1F3A0[font] >> 1;
                break;
            case 3:
                width += lbl_2_data_1F3A0[font];
                break;
            default:
                return width;
            }
        } else {
            width += (c & MENU_TEXT_WIDE) ? lbl_2_data_1F3A0[font] : (u16)((u32)lbl_2_data_1F3A0[font] >> 1);
        }
    }
}
#endif

// fn_2_51470, size:0xF8
// NONMATCHING 79%: inlined fn_2_5156C/fn_2_513E8 schedule the table lookups differently, plus the dead trailing `blr`
#if NONMATCHING
s32 fn_2_51470(s32 index, u16 font) {
    return fn_2_513E8(fn_2_5156C(index, font), font);
}
#endif

extern u8 lbl_803CB8F0[];

// One roster slot in the menu work buffer lbl_2_bss_1A8248[0] (0x36 of them).
typedef struct MenuRosterSlot {
    /*0x00*/ u8 _00[5];
    /*0x05*/ s8 _05;
    /*0x06*/ u8 _06;
    /*0x07*/ u8 _07; // saved copy of _06
    /*0x08*/ u8 _08;
    /*0x09*/ u8 _09[20];
    /*0x1D*/ u8 _1D[20]; // saved copy of _09
    /*0x31*/ s8 _31;
    /*0x32*/ u8 _32[2];
} MenuRosterSlot; // size: 0x34

// fn_2_4D378, size:0x304
// NONMATCHING 95%: first copy loop (unrolled x8) starts its offset with `li` instead of `mr r6,r4`, shifting registers (see docs/patterns/inlining.md agent-r1 notes)
#if NONMATCHING
void fn_2_4D378(void) {
    s32 i;
    s32 j;
    *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
    lbl_2_bss_1A8248[0][0x441E] = lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F3]; // TODO type
    lbl_2_bss_1A8248[0][0x441F] = lbl_803CB8F0[lbl_2_bss_1A8248[0][0x441E]];
    fn_2_4C3EC();
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* e = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        e->_07 = e->_06;
    }
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        for (j = 0; j < 10; j++) {
            slot->_1D[j * 2] = slot->_09[j * 2];
            slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
        }
    }
}
#endif

extern s32 fn_2_68690(s32 index);

// fn_2_4D67C, size:0x2E4
// NONMATCHING 95%: same first-loop `li` vs `mr r4,r6` offset init as fn_2_4D378, shifting registers
#if NONMATCHING
void fn_2_4D67C(void) {
    s32 i;
    s32 j;
    s32 result;
    *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
    result = fn_2_68690(0);
    lbl_2_bss_1A8248[0][0x441E] = result;
    lbl_2_bss_1A8248[0][0x4420] = result - 2;
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* e = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        e->_07 = e->_06;
    }
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        for (j = 0; j < 10; j++) {
            slot->_1D[j * 2] = slot->_09[j * 2];
            slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
        }
    }
}
#endif

// fn_2_4D960, size:0x2C4
// NONMATCHING 95%: same first-loop `li` vs `mr r6,r3` offset init as fn_2_4D378, shifting registers
#if NONMATCHING
void fn_2_4D960(void) {
    s32 i;
    s32 j;
    *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
    lbl_2_bss_1A8248[0][0x441E] = 1;
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* e = (MenuRosterSlot*)lbl_2_bss_1A8248[0] + i;
        e->_07 = e->_06;
    }
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        for (j = 0; j < 10; j++) {
            slot->_1D[j * 2] = slot->_09[j * 2];
            slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
        }
    }
}
#endif

// fn_2_4DC24, size:0x2C4
// NONMATCHING 95%: identical to fn_2_4D960; first-loop `li` vs `mr r6,r3` offset init shifts registers
#if NONMATCHING
void fn_2_4DC24(void) {
    s32 i;
    s32 j;
    *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
    lbl_2_bss_1A8248[0][0x441E] = 1;
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* e = (MenuRosterSlot*)lbl_2_bss_1A8248[0] + i;
        e->_07 = e->_06;
    }
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        for (j = 0; j < 10; j++) {
            slot->_1D[j * 2] = slot->_09[j * 2];
            slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
        }
    }
}
#endif

// fn_2_4DEE8, size:0x2D8
// NONMATCHING 93%: same first-loop `li` vs `mr` offset init as fn_2_4D960, plus prologue lis/addi scheduling
#if NONMATCHING
void fn_2_4DEE8(void) {
    s32 i;
    s32 j;
    *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
    lbl_2_bss_1A8248[0][0x441E] = 1;
    lbl_2_bss_1A8248[0][0x441F] = 0x13;
    lbl_2_bss_1A8248[0][0x444A] = 0;
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* e = (MenuRosterSlot*)lbl_2_bss_1A8248[0] + i;
        e->_07 = e->_06;
    }
    for (i = 0; i < 0x36; i++) {
        MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
        for (j = 0; j < 10; j++) {
            slot->_1D[j * 2] = slot->_09[j * 2];
            slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
        }
    }
}
#endif

// fn_2_4E1C0, size:0x5E4
// NONMATCHING 95%: same first-loop `li` vs `mr` offset init as fn_2_4D378 in both branches, shifting registers
#if NONMATCHING
void fn_2_4E1C0(void) {
    s32 i;
    s32 j;
    if (*(s8*)(lbl_2_bss_1A8248[0] + 0x44EF) == 0) {
        *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
        lbl_2_bss_1A8248[0][0x441E] = lbl_2_bss_1A8248[0][*(s16*)(lbl_2_bss_1A8248[0] + 0x16C2) * 10 + 0x40F3]; // TODO type
        lbl_2_bss_1A8248[0][0x441F] = lbl_803CB8F0[lbl_2_bss_1A8248[0][0x441E]];
        fn_2_4C3EC();
        lbl_2_bss_1A8248[0][0x444A] = 0;
        for (i = 0; i < 0x36; i++) {
            MenuRosterSlot* e = (MenuRosterSlot*)lbl_2_bss_1A8248[0] + i;
            e->_07 = e->_06;
        }
        for (i = 0; i < 0x36; i++) {
            MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
            for (j = 0; j < 10; j++) {
                slot->_1D[j * 2] = slot->_09[j * 2];
                slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
            }
        }
    } else {
        *(s8*)(lbl_2_bss_1A824C[0] + 0x197843) = -1;
        lbl_2_bss_1A8248[0][0x441E] = 0;
        lbl_2_bss_1A8248[0][0x441F] = 0;
        fn_2_4C3EC();
        lbl_2_bss_1A8248[0][0x444A] = 0;
        for (i = 0; i < 0x36; i++) {
            MenuRosterSlot* e = (MenuRosterSlot*)lbl_2_bss_1A8248[0] + i;
            e->_07 = e->_06;
        }
        for (i = 0; i < 0x36; i++) {
            MenuRosterSlot* slot = &((MenuRosterSlot*)lbl_2_bss_1A8248[0])[i];
            for (j = 0; j < 10; j++) {
                slot->_1D[j * 2] = slot->_09[j * 2];
                slot->_1D[j * 2 + 1] = slot->_09[j * 2 + 1];
            }
        }
    }
}
#endif

#include "main/file_800A7C08.h"
#include "menus/rep_0788.h"
#include "menus/rep_08E8.h"

extern s8 lbl_2_bss_9E10;
extern void fn_2_93C64(void);

// lbl_803C77B8 is the PadState[4] array (main/file_800A7C08.h).
#define MENU_PADS ((PadState*)&lbl_803C77B8)

// fn_2_535B0, size:0x2EC
// NONMATCHING 99%: post-loop pad lookup computes `lbl_803C77B8 + off` with base/offset registers swapped (r0/r3)
#if NONMATCHING
void fn_2_535B0(void) {
    u8* o = lbl_803CC1B8[0];
    s32 i;
    switch (*(s8*)(o + 0x28)) {
    case 0:
        *(s32*)(lbl_2_bss_1A824C[0] + 0x1976A4) = 0; // TODO type
        *(s32*)(lbl_2_bss_1A824C[0] + 0x1976A0) = 0;
        o[0x28] = 1;
        break;
    case 1:
        fn_2_1FFC4(2);
        for (i = 0; i < 2; i++) {
            fn_2_1FF10(i);
            switch (i) {
            case 0:
                if (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976A0) == i &&
                    ((MENU_PADS[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863)].down & 0x100) ||
                     MENU_PADS[0].sticks.substickY > 0x32)) {
                    o[0x28] = 3;
                }
                break;
            case 1:
                if (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976A0) == i &&
                    (MENU_PADS[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863)].down & 0x102)) {
                    lbl_2_bss_1A824C[0][0x19784A] = 1;
                    lbl_2_bss_1A824C[0][0x197846] = 0;
                    lbl_2_bss_1A824C[0][0x197845] = 1;
                    lbl_2_bss_9E10 = 1;
                    o[0x28] = 2;
                }
                break;
            }
        }
        if ((MENU_PADS[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863)].down & 0x200) ||
            MENU_PADS[0].sticks.substickY > 0x32) {
            o[0x28] = 3;
        }
        break;
    case 2:
        fn_2_1FF14(1);
        for (i = 0; i < 1; i++) {
            fn_2_1FF0C(i);
            switch (i) {
            case 0:
                if (*(s32*)(lbl_2_bss_1A824C[0] + 0x1976A4) == i) {
                    u16 down = MENU_PADS[*(s8*)(lbl_2_bss_1A824C[0] + 0x197863)].down;
                    if (down & 0x200) {
                        lbl_2_bss_1A824C[0][0x19784A] = 0;
                        lbl_2_bss_1A824C[0][0x197846] = 0;
                        *(s32*)(lbl_2_bss_1A824C[0] + 0x1976A4) = 0;
                        lbl_2_bss_1A824C[0][0x197845] = 0;
                        o[0x28] = 1;
                    } else if (down & 0x100) {
                        lbl_2_bss_9E10 ^= 1;
                    } else if (down & 0x1000) {
                        fn_2_93C64();
                    }
                    if (lbl_2_bss_9E10 != 0) {
                        fn_2_489DC();
                    }
                }
                break;
            }
        }
        break;
    case 3: {
        u8* q = *(u8**)(o + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        o[0x28] = 0;
        break;
    }
    }
}
#endif

// fn_2_54474, size:0x3D0
void fn_2_54474(void) {
    MenuDrawEntry* entry;
    s32 row;
    s32 column;
    for (row = 0; row < 70; row++) {
        for (column = 0; column < 864; column++) {
            entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8234[0])[row][column];
            entry->draw = NULL;
            entry->_04 = 0;
            entry->_06 = 0;
            entry->_10 = 0;
            entry->_08 = 0;
            entry->_0A = 0;
            entry->_0C = 0;
            entry->_0E = 0;
            entry->_12 = 0;
            entry->_14 = 0;
        }
    }
    for (row = 0; row < 10; row++) {
        for (column = 0; column < 864; column++) {
            entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8230[0])[row][column];
            entry->draw = NULL;
            entry->_04 = 0;
            entry->_06 = 0;
            entry->_10 = 0;
            entry->_08 = 0;
            entry->_0A = 0;
            entry->_0C = 0;
            entry->_0E = 0;
            entry->_12 = 0;
            entry->_14 = 0;
        }
    }
}

#include "musyx/musyx.h"

extern u8 lbl_800EFBA4[];

// Pad buttons copied from lbl_8034E9A0 + 0x472C.
typedef struct MenuPadCopy {
    u16 held;
    u16 down;
    u16 repeat;
} MenuPadCopy;

// fn_2_52260, size:0x3E8
void fn_2_52260(void) {
    s32 sel = lbl_2_bss_F410.w50;
    MenuPadCopy pad;
    memset(&pad, 0, sizeof(pad));
    pad.held = *(u16*)(lbl_8034E9A0 + 0x472C); // TODO type
    pad.down = *(u16*)(lbl_8034E9A0 + 0x472E);
    pad.repeat = *(u16*)(lbl_8034E9A0 + 0x4730);
    if (pad.down & 8) {
        if (--sel < 0) {
            sel = 2;
        }
        if (lbl_2_bss_33FBCC.bF != -1 && sel == lbl_8034E9A0[0x4754]) {
            if (--sel < 0) {
                sel = 2;
            }
        }
        lbl_2_bss_33FBCC.b17 = 0x4C;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad.down & 4) {
        if (++sel == 3) {
            sel = 0;
        }
        if (lbl_2_bss_33FBCC.bF != -1 && sel == lbl_8034E9A0[0x4754]) {
            if (++sel == 3) {
                sel = 0;
            }
        }
        lbl_2_bss_33FBCC.b17 = 0x4C;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad.down & 0x100) {
        lbl_8034E9A0[0x4754] = sel;
        lbl_80361B20[0xF6] = sel;
        if (lbl_8034E9A0[0x4756] == 0 && lbl_2_bss_33FBCC.bF == -1) {
            lbl_2_bss_33FBCC.state = 0;
            lbl_2_bss_F410.w54 = 0;
            lbl_2_bss_9E08 = 6;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (lbl_8034E9A0[0x4756] == 1 || lbl_2_bss_33FBCC.bF != -1) {
            if (lbl_2_bss_33FBCC.bF != -1) {
                if (lbl_80354768[3].b[0x46 + sel] != 0) { // TODO type: what lives here // TODO type
                    fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x29, 0, 0);
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    lbl_2_bss_9E08 = 7;
                } else {
                    fn_8003BF54(0, 0, 0, 0, 1, 1, 2, sel, 2);
                    sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                    *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
                    lbl_2_bss_9E08 = 9;
                }
            } else {
                fn_8004A34C(lbl_2_bss_33FB4C, 0, 0x1B, 0, 0);
                sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
                lbl_2_bss_9E08 = 7;
            }
        }
    } else if (pad.down & 0x200) {
        if (lbl_2_bss_33FBCC.bF != -1) {
            lbl_2_bss_33FBCC.b10 = lbl_2_bss_33FBCC.bF;
            lbl_2_bss_33FBCC.bF = -1;
            lbl_2_bss_9E08 = 6;
            lbl_2_bss_33FBCC.b17 = 0x4E;
            lbl_803C50E8[0x52] = 0;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        } else {
            lbl_2_bss_33FBCC.b17 = 0x4A;
            sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
            lbl_2_bss_33FBCC.bF = -1;
            lbl_2_bss_9E08 = 0xE;
        }
    }
    lbl_2_bss_F410.w50 = sel;
}

extern u8 starMissionCompletionTracker[]; // challenge save block, sizeof(MenuSlot)
extern void fn_80041150(u8 mask, u8 slot);

// fn_2_51C58, size:0x44C
void fn_2_51C58(void) {
    s32 cursor = lbl_2_bss_F410.w54;
    s32 sel = lbl_2_bss_F410.w50;
    MenuPadCopy pad;
    memset(&pad, 0, sizeof(pad));
    pad.held = *(u16*)(lbl_8034E9A0 + 0x472C); // TODO type
    pad.down = *(u16*)(lbl_8034E9A0 + 0x472E);
    pad.repeat = *(u16*)(lbl_8034E9A0 + 0x4730);
    if (lbl_2_bss_33FBCC.b21 != 0) {
        pad.repeat = 0;
        pad.down = 0;
        pad.held = 0;
    }
    if (pad.down & 0x100) {
        switch (cursor) {
        case 0:
            lbl_2_bss_33FBCC.b17 = 0x4A;
            memset(&lbl_80354768[lbl_8034E9A0[0x4754]].b[0xAF8], 0, 0xB10);
            memcpy(starMissionCompletionTracker, &lbl_80354768[lbl_8034E9A0[0x4754]], sizeof(MenuSlot));
            lbl_80361B20[0xF6] = sel;
            lbl_2_bss_33FBCC.b6 = 0;
            lbl_2_bss_33FBCC.state = 2;
            break;
        case 1:
            fn_80041150(2, lbl_8034E9A0[0x4754]);
            lbl_2_bss_33FBCC.b17 = 0x4A;
            lbl_2_bss_33FBCC.b22 = 0x52;
            lbl_8034E978[0x26] = 1;
            fn_2_5163C();
            lbl_80361B20[0xF6] = sel;
            lbl_2_bss_33FBCC.b6 = 1;
            lbl_2_bss_33FBCC.bE = 1;
            lbl_2_bss_9E08 = 0xA;
            break;
        case 2:
            if (lbl_80354768[lbl_8034E9A0[0x4754]].b[0x441B] != 0) {
                fn_8004A34C(lbl_803C50E8, 0, 0x38, 0, 0);
            } else {
                fn_8004A34C(lbl_803C50E8, 0, 0x37, 0, 0);
            }
            lbl_80361B20[0xF6] = sel;
            lbl_2_bss_33FBCC.b6 = 0;
            lbl_2_bss_9E08 = 0x10;
            break;
        case 3:
            lbl_2_bss_33FBCC.bF = lbl_8034E9A0[0x4754];
            lbl_2_bss_33FBCC.b15 = 3;
            memcpy(starMissionCompletionTracker, &lbl_80354768[(s8)lbl_8034E9A0[0x4754]], sizeof(MenuSlot));
            lbl_803C50E8[0x52] = 5;
            if (++lbl_2_bss_F410.w50 == 3) {
                lbl_2_bss_F410.w50 = 0;
            }
            lbl_2_bss_33FBCC.bD = lbl_2_bss_F410.w50;
            lbl_2_bss_33FBCC.b17 = 0x4D;
            lbl_2_bss_33FBCC.state = 3;
            break;
        case 4:
            lbl_2_bss_33FBCC.bF = lbl_8034E9A0[0x4754];
            lbl_2_bss_33FBCC.b15 = 4;
            lbl_2_bss_33FBCC.state = 4;
            break;
        case 5:
            lbl_2_bss_33FBCC.state = 3;
            break;
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (pad.down & 0x200) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        lbl_2_bss_33FBCC.state = 3;
    } else if (pad.repeat & 8) {
        lbl_2_bss_33FBCC.w1C = cursor;
        do {
            if (--cursor < 0) {
                cursor = 5;
            }
        } while (lbl_2_bss_33FBCC.options[cursor] == 0);
        lbl_2_bss_33FBCC.b22 = 0x53;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (pad.repeat & 4) {
        lbl_2_bss_33FBCC.w1C = cursor;
        do {
            if (++cursor == 6) {
                cursor = 0;
            }
        } while (lbl_2_bss_33FBCC.options[cursor] == 0);
        lbl_2_bss_33FBCC.b22 = 0x53;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
    lbl_2_bss_F410.w54 = cursor;
}

extern u8 lbl_803C5EA4[];
extern u8 lbl_8037169C[];
extern u8 lbl_800EF808[];
extern void fn_80021410(void);
extern void fn_80062A74(void);

// fn_2_52690, size:0xD78
// NONMATCHING 99%: only the `addi lbl_803C50E8@l` is scheduled one slot earlier in the two removeQueue tails (cases 11 and 13)
#if NONMATCHING
void fn_2_52690(void) {
    switch (lbl_2_bss_9E08) {
    case 0:
        changeScene(1, 6);
        lbl_2_bss_33FBCC.bF = -1;
        lbl_2_bss_33FBCC.b1A = 0;
        lbl_2_bss_F410.w54 = 0;
        lbl_2_bss_F410.w50 = 0;
        lbl_2_bss_9E08 = 1;
        break;
    case 1:
        fn_2_52198();
        lbl_803C5EA4[0x36] = 1;
        lbl_803C5EA4[0x37] = lbl_803C5EA4[0x38];
        lbl_803C5EA4[0x38] = 0;
        lbl_2_bss_33FBCC.b17 = 0x49;
        if (lbl_8034E9A0[0x4756] == 1) {
            if (lbl_803C50E8[0x47] != 0) {
                lbl_2_bss_9E08 = 0xF;
                break;
            }
            lbl_2_bss_9E08 = 2;
        } else {
            lbl_2_bss_9E08 = 5;
        }
        lbl_2_bss_F410.w54 = lbl_80361B20[0xF6];
        break;
    case 2:
        if (lbl_800E877C[0x18] == 8 || lbl_800E877C[0x18] == 9) {
            if (lbl_800E877C[0x18] == 9) {
                lbl_803C50E8[0x52] = 3;
            } else {
                lbl_803C50E8[0x52] = 1;
            }
            fn_8003BF54(0, 0, 0, 0, 1, 1, 2, lbl_80361B20[0xF6], 0);
            *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
            lbl_2_bss_9E08 = 9;
        } else {
            fn_8004A34C(lbl_803C50E8, 0, 0x34, 0, 0);
            lbl_803C50E8[0x52] = 2;
            lbl_2_bss_9E08 = 3;
        }
        break;
    case 3:
        switch (lbl_803C50E8[0x45]) {
        case 2:
            if (lbl_800E877C[0x18] == 9) {
                lbl_803C5EA4[0x39] = 1;
            } else if (lbl_800E877C[0x18] == 0xA) {
                *(u16*)(starMissionCompletionTracker + 0x43BC) = 0; // TODO type
            }
            fn_8003BF54(0, 0, 0, 0, 1, 1, 2, lbl_80361B20[0xF6], 0);
            *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
            lbl_2_bss_9E08 = 9;
            break;
        case 3:
        case 4:
            if (lbl_800E877C[0x18] == 0xA) {
                fn_8004A34C(lbl_803C50E8, 0, 0x35, 0, 0);
                lbl_2_bss_9E08 = 4;
            } else {
                lbl_2_bss_33FBCC.b17 = 0x4A;
                lbl_2_bss_33FBCC.bF = -1;
                lbl_2_bss_9E08 = 0xE;
            }
            break;
        }
        break;
    case 4:
        switch (lbl_803C50E8[0x45]) {
        case 2:
            lbl_2_bss_33FBCC.b17 = 0x4A;
            lbl_2_bss_33FBCC.bF = -1;
            lbl_2_bss_9E08 = 0xA;
            break;
        case 3:
        case 4:
            lbl_2_bss_9E08 = 2;
            break;
        }
        break;
    case 5:
        if (lbl_2_bss_33FBCC.b17 != 0x49 && lbl_2_bss_33FBCC.b21 == 0 && lbl_2_bss_33FBCC.b19 == 0) {
            fn_2_52260();
        }
        break;
    case 6:
        fn_2_520A4();
        break;
    case 7:
        lbl_2_bss_9E08 = 8;
        break;
    case 8:
        switch (fn_8004CA6C(*(u16*)(lbl_8034E9A0 + 0x472E))) {
        case 0:
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            if (lbl_2_bss_33FBCC.bF != -1) {
                fn_8003BF54(0, 0, 0, 0, 1, 1, 2, lbl_8034E9A0[0x4754], 2);
            } else {
                fn_8003BF54(0, 0, 0, 0, 1, 1, 2, lbl_8034E9A0[0x4754], 0);
            }
            *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
            lbl_2_bss_9E08 = 9;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            lbl_2_bss_33FBCC.b17 = 0x4E;
            lbl_2_bss_33FBCC.b10 = lbl_2_bss_33FBCC.bF;
            lbl_2_bss_33FBCC.bF = -1;
            lbl_2_bss_9E08 = 5;
            break;
        }
        break;
    case 9: {
        s16 result = *(s16*)(lbl_803CC1B8[0] + 0x10);
        if (result != 0) {
            if (lbl_8034E9A0[0x4756] == 1) {
                switch (result) {
                case 1:
                    if (lbl_2_bss_33FBCC.bF != -1) {
                        lbl_2_bss_33FBCC.b17 = 0x4E;
                        lbl_2_bss_33FBCC.b22 = 0x52;
                        lbl_2_bss_33FBCC.b10 = lbl_2_bss_33FBCC.bF;
                        lbl_2_bss_33FBCC.bF = -1;
                        lbl_2_bss_9E08 = 5;
                    } else {
                        lbl_2_bss_33FBCC.b17 = 0x4B;
                        lbl_2_bss_33FBCC.b22 = 0x52;
                        lbl_2_bss_33FBCC.b16 = 0x64;
                        lbl_2_bss_9E08 = 0xF;
                    }
                    break;
                case 11:
                    if (lbl_2_bss_33FBCC.bF != -1) {
                        lbl_2_bss_33FBCC.b22 = 0x52;
                        lbl_2_bss_9E08 = 5;
                    } else {
                        if (lbl_800E877C[0x18] == 9) {
                            fn_8004A34C(lbl_803C50E8, 0, 0x24, 0, 0);
                        } else if (lbl_800E877C[0x18] == 0xA) {
                            lbl_2_bss_33FBCC.b17 = 0x4A;
                            lbl_2_bss_9E08 = 0xF;
                            break;
                        } else {
                            fn_8004A34C(lbl_803C50E8, 0, 0x1C, 0, 0);
                        }
                        lbl_2_bss_9E08 = 0x11;
                    }
                    break;
                default:
                    if (lbl_803C50E8[0x52] == 2) {
                        lbl_2_bss_9E08 = 2;
                    } else if (lbl_803C50E8[0x52] == 4) {
                        lbl_2_bss_33FBCC.bE = 1;
                        lbl_2_bss_9E08 = 5;
                    } else if (lbl_803C50E8[0x52] == 1 || lbl_803C50E8[0x52] == 3) {
                        lbl_2_bss_33FBCC.b17 = 0x4B;
                        lbl_2_bss_33FBCC.b16 = 0x64;
                        lbl_2_bss_9E08 = 0xF;
                    } else {
                        lbl_2_bss_9E08 = 5;
                    }
                    lbl_2_bss_33FBCC.b22 = 0x52;
                    break;
                }
            } else {
                switch (result) {
                case 1:
                if (lbl_2_bss_33FBCC.bF != -1) {
                    if (lbl_2_bss_33FBCC.b15 == 4) {
                        lbl_2_bss_33FBCC.b22 = 0x52;
                        lbl_2_bss_33FBCC.bE = 1;
                    } else {
                        lbl_2_bss_33FBCC.b17 = 0x4F;
                        lbl_2_bss_33FBCC.b22 = 0x52;
                    }
                    lbl_2_bss_33FBCC.b10 = lbl_2_bss_33FBCC.bF;
                    lbl_2_bss_33FBCC.bF = -1;
                    lbl_2_bss_9E08 = 5;
                } else if (lbl_2_bss_33FBCC.b6 == 1) {
                    lbl_2_bss_33FBCC.b17 = 0x4A;
                    lbl_2_bss_33FBCC.b22 = 0x52;
                    lbl_8034E978[0x26] = 1;
                    lbl_2_bss_33FBCC.bE = 1;
                    lbl_2_bss_9E08 = 0xA;
                } else {
                    lbl_2_bss_33FBCC.b17 = 0x4A;
                    lbl_2_bss_33FBCC.b22 = 0x52;
                    lbl_2_bss_33FBCC.bE = 1;
                    lbl_2_bss_9E08 = 0xA;
                    lbl_2_bss_33FBCC.state = 0;
                }
                break;
                default:
                lbl_2_bss_33FBCC.b22 = 0x52;
                if (lbl_2_bss_33FBCC.bF != -1) {
                    lbl_2_bss_33FBCC.b17 = 0x4E;
                    lbl_2_bss_33FBCC.b10 = lbl_2_bss_33FBCC.bF;
                    lbl_2_bss_33FBCC.bF = -1;
                }
                lbl_2_bss_33FBCC.bE = 1;
                lbl_2_bss_9E08 = 5;
                break;
                }
            }
        }
        break;
    }
    case 10:
        if (lbl_2_bss_33FBCC.b19 != 1 && lbl_8037169C[0x13] != 0) {
            lbl_2_bss_9E08 = 0xB;
        }
        break;
    case 11:
        if (lbl_8034E9A0[0x4756] == 0) {
            fn_80035B50(8);
            switch (lbl_2_bss_33FBCC.b6) {
            case 0:
                fn_80042D38(0xC);
                break;
            case 2:
                break;
            case 1:
                fn_80062A74();
                fn_80035B50(0xF);
                fn_80035B50(0x12);
                fn_80035B50(9);
                fn_80035B50(6);
                fn_800AD054(*(void**)(lbl_8034E9A0 + 0x46F0), *(void**)(lbl_8034E9A0 + 0x46F4)); // TODO type
                fn_80021410();
                fn_800ACFB0(*(void**)(lbl_800EF808 + 0x98));
                fn_80042D38(0x10);
                break;
            }
            lbl_2_bss_33FBCC.b6 = 0;
            lbl_800E877C[0x18] = 1;
            lbl_800E877C[0x19] = 0;
        } else {
            fn_80035B50(6);
            fn_80035B50(8);
            if (lbl_800E877C[0x18] == 8) {
                fn_80042D38(0x10);
            } else {
                fn_80042D38(5);
            }
            lbl_8034E978[0x26] = 1;
        }
        lbl_2_bss_33FBCC.w0 = 0;
        lbl_2_bss_F410.w50 = 0;
        lbl_2_bss_9E08 = 0;
        lbl_803C50E8[0x52] = 0;
        fn_800B0A14_removeQueue(lbl_803C50E8);
        break;
    case 14:
        if (lbl_2_bss_33FBCC.b19 != 1 && lbl_8037169C[0x13] != 0) {
            lbl_2_bss_9E08 = 0xD;
        }
        break;
    case 13:
        lbl_8034E978[0x26] = 1;
        lbl_8034E9A0[0x48AF] = 1;
        if (lbl_8034E9A0[0x4756] == 0) {
            fn_80035B50(8);
            fn_80042D38(5);
            lbl_800E877C[0x18] = 1;
            lbl_800E877C[0x19] = 0;
        } else {
            fn_80035B50(6);
            fn_80035B50(8);
            if (lbl_800E877C[0x18] != 0xA) {
                lbl_800E877C[0x18] = 8;
                lbl_800E877C[0x19] = 0;
                fn_80042D38(0x10);
            } else {
                lbl_800E877C[0x18] = 9;
                lbl_800E877C[0x19] = 0;
                fn_80042D38(5);
            }
        }
        lbl_2_bss_33FBCC.w0 = 0;
        lbl_2_bss_F410.w50 = 0;
        lbl_2_bss_9E08 = 0;
        lbl_803C50E8[0x52] = 0;
        fn_800B0A14_removeQueue(lbl_803C50E8);
        break;
    case 12:
        if (lbl_803C50E8[0x45] != 0) {
            switch (lbl_803C50E8[0x45]) {
            case 2:
            case 3:
                lbl_2_bss_9E08 = 5;
                break;
            }
        }
        break;
    case 15:
        if (lbl_2_bss_33FBCC.b19 != 1) {
            if ((s8)lbl_2_bss_33FBCC.b16 > 0) {
                lbl_2_bss_33FBCC.b16--;
            } else {
                lbl_2_bss_33FBCC.b16 = 0;
                lbl_2_bss_33FBCC.b17 = 0x4A;
                lbl_2_bss_9E08 = 0xA;
            }
        }
        break;
    case 16:
        switch (lbl_803C50E8[0x45]) {
        case 1:
        case 2:
            fn_80041150(2, lbl_8034E9A0[0x4754]);
            lbl_2_bss_33FBCC.b17 = 0x4A;
            lbl_2_bss_33FBCC.b22 = 0x52;
            lbl_2_bss_33FBCC.bE = 1;
            lbl_2_bss_9E08 = 0xA;
            break;
        }
        break;
    case 17:
        switch (lbl_803C50E8[0x45]) {
        case 2:
            lbl_2_bss_33FBCC.b17 = 0x4A;
            lbl_2_bss_9E08 = 0xF;
            break;
        case 3:
        case 4:
            fn_8003BF54(0, 0, 0, 0, 1, 1, 2, lbl_80361B20[0xF6], 0);
            *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
            lbl_2_bss_9E08 = 9;
            break;
        }
        break;
    }
}
#endif
