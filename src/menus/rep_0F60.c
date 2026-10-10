#include "menus/rep_0F60.h"

#include "static/UnknownHomes_Static.h"


extern u8* lbl_2_bss_1A8248[];
extern u8 lbl_8036E548[];
extern u8* lbl_2_bss_340140;
extern u8* lbl_2_bss_1A824C;
extern u8 lbl_2_data_2F990[];
extern void* _OSAllocFromHeap(s32 alignment, s32 size);
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
        lbl_2_bss_1A8248[0][0x307A] = 3;
    } else {
        lbl_2_bss_1A8248[0][0x307A] = 0;
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
    u8* t = lbl_2_data_2F990;
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
        v = *(u32*)(lbl_2_data_2F990 + i * 0x10 + 4) & 0x0FFFFFFF;
        if (max < v) max = v;
    }
    size = (max + 0x1F) & ~0x1F;
    *(s32*)(lbl_2_bss_340140 + 0x2C90) = size;
    *(void**)(lbl_2_bss_340140 + 0x2C88) = _OSAllocFromHeap(0x20, size * *(s16*)(lbl_2_bss_1A824C + 0x197746));
    for (i = 0; i < *(s16*)(lbl_2_bss_1A824C + 0x197746); i++) {
        *(s32*)(lbl_2_bss_340140 + i * 0x27C + 0xC14) = 0;
    }
}

extern void fn_800BDC88(u8*, u16, u16, s32, s32, s32);
extern void fn_800BD548(u8*, s32, ...);
extern void CTRLSetTranslation(u8*, f32, f32, f32);
extern void CTRLSetRotation(u8*, f32, f32, f32);

typedef struct { u8 pad[0x2DA0]; struct { s32 v; s32 x; s32 y; } arr[1]; } S2DA0;

// fn_2_8C80C, size:0x104
void fn_2_8C80C(s32 a, s32 b, s32 c, s32 d, s32 e) {
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
extern void fn_2_8D270(u8 a);

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

extern void LoadActorLayout(void* a);
extern void convertGeometryAndSknHeader(void* a, s32 b);
extern void* ActorObjectInitTable(u16 n);

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
        fn_800BD190((struct GQRValueGroups*)g, (s32)x);
        i++;
        off += 0xC;
    } while (i < 4);
}

// fn_2_8B158, size:0x168
void fn_2_8B158(void) {
    s32 i;
    *(u16*)(lbl_2_bss_340140 + 0x3078) = 4;
    *(void**)(lbl_2_bss_340140 + 0x2D94) = _OSAllocFromHeap(0x20, *(u16*)(lbl_2_bss_340140 + 0x3078) * 0x28);
    *(void**)(lbl_2_bss_340140 + 0x68) = ActorObjectInitTable(*(u16*)(lbl_2_bss_340140 + 0x3078));
    for (i = 0; i < *(u16*)(lbl_2_bss_340140 + 0x3078); i++) {
        fn_2_8C80C(i, i, 1, 0, 0);
    }
}

extern u8 lbl_80366158[];
extern u8 lbl_803CBC3C;
extern s32* fn_800111D8(u8* o);
extern f32 fn_800B4A44(s32 a, u16 b);
extern void fn_2_8CD58(s32, s16, u8, u8, s16, u8, u8);

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
extern u8 lbl_2_data_2FE48[];
extern void fn_2_8C910(void);
extern void fn_2_8B418(void);
extern void fn_80052D70(void);

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
        *(s32*)(lbl_2_bss_340140 + 0x2D9C) = ARAMTransfer(lbl_2_data_2FE48, 0, 0, 0);
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

extern void* memcpy(void* d, const void* s, u32 n);
extern f32 fn_2_4A1E8(f32 x);
extern Vec lbl_2_data_2FEE0;
extern f32 lbl_2_data_2FED4[];
extern f32 lbl_2_bss_B2B8;
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
    Vec a;
    Vec b;
    u8* ent;
    s32 i;
    i = 0;
    for (; i < *(u16*)(lbl_2_bss_340140 + 0x3078); i++) {
        ent = *(u8**)(lbl_2_bss_340140 + 0x2D94) + i * 0x28;
        memcpy(&a, ent + 4, 0xC);
        PSVECSubtract(&a, &lbl_2_data_2FEE0, &b);
        b.x = b.x * lbl_2_rodata_FB0;
        b.z = b.z * lbl_2_rodata_FB0;
        if (0.0f != b.x || 0.0f != b.z) {
            lbl_2_bss_B2B8 = fn_2_4A1E8(b.z);
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
