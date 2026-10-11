#include "game/auto_00_00097144_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/stl.h"

extern s16 lbl_3_data_BE50[][4];  // TODO type: 8-byte entries, first field read here
extern u8 lbl_3_data_D648[];      // sprite descriptors for fn_80034E20
extern u8 lbl_3_data_D7A8[];
extern u8 lbl_3_data_D9E4[];
extern u8 lbl_3_data_DA50[];
extern u8 lbl_3_common_bss_37400[];
extern u16 lbl_3_data_DA44[2][3]; // frame per option, [simple layout][option]

extern void fn_3_96CA4(void);
extern void fn_3_95970(void);
extern void fn_3_91A60(void);

// .text:0x00097144 size:0x15C mapped:0x806D61D8
void fn_3_97144(void) {
    BOOL started = FALSE;

    if (g_GameLogic.gameStatus == 3 || (u8)(g_GameLogic.gameStatus - 0x13) <= 4 || g_GameLogic.gameStatus == 0x18) {
        g_UnkSound_32718._02 = 0;
        g_UnkSound_32718._03 = 0;
        g_UnkSound_32718._04 = 0;
        g_UnkSound_32718._05 = 0;
        g_UnkSound_32718._06 = 0;
        return;
    }
    if (g_UnkSound_32718._07 == 0) {
        if (g_UnkSound_32718._02 != 0) {
            if (g_Stats.replayInd == 0) {
                started = TRUE;
                g_UnkSound_32718._07 = g_UnkSound_32718._02;
                g_UnkSound_32718._02 = g_UnkSound_32718._03;
                g_UnkSound_32718._03 = g_UnkSound_32718._04;
                g_UnkSound_32718._04 = g_UnkSound_32718._05;
                g_UnkSound_32718._05 = g_UnkSound_32718._06;
                g_UnkSound_32718._06 = 0;
                g_UnkSound_32718._00 = 0;
            }
            sndFXKeyOff(lbl_3_common_bss_34C58._1C);
        }
    } else {
        g_UnkSound_32718._00++;
        if (g_UnkSound_32718._02 != 0 && g_UnkSound_32718._00 < 0x3C) {
            g_UnkSound_32718._00 = 0x3C;
        }
    }
    if (lbl_3_data_BE50[g_UnkSound_32718._07][0] >= 0 && started) {
        fn_800B0A5C_insertQueue(fn_3_96CA4, 2);
    }
}

// .text:0x000972A0 size:0x28 mapped:0x806D6334
void fn_3_972A0(void* owner, s32 idx, s32 track, u32 frame) {
    fn_8003649C(owner, idx, track, 0x28, frame);
}

// .text:0x000972C8 size:0x124 mapped:0x806D635C
void fn_3_972C8(void) {
    lbl_3_common_bss_32724.hudOff = 1;
    if (g_d_GameSettings.GameModeSelected == 4) {
        fn_80069A98();
        fn_80035CA4(0x16);
    }
    if (g_d_GameSettings.GameModeSelected == 0 || g_d_GameSettings.GameModeSelected == 5 || g_d_GameSettings.GameModeSelected == 4) {
        fn_80035CA4(0x10);
        fn_80035CA4(0xF);
    }
    fn_80035CA4(2);
    fn_80035CA4(5);
    fn_80035CA4(4);
    if (g_d_GameSettings.minigamesEnabled != 0) {
        fn_80035CA4(0x14);
        if (g_d_GameSettings.GameModeSelected == 6) {
            fn_80035CA4(0xE);
        }
        fn_80035CA4(3);
        fn_80035CA4(9);
        fn_80035CA4(0xD);
        fn_80035CA4(0x11);
    } else if (g_d_GameSettings.GameModeSelected == 2) {
        fn_80035CA4(0xB);
        fn_80035CA4(9);
    }
    if (lbl_3_common_bss_32724._D1 != 0) {
        fn_80035CA4(0xC);
    }
}

// .text:0x000973EC size:0x414 mapped:0x806D6480
void fn_3_973EC(void) {
    return;
}

// .text:0x00097800 size:0xDC mapped:0x806D6894
void fn_3_97800(void) {
    lbl_3_common_bss_32724.hudOff = 0;
    lbl_3_common_bss_32724._A5 = 0;
    lbl_3_common_bss_32724._97 = 0;
    lbl_3_common_bss_32724._A8 = 0;
    lbl_3_common_bss_32724._98 = 0;
    lbl_3_common_bss_32724._99 = 0;
    lbl_3_common_bss_32724._D1 = 0;
    lbl_3_common_bss_32724._AD = 0;
    lbl_3_common_bss_32724._AE = 0;
    lbl_3_common_bss_32724._B0 = 0;
    lbl_3_common_bss_32724._B1 = 0;
    lbl_3_common_bss_32724._B2 = 0;
    lbl_3_common_bss_32724._C7 = 0;
    lbl_3_common_bss_32724._D6 = 0;
    lbl_3_common_bss_32724._B6 = 0;
    lbl_3_common_bss_32724._D9 = 0;
    lbl_3_common_bss_32724._DA = 0;
    lbl_3_common_bss_32724._BC = 0;
    lbl_3_common_bss_32724._C0 = 0;
    lbl_3_common_bss_32724._C1 = 0;
    lbl_3_common_bss_32724._C2 = 0;
    lbl_3_common_bss_32724._C6 = 0;
    lbl_3_common_bss_32724.pauseTitleShown = 0;
    lbl_3_common_bss_32724.pauseMenuShown = 0;
    lbl_3_common_bss_32724._C3 = 0;
    lbl_3_common_bss_32724._C4 = 0;
    lbl_3_common_bss_32724._BE = 0;
    lbl_3_common_bss_32724._BF = 0;
    lbl_3_common_bss_32724._B3 = 0;
    lbl_3_common_bss_32724._B4 = 0;
    lbl_3_common_bss_32724._B5 = 0;
    lbl_3_common_bss_32724._C5 = 0;
    if (g_d_GameSettings.minigamesEnabled == 0) {
        fn_800B0A5C_insertQueue(fn_3_95970, 2);
    }
    fn_800B0A5C_insertQueue(fn_3_91A60, 2);
}

// .text:0x000978DC size:0x410 mapped:0x806D6970
void fn_3_978DC(void) {
    return;
}

// .text:0x00097CEC size:0x33C mapped:0x806D6D80
void fn_3_97CEC(void) {
    return;
}

// .text:0x00098028 size:0x390 mapped:0x806D70BC
void fn_3_98028(void) {
    HudTask* task = HUD_TASK;
    s32 simple = 0;
    BOOL done;

    if (lbl_3_common_bss_32724.hudOff == 0 && lbl_3_common_bss_34C90.state != 6) {
        if (lbl_800E8754._04 == 0 && g_d_GameSettings.GameModeSelected != 2) {
            simple = 1;
        }
        if (task->state == 0) {
            HUD_OBJ(task, 1)->_5C = lbl_3_data_DA44[simple][task->_1E] << 16;
            if (task->_20 == 0) {
                HUD_OBJ(task, 0)->_5C = 0;
                HUD_OBJ(task, 0)->_68 = 1;
            } else {
                HUD_OBJ(task, 0)->_5C = 0xF0000;
                HUD_OBJ(task, 0)->_68 = 4;
            }
            lbl_3_common_bss_32724._C3 = 1;
            task->state++;
            return;
        } else if (task->state == 1) {
            if (task->_20 == 0) {
                if ((HUD_OBJ(task, 0)->_5C >> 16) >= 8) {
                    HUD_OBJ(task, 0)->_68 = 0;
                    task->state++;
                }
            } else {
                if ((HUD_OBJ(task, 0)->_5C >> 16) <= 8) {
                    HUD_OBJ(task, 0)->_68 = 0;
                    task->state++;
                }
            }
            lbl_3_common_bss_32724._C3 = 1;
            return;
        } else if (task->state == 2) {
            lbl_3_common_bss_32724._C3 = 0;
            if ((g_d_GameSettings.GameModeSelected == 2 && lbl_3_common_bss_34C90._1D3 == 6) ||
                (g_d_GameSettings.GameModeSelected != 2 && lbl_3_common_bss_34C90.state == 5)) {
                HUD_OBJ(task, 0)->_68 = 1;
                task->_20 = 0;
                task->state = 4;
                return;
            }
            if (lbl_3_common_bss_34C90._221 != task->_1E) {
                task->_1E = lbl_3_common_bss_34C90._221;
                HUD_OBJ(task, 1)->_5C = lbl_3_data_DA44[simple][task->_1E] << 16;
            }
            return;
        } else {
            done = FALSE;
            lbl_3_common_bss_32724._C3 = 1;
            if (task->_20 == 0) {
                if ((HUD_OBJ(task, 0)->_5C >> 16) >= 0xF) {
                    done = TRUE;
                }
            } else if ((HUD_OBJ(task, 0)->_5C >> 16) == 0) {
                done = TRUE;
            }
            if (!done) {
                return;
            }
            task->_1E = lbl_3_common_bss_34C90._221;
            HUD_OBJ(task, 0)->_68 = 0;
            if (task->state == 3) {
                task->state = 0;
                return;
            }
        }
    }
    fn_800B0A14_removeQueue(fn_80034CEC(task));
    lbl_3_common_bss_32724._C3 = 0;
}

// .text:0x000983B8 size:0x7C mapped:0x806D744C
void fn_3_983B8(void) {
    HudTask* task = HUD_TASK;

    fn_80034E20(task, lbl_3_data_D9E4);
    lbl_3_common_bss_32724._C3 = 0;
    task->state = 0;
    task->_1E = lbl_3_common_bss_34C90._221;
    task->_20 = 0;
    HUD_TASK->func = fn_3_98028;
}

// .text:0x00098434 size:0x518 mapped:0x806D74C8
void fn_3_98434(void) {
    return;
}

// .text:0x0009894C size:0x2D4 mapped:0x806D79E0
void fn_3_9894C(void) {
    return;
}

// .text:0x00098C20 size:0x1C0 mapped:0x806D7CB4
void fn_3_98C20(void) {
    HudTask* task = HUD_TASK;

    if (lbl_3_common_bss_32724.hudOff == 0) {
        if (task->state == 0) {
            task->state = 1;
            return;
        } else if (task->state == 1) {
            if (g_d_GameSettings.GameModeSelected == 2) {
                if (g_Practice._19F == 0) {
                    goto remove;
                }
                if (lbl_3_common_bss_34C90.state == 4) {
                    task->state = 2;
                }
                return;
            } else if (g_d_GameSettings.minigamesEnabled != 0) {
                if (g_GameLogic.gameStatus == 0xB && lbl_3_common_bss_34C90.state == 4) {
                    task->state = 2;
                }
                if (g_d_GameSettings.GameModeSelected != 7) {
                    return;
                }
                if (lbl_3_common_bss_34C90.state == 4) {
                    task->state = 2;
                }
                if (lbl_3_common_bss_34C90.state != 7 && lbl_3_common_bss_34C90.state != 0xD) {
                    return;
                }
                goto remove;
            } else {
                if ((((lbl_3_common_bss_34C90.menu != 2 && lbl_3_common_bss_34C90.menu != 9)) || lbl_3_common_bss_34C90.state != 4) &&
                    lbl_3_common_bss_34C90.itemsState != 2) {
                    return;
                }
                goto remove;
            }
        } else if (task->state == 2) {
            HUD_OBJ(task, 0)->_68 = 4;
            if ((HUD_OBJ(task, 0)->_5C >> 16) == 0) {
                goto remove;
            }
        }
        return;
    }
remove:
    fn_800B0A14_removeQueue(fn_80034CEC(task));
    lbl_3_common_bss_32724.pauseTitleShown = 0;
}

// .text:0x00098DE0 size:0xC8 mapped:0x806D7E74
void fn_3_98DE0(void) {
    HudTask* task = HUD_TASK;

    fn_80034E20(task, lbl_3_data_D7A8);
    if (g_d_GameSettings.minigamesEnabled != 0) {
        HUD_OBJ(task, 0)->layer = 5;
    } else if (g_d_GameSettings.GameModeSelected == 2) {
        HUD_OBJ(task, 0)->layer = 6;
    }
    lbl_3_common_bss_32724.pauseTitleShown = 1;
    task->state = 0;
    HUD_TASK->func = fn_3_98C20;
}

// .text:0x00098EA8 size:0x1BC mapped:0x806D7F3C
void fn_3_98EA8(void) {
    if (lbl_3_common_bss_34C90.state == 2) {
        fn_800B0A5C_insertQueue(fn_80053FE8, 2);
        memset(&lbl_8034E978, 0, sizeof(lbl_8034E978));
        switch (lbl_803297E0._CFA2[lbl_3_common_bss_34C90.team]) {
        case 0:
            lbl_8034E978.menu = g_d_GameSettings.GameModeSelected == 5 ? 0x1C : 8;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[g_d_GameSettings.GameModeSelected == 5 ? 0x1C : 8].track;
            break;
        case 1:
            lbl_8034E978.menu = 0xA;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0xA].track;
            break;
        case 2:
            lbl_8034E978.menu = 0x1E;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x1E].track;
            break;
        case 3:
            lbl_8034E978.menu = 0x1F;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x1F].track;
            break;
        }
        fn_800486E0(0, g_GameLogic.teams[lbl_3_common_bss_34C90.team], lbl_3_common_bss_34C90.team);
    }
    if (lbl_3_common_bss_34C90.state == 5) {
        lbl_8034E978._26 = 1;
    }
}

// .text:0x00099064 size:0x344 mapped:0x806D80F8
void fn_3_99064(void) {
    if ((lbl_3_common_bss_34C90.menu == 2 || lbl_3_common_bss_34C90.menu == 9) && lbl_3_common_bss_34C90.state == 0) {
        if (lbl_3_common_bss_32724.pauseTitleShown == 0) {
            fn_800B0A5C_insertQueue(fn_3_98DE0, 2);
        }
        fn_800B0A5C_insertQueue(fn_3_9894C, 2);
    }
    if (lbl_3_common_bss_34C90.menu == 4 || lbl_3_common_bss_34C90.menu == 0xB || lbl_3_common_bss_34C90.menu == 0xE ||
        (u8)(lbl_3_common_bss_34C90.menu - 7) <= 1 || lbl_3_common_bss_34C90.menu == 0xF) {
        fn_3_98EA8();
    }
    if ((lbl_3_common_bss_34C90.menu == 6 || lbl_3_common_bss_34C90.menu == 0xD) && lbl_3_common_bss_34C90.state == 2) {
        fn_800B0A5C_insertQueue(fn_3_983B8, 2);
    }
    if ((lbl_3_common_bss_34C90.menu == 0xC || lbl_3_common_bss_34C90.menu == 5) && lbl_3_common_bss_34C90.state == 1) {
        fn_800B0A5C_insertQueue(fn_80053FE8, 0);
        if (g_d_GameSettings.GameModeSelected != 5) {
            lbl_8034E978.menu = 9;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[9].track;
        } else {
            lbl_8034E978.menu = 0x1B;
            lbl_8034E978.prevTrack = lbl_8034E978.track;
            lbl_8034E978.track = lbl_800FEF70[0x1B].track;
        }
        fn_800B0A5C_insertQueue(fn_3_97CEC, 2);
    }
}
