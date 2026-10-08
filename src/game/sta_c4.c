#include "game/sta_c4.h"
#include "header_rep_data.h"
#pragma dont_inline on
extern void* lbl_803CC1B8;
extern void fn_800B0A14_removeQueue(void*);
extern u32 fn_80033A24(void*, s32, s32, s32, s32, s32);

#include "Dolphin/GX/GXBump.h"
#include "Dolphin/GX/GXTexture.h"
extern GXTexObj lbl_3_bss_B640;
extern void fn_3_B9510(s32);
#include "Dolphin/GX/GXPixel.h"

extern u8 lbl_3_bss_B5D4;
extern u8 g_GameLogic[];
extern u8 g_d_GameSettings[];
extern u8 lbl_3_data_81DC[];
extern s32 lbl_3_bss_B574[];
extern u8 lbl_3_bss_B664;
extern u8 lbl_3_bss_B630[];
extern const f32 lbl_3_rodata_3064;
extern void AnimateActorBones(void*);
extern u8* lbl_3_bss_B628[];
extern u8 lbl_80371C30[];
extern void fn_800528C0(f32, f32, f32, s16*, s16*);
extern void fn_3_8B890(s32);
extern void fn_3_8BA60(s32, s32, s32);
extern s32 fn_3_8BBC4(s32, s32, s32, s32);
extern const f32 lbl_3_rodata_2FB8[3];
extern const f32 lbl_3_rodata_2FC4;
extern const f64 lbl_3_rodata_2FC8;
extern const f32 lbl_3_rodata_2FD0;
extern const f32 lbl_3_rodata_2FD4;
extern const f32 lbl_3_rodata_3028;
extern const f32 lbl_3_rodata_302C;
extern const char lbl_3_rodata_3030[];
extern const char lbl_3_rodata_303C[];
extern u8* lbl_3_bss_B63C;
extern void* fn_3_B9534(u32, u32, void*);
extern s32 fn_800247E4(s32, s32, s32, s32);
extern void OSPanic(const char*, int, const char*, ...);
extern int rand(void);
typedef struct {
    u8* p0;
    u8 pad4[0x2C];
    s32 n;
    u8 pad34[8];
    u32* a3C;
    u16* a40;
    u32* a44;
    u8* a48;
    f32 f4C[3];
    f32 f58[3];
    s16 cnt;
    u8 pad66[5];
    u8 b6B;
} StaCommon;
extern StaCommon lbl_3_common_bss_350E4;
extern u8 g_Ball[];
extern u8 lbl_3_bss_B570[];
extern void fn_80034CEC(void*);
extern u32 sndFXStartEx(int, u8, u8, u8);
extern void sndFXCtrl(int, int, u8);
extern u8 lbl_3_data_8404[];
extern u8 lbl_3_data_84B8[];
extern u8 lbl_3_bss_B620[];
typedef struct { f32 x, y, z; } V3;
extern V3 lbl_3_bss_B5D8[6];
extern u8 lbl_8036E548[];
extern u32 lbl_3_data_1BA88[];
extern void fn_3_F92FC(void);
extern const f32 lbl_3_rodata_3060;
extern void* fn_800B0A5C_insertQueue(void*, s32);
extern void* memcpy(void*, const void*, u32);
extern void* memset(void*, int, u32);
extern void DCFlushRange(void*, u32);

// .text:0x000F8444 size:0x10
void fn_3_F8444(void) {
    lbl_3_bss_B5D4 = 1;
}

// .text:0x000F8454 size:0xD0
void fn_3_F8454(void) {
    if (g_GameLogic[0x11E] == 0xB) {
        if (lbl_3_bss_B664 == 0) {
            fn_3_8B890(lbl_3_bss_B574[0]);
            lbl_3_bss_B664 = 1;
        }
    } else if (lbl_3_bss_B664 != 0) {
        lbl_3_bss_B574[0] = fn_3_8BBC4(((u16*)lbl_3_data_81DC)[g_d_GameSettings[9]] + 3, 0, 0, 2);
        lbl_3_bss_B664 = 0;
    } else {
        fn_3_8BA60(lbl_3_bss_B574[0], 0, 0);
    }
}

// .text:0x000F8524 size:0x8C mapped:0x807375B8
void fn_3_F8524(u8* p) {
    if (p[0x4F] < 0x2A) {
        *(f32*)(p + 0x14) = lbl_3_rodata_2FC4;
        *(f32*)(p + 0x4) = lbl_3_rodata_2FB8[0];
        *(f32*)(p + 0x8) = lbl_3_rodata_2FB8[1] - lbl_3_rodata_2FC8;
        *(f32*)(p + 0xC) = lbl_3_rodata_2FB8[2];
        *(f32*)(p + 0x38) = lbl_3_rodata_2FD0;
        *(f32*)(p + 0x3C) = lbl_3_rodata_2FD4;
    }
    p[0x42] = 0xFF;
    p[0x41] = 0xFF;
    p[0x40] = 0xFF;
    p[0x43] = 0xFF;
    *(s16*)(p + 0x4A) = 0x80;
    *(s16*)(p + 0x48) = 0;
}

// .text:0x000F85B0 size:0x2C8 mapped:0x80737644
void fn_3_F85B0(void) {
    return;
}

// .text:0x000F8878 size:0x244 mapped:0x8073790C
void fn_3_F8878(void) {
    return;
}

// .text:0x000F8ABC size:0x48 mapped:0x80737B50
void fn_3_F8ABC(void) {
    if (fn_80033A24(fn_3_F85B0, 0xF0, 0xD, 0x2A, 1, 0x7F) != 0) {
        fn_3_F8878();
    }
}

// .text:0x000F8B04 size:0x2C mapped:0x80737B98
void fn_3_F8B04(void) {
    GXSetZMode(1, 3, 0);
}

// .text:0x000F8B30 size:0x4 mapped:0x80737BC4
void fn_3_F8B30(void) {
    return;
}

// .text:0x000F8B34 size:0x74 mapped:0x80737BC8
void fn_3_F8B34(void) {
    fn_3_B9510(0);
    GXLoadTexObj(&lbl_3_bss_B640, 7);
    GXSetIndTexOrder(0, 0, 7);
    GXSetNumIndStages(1);
    GXSetIndTexCoordScale(0, 0, 0);
    GXSetTevIndWarp(0, 0, 0, 0, 1);
}

// .text:0x000F8BA8 size:0x158 mapped:0x80737C3C
void fn_3_F8BA8(u8* o) {
    u32* r = *(u32**)(*(u8**)(*(u8**)(*(u8**)(*(u8**)(*(u8**)(*(u8**)(o + 0x74)) + 0x18)) + 0x14) + 0x10) + 4);
    s8 prev;
    u32 i, j;
    if (o[0xA3] != 0 && o[0xA3] % 3 == 0) {
        o[0xA2]++;
        if (o[0xA2] > 0x19) {
            o[0xA2] = 0xA;
            o[0xA3] = 0;
        }
        r[1] &= ~0x1FFF;
        r[1] |= o[0xA2];
        for (i = 0; i < 0x80; i++) {
            for (j = 0; j < 0x80; j++) {
                if (j == 0) {
                    prev = lbl_3_bss_B63C[fn_800247E4(i, 0x7F, 0x80, 2)];
                }
                {
                    s32 idx = fn_800247E4(i, j, 0x80, 2);
                    s8 t = lbl_3_bss_B63C[idx];
                    lbl_3_bss_B63C[idx] = prev;
                    prev = t;
                }
            }
        }
        DCFlushRange(lbl_3_bss_B63C, 0x8000);
    }
    o[0xA3]++;
}

// .text:0x000F8D00 size:0x120 mapped:0x80737D94
void fn_3_F8D00(void) {
    f32 m[2][3];
    u32 i, j;
    m[0][0] = lbl_3_rodata_3028;
    m[0][1] = lbl_3_rodata_302C;
    m[0][2] = lbl_3_rodata_302C;
    m[1][0] = lbl_3_rodata_302C;
    m[1][1] = lbl_3_rodata_3028;
    m[1][2] = lbl_3_rodata_302C;
    GXSetIndTexMtx(GX_ITM_0, m, 2);
    lbl_3_bss_B63C = (u8*)fn_3_B9534(0x80, 0x80, &lbl_3_bss_B640);
    if (lbl_3_bss_B63C == NULL) {
        OSPanic(lbl_3_rodata_3030, 0x6DF, lbl_3_rodata_303C);
    }
    for (i = 0; i < 0x80; i++) {
        for (j = 0; j < 0x80; j++) {
            s32 idx = fn_800247E4(j, i, 0x80, 2);
            lbl_3_bss_B63C[idx] = (u8)(rand() % 4) + 0x7E;
        }
    }
}

// .text:0x000F8E20 size:0x268 mapped:0x80737EB4
void fn_3_F8E20(void) {
    s16 spE;
    s16 spC;
    s16 spA;
    s16 sp8;
    u8* b = lbl_3_bss_B570;
    u8* sp = b + 0xB0;
    f32* p = (f32*)(b + 0x68);
    u8* st = lbl_803CC1B8;
    s32 i;
    for (i = 0; i < 6; i++, sp++, p += 3) {
        switch (*sp) {
            case 1:
                fn_800528C0(p[0], p[1], p[2], &spC, &spE);
                *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(*(u8**)(b + 0xB8) + 0x14) + i) * 8) + 0x48) = spC;
                *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(*(u8**)(b + 0xB8) + 0x14) + i) * 8) + 0x4C) = spE;
                *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(*(u8**)(b + 0xB8) + 0x14) + i) * 8) + 0x50) = 0.0f;
                *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(st + 0x14) + i) * 8) + 0x5C) = 0;
                *(u32*)(*(u8**)(lbl_80371C30 + (*(u16*)(st + 0x14) + i) * 8) + 0x54) |= 2;
                *sp = 2;
                break;
            case 2: {
                u8* o;
                fn_800528C0(p[0], p[1], p[2], &sp8, &spA);
                *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(*(u8**)(b + 0xB8) + 0x14) + i) * 8) + 0x48) = sp8;
                *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(*(u8**)(b + 0xB8) + 0x14) + i) * 8) + 0x4C) = spA;
                *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(*(u8**)(b + 0xB8) + 0x14) + i) * 8) + 0x50) = 0.0f;
                o = *(u8**)(lbl_80371C30 + (*(u16*)(st + 0x14) + i) * 8);
                if ((u32)__cntlzw(2 - o[0x69]) >> 5) {
                    *(u32*)(o + 0x54) &= ~2;
                    *sp = 0;
                }
                break;
            }
        }
    }
    if (b[0x64] != 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
        fn_80034CEC(*(void**)(b + 0xB8));
        b[0x64] = 0;
    }
}

// .text:0x000F9088 size:0xDC mapped:0x8073811C
void fn_3_F9088(f32* pos, s32 idx) {
    s16 x;
    s16 y;
    fn_800528C0(pos[0], pos[1], pos[2], &x, &y);
    *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(lbl_3_bss_B628[0] + 0x14) + idx) * 8) + 0x48) = x;
    *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(lbl_3_bss_B628[0] + 0x14) + idx) * 8) + 0x4C) = y;
    *(f32*)(*(u8**)(lbl_80371C30 + (*(u16*)(lbl_3_bss_B628[0] + 0x14) + idx) * 8) + 0x50) = 0.0f;
}

// .text:0x000F9164 size:0x198 mapped:0x807381F8
// partial: ~14 diff insns; only the g_Ball/B5D8/B620 tail address-reg assignment (r3/r4/r5) and snd/stad saved-reg order differ
void fn_3_F9164(u8* o) {
    s32 stad;
    s32 slot;
    s32 snd;
    u32 h;
    u8 v;
    V3* d;
    switch (o[0xA2]) {
        case 0:
            snd = 2;
            slot = g_Ball[0x1BE5];
            break;
        case 1:
            snd = 1;
            slot = g_Ball[0x1BE5] + 2;
            break;
        case 2:
            snd = 0;
            slot = g_Ball[0x1BE5] + 4;
            break;
    }
    stad = g_d_GameSettings[9];
    if (g_d_GameSettings[7] == 6) {
        v = lbl_3_data_84B8[snd * 2];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2];
    }
    h = sndFXStartEx((u16)(snd + ((u16*)lbl_3_data_81DC)[stad]), v, 0x3F, 0);
    if (g_d_GameSettings[7] == 6) {
        v = lbl_3_data_84B8[snd * 2 + 1];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2 + 1];
    }
    sndFXCtrl(h, 0x5B, v);
    lbl_3_bss_B5D8[slot].x = *(f32*)(g_Ball + 0);
    d = &lbl_3_bss_B5D8[slot];
    d->y = -*(f32*)(g_Ball + 4);
    lbl_3_bss_B620[slot] = 1;
    d->z = *(f32*)(g_Ball + 8);
}

// .text:0x000F92FC size:0x50 mapped:0x80738390
void fn_3_F92FC(void) {
    typedef struct { u8 pad[0x90]; u8 a : 2; u8 f : 1; u8 b : 5; } FlagObj;
    typedef struct { u8 pad[0x10]; s16 cnt; FlagObj* obj; } StateObj;
    StateObj* st = (StateObj*)lbl_803CC1B8;
    if (st->cnt-- == 0) {
        FlagObj* o = st->obj;
        o->f = 1;
        fn_800B0A14_removeQueue(o);
    }
}

// .text:0x000F934C size:0x2F0 mapped:0x807383E0
void fn_3_F934C(void) {
    return;
}

// .text:0x000F963C size:0x130 mapped:0x807386D0
#pragma dont_inline off
void fn_3_F963C(s32 idx, u8* v) {
    typedef struct { u8 pad[0x90]; u8 a : 1; u8 f : 1; u8 b : 6; } FlagObj;
    u8* p;
    lbl_3_common_bss_350E4.b6B = 1;
    p = fn_800B0A5C_insertQueue(fn_3_F934C, (u16)(*(u16*)((u8*)lbl_803CC1B8 + 0x12) + 1));
    memcpy(lbl_3_common_bss_350E4.f4C, g_Ball, 0xC);
    memcpy(lbl_3_common_bss_350E4.f58, g_Ball + 0x318, 0xC);
    lbl_3_common_bss_350E4.f4C[1] = -lbl_3_common_bss_350E4.f4C[1];
    lbl_3_common_bss_350E4.f58[1] = -lbl_3_common_bss_350E4.f58[1];
    if (v != NULL) {
        PSVECScale((Vec*)(v + 0xC), lbl_3_rodata_3060, (Vec*)(p + 0x14));
    }
    memset(p + 0x20, 0, 0xC);
    *(s32*)(p + 0x2C) = idx;
    p[0x30] = 0;
    ((FlagObj*)(lbl_3_common_bss_350E4.p0 + *(s32*)(p + 0x2C) * 0xE8))->f = 0;
}
#pragma dont_inline on

// .text:0x000F976C size:0x284 mapped:0x80738800
// partial: = inlined F99F0 + F963C; same snd/stad saved-reg swap and tail reg assignment as F99F0
void fn_3_F976C(s32 idx, s32 b, u8* c) {
    fn_3_F99F0(idx);
    fn_3_F963C(idx, c);
}

// .text:0x000F99F0 size:0x1AC mapped:0x80738A84
// partial: prologue matches; tail lis/addi reg assignment for g_Ball/B5D8/B620 differs (we put g_Ball in r3, orig r4)
#pragma dont_inline off
void fn_3_F99F0(s32 idx) {
    s32 snd;
    s32 slot;
    s32 stad;
    u32 h;
    u8 v;
    V3* d;
    switch (*(u8*)((u32)lbl_3_common_bss_350E4.p0 + idx * 0xE8 + 0xA2)) {
        case 0:
            snd = 2;
            slot = g_Ball[0x1BE5];
            break;
        case 1:
            snd = 1;
            slot = g_Ball[0x1BE5] + 2;
            break;
        case 2:
            snd = 0;
            slot = g_Ball[0x1BE5] + 4;
            break;
    }
    stad = g_d_GameSettings[9];
    if (g_d_GameSettings[7] == 6) {
        v = lbl_3_data_84B8[snd * 2];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2];
    }
    h = sndFXStartEx((u16)(snd + ((u16*)lbl_3_data_81DC)[stad]), v, 0x3F, 0);
    if (g_d_GameSettings[7] == 6) {
        v = lbl_3_data_84B8[snd * 2 + 1];
    } else {
        v = lbl_3_data_8404[stad * 0x1E + snd * 2 + 1];
    }
    sndFXCtrl(h, 0x5B, v);
    lbl_3_bss_B5D8[slot].x = *(f32*)(g_Ball + 0);
    lbl_3_bss_B5D8[slot].y = -*(f32*)(g_Ball + 4);
    lbl_3_bss_B620[slot] = 1;
    lbl_3_bss_B5D8[slot].z = *(f32*)(g_Ball + 8);
}

#pragma dont_inline on

// .text:0x000F9B9C size:0x1F8 mapped:0x80738C30
// partial: F963C inlined OK; only prologue reg order (lis r6/addi r7 base vs ours r3/r6) differs
void fn_3_F9B9C(s32 idx, s32 b, u8* c) {
    typedef struct { u8 pad[0x90]; u8 a : 1; u8 f : 1; u8 g : 1; u8 h : 5; } FlagObj;
    u8* o = lbl_3_common_bss_350E4.p0 + idx * 0xE8;
    u8* q;
    u32 t;
    o[0xA1] = o[0xA2];
    if (o[0xA1] == 0) {
        fn_3_F9E78();
        return;
    }
    if (o[0xA1] == 2) {
        fn_3_F963C(idx, c);
    }
    *(u32*)(o + 0x74) = *(u32*)(lbl_8036E548 + 0x6C) + o[0xA2] * 0x90 + 0x34;
    *(u32*)(o + 0x80) = lbl_3_data_1BA88[o[0xA2]];
    t = 0;
    if (((FlagObj*)o)->a && *(u32*)(o + 0x78) != 0) {
        t = 1;
    }
    ((FlagObj*)o)->f = t;
    (*(void (**)(s32, s32, u8*))(o + 0x80))(idx, b, c);
    ((FlagObj*)o)->g = 0;
    q = fn_800B0A5C_insertQueue(fn_3_F92FC, 0);
    *(s16*)(q + 0x10) = 0x5A;
    *(u8**)(q + 0x14) = o;
}

// .text:0x000F9D94 size:0xE4 mapped:0x80738E28
void fn_3_F9D94(u8* o) {
    typedef struct { u8 pad[0x90]; u8 a : 1; u8 b : 1; u8 c : 6; } FlagObj90;
    u8** anim = *(u8***)(o + 0x74);
    s32 i;
    if (*(f32*)(o + 0x9C) >= *(f32*)(*(u8**)(*(u8**)(anim[1] + 4) + 4) + *(u16*)((u8*)anim + 0xE) * 0x10)) {
        ((FlagObj90*)o)->a = 0;
        *(u32*)(o + 0x74) = 0;
        *(u32*)(o + 0x78) = 0;
        *(u32*)(o + 0x7C) = 0;
        *(u32*)(o + 0x80) = 0;
        ((FlagObj90*)o)->b = 0;
        for (i = 0; i < 9; i++) {
            if (lbl_3_bss_B630[i] == o[0xA0]) {
                lbl_3_bss_B630[i] = 0xFF;
                break;
            }
        }
    } else {
        AnimateActorBones(anim[0]);
        *(f32*)(o + 0x9C) = *(f32*)(o + 0x9C) + lbl_3_rodata_3064;
    }
}

// .text:0x000F9E78 size:0x548 mapped:0x80738F0C
void fn_3_F9E78(void) {
    return;
}

// .text:0x000FA3C0 size:0x1CC mapped:0x80739454
// 93.9%: only saved-reg ranking differs (orig: offC<cnt<j<i<off18; ours: i<cnt<j<off18<offC), plus the zero-init copies come from i in the orig
extern u8 lbl_3_data_1BA98[];
extern void* _OSAllocFromHeap(s32, s32);
extern void* memset(void*, int, u32);
extern void CTRLBuildMatrix(void*, void*);
extern void fn_3_B8414(void*, void*);
extern void fn_3_B8464(void*, void*);
extern void fn_3_B8574(void);
void fn_3_FA3C0(void) {
    Mtx m;
    s32 j;
    s32 cnt;
    s32 i;
    s32 size;
    s32 idx;
    size = (lbl_3_common_bss_350E4.n << 2) + (lbl_3_common_bss_350E4.n << 1) + (lbl_3_common_bss_350E4.n << 2) + lbl_3_common_bss_350E4.n * 0x18;
    if (lbl_3_common_bss_350E4.a48 == NULL) {
        lbl_3_common_bss_350E4.a48 = _OSAllocFromHeap(4, size);
        lbl_3_common_bss_350E4.a3C = (u32*)(lbl_3_common_bss_350E4.a48 + lbl_3_common_bss_350E4.n * 0x18);
        lbl_3_common_bss_350E4.a44 = lbl_3_common_bss_350E4.a3C + lbl_3_common_bss_350E4.n;
        lbl_3_common_bss_350E4.a40 = (u16*)(lbl_3_common_bss_350E4.a44 + lbl_3_common_bss_350E4.n);
    }
    memset(lbl_3_common_bss_350E4.a48, 0, size);
    cnt = 0;
    for (i = 0; i < 10; i++) {
        j = (u16)(lbl_3_common_bss_350E4.a40[cnt - 1] + lbl_3_common_bss_350E4.a3C[cnt - 1]);
        lbl_3_common_bss_350E4.a40[cnt] = j;
        idx = j;
        fn_3_B8574();
        for (j = 0; j < lbl_3_common_bss_350E4.n; j++) {
            if (i == lbl_3_data_1BA98[j * 0x14 + 0x12] && (lbl_3_common_bss_350E4.p0[j * 0xE8 + 0x90] >> 6 & 1)) {
                lbl_3_common_bss_350E4.a44[idx] = j;
                idx++;
                lbl_3_common_bss_350E4.a3C[cnt]++;
                size = (s32)(lbl_3_common_bss_350E4.p0 + j * 0xE8);
                CTRLBuildMatrix((void*)size, m);
                fn_3_B8464(m, *(void**)(size + 0x78));
            }
        }
        if (lbl_3_common_bss_350E4.a3C[cnt] != 0) {
            fn_3_B8414(lbl_3_common_bss_350E4.a48 + cnt * 0x18, lbl_3_common_bss_350E4.a48 + (cnt * 0x18 + 0xC));
            cnt++;
        }
    }
    lbl_3_common_bss_350E4.cnt = cnt;
}

// .text:0x000FA58C size:0xE4C mapped:0x80739620
void fn_3_FA58C(void) {
    return;
}

// .text:0x000FB3D8 size:0x7C8 mapped:0x8073A46C
void fn_3_FB3D8(void) {
    return;
}

// .text:0x000FBBA0 size:0x130 mapped:0x8073AC34
void fn_3_FBBA0(u8* t) {
    GXTexObj tex;
    GXTlutObj tlut;
    if (*(u32*)(t + 4) != 0) {
        GXInitTexObjCI(&tex, *(void**)t, *(u16*)(t + 0xA), *(u16*)(t + 8), (GXCITexFmt) * (u8*)(t + 0x17), (GXTexWrapMode) * (u8*)(t + 0xC),
                       (GXTexWrapMode) * (u8*)(t + 0xD), t[0x15] != t[0x16], 0);
        GXInitTlutObj(&tlut, *(void**)(t + 4), (GXTlutFmt) * (u8*)(t + 0x1A), *(u16*)(t + 0x18));
        GXLoadTlut(&tlut, 0);
    } else {
        GXInitTexObj(&tex, *(void**)t, *(u16*)(t + 0xA), *(u16*)(t + 8), (GXTexFmt) * (u8*)(t + 0x17), (GXTexWrapMode) * (u8*)(t + 0xC),
                     (GXTexWrapMode) * (u8*)(t + 0xD), t[0x15] != t[0x16]);
    }
    GXInitTexObjLOD(&tex, (GXTexFilter)t[0xE], (GXTexFilter)t[0xF], (f32)t[0x15], (f32)t[0x16], *(f32*)(t + 0x10), 0, 0, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP0);
}


#pragma dont_inline off
