#include "main/file_80022DAC.h"

// "Display object id %d is greater than number of objects %d\n" at +0x0,
// "objinit.c" at +0x3C, "Incorrect number of bones in actor" at +0x48.
extern char lbl_800E6698[];
extern Vec lbl_800E6708; // {1, 0, 0}
extern Vec lbl_800E6714; // {0, 1, 0}
// Stadium lights, one row per stadium (lbl_800F7478; viewed as StadiumLights in file_80011640.h).
typedef struct StadiumLightSet {
    /* 0x00 */ StadiumLight light[4];
    /* 0x28 */ GXColor ambient;
} StadiumLightSet; // size: 0x2C

extern u8* lbl_8017EB40[0x1C];
extern u8* lbl_8017EBB0[];
extern u32 lbl_803CBC58;
extern u32 lbl_803CBC5C;
extern u32 lbl_803CBC60;
extern const f32 lbl_803CC560; // 0.0f
extern const f32 lbl_803CC564; // 1.0f
extern const f32 lbl_803CC568; // 3.1415925f
extern const f32 lbl_803CC56C; // 2048.0f
#ifdef TARGET_PC
#include "main/file_80011640.h" // CharMgr lbl_8036E548
#else
extern u8 lbl_8036E548[]; // TODO type
#endif

// TODO: these belong in their own units' headers.
void* _OSAllocFromHeap(u32 align, u32 size);
#ifdef TARGET_PC
#define ActorObjectInitTable(count) ((ActorSlotTable*)ActorObjectInitTable(count)) // ActorObjectTable* (file_800BD8C4.h)
#else
ActorSlotTable* ActorObjectInitTable(u16 count);
#endif
void fn_800B4724(MActor* actor, struct sHdr* skHeader); // GameActor* in main/file_800B2C44.h
void fn_800A7E00(void);
void OSReport(const char* msg, ...);
void OSPanic(const char* file, int line, const char* msg, ...);
void OSSetProgressiveMode(u32 on);
void* memset(void* dst, int c, size_t n);
void* memcpy(void* dst, const void* src, size_t n);
// ACTSort and DOSetWorldMatrix are declared in C3/ with the SDK's Actor/DODisplayObj layouts.

// Sizes of the per-actor bump buffers. MDisplayObj and the actor/bone
// structs hold pointers: bigger on PC.
#ifdef TARGET_PC
#define MDISPLAYOBJ_ALLOC ((sizeof(MDisplayObj) + 0x1F) & ~0x1F)
#define ACTOR_BUFFER_SMALL (0x1BC0 * 2)
#define ACTOR_BUFFER_LARGE (0x86A0 * 2)
#else
#define MDISPLAYOBJ_ALLOC 0x80
#define ACTOR_BUFFER_SMALL 0x1BC0
#define ACTOR_BUFFER_LARGE 0x86A0
#endif

// Bump allocator over a caller-supplied buffer.
typedef struct BufferCursor {
    u8* ptr;
} BufferCursor;

static inline u8* allocBuffer(BufferCursor* cursor, u32 size) {
    u8* p = cursor->ptr;
    *(u8**)cursor += size; // through a cast: keeps the cursor in memory, as in the original
    return p;
}

// Set up the display object `id` of `pal` in `buffer`; returns the end of what it used.
static inline u8* loadDisplayObj(MDisplayObj** dispObj, DODisplayData* pal, u16 id, u8* buffer) {
    BufferCursor cursor;
    MDisplayLayout* layout;

    cursor.ptr = buffer;
    if (id >= pal->numDescriptors) {
        OSReport(lbl_800E6698, id, pal->numDescriptors);
        *dispObj = NULL;
        return buffer;
    }
    layout = (MDisplayLayout*)PTR32_GET(DODisplayLayout, PTR32_GET(DODescriptor, pal->descriptorArray)[id].layout);
    *dispObj = (MDisplayObj*)allocBuffer(&cursor, MDISPLAYOBJ_ALLOC);
    cursor.ptr = fn_80023078(*dispObj, layout, cursor.ptr);
    return cursor.ptr;
}

// .text:0x80022DAC size:0x2CC
u8* f_InitBone(MBone* parent, MBoneLayout* layout, MActor* actor, u16* boneIndex, MBone* bones, u8* buffer) {
    MBone* bone;

    while (layout != NULL) {
        bone = &bones[*boneIndex];
        bone->branch.Children = NULL;
        DSInsertBranchBelow(&actor->hierarchy, (Ptr)parent, (Ptr)bone);
        actor->boneArray[*boneIndex] = bone;
        bone->boneID = layout->boneID;
        bone->inheritanceFlag = layout->inheritanceFlag;
        bone->drawingPriority = layout->drawingPriority;
        bone->orientationCtrl.ctrl.type = 0;
        if (layout->orientationCtrl != NULL) {
            bone->orientationCtrl = *PTR32_GET(MControl, layout->orientationCtrl);
        }
        bone->dispObj = NULL;
        if (layout->geoFileID != 0xFFFF) {
            buffer = loadDisplayObj(&bone->dispObj, actor->pal, layout->geoFileID, buffer);
        }
        bone->drawObj = bone->dispObj;
        bone->anim = NULL;
        bone->unk60 = 0;
        bone->unkA4 = 0;
        bone->anim = (MBoneAnim*)buffer;
        buffer += 0x20;
        bone->anim->time = lbl_803CC560;
        bone->anim->unk4 = lbl_803CC560;
        bone->anim->speed = lbl_803CC564;
        bone->anim->track = NULL;
        bone->anim->unk10 = NULL;
        bone->anim->unk16 = 0;
        bone->anim->unk17 = 1;
        bone->anim->unk18 = 1;
        bone->anim->unk14 = 0;
        bone->unk134 = 1;
        bone->unk136 = 0;
        bone->unk137 = 0;
        bone->forwardMtx = actor->forwardMtxArray[*boneIndex];
        PSMTXIdentity(bone->forwardMtx);
        if (actor->skinObject != NULL) {
            bone->skinMtx = actor->skinMtxArray[*boneIndex];
            PSMTXIdentity(bone->skinMtx);
            bone->orientationInvMtx = actor->orientationInvMtxArray[*boneIndex];
            PSMTXIdentity(bone->orientationInvMtx);
            if (actor->skinObject->lightingData != NULL) {
                bone->skinInvTransposeMtx = actor->skinInvTransposeMtxArray[*boneIndex];
                PSMTXIdentity(bone->skinInvTransposeMtx);
            } else {
                bone->skinInvTransposeMtx = NULL;
            }
        } else {
            bone->skinMtx = NULL;
            bone->orientationInvMtx = NULL;
            bone->skinInvTransposeMtx = NULL;
        }
        (*boneIndex)++;
        if (layout->branch.Children != NULL) {
            buffer = f_InitBone(bone, PTR32_GET(MBoneLayout, layout->branch.Children), actor, boneIndex, bones, buffer);
        }
        layout = PTR32_GET(MBoneLayout, layout->branch.Next);
    }
    return buffer;
}

// .text:0x80023078 size:0x268
u8* fn_80023078(MDisplayObj* dispObj, MDisplayLayout* layout, u8* buffer) {
    BufferCursor cursor;
    u16 i;

    cursor.ptr = buffer;
    if (layout->positionData != NULL) {
        dispObj->positionData = (PositionData*)allocBuffer(&cursor, 0x20);
        *dispObj->positionData = *layout->positionData;
    } else {
        dispObj->positionData = NULL;
    }
    if (layout->colorData != NULL) {
        dispObj->colorData = (ColorData*)allocBuffer(&cursor, 0x20);
        *dispObj->colorData = *layout->colorData;
    } else {
        dispObj->colorData = NULL;
    }
    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        s32 count;
        dispObj->textureData = (TextureData*)cursor.ptr;
        count = layout->numTextureChannels;
        dispObj->numTextureChannels = count;
        allocBuffer(&cursor, (count * sizeof(TextureData) + 0x1F) & ~0x1F);
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = layout->textureData[i];
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }
    if (layout->lightingData != NULL) {
        dispObj->lightingData = (LightingData*)allocBuffer(&cursor, 0x20);
        *dispObj->lightingData = *layout->lightingData;
    } else {
        dispObj->lightingData = NULL;
    }
    if (layout->displayData != NULL) {
        dispObj->displayData = (DisplayData*)allocBuffer(&cursor, 0x20);
        *dispObj->displayData = *layout->displayData;
    } else {
        dispObj->displayData = NULL;
    }
    dispObj->visibility = 1;
    PSMTXIdentity(dispObj->worldMatrix);
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    dispObj->unk15 = layout->unk15;
    memcpy(&dispObj->colors[1], &layout->colors[1], sizeof(GXColor));
    memcpy(&dispObj->colors[0], &layout->colors[0], sizeof(GXColor));
    memcpy(&dispObj->colors[3], &layout->colors[3], sizeof(GXColor));
    memcpy(&dispObj->colors[2], &layout->colors[2], sizeof(GXColor));
    memcpy(&dispObj->colors[5], &layout->colors[5], sizeof(GXColor));
    memcpy(&dispObj->colors[4], &layout->colors[4], sizeof(GXColor));
    return cursor.ptr;
}

// .text:0x800232E0 size:0x32C
// NONMATCHING 80%: the original keeps the skin object pointer in a stack slot and the string table
// (lbl_800E6698) in a saved register, and has a 0x110 frame; logic and calls are the same.
#if NONMATCHING
MActor* f_InitActorWithLayout(MActorLayout* layout, u8* buffer) {
    u16 boneCount;
    Mtx identity;
    MDisplayObj* skin;
    MActor* actor;
    s32 ptrArraySize;
    s32 mtxArraySize;
    s32 skinMtxSize = 0;
    s32 orientationInvSize = 0;
    s32 invTransposeSize = 0;
    u32 i;
    s32 normalOffset;
    DODescriptor* desc;
    PositionData* positionData;

    boneCount = 0;
    ptrArraySize = (layout->totalBones * sizeof(MBone*) + 0x1F) & ~0x1F;
    mtxArraySize = (layout->totalBones * sizeof(Mtx) + 0x1F) & ~0x1F;
    if (layout->skinFileID != 0xFFFF) {
        buffer = loadDisplayObj(&skin, PTR32_GET(DODisplayData, layout->pal), layout->skinFileID, buffer);
        skinMtxSize = orientationInvSize = (layout->totalBones * sizeof(Mtx) + 0x1F) & ~0x1F;
        if (skin->lightingData != NULL) {
            invTransposeSize = skinMtxSize;
        }
    }
    actor = (MActor*)buffer;
    actor->boneArray = (MBone**)((u8*)actor + sizeof(MActor));
    actor->forwardMtxArray = (Mtx*)((u8*)actor->boneArray + ptrArraySize);
    actor->skinObject = skin;
    actor->unk7C = 0;
    buffer = (u8*)actor + ((ptrArraySize + mtxArraySize + skinMtxSize + orientationInvSize + invTransposeSize +
                            ((layout->totalBones * sizeof(MBone) + 0x1F) & ~0x1F) + sizeof(MActor) + 0x1F) &
                           ~0x1F);
    PSMTXIdentity(identity);
    actor->actorID = layout->actorID;
    actor->layout = layout;
    actor->totalBones = layout->totalBones;
    DSInitTree(&actor->hierarchy, NULL, (DSBranchPtr)OFFSET_OF(MBone, branch));
    DSInitList(&actor->drawPriorityList, NULL, (DSLinkPtr)OFFSET_OF(MBone, drawPriorityLink));
    actor->pal = NULL;
    if (layout->pal != NULL) {
        actor->pal = PTR32_GET(DODisplayData, layout->pal);
    }
    if (layout->skinFileID != 0xFFFF) {
        DOSetWorldMatrix((struct DODisplayObj*)actor->skinObject, identity);
        actor->skinMtxArray = (Mtx*)((u8*)actor->forwardMtxArray + mtxArraySize);
        actor->orientationInvMtxArray = (Mtx*)((u8*)actor->skinMtxArray + skinMtxSize);
        // The skin's normals live right after its positions in a shared array.
        positionData = actor->skinObject->positionData;
        normalOffset = (s32)(actor->skinObject->lightingData->normalArray - positionData->positionArray);
        desc = PTR32_GET(DODescriptor, PTR32_GET(DODisplayData, layout->pal)->descriptorArray);
        for (i = 0; i < PTR32_GET(DODisplayData, layout->pal)->numDescriptors; i++, desc++) {
            PTR32(char) positions;
            if (PTR32_GET(PositionData, PTR32_GET(DODisplayLayout, desc->layout)->positionData)->compCount == 6) {
                positions = PTR32_GET(PositionData, PTR32_GET(DODisplayLayout, desc->layout)->positionData)->positionArray;
                positionData->positionArray = positions;
                actor->skinObject->lightingData->normalArray = positions + normalOffset;
                break;
            }
        }
        if (actor->skinObject->lightingData != NULL) {
            actor->skinInvTransposeMtxArray = (Mtx*)((u8*)actor->orientationInvMtxArray + orientationInvSize);
        } else {
            actor->skinInvTransposeMtxArray = NULL;
        }
    } else {
        actor->skinObject = NULL;
        actor->skinMtxArray = NULL;
        actor->orientationInvMtxArray = NULL;
        actor->skinInvTransposeMtxArray = NULL;
    }
    actor->unk1C = 0;
    if (layout->hierarchyRoot != NULL) {
        f_InitBone(NULL, PTR32_GET(MBoneLayout, layout->hierarchyRoot), actor, &boneCount,
                   (MBone*)((u8*)actor->forwardMtxArray + mtxArraySize + skinMtxSize + orientationInvSize + invTransposeSize),
                   buffer);
    }
    if (boneCount != actor->totalBones) {
        OSPanic(lbl_800E6698 + 0x3C, 0x209, lbl_800E6698 + 0x48);
    }
    if (actor->skinObject != NULL) {
        BuildBoneSkinOrientationMatrix((MBone*)actor->hierarchy.Root, identity);
    }
    ACTSort((struct GameActor*)actor);
    actor->unk80 = 0;
    actor->unk82 = 0;
    actor->unk84 = 0;
    actor->unk88 = 0;
    actor->unk8C = lbl_803CC564;
    actor->unk90 = lbl_803CC560;
    actor->unk99 = 0;
    actor->unk98 = 0;
    actor->unk94 = 0;
    return actor;
}
#endif

// .text:0x8002360C size:0x2D4
void BuildBoneSkinOrientationMatrix(MBone* bone, MtxPtr parent) {
    Mtx local;
    Mtx world;

    for (; bone != NULL; bone = (MBone*)bone->branch.Next) {
        if (bone->inheritanceFlag == 1) {
            CTRLBuildMatrix(&bone->orientationCtrl.ctrl, local);
            PSMTXConcat(parent, local, world);
            PSMTXInverse(world, bone->orientationInvMtx);
        } else {
            CTRLBuildInverseMatrix(&bone->orientationCtrl.ctrl, bone->orientationInvMtx);
        }
        if (bone->branch.Children != NULL) {
            BuildBoneSkinOrientationMatrix((MBone*)bone->branch.Children, world);
        }
    }
}

// .text:0x800238E0 size:0xBC
void fn_800238E0(ActorSlotTable* table, u16 index, s16 id, MActorLayout* layout) {
    memset(lbl_8017EB40[index], 0, lbl_803CBC58);
    layout->actorID = id;
    table->slots[index].actor = f_InitActorWithLayout(layout, lbl_8017EB40[index]);
    table->slots[index].unkE = 0;
    table->slots[index].speed = lbl_803CC564;
    table->slots[index].unk64 = 0;
    table->slots[index].unk66 = 0;
    table->slots[index].unk68 = 0;
    table->slots[index].unk6D = 0;
    table->slots[index].unk70[0] = 0;
    table->slots[index].unk70[1] = 0;
    table->slots[index].unk70[2] = 0;
    table->slots[index].unk70[3] = 0;
    table->slots[index].unk70[4] = 0;
    table->slots[index].unk70[5] = 0;
    table->slots[index].unk70[6] = 0;
    table->slots[index].unk70[7] = 0;
    table->slots[index].id = id;
    table->slots[index].unk6C = 1;
    table->slots[index].unk8 = 0;
}

// .text:0x8002399C size:0x108
// NONMATCHING 83%: the original recomputes &lbl_8017EBB0[index] after memset (6 saved regs) where we
// keep it in a register; otherwise identical.
#if NONMATCHING
void fn_8002399C(ActorSlot* slot, u16 index, s16 id, MActorLayout* layout, void* anim, struct sHdr* skin) {
    memset(lbl_8017EBB0[index], 0, lbl_803CBC5C);
    layout->actorID = id;
    slot->actor = f_InitActorWithLayout(layout, lbl_8017EBB0[index]);
    fn_800B4724(slot->actor, skin);
    slot->unkE = 0;
    slot->speed = lbl_803CC564;
    slot->unk64 = 0;
    slot->unk66 = 0;
    slot->unk68 = 0;
    slot->unk6D = 0;
    slot->unk70[0] = 0;
    slot->unk70[1] = 0;
    slot->unk70[2] = 0;
    slot->unk70[3] = 0;
    slot->unk70[4] = 0;
    slot->unk70[5] = 0;
    slot->unk70[6] = 0;
    slot->unk70[7] = 0;
    slot->id = id;
    slot->unk6C = 1;
    if (anim != NULL) {
        slot->anim = anim;
        slot->unk58 = 1;
        slot->unk5A = 1;
        slot->unk59 = 1;
        slot->unk60 = lbl_803CC560;
        if (slot->actor != NULL) {
            slot->actor->unk99 = 0;
        }
    }
    slot->unk8 = 0;
}
#endif

// .text:0x80023AA4 size:0x60
ActorSlotTable* fn_80023AA4(void) {
    u32 i;
    u8** p;

    lbl_8017EB40[0] = _OSAllocFromHeap(0x20, 0x1C * ACTOR_BUFFER_SMALL);
    p = &lbl_8017EB40[1];
    i = 1;
    do {
        i++;
        *p = p[-1] + ACTOR_BUFFER_SMALL;
        p++;
    } while (i < 0x1C);
    return ActorObjectInitTable(0x1C);
}

// .text:0x80023B04 size:0x8C
void fn_80023B04(s32 count) {
    s32 i;
    u8** p;

    lbl_8017EBB0[0] = _OSAllocFromHeap(0x20, count * ACTOR_BUFFER_LARGE);
    p = &lbl_8017EBB0[1];
    i = 1;
    do {
        i++;
        *p = p[-1] + ACTOR_BUFFER_LARGE;
        p++;
    } while (i < count);
    lbl_803CBC5C = ACTOR_BUFFER_LARGE;
#ifdef TARGET_PC
    lbl_8036E548.slots = (ActorObjectTable*)ActorObjectInitTable(0xD);
#else
    *(ActorSlotTable**)(lbl_8036E548 + 0x60) = ActorObjectInitTable(0xD); // TODO type
#endif
}

// .text:0x80023B90 size:0x164
void fn_80023B90(StadiumLight* light, StadiumLightPos* out) {
    Mtx m;
    Mtx rot;
    Vec axis = lbl_800E6708;
    Vec pos = lbl_800E6714;

    PSMTXRotAxisRad(rot, &axis, lbl_803CC568 * light->yaw / lbl_803CC56C);
    PSMTXConcat(m, rot, m);
    PSMTXRotAxisRad(m, &pos, lbl_803CC568 * (light->pitch + 0x800) / lbl_803CC56C);
    PSMTXConcat(m, rot, m);
    pos.y = light->height;
    PSMTXMultVec(m, &pos, &pos);
    out->x = pos.x;
    out->y = pos.y;
    out->z = pos.z;
    out->r = light->r;
    out->g = light->g;
    out->b = light->b;
}

// .text:0x80023CF4 size:0x48
void fn_80023CF4(u32 progressive) {
    if (progressive) {
        OSSetProgressiveMode(1);
        fn_800A7E00();
    } else {
        OSSetProgressiveMode(0);
    }
    lbl_803CBC60 = progressive;
}

// fn_80023EEC, size:0x20
void fn_80023EEC(VecQueue* queue, Vec* entries, s32 capacity) {
    queue->entries = entries;
    queue->capacity = capacity;
    queue->count = 0;
    queue->head = 0;
    queue->tail = 0;
    queue->step = 0;
}

// fn_80023D4C, size:0x4C
s32 fn_80023D4C(VecQueue* queue, Vec* result) {
    if (queue->count != 0) {
        queue->cursor = queue->tail;
        *result = queue->entries[queue->cursor];
        return 1;
    }
    return 0;
}

// fn_80023DFC, size:0x4C
s32 fn_80023DFC(VecQueue* queue, Vec* result) {
    if (queue->count != 0) {
        queue->cursor = queue->head;
        *result = queue->entries[queue->cursor];
        return 1;
    }
    return 0;
}

// fn_80023D3C, size:0x8
u32 fn_80023D3C(void) {
    return lbl_803CBC60;
}

// fn_80023D44, size:0x8
void fn_80023D44(u32 value) {
    lbl_803CBC60 = value;
}

// fn_80023E48, size:0xA4
void fn_80023E48(VecQueue* queue, Vec* value) {
    queue->head = (queue->head + queue->step) % queue->capacity;
    if (queue->tail == queue->head) {
        queue->tail = (queue->tail + queue->step) % queue->capacity;
    }
    queue->step = 1;
    queue->entries[queue->head] = *value;
    queue->count += queue->count < queue->capacity;
}

static inline s32 VecQueueLastIndex(s32 capacity) {
    return capacity - 1;
}

// fn_80023D98, size:0x64
s32 fn_80023D98(VecQueue* queue, Vec* result) {
    s32 cursor = queue->cursor;
    if (cursor == queue->tail) {
        return 0;
    }
    queue->cursor = (cursor + VecQueueLastIndex(queue->capacity)) % queue->capacity;
    *result = queue->entries[queue->cursor];
    return 1;
}

// .text:0x80023F0C size:0x278
// Copy a srcX/srcY/width/height block of texels from src to dstX/dstY in dst
// (whole GX tiles only). Returns 1 if the formats can't be copied.
s32 fn_80023F0C(TexImage* src, TexImage* dst, s32 srcX, s32 srcY, s32 width, s32 height, s32 dstX, s32 dstY) {
    s32 format;
    s32 srcStride;
    s32 dstStride;
    u8* srcRow;
    u8* dstRow;

    if (src->format != dst->format) {
        return 1;
    }
    format = src->format;
    if (src->tlut != NULL) {
        switch (format) {
        case GX_TF_C4:
            srcStride = (src->width + 7) / 8;
            dstStride = (dst->width + 7) / 8;
            width = (width + 7) / 8 + ((srcX & 7) != 0);
            srcX /= 8;
            height = (height + 7) / 8 + ((srcY & 7) != 0);
            srcY /= 8;
            dstX /= 8;
            dstY /= 8;
            break;
        case GX_TF_C8:
            srcStride = (src->width + 7) / 8;
            dstStride = (dst->width + 7) / 8;
            width = (width + 7) / 8 + ((srcX & 7) != 0);
            srcX /= 8;
            height = (height + 3) / 4 + ((srcY & 3) != 0);
            srcY /= 4;
            dstX /= 8;
            dstY /= 4;
            break;
        case GX_TF_C14X2:
            return 1;
        }
    } else {
        switch (format) {
        case GX_TF_CMPR:
            srcStride = (src->width + 7) / 8;
            dstStride = (dst->width + 7) / 8;
            width = (width + 7) / 8 + ((srcX & 7) != 0);
            srcX /= 8;
            height = (height + 7) / 8 + ((srcY & 7) != 0);
            srcY /= 8;
            dstX /= 8;
            dstY /= 8;
            break;
        default:
            return 1;
        }
    }
    srcRow = src->data + (srcX + srcStride * srcY) * 32;
    dstRow = dst->data + (dstX + dstStride * dstY) * 32;
    for (; height != 0; height--) {
        memcpy(dstRow, srcRow, width * 32);
        srcRow += srcStride * 32;
        dstRow += dstStride * 32;
    }
    return 0;
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x800F7478..0x800F76E0
StadiumLightSet lbl_800F7478[14] = {
    {
        {
            {200, 1775, 3719, 255, 255, 228},
            {200, 1315, 646, 150, 140, 130},
            {200, 1098, 2628, 88, 88, 88},
            {200, 339, 1537, 33, 66, 45},
        },
        {100, 114, 108, 255},
    },
    {
        {
            {200, 1426, 144, 104, 127, 174},
            {200, 1238, 1027, 110, 52, 23},
            {200, 827, 2712, 111, 64, 52},
            {200, 269, 391, 27, 60, 104},
        },
        {70, 78, 82, 255},
    },
    {
        {
            {200, 1516, 714, 255, 255, 216},
            {200, 1282, 1073, 176, 144, 90},
            {200, 720, 3074, 40, 53, 43},
            {200, 342, 579, 106, 101, 36},
        },
        {108, 92, 106, 255},
    },
    {
        {
            {200, 1583, 901, 255, 255, 232},
            {200, 1064, 646, 61, 63, 62},
            {200, 1098, 3069, 78, 83, 86},
            {200, 339, 1537, 45, 99, 59},
        },
        {102, 104, 99, 255},
    },
    {
        {
            {200, 1411, 2274, 255, 255, 228},
            {200, 1449, 528, 59, 55, 50},
            {200, 1161, 3437, 87, 88, 88},
            {200, 339, 1537, 36, 115, 46},
        },
        {122, 122, 120, 255},
    },
    {
        {
            {200, 1700, 1005, 245, 252, 255},
            {200, 872, 3632, 16, 46, 14},
            {200, 687, 466, 66, 82, 100},
            {200, 1074, 2432, 12, 36, 24},
        },
        {80, 78, 86, 255},
    },
    {
        {
            {200, 1775, 3719, 255, 255, 228},
            {200, 1315, 646, 150, 140, 130},
            {200, 1098, 2628, 88, 88, 88},
            {200, 339, 1537, 33, 66, 45},
        },
        {110, 100, 90, 255},
    },
    {
        {
            {200, 1626, 2653, 122, 136, 125},
            {200, 1401, 1158, 72, 89, 101},
            {200, 568, 3455, 48, 61, 56},
            {200, 579, 1496, 58, 58, 51},
        },
        {93, 100, 98, 255},
    },
    {
        {
            {200, 1426, 144, 104, 127, 174},
            {200, 1238, 1027, 110, 52, 23},
            {200, 827, 2712, 111, 64, 52},
            {200, 269, 391, 27, 60, 104},
        },
        {70, 78, 82, 255},
    },
    {
        {
            {200, 1506, 254, 255, 255, 224},
            {200, 1282, 1073, 176, 144, 90},
            {200, 720, 3074, 56, 70, 60},
            {200, 342, 579, 106, 101, 36},
        },
        {128, 108, 118, 255},
    },
    {
        {
            {200, 1583, 901, 255, 255, 232},
            {200, 1064, 646, 61, 63, 62},
            {200, 1098, 3069, 78, 83, 86},
            {200, 339, 1537, 45, 99, 59},
        },
        {102, 104, 99, 255},
    },
    {
        {
            {200, 1411, 2274, 255, 255, 228},
            {200, 1449, 528, 59, 55, 50},
            {200, 1161, 3437, 87, 88, 88},
            {200, 339, 1537, 36, 115, 46},
        },
        {122, 122, 120, 255},
    },
    {
        {
            {200, 1700, 594, 252, 255, 255},
            {200, 872, 3632, 16, 46, 14},
            {200, 687, 466, 72, 82, 92},
            {200, 1074, 2432, 12, 36, 24},
        },
        {84, 82, 90, 255},
    },
    {
        {
            {200, 1775, 3719, 255, 255, 228},
            {200, 1315, 646, 150, 140, 130},
            {200, 1098, 2628, 88, 88, 88},
            {200, 339, 1537, 33, 66, 45},
        },
        {110, 100, 90, 255},
    },
};

// .bss 0x8017EB40..0x8017EC00 (MWCC lays these out in reverse definition order)
u8* lbl_8017EBB0[];
u8* lbl_8017EB40[0x1C];

// .sbss 0x803CBC58..0x803CBC68 (MWCC lays these out in reverse definition order)
u32 lbl_803CBC60;
u32 lbl_803CBC5C;
u32 lbl_803CBC58;

