#include "main/file_800BD3EC.h"
#include "main/file_800B9974.h"
#include "main/file_800BDEA0.h"
#include "Dolphin/gx.h"

extern void* _OSAllocFromHeap(s32 align, s32 size);
// TODO: move to file_800B2C44.h once fn_800B3A78 (DORender-like, variadic) has C there
extern void fn_800B3A78(struct DODisplayObj* dispObj, MtxPtr camera, u8 numArgs, ...);


// .text:0x800BD3EC size:0x8C
void LITAlloc(Light** light) {
    *light = _OSAllocFromHeap(0x20, sizeof(Light));
    (*light)->position.z = 0.0f;
    (*light)->position.y = 0.0f;
    (*light)->position.x = 0.0f;
    (*light)->direction.y = 0.0f;
    (*light)->direction.x = 0.0f;
    (*light)->direction.z = 1.0f;
    (*light)->parent = NULL;
    (*light)->animPipe = NULL;
    (*light)->control.type = 0;
}

// .text:0x800BD478 size:0xD0
void fn_800BD478(Actor** actor, ActorLayoutFile* layout) {
    s32 j;
    s32 i;
    struct DODisplayObj* obj;

    for (i = 0; i < layout->header.totalBones; i++) {
        if (layout->bones[i].pad16 & 0x18) {
            for (j = 0; j < (*actor)->totalBones; j++) {
                if (layout->bones[i].boneID == (*actor)->boneArray[j]->boneID) {
                    if (layout->bones[i].geoFileID != 0xFFFF) {
                        obj = (*actor)->boneArray[j]->dispObj;
                        if (obj != NULL) {
                            fn_800BC824(obj, *(void**)((u8*)fn_800BF068() + 8)); // TODO type
                        }
                    }
                    break;
                }
            }
        }
    }
}

// .text:0x800BD548 size:0x128
void fn_800BD548(void) {
    return;
}

// .text:0x800BD670 size:0x254
void fn_800BD670(void) {
    return;
}
