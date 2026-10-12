#include "game/rep_2390.h"
#define REP_HEADER_FN repHeader_2390
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"

extern u8 lbl_8036E548[];
extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_80366158[];
extern s32 lbl_3_data_17DC0[240];
extern u16 lbl_3_data_6660[];
extern void fn_80030D88(Vec*, Vec*, void*, int);
extern void fn_80030470(Vec*, Vec*, Vec*, void*, int);

typedef struct {
    u32 w0, w4;
    u8 pad8[0x48];
} E2390;

typedef struct {
    u32 w0;
    u8 pad4[0x40];
} E18180;
// .data 0x00017DC0..0x00018268
s32 lbl_3_data_17DC0[240] = {
    0, 21, 5, 280000, 0, 0, 4, 2,
    120000, 90000, 0, 128, 1000000, 1000000, -500000, 500000,
    -256, 0, -28000, 1, 0, 7, 10, 78000,
    60000, 50000, 12, 6, 109000, 101000, 0, 40,
    4500000, 9500000, -1000000, 4500000, -256, 0, 0, 0,
    0, 4, 3, 90000, 100000, 10000, 20, 10,
    103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000,
    1010580480, 0, 0, 0, 0, 21, 5, 280000,
    0, 0, 4, 2, 120000, 90000, 0, 128,
    500000, 1000000, -500000, 500000, -256, 0, -28000, 1,
    0, 7, 10, 78000, 60000, 50000, 12, 6,
    109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000,
    -256, 0, 0, 0, 0, 4, 3, 90000,
    100000, 10000, 20, 10, 103000, 105999, 0, 60,
    10000000, 18000000, 1000000, -1000000, 1010580480, 0, 0, 0,
    0, 21, 5, 350000, 0, 0, 4, 2,
    120000, 90000, 0, 60, 500000, 1000000, -500000, 500000,
    -256, 0, -50000, 1, 0, 7, 10, 70000,
    80000, 50000, 20, 10, 109000, 110000, 0, 40,
    4500000, 9000000, -4500000, 4500000, -256, 0, 0, 0,
    0, 4, 5, 90000, 100000, 10000, 20, 10,
    103000, 105999, 0, 60, 10000000, 18000000, 4500000, -4500000,
    1010580480, 0, 0, 0, 0, 21, 3, 140000,
    0, 0, 16, 2, 120000, 90000, 0, 128,
    1000000, 1000000, -500000, 500000, -256, 0, -28000, 1,
    0, 7, 10, 39000, 30000, 50000, 12, 6,
    109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000,
    -256, 0, 0, 0, 0, 4, 3, 45000,
    50000, 10000, 20, 10, 103000, 105999, 0, 60,
    10000000, 18000000, 1000000, -1000000, 1010580480, 0, 0, 0,
};
E18180 lbl_3_data_18180[3] = {
    {
        0,
        {
            0, 0, 0, 20, 0, 0, 0, 8, 0, 0, 0, 7, 0, 3, 208, 144,
            0, 0, 195, 80, 0, 8, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 12, 0, 0, 0, 13, 0, 0, 0, 14, 0, 0, 0, 15,
            0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0, 18, 0, 0, 0, 19,
        },
    },
    {
        0,
        {
            0, 0, 0, 20, 0, 0, 0, 8, 0, 0, 0, 7, 0, 3, 208, 144,
            0, 0, 195, 80, 0, 8, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 12, 0, 0, 0, 13, 0, 0, 0, 14, 0, 0, 0, 15,
            0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0, 18, 0, 0, 0, 19,
        },
    },
    {
        0,
        {
            0, 0, 0, 20, 0, 0, 0, 8, 0, 0, 0, 7, 0, 4, 147, 224,
            0, 1, 134, 160, 0, 8, 100, 112, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 12, 0, 0, 0, 13, 0, 0, 0, 14, 0, 0, 0, 15,
            0, 0, 0, 16, 0, 0, 0, 17, 0, 0, 0, 18, 0, 0, 0, 19,
        },
    },
}; // WARNING: 0x1C bytes past the type are not zero: 00000000000000003f8000000000000000000000be4ccccd00000000 // NOTE: type size 0xCC != symbol size 0xE8
f32 lbl_3_data_1824C[7] = {0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -0.2f, 0.0f}; // unreferenced

// .text:0x000CB3AC size:0x18C mapped:0x8070A440
// WIP: orig keeps three pointer copies (base, base+0x320, base+0x2D0 = E[11],E[10],E[9] of stride 0x50) in r29/r30/r28 (mr then addi); we fold them into r31+offset.
void fn_3_CB3AC(void) {
    Vec sp8;
    u8* q = *(u8**)(lbl_8036E548 + 0x2C50);
    u8* g = ((u8*)lbl_3_data_17DC0);
    E2390* e;
    E2390* e1;
    E2390* e2;
    u16 anim;
    s32 i;
    u16* t;
    if (PSVECMag((Vec*)(g + 0x48C)) && q != 0) {
        e = (E2390*)g;
        e1 = e;
        e2 = e;
        e[11].w0 = *(u32*)(lbl_3_common_bss_35154 + 4);
        e1[10].w0 = *(u32*)(lbl_3_common_bss_35154 + 4);
        e2[9].w0 = *(u32*)(lbl_3_common_bss_35154 + 4);
        e2[9].w4 = 0x15;
        e1[10].w4 = 7;
        anim = 0x1A;
        if (q[0x25A] != 0) {
            i = 0;
            t = lbl_3_data_6660;
            do {
                if (t[0] == 0x1A) {
                    anim = lbl_3_data_6660[i * 2 + 1];
                    break;
                }
                if (t[1] == 0x1A) {
                    anim = lbl_3_data_6660[i * 2];
                    break;
                }
                t += 2;
                i++;
            } while (lbl_3_data_6660[i * 2] != 0xFFFF);
        }
        getAnimRelatedCoordinates(0, anim, (VecXYZ*)&sp8);
        PSVECAdd(&sp8, (Vec*)(g + 0x498), &sp8);
        if (lbl_80366158[0x28] == 0) {
            fn_80030D88(&sp8, (Vec*)(g + 0x48C), &e[10], 5);
            fn_80030D88(&sp8, (Vec*)(g + 0x48C), &e[11], 5);
            fn_80030470(&sp8, (Vec*)(g + 0x48C), (Vec*)(g + 0x48C), &e[9], 5);
        }
    }
}

extern E18180 lbl_3_data_18180[];
extern void fn_8002F5F4(Vec* pos, Vec* dir, void* prm); // prm: ParticleParams8*

// .text:0x000CB538 size:0x17C mapped:0x8070A5CC
// WIP: orig has mode in r28 and k/loop counter in r29 (we swap them); stwx vs add+stw for the 0x44-stride store; decl-order permutations of k/j/e/r28 tried.
void fn_3_CB538(s32 mode) {
    Vec d;
    Vec bv;
    Vec* p31;
    Vec* p30;
    s32 j;
    s32 k;
    u8* e;
    u8* r28;
    u32 v;
    u8* f;
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        k = 2;
    } else {
        k = g_Ball.framesSinceHit > 0;
    }
    p30 = (Vec*)(lbl_3_common_bss_35154 + 0x44C);
    p31 = (Vec*)(lbl_3_common_bss_35154 + 0x440);
    PSVECSubtract(p30, p31, &d);
    if (PSVECMag(&d)) {
        e = ((u8*)lbl_3_data_17DC0) + k * 0xF0;
        v = *(u32*)(lbl_3_common_bss_35154 + 4);
        *(u32*)(e + 0xA0) = v;
        *(u32*)(e + 0x50) = v;
        f = (u8*)lbl_3_data_18180 + k * 0x44;
        *(u32*)f = v;
        *(u32*)e = v;
        if (mode == 2) {
            *(u32*)(e + 4) = 0x1B;
            *(u32*)(e + 0x54) = 0x1C;
        } else {
            *(u32*)(e + 4) = 0x15;
            *(u32*)(e + 0x54) = 7;
        }
        fn_8002F5F4(p31, &d, f);
        if (lbl_80366158[0x28] == 0) {
            r28 = e + 0x50;
            j = 1;
            do {
                fn_80030D88(p31, &d, r28, 5);
                j++;
                r28 += 0x50;
            } while (j < 3);
            PSVECNormalize(&d, &d);
            PSVECSubtract(p31, p30, &bv);
            fn_80030470(p31, &d, &bv, e, 5);
        }
    }
}

