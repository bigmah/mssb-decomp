#include "challenge/rep_7920.h"

typedef struct { u16 first; u16 second; void* data; } ChallengeResource;
extern ChallengeResource lbl_1_common_bss_4C6F8[];
extern const f32 lbl_1_rodata_7970[];
extern const f32 lbl_1_rodata_7974;


// fn_1_26BFC, size:0x30
void* fn_1_26BFC(u16* resource, s32 index) {
    ChallengeResource* entry = &lbl_1_common_bss_4C6F8[index];
    entry->first = resource[0];
    entry->second = resource[1];
    entry->data = resource + 2;
    return entry;
}

// fn_1_26B7C, size:0x80
void fn_1_26B7C(ChallengeAnimation* animation) {
    animation->position = lbl_1_rodata_7970[0];
    animation->scale = lbl_1_rodata_7974;
    animation->mode = 1;
    animation->frame = 0;
    animation->timer = 0;
    animation->resourceIndex = -1;
    animation->enabled = 1;
    animation->data = NULL;
    animation->active = 1;
    if (animation != NULL) {
        animation->horizontal = 3;
    }
    if (animation != NULL) {
        animation->vertical = 3;
    }
}
