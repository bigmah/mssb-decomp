#include "game/rep_A00.h"
#include "header_rep_data.h"

extern u8* lbl_3_common_bss_1323C;
extern void changeScene(s32, s32);
extern u8 g_GameLogic[];
extern u8 g_Scores[];
extern u8 g_Batter[];
extern u8 g_Fielders[];
extern void fn_80052798(s32);
extern u8 lbl_3_data_2398[];
extern u8 lbl_8036E548[];
extern u8* lbl_803CC1B8;
extern u8 lbl_803C5090[];
extern u8 lbl_3_rodata_A50[];
extern s32 lbl_3_bss_A0;
extern s32 lbl_3_bss_9C;
extern u8* g_pCamera[];
extern void fn_800B0A14_removeQueue();

// .text:0x00021C90 size:0x154 mapped:0x80660D24
void fn_3_21C90(void) {
    u8* p = lbl_803CC1B8;
    u8* q;
    u8* cam;
    switch (lbl_3_bss_A0) {
    case 0:
        *(u16*)(p + 0x1E) = 0;
        *(u16*)(p + 0x20) = 0xFF;
        lbl_803C5090[0x1D] = 9;
        *(f32*)lbl_803C5090 = 1.0f;
        *(u16*)(lbl_803C5090 + 0x14) = 0x1C0;
        lbl_803C5090[0x19] = 1;
        lbl_803C5090[0x18] = 0;
        lbl_803C5090[0x1A] = 0xFF;
        lbl_803C5090[0x1B] = 0xFF;
        lbl_803C5090[0x1C] = 0xFF;
        lbl_803C5090[0x17] = *(u16*)(p + 0x20);
        lbl_3_bss_A0 += 1;
        return;
    case 1:
        lbl_803C5090[0x1D] = 8;
        *(f32*)lbl_803C5090 = *(f32*)lbl_3_rodata_A50;
        *(u16*)(lbl_803C5090 + 0x14) = 0x1C0;
        lbl_803C5090[0x19] = 1;
        lbl_803C5090[0x18] = 0;
        lbl_803C5090[0x1A] = 0xFF;
        lbl_803C5090[0x1B] = 0xFF;
        lbl_803C5090[0x1C] = 0xFF;
        lbl_803C5090[0x17] = *(u16*)(p + 0x20);
        *(u16*)(p + 0x1E) = *(u16*)(p + 0x1E) + 1;
        if (*(u16*)(g_pCamera[0] + 0xAAC) <= *(u16*)(p + 0x1E)) {
            *(u16*)(g_pCamera[0] + 0xAA8) = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)();
            lbl_3_bss_A0 = 0;
            return;
        }
        *(u16*)(p + 0x20) = 0xFF - (*(u16*)(p + 0x1E) * 0xFF) / *(u16*)(g_pCamera[0] + 0xAAC);
        return;
    case 2:
    default:
        return;
    }
}

// .text:0x00021DE4 size:0x130 mapped:0x80660E78
void fn_3_21DE4(void) {
    u8* p = lbl_803CC1B8;
    switch (lbl_3_bss_9C) {
    case 0:
        *(u16*)(p + 0x1E) = 0;
        *(u16*)(p + 0x20) = 0xFF;
        lbl_803C5090[0x1D] = 9;
        *(f32*)lbl_803C5090 = 1.0f;
        *(u16*)(lbl_803C5090 + 0x14) = 0x1C0;
        lbl_803C5090[0x19] = 1;
        lbl_803C5090[0x18] = 0;
        lbl_803C5090[0x1A] = 0xFF;
        lbl_803C5090[0x1B] = 0xFF;
        lbl_803C5090[0x1C] = 0xFF;
        lbl_803C5090[0x17] = 0xFF;
        lbl_3_bss_9C += 1;
        return;
    case 1:
        lbl_803C5090[0x1D] = 8;
        *(f32*)lbl_803C5090 = *(f32*)lbl_3_rodata_A50;
        *(u16*)(lbl_803C5090 + 0x14) = 0x1C0;
        lbl_803C5090[0x19] = 1;
        lbl_803C5090[0x18] = 0;
        lbl_803C5090[0x1A] = 0xFF;
        lbl_803C5090[0x1B] = 0xFF;
        lbl_803C5090[0x1C] = 0xFF;
        lbl_803C5090[0x17] = 0xFF;
        *(u16*)(p + 0x1E) = *(u16*)(p + 0x1E) + 1;
        if (*(u16*)(g_pCamera[0] + 0xAAE) <= *(u16*)(p + 0x1E)) {
            *(u16*)(g_pCamera[0] + 0xAAA) = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)();
            lbl_3_bss_9C = 0;
        }
        return;
     case 2:
    default:
        return;
    }
}

// .text:0x00021F14 size:0x828 mapped:0x80660FA8
void fn_3_21F14(void) {
    return;
}

// .text:0x0002273C size:0xE0 mapped:0x806617D0
s32 fn_3_2273C(void) {
    u8* f = g_Fielders;
    u8** r = (u8**)lbl_8036E548;
    u8* p;
    s32 i;
    for (i = 0; i < 9; i++) {
        if (f[0x218] == 0) {
            p = r[0x2C50 / 4];
            if (p == 0) {
                return 1;
            }
            if (*(s16*)(p + 0x68) == 0) {
                return 1;
            }
        }
        f += 0x268;
        r++;
    }
    return 0;
}

// .text:0x0002281C size:0x34 mapped:0x806618B0
extern u8 lbl_8036E548[];

s32 fn_3_2281C(s32 i) {
    u8** arr = (u8**)(lbl_8036E548 + 0x2C50);
    u8* p = arr[i];
    if (p == NULL) {
        return 1;
    }
    return *(s16*)(p + 0x68) == 0;
}

// .text:0x00022850 size:0xF4 mapped:0x806618E4
void fn_3_22850(void) {
    s32 i;
    for (i = 0; i < 0x21; i++) {
        *(s32*)(lbl_3_data_2398 + i * 0x40 + 0x38) = 0;
        *(s32*)(lbl_3_data_2398 + i * 0x40 + 0x3C) = 0;
    }
    (&lbl_3_common_bss_1323C)[0][0x27B] = 0;
}

// .text:0x00022944 size:0x4 mapped:0x806619D8
void fn_3_22944(void) {
    return;
}

// .text:0x00022948 size:0xD8 mapped:0x806619DC
void fn_3_22948(void) {
    s32 i;
    for (i = 0; i < 0x21; i++) {
        *(s32*)(lbl_3_data_2398 + i * 0x40 + 0x34) = 0;
        *(s32*)(lbl_3_data_2398 + i * 0x40 + 0x38) = 0;
        *(s32*)(lbl_3_data_2398 + i * 0x40 + 0x3C) = 0;
    }
    (&lbl_3_common_bss_1323C)[0][0x27B] = 0;
}

// .text:0x00022A20 size:0x9C mapped:0x80661AB4
s32 fn_3_22A20(void) {
    s16 x; s16 y; s16* sc;
    if (g_Batter[0x78] != 0) {
        sc = (s16*)(g_Scores + 4); x = sc[*(s32*)(g_GameLogic + 0xC) * 0x13]; y = sc[*(s32*)(g_GameLogic + 0x10) * 0x13];
        return x >= y;
    }
    sc = (s16*)(g_Scores + 4); x = sc[*(s32*)(g_GameLogic + 0xC) * 0x13]; y = sc[*(s32*)(g_GameLogic + 0x10) * 0x13];
    return (u32)__cntlzw(x >= y) >> 5;
}

// .text:0x00022ABC size:0x154 mapped:0x80661B50
void fn_3_22ABC(void) {
    return;
}

// .text:0x00022C10 size:0x10 mapped:0x80661CA4
void fn_3_22C10(void) {
    int i;
    for (i = 13; i != 0; i--) {
    }
}

// .text:0x00022C20 size:0x4B4 mapped:0x80661CB4
void fn_3_22C20(void) {
    return;
}

// .text:0x000230D4 size:0x3E8 mapped:0x80662168
void fn_3_230D4(void) {
    return;
}

// .text:0x000234BC size:0x3D4 mapped:0x80662550
void fn_3_234BC(void) {
    return;
}

// .text:0x00023890 size:0x45C mapped:0x80662924
void fn_3_23890(void) {
    return;
}

// .text:0x00023CEC size:0x40C mapped:0x80662D80
void fn_3_23CEC(void) {
    return;
}

// .text:0x000240F8 size:0x4A0 mapped:0x8066318C
void fn_3_240F8(void) {
    return;
}

// .text:0x00024598 size:0x98 mapped:0x8066362C
void fn_3_24598(void) {
    if (*(s16*)(lbl_3_common_bss_1323C + 0x23C) < 0x7FFE) {
        *(s16*)(lbl_3_common_bss_1323C + 0x23C) += 1;
    } else {
        *(s16*)(lbl_3_common_bss_1323C + 0x23C) = 0x7FFF;
    }
    if (*(s16*)(lbl_3_common_bss_1323C + 0x23C) == *(s16*)(lbl_3_common_bss_1323C + 0x23E) - 7) {
        changeScene(3, 6);
    }
    if (*(s16*)(lbl_3_common_bss_1323C + 0x23C) == *(s16*)(lbl_3_common_bss_1323C + 0x23E)) {
        g_GameLogic[0x125] += 1;
    }
}

// .text:0x00024630 size:0xD8 mapped:0x806636C4
void fn_3_24630(void) {
    s32 i;
    fn_80052798(1);
    for (i = 0; i < 13; i++) {
        (&lbl_3_common_bss_1323C)[0][0x261 + i] = 0;
    }
    (&lbl_3_common_bss_1323C)[0][0x25C] = 0;
}

// .text:0x00024708 size:0x2E0 mapped:0x8066379C
void fn_3_24708(void) {
    return;
}

