#include "main/file_800B2C44.h"

extern u32 lbl_803CC1E8; // actor->tickFlag of the actor being built
extern Mtx lbl_80111640; // extra root transform for actors with a bone remap table
extern Vec lbl_800E7D28; // {0, 0, 0}

// .text:0x800B2C44 size:0x44
void fn_800B2C44(GameActor* actor, u16 bone, Vec* pos) {
    pos->x = 0.0f;
    pos->y = 0.0f;
    pos->z = 0.0f;
    PSMTXMultVec(actor->forwardMtxArray[bone], pos, pos);
}

// .text:0x800B2C88 size:0x34
void fn_800B2C88(GameActor* actor, u16 bone, Mtx m) {
    PSMTXCopy(actor->forwardMtxArray[bone], m);
}

// .text:0x800B2CBC size:0xA0
void ACTSort(GameActor* actor) {
    u16 i;
    GameBone* bone;
    GameBone* cursor;

    actor->drawPriorityList.Head = NULL;
    actor->drawPriorityList.Tail = NULL;
    for (i = 0; i < actor->totalBones; i++) {
        bone = actor->boneArray[i];
        if (bone->dispObj == NULL) {
            continue;
        }
        cursor = (GameBone*)actor->drawPriorityList.Head;
        while (cursor != NULL) {
            if (cursor->drawingPriority > actor->boneArray[i]->drawingPriority) {
                break;
            }
            cursor = (GameBone*)cursor->drawPriorityLink.Next;
        }
        DSInsertListObject(&actor->drawPriorityList, (Ptr)cursor, (Ptr)bone);
    }
}

// .text:0x800B2D5C size:0x74
void fn_800B2D5C(GameActor* actor) {
    PositionData* pos;

    GQRSetup5(8, 4, 8, 4);
    pos = actor->skinObject->positionData;
    if (pos->quantizeInfo == 0x40) {
        SKNIt(actor->boneArray, actor->skHeader, pos->positionArray);
    } else {
        fn_800BF2A8(actor->boneArray, actor->skHeader, pos->positionArray);
    }
}

// .text:0x800B2DD0 size:0x36C
// NONMATCHING 98%: blend switch is missing a dead `b` after case 0; `mr r30,r4` scheduled differently
#if NONMATCHING
void fn_800B2DD0(GameActor* actor, GameBone* bone) {
    Mtx world; // never initialised in the original
    Mtx m;
    Mtx ctrlMtx;
    Mtx rot;
    GameControl blended;
    f32 blend;
    GameBone* parent;
    GameBone* target;
    GameBone* child;
    u16 i;

    blend = actor->blend;
    switch (bone->flags & 3) {
    case 0:
        blend = 1.0f;
        break;
    case 1:
        break;
    case 2:
        blend = blend * blend;
        break;
    default:
        blend = 1.0f;
        break;
    }

    if (bone->flags & 0x20) {
        if (bone->flags & 4) {
            bone->blendCtrl.controlParams.srt.t.x = bone->animCtrl.controlParams.srt.t.x;
        }
        if (bone->flags & 8) {
            bone->blendCtrl.controlParams.srt.t.y = bone->animCtrl.controlParams.srt.t.y;
        }
        if (bone->flags & 0x10) {
            bone->blendCtrl.controlParams.srt.t.z = bone->animCtrl.controlParams.srt.t.z;
        }
    }

    if (bone->animCtrl.type != 0) {
        if (actor->boneRemap == NULL) {
            fn_800B84AC(&bone->animCtrl, &bone->blendCtrl, &bone->animCtrl, blend);
            CTRLBuildMatrix(&bone->animCtrl, m);
        } else if (actor->boneCallback == NULL ||
                   actor->boneCallback(bone, actor->boneArray[actor->boneRemap[0]], m, blend) == 0) {
            for (i = 0; i < actor->totalBones; i++) {
                if (bone->boneID == actor->boneArray[i]->boneID) {
                    target = actor->boneArray[actor->boneRemap[i]];
                    break;
                }
            }
            fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, blend);
            if (bone->branch.Parent != NULL) {
                CTRLBuildMatrix_FlipY(&target->animCtrl, m);
            } else {
                CTRLBuildMatrix_FlipX(&target->animCtrl, m);
            }
            switch (bone->rotAxis) {
            case 1:
                PSMTXRotRad(rot, 'X', 3.1415927f);
                PSMTXConcat(m, rot, m);
                break;
            case 2:
                PSMTXRotRad(rot, 'Y', 3.1415927f);
                PSMTXConcat(m, rot, m);
                break;
            case 3:
                PSMTXRotRad(rot, 'Z', 3.1415927f);
                PSMTXConcat(m, rot, m);
                break;
            }
        }
        if (bone->animPipe->replaceHierarchyCtrl == 0) {
            CTRLBuildMatrix(&bone->orientationCtrl.base, ctrlMtx);
            PSMTXConcat(ctrlMtx, m, m);
        }
    } else {
        fn_800B84AC(&blended.base, &bone->blendCtrl, &bone->orientationCtrl.base, blend);
        CTRLBuildMatrix(&blended.base, m);
    }

    parent = (GameBone*)bone->branch.Parent;
    if (bone->inheritanceFlag == 1 && parent != NULL) {
        PSMTXConcat(parent->forwardMtx, m, bone->forwardMtx);
    } else {
        PSMTXConcat(world, m, bone->forwardMtx);
    }
    if (bone->dispObj != NULL) {
        DOSetWorldMatrix(bone->dispObj, bone->forwardMtx);
    }
    if (actor->skinObject != NULL) {
        PSMTXConcat(bone->forwardMtx, bone->orientationInvMtx, bone->skinMtx);
        if (actor->skinObject->lightingData != NULL) {
            PSMTXInverse(bone->skinMtx, m);
            PSMTXTranspose(m, bone->skinInvTransposeMtx);
        }
    }
    for (child = (GameBone*)bone->branch.Children; child != NULL; child = (GameBone*)child->branch.Next) {
        fn_800B2DD0(actor, child);
    }
}
#endif

// .text:0x800B313C size:0x378
// Builds every bone's forward (and skinning) matrix.
// NONMATCHING 99%: blend switch is missing a dead `b` after case 0 (see docs/patterns/control-flow.md)
#if NONMATCHING
void fn_800B313C(GameActor* actor) {
    Mtx world;
    Mtx m;
    Mtx ctrlMtx;
    Mtx rot;
    GameControl blended;
    f32 blend;
    GameBone* bone;
    GameBone* parent;
    GameBone* target;
    u16 i;

    lbl_803CC1E8 = actor->tickFlag;
    CTRLBuildMatrix(&actor->worldControl.base, world);
    if (actor->boneRemap != NULL) {
        PSMTXConcat(world, lbl_80111640, world);
    }
    for (i = 0; i < actor->totalBones; i++) {
        bone = actor->boneArray[i];
        blend = actor->blend;
        switch (bone->flags & 3) {
        case 0:
            blend = 1.0f;
            break;
        case 1:
            break;
        case 2:
            blend = blend * blend;
            break;
        default:
            blend = 1.0f;
            break;
        }

        if (bone->flags & 0x20) {
            if (bone->flags & 4) {
                bone->blendCtrl.controlParams.srt.t.x = bone->animCtrl.controlParams.srt.t.x;
            }
            if (bone->flags & 8) {
                bone->blendCtrl.controlParams.srt.t.y = bone->animCtrl.controlParams.srt.t.y;
            }
            if (bone->flags & 0x10) {
                bone->blendCtrl.controlParams.srt.t.z = bone->animCtrl.controlParams.srt.t.z;
            }
        }

        if (bone->animCtrl.type != 0) {
            if (actor->boneRemap == NULL) {
                fn_800B84AC(&bone->animCtrl, &bone->blendCtrl, &bone->animCtrl, blend);
                CTRLBuildMatrix(&bone->animCtrl, m);
            } else if (actor->boneCallback == NULL ||
                       actor->boneCallback(bone, actor->boneArray[actor->boneRemap[i]], m, blend) == 0) {
                target = actor->boneArray[actor->boneRemap[i]];
                fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, blend);
                if (bone->branch.Parent != NULL) {
                    CTRLBuildMatrix_FlipY(&target->animCtrl, m);
                } else {
                    CTRLBuildMatrix_FlipX(&target->animCtrl, m);
                }
                switch (bone->rotAxis) {
                case 1:
                    PSMTXRotRad(rot, 'X', 3.1415927f);
                    PSMTXConcat(m, rot, m);
                    break;
                case 2:
                    PSMTXRotRad(rot, 'Y', 3.1415927f);
                    PSMTXConcat(m, rot, m);
                    break;
                case 3:
                    PSMTXRotRad(rot, 'Z', 3.1415927f);
                    PSMTXConcat(m, rot, m);
                    break;
                }
            }
            if (bone->animPipe->replaceHierarchyCtrl == 0) {
                CTRLBuildMatrix(&bone->orientationCtrl.base, ctrlMtx);
                PSMTXConcat(ctrlMtx, m, m);
            }
        } else {
            fn_800B84AC(&blended.base, &bone->blendCtrl, &bone->orientationCtrl.base, blend);
            CTRLBuildMatrix(&blended.base, m);
        }

        parent = (GameBone*)bone->branch.Parent;
        if (bone->inheritanceFlag == 1 && parent != NULL) {
            PSMTXConcat(parent->forwardMtx, m, bone->forwardMtx);
        } else {
            PSMTXConcat(world, m, bone->forwardMtx);
        }
        if (bone->dispObj != NULL) {
            DOSetWorldMatrix(bone->dispObj, bone->forwardMtx);
        }
        if (actor->skinObject != NULL) {
            PSMTXConcat(bone->forwardMtx, bone->orientationInvMtx, bone->skinMtx);
            if (actor->skinObject->lightingData != NULL) {
                PSMTXInverse(bone->skinMtx, m);
                PSMTXTranspose(m, bone->skinInvTransposeMtx);
            }
        }
    }
}
#endif

// .text:0x800B34B4 size:0x2F0
// Builds the forward matrix of one bone after (recursively) building its parents.
// NONMATCHING 97%: blend switch is missing a dead `b` after case 0; prologue arg moves scheduled differently
#if NONMATCHING
void fn_800B34B4(GameActor* actor, GameBone* bone, Mtx world) {
    Mtx m;
    Mtx ctrlMtx;
    Mtx rot;
    f32 blend;
    GameBone* parent;
    GameBone* target;
    u16 i;

    blend = actor->blend;
    switch (bone->flags & 3) {
    case 0:
        blend = 1.0f;
        break;
    case 1:
        break;
    case 2:
        blend = blend * blend;
        break;
    default:
        blend = 1.0f;
        break;
    }

    for (i = 0; i < actor->totalBones && bone->boneID != actor->boneArray[i]->boneID; i++) {
    }

    parent = (GameBone*)bone->branch.Parent;
    if (parent != NULL) {
        fn_800B34B4(actor, parent, world);
    }

    if (bone->flags & 0x20) {
        if (bone->flags & 4) {
            bone->blendCtrl.controlParams.srt.t.x = bone->animCtrl.controlParams.srt.t.x;
        }
        if (bone->flags & 8) {
            bone->blendCtrl.controlParams.srt.t.y = bone->animCtrl.controlParams.srt.t.y;
        }
        if (bone->flags & 0x10) {
            bone->blendCtrl.controlParams.srt.t.z = bone->animCtrl.controlParams.srt.t.z;
        }
    }

    if (bone->animCtrl.type != 0) {
        if (actor->boneRemap == NULL) {
            fn_800B84AC(&bone->animCtrl, &bone->blendCtrl, &bone->animCtrl, blend);
            CTRLBuildMatrix(&bone->animCtrl, m);
        } else if (actor->boneCallback == NULL ||
                   actor->boneCallback(bone, actor->boneArray[actor->boneRemap[i]], m, blend) == 0) {
            target = actor->boneArray[actor->boneRemap[i]];
            fn_800B84AC(&target->animCtrl, &target->blendCtrl, &target->animCtrl, blend);
            if (bone->branch.Parent != NULL) {
                CTRLBuildMatrix_FlipY(&target->animCtrl, m);
            } else {
                CTRLBuildMatrix_FlipX(&target->animCtrl, m);
            }
            switch (bone->rotAxis) {
            case 1:
                PSMTXRotRad(rot, 'X', 3.1415927f);
                PSMTXConcat(m, rot, m);
                break;
            case 2:
                PSMTXRotRad(rot, 'Y', 3.1415927f);
                PSMTXConcat(m, rot, m);
                break;
            case 3:
                PSMTXRotRad(rot, 'Z', 3.1415927f);
                PSMTXConcat(m, rot, m);
                break;
            }
        }
        if (bone->animPipe->replaceHierarchyCtrl == 0) {
            CTRLBuildMatrix(&bone->orientationCtrl.base, ctrlMtx);
            PSMTXConcat(ctrlMtx, m, m);
        }
    } else {
        CTRLBuildMatrix(&bone->orientationCtrl.base, m);
    }

    if (bone->inheritanceFlag == 1 && parent != NULL) {
        PSMTXConcat(parent->forwardMtx, m, bone->forwardMtx);
    } else {
        PSMTXConcat(world, m, bone->forwardMtx);
    }
}
#endif

// .text:0x800B37A4 size:0x2D4
void f_BuildBoneSkinOrientationMatrix(GameBone* bone, Mtx parent) {
    Mtx local;
    Mtx accum;

    for (; bone != NULL; bone = (GameBone*)bone->branch.Next) {
        if (bone->inheritanceFlag == 1) {
            CTRLBuildMatrix(&bone->orientationCtrl.base, local);
            PSMTXConcat(parent, local, accum);
            PSMTXInverse(accum, bone->orientationInvMtx);
        } else {
            CTRLBuildInverseMatrix(&bone->orientationCtrl.base, bone->orientationInvMtx);
        }
        if (bone->branch.Children != NULL) {
            f_BuildBoneSkinOrientationMatrix((GameBone*)bone->branch.Children, accum);
        }
    }
}

// .text:0x800B3A78 size:0x18C
// ACTRender: draws the skin, then every bone's display object in priority order.
void fn_800B3A78(GameActor* actor, Mtx camera, u8 numLights, ...) {
    va_list list;
    GameBone* bone;

    if (!(actor->flags & 9)) {
        return;
    }
    if (actor->skinObject != NULL) {
        fn_800B2D5C(actor);
        GXInvalidateVtxCache();
        va_start(list, numLights);
        if (actor->skHeader != NULL) {
            DOVARender(actor->skinObject, camera, numLights, &list);
        } else {
            DOVARenderSkin(actor->skinObject, camera, (MtxPtr)actor->skinMtxArray,
                           (MtxPtr)actor->skinInvTransposeMtxArray, numLights, &list);
        }
    }
    for (bone = (GameBone*)actor->drawPriorityList.Head; bone != NULL; bone = (GameBone*)bone->drawPriorityLink.Next) {
        if (bone->dispObj != NULL) {
            DOSetWorldMatrix(bone->dispObj, bone->forwardMtx);
        }
        va_start(list, numLights);
        DOVARender(bone->dispObj, camera, numLights, &list);
    }
}

// .text:0x800B3C04 size:0x31C
// Visibility test: 3 if a display object is in view, 2 if only the actor's
// fallback box is, 0 otherwise.
u8 fn_800B3C04(void* frustum, GameActor* actor, Mtx camera) {
    Vec pos;
    Mtx m;
    Vec box[8];
    GameBone* bone;
    struct DODisplayObj* obj;
    u8 result;

    result = 0;
    bone = (GameBone*)actor->drawPriorityList.Head;
    pos = lbl_800E7D28;
    if (actor->skinObject != NULL) {
        PSMTXCopy(actor->forwardMtxArray[actor->rootBone], m);
        PSMTXMultVec(m, &pos, &pos);
        PSMTXConcat(camera, m, m);
        obj = actor->skinObject;
        box[0].x = 1.2f * obj->bounds[1];
        box[0].y = obj->bounds[3] - pos.y;
        box[0].z = 1.2f * obj->bounds[4];
        box[1].x = 1.2f * obj->bounds[0];
        box[1].y = obj->bounds[3] - pos.y;
        box[1].z = 1.2f * obj->bounds[4];
        box[2].x = 1.2f * obj->bounds[0];
        box[2].y = obj->bounds[3] - pos.y;
        box[2].z = 1.2f * obj->bounds[5];
        box[3].x = 1.2f * obj->bounds[1];
        box[3].y = obj->bounds[3] - pos.y;
        box[3].z = 1.2f * obj->bounds[5];
        box[4].x = 1.2f * obj->bounds[1];
        box[4].y = obj->bounds[2] - pos.y;
        box[4].z = 1.2f * obj->bounds[4];
        box[5].x = 1.2f * obj->bounds[0];
        box[5].y = obj->bounds[2] - pos.y;
        box[5].z = 1.2f * obj->bounds[4];
        box[6].x = 1.2f * obj->bounds[0];
        box[6].y = obj->bounds[2] - pos.y;
        box[6].z = 1.2f * obj->bounds[5];
        box[7].x = 1.2f * obj->bounds[1];
        box[7].y = obj->bounds[2] - pos.y;
        box[7].z = 1.2f * obj->bounds[5];
        if (fn_800B7D3C(frustum, box, m)) {
            if (actor->flags & 0x24) {
                fn_800BEA04(pos);
            }
            return 3;
        }
        box[0].x = -2.0f;
        box[0].z = 2.0f;
        box[1].x = 2.0f;
        box[1].z = 2.0f;
        box[2].x = 2.0f;
        box[2].z = -2.0f;
        box[3].x = -2.0f;
        box[3].z = -2.0f;
        box[4].x = -2.0f;
        box[4].z = 2.0f;
        box[5].x = 2.0f;
        box[5].z = 2.0f;
        box[6].x = 2.0f;
        box[6].z = -2.0f;
        box[7].x = -2.0f;
        box[7].z = -2.0f;
        if (fn_800B7D3C(frustum, box, m)) {
            result = 2;
        }
    }
    for (; bone != NULL; bone = (GameBone*)bone->drawPriorityLink.Next) {
        obj = bone->dispObj;
        if (obj == NULL) {
            continue;
        }
        box[0].x = obj->bounds[1];
        box[0].y = obj->bounds[3];
        box[0].z = obj->bounds[4];
        box[1].x = obj->bounds[0];
        box[1].y = obj->bounds[3];
        box[1].z = obj->bounds[4];
        box[2].x = obj->bounds[0];
        box[2].y = obj->bounds[3];
        box[2].z = obj->bounds[5];
        box[3].x = obj->bounds[1];
        box[3].y = obj->bounds[3];
        box[3].z = obj->bounds[5];
        box[4].x = obj->bounds[1];
        box[4].y = obj->bounds[2];
        box[4].z = obj->bounds[4];
        box[5].x = obj->bounds[0];
        box[5].y = obj->bounds[2];
        box[5].z = obj->bounds[4];
        box[6].x = obj->bounds[0];
        box[6].y = obj->bounds[2];
        box[6].z = obj->bounds[5];
        box[7].x = obj->bounds[1];
        box[7].y = obj->bounds[2];
        box[7].z = obj->bounds[5];
        PSMTXConcat(camera, obj->worldMatrix, m);
        if (fn_800B7D3C(frustum, box, m)) {
            if (actor->flags & 0x24) {
                PSMTXMultVec(obj->worldMatrix, &pos, &pos);
                fn_800BEA04(pos);
            }
            return 3;
        }
    }
    if (result != 0 && (actor->flags & 4)) {
        fn_800BEA04(pos);
    }
    return result;
}

// .text:0x800B3F20 size:0x128
// Moves the actor so that anchorBoneA lands where anchorBoneB mirrored about it was.
void fn_800B3F20(GameActor* actor) {
    Vec posA;
    Vec posB;
    Mtx world;

    if (actor->anchorBoneA == actor->anchorBoneB) {
        return;
    }
    CTRLBuildMatrix(&actor->worldControl.base, world);
    if (actor->boneRemap != NULL) {
        PSMTXConcat(world, lbl_80111640, world);
    }
    fn_800B34B4(actor, actor->boneArray[actor->anchorBoneA], world);
    fn_800B34B4(actor, actor->boneArray[actor->anchorBoneB], world);
    fn_800B2C44(actor, actor->anchorBoneB, &posB);
    fn_800B2C44(actor, actor->anchorBoneA, &posA);
    posA.x = posA.x - (posB.x - posA.x);
    posA.z = posA.z - (posB.z - posA.z);
    CTRLSetTranslation(&actor->worldControl.base, posA.x, posA.y, posA.z);
}

// .text:0x800B4048 size:0x3C
s32 fn_800B4048(GameActor** actor, ActorLayout* layout, u16 actorID) {
    layout->actorID = actorID;
    *actor = fn_800B43A0(layout);
    return 1;
}

// .text:0x800B4084 size:0x1F4
// Creates the bones of one layout sibling chain (and their children) under parent.
void fn_800B4084(GameBone* parent, ActorBone* layoutBone, GameActor* actor, u16* boneIndex, GameBone* boneMem) {
    GameBone* bone;

    for (; layoutBone != NULL; layoutBone = (ActorBone*)layoutBone->branch.Next) {
        bone = &boneMem[*boneIndex];
        bone->branch.Children = NULL;
        DSInsertBranchBelow(&actor->hierarchy, (Ptr)parent, (Ptr)bone);
        actor->boneArray[*boneIndex] = bone;
        bone->boneID = layoutBone->boneID;
        bone->inheritanceFlag = layoutBone->inheritanceFlag;
        bone->drawingPriority = layoutBone->drawingPriority;
        bone->orientationCtrl.base.type = 0;
        if (layoutBone->orientationCtrl != NULL) {
            bone->orientationCtrl = *(GameControl*)layoutBone->orientationCtrl;
        }
        bone->dispObj = NULL;
        if (layoutBone->geoFileID != 0xFFFF) {
            DOGet(&bone->dispObj, actor->pal, layoutBone->geoFileID);
        }
        bone->baseDispObj = bone->dispObj;
        bone->animPipe = NULL;
        bone->animCtrl.type = 0;
        bone->blendCtrl.type = 0;
        bone->flags = 1;
        bone->unk136 = 0;
        bone->rotAxis = 0;
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
        if (layoutBone->branch.Children != NULL) {
            fn_800B4084(bone, (ActorBone*)layoutBone->branch.Children, actor, boneIndex, boneMem);
        }
    }
}

static inline void ReleaseDisplayObj(struct DODisplayObj* obj) {
    if (obj->displayData != NULL) {
        fn_800ACFB0(obj->displayData);
    }
    if (obj->lightingData != NULL) {
        fn_800ACFB0(obj->lightingData);
    }
    if (obj->textureData != NULL) {
        fn_800ACFB0(obj->textureData);
    }
    if (obj->colorData != NULL) {
        fn_800ACFB0(obj->colorData);
    }
    if (obj->positionData != NULL) {
        fn_800ACFB0(obj->positionData);
    }
    fn_800ACFB0(obj);
}

// .text:0x800B4278 size:0x128
// ACTRelease. Note: the original reads actor->skinObject after freeing actor.
void fn_800B4278(GameActor* actor) {
    struct DODisplayObj* obj;
    s32 i;
    struct DODisplayObj* skin;

    skin = actor->skinObject;
    fn_800B4CDC(actor);
    for (i = actor->totalBones - 1; i >= 0; i--) {
        obj = actor->boneArray[i]->dispObj;
        if (obj != NULL) {
            ReleaseDisplayObj(obj);
        }
    }
    fn_800ACFB0(actor);
    if (skin != NULL) {
        ReleaseDisplayObj(actor->skinObject);
    }
}

// .text:0x800B43A0 size:0x384
// ACTBuild: allocates an actor and all its bones/matrices in one block.
// NONMATCHING 93%: original frame is 0xA0 bytes larger and the size sums are associated differently
#if NONMATCHING
GameActor* fn_800B43A0(ActorLayout* layout) {
    Mtx identity;
    struct DODisplayObj* skin;
    GameActor* actor;
    u16 boneCount;
    u32 boneArraySize;
    u32 forwardSize;
    u32 skinSize;
    u32 orientSize;
    u32 invTransposeSize;
    u32 vertexSize;
    u16 compSize;
    PositionData* pos;
    u32 size;

    skinSize = 0;
    orientSize = 0;
    invTransposeSize = 0;
    vertexSize = 0;
    boneCount = 0;
    boneArraySize = OSRoundUp32B(layout->totalBones * sizeof(GameBone*));
    forwardSize = OSRoundUp32B(layout->totalBones * sizeof(Mtx));
    if (layout->skinFileID != 0xFFFF) {
        DOGet(&skin, layout->geoPalette, layout->skinFileID);
        skinSize = orientSize = OSRoundUp32B(layout->totalBones * sizeof(Mtx));
        if (skin->lightingData != NULL) {
            invTransposeSize = skinSize;
        }
        pos = skin->positionData;
        switch ((u8)(pos->quantizeInfo >> 4)) {
        case 0:
        case 1:
            compSize = 1;
            break;
        case 2:
        case 3:
            compSize = 2;
            break;
        case 4:
            compSize = 4;
            break;
        default:
            compSize = 0;
            break;
        }
        vertexSize = OSRoundUp32B(pos->numPositions * (pos->compCount * compSize));
    }

    size = boneArraySize + forwardSize + skinSize + orientSize + vertexSize + invTransposeSize;
    actor = _OSAllocFromHeap(0x20, size + OSRoundUp32B(layout->totalBones * sizeof(GameBone)) + sizeof(GameActor));
    actor->boneArray = (GameBone**)(actor + 1);
    actor->forwardMtxArray = (Mtx*)((u8*)actor->boneArray + boneArraySize);
    actor->skinObject = skin;
    actor->skHeader = NULL;
    PSMTXIdentity(identity);
    actor->actorID = layout->actorID;
    actor->layout = layout;
    actor->totalBones = layout->totalBones;
    DSInitTree(&actor->hierarchy, NULL, &((GameBone*)NULL)->branch);
    DSInitList(&actor->drawPriorityList, NULL, &((GameBone*)NULL)->drawPriorityLink);
    actor->pal = NULL;
    if (layout->geoPalette != NULL) {
        actor->pal = layout->geoPalette;
    }

    if (layout->skinFileID != 0xFFFF) {
        u32 normalOffset;

        DOSetWorldMatrix(actor->skinObject, identity);
        actor->skinMtxArray = (Mtx*)((u8*)actor->forwardMtxArray + forwardSize);
        actor->orientationInvMtxArray = (Mtx*)((u8*)actor->skinMtxArray + skinSize);
        // Move the skin's vertex positions (and the normals right after them) into the actor block.
        normalOffset = actor->skinObject->lightingData->normalArray - actor->skinObject->positionData->positionArray;
        actor->skinObject->positionData->positionArray = (char*)actor->orientationInvMtxArray + orientSize;
        actor->skinObject->lightingData->normalArray = actor->skinObject->positionData->positionArray + normalOffset;
        if (actor->skinObject->lightingData != NULL) {
            actor->skinInvTransposeMtxArray = (Mtx*)(actor->skinObject->positionData->positionArray + vertexSize);
        } else {
            actor->skinInvTransposeMtxArray = NULL;
        }
    } else {
        actor->skinObject = NULL;
        actor->skinMtxArray = NULL;
        actor->orientationInvMtxArray = NULL;
        actor->skinInvTransposeMtxArray = NULL;
    }

    actor->worldControl.base.type = 0;
    if (layout->hierarchy.Root != NULL) {
        fn_800B4084(NULL, (ActorBone*)layout->hierarchy.Root, actor, &boneCount,
                    (GameBone*)((u8*)actor->forwardMtxArray +
                                (forwardSize + skinSize + orientSize + vertexSize + invTransposeSize)));
    }
    if (boneCount != actor->totalBones) {
        OSPanic("act.c", 0x1F0, "Incorrect number of bones in actor");
    }
    if (actor->skinObject != NULL) {
        f_BuildBoneSkinOrientationMatrix((GameBone*)actor->hierarchy.Root, identity);
    }
    ACTSort(actor);
    actor->anchorBoneA = 0;
    actor->anchorBoneB = 0;
    actor->rootBone = 0;
    actor->boneRemap = NULL;
    actor->blend = 1.0f;
    actor->blendSpeed = 0.0f;
    actor->tickFlag = 0;
    actor->flags = 0;
    actor->boneCallback = NULL;
    return actor;
}
#endif

// .text:0x800B4724 size:0x8
void fn_800B4724(GameActor* actor, sHdr* skHeader) {
    actor->skHeader = skHeader;
}

// .text:0x800B472C size:0x1DC
void fn_800B472C(StaticModel* model) {
    MtxPtr world;
    MtxPtr camera;
    s32 i;
    ActorLayoutFile* file;
    struct DODisplayObj* obj;
    DODisplayData* pal;
    ActorBone* layoutBone;
    Mtx m;
    Vec box[8];

    world = model->world;
    camera = model->camera;
    file = (ActorLayoutFile*)model->layout;
    pal = file->header.geoPalette;
    for (i = 0; i < file->header.totalBones; i++) {
        layoutBone = &file->bones[i];
        if (layoutBone->geoFileID == 0xFFFF) {
            continue;
        }
        // TODO type: MSSB's descriptor entries point straight at display objects.
        obj = (struct DODisplayObj*)pal->descriptorArray[layoutBone->geoFileID].layout;
        CTRLBuildMatrix(layoutBone->orientationCtrl, obj->worldMatrix);
        PSMTXConcat(world, obj->worldMatrix, obj->worldMatrix);
        PSMTXConcat(camera, obj->worldMatrix, m);
        box[0].x = obj->bounds[1];
        box[0].y = obj->bounds[3];
        box[0].z = obj->bounds[4];
        box[1].x = obj->bounds[0];
        box[1].y = obj->bounds[3];
        box[1].z = obj->bounds[4];
        box[2].x = obj->bounds[0];
        box[2].y = obj->bounds[3];
        box[2].z = obj->bounds[5];
        box[3].x = obj->bounds[1];
        box[3].y = obj->bounds[3];
        box[3].z = obj->bounds[5];
        box[4].x = obj->bounds[1];
        box[4].y = obj->bounds[2];
        box[4].z = obj->bounds[4];
        box[5].x = obj->bounds[0];
        box[5].y = obj->bounds[2];
        box[5].z = obj->bounds[4];
        box[6].x = obj->bounds[0];
        box[6].y = obj->bounds[2];
        box[6].z = obj->bounds[5];
        box[7].x = obj->bounds[1];
        box[7].y = obj->bounds[2];
        box[7].z = obj->bounds[5];
        if (fn_800B7D3C(NULL, box, m)) {
            if (layoutBone->flags & 1) {
                GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            } else {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
            }
            switch (layoutBone->flags & 6) {
            case 2:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_CLEAR);
                break;
            case 4:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTCOL, GX_BL_ZERO, GX_LO_CLEAR);
                break;
            default:
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                break;
            }
            DOVARender(obj, camera, 0, NULL);
        }
    }
}

// .text:0x800B4908 size:0x8
void haveActLayoutPointToGeoHeader(ActorLayout* layout, DODisplayData* geoPalette) {
    layout->geoPalette = geoPalette;
}

// .text:0x800B4910 size:0xD4
void LoadActorLayout(void) {
    return;
}

// .text:0x800B49E4 size:0x60
// Same as LoadActorLayout for static layouts (no null checks, no branches).
void fn_800B49E4(ActorLayout* layout) {
    ActorLayoutFile* file = (ActorLayoutFile*)layout;
    s32 i;

    layout->hierarchy.Offset = (u32)layout + layout->hierarchy.Offset;
    layout->hierarchy.Root = (Ptr)layout + (u32)layout->hierarchy.Root;
    layout->geoPaletteName = (char*)layout + (u32)layout->geoPaletteName;
    layout->userData = (char*)layout + (u32)layout->userData;
    for (i = 0; i < layout->totalBones; i++) {
        file->bones[i].orientationCtrl = (Control*)((u8*)layout + (u32)file->bones[i].orientationCtrl);
    }
}
