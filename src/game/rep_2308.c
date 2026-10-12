#include "game/rep_2308.h"
#define REP_HEADER_FN repHeader_2308
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "game/rep_1F58.h"
#include "game/rep_3AE8.h"
#include "static/UnknownHomes_Static.h"

extern Rep2308Bss35154 lbl_3_common_bss_35154;
extern s32 lbl_3_data_17D08[2];
extern Rep2308Task* lbl_3_data_17D10[2];
#include "Dolphin/mtx.h"
#include "stl/fdlibm.h"
extern void* memcpy(void*, const void*, u32);

#include "C3/actor.h"                // ACTSetAnimation
#include "main/file_80008E00.h"     // lbl_80366158
#include "main/file_80011640.h"     // CharMgr lbl_8036E548
#include "main/file_8004C5F8.h"     // fn_8005268C, fn_80052734
#include "main/file_800B4A44.h"     // fn_800B4C04, fn_800B4CA0

extern Rep2308Task* lbl_803CC1B8;
extern u8 lbl_803CBBC0;
extern void fn_800A7D4C(int, void*);

extern R2308 lbl_3_data_17D18[];

// .text:0x000CB284 size:0xC0 mapped:0x8070A318
void fn_3_CB284(int a, int c, f32 f) {
    CharActor* p;
    Rep2308Bss35154* b;
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        b = &lbl_3_common_bss_35154;
        if (b->_467 != 0 && c == 0x23) {
            p = lbl_8036E548.active[a];
            b->pos.x = p->pos.x;
            b->pos.y = -p->pos.y;
            b->pos.z = p->pos.z;
            b->flags |= 0x10;
        }
        ((void (*)(int, int, f32, f32))fn_3_C1344)(a, c == 0x1E, 100.0f * f, 100.0f);
    }
}

// .text:0x000CB234 size:0x50 mapped:0x8070A2C8
void fn_3_CB234(int a, int b) {
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        ((void (*)(int, int))fn_3_C11CC)(a, b);
    }
}

// .text:0x000CB1B0 size:0x84 mapped:0x8070A244
void fn_3_CB1B0(int a, u8 b, int c) {
    CharActor* p;
    if (g_d_GameSettings.GameModeSelected != 7 || (g_Minigame.GameMode_MiniGame != 1 && g_Minigame.GameMode_MiniGame != 3)) {
        if (c == 0x23) {
            lbl_3_common_bss_35154._467 = b;
            p = lbl_8036E548.active[a];
            lbl_3_common_bss_35154.pos.x = p->pos.x;
            lbl_3_common_bss_35154.pos.y = -p->pos.y;
            lbl_3_common_bss_35154.pos.z = p->pos.z;
            lbl_3_common_bss_35154.flags |= 0x10;
        }
    }
}

// .text:0x000CAF9C size:0x214 mapped:0x8070A030
void fn_3_CAF9C(void) {
    Vec a;
    Vec b;
    Vec c;
    Rep2308Task* q;
    s32 n;
    s32 i;
    Rep2308Task** slot;
    q = fn_800B0A5C_insertQueue(fn_3_CAE00, 1);
    q->frame = 0;
    q->actor = g_Pitcher.rosterID;
    memcpy(&a, &g_Pitcher, 0xC);
    memcpy(&b, &g_Pitcher.ballVelocity, 0xC);
    memcpy(&c, &g_Pitcher.pitchCurveVeloV1, 0xC);
    n = lbl_3_data_17D08[1];
    while (n-- != 0) {
        ((void (*)(Vec*, Vec*, Vec*, int))fn_3_15C024)(&a, &b, &c, 0);
    }
    q->pos.x = a.x;
    q->pos.y = -a.y;
    q->pos.z = a.z;
    a.x = a.x - g_Pitcher.ballCurrentPosition.x;
    a.y = a.y - g_Pitcher.ballCurrentPosition.y;
    a.z = a.z - g_Pitcher.ballCurrentPosition.z;
    a.y = -a.y;
    PSVECNormalize(&a, &a);
    b.x = (-1.0f); b.y = 0.0f; b.z = 0.0f;
    PSVECCrossProduct(&b, &a, &q->rot.axis);
    q->rot.q.w = acos(PSVECDotProduct(&b, &a)) / 2.0;
    if (PSVECMag(&q->rot.axis)) {
        PSVECNormalize(&q->rot.axis, &q->rot.axis);
        PSVECScale(&q->rot.axis, sin(q->rot.q.w), &q->rot.axis);
    }
    q->rot.q.w = cos(q->rot.q.w);
    q->done = i = 0;
    slot = lbl_3_data_17D10;
    for (; i < 2; slot++, i++) {
        if (*slot == 0) {
            lbl_3_data_17D10[i] = q;
            q->slot = i;
            break;
        }
    }
}

// .text:0x000CAE00 size:0x19C mapped:0x80709E94
void fn_3_CAE00(void) {
    Rep2308Task* p = lbl_803CC1B8;
    CharActor* t = lbl_8036E548.active[p->actor];
    if (p->done == 0 && t != 0) {
        fn_800A7D4C(0, &lbl_3_data_17D18[p->slot].e[lbl_803CBBC0]);
        lbl_3_data_17D18[p->slot].e[lbl_803CBBC0].frame = p->frame;
        lbl_3_data_17D18[p->slot].e[lbl_803CBBC0].pos.x = p->pos.x;
        lbl_3_data_17D18[p->slot].e[lbl_803CBBC0].pos.y = p->pos.y;
        lbl_3_data_17D18[p->slot].e[lbl_803CBBC0].pos.z = p->pos.z;
        {
            E2308* e = &lbl_3_data_17D18[p->slot].e[lbl_803CBBC0];
            e->rot = p->rot;
        }
        if (lbl_80366158._28 == 0) {
            p->frame += 1;
        }
    } else {
        lbl_3_data_17D10[p->slot] = NULL;
        fn_800B0A14_removeQueue(lbl_3_data_17D10);
    }
    if (p->frame >= lbl_3_common_bss_35154.anim[2].state.seqs[0].hdr.length) {
        lbl_3_data_17D10[p->slot] = NULL;
        fn_800B0A14_removeQueue(lbl_3_data_17D10);
    }
}

// .text:0x000CABF0 size:0x210 mapped:0x80709C84
void fn_3_CABF0(E2308* p) {
    Mtx m;
    ShapeData* b[3];
    ShapeAnimState* a[3];
    f32 sc;
    ActorObject* r31;
    GameActor* o;
    s32 i;
    sc = (f32)lbl_3_data_17D08[0] / 100000.0f;
    r31 = &lbl_3_common_bss_35154.anim[0].table->objects[1];
    b[0] = lbl_3_common_bss_35154.anim[2].shape;
    a[0] = &lbl_3_common_bss_35154.anim[2].state;
    b[1] = lbl_3_common_bss_35154.anim[3].shape;
    a[1] = &lbl_3_common_bss_35154.anim[3].state;
    b[2] = lbl_3_common_bss_35154.anim[4].shape;
    a[2] = &lbl_3_common_bss_35154.anim[4].state;
    PSMTXQuat(m, &p->rot.q);
    PSMTXScaleApply(m, m, sc, sc, sc);
    PSMTXTransApply(m, m, p->pos.x, p->pos.y, p->pos.z);
    PSMTXConcat(((camera_803c639c_s*)fn_80052734(fn_8005268C()))->view, m, m);
    i = 2;
    do {
        ShapeAnimState* t = a[i];
        t->frame = 0.0f;
        t->keyIdx = 0;
        t->speed = p->frame;
        fn_80024DB0(t);
        // ShapeModel is fn_80024FA4's view of the GameActor that r31->actor points to.
        fn_80024FA4((ShapeModel**)&r31->actor, b[i], a[i], -1);
    } while (i-- != 0);
    r31->actor->tickFlag = 1;
    ACTSetAnimation(r31->actor, r31->animBank, NULL, r31->seqNum, 0.0f, r31->speed);
    fn_800B4CA0(r31->actor, p->frame);
    fn_800B4C04(r31->actor, 1.0f);
    fn_800BDA24(r31);
    o = r31->actor;
    o->flags = 0xFF;
    fn_800BDA94(r31, m);
}

// .data 0x17D08..0x17DC0
s32 lbl_3_data_17D08[2] = {23000, 8}; // scale (/100000), number of fn_3_15C024 steps
Rep2308Task* lbl_3_data_17D10[2] = {NULL, NULL}; // running tasks (two slots)
R2308 lbl_3_data_17D18[2] = {
    {{{NULL, fn_3_CABF0}, {NULL, fn_3_CABF0}}},
    {{{NULL, fn_3_CABF0}, {NULL, fn_3_CABF0}}},
};
s32 lbl_3_data_17DB8[2] = {3, 0}; // unreferenced
