#include "challenge/rep_7920.h"

typedef struct { u16 first; u16 second; void* data; } ChallengeResource;
extern ChallengeResource lbl_1_common_bss_4C6F8[];


// fn_1_26BFC, size:0x30
void* fn_1_26BFC(u16* resource, s32 index) {
    ChallengeResource* entry = &lbl_1_common_bss_4C6F8[index];
    entry->first = resource[0];
    entry->second = resource[1];
    entry->data = resource + 2;
    return entry;
}
