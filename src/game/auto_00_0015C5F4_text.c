#include "game/auto_00_0015C5F4_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// .text:0x0015C5F4 size:0x44 mapped:0x8079B688
void fn_3_15C5F4(void) {
    SceneTask* task = lbl_803CC1B8;

    if (g_GameLogic._125 == 7) {
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
}

// .text:0x0015C638 size:0xAC mapped:0x8079B6CC
void fn_3_15C638(void) {
    ScoreBookTask* task = SB_TASK;

    fn_80034E20(task, lbl_3_data_27C54);
    if (lbl_80353A90._104 == 2) {
        SB_OBJ(task, 0)->_64 = 0xD3;
    } else if (lbl_80353A90._104 == 3) {
        SB_OBJ(task, 0)->_64 = 0xC0;
    }
    SB_TASK->func = fn_3_15C5F4;
}

// .text:0x0015C6E4 size:0xAF4 mapped:0x8079B778
// Shows a number in the digit sprites of object idx, in one of several layouts.
void fn_3_15C6E4(ScoreBookTask* task, s32 idx, s32 value, s32 format) {
    fn_800362F0(task, idx);
    if (format == 0x15) {
        SB_OBJ(task, idx)->_64 = 0x10;
        fn_800363D8(task, idx, 1, 0x1A, 0xE);
        fn_800363D8(task, idx, 2, 0x1A, 0xE);
    } else if (format == 0x16) {
        SB_OBJ(task, idx)->_64 = 0x15;
        fn_800363D8(task, idx, 3, 0x1A, 0xE);
        fn_800363D8(task, idx, 2, 0x1A, 0xE);
        fn_800363D8(task, idx, 1, 0x1A, 0xE);
        fn_800363D8(task, idx, 6, 0x1A, 0xE);
        fn_800363D8(task, idx, 5, 0x1A, 0xE);
        fn_800363D8(task, idx, 4, 0x1A, 0xE);
    } else if (format == 10) {
        if (value >= 1000) {
            SB_OBJ(task, idx)->_64 = 0x18;
            fn_800363D8(task, idx, 1, 0x1A, 1);
            fn_800363D8(task, idx, 3, 0x1A, 0);
            fn_800363D8(task, idx, 4, 0x1A, 0);
            fn_800363D8(task, idx, 5, 0x1A, 0);
            fn_800363D8(task, idx, 6, 0x1A, 1);
            fn_800363D8(task, idx, 8, 0x1A, 0);
            fn_800363D8(task, idx, 9, 0x1A, 0);
            fn_800363D8(task, idx, 10, 0x1A, 0);
        } else {
            s32 a, b, c;

            SB_OBJ(task, idx)->_64 = 0x19;
            a = value / 100;
            fn_800363D8(task, idx, 2, 0x1A, a);
            b = (value / 10) % 10;
            fn_800363D8(task, idx, 3, 0x1A, b);
            c = value % 10;
            fn_800363D8(task, idx, 4, 0x1A, c);
            fn_800363D8(task, idx, 6, 0x1A, a);
            fn_800363D8(task, idx, 7, 0x1A, b);
            fn_800363D8(task, idx, 8, 0x1A, c);
        }
    } else if (format == 11) {
        if (value >= 1000) {
            s32 a, b, c, d;

            if (value >= 10000) {
                value = 9999;
            }
            SB_OBJ(task, idx)->_64 = 0x17;
            a = value / 1000;
            fn_800363D8(task, idx, 1, 0x1A, a);
            b = (value / 100) % 10;
            fn_800363D8(task, idx, 2, 0x1A, b);
            c = (value / 10) % 10;
            fn_800363D8(task, idx, 4, 0x1A, c);
            d = value % 10;
            fn_800363D8(task, idx, 5, 0x1A, d);
            fn_800363D8(task, idx, 6, 0x1A, a);
            fn_800363D8(task, idx, 7, 0x1A, b);
            fn_800363D8(task, idx, 9, 0x1A, c);
            fn_800363D8(task, idx, 10, 0x1A, d);
        } else {
            s32 a, b, c;

            SB_OBJ(task, idx)->_64 = 0x16;
            a = (value / 100) % 10;
            fn_800363D8(task, idx, 1, 0x1A, a);
            b = (value / 10) % 10;
            fn_800363D8(task, idx, 3, 0x1A, b);
            c = value % 10;
            fn_800363D8(task, idx, 4, 0x1A, c);
            fn_800363D8(task, idx, 5, 0x1A, a);
            fn_800363D8(task, idx, 7, 0x1A, b);
            fn_800363D8(task, idx, 8, 0x1A, c);
        }
    } else {
        if (format == 12) {
            s32 r;
            s32 q;

            // thirds (innings pitched): whole part, then a 1/3 or 2/3 glyph
            r = value % 3;
            q = value / 3;
            if (value == 0) {
                SB_OBJ(task, idx)->_64 = 0x11;
                fn_800363D8(task, idx, 1, 0x1A, 0xB);
                fn_800363D8(task, idx, 2, 0x1A, 0xB);
                return;
            }
            if (r != 0) {
                if (q >= 10) {
                    s32 a, b;

                    SB_OBJ(task, idx)->_64 = 0x14;
                    a = q / 10;
                    fn_800363D8(task, idx, 1, 0x1A, a);
                    b = q % 10;
                    fn_800363D8(task, idx, 2, 0x1A, b);
                    fn_800363D8(task, idx, 3, 0x1A, r + 0xB);
                    fn_800363D8(task, idx, 4, 0x1A, a);
                    fn_800363D8(task, idx, 5, 0x1A, b);
                    fn_800363D8(task, idx, 6, 0x1A, r + 0xB);
                } else if (q != 0) {
                    SB_OBJ(task, idx)->_64 = 0x12;
                    fn_800363D8(task, idx, 1, 0x1A, q);
                    fn_800363D8(task, idx, 2, 0x1A, r + 0xB);
                    fn_800363D8(task, idx, 3, 0x1A, q);
                    fn_800363D8(task, idx, 4, 0x1A, r + 0xB);
                } else {
                    SB_OBJ(task, idx)->_64 = 0x11;
                    fn_800363D8(task, idx, 1, 0x1A, r + 0xB);
                    fn_800363D8(task, idx, 2, 0x1A, r + 0xB);
                }
                return;
            }
            value = q;
        }
        if (value < 10) {
            SB_OBJ(task, idx)->_64 = 0x10;
            fn_800363D8(task, idx, 1, 0x1A, value);
            fn_800363D8(task, idx, 2, 0x1A, value);
        } else if (format == 2 || value < 100) {
            s32 a, b;

            if (value >= 100) {
                value = 99;
            }
            SB_OBJ(task, idx)->_64 = 0x13;
            a = value % 10;
            fn_800363D8(task, idx, 2, 0x1A, a);
            b = value / 10;
            fn_800363D8(task, idx, 1, 0x1A, b);
            fn_800363D8(task, idx, 4, 0x1A, a);
            fn_800363D8(task, idx, 3, 0x1A, b);
        } else {
            s32 a, b, c;

            if (value >= 1000) {
                value = 999;
            }
            SB_OBJ(task, idx)->_64 = 0x15;
            a = value % 10;
            fn_800363D8(task, idx, 3, 0x1A, a);
            b = (value / 10) % 10;
            fn_800363D8(task, idx, 2, 0x1A, b);
            c = value / 100;
            fn_800363D8(task, idx, 1, 0x1A, c);
            fn_800363D8(task, idx, 6, 0x1A, a);
            fn_800363D8(task, idx, 5, 0x1A, b);
            fn_800363D8(task, idx, 4, 0x1A, c);
        }
    }
}

// .text:0x0015D1D8 size:0x96C mapped:0x8079C26C
// Fills the five visible scorebook rows (and the team totals) for the current page.
// NONMATCHING 98.7%: saved-register coloring (row/i and team/order swapped; the original seems to
// reuse one pointer for order/bat and roster/b) plus one extra `li` for the first unrolled total.
#if NONMATCHING
void fn_3_15D1D8(ScoreBookTask* task) {
    s32 rows[5];
    BatterRecord* bat;
    ScoreOrderEntry* order;
    s32 team;
    s32* out;
    s32 i;
    PitcherRecord* pit;
    s32* row;
    CharacterStats* roster;
    s32 j;
    PitcherRecord* p;
    BatterRecord* b;
    s32 sum;
    s32 sum2;
    s32 avg;

    row = rows;
    out = row;
    team = task->team ^ g_GameLogic._000;
    order = lbl_80354720[team];
    roster = inMemRoster[team];
    for (i = 0; i < 5; i++, out++) {
        for (j = 0; j < 9; j++) {
            if (i + task->scroll == order[j].row) {
                *out = j;
                fn_800363D8(task, i + 2, 1, 0xD, roster[j].stats.CharID);
                break;
            }
        }
    }

    if (task->page == 0) {
        bat = lbl_803537E4[team];
        for (i = 0; i < 5; i++, row++) {
            b = &bat[*row];
            fn_3_15C6E4(task, i + 7, b->hits, 3);
            fn_3_15C6E4(task, i + 0xD, b->_10, 3);
            fn_3_15C6E4(task, i + 0x13, b->_09, 3);
            fn_3_15C6E4(task, i + 0x19, b->_12, 3);
            fn_3_15C6E4(task, i + 0x1F, b->_24, 3);
            if (b->atBats == 0) {
                fn_3_15C6E4(task, i + 0x25, 0, 0x16);
            } else {
                avg = b->hits * 10000 / b->atBats;
                if (avg % 10 >= 5) {
                    avg += 10;
                }
                fn_3_15C6E4(task, i + 0x25, avg / 10, 10);
            }
        }

        for (j = 0, sum = 0; j < 9; j++) {
            sum += bat[j].hits;
        }
        fn_3_15C6E4(task, 0xC, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += bat[j]._10;
        }
        fn_3_15C6E4(task, 0x12, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += bat[j]._09;
        }
        fn_3_15C6E4(task, 0x18, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += bat[j]._12;
        }
        fn_3_15C6E4(task, 0x1E, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += bat[j]._24;
        }
        fn_3_15C6E4(task, 0x24, sum, 3);
        for (j = 0, sum = 0, sum2 = 0; j < 9; j++) {
            sum += bat[j].hits;
            sum2 += bat[j].atBats;
        }
        avg = sum * 10000 / sum2;
        if (avg % 10 >= 5) {
            avg += 10;
        }
        fn_3_15C6E4(task, 0x2A, avg / 10, 10);
    } else {
        bat = lbl_803537E4[team];
        pit = lbl_803535C8[team];
        for (i = 0; i < 5; i++, row++) {
            b = &bat[*row];
            p = &pit[*row];
            fn_3_15C6E4(task, i + 7, b->_23, 3);
            if (p->_00 == 0) {
                fn_3_15C6E4(task, i + 0xD, 0, 0x15);
                fn_3_15C6E4(task, i + 0x13, 0, 0x15);
                fn_3_15C6E4(task, i + 0x19, 0, 0x15);
                fn_3_15C6E4(task, i + 0x1F, 0, 0x15);
            } else {
                fn_3_15C6E4(task, i + 0xD, p->_0A, 3);
                fn_3_15C6E4(task, i + 0x13, p->_1C, 3);
                fn_3_15C6E4(task, i + 0x19, p->_02, 3);
                fn_3_15C6E4(task, i + 0x1F, p->_1D, 3);
            }
            // ERA x100: earned runs * 9 innings * 3 outs * 1000 / outs, rounded
            if (p->outs != 0) {
                avg = p->earnedRuns * 27000 / p->outs;
                if (avg % 10 >= 5) {
                    avg += 10;
                }
                avg /= 10;
            } else if (p->_00 != 0) {
                avg = 9999;
            } else {
                avg = 0;
            }
            if (p->_00 == 0) {
                fn_3_15C6E4(task, i + 0x25, 0, 0x16);
            } else {
                fn_3_15C6E4(task, i + 0x25, avg, 11);
            }
        }

        for (j = 0, sum = 0; j < 9; j++) {
            sum += bat[j]._23;
        }
        fn_3_15C6E4(task, 0xC, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += pit[j]._0A;
        }
        fn_3_15C6E4(task, 0x12, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += pit[j]._1C;
        }
        fn_3_15C6E4(task, 0x18, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += pit[j]._02;
        }
        fn_3_15C6E4(task, 0x1E, sum, 3);
        for (j = 0, sum = 0; j < 9; j++) {
            sum += pit[j]._1D;
        }
        fn_3_15C6E4(task, 0x24, sum, 3);
        for (j = 0, sum = 0, sum2 = 0; j < 9; j++) {
            sum += pit[j].earnedRuns;
            sum2 += pit[j].outs;
        }
        if (sum2 == 0) {
            avg = 9999;
        } else {
            avg = sum * 27000 / sum2;
            if (avg % 10 >= 5) {
                avg += 10;
            }
            avg /= 10;
        }
        fn_3_15C6E4(task, 0x2A, avg, 11);
    }
}
#endif

// .text:0x0015DB44 size:0x12E8 mapped:0x8079CBD8
// Scorebook task: page / team / scroll transitions.
// NONMATCHING 99.9%: `add` operand order in the two closing-animation index loops (base + i vs i + base).
#if NONMATCHING
void fn_3_15DB44(void) {
    ScoreBookTask* task = SB_TASK;
    LayoutObj* o;
    s32 i;
    s32 j;
    s32 done;
    s32 team;
    s32 frame;
    u32 f;

    if (task->timer < 0xFFFE) {
        task->timer++;
    } else {
        task->timer = 0xFFFF;
    }
    done = 0;
    lbl_3_common_bss_32724._D2 = 0;
    if (g_GameLogic._125 == 10) {
        goto remove;
    }

    if (task->state == 0) {
        lbl_3_common_bss_32724._D2 = 1;
        task->state++;
    } else if (task->state == 1) {
        // opening
        lbl_3_common_bss_32724._D2 = 1;
        if (task->page == 0) {
            o = SB_OBJ(task, 0x31);
            if ((o->_5C >> 16) >= 10) {
                o->_68 = 0;
            }
            o = SB_OBJ(task, 0x32);
            if ((o->_5C >> 16) >= 5) {
                o->_68 = 0;
            }
        } else {
            o = SB_OBJ(task, 0x31);
            if ((o->_5C >> 16) >= 5) {
                o->_68 = 0;
            }
            o = SB_OBJ(task, 0x32);
            if ((o->_5C >> 16) >= 10) {
                o->_68 = 0;
            }
        }
        o = SB_OBJ(task, 0x36);
        if ((o->_5C >> 16) >= 10) {
            o->_68 = 0;
        }
        if (task->timer >= 30) {
            SB_OBJ(task, 0)->_68 = 0;
            task->state++;
        }
    } else if (task->state == 2) {
        // idle: wait for an input change
        if (task->scroll != g_GameLogic.scoreBook_scrollIndex) {
            lbl_3_common_bss_32724._D2 = 1;
            task->timer = 0;
            task->state = 7;
        } else if (task->team != g_GameLogic.scoreBook_teamDisplayed) {
            lbl_3_common_bss_32724._D2 = 1;
            task->timer = 0;
            task->state = 3;
        } else if (task->page != g_GameLogic.scoreBook_batter_pitcherStatsDisplayed) {
            lbl_3_common_bss_32724._D2 = 1;
            task->timer = 0;
            task->state = 5;
        } else if (g_GameLogic._125 == 8) {
            lbl_3_common_bss_32724._D2 = 1;
            task->timer = 0;
            task->state = 9;
        }
    } else if (task->state == 3) {
        // team change: wipe out
        lbl_3_common_bss_32724._D2 = 1;
        done = 0;
        if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right == 0) {
            if (task->timer == 1) {
                SB_OBJ(task, 0x36)->_5C = 0x15 << 16;
                SB_OBJ(task, 0x36)->_68 = 1;
            }
            o = SB_OBJ(task, 0x36);
            if ((o->_5C >> 16) >= 0x1F) {
                done = 1;
                o->_68 = 0;
            }
        } else {
            if (task->timer == 1) {
                SB_OBJ(task, 0x36)->_5C = 10 << 16;
                SB_OBJ(task, 0x36)->_68 = 1;
            }
            o = SB_OBJ(task, 0x36);
            if ((o->_5C >> 16) >= 0x14) {
                done = 1;
                o->_68 = 0;
            }
        }
        for (i = 2; i <= 0x2A; i++) {
            SB_OBJ(task, i)->_68 = 4;
        }
        if (done) {
            task->state = 4;
            task->timer = 0;
        }
    } else if (task->state == 4) {
        // team change: redraw and wipe in
        lbl_3_common_bss_32724._D2 = 1;
        if (task->timer == 1) {
            task->team = g_GameLogic.scoreBook_teamDisplayed;
            if (task->team == 0) {
                SB_OBJ(task, 0x37)->flags |= 2;
                SB_OBJ(task, 0x38)->flags &= ~2;
            } else {
                SB_OBJ(task, 0x37)->flags &= ~2;
                SB_OBJ(task, 0x38)->flags |= 2;
            }
            team = g_GameLogic._000 ^ task->team;
            if (g_GameLogic._13E[team] != 0) {
                fn_800363D8(task, 0x39, 1, 3, g_GameLogic.teams[team] + 4);
            } else {
                fn_800363D8(task, 0x39, 1, 3, g_GameLogic.teams[team]);
            }
            fn_3_15D1D8(task);
        }
        if (g_GameLogic.scoreBook_logoFadeDirectionLeft_Right == 1) {
            if (task->timer == 1) {
                SB_OBJ(task, 0x36)->_5C = 0x1F << 16;
                SB_OBJ(task, 0x36)->_68 = 4;
            }
            if ((SB_OBJ(task, 0x36)->_5C >> 16) <= 0x15) {
                SB_OBJ(task, 0x36)->_5C = 10 << 16;
                done = 1;
                SB_OBJ(task, 0x36)->_68 = 0;
            }
        } else {
            if (task->timer == 1) {
                SB_OBJ(task, 0x36)->_5C = 0x14 << 16;
                SB_OBJ(task, 0x36)->_68 = 4;
            }
            if ((SB_OBJ(task, 0x36)->_5C >> 16) <= 10) {
                SB_OBJ(task, 0x36)->_5C = 10 << 16;
                done = 1;
                SB_OBJ(task, 0x36)->_68 = 0;
            }
        }
        for (i = 2; i <= 0x2A; i++) {
            SB_OBJ(task, i)->_68 = 1;
        }
        if (done) {
            task->state = 2;
            task->timer = 0;
        }
    } else if (task->state == 5) {
        // page change: hide stats
        lbl_3_common_bss_32724._D2 = 1;
        if (task->timer == 1) {
            for (i = 7; i <= 0x30; i++) {
                SB_OBJ(task, i)->_68 = 4;
            }
        }
        if (task->page == 0) {
            o = SB_OBJ(task, 0x31);
            if ((o->_5C >> 16) <= 5) {
                o->_68 = 0;
            } else {
                o->_68 = 4;
            }
            o = SB_OBJ(task, 0x32);
            if ((o->_5C >> 16) >= 10) {
                o->_68 = 0;
            } else {
                o->_68 = 1;
            }
        } else {
            o = SB_OBJ(task, 0x32);
            if ((o->_5C >> 16) <= 5) {
                o->_68 = 0;
            } else {
                o->_68 = 4;
            }
            o = SB_OBJ(task, 0x31);
            if ((o->_5C >> 16) >= 10) {
                o->_68 = 0;
            } else {
                o->_68 = 1;
            }
        }
        if (task->timer >= 8) {
            task->state = 6;
            task->timer = 0;
        }
    } else if (task->state == 6) {
        // page change: redraw
        lbl_3_common_bss_32724._D2 = 1;
        if (task->timer == 1) {
            task->page = g_GameLogic.scoreBook_batter_pitcherStatsDisplayed;
            for (i = 7; i <= 0x30; i++) {
                SB_OBJ(task, i)->_68 = 1;
            }
            for (j = 0; j < 6; j++) {
                fn_800363D8(task, j + 0x2B, 1, 0xF, lbl_3_data_27C40[task->page][j]);
            }
            if (task->page == 0) {
                SB_OBJ(task, 0x35)->_5C = 5 << 16;
            } else {
                SB_OBJ(task, 0x35)->_5C = 0x33 << 16;
            }
            fn_3_15D1D8(task);
        }
        if (task->timer >= 8) {
            task->state = 2;
            task->timer = 0;
        }
    } else if (task->state == 7) {
        // scroll: hide the rows (not the totals column)
        lbl_3_common_bss_32724._D2 = 1;
        if (task->timer == 1) {
            for (i = 2; i <= 0x2A; i++) {
                if (i != 0xC && i != 0x12 && i != 0x18 && i != 0x1E && i != 0x24 && i != 0x2A) {
                    SB_OBJ(task, i)->_68 = 4;
                }
            }
        }
        if (task->timer >= 8) {
            task->state = 8;
            task->timer = 0;
        }
    } else if (task->state == 8) {
        // scroll: redraw
        lbl_3_common_bss_32724._D2 = 1;
        if (task->timer == 1) {
            task->scroll = g_GameLogic.scoreBook_scrollIndex;
            for (i = 2; i <= 0x2A; i++) {
                SB_OBJ(task, i)->_68 = 1;
            }
            fn_3_15D1D8(task);
        }
        if (task->timer >= 8) {
            task->state = 2;
            task->timer = 0;
        }
    } else {
        // closing
        lbl_3_common_bss_32724._D2 = 1;
        SB_OBJ(task, 0)->_68 = 4;
        frame = SB_OBJ(task, 0)->_5C >> 16;
        if (frame == 10) {
            SB_OBJ(task, 0x36)->_68 = 4;
            SB_OBJ(task, 0x33)->_68 = 4;
            if (task->page == 0) {
                SB_OBJ(task, 0x35)->_5C = 5 << 16;
                SB_OBJ(task, 0x35)->_68 = 4;
            } else {
                SB_OBJ(task, 0x35)->_5C = 0x33 << 16;
                SB_OBJ(task, 0x35)->_68 = 1;
            }
        }
        if (frame <= lbl_3_data_27C4C[0] + 5) {
            if (task->page == 0) {
                SB_OBJ(task, 0x31)->_68 = 1;
                SB_OBJ(task, 0x32)->_68 = 4;
            } else {
                SB_OBJ(task, 0x31)->_68 = 4;
                SB_OBJ(task, 0x32)->_68 = 1;
            }
        }
        for (i = 0; i < 5; i++) {
            if (frame <= lbl_3_data_27C4C[i] + 5) {
                SB_OBJ(task, i + 2)->_68 = 4;
            }
        }
        for (i = 0; i < 6; i++) {
            if (frame <= lbl_3_data_27C4C[i] + 5) {
                lbl_80371C30[(i + 0x2B) + task->baseIdx].obj->_68 = 4;
            }
        }
        for (i = 0; i < 6; i++) {
            if (frame <= lbl_3_data_27C4C[i] + 5) {
                for (j = 0; j < 6; j++) {
                    lbl_80371C30[(i * 6 + j + 7) + task->baseIdx].obj->_68 = 4;
                }
            }
        }
        if ((SB_OBJ(task, 0)->_5C >> 16) == 0) {
            goto remove;
        }
    }

    // keep the looping animations within their ranges
    if (task->state >= 2) {
        if (task->page == 0) {
            o = SB_OBJ(task, 0x35);
            if ((o->_5C >> 16) >= 0x2D) {
                o->_5C = 5 << 16;
            }
        } else {
            o = SB_OBJ(task, 0x35);
            if ((o->_5C >> 16) >= 0x5D) {
                o->_5C = 0x33 << 16;
            }
        }
    }
    if (task->scroll == 0) {
        o = SB_OBJ(task, 0x34);
        f = o->_5C >> 16;
        if (f >= 0x12E || f < 0xCA) {
            o->_5C = 0xCA << 16;
        }
    } else if (task->scroll == 4) {
        o = SB_OBJ(task, 0x34);
        f = o->_5C >> 16;
        if (f >= 0xC9 || f < 0x65) {
            o->_5C = 0x65 << 16;
        }
    } else {
        o = SB_OBJ(task, 0x34);
        if ((o->_5C >> 16) >= 0x64) {
            o->_5C = 0;
        }
    }
    return;

remove:
    fn_800B0A14_removeQueue(fn_80034CEC(task));
}
#endif

// .text:0x0015EE2C size:0x25C mapped:0x8079DEC0
void fn_3_15EE2C(void) {
    return;
}

// .text:0x0015F088 size:0x198 mapped:0x8079E11C
void fn_3_15F088(void) {
    return;
}

// .text:0x0015F220 size:0x160 mapped:0x8079E2B4
void fn_3_15F220(void) {
    return;
}

// .text:0x0015F380 size:0x44 mapped:0x8079E414
void fn_3_15F380(void) {
    return;
}

// .text:0x0015F3C4 size:0x4C mapped:0x8079E458
void fn_3_15F3C4(void) {
    return;
}

// .text:0x0015F410 size:0x164 mapped:0x8079E4A4
void fn_3_15F410(void) {
    return;
}
