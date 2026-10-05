#include "game/sta_c6.h"
#include "header_rep_data.h"

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/rand.h"
extern u32 lbl_3_data_19018[];

extern f32 lbl_3_rodata_2B9C;
extern f32 lbl_3_rodata_2BA0;

extern f32 lbl_3_rodata_2B90;
extern f32 lbl_3_rodata_2B94;
extern f32 lbl_3_rodata_2B98;
extern f32 fn_800B4C40(void*);
extern void fn_800B4CA0(void*, f32);
extern void AnimateActorBones(void*);
#include "static/UnknownHomes_Static.h"

extern u8 lbl_3_common_bss_350E4[];
#pragma dont_inline on

extern u8 lbl_3_data_196B4[];

extern u8 lbl_3_common_bss_350E4[];

extern u8 lbl_3_data_1963F;
extern u8 lbl_3_data_19640;

// .text:0x000E59B4 size:0x68 mapped:0x80724A48
void fn_3_E59B4(u8* a) {
    void* o = **(void***)(a + 0x74);
    if (lbl_3_rodata_2B90 + fn_800B4C40(o) > lbl_3_rodata_2B94) {
        fn_800B4CA0(o, lbl_3_rodata_2B98);
    }
    AnimateActorBones(o);
}

// .text:0x000E5A1C size:0x68 mapped:0x80724AB0
void fn_3_E5A1C(u8* a) {
    void* o = **(void***)(a + 0x74);
    if (lbl_3_rodata_2B90 + fn_800B4C40(o) > lbl_3_rodata_2B9C) {
        fn_800B4CA0(o, lbl_3_rodata_2BA0);
    }
    AnimateActorBones(o);
}

// .text:0x000E5A84 size:0x238 mapped:0x80724B18
void fn_3_E5A84(void) {
    return;
}

// .text:0x000E5CBC size:0x158 mapped:0x80724D50
void fn_3_E5CBC(void) {
    return;
}

// .text:0x000E5E14 size:0x5C mapped:0x80724EA8
void fn_3_E5E14(void) {
    return;
}

// .text:0x000E5E70 size:0x17C mapped:0x80724F04
void fn_3_E5E70(void) {
    return;
}

// .text:0x000E5FEC size:0x424 mapped:0x80725080
void fn_3_E5FEC(void) {
    return;
}

// .text:0x000E6410 size:0x98 mapped:0x807254A4
void fn_3_E6410(void) {
    return;
}

// .text:0x000E64A8 size:0x80 mapped:0x8072553C
u32* fn_3_E64A8(void) {
    u8 v = rand() % 3;
    switch (v) {
    case 0:
        return lbl_3_data_19018;
    case 1:
        return lbl_3_data_19018 + 1;
    default:
        return lbl_3_data_19018 + 2;
    }
}

// .text:0x000E6528 size:0x50 mapped:0x807255BC
void fn_3_E6528(void) {
    return;
}

// .text:0x000E6578 size:0xC0 mapped:0x8072560C
void fn_3_E6578(void) {
    return;
}

// .text:0x000E6638 size:0x4C mapped:0x807256CC
void fn_3_E6638(u8* a) {
    u8** c = *(u8***)(*(u8**)(*(u8**)(a + 0x74)) + 0x18);
    u8* d;
    d = c[0];
    *(u32*)(d + 0x14) = *(u32*)(d + 0x18);
    c = *(u8***)(*(u8**)(*(u8**)(a + 0x74)) + 0x18);
    d = c[1];
    *(u32*)(d + 0x14) = *(u32*)(d + 0x18);
    c = *(u8***)(*(u8**)(*(u8**)(a + 0x74)) + 0x18);
    d = c[2];
    *(u32*)(d + 0x14) = *(u32*)(d + 0x18);
}

// .text:0x000E6684 size:0x98 mapped:0x80725718
void fn_3_E6684(void) {
    return;
}

// .text:0x000E671C size:0x7C mapped:0x807257B0
void fn_3_E671C(u8* a) {
    u8* o = **(u8***)(a + 0x74);
    u8* t;
    t = ((u8**)*(u8**)(o + 0x18))[0];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
    t = ((u8**)*(u8**)(o + 0x18))[1];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
    t = ((u8**)*(u8**)(o + 0x18))[2];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
    t = ((u8**)*(u8**)(o + 0x18))[3];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
    t = ((u8**)*(u8**)(o + 0x18))[4];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
    t = ((u8**)*(u8**)(o + 0x18))[5];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
    t = ((u8**)*(u8**)(o + 0x18))[6];
    *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
}

// .text:0x000E6798 size:0x5C mapped:0x8072582C
void fn_3_E6798(u8* a) {
    u8* o = **(u8***)(a + 0x74);
    s32 i;
    for (i = 0; i < 7; i++) {
        if (lbl_3_data_196B4[i] != 0) {
            u8* t = ((u8**)*(u8**)(o + 0x18))[i];
            *(u32*)(t + 0x14) = *(u32*)(t + 0x18);
        } else {
            u8* t = ((u8**)*(u8**)(o + 0x18))[i];
            *(u32*)(t + 0x14) = 0;
        }
    }
}

// .text:0x000E67F4 size:0xB4 mapped:0x80725888
void fn_3_E67F4(void) {
    return;
}

// .text:0x000E68A8 size:0xE4 mapped:0x8072593C
void fn_3_E68A8(void) {
    return;
}

// .text:0x000E698C size:0xBC mapped:0x80725A20
void fn_3_E698C(void) {
    return;
}

// .text:0x000E6A48 size:0x348 mapped:0x80725ADC
void fn_3_E6A48(void) {
    return;
}

// .text:0x000E6D90 size:0x5C0 mapped:0x80725E24
void fn_3_E6D90(void) {
    return;
}

// .text:0x000E7350 size:0x14 mapped:0x807263E4
void fn_3_E7350(void) {
    lbl_3_data_1963F = lbl_3_data_19640;
}

// .text:0x000E7364 size:0x24 mapped:0x807263F8
void fn_3_E7364(void) {
    return;
}

// .text:0x000E7388 size:0x9C mapped:0x8072641C
void fn_3_E7388(void) {
    return;
}

// .text:0x000E7424 size:0xF8 mapped:0x807264B8
void fn_3_E7424(void) {
    return;
}

// .text:0x000E751C size:0x120 mapped:0x807265B0
void fn_3_E751C(void) {
    return;
}

// .text:0x000E763C size:0x3F0 mapped:0x807266D0
void fn_3_E763C(void) {
    return;
}

// .text:0x000E7A2C size:0xF4 mapped:0x80726AC0
void fn_3_E7A2C(void) {
    return;
}

// .text:0x000E7B20 size:0xFA8 mapped:0x80726BB4
u8 fn_3_E7B20(void* a, void* b) {
    return 0;
}

// .text:0x000E8AC8 size:0x5C mapped:0x80727B5C
s32 fn_3_E8AC8(void) {
    if (g_d_GameSettings.StadiumID != 6) {
        return 0;
    }
    return fn_3_E7B20(*(void**)(lbl_3_common_bss_350E4 + 0x38), *(void**)(lbl_3_common_bss_350E4 + 0x34)) != 0;
}

// .text:0x000E8B24 size:0x5F8 mapped:0x80727BB8
void fn_3_E8B24(void) {
    return;
}

