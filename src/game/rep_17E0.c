#include "game/rep_17E0.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_data_4380[];

// .text:0x0009CAF0 size:0x2A0 mapped:0x806DBB84
void fn_3_9CAF0(void) {
    if (g_Ball.deadBallReason == 1) {
        if (g_Ball.homeRunInd == 1) {
            if (g_Ball.homeRunClassification == 1) {
                lbl_3_common_bss_32A94._4 = 4;
                return;
            }
            if (g_Ball.Hit_VerticalAngle < 0x100) {
                lbl_3_common_bss_32A94._4 = 8;
                return;
            }
            lbl_3_common_bss_32A94._4 = 0xC;
            return;
        }
        {
            int t = lbl_3_data_4380[g_d_GameSettings.StadiumID];
            s16 ang = g_Ball.ballAngleFromHome;
            if (ang < 0x400 - t) {
                if (g_Ball.homeRunClassification == 1) {
                    lbl_3_common_bss_32A94._4 = 3;
                    return;
                }
                if (g_Ball.Hit_VerticalAngle < 0x100) {
                    lbl_3_common_bss_32A94._4 = 7;
                    return;
                }
                lbl_3_common_bss_32A94._4 = 0xB;
                return;
            }
            if (ang > t + 0x400) {
                if (g_Ball.homeRunClassification == 1) {
                    lbl_3_common_bss_32A94._4 = 1;
                    return;
                }
                if (g_Ball.Hit_VerticalAngle < 0x100) {
                    lbl_3_common_bss_32A94._4 = 5;
                    return;
                }
                lbl_3_common_bss_32A94._4 = 9;
                return;
            }
        }
        if (g_Ball.homeRunClassification == 1) {
            lbl_3_common_bss_32A94._4 = 2;
            return;
        }
        if (g_Ball.Hit_VerticalAngle < 0x100) {
            lbl_3_common_bss_32A94._4 = 6;
            return;
        }
        lbl_3_common_bss_32A94._4 = 0xA;
        return;
    }
    if (g_Ball.AtBat_ContactResult == 3) {
        u8 r = ((u8*)g_Runners)[0x51F];
        if (r == 1 && g_Ball.timeSinceBallPickedUp < 0x3C && g_Ball.framesSinceThrowStarted < 1 &&
            ((u8*)g_Runners)[0x524] == 0 && *(f32*)((u8*)g_Runners + 0x460) >= 3.15f) {
            lbl_3_common_bss_32A94._4 = 0xE;
        }
        if (r == 3 && lbl_3_common_bss_32A94._4 == 0xE && g_Ball.framesSinceBallHitGroundOrWasCaught <= 0xF0 &&
            g_Strikes.storedOuts < 2) {
            lbl_3_common_bss_32A94._4 = 0xD;
            lbl_3_common_bss_32A94._0 = 0x11;
        }
        if (lbl_3_common_bss_32A94._4 == 0xE && (((u8*)g_Runners)[0x533] == 2 || ((u8*)g_Runners)[0x533] == 3)) {
            lbl_3_common_bss_32A94._4 = 0;
        }
    }
}
