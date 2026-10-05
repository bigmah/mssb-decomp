#include "game/rep_540.h"
#include "header_rep_data.h"

extern f32 lbl_3_rodata_590;
extern u8 g_Minigame[];
extern u8 lbl_3_data_450C[];
extern f32 lbl_3_rodata_5E4;
extern f32 lbl_3_rodata_5D4;
extern int fn_3_B7DD8(f32, f32);
extern f32 lbl_3_rodata_608;
extern f32 lbl_3_rodata_59C;
extern f32 lbl_3_rodata_5F8;
extern f64 lbl_3_rodata_600;
extern u8 g_Ball[];
extern u8 g_FieldingLogic[];
extern s32 g_Strikes;
extern void fn_3_88D88(s32);
extern u8 g_d_GameSettings[];
extern void fn_3_27648(void);

extern s16 g_RunningLogic;
extern void fn_3_59918(s32, s32);

// .text:0x00006530 size:0x78 mapped:0x806455C4
void fn_3_6530(void) {
    return;
}

// .text:0x000065A8 size:0x20 mapped:0x8064563C
void fn_3_65A8(void) {
    if (g_Ball[0x1BC9] == 2) {
        g_Ball[0x1BC9] = 1;
    }
}

// .text:0x000065C8 size:0x2C mapped:0x8064565C
void fn_3_65C8(void) {
    if (*(s16*)(g_Ball + 0x1BBC) < 0x7FFE) {
        *(s16*)(g_Ball + 0x1BBC) += 1;
    } else {
        *(s16*)(g_Ball + 0x1BBC) = 0x7FFF;
    }
}

// .text:0x000065F4 size:0x2C mapped:0x80645688
extern u8 g_FieldingLogic[];

void fn_3_65F4(void) {
    g_Ball[0x1BF3] = 0;
    g_FieldingLogic[0x13B] = 1;
    g_Ball[0x1BF5] = 3;
}

// .text:0x00006620 size:0x74 mapped:0x806456B4
void fn_3_6620(void) {
    if (g_Ball[0x1BF3] == 0) {
        g_Ball[0x1BF3] = 1;
        g_Ball[0x1BF4] = 1;
        *(s16*)(g_Ball + 0x1BBC) = 0;
        g_Ball[0x1BC1] = 0;
        g_Ball[0x1BE7] = 0;
        g_Ball[0x1BE5] = 0;
        g_Ball[0x1BF1] = 1;
        g_Ball[0x1BEB] = 0;
        g_Ball[0x1BED] = 0;
        *(f32*)(g_Ball + 0x324) = lbl_3_rodata_590;
        *(f32*)(g_Ball + 0x328) = lbl_3_rodata_590;
        *(f32*)(g_Ball + 0x32C) = lbl_3_rodata_590;
        fn_3_27648();
    }
}

// .text:0x00006694 size:0x5A4 mapped:0x80645728
void fn_3_6694(void) {
    return;
}

// .text:0x00006C38 size:0x20B8 mapped:0x80645CCC
void fn_3_6C38(void) {
    return;
}

// .text:0x00008CF0 size:0x35C mapped:0x80647D84
void fn_3_8CF0(void) {
    return;
}

// .text:0x0000904C size:0x214 mapped:0x806480E0
void fn_3_904C(void) {
    return;
}

// .text:0x00009260 size:0x2A8 mapped:0x806482F4
void fn_3_9260(void) {
    return;
}

// .text:0x00009508 size:0x300 mapped:0x8064859C
void fn_3_9508(void) {
    return;
}

// .text:0x00009808 size:0x36C mapped:0x8064889C
void fn_3_9808(void) {
    return;
}

// .text:0x00009B74 size:0x16C mapped:0x80648C08
void fn_3_9B74(void) {
    return;
}

// .text:0x00009CE0 size:0x138 mapped:0x80648D74
void fn_3_9CE0(void) {
    return;
}

// .text:0x00009E18 size:0x6C mapped:0x80648EAC
void fn_3_9E18(void) {
    if (g_Ball[0x1BD1] != 4) {
        *(f32*)(g_Ball + 0x1A3C) = *(f32*)(g_Ball + 0);
        *(f32*)(g_Ball + 0x1A40) = *(f32*)(g_Ball + 4);
        *(f32*)(g_Ball + 0x1A44) = *(f32*)(g_Ball + 8);
        g_Ball[0x1BD1] = 4;
        if (g_RunningLogic != 0) {
            fn_3_59918(0x14, 0);
        }
    }
}

// .text:0x00009E84 size:0x120 mapped:0x80648F18
void fn_3_9E84(void) {
    u8 st = g_Ball[0x1BD1];
    if (st == 0) {
        if (g_FieldingLogic[0x107] != 0) {
            if (st != 4) {
                *(f32*)(g_Ball + 0x1A3C) = *(f32*)(g_Ball + 0);
                *(f32*)(g_Ball + 0x1A40) = *(f32*)(g_Ball + 4);
                *(f32*)(g_Ball + 0x1A44) = *(f32*)(g_Ball + 8);
                g_Ball[0x1BD1] = 4;
                if (g_RunningLogic != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else if (g_Ball[0x1BD8] != 0 && g_Ball[0x1BD7] != 0) {
            if (st != 4) {
                *(f32*)(g_Ball + 0x1A3C) = *(f32*)(g_Ball + 0);
                *(f32*)(g_Ball + 0x1A40) = *(f32*)(g_Ball + 4);
                *(f32*)(g_Ball + 0x1A44) = *(f32*)(g_Ball + 8);
                g_Ball[0x1BD1] = 4;
                if (g_RunningLogic != 0) {
                    fn_3_59918(0x14, 0);
                }
            }
        } else {
            g_Ball[0x1BD1] = 3;
            *(f32*)(g_Ball + 0x1A3C) = *(f32*)(g_Ball + 0);
            *(f32*)(g_Ball + 0x1A40) = *(f32*)(g_Ball + 4);
            *(f32*)(g_Ball + 0x1A44) = *(f32*)(g_Ball + 8);
            fn_3_59918(7, 0);
        }
    }
}

// .text:0x00009FA4 size:0x7C mapped:0x80649038
void fn_3_9FA4(void) {
    if (g_Ball[0x1BD1] == 0) {
        *(f32*)(g_Ball + 0x1A3C) = *(f32*)(g_Ball + 0);
        *(f32*)(g_Ball + 0x1A40) = *(f32*)(g_Ball + 4);
        *(f32*)(g_Ball + 0x1A44) = *(f32*)(g_Ball + 8);
        g_Ball[0x1BD1] = 1;
        *(s16*)(g_Ball + 0x1BA4) = 1;
        *(s16*)(g_Ball + 0x1B7A) = 1;
        g_Ball[0x1BC6] = 1;
        if (g_d_GameSettings[7] != 6) {
            fn_3_59918(0xF, 0);
        }
    }
}

// .text:0x0000A020 size:0xD0 mapped:0x806490B4
void fn_3_A020(void) {
    s32 done;
    if (g_Ball[0x1BD1] == 0) {
        g_Ball[0x1BD1] = 2;
        done = 0;
        *(f32*)(g_Ball + 0x1A3C) = *(f32*)(g_Ball + 0);
        *(f32*)(g_Ball + 0x1A40) = *(f32*)(g_Ball + 4);
        *(f32*)(g_Ball + 0x1A44) = *(f32*)(g_Ball + 8);
        *(s16*)(g_Ball + 0x1B7A) = -1;
        g_Ball[0x1BC6] = 1;
        if (g_FieldingLogic[0x110] != 1) {
            g_FieldingLogic[0x110] = 1;
            g_Strikes = g_Strikes + 1;
            if (g_Strikes >= 3) {
                if (g_Ball[0x1BCF] != 0) {
                    g_Ball[0x1BD3] = 1;
                    fn_3_88D88(0);
                    done = 1;
                } else {
                    g_Strikes = 2;
                }
            }
            if (done == 0) {
                fn_3_59918(3, 0);
            }
        }
    }
}

// .text:0x0000A0F0 size:0xA8 mapped:0x80649184
void fn_3_A0F0(void) {
    s32 done;
    *(s16*)(g_Ball + 0x1B7A) = -1;
    g_Ball[0x1BC6] = 1;
    done = 0;
    if (g_FieldingLogic[0x110] != 1) {
        g_FieldingLogic[0x110] = 1;
        g_Strikes = g_Strikes + 1;
        if (g_Strikes >= 3) {
            if (g_Ball[0x1BCF] != 0) {
                g_Ball[0x1BD3] = 1;
                fn_3_88D88(0);
                done = 1;
            } else {
                g_Strikes = 2;
            }
        }
        if (done == 0) {
            fn_3_59918(3, 0);
        }
    }
}

// .text:0x0000A198 size:0x6A4 mapped:0x8064922C
void fn_3_A198(void) {
    return;
}

// .text:0x0000A83C size:0x134 mapped:0x806498D0
void fn_3_A83C(void) {
    return;
}

// .text:0x0000A970 size:0xAD0 mapped:0x80649A04
void fn_3_A970(void) {
    return;
}

// .text:0x0000B440 size:0x500 mapped:0x8064A4D4
void fn_3_B440(void) {
    return;
}

// .text:0x0000B940 size:0x27C mapped:0x8064A9D4
void fn_3_B940(void) {
    return;
}

// .text:0x0000BBBC size:0x98 mapped:0x8064AC50
s32 fn_3_BBBC(f32* out, s32 n, s32 step, f32 x, f32 z) {
    f32 best = lbl_3_rodata_608;
    s32 i;
    s32 found = -1;
    for (i = 0; i < n; i += step) {
        f32 dx = *(f32*)(g_Ball + i * 16 + 0x354) - x;
        f32 dz = *(f32*)(g_Ball + i * 16 + 0x35C) - z;
        f32 d = dx * dx + dz * dz;
        if (d < best) {
            best = d;
            found = i;
        } else {
            break;
        }
    }
    if (found < 0) {
        return -1;
    }
    {
        u8* e = g_Ball + found * 16;
        out[0] = *(f32*)(e + 0x354);
        out[1] = *(f32*)(e + 0x358);
        out[2] = *(f32*)(e + 0x35C);
    }
    return found;
}

// .text:0x0000BC54 size:0x124 mapped:0x8064ACE8
void fn_3_BC54(void) {
    f32 v;
    if (fn_3_B7DD8(*(f32*)(g_Ball + 0), *(f32*)(g_Ball + 8)) == 0) {
        if (*(f32*)(g_Ball + 0) > lbl_3_rodata_590) {
            v = *(f32*)(g_Ball + 8) - *(f32*)(g_Ball + 0);
        } else {
            v = *(f32*)(g_Ball + 8) + *(f32*)(g_Ball + 0);
        }
        if (!(v < lbl_3_rodata_5E4 || *(f32*)(g_Ball + 0x1A14) < lbl_3_rodata_5D4)) {
            return;
        }
    }
    fn_3_A0F0();
}

// .text:0x0000BD78 size:0x2BC mapped:0x8064AE0C
void fn_3_BD78(void) {
    return;
}

// .text:0x0000C034 size:0x9C0 mapped:0x8064B0C8
void fn_3_C034(void) {
    return;
}

// .text:0x0000C9F4 size:0x434 mapped:0x8064BA88
void fn_3_C9F4(void) {
    return;
}

// .text:0x0000CE28 size:0xBC4 mapped:0x8064BEBC
void estimateAndSetFutureCoords(int) {
    return;
}

// .text:0x0000D9EC size:0x1E4 mapped:0x8064CA80
void fn_3_D9EC(void) {
    return;
}

// .text:0x0000DBD0 size:0x78 mapped:0x8064CC64
void fn_3_DBD0(void) {
    f32 t = lbl_3_rodata_59C - (f32)*(s16*)(g_Ball + 0x1B58) / lbl_3_rodata_5F8;
    *(f32*)(g_Ball + 0x318) = *(f32*)(g_Ball + 0x318) * t;
    *(f32*)(g_Ball + 0x31C) = *(f32*)(g_Ball + 0x31C) * t;
    *(f32*)(g_Ball + 0x320) = *(f32*)(g_Ball + 0x320) * t;
}

// .text:0x0000DC48 size:0x68C mapped:0x8064CCDC
void fn_3_DC48(void) {
    return;
}

// .text:0x0000E2D4 size:0xB78 mapped:0x8064D368
void fn_3_E2D4(void) {
    return;
}

// .text:0x0000EE4C size:0x390 mapped:0x8064DEE0
void fn_3_EE4C(void) {
    return;
}

// .text:0x0000F1DC size:0x39C mapped:0x8064E270
void fn_3_F1DC(void) {
    return;
}

// .text:0x0000F578 size:0x240 mapped:0x8064E60C
void fn_3_F578(void) {
    return;
}

// .text:0x0000F7B8 size:0x240 mapped:0x8064E84C
void fn_3_F7B8(void) {
    return;
}

// .text:0x0000F9F8 size:0x1B0 mapped:0x8064EA8C
void fn_3_F9F8(void) {
    s32 i;
    *(f32*)(g_Ball + 0) = *(f32*)(lbl_3_data_450C + 0);
    *(f32*)(g_Ball + 4) = lbl_3_rodata_590;
    *(f32*)(g_Ball + 8) = *(f32*)(lbl_3_data_450C + 4);
    if (g_Minigame[0x1A2A] == 6) {
        *(f32*)(g_Ball + 0) = lbl_3_rodata_590;
        *(f32*)(g_Ball + 8) = lbl_3_rodata_590;
        *(f32*)(g_Ball + 4) = lbl_3_rodata_59C;
    }
    for (i = 0; i < 0x3C; i++) {
        *(f32*)(g_Ball + i * 12 + 0x3C) = *(f32*)(g_Ball + 0);
        *(f32*)(g_Ball + i * 12 + 0x40) = *(f32*)(g_Ball + 4);
        *(f32*)(g_Ball + i * 12 + 0x44) = *(f32*)(g_Ball + 8);
    }
    *(f32*)(g_Ball + 0x318) = lbl_3_rodata_590;
    *(f32*)(g_Ball + 0x324) = lbl_3_rodata_590;
    *(f32*)(g_Ball + 0x31C) = lbl_3_rodata_590;
    *(f32*)(g_Ball + 0x328) = lbl_3_rodata_590;
    *(f32*)(g_Ball + 0x320) = lbl_3_rodata_590;
    *(f32*)(g_Ball + 0x32C) = lbl_3_rodata_590;
}

// .text:0x0000FBA8 size:0x3A4 mapped:0x8064EC3C
void fn_3_FBA8(void) {
    return;
}
