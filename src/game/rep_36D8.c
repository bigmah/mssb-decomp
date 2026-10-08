#include "game/rep_36D8.h"
#include "header_rep_data.h"

#pragma dont_inline on

extern u8 g_Minigame[];
extern u8 lbl_3_data_21804[];
extern void fn_3_157DB8(s16);
extern u8 lbl_3_data_218BC[];
extern void fn_3_14C904(u8*, s32);
extern void fn_3_90064(s32);
extern u8 lbl_3_data_2188C[];
extern s16 lbl_3_data_218A8;
extern f64 lbl_3_rodata_3760;
extern f32 lbl_3_rodata_3734;
extern void fn_8004C094(void*);
extern void fn_3_6C854(int, int);
extern void fn_3_DE4FC(void);
extern f32 lbl_3_data_217F8[];
extern f32 lbl_3_rodata_3768;
extern u8 lbl_3_data_21944[];
extern u8 lbl_3_data_2194C[];
extern u8 lbl_3_data_2197C[];
extern u8 lbl_3_data_21980[];
extern int RandomInt_Game_Range(int, int);
extern int RandomInt_Game(int);
extern void* memset(void*, int, u32);
extern u8 lbl_800EFBA4[];
extern s16 lbl_3_data_21904;
extern void fn_3_151798(void);
extern void fn_3_11F480(void);
extern void fn_80011578(void);
extern void fn_3_1578F8(void);
extern u32 sndFXStartEx(s32, u8, u8, u8);
extern u8 g_Runners[];
extern u8 g_GameLogic[];
extern u8 lbl_3_data_21278[];
extern void changeScene(s32, s32);
extern void fn_3_7DD6C(void);
extern void fn_3_10F550(s32, s32);
extern void fn_3_5A6D4(s32);
extern u8 lbl_3_data_218BC[];
extern s32 lbl_3_bss_B798[];
extern f32 lbl_3_bss_B794;
#include "static/UnknownHomes_Static.h"

// .text:0x0013C7BC size:0xDBC mapped:0x8077B850
void fn_3_13C7BC(void) {
    return;
}

// .text:0x0013D578 size:0x70 mapped:0x8077C60C
u32 fn_3_13D578(s8 a) {
 u8* m = g_Minigame; s16* sp=(s16*)g_Minigame; s16* tp=(s16*)(g_Minigame+0x1890+a*2); s8 i=0;
 do {
     s8 t = *(s8*)(m + 0x18CC);
        if (t >= 0 && t < 4 && *(s16*)((u8*)sp + 0x1890) > *tp) { return 1; }
        i++; m += 1; sp += 1;
    } while (i < 4);
    return 0;
}

// .text:0x0013D5E8 size:0x30 mapped:0x8077C67C
s32 fn_3_13D5E8(f32* a, f32* b) {
    f32 c = 100.0f;
    f32 y = *b;
    f32 x = *a;
    return (s32)(c * x - c * y);
}

// .text:0x0013D618 size:0x408 mapped:0x8077C6AC
void fn_3_13D618(void) {
    return;
}

// .text:0x0013DA20 size:0x30 mapped:0x8077CAB4
s32 fn_3_13DA20(f32* a, f32* b) {
    f32 c = 100.0f;
    f32 y = *b;
    f32 x = *a;
    return (s32)(c * x - c * y);
}

// .text:0x0013DA50 size:0x1F8 mapped:0x8077CAE4
void fn_3_13DA50(void) {
    return;
}

// .text:0x0013DC48 size:0x198 mapped:0x8077CCDC
void fn_3_13DC48(s8 idx, f32 ang, f32* out1, f32* out2) {
    u8* r = g_Runners + idx * 0x154;
    f32 a = *(f32*)(r + 0x64);
    f32 b = ang;
    if (a < 0.0f) {
        a += 4.0f;
    } else if (a >= 4.0f) {
        a -= 4.0f;
    }
    if (ang < 0.0f) {
        b += 4.0f;
    } else if (ang >= 4.0f) {
        b -= 4.0f;
    }
    if (a > b) {
        *out1 = (4.0f + b) - a;
    } else {
        *out1 = b - a;
    }
    if (r[0x137] == 3) {
        *out1 = *out1 + 0.15f;
    }
    a = *(f32*)(r + 0x64);
    if (a < 0.0f) {
        a += 4.0f;
    } else if (a >= 4.0f) {
        a -= 4.0f;
    }
    if (ang < 0.0f) {
        ang += 4.0f;
    } else if (ang >= 4.0f) {
        ang -= 4.0f;
    }
    if (a < ang) {
        *out2 = (4.0f + a) - ang;
    } else {
        *out2 = a - ang;
    }
    if (r[0x137] == 1) {
        *out2 = *out2 + 0.15f;
    }
}// .text:0x0013DDE0 size:0xC4 mapped:0x8077CE74
f32 fn_3_13DDE0(f32 a, f32 b, u8 mode) {
    if (a < 0.0f) {
        a += 4.0f;
    } else if (a >= 4.0f) {
        a -= 4.0f;
    }
    if (b < 0.0f) {
        b += 4.0f;
    } else if (b >= 4.0f) {
        b -= 4.0f;
    }
    if (mode == 1) {
        if (a > b) {
            return (4.0f + b) - a;
        }
        return b - a;
    }
    if (a < b) {
        return (4.0f + a) - b;
    }
    return a - b;
}// .text:0x0013DFBC size:0x1B8 mapped:0x8077D050
void fn_3_13DFBC(void) {
    return;
}

// .text:0x0013E174 size:0xA8 mapped:0x8077D208
void fn_3_13E174(u8 a) {
    switch (a) {
    case 0:
        lbl_3_bss_B798[0] = (s32)((f32*)lbl_3_data_218BC)[12];
        lbl_3_bss_B794 = ((f32*)lbl_3_data_218BC)[14];
        break;
    case 1:
        lbl_3_bss_B798[0] = (s32)((f32*)lbl_3_data_218BC)[13];
        lbl_3_bss_B794 = ((f32*)lbl_3_data_218BC)[15];
        break;
    default:
        return;
    }
    fn_800528AC((fn_800528AC_parameter)fn_3_13DFBC);
}
// .text:0x0013E21C size:0x188 mapped:0x8077D2B0
void fn_3_13E21C(u8* a) {
    return;
}

// .text:0x0013E3A4 size:0x2CC mapped:0x8077D438
void fn_3_13E3A4(u8* a) {
    return;
}

// .text:0x0013E670 size:0x64 mapped:0x8077D704
void fn_3_13E670(void) {
    u8* m = g_Minigame;
    if (m[0x190B] != 0) {
        *(s8*)(m + 0x1D74) = -1;
        m[0xCCE] = 0;
    } else if (m[0xCCE] != 0) {
        fn_3_13E21C(m + 0xCB0);
    } else {
        fn_3_13E3A4(m + 0xCB0);
    }
}

// .text:0x0013E6D4 size:0x100 mapped:0x8077D768
void fn_3_13E6D4(void) {
    s16 t;
    u32 i;
    for (i = 15; i < 0x23; i++) {
        if (g_Minigame + 0x193A != NULL) {
            PSVECAdd((Vec*)(g_Minigame + 0xCD0 + i * 12), (Vec*)(g_Minigame + 0x1180 + i * 12), (Vec*)(g_Minigame + 0xCD0 + i * 12));
            *(f32*)(g_Minigame + 0x1184 + i * 12) = *(f32*)(g_Minigame + 0x1184 + i * 12) + ((f32*)lbl_3_data_2188C)[4];
            if (*(f32*)(g_Minigame + 0xCD4 + i * 12) < lbl_3_rodata_3760) {
                *(f32*)(g_Minigame + 0xCD4 + i * 12) = lbl_3_rodata_3768;
                *(f32*)(g_Minigame + 0x1180 + i * 12) = *(f32*)(g_Minigame + 0x1180 + i * 12) * ((f32*)lbl_3_data_2188C)[5];
                *(f32*)(g_Minigame + 0x1188 + i * 12) = *(f32*)(g_Minigame + 0x1188 + i * 12) * ((f32*)lbl_3_data_2188C)[5];
                *(f32*)(g_Minigame + 0x1184 + i * 12) = *(f32*)(g_Minigame + 0x1184 + i * 12) * -((f32*)lbl_3_data_2188C)[6];
            }
            t = *(s16*)(g_Minigame + 0x17C8 + i * 2) + 1;
            *(s16*)(g_Minigame + 0x17C8 + i * 2) = t;
            if (t >= lbl_3_data_218A8) {
                g_Minigame[0x193A + i] = 0;
            }
        }
    }
}

// .text:0x0013EA30 size:0x214 mapped:0x8077DAC4
void fn_3_13EA30(void) {
    return;
}

// .text:0x0013EC44 size:0x840 mapped:0x8077DCD8
void fn_3_13EC44(void) {
    return;
}

// .text:0x0013F484 size:0x244 mapped:0x8077E518
void fn_3_13F484(void) {
    return;
}

// .text:0x0013F6C8 size:0x11C mapped:0x8077E75C
void fn_3_13F6C8(void) {
    u8* d;
    u32 i;
    u8* a;
    u8* b;
    u8* c;
    u8* fl;
    s16 t;
    if (g_Minigame[0x190B] == 0) {
        fn_3_13F484();
        fn_3_13EA30();
        d = lbl_3_data_2188C;
        a = g_Minigame + 0xB4;
        b = g_Minigame + 0x1E;
        c = g_Minigame + 0xF;
        fl = g_Minigame + 0x193A;
        for (i = 15; i < 0x23; i++, a += 0xC, b += 2, c += 1) {
            if (fl != NULL) {
                PSVECAdd((Vec*)(a + 0xCD0), (Vec*)(a + 0x1180), (Vec*)(a + 0xCD0));
                *(f32*)(a + 0x1184) = *(f32*)(a + 0x1184) + ((f32*)d)[4];
                if (*(f32*)(a + 0xCD4) < lbl_3_rodata_3760) {
                    *(f32*)(a + 0xCD4) = lbl_3_rodata_3768;
                    *(f32*)(a + 0x1180) = *(f32*)(a + 0x1180) * ((f32*)d)[5];
                    *(f32*)(a + 0x1188) = *(f32*)(a + 0x1188) * ((f32*)d)[5];
                    *(f32*)(a + 0x1184) = *(f32*)(a + 0x1184) * -((f32*)d)[6];
                }
                t = *(s16*)(b + 0x17C8) + 1;
                *(s16*)(b + 0x17C8) = t;
                if (t >= lbl_3_data_218A8) {
                    c[0x193A] = 0;
                }
            }
        }
    }
}
// .text:0x0013F7E4 size:0xE0 mapped:0x8077E878
void fn_3_13F7E4(void) {
    u8* m = g_Minigame;
    u8* p;
    s16* q;
    s32 i;
    if (m[0x1B19] != 1) {
        return;
    }
    if (*(s16*)(m + 0x1AFA) <= 0) {
        *(s16*)(m + 0x1AFE) = 0;
        *(s16*)(m + 0x1B00) = 0;
        *(s16*)(m + 0x1B02) = 0;
        *(s16*)(m + 0x1B04) = 0;
    }
    for (p = g_Minigame, q = (s16*)g_Minigame, i = 0; i < 4; p++, q++, i++) {
        s8 r = *(s8*)(p + 0x1900);
        if (r >= 0) {
            u8 st = g_Runners[r * 0x154 + 0x137];
            if (st == 1 || st == 3) {
                *(s16*)((u8*)q + 0x1AFE) += 1;
            }
        }
    }
}
// .text:0x0013F8C4 size:0x360 mapped:0x8077E958
void fn_3_13F8C4(void) {
    return;
}

// .text:0x0013FC24 size:0x660 mapped:0x8077ECB8
void fn_3_13FC24(void) {
    return;
}

// .text:0x00140284 size:0x200 mapped:0x8077F318
void fn_3_140284(void) {
    return;
}

// .text:0x00140484 size:0x154 mapped:0x8077F518
void fn_3_140484(void) {
    u8* m = g_Minigame;
    f32 a;
    f32 b;
    f32 c;
    s32 i;
    if (m[0x190B] == 0) {
        *(f32*)(m + 0x1AE4) += *(f32*)(m + 0x1AF0);
        a = *(f32*)(m + 0x1AE4);
        b = *(f32*)(m + 0x1AF0);
        if (a <= 0.0f && b < -((f32*)lbl_3_data_218BC)[6]) {
            *(f32*)(m + 0x1AF0) = 0.0f;
            *(f32*)(m + 0x1AE4) = 0.0f;
            fn_8004C094(m + 0x1AE0);
            fn_3_90064(0x2DF);
            lbl_3_bss_B798[0] = (s32)((f32*)lbl_3_data_218BC)[12];
            lbl_3_bss_B794 = ((f32*)lbl_3_data_218BC)[14];
            fn_800528AC((fn_800528AC_parameter)fn_3_13DFBC);
            i = 0;
            do {
                fn_3_6C854(i, 1);
                i++;
            } while (i < 4);
        } else if (a > 0.0f) {
            *(f32*)(m + 0x1AF0) -= ((f32*)lbl_3_data_218BC)[6];
        }
        if (*(s16*)(g_Minigame + 0x1AFA) >= *(s16*)((u8*)&lbl_3_data_21904 + 0x12)) {
            g_Minigame[0x1B19] = 2;
            *(s16*)(g_Minigame + 0x1AFA) = 0;
            *(f32*)(m + 0x1AF0) = ((f32*)lbl_3_data_218BC)[4];
        }
    }
}

// .text:0x001405D8 size:0x11C mapped:0x8077F66C
void fn_3_1405D8(void) {
    s16* tbl;
    u8 sel;
    s16 i;
    s16 rnd;
    u8* m = g_Minigame;
    s16 v = *(s16*)(m + 0x1AFA);
    s16 t;
    if (v <= 1) {
        if (m[0x1909] != 0) {
            sel = 4;
        } else {
            sel = m[0x1A2B];
        }
        rnd = RandomInt_Game_Range(0, 1000);
        *(s16*)(g_Minigame + 0x1B06) = 0;
        tbl = (s16*)(lbl_3_data_21804 + sel * 0x12);
        do {
            i = *(s16*)(g_Minigame + 0x1B06);
            rnd -= tbl[i];
            *(s16*)(g_Minigame + 0x1B06) = ++i;
        } while (rnd > 0 && tbl[i] >= 0);
        t = *(s16*)(g_Minigame + 0x1B06) * 0x78;
        *(s16*)(g_Minigame + 0x1B06) = t;
        t = t - 0x30;
        *(s16*)(g_Minigame + 0x1B06) = t;
        fn_3_157DB8(t);
    } else {
        *(s16*)(m + 0x1AF8) = 0xE00;
        if (v >= *(s16*)(m + 0x1B06)) {
            m[0x1B19] = 1;
            *(s16*)(m + 0x1AFA) = 0;
            *(f32*)(m + 0x1AF0) = ((f32*)lbl_3_data_218BC)[3];
            ((void (*)(u8*))fn_3_14C904)(lbl_3_data_218BC);
            fn_3_90064(0x2E0);
        }
    }
}

// .text:0x001409AC size:0x220 mapped:0x8077FA40
void fn_3_1409AC(void) {
    u8* m;
    u32 i;
    fn_3_DE4FC();
    m = g_Minigame;
    if (m[0x1A2B] <= 2 && m[0x1909] == 0) {
        if (m[0x18E8 + (s8)m[0x1908]] == 1 && m[0x19A8] == 0) {
            m[0x1A37] = 1;
        } else {
            g_Minigame[0x1A37] = 2;
        }
    }
    fn_3_5A6D4(0xE);
    m = g_Minigame;
    *(s16*)(m + 0x1AF8) = 0;
    m[0x1B19] = 0;
    *(f32*)(m + 0x1AE0) = lbl_3_data_217F8[0];
    *(f32*)(m + 0x1AE4) = lbl_3_data_217F8[1];
    *(f32*)(m + 0x1AE8) = lbl_3_data_217F8[2];
    *(f32*)(m + 0x1AEC) = 0.0f;
    *(f32*)(m + 0x1AF0) = 0.0f;
    *(f32*)(m + 0x1AF4) = 0.0f;
    *(s16*)(m + 0x1AFA) = 0;
    *(s16*)(m + 0x1AF8) = 0xE00;
    for (i = 0; i < 100; i++) {
        g_Minigame[0x193A + i] = 0;
        *(s16*)(g_Minigame + 0x17C8 + i * 2) = 0;
    }
    m = g_Minigame;
    m[0x1B1A] = 0;
    *(s16*)(m + 0x1B08) = 0;
    m[0x1B1B] = 0;
    *(s16*)(m + 0x1B0A) = 0;
    m[0x1B1C] = 0;
    *(s16*)(m + 0x1B0C) = 0;
    m[0x1B1D] = 0;
    *(s16*)(m + 0x1B0E) = 0;
    m[0x1B1E] = 0;
    *(s16*)(m + 0x1B10) = 0;
    m[0x1B1F] = 0;
    *(s16*)(m + 0x1B12) = 0;
    *(s8*)(m + 0x1B26) = -1;
    *(s8*)(m + 0x1B27) = -1;
    *(s8*)(m + 0x1B28) = -1;
    *(s8*)(m + 0x1B29) = -1;
    *(s8*)(m + 0x1B2A) = -1;
    *(s8*)(m + 0x1B2B) = -1;
    *(s8*)(m + 0x1B2C) = -1;
    *(s8*)(m + 0x1B2D) = -1;
    m[0x1B2E] = 0;
    m[0xCCE] = 0;
}

// .text:0x00140BCC size:0x114 mapped:0x8077FC60
void fn_3_140BCC(void) {
    u8* m = g_Minigame;
    if (m[0x190B] == 0) {
        if (*(u32*)(m + 0x17C4) == 0) {
            fn_3_10F550(3, 0);
            sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
            fn_3_151798();
            fn_3_11F480();
            fn_80011578();
            g_Minigame[0xCCE] = 0;
            m[0x190B] = 1;
        }
    } else {
        if (m[0x190B] == 1) {
            m[0x190B] = 2;
            *(s16*)(g_GameLogic + 0x100) = lbl_3_data_21904;
        }
        if (g_Minigame[0x1B19] != 3) {
            *(s16*)(g_GameLogic + 0x100) -= 1;
        }
        m = g_GameLogic;
        if (*(s16*)(m + 0x100) == 7) {
            changeScene(3, 6);
            fn_3_1578F8();
        }
        if (*(s16*)(m + 0x100) <= 0) {
            fn_3_1409AC();
        }
    }
}
// .text:0x00140CE0 size:0x410 mapped:0x8077FD74
void fn_3_140CE0(void) {
    return;
}

// .text:0x001410F0 size:0x1CC mapped:0x80780184
void fn_3_1410F0(void) {
    return;
}

// .text:0x001412BC size:0x128 mapped:0x80780350
void fn_3_1412BC(void) {
    u8* e;
    u8* m;
    u8* p3;
    u8* p2;
    u8* p1;
    s8 i;
    int idx;
    e = g_Minigame + 0x1DCC;
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    m = g_Minigame;
    p2 = lbl_3_data_2197C;
    p3 = lbl_3_data_21944;
    p1 = lbl_3_data_2194C;
    i = 0;
    do {
        idx = m[0x18DC];
        *(s16*)e = RandomInt_Game_Range(((s16*)p1)[idx * 2], ((s16*)p1)[idx * 2 + 1]);
        if (RandomInt_Game(100) < *(s8*)(p2 + idx)) {
            if (*(s8*)(lbl_3_data_21980 + idx) < 8) {
                e[6] = RandomInt_Game_Range(*(s8*)(lbl_3_data_21980 + idx), 8);
            } else {
                e[6] = 8;
            }
        } else {
            e[6] = 0x7F;
        }
        e[5] = 2;
        e[7] = RandomInt_Game_Range(*(s8*)(p3 + idx * 2), *(s8*)(p3 + idx * 2 + 1));
        i++;
        e += 8;
        m++;
    } while (i < 4);
    changeScene(1, 6);
    fn_3_5A6D4(2);
}
// .text:0x001413E4 size:0xC8 mapped:0x80780478
void fn_3_1413E4(void) {
    u8* g;
    fn_3_7DD6C();
    g = g_GameLogic;
    switch (g[0x125]) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        *(s16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(g + 0xFE) > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g[0x125] = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}
// .text:0x001414AC size:0x580 mapped:0x80780540
void fn_3_1414AC(void) {
    return;
}

