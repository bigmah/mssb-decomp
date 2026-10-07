#include "game/rep_FE0.h"
#include "header_rep_data.h"
#include "game/rep_1838.h"
#include "static/UnknownHomes_Static.h"

extern u8 g_Fielders[];
extern u8 g_UnkAnimation_31EAC[];

// .text:0x0006AF9C size:0x1A8 mapped:0x806AA030
f32 fn_3_6AF9C(int idx) {
    u8* fielder = g_Fielders + idx * 0x268;
    u8* anim = g_UnkAnimation_31EAC + idx * 0x54;
    f32 base = fn_3_9FEA8(-*(f32*)(fielder + 0x48) - 1.5707964f);
    int a;
    int b;
    int diff;
    if (fielder[0x1FC] != 0) {
        return base;
    }
    a = radToShortAngle(base);
    b = radToShortAngle(*(f32*)(anim + 0x28));
    diff = fn_3_9FCA4(b, a);
    if (diff > 0x800) {
        diff -= 0x1000;
    } else if (diff <= -0x800) {
        diff += 0x1000;
    }
    if (diff > 0x600) {
        if (fielder[0x1C7] == 0) {
            b -= 0x280;
        } else {
            b += 0x280;
        }
    } else if (diff < -0x600) {
        if (fielder[0x1C7] == 0) {
            b -= 0x280;
        } else {
            b += 0x280;
        }
    } else if (diff > 0x200) {
        b -= 0x180;
    } else if (diff < -0x200) {
        b += 0x180;
    } else if (diff > 0x180) {
        b -= 0x100;
    } else if (diff < -0x180) {
        b += 0x100;
    } else if (diff > 0xC0) {
        b -= 0x80;
    } else if (diff < -0xC0) {
        b += 0x80;
    } else if (diff > 0x60) {
        b -= 0x40;
    } else if (diff < -0x60) {
        b += 0x40;
    } else {
        return base;
    }
    return shortAngleToRad(b);
}

extern const f32 lbl_3_rodata_1034;
extern u8 lbl_8036E548[];
extern u8 lbl_3_data_69C0[];
extern u8* lbl_3_common_bss_1323C;

// .text:0x0006B144 size:0x384 mapped:0x806AA1D8
void fn_3_6B144(void) {
    u8* p;
    u8* q;
    int j;
    int i;
    u8* fielders;
    u8* anims;
    u8* flags;
    u8* base;
    u8 st;

    st = g_GameLogic.gameStatus;
    if (st != 0 && st != 1 && st != 2 && st != 8 && st != 3 && st != 0x16 && st != 0x1A &&
        (((u8*)&g_d_GameSettings)[7] != 6 || st != 0xB)) {
        base = lbl_8036E548;
        for (j = 0; j < 9; j++) {
            q = *(u8**)(base + 0x2C50);
            if (q != NULL) {
                q[0x25D] = 0;
            }
            base += 4;
        }
        return;
    }
    for (i = 0; i < 9; i++) {
        f32 f;
        f32 z;
        base = lbl_8036E548 + i * 4;
        fielders = g_Fielders + i * 0x268;
        anims = g_UnkAnimation_31EAC + i * 0x54;
        flags = lbl_3_data_69C0 + i;
        p = *(u8**)(base + 0x2C50);
        if (p != NULL) {
            p[0x25D] = 0;
            p[0x275] = fielders[0x1E6];
            if (g_GameLogic.gameStatus == 3) {
                continue;
            }
            if (((u8*)&g_d_GameSettings)[7] == 2 &&
                (g_GameLogic.secondaryGameMode == 0xE || g_Practice.practiceLevel == 4 ||
                 ((g_GameLogic.secondaryGameMode == 0xB || g_GameLogic.secondaryGameMode == 0xC) && i > 0))) {
                continue;
            }
            p[0x25D] = 1;
            if (anims[0x42] == 0) {
                *(f32*)(p + 0x34) = *(f32*)(fielders + 0);
                *(f32*)(p + 0x38) = -*(f32*)(fielders + 4) - *(f32*)(fielders + 0xC);
                *(f32*)(p + 0x3C) = *(f32*)(fielders + 8);
            }
            f = fn_3_6AF9C(i);
            if (fielders[0x20A] != 0) {
                f = *(f32*)(anims + 0x28);
            }
            *(f32*)(p + 0x44) = f;
            z = lbl_3_rodata_1034;
            *(f32*)(p + 0x40) = z;
            *(f32*)(p + 0x48) = z;
            *(f32*)(anims + 0x28) = f;
            if (fielders[0x263] != 0) {
                p[0x25D] = 2;
            }
            if (((u8*)&g_Stats)[0x36] != 0) {
                p[0x25D] = lbl_3_common_bss_1323C[i + 0x261];
            } else {
                if (i == 1) {
                    u8 s = g_GameLogic.gameStatus;
                    if (s == 1 || !s || s == 7 || s == 0x16 || g_GameLogic.sceneID == 1) {
                        p[0x25D] = 2;
                    }
                    if (g_GameLogic.sceneID == 3) {
                        p[0x25D] = 1;
                    }
                } else if (*flags != 0) {
                    u8 s = g_GameLogic.gameStatus;
                    if (s == 1 || !s || s == 7 || s == 0x16 || g_GameLogic.sceneID == 1) {
                        p[0x25D] = 2;
                    }
                    if (g_GameLogic.sceneID == 3) {
                        p[0x25D] = 1;
                    }
                }
            }
            {
                u8 t = fielders[0x205];
                if (t == 1 || (u8)(t - 2) <= 3 || t == 6) {
                    p[0x25D] = 3;
                }
            }
        }
    }
}
