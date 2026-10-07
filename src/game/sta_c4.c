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
extern void fn_3_8B890(s32);
extern void fn_3_8BA60(s32, s32, s32);
extern s32 fn_3_8BBC4(s32, s32, s32, s32);
extern const f32 lbl_3_rodata_2FB8[3];
extern const f32 lbl_3_rodata_2FC4;
extern const f64 lbl_3_rodata_2FC8;
extern const f32 lbl_3_rodata_2FD0;
extern const f32 lbl_3_rodata_2FD4;

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
void fn_3_F8BA8(void) {
    return;
}

// .text:0x000F8D00 size:0x120 mapped:0x80737D94
void fn_3_F8D00(void) {
    return;
}

// .text:0x000F8E20 size:0x268 mapped:0x80737EB4
void fn_3_F8E20(void) {
    return;
}

// .text:0x000F9088 size:0xDC mapped:0x8073811C
void fn_3_F9088(void) {
    return;
}

// .text:0x000F9164 size:0x198 mapped:0x807381F8
void fn_3_F9164(void) {
    return;
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
void fn_3_F963C(void) {
    return;
}

// .text:0x000F976C size:0x284 mapped:0x80738800
void fn_3_F976C(void) {
    return;
}

// .text:0x000F99F0 size:0x1AC mapped:0x80738A84
void fn_3_F99F0(void) {
    return;
}

// .text:0x000F9B9C size:0x1F8 mapped:0x80738C30
void fn_3_F9B9C(void) {
    return;
}

// .text:0x000F9D94 size:0xE4 mapped:0x80738E28
void fn_3_F9D94(void) {
    return;
}

// .text:0x000F9E78 size:0x548 mapped:0x80738F0C
void fn_3_F9E78(void) {
    return;
}

// .text:0x000FA3C0 size:0x1CC mapped:0x80739454
void fn_3_FA3C0(void) {
    return;
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
void fn_3_FBBA0(void) {
    return;
}

