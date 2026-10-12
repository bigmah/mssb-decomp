#include "game/auto_00_00167CC4_text.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_001690C0_text.h" // Bss35154View
#include "game/rep_3E58.h"
#include "static/GameSettings.h"
#include "main/file_800B0724.h" // scene task queue
#include "main/file_800263FC.h" // ParticleParamsF, fn_80026998
#include "Dolphin/stl.h"
#include "Dolphin/rand.h"

extern SparkleTask* lbl_803CC1B8; // running scene task
extern Bss35154View lbl_3_common_bss_35154;
extern ParticleParamsF lbl_3_data_28508; // sparkle emitter template
extern u8 lbl_3_data_28558[23];          // joints a sparkle can spawn at
extern TexArchive* lbl_803CBD0C;

// Spawns a randomly coloured sparkle at a random joint of the task's actor.
static inline void spawnSparkle(SparkleTask* task) {
    s8 joint = (s8)lbl_3_data_28558[(u32)rand() % 23];
    CharActor* actor = task->actor;
    Vec pos;
    ParticleParamsF prm;

    memset(&pos, 0, sizeof(Vec));
    memcpy(&prm, &lbl_3_data_28508, sizeof(ParticleParamsF));
    prm.tex = lbl_803CBD0C;
    if (fn_8001B728(actor->index, joint, &pos) == 0) {
        memset(&pos, 0, sizeof(Vec));
        fn_8001B728(actor->index, 4, &pos);
    }
    memcpy(&prm.pos, &pos, sizeof(Vec));
    prm.r = rand() % 256;
    prm.g = rand() % 256;
    prm.b = rand() % 256;
    fn_80026998(&prm);
}

// Starts the sparkle task for an actor; kind picks which animation(s) trigger it.
// .text:0x001682AC size:0x168 mapped:0x807A7340
void fn_3_1682AC(CharActor* actor, s8 kind) {
    SparkleTask* task = NULL;

    if (actor == NULL) {
        return;
    }
    switch (kind) {
    case 1:
        task = fn_800B0A5C_insertQueue(fn_3_1680D4, 0xFFFA);
        break;
    case 2:
        task = fn_800B0A5C_insertQueue(fn_3_167F14, 0xFFFA);
        break;
    case 4:
        task = fn_800B0A5C_insertQueue(fn_3_167CC4, 0xFFFA);
        break;
    case 3:
        task = fn_800B0A5C_insertQueue(fn_3_167D4C, 0xFFFA);
        break;
    case 10:
        task = fn_800B0A5C_insertQueue(fn_3_1678A8, 0xFFFA);
        break;
    case 8:
        task = fn_800B0A5C_insertQueue(fn_3_1674D0, 0xFFFA);
        break;
    case 6:
        task = fn_800B0A5C_insertQueue(fn_3_166FCC, 0xFFFA);
        break;
    case 12:
        task = fn_800B0A5C_insertQueue(fn_3_167178, 0xFFFA);
        break;
    case 11:
        task = fn_800B0A5C_insertQueue(fn_3_166E04, 0xFFFA);
        break;
    case 7:
        task = fn_800B0A5C_insertQueue(fn_3_166D40, 0xFFFA);
        break;
    }
    if (task != NULL) {
        task->actor = actor;
        task->_18 = 0;
        task->kind = kind;
        task->done = FALSE;
    }
}

// .text:0x001680D4 size:0x1D8 mapped:0x807A7168
void fn_3_1680D4(void) {
    SparkleTask* task = lbl_803CC1B8;
    void* q;
    s16 anim;

    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    anim = task->actor->anim[0];
    if (anim == 0x26 || (u16)(anim - 0x28) <= 3 || anim == 0x2C) {
        spawnSparkle(task);
        task->done = TRUE;
        return;
    }
    if (task->done) {
        fn_800B0A14_removeQueue((void*)(intptr_t)anim); // the argument is ignored
    }
}

// .text:0x00167F14 size:0x1C0 mapped:0x807A6FA8
void fn_3_167F14(void) {
    SparkleTask* task = lbl_803CC1B8;
    void* q;

    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    if (task->actor->anim[0] == 0x26) {
        spawnSparkle(task);
        task->done = TRUE;
        return;
    }
    if (task->done) {
        fn_800B0A14_removeQueue(task->actor);
    }
}

// .text:0x00167D4C size:0x1C8 mapped:0x807A6DE0
void fn_3_167D4C(void) {
    SparkleTask* task = lbl_803CC1B8;
    void* q;
    s16 anim;

    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    anim = task->actor->anim[0];
    if (anim == 0x1B || anim == 0x1A) {
        spawnSparkle(task);
        task->done = TRUE;
        return;
    }
    if (task->done) {
        fn_800B0A14_removeQueue(task->actor);
    }
}

// .text:0x00167CC4 size:0x88 mapped:0x807A6D58
void fn_3_167CC4(void) {
    void* q;

    // removeQueue ignores its argument; the original passes whatever is in r3.
    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    if (g_Ball.ballState == 2) {
        fn_3_16699C();
        return;
    }
    fn_800B0A14_removeQueue(&g_Ball);
}

