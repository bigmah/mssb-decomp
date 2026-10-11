#include "game/auto_00_001293D0_text.h"
#include "game/rep_3448.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "main/menu_globals.h"

extern HudTask* lbl_803CC1B8;
extern LayoutSlot lbl_80371C30[];
extern u8 lbl_3_common_bss_32724[];
extern u8 lbl_3_common_bss_34C90[];
extern u8 lbl_3_common_bss_37400[];
extern u8 lbl_3_data_9FB4[];
extern u8 lbl_3_data_9ECC[];
extern u8 lbl_3_data_9208[];
extern u16 lbl_3_data_92C8[];
extern u8 lbl_3_data_92D4[];
extern u8 lbl_3_data_21268[];
extern s16 lbl_3_data_217A4[];
extern void fn_80034E20(void*, void*);
extern void fn_8004CC2C(void);
extern void fn_8004D0F0(void);
extern void fn_3_11E7C4(void);
extern void fn_3_11E364(void);
extern void fn_3_EB6E0(void);
extern void fn_3_97144(void);
extern void fn_3_99BDC(void);
extern void fn_3_1608F0(s32, s32, u8);
extern void fn_3_11D780(void);
extern void fn_3_EA454(void);
extern void* memset(void*, s32, u32);
extern int __abs(int);
extern void* memcpy(void*, const void*, unsigned long);

// fn_3_12DB54, size:0x2C
void fn_3_12DB54(void) {
    s8 i;
    i = 0;
    do {
        g_Minigame._1DBC[i] = 0;
        i++;
    } while (i < 4);
}

// fn_3_12E808, size:0x34
void fn_3_12E808(void) {
    memset(g_Minigame._1D7C, 0, 0x78);
}

// fn_3_12DD88, size:0x44
u32 fn_3_12DD88(void) {
    u32 i = 0;
    do {
        if (g_Minigame.barrels[i].barrelState != 2) {
            break;
        }
        i++;
    } while (i < 0xF);
    return i >= 0xF;
}

// fn_3_1293D0, size:0x88
void fn_3_1293D0(void) {
    if (g_GameLogic._125 == 0) {
        fn_800B0A5C_insertQueue(fn_3_129370, 2);
    }
    if (g_GameLogic._125 == 5 && g_GameLogic.FrameCountOfCurrentAtBat_Copy == 1) {
        fn_800B0A5C_insertQueue(fn_8004D0F0, 2);
    }
    if (g_GameLogic._125 == 6) {
        fn_8004CC2C();
    }
}

// fn_3_12C514, size:0xB8
void fn_3_12C514(void) {
    if (g_GameLogic.gameStatus == 0x1A && g_GameLogic._125 == 0) {
        memset(g_Minigame._1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11E364, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_12C5CC, size:0xB8
void fn_3_12C5CC(void) {
    if (g_GameLogic.gameStatus == 0x1A && g_GameLogic._125 == 0) {
        memset(g_Minigame._1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11E7C4, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_129F48, size:0xB0
void fn_3_129F48(void) {
    HudTask* task = lbl_803CC1B8;
    fn_80034E20(task, lbl_3_data_9FB4);
    task->state = 0;
    if (lbl_3_common_bss_32724[0xBF] != 0) {
        lbl_80371C30[task->baseIdx].obj->_5C = 0x160000;
        task->state = 2;
    }
    task->timer = 0;
    task->_1A = 0;
    lbl_3_common_bss_32724[0xBE] = 1;
    lbl_803CC1B8->func = fn_3_129C88;
}

// fn_3_12C684, size:0xC8
void fn_3_12C684(void) {
    if (g_GameLogic.gameStatus == 0x1A && g_GameLogic._125 == 0) {
        memset(g_Minigame._1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_123990, 2);
        fn_800B0A5C_insertQueue(fn_3_123EBC, 2);
        fn_800B0A5C_insertQueue(fn_3_11EC28, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_11F02C, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_129458, size:0x104
void fn_3_129458(void) {
    if (g_GameLogic.gameStatus == 0xE && g_GameLogic._125 == 1) {
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        if (g_Minigame.GameMode_MiniGame == 1 && g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == 3) {
            fn_800B0A5C_insertQueue(fn_3_11D780, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_EA454, 2);
        fn_800B0A5C_insertQueue(fn_3_129370, 2);
    }
    if (g_GameLogic.gameStatus == 0x22 && (lbl_3_common_bss_34C90[0x1D2] == 7 || g_GameLogic.framesOfExitingToMenu != 0)) {
        lbl_3_common_bss_32724[0xB7] = 1;
    }
}

// fn_3_12E83C, size:0xC0
// Barrel Batter: score the barrels hit this turn.
void fn_3_12E83C(void) {
    s32 points;
    MiniGameStruct* g = &g_Minigame;
    u8 hit = g->barrelBatter_barrelsHit;
    if (hit <= 1) {
        points = lbl_3_data_217A4[5] * hit;
    } else {
        points = hit * ((hit - 1) * lbl_3_data_217A4[5]);
    }
    g_Minigame.miniGameCurrentPoints[g_Minigame.rosterID] += points;
    g_Minigame._1DF4[0] = points;
    if (g_d_GameSettings.exhibitionMatchInd == 0 && g_Minigame.rosterID == *(s16*)(lbl_3_common_bss_37400 + 0x40)) { // TODO type
        fn_3_1608F0(2, points, g->barrelBatter_barrelsHit);
    }
}

// fn_3_12C74C, size:0x11C
void fn_3_12C74C(void) {
    if (lbl_3_common_bss_32724[0xB6] != 0) {
        memset(g_Minigame._1DF4, 0, 0xE);
        if (g_Minigame.multiPlayerInd == 0) {
            fn_800B0A5C_insertQueue(fn_3_11F508, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_11F778, 2);
        fn_800B0A5C_insertQueue(fn_3_11FA58, 2);
        fn_800B0A5C_insertQueue(fn_3_11FDB0, 2);
        if (g_Minigame.multiPlayerInd != 0) {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124738, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
}

// fn_3_12C868, size:0x11C
void fn_3_12C868(void) {
    if (g_GameLogic.gameStatus == 0x1A) {
        memset(g_Minigame._1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_12026C, 2);
        fn_800B0A5C_insertQueue(fn_3_12089C, 2);
        if (g_Minigame.multiPlayerInd == 0 && g_Minigame._1A3C == 0 && g_Minigame.soloMinigameDifficulty == 3) {
            fn_800B0A5C_insertQueue(fn_3_120FF8, 2);
        } else {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
            fn_800B0A5C_insertQueue(fn_3_123990, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_121304, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
        fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
    }
}

// fn_3_12C984, size:0x10C
void fn_3_12C984(void) {
    if (lbl_3_common_bss_32724[0xB6] != 0) {
        memset(g_Minigame._1DF4, 0, 0xE);
        fn_800B0A5C_insertQueue(fn_3_121908, 2);
        if (g_Minigame.multiPlayerInd != 0) {
            fn_800B0A5C_insertQueue(fn_3_1243A4, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_124738, 2);
        fn_800B0A5C_insertQueue(fn_3_1226D4, 2);
        fn_800B0A5C_insertQueue(fn_3_122334, 2);
        fn_800B0A5C_insertQueue(fn_3_1235B8, 2);
        fn_800B0A5C_insertQueue(fn_3_124CE0, 2);
        fn_800B0A5C_insertQueue(fn_3_EB6E0, 2);
        lbl_3_common_bss_32724[0xB7] = 0;
        lbl_3_common_bss_32724[0xB6] = 0;
        fn_800B0A5C_insertQueue(fn_3_125850, 2);
    }
    fn_3_97144();
}

// fn_3_12C3F0, size:0x124
void fn_3_12C3F0(void) {
    HudTask* task = lbl_803CC1B8;
    LayoutSlot* slots;
    u16 anim;
    fn_80034E20(task, lbl_3_data_9208);
    lbl_3_common_bss_32724[0xD9] = 1;
    if (g_d_GameSettings.GameModeSelected == 7) {
        if (g_GameLogic.gameStatus == 0x1C || g_GameLogic.gameStatus == 0x1B || g_GameLogic.gameStatus == 0x1D) {
            anim = lbl_3_data_92C8[0];
        } else {
            anim = lbl_3_data_92C8[1];
        }
    } else if (g_Practice.practiceType_1 == 6) {
        anim = lbl_3_data_92C8[4];
    } else {
        anim = lbl_3_data_92C8[3];
    }
    slots = lbl_80371C30 + 1;
    slots[task->baseIdx].obj->_64 = anim;
    slots[task->baseIdx].obj->_5C = 0x280000;
    task->state = anim;
    task->_1E = 0;
    lbl_803CC1B8->func = fn_3_12C1AC;
}

// fn_3_12BFE8, size:0x1C4
void fn_3_12BFE8(void) {
    HudTask* task = lbl_803CC1B8;
    fn_80034E20(task, lbl_3_data_92D4);
    if (g_d_GameSettings.GameModeSelected != 2) {
        if (g_d_GameSettings.GameModeSelected == 6) {
            lbl_80371C30[task->baseIdx + 5].obj->flags &= ~2;
            lbl_80371C30[task->baseIdx + 6].obj->flags &= ~2;
        } else {
            lbl_80371C30[task->baseIdx + 5].obj->flags &= ~2;
            lbl_80371C30[task->baseIdx + 6].obj->flags &= ~2;
        }
    }
    lbl_3_common_bss_32724[0xBC] = 1;
    if (g_d_GameSettings.GameModeSelected == 2) {
        task->_20 = g_Practice.practiceType_2;
        lbl_80371C30[task->baseIdx + 3].obj->_64 = 0x5F;
        lbl_80371C30[task->baseIdx + 4].obj->_64 = 0x5C;
    } else {
        task->_20 = lbl_3_data_21268[(s8)g_Minigame._19E1];
        lbl_80371C30[task->baseIdx + 3].obj->_64 = 0x5E;
        lbl_80371C30[task->baseIdx + 4].obj->_64 = 0x5B;
    }
    task->_1A = 0;
    task->state = 0;
    task->_22 = 0;
    lbl_803CC1B8->func = fn_3_12BB64;
}

// fn_3_12C1AC, size:0x244
void fn_3_12C1AC(void) {
    HudTask* task;
    LayoutSlot* slots;
    u16 anim;
    u8 status;
    s32 idx;
    task = lbl_803CC1B8;
    if (lbl_3_common_bss_32724[0x96] == 0) {
        if (g_d_GameSettings.GameModeSelected == 7 || g_d_GameSettings.GameModeSelected == 6) {
            status = g_GameLogic.gameStatus;
            if (status == 5) {
                goto remove;
            }
            if (status == 0x28 || status == 0x21) {
                anim = lbl_3_data_92C8[2];
            } else if (status == 0x1B || status == 0x1C || status == 0x1D) {
                anim = lbl_3_data_92C8[0];
            } else {
                anim = lbl_3_data_92C8[1];
            }
        } else if (g_GameLogic.secondaryGameMode == 0xA) {
            if (g_Practice.practiceType_1 == 6) {
                anim = lbl_3_data_92C8[4];
            } else {
                anim = lbl_3_data_92C8[3];
            }
        } else {
            goto remove;
        }
        if (task->state != anim) {
            task->state = anim;
            task->_1E = 1;
            slots = lbl_80371C30 + 2;
            slots[task->baseIdx].obj->flags |= 2;
            slots[task->baseIdx].obj->_68 = 1;
            slots[task->baseIdx].obj->_5C = 0;
            lbl_80371C30[task->baseIdx + 3].obj->_64 = anim;
            lbl_80371C30[task->baseIdx].obj->_68 = 4;
            return;
        }
        if (task->_1E != 0) {
            idx = task->baseIdx;
            if ((lbl_80371C30[idx].obj->_5C >> 16) == 0) {
                lbl_80371C30[idx + 2].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + 1].obj->_64 = task->state;
                lbl_80371C30[task->baseIdx].obj->_5C = 0x280000;
                lbl_80371C30[task->baseIdx].obj->_68 = 0;
                task->_1E = 0;
            }
        }
        return;
    }
remove:
    fn_800B0A14_removeQueue(fn_80034CEC(task));
    lbl_3_common_bss_32724[0xD9] = 0;
    lbl_8034E978._26 = 1;
}


// fn_3_12E084, size:0xF8
// Sort order for BbTarget: best score first, then by chain length, then
// prefer the centre column and the middle row.
s32 fn_3_12E084(void* pa, void* pb) {
    BbTarget* a = pa;
    BbTarget* b = pb;
    MiniGameStruct* mg = &g_Minigame;
    s8 da;
    s8 db;
    if (a->score != b->score) {
        return b->score - a->score;
    }
    if (a->chain != b->chain) {
        if (mg->bB_cpuPreferLow != 0) {
            return a->chain - b->chain;
        }
        return b->chain - a->chain;
    }
    da = __abs(2 - a->barrel / 3);
    db = __abs(2 - b->barrel / 3);
    if (da != db) {
        return da - db;
    }
    da = __abs(1 - a->barrel % 3);
    db = __abs(1 - b->barrel % 3);
    return da - db;
}

// fn_3_12A2B8, size:0x138
void fn_3_12A2B8(void) {
    HudTask* task = lbl_803CC1B8;
    s32 level;
    s32 i;
    level = g_d_GameSettings._14[g_Minigame.GameMode_MiniGame - 1];
    if (g_Minigame._190A != 0) {
        level = 2;
    }
    fn_80034E20(task, lbl_3_data_9ECC);
    for (i = 0; i < 4; i++) {
        if (level >= i) {
            fn_800363D8(task, i + 2, 1, 0x6B, i);
        } else {
            fn_800363D8(task, i + 2, 1, 0x6B, 4);
        }
    }
    task->state = 0;
    if (lbl_3_common_bss_32724[0xBF] != 0) {
        lbl_80371C30[task->baseIdx].obj->_5C = 0x160000;
        task->state = 2;
    }
    task->timer = 0;
    task->_1A = 0;
    lbl_3_common_bss_32724[0xBE] = 1;
    lbl_803CC1B8->func = fn_3_129FF8;
}

// fn_3_12E384, size:0x484
// Flood fill: knock down the standing barrel at idx and every standing
// neighbour of the same colour (5 rows of 3); returns how many fell.
u8 fn_3_12E384(BbCell* grid, s8 idx, u8 colour) {
    u8 count;
    if (colour == grid[idx].colour && grid[idx].state == 2) {
        grid[idx].state = 0;
        count = 1;
        if (idx / 3 > 0) {
            count += fn_3_12E384(grid, idx - 3, colour);
        }
        if (idx / 3 < 4) {
            count += fn_3_12E384(grid, idx + 3, colour);
        }
        if (idx % 3 > 0) {
            count += fn_3_12E384(grid, idx - 1, colour);
        }
        if (idx % 3 < 2) {
            count += fn_3_12E384(grid, idx + 1, colour);
        }
        return count;
    }
    return 0;
}

// fn_3_12E17C, size:0x208
// Barrel Batter CPU: for every barrel, how many barrels hitting it knocks
// down (chain) and the points that scores; with lookahead, also add the best
// follow-up shot once the remaining barrels have slid left.
// NONMATCHING 98.6%: register allocation only (loop/pointer regs rotated)
#if NONMATCHING
void fn_3_12E17C(s8* chain, s16* score, u8 lookahead) {
    BbCell grid[15];
    BbCell trial[15];
    s16 best;
    s8 row;
    s8 pass;
    s8 n;
    s8 j;
    s8 i;
    s8 col;
    s16 points;

    i = 0;
    do {
        j = 0;
        do {
            grid[j].state = g_Minigame.barrels[j].barrelState;
            grid[j].colour = g_Minigame.barrels[j].barrelColour;
            j++;
        } while (j < 15);
        chain[i] = fn_3_12E384(grid, i, grid[i].colour);
        if (chain[i] >= 2) {
            *score = (chain[i] - 1) * chain[i];
        } else {
            *score = chain[i];
        }
        if (lookahead != 0) {
            pass = 0;
            do {
                col = 0;
                do {
                    row = 0;
                    do {
                        if (grid[col + row * 3].state != 2) {
                            memcpy(&grid[col + row * 3], &grid[(col + 1) + row * 3], 2);
                            grid[(col + 1) + row * 3].state = 0;
                        }
                        row++;
                    } while (row < 5);
                    col++;
                } while (col < 2);
                pass++;
            } while (pass < 2);
            best = 0;
            j = 0;
            do {
                n = 0;
                do {
                    memcpy(&trial[n], &grid[n], 2);
                    n++;
                } while (n < 15);
                n = fn_3_12E384(trial, j, trial[j].colour);
                if (n >= 2) {
                    points = (n - 1) * n;
                } else {
                    points = n;
                }
                if (points > best) {
                    best = points;
                }
                j++;
            } while (j < 15);
            *score += best;
        }
        i++;
        score++;
    } while (i < 15);
}
#endif
