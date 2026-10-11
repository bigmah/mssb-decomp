#include "main/file_800B4A44.h"
extern void fn_800ACFB0(void* object); // free
#include "charPipeline/structures/dolphinString.h"

extern f32 lbl_803CCF78; // 0.0f
extern f32 lbl_803CCF7C; // 1.0f

// .text:0x800B4A44 size:0x50
f32 fn_800B4A44(GameActor* actor, u16 boneIndex) {
    GameBone* bone = actor->boneArray[boneIndex];

    if (bone->animPipe != NULL) {
        if (bone->animPipe->forward == 0) {
            return bone->animPipe->time;
        }
        if (bone->animPipe->currentTrack != NULL) {
            return bone->animPipe->currentTrack->animTime - bone->animPipe->time;
        }
    }
    return lbl_803CCF78;
}

// .text:0x800B4A94 size:0x68
f32 fn_800B4A94(GameActor* actor) {
    u32 i;
    GameBone* bone;

    for (i = 0; i < actor->totalBones; i++) {
        bone = actor->boneArray[i];
        if (bone->animPipe != NULL) {
            if (bone->animPipe->forward == 0) {
                return bone->animPipe->time;
            }
            if (bone->animPipe->currentTrack != NULL) {
                return bone->animPipe->currentTrack->animTime - bone->animPipe->time;
            }
        }
    }
    return lbl_803CCF78;
}

// .text:0x800B4AFC size:0x3C
void fn_800B4AFC(GameActor* actor, u8 loop) {
    u32 i;
    struct ANIMPipe* pipe;

    for (i = 0; i < actor->totalBones; i++) {
        pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) {
            pipe->loop = loop;
        }
    }
}

// .text:0x800B4B38 size:0x90
void AnimateActorBones(GameActor* actor) {
    u32 i;

    actor->blend += actor->blendSpeed;
    if (actor->blend > 1.0f) {
        actor->blend = 1.0f;
    }
    for (i = 0; i < actor->totalBones; i++) {
        ANIMTick(actor->boneArray[i]->animPipe, actor->tickFlag);
    }
}

// .text:0x800B4BC8 size:0x3C
void fn_800B4BC8(GameActor* actor, u8 forward) {
    u32 i;
    struct ANIMPipe* pipe;

    for (i = 0; i < actor->totalBones; i++) {
        pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) {
            pipe->forward = forward;
        }
    }
}

// .text:0x800B4C04 size:0x3C
void fn_800B4C04(GameActor* actor, f32 speed) {
    u32 i;
    struct ANIMPipe* pipe;

    for (i = 0; i < actor->totalBones; i++) {
        pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) {
            pipe->speed = speed;
        }
    }
}

// .text:0x800B4C40 size:0x60
f32 fn_800B4C40(GameActor* actor) {
    u32 i;
    struct ANIMPipe* pipe;

    for (i = 0; i < actor->totalBones; i++) {
        pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL && pipe->currentTrack != NULL) {
            return actor->boneArray[i]->animPipe->time;
        }
    }
    return lbl_803CCF78;
}

// .text:0x800B4CA0 size:0x3C
void fn_800B4CA0(GameActor* actor, f32 time) {
    u32 i;
    struct ANIMPipe* pipe;

    for (i = 0; i < actor->totalBones; i++) {
        pipe = actor->boneArray[i]->animPipe;
        if (pipe != NULL) {
            pipe->time = time;
        }
    }
}

// .text:0x800B4CDC size:0x88
void fn_800B4CDC(GameActor* actor) {
    s32 i;

    for (i = actor->totalBones - 1; i >= 0; i--) {
        if (actor->boneArray[i]->animPipe != NULL) {
            fn_800ACFB0(actor->boneArray[i]->animPipe);
            actor->boneArray[i]->animPipe = NULL;
        }
    }
}

// .text:0x800B4D64 size:0x138
void ACTSetAnimation(GameActor* actor, ANIMBank* animBank, char* sequenceName, u16 seqNum, f32 time, f32 blendSpeed) {
    u16 i;
    ANIMSequences* seq = ANIMGetSequence(animBank, sequenceName, seqNum);
    struct ANIMAnimTrack* track = NULL;
    GameBone* bone;
    s32 blendFlag;

    for (i = 0; i < actor->totalBones; i++) {
        if (seq != NULL) {
            track = ANIMGetTrackFromSequence(seq, actor->boneArray[i]->boneID);
        }
        bone = actor->boneArray[i];
        blendFlag = 0;
        if (actor->blend < 1.0f && bone->flags != 0) {
            blendFlag = 1;
        }
        ACTSetBoneTrack(bone, track, time, blendFlag);
        if (actor->boneArray[i]->flags & 0x1C) {
            actor->boneArray[i]->flags |= 0x20;
        } else {
            actor->boneArray[i]->flags &= 0xFFDF;
        }
    }
    actor->blend = (blendSpeed != lbl_803CCF78) ? lbl_803CCF78 : lbl_803CCF7C;
    actor->blendSpeed = blendSpeed;
}

// .text:0x800B4E9C size:0x100
// NONMATCHING 98%: r8/r9 swapped between (u16)i and total - 1 (see docs/patterns/regalloc.md)
#if NONMATCHING
void ANIMGetKeyFrameFromTrack(struct ANIMAnimTrack* animTrack, f32 time, KeyFrame** currentFrame, KeyFrame** nextFrame, u16* frameIndex) {
    KeyFrame* keyFrames;
    u32 start;
    u16 total;
    KeyFrame* frame;
    u16 i;
    u16 count;

    keyFrames = animTrack->keyFrames;
    start = (keyFrames[*frameIndex].time <= time) ? *frameIndex : 0;
    total = animTrack->totalFrames;
    i = start;
    count = total;
    while (count--) {
        frame = &keyFrames[i];
        if (frame->time <= time) {
            if (i < total - 1) {
                if (keyFrames[i + 1].time > time) {
                    if (currentFrame != NULL) {
                        *currentFrame = frame;
                    }
                    if (nextFrame != NULL) {
                        *nextFrame = &animTrack->keyFrames[i + 1];
                    }
                    *frameIndex = i;
                    return;
                }
            } else {
                if (currentFrame != NULL) {
                    *currentFrame = frame;
                }
                if (nextFrame != NULL) {
                    *nextFrame = animTrack->keyFrames;
                }
                *frameIndex = i;
                return;
            }
        }
        i = (i + 1) % total;
    }
}
#endif

// .text:0x800B4F9C size:0x50
struct ANIMAnimTrack* ANIMGetTrackFromSequence(ANIMSequences* animSeq, u16 animTrackID) {
    u32 i;

    for (i = 0; i < animSeq->totalTracks; i++) {
        if (animTrackID == animSeq->trackArray[i].trackID) {
            return &animSeq->trackArray[i];
        }
    }
    return NULL;
}

// .text:0x800B4FEC size:0xA0
ANIMSequences* ANIMGetSequence(ANIMBank* animBank, char* sequenceName, u16 seqNum) {
    u32 i;

    if (sequenceName != NULL) {
        for (i = 0; i < animBank->numSequences; i++) {
            if (Strcmp(animBank->animSequences[i].sequenceName, sequenceName) == 0) {
                return &animBank->animSequences[i];
            }
        }
    } else if (animBank == NULL) {
        return NULL;
    }
    return &animBank->animSequences[seqNum];
}

// .text:0x800B508C size:0xE0
// Converts the bank's file offsets into pointers in place.
void ANIMGet(ANIMBank* animBank) {
    ANIMSequences* seq;
    struct ANIMAnimTrack* track;
    KeyFrame* keyFrame;
    u32 i;

    if (animBank->userDataSize != 0 && animBank->userData != NULL) {
        animBank->userData = (u8*)animBank->userData + (u32)animBank;
    }
    seq = (ANIMSequences*)(animBank + 1);
    track = (struct ANIMAnimTrack*)(seq + animBank->numSequences);
    keyFrame = (KeyFrame*)(track + animBank->numTracks);
    animBank->animSequences = (ANIMSequences*)((u8*)animBank->animSequences + (u32)animBank);

    for (i = 0; i < animBank->numSequences; i++) {
        seq[i].sequenceName = (char*)animBank + (u32)seq[i].sequenceName;
        seq[i].trackArray = (struct ANIMAnimTrack*)((u8*)animBank + (u32)seq[i].trackArray);
    }
    for (i = 0; i < animBank->numTracks; i++) {
        track[i].keyFrames = (KeyFrame*)((u8*)animBank + (u32)track[i].keyFrames);
    }
    for (i = 0; i < animBank->numKeyFrames; i++) {
        keyFrame[i].setting = (char*)animBank + (u32)keyFrame[i].setting;
        keyFrame[i].interpolation = (char*)animBank + (u32)keyFrame[i].interpolation;
    }
}
