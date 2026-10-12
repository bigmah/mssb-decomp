#include "menus/rep_0B08.h"

extern const f32 lbl_2_rodata_B6C[];
extern const f32 lbl_2_rodata_C28;

#include <string.h>
#include <math.h>

#include "static/UnknownHomes_Static.h"
#include "main/file_80011640.h"
extern const f32 lbl_2_rodata_BA0;

extern u8 lbl_800F7478[];

extern void fn_2_69E1C(s32 index);


extern f64 __fabs(f64 value);
extern const f32 lbl_2_rodata_BA8;

extern MenuCtx* lbl_2_bss_1A8248[];
extern const f32 lbl_2_rodata_B58;
extern f32 fn_2_4A18C(f32);
extern const Vec lbl_2_data_2EA4[];
extern const f64 lbl_2_rodata_C30;
extern const f32 lbl_2_rodata_C3C;
extern const f32 lbl_2_rodata_C38;
extern const f32 lbl_2_rodata_B5C;
extern const f32 lbl_2_rodata_B60;
extern const f32 lbl_2_rodata_B64;
extern const f32 lbl_2_rodata_B68[];
extern f32 lbl_2_data_3EF4[];
extern f32 lbl_2_data_3F5C;
extern const Vec lbl_2_data_3150[];
extern const f32 lbl_2_rodata_BAC[];
extern const f64 lbl_2_rodata_BE0;
extern const f64 lbl_2_rodata_BE8;
extern const f32 lbl_2_rodata_C40;

// fn_2_6F78C, size:0x100
void fn_2_6F78C(MenuEntry* entry) {
    f32 difference;

    entry->heading = (f32)atan2(-(lbl_2_bss_1A8248[0]->entries[0].position.x - entry->position.x),
        -(lbl_2_bss_1A8248[0]->entries[0].position.z - entry->position.z));
    difference = fn_2_4A18C(entry->angle34 - entry->heading);
    if ((difference < lbl_2_rodata_BE0 && difference > lbl_2_rodata_B58) ||
        (difference > lbl_2_rodata_BE8 && difference < lbl_2_rodata_B58)) {
        entry->state = 3;
    } else if (difference < lbl_2_rodata_B58) {
        entry->angle34 += lbl_2_rodata_C40;
    } else {
        entry->angle34 -= lbl_2_rodata_C40;
    }
    entry->heading = entry->angle34;
}

extern MenuData* lbl_2_bss_1A824C[];
// .bss 0xA170..0xA840 (mwcc emits file statics in reverse order of definition).
static u8 lbl_2_bss_A174[0x6CC]; // unreferenced
static f32 lbl_2_bss_A170;
extern Vec lbl_2_data_2A340;
extern const f32 lbl_2_rodata_BB0;
extern const f32 lbl_2_rodata_C10;
extern f32 fn_2_4A1E8(f32 x, f32 y);

// fn_2_6B024, size:0xFC
void fn_2_6B024(MenuEntry* owner) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[owner->objectId];
    f32 height;

    if (entry->flagD0 != 0) {
        height = -sinf_kludge(entry->bouncePhase);
        height = lbl_2_rodata_BA8 * height;
        entry->bouncePhase += lbl_2_rodata_BAC[0];
        if (entry->position.y > 0.0f) {
            entry->bouncePhase = 0.0f;
            height = 0.0f;
            entry->flagD0 = 0;
            if (entry->typeC3 == 19) {
                ((u8*)lbl_2_bss_1A8248[0])[entry->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
            }
        }
        entry->position.y = height;
    } else {
        entry->position.y = 0.0f;
    }
    if (owner->flagD0 == 0) {
        owner->flagC4 = 1;
    }
}

// fn_2_687A4, size:0x100
u8 fn_2_687A4(s32 index, s32 targetIndex, s32 location) {
    Vec position;
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    MenuEntry* target = &lbl_2_bss_1A8248[0]->entries[targetIndex];
    f32 bearing = (f32)atan2(-(target->position.x - entry->position.x),
        -(target->position.z - entry->position.z));

    memcpy(&position, &lbl_2_data_2EA4[location], sizeof(Vec));
    bearing -= (f32)atan2(-(position.x - entry->position.x), -(position.z - entry->position.z));
    if (bearing < lbl_2_rodata_B5C && bearing > lbl_2_rodata_B60) {
        return 1;
    }
    return 0;
}

// fn_2_68A88, size:0xCC
s32 fn_2_68A88(s32 index, s32 location) {
    Vec scaled;
    const Vec* point;
    MenuEntry* entry;
    f32 distance;
    f32 limit;
    f32 bias;
    point = &lbl_2_bss_1A8248[0]->objects[location].position;
    entry = &lbl_2_bss_1A8248[0]->entries[index];

    scaled.x = point->x * lbl_2_rodata_B68[0];
    scaled.y = point->y * lbl_2_rodata_B68[0];
    scaled.z = point->z * lbl_2_rodata_B68[0];
    distance = PSVECDistance(&entry->position, &scaled);
    limit = lbl_2_data_3EF4[lbl_2_bss_1A8248[0]->_441C];
    bias = lbl_2_data_3F5C;
    bias = limit + bias;
    if (distance < bias && (u8)entry->flagC0 != 0) {
        return 1;
    }
    return 0;
}

// fn_2_6A628, size:0xE0
void fn_2_6A628(void) {
    Mtx rotation;
    Vec movement;
    MenuCtx* menu = lbl_2_bss_1A8248[0];

    if (!(menu->entries[0]._38 <= lbl_2_rodata_B58)) {
        PSMTXRotRad(rotation, 'Y', menu->entries[0].heading);
        movement.x = lbl_2_rodata_B58;
        movement.y = lbl_2_rodata_B58;
        movement.z = -menu->entries[0]._38;
        PSMTXMultVec(rotation, &movement, &movement);
        menu->entries[0].velocity.x = movement.x;
        menu->entries[0].velocity.z = movement.z;
        menu->entries[0].position.x += menu->entries[0].velocity.x;
        menu->entries[0].position.z += menu->entries[0].velocity.z;
    }
    menu->entries[0].previousPosition.x = menu->entries[0].position.x;
    menu->entries[0].previousPosition.z = menu->entries[0].position.z;
    if (lbl_2_rodata_B58 == menu->entries[0]._38) {
        menu->entries[0].acceleration.x = lbl_2_rodata_B58;
        menu->entries[0].acceleration.z = lbl_2_rodata_B58;
    }
}

// fn_2_6832C, size:0xC0
void fn_2_6832C(void) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[1];
    f32 heading;
    MenuCtx* state;

    memcpy(&entry->position, &lbl_2_data_2EA4[5], sizeof(Vec));
    entry->previousPosition.x = lbl_2_rodata_B58;
    entry->previousPosition.y = lbl_2_rodata_B58;
    entry->previousPosition.z = lbl_2_rodata_B58;
    entry->velocity.x = lbl_2_rodata_B58;
    entry->velocity.y = lbl_2_rodata_B58;
    entry->velocity.z = lbl_2_rodata_B58;
    entry->storedX = entry->position.x;
    entry->storedZ = entry->position.z;
    entry->_38 = lbl_2_rodata_B58;
    entry->flagBB = 0;
    heading = entry->heading;
    entry->angle34 = heading;
    entry->angle30 = heading;
    lbl_2_bss_1A8248[0]->entries[1].locationIndex = 5;
    state = lbl_2_bss_1A8248[0];
    state->entries[1].typeC3 = 6;
    state->entries[1].state = 0;
    lbl_2_bss_1A8248[0]->_442F = 1;
}

// fn_2_6AB3C, size:0xC0
void fn_2_6AB3C(s32 index, const Vec* position, f32 heading) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 x;
    f32 z;
    f32 angle;

    memcpy(&entry->position, position, sizeof(Vec));
    entry->previousPosition.x = lbl_2_rodata_B58;
    entry->previousPosition.y = lbl_2_rodata_B58;
    entry->previousPosition.z = lbl_2_rodata_B58;
    entry->velocity.x = lbl_2_rodata_B58;
    entry->velocity.y = lbl_2_rodata_B58;
    entry->velocity.z = lbl_2_rodata_B58;
    entry->angle30 = heading;
    entry->storedX = entry->position.x;
    entry->storedZ = entry->position.z;
    entry->_38 = lbl_2_rodata_B58;
    entry->flagBB = 0;
    x = -entry->position.x;
    z = -entry->position.z;
    angle = (f32)atan2(-x, -z);
    entry->angle34 = angle;
    entry->angle30 = angle;
}
extern MenuData* lbl_2_bss_1A824C[];

typedef struct {
    s16 clip;
    s16 end;
    u8 mode;
    u8 padding;
} MenuAnimation;

extern MenuAnimation lbl_2_data_3C84[];
extern void fn_2_8CD58(s32, s16, u8, u8, s16, u8, u8);
extern s32 fn_2_8CC88(s32 index);
extern s32 lbl_2_data_3C40[];
extern s32 lbl_2_data_3C5C[];

// fn_2_68F24, size:0x98
void fn_2_68F24(s32 index, s32 animation) {
    MenuEntry* entry;
    MenuAnimation* settings;
    s16* cache;

    entry = &lbl_2_bss_1A8248[0]->entries[index];
    settings = &lbl_2_data_3C84[animation];
    fn_2_8CD58(entry->objectId, settings->clip, settings->mode, 1, settings->end, 0, 0);
    cache = lbl_2_bss_1A824C[0]->_197756;
    cache[entry->objectId] = animation;
}

// fn_2_689CC, size:0xBC
s16 fn_2_689CC(s32 index) {
    Vec position;
    Vec candidate;
    f32 distance;
    f32 nearest;
    s32 current;
    s32 closest;

    nearest = lbl_2_rodata_B64;
    closest = 0;
    memcpy(&position, &lbl_2_bss_1A8248[0]->entries[index].position, sizeof(position));
    for (current = 0; current < 51; current++) {
        memcpy(&candidate, &lbl_2_data_2EA4[current], sizeof(candidate));
        distance = PSVECDistance(&position, &candidate);
        if (distance < nearest) {
            nearest = distance;
            closest = current;
        }
    }
    return closest;
}

// fn_2_686EC, size:0xB8
s32 fn_2_686EC(s32 from, s32 to) {
    f32 angle = fn_2_68940(from, to);
    if (angle < lbl_2_rodata_B5C && angle > lbl_2_rodata_B60) {
        return 1;
    }
    return 0;
}

// fn_2_6BAD8, size:0xA4
void fn_2_6BAD8(MenuFadeState* fade) {
    s32 alpha;
    fade->progress = (f32)((f64)fade->progress - lbl_2_rodata_C30);
    alpha = (s32)(lbl_2_rodata_C38 * fade->progress);
    if (alpha > 1) {
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = alpha;
    } else {
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 0;
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
        fade->state = 2;
    }
}

// fn_2_6BDE0, size:0xA0
void fn_2_6BDE0(MenuFadeState* fade) {
    s32 alpha;

    ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fade->progress = (f32)((f64)fade->progress + lbl_2_rodata_C30);
    alpha = (s32)(lbl_2_rodata_C3C * fade->progress);
    if (alpha < 255) {
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = alpha;
    } else {
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 255;
        fade->state = 2;
    }
}

// fn_2_688A4, size:0x9C
f32 fn_2_688A4(s32 index, s32 location) {
    Vec target;
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 angle;

    memcpy(&target, &lbl_2_data_2EA4[location], sizeof(target));
    angle = (f32)atan2(-(target.x - entry->position.x), -(target.z - entry->position.z));
    return fn_2_4A18C(entry->heading) - angle;
}

// fn_2_68940, size:0x8C
f32 fn_2_68940(s32 from, s32 to) {
    MenuEntry* source = &lbl_2_bss_1A8248[0]->entries[from];
    MenuEntry* target = &lbl_2_bss_1A8248[0]->entries[to];
    f32 angle = (f32)atan2(-(target->position.x - source->position.x),
        -(target->position.z - source->position.z));
    return fn_2_4A18C(source->heading) - angle;
}

// fn_2_6A5A8, size:0x80
void fn_2_6A5A8(s32 index) {
    lbl_2_bss_1A8248[0]->entries[index].previousPosition.x = lbl_2_bss_1A8248[0]->entries[index].position.x;
    lbl_2_bss_1A8248[0]->entries[index].previousPosition.y = lbl_2_bss_1A8248[0]->entries[index].position.y;
    lbl_2_bss_1A8248[0]->entries[index].previousPosition.z = lbl_2_bss_1A8248[0]->entries[index].position.z;
    lbl_2_bss_1A8248[0]->entries[index].velocity.x = lbl_2_rodata_B58;
    lbl_2_bss_1A8248[0]->entries[index].velocity.y = lbl_2_rodata_B58;
    lbl_2_bss_1A8248[0]->entries[index].velocity.z = lbl_2_rodata_B58;
    lbl_2_bss_1A8248[0]->entries[index]._38 = lbl_2_rodata_B58;
    lbl_2_bss_1A8248[0]->entries[index]._50 = lbl_2_rodata_B58;
}

extern void (*lbl_2_data_2A2E0[])(MenuEntry* object);
extern void (*lbl_2_data_2A2D4[])(MenuEntry* object);
extern void (*lbl_2_data_2A2C4[])(MenuEntry* object);
extern void (*lbl_2_data_2A2B8[])(MenuEntry* object);
extern void (*lbl_2_data_2A2AC[])(MenuEntry* object);
extern void (*lbl_2_data_2A29C[])(MenuEntry* object);
extern void (*lbl_2_data_2A28C[])(MenuEntry* object);
extern void (*lbl_2_data_2A280[])(MenuEntry* object);
extern void (*lbl_2_data_2A274[])(MenuEntry* object);
extern void (*lbl_2_data_2A268[])(MenuEntry* object);
extern void (*lbl_2_data_2A25C[])(MenuEntry* object);
extern void (*lbl_2_data_2A250[])(MenuEntry* object);
extern void (*lbl_2_data_2A248[])(MenuEntry* object);
extern void (*lbl_2_data_2A234[])(MenuEntry* object);
extern void (*lbl_2_data_2A220[])(MenuEntry* object);
extern void (*lbl_2_data_2A210[])(MenuEntry* object);
extern void (*lbl_2_data_2A208[])(MenuEntry* object);
extern void (*lbl_2_data_2A200[])(MenuEntry* object);
extern void (*lbl_2_data_2A1F4[])(MenuEntry* object);

// .text:0x71A38 size:0x38
void fn_2_71A38(MenuEntry* object) {
    lbl_2_data_2A1F4[object->state](object);
}

// .text:0x70588 size:0x38
void fn_2_70588(MenuEntry* object) {
    lbl_2_data_2A200[object->state](object);
}

// .text:0x704A0 size:0xC
void fn_2_704A0(MenuEntry* object) {
    object->state = 2;
}

// .text:0x70494 size:0xC
void fn_2_70494(MenuEntry* object) {
    object->state = 2;
}

// .text:0x7045C size:0x38
void fn_2_7045C(MenuEntry* object) {
    lbl_2_data_2A208[object->state](object);
}

// .text:0x6FE34 size:0x38
void fn_2_6FE34(MenuEntry* object) {
    lbl_2_data_2A210[object->state](object);
}

// .text:0x6F6F4 size:0x38
void fn_2_6F6F4(MenuEntry* object) {
    lbl_2_data_2A220[object->state](object);
}

// .text:0x6E880 size:0xC
void fn_2_6E880(MenuEntry* object) {
    object->state = 4;
}

// .text:0x6E848 size:0x38
void fn_2_6E848(MenuEntry* object) {
    lbl_2_data_2A234[object->state](object);
}

// .text:0x6D840 size:0x38
void fn_2_6D840(MenuEntry* object) {
    lbl_2_data_2A248[object->state](object);
}

// .text:0x6D748 size:0xC
void fn_2_6D748(MenuEntry* object) {
    object->state = 1;
}

// .text:0x6D710 size:0x38
void fn_2_6D710(MenuEntry* object) {
    lbl_2_data_2A250[object->state](object);
}

// .text:0x6D4E8 size:0x10
void fn_2_6D4E8(MenuEntry* object) {
    object->timer -= 1;
}

// .text:0x6D4B0 size:0x38
void fn_2_6D4B0(MenuEntry* object) {
    lbl_2_data_2A25C[object->state](object);
}

// .text:0x6D288 size:0x10
void fn_2_6D288(MenuEntry* object) {
    object->timer -= 1;
}

// .text:0x6D250 size:0x38
void fn_2_6D250(MenuEntry* object) {
    lbl_2_data_2A268[object->state](object);
}

// .text:0x6D078 size:0x10
void fn_2_6D078(MenuEntry* object) {
    object->timer -= 1;
}

// .text:0x6D040 size:0x38
void fn_2_6D040(MenuEntry* object) {
    lbl_2_data_2A274[object->state](object);
}

// .text:0x6CB78 size:0x38
void fn_2_6CB78(MenuEntry* object) {
    lbl_2_data_2A280[object->state](object);
}

// .text:0x6C97C size:0xC
void fn_2_6C97C(MenuEntry* object) {
    object->state = 2;
}

// .text:0x6C970 size:0xC
void fn_2_6C970(MenuEntry* object) {
    object->state = 2;
}

// .text:0x6C938 size:0x38
void fn_2_6C938(MenuEntry* object) {
    lbl_2_data_2A28C[object->state](object);
}

// .text:0x6C28C size:0x38
void fn_2_6C28C(MenuEntry* object) {
    lbl_2_data_2A29C[object->state](object);
}

// .text:0x6BF88 size:0x38
void fn_2_6BF88(MenuEntry* object) {
    lbl_2_data_2A2AC[object->state](object);
}

// .text:0x6BDD4 size:0xC
void fn_2_6BDD4(MenuEntry* object) {
    object->state = 2;
}

// .text:0x6BD9C size:0x38
void fn_2_6BD9C(MenuEntry* object) {
    lbl_2_data_2A2B8[object->state](object);
}

// .text:0x6BC00 size:0xC
void fn_2_6BC00(MenuEntry* object) {
    object->state = 2;
}

// .text:0x6BBC8 size:0x38
void fn_2_6BBC8(MenuEntry* object) {
    lbl_2_data_2A2C4[object->state](object);
}

// .text:0x6BA18 size:0x38
void fn_2_6BA18(MenuEntry* object) {
    lbl_2_data_2A2D4[object->state](object);
}

// .text:0x6B4C4 size:0x38
void fn_2_6B4C4(MenuEntry* object) {
    lbl_2_data_2A2E0[object->state](object);
}

// .text:0x6ACF0 size:0x4
void fn_2_6ACF0(void) {
}

// .text:0x6AAB8 size:0x4
void fn_2_6AAB8(void) {
}

// fn_2_6C2C4, size:0x24
void fn_2_6C2C4(void) {
    MenuCtx* menu;
    lbl_2_bss_1A8248[0]->_442F = 0;
    menu = lbl_2_bss_1A8248[0];
    menu->entries[1].typeC3 = 0;
    menu->entries[1].state = 0;
}

// fn_2_68638, size:0x1C
void fn_2_68638(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCE)] = value;
}

// fn_2_68654, size:0x1C
void fn_2_68654(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCD)] = value;
}

// fn_2_686D0, size:0x1C
void fn_2_686D0(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCF)] = value;
}

// fn_2_68D90, size:0x1C
void fn_2_68D90(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = value;
}

// fn_2_68F08, size:0x1C
void fn_2_68F08(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = value;
}

// fn_2_6AF80, size:0x1C
void fn_2_6AF80(s32 index, s8 value) {
    ((u8*)lbl_2_bss_1A8248[0])[index * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC4)] = value;
}

// fn_2_68670, size:0x20
s32 fn_2_68670(s32 index) {
    return ((s8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DD];
}

// fn_2_68690, size:0x20
s32 fn_2_68690(s32 index) {
    return ((s8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DC];
}

// fn_2_686B0, size:0x20
s32 fn_2_686B0(s32 index) {
    return ((s8*)lbl_2_bss_1A8248[0])[index * 0xD8 + 0x16DB];
}

// fn_2_6BAAC, size:0x2C
void fn_2_6BAAC(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 0xFF;
    object->state = 3;
}

// fn_2_6F72C, size:0x60
void fn_2_6F72C(MenuEntry* object) {
    f32 distance = (f32)__fabs(PSVECDistance(&lbl_2_bss_1A8248[0]->entries[0].position, &object->position));
    if (distance > lbl_2_rodata_BA8) {
        object->state = 1;
    }
}

// fn_2_6BFC0, size:0x60
void fn_2_6BFC0(MenuEntry* object) {
    f32 distance = (f32)__fabs(PSVECDistance(&lbl_2_bss_1A8248[0]->entries[0].position, &object->position));
    if (distance > lbl_2_rodata_BA8) {
        object->state = 1;
    }
}

// fn_2_6C2E8, size:0x60
void fn_2_6C2E8(MenuEntry* object) {
    fn_2_69E1C(object->objectId);
    if (object->_50 <= 0.0f) {
        object->mode = 4;
        object->flagC4 = 1;
        object->state = 3;
    }
}

// fn_2_6BA50, size:0x5C
void fn_2_6BA50(MenuEntry* object) {
    GXColor color = *(GXColor*)(lbl_800F7478 + 0x28);
    color.a = 0xFF;
    fn_800BD2CC(0, color);
    object->state = 2;
}

// fn_2_6BB7C, size:0x4C
void fn_2_6BB7C(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 0xFF;
    object->progress = lbl_2_rodata_BA0;
    object->state = 1;
}

// fn_2_6C120, size:0x70
void fn_2_6C120(MenuEntry* object) {
    f32 distance = (f32)__fabs(PSVECDistance(&lbl_2_bss_1A8248[0]->entries[0].position, &object->position));
    if (distance < lbl_2_rodata_BA8 && distance != 0.0f) {
        object->state = 2;
    }
}

// fn_2_6AF9C, size:0x38
s32 fn_2_6AF9C(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    if (entry->flagD0 == 0) {
        entry->flagD0 = 0;
        return 1;
    }
    return 0;
}

// fn_2_6AFD4, size:0x50
s32 fn_2_6AFD4(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    u8 flag = entry->flagC4;
    if (flag == 1) {
        entry->flagC4 = 0;
        return 1;
    }
    if (flag == 2) {
        entry->flagC4 = 0;
        return 2;
    }
    return 0;
}

// fn_2_68DAC, size:0x3C
void fn_2_68DAC(s32 index, void* result) {
    memcpy(result, &lbl_2_bss_1A8248[0]->entries[index], 0xC);
}

// fn_2_696D4, size:0x3C
void fn_2_696D4(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    if (entry->_A0 != 0) {
        entry->_38 = entry->_3C;
        return;
    }
    entry->_38 = 0.0f;
}

// fn_2_68DE8, size:0x80
void fn_2_68DE8(s32 index, Vec* result) {
    if (index != -1) {
        memcpy(result, &lbl_2_bss_1A8248[0]->entries[index], 0xC);
        PSVECScale(result, lbl_2_rodata_B6C[0], result);
        return;
    }
    result->z = 0.0f;
    result->y = 0.0f;
    result->x = 0.0f;
}

// fn_2_6AABC, size:0x80
void fn_2_6AABC(s32 index, const Vec* position) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    MenuEntry* p = entry;
    memcpy(entry, position, 0xC);
    p->previousPosition.x = 0.0f;
    p->previousPosition.y = 0.0f;
    p->previousPosition.z = 0.0f;
    p->velocity.x = 0.0f;
    p->velocity.y = 0.0f;
    p->velocity.z = 0.0f;
    p->storedX = p->position.x;
    p->storedZ = p->position.z;
    p->_38 = 0.0f;
    p->flagBB = 0;
}

// fn_2_6BC0C, size:0xA0
void fn_2_6BC0C(MenuFadeState* fade) {
    s32 alpha;

    ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fade->progress = (f32)((f64)fade->progress + lbl_2_rodata_C30);
    alpha = (s32)(lbl_2_rodata_C3C * fade->progress);
    if (alpha < 255) {
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = alpha;
    } else {
        ((u8*)lbl_2_bss_1A8248[0])[fade->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 255;
        fade->state = 2;
    }
}

// fn_2_683EC, size:0xE4
void fn_2_683EC(void) {
    MenuEntry* entry;
    f32 heading;
    MenuCtx* state;
    MenuCtx* menu;

    menu = lbl_2_bss_1A8248[0];
    menu->entries[1].position.x = menu->entries[0].position.x;
    menu->entries[1].position.y = menu->entries[0].position.y;
    menu->entries[1].position.z = menu->entries[0].position.z;
    entry = &lbl_2_bss_1A8248[0]->entries[1];
    memcpy(&entry->position, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[0].locationIndex], sizeof(Vec));
    entry->previousPosition.x = lbl_2_rodata_B58;
    entry->previousPosition.y = lbl_2_rodata_B58;
    entry->previousPosition.z = lbl_2_rodata_B58;
    entry->velocity.x = lbl_2_rodata_B58;
    entry->velocity.y = lbl_2_rodata_B58;
    entry->velocity.z = lbl_2_rodata_B58;
    entry->storedX = entry->position.x;
    entry->storedZ = entry->position.z;
    entry->_38 = lbl_2_rodata_B58;
    entry->flagBB = 0;
    heading = entry->heading;
    entry->angle34 = heading;
    entry->angle30 = heading;
    lbl_2_bss_1A8248[0]->entries[1].locationIndex = lbl_2_bss_1A8248[0]->entries[0].locationIndex;
    state = lbl_2_bss_1A8248[0];
    state->entries[1].typeC3 = 6;
    state->entries[1].state = 0;
    lbl_2_bss_1A8248[0]->_442F = 1;
}

// fn_2_6ABFC, size:0xF4
void fn_2_6ABFC(s32 index, s32 location) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 heading;

    if (index < 2) {
        memcpy(&entry->position, &lbl_2_data_2EA4[location], sizeof(Vec));
    } else if (index >= 2 && index <= 6) {
        memcpy(&entry->position, &lbl_2_data_2EA4[location], sizeof(Vec));
    } else {
        memcpy(&entry->position, &lbl_2_data_3150[index - 7], sizeof(Vec));
    }
    entry->previousPosition.x = lbl_2_rodata_B58;
    entry->previousPosition.y = lbl_2_rodata_B58;
    entry->previousPosition.z = lbl_2_rodata_B58;
    entry->velocity.x = lbl_2_rodata_B58;
    entry->velocity.y = lbl_2_rodata_B58;
    entry->velocity.z = lbl_2_rodata_B58;
    entry->storedX = entry->position.x;
    entry->storedZ = entry->position.z;
    entry->_38 = lbl_2_rodata_B58;
    entry->flagBB = 0;
    heading = entry->heading;
    entry->angle34 = heading;
    entry->angle30 = heading;
}

// fn_2_698EC, size:0xE8
void fn_2_698EC(s32 index, f32 threshold) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 height;

    if (entry->flagD0 != 0) {
        height = -sinf_kludge(entry->bouncePhase);
        height = lbl_2_rodata_BA8 * height;
        entry->bouncePhase += lbl_2_rodata_BAC[0];
        if (entry->position.y > threshold) {
            entry->bouncePhase = 0.0f;
            height = 0.0f;
            entry->flagD0 = 0;
            if (entry->typeC3 == 19) {
                ((u8*)lbl_2_bss_1A8248[0])[entry->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
            }
        }
        entry->position.y = height;
    } else {
        entry->position.y = 0.0f;
    }
}

// fn_2_68E68, size:0xA0
void fn_2_68E68(void) {
    MenuEntry* src;
    CharActor* params;
    s32 i;
    for (i = 0; i < lbl_2_bss_1A824C[0]->_197746; i++) {
        params = &lbl_8036E548.actors[i];
        src = &lbl_2_bss_1A8248[0]->entries[i];
        memcpy(&params->pos, src, sizeof(Vec));
        params->rot.y = src->heading;
        params->mode[0] = src->flagC0;
        params->_277 = src->flagCA;
    }
}

// fn_2_6C020, size:0x100
void fn_2_6C020(MenuEntry* entry) {
    f32 difference;

    entry->heading = (f32)atan2(-(lbl_2_bss_1A8248[0]->entries[0].position.x - entry->position.x),
        -(lbl_2_bss_1A8248[0]->entries[0].position.z - entry->position.z));
    difference = fn_2_4A18C(entry->angle34 - entry->heading);
    if ((difference < lbl_2_rodata_BE0 && difference > lbl_2_rodata_B58) ||
        (difference > lbl_2_rodata_BE8 && difference < lbl_2_rodata_B58)) {
        entry->state = 3;
    } else if (difference < lbl_2_rodata_B58) {
        entry->angle34 += lbl_2_rodata_C40;
    } else {
        entry->angle34 -= lbl_2_rodata_C40;
    }
    entry->heading = entry->angle34;
}

// fn_2_6BCAC, size:0xBC
void fn_2_6BCAC(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
    fn_2_68F24(object->objectId, 9);
    object->heading = lbl_2_rodata_B58;
    object->angle34 = lbl_2_rodata_B58;
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 0xFF;
    object->progress = lbl_2_rodata_B58;
    object->state = 1;
}

// fn_2_68FBC, size:0xB4
void fn_2_68FBC(s32 index, s32 animation) {
    MenuEntry* entry;
    MenuAnimation* settings;
    s16* cache;
    s32 cur;

    entry = &lbl_2_bss_1A8248[0]->entries[index];
    settings = &lbl_2_data_3C84[animation];
    cache = lbl_2_bss_1A824C[0]->_197756;
    cur = cache[entry->objectId];
    if (cur != animation) {
        fn_2_8CD58(entry->objectId, settings->clip, settings->mode, 1, settings->end, 0, 0);
        cache = lbl_2_bss_1A824C[0]->_197756;
        cache[entry->objectId] = animation;
    }
}

// fn_2_704AC, size:0xDC
void fn_2_704AC(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fn_2_68FBC(object->objectId, 1);
    object->state = 1;
}

// fn_2_6D4F8
void fn_2_6D4F8(MenuEntry* object) {
    if (fn_2_8CC88(object->_84) != 0) {
        fn_2_68FBC(object->objectId, 5);
        object->timer = 0x1E;
        object->state = 2;
    }
}

// fn_2_6D088
void fn_2_6D088(MenuEntry* object) {
    if (fn_2_8CC88(object->_84) != 0) {
        fn_2_68FBC(object->objectId, 7);
        object->timer = 0x1E;
        object->state = 2;
    }
}

// fn_2_6D298
void fn_2_6D298(MenuEntry* object) {
    if (fn_2_8CC88(object->_84) != 0) {
        fn_2_68FBC(object->objectId, 6);
        object->timer = 0x1E;
        object->state = 2;
    }
}

// fn_2_6D164
void fn_2_6D164(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    object->angle34 = lbl_2_rodata_B58;
    object->heading = lbl_2_rodata_B58;
    fn_2_68FBC(object->objectId, 4);
    object->state = 1;
}

// fn_2_6D754
void fn_2_6D754(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fn_2_68FBC(object->objectId, 1);
    object->heading = lbl_2_rodata_B58;
    object->angle34 = lbl_2_rodata_B58;
    object->state = 1;
}

// fn_2_6C190
void fn_2_6C190(MenuEntry* object) {
    extern void fn_2_46C88(s32 index, s32 unused);
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fn_2_68FBC(object->objectId, 1);
    object->angle34 = object->heading;
    fn_2_46C88(lbl_2_bss_1A8248[0]->_441E, 0);
    object->state = 1;
}

// fn_2_6D878
void fn_2_6D878(MenuEntry* object) {
    s32 index = object->objectId;
    if (lbl_2_bss_1A8248[0]->entries[0].flagCD == 0) {
        object->timer = 0x78;
        fn_2_68FBC(index, 1);
        object->mode = 9;
        object->_50 = lbl_2_rodata_B58;
        object->_38 = lbl_2_rodata_B58;
        object->state = 2;
    }
}

// fn_2_6D5D4
void fn_2_6D5D4(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    if (object->_84 == 0) {
        fn_80062890(lbl_2_data_3C40[lbl_2_bss_1A8248[0]->_441C]);
    } else if (object->_84 == 1) {
        fn_80062890(lbl_2_data_3C40[6]);
    }
    object->angle34 = lbl_2_rodata_B58;
    object->heading = lbl_2_rodata_B58;
    fn_2_68FBC(object->objectId, 2);
    object->state = 1;
}

// fn_2_6D374
void fn_2_6D374(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    if (object->_84 == 0) {
        fn_80062890(lbl_2_data_3C5C[lbl_2_bss_1A8248[0]->_441C]);
    } else if (object->_84 == 1) {
        fn_80062890(lbl_2_data_3C5C[6]);
    }
    object->angle34 = lbl_2_rodata_B58;
    object->heading = lbl_2_rodata_B58;
    fn_2_68FBC(object->objectId, 3);
    object->state = 1;
}

// fn_2_6BE80
void fn_2_6BE80(MenuEntry* object) {
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
    fn_2_68FBC(object->objectId, 1);
    ((u8*)lbl_2_bss_1A8248[0])[object->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagCA)] = 0xFF;
    object->progress = lbl_2_rodata_B58;
    object->state = 1;
}

extern f32 lbl_2_data_3F0C[];
extern f32 lbl_2_data_3F2C[];

// fn_2_68C80
s32 fn_2_68C80(s32 first, s32 second) {
    MenuEntry* a = &lbl_2_bss_1A8248[0]->entries[first];
    MenuEntry* b = &lbl_2_bss_1A8248[0]->entries[second];
    f32 distance = PSVECDistance(&a->position, &b->position);
    f32 x;
    f32 y;

    if (first == 0) {
        x = lbl_2_data_3EF4[lbl_2_bss_1A8248[0]->_441C];
        y = lbl_2_data_3F0C[second];
    } else {
        x = lbl_2_data_3F0C[first];
        y = lbl_2_data_3EF4[lbl_2_bss_1A8248[0]->_441C];
    }
    if (distance < x + y && (u8)a->flagC0 != 0 && (u8)b->flagC0 != 0) {
        return 1;
    }
    return 0;
}

// fn_2_6B120
void fn_2_6B120(MenuEntry* owner) {
    s32 index = owner->objectId;
    MenuEntry* entry;
    f32 height;

    fn_2_69E1C(index);
    entry = &lbl_2_bss_1A8248[0]->entries[index];
    if (entry->flagD0 != 0) {
        height = (f32)sin(entry->bouncePhase);
        height = lbl_2_rodata_BA8 * -height;
        entry->bouncePhase += lbl_2_rodata_BAC[0];
        if (entry->position.y > 0.0f) {
            entry->bouncePhase = 0.0f;
            height = 0.0f;
            entry->flagD0 = 0;
            if (entry->typeC3 == 19) {
                ((u8*)lbl_2_bss_1A8248[0])[entry->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
            }
        }
        entry->position.y = height;
    } else {
        entry->position.y = 0.0f;
    }
    if (owner->_50 <= 0.0f) {
        owner->mode = 4;
        owner->state = 2;
    }
}

extern const f32 lbl_2_rodata_C28;

// fn_2_6B620
void fn_2_6B620(MenuEntry* owner) {
    s32 index = owner->objectId;
    MenuEntry* entry;
    f32 height;

    fn_2_69E1C(index);
    entry = &lbl_2_bss_1A8248[0]->entries[index];
    if (entry->flagD0 != 0) {
        height = (f32)sin(entry->bouncePhase);
        height = lbl_2_rodata_BA8 * -height;
        entry->bouncePhase += lbl_2_rodata_BAC[0];
        if (entry->position.y > lbl_2_rodata_C28) {
            entry->bouncePhase = 0.0f;
            height = 0.0f;
            entry->flagD0 = 0;
            if (entry->typeC3 == 19) {
                ((u8*)lbl_2_bss_1A8248[0])[entry->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
            }
        }
        entry->position.y = height;
    } else {
        entry->position.y = 0.0f;
    }
    if (owner->_50 <= 0.0f) {
        owner->mode = 4;
        owner->flagC4 = 1;
        owner->state = 2;
    }
}

// fn_2_6ACF4, size:0x114
void fn_2_6ACF4(void) {
    s32 off;
    MenuEntry* e;
    s32 i;

    for (i = 0, off = 0; i < 8; i++) {
        e = (MenuEntry*)((u8*)lbl_2_bss_1A8248[0] + off + offsetof(MenuCtx, entries));
        e->objectId = i;
        e->_84 = i;
        e->progress = lbl_2_rodata_B58;
        e->_B6 = 10;
        e->_40 = 0.0003f * e->_B6 + 0.1f;
        e->_B8 = 10;
        e->_B7 = 15;
        e->_44 = e->_40 / e->_B7;
        e->flagBB = 0;
        e->flagC0 = 0;
        e->_96 = i;
        e->_98 = -1;
        e->flagBC = 1;
        e->typeC3 = 0;
        e->state = 0;
        e->_C6 = -1;
        e->flagC4 = 0;
        e->_C5 = 0;
        e->_88 = lbl_2_rodata_B58;
        e->_C1[0] = 0;
        e->_AC = 0;
        *(u8*)&e->flagCA = 0xFF;
        e->flagCB = -1;
        e->flagCC = -1;
        off += sizeof(MenuEntry);
    }
}

// fn_2_68B54
s32 fn_2_68B54(s32 first, s32 second) {
    MenuEntry* a = &lbl_2_bss_1A8248[0]->entries[first];
    MenuEntry* b = &lbl_2_bss_1A8248[0]->entries[second];
    f32 distance = PSVECDistance(&a->position, &b->position);
    f32 x;
    f32 y;

    if (first == 0) {
        x = lbl_2_data_3EF4[lbl_2_bss_1A8248[0]->_441C] + lbl_2_data_3F2C[lbl_2_bss_1A8248[0]->_441C];
        y = lbl_2_data_3F0C[second];
    } else {
        x = lbl_2_data_3F0C[first];
        y = lbl_2_data_3EF4[lbl_2_bss_1A8248[0]->_441C] + lbl_2_data_3F2C[lbl_2_bss_1A8248[0]->_441C];
    }
    if (distance < x + y && (u8)a->flagC0 != 0 && (u8)b->flagC0 != 0) {
        return 1;
    }
    return 0;
}

extern s16 lbl_2_data_3D30[][4];

// fn_2_6CCB8
void fn_2_6CCB8(MenuEntry* owner) {
    s32 i;

    fn_2_69E1C(owner->objectId);
    if (owner->_50 <= 0.0f) {
        owner->mode = 4;
        owner->flagC4 = 1;
        for (i = 0; i < 4; i++) {
            if (lbl_2_bss_1A8248[0]->entries[0].targetLocation == *(s16*)((u8*)lbl_2_data_3D30 + lbl_2_bss_1A8248[0]->entries[0].locationIndex * 8 + i * 2)) {
                lbl_2_bss_1A8248[0]->_4448 = i;
            }
        }
        lbl_2_bss_1A8248[0]->entries[0].locationIndex = lbl_2_bss_1A8248[0]->entries[0].targetLocation;
        owner->state = 2;
    }
}

// fn_2_684D0
s32 fn_2_684D0(s32 first) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[first];
    s32 i;
    u8 hit;

    entry->flagCC = -1;
    for (i = 1; i < 7; i++) {
        hit = fn_2_68B54(first, i);
        if (hit != 0 && i >= 2 && i <= 6) {
            entry->flagCC = i;
            break;
        }
        entry->flagCC = -1;
    }
    return entry->flagCC;
}

extern s16 lbl_2_data_2E80[];

// .text:0x71B80 size:0xEC
void fn_2_71B80(MenuEntry* object) {
    u8 type;
    CharActor* p;
    s32 lo;
    s16* t;
    s32 b, c;
    s32 hi;
    s32 base;

    fn_2_69E1C(object->objectId);
    type = lbl_2_bss_1A8248[0]->_441C;
    t = lbl_2_data_2E80;
    base = t[type * 3] * 2;
    c = t[type * 3 + 2] * 2;
    b = t[type * 3 + 1] * 2;
    hi = base - c;
    lo = base - b;
    if (object->objectId == 0) {
        p = &lbl_8036E548.actors[0];
        if (p != NULL) {
            c = p->_068;
            if (c == hi || c == lo) {
                if (type == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (object->_50 <= lbl_2_rodata_B58) {
        object->mode = 4;
        object->flagC4 = 1;
        object->state = 2;
    }
}

// .text:0x71A70 size:0x110
void fn_2_71A70(MenuEntry* object) {
    s16* t;
    u8 type;
    s32 hi;
    s32 base;
    CharActor* p;
    s32 lo;
    s32 index;
    s32 b, c;

    index = object->objectId;
    fn_2_69E1C(index);
    type = lbl_2_bss_1A8248[0]->_441C;
    t = lbl_2_data_2E80;
    base = t[type * 3] * 2;
    c = t[type * 3 + 2] * 2;
    b = t[type * 3 + 1] * 2;
    hi = base - c;
    lo = base - b;
    if (object->objectId == 0) {
        p = &lbl_8036E548.actors[0];
        if (p != NULL) {
            c = p->_068;
            if (c == hi || c == lo) {
                if (type == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (object->_38 <= lbl_2_rodata_B58) {
        MenuEntry* e;
        object->angle34 = object->heading;
        e = &lbl_2_bss_1A8248[0]->entries[index];
        e->typeC3 = 3;
        e->state = 0;
    }
}

// .text:0x6CBB0 size:0x108
void fn_2_6CBB0(MenuEntry* object) {
    s16* t;
    u8 type;
    s32 hi;
    s32 base;
    CharActor* p;
    s32 lo;
    s32 index;
    s32 b, c;

    index = object->objectId;
    fn_2_69E1C(index);
    type = lbl_2_bss_1A8248[0]->_441C;
    t = lbl_2_data_2E80;
    base = t[type * 3] * 2;
    c = t[type * 3 + 2] * 2;
    b = t[type * 3 + 1] * 2;
    hi = base - c;
    lo = base - b;
    if (object->objectId == 0) {
        p = &lbl_8036E548.actors[0];
        if (p != NULL) {
            c = p->_068;
            if (c == hi || c == lo) {
                if (type == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (object->_38 <= lbl_2_rodata_B58) {
        MenuEntry* e;
        e = &lbl_2_bss_1A8248[0]->entries[index];
        e->typeC3 = 3;
        e->state = 0;
    }
}

extern const f64 lbl_2_rodata_B78;
extern const f64 lbl_2_rodata_B80;
extern const f64 lbl_2_rodata_B88;

static inline f32 menuSqrtf(f32 x) {
    if (x > 0.0f) {
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        x = (f32)(xd * guess);
    } else if (x < lbl_2_rodata_B88) {
        x = NAN;
    } else if (isnan(x)) {
        x = NAN;
    }
    return x;
}

// .text:0x6A450 size:0x158
void fn_2_6A450(s32 index, f32 x, f32 z) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 dx;
    f32 dz;

    entry->previousPosition.x = x;
    entry->previousPosition.z = z;
    dx = x - entry->position.x;
    dz = z - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
}

// .text:0x69554 size:0x180
s32 fn_2_69554(s32 index, f32 x, f32 z) {
    f32 dz;
    f64 guess;
    f32 dx;
    f32 px;
    MenuEntry* entry;
    f32 divisor;
    f32 sum;
    f32 sz;
    u32 bonus;
    f64 xd;
    f32 sx;

    entry = &lbl_2_bss_1A8248[0]->entries[index];
    px = entry->position.x;
    if (x == px && z == entry->position.z) {
        return 1;
    }
    dx = x - px;
    dz = z - entry->position.z;
    sz = dz * dz;
    sx = dx * dx;
    sum = sx + sz;
    if (sum > 0.0f) {
        xd = (f64)sum;
        guess = __frsqrte(xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        sum = (f32)(xd * guess);
    } else if (sum < lbl_2_rodata_B88) {
        sum = NAN;
    } else if (isnan(sum)) {
        sum = NAN;
    }
    bonus = (u32)entry->_B7 >> 1;
    divisor = entry->_40;
    divisor = (0.0f == divisor) ? 1.0f : divisor;
    return bonus + (s32)(sum / divisor);
}

extern const f32 lbl_2_rodata_C14;
extern const f32 lbl_2_rodata_C18;

// .text:0x6AE08 size:0x178
void fn_2_6AE08(void) {
    MenuEntry* e;
    s32 i;

    i = 0;
    do {
        e = &lbl_2_bss_1A8248[0]->entries[i];
        memset(e, 0, 0xD8);
        e->objectId = i;
        e->_84 = i;
        e->progress = lbl_2_rodata_B58;
        e->_B6 = 10;
        e->_40 = lbl_2_rodata_C18 * (f32) e->_B6 + lbl_2_rodata_C14;
        e->_B8 = 10;
        e->_B7 = 15;
        e->_44 = e->_40 / (f32) e->_B7;
        e->flagBB = 0;
        e->flagC0 = 0;
        e->_96 = i;
        i++;
        e->_98 = -1;
        e->flagBC = 1;
        e->typeC3 = 0;
        e->state = 0;
        e->_C6 = -1;
        e->flagC4 = 0;
        e->_C5 = 0;
        e->_88 = lbl_2_rodata_B58;
        e->_C1[0] = 0;
        e->mode = 12;
        e->_AC = 0;
        *(u8*)&e->flagCA = 0xFF;
        e->flagCB = -1;
        e->flagCC = -1;
    } while (i < 8);
}

// fn_2_6D968, size:0x1C8
void fn_2_6D968(MenuEntry* entry) {
    f32 difference;
    s32 id = entry->objectId;
    MenuEntry* target;
    MenuAnimation* settings;
    s16* cache;

    entry->heading = (f32)atan2(-(lbl_2_bss_1A8248[0]->entries[0].position.x - entry->position.x),
        -(lbl_2_bss_1A8248[0]->entries[0].position.z - entry->position.z));
    difference = fn_2_4A18C(entry->angle34 - entry->heading);
    if ((difference < lbl_2_rodata_BE0 && difference > lbl_2_rodata_B58) ||
        (difference > lbl_2_rodata_BE8 && difference < lbl_2_rodata_B58)) {
        entry->state = 4;
    } else if (difference < lbl_2_rodata_B58) {
        entry->angle34 += lbl_2_rodata_C40;
    } else {
        entry->angle34 -= lbl_2_rodata_C40;
    }
    entry->heading = entry->angle34;
    if (lbl_2_bss_1A8248[0]->entries[0].flagCD == 0) {
        entry->timer = 0x78;
        target = &lbl_2_bss_1A8248[0]->entries[id];
        settings = &lbl_2_data_3C84[1];
        cache = lbl_2_bss_1A824C[0]->_197756;
        if (cache[target->objectId] != 1) {
            fn_2_8CD58(target->objectId, settings->clip, settings->mode, 1, settings->end, 0, 0);
            cache = lbl_2_bss_1A824C[0]->_197756;
            cache[target->objectId] = 1;
        }
        entry->mode = 9;
        entry->_50 = lbl_2_rodata_B58;
        entry->_38 = lbl_2_rodata_B58;
        entry->state = 2;
    }
}

extern const f32 lbl_2_rodata_BA4;
extern s16 fn_2_4A150(s16);
extern s32 fn_2_4A2C4(f32);

// fn_2_69710, size:0x1C4
void fn_2_69710(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    s16 a;
    s16 d;

    if (entry->_9C == 0) {
        a = fn_2_4A2C4(entry->heading);
        d = fn_2_4A150((s16)(a - (s16)fn_2_4A2C4(entry->angle30)));
        if (d < 0x200) {
            entry->_BE = 0;
        } else if (d < 0x600) {
            entry->_BE = 3;
        } else if (d < 0xA00) {
            entry->_BE = 1;
        } else if (d < 0xE00) {
            entry->_BE = 2;
        } else {
            entry->_BE = 0;
        }
        if (entry->flagBC != 1) {
            if (entry->_BE == 1) {
                entry->_BE = 5;
            } else {
                entry->_BE = 4;
            }
        }
    }
    if (entry->_BE == 4 || entry->_BE == 5) {
        entry->_38 = lbl_2_rodata_B68[0] * entry->_44 + entry->_38;
    } else {
        entry->_38 = entry->_38 + entry->_44;
    }
    if (entry->_C1[0] == 0 && entry->_C1[1] != 0 && entry->_A0 == 0) {
        entry->_A0 = 0x1E;
    }
    if (entry->_C1[0] != 0) {
        if (entry->_38 > entry->_40) {
            entry->_38 = entry->_40;
        }
        entry->_A0 = 0;
    } else if (entry->_A0 != 0) {
        if (entry->_38 >= entry->_40) {
            entry->_38 = entry->_40;
        } else {
            entry->_A0 = 0;
        }
    } else if (entry->_38 > 0.12f) {
        entry->_38 = 0.12f;
    }
}

extern const f32 lbl_2_rodata_BB4;
extern const f32 lbl_2_rodata_BB8;
extern const f32 lbl_2_rodata_BBC;
extern const f32 lbl_2_rodata_BC0;
extern const f32 lbl_2_rodata_BC4;
extern const f32 lbl_2_rodata_BC8;
extern const f32 lbl_2_rodata_BCC;
extern const f32 lbl_2_rodata_BD0;
extern const f32 lbl_2_rodata_BD4;
extern const f32 lbl_2_rodata_BD8;

// fn_2_6E88C, size:0x1E8
void fn_2_6E88C(MenuEntry* entry) {
    f32 difference;
    f32 magnitude;
    f32 step;

    entry->heading = (f32)atan2(-(lbl_2_bss_1A8248[0]->entries[0].position.x - entry->position.x),
        -(lbl_2_bss_1A8248[0]->entries[0].position.z - entry->position.z));
    difference = fn_2_4A18C(entry->angle34 - entry->heading);
    magnitude = (f32)__fabs(difference);
    if (magnitude > lbl_2_rodata_BB4) {
        step = lbl_2_rodata_BB8;
    } else if (magnitude > lbl_2_rodata_BB8) {
        step = lbl_2_rodata_BBC;
    } else if (magnitude > lbl_2_rodata_BBC) {
        step = lbl_2_rodata_BC0;
    } else if (magnitude > lbl_2_rodata_BC0) {
        step = lbl_2_rodata_BC4;
    } else if (magnitude > lbl_2_rodata_BC4) {
        step = lbl_2_rodata_BC8;
    } else if (magnitude > lbl_2_rodata_BC8) {
        step = lbl_2_rodata_BCC;
    } else if (magnitude > lbl_2_rodata_BCC) {
        step = lbl_2_rodata_BD0;
    } else if (magnitude > lbl_2_rodata_BD0) {
        step = lbl_2_rodata_BD4;
    } else if (magnitude < lbl_2_rodata_BD0) {
        step = lbl_2_rodata_BD8;
    }
    if (!((difference < lbl_2_rodata_BE0 && difference > lbl_2_rodata_B58) ||
          (difference > lbl_2_rodata_BE8 && difference < lbl_2_rodata_B58))) {
        if (difference < lbl_2_rodata_B58) {
            entry->angle34 += step;
        } else {
            entry->angle34 -= step;
        }
    }
    entry->heading = entry->angle34;
}

extern const f32 lbl_2_rodata_C4C;
extern void fn_2_46C88(s32 index, s32 unused);

// fn_2_6C988, size:0x1F0
void fn_2_6C988(MenuEntry* entry) {
    Vec sum;
    Vec offset;
    Mtx rotation;
    MenuCtx* menu;

    ((u8*)lbl_2_bss_1A8248[0])[entry->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    menu = lbl_2_bss_1A8248[0];
    PSVECSubtract(&lbl_2_data_2EA4[menu->entries[0].targetLocation], &lbl_2_data_2EA4[menu->entries[0]._AE], &sum);
    PSVECScale(&sum, lbl_2_rodata_B68[0], &sum);
    PSMTXRotRad(rotation, 'Y', menu->entries[0].heading);
    offset.x = lbl_2_rodata_B58;
    offset.y = lbl_2_rodata_B58;
    offset.z = lbl_2_rodata_C4C;
    PSMTXMultVec(rotation, &offset, &offset);
    PSVECAdd(&sum, &offset, &sum);
    memcpy(&entry->position, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[0]._AE], sizeof(Vec));
    PSVECAdd(&entry->position, &sum, &entry->position);
    fn_2_68FBC(entry->objectId, 1);
    entry->heading = (f32)atan2(-(menu->entries[0].position.x - entry->position.x),
        -(menu->entries[0].position.z - entry->position.z));
    fn_2_46C88(entry->objectId, 0);
    entry->state = 1;
}

// fn_2_6CDD4, size:0x1AC
void fn_2_6CDD4(MenuEntry* owner) {
    s32 id;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    id = owner->objectId;
    ((u8*)lbl_2_bss_1A8248[0])[owner->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    memcpy(&owner->target, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[0].targetLocation], sizeof(Vec));
    entry = &lbl_2_bss_1A8248[0]->entries[id];
    pz = owner->target.z;
    px = owner->target.x;
    entry->previousPosition.x = px;
    entry->previousPosition.z = pz;
    dx = px - entry->position.x;
    dz = pz - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
    owner->mode = 12;
    fn_2_69E1C(id);
    fn_2_68FBC(id, 0);
    owner->state = 1;
}

// fn_2_6F88C, size:0x1CC
void fn_2_6F88C(MenuEntry* owner) {
    s32 id = owner->objectId;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    s32 other = menu->entries[0].objectId;
    s32 who;
    s32 mode;

    if (id >= 2 && id <= 6 && (mode = *(u8*)&menu->entries[0].flagCD, who = menu->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 2;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 2;
            return;
        }
        if (id >= 2 && id <= 6) {
            owner->flagCB = 0;
        }
    } else {
        owner->flagCB = -1;
    }
}

extern const f32 lbl_2_rodata_B90;
extern s16 fn_2_4A234(f32, f32);
extern s16 fn_2_4A310(s16, s16);

// fn_2_692D0, size:0x284
void fn_2_692D0(s32 index, s32 steps, f32* outX, f32* outZ, f32* outDistance, f32 dx, f32 dz) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 total = lbl_2_rodata_B58;
    f32 speed = entry->_38;
    f32 nx;
    f32 inv;
    s32 n;
    f32 nz;
    s32 i;
    s16 heading;
    s16 side;
    f64 xd;
    f64 guess;
    if (total == dx && total == dz) {
        *outX = entry->position.x;
        *outZ = entry->position.z;
        *outDistance = total;
        return;
    }
    inv = dx * dx + dz * dz;
    if (inv > 0.0f) {
        xd = (f64)inv;
        guess = __frsqrte(xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        inv = (f32)(xd * guess);
    } else if (inv < lbl_2_rodata_B88) {
        inv = NAN;
    } else if (isnan(inv)) {
        inv = NAN;
    }
    nx = dx / inv;
    nz = dz / inv;
    heading = fn_2_4A234(nx, nz);
    if (!(entry->_38 < lbl_2_rodata_B90) && (side = entry->_9A) >= 0 && fn_2_4A310(heading, side) > 0x2A8) {
        speed = lbl_2_rodata_B58;
    }
    n = entry->_B7;
    for (i = 0; i <= n; i++) {
        f32 a = entry->_44;
        f32 b = entry->_40;
        speed += a;
        if (speed > b) {
            total += b;
            break;
        }
        total += speed;
    }
    steps -= i + 1;
    total = entry->_40 * (f32)steps + total;
    *outDistance = total;
    *outX = nx * total + entry->position.x;
    *outZ = nz * total + entry->position.z;
}

// fn_2_71C6C, size:0x258
void fn_2_71C6C(MenuEntry* owner) {
    s32 id;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    id = owner->objectId;
    ((u8*)lbl_2_bss_1A8248[0])[owner->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    memcpy(&owner->target, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[0].targetLocation], sizeof(Vec));
    entry = &lbl_2_bss_1A8248[0]->entries[id];
    pz = owner->target.z;
    px = owner->target.x;
    entry->previousPosition.x = px;
    entry->previousPosition.z = pz;
    dx = px - entry->position.x;
    dz = pz - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
    owner->mode = 13;
    fn_2_68FBC(id, 0);
    owner->state = 1;
}

extern const f32 lbl_2_rodata_C44[];

// fn_2_6C348, size:0x298
void fn_2_6C348(MenuEntry* owner) {
    s32 id;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    id = owner->objectId;
    fn_2_69E1C(id);
    if (owner->_50 <= lbl_2_rodata_B58) {
        if (lbl_2_bss_1A8248[0]->_4439 == 1) {
            owner->mode = 4;
            owner->flagC4 = 1;
            owner->state = 3;
            return;
        }
        memcpy(&owner->target, &lbl_2_data_2EA4[42], sizeof(Vec));
        pz = lbl_2_rodata_B68[0] + owner->target.z;
        px = lbl_2_rodata_C44[0] + owner->target.x;
        entry = &lbl_2_bss_1A8248[0]->entries[id];
        entry->previousPosition.x = px;
        entry->previousPosition.z = pz;
        dx = px - entry->position.x;
        dz = pz - entry->position.z;
        if (0.0f == dx && 0.0f == dz) {
            entry->_38 = 0.0f;
            entry->_50 = 0.0f;
        } else {
            dx = dx * dx + dz * dz;
            entry->_50 = menuSqrtf(dx);
        }
        entry->flagBB = 1;
        fn_2_68FBC(id, 0);
        owner->state = 2;
    }
}

// fn_2_6EA74, size:0x2BC
void fn_2_6EA74(MenuEntry* owner) {
    s32 id = owner->objectId;
    MenuCtx* menu = lbl_2_bss_1A8248[0];
    s32 other = menu->entries[0].objectId;
    s32 who;
    s32 mode;
    s16 timer;

    if (id >= 2 && id <= 6 && (mode = *(u8*)&menu->entries[0].flagCD, who = menu->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 3;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 3;
            return;
        }
        if (id >= 2 && id <= 6) {
            owner->flagCB = 0;
        } else {
            owner->flagCB = -1;
        }
    } else {
        owner->flagCB = -1;
    }
    timer = owner->timer;
    owner->timer = timer - 1;
    if (timer == 0) {
        owner->state = 0;
    }
}

// fn_2_6FE6C, size:0x2A4
void fn_2_6FE6C(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 i;
    s32 hit;
    MenuEntry* e;

    if (owner->flagCD == 1) {
        MenuEntry* b = &lbl_2_bss_1A8248[0]->entries[owner->flagCE];
        MenuEntry* a = &lbl_2_bss_1A8248[0]->entries[id];
        f32 angle = (f32)atan2(-(a->position.x - b->position.x), -(a->position.z - b->position.z));
        f32 diff = fn_2_4A18C(b->heading) - angle;

        if (b->typeC3 == 7 && (owner->state == 0 || owner->state == 1)) {
            if ((f32)__fabs(diff) < 1.5707964f) {
                lbl_2_bss_1A824C[0]->_1978F1 = 0;
            } else {
                lbl_2_bss_1A824C[0]->_1978F1 = 2;
            }
        } else {
            lbl_2_bss_1A824C[0]->_1978F1 = 1;
        }
    }
    for (i = 1; i < 7; i++) {
        hit = (u8)fn_2_68C80(id, i);
        if (hit != 0 && i == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            owner->flagC4 = 2;
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 3;
            e->state = 0;
            return;
        }
        if (hit != 0 && i >= 2 && i <= 6) {
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 4;
            e->state = 0;
            return;
        }
        owner->flagCB = -1;
    }
}

// fn_2_6DE54, size:0x37C
void fn_2_6DE54(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 other = lbl_2_bss_1A8248[0]->entries[0].objectId;
    s32 mode;
    s32 who;

    fn_2_69E1C(id);
    if (id >= 2 && id <= 6 && (mode = (u8)lbl_2_bss_1A8248[0]->entries[0].flagCD, who = lbl_2_bss_1A8248[0]->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 4;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 3;
            return;
        }
        if (id >= 2 && id <= 6) {
            owner->flagCB = 0;
            owner->flagCF = -1;
            owner->state = 0;
        }
    } else {
        owner->flagCB = -1;
    }
    if (owner->_50 <= lbl_2_rodata_B58) {
        owner->_AE = owner->locationIndex;
        owner->locationIndex = owner->targetLocation;
        owner->timer = 0x78;
        fn_2_68FBC(id, 1);
        owner->mode = 9;
        owner->_50 = lbl_2_rodata_B58;
        owner->_38 = lbl_2_rodata_B58;
        owner->state = 2;
    }
}

extern int rand();

// fn_2_6ED30, size:0x3D4
void fn_2_6ED30(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 other = lbl_2_bss_1A8248[0]->entries[0].objectId;
    s32 mode;
    s32 who;

    fn_2_69E1C(id);
    if (id >= 2 && id <= 6 && (mode = (u8)lbl_2_bss_1A8248[0]->entries[0].flagCD, who = lbl_2_bss_1A8248[0]->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 3;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 3;
            return;
        }
        if (id >= 2 && id <= 6) {
            owner->flagCB = 0;
        } else {
            owner->flagCB = -1;
        }
    } else {
        owner->flagCB = -1;
    }
    if (owner->_50 <= lbl_2_rodata_B58) {
        owner->_AE = owner->locationIndex;
        owner->locationIndex = owner->targetLocation;
        if (rand() % 100 < 10) {
            fn_2_68FBC(id, 1);
            owner->timer = rand() % 180 + 60;
            owner->state = 2;
            return;
        }
        owner->state = 0;
    }
}

// fn_2_70110, size:0x34C
void fn_2_70110(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 i;
    s32 hit;
    MenuEntry* e;

    ((u8*)lbl_2_bss_1A8248[0])[owner->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fn_2_68FBC(owner->objectId, 1);
    if (owner->flagCD == 1) {
        MenuEntry* b = &lbl_2_bss_1A8248[0]->entries[owner->flagCE];
        MenuEntry* a = &lbl_2_bss_1A8248[0]->entries[id];
        f32 angle = (f32)atan2(-(a->position.x - b->position.x), -(a->position.z - b->position.z));
        f32 diff = fn_2_4A18C(b->heading) - angle;

        if (b->typeC3 == 7 && (owner->state == 0 || owner->state == 1)) {
            if ((f32)__fabs(diff) < 1.5707964f) {
                lbl_2_bss_1A824C[0]->_1978F1 = 0;
            } else {
                lbl_2_bss_1A824C[0]->_1978F1 = 2;
            }
        } else {
            lbl_2_bss_1A824C[0]->_1978F1 = 1;
        }
    }
    for (i = 1; i < 7; i++) {
        hit = (u8)fn_2_68C80(id, i);
        if (hit != 0 && i == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            owner->flagC4 = 2;
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 3;
            e->state = 0;
            return;
        }
        if (hit != 0 && i >= 2 && i <= 6) {
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 4;
            e->state = 0;
            return;
        }
        owner->flagCB = -1;
    }
    owner->state = 1;
}

// fn_2_6B4FC, size:0x124
void fn_2_6B4FC(MenuEntry* owner) {
    MenuEntry* entry;
    s32 off;
    f32 height;

    entry = (MenuEntry*)((u8*)lbl_2_bss_1A8248[0] + offsetof(MenuCtx, entries) + (off = owner->objectId * sizeof(MenuEntry)));
    if (entry->flagD0 != 0) {
        height = (f32)sin(entry->bouncePhase);
        height = lbl_2_rodata_BA8 * -height;
        entry->bouncePhase += lbl_2_rodata_BAC[0];
        if (entry->position.y > lbl_2_rodata_C28) {
            entry->bouncePhase = lbl_2_rodata_B58;
            height = lbl_2_rodata_B58;
            entry->flagD0 = 0;
            if (entry->typeC3 == 19) {
                ((u8*)lbl_2_bss_1A8248[0])[entry->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 0;
            }
        }
        entry->position.y = height;
    } else {
        entry->position.y = lbl_2_rodata_B58;
    }
    if (owner->flagD0 == 0) {
        MenuEntry* e = (MenuEntry*)((u8*)lbl_2_bss_1A8248[0] + off + offsetof(MenuCtx, entries));
        e->typeC3 = 0;
        e->state = 0;
    }
}

// fn_2_6FB0C, size:0x328
void fn_2_6FB0C(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 other = lbl_2_bss_1A8248[0]->entries[0].objectId;
    s32 mode;
    s32 who;

    ((u8*)lbl_2_bss_1A8248[0])[owner->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    fn_2_68FBC(owner->objectId, 1);
    owner->angle34 = owner->heading;
    if (id >= 2 && id <= 6 && (mode = (u8)lbl_2_bss_1A8248[0]->entries[0].flagCD, who = lbl_2_bss_1A8248[0]->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 2;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 2;
            return;
        }
        if (id >= 2 && id <= 6) {
            owner->flagCB = 0;
        }
    } else {
        owner->flagCB = -1;
    }
    owner->state = 1;
}

extern const f32 lbl_2_rodata_C48;
extern void fn_2_9033C(s32 index, const void* position, const f32* unused, f32 value, f32 unused2, f32 unused3);
extern void fn_2_92654(s32, u8);
extern void fn_2_8F73C(s32, u8);

// fn_2_6C5E0, size:0x358
void fn_2_6C5E0(MenuEntry* owner) {
    s32 id;
    s32 flag;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;
    f32 pos[3];

    id = owner->objectId;
    ((u8*)lbl_2_bss_1A8248[0])[owner->objectId * sizeof(MenuEntry) + offsetof(MenuCtx, entries[0].flagC0)] = 1;
    owner->mode = 11;
    if (lbl_2_bss_1A8248[0]->_4439 == 1) {
        memcpy(&owner->target, &lbl_2_data_2EA4[40], sizeof(Vec));
        flag = 1;
    } else if (owner->position.x > lbl_2_data_2EA4[40].x && owner->position.z > lbl_2_data_2EA4[40].z) {
        memcpy(&owner->target, &lbl_2_data_2EA4[42], sizeof(Vec));
        flag = 0;
    } else {
        memcpy(&owner->target, &lbl_2_data_2EA4[40], sizeof(Vec));
        flag = 1;
    }
    pz = owner->target.z;
    px = owner->target.x;
    entry = &lbl_2_bss_1A8248[0]->entries[id];
    entry->previousPosition.x = px;
    entry->previousPosition.z = pz;
    dx = px - entry->position.x;
    dz = pz - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
    fn_2_68FBC(id, 0);
    if (lbl_2_bss_1A824C[0]->_197843 == 0) {
        pos[0] = lbl_2_rodata_B6C[0] * owner->position.x;
        pos[1] = lbl_2_rodata_B6C[0] * (lbl_2_rodata_C48 + owner->position.y);
        pos[2] = lbl_2_rodata_B6C[0] * owner->position.z;
        fn_2_9033C(0x1C, pos, lbl_2_rodata_B6C, lbl_2_rodata_B58, lbl_2_rodata_C48, lbl_2_rodata_B6C[0]);
        fn_2_92654(0x1C, 10);
        fn_2_8F73C(0x1C, 1);
    }
    if (flag == 1) {
        owner->state = 1;
    } else {
        owner->state = 2;
    }
}

extern f32 lbl_2_bss_A170;
extern Vec lbl_2_data_2A340;

// .text:0x6A708 size:0x174
// NONMATCHING 86%: scheduling only; lbl_803C77B8 address and the int->float magic load move earlier than in the original
#if NONMATCHING
void fn_2_6A708(void) {
    Vec position;
    Vec delta;
    MenuEntry* player = &lbl_2_bss_1A8248[0]->entries[0];
    MenuStickPad* pad;

    memcpy(&position, &player->position, sizeof(Vec));
    PSVECSubtract(&position, &lbl_2_data_2A340, &delta);
    delta.x *= lbl_2_rodata_BB0;
    delta.z *= lbl_2_rodata_BB0;
    pad = (MenuStickPad*)&lbl_803C77B8;
    pad = &pad[(s8)(u8)lbl_2_bss_1A824C[0]->port];
    position.x += pad->stickX / lbl_2_rodata_C10;
    position.z += pad->stickY / lbl_2_rodata_C10;
    if (lbl_2_rodata_B58 != delta.x || lbl_2_rodata_B58 != delta.z) {
        lbl_2_bss_A170 = fn_2_4A1E8(delta.z, delta.x);
    }
    memcpy(&lbl_2_data_2A340, &player->position, sizeof(Vec));
    player->position.x = position.x;
    player->position.y = position.y;
    player->position.z = position.z;
    player->heading = lbl_2_bss_A170;
}
#endif

// .text:0x6A87C size:0x23C
// NONMATCHING 88%: original inlines fn_2_6A708 and fn_2_6A628; same scheduling issue as fn_2_6A708
#if NONMATCHING
void fn_2_6A87C(void) {
    lbl_2_bss_1A8248[0]->entries[0].flagBB = 0;
    fn_2_6A708();
    fn_2_6A628();
}
#endif

extern const f32 lbl_2_rodata_B70;

// Same as menuSqrtf, written with early returns (gives a different block order).
static inline f32 menuSqrtfR(f32 x) {
    if (x > 0.0f) {
        f64 xd = (f64)x;
        f64 guess = __frsqrte(xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
        return (f32)(xd * guess);
    } else if (x < lbl_2_rodata_B88) {
        return NAN;
    } else if (isnan(x)) {
        return NAN;
    }
    return x;
}

// .text:0x69070 size:0x260
// Distance from (x, z) to the entry: straight-line when it is (almost) still,
// otherwise the perpendicular distance to its line of motion.
f32 fn_2_69070(s32 index, f32 x, f32 z) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    f32 dz;
    f32 dx;
    f32 along;
    f32 distance;

    if (entry->_38 < lbl_2_rodata_B70) {
        dx = entry->position.x - x;
        dz = entry->position.z - z;
        {
            f32 xx = dx * dx;
            f32 zz = dz * dz;
            return menuSqrtf(xx + zz);
        }
    }
    dz = z - entry->position.z;
    dx = x - entry->position.x;
    along = entry->acceleration.x * dx + entry->acceleration.z * dz;
    distance = (dx * dx + dz * dz) - along * along;
    if (distance < 0.0f) {
        return 0.0f;
    }
    return menuSqrtfR(distance);
}

// .text:0x6B238 size:0x28C
void fn_2_6B238(MenuEntry* owner) {
    s32 id;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    id = owner->objectId;
    fn_2_68F08(id, 1);
    owner->mode = 14;
    owner->flagD0 = 1;
    owner->bouncePhase = 0.0f;
    owner->position.y = 0.0f;
    if (lbl_2_bss_1A8248[0]->entries[id].targetLocation == 48) {
        memcpy(&owner->target, &lbl_2_data_2EA4[50], sizeof(Vec));
    } else {
        memcpy(&owner->target, &lbl_2_data_2EA4[18], sizeof(Vec));
    }
    pz = owner->target.z;
    px = owner->target.x;
    entry = &lbl_2_bss_1A8248[0]->entries[id];
    entry->previousPosition.x = px;
    entry->previousPosition.z = pz;
    dx = px - entry->position.x;
    dz = pz - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
    fn_2_68FBC(id, 8);
    owner->state = 1;
}

extern MenuSpot lbl_2_data_3198[]; // menus/menu_work.h

// .text:0x6B744 size:0x2D4
void fn_2_6B744(MenuEntry* owner) {
    s32 id;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;
    Vec spot;

    id = owner->objectId;
    fn_2_68F08(id, 1);
    owner->mode = 12;
    owner->flagD0 = 1;
    owner->bouncePhase = 0.0f;
    owner->position.y = 0.0f;
    if (lbl_2_bss_1A8248[0]->entries[id].targetLocation == 48) {
        memcpy(&spot, &lbl_2_data_3198[25].position, sizeof(Vec));
        PSVECScale(&spot, lbl_2_rodata_B68[0], &spot);
        memcpy(&owner->target, &spot, sizeof(Vec));
    } else {
        memcpy(&spot, &lbl_2_data_3198[26].position, sizeof(Vec));
        PSVECScale(&spot, lbl_2_rodata_B68[0], &spot);
        memcpy(&owner->target, &spot, sizeof(Vec));
    }
    pz = owner->target.z;
    px = owner->target.x;
    entry = &lbl_2_bss_1A8248[0]->entries[id];
    entry->previousPosition.x = px;
    entry->previousPosition.z = pz;
    dx = px - entry->position.x;
    dz = pz - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
    fn_2_68FBC(id, 8);
    owner->state = 1;
}

// Per-fielder (ids 2..6) pointers to their home location.
extern s16* lbl_2_data_3C2C[];

// .text:0x6DB30 size:0x324
void fn_2_6DB30(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 other = lbl_2_bss_1A8248[0]->entries[0].objectId;
    s32 mode;
    s32 who;
    s16 timer;

    fn_2_69E1C(id);
    if (id >= 2 && id <= 6) {
        if (id == 2) { // no-op, but present in the original
            id = 2;
        }
        if ((mode = (u8)lbl_2_bss_1A8248[0]->entries[0].flagCD, who = lbl_2_bss_1A8248[0]->entries[0].flagCC, mode == 1) && who == id) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 4;
            return;
        }
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 4;
            return;
        }
        if (id >= 2 && id <= 6) {
            if (lbl_2_bss_1A8248[0]->entries[id].locationIndex == *lbl_2_data_3C2C[id - 2]) {
                owner->flagCB = 0;
                owner->timer = 0x78;
                owner->flagCF = 0;
            } else {
                owner->flagCB = 0;
                owner->flagCF = -1;
                owner->state = 0;
            }
        }
    } else {
        owner->flagCB = -1;
    }
    timer = owner->timer;
    owner->timer = timer - 1;
    if (timer == 0) {
        owner->state = 0;
    }
}

// .text:0x705C0 size:0x3E0
// NONMATCHING 99%: r4/r5 swapped for the menu base and the self entry before atan2
#if NONMATCHING
void fn_2_705C0(MenuEntry* owner) {
    s16* t;
    u8 type;
    s32 hi;
    s32 base;
    CharActor* p;
    s32 lo;
    s32 index;
    s32 b, c;
    s32 i;
    s32 hit;
    MenuEntry* e;

    index = owner->objectId;
    fn_2_69E1C(index);
    type = lbl_2_bss_1A8248[0]->_441C;
    t = lbl_2_data_2E80;
    base = t[type * 3] * 2;
    c = t[type * 3 + 2] * 2;
    b = t[type * 3 + 1] * 2;
    hi = base - c;
    lo = base - b;
    if (owner->objectId == 0) {
        p = &lbl_8036E548.actors[0];
        if (p != NULL) {
            c = p->_068;
            if (c == hi || c == lo) {
                if (type == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (owner->_38 <= lbl_2_rodata_B58) {
        owner->angle34 = owner->heading;
        e = &lbl_2_bss_1A8248[0]->entries[index];
        e->typeC3 = 4;
        e->state = 0;
    }
    for (i = 1; i < 7; i++) {
        hit = (u8)fn_2_68C80(index, i);
        if (hit != 0 && i == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            owner->flagC4 = 2;
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[index];
            e->typeC3 = 3;
            e->state = 0;
            return;
        }
        owner->flagCB = -1;
    }
    if (owner->flagCD == 1) {
        MenuEntry* other;
        MenuEntry* self;
        f32 angle;
        f32 diff;

        self = &lbl_2_bss_1A8248[0]->entries[index];
        other = &lbl_2_bss_1A8248[0]->entries[owner->flagCE];
        angle = (f32)atan2(-(self->position.x - other->position.x), -(self->position.z - other->position.z));
        diff = fn_2_4A18C(other->heading) - angle;

        if (other->typeC3 == 7 && (owner->state == 0 || owner->state == 1)) {
            if ((f32)__fabs(diff) < lbl_2_rodata_BB8) {
                lbl_2_bss_1A824C[0]->_1978F1 = 0;
            } else {
                lbl_2_bss_1A824C[0]->_1978F1 = 2;
            }
        } else {
            lbl_2_bss_1A824C[0]->_1978F1 = 1;
        }
        owner->mode = 4;
        owner->flagC4 = 1;
        owner->locationIndex = fn_2_689CC(0);
        e = &lbl_2_bss_1A8248[0]->entries[index];
        e->typeC3 = 4;
        e->state = 0;
    }
}
#endif

// .text:0x699D4 size:0x448
void fn_2_699D4(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    Mtx rotation;
    Vec movement;
    f32 dx;
    f32 dz;
    f32 distance;
    f32 difference;
    f32 magnitude;
    f32 step;

    if (entry->_38 <= 0.0f) {
        entry->_38 = 0.0f;
    }
    entry->_50 -= entry->_38;
    dx = entry->position.x - entry->previousPosition.x;
    dz = entry->position.z - entry->previousPosition.z;
    {
        f32 xx = dx * dx;
        f32 zz = dz * dz;
        distance = xx + zz;
        if (distance > 0.0f) {
            f64 xd = (f64)distance;
            f64 guess = __frsqrte(xd);
            guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
            guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
            guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
            distance = (f32)(xd * guess);
        } else if (distance < lbl_2_rodata_B88) {
            distance = NAN;
        } else if (isnan(distance)) {
            distance = NAN;
        }
    }
    if (distance < entry->_38) {
        entry->_50 = lbl_2_rodata_BB0;
    }
    if (entry->mode != 4 && entry->mode != 24 && entry->_50 > lbl_2_rodata_B58) {
        entry->heading = (f32)atan2(-(entry->previousPosition.x - entry->position.x),
            -(entry->previousPosition.z - entry->position.z));
    }
    PSMTXRotRad(rotation, 'Y', entry->angle34);
    movement.x = lbl_2_rodata_B58;
    movement.y = lbl_2_rodata_B58;
    movement.z = lbl_2_rodata_B58;
    PSMTXMultVec(rotation, &movement, &movement);
    entry->velocity.x = movement.x;
    entry->velocity.z = movement.z;
    entry->position.x += entry->velocity.x;
    entry->position.z += entry->velocity.z;
    if (entry->mode != 4 && entry->mode != 24 && entry->_50 > lbl_2_rodata_B58) {
        entry->heading = (f32)atan2(-(entry->previousPosition.x - entry->position.x),
            -(entry->previousPosition.z - entry->position.z));
        difference = fn_2_4A18C(entry->angle34 - entry->heading);
        magnitude = (f32)__fabs(difference);
        if (magnitude > lbl_2_rodata_BB4) {
            step = lbl_2_rodata_BB8;
        } else if (magnitude > lbl_2_rodata_BB8) {
            step = lbl_2_rodata_BBC;
        } else if (magnitude > lbl_2_rodata_BBC) {
            step = lbl_2_rodata_BC0;
        } else if (magnitude > lbl_2_rodata_BC0) {
            step = lbl_2_rodata_BC4;
        } else if (magnitude > lbl_2_rodata_BC4) {
            step = lbl_2_rodata_BC8;
        } else if (magnitude > lbl_2_rodata_BC8) {
            step = lbl_2_rodata_BCC;
        } else if (magnitude > lbl_2_rodata_BCC) {
            step = lbl_2_rodata_BD0;
        } else if (magnitude > lbl_2_rodata_BD0) {
            step = lbl_2_rodata_BD4;
        } else if (magnitude < lbl_2_rodata_BD0) {
            step = lbl_2_rodata_BD8;
        }
        if (!((difference < lbl_2_rodata_BE0 && difference > lbl_2_rodata_B58) ||
              (difference > lbl_2_rodata_BE8 && difference < lbl_2_rodata_B58))) {
            if (difference < lbl_2_rodata_B58) {
                entry->angle34 += step;
            } else {
                entry->angle34 -= step;
            }
        }
        entry->heading = entry->angle34;
    }
    if (lbl_2_rodata_B58 == entry->_38 && entry->flagBD == 0) {
        entry->flagBC = 1;
    }
}

extern const f32 lbl_2_rodata_BF0;
extern const f32 lbl_2_rodata_BF4;
extern const f32 lbl_2_rodata_BF8;
extern const f32 lbl_2_rodata_BFC;
extern const f32 lbl_2_rodata_C00;
extern const f32 lbl_2_rodata_C04;
extern const f32 lbl_2_rodata_C08;
extern const f32 lbl_2_rodata_C0C;
extern f32 lbl_2_data_3F44[];

// .text:0x69E1C size:0x634
void fn_2_69E1C(s32 index) {
    MenuEntry* entry = &lbl_2_bss_1A8248[0]->entries[index];
    Mtx rotation;
    Vec movement;
    f32 dx;
    f32 dz;
    f32 distance;
    f32 difference;
    f32 magnitude;
    f32 step;

    if (entry->_50 > lbl_2_rodata_B58) {
        s16 heading = fn_2_4A2C4(entry->heading);
        fn_2_4A310(heading, fn_2_4A2C4(entry->_54));
        entry->flagBC = 0;
        entry->flagBD = 0;
        if (entry->_9E < 0x7FFE) {
            entry->_9E++;
        } else {
            entry->_9E = 0x7FFF;
        }
    } else {
        entry->flagBC = 1;
        if (entry->_9E > 45) {
            entry->_9E = 45;
        }
        if (entry->_9E != 0) {
            entry->_9E--;
        }
    }
    switch (entry->mode) {
    case 0:
        fn_2_69710(index);
        break;
    case 1:
    case 5:
        entry->_38 -= lbl_2_rodata_BF0;
        break;
    case 2:
    case 6:
        entry->_38 -= lbl_2_rodata_BF4;
        break;
    case 3:
    case 7:
        entry->_38 -= lbl_2_rodata_BF8;
        break;
    case 4:
    case 8:
        entry->mode += 20;
        break;
    case 24:
    case 28:
        entry->_38 -= lbl_2_rodata_BFC;
        break;
    case 9:
        entry->_38 = lbl_2_rodata_B58;
        break;
    case 10:
        entry->_38 = lbl_2_rodata_C00;
        break;
    case 11:
        entry->_38 = lbl_2_rodata_BA4;
        break;
    case 12:
        if (index == 0) {
            entry->_38 = lbl_2_data_3F44[lbl_2_bss_1A8248[0]->_441C];
        } else {
            entry->_38 = lbl_2_rodata_C04;
        }
        break;
    case 13:
        entry->_38 = lbl_2_rodata_C08;
        break;
    case 14:
        entry->_38 = lbl_2_rodata_C0C;
        break;
    }
    if (entry->_38 <= 0.0f) {
        entry->_38 = 0.0f;
    }
    entry->_50 -= entry->_38;
    dx = entry->position.x - entry->previousPosition.x;
    dz = entry->position.z - entry->previousPosition.z;
    {
        f32 xx = dx * dx;
        f32 zz = dz * dz;
        distance = xx + zz;
        if (distance > 0.0f) {
            f64 xd = (f64)distance;
            f64 guess = __frsqrte(xd);
            guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
            guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
            guess = lbl_2_rodata_B78 * guess * (lbl_2_rodata_B80 - guess * guess * xd);
            distance = (f32)(xd * guess);
        } else if (distance < lbl_2_rodata_B88) {
            distance = NAN;
        } else if (isnan(distance)) {
            distance = NAN;
        }
    }
    if (distance < entry->_38) {
        entry->_50 = lbl_2_rodata_BB0;
    }
    if (!(entry->_38 <= lbl_2_rodata_B58)) {
        if (entry->mode != 4 && entry->mode != 24 && entry->_50 > lbl_2_rodata_B58) {
            entry->heading = (f32)atan2(-(entry->previousPosition.x - entry->position.x),
                -(entry->previousPosition.z - entry->position.z));
        }
        PSMTXRotRad(rotation, 'Y', entry->angle34);
        movement.x = lbl_2_rodata_B58;
        movement.y = lbl_2_rodata_B58;
        movement.z = -entry->_38;
        PSMTXMultVec(rotation, &movement, &movement);
        entry->velocity.x = movement.x;
        entry->velocity.z = movement.z;
        entry->position.x += entry->velocity.x;
        entry->position.z += entry->velocity.z;
        if (entry->mode != 4 && entry->mode != 24 && entry->_50 > lbl_2_rodata_B58) {
            entry->heading = (f32)atan2(-(entry->previousPosition.x - entry->position.x),
                -(entry->previousPosition.z - entry->position.z));
            difference = fn_2_4A18C(entry->angle34 - entry->heading);
            magnitude = (f32)__fabs(difference);
            if (magnitude > lbl_2_rodata_BB4) {
                step = lbl_2_rodata_BB8;
            } else if (magnitude > lbl_2_rodata_BB8) {
                step = lbl_2_rodata_BBC;
            } else if (magnitude > lbl_2_rodata_BBC) {
                step = lbl_2_rodata_BC0;
            } else if (magnitude > lbl_2_rodata_BC0) {
                step = lbl_2_rodata_BC4;
            } else if (magnitude > lbl_2_rodata_BC4) {
                step = lbl_2_rodata_BC8;
            } else if (magnitude > lbl_2_rodata_BC8) {
                step = lbl_2_rodata_BCC;
            } else if (magnitude > lbl_2_rodata_BCC) {
                step = lbl_2_rodata_BD0;
            } else if (magnitude > lbl_2_rodata_BD0) {
                step = lbl_2_rodata_BD4;
            } else if (magnitude < lbl_2_rodata_BD0) {
                step = lbl_2_rodata_BD8;
            }
            if (!((difference < lbl_2_rodata_BE0 && difference > lbl_2_rodata_B58) ||
                  (difference > lbl_2_rodata_BE8 && difference < lbl_2_rodata_B58))) {
                if (difference < lbl_2_rodata_B58) {
                    entry->angle34 += step;
                } else {
                    entry->angle34 -= step;
                }
            }
            entry->heading = entry->angle34;
        }
    }
    if (lbl_2_rodata_B58 == entry->_38 && entry->flagBD == 0) {
        entry->flagBC = 1;
    }
}

// .text:0x6F104 size:0x5F0
// NONMATCHING 99%: r5/r8 swapped for the candidate pointer and the locationIndex offset in the loop
#if NONMATCHING
void fn_2_6F104(MenuEntry* owner) {
    s16 candidates[4];
    s16* out;
    s32 i;
    s32 count;
    s32 id;
    s32 other;
    s32 mode;
    s32 who;
    s16 location;
    MenuCtx* menu;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    count = 0;
    candidates[3] = 0;
    candidates[2] = 0;
    candidates[1] = 0;
    candidates[0] = 0;
    id = owner->objectId;
    other = lbl_2_bss_1A8248[0]->entries[0].objectId;
    fn_2_68F08(owner->objectId, 1);
    out = candidates;
    menu = lbl_2_bss_1A8248[0];
    for (i = 0; i < 4; i++) {
        location = lbl_2_data_3D30[menu->entries[id].locationIndex][i];
        if (location != -1 && menu->slots[location]._6 == 0 &&
            menu->slots[location]._4 != 7 && menu->slots[location]._4 != 8) {
            *out++ = location;
            count++;
        }
    }
    lbl_2_bss_1A8248[0]->entries[id].targetLocation = candidates[(s16)(rand() % count)];
    memcpy(&owner->target, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[id].targetLocation], sizeof(Vec));
    pz = owner->target.z;
    px = owner->target.x;
    fn_2_6A450(id, px, pz);
    owner->mode = 13;
    fn_2_69E1C(id);
    fn_2_68FBC(id, 0);
    if (id >= 2 && id <= 6 && (mode = (u8)lbl_2_bss_1A8248[0]->entries[0].flagCD, who = lbl_2_bss_1A8248[0]->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 3;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 3;
            return;
        }
        if (id >= 2 && id <= 6) {
            owner->flagCB = 0;
        } else {
            owner->flagCB = -1;
            owner->state = 1;
        }
    } else {
        owner->flagCB = -1;
        owner->state = 1;
    }
}
#endif

// Per-fielder (ids 2..6) location-choice counts and fallback home locations.
extern s16 lbl_2_data_3C20[];
extern s16 lbl_2_data_3ED4[];

// .text:0x6E1D0 size:0x678
void fn_2_6E1D0(MenuEntry* owner) {
    s32 id;
    s32 other;
    s16 location;
    s32 count;
    s16* choices;
    s16 choice;
    s32 mode;
    s32 who;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    id = owner->objectId;
    other = lbl_2_bss_1A8248[0]->entries[0].objectId;
    fn_2_68F08(owner->objectId, 1);
    count = lbl_2_data_3C20[id - 2];
    choices = lbl_2_data_3C2C[id - 2];
    choice = rand() % count;
    if (owner->flagCF == -1) {
        choice = 0;
        owner->flagCF = 0;
    } else {
        location = choices[choice];
        if (location == owner->locationIndex) {
            choice ^= 1;
        }
    }
    location = choices[choice];
    lbl_2_bss_1A8248[0]->entries[id].targetLocation = location;
    memcpy(&owner->target, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[id].targetLocation], sizeof(Vec));
    pz = owner->target.z;
    px = owner->target.x;
    entry = &lbl_2_bss_1A8248[0]->entries[id];
    entry->previousPosition.x = px;
    entry->previousPosition.z = pz;
    dx = px - entry->position.x;
    dz = pz - entry->position.z;
    if (0.0f == dx && 0.0f == dz) {
        entry->_38 = 0.0f;
        entry->_50 = 0.0f;
    } else {
        dx = dx * dx + dz * dz;
        entry->_50 = menuSqrtf(dx);
    }
    entry->flagBB = 1;
    owner->mode = 13;
    fn_2_69E1C(id);
    fn_2_68FBC(id, 0);
    if (id >= 2 && id <= 6 && (mode = (u8)lbl_2_bss_1A8248[0]->entries[0].flagCD, who = lbl_2_bss_1A8248[0]->entries[0].flagCC, mode == 1) && who == id) {
        fn_2_68FBC(id, 1);
        owner->flagC4 = 2;
        owner->flagCB = 0;
        owner->state = 4;
        return;
    }
    if ((u8)fn_2_68C80(id, other)) {
        if (id == 1) {
            fn_2_68FBC(id, 1);
            owner->flagC4 = 2;
            owner->flagCB = 0;
            owner->state = 3;
            return;
        }
        if (id >= 2 && id <= 6) {
            if ((lbl_2_bss_1A8248[0]->entries[id].locationIndex == location &&
                 lbl_2_bss_1A8248[0]->entries[id].targetLocation == location) ||
                (lbl_2_bss_1A8248[0]->entries[id].locationIndex == lbl_2_data_3ED4[id - 2] &&
                 lbl_2_bss_1A8248[0]->entries[id].targetLocation == lbl_2_data_3ED4[id - 2])) {
                if (owner->_50 <= lbl_2_rodata_B70) {
                    owner->timer = 0x78;
                    fn_2_68FBC(id, 1);
                    owner->mode = 9;
                    owner->_50 = lbl_2_rodata_B58;
                    owner->_38 = lbl_2_rodata_B58;
                    owner->flagCF = 0;
                    owner->state = 2;
                    return;
                }
            }
            owner->flagCB = 0;
            owner->flagCF = -1;
            owner->state = 0;
        }
    } else {
        owner->flagCB = -1;
        owner->state = 1;
    }
}

// .text:0x709A0 size:0x6F8
// NONMATCHING 99%: r4/r5 swapped for the menu base and the self entry before atan2 (as in fn_2_705C0)
#if NONMATCHING
void fn_2_709A0(MenuEntry* owner) {
    s32 id = owner->objectId;
    s32 i;
    s32 hit;
    s32 inFront = 0;
    MenuEntry* e;
    s16* t;
    u8 type;
    s32 hi;
    s32 base;
    CharActor* p;
    s32 lo;
    s32 b, c;

    for (i = 1; i < 7; i++) {
        if ((u8)fn_2_68C80(id, i)) {
            owner->flagCB = i;
            break;
        }
        owner->flagCB = -1;
    }
    if (owner->flagCB >= 2 && owner->flagCB <= 6) {
        fn_2_68940(id, owner->flagCB);
        inFront = fn_2_687A4(id, owner->flagCB, lbl_2_bss_1A8248[0]->entries[0].targetLocation);
    }
    for (i = 1; i < 7; i++) {
        hit = (u8)fn_2_68C80(id, i);
        if (hit != 0 && i == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            owner->flagC4 = 2;
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 3;
            e->state = 0;
            return;
        }
        if (hit != 0 && i >= 2 && i <= 6) {
            owner->mode = 4;
            owner->flagC4 = 1;
            owner->locationIndex = fn_2_689CC(0);
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 4;
            e->state = 0;
            return;
        }
        owner->flagCB = -1;
    }
    if (inFront == 0) {
        fn_2_69E1C(id);
    } else {
        fn_2_699D4(id);
    }
    type = lbl_2_bss_1A8248[0]->_441C;
    t = lbl_2_data_2E80;
    base = t[type * 3] * 2;
    c = t[type * 3 + 2] * 2;
    b = t[type * 3 + 1] * 2;
    hi = base - c;
    lo = base - b;
    if (owner->objectId == 0) {
        p = &lbl_8036E548.actors[0];
        if (p != NULL) {
            c = p->_068;
            if (c == hi || c == lo) {
                if (type == 5) {
                    fn_80062890(1);
                } else {
                    fn_80062890(0);
                }
            }
        }
    }
    if (owner->_50 <= lbl_2_rodata_B58) {
        owner->mode = 4;
        owner->flagC4 = 1;
        if (lbl_2_bss_1A824C[0]->_19783D == 0) {
            lbl_2_bss_1A8248[0]->entries[0].locationIndex = lbl_2_bss_1A8248[0]->entries[0].targetLocation;
        } else {
            lbl_2_bss_1A8248[0]->entries[0].locationIndex = lbl_2_bss_1A8248[0]->entries[0]._AE;
        }
        owner->state = 2;
        return;
    }
    if (owner->flagCD == 1) {
        MenuEntry* other;
        MenuEntry* self;
        f32 angle;
        f32 diff;

        self = &lbl_2_bss_1A8248[0]->entries[id];
        other = &lbl_2_bss_1A8248[0]->entries[owner->flagCE];
        angle = (f32)atan2(-(self->position.x - other->position.x), -(self->position.z - other->position.z));
        diff = fn_2_4A18C(other->heading) - angle;
        if (other->typeC3 == 7 && (owner->state == 0 || owner->state == 1)) {
            if ((f32)__fabs(diff) < lbl_2_rodata_BB8) {
                lbl_2_bss_1A824C[0]->_1978F1 = 0;
            } else {
                lbl_2_bss_1A824C[0]->_1978F1 = 2;
            }
        } else {
            lbl_2_bss_1A824C[0]->_1978F1 = 1;
        }
        owner->mode = 4;
        owner->flagC4 = 1;
        owner->locationIndex = fn_2_689CC(0);
        e = &lbl_2_bss_1A8248[0]->entries[id];
        e->typeC3 = 4;
        e->state = 0;
    }
}
#endif

// .text:0x71098 size:0x9A0
// NONMATCHING 99%: r4/r5 swapped for the menu base and the self entry before atan2 (as in fn_2_705C0)
#if NONMATCHING
void fn_2_71098(MenuEntry* owner) {
    s32 id;
    s32 inFront;
    s32 i;
    s32 hit;
    MenuEntry* e;
    MenuEntry* entry;
    f32 dx;
    f32 dz;
    f32 px;
    f32 pz;

    id = owner->objectId;
    fn_2_68F08(owner->objectId, 1);
    inFront = 0;
    memcpy(&owner->target, &lbl_2_data_2EA4[lbl_2_bss_1A8248[0]->entries[0].targetLocation], sizeof(Vec));
    pz = owner->target.z;
    px = owner->target.x;
    fn_2_6A450(id, px, pz);
    owner->mode = 12;
    for (i = 1; i < 7; i++) {
        if ((u8)fn_2_68C80(id, i)) {
            owner->flagCB = i;
            break;
        }
        owner->flagCB = -1;
    }
    if (owner->flagCB >= 2 && owner->flagCB <= 6) {
        fn_2_68940(id, owner->flagCB);
        inFront = fn_2_687A4(id, owner->flagCB, lbl_2_bss_1A8248[0]->entries[0].targetLocation);
    }
    if (inFront == 0) {
        fn_2_69E1C(id);
    } else {
        fn_2_699D4(id);
    }
    fn_2_68FBC(id, 0);
    for (i = 1; i < 7; i++) {
        hit = (u8)fn_2_68C80(id, i);
        if (hit != 0 && i == 1 && lbl_2_bss_1A8248[0]->_44F3 == 0) {
            owner->flagC4 = 2;
            owner->flagCB = i;
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 3;
            e->state = 0;
            return;
        }
        if (hit != 0 && i >= 2 && i <= 6) {
            owner->mode = 4;
            owner->flagC4 = 1;
            owner->locationIndex = fn_2_689CC(0);
            e = &lbl_2_bss_1A8248[0]->entries[id];
            e->typeC3 = 4;
            e->state = 0;
            return;
        }
        owner->flagCB = -1;
        owner->state = 1;
    }
    if (owner->flagCD == 1) {
        MenuEntry* other;
        MenuEntry* self;
        f32 angle;
        f32 diff;

        self = &lbl_2_bss_1A8248[0]->entries[id];
        other = &lbl_2_bss_1A8248[0]->entries[owner->flagCE];
        angle = (f32)atan2(-(self->position.x - other->position.x), -(self->position.z - other->position.z));
        diff = fn_2_4A18C(other->heading) - angle;
        if (other->typeC3 == 7 && (owner->state == 0 || owner->state == 1)) {
            if ((f32)__fabs(diff) < lbl_2_rodata_BB8) {
                lbl_2_bss_1A824C[0]->_1978F1 = 0;
            } else {
                lbl_2_bss_1A824C[0]->_1978F1 = 2;
            }
        } else {
            lbl_2_bss_1A824C[0]->_1978F1 = 1;
        }
        owner->mode = 4;
        owner->flagC4 = 1;
        owner->locationIndex = fn_2_689CC(0);
        e = &lbl_2_bss_1A8248[0]->entries[id];
        e->typeC3 = 4;
        e->state = 0;
    }
    if (owner->_50 <= lbl_2_rodata_B58) {
        owner->mode = 9;
        owner->flagC4 = 1;
        if (lbl_2_bss_1A824C[0]->_19783D == 0) {
            lbl_2_bss_1A8248[0]->entries[0].locationIndex = lbl_2_bss_1A8248[0]->entries[0].targetLocation;
        } else {
            lbl_2_bss_1A8248[0]->entries[0].locationIndex = lbl_2_bss_1A8248[0]->entries[0]._AE;
        }
        fn_2_68FBC(id, 1);
        owner->flagC4 = 1;
        owner->locationIndex = fn_2_689CC(0);
        e = &lbl_2_bss_1A8248[0]->entries[id];
        e->typeC3 = 4;
        e->state = 0;
    }
}
#endif

// .data 0x2A1E8-0x2A3C0: per-object state handler tables, then the per-type init table.
// .data 0x0002A1E8..0x0002A3C0
void *lbl_2_data_2A1E8[3] = {fn_2_71C6C, fn_2_71B80, fn_2_71A70};
void (*lbl_2_data_2A1F4[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_71098, (void (*)(MenuEntry*))fn_2_709A0, (void (*)(MenuEntry*))fn_2_705C0};
void (*lbl_2_data_2A200[2])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_704AC, (void (*)(MenuEntry*))fn_2_704A0};
void (*lbl_2_data_2A208[2])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_70110, (void (*)(MenuEntry*))fn_2_6FE6C};
void (*lbl_2_data_2A210[4])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6FB0C, (void (*)(MenuEntry*))fn_2_6F88C, (void (*)(MenuEntry*))fn_2_6F78C, (void (*)(MenuEntry*))fn_2_6F72C};
void (*lbl_2_data_2A220[5])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6F104, (void (*)(MenuEntry*))fn_2_6ED30, (void (*)(MenuEntry*))fn_2_6EA74, (void (*)(MenuEntry*))fn_2_6E88C, (void (*)(MenuEntry*))fn_2_6E880};
void (*lbl_2_data_2A234[5])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6E1D0, (void (*)(MenuEntry*))fn_2_6DE54, (void (*)(MenuEntry*))fn_2_6DB30, (void (*)(MenuEntry*))fn_2_6D968, (void (*)(MenuEntry*))fn_2_6D878};
void (*lbl_2_data_2A248[2])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6D754, (void (*)(MenuEntry*))fn_2_6D748};
void (*lbl_2_data_2A250[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6D5D4, (void (*)(MenuEntry*))fn_2_6D4F8, (void (*)(MenuEntry*))fn_2_6D4E8};
void (*lbl_2_data_2A25C[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6D374, (void (*)(MenuEntry*))fn_2_6D298, (void (*)(MenuEntry*))fn_2_6D288};
void (*lbl_2_data_2A268[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6D164, (void (*)(MenuEntry*))fn_2_6D088, (void (*)(MenuEntry*))fn_2_6D078};
void (*lbl_2_data_2A274[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6CDD4, (void (*)(MenuEntry*))fn_2_6CCB8, (void (*)(MenuEntry*))fn_2_6CBB0};
void (*lbl_2_data_2A280[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6C988, (void (*)(MenuEntry*))fn_2_6C97C, (void (*)(MenuEntry*))fn_2_6C970};
void (*lbl_2_data_2A28C[4])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6C5E0, (void (*)(MenuEntry*))fn_2_6C348, (void (*)(MenuEntry*))fn_2_6C2E8, (void (*)(MenuEntry*))fn_2_6C2C4};
void (*lbl_2_data_2A29C[4])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6C190, (void (*)(MenuEntry*))fn_2_6C120, (void (*)(MenuEntry*))fn_2_6C020, (void (*)(MenuEntry*))fn_2_6BFC0};
void (*lbl_2_data_2A2AC[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6BE80, (void (*)(MenuEntry*))fn_2_6BDE0, (void (*)(MenuEntry*))fn_2_6BDD4};
void (*lbl_2_data_2A2B8[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6BCAC, (void (*)(MenuEntry*))fn_2_6BC0C, (void (*)(MenuEntry*))fn_2_6BC00};
void (*lbl_2_data_2A2C4[4])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6BB7C, (void (*)(MenuEntry*))fn_2_6BAD8, (void (*)(MenuEntry*))fn_2_6BAAC, (void (*)(MenuEntry*))fn_2_6BA50};
void (*lbl_2_data_2A2D4[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6B744, (void (*)(MenuEntry*))fn_2_6B620, (void (*)(MenuEntry*))fn_2_6B4FC};
void (*lbl_2_data_2A2E0[3])(MenuEntry* object) = {(void (*)(MenuEntry*))fn_2_6B238, (void (*)(MenuEntry*))fn_2_6B120, (void (*)(MenuEntry*))fn_2_6B024};
void fn_2_71EFC(u8* obj);
void fn_2_71EC4(u8* obj);
void *lbl_2_data_2A2EC[21] = {
    fn_2_71EFC,
    fn_2_71EC4,
    fn_2_71A38,
    fn_2_70588,
    fn_2_7045C,
    fn_2_6FE34,
    fn_2_6F6F4,
    fn_2_6E848,
    fn_2_6D840,
    fn_2_6D710,
    fn_2_6D4B0,
    fn_2_6D250,
    fn_2_6D040,
    fn_2_6CB78,
    fn_2_6C938,
    fn_2_6C28C,
    fn_2_6BF88,
    fn_2_6BD9C,
    fn_2_6BBC8,
    fn_2_6BA18,
    fn_2_6B4C4,
};
Vec lbl_2_data_2A340 = {0.0f, 0.0f, 0.0f};

