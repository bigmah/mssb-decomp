#include "game/rep_1090.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_8036E548[];
extern u8 lbl_3_data_6EF0[];
extern u8* lbl_3_common_bss_1323C;
extern void fn_3_6A25C(void);
extern void fn_3_6A250(void);
extern void fn_3_6A254(void);
extern void fn_3_6A2A4(u8);
extern void fn_3_E07DC(void);
extern int fn_8004ACC4(int);
extern int fn_8004ACDC(int);

#define CLEAR4()                                      \
    {                                                 \
        u8* b = lbl_8036E548;                         \
        int k;                                        \
        for (k = 0; k < 4; k++) {                     \
            u8* q = *(u8**)(b + 0x2C74);              \
            if (q != NULL) {                          \
                q[0x25D] = 0;                         \
            }                                         \
            b += 4;                                   \
        }                                             \
    }

// .text:0x0006C4D0 size:0x384 mapped:0x806AB564
void fn_3_6C4D0(void) {
    u8* p;
    u8* r;
    u8* d;
    u8* pp;
    int i;
    if (lbl_8036E548[0x2D77] != 0) {
        CLEAR4();
        fn_3_6A25C();
        fn_3_6A250();
        return;
    }
    if (g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 2 &&
        g_GameLogic.gameStatus != 8 && g_GameLogic.gameStatus != 0x16) {
        CLEAR4();
        fn_3_6A25C();
        fn_3_6A250();
        if (g_GameLogic.gameStatus == 0xE) {
            fn_3_E07DC();
        }
        return;
    }
    if (g_GameLogic.secondaryGameMode == 0xB) {
        CLEAR4();
        fn_3_6A25C();
        fn_3_6A250();
        return;
    }
    for (i = 0; i < 4; i++) {
        p = ((u8**)lbl_8036E548)[i + 0xB1D];
        r = (u8*)g_Runners + i * 0x154;
        d = lbl_3_data_6EF0 + i;
        if (p != NULL) {
            p[0x275] = r[0x14C];
            if (i == 0) {
                p[0x278] = 1;
            }
            if (r[0x146] == 3) {
                p[0x25D] = 0;
            } else {
                u8 t;
                if (i == 0 && ((u8*)&g_Pitcher)[0x14E] == 3) {
                    t = p[0x252];
                    if ((s8)t == 0x26) {
                        if (fn_8004ACDC(1) != 0) {
                            fn_3_6A254();
                        }
                        goto L50;
                    }
                    if ((u8)(t - 0x30) <= 2U || (s8)t == 0x33) {
                        p[0x25D] = 2;
                        if (fn_8004ACC4(1) != 0) {
                            fn_3_6A2A4(p[0x252]);
                        }
                    } else {
                        goto L50;
                    }
                } else {
                L50:
                    if (r[0x123] == 0 || *(s16*)(r + 0xE0) < 0) {
                        p[0x25D] = 0;
                    } else if (r[0x146] == 3) {
                        p[0x25D] = 0;
                    } else {
                        p[0x25D] = 1;
                        *(f32*)(p + 0x34) = *(f32*)r;
                        *(f32*)(p + 0x38) = *(f32*)(r + 4);
                        *(f32*)(p + 0x3C) = *(f32*)(r + 8);
                        *(f32*)(p + 0x40) = 0.0f;
                        *(f32*)(p + 0x44) = *(f32*)(r + 0x30);
                        *(f32*)(p + 0x48) = 0.0f;
                    }
                    if (g_Stats.replayInd != 0) {
                        p[0x25D] = lbl_3_common_bss_1323C[i + 0x261];
                    } else if (*d != 0 && g_GameLogic.sceneID != 3 && g_GameLogic.secondaryGameMode != 0xE &&
                               (g_GameLogic.gameStatus == 1 || g_GameLogic.gameStatus == 0 ||
                                g_GameLogic.gameStatus == 7 || g_GameLogic.sceneID == 1)) {
                        p[0x25D] = 0;
                    }
                }
            }
        }
    }
}
