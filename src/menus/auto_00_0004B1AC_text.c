#include "menus/auto_00_0004B1AC_text.h"

#include <string.h>
#include "Dolphin/GX.h"
extern void fn_2_4906C(void);

extern void fn_8003BF54(s32, s32, s32, s32, s32, s32, s32, s32, u8);

extern void fn_2_52690(void);
extern u8 lbl_8034E9A0[];

#include "static/UnknownHomes_Static.h"

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
    void (*draw)(s32 context, MenuDrawEntry* entry);
    u8 data[0x14];
};
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
void* fn_2_4E858(void* object) {
    return fn_80034CEC(object);
}

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
void fn_2_4E878(void* object, void* data) {
    fn_80034E20(object, data);
}

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

extern u8* lbl_80366B18[];

// fn_2_5156C, size:0x70
s32 fn_2_5156C(s32 index, u16 flag) {
    if (flag == 0) {
        u8* menu = *(u8**)&lbl_2_bss_1A824C;
        u8* p = lbl_80366B18[menu[0x1972B8] + 0x1E6];
        p += index * 4;
        return *(s32*)(p + 4);
    }
    {
        u8* menu = *(u8**)&lbl_2_bss_1A824C;
        u8* p = lbl_80366B18[menu[0x1972B8] + 0x1E6];
        p += index * 4;
        return *(s32*)(p + 4);
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

typedef struct {
    u8* object;
    s32 _04;
} MenuTblEntry;
extern MenuTblEntry lbl_80371C30[];

// fn_2_53CEC, size:0x10C
void fn_2_53CEC(u8* menu) {
    MenuDrawEntry* entry;
    s32 row;
    s32 column;
    for (row = 0; row < 10; row++) {
        for (column = 0; column < 864; column++) {
            entry = &((MenuDrawEntry(*)[864])lbl_2_bss_1A8230[0])[row][column];
            if (entry->draw != NULL) {
                lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)((u8*)entry + 0xE)].object[0x68] = 0;
                *(u32*)(lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)((u8*)entry + 0xE)].object + 0x54) &= ~2;
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
                lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)((u8*)entry + 0xE)].object[0x68] = 0;
                *(u32*)(lbl_80371C30[*(u16*)(menu + 0x14) + *(s16*)((u8*)entry + 0xE)].object + 0x54) &= ~2;
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
    u8 pad0[2];
    u16 state;
    u8 pad4;
    u8 b5;
    u8 pad6;
    u8 b7;
    u8 b8;
    u8 b9;
    u8 bA;
    u8 bB;
    u8 bC;
    u8 padD;
    u8 bE;
    u8 pad0F[0x13];
    u8 b22;
    u8 pad23;
} Bss33FBCC;
extern Bss33FBCC lbl_2_bss_33FBCC;
extern s16 lbl_2_bss_9E08;
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
    u8 pad[0x54];
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
            lbl_2_bss_33FBCC.b7 = 0;
            lbl_2_bss_33FBCC.b8 = 1;
            lbl_2_bss_33FBCC.b9 = 1;
            lbl_2_bss_33FBCC.bA = 1;
            lbl_2_bss_33FBCC.bB = 1;
            lbl_2_bss_33FBCC.bC = 1;
        } else {
            lbl_2_bss_F410.w54 = 2;
            lbl_2_bss_33FBCC.b5 = 2;
            lbl_2_bss_33FBCC.b7 = 0;
            lbl_2_bss_33FBCC.b8 = 0;
            lbl_2_bss_33FBCC.b9 = 1;
            lbl_2_bss_33FBCC.bA = 1;
            lbl_2_bss_33FBCC.bB = 1;
            lbl_2_bss_33FBCC.bC = 1;
        }
    } else {
        if (lbl_80354768[lbl_8034E9A0[0x4754]].b[0x441B] != 0) {
            lbl_2_bss_F410.w54 = 1;
            lbl_2_bss_33FBCC.b5 = 1;
            lbl_2_bss_33FBCC.b7 = 0;
            lbl_2_bss_33FBCC.b8 = 1;
            lbl_2_bss_33FBCC.b9 = 0;
            lbl_2_bss_33FBCC.bA = 1;
            lbl_2_bss_33FBCC.bB = 1;
            lbl_2_bss_33FBCC.bC = 1;
        } else {
            lbl_2_bss_F410.w54 = 0;
            lbl_2_bss_33FBCC.b5 = 0;
            lbl_2_bss_33FBCC.b7 = 1;
            lbl_2_bss_33FBCC.b8 = 0;
            lbl_2_bss_33FBCC.b9 = 0;
            lbl_2_bss_33FBCC.bA = 0;
            lbl_2_bss_33FBCC.bB = 0;
            lbl_2_bss_33FBCC.bC = 1;
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
    u8* p = lbl_80366B18[menu[0x1972B8] + 0x1E6];
    u16 v;
    u16** q = (u16**)(p + 4);
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
    u8* p = lbl_80366B18[menu[0x1972B8] + 0x1E6];
    u16 v;
    u16** q = (u16**)(p + 4);
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

extern u8* lbl_803CC1B8[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_2_data_1FF84[];
extern u8 lbl_2_data_1FF94[];
extern void fn_800111B4(s32);
extern void fn_800216F8(s32, void*);
extern void fn_800627C4(void);
extern void fn_2_8E8A4(void);

// fn_2_549B4, size:0x184
void fn_2_549B4(void) {
    u8* o = lbl_803CC1B8[0];
    u8* q;
    switch ((s8)o[0x28]) {
    case 0:
        *(s32*)((u8*)lbl_80366B18 + 0x7A0) = ARAMTransfer(lbl_2_data_1FF94, 0, 1, 0);
        o[0x28] = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            fn_800111B4(*(s32*)((u8*)lbl_80366B18 + 0x7A0));
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
