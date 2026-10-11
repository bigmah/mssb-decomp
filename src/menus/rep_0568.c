#include "menus/rep_0568.h"

#include <string.h>
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#include "main/file_80011640.h"

extern u8 lbl_2_bss_100B8[];
extern MenuCharLoadTask* lbl_803CC1B8;
extern u8 lbl_800FE930[];
extern u8 lbl_800FE5D4[];
extern u8 lbl_80361B20[];
extern u8 lbl_2_bss_F410[];
extern u8* lbl_2_bss_1224;
extern u8* lbl_2_bss_122C;
extern u8* lbl_2_data_2780[];
extern void* _OSAllocFromHeap(s32, s32);
typedef struct {
    u8* p;
    u8 pad[0x5C];
    s8 a;
    s8 b;
    u8 pad2[2];
} Ent64;
extern Ent64 lbl_2_bss_101AC[];
extern void fn_2_18398(void);
extern void fn_2_188EC(void);
extern const f32 lbl_2_rodata_5BC;
extern const f32 lbl_2_rodata_5D4;
extern const f32 lbl_2_rodata_5D8;
extern const f32 lbl_2_rodata_5DC;
extern const f32 lbl_2_rodata_5E0;
extern const f32 lbl_2_rodata_5E4;
extern const f32 lbl_2_rodata_5E8;
extern void fn_800BDA94(CharSlot* slot, MtxPtr view);
extern u8 lbl_8034E9A0[];
extern u8* lbl_803CBBCC[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_803C66B0[];
extern u8 lbl_2_bss_100B4[];
extern u8 lbl_2_data_241C[];
extern s32 ARAMTransfer(void*, int, int, int);
extern void fn_2_16F78(u8);
extern void fn_2_14BB8(u8, s32);

#include "static/UnknownHomes_Static.h"

extern void ACTSetAnimation(void* act, void* bank, s32 a, u16 anim, f32 frame, f32 speed);
extern void fn_800B4CA0(CharModel* model, f32 v);
extern void fn_800B4C04(CharModel* model, f32 v);
extern void fn_800B4AFC(CharModel* model, u8 loop);
extern void Set_FUN_800b2b6c(CharModel* model, void* p);
extern void fn_800BDA24(CharSlot* slot);
extern void fn_800B2B54(CharModel* model, u16 joint, s32 arg);
extern CharSlot* fn_800111D8(CharActor* actor);
extern u8 lbl_2_data_2794[];


// fn_2_190B8, size:0x24
void fn_2_190B8(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_2_16CE0, size:0x58
void fn_2_16CE0(void) {
    CharActor* actor;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL && actor->anim[0] == 0x6B) {
            lbl_2_bss_100B8[i + 0x40] = 1;
        }
    }
}

// fn_2_16D38, size:0x70
void fn_2_16D38(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        memset(lbl_8036E548.actors[i].files, 0, 0x5C);
    }
}

// fn_2_18650, size:0xF8
s32 fn_2_18650(s32 a) {
    s32 next = (*(s8*)&lbl_2_bss_100B8[0] + 1) % 10;
    if (next != *(s8*)&lbl_2_bss_100B8[1]) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224[0x1C] = 0;
                lbl_2_bss_1224[0x1D] = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8[*(s8*)&lbl_2_bss_100B8[0] + 2] = a;
        lbl_2_bss_100B8[0] = next;
        lbl_2_bss_100B8[a + 0x42] = 1;
        return 1;
    }
    return 0;
}

// fn_2_18FBC, size:0xFC
void fn_2_18FBC(void) {
    u8* q;
    s32 i;
    q = fn_800B0A5C_insertQueue(fn_2_188EC, 0x6000);
    lbl_2_bss_100B8[0x19] = 0;
    lbl_2_bss_100B8[0x1B] = 1;
    if (lbl_8034E9A0[0x4701] == 0) {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            ((s8*)lbl_2_bss_100B8)[i + 0x27] = -1;
        }
        q[0x1C] = 0;
    } else {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            lbl_2_bss_100B8[i + 0x14] = 0;
        }
        q[0x1C] = 0;
    }
    lbl_2_bss_100B8[0] = i = 0;
    lbl_2_bss_100B8[1] = 0;
    for (; i < 10; i++) {
        ((s8*)lbl_2_bss_100B8)[i + 2] = -1;
    }
}

// fn_2_1937C, size:0x140
void fn_2_1937C(CharSlotList* list, MtxPtr view) {
    Mtx44 m;
    u16 i;
    f32 fx;
    f32 fy;
    CharActor* actor;
    CharSlot* slot;
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            slot = &list->slots[i];
            if (slot->model != NULL && slot->_6C != 0) {
                fx = actor->pos.x / lbl_2_rodata_5D4;
                fy = actor->pos.y / lbl_2_rodata_5D4;
                C_MTXFrustum(m, lbl_2_rodata_5D8 + fy, lbl_2_rodata_5DC + fy, lbl_2_rodata_5E0 + fx, lbl_2_rodata_5E4 + fx, lbl_2_rodata_5BC, lbl_2_rodata_5E8);
                GXSetProjection(m, GX_PERSPECTIVE);
                fn_800BDA94(slot, view);
            }
        }
    }
}

// fn_2_17AB8, size:0x1D0
void fn_2_17AB8(void) {
    s32 size;
    s32 i;
    size = ((*(u32*)(lbl_2_data_2780[0] + 4) & 0x0FFFFFFF) + 0x1F) & ~0x1F;
    lbl_2_bss_122C = _OSAllocFromHeap(0x20, size * lbl_2_bss_100B8[0x2D]);
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        lbl_2_bss_101AC[i].p = lbl_2_bss_122C + size * i;
        lbl_2_bss_101AC[i].b = -1;
        lbl_2_bss_101AC[i].a = -1;
    }
}

// fn_2_18148, size:0x250
void fn_2_18148(MenuCharLoadTask* task) {
    u8 gf;
    switch (task->step) {
    case 0:
        task->actor = &lbl_8036E548.actors[task->index];
        task->actor->kind = task->charId[task->index];
        task->showFlag = lbl_2_bss_100B8[task->index + 0x46];
        lbl_8036E548.actors[task->index].mode[0] = 0;
        task->actor->_068 = -1;
        lbl_2_bss_100B4[1] = 1;
        task->step++;
        break;
    case 1:
        ARAMTransfer(lbl_2_data_241C + (s8)task->charId[task->index] * 0x10, (s32)task->actor->files, 0, 0); // TODO type: ARAM dest address
        task->step++;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            fn_2_16F78(task->index);
            gf = g_d_GameSettings._10;
            if (gf == 0 && lbl_803C66B0[0x59] == 0 && task->index == 1) {
                lbl_8036E548.actors[task->index].mode[0] = 0;
            } else {
                lbl_8036E548.actors[task->index].mode[0] = (task->showFlag != 0);
            }
            if (g_d_GameSettings.GameModeSelected == 5 || gf != 0 || *(u16*)(lbl_803CBBCC[0] + 6) == 5) {
                fn_2_14BB8(task->index, 1);
            } else if (lbl_2_bss_100B8[0x10] != 0) {
                fn_2_14BB8(task->index, task->index != 0);
            }
            task->step = 0;
            lbl_2_bss_100B8[0x32] = 1;
            lbl_2_bss_100B4[1] = 0;
            lbl_2_bss_100B8[0x18] = 1;
            lbl_2_bss_100B8[task->index + 0x42] = 0;
        }
        break;
    }
}

// fn_2_18748, size:0x1A4
void fn_2_18748(void) {
    MenuCharLoadTask* task;
    s32 i;
    switch ((task = lbl_803CC1B8)->state) {
    case 0:
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            if (g_d_GameSettings.GameModeSelected == 5) {
                task->charId[i] = (lbl_800FE930 + lbl_80361B20[0xF4] * 6)[*(s32*)(lbl_2_bss_F410 + task->index * 4 + 0x10)];
            } else {
                task->charId[i] = lbl_800FE5D4[*(s32*)(lbl_2_bss_F410 + task->index * 4 + 0x10)];
            }
            if (task->index == 2) {
                task->index = 0;
            }
        }
        task->timer = 0;
        task->step = 0;
        task->state++;
    case 1:
        fn_2_18148(task);
        if (lbl_2_bss_100B8[0x18] != 0) {
            lbl_2_bss_100B8[0x18] = 0;
            lbl_2_bss_100B8[0x32] = 0;
            task->step = 0;
            task->timer = 0;
            task->index++;
            if (task->index >= lbl_2_bss_100B8[0x2D]) {
                task->index = 0;
                task->state = 0;
                lbl_2_bss_100B8[0x19] = 1;
                ((void (*)(void))fn_800B0A14_removeQueue)(); // arg unused
            } else {
                task->state = 0;
            }
        } else if (lbl_2_bss_100B4[0] != 0) {
            task->index = 0;
            task->state = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)(); // arg unused
        }
        break;
    }
}

// fn_2_16DA8, size:0x164
void fn_2_16DA8(void) {
    s32 i;
    lbl_8036E548._3078 = 0;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        lbl_8036E548.active[i] = &lbl_8036E548.actors[i];
    }
    i = 3;
    do {
        lbl_2_bss_100B8[i + 0x42] = 0;
    } while (i-- != 0);
    if (*(u16*)(lbl_803CBBCC[0] + 6) == 5 || g_d_GameSettings.GameModeSelected == 5) {
        lbl_2_bss_100B8[0x46] = 1;
        lbl_2_bss_100B8[0x47] = 0;
        return;
    }
    lbl_2_bss_100B8[0x46] = 1;
    lbl_2_bss_100B8[0x47] = 1;
}

// fn_2_16F0C, size:0x6C
void fn_2_16F0C(u8 index) {
    CharActor* actor = &lbl_8036E548.actors[index];
    s8 kind = actor->kind;
    s8 actorIndex = actor->index;
    if (lbl_8036E548.partsPool[index]._D0 == -1) {
        lbl_8036E548.partsPool[index]._CF = kind;
        lbl_8036E548.partsPool[index]._D1 = lbl_8036E548.partsPool[index]._D0;
        lbl_8036E548.partsPool[index]._D0 = actorIndex;
        lbl_8036E548.partsPool[index]._CD = actor->_265[0];
    }
    actor->parts = &lbl_8036E548.partsPool[index];
}

// fn_2_190DC, size:0x148
void fn_2_190DC(CharSlotList* list, MtxPtr view) {
    u16 i;
    CharSlot* slot;
    u8 flags;
    for (i = 0; i < list->count; i++) {
        if (&lbl_8036E548.trail2[i] == NULL) {
            continue;
        }
        slot = &list->slots[i];
        if (slot->model == NULL) {
            continue;
        }
        if (slot->_58 != 0) {
            ACTSetAnimation(slot->model, slot->act, 0, slot->animId, 0.0f, slot->_60);
        }
        if (slot->_59 != 0) {
            fn_800B4CA0(slot->model, slot->_5C);
        }
        if (slot->_5A != 0) {
            fn_800B4C04(slot->model, slot->_54);
        }
        flags = slot->_5B;
        if (flags & 2) {
            fn_800B4AFC(slot->model, flags & 1);
        }
        Set_FUN_800b2b6c(slot->model, slot->mirror);
        if (slot->_6C != 0) {
            fn_800BDA24(slot);
        }
        slot->model->flags = 1;
        slot->_58 = 0;
        slot->_59 = 0;
        slot->_5A = 0;
        slot->_5B &= 1;
    }
}

// fn_2_19224, size:0x158
void fn_2_19224(CharSlotList* list, MtxPtr view) {
    u16 i;
    CharActor* actor;
    CharSlot* slot;
    u8 flags;
    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        slot = &list->slots[i];
        if (slot->model == NULL) {
            continue;
        }
        if (slot->_58 != 0) {
            ACTSetAnimation(slot->model, slot->act, 0, slot->animId, 0.0f, slot->_60);
        }
        if (slot->_59 != 0) {
            fn_800B4CA0(slot->model, slot->_5C);
        }
        if (slot->_5A != 0) {
            fn_800B4C04(slot->model, slot->_54);
        }
        flags = slot->_5B;
        if (flags & 2) {
            fn_800B4AFC(slot->model, flags & 1);
        }
        Set_FUN_800b2b6c(slot->model, slot->mirror);
        if (slot->_6C != 0) {
            fn_800BDA24(slot);
        }
        slot->model->flags = 1;
        slot->_58 = 0;
        slot->_59 = 0;
        slot->_5A = 0;
        slot->_5B &= 1;
    }
}

// fn_2_16A98, size:0x248
// Menu version of the character animation request (cf. fn_8001BA44): only the
// three menu animations (bank 5) are supported; the only caller passes anim 0
// (bank/idx are left unset for anim >= 3, as in the original).
// NONMATCHING 99%: `mr r5, r23` scheduled before `addi r3, r3, 0x68` at the parts call
#if NONMATCHING
void fn_2_16A98(s32 index, s32 anim, u8 loop, u8 b, s16 frame, u8 d, u8 blend) {
    CharActor* actor;
    CharSlot* slot;
    CharAnimBank* bankData;
    s32 bank;
    s32 idx;
    u8 entry;
    f32 speed = 0.0f;

    actor = lbl_8036E548.active[index];
    if (actor == NULL) {
        return;
    }
    slot = fn_800111D8(actor);
    if (blend != 0) {
        speed = 1.0f / blend;
    }
    if (actor->_26C[0] == 0) {
        fn_800B2B54(actor->model, lbl_8036E548.active[index] != NULL ? lbl_8036E548.active[index]->jointIdx[4] : 0xFFFF, 0xD);
    } else {
        fn_800B2B54(actor->model, lbl_8036E548.active[index] != NULL ? lbl_8036E548.active[index]->jointIdx[4] : 0xFFFF, 1);
    }
    if (anim < 3) {
        bank = 5;
        idx = anim;
    }
    entry = lbl_2_data_2794[idx];
    if (actor->part != NULL) {
        fn_80025EEC(&actor->part->player, 5, entry);
    }
    if (actor->parts != NULL && actor->parts->_CC != 0) {
        fn_80025EEC(&actor->parts->part[1].player, 5, entry);
        fn_80025EEC(&actor->parts->part[0].player, 5, entry);
    }
    if (index < lbl_2_bss_100B8[0x2D] && (bankData = actor->banks.b[bank]) != NULL) {
        if (idx >= bankData->count) {
            return;
        }
        slot->act = bankData;
        slot->animId = idx;
        slot->_5C = 0.0f;
        slot->_58 = 1;
        slot->_59 = bankData != NULL;
        slot->_5A = bankData != NULL;
        slot->_60 = speed;
    }
    if (loop != 0) {
        slot->_5B = 3;
    } else {
        slot->_5B = 2;
    }
    slot->_5C = frame * actor->_04C;
    slot->_59 = 1;
    actor->_268 = b;
}
#endif
