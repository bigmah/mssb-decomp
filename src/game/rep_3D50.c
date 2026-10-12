#include "game/rep_3D50.h"
#define REP_HEADER_FN repHeader_3D50
#include "header_rep_inline.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"
#include "main/scene_task.h"
#include "main/file_80008E00.h" // lbl_80366158
#include "game/rep_3CE0.h"       // FadeState

extern FadeState lbl_3_common_bss_35154;
extern SceneTask* lbl_803CC1B8;
BurstParams lbl_3_data_281F0[8] = {
    {0, {4, 3, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFF0000, 0, 50000, 20000}},
    {0, {4, 3, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFF0000, 0, 50000, 20000}},
    {0, {4, 12, 200000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFF0000, 0, 50000, 20000}},
    {0, {4, 1, 90000, 111000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xFFFF0000, 0, 50000, 20000}},
    {0, {4, 3, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xB559FF00, 0, 50000, 20000}},
    {0, {4, 3, 110000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xB559FF00, 0, 50000, 20000}},
    {0, {4, 12, 200000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xB559FF00, 0, 50000, 20000}},
    {0, {4, 1, 70000, 1000, 90000, 40, 1, 102000, 101000, 100, 10000000, 0xB559FF00, 0, 50000, 20000}},
};
s32 lbl_3_data_283F0[2][4] = {{10, 10, 10, 10}, {10, 10, 10, 1}};
s32 lbl_3_data_28410[2] = {40, 40};
// The garlic-burst scene task (fn_3_160578): a SceneTask with its own bytes at 0x14.
typedef struct {
    /*0x00*/ u8 pad[0x14]; // SceneTask head (main/scene_task.h)
    /*0x14*/ u8 f14; // nonzero: second burst set (lbl_3_data_281F0[4..7])
    /*0x15*/ u8 f15; // 0: waiting, 1: garlic just started, 2: running
    /*0x16*/ u8 f16; // delay reload
    /*0x17*/ u8 f17; // frames until the next burst
} Q3D50;
static Q3D50* lbl_3_bss_B9B8[10]; // only [0] is used
extern void* memcpy(void*, const void*, u32);
extern void fn_8002C2D0(Vec*, Vec*, void*);

// .text:0x00160814 size:0xDC mapped:0x8079F8A8
void fn_3_160814(s32 a) {
    Q3D50* q;
    u8 t;
    if (lbl_3_common_bss_35154._464 == 0) {
        q = fn_800B0A5C_insertQueue(fn_3_160578, (u16)(lbl_803CC1B8->priority + 1));
        lbl_3_bss_B9B8[0] = q;
        q->f14 = (a == 4);
        {int i = lbl_3_bss_B9B8[0]->f14; lbl_3_bss_B9B8[0]->f15 = 0; lbl_3_bss_B9B8[0]->f16 = lbl_3_data_283F0[i][0];}
        lbl_3_bss_B9B8[0]->f17 = 0;
        t = lbl_3_bss_B9B8[0]->f14;
        lbl_3_common_bss_35154.garlicFrames[t != 0] = lbl_3_data_28410[t];
    }
}

// .text:0x00160578 size:0x29C mapped:0x8079F60C
void fn_3_160578(void) {
    Vec d;
    Vec bv;
    Q3D50* q = (Q3D50*)lbl_803CC1B8;
    s32 k;
    Vec* p29;
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.disabled != 0) {
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (lbl_3_common_bss_35154._466 == 0) {
        lbl_3_bss_B9B8[0] = 0;
        REMOVE_QUEUE_NOARG();
        return;
    }
    if (lbl_80366158._28 == 0) {
        if (q->f15 == 0 && g_Ball.warioWaluGarlicIsActive != 0) {
            q->f15 = 1;
            q->f17 = 0;
        }
        if (q->f17 != 0) {
            q->f17 = q->f17 - 1;
            return;
        }
        if (q->f15 == 0) {
            k = (u32)g_GameLogic.bOD_framesInLiveBallScene >> 31 ^ 1;
        } else if (q->f15 == 1) {
            k = 2;
            q->f15 = 2;
        } else {
            k = 3;
        }
        if (q->f14 != 0) {
            k += 4;
        }
        p29 = &lbl_3_common_bss_35154._440;
        PSVECSubtract(&lbl_3_common_bss_35154._44C, p29, &bv);
        if (PSVECMag(&bv)) {
            lbl_3_data_281F0[k].file = lbl_3_common_bss_35154.effectFile;
            fn_8002C2D0(p29, &bv, &lbl_3_data_281F0[k]);
        }
        d.x = g_Ball.warioStarHitCoords[2].x;
        d.y = -g_Ball.warioStarHitCoords[2].y;
        d.z = g_Ball.warioStarHitCoords[2].z;
        if (k % 4 == 3) {
            PSVECSubtract(&lbl_3_common_bss_35154._458, &d, &bv);
            if (PSVECMag(&bv)) {
                if (g_Ball.framesUntilBallHitsGround == lbl_3_common_bss_35154.garlicFrames[q->f14 != 0]) {
                    k -= 1;
                }
                fn_8002C2D0(&d, &bv, &lbl_3_data_281F0[k]);
            }
        }
        if (q->f15 == 2) {
            memcpy(&lbl_3_common_bss_35154._458, &d, sizeof(Vec));
        }
        q->f17 = q->f16;
        if (q->f16 != 0) {
            q->f16 = q->f16 - 1;
        }
    }
}

