#include "main/file_800BD8C4.h"
#include "main/file_800BDEA0.h"
#include "Dolphin/os.h"
#include "Dolphin/stl.h"

extern const f32 lbl_803CD060; // 0.0f
extern const f32 lbl_803CD064; // 1.0f
extern char lbl_800E7FC8[];

void* _OSAllocFromHeap(s32 align, s32 size);
void ACTSetAnimation(ActorInst* actor, void* animBank, int seqName, u16 seqNum, f32 time, f32 speed);
void Set_FUN_800b2b6c(ActorInst* actor, s32 value);
void fn_800B2BFC(ActorInst* actor, u16 a, u16 b);
void fn_800B313C(ActorInst* actor);
s32 fn_800B3A78(ActorInst* actor, MtxPtr camera, u8 numLights, ...);
u8 fn_800B3C04(s32 arg0, ActorInst* actor, s32 arg2);
void fn_800B3F20(ActorInst* actor);
s32 fn_800B4048(ActorObject* obj, void* layout, u32 id);
void fn_800B4724(ActorInst* actor, s32 arg1);
void fn_800B4AFC(ActorInst* actor, u8 value);
void AnimateActorBones(ActorInst* actor);
void fn_800B4C04(ActorInst* actor, f32 value);
void fn_800B4CA0(ActorInst* actor, f32 time);

// .text:0x800BD8C4 size:0x160
void fn_800BD8C4(ActorObjectTable* table, s32 arg1) {
    ActorObjectTable* t;
    ActorInst* actor;
    u16 i;

    for (i = 0; i < table->count; i++) {
        // t->objects[0] is table->objects[i] (this form keeps the original codegen)
        t = (ActorObjectTable*)((u8*)table + i * sizeof(ActorObject));
        if (t->objects[0].actor == NULL) {
            continue;
        }
        if (t->objects[0].setAnimation) {
            ACTSetAnimation(t->objects[0].actor, t->objects[0].animBank, 0, t->objects[0].seqNum, lbl_803CD060, t->objects[0].speed);
        }
        if (t->objects[0].setTime) {
            fn_800B4CA0(t->objects[0].actor, t->objects[0].time);
        }
        if (t->objects[0].setSpeed) {
            fn_800B4C04(t->objects[0].actor, t->objects[0].unk54);
        }
        if (t->objects[0].visFlags & 2) {
            fn_800B4AFC(t->objects[0].actor, t->objects[0].visFlags & 1);
        }
        Set_FUN_800b2b6c(t->objects[0].actor, t->objects[0].unk68);
        if (t->objects[0].animateBones) {
            actor = t->objects[0].actor;
            memcpy(actor->worldControl, t->objects[0].worldControl, sizeof(t->objects[0].worldControl));
            fn_800B2BFC(t->objects[0].actor, t->objects[0].unk64, t->objects[0].unk66);
            AnimateActorBones(actor);
            fn_800B3F20(actor);
            fn_800B313C(actor);
        }
        actor = t->objects[0].actor;
        actor->flags98 = (actor->flags98 & 0xFC) | fn_800B3C04(0, actor, arg1);
        t->objects[0].setAnimation = 0;
        t->objects[0].setTime = 0;
        t->objects[0].setSpeed = 0;
        t->objects[0].visFlags &= 1;
    }
}

// .text:0x800BDA24 size:0x70
void fn_800BDA24(ActorObject* obj) {
    ActorInst* actor = obj->actor;

    memcpy(obj->actor->worldControl, obj->worldControl, sizeof(obj->worldControl));
    fn_800B2BFC(obj->actor, obj->unk64, obj->unk66);
    AnimateActorBones(actor);
    fn_800B3F20(actor);
    fn_800B313C(actor);
}

// .text:0x800BDA94 size:0x1F4
void fn_800BDA94(ActorObject* obj, MtxPtr camera) {
    ActorInst* actor = obj->actor;

    if (obj->callback != NULL) {
        obj->callback();
    }
    switch (obj->numLights) {
    case 0:
        fn_800B3A78(actor, camera, 0);
        break;
    case 1:
        fn_800B3A78(actor, camera, 1, obj->lights[0]);
        break;
    case 2:
        fn_800B3A78(actor, camera, 2, obj->lights[0], obj->lights[1]);
        break;
    case 3:
        fn_800B3A78(actor, camera, 3, obj->lights[0], obj->lights[1], obj->lights[2]);
        break;
    case 4:
        fn_800B3A78(actor, camera, 4, obj->lights[0], obj->lights[1], obj->lights[2], obj->lights[3]);
        break;
    case 5:
        fn_800B3A78(actor, camera, 5, obj->lights[0], obj->lights[1], obj->lights[2], obj->lights[3],
                    obj->lights[4]);
        break;
    case 6:
        fn_800B3A78(actor, camera, 6, obj->lights[0], obj->lights[1], obj->lights[2], obj->lights[3],
                    obj->lights[4], obj->lights[5]);
        break;
    case 7:
        fn_800B3A78(actor, camera, 7, obj->lights[0], obj->lights[1], obj->lights[2], obj->lights[3],
                    obj->lights[4], obj->lights[5], obj->lights[6]);
        break;
    case 8:
        fn_800B3A78(actor, camera, 8, obj->lights[0], obj->lights[1], obj->lights[2], obj->lights[3],
                    obj->lights[4], obj->lights[5], obj->lights[6], obj->lights[7]);
        break;
    }
}

// .text:0x800BDC88 size:0xEC
void fn_800BDC88(ActorObjectTable* table, u16 index, u16 id, void* layout, void* animBank, s32 arg5) {

    fn_800B4048(&table->objects[index], layout, index);
    fn_800B4724(table->objects[index].actor, arg5);
    table->objects[index].seqNum = 0;
    table->objects[index].unk54 = lbl_803CD064;
    table->objects[index].unk64 = 0;
    table->objects[index].unk66 = 0;
    table->objects[index].unk68 = 0;
    table->objects[index].numLights = 0;
    table->objects[index].lights[0] = NULL;
    table->objects[index].lights[1] = NULL;
    table->objects[index].lights[2] = NULL;
    table->objects[index].lights[3] = NULL;
    table->objects[index].lights[4] = NULL;
    table->objects[index].lights[5] = NULL;
    table->objects[index].lights[6] = NULL;
    table->objects[index].lights[7] = NULL;
    table->objects[index].id = id;
    table->objects[index].animateBones = 1;
    if (animBank != NULL) {
        table->objects[index].animBank = animBank;
        table->objects[index].setAnimation = 1;
        table->objects[index].setSpeed = 1;
        table->objects[index].setTime = 1;
        table->objects[index].speed = lbl_803CD060;
        if (table->objects[index].actor != NULL) {
            table->objects[index].actor->unk99 = 0;
        }
    }
    table->objects[index].callback = NULL;
}

// .text:0x800BDD74 size:0x118
ActorObjectTable* ActorObjectInitTable(u16 count) {
    ActorObjectTable* table;
    u16 i;

    if (count == 0) {
        OSReport(lbl_800E7FC8);
        return NULL;
    }
    table = _OSAllocFromHeap(0x20, count * sizeof(ActorObject) + 0x34);
    table->count = count;
    PSMTXIdentity(table->mtx);
    for (i = 0; i < table->count; i++) {
        table->objects[i].actor = NULL;
        table->objects[i].animBank = NULL;
        table->objects[i].callback = NULL;
        table->objects[i].seqNum = 0;
        table->objects[i].unk54 = lbl_803CD064;
        table->objects[i].time = lbl_803CD060;
        table->objects[i].speed = lbl_803CD060;
        table->objects[i].unk64 = 0;
        table->objects[i].unk66 = 0;
        table->objects[i].unk68 = 0;
        table->objects[i].numLights = 0;
        table->objects[i].lights[0] = NULL;
        table->objects[i].lights[1] = NULL;
        table->objects[i].lights[2] = NULL;
        table->objects[i].lights[3] = NULL;
        table->objects[i].lights[4] = NULL;
        table->objects[i].lights[5] = NULL;
        table->objects[i].lights[6] = NULL;
        table->objects[i].lights[7] = NULL;
        table->objects[i].id = 0;
        table->objects[i].animateBones = 0;
        table->objects[i].setAnimation = 0;
        table->objects[i].setSpeed = 0;
        table->objects[i].setTime = 0;
        table->objects[i].visFlags = 1;
        table->objects[i].worldControl[0] = 0;
        table->objects[i].id = i;
    }
    return table;
}

// fn_800BDE8C, size:0x14
void fn_800BDE8C(u32 value) {
    lbl_803009F8.flags = (value & 7) << 5;
}
