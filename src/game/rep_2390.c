#include "game/rep_2390.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "Dolphin/mtx.h"
#include "main/file_800263FC.h"
#include "main/file_80011640.h"

extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_80366158[];
extern u16 lbl_3_data_6660[];

// .data lbl_3_data_17DC0..18268: separate statics reached through one pooled base.
// Ball particle effects, three per ball state (pitch, hit, live ball, and a fourth set).
static ParticleParams5 lbl_3_data_17DC0[12] = {
    {NULL, 21, 5, 280000, 0, 0, 4, 2, 120000, 90000, 0, 128, 1000000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1},
    {NULL, 7, 10, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 3, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0},
    {NULL, 21, 5, 280000, 0, 0, 4, 2, 120000, 90000, 0, 128, 500000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1},
    {NULL, 7, 10, 78000, 60000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 3, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0},
    {NULL, 21, 5, 350000, 0, 0, 4, 2, 120000, 90000, 0, 60, 500000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -50000, 1},
    {NULL, 7, 10, 70000, 80000, 50000, 20, 10, 109000, 110000, 0, 40, 4500000, 9000000, -4500000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 5, 90000, 100000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 4500000, -4500000, 0x3C3C3C00, 0, 0, 0},
    {NULL, 21, 3, 140000, 0, 0, 16, 2, 120000, 90000, 0, 128, 1000000, 1000000, -500000, 500000, 0xFFFFFF00, 0, -28000, 1},
    {NULL, 7, 10, 39000, 30000, 50000, 12, 6, 109000, 101000, 0, 40, 4500000, 9500000, -1000000, 4500000, 0xFFFFFF00, 0, 0, 0},
    {NULL, 4, 3, 45000, 50000, 10000, 20, 10, 103000, 105999, 0, 60, 10000000, 18000000, 1000000, -1000000, 0x3C3C3C00, 0, 0, 0},
};
// Trail parameters (ParticleParams8 with 8 texture indices), one per ball state.
typedef struct {
    ParticleParams8 p;
    s32 texIndex2[7];
} ParticleParams8x8;
static ParticleParams8x8 lbl_3_data_18180[3] = {
    {{NULL, 20, 8, 7, 250000, 50000, 550000, 0, 0, {12}}, {13, 14, 15, 16, 17, 18, 19}},
    {{NULL, 20, 8, 7, 250000, 50000, 550000, 0, 0, {12}}, {13, 14, 15, 16, 17, 18, 19}},
    {{NULL, 20, 8, 7, 300000, 100000, 550000, 0, 0, {12}}, {13, 14, 15, 16, 17, 18, 19}},
};
static Vec lbl_3_data_1824C = {0.0f, 0.0f, 1.0f};  // emit direction
static Vec lbl_3_data_18258 = {0.0f, 0.0f, -0.2f}; // offset from the animation point
// lbl_3_data_18264: 4 zero bytes (padding)

// .text:0x000CB3AC size:0x18C mapped:0x8070A440
void fn_3_CB3AC(void) {
    Vec sp8;
    CharActor* q = lbl_8036E548.active[0];
    ParticleParams5* p10;
    ParticleParams5* p11;
    ParticleParams5* p9;
    u16* t;
    s32 i;
    u16 anim;
    if (PSVECMag(&lbl_3_data_1824C) && q != 0) {
        lbl_3_data_17DC0[11].tex = *(TexArchive**)(lbl_3_common_bss_35154 + 4);
        lbl_3_data_17DC0[10].tex = *(TexArchive**)(lbl_3_common_bss_35154 + 4);
        lbl_3_data_17DC0[9].tex = *(TexArchive**)(lbl_3_common_bss_35154 + 4);
        lbl_3_data_17DC0[9].texIndex = 0x15;
        lbl_3_data_17DC0[10].texIndex = 7;
        p10 = &lbl_3_data_17DC0[10];
        p11 = &lbl_3_data_17DC0[11];
        p9 = &lbl_3_data_17DC0[9];
        anim = 0x1A;
        if (q->_25A != 0) {
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
            } while (lbl_3_data_6660[++i * 2] != 0xFFFF);
        }
        getAnimRelatedCoordinates(0, anim, &sp8);
        PSVECAdd(&sp8, &lbl_3_data_18258, &sp8);
        if (lbl_80366158[0x28] == 0) {
            fn_80030D88(&sp8, &lbl_3_data_1824C, p10, 5);
            fn_80030D88(&sp8, &lbl_3_data_1824C, p11, 5);
            fn_80030470(&sp8, &lbl_3_data_1824C, &lbl_3_data_1824C, p9, 5);
        }
    }
}


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
        e = (u8*)lbl_3_data_17DC0 + k * 0xF0;
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
        fn_8002F5F4(p31, &d, (ParticleParams8*)f);
        if (lbl_80366158[0x28] == 0) {
            r28 = e + 0x50;
            j = 1;
            do {
                fn_80030D88(p31, &d, (ParticleParams5*)r28, 5);
                j++;
                r28 += 0x50;
            } while (j < 3);
            PSVECNormalize(&d, &d);
            PSVECSubtract(p31, p30, &bv);
            fn_80030470(p31, &d, &bv, (ParticleParams5*)e, 5);
        }
    }
}
