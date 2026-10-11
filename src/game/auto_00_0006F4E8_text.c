#include "game/auto_00_0006F4E8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0001D86C_text.h"
#include "game/auto_00_0005985C_text.h"

// Views declared in the unit headers (kept out of them: other units have their own views).
extern RunningLogicStruct g_RunningLogic;

// .text:0x0006F4E8 size:0x1E4 mapped:0x806AE57C
s32 fn_3_6F4E8(void) {
    s32 found = 0;
    s32 i;
    s32 j;

    if (g_Strikes.outs >= 3) {
        return 0;
    }
    if (g_Strikes.outs >= 2 && g_Pitcher.strikeOutOrWalk == 1) {
        return 0;
    }
    if (g_Pitcher.strikeOutOrWalk == 2) {
        if (g_RunningLogic._12 == 4) {
            return 0;
        }
        for (i = 1; i < 4; i++) {
            if ((g_Runners[i].runnerOnFieldOrOutOrScored == 1 || g_Runners[i].runnerOnFieldOrOutOrScored == 3) &&
                g_Runners[i].furthestBaseForcedToGoToOnWalk == 1) {
                found = 1;
            }
        }
        if (found == 0) {
            return 0;
        }
    }
    for (i = 1; i < 4; i++) {
        if (g_Runners[i].runnerOnFieldOrOutOrScored == 1 && g_Runners[i].furthestBaseForcedToGoToOnWalk != 0) {
            g_Pitcher.pickOffLoc = 5;
            fn_3_5C69C(1);
            if (g_Pitcher.strikeOutOrWalk == 1) {
                g_Strikes.outs++;
                for (j = 0; j < 3; j++) {
                    if (g_Strikes.runnerIndexForEachOutThisPitch[j] == -1) {
                        g_Strikes.runnerIndexForEachOutThisPitch[j] = 0;
                        break;
                    }
                }
            }
            return 1;
        }
    }
    return 0;
}
