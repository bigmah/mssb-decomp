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
    GameAnimPipe* pipe;

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
void fn_800B4BC8(void) {
    return;
}

// .text:0x800B4C04 size:0x3C
void fn_800B4C04(void) {
    return;
}

// .text:0x800B4C40 size:0x60
void fn_800B4C40(void) {
    return;
}

// .text:0x800B4CA0 size:0x3C
void fn_800B4CA0(void) {
    return;
}

// .text:0x800B4CDC size:0x88
void fn_800B4CDC(void) {
    return;
}

// .text:0x800B4D64 size:0x138
void ACTSetAnimation(void) {
    return;
}

// .text:0x800B4E9C size:0x100
void ANIMGetKeyFrameFromTrack(void) {
    return;
}

// .text:0x800B4F9C size:0x50
void ANIMGetTrackFromSequence(void) {
    return;
}

// .text:0x800B4FEC size:0xA0
void ANIMGetSequence(void) {
    return;
}

// .text:0x800B508C size:0xE0
void ANIMGet(void) {
    return;
}
