#include "main/file_800BD3EC.h"
#include "main/file_800B9974.h"
#include "main/file_800BDEA0.h"
#include "main/file_800B2C44.h"
#include "main/file_800A7C08.h"
#include "Dolphin/gx.h"


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
void fn_800BD478(GameActor** actor, ActorLayoutFile* layout) {
    s32 j;
    s32 i;
    struct DODisplayObj* obj;

    for (i = 0; i < layout->header.totalBones; i++) {
        if (layout->bones[i].flags & 0x18) {
            for (j = 0; j < (*actor)->totalBones; j++) {
                if (layout->bones[i].boneID == (*actor)->boneArray[j]->boneID) {
                    if (layout->bones[i].geoFileID != 0xFFFF) {
                        obj = (*actor)->boneArray[j]->dispObj;
                        if (obj != NULL) {
                            fn_800BC824(obj, fn_800BF068()->texObjs);
                        }
                    }
                    break;
                }
            }
        }
    }
}

// .text:0x800BD548 size:0x128
void fn_800BD548(ActorObject* obj, u8 numLights, ...) {
    va_list list;
    s32 i;
    void* arg;

    obj->numLights = numLights;
    va_start(list, numLights);
    for (i = 1; i <= numLights; i++) {
        arg = va_arg(list, void*);
        switch (i) {
        case 1:
            obj->lights[0] = arg;
            break;
        case 2:
            obj->lights[1] = arg;
            break;
        case 3:
            obj->lights[2] = arg;
            break;
        case 4:
            obj->lights[3] = arg;
            break;
        case 5:
            obj->lights[4] = arg;
            break;
        case 6:
            obj->lights[5] = arg;
            break;
        case 7:
            obj->lights[6] = arg;
            break;
        case 8:
            obj->lights[7] = arg;
            break;
        }
    }
    va_end(list);
}

// NONMATCHING 98%: loop counter i and entry pointer swap r30/r31
#if NONMATCHING
// .text:0x800BD670 size:0x254
void fn_800BD670(ActorObjectTable* table, MtxPtr camera) {
    u16 i;
    ActorObject* entry;
    GameActor* obj;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < table->count; i++) {
        obj = table->objects[i].actor;
        if (obj == NULL || table->objects[i].animateBones == 0) {
            continue;
        }
        entry = &table->objects[i];
        if (entry->callback != NULL) {
            entry->callback(entry);
        }
        switch (entry->numLights) {
        case 0: fn_800B3A78(obj, camera, 0); break;
        case 1: fn_800B3A78(obj, camera, 1, entry->lights[0]); break;
        case 2: fn_800B3A78(obj, camera, 2, entry->lights[0], entry->lights[1]); break;
        case 3: fn_800B3A78(obj, camera, 3, entry->lights[0], entry->lights[1], entry->lights[2]); break;
        case 4: fn_800B3A78(obj, camera, 4, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3]); break;
        case 5: fn_800B3A78(obj, camera, 5, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4]); break;
        case 6: fn_800B3A78(obj, camera, 6, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5]); break;
        case 7: fn_800B3A78(obj, camera, 7, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5], entry->lights[6]); break;
        case 8: fn_800B3A78(obj, camera, 8, entry->lights[0], entry->lights[1], entry->lights[2], entry->lights[3], entry->lights[4], entry->lights[5], entry->lights[6], entry->lights[7]); break;
        }
    }
}
#endif
