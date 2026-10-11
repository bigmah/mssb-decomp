#include "main/file_800B79D0.h"

// .text:0x800B79D0 size:0x36C
void ACTSetBoneTrack(GameBone* bone, struct ANIMAnimTrack* track, f32 time, s32 blend) {
    u8 orientType;
    Quaternion pose; // x,y,z(,w) of whichever component is being copied

    if (track == NULL) {
        if (bone->animPipe != NULL && bone->animPipe->control != NULL) {
            bone->animPipe->control->type = 0;
            bone->animPipe->currentTrack = NULL;
        }
        return;
    }

    if (bone->animPipe == NULL) {
        bone->animPipe = _OSAllocFromHeap(0x20, sizeof(struct ANIMPipe));
        bone->animPipe->time = 0.0f;
        bone->animPipe->prevTime = 0.0f;
        bone->animPipe->speed = 1.0f;
        bone->animPipe->currentTrack = NULL;
        bone->animPipe->control = NULL;
        bone->animPipe->replaceHierarchyCtrl = 0;
        bone->animPipe->forward = 1;
        bone->animPipe->loop = 1;
    }
    bone->animPipe->keyFrameCache = 0;

    // Remember the pose we are blending from.
    if (blend) {
        if (bone->animPipe->control != NULL) {
            if (bone->animPipe->control->type != 0) {
                bone->blendCtrlFull = bone->animCtrlFull;
            } else {
                bone->blendCtrlFull = bone->orientCtrl;
            }
        } else {
            bone->blendCtrlFull = bone->animCtrlFull;
        }
    }

    ANIMBind(bone->animPipe, &bone->animCtrl, track, time);

    if (bone->stepTranslation) {
        bone->animPipe->currentTrack->interpolationType &= ~3;
    }

    // Components the track does not animate keep the bone's rest orientation.
    orientType = bone->orientCtrl.base.type;
    if ((orientType & CTRL_TRANS) && !(track->animType & 0x01)) {
        CTRLGetTranslation(&bone->orientCtrl.base, &pose.x, &pose.y, &pose.z);
        CTRLSetTranslation(&bone->animCtrl, pose.x, pose.y, pose.z);
    }
    if ((orientType & CTRL_SCALE) && !(track->animType & 0x02)) {
        CTRLGetScale(&bone->orientCtrl.base, &pose.x, &pose.y, &pose.z);
        CTRLSetScale(&bone->animCtrl, pose.x, pose.y, pose.z);
        if ((orientType & CTRL_SCALE_QUAT) && !(track->animType & 0x20)) {
            CTRL_GetQuatUnk(&bone->orientCtrl.base, &pose.x, &pose.y, &pose.z, &pose.w);
        } else {
            pose.x = 0.0f;
            pose.y = 0.0f;
            pose.z = 0.0f;
            pose.w = 1.0f;
        }
        CTRL_SetQuatUnk(&bone->animCtrl, pose.x, pose.y, pose.z, pose.w);
    }
    if ((orientType & CTRL_ROT_EULER) && !(track->animType & 0x04)) {
        CTRLGetRotation(&bone->orientCtrl.base, &pose.x, &pose.y, &pose.z);
        CTRLSetRotation(&bone->animCtrl, pose.x, pose.y, pose.z);
    } else if ((orientType & CTRL_ROT_QUAT) && !(track->animType & 0x08)) {
        CTRLGetQuat(&bone->orientCtrl.base, &pose.x, &pose.y, &pose.z, &pose.w);
        CTRLSetQuat(&bone->animCtrl, pose.x, pose.y, pose.z, pose.w);
    }

    if (!blend) {
        bone->blendCtrlFull = bone->animCtrlFull;
    }
}
