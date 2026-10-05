#include "game/rep_2390.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"

extern u8 lbl_8036E548[];
extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_80366158[];
extern u8 lbl_3_data_17DC0[];
extern u16 lbl_3_data_6660[];
extern void fn_80030D88(Vec*, Vec*, void*, int);
extern void fn_80030470(Vec*, Vec*, Vec*, void*, int);

typedef struct {
    u32 w0, w4;
    u8 pad8[0x48];
} E2390;

// .text:0x000CB3AC size:0x18C mapped:0x8070A440
// WIP: orig keeps three pointer copies (base, base+0x320, base+0x2D0 = E[11],E[10],E[9] of stride 0x50) in r29/r30/r28 (mr then addi); we fold them into r31+offset.
void fn_3_CB3AC(void) {
    Vec sp8;
    u8* q = *(u8**)(lbl_8036E548 + 0x2C50);
    u8* g = lbl_3_data_17DC0;
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

typedef struct {
    u32 w0;
    u8 pad4[0x40];
} E18180;
extern E18180 lbl_3_data_18180[];
extern void fn_8002F5F4(Vec*, Vec*);

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
        e = lbl_3_data_17DC0 + k * 0xF0;
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
        fn_8002F5F4(p31, &d);
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
