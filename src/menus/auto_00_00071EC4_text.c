#include "menus/auto_00_00071EC4_text.h"

#include "static/UnknownHomes_Static.h"

extern u8 lbl_803CBBC4[];
extern u8 lbl_803CBCD8[];
extern u8 lbl_80371C30[];
extern u8 lbl_2_bss_F468[];
extern void fn_2_74F40(u8* o, s32 index);
extern u8* lbl_2_bss_1A8248[];
extern u8* lbl_2_bss_1A824C[];
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

// fn_2_71F60, size:0xD8
void fn_2_71F60(void) {
    s32 off;
    s32 i;
    u8* obj;
    u8* h;
    u8 x = lbl_2_bss_1A8248[0][0x44F2];
    if (x == 1) {
        return;
    }
    if (x == 2 || x == 3) {
        return;
    }
    i = 0;
    off = 0;
    for (; i < 8; i++) {
        obj = lbl_2_bss_1A8248[0] + off + 0x1610;
        *(void**)(obj + 0xD4) = lbl_2_data_2A2EC[obj[0xC3]];
        (*(void (**)(u8*))(obj + 0xD4))(obj);
        off += 0xD8;
    }
    h = lbl_2_bss_1A824C[0] + 0x190000;
    if (h[0x72BC] != 0) {
        h[0x72BC] = 0;
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
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

// fn_2_82CF0, size:0xF8
void fn_2_82CF0(void) {
    u8* o = *(u8**)(lbl_8034E9A0 + 0x4748);
    if (lbl_803C5EA4[0x36] != 0) {
        *(s32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x280000;
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x10) + 0x64) = lbl_803C5EA4[0x38] + 0x123;
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x18) + 0x64) = lbl_803C5EA4[0x37] + 0x123;
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 1;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 4;
        lbl_803C5EA4[0x36] = 0;
    }
    if (lbl_8034E9A0[0x48AF] != 0) {
        lbl_8034E9A0[0x48AF] = 0;
        fn_80034CEC(o);
        ((void (*)(void))fn_800B0A14_removeQueue)();
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

// fn_2_729E0, size:0x78
void fn_2_729E0(u8* o) {
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        *(s32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x190000;
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 1;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x190000;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 1;
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_72D60, size:0x7C
void fn_2_72D60(u8* o) {
    if ((lbl_803CBBC4[2] == 0) ? 1 : 0) {
        *(s32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x190000;
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 4;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x190000;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 4;
        lbl_803CBBC4[2] = 1;
        lbl_803CBBC4[3] = 1;
    }
}

// fn_2_72814, size:0xAC
void fn_2_72814(s32 a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, 0, 0) != 0;
        n += fn_80042DA8(a, 1, 0) != 0;
        if (n == 2) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[4] = 1;
        }
    }
}

// fn_2_72CB4, size:0xAC
void fn_2_72CB4(s32 a) {
    if ((lbl_803CBBC4[3] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, 0, 0) != 0;
        n += fn_80042DA8(a, 1, 0) != 0;
        if (n == 2) {
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[4] = 1;
        }
    }
}

// fn_2_83744, size:0x94
void fn_2_83744(u8* o) {
    if ((*(u32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) >> 16) == 0x14) {
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 1;
    }
    if ((*(u32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) >> 16) == 0x1E) {
        lbl_803CBCD8[4] = 1;
        fn_80062674(0);
        lbl_803C66B0[0x31] = 2;
    }
}

// fn_2_8082C, size:0xAC
void fn_2_8082C(s32 a, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, index + 0x89, 5) != 0;
        n += fn_80042DA8(a, index + 0x8B, 0xA) != 0;
        if (n == 2) {
            fn_80062674(index);
            lbl_803C66B0[index + 0xD] = 2;
        }
    }
}

// fn_2_80B5C, size:0xD0
void fn_2_80B5C(s32 a, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, index, 0) != 0;
        n += fn_80042DA8(a, index + 2, 0) != 0;
        n += fn_80042DA8(a, index + 0x89, 0xA) != 0;
        if (n == 3) {
            fn_80062674(index);
            lbl_803C66B0[index + 0xD] = 2;
        }
    }
}

// fn_2_74564, size:0xD8
void fn_2_74564(s32 a) {
    s32 i;
    s32 hits;
    s32 total;
    s32 cur;
    cur = lbl_2_bss_F410;
    if ((lbl_803C66B0[7] == 1) ? 1 : 0) {
        hits = 0;
        total = 0;
        for (i = 0; i < 7; i++) {
            if (cur == i) {
                total++;
                hits += fn_80042DA8(a, i + 3, 0xE) != 0;
            }
        }
        hits += fn_80042DA8(a, 0x20, 0xA) != 0;
        if (hits == total + 1) {
            fn_80062674(0);
            lbl_803C66B0[7] = 2;
            fn_800625A4(0, 0x57);
        }
    }
}

// fn_2_7EF68, size:0xC8
void fn_2_7EF68(u8* o, s32 index) {
    s32 i;
    for (i = 0; i < 9; i++) {
        if (i == ((s32*)lbl_2_bss_F468)[index]) {
            *(u32*)(((u8**)lbl_80371C30)[(0x22 + *(u16*)(o + 0x14) + i + index * 9) * 2] + 0x54) |= 2;
        }
    }
}

// fn_2_79688, size:0xDC
void fn_2_79688(u8* o, s32 index) {
    s32 i;
    if (lbl_803C66B0[index + 0xD] != 0) {
        return;
    }
    for (i = 0; i < 9; i++) {
        ((u8**)lbl_80371C30)[(0x46 + *(u16*)(o + 0x14) + i + index * 9) * 2][0x68] = 4;
    }
    *(s32*)(((u8**)lbl_80371C30)[(0x95 + *(u16*)(o + 0x14) + index) * 2] + 0x5C) = 0xA0000;
    ((u8**)lbl_80371C30)[(0x95 + *(u16*)(o + 0x14) + index) * 2][0x68] = 1;
}

// fn_2_7EE7C, size:0xEC
void fn_2_7EE7C(u8* o, s32 index) {
    s32 v = ((s32*)lbl_2_bss_F468)[index];
    if (lbl_2_bss_F468[index + 0x41] != 0) {
        *(u32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + 0x22 + v + index * 9) * 2] + 0x54) &= ~2;
    } else {
        *(u32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + 0x22 + v + index * 9) * 2] + 0x54) |= 2;
    }
    fn_2_74F40(o, index);
    lbl_803C66B0[index + 0x5D] = 0;
    if (lbl_2_bss_F468[index + 0x59] != 0) {
        fn_800625A4(index, 0x1A);
    }
}

// fn_2_80500, size:0xDC
void fn_2_80500(u8* o, s32 index) {
    u8* p = lbl_803C66B0 + index;
    if ((*(p += 0xD) == 0) ? 1 : 0) {
        u8 b = ((s8)lbl_8034E9A0[0x46F8] == 0) ? 1 : 0;
        *(s32*)(((u8**)(lbl_80371C30 + 0x3D8))[*(u16*)(o + 0x14) * 2] + 0x5C) = b << 16;
        *(s32*)(((u8**)(lbl_80371C30 + 0xC8))[*(u16*)(o + 0x14) * 2] + 0x5C) = (b + 4) << 16;
        fn_800626EC(index);
        *p = 1;
    }
    if (*p == 1) {
        fn_80062674(index);
        *p = 2;
        ((u8*)&g_d_GameSettings)[0x10] = 0;
    }
}

// fn_2_7E860, size:0x114
void fn_2_7E860(s32 a, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8(a, index + 0xC, 0xA) != 0;
        n += fn_80042DA8(a, index + 0xE, 0xE) != 0;
        n += fn_80042DA8(a, index + 0x12, 0xA) != 0;
        n += fn_80042DA8(a, index + 0x1C, 0x14) != 0;
        n += fn_80042DA8(a, index + 0x6A, 0x1E) != 0;
        if (n == 5) {
            fn_80062674(index);
            lbl_803C66B0[index + 0xD] = 2;
        }
    }
}

// fn_2_7A460, size:0x158
void fn_2_7A460(u8* o, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 1) ? 1 : 0) {
        s32 n = 0;
        n += fn_80042DA8((s32)o, index, 0x28) != 0;
        n += fn_80042DA8((s32)o, index + 2, 0x28) != 0;
        n += fn_80042DA8((s32)o, index + 0x85, 0x1E) != 0;
        n += fn_80042DA8((s32)o, index + 0x1C, 0x1E) != 0;
        n += fn_80042DA8((s32)o, index + 0x6A, 0x32) != 0;
        if (n == 5) {
            *(u32*)(((u8**)lbl_80371C30)[(0xC + *(u16*)(o + 0x14) + index) * 2] + 0x54) &= ~2;
            *(u32*)(((u8**)lbl_80371C30)[(0x12 + *(u16*)(o + 0x14) + index) * 2] + 0x54) &= ~2;
            fn_80062674(index);
            lbl_803C66B0[index + 0xD] = 2;
        }
    }
}

// fn_2_73BF0, size:0xCC
s32 fn_2_73BF0(s32 arg0) {
    s32 r;
    if (lbl_2_bss_A840 == 0 && arg0 == 6) {
        if (lbl_8034E9A0[0x4752] != 0) { r = 0x36; } else { r = 0x36; }
    } else if (lbl_2_bss_A840 == 6 && arg0 == 0) {
        if (lbl_8034E9A0[0x4752] != 0) { r = 8; } else { r = 0; }
    } else if (lbl_2_bss_A840 <= arg0) {
        if (lbl_8034E9A0[0x4752] != 0) { r = 0x17; } else { r = 0xF; }
    } else if (lbl_2_bss_A840 > arg0) {
        if (lbl_8034E9A0[0x4752] != 0) { r = 0x26; } else { r = 0x1E; }
    } else r = arg0;
    return r;
}

extern u8 lbl_2_data_2AF4C[];
extern u8 lbl_803C6724[];
extern void fn_2_7308C(void);

// fn_2_73758, size:0x144
void fn_2_73758(void) {
    u8* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2AF4C);
    for (i = 0; i < 8; i++) {
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(obj + 0x14) + i + 4) * 2] + 0x5C) = *(s8*)(lbl_803C6724 + 3 + i) << 16;
    }
    lbl_803CBCD8[5] = 0;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_2_7308C;
}

// fn_2_7A5B8, size:0xDC
void fn_2_7A5B8(u8* o, s32 index) {
    if ((lbl_803C66B0[index + 0xD] == 0) ? 1 : 0) {
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + index) * 2] + 0x5C) = 0x140000;
        *(s32*)(((u8**)lbl_80371C30)[(2 + *(u16*)(o + 0x14) + index) * 2] + 0x5C) = 0x140000;
        ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + index) * 2][0x68] = 1;
        ((u8**)lbl_80371C30)[(2 + *(u16*)(o + 0x14) + index) * 2][0x68] = 1;
        *(s32*)(((u8**)lbl_80371C30)[(133 + *(u16*)(o + 0x14) + index) * 2] + 0x5C) = 0x140000;
        ((u8**)lbl_80371C30)[(133 + *(u16*)(o + 0x14) + index) * 2][0x68] = 1;
        *(s32*)(((u8**)lbl_80371C30)[(28 + *(u16*)(o + 0x14) + index) * 2] + 0x5C) = 0x140000;
        ((u8**)lbl_80371C30)[(28 + *(u16*)(o + 0x14) + index) * 2][0x68] = 1;
        *(s32*)(((u8**)lbl_80371C30)[(106 + *(u16*)(o + 0x14) + index) * 2] + 0x5C) = 0x1E0000;
        ((u8**)lbl_80371C30)[(106 + *(u16*)(o + 0x14) + index) * 2][0x68] = 1;
        if (g_d_GameSettings.GameModeSelected != 5 || index == 0) {
            *(u32*)(((u8**)lbl_80371C30)[(147 + *(u16*)(o + 0x14) + index) * 2] + 0x54) &= ~2;
        }
        fn_800626EC(index);
        lbl_803C66B0[index + 0xD] = 1;
    }
}

extern u8 lbl_2_data_2DC84[];
extern u8 lbl_2_data_2DC8C[];
extern void fn_2_845A8(void);

// fn_2_84FA8, size:0x160
void fn_2_84FA8(void) {
    u8* obj;
    s32 i;
    s8 v;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2DC8C);
    for (i = 0; i < 6; i++) {
        if (lbl_80361B20[0xF5] == 0 && lbl_2_data_2DC84[i] == 1) {
            v = 6;
        } else {
            v = lbl_2_data_2DC84[i];
        }
        fn_800363D8(obj, i + 6, 2, 0x1E, v);
    }
    if (lbl_80361B20[0xF5] == 0 && lbl_2_data_2DC84[*(s32*)((u8*)&lbl_2_bss_F410 + 0x44)] == 1) {
        v = 0x12;
    } else {
        v = lbl_2_data_2DC84[*(s32*)((u8*)&lbl_2_bss_F410 + 0x44)];
    }
    if (*(s32*)((u8*)&lbl_2_bss_F410 + 0x44) != 0) {
        fn_800363D8(obj, 0, 1, 0x20, v);
    }
    lbl_803CBCD8[4] = 0;
    *(s16*)(obj + 0x18) = 0;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_2_845A8;
}

// fn_2_851A8, size:0x168
void fn_2_851A8(void) {
    switch (*(s16*)(((u8**)&lbl_803CC1B8)[0] + 0x10)) {
    case 0:
        fn_800625A4(0, 0);
        *(s16*)(lbl_803CC1B8 + 0x10) = *(s16*)(lbl_803CC1B8 + 0x10) + 1;
    case 1:
        if (lbl_803C66B0[1] == 0) {
            lbl_803C66B0[1] = 1;
            fn_800626EC(0);
            switch (lbl_803C66B0[0x5D]) {
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                fn_80062674(0);
                break;
            }
        }
        if (lbl_803C66B0[1] == 1) {
            switch (lbl_803C66B0[0x5D]) {
            case 0:
            case 1:
            case 2:
                lbl_803C66B0[1] = 2;
                fn_80062674(0);
                break;
            case 3:
                if (lbl_2_bss_F410 == 0) {
                    lbl_803C66B0[1] = 2;
                    *(s16*)((u8*)fn_800B0A5C_insertQueue((void*)fn_2_85160, *(u16*)(lbl_803CC1B8 + 0x12)) + 0x10) = 0xB4;
                } else {
                    fn_800625A4(0, 4);
                }
                break;
            case 4:
                lbl_803C66B0[1] = 2;
                fn_80062674(0);
                ((void (*)(void))fn_800B0A14_removeQueue)();
                break;
            }
        }
        break;
    }
}

extern u8 lbl_800EFBA4[];
extern u32 sndFXStartEx(u32 fid, u8 vol, u8 pan, u8 studio);

// fn_2_85310, size:0x1A0
s32 fn_2_85310(u16 a, u16 b, u16 c) {
    s32 r = 0;
    if (c & 3) {
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        if (lbl_2_bss_F410 == 1) {
            fn_800625A4(0, 1);
        } else {
            fn_800625A4(0, 2);
        }
        lbl_2_bss_F410 ^= 1;
    } else if (b & 0x100) {
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        fn_800625A4(0, 3);
        r = 1;
    } else if (b & 0x200) {
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        if (lbl_2_bss_F410 == 1) {
            fn_800625A4(0, 3);
            r = 1;
        } else {
            fn_800625A4(0, 2);
            lbl_2_bss_F410 = 1;
        }
    }
    if ((c | (a | b)) != 0) {
        ((s32*)&lbl_2_bss_F410)[1] = 0x258;
    } else {
        if (--((s32*)&lbl_2_bss_F410)[1] == 0) {
            fn_800625A4(0, 3);
            r = 1;
        }
    }
    return r;
}

extern s8 lbl_2_data_2E2EC;

// fn_2_837D8, size:0x19C
void fn_2_837D8(u8* o) {
    s32 n;
    s32 v;
    if ((lbl_803C66B0[0x2B] == 0) ? 1 : 0) {
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 4;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 0;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x10))[0x68] = 1;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x28))[0x68] = 1;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x18))[0x68] = 1;
        *(s32*)(((u8**)(lbl_80371C30 + 0x20))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0x280000;
        ((u8**)(lbl_80371C30 + 0x20))[*(u16*)(o + 0x14) * 2][0x68] = 4;
        fn_800626EC(0);
        lbl_803C66B0[0x2B] = 1;
    }
    if (lbl_803C66B0[0x2B] == 1) {
        n = fn_80042DA8((s32)o, 0, 0xA) != 0;
        if (n + (fn_80042DA8((s32)o, 4, 0x14) != 0) == 2) {
            v = *(s32*)((u8*)&lbl_2_bss_F410 + 0x44);
            if (lbl_80361B20[0xF5] == 0 && v != 0) {
                v -= 1;
            }
            lbl_2_data_2E2EC = v;
            ((void (*)(s32, s8*))fn_80062674)(0, &lbl_2_data_2E2EC);
            lbl_803C66B0[0x2B] = 2;
        }
    }
}

extern void fn_80062674(s32 index);
extern void fn_800626EC(s32 index);

// fn_2_78F78, size:0x1B4
void fn_2_78F78(u8* o, s32 i) {
    u8* e = lbl_803C66B0 + i;
    s32 ok = (*(e += 0xD) == 0);
    if (ok) {
        *(u32*)(((u8**)lbl_80371C30)[(0xA + *(u16*)(o + 0x14) + i) * 2] + 0x54) |= 2;
        ((u8**)lbl_80371C30)[(0xA + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
        ((u8**)lbl_80371C30)[(0x1E + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
        *(s32*)(((u8**)lbl_80371C30)[(0x89 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0;
        ((u8**)lbl_80371C30)[(0x89 + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
        *(s32*)(((u8**)lbl_80371C30)[(0x8D + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0;
        ((u8**)lbl_80371C30)[(0x8D + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
        ((u8**)lbl_80371C30)[(0x6A + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        if (((u8*)&g_d_GameSettings)[7] != 5) {
            *(s16*)(((u8**)lbl_80371C30)[(0x8F + *(u16*)(o + 0x14) + i) * 2] + 0x64) = 8;
            *(s32*)(((u8**)lbl_80371C30)[(0x8F + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0;
            ((u8**)lbl_80371C30)[(0x8F + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
        }
        fn_800626EC(i);
        *e = 1;
    }
    if (*e == 1) {
        fn_80062674(i);
        *e = 2;
    }
}

extern u8 lbl_800FE5D4[];
extern u8 lbl_2_data_2B3A4[];
extern u8 starMissionCompletionTracker[];

// fn_2_73994, size:0x1C0
void fn_2_73994(u8* o, s32 i) {
    s32 a;
    s32 b;
    u8 x;
    u8 y;
    if (((u8*)&g_d_GameSettings)[7] != 5) {
        b = lbl_803C6724[i];
        a = lbl_800FE5D4[((s32*)((u8*)&lbl_2_bss_F410 + 0x10))[i]];
        b = lbl_800FE5D4[b];
    } else if (i != 0) {
        b = ((s8*)starMissionCompletionTracker)[0x441F];
        a = b;
    } else {
        a = b = starMissionCompletionTracker[0x441D];
    }
    x = lbl_8034E9A0[0x34 + (a / 9) * 0x5A0 + (a % 9) * 0xA0];
    y = lbl_8034E9A0[0x34 + (b / 9) * 0x5A0 + (b % 9) * 0xA0];
    *(s32*)(((u8**)lbl_80371C30)[(0x82 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = lbl_2_data_2B3A4[x] << 16;
    *(s32*)(((u8**)lbl_80371C30)[(0x7E + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = lbl_2_data_2B3A4[x] << 16;
    fn_800363D8(o, i + 0x89, 1, 3, lbl_2_data_2B3A4[x]);
    fn_800363D8(o, i + 0x8B, 1, 3, lbl_2_data_2B3A4[y]);
}

// fn_2_83974, size:0x168
void fn_2_83974(u8* o) {
    s32 n;
    if ((lbl_803C66B0[0x2B] == 0) ? 1 : 0) {
        *(s32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) = 0xA0000;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 1;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 0;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x10))[0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x18))[0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x28))[0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x20))[0x68] = 1;
        fn_800626EC(0);
        lbl_803C66B0[0x2B] = 1;
    }
    if (lbl_803C66B0[0x2B] == 1) {
        n = fn_80042DA8((s32)o, 0, 0x14) != 0;
        n += fn_80042DA8((s32)o, 2, 0) != 0;
        n += fn_80042DA8((s32)o, 5, 0) != 0;
        n += fn_80042DA8((s32)o, 3, 0) != 0;
        if (n == 4) {
            lbl_2_data_2E2EC = *(s32*)((u8*)&lbl_2_bss_F410 + 0x44);
            fn_80062674(0);
            lbl_803C66B0[0x2B] = 2;
        }
    }
}

extern u8 lbl_8037169C[];
extern void changeScene(s32 a, s32 b);

// fn_2_7463C, size:0x1C0
s32 fn_2_7463C(u8* o) {
    s32 i;
    s32 cur = lbl_2_bss_F410;
    s32 ok = (lbl_803C66B0[7] == 0);
    if (ok) {
        for (i = 0; i < 7; i++) {
            if (cur == i) {
                *(u32*)(((u8**)lbl_80371C30)[(3 + *(u16*)(o + 0x14) + i) * 2] + 0x54) |= 2;
                *(s32*)(((u8**)lbl_80371C30)[(3 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0;
                ((u8**)lbl_80371C30)[(3 + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
                *(s32*)(((u8**)lbl_80371C30)[(0x18 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0;
                ((u8**)lbl_80371C30)[(0x18 + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
            } else {
                *(s32*)(((u8**)lbl_80371C30)[(0x18 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0;
                ((u8**)lbl_80371C30)[(0x18 + *(u16*)(o + 0x14) + i) * 2][0x68] = 0;
                *(u32*)(((u8**)lbl_80371C30)[(3 + *(u16*)(o + 0x14) + i) * 2] + 0x54) &= ~2;
            }
        }
        if (lbl_8037169C[0x10] != 0) {
            changeScene(1, 6);
        }
        *(s32*)(((u8**)(lbl_80371C30 + 0x100))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)(lbl_80371C30 + 0x100))[*(u16*)(o + 0x14) * 2][0x68] = 1;
        ok = ((s32 (*)(s32))fn_800626EC)(0);
        lbl_803C66B0[7] = 1;
    }
    return ok;
}

extern u8 lbl_2_data_2E02C[];
extern void fn_2_82EC0(void);

// fn_2_834F0, size:0x1B4
void fn_2_834F0(void) {
    u8* obj;
    s32 i;
    fn_80034E20(obj = lbl_803CC1B8, lbl_2_data_2E02C);
    for (i = 0; i < 4; i++) {
        if (lbl_2_bss_F468[0x57] < i) {
            fn_800363D8(obj, i + 3, 1, 0x6B, 4);
        } else {
            fn_800363D8(obj, i + 3, 1, 0x6B, i);
        }
    }
    *(s32*)(((u8**)(lbl_80371C30 + 0x60))[*(u16*)(obj + 0x14) * 2] + 0x5C) = 0;
    if (lbl_80361B20[0xF4] != 0) {
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(obj + 0x14) * 8 + 0x8) + 0x64) = 0x22;
        *(s32*)(*(u8**)(lbl_80371C30 + *(u16*)(obj + 0x14) * 8 + 0x58) + 0x5C) = 0x40000;
    } else {
        *(s16*)(*(u8**)(lbl_80371C30 + *(u16*)(obj + 0x14) * 8 + 0x8) + 0x64) = 0x21;
        *(s32*)(*(u8**)(lbl_80371C30 + *(u16*)(obj + 0x14) * 8 + 0x58) + 0x5C) = 0;
    }
    if (lbl_80361B20[0xE4] != 0) {
        *(u32*)(((u8**)(lbl_80371C30 + 0x48))[*(u16*)(obj + 0x14) * 2] + 0x54) |= 2;
        ((u8**)(lbl_80371C30 + 0x48))[*(u16*)(obj + 0x14) * 2][0x68] = 1;
        fn_800363D8(obj, 9, 1, 0x27, 0);
    }
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_2_82EC0;
}

// fn_2_80C2C, size:0x1E0
void fn_2_80C2C(u8* o, s32 i) {
    u8* e = lbl_803C66B0 + i;
    s32 ok = (*(e += 0xD) == 0);
    if (ok) {
        if ((lbl_803C66B0 + i)[0x55] != 0) {
            fn_80062674(i);
            (lbl_803C66B0 + i)[0x5D] = 2;
        }
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0x140000;
        *(s32*)(((u8**)lbl_80371C30)[(2 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0x140000;
        ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        ((u8**)lbl_80371C30)[(2 + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        *(s32*)(((u8**)lbl_80371C30)[(4 + *(u16*)(o + 0x14) + i) * 2] + 0x5C) = 0x1E0000;
        ((u8**)lbl_80371C30)[(4 + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        ((u8**)lbl_80371C30)[(0x89 + *(u16*)(o + 0x14) + i) * 2][0x68] = 1;
        ((u8**)lbl_80371C30)[(0x80 + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        ((u8**)lbl_80371C30)[(0x78 + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        ((u8**)lbl_80371C30)[(0x7C + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        ((u8**)lbl_80371C30)[(0x97 + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        ((u8**)lbl_80371C30)[(0xAC + *(u16*)(o + 0x14) + i) * 2][0x68] = 4;
        *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x420) + 0x54) &= ~2;
        fn_800626EC(i);
        *e = 1;
    }
}

// fn_2_84194, size:0x1F4
void fn_2_84194(u8* o) {
    s32 n;
    if ((lbl_803C66B0[0x2B] == 0) ? 1 : 0) {
        *(s32*)(((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2] + 0x5C) = 0xA0000;
        *(s32*)(((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0xA0000;
        ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2][0x68] = 4;
        ((u8**)(lbl_80371C30 + 8))[*(u16*)(o + 0x14) * 2][0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x10))[0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x18))[0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x28))[0x68] = 4;
        (*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x20))[0x68] = 4;
        fn_800626EC(0);
        lbl_803C66B0[0x2B] = 1;
    }
    if (lbl_803C66B0[0x2B] == 1) {
        n = fn_80042DA8((s32)o, 0, 0) != 0;
        n += fn_80042DA8((s32)o, 1, 0) != 0;
        n += fn_80042DA8((s32)o, 2, 0) != 0;
        n += fn_80042DA8((s32)o, 3, 0) != 0;
        n += fn_80042DA8((s32)o, 5, 0) != 0;
        if (n == 5) {
            lbl_2_data_2E2EC = *(s32*)((u8*)&lbl_2_bss_F410 + 0x44);
            fn_80062674(0);
            lbl_803C66B0[0x2B] = 2;
            lbl_2_data_2E2EC = -1;
            fn_800B0A14_removeQueue(fn_80034CEC(o));
        }
    }
}

extern void fn_2_7630C(u8* o, s32 a);

// fn_2_802EC, size:0x214
void fn_2_802EC(u8* o) {
    s32 n;
    if ((lbl_803C66B0[0xE] == 0) ? 1 : 0) {
        *(u32*)(((u8**)(lbl_80371C30 + 0x408))[*(u16*)(o + 0x14) * 2] + 0x54) |= 2;
        *(s32*)(((u8**)(lbl_80371C30 + 0x408))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)(lbl_80371C30 + 0x408))[*(u16*)(o + 0x14) * 2][0x68] = 1;
        *(u32*)(((u8**)(lbl_80371C30 + 0x420))[*(u16*)(o + 0x14) * 2] + 0x54) &= ~2;
        ((u8**)(lbl_80371C30 + 0x420))[*(u16*)(o + 0x14) * 2][0x68] = 0;
        *(s32*)(((u8**)(lbl_80371C30 + 0x3E8))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)(lbl_80371C30 + 0x3E8))[*(u16*)(o + 0x14) * 2][0x68] = 1;
        *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(o + 0x14) * 8 + 0x4C0) + 0x54) |= 2;
        *(s32*)(((u8**)(lbl_80371C30 + 0x430))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)(lbl_80371C30 + 0x430))[*(u16*)(o + 0x14) * 2][0x68] = 1;
        *(s32*)(((u8**)(lbl_80371C30 + 0x450))[*(u16*)(o + 0x14) * 2] + 0x5C) = 0;
        ((u8**)(lbl_80371C30 + 0x450))[*(u16*)(o + 0x14) * 2][0x68] = 1;
        fn_2_7630C(o, 1);
        fn_2_74F40(o, 1);
        fn_800626EC(1);
        lbl_803C66B0[0xE] = 1;
    }
    if (lbl_803C66B0[0xE] == 1) {
        n = fn_80042DA8((s32)o, 0x81, 0x14) != 0;
        n += fn_80042DA8((s32)o, 0x7D, 0x14) != 0;
        n += fn_80042DA8((s32)o, 0x86, 0xA) != 0;
        n += fn_80042DA8((s32)o, 0x8A, 5) != 0;
        if (n == 4) {
            fn_80062674(1);
            lbl_803C66B0[0xE] = 2;
        }
    }
}
