#include "game/rep_3E58.h"
#include "game/UnknownHomes_Game.h"
#include "game/auto_00_001690C0_text.h" // Bss35154View
#include "game/auto_00_00167CC4_text.h" // SparkleTask
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "main/file_800B0724.h" // scene task queue
#include "main/file_800263FC.h" // ParticleParamsF, fn_80026998
#include "main/file_80011640.h" // CharMgr, CharActor
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "Dolphin/rand.h"
#include "stl/math.h"



extern SparkleTask* lbl_803CC1B8; // running scene task
extern Bss35154View lbl_3_common_bss_35154;
extern ParticleParamsF lbl_3_data_28508; // sparkle emitter template
extern u8 lbl_3_data_28558[23];          // joints a sparkle can spawn at
extern TexArchive* lbl_803CBD0C;
extern camera_803c639c_s* fn_80052768_getCamera(int);

#define RANDF() ((f32)rand() / 32767.0f)

static s8 lbl_3_bss_B9E0; // fn_3_1666B0 call counter

// .text:0x001666B0 size:0x1EC mapped:0x807A5744
// Every fifth call, puffs a randomly coloured sparkle near pos.
void fn_3_1666B0(Vec* pos) {
    Vec p;
    ParticleParamsF prm;

    if (++lbl_3_bss_B9E0 >= 5) {
        memset(&prm, 0, sizeof(ParticleParamsF));
        memcpy(&prm, &lbl_3_data_28508, sizeof(ParticleParamsF));
        memcpy(&p, pos, sizeof(Vec));
        prm.size1 = 0.2f * prm.size0;
        if (p.y > 0.0f) {
            p.y *= -1.0f;
        }
        lbl_3_bss_B9E0 = 0;
        prm.tex = lbl_803CBD0C;
        p.x += 5.0f * (RANDF() - 0.5f);
        p.y -= 3.0f * RANDF();
        p.z -= 0.45f;
        memcpy(&prm.pos, &p, sizeof(Vec));
        prm.r = rand() % 256;
        prm.g = rand() % 256;
        prm.b = rand() % 256;
        fn_80026998(&prm);
    }
}

// .text:0x0016689C size:0xD0 mapped:0x807A5930
void fn_3_16689C(void) {
    // removeQueue ignores its argument; the original passes whatever is in r3.
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL || g_GameLogic.framesOfExitingToMenu != 0 || g_Ball.fielderWBallIndex < 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (g_d_GameSettings.GameModeSelected == 6 && g_Minigame.TF_ballDespawnedInd) {
        fn_800B0A14_removeQueue(&g_Minigame);
        return;
    }
    if (g_Ball.ballState != 1) {
        fn_800B0A14_removeQueue(&g_Ball);
        return;
    }
    fn_3_16699C();
}

// .text:0x0016696C size:0x30 mapped:0x807A5A00
void fn_3_16696C(void) {
    fn_800B0A5C_insertQueue(fn_3_16689C, 0xFFFA);
}

// .text:0x0016699C size:0x294 mapped:0x807A5A30
// Spawns a randomly coloured sparkle near the trail point of the current star swing.
void fn_3_16699C(void) {
    Vec p;
    Vec base;
    Mtx inv;
    ParticleParamsF prm;
    CharTrail* trail;

    memset(&p, 0, sizeof(Vec));
    memcpy(&prm, &lbl_3_data_28508, sizeof(ParticleParamsF));
    prm.tex = lbl_803CBD0C;
    p.x = 2.0f * (RANDF() - 0.5f);
    p.y = 0.5f * (2.0f * (RANDF() - 0.5f));
    PSMTXInverse(fn_80052768_getCamera(0)->view, inv);
    PSMTXMultVecSR(inv, &p, &p);
    switch (g_Ball.currentStarSwing) {
    case 5:
        trail = &lbl_8036E548.trail[7];
        break;
    case 6:
        trail = &lbl_8036E548.trail[7];
        break;
    case 7:
        trail = &lbl_8036E548.trail[10];
        break;
    case 8:
        trail = &lbl_8036E548.trail[11];
        break;
    case 9:
        trail = &lbl_8036E548.trail[8];
        break;
    case 10:
        trail = &lbl_8036E548.trail[9];
        break;
    default:
        trail = &lbl_8036E548.trail[0];
        break;
    }
    memcpy(&base, &trail->_04[0], sizeof(Vec));
    p.x += base.x;
    p.y += base.y;
    p.z += base.z;
    memcpy(&prm.pos, &p, sizeof(Vec));
    prm.r = rand() % 256;
    prm.g = rand() % 256;
    prm.b = rand() % 256;
    fn_80026998(&prm);
}

// .text:0x00166C30 size:0x110 mapped:0x807A5CC4
// Spawns a randomly coloured sparkle at the given joint of actor (joint 4 if it has none).
void fn_3_166C30(CharActor* actor, s8 joint) {
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

// Inline copy of fn_3_166C30.
static inline void spawnSparkleAt(CharActor* actor, s8 joint) {
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

// .text:0x00166D40 size:0xC4 mapped:0x807A5DD4
void fn_3_166D40(void) {
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
    q = task->actor;
    anim = task->actor->anim[0];
    if (anim == 0x1B || anim == 0x1A) {
        q = &g_Ball;
        if (g_Ball.ballState == 0) {
            fn_3_16699C();
            task->done = TRUE;
            return;
        }
    }
    if (task->done) {
        fn_800B0A14_removeQueue(q);
    }
}

// .text:0x00166E04 size:0x1C8 mapped:0x807A5E98
void fn_3_166E04(void) {
    SparkleTask* task = lbl_803CC1B8;
    void* q;
    s16 anim;
    s8 joint;

    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    anim = task->actor->anim[0];
    if (anim == 0x22 || (g_Ball.ballState == 1 && (anim == 5 || anim == 7))) {
        joint = (s8)lbl_3_data_28558[(u32)rand() % 23];
        spawnSparkleAt(task->actor, joint);
    } else {
        // removeQueue ignores its argument; the original passes whatever is in r3.
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x00166FCC size:0x1AC mapped:0x807A6060
void fn_3_166FCC(void) {
    SparkleTask* task = lbl_803CC1B8;
    void* q;
    s16 anim;
    s8 joint;

    if ((q = &g_d_GameSettings, g_d_GameSettings._55 != 0) || (q = &lbl_3_common_bss_35154, lbl_3_common_bss_35154._479 != 0)) {
        fn_800B0A14_removeQueue(q);
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    anim = task->actor->anim[0];
    if (anim == 0x26 || anim == 0x27) {
        joint = (s8)lbl_3_data_28558[(u32)rand() % 23];
        spawnSparkleAt(task->actor, joint);
    } else {
        fn_800B0A14_removeQueue(task->actor);
    }
}

// .text:0x00167178 size:0x358 mapped:0x807A620C
// Bursts a ring of 20 sparkles around joint 4 of the task's actor, then ends.
void fn_3_167178(void) {
    SparkleTask* task = lbl_803CC1B8;
    Vec pos = {0.0f, 0.0f, 0.0f};
    Vec dir;
    Mtx inv;
    ParticleParamsF prm;
    u32 i;
    f32 angle;

    // removeQueue ignores its argument; the original passes whatever is in r3.
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (g_GameLogic.gameStatus != GAME_STATUS_LIVE_BALL) {
        fn_800B0A14_removeQueue(&g_GameLogic);
        return;
    }
    fn_8001B728(task->actor->index, 4, &pos);
    PSMTXInverse(fn_80052768_getCamera(0)->view, inv);
    memcpy(&prm, &lbl_3_data_28508, sizeof(ParticleParamsF));
    memcpy(&prm.pos, &pos, sizeof(Vec));
    prm.tex = lbl_803CBD0C;
    prm.size1 = prm.size0;
    for (i = 0; i < 20; i++) {
        angle = 18.0 * i;
        angle += 9.0 * (2.0 * (RANDF() - 0.5));
        angle = 0.017453292f * angle;
        dir.x = cosf_kludge(angle);
        dir.y = sinf_kludge(angle);
        dir.z = 0.0f;
        PSMTXMultVecSR(inv, &dir, &dir);
        angle = 0.03f * (2.0 * (RANDF() - 0.5)) + 0.1f;
        memcpy(&prm.vel, &dir, sizeof(Vec));
        prm.velScale = angle;
        prm.r = rand() % 256;
        prm.g = rand() % 256;
        prm.b = rand() % 256;
        fn_80026998(&prm);
    }
    ((void (*)(void))fn_800B0A14_removeQueue)();
}

// .text:0x001674D0 size:0x3D8 mapped:0x807A6564
// While the actor's swing animation (0x1A/0x1B) runs before the ball is hit, puffs five
// sparkles around joint 0x2F, pushed further out each frame.
void fn_3_1674D0(void) {
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
    q = task->actor;
    anim = task->actor->anim[0];
    if (anim == 0x1B || anim == 0x1A) {
        if (g_Ball.ballState == 0) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            Vec dir;
            Vec off;
            Mtx inv;
            ParticleParamsF prm;
            u32 i;

            fn_8001B728(task->actor->index, 0x2F, &pos);
            dir.x = -1.0f * -sinf_kludge(-task->actor->rot.y);
            dir.z = -1.0f * cosf_kludge(-task->actor->rot.y);
            dir.y = -g_Ball.AtBat_Contact_BallPos.y - pos.y;
            dir.x = 5.0f * dir.x * (task->_18 / 10.0f);
            dir.z = 5.0f * dir.z * (task->_18 / 10.0f);
            dir.y = dir.y * (task->_18 / 10.0f);
            PSVECAdd(&dir, &pos, &dir);
            memcpy(&prm, &lbl_3_data_28508, sizeof(ParticleParamsF));
            prm.tex = lbl_803CBD0C;
            PSMTXInverse(fn_80052768_getCamera(0)->view, inv);
            for (i = 0; i < 5; i++) {
                off.x = 0.5f * (2.0f * (RANDF() - 0.5f));
                off.y = 0.5f * (2.0f * (RANDF() - 0.5f));
                off.z = 0.0f;
                PSMTXMultVecSR(inv, &off, &off);
                PSVECAdd(&off, &dir, &off);
                memcpy(&prm.pos, &off, sizeof(Vec));
                prm.r = rand() % 256;
                prm.g = rand() % 256;
                prm.b = rand() % 256;
                fn_80026998(&prm);
            }
        } else {
            fn_800B0A14_removeQueue(&g_Ball);
        }
        task->done = TRUE;
        task->_18++;
        return;
    }
    if (task->done) {
        fn_800B0A14_removeQueue(q);
    }
}

// .text:0x001678A8 size:0x41C mapped:0x807A693C
void fn_3_1678A8(void) {
    return;
}
