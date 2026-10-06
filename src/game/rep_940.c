#include "game/rep_940.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
extern f32 lbl_3_rodata_990;
extern f32 lbl_3_rodata_994;
extern f32 lbl_3_rodata_998;
extern f32 lbl_3_data_4474[];
extern u8 lbl_3_data_190C[];

// .text:0x00020CEC size:0x164 mapped:0x8065FD80
s32 fn_3_20CEC(f32 k) {
    f32 d;
    s32 t = g_Ball.pitchHangtimeCounter;
    if (t <= 1) {
        return 0;
    }
    if (lbl_3_rodata_990 == k) {
        return 0;
    }
    d = g_AiLogic.aiPitchCurveEndingX - g_Pitcher.pitchXPosition2;
    if (g_AiLogic.pitchAIDelayCurveStart != 0) {
        s32 r = g_Pitcher.frameWhenUnhittable - t;
        f32 lim;
        if (r <= 0) {
            return 0;
        }
        lim = k * (f32)((r / 2) * r);
        if (d < lbl_3_rodata_990) {
            if (-d < lim) {
                return 0;
            }
        } else if (d < lim) {
            return 0;
        }
        g_AiLogic.pitchAIDelayCurveStart = 0;
    }
    if (d > lbl_3_rodata_994) {
        if ((s8)g_AiLogic.aiPitchDirectionInput == -1) {
            return 0;
        }
        g_AiLogic.aiPitchDirectionInput = 1;
        return 1;
    }
    if (d < lbl_3_rodata_998) {
        if (*(s8*)&g_AiLogic.aiPitchDirectionInput == 1) {
            return 0;
        }
        *(s8*)&g_AiLogic.aiPitchDirectionInput = -1;
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
    f32 lo;
    f32 hi;
    f32 step;
    f32 fi;
    if (g_AiLogic.pitcherAIPitchDownTheMiddleInd != 0) {
        g_AiLogic.aIMoundLocationX = lbl_3_rodata_990;
        return;
    }
    idx = RandomIndexFromWeights(lbl_3_data_190C + g_Pitcher.charClass * 6, 6);
    if (idx != 5) {
        g_AiLogic.aIMoundLocationIndex = idx;
        hi = lbl_3_data_4474[1];
        lo = lbl_3_data_4474[0];
        step = hi - lo;
        step = step / 5.0f;
        g_AiLogic.aIMoundLocationX = step * (f32)idx + lo;
    }
}

// .text:0x00020FB0 size:0x2F0 mapped:0x80660044
void fn_3_20FB0(void) {
    return;
}

// .text:0x000212A0 size:0x30C mapped:0x80660334
void fn_3_212A0(void) {
    return;
}

// .text:0x000215AC size:0x1BC mapped:0x80660640
void fn_3_215AC(void) {
    return;
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

