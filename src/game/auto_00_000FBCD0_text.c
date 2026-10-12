#include "game/auto_00_000FBCD0_text.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "static/Camera.h"
#include "game/rep_1D58.h"
#include "game/rep_1838.h"
#include "Dolphin/mtx.h"

// Draw node queued with fn_800A7D4C (two per frame buffer, indexed by lbl_803CBBC0).
typedef struct FBNode {
    /* 0x00 */ u32 link; // low bits: flags; the rest is set by fn_800A7D4C
    /* 0x04 */ void (*draw)(struct FBNode* node);
    /* 0x08 */ u8 _08[0x38 - 0x08];
    /* 0x38 */ Mtx view; // camera view matrix for this frame
    /* 0x68 */ u8 _68[4];
} FBNode; // size: 0x6C

extern FBNode lbl_3_data_1BE94[2];
extern s32 lbl_3_data_20E0C[];
extern s32* lbl_3_data_1DAE4[7]; // per stadium group: candidate scene indices
extern u8 lbl_803CBBC0;
extern void fn_800A7D4C(s32, void*);

// Spring step: pulls pos toward anchor (rest length restLen) and returns the new pos.
// .text:0x000FC2FC size:0x14C mapped:0x8073B390
Vec fn_3_FC2FC(Vec* pos, Vec* anchor, Vec* vel, f32 dt, f32 k, f32 damping, f32 restLen) {
    Vec diff;
    Vec velScaled;
    Vec rel;
    f32 dist;
    f32 force;

    PSVECSubtract(pos, anchor, &diff);
    dist = PSVECDistance(pos, anchor);
    PSVECSubtract(vel, anchor, &rel);
    PSVECScale(&rel, dt, &velScaled);
    force = k * (restLen - dist) + damping * (PSVECDotProduct(&velScaled, &diff) / dist);
    PSVECNormalize(&diff, &diff);
    PSVECScale(&diff, force * dt, &diff);
    PSVECAdd(pos, &diff, pos);
    return *pos;
}

// .text:0x000FBE24 size:0x4D8 mapped:0x8073AEB8
void fn_3_FBE24(void) {
    switch (g_Stats._3C) {
    case 2:
    case 9:
        fn_3_FBDAC(lbl_3_data_1DAE4[0][random_fn_3_9EE24(3)]);
        break;
    case 3:
    case 4:
    case 10:
        fn_3_FBDAC(lbl_3_data_1DAE4[2][random_fn_3_9EE24(3)]);
        break;
    case 5:
    case 11:
        fn_3_FBDAC(lbl_3_data_1DAE4[3][random_fn_3_9EE24(3)]);
        break;
    case 6:
        fn_3_FBDAC(lbl_3_data_1DAE4[4][1]);
        break;
    case 7:
        fn_3_FBDAC(lbl_3_data_1DAE4[5][random_fn_3_9EE24(3)]);
        break;
    case 8:
        fn_3_FBDAC(lbl_3_data_1DAE4[6][random_fn_3_9EE24(3)]);
        break;
    case 13:
        fn_3_FBDAC(lbl_3_data_1DAE4[1][random_fn_3_9EE24(3)]);
        break;
    default:
        fn_3_FBDAC(lbl_3_data_1DAE4[0][random_fn_3_9EE24(3)]);
        break;
    }
}

// .text:0x000FBDAC size:0x78 mapped:0x8073AE40
void fn_3_FBDAC(int scene) {
    lbl_3_common_bss_DE94_s2* p = lbl_3_common_bss_DE94._0000;
    p->_09AB = 1;
    lbl_3_common_bss_DE94._0000->_09AC = 1;
    lbl_3_common_bss_DE94._0000->_09AF = 1;
    lbl_3_common_bss_DE94._0000->_09B0 = 1;
    p->_0018 = 0;
    p->_0008 = 0;
    p->_0014 = 0;
    lbl_3_common_bss_DE94._0000->_092C = scene;
    lbl_3_common_bss_DE94._0000->_0000 = lbl_3_data_20E0C[scene];
    lbl_3_common_bss_DE94._0000->_09AE = 1;
    lbl_3_common_bss_DE94._0000->_0118 = 0;
    lbl_3_common_bss_DE94._0000->_0944 = 0;
}

// .text:0x000FBD70 size:0x3C mapped:0x8073AE04
void fn_3_FBD70(void) {
    lbl_3_common_bss_DE94_s2* p = lbl_3_common_bss_DE94._0000;
    p->_09AF = 0;
    lbl_3_common_bss_DE94._0000->_09B0 = 0;
    lbl_3_common_bss_DE94._0000->_09AE = 0;
    lbl_3_common_bss_DE94._0000->_09AB = 0;
    lbl_3_common_bss_DE94._0000->_09B6 = 0;
    p->_0018 = 0;
}

// .text:0x000FBD58 size:0x18 mapped:0x8073ADEC
void fn_3_FBD58(void) {
    lbl_3_common_bss_DE94._0000->_09AC = 0;
}

// .text:0x000FBCD0 size:0x88 mapped:0x8073AD64
void fn_3_FBCD0(void) {
    fn_3_B939C();
    if (g_GameLogic.bOD_framesInLiveBallScene >= 0) {
        PSMTXCopy(fn_80052768_getCamera(0)->view, lbl_3_data_1BE94[lbl_803CBBC0].view);
        fn_800A7D4C(1, &lbl_3_data_1BE94[lbl_803CBBC0]);
    }
}

