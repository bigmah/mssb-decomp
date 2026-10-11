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
#include "game/rep_2940.h"
#include "game/rep_28A8.h"
#include "game/sta_c6.h"
#include <stdlib.h>

extern void possiblyTransitionBlackScreen(void);

extern f32 lbl_3_data_18D98[];
extern MinigameCoinTiming lbl_3_data_18BB0[];
extern f32 lbl_3_data_18DD0; // coin spin per frame
extern s16 lbl_3_data_18C48[]; // minigame starting points
extern u8 lbl_3_data_189A4[];  // toy field turn counts
extern u8 lbl_3_data_18944[];
extern u8 lbl_3_data_21270[]; // per minigame: number of participants - 1
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
    return;
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

// .text:0x000DFBAC size:0xABC mapped:0x8071EC40
void fn_3_DFBAC(void) {
    return;
}

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

// .text:0x000E07DC size:0xA04 mapped:0x8071F870
void fn_3_E07DC(void) {
    return;
}
