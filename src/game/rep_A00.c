#include "game/rep_A00.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/GameSettings.h"
#include "game/auto_00_000249E8_text.h"
#include "main/file_80069BDC.h"
#include "main/file_80039AC0.h"
#include "Dolphin/stl.h"
#include "game/auto_00_000FBCD0_text.h"
#include "game/auto_00_0006C854_text.h"
#include "game/auto_00_0005985C_text.h"
#include "game/rep_E08.h"
#include "main/file_80011640.h"

// Views declared here (other units have their own views of these objects).
extern FielderView g_Fielders[];
extern SceneWork* lbl_3_common_bss_1323C;
extern GameScores g_Scores;
extern ScreenFx lbl_803C5090;
extern Unk2398Entry lbl_3_data_2398[];
extern ARAMLoaderView lbl_803C6CF8;

extern const f32 lbl_3_rodata_A50;
extern const f32 lbl_3_rodata_A54; // 0.0f
extern const f64 lbl_3_rodata_A58; // 0.02
extern const f64 lbl_3_rodata_A60; // -0.02
extern const f32 lbl_3_rodata_A68; // 1 degree in radians
extern const f32 lbl_3_rodata_A6C; // 3.0f, arrival distance
extern s32 lbl_3_bss_A0;
extern s32 lbl_3_bss_9C;

void fn_80052798(s32 count); // main/file_8004C5F8.h
f32 fn_3_9FEA8(f32 v);        // game/rep_1838.h: wrap angle

#define SCENE lbl_3_common_bss_1323C
#define FADE_TASK ((FadeTask*)lbl_803CC1B8)

// Inline copy of fn_3_24DBC (auto_00_000249E8_text.c): clears the scene actors and starts scene mode `mode`.
static inline void SceneReset(s32 mode) {
    s32 i;

    for (i = 0; i < 13; i++) {
        SCENE->actorSetup[i] = -1;
        memset(&SCENE->actors[i], 0, sizeof(SceneActorState));
        SCENE->animSet[i] = 0;
    }
    fn_3_6714C(0);
    SCENE->_25C = 1;
    SCENE->_23C = 0;
    SCENE->_27C = 0;
    SCENE->mode = mode;
    SCENE->_25F = 1;
    SCENE->_27D = 0;
    SCENE->busy = 0;
    SCENE->_25A = 0;
    SCENE->_280 = 1;
}

// .text:0x00021C90 size:0x154 mapped:0x80660D24
void fn_3_21C90(void) {
    FadeTask* p = FADE_TASK;
    switch (lbl_3_bss_A0) {
    case 0:
        p->frame = 0;
        p->alpha = 0xFF;
        lbl_803C5090.flags = 9;
        lbl_803C5090.scale = 1.0f;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = p->alpha;
        lbl_3_bss_A0 += 1;
        return;
    case 1:
        lbl_803C5090.flags = 8;
        lbl_803C5090.scale = lbl_3_rodata_A50;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = p->alpha;
        p->frame = p->frame + 1;
        if (g_pCamera->_AAC <= p->frame) {
            g_pCamera->_AA8 = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)();
            lbl_3_bss_A0 = 0;
            return;
        }
        p->alpha = 0xFF - (p->frame * 0xFF) / g_pCamera->_AAC;
        return;
    case 2:
    default:
        return;
    }
}

// .text:0x00021DE4 size:0x130 mapped:0x80660E78
void fn_3_21DE4(void) {
    FadeTask* p = FADE_TASK;
    switch (lbl_3_bss_9C) {
    case 0:
        p->frame = 0;
        p->alpha = 0xFF;
        lbl_803C5090.flags = 9;
        lbl_803C5090.scale = 1.0f;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = 0xFF;
        lbl_3_bss_9C += 1;
        return;
    case 1:
        lbl_803C5090.flags = 8;
        lbl_803C5090.scale = lbl_3_rodata_A50;
        lbl_803C5090.lines = 0x1C0;
        lbl_803C5090.repeat = 1;
        lbl_803C5090.unk18 = 0;
        lbl_803C5090.r = 0xFF;
        lbl_803C5090.g = 0xFF;
        lbl_803C5090.b = 0xFF;
        lbl_803C5090.alpha = 0xFF;
        p->frame = p->frame + 1;
        if (g_pCamera->_AAE <= p->frame) {
            g_pCamera->_AAA = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)();
            lbl_3_bss_9C = 0;
        }
        return;
    case 2:
    default:
        return;
    }
}

// .text:0x00021F14 size:0x828 mapped:0x80660FA8
void fn_3_21F14(void) {
    return;
}

// .text:0x0002273C size:0xE0 mapped:0x806617D0
s32 fn_3_2273C(void) {
    FielderView* f = g_Fielders;
    CharActor* p;
    s32 i;
    for (i = 0; i < 9; i++) {
        if (f->opponentIdx == 0) {
            p = lbl_8036E548.active[i];
            if (p == NULL) {
                return 1;
            }
            if (p->_068 == 0) {
                return 1;
            }
        }
        f++;
    }
    return 0;
}

// .text:0x0002281C size:0x34 mapped:0x806618B0
s32 fn_3_2281C(s32 i) {
    CharActor* p = lbl_8036E548.active[i];
    if (p == NULL) {
        return 1;
    }
    return p->_068 == 0;
}

// .text:0x00022850 size:0xF4 mapped:0x806618E4
void fn_3_22850(void) {
    s32 i;
    for (i = 0; i < 0x21; i++) {
        lbl_3_data_2398[i]._34[1] = 0;
        lbl_3_data_2398[i]._34[2] = 0;
    }
    SCENE->_27B = 0;
}

// .text:0x00022944 size:0x4 mapped:0x806619D8
void fn_3_22944(void) {
    return;
}

// .text:0x00022948 size:0xD8 mapped:0x806619DC
void fn_3_22948(void) {
    s32 i;
    for (i = 0; i < 0x21; i++) {
        lbl_3_data_2398[i]._34[0] = 0;
        lbl_3_data_2398[i]._34[1] = 0;
        lbl_3_data_2398[i]._34[2] = 0;
    }
    SCENE->_27B = 0;
}

// .text:0x00022A20 size:0x9C mapped:0x80661AB4
s32 fn_3_22A20(void) {
    s16 x;
    s16 y;
    GameScoresTeam* t;
    if (g_Batter.aiControlledInd != 0) {
        t = g_Scores.team;
        x = t[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0];
        y = t[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
        return x >= y;
    }
    t = g_Scores.team;
    x = t[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0];
    y = t[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0];
    return (u32)__cntlzw(x >= y) >> 5; // !(x >= y)
}

// .text:0x00022ABC size:0x154 mapped:0x80661B50
s32 fn_3_22ABC(void) {
    s32 r = 0;
    s32 n = 0;
    s32 m;
    GameScores* sc = &g_Scores;
    InMemRunnerType* r2;
    InMemRunnerType* r3;
    s32 d;
    if (g_Runners[1].rosterID != -1) {
        n = 1;
    }
    r2 = g_Runners;
    if (r2[2].rosterID != -1) {
        n += 1;
    }
    r3 = g_Runners;
    if (r3[3].rosterID != -1) {
        n += 1;
    }
    d = sc->_A6;
    if (__abs(d) <= 4 && n == 3 && sc->team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] <= sc->team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
        r = 1;
    }
    m = 0;
    if (r2[2].rosterID != -1) {
        m = 1;
    }
    if (r3[3].rosterID != -1) {
        m += 1;
    }
    d = sc->_A6;
    if (__abs(d) <= m && m > 0 && sc->team[g_GameLogic.homeTeamBattingInd_fieldingTeam].runs[0] <= sc->team[g_GameLogic.awayTeamBattingInd_battingTeam].runs[0]) {
        r = 1;
    }
    if (r != 0) {
        return g_Batter.aiControlledInd != 0 ? 1 : 2;
    }
    return -1;
}

// .text:0x00022C10 size:0x10 mapped:0x80661CA4
void fn_3_22C10(void) {
    int i;
    for (i = 13; i != 0; i--) {
    }
}

// .text:0x00022C20 size:0x4B4 mapped:0x80661CB4
void fn_3_22C20(void) {
    return;
}

// .text:0x000230D4 size:0x3E8 mapped:0x80662168
void fn_3_230D4(void) {
    GameInitVariables* gs = &g_d_GameSettings;
    GameControlsStruct* gl = &g_GameLogic;
    s32 i;
    switch (gl->_125) {
    case 0:
        if ((s32)lbl_803C6CF8.idle == 1) {
            changeScene(1, 6);
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(0);
        }
        break;
    case 1:
        changeScene(1, 6);
        SceneReset(1);
        fn_3_FBDAC(0x6B);
        g_GameLogic.FrameCountOfCurrentAtBat_Copy = 0;
        gl->_125 = 2;
        break;
    case 2:
        if (SCENE->_23C == 9) {
            changeScene(1, 6);
        }
        if (SCENE->_23C < 0x7FFE) {
            SCENE->_23C += 1;
        } else {
            SCENE->_23C = 0x7FFF;
        }
        for (i = 0; i < 13; i++) {
            fn_8001D074(i, 1);
        }
        if (fn_3_6C938(1, 0x1100) != 0 && SCENE->_23C < SCENE->_23E - 7 && gs->GameModeSelected != 4
            && g_GameLogic.FrameCountOfCurrentAtBat_Copy > 60) {
            SCENE->_23C = SCENE->_23E - 8;
            changeScene(3, 6);
        }
        if (SCENE->_23C == SCENE->_23E) {
            fn_3_24630();
            fn_3_FBD70();
            fn_3_FBD58();
            fn_3_5A6D4(0);
        }
        break;
    }
}

// .text:0x000234BC size:0x3D4 mapped:0x80662550
void fn_3_234BC(void) {
    return;
}

// .text:0x00023890 size:0x45C mapped:0x80662924
void fn_3_23890(void) {
    return;
}

// .text:0x00023CEC size:0x40C mapped:0x80662D80
void fn_3_23CEC(void) {
    return;
}

// .text:0x000240F8 size:0x4A0 mapped:0x8066318C
void fn_3_240F8(void) {
    return;
}

// .text:0x00024598 size:0x98 mapped:0x8066362C
void fn_3_24598(void) {
    if (SCENE->_23C < 0x7FFE) {
        SCENE->_23C += 1;
    } else {
        SCENE->_23C = 0x7FFF;
    }
    if (SCENE->_23C == SCENE->_23E - 7) {
        changeScene(3, 6);
    }
    if (SCENE->_23C == SCENE->_23E) {
        g_GameLogic._125 += 1;
    }
}

// .text:0x00024630 size:0xD8 mapped:0x806636C4
void fn_3_24630(void) {
    s32 i;
    fn_80052798(1);
    for (i = 0; i < 13; i++) {
        SCENE->animSet[i] = 0;
    }
    SCENE->_25C = 0;
}

// .text:0x00024708 size:0x2E0 mapped:0x8066379C
// Walks each scripted actor toward its scene target; marks it arrived when close enough
// (or, in mode 3, when its animation has finished).
void fn_3_24708(void) {
    Mtx m;
    Vec v;
    CharActor* a;
    SceneActorState* st;
    InMemRunnerType* r;
    s32 i;
    f32 dist;
    f32 diff;

    i = 0;

    do {
        a = lbl_8036E548.active[i];
        if (a != NULL && (st = &SCENE->actors[i])->moving == 1) {
            if ((s32)SCENE->_27F != 3 || !(st->_1C > a->_068)) {
                if (i <= 8) {
                    dist = PSVECDistance((Vec*)&g_Fielders[i].pos, (Vec*)&st->pos);
                } else if (i <= 12) {
                    r = &g_Runners[i - 9];
                    SCENE->actors[i].targetRotY = atan2(-(st->pos.x - r->position.x), -(st->pos.z - r->position.z));
                    PSMTXRotRad(m, 'Y', SCENE->actors[i].rotY);
                    v.x = lbl_3_rodata_A54;
                    v.y = lbl_3_rodata_A54;
                    v.z = SCENE->actors[i].speed;
                    PSMTXMultVec(m, &v, &v);
                    r->position.x = r->position.x - v.x;
                    r->position.z = r->position.z - v.z;
                    st = &SCENE->actors[i];
                    diff = fn_3_9FEA8(st->rotY - st->targetRotY);
                    if (!((diff < lbl_3_rodata_A58 && diff > lbl_3_rodata_A54) || (diff > lbl_3_rodata_A60 && diff < lbl_3_rodata_A54))) {
                        if (diff < lbl_3_rodata_A54) {
                            SCENE->actors[i].rotY += lbl_3_rodata_A68;
                        } else {
                            SCENE->actors[i].rotY -= lbl_3_rodata_A68;
                        }
                    }
                    r->runningAngle = SCENE->actors[i].rotY;
                    dist = PSVECDistance((Vec*)&r->position, (Vec*)&SCENE->actors[i].pos);
                }
            }
            if ((s32)SCENE->_27F == 3) {
                if (a->_068 == 0) {
                    SCENE->actors[i].arrived = 1;
                    SCENE->actors[i].moving = 0;
                }
            } else if (dist < lbl_3_rodata_A6C) {
                SCENE->actors[i].arrived = 1;
                SCENE->actors[i].moving = 0;
            }
        }
        i++;
    } while (i < 13);
}

