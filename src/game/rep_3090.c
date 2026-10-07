#include "game/rep_3090.h"
#include "header_rep_data.h"
#include "Dolphin/mtxext.h"

extern u8 lbl_80366158[];
extern Vec lbl_3_data_21004;
extern Vec lbl_3_data_20FF8;
extern Vec lbl_3_data_20FEC;

extern u8* lbl_3_common_bss_DE94;
extern u8* g_pCamera;
extern f32 fn_3_9FEA8(f32);
extern f64 cos(f64);
extern f64 sin(f64);
extern u32 lbl_3_rodata_30EC[];
extern u8 g_Camera[];
extern s16 lbl_3_bss_B67A;
extern void* memset(void*, s32, u32);
extern void* memcpy(void*, const void*, u32);
extern f32 lbl_3_rodata_30FC;
extern const f32 lbl_3_rodata_30F8;
extern const f32 lbl_3_rodata_3158;
extern const f32 lbl_3_rodata_315C;
extern u8 lbl_8036E548[];
extern void** fn_800111D8(void*);
extern void fn_800B2C44(void*, u16, Vec*);
extern u8* lbl_803CC1B8;
extern u8 g_Fielders[];
extern u8 LoadModel(void*);
extern void fn_800B0A14_removeQueue(void*);
#pragma dont_inline on

// .text:0x000FC448 size:0x4F0 mapped:0x8073B4DC
void fn_3_FC448(void) {
    return;
}

// .text:0x000FC938 size:0x500 mapped:0x8073B9CC
void fn_3_FC938(void) {
    return;
}

// .text:0x000FCE38 size:0x74 mapped:0x8073BECC
void fn_3_FCE38(void) {
    return;
}

// .text:0x000FCEAC size:0x4 mapped:0x8073BF40
void fn_3_FCEAC(void) {
    return;
}

// .text:0x000FCEB0 size:0x70 mapped:0x8073BF44
void fn_3_FCEB0(void) {
    return;
}

// .text:0x000FCF20 size:0x4 mapped:0x8073BFB4
void fn_3_FCF20(void) {
    return;
}

// .text:0x000FCF24 size:0x4E4 mapped:0x8073BFB8
void fn_3_FCF24(void) {
    return;
}

// .text:0x000FD408 size:0xD4 mapped:0x8073C49C
typedef struct { Vec pos; f32 u; f32 v; u8 pad[0x2C]; } PathPt;
void fn_3_FD408(u32 i, void* out, f32* uv) {
    u8* d = lbl_3_common_bss_DE94;
    if (*(u32*)(d + 0x3C) > i) {
        memcpy(out, &(*(PathPt**)(d + 0x34))[i], 12);
        uv[0] = (*(PathPt**)(d + 0x34))[i].u;
        uv[1] = (*(PathPt**)(d + 0x34))[i].v;
    } else {
        memcpy(out, &(*(PathPt**)(d + 0x34))[*(u32*)(d + 0x3C) - 1], 12);
        uv[0] = (*(PathPt**)(d + 0x34))[*(u32*)(d + 0x3C) - 1].u;
        uv[1] = (*(PathPt**)(d + 0x34))[*(u32*)(d + 0x3C) - 1].v;
    }
}

// .text:0x000FD4DC size:0x40 mapped:0x8073C570
void fn_3_FD4DC(void) {
    u8* p = lbl_3_common_bss_DE94;
    if ((*(u32*)(p + 0x118) >> 16) == 0) {
        *(u32*)(p + 0x20) = *(u32*)(p + 0x124);
    }
    fn_3_FCF24();
}

// .text:0x000FD51C size:0x8C mapped:0x8073C5B0
typedef struct { u32 a, b, c; } V3U;

void fn_3_FD51C(s32 i) {
    u8* c = g_Camera + i * 0x9BC;
    u8* p;
    V3U v = *(V3U*)lbl_3_rodata_30EC;
    *(u32*)(c + 0x140) = 0;
    *(u32*)(c + 0x144) = 0;
    p = c + 0x13C;
    *(V3U*)(p + 0xC) = v;
    *(u32*)(p + 0x1C) = 0;
    *(u32*)(p + 0x20) = 0;
    *(u32*)(p + 0x24) = 0;
    *(u32*)(p + 0x28) = 0;
    *(f32*)(p + 0x2C) = 0.0f;
    *(u32*)(p + 0x30) = 0;
    *(u32*)(p + 0x34) = 0;
    *(u32*)(p + 0x38) = 0;
    *(u32*)(p + 0x3C) = 0;
    *(u32*)(p + 0x40) = 0;
    *(f32*)(p + 0x44) = 0.0f;
}

// .text:0x000FD5A8 size:0xC8 mapped:0x8073C63C
void fn_3_FD5A8(void) {
    s32 i;
    V3U v = *(V3U*)lbl_3_rodata_30EC;
    for (i = 0; i < 2; i++) {
        u8* c = g_Camera + i * 0x9BC;
        u8* p;
        *(u32*)(c + 0x140) = 0;
        *(u32*)(c + 0x144) = 0;
        p = c + 0x13C;
        *(V3U*)(p + 0xC) = v;
        *(u32*)(p + 0x1C) = 0;
        *(u32*)(p + 0x20) = 0;
        *(u32*)(p + 0x24) = 0;
        *(u32*)(p + 0x28) = 0;
        *(f32*)(p + 0x2C) = 0.0f;
        *(u32*)(p + 0x30) = 0;
        *(u32*)(p + 0x34) = 0;
        *(u32*)(p + 0x38) = 0;
        *(u32*)(p + 0x3C) = 0;
        *(u32*)(p + 0x40) = 0;
        *(f32*)(p + 0x44) = 0.0f;
    }
}

// .text:0x000FD670 size:0x38C mapped:0x8073C704
void fn_3_FD670(void) {
    return;
}

// .text:0x000FD9FC size:0x20 mapped:0x8073CA90
s32 fn_3_FD9FC(void) {
    return *(s32*)(lbl_3_common_bss_DE94 + 0x18) == 1;
}

typedef struct { u8 pad[0x218]; u8 f; u8 pad2[0x268 - 0x219]; } FDA1CT;

// .text:0x000FDA1C size:0x114 mapped:0x8073CAB0
void fn_3_FDA1C(void) {
    u8* p = lbl_803CC1B8;
    u16 i;
    u8* model;

    switch (*(s16*)(p + 0x22)) {
    case 0:
        *(s16*)(p + 0x22) = 1;
        break;
    case 1:
        i = *(u16*)(p + 0x1E);
        model = ((u8**)(lbl_8036E548 + 0x2C50))[i];
        if (((FDA1CT*)g_Fielders)[i].f == 0) {
            if (i < 9) {
                *(u16*)(p + 0x1E) = i + 1;
                *(s16*)(p + 0x22) = 0;
            } else {
                *(s16*)(p + 0x22) = 2;
            }
        } else if (model == NULL || LoadModel(model)) {
            if (*(u16*)(p + 0x1E) < 9) {
                *(u16*)(p + 0x1E) = *(u16*)(p + 0x1E) + 1;
                *(s16*)(p + 0x22) = 0;
            } else {
                *(s16*)(p + 0x22) = 2;
            }
        }
        break;
    case 2:
        model = *(u8**)(p + 0xC);
        *(s16*)(model + 0x10) = 1;
        fn_800B0A14_removeQueue(model);
        *(s16*)(p + 0x22) = 0;
        break;
    }
}

// .text:0x000FDB30 size:0x24E8 mapped:0x8073CBC4
void fn_3_FDB30(void) {
    return;
}

// .text:0x00100018 size:0x20 mapped:0x8073F0AC

s32 fn_3_100018(void) {
    return *(u8*)(lbl_3_common_bss_DE94 + 0x9B6) == 1;
}

// .text:0x00100038 size:0x44 mapped:0x8073F0CC
void fn_3_100038(void) {
    if (*(u32*)(lbl_3_common_bss_DE94 + 0x118) > *(u32*)(lbl_3_common_bss_DE94 + 0x11C)) {
        if (lbl_3_common_bss_DE94[0x9B1] == 0) {
            *(u32*)(lbl_3_common_bss_DE94 + 0x118) = *(u32*)(lbl_3_common_bss_DE94 + 0x11C);
        } else {
            *(u32*)(lbl_3_common_bss_DE94 + 0x118) = 0;
        }
    } else {
        *(u32*)(lbl_3_common_bss_DE94 + 0x118) += 0x10000;
    }
}

// .text:0x0010007C size:0x5C mapped:0x8073F110
s32 fn_3_10007C(void) {
    u8* p = lbl_3_common_bss_DE94;
    if (p[0x9AB] == 1) {
        if (*(s32*)(p + 0x14) != 0) {
            lbl_80366158[0x28] = 1;
            return 0;
        }
        lbl_80366158[0x28] = 0;
        return 1;
    }
    return 1;
}

// .text:0x001000D8 size:0x1BEC mapped:0x8073F16C
void fn_3_1000D8(void) {
    return;
}

// .text:0x00101CC4 size:0x1F6C mapped:0x80740D58
void fn_3_101CC4(void) {
    return;
}

// .text:0x00103C30 size:0x24C mapped:0x80742CC4
void fn_3_103C30(void) {
    return;
}

// .text:0x00103E7C size:0x25C mapped:0x80742F10
void fn_3_103E7C(void) {
    return;
}

// .text:0x001040D8 size:0x260 mapped:0x8074316C
void fn_3_1040D8(void) {
    return;
}

// .text:0x00104338 size:0x270 mapped:0x807433CC
void fn_3_104338(void) {
    return;
}

// .text:0x001045A8 size:0x198 mapped:0x8074363C
#define CAMF(off) (*(f32*)(g_pCamera + (off)))
void fn_3_1045A8(void) {
    f32 sinPitch;
    f32 cosYaw;
    f32 yaw;
    f32 pitch;
    f32 dist;
    f32 sinYaw;
    f32 dx, dy, dz;

    pitch = fn_3_9FEA8(CAMF(0x2874));
    dist = 20.0f * (f32)cos(pitch);
    sinPitch = (f32)sin(pitch);
    yaw = fn_3_9FEA8(CAMF(0x2870));
    cosYaw = (f32)cos(yaw);
    sinYaw = (f32)sin(yaw);
    dx = cosYaw * dist;
    dy = 20.0f * sinPitch;
    dz = sinYaw * dist;
    CAMF(0x2858) += cosYaw * CAMF(0x287C);
    CAMF(0x2860) += sinYaw * CAMF(0x287C);
    CAMF(0x2858) += sinYaw * CAMF(0x2880);
    CAMF(0x2860) -= cosYaw * CAMF(0x2880);
    CAMF(0x284C) = dx + CAMF(0x2858);
    CAMF(0x2850) = dy + CAMF(0x285C);
    CAMF(0x2854) = dz + CAMF(0x2860);
    CAMF(0x2840) = CAMF(0x2858);
    CAMF(0x2844) = CAMF(0x285C);
    CAMF(0x2848) = CAMF(0x2860);
    CAMF(0x287C) = 0.0f;
    CAMF(0x2880) = 0.0f;
}

// .text:0x00104740 size:0x1A0 mapped:0x807437D4
#define DEF(off) (*(f32*)(lbl_3_common_bss_DE94 + (off)))
void fn_3_104740(void) {
    if (lbl_3_common_bss_DE94[0x9A7] == 2) {
        DEF(0xC4) = lbl_3_rodata_3158 + CAMF(0x284C);
        DEF(0xC8) = lbl_3_rodata_3158 + CAMF(0x2850);
        DEF(0xCC) = lbl_3_rodata_3158 + CAMF(0x2854);
        DEF(0xD0) = lbl_3_rodata_315C + CAMF(0x284C);
        DEF(0xD4) = lbl_3_rodata_315C + CAMF(0x2850);
        DEF(0xD8) = lbl_3_rodata_315C + CAMF(0x2854);
    } else {
        DEF(0xC4) = lbl_3_rodata_3158 + CAMF(0x2870);
        DEF(0xC8) = lbl_3_rodata_3158 + CAMF(0x2874);
        DEF(0xCC) = lbl_3_rodata_30F8;
        DEF(0xD0) = lbl_3_rodata_3158 + CAMF(0x2870);
        DEF(0xD4) = lbl_3_rodata_3158 + CAMF(0x2874);
        DEF(0xD8) = lbl_3_rodata_30F8;
    }
    DEF(0xAC) = CAMF(0x2840);
    DEF(0xB0) = CAMF(0x2844);
    DEF(0xB4) = CAMF(0x2848);
    DEF(0xB8) = lbl_3_rodata_3158 + CAMF(0x2840);
    DEF(0xBC) = lbl_3_rodata_3158 + CAMF(0x2844);
    DEF(0xC0) = lbl_3_rodata_3158 + CAMF(0x2848);
}

// .text:0x001048E0 size:0x15C mapped:0x80743974
void fn_3_1048E0(void) {
    return;
}

// .text:0x00104A3C size:0x4C mapped:0x80743AD0
void fn_3_104A3C(void* dst, void* mtx) {
    PSMTX44MultVec(mtx, &lbl_3_data_21004, dst);
    PSVECNormalize(dst, dst);
}

// .text:0x00104A88 size:0x4C mapped:0x80743B1C
void fn_3_104A88(void* dst, void* mtx) {
    PSMTX44MultVec(mtx, &lbl_3_data_20FF8, dst);
    PSVECNormalize(dst, dst);
}

// .text:0x00104AD4 size:0x4C mapped:0x80743B68
void fn_3_104AD4(void* dst, void* mtx) {
    PSMTX44MultVec(mtx, &lbl_3_data_20FEC, dst);
    PSVECNormalize(dst, dst);
}

// .text:0x00104B20 size:0x1C mapped:0x80743BB4
void fn_3_104B20(void) {
    return;
}

// .text:0x00104B3C size:0x990 mapped:0x80743BD0
void fn_3_104B3C(void) {
    return;
}

// .text:0x001054CC size:0x4 mapped:0x80744560
void fn_3_1054CC(void) {
    return;
}

// .text:0x001054D0 size:0x540 mapped:0x80744564
void fn_3_1054D0(void) {
    return;
}

// .text:0x00105A10 size:0xBC mapped:0x80744AA4
void fn_3_105A10(f32* out, f32* a, f32* b, f32 t) {
    Quaternion r;
    Quaternion va;
    Quaternion vb;
    memcpy(&va, a, 12);
    memcpy(&vb, b, 12);
    r.x = va.x * t + vb.x * (lbl_3_rodata_30FC - t);
    r.y = va.y * t + vb.y * (lbl_3_rodata_30FC - t);
    r.z = va.z * t + vb.z * (lbl_3_rodata_30FC - t);
    memcpy(out, &r, 12);
}

// .text:0x00105ACC size:0x10C mapped:0x80744B60
void fn_3_105ACC(void) {
    return;
}

// .text:0x00105BD8 size:0x50 mapped:0x80744C6C
void fn_3_105BD8(u8* p) {
    f32 v;
    memset(p, 0, 0x88);
    v = lbl_3_rodata_30FC;
    *(f32*)(p + 0x3C) = v;
    *(f32*)(p + 0x28) = v;
    *(f32*)(p + 0x14) = v;
    *(f32*)(p + 0x00) = v;
    *(f32*)(p + 0x40) = v;
}

// .text:0x00105C28 size:0x5C mapped:0x80744CBC
u32 fn_3_105C28(u8* p, u32 key) {
    u32 hi;
    u32 res;
    u16 n;
    u16* tbl;
    u16* e;
    u32 lo;
    u16* last;
    res = 0;
    hi = key >> 16;
    tbl = *(u16**)(p + 8);
    lo = (u16)key;
    n = tbl[0];
    e = tbl + 2;
    do {
        last = e;
        if (e[0] == hi && lo == 0) {
            res = e[1];
        }
        if (*(e += 2) > hi) break;
        n--;
    } while (n != 0);
    return res | (last[1] << 16);
}

// .text:0x00105C84 size:0x58 mapped:0x80744D18
void fn_3_105C84(u8* p) {
    u32* a = (u32*)(p + 8);
    u32* q;
    s16 i = 0;
    *a += (u32)p;
    q = a;
    for (; i < *(s16*)(p + 6); i++) {
        q[1] += (u32)p;
        q++;
    }
    *(u32*)(lbl_3_common_bss_DE94 + 0x11C) = *(u16*)(p + 4) << 16;
}

// .text:0x00105CDC size:0x124 mapped:0x80744D70
void fn_3_105CDC(void) {
    Vec* arr = *(Vec**)(lbl_3_common_bss_DE94 + 0x98);
    s32 i;
    for (i = 0; i < 1000; i++) {
        Vec* v = &arr[i];
        s32 x, z;
        if (-1000.0 == v->x || -1000.0 == v->y || -1000.0 == v->z) {
            continue;
        }
        x = (s32)v->x * 320 + 320;
        z = (s32)v->z * 224 + 224;
        if (i == 135) {
            i = 135;
        }
        if (i == 5) {
            i = 5;
        }
        fn_3_105E00(x / 50 + 150, -z / 50 + 400, 2, 2);
    }
}

// .text:0x00105E00 size:0x214 mapped:0x80744E94
void fn_3_105E00(s16 x, s16 y, s32 a, s32 b) {
    return;
}

// .text:0x00106014 size:0xC4 mapped:0x807450A8
void fn_3_106014(f32 x, f32 y, f32 z) {
    Vec* t = *(Vec**)(((u8**)&lbl_3_common_bss_DE94)[0] + 0x98);
    s16* n = &lbl_3_bss_B67A;
    s16 c;
    Vec* e;
    c = *n;
    if (c == 0) {
        t[*n].x = x;
        t[*n].y = y;
        t[*n].z = z;
        *n += 1;
        return;
    }
    e = (Vec*)((u8*)t + c * 0xC);
    if (x != e[-1].x && y != e[-1].y && z != e[-1].z) {
        t[c].x = x;
        t[*n].y = y;
        t[*n].z = z;
        if (*n < 1000) {
            *n += 1;
        }
    }
}

// .text:0x001060D8 size:0xA4 mapped:0x8074516C
void fn_3_1060D8(void) {
    u8* p = *(u8**)(((u8**)&lbl_3_common_bss_DE94)[0] + 0x98);
    s32 i;
    lbl_3_bss_B67A = 0;
    for (i = 0; i < 1000; i++) {
        *(f32*)(p + 0) = *(f32*)(p + 4) = *(f32*)(p + 8) = -1000.0f;
        p += 0xC;
    }
}

// .text:0x0010617C size:0xF4 mapped:0x80745210
s32 fn_3_10617C(s32 idx, s32 j, Vec* out) {
    u8* obj;
    Vec v;

    obj = ((u8**)(lbl_8036E548 + 0x2C50))[idx];
    if (obj == NULL) {
        return 0;
    }
    j = ((u16*)(obj + 0x162))[j];
    if (j == 0xFFFF) {
        out->x = 0.0f;
        out->y = 0.0f;
        out->z = 0.0f;
        return 0;
    }
    fn_800B2C44(*fn_800111D8(obj), j, &v);
    out->x = v.x;
    out->y = v.y;
    out->z = v.z;
    out->x += *(f32*)(obj + 0x34);
    out->y += *(f32*)(obj + 0x38);
    out->z += *(f32*)(obj + 0x3C);
    return 1;
}

// .text:0x00106270 size:0x71C mapped:0x80745304
void fn_3_106270(void) {
    return;
}

// .text:0x0010698C size:0x24 mapped:0x80745A20
s32 fn_3_10698C(u32* p) {
    s32 n = 0;
    while (*p != 0) {
        p++;
        n++;
    }
    return n;
}

// .text:0x001069B0 size:0x10 mapped:0x80745A44
void* fn_3_1069B0(s32* base, s32 idx) {
    return (u8*)base + base[idx];
}

// .text:0x001069C0 size:0x1E0 mapped:0x80745A54
void fn_3_1069C0(void) {
    return;
}

// .text:0x00106BA0 size:0x25C mapped:0x80745C34
void fn_3_106BA0(void) {
    return;
}

