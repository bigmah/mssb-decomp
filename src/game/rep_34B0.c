#include "game/rep_34B0.h"
#include "header_rep_data.h"

#include "musyx/musyx.h"
extern u8 lbl_800EFBA4[];

extern void setInMemBatterConstants(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_8913C(void);
extern void fn_3_58870(void);
extern void fn_3_BF1AC(void);
extern void fn_3_BF158(void);
extern void* memset(void*, s32, u32);
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];

extern void fn_3_5A6D4(s32);
extern f32 lbl_3_data_21770[];
extern f32 lbl_3_data_216BC[];
extern int random_fn_3_9EE24(int max);
extern f32 lbl_3_rodata_351C[];
extern f32 lbl_3_rodata_3518;
extern void fn_8004C108(f32*, s32);
extern void fn_3_90064(s32);
extern u8 lbl_3_data_18C48[];
extern u8 lbl_8037169C[];
extern void changeScene(s32, s32);
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern u8 lbl_3_data_21798[];
extern u8 lbl_803CBC3C[];
extern u8 lbl_3_common_bss_32234[];
extern u8 lbl_3_common_bss_32724[];
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern void fn_3_6EBB4(s32);
extern void setBatterContactConstants(void);
extern s32 someAnimationIndFunction(void);
extern u8 g_Minigame[];
extern u8 g_Scores[];
extern void fn_3_10F550(s32, s32);
extern void fn_3_10AD48(void);
extern void fn_3_6C854(int, int);
extern u8 g_Pitcher[];
extern s16 lbl_3_data_217A4;
extern s16 lbl_3_data_21788[];

// .text:0x0012E8FC size:0x214 mapped:0x8076D990
void fn_3_12E8FC(void) {
    s32 i;
    s32 have = 0;
    s32 pick;
    u8* p;
    f32* t;

    if (g_Minigame[0x1ADA] >= lbl_3_data_21788[2]) {
        for (i = 0, pick = 0; i < 15; i++) {
            if (g_Minigame[i * 0x34 + 0x890] == 0) {
                pick++;
            }
        }
        pick = random_fn_3_9EE24(pick);
        g_Minigame[0x1ADA] = 0;
        have = 1;
    }
    for (i = 0; i < 15; i++) {
        p = g_Minigame + i * 0x34;
        t = lbl_3_data_216BC + i * 3;
        if (p[0x890] == 0) {
            p[0x890] = 1;
            *(s16*)(p + 0x88C) = 0;
            *(f32*)(p + 0x860) = t[0];
            *(f32*)(p + 0x864) = t[1];
            *(f32*)(p + 0x868) = t[2];
            *(f32*)(p + 0x864) = *(f32*)(p + 0x864) + lbl_3_data_21770[0];
            *(f32*)(p + 0x864) = *(f32*)(p + 0x864) + ((f64)((i % 3) * 10) - (f64)(random_fn_3_9EE24(0x65) * 5) / 100.0);
            p[0x891] = random_fn_3_9EE24(3);
            if (have != 0) {
                if (pick == 0) {
                    pick = -1;
                    p[0x891] = 3;
                    *(s16*)(g_Minigame + 0x18A4) = i;
                } else if (pick > 0) {
                    pick--;
                }
            }
        }
    }
}

// .text:0x0012EB10 size:0x270 mapped:0x8076DBA4
void fn_3_12EB10(void) {
    return;
}

// .text:0x0012ED80 size:0xE8 mapped:0x8076DE14
s32 fn_3_12ED80(void) {
    s32 i;
    u8* p = g_Minigame + 0x34;
    for (i = 0; i < 5; i++) {
        if (p[0x892] != 0) {
            return 0;
        }
        if (p[0x8C6] != 0) {
            return 0;
        }
        p += 0x9C;
    }
    return 1;
}

// .text:0x0012EE68 size:0x13C mapped:0x8076DEFC
void fn_3_12EE68(s32 i) {
    u8* a;
    u8* b;
    s32 off;
    u8 k;

    off = i * 0x34;
    a = g_Minigame + off + 0x860;
    if (i % 3 == 2) {
        return;
    }
    b = g_Minigame + (i + 1) * 0x34 + 0x860;
    if (b[0x30] == 4) {
        return;
    }
    if (b[0x30] == 3 && *(f32*)(b + 4) - *(f32*)(a + 4) > 0.3 + lbl_3_data_21770[3]) {
        return;
    }
    b[0x32] = 1;
    *(f32*)(b + 0x24) = lbl_3_data_21770[4];
    if ((i + 1) % 3 == 1) {
        *(f32*)(b + 0x28) = lbl_3_data_216BC[i * 3 + 1];
    } else {
        k = 0;
        k |= (g_Minigame[off + 0x85C] == 2);
        k |= (g_Minigame[off + 0x890] == 2);
        *(f32*)(b + 0x28) = lbl_3_data_216BC[k * 3 + 1];
    }
}

// .text:0x0012EFA4 size:0x2E8 mapped:0x8076E038
void fn_3_12EFA4(void) {
    return;
}

// .text:0x0012F28C size:0x198 mapped:0x8076E320
void fn_3_12F28C(s32 i) {
    u8* p;

    p = g_Minigame + i * 0x34 + 0x860;
    if (*(s16*)(p + 0x2C) >= *(s16*)(p + 0x2E)) {
        p[0x30] = 4;
        *(s16*)(p + 0x2C) = 0;
        fn_3_12EE68(i);
        fn_3_6C854(*(s8*)(g_Minigame + *(s8*)(g_Minigame + 0x1905) + 0x18CC), 0);
    }
}

// .text:0x0012F424 size:0x200 mapped:0x8076E4B8
void fn_3_12F424(void) {
    return;
}

// .text:0x0012F624 size:0x3B0 mapped:0x8076E6B8
void fn_3_12F624(void) {
    return;
}

// .text:0x0012F9D4 size:0xF0 mapped:0x8076EA68
void fn_3_12F9D4(s32 idx) {
    f32 v[3];
    f32* a = (f32*)(g_Minigame + idx * 0x34 + 0x860);
    a[1] += lbl_3_data_21770[1];
    if (a[1] < a[4]) {
        a[1] = a[4];
        if (a[7] != a[4]) {
            f32 z = a[2];
            f32 y = a[1];
            f32 x = a[0];
            v[1] = y;
            v[2] = z;
            v[0] = x;
            v[1] = -v[1];
            v[2] = v[2] - lbl_3_rodata_351C[0];
            if (y <= lbl_3_rodata_3518) {
                fn_8004C108(v, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(v, 0);
                fn_3_90064(0x2E5);
            }
        }
        *((u8*)a + 0x30) = 2;
    }
}

// .text:0x0012FAC4 size:0x2A8 mapped:0x8076EB58
void fn_3_12FAC4(void) {
    return;
}

// .text:0x0012FD6C size:0x118 mapped:0x8076EE00
void fn_3_12FD6C(void) {
    s32 i;
    u8* p;
    for (i = 0; i < 15; i++) {
        p = g_Minigame + i * 0x34;
        if (p[0x890] != 0) {
            *(f32*)(p + 0x878) = *(f32*)(p + 0x860);
            *(f32*)(p + 0x87C) = *(f32*)(p + 0x864);
            *(f32*)(p + 0x880) = *(f32*)(p + 0x868);
            p[0x890] = 1;
        }
        *(s16*)(p + 0x88C) = 0;
    }
}

// .text:0x0012FE84 size:0x150 mapped:0x8076EF18
void fn_3_12FE84(void) {
    f32 z, y, x;
    u8* q;
    f32* t;
    s32 i;
    for (i = 0; i < 15; i++) {
        q = g_Minigame + i * 0x34;
        t = lbl_3_data_216BC + i * 3;
        q[0x890] = 1;
        *(s16*)(q + 0x88C) = 0;
        q[0x892] = 0;
        x = t[0];
        y = t[1];
        z = t[2];
        *(f32*)(q + 0x86C) = x;
        *(f32*)(q + 0x870) = y;
        *(f32*)(q + 0x874) = z;
        *(f32*)(q + 0x860) = x;
        *(f32*)(q + 0x864) = y;
        *(f32*)(q + 0x868) = z;
        *(f32*)(q + 0x864) = *(f32*)(q + 0x864) + lbl_3_data_21770[0];
        *(f32*)(q + 0x864) = *(f32*)(q + 0x864) + ((f64)((i % 3) * 10) - (f64)(random_fn_3_9EE24(0x65) * 5) / 100.0);
        q[0x891] = random_fn_3_9EE24(3);
    }
}

// .text:0x0012FFD4 size:0x2B4 mapped:0x8076F068
void fn_3_12FFD4(void) {
    return;
}

// .text:0x00130288 size:0x548 mapped:0x8076F31C
void fn_3_130288(void) {
    return;
}

// .text:0x001307D0 size:0x2B0 mapped:0x8076F864
void fn_3_1307D0(void) {
    return;
}

// .text:0x00130A80 size:0x4C mapped:0x8076FB14
extern u8 g_Minigame[];
extern u8 g_GameLogic[];

void fn_3_130A80(void) {
    *(s16*)(g_Minigame + 0x18A4) = -1;
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    fn_3_5A6D4(8);
}

// .text:0x00130ACC size:0x1A0 mapped:0x8076FB60
void fn_3_130ACC(void) {
    if (g_Minigame[0x190B] == 0) {
        if (g_Pitcher[0x13E] == 4) {
            if (g_Minigame[0x1A2E] == 0) {
                g_Minigame[0x190B] = 1;
                g_Minigame[0x1912] = 2;
            }
            *(s16*)(g_Minigame + 0x18A2) = 0;
            *(s16*)(g_Minigame + 0x18A4) = -1;
        }
        return;
    }
    if (g_Minigame[0x190B] == 1) {
        g_Minigame[0x190B] = 2;
        *(s16*)(g_GameLogic + 0x100) = lbl_3_data_217A4;
    }
    *(s16*)(g_GameLogic + 0x100) -= 1;
    if (g_Minigame[0x1912] != 0) {
        if (*(s16*)(g_GameLogic + 0x100) <= 0) {
            *(s16*)(g_Minigame + 0x18A4) = -1;
            g_GameLogic[0x12B] = 1;
            g_GameLogic[0x12C] = 1;
            g_GameLogic[0x12E] = 1;
            fn_3_5A6D4(8);
        }
    } else if (*(s16*)(g_GameLogic + 0x100) <= 0) {
        fn_3_5A6D4(0);
    }
    if (g_Minigame[0x1912] != 0
        && (g_Minigame[0x1909] == 0
            || (g_Minigame[0x1909] != 0 && g_Minigame[0x190C] + 1 >= g_Minigame[0x1906] && *(s32*)g_Scores >= g_Scores[0xAA]))
        && g_Minigame[0x1A37] == 0 && *(s16*)(g_GameLogic + 0x100) == 1) {
        sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
    }
}

// .text:0x00130C6C size:0x4A8 mapped:0x8076FD00
void fn_3_130C6C(void) {
    return;
}

// .text:0x00131114 size:0x88 mapped:0x807701A8
void fn_3_131114(void) {
    setInMemBatterConstants(*(s8*)(g_Minigame + 0x1905));
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_8913C();
    fn_3_58870();
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    fn_3_BF1AC();
    fn_3_BF158();
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
}

// .text:0x0013119C size:0xF0 mapped:0x80770230
void fn_3_13119C(void) {
    u8* gl = g_GameLogic;
    switch (gl[0x125]) {
    case 0:
        changeScene(1, 6);
        gl[0x125] = 1;
        break;
    case 1: {
        s32 t = *(u16*)(gl + 0xFC);
        if (t >= *(s16*)(lbl_3_data_18C48 + 4) ||
            (t >= *(s16*)(lbl_3_data_18C48 + 2) && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            gl[0x125] = 2;
        }
        break;
    }
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            gl[0x125] = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// .text:0x0013128C size:0x48 mapped:0x80770320
extern u8 g_Scores[];

void fn_3_13128C(void) {
    if (*(s32*)g_Scores >= g_Scores[0xAA]) {
        fn_3_5A6D4(0xF);
    } else {
        fn_3_5A6D4(6);
    }
}

// .text:0x001312D4 size:0x26C mapped:0x80770368
void fn_3_1312D4(void) {
    return;
}

// .text:0x00131540 size:0x748 mapped:0x807705D4
void fn_3_131540(void) {
    return;
}

// .text:0x00131C88 size:0x23C mapped:0x80770D1C
void fn_3_131C88(void) {
    return;
}

// .text:0x00131EC4 size:0x138 mapped:0x80770F58
void fn_3_131EC4(void) {
    u8* gl = g_GameLogic;
    u8* mg;
    switch (gl[0x125]) {
    case 0:
        mg = g_Minigame;
        mg[0x1905] = mg[0x18E0 + mg[0x190C]];
        gl[0x12B] = 1;
        mg[0x1A2D] = 0;
        mg[0x1912] = 0;
        if (mg[0x1909] == 0) {
            mg[0x1A2E] = lbl_3_data_21798[mg[0x1A2B]];
        } else {
            mg[0x1A2E] = lbl_3_data_21798[4];
        }
        fn_3_F578();
        fn_3_753E8(0);
        fn_3_6EBB4(-1);
        setBatterContactConstants();
        setInMemBatterConstants(*(s8*)(mg + 0x1905));
        lbl_803CBC3C[2] = 0;
        gl[0x125] += 1;
        break;
    case 1:
        if (someAnimationIndFunction() != 0) {
            lbl_3_common_bss_32234[1] = 1;
            gl[0x125] += 1;
        }
        break;
    default:
        lbl_3_common_bss_32724[0xB6] = 1;
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00131FFC size:0x80 mapped:0x80771090
void fn_3_131FFC(void) {
    *(s32*)g_Scores += 1;
    g_Minigame[0x190C] = 0;
    if (g_Minigame[0x1909] == 0) {
        fn_3_5A6D4(7);
        return;
    }
    fn_3_10F550(4, 0);
    if (*(s32*)g_Scores == 1) {
        fn_3_10AD48();
    }
    fn_3_5A6D4(7);
}

// .text:0x0013207C size:0x40 mapped:0x80771110
void fn_3_13207C(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_5A6D4(6);
}

// .text:0x001320BC size:0x310 mapped:0x80771150
void fn_3_1320BC(void) {
    return;
}

static inline void mgStep_1323CC(s32 idx) {
    f32 v[3];
    f32* a = (f32*)(g_Minigame + idx * 0x34 + 0x860);
    a[1] += lbl_3_data_21770[1];
    if (a[1] < a[4]) {
        a[1] = a[4];
        if (a[7] != a[4]) {
            f32 x = a[0];
            f32 y = a[1];
            f32 z = a[2];
            v[1] = y;
            v[0] = x;
            v[2] = z;
            v[1] = -v[1];
            v[2] = v[2] - lbl_3_rodata_351C[0];
            if (y <= lbl_3_rodata_3518) {
                fn_8004C108(v, 1);
                fn_3_90064(0x2E4);
            } else {
                fn_8004C108(v, 0);
                fn_3_90064(0x2E5);
            }
        }
        *((u8*)a + 0x30) = 2;
    }
}

// .text:0x001323CC size:0x11C mapped:0x80771460
void fn_3_1323CC(void) {
    u32 i;
    for (i = 0; i < 15; i++) {
        if (g_Minigame[i * 0x34 + 0x890] == 1) {
            mgStep_1323CC(i);
        }
    }
}

// .text:0x001324E8 size:0x9F4 mapped:0x8077157C
void fn_3_1324E8(void) {
    return;
}

