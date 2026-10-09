#include "menus/rep_1028.h"

extern void* lbl_2_bss_3401BC;
extern const f32 lbl_2_rodata_1080;
extern const f32 lbl_2_rodata_1078;
typedef struct {
    u32 pad0;
    u32 resource;
    u8 pad8[6];
    s16 type;
    u8 pad10[0x44];
    f32 f54;
    u8 enabled;
    u8 flag59;
    u8 flag5A;
    u8 mode;
    f32 f5C;
    f32 f60;
} MenuEffect;

#include <string.h>
#include <math.h>

#include "static/UnknownHomes_Static.h"
extern void* lbl_2_bss_340140[];

extern u8 lbl_800F7478[];

extern void fn_2_8AC84(s32 index, s32 value);
typedef struct {
    u8 _00[0x90];
    s16 state;
    u8 _92[0x19];
    u8 active;
    u8 _AC[0x10];
} MenuSlot;

typedef struct {
    u8 _00[0x21E0];
    MenuSlot slots[32];
} MenuSlots;

extern MenuSlots* lbl_2_bss_1A8248[];
extern MenuStateCallback lbl_2_data_308A4[3];
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

extern u8 lbl_2_data_3198[];
extern const f32 lbl_2_rodata_1084;
extern const f64 lbl_2_rodata_1088;
extern const f32 lbl_2_rodata_10B8[];
extern const f32 lbl_2_rodata_10BC;
extern u8 lbl_2_data_30900[];
extern const f32 lbl_2_rodata_10A8[];
extern const f32 lbl_2_rodata_10AC[];
extern const f32 lbl_2_rodata_10B4[];
extern const f32 lbl_2_rodata_10B0;
extern u8 lbl_2_data_369C[];

// .text:0x904A8 size:0x90
void fn_2_904A8(void) {
    u8* slot;
    s32 i;
    for (i = 0; i < 29; i++) {
        slot = (u8*)&lbl_2_bss_1A8248[0]->slots[i];
        *(s32*)(slot + 0x78) = i;
        *(s32*)(slot + 0x7C) = i;
        *(f32*)(slot + 0x84) = lbl_2_rodata_1080;
        *(f32*)(slot + 0x38) = lbl_2_rodata_1080;
        *(f32*)(slot + 0x3C) = lbl_2_rodata_1080;
        slot[0xAA] = 0;
        *(s16*)(slot + 0x92) = i;
        *(s16*)(slot + 0x94) = -1;
        slot[0xA8] = 0;
        slot[0xAB] = 0;
        *(s16*)(slot + 0x90) = 0;
        *(s8*)(slot + 0xAE) = -1;
        slot[0xAC] = 0;
        slot[0xAD] = 0;
        *(f32*)(slot + 0x80) = lbl_2_rodata_1080;
        *(s16*)(slot + 0xA6) = 0;
        slot[0xB2] = 0xFF;
        slot[0xB4] = 0;
    }
}

// .text:0x8FC88 size:0x8C
void fn_2_8FC88(s32 index) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0xC);
        MenuEffect* effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        u8 valid;
        effect->resource = resource;
        effect->type = 0;
        valid = resource != 0;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        effect->flag5A = effect->flag59 = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// .text:0x903A8 size:0x80
void fn_2_903A8(s32 index) {
    s32 offset = index * 0x14;
    MenuSlot* slot = &lbl_2_bss_1A8248[0]->slots[index];
    memcpy(slot, lbl_2_data_369C + offset, 12);
    *(f32*)((u8*)slot + 0x30) = lbl_2_rodata_1080;
    *(f32*)((u8*)slot + 0x28) = ((f32*)lbl_2_data_369C)[index * 5 + 3];
}

// .text:0x90428 size:0x80
void fn_2_90428(s32 index) {
    s32 offset = index * 0x14;
    MenuSlot* slot = &lbl_2_bss_1A8248[0]->slots[index];
    memcpy(slot, lbl_2_data_3198 + offset, 12);
    *(f32*)((u8*)slot + 0x30) = lbl_2_rodata_1080;
    *(f32*)((u8*)slot + 0x28) = ((f32*)lbl_2_data_3198)[index * 5 + 3];
}

// .text:0x00091B7C size:0x4
void fn_2_91B7C(void) {}

// .text:0x00091B28 size:0x4
void fn_2_91B28(void) {}

// .text:0x00091C40 size:0xC
void fn_2_91C40(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x00091B70 size:0xC
void fn_2_91B70(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x00091B2C size:0xC
void fn_2_91B2C(u8* object) {
    *(s16*)(object + 0x90) = 1;
}

// .text:0x00091B1C size:0xC
void fn_2_91B1C(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x000919C0 size:0xC
void fn_2_919C0(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x000919B4 size:0xC
void fn_2_919B4(u8* object) {
    *(s16*)(object + 0x90) = 2;
}

// .text:0x000918E8 size:0xC
void fn_2_918E8(u8* object) {
    *(s16*)(object + 0x90) = 2;
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

void fn_2_90E98(u8* object) {
    MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
    entry->active = 0;
    entry->state = 0;
}

void fn_2_90C14(u8* object) {
    if (*(s16*)(object + 0xA0) == 1) {
        MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
        entry->active = 0;
        entry->state = 0;
    }
}

void fn_2_90838(u8* object) {
    if (*(s16*)(object + 0xA0) == 1) {
        fn_2_8AC84(*(s32*)(object + 0x78), 0);
        *(s16*)(object + 0xA0) = 2;
    }
    *(s16*)(object + 0x90) = 2;
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
void fn_2_90628(u8* object) {
    if (*(s16*)(object + 0xA0) == 1) {
        fn_2_8AC84(*(s32*)(object + 0x78), 0);
        *(s16*)(object + 0xA0) = 2;
        {
            MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
            entry->active = 0;
            entry->state = 0;
        }
    }
}

// fn_2_8F688, size:0x48
void fn_2_8F688(void) {
    GXColor color = *(GXColor*)(lbl_800F7478 + 0x28);
    color.a = 0xFF;
    fn_800BD2CC(0, color);
}

// fn_2_8F640, size:0x48
void fn_2_8F640(void) {
    GXColor color = *(GXColor*)(lbl_800F7478 + 0x28);
    color.a = 0xFF;
    fn_800BD2CC(1, color);
}

// fn_2_8F774, size:0x3C
void fn_2_8F774(s32 index) {
    u8* data = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x68);
    fn_800B4A94(((void**)data)[index * 0x24 + 13]);
}

// fn_2_916F8, size:0x84
void fn_2_916F8(u8* object) {
    u8* data = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x68);
    if (fn_800B4A94(((void**)data)[*(s32*)(object + 0x78) * 0x24 + 13]) == 0.0f) {
        MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_91488, size:0x84
void fn_2_91488(u8* object) {
    u8* data = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x68);
    if (fn_800B4A94(((void**)data)[*(s32*)(object + 0x78) * 0x24 + 13]) == 0.0f) {
        MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_91218, size:0x84
void fn_2_91218(u8* object) {
    u8* data = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x68);
    if (fn_800B4A94(((void**)data)[*(s32*)(object + 0x78) * 0x24 + 13]) == 0.0f) {
        MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_90A2C, size:0x84
void fn_2_90A2C(u8* object) {
    u8* data = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x68);
    if (fn_800B4A94(((void**)data)[*(s32*)(object + 0x78) * 0x24 + 13]) == 0.0f) {
        MenuSlot* entry = &lbl_2_bss_1A8248[0]->slots[*(s32*)(object + 0x78)];
        entry->active = 2;
        entry->state = 0;
    }
}

// fn_2_9033C, size:0x6C
void fn_2_9033C(s32 index, const void* position, f32 value) {
    MenuSlot* slot = &lbl_2_bss_1A8248[0]->slots[index];
    memcpy(slot, position, 0xC);
    *(f32*)((u8*)slot + 0x28) = value;
    *(f32*)((u8*)slot + 0x30) = 0.0f;
    *(f32*)((u8*)slot + 0x28) = value;
}

// fn_2_8F7B0, size:0x88
void fn_2_8F7B0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x4C);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// fn_2_8F838, size:0x88
void fn_2_8F838(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x48);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// fn_2_8F8C0, size:0x88
void fn_2_8F8C0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x44);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// fn_2_8F948, size:0x88
void fn_2_8F948(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x40);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// fn_2_8F9D0, size:0x88
void fn_2_8F9D0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x3C);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// fn_2_8FA58, size:0x88
void fn_2_8FA58(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x38);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}

// fn_2_8FAE0, size:0x88
void fn_2_8FAE0(s32 index, s16 type) {
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x34);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = type;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
}


// .text:0x8F6D0 size:0x50
void fn_2_8F6D0(s32 index, s32 value) {
    u8* slot = (u8*)lbl_2_bss_1A8248[0] + index * 0xBC + 0x21E0;
    u8* anim = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x2D94);
    if (anim != NULL) {
        *(s16*)(slot + 0xA6) = 0;
        *(u32*)(anim + index * 0x28) = ((u32*)lbl_2_data_30900)[value];
    }
}

// .text:0x90888 size:0x74
void fn_2_90888(u8* object) {
    *(f32*)(object + 0x8C) = lbl_2_rodata_10AC[0];
    fn_2_8F6D0(*(s32*)(object + 0x78), 5);
    *(s16*)(object + 0xA0) = 0;
    *(s16*)(object + 0x90) = 1;
}

// .text:0x90698 size:0x80
void fn_2_90698(u8* object) {
    s16 timer = *(s16*)(object + 0x9C);
    *(s16*)(object + 0x9C) = timer - 1;
    if (timer == 0) {
        *(f32*)(object + 0x8C) = lbl_2_rodata_10A8[0];
        fn_2_8F6D0(*(s32*)(object + 0x78), 5);
        *(s16*)(object + 0x90) = 2;
    }
}

// .text:0x90C4C size:0x84
void fn_2_90C4C(u8* object) {
    s16 timer = *(s16*)(object + 0x9C);
    *(s16*)(object + 0x9C) = timer - 1;
    if (timer == 0) {
        *(f32*)(object + 0x8C) = lbl_2_rodata_10B4[0];
        *(s16*)(object + 0xA0) = 0;
        fn_2_8F6D0(*(s32*)(object + 0x78), 3);
        *(s16*)(object + 0x90) = 2;
    }
}

// .text:0x8FD14 size:0x9C
void fn_2_8FD14(void) {
    u8* anim;
    u8* dst;
    u8* src;
    s32 i;
    for (i = 0; i < *(u16*)((u8*)lbl_2_bss_340140[0] + 0x3078); i++) {
        anim = *(u8**)((u8*)lbl_2_bss_340140[0] + 0x2D94);
        if (anim != NULL) {
            dst = anim + i * 0x28;
            src = (u8*)lbl_2_bss_1A8248[0] + i * 0xBC + 0x21E0;
            memcpy(dst + 4, src, 0xC);
            *(f32*)(dst + 0x14) = *(f32*)(src + 0x28);
            dst[0x26] = src[0xAA];
        }
    }
}

// .text:0x90538 size:0xE4
void fn_2_90538(void) {
    u8* slot;
    s32 i;
    for (i = 0; i < 29; i++) {
        slot = (u8*)lbl_2_bss_1A8248[0] + i * 0xBC + 0x21E0;
        memset(slot, 0, 0xBC);
        *(s32*)(slot + 0x78) = i;
        *(s32*)(slot + 0x7C) = i;
        *(f32*)(slot + 0x84) = lbl_2_rodata_1080;
        *(f32*)(slot + 0x38) = lbl_2_rodata_1080;
        *(f32*)(slot + 0x3C) = lbl_2_rodata_1080;
        slot[0xAA] = 0;
        *(s16*)(slot + 0x92) = i;
        *(s16*)(slot + 0x94) = -1;
        slot[0xA8] = 0;
        slot[0xAB] = 0;
        *(s16*)(slot + 0x90) = 0;
        *(s8*)(slot + 0xAE) = -1;
        slot[0xAC] = 0;
        slot[0xAD] = 0;
        *(f32*)(slot + 0x80) = lbl_2_rodata_1080;
        *(s16*)(slot + 0xA6) = 0;
        slot[0xB2] = 0xFF;
        slot[0xB4] = 0;
    }
}

// .text:0x90718 size:0xDC
void fn_2_90718(u8* object) {
    s32 index;
    fn_2_8AC84(*(s32*)(object + 0x78), 1);
    index = *(s32*)(object + 0x78);
    if (lbl_2_bss_3401BC != NULL) {
        s32 resource;
        MenuEffect* effect;
        u8 valid;
        resource = *(s32*)((u8*)lbl_2_bss_3401BC + 0x3C);
        effect = (MenuEffect*)(*(u8**)((u8*)lbl_2_bss_340140[0] + 0x68) + index * 0x90 + 0x34);
        effect->resource = resource;
        effect->type = 2;
        effect->f5C = lbl_2_rodata_1080;
        effect->enabled = 1;
        valid = resource != 0;
        effect->flag59 = valid;
        effect->flag5A = valid;
        effect->f60 = lbl_2_rodata_1080;
        effect->f54 = lbl_2_rodata_1078;
        effect->flag5A = 1;
        effect->f5C = lbl_2_rodata_1080;
        effect->flag59 = 1;
        effect->mode = 3;
    }
    *(s16*)(object + 0x9C) = 0x50;
    *(s16*)(object + 0xA0) = 0;
    *(s16*)(object + 0x90) = 1;
}

// .text:0x90DE4 size:0xB4
void fn_2_90DE4(u8* object, f32 limit) {
    if (object[0xB5] != 0) {
        f32 s = (f32)sin(*(f32*)(object + 0x88));
        f32 v = lbl_2_rodata_10B8[0] * -s;
        *(f32*)(object + 0x88) = *(f32*)(object + 0x88) + lbl_2_rodata_10BC;
        if (v >= limit) {
            *(f32*)(object + 0x88) = lbl_2_rodata_1080;
            v = lbl_2_rodata_1080;
            object[0xB5] = 0;
        }
        *(f32*)(object + 4) = v;
    } else {
        *(f32*)(object + 4) = lbl_2_rodata_1080;
    }
}

// .text:0x8F528 size:0x118
void fn_2_8F528(s32 index) {
    u8* slot = (u8*)lbl_2_bss_1A8248[0] + index * 0xBC + 0x21E0;
    GXColor color = *(GXColor*)(lbl_800F7478 + 0x28);
    s32 alpha;
    switch (*(s16*)(slot + 0xA6)) {
    case 0:
        *(f32*)(slot + 0x84) = lbl_2_rodata_1080;
        *(s16*)(slot + 0xA6) = 1;
    case 1:
        *(f32*)(slot + 0x84) = (f32)(*(f32*)(slot + 0x84) + lbl_2_rodata_1088);
        alpha = (s32)(lbl_2_rodata_1084 * *(f32*)(slot + 0x84));
        if (alpha < 0xFF) {
            color.a = 1;
            color.a = alpha;
            fn_800BD2CC(1, color);
        } else {
            color.a = 0xFF;
            fn_800BD2CC(0, color);
            *(s16*)(slot + 0xA6) = 2;
        }
        break;
    case 2:
        *(f32*)(slot + 0x84) = lbl_2_rodata_1080;
        break;
    }
}
