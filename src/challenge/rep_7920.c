#include "challenge/rep_7920.h"
#define REP_HEADER_FN repHeader_7920
#include "header_rep_inline.h"

extern ChallengeResource lbl_1_common_bss_4C6F8[];
extern ChallengeAnimation lbl_1_common_bss_4BC30[];
static u8 lbl_1_data_108E0[2] = { 1, 1 }; // [0]: cleared by the first fn_1_26C2C
// .bss is laid out in reverse definition order.
static u16 lbl_1_bss_47052;
static u16 lbl_1_bss_47050;


// .text:0x00026C2C size:0xFC
ChallengeAnimation* fn_1_26C2C(ChallengeResource* resource, s32 index) {
    if (resource == NULL) {
        return NULL;
    }
    if (lbl_1_data_108E0[0] != 0) {
        lbl_1_data_108E0[0] = 0;
    }
    fn_1_26B7C(&lbl_1_common_bss_4BC30[index]);
    lbl_1_common_bss_4BC30[index].first = resource->first;
    lbl_1_common_bss_4BC30[index].second = resource->second;
    lbl_1_common_bss_4BC30[index].resource = resource->data;
    lbl_1_bss_47052 = resource->first;
    lbl_1_bss_47050 = resource->second;
    return &lbl_1_common_bss_4BC30[index];
}

// .text:0x00026BFC size:0x30
void* fn_1_26BFC(u16* resource, s32 index) {
    ChallengeResource* entry = &lbl_1_common_bss_4C6F8[index];
    entry->first = resource[0];
    entry->second = resource[1];
    entry->data = resource + 2;
    return entry;
}

// .text:0x00026B7C size:0x80
void fn_1_26B7C(ChallengeAnimation* animation) {
    animation->position = 0.0f;
    animation->scale = 1.0f;
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
