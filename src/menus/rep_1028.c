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
