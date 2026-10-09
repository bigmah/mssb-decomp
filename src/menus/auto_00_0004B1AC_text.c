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
extern MenuDrawEntry (*lbl_2_bss_1A8234[])[864];
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
            MenuDrawEntry* entry = &lbl_2_bss_1A8234[0][row][column];
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

extern s16 lbl_2_bss_9600[];
extern s16 lbl_2_bss_9608[][0x100];

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
extern void fn_2_4EB9C(void);

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

typedef struct {
    s32 w0;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
} InitEntry;
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
