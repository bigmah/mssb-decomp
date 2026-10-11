#include "game/rep_1770.h"
#include "header_rep_data.h"

#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_data_D258[];
extern u8 lbl_3_data_D250[5];
extern u8 lbl_3_data_C56C[2][0x660];
extern u16 lbl_3_data_D22C[4];
extern u16 lbl_3_data_D234[14];
extern u8 lbl_3_data_C34C[];
extern u8 lbl_3_data_F430[12][2];
extern u8 lbl_3_data_F4D0[16];
extern s16 lbl_3_data_5F3C[4];
extern u8 lbl_3_data_C22C[];
extern u8 lbl_3_data_D378[];
extern u8 lbl_3_data_D4F8[];
extern void playSoundEffect(int);

// .text:0x000993A8 size:0x3C4 mapped:0x806D843C
void fn_3_993A8(void) {
    HudTask* task = HUD_TASK;
    s32 level = 0;
    LayoutObj* o;
    if (lbl_3_common_bss_32724.hudOff == 0 && lbl_3_common_bss_32724._A7 != 0) {
        if (g_Batter.chargeStatus != 0) {
            if (g_Batter.chargeUp < 1.0f) {
                HUD_OBJ(task, 2)->_64 = 0x49;
                level = 75.0f * g_Batter.chargeUp;
            } else {
                HUD_OBJ(task, 2)->_64 = 0x48;
                level = (s32)(31.0f * g_Batter.chargeDown) + 75;
            }
            if (g_Batter.chargeDown >= 1.0f) {
                HUD_OBJ(task, 3)->_5C = 0x6A << 16;
                o = HUD_OBJ(task, 2);
                if ((o->_5C >> 16) < 0x6A) {
                    o->_5C = 0x6A << 16;
                } else {
                    o->_68 = 1;
                }
                level = 0x6A;
            } else {
                HUD_OBJ(task, 3)->_5C = level << 16;
                HUD_OBJ(task, 2)->_5C = 0;
                HUD_OBJ(task, 2)->_68 = 0;
            }
        } else {
            HUD_OBJ(task, 3)->_5C = 0;
            HUD_OBJ(task, 3)->_68 = 0;
            HUD_OBJ(task, 2)->_5C = 0;
        }
        if (g_Batter.chargeStatus != 0) {
            HUD_OBJ(task, 5)->_68 = 0;
            if (g_Batter.swingInd != 0 && g_Batter.chargeDown >= 1.0f) {
                o = HUD_OBJ(task, 5);
                if ((o->_5C >> 16) < 0x6A) {
                    o->_5C = 0x6A << 16;
                } else {
                    o->_68 = 1;
                }
            } else {
                HUD_OBJ(task, 5)->_5C = (level + 10) << 16;
            }
        } else {
            if ((HUD_OBJ(task, 5)->_5C >> 16) < 10) {
                HUD_OBJ(task, 5)->_68 = 1;
            } else {
                HUD_OBJ(task, 5)->_5C = 10 << 16;
                HUD_OBJ(task, 5)->_68 = 0;
            }
        }
        if (g_Batter.chargeStatus != 0 && g_Batter.swingInd != 0) {
            if (task->state == 0) {
                HUD_OBJ(task, 6)->flags |= 2;
                HUD_OBJ(task, 6)->_5C = level << 16;
                HUD_OBJ(task, 7)->_5C = 0;
                HUD_OBJ(task, 7)->_68 = 1;
                task->state = 1;
            }
        } else {
            HUD_OBJ(task, 6)->flags &= ~2;
            task->state = 0;
        }
    } else {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x0009976C size:0xAC mapped:0x806D8800
void fn_3_9976C(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_D378);
    if (g_Batter.batterHand != 0) {
        HUD_OBJ(task, 0)->_5C = 0;
    } else {
        HUD_OBJ(task, 0)->_5C = 0x10000;
    }
    task->state = 0;
    HUD_TASK->func = fn_3_993A8;
}

// .text:0x00099818 size:0x3C4 mapped:0x806D88AC
void fn_3_99818(void) {
    HudTask* task = HUD_TASK;
    s32 level = 0;
    LayoutObj* o;
    f32 t;
    if (lbl_3_common_bss_32724.hudOff != 0) {
        goto remove;
    }
    if (g_Minigame.GameMode_MiniGame == 2) {
        if (g_GameLogic.gameStatus == 0xF) {
            goto remove;
        }
        if (g_Minigame.pauseInd != 0 && (lbl_3_common_bss_34C90.state == 7 || lbl_3_common_bss_34C90.state == 0xD)) {
            goto remove;
        }
    } else if (lbl_3_common_bss_32724._A7 == 0) {
        goto remove;
    }
    if (g_Pitcher.ChargePitchType != 0) {
        t = (f32)g_Pitcher.unknownFrameCounter / (f32)(g_Pitcher.pitchWindUpCountDown - lbl_3_data_5F3C[2]);
        if (t >= 1.0f) {
            t = 1.0f;
        }
        HUD_OBJ(task, 3)->_68 = 0;
        level = 106.0f * t;
        if (g_Pitcher.ChargePitchType == 3) {
            HUD_OBJ(task, 3)->_5C = 0x6A << 16;
            o = HUD_OBJ(task, 2);
            if ((s32)(o->_5C >> 16) < 0x6A) {
                o->_5C = 0x6A << 16;
            } else {
                o->_68 = 1;
            }
            level = 0x6A;
        } else if (g_Pitcher.overChargeInd != 0) {
            level = 106.0f * g_Pitcher.pitchChargeUp;
            HUD_OBJ(task, 3)->_5C = level << 16;
        } else {
            HUD_OBJ(task, 3)->_5C = level << 16;
        }
    } else {
        HUD_OBJ(task, 3)->_5C = 0;
        HUD_OBJ(task, 3)->_68 = 0;
        HUD_OBJ(task, 2)->_5C = 0;
    }
    if (g_Pitcher.ChargePitchType != 0) {
        HUD_OBJ(task, 5)->_68 = 0;
        if (g_Pitcher.ChargePitchType == 3) {
            HUD_OBJ(task, 5)->_68 = 1;
        } else {
            HUD_OBJ(task, 5)->_5C = (level + 10) << 16;
        }
    } else {
        if ((HUD_OBJ(task, 5)->_5C >> 16) < 10) {
            HUD_OBJ(task, 5)->_68 = 1;
        } else {
            HUD_OBJ(task, 5)->_5C = 10 << 16;
            HUD_OBJ(task, 5)->_68 = 0;
        }
    }
    if (g_Pitcher.ChargePitchType >= 2) {
        if (task->state == 0) {
            HUD_OBJ(task, 6)->flags |= 2;
            HUD_OBJ(task, 6)->_5C = level << 16;
            HUD_OBJ(task, 7)->_5C = 0;
            HUD_OBJ(task, 7)->_68 = 1;
            task->state = 1;
        }
    } else {
        HUD_OBJ(task, 6)->flags &= ~2;
        task->state = 0;
    }
    return;
remove:
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
}

// .text:0x00099BDC size:0xAC mapped:0x806D8C70
void fn_3_99BDC(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_D258);
    if (g_Minigame.GameMode_MiniGame == 2) {
        HUD_OBJ(task, 0)->_5C = 0x30000;
    } else {
        HUD_OBJ(task, 0)->_5C = 0x20000;
    }
    task->state = 0;
    HUD_TASK->func = fn_3_99818;
}

// .text:0x00099C88 size:0x74 mapped:0x806D8D1C
void fn_3_99C88(void) {
    HudTask* task = HUD_TASK;
    u8 v;
    if (lbl_3_common_bss_32724.hudOff == 0 && (v = lbl_3_common_bss_32724._A7) != 0) {
        LayoutObj* o = HUD_OBJ(task, 0);
        u32 w = o->color;
        w = v | (w & ~0xFF);
        o->color = w;
    } else {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00099CFC size:0x114 mapped:0x806D8D90
void fn_3_99CFC(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_D4F8);
    if (!(g_Batter.runnersOnBase & 1)) {
        HUD_OBJ(task, 3)->flags &= ~2;
    }
    if (!(g_Batter.runnersOnBase & 2)) {
        HUD_OBJ(task, 2)->flags &= ~2;
    }
    if (!(g_Batter.runnersOnBase & 4)) {
        HUD_OBJ(task, 1)->flags &= ~2;
    }
    if (g_Pitcher.nPitchesThisAB == 0 && g_Pitcher.nPickoffAttempts == 0) {
        playSoundEffect(0x1AB);
    }
    HUD_TASK->func = fn_3_99C88;
}

// .text:0x00099E10 size:0xA94 mapped:0x806D8EA4
// NONMATCHING 99%: register allocation only (original walks task->stars and &g_GameLogic.TeamStars with r31/r12); decl-order shuffles did not fix it
#if NONMATCHING
void fn_3_99E10(void) {
    StarHudTask* task = (StarHudTask*)lbl_803CC1B8;
    s32 gained = -1;
    s32 lost = -1;
    s32 moonStars = -1;
    s32 i;
    s32 team;
    task->timer++;
    if (lbl_3_common_bss_32724.hudOff != 0 || g_GameLogic.hudLoadingRelated != 0 || g_GameLogic.gameStatus == 3 ||
        g_GameLogic.gameStatus == 0xE || g_GameLogic.secondaryGameMode == 0xA) {
        goto remove;
    }
    if (g_GameLogic.IsStarChance == 0 || lbl_3_common_bss_34C90._1D5 != 0) {
        if (lbl_3_common_bss_32724._A7 == 0) {
            goto remove;
        }
        if (lbl_3_common_bss_32724._A7 < 0xFF) {
            for (i = 0; i < 50; i++) {
                HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A7;
            }
        } else {
            for (i = 0; i < 50; i++) {
                HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A6;
            }
        }
    }
    if (lbl_3_common_bss_34C90._1D5 != 0) {
        if (lbl_3_common_bss_32724._A7 == 0) {
            goto remove;
        }
        if (lbl_3_common_bss_32724._A7 < 0xFF) {
            for (i = 0; i < 50; i++) {
                HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A7;
            }
        }
    }
    for (team = 0; team < 2; team++) {
        for (i = 0; i < 5; i++) {
            s32 idx = i + 0x27;
            u16 base;
            s32 stars;
            LayoutObj* o;
            s32 frame;
            if (team == g_GameLogic.teamFielding) {
                idx = i + 0x22;
            }
            base = task->baseIdx;
            stars = g_GameLogic.TeamStars[team];
            o = lbl_80371C30[base + idx].obj;
            frame = o->_5C >> 16;
            if (g_Batter.moonShotInd != 0 && g_Ball.framesSinceHit == 0 && team == g_GameLogic.teamBatting) {
                {
                    s32 k;
                    for (k = 0; k < 5; k++) {
                        if (lbl_3_data_D250[k] > g_GameLogic.PauseSimulationFrameCount) {
                            break;
                        }
                    }
                    stars = k;
                }
                moonStars = stars;
            }
            if (stars > i) {
                if (task->stars[team] <= i) {
                    if (frame == 0) {
                        s32 flash = lbl_80371C30[base + 44].obj->_5C >> 16;
                        if (flash == 0) {
                            gained = team;
                        } else if (flash == 0x19) {
                            o->_5C = 0x40000;
                            HUD_OBJ(task, idx)->_68 = 1;
                        }
                    } else if (frame >= 0x14) {
                        o->_5C = 0x30000;
                        HUD_OBJ(task, idx)->_68 = 0;
                        task->stars[team]++;
                    }
                } else if (frame >= 3) {
                    o->_68 = 0;
                }
            } else if (stars < task->stars[team] && frame >= 3) {
                o->_68 = 4;
                lost = team;
                task->stars[team]--;
                if (moonStars >= 0 && moonStars != 4) {
                    lost = -1;
                }
            }
        }
    }
    if (gained >= 0) {
        HUD_OBJ(task, 44)->flags |= 2;
        HUD_OBJ(task, 44)->_68 = 1;
        HUD_OBJ(task, 45)->_68 = 1;
        if (g_Batter.batterHand == 0) {
            if (gained == g_GameLogic.teamFielding) {
                HUD_OBJ(task, 45)->_72 = 1;
            } else {
                HUD_OBJ(task, 45)->_72 = 0;
            }
        } else if (gained == g_GameLogic.teamFielding) {
            HUD_OBJ(task, 45)->_72 = 3;
        } else {
            HUD_OBJ(task, 45)->_72 = 2;
        }
    } else if ((HUD_OBJ(task, 44)->_69 == 2) ? 1 : 0) {
        HUD_OBJ(task, 44)->flags |= 2;
        HUD_OBJ(task, 44)->_68 = 0;
        HUD_OBJ(task, 44)->_5C = 0;
        HUD_OBJ(task, 45)->_68 = 0;
        HUD_OBJ(task, 45)->_5C = 0;
        HUD_OBJ(task, 44)->flags &= ~2;
    }
    if (lost >= 0) {
        HUD_OBJ(task, 46)->flags |= 2;
        HUD_OBJ(task, 46)->_68 = 4;
        HUD_OBJ(task, 47)->_68 = 4;
        if (g_Batter.batterHand == 0) {
            if (lost == g_GameLogic.teamFielding) {
                HUD_OBJ(task, 47)->_72 = 1;
            } else {
                HUD_OBJ(task, 47)->_72 = 0;
            }
        } else if (lost == g_GameLogic.teamFielding) {
            HUD_OBJ(task, 47)->_72 = 3;
        } else {
            HUD_OBJ(task, 47)->_72 = 2;
        }
    } else if ((HUD_OBJ(task, 46)->_5C >> 16) == 0) {
        HUD_OBJ(task, 46)->flags |= 2;
        HUD_OBJ(task, 46)->_68 = 0;
        HUD_OBJ(task, 46)->_5C = 0x1E0000;
        HUD_OBJ(task, 47)->_68 = 0;
        HUD_OBJ(task, 47)->_5C = 0x1E0000;
        HUD_OBJ(task, 46)->flags &= ~2;
    }
    return;
remove:
    fn_80034CEC(task);
    REMOVE_QUEUE_NOARG();
    lbl_3_common_bss_32724._A8 = 0;
}
#endif

// .text:0x0009A8A4 size:0x864 mapped:0x806D9938
void fn_3_9A8A4(void) {
    HudTask* task = HUD_TASK;
    s32 next;
    s32 i;
    fn_80034E20(task, lbl_3_data_C56C[g_Batter.batterHand]);
    HUD_OBJ(task, 9)->_5C = inMemRoster[g_GameLogic.teamFielding][g_Pitcher.rosterID].stats.CharID << 16;
    HUD_OBJ(task, 10)->_5C = inMemRoster[g_GameLogic.teamBatting][g_Batter.rosterID].stats.CharID << 16;
    next = g_GameLogic.currentBatterPerTeam[g_GameLogic.homeTeamBattingInd_fieldingTeam] + 1;
    if (next > 9) {
        next = 1;
    }
    next = g_GameLogic.battingOrderAndPositionMapping[g_GameLogic.homeTeamBattingInd_fieldingTeam][next][0];
    HUD_OBJ(task, 6)->_5C = inMemRoster[g_GameLogic.teamBatting][next].stats.CharID << 16;
    fn_800363D8(task, 13, 1, 0x2A, lbl_3_data_D22C[inMemRoster[g_GameLogic.teamFielding][g_Pitcher.rosterID].stats.CharacterClass]);
    fn_800363D8(task, 14, 1, 0x2A, lbl_3_data_D22C[inMemRoster[g_GameLogic.teamBatting][g_Batter.rosterID].stats.CharacterClass]);
    if (g_GameLogic._13E[g_GameLogic.teamFielding] != 0) {
        HUD_OBJ(task, 15)->_5C = (g_GameLogic.teams[g_GameLogic.teamFielding] + 4) << 16;
    } else {
        HUD_OBJ(task, 15)->_5C = g_GameLogic.teams[g_GameLogic.teamFielding] << 16;
    }
    if (g_GameLogic._13E[g_GameLogic.teamBatting] != 0) {
        HUD_OBJ(task, 16)->_5C = (g_GameLogic.teams[g_GameLogic.teamBatting] + 4) << 16;
    } else {
        HUD_OBJ(task, 16)->_5C = g_GameLogic.teams[g_GameLogic.teamBatting] << 16;
    }
    for (i = 0; i < 5; i++) {
        if (g_GameLogic.TeamStars[g_GameLogic.teamFielding] > i) {
            lbl_80371C30[task->baseIdx + 0x22 + i].obj->_5C = 0x30000;
        }
        if (g_GameLogic.TeamStars[g_GameLogic.teamBatting] > i) {
            lbl_80371C30[task->baseIdx + 0x27 + i].obj->_5C = 0x30000;
        }
    }
    if (lbl_800E8754._04 == 0 && g_d_GameSettings.GameModeSelected != 2) {
        fn_800363D8(task, 3, 1, 0x22, lbl_3_data_D234[0]);
        fn_800363D8(task, 4, 1, 0x22, lbl_3_data_D234[0]);
        HUD_OBJ(task, 3)->color = (HUD_OBJ(task, 3)->color & 0xFF) | 0xBEBEBE00;
        HUD_OBJ(task, 4)->color = (HUD_OBJ(task, 4)->color & 0xFF) | 0xBEBEBE00;
        for (i = 0x18; i <= 0x2B; i++) {
            HUD_OBJ(task, i)->flags &= ~2;
        }
    } else {
        fn_800363D8(task, 3, 1, 0x22, lbl_3_data_D234[inMemRoster[g_GameLogic.teamFielding][g_Pitcher.rosterID].stats.CaptainStarHitPitch]);
        fn_800363D8(task, 4, 1, 0x22, lbl_3_data_D234[inMemRoster[g_GameLogic.teamBatting][g_Batter.rosterID].stats.CaptainStarHitPitch]);
    }
    if (g_GameLogic.IsStarChance != 0) {
        HUD_OBJ(task, 21)->flags &= ~2;
        HUD_OBJ(task, 17)->flags &= ~2;
    } else {
        HUD_OBJ(task, 22)->flags &= ~2;
        if (g_Batter.chemLinksOnBase == 0) {
            HUD_OBJ(task, 17)->flags &= ~2;
        }
        if (lbl_3_common_bss_32724._AE == 0 || lbl_3_common_bss_32724._AF != g_Pitcher.rosterID) {
            HUD_OBJ(task, 21)->flags &= ~2;
        }
    }
    HUD_OBJ(task, 46)->_5C = 0x1E0000;
    HUD_OBJ(task, 47)->_5C = 0x1E0000;
    if (g_d_GameSettings.exhibitionMatchInd == 0) {
        // TODO type: per-character "starred" flags live 0x43D6 bytes into this save block
        u8* starred = (u8*)starMissionCompletionTracker + 0x43D6;
        if (starred[g_Pitcher.charID] != 0 && g_GameLogic._13E[g_GameLogic.teamFielding] == 0) {
            HUD_OBJ(task, 48)->flags |= 2;
        }
        if (starred[g_Batter.charID] != 0 && g_GameLogic._13E[g_GameLogic.teamBatting] == 0) {
            HUD_OBJ(task, 49)->flags |= 2;
        }
    } else {
        if ((lbl_8034E9A0._489B + g_GameLogic.teamFielding * 9)[g_Pitcher.rosterID] != 0) {
            HUD_OBJ(task, 48)->flags |= 2;
        }
        if ((lbl_8034E9A0._489B + g_GameLogic.teamBatting * 9)[g_Batter.rosterID] != 0) {
            HUD_OBJ(task, 49)->flags |= 2;
        }
    }
    if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceLevel != 7) {
        HUD_OBJ(task, 20)->flags &= ~2;
        HUD_OBJ(task, 5)->flags &= ~2;
    }
    task->timer = 0;
    task->state = g_GameLogic.TeamStars[0];
    task->_1E = g_GameLogic.TeamStars[1];
    task->_20 = 0;
    lbl_3_common_bss_32724._A8 = 1;
    HUD_TASK->func = fn_3_99E10;
}

// .text:0x0009B108 size:0x218 mapped:0x806DA19C
void fn_3_9B108(HudTask* task) {
    if (g_Scores.team[0].runs[0] >= 10) {
        fn_3_972A0(task, 11, 4, g_Scores.team[0].runs[0] % 10);
        fn_3_972A0(task, 12, 3, g_Scores.team[0].runs[0] / 10);
        fn_3_972A0(task, 11, 10, g_Scores.team[0].runs[0] % 10);
        fn_3_972A0(task, 12, 9, g_Scores.team[0].runs[0] / 10);
    } else {
        fn_3_972A0(task, 10, 1, g_Scores.team[0].runs[0]);
        fn_3_972A0(task, 10, 7, g_Scores.team[0].runs[0]);
    }
    if (g_Scores.team[1].runs[0] >= 10) {
        fn_3_972A0(task, 14, 6, g_Scores.team[1].runs[0] % 10);
        fn_3_972A0(task, 15, 5, g_Scores.team[1].runs[0] / 10);
        fn_3_972A0(task, 14, 12, g_Scores.team[1].runs[0] % 10);
        fn_3_972A0(task, 15, 11, g_Scores.team[1].runs[0] / 10);
    } else {
        fn_3_972A0(task, 13, 2, g_Scores.team[1].runs[0]);
        fn_3_972A0(task, 13, 8, g_Scores.team[1].runs[0]);
    }
}

// .text:0x0009B320 size:0x4D4 mapped:0x806DA3B4
void fn_3_9B320(void) {
    HudTask* task = HUD_TASK;
    s32 i;
    task->timer++;
    if (lbl_3_common_bss_32724.hudOff != 0 || lbl_3_common_bss_32724._A7 == 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (task->state != g_Scores.team[0].runs[0] || task->_1E != g_Scores.team[1].runs[0]) {
        fn_3_9B108(task);
    }
    if (lbl_3_common_bss_32724._A7 < 0xFF) {
        for (i = 0; i < 16; i++) {
            HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A7;
        }
    } else {
        for (i = 4; i <= 15; i++) {
            HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A6;
        }
    }
}

// .text:0x0009B7F4 size:0x6EC mapped:0x806DA888
void fn_3_9B7F4(void) {
    HudTask* task = HUD_TASK;
    fn_80034E20(task, lbl_3_data_C34C);
    HUD_OBJ(task, 5)->_64 = lbl_3_data_F430[g_GameLogic.logo[0].captain][1];
    HUD_OBJ(task, 6)->_64 = lbl_3_data_F430[g_GameLogic.logo[1].captain][1];
    HUD_OBJ(task, 5)->_5C = g_GameLogic.logo[0].variationID << 16;
    HUD_OBJ(task, 6)->_5C = g_GameLogic.logo[1].variationID << 16;
    if (g_Scores._AD != 0) {
        HUD_OBJ(task, 1)->_64 = 0x11B;
        HUD_OBJ(task, 2)->_64 = 0x119;
        HUD_OBJ(task, 3)->_64 = 0x116;
    }
    fn_8003649C(task, 3, 1, 0x110, lbl_3_data_F4D0[g_Scores.inning - 1]);
    fn_8003649C(task, 3, 3, 0x110, lbl_3_data_F4D0[g_Scores.inning - 1]);
    if (g_Scores.inning >= 10) {
        HUD_OBJ(task, 7)->flags &= ~2;
        HUD_OBJ(task, 8)->flags |= 2;
        HUD_OBJ(task, 9)->flags |= 2;
        HUD_OBJ(task, 9)->_5C = 0;
        HUD_OBJ(task, 8)->_5C = 0x10000;
        fn_8003649C(task, 9, 1, 0x112, g_Scores.inning / 10);
        fn_8003649C(task, 8, 2, 0x112, g_Scores.inning % 10);
        fn_8003649C(task, 9, 4, 0x112, g_Scores.inning / 10);
        fn_8003649C(task, 8, 5, 0x112, g_Scores.inning % 10);
    } else {
        HUD_OBJ(task, 7)->_5C = 0x20000;
        fn_8003649C(task, 7, 3, 0x112, g_Scores.inning);
        fn_8003649C(task, 7, 6, 0x112, g_Scores.inning);
    }
    if (g_Scores.team[0].runs[0] >= 10) {
        HUD_OBJ(task, 10)->flags &= ~2;
        HUD_OBJ(task, 11)->flags |= 2;
        HUD_OBJ(task, 12)->flags |= 2;
        HUD_OBJ(task, 12)->_5C = 0x20000;
        HUD_OBJ(task, 11)->_5C = 0x30000;
    } else {
        HUD_OBJ(task, 10)->_5C = 0;
    }
    if (g_Scores.team[1].runs[0] >= 10) {
        HUD_OBJ(task, 13)->flags &= ~2;
        HUD_OBJ(task, 14)->flags |= 2;
        HUD_OBJ(task, 15)->flags |= 2;
        HUD_OBJ(task, 15)->_5C = 0x40000;
        HUD_OBJ(task, 14)->_5C = 0x50000;
    } else {
        HUD_OBJ(task, 13)->_5C = 0x10000;
    }
    fn_3_9B108(task);
    task->state = g_Scores.team[0].runs[0];
    task->_1E = g_Scores.team[1].runs[0];
    task->timer = 0;
    HUD_TASK->func = fn_3_9B320;
}

// .text:0x0009BEE0 size:0x134 mapped:0x806DAF74
void fn_3_9BEE0(HudTask* task) {
    // TODO type: strikes/balls/outs read as an s32[3]; the named fields change register allocation
    s32 target = ((s32*)&g_Strikes)[2];
    s32 i;
    if (g_d_GameSettings.GameModeSelected == 6) {
        target = g_Minigame._190D - g_Minigame._1910;
    }
    for (i = 0; i < 7; i++) {
        s32 state = 3;
        if (g_d_GameSettings.GameModeSelected == 6 && i >= 5) {
            break;
        }
        if (i < 2) {
            if (task->state == ((s32*)&g_Strikes)[0]) {
                continue;
            }
            if (((s32*)&g_Strikes)[0] >= i + 1) {
                state = 0;
            }
        } else if (i < 5) {
            if (task->_1E == ((s32*)&g_Strikes)[1]) {
                continue;
            }
            if (((s32*)&g_Strikes)[1] >= i - 1) {
                state = 1;
            }
        } else {
            if (task->_20 == target) {
                continue;
            }
            if (target >= i - 4) {
                state = 2;
            }
        }
        fn_8003649C(task, i + 1, i + 1, 0x107, state);
    }
    task->state = ((s32*)&g_Strikes)[0];
    task->_1E = ((s32*)&g_Strikes)[1];
    task->_20 = target;
}

// .text:0x0009C014 size:0x278 mapped:0x806DB0A8
void fn_3_9C014(void) {
    HudTask* task = HUD_TASK;
    s32 i;
    if (lbl_3_common_bss_32724.hudOff != 0 || lbl_3_common_bss_32724._A7 == 0) {
        fn_80034CEC(task);
        REMOVE_QUEUE_NOARG();
        return;
    }
    task->timer++;
    fn_3_9BEE0(task);
    if (lbl_3_common_bss_32724._A7 < 0xFF) {
        HUD_OBJ(task, 0)->color = (HUD_OBJ(task, 0)->color & ~0xFF) | lbl_3_common_bss_32724._A7;
        for (i = 1; i < 8; i++) {
            HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A7;
        }
    } else {
        for (i = 1; i < 8; i++) {
            HUD_OBJ(task, i)->color = (HUD_OBJ(task, i)->color & ~0xFF) | lbl_3_common_bss_32724._A6;
        }
    }
}

// .text:0x0009C28C size:0x2EC mapped:0x806DB320
void fn_3_9C28C(void) {
    HudTask* task = HUD_TASK;
    s32 i;
    fn_80034E20(task, lbl_3_data_C22C);
    task->_22 = 0;
    if (g_d_GameSettings.GameModeSelected == 6) {
        task->_22 = 1;
        for (i = 0; i < 8; i++) {
            HUD_OBJ(task, i)->y = -30.0f;
        }
    } else if (g_d_GameSettings.GameModeSelected == 2 && g_Practice.practiceLevel != 7 && g_Practice.practiceLevel != 6) {
        task->_22 = 1;
    }
    if (task->_22 != 0) {
        for (i = 1; i < 6; i++) {
            HUD_OBJ(task, i)->_64 = 0x104;
        }
        HUD_OBJ(task, 0)->_64 = 0x103;
        HUD_OBJ(task, 6)->flags &= ~2;
        HUD_OBJ(task, 7)->flags &= ~2;
    }
    task->_20 = 9;
    task->_1E = 9;
    task->state = 9;
    for (i = 1; i < 8; i++) {
        HUD_OBJ(task, i)->_5C = (i - 1) << 16;
    }
    fn_3_9BEE0(task);
    task->timer = 0;
    HUD_TASK->func = fn_3_9C014;
}

