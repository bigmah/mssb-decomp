#include "menus/auto_00_00001254_text.h"
#include "static/UnknownHomes_Static.h"
#include <string.h>

extern void fn_800625A4(u8, s32);

extern u8 lbl_803297E0[];
extern void fn_2_2FC0(u8, s32, s32);

extern void fn_2_7DDC(void);
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
extern void fn_80050138(s32, s32, s32, s32, s32, s32);
extern u8 lbl_80353B98[];
extern u8 lbl_80354720[];
extern void fn_800506E8(s32, s32, s32);
extern void fn_80067B40(s32, u8, s32);
extern u8 lbl_80108EDC[];
extern u8 inMemRoster[];
extern u8 lbl_800EFBA4[];
extern int sndFXStartEx(int, int, int, int);
extern void fn_8004EEF4(s32, s32, s32, s32, s32);
extern u8 lbl_803C6724[];
extern u8 starMissionCompletionTracker[];
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

// fn_2_3204, size:0x38
void fn_2_3204(void) {
    fn_2_2FC0(lbl_803297E0[0xCF5F], 1, 1);
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
