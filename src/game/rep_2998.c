#include "game/rep_2998.h"
#include "header_rep_data.h"

#pragma dont_inline on

extern f32 lbl_3_rodata_2A5C;

extern u32 lbl_3_bss_AE18;
extern void fn_3_B97DC(void*, u32);
extern void fn_3_65F4(void);
typedef struct { u8 pad[0x74]; u8*** p74; u32 f78; u8 pad3[0x9D-0x7C]; u8 f9D; u8 pad4[0xC4-0x9E]; u8 fC4; u8 pad5[3]; u8 fC8; u8 pad2[0xE8 - 0xC9]; } E4BE8Ctl;
typedef struct {
    E4BE8Ctl* arr;
    u8 pad0[0x30 - 4];
    s32 count;
    u8 pad1[0x3C - 0x34];
    u8* p3C;
    u8* p40;
    u8* p44;
    u8* p48;
    u8 pad2[0x64 - 0x4C];
    s16 s64;
} E4EF4Ctl;
extern E4EF4Ctl lbl_3_common_bss_350E4;
extern void fn_800B4AFC(void*, s32);

#include "C3/control.h"
typedef struct { Vec pos; f32 rot; u8 f10; u8 f11; u8 f12; u8 pad[9]; } Ent18ED0;
extern Ent18ED0 lbl_3_data_18ED0[];
extern Vec lbl_3_rodata_2A48;
extern const f32 lbl_3_rodata_2B20;
extern f32 lbl_3_rodata_2B24;
extern f32 lbl_3_rodata_2A60;
extern f32 lbl_3_rodata_2A64;
extern u8 g_Ball[];
extern double acos(double);
extern void* _OSAllocFromHeap(s32, u32);
extern void* memset(void*, int, u32);
extern void fn_3_E4CB0(s32*, s32*);
extern double sin(double);
extern double cos(double);
extern f32 lbl_3_rodata_2AC0;
extern f64 lbl_3_rodata_2AB8;
extern f64 lbl_3_rodata_2A98;
extern f64 lbl_3_rodata_2AC8;
extern f64 lbl_3_rodata_2AD0;
extern u8 lbl_800E8754[];
extern void fn_3_CB7E8(f32, f32, f32);
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
u32 fn_3_E28DC(u8* a) {
    Vec v1;
    Vec v2;
    v1 = *(Vec*)(a + 0xA0);
    PSVECSubtract((Vec*)g_Ball, &v1, &v2);
    v2.y = 0.0f;
    if (2.5 >= PSVECMag(&v2)) {
        *(u32*)(a + 0xAC) = ((u32*)&lbl_3_bss_AE18)[6];
        fn_3_B97DC(*(void**)(a + 0x74), *(u32*)(a + 0xAC));
        (*(u8**)(a + 0x74))[0x5B] = 2;
        fn_800B4AFC(**(void***)(a + 0x74), (*(u8**)(a + 0x74))[0x5B] & 1);
        *(f32*)(a + 0xB8) = *(f32*)(*(u8**)(a + 0x74) + 0x5C);
        a[0xCB] = 6;
        return 1;
    }
    return 0;
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
void fn_3_E2E78(u8* a) {
    if (a[0xC5] == 0) {
        a[0xC8] = 0;
        a[0xC4] = 0;
    } else {
        *(f32*)(a + 0xB4) = *(f32*)(a + 0xB4) - 1.0857142857142859 / a[0xC6];
        *(f32*)(a + 0xA4) = -(1.2 * *(f32*)(a + 0xB4));
        CTRLSetTranslation((Control*)a, *(f32*)(a + 0xA0), -*(f32*)(a + 0xA4), *(f32*)(a + 0xA8));
        CTRLSetScale((Control*)a, *(f32*)(a + 0xB4), *(f32*)(a + 0xB4), *(f32*)(a + 0xB4));
        a[0xC5] -= 1;
    }
}
// .text:0x000E2F4C size:0xF8 mapped:0x80721FE0
void fn_3_E2F4C(u8* a) {
    f32 ang;
    f32 x;
    f32 c;
    f32 s;
    f32 sc;
    f32 b8 = *(f32*)(a + 0xB8);
    f32 d54 = *(f32*)(*(u8**)(a + 0x74) + 0x54);
    if (b8 >= lbl_3_rodata_2AB8) {
        if (b8 - d54 < lbl_3_rodata_2AB8) {
            if (lbl_800E8754[4] != 0) {
                ang = -*(f32*)(a + 0xB0);
                ang = lbl_3_rodata_2AC0 * ang;
                s = sin(ang);
                x = *(f32*)(a + 0xB4) * (lbl_3_rodata_2A98 * s) + *(f32*)(a + 0xA0);
                c = cos(ang);
                sc = *(f32*)(a + 0xB4);
                fn_3_CB7E8(x, lbl_3_rodata_2AC8 * sc, sc * (lbl_3_rodata_2AD0 * c) + *(f32*)(a + 0xA8));
            }
        }
    }
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

// A callee is inlined only if dont_inline is off both where it is defined and
// at the end of the file (-inline deferred). fn_3_E4658/fn_3_E4760 inline the
// functions below, so inlining stays on from here to the end; stubs that are
// called later must be asm (see fn_3_E4CB0) or they get inlined.
#pragma dont_inline off
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
    CTRLSetRotation((Control*)a, 0.0f, lbl_3_data_18ED0[a[0x9C]].rot, 0.0f);
    *(f32*)(a + 0xB0) = lbl_3_data_18ED0[a[0x9C]].rot;
}

// .text:0x000E4658 size:0x108 mapped:0x807236EC
void fn_3_E4658(u8* a) {
    a[0] = 0;
    CTRLSetTranslation((Control*)a, lbl_3_data_18ED0[a[0x9C]].pos.x, lbl_3_rodata_2B20 + lbl_3_data_18ED0[a[0x9C]].pos.y, lbl_3_data_18ED0[a[0x9C]].pos.z);
    PSVECScale(&lbl_3_data_18ED0[a[0x9C]].pos, lbl_3_rodata_2B24, (Vec*)(a + 0xA0));
    *(f32*)(a + 0xA4) = *(f32*)(a + 0xA4) - lbl_3_rodata_2B20;
    fn_3_E45F0(a);
    fn_3_E45A8(a);
}

// .text:0x000E4760 size:0x170 mapped:0x807237F4
void fn_3_E4760(u8* a) {
    fn_3_E4658(a);
    fn_3_E4554(a);
    a[0xC5] = 0;
    a[0xC4] = 0;
    a[0xC7] = 0;
    a[0xC8] = 0;
    if (a[0xCA] != 0) {
        fn_3_65F4();
        a[0xCA] = 0;
        *(f32*)(a + 0xC0) = 0.0f;
    }
    a[0xC9] = 0;
}

// .text:0x000E48D0 size:0x168
void fn_3_E48D0(u8* a) {
    fn_3_E4658(a);
    fn_3_E4554(a);
    a[0xC5] = 0;
    a[0xC4] = 0;
    a[0xC7] = 0;
    a[0xC8] = 0;
    if (a[0xCA] != 0) {
        fn_3_65F4();
        a[0xCA] = 0;
        *(f32*)(a + 0xC0) = 0.0f;
    }
}

// .text:0x000E4A38 size:0x1B0 mapped:0x80723ACC
extern u8 lbl_3_bss_AE01;
extern f32 lbl_3_rodata_2B2C;
extern f32 lbl_3_rodata_2B30;
void fn_3_E4A38(f32 (*m)[4], u8* b) {
    Vec sp14;
    Vec sp8;
    int n;
    u8* p;
    int t;
    u32 cnt;
    f32 minx, miny, minz, maxx, maxy, maxz;
    minz = miny = minx = lbl_3_rodata_2B2C;
    maxz = maxy = maxx = lbl_3_rodata_2B30;
    p = *(u8**)(b + 8);
    for (;;) {
        cnt = *(u16*)(p + 2);
        if (cnt == 0) break;
        t = cnt * 3;
        if (p[1] != 0) {
            t = cnt + 2;
        }
        n = t;
        p += 4;
        do {
            if (lbl_3_bss_AE01 == 0) {
                PSMTXMultVec(m, (Vec*)p, &sp14);
            } else {
                PSVECScale((Vec*)p, 1.0f, &sp14);
            }
            p += 0x10;
            if (minx > sp14.x) minx = sp14.x;
            if (miny > sp14.y) miny = sp14.y;
            if (minz > sp14.z) minz = sp14.z;
            if (maxx < sp14.x) maxx = sp14.x;
            if (maxy < sp14.y) maxy = sp14.y;
            if (maxz < sp14.z) maxz = sp14.z;
            n--;
        } while (n != 0);
    }
    PSVECScale((Vec*)g_Ball, 1.0f, &sp8);
}

// .text:0x000E4BE8 size:0xC8 mapped:0x80723C7C
static inline E4BE8Ctl* e4be8_ctl(s32 idx) {
    return &lbl_3_common_bss_350E4.arr[idx];
}
u32 fn_3_E4BE8(s32 idx, f32 (*m)[4]) {
    Mtx tmp;
    E4BE8Ctl* c = e4be8_ctl(idx);
    CTRLBuildMatrix((Control*)c, m);
    if (c->f9D == 0) {
        if (c->fC8 == 0 || c->fC4 == 0 || c->fC4 == 5 || c->fC4 == 4) {
            return 0;
        }
        PSMTXCopy(*(void**)(*(u8**)(*(u8**)((u8*)(*c->p74) + 0x18) + 0x40) + 0xEC), tmp);
        PSMTXConcat(m, tmp, m);
    }
    return lbl_3_common_bss_350E4.arr[idx].f78;
}

// .text:0x000E4CB0 size:0x244 mapped:0x80723D44
typedef struct { u32 w[17]; } E4CB0Cpy;
extern void fn_3_B8574(void);
extern void fn_3_B8414(void*, void*);
extern void fn_3_B8464(void*, void*);
void fn_3_E4CB0(s32* a, s32* b) {
    E4CB0Cpy sp44;
    Mtx sp14;
    Vec t;
    Ent18ED0* p;
    u32 off;
    E4BE8Ctl* c;
    int i;
    int j;
    u16* q;
    for (i = 0; i < 10; i++) {
        u32 v;
        q = (u16*)(lbl_3_common_bss_350E4.p40 + *a * 2);
        v = (u16)(q[-1] + *(u32*)(lbl_3_common_bss_350E4.p3C + *a * 4 - 4));
        q[0] = v;
        fn_3_B8574();
        p = lbl_3_data_18ED0;
        off = v;
        for (j = 0; j < 10; j++) {
            p = &lbl_3_data_18ED0[j];
            if (i == p->f12 && p->f10 != 2) {
                if ((*((u8*)lbl_3_common_bss_350E4.arr + *b * 0xE8 + 0x90) >> 6) & 1) {
                    ((s32*)lbl_3_common_bss_350E4.p44)[off] = *b;
                    *(u32*)(lbl_3_common_bss_350E4.p3C + *a * 4) += 1;
                    c = (E4BE8Ctl*)((u8*)lbl_3_common_bss_350E4.arr + *b * 0xE8);
                    off += 1;
                    sp44 = *(E4CB0Cpy*)c;
                    CTRLGetTranslation((Control*)&sp44, &t.x, &t.y, &t.z);
                    CTRLSetTranslation((Control*)&sp44, t.x - 4.0, t.y, t.z - 4.0);
                    CTRLBuildMatrix((Control*)&sp44, sp14);
                    fn_3_B8464(sp14, (void*)c->f78);
                    CTRLSetTranslation((Control*)&sp44, 4.0 + t.x, t.y - 10.0, 4.0 + t.z);
                    CTRLBuildMatrix((Control*)&sp44, sp14);
                    fn_3_B8464(sp14, (void*)c->f78);
                    *b += 1;
                }
            }
        }
        if (*(u32*)(lbl_3_common_bss_350E4.p3C + *a * 4) != 0) {
            fn_3_B8414(lbl_3_common_bss_350E4.p48 + *a * 0x18, lbl_3_common_bss_350E4.p48 + (*a * 2 + 1) * 0xC);
            *a += 1;
        }
    }
}

// .text:0x000E4EF4 size:0xD0 mapped:0x80723F88
void fn_3_E4EF4(void) {
    s32 spC;
    s32 sp8;
    E4EF4Ctl* c = &lbl_3_common_bss_350E4;
    s32 size = (c->count << 1) + (c->count << 2) + (c->count << 2) + c->count * 0x18;
    if (c->p48 == NULL) {
        u8* p = _OSAllocFromHeap(4, size);
        c->p48 = p;
        lbl_3_common_bss_350E4.p3C = p + c->count * 0x18;
        lbl_3_common_bss_350E4.p44 = lbl_3_common_bss_350E4.p3C + c->count * 4;
        lbl_3_common_bss_350E4.p40 = lbl_3_common_bss_350E4.p44 + c->count * 4;
    }
    memset(c->p48, 0, size);
    spC = 0;
    sp8 = 0;
    fn_3_E4CB0(&spC, &sp8);
    lbl_3_common_bss_350E4.s64 = spC;
}// .text:0x000E4FC4 size:0x8B8 mapped:0x80724058
void fn_3_E4FC4(void) {
    return;
}

