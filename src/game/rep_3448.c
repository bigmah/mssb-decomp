#include "game/rep_3448.h"
#include "header_rep_data.h"

typedef struct {
    u8* p;
    s32 pad;
} QEnt;

extern u8 g_Scores[];
extern u8 lbl_3_data_24CE4[];
extern u8 lbl_3_data_246E4[];
extern u8 lbl_3_data_24D44[];
extern u8 g_Batter[];
extern u8 lbl_3_data_24DA4[];
extern u8 lbl_3_data_21798[];
extern u8 lbl_3_data_91FC[];
extern u8 lbl_800EF808[];
extern u8 lbl_800EFBA4[];
extern void fn_800363D8(void*, int, int, int, s32);
extern void fn_800362F0(void*, int);
extern void fn_3_90064(int);
extern u32 sndFXStartEx(int, u8, u8, u8);
extern u8 g_d_GameSettings[];
extern u8 lbl_3_data_23894[];
extern u8 lbl_3_data_238F4[];
extern void* fn_80034CEC(void*);
extern void fn_800B0A14_removeQueue(void*);
extern u8 g_GameLogic[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_common_bss_34C90[];
extern s16 lbl_3_data_21672;
extern u8 lbl_3_data_21654[];
extern u8 lbl_3_data_B140[];
extern u8 lbl_3_data_B0E0[];

extern u8 lbl_3_data_91BC[];
extern u8 g_Minigame[];
extern u8 lbl_3_data_21884[];

extern u8* lbl_803CC1B8;
extern void fn_80034E20(void*, void*);
extern u8 lbl_3_data_A9F8[];

extern u8 lbl_80371C30[];
extern u8 lbl_3_data_226E0[];
extern u8 lbl_3_data_24784[];
extern u8 lbl_3_data_23A44[];
extern u8 g_Pitcher[];
extern u8 lbl_3_data_23904[];
extern u8 lbl_803616CC[];
extern u8 lbl_80109410[];
extern u8 lbl_3_data_23DA4[];
extern u8 lbl_3_data_213EC[];
extern u8 lbl_3_data_23D24[];
extern u8 g_Ball[];
extern u8 lbl_3_data_23F24[];
extern u8 lbl_80366158[];
extern u8 lbl_3_data_23AE4[];

// .text:0x0011EC28 size:0x404 mapped:0x8075DCBC
void fn_3_11EC28(void) {
    return;
}

// .text:0x0011F02C size:0x454 mapped:0x8075E0C0
void fn_3_11F02C(void) {
    return;
}

// .text:0x0011F480 size:0x34 mapped:0x8075E514
void fn_3_11F480(void) {
    u8* p = g_Minigame;
    u32 i;
    if (p[0x1A2A] == 4) {
        i = 0;
        do {
            *(s16*)(p + 0x1DF4) = *(s16*)(p + 0x1890);
            i++;
            p += 2;
        } while (i < 4);
    }
}

// .text:0x0011F4B4 size:0x54 mapped:0x8075E548
void fn_3_11F4B4(s32 idx, s32 flag) {
    u8* p = g_Minigame;
    if (p[0x1A2A] == 4) {
        u8* q = p + idx * 2;
        *(s16*)(q + 0x1DF4) += lbl_3_data_21884[(flag != 0 ? 2 : 0) * 2 + 1];
    }
}

// .text:0x0011F508 size:0x270 mapped:0x8075E59C
void fn_3_11F508(void) {
    u8** tbl;
    u8* q = lbl_803CC1B8;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_24DA4);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = (g_Batter[0x7B] == 0) << 16;
        tbl = (u8**)(lbl_80371C30 + 8);
        (*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8))[0x68] = 0;
        *(u32*)(*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
        if (g_GameLogic[0x11E] == 2 && g_Minigame[0x1ADB] != 0 && *(s16*)(g_Minigame + 0x18A2) != 0) {
            u32 v = lbl_3_data_21798[6];
            if (v > 9) {
                v = 9;
            }
            fn_800363D8(q, 1, 2, 0x12F, v % 10);
            (*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8))[0x68] = 1;
            *(u16*)(q + 0x1C) = 2;
        }
        break;
    case 2:
        {
        u8* e = lbl_80371C30;
        e += *(u16*)(q + 0x14) * 8;
        if ((*(u8**)(e + 8))[0x69] == 2 && g_GameLogic[0x11E] != 2) {
            *(u16*)(q + 0x1C) = 1;
        }
        }
        break;
    }
}

// .text:0x0011F778 size:0x2E0 mapped:0x8075E80C
void fn_3_11F778(void) {
    u8** tbl;
    u8* q = lbl_803CC1B8;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_24D44);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = (g_Batter[0x7B] == 0) << 16;
        tbl = (u8**)(lbl_80371C30 + 8);
        (*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8))[0x68] = 0;
        *(u32*)(*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
        if (g_GameLogic[0x11E] == 2 && g_Minigame[0x1ADB] != 0 && g_Minigame[0x1ADD] >= 2) {
            u32 n = g_Minigame[0x1ADD];
            if (n > 0x63) {
                n = 0x63;
            }
            if (n < 10) {
                *(u16*)(*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8) + 0x64) = 0x12A;
            } else {
                *(u16*)(*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8) + 0x64) = 0x129;
            }
            fn_800363D8(q, 1, 5, 0x12C, (n % 100) / 10);
            fn_800363D8(q, 1, 4, 0x12C, n % 10);
            (*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8))[0x68] = 1;
            *(u16*)(q + 0x1C) = 2;
        }
        break;
    case 2:
        {
        u8* e = lbl_80371C30;
        e += *(u16*)(q + 0x14) * 8;
        if ((*(u8**)(e + 8))[0x69] == 2 && g_GameLogic[0x11E] != 2) {
            *(u16*)(q + 0x1C) = 1;
        }
        }
        break;
    }
}

// .text:0x0011FA58 size:0x358 mapped:0x8075EAEC
void fn_3_11FA58(void) {
    u8** tbl;
    u8* q = lbl_803CC1B8;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_24CE4);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = (g_Batter[0x7B] == 0) << 16;
        tbl = (u8**)(lbl_80371C30 + 8);
        (*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8))[0x68] = 0;
        *(u32*)(*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
        if (g_GameLogic[0x11E] == 2 && g_Minigame[0x1ADB] != 0) {
            s16 s = *(s16*)(g_Minigame + 0x1DF4);
            if (s > 0) {
                u32 n;
                *(s16*)(g_Minigame + 0x1DF4) = 0;
                n = s;
                if ((u32)s > 0x270F) {
                    n = 0x270F;
                }
                fn_800363D8(q, 1, 4, 0x11B, n >= 0x3E8 ? (n % 10000) / 1000 : 10);
                fn_800363D8(q, 1, 3, 0x11B, n >= 0x64 ? (n % 1000) / 100 : 10);
                fn_800363D8(q, 1, 2, 0x11B, n >= 0xA ? (n % 100) / 10 : 10);
                fn_800363D8(q, 1, 1, 0x11B, n % 10);
                (*(u8**)((u8*)tbl + *(u16*)(q + 0x14) * 8))[0x68] = 1;
                *(u16*)(q + 0x1C) = 2;
            }
        }
        break;
    case 2:
        {
        u8* e = lbl_80371C30;
        e += *(u16*)(q + 0x14) * 8;
        if ((*(u8**)(e + 8))[0x69] == 2 && g_GameLogic[0x11E] != 2) {
            *(u16*)(q + 0x1C) = 1;
        }
        }
        break;
    }
}

// .text:0x0011FDB0 size:0x4BC mapped:0x8075EE44
void fn_3_11FDB0(void) {
    return;
}

// .text:0x0012026C size:0x630 mapped:0x8075F300
void fn_3_12026C(void) {
    return;
}

// .text:0x0012089C size:0x6C0 mapped:0x8075F930
static u32 AnyBusy(u8* q) {
    u8* o;
    u32 i;
    u32 n = *(u16*)(q + 0x16);
    for (i = 0; i < n; i++) {
        o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + i].p;
        if (o[0x68] == 1) {
            if (o[0x69] != 2) {
                return 1;
            }
        } else if (o[0x68] == 4 && (*(u32*)(o + 0x5C) >> 16) != 0) {
            return 1;
        }
    }
    return 0;
}

void fn_3_12089C(void) {
    QEnt* e2;
    QEnt* e3;
    QEnt* e1;
    QEnt* e4;
    u8* q = lbl_803CC1B8;
    QEnt* e0;
    u8* m;
    u32 v;
    s32 w;
    s32 i;
    u32 found;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (g_GameLogic[0x11E] == 0) {
        *(u16*)(q + 0x1E) = 1;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_24784);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        e0 = (QEnt*)lbl_80371C30;
        e3 = e0 + 3;
        e1 = e0 + 1;
        e2 = e0 + 2;
        e4 = e0 + 4;
        e3[*(u16*)(q + 0x14)].p[0x68] = 0;
        *(u32*)(e3[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        e0[*(u16*)(q + 0x14)].p[0x68] = 0;
        *(u32*)(e0[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        e1[*(u16*)(q + 0x14)].p[0x68] = 0;
        *(u32*)(e1[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        e2[*(u16*)(q + 0x14)].p[0x68] = 0;
        *(u32*)(e2[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        e4[*(u16*)(q + 0x14)].p[0x68] = 0;
        *(u32*)(e4[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        if (g_GameLogic[0x11E] == 1 && (g_Pitcher[0x13E] == 4 || g_Minigame[0x1A81] != 0)) {
            if (g_Minigame[0x1A8A] != 0) {
                fn_3_90064(0x300);
                e2[*(u16*)(q + 0x14)].p[0x68] = 1;
                if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
                    m = g_Minigame;
                    w = *(s16*)(m + *(s8*)(m + 0x1904) * 2 + 0x1890) / 2;
                    if (w != 0) {
                        if ((u32)w > 0x3E7) {
                            w = 0x3E7;
                        }
                        if ((u32)w >= 0x64) {
                            fn_800363D8(q, 4, 4, 0x11C, 0xB);
                            fn_800363D8(q, 4, 3, 0x11C, ((u32)w % 1000) / 100);
                        } else if ((u32)w >= 0xA) {
                            fn_800363D8(q, 4, 4, 0x11C, 0xA);
                            fn_800363D8(q, 4, 3, 0x11C, 0xB);
                        } else {
                            fn_800363D8(q, 4, 4, 0x11C, 0xA);
                            fn_800363D8(q, 4, 3, 0x11C, 0xA);
                        }
                        if ((u32)w >= 0xA) {
                            fn_800363D8(q, 4, 2, 0x11C, ((u32)w % 100) / 10);
                        } else {
                            fn_800363D8(q, 4, 2, 0x11C, 0xB);
                        }
                        fn_800363D8(q, 4, 1, 0x11C, (u32)w % 10);
                        e4[*(u16*)(q + 0x14)].p[0x68] = 1;
                    }
                }
            } else {
                s16 mult = 1;
                if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
                    if (*(s32*)g_Scores == g_Scores[0xAA]) {
                        mult = lbl_3_data_21672;
                    }
                }
                if (g_Minigame[0x1A89] == 1) {
                    v = *(s16*)(lbl_3_data_21654 + 0x14) * mult;
                } else {
                    u8* ee = g_Minigame;
                    ee += *(s8*)(ee + 0x1904) * 2;
                    v = *(s16*)(ee + 0x1898) * mult;
                }
                if (v > 0x3E7) {
                    v = 0x3E7;
                }
                if (v >= 0x64) {
                    fn_800363D8(q, 3, 3, 0x11B, (v % 1000) / 100);
                } else {
                    fn_800363D8(q, 3, 3, 0x11B, 0xA);
                }
                if (v >= 0xA) {
                    fn_800363D8(q, 3, 2, 0x11B, (v % 100) / 10);
                } else {
                    fn_800363D8(q, 3, 2, 0x11B, 0xA);
                }
                fn_800363D8(q, 3, 1, 0x11B, v % 10);
                e3[*(u16*)(q + 0x14)].p[0x68] = 1;
                if (g_Minigame[0x1A89] == 1) {
                    ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p[0x68] = 1;
                    e1[*(u16*)(q + 0x14)].p[0x68] = 1;
                }
            }
            *(u16*)(q + 0x1E) = 0;
            *(u16*)(q + 0x1C) = 2;
        }
        break;
    case 2:
        if (AnyBusy(q) == 0 && *(u16*)(q + 0x1E) != 0) {
            *(u16*)(q + 0x1C) = 1;
        }
        break;
    }
}

// .text:0x00120F5C size:0x9C mapped:0x8075FFF0
s32 fn_3_120F5C(void) {
    s16 mult = 1;
    if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
        if (*(s32*)g_Scores == g_Scores[0xAA]) {
            mult = lbl_3_data_21672;
        }
    }
    if (g_Minigame[0x1A89] == 1) {
        return *(s16*)(lbl_3_data_21654 + 0x14) * mult;
    }
    {
        u8* e = g_Minigame;
        e += *(s8*)(e + 0x1904) * 2;
        return *(s16*)(e + 0x1898) * mult;
    }
}

// .text:0x00120FF8 size:0x30C mapped:0x8076008C
// near-match (12 lines): case 1 gt-2 block base reg r5/r6 swap only
void fn_3_120FF8(void) {
    u8* q = lbl_803CC1B8;
    u32 v;
    u8* o;
    u8* t;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_246E4);
        {
            u8* e = lbl_80371C30;
            e += *(u16*)(q + 0x14) * 8;
            *(u32*)(*(u8**)(e + 0x10) + 0x5C) = 0xD0000;
        }
        *(u16*)(q + 0x1E) = *(u16*)(q + 0x20) = g_Scores[0xAA];
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        if (g_GameLogic[0x11E] == 7) {
            *(u16*)(q + 0x1E) = g_Scores[0xAA] - (*(s32*)g_Scores - 1);
        }
        v = *(u16*)(q + 0x1E);
        if (v > 9) {
            v = 9;
        }
        fn_800363D8(q, 1, 1, 0x14E, v % 10);
        o = *(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8);
        if ((*(u32*)(o + 0x5C) >> 16) < 10) {
            o[0x68] = 1;
        } else if ((*(u32*)(o + 0x5C) >> 16) > 10) {
            o[0x68] = 4;
        } else {
            o[0x68] = 0;
        }
        if (*(u16*)(q + 0x20) != *(u16*)(q + 0x1E)) {
            if (*(u16*)(q + 0x20) < *(u16*)(q + 0x1E)) {
                t = lbl_80371C30 + 0x10;
                (*(u8**)(t + *(u16*)(q + 0x14) * 8))[0x68] = 1;
                *(u32*)(*(u8**)(t + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
            } else if (*(u16*)(q + 0x20) - *(u16*)(q + 0x1E) == 2) {
                u8* b = lbl_80371C30;
                t = b + 0x18;
                (*(u8**)(t + *(u16*)(q + 0x14) * 8))[0x68] = 1;
                *(u32*)(*(u8**)(t + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
                (*(u8**)(b + *(u16*)(q + 0x14) * 8))[0x68] = 1;
                *(u16*)(q + 0x1C) = 2;
            }
            *(u16*)(q + 0x20) = *(u16*)(q + 0x1E);
        }
        break;
    case 2:
        o = *(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8);
        if ((u32)__cntlzw(2 - o[0x69]) >> 5) {
            *(u32*)(o + 0x5C) = 0xA0000;
            *(u16*)(q + 0x1C) = 1;
        }
        break;
    }
}

// .text:0x00121304 size:0x604 mapped:0x80760398
void fn_3_121304(void) {
    return;
}

// .text:0x00121908 size:0xA2C mapped:0x8076099C
void fn_3_121908(void) {
    return;
}

// .text:0x00122334 size:0x3A0 mapped:0x807613C8
void fn_3_122334(void) {
    u8* q = lbl_803CC1B8;
    u8* m = g_Minigame;
    u8* o;
    u32 v;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_23F24);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        if (m[0x1DF7] != 0) {
            *(u16*)(q + 0x1E) = 1;
        }
        if (g_GameLogic[0x11E] == 2) {
            if (*(u16*)(q + 0x1E) != 0) {
                (*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x68] = 1;
            } else {
                o = *(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8);
                if ((*(u32*)(o + 0x5C) >> 16) < 10) {
                    o[0x68] = 1;
                } else if ((*(u32*)(o + 0x5C) >> 16) > 10) {
                    o[0x68] = 4;
                } else {
                    o[0x68] = 0;
                }
            }
            if (g_Ball[0x1BD1] != 0 && g_Ball[0x1BEE] != 0) {
                u16 cur = *(u16*)(q + 0x20);
                s32 d = *(s16*)(g_Ball + 0x1B9E) - cur;
                if (d != 0) {
                    s32 step = d / 4;
                    if (step != 0) {
                        *(u16*)(q + 0x20) = cur + step;
                    } else {
                        *(u16*)(q + 0x20) = cur + d / (d < 0 ? -d : d);
                    }
                }
            } else if (*(s16*)(g_Ball + 0x1B7A) != 1 && g_Ball[0x1BCC] == 0) {
                *(u16*)(q + 0x20) = (s32)*(f32*)(g_Ball + 0x1A00);
            }
            v = *(u16*)(q + 0x20);
            if (v > 0x3E7) {
                v = 0x3E7;
            }
            if (v >= 0x64) {
                fn_800363D8(q, 0, 3, 0x169, (v % 1000) / 100);
            } else {
                fn_800363D8(q, 0, 3, 0x169, 10);
            }
            if (v >= 10) {
                fn_800363D8(q, 0, 2, 0x169, (v % 100) / 10);
            } else {
                fn_800363D8(q, 0, 2, 0x169, 10);
            }
            fn_800363D8(q, 0, 1, 0x169, v % 10);
        } else {
            (*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x68] = 0;
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
            *(u16*)(q + 0x1E) = 0;
            *(u16*)(q + 0x20) = 0;
        }
        break;
    }
}

// .text:0x001226D4 size:0x650 mapped:0x80761768
void fn_3_1226D4(void) {
    return;
}

// .text:0x00122D24 size:0x4B0 mapped:0x80761DB8
void fn_3_122D24(void) {
    return;
}

// .text:0x001231D4 size:0x3E4 mapped:0x80762268
// near-match: only reg allocation (orig keeps *(q+0xC) in r3 and prelude base in r4; ours swaps them)
void fn_3_1231D4(void) {
    u8* q = lbl_803CC1B8;
    u8* r = *(u8**)(q + 0xC);
    QEnt* b;
    u8* p;
    s32 v;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_23DA4);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        b = (QEnt*)lbl_80371C30;
        b[*(u16*)(q + 0x14)].p[0x68] = 4;
        if (*(u16*)(r + 0x1A) == 1) {
            p = g_Minigame;
            if (p[0x1AD5] != 0) {
                if (p[0x1ACC + *(s8*)(p + 0x1905) * 2] >= 2) {
                    *(u16*)(b[*(u16*)(q + 0x14)].p + 0x64) = 0x164;
                    *(u16*)(b[*(u16*)(q + 0x14) + 1].p + 0x72) = 0;
                } else {
                    *(u16*)(b[*(u16*)(q + 0x14)].p + 0x64) = 0x163;
                    *(u16*)(b[*(u16*)(q + 0x14) + 1].p + 0x72) = 0;
                }
                v = *(s16*)(lbl_3_data_213EC + 0xE);
                if ((u32)v > 0x270F) {
                    v = 0x270F;
                }
                if ((u32)v >= 0x3E8) {
                    fn_800363D8(q, 1, 4, 0x167, ((u32)v % 10000) / 1000);
                } else if ((u32)v >= 0x64) {
                    fn_800363D8(q, 1, 4, 0x167, 0xB);
                } else {
                    fn_800363D8(q, 1, 4, 0x167, 0xA);
                }
                if ((u32)v >= 0x64) {
                    fn_800363D8(q, 1, 3, 0x167, ((u32)v % 1000) / 100);
                } else if ((u32)v >= 0xA) {
                    fn_800363D8(q, 1, 3, 0x167, 0xB);
                } else {
                    fn_800363D8(q, 1, 3, 0x167, 0xA);
                }
                if ((u32)v >= 0xA) {
                    fn_800363D8(q, 1, 2, 0x167, ((u32)v % 100) / 10);
                } else {
                    fn_800363D8(q, 1, 2, 0x167, 0xB);
                }
                fn_800363D8(q, 1, 1, 0x167, (u32)v % 10);
                *(u16*)(q + 0x1C) = 2;
            }
        }
        break;
    case 2:
        (*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x68] = 1;
        if (*(u16*)(r + 0x1A) != 1) {
            *(u16*)(q + 0x1C) = 1;
        }
        break;
    }
}

// .text:0x001235B8 size:0x3D8 mapped:0x8076264C
// 99%: only diff is v%10 in v>=10 branch: orig computes into r7 then `mr r29,r7`, ours computes into r29 then `mr r7,r29`
void fn_3_1235B8(void) {
    u8* q = lbl_803CC1B8;
    u8* p;
    u8* t;
    u32 v;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_23D24);
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        if (g_GameLogic[0x11E] == 1) {
            p = g_Minigame;
            t = p + 0x1ACC;
            if (t[*(s8*)(p + 0x1905) * 2] >= 2) {
                *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = (g_Batter[0x7B] != 0) << 16;
                v = t[*(s8*)(p + 0x1905) * 2];
                if (v > 0x63) {
                    v = 0x63;
                }
                if (v < 10) {
                    QEnt* b = (QEnt*)lbl_80371C30;
                    QEnt* e;
                    b[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
                    fn_800363D8(q, 1, 4, 0x104, v % 10);
                    fn_800363D8(q, 1, 5, 0x104, v % 10);
                    fn_800363D8(q, 1, 6, 0x104, v % 10);
                    b = (QEnt*)lbl_80371C30;
                    e = b + 2;
                    e[*(u16*)(q + 0x14)].p[0x68] = 0;
                    *(u32*)(e[*(u16*)(q + 0x14)].p + 0x5C) = 0;
                } else {
                    QEnt* b = (QEnt*)lbl_80371C30;
                    QEnt* e;
                    b[*(u16*)(q + 0x14) + 2].p[0x68] = 1;
                    fn_800363D8(q, 2, 4, 0x104, v % 10);
                    fn_800363D8(q, 2, 5, 0x104, v % 10);
                    fn_800363D8(q, 2, 6, 0x104, v % 10);
                    fn_800363D8(q, 2, 7, 0x104, (v % 100) / 10);
                    fn_800363D8(q, 2, 8, 0x104, (v % 100) / 10);
                    fn_800363D8(q, 2, 9, 0x104, (v % 100) / 10);
                    b = (QEnt*)lbl_80371C30;
                    e = b + 1;
                    e[*(u16*)(q + 0x14)].p[0x68] = 0;
                    *(u32*)(e[*(u16*)(q + 0x14)].p + 0x5C) = 0;
                }
                break;
            }
        }
        ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 1].p[0x68] = 4;
        ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p[0x68] = 4;
        break;
    }
}

// .text:0x00123990 size:0x52C mapped:0x80762A24
void fn_3_123990(void) {
    return;
}

// .text:0x00123EBC size:0x4E8 mapped:0x80762F50
void fn_3_123EBC(void) {
    u8* d = lbl_3_data_226E0;
    u8* q = lbl_803CC1B8;
    u8* o;
    u32 x;
    u32 v;
    u32 i;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        switch (g_Minigame[0x1A2A]) {
        case 4:
            fn_80034E20(q, d + 0x1484);
            break;
        case 5:
            fn_80034E20(q, d + 0x14E4);
            break;
        case 6:
            fn_80034E20(q, d + 0x1544);
            break;
        }
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        switch (g_Minigame[0x1A2A]) {
        case 4:
            o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
            x = *(u32*)(o + 0x5C) >> 16;
            if (x < 12) {
                o[0x68] = 1;
            } else if (x > 12) {
                o[0x68] = 4;
            } else {
                o[0x68] = 0;
            }
            if (g_Minigame[0x1B19] == 3) {
                *(u16*)(q + 0x1C) = 2;
            }
            break;
        case 5:
            o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
            x = *(u32*)(o + 0x5C) >> 16;
            if (x < 10) {
                o[0x68] = 1;
            } else if (x > 10) {
                o[0x68] = 4;
            } else {
                o[0x68] = 0;
            }
            break;
        case 6:
            o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
            x = *(u32*)(o + 0x5C) >> 16;
            if (x < 10) {
                o[0x68] = 1;
            } else if (x > 10) {
                o[0x68] = 4;
            } else {
                o[0x68] = 0;
            }
            break;
        }
        break;
    case 2:
    case 4:
        ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p[0x68] = 1;
        if (g_Minigame[0x1B19] != 3) {
            o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
            if ((u32)__cntlzw(2 - o[0x69]) >> 5) {
                *(u32*)(o + 0x5C) = 0;
                *(u16*)(q + 0x1C) = 1;
            }
        }
        break;
    }
    v = *(u32*)(g_Minigame + 0x17C4) * 100 / 60;
    if (v > 0x270F) {
        v = 0x270F;
    }
    for (i = 0; i < 2; i++) {
        fn_800363D8(q, 1, i * 4 + 1, 0x138, (v % 10000) / 1000);
        fn_800363D8(q, 1, i * 4 + 2, 0x138, (v % 1000) / 100);
        fn_800363D8(q, 1, i * 4 + 3, 0x138, (v % 100) / 10);
        fn_800363D8(q, 1, i * 4 + 4, 0x138, v % 10);
    }
    if (v < 1000) {
        if (lbl_80366158[0x28] != 0) {
            QEnt* t = (QEnt*)lbl_80371C30;
            t[*(u16*)(q + 0x14) + 1].p[0x68] = 0;
        } else {
            QEnt* t = (QEnt*)lbl_80371C30;
            t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
        }
    } else {
        QEnt* t = (QEnt*)lbl_80371C30 + 1;
        *(u32*)(t[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        t[*(u16*)(q + 0x14)].p[0x68] = 0;
    }
}

// .text:0x001243A4 size:0x394 mapped:0x80763438
void fn_3_1243A4(void) {
    u8* q = lbl_803CC1B8;
    u8* p;
    u32 a;
    u32 b;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_23AE4);
        switch (g_Minigame[0x1A2A]) {
        case 1:
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
            break;
        case 2:
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = 0x10000;
            break;
        case 3:
            *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = 0x20000;
            break;
        }
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        p = g_Minigame;
        switch (p[0x1A2A]) {
        case 1:
            a = *(u32*)g_Scores;
            b = g_Scores[0xAA];
            break;
        case 2:
            a = *(u32*)g_Scores;
            b = g_Scores[0xAA];
            break;
        case 3:
            a = *(u32*)g_Scores;
            b = g_Scores[0xAA];
            break;
        }
        if (b > 9) {
            b = 9;
        }
        if (a > b) {
            a = b;
        }
        fn_800363D8(q, 2, 1, 0x140, a);
        fn_800363D8(q, 2, 4, 0x140, b);
        switch (p[0x1A2A]) {
        case 1:
            if (g_GameLogic[0x11E] == 0 || g_GameLogic[0x11E] == 1) {
                { QEnt* t = (QEnt*)lbl_80371C30; t[*(u16*)(q + 0x14) + 1].p[0x68] = 1; }
            } else {
                { QEnt* t = (QEnt*)lbl_80371C30; t[*(u16*)(q + 0x14) + 1].p[0x68] = 4; }
            }
            break;
        case 2:
            { QEnt* t = (QEnt*)lbl_80371C30; t[*(u16*)(q + 0x14) + 1].p[0x68] = 1; }
            break;
        case 3:
            { QEnt* t = (QEnt*)lbl_80371C30; t[*(u16*)(q + 0x14) + 1].p[0x68] = 1; }
            break;
        }
        if (lbl_80366158[0x28] != 0) {
            { QEnt* t = (QEnt*)lbl_80371C30; t[*(u16*)(q + 0x14) + 2].p[0x68] = 0; }
        } else {
            { QEnt* t = (QEnt*)lbl_80371C30; t[*(u16*)(q + 0x14) + 2].p[0x68] = 1; }
        }
        break;
    }
}

// .text:0x00124738 size:0x5A8 mapped:0x807637CC
void fn_3_124738(void) {
    u8* q = lbl_803CC1B8;
    u8* gl;
    u8* m;
    u8* o;
    QEnt* t;
    s32 n;
    u32 x;
    u32 f;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        fn_80034E20(q, lbl_3_data_23A44);
        if (g_Minigame[0x1A2A] == 3) {
            fn_800363D8(q, 1, 4, 0x14D, 1);
        }
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        gl = g_GameLogic;
        if (gl[0x11E] == 1 && *(u16*)(gl + 0xFC) == 0) {
            m = g_Minigame;
            if (m[0x1A2A] == 1) {
                q[0x24] = m[0x1A2F] - m[0x1A2D];
                q[0x25] = m[0x1A2D];
            } else {
                q[0x24] = m[0x1A2E];
            }
        }
        n = *(s8*)(q + 0x24);
        if (n > 0x63) {
            n = 0x63;
        }
        if (n > 1) {
            {
                QEnt* tt = (QEnt*)lbl_80371C30;
                *(u32*)(tt[*(u16*)(q + 0x14) + 1].p + 0x5C) = 0;
            }
            if (n >= 10) {
                fn_800363D8(q, 1, 1, 0x14E, (n % 100) / 10);
            } else {
                fn_800363D8(q, 1, 1, 0x14E, 10);
            }
            fn_800363D8(q, 1, 2, 0x14E, n % 10);
            t = (QEnt*)lbl_80371C30 + 2;
            t[*(u16*)(q + 0x14)].p[0x68] = 0;
            *(u32*)(t[*(u16*)(q + 0x14)].p + 0x5C) = 0;
        } else {
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 1].p + 0x5C) = 0x10000;
            ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p[0x68] = 1;
        }
        m = g_Minigame;
        if (m[0x1A2A] == 1) {
            if (m[0x1909] == 0 && m[0x1A3C] == 0 && m[0x1A2B] == 3) {
                if (m[0x1A2F] <= q[0x25] && q[0x25] < 0x13) {
                    *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 1].p + 0x5C) = 0x10000;
                    t = (QEnt*)lbl_80371C30 + 2;
                    t[*(u16*)(q + 0x14)].p[0x68] = 0;
                    *(u32*)(t[*(u16*)(q + 0x14)].p + 0x5C) = 0;
                    ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 3].p[0x68] = 1;
                } else {
                    t = (QEnt*)lbl_80371C30 + 3;
                    t[*(u16*)(q + 0x14)].p[0x68] = 0;
                    *(u32*)(t[*(u16*)(q + 0x14)].p + 0x5C) = 0;
                }
            }
            if (gl[0x11E] == 0 || gl[0x11E] == 1) {
                if (*(s8*)(q + 0x24) <= 1 && g_Pitcher[0x13E] >= 4) {
                    ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p[0x68] = 1;
                } else {
                    o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
                    x = *(u32*)(o + 0x5C) >> 16;
                    if (x < 0xE) {
                        o[0x68] = 1;
                    } else if (x > 0xE) {
                        o[0x68] = 4;
                    } else {
                        o[0x68] = 0;
                    }
                }
            } else {
                o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
                x = *(u32*)(o + 0x5C) >> 16;
                if (x != 0) {
                    if (x < 0x18) {
                        o[0x68] = 1;
                        f = 0;
                    } else if (x > 0x18) {
                        o[0x68] = 4;
                        f = 0;
                    } else {
                        o[0x68] = 0;
                        f = 1;
                    }
                    if (f != 0) {
                        *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0;
                    }
                }
            }
        } else {
            if (m[0x1A2E] == 0 && gl[0x11E] != 0 && gl[0x11E] != 1 && gl[0x11E] != 2) {
                ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p[0x68] = 1;
            } else {
                o = ((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p;
                x = *(u32*)(o + 0x5C) >> 16;
                if (x < 0xE) {
                    o[0x68] = 1;
                } else if (x > 0xE) {
                    o[0x68] = 4;
                } else {
                    o[0x68] = 0;
                }
            }
        }
        break;
    }
}

// .text:0x00124CE0 size:0x68C mapped:0x80763D74
void fn_3_124CE0(void) {
    u8* q = lbl_803CC1B8;
    u8* m;
    QEnt* b;
    u32 v;
    s32 lim;
    u32 t;
    if (fn_3_12536C()) {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        if (g_Minigame[0x1909] != 0) {
            ((void (*)(void))fn_800B0A14_removeQueue)();
            break;
        }
        if (g_Minigame[0x1909] == 0 && g_Minigame[0x1A3C] == 0 && g_Minigame[0x1A2B] == 3) {
            *(u16*)(q + 0x1E) = 1;
        } else if (g_Minigame[0x1A2A] == 1 || g_Minigame[0x1A2A] == 3) {
            *(u16*)(q + 0x1E) = 0;
        } else {
            ((void (*)(void))fn_800B0A14_removeQueue)();
            break;
        }
        fn_80034E20(q, lbl_3_data_23904);
        switch (g_Minigame[0x1A2A]) {
        case 1:
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0;
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p + 0x5C) = 0;
            break;
        case 2:
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0x10000;
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p + 0x5C) = 0x10000;
            break;
        case 3:
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0x20000;
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p + 0x5C) = 0x20000;
            break;
        case 4:
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0x40000;
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p + 0x5C) = 0x40000;
            break;
        case 5:
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0x30000;
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p + 0x5C) = 0x30000;
            break;
        case 6:
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14)].p + 0x5C) = 0x50000;
            *(u32*)(((QEnt*)lbl_80371C30)[*(u16*)(q + 0x14) + 2].p + 0x5C) = 0x50000;
            break;
        }
        b = (QEnt*)lbl_80371C30;
        t = *(u16*)(q + 0x1E);
        *(u32*)(b[*(u16*)(q + 0x14) + 3].p + 0x5C) = t << 16;
        t = *(u16*)(q + 0x1E);
        *(s16*)(b[*(u16*)(q + 0x14) + 4].p + 0x64) = ((s32)(-t | t) >> 31) + 0x142;
        *(u32*)(b[*(u16*)(q + 0x14) + 5].p + 0x5C) = 0x3D0000;
        *(u32*)(b[*(u16*)(q + 0x14) + 6].p + 0x5C) = 0x3D0000;
        *(u32*)(b[*(u16*)(q + 0x14) + 7].p + 0x5C) = 0x3D0000;
        *(u32*)(b[*(u16*)(q + 0x14) + 8].p + 0x5C) = 0x3D0000;
        *(u16*)(q + 0x1C) = 1;
        break;
    case 1:
        if (*(u16*)(q + 0x1E) != 0) {
            v = *(u32*)(lbl_803616CC + g_Minigame[0x1A2A] * 0x28);
        } else {
            v = *(s16*)(g_Minigame + 0x1A26);
        }
        m = g_Minigame;
        lim = *(s16*)(lbl_80109410 + m[0x1A2A] * 2);
        if (v > lim) {
            v = lim;
        }
        fn_800363D8(q, 5, 1, 0x145, (v % 10000) / 1000);
        fn_800363D8(q, 6, 1, 0x145, (v % 1000) / 100);
        fn_800363D8(q, 7, 1, 0x145, (v % 100) / 10);
        fn_800363D8(q, 8, 1, 0x145, v % 10);
        switch (m[0x1A2A]) {
        case 1:
            if (g_GameLogic[0x11E] == 0 || g_GameLogic[0x11E] == 1) {
                {
                    QEnt* t = (QEnt*)lbl_80371C30;
                    t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
                }
            } else {
                {
                    QEnt* t = (QEnt*)lbl_80371C30;
                    t[*(u16*)(q + 0x14) + 1].p[0x68] = 4;
                }
            }
            break;
        case 2:
            {
                QEnt* t = (QEnt*)lbl_80371C30;
                t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
            }
            break;
        case 3:
            {
                QEnt* t = (QEnt*)lbl_80371C30;
                t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
            }
            break;
        case 4:
            if (g_Minigame[0x1B19] != 3) {
                {
                    QEnt* t = (QEnt*)lbl_80371C30;
                    t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
                }
            } else {
                {
                    QEnt* t = (QEnt*)lbl_80371C30;
                    t[*(u16*)(q + 0x14) + 1].p[0x68] = 4;
                }
            }
            break;
        case 5:
            {
                QEnt* t = (QEnt*)lbl_80371C30;
                t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
            }
            break;
        case 6:
            {
                QEnt* t = (QEnt*)lbl_80371C30;
                t[*(u16*)(q + 0x14) + 1].p[0x68] = 1;
            }
            break;
        }
        break;
    }
}

// .text:0x0012536C size:0xB8 mapped:0x80764400
u32 fn_3_12536C(void) {
    if (lbl_3_common_bss_32724[0x96] != 0 || lbl_3_common_bss_32724[0xB7] != 0) {
        return 1;
    }
    if (g_GameLogic[0x11E] == 0xF) {
        return 1;
    }
    if (g_Minigame[0x1A3B] != 0) {
        u8 v = lbl_3_common_bss_34C90[0x1D2];
        if (v == 7 || v == 9) {
            return 1;
        }
        if (v == 0xD) {
            return 1;
        }
    }
    if (g_GameLogic[0x11E] == 0xE && *(u16*)(g_GameLogic + 0xFC) == 0) {
        return 1;
    }
    return 0;
}

// .text:0x00125424 size:0x5C mapped:0x807644B8
s32 fn_3_125424(u8* a, s32 i, u32 v) {
    u8* e = *(u8**)(lbl_80371C30 + ((*(u16*)(a + 0x14) + i) << 3));
    u32 x = *(u32*)(e + 0x5C) >> 16;
    if (x < v) {
        e[0x68] = 1;
        return 0;
    }
    if (x > v) {
        e[0x68] = 4;
        return 0;
    }
    e[0x68] = 0;
    return 1;
}

// .text:0x00125480 size:0x78 mapped:0x80764514
s32 fn_3_125480(u8* a) {
    u8* e;
    u32 i;
    u16 n = *(u16*)(a + 0x16);
    for (i = 0; i < n; i++) {
        e = *(u8**)(lbl_80371C30 + ((*(u16*)(a + 0x14) + i) << 3));
        if (e[0x68] == 1) {
            if (e[0x69] != 2) {
                return 1;
            }
        } else if (e[0x68] == 4) {
            if ((*(u32*)(e + 0x5C) >> 16) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

// .text:0x001254F8 size:0x10C mapped:0x8076458C
void fn_3_1254F8(void) {
    u8* q = lbl_803CC1B8;
    if (g_GameLogic[0x11E] != 5) {
        g_Minigame[0x1E02] = 0;
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    switch (*(u16*)(q + 0x1C)) {
    case 0:
        g_Minigame[0x1E02] = 1;
        fn_80034E20(q, lbl_3_data_23894);
        *(u16*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x64) = *(u16*)(lbl_3_data_238F4 + g_Minigame[0x1A2A] * 2);
        if (g_Minigame[0x1A3C] != 0 && g_Minigame[0x1E2A] >= 6) {
            u8* t = *(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8 + 8);
            *(u32*)(t + 0x54) |= 2;
        }
        *(u16*)(q + 0x1C) = 1;
    case 1:
        break;
    }
}

// .text:0x00125604 size:0x24C mapped:0x80764698
void fn_3_125604(void) {
    u8* q = lbl_803CC1B8;
    if (g_Minigame[0x1A40] == 0) {
        u16 t = *(u16*)(q + 0x18);
        if (t < 0xFFFE) {
            *(u16*)(q + 0x18) = t + 1;
        } else {
            *(u16*)(q + 0x18) = 0xFFFF;
        }
        t = *(u16*)(q + 0x1C);
        if (t == 0) {
            u8* m = g_Minigame;
            if (m[0x1A41] != 0) {
                *(s16*)(m + 0x1A28) -= 1;
                if (*(s16*)(m + 0x1A28) <= 0) {
                    *(u16*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x64) = *(u16*)(lbl_3_data_91FC + m[0x1A41] * 2);
                    *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x54) |= 2;
                    (*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x68] = 1;
                    *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) = 0;
                    if (m[0x1A41] == 4) {
                        fn_800363D8(q, 0, 1, 0x13C, *(s32*)g_Scores - 1);
                        fn_3_90064(0x2F8);
                    }
                    *(u16*)(q + 0x1C) = m[0x1A41];
                    *(u16*)(q + 0x18) = 0;
                    g_Minigame[0x1A42] = 1;
                    m[0x1A41] = 0;
                }
            }
        } else {
            if ((*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x69] == 2) {
                if (t == 4) {
                    fn_800362F0(q, 0);
                }
                *(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x54) &= ~2;
                g_Minigame[0x1A42] = 0;
                g_Minigame[0x1A41] = 0;
                *(u16*)(q + 0x1C) = 0;
            }
            t = *(u16*)(q + 0x1C);
            if (t == 2) {
                if (*(u16*)(q + 0x18) == 0x46) {
                    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
                    return;
                }
            } else if (t == 1) {
                if (*(u16*)(q + 0x18) == 1 && lbl_800EF808[0x398] == 1) {
                    fn_3_90064(0x2EE);
                    return;
                }
            }
        }
    } else {
        fn_80034CEC(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x00125850 size:0x70 mapped:0x807648E4
void fn_3_125850(void) {
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_91BC);
    g_Minigame[0x1A42] = 0;
    *(s16*)(p + 0x18) = 0;
    *(s16*)(p + 0x1A) = 0;
    *(s16*)(p + 0x1C) = 0;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_3_125604;
}

// .text:0x001258C0 size:0xD44 mapped:0x80764954
void fn_3_1258C0(void) {
    return;
}

// .text:0x00126604 size:0xEB0 mapped:0x80765698
void fn_3_126604(void) {
    return;
}

// .text:0x001274B4 size:0x6B4 mapped:0x80766548
void fn_3_1274B4(void) {
    return;
}

// .text:0x00127B68 size:0xED0 mapped:0x80766BFC
void fn_3_127B68(void) {
    return;
}

// .text:0x00128A38 size:0x158 mapped:0x80767ACC
void fn_3_128A38(void) {
    u8* q;
    u8* o;
    u16 v;
    u8 flag = lbl_3_common_bss_32724[0x96];
    q = ((u8**)&lbl_803CC1B8)[0];
    if (flag == 0) {
        v = *(u16*)(q + 0x1C);
        if (v == 1) {
        o = *(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8);
        if ((*(u32*)(o + 0x5C) >> 16) >= 0xA) {
            o[0x68] = 0;
            *(u16*)(q + 0x1C) = *(u16*)(q + 0x1C) + 1;
        }
        } else if (v == 2) {
        if (g_d_GameSettings[7] == 6) {
            if (lbl_3_common_bss_34C90[0x1D2] == 5) {
                (*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x68] = 1;
                *(u16*)(q + 0x1C) = *(u16*)(q + 0x1C) + 1;
            }
        } else if (lbl_3_common_bss_34C90[0x1D4] == 5) {
            (*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8))[0x68] = 1;
            *(u16*)(q + 0x1C) = *(u16*)(q + 0x1C) + 1;
        }
        } else if (v == 3) {
            if ((*(u32*)(*(u8**)(lbl_80371C30 + *(u16*)(q + 0x14) * 8) + 0x5C) >> 16) >= 0x14) {
                goto rem;
            }
        }
        return;
    }
rem:
        ((void (*)(u8*))fn_80034CEC)(q);
        ((void (*)(void))fn_800B0A14_removeQueue)();
}

// .text:0x00128B90 size:0x88 mapped:0x80767C24
void fn_3_128B90(void) {
    u8* q = lbl_803CC1B8;
    u16* tb = (u16*)lbl_3_data_B140;
    u32 i = g_Minigame[0x1A2A];
    u16 v = tb[i * 2];
    *(u16*)(lbl_3_data_B0E0 + 2) = v;
    *(u16*)(lbl_3_data_B0E0 + 0x22) = tb[i * 2 + 1];
    fn_80034E20(q, lbl_3_data_B0E0);
    *(s16*)(q + 0x1C) = 1;
    *(void**)lbl_803CC1B8 = fn_3_128A38;
}

// .text:0x00128C18 size:0x758 mapped:0x80767CAC
void fn_3_128C18(void) {
    return;
}

// .text:0x00129370 size:0x60 mapped:0x80768404
void fn_3_129370(void) {
    u8* p = lbl_803CC1B8;
    fn_80034E20(p, lbl_3_data_A9F8);
    *(s16*)(p + 0x18) = 0;
    *(s16*)(p + 0x1A) = 0;
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_3_128C18;
}

