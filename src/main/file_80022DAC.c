#include "main/file_80022DAC.h"

// "Display object id %d is greater than number of objects %d\n" at +0x0,
// "objinit.c" at +0x3C, "Incorrect number of bones in actor" at +0x48.
extern char lbl_800E6698[];
extern Vec lbl_800E6708; // {1, 0, 0}
extern Vec lbl_800E6714; // {0, 1, 0}
extern u8* lbl_8017EB40[0x1C];
extern u8* lbl_8017EBB0[];
extern u32 lbl_803CBC58;
extern u32 lbl_803CBC5C;
extern u32 lbl_803CBC60;
extern const f32 lbl_803CC560; // 0.0f
extern const f32 lbl_803CC564; // 1.0f
extern const f32 lbl_803CC568; // 3.1415925f
extern const f32 lbl_803CC56C; // 2048.0f
extern u8 lbl_8036E548[]; // TODO type

// TODO: these belong in their own units' headers.
void* _OSAllocFromHeap(u32 align, u32 size);
ActorSlotTable* ActorObjectInitTable(u16 count);
void fn_800B4724(MActor* actor, u32 value);
void fn_800A7E00(void);
void OSReport(const char* msg, ...);
void OSPanic(const char* file, int line, const char* msg, ...);
void OSSetProgressiveMode(u32 on);
void* memset(void* dst, int c, u32 n);
void* memcpy(void* dst, const void* src, u32 n);
// ACTSort and DOSetWorldMatrix are declared in C3/ with the SDK's Actor/DODisplayObj layouts.

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
    layout = (MDisplayLayout*)pal->descriptorArray[id].layout;
    *dispObj = (MDisplayObj*)allocBuffer(&cursor, 0x80);
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
            bone->orientationCtrl = *layout->orientationCtrl;
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
            buffer = f_InitBone(bone, (MBoneLayout*)layout->branch.Children, actor, boneIndex, bones, buffer);
        }
        layout = (MBoneLayout*)layout->branch.Next;
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
        buffer = loadDisplayObj(&skin, layout->pal, layout->skinFileID, buffer);
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
        actor->pal = layout->pal;
    }
    if (layout->skinFileID != 0xFFFF) {
        DOSetWorldMatrix((struct DODisplayObj*)actor->skinObject, identity);
        actor->skinMtxArray = (Mtx*)((u8*)actor->forwardMtxArray + mtxArraySize);
        actor->orientationInvMtxArray = (Mtx*)((u8*)actor->skinMtxArray + skinMtxSize);
        // The skin's normals live right after its positions in a shared array.
        positionData = actor->skinObject->positionData;
        normalOffset = actor->skinObject->lightingData->normalArray - positionData->positionArray;
        desc = layout->pal->descriptorArray;
        for (i = 0; i < layout->pal->numDescriptors; i++, desc++) {
            char* positions;
            if (desc->layout->positionData->compCount == 6) {
                positions = desc->layout->positionData->positionArray;
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
        f_InitBone(NULL, layout->hierarchyRoot, actor, &boneCount,
                   (MBone*)((u8*)actor->forwardMtxArray + mtxArraySize + skinMtxSize + orientationInvSize + invTransposeSize),
                   buffer);
    }
    if (boneCount != actor->totalBones) {
        OSPanic(lbl_800E6698 + 0x3C, 0x209, lbl_800E6698 + 0x48);
    }
    if (actor->skinObject != NULL) {
        BuildBoneSkinOrientationMatrix((MBone*)actor->hierarchy.Root, identity);
    }
    ACTSort((Actor*)actor);
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
void fn_800238E0(void) {
    return;
}

// .text:0x8002399C size:0x108
void fn_8002399C(void) {
    return;
}

// .text:0x80023AA4 size:0x60
void fn_80023AA4(void) {
    return;
}

// .text:0x80023B04 size:0x8C
void fn_80023B04(void) {
    return;
}

// .text:0x80023B90 size:0x164
void fn_80023B90(void) {
    return;
}

// .text:0x80023CF4 size:0x48
void fn_80023CF4(void) {
    return;
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
void fn_80023F0C(void) {
    return;
}
