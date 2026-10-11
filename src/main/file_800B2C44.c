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
void fn_800B2DD0(void) {
    return;
}

// .text:0x800B313C size:0x378
void fn_800B313C(void) {
    return;
}

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
void fn_800B4048(void) {
    return;
}

// .text:0x800B4084 size:0x1F4
void fn_800B4084(void) {
    return;
}

// .text:0x800B4278 size:0x128
void fn_800B4278(void) {
    return;
}

// .text:0x800B43A0 size:0x384
void fn_800B43A0(void) {
    return;
}

// .text:0x800B4724 size:0x8
void fn_800B4724(GameActor* actor, sHdr* skHeader) {
    actor->skHeader = skHeader;
}

// .text:0x800B472C size:0x1DC
void fn_800B472C(void) {
    return;
}

// .text:0x800B4908 size:0x8
void haveActLayoutPointToGeoHeader(void) {
    return;
}

// .text:0x800B4910 size:0xD4
void LoadActorLayout(void) {
    return;
}

// .text:0x800B49E4 size:0x60
void fn_800B49E4(void) {
    return;
}
