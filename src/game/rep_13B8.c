#include "game/rep_13B8.h"
#include "header_rep_data.h"
extern f32 lbl_3_data_4A34[];
extern s16 lbl_3_data_21904[];
typedef struct { f32 x, z; } P2;

extern f32 lbl_3_rodata_1498;

#pragma dont_inline on

extern u8 inMemRoster[];
extern u8 g_GameLogic[];

extern u8 g_Scores[];

extern u8 g_Batter[];
extern u8 g_Runners[];
extern u8 g_Ball[];
extern u8 g_Fielders[];
extern u8 g_d_GameSettings[];
extern u8 lbl_3_common_bss_37400[];
extern void fn_3_161588(int, s16);
extern u8 g_FieldingLogic[];
extern int g_Strikes[];
extern u8 g_Practice[];
extern u8 g_RunningLogic[];
extern u8 g_Minigame[];

// .text:0x0007D79C size:0x184 mapped:0x806BC830
void fn_3_7D79C(void) {
    return;
}

// .text:0x0007D920 size:0xBC mapped:0x806BC9B4
void fn_3_7D920(int i) {
    u8* r = g_Runners + i * 0x154;
    s8 k = *(s8*)(g_Minigame + i + 0x18FC);
    if (g_Minigame[k + 0x1B15] == 2) {
        if (g_Minigame[0x1B19] == 0) {
            g_Minigame[k + 0x1B15] = 3;
            *(s16*)(r + 0x108) = 0;
        }
        return;
    }
    if (*(s16*)(r + 0x108) < lbl_3_data_21904[1]) {
        *(f32*)(r + 0x0) += *(f32*)(r + 0x18);
        *(f32*)(r + 0x8) += *(f32*)(r + 0x20);
    } else {
        g_Minigame[k + 0x1B15] = 2;
    }
    if (*(s16*)(r + 0x108) < 0x7FFE) {
        *(s16*)(r + 0x108) += 1;
    } else {
        *(s16*)(r + 0x108) = 0x7FFF;
    }
}

// .text:0x0007D9DC size:0x154 mapped:0x806BCA70
void fn_3_7D9DC(void) {
    return;
}

// .text:0x0007DB30 size:0x1F4 mapped:0x806BCBC4
void fn_3_7DB30(int a) {
    return;
}

// .text:0x0007DD24 size:0x48 mapped:0x806BCDB8
void fn_3_7DD24(int a) {
    if (g_GameLogic[0x11E] == 2 && g_Minigame[0x190B] == 0) {
        fn_3_7DB30(a);
    }
}

// .text:0x0007DD6C size:0x550 mapped:0x806BCE00
void fn_3_7DD6C(void) {
    return;
}

// .text:0x0007E2BC size:0x7AC mapped:0x806BD350
void fn_3_7E2BC(void) {
    return;
}

// .text:0x0007EA68 size:0x16C mapped:0x806BDAFC
void fn_3_7EA68(void) {
    return;
}

// .text:0x0007EBD4 size:0x128 mapped:0x806BDC68
void fn_3_7EBD4(int i) {
    return;
}

// .text:0x0007ECFC size:0x5DC mapped:0x806BDD90
void fn_3_7ECFC(int i) {
    return;
}

// .text:0x0007F2D8 size:0x1BC mapped:0x806BE36C
void fn_3_7F2D8(void) {
    return;
}

// .text:0x0007F494 size:0x530 mapped:0x806BE528
void fn_3_7F494(int i) {
    return;
}

// .text:0x0007F9C4 size:0xB4 mapped:0x806BEA58
void fn_3_7F9C4(int i) {
    u8* r = g_Runners + i * 0x154;
    if (r[0x145] != 0) {
        r[0x13E] = 0;
        r[0x13A] = 0;
        return;
    }
    fn_3_7ECFC(i);
    fn_3_7F494(i);
    if (g_GameLogic[0x121] != 6) {
        if (i == 0 && r[0x126] == 1) {
            fn_3_7F2D8();
        } else if (r[0x13E] == 1) {
            r[0x13E] = 0;
        }
        fn_3_7EBD4(i);
    }
}

// .text:0x0007FA78 size:0x318 mapped:0x806BEB0C
void fn_3_7FA78(void) {
    return;
}

// .text:0x0007FD90 size:0x118 mapped:0x806BEE24
void fn_3_7FD90(void) {
    return;
}

// .text:0x0007FEA8 size:0x2C mapped:0x806BEF3C
void fn_3_7FEA8(s32 i, s32 v) {
    u8* r = g_Runners + i * 0x154;
    if (*(s16*)(r + 0xE0) < 0) {
        return;
    }
    if (v == 0) {
        return;
    }
    r[0x135] = v;
}

// .text:0x0007FED4 size:0xFC mapped:0x806BEF68
void fn_3_7FED4(void) {
    return;
}

// .text:0x0007FFD0 size:0x58 mapped:0x806BF064
#pragma fp_contract off
void fn_3_7FFD0(f32* out, int a, int b, f32 t) {
    f32* T = lbl_3_data_4A34;
    f32 d[2];
    d[0] = T[b * 2] - T[a * 2];
    d[1] = T[b * 2 + 1] - T[a * 2 + 1];
    d[0] *= t;
    d[1] *= t;
    out[0] = d[0] + T[a * 2];
    out[2] = d[1] + T[a * 2 + 1];
    out[1] = 0.0f;
}
#pragma fp_contract on

// .text:0x00080028 size:0x109C mapped:0x806BF0BC
void fn_3_80028(void) {
    return;
}

// .text:0x000810C4 size:0xCC mapped:0x806C0158
void fn_3_810C4(void) {
    return;
}

// .text:0x00081190 size:0x928 mapped:0x806C0224
void fn_3_81190(void) {
    return;
}

// .text:0x00081AB8 size:0x34 mapped:0x806C0B4C
void fn_3_81AB8(int i) {
    u8* r = g_Runners + i * 0x154;
    r[0x137] = 2;
    r[0x136] = 2;
    *(f32*)(r + 0x84) = lbl_3_rodata_1498;
    *(f32*)(r + 0xA4) = lbl_3_rodata_1498;
    *(f32*)(r + 0xB0) = lbl_3_rodata_1498;
}

// .text:0x00081AEC size:0xDC mapped:0x806C0B80
void fn_3_81AEC(int i) {
    u8* r = g_Runners + i * 0x154;
    s16 n;
    f32 v;
    if (*(s16*)(r + 0x10C) < 0x7FFE) {
        *(s16*)(r + 0x10C) = *(s16*)(r + 0x10C) + 1;
    } else {
        *(s16*)(r + 0x10C) = 0x7FFF;
    }
    n = *(s16*)(r + 0x10E);
    if (n <= 0) {
        r[0x133] = 2;
        *(f32*)(r + 0xA4) = lbl_3_rodata_1498;
    } else {
        v = *(f32*)(r + 0xBC) + *(f32*)(r + 0x54);
        v -= *(f32*)(r + 0x68);
        v /= (f32)n;
        *(f32*)(r + 0xA4) = v;
        *(f32*)(r + 0x68) = *(f32*)(r + 0x68) + v;
        *(f32*)(r + 0x64) = (f32)r[0x124] + *(f32*)(r + 0x68);
        *(s16*)(r + 0x10E) = *(s16*)(r + 0x10E) - 1;
    }
}

// .text:0x00081BC8 size:0x2E4 mapped:0x806C0C5C
void fn_3_81BC8(void) {
    return;
}

// .text:0x00081EAC size:0x508 mapped:0x806C0F40
void fn_3_81EAC(void) {
    return;
}

// .text:0x000823B4 size:0x2BC mapped:0x806C1448
void fn_3_823B4(void) {
    return;
}

// .text:0x00082670 size:0x910 mapped:0x806C1704
void fn_3_82670(void) {
    return;
}

// .text:0x00082F80 size:0xFC mapped:0x806C2014
void fn_3_82F80(void) {
    return;
}

// .text:0x0008307C size:0x370 mapped:0x806C2110
void fn_3_8307C(void) {
    return;
}

// .text:0x000833EC size:0x1C4 mapped:0x806C2480
void fn_3_833EC(void) {
    return;
}

// .text:0x000835B0 size:0x164 mapped:0x806C2644
void fn_3_835B0(void) {
    return;
}

// .text:0x00083714 size:0xAAC mapped:0x806C27A8
void fn_3_83714(void) {
    return;
}

// .text:0x000841C0 size:0x124 mapped:0x806C3254
void fn_3_841C0(void) {
    return;
}

// .text:0x000842E4 size:0x3E4 mapped:0x806C3378
void fn_3_842E4(void) {
    return;
}

// .text:0x000846C8 size:0x408 mapped:0x806C375C
void fn_3_846C8(void) {
    return;
}

// .text:0x00084AD0 size:0x5A4 mapped:0x806C3B64
void fn_3_84AD0(void) {
    return;
}

// .text:0x00085074 size:0x6D0 mapped:0x806C4108
void fn_3_85074(void) {
    return;
}

// .text:0x00085744 size:0xFC mapped:0x806C47D8
void fn_3_85744(void) {
    return;
}

// .text:0x00085840 size:0x230 mapped:0x806C48D4
void fn_3_85840(void) {
    return;
}

// .text:0x00085A70 size:0x1D4 mapped:0x806C4B04
void fn_3_85A70(void) {
    return;
}

// .text:0x00085C44 size:0x6C mapped:0x806C4CD8
void fn_3_85C44(s32 i, s32 d) {
    u8* r = g_Runners + i * 0x154;
    if (r[0x13E] == 1 && r[0x140] >= 2 && d != 1) {
        return;
    }
    if (d == -1) {
        if (r[0x124] == *(s16*)(r + 0xE6)) {
            d = 0;
        }
    }
    fn_3_85EF4(i, d);
}

// .text:0x00085CB0 size:0x244 mapped:0x806C4D44
void fn_3_85CB0(void) {
    return;
}

// .text:0x00085EF4 size:0x158 mapped:0x806C4F88
void fn_3_85EF4(s32 i, s32 d) {
    return;
}

// .text:0x0008604C size:0xCC mapped:0x806C50E0
void fn_3_8604C(void) {
    return;
}

// .text:0x00086118 size:0x684 mapped:0x806C51AC
void fn_3_86118(void) {
    return;
}

// .text:0x0008679C size:0x660 mapped:0x806C5830
void fn_3_8679C(void) {
    return;
}

// .text:0x00086DFC size:0xFC mapped:0x806C5E90
void fn_3_86DFC(void) {
    u8* r = g_Runners;
    int i;
    for (i = 0; i < 4; i++) {
        if (r[0x123] != 0) {
            if (g_FieldingLogic[0x107] == 1 && r[0x14E] != 0 && *(s16*)(r + 0xE0) >= 0) {
                r[0x135] = 1;
            }
            r[0x14E] = 0;
        }
        r += 0x154;
    }
}

// .text:0x00086EF8 size:0x1B4 mapped:0x806C5F8C
void fn_3_86EF8(void) {
    return;
}

// .text:0x000870AC size:0x110 mapped:0x806C6140
void fn_3_870AC(void) {
    u8* r;
    g_Runners[0x130] = 0;
    g_Runners[0x284] = 0;
    g_Runners[0x3D8] = 0;
    g_Runners[0x52C] = 0;
    if ((g_FieldingLogic[0x111] == 2 || g_FieldingLogic[0x111] == 4) && *(s16*)(g_FieldingLogic + 0xE8) >= 0) {
        r = g_Runners + *(s16*)(g_FieldingLogic + 0xE8) * 0x154;
        if (r[0x123] == 1) {
            r[0x130] = 1;
        }
        if (*(s16*)(g_FieldingLogic + 0xEC) < 5 && r[0x13A] != 0) {
            r[0x130] = 2;
        }
        if (g_d_GameSettings[8] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x40) == *(s32*)(g_GameLogic + 8)) {
            {
                u8* f;
                f = g_Fielders;
                f += *(s16*)(g_Ball + 0x1B78) * 0x268;
                fn_3_161588(6, *(s16*)(f + 0x178));
            }
        }
    }
}

// .text:0x000871BC size:0x110 mapped:0x806C6250
void fn_3_871BC(void) {
    return;
}

// .text:0x000872CC size:0x158 mapped:0x806C6360
void fn_3_872CC(void) {
    return;
}

// .text:0x00087424 size:0x3F8 mapped:0x806C64B8
void fn_3_87424(void) {
    return;
}

// .text:0x0008781C size:0x2CC mapped:0x806C68B0
void fn_3_8781C(void) {
    return;
}

// .text:0x00087AE8 size:0x1E0 mapped:0x806C6B7C
void fn_3_87AE8(void) {
    return;
}

// .text:0x00087CC8 size:0x1B8 mapped:0x806C6D5C
void fn_3_87CC8(void) {
    return;
}

// .text:0x00087E80 size:0x3A8 mapped:0x806C6F14
void fn_3_87E80(void) {
    return;
}

// .text:0x00088228 size:0x1E0 mapped:0x806C72BC
void fn_3_88228(void) {
    return;
}

// .text:0x00088408 size:0x5F4 mapped:0x806C749C
void fn_3_88408(void) {
    return;
}

// .text:0x000889FC size:0x11C mapped:0x806C7A90
void fn_3_889FC(void) {
    return;
}

// .text:0x00088B18 size:0x10C mapped:0x806C7BAC
void fn_3_88B18(void) {
    return;
}

// .text:0x00088C24 size:0x164 mapped:0x806C7CB8
void fn_3_88C24(void) {
    return;
}

// .text:0x00088D88 size:0x210 mapped:0x806C7E1C
void fn_3_88D88(void) {
    return;
}

// .text:0x00088F98 size:0x90 mapped:0x806C802C
typedef struct { u8 b[0x154]; } RunnerT;
void fn_3_88F98(void) {
    int i;
    RunnerT* rs = (RunnerT*)g_Runners;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            fn_3_85EF4(i, 1);
        }
        if (i == 0) {
            rs[i].b[0x12A] = 1;
        } else {
            rs[i].b[0x12A] = 0;
            if (g_Strikes[3] < 2) {
                rs[i].b[0x128] = 1;
            } else {
                rs[i].b[0x128] = 0;
            }
        }
    }
}

// .text:0x00089028 size:0xF4 mapped:0x806C80BC
void fn_3_89028(void) {
    return;
}

// .text:0x0008911C size:0x20 mapped:0x806C81B0
void fn_3_8911C(void) {
    g_Runners[0x133] = 0;
    g_Runners[0x287] = 0;
    g_Runners[0x3DB] = 0;
    g_Runners[0x52F] = 0;
}

// .text:0x0008913C size:0x728 mapped:0x806C81D0
void fn_3_8913C(void) {
    return;
}

// .text:0x00089864 size:0x58 mapped:0x806C88F8
void fn_3_89864(s32 i, s32 d) {
    u8* r = g_Runners + i * 0x154;
    r[0x125] += d;
    r[0x126] = (r[0x125] + 1) & 3;
    if (r[0x125] < 4) {
        return;
    }
    r[0x123] = 3;
    *(s16*)(g_Scores + 0x9C) += 1;
}

// .text:0x000898BC size:0x58 mapped:0x806C8950
void fn_3_898BC(s32 i, s32 j) {
    u8* r = g_Runners + i * 0x154;
    *(s16*)(r + 0xE0) = j;
    r[0x11C] = inMemRoster[*(s32*)(g_GameLogic + 4) * 0x5A0 + j * 0xA0 + 0x26];
    if (r[0x11C] == 2) {
        r[0x11C] = 0;
    }
}

// .text:0x00089914 size:0xA8 mapped:0x806C89A8
void fn_3_89914(s32 a, s32 b) {
    u8* ra = g_Runners + a * 0x154;
    u8* rb = g_Runners + b * 0x154;
    if (a >= 0 && a <= 3) {
        if (*(u8*)(g_GameLogic + 0x121) == 0xF && a == 0) {
            *(s16*)(rb + 0xE0) = *(u8*)(g_Practice + 0x1EF);
        } else {
            *(s16*)(rb + 0xE0) = *(s16*)(ra + 0xE0);
            *(u8*)(rb + 0x11C) = *(u8*)(ra + 0x11C);
            *(u8*)(rb + 0x131) = *(u8*)(ra + 0x131);
            *(s16*)(rb + 0xFC) = *(s16*)(ra + 0xFC);
        }
        { u8* q = g_RunningLogic; q += a * 2; *(s16*)(q + 6) = b; }
        return;
    }
    *(s16*)(rb + 0xE0) = -1;
    *(u8*)(rb + 0x131) = 0;
    *(s16*)(rb + 0xFC) = -1;
}

// .text:0x000899BC size:0x81C mapped:0x806C8A50
void fn_3_899BC(void) {
    return;
}

// .text:0x0008A1D8 size:0x178 mapped:0x806C926C
void fn_3_8A1D8(void) {
    return;
}

// .text:0x0008A350 size:0x178 mapped:0x806C93E4
void fn_3_8A350(void) {
    return;
}

// .text:0x0008A4C8 size:0x1C mapped:0x806C955C

void fn_3_8A4C8(void) {
    *(f32*)g_Runners = *(f32*)g_Batter;
    *(f32*)(g_Runners + 8) = *(f32*)(g_Batter + 4);
}

// .text:0x0008A4E4 size:0xC0 mapped:0x806C9578
void fn_3_8A4E4(void) {
    return;
}

// .text:0x0008A5A4 size:0x74 mapped:0x806C9638
void fn_3_8A5A4(void) {
    s8 i;
    for (i = 0; i < 4; i++) {
        u8* r = g_Runners + i * 0x154;
        *(s16*)(r + 0xE0) = -1;
        r[0x121] = 10;
        r[0x122] = 30;
        *(f32*)(r + 0xBC) = lbl_3_rodata_1498;
        r[0x14C] = 0;
    }
}

// .text:0x0008A618 size:0x19C mapped:0x806C96AC
void fn_3_8A618(void) {
    return;
}

// .text:0x0008A7B4 size:0x1A4 mapped:0x806C9848
void fn_3_8A7B4(void) {
    return;
}

// .text:0x0008A958 size:0x73C mapped:0x806C99EC
void fn_3_8A958(void) {
    return;
}

