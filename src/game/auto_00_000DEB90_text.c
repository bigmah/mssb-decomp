#include "game/auto_00_000DEB90_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/auto_00_0005985C_text.h"
#include "game/rep_1838.h"
#include "game/rep_1200.h"
#include "game/game_batter.h"
#include "game/rep_540.h"
#include "game/rep_AC8.h"
#include "game/auto_00_0001E154_text.h"
#include "game/rep_1C0.h"
#include "game/rep_1188.h"
#include "game/auto_00_000AC9F8_text.h"
#include "game/auto_00_0001D86C_text.h"
#include "game/rep_3090.h"
#include "game/auto_00_000FBCD0_text.h"
#include "game/auto_00_00090754_text.h"
#include "game/auto_00_000E1964_text.h"
#include "game/rep_2940.h"
#include "game/rep_28A8.h"
#include "game/sta_c6.h"
#include <stdlib.h>

extern void possiblyTransitionBlackScreen(void);

// Views declared in game/auto_00_000DEB90_text.h (kept out of the header: other units have their own views).
extern MinigameCharMgrView lbl_8036E548;
extern MinigameScoresView g_Scores;
extern MinigameBss32724View lbl_3_common_bss_32724;
extern MinigameBss32234View lbl_3_common_bss_32234;
extern MinigameCBC3CView lbl_803CBC3C;
extern MinigameFielderView g_Fielders[];
extern MinigameLineScoreView lbl_80353A90;
extern MinigameBss37400View lbl_3_common_bss_37400;
extern MinigameSceneFadeView lbl_8037169C;

extern f32 lbl_3_data_18D98[];
extern MinigameCoinTiming lbl_3_data_18BB0[];
extern f32 lbl_3_data_18DD0; // coin spin per frame
extern s16 lbl_3_data_18C48[]; // minigame starting points
extern u8 lbl_3_data_189A4[];  // toy field turn counts
extern u8 lbl_3_data_18944[];
extern u8 lbl_3_data_21270[];
extern u8 lbl_3_data_18910[];                   // stadium ids, index into lbl_3_data_2130C
extern MinigameStageCamera lbl_3_data_2130C[];  // [stadium] / [minigame]
extern VecXYZ lbl_3_data_18E04[][4];            // actor offsets: [participants - 1][slot]
extern f32 lbl_3_data_18EC4[];                  // z offsets for winners / losers
extern s16 lbl_3_data_2137C;                    // frame the result jingle starts
extern s16 lbl_3_data_1899C[];                 // turn-over fade countdown: start, minimum
extern MinigamePointsAward lbl_3_data_18BB8[]; // indexed by turn result + 4 // per minigame: number of participants - 1
extern u8 lbl_3_data_18980[]; // AI strength of each CPU player

// NONMATCHING 95%: the fieldOrder fill loops address it as (&g_Minigame + 1 + n)->0x18F4 in the original
// (ours: pointer to fieldOrder[1]); r5/r6 swapped there
// .text:0x000DEB90 size:0x47C mapped:0x8071DC24
#if NONMATCHING
void fn_3_DEB90(void) {
    s32 pick;
    s32 i;
    s8 j;
    s8* list;

    g_Minigame._19C7 = 0;
    if (g_Minigame.toyField_turnNumber == 0) {
        // First turn: random pitcher among the non-batters.
        g_Minigame._19C7 = 1;
        pick = random_fn_3_9EE24(3);
        for (i = 0; i < 4; i++) {
            if (g_Minigame.rosterID != i) {
                if (pick == 0) {
                    g_Minigame.minigamePlayerSelectedOrder = i;
                    break;
                }
                pick--;
            }
        }
        list = &g_Minigame.minigameControlStruct[0].fieldOrder[1];
        for (i = 0; i < 4; i++) {
            if (g_Minigame.rosterID != i && g_Minigame.minigamePlayerSelectedOrder != i) {
                *list++ = i;
            }
        }
    } else {
        if ((u8)g_Minigame.rosterID == g_Minigame._19C6) {
            fn_3_59918(0x15, 0);
        } else {
            // The next batter must not pitch; otherwise the fielder who pitched least recently pitches.
            if (g_Minigame.minigameControlStruct[0].fieldOrder[1] == g_Minigame._19C6) {
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.minigameControlStruct[0].fieldOrder[2];
            } else if (g_Minigame.minigameControlStruct[0].fieldOrder[2] == g_Minigame._19C6) {
                g_Minigame.minigamePlayerSelectedOrder = g_Minigame.minigameControlStruct[0].fieldOrder[1];
            } else {
                u8 a = g_Minigame.roleStreak[g_Minigame.minigameControlStruct[0].fieldOrder[1]].count;
                u8 b = g_Minigame.roleStreak[g_Minigame.minigameControlStruct[0].fieldOrder[2]].count;
                if (a < b) {
                    g_Minigame.minigamePlayerSelectedOrder = g_Minigame.minigameControlStruct[0].fieldOrder[2];
                } else if (a > b) {
                    g_Minigame.minigamePlayerSelectedOrder = g_Minigame.minigameControlStruct[0].fieldOrder[1];
                } else {
                    pick = random_fn_3_9EE24(2) + 1;
                    g_Minigame.minigamePlayerSelectedOrder = g_Minigame.minigameControlStruct[0].fieldOrder[pick];
                }
            }
            g_Minigame.rosterID = g_Minigame._19C6;
            g_Minigame._19C7 = 1;
        }
        list = &g_Minigame.minigameControlStruct[0].fieldOrder[1];
        for (j = 0; j < 4; j++) {
            if (j != g_Minigame.minigamePlayerSelectedOrder && j != g_Minigame.rosterID) {
                *list++ = j;
            }
        }
    }

    g_Minigame.minigameControlStruct[0]._24[g_Minigame.rosterID] = 1;
    setInMemBatterConstants(g_Minigame.rosterID);
    g_Minigame._19C6 = g_Minigame.rosterID;
    g_Minigame.minigameControlStruct[0].fieldOrder[0] = g_Minigame.minigamePlayerSelectedOrder;

    g_Minigame.minigameControlStruct[0]._24[g_Minigame.minigamePlayerSelectedOrder] = 0;
    g_Minigame.minigameFielderIndex[g_Minigame.minigamePlayerSelectedOrder] = 0;
    g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame.minigamePlayerSelectedOrder]].rosterID =
        g_Minigame.minigameControlStruct[0].fieldOrder[0];

    g_Minigame.minigameControlStruct[0]._24[g_Minigame.minigameControlStruct[0].fieldOrder[1]] = 0;
    g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[1]] = 3;
    g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[1]]].rosterID =
        g_Minigame.minigameControlStruct[0].fieldOrder[1];

    g_Minigame.minigameControlStruct[0]._24[g_Minigame.minigameControlStruct[0].fieldOrder[2]] = 0;
    g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[2]] = 4;
    g_Fielders[g_Minigame.minigameFielderIndex[g_Minigame.minigameControlStruct[0].fieldOrder[2]]].rosterID =
        g_Minigame.minigameControlStruct[0].fieldOrder[2];

    // Track how many turns in a row each player has had the same role (0 pitcher, 1 batter, 2 fielder).
    for (i = 0; i < 4; i++) {
        if (g_Minigame.minigameControlStruct[0].fieldOrder[0] == i) {
            if (g_Minigame.roleStreak[i].role == 0) {
                if (g_Minigame.roleStreak[i].count < 0xFE) {
                    g_Minigame.roleStreak[i].count++;
                } else {
                    g_Minigame.roleStreak[i].count = 0xFF;
                }
            } else {
                g_Minigame.roleStreak[i].role = 0;
                g_Minigame.roleStreak[i].count = 1;
            }
        } else if (g_Minigame.rosterID == i) {
            if (g_Minigame.roleStreak[i].role == 1) {
                if (g_Minigame.roleStreak[i].count < 0xFE) {
                    g_Minigame.roleStreak[i].count++;
                } else {
                    g_Minigame.roleStreak[i].count = 0xFF;
                }
            } else {
                g_Minigame.roleStreak[i].role = 1;
                g_Minigame.roleStreak[i].count = 1;
            }
        } else if (g_Minigame.roleStreak[i].role == 2) {
            if (g_Minigame.roleStreak[i].count < 0xFE) {
                g_Minigame.roleStreak[i].count++;
            } else {
                g_Minigame.roleStreak[i].count = 0xFF;
            }
        } else {
            g_Minigame.roleStreak[i].role = 2;
            g_Minigame.roleStreak[i].count = 1;
        }
    }
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame.minigameControlStruct[0].turnOrder[0] = g_Minigame.rosterID;
    g_Minigame.minigameControlStruct[0].turnOrder[1] = g_Minigame.minigamePlayerSelectedOrder;
    g_Minigame.minigameControlStruct[0].turnOrder[2] = g_Minigame.minigameControlStruct[0].fieldOrder[1];
    g_Minigame.minigameControlStruct[0].turnOrder[3] = g_Minigame.minigameControlStruct[0].fieldOrder[2];
}
#endif

// .text:0x000DF00C size:0x250 mapped:0x8071E0A0
void fn_3_DF00C(void) {
    switch (g_GameLogic._125) {
    case 0:
        if (g_Minigame._19A6 == 1) {
            // sta_c6.h declares it s32, but the original only tests the low byte
            if ((u8)fn_3_E8AC8() == 0) {
                break;
            }
            g_Minigame._19A6 = 0;
        }
        if (g_Minigame._19A2 != 0) {
            g_Minigame._19A2--;
        }
        g_Minigame.minigameFielderIndex[0] = -1;
        g_Minigame.minigameFielderIndex[1] = -1;
        g_Minigame.minigameFielderIndex[2] = -1;
        g_Minigame.minigameFielderIndex[3] = -1;
        fn_3_DEB90();
        fn_3_F578();
        fn_3_753E8(0);
        setBatterContactConstants();
        fn_3_58E50();
        fn_3_2E87C();
        fn_3_1E154();
        fn_3_E1370(0);
        lbl_3_common_bss_32234._01 = 1;
        g_GameLogic.pre_PostMiniGameInd = 1;
        g_GameLogic.minigameLastTurnSuccessInd = 1;
        g_Strikes.strikes = 0;
        g_Strikes.balls = 0;
        lbl_803CBC3C._02 = 0;
        g_GameLogic._125++;
        break;
    case 1:
        if (g_Minigame._19C7 != 0) {
            if (someAnimationIndFunction() != 0) {
                lbl_3_common_bss_32234._01 = 1;
                g_GameLogic._125++;
            }
        } else {
            g_GameLogic._125++;
        }
        break;
    default:
        fn_3_DE744();
        if (++g_Minigame._190F == 1) {
            g_Minigame._1911 = 1;
        }
        if (g_Minigame.toyField_turnNumber < 0x7FFE) {
            g_Minigame.toyField_turnNumber++;
        } else {
            g_Minigame.toyField_turnNumber = 0x7FFF;
        }
        // Pick the next "coins x2" turn at the start of every 10 turns.
        if (g_Minigame.toyField_turnNumber < g_Minigame.toyField_selectedTurns &&
            g_Minigame.toyField_turnNumber % 10 == 1) {
            g_Minigame.toyField_next_CoinsX2_TurnNumber = random_fn_3_9EE24(6) + 4 + g_Minigame.toyField_turnNumber;
        }
        if (g_Minigame.toyField_next_CoinsX2_TurnNumber == g_Minigame.toyField_turnNumber) {
            g_Minigame.toyField_pointMultiplier = 2;
        } else {
            g_Minigame.toyField_pointMultiplier = 1;
        }
        break;
    }
}

// .text:0x000DF25C size:0x17C mapped:0x8071E2F0
void fn_3_DF25C(void) {
    s32 i;
    s32 pick;
    s32 slot;
    s32 n;
    s32 remaining;

    g_Scores._AC = fn_3_5C530(++g_Scores.inning);
    g_Strikes.outs = 0;
    g_Strikes.storedOuts = 0;
    lbl_3_common_bss_32724._D5 = 1;
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame._190D = 3;
    g_Minigame.panelHitInd = 0;
    g_Minigame._19A5 = 1;
    g_Minigame._190F = 0;
    g_Minigame._1910 = 3;
    g_Minigame._1911 = 0;
    g_Minigame._1914 = 0;
    g_Minigame._1915 = 0;
    g_Minigame._1916 = 0;
    g_Minigame._1917 = 0;
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        g_Minigame.minigameControlStruct[0]._18[i] = i;
    }

    // Shuffle the participants into a random turn order.
    remaining = g_Minigame.miniGameNumberOfParticipants;
    slot = 0;
    for (n = 0; n < g_Minigame.miniGameNumberOfParticipants; n++) {
        pick = random_fn_3_9EE24(remaining);
        for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
            if (g_Minigame.minigameControlStruct[0]._18[i] >= 0) {
                if (pick == 0) {
                    g_Minigame.minigameControlStruct[0].turnOrder[slot] = i;
                    g_Minigame.minigameControlStruct[0]._18[i] = -1;
                    remaining--;
                    slot++;
                    break;
                }
                pick--;
            }
        }
    }
    changeScene(1, 6);
    fn_3_5A6D4(3);
}

// .text:0x000DF3D8 size:0x230 mapped:0x8071E46C
void fn_3_DF3D8(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_E8AC8();
        fn_800203E0(7, 0);
        g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[g_Minigame._1A24[0]];
        if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
            g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[5];
        }
        lbl_8036E548._307E = 1;
        lbl_8036E548._2D8E = 0;
        lbl_8036E548._307A = 3;
        if (g_Minigame._190A != 0) {
            g_GameLogic._125 = 1;
        } else {
            fn_3_59B20();
            g_GameLogic._125 = 2;
        }
        break;
    case 1:
        fn_3_10C81C();
        if (g_Minigame._1A0F[0] < 0) {
            fn_3_59B20();
            g_GameLogic._125 = 2;
        }
        break;
    case 2:
        if (fn_3_59AE4() == 0) {
            break;
        }
        g_GameLogic._125 = 3;
    case 3:
        if (fn_80016F7C() != 0) {
            if (g_Minigame._1A38 != 0) {
                g_GameLogic._125 = 6;
            } else {
                g_GameLogic._125 = 4;
            }
            lbl_3_common_bss_34C58._2C = 0;
        }
        break;
    case 4:
        if (fn_3_90DD8() != 0) {
            g_GameLogic._125 = 6;
        }
        break;
    case 6:
        if (lbl_8037169C.done != 0 &&
            (g_GameLogic.FrameCountOfCurrentPitch >= 240 || fn_3_FD9FC() != 0) &&
            fn_3_6C938(1, 0x1300) != 0) {
            g_GameLogic._125 = 7;
        }
        break;
    case 7:
        changeScene(3, 6);
        if (lbl_8037169C._13 != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic._125 = 8;
        }
        break;
    case 8:
        fn_3_E1964();
        g_Minigame._1A38 = 0;
        g_Minigame._19A2 = 0;
        lbl_8036E548._307A = 1;
        fn_3_5A6D4(6);
        break;
    }
}

// NONMATCHING 96%: only scheduling, the lbz of g_d_GameSettings._35 is hoisted above `li r0,0` / the DATA lis
// .text:0x000DF608 size:0xCC mapped:0x8071E69C
#if NONMATCHING
void fn_3_DF608(void) {
    u8* aiStrength = lbl_3_data_18980;
    s32 i;

    g_Minigame._19DA[g_d_GameSettings._35] = 0;
    for (i = 0; i < 4; i++) {
        if (g_d_GameSettings._35 != i) {
            g_Minigame.minigameControlStruct[0].aIStrength[i] = *aiStrength++;
        }
    }
    g_Minigame.miniGameNumberOfParticipants = lbl_3_data_18944[g_Minigame.GameMode_MiniGame] + 1;
    g_Minigame._1907 = 1;
    g_Minigame.multiPlayerInd = 1;
    g_Scores.minigameRelated = 1;
}
#endif

// NONMATCHING 95%: inlines fn_3_DF608 (same scheduling issue); the tail g_d_GameSettings._35 load is also hoisted
// .text:0x000DF6D4 size:0x14C mapped:0x8071E768
#if NONMATCHING
void fn_3_DF6D4(void) {
    switch (g_GameLogic._125) {
    case 0:
        fn_3_DF608();
        g_GameLogic._125++;
    }
    g_Minigame._190A = 1;
    g_Minigame._19DA[g_d_GameSettings._35] = g_d_GameSettings._35;
    lbl_3_common_bss_37400.humanPlayer = g_d_GameSettings._35;
    g_Minigame.GameMode_MiniGame = g_d_GameSettings._33;
    g_Minigame._19DF = 30;
    fn_3_5A6D4(0x1B);
}
#endif

// .text:0x000DF820 size:0xB4 mapped:0x8071E8B4
void fn_3_DF820(void) {
    s32 i;

    fn_3_10C81C();
    for (i = 0; i < 4; i++) {
        if (g_Minigame._19E8[i]._0 != g_Minigame._19E8[i]._2) {
            break;
        }
    }
    if (i >= 4) {
        fn_3_5A6D4(0x1D);
    }
}

// .text:0x000DF8D4 size:0x14C mapped:0x8071E968
void fn_3_DF8D4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameCurrentPoints[i] = lbl_3_data_18C48[0];
        g_Minigame.minigameControlStruct[0]._1C[i] = 0;
        g_Minigame.minigameControlStruct[0].fieldOrder[i] = -1;
        g_Minigame.minigameFielderIndex[i] = -1;
        g_Minigame._18FC[i] = -1;
        g_Minigame.minigameControlStruct[0].turnOrder[i] = -1;
        g_Minigame.minigameControlStruct[0]._18[i] = i;
        g_Minigame.roleStreak[i].role = -1;
    }
    g_Minigame._1914 = 0;
    g_Minigame._1915 = 0;
    g_Minigame._1916 = 0;
    g_Minigame._1917 = 0;
    g_Minigame.turnNumberWithinRound = 0;
    g_Minigame._1939 = 0;
    g_Minigame._190D = 3;
    g_Minigame._19A6 = 0;
    g_Minigame.challenge_minigame_haven_tWonYetIndicator = 1;
    g_Minigame._19A9 = 0;
    g_Minigame._1911 = 0;
    g_Minigame.toyField_pointMultiplier = 1;
    g_Minigame.toyfield_waitFor_CoinsX2_AnimationToEnd = 0;
    g_Minigame._19CD = 0;
    g_Minigame._19CE = 0;
    g_Minigame._19CF = 0;
    g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[g_Minigame._1A24[0]];
    g_Minigame.toyField_turnNumber = 0;
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        g_Minigame.toyField_selectedTurns = lbl_3_data_189A4[5];
    }
    fn_3_754B8();
    initializeInMemBatter();
    fn_3_FBA8();
    fn_3_595C4();
    fn_3_1E328();
}

// .text:0x000DFA20 size:0x18C mapped:0x8071EAB4
void fn_3_DFA20(void) {
    s32 i;

    g_GameLogic.secondaryGameMode = 1;
    fn_800B0A5C_insertQueue(possiblyTransitionBlackScreen, 2);
    fn_800B0A5C_insertQueue(fn_3_5BAC, 4);
    g_d_GameSettings._33 = 0;
    g_Minigame.GameMode_MiniGame = 0;
    g_Minigame._19DF = 30;
    g_Minigame._1A2C = -1;
    g_Minigame._1A0C = -1;
    g_Minigame._19E6 = 2;
    g_Minigame._19E7 = 1;
    g_Minigame._1A3C = 0;
    g_Minigame._19A7 = lbl_3_data_21270[0];
    g_Minigame._1A38 = 0;
    g_Minigame._1A39 = 0;
    g_Minigame.battingHandedness[5] = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame._19DA[i] = -1;
        g_Minigame._19E8[i]._0 = -1;
        g_Minigame._19E8[i]._2 = -1;
        g_Minigame._19E8[i]._3 = -1;
        g_Minigame._1A0F[i] = -1;
        g_Minigame._19D2[i] = 20;
        g_Minigame._1A13[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        g_Minigame.minigameControlStruct[0].characterIndex[i] = -1;
        g_Minigame.minigameControlStruct[0].battingHandedness[i] = 0;
    }
    g_Minigame.miniGameNumberOfParticipants = 0;
    lbl_3_common_bss_34C58._30 = 0;
    fn_3_DF8D4();
    if (g_d_GameSettings.exhibitionMatchInd == FALSE) {
        g_Minigame._190A = 1;
        fn_3_5A6D4(0x25);
    } else {
        fn_3_5A6D4(0x1B);
    }
}

// NONMATCHING 77%: the original inlines fn_3_DF820 (case 27) and fn_3_DF6D4 (case 37), and reaches the .data tables
// (lbl_3_data_18980/18944/1899C/18BB8) through one pooled base lbl_3_data_188E8
// .text:0x000DFBAC size:0xABC mapped:0x8071EC40
#if NONMATCHING
void fn_3_DFBAC(void) {
    MinigamePointsAward* award;
    s32 i;
    u8 mult;

    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    g_Minigame._19A1 = 0;
    g_Minigame._1925 = 0;
    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameLatestPoints[i] = 0;
    }
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }

    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_DE744();
        break;
    case 1:
        // Pause: the first human player to press START.
        if (g_Pitcher.pitchTotalTimeCounter <= 0 && lbl_3_common_bss_34C90.active == 0) {
            for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
                if (g_Minigame.minigameControlStruct[0].characterIndex[i] >= 0 &&
                    g_Minigame.minigameControlStruct[0].battingHandedness[i] == 0 &&
                    (g_Controls[g_Minigame.minigameControlStruct[0].characterIndex[i]].newButtonInput & 0x1000)) {
                    lbl_3_common_bss_34C90.active = 1;
                    lbl_3_common_bss_34C90.team = g_Minigame.minigameControlStruct[0].characterIndex[i];
                    fn_3_AFD80(0);
                    fn_3_59918(0xE, 0);
                    break;
                }
            }
        }
        if (lbl_3_common_bss_34C90.active != 0) {
            if (lbl_3_common_bss_34C90.frames < 0x7FFE) {
                lbl_3_common_bss_34C90.frames++;
            } else {
                lbl_3_common_bss_34C90.frames = 0x7FFF;
            }
            lbl_803CBC3C._00 = 1;
            if (lbl_3_common_bss_34C90.frames > 60) {
                fn_3_AFD80(1);
                fn_3_5A6D4(0xB);
            } else {
                fn_3_2EA24();
            }
            break;
        }
        fn_3_75560();
        atBat_batter();
        fn_3_2EA24();
        if (g_Minigame.toyFieldBallStateResult2 == 0) {
            switch (g_Pitcher.strikeOutOrWalk) {
            case 0:
                break;
            case 1:
                g_Minigame.toyFieldBallStateResult2 = 2;
                break;
            case 2:
                g_Minigame.toyFieldBallStateResult2 = 7;
                break;
            default:
                g_Minigame.toyFieldBallStateResult2 = 8;
                break;
            }
        }
        if (g_Minigame.toyFieldBallStateResult2 != 0) {
            fn_3_DA834();
        }
        if (g_Minigame.turnOverStatus == 0) {
            break;
        }
        if (g_Minigame.turnOverStatus == 1) {
            g_Minigame.turnOverStatus = 2;
            g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[0];
        }
        g_GameLogic.CountdownUntilFade--;
        if (g_Minigame._19A0 != 0 && g_GameLogic.CountdownUntilFade < lbl_3_data_1899C[1]) {
            g_GameLogic.CountdownUntilFade = lbl_3_data_1899C[1];
        }
        if (g_GameLogic.CountdownUntilFade == lbl_3_data_1899C[1] - 10) {
            if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns &&
                g_Minigame.minigameControlStruct[0]._1C[g_Minigame.rosterID] == 1) {
                fn_3_59918(0xD, 0);
            } else if ((u8)g_Minigame.rosterID != g_Minigame._19C6) {
                if (g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
                    fn_3_59918(0xD, 0);
                } else {
                    fn_3_59918(5, 0);
                }
            }
        }
        if (g_GameLogic.CountdownUntilFade == 7) {
            changeScene(3, 6);
        }
        if (g_GameLogic.CountdownUntilFade <= 0) {
            if (g_Minigame._19CE != 0) {
                fn_3_FBD70();
                fn_3_FBD58();
            }
            g_GameLogic.hudLoadingRelated = 1;
            g_GameLogic.pre_PostMiniGameInd = 1;
            g_GameLogic.minigameLastTurnSuccessInd = 1;
            fn_3_1DD48();
            if (g_Minigame.pointsTargetReachedInd == 0) {
                fn_3_2E87C();
                fn_3_5A6D4(0);
            } else {
                fn_3_5A6D4(8);
            }
        }
        break;
    case 2:
        fn_3_DD9A4();
        break;
    case 3:
        fn_3_DD1A8();
        break;
    case 5:
        fn_3_DF3D8();
        break;
    case 6:
        fn_3_DF25C();
        break;
    case 7:
        fn_3_DF00C();
        break;
    case 8:
        g_Minigame.panelHitInd = 0;
        if (g_Minigame._19A6 != 0) {
            g_Minigame._19A6--;
            if (g_Pitcher.strikeOutOrWalk == 2 || g_Pitcher.strikeOutOrWalk == 3) {
                g_Minigame._19A6 = 3;
            }
        }
        g_Strikes.outs = 0;
        g_Strikes.storedOuts = 0;
        g_Minigame._19A5 = 1;
        if ((g_Minigame.rosterID != g_Minigame._19C6 ||
             g_Minigame.minigameControlStruct[0]._1C[g_Minigame.rosterID] == 1) &&
            g_Minigame.toyField_turnNumber >= g_Minigame.toyField_selectedTurns) {
            lbl_3_common_bss_34C90.subState = 0;
            fn_3_5A6D4(0xE);
        } else if (g_Minigame.toyField_turnNumber < g_Minigame.toyField_selectedTurns &&
                   g_Minigame.toyField_turnNumber % 10 == 0) {
            fn_3_5A6D4(3);
        } else {
            fn_3_5A6D4(7);
        }
        break;
    case 9:
        fn_3_DD000();
        break;
    case 11:
        fn_3_DCC80();
        break;
    case 13:
        lbl_803CBC3C._00 = 1;
        if (lbl_3_common_bss_34C90.subFrames < 0x7FFE) {
            lbl_3_common_bss_34C90.subFrames++;
        } else {
            lbl_3_common_bss_34C90.subFrames = 0x7FFF;
        }
        lbl_3_common_bss_34C90.heldButtons = g_Controls[lbl_3_common_bss_34C90.team].buttonInput;
        lbl_3_common_bss_34C90.newButtons = g_Controls[lbl_3_common_bss_34C90.team].newButtonInput;
        lbl_3_common_bss_34C90.repeatButtons = g_Controls[lbl_3_common_bss_34C90.team]._08;
        fn_3_ACAF8();
        break;
    case 14:
        fn_3_10A0A0();
        break;
    case 27:
        fn_3_DF820(); // inlined in the original
        break;
    case 29:
        fn_3_10F3D8();
        break;
    case 30:
        fn_3_10E60C();
        break;
    case 33:
        fn_3_10B8D0();
        break;
    case 34:
        fn_3_DC6E8();
        break;
    case 36:
        fn_3_109254();
        break;
    case 37:
        fn_3_DF6D4(); // inlined in the original
        break;
    }

    // Award this turn's points once.
    if (g_Minigame._19CD == 1) {
        award = &lbl_3_data_18BB8[g_Minigame._1921 + 4];
        if (g_Minigame._1921 + 4 == 20 || g_Minigame._1921 + 4 == 21) {
            mult = g_Minigame.toyField_pointMultiplier;
            g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] += mult * award->batter;
            g_Minigame.miniGameLatestPoints[g_Minigame.minigamePlayerSelectedOrder] += g_Minigame.toyField_pointMultiplier * award->pitcher;
            g_Minigame.miniGameLatestPoints[(u8)g_Fielders[g_Ball.fielderWBallIndex].rosterID] +=
                g_Minigame.toyField_pointMultiplier * award->fielder;
        } else {
            g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * award->batter;
            g_Minigame.miniGameLatestPoints[g_Minigame.minigamePlayerSelectedOrder] += g_Minigame.toyField_pointMultiplier * award->pitcher;
            g_Minigame.miniGameLatestPoints[g_Minigame.minigameControlStruct[0].fieldOrder[1]] +=
                g_Minigame.toyField_pointMultiplier * award->fielder;
            g_Minigame.miniGameLatestPoints[g_Minigame.minigameControlStruct[0].fieldOrder[2]] +=
                g_Minigame.toyField_pointMultiplier * award->fielder;
        }
        for (i = 0; i < 4; i++) {
            if (g_Minigame.miniGameLatestPoints[i] != 0) {
                g_Minigame.minigamePoints_current_Latest[i].current = g_Minigame.miniGameCurrentPoints[i];
                g_Minigame.minigamePoints_current_Latest[i].latest = g_Minigame.miniGameLatestPoints[i];
            }
        }
        g_Minigame._19CD = 2;
    }
    for (i = 0; i < 4; i++) {
        g_Minigame.miniGameCurrentPoints[i] += g_Minigame.miniGameLatestPoints[i];
        if (g_Minigame.miniGameCurrentPoints[i] > 999) {
            g_Minigame.miniGameCurrentPoints[i] = 999;
        }
        if (g_Minigame.miniGameCurrentPoints[i] < 0) {
            g_Minigame.miniGameCurrentPoints[i] = 0;
        }
    }
    if (lbl_3_common_bss_34C58._30 != 0) {
        lbl_3_common_bss_34C58._30--;
    }
    fn_3_DE4FC();
}
#endif

// .text:0x000E0668 size:0xF0 mapped:0x8071F6FC
void fn_3_E0668(void) {
    MinigameCoinSprite* coin;
    s32 i;

    for (i = 0; i < 30; i++) {
        coin = &lbl_8036E548.trail2[i];
        if (g_Minigame.wallBall_coinsVisibleInd[i] == 0) {
            coin->visible = 0;
        } else if (g_Minigame.wallBall_coinsVisibleFrameCounter > lbl_3_data_18BB0[g_Minigame._199E].blinkStart &&
                   (g_Minigame.wallBall_coinsVisibleFrameCounter & 1)) {
            coin->visible = 0;
        } else {
            coin->visible = 1;
            coin->x = g_Minigame.wallBall_coinCoordinates[i].x;
            coin->y = -g_Minigame.wallBall_coinCoordinates[i].y;
            coin->z = g_Minigame.wallBall_coinCoordinates[i].z;
            coin->angle = fn_3_9FEA8(coin->angle + lbl_3_data_18DD0);
        }
    }
}

// .text:0x000E0758 size:0x84 mapped:0x8071F7EC
void fn_3_E0758(void) {
    MinigameCoinSprite* coin;
    s32 i;

    for (i = 0; i < 30; i++) {
        coin = &lbl_8036E548.trail2[i];
        fn_8001D0D0(i, lbl_3_data_18D98[0]);
        coin->angle = shortAngleToRad_Capped(rand() % 4096);
    }
}

// NONMATCHING 94%: winner-list loops unrolled differently, list stores and register allocation differ
// .text:0x000E07DC size:0xA04 mapped:0x8071F870
#if NONMATCHING
void fn_3_E07DC(void) {
    s32 list[4];
    VecXYZ v;
    s32 hide;
    s32 n;
    s32 i;
    s32 best;
    s32 found;
    s32 notify;
    s32 allDone;
    u8 count;
    s32 placed;
    MinigameActorView* actor;
    MinigameStageCamera* cam;
    VecXYZ* offset;

    hide = 0;
    notify = 1;
    allDone = g_Minigame.challenge_minigame_haven_tWonYetIndicator;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if (g_GameLogic.gameStatus == 0xE && g_GameLogic._125 == 0) {
            hide = 1;
        }
    } else if (g_GameLogic.gameStatus == 0xE &&
               (g_GameLogic._125 < 4 || (g_GameLogic._125 == 4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 0))) {
        hide = 1;
    }
    if (g_GameLogic.gameStatus == 0xF || hide != 0) {
        for (i = 0; i < 4; i++) {
            if (lbl_8036E548.actors[i] != NULL) {
                lbl_8036E548.actors[i]->visible = 0;
            }
        }
        return;
    }

    if (g_GameLogic.gameStatus == 0x27) {
        allDone = 1;
        if (g_Minigame._1A3D == 1) {
            allDone = 0;
            if (g_Minigame._1E22[0] == g_Minigame._1E22[1] && g_Minigame._1E22[0] == g_Minigame._1E22[2] &&
                g_Minigame._1E22[0] == g_Minigame._1E22[3]) {
                allDone = 1;
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (g_Minigame.minigameControlStruct[0]._1C[i] != 1) {
                    allDone = 0;
                    break;
                }
            }
        }
    }

    found = 0;
    if (g_d_GameSettings.minigamesEnabled != 0) {
        if ((g_GameLogic.gameStatus == 0xE && g_GameLogic.FrameCountOfCurrentPitch == 1) ||
            (g_GameLogic.gameStatus == 0x27 && g_GameLogic.FrameCountOfCurrentPitch == 1)) {
            found = 1;
        }
    } else if (g_GameLogic.gameStatus == 0xE && g_GameLogic._125 == 4 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        found = 1;
    }
    if (found != 0) {
        // Build the list of winners to celebrate.
        n = 0;
        if (g_GameLogic.gameStatus == 0x27 || g_Minigame._1A3E != 0) {
            best = -1;
            for (i = 0; i < 4; i++) {
                if (g_Minigame._1E22[i] > best) {
                    best = g_Minigame._1E22[i];
                }
            }
            if (g_Minigame._1A3D == 1) {
                for (i = 0; i < 4; i++) {
                    if (g_Minigame.resultSlot[i].player == g_Minigame._1908 && g_Minigame.resultSlot[i].taken == 0) {
                        list[0] = g_Minigame._1908;
                        n = 1;
                        break;
                    }
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (g_Minigame._1E22[i] == best) {
                        list[n++] = i;
                    }
                }
            }
        } else if (g_d_GameSettings.minigamesEnabled == 0) {
            list[0] = 9;
            n = 1;
            if (lbl_80353A90._104 >= 2) {
                notify = 0;
            }
        } else if (g_Minigame.miniGameNumberOfParticipants > 1) {
            for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
                if (g_Minigame.minigameControlStruct[0]._1C[i] == 1) {
                    n++;
                    list[n - 1] = g_Minigame.minigameControlStruct[0].characterIndex[i];
                }
            }
            lbl_80353A90._104 = 0;
        } else if (g_Minigame.soloMinigameDifficulty == 3) {
            if (g_Minigame._1A43 == 1 || g_Minigame._19AA != 0) {
                n = 1;
                list[0] = g_Minigame.minigameControlStruct[0].characterIndex[0];
            }
        } else {
            list[0] = g_Minigame.minigameControlStruct[0].characterIndex[0];
            if (g_Minigame._1A37 == 1) {
                n = 1;
                lbl_80353A90._104 = 0;
            }
        }
        if (allDone == 0 || n == 1) {
            fn_3_14A070(list, n);
            if (notify != 0 && g_d_GameSettings.minigamesEnabled != 0) {
                if (n == 1) {
                    n = 2;
                    list[1] = list[0];
                } else if (n == 2) {
                    n = 4;
                    list[2] = list[0];
                    list[3] = list[1];
                }
                fn_3_15FA58(n, list);
            }
        }
    }

    if (allDone == 0 &&
        ((g_GameLogic.gameStatus == 0xE && g_GameLogic.FrameCountOfCurrentPitch == lbl_3_data_2137C &&
          lbl_80353A90._104 <= 1) ||
         (g_GameLogic.gameStatus == 0x27 && g_GameLogic.FrameCountOfCurrentPitch == lbl_3_data_2137C))) {
        found = 1;
        if (g_GameLogic.gameStatus == 0x27 && g_Minigame._1A3D == 1) {
            found = 0;
            for (i = 0; i < 4; i++) {
                if (g_Minigame.resultSlot[i].player == g_Minigame._1908 && g_Minigame.resultSlot[i].taken == 0) {
                    found = 1;
                    break;
                }
            }
        }
        if (found != 0) {
            if (g_d_GameSettings.minigamesEnabled != 0) {
                fn_3_15F9AC();
            }
            fn_3_149BA8();
        }
    }

    if (g_d_GameSettings.minigamesEnabled == 0) {
        // Exhibition: place the camera for this stadium.
        for (i = 0; i < 6; i++) {
            if (g_d_GameSettings.StadiumID == lbl_3_data_18910[i]) {
                break;
            }
        }
        lbl_8036E548._24BD = 1;
        cam = &lbl_3_data_2130C[i];
        fn_3_9F79C(cam->angle, cam->_0, cam->_8, &v.x, &v.z);
        v.y = lbl_3_data_2130C[i].y;
        lbl_8036E548.camera.y = v.y + lbl_3_data_18E04[0][0].y;
        lbl_8036E548.camera.x = v.x + lbl_3_data_18E04[0][0].x;
        lbl_8036E548.camera.z = v.z + lbl_3_data_18E04[0][0].z;
        lbl_8036E548.camera.y = -lbl_8036E548.camera.y;
        lbl_8036E548.cameraAngle = cam->angle;
        return;
    }

    // Minigame: line up the participants' actors.
    count = g_Minigame.miniGameNumberOfParticipants;
    placed = 0;
    for (i = 0; i < 4; i++) {
        actor = lbl_8036E548.actors[i];
        if (actor == NULL) {
            continue;
        }
        actor->visible = 0;
        if (g_GameLogic.gameStatus == 0x22 &&
            (lbl_3_common_bss_34C90.subState == 7 || g_GameLogic.framesOfExitingToMenu != 0)) {
            continue;
        }
        if (g_Minigame.minigameControlStruct[0].characterIndex[placed] != i) {
            continue;
        }
        if (g_Minigame._1A3D == 1) {
            if (g_Minigame.minigameControlStruct[0].characterIndex[i] != g_Minigame._1908) {
                continue;
            }
            count = 1;
        }
        actor->visible = 1;
        cam = &lbl_3_data_2130C[g_Minigame.GameMode_MiniGame];
        fn_3_9F79C(cam->angle, cam->_0, cam->_8, &v.x, &v.z);
        offset = &lbl_3_data_18E04[count - 1][placed];
        v.y = lbl_3_data_2130C[g_Minigame.GameMode_MiniGame].y;
        actor->pos.x = v.x + offset->x;
        actor->pos.y = v.y + offset->y;
        actor->pos.z = v.z + offset->z;
        actor->pos.y = -actor->pos.y;
        actor->rotY = lbl_3_data_2130C[g_Minigame.GameMode_MiniGame].angle;
        if (g_GameLogic.gameStatus == 0x27 || g_Minigame._1A3E != 0) {
            if (g_Minigame._1A3D > 1) {
                if (g_Minigame.minigameControlStruct[0]._1C[i] == 1) {
                    actor->pos.z += lbl_3_data_18EC4[0];
                } else {
                    actor->pos.z += lbl_3_data_18EC4[2];
                }
            }
        } else if (allDone != 0) {
            if (g_Minigame.minigameControlStruct[0].charID[i] == 0x26) {
                actor->pos.z += lbl_3_data_18EC4[1];
            } else {
                actor->pos.z += lbl_3_data_18EC4[0];
            }
        } else if (g_Minigame.minigameControlStruct[0]._20[i] == 1) {
            actor->pos.z += lbl_3_data_18EC4[0];
        } else {
            actor->pos.z += lbl_3_data_18EC4[2];
        }
        placed++;
    }
}
#endif
