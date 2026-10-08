#include "game/rep_1E08.h"
#include "header_rep_data.h"
#include "Dolphin/GX.h"
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
extern const f32 lbl_3_rodata_1EC4;
extern f64 sin(f64);
extern f64 cos(f64);
extern s32 lbl_3_data_170D8[];
extern f32 lbl_3_rodata_1EC0;
extern const f32 lbl_3_rodata_1E68;
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
extern void fn_800BD548(void*, int, ...);
extern void fn_800BD8C4(void*, u32);
extern void CTRLSetTranslation(void*, f32, f32, f32);
extern void CTRLSetRotation(void*, f32, f32, f32);
extern u8 lbl_80366158[];
extern u8 lbl_3_data_12354[];
extern f32 lbl_3_rodata_1F18;
extern f32 lbl_3_rodata_1F1C;
extern f32 lbl_3_rodata_1F20;
extern const f32 lbl_3_rodata_1E64;
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
extern void CTRLBuildMatrix(void*, Mtx);
extern const f32 lbl_3_rodata_1E6C;
extern const f32 lbl_3_rodata_1E70;
extern const f32 lbl_3_rodata_1E74;
extern const f32 lbl_3_rodata_1E78;
extern const f32 lbl_3_rodata_1E7C;
extern const f32 lbl_3_rodata_1E80;
extern const f32 lbl_3_rodata_1E88;
extern const f32 lbl_3_rodata_1E84;
void fn_3_BA538(u8* p) {
    u8 ctrl[0x50];
    f32 q[12];
    Mtx m;
    Mtx44 proj;
    f32 hw;
    f32 hh;
    f32 tx;
    f32 ux;
    f32 uy;
    f32 ty;
    f32 sc;
    s32 i;
    hw = *(f32*)(p + 0x38) * lbl_3_rodata_1E64;
    hh = *(f32*)(p + 0x3C) * lbl_3_rodata_1E64;
    ctrl[0] = 0;
    q[3] = hw;
    q[6] = hw;
    q[0] = -hw;
    q[1] = -hh;
    q[4] = -hh;
    q[7] = hh;
    q[9] = -hw;
    q[10] = hh;
    q[11] = 0.0f;
    q[8] = 0.0f;
    q[5] = 0.0f;
    q[2] = 0.0f;
    CTRLSetRotation(ctrl, *(f32*)(p + 0x1C), *(f32*)(p + 0x20), *(f32*)(p + 0x24));
    sc = *(f32*)(p + 0xC);
    tx = lbl_3_rodata_1E64 * *(f32*)(p + 4);
    ty = 0.35f * *(f32*)(p + 8);
    ux = tx * lbl_3_rodata_1E64;
    uy = ty * lbl_3_rodata_1E64;
    CTRLSetTranslation(ctrl, ux * sc, uy * sc, lbl_3_rodata_1E70);
    CTRLBuildMatrix(ctrl, m);
    GXLoadPosMtxImm(m, 0);
    GXSetCurrentMtx(0);
    C_MTXOrtho(proj, lbl_3_rodata_1E74 * *(f32*)(p + 0xC), lbl_3_rodata_1E78 * *(f32*)(p + 0xC),
               lbl_3_rodata_1E7C * *(f32*)(p + 0xC), lbl_3_rodata_1E80 * *(f32*)(p + 0xC), lbl_3_rodata_1E84,
               lbl_3_rodata_1E88);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(q[i * 3], q[i * 3 + 1], q[i * 3 + 2]);
        GXColor1u32(*(u32*)(p + 0x40));
    }
    GXSetCullMode(GX_CULL_FRONT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(q[i * 3], q[i * 3 + 1], q[i * 3 + 2]);
        GXColor1u32(*(u32*)(p + 0x44));
    }
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
extern int rand(void);
extern const f32 lbl_3_rodata_1EB0;
extern const f32 lbl_3_rodata_1EC8;
extern const f32 lbl_3_rodata_1E84;
extern const f32 lbl_3_rodata_1E98;
void fn_3_BB15C(u8* p) {
    s32 lo;
    u8 lo8;
    f32 sc;
    f32 r;
    f32 sn;
    f32 cs;
    s32 range;
    f32 ang;
    ang = 0.0f;
    lo8 = lbl_3_data_170D8[5];
    lo = lbl_3_data_170D8[5];
    *(f32*)(p + 4) = (f32)(*(s16*)(p + 0x4A) * 2) / (f32)lbl_3_data_170D8[0] - lbl_3_rodata_1E84;
    *(f32*)(p + 8) = lbl_3_rodata_1E98;
    r = (f32)rand() / lbl_3_rodata_1EB0;
    *(f32*)(p + 0xC) = 50.0f * r + 50.0f;
    sn = sin(ang);
    cs = cos(ang);
    *(f32*)(p + 0x10) = (sn * (f32)lbl_3_data_170D8[1]) / lbl_3_rodata_1EC4;
    *(f32*)(p + 0x14) = (cs * (f32)lbl_3_data_170D8[1]) / lbl_3_rodata_1EC4;
    *(f32*)(p + 0x18) = 0.0f;
    *(f32*)(p + 0x24) = 0.0f;
    *(f32*)(p + 0x20) = 0.0f;
    *(f32*)(p + 0x1C) = 0.0f;
    sc = (f32)lbl_3_data_170D8[2] / lbl_3_rodata_1EC4;
    *(f32*)(p + 0x28) = sc * ((f32)rand() / lbl_3_rodata_1EB0);
    *(f32*)(p + 0x2C) = sc * ((f32)rand() / lbl_3_rodata_1EB0);
    *(f32*)(p + 0x30) = sc * ((f32)rand() / lbl_3_rodata_1EB0);
    p[0x47] = 0xFF;
    p[0x43] = 0xFF;
    p[0x41] = lo8 + rand() % (range = (u8)(0xFF - lo));
    p[0x42] = lo8 + rand() % range;
    p[0x44] = lo8 + rand() % range;
    p[0x45] = lo8 + rand() % range;
    p[0x46] = lo8 + rand() % range;
}


// .text:0x000BB454 size:0x3A0 mapped:0x806FA4E8
void fn_3_BB454(u8* a) {
    u8* p;
    u32 i;
    s32 t;
    p = *(u8**)(a + 0xC);
    i = 0;
    do {
        *(s16*)(p + 0x4A) = i;
        *(f32*)(p + 0x38) = (f32)lbl_3_data_170D8[3] / lbl_3_rodata_1EC4;
        *(f32*)(p + 0x3C) = (f32)lbl_3_data_170D8[4] / lbl_3_rodata_1EC4;
        fn_3_BB15C(p);
        t = lbl_3_data_170D8[0] / 5;
        *(s16*)(p + 0x48) = ((i % 5) * t + rand() % t) * 2;
        i++;
        p = *(u8**)p;
    } while (p != NULL);
}

// .text:0x000BB7F4 size:0x3D0 mapped:0x806FA888
void fn_3_BB7F4(void) {
    u8* t = fn_80033A24(fn_3_BA7F4, 0x80, 0, lbl_3_data_170D8[0], 1, 0x19);
    if (t != NULL) {
        fn_3_BB454(t);
    }
}

// .text:0x000BBBC4 size:0x3D0 mapped:0x806FAC58
void fn_3_BBBC4(void) {
    u8* t = fn_80033A24(fn_3_BA7F4, 0x80, 0, lbl_3_data_170D8[0], 1, 0x19);
    if (t != NULL) {
        fn_3_BB454(t);
    }
}

// .text:0x000BBF94 size:0x290 mapped:0x806FB028
extern u8 g_GameLogic[];
extern void fn_3_15FB84(u8, ...);
extern void fn_3_169150(void);
extern void fn_3_CB3AC(void);
extern void fn_3_168CD8(void);
extern void fn_3_16892C(void);
extern int fn_8004ABE8(int);
extern int fn_8004ABE0(void);
extern void playSoundEffect(int);
extern f32 lbl_3_bss_9964;
extern f32 lbl_3_data_12CB4;
extern const f32 lbl_3_rodata_1E68;
extern void fn_8003A550(s32, Vec*, Vec*, s32);
extern BOOL getAnimRelatedCoordinates(int, int, void*);
// 99%: loop pointer init emits addi r0; mr r30,r0 (known open pattern); jumptable reloc name differs
void fn_3_BBF94(void) {
    Mtx m;
    Vec v;
    Vec c;
    u8* gl = g_GameLogic;
    s32 i;
    s32 k;
    u8** p;
    u8* o;
    u8 st = gl[0x11E];
    switch (st) {
        case 0:
        case 3:
        case 4:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 15:
        case 16:
        case 17:
        case 18:
        case 24:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
            lbl_3_common_bss_35154[0x479] = 1;
            break;
    }
    if (st < 0x1B) {
        fn_3_BC2DC();
    }
    if (gl[0x11E] == 1 || (u8)(gl[0x11E] - 2) <= 1 || (u8)(gl[0x11E] - 0x13) <= 1 ||
        gl[0x11E] == 0x16 || gl[0x11E] == 0x17) {
        for (i = 0, p = (u8**)lbl_8036E548; i < 13; i++, p++) {
            o = p[0x2C50 / 4];
            if (o != NULL) {
                if (o[0x25D] == 0) {
                    o[0x279] = 0;
                } else {
                    PSMTXRotRad(m, 'Y', *(f32*)(o + 0x44));
                    v.x = lbl_3_bss_9964;
                    v.y = lbl_3_rodata_1E68;
                    v.z = lbl_3_data_12CB4;
                    PSMTXMultVec(m, &v, &v);
                    k = o[0x276] & 0x14;
                    if (k == 0x10 && (o[0x275] & 0x7F) == 6) {
                        getAnimRelatedCoordinates(i, 0x22, &c);
                        c.y = 0.0f;
                        fn_8003A550(i, &c, &v, !o[0x25A]);
                    }
                    o[0x279] = (k == 4);
                    k = o[0x276] & 0xA;
                    if (k == 8 && (o[0x275] & 0x7F) == 6) {
                        getAnimRelatedCoordinates(i, 0x1E, &c);
                        c.y = 0.0f;
                        fn_8003A550(i, &c, &v, o[0x25A]);
                    }
                    o[0x279] |= (k == 2) << 1;
                }
            }
        }
    }
    if (lbl_3_common_bss_35154[0x470] != 0) {
        fn_3_15FB84(lbl_3_common_bss_35154[0x472], lbl_3_common_bss_35154[0x473], lbl_3_common_bss_35154[0x474],
                    lbl_3_common_bss_35154[0x475], lbl_3_common_bss_35154[0x476]);
    }
    fn_3_169150();
    fn_8006C43C((int)fn_3_168CD8);
    fn_8006C3F0((int)fn_3_16892C);
    if (fn_8004ABE8(1) != 0) {
        fn_3_CB3AC();
        if (fn_8004ABE0() != 0) {
            playSoundEffect(0x1B6);
        }
    }
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
#pragma dont_inline on
void fn_3_BC2DC(void) {
    return;
}
#pragma dont_inline reset

// .text:0x000BC6D8 size:0x178 mapped:0x806FB76C
extern s32 lbl_3_bss_9968;
extern s32 g_UNK_StadiumDetails[];
extern int rand(void);
extern void fn_3_90064(int);
extern void fn_80028628(int, int, void*, int, void*, void*, int);
static u8 s_BF070a[8] = {0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0};
static u8 s_BF070b[8][3] = {{0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x5C, 0x40, 0x16}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}, {0x0, 0x0, 0x0}};
static V2f s_BF070c[0x36] = {{1.2f, 1.2f}, {1.2f, 1.2f}, {1.5f, 1.5f}, {0.6f, 0.6f}, {0.5f, 0.5f}, {0.5f, 0.5f}, {1.4f, 1.4f}, {0.5f, 0.5f}, {0.5f, 0.5f}, {1.5f, 1.5f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.0f, 1.0f}, {1.2f, 1.2f}, {1.3f, 1.3f}, {1.3f, 1.3f}, {1.0f, 1.0f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.0f, 1.0f}, {1.4f, 1.4f}, {0.7f, 0.7f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.3f, 1.3f}, {1.3f, 1.3f}, {1.3f, 1.3f}, {1.3f, 1.3f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}, {1.2f, 1.2f}};
static u8 s_BF070e[0x274] = {1};
static u8 s_BF070f[0x5864] = {1};
static s32 s_BC6D8_a[14] = {1};
static s32 s_BC6D8_b[14] = {1};
static u8 s_BC6D8_pad1[0xC] = {1};
static u32 s_BC6D8_c[14] = {1};
static s32 s_BC6D8_d[16] = {1};
static u8 s_BC6D8_pad2[0x20] = {1};
static s32 s_BC6D8_e[18] = {1};
static s32 s_BC6D8_f[1] = {1};
// 99%: only the null-test compare differs (original cmplwi, the switch form that gives the right beq/b shape emits cmpwi)
void fn_3_BC6D8(int a, int b, int idx, int c) {
    s32 old = s_BC6D8_e[3];
    u32 p;
    s_BC6D8_e[0] = g_UNK_StadiumDetails[1];
    s_BC6D8_f[0] = g_UNK_StadiumDetails[1];
    s_BC6D8_e[3] = (s32)((f32)old * ((f32)s_BC6D8_b[idx % 14] / lbl_3_rodata_1EC4));
    p = s_BC6D8_c[idx];
    switch (p) { case 0: p = (u32)&s_BC6D8_d[lbl_3_bss_9968 & 0xF]; break; }
    fn_80028628(a, b, s_BC6D8_e, s_BC6D8_a[idx % 14], (void*)p, s_BC6D8_f, c);
    lbl_3_bss_9968 += rand();
    s_BC6D8_e[3] = old;
    if (idx == 13) {
        fn_3_90064(0x2D9);
    } else if (idx >= 4 && idx <= 7) {
        fn_3_90064(0x2D7);
    } else {
        fn_3_90064(0x2D8);
    }
}

// .text:0x000BC850 size:0x38 mapped:0x806FB8E4
void fn_3_BC850(int a, int i) {
    ((void (*)(int, f32, f32))fn_8003A688)(a, lbl_3_data_111C8[i].x, lbl_3_data_111C8[i].y);
}

// .text:0x000BC888 size:0x198 mapped:0x806FB91C
extern f32 lbl_3_bss_9964;
extern f32 lbl_3_data_12CB4;
extern void fn_8003A550(s32, Vec*, Vec*, s32);
extern BOOL getAnimRelatedCoordinates(int, int, void*);
void fn_3_BC888(void) {
    Mtx m;
    Vec c;
    Vec v;
    u8* o;
    s32 i;
    s32 k;
    for (i = 0; i < 13; i++) {
        o = ((u8**)lbl_8036E548)[i + 0x2C50 / 4];
        if (o != NULL) {
            if (o[0x25D] == 0) {
                o[0x279] = 0;
            } else {
                PSMTXRotRad(m, 'Y', *(f32*)(o + 0x44));
                v.x = lbl_3_bss_9964;
                v.y = lbl_3_rodata_1E68;
                v.z = lbl_3_data_12CB4;
                PSMTXMultVec(m, &v, &v);
                k = o[0x276] & 0x14;
                if (k == 0x10 && (o[0x275] & 0x7F) == 6) {
                    getAnimRelatedCoordinates(i, 0x22, &c);
                    c.y = 0.0f;
                    fn_8003A550(i, &c, &v, !o[0x25A]);
                }
                o[0x279] = (k == 4);
                k = o[0x276] & 0xA;
                if (k == 8 && (o[0x275] & 0x7F) == 6) {
                    getAnimRelatedCoordinates(i, 0x1E, &c);
                    c.y = 0.0f;
                    fn_8003A550(i, &c, &v, o[0x25A]);
                }
                o[0x279] |= (k == 2) << 1;
            }
        }
    }
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
extern const f32 lbl_3_rodata_1E84;
extern const f32 lbl_3_rodata_1E98;
extern f32 lbl_3_rodata_1EE0;
extern f32 lbl_3_rodata_1F10;
extern f32 lbl_3_rodata_1EE4;
extern f32 lbl_3_rodata_1F14;
extern f32 lbl_3_rodata_1EFC;
extern Vec lbl_3_bss_9978[];
extern Vec lbl_3_bss_996C;
extern u8 fn_3_8D4(void*, void*);
extern void* memcpy(void*, const void*, u32);
// 81%: stack layout (orig sp8,sp14,sp2C,sp38 + 0x10 spare) and float-reg order of the 4-way box test not matched
void fn_3_BD1D8(f32 (*m)[4]) {
    Vec sp38;
    Vec sp2C;
    struct { Vec a, b; } sp14;
    Vec sp8;
    f32 zoom;
    u8 hit;
    f32 z;
    f32 xr;
    f32 yr;
    f32 top, bottom, right, left;
    zoom = lbl_3_rodata_1E84 / fn_80052768_getCamera(0)->zoom;
    *(u32*)(lbl_3_common_bss_35154 + 0x3C8) =
        (*(u32*)(lbl_3_common_bss_35154 + 0x3C8) + 1) % *(u32*)(lbl_3_common_bss_35154 + 0x3CC);
    PSVECScale((Vec*)(lbl_3_common_bss_35154 + 0x3BC), lbl_3_rodata_1E84, &sp8);
    PSMTXMultVec(m, &sp8, lbl_3_bss_9978);
    z = lbl_3_bss_9978[0].z;
    if (z <= lbl_3_rodata_1E98) {
        hit = 0;
        xr = ((lbl_3_rodata_1EE0 * z) * lbl_3_rodata_1E64) / lbl_3_rodata_1EE4 * zoom;
        yr = ((lbl_3_rodata_1F10 * z) * lbl_3_rodata_1E64) / lbl_3_rodata_1EE4 * zoom;
        top = lbl_3_rodata_1F14 + lbl_3_bss_9978[0].y;
        bottom = lbl_3_bss_9978[0].y - lbl_3_rodata_1F14;
        right = lbl_3_rodata_1F14 + lbl_3_bss_9978[0].x;
        left = lbl_3_bss_9978[0].x - lbl_3_rodata_1F14;
        if (yr < top && bottom < -yr && xr > left && right > -xr) {
            hit = 1;
        }
        lbl_3_common_bss_35154[0x3E1] = hit;
        if (hit) {
            lbl_3_bss_996C.x = lbl_3_rodata_1EFC * -lbl_3_bss_9978[0].x;
            lbl_3_bss_996C.y = lbl_3_rodata_1EFC * -lbl_3_bss_9978[0].y;
            lbl_3_bss_996C.z = lbl_3_rodata_1E68;
            if (*(s16*)((u8*)g_UNK_StadiumDetails + 0x77C) != 0) {
                memcpy(&sp2C, &fn_80052768_getCamera(0)->eye, 0xC);
                memcpy(&sp38, lbl_3_common_bss_35154 + 0x3BC, 0xC);
                lbl_3_common_bss_35154[0x3E2] = fn_3_8D4(&sp2C, &sp14);
                if (lbl_3_common_bss_35154[0x3E2] == 0) {
                    memcpy(&sp38, &fn_80052768_getCamera(0)->eye, 0xC);
                    memcpy(&sp2C, lbl_3_common_bss_35154 + 0x3BC, 0xC);
                    lbl_3_common_bss_35154[0x3E2] = fn_3_8D4(&sp2C, &sp14);
                }
            }
        }
    } else {
        lbl_3_common_bss_35154[0x3E1] = 0;
    }
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
extern void* memcpy(void*, const void*, u32);
extern void fn_3_CB538(s32 mode);
extern void fn_3_15B79C(int flag);
extern void fn_3_15F574(void);
extern void fn_3_160814(s32 a);
void fn_3_BD504(int a, f32 x, f32 y, f32 z) {
    int v;
    if (lbl_80366158[0x28] == 0) {
        memcpy(lbl_3_common_bss_35154 + 0x44C, lbl_3_common_bss_35154 + 0x440, 0xC);
        *(f32*)(lbl_3_common_bss_35154 + 0x440) = x;
        *(f32*)(lbl_3_common_bss_35154 + 0x444) = y;
        *(f32*)(lbl_3_common_bss_35154 + 0x448) = z;
    }
    if (lbl_3_common_bss_35154[0x466] != 0) {
        if (a != 0) {
            v = g_Ball[0x1BE7];
            switch (v) {
            case 1:
            case 2:
                fn_3_CB538(v);
                break;
            case 7:
            case 8:
                fn_3_15F574();
                break;
            case 3:
            case 4:
                fn_3_160814(v);
                break;
            case 11:
            case 12:
                break;
            }
        } else {
            v = g_Pitcher[0x165];
            switch (v) {
            case 1:
            case 2:
                fn_3_CB538(v);
                break;
            case 7:
            case 8:
                fn_3_15F574();
                break;
            case 0xB:
            case 0xC:
                fn_3_15B79C(v == 0xC);
                break;
            }
        }
        if (lbl_80366158[0x28] == 0) {
            *(s16*)(lbl_3_common_bss_35154 + 0x464) += 1;
        }
    }
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
// 97%: compiler folds base+0x3E4 into offsets off one reg; original keeps bss base in r5 and c=r5+0x3e4 in r30
void fn_3_BD80C(u32 a) {
    f32* c;
    u8* g;
    u8* bs = lbl_3_common_bss_35154;
    c = (f32*)(bs + 0x3E4);
    g = lbl_8036E548;
    if (bs[0x40A] != 0) {
        CTRLSetTranslation(*(u8**)(g + 0x70) + 0x44, c[1], c[2], c[3]);
        CTRLSetRotation(*(u8**)(g + 0x70) + 0x44, 57.295776f * c[4], 57.295776f * c[5], 57.295776f * c[6]);
        fn_800BD548(*(u8**)(g + 0x70) + 0x34, 4, *(s32*)(g + 0xAC), *(s32*)(g + 0xB0), *(s32*)(g + 0xB4), *(s32*)(g + 0xB8));
    }
    fn_800BD8C4(*(void**)(g + 0x70), a);
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
extern u8 lbl_803CBBC0;
extern const f32 lbl_3_rodata_1E84;
extern u8 lbl_80366158[];
extern void fn_800A7D4C(int, void*);
typedef struct { u8 pad[8]; Mtx m; f32 x, y, z; s32 n; f32 s; u8 pad2[0x34C - 0x4C]; } BDCA4E;
void fn_3_BDCA4(void) {
    u8* o = lbl_803CC1B8;
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154[0x479] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    *(s32*)(o + 0x20) -= (lbl_80366158[0x28] != 2);
    (*(BDCA4E**)(o + 0x24))[lbl_803CBBC0].s = lbl_3_rodata_1E84 / fn_80052768_getCamera(0)->zoom;
    (*(BDCA4E**)(o + 0x24))[lbl_803CBBC0].x = *(f32*)(o + 0x14);
    (*(BDCA4E**)(o + 0x24))[lbl_803CBBC0].y = *(f32*)(o + 0x18);
    (*(BDCA4E**)(o + 0x24))[lbl_803CBBC0].z = *(f32*)(o + 0x1C);
    (*(BDCA4E**)(o + 0x24))[lbl_803CBBC0].n = *(s32*)(o + 0x20);
    PSMTXCopy(*(Mtx*)((u8*)fn_80052768_getCamera(0) + 0x40), (*(BDCA4E**)(o + 0x24))[lbl_803CBBC0].m);
    fn_800A7D4C(0, &(*(BDCA4E**)(o + 0x24))[lbl_803CBBC0]);
    if (*(s32*)(o + 0x20) == 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x000BDE14 size:0x160 mapped:0x806FCEA8
extern const f32 lbl_3_rodata_1F38;
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
typedef struct { u8 pad[0x6E4]; V2f pts[0x60]; } BDF74T;
void fn_3_BDF74(void) {
    u8* o = lbl_803CC1B8;
    BDF74T* p;
    int i;
    f32 a;
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154[0x479] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (*(s16*)(o + 0x10) != 0) {
        *(s16*)(o + 0x10) -= 1;
        return;
    }
    *(f32*)(o + 0x14) = *(f32*)(g_Ball + 0x354);
    *(f32*)(o + 0x18) = -*(f32*)(g_Ball + 0x358);
    *(f32*)(o + 0x1C) = *(f32*)(g_Ball + 0x35C);
    *(s32*)(o + 0x20) = lbl_3_data_A3C[1] - 2;
    p = (BDF74T*)lbl_3_data_11620;
    *(u8**)(o + 0x24) = lbl_3_data_11620 + 0x698;
    for (i = 0; i < 0x60; i++) {
        a = (lbl_3_rodata_1F38 * (f32)rand()) / lbl_3_rodata_1EB0;
        p->pts[i].x = lbl_3_rodata_1F40 * cos(a);
        p->pts[i].y = lbl_3_rodata_1F40 * sin(a);
    }
    memcpy(lbl_3_data_11620 + 0xA30, lbl_3_data_11620 + 0x6E4, 0x300);
    *(void**)((u8**)&lbl_803CC1B8)[0] = fn_3_BDCA4;
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
extern u8 lbl_3_data_111A8[];
extern void fn_8003A85C(u8);
extern void fn_8003A848(u8, u8, u8);
extern void fn_8003A6B0(s32, void*, f32, f32);
void fn_3_BF070(void) {
    u8* w;
    s32 i;
    fn_8003A85C(s_BF070a[g_d_GameSettings.StadiumID]);
    fn_8003A848(s_BF070b[g_d_GameSettings.StadiumID][0], s_BF070b[g_d_GameSettings.StadiumID][1], s_BF070b[g_d_GameSettings.StadiumID][2]);
    w = *(u8**)(*(u8**)(lbl_3_common_bss_35154 + 8) + 0x18);
    lbl_3_common_bss_35154[0x3B1] = 1;
    for (i = 0; i < 13; i++) {
        u8* o = ((u8**)lbl_8036E548)[i + 0x2C50 / 4];
        if (o != NULL) {
            fn_8003A6B0(i, w + 4, s_BF070c[*(s8*)(o + 0x252)].x, s_BF070c[*(s8*)(o + 0x252)].y);
        } else {
            fn_8003A6B0(i, w + 4, s_BF070c[0].x, s_BF070c[0].y);
        }
    }
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
extern void fn_3_B9D68(void*, int, void*, void*);
extern void fn_8004B1B8(s32, void*);
extern void fn_80035750(s32, s32, int);
extern void* ActorObjectInitTable(int);
extern void fn_800BDC88(void*, int, int, s32, int, int);
extern void fn_3_6750C(s32);
void fn_3_BF6C0(void) {
    s32 buf[8];
    u8* c;
    u8* t;
    u8* w;
    s32 i;
    if (*(s8*)(lbl_803C6CF8 + 0x715) == 1) {
        fn_3_B9D68(s_BF070e, 6, *(void**)(lbl_3_common_bss_35154 + 8), buf);
        c = lbl_3_common_bss_35154;
        *(s32*)(lbl_3_common_bss_35154 + 4) = **(s32**)(c + 8);
        fn_8004B1B8(**(s32**)(c + 8), *(void**)(c + 8));
        fn_80035750(*(s32*)(*(u8**)(c + 8) + 4), *(s32*)(*(u8**)(c + 8) + 8), 4);
        t = ActorObjectInitTable(1);
        *(void**)(lbl_8036E548 + 0x70) = t;
        fn_800BDC88(t, 0, 0, ((s32*)*(u8**)(c + 8))[buf[4]], 0, 0);
        fn_8003A85C(s_BF070a[g_d_GameSettings.StadiumID]);
        fn_8003A848(s_BF070b[g_d_GameSettings.StadiumID][0], s_BF070b[g_d_GameSettings.StadiumID][1], s_BF070b[g_d_GameSettings.StadiumID][2]);
        w = *(u8**)(*(u8**)(c + 8) + 0x18);
        lbl_3_common_bss_35154[0x3B1] = 1;
        for (i = 0; i < 13; i++) {
            u8* o = ((u8**)lbl_8036E548)[i + 0x2C50 / 4];
            if (o != NULL) {
                fn_8003A6B0(i, w + 4, s_BF070c[*(s8*)(o + 0x252)].x, s_BF070c[*(s8*)(o + 0x252)].y);
            } else {
                fn_8003A6B0(i, w + 4, s_BF070c[0].x, s_BF070c[0].y);
            }
        }
        fn_3_6750C(*(s32*)(lbl_3_common_bss_35154 + 4));
        *(s32*)(lbl_3_common_bss_35154 + 0xC) = ARAMTransfer(s_BF070f, 0, 0, 0);
        *(void**)lbl_803CC1B8 = fn_3_BF238;
    }
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
extern u16 lbl_800F7860[];
extern f32 lbl_3_rodata_1EF8;
extern void fn_80033B58(void*, s32, s32, s32);
extern void* memset(void*, int, u32);
// 95%: x/y of the quad are read via lfsx (reg+reg) in the original and the e-based loads are not CSE'd with them
void fn_3_BF8F8(u8* a, f32 (*in)[4], f32* pos, f32 (*cb)(u8*, s32, f32 (*)[4], f32)) {
    Mtx cur;
    Mtx inv;
    f32 quad[12];
    Vec tmp;
    u8* b;
    f32 k;
    u32 col;
    s32 j;
    f32 x;
    f32 y;
    s32 off;
    s32 alpha;
    s32 i;
    if (cb == NULL) {
        cb = fn_3_BFB3C;
    }
    PSMTXInverse(in, inv);
    inv[0][3] = lbl_3_rodata_1E68;
    inv[1][3] = lbl_3_rodata_1E68;
    inv[2][3] = lbl_3_rodata_1E68;
    memset(quad, 0, 0x30);
    i = 0;
    k = lbl_3_rodata_1EF8;
    off = 0;
    for (; i < *(s32*)(a + 8); off += 0x44, i++) {
        b = *(u8**)a;
        alpha = (s32)(k * cb(b + off, (s32) * (f32*)(a + 0x10), cur, *(f32*)(a + 0x14)));
        if ((u8)alpha != 0) {
            u8* e;
            b = *(u8**)a;
            e = (u8*)((u32)b + off);
            x = *(f32*)(b + off);
            y = *(f32*)(b + (off + 4));
            quad[0] = x;
            quad[1] = y;
            quad[3] = *(f32*)e + *(f32*)(e + 8);
            quad[4] = y;
            quad[6] = quad[3];
            quad[7] = *(f32*)(e + 4) + *(f32*)(e + 0xC);
            quad[9] = x;
            quad[10] = quad[7];
            PSMTXConcat(inv, cur, cur);
            e = *(u8**)a + off;
            fn_80033B58(((void**)*(u8**)(a + 4))[*(u16*)(e + 0x10)], *(u16*)(e + 0x12), 0, 0);
            GXBegin(0x80, 0, 4);
            col = 0xFFFFFF00;
            col = (col & ~0xFF) | (alpha & 0xFF);
            for (j = 0; j < 4; j++) {
                PSMTXMultVec(cur, (Vec*)&quad[j * 3], &tmp);
                GXPosition3f32(pos[0] + tmp.x, pos[1] + tmp.y, pos[2] + tmp.z);
                GXColor1u32(col);
                GXTexCoord2f32((f32)lbl_800F7860[j * 2], (f32)lbl_800F7860[j * 2 + 1]);
            }
        }
    }
}

// .text:0x000BFB3C size:0x268 mapped:0x806FEBD0
f32 fn_3_BFB3C(u8* e, s32 x, f32 (*m)[4], f32 t) {
    Mtx tmp;
    f32 r;
    PSMTXIdentity(m);
    PSMTXIdentity(tmp);
#define BFB3C_CH(k) fn_3_BFDA4(*(void**)(e + 0x14 + (k) * 4), t, e[0x34 + (k)], x, e[0x3C + (k)], e + 0x3C + (k))
    m[0][0] = *(u32*)(e + 0x14) ? BFB3C_CH(0) : lbl_3_rodata_1E84;
    m[1][1] = *(u32*)(e + 0x18) ? BFB3C_CH(1) : lbl_3_rodata_1E84;
    r = *(u32*)(e + 0x2C) ? BFB3C_CH(6) : lbl_3_rodata_1E68;
    if (r != lbl_3_rodata_1E68) {
        PSMTXRotRad(tmp, 'Z', r);
        PSMTXConcat(tmp, m, m);
    }
    r = *(u32*)(e + 0x28) ? BFB3C_CH(5) : lbl_3_rodata_1E68;
    if (r != lbl_3_rodata_1E68) {
        PSMTXRotRad(tmp, 'Y', r);
        PSMTXConcat(tmp, m, m);
    }
    PSMTXIdentity(tmp);
    tmp[0][3] = *(u32*)(e + 0x1C) ? BFB3C_CH(2) : lbl_3_rodata_1E68;
    tmp[1][3] = *(u32*)(e + 0x20) ? BFB3C_CH(3) : lbl_3_rodata_1E68;
    tmp[2][3] = *(u32*)(e + 0x24) ? BFB3C_CH(4) : lbl_3_rodata_1E68;
    PSMTXConcat(tmp, m, m);
    return *(u32*)(e + 0x30) ? BFB3C_CH(7) : lbl_3_rodata_1E84;
#undef BFB3C_CH
}

// .text:0x000BFDA4 size:0x390 mapped:0x806FEE38
#pragma dont_inline on
f32 fn_3_BFDA4(void* p, f32 t, u8 a, s32 x, u8 b, u8* c) {
    return lbl_3_rodata_1E68;
}
#pragma dont_inline reset

// .text:0x000C0134 size:0x63C mapped:0x806FF1C8
void fn_3_C0134(void) {
    return;
}

