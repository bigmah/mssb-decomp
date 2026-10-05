#include "game/rep_3D50.h"
#include "header_rep_data.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/mtx.h"

extern u8 lbl_3_common_bss_35154[];
extern u8 lbl_80366158[];
extern u8* lbl_803CC1B8;
extern u8 lbl_3_data_281F0[];
extern u8 lbl_3_data_283F0[];
extern u8 lbl_3_data_28410[];
extern u8* lbl_3_bss_B9B8[];
extern void* memcpy(void*, const void*, u32);
extern void fn_8002C2D0(Vec*, Vec*, void*);

// .text:0x00160578 size:0x29C mapped:0x8079F60C
void fn_3_160578(void) {
    Vec d;
    Vec bv;
    u8* q = lbl_803CC1B8;
    s32 k;
    Vec* p29;
    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154[0x479] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (lbl_3_common_bss_35154[0x466] == 0) {
        lbl_3_bss_B9B8[0] = 0;
        ((void (*)(void))fn_800B0A14_removeQueue)();
        return;
    }
    if (lbl_80366158[0x28] == 0) {
        if (q[0x15] == 0 && g_Ball.warioWaluGarlicIsActive != 0) {
            q[0x15] = 1;
            q[0x17] = 0;
        }
        if (q[0x17] != 0) {
            q[0x17] = q[0x17] - 1;
            return;
        }
        if (q[0x15] == 0) {
            k = (u32)g_GameLogic.bOD_framesInLiveBallScene >> 31 ^ 1;
        } else if (q[0x15] == 1) {
            k = 2;
            q[0x15] = 2;
        } else {
            k = 3;
        }
        if (q[0x14] != 0) {
            k += 4;
        }
        p29 = (Vec*)(lbl_3_common_bss_35154 + 0x440);
        PSVECSubtract((Vec*)(lbl_3_common_bss_35154 + 0x44C), p29, &bv);
        if (PSVECMag(&bv)) {
            *(u32*)(lbl_3_data_281F0 + k * 0x40) = *(u32*)(lbl_3_common_bss_35154 + 4);
            fn_8002C2D0(p29, &bv, lbl_3_data_281F0 + k * 0x40);
        }
        d.x = *(f32*)((u8*)&g_Ball + 0x1A80);
        d.y = -*(f32*)((u8*)&g_Ball + 0x1A84);
        d.z = *(f32*)((u8*)&g_Ball + 0x1A88);
        if (k % 4 == 3) {
            PSVECSubtract((Vec*)(lbl_3_common_bss_35154 + 0x458), &d, &bv);
            if (PSVECMag(&bv)) {
                if (g_Ball.framesUntilBallHitsGround == ((u16*)(lbl_3_common_bss_35154 + 0x47A))[q[0x14] != 0]) {
                    k -= 1;
                }
                fn_8002C2D0(&d, &bv, lbl_3_data_281F0 + k * 0x40);
            }
        }
        if (q[0x15] == 2) {
            memcpy(lbl_3_common_bss_35154 + 0x458, &d, 0xC);
        }
        q[0x17] = q[0x16];
        if (q[0x16] != 0) {
            q[0x16] = q[0x16] - 1;
        }
    }
}

// .text:0x00160814 size:0xDC mapped:0x8079F8A8
void fn_3_160814(s32 a) {
    u8* q;
    u8 t;
    if (*(s16*)(lbl_3_common_bss_35154 + 0x464) == 0) {
        q = fn_800B0A5C_insertQueue(fn_3_160578, (u16)(*(u16*)(lbl_803CC1B8 + 0x12) + 1));
        lbl_3_bss_B9B8[0] = q;
        q[0x14] = (a == 4);
        lbl_3_bss_B9B8[0][0x15] = 0;
        lbl_3_bss_B9B8[0][0x16] = *(u32*)(lbl_3_data_283F0 + lbl_3_bss_B9B8[0][0x14] * 0x10);
        lbl_3_bss_B9B8[0][0x17] = 0;
        t = lbl_3_bss_B9B8[0][0x14];
        ((s16*)(lbl_3_common_bss_35154 + 0x47A))[t != 0] = *(u32*)(lbl_3_data_28410 + t * 4);
    }
}
