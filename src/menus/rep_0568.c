#include "menus/rep_0568.h"

#include <string.h>
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
extern u8 lbl_8036E548[];
extern u8 lbl_2_bss_100B8[];

extern u8 lbl_8036E548[];
extern u8 lbl_2_bss_100B8[];
extern u8* lbl_2_bss_1224;
extern u8* lbl_2_bss_122C;
extern u8* lbl_2_data_2780[];
extern void* _OSAllocFromHeap(s32, s32);
typedef struct {
    u8* p;
    u8 pad[0x5C];
    s8 a;
    s8 b;
    u8 pad2[2];
} Ent64;
extern Ent64 lbl_2_bss_101AC[];
extern void fn_2_18398(void);
extern void fn_2_188EC(void);
extern const f32 lbl_2_rodata_5BC;
extern const f32 lbl_2_rodata_5D4;
extern const f32 lbl_2_rodata_5D8;
extern const f32 lbl_2_rodata_5DC;
extern const f32 lbl_2_rodata_5E0;
extern const f32 lbl_2_rodata_5E4;
extern const f32 lbl_2_rodata_5E8;
extern void fn_800BDA94(void*, s32);
extern u8 lbl_8034E9A0[];
extern u8* lbl_803CBBCC[];
extern u8 lbl_803C6CF8[];
extern u8 lbl_803C66B0[];
extern u8 lbl_2_bss_100B4[];
extern u8 lbl_2_data_241C[];
extern s32 ARAMTransfer(void*, int, int, int);
extern void fn_2_16F78(u8);
extern void fn_2_14BB8(u8, s32);

#include "static/UnknownHomes_Static.h"


// fn_2_190B8, size:0x24
void fn_2_190B8(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_2_16CE0, size:0x58
void fn_2_16CE0(void) {
    u8* resource;
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        resource = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
        if (resource != NULL && *(s16*)(resource + 0x62) == 0x6B) {
            lbl_2_bss_100B8[i + 0x40] = 1;
        }
    }
}

// fn_2_16D38, size:0x70
void fn_2_16D38(void) {
    s32 i;
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        memset(*(void**)(lbl_8036E548 + i * 0x27C + 0xC0C), 0, 0x5C);
    }
}

// fn_2_18650, size:0xF8
s32 fn_2_18650(s32 a) {
    s32 next = (*(s8*)&lbl_2_bss_100B8[0] + 1) % 10;
    if (next != *(s8*)&lbl_2_bss_100B8[1]) {
        if (lbl_2_bss_1224 == NULL) {
            lbl_2_bss_1224 = fn_800B0A5C_insertQueue(fn_2_18398, 0xFFFF);
            if (lbl_2_bss_1224 != NULL) {
                lbl_2_bss_1224[0x1C] = 0;
                lbl_2_bss_1224[0x1D] = 0;
            } else {
                return 0;
            }
        }
        lbl_2_bss_100B8[*(s8*)&lbl_2_bss_100B8[0] + 2] = a;
        lbl_2_bss_100B8[0] = next;
        lbl_2_bss_100B8[a + 0x42] = 1;
        return 1;
    }
    return 0;
}

// fn_2_18FBC, size:0xFC
void fn_2_18FBC(void) {
    u8* q;
    s32 i;
    q = fn_800B0A5C_insertQueue(fn_2_188EC, 0x6000);
    lbl_2_bss_100B8[0x19] = 0;
    lbl_2_bss_100B8[0x1B] = 1;
    if (lbl_8034E9A0[0x4701] == 0) {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            ((s8*)lbl_2_bss_100B8)[i + 0x27] = -1;
        }
        q[0x1C] = 0;
    } else {
        for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
            lbl_2_bss_100B8[i + 0x14] = 0;
        }
        q[0x1C] = 0;
    }
    lbl_2_bss_100B8[0] = i = 0;
    lbl_2_bss_100B8[1] = 0;
    for (; i < 10; i++) {
        ((s8*)lbl_2_bss_100B8)[i + 2] = -1;
    }
}

// fn_2_1937C, size:0x140
void fn_2_1937C(u16* a, s32 b) {
    Mtx44 m;
    u16 i;
    f32 fx;
    f32 fy;
    u8* e;
    u8* c;
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (i = 0; i < *a; i++) {
        e = *(u8**)(lbl_8036E548 + i * 4 + 0x2C50);
        if (e != NULL) {
            c = (u8*)a + i * 0x90 + 0x34;
            if (*(u32*)c != 0 && c[0x6C] != 0) {
                fx = *(f32*)(e + 0x34) / lbl_2_rodata_5D4;
                fy = *(f32*)(e + 0x38) / lbl_2_rodata_5D4;
                C_MTXFrustum(m, lbl_2_rodata_5D8 + fy, lbl_2_rodata_5DC + fy, lbl_2_rodata_5E0 + fx, lbl_2_rodata_5E4 + fx, lbl_2_rodata_5BC, lbl_2_rodata_5E8);
                GXSetProjection(m, GX_PERSPECTIVE);
                fn_800BDA94(c, b);
            }
        }
    }
}

// fn_2_17AB8, size:0x1D0
void fn_2_17AB8(void) {
    s32 size;
    s32 i;
    size = ((*(u32*)(lbl_2_data_2780[0] + 4) & 0x0FFFFFFF) + 0x1F) & ~0x1F;
    lbl_2_bss_122C = _OSAllocFromHeap(0x20, size * lbl_2_bss_100B8[0x2D]);
    for (i = 0; i < lbl_2_bss_100B8[0x2D]; i++) {
        lbl_2_bss_101AC[i].p = lbl_2_bss_122C + size * i;
        lbl_2_bss_101AC[i].b = -1;
        lbl_2_bss_101AC[i].a = -1;
    }
}

// fn_2_18148, size:0x250
void fn_2_18148(u8* q) {
    u8 gf;
    switch (q[0x21]) {
    case 0:
        *(u8**)(q + 0x14) = lbl_8036E548 + q[0x1E] * 0x27C + 0xC04;
        (*(u8**)(q + 0x14))[0x252] = q[q[0x1E] + 0x18];
        q[0x20] = lbl_2_bss_100B8[q[0x1E] + 0x46];
        lbl_8036E548[q[0x1E] * 0x27C + 0xE61] = 0;
        *(s16*)(*(u8**)(q + 0x14) + 0x68) = -1;
        lbl_2_bss_100B4[1] = 1;
        q[0x21] = q[0x21] + 1;
        break;
    case 1:
        ARAMTransfer(lbl_2_data_241C + (s8)q[q[0x1E] + 0x18] * 0x10, *(s32*)(*(u8**)(q + 0x14) + 8), 0, 0);
        q[0x21] = q[0x21] + 1;
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            fn_2_16F78(q[0x1E]);
            gf = *((u8*)&g_d_GameSettings + 0x10);
            if (gf == 0 && lbl_803C66B0[0x59] == 0 && q[0x1E] == 1) {
                lbl_8036E548[q[0x1E] * 0x27C + 0xE61] = 0;
            } else {
                lbl_8036E548[q[0x1E] * 0x27C + 0xE61] = (q[0x20] != 0);
            }
            if (g_d_GameSettings.GameModeSelected == 5 || gf != 0 || *(u16*)(lbl_803CBBCC[0] + 6) == 5) {
                fn_2_14BB8(q[0x1E], 1);
            } else if (lbl_2_bss_100B8[0x10] != 0) {
                fn_2_14BB8(q[0x1E], q[0x1E] != 0);
            }
            q[0x21] = 0;
            lbl_2_bss_100B8[0x32] = 1;
            lbl_2_bss_100B4[1] = 0;
            lbl_2_bss_100B8[0x18] = 1;
            lbl_2_bss_100B8[q[0x1E] + 0x42] = 0;
        }
        break;
    }
}
