#include "menus/rep_0F60.h"

#include "static/UnknownHomes_Static.h"


extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_340140;
extern u8* lbl_2_bss_1A824C;
extern void* _OSAllocFromHeap(s32 alignment, s32 size);
extern u8 lbl_800F5D98[];
extern u8 lbl_800F71D8[];
extern void fn_2_8ACDC(void);

// Model files, indexed by kind (fn_2_8D9DC, fn_2_8DB14..fn_2_8DCD8, auto_00_0008E6A4).
MenuAsset lbl_2_data_2F990[13] = {
    {0x0000040B, 0x4005A338, 0x19233000, 0x0003A448},
    {0x0000040B, 0x4004D644, 0x1926D800, 0x00030E60},
    {0x0000040B, 0x40061CB0, 0x1929E800, 0x0003E260},
    {0x0000040B, 0x4004A820, 0x1930B800, 0x000316E0},
    {0x0000040B, 0x40046B64, 0x192DD000, 0x0002E4EC},
    {0x0000040B, 0x40047D78, 0x1933D000, 0x0002F2DC},
    {0x0000040B, 0x40042A7C, 0x1936C800, 0x0002AD8C},
    {0x0000040B, 0x40047B30, 0x19397800, 0x0002D5A8},
    {0x0000040B, 0x4003F9D0, 0x193C5000, 0x00025C68},
    {0x0000040B, 0x400413A4, 0x193EB000, 0x000292B0},
    {0x0000040B, 0x40044F28, 0x19432000, 0x0002D5EC},
    {0x0000040B, 0x40030574, 0x19414800, 0x0001D740},
    {0x0000040B, 0x40036CD8, 0x1945F800, 0x00023828},
};
// Animation files, indexed through lbl_2_data_2FDC0.
MenuAsset lbl_2_data_2FA60[54] = {
    {0x0000040B, 0x4005A338, 0x19233000, 0x0003A448},
    {0x0000040B, 0x40062C34, 0x19483800, 0x000405F4},
    {0x0000040B, 0x4004A820, 0x1930B800, 0x000316E0},
    {0x0000040B, 0x4005C0CC, 0x194C4000, 0x0003C38C},
    {0x0000040B, 0x4004D644, 0x1926D800, 0x00030E60},
    {0x0000040B, 0x4004E624, 0x19500800, 0x000333F4},
    {0x0000040B, 0x40046B64, 0x192DD000, 0x0002E4EC},
    {0x0000040B, 0x40047BF8, 0x19534000, 0x0002D124},
    {0x0000040B, 0x400474C4, 0x19561800, 0x0002D2C4},
    {0x0000040B, 0x40047D78, 0x1933D000, 0x0002F2DC},
    {0x0000040B, 0x40061CB0, 0x1929E800, 0x0003E260},
    {0x0000040B, 0x4005C08C, 0x1958F000, 0x0003F088},
    {0x0000040B, 0x40044F28, 0x19432000, 0x0002D5EC},
    {0x0000040B, 0x4003F9D0, 0x193C5000, 0x00025C68},
    {0x0000040B, 0x4002F3E8, 0x195CE800, 0x0001E374},
    {0x0000040B, 0x40049F94, 0x195ED000, 0x0002D67C},
    {0x0000040B, 0x40030574, 0x19414800, 0x0001D740},
    {0x0000040B, 0x4004EB58, 0x1961A800, 0x00031A64},
    {0x0000040B, 0x4002D3B8, 0x1964C800, 0x0001C224},
    {0x0000040B, 0x40042A7C, 0x1936C800, 0x0002AD8C},
    {0x0000040B, 0x400425E0, 0x19669000, 0x0002BC8C},
    {0x0000040B, 0x40047B30, 0x19397800, 0x0002D5A8},
    {0x0000040B, 0x400425E0, 0x19669000, 0x0002BC8C},
    {0x0000040B, 0x40040EF0, 0x19695000, 0x00028E20},
    {0x0000040B, 0x40035DC0, 0x196BE000, 0x00021B80},
    {0x0000040B, 0x40027FF8, 0x196E0000, 0x00018538},
    {0x0000040B, 0x40027FF8, 0x196F8800, 0x00018538},
    {0x0000040B, 0x4003F0E8, 0x19711000, 0x00026FA4},
    {0x0000040B, 0x40036CD8, 0x1945F800, 0x00023828},
    {0x0000040B, 0x4003F9D0, 0x19738000, 0x00025C68},
    {0x0000040B, 0x4003F9D0, 0x1975E000, 0x00025C68},
    {0x0000040B, 0x4003F9D0, 0x19784000, 0x00025C68},
    {0x0000040B, 0x4003F9D0, 0x197AA000, 0x00025C68},
    {0x0000040B, 0x400413A4, 0x193EB000, 0x000292B0},
    {0x0000040B, 0x40034750, 0x197D0000, 0x000200C4},
    {0x0000040B, 0x40034750, 0x197F0800, 0x000200C4},
    {0x0000040B, 0x40034750, 0x19811000, 0x000200C4},
    {0x0000040B, 0x4002E558, 0x19831800, 0x0001C538},
    {0x0000040B, 0x4003CA98, 0x1984E000, 0x0002768C},
    {0x0000040B, 0x4005577C, 0x19875800, 0x000386A0},
    {0x0000040B, 0x40023EF8, 0x198AE000, 0x00017274},
    {0x0000040B, 0x4003307C, 0x198C5800, 0x000203B8},
    {0x0000040B, 0x4003EF28, 0x198E6000, 0x000297C4},
    {0x0000040B, 0x4003CC00, 0x1990F800, 0x00027F38},
    {0x0000040B, 0x40030574, 0x19937800, 0x0001D740},
    {0x0000040B, 0x40030574, 0x19955000, 0x0001D740},
    {0x0000040B, 0x40030574, 0x19972800, 0x0001D740},
    {0x0000040B, 0x40030574, 0x19990000, 0x0001D740},
    {0x0000040B, 0x40038A88, 0x199AD800, 0x00023C60},
    {0x0000040B, 0x4002A408, 0x199D1800, 0x0001AB60},
    {0x0000040B, 0x40038A88, 0x199EC800, 0x00023C60},
    {0x0000040B, 0x4002A408, 0x19A10800, 0x0001AB60},
    {0x0000040B, 0x4003AD18, 0x19A2B800, 0x00021DBC},
    {0x0000040B, 0x4003AD18, 0x19A4D800, 0x00021DBC},
};
s32 lbl_2_data_2FDC0[32] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x18, 0x1B,
    0x1C, 0x21, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30,
};
void* lbl_2_data_2FE40[2] = {lbl_800F5D98, lbl_800F71D8}; // unreferenced
MenuAsset lbl_2_data_2FE48 = {0x0000040B, 0x400D198C, 0x191D5800, 0x0005D268};
MenuAsset lbl_2_data_2FE58 = {0x0000040B, 0x400204C0, 0x191C1800, 0x00013FCC};
u32 lbl_2_data_2FE68[3] = {0, 0, 0};
MenuDrawNode0F60 lbl_2_data_2FE74 = {2, fn_2_8ACDC}; // unreferenced
u8 lbl_2_data_2FE7C[8] = {5, 6, 9, 11, 7, 8, 10, 12};
s32 lbl_2_data_2FE84[10] = {1, 1, 5, 5, 5, 5, 5, 5, 2, 5};
s32 lbl_2_data_2FEAC[10] = {2, 0xB, 4, 7, 0xA, 2, 8, 0xB, 0x26, 0};
f32 lbl_2_data_2FED4[3] = {0.0f, 0.0f, 0.0f};
Vec lbl_2_data_2FEE0 = {0.0f, 0.0f, 0.0f};
// The jump tables of fn_2_8D270, fn_2_8DFB0 and fn_2_8EA80 follow (defined next to them while NONMATCHING).

static f32 lbl_2_bss_B2B8;
typedef struct {
    u8 pad0[0x25D];
    u8 enabled;
    u8 pad25E[0x1E];
} MenuEntry;

// fn_2_8D24C, size:0x24
void fn_2_8D24C(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_2_8B118, size:0x40
void fn_2_8B118(f32 value) {
    if (value) {
        lbl_2_bss_340140[0x307A] = 3;
    } else {
        lbl_2_bss_340140[0x307A] = 0;
    }
}

// fn_2_8CC88, size:0x24
s32 fn_2_8CC88(s32 index) {
    u8* base = lbl_8036E548;
    u8* object;
    base += index * 4;
    object = *(u8**)(base + 0x2C50);
    return !*(s16*)(object + 0x68);
}

// fn_2_8CCAC, size:0x20
void fn_2_8CCAC(s32 index, u8 value) {
    MenuEntry* entry = (MenuEntry*)(lbl_2_bss_340140 + index * 0x27C + 0xC04);
    if (entry != NULL) {
        entry->enabled = value;
    }
}

// fn_2_8CCCC, size:0x8C
void fn_2_8CCCC(s32 index, s32 a, s32 b, u8 mode, s32 c, s32 d, s32 e, s32 f) {
    u8* p;
    { u8* base = lbl_2_bss_340140; base += index * 4; p = *(u8**)(base + 0x2C50); }
    if (p == NULL) return;
    if (mode == 1 && *(s16*)(p + 0x62) == a) return;
    if (mode == 3) mode = 1;
    *(s16*)(p + 0x64) = a;
    *(s16*)(p + 0x6C) = d;
    p[0x260] = b;
    p[0x25E] = mode;
    p[0x263] = c;
    p[0x266] = e;
    p[0x26D] = 0;
    if (f == -1) {
        p[0x26A] = 5;
    } else {
        p[0x26A] = f;
    }
    *(s16*)(p + 0x66) = -1;
}

// fn_2_8DC00, size:0xD8
void fn_2_8DC00(void) {
    u8* t = (u8*)lbl_2_data_2F990;
    u32 max = 0;
    u32 v;
    s32 i;
    s32 size;
    for (i = 0; i < 13; i++) {
        v = *(u32*)(t + 4) & 0x0FFFFFFF;
        if (max < v) max = v;
        t += 0x10;
    }
    size = (max + 0x1F) & ~0x1F;
    *(void**)(lbl_2_bss_340140 + 0x2C8C) = _OSAllocFromHeap(0x20, size * *(s16*)(lbl_2_bss_1A824C + 0x197746));
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        *(u8**)(lbl_2_bss_340140 + i * 0x27C + 0xC0C) = *(u8**)(lbl_2_bss_340140 + 0x2C8C) + i * size;
    }
}

// fn_2_8C724, size:0xE8
void fn_2_8C724(void) {
    s32 i;
    for (i = 0; i < *(u16*)(lbl_2_bss_340140 + 0x3078); i++) {
        *(f32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 4) = 0.0f;
        *(f32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 8) = 0.0f;
        *(f32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 0xC) = 0.0f;
        *(f32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 0x10) = 0.0f;
        *(f32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 0x14) = 0.0f;
        *(f32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 0x18) = 0.0f;
        *(u8*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28 + 0x26) = 0;
        *(s32*)(*(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28) = 0;
        *(u8*)(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0xA0) = 0;
    }
}

// fn_2_8DB14, size:0xEC
void fn_2_8DB14(void) {
    u32 max = 0;
    u32 v;
    s32 i;
    s32 size;
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        v = lbl_2_data_2F990[i].sizeFlags & 0x0FFFFFFF;
        if (max < v) max = v;
    }
    size = (max + 0x1F) & ~0x1F;
    *(s32*)(lbl_2_bss_340140 + 0x2C90) = size;
    *(void**)(lbl_2_bss_340140 + 0x2C88) = _OSAllocFromHeap(0x20, size * *(s16*)(lbl_2_bss_1A824C + 0x197746));
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        *(s32*)(lbl_2_bss_340140 + i * 0x27C + 0xC14) = 0;
    }
}

extern void fn_800BDC88(void* table, u16 first, u16 last, void* layout, void* anim, void* skin);
extern void fn_800BD548(u8*, s32, ...);
extern void CTRLSetTranslation(u8*, f32, f32, f32);
extern void CTRLSetRotation(u8*, f32, f32, f32);

typedef struct { u8 pad[0x2DA0]; struct { void* v; s32 x; s32 y; } arr[1]; } S2DA0; // v: model layout

// fn_2_8C80C, size:0x104
void fn_2_8C80C(s32 a, s32 b, s32 c, void* d, void* e) {
    s32 i;
    for (i = b; i < b + c; i++) {
        fn_800BDC88(*(u8**)(lbl_2_bss_340140 + 0x68), i, i, ((S2DA0*)lbl_2_bss_340140)->arr[a].v, d, e);
        (*(u8**)(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0x34))[0x99] = 1;
        fn_800BD548(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0x34, 4, *(s32*)(lbl_2_bss_340140 + 0xAC), *(s32*)(lbl_2_bss_340140 + 0xB0), *(s32*)(lbl_2_bss_340140 + 0xB4), *(s32*)(lbl_2_bss_340140 + 0xB8));
        CTRLSetTranslation(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0x44, 0.0f, 0.0f, 0.0f);
        CTRLSetRotation(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0x44, 0.0f, 0.0f, 0.0f);
    }
}

extern u8 lbl_2_data_3CD0[];
extern u8 lbl_800E869C[];

// NONMATCHING 95%: lis of lbl_800E869C scheduled before the lbl_2_bss_1A824C load in case 2
#if NONMATCHING
// fn_2_8D9DC, size:0x138
void fn_2_8D9DC(s32 mode) {
    s32 i;
    
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        *(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50) = lbl_8036E548 + i * 0x27C + 0xC04;
        (*(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50))[0x255] = i;
        (*(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50))[0x254] = i;
        switch (mode) {
        case 0:
            (*(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50))[0x252] = lbl_2_data_3CD0[i];
            break;
        case 1:
            (*(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50))[0x252] = 0x1C;
            break;
        case 2:
            (*(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50))[0x252] = lbl_800E869C[*(s16*)(lbl_2_bss_1A824C + 0x197706)];
            break;
        }
        fn_2_8D270(i);
    }
}
#endif

extern void LoadActorLayout(void* a);
extern void convertGeometryAndSknHeader(void* geometry, void* sknHeader);
extern void* ActorObjectInitTable(u16 n);

// NONMATCHING 96%: original copies i into off (mr r30,r29) and swaps r3/r4 in the pointer table setup
#if NONMATCHING
// fn_2_8B2C0, size:0x158
void fn_2_8B2C0(void) {
    s32 off;
    s32 i;
    u8* t;
    *(u16*)(lbl_2_bss_340140 + 0x3078) = off = i = 0;
    *(u8**)(lbl_2_bss_340140 + 0x2DA0) = (t = *(u8**)(lbl_2_bss_340140 + 0x2D9C)) + *(s32*)(t + 0x0);
    *(u8**)(lbl_2_bss_340140 + 0x2DA4) = t + *(s32*)(t + 0x4);
    *(u8**)(lbl_2_bss_340140 + 0x2DA8) = t + *(s32*)(t + 0x8);
    *(u8**)(lbl_2_bss_340140 + 0x2DAC) = t + *(s32*)(t + 0xC);
    *(u8**)(lbl_2_bss_340140 + 0x2DB0) = t + *(s32*)(t + 0x10);
    *(u8**)(lbl_2_bss_340140 + 0x2DB4) = t + *(s32*)(t + 0x14);
    *(u8**)(lbl_2_bss_340140 + 0x2DB8) = t + *(s32*)(t + 0x18);
    *(u8**)(lbl_2_bss_340140 + 0x2DBC) = t + *(s32*)(t + 0x1C);
    *(u8**)(lbl_2_bss_340140 + 0x2DC0) = t + *(s32*)(t + 0x20);
    *(u8**)(lbl_2_bss_340140 + 0x2DC4) = t + *(s32*)(t + 0x24);
    *(u8**)(lbl_2_bss_340140 + 0x2DC8) = t + *(s32*)(t + 0x28);
    *(u8**)(lbl_2_bss_340140 + 0x2DCC) = t + *(s32*)(t + 0x2C);
    do {
        u8* e = lbl_2_bss_340140 + off;
        u8* a = *(u8**)(e + 0x2DA0);
        u8* g = *(u8**)(e + 0x2DA4);
        u8* x = *(u8**)(e + 0x2DA8);
        LoadActorLayout(a);
        convertGeometryAndSknHeader(g, 0);
        haveActLayoutPointToGeoHeader(a, g);
        convertTextureHeader(x);
        fn_800BD190((struct GQRValueGroups*)g, x);
        i++;
        off += 0xC;
    } while (i < 4);
}
#endif

// fn_2_8B158, size:0x168
void fn_2_8B158(void) {
    s32 i;
    *(u16*)(lbl_2_bss_340140 + 0x3078) = 4;
    *(void**)(lbl_2_bss_340140 + 0x2D94) = _OSAllocFromHeap(0x20, *(u16*)(lbl_2_bss_340140 + 0x3078) * 0x28);
    *(void**)(lbl_2_bss_340140 + 0x68) = ActorObjectInitTable(*(u16*)(lbl_2_bss_340140 + 0x3078));
    for (i = 0; i < *(u16*)(lbl_2_bss_340140 + 0x3078); i++) {
        fn_2_8C80C(i, i, 1, NULL, NULL);
    }
}

extern u8 lbl_80366158[];
extern u8 lbl_803CBC3C;
extern void** fn_800111D8(u8* o);
extern f32 fn_800B4A44(void* actor, u16 bone);

// fn_2_8D024, size:0x228
void fn_2_8D024(void) {
    u8* o;
    s32 i;
    s16 t;
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        o = *(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50);
        if (o != NULL && o[0x25D] != 0) {
            u8* p;
            f32 v;
            u32 id;
            if (*(s16*)(o + 0x6A) < 0x258 && lbl_80366158[0x28] == 0 && lbl_803CBC3C == 0 && o[0x26F] == 0) {
                *(s16*)(o + 0x6A) = *(s16*)(o + 0x6A) + 1;
            }
            p = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
            v = 1.0f;
            if (p != NULL) {
                id = *(u16*)(p + 0x16A);
            } else {
                id = 0xFFFF;
            }
            if ((s32)id != 0xFFFF) {
                v = fn_800B4A44(*fn_800111D8(o), (u16)id);
            }
            *(s16*)(o + 0x68) = v / *(f32*)(o + 0x4C);
            if (o[0x25E] == 1 || (o[0x25E] == 2 && *(s16*)(o + 0x68) == 0 && *(s16*)(o + 0x6A) > 1) || *(s16*)(o + 0x62) == -1) {
                if (*(s16*)(o + 0x64) >= 0 && (fn_2_8CD58(i, *(s16*)(o + 0x64), o[0x260], o[0x263], *(s16*)(o + 0x6C), o[0x266], o[0x26A]),
                    *(s16*)(o + 0x60) = *(s16*)(o + 0x62),
                    *(s16*)(o + 0x62) = *(s16*)(o + 0x64),
                    *(s16*)(o + 0x64) = -1,
                    o[0x25F] = o[0x260],
                    o[0x262] = o[0x263],
                    o[0x265] = o[0x266],
                    o[0x269] = o[0x26A],
                    o[0x26C] = o[0x26D],
                    *(s16*)(o + 0x6A) = 0,
                    t = *(s16*)(o + 0x66),
                    t >= 0)) {
                    *(s16*)(o + 0x64) = t;
                    *(s16*)(o + 0x6C) = *(s16*)(o + 0x6E);
                    o[0x260] = o[0x261];
                    o[0x263] = o[0x264];
                    o[0x25E] = 2;
                    o[0x266] = o[0x267];
                    o[0x26A] = o[0x26B];
                    o[0x26D] = o[0x26E];
                    *(s16*)(o + 0x66) = -1;
                } else {
                    o[0x25E] = 0;
                }
            }
        }
    }
}

extern u8* lbl_803CC1B8;
extern u8 lbl_803C6CF8[];
extern void fn_80052D70(void);

// NONMATCHING 97%: li r6,1 scheduled before the lbl_2_bss_1A824C load in state 6
#if NONMATCHING
// fn_2_8E478, size:0x22C
void fn_2_8E478(void) {
    u8* o = lbl_803CC1B8;
    switch (*(s8*)(o + 0x28)) {
    case 0:
        lbl_2_bss_340140 = lbl_8036E548;
        *(s16*)(o + 0x14) = 0;
        o[0x28] = 1;
        break;
    case 1:
        *(void**)(lbl_2_bss_340140 + 0x2D9C) = ARAMTransfer(&lbl_2_data_2FE48, 0, 0, 0);
        *(s16*)(o + 0x14) = *(s16*)(o + 0x14) + 1;
        o[0x28] = 2;
        break;
    case 2: {
        s32 st = lbl_803C6CF8[0x715];
        if (st == 1) {
            o[0x28] = 5;
        }
        break;
    }
    case 5:
        fn_2_8C910();
        o[0x28] = 6;
        break;
    case 6:
        fn_2_8B418();
        fn_2_8C724();
        fn_80052D70();
        lbl_2_bss_1A824C[0x1978F3] = 1;
        lbl_2_bss_340140[0x307A] = 4;
        {
            u8* q = *(u8**)(lbl_803CC1B8 + 0xC);
            *(s16*)(q + 0x10) = 1;
            fn_800B0A14_removeQueue(q);
        }
        o[0x28] = 0;
        break;
    }
}
#endif

extern void* memcpy(void* d, const void* s, u32 n);
extern f32 fn_2_4A1E8(f32 x, f32 y);
extern u8* lbl_2_bss_3401BC;
extern void CTRLSetTranslation(u8*, f32, f32, f32);
extern void CTRLSetRotation(u8*, f32, f32, f32);

typedef struct { f32 x, y, z; } V3F;
extern const f32 lbl_2_rodata_FB0;
extern const f32 lbl_2_rodata_FB4;
extern const f32 lbl_2_rodata_FB8;
extern const f32 lbl_2_rodata_FBC;

// fn_2_8ACE0, size:0x200
void fn_2_8ACE0(void) {
    f32 x;
    f32 z;
    Vec a;
    Vec b;
    u8* ent;
    s32 i;
    i = 0;
    for (; i < *(u16*)(lbl_2_bss_340140 + 0x3078); i++) {
        ent = *(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28;
        memcpy(&a, ent + 4, 0xC);
        PSVECSubtract(&a, &lbl_2_data_2FEE0, &b);
        x = b.x * lbl_2_rodata_FB0;
        z = b.z * lbl_2_rodata_FB0;
        b.x = x;
        b.z = z;
        if (0.0f != x || 0.0f != z) {
            lbl_2_bss_B2B8 = fn_2_4A1E8(b.z, x);
        }
        memcpy(&lbl_2_data_2FEE0, ent + 4, 0xC);
        if (0.0f != a.x) *(f32*)(ent + 4) = a.x * lbl_2_rodata_FB8;
        if (0.0f != a.y) *(f32*)(ent + 8) = a.y * lbl_2_rodata_FB8;
        if (0.0f != a.z) *(f32*)(ent + 0xC) = a.z * lbl_2_rodata_FB8;
        lbl_2_data_2FED4[1] = *(f32*)(ent + 0x14);
        CTRLSetTranslation(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0x44, a.x, a.y, a.z);
        CTRLSetRotation(*(u8**)(lbl_2_bss_340140 + 0x68) + i * 0x90 + 0x44, lbl_2_rodata_FBC * lbl_2_data_2FED4[0], lbl_2_rodata_FBC * lbl_2_data_2FED4[1], lbl_2_rodata_FBC * lbl_2_data_2FED4[2]);
        (*(u8**)(lbl_2_bss_340140 + 0x68))[i * 0x90 + 0xA0] = lbl_2_bss_3401BC[i + 0x50];
    }
}

extern Mtx lbl_2_bss_1A81D4;
extern void fn_2_190DC(u8*, Mtx);

// fn_2_8AEE0, size:0x238
void fn_2_8AEE0(void) {
    fn_2_8ACE0();
    PSMTXCopy(lbl_2_bss_1A81D4, fn_80052768_getCamera(0)->view);
    fn_2_190DC(*(u8**)(lbl_2_bss_340140 + 0x68), fn_80052768_getCamera(0)->view);
}

extern void fn_80023B04(s32 count);
extern void fn_80014204(s32 count);
extern void* fn_80023AA4(void);

// NONMATCHING 97%: original keeps &lbl_2_data_2F990 in r31 across the inlined fn_2_8DC00/fn_2_8DB14 table scans
#if NONMATCHING
// .text:0x8DCD8 size:0x2D8
void fn_2_8DCD8(void) {
    s32 i;
    fn_2_8DC00();
    fn_2_8DB14();
    fn_80023B04(*(s16*)(lbl_2_bss_1A824C + 0x197746));
    fn_80014204(*(s16*)(lbl_2_bss_1A824C + 0x197746));
    *(void**)(lbl_2_bss_340140 + 0x13C) = fn_80023AA4();
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        *(s8*)(lbl_2_bss_340140 + i * 0x27C + 0xE59) = i;
        *(u8**)(lbl_2_bss_340140 + i * 4 + 0x2C50) = NULL;
        *(s8*)(lbl_2_bss_340140 + i + 0x2D6A) = -1;
        *(s8*)(lbl_2_bss_340140 + i * 0x27C + 0xE5B) = -1;
    }
    for (i = 0; i < 9; i++) {
        *(s8*)(lbl_2_bss_340140 + i + 0x2D7F) = -1;
    }
    for (i = 0; i < 4; i++) {
        *(s8*)(lbl_2_bss_340140 + i + 0x2D89) = -1;
    }
    lbl_2_bss_340140[0x2D77] = 0;
    lbl_2_bss_340140[0x2D7B] = 0;
}
#endif

extern void fn_800B2B54(struct GameActor* actor, u16 bone, u8 value);
extern void fn_800B2B4C(struct GameActor* actor, f32 speed);
extern void fn_8001B308(s32 index, s32 enable);
extern void fn_8001B5EC(s32 index, s32 enable);
extern const f32 lbl_2_rodata_FC0;
extern const f32 lbl_2_rodata_FC4;

// Joint 4 of active actor `index` in lbl_8036E548, or 0xFFFF.
#define ACTIVE_JOINT4(index) \
    (((MenuActor**)(lbl_8036E548 + 0x2C50))[index] != NULL ? ((MenuActor**)(lbl_8036E548 + 0x2C50))[index]->joints[4] : 0xFFFF)

// .text:0x8CD58 size:0x2CC
void fn_2_8CD58(s32 index, s32 anim, u8 loop, u8 face, s16 time, u8 eyes, u8 frames) {
    MenuActor* actor;
    s32 shapeTable;
    s32 shapeEntry;
    MenuAnimObject* obj;
    f32 speed = lbl_2_rodata_FB4;
    MenuAnimBank* bank;
    u8 valid;
    actor = ((MenuActor**)(lbl_2_bss_340140 + 0x2C50))[index];
    if (index == 4) {
        shapeTable = 1;
        shapeEntry = 0;
    } else {
        shapeTable = lbl_2_data_2FE84[anim];
        shapeEntry = lbl_2_data_2FEAC[anim];
    }
    if (actor == NULL) {
        return;
    }
    obj = (MenuAnimObject*)fn_800111D8((u8*)actor);
    if (frames != 0) {
        speed = lbl_2_rodata_FC0 / frames;
    }
    if (actor->blend == 0) {
        fn_800B2B54(actor->actor, ACTIVE_JOINT4(index), 13);
    } else {
        fn_800B2B54(actor->actor, ACTIVE_JOINT4(index), 1);
        fn_800B2B54(obj->actor, ACTIVE_JOINT4(index), 1);
        fn_800B2B4C(obj->actor, lbl_2_rodata_FC4);
        ((MenuModel*)obj->actor)->blend = lbl_2_rodata_FB4;
    }
    if (actor->face != NULL) {
        fn_80025EEC(&actor->face->main.anim, shapeTable, shapeEntry);
    }
    if (actor->faceSub != NULL && actor->faceSub->hasSub) {
        fn_80025EEC(&actor->faceSub->sub.anim, shapeTable, shapeEntry);
        fn_80025EEC(&actor->faceSub->main.anim, shapeTable, shapeEntry);
    }
    bank = actor->animBank;
    if (bank != NULL) {
        if (anim >= bank->count) return;
        if (anim < 0) return;
        obj->animBank = bank;
        obj->seqNum = anim;
        obj->time = lbl_2_rodata_FB4;
        obj->setAnimation = 1;
        valid = bank != NULL;
        obj->setTime = valid;
        obj->setSpeed = valid;
        obj->speed = speed;
    }
    if (loop) {
        obj->visFlags = 3;
    } else {
        obj->visFlags = 2;
    }
    obj->time = time * actor->animFrames;
    obj->setTime = 1;
    fn_8001B5EC(index, face);
    fn_8001B308(index, eyes);
    actor->faceMode = face;
}

#include "C3/anim.h"

// Relocated resource pointers at lbl_2_bss_340140 + 0x2DA0: 19 x (actor layout, geometry, textures).
#define MENU_RES(i) (*(u8**)(lbl_2_bss_340140 + (i) * 4 + 0x2DA0))
// Animation banks at lbl_2_bss_3401BC + 0xC, indexed like the menu slots.
#define MENU_ANIM_BANK(i) (*(ANIMBank**)(lbl_2_bss_3401BC + (i) * 4 + 0xC))

// NONMATCHING 83%: original folds the i<57 precheck of the unrolled first loop and swaps r30/r31 (i/file)
#if NONMATCHING
// .text:0x8C910 size:0x378
void fn_2_8C910(void) {
    s32 i;
    s32 j;
    u8* file;
    *(u16*)(lbl_2_bss_340140 + 0x3078) = 0;
    file = *(u8**)(lbl_2_bss_340140 + 0x2D9C);
    for (i = 0; i < 19 * 3; i++) {
        MENU_RES(i) = file + ((s32*)file)[i];
    }
    for (j = 0; j < 7; j++, i++) {
        MENU_ANIM_BANK(1 + j) = (ANIMBank*)(file + ((s32*)file)[i]);
        ANIMGet(MENU_ANIM_BANK(1 + j));
    }
    for (j = 0; j < 2; j++, i++) {
        MENU_ANIM_BANK(8 + j) = (ANIMBank*)(file + ((s32*)file)[i]);
        ANIMGet(MENU_ANIM_BANK(8 + j));
    }
    MENU_ANIM_BANK(10) = (ANIMBank*)(file + ((s32*)file)[i]);
    ANIMGet(MENU_ANIM_BANK(10));
    MENU_ANIM_BANK(11) = (ANIMBank*)(file + ((s32*)file)[i + 1]);
    ANIMGet(MENU_ANIM_BANK(11));
    MENU_ANIM_BANK(12) = (ANIMBank*)(file + ((s32*)file)[i + 2]);
    ANIMGet(MENU_ANIM_BANK(12));
    MENU_ANIM_BANK(13) = (ANIMBank*)(file + ((s32*)file)[i + 3]);
    ANIMGet(MENU_ANIM_BANK(13));
    MENU_ANIM_BANK(14) = (ANIMBank*)(file + ((s32*)file)[i + 4]);
    ANIMGet(MENU_ANIM_BANK(14));
    MENU_ANIM_BANK(15) = (ANIMBank*)(file + ((s32*)file)[i + 5]);
    ANIMGet(MENU_ANIM_BANK(15));
    MENU_ANIM_BANK(16) = (ANIMBank*)(file + ((s32*)file)[i + 6]);
    ANIMGet(MENU_ANIM_BANK(16));
    for (j = 0; j < 19; j++) {
        u8* e = lbl_2_bss_340140 + j * 0xC;
        u8* a = *(u8**)(e + 0x2DA0);
        u8* g = *(u8**)(e + 0x2DA4);
        u8* x = *(u8**)(e + 0x2DA8);
        LoadActorLayout(a);
        convertGeometryAndSknHeader(g, 0);
        haveActLayoutPointToGeoHeader(a, g);
        convertTextureHeader(x);
        fn_800BD190((struct GQRValueGroups*)g, x);
    }
}
#endif

extern void fn_2_4E824(void);
extern void fn_2_48DB4(void);
extern void fn_2_93C64(void);

#if !NONMATCHING
// Switch jump tables of fn_2_8DFB0; mwcc emits them itself once the function matches.
void* jumptable_2_data_2FFAC[11] = {
    (u8*)fn_2_8DFB0 + 0x44, (u8*)fn_2_8DFB0 + 0x78, (u8*)fn_2_8DFB0 + 0xCC, (u8*)fn_2_8DFB0 + 0x4B4,
    (u8*)fn_2_8DFB0 + 0x4B4, (u8*)fn_2_8DFB0 + 0xEC, (u8*)fn_2_8DFB0 + 0x22C, (u8*)fn_2_8DFB0 + 0x44C,
    (u8*)fn_2_8DFB0 + 0x458, (u8*)fn_2_8DFB0 + 0x478, (u8*)fn_2_8DFB0 + 0x484,
};
#endif

// NONMATCHING 98%: the inlined fn_2_8B2C0 has the same i/off copy and r3/r4 swap as fn_2_8B2C0
#if NONMATCHING
// .text:0x8DFB0 size:0x4C8
void fn_2_8DFB0(void) {
    u8* task = lbl_803CC1B8;
    switch (*(s8*)(task + 0x28)) {
    case 0:
        lbl_2_bss_340140 = lbl_8036E548;
        *(s16*)(task + 0x14) = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_48DB4();
        fn_2_93C64();
        task[0x28] = 1;
        break;
    case 1:
        *(s16*)(lbl_2_bss_1A824C + 0x197746) = 0;
        *(void**)(lbl_2_bss_340140 + 0x2D9C) = ARAMTransfer(&lbl_2_data_2FE58, 0, 0, 0);
        *(s16*)(task + 0x14) = *(s16*)(task + 0x14) + 1;
        task[0x28] = 2;
        break;
    case 2: {
        s32 st = lbl_803C6CF8[0x715];
        if (st == 1) {
            task[0x28] = 5;
        }
        break;
    }
    case 5:
        fn_2_8B2C0();
        task[0x28] = 6;
        break;
    case 6:
        fn_2_8B158();
        fn_2_8C724();
        fn_80052D70();
        task[0x28] = 7;
        break;
    case 7:
        task[0x28] = 8;
        break;
    case 8:
        lbl_2_bss_340140[0x307A] = 3;
        task[0x28] = 9;
        break;
    case 9:
        task[0x28] = 10;
        break;
    case 10: {
        u8* q;
        lbl_2_bss_340140[0x307A] = 3;
        q = *(u8**)(lbl_803CC1B8 + 0xC);
        *(s16*)(q + 0x10) = 1;
        fn_800B0A14_removeQueue(q);
        task[0x28] = 0;
        break;
    }
    }
}
#endif

struct ActorSlot;
extern void fn_8002399C(struct ActorSlot* slot, u16 index, s16 id, void* layout, void* anim, void* arg5);
extern void fn_800B2B74(struct GameActor* actor, u16 bone);
extern struct DODisplayObj* fn_800B2BA8(struct GameActor* actor, u16 bone, struct GameActor* src, u16 srcBone);
extern void fn_800B2C08(struct GameActor* actor, u16 bone);
extern void fn_800126EC(MenuFacePart* part, void* tex, u8* fileIdx);
extern void fn_8001D180(s32 index, s32 which, s32 enable);
extern void fn_80014990(s32 index, void* model, void* set);
extern void fn_8001FC4C(MenuActor* actor);
extern s32 fn_800638B4(void* player, void* slot);
extern s32 fn_80063010(void* player, void* slot);
extern s32 fn_8004B7B4(void* player, void* slot);
extern s32 fn_800637BC(void* player, void* slot);
extern s32 fn_8004BD6C(void* player, void* slot);
extern s32 fn_800637D4(void* player, void* slot);
extern void* fn_80052634(void* player, void* slot);
extern s32 fn_80062ED4(void* player, void* slot);
extern void* memset(void* str, int c, u32 n);
extern const f32 lbl_2_rodata_FB8;

// Sets bone `j` of the slot's model up as a separately drawn part (0xFFFF: no such bone).
#define MENU_DETACH_JOINT(slot, j) \
    if ((j) != 0xFFFF) { \
        fn_800B2BA8((slot)->actor, (j), NULL, 0); \
        ((MenuModel*)(slot)->actor)->joints[(u16)(j)]->_136 = 1; \
    }

#if !NONMATCHING
// Switch jump tables of fn_2_8D270; mwcc emits them itself once the function matches.
void* jumptable_2_data_2FEEC[48] = {
    (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x678, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x688, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x688, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x6B8, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x71C, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x72C, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x70C, (u8*)fn_2_8D270 + 0x6A8,
    (u8*)fn_2_8D270 + 0x6D8, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x6C8, (u8*)fn_2_8D270 + 0x6C8, (u8*)fn_2_8D270 + 0x6C8, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x738, (u8*)fn_2_8D270 + 0x698, (u8*)fn_2_8D270 + 0x698, (u8*)fn_2_8D270 + 0x698,
    (u8*)fn_2_8D270 + 0x698, (u8*)fn_2_8D270 + 0x71C, (u8*)fn_2_8D270 + 0x6E8, (u8*)fn_2_8D270 + 0x738,
    (u8*)fn_2_8D270 + 0x70C, (u8*)fn_2_8D270 + 0x700, (u8*)fn_2_8D270 + 0x6B8, (u8*)fn_2_8D270 + 0x6D8,
    (u8*)fn_2_8D270 + 0x72C, (u8*)fn_2_8D270 + 0x72C, (u8*)fn_2_8D270 + 0x72C, (u8*)fn_2_8D270 + 0x72C,
};
#endif

// NONMATCHING 94%: register allocation (slot r28/r29), joint ids compared as s32 (addis), kind test via a flag
#if NONMATCHING
// Menu version of fn_80017814: relocates and sets up the model of actor `index`.
// .text:0x8D270 size:0x76C
void fn_2_8D270(u8 index) {
    MenuActor* actor = (MenuActor*)(lbl_2_bss_340140 + index * 0x27C + 0xC04);
    MenuAnimObject* slot = (MenuAnimObject*)fn_800111D8((u8*)actor);
    void** files = actor->files;
    void* tex;
    void* layout;
    void* geo;
    void* skn;
    MenuAnimObject* modelSlot;
    MenuFaceAnim* face;
    s32 count;
    s32 i;
    u16 j;
    s32 partA;
    s32 partB;

    // TODO type: the file header holds offsets that are relocated in place.
    for (i = 0; i < 15; i++) {
        if (actor->files[i] == NULL) {
            break;
        }
        actor->files[i] = (u8*)files + (u32)files[i];
    }
    tex = actor->files[0];
    convertTextureHeader(tex);
    if (actor->files[1] != NULL) {
        layout = actor->files[1];
        geo = actor->files[2];
        skn = actor->files[3];
        LoadActorLayout(layout);
        convertGeometryAndSknHeader(geo, skn);
        haveActLayoutPointToGeoHeader(layout, geo);
        fn_800BD190((struct GQRValueGroups*)geo, tex);
    } else {
        return;
    }
    actor->animBank = (MenuAnimBank*)actor->files[4];
    ANIMGet((ANIMBank*)actor->animBank);
    fn_8002399C((struct ActorSlot*)slot, actor->modelIndex, index, layout, actor->animBank, skn);

    modelSlot = (MenuAnimObject*)(*(u8**)(lbl_2_bss_340140 + 0x60) + index * 0x90 + 0x34);
    if (actor == NULL && *(u8**)(lbl_2_bss_340140 + 0x60) == NULL && modelSlot == NULL) {
        return;
    }
    count = ((MenuModel*)modelSlot->actor)->jointCount;
    memset(actor->joints, 0xFF, sizeof(actor->joints));
    for (i = 0; i < count; i++) {
        if (((MenuModel*)modelSlot->actor)->joints[i]->id != 0xFFFF) {
            actor->joints[((MenuModel*)modelSlot->actor)->joints[i]->id] = i;
        }
    }
    fn_800B2B74(slot->actor, actor->joints[19]);
    fn_800B2B74(slot->actor, actor->joints[25]);
    fn_800B2B74(slot->actor, actor->joints[36]);
    actor->actor = slot->actor;
    if (actor->joints[3] != 0xFFFF) {
        fn_800B2B54(actor->actor, actor->joints[3], 0xD);
    }
    fn_800BD548((u8*)slot, 4, *(s32*)(lbl_2_bss_340140 + 0xAC), *(s32*)(lbl_2_bss_340140 + 0xB0),
                *(s32*)(lbl_2_bss_340140 + 0xB4), *(s32*)(lbl_2_bss_340140 + 0xB8));
    actor->rot.x = actor->rot.y = actor->rot.z = lbl_2_rodata_FB4;
    CTRLSetTranslation(slot->ctrl, lbl_2_rodata_FB4, lbl_2_rodata_FB4, lbl_2_rodata_FB4);
    CTRLSetRotation(slot->ctrl, lbl_2_rodata_FB4, lbl_2_rodata_FB4, lbl_2_rodata_FB4);
    slot->_54 = lbl_2_rodata_FB8;
    slot->setSpeed = 1;
    j = actor->joints[3];
    MENU_DETACH_JOINT(slot, j)
    j = actor->joints[2];
    MENU_DETACH_JOINT(slot, j)
    j = actor->joints[1];
    MENU_DETACH_JOINT(slot, j)
    if (actor->joints[36] != 0xFFFF) {
        fn_800B2BA8(slot->actor, actor->joints[36], NULL, 0);
    }
    j = actor->joints[46];
    MENU_DETACH_JOINT(slot, j)

    face = (MenuFaceAnim*)(lbl_2_bss_340140 + actor->modelIndex * 0xD4 + 0x140);
    if (actor->files[5] != NULL) {
        actor->faceSub = (MenuFaceAnim*)(lbl_2_bss_340140 + index * 0xD4 + 0x140);
        face->main.files = actor->files;
        fn_800126EC(&face->main, tex, lbl_2_data_2FE7C);
        face->sub.files = actor->files;
        fn_800126EC(&face->sub, tex, lbl_2_data_2FE7C + 4);
    }
    if (actor->kind == 18 || actor->kind == 38 || actor->kind == 40 || actor->kind == 41) {
        switch (actor->kind) {
        case 18:
            partA = 4;
            partB = 5;
            break;
        case 38:
            partA = 2;
            partB = 3;
            break;
        case 40:
        case 41:
            partA = 6;
            partB = 7;
            break;
        }
    } else {
        partA = 1;
        partB = 0;
    }
    fn_8001D180(index, partA, 1);
    fn_8001D180(index, partB, 1);
    actor->face = NULL;
    if (actor->files[13] != NULL && actor->files[14] != NULL) {
        u8* shape = actor->files[13];
        void* set = actor->files[14];
        fn_80025DDC(shape);
        fn_80014990(index, shape, set);
        fn_80025C58((ShapeData*)shape, (ShapeModel**)&slot->actor);
    }
    actor->faceSub->hasSub = 1;
    actor->faceSub->sub.anim.state.speed = lbl_2_rodata_FB8;
    actor->faceSub->main.anim.state.speed = lbl_2_rodata_FB8;
    fn_800B2C08(slot->actor, actor->joints[4]);
    fn_8001FC4C(actor);
    slot->callback = fn_2_8D24C;
    for (i = 0; i < 8; i++) {
        actor->anims[i] = -1;
    }
    actor->_25D[0] = 0;
    actor->_25D[1] = 0;
    actor->_25D[2] = 0;
    actor->_25D[3] = 0;
    actor->_25D[4] = 0;
    actor->_25D[5] = 1;
    actor->_25D[6] = 1;
    actor->_25D[7] = 1;
    actor->_25D[8] = 0;
    actor->_25D[9] = 0;
    actor->_25D[10] = 0;
    actor->faceMode = 0;
    actor->_269[0] = 0;
    actor->_269[1] = 0;
    actor->_269[2] = 0;
    actor->blend = 0;
    actor->_26D[0] = 0;
    actor->_26D[1] = 0;
    actor->_270[0] = 0;
    actor->_270[1] = 0;
    actor->_270[2] = 0;
    actor->_270[3] = 0;
    actor->_277 = 0xFF;
    actor->_05C = 0;
    actor->animFrames = lbl_2_rodata_FB8;
    switch (actor->kind) {
    case 2:
        fn_800638B4(actor, slot);
        break;
    case 33:
    case 34:
    case 35:
    case 36:
        fn_80063010(actor, slot);
        break;
    case 19:
        fn_8004B7B4(actor, slot);
        break;
    case 6:
    case 10:
        ((MenuModel*)slot->actor)->_99 = 1;
        break;
    case 12:
    case 42:
        ((MenuModel*)slot->actor)->_99 = 1;
        break;
    case 24:
    case 25:
    case 26:
        ((MenuModel*)slot->actor)->_99 = 1;
        break;
    case 20:
    case 43:
        fn_800637BC(actor, slot);
        break;
    case 38:
        ((MenuModel*)slot->actor)->_99 = 1;
        fn_8004BD6C(actor, slot);
        break;
    case 41:
        fn_800637D4(actor, slot);
    case 18:
    case 40:
        fn_8004BD6C(actor, slot);
        break;
    case 14:
    case 37:
        fn_80052634(actor, slot);
        break;
    case 16:
    case 44:
    case 45:
    case 46:
    case 47:
        fn_80062ED4(actor, slot);
        break;
    }
    fn_2_8CD58(index, 0, 1, 1, 0, 0, 0);
}
#endif

// Sets up the 29 actor objects of the menu scene from the 19 resource sets
// (objects 10..15 share set 10, objects 16..21 share set 11).
// .text:0x8B418 size:0x130C
void fn_2_8B418(void) {
    *(u16*)(lbl_2_bss_340140 + 0x3078) = 29;
    *(void**)(lbl_2_bss_340140 + 0x2D94) = _OSAllocFromHeap(0x20, *(u16*)(lbl_2_bss_340140 + 0x3078) * 0x28);
    *(void**)(lbl_2_bss_340140 + 0x68) = ActorObjectInitTable(*(u16*)(lbl_2_bss_340140 + 0x3078));
    fn_2_8C80C(0, 0, 1, NULL, NULL);
    fn_2_8C80C(1, 1, 1, NULL, NULL);
    fn_2_8C80C(2, 2, 1, NULL, NULL);
    fn_2_8C80C(3, 3, 1, NULL, NULL);
    fn_2_8C80C(4, 4, 1, NULL, NULL);
    fn_2_8C80C(5, 5, 1, NULL, NULL);
    fn_2_8C80C(6, 6, 1, NULL, NULL);
    fn_2_8C80C(7, 7, 1, NULL, NULL);
    fn_2_8C80C(8, 8, 1, NULL, NULL);
    fn_2_8C80C(9, 9, 1, NULL, NULL);
    fn_2_8C80C(10, 10, 1, NULL, NULL);
    fn_2_8C80C(10, 11, 1, NULL, NULL);
    fn_2_8C80C(10, 12, 1, NULL, NULL);
    fn_2_8C80C(10, 13, 1, NULL, NULL);
    fn_2_8C80C(10, 14, 1, NULL, NULL);
    fn_2_8C80C(10, 15, 1, NULL, NULL);
    fn_2_8C80C(11, 16, 1, NULL, NULL);
    fn_2_8C80C(11, 17, 1, NULL, NULL);
    fn_2_8C80C(11, 18, 1, NULL, NULL);
    fn_2_8C80C(11, 19, 1, NULL, NULL);
    fn_2_8C80C(11, 20, 1, NULL, NULL);
    fn_2_8C80C(11, 21, 1, NULL, NULL);
    fn_2_8C80C(12, 22, 1, NULL, NULL);
    fn_2_8C80C(13, 23, 1, NULL, NULL);
    fn_2_8C80C(14, 24, 1, NULL, NULL);
    fn_2_8C80C(15, 25, 1, NULL, NULL);
    fn_2_8C80C(16, 26, 1, NULL, NULL);
    fn_2_8C80C(17, 27, 1, NULL, NULL);
    fn_2_8C80C(18, 28, 1, NULL, NULL);
}

// ---- 0x8E6A4..0x8ED4C: menu actor loader tasks ----

extern u8 lbl_2_bss_3401C0[0x74];
extern u8* lbl_2_bss_1A8248[];
extern void fn_2_94854(s32 value);
extern void fn_2_9461C(s16 value);
extern void fn_2_94604(u8 value);
extern void fn_2_94634(s32 i);

// lbl_2_bss_340140 points at lbl_8036E548 (MenuActorMgr view).
#define MENU_MGR ((MenuActorMgr*)lbl_2_bss_340140)
// TODO type: lbl_2_bss_1A824C work area
#define MENU_ACTOR_COUNT (*(s16*)(lbl_2_bss_1A824C + 0x197746))
#define MENU_STADIUM (*(s16*)(lbl_2_bss_1A824C + 0x197706))

// .text:0x0008E6A4 size:0x200
// NONMATCHING 93.8%: actor loop induction registers rotated (i/actor/offset; docs/patterns/loops.md)
#if NONMATCHING
void fn_2_8E6A4(void) {
    s32 i;
    MenuLoadTask* parent;
    MenuLoadTask* task = (MenuLoadTask*)lbl_803CC1B8;

    switch (task->step) {
    case 0:
        lbl_2_bss_340140 = lbl_8036E548;
        task->count = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        task->step = 1;
        break;
    case 1:
        MENU_MGR->actors[task->count].files =
            ARAMTransfer(&lbl_2_data_2FA60[lbl_2_data_2FDC0[task->kind]], 0, 0, 0);
        task->count++;
        task->step = 2;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            task->step = 5;
        }
        break;
    case 5:
        for (i = 0; i < MENU_ACTOR_COUNT; i++) {
            MENU_MGR->active[i] = &((MenuActorMgr*)lbl_8036E548)->actors[i];
            MENU_MGR->active[i]->modelIndex = i;
            MENU_MGR->active[i]->_254 = i;
            MENU_MGR->active[i]->kind = lbl_800E869C[MENU_STADIUM];
            fn_2_8D270(i);
        }
        task->step = 6;
        break;
    case 6:
        MENU_MGR->_307A = 2;
        parent = ((MenuLoadTask*)lbl_803CC1B8)->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif

// .text:0x0008E8A4 size:0x1DC
// NONMATCHING 92.3%: actor loop induction registers rotated (i/actor/offset; docs/patterns/loops.md)
#if NONMATCHING
void fn_2_8E8A4(void) {
    s32 i;
    MenuLoadTask* parent;
    MenuLoadTask* task = (MenuLoadTask*)lbl_803CC1B8;

    switch (task->step) {
    case 0:
        lbl_2_bss_340140 = lbl_8036E548;
        task->count = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        task->step = 1;
        break;
    case 1:
        MENU_MGR->actors[task->count].files = ARAMTransfer(&lbl_2_data_2F990[task->kind], 0, 0, 0);
        task->count++;
        task->step = 2;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            task->step = 5;
        }
        break;
    case 5:
        for (i = 0; i < MENU_ACTOR_COUNT; i++) {
            MENU_MGR->active[i] = &((MenuActorMgr*)lbl_8036E548)->actors[i];
            MENU_MGR->active[i]->modelIndex = i;
            MENU_MGR->active[i]->_254 = i;
            MENU_MGR->active[i]->kind = 0x1C;
            fn_2_8D270(i);
        }
        task->step = 6;
        break;
    case 6:
        MENU_MGR->_307A = 2;
        parent = ((MenuLoadTask*)lbl_803CC1B8)->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif

#if !NONMATCHING
// Switch jump tables of fn_2_8EA80; mwcc emits them itself once the function matches.
void* jumptable_2_data_2FFD8[8] = {
    (u8*)fn_2_8EA80 + 0x40, (u8*)fn_2_8EA80 + 0x88, (u8*)fn_2_8EA80 + 0xEC, (u8*)fn_2_8EA80 + 0x10C,
    (u8*)fn_2_8EA80 + 0x168, (u8*)fn_2_8EA80 + 0x1B4, (u8*)fn_2_8EA80 + 0x250, (u8*)fn_2_8EA80 + 0x25C,
};
#endif

// .text:0x0008EA80 size:0x2CC
// NONMATCHING 95.7%: actor loop induction registers rotated (i/actor/offset; docs/patterns/loops.md)
#if NONMATCHING
void fn_2_8EA80(void) {
    s32 i;
    MenuLoadTask* parent;
    MenuLoadTask* task = (MenuLoadTask*)lbl_803CC1B8;

    switch (task->step) {
    case 0:
        lbl_2_bss_340140 = lbl_8036E548;
        lbl_2_bss_3401BC = lbl_2_bss_3401C0;
        task->count = 0;
        fn_2_4E824();
        fn_80052D70();
        fn_2_8DCD8();
        fn_2_48DB4();
        fn_2_93C64();
        task->step = 1;
        break;
    case 1:
        // TODO type: lbl_2_bss_1A8248[0] + 0x441C is the selected stadium/file index
        MENU_MGR->actors[task->count].files =
            ARAMTransfer(&lbl_2_data_2F990[lbl_2_bss_1A8248[0][0x441C]], 0, 0, 0);
        task->count++;
        task->step = 2;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            task->step = 3;
        }
        break;
    case 3:
        MENU_MGR->actors[task->count].files = ARAMTransfer(&lbl_2_data_2F990[task->count + 5], 0, 0, 0);
        task->count++;
        task->step = 4;
        break;
    case 4:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            if (task->count == MENU_ACTOR_COUNT) {
                task->step = 5;
            } else {
                task->step = 3;
            }
        }
        break;
    case 5:
        for (i = 0; i < MENU_ACTOR_COUNT; i++) {
            MENU_MGR->active[i] = &((MenuActorMgr*)lbl_8036E548)->actors[i];
            MENU_MGR->active[i]->modelIndex = i;
            MENU_MGR->active[i]->_254 = i;
            MENU_MGR->active[i]->kind = lbl_2_data_3CD0[i];
            fn_2_8D270(i);
        }
        task->step = 6;
        break;
    case 6:
        task->step = 7;
        break;
    case 7:
        fn_2_94854(0xB);
        fn_2_9461C(0);
        fn_2_94604(0);
        fn_2_94634(1);
        fn_2_93C64();
        MENU_MGR->_307A = 2;
        parent = ((MenuLoadTask*)lbl_803CC1B8)->parent;
        parent->_10 = 1;
        fn_800B0A14_removeQueue(parent);
        task->step = 0;
        break;
    }
}
#endif
