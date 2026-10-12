#include "game/rep_3F60.h"
#include "game/UnknownHomes_Game.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "main/file_80008E00.h" // lbl_80366158
#include "main/file_800B0724.h" // scene task queue
#include "C3/actor.h"

extern EffectTask* lbl_803CC1B8; // running scene task
extern EffectAnims lbl_3_common_bss_35154;
extern u8 lbl_803CBBC0; // current frame buffer (0/1)
extern s32 fn_8005268C(void);
extern void* fn_80052734(s32 index);
extern void fn_800A7D4C(s32 list, void* node);
extern void fn_800B4C04(GameActor* actor, f32 speed);
extern void fn_800B4CA0(GameActor* actor, f32 time);
void fn_3_168A6C(EffectNode* node);

// .data lbl_3_data_285A8..28928: separate objects that the code reaches through one pooled base.
// Effect height offset per character kind, fixed point (/100000).
static s32 lbl_3_data_285A8[0x36] = {
    -250000, -250000, -250000, -200000, -200000, -200000, -250000, -240000,
    -240000, -250000, -200000, -150000, -200000, -200000, -250000, -350000,
    -200000, -250000, -200000, -200000, -250000, -200000, -200000, -200000,
    -180000, -180000, -180000, -250000, -200000, -200000, -200000, -200000,
    -200000, -250000, -250000, -250000, -250000, -180000, -280000, -200000,
    -200000, -200000, -250000, -250000, -200000, -200000, -200000, -200000,
    -250000, -250000, -250000, -250000, -250000, -250000,
};
// Fixed point (/100000): [1 + 3 * i] model offsets, [0xD..0x11] sizes/frames.
static s32 lbl_3_data_28680[0x12] = {0, 50000, 0, 0, 50000, 0, 0, 50000, 0, 0, 0, 0, 0, 300000, 100000, 300000, 100000, 300000};
static EffectNode lbl_3_data_286C8[9][2] = {
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
    {{NULL, fn_3_168A6C}, {NULL, fn_3_168A6C}},
};
// Set while an actor's effect node is queued this frame (cleared by auto_00_001690C0_text).
u8 lbl_3_data_28908[0xC] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
u8 lbl_3_data_28914[0xA] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static u16 lbl_3_data_2891E = 9;
static u16 lbl_3_data_28920 = 9;
static u16 lbl_3_data_28922 = 9;
u16 lbl_3_data_28924[2] = {0, 0}; // unused

#define FIXED(x) ((f32)(x) / 100000.0f)

// NONMATCHING 99%: only scratch registers for the two index loads and the bone pointer (r27 vs r24) differ
#if NONMATCHING
// .text:0x00168414 size:0x2F0 mapped:0x807A74A8
// Draws an effect model blended from two shape animations; bones 1-4 face the camera.
void fn_3_168414(EffectNode* node) {
    ShapeData* shapes[2];
    ShapeAnimState* states[2];
    Mtx m;
    Mtx tmp;
    ActorObject* obj;
    MtxPtr view;
    s32* ofs;
    s32 i;
    GameBone* bone;

    shapes[0] = lbl_3_common_bss_35154.anim[node->animIdx].shape;
    shapes[1] = lbl_3_common_bss_35154.anim[node->animIdx2].shape;
    states[0] = &lbl_3_common_bss_35154.anim[node->animIdx].state;
    states[1] = &lbl_3_common_bss_35154.anim[node->animIdx2].state;
    obj = &lbl_3_common_bss_35154.anim[0].table->objects[node->objIdx];
    view = ((camera_803c639c_s*)fn_80052734(fn_8005268C()))->view;
    ofs = &lbl_3_data_28680[node->ofsIdx * 3];
    PSMTXTrans(m, FIXED(ofs[1]), FIXED(ofs[2]), FIXED(ofs[3]));
    PSMTXScaleApply(m, m, node->scale, node->scale, node->scale);
    PSMTXTransApply(m, m, node->pos.x, node->pos.y, node->pos.z);
    PSMTXConcat(view, m, m);
    for (i = 0; i < 2; i++) {
        states[i]->frame = 0.0f;
        states[i]->keyIdx = 0;
        states[i]->speed = node->frame;
        fn_80024DB0(states[i]);
        // TODO type: ShapeModel is a view of the GameActor that obj->actor points to.
        fn_80024FA4((ShapeModel**)&obj->actor, shapes[i], states[i], -1);
    }
    obj->actor->tickFlag = 1;
    ACTSetAnimation(obj->actor, obj->animBank, NULL, obj->seqNum, 0.0f, obj->speed);
    fn_800B4CA0(obj->actor, node->frame + 15);
    fn_800B4C04(obj->actor, 1.0f);
    fn_800BDA24(obj);
    for (i = 0; i < obj->actor->totalBones; i++) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
            bone = obj->actor->boneArray[i];
            PSMTXConcat(view, bone->forwardMtx, tmp);
            PSMTXInverse(tmp, tmp);
            tmp[0][3] = tmp[1][3] = tmp[2][3] = 0.0f;
            PSMTXConcat(bone->forwardMtx, tmp, bone->forwardMtx);
            break;
        }
    }
    obj->actor->flags = 0xFF;
    fn_800BDA94(obj, m);
}
#endif

// .text:0x00168704 size:0x228 mapped:0x807A7798
// Queues the effect node of the task's actor (at its joint) while flag bit 1 stays set.
void fn_3_168704(void) {
    EffectTask* task = lbl_803CC1B8;
    EffectNode* node;
    CharActor* actor;
    u8 idx;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        // removeQueue ignores its argument; the original passes whatever is in r3.
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (lbl_3_data_28908[task->actor] != 0) {
        if (lbl_80366158._28 != 0) {
            lbl_3_data_28914[task->actor] &= ~1;
        }
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (!(lbl_3_data_28914[task->actor] & 2)) {
        lbl_3_data_28914[task->actor] &= ~1;
        REMOVE_QUEUE_NOARG();
        return;
    }
    lbl_3_data_28908[task->actor] = 1;
    idx = task->actor;
    actor = lbl_8036E548.active[idx];
    node = &lbl_3_data_286C8[idx][lbl_803CBBC0];
    node->draw = fn_3_168414;
    node->frame = task->frame;
    getAnimRelatedCoordinates(task->actor, lbl_3_data_28922, &node->pos);
    node->pos.y += FIXED(lbl_3_data_285A8[actor->kind]);
    node->scale = FIXED(lbl_3_data_28680[0x34 / 4]);
    node->objIdx = task->objIdx;
    node->animIdx = task->animIdx;
    node->animIdx2 = task->animIdx2;
    node->ofsIdx = task->ofsIdx;
    if (lbl_80366158._28 == 0) {
        task->frame++;
    }
    fn_800A7D4C(0, node);
    task->frame %= 60;
}

// .text:0x0016892C size:0x140 mapped:0x807A79C0
void fn_3_16892C(CharActor* actor, f32 frame, s32 b, s32 unused) {
    s32 a = actor->index;
    EffectTask* task;
    if (frame == FIXED(lbl_3_data_28680[0x40 / 4])) {
        if (!(lbl_3_data_28914[a] & 1)) {
            lbl_3_data_28914[a] |= 1;
            if (actor != NULL) {
                task = fn_800B0A5C_insertQueue(fn_3_168704, (u16)(lbl_803CC1B8->priority + 1));
                task->actor = a;
                task->frame = 0;
                task->scale = FIXED(lbl_3_data_28680[0x44 / 4]);
                task->_26 = b;
                task->ofsIdx = 3;
                task->objIdx = 5;
                task->animIdx = 8;
                task->animIdx2 = 9;
            }
        }
    }
    lbl_3_data_28914[a] |= 2;
}

// NONMATCHING 99%: r0/r4 swapped for the animIdx/objIdx loads at the top
#if NONMATCHING
// .text:0x00168A6C size:0x26C mapped:0x807A7B00
// Draws an effect model turned to face the camera.
void fn_3_168A6C(EffectNode* node) {
    Mtx m;
    Mtx tmp;
    EffectAnim* anim;
    ShapeData* shape;
    ShapeAnimState* state;
    ActorObject* obj;
    MtxPtr view;
    s32* ofs;

    anim = &lbl_3_common_bss_35154.anim[node->animIdx];
    shape = anim->shape;
    state = &anim->state;
    obj = &lbl_3_common_bss_35154.anim[0].table->objects[node->objIdx];
    view = ((camera_803c639c_s*)fn_80052734(fn_8005268C()))->view;
    ofs = &lbl_3_data_28680[node->ofsIdx * 3];
    PSMTXTrans(m, FIXED(ofs[1]), FIXED(ofs[2]), FIXED(ofs[3]));
    PSMTXInverse(view, tmp);
    tmp[0][3] = tmp[1][3] = tmp[2][3] = 0.0f;
    PSMTXConcat(tmp, m, m);
    PSMTXScaleApply(m, m, node->scale, node->scale, node->scale);
    PSMTXRotRad(tmp, 'Y', 3.1415927f);
    PSMTXConcat(tmp, m, m);
    PSMTXTransApply(m, m, node->pos.x, node->pos.y, node->pos.z);
    PSMTXConcat(view, m, m);
    state->frame = 0.0f;
    state->keyIdx = 0;
    state->speed = node->frame;
    fn_80024DB0(state);
    // TODO type: ShapeModel is a view of the GameActor that obj->actor points to.
    fn_80024FA4((ShapeModel**)&obj->actor, shape, state, -1);
    obj->actor->tickFlag = 1;
    ACTSetAnimation(obj->actor, obj->animBank, NULL, obj->seqNum, 0.0f, obj->speed);
    fn_800B4CA0(obj->actor, node->frame);
    fn_800B4C04(obj->actor, 1.0f);
    fn_800BDA24(obj);
    obj->actor->flags = 0xFF;
    fn_800BDA94(obj, m);
}
#endif

// .text:0x00168CD8 size:0x124 mapped:0x807A7D6C
void fn_3_168CD8(CharActor* actor, f32 frame, s32 unused0, s32 unused1) {
    s32 a = actor->index;
    EffectTask* task;
    if (frame == FIXED(lbl_3_data_28680[0x38 / 4]) && actor != NULL) {
        task = fn_800B0A5C_insertQueue(fn_3_168DFC, (u16)(lbl_803CC1B8->priority + 1));
        task->actor = a;
        task->frame = 0;
        task->scale = FIXED(lbl_3_data_28680[0x3C / 4]);
        getAnimRelatedCoordinates(a, lbl_3_data_28920, &task->pos);
        task->ofsIdx = 2;
        task->objIdx = 4;
        task->animIdx = 7;
    }
}

// .text:0x00168DFC size:0x1A4 mapped:0x807A7E90
// Queues the task's effect node at a fixed position until its animation has run once.
void fn_3_168DFC(void) {
    EffectTask* task = lbl_803CC1B8;
    EffectNode* node;
    u8* shown;
    u8 idx;
    CharActor* actor;

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154._479 != 0) {
        // removeQueue ignores its argument; the original passes whatever is in r3.
        REMOVE_QUEUE_NOARG();
        return;
    }
    shown = lbl_3_data_28908;
    if (shown[task->actor] != 0) {
        REMOVE_QUEUE_NOARG();
        return;
    }
    shown[task->actor] = 1;
    idx = task->actor;
    actor = lbl_8036E548.active[idx];
    node = &lbl_3_data_286C8[idx][lbl_803CBBC0];
    node->draw = fn_3_168A6C;
    node->frame = task->frame;
    node->pos.x = task->pos.x;
    node->pos.y = task->pos.y + FIXED(lbl_3_data_285A8[actor->kind]);
    node->pos.z = task->pos.z;
    node->scale = task->scale;
    node->objIdx = task->objIdx;
    node->animIdx = task->animIdx;
    node->ofsIdx = task->ofsIdx;
    if (lbl_80366158._28 == 0) {
        task->frame++;
    }
    fn_800A7D4C(0, node);
    if (task->frame >= lbl_3_common_bss_35154.anim[task->animIdx].state.seqs[0].hdr.length) {
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x00168FA0 size:0x120 mapped:0x807A8034
void fn_3_168FA0(s32 a, s32 b) {
    EffectTask* task;
    if (lbl_8036E548.active[a] != NULL) {
        task = fn_800B0A5C_insertQueue(fn_3_168DFC, (u16)(lbl_803CC1B8->priority + 1));
        task->actor = a;
        task->frame = 0;
        task->scale = FIXED(lbl_3_data_28680[0x34 / 4]);
        getAnimRelatedCoordinates(a, lbl_3_data_2891E, &task->pos);
        if (b != 0) {
            task->ofsIdx = 1;
            task->objIdx = 3;
            task->animIdx = 6;
        } else {
            task->ofsIdx = 0;
            task->objIdx = 2;
            task->animIdx = 5;
        }
    }
}
