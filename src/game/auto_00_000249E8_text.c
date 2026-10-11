#include "game/auto_00_000249E8_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "game/rep_E08.h"
#include "game/rep_1838.h"
#include "Dolphin/stl.h"

// main.dol (main/file_80011640.h)
void QueueCharacterAnimation(s32 index, s32 anim, s32 a, s32 b, s32 c, s32 d, s32 e);
void AnimateCharacter(s32 index, s32 anim, s32 a, u8 mode, s32 b, s32 c, s32 d, s32 e);

extern SceneActorSetup lbl_3_data_1D28[];
extern SceneActorSetup lbl_3_data_1E434[];
extern SceneActorSetup lbl_3_data_1F090[];
extern u8* lbl_3_data_1F40[13]; // per mode: actor-setup script

typedef struct Unk2398Entry {
    /*0x00*/ u8 _00[0x34];
    /*0x34*/ s32 _34[3];
} Unk2398Entry; // size: 0x40
extern Unk2398Entry lbl_3_data_2398[];

// .text:0x000249E8 size:0xF4 mapped:0x80663A7C
void fn_3_249E8(s32 idx) {
    SceneActorSetup* e = &lbl_3_data_1F090[idx];
    s32 i;
    u8 key = e->actor;

    for (i = 0; i < 9; i++) {
        if (key == g_Fielders[i].opponentIdx) {
            lbl_3_common_bss_1323C->actorSetup[i] = idx;
            if (!e->keepPos) {
                memcpy(&g_Fielders[i], e, 0xC);
            }
            g_Fielders[i].rotY = lbl_3_common_bss_1323C->actors[i].rotY = e->rotY;
            lbl_3_common_bss_1323C->animSet[i] = 1;
            AnimateCharacter(i, e->anim, e->animA, e->animMode, e->animB, e->animArg, 0, 0);
        }
    }
}

// .text:0x00024ADC size:0x2E0 mapped:0x80663B70
void fn_3_24ADC(s32 idx, s32 queued) {
    SceneActorSetup* e = &lbl_3_data_1E434[idx];
    s32 a = e->actor;
    GameActorView* actor;
    InMemRunnerType* runner;
    u8 m;

    lbl_3_common_bss_1323C->actorSetup[a] = idx;
    if (a <= 8) {
        actor = lbl_8036E548.actors[a];
        if (!e->keepPos) {
            memcpy(&g_Fielders[a], e, 0xC);
            if (actor != NULL) {
                memcpy(&actor->pos, e, 0xC);
            }
        }
        g_Fielders[a].rotY = lbl_3_common_bss_1323C->actors[a].rotY = e->rotY;
        if (actor != NULL) {
            actor->rotY = e->rotY;
            actor->_25D = 1;
        }
        if (e->anim >= 0x69 && e->anim < 0x75) {
            m = 0;
        } else {
            m = g_Fielders[a]._1C7;
        }
        lbl_3_common_bss_1323C->animSet[a] = 1;
        lbl_3_common_bss_1323C->posSet[a] = 1;
    } else if (a <= 12) {
        actor = lbl_8036E548.actors[a];
        if (a == 10) {
            if (actor == NULL) {
                return;
            }
        } else if (a == 11) {
            if (actor == NULL) {
                return;
            }
        } else if (a == 12) {
            if (actor == NULL) {
                return;
            }
        }
        runner = &g_Runners[a - 9];
        if (!e->keepPos) {
            memcpy(runner, e, 0xC);
            if (actor != NULL) {
                memcpy(&actor->pos, e, 0xC);
            }
        }
        runner->runningAngle = lbl_3_common_bss_1323C->actors[a].rotY = e->rotY;
        if (actor != NULL) {
            actor->rotY = e->rotY;
            actor->_25D = 1;
        }
        lbl_3_common_bss_1323C->animSet[a] = 1;
        lbl_3_common_bss_1323C->posSet[a] = 1;
        if (a == 9) {
            if (lbl_3_common_bss_1323C->mode == 0 || lbl_3_common_bss_1323C->mode == 1) {
                if (g_Batter.batterHand == 1) {
                    m = 0;
                } else {
                    m = 1;
                }
            } else {
                m = 0;
            }
        } else {
            m = 0;
        }
    }
    if (queued == 0) {
        AnimateCharacter(a, e->anim, e->animA, e->animMode, e->animB, e->animArg, m, 0);
    } else {
        QueueCharacterAnimation(a, e->anim, e->animA, e->animB, e->animArg, m, 0);
    }
}

// .text:0x00024DBC size:0xE4 mapped:0x80663E50
void fn_3_24DBC(s32 mode) {
    s32 i;

    for (i = 0; i < 13; i++) {
        lbl_3_common_bss_1323C->actorSetup[i] = -1;
        memset(&lbl_3_common_bss_1323C->actors[i], 0, sizeof(SceneActorState));
        lbl_3_common_bss_1323C->animSet[i] = 0;
    }
    fn_3_6714C(0);
    lbl_3_common_bss_1323C->_25C = 1;
    lbl_3_common_bss_1323C->_23C = 0;
    lbl_3_common_bss_1323C->_27C = 0;
    lbl_3_common_bss_1323C->mode = mode;
    lbl_3_common_bss_1323C->_25F = 1;
    lbl_3_common_bss_1323C->_27D = 0;
    lbl_3_common_bss_1323C->busy = 0;
    lbl_3_common_bss_1323C->_25A = 0;
    lbl_3_common_bss_1323C->_280 = 1;
}

// .text:0x00024EA0 size:0x80 mapped:0x80663F34
void fn_3_24EA0(void) {
    s32 i;

    for (i = 0; i < 13; i++) {
        lbl_3_common_bss_1323C->actorSetup[i] = -1;
        memset(&lbl_3_common_bss_1323C->actors[i], 0, sizeof(SceneActorState));
        lbl_3_common_bss_1323C->animSet[i] = 0;
    }
}

// .text:0x00024F20 size:0x4 mapped:0x80663FB4
void fn_3_24F20(void) {
}

// .text:0x00024F24 size:0x1D8 mapped:0x80663FB8
void fn_3_24F24(s32 mode) {
    u8* script = lbl_3_data_1F40[mode];
    s32 range = 0;
    s32 i;
    u8 k;

    for (i = 0; i < 13; i++) {
        lbl_3_common_bss_1323C->actorSetup[i] = -1;
    }
    lbl_3_common_bss_1323C->_25C = 1;
    lbl_3_common_bss_1323C->_23C = 0;
    lbl_3_common_bss_1323C->_27C = 0;
    lbl_3_common_bss_1323C->mode = mode;
    lbl_3_common_bss_1323C->_25F = 1;
    lbl_3_common_bss_1323C->_27D = 0;
    lbl_3_common_bss_1323C->busy = 0;
    lbl_3_common_bss_1323C->_25A = 0;
    lbl_3_common_bss_1323C->_280 = 1;
    lbl_3_common_bss_1323C->_23E = *script * 10;
    if (*++script == 0xFD) {
        range = 2;
        script++;
    }
    lbl_3_common_bss_1323C->_25E = *script++;
    if (range != 0) {
        lbl_3_common_bss_1323C->_25E += random_fn_3_9EE24(range);
    }
    for (;;) {
        k = *script;
        if (k == 0xFE) {
            break;
        }
        script++;
        lbl_3_common_bss_1323C->actorSetup[lbl_3_data_1D28[k].actor] = k;
    }
}

// .text:0x000250FC size:0xE8 mapped:0x80664190
void fn_3_250FC(void) {
    return;
}
