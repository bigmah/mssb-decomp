#include "game/rep_EA0.h"
#include "header_rep_data.h"

extern u8 lbl_8036E548[];
extern u8 g_Batter[];
extern u8 g_GameLogic[];
extern u8 g_Practice[];
extern u8 g_Stats[];
extern u8 g_d_GameSettings[];
extern f32 lbl_3_data_6848[];
extern u8 lbl_3_bss_200[];
extern f32 lbl_3_rodata_F20;
extern f32 lbl_3_rodata_F24;
extern u8 lbl_3_data_6880[];
extern s32 lbl_3_bss_169C;
typedef struct { s32 a; f32 b; f32 c; s32 d; } E6880;
extern u8 lbl_3_common_bss_32724[];

// .text:0x0006750C size:0xAC mapped:0x806A65A0
void fn_3_6750C(s32 base) {
    E6880* e = (E6880*)(lbl_3_data_6880 + 0x10);
    s32 i;
    for (i = 0; i < 11; i++, e++) {
        e->a = base + (e->a << 5) + 4;
        if (lbl_3_rodata_F20 == e->c) {
            e->c = lbl_3_rodata_F24;
        } else {
            e->c = e->c / e->b;
        }
        e->d = e->d * 60 / 100;
        if (e->d < 2) {
            e->d = 2;
        }
    }
    lbl_3_bss_169C = 0;
}

// .text:0x000675B8 size:0x68 mapped:0x806A664C
void fn_3_675B8(u16 n) {
    u8* b = lbl_3_bss_200;
    if (n == 0) {
        lbl_3_common_bss_32724[0xCC] = 0;
        *(f32*)(b + 0x14A8) = lbl_3_rodata_F20;
        return;
    }
    *(s32*)(b + 0xC) = n;
    *(f32*)(b + 0x14A4) = *(f32*)(b + 0x14A8) / (f32)n;
}

// .text:0x00067620 size:0x298 mapped:0x806A66B4
void fn_3_67620(void) {
    return;
}

// .text:0x000678B8 size:0x190 mapped:0x806A694C
void fn_3_678B8(void) {
    return;
}

// .text:0x00067A48 size:0x1EC mapped:0x806A6ADC
void fn_3_67A48(void) {
    return;
}

// .text:0x00067C34 size:0x2BC mapped:0x806A6CC8
void fn_3_67C34(void) {
    return;
}

// .text:0x00067EF0 size:0x700 mapped:0x806A6F84
void fn_3_67EF0(void) {
    return;
}

// .text:0x000685F0 size:0x5C4 mapped:0x806A7684
void fn_3_685F0(void) {
    return;
}

// .text:0x00068BB4 size:0x548 mapped:0x806A7C48
void fn_3_68BB4(void) {
    return;
}

// .text:0x000690FC size:0x70 mapped:0x806A8190
void fn_3_690FC(void) {
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x26] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x4E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x76] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x9E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0xEE] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x116] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x13E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x166] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x18E] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x1B6] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x206] = 0;
    (*(u8**)(lbl_8036E548 + 0x2D90))[0x22E] = 0;
}

// .text:0x0006916C size:0x18 mapped:0x806A8200
extern u8 lbl_3_common_bss_32724[];

void fn_3_6916C(void) {
    lbl_3_common_bss_32724[0xCB] = 0;
    lbl_3_common_bss_32724[0xCC] = 0;
}

// .text:0x00069184 size:0x15C mapped:0x806A8218
void fn_3_69184(void) {
    u8* p;
    if (g_Batter[0x8A] == 1) {
        p = *(u8**)(lbl_8036E548 + 0x2D90) + 0xF0;
    } else {
        p = *(u8**)(lbl_8036E548 + 0x2D90) + 0xC8;
    }
    p[0x26] = 0;
    if (g_d_GameSettings[7] == 2) {
        if (g_GameLogic[0x121] == 0xA) {
            return;
        }
        if (g_Practice[0x194] != 4 && g_Practice[0x193] != 1) {
            return;
        }
    } else if (g_Batter[0x7A] == 0) {
        return;
    }
    if (g_Stats[0x36] != 0) {
        return;
    }
    if (g_GameLogic[0x11E] != 0 && g_GameLogic[0x11E] != 1) {
        return;
    }
    if (g_GameLogic[0x120] != 1) {
        return;
    }
    p[0x26] = 1;
    if (g_Batter[0x7B] != 0) {
        *(f32*)(p + 4) = -*(f32*)(g_Batter + 0x4C);
        *(f32*)(p + 0x14) = 3.1415927f;
    } else {
        *(f32*)(p + 4) = *(f32*)(g_Batter + 0x4C);
        *(f32*)(p + 0x14) = 0.0f;
    }
    *(f32*)(p + 0xC) = *(f32*)(g_Batter + 0x54) + lbl_3_data_6848[1];
    *(f32*)(p + 8) = lbl_3_data_6848[0];
}

// .text:0x000692E0 size:0x318 mapped:0x806A8374
void fn_3_692E0(void) {
    return;
}

// .text:0x000695F8 size:0x1D4 mapped:0x806A868C
void fn_3_695F8(void) {
    return;
}

// .text:0x000697CC size:0x994 mapped:0x806A8860
void fn_3_697CC(void) {
    return;
}

