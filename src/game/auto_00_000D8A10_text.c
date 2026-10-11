#include "game/auto_00_000D8A10_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_1838.h"
#include "musyx/musyx.h"
#include <stdlib.h>
#include "game/auto_00_000DEB90_text.h"

extern MinigameBss37400View lbl_3_common_bss_37400;
extern u8 lbl_800EF808[];          // TODO type: options block (0x398: sound/rumble setting)
extern u16 lbl_3_data_81DC[];      // per stadium: crowd sound id base
extern MinigameSoundParams lbl_3_data_8404[];
extern MinigameSoundParams lbl_3_data_84B8[];

static inline void playCrowdSound(s32 n) {
    s32 stadium;
    u8 vol;
    SND_VOICEID voice;

    stadium = g_d_GameSettings.StadiumID;
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].vol;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].vol;
    }
    voice = sndFXStartEx(lbl_3_data_81DC[stadium] + n, vol, 0x3F, 0);
    if (g_d_GameSettings.GameModeSelected == 6) {
        vol = lbl_3_data_84B8[n].ctrl;
    } else {
        vol = lbl_3_data_8404[stadium * 15 + n].ctrl;
    }
    sndFXCtrl(voice, 0x5B, vol);
}
extern MinigamePointsAward lbl_3_data_18BB8[];
extern s16 lbl_3_data_18C48[];
extern s16 lbl_3_data_189AC[];             // [10] near-miss chance, [11] jackpot chance (percent)
extern MinigameSlotData lbl_3_data_189C4;

// .text:0x000D8A10 size:0x2C0 mapped:0x80717AA4
void fn_3_D8A10(void) {
    s32 i;

    if (g_Minigame._19CE == 1) {
        g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[12].batter;
        g_Minigame.miniGameLatestPoints[g_Minigame.minigamePlayerSelectedOrder] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[12].pitcher;
        g_Minigame.miniGameLatestPoints[g_Minigame.minigameControlStruct[0].fieldOrder[1]] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[12].fielder;
        g_Minigame.miniGameLatestPoints[g_Minigame.minigameControlStruct[0].fieldOrder[2]] +=
            g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[12].fielder;
        for (i = 0; i < 4; i++) {
            if (g_Minigame.miniGameLatestPoints[i] != 0) {
                g_Minigame.minigamePoints_current_Latest[i].current = g_Minigame.miniGameCurrentPoints[i];
                g_Minigame.minigamePoints_current_Latest[i].latest = g_Minigame.miniGameLatestPoints[i];
            }
        }
        g_Minigame._19BA = 0;
        g_Minigame._19CE = 2;
        // TODO type: _1914.._1917 and _1918.._191B are per-player u8[4] arrays
        for (i = 0; i < 4; i++) {
            if ((&g_Minigame._1918)[i] != 0) {
                (&g_Minigame._1914)[i] = 0;
            }
        }
        if (lbl_800EF808[0x398] == 1) {
            playCrowdSound(26);
        }
    }
    if (g_Minigame._19BA < 0x7FFE) {
        g_Minigame._19BA++;
    } else {
        g_Minigame._19BA = 0x7FFF;
    }
    if (g_Minigame._19BA > lbl_3_data_18C48[3]) {
        g_Minigame._19CE = 3;
    }
}

// .text:0x000D8CD0 size:0xB98 mapped:0x80717D64
static inline void awardTurnPoints(s32 row) {
    g_Minigame.miniGameLatestPoints[g_Minigame.rosterID] += g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[row].batter;
    g_Minigame.miniGameLatestPoints[g_Minigame.minigamePlayerSelectedOrder] +=
        g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[row].pitcher;
    g_Minigame.miniGameLatestPoints[g_Minigame.minigameControlStruct[0].fieldOrder[1]] +=
        g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[row].fielder;
    g_Minigame.miniGameLatestPoints[g_Minigame.minigameControlStruct[0].fieldOrder[2]] +=
        g_Minigame.toyField_pointMultiplier * lbl_3_data_18BB8[row].fielder;
}

static inline void snapshotPoints(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_Minigame.miniGameLatestPoints[i] != 0) {
            g_Minigame.minigamePoints_current_Latest[i].current = g_Minigame.miniGameCurrentPoints[i];
            g_Minigame.minigamePoints_current_Latest[i].latest = g_Minigame.miniGameLatestPoints[i];
        }
    }
}

void fn_3_D8CD0(void) {
    s32 k;
    s32 amount;
    s16 tmp;

    g_Minigame._18BA = 0;
    if (g_Minigame._192D == 0 || (u8)(g_Minigame._192D - 3) <= 1 || g_Minigame._192D == 5) {
        switch (g_Minigame._192D) {
        case 0:
            // The batter takes points from everyone else.
            g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[0]] = 0;
            k = 1;
            do {
                amount = lbl_3_data_18BB8[15].batter * g_Minigame.toyField_pointMultiplier;
                if (g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[k]] < amount) {
                    amount = g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[k]];
                }
                g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[0]] += amount;
                g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[k]] = -amount;
            } while (++k < g_Minigame.miniGameNumberOfParticipants);
            playCrowdSound(1);
            break;
        case 3:
            amount = lbl_3_data_18BB8[13].batter * g_Minigame.toyField_pointMultiplier;
            if (g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[1]] < amount) {
                amount = g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[1]];
            }
            g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[0]] = amount;
            g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[1]] = -amount;
            playCrowdSound(1);
            break;
        case 4:
            amount = lbl_3_data_18BB8[14].batter * g_Minigame.toyField_pointMultiplier;
            if (g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[1]] < amount) {
                amount = g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[1]];
            }
            g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[0]] = amount;
            g_Minigame.miniGameLatestPoints[g_Minigame.playerOrder[1]] = -amount;
            playCrowdSound(1);
            break;
        case 5:
            // Swap scores.
            tmp = g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[0]];
            g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[0]] =
                g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[1]];
            g_Minigame.miniGameCurrentPoints[g_Minigame.playerOrder[1]] = tmp;
            playCrowdSound(10);
            break;
        }
        if (g_Minigame._192D != 5) {
            snapshotPoints();
        }
    } else {
        if (g_Minigame._192D == 7) {
            g_Minigame.toyFieldBallStateResult2 = 2;
            playCrowdSound(9);
            awardTurnPoints(18);
            snapshotPoints();
        } else if (g_Minigame._192D == 2) {
            g_Minigame._19A2 = 2;
            g_Minigame._19C6 = g_Minigame.rosterID;
            playCrowdSound(5);
            awardTurnPoints(16);
            snapshotPoints();
            g_Minigame._1915 = 1;
            g_Minigame._1916 = 1;
            g_Minigame._1917 = 1;
        } else if (g_Minigame._192D == 6) {
            g_Minigame._19C6 = g_Minigame.rosterID;
            playCrowdSound(11);
            awardTurnPoints(17);
            snapshotPoints();
        }
    }
    g_Minigame.turnOverStatus = 1;
    if (g_Minigame._192D == 7 || g_Minigame._192D == 8) {
        g_Strikes.outs++;
        fn_3_59918(1, 0);
        if (g_Minigame.rosterID == g_Minigame._19C6) {
            g_Minigame._19C6 = g_Minigame.minigamePlayerSelectedOrder;
        }
    }
    if (g_Minigame._192D == 2) {
        g_Minigame._1910 = g_Minigame._190D;
    } else {
        g_Minigame.pointsTargetReachedInd = 1;
    }
}

// NONMATCHING 98%: second count loop: original does `li r3,0; mr r6,r3` (we get two li) and loads the count later
// .text:0x000D9868 size:0x1C8 mapped:0x807188FC
#if NONMATCHING
void fn_3_D9868(void) {
    u8 players[4][2]; // [i][0] player, [i][1] flag
    u32 count;
    u32 i;
    u32 k;
    u32 n;

    fn_3_1079C8(&players[0][0], 0);
    count = 0;
    i = 0;
    do {
        if (players[i][1] == 0) {
            count++;
        }
    } while (++i < g_Minigame.miniGameNumberOfParticipants);
    switch (g_Minigame._192D) {
    case 0:
        i = 0;
        k = 1;
        g_Minigame.playerOrder[0] = g_Minigame.rosterID;
        do {
            if (i != g_Minigame.rosterID) {
                g_Minigame.playerOrder[k++] = i;
            }
        } while (++i < g_Minigame.miniGameNumberOfParticipants);
        break;
    case 3:
        g_Minigame.playerOrder[0] = g_Minigame.rosterID;
        do {
            g_Minigame.playerOrder[1] = random_fn_3_9EE24(g_Minigame.miniGameNumberOfParticipants);
        } while (g_Minigame.playerOrder[1] == g_Minigame.playerOrder[0]);
        break;
    case 4:
    case 5:
        g_Minigame.playerOrder[0] = g_Minigame.rosterID;
        if (count == 1 && players[0][0] == g_Minigame.playerOrder[0]) {
            n = 0;
            i = n;
            do {
                if (players[i][1] == 1) {
                    n++;
                }
            } while (++i < g_Minigame.miniGameNumberOfParticipants);
            g_Minigame.playerOrder[1] = players[random_fn_3_9EE24(n) + 1][0];
        } else {
            do {
                g_Minigame.playerOrder[1] = players[random_fn_3_9EE24(count)][0];
            } while (g_Minigame.playerOrder[1] == g_Minigame.playerOrder[0]);
        }
        break;
    }
}
#endif

// NONMATCHING 92%: the original reaches lbl_3_data_189AC/189C4 through one pooled base (lbl_3_data_188E8), which
// shifts register allocation
// .text:0x000D9A30 size:0x470 mapped:0x80718AC4
#if NONMATCHING
void fn_3_D9A30(void) {
    s32 progress;
    s32 standing;
    s32 nearMiss;
    s32 third;
    s32 flags;
    s32 i;
    s32 r;
    s32 k;
    s16 myPoints;

    progress = 0;
    standing = 1;
    nearMiss = 0;
    third = g_Minigame.toyField_selectedTurns / 3;
    if (third * 2 > g_Minigame.toyField_turnNumber) {
        progress = 2;
    } else if (third > g_Minigame.toyField_turnNumber) {
        progress = 1;
    }

    // Is the batter behind (bit 0) and/or ahead of (bit 4) anyone?
    flags = 0;
    myPoints = g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID];
    for (i = 0; i < g_Minigame.miniGameNumberOfParticipants; i++) {
        if (i != g_Minigame.rosterID) {
            if (myPoints < g_Minigame.miniGameCurrentPoints[i]) {
                flags |= 1;
            }
            if (myPoints > g_Minigame.miniGameCurrentPoints[i]) {
                flags |= 0x10;
            }
        }
    }
    if (!(flags & 1)) {
        standing = 0;
    } else if (!(flags & 0x10)) {
        standing = 2;
    }

    g_Minigame._192D = RandomIndexFromWeights(
        lbl_3_data_189C4.weights[g_Minigame.miniGameNumberOfParticipants - 2][progress][standing], 8);
    if (g_d_GameSettings.exhibitionMatchInd == FALSE && g_Minigame.rosterID == lbl_3_common_bss_37400.humanPlayer) {
        fn_3_1608F0(7, 0, 0);
    }
    if (g_Minigame._192D == 7) {
        if (g_Minigame._1915 == 0 && g_Minigame._1916 == 0 && g_Minigame._1917 == 0) {
            g_Minigame._192D = 8;
        } else if (rand() % 100 < lbl_3_data_189AC[11]) {
            g_Minigame._192D = 8;
        }
        if (g_Minigame._192D == 8 && rand() % 99 < lbl_3_data_189AC[10]) {
            nearMiss = 1;
        }
    }

    for (r = 0; r < 3; r++) {
        g_Minigame.reelStart[r] = random_fn_3_9EE24(7);
        g_Minigame.reelStop[r] = 0;
        if (g_Minigame._192D == 8) {
            if (nearMiss != 0) {
                // Two matching symbols, the third one off by one.
                if (r == 0) {
                    g_Minigame.reelSymbol[0] = lbl_3_data_189C4.reels[r][random_fn_3_9EE24(7)];
                } else if (r == 1) {
                    g_Minigame.reelSymbol[1] = g_Minigame.reelSymbol[0];
                } else {
                    for (k = 0; k < 7; k++) {
                        if (g_Minigame.reelSymbol[0] == lbl_3_data_189C4.reels[2][k]) {
                            break;
                        }
                    }
                    if (++k >= 7) {
                        k = 0;
                    }
                    g_Minigame.reelSymbol[2] = lbl_3_data_189C4.reels[2][k];
                }
            } else {
                g_Minigame.reelSymbol[r] = lbl_3_data_189C4.reels[r][random_fn_3_9EE24(7)];
                if (r == 2 && g_Minigame.reelSymbol[0] == g_Minigame.reelSymbol[1] &&
                    g_Minigame.reelSymbol[0] == g_Minigame.reelSymbol[2]) {
                    // Avoid an accidental jackpot.
                    for (k = 0; k < 7; k++) {
                        if (g_Minigame.reelSymbol[2] == lbl_3_data_189C4.reels[2][k]) {
                            break;
                        }
                    }
                    if (++k >= 7) {
                        k = 0;
                    }
                    g_Minigame.reelSymbol[2] = lbl_3_data_189C4.reels[2][k];
                }
            }
        } else {
            g_Minigame.reelSymbol[r] = g_Minigame._192D;
        }
    }
    g_Minigame._18B8 = 0;
}
#endif
