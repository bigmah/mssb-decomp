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
extern void fn_2_3624(s32);
extern void fn_2_104FC(s32);
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
extern void fn_80067B40(s32, u8, s32);
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
