#include "game/auto_00_00157DB8_text.h"
#include "game/rep_1200.h"
#include "game/auto_00_0005985C_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80011640.h"
#include "game/auto_00_000B3B70_text.h"
#include "main/file_8000F150.h"
#include "game/rep_1770.h"

extern s16 lbl_3_data_FC1C;
extern u8 lbl_3_data_BD90[];
extern u8 lbl_3_data_BD50[];
extern u8 lbl_3_data_B3F4[];
extern u8 lbl_800EF808[];
extern void fn_80034E20(void*, void*);
extern void* fn_80033A24(void*, int, int, int, int, int);
extern void fn_3_6B870(void);
extern void* lbl_803CC1B8[];
extern u32 fn_3_157AC4(u8* o);
extern void fn_3_5F154(void);
extern void fn_3_5EFEC(void);
extern void fn_3_5EDD8(void);
extern void fn_3_5F3FC(void);
extern void fn_3_5CD24(void);
extern void fn_3_9669C(void);
extern u8 lbl_3_data_FAF4[];
extern u8 lbl_3_data_B85C[];
extern PracticeHudBss lbl_3_common_bss_32724;
extern PracticeTutorBss lbl_3_common_bss_34C90;
extern void fn_3_8A350(void);
extern void fn_3_F7B8(void);
extern void fn_3_59338(void);
extern PracticeMsgEntry lbl_3_data_103B8[][4][4];
extern u8 lbl_3_data_FAA8[3][9];
extern s16 lbl_3_data_104B8[][2][3];
extern u8 lbl_3_data_B1BC[];
extern u16 lbl_3_data_B3DC[6];
extern u16 lbl_3_data_B3E8[6];
extern u8 lbl_3_data_FAC4[8];

// fn_3_157DB8, size:0x70
void fn_3_157DB8(s32 arg0) {
    u8* p = fn_80033A24(fn_3_157AC4, 0x80, 0, 1, 1, 0x16);
    if (p != NULL) {
        *(s32*)(p + 0x18) = 0;
        *(s32*)(p + 0x1C) = arg0;
        (*(u8**)(p + 0xC))[0x4D] = 0;
        *(s32*)(*(u8**)(p + 0xC) + 0x40) = -1;
    }
}

// fn_3_1580AC, size:0x60
void fn_3_1580AC(void) {
    PracticeMsgTask* o = lbl_803CC1B8[0];
    fn_80034E20(o, lbl_3_data_BD90);
    o->state = 0;
    o->text = 0;
    ((PracticeTask*)lbl_803CC1B8[0])->callback = fn_3_157E28;
}

// fn_3_15810C, size:0xF0
void fn_3_15810C(void) {
    PracticeTask* o = lbl_803CC1B8[0];
    s32 lim;
    if (lbl_3_common_bss_32724._96 == 0) {
        lim = 0x96;
        if (g_Practice.practiceType_2 == 0) {
            lim = 0x5A;
        }
        if (g_Practice._186 < lim - 0x14) {
            LayoutObj* t = lbl_80371C30[o->baseIdx].obj;
            if ((t->_5C >> 16) >= 0x21) {
                t->_68 = 0;
            }
        } else {
            lbl_80371C30[o->baseIdx].obj->_68 = 1;
        }
        if (g_Practice._1C7 == 0 || lbl_3_common_bss_34C90._1D2 != 0) {
            return;
        }
    }
    fn_800B0A14_removeQueue(fn_80034CEC(o));
}

// fn_3_1581FC, size:0x68
void fn_3_1581FC(void) {
    fn_80034E20(lbl_803CC1B8[0], lbl_3_data_BD50);
    if (lbl_800EF808[0x398] == 1) {
        playSoundEffect(0x1AD);
    }
    ((PracticeTask*)lbl_803CC1B8[0])->callback = fn_3_15810C;
}

// fn_3_158264, size:0x148
void fn_3_158264(PracticeTask* o) {
    s32 v;
    s32 c;
    u8* row = lbl_3_data_FAF4 + g_Practice.practiceType_2 * 4;
    v = row[g_Practice.practiceLevel];
    fn_800363D8(o, 1, 3, 0x32, v);
    fn_800363D8(o, 1, 4, 0x32, v);
    c = g_Practice.guidedPracticeCounter;
    fn_800363D8(o, 1, 1, 0x32, c);
    fn_800363D8(o, 1, 2, 0x32, c);
    if (c != o->_1A) {
        LayoutSlot* t = &lbl_80371C30[1];
        LayoutObj* q = t[o->baseIdx].obj;
        if ((q->_5C >> 16) <= 9) {
            q->_5C = 0xA0000;
            t[o->baseIdx].obj->_68 = 1;
        }
        q = t[o->baseIdx].obj;
        if ((q->_5C >> 16) >= 0x13) {
            q->_5C = 0x90000;
            t[o->baseIdx].obj->_68 = 0;
            o->_1A = c;
        }
    }
}

// fn_3_1589C4, size:0x1A0
void fn_3_1589C4(void) {
    if (g_Practice.practiceType_2 == 0 || g_Practice.practiceType_2 == 1 || g_Practice.practiceType_2 == 2) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            if (lbl_3_common_bss_32724._C6 == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                lbl_3_common_bss_32724._C6 = 1;
            }
            if (g_Practice.practiceType_2 == 2 && g_Ball.totalFramesAtPlay == 1) {
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice.practiceType_2 == 2) {
                if (g_Practice._186 == 0x3C) {
                    fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
                }
            } else if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    } else if (g_Practice.practiceType_2 == 3) {
        if (g_Practice.tutorialState == 3 && g_Practice._1C7 == 0) {
            if (lbl_3_common_bss_32724._C7 == 0) {
                fn_800B0A5C_insertQueue(fn_3_1586B0, 2);
                fn_800B0A5C_insertQueue(fn_3_9669C, 2);
            }
            if (g_Practice._186 == 1) {
                fn_800B0A5C_insertQueue(fn_3_1581FC, 2);
            }
        }
    }
}

// fn_3_1590C8, size:0x4C
void fn_3_1590C8(void) {
    if (g_Practice.tutorialState == 0 && g_Practice.practiceState == 7) {
        fn_800B0A5C_insertQueue(fn_3_158FE4, 2);
    }
}

// fn_3_159590, size:0x64
void fn_3_159590(void) {
    PracticeTask* o = lbl_803CC1B8[0];
    fn_80034E20(o, lbl_3_data_B3F4);
    o->timer = 0;
    o->_1A = 0;
    o->text[0] = 0;
    ((PracticeTask*)lbl_803CC1B8[0])->callback = fn_3_159114;
}

// fn_3_15AD94, size:0x40
void fn_3_15AD94(void) {
    if (g_Pitcher.currentStateFrameCounter > lbl_3_data_FC1C) {
        fn_3_750C4(2);
    }
}

// fn_3_15ADD4, size:0x60
void fn_3_15ADD4(void) {
    fn_3_6B870();
    g_GameLogic._135 = 0;
    g_GameLogic._136 = 0;
    if (g_GameLogic.secondaryGameMode == 0xF && g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    fn_3_5A6D4(7);
}


// fn_3_15AF78, size:0x160
void fn_3_15AF78(void) {
    g_GameLogic.hudElementLoadingInd = 0;
    g_GameLogic.hudLoadingRelated = 0;
    if (g_Ball.totalFramesAtPlay < 0x7FFE) {
        g_Ball.totalFramesAtPlay++;
    } else {
        g_Ball.totalFramesAtPlay = 0x7FFF;
    }
    if (g_Practice.frames_sinceMovedToFromMenu < 0xFFFE) {
        g_Practice.frames_sinceMovedToFromMenu++;
    } else {
        g_Practice.frames_sinceMovedToFromMenu = 0xFFFF;
    }
    switch (g_GameLogic.gameStatus) {
    case 0:
        fn_3_5F154();
        break;
    case 1:
        fn_3_5EFEC();
        break;
    case 2:
        fn_3_5EDD8();
        break;
    case 7:
        fn_3_5F3FC();
        if (g_GameLogic.FrameCountOfCurrentPitch == 1) {
            fn_3_15AE34();
        }
        break;
    case 8:
        fn_3_15ADD4();
        break;
    case 10:
        fn_3_5CD24();
        break;
    }
    if (g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
        g_Strikes.outs = 0;
    }
}

// fn_3_15B610, size:0x18C
void fn_3_15B610(void) {
    switch (g_Practice.tutorialState) {
    case 0:
        fn_3_15B494();
        break;
    case 3:
        fn_3_15AF78();
        break;
    }
}

// fn_3_158FE4, size:0xE4
void fn_3_158FE4(void) {
    PracticeMsgTask* o;
    LayoutObj* w;
    LayoutSlot* e;
    fn_80034E20(o = lbl_803CC1B8[0], lbl_3_data_B85C);
    e = lbl_80371C30;
    e += o->baseIdx;
    w = e[8].obj;
    w->flags &= ~2;
    fn_800363D8(o, 0xD, 1, 0xE, g_Practice.practiceLevel);
    fn_800363D8(o, 0xD, 2, 0xE, g_Practice.practiceLevel);
    g_Practice.laukituTextChannelIndex = -1;
    g_Practice.diagramTextChannelIndex = -1;
    o->timer = 0;
    o->_1A = 0;
    o->state = 0;
    o->text = 0;
    o->_20 = 0;
    ((PracticeTask*)lbl_803CC1B8[0])->callback = fn_3_158B64;
}

// .text:0x0015B0D8 size:0x12C
void fn_3_15B0D8(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        g_GameLogic._13E[i] = 0;
        g_GameLogic._140[i] = 0;
        g_GameLogic.teamAIInd[i] = 0;
        g_GameLogic.autoFielding[i] = 0;
        g_GameLogic.batterHandedness[i] = 0;
        g_GameLogic.battingAIInd[i] = 0;
    }
    g_Practice.aIEnabled = 0;
    g_Practice.practiceBatterHandedness = 0;
    g_Practice.freePracticeInd_writeOnly = 0;
    g_Practice._1A4 = 0;
    if (g_GameLogic.secondaryGameMode == 0xF) {
        g_Practice.aIEnabled = 1;
        g_GameLogic._13E[g_GameLogic.teamFielding] = 1;
        g_Practice.freePracticeInd_writeOnly = 1;
        g_GameLogic._140[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_Practice.rosterID = 1;
        g_GameLogic.teamAIInd[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
        g_GameLogic.autoFielding[g_GameLogic.awayTeamBattingInd_battingTeam] = 1;
    } else {
        g_Practice.practiceBatterHandedness = 1;
        g_GameLogic._13E[g_GameLogic.teamBatting] = 1;
        g_Practice._1A4 = 1;
        g_GameLogic.batterHandedness[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
        g_GameLogic.battingAIInd[g_GameLogic.homeTeamBattingInd_fieldingTeam] = 1;
    }
    g_Practice._186 = 0;
    fn_3_5A684();
    fn_3_8A350();
    fn_3_F7B8();
    fn_3_75434();
    fn_3_59338();
    g_GameLogic.EventTriggers_GameHasStarted = 0;
    g_GameLogic.currentBatterPerTeam[0] = 1;
    g_GameLogic.currentBatterPerTeam[1] = 1;
}

// .text:0x0015AE34 size:0x144

// NONMATCHING 97%: register coloring of the ids[] constants and second-loop pointer (r7/r9), stw scheduling
// .text:0x0015AE34 size:0x144
#if NONMATCHING
void fn_3_15AE34(void) {
    s32 ids[4];
    InMemRunnerType* r;
    s32* q;
    s32* p;
    s32 i;
    s32 j;

    if (g_GameLogic.secondaryGameMode == 0xF) {
        q = ids;
        ids[0] = 1;
        ids[1] = 2;
        ids[2] = 3;
        ids[3] = 4;
        for (i = 0, p = q; i < 4; i++, p++) {
            for (j = 1, r = &g_Runners[1]; j < 4; j++, r++) {
                if (r->rosterID == *p) {
                    *p = -1;
                }
            }
        }
        for (i = 0; i < 4; q++, i++) {
            if (*q >= 0) {
                g_Practice.rosterID = ids[i];
                break;
            }
        }
    }
    if (g_GameLogic.TeamStars[0] == 0) {
        g_GameLogic.TeamStars[0] = 5;
    }
    if (g_GameLogic.TeamStars[1] == 0) {
        g_GameLogic.TeamStars[1] = 5;
    }
    if (g_Strikes.outs >= 3) {
        g_Strikes.outs = 0;
    }
    g_Practice.guidedPracticeCompletionRelated = 0;
}
#endif

// .text:0x0015B494 size:0x17C
// NONMATCHING 95%: case 3 roster lookup address arithmetic scheduled differently (r4/r5 swap); rest only jumptable label
#if NONMATCHING
void fn_3_15B494(void) {
    switch (g_Practice.practiceState) {
    case 0:
        lbl_8036E548.state = 0;
        lbl_8036E548._2D7A[1] = 0;
        lbl_8036E548._2D7C = 0;
        lbl_3_common_bss_32724._9C = 0;
        g_Practice._1D9 = 0;
        g_Practice._1C7 = 0;
        lbl_8036E548._307D = 0;
        fn_3_15B204();
        fn_3_15B0D8();
        fn_80011BE4(9);
        fn_3_B3C94(1);
        break;
    case 1:
        if (fn_8001594C(g_GameLogic.teamFielding) != 0) {
            fn_3_B3C94(2);
        }
        break;
    case 2:
        if (fn_3_750DC() != 0) {
            fn_3_B3C94(3);
        }
        break;
    case 3:
        {
            s32 t = g_GameLogic.homeTeamBattingInd_fieldingTeam;
            if (fn_80014D4C(inMemRoster[g_GameLogic.teamBatting][g_GameLogic.battingOrderAndPositionMapping[t][g_GameLogic.currentBatterPerTeam[t]][0]].stats.CharID) != 0) {
                fn_3_B3C94(4);
            }
        }
        break;
    case 4:
        if (fn_3_B3CD4() != 0) {
            fn_3_B3C94(7);
        }
        break;
    case 7:
        fn_3_B3B70();
        g_GameLogic.freeFieldingPracticeInd = 1;
        g_GameLogic.TeamStars[0] = 5;
        g_GameLogic.TeamStars[1] = 5;
        fn_3_5A6D4(7);
        fn_3_B3C78(3);
        break;
    }
}
#endif

// .text:0x0015A244 size:0x204
void fn_3_15A244(void) {
    PracticeMsgTask* o = lbl_803CC1B8[0];
    s32 i;

    fn_80034E20(o, lbl_3_data_B1BC);
    for (i = 0; i < 5; i++) {
        lbl_80371C30[o->baseIdx + i + 6].obj->_5C = lbl_3_data_B3DC[lbl_3_data_FAC4[i]] << 16;
    }
    o->state = 1;
    if (g_Practice.practiceType_1 == 1 || (u8)(g_Practice.practiceType_1 - 2) <= 2 ||
        g_Practice.practiceType_1 == 5) {
        lbl_80371C30[o->baseIdx].obj->_64 = lbl_3_data_B3E8[g_Practice.practiceType];
        lbl_80371C30[o->baseIdx].obj->_5C = 0x320000;
        lbl_80371C30[o->baseIdx].obj->_68 = 4;
        lbl_80371C30[o->baseIdx + 1 + g_Practice.practiceType].obj->_5C = 0x690000;
        lbl_80371C30[o->baseIdx + 11 + g_Practice.practiceType].obj->_5C = 0x690000;
        o->state = 5;
    }
    lbl_3_common_bss_32724._C0 = 1;
    ((PracticeTask*)lbl_803CC1B8[0])->callback = fn_3_159D50;
}

// .text:0x00157E28 size:0x284
void fn_3_157E28(void) {
    PracticeMsgTask* o = lbl_803CC1B8[0];
    LayoutObj* obj;

    if (lbl_3_common_bss_32724._96 != 0) {
        goto end;
    }
    if (o->state == 0) {
        o->text = fn_8000F988((LayoutGroup*)o, 4, 0, 5, 0, 0);
        lbl_80366B18.entries[o->text].hAlign = 0;
        lbl_80366B18.entries[o->text].vAlign = 1;
        fn_8000FD9C(o->text, 2, 0);
        o->state++;
    } else if (o->state == 1) {
        obj = lbl_80371C30[o->baseIdx].obj;
        if ((obj->_5C >> 16) >= 0xF) {
            obj->_68 = 0;
        }
        if (g_Practice.loadingGuidedPractice == 0) {
            if (g_Practice._1C7 != 0) {
                goto end;
            }
            lbl_80371C30[o->baseIdx + 1].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 2].obj->_68 = 4;
            lbl_80371C30[o->baseIdx + 2].obj->_5C = 0x90000;
            o->state++;
        }
    } else if (o->state == 2) {
        if ((lbl_80371C30[o->baseIdx + 1].obj->_5C >> 16) == 0) {
            goto end;
        }
    }
    if (g_Practice._1C7 != 0) {
        lbl_80371C30[o->baseIdx + 3].obj->flags &= ~2;
    } else {
        lbl_80371C30[o->baseIdx + 3].obj->flags |= 2;
    }
    if (g_Practice._188 == 1) {
        fn_8000FE08(o->text, 5,
            lbl_3_data_104B8[g_Practice.practiceLevel_2][g_Practice._1D7][g_Practice._1D8]);
    }
    g_Practice.currentMessageDoneTyping = lbl_80366B18.entries[o->text].finished;
    return;
end:
    fn_8000FEE8(o->text);
    fn_8000F8F4((LayoutGroup*)o);
    fn_800B0A14_removeQueue(fn_80034CEC(o));
}

// .text:0x0015B204 size:0x290
void fn_3_15B204(void) {
    s32 i;
    s32 found;

    for (i = 0; i < 9; i++) {
        fn_3_B4124(0, i, lbl_3_data_FAA8[1][i], -1);
        if (g_GameLogic.secondaryGameMode == 0x10) {
            fn_3_B4124(1, i, lbl_3_data_FAA8[2][i], -1);
        } else {
            fn_3_B4124(1, i, lbl_3_data_FAA8[0][i], -1);
        }
    }
    if (g_GameLogic.secondaryGameMode == 0xF) {
        if (g_Minigame._19E8[g_Practice.homeAway]._0 == 1) {
            fn_3_B4124(0, 0, 0, -1);
        } else {
            fn_3_B4124(0, 0, 1, -1);
        }
        fn_3_B4124(1, 0, g_Minigame._19E8[g_Practice.homeAway]._0, g_Minigame.battingHandedness[g_Practice.homeAway]);
        return;
    }
    fn_3_B4124(0, 0, g_Minigame._19E8[g_Practice.homeAway]._0, g_Minigame.battingHandedness[g_Practice.homeAway]);
    found = 0;
    for (i = 1; i < 9; i++) {
        if (g_Minigame._19E8[g_Practice.homeAway]._0 == inMemRoster[0][i].stats.CharID) {
            fn_3_B4124(0, i, 0x2E, -1);
            found = 1;
            break;
        }
    }
    if (found == 0) {
        for (i = 0; i < 9; i++) {
            if (inMemRoster[1][i].stats.CharID == g_Minigame._19E8[g_Practice.homeAway]._0) {
                if (i == 0 || i == 1 || i == 8) {
                    fn_3_B4124(1, i, 3, -1);
                } else if (i == 2 || i == 3 || i == 4) {
                    fn_3_B4124(1, i, 0x13, -1);
                } else {
                    fn_3_B4124(1, i, 0x11, -1);
                }
                break;
            }
        }
    }
}

// .text:0x0015A75C size:0x298
void fn_3_15A75C(void) {
    if (g_GameLogic.hudElementLoadingInd != 0 && lbl_3_common_bss_32724._A5 == 0 && g_Practice.instructionNumber < 0) {
        lbl_3_common_bss_32724._A5 = 1;
        lbl_3_common_bss_32724._A6 = 0;
        lbl_3_common_bss_32724._A7 = 0xFF;
        if (g_Practice.practiceLevel == 4) {
            fn_800B0A5C_insertQueue(fn_3_9976C, 2);
        } else if (g_Practice.practiceLevel == 5) {
            fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
        } else if (g_Practice.practiceType_2 == 4) {
            fn_800B0A5C_insertQueue(fn_3_9C28C, 2);
            fn_800B0A5C_insertQueue(fn_3_9A8A4, 2);
        } else if (g_Practice.practiceType_2 == 0) {
            if (g_Practice.practiceLevel == 1) {
                fn_800B0A5C_insertQueue(fn_3_99BDC, 2);
            }
        } else if (g_Practice.practiceType_2 == 1) {
            if (g_Practice.practiceLevel == 1) {
                fn_800B0A5C_insertQueue(fn_3_9976C, 2);
            }
        }
    }
    if (lbl_3_common_bss_32724._A5 != 0 && lbl_3_common_bss_32724._A6 < 0xFF) {
        if (lbl_3_common_bss_32724._A6 < 0xF0) {
            lbl_3_common_bss_32724._A6 += 0x10;
        } else {
            lbl_3_common_bss_32724._A6 = 0xFF;
        }
    }
    if (lbl_3_common_bss_32724._A7 != 0 && lbl_3_common_bss_32724._A7 < 0xFF) {
        if (lbl_3_common_bss_32724._A7 <= 0x10) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        } else {
            lbl_3_common_bss_32724._A7 -= 0x10;
        }
    } else if (lbl_3_common_bss_32724._A5 != 0) {
        if (g_GameLogic.gameStatus != 1 && g_GameLogic.gameStatus != 0 && g_GameLogic.gameStatus != 7) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
        if (lbl_3_common_bss_34C90._1D5 != 0) {
            lbl_3_common_bss_32724._A7 = 0xF0;
        }
        if (g_Practice._19F != 0 &&
            (lbl_3_common_bss_34C90._1D2 == 7 || lbl_3_common_bss_34C90._1D2 == 9 || lbl_3_common_bss_34C90._1D2 == 0xB)) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        }
        if (g_Practice._1C7 != 0 &&
            (lbl_3_common_bss_34C90._1D2 == 5 || lbl_3_common_bss_34C90._1D2 == 0xB || lbl_3_common_bss_34C90._1D2 == 7)) {
            lbl_3_common_bss_32724._A7 = 0;
            lbl_3_common_bss_32724._A5 = 0;
        }
    }
    if (g_GameLogic.gameStatus == 8) {
        lbl_3_common_bss_32724._A7 = 0;
        lbl_3_common_bss_32724._A5 = 0;
    }
}

// .text:0x001583AC size:0x304
void fn_3_1583AC(void) {
    PracticeTask* o = lbl_803CC1B8[0];
    s32 v;
    s32 c;
    s32 i;
    s32 any;

    if (lbl_3_common_bss_32724._96 == 0 && (g_Practice._1C7 == 0 || lbl_3_common_bss_34C90._1D2 != 0) &&
        (g_Practice._19F == 0 || (lbl_3_common_bss_34C90._1D2 != 7 && lbl_3_common_bss_34C90._1D2 != 0xB))) {
        if (o->timer == 0) {
            for (i = 0; i < 4; i++) {
                PracticeMsgEntry* e = &lbl_3_data_103B8[g_Practice.practiceType_2][g_Practice.practiceLevel][i];
                if (e->enabled != 0) {
                    o->text[i] = fn_8000F988((LayoutGroup*)o, i + 0x12, 0, 5, e->msg, 0);
                    lbl_80366B18.entries[o->text[i]].hAlign = 1;
                    lbl_80366B18.entries[o->text[i]].vAlign = 1;
                }
            }
            o->timer++;
        }
        {
            u8* row = lbl_3_data_FAF4 + g_Practice.practiceType_2 * 4;
            v = row[g_Practice.practiceLevel];
            fn_800363D8(o, 1, 3, 0x32, v);
            fn_800363D8(o, 1, 4, 0x32, v);
            c = g_Practice.guidedPracticeCounter;
            fn_800363D8(o, 1, 1, 0x32, c);
            fn_800363D8(o, 1, 2, 0x32, c);
            if (c != o->_1A) {
                LayoutSlot* t = &lbl_80371C30[1];
                LayoutObj* q = t[o->baseIdx].obj;
                if ((q->_5C >> 16) <= 9) {
                    q->_5C = 0xA0000;
                    t[o->baseIdx].obj->_68 = 1;
                }
                q = t[o->baseIdx].obj;
                if ((q->_5C >> 16) >= 0x13) {
                    q->_5C = 0x90000;
                    t[o->baseIdx].obj->_68 = 0;
                    o->_1A = c;
                }
            }
        }
    } else {
        any = 0;
        for (i = 0; i < 4; i++) {
            if (lbl_3_data_103B8[g_Practice.practiceType_2][g_Practice.practiceLevel][i].enabled > 0) {
                fn_8000FEE8(o->text[i]);
                any = 1;
            }
        }
        if (any) {
            fn_8000F8F4((LayoutGroup*)o);
        }
        lbl_3_common_bss_32724._C6 = 0;
        fn_800B0A14_removeQueue(fn_80034CEC(o));
    }
}
