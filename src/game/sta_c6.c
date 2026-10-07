#include "game/sta_c6.h"
#include "header_rep_data.h"
#include "Dolphin/stl.h"
#include "Dolphin/os.h"
extern u8 lbl_3_data_19024[];

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
extern u8 lbl_8036E548[];
extern char lbl_3_rodata_2BB0[];
extern char lbl_3_rodata_2BBC[];

extern u8 lbl_3_common_bss_350E4[];

extern u8 lbl_3_bss_AE80[];
extern s32 fn_8005268C(void);
extern u8* fn_80052734(s32);
extern u8 fn_800B3C04(s32, void*, void*);
extern void fn_800BDA24(void*);
extern void fn_800BDA94(void*, void*);
extern u8 lbl_3_data_1963F;
extern u8 lbl_3_data_19640;
extern u8 lbl_3_bss_AEAC;

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
s32 fn_3_E5E14(u8* p) {
    switch ((u8)((s32)(*(u8**)(p + 4))[6] >> 4)) {
    case 0:
    case 3:
        return 2;
    case 5:
        return 4;
    case 1:
    case 2:
    case 4:
        return 3;
    default:
        return 0;
    }
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
void fn_3_E6410(u8* p) {
    u32* list[3];
    u32** w = list;
    s32 i;
    for (i = 0; i < 3; i++) {
        if (*(u32**)(p + 0xAC) != &lbl_3_data_19018[i]) {
            *w++ = &lbl_3_data_19018[i];
        }
    }
    *(u32**)(p + 0xA8) = list[rand() % 2];
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
void fn_3_E6528(u8* p) {
    memcpy(p + 0xA4, *(void**)(p + 0xB4), 4);
    *(void**)(p + 0xBC) = lbl_3_data_19024 + 0x64;
    p[0xC2] = 0;
}

// .text:0x000E6578 size:0xC0 mapped:0x8072560C
void fn_3_E6578(u8* a) {
    u8** p;
    u8* q;
    u8* r;

    p = *(u8***)(a + 0x9C);
    if (p == NULL) {
        return;
    }
    q = *(u8**)(*(u8**)(*(u8**)(*p + 0x18) + 4) + 0x14);
    r = *(u8**)(q + 8);
    if ((*(u8**)(*(u8**)(q + 0x10) + 4))[0x20] != 3) {
        OSPanic(lbl_3_rodata_2BB0, 0x713, lbl_3_rodata_2BBC);
    }
    if (a[0xC1] == 2) {
        *(s16*)(*(u8**)(r + 0xC) + 0xA0) = 1;
    } else if (a[0xC1] == 10) {
        *(s16*)(*(u8**)(r + 0xC) + 0xA0) = 0;
    } else {
        *(s16*)(*(u8**)(r + 0xC) + 0xA0) = 4;
    }
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
void fn_3_E6684(u8* p) {
    u32* o;
    s32 i;
    for (i = 0; i < 3; i++) {
        o = (*(u32***)(**(u8***)(p + 0x74) + 0x18))[i];
        if (lbl_3_bss_AE80[i + 1] != 0) {
            o[0x14 / 4] = o[0x18 / 4];
        } else {
            o[0x14 / 4] = 0;
        }
    }
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
typedef struct { u8 pad[0x34]; u8 sub[0x5C]; } E67F4B;
void fn_3_E67F4(void) {
    u32 i;
    void* o;
    u8* e;
    u8* b;

    for (i = 0; i < 7; i++) {
        lbl_3_data_196B4[i] = 0;
        b = *(u8**)(lbl_8036E548 + 0x6C);
        o = *(void**)(b + i * 0x90 + 0x934);
        e = ((E67F4B*)b)[i + 0x10].sub;
        *(f32*)(e + 0x5C) = 20.0f;
        e[0x59] = 1;
        fn_800B4CA0(o, *(f32*)(*(u8**)(lbl_8036E548 + 0x6C) + i * 0x90 + 0x990));
        AnimateActorBones(o);
    }
}

// .text:0x000E68A8 size:0xE4 mapped:0x8072593C
typedef struct { u8 pad[0x74]; void** p74; u8 pad2[0x24]; void** p9C; } E68A8S;
void fn_3_E68A8(u8* a) {
    E68A8S* s = (E68A8S*)a;
    void* o = *s->p9C;
    f32 t = fn_800B4C40(*s->p74) - *(f32*)((u8*)s->p74 + 0x54);
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (s->p9C != NULL) {
        memcpy((u8*)s->p9C + 0x10, s, 0x44);
        fn_800B4CA0(o, t);
        fn_800BDA24(s->p9C);
        ((u8*)*s->p9C)[0x98] = fn_800B3C04(0, *s->p9C, fn_80052734(fn_8005268C()) + 0x40);
        fn_800BDA94(s->p9C, (u8*)fn_80052768_getCamera(fn_8005268C()) + 0x40);
    }
}

// .text:0x000E698C size:0xBC mapped:0x80725A20
void fn_3_E698C(u8* a) {
    void* o;
    f32 t;
    u8 idx;
    void* tmp;

    o = tmp = **(void***)(a + 0x74);
    t = fn_800B4C40(tmp);
    idx = a[0xC1] - 0x10;
    if (lbl_3_data_196B4[idx] == 0) {
        fn_800B4CA0(o, 0.0f);
        AnimateActorBones(o);
    }
    if (lbl_3_data_196B4[idx] != 0 && t <= 60.0f) {
        AnimateActorBones(o);
    }
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
typedef struct { u8 pad[0xC0]; u8 v; u8 pad2[0x27]; } E8;
void fn_3_E7364(s32 i) {
    lbl_3_data_19640 = ((E8*)*(u8**)lbl_3_common_bss_350E4)[i].v;
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
void fn_3_E7A2C(u8* o) {
    *(void**)(o + 0x7C) = 0;
    *(void**)(o + 0x80) = 0;
    *(void**)(o + 0x84) = 0;
    *(void**)(o + 0x88) = 0;
    switch (o[0xC1]) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        *(void**)(o + 0x80) = fn_3_E7364;
        *(void**)(o + 0x84) = fn_3_E6D90;
        lbl_3_bss_AEAC++;
        break;
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
        *(void**)(o + 0x7C) = fn_3_E698C;
        *(void**)(o + 0x84) = fn_3_E68A8;
        break;
    case 23:
        *(void**)(o + 0x84) = fn_3_E6798;
        *(void**)(o + 0x88) = fn_3_E671C;
        break;
    case 24:
        *(void**)(o + 0x84) = fn_3_E6684;
        *(void**)(o + 0x88) = fn_3_E6638;
        break;
    case 26:
        *(void**)(o + 0x7C) = fn_3_E59B4;
        break;
    case 25:
        *(void**)(o + 0x7C) = fn_3_E5A1C;
        break;
    }
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

