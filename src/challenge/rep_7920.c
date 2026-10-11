#include "challenge/rep_7920.h"

extern ChallengeResource lbl_1_common_bss_4C6F8[];
extern const f32 lbl_1_rodata_7970[];
extern const f32 lbl_1_rodata_7974;
extern ChallengeAnimation lbl_1_common_bss_4BC30[];
extern u8 lbl_1_data_108E0;
u16 lbl_1_bss_47050;
u16 lbl_1_bss_47052;


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

// fn_1_26C2C, size:0xFC
// NONMATCHING 90%: inlined fn_1_26B7C keeps &anim->flags (addi r6,r9,0x11) in a reg and schedules the lfs earlier
#if NONMATCHING
ChallengeAnimation* fn_1_26C2C(ChallengeResource* resource, s32 index) {
    ChallengeAnimation* animation;

    if (resource == NULL) {
        return NULL;
    }
    if (lbl_1_data_108E0 != 0) {
        lbl_1_data_108E0 = 0;
    }
    animation = &lbl_1_common_bss_4BC30[index];
    fn_1_26B7C(animation);
    lbl_1_common_bss_4BC30[index].first = resource->first;
    lbl_1_common_bss_4BC30[index].second = resource->second;
    lbl_1_common_bss_4BC30[index].resource = resource->data;
    lbl_1_bss_47052 = resource->first;
    lbl_1_bss_47050 = resource->second;
    return animation;
}
#endif
