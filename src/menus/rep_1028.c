#include "menus/rep_1028.h"

extern MenuAnimArchive* lbl_2_bss_3401BC;
extern const f32 lbl_2_rodata_1080;
extern const f32 lbl_2_rodata_1078;
extern const f32 lbl_2_rodata_107C;

#include <string.h>
#include <math.h>

#include "static/UnknownHomes_Static.h"
#include "main/file_800A7C08.h"
#include "main/file_80011640.h"

// Effects are the ActorObjects of CharMgr.slots68 (main/file_800BD8C4.h).
typedef ActorObject MenuEffect;

// objects[i].actor of an ActorObjectTable, indexed through a void** the way the original does.
#define SLOT_ACTOR(table, i) \
    (((GameActor**)(table))[(i) * (s32)(sizeof(ActorObject) / sizeof(void*)) + (s32)(offsetof(ActorObjectTable, objects) / sizeof(void*))])
extern CharMgr* lbl_2_bss_340140[];
extern MenuTask* lbl_803CC1B8;
extern MenuData* lbl_2_bss_1A824C[];
extern void fn_2_3FA14(void);
extern void fn_2_46D34(s32 delta);
extern s32 lbl_2_data_38BC;

extern StadiumLights lbl_800F7478[]; // per stadium (main/file_80011640.h)

extern void fn_2_8AC84(s32 index, s32 value);
extern MenuCtx* lbl_2_bss_1A8248[];
extern MenuStateCallback lbl_2_data_308A4[4];
extern MenuStateCallback lbl_2_data_30898[3];
extern MenuStateCallback lbl_2_data_3088C[3];
extern MenuStateCallback lbl_2_data_30810[3];
extern MenuStateCallback lbl_2_data_3081C[3];
extern MenuStateCallback lbl_2_data_30828[3];
extern MenuStateCallback lbl_2_data_30834[3];
extern MenuStateCallback lbl_2_data_30840[3];
extern MenuStateCallback lbl_2_data_3084C[3];
extern MenuStateCallback lbl_2_data_30858[3];
extern MenuStateCallback lbl_2_data_30864[3];
extern MenuStateCallback lbl_2_data_30870[4];
extern MenuStateCallback lbl_2_data_30880[3];

extern MenuSpot lbl_2_data_3198[];
extern const f32 lbl_2_rodata_1084;
extern const f64 lbl_2_rodata_1088;
extern const f32 lbl_2_rodata_10B8[];
extern const f32 lbl_2_rodata_10BC;
extern void* lbl_2_data_30900[];
extern const f32 lbl_2_rodata_10A8[];
extern const f32 lbl_2_rodata_10AC[];
extern const f32 lbl_2_rodata_10B4[];
extern const f32 lbl_2_rodata_10B0;
extern MenuSpot lbl_2_data_369C[];

// .text:0x904A8 size:0x90
void fn_2_904A8(void) {
    MenuObject* slot;
    s32 i;
    for (i = 0; i < 29; i++) {
        slot = &lbl_2_bss_1A8248[0]->objects[i];
        slot->_78 = i;
        slot->_7C = i;
        slot->_84 = lbl_2_rodata_1080;
        slot->_38 = lbl_2_rodata_1080;
        slot->_3C = lbl_2_rodata_1080;
        slot->_AA = 0;
        slot->_92 = i;
        slot->_94 = -1;
        slot->_A8 = 0;
        slot->active = 0;
        slot->state = 0;
        slot->_AE = -1;
        slot->_AC = 0;
        slot->_AD = 0;
        slot->_80 = lbl_2_rodata_1080;
        slot->_A6 = 0;
        slot->_B2 = 0xFF;
        slot->_B4 = 0;
    }
}

// .text:0x8FC88 size:0x8C
void fn_2_8FC88(s32 index) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource = lbl_2_bss_3401BC->banks[0];
        MenuEffect* effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        u8 valid;
        effect->animBank = resource;
        effect->seqNum = 0;
        valid = resource != 0;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        effect->setSpeed = effect->setTime = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// .text:0x903A8 size:0x80
void fn_2_903A8(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    memcpy(slot, &lbl_2_data_369C[index].position, sizeof(Vec));
    slot->_30 = lbl_2_rodata_1080;
    slot->_28 = lbl_2_data_369C[index]._0C;
}

// .text:0x90428 size:0x80
void fn_2_90428(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    memcpy(slot, &lbl_2_data_3198[index].position, sizeof(Vec));
    slot->_30 = lbl_2_rodata_1080;
    slot->_28 = lbl_2_data_3198[index]._0C;
}

// .text:0x00091B7C size:0x4
void fn_2_91B7C(void) {}

// .text:0x00091B28 size:0x4
void fn_2_91B28(void) {}

// .text:0x00091C40 size:0xC
void fn_2_91C40(MenuObject* object) {
    object->state = 2;
}

// .text:0x00091B70 size:0xC
void fn_2_91B70(MenuObject* object) {
    object->state = 2;
}

// .text:0x00091B2C size:0xC
void fn_2_91B2C(MenuObject* object) {
    object->state = 1;
}

// .text:0x00091B1C size:0xC
void fn_2_91B1C(MenuObject* object) {
    object->state = 2;
}

// .text:0x000919C0 size:0xC
void fn_2_919C0(MenuObject* object) {
    object->state = 2;
}

// .text:0x000919B4 size:0xC
void fn_2_919B4(MenuObject* object) {
    object->state = 2;
}

// .text:0x000918E8 size:0xC
void fn_2_918E8(MenuObject* object) {
    object->state = 2;
}

// .text:0x00091C08 size:0x38
void fn_2_91C08(MenuStateObject* object) {
    lbl_2_data_30810[object->state](object);
}

// .text:0x00091B38 size:0x38
void fn_2_91B38(MenuStateObject* object) {
    lbl_2_data_3081C[object->state](object);
}

// .text:0x00091AE4 size:0x38
void fn_2_91AE4(MenuStateObject* object) {
    lbl_2_data_30828[object->state](object);
}

// .text:0x0009197C size:0x38
void fn_2_9197C(MenuStateObject* object) {
    lbl_2_data_30834[object->state](object);
}

// .text:0x000918A4 size:0x38
void fn_2_918A4(MenuStateObject* object) {
    lbl_2_data_30840[object->state](object);
}

// .text:0x000916C0 size:0x38
void fn_2_916C0(MenuStateObject* object) {
    lbl_2_data_3084C[object->state](object);
}

// .text:0x00091450 size:0x38
void fn_2_91450(MenuStateObject* object) {
    lbl_2_data_30858[object->state](object);
}

// .text:0x000911E0 size:0x38
void fn_2_911E0(MenuStateObject* object) {
    lbl_2_data_30864[object->state](object);
}

// .text:0x00090DAC size:0x38
void fn_2_90DAC(MenuStateObject* object) {
    lbl_2_data_30870[object->state](object);
}

// .text:0x00090BD0 size:0x38
void fn_2_90BD0(MenuStateObject* object) {
    lbl_2_data_30880[object->state](object);
}

void fn_2_918DC(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_9177C(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_9150C(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_9129C(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_90C08(MenuStateObject* object) {
    object->state = 3;
}

void fn_2_90AB0(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_90940(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_90934(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_9082C(MenuStateObject* object) {
    object->state = 2;
}

void fn_2_9061C(MenuStateObject* object) {
    object->state = 3;
}

void fn_2_909F4(MenuStateObject* object) {
    lbl_2_data_3088C[object->state](object);
}

void fn_2_908FC(MenuStateObject* object) {
    lbl_2_data_30898[object->state](object);
}

void fn_2_907F4(MenuStateObject* object) {
    lbl_2_data_308A4[object->state](object);
}

void fn_2_90E98(MenuObject* object) {
    MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
    entry->active = 0;
    entry->state = 0;
}

void fn_2_90C14(MenuObject* object) {
    if (object->_A0 == 1) {
        MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
        entry->active = 0;
        entry->state = 0;
    }
}

void fn_2_90838(MenuObject* object) {
    if (object->_A0 == 1) {
        fn_2_8AC84(object->_78, 0);
        object->_A0 = 2;
    }
    object->state = 2;
}

// fn_2_8F758, size:0x1C
void fn_2_8F758(s32 index, u8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xBC + 0x2288] = value;
}

// fn_2_8F73C, size:0x1C
void fn_2_8F73C(s32 index, u8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * 0xBC + 0x2294] = value;
}

// fn_2_8F720, size:0x1C
u8 fn_2_8F720(s32 index) {
    return ((u8*)lbl_2_bss_1A8248[0])[index * 0xBC + 0x2294];
}

// fn_2_90628, size:0x70
void fn_2_90628(MenuObject* object) {
    if (object->_A0 == 1) {
        fn_2_8AC84(object->_78, 0);
        object->_A0 = 2;
        {
            MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
            entry->active = 0;
            entry->state = 0;
        }
    }
}

// fn_2_8F688, size:0x48
void fn_2_8F688(void) {
    GXColor color = lbl_800F7478[0].ambient;
    color.a = 0xFF;
    fn_800BD2CC(0, color);
}

// fn_2_8F640, size:0x48
void fn_2_8F640(void) {
    GXColor color = lbl_800F7478[0].ambient;
    color.a = 0xFF;
    fn_800BD2CC(1, color);
}

// fn_2_8F774, size:0x3C
void fn_2_8F774(s32 index) {
    ActorObjectTable* data = lbl_2_bss_340140[0]->slots68;
    fn_800B4A94(SLOT_ACTOR(data, index));
}

// fn_2_916F8, size:0x84
void fn_2_916F8(MenuObject* object) {
    ActorObjectTable* data = lbl_2_bss_340140[0]->slots68;
    if (fn_800B4A94(SLOT_ACTOR(data, object->_78)) == 0.0f) {
        MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_91488, size:0x84
void fn_2_91488(MenuObject* object) {
    ActorObjectTable* data = lbl_2_bss_340140[0]->slots68;
    if (fn_800B4A94(SLOT_ACTOR(data, object->_78)) == 0.0f) {
        MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_91218, size:0x84
void fn_2_91218(MenuObject* object) {
    ActorObjectTable* data = lbl_2_bss_340140[0]->slots68;
    if (fn_800B4A94(SLOT_ACTOR(data, object->_78)) == 0.0f) {
        MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_90A2C, size:0x84
void fn_2_90A2C(MenuObject* object) {
    ActorObjectTable* data = lbl_2_bss_340140[0]->slots68;
    if (fn_800B4A94(SLOT_ACTOR(data, object->_78)) == 0.0f) {
        MenuObject* entry = &lbl_2_bss_1A8248[0]->objects[object->_78];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_9033C, size:0x6C
void fn_2_9033C(s32 index, const void* position, const f32* unused, f32 value, f32 unused2, f32 unused3) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    memcpy(slot, position, 0xC);
    slot->_28 = value;
    slot->_30 = 0.0f;
    slot->_28 = value;
}

// fn_2_8F7B0, size:0x88
void fn_2_8F7B0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[16];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8F838, size:0x88
void fn_2_8F838(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[15];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8F8C0, size:0x88
void fn_2_8F8C0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[14];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8F948, size:0x88
void fn_2_8F948(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[13];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8F9D0, size:0x88
void fn_2_8F9D0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[12];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8FA58, size:0x88
void fn_2_8FA58(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[11];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8FAE0, size:0x88
void fn_2_8FAE0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[10];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}


// fn_2_8FB68, size:0x90
void fn_2_8FB68(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        MenuAnimArchive* base = lbl_2_bss_3401BC;
        void* resource;
        MenuEffect* effect;
        u8 valid;
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        resource = base->banks[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// fn_2_8FBF8, size:0x90
void fn_2_8FBF8(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        MenuAnimArchive* base = lbl_2_bss_3401BC;
        void* resource;
        MenuEffect* effect;
        u8 valid;
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        resource = base->banks[index];
        effect->animBank = resource;
        effect->seqNum = type;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// .text:0x8F6D0 size:0x50
void fn_2_8F6D0(s32 index, s32 value) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    CharTrail* anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[value];
    }
}

// .text:0x90888 size:0x74
void fn_2_90888(MenuObject* object) {
    object->_8C = lbl_2_rodata_10AC[0];
    fn_2_8F6D0(object->_78, 5);
    object->_A0 = 0;
    object->state = 1;
}

// .text:0x90698 size:0x80
void fn_2_90698(MenuObject* object) {
    s16 timer = object->_9C;
    object->_9C = timer - 1;
    if (timer == 0) {
        object->_8C = lbl_2_rodata_10A8[0];
        fn_2_8F6D0(object->_78, 5);
        object->state = 2;
    }
}

// .text:0x90C4C size:0x84
void fn_2_90C4C(MenuObject* object) {
    s16 timer = object->_9C;
    object->_9C = timer - 1;
    if (timer == 0) {
        object->_8C = lbl_2_rodata_10B4[0];
        object->_A0 = 0;
        fn_2_8F6D0(object->_78, 3);
        object->state = 2;
    }
}

// .text:0x8FD14 size:0x9C
void fn_2_8FD14(void) {
    CharTrail* anim;
    CharTrail* dst;
    MenuObject* src;
    s32 i;
    for (i = 0; i < lbl_2_bss_340140[0]->_3078; i++) {
        anim = lbl_2_bss_340140[0]->trail2;
        if (anim != NULL) {
            dst = &anim[i];
            src = &lbl_2_bss_1A8248[0]->objects[i];
            memcpy(dst->_04, src, sizeof(Vec));
            dst->_04[4] = src->_28;
            dst->_26 = src->_AA;
        }
    }
}

// .text:0x90538 size:0xE4
void fn_2_90538(void) {
    MenuObject* slot;
    s32 i;
    for (i = 0; i < 29; i++) {
        slot = &lbl_2_bss_1A8248[0]->objects[i];
        memset(slot, 0, sizeof(*slot)); // 0xBC
        slot->_78 = i;
        slot->_7C = i;
        slot->_84 = lbl_2_rodata_1080;
        slot->_38 = lbl_2_rodata_1080;
        slot->_3C = lbl_2_rodata_1080;
        slot->_AA = 0;
        slot->_92 = i;
        slot->_94 = -1;
        slot->_A8 = 0;
        slot->active = 0;
        slot->state = 0;
        slot->_AE = -1;
        slot->_AC = 0;
        slot->_AD = 0;
        slot->_80 = lbl_2_rodata_1080;
        slot->_A6 = 0;
        slot->_B2 = 0xFF;
        slot->_B4 = 0;
    }
}

// .text:0x90718 size:0xDC
void fn_2_90718(MenuObject* object) {
    s32 index;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[12];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = 2;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
    object->_9C = 0x50;
    object->_A0 = 0;
    object->state = 1;
}

// .text:0x90DE4 size:0xB4
void fn_2_90DE4(MenuObject* object, f32 limit) {
    if (object->_B5 != 0) {
        f32 s = (f32)sin(object->_88);
        f32 v = lbl_2_rodata_10B8[0] * -s;
        object->_88 = object->_88 + lbl_2_rodata_10BC;
        if (v >= limit) {
            object->_88 = lbl_2_rodata_1080;
            v = lbl_2_rodata_1080;
            object->_B5 = 0;
        }
        object->position.y = v;
    } else {
        object->position.y = lbl_2_rodata_1080;
    }
}

// .text:0x8F528 size:0x118
void fn_2_8F528(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    GXColor color = lbl_800F7478[0].ambient;
    s32 alpha;
    switch (slot->_A6) {
    case 0:
        slot->_84 = lbl_2_rodata_1080;
        slot->_A6 = 1;
    case 1:
        slot->_84 = (f32)(slot->_84 + lbl_2_rodata_1088);
        alpha = (s32)(lbl_2_rodata_1084 * slot->_84);
        if (alpha < 0xFF) {
            color.a = 1;
            color.a = alpha;
            fn_800BD2CC(1, color);
        } else {
            color.a = 0xFF;
            fn_800BD2CC(0, color);
            slot->_A6 = 2;
        }
        break;
    case 2:
        slot->_84 = lbl_2_rodata_1080;
        break;
    }
}

// .text:0x8F27C size:0x158
void fn_2_8F27C(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    GXColor color = lbl_800F7478[0].ambient;
    s32 alpha;
    switch (slot->_A6) {
    case 0:
        fn_2_8AC84(slot->_78, 1);
        slot->_84 = lbl_2_rodata_1080;
        color.a = (s32)(lbl_2_rodata_1084 * slot->_84);
        fn_800BD2CC(1, color);
        slot->_A6 = 1;
        break;
    case 1:
        slot->_84 = slot->_84 + slot->_8C;
        alpha = (s32)(lbl_2_rodata_1084 * slot->_84);
        if (alpha < 0xFF) {
            color.a = 1;
            color.a = alpha;
            fn_800BD2CC(1, color);
        } else {
            color.a = 0xFF;
            fn_800BD2CC(0, color);
            slot->_A6 = 2;
        }
        break;
    case 2:
        slot->_84 = lbl_2_rodata_1080;
        break;
    }
}

// .text:0x91B80 size:0x88
void fn_2_91B80(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->state = 1;
}

// .text:0x918F4 size:0x88
void fn_2_918F4(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[2];
    }
    object->state = 1;
}

// .text:0x9094C size:0xA8
void fn_2_9094C(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 0);
    object->_8C = lbl_2_rodata_10B0;
    object->_A0 = 0;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[4];
    }
    object->state = 1;
}

// .text:0x8FDB0 size:0xEC
void fn_2_8FDB0(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    Mtx m;
    Vec v;
    if (!(slot->_30 <= lbl_2_rodata_1080)) {
        PSMTXRotRad(m, 'Y', slot->_44);
        v.x = lbl_2_rodata_1080;
        v.y = lbl_2_rodata_1080;
        v.z = -slot->_30;
        PSMTXMultVec(m, &v, &v);
        slot->_18 = v.x;
        slot->_1C = v.z;
        slot->position.x = slot->position.x + slot->_18;
        slot->position.z = slot->position.z + slot->_1C;
    }
    slot->_0C = slot->position.x;
    slot->_14 = slot->position.z;
    if (lbl_2_rodata_1080 == slot->_30) {
        slot->_20 = lbl_2_rodata_1080;
        slot->_24 = lbl_2_rodata_1080;
    }
}

// .text:0x90ABC size:0x114
void fn_2_90ABC(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[10];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->state = 1;
}

// .text:0x919CC size:0x118
void fn_2_919CC(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[0];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = 0;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->state = 1;
}

// .text:0x91518 size:0x1A8
void fn_2_91518(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    if (index == 0x19) {
        if (lbl_2_bss_3401BC != NULL) {
            void* resource;
            MenuEffect* effect;
            u8 valid;
            resource = lbl_2_bss_3401BC->banks[14];
            effect = &lbl_2_bss_340140[0]->slots68->objects[index];
            effect->animBank = resource;
            effect->seqNum = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setAnimation = 1;
            valid = resource != 0;
            effect->setTime = valid;
            effect->setSpeed = valid;
            effect->speed = lbl_2_rodata_1080;
            effect->unk54 = lbl_2_rodata_1078;
            effect->setSpeed = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setTime = 1;
            effect->visFlags = 3;
        }
    } else {
        if (lbl_2_bss_3401BC != NULL) {
            void* resource;
            MenuEffect* effect;
            u8 valid;
            resource = lbl_2_bss_3401BC->banks[15];
            effect = &lbl_2_bss_340140[0]->slots68->objects[index];
            effect->animBank = resource;
            effect->seqNum = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setAnimation = 1;
            valid = resource != 0;
            effect->setTime = valid;
            effect->setSpeed = valid;
            effect->speed = lbl_2_rodata_1080;
            effect->unk54 = lbl_2_rodata_1078;
            effect->setSpeed = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setTime = 1;
            effect->visFlags = 3;
        }
    }
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->state = 1;
}

// .text:0x912A8 size:0x1A8
void fn_2_912A8(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    if (index == 0x19) {
        if (lbl_2_bss_3401BC != NULL) {
            void* resource;
            MenuEffect* effect;
            u8 valid;
            resource = lbl_2_bss_3401BC->banks[14];
            effect = &lbl_2_bss_340140[0]->slots68->objects[index];
            effect->animBank = resource;
            effect->seqNum = 3;
            effect->time = lbl_2_rodata_1080;
            effect->setAnimation = 1;
            valid = resource != 0;
            effect->setTime = valid;
            effect->setSpeed = valid;
            effect->speed = lbl_2_rodata_1080;
            effect->unk54 = lbl_2_rodata_1078;
            effect->setSpeed = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setTime = 1;
            effect->visFlags = 3;
        }
    } else {
        if (lbl_2_bss_3401BC != NULL) {
            void* resource;
            MenuEffect* effect;
            u8 valid;
            resource = lbl_2_bss_3401BC->banks[15];
            effect = &lbl_2_bss_340140[0]->slots68->objects[index];
            effect->animBank = resource;
            effect->seqNum = 3;
            effect->time = lbl_2_rodata_1080;
            effect->setAnimation = 1;
            valid = resource != 0;
            effect->setTime = valid;
            effect->setSpeed = valid;
            effect->speed = lbl_2_rodata_1080;
            effect->unk54 = lbl_2_rodata_1078;
            effect->setSpeed = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setTime = 1;
            effect->visFlags = 3;
        }
    }
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->state = 1;
}

// .text:0x8F3D4 size:0x154
void fn_2_8F3D4(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    GXColor color = lbl_800F7478[0].ambient;
    s32 alpha;
    switch (slot->_A6) {
    case 0:
        color.a = 0xFF;
        slot->_84 = lbl_2_rodata_1078;
        slot->_A6 = 1;
        fn_800BD2CC(1, color);
    case 1:
        slot->_A6 = 2;
    case 2:
        slot->_84 = slot->_84 - slot->_8C;
        alpha = (s32)(lbl_2_rodata_107C * slot->_84);
        if (alpha > 1) {
            color.a = alpha;
            fn_800BD2CC(1, color);
        } else {
            color.a = 0;
            fn_800BD2CC(1, color);
            slot->_A6 = 3;
        }
        break;
    case 3:
        color.a = 0;
        fn_800BD2CC(1, color);
        slot->_A0 = 1;
        slot->_84 = lbl_2_rodata_1080;
        break;
    }
}

// .text:0x8F0F4 size:0x188
void fn_2_8F0F4(s32 index) {
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    GXColor color = lbl_800F7478[0].ambient;
    s32 alpha;
    switch (slot->_A6) {
    case 0:
        color.a = 0xFF;
        slot->_84 = lbl_2_rodata_1078;
        slot->_A6 = 1;
        fn_800BD2CC(1, color);
    case 1:
        slot->_84 = slot->_84 - slot->_8C;
        alpha = (s32)(lbl_2_rodata_107C * slot->_84);
        if (alpha > 1) {
            color.a = alpha;
            fn_800BD2CC(1, color);
        } else {
            color.a = 0;
            fn_800BD2CC(1, color);
            slot->_A6 = 2;
        }
        break;
    case 2:
        color.a = 0;
        fn_800BD2CC(1, color);
        slot->_A0 = 1;
        slot->_84 = lbl_2_rodata_1080;
        slot->_A6 = 3;
        break;
    case 3:
        if (slot->_A0 == 2) {
            color.a = 0xFF;
            fn_800BD2CC(0, color);
            slot->_A6 = 4;
        }
        break;
    }
}

// .text:0x91058 size:0x188
void fn_2_91058(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* anim;
    MenuCtx* g = lbl_2_bss_1A8248[0];
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect;
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[16];
        effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        effect->animBank = resource;
        effect->seqNum = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        valid = resource != 0;
        effect->setTime = valid;
        effect->setSpeed = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    anim = lbl_2_bss_340140[0]->trail2;
    if (anim != NULL) {
        slot->_A6 = 0;
        anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->_B5 = 1;
    object->_88 = lbl_2_rodata_10BC;
    object->position.y = lbl_2_rodata_1080;
    object->_28 = lbl_2_rodata_1080;
    object->_28 = lbl_2_rodata_1080;
    fn_80062890(0x40);
    object->_2C = (f32)atan2(-(g->entries[0].position.x - g->entries[1].position.x), -(g->entries[0].position.z - g->entries[1].position.z));
    object->state = 1;
}

// .text:0x90EC4 size:0x194
void fn_2_90EC4(MenuObject* object) {
    Mtx m;
    Vec v;
    MenuTask* queue = lbl_803CC1B8;
    if (object->_B5 != 0) {
        f32 s = (f32)sin(object->_88);
        f32 v = lbl_2_rodata_10B8[0] * -s;
        object->_88 = object->_88 + lbl_2_rodata_10BC;
        if (v >= 0.0f) {
            object->_88 = 0.0f;
            v = 0.0f;
            object->_B5 = 0;
        }
        object->position.y = v;
    } else {
        object->position.y = 0.0f;
    }
    PSMTXRotRad(m, 'Y', object->_2C);
    v.x = lbl_2_rodata_1080;
    v.y = lbl_2_rodata_1080;
    v.z = lbl_2_rodata_10A8[0];
    PSMTXMultVec(m, &v, &v);
    object->position.x = object->position.x - v.x;
    object->position.z = object->position.z - v.z;
    if (object->position.y >= lbl_2_rodata_1080) {
        fn_2_46D34(lbl_2_data_38BC);
        if (lbl_2_bss_1A8248[0]->_43BE < 0x3E7) {
            MenuTask* q = fn_800B0A5C_insertQueue((void*)fn_2_3FA14, 2);
            q->step = 0;
            queue->_10 = 0;
        } else {
            lbl_2_bss_1A824C[0]->_197740 = 1;
        }
        object->state = 2;
    }
}

// fn_2_91C4C, size:0x128
void fn_2_91C4C(MenuObject* object) {
    s32 index = object->_78;
    u8 st = object->_A8;
    if (st == 1) {
        if (lbl_2_bss_3401BC != NULL) {
            MenuEffect* effect = (MenuEffect*)((u8*)lbl_2_bss_340140[0]->slots68 + index * sizeof(ActorObject) + offsetof(ActorObjectTable, objects));
            effect->unk54 = lbl_2_rodata_1080;
            effect->setSpeed = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setTime = 1;
            effect->visFlags = 2;
            effect->setAnimation = 0;
            object->state = 2;
        }
    } else if (st == 2) {
        if (fn_800B4A94(((ActorObject*)((u8*)lbl_2_bss_340140[0]->slots68 + index * sizeof(ActorObject) + offsetof(ActorObjectTable, objects)))->actor) == lbl_2_rodata_1080
            && lbl_2_bss_3401BC != NULL) {
            MenuEffect* effect = (MenuEffect*)((u8*)lbl_2_bss_340140[0]->slots68 + index * sizeof(ActorObject) + offsetof(ActorObjectTable, objects));
            effect->unk54 = lbl_2_rodata_1080;
            effect->setSpeed = 1;
            effect->time = lbl_2_rodata_1080;
            effect->setTime = 1;
            effect->visFlags = 2;
            effect->setAnimation = 0;
            object->state = 2;
        }
    }
}

static inline void setupEffect(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        void* resource;
        MenuEffect* effect = &lbl_2_bss_340140[0]->slots68->objects[index];
        u8 valid;
        resource = lbl_2_bss_3401BC->banks[index];
        effect->animBank = resource;
        effect->seqNum = type;
        valid = resource != 0;
        effect->time = lbl_2_rodata_1080;
        effect->setAnimation = 1;
        effect->setSpeed = effect->setTime = valid;
        effect->speed = lbl_2_rodata_1080;
        effect->unk54 = lbl_2_rodata_1078;
        effect->setSpeed = 1;
        effect->time = lbl_2_rodata_1080;
        effect->setTime = 1;
        effect->visFlags = 3;
    }
}

// .text:0x90CD0 size:0xDC
void fn_2_90CD0(MenuObject* object) {
    fn_2_8AC84(object->_78, 1);
    setupEffect(object->_78, 0);
    object->_9C = 0x1C;
    object->state = 1;
}

// .text:0x91D74 size:0x620
void fn_2_91D74(MenuObject* object) {
    fn_2_8AC84(object->_78, 1);
    if (object->_78 >= 1 && object->_78 <= 7) {
        setupEffect(object->_78, 0);
    } else if (object->_78 == 8) {
        setupEffect(object->_78, 0);
    } else if (object->_78 >= 10 && object->_78 <= 15) {
        fn_2_8FAE0(object->_78, 0);
    } else if (object->_78 == 22) {
        fn_2_8FA58(object->_78, 0);
    } else if (object->_78 == 24) {
        fn_2_8F9D0(object->_78, 0);
    } else if (object->_78 == 27) {
        fn_2_8F948(object->_78, 0);
    } else if (object->_78 == 25) {
        fn_2_8F8C0(object->_78, 0);
    } else if (object->_78 == 26) {
        fn_2_8F838(object->_78, 0);
    } else if (object->_78 == 28) {
        fn_2_8F7B0(object->_78, 0);
    }
    {
        // inlined fn_2_8F6D0(index, 0)
        s32 index = object->_78;
        MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
        CharTrail* anim = lbl_2_bss_340140[0]->trail2;
        if (anim != NULL) {
            slot->_A6 = 0;
            anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
        }
    }
    object->state = 1;
}

// .text:0x91788 size:0x11C
void fn_2_91788(MenuObject* object) {
    fn_2_8AC84(object->_78, 1);
    setupEffect(object->_78, 1);
    {
        // inlined fn_2_8F6D0(index, 0)
        s32 index = object->_78;
        MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
        CharTrail* anim = lbl_2_bss_340140[0]->trail2;
        if (anim != NULL) {
            slot->_A6 = 0;
            anim[index].draw = (void (*)(void))lbl_2_data_30900[0];
        }
    }
    object->state = 1;
}

extern f32 fn_2_4A1E8(f32 x, f32 y);
// .bss (mwcc emits file statics in reverse order of definition).
static f32 lbl_2_bss_B640;
static u8 lbl_2_bss_B2C8[0x378]; // unreferenced
extern Vec lbl_2_data_308F4;
extern const f32 lbl_2_rodata_1090;
extern const f32 lbl_2_rodata_1094;
extern const f32 lbl_2_rodata_1098;

#if NONMATCHING
// Moves cursor slot `index` with the stick (x/z) and d-pad up/down (y); body of fn_2_8FE9C.
static inline void moveSlotWithPad(s32 index) {
    f32 x;
    f32 z;
    Vec position;
    Vec direction;
    PadState* pad;
    MenuObject* slot = &lbl_2_bss_1A8248[0]->objects[index];
    memcpy(&position, slot, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_308F4, &direction);
    x = direction.x * lbl_2_rodata_1090;
    z = direction.z * lbl_2_rodata_1090;
    direction.x = x;
    direction.z = z;
    pad = &((PadState*)&lbl_803C77B8)[lbl_2_bss_1A824C[0]->port];
    position.x += pad->sticks.stickX / lbl_2_rodata_1094;
    position.z += pad->sticks.stickY / lbl_2_rodata_1094;
    if (lbl_2_rodata_1080 != x || lbl_2_rodata_1080 != z) {
        lbl_2_bss_B640 = fn_2_4A1E8(direction.z, x);
    }
    if (((PadState*)&lbl_803C77B8)[lbl_2_bss_1A824C[0]->port].repeat & 0x40) {
        position.y -= lbl_2_rodata_1098;
    } else if (((PadState*)&lbl_803C77B8)[lbl_2_bss_1A824C[0]->port].repeat & 0x20) {
        position.y += lbl_2_rodata_1098;
    }
    memcpy(&lbl_2_data_308F4, slot, sizeof(Vec));
    slot->position.x = position.x;
    slot->position.y = position.y;
    slot->position.z = position.z;
    slot->_44 = lbl_2_bss_B640;
}

// NONMATCHING 89%: scheduling only (lbl_803C77B8 address hoisted to the top, f-reg numbering)
// .text:0x8FE9C size:0x1E0
void fn_2_8FE9C(s32 index) {
    moveSlotWithPad(index);
}

// NONMATCHING 92%: inlined fn_2_8FE9C body has the same scheduling difference, stack slots differ
// .text:0x9007C size:0x2C0
void fn_2_9007C(void) {
    Mtx m;
    Vec v;
    s32 index = lbl_2_bss_1A824C[0]->_1972BE;
    MenuObject* slot;
    moveSlotWithPad(index);
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    if (!(slot->_30 <= lbl_2_rodata_1080)) {
        PSMTXRotRad(m, 'Y', slot->_44);
        v.x = lbl_2_rodata_1080;
        v.y = lbl_2_rodata_1080;
        v.z = -slot->_30;
        PSMTXMultVec(m, &v, &v);
        slot->_18 = v.x;
        slot->_1C = v.z;
        slot->position.x = slot->position.x + slot->_18;
        slot->position.z = slot->position.z + slot->_1C;
    }
    slot->_0C = slot->position.x;
    slot->_14 = slot->position.z;
    if (lbl_2_rodata_1080 == slot->_30) {
        slot->_20 = lbl_2_rodata_1080;
        slot->_24 = lbl_2_rodata_1080;
    }
}
#endif

// ---- 0x92394..0x927C8: the object state handlers at the end of this unit's .text
// (once a separate auto split; they share this unit's pooled lbl_2_data_30900
// statics and the lbl_2_data_308B4 handler table).
#include "menus/auto_00_00092394_text.h"


extern void (*lbl_2_data_308B4[])(MenuObject* object);
extern void (*lbl_2_data_307F0[])(MenuObject* object);
extern void (*lbl_2_data_307F8[])(MenuObject* object);
extern void (*lbl_2_data_30804[])(MenuObject* object);

// fn_2_923CC, size:0xC
void fn_2_923CC(MenuObject* object) {
    object->state = 2;
}

// fn_2_923D8, size:0xC
void fn_2_923D8(MenuObject* object) {
    object->state = 2;
}

// fn_2_923E4, size:0x88
void fn_2_923E4(MenuObject* object) {
    s32 index;
    MenuObject* slot;
    CharTrail* p;
    fn_2_8AC84(object->_78, 1);
    index = object->_78;
    slot = &lbl_2_bss_1A8248[0]->objects[index];
    p = lbl_2_bss_340140[0]->trail2;
    if (p != NULL) {
        slot->_A6 = 0;
        p[index].draw = (void (*)(void))lbl_2_data_30900[0];
    }
    object->state = 1;
}

// fn_2_924A4, size:0xC
void fn_2_924A4(MenuObject* object) {
    object->state = 1;
}

// fn_2_92394, size:0x38
void fn_2_92394(MenuObject* object) {
    lbl_2_data_30804[object->state](object);
}

// fn_2_9246C, size:0x38
void fn_2_9246C(MenuObject* object) {
    lbl_2_data_307F8[object->state](object);
}

// fn_2_92504, size:0x38
void fn_2_92504(MenuObject* object) {
    lbl_2_data_307F0[object->state](object);
}

// fn_2_9253C, size:0x40
void fn_2_9253C(MenuObject* object) {
    PTR32_SET(object->update, lbl_2_data_308B4[object->active]);
    PTR32_GET(MenuObjectUpdateFn, object->update)(object);
}

// fn_2_9257C, size:0xD8
void fn_2_9257C(void) {
    s32 i;
    MenuData* work;

    if (lbl_2_bss_1A8248[0]->_44F2 == 1 || lbl_2_bss_1A8248[0]->_44F2 == 2 ||
        lbl_2_bss_1A8248[0]->_44F2 == 3) {
        return;
    }
    for (i = 0; i < 29; i++) {
        fn_2_9253C(&lbl_2_bss_1A8248[0]->objects[i]);
    }
    work = lbl_2_bss_1A824C[0];
    if (work->_1972C0 != 0) {
        work->_1972C0 = 0;
#if NONMATCHING
        fn_800B0A14_removeQueue(NULL); // the argument is unused
#else
        REMOVE_QUEUE_NOARG(); // original passes a stale r3
#endif
    }
}

// fn_2_92654, size:0x28
void fn_2_92654(s32 index, u8 state) {
    MenuObject* object = &lbl_2_bss_1A8248[0]->objects[index];
    object->active = state;
    object->state = 0;
}

// fn_2_924B0, size:0x54
void fn_2_924B0(MenuObject* object) {
    GXColor color = lbl_800F7478[0].ambient;
    fn_2_8AC84(object->_78, 0);
    color.a = 0xFF;
    fn_800BD2CC(0, color);
}


// fn_2_9267C, size:0x14C
void fn_2_9267C(Vec* result, Vec* position, Vec* anchor, Vec* target,
               f32 step, f32 spring, f32 damping, f32 restDistance) {
    Vec direction;
    Vec velocity;
    Vec displacement;
    f32 distance;
    f32 force;
    PSVECSubtract(position, anchor, &direction);
    distance = PSVECDistance(position, anchor);
    PSVECSubtract(target, anchor, &displacement);
    PSVECScale(&displacement, step, &velocity);
    force = spring * (restDistance - distance) +
            damping * (PSVECDotProduct(&velocity, &direction) / distance);
    PSVECNormalize(&direction, &direction);
    PSVECScale(&direction, force * step, &direction);
    PSVECAdd(position, &direction, position);
    *result = *position;
}

// ---- .data 0x307F0..0x30918 (the .data before it, 0x2FFF8..0x307EC, is rep_0FD8's)

void (*lbl_2_data_307F0[2])(MenuObject* object) = {
    (void (*)(MenuObject*))fn_2_924B0,
    (void (*)(MenuObject*))fn_2_924A4,
};

void (*lbl_2_data_307F8[3])(MenuObject* object) = {
    (void (*)(MenuObject*))fn_2_923E4,
    (void (*)(MenuObject*))fn_2_923D8,
    (void (*)(MenuObject*))fn_2_923CC,
};

void (*lbl_2_data_30804[3])(MenuObject* object) = {
    (void (*)(MenuObject*))fn_2_91D74,
    (void (*)(MenuObject*))fn_2_91C4C,
    (void (*)(MenuObject*))fn_2_91C40,
};

MenuStateCallback lbl_2_data_30810[3] = {
    (MenuStateCallback)fn_2_91B80,
    (MenuStateCallback)fn_2_91B7C,
    (MenuStateCallback)fn_2_91B70,
};

MenuStateCallback lbl_2_data_3081C[3] = {
    (MenuStateCallback)fn_2_91B2C,
    (MenuStateCallback)fn_2_91B28,
    (MenuStateCallback)fn_2_91B1C,
};

MenuStateCallback lbl_2_data_30828[3] = {
    (MenuStateCallback)fn_2_919CC,
    (MenuStateCallback)fn_2_919C0,
    (MenuStateCallback)fn_2_919B4,
};

MenuStateCallback lbl_2_data_30834[3] = {
    (MenuStateCallback)fn_2_918F4,
    (MenuStateCallback)fn_2_918E8,
    (MenuStateCallback)fn_2_918DC,
};

MenuStateCallback lbl_2_data_30840[3] = {
    (MenuStateCallback)fn_2_91788,
    (MenuStateCallback)fn_2_9177C,
    (MenuStateCallback)fn_2_916F8,
};

MenuStateCallback lbl_2_data_3084C[3] = {
    (MenuStateCallback)fn_2_91518,
    (MenuStateCallback)fn_2_9150C,
    (MenuStateCallback)fn_2_91488,
};

MenuStateCallback lbl_2_data_30858[3] = {
    (MenuStateCallback)fn_2_912A8,
    (MenuStateCallback)fn_2_9129C,
    (MenuStateCallback)fn_2_91218,
};

MenuStateCallback lbl_2_data_30864[3] = {
    (MenuStateCallback)fn_2_91058,
    (MenuStateCallback)fn_2_90EC4,
    (MenuStateCallback)fn_2_90E98,
};

MenuStateCallback lbl_2_data_30870[4] = {
    (MenuStateCallback)fn_2_90CD0,
    (MenuStateCallback)fn_2_90C4C,
    (MenuStateCallback)fn_2_90C14,
    (MenuStateCallback)fn_2_90C08,
};

MenuStateCallback lbl_2_data_30880[3] = {
    (MenuStateCallback)fn_2_90ABC,
    (MenuStateCallback)fn_2_90AB0,
    (MenuStateCallback)fn_2_90A2C,
};

MenuStateCallback lbl_2_data_3088C[3] = {
    (MenuStateCallback)fn_2_9094C,
    (MenuStateCallback)fn_2_90940,
    (MenuStateCallback)fn_2_90934,
};

MenuStateCallback lbl_2_data_30898[3] = {
    (MenuStateCallback)fn_2_90888,
    (MenuStateCallback)fn_2_90838,
    (MenuStateCallback)fn_2_9082C,
};

MenuStateCallback lbl_2_data_308A4[4] = {
    (MenuStateCallback)fn_2_90718,
    (MenuStateCallback)fn_2_90698,
    (MenuStateCallback)fn_2_90628,
    (MenuStateCallback)fn_2_9061C,
};

void (*lbl_2_data_308B4[16])(MenuObject* object) = {
    (void (*)(MenuObject*))fn_2_92504,
    (void (*)(MenuObject*))fn_2_9246C,
    (void (*)(MenuObject*))fn_2_92394,
    (void (*)(MenuObject*))fn_2_91C08,
    (void (*)(MenuObject*))fn_2_91B38,
    (void (*)(MenuObject*))fn_2_91AE4,
    (void (*)(MenuObject*))fn_2_9197C,
    (void (*)(MenuObject*))fn_2_918A4,
    (void (*)(MenuObject*))fn_2_916C0,
    (void (*)(MenuObject*))fn_2_91450,
    (void (*)(MenuObject*))fn_2_911E0,
    (void (*)(MenuObject*))fn_2_90DAC,
    (void (*)(MenuObject*))fn_2_90BD0,
    (void (*)(MenuObject*))fn_2_909F4,
    (void (*)(MenuObject*))fn_2_908FC,
    (void (*)(MenuObject*))fn_2_907F4,
};

Vec lbl_2_data_308F4 = {0.0f, 0.0f, 0.0f};

// Stored into the animation slots (fn_2_8F7B0..); first entries of this unit's pooled statics.
void* lbl_2_data_30900[6] = {
    (void*)fn_2_8F688,
    (void*)fn_2_8F640,
    (void*)fn_2_8F528,
    (void*)fn_2_8F3D4,
    (void*)fn_2_8F27C,
    (void*)fn_2_8F0F4,
};
