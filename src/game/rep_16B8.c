#include "game/rep_16B8.h"
#include "header_rep_data.h"
#include "main/menu_globals.h"

extern u8 lbl_3_data_F390[];
extern u8 lbl_3_data_E160[];
extern u8 lbl_3_data_E21C[];
extern u8 lbl_3_data_E2F8[];
extern u8 lbl_3_data_E278[];
extern u16 lbl_3_data_E200[];
extern u8 lbl_3_common_bss_37400[];
extern u8 fn_3_ED574[];
extern u8 lbl_3_data_BF6C[];

extern u8 lbl_3_data_E0E0[];

extern u8 lbl_3_data_F350[];

extern u8 lbl_3_data_F3F0[];

extern u8 lbl_3_data_E120[];

extern void fn_80034E20(void*, void*);
extern void fn_800363D8(void*, s32, s32, s32, s32);
typedef struct { u8 p[0x24]; s16 v; u8 q[0x7A]; } RT;
typedef struct { u8* a; u8* b; } TB;
typedef struct { s8 a, b, c, d, e; } E5;
typedef struct { u8 p[4]; s16 f; u8 q[0x20]; } SC;
extern u8 lbl_3_data_C1EC[];

extern void* lbl_803CC1B8[];
extern u8 lbl_3_common_bss_32724[];
extern RepLineScoreData lbl_3_data_EC1C;
extern u8 lbl_3_data_F430[];
extern u8 lbl_3_data_EABC[];
extern u8 lbl_3_data_E85C[];
extern f32 lbl_3_data_C1CC[4]; // field-map transform: offset x, offset y, scale x, scale y
extern u8 lbl_3_common_bss_34C90[]; // TODO type: GamePauseState (auto_00_00097144_text.h)
extern void fn_3_ED0F4(void);
extern u8 lbl_3_data_F224[];
extern u8 lbl_3_data_F200[3][12]; // [0]: fn_3_91E4C thresholds, [1]/[2]: line-score column _72 values
extern u8 lbl_3_data_E378[];
extern u8 lbl_3_data_8D88[];
extern u8 lbl_3_data_BFEC[];
extern u8 lbl_3_data_E758[];
extern u8 lbl_3_data_F344[];
extern u8 lbl_3_data_E75C[];
#include "static/UnknownHomes_Static.h"
#include "musyx/musyx.h"

extern RepBannerData lbl_3_data_BE50;
extern RepRunningLogic g_RunningLogic;
extern RepSoundParams lbl_3_data_8404[];
extern RepSoundParams lbl_3_data_84B8[];
extern u16 lbl_3_data_81DC[];
extern u8 lbl_800EF808[]; // TODO type: 0x39C-byte options block; [0x398] = rumble/sound flag
extern RepFielderView g_Fielders[9];
BOOL fn_3_1650C(int* outX, int* outY, BOOL r5, f32 pX, f32 pY, f32 pZ);
extern void fn_8003649C(void* owner, s32 idx, s32 track, u16 animId, u32 frame);
extern GameScores g_Scores;

// .text:0x00091520 size:0x540 mapped:0x806D05B4
void fn_3_91520(void) {
    RepTask* task = lbl_803CC1B8[0];
    int sx;
    int sy;
    if (lbl_3_common_bss_32724[0x96] == 0) {
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (g_UnkSound_32718._08 != 0) {
        if (g_Stats.replayInd != 0) {
            g_UnkSound_32718._08 = 0;
            return;
        }
        if (g_GameLogic.framesOfExitingToMenu != 0) {
            g_UnkSound_32718._08 = 0;
            return;
        }
        fn_3_1650C(&sx, &sy, FALSE, g_Ball.AtBat_Contact_BallPos.x, -g_Ball.AtBat_Contact_BallPos.y, g_Ball.AtBat_Contact_BallPos.z);
        switch (g_UnkSound_32718._08) {
        case 1:
            if (task->_1C == 0) {
                REP_OBJ(task, 0)->_5C = 0;
                REP_OBJ(task, 0)->flags |= 2;
                REP_OBJ(task, 0)->_68 = 1;
                REP_OBJ(task, 0)->x = sx;
                REP_OBJ(task, 0)->y = sy;
                task->_1C = 1;
            }
            break;
        case 2:
            if (task->_1E == 0) {
                REP_OBJ(task, 1)->_5C = 0;
                REP_OBJ(task, 1)->flags |= 2;
                REP_OBJ(task, 1)->_68 = 1;
                REP_OBJ(task, 1)->_64 = 1;
                REP_OBJ(task, 1)->x = sx;
                REP_OBJ(task, 1)->y = sy;
                task->_1E = 1;
            }
            break;
        case 3:
            if (task->_1E == 0) {
                REP_OBJ(task, 1)->_5C = 0;
                REP_OBJ(task, 1)->flags |= 2;
                REP_OBJ(task, 1)->_68 = 1;
                REP_OBJ(task, 1)->_64 = 2;
                REP_OBJ(task, 1)->x = sx;
                REP_OBJ(task, 1)->y = sy;
                task->_1E = 1;
            }
            break;
        case 4:
            if (g_d_GameSettings.GameModeSelected == 6) {
                g_UnkSound_32718._08 = 0;
                return;
            }
            if (task->_20 == 0) {
                REP_OBJ(task, 2)->_5C = 0;
                REP_OBJ(task, 2)->flags |= 2;
                REP_OBJ(task, 2)->_68 = 0;
                REP_OBJ(task, 2)->x = 0.0f;
                REP_OBJ(task, 2)->y = 0.0f;
                task->_20 = 1;
            }
            break;
        }
        task->timer = 0;
        g_UnkSound_32718._08 = 0;
    } else {
        if (task->_1C != 0 && ((REP_OBJ(task, 0)->_69 == 2) ? 1 : 0)) {
            REP_OBJ(task, 0)->flags &= ~2;
            task->_1C = 0;
        }
        if (task->_1E != 0 && ((REP_OBJ(task, 1)->_69 == 2) ? 1 : 0)) {
            REP_OBJ(task, 1)->flags &= ~2;
            task->_1E = 0;
        }
        if (task->_20 != 0) {
            if (task->timer == 0x1E) {
                playSoundEffect(0x1AC);
                REP_OBJ(task, 2)->_68 = 1;
            }
            if (((REP_OBJ(task, 2)->_69 == 2) ? 1 : 0)) {
                REP_OBJ(task, 2)->flags &= ~2;
                task->_20 = 0;
            }
        }
    }
    } else {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}

// .text:0x00091A60 size:0x68 mapped:0x806D0AF4
void fn_3_91A60(void) {
    u16* o;
    fn_80034E20(o = lbl_803CC1B8[0], lbl_3_data_BF6C);
    o[0xC] = 0;
    o[0xE] = 0;
    o[0xF] = 0;
    o[0x10] = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_91520;
}

// .text:0x00091AC8 size:0x88 mapped:0x806D0B5C
void fn_3_91AC8(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] == 0 && ((u8*)&g_Stats)[0x36] == 0) {
        if (((u8*)&g_GameLogic)[0x11E] == 2 || ((u8*)&g_GameLogic)[0x11E] == 1) {
            return;
        }
    }
    fn_800B0A14_removeQueue(fn_80034CEC(p));
    lbl_3_common_bss_32724[0xB2] = 0;
}
// .text:0x00091B50 size:0x4C mapped:0x806D0BE4
void fn_3_91B50(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_F350);
    *(void**)lbl_803CC1B8[0] = fn_3_91AC8;
}

// .text:0x00091B9C size:0xD4 mapped:0x806D0C30
void fn_3_91B9C(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] == 0) {
        u32 idx = *(u16*)((u8*)p + 0x14);
        u8** t = (u8**)((u8*)lbl_80371C30);
        if ((*(u32*)(t[idx * 2] + 0x5C) >> 16) >= 0x4B) {
            u8* q = t[idx * 2 + 2];
            *(u32*)(q + 0x54) |= 2;
        }
        if ((((u8*)&g_Stats)[0x36] == 0 && ((u8*)&g_Stats)[0x39] == 0) || ((u8*)&g_GameLogic)[0x11E] == 3 || ((u8*)&g_GameLogic)[0x11E] == 0xB || ((u8*)&g_GameLogic)[0x11E] == 0xE) {
            goto call;
        }
    } else {
call:
        fn_800B0A14_removeQueue(fn_80034CEC(p));
        lbl_3_common_bss_32724[0xB0] = 0;
        lbl_3_common_bss_32724[0xB1] = 0;
    }
}

// .text:0x00091C70 size:0x5C mapped:0x806D0D04
void fn_3_91C70(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_F390);
    lbl_3_common_bss_32724[0xB0] = 1;
    *(void**)lbl_803CC1B8[0] = fn_3_91B9C;
}

// .text:0x00091CCC size:0x50 mapped:0x806D0D60
void fn_3_91CCC(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || lbl_3_common_bss_32724[0xCD] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x00091D1C size:0x130 mapped:0x806D0DB0
void fn_3_91D1C(void) {
    u8* o;
    s32 i;
    fn_80034E20(o = lbl_803CC1B8[0], lbl_3_data_F224);
    *(u16*)(((u8**)(((u8*)lbl_80371C30) + 0x18))[*(u16*)(o + 0x14) * 2] + 0x64) = ((u16*)lbl_3_data_F344)[g_d_GameSettings.StadiumID];
    for (i = 0; i < 3; i++) {
        s32 k = *(s32*)(((u8*)&g_GameLogic) + *(s32*)(((u8*)&g_GameLogic) + 0x10) * 4 + 0xDC) - (-i);
        s32 m;
        if (k > 9) k -= 9;
        m = *(s32*)(((u8*)&g_GameLogic) + *(s32*)(((u8*)&g_GameLogic) + 0x10) * 0x50 + k * 8 + 0x3C);
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) - (-5) - (-i)) * 2] + 0x5C) = ((RT*)(((u8*)&inMemRoster) + *(s32*)(((u8*)&g_GameLogic) + 0x8) * 0x5A0))[m].v << 16;
    }
    fn_800363D8(o, 1, 4, 7, g_d_GameSettings.StadiumID);
    *(void**)lbl_803CC1B8[0] = fn_3_91CCC;
}

// .text:0x00091E4C size:0x178 mapped:0x806D0EE0
// NONMATCHING 99%: only the tail differs: original `bge remove; b end`, ours `blt end` after the 0x1A counter check
// (tried goto/else-return/switch fallthrough forms)
#if NONMATCHING
void fn_3_91E4C(void) {
    RepTask* task = lbl_803CC1B8[0];
    s32 i;
    s32 v;
    if (lbl_3_common_bss_32724[0xCD] == 0) {
        if (lbl_3_common_bss_32724[0xCE] == 0) {
            return;
        }
        REP_OBJ(task, 0)->_68 = 4;
        REP_OBJ(task, 1)->_68 = 4;
        v = REP_OBJ(task, 1)->_5C >> 16;
        for (i = 0; i < 11; i++) {
            if (v <= lbl_3_data_F200[0][i]) {
                if (i == 0) {
                    REP_OBJ(task, 2)->_68 = 4;
                    REP_OBJ(task, 3)->_68 = 4;
                }
                lbl_80371C30[task->baseIdx + 6 + i].obj->_68 = 4;
                lbl_80371C30[task->baseIdx + 17 + i].obj->_68 = 4;
            }
        }
        task->_1A++;
        if (task->_1A < 45) {
            return;
        }
    }
    fn_800B0A14_removeQueue(fn_80034CEC(task));
    if (g_GameLogic.gameStatus == 3) {
        lbl_8034E978._26 = 1;
    }
}
#endif

// .text:0x00091FC4 size:0xD14 mapped:0x806D1058
// NONMATCHING 87% (with the two helpers inlined): the original reaches lbl_3_data_EC1C/F200/F430 through the
// pooled lbl_3_data_8D88 base; the helpers stay calls here because the file ends in `dont_inline on`
#if NONMATCHING
static void fn_3_91FC4_digits(RepTask* task, s32 slot, s32 n) {
    if (n >= 99) {
        n = 99;
    }
    if (n < 10) {
        REP_OBJ(task, slot)->_64 = lbl_3_data_EC1C.blankDigitAnim;
        fn_800363D8(task, slot, 1, 0xC4, n);
    } else {
        fn_800363D8(task, slot, 2, 0xC4, n % 10);
        fn_800363D8(task, slot, 1, 0xC4, n / 10);
    }
}

// One line-score column: col 1..9 on screen, showing inning `inning`.
static void fn_3_91FC4_column(RepTask* task, s32 col, s32 inning) {
    s32 n;
    REP_OBJ(task, col + 5)->flags |= 2;
    fn_3_91FC4_digits(task, col + 5, g_Scores.team[0].runs[inning]);
    if (inning < lbl_3_common_bss_32724[0xCF] || (inning == lbl_3_common_bss_32724[0xCF] && lbl_3_common_bss_32724[0xD0] != 0)) {
        REP_OBJ(task, col + 16)->flags |= 2;
        n = g_Scores.team[1].runs[inning];
        if (n >= 99) {
            n = 99;
        }
        if (n < 10) {
            if (inning >= g_Scores.inning && (g_GameLogic.winType == 3 || g_GameLogic.winType == 6)) {
                fn_800363D8(task, col + 16, 2, 0xC4, 11);
                fn_800363D8(task, col + 16, 1, 0xC4, n);
            } else {
                REP_OBJ(task, col + 16)->_64 = lbl_3_data_EC1C.blankDigitAnim;
                fn_800363D8(task, col + 16, 1, 0xC4, n);
            }
        } else {
            fn_800363D8(task, col + 16, 2, 0xC4, n % 10);
            fn_800363D8(task, col + 16, 1, 0xC4, n / 10);
        }
    } else if (g_GameLogic.gameStatus == 0xE) {
        REP_OBJ(task, col + 16)->flags |= 2;
        REP_OBJ(task, col + 16)->_64 = lbl_3_data_EC1C.blankDigitAnim;
        fn_800363D8(task, col + 16, 1, 0xC4, 10);
    }
}

void fn_3_91FC4(void) {
    RepTask* task = lbl_803CC1B8[0];
    s32 extra = 0;
    s32 i;
    s32 col;
    s32 inning;
    s32 shown;
    u8 innings = lbl_3_common_bss_32724[0xCF];
    if (innings == 12) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC9;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else if (innings == 11) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC8;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else if (innings == 10) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC7;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else if (innings > 5 || g_Scores.maxInnings > 5) {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xC6;
        extra = 1;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC1;
    } else {
        lbl_3_data_EC1C.lineDescs[0].animId = 0xCA;
        lbl_3_data_EC1C.lineDescs[1].animId = 0xC5;
    }
    fn_80034E20(task, lbl_3_data_EC1C.lineDescs);
    if (extra) {
        REP_OBJ(task, 2)->_72 = lbl_3_data_F200[1][0];
        REP_OBJ(task, 3)->_72 = lbl_3_data_F200[2][0];
        for (i = 0; i < 11; i++) {
            REP_OBJ(task, i + 6)->_72 = lbl_3_data_F200[1][i + 1];
            REP_OBJ(task, i + 17)->_72 = lbl_3_data_F200[2][i + 1];
        }
    }
    REP_OBJ(task, 4)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain * 2];
    REP_OBJ(task, 5)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain * 2];
    REP_OBJ(task, 4)->_5C = g_GameLogic.logo[0].variationID << 16;
    REP_OBJ(task, 5)->_5C = g_GameLogic.logo[1].variationID << 16;
    // totals: runs (slots 15/26) and hits (slots 16/27)
    if (lbl_3_common_bss_32724[0xCF] >= 1) {
        REP_OBJ(task, 15)->flags |= 2;
        REP_OBJ(task, 16)->flags |= 2;
        fn_3_91FC4_digits(task, 15, g_Scores.team[0].runs[0]);
        fn_3_91FC4_digits(task, 16, g_Scores.hits[0].runs[0]);
    }
    if (lbl_3_common_bss_32724[0xCF] >= 2 || lbl_3_common_bss_32724[0xD0] != 0) {
        REP_OBJ(task, 26)->flags |= 2;
        REP_OBJ(task, 27)->flags |= 2;
        fn_3_91FC4_digits(task, 26, g_Scores.team[1].runs[0]);
        fn_3_91FC4_digits(task, 27, g_Scores.hits[1].runs[0]);
    }
    if (lbl_3_common_bss_32724[0xCF] >= 10) {
        // extra innings: innings 10.. first, then a gap, then the remaining early innings
        for (col = 1, inning = 10; col <= 9; col++, inning++) {
            if (inning <= lbl_3_common_bss_32724[0xCF]) {
                shown = inning;
            } else if (inning == lbl_3_common_bss_32724[0xCF] + 1) {
                continue;
            } else {
                shown = col;
            }
            fn_3_91FC4_column(task, col, shown);
        }
    } else {
        for (col = 1; col <= lbl_3_common_bss_32724[0xCF]; col++) {
            fn_3_91FC4_column(task, col, col);
        }
    }
    lbl_3_common_bss_32724[0xCD] = 0;
    lbl_3_common_bss_32724[0xCE] = 0;
    task->_1A = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_91E4C;
}
#endif

// .text:0x00092CD8 size:0x6F4 mapped:0x806D1D6C
void fn_3_92CD8(RepScoreTask* task) {
    s32 team;
    s32 a;
    s32 b;
    s32 done;
    s32 k;
    for (k = 0; k < 2; k++) {
        for (team = 0; team < 2; team++) {
            if (task->score[k][team] >= 100) {
                task->score[k][team] = 99;
            }
        }
    }
    if (task->_1A == 0 && ((REP_OBJ(task, 11)->_5C >> 16) >= 20 || (REP_OBJ(task, 12)->_5C >> 16) >= 20)) {
        for (k = 11; k < 17; k++) {
            lbl_80371C30[task->baseIdx + k].obj->_68 = 0;
            lbl_80371C30[task->baseIdx + k].obj->_5C = 20 << 16;
        }
    }
    for (team = 0; team < 2; team++) {
        if (team == 0) {
            a = 11;
            b = 5;
        } else {
            a = 14;
            b = 8;
        }
        if (task->score[1][team] == task->score[0][team]) {
            if (task->score[0][team] < 10) {
                lbl_80371C30[task->baseIdx + a + 1].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + a + 2].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + a].obj->flags |= 2;
                fn_800363D8(task, a, 1, 0xF6, task->score[0][team]);
            } else {
                lbl_80371C30[task->baseIdx + a].obj->flags &= ~2;
                lbl_80371C30[task->baseIdx + a + 1].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + a + 2].obj->flags |= 2;
                fn_800363D8(task, a + 1, 1, 0xF6, task->score[0][team] / 10);
                fn_800363D8(task, a + 2, 1, 0xF6, task->score[0][team] % 10);
            }
            for (k = 0; k < 3; k++) {
                lbl_80371C30[task->baseIdx + a + k].obj->_5C = 20 << 16;
                lbl_80371C30[task->baseIdx + b + k].obj->_5C = 45 << 16;
                lbl_80371C30[task->baseIdx + b + k].obj->flags &= ~2;
            }
        } else {
            done = 0;
            if (task->score[0][team] < 10) {
                lbl_80371C30[task->baseIdx + a].obj->_68 = 1;
                if ((s32)(lbl_80371C30[task->baseIdx + a].obj->_5C >> 16) >= 45) {
                    done = 1;
                    lbl_80371C30[task->baseIdx + a].obj->_68 = 0;
                }
            } else {
                lbl_80371C30[task->baseIdx + a + 1].obj->_68 = 1;
                lbl_80371C30[task->baseIdx + a + 2].obj->_68 = 1;
                if ((lbl_80371C30[task->baseIdx + a + 1].obj->_5C >> 16) >= 45) {
                    done = 1;
                    lbl_80371C30[task->baseIdx + a + 1].obj->_68 = 0;
                    lbl_80371C30[task->baseIdx + a + 2].obj->_68 = 0;
                }
            }
            if (task->score[1][team] < 10) {
                lbl_80371C30[task->baseIdx + b].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + b].obj->_68 = 1;
                fn_800363D8(task, b, 1, 0xF6, task->score[1][team]);
                if ((lbl_80371C30[task->baseIdx + b].obj->_5C >> 16) >= 70) {
                    done++;
                    lbl_80371C30[task->baseIdx + b].obj->_68 = 0;
                }
            } else {
                lbl_80371C30[task->baseIdx + b + 1].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + b + 2].obj->flags |= 2;
                lbl_80371C30[task->baseIdx + b + 1].obj->_68 = 1;
                lbl_80371C30[task->baseIdx + b + 2].obj->_68 = 1;
                fn_800363D8(task, b + 1, 1, 0xF6, task->score[1][team] / 10);
                fn_800363D8(task, b + 2, 1, 0xF6, task->score[1][team] % 10);
                if ((lbl_80371C30[task->baseIdx + b + 1].obj->_5C >> 16) >= 70) {
                    done++;
                    lbl_80371C30[task->baseIdx + b + 1].obj->_68 = 0;
                    lbl_80371C30[task->baseIdx + b + 2].obj->_68 = 0;
                }
            }
            if (done >= 2) {
                task->score[0][team] = task->score[1][team];
            }
        }
    }
}

#pragma dont_inline on
typedef struct { u8 a[4]; s16 v; u8 b[0x20]; } ScT;
// .text:0x000933CC size:0x178 mapped:0x806D2460
void fn_3_933CC(void) {
    u8* o = lbl_803CC1B8[0];
    u16 w = *(u16*)(o + 0x18);
    if (w < 0xFFFE) {
        *(u16*)(o + 0x18) = w + 1;
    } else {
        *(u16*)(o + 0x18) = 0xFFFF;
    }
    if (lbl_3_common_bss_32724[0x96] == 0 && ((u8*)&g_GameLogic)[0x11E] == 0x13) {
        u8* t;
        u16 c;
        ((void (*)(void*))fn_3_92CD8)(o);
        if (*(u16*)(o + 0x1A) == 0) {
            u8* q = ((u8**)lbl_80371C30)[*(u16*)(o + 0x14) * 2];
            t = ((u8*)lbl_80371C30);
            if ((*(u32*)(q + 0x5C) >> 16) >= 0x15) {
                q[0x68] = 0;
                { u8* e = t; e += *(u16*)(o + 0x14) * 8; (*(u8**)(e + 0x18))[0x68] = 0; }
                { u8* e = t; e += *(u16*)(o + 0x14) * 8; (*(u8**)(e + 0x20))[0x68] = 0; }
                *(u16*)(o + 0x1A) = 1;
            }
        }
        c = *(u16*)(o + 0x18);
        if (c >= 0x1E && (c - 0x1E) % 27 == 0) {
            u16* p = (u16*)(o + *(s32*)(((u8*)&g_GameLogic) + 0xC) * 2);
            u16 v = p[0x10];
            ScT* sc = (ScT*)((u8*)&g_Scores);
            if (v < sc[*(s32*)(((u8*)&g_GameLogic) + 0xC)].v) {
                p[0x10] = v + 1;
            }
        }
    } else {
        fn_800B0A14_removeQueue(fn_80034CEC(o));
        lbl_3_common_bss_32724[0xC5] = 0;
    }
}

#pragma dont_inline on
// .text:0x00093544 size:0x144 mapped:0x806D25D8
void fn_3_93544(void) {
    u8* o;
    fn_80034E20(o = lbl_803CC1B8[0], lbl_3_data_EC1C.scoreDescs);
    *(s16*)(((u8**)(((u8*)lbl_80371C30) + 8))[*(u16*)(o + 0x14) * 2] + 0x64) = (lbl_3_data_F430 + 1)[*(s32*)(((u8*)&g_GameLogic) + 0x2C) * 2];
    *(s16*)(((u8**)(((u8*)lbl_80371C30) + 0x10))[*(u16*)(o + 0x14) * 2] + 0x64) = (lbl_3_data_F430 + 1)[*(s32*)(((u8*)&g_GameLogic) + 0x38) * 2];
    *(s32*)(((u8**)(((u8*)lbl_80371C30) + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = *(s32*)(((u8*)&g_GameLogic) + 0x28) << 16;
    *(s32*)(((u8**)(((u8*)lbl_80371C30) + 0x10))[*(u16*)(o + 0x14) * 2] + 0x5C) = *(s32*)(((u8*)&g_GameLogic) + 0x34) << 16;
    if (*(s32*)(((u8*)&g_GameLogic) + 0xC) == 0) {
        *(s16*)(o + 0x1C) = *(s16*)(((u8*)&g_Scores) + 0xA0);
        *(s16*)(o + 0x1E) = *(s16*)(((u8*)&g_Scores) + 0x2A);
    } else {
        *(s16*)(o + 0x1C) = *(s16*)(((u8*)&g_Scores) + 0x4);
        *(s16*)(o + 0x1E) = *(s16*)(((u8*)&g_Scores) + 0xA0);
    }
    *(u16*)(o + 0x20) = *(u16*)(o + 0x1C);
    *(u16*)(o + 0x22) = *(u16*)(o + 0x1E);
    ((void (*)(void*))fn_3_92CD8)(o);
    *(s16*)(o + 0x18) = 0;
    *(s16*)(o + 0x1A) = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_933CC;
}

#pragma dont_inline reset
// .text:0x00093688 size:0x2D8 mapped:0x806D271C
void fn_3_93688(RepTask* task) {
    s32 n;
    if (g_Scores.team[0].runs[0] >= 10) {
        n = g_Scores.team[0].runs[0];
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 4)->flags &= ~2;
        REP_OBJ(task, 5)->flags |= 2;
        REP_OBJ(task, 6)->flags |= 2;
        fn_8003649C(task, 5, 2, 0xF6, n / 10);
        fn_8003649C(task, 6, 3, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 4)->flags |= 2;
        REP_OBJ(task, 5)->flags &= ~2;
        REP_OBJ(task, 6)->flags &= ~2;
        fn_8003649C(task, 4, 1, 0xF6, g_Scores.team[0].runs[0]);
    }
    n = g_Scores.team[1].runs[0];
    if (n >= 10) {
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 7)->flags &= ~2;
        REP_OBJ(task, 8)->flags |= 2;
        REP_OBJ(task, 9)->flags |= 2;
        fn_8003649C(task, 8, 5, 0xF6, n / 10);
        fn_8003649C(task, 9, 6, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 7)->flags |= 2;
        REP_OBJ(task, 8)->flags &= ~2;
        REP_OBJ(task, 9)->flags &= ~2;
        fn_8003649C(task, 7, 4, 0xF6, g_Scores.team[1].runs[0]);
    }
}

// .text:0x00093960 size:0x3FC mapped:0x806D29F4
void fn_3_93960(void) {
    RepTask* task = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x98] == 2) {
        lbl_3_common_bss_32724[0x98] = 1;
        task->timer = 0;
    }
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724[0x96] == 0 && (g_GameLogic.gameStatus != 3 || g_GameLogic._125 != 9) &&
        (g_GameLogic.gameStatus != 9 || g_GameLogic._125 != 4) &&
        (g_GameLogic.gameStatus != 5 || (g_GameLogic._125 != 0xA && g_GameLogic._125 != 0xB)) &&
        ((g_UnkSound_32718._07 != 7 && g_UnkSound_32718._07 != 0x14) || task->timer <= 30) &&
        g_GameLogic.gameStatus != 8 && g_GameLogic.gameStatus != 6 && (g_GameLogic.gameStatus != 2 || task->timer <= 90)) {
        s32 n = g_Scores.team[0].runs[0];
        if (n >= 10) {
            if (n >= 99) {
                n = 99;
            }
            REP_OBJ(task, 4)->flags &= ~2;
            REP_OBJ(task, 5)->flags |= 2;
            REP_OBJ(task, 6)->flags |= 2;
            fn_8003649C(task, 5, 2, 0xF6, n / 10);
            fn_8003649C(task, 6, 3, 0xF6, n % 10);
        } else {
            REP_OBJ(task, 4)->flags |= 2;
            REP_OBJ(task, 5)->flags &= ~2;
            REP_OBJ(task, 6)->flags &= ~2;
            fn_8003649C(task, 4, 1, 0xF6, g_Scores.team[0].runs[0]);
        }
        n = g_Scores.team[1].runs[0];
        if (n >= 10) {
            if (n >= 99) {
                n = 99;
            }
            REP_OBJ(task, 7)->flags &= ~2;
            REP_OBJ(task, 8)->flags |= 2;
            REP_OBJ(task, 9)->flags |= 2;
            fn_8003649C(task, 8, 5, 0xF6, n / 10);
            fn_8003649C(task, 9, 6, 0xF6, n % 10);
        } else {
            REP_OBJ(task, 7)->flags |= 2;
            REP_OBJ(task, 8)->flags &= ~2;
            REP_OBJ(task, 9)->flags &= ~2;
            fn_8003649C(task, 7, 4, 0xF6, g_Scores.team[1].runs[0]);
        }
        return;
    }
    lbl_3_common_bss_32724[0x98] = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}

// .text:0x00093D5C size:0x3E0 mapped:0x806D2DF0
// NONMATCHING 98%: same instructions; the 3<<16 constant and the slot-7..9 bases get r28/r29-r31 instead of r31/r28-r30
#if NONMATCHING
void fn_3_93D5C(void) {
    RepTask* task = lbl_803CC1B8[0];
    s32 n;
    fn_80034E20(task, lbl_3_data_EABC);
    REP_OBJ(task, 2)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain * 2 + 1];
    REP_OBJ(task, 3)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain * 2 + 1];
    REP_OBJ(task, 2)->_5C = g_GameLogic.logo[0].variationID << 16;
    REP_OBJ(task, 3)->_5C = g_GameLogic.logo[1].variationID << 16;
    REP_OBJ(task, 4)->_5C = 0 << 16;
    REP_OBJ(task, 5)->_5C = 1 << 16;
    REP_OBJ(task, 6)->_5C = 2 << 16;
    REP_OBJ(task, 7)->_5C = 3 << 16;
    REP_OBJ(task, 8)->_5C = 4 << 16;
    REP_OBJ(task, 9)->_5C = 5 << 16;
    n = g_Scores.team[0].runs[0];
    if (n >= 10) {
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 4)->flags &= ~2;
        REP_OBJ(task, 5)->flags |= 2;
        REP_OBJ(task, 6)->flags |= 2;
        fn_8003649C(task, 5, 2, 0xF6, n / 10);
        fn_8003649C(task, 6, 3, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 4)->flags |= 2;
        REP_OBJ(task, 5)->flags &= ~2;
        REP_OBJ(task, 6)->flags &= ~2;
        fn_8003649C(task, 4, 1, 0xF6, g_Scores.team[0].runs[0]);
    }
    n = g_Scores.team[1].runs[0];
    if (n >= 10) {
        if (n >= 99) {
            n = 99;
        }
        REP_OBJ(task, 7)->flags &= ~2;
        REP_OBJ(task, 8)->flags |= 2;
        REP_OBJ(task, 9)->flags |= 2;
        fn_8003649C(task, 8, 5, 0xF6, n / 10);
        fn_8003649C(task, 9, 6, 0xF6, n % 10);
    } else {
        REP_OBJ(task, 7)->flags |= 2;
        REP_OBJ(task, 8)->flags &= ~2;
        REP_OBJ(task, 9)->flags &= ~2;
        fn_8003649C(task, 7, 4, 0xF6, g_Scores.team[1].runs[0]);
    }
    lbl_3_common_bss_32724[0x98] = 1;
    task->timer = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_93960;
}
#endif

// .text:0x0009413C size:0x58 mapped:0x806D31D0
void fn_3_9413C(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || ((u8*)&g_GameLogic)[0x11E] != 9) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x00094194 size:0x574 mapped:0x806D3228
void fn_3_94194(void) {
    RepTask* task = lbl_803CC1B8[0];
    s32 i;
    s32 n;
    fn_80034E20(task, lbl_3_data_E85C);
    if (g_Scores.team[0].runs[0] == g_Scores.team[1].runs[0]) {
        REP_OBJ(task, 9)->_64 = 0xE6;
    }
    if (g_GameLogic.winType != 5 && g_GameLogic.winType != 6) {
        REP_OBJ(task, 17)->flags &= ~2;
    }
    for (i = 0; i < 3; i++) {
        lbl_80371C30[3 + task->baseIdx + i].obj->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain * 2 + 1];
        lbl_80371C30[6 + task->baseIdx + i].obj->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain * 2 + 1];
        lbl_80371C30[3 + task->baseIdx + i].obj->_5C = g_GameLogic.logo[0].variationID << 16;
        lbl_80371C30[6 + task->baseIdx + i].obj->_5C = g_GameLogic.logo[1].variationID << 16;
    }
    if (g_Scores.team[0].runs[0] < 10) {
        REP_OBJ(task, 10)->flags &= ~2;
        fn_800363D8(task, 11, 1, 0xF6, g_Scores.team[0].runs[0]);
    } else {
        n = g_Scores.team[0].runs[0];
        if (n > 99) {
            n = 99;
        }
        fn_800363D8(task, 10, 1, 0xF6, n / 10);
        fn_800363D8(task, 11, 1, 0xF6, n % 10);
    }
    if (g_Scores.team[1].runs[0] < 10) {
        if (g_GameLogic.winType == 3 || g_GameLogic.winType == 6) {
            fn_800363D8(task, 12, 1, 0xF6, g_Scores.team[1].runs[0]);
            fn_800363D8(task, 13, 1, 0xF6, 10);
        } else {
            fn_800363D8(task, 12, 1, 0xF6, g_Scores.team[1].runs[0]);
            REP_OBJ(task, 13)->flags &= ~2;
        }
    } else {
        n = g_Scores.team[1].runs[0];
        if (n > 99) {
            n = 99;
        }
        fn_800363D8(task, 12, 1, 0xF6, n / 10);
        fn_800363D8(task, 13, 1, 0xF6, n % 10);
    }
    if (g_Scores._A4 == 0) {
        REP_OBJ(task, 1)->_64 = 0xEC;
        REP_OBJ(task, 2)->_64 = 0xE9;
        REP_OBJ(task, 15)->flags &= ~2;
        REP_OBJ(task, 4)->flags |= 2;
        REP_OBJ(task, 5)->flags |= 2;
    } else if (g_Scores._A4 == 1) {
        REP_OBJ(task, 1)->_64 = 0xE8;
        REP_OBJ(task, 2)->_64 = 0xED;
        REP_OBJ(task, 16)->flags &= ~2;
        REP_OBJ(task, 7)->flags |= 2;
        REP_OBJ(task, 8)->flags |= 2;
    } else {
        for (i = 10; i < 14; i++) {
            lbl_80371C30[task->baseIdx + i].obj->_64 = 0xEA;
        }
        REP_OBJ(task, 1)->_64 = 0xE3;
        REP_OBJ(task, 2)->_64 = 0xE4;
        REP_OBJ(task, 14)->flags &= ~2;
        REP_OBJ(task, 15)->flags &= ~2;
        REP_OBJ(task, 16)->flags &= ~2;
    }
    *(void**)lbl_803CC1B8[0] = fn_3_9413C;
}

// .text:0x00094708 size:0x58 mapped:0x806D379C
void fn_3_94708(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || ((u8*)&g_GameLogic)[0x125] > 9) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x00094760 size:0x158 mapped:0x806D37F4
// NONMATCHING 98%: only the scheduling of `li r6,0x25` / `li r4,5` (original hoists them above the first stores)
#if NONMATCHING
void fn_3_94760(void) {
    RepTask* task;
    fn_80034E20(task = lbl_803CC1B8[0], lbl_3_data_E75C);
    REP_OBJ(task, 3)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain * 2];
    REP_OBJ(task, 4)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain * 2];
    REP_OBJ(task, 3)->_5C = g_GameLogic.logo[0].variationID << 16;
    REP_OBJ(task, 4)->_5C = g_GameLogic.logo[1].variationID << 16;
    fn_800363D8(task, 5, 1, 0x25, g_GameLogic.teams[g_GameLogic._000] + g_GameLogic._13E[g_GameLogic._000] * 4);
    fn_800363D8(task, 6, 1, 0x25, g_GameLogic.teams[g_GameLogic._000 ^ 1] + g_GameLogic._13E[g_GameLogic._000 ^ 1] * 4);
    *(void**)lbl_803CC1B8[0] = fn_3_94708;
}
#endif

// .text:0x000948B8 size:0x78 mapped:0x806D394C
void fn_3_948B8(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || ((u8*)&g_GameLogic)[0x11E] != 0x17 || (*(u8**)(((u8*)lbl_80371C30) + *(u16*)((u8*)p + 0x14) * 8))[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x00094930 size:0x4C mapped:0x806D39C4
void fn_3_94930(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_F3F0);
    *(void**)lbl_803CC1B8[0] = fn_3_948B8;
}

// .text:0x0009497C size:0x248 mapped:0x806D3A10
// NONMATCHING 99%: same instructions; the unrolled j loop loads order[i] before baseIdx and allocates temps differently
#if NONMATCHING
void fn_3_9497C(void) {
    RepTask* task = lbl_803CC1B8[0];
    u16 mode;
    s32 i;
    s32 j;
    LayoutObj* obj;
    if (lbl_3_common_bss_32724[0x96] != 0) {
        goto remove;
    }
    if (g_UnkSound_32718._07 == 0 || g_GameLogic.gameStatus == 1) {
        REP_OBJ(task, 0)->_68 = 1;
        REP_OBJ(task, 2)->_68 = 1;
        REP_OBJ(task, 3)->_68 = 1;
        REP_OBJ(task, 4)->_68 = 1;
        REP_OBJ(task, 5)->_68 = 1;
    }
    mode = task->_1C;
    if (mode == 2) {
        if (lbl_3_common_bss_32724[0xB4] == 0) {
            goto remove;
        }
    } else if (mode != 0) {
        if (g_GameLogic.gameStatus != 0x16) {
            goto remove;
        }
    } else if (lbl_3_common_bss_32724[0xB3] == 0) {
        goto remove;
    }
    if (mode != 2) {
        for (i = 0; i < task->_1A; i++) {
            for (j = 1; j < 6; j++) {
                obj = lbl_80371C30[task->baseIdx + (lbl_3_data_E758[i] + j)].obj;
                if ((obj->_5C >> 16) > 40) {
                    obj->_5C = 60 << 16;
                }
            }
        }
    }
    return;
remove:
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

// .text:0x00094BC4 size:0x2A4 mapped:0x806D3C58
// 99%: only the loop-setup copies differ (original `addi r7,r4,bss@l` / `addi r8,r3,DATA@l` direct; ours adds `mr r7,r4` / `mr r8,r0`)
void fn_3_94BC4(void) {
    u8* o = lbl_803CC1B8[0];
    s8* pb;
    s8* pa;
    s8* pc;
    u8* p;
    u8* d;
    s32 b;
    u8* t;
    s32 i;
    u8* e;
    s32 j;
    s32 s;
    s32 n;
    s32 k;
    if (lbl_3_common_bss_32724[0xB4] != 0) {
        *(u16*)(o + 0x1C) = 2;
    } else if (((u8*)&g_GameLogic)[0x11E] == 0x16) {
        *(u16*)(o + 0x1C) = 1;
    } else {
        *(u16*)(o + 0x1C) = 0;
    }
    fn_80034E20(o, lbl_3_data_E378);
    p = lbl_3_common_bss_37400;
    i = 0;
    d = lbl_3_data_E758;
    n = 0;
    do {
        if (*(s8*)(p + 0x15) != 0) {
            b = *d;
            *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + b) * 2] + 0x5C) = *(s8*)(p + 0x16) << 16;
            pb = (s8*)(p + 0x13);
            pa = (s8*)(p + 0x12);
            pc = (s8*)(p + 0x14);
            for (j = 0; j < 5; j++) {
                k = b + j + 1;
                if (j >= *pb) {
                    t = ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2];
                    *(u32*)(t + 0x54) &= ~2;
                } else {
                    t = ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2];
                    *(u32*)(t + 0x54) |= 2;
                    ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2][0x68] = 0;
                    *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2] + 0x5C) = 0;
                    s = *pa;
                    if (j < s) {
                        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2] + 0x5C) = 0x10000;
                    } else if (j < *pc + s) {
                        if (*(u16*)(o + 0x1C) == 2) {
                            *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2] + 0x5C) = 0x280000;
                        } else {
                            *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2] + 0x5C) = 0x3C0000;
                        }
                        ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + k) * 2][0x68] = 1;
                    }
                }
            }
            d++;
            n++;
        }
        i++;
        p += 5;
    } while (i < 9);
    if (n < 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    *(s32*)(((u8**)(((u8*)lbl_80371C30) + 8))[*(u16*)(o + 0x14) * 2] + 0x5C) = (n - 1) << 16;
    *(u16*)(o + 0x1A) = n;
    *(void**)lbl_803CC1B8[0] = fn_3_9497C;
}

// .text:0x00094E68 size:0x198 mapped:0x806D3EFC
void fn_3_94E68(void) {
    u8* p = lbl_803CC1B8[0];
    u8 g;
    if (lbl_3_common_bss_32724[0x96] == 0 && (*(u16*)(p + 0x1C) == lbl_3_common_bss_37400[0x46] || lbl_3_common_bss_37400[0x47] == 2) &&
        (g = ((u8*)&g_GameLogic)[0x11E]) != 3 && (g != 8 || lbl_3_common_bss_37400[0x47] == 0) && (g != 0 || lbl_3_common_bss_37400[0x47] != 2)) {
        if (((u8*)&g_Stats)[0x36] != 0) {
            LayoutSlot* t = lbl_80371C30;
            t[*(u16*)(p + 0x14)].obj->flags &= ~2;
            t[*(u16*)(p + 0x14) + 1].obj->flags &= ~2;
        } else if (g <= 1 || g == 2) {
            LayoutSlot* t = lbl_80371C30;
            t[*(u16*)(p + 0x14)].obj->flags |= 2;
            t[*(u16*)(p + 0x14) + 1].obj->flags |= 2;
        } else {
            LayoutSlot* t = lbl_80371C30;
            t[*(u16*)(p + 0x14)].obj->flags &= ~2;
            t[*(u16*)(p + 0x14) + 1].obj->flags &= ~2;
        }
        return;
    }
    fn_800B0A14_removeQueue(fn_80034CEC(p));
}

// .text:0x00095000 size:0x98 mapped:0x806D4094
void fn_3_95000(void) {
    u8* p;
    fn_80034E20(p = lbl_803CC1B8[0], lbl_3_data_E2F8);
    {
        u8** t = (u8**)((u8*)lbl_80371C30);
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400[0x46]];
        ((s32*)t[*(u16*)(p + 0x14) * 2 + 4])[0x5C / 4] = v << 16;
    }
    *(u16*)(p + 0x1C) = lbl_3_common_bss_37400[0x46];
    *(void**)lbl_803CC1B8[0] = fn_3_94E68;
}

// .text:0x00095098 size:0x8C mapped:0x806D412C
void fn_3_95098(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || (*(u8**)(((u8*)lbl_80371C30) + *(u16*)((u8*)p + 0x14) * 8))[0x69] == 2) {
        fn_800B0A5C_insertQueue(fn_3_95000, 2);
        lbl_3_common_bss_32724[0xB3] = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x00095124 size:0x90 mapped:0x806D41B8
void fn_3_95124(void) {
    u8* p;
    fn_80034E20(p = lbl_803CC1B8[0], lbl_3_data_E278);
    {
        u8** t = (u8**)((u8*)lbl_80371C30);
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400[0x46]];
        ((s32*)t[*(u16*)(p + 0x14) * 2 + 4])[0x5C / 4] = v << 16;
    }
    *(void**)lbl_803CC1B8[0] = fn_3_95098;
}

// .text:0x000951B4 size:0x128 mapped:0x806D4248
void fn_3_951B4(void) {
    void* p = lbl_803CC1B8[0];
    if (((u8*)&g_Ball)[0x1BD1] == 1) {
        if (((u8*)&g_GameLogic)[0x11E] == 0x14) {
            (*(u8**)(((u8*)lbl_80371C30) + *(u16*)((u8*)p + 0x14) * 8))[0x68] = 1;
        }
        if (((u8*)&g_GameLogic)[0x11E] == 2 || ((u8*)&g_GameLogic)[0x11E] == 0x14) {
            return;
        }
    } else {
        if (((u8*)&g_UnkSound_32718)[7] == 0 || ((u8*)&g_GameLogic)[0x11E] == 1) {
            (*(u8**)(((u8*)lbl_80371C30) + *(u16*)((u8*)p + 0x14) * 8))[0x68] = 1;
        }
        if (lbl_3_common_bss_32724[0x96] == 0 && *(s16*)(lbl_3_common_bss_37400 + 0x42) != 0) {
            if (((u8*)&g_GameLogic)[0x11E] == 1 || ((u8*)&g_GameLogic)[0x11E] == 2) {
                return;
            }
        }
    }
    lbl_3_common_bss_32724[0xB4] = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(p));
}

// .text:0x000952DC size:0xB0 mapped:0x806D4370
void fn_3_952DC(void) {
    u8* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0xB5] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    fn_80034E20(p, lbl_3_data_E21C);
    if (lbl_3_common_bss_37400[0x47] == 1) {
        u8** t = (u8**)((u8*)lbl_80371C30);
        *(s16*)(t[*(u16*)(p + 0x14) * 2] + 0x64) = 0x5A;
    }
    lbl_3_common_bss_32724[0xB5] = 1;
    *(void**)lbl_803CC1B8[0] = fn_3_951B4;
}

// .text:0x0009538C size:0x70 mapped:0x806D4420
void fn_3_9538C(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || ((u8*)&g_GameLogic)[0x11E] != 0x16) {
        fn_800B0A5C_insertQueue(fn_3_95000, 2);
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x000953FC size:0xC8 mapped:0x806D4490
void fn_3_953FC(void) {
    u8* p;
    fn_80034E20(p = lbl_803CC1B8[0], lbl_3_data_E160);
    {
        u8** t = (u8**)((u8*)lbl_80371C30);
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400[0x46]];
        ((s32*)t[*(u16*)(p + 0x14) * 2 + 4])[0x5C / 4] = v << 16;
    }
    {
        u8** t = (u8**)((u8*)lbl_80371C30);
        s32 v = lbl_3_data_E200[lbl_3_common_bss_37400[0x46]];
        ((s32*)t[*(u16*)(p + 0x14) * 2 + 6])[0x5C / 4] = v << 16;
    }
    lbl_3_common_bss_32724[0xB4] = 0;
    lbl_3_common_bss_32724[0xB3] = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_9538C;
}

// .text:0x000954C4 size:0x58 mapped:0x806D4558
void fn_3_954C4(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || ((u8*)&g_GameLogic)[0x11E] != 0x16) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x0009551C size:0x4C mapped:0x806D45B0
void fn_3_9551C(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_E120);
    *(void**)lbl_803CC1B8[0] = fn_3_954C4;
}

// .text:0x00095568 size:0x64 mapped:0x806D45FC
void fn_3_95568(void) {
    void* p = lbl_803CC1B8[0];
    if (lbl_3_common_bss_32724[0x96] != 0 || (*(u8**)(((u8*)lbl_80371C30) + *(u16*)((u8*)p + 0x14) * 8))[0x69] == 2) {
        fn_800B0A14_removeQueue(fn_80034CEC(p));
    }
}

// .text:0x000955CC size:0x54 mapped:0x806D4660
void fn_3_955CC(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_E0E0);
    playSoundEffect(0x1A9);
    *(void**)lbl_803CC1B8[0] = fn_3_95568;
}

// .text:0x00095620 size:0x350 mapped:0x806D46B4
// NONMATCHING 97%: original loads the -2.0f / int->float constants through `addi rN; lfs 0(rN)` and schedules the two conversions differently
#if NONMATCHING
void fn_3_95620(void) {
    RepTask* task = lbl_803CC1B8[0];
    RepFielderView* f;
    int sx;
    int sy;
    s16 idx;
    if (lbl_3_common_bss_32724[0x96] != 0) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 2) {
        if (g_GameLogic.secondaryGameMode == 0xD || (u8)(g_GameLogic.secondaryGameMode - 0xE) <= 1 || g_GameLogic.secondaryGameMode == 0x10) {
            if (g_Practice._186 != 0) {
                REP_OBJ(task, 0)->flags &= ~2;
                return;
            }
        } else {
            REP_OBJ(task, 0)->flags &= ~2;
            return;
        }
    }
    if (g_Stats.replayInd != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic.gameStatus != 2) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic.sceneID == 1) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic._13E[g_GameLogic.teamFielding] != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] != 0 && g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    if (g_FieldingLogic._139 != 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    idx = g_FieldingLogic._0B0;
    if (idx < 0) {
        REP_OBJ(task, 0)->flags &= ~2;
        return;
    }
    REP_OBJ(task, 0)->flags |= 2;
    f = &g_Fielders[idx];
    fn_3_1650C(&sx, &sy, FALSE, f->x, -2.0f - f->_00C, f->z);
    REP_OBJ(task, 0)->x = sx;
    REP_OBJ(task, 0)->y = sy;
    REP_OBJ(task, 0)->color = (REP_OBJ(task, 0)->color & 0xFF) | 0xFFFFFF00;
}
#endif

// .text:0x00095970 size:0x4C mapped:0x806D4A04
void fn_3_95970(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_C1EC);
    *(void**)lbl_803CC1B8[0] = fn_3_95620;
}

// .text:0x000959BC size:0xCE0 mapped:0x806D4A50
// NONMATCHING 91%: (with the alpha helper pasted in by hand; it stays a call here because the file ends in
// `dont_inline on`) block layout of the i == 0 runner case, a few `+1` slot offsets folded into lwz, regalloc
#if NONMATCHING
static inline void fn_3_959BC_setAlpha(RepFieldHudTask* task, s32 alpha) {
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        for (i = 1; i < 6; i++) {
            lbl_80371C30[task->baseIdx + i].obj->color = alpha | (lbl_80371C30[task->baseIdx + i].obj->color & ~0xFF);
        }
    } else {
        for (i = 1; i < 14; i++) {
            lbl_80371C30[task->baseIdx + i].obj->color = alpha | (lbl_80371C30[task->baseIdx + i].obj->color & ~0xFF);
        }
    }
}

void fn_3_959BC(void) {
    RepFieldHudTask* task = lbl_803CC1B8[0];
    s32 i;
    s32 any;
    s32 phase;
    s32 digit;
    s32 slot;
    s32 alpha;
    u8 status;
    InMemRunnerType* r;
    f32 sx;
    f32 sy;
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724[0x96] != 0 ||
        (g_d_GameSettings.GameModeSelected == 2 && (g_Practice.tutorialState == 0 || g_Practice._1C7 != 0))) {
        goto remove;
    }
    if (task->blinkTimer != 0) {
        if (task->blinkTimer < 0xFFFE) {
            task->blinkTimer++;
        } else {
            task->blinkTimer = 0xFFFF;
        }
    }
    if (g_d_GameSettings.GameModeSelected == 6) {
        if (g_Minigame.framesSincePanelHit == 1) {
            any = 0;
            for (i = 0; i < 4; i++) {
                if (g_Minigame._191C[i] > i) {
                    any = 1;
                }
            }
            if (any) {
                task->blinkTimer = 1;
            }
        }
        if (task->blinkTimer != 0) {
            for (i = 1; i < 5; i++) {
                lbl_80371C30[task->baseIdx + i].obj->flags &= ~2;
            }
            phase = (task->blinkTimer - 1) % 45;
            if (phase == 0) {
                for (i = 0; i < 4; i++) {
                    digit = task->progress[i] % 10;
                    if (digit == 4) {
                        task->progress[i] = 14;
                    } else if (digit < g_Minigame._191C[i]) {
                        task->progress[i]++;
                        lbl_80371C30[(task->progress[i] % 10) % 4 + task->baseIdx + 1].obj->flags |= 2;
                    } else if (digit > 0 && digit < 4 && digit == g_Minigame._191C[i]) {
                        lbl_80371C30[digit % 4 + task->baseIdx + 1].obj->flags |= 2;
                        if (task->progress[i] < 10) {
                            task->progress[i] += 10;
                        }
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                slot = (task->progress[i] % 10) % 4 + 1;
                if (task->progress[i] <= g_Minigame._191C[i]) {
                    if (slot == 1) {
                        lbl_80371C30[task->baseIdx + slot].obj->flags |= 2;
                    } else if (phase <= 15 || phase > 30) {
                        lbl_80371C30[task->baseIdx + slot].obj->flags |= 2;
                    }
                    g_Minigame._1925 |= 1 << (slot - 1);
                } else if (task->progress[i] >= 10) {
                    g_Minigame._1925 |= 1 << (slot - 1);
                    lbl_80371C30[task->baseIdx + slot].obj->flags |= 2;
                }
            }
        }
    } else {
        // runner markers (slots 1-4) and occupied-base markers (slots 9-11)
        lbl_80371C30[task->baseIdx + 9].obj->flags &= ~2;
        lbl_80371C30[task->baseIdx + 10].obj->flags &= ~2;
        lbl_80371C30[task->baseIdx + 11].obj->flags &= ~2;
        r = g_Runners;
        for (i = 0; i < 4; i++, r++) {
            status = r->runnerOnFieldOrOutOrScored;
            if (status != 1 || g_Strikes.outs >= 3) {
                lbl_80371C30[task->baseIdx + (i + 1)].obj->flags &= ~2;
                continue;
            }
            if (i == 0) {
                if (g_Ball.framesSinceHit < 1) {
                    lbl_80371C30[task->baseIdx + (i + 1)].obj->flags &= ~2;
                    continue;
                }
                if (status == 1 || status == 5) {
                    if (g_Ball.framesSinceHit < 16) {
                        lbl_80371C30[task->baseIdx + (i + 1)].obj->color =
                            (g_Ball.framesSinceHit * 16) | (lbl_80371C30[task->baseIdx + (i + 1)].obj->color & ~0xFF);
                    } else {
                        lbl_80371C30[task->baseIdx + (i + 1)].obj->color = (lbl_80371C30[task->baseIdx + (i + 1)].obj->color & ~0xFF) | 0xFF;
                    }
                }
            } else {
                lbl_80371C30[task->baseIdx + (i + 1)].obj->color = (lbl_80371C30[task->baseIdx + (i + 1)].obj->color & ~0xFF) | 0xFF;
            }
            lbl_80371C30[task->baseIdx + (i + 1)].obj->flags |= 2;
            sx = lbl_3_data_C1CC[2] * r->position.x;
            sy = lbl_3_data_C1CC[3] * -r->position.z;
            lbl_80371C30[task->baseIdx + (i + 1)].obj->x = sx + lbl_3_data_C1CC[0];
            lbl_80371C30[task->baseIdx + (i + 1)].obj->y = sy + lbl_3_data_C1CC[1];
            if (r->currentBase >= 1 && r->currentBase <= 3) {
                lbl_80371C30[task->baseIdx + r->currentBase + 8].obj->flags |= 2;
            }
        }
        // steal indicator (slot 12)
        REP_OBJ(task, 12)->flags &= ~2;
        if (g_GameLogic.sceneID == 1) {
            for (i = 1; i < 4; i++) {
                if (g_Runners[i].runnerOnFieldOrOutOrScored != 0 && g_Runners[i].furthestBaseForcedToGoToOnWalk != 0) {
                    REP_OBJ(task, 12)->flags |= 2;
                    for (; i < 4; i++) {
                        if (g_Runners[i].stealingStatus == 3) {
                            break;
                        }
                    }
                    if (i < 4) {
                        REP_OBJ(task, 12)->_64 = 0xA2;
                    } else {
                        REP_OBJ(task, 12)->_64 = 0xA6;
                    }
                    break;
                }
            }
        }
        // CPU-batting indicator (slot 13)
        REP_OBJ(task, 13)->flags &= ~2;
        if (g_d_GameSettings.GameModeSelected != 2 && g_GameLogic._13E[g_GameLogic.teamBatting] == 0 &&
            g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] != 0) {
            REP_OBJ(task, 13)->flags |= 2;
        }
    }
    if (task->timer <= 16) {
        alpha = task->timer * 16;
        if (alpha > 0xFF) {
            alpha = 0xFF;
        }
        fn_3_959BC_setAlpha(task, alpha);
    }
    if (((RepPauseView*)&lbl_3_common_bss_34C90)->_1D5 != 0 && g_d_GameSettings.GameModeSelected != 6) {
        alpha = 0xF0 - ((RepPauseView*)&lbl_3_common_bss_34C90)->_00C * 16;
        if (alpha <= 0) {
            goto remove;
        }
        fn_3_959BC_setAlpha(task, alpha);
    }
    if (g_GameLogic.hudLoadingRelated == 0 && g_GameLogic.gameStatus != 3 && g_GameLogic.gameStatus != 0xE &&
        g_GameLogic.secondaryGameMode != 0xA) {
        return;
    }
remove:
    lbl_3_common_bss_32724[0xC7] = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

// .text:0x0009669C size:0x278 mapped:0x806D5730
void fn_3_9669C(void) {
    u8* o = lbl_803CC1B8[0];
    s32 k;
    u8* r;
    if (g_d_GameSettings.GameModeSelected == 6) {
        fn_80034E20(o, lbl_3_data_8D88);
        for (k = 1; k < 4; k++) {
            if (((u8*)&g_Minigame)[0x1914 + k] != 0) {
                u8* e = ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) - (-1) - (-k)) * 2];
                *(u32*)(e + 0x54) |= 2;
                ((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) - (-1) - (-k)) * 2][0x68] = 0;
                *(u16*)(o + 0x1C + k * 2) = k;
            } else {
                *(u16*)(o + 0x1C + k * 2) = 9;
            }
            *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) - (-1) - (-k)) * 2] + 0x5C) = (k - 1) << 16;
        }
        if (((u8*)&g_Minigame)[0x19A2] != 0) {
            u8* e = ((u8*)lbl_80371C30);
            e += *(u16*)(o + 0x14) * 8;
            e = *(u8**)(e + 0x28);
            *(u32*)(e + 0x54) |= 2;
        }
    } else {
        fn_80034E20(o, lbl_3_data_BFEC);
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + 9) * 2] + 0x5C) = 0;
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + 0xA) * 2] + 0x5C) = 0x10000;
        *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + 0xB) * 2] + 0x5C) = 0x20000;
        r = ((u8*)g_Runners);
        for (k = 0; k < 4; k++, r += 0x154) {
            s16 v = *(s16*)(r + 0xE2);
            if (v >= 0) {
                *(s32*)(((u8**)lbl_80371C30)[(*(u16*)(o + 0x14) + 5 + k) * 2] + 0x5C) = v << 16;
            }
        }
    }
    lbl_3_common_bss_32724[0xC7] = 1;
    *(u16*)(o + 0x18) = 0;
    *(u16*)(o + 0x1A) = 0;
    *(u16*)(o + 0x1C) = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_959BC;
}

// .text:0x00096914 size:0x78 mapped:0x806D59A8
void fn_3_96914(void) {
    if (lbl_3_common_bss_32724[0xC7] == 0 && ((u8*)&g_GameLogic)[0x12D] != 0) {
        fn_800B0A5C_insertQueue(fn_3_9669C, 2);
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_800B0A5C_insertQueue(fn_3_ED574, 2);
        }
    }
}

// .text:0x0009698C size:0x318 mapped:0x806D5A20
void fn_3_9698C(void) {
    RepTask* task = lbl_803CC1B8[0];
    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    if (lbl_3_common_bss_32724[0x96] != 0 || g_Stats.replayInd != 0) {
        goto remove;
    }
    if (task->_1C == 15) {
        if (REP_OBJ(task, 0)->_69 == 2) {
            if (g_d_GameSettings.GameModeSelected == 6) {
                fn_800B0A5C_insertQueue(fn_3_ED0F4, 2);
            }
            goto remove;
        }
        if (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 20) {
            goto remove;
        }
    } else if (task->_1E == 2) {
        if (REP_OBJ(task, 0)->_69 == 2 || g_GameLogic.hudElementLoadingInd != 0) {
            goto remove;
        }
        if (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0) {
            goto remove;
        }
    } else if (task->_1E == 1) {
        if (g_GameLogic.hudElementLoadingInd != 0) {
            goto remove;
        }
        if (g_GameLogic.gameStatus != 2 && g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0) {
            goto remove;
        }
    }
    if (task->_1E == 0) {
        if ((REP_OBJ(task, 0)->_5C >> 16) >= lbl_3_data_BE50.kinds[task->_1C][1]) {
            task->_1E = 1;
            REP_OBJ(task, 0)->_68 = 0;
        }
    } else if (task->_1E == 1) {
        if (g_UnkSound_32718._02 != 0 || (g_d_GameSettings.exhibitionMatchInd == 0 && lbl_3_common_bss_32724[0xB4] != 0)) {
            REP_OBJ(task, 0)->_68 = 1;
            task->_1E = 2;
        } else {
            if (task->_1A < 0xFFFE) {
                task->_1A++;
            } else {
                task->_1A = 0xFFFF;
            }
            if (task->_1A >= lbl_3_data_BE50.kinds[task->_1C][2]) {
                REP_OBJ(task, 0)->_68 = 1;
                task->_1E = 2;
            }
        }
    }
    if ((task->_1C == 0x10 || task->_1C == 0x16) && task->timer == 0x23) {
        playSoundEffect(0x15C);
    }
    return;
remove:
    g_UnkSound_32718._07 = 0;
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}

// .text:0x00096CA4 size:0x4A0 mapped:0x806D5D38
// NONMATCHING 87%: original reaches lbl_3_data_BE50 through the pooled lbl_3_data_8D88 base (+0x30C8/+0x3190/+0x31A4; data defined in this TU), so registers and stack frame differ
#if NONMATCHING
void fn_3_96CA4(void) {
    RepTask* task = lbl_803CC1B8[0];
    s16 anim;
    u32 stadium;
    u8 v;
    s32 voice;
    s32 lead;
    s16 runs;
    if (g_UnkSound_32718._07 == 0xD && lbl_3_common_bss_32724[0x98] != 0) {
        return;
    }
    task->_1C = g_UnkSound_32718._07;
    anim = lbl_3_data_BE50.kinds[task->_1C][0];
    if (g_d_GameSettings.minigamesEnabled == 0 && (anim == 0xBB || anim == 0xFD)) {
        if (++lbl_3_common_bss_32724[0xA9] == 2) {
            task->_1C = 0x17;
        }
        if (lbl_3_common_bss_32724[0xA9] == 3) {
            task->_1C = 0x18;
        }
        anim = lbl_3_data_BE50.kinds[task->_1C][0];
    }
    switch (g_UnkSound_32718._07) {
    case 1:
        playSoundEffect(0x15C);
        break;
    case 2:
        playSoundEffect(0x15D);
        break;
    case 5:
        playSoundEffect(0x165);
        break;
    case 8:
        playSoundEffect(0x15A);
        break;
    case 9:
        playSoundEffect(0x15B);
        break;
    case 10:
        playSoundEffect(0x162);
        break;
    case 11:
        playSoundEffect(0x163);
        break;
    case 12:
        playSoundEffect(0x15E);
        break;
    case 18:
        playSoundEffect(0x15C);
        break;
    case 14:
        playSoundEffect(0x15F);
        break;
    case 13:
    case 17:
        playSoundEffect(0x160);
        break;
    case 3:
        playSoundEffect(0x164);
        break;
    case 4:
        playSoundEffect(0x166);
        break;
    case 6:
        playSoundEffect(0x167);
        break;
    case 21:
        if (lbl_800EF808[0x398] == 1) {
            stadium = g_d_GameSettings.StadiumID;
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[25].vol;
            } else {
                v = lbl_3_data_8404[stadium * 15 + 25].vol;
            }
            voice = sndFXStartEx(lbl_3_data_81DC[stadium] + 0x19, v, 0x3F, 0);
            if (g_d_GameSettings.GameModeSelected == 6) {
                v = lbl_3_data_84B8[25].ctrl;
            } else {
                v = lbl_3_data_8404[stadium * 15 + 25].ctrl;
            }
            sndFXCtrl(voice, 0x5B, v);
        }
        break;
    case 16:
        playSoundEffect(0x15A);
        break;
    case 22:
        playSoundEffect(0x164);
        break;
    }
    lbl_3_data_BE50.desc[0].animId = anim;
    if (g_d_GameSettings.GameModeSelected != 6 && task->_1C == 0xF) {
        lead = 0;
        if (g_d_GameSettings.GameModeSelected == 2) {
            lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[g_RunningLogic.runsScored - 1];
        } else {
            runs = g_Scores.team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
            if (g_Scores._A0 < runs && g_Scores._A0 + g_RunningLogic.runsScored > runs) {
                lead = 1;
            }
            if (g_Scores.inning >= g_Scores.maxInnings && g_Scores._AD != 0 && g_Scores._A0 + g_RunningLogic.runsScored > runs) {
                if (lead) {
                    if (g_RunningLogic.runsScored == 4) {
                        lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[8];
                    } else {
                        lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[7];
                    }
                } else {
                    lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[6];
                }
            } else if (lead) {
                if (g_RunningLogic.runsScored == 4) {
                    lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[5];
                } else {
                    lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[4];
                }
            } else {
                lbl_3_data_BE50.desc[0].animId = lbl_3_data_BE50.runsAnim[g_RunningLogic.runsScored - 1];
            }
        }
    }
    if (task->_1C == 0x15) {
        lbl_3_data_BE50.desc[0].texId = 0xE;
    } else {
        lbl_3_data_BE50.desc[0].texId = 2;
    }
    fn_80034E20(task, lbl_3_data_BE50.desc);
    if (g_d_GameSettings.GameModeSelected == 6) {
        REP_OBJ(task, 0)->y = lbl_3_data_BE50.kinds[task->_1C][3];
    }
    task->timer = 0;
    task->_1A = 0;
    task->_1E = 0;
    *(void**)lbl_803CC1B8[0] = fn_3_9698C;
}
#endif

