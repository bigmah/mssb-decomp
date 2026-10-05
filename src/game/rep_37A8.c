#include "game/rep_37A8.h"
#include "header_rep_data.h"
#pragma dont_inline on

extern u8 g_Minigame[];

#include "static/UnknownHomes_Static.h"
extern void fn_3_141C8C(void);
extern u8 lbl_3_bss_B7C1[];
extern void fn_800B993C(void);
extern u8 g_GameLogic[];
extern u8 lbl_3_data_21278[];
extern void fn_3_10F550(s32, u8);
extern void fn_3_5A6D4(s32);
extern void changeScene(s32, s32);
extern void* memset(void*, s32, u32);
extern s16 RandomInt_Game_Range(s16, s16);
extern s16 lbl_3_data_21EAC[];
extern u8 lbl_80366158[];
extern s32 lbl_3_bss_B7E4;
extern u8 lbl_3_bss_B800[];
extern s8 lbl_3_data_266A4;
extern void DCFlushRange(void*, u32);

// .text:0x00141C44 size:0x48
void fn_3_141C44(void) {
    lbl_3_bss_B7C1[0] += 1;
    if (lbl_3_bss_B7C1[0] >= 6) {
        lbl_3_bss_B7C1[0] = 0;
        fn_800B993C();
    }
}

// .text:0x00141C8C size:0x2A4 mapped:0x80780D20
void fn_3_141C8C(void) {
    return;
}

// .text:0x00141F30 size:0x100 mapped:0x80780FC4
void fn_3_141F30(void) {
    s32 v;
    u8* p;
    s32 n;
    s32 i;
    lbl_3_bss_B7E4 = lbl_3_bss_B7E4 + (lbl_80366158[0x28] == 0);
    if (!(lbl_3_bss_B7E4 & 1)) {
        p = lbl_3_bss_B800;
        v = p[0];
        v += lbl_3_data_266A4 * 2;
        if (v > 0xFF) {
            v = 0xFF;
        } else if (v < 0) {
            v = 0;
        }
        for (i = 16; i != 0; i--) {
            *p = v;
            p += 2;
        }
        DCFlushRange(lbl_3_bss_B800, 0x40);
        n = v + lbl_3_data_266A4 * 2;
        if (n > 0xFF || n < 0) {
            lbl_3_data_266A4 *= -1;
        }
    }
}

// .text:0x00142030 size:0x58 mapped:0x807810C4
s32 fn_3_142030(s32 a, s32 b, s32 c) {
    return (b / 4) * 4 * c + (a / 4) * 4 * 4 + (b % 4) * 4 + a % 4;
}

// .text:0x00142088 size:0x1D4 mapped:0x8078111C
void fn_3_142088(void) {
    return;
}

// .text:0x0014225C size:0x28 mapped:0x807812F0
void fn_3_14225C(void) {
    fn_800B9948(fn_3_141C8C);
}

// .text:0x00142284 size:0x2EC mapped:0x80781318
void fn_3_142284(void) {
    return;
}

// .text:0x00142570 size:0x380 mapped:0x80781604
void fn_3_142570(void) {
    return;
}

// .text:0x001428F0 size:0x328 mapped:0x80781984
void fn_3_1428F0(void) {
    return;
}

// .text:0x00142C18 size:0x90 mapped:0x80781CAC
void fn_3_142C18(void) {
    return;
}

// .text:0x00142CA8 size:0x10C mapped:0x80781D3C
typedef struct { u8 pad0[0x1890]; s16 a[4]; u8 pad1[0x1B58 - 0x1898]; u8 b[4][10]; } MgArr2;

void fn_3_142CA8(void) {
    MgArr2* m = (MgArr2*)g_Minigame;
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            m->a[i] += m->b[i][j];
            m->b[i][j] = 0;
        }
        g_Minigame[0x1B80 + i] = 0;
    }
}

// .text:0x00142DB4 size:0x31C mapped:0x80781E48
void fn_3_142DB4(void) {
    return;
}

// .text:0x001430D0 size:0x288 mapped:0x80782164
void fn_3_1430D0(void) {
    return;
}

// .text:0x00143358 size:0x3BC mapped:0x807823EC
void fn_3_143358(s32 i) {
    return;
}

// .text:0x00143714 size:0x5C mapped:0x807827A8
void fn_3_143714(void) {
    s32 i;
    for (i = 0; i < 0x28; i++) {
        if (g_Minigame[0xCE + i * 0x28] != 0) {
            fn_3_143358(i);
        }
    }
}

// .text:0x00143770 size:0x27C mapped:0x80782804
void fn_3_143770(void) {
    return;
}

// .text:0x001439EC size:0x5C0 mapped:0x80782A80
void fn_3_1439EC(void) {
    return;
}

// .text:0x00143FAC size:0x80 mapped:0x80783040
void fn_3_143FAC(void) {
    return;
}

// .text:0x0014402C size:0x210 mapped:0x807830C0
void fn_3_14402C(void) {
    return;
}

// .text:0x0014423C size:0x200 mapped:0x807832D0
void fn_3_14423C(void) {
    return;
}

// .text:0x0014443C size:0x2E0 mapped:0x807834D0
void fn_3_14443C(void) {
    return;
}

// .text:0x0014471C size:0x3C0 mapped:0x807837B0
void fn_3_14471C(void) {
    return;
}

// .text:0x00144ADC size:0x1DC mapped:0x80783B70
void fn_3_144ADC(void) {
    return;
}

// .text:0x00144CB8 size:0x704 mapped:0x80783D4C
void fn_3_144CB8(void) {
    return;
}

// .text:0x001453BC size:0x714 mapped:0x80784450
void fn_3_1453BC(void) {
    return;
}

// .text:0x00145AD0 size:0xC8 mapped:0x80784B64
void fn_3_145AD0(void) {
    return;
}

// .text:0x00145B98 size:0x320 mapped:0x80784C2C
void fn_3_145B98(void) {
    return;
}

// .text:0x00145EB8 size:0x13C mapped:0x80784F4C
void fn_3_145EB8(void) {
    return;
}

// .text:0x00145FF4 size:0x1B0 mapped:0x80785088
void fn_3_145FF4(void) {
    return;
}

// .text:0x001461A4 size:0x264 mapped:0x80785238
void fn_3_1461A4(void) {
    return;
}

// .text:0x00146408 size:0x520 mapped:0x8078549C
void fn_3_146408(void) {
    return;
}

// .text:0x00146928 size:0xA4 mapped:0x807859BC
void fn_3_146928(void) {
    return;
}

// .text:0x001469CC size:0xC4 mapped:0x80785A60
void fn_3_1469CC(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        fn_3_10F550(2, lbl_3_data_21278[0]);
        changeScene(1, 6);
        *(s16*)(g_GameLogic + 0xFE) = 0;
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFE) > lbl_3_data_21278[0] + lbl_3_data_21278[1]) {
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        fn_3_5A6D4(0);
        break;
    }
}

// .text:0x00146A90 size:0x730 mapped:0x80785B24
void fn_3_146A90(void) {
    return;
}

