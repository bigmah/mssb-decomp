#include "game/rep_940.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1200.h"
extern f32 lbl_3_rodata_990;
extern f32 lbl_3_data_4474[];
extern u8 lbl_3_data_190C[];
extern f32 lbl_3_rodata_9A8;
extern f32 lbl_3_rodata_994;
extern f32 lbl_3_rodata_998;

// .text:0x00020CEC size:0x164 mapped:0x8065FD80
s32 fn_3_20CEC(f32 k) {
    f32 dx;
    f32 lim;
    s32 t;
    if (g_Ball.pitchHangtimeCounter <= 1) {
        return 0;
    }
    if (lbl_3_rodata_990 == k) {
        return 0;
    }
    dx = g_AiLogic.aiPitchCurveEndingX - g_Pitcher.pitchXPosition2;
    if (g_AiLogic.pitchAIDelayCurveStart != 0) {
        t = g_Pitcher.frameWhenUnhittable - g_Ball.pitchHangtimeCounter;
        if (t <= 0) {
            return 0;
        }
        lim = k * (f32)((t / 2) * t);
        if (dx < lbl_3_rodata_990) {
            if (-dx < lim) {
                return 0;
            }
        } else if (dx < lim) {
            return 0;
        }
        g_AiLogic.pitchAIDelayCurveStart = 0;
    }
    if (dx > lbl_3_rodata_994) {
        if (g_AiLogic.aiPitchDirectionInput == -1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = 1;
        return 1;
    }
    if (dx < lbl_3_rodata_998) {
        if (g_AiLogic.aiPitchDirectionInput == 1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = -1;
        return -1;
    }
    return 0;
}

// .text:0x00020E50 size:0x9C mapped:0x8065FEE4
void fn_3_20E50(void) {
    f32 d;
    if (g_Pitcher.currentStateFrameCounter >= 0x1E && g_AiLogic.aIMoundLocationX != g_Pitcher.pitcher.x) {
        d = g_AiLogic.aIMoundLocationX - g_Pitcher.pitcher.x;
        if (d > lbl_3_rodata_990) {
            if (d <= lbl_3_data_4474[2]) {
                g_Pitcher.pitcher.x = g_AiLogic.aIMoundLocationX;
            } else {
                g_Pitcher.pitcher.x += lbl_3_data_4474[2];
            }
        } else {
            if (d >= -lbl_3_data_4474[2]) {
                g_Pitcher.pitcher.x = g_AiLogic.aIMoundLocationX;
            } else {
                g_Pitcher.pitcher.x -= lbl_3_data_4474[2];
            }
        }
    }
}

// .text:0x00020EEC size:0xC4 mapped:0x8065FF80
void fn_3_20EEC(void) {
    s32 idx;
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aIMoundLocationX = lbl_3_rodata_990;
        return;
    }
    idx = RandomIndexFromWeights(lbl_3_data_190C + g_Pitcher.charClass * 6, 6);
    if (idx != 5) {
        g_AiLogic.aIMoundLocationIndex = idx;
        { f32 lo = lbl_3_data_4474[0]; f32 st = lbl_3_data_4474[1] - lo; st = st / 5.0f; g_AiLogic.aIMoundLocationX = st * (f32)idx + lo; }
    }
}

// .text:0x00020FB0 size:0x2F0 mapped:0x80660044
#pragma dont_inline on
void fn_3_20FB0(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000212A0 size:0x30C mapped:0x80660334
#pragma dont_inline on
void fn_3_212A0(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000215AC size:0x1BC mapped:0x80660640
void fn_3_215AC(void) {
    if (g_Pitcher.currentStateFrameCounter == 1) {
        fn_3_20EEC();
    }
    fn_3_20E50();
    if (g_Pitcher.currentStateFrameCounter >= g_AiLogic.AIFrameToBeginPitch) {
        if (g_Batter.beginningOfABAnimationOccuring == 0) {
            fn_3_212A0();
            fn_3_20FB0();
            fn_3_750C4(2);
            *((u8*)&g_Stats + 0x38) = 1;
        }
    }
}

// .text:0x00021768 size:0x238 mapped:0x806607FC
void fn_3_21768(void) {
    return;
}

// .text:0x000219A0 size:0x2C mapped:0x80660A34
void fn_3_219A0(void) {
    g_AiLogic.nStarPitchesThrownThisAB = 0;
    g_AiLogic.aIMoundLocationX = lbl_3_rodata_990;
    g_AiLogic.aIMoundLocationIndex = 2;
    g_AiLogic.always0_AIPickoffRelated = 0;
}

