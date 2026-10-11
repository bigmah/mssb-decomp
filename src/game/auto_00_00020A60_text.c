#include "game/auto_00_00020A60_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0001D86C_text.h"
#include "game/rep_1838.h"

extern const f32 lbl_3_rodata_930; // 0.0f
extern const f32 lbl_3_rodata_938; // 30.0f
extern const f32 lbl_3_rodata_93C; // 40.0f
extern u8 lbl_3_data_1924[4][4]; // pickoff chance (%) by pitcher class and AI level

// .text:0x00020A60 size:0x50 mapped:0x8065FAF4
void fn_3_20A60(void) {
    g_AiLogic.boxHorizontalPoint = g_Batter.batPosition2.x;
    g_AiLogic.boxVerticalPoint = g_Batter.batPosition2.z;
    g_AiLogic.batterAIDesiredZPosInBox = maybeInitialBatPos.z;
    g_AiLogic.batterAIABStrat = -1;
    g_AiLogic._67 = 0;
    g_AiLogic.batterAIBuntPossibility = 1;
    g_AiLogic.batterAIBuntInd = 0;
}

// .text:0x00020AB0 size:0x30 mapped:0x8065FB44
void fn_3_20AB0(void) {
    g_AiLogic.lastPitchFramesUntilPitchGetsToBatter = 0;
    g_AiLogic.lastPitchType = 0xFF;
    g_AiLogic.starRelated[0] = 0;
    g_AiLogic.starRelated[1] = 0;
    g_AiLogic.lastPitchBallLocZone = 0xFF;
    g_AiLogic.lastPitchMoundZone = 0xFF;
    g_AiLogic.batterAIStealIndicator = 0;
}

// .text:0x00020AE0 size:0x50 mapped:0x8065FB74
void fn_3_20AE0(void) {
    return;
}

// .text:0x00020B30 size:0x104 mapped:0x8065FBC4
s32 fn_3_20B30(void) {
    if (!g_AiLogic.aIPitcherPickOffInd) {
        return 0;
    }
    if (g_Pitcher.currentStateFrameCounter > g_AiLogic.AIFrameToBeginPitch - 10) {
        if (g_RunningLogic.runnerBits == 0x1011) {
            if (RandomInt_Game(3) == 0) {
                g_Pitcher.pickOffLoc = 3;
            } else {
                g_Pitcher.pickOffLoc = 1;
            }
        } else if (g_RunningLogic.runnerBits == 0x1101) {
            g_Pitcher.pickOffLoc = 3;
        } else if (g_RunningLogic.runnerBits == 0x111) {
            g_Pitcher.pickOffLoc = 2;
        } else if (g_RunningLogic.runnerBits == 0x1001) {
            g_Pitcher.pickOffLoc = 3;
        } else if (g_RunningLogic.runnerBits == 0x101) {
            g_Pitcher.pickOffLoc = 2;
        } else {
            g_Pitcher.pickOffLoc = 1;
        }
        return 1;
    }
    return 0;
}

// .text:0x00020C34 size:0xB8 mapped:0x8065FCC8
void fn_3_20C34(void) {
    s32 chance;

    if (!g_AiLogic.pitcherAIPitchDownTheMiddleInd) {
        g_AiLogic.aIPitcherPickOffInd = 0;
        if (g_RunningLogic.runnerBits == 1 || g_RunningLogic.runnerBits == 0x1111) {
            return;
        }
        if (g_AiLogic.always0_AIPickoffRelated) {
            chance = 5;
        } else {
            chance = lbl_3_data_1924[g_Pitcher.charClass][g_AiLogic._49];
        }
        if (RandomInt_Game(100) < chance) {
            g_AiLogic.aIPitcherPickOffInd = 1;
        }
    }
}
