#include "menus/auto_00_00071EC4_text.h"

#include "static/UnknownHomes_Static.h"

extern u8 lbl_803CBBC4[];
extern u8 lbl_80371C30[];
extern u8* lbl_2_bss_1A8248[];
extern u8 lbl_803C66B0[];
extern u8 lbl_8034E978[];
extern void* lbl_2_data_2A1E8[];
extern void* lbl_2_data_2A2EC[];
extern s32 lbl_2_bss_A840;
extern s32 lbl_2_bss_F410;
extern u8 lbl_2_data_2D33C[];
extern u8 lbl_803C50E8[];
extern void fn_80053FE8(void);
extern void fn_8004E2EC(void);
extern void fn_8004F964(void);
extern void fn_80062674(s32 index);
extern void fn_800626EC(s32 index);
extern void fn_800625A4(s32 a, s32 b);
extern u8* lbl_803CC1B8;
extern s32 fn_80042DA8(s32 a, s32 b, s32 c);
extern void fn_80034E20(void* object, void* data);
extern u8 lbl_800FEF70[];
extern u8 lbl_80361B20[];
extern u8 lbl_800FE930[];
extern u8 lbl_8034E9A0[];
extern u8 lbl_803C5EA4[];
extern u8* lbl_803CBBCC[];
extern u8 lbl_2_data_2B4DC[];
extern u8 lbl_2_data_2AADC[];
#include "menus/auto_00_00001254_text.h"

// fn_2_73028, size:0x4
void fn_2_73028(void) {
}

// fn_2_71EC4, size:0x38
void fn_2_71EC4(u8* obj) {
    ((void (*)(u8*))lbl_2_data_2A1E8[*(s16*)(obj + 0x94)])(obj);
}

// fn_2_71EFC, size:0x24
void fn_2_71EFC(u8* obj) {
    s32 i = *(s32*)(obj + 0x80);
    u8* b = lbl_2_bss_1A8248[0];
    *(u8*)(b + i * 0xD8 + 0x16D0) = 0;
}

// fn_2_72038, size:0x1C
void fn_2_72038(s32 index, s16 value) {
    *(s16*)(lbl_2_bss_1A8248[0] + index * 0xD8 + 0x16C4) = value;
}

// fn_2_72054, size:0x28
void fn_2_72054(s32 index, s8 value) {
    u8* e = lbl_2_bss_1A8248[0] + index * 0xD8 + 0x1610;
    e[0xC3] = value;
    *(s16*)(e + 0x94) = 0;
}

// fn_2_72630, size:0x2C
void fn_2_72630(void) {
    fn_800B0A5C_insertQueue((void*)fn_2_72594, 0x3000);
}

// fn_2_73B54, size:0x40
s32 fn_2_73B54(s32 a) {
    s32 b = lbl_2_bss_A840;
    if (b == 0 && a == 6) {
        return 4;
    }
    if (b == 6 && a == 0) {
        return 1;
    }
    return 1;
}

// fn_2_744C8, size:0x50
void fn_2_744C8(void) {
    if ((lbl_803C66B0[7] == 1) ? 1 : 0) {
        fn_80062674(0);
        lbl_803C66B0[7] = 2;
    }
}

// fn_2_74518, size:0x4C
void fn_2_74518(void) {
    if ((lbl_803C66B0[7] == 0) ? 1 : 0) {
        fn_800626EC(0);
        lbl_803C66B0[7] = 1;
    }
}

// fn_2_74D8C, size:0x2C
void fn_2_74D8C(void) {
    fn_800B0A5C_insertQueue((void*)fn_2_74CD8, 0x1000);
}

// fn_2_76098, size:0x4
void fn_2_76098(void) {
}

// fn_2_7609C, size:0x30
void fn_2_7609C(s32 unused, u8 a, u8 c) {
    if (c == 0) {
        fn_2_8794(a, 0);
    }
}

// fn_2_7664C, size:0x4
void fn_2_7664C(void) {
}

// fn_2_78034, size:0x28
void fn_2_78034(s32 unused, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 0) ? 1 : 0) {
        lbl_803C66B0[index + 0xD] = 1;
    }
}

// fn_2_79634, size:0x54
void fn_2_79634(s32 unused, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 1) ? 1 : 0) {
        fn_80062674(index);
        lbl_803C66B0[index + 0xD] = 2;
    }
}

// fn_2_85108, size:0x54
void fn_2_85108(void) {
    u8* a = lbl_8034E978;
    u8* b = lbl_800FEF70;
    a[0] = 5;
    a[9] = a[8];
    a[8] = *(u16*)(b + 0x58);
    fn_800B0A5C_insertQueue((void*)fn_2_84FA8, 0x3000);
}

// fn_2_8515C, size:0x4
void fn_2_8515C(void) {
}

// fn_2_85160, size:0x48
void fn_2_85160(void) {
    u8* p = lbl_803CC1B8;
    if (--*(s16*)(p + 0x10) == 0) {
        fn_800625A4(0, 4);
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// fn_2_73B94, size:0x5C
s32 fn_2_73B94(s32 a) {
    if (lbl_2_bss_A840 == 0 && a == 6) {
        return 0x2D;
    }
    if (lbl_2_bss_A840 == 6 && a == 0) {
        return 0xE;
    }
    if (lbl_2_bss_A840 <= a) {
        return 0x1D;
    } else if (lbl_2_bss_A840 > a) {
        return 0x2C;
    }
}

// fn_2_82DE8, size:0x70
void fn_2_82DE8(void) {
    *(u8**)(lbl_8034E9A0 + 0x4748) = ((u8**)&lbl_803CC1B8)[0];
    lbl_8034E9A0[0x48AF] = 0;
    lbl_803C5EA4[0x37] = 0;
    lbl_803C5EA4[0x38] = 0;
    fn_80034E20(((u8**)&lbl_803CC1B8)[0], lbl_2_data_2B4DC);
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_2_82CF0;
}

// fn_2_82E58, size:0x68
void fn_2_82E58(void) {
    if (*(u16*)(lbl_803CBBCC[0] + 6) != 0xB && g_d_GameSettings.GameModeSelected != 5) {
        fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
    }
    fn_800B0A5C_insertQueue((void*)fn_2_8279C, 0x3000);
}

// fn_2_71F20, size:0x40
void fn_2_71F20(u8* obj) {
    *(void**)(obj + 0xD4) = lbl_2_data_2A2EC[obj[0xC3]];
    (*(void (**)(u8*))(obj + 0xD4))(obj);
}

// fn_2_72594, size:0x9C
void fn_2_72594(void) {
    u8* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2AADC);
    for (i = 0; i < 4; i++) {
        fn_800363D8(obj, i + 7, 1, 0x32, 3 - i);
    }
    fn_800363D8(obj, 2, 1, 0x35, 0);
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_2_7207C;
}

// fn_2_74DB8, size:0x5C
s32 fn_2_74DB8(s32 a) {
    switch (a) {
    case 13:
    case 16:
    case 20:
    case 22:
    case 25:
    case 34:
    case 42:
    case 50:
    case 52:
        return 1;
    case 21:
    case 24:
    case 29:
    case 33:
    case 44:
    case 51:
    case 53:
        return 2;
    case 23:
    case 30:
    case 36:
    case 45:
        return 3;
    case 12:
    case 26:
    case 27:
    case 31:
    case 35:
    case 43:
    case 46:
    case 49:
        return 4;
    case 32:
        return 5;
    case 47:
        return 6;
    default:
        return 0;
    }
}

// fn_2_75B58, size:0x8C
u8 fn_2_75B58(s32 a, s32 index) {
    s32 i;
    s32 hits;
    s32 total;
    u8 n;
    hits = 0;
    total = 0;
    i = 0;
    n = lbl_8034E9A0[index + 0x470F];
    for (; i < n; i++) {
        total++;
        hits += fn_80042DA8(a, i + 0x6E + index * 5, 0x1E) != 0;
    }
    return hits == total;
}

// fn_2_74CD8, size:0xB4
void fn_2_74CD8(void) {
    u8* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2D33C);
    for (i = 0; i < 7; i++) {
        fn_800363D8(obj, i + 0x18, 1, 0x36, i);
    }
    fn_800363D8(obj, 0x20, 1, 0x32, 0);
    lbl_2_bss_A840 = lbl_2_bss_F410;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_2_747FC;
}

// fn_2_836A4, size:0xA0
void fn_2_836A4(void) {
    u8* a;
    if (lbl_803C50E8[0x47] != 0) {
        fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0);
    }
    a = lbl_8034E978;
    a[9] = a[8];
    a[0] = 0xC;
    a[8] = *(u16*)(lbl_800FEF70 + 0xC8);
    if (*(u16*)(lbl_803CBBCC[0] + 6) != 9) {
        fn_800B0A5C_insertQueue((void*)fn_2_82DE8, 0x3000);
    }
    fn_800B0A5C_insertQueue((void*)fn_2_834F0, 0x3000);
}

// fn_2_738C8, size:0xCC
void fn_2_738C8(void) {
    u8* a;
    if (*(u16*)(lbl_803CBBCC[0] + 6) == 5) {
        fn_800B0A5C_insertQueue((void*)fn_80053FE8, 0);
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        a = lbl_8034E978;
        a[0] = 0xD;
        a[9] = a[8];
        a[8] = *(u16*)(lbl_800FEF70 + 0xD8);
        fn_800B0A5C_insertQueue((void*)fn_8004E2EC, 0x3000);
    } else {
        a = lbl_8034E978;
        a[0] = 0;
        a[9] = a[8];
        a[8] = *(u16*)(lbl_800FEF70 + 8);
        fn_800B0A5C_insertQueue((void*)fn_8004F964, 0x3000);
    }
}

// fn_2_72A58, size:0x30
void fn_2_72A58(void) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        lbl_803CBBC4[3] = 0;
        lbl_803CBBC4[2] = 0;
        lbl_803CBBC4[0] = 0;
    }
}

// fn_2_72DDC, size:0x78
void fn_2_72DDC(s32 a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        if ((s32)(fn_80042DA8(a, 0, 0x19) != 0) == 1) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
        }
    }
}

// fn_2_7293C, size:0xA4
void fn_2_7293C(s32 a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, 0, 0x19) != 0;
        n += fn_80042DA8(a, 1, 0x19) != 0;
        if (n == 2) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
        }
    }
}

// fn_2_728C0, size:0x7C
void fn_2_728C0(u8* o) {
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        *(s32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x190000;
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 4;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x190000;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 4;
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}
