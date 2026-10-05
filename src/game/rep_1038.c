#include "game/rep_1038.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern void fn_3_690FC(void);
extern void fn_3_6AEE0(void);
extern void fn_3_6C454(void);
extern void fn_3_6C410(void);
extern void fn_3_697CC(void);
extern void fn_3_685F0(void);
extern void fn_3_6B144(void);
extern void fn_3_6C4D0(void);
extern void fn_3_6C428(void);
extern void fn_3_6B674(void);
extern void fn_3_6AB58(void);
extern void fn_3_15A9F4(void);
extern void fn_3_973EC(void);
extern u8* lbl_3_common_bss_1323C[];
extern u8 g_Fielders[];
extern u8 lbl_8036E548[];

// .text:0x0006BEA4 size:0x15C mapped:0x806AAF38
void fn_3_6BEA4(void) {
    int i;
    fn_3_690FC();
    fn_3_6AEE0();
    fn_3_6C454();
    ((u8*)&g_UnkSound_32718)[7] = 0;
    for (i = 0; i < 13; i++) {
        u8* o = lbl_3_common_bss_1323C[0];
        u8* p;
        if (*(s16*)(o + 0x240 + i * 2) >= 0) {
            p = ((u8**)lbl_8036E548)[0xB14 + i];
            if (p != NULL) {
                p[0x25D] = o[0x261 + i];
                if (i <= 8) {
                    u8* f = (u8*)g_Fielders + i * 0x268;
                    lbl_3_common_bss_1323C[0][0x26E + i] = 0;
                    if (*(s16*)(f + 0x178) != -1) {
                        *(f32*)(p + 0x34) = *(f32*)(f + 0);
                        *(f32*)(p + 0x38) = *(f32*)(f + 4);
                        *(f32*)(p + 0x3C) = *(f32*)(f + 8);
                        *(f32*)(p + 0x44) = *(f32*)(f + 0x48);
                    }
                } else if (i <= 12) {
                    u8* r = (u8*)g_Runners + (i - 9) * 0x154;
                    lbl_3_common_bss_1323C[0][0x26E + i] = 0;
                    if (*(s16*)(r + 0xE0) != -1) {
                        *(f32*)(p + 0x34) = *(f32*)(r + 0);
                        *(f32*)(p + 0x38) = *(f32*)(r + 4);
                        *(f32*)(p + 0x3C) = *(f32*)(r + 8);
                        *(f32*)(p + 0x44) = *(f32*)(r + 0x30);
                    }
                }
                *(f32*)(p + 0x40) = 0.0f;
                *(f32*)(p + 0x48) = 0.0f;
            }
        }
    }
}

// .text:0x0006C000 size:0xE0 mapped:0x806AB094
extern f32 lbl_3_data_18DD4[];

void fn_3_6C000(void) {
    int i;
    u8* p;
    u8* q;
    *(s16*)(lbl_8036E548 + 0x2D68) = -1;
    for (i = 0; i < 13; i++) {
        p = ((u8**)lbl_8036E548)[i + 0xB14];
        if (p != NULL) {
            p[0x25D] = 0;
        }
    }
    if (((u8*)&g_Practice)[0x195] != 6 && ((u8*)&g_Practice)[0x195] > 1 && (q = *(u8**)(lbl_8036E548 + 0x2C74)) != NULL
        && ((u8*)&g_Minigame)[0x1A13] == 0 && *(s8*)((u8*)&g_Minigame + 0x19EA) >= 0 && *(s8*)((u8*)&g_Minigame + 0x19EF) != 0
        && *(s8*)((u8*)&g_Minigame + 0x19DA) >= 0) {
        f32* d = lbl_3_data_18DD4;
        q[0x25D] = 1;
        *(f32*)(q + 0x34) = d[0];
        *(f32*)(q + 0x38) = -d[1];
        *(f32*)(q + 0x3C) = d[2];
        *(f32*)(q + 0x40) = 0.0f;
        *(f32*)(q + 0x44) = 0.0f;
        *(f32*)(q + 0x48) = 0.0f;
    }
}

// .text:0x0006C0E0 size:0x28 mapped:0x806AB174
extern u8 lbl_3_common_bss_32724[];

void fn_3_6C0E0(void) {
    *(s16*)(lbl_3_common_bss_32724 + 0x90) = -1;
    *(s16*)(lbl_3_common_bss_32724 + 0x92) = 0;
    lbl_3_common_bss_32724[0xA9] = 0;
    lbl_3_common_bss_32724[0xD3] = 0;
    lbl_3_common_bss_32724[0xB5] = 0;
}

// .text:0x0006C108 size:0x34 mapped:0x806AB19C
extern void fn_3_B93C8(s32);

void fn_3_6C108(void) {
    fn_3_B93C8(1);
    lbl_3_common_bss_32724[0xAE] = 0;
}

// .text:0x0006C13C size:0x14 mapped:0x806AB1D0
extern u8 g_Scores[];

void fn_3_6C13C(void) {
    g_Scores[0xC3] = 0;
}

// .text:0x0006C150 size:0x88 mapped:0x806AB1E4
extern void fn_3_6916C(void*);
extern void fn_3_674E0(void);
extern void fn_3_97800(void);

void fn_3_6C150(void) {
    *(s16*)(lbl_3_common_bss_32724 + 0x9E) = -1;
    *(s16*)(lbl_3_common_bss_32724 + 0xA0) = -1;
    *(s16*)(lbl_3_common_bss_32724 + 0xA2) = -1;
    fn_3_6916C(lbl_3_common_bss_32724);
    fn_3_674E0();
    fn_3_97800();
    if (((u8*)&g_d_GameSettings)[0x11] != 0) {
        lbl_8036E548[0x307E] = 0;
        return;
    }
    if (((u8*)&g_d_GameSettings)[7] != 2) {
        lbl_8036E548[0x307A] = 1;
        lbl_8036E548[0x307E] = 1;
    }
}

// .text:0x0006C1D8 size:0x238 mapped:0x806AB26C

void fn_3_6C1D8(void) {
    u8 mode = ((u8*)&g_GameLogic)[0x11E];
    if (mode != 4) {
        u8 gm = ((u8*)&g_d_GameSettings)[7];
        if (gm == 2 && ((u8*)&g_GameLogic)[0x121] == 0xA && ((u8*)&g_Practice)[0x198] == 6) {
            fn_3_6C000();
        } else if (mode != 5 && lbl_8036E548[0x307A] != 0) {
            if (lbl_3_common_bss_1323C[0][0x25C] != 0) {
                fn_3_6BEA4();
            } else if ((((u8)(mode - 0xB) <= 1) || ((u8*)&g_GameLogic)[0x121] == 0xA || ((u8*)&g_GameLogic)[0x121] == 0x12
                        || (gm == 2 && ((u8*)&g_Practice)[0x196] == 0))
                       && (gm != 6 || mode != 0xB)) {
                fn_3_690FC();
                fn_3_6AEE0();
                fn_3_6C454();
                fn_3_6C410();
                ((u8*)&g_UnkSound_32718)[7] = 0;
            } else {
                fn_3_697CC();
                fn_3_685F0();
                fn_3_6B144();
                fn_3_6C4D0();
                fn_3_6C428();
                fn_3_6B674();
                fn_3_6AB58();
            }
        }
        if (((u8*)&g_d_GameSettings)[7] == 2) {
            fn_3_15A9F4();
        } else {
            fn_3_973EC();
        }
    }
}

