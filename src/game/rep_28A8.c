#include "game/rep_28A8.h"
#include "header_rep_data.h"

extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void setDefaultInMemBatter(void);
extern void fn_3_58870(void);
extern void fn_3_1DEB8(void);
extern void fn_3_BF1AC(void);
extern void Set_803cb848(s32);
extern void fn_3_BF158(void);
extern void fn_3_AFD80(s32);
extern void fn_3_5A6D4(s32);
extern void fn_3_2EA24(void);
extern void fn_3_2E87C(void);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern void fn_3_1DD48(void*);
extern struct { u8 pad[0xC]; s16 n; } lbl_3_common_bss_34C90;
extern u8 lbl_803CBC3C;
extern u8 g_Minigame[];
extern u8 g_Ball[];
extern u8 g_Fielders[];
extern s32 fn_3_E5924(void);
extern void fn_3_59918(s32, s32);
extern void fn_3_A0F0(void);
extern u8 g_GameLogic[];
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];

// .text:0x000D9EA0 size:0x7A0 mapped:0x80718F34
void fn_3_D9EA0(void) {
    return;
}

// .text:0x000DA640 size:0x1F4 mapped:0x807196D4
void fn_3_DA640(void) {
    return;
}

// .text:0x000DA834 size:0x1A0C mapped:0x807198C8
void fn_3_DA834(void) {
    return;
}

// .text:0x000DC240 size:0x140 mapped:0x8071B2D4
void fn_3_DC240(void) {
    g_Minigame[0x1920] = g_Minigame[0x19C9];
    if (fn_3_E5924() != 0) {
        if (g_Minigame[0x19CF] == 0) {
            g_Minigame[0x1920] = 0xC;
        }
        if (g_Minigame[0x19CF] > 0x3C) {
            g_Minigame[0x19CE] = 1;
            return;
        }
        if (g_Minigame[0x19CF] < 0xFE) {
            g_Minigame[0x19CF] = g_Minigame[0x19CF] + 1;
            return;
        }
        g_Minigame[0x19CF] = 0xFF;
        return;
    }
    if (g_Minigame[0x1920] == 2 || g_Ball[0x1BD3] != 0) {
        if (g_Ball[0x1BD3] == 0) {
            fn_3_59918(1, 0);
        }
        g_Minigame[0x19C6] = g_Minigame[0x1904];
        if (*(s16*)(g_Ball + 0x1B78) >= 0) {
            g_Minigame[0x19C6] = g_Fielders[*(s16*)(g_Ball + 0x1B78) * 0x268 + 0x20D];
        }
    } else {
        u8 st = g_Minigame[0x1920];
        if (st == 1) {
            fn_3_A0F0();
        } else if (st == 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x000DC380 size:0x224 mapped:0x8071B414
void fn_3_DC380(void) {
    return;
}

// .text:0x000DC5A4 size:0x144 mapped:0x8071B638
void fn_3_DC5A4(void) {
    return;
}

// .text:0x000DC6E8 size:0x380 mapped:0x8071B77C
void fn_3_DC6E8(void) {
    return;
}

// .text:0x000DCA68 size:0x218 mapped:0x8071BAFC
void fn_3_DCA68(void) {
    return;
}

// .text:0x000DCC80 size:0x250 mapped:0x8071BD14
void fn_3_DCC80(void) {
    return;
}

// .text:0x000DCED0 size:0x74 mapped:0x8071BF64
void fn_3_DCED0(void) {
    s16* p = &lbl_3_common_bss_34C90.n;
    if (*p < 0x7FFE) {
        *p += 1;
    } else {
        *p = 0x7FFF;
    }
    lbl_803CBC3C = 1;
    if (*p > 0x3C) {
        fn_3_AFD80(1);
        fn_3_5A6D4(0xB);
        return;
    }
    fn_3_2EA24();
}

// .text:0x000DCF44 size:0xBC mapped:0x8071BFD8
void fn_3_DCF44(void) {
    return;
}

// .text:0x000DD000 size:0x1A8 mapped:0x8071C094
void fn_3_DD000(void) {
    return;
}

// .text:0x000DD1A8 size:0x1D4 mapped:0x8071C23C
void fn_3_DD1A8(void) {
    return;
}

// .text:0x000DD37C size:0x80 mapped:0x8071C410
void fn_3_DD37C(void) {
    if (g_Minigame[0x19CE] != 0) {
        fn_3_FBD70();
        fn_3_FBD58();
    }
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    fn_3_1DD48(g_GameLogic);
    if (g_Minigame[0x1912] == 0) {
        fn_3_2E87C();
        fn_3_5A6D4(0);
        return;
    }
    fn_3_5A6D4(8);
}

// .text:0x000DD3FC size:0x5A8 mapped:0x8071C490
void fn_3_DD3FC(void) {
    return;
}

// .text:0x000DD9A4 size:0x3BC mapped:0x8071CA38
void fn_3_DD9A4(void) {
    return;
}

// .text:0x000DDD60 size:0x1BC mapped:0x8071CDF4
void fn_3_DDD60(void) {
    return;
}

// .text:0x000DDF1C size:0x84 mapped:0x8071CFB0
void fn_3_DDF1C(void) {
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    fn_3_F1DC();
    fn_3_751B4();
    setDefaultInMemBatter();
    fn_3_58870();
    fn_3_1DEB8();
    fn_3_BF1AC();
    Set_803cb848(1);
    fn_3_BF158();
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    g_GameLogic[0x126] = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
}

// .text:0x000DDFA0 size:0x368 mapped:0x8071D034
void fn_3_DDFA0(void) {
    return;
}

// .text:0x000DE308 size:0x1F4 mapped:0x8071D39C
void fn_3_DE308(void) {
    return;
}

// .text:0x000DE4FC size:0x114 mapped:0x8071D590
void fn_3_DE4FC(void) {
    s32 i;
    s32 j;
    s16 score;
    s32 rank;
    s32 n;

    g_Minigame[0x18E8] = 0;
    g_Minigame[0x18EC] = 0;
    g_Minigame[0x18E9] = 0;
    g_Minigame[0x18ED] = 0;
    g_Minigame[0x18EA] = 0;
    g_Minigame[0x18EE] = 0;
    g_Minigame[0x18EB] = 0;
    g_Minigame[0x18EF] = 0;
    for (i = 0; i < g_Minigame[0x1906]; i++) {
        rank = 1;
        score = *(s16*)(g_Minigame + 0x1890 + i * 2);
        for (j = 0; j < g_Minigame[0x1906]; j++) {
            if (*(s16*)(g_Minigame + 0x1890 + j * 2) > score) {
                rank++;
            }
        }
        g_Minigame[0x18E8 + i] = rank;
        g_Minigame[0x18EC + i] = rank;
    }
    for (n = 0; n < 4; n++) {
        if (g_Minigame[0x18E8 + n] > 1) {
            break;
        }
    }
    if (n >= 4 && g_Minigame[0x1906] > 1) {
        g_Minigame[0x19A8] = 1;
    } else {
        g_Minigame[0x19A8] = 0;
    }
}

// .text:0x000DE610 size:0x134 mapped:0x8071D6A4
void fn_3_DE610(void) {
    return;
}

// .text:0x000DE744 size:0x44C mapped:0x8071D7D8
void fn_3_DE744(void) {
    return;
}

