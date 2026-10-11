#include "main/file_800BD8C4.h"
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
void fn_800BD8C4(void) {
    return;
}

// .text:0x800BDA24 size:0x70
void fn_800BDA24(void) {
    return;
}

// .text:0x800BDA94 size:0x1F4
void fn_800BDA94(void) {
    return;
}

// .text:0x800BDC88 size:0xEC
void fn_800BDC88(void) {
    return;
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

extern u8 lbl_803009F8[];

// fn_800BDE8C, size:0x14
void fn_800BDE8C(u32 value) {
    lbl_803009F8[0x4C] = (value & 7) << 5;
}
