#include "game/rep_2998.h"
#include "header_rep_data.h"

#pragma dont_inline on

extern f32 lbl_3_rodata_2A5C;
extern u8 lbl_3_data_18ED0[];

extern u32 lbl_3_bss_AE18;
extern void fn_3_B97DC(void*, u32);
extern u8* lbl_3_common_bss_350E4;
extern void fn_800B4AFC(void*, s32);

#include "C3/control.h"
extern Vec lbl_3_rodata_2A48;
extern f32 lbl_3_rodata_2A60;
extern f32 lbl_3_rodata_2A64;
extern u8 g_Ball[];
extern double acos(double);
extern f32 lbl_3_rodata_2B28;

extern f32 lbl_3_rodata_2A54;
extern f32 lbl_3_rodata_2A58;
extern void fn_800B4CA0(void*, f32);
extern void AnimateActorBones(void*);

// .text:0x000E1FA8 size:0x8C mapped:0x8072103C
void fn_3_E1FA8(u8* a) {
    u8* d = *(u8**)(a + 0x74);
    void* o = *(void**)d;
    if (*(f32*)(d + 0x5C) + *(f32*)(d + 0x54) > lbl_3_rodata_2A54) {
        *(f32*)(d + 0x5C) = lbl_3_rodata_2A58;
        d[0x59] = 1;
        fn_800B4CA0(o, *(f32*)(d + 0x5C));
    }
    AnimateActorBones(o);
    *(f32*)(d + 0x5C) = *(f32*)(d + 0x5C) + *(f32*)(d + 0x54);
}

// .text:0x000E2034 size:0xE4 mapped:0x807210C8
void fn_3_E2034(u8* a) {
    Vec v2;
    Vec v1;
    f32 r;
    v1 = lbl_3_rodata_2A48;
    PSVECSubtract((Vec*)g_Ball, (Vec*)(a + 0xA0), &v2);
    v2.y = lbl_3_rodata_2A5C;
    PSVECNormalize(&v2, &v2);
    PSVECNormalize(&v1, &v1);
    r = lbl_3_rodata_2A60 * (f32)acos(PSVECDotProduct(&v2, &v1));
    if (v2.x < lbl_3_rodata_2A5C) {
        r = lbl_3_rodata_2A64 - r;
    }
    {
        *(f32*)(a + 0xB0) = -r;
        CTRLSetRotation((Control*)a, 0.0f, *(f32*)(a + 0xB0), 0.0f);
    }
}
// .text:0x000E2118 size:0x18C mapped:0x807211AC
void fn_3_E2118(void) {
    return;
}

// .text:0x000E22A4 size:0x80 mapped:0x80721338
void fn_3_E22A4(u8* a) {
    u8* p = *(u8**)(a + 0x74);
    u8 st;
    u8 v;
    u32* r;
    p = *(u8**)p;
    p = *(u8**)(p + 0x10);
    p = *(u8**)(p + 0x10);
    p = *(u8**)p;
    p = *(u8**)(p + 0x10);
    r = *(u32**)(p + 4);
    r[1] &= ~0x1FFF;
    st = a[0xC4];
    if (st != 0) {
        v = a[0xC8] + 1;
        if (st == 1 || st == 5) {
            if (a[0xC5] % 2 == 0) {
                v = 0;
            }
        }
        r[1] |= v;
    }
}

// .text:0x000E2324 size:0x2AC mapped:0x807213B8
void fn_3_E2324(void) {
    return;
}

// .text:0x000E25D0 size:0x9C mapped:0x80721664
void fn_3_E25D0(u8* a, u32 b) {
    *(u32*)(a + 0xAC) = ((u32*)&lbl_3_bss_AE18)[b];
    fn_3_B97DC(*(void**)(a + 0x74), *(u32*)(a + 0xAC));
    if (b != 0 && b != 2 && b != 3) {
        (*(u8**)(a + 0x74))[0x5B] = 2;
        fn_800B4AFC(**(void***)(a + 0x74), (*(u8**)(a + 0x74))[0x5B] & 1);
    }
    *(f32*)(a + 0xB8) = *(f32*)(*(u8**)(a + 0x74) + 0x5C);
    a[0xCB] = b;
}
// .text:0x000E266C size:0x270 mapped:0x80721700
void fn_3_E266C(void) {
    return;
}

// .text:0x000E28DC size:0xD8 mapped:0x80721970
void fn_3_E28DC(void) {
    return;
}

// .text:0x000E29B4 size:0x1BC mapped:0x80721A48
void fn_3_E29B4(void) {
    return;
}

// .text:0x000E2B70 size:0x308 mapped:0x80721C04
u8 fn_3_E2B70(u8* a) {
    return;
}

// .text:0x000E2E78 size:0xD4 mapped:0x80721F0C
void fn_3_E2E78(void) {
    return;
}

// .text:0x000E2F4C size:0xF8 mapped:0x80721FE0
void fn_3_E2F4C(void) {
    return;
}

// .text:0x000E3044 size:0x240 mapped:0x807220D8
void fn_3_E3044(void) {
    return;
}

// .text:0x000E3284 size:0x3E4 mapped:0x80722318
void fn_3_E3284(u8* a) {
    return;
}

// .text:0x000E3668 size:0xFC mapped:0x807226FC
void fn_3_E3668(u8* a) {
    Vec v1;
    Vec v2;
    f32 r;
    if (fn_3_E2B70(a)) {
        fn_3_E3284(a);
        return;
    }
    v1 = lbl_3_rodata_2A48;
    PSVECSubtract((Vec*)g_Ball, (Vec*)(a + 0xA0), &v2);
    v2.y = lbl_3_rodata_2A5C;
    PSVECNormalize(&v2, &v2);
    PSVECNormalize(&v1, &v1);
    r = lbl_3_rodata_2A60 * (f32)acos(PSVECDotProduct(&v2, &v1));
    if (v2.x < lbl_3_rodata_2A5C) {
        r = lbl_3_rodata_2A64 - r;
    }
    *(f32*)(a + 0xB0) = -r;
    CTRLSetRotation((Control*)a, 0.0f, *(f32*)(a + 0xB0), 0.0f);
}
// .text:0x000E3764 size:0x1B0 mapped:0x807227F8
void fn_3_E3764(void) {
    return;
}

// .text:0x000E3914 size:0x274 mapped:0x807229A8
void fn_3_E3914(void) {
    return;
}

// .text:0x000E3B88 size:0x9CC mapped:0x80722C1C
void fn_3_E3B88(void) {
    return;
}

// .text:0x000E4554 size:0x54 mapped:0x807235E8
void fn_3_E4554(u8* a) {
    *(u32*)(a + 0xAC) = lbl_3_bss_AE18;
    fn_3_B97DC(*(void**)(a + 0x74), *(u32*)(a + 0xAC));
    *(f32*)(a + 0xB8) = *(f32*)(*(u8**)(a + 0x74) + 0x5C);
    a[0xCB] = 0;
}

// .text:0x000E45A8 size:0x48 mapped:0x8072363C
void fn_3_E45A8(u8* a) {
    CTRLSetScale((Control*)a, 0.2f, 0.2f, 0.2f);
    *(f32*)(a + 0xB4) = 0.2f;
}

// .text:0x000E45F0 size:0x68 mapped:0x80723684
void fn_3_E45F0(u8* a) {
    f32* t = (f32*)(lbl_3_data_18ED0 + 0xC);
    CTRLSetRotation((Control*)a, 0.0f, t[a[0x9C] * 7], 0.0f);
    *(f32*)(a + 0xB0) = t[a[0x9C] * 7];
}

// .text:0x000E4658 size:0x108 mapped:0x807236EC
void fn_3_E4658(void) {
    return;
}

// .text:0x000E4760 size:0x170 mapped:0x807237F4
void fn_3_E4760(void) {
    return;
}

// .text:0x000E48D0 size:0x168 mapped:0x80723964
void fn_3_E48D0(void) {
    return;
}

// .text:0x000E4A38 size:0x1B0 mapped:0x80723ACC
void fn_3_E4A38(void) {
    return;
}

// .text:0x000E4BE8 size:0xC8 mapped:0x80723C7C
typedef struct { u8 pad[0x78]; u32 f78; u8 pad2[0xE8 - 0x7C]; } E4BE8Ctl;
static inline u32 e4be8_get78(s32 idx) {
    return ((E4BE8Ctl*)lbl_3_common_bss_350E4)[idx].f78;
}
u32 fn_3_E4BE8(s32 idx, f32 (*m)[4]) {
    Mtx tmp;
    u8* c;
    c = (u8*)&((E4BE8Ctl*)lbl_3_common_bss_350E4)[idx];
    CTRLBuildMatrix((Control*)c, m);
    if (c[0x9D] == 0) {
        if (c[0xC8] == 0 || c[0xC4] == 0 || c[0xC4] == 5 || c[0xC4] == 4) {
            return 0;
        }
        PSMTXCopy(*(void**)(*(u8**)(*(u8**)(*(u8**)(*(u8**)(c + 0x74)) + 0x18) + 0x40) + 0xEC), tmp);
        PSMTXConcat(m, tmp, m);
    }
    return e4be8_get78(idx);
}// .text:0x000E4EF4 size:0xD0 mapped:0x80723F88
void fn_3_E4EF4(void) {
    return;
}

// .text:0x000E4FC4 size:0x8B8 mapped:0x80724058
void fn_3_E4FC4(void) {
    return;
}

