#include "game/rep_1E08.h"
#include "header_rep_data.h"
typedef struct { f32 x, y; } V2f;
extern V2f lbl_3_data_111C8[];
extern void fn_8003A688(f32, f32);

extern u8 lbl_8036E548[];
extern u8 lbl_3_data_1146C[];
extern void fn_80034E20(void*, void*, void*);
extern u8* lbl_803CC1B8;
extern void* (*lbl_3_data_11390[])(void*);
extern u8 lbl_803C6CF8[];
extern u8 lbl_3_data_11380[];
extern s32 lbl_3_data_17000[];
extern f32 lbl_3_rodata_1EC4;
extern f64 sin(f64);
extern f64 cos(f64);
extern s32 lbl_3_data_170D8[];
extern f32 lbl_3_rodata_1EC0;
extern f32 lbl_3_rodata_1E68;
extern s32 ARAMTransfer(void*, int, int, int);
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void fn_8006C43C(int);
extern void fn_8006C3F0(int);
extern void fn_8003A688(f32, f32);

extern void fn_3_BDF74(void);

extern void fn_3_C39C8(void);
extern void fn_3_CE8E4(void);
extern void fn_3_F8ABC(void);
#include "static/UnknownHomes_Static.h"

extern s16 lbl_3_bss_9952;

void fn_3_C0770(void) {
    pitchingMachinePitching(0x10);
    lbl_3_bss_9952 = 0;
}

extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_3_data_12354[];
extern f32 lbl_3_rodata_1F18;
extern f32 lbl_3_rodata_1F1C;
extern f32 lbl_3_rodata_1F20;
extern f32 lbl_3_rodata_1E64;
extern u8 g_Ball[];
extern u8 g_Pitcher[];
extern void fn_3_15BAA0(int);
extern void minigamesSetSomePointers(void);
extern void fn_3_C0854(void);
extern void fn_3_CABB4(void);

extern u8 lbl_3_bss_995C;

void fn_3_C07A0(void) {
    lbl_3_bss_995C = 3;
}

extern int fn_80033928(int);
extern void* fn_80033A24(void*, int, int, int, int, int);

void fn_3_C07B0(void) {
    if (fn_80033928(0x10) != 0 || fn_80033A24(fn_3_C0134, 0x80, 0, 0, 0, 0x10) != NULL) {
        lbl_3_bss_995C = 0;
    }
}

// .text:0x000BA538 size:0x2BC mapped:0x806F95CC
void fn_3_BA538(void) {
    return;
}

// .text:0x000BA7F4 size:0x888 mapped:0x806F9888
void fn_3_BA7F4(void) {
    return;
}

// .text:0x000BB07C size:0xE0 mapped:0x806FA110
void fn_3_BB07C(f32* out, f32 deg) {
    f32 s;
    f32 a;
    f32 c;
    a = lbl_3_rodata_1EC0 * deg;
    s = sin(a);
    c = cos(a);
    out[4] = (s * (f32)lbl_3_data_170D8[1]) / 100000.0f;
    out[5] = (c * (f32)lbl_3_data_170D8[1]) / 100000.0f;
    out[6] = 0.0f;
}

// .text:0x000BB15C size:0x2F8 mapped:0x806FA1F0
void fn_3_BB15C(void) {
    return;
}

// .text:0x000BB454 size:0x3A0 mapped:0x806FA4E8
void fn_3_BB454(void) {
    return;
}

// .text:0x000BB7F4 size:0x3D0 mapped:0x806FA888
void fn_3_BB7F4(void) {
    return;
}

// .text:0x000BBBC4 size:0x3D0 mapped:0x806FAC58
void fn_3_BBBC4(void) {
    return;
}

// .text:0x000BBF94 size:0x290 mapped:0x806FB028
void fn_3_BBF94(void) {
    return;
}

// .text:0x000BC224 size:0x38 mapped:0x806FB2B8
void fn_3_BC224(void) {
    fn_80034CEC(*(void**)lbl_3_common_bss_35154);
    *(u32*)lbl_3_common_bss_35154 = 0;
}

// .text:0x000BC25C size:0x18 mapped:0x806FB2F0
void fn_3_BC25C(void) {
    *(u32*)(lbl_3_common_bss_35154 + 0x3AC) |= 0x40;
}

// .text:0x000BC274 size:0x68 mapped:0x806FB308
s32 fn_3_BC274(u8* a, u8* b, u8* c) {
    return (*(f32*)(b + 4) - *(f32*)(c + 4)) < (f32)lbl_3_data_17000[*(s8*)(a + 0x252)] / lbl_3_rodata_1EC4;
}

// .text:0x000BC2DC size:0x3FC mapped:0x806FB370
void fn_3_BC2DC(void) {
    return;
}

// .text:0x000BC6D8 size:0x178 mapped:0x806FB76C
void fn_3_BC6D8(void) {
    return;
}

// .text:0x000BC850 size:0x38 mapped:0x806FB8E4
void fn_3_BC850(int a, int i) {
    ((void (*)(int, f32, f32))fn_8003A688)(a, lbl_3_data_111C8[i].x, lbl_3_data_111C8[i].y);
}

// .text:0x000BC888 size:0x198 mapped:0x806FB91C
void fn_3_BC888(void) {
    return;
}

// .text:0x000BCA20 size:0x7B4 mapped:0x806FBAB4
void fn_3_BCA20(void) {
    return;
}

// .text:0x000BD1D4 size:0x4 mapped:0x806FC268
void fn_3_BD1D4(void) {
    return;
}

// .text:0x000BD1D8 size:0x25C mapped:0x806FC26C
void fn_3_BD1D8(void) {
    return;
}

// .text:0x000BD434 size:0xBC mapped:0x806FC4C8
typedef struct { f32 x, y, z; u8 pad; u8 pad1; u8 e; u8 pad2; } BD434E;
typedef struct { u8 pad[0x3B8]; BD434E* p; f32 x, y, z; s32 c8; s32 cc; f32 d0, d4, d8, dc; u8 e0; } BD434S;
#define G (*(BD434S*)lbl_3_common_bss_35154)
void fn_3_BD434(int a, int b) {
    int n;
    G.p = (BD434E*)(lbl_3_data_12354 + (a + b * 7) * 0xA0);
    G.cc = 0x1518;
    G.c8 = 0;
    G.d0 = lbl_3_rodata_1F18;
    G.d4 = lbl_3_rodata_1F1C;
    G.d8 = lbl_3_rodata_1E64;
    for (n = 0; G.p[n].e < 4; n++) {
    }
    G.e0 = 1;
    G.x = G.p[n].x;
    G.y = G.p[n].y;
    G.z = G.p[n].z;
    G.dc = lbl_3_rodata_1F20;
}

// .text:0x000BD4F0 size:0x14 mapped:0x806FC584

void fn_3_BD4F0(void) {
    lbl_3_common_bss_35154[0x466] = 0;
}

// .text:0x000BD504 size:0x1A8 mapped:0x806FC598
void fn_3_BD504(void) {
    return;
}

// .text:0x000BD6AC size:0xAC mapped:0x806FC740
void fn_3_BD6AC(int a, f32 x, f32 y, f32 z) {
    u8* c = lbl_3_common_bss_35154;
    int v;
    c[0x466] = 1;
    *(f32*)(c + 0x440) = x;
    *(f32*)(c + 0x444) = y;
    *(f32*)(c + 0x448) = z;
    *(s16*)(c + 0x464) = 0;
    if (a != 0) {
        v = g_Ball[0x1BE7];
        switch (v) {
        case 0xB:
        case 0xC:
            fn_3_15BAA0(v == 0xC);
            break;
        }
    } else {
        v = g_Pitcher[0x165];
        switch (v) {
        case 0xB:
        case 0xC:
            fn_3_15BAA0(v == 0xC);
            break;
        }
    }
}

// .text:0x000BD758 size:0x78 mapped:0x806FC7EC
void fn_3_BD758(void) {
    u8* q = lbl_803CC1B8;
    void* r;
    if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
        lbl_3_common_bss_35154[0x418] = 0;
        r = lbl_3_data_11390[*(u16*)(q + 0x14)](*(void**)(lbl_3_common_bss_35154 + *(u16*)(q + 0x16) * 4 + 0x40C));
        fn_800B0A14_removeQueue(r);
    }
}

// .text:0x000BD7D0 size:0x8 mapped:0x806FC864
s32 fn_3_BD7D0(void) {
    return 1;
}

// .text:0x000BD7D8 size:0x4 mapped:0x806FC86C
void fn_3_BD7D8(void) {
    return;
}

// .text:0x000BD7DC size:0x30 mapped:0x806FC870
void fn_3_BD7DC(u32 a) {
    fn_800BD670(*(void**)(lbl_8036E548 + 0x70), a);
}

// .text:0x000BD80C size:0xCC mapped:0x806FC8A0
void fn_3_BD80C(void) {
    return;
}

// .text:0x000BD8D8 size:0x24 mapped:0x806FC96C
void fn_3_BD8D8(void) {
    *(void**)(lbl_8036E548 + 0x3070) = fn_3_BD80C;
    *(void**)(lbl_8036E548 + 0x3074) = fn_3_BD7DC;
}

// .text:0x000BD8FC size:0x3A8 mapped:0x806FC990
void fn_3_BD8FC(void) {
    return;
}

// .text:0x000BDCA4 size:0x170 mapped:0x806FCD38
void fn_3_BDCA4(void) {
    return;
}

// .text:0x000BDE14 size:0x160 mapped:0x806FCEA8
extern const f32 lbl_3_rodata_1F38;
extern const f32 lbl_3_rodata_1EB0;
extern const f64 lbl_3_rodata_1F40;
extern int rand(void);
extern void* memcpy(void*, const void*, u32);
extern BOOL getAnimRelatedCoordinates(int, int, void*);
extern u8 lbl_3_data_A3C[];
extern u8 lbl_3_data_11620[];
typedef struct { u8 pad[0x4C]; V2f pts[0x60]; V2f pts2[0x60]; } BDE14T;
void fn_3_BDE14(void) {
    u8* q;
    BDE14T* p;
    int i;
    f32 a;
    q = fn_800B0A5C_insertQueue(fn_3_BDCA4, 3);
    getAnimRelatedCoordinates(0, 7, q + 0x14);
    *(s32*)(q + 0x20) = lbl_3_data_A3C[1] - 2;
    *(BDE14T**)(q + 0x24) = p = (BDE14T*)lbl_3_data_11620;
    for (i = 0; i < 0x60; i++) {
        a = (lbl_3_rodata_1F38 * (f32)rand()) / lbl_3_rodata_1EB0;
        p->pts[i].x = lbl_3_rodata_1F40 * cos(a);
        p->pts[i].y = lbl_3_rodata_1F40 * sin(a);
    }
    memcpy(lbl_3_data_11620 + 0x398, lbl_3_data_11620 + 0x4C, 0x300);
}

// .text:0x000BDF74 size:0x1CC mapped:0x806FD008
void fn_3_BDF74(void) {
    return;
}

// .text:0x000BE140 size:0x34 mapped:0x806FD1D4
void fn_3_BE140(void) {
    u8* p = fn_800B0A5C_insertQueue(fn_3_BDF74, 3);
    *(s16*)(p + 0x10) = 2;
}

// .text:0x000BE174 size:0x60 mapped:0x806FD208
void fn_3_BE174(s32 a, f32 x, f32 y, f32 z) {
    *(f32*)(lbl_3_common_bss_35154 + 0x41C) = x;
    *(u32*)(lbl_3_common_bss_35154 + 0x3AC) |= 1;
    *(f32*)(lbl_3_common_bss_35154 + 0x420) = y;
    *(f32*)(lbl_3_common_bss_35154 + 0x424) = z;
    lbl_3_common_bss_35154[0x419] = a;
    if (a == 4) {
        u8* p = fn_800B0A5C_insertQueue(fn_3_BDF74, 3);
        *(s16*)(p + 0x10) = 2;
    }
}

// .text:0x000BE1D4 size:0xE24 mapped:0x806FD268
void fn_3_BE1D4(void) {
    return;
}

// .text:0x000BEFF8 size:0x78 mapped:0x806FE08C
void fn_3_BEFF8(void) {
    u8* q = lbl_803CC1B8;
    *(u8**)lbl_3_common_bss_35154 = q;
    fn_80034E20(q, lbl_3_data_1146C, lbl_3_common_bss_35154);
    *(s16*)(q + 0x18) = 0;
    *(void**)lbl_803CC1B8 = fn_3_BE1D4;
    *(u32*)(lbl_3_common_bss_35154 + 0x3AC) = 0;
}

// .text:0x000BF070 size:0xE8 mapped:0x806FE104
void fn_3_BF070(void) {
    return;
}

// .text:0x000BF158 size:0x54 mapped:0x806FE1EC
void fn_3_BF158(void) {
    u8 v = g_d_GameSettings.StadiumID;
    if (v == 1) {
        fn_3_C39C8();
    } else if (v == 2) {
        fn_3_CE8E4();
    } else if (v == 4) {
        fn_3_F8ABC();
    }
}

// .text:0x000BF1AC size:0x60 mapped:0x806FE240
#pragma opt_unroll_loops off
void fn_3_BF1AC(void) {
    int i;
    u8* p;
    minigamesSetSomePointers();
    fn_3_C0854();
    fn_3_CABB4();
    p = lbl_8036E548 + 0x1DD0;
    i = 12;
    do {
        *(u32*)(p + 0xC60) = 0;
        p -= 0x27C;
    } while (i-- != 0);
    lbl_3_common_bss_35154[0x479] = 1;
}
#pragma opt_unroll_loops reset

// .text:0x000BF20C size:0x2C mapped:0x806FE2A0
void fn_3_BF20C(void) {
    fn_8006C43C(0);
    fn_8006C3F0(0);
}

// .text:0x000BF238 size:0x488 mapped:0x806FE2CC
void fn_3_BF238(void) {
    return;
}

// .text:0x000BF6C0 size:0x1B8 mapped:0x806FE754
void fn_3_BF6C0(void) {
    return;
}

// .text:0x000BF878 size:0x80 mapped:0x806FE90C
int fn_3_BF878(void) {
    if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
        *(s32*)(lbl_3_common_bss_35154 + 8) = ARAMTransfer(lbl_3_data_11380, 0, 0, 0);
        fn_800B0A5C_insertQueue(fn_3_BF6C0, 0);
        lbl_3_common_bss_35154[0x3B0] = 1;
        return 1;
    }
    return 0;
}

// .text:0x000BF8F8 size:0x244 mapped:0x806FE98C
void fn_3_BF8F8(void) {
    return;
}

// .text:0x000BFB3C size:0x268 mapped:0x806FEBD0
void fn_3_BFB3C(void) {
    return;
}

// .text:0x000BFDA4 size:0x390 mapped:0x806FEE38
void fn_3_BFDA4(void) {
    return;
}

// .text:0x000C0134 size:0x63C mapped:0x806FF1C8
void fn_3_C0134(void) {
    return;
}

