#include "game/sta_c0.h"
#include "header_rep_data.h"

extern u8 g_GameLogic[];
extern void AnimateActorBones(void*);
typedef struct { u8 pad[0x90]; u8 f : 1; } BF90;
#include "Dolphin/GX/GXBump.h"
#include "Dolphin/GX/GXTexture.h"
extern GXTexObj lbl_3_bss_9F4C;
extern void fn_3_B9510(s32);
extern u8* lbl_3_bss_9F48;
extern u8 lbl_3_common_bss_350E4[];
extern u8 g_Stats[];
extern Vec lbl_3_rodata_22D8;
extern void GXSetZCompLoc(u8);
extern s32 fn_8005268C(void);
extern u8* fn_80052734(s32);
extern void PSVECSubtract(const Vec*, const Vec*, Vec*);
extern f32 PSVECMag(const Vec*);
extern f32 PSVECDotProduct(const Vec*, const Vec*);
extern u32 lbl_3_bss_9F3C;
extern void DCFlushRange(void*, u32);
extern char lbl_3_rodata_22EC[];
extern char lbl_3_rodata_22F8[];
extern u32 fn_3_B9534(s32, s32, void*);
extern s32 fn_800247E4(u32, u32, s32, s32);
extern u32 rand();
extern void OSPanic(const char*, int, const char*, ...);

extern u8 g_d_GameSettings[];
extern u16 lbl_3_data_81DC[];
typedef struct { u8 pad0[8]; s32 h0; s32 h1; u8 pad1[0x24]; u8 flag; } S9F38;
extern S9F38 lbl_3_bss_9F38;
extern void fn_3_8B890(s32);
extern void fn_3_8BA60(s32, s32, s32);
extern s32 fn_3_8BBC4(s32, s32, s32, s32);
extern void fn_3_B7FC8(void);

// .text:0x000C9744 size:0x134
void fn_3_C9744(void) {
    S9F38* s = &lbl_3_bss_9F38;
    u8* gs = g_d_GameSettings;
    if (gs[7] != 2 && g_GameLogic[0x11E] != 0x21) {
        if (g_GameLogic[0x11E] == 0xB) {
            if (s->flag == 0) {
                fn_3_8B890(s->h0);
                if (gs[7] != 7) {
                    fn_3_8B890(s->h1);
                }
                s->flag = 1;
            }
        } else {
            if (s->flag != 0) {
                s->h0 = fn_3_8BBC4(lbl_3_data_81DC[gs[9]] + 1, 0, 0, 1);
                if (gs[7] != 7) {
                    s->h1 = ((s32(*)(void*, void*))fn_3_B7FC8)((void*)lbl_3_data_81DC[gs[9]], NULL);
                }
                s->flag = 0;
            } else {
                fn_3_8BA60(s->h0, 0, 0);
                if (gs[7] != 7) {
                    fn_3_8BA60(s->h1, 0, 0);
                }
            }
        }
    }
}

// .text:0x000C9878 size:0x180 mapped:0x8070890C
void fn_3_C9878(void) {
    u8* p = *(u8**)(lbl_3_common_bss_350E4 + 0x10);
    Vec diff;
    Vec dir = lbl_3_rodata_22D8;
    s32 idx;
    u8 flag;
    u8* r;
    u8* q;
    s32 i;
    s32 gl;
    f32 lim;
    if (p != NULL) {
        GXSetZCompLoc(0);
        idx = fn_8005268C();
        gl = g_GameLogic[0x11E];
        if (gl != 0xB) {
            if (gl < 0xB) {
                if (gl == 3) {
                    goto zero;
                }
                goto check;
            }
            if (gl >= 0x18 || gl < 0x13) {
            check:
                if (g_Stats[0x36] == 0) {
                    u8* t = fn_80052734(idx);
                    PSVECSubtract((Vec*)(t + 0x7C), (Vec*)(t + 0x70), &diff);
                    diff.y = 0.0f;
                    lim = *(f32*)(p + 0x1C) * PSVECMag(&diff);
                    flag = PSVECDotProduct(&diff, &dir) > lim;
                } else {
                    goto zero;
                }
            } else {
                goto zero;
            }
        } else {
        zero:
            flag = 0;
        }
        q = p + idx * 0xC;
        r = q + flag;
        for (i = 0; i < p[0x20]; i++) {
            *(s16*)(*(u8**)(p + 0x18) + (q[0] << 5) + 0x1C) = r[1];
            *(s16*)(*(u8**)(p + 0x18) + (q[3] << 5) + 0x1C) = r[4];
            q += 6;
            r += 6;
        }
    }
}

// .text:0x000C99F8 size:0x68 mapped:0x80708A8C
void fn_3_C99F8(void* a_) {
    BF90* a = a_;
    if (g_GameLogic[0x11E] == 1 || g_GameLogic[0x11E] == 0) {
        a->f = 0;
    } else {
        a->f = 1;
        AnimateActorBones(**(void***)((u8*)a + 0x74));
    }
}

// .text:0x000C9A60 size:0x68 mapped:0x80708AF4
void fn_3_C9A60(void* a_) {
    BF90* a = a_;
    if (g_GameLogic[0x11E] == 1 || g_GameLogic[0x11E] == 0) {
        a->f = 0;
    } else {
        a->f = 1;
        AnimateActorBones(**(void***)((u8*)a + 0x74));
    }
}

// .text:0x000C9AC8 size:0x94 mapped:0x80708B5C
void fn_3_C9AC8(void) {
    fn_3_B9510(0);
    fn_3_B9510(1);
    GXLoadTexObj(&lbl_3_bss_9F4C, 7);
    GXSetIndTexOrder(0, 0, 7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetTevIndWarp(0, 0, 0, 0, 1);
    GXSetTevIndWarp(1, 0, 0, 0, 1);
}

// .text:0x000C9B5C size:0x138 mapped:0x80708BF0
void fn_3_C9B5C(void* a_) {
    BF90* a = a_;
    u32 y;
    u32 x;
    s8 prev;
    if (g_GameLogic[0x11E] == 1 || g_GameLogic[0x11E] == 0) {
        a->f = 0;
        return;
    }
    a->f = 1;
    if (lbl_3_bss_9F3C < 3) {
        lbl_3_bss_9F3C++;
        return;
    }
    for (y = 0; y < 0x80; y++) {
        for (x = 0; x < 0x40; x++) {
            if (x == 0) {
                prev = (s8)lbl_3_bss_9F48[fn_800247E4(y, 0x3F, 0x80, 2)];
            }
            {
                s32 o = fn_800247E4(y, x, 0x80, 2);
                s32 t = (s8)lbl_3_bss_9F48[o];
                lbl_3_bss_9F48[o] = prev;
                prev = t;
            }
        }
    }
    lbl_3_bss_9F3C = 0;
    DCFlushRange(lbl_3_bss_9F48, 0x4000);
}

// .text:0x000C9C94 size:0x120 mapped:0x80708D28
void fn_3_C9C94(void) {
    f32 m[6];
    s32 off;
    u32 y;
    u32 x;
    m[0] = 0.5f;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;
    m[4] = 0.0f;
    m[5] = 0.0f;
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])m, 2);
    lbl_3_bss_9F48 = (u8*)fn_3_B9534(0x80, 0x40, &lbl_3_bss_9F4C);
    if (lbl_3_bss_9F48 == NULL) {
        OSPanic(lbl_3_rodata_22EC, 0x29F, lbl_3_rodata_22F8);
    }
    for (y = 0; y < 0x40; y++) {
        for (x = 0; x < 0x80; x++) {
            off = fn_800247E4(x, y, 0x80, 2);
            lbl_3_bss_9F48[off] = (u8)((s32)rand() % 4) + 0x7E;
        }
    }
}

// .text:0x000C9DB4 size:0xE00 mapped:0x80708E48
void fn_3_C9DB4(void) {
    return;
}

