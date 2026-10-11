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
// Menu selection state (lbl_2_bss_F410), only the fields used here.
typedef struct MenuSelect0568 {
    /*0x00*/ u8 _00[0x10];
    /*0x10*/ s32 charSel[8];  // per player: selected character
    /*0x30*/ s32 rosterSel[2]; // per team: selected roster entry
} MenuSelect0568;
extern MenuSelect0568 lbl_2_bss_F410;
extern MenuCharLoadTask* lbl_2_bss_1224;
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
extern const f32 lbl_2_rodata_5BC;
extern const f32 lbl_2_rodata_5D4;
extern const f32 lbl_2_rodata_5D8;
extern const f32 lbl_2_rodata_5DC;
extern const f32 lbl_2_rodata_5E0;
extern const f32 lbl_2_rodata_5E4;
extern const f32 lbl_2_rodata_5E8;
extern void fn_800BDA94(ActorObject* slot, MtxPtr view);
// lbl_8034E9A0 (character select state, cf. CharSelectState in main/file_800639BC.h).
typedef struct MenuRosterChar {
    /*0x00*/ u8 _00[0x24];
    /*0x24*/ s16 charId;
    /*0x26*/ u8 _26[0xA0 - 0x26];
} MenuRosterChar; // size: 0xA0
typedef struct MenuCharSelect {
    /*0x0000*/ MenuRosterChar roster[6][9];
    /*0x21C0*/ u8 _21C0[0x4701 - 0x21C0];
    /*0x4701*/ u8 _4701;
    /*0x4702*/ u8 _4702[0x4755 - 0x4702];
    /*0x4755*/ u8 _4755;
} MenuCharSelect;
extern MenuCharSelect lbl_8034E9A0;
extern MenuRosterChar inMemRoster[2][9];
extern u8* lbl_803CBBCC[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_803C66B0[];
extern u8 lbl_2_bss_100B4[];
// ARAM load descriptors of the menu character models (AssetLoadInstructions).
typedef struct MenuAssetInfo {
    /*0x0*/ u32 _0;
    /*0x4*/ u32 sizeInfo; // low 28 bits: size
    /*0x8*/ u32 diskLocation;
    /*0xC*/ u32 compressedSize;
} MenuAssetInfo;
extern MenuAssetInfo lbl_2_data_241C[];
extern u8* lbl_2_bss_1228;
extern MenuAssetInfo* lbl_2_data_277C; // part model descriptors, 6 per character
extern void* ARAMTransfer(void* instr, void* dest, u8 mode, u32 aramAddr);
extern void fn_2_14BB8(u8, s32);

#include "static/GameSettings.h"

extern void fn_800B9AA8(void* light);
extern void* fn_800B0A5C_insertQueue(void* draw, s32 priority);
extern void fn_800B0A14_removeQueue(void* unused);

extern void ACTSetAnimation(void* act, void* bank, s32 a, u16 anim, f32 frame, f32 speed);
extern void fn_800B4CA0(GameActor* model, f32 v);
extern void fn_800B4C04(GameActor* model, f32 v);
extern void fn_800B4AFC(GameActor* model, u8 loop);
extern void Set_FUN_800b2b6c(GameActor* model, void* p);
extern void fn_800BDA24(ActorObject* slot);
extern void fn_800B2B54(GameActor* model, u16 joint, s32 arg);
extern ActorObject* fn_800111D8(CharActor* actor);
extern u8 lbl_2_data_2794[];
extern void fn_80014204(s32 count);
extern ActorObjectTable* fn_80023AA4(void);
extern void fn_80023B04(s32 count);
extern void ANIMGet(void* bank);
extern void convertTextureHeader(void* textures);
extern void LoadActorLayout(void* layout);
extern void convertGeometryAndSknHeader(void* geo, void* skn);
extern void haveActLayoutPointToGeoHeader(void* layout, void* geo);
extern void fn_800BD190(void* geo, void* tex);
extern void fn_8002399C(ActorObject* slot, s32 modelIndex, u16 index, void* layout, void* bank, void* skn);
extern void fn_800B2B74(GameActor* model, u16 joint);
extern void fn_800B2BA8(GameActor* model, u16 joint, s32 a, s32 b);
extern void fn_800B2C08(GameActor* model, u16 joint);
extern void fn_800BD548(ActorObject* slot, s32 count, ...);
extern void fn_8004B7B4(CharActor* actor, ActorObject* slot);
extern Vec lbl_2_data_20F8[]; // menu actor positions
extern u8 lbl_2_data_278C[];  // part file indices (fn_800126EC), 4 per part
extern Mtx lbl_2_bss_1010C;   // menu camera view matrix
extern void fn_2_166CC(void);
extern void fn_2_16724(void);
extern void fn_2_16460(void);
// Camera returned by fn_80052768_getCamera (camera_803c639c_s), only the fields used here.
typedef struct MenuCamera0568 {
    /*0x00*/ Mtx44 proj;
    /*0x40*/ Mtx view;
} MenuCamera0568;
extern MenuCamera0568* fn_80052768_getCamera(int index);


// fn_2_190B8, size:0x24
void fn_2_190B8(ActorObject* slot) {
    fn_800B9AA8(slot->lights[0]);
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
                lbl_2_bss_1224->_1C = 0;
                lbl_2_bss_1224->state = 0;
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
    if (lbl_8034E9A0._4701 == 0) {
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
void fn_2_1937C(ActorObjectTable* list, MtxPtr view) {
    Mtx44 m;
    u16 i;
    f32 fx;
    f32 fy;
    CharActor* actor;
    ActorObject* slot;
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            slot = &list->objects[i];
            if (slot->actor != NULL && slot->animateBones != 0) {
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
        ARAMTransfer(&lbl_2_data_241C[(s8)task->charId[task->index]], task->actor->files, 0, 0);
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
                task->charId[i] = (lbl_800FE930 + lbl_80361B20[0xF4] * 6)[lbl_2_bss_F410.charSel[task->index]];
            } else {
                task->charId[i] = lbl_800FE5D4[lbl_2_bss_F410.charSel[task->index]];
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
void fn_2_190DC(ActorObjectTable* list, MtxPtr view) {
    u16 i;
    ActorObject* slot;
    u8 flags;
    for (i = 0; i < list->count; i++) {
        if (&lbl_8036E548.trail2[i] == NULL) {
            continue;
        }
        slot = &list->objects[i];
        if (slot->actor == NULL) {
            continue;
        }
        if (slot->setAnimation != 0) {
            ACTSetAnimation(slot->actor, slot->animBank, 0, slot->seqNum, 0.0f, slot->speed);
        }
        if (slot->setTime != 0) {
            fn_800B4CA0(slot->actor, slot->time);
        }
        if (slot->setSpeed != 0) {
            fn_800B4C04(slot->actor, slot->unk54);
        }
        flags = slot->visFlags;
        if (flags & 2) {
            fn_800B4AFC(slot->actor, flags & 1);
        }
        Set_FUN_800b2b6c(slot->actor, slot->boneRemap);
        if (slot->animateBones != 0) {
            fn_800BDA24(slot);
        }
        slot->actor->flags = 1;
        slot->setAnimation = 0;
        slot->setTime = 0;
        slot->setSpeed = 0;
        slot->visFlags &= 1;
    }
}

// fn_2_19224, size:0x158
void fn_2_19224(ActorObjectTable* list, MtxPtr view) {
    u16 i;
    CharActor* actor;
    ActorObject* slot;
    u8 flags;
    for (i = 0; i < list->count; i++) {
        actor = lbl_8036E548.active[i];
        if (actor == NULL || actor->mode[0] == 0) {
            continue;
        }
        slot = &list->objects[i];
        if (slot->actor == NULL) {
            continue;
        }
        if (slot->setAnimation != 0) {
            ACTSetAnimation(slot->actor, slot->animBank, 0, slot->seqNum, 0.0f, slot->speed);
        }
        if (slot->setTime != 0) {
            fn_800B4CA0(slot->actor, slot->time);
        }
        if (slot->setSpeed != 0) {
            fn_800B4C04(slot->actor, slot->unk54);
        }
        flags = slot->visFlags;
        if (flags & 2) {
            fn_800B4AFC(slot->actor, flags & 1);
        }
        Set_FUN_800b2b6c(slot->actor, slot->boneRemap);
        if (slot->animateBones != 0) {
            fn_800BDA24(slot);
        }
        slot->actor->flags = 1;
        slot->setAnimation = 0;
        slot->setTime = 0;
        slot->setSpeed = 0;
        slot->visFlags &= 1;
    }
}

// fn_2_16F78, size:0x6D0
// Sets up a menu actor once its model file has been streamed in (cf. fn_80017814).
// NONMATCHING 95%: register allocation (index copies, slot base), slot field stores not CSE'd
#if NONMATCHING
void fn_2_16F78(u8 index) {
    CharActor* actor = &lbl_8036E548.actors[index];
    void** base;
    u32* offsets;
    s32 k;
    void* tex;
    void* layout;
    void* geo;
    void* skn;
    void* bank;
    ActorObject* slot;
    ActorObject* menuSlot;
    s32 count;
    s32 i;
    s32 j;
    CharParts* parts;
    s32 animA;
    s32 animB;
    BOOL special;
    void* shape;
    ShapeAnimSet* set;

    actor->modelIndex = index;
    // The file header holds offsets that are relocated in place.
    base = actor->files;
    offsets = (u32*)base;
    for (k = 0; k < 15; k++) {
        if (actor->files[k] == NULL) {
            break;
        }
        actor->files[k] = (u8*)base + offsets[k];
    }
    tex = actor->files[0];
    layout = actor->files[1];
    geo = actor->files[2];
    skn = actor->files[3];
    convertTextureHeader(tex);
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, skn);
    haveActLayoutPointToGeoHeader(layout, geo);
    fn_800BD190(geo, tex);
    bank = actor->files[4];
    actor->banks.b[5] = bank;
    ANIMGet(actor->banks.b[5]);
    slot = fn_800111D8(actor);
    fn_8002399C(slot, index, index, layout, bank, skn);

    menuSlot = &lbl_8036E548.slots->objects[index];
    menuSlot->animBank = actor->banks.b[5];
    menuSlot->seqNum = 0;
    menuSlot->time = 0.0f;
    menuSlot->setAnimation = 1;
    menuSlot->setTime = menuSlot->setSpeed = menuSlot->animBank != NULL;
    menuSlot->speed = 0.0f;
    count = lbl_8036E548.slots->objects[index].actor->totalBones;
    memset(actor->jointIdx, 0xFF, 0x64);
    for (i = 0; i < count; i++) {
        if (lbl_8036E548.slots->objects[index].actor->boneArray[i]->boneID != 0xFFFF) {
            actor->jointIdx[lbl_8036E548.slots->objects[index].actor->boneArray[i]->boneID] = i;
        }
    }
    fn_800BD548(&lbl_8036E548.slots->objects[index], 4, lbl_8036E548.lights[0], lbl_8036E548.lights[1], lbl_8036E548.lights[2], lbl_8036E548.lights[3]);
    actor->rot.x = actor->rot.y = actor->rot.z = 0.0f;
    CTRLSetTranslation(&lbl_8036E548.slots->objects[index].worldControl.base, 0.0f, 0.0f, 0.0f);
    CTRLSetRotation(&lbl_8036E548.slots->objects[index].worldControl.base, 0.0f, 0.0f, 0.0f);
    lbl_8036E548.slots->objects[index].unk54 = 0.5f;
    lbl_8036E548.slots->objects[index].setSpeed = 1;
    fn_800B2C08(lbl_8036E548.slots->objects[index].actor, lbl_8036E548.active[index] != NULL ? lbl_8036E548.active[index]->jointIdx[4] : 0xFFFF);
    fn_8001FC4C(lbl_8036E548.active[index]);
    actor->pos.x = lbl_2_data_20F8[index].x;
    actor->pos.y = lbl_2_data_20F8[index].y;
    actor->pos.z = lbl_2_data_20F8[index].z;
    actor->_04C = 0.5f;
    actor->mode[0] = 0;
    lbl_8036E548.slots->objects[index].callback = fn_2_190B8;
    actor->model = slot->actor;
    fn_800B2B74(slot->actor, actor->jointIdx[19]);
    fn_800B2B74(slot->actor, actor->jointIdx[25]);
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2B54(actor->model, j, 0xD);
    }
    j = actor->jointIdx[3];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[2];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[1];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }
    j = actor->jointIdx[36];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
    }
    j = actor->jointIdx[46];
    if (j != 0xFFFF) {
        fn_800B2BA8(slot->actor, j, 0, 0);
        slot->actor->boneArray[(u16)j]->stepTranslation = 1;
    }

    parts = &lbl_8036E548.partsPool[actor->modelIndex];
    if (actor->files[5] != NULL) {
        actor->parts = &lbl_8036E548.partsPool[index];
        parts->part[0].files = actor->files;
        fn_800126EC(&parts->part[0], tex, lbl_2_data_278C);
        parts->part[1].files = actor->files;
        fn_800126EC(&parts->part[1], tex, lbl_2_data_278C + 4);
    }
    special = FALSE;
    if (actor->kind == 0x12 || actor->kind == 0x26 || actor->kind == 0x28 || actor->kind == 0x29) {
        special = TRUE;
    }
    if (special) {
        switch (actor->kind) {
        case 0x12:
            animA = 4;
            animB = 5;
            break;
        case 0x26:
            animA = 2;
            animB = 3;
            break;
        case 0x28:
        case 0x29:
            animA = 6;
            animB = 7;
            break;
        }
    } else {
        animA = 1;
        animB = 0;
    }
    fn_8001D180(index, animA, 1);
    fn_8001D180(index, animB, 1);
    shape = actor->files[13];
    if (shape != NULL) {
        set = actor->files[14];
        if (set != NULL) {
            fn_80025DDC(shape);
            fn_80014990(index, shape, set);
            fn_80025C58(shape, (ShapeModel**)&slot->actor);
        }
    }
    actor->parts->_CC = 1;
    actor->parts->part[1].player.state.speed = 0.5f;
    actor->parts->part[0].player.state.speed = 0.5f;
    switch (actor->kind) {
    case 2:
        fn_800638B4(actor, slot);
        break;
    case 0x13:
        actor->_25C = 1;
        fn_8004B7B4(actor, slot);
        break;
    }
    fn_2_16A98(index, 0, 1, 0, 0, 0, 0);
}
#endif

// fn_2_17648, size:0x470
// Allocates the two part file buffers of every menu actor and resets its parts state.
// NONMATCHING 97%: loop counters in different registers (`mr r4, r12` vs `li r4, 0` for the second loop)
#if NONMATCHING
void fn_2_17648(void) {
    u32 bufSize;
    s32 k;
    u32 size;
    s16* id;
    s32 n;
    s32 i;
    s32 j;
    u32 maxSize = 0;

    for (i = 0; i < 12; i++) {
        for (j = 0; j < 9; j++) {
            // Only the first roster entry is ever measured.
            if (i * 9 + j == 0x35 || j != 0) {
                goto done;
            }
            id = &lbl_8034E9A0.roster[i][j].charId;
            for (k = 0; k < 6; k++) {
                size = lbl_2_data_277C[*id + k].sizeInfo & 0x0FFFFFFF;
                if (maxSize < size) {
                    maxSize = size;
                }
            }
        }
    }
done:
    bufSize = (maxSize + 0x1F) & ~0x1F;
    lbl_2_bss_1228 = _OSAllocFromHeap(0x20, bufSize * lbl_2_bss_100B8[0x2D] * 2);
    for (n = 0; n < lbl_2_bss_100B8[0x2D]; n++) {
        lbl_8036E548.partsPool[n].part[0].files = (void**)(lbl_2_bss_1228 + bufSize * (u32)(n * 2));
        lbl_8036E548.partsPool[n].part[1].files = (void**)(lbl_2_bss_1228 + bufSize * (u32)(n * 2 + 1));
    }
    for (n = 0; n < lbl_2_bss_100B8[0x2D]; n++) {
        lbl_8036E548.partsPool[n]._CF = -1;
        lbl_8036E548.partsPool[n]._D1 = -1;
        lbl_8036E548.partsPool[n]._D0 = -1;
        lbl_8036E548.partsPool[n]._CD = 0xFF;
        lbl_8036E548.partsPool[n].tex = NULL;
        lbl_8036E548.partsPool[n]._CC = 0;
        lbl_8036E548.partsPool[n].part[0].slot = n * 2;
        lbl_8036E548.partsPool[n].part[1].slot = n * 2 + 1;
    }
}
#endif

// fn_2_17C88, size:0x250
// Allocates one model file buffer per menu actor, big enough for the largest
// character model.
void fn_2_17C88(void) {
    u32 size;
    s32 i;
    s32 j;
    u32 maxSize = 0;
    s32 n;
    u32 bufSize;

    for (i = 0; i < 12; i++) {
        for (j = 0; j < 9; j++) {
            if (i * 9 + j == 0x35) {
                goto done;
            }
            size = lbl_2_data_241C[lbl_8034E9A0.roster[i][j].charId].sizeInfo & 0x0FFFFFFF;
            if (maxSize < size) {
                maxSize = size;
            }
        }
    }
done:
    bufSize = (maxSize + 0x1F) & ~0x1F;
    lbl_8036E548.fileBuf = _OSAllocFromHeap(0x20, bufSize * lbl_2_bss_100B8[0x2D]);
    for (n = 0; n < lbl_2_bss_100B8[0x2D]; n++) {
        lbl_8036E548.actors[n].files = (void**)(lbl_8036E548.fileBuf + bufSize * (u32)n);
    }
}

// fn_2_17ED8, size:0x270
// fn_2_17C88 (inlined) plus the part slots of the menu actors.
void fn_2_17ED8(void) {
    fn_2_17C88();
    fn_80014204(lbl_2_bss_100B8[0x2D]);
    lbl_8036E548.partSlots = fn_80023AA4();
    fn_80023B04(4);
}

// fn_2_16A98, size:0x248
// Menu version of the character animation request (cf. fn_8001BA44): only the
// three menu animations (bank 5) are supported; the only caller passes anim 0
// (bank/idx are left unset for anim >= 3, as in the original).
// NONMATCHING 99%: `mr r5, r23` scheduled before `addi r3, r3, 0x68` at the parts call
#if NONMATCHING
void fn_2_16A98(s32 index, s32 anim, u8 loop, u8 b, s16 frame, u8 d, u8 blend) {
    CharActor* actor;
    ActorObject* slot;
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
        slot->animBank = bankData;
        slot->seqNum = idx;
        slot->time = 0.0f;
        slot->setAnimation = 1;
        slot->setTime = bankData != NULL;
        slot->setSpeed = bankData != NULL;
        slot->speed = speed;
    }
    if (loop != 0) {
        slot->visFlags = 3;
    } else {
        slot->visFlags = 2;
    }
    slot->time = frame * actor->_04C;
    slot->setTime = 1;
    actor->_268 = b;
}
#endif

// fn_2_18398, size:0x2B8
// Scene task: takes the next actor index off the load queue (fn_2_18650) and
// streams that character in (fn_2_18148).
// NONMATCHING 95%: register numbering/scheduling of the ring-buffer pop (magic-divide temps)
#if NONMATCHING
void fn_2_18398(void) {
    s32 index;
    MenuCharLoadTask* task;
    u8 mode;
    u8 next;
    u8 sel;

    switch ((task = lbl_803CC1B8)->state) {
    case 0:
        next = (lbl_2_bss_100B8 + 2)[*(s8*)&lbl_2_bss_100B8[1]];
        if ((s8)next == -1) {
            lbl_2_bss_100B8[0x18] = 0;
            lbl_2_bss_100B8[0x1B] = 1;
            lbl_2_bss_100B8[0x1A] = 0;
            lbl_2_bss_100B8[0x32] = 0;
            lbl_2_bss_1224 = NULL;
            ((void (*)(void))fn_800B0A14_removeQueue)(); // arg unused
            return;
        }
        task->index = next;
        ((s8*)(lbl_2_bss_100B8 + 2))[*(s8*)&lbl_2_bss_100B8[1]] = -1;
        lbl_2_bss_100B8[0x1A] = 1;
        lbl_2_bss_100B8[0x1B] = 0;
        lbl_2_bss_100B8[1] = (*(s8*)&lbl_2_bss_100B8[1] + 1) % 10;
        lbl_2_bss_100B8[task->index + 0x27] = task->index;
        task->state = 1;
        task->timer = 0;
        mode = g_d_GameSettings.GameModeSelected;
        sel = lbl_8034E9A0._4755;
        if (sel == 0) {
            if (mode == 5) {
                task->charId[task->index] = (lbl_800FE930 + lbl_80361B20[0xF4] * 6)[*(s32*)((u8*)lbl_2_bss_F410.charSel + task->index * 4)];
            } else {
                task->charId[task->index] = lbl_800FE5D4[*(s32*)((u8*)lbl_2_bss_F410.charSel + task->index * 4)];
            }
            if (task->index == 2) {
                task->index = 0;
            }
        } else if (sel == 1) {
            index = task->index;
            switch (index) {
            case 0:
            case 1:
                task->charId[index] = inMemRoster[index][lbl_2_bss_F410.rosterSel[index] - (index * 11 + 2)].charId;
                break;
            case 2:
            case 3:
                task->charId[index] = lbl_2_bss_F410.charSel[index + 2];
                break;
            }
        }
    case 1:
        fn_2_18148(task);
        if (lbl_2_bss_100B4[0] != 0 && lbl_2_bss_100B4[1] == 0) {
            lbl_2_bss_1224 = NULL;
            lbl_2_bss_100B8[0x18] = 0;
            lbl_2_bss_100B8[0x1B] = 1;
            lbl_2_bss_100B8[0x1A] = 0;
            lbl_2_bss_100B8[0x32] = 0;
            task->state = 0;
            ((void (*)(void))fn_800B0A14_removeQueue)(); // arg unused
            return;
        }
        if (lbl_2_bss_100B8[0x18] != 0) {
            lbl_2_bss_100B8[0x18] = 0;
            lbl_2_bss_100B8[0x1A] = 0;
            task->state = 0;
        }
        break;
    }
}
#endif

// fn_2_188EC, size:0x6D0
// Scene task that loads the menu characters: allocates their buffers, queues the
// character loader (fn_2_18748), then streams in the actors that were requested.
// NONMATCHING 98%: bufSize in the inlined fn_2_17C88 lives in r30 instead of r27
#if NONMATCHING
// Queues the actors that were requested for loading (cf. fn_2_16870, which is the
// same code as a separate function).
static inline void menuQueueRequested(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        if (lbl_2_bss_100B8[i + 0x14] != 0 && fn_2_18650(i)) {
            lbl_2_bss_100B8[i + 0x14] = 0;
        }
    }
    lbl_8036E548._307A = 5;
    lbl_8036E548._307C = 1;
    fn_2_16460();
    PSMTXCopy(lbl_2_bss_1010C, fn_80052768_getCamera(0)->view);
    fn_2_16CE0();
}

void fn_2_188EC(void) {
    MenuCharLoadTask* task = lbl_803CC1B8;
    MenuCharLoadTask* loader;
    s32 i;

    lbl_8036E548._307A = 0;
    lbl_8036E548._307C = 0;
    switch (task->_1C) {
    case 0:
        fn_2_166CC();
        fn_2_16724();
        fn_2_17ED8();
        fn_2_16DA8();
        task->_1C++;
        break;
    case 1:
        loader = fn_800B0A5C_insertQueue(fn_2_18748, 0);
        loader->state = 0;
        loader->_1F = 0;
        loader->index = 0;
        task->_1C++;
        break;
    case 2:
        if (lbl_2_bss_100B4[0] != 0) {
            // Wait until every actor is loaded, then drop them and finish.
            for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
                if (lbl_2_bss_100B8[i + 0x40] == 0) {
                    goto loading;
                }
            }
            for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
                lbl_8036E548.active[i] = NULL;
            }
            ((void (*)(void))fn_800B0A14_removeQueue)(); // arg unused
            return;
        }
    loading:
        if (lbl_2_bss_100B8[0x19] != 0) {
            menuQueueRequested();
        }
        break;
    }
}
#endif
