#include "menus/auto_00_00001254_text.h"
#include "static/UnknownHomes_Static.h"
#include <string.h>

extern void fn_800625A4(u8, s32);

extern u8 lbl_803297E0[];
extern u8 lbl_803CB748[];
extern u8 lbl_2_bss_3A0[];
extern u8 lbl_803CBD24[];
extern void fn_8004D0F0(void);
extern s32 fn_8004CA6C(u16 buttons);
extern void fn_8004CC2C(void);
extern u8 lbl_80108EC4[];
extern void fn_800628D4(s32 id);
extern void fn_80050FE8(s32 p0, s32 p1, s32 p2, s32 p3, s32 arg4, s32 lockMode);
extern void fn_2_7265C(void);
extern s16 lbl_2_bss_3E4[];
extern s16 fn_80067AC8(s16 id, s8 col);
extern u8 lbl_800EF808[];
extern void fn_80021AC8(void);
extern void fn_2_74D8C(void);
extern s8 lbl_80108DB8[];
extern u8 lbl_803CBBC4[];
extern u8 lbl_803C50E8[];
extern u8 lbl_800FEF70[];
extern u8 lbl_2_bss_758;
extern void fn_2_15A90(s32* value, s32 min, u8 max);
extern void fn_2_836A4(void);
extern void fn_2_85108(void);
extern u8 lbl_2_data_720[];
extern void fn_800216F8(s32 group, void* callback);
extern void fn_8006285C(void);
extern void fn_8006496C(void);
extern void fn_2_82E58(void);
extern u8 lbl_2_bss_E8CC[];
extern u8 lbl_2_bss_DCE8[];
extern u8 lbl_803C6028[];
extern s32 fn_80050760(s32 p, s32 held, s32 pressed, s32 dirs, s32 mode);
extern u8 lbl_2_bss_20[];
extern u8 lbl_2_data_180[];
extern u8* lbl_803CC1B8;
extern u8 lbl_803CBCE0[];
extern u8 lbl_803C6714[];
extern void initializeUnknown(void);
extern void fn_80062764(void* task);
extern s32 fn_80022B68(void);
extern void fn_2_12988(void);
extern s32 fn_800697B0(void);
extern void fn_8003F23C(void);
extern u8 lbl_2_bss_3A8[];
extern void fn_80066EAC(u8 team);
extern u8 lbl_803CBCD8[];
extern u8 lbl_80361B20[];
extern u8 lbl_2_data_130C[];
extern void fn_2_328(void);
extern void fn_2_2DC(void);
extern s32 fn_80062578(void);
extern s32 fn_80050F78(s32 arg);
extern void fn_2_19F2C(void);
extern void fn_80062A74(void);
extern s32 fn_80021410(void);
extern void fn_80035CA4(s32 id);
extern void fn_2_11A0(u16 value);
extern void fn_80021AC0(s32 team, s32 slot);
extern u8 lbl_2_data_E64[];
extern u8 lbl_80366158[];
extern u8 lbl_2_bss_3E0[];
extern void fn_800649BC(void);
extern void fn_800671FC(void);
extern void fn_800684A4(void);
extern void fn_80069854(void);
extern void fn_80067F70(u8 team);
extern void characterSelectScreen(u8 team);
extern void fn_2_72630(void);
extern void fn_800678CC(s32 team);
extern void unsure_FillRosterPositions(u8 team);
extern MenuCharEntry lbl_800E8558[54];

extern void fn_2_7DDC(void);
extern void fn_2_3624(u8 port);
extern void fn_2_104FC(u16 port);
extern void fn_2_87A8(void);
extern void fn_2_7504(void);

extern u8 lbl_8034E9A0[];
extern u8 lbl_8034E978[];
extern u8 lbl_803C66B0[];
extern u8 lbl_803C5EA4[];

extern u32 lbl_803CB750[];

extern u8 lbl_2_bss_F468[];

typedef struct MenuEntrySlot {
    u8* object;
    u32 pad;
} MenuEntrySlot;

extern MenuEntrySlot lbl_80371C30[];

extern u8 lbl_2_bss_100B4;
extern u8 lbl_2_bss_F410[];
extern u8 lbl_800FDE84[];
extern void fn_800506E8(s32, s32, s32);
extern void fn_80050138(s32, s32, s32, s32, s32, s32);
extern u8 lbl_80353B98[];
extern u8 lbl_80354720[];
extern u8 lbl_803CB8D0[];
extern u8 lbl_800E8754[];
extern s16 randRange_FUN_80042bf0(s32, s32);
extern u8 lbl_80109038[];
extern s32 fn_80067B40(s32, u8, s32);
extern u8 lbl_80108EDC[];
extern u8 inMemRoster[];
extern u8 lbl_800EFBA4[];
extern int sndFXStartEx(int, int, int, int);
extern void fn_8004EEF4(s32, s32, s32, s32, s32);
extern u8 lbl_803C6724[];
extern u8 lbl_2_data_E88[];
extern void fn_800670A0(u8);
extern u8 starMissionCompletionTracker[];
extern u8 lbl_2_data_3CE0[];
extern u8 lbl_8037169C[];
extern u8* lbl_803CBBCC[];
extern void fn_800203E0(s32, s8);
extern u8 lbl_2_bss_100B8[];
extern void fn_2_16A74(s32, s32);
extern u8* lbl_803CBBCC[];

// fn_2_1D54, size:0x70
void fn_2_1D54(s32* selection, u8 controller, s32 count) {
    u8* controls = lbl_8034E9A0;
    u16 buttons;
    controls += controller * 6;
    buttons = *(u16*)(controls + 0x4730);
    if (buttons & 8) {
        (*selection)--;
        if (*selection < 0) {
            *selection = count - 1;
        }
    } else if (buttons & 4) {
        (*selection)++;
        if (*selection == count) {
            *selection = 0;
        }
    }
}

// fn_2_6138, size:0x68
void fn_2_6138(void) {
    fn_800625A4(0, 19);
    fn_800625A4(1, 19);
    lbl_2_bss_F468[0x4F] = 0;
    lbl_2_bss_F468[0x2E] = 0;
    lbl_2_bss_100B4 = 1;
    *(s16*)(lbl_803CBBCC[0] + 4) = 8;
}

// fn_2_35D0, size:0x54
s32 fn_2_35D0(u8 index) {
    u8* flag = (u8*)((u32)lbl_2_bss_F468 + 0x45 + index);
    if (*flag != 0) {
        *flag = 0;
        sndFXRelated(0x200);
        return 1;
    }
    return 0;
}

// fn_2_112F4, size:0x4C
s32 fn_2_112F4(void* menu, s32 item, s32 index, const u16* values, s16 value) {
    u8* object = lbl_80371C30[*(u16*)((u8*)menu + 0x14) + item].object;
    if ((s32)(*(u32*)(object + 0x5C) >> 16) == values[index + 1] - 1) {
        *(s16*)(object + 0x64) = value;
        return 1;
    }
    return 0;
}

// fn_2_1258, size:0x48
u32 fn_2_1258(const void* base, u32 offset, s32 size) {
    u32 value = 0;
    switch (size) {
    case 1:
        value = *(const u8*)(offset + (u32)base);
        break;
    case 2:
        value = *(const u16*)((const u8*)base + offset);
        break;
    case 3:
        break;
    case 4:
        value = *(const u32*)((const u8*)base + offset);
        break;
    }
    return value;
}

// fn_2_8780, size:0x14
s32 fn_2_8780(s32 mode) {
    if (mode != 0) {
        return 0x13;
    }
    return 9;
}

// fn_2_8794, size:0x14
s32 fn_2_8794(s32 mode, s32 index) {
    if (mode != 0) index += 10;
    return index;
}

// fn_2_57E8, size:0x8
s8 fn_2_57E8(s32 unused, s32 value) {
    return value;
}

// fn_2_EC34, size:0x20
void fn_2_EC34(void) {
    if (lbl_2_bss_F468[0x56] == 0) lbl_2_bss_F468[0x56] = 1;
}

// fn_2_145C, size:0x30
s32 fn_2_145C(u16* a, u16* b) {
    for (;;) {
        u16 x = *a++;
        u16 y = *b++;
        if (x != y) {
            return 0;
        }
        if (x == 0x4000) {
            return 1;
        }
    }
}

// fn_2_1554, size:0x24
u32 fn_2_1554(void) {
    lbl_803CB750[0] = lbl_803CB750[0] * 0x5D588B65 + 1;
    return lbl_803CB750[0];
}

// fn_2_1328, size:0x2C
void fn_2_1328(u32* value, u16 increment) {
    u32 sum = *value + increment;
    if (sum > 0x7FFFFFFF) {
        *value = 0x7FFFFFFF;
        return;
    }
    *value = sum;
}

// fn_2_12A0, size:0x2C
void fn_2_12A0(s16* value, s32 increment) {
    s16 current = *value;
    if (current < 0x7FFF - (s16)increment) {
        *value = current + increment;
        return;
    }
    *value = 0x7FFF;
}

// fn_2_12CC, size:0x2C
void fn_2_12CC(u8* value, s32 increment) {
    u8 current = *value;
    if (current + (u16)increment > 0xFF) {
        *value = 0xFF;
        return;
    }
    *value = current + increment;
}

// fn_2_12F8, size:0x30
void fn_2_12F8(u16* value, s32 increment) {
    u16 current = *value;
    if (current + (u16)increment > 0xFFFF) {
        *value = 0xFFFF;
        return;
    }
    *value = current + increment;
}

// fn_2_1D28, size:0x2C
void fn_2_1D28(void) {
    lbl_8034E9A0[0x472A] = 0xFF;
    lbl_8034E9A0[0x4756] = 0;
    lbl_8034E9A0[0x4754] = 0;
    lbl_8034E9A0[0x4755] = 3;
    lbl_8034E9A0[0x48B3] = 0;
}

// fn_2_1254, size:0x4
void fn_2_1254(void) {
    return;
}

// fn_2_1DC4, size:0x4
void fn_2_1DC4(void) {
    return;
}

// fn_2_893C, size:0x4
void fn_2_893C(void) {
    return;
}

// fn_2_CCBC, size:0x24
void fn_2_CCBC(void) {
    fn_2_7DDC();
    fn_2_7504();
}

// fn_2_2BB8, size:0x164
void fn_2_2BB8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        s16* t = (s16*)lbl_2_data_E88;
        u8* pa = lbl_803C6724 + i * 9;
        u8* pb = lbl_80354720 + i * 0x24;
        s32* pw = (s32*)(lbl_8034E9A0 + 0x46E0 + i * 4);
        s32 j;
        for (j = 0; j < 9; j++) {
            s32 w = *pw;
            s32 v;
            if (w == 0) {
                v = t[0];
                pa[2] = v;
                pa[0x26] = (lbl_8034E9A0 + (v / 9) * 0x5A0 + (v % 9) * 0xA0 + w)[0x3B];
            } else {
                v = t[9];
                pa[2] = v;
                pa[0x26] = (lbl_8034E9A0 + (v / 9) * 0x5A0 + (v % 9) * 0xA0 + w)[0x3B];
            }
            pb[2] = j;
            pb[1] = j;
            pb[0] = j;
            t++;
            pa++;
            pb += 4;
        }
        fn_800670A0(i);
    }
}

// fn_2_3204, size:0x38
void fn_2_3204(void) {
    ((void (*)(u8, s32, s32))fn_2_2FC0)(lbl_803297E0[0xCF5F], 1, 1);
}

// fn_2_5F80, size:0x118
void fn_2_5F80(void) {
    s32 i;
    s32 j;
    s32 k;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            for (k = 0; k < 9; k++) {
                if (*(s8*)(lbl_80354720 + i * 0x24 + j * 4 + 2) == *(s8*)(lbl_80354720 + i * 0x24 + k * 4 + 2)) {
                    (lbl_803C6724 + i * 9 + j)[2] = *(s16*)(inMemRoster + i * 0x5A0 + k * 0xA0 + 0x24);
                }
            }
            (lbl_803C6724 + i * 9 + j)[0x14] = j;
        }
    }
}

// fn_2_6098, size:0x3C
void fn_2_6098(s32 index) {
    ((u32*)lbl_2_bss_F468)[(u8)index] = 9;
    fn_800625A4((u8)index, 0x17);
}

// fn_2_1BAC, size:0x88
void fn_2_1BAC(void) {
    memset(lbl_803C66B0 + 1, 0, 0x54);
    lbl_803C66B0[0x56] = 0;
    lbl_803C66B0[0x55] = 0;
    memset(lbl_803C5EA4, 0, 0x3A);
    memset(lbl_8034E9A0 + 0x489B, 0, 0x12);
    memset(lbl_8034E978, 0, 0x28);
}

// fn_2_60D4, size:0x64
s32 fn_2_60D4(u8 index) {
    u8* p;
    if (g_d_GameSettings.GameModeSelected != 5) {
        p = lbl_8034E9A0;
        p += index * 4;
        return *(s32*)(p + 0x46E0);
    }
    if (index != 0) {
        p = lbl_8034E9A0;
        p += index * 4;
        return *(s32*)(p + 0x46E0);
    }
    p = lbl_8034E9A0;
    p += index * 4;
    return *(s32*)(p + 0x46E0);
}

// fn_2_148C, size:0x6C
s32 fn_2_148C(u16* p) {
    s32 n = 0;
    for (;;) {
        u16 c = *p++;
        if (c & 0x4000) {
            switch (c & 0x3FFF) {
            case 0:
                goto done;
            case 2:
                n += 0xB;
                break;
            case 3:
                n += 0x16;
                break;
            }
        } else if (c & 0x8000) {
            n += 0x16;
        } else {
            n += 0xB;
        }
    }
done:
    return n;
}

// fn_2_120D0, size:0x9C
void fn_2_120D0(void) {
    lbl_8034E9A0[0x48AD] = 1;
    lbl_8034E9A0[0x4755] = 3;
    lbl_803C66B0[0] = 0;
    lbl_803C66B0[0x5A] = 0;
    lbl_803C66B0[0x59] = 0;
    lbl_8034E9A0[0x472A] = 0xFF;
    lbl_8034E9A0[0x48AF] = 1;
    lbl_8034E9A0[0x48B1] = 1;
    memset(lbl_803C66B0 + 1, 0, 6);
    lbl_8034E978[0x26] = 1;
    fn_800AD038(*(void**)(lbl_8034E9A0 + 0x46E8));
    ((u8*)&g_d_GameSettings)[0x10] = 0;
}

// fn_2_7D44, size:0x98
void fn_2_7D44(void) {
    if (*(u16*)(lbl_803CBBCC[0] + 6) == 9) {
        memset(lbl_2_bss_100B8, 0, 0x54);
    }
    lbl_8034E9A0[0x4755] = 1;
    lbl_2_bss_100B8[0x2D] = 4;
    fn_2_16A74(0, 0);
    fn_2_16A74(1, 0);
    fn_2_16A74(2, 0);
    fn_2_16A74(3, 0);
}

// fn_2_33BC, size:0xD0
s32 fn_2_33BC(void) {
    s32 r = 1;
    s32 i;
    s8 a = *(s8*)(starMissionCompletionTracker + 0x40BB);
    for (i = 1; i < 9; i++) {
        if (a == *(s8*)(starMissionCompletionTracker + 0x40BB + i * 6)) {
            r = 0;
        }
    }
    return r;
}

// fn_2_A62C, size:0xB4
s32 fn_2_A62C(void) {
    s32 i;
    s32 j;
    s32 a;
    for (i = 0; i < 9; i++) {
        a = *(s8*)(lbl_803C6724 + 2 + i);
        for (j = 0; j < 9; j++) {
            if (a == *(s8*)(lbl_803C6724 + 0xB + j) && a != 0xFF) {
                return 1;
            }
        }
    }
    return 0;
}

// fn_2_1216C, size:0xCC
void fn_2_1216C(void) {
    s8 buf[4];
    s8 k;
    memset(buf, 2, 4);
    if (((u8*)&g_d_GameSettings)[0x10] == 0) {
        k = *(s8*)(lbl_8034E9A0 + 0x46F8);
        buf[k] = 1;
        if (k == 0) {
            buf[1] = 2;
        } else {
            buf[0] = 2;
        }
    } else {
        buf[*(s8*)(lbl_8034E9A0 + 0x46F9)] = 1;
        buf[*(s8*)(lbl_8034E9A0 + 0x46F8)] = 1;
    }
    fn_8004EEF4(buf[0], buf[1], buf[2], buf[3], 1);
}

// fn_2_1C34, size:0xF4
void fn_2_1C34(u32 buttons) {
    switch ((u16)buttons) {
    case 0x100:
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        break;
    case 0x200:
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        break;
    case 3:
    case 0x20:
    case 0x40:
    case 0x400:
    case 0x800:
        break;
    }
}

// fn_2_1354, size:0x108
void fn_2_1354(SortEntry* e, s32 n, s32 descending) {
    u32 i;
    u32 j;
    SortEntry t;
    if (n >= 2) {
        if (descending == 0) {
            for (i = 0; i < (u32)n; i++) {
                j = i;
                while (j >= 1 && e[j - 1].value > e[j].value) {
                    t = e[j - 1];
                    e[j - 1] = e[j];
                    e[j] = t;
                    j--;
                }
            }
        } else {
            SortEntry t2;
            for (i = 0; i < (u32)n; i++) {
                j = i;
                while (j >= 1 && e[j - 1].value < e[j].value) {
                    t2 = e[j - 1];
                    e[j - 1] = e[j];
                    e[j] = t2;
                    j--;
                }
            }
        }
    }
}

// fn_2_A50C, size:0x120
s32 fn_2_A50C(void) {
    s32 i;
    s32 j;
    s32 a;
    for (i = 0; i < 9; i++) {
        a = *(s8*)(lbl_803C6724 + 2 + i);
        for (j = 0; j < 9; j++) {
            if (a == *(s8*)(lbl_803C6724 + 0xB + j)) {
                return 1;
            }
        }
    }
    return 0;
}

// fn_2_EC54, size:0x140
void fn_2_EC54(s32 index) {
    s32 i;
    s32 j;
    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (((u8*)&g_d_GameSettings)[0x10] == 1) {
        lbl_2_bss_100B8[0x2F] = 0;
        lbl_2_bss_100B8[0x2E] = 0;
    } else {
        lbl_2_bss_100B8[index + 0x2E] = 0;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 9; j++) {
            lbl_803C6724[i * 9 + 0x26 + j] = 0;
        }
        if (lbl_2_bss_F468[i + 0x45] != 0) {
            lbl_2_bss_F468[i + 0x45] = 0;
        }
    }
    if (lbl_2_bss_F468[0x56] == 0) {
        lbl_2_bss_F468[0x56] = 1;
    }
    lbl_2_bss_F468[0x2E] = 1;
    lbl_2_bss_100B4 = 1;
    *(s16*)(lbl_803CBBCC[0] + 4) = 8;
}

// fn_2_C324, size:0x160
s8 fn_2_C324(s32 id) {
    s32 r;
    s32 i;
    s32 j;
    s32 k;
    s16 v;
    r = -1;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            if (id == *(s16*)(lbl_80108EDC + i * 10 + j * 2)) {
                r = i;
                goto found;
            }
        }
    }
found:
    if (r == -1) {
        return r;
    }
    for (k = 0; k < 9; k++) {
        v = *(s16*)(inMemRoster + k * 0xA0 + 0x24);
        for (j = 0; j < 5; j++) {
            if (v == *(s16*)(lbl_80108EDC + r * 10 + j * 2) && v != id) {
                return r;
            }
        }
    }
    return -1;
}

// fn_2_A040, size:0x160
void fn_2_A040(s32 a, s32 b, u8 c, u8 d) {
    s16* t;
    s32 n;
    s32 i;
    s32 j;
    t = (s16*)(lbl_80108EDC + a * 10);
    if (t[b] != -1 && b < 4) {
        n = b + 1;
        if (n == 5 || t[n] == -1) {
            n = 0;
        }
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 9; j++) {
                if (*(s8*)(lbl_803C6724 + i * 9 + 2 + j) == t[n]) {
                    return;
                }
            }
        }
        (lbl_803C6724 + c * 9 + d)[2] = t[n];
        return;
    }
    (lbl_803C6724 + c * 9 + d)[2] = t[0];
}

// fn_2_B508, size:0x164
void fn_2_B508(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 0x36; i++) {
        for (j = 1; j < 9; j++) {
            if (*(s8*)(lbl_803C6724 + j + 0xB) == i) {
                lbl_8034E9A0[0x4757 + i] = 0;
                fn_800506E8(*(s8*)(lbl_8034E9A0 + 0x46F9), i, 0);
                fn_80067B40(1, i, 0);
            }
        }
    }
    for (i = 1; i < 9; i++) {
        lbl_80354720[0x26 + i * 4] = i;
        lbl_80353B98[0x26 + i * 4] = i;
        lbl_803C6724[0xB + i] = 0x36;
        lbl_803C6724[0x53 + i] = 0;
    }
}

// fn_2_52CC, size:0x178
#pragma opt_propagation off
void fn_2_52CC(void) {
    s32 i;
    s32 one = 1;
    lbl_2_bss_100B8[0x2E] = one;
    lbl_803C66B0[0x59] = one;
    ((s32*)lbl_2_bss_F468)[one] = 0xA;
    lbl_803C5EA4[0xE] = one;
    if (lbl_8034E9A0[0x4757 + *(s32*)(lbl_2_bss_F410 + 0x24)] != 0) {
        for (i = 0; i < 0x20; i++) {
            if (lbl_8034E9A0[0x4757 + lbl_800FDE84[i]] == 0) {
                *(s32*)(lbl_2_bss_F410 + 0x24) = lbl_800FDE84[i];
                break;
            }
        }
    }
    switch (*(s8*)(lbl_8034E9A0 + 0x46F9)) {
    case 0:
        fn_80050138(one, *(s32*)(lbl_2_bss_F410 + 0x24), -1, -1, -1, 0);
        break;
    case 1:
        fn_80050138(one, -1, *(s32*)(lbl_2_bss_F410 + 0x24), -1, -1, 0);
        break;
    case 2:
        fn_80050138(one, -1, -1, *(s32*)(lbl_2_bss_F410 + 0x24), -1, 0);
        break;
    case 3:
        fn_80050138(one, -1, -1, -1, *(s32*)(lbl_2_bss_F410 + 0x24), 0);
        break;
    }
}
#pragma opt_propagation reset

// fn_2_86EC, size:0x94
void fn_2_86EC(void) {
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_8037169C[0x12] == 0) {
        fn_800203E0(0xA, lbl_2_data_3CE0[starMissionCompletionTracker[0x441E]]);
    }
    fn_2_7DDC();
    fn_2_7504();
    lbl_2_bss_F468[0x56] = 0;
    *(u16*)(lbl_803CBBCC[0] + 4) = 2;
}

// fn_2_C698, size:0x144
void fn_2_C698(u8 a, s32 b) {
    s32 slot;
    if (g_d_GameSettings.GameModeSelected != 5) {
        u8 idx = b;
        u8* row = lbl_803C6724;
        u8* p;
        row += idx * 9;
        p = row;
        p += a;
        slot = *(s8*)(p + 2);
        lbl_8034E9A0[slot + 0x4757] = 1;
        if (((u8*)&g_d_GameSettings)[0x10] == 0 && idx != 0) {
            if (*(s8*)(lbl_8034E9A0 + 0x46F8) == 0) {
                fn_800506E8(1, slot, 1);
            } else {
                fn_800506E8(0, slot, 1);
            }
        } else {
            fn_800506E8(*(s8*)(lbl_8034E9A0 + idx + 0x46F8), slot, 1);
        }
        fn_80067B40(b, slot, 1);
        return;
    }
    {
        u8* r2 = lbl_803C6724;
        r2 += a;
        slot = *(s8*)(r2 + 2);
    }
    fn_800506E8(0, slot, 1);
    lbl_8034E9A0[slot + 0x4757] = 1;
    fn_80067B40(b, slot, 1);
}

// fn_2_1DC8, size:0x168
void fn_2_1DC8(void) {
    switch (*(u32*)lbl_2_bss_F410) {
    case 0:
        lbl_8034E9A0[0x4708] = 0;
        ((u8*)&g_d_GameSettings)[7] = 0;
        break;
    case 1:
        lbl_8034E9A0[0x4708] = 1;
        ((u8*)&g_d_GameSettings)[7] = 5;
        break;
    case 2:
        lbl_8034E9A0[0x4708] = 3;
        ((u8*)&g_d_GameSettings)[7] = 7;
        changeScene(4, 6);
        break;
    case 3:
        lbl_8034E9A0[0x4708] = 2;
        ((u8*)&g_d_GameSettings)[7] = 6;
        changeScene(4, 6);
        break;
    case 4:
        lbl_8034E9A0[0x4708] = 4;
        ((u8*)&g_d_GameSettings)[7] = 2;
        ((u8*)&g_d_GameSettings)[9] = 0;
        ((u8*)&g_d_GameSettings)[0xA] = 2;
        changeScene(4, 6);
        break;
    case 5:
        lbl_8034E9A0[0x4708] = 6;
        break;
    case 6:
        lbl_8034E9A0[0x4708] = 5;
        break;
    }
    *(s16*)(lbl_803CBBCC[0] + 4) = 5;
    fn_800625A4(0, 0x58);
}

// fn_2_6484, size:0x184
void fn_2_6484(void) {
    switch (lbl_2_bss_F468[0x33]) {
    case 0:
        if (lbl_803C66B0[0x5D] == 0 || lbl_803C66B0[0x5E] == 0) {
            if (lbl_2_bss_F468[0x34] == 0) {
                fn_800625A4(0, 0x1E);
                lbl_2_bss_F468[0x34] = 1;
            }
            lbl_2_bss_F468[0x33] = 1;
        }
        break;
    case 1:
        if (lbl_803C66B0[0x5D] == 0 || lbl_803C66B0[0x5E] == 0) {
            ((void (*)(void))fn_2_87A8)();
        }
        break;
    case 2:
        if (lbl_803C66B0[0x5D] == 0 || lbl_803C66B0[0x5E] == 0) {
            lbl_8034E9A0[0x472A] = 1;
            if (lbl_2_bss_F468[0x35] == 0) {
                lbl_2_bss_F468[0x2E] = 0;
                lbl_2_bss_100B4 = 1;
                *(s16*)(lbl_803CBBCC[0] + 4) = 8;
                fn_800625A4(0, 0x13);
                fn_800625A4(1, 0x13);
            } else {
                fn_800625A4(1, 0x12);
                *(s16*)(lbl_803CBBCC[0] + 4) = 2;
            }
            lbl_2_bss_F468[0x35] = 0;
            lbl_2_bss_F468[0x33] = 0;
        }
        break;
    }
}

// fn_2_6608, size:0x17C
void fn_2_6608(void) {
    s32 i;
    u8* p;
    if (lbl_2_bss_F468[0x59] != 0) {
        fn_2_3624(0);
    } else if (lbl_2_bss_F468[0x5A] != 0 && lbl_2_bss_100B8[0x2E] != 0 && ((u8*)&g_d_GameSettings)[0x10] == 0) {
        fn_2_3624(0);
    } else {
        fn_2_104FC(0);
    }
    if (((u8*)&g_d_GameSettings)[0x10] == 1) {
        if (lbl_2_bss_F468[0x5A] != 0) {
            fn_2_3624(1);
        } else {
            fn_2_104FC(1);
        }
    }
    if (lbl_2_bss_F468[0x56] != 0) {
        lbl_803C5EA4[9] = 0;
        lbl_803C5EA4[8] = 0;
        lbl_2_bss_100B8[0x31] = 0;
        lbl_2_bss_100B8[0x30] = 0;
        if (((u8*)&g_d_GameSettings)[0x10] == 0) {
            *(u32*)lbl_2_bss_F468 = 9;
            lbl_803C66B0[0x59] = 0;
        }
        for (i = 0; i < 2; i++) {
            if (lbl_2_bss_F468[i + 0x59] != 0) {
                ((void (*)(s32, s32))fn_800625A4)(i, 0x1B);
                lbl_2_bss_F468[i + 0x59] = 0;
            } else {
                ((void (*)(s32, s32))fn_800625A4)(i, 0xB);
            }
        }
    }
}

typedef struct RosterSlot {
    u8 pad0[0x24];
    s16 x24;
    u8 pad26[0xA0 - 0x26];
} RosterSlot;

// fn_2_9F70, size:0xD0
s32 fn_2_9F70(s8 team) {
    s32 result;
    u8 other;
    s32 i;
    s32 j;
    u8 v;
    other = (lbl_2_bss_F468 + 0x2F)[team ^ 1];
    switch (*(s32*)(lbl_2_bss_F468 + (s8)(lbl_2_bss_F468 + 0x2F)[team] * 4 + 0x10)) {
    case 1:
        result = 2;
        break;
    case 2:
        result = 1;
        break;
    case 3:
        result = 1;
        break;
    }
retry:
    for (i = 0; i < 9; i++) {
        v = ((RosterSlot*)(inMemRoster + (s8)other * 0x5A0))[i].x24;
        for (j = 0; j < 9; j++) {
            if (v == 0) {
                if (result == 1 || result == 2) {
                    return 3;
                }
                result = 2;
                goto retry;
            }
        }
    }
    return result;
}

// fn_2_6784, size:0x100
void fn_2_6784(void) {
    s32 i;
    s32 j;
    u8 dup;
    u8 v;
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            *(u32*)(lbl_8034E9A0 + 0x46E4) = 0;
            lbl_803C6724[0xB] = 0;
            lbl_803C6724[0x53] = 1;
            lbl_8034E9A0[lbl_803C6724[0xB] + 0x4757] = 1;
        } else {
            do {
                dup = 0;
                v = lbl_80109038[randRange_FUN_80042bf0(0, 9)];
                for (j = 0; j < i; j++) {
                    if (*(s8*)(lbl_803C6724 + j + 0xB) == v) {
                        dup = 1;
                    }
                }
            } while (dup);
            lbl_803C6724[i + 0xB] = v;
            lbl_803C6724[i + 0x53] = 1;
            lbl_8034E9A0[v + 0x4757] = 1;
        }
        lbl_80354720[i * 4 + 0x24] = i;
        lbl_80354720[i * 4 + 0x26] = i;
        lbl_80354720[i * 4 + 0x25] = i;
    }
}

static inline void fn_2_87A8_work(s32 prev) {
    u8* pad;
    u16 b;
    pad = (u8*)&lbl_803C77B8;
    pad += *(s8*)(lbl_8034E9A0 + 0x46F8) * 0x20;
    b = *(u16*)(pad + 4);
    if (b & 8) {
        if ((*(s32*)(lbl_2_bss_F410 + 0x4C) = prev - 1) < 0) {
            *(s32*)(lbl_2_bss_F410 + 0x4C) = 3;
        }
        if (prev != *(s32*)(lbl_2_bss_F410 + 0x4C)) {
            fn_800625A4(0, 0x20);
        }
        ((void (*)(u32))fn_2_1C34)(8);
    } else if (b & 4) {
        if ((*(s32*)(lbl_2_bss_F410 + 0x4C) = prev + 1) == 4) {
            *(s32*)(lbl_2_bss_F410 + 0x4C) = 0;
        }
        if (prev != *(s32*)(lbl_2_bss_F410 + 0x4C)) {
            fn_800625A4(0, 0x20);
        }
        ((void (*)(u32))fn_2_1C34)(4);
    } else if (*(u16*)(pad + 2) & 0x200) {
        lbl_2_bss_F468[0x33] = 2;
        lbl_2_bss_F468[0x34] = 0;
        lbl_2_bss_F468[0x35] = 1;
        lbl_803C5EA4[0xE] = 1;
        fn_800625A4(1, 0x1F);
        ((void (*)(u32))fn_2_1C34)(0x200);
    } else if (*(u16*)(pad + 2) & 0x100) {
        lbl_800E8754[3] = lbl_803CB8D0[prev];
        fn_800625A4(0, 0x21);
        lbl_2_bss_F468[0x33] = 2;
        lbl_2_bss_F468[0x34] = 0;
        lbl_2_bss_F468[0x35] = 0;
        ((void (*)(u32))fn_2_1C34)(0x100);
    }
}

// fn_2_87A8, size:0x194
void fn_2_87A8(void) {
    s32 prev = *(s32*)(lbl_2_bss_F410 + 0x4C);
    if (lbl_803C66B0[0x55] != 0 || lbl_803C66B0[0x56] != 0) {
        return;
    }
    fn_2_87A8_work(prev);
}

// NONMATCHING 80%: lo/hi register allocation and scheduling around the inlined fn_2_1554
#if NONMATCHING
// fn_2_14F8, size:0x5C
s32 fn_2_14F8(s32 a, s32 b) {
    s32 lo;
    s32 hi;
    if (a == b) {
        return a;
    }
    if (a <= b) {
        lo = a;
        hi = b;
    } else {
        lo = b;
        hi = a;
    }
    return (s32)(fn_2_1554() >> 16) % (hi - lo + 1) + lo;
}
#endif

// NONMATCHING 95%: (base + i + 9)[2] folded into one displacement; loop counters in other regs
#if NONMATCHING
// fn_2_A1A0, size:0xE8
void fn_2_A1A0(s32 count, s32 team) {
    s32 i;
    s32 v;
    u8* row = lbl_803C6724 + (u8)team * 9;
retry:
    while (lbl_8034E9A0[0x4757] != 0) {
    }
    for (i = 0; i < (u8)count; i++) {
        s32 idx = i + 2;
        if (g_d_GameSettings._10 == 0 && lbl_2_bss_100B8[0x2E] != 0) {
            v = (s8)(lbl_803C6724 + i)[2];
        } else {
            v = (s8)row[idx];
        }
        if (v == 0) {
            goto retry;
        }
        if (g_d_GameSettings._10 == 0 && lbl_2_bss_100B8[0x2E] != 0) {
            v = (s8)(lbl_803C6724 + i + 9)[2];
        } else {
            v = (s8)row[idx];
        }
        if (v == 0) {
            goto retry;
        }
    }
    (lbl_803C6724 + (u8)team * 9 + (u8)count)[2] = 0;
}
#endif

#define g_Pads ((MenuPad*)&lbl_803C77B8)

// fn_2_1A88, size:0x124
void fn_2_1A88(void) {
    s32 n;
    s32 i;
    lbl_8034E9A0[0x46F8] = 0;
    n = 1;
    for (i = 1; i < 4; i++) {
        if (g_Pads[i].err != -1) {
            lbl_8034E9A0[0x46F8 + n++] = i;
        }
    }
    while (n < 4) {
        ((s8*)lbl_8034E9A0)[0x46F8 + n++] = -1;
    }
}

// fn_2_348C, size:0x144
void fn_2_348C(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 6; i++) {
        s32 locked = g_d_GameSettings._1A[i] == 0;
        for (j = 0; j < 0x36; j++) {
            if (lbl_803CB748[i] == lbl_800E8558[j].lockId) {
                lbl_8034E9A0[0x4757 + j] = locked;
            }
        }
        lbl_803CB748[i] = lbl_803CB748[i];
    }
}

// NONMATCHING 85%: team kept in two regs (raw + clrlwi) differently; loop counter/pointer regs swapped
#if NONMATCHING
// fn_2_5184, size:0x148
void fn_2_5184(u8 team) {
    s32 i;
    s8* row;
    lbl_2_bss_F468[team + 0x3D] = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (lbl_2_bss_F468[team + 0x37] == 0) {
        fn_2_102C8(team);
        ((u32*)lbl_2_bss_F468)[team] = 9;
        return;
    }
    row = (s8*)(lbl_803C6724 + team * 9);
    for (i = 0; i < 9; i++) {
        if (*(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0) != row[2]) {
            lbl_8034E9A0[row[2] + 0x4757] = 0;
            fn_800506E8(*(s8*)(lbl_8034E9A0 + team + 0x46F8), row[2], 0);
            fn_80067B40(team, row[2], 0);
            row[2] = -1;
            row[0x4A] = 0;
            row[0x26] = 0;
        }
        row++;
    }
    lbl_2_bss_F468[team + 0x37] = 0;
    lbl_2_bss_F468[team + 0x43] = 1;
    fn_800625A4(team, 0x19);
}
#endif

// NONMATCHING 85%: register allocation/scheduling of the selection pointer; the trailing loop really never exits in the original
#if NONMATCHING
// fn_2_EAE0, size:0x154
void fn_2_EAE0(void) {
    s32 i;
    s32* sel;
    s32 port;
    for (i = 0; i < (g_d_GameSettings._10 == 1) + 1; i++) {
        if (lbl_803C5EA4[i + 8] != 0) {
            sel = (s32*)lbl_2_bss_F410 + 8 + i;
            if (lbl_8034E9A0[lbl_800FDE84[*sel] + 0x4757] != 0) {
                do {
                    do {
                        (*sel)++;
                        if (*sel == 0x36) {
                            *sel = 0;
                        }
                    } while (lbl_8034E9A0[lbl_800FDE84[*sel] + 0x4757] != 0);
                } while (((s32*)lbl_2_bss_F410)[8] == ((s32*)lbl_2_bss_F410)[9]);
            }
            for (;;) {
                port = *(s8*)(lbl_8034E9A0 + i + 0x46F8);
                if (*(s8*)(lbl_8034E9A0 + port + 0x46FC) != 0) {
                    port = *(s8*)(lbl_8034E9A0 + 0x46F8) == 0;
                }
                ((void (*)(s32*, u8, s32))fn_2_1D54)((s32*)lbl_2_bss_F410 + 8 + i, port, 0x36);
            }
        }
    }
}
#endif

// NONMATCHING 90%: team*4 index recomputed from the raw u8 param (clrlslwi) instead of reusing the clrlwi copy
#if NONMATCHING
// fn_2_CCE0, size:0x164
void fn_2_CCE0(u8 team) {
    s32 i;
    if (lbl_2_bss_F468[team + 0x37] != 0) {
        return;
    }
    for (i = 0; i < 9; i++) {
        s32 v = (s8)(lbl_803C6724 + team * 9)[i + 2];
        if (v == -1 || v == 0x36) {
            break;
        }
    }
    if (i == 9) {
        lbl_2_bss_F468[team + 0x37] = 1;
        ((s32*)lbl_2_bss_F468)[team + 2] = ((s32*)lbl_2_bss_F468)[team];
        ((s32*)lbl_2_bss_F468)[team] = 9;
        lbl_2_bss_F468[team + 0x41] = 0;
        fn_800625A4(team, 0x14);
        fn_80050138(1, -1, -1, -1, -1, 0);
    } else {
        ((s32*)lbl_2_bss_F468)[team + 2] = ((s32*)lbl_2_bss_F468)[team];
        ((s32*)lbl_2_bss_F468)[team] = (s8)(lbl_803C6724 + team * 9)[i + 0x14];
        fn_800625A4(team, 0xE);
    }
}
#endif

// NONMATCHING 98%: case 4 store scheduling (lbl_2_bss_3A0 address via addi in the original)
#if NONMATCHING
// fn_2_323C, size:0x180
void fn_2_323C(void) {
    switch (lbl_2_bss_3A0[0]) {
    case 0:
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        lbl_2_bss_3A0[0]++;
        break;
    case 1:
        switch (fn_8004CA6C(*(u16*)(lbl_8034E9A0 + lbl_803CBD24[4] * 6 + 0x472E))) {
        case 0:
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            fn_2_2FC0(0xA, 1, 1);
            lbl_803CBD24[4] = 0;
            fn_800625A4(0, 0x13);
            fn_800625A4(1, 0x13);
            changeScene(0xF, 6);
            lbl_2_bss_3A0[0] = 0;
            lbl_2_bss_F468[0x2E] = 0;
            lbl_2_bss_100B4 = 1;
            *(s16*)(lbl_803CBBCC[0] + 4) = 8;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            lbl_2_bss_3A0[0] = 0;
            lbl_803CBD24[4] = 0;
            lbl_803297E0[0xCF5F] = 0;
            *(s16*)(lbl_803CBBCC[0] + 4) = 2;
            break;
        }
        break;
    }
}
#endif

// NONMATCHING 75%: same instructions, store order/scheduling differs (second loop never runs, as in the original)
#if NONMATCHING
// fn_2_B324, size:0x1E4
void fn_2_B324(void) {
    s32 i;
    s32 base0 = *(s32*)(lbl_8034E9A0 + 0x46E0);
    s32 base1 = *(s32*)(lbl_8034E9A0 + 0x46E4);
    for (i = 0; i < 9; i++) {
        lbl_80354720[i * 4 + 0] = i;
        lbl_80354720[i * 4 + 0x24] = i;
        lbl_80354720[i * 4 + 1] = i;
        lbl_80354720[i * 4 + 0x25] = i;
        lbl_80354720[i * 4 + 2] = i;
        lbl_80354720[i * 4 + 0x26] = i;
        lbl_80354720[i * 4 + 3] = 1;
        lbl_80354720[i * 4 + 0x27] = 1;
        lbl_80353B98[i * 4 + 0] = i;
        lbl_80353B98[i * 4 + 0x24] = i;
        lbl_80353B98[i * 4 + 1] = i;
        lbl_80353B98[i * 4 + 0x25] = i;
        lbl_80353B98[i * 4 + 2] = i;
        lbl_80353B98[i * 4 + 0x26] = i;
        *(s16*)(inMemRoster + i * 0xA0 + 0x24) = base0 + i;
        *(s16*)(inMemRoster + 0x5A0 + i * 0xA0 + 0x24) = base1 + i;
    }
    for (; i < 9; i++) {
        lbl_80354720[i * 4 + 0] = i;
        lbl_80354720[i * 4 + 0x24] = i;
        lbl_80354720[i * 4 + 1] = -1;
        lbl_80354720[i * 4 + 0x25] = -1;
        lbl_80354720[i * 4 + 2] = -1;
        lbl_80354720[i * 4 + 0x26] = -1;
        lbl_80354720[i * 4 + 3] = -1;
        lbl_80354720[i * 4 + 0x27] = -1;
        lbl_80353B98[i * 4 + 0] = i;
        lbl_80353B98[i * 4 + 0x24] = i;
        lbl_80353B98[i * 4 + 1] = -1;
        lbl_80353B98[i * 4 + 0x25] = -1;
        lbl_80353B98[i * 4 + 2] = -1;
        lbl_80353B98[i * 4 + 0x26] = -1;
        *(s16*)(inMemRoster + i * 0xA0 + 0x24) = 0;
        *(s16*)(inMemRoster + 0x5A0 + i * 0xA0 + 0x24) = 0;
    }
}
#endif

// NONMATCHING 93%: random id kept as mr+extsh instead of extsh in place; loop regs rotated
#if NONMATCHING
// fn_2_FAA0, size:0x214
void fn_2_FAA0(s32 team) {
    s32 i;
    s32 g;
    s32 k;
    s16 id;
    s32 w = *(s32*)(lbl_8034E9A0 + (u8)team * 4 + 0x46E0);
    u8* row = lbl_803C6724 + (u8)team * 9;
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[2];
        if (v == -1 || v == 0x36) {
            do {
                id = randRange_FUN_80042bf0(0, 0x35);
            } while (lbl_8034E9A0[id + 0x4757] != 0);
            fn_80067B40(team, id, 1);
            for (g = 0; g < 9; g++) {
                for (k = 0; k < 5; k++) {
                    if (id == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                        s16* grp = (s16*)(lbl_80108EDC + g * 10);
                        lbl_8034E9A0[grp[1] + 0x4757] = 1;
                        lbl_8034E9A0[grp[2] + 0x4757] = 1;
                        lbl_8034E9A0[grp[3] + 0x4757] = 1;
                        lbl_8034E9A0[grp[4] + 0x4757] = 1;
                        id = grp[0];
                        goto found;
                    }
                }
            }
        found:
            if (g_d_GameSettings._10 == 0 && (u8)team != 0) {
                if (*(s8*)(lbl_8034E9A0 + 0x46F8) == 0) {
                    fn_800506E8(1, id, 1);
                } else {
                    fn_800506E8(1, id, 1);
                }
            } else {
                fn_800506E8(*(s8*)(lbl_8034E9A0 + (u8)team + 0x46F8), id, 1);
            }
            row[2] = id;
            lbl_8034E9A0[id + 0x4757] = 1;
            row[0x26] = (lbl_8034E9A0 + w)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x3B];
        }
        row++;
    }
}
#endif

// fn_2_C484, size:0x214
void fn_2_C484(s32 owner, s16 id) {
    s32 i;
    for (i = 0; i < 0x36; i++) {
        if (i == id) {
            lbl_8034E9A0[i + 0x4757] = 0;
            if (g_d_GameSettings.GameModeSelected == 5) {
                if (fn_2_C324(i) == -1) {
                    fn_800506E8(owner & 0xFF, i, 0);
                }
            } else {
                fn_800506E8(owner & 0xFF, i, 0);
                fn_80067B40(owner, i, 0);
            }
            return;
        }
    }
}

#define g_Roster ((MenuCharStats*)inMemRoster)

// fn_2_11EA8, size:0x228
void fn_2_11EA8(void) {
    MenuCharStats* src;
    s32 i;
    s8 sel;
    for (i = 0; i < 9; i++) {
        sel = *(s8*)(lbl_803C6724 + i + 2);
        src = (MenuCharStats*)(lbl_8034E9A0 + sel / 9 * 0x5A0 + sel % 9 * 0xA0);
        MENU_COPY_CHAR_STATS(&g_Roster[i], src);
        lbl_80354720[i * 4 + 2] = i;
        lbl_80354720[i * 4 + 1] = i;
        lbl_80354720[i * 4 + 0] = i;
    }
}

// NONMATCHING 88%: original keeps raw + two clrlwi copies of team (r27/r29/r30); we keep one
#if NONMATCHING
// fn_2_102C8, size:0x234
void fn_2_102C8(u8 team) {
    s32 i;
    s32 empty = 0;
    s32 other;
    u8* flag;
    for (i = 0; i < 9; i++) {
        s32 v = (s8)(lbl_803C6724 + team * 9)[i + 2];
        if (v == -1 || v == 0x36) {
            empty++;
        }
    }
    other = team ^ 1;
    if (lbl_2_bss_F468[other + 0x41] != 0) {
        flag = &lbl_8034E9A0[((s32*)lbl_2_bss_F410)[other + 8] + 0x4757];
        if (*flag == 0) {
            *flag = 1;
            lbl_2_bss_F468[team + 0x3B] = 1;
        }
    }
    if (empty != 0) {
        do {
            lbl_803CBD24[2] = randRange_FUN_80042bf0(0, 2);
        } while (lbl_803CBD24[3] == lbl_803CBD24[2]);
        fn_2_ABC0(team);
        switch (lbl_803CBD24[2]) {
        case 0:
            fn_2_FCB4(team);
            break;
        case 1:
            fn_2_FAA0(team);
            break;
        case 2:
            fn_2_F200(team);
            break;
        }
        fn_800678CC(team);
        unsure_FillRosterPositions(team);
        fn_800625A4(team, 0x16);
        lbl_803CBD24[3] = lbl_803CBD24[2];
        lbl_2_bss_F468[team + 0x37] = 1;
    } else {
        ((s32*)lbl_2_bss_F468)[team] = 9;
        fn_800625A4(team, 0x11);
    }
    if (lbl_2_bss_F468[team + 0x3B] != 0) {
        lbl_2_bss_F468[team + 0x3B] = 0;
        lbl_8034E9A0[((s32*)lbl_2_bss_F410)[other + 8] + 0x4757] = 0;
    }
}
#endif

// NONMATCHING 99%: case 3 reloads the s8 timer before the decrement in the original
#if NONMATCHING
// fn_2_110B0, size:0x244
void fn_2_110B0(void) {
    u8* scene = lbl_803CBBCC[0];
    s32 ok;
    switch (*(u16*)(scene + 4)) {
    case 0:
        if (g_d_GameSettings.GameModeSelected == 5 || *(u16*)(scene + 6) != 9) {
            *(u16*)(scene + 4) = 5;
        } else {
            lbl_803297E0[0xCFA1] = 0;
            *(u16*)(scene + 4) = 1;
        }
        break;
    case 1:
        fn_2_86EC();
        break;
    case 2:
        if (g_d_GameSettings.GameModeSelected == 5) {
            ok = lbl_8037169C[0x12];
        } else {
            ok = 1;
        }
        if (ok) {
            ((void (*)(void))fn_2_6608)();
        }
        break;
    case 3:
        if ((s8)lbl_2_bss_F468[0x36] < 0) {
            if (lbl_803C66B0[0x5D] == 0 && lbl_803C66B0[0x5E] == 0) {
                fn_2_72630();
                lbl_2_bss_F468[0x33] = 0;
                *(u16*)(lbl_803CBBCC[0] + 4) = 4;
            }
        } else {
            lbl_2_bss_F468[0x36]--;
        }
        break;
    case 4:
        ((void (*)(void))fn_2_6484)();
        break;
    case 5:
        fn_2_6D3C();
        break;
    case 6:
        fn_2_323C();
        break;
    case 7:
        if ((s8)lbl_2_bss_F468[0x36] < 0) {
            fn_800625A4(0, 0x13);
            fn_800625A4(1, 0x13);
            lbl_2_bss_F468[0x4F] = 0;
            lbl_2_bss_F468[0x2E] = 0;
            lbl_2_bss_100B4 = 1;
            *(u16*)(lbl_803CBBCC[0] + 4) = 8;
        } else {
            lbl_2_bss_F468[0x36]--;
        }
        break;
    case 8:
        fn_2_61A0();
        break;
    }
}
#endif

// fn_2_2FC0, size:0x244
void fn_2_2FC0(u8 mode, s32 b, s32 c) {
    switch (mode) {
    case 9:
        fn_800684A4();
        if (c == 0) {
            break;
        }
    case 10:
        memset(lbl_8034E9A0 + 0x4757, 0, 0x36);
        (lbl_8034E9A0 + 0x4757)[*(s32*)(lbl_8034E9A0 + 0x46E0)] = 1;
        (lbl_8034E9A0 + 0x4757)[*(s32*)(lbl_8034E9A0 + 0x46E4)] = 1;
        fn_2_348C();
        fn_80067F70(0);
        fn_80067F70(1);
        fn_2_8940();
        fn_800678CC(0);
        fn_800678CC(1);
        unsure_FillRosterPositions(0);
        unsure_FillRosterPositions(1);
        characterSelectScreen(0);
        characterSelectScreen(1);
        fn_80069854();
        if (c == 0) {
            break;
        }
    case 12:
        fn_800671FC();
        if (b != 0) {
            fn_800649BC();
        }
        break;
    case 11:
        break;
    }
}

// NONMATCHING 90%: preset base (+0x4380) hoisted differently; the ==1 test is cmpwi (enum field) in the original
#if NONMATCHING
// fn_2_6AF4, size:0x248
void fn_2_6AF4(void) {
    u8 idx = 0; // uninitialized in the original if no captain matches
    s32 i;
    u8 id;
    for (i = 0; i < 12; i++) {
        if ((s8)starMissionCompletionTracker[0x441F] == lbl_80108EC4[i]) {
            idx = i;
            break;
        }
    }
    for (i = 0; i < 9; i++) {
        id = lbl_8034E9A0[0x4380 + idx * 0x48 + i];
        lbl_80354720[0x24 + i * 4] = i;
        lbl_80354720[0x26 + i * 4] = i;
        lbl_80354720[0x25 + i * 4] = i;
        lbl_803C6724[0xB + i] = *(s16*)(lbl_8034E9A0 + (u8)(id / 9) * 0x5A0 + (u8)(id % 9) * 0xA0 + 0x24);
        lbl_803C6724[0x53 + i] = 1;
    }
    *(s32*)(lbl_8034E9A0 + 0x46E0) = starMissionCompletionTracker[0x441D];
    *(s32*)(lbl_8034E9A0 + 0x46E4) = (s8)starMissionCompletionTracker[0x441F];
    for (i = 0; i < 9; i++) {
        if (starMissionCompletionTracker[(s8)lbl_803C6724[0xB + i] * 0x34 + 0x31] == 1) {
            lbl_803C6724[0xB + i] = 0x36;
        }
    }
}
#endif

// NONMATCHING 80%: inlines fn_2_A1A0 (itself NONMATCHING) and fn_2_C698; slot index scheduling differs
#if NONMATCHING
// fn_2_CA60, size:0x25C
void fn_2_CA60(u8 slot, s32 team) {
    s32 v = (s8)(lbl_803C6724 + (u8)team * 9)[slot + 2];
    if (v != -1 && v != 0x36) {
        u8* order = lbl_80354720 + (u8)team * 0x24;
        order[slot * 4 + 1] = slot;
        order[slot * 4 + 0] = slot;
        g_Roster[(u8)team * 9 + slot].h24 = v;
    } else {
        fn_2_A1A0(slot, team);
    }
    fn_2_C698(slot, team);
}
#endif

// NONMATCHING 97%: register-only diff inside the inlined fn_2_C324 (r12/r30/r31 rotated)
#if NONMATCHING
// fn_2_6884, size:0x270
void fn_2_6884(void) {
    s32 i;
    s32 k;
    s8 g;
    for (i = 0; i < 9; i++) {
        s16 id = *(s16*)(starMissionCompletionTracker + i * 6 + 0x40B8);
        lbl_803C6724[i + 2] = id;
        lbl_80354720[i * 4 + 1] = starMissionCompletionTracker[i * 6 + 0x40BA];
        lbl_80354720[i * 4 + 0] = i;
        lbl_803C6724[i + 0x4A] = 1;
        lbl_80354720[i * 4 + 2] = i;
        lbl_8034E9A0[(u8)id + 0x4757] = 1;
        g = fn_2_C324((u8)id);
        if (g != -1) {
            for (k = 0; k < 5; k++) {
                s16 v = *(s16*)(lbl_80108EDC + g * 10 + k * 2);
                if (v != -1) {
                    lbl_8034E9A0[v + 0x4757] = 1;
                }
            }
        }
    }
}
#endif

// NONMATCHING 70%: retry loop shape (slot==0 test inside the loop in the original) and store addressing differ; inlines fn_2_C698
#if NONMATCHING
// fn_2_C7DC, size:0x284
void fn_2_C7DC(u8 slot, s32 team) {
    s32 id;
    s32 j;
    u8* order;
    u8* order2;
    if (slot == 0) {
        order = lbl_80354720 + (u8)team * 0x24 + slot * 4;
        order2 = lbl_80353B98 + (u8)team * 0x24 + slot * 4;
        order[1] = slot;
        order2[1] = slot;
        order2[0] = slot;
        order[0] = slot;
        order[2] = slot;
        g_Roster[(u8)team * 9 + slot].h24 = *(s32*)(lbl_8034E9A0 + (u8)team * 4 + 0x46E0);
        order2[2] = slot;
        return;
    }
retry:
    id = fn_2_14F8(0, 0x35);
    if (lbl_8034E9A0[lbl_800FDE84[id] + 0x4757] != 0) {
        goto retry;
    }
    for (j = 0; j < slot; j++) {
        if (g_Roster[j].h24 == id || g_Roster[9 + j].h24 == id) {
            goto retry;
        }
    }
    order = lbl_80354720 + (u8)team * 0x24 + slot * 4;
    order2 = lbl_80353B98 + (u8)team * 0x24 + slot * 4;
    order[1] = slot;
    order[0] = slot;
    order2[1] = slot;
    order2[0] = slot;
    order[2] = slot;
    g_Roster[(u8)team * 9 + slot].h24 = id;
    order2[2] = slot;
    fn_2_C698(slot, team);
}
#endif

// NONMATCHING 70%: the original fully unrolls the 8-entry preset scan; flag reads use [1],[2] after writing [0],[1] exactly as the original does
#if NONMATCHING
// fn_2_A288, size:0x284
void fn_2_A288(void) {
    u8 idx = 0; // uninitialized in the original if the captain isn't found
    u8 n = 0;
    s32 i;
    s32 k;
    s32 j;
    for (i = 0; i < 12; i++) {
        if (lbl_80108EC4[i] == *(s32*)(lbl_8034E9A0 + 0x46E0)) {
            lbl_8034E9A0[0x470B] = i;
            idx = i;
        } else if (lbl_80108EC4[i] == *(s32*)(lbl_8034E9A0 + 0x46E4)) {
            lbl_8034E9A0[0x470C] = i;
        }
    }
    for (k = 1; k < 3; k++) {
        for (j = 1; j < 9; j++) {
            u8 v = lbl_8034E9A0[0x4380 + idx * 0x48 + k * 0x12 + j];
            if (v == *(s32*)(lbl_8034E9A0 + 0x46E4) && v != 0xFF) {
                lbl_2_bss_3E0[k - 1] = -1;
            }
        }
        if ((s8)lbl_2_bss_3E0[k - 1] == -1) {
            lbl_2_bss_3E0[k - 1] = 0;
        } else {
            lbl_2_bss_3E0[k - 1] = 1;
        }
    }
    for (k = 1; k < 3; k++) {
        if ((s8)lbl_2_bss_3E0[k] == 0) {
            n++;
        }
    }
    if (n == 2) {
        lbl_2_bss_3E0[0] = -1;
    }
}
#endif

// NONMATCHING 97%: register choice for the three button words (held/down/repeat); inlines fn_2_1DC8
#if NONMATCHING
// fn_2_1800, size:0x288
void fn_2_1800(void) {
    MenuButtons b;
    memset(&b, 0, sizeof(b));
    b.held = *(u16*)(lbl_8034E9A0 + 0x472C);
    b.down = *(u16*)(lbl_8034E9A0 + 0x472E);
    b.repeat = *(u16*)(lbl_8034E9A0 + 0x4730);
    if (lbl_803C66B0[0x55] != 0) {
        return;
    }
    if (b.down & 0x100) {
        fn_2_1DC8();
        lbl_80366158[0x27] = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (b.down & 0x200) {
        lbl_80366158[0x29] = 2;
        lbl_8034E9A0[0x472A] = 0;
        *(s16*)(lbl_803CBBCC[0] + 4) = 6;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if ((b.repeat & 8) || (b.repeat & 4)) {
        ((s32*)lbl_2_bss_F410)[1] = ((s32*)lbl_2_bss_F410)[0];
        if (b.repeat & 8) {
            if (--((s32*)lbl_2_bss_F410)[0] < 0) {
                ((s32*)lbl_2_bss_F410)[0] = 6;
            }
        } else if (b.repeat & 4) {
            if (++((s32*)lbl_2_bss_F410)[0] == 7) {
                ((s32*)lbl_2_bss_F410)[0] = 0;
            }
        }
        fn_800625A4(0, 0x56);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}
#endif

// NONMATCHING 97%: same code as fn_2_1800; register choice for the three button words
#if NONMATCHING
// fn_2_1578, size:0x288
void fn_2_1578(void) {
    MenuButtons b;
    memset(&b, 0, sizeof(b));
    b.held = *(u16*)(lbl_8034E9A0 + 0x472C);
    b.down = *(u16*)(lbl_8034E9A0 + 0x472E);
    b.repeat = *(u16*)(lbl_8034E9A0 + 0x4730);
    if (lbl_803C66B0[0x55] != 0) {
        return;
    }
    if (b.down & 0x100) {
        fn_2_1DC8();
        lbl_80366158[0x27] = 0;
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (b.down & 0x200) {
        lbl_80366158[0x29] = 2;
        lbl_8034E9A0[0x472A] = 0;
        *(s16*)(lbl_803CBBCC[0] + 4) = 6;
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if ((b.repeat & 8) || (b.repeat & 4)) {
        ((s32*)lbl_2_bss_F410)[1] = ((s32*)lbl_2_bss_F410)[0];
        if (b.repeat & 8) {
            if (--((s32*)lbl_2_bss_F410)[0] < 0) {
                ((s32*)lbl_2_bss_F410)[0] = 6;
            }
        } else if (b.repeat & 4) {
            if (++((s32*)lbl_2_bss_F410)[0] == 7) {
                ((s32*)lbl_2_bss_F410)[0] = 0;
            }
        }
        fn_800625A4(0, 0x56);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}
#endif

// NONMATCHING 93%: same instructions, scheduling/register rotation in the unrolled pick loop
#if NONMATCHING
// fn_2_2D1C, size:0x2A4
void fn_2_2D1C(void) {
    s32 t;
    s32 i;
    *(s32*)(lbl_8034E9A0 + 0x46E0) = 10;
    *(s32*)(lbl_8034E9A0 + 0x46E4) = 2;
    for (t = 0; t < 2; t++) {
        s16* tbl = (s16*)lbl_2_data_E64 + t * 9;
        for (i = 0; i < 9; i++) {
            s32 v = tbl[i];
            lbl_803C6724[t * 9 + i + 2] = v;
            lbl_803C6724[t * 9 + i + 0x26] =
                (lbl_8034E9A0 + *(s32*)(lbl_8034E9A0 + 0x46E0 + t * 4) + (v / 9) * 0x5A0 + (v % 9) * 0xA0)[0x3B];
        }
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            lbl_80354720[t * 0x24 + i * 4 + 2] = i;
            lbl_80354720[t * 0x24 + i * 4 + 1] = i;
            lbl_80354720[t * 0x24 + i * 4 + 0] = i;
        }
    }
}
#endif

// NONMATCHING 85%: the original inlines fn_2_CA60 (NONMATCHING) into the slot loop; fn_2_14F8 must stay a call
#if NONMATCHING
// fn_2_B66C, size:0x2B4
void fn_2_B66C(void) {
    s8 pick;
    s32 k;
    s32 i;
    fn_2_A6E0();
    if ((s8)lbl_2_bss_3E0[0] == -1) {
        pick = -1;
    } else {
        do {
            k = fn_2_14F8(1, 2);
        } while ((s8)lbl_2_bss_3E0[k] == 0);
        pick = k;
    }
    switch (pick) {
    case 0:
        ((s32*)lbl_2_bss_F468)[5] = 1;
        break;
    case 1:
        ((s32*)lbl_2_bss_F468)[5] = 2;
        break;
    case -1:
        ((s32*)lbl_2_bss_F468)[5] = 3;
        break;
    }
    fn_2_ABC0(1);
    for (i = 0; i < 9; i++) {
        fn_2_CA60(i, 1);
    }
}
#endif

// NONMATCHING 99%: two li constants scheduled differently in the CF5F branch
#if NONMATCHING
// fn_2_61A0, size:0x2E4
void fn_2_61A0(void) {
    s32 i;
    s32 t;
    s32 j;
    if (fn_80062578() == 0) {
        return;
    }
    if (lbl_2_bss_F468[0x2E] == 0) {
        if (fn_80050F78(0) == 0) {
            lbl_803C66B0[0x56] = 1;
            lbl_803C66B0[0x55] = 1;
            return;
        }
    } else if (fn_80050F78(2) == 0) {
        lbl_803C66B0[0x56] = 1;
        lbl_803C66B0[0x55] = 1;
        return;
    }
    if ((s8)lbl_2_bss_F468[0x36] > 0) {
        lbl_2_bss_F468[0x36]--;
        return;
    }
    lbl_803C66B0[0x56] = 0;
    lbl_803C66B0[0x55] = 0;
    if (lbl_2_bss_F468[0x2E] == 0) {
        if (lbl_803297E0[0xCF5F] != 0) {
            fn_2_19F2C();
            lbl_8034E9A0[0x48AD] = 1;
            lbl_803C66B0[0] = 0;
            memset(lbl_803C66B0 + 1, 0, 6);
            lbl_8034E9A0[0x4755] = 3;
            fn_80062A74();
            fn_80021410();
            fn_80035CA4(0xF);
            fn_80035CA4(0x12);
            fn_80035CA4(9);
            fn_80035CA4(6);
            lbl_8034E9A0[0x48AF] = 1;
            lbl_8034E9A0[0x48B1] = 1;
            lbl_8034E978[0x26] = 1;
            lbl_803297E0[0xCF5F] = 0;
            fn_2_11A0(4);
        } else {
            lbl_2_bss_F468[0x28] = 0;
            lbl_2_bss_F468[0x29] = 0;
            lbl_2_bss_F468[0x2A] = 0;
            lbl_2_bss_F468[0x2B] = 0;
            lbl_2_bss_F468[0x2C] = 0;
            fn_2_8940();
            fn_2_AEE8();
            lbl_803C66B0[0] = 0;
            memset(lbl_803C66B0 + 1, 0, 6);
            lbl_8034E9A0[0x48B1] = 1;
            fn_2_11A0(0xB);
            for (i = 1; i < 9; i++) {
                fn_80021AC0(0, i);
                fn_80021AC0(1, i);
            }
        }
    } else {
        if (lbl_8034E978[0x24] != 0) {
            return;
        }
        lbl_2_bss_F468[0x42] = 0;
        lbl_2_bss_F468[0x41] = 0;
        lbl_2_bss_F468[0x38] = 0;
        lbl_2_bss_F468[0x37] = 0;
        for (t = 0; t < 2; t++) {
            for (j = 0; j < 9; j++) {
                lbl_803C6724[t * 9 + j + 0x4A] = 0;
            }
        }
        fn_2_11A0(9);
        *(u16*)(lbl_803CBBCC[0] + 8) = 0;
    }
    fn_800AD038(*(void**)(lbl_8034E9A0 + 0x46E8));
    lbl_8034E9A0[0x4755] = 3;
    lbl_8034E9A0[0x472A] = 0;
    lbl_8034E9A0[0x48AD] = 1;
}
#endif

// NONMATCHING 85%: captain-stats pointer setup and the sort's cached chem[i] register differ
#if NONMATCHING
// fn_2_ABC0, size:0x328
void fn_2_ABC0(u8 team) {
    u8 chem[0x36];
    u8 ids[0x36];
    s32 i;
    s32 j;
    s32 cap = *(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0);
    MenuCharStats* c = (MenuCharStats*)(lbl_8034E9A0 + cap / 9 * 0x5A0 + cap % 9 * 0xA0);
    for (i = 0; i < 0x36; i++) {
        ids[i] = i;
        chem[i] = c->chem[i];
    }
    for (i = 0; i < 0x36; i++) {
        for (j = i + 1; j < 0x36; j++) {
            if (chem[i] < chem[j]) {
                u8 tc = chem[i];
                u8 ti = ids[i];
                chem[i] = chem[j];
                ids[i] = ids[j];
                chem[j] = tc;
                ids[j] = ti;
            }
        }
    }
    for (i = 0; i < 0x36; i++) {
        lbl_8034E9A0[0x478D + team * 0x36 + i] = ids[i];
    }
}
#endif

// NONMATCHING 80%: stadium-selection pointer kept in a register differently; branch layout of the button chain
#if NONMATCHING
// fn_2_11340, size:0x358
void fn_2_11340(u8 team) {
    u8 found = 0;
    s32* stadium = (s32*)(lbl_2_bss_F410 + 0x44);
    s32 prev;
    s32 r;
    s8 port;
    u16 repeat;
    u16 down;
    if (lbl_803CBCD8[0] != 0) {
        prev = *stadium;
        do {
            if (lbl_80361B20[0xF5] != 0) {
                r = fn_2_14F8(0, 5);
            } else {
                r = fn_2_14F8(0, 4);
            }
        } while (prev == r);
        *stadium = r;
        lbl_803CBCD8[1]--;
        fn_800625A4(0, 0x28);
        return;
    }
    if (lbl_803C66B0[0x55] != 0) {
        return;
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        port = lbl_8034E9A0[0x46F8 + team];
        if (g_d_GameSettings.PlayerPorts[0] == port) {
            found = 1;
        }
        if (g_d_GameSettings.PlayerPorts[1] == port) {
            found = 1;
        }
        lbl_8034E9A0[0x46F8 + team] = port;
        if (!found) {
            return;
        }
    } else if (team != 0) {
        return;
    }
    repeat = *(u16*)(lbl_8034E9A0 + team * 6 + 0x4730);
    down = *(u16*)(lbl_8034E9A0 + team * 6 + 0x472E);
    if (repeat & 1) {
        if (lbl_803C66B0[0x5D] != 0x24) {
            if (--*stadium < 0) {
                *stadium = 5;
            }
            fn_800625A4(0, 0x28);
            fn_2_1C34(1);
        }
    } else if (repeat & 2) {
        if (lbl_803C66B0[0x5D] != 0x24) {
            if (++*stadium == 6) {
                *stadium = 0;
            }
            fn_800625A4(0, 0x28);
            fn_2_1C34(2);
        }
    } else if (down & 0x20) {
        if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_803CBCD8[0] = 1;
            lbl_803CBCD8[1] = 6;
        }
    } else if (down & 0x100) {
        if (*stadium < 6) {
            if (lbl_80361B20[0xF5] == 0 && lbl_2_data_130C[*stadium] == 1) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            } else if (lbl_803C66B0[0x5D] == 0) {
                g_d_GameSettings.StadiumID = lbl_2_data_130C[*stadium];
                lbl_2_bss_F468[0x58] = 1;
                fn_2_328();
                fn_2_1C34(0x100);
                fn_800625A4(0, 0x25);
                *(u16*)(lbl_803CBBCC[0] + 4) = 4;
            }
        }
    } else if (down & 0x200) {
        if (lbl_803CBCD8[0] == 0 && lbl_803C66B0[0x5D] == 0) {
            fn_2_2DC();
            fn_2_1C34(0x200);
            *(u16*)(lbl_803CBBCC[0] + 6) = 0xC;
            fn_800625A4(0, 0x24);
            *(u16*)(lbl_803CBBCC[0] + 4) = 3;
        }
    }
}
#endif

// NONMATCHING 75%: the original inlines fn_2_CA60 (NONMATCHING) into the slot loop
#if NONMATCHING
// fn_2_BF90, size:0x394
void fn_2_BF90(void) {
    s32 idx = -1;
    s32 i;
    memset(lbl_8034E9A0 + 0x4757, 0, 0x36);
    for (i = 0; i < 12; i++) {
        if (lbl_80108EC4[i] == (s8)starMissionCompletionTracker[0x441F]) {
            lbl_8034E9A0[0x470C] = i;
            idx = (u8)i;
        }
    }
    ((s32*)lbl_2_bss_F468)[5] = 0;
    ((s32*)lbl_2_bss_F468)[4] = 0;
    for (i = 0; i < 9; i++) {
        lbl_803C6724[0xB + i] = lbl_8034E9A0[0x4380 + idx * 0x48 + i];
    }
    for (i = 0; i < 9; i++) {
        fn_2_CA60(i, 1);
    }
}
#endif

// NONMATCHING 90%: mode-5 copy loop register/scheduling; inlined fn_2_52CC indexes F468 via slwi/stwx in the original
#if NONMATCHING
// fn_2_5444, size:0x3A4
void fn_2_5444(u8 team) {
    s32 i;
    u8 s10;
    lbl_2_bss_F468[team + 0x3D] = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 9; i++) {
            s16 id = (s8)lbl_803C6724[i + 2];
            u8 pos = lbl_803C6724[i + 0x14];
            *(s16*)(starMissionCompletionTracker + i * 6 + 0x40B8) = id;
            starMissionCompletionTracker[i * 6 + 0x40BA] = i;
            starMissionCompletionTracker[i * 6 + 0x40BB] = pos;
            g_Roster[i].h24 = id;
            lbl_80354720[i * 4 + 2] = pos;
        }
        fn_800625A4(0, 0x13);
        fn_800625A4(1, 0x13);
        lbl_2_bss_F468[0x2E] = 0;
        lbl_2_bss_100B4 = 1;
        *(s16*)(lbl_803CBBCC[0] + 4) = 8;
        return;
    }
    s10 = g_d_GameSettings._10;
    if (s10 == 0 && lbl_2_bss_100B8[0x2E] != 0) {
        fn_800625A4(1, 0x11);
        lbl_8034E9A0[0x472A] = 0xFF;
        lbl_2_bss_F468[0x36] = 0x1E;
        *(s16*)(lbl_803CBBCC[0] + 4) = 3;
    } else if (s10 == 0) {
        fn_2_52CC();
        fn_800625A4(0, 0x11);
    } else if (s10 == 1) {
        lbl_2_bss_100B8[0x2E + team] = 1;
        fn_800625A4(team, 0x11);
        if (lbl_2_bss_100B8[0x2E] != 0 && lbl_2_bss_100B8[0x2F] != 0) {
            lbl_2_bss_F468[0x4F] = 1;
            lbl_2_bss_F468[0x36] = 0x1E;
            *(s16*)(lbl_803CBBCC[0] + 4) = 7;
        }
    }
}
#endif

// NONMATCHING 88%: copy-loop induction registers differ (r14-r16 vs r17-r19); v >> 1 is extrwi in the original
#if NONMATCHING
// fn_2_8940, size:0x3B8
void fn_2_8940(void) {
    s32 t;
    s32 i;
    s8 sel;
    MenuCharStats* src;
    MenuCharStats* dst;
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            sel = lbl_803C6724[t * 9 + i + 2];
            src = (MenuCharStats*)(lbl_8034E9A0 + sel / 9 * 0x5A0 + sel % 9 * 0xA0);
            dst = &g_Roster[t * 9 + i];
            MENU_COPY_CHAR_STATS(dst, src);
            lbl_80354720[t * 0x24 + i * 4 + 2] = lbl_803C6724[t * 9 + i + 0x14];
            if (t == 0 && g_d_GameSettings.GameModeSelected == 5) {
                s32 v = lbl_2_bss_3A8[*(s16*)(starMissionCompletionTracker + i * 6 + 0x40B8)];
                dst->b26 = v >> 1;
                dst->b27 = v % 2;
            }
        }
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            *(s16*)(lbl_803C5EA4 + 0x12 + t * 0x12 + i * 2) = (s8)lbl_803C6724[t * 9 + i + 2];
        }
    }
    fn_80066EAC(0);
    fn_80066EAC(1);
}
#endif

// NONMATCHING 85%: lbl_2_data_180 and the state pointer are hoisted once in the original; case bodies laid out differently
#if NONMATCHING
static inline void fn_2_27E0_init(void) {
    initializeUnknown();
    lbl_8034E9A0[0x4700] = 0;
    lbl_8034E9A0[0x472A] = 0xFF;
    lbl_8034E9A0[0x4756] = 0;
    lbl_8034E9A0[0x4754] = 0;
    lbl_8034E9A0[0x4755] = 3;
    lbl_8034E9A0[0x48B3] = 0;
    lbl_8034E9A0[0x4701] = 0;
    lbl_8034E9A0[0x4702] = 0;
    lbl_8034E9A0[0x4703] = 0;
    lbl_8034E9A0[0x4704] = 0;
    lbl_8034E9A0[0x4705] = 0;
    lbl_8034E9A0[0x4706] = 0;
    lbl_8034E9A0[0x4707] = 0;
    lbl_8034E9A0[0x4700] = 1;
    if (*(u16*)(lbl_803CBBCC[0] + 6) != 1) {
        fn_80062764(lbl_803CC1B8);
    }
    lbl_2_bss_20[0]++;
}

// fn_2_27E0, size:0x3D8
void fn_2_27E0(void) {
    s16 v;
    switch (lbl_2_bss_20[0]) {
    case 0:
        fn_2_19F2C();
        switch (*(u16*)(lbl_803CBBCC[0] + 6)) {
        case 8:
            lbl_2_bss_20[0] = 3;
            break;
        case 6:
        case 9:
        case 12:
            lbl_2_bss_20[0] = 0xC;
            break;
        case 15:
            if (lbl_8034E9A0[0x4756] == 0) {
                lbl_2_bss_20[0] = 0xC;
                break;
            }
        default:
            fn_2_27E0_init();
            break;
        }
        break;
    case 1:
        lbl_2_bss_20[0]++;
    case 2:
        if (fn_80022B68() != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 3:
        fn_2_12988();
        lbl_2_bss_20[0]++;
        break;
    case 4:
        if (fn_800697B0() == 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 5:
        if (fn_80035838(lbl_2_data_180 + 0x2C4, 6) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 6:
        if (fn_80035838(lbl_2_data_180 + 0x2D4, 9) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 7:
        if (fn_80035838(lbl_2_data_180 + 0x2E4, 0x12) != 0) {
            lbl_2_bss_20[0]++;
        }
        break;
    case 8:
        if (fn_80035838(lbl_2_data_180 + 0x2F4, 0xF) != 0) {
            if (*(u16*)(lbl_803CBBCC[0] + 6) == 1) {
                lbl_2_bss_20[0] = 0xB;
            } else {
                lbl_2_bss_20[0]++;
            }
        }
        break;
    case 9:
        if (lbl_8034E9A0[0x48B4] != 0) {
            if (lbl_803CBCE0[0] == 0) {
                fn_8003F23C();
            }
            lbl_2_bss_20[0]++;
        } else {
            lbl_2_bss_20[0] = 0xB;
        }
        break;
    case 10:
        if (lbl_803CBCE0[0] == 0) {
            v = *(s16*)(lbl_803CC1B8 + 0x10);
            if (v == 1 || v == 0xB) {
                lbl_803CBCE0[0] = 1;
                lbl_80361B20[0xDE] = 1;
                lbl_80361B20[0xDF] = 1;
                lbl_80361B20[0xE0] = 1;
                lbl_80361B20[0xE1] = 1;
                lbl_80361B20[0xE2] = 1;
                lbl_80361B20[0xE3] = 1;
                lbl_2_bss_20[0]++;
            }
        } else {
            lbl_2_bss_20[0]++;
        }
        break;
    case 11:
        if (*(u16*)(lbl_803CBBCC[0] + 6) != 6 && lbl_803C6714[4] == 0) {
            fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
        }
        *(u16*)(lbl_803CBBCC[0] + 4) = 0;
        lbl_2_bss_20[0]++;
        break;
    case 12:
        fn_2_1F30();
        break;
    }
}
#endif

// NONMATCHING 80%: same shape as fn_2_ABC0 for both teams; pointer/induction registers differ
#if NONMATCHING
// fn_2_AEE8, size:0x43C
void fn_2_AEE8(void) {
    u8 chem[0x36];
    u8 ids[2][0x36];
    s32 t;
    s32 i;
    s32 j;
    s32 cap;
    MenuCharStats* c;
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 0x36; i++) {
            ids[t][i] = i;
        }
    }
    for (t = 0; t < 2; t++) {
        cap = *(s32*)(lbl_8034E9A0 + t * 4 + 0x46E0);
        c = (MenuCharStats*)(lbl_8034E9A0 + cap / 9 * 0x5A0 + cap % 9 * 0xA0);
        for (i = 0; i < 0x36; i++) {
            chem[i] = c->chem[i];
        }
        for (i = 0; i < 0x36; i++) {
            for (j = i + 1; j < 0x36; j++) {
                if (chem[i] < chem[j]) {
                    u8 tc = chem[i];
                    u8 ti = ids[t][i];
                    chem[i] = chem[j];
                    ids[t][i] = ids[t][j];
                    chem[j] = tc;
                    ids[t][j] = ti;
                }
            }
        }
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 0x36; i++) {
            lbl_8034E9A0[0x478D + t * 0x36 + i] = ids[t][i];
        }
    }
}
#endif

// NONMATCHING 85%: register allocation and branch layout differ; fn_2_35D0 inlines as in the original
#if NONMATCHING
static inline void fn_2_ED94_toggle(u8 team, u16 held) {
    if (lbl_2_bss_F468[team + 0x47] == 0 && (held & 2)) {
        lbl_2_bss_F468[team + 0x47] = 1;
        lbl_2_bss_F468[team + 0x49] = 0;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (lbl_2_bss_F468[team + 0x47] == 1 && (held & 1)) {
        lbl_2_bss_F468[team + 0x47] = 0;
        lbl_2_bss_F468[team + 0x49] = 0;
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}

// fn_2_ED94, size:0x46C
s32 fn_2_ED94(u8 team, u16 held, u16 pressed, s32 dirs) {
    s8 owner;
    if (lbl_2_bss_F468[team + 0x41] == 0) {
        if ((held & 8) || (held & 4) || (held & 1) || (held & 2)) {
            if (lbl_2_bss_F468[team + 0x45] != 0) {
                fn_2_ED94_toggle(team, held);
                dirs = 0;
                pressed = 0;
                held = 0;
            }
            if (lbl_2_bss_F468[team + 0x59] != 0) {
                dirs = 0;
                pressed = 0;
                held = 0;
            }
            fn_2_57F0(team, held, pressed, dirs);
            return 1;
        }
    } else {
        if (lbl_2_bss_F468[team + 0x59] != 0) {
            lbl_2_bss_F468[team + 0x41] = 0;
            fn_800625A4(team, 0xD);
            return 1;
        }
        if (((s32*)lbl_2_bss_F468)[team] != 9) {
            ((s32*)lbl_2_bss_F468)[team + 8] = ((s32*)lbl_2_bss_F410)[team + 8];
            if (lbl_2_bss_F468[team + 0x45] != 0) {
                fn_2_ED94_toggle(team, held);
                if (g_d_GameSettings._10 == 0 && team != 0) {
                    owner = *(s8*)(lbl_8034E9A0 + 0x46F8) == 0;
                    lbl_803C6028[0x74 + owner] = 1;
                    ((s32*)lbl_2_bss_F410)[team + 8] = fn_80050760(owner, 0, 0, 0, 0);
                } else {
                    owner = *(s8*)(lbl_8034E9A0 + 0x46F8 + team);
                    if (*(s8*)(lbl_8034E9A0 + 0x46FC + owner) != 0) {
                        owner = *(s8*)(lbl_8034E9A0 + 0x46F8) == 0;
                    }
                    ((s32*)lbl_2_bss_F410)[team + 8] = fn_80050760(owner, 0, 0, 0, 0);
                }
            } else if (g_d_GameSettings._10 == 0 && team != 0) {
                owner = *(s8*)(lbl_8034E9A0 + 0x46F8) == 0;
                lbl_803C6028[0x74 + owner] = 1;
                ((s32*)lbl_2_bss_F410)[team + 8] = fn_80050760(owner, held, pressed, dirs, 0);
            } else {
                owner = *(s8*)(lbl_8034E9A0 + 0x46F8 + team);
                if (*(s8*)(lbl_8034E9A0 + 0x46FC + owner) != 0) {
                    owner = *(s8*)(lbl_8034E9A0 + 0x46F8) == 0;
                }
                ((s32*)lbl_2_bss_F410)[team + 8] = fn_80050760(owner, held, pressed, dirs, 0);
            }
        }
    }
    if (pressed & 0x100) {
        if (fn_2_35D0(team)) {
            return 1;
        }
        fn_2_DFAC(team);
        return 1;
    }
    if (pressed & 0x200) {
        if (fn_2_35D0(team)) {
            return 1;
        }
        fn_2_CE44(team);
        return 1;
    }
    return 0;
}
#endif

#define FN_2_9ACC_RESTORE(t, i)                                                   \
    do {                                                                          \
        MenuCharStats* dst = &g_Roster[(t) * 9 + (i)];                            \
        MenuCharStats* src = &((MenuCharStats*)lbl_2_bss_E8CC)[(t) * 9 + (i)];    \
        u8* order = lbl_80354720 + (t) * 0x24 + (i) * 4;                          \
        u8* saved = lbl_2_bss_DCE8 + (t) * 0x24 + (i) * 4;                        \
        MENU_COPY_CHAR_STATS(dst, src);                                           \
        order[0] = saved[0];                                                      \
        order[1] = saved[1];                                                      \
        order[2] = saved[2];                                                      \
        dst->h24 = *(s32*)(lbl_8034E9A0 + (t) * 4 + 0x46E0);                      \
        order[3] = saved[3];                                                      \
    } while (0)

// NONMATCHING 90%: same instructions modulo induction registers (r18-r22 vs r26-r31)
#if NONMATCHING
// fn_2_9ACC, size:0x4A4
void fn_2_9ACC(u16 team) {
    s32 t;
    s32 i;
    if (g_d_GameSettings._10 == 1) {
        for (i = 0; i < 9; i++) {
            if (lbl_2_bss_100B8[team + 0x30] != 0) {
                FN_2_9ACC_RESTORE(team, i);
            }
        }
        return;
    }
    for (t = 0; t < 2; t++) {
        for (i = 0; i < 9; i++) {
            if (lbl_2_bss_100B8[t + 0x30] != 0) {
                FN_2_9ACC_RESTORE(t, i);
            }
        }
    }
}
#endif

// NONMATCHING 85%: both duplicate scans inline as in the original; registers and flag-store forms differ
#if NONMATCHING
static inline s32 fn_2_A6E0_shared(void) {
    s32 i;
    s32 j;
    for (i = 0; i < 9; i++) {
        s8 a = lbl_803C6724[2 + i];
        for (j = 0; j < 9; j++) {
            if (a == (s8)lbl_803C6724[0xB + j] && a != -1) {
                return 1;
            }
        }
    }
    return 0;
}

// fn_2_A6E0, size:0x4E0
void fn_2_A6E0(void) {
    s32 k;
    s32 n = 0;
    if (g_d_GameSettings.GameModeSelected == 5) {
        return;
    }
    if (lbl_2_bss_100B8[0x2E] != 0 && g_d_GameSettings._10 == 0) {
        lbl_2_bss_3E0[1] = fn_2_A50C() == 0;
        lbl_2_bss_3E0[2] = fn_2_A50C() == 0;
        if ((s8)lbl_2_bss_3E0[1] == 0 && (s8)lbl_2_bss_3E0[2] == 0) {
            lbl_2_bss_3E0[0] = -1;
        }
    } else {
        for (k = 1; k < 3; k++) {
            if (fn_2_A6E0_shared() == 0) {
                lbl_2_bss_3E0[k - 1] = 1;
            } else {
                lbl_2_bss_3E0[k - 1] = 0;
            }
            if (fn_2_A6E0_shared() == 0) {
                lbl_2_bss_3E0[k + 1] = 1;
            } else {
                lbl_2_bss_3E0[k + 1] = 0;
            }
        }
        if ((s8)lbl_2_bss_3E0[0] == 0) {
            n = 1;
        }
        if ((s8)lbl_2_bss_3E0[1] == 0) {
            n++;
        }
        if ((s8)lbl_2_bss_3E0[2] == 0) {
            n++;
        }
        if ((s8)lbl_2_bss_3E0[3] == 0) {
            n++;
        }
        if (n == 4) {
            lbl_2_bss_3E0[0] = -1;
        }
    }
}
#endif

// NONMATCHING 60%: only computes colours/slots into locals (the draw calls that used them
// are compiled out), so it has no side effects; kept as a readable reconstruction.
#if NONMATCHING
// fn_2_95D8, size:0x4F4
void fn_2_95D8(void) {
    u32 color[2];
    s8 slot[2][9];
    s8 used[0x36];
    s32 t;
    s32 i;
    s32 j;
    s32 sel;
    s32 cap;
    s32 n;
    if (*(u16*)(lbl_803CBBCC[0] + 4) < 4) {
        for (t = 0; t < 2; t++) {
            sel = (t == 0) ? ((s32*)lbl_2_bss_F468)[t] : ((s32*)lbl_2_bss_F468)[t] - 10;
            color[t] = (t == 0) ? 0xFF0F : 0xF00F;
            for (i = 0; i < 9; i++) {
                for (j = 0; j < 9; j++) {
                    if (i == (s8)lbl_80354720[t * 0x24 + j * 4 + 1]) {
                        break;
                    }
                }
                if (g_d_GameSettings.GameModeSelected != 5 || t == 0) {
                    cap = *(s32*)(lbl_8034E9A0 + t * 4 + 0x46E0);
                } else {
                    cap = (s8)starMissionCompletionTracker[0x441F];
                }
                if ((s8)lbl_803C6724[t * 9 + i + 2] == cap) {
                    color[t] = 0x88FF;
                } else if (i == sel) {
                    color[t] = 0xFF0F;
                } else {
                    color[t] = 0xFFFF;
                }
            }
        }
        n = 5;
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                slot[t][i] = -1;
            }
        }
        for (i = 0; i < 0x36; i++) {
            used[i] = -1;
        }
        for (i = 0; i < 0x36; i++) {
            if (i == ((s32*)lbl_2_bss_F410)[8]) {
                color[0] = 0xFFF;
            } else if (i == ((s32*)lbl_2_bss_F410)[9]) {
                color[1] = 0xF0FF;
            } else {
                color[0] = 0xFFFF;
                color[1] = 0xFFFF;
            }
            for (t = 0; t < 2; t++) {
                for (j = 0; j < 9; j++) {
                    if (i == (s8)lbl_803C6724[t * 9 + j + 2] && color[0] != 0xFFF) {
                        used[i] = i;
                        color[0] = (t == 0) ? 0x88F : 0x808F;
                        slot[t][j] = i;
                    }
                }
            }
            if (lbl_8034E9A0[i + 0x4757] != 0 && used[i] == -1) {
                color[0] = 0x888F;
            }
            if (g_d_GameSettings._10 != 1 || i != ((s32*)lbl_2_bss_F410)[9]) {
                n++;
            }
            if (n == 0x1A) {
                n = 6;
            }
        }
    }
}
#endif

// NONMATCHING 80%: chemOrder entry reloads/addressing and loop registers differ
#if NONMATCHING
// fn_2_FCB4, size:0x614
void fn_2_FCB4(u8 team) {
    s8 cand[0x36];
    s32 empty = 0;
    s32 cap = *(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0);
    s32 i;
    s32 j;
    s32 g;
    s32 k;
    s8 r;
    s8 id;
    s8 t;
    s16* grp;
    u8* row;
    u8* other;
    u8 ot;
    memset(cand, -1, 0x36);
    for (i = 0; i < 0x36; i++) {
        for (g = 0; g < 9; g++) {
            for (k = 1; k < 5; k++) {
                if (lbl_8034E9A0[0x478D + team * 0x36 + i] == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                    lbl_8034E9A0[lbl_8034E9A0[0x478D + team * 0x36 + i] + 0x4757] = 1;
                }
            }
        }
        if (lbl_8034E9A0[lbl_8034E9A0[0x478D + team * 0x36 + i] + 0x4757] == 0) {
            cand[i] = lbl_8034E9A0[0x478D + team * 0x36 + i];
        }
    }
    for (i = 0; i < 0x36; i++) {
        for (j = i; j < 0x36; j++) {
            t = cand[i];
            if (t == -1 && cand[j] != -1) {
                cand[i] = cand[j];
                cand[j] = t;
            }
        }
    }
    row = lbl_803C6724 + team * 9;
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[i + 2];
        if (v == -1 || v == 0x36) {
            empty++;
        }
    }
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[i + 2];
        if (v != -1 && v != 0x36) {
            continue;
        }
        do {
            r = fn_2_14F8(0, (s8)(0x14 - (9 - empty)));
            id = cand[r];
        } while (id == -1 || lbl_8034E9A0[id + 0x4757] == 1);
        cand[r] = -1;
        lbl_8034E9A0[id + 0x4757] = 1;
        if (g_d_GameSettings._10 == 0 && team != 0) {
            if (*(s8*)(lbl_8034E9A0 + 0x46F8) == 0) {
                fn_800506E8(1, id, 1);
            } else {
                fn_800506E8(1, id, 1);
            }
        } else {
            fn_800506E8(*(s8*)(lbl_8034E9A0 + team + 0x46F8), id, 1);
        }
        fn_80067B40(team, id, 1);
        for (g = 0; g < 9; g++) {
            for (k = 0; k < 5; k++) {
                if (id == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                    grp = (s16*)(lbl_80108EDC + g * 10);
                    id = grp[0];
                    for (k = 0; k < 5; k++) {
                        s16 m = grp[k];
                        if (m != -1) {
                            for (j = 0; j < 0x36; j++) {
                                if (cand[j] == m) {
                                    cand[j] = -1;
                                }
                            }
                        }
                    }
                    goto found;
                }
            }
        }
    found:
        row[i + 2] = id;
        empty--;
        row[i + 0x26] = (lbl_8034E9A0 + cap)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x3B];
    }
    for (i = 0; i < 45; i++) {
        lbl_8034E9A0[((s16*)lbl_80108EDC)[i] + 0x4757] = 0;
    }
    ot = team ^ 1;
    other = lbl_803C6724 + ot * 9;
    for (i = 0; i < 9; i++) {
        fn_80067B40(ot, other[i + 2], 1);
        fn_80067B40(team, row[i + 2], 1);
    }
    if (g_d_GameSettings._1A[5] == 0) {
        lbl_8034E9A0[0x478C] = 1;
        lbl_8034E9A0[0x478B] = 1;
        lbl_8034E9A0[0x4772] = 1;
    }
}
#endif

// NONMATCHING 70%: the original inlines fn_2_CA60 (NONMATCHING) and fully unrolls the team-1 reset loop
#if NONMATCHING
// fn_2_B920, size:0x670
void fn_2_B920(void) {
    u8 idx0 = 0;
    u8 idx1 = 0;
    s32 i;
    s8 pick;
    s32 k;
    s32 type;
    memset(lbl_8034E9A0 + 0x4757, 0, 0x36);
    if (g_d_GameSettings.GameModeSelected != 5) {
        for (i = 0; i < 12; i++) {
            if (lbl_80108EC4[i] == *(s32*)(lbl_8034E9A0 + 0x46E0)) {
                lbl_8034E9A0[0x470B] = i;
                idx0 = i;
            } else if (lbl_80108EC4[i] == *(s32*)(lbl_8034E9A0 + 0x46E4)) {
                lbl_8034E9A0[0x470C] = i;
                idx1 = i;
            }
        }
    } else {
        for (i = 0; i < 12; i++) {
            if (lbl_80108EC4[i] == starMissionCompletionTracker[0x441D]) {
                lbl_8034E9A0[0x470B] = i;
            } else if (lbl_80108EC4[i] == (s8)starMissionCompletionTracker[0x441F]) {
                lbl_8034E9A0[0x470C] = i;
            }
        }
    }
    fn_2_A288();
    if ((s8)lbl_2_bss_3E0[0] != -1) {
        do {
            k = fn_2_14F8(1, 2);
        } while ((s8)lbl_2_bss_3E0[k] == 0);
        pick = k;
    } else {
        pick = -1;
    }
    switch (pick) {
    case 0:
        ((s32*)lbl_2_bss_F468)[4] = 1;
        break;
    case 1:
        ((s32*)lbl_2_bss_F468)[4] = 2;
        break;
    case -1:
        ((s32*)lbl_2_bss_F468)[4] = 3;
        break;
    }
    ((s32*)lbl_2_bss_F468)[5] = 3;
    for (i = 0; i < 9; i++) {
        lbl_803C6724[i + 2] = lbl_8034E9A0[0x4380 + idx0 * 0x48 + ((s32*)lbl_2_bss_F468)[4] * 0x12 + i];
    }
    type = ((s32*)lbl_2_bss_F468)[5];
    for (i = 0; i < 9; i++) {
        lbl_803C6724[i + 0xB] = lbl_8034E9A0[0x4380 + idx1 * 0x48 + type * 0x12 + i];
    }
    ((s32*)lbl_2_bss_F468)[5] = type;
    fn_2_ABC0(0);
    lbl_8034E9A0[*(s32*)(lbl_8034E9A0 + 0x46E4) + 0x4757] = 1;
    for (i = 0; i < 9; i++) {
        fn_2_CA60(i, 0);
    }
    for (i = 0; i < 9; i++) {
        lbl_80354720[0x26 + i * 4] = i;
        lbl_80353B98[0x26 + i * 4] = i;
        lbl_803C6724[0xB + i] = (i == 0) ? (s8)*(s32*)(lbl_8034E9A0 + 0x46E4) : 0x36;
        lbl_803C6724[0x53 + i] = (i == 0) ? 1 : 0;
    }
}
#endif

// NONMATCHING 75%: the original repeats the sound call per branch and indexes state via stwx; same transitions
#if NONMATCHING
// fn_2_57F0, size:0x790
void fn_2_57F0(u8 team, u16 held, u16 pressed, u16 repeat) {
    s32* state = (s32*)lbl_2_bss_F468;
    u8* done = lbl_2_bss_F468 + 0x37;
    state[team + 2] = state[team];
    if ((repeat & 8) || (pressed & 8)) {
        if (state[team] == 9) {
            state[team] = 2;
            fn_800625A4(team, 0xE);
        } else if (state[team] == 10) {
            if (done[team] != 0) {
                state[team] = 9;
                fn_800625A4(team, 0x18);
            } else {
                state[team] = 2;
                fn_800625A4(team, 0xE);
            }
        } else {
            switch (state[team]) {
            case 0: state[team] = 5; break;
            case 1: state[team] = 0; break;
            case 2: state[team] = 8; break;
            case 3: state[team] = 7; break;
            case 4: state[team] = 6; break;
            case 5: state[team] = 7; break;
            case 6: state[team] = 4; break;
            case 7: state[team] = 1; break;
            case 8:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    state[team] = 10;
                } else if (done[team] != 0) {
                    state[team] = 9;
                } else {
                    state[team] = 2;
                }
                break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if ((repeat & 4) || (pressed & 4)) {
        if (state[team] == 9) {
            if (g_d_GameSettings.GameModeSelected != 5) {
                state[team] = 10;
                fn_800625A4(team, 0x18);
            } else {
                state[team] = 8;
                fn_800625A4(team, 0xE);
            }
        } else if (state[team] == 10) {
            state[team] = 8;
            fn_800625A4(team, 0xE);
        } else {
            switch (state[team]) {
            case 0: state[team] = 1; break;
            case 1: state[team] = 7; break;
            case 2:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    if (done[team] != 0) {
                        state[team] = 9;
                    } else {
                        state[team] = 10;
                    }
                } else if (done[team] != 0) {
                    state[team] = 9;
                } else {
                    state[team] = 8;
                }
                break;
            case 3: state[team] = 0; break;
            case 4: state[team] = 6; break;
            case 5: state[team] = 0; break;
            case 6: state[team] = 4; break;
            case 7: state[team] = 5; break;
            case 8: state[team] = 2; break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if ((repeat & 1) || (pressed & 1)) {
        if (state[team] == 9) {
            state[team] = 0;
            fn_800625A4(team, 0xE);
        } else if (state[team] == 10) {
            state[team] = 1;
            fn_800625A4(team, 0xE);
        } else {
            switch (state[team]) {
            case 0: state[team] = 4; break;
            case 1:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    state[team] = 10;
                } else if (done[team] != 0) {
                    state[team] = 9;
                } else {
                    return;
                }
                break;
            case 2: state[team] = 3; break;
            case 3: state[team] = 5; break;
            case 4: state[team] = 2; break;
            case 5: state[team] = 4; break;
            case 6: state[team] = 8; break;
            case 7: state[team] = 6; break;
            case 8: state[team] = 7; break;
            case 9: break;
            case 10: state[team] = 1; break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if ((repeat & 2) || (pressed & 2)) {
        if (state[team] == 9) {
            state[team] = 0;
            fn_800625A4(team, 0xE);
        } else if (state[team] == 10) {
            if (done[team] != 0) {
                state[team] = 9;
                fn_800625A4(team, 0x18);
            } else {
                state[team] = 1;
                fn_800625A4(team, 0xE);
            }
        } else {
            switch (state[team]) {
            case 0:
                if (done[team] != 0) {
                    state[team] = 9;
                    fn_800625A4(team, 0x18);
                } else {
                    state[team] = 2;
                    fn_800625A4(team, 0xE);
                }
                break;
            case 1:
                if (g_d_GameSettings.GameModeSelected != 5) {
                    state[team] = 10;
                } else if (done[team] != 0) {
                    state[team] = 9;
                } else {
                    return;
                }
                break;
            case 2: state[team] = 4; break;
            case 3: state[team] = 2; break;
            case 4: state[team] = 5; break;
            case 5: state[team] = 3; break;
            case 6: state[team] = 7; break;
            case 7: state[team] = 8; break;
            case 8: state[team] = 6; break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    }
}
#endif

// NONMATCHING 70%: the original inlines fn_2_6784, fn_2_6AF4 and fn_2_6884 (the latter two NONMATCHING here)
#if NONMATCHING
// fn_2_6D3C, size:0x7C8
void fn_2_6D3C(void) {
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_803C5EA4[0x11] == 0) {
        if (lbl_2_bss_F468[0x2C] == 0) {
            if (lbl_2_bss_F468[0x2D] == 0) {
                fn_800216F8(0x25, fn_8006285C);
                lbl_2_bss_F468[0x2D] = 1;
                return;
            }
            if (lbl_2_bss_F468[0x2D] == 1) {
                if (*(s16*)(lbl_803CC1B8 + 0x10) == 0) {
                    return;
                }
                *(s16*)(lbl_803CC1B8 + 0x10) = 0;
                initializeUnknown();
                fn_800B0A5C_insertQueue(fn_80062A94, 0x1000);
                lbl_2_bss_F468[0x2D] = 0;
            }
        }
        lbl_2_bss_F468[0x2C] = 1;
        if (lbl_2_bss_F468[0x28] == 0 && fn_800697B0() != 0) {
            return;
        }
        lbl_2_bss_F468[0x28] = 1;
        if (lbl_2_bss_F468[0x29] == 0 && fn_80035838(lbl_2_data_720 + 0x5F4, 6) == 0) {
            return;
        }
        lbl_2_bss_F468[0x29] = 1;
        if (lbl_2_bss_F468[0x2A] == 0 && fn_80035838(lbl_2_data_720 + 0x604, 9) == 0) {
            return;
        }
        lbl_2_bss_F468[0x2A] = 1;
        if (lbl_2_bss_F468[0x2B] == 0 && fn_80035838(lbl_2_data_720 + 0x624, 0xF) == 0) {
            return;
        }
        lbl_2_bss_F468[0x2B] = 1;
    }
    if (g_d_GameSettings.GameModeSelected == 5 && starMissionCompletionTracker[0x4445] != 0) {
        starMissionCompletionTracker[0x4445] = 0;
        lbl_803297E0[0xCFA1] = 1;
        if (lbl_80361B20[0xE4] != 0) {
            lbl_803297E0[0xCF70] = 0;
        } else {
            lbl_803297E0[0xCF70] = 1;
        }
        fn_2_BF90();
        unsure_FillRosterPositions(1);
    } else if (g_d_GameSettings.GameModeSelected == 5 && starMissionCompletionTracker[0x4445] == 0) {
        if (starMissionCompletionTracker[0x441D] == 9 && (s8)starMissionCompletionTracker[0x44EF] != 0) {
            fn_2_6784();
        } else {
            fn_2_6AF4();
        }
        fn_2_6884();
        lbl_803297E0[0xCFA1] = 0;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        fn_8006496C();
    }
    fn_2_82E58();
    *(u16*)(lbl_803CBBCC[0] + 4) = 1;
}
#endif

// fn_2_11698, size:0x810
void fn_2_11698(void) {
    s8 best = -1;
    s32 i;
    u8* scene = lbl_803CBBCC[0];
    switch (*(u16*)(scene + 4)) {
    case 0:
        if (*(u16*)(scene + 6) == 0xD) {
            fn_800625A4(0, 0x26);
            *(u16*)(lbl_803CBBCC[0] + 4) = 1;
            return;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            changeScene(1, 6);
            fn_2_836A4();
            lbl_2_bss_F468[0x57] = 0;
            for (i = 0; i < 4; i++) {
                if (lbl_80361B20[0xE4 + i] != 0 && best < i) {
                    best = i;
                }
            }
            if (best != -1) {
                lbl_2_bss_F468[0x57] = best + 1;
                if (lbl_2_bss_F468[0x57] > 3) {
                    lbl_2_bss_F468[0x57] = 3;
                }
            }
            *(u16*)(lbl_803CBBCC[0] + 4) = 5;
            return;
        }
        fn_2_85108();
        if (lbl_803C66B0[0x55] == 0 && lbl_803C66B0[0x56] == 0) {
            lbl_8034E978[0] = 5;
            lbl_8034E978[9] = lbl_8034E978[8];
            lbl_8034E978[8] = *(u16*)(lbl_800FEF70 + 0x58);
            lbl_803C5EA4[0x36] = 1;
            lbl_803C5EA4[0x37] = lbl_803C5EA4[0x38];
            lbl_803C5EA4[0x38] = 2;
            lbl_803C66B0[0] = 4;
            if (lbl_8034E9A0[0x4703] == 0) {
                *(s32*)(lbl_2_bss_F410 + 0x44) = 0;
                *(s32*)(lbl_2_bss_F410 + 0x44) = 0;
            }
            lbl_8034E9A0[0x4703] = 1;
            fn_800625A4(0, 0x27);
            *(u16*)(lbl_803CBBCC[0] + 4) = 1;
        }
        break;
    case 1:
        if (lbl_803C66B0[0x55] == 0 && lbl_803C66B0[0x56] == 0) {
            *(u16*)(lbl_803CBBCC[0] + 4) = 2;
        }
        break;
    case 2:
        for (i = 0; i < 2; i++) {
            fn_2_11340(i);
        }
        break;
    case 3:
        if (lbl_803CBCD8[4] == 0 && lbl_803C66B0[0x5D] == 0) {
            lbl_803C66B0[0] = 3;
            *(u16*)(lbl_803CBBCC[0] + 4) = 0xB;
        }
        break;
    case 4:
        if (lbl_803C66B0[0x5D] == 0) {
            lbl_2_bss_100B4 = 1;
            *(u16*)(lbl_803CBBCC[0] + 4) = 0xC;
        }
        break;
    case 5:
        if (lbl_803C66B0[0x55] == 0) {
            lbl_803CBBC4[0] = 0;
            lbl_803CBBC4[2] = 0;
            lbl_803CBBC4[3] = 0;
            lbl_803CBBC4[4] = 0;
            *(s32*)(lbl_2_bss_F410 + 0x44) = 0;
            changeScene(1, 6);
            lbl_803C5EA4[0x36] = 1;
            lbl_803C5EA4[0x37] = lbl_803C5EA4[0x38];
            lbl_803C5EA4[0x38] = 4;
            lbl_803CBBC4[0] = 0x5D;
            lbl_803CBBC4[5] = 0;
            *(u16*)(lbl_803CBBCC[0] + 4) = 6;
        }
        break;
    case 6:
        if (lbl_803C66B0[0x55] == 0) {
            lbl_803CBBC4[1] = *(s32*)(lbl_2_bss_F410 + 0x44);
            fn_2_15A90((s32*)(lbl_2_bss_F410 + 0x44), 0, lbl_2_bss_F468[0x57]);
            lbl_8034E9A0[0x4711] = *(s32*)(lbl_2_bss_F410 + 0x44);
            if (lbl_803CBBC4[1] != (u8)*(s32*)(lbl_2_bss_F410 + 0x44)) {
                lbl_803CBBC4[0] = 0x5E;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            if (*(u16*)(lbl_8034E9A0 + 0x472E) & 0x100) {
                if (*(s32*)(lbl_2_bss_F410 + 0x44) < 6) {
                    if (lbl_80361B20[0xE3 + lbl_8034E9A0[0x4711]] == 0 && lbl_8034E9A0[0x4711] != 0) {
                        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                        return;
                    }
                    lbl_803CBBC4[0] = 0x60;
                    lbl_8034E9A0[0x472A] = 1;
                    ((void (*)(u32))fn_2_1C34)(0x100);
                    *(u16*)(lbl_803CBBCC[0] + 4) = 7;
                }
            } else if (*(u16*)(lbl_8034E9A0 + 0x472E) & 0x200) {
                ((void (*)(u32))fn_2_1C34)(0x200);
                lbl_803CBBC4[0] = 0x60;
                lbl_8034E9A0[0x472A] = 1;
                *(u16*)(lbl_803CBBCC[0] + 4) = 8;
            }
        }
        break;
    case 7:
        if (lbl_803CBBC4[5] != 0) {
            lbl_803CBBC4[5] = 0;
            lbl_2_bss_100B4 = 1;
            *(u16*)(lbl_803CBBCC[0] + 4) = 0xC;
        }
        break;
    case 8:
        if (lbl_803CBBC4[5] != 0) {
            *(u16*)(lbl_803CBBCC[0] + 4) = 0xB;
        }
        break;
    case 9:
        fn_800B0A5C_insertQueue(fn_8004D0F0, 0x3000);
        *(u16*)(lbl_803CBBCC[0] + 4) = 0xA;
        break;
    case 10:
        switch (fn_8004CA6C(*(u16*)(lbl_8034E9A0 + 0x472E))) {
        case 0:
            break;
        case 1:
            fn_8004CC2C();
            break;
        case 3:
            ((void (*)(u8, s32, s32))fn_2_2FC0)(0xC, 1, 1);
            lbl_803CBCD8[4] = 1;
            fn_80035CA4(0xF);
            fn_80035CA4(0x12);
            fn_80035CA4(9);
            fn_80035CA4(6);
            lbl_8034E9A0[0x48AF] = 1;
            lbl_8034E9A0[0x48B1] = 1;
            lbl_8034E978[0x26] = 1;
            changeScene(0xF, 6);
            *(u16*)(lbl_803CBBCC[0] + 4) = 0xC;
            lbl_2_bss_758 = 1;
            break;
        case 2:
            fn_8004CC2C();
            break;
        case 4:
            lbl_803297E0[0xCF5F] = 0;
            *(u16*)(lbl_803CBBCC[0] + 4) = 2;
            break;
        }
        break;
    case 11:
        if (g_d_GameSettings.GameModeSelected != 5) {
            if (lbl_803CBCD8[4] == 0 && lbl_803C66B0[0x5D] == 0) {
                lbl_803CBCD8[1] = 0;
                lbl_803CBCD8[0] = 0;
                fn_2_11A0(0xB);
                goto reset;
            }
        } else {
            lbl_803CBBC4[4] = 1;
            if (lbl_803C50E8[0x47] == 0) {
                fn_2_11A0(0xF);
            } else {
                lbl_8034E978[0x26] = 1;
                lbl_8034E9A0[0x48AF] = 1;
                fn_2_11A0(5);
            }
        reset:
            *(u16*)(lbl_803CBBCC[0] + 8) = 0;
        }
        break;
    case 12:
        if (lbl_2_bss_758 != 0) {
            if (lbl_8034E978[0x24] == 0) {
                fn_80062A74();
                lbl_2_bss_758 = 0;
                changeScene(0xF, 6);
                fn_2_11A0(4);
            }
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_803CBCD8[4] = 0;
            lbl_2_bss_F468[0x58] = 0;
            fn_2_11A0(0xD);
        } else if (lbl_803CBBC4[3] != 1) {
            lbl_803CBBC4[4] = 1;
            fn_2_11A0(9);
        }
        break;
    }
}

// NONMATCHING 50%: written as plain C; the original unrolls the per-class candidate scan four
// times (one copy per class) and keeps every counter in its own register.
#if NONMATCHING
#define CHAR_CLASS(id) (lbl_8034E9A0[((id) / 9) * 0x5A0 + ((id) % 9) * 0xA0 + 0x31])

// Collects up to 32 unused character ids of one class from lbl_80108DB8; returns count - 1.
static s32 fn_2_F200_collect(s8* cand, u8 cls) {
    s32 i;
    s32 last = -1;
    for (i = 0; i < 32; i++) {
        s8 id = lbl_80108DB8[i];
        if (CHAR_CLASS(id) == cls && lbl_8034E9A0[id + 0x4757] == 0) {
            cand[++last] = id;
        }
    }
    return last;
}

// fn_2_F200, size:0x8A0
void fn_2_F200(u8 team) {
    u8 count[4];
    u8 full[4];
    s8 classes[9];
    s8 cand[32];
    s32 cap = *(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0);
    u8* row = lbl_803C6724 + team * 9;
    s32 i;
    s32 c;
    s32 g;
    s32 k;
    s32 last;
    s8 id;
    for (c = 0; c < 4; c++) {
        count[c] = 0;
        full[c] = 0;
    }
    memset(classes, -1, 9);
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[i + 2];
        if (v != -1 && v != 0x36) {
            classes[i] = CHAR_CLASS((s8)row[i + 2]);
            c = classes[i];
            if (c >= 0 && c < 4) {
                if (++count[c] >= 2) {
                    full[c] = 1;
                }
            }
        }
    }
    for (i = 0; i < 9; i++) {
        s32 v = (s8)row[i + 2];
        if (v != -1 && v != 0x36) {
            continue;
        }
        memset(cand, -1, 8);
        id = -1;
        for (c = 0; c < 4; c++) {
            if (full[c] == 0) {
                break;
            }
        }
        if (c < 4) {
            last = fn_2_F200_collect(cand, c);
            if (cand[0] != -1) {
                if (++count[c] >= 2) {
                    full[c] = 1;
                }
                id = cand[randRange_FUN_80042bf0(0, (s8)last)];
            }
        }
        if (id == -1) {
            do {
                id = randRange_FUN_80042bf0(0, 0x35);
            } while (lbl_8034E9A0[id + 0x4757] != 0);
        }
        fn_80067B40(team, id, 1);
        for (g = 0; g < 9; g++) {
            for (k = 0; k < 5; k++) {
                if (id == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                    s16* grp = (s16*)(lbl_80108EDC + g * 10);
                    lbl_8034E9A0[grp[1] + 0x4757] = 1;
                    lbl_8034E9A0[grp[2] + 0x4757] = 1;
                    id = grp[0];
                    lbl_8034E9A0[grp[3] + 0x4757] = 1;
                    lbl_8034E9A0[grp[4] + 0x4757] = 1;
                    goto found;
                }
            }
        }
    found:
        if (g_d_GameSettings._10 == 0 && team != 0) {
            if (*(s8*)(lbl_8034E9A0 + 0x46F8) == 0) {
                fn_800506E8(1, id, 1);
            } else {
                fn_800506E8(1, id, 1);
            }
        } else {
            fn_800506E8(*(s8*)(lbl_8034E9A0 + team + 0x46F8), id, 1);
        }
        row[i + 2] = id;
        lbl_8034E9A0[id + 0x4757] = 1;
        row[i + 0x26] = (lbl_8034E9A0 + cap)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x3B];
    }
}
#endif

// NONMATCHING 95%: inlines fn_2_1A88/fn_2_1BAC/fn_2_1800 (the last NONMATCHING); the case-2 button copy reloads one word
#if NONMATCHING
static inline void fn_2_1F30_unload(void) {
    fn_80035B50(0xF);
    fn_80035B50(0x12);
    fn_80035B50(9);
    fn_80035B50(6);
    fn_800AD054(*(void**)(lbl_8034E9A0 + 0x46F0), *(void**)(lbl_8034E9A0 + 0x46F4));
}

// fn_2_1F30, size:0x8B0
void fn_2_1F30(void) {
    switch (*(u16*)(lbl_803CBBCC[0] + 4)) {
    case 0:
        if (*(u16*)(lbl_803CBBCC[0] + 6) < 5) {
            fn_2_1A88();
        }
        fn_2_1BAC();
        memset(lbl_8034E9A0 + 0x4712, 0, 2);
        ((s32*)lbl_2_bss_F410)[0] = lbl_8034E9A0[0x4712];
        ((s32*)lbl_2_bss_F410)[1] = lbl_8034E9A0[0x4713];
        g_d_GameSettings._10 = 0;
        lbl_803C66B0[0] = 0;
        memset(lbl_803C66B0 + 1, 0, 6);
        lbl_8034E9A0[0x472A] = 0xFF;
        fn_2_74D8C();
        fn_800625A4(0, 0x54);
        (*(u16*)(lbl_803CBBCC[0] + 4))++;
        break;
    case 1:
        (*(u16*)(lbl_803CBBCC[0] + 4))++;
        break;
    case 2:
        fn_2_1800();
        break;
    case 3:
        lbl_8034E9A0[0x4728] = g_d_GameSettings.GameModeSelected;
        lbl_8034E9A0[0x4729] = g_d_GameSettings._10;
        g_d_GameSettings.exhibitionMatchInd = 1;
        if (g_d_GameSettings.GameModeSelected == 0) {
            fn_2_11A0(9);
        } else if (g_d_GameSettings.GameModeSelected == 5) {
            if (lbl_803C50E8[0x47] != 0) {
                g_d_GameSettings._10 = 0;
                fn_2_11A0(0xC);
            } else {
                fn_2_11A0(0xF);
            }
        } else {
            fn_80062A74();
            fn_2_1F30_unload();
            fn_80021410();
            fn_800ACFB0(*(void**)(lbl_800EF808 + 0x98));
            fn_2_11A0(4);
        }
        lbl_2_bss_20[0] = 0;
        break;
    case 4:
        lbl_8034E9A0[0x48AF] = 1;
        lbl_8034E9A0[0x48B1] = 1;
        *(u16*)(lbl_803CBBCC[0] + 4) = 3;
        break;
    case 5:
        if (lbl_803C66B0[0x55] == 0) {
            lbl_8034E9A0[0x4712] = ((s32*)lbl_2_bss_F410)[0];
            lbl_8034E9A0[0x4713] = ((s32*)lbl_2_bss_F410)[1];
            switch (lbl_8034E9A0[0x4708]) {
            case 0:
                fn_80021AC8();
                fn_2_82E58();
                changeScene(3, 6);
                *(u16*)(lbl_803CBBCC[0] + 4) = 3;
                break;
            default:
                *(u16*)(lbl_803CBBCC[0] + 4) = 4;
                break;
            case 6:
                lbl_8034E9A0[0x48AF] = 1;
                lbl_8034E9A0[0x48B1] = 1;
                changeScene(3, 6);
                *(u16*)(lbl_803CBBCC[0] + 4) = 8;
                break;
            case 5:
                lbl_8034E9A0[0x48AF] = 1;
                lbl_8034E9A0[0x48B1] = 1;
                changeScene(3, 6);
                *(u16*)(lbl_803CBBCC[0] + 4) = 0xA;
                break;
            case 1:
                lbl_8034E9A0[0x4756] = 0;
                lbl_8034E9A0[0x48AF] = 1;
                lbl_8034E9A0[0x48B1] = 1;
                changeScene(3, 6);
                *(u16*)(lbl_803CBBCC[0] + 4) = 3;
                break;
            }
            lbl_8034E9A0[0x472A] = 0;
        }
        break;
    case 6:
        lbl_803CBCE0[0] = 0;
        lbl_8034E9A0[0x48B4] = 0;
        fn_80062A74();
        fn_2_1F30_unload();
        fn_2_11A0(1);
        lbl_2_bss_20[0] = 0;
        break;
    case 7:
        lbl_8034E9A0[0x472A] = 0;
        fn_2_11A0(1);
        lbl_803CBCE0[0] = 0;
        lbl_8034E9A0[0x48B4] = 0;
        break;
    case 8:
        fn_2_11A0(6);
        lbl_2_bss_20[0] = 0;
        break;
    case 9:
        fn_80062A74();
        fn_2_1F30_unload();
        fn_80021410();
        fn_800ACFB0(*(void**)(lbl_800EF808 + 0x98));
        fn_2_11A0(7);
        lbl_2_bss_20[0] = 0;
        break;
    case 10:
        fn_2_1F30_unload();
        fn_2_11A0(8);
        lbl_2_bss_20[0] = 0;
        break;
    }
}
#endif

// NONMATCHING 70%: the release sequence is duplicated in the original (once per branch) and
// fn_2_C698 is inlined into each copy.
#if NONMATCHING
static void fn_2_4970_release(u8 team, s32 slot) {
    u8* row = lbl_803C6724 + team * 9;
    s32 g = 0;
    s32 i;
    s32 k;
    s32 dup = 0;
    fn_2_C698(slot, team);
    if (g_d_GameSettings.GameModeSelected != 5) {
        fn_800506E8(team, (s8)row[slot + 2], 0);
        fn_80067B40(team, row[slot + 2], 0);
        lbl_8034E9A0[(s8)row[slot + 2] + 0x4757] = 0;
    } else if (fn_80067B40(team, row[slot + 2], 2) != 0) {
        for (i = 0; i < 9; i++) {
            for (k = 0; k < 5; k++) {
                if ((s8)row[slot + 2] == *(s16*)(lbl_80108EDC + i * 10 + k * 2)) {
                    g = i;
                    goto found;
                }
            }
        }
    found:
        for (i = 0; i < 9; i++) {
            for (k = 0; k < 5; k++) {
                s16 m = *(s16*)(lbl_80108EDC + g * 10 + k * 2);
                if ((s8)row[i + 2] == m && m != -1 && (s8)row[i + 2] != (s8)row[slot + 2]) {
                    dup = 1;
                }
            }
        }
        if (dup == 0) {
            fn_800506E8(team, (s8)fn_80067AC8((s8)row[slot + 2], 0), 0);
            lbl_8034E9A0[fn_80067AC8((s8)row[slot + 2], 0) + 0x4757] = 0;
        }
    } else {
        fn_800506E8(team, (s8)row[slot + 2], 0);
        lbl_8034E9A0[(s8)row[slot + 2] + 0x4757] = 0;
    }
    row[slot + 0x26] = 0;
    row[slot + 2] = -1;
}

// fn_2_4970, size:0x814
void fn_2_4970(u8 team, s32 empty) {
    s32* state = (s32*)lbl_2_bss_F468;
    s32 cur = state[team];
    u8* row = lbl_803C6724 + team * 9;
    s32 slot = 0; // uninitialized in the original if no position matches
    s32 j;
    s8 v;
    for (j = 0; j < 9; j++) {
        if ((s8)row[j + 0x14] == cur) {
            slot = j;
        }
    }
    v = row[slot + 2];
    if (v == empty) {
        if (--state[team] < 0) {
            state[team] = 8;
        }
    } else {
        if (lbl_2_bss_F468[team + 0x37] == 0 && lbl_2_bss_F468[team + 0x3D] == 0) {
            state[team + 2] = cur;
            if (--state[team] < 0) {
                state[team] = 8;
            }
            if (v != -1 && v != 0x36) {
                fn_2_4970_release(team, slot);
                row[slot + 0x4A] = 0;
            }
        } else {
            fn_2_4970_release(team, slot);
            lbl_2_bss_F468[team + 0x3D] = 0;
            row[slot + 0x4A] = 0;
        }
        lbl_2_bss_F468[team + 0x37] = 0;
    }
    fn_800625A4(team, 0x10);
}
#endif

// NONMATCHING 85%: plain loops; the original unrolls the unique-position check and the
// 54-entry star-rating table.
#if NONMATCHING
// fn_2_7504, size:0x840
void fn_2_7504(void) {
    s32 free = 0;
    u8 unique = 0;
    u8 u;
    s32 t;
    s32 i;
    u32 cap;
    lbl_803CBD24[2] = 0;
    lbl_803CBD24[3] = 0xFF;
    lbl_2_bss_F468[0x62] = -1;
    lbl_2_bss_F468[0x61] = -1;
    lbl_2_bss_F468[0x66] = 0;
    lbl_2_bss_F468[0x65] = 0;
    if (*(u16*)(lbl_803CBBCC[0] + 6) != 9) {
        if (g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) {
            lbl_2_bss_100B8[0x2E] = 1;
            lbl_2_bss_100B8[0x2F] = 1;
        } else {
            lbl_2_bss_100B8[0x2F] = 0;
            lbl_2_bss_100B8[0x2E] = 0;
        }
        if (g_d_GameSettings.GameModeSelected == 5) {
            for (t = 0; t < 2; t++) {
                u8* row = lbl_803C6724 + t * 9;
                if (t == 0) {
                    cap = starMissionCompletionTracker[0x441D];
                    u = 1;
                    for (i = 1; i < 9; i++) {
                        if ((s8)starMissionCompletionTracker[0x40BB] == (s8)starMissionCompletionTracker[0x40BB + i * 6]) {
                            u = 0;
                        }
                    }
                    unique = u;
                } else {
                    cap = (u8)(s8)starMissionCompletionTracker[0x441F];
                }
                for (i = 0; i < 9; i++) {
                    s8 id = row[i + 2];
                    if (t == 0 && lbl_803297E0[0xCFA1] == 0) {
                        row[i + 0x14] = starMissionCompletionTracker[0x40BB + i * 6];
                    } else if (t == 0 && unique != 0) {
                        row[i + 0x14] = starMissionCompletionTracker[0x40BB + i * 6];
                    } else {
                        row[i + 0x14] = i;
                    }
                    row[i + 0x26] = (lbl_8034E9A0 + cap)[(id / 9) * 0x5A0 + (id % 9) * 0xA0 + 0x3B];
                }
            }
            for (i = 0; i < 0x36; i++) {
                MenuCharStats* c = (MenuCharStats*)(lbl_8034E9A0 + (i / 9) * 0x5A0 + (i % 9) * 0xA0);
                lbl_2_bss_3A8[i] = c->b27 + c->b26 * 2;
            }
            if (*(u16*)(lbl_803CBBCC[0] + 6) != 0xB && lbl_803297E0[0xCFA1] == 0) {
                for (i = 0; i < 9; i++) {
                    lbl_2_bss_3A8[*(s16*)(starMissionCompletionTracker + 0x40B8 + i * 6)] =
                        starMissionCompletionTracker[0x40BC + i * 6];
                }
            }
        }
    } else {
        for (t = 0; t < 2; t++) {
            u8* row = lbl_803C6724 + t * 9;
            for (i = 0; i < 9; i++) {
                row[i + 0x14] = i;
                row[i + 0x4A] = 0;
                row[i + 0x26] = 0;
                if (i != 0) {
                    row[i + 2] = -1;
                }
            }
        }
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (t = 0; t < 2; t++) {
            fn_800678CC(t);
        }
    }
    lbl_8034E9A0[0x4702] = 1;
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 0x36; i++) {
            if (lbl_8034E9A0[i + 0x4757] == 0) {
                free++;
            }
        }
        if (free == 0) {
            lbl_2_bss_F468[0x3F] = 1;
            lbl_2_bss_F468[0x37] = 1;
            ((s32*)lbl_2_bss_F468)[0] = 9;
            return;
        }
        lbl_2_bss_F468[0x3F] = 0;
    }
}
#endif

// NONMATCHING 80%: same copies; loop pointer registers and some load scheduling differ.
#if NONMATCHING
#define FN_2_8CF8_SAVE(t, i)                                                      \
    do {                                                                          \
        MenuCharStats* src = &g_Roster[(t) * 9 + (i)];                            \
        MenuCharStats* dst = &((MenuCharStats*)lbl_2_bss_E8CC)[(t) * 9 + (i)];    \
        u8* order = lbl_80354720 + (t) * 0x24 + (i) * 4;                          \
        u8* saved = lbl_2_bss_DCE8 + (t) * 0x24 + (i) * 4;                        \
        MENU_COPY_CHAR_STATS(dst, src);                                           \
        saved[0] = order[0];                                                      \
        saved[1] = order[1];                                                      \
        saved[2] = order[2];                                                      \
        saved[3] = order[3];                                                      \
        lbl_2_bss_3E4[(t) * 9 + (i)] = src->h24;                                  \
    } while (0)

#define FN_2_8CF8_LOAD(t, i)                                                      \
    do {                                                                          \
        MenuCharStats* dst = &g_Roster[(t) * 9 + (i)];                            \
        MenuCharStats* src = &((MenuCharStats*)lbl_2_bss_E8CC)[(t) * 9 + (i)];    \
        u8* order = lbl_80354720 + (t) * 0x24 + (i) * 4;                          \
        u8* saved = lbl_2_bss_DCE8 + (t) * 0x24 + (i) * 4;                        \
        MENU_COPY_CHAR_STATS(dst, src);                                           \
        order[0] = saved[0];                                                      \
        order[1] = saved[1];                                                      \
        order[2] = saved[2];                                                      \
        order[3] = saved[3];                                                      \
        dst->h24 = lbl_2_bss_3E4[(t) * 9 + (i)];                                  \
    } while (0)

// fn_2_8CF8, size:0x8E0
void fn_2_8CF8(u16 team) {
    s32 t;
    s32 i;
    if (lbl_2_bss_100B8[team + 0x30] != 0) {
        if (g_d_GameSettings._10 != 1) {
            for (t = 0; t < 2; t++) {
                for (i = 0; i < 9; i++) {
                    FN_2_8CF8_SAVE(t, i);
                }
            }
        } else {
            for (i = 0; i < 9; i++) {
                FN_2_8CF8_SAVE(team, i);
            }
        }
        fn_2_9ACC(team);
        return;
    }
    if (g_d_GameSettings._10 != 1) {
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                FN_2_8CF8_LOAD(t, i);
            }
        }
        return;
    }
    for (i = 0; i < 9; i++) {
        FN_2_8CF8_LOAD(team, i);
    }
}
#endif

// NONMATCHING 70%: plain loops; fn_2_348C inlines into the non-challenge branch as in the original.
#if NONMATCHING
// fn_2_7DDC, size:0x910
void fn_2_7DDC(void) {
    u8 buf[4];
    s32 i;
    s32 t;
    s32 g;
    s32 k;
    s32* sel;
    if (g_d_GameSettings.GameModeSelected != 5) {
        memset(lbl_8034E9A0 + 0x4757, 0, 0x36);
    }
    lbl_8034E9A0[0x48AD] = 0;
    lbl_803C66B0[0] = 2;
    memset(buf, 0xFF, 4);
    if (*(u16*)(lbl_803CBBCC[0] + 6) == 9) {
        lbl_803C66B0[0x59] = 0;
        lbl_803C66B0[0x5A] = 1;
    } else {
        if (g_d_GameSettings._10 == 0 && g_d_GameSettings.GameModeSelected != 5) {
            lbl_803C66B0[0x59] = 1;
        } else {
            lbl_803C66B0[0x59] = 0;
        }
        lbl_803C66B0[0x5A] = 1;
    }
    memset(buf, 0, 4);
    if (g_d_GameSettings._10 == 0) {
        buf[*(s8*)(lbl_8034E9A0 + 0x46F8)] = 1;
        if (*(s8*)(lbl_8034E9A0 + 0x46F8) == 0) {
            buf[1] = 2;
        } else {
            buf[0] = 2;
        }
    } else {
        buf[*(s8*)(lbl_8034E9A0 + 0x46F9)] = 1;
        buf[*(s8*)(lbl_8034E9A0 + 0x46F8)] = 1;
    }
    if (g_d_GameSettings.GameModeSelected != 5) {
        fn_80050FE8(buf[0], buf[1], buf[2], buf[3], 0, 1);
    } else {
        fn_80050FE8(buf[0], buf[1], buf[2], buf[3], 0, 0);
    }
    fn_2_7265C();
    lbl_8034E9A0[0x472A] = 0xFF;
    if (*(u16*)(lbl_803CBBCC[0] + 6) != 0xB && g_d_GameSettings.GameModeSelected != 5) {
        ((s32*)lbl_2_bss_F468)[0] = 0xA;
        ((s32*)lbl_2_bss_F468)[1] = 0xA;
    } else {
        ((s32*)lbl_2_bss_F468)[0] = 9;
        ((s32*)lbl_2_bss_F468)[1] = 9;
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 0x36; i++) {
            if (starMissionCompletionTracker[i * 0x34 + 0x31] == 1) {
                lbl_8034E9A0[i + 0x4757] = 0;
                fn_800506E8(0, i, 0);
            } else {
                s16 alt;
                lbl_8034E9A0[i + 0x4757] = 1;
                alt = fn_80067AC8(i, 0);
                if (alt != -1 && starMissionCompletionTracker[alt * 0x34 + 0x31] == 1) {
                    fn_800506E8(0, i, 0);
                } else {
                    fn_800506E8(0, i, 1);
                }
            }
        }
        for (i = 0; i < 9; i++) {
            s8 id = lbl_803C6724[i + 2];
            lbl_8034E9A0[id + 0x4757] = 1;
            fn_800506E8(0, id, 1);
            if (fn_80067B40(0, lbl_803C6724[i + 2], 2) != 0) {
                for (g = 0; g < 9; g++) {
                    for (k = 0; k < 5; k++) {
                        if ((s8)lbl_803C6724[i + 2] == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                            s16* grp = (s16*)(lbl_80108EDC + g * 10);
                            s32 m;
                            for (m = 0; m < 5; m++) {
                                if (grp[m] == -1) {
                                    goto next;
                                }
                                lbl_8034E9A0[grp[m] + 0x4757] = 1;
                            }
                        }
                    }
                }
            }
        next:;
        }
        lbl_2_bss_F468[0x37] = 1;
    } else {
        fn_2_348C();
        for (t = 0; t < 2; t++) {
            for (i = 0; i < 9; i++) {
                s8 id = lbl_803C6724[t * 9 + i + 2];
                if (id == -1) {
                    continue;
                }
                lbl_8034E9A0[id + 0x4757] = 1;
                if (g_d_GameSettings._10 == 0 && t != 0) {
                    if (*(s8*)(lbl_8034E9A0 + 0x46F8) == 0) {
                        fn_800506E8(1, id, 1);
                    } else {
                        fn_800506E8(0, id, 1);
                    }
                } else {
                    fn_800506E8(*(s8*)(lbl_8034E9A0 + 0x46F8 + t), (s8)lbl_803C6724[t * 9 + i + 2], 1);
                }
                fn_80067B40(t, lbl_803C6724[t * 9 + i + 2], 1);
            }
        }
    }
    for (t = 0; t < 2; t++) {
        sel = (s32*)lbl_2_bss_F410 + 8 + t;
        if (g_d_GameSettings._10 == 0 && t != 0) {
            lbl_803C6028[0x74 + *(s8*)(lbl_8034E9A0 + 0x46F8 + t)] = 1;
        } else {
            lbl_803C6028[0x74 + *(s8*)(lbl_8034E9A0 + 0x46F8 + t)] = 0;
        }
        if (t != 0) {
            *sel = 9;
        } else {
            *sel = 0;
        }
        if (lbl_8034E9A0[*sel + 0x4757] != 0) {
            for (i = 0; i < 32; i++) {
                u8 c = lbl_800FDE84[i];
                if (lbl_8034E9A0[c + 0x4757] == 0 && c != 0xFF) {
                    *sel = lbl_800FDE84[i];
                    break;
                }
            }
        }
        switch (*(s8*)(lbl_8034E9A0 + 0x46F8 + t)) {
        case 0:
            fn_80050138(1, *sel, -1, -1, -1, 0);
            break;
        case 1:
            fn_80050138(1, -1, *sel, -1, -1, 0);
            break;
        case 2:
            fn_80050138(1, -1, -1, *sel, -1, 0);
            break;
        case 3:
            fn_80050138(1, -1, -1, -1, *sel, 0);
            break;
        }
    }
    if (*(u16*)(lbl_803CBBCC[0] + 6) == 9) {
        fn_800625A4(0, 0xA);
        fn_800625A4(1, 0xA);
    } else if (*(u16*)(lbl_803CBBCC[0] + 6) != 0xB && g_d_GameSettings.GameModeSelected == 5) {
        fn_800625A4(0, 0xA);
        fn_800625A4(1, 0xA);
    } else {
        fn_800625A4(0, 9);
        fn_800625A4(1, 9);
    }
    lbl_803C66B0[0] = 2;
}
#endif

// NONMATCHING 70%: plain C; the original inlines fn_2_5184/fn_2_C698 and unrolls the counting loops.
#if NONMATCHING
// fn_2_DFAC, size:0xB34
void fn_2_DFAC(u8 team) {
    s32* state = (s32*)lbl_2_bss_F468;
    s32* sel = (s32*)lbl_2_bss_F410 + 8;
    s32 cur = state[team];
    s32 cap = *(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0);
    u8* row = lbl_803C6724 + team * 9;
    s32 slot = 0;
    s32 locked;
    s32 n = 0;
    s32 free = 0;
    s32 g = -1;
    s32 i;
    s32 k;
    s32 id;
    s8 p;
    if (lbl_803C66B0[0x5D] == 0xB) {
        return;
    }
    for (i = 0; i < 9; i++) {
        if ((s8)cur == (s8)row[i + 0x14]) {
            slot = i;
            break;
        }
    }
    locked = g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468[0x3F] != 0;
    if (lbl_2_bss_F468[0x41 + team] == 0) {
        if (state[team] == 9) {
            fn_2_5444(team);
            ((void (*)(u32))fn_2_1C34)(0x100);
            return;
        }
        if (state[team] == 10) {
            if (locked) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            fn_2_5184(team);
            ((void (*)(u32))fn_2_1C34)(0x100);
            return;
        }
        if ((s8)row[slot + 2] == *(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0)) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (locked) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        lbl_2_bss_F468[0x41 + team] = 1;
        fn_800625A4(team, 0xD);
        ((void (*)(u32))fn_2_1C34)(0x100);
        return;
    }
    id = sel[team];
    if (lbl_8034E9A0[id + 0x4757] != 0 || id == -1) {
        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
        return;
    }
    if (locked) {
        return;
    }
    if (g_d_GameSettings._10 == 1 && id != -1) {
        u8 other = team ^ 1;
        if (id == sel[other] && lbl_2_bss_F468[0x41 + other] != 0) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
    }
    p = row[slot + 2];
    if (g_d_GameSettings.GameModeSelected != 5) {
        if (p != -1 && p != 0x36) {
            fn_800506E8(team, p, 0);
            lbl_8034E9A0[(s8)row[slot + 2] + 0x4757] = 0;
            fn_80067B40(team, row[slot + 2], 0);
        }
    } else {
        for (i = 0; i < 9; i++) {
            s8 v = row[i + 2];
            if (v != -1 && v != 0x36 && v != cap) {
                n++;
            }
        }
        for (i = 0; i < 0x36; i++) {
            if (lbl_8034E9A0[i + 0x4757] == 0) {
                free++;
            }
        }
        if (free <= 8 - n && p != -1 && p != 0x36) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (p != -1 && p != 0x36) {
            if (fn_80067B40(team, row[slot + 2], 2) != 0) {
                for (i = 0; i < 9 && g == -1; i++) {
                    for (k = 0; k < 5; k++) {
                        if ((s8)row[slot + 2] == *(s16*)(lbl_80108EDC + i * 10 + k * 2)) {
                            g = i;
                            break;
                        }
                    }
                }
                if (g != -1) {
                    for (i = 0; i < 9; i++) {
                        for (k = 0; k < 5; k++) {
                            s16 m = *(s16*)(lbl_80108EDC + g * 10 + k * 2);
                            if ((s8)row[i + 2] == m && i != slot && m != -1) {
                                goto assign;
                            }
                        }
                    }
                    fn_800506E8(team, (s8)fn_80067AC8((s8)row[slot + 2], 0), 0);
                    lbl_8034E9A0[fn_80067AC8((s8)row[slot + 2], 0) + 0x4757] = 0;
                }
            } else {
                fn_800506E8(team, (s8)row[slot + 2], 0);
                lbl_8034E9A0[(s8)row[slot + 2] + 0x4757] = 0;
            }
        }
    }
assign:
    row[slot + 2] = sel[team];
    row[slot + 0x4A] = 1;
    fn_800628D4((s8)row[slot + 2]);
    fn_800678CC(team);
    fn_2_C698(slot, team);
    lbl_803C5EA4[team + 0xC] = slot;
    lbl_803C5EA4[team + 0xA] = 1;
    row[slot + 0x26] = (lbl_8034E9A0 + cap)[(sel[team] / 9) * 0x5A0 + (sel[team] % 9) * 0xA0 + 0x3B];
    fn_800625A4(team, 0xF);
    if (lbl_2_bss_F468[0x37 + team] != 0) {
        lbl_2_bss_F468[0x41 + team] = 0;
    }
}
#endif

// NONMATCHING 70%: plain C; the original inlines fn_2_35D0, fn_2_A040 and fn_2_C698 and
// unrolls the slot searches.
#if NONMATCHING
// fn_2_104FC, size:0xBB4
void fn_2_104FC(u16 port) {
    u8 team = lbl_803C66B0[0x59 + port];
    s32* state = (s32*)lbl_2_bss_F468;
    s32* sel = (s32*)lbl_2_bss_F410 + 8;
    u8* row = lbl_803C6724 + team * 9;
    u16 held;
    u16 down;
    u16 repeat;
    s32 slot = 0;
    s32 n = 0;
    s32 i;
    s32 g;
    s32 k;
    s8 owner;
    if (lbl_803C66B0[0x5D + team] != 0) {
        down = 0;
        repeat = 0;
        held = 0;
    } else if (g_d_GameSettings._10 == 1 && lbl_2_bss_100B8[0x2E + team] != 0) {
        held = *(u16*)(lbl_8034E9A0 + port * 6 + 0x472C) & 0x200;
        down = *(u16*)(lbl_8034E9A0 + port * 6 + 0x472E) & 0x200;
        repeat = *(u16*)(lbl_8034E9A0 + port * 6 + 0x4730) & 0x200;
    } else if (lbl_2_bss_F468[0x52 + team] != 0) {
        down = 0;
        repeat = 0;
        held = 0;
    } else {
        held = *(u16*)(lbl_8034E9A0 + port * 6 + 0x472C);
        down = *(u16*)(lbl_8034E9A0 + port * 6 + 0x472E);
        repeat = *(u16*)(lbl_8034E9A0 + port * 6 + 0x4730);
    }
    if (down & 0x1000) {
        return;
    }
    if (down & 0x40) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468[0x41 + team] != 0) {
            if (g_d_GameSettings.GameModeSelected != 5 && lbl_8034E9A0[sel[team] + 0x4757] == 0) {
                owner = *(s8*)(lbl_8034E9A0 + 0x46F8 + team);
                if (*(s8*)(lbl_8034E9A0 + 0x46FC + owner) != 0) {
                    owner = *(s8*)(lbl_8034E9A0 + 0x46F8) == 0;
                }
                sel[team] = fn_80050760(owner, held, down, repeat, 0);
            }
        } else if (g_d_GameSettings.GameModeSelected != 5) {
            s8 v;
            for (i = 0; i < 9; i++) {
                if ((s8)row[i + 0x14] == state[team]) {
                    slot = i;
                    break;
                }
            }
            v = row[slot + 2];
            if (v == -1 || v == 0x36) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            if (state[team] == 9 || state[team] == 10) {
                sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
                return;
            }
            lbl_2_bss_F468[0x50 + team] = 0;
            for (g = 0; g < 9; g++) {
                for (k = 0; k < 5; k++) {
                    if (v == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                        lbl_2_bss_F468[0x50 + team] = 1;
                        goto found;
                    }
                }
            }
        found:
            if (lbl_2_bss_F468[0x50 + team] != 0) {
                fn_2_A040(g, k, team, slot);
                fn_2_C698(slot, team);
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
        }
    } else if (down & 0x800) {
        if (fn_2_35D0(team)) {
            return;
        }
        for (i = 0; i < 9; i++) {
            s8 v = row[i + 2];
            if (v != -1 && v != 0x36) {
                n++;
            }
        }
        if (n != 1 && g_d_GameSettings.GameModeSelected != 5) {
            for (i = 1; i < 9; i++) {
                s8 v = row[i + 2];
                if (v != -1 && v != 0x36) {
                    lbl_8034E9A0[v + 0x4757] = 0;
                    fn_800506E8(*(s8*)(lbl_8034E9A0 + 0x46F8 + team), v, 0);
                    fn_80067B40(team, row[i + 2], 0);
                    row[i + 2] = -1;
                    row[i + 0x4A] = 0;
                    row[i + 0x26] = 0;
                }
            }
            lbl_2_bss_F468[0x37 + team] = 0;
            lbl_2_bss_F468[0x41 + team] = 0;
            lbl_2_bss_F468[0x50 + team] = 0;
            state[team + 2] = state[team];
            state[team] = 0xA;
            lbl_2_bss_F468[0x3D + team] = 0;
            lbl_2_bss_F468[0x52 + team] = 1;
        }
    } else if (down & 0x10) {
        if (fn_2_35D0(team)) {
            return;
        }
        for (i = 0; i < 9; i++) {
            if ((s8)row[i + 0x14] == state[team]) {
                slot = i;
                break;
            }
        }
        if (state[team] != 0xA && state[team] != 9) {
            s8 v = row[slot + 2];
            if (v != -1 && v != 0x36 && lbl_2_bss_F468[0x41 + team] == 0) {
                lbl_2_bss_F468[0x45 + team] = 1;
                lbl_2_bss_F468[0x4B + team] = 1;
                lbl_2_bss_F468[0x47 + team] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
                return;
            }
        }
        if (lbl_2_bss_F468[0x41 + team] != 0) {
            if (lbl_8034E9A0[sel[team] + 0x4757] == 0 && sel[team] != -1) {
                lbl_2_bss_F468[0x45 + team] = 1;
                lbl_2_bss_F468[0x4B + team] = 1;
                lbl_2_bss_F468[0x47 + team] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            }
        }
    } else if (down & 0x20) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (lbl_2_bss_F468[0x59 + team] == 0) {
            lbl_2_bss_F468[0x59 + team] = 1;
            lbl_2_bss_F468[0x61 + team] = -1;
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            if (lbl_2_bss_F468[0x41 + team] != 0) {
                lbl_2_bss_F468[0x41 + team] = 0;
                fn_800625A4(team, 0xD);
                return;
            }
            if (state[team] == 0xA) {
                lbl_2_bss_F468[0x63 + team] = 1;
                state[team + 2] = state[team];
                state[team] = 1;
                fn_800625A4(team, 0xE);
                return;
            }
            fn_800625A4(team, 0x1A);
        }
    } else {
        fn_2_ED94(team, held, down, repeat);
    }
}
#endif

// NONMATCHING 60%: plain C; the original inlines fn_2_EC54/fn_2_C698 at every use, unrolls
// the slot searches and shares one fn_2_1C34(0x200) tail.
#if NONMATCHING
static void fn_2_CE44_clear_ratings(void) {
    s32 i;
    for (i = 0; i < 9; i++) {
        lbl_803C6724[0x26 + i] = 0;
    }
    for (i = 0; i < 9; i++) {
        lbl_803C6724[0x2F + i] = 0;
    }
}

static void fn_2_CE44_reset_both(void) {
    lbl_2_bss_100B8[0x2F] = 0;
    lbl_2_bss_100B8[0x2E] = 0;
    lbl_803C5EA4[0xE] = 0;
    lbl_803C66B0[0x5A] = 0;
    lbl_803C66B0[0x59] = 0;
    ((s32*)lbl_2_bss_F468)[1] = 9;
    ((s32*)lbl_2_bss_F468)[0] = 9;
    fn_800625A4(0, 0x12);
}

// fn_2_CE44, size:0x1168
void fn_2_CE44(s8 team) {
    s32* state = (s32*)lbl_2_bss_F468;
    s32 cap;
    u8* row;
    s32 n = 0;
    s8 free = 0;
    s32 slot = 0; // uninitialized in the original if no position matches
    s32 st;
    s32 i;
    s32 t;
    if (g_d_GameSettings.GameModeSelected == 5 && lbl_2_bss_F468[0x3F] != 0) {
        sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
        return;
    }
    if (lbl_2_bss_F468[0x41 + team] != 0) {
        lbl_2_bss_F468[0x41 + team] = 0;
        fn_800625A4(team, 0xD);
        goto end;
    }
    cap = *(s32*)(lbl_8034E9A0 + team * 4 + 0x46E0);
    row = lbl_803C6724 + team * 9;
    for (i = 0; i < 9; i++) {
        s8 v = row[i + 2];
        if (v != -1 && v != 0x36 && v != cap) {
            n++;
        }
    }
    if (g_d_GameSettings.GameModeSelected == 5) {
        for (i = 0; i < 0x36; i++) {
            if (lbl_8034E9A0[i + 0x4757] == 0) {
                free++;
            }
        }
        if (free <= 8 - n) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
    }
    state[team + 2] = state[team];
    if (n == 0) {
        lbl_2_bss_F468[0x37 + team] = 0;
        if (state[team] == 9) {
            state[team] = 0;
            switch (team) {
            case 0:
                if ((s8)lbl_803C6724[2] == *(s32*)(lbl_8034E9A0 + 0x46E0)) {
                    state[0] = 1;
                }
                break;
            case 1:
                if ((s8)lbl_803C6724[0xB] == *(s32*)(lbl_8034E9A0 + 0x46E4)) {
                    state[1] = 1;
                }
                break;
            }
        }
    }
    if (g_d_GameSettings._10 == 0) {
        st = state[team];
        if (st != 9 && st != 10 && n != 0) {
            fn_2_4970(team, cap);
            goto end;
        }
        if (st == 9) {
            state[team + 2] = state[team];
            state[team]--;
            if (cap == (s8)row[8 + 2]) {
                state[team]--;
            }
            fn_800625A4(team, 0x15);
            goto end;
        }
        if (st == 10) {
            if (n == 0 && lbl_803C5EA4[0xE] != 0) {
                fn_2_CE44_reset_both();
                goto end;
            }
            if (n == 0 && lbl_803C5EA4[0xE] == 0) {
                if (lbl_803C66B0[0x55] == 0 && lbl_803C66B0[0x56] == 0) {
                    fn_2_CE44_clear_ratings();
                    fn_2_EC54(team);
                    goto end;
                }
                return;
            }
            state[team + 2] = state[team];
            state[team] = 8;
            if (cap == (s8)row[8 + 2]) {
                state[team]--;
            }
            fn_800625A4(team, 0x15);
            goto end;
        }
        if (lbl_2_bss_F468[0x37] != 0 && n == 0) {
            fn_2_CE44_reset_both();
            goto end;
        }
        if (n == 0) {
            if (lbl_803C66B0[0x55] == 0 && lbl_803C66B0[0x56] == 0) {
                fn_2_CE44_clear_ratings();
                fn_2_EC54(team);
                goto end;
            }
            return;
        }
        goto end;
    }
    if (g_d_GameSettings._10 != 1) {
        goto end;
    }
    st = state[team];
    if (st != 9 && st != 10) {
        if (n == 0) {
            if (lbl_803C66B0[0x55] == 0 && lbl_803C66B0[0x56] == 0) {
                lbl_2_bss_F468[0x46] = 0;
                lbl_2_bss_F468[0x45] = 0;
                state[1] = 0;
                state[0] = 0;
                lbl_2_bss_F468[0x60] = 0;
                lbl_2_bss_F468[0x5F] = 0;
                fn_2_EC54(team);
            }
            return;
        }
        for (i = 0; i < 9; i++) {
            if ((s8)row[i + 0x14] == st) {
                slot = i;
            }
        }
        state[team] = st;
        if ((s8)row[slot + 2] == cap) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        state[team + 2] = state[team];
        if (--state[team] < 0) {
            state[team] = 8;
        }
        if ((s8)row[state[team] + 2] == cap) {
            if (--state[team] < 0) {
                state[team] = 8;
            }
        }
        for (i = 0; i < 9; i++) {
            if ((s8)row[i + 0x14] == state[team + 2]) {
                slot = i;
            }
        }
        if ((s8)row[slot + 2] != -1) {
            fn_2_C698(slot, team);
            fn_800506E8(team, (s8)row[slot + 2], 0);
            fn_80067B40(team, row[slot + 2], 0);
            row[slot + 0x26] = 0;
            row[slot + 2] = -1;
            lbl_2_bss_F468[0x3D] = 0;
            lbl_8034E9A0[(s8)row[slot + 2] + 0x4757] = 0;
            row[slot + 0x4A] = 0;
            lbl_2_bss_F468[0x37 + team] = 0;
        }
        fn_800625A4(team, 0x10);
        goto end;
    }
    if (lbl_2_bss_100B8[0x2E + team] != 0) {
        lbl_2_bss_100B8[0x2E + team] = 0;
        fn_800625A4(team, 0x12);
        ((void (*)(u32))fn_2_1C34)(0x200);
        return;
    }
    if (n != 0) {
        state[team + 2] = state[team];
        state[team] = 8;
        if (cap == (s8)row[8 + 2]) {
            state[team]--;
        }
        fn_800625A4(team, 0x15);
        ((void (*)(u32))fn_2_1C34)(0x200);
        return;
    }
    if (lbl_803C66B0[0x55] != 0 || lbl_803C66B0[0x56] != 0) {
        return;
    }
    fn_2_CE44_clear_ratings();
    lbl_2_bss_F468[0x46] = 0;
    lbl_2_bss_F468[0x45] = 0;
    state[1] = 0;
    state[0] = 0;
    lbl_2_bss_F468[0x60] = 0;
    lbl_2_bss_F468[0x5F] = 0;
    for (t = 0; t < 2; t++) {
        u8* r = lbl_803C6724 + t * 9;
        for (i = 1; i < 9; i++) {
            s8 id = r[i + 2];
            lbl_8034E9A0[id + 0x4757] = 0;
            fn_800506E8(*(s8*)(lbl_8034E9A0 + 0x46F8 + t), id, 0);
            fn_80067B40(t, r[i + 2], 0);
            r[i + 2] = -1;
            r[i + 0x4A] = 0;
            r[i + 0x26] = 0;
        }
        lbl_2_bss_F468[0x37 + t] = 0;
        if (state[t] == 9) {
            state[t] = 0;
            switch (t) {
            case 0:
                if ((s8)lbl_803C6724[2] == *(s32*)(lbl_8034E9A0 + 0x46E0)) {
                    state[0] = 1;
                }
                break;
            case 1:
                if ((s8)lbl_803C6724[0xB] == *(s32*)(lbl_8034E9A0 + 0x46E4)) {
                    state[1] = 0xB;
                }
                break;
            }
        }
        lbl_2_bss_F468[0x3D + t] = 0;
    }
    fn_2_EC54(team);
end:
    ((void (*)(u32))fn_2_1C34)(0x200);
}
#endif

// NONMATCHING 60%: plain C; the original inlines fn_2_35D0/fn_2_52CC/fn_2_A040/fn_2_C698,
// unrolls the slot searches and repeats the cursor-sound tail per branch.
#if NONMATCHING
#define FN_2_3624_FIND_SLOT(row, value, out)              \
    do {                                                  \
        s32 j_;                                           \
        for (j_ = 0; j_ < 9; j_++) {                      \
            if ((s8)(row)[j_ + 0x14] == (s8)(value)) {    \
                (out) = j_;                               \
                break;                                    \
            }                                             \
        }                                                 \
    } while (0)

// fn_2_3624, size:0x134C
void fn_2_3624(u8 port) {
    u8 team = lbl_803C66B0[0x59 + port];
    s32* state = (s32*)lbl_2_bss_F468;
    u8* row = lbl_803C6724 + team * 9;
    u8* f = lbl_2_bss_F468 + team;
    u16 btn[3];
    u16 repeat;
    u16 down;
    s32 slot = 0;
    s32 i;
    s32 g;
    s32 k;
    memset(btn, 0, 6);
    if (lbl_803C66B0[0x5D + team] != 0) {
        return;
    }
    btn[0] = *(u16*)(lbl_8034E9A0 + port * 6 + 0x472C);
    btn[1] = down = *(u16*)(lbl_8034E9A0 + port * 6 + 0x472E);
    btn[2] = repeat = *(u16*)(lbl_8034E9A0 + port * 6 + 0x4730);
    if (repeat & 8) {
        if (f[0x45] != 0) {
            return;
        }
        if (state[team] == 9) {
            state[team] = 2;
            fn_800625A4(team, 0xE);
        } else if (state[team] == 10) {
            if (f[0x37] != 0) {
                state[team] = 9;
                fn_800625A4(team, 0x18);
            } else {
                state[team] = 2;
                fn_800625A4(team, 0xE);
            }
        } else {
            state[team + 2] = state[team];
            switch (state[team]) {
            case 0: state[team] = 5; break;
            case 1: state[team] = 0; break;
            case 2: state[team] = 8; break;
            case 3: state[team] = 7; break;
            case 4: state[team] = 6; break;
            case 5: state[team] = 7; break;
            case 6: state[team] = 4; break;
            case 7: state[team] = 1; break;
            case 8:
                if (f[0x37] != 0 && f[0x5F] == 0) {
                    state[team] = 9;
                } else {
                    state[team] = 2;
                }
                break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (repeat & 4) {
        if (f[0x45] != 0) {
            return;
        }
        if (state[team] == 9) {
            state[team] = 8;
            fn_800625A4(team, 0xE);
        } else {
            state[team + 2] = state[team];
            switch (state[team]) {
            case 0: state[team] = 1; break;
            case 1: state[team] = 7; break;
            case 2:
                if (f[0x37] != 0 && f[0x5F] == 0) {
                    state[team] = 9;
                } else {
                    state[team] = 8;
                }
                break;
            case 3: state[team] = 0; break;
            case 4: state[team] = 6; break;
            case 5: state[team] = 0; break;
            case 6: state[team] = 4; break;
            case 7: state[team] = 5; break;
            case 8: state[team] = 2; break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (repeat & 1) {
        if (f[0x45] != 0) {
            if (f[0x47] == 1) {
                f[0x47] = 0;
                f[0x49] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            return;
        }
        if (state[team] == 9) {
            state[team] = 0;
            fn_800625A4(team, 0xE);
        } else {
            state[team + 2] = state[team];
            switch (state[team]) {
            case 0: state[team] = 4; break;
            case 1:
                if (f[0x37] != 0 && f[0x5F] == 0) {
                    state[team] = 9;
                    break;
                }
                return;
            case 2: state[team] = 3; break;
            case 3: state[team] = 5; break;
            case 4: state[team] = 2; break;
            case 5: state[team] = 4; break;
            case 6: state[team] = 8; break;
            case 7: state[team] = 6; break;
            case 8: state[team] = 7; break;
            case 10: state[team] = 1; break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (repeat & 2) {
        if (f[0x45] != 0) {
            if (f[0x47] == 0) {
                f[0x47] = 1;
                f[0x49] = 0;
                sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
            }
            return;
        }
        if (state[team] == 9) {
            state[team] = 0;
            fn_800625A4(team, 0xE);
        } else {
            state[team + 2] = state[team];
            switch (state[team]) {
            case 0:
                if (f[0x37] != 0 && f[0x5F] == 0) {
                    state[team] = 9;
                    fn_800625A4(team, 0x18);
                } else {
                    state[team] = 2;
                    fn_800625A4(team, 0xE);
                }
                break;
            case 1:
                if (f[0x37] != 0 && f[0x5F] == 0) {
                    state[team] = 9;
                    break;
                }
                return;
            case 2: state[team] = 4; break;
            case 3: state[team] = 2; break;
            case 4: state[team] = 5; break;
            case 5: state[team] = 3; break;
            case 6: state[team] = 7; break;
            case 7: state[team] = 8; break;
            case 8: state[team] = 6; break;
            }
            if (state[team + 2] != state[team]) {
                fn_800625A4(team, 0xE);
            }
        }
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
    } else if (down & 0x100) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (state[team] == 9) {
            f[0x59] = 0;
            f[0x61] = -1;
            f[0x65] = 1;
            if (g_d_GameSettings.GameModeSelected == 5) {
                for (i = 0; i < 9; i++) {
                    s16 id = (s8)lbl_803C6724[i + 2];
                    u8 pos = lbl_803C6724[i + 0x14];
                    *(s16*)(starMissionCompletionTracker + i * 6 + 0x40B8) = id;
                    starMissionCompletionTracker[i * 6 + 0x40BA] = i;
                    starMissionCompletionTracker[i * 6 + 0x40BB] = pos;
                    g_Roster[i].h24 = id;
                    lbl_80354720[i * 4 + 2] = pos;
                }
                lbl_2_bss_F468[0x2E] = 0;
                lbl_2_bss_100B4 = 1;
                *(s16*)(lbl_803CBBCC[0] + 4) = 8;
            } else if (g_d_GameSettings._10 == 0) {
                if (team != 0) {
                    lbl_2_bss_F468[0x36] = 0x1E;
                    *(s16*)(lbl_803CBBCC[0] + 4) = 3;
                } else {
                    fn_2_52CC();
                }
            } else {
                lbl_2_bss_100B8[0x2E + team] = 1;
                if (lbl_2_bss_100B8[0x2E] != 0 && lbl_2_bss_100B8[0x2F] != 0) {
                    lbl_2_bss_F468[0x4F] = 1;
                    lbl_2_bss_F468[0x36] = 0x1E;
                    *(s16*)(lbl_803CBBCC[0] + 4) = 7;
                }
            }
            fn_800625A4(team, 0x1B);
        } else if (f[0x5F] == 0) {
            f[0x61] = state[team];
            fn_800625A4(team, 0x1C);
        } else {
            s32 j1 = 0;
            s32 j2 = 0;
            s8 v1 = 0;
            s32 v2 = 0;
            for (i = 0; i < 9; i++) {
                if ((s8)row[i + 0x14] == (s8)f[0x61]) {
                    j1 = i;
                    v1 = f[0x61];
                }
                if ((s8)row[i + 0x14] == state[team]) {
                    j2 = i;
                    v2 = state[team];
                }
            }
            row[j1 + 0x14] = v2;
            row[j2 + 0x14] = v1;
            fn_800625A4(team, 0x1C);
        }
        sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
    } else if (down & 0x200) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (f[0x5F] != 0) {
            fn_800625A4(team, 0x1D);
        }
        sndFXStartEx(0x1B9, lbl_800EFBA4[2], 0x3F, 0);
    } else if (down & 0x20) {
        if (fn_2_35D0(team)) {
            return;
        }
        if (f[0x5F] != 0) {
            f[0x5F] = 0;
        }
        fn_800625A4(team, 0x1B);
        sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        f[0x59] = 0;
    } else if (down & 0x40) {
        s8 v;
        if (fn_2_35D0(team) || g_d_GameSettings.GameModeSelected == 5) {
            return;
        }
        FN_2_3624_FIND_SLOT(row, state[team], slot);
        v = row[slot + 2];
        if (v == -1 || v == 0x36) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        if (state[team] == 9) {
            sndFXStartEx(0x1BA, lbl_800EFBA4[3], 0x3F, 0);
            return;
        }
        f[0x50] = 0;
        for (g = 0; g < 9; g++) {
            for (k = 0; k < 5; k++) {
                if (v == *(s16*)(lbl_80108EDC + g * 10 + k * 2)) {
                    f[0x50] = 1;
                    goto found;
                }
            }
        }
    found:
        if (f[0x50] != 0) {
            fn_2_A040(g, k, team, slot);
            fn_2_C698(slot, team);
            sndFXStartEx(0x1B7, lbl_800EFBA4[0], 0x3F, 0);
        }
    } else if (down & 0x10) {
        if (fn_2_35D0(team)) {
            return;
        }
        FN_2_3624_FIND_SLOT(row, state[team], slot);
        if (state[team] != 9) {
            s8 v = row[slot + 2];
            if (v != -1 && v != 0x36 && f[0x41] == 0) {
                f[0x45] = 1;
                f[0x4B] = 1;
                f[0x47] = 0;
                sndFXStartEx(0x1BF, lbl_800EFBA4[8], 0x3F, 0);
            }
        }
    }
}
#endif
