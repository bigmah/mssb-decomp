#include "challenge/rep_0610.h"

extern u32 lbl_1_bss_30BC;
extern u8 lbl_1_bss_30C0[];
extern u8 lbl_1_data_F4F8[];
extern u8 lbl_803CBBC0[];
extern void fn_800A7D4C(s32, void*, u8);

extern u32 lbl_80108B90;
extern u16 lbl_1_data_F17C[];
extern void fn_800324EC(u16, s32, s32, void*);

extern u8 lbl_1_bss_3070[];

extern void fn_1_12820(void*, void*);
extern s16 lbl_1_data_A978[];
extern u8 lbl_1_bss_68FC[];
extern void* lbl_1_bss_5F7C[];

#include "Dolphin/vec.h"
extern void fn_80026134(s32, Vec*);
extern void fn_80026130(s32, void*, f32);
extern f32 lbl_1_data_ADC0[];
extern u8 lbl_1_data_ADC4[];

#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXTransform.h"
extern const f32 lbl_1_rodata_73CC[];
extern const f32 lbl_1_rodata_73D0[];
extern const f32 lbl_1_rodata_73D4[];
extern const f32 lbl_1_rodata_73D8[];
extern const f32 lbl_1_rodata_73DC[];
extern const f32 lbl_1_rodata_73E0[];

extern u8 lbl_8036E548[];
extern u8 lbl_1_bss_5F73[];
typedef struct { void* data; u32 pad4; u32 pad8; } ChallengeEntry;

extern void LITXForm(void* light, void* matrix);

extern u8 lbl_1_bss_5F74;
extern u8 lbl_1_bss_5F78[];

extern void* lbl_1_bss_67B8[];

extern u8 lbl_1_bss_67E0[];

extern u8 lbl_1_bss_5F71;

extern void* lbl_80366158[];
extern u8* lbl_803CC1B8[];

extern s32 lbl_1_data_F4DC[3];
extern u8 lbl_1_bss_3216[];
extern void fn_1_1496C(u8* object);
#include "static/UnknownHomes_Static.h"
extern void fn_1_10560(void* object);
extern void* lbl_1_bss_3098[];
extern u8 lbl_1_bss_3215[];
extern u8 lbl_1_bss_3214[];
extern u8 lbl_1_bss_30B8;

// .text:0x163FC size:0x4
void fn_1_163FC(void) {
}

void fn_1_D2F0(void) {
    lbl_1_bss_30B8 = 1;
}

void fn_1_D650(void) {
    lbl_1_bss_3214[0] = 1;
}

void fn_1_D67C(u8 value) {
    lbl_1_bss_3215[0] = value;
}

void fn_1_106B4(void) {
    lbl_1_bss_3098[0] = 0;
}

void* fn_1_106A4(void) {
    return lbl_1_bss_3098[0];
}

void fn_1_10670(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_10560, 11);
    *(s16*)(object + 0x10) = 0;
}

void fn_1_176EC(u8* object) {
    fn_1_1496C(object);
}

u8 fn_1_D638(void) {
    u8 flag = lbl_1_bss_3214[0];
    lbl_1_bss_3214[0] = 0;
    return flag;
}

s32 fn_1_D660(void) {
    return lbl_1_bss_3215[0] != 0;
}

void fn_1_D688(void) {
    lbl_1_bss_3216[0]++;
    if (lbl_1_bss_3216[0] == 3) lbl_1_bss_3216[0] = 0;
}

void fn_1_D6B4(void) {
    if (lbl_1_bss_3216[0] == 0) lbl_1_bss_3216[0] = 3;
    lbl_1_bss_3216[0]--;
}

s32 fn_1_D6E4(void) {
    u8 index = lbl_1_bss_3216[0];
    switch (index) {
    case 0:
    case 1:
    case 2:
        return lbl_1_data_F4DC[index];
    default:
        return 0;
    }
}

// fn_1_160D8, size:0x20
s32 fn_1_160D8(s8 a, s8 b) {
    if (a == b) return 0xFF0F;
    return 0xFFFF;
}

// fn_1_116EC, size:0x28
void fn_1_116EC(void* object) {
    SetDisplayStateTexture(object, 0, 0);
}

// fn_1_14928, size:0x44
void fn_1_14928(void) {
    fn_800AD038(lbl_80366158[2]);
    *(s16*)(*(u8**)(lbl_803CC1B8[0] + 0xC) + 0x10) = 1;
}

// fn_1_148CC, size:0x5C
void fn_1_148CC(void) {
    fn_800AD038(lbl_80366158[2]);
    *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
    *(void (**)(u8*))(lbl_803CC1B8[0]) = fn_1_176EC;
    lbl_1_bss_30B8 = 1;
}

// fn_1_15170, size:0x88
void fn_1_15170(void) {
    u16 buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 0x200) {
        fn_1_148CC();
    } else if (buttons & 0x100) {
        lbl_1_bss_5F71 = 1;
    }
}

// fn_1_14888, size:0x44
void fn_1_14888(u8* object) {
    if (lbl_1_bss_67E0[0x118]) {
        fn_800B9AA8(lbl_1_bss_67E0 + 0x30);
    } else {
        fn_800B9AA8(*(void**)(object + 0x70));
    }
}

// fn_1_E9F8, size:0x28
void fn_1_E9F8(u8* object, s32 index, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        index++;
        if (index == *(u16*)(object + 6)) index = 0;
    }
}

// fn_1_10AA4, size:0x28
void fn_1_10AA4(u8* object, f32 value) {
    *(f32*)(object + 0x54) = value;
    object[0x5A] = 1;
    if (lbl_1_bss_67B8[0] != 0) {
        *(f32*)((u8*)lbl_1_bss_67B8[0] + 4) = value;
    }
}

// fn_1_161D0, size:0x3C
void fn_1_161D0(void) {
    lbl_1_bss_5F74 ^= 1;
    fn_800B9A9C(lbl_1_bss_5F74, *(f32*)lbl_1_bss_5F78);
}

// fn_1_16558, size:0x38
void* fn_1_16558(s32 group, s32 index) {
    u8* base = lbl_8036E548;
    u8* table;
    u8* row;
    base += lbl_1_bss_5F73[0] * 0x27C;
    row = base; row += group * 4; table = *(u8**)(row + 0xC14);
    table = *(u8**)(table + 4);
    return ((ChallengeEntry*)table)[index].data;
}

// fn_1_17954, size:0x78
void fn_1_17954(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
}

// fn_1_1073C, size:0x7C
void fn_1_1073C(u8* object) {
    Vec displacement;
    displacement.x = *(f32*)(lbl_1_bss_67E0 + 0x108) - *(f32*)(object + 0x34);
    displacement.y = *(f32*)(lbl_1_bss_67E0 + 0x10C) - *(f32*)(object + 0x38);
    displacement.z = *(f32*)(lbl_1_bss_67E0 + 0x110) - *(f32*)(object + 0x3C);
    fn_80026134(0, &displacement);
    fn_80026130(0, lbl_1_data_ADC4, lbl_1_data_ADC0[0]);
}

// fn_1_12F18, size:0x74
void fn_1_12F18(u8* object) {
    fn_1_12820(*(void**)(lbl_8036E548 + 0x60), object + 8);
    if (lbl_1_data_A978[lbl_1_bss_68FC[0x40]] >= 0) {
        fn_800BD670(lbl_1_bss_5F7C[0], (u32)(object + 8));
    }
}

// fn_1_106C4, size:0x78
void fn_1_106C4(void) {
    u8* state = lbl_1_bss_3070;
    s32 buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 8) return;
    if (buttons & 4) return;
    if (buttons & 1) {
        state[0x11] ^= 1;
        return;
    }
    if (buttons & 2) {
        state[0x11] ^= 1;
        return;
    }
    if (!(buttons & 0x100) && (buttons & 0x200)) {
        *(u32*)(state + 0xC) = 0;
        state[0x2F01] = 1;
    }
}

// fn_1_F2F8, size:0x84
void fn_1_F2F8(void) {
    u8* state = lbl_1_bss_3070;
    s32 buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 0x100) {
        lbl_80108B90 = *(u32*)(state + 0x28);
        fn_800324EC(lbl_1_data_F17C[0], 0, -1, &lbl_80108B90);
    } else if (buttons & 0x200) {
        lbl_80108B90 = 0;
        *(u32*)(state + 0xC) = 0;
        state[0x2F01] = 10;
    }
}

// fn_1_CB9C, size:0x88
void fn_1_CB9C(s32 reset) {
    if (reset != 0) {
        lbl_1_bss_30BC = 0;
    } else {
        s32 index;
        u8* entry = lbl_1_data_F4F8 + lbl_803CBBC0[0] * 0x38;
        PSMTXCopy((f32(*)[4])(lbl_1_bss_30C0 + 0x58), (f32(*)[4])(entry + 8));
        index = lbl_803CBBC0[0];
        ((void (*)(s32, void*))fn_800A7D4C)(8, lbl_1_data_F4F8 + index * 0x38);
    }
}

// fn_1_11C98, size:0x68
void fn_1_11C98(void) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(*(void**)(lbl_8036E548 + i * 4 + 0xAC), lbl_1_bss_68FC + 0x10);
    }
}
