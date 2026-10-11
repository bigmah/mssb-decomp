#include "game/auto_00_00114FC0_text.h"
#include "game/auto_00_0005985C_text.h"
#include "game/auto_00_00113398_text.h"

extern u8 g_GameLogic[];
extern u8 g_Minigame[];
extern u8 g_Scores[];
extern u8 lbl_8036E548[];
extern u8 lbl_800EFBA4[];
extern s32 sndFXStartEx(s32, u8, u8, u8);
extern void fn_3_114A88(s32);
extern void changeScene(s32, s32);
extern s32 fn_3_6C938(s32, s32);
extern void fn_3_FBD70(void);
extern void fn_3_FBD58(void);
extern s16 lbl_3_data_18C48[];
extern u8 lbl_8037169C[];
extern void fn_3_F578(void);
extern void fn_3_753E8(s32);
extern u8 g_Batter[];
extern u8 lbl_3_data_21BC4[];
extern f32 lbl_3_data_226C4[];
extern void fn_3_11881C(void);
extern void fn_8001D110(s32 i, f32 a, f32 b, f32 c);
extern u8 g_Ball[];
extern f32 maybeInitialBatPos[];
extern s16 lbl_3_data_2167C[]; // [0] turn-over delay, [2] frame limit, [4] coin lifetime
extern void fn_3_6EBB4(s32);
extern void fn_3_F1DC(void);
extern void fn_3_751B4(void);
extern void fn_3_58870(void);
extern void fn_3_DE4FC(void);
extern void fn_3_10F550(s32, s32);
extern void Set_803cb848(s32);
extern void* memset(void*, s32, u32);
extern u8 g_FieldingLogic[];
extern u8 unkSimulationRelatedStruct[];
extern WallBallPitcherView g_Pitcher;
extern WallBallFielderView g_Fielders[];
extern u8 g_d_GameSettings[];
extern u8 lbl_3_common_bss_32234[];
extern u8 lbl_3_common_bss_37400[];
extern WallBallCoinPhysics lbl_3_data_21634;
extern f32 lbl_3_data_219B8[];      // [14]: coin floor height
extern s16 lbl_3_data_21654[];      // [10]: bonus points per hit
extern u8 lbl_3_data_21671;         // max rounds
extern s16 lbl_3_data_21672;        // last-round point multiplier
extern u8 lbl_3_data_2127C[][5];    // AI strength per [game mode][difficulty]
extern u8 lbl_3_data_2166C[];       // rounds per difficulty
extern s32 fn_3_108854(void);
extern void fn_3_1133C4(void);
extern void fn_3_113A48(void);
extern void fn_3_113D20(void);
extern void fn_3_113F14(void);
extern void fn_3_114204(void);
extern void fn_3_114384(void);
extern void fn_3_1500C8(void);
extern void fn_3_2EA24(void);
extern void fn_3_75560(void);
extern void fn_3_1608F0(s32 type, s32 value, s32 flag);
extern void fn_3_59A90(void);
extern void minigamesSetSomePointers(void);
extern void minigamesGXStuff(void);
extern void minigamesSetSomePointers2(void);
extern void fn_3_F8ABC(void);

#define WB ((WallBallView*)g_Minigame)
#define SCORES ((WallBallScoresView*)g_Scores)


// fn_3_114FC0, size:0x6C
void fn_3_114FC0(void) {
    g_GameLogic[0x12B] = 1;
    g_GameLogic[0x12C] = 1;
    g_GameLogic[0x12E] = 1;
    g_Minigame[0x190C]++;
    if (g_Minigame[0x190C] >= g_Minigame[0x1906]) {
        fn_3_5A6D4(0x19);
        return;
    }
    fn_3_5A6D4(7);
}

// fn_3_11502C, size:0xDC
void fn_3_11502C(void) {
    if (g_Minigame[0x190B] == 1) {
        g_Minigame[0x190B] = 2;
        *(s16*)(g_GameLogic + 0x100) = lbl_3_data_2167C[0];
    }
    *(s16*)(g_GameLogic + 0x100) -= 1;
    if (*(s16*)(g_GameLogic + 0x100) == 7) {
        changeScene(3, 6);
    }
    if (*(s16*)(g_GameLogic + 0x100) <= 0) {
        g_GameLogic[0x12B] = 1;
        g_GameLogic[0x12C] = 1;
        g_GameLogic[0x12E] = 1;
        g_Minigame[0x190C]++;
        if (g_Minigame[0x190C] >= g_Minigame[0x1906]) {
            fn_3_5A6D4(0x19);
            return;
        }
        fn_3_5A6D4(7);
    }
}

// Same as fn_3_113398 (inlined here).
static inline void WallBall_ClearFlags(void) {
    s8 i;

    i = 0;
    do {
        ((MG1133View*)g_Minigame)->flag[i] = 0;
        i++;
    } while (i < 4);
}

static inline void WallBall_UpdateCoins(void) {
    s32 c;
    s16 lifetime;
    f32 friction;
    f32 bounce;
    f32 floorY;
    f32 gravity;

    gravity = lbl_3_data_21634.gravity;
    floorY = lbl_3_data_219B8[14];
    bounce = lbl_3_data_21634.bounce;
    friction = lbl_3_data_21634.friction;
    lifetime = lbl_3_data_2167C[4];

    for (c = 0; c < 100; c++) {
        if (WB->coinVisible[c] != 0) {
            WB->coinFrames[c]++;
            WB->coinPos[c].x += WB->coinVel[c].x;
            WB->coinPos[c].y += WB->coinVel[c].y;
            WB->coinPos[c].z += WB->coinVel[c].z;
            WB->coinVel[c].y -= gravity;
            if (WB->coinPos[c].y < floorY) {
                WB->coinPos[c].y = floorY;
                WB->coinVel[c].y = -WB->coinVel[c].y * bounce;
                WB->coinVel[c].x *= friction;
                WB->coinVel[c].z *= friction;
            }
            if (WB->coinFrames[c] > lifetime) {
                WB->coinVisible[c] = 0;
            }
        }
    }
}

// fn_3_115108, size:0x438
// End of a Wall Ball turn: award points, advance the turn and the round.
// NONMATCHING 98%: &currentPoints[player] is kept as a pointer (extra addi) and two scratch regs swap at the turn update
#if NONMATCHING
void fn_3_115108(void) {
    s32 points;
    s16 mult;
    s16 half;
    s32 share;
    s16 i;
    s32 over;
    u8 turn;

    over = 0;
    if (g_Pitcher.pitcherActionState == 4) {
        if (g_Pitcher.currentStateFrameCounter > 0x4A) {
            over = 1;
        } else if (WB->difficulty == 3 && g_Pitcher.currentStateFrameCounter == 0x4A) {
            WB->_1A8C = 1;
        }
    } else if (WB->frames > lbl_3_data_2167C[2]) {
        over = 1;
    } else if (WB->difficulty == 3 && WB->frames == lbl_3_data_2167C[2]) {
        WB->_1A8C = 1;
    }
    if (over == 0) {
        return;
    }

    if (WB->_1A8A == 0) {
        mult = 1;
        if ((WB->multiPlayerInd != 0 || WB->_1A3C != 0 || WB->difficulty != 3) && SCORES->round == SCORES->lastRound) {
            mult = lbl_3_data_21672;
        }
        if (WB->_1A89 == 1) {
            points = WB->bonus + lbl_3_data_21654[10] * mult;
            WB->currentPoints[WB->currentPlayer] += points;
            WB->bonus = 0;
        } else {
            points = WB->latestPoints[WB->currentPlayer] * mult;
            WB->currentPoints[WB->currentPlayer] += points;
        }
    } else {
        points = 0;
        if (WB->multiPlayerInd != 0 || WB->_1A3C != 0 || WB->difficulty != 3) {
            half = WB->currentPoints[WB->currentPlayer] / 2;
            WB->currentPoints[WB->currentPlayer] -= half;
            share = half / 3;
            for (i = 0; i < 4; i++) {
                if (i != WB->currentPlayer) {
                    WB->currentPoints[i] += share;
                }
            }
            points = -half;
        }
    }
    if (g_d_GameSettings[8] == 0 && WB->currentPlayer == *(s16*)(lbl_3_common_bss_37400 + 0x40)) { // TODO type
        fn_3_1608F0(1, points, WB->_1A89);
    }

    turn = WB->turnNumberWithinRound + 1;
    WB->pitcherX = g_Pitcher.x;
    WB->pitcherZ = g_Pitcher.z;
    WB->turnNumberWithinRound = turn;
    if (turn >= WB->numParticipants) {
        WB->turnNumberWithinRound = turn - WB->numParticipants;
        SCORES->round++;
        if (WB->multiPlayerInd == 0 && WB->_1A3C == 0 && WB->difficulty == 3) {
            SCORES->round--;
            if (WB->_1A89 == 1) {
                if (SCORES->lastRound < lbl_3_data_21671) {
                    SCORES->lastRound++;
                }
            } else {
                SCORES->lastRound--;
                if (WB->_1A8A != 0) {
                    for (i = 0; i < 1; i++) {
                        if (SCORES->lastRound == 0) {
                            break;
                        }
                        SCORES->lastRound--;
                    }
                }
            }
        }
    }
    fn_3_1500C8();
    if (SCORES->round > SCORES->lastRound) {
        sndFXStartEx(0x1BE, lbl_800EFBA4[7], 0x3F, 0);
        fn_3_5A6D4(0xF);
        return;
    }
    WB->phase = 0;
    fn_3_5A6D4(7);
    if ((WB->multiPlayerInd != 0 || WB->_1A3C != 0 || WB->difficulty != 3) && WB->turnNumberWithinRound == 0) {
        fn_3_10F550(4, 0);
    }
}
#endif

// fn_3_115540, size:0x1F8
// Per-frame update while the ball is in play: phase logic and the coin physics.
// NONMATCHING 91%: coin loop: g_Minigame base is materialised after the constant tables, walker regs shifted by one
#if NONMATCHING
void fn_3_115540(void) {
    if (fn_3_108854() != 0) {
        return;
    }
    if (WB->_1A7E != 0) {
        fn_3_114A88(0);
    } else if (WB->phase == 2) {
        fn_3_1133C4();
        fn_3_75560();
        WallBall_ClearFlags();
        fn_3_113A48();
    }
    if (WB->counting != 0) {
        if (WB->frames < 0x7FFE) {
            WB->frames++;
        } else {
            WB->frames = 0x7FFF;
        }
    }
    fn_3_2EA24();
    if (WB->phase == 0) {
        fn_3_114384();
        fn_3_1500C8();
    } else if (WB->phase == 1) {
        fn_3_114204();
    } else if (WB->phase == 2) {
        fn_3_113F14();
        fn_3_113D20();
    }
    WallBall_UpdateCoins();
    fn_3_115108();
}
#endif

// fn_3_115738, size:0xF0
void fn_3_115738(void) {
    switch (g_GameLogic[0x125]) {
    case 0:
        changeScene(1, 6);
        g_GameLogic[0x125] = 1;
        break;
    case 1:
        if (*(u16*)(g_GameLogic + 0xFC) >= lbl_3_data_18C48[2] ||
            (*(u16*)(g_GameLogic + 0xFC) >= lbl_3_data_18C48[1] && fn_3_6C938(1, 0x1100) != 0)) {
            changeScene(3, 6);
            g_GameLogic[0x125] = 2;
        }
        break;
    case 2:
        if (lbl_8037169C[0x13] != 0) {
            fn_3_FBD70();
            fn_3_FBD58();
            g_GameLogic[0x125] = 3;
        }
        break;
    case 3:
        fn_3_5A6D4(7);
        break;
    }
}

// fn_3_115828, size:0x88
void fn_3_115828(void) {
    fn_3_DE4FC();
    if (g_Minigame[0x1A2B] <= 2 && g_Minigame[0x1909] == 0) {
        if (g_Minigame[*(s8*)(g_Minigame + 0x1908) + 0x18E8] == 1 && g_Minigame[0x19A8] == 0) {
            g_Minigame[0x1A37] = 1;
        } else {
            g_Minigame[0x1A37] = 2;
        }
    }
    fn_3_5A6D4(0xE);
}

// fn_3_1158B0, size:0x48
void fn_3_1158B0(void) {
    if (*(s32*)g_Scores >= (s32)g_Scores[0xAA]) {
        fn_3_5A6D4(0xF);
        return;
    }
    fn_3_5A6D4(6);
}

// fn_3_1158F8, size:0x80
void fn_3_1158F8(void) {
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    fn_3_F1DC();
    fn_3_751B4();
    fn_3_58870();
    memset(g_Minigame + 0x1D7C, 0, 0x78);
    Set_803cb848(1);
    *(s16*)(g_FieldingLogic + 0xAE) = 0;
    unkSimulationRelatedStruct[5] = 0;
    unkSimulationRelatedStruct[6] = 4;
}

// fn_3_115978, size:0x13C
void fn_3_115978(void) {
    fn_3_1158F8();
    g_Minigame[0x190B] = 0;
    g_Minigame[0x1A81] = 0;
    *(s16*)(g_Minigame + 0x1A72) = 0;
    *(s16*)(g_Minigame + 0x1A74) = 0;
    *(s16*)(g_Minigame + 0x1A76) = 0;
    g_Minigame[0x1A89] = 0;
    g_Minigame[0x1A8A] = 0;
    ((s8*)g_Minigame)[0x1A8B] = -1;
    *(s16*)(g_Ball + 0x1B64) = 0;
    if (g_Minigame[0x1A2D] == 0) {
        if (g_GameLogic[0x12B] != 0) {
            g_GameLogic[0x12C] = 1;
            g_GameLogic[0x12D] = 1;
        } else {
            g_GameLogic[0x12C] = 0;
        }
        g_GameLogic[0x12B] = 0;
    } else if (g_Minigame[0x1A2B] != 3) {
        *(s16*)(g_Minigame + 0x1A70) = 0;
        g_Minigame[0x1A7E] = 1;
        fn_3_114A88(0);
    } else {
        g_GameLogic[0x12C] = 0;
    }
    changeScene(1, 6);
    fn_3_5A6D4(1);
}

// fn_3_115AB4, size:0xA8
void fn_3_115AB4(void) {
 u8 t;
t = g_Minigame[g_Minigame[0x190C] + 0x18E0]; g_Minigame[0x1904] = t;
g_GameLogic[0x12B] = 1;
*(s16*)(g_Minigame + 0x1898) = 0; *(s16*)(g_Minigame + 0x189A) = 0; *(s16*)(g_Minigame + 0x189C) = 0; *(s16*)(g_Minigame + 0x189E) = 0;
    fn_3_F578();
    fn_3_753E8(0);
    fn_3_6EBB4(*(s8*)(g_Minigame + 0x1904));
    *(f32*)(g_Batter + 0x4C) = maybeInitialBatPos[0];
    *(f32*)(g_Batter + 0x50) = maybeInitialBatPos[1];
    *(f32*)(g_Batter + 0x54) = maybeInitialBatPos[2];
    fn_3_5A6D4(0);
}

// fn_3_115B5C, size:0x80
void fn_3_115B5C(void) {
    *(s32*)g_Scores += 1;
    g_Minigame[0x190C] = 0;
    fn_3_5A6D4(7);
    if (g_Minigame[0x1909] != 0 || g_Minigame[0x1A3C] != 0 || g_Minigame[0x1A2B] != 3) {
        fn_3_10F550(4, 0);
    }
}

// fn_3_115BDC, size:0x48
void fn_3_115BDC(void) {
    sndFXStartEx(0x1BD, lbl_800EFBA4[6], 0x3F, 0);
    fn_3_114A88(1);
    fn_3_5A6D4(6);
}

// fn_3_115C24, size:0x494
// Wall Ball setup.
// NONMATCHING 87%: g_Minigame stays in r30 across the calls (original reloads it into r7), fielder index not strength-reduced in the original
#if NONMATCHING
void fn_3_115C24(void) {
    s32 i;
    s32 n;
    u8 strength;

    if (g_GameLogic[0x125] == 0) {
        fn_3_59A90();
        g_GameLogic[0x121] = 4;
        for (i = 0; i < 4; i++) {
            WB->currentPoints[i] = 0;
            WB->latestPoints[i] = 0;
            WB->pointsPair[i][0] = 0;
            WB->pointsPair[i][1] = 0;
            WB->slotPlayer[i] = -1;
            WB->playerSlot[i] = -1;
            WB->_18FC[i] = -1;
            WB->_1900[i] = -1;
            WB->_18F0[i] = 0;
        }
        SCORES->round = 0;
        WB->turnNumberWithinRound = 0;
        WB->pointsReqToWin = 0;
        WB->rosterID = -1;
        WB->_17C0 = 0;
        WB->_1A37 = 0;
        WB->turnCounter = 0;
        if (WB->multiPlayerInd == 0) {
            strength = lbl_3_data_2127C[WB->gameMode][WB->difficulty];
            SCORES->lastRound = lbl_3_data_2166C[WB->difficulty];
            for (i = 0; i < 4; i++) {
                WB->aIStrength[i] = strength;
            }
        } else {
            if (WB->_1A3C != 0) {
                for (i = 0; i < 4; i++) {
                    WB->aIStrength[i] = lbl_3_data_2127C[7][0];
                }
            }
            SCORES->lastRound = lbl_3_data_2166C[4];
        }
        n = 0;
        for (i = 0; i < 4; i++) {
            if (WB->characterIndex[i] >= 0) {
                WB->slotPlayer[n] = i;
                WB->playerSlot[WB->slotPlayer[n]] = n + 2;
                WB->turnOrder[n] = i;
                g_Fielders[n + 2].rosterID = i;
                n++;
            }
        }
        fn_3_58870();
        fn_3_114A88(1);
        for (i = 0; i < 7; i++) {
            WB->bumper[i]._00 = 0;
            WB->bumper[i].id = i;
            WB->bumperOrder[i] = i;
        }
        WB->phase = 0;
        WB->_1A80 = 0;
        WB->_1A78 = 0;
        for (i = 0; i < 2; i++) {
            WB->_1A7C[i] = (i & 1) ? 0 : 6;
        }
        WB->_1A70 = 0;
        WB->_1A7E = 0;
        WB->_1A89 = 0;
        WB->_1A8A = 0;
        WB->_1A8B = -1;
        WB->bonus = 0;
        WB->_1A8C = 0;
        for (i = 0; i < 100; i++) {
            WB->coinVisible[i] = 0;
        }
        minigamesSetSomePointers();
        minigamesGXStuff();
        minigamesSetSomePointers2();
        fn_3_F8ABC();
        g_GameLogic[0x125]++;
    } else {
        lbl_3_common_bss_32234[1] = 1;
        fn_3_5A6D4(5);
    }
}
#endif

// fn_3_1160B8, size:0x4
void fn_3_1160B8(void) {
}

// fn_3_11669C, size:0x30
void fn_3_11669C(void) {
    u8* p = lbl_8036E548;
    (*(u8**)(p + 0x2D94))[0x25A6] = 0;
    (*(u8**)(p + 0x2D94))[0x25CE] = 0;
    (*(u8**)(p + 0x2D94))[0x25F6] = 0;
    (*(u8**)(p + 0x2D94))[0x261E] = 0;
}

// fn_3_1166CC, size:0xC0
void fn_3_1166CC(void) {
    u32 i;
    for (i = 0; i < 40; i++) {
        u8* p = *(u8**)(lbl_8036E548 + 0x2D94) + i * 0x28;
        p[0x26] = 0;
        *(s32*)p = 0;
    }
}

// fn_3_11678C, size:0xB4
void fn_3_11678C(void) {
    u8* e;
    s32 i;
    f32* v;
    for (i = 0; i < 7; i++) {
        e = *(u8**)(lbl_8036E548 + 0x2D94) + (i + 0xE9) * 0x28;
        e[0x26] = 0;
        if (i >= 4) {
            e[0x26] = 1;
            v = (f32*)(lbl_3_data_21BC4 + i * 0x30 - 0xC0);
            *(f32*)(e + 4) = v[0];
            *(f32*)(e + 8) = -v[1];
            *(f32*)(e + 0xC) = v[2];
            fn_8001D110(i + 0xE9, lbl_3_data_226C4[0], lbl_3_data_226C4[1], lbl_3_data_226C4[0]);
            *(void**)e = fn_3_11881C;
        }
    }
}
