#include "game/rep_2940.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_8036E548[];
extern void fn_3_6A25C(void);
extern void fn_3_6A250(void);

// .text:0x000E11E0 size:0x118 mapped:0x80720274
#define MGB ((u8*)&g_Minigame)
extern f32 lbl_3_data_18DD4[];
extern f32 lbl_3_rodata_1088;

void fn_3_E11E0(void) {
    int i;
    u8* b = lbl_8036E548;
    *(s16*)(b + 0x2D68) = -1;
    for (i = 0; i < 4; b += 4, i++) {
        u8* e = *(u8**)(b + 0x2C50);
        if (e != 0) {
            e[0x25D] = 0;
            if (MGB[0x1A13 + i] == 0 && *(s8*)(MGB + 0x19EA + i * 9) >= 0 &&
                *(s8*)(MGB + 0x19EF + i * 9) != 0) {
                s8 t = *(s8*)(MGB + 0x19DA + i);
                if (t >= 0) {
                    if (g_d_GameSettings.exhibitionMatchInd == 0) {
                        if (t >= 1) {
                        } else {
                            goto set;
                        }
                    } else if (MGB[0x19E6] != 1 || g_d_GameSettings.GameModeSelected == 6 || MGB[0x1A3C] != 0 || t < 1) {
                    set:
                        e[0x25D] = 1;
                        *(f32*)(e + 0x34) = lbl_3_data_18DD4[i * 3];
                        *(f32*)(e + 0x38) = -lbl_3_data_18DD4[i * 3 + 1];
                        *(f32*)(e + 0x3C) = lbl_3_data_18DD4[i * 3 + 2];
                        *(f32*)(e + 0x40) = 0.0f;
                        *(f32*)(e + 0x44) = 0.0f;
                        *(f32*)(e + 0x48) = 0.0f;
                    }
                }
            }
        }
    }
}

// .text:0x000E12F8 size:0x78 mapped:0x8072038C
void fn_3_E12F8(void) {
    int i;
    u8* p;
    for (i = 0; i < 4; i++) {
        p = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
        if (p != NULL) {
            p[0x25D] = 0;
        }
    }
    fn_3_6A25C();
    fn_3_6A250();
}

// .text:0x000E1370 size:0x108 mapped:0x80720404
void fn_3_E1370(int mode) {
    s8* mg = (s8*)&g_Minigame;
    u8* p;
    int i;
    for (i = 0; i < 4; i++) {
        if (mode == 3) {
            p = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
            if (g_d_GameSettings.GameModeSelected == 2) {
                p = *(u8**)(lbl_8036E548 + 0x2C74);
                if (i >= 1) {
                    return;
                }
            }
            if (p != NULL) {
                p[0x25A] = mg[0x19EC + i * 9] / 2;
                p[0x25B] = mg[0x19EC + i * 9] % 2;
            }
        }
    }
}

// .text:0x000E1478 size:0x4EC mapped:0x8072050C
void fn_3_E1478(void) {
    return;
}

