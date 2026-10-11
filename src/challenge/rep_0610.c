#include "challenge/rep_0610.h"

// POOL BEGIN
static u8 ch_6940[0x48 * 4];
static u8 ch_fill692C[0x14];
static u8 ch_68FC[0x30];
static u8 ch_fill68F8[0x4];
static u8 ch_67E0[0x118];
static s32 ch_67B8[0xA];
static u8 ch_fill62B8[0x500];
static u8 ch_60EC[0x5C * 5];
static u8* ch_60E8;
static u8 ch_fill60E4[0x4];
static u8* ch_60E0;
static u8 ch_fill60DF;
static u8 ch_fill60DE;
static u8 ch_fill60DD;
static u8 ch_fill60DC;
static u8 ch_fill60DB;
static u8 ch_fill60DA;
static u8 ch_60A4[0x36];
static u8 ch_fill5F74[0x130];
static u8 ch_5F73;
static u8 ch_5F72;
static u8 ch_5F71;
static u8 ch_fill5F70;
static u32 ch_5F6C;
static u8 ch_fill5F6B;
static u8 ch_fill5F6A;
static u8 ch_5F69;
static u8 ch_5F68;
static f32 ch_5F64;
static u8 ch_fill5F63;
static s8 ch_5F62;
static u16 ch_5F60;
static s32 ch_5F5C;
static u8 ch_3758[0x2804];
static u8 ch_3258[0x500];
static u8 ch_3218[0x40];
static u8 ch_fill30C0[0x158];
static s32 ch_30BC;
static u8 ch_fill3090[0x2C];
static s32 ch_308C;
static s32 ch_3088;
static u8 ch_fill3084[0x4];
static u8 ch_fill3083;
static u8 ch_fill3082;
static u8 ch_3081;
static u8 ch_3080;
static s32 ch_307C;
static u8 ch_fill307B;
static u8 ch_fill307A;
static u8 ch_fill3079;
static u8 ch_3078;
static u8 ch_3070[0x8];
// POOL END

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
extern u32 lbl_1_bss_5F6C;
extern u8 lbl_1_bss_6940[];
typedef struct { void* data; u32 pad4; u32 pad8; } ChallengeEntry;

extern void LITXForm(void* light, void* matrix);

extern u8 lbl_1_bss_5F74[];
extern u8 lbl_1_bss_5F78;

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
    lbl_1_bss_5F78 ^= 1;
    fn_800B9A9C(lbl_1_bss_5F78, (*(f32*)lbl_1_bss_5F74));
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

// fn_1_16400, size:0x4C
void fn_1_16400(s8 arg) {
    u8* base = lbl_8036E548;
    u8* row;
    u32 mod;
    base += ch_5F73 * 0x27C;
    row = *(u8**)(base + 0xC08);
    mod = *(u16*)(row + 0x6);
    ch_5F6C = (ch_5F6C + mod + arg) % mod;
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

typedef struct {
    f32 position;
    u8 padding04[8];
    void* track;
} ChallengeAnimation;

typedef struct {
    u8 padding[0xE8];
    ChallengeAnimation* animation;
} ChallengeAnimationNode;

typedef struct {
    u8 padding00[6];
    u16 count;
    u8 padding08[0x10];
    ChallengeAnimationNode** nodes;
} ChallengeAnimationModel;

typedef struct {
    u8 padding00[0x34];
    ChallengeAnimationModel* model;
    u8 padding38[0x58];
} ChallengeRenderObject;

// .text:0xD71C size:0x88
f32 fn_1_D71C(s32 index) {
    s32 current;
    ChallengeRenderObject* objects;
    s32 count;
    ChallengeAnimationModel* model;
    objects = *(ChallengeRenderObject**)(lbl_8036E548 + 0x60);
    model = objects[index].model;
    count = model->count;
    for (current = 0; current < count; current++) {
        ChallengeAnimation* animation = model->nodes[current]->animation;
        if (animation != NULL && animation->track != NULL) {
            break;
        }
    }
    if (current < count) {
        return model->nodes[current]->animation->position;
    }
    return 0.0f;
}

typedef struct { s32 words[3]; } ChallengeCommand;
extern const ChallengeCommand lbl_1_rodata_7344;
extern s32 lbl_1_data_F2A0;

// .text:0xF040 size:0x90
void fn_1_F040(void) {
    ChallengeCommand command;
    u8* challenge = lbl_1_bss_3070;
    u16 buttons;
    command = lbl_1_rodata_7344;
    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 0x100) {
        lbl_1_data_F2A0 = *(s32*)(challenge + 0x28);
        fn_8002955C(&command, 0, &lbl_1_data_F2A0);
    } else if (buttons & 0x200) {
        *(s32*)(challenge + 0xC) = 0;
        challenge[0x2F01] = 10;
    }
}

extern ChallengeCommand lbl_1_rodata_731C;
extern u8 lbl_1_data_F0A8[];
extern s32 lbl_1_data_F0BC;
extern void fn_1_F798(void*, void*, s32);

// .text:0xF6E4 size:0xB4
void fn_1_F6E4(void) {
    ChallengeCommand command;
    s32* parameters = &lbl_1_data_F0BC;
    u8* challenge = lbl_1_bss_3070;
    u16 buttons;
    command = lbl_1_rodata_731C;
    fn_1_F798(parameters, lbl_1_data_F0A8, 12);
    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 0x100) {
        *parameters = *(s32*)(challenge + 0x28);
        fn_80031CA4((Vec*)&command, (u32*)parameters);
    } else if (buttons & 0x200) {
        *(s32*)(challenge + 0xC) = 0;
        challenge[0x2F01] = 10;
    }
}

extern const f32 lbl_1_rodata_7430;
extern const f32 lbl_1_rodata_73F8;
extern f32 lbl_1_rodata_73BC;
extern const f32 lbl_1_rodata_7394;

#pragma fp_contract off
// .text:0x160F8 size:0xD8
void fn_1_160F8(s32 direction) {
    f32 step = lbl_1_rodata_7430;
    f32 value;
    if (*(u16*)&lbl_803C77B8 & 0x400) {
        step *= lbl_1_rodata_73F8;
    }
    step *= (f32)direction;
    value = (*(f32*)lbl_1_bss_5F74) + step;
    (*(f32*)lbl_1_bss_5F74) = value;
    if (value > lbl_1_rodata_73BC) {
        (*(f32*)lbl_1_bss_5F74) = lbl_1_rodata_7394;
    }
    if ((*(f32*)lbl_1_bss_5F74) < lbl_1_rodata_7394) {
        (*(f32*)lbl_1_bss_5F74) = lbl_1_rodata_73BC;
    }
    fn_800B9A9C(lbl_1_bss_5F78, (*(f32*)lbl_1_bss_5F74));
}

#pragma fp_contract on

extern const f32 lbl_1_rodata_73C8;
extern s32 getAnimRelatedCoordinates(s32, s32, void*);

// .text:0xD4BC size:0xD4
void fn_1_D4BC(void) {
    Vec coordinates;
    u8* scene = lbl_8036E548;
    u8* object = scene + 0xC04;
    if (object != NULL) {
        object[0x276] = (s32)object[0x276] >> 1;
        object[0x276] = (object[0x276] * 8) & 0xF8;
        getAnimRelatedCoordinates(0, 0x1E, &coordinates);
        if (*(f32*)(object + 0x38) - coordinates.y < lbl_1_rodata_73C8) {
            object[0x276] |= 2;
        }
        getAnimRelatedCoordinates(0, 0x22, &coordinates);
        if (*(f32*)(object + 0x38) - coordinates.y < lbl_1_rodata_73C8) {
            object[0x276] |= 4;
        }
    }
    object = *(u8**)(scene + 0x2C50);
    object[0x276] |= 1;
}

extern s32* lbl_1_data_F278[];
extern u8 lbl_1_data_F284[];
extern void fn_1_F1D8(void*);

// .text:0xF0D0 size:0x108
void fn_1_F0D0(void) {
    u8* challenge = lbl_1_bss_3070;
    u16 buttons;
    fn_1_F798(lbl_1_data_F278[*(s32*)(challenge + 0x38)], lbl_1_data_F284, 16);
    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 0x1000) {
        *(s32*)(challenge + 0x38) = (*(s32*)(challenge + 0x38) + 1) % 3;
    } else if (*(u16*)((u8*)&lbl_803C77B8) & 0x100) {
        if (*(u16*)((u8*)&lbl_803C77B8 + 2) & 0x100) {
            u8* queue;
            s32 resource = *(s32*)(challenge + 0x28);
            *lbl_1_data_F278[2] = resource;
            *lbl_1_data_F278[1] = resource;
            *lbl_1_data_F278[0] = resource;
            queue = fn_800B0A5C_insertQueue((void*)fn_1_F1D8, 0);
            *(s32*)(queue + 0x20) = 240;
            *(s32*)(queue + 0x24) = 4;
        }
    } else if (buttons & 0x200) {
        *(s32*)(challenge + 0xC) = 0;
        challenge[0x2F01] = 10;
    }
}

extern u8 lbl_1_bss_5F69;
extern f32 lbl_1_rodata_73C0[];
extern f32 lbl_1_rodata_73C4[];
extern f32 lbl_1_rodata_73A4[];
extern f32 lbl_1_data_F568[];

// .text:0xCCC8 size:0x100
void fn_1_CCC8(void) {
    u8* queue = lbl_803CC1B8[0];
    f32* animation = *(f32**)(queue + 0x14);
    if (animation != NULL && animation[0] < animation[1]) {
        if (lbl_1_bss_5F69 != 0) {
            fn_800385F0(lbl_1_bss_30C0, lbl_1_rodata_73BC, lbl_1_rodata_73C0[0], lbl_1_rodata_73C4[0], lbl_1_rodata_73BC);
        } else {
            fn_800385F0(lbl_1_bss_30C0, lbl_1_rodata_73A4[0], lbl_1_rodata_73C0[0], lbl_1_rodata_73C4[0], lbl_1_rodata_73BC);
        }
        *(f32*)(lbl_1_bss_30C0 + 0x50) = lbl_1_data_F568[0];
        fn_800B0A14_removeQueue(fn_80037AA0(lbl_1_bss_30C0, 0, (void*)fn_1_CB9C, *(u16*)(queue + 0x18), *(void**)(queue + 0x14)));
    }
}

// .text:0x16590 size:0x50
void* fn_1_16590(void) {
    u32 scene = lbl_1_bss_5F73[0];
    u8* base = lbl_8036E548;
    u8* table;
    u8* row;
    base += scene * 0x27C;
    row = base; row += lbl_1_bss_6940[scene * 0x48 + 0x44] * 4; table = *(u8**)(row + 0xC14);
    table = *(u8**)(table + 4);
    return ((ChallengeEntry*)table)[lbl_1_bss_6940[scene * 0x48 + 0x45]].data;
}

#include "Dolphin/OS/OSUtil.h"
extern s32 lbl_1_bss_3084[];
extern void fn_1_135C0(void);
extern void fn_1_1770C(u8* object);

// .text:0x168C8 size:0xB0
void fn_1_168C8(void) {
    u8* queue = lbl_803CC1B8[0];
    if (lbl_1_bss_3084[0] == 0) {
        lbl_1_bss_3084[0] = 1;
        *(u32*)(queue + 0x1C) = OSGetTick();
        fn_1_135C0();
        *(u32*)(queue + 0x1C) = OSGetTick() - *(u32*)(queue + 0x1C);
    } else {
        lbl_1_bss_3084[0] = 0;
        *(s16*)(queue + 0x10) = 0;
        if (*(u32*)(*(u8**)(lbl_8036E548 + 0xC0C) + 0x10) != 0) {
            *(void (**)(u8*))lbl_803CC1B8[0] = fn_1_1770C;
        } else {
            *(void (**)(u8*))lbl_803CC1B8[0] = fn_1_1770C;
        }
    }
}

extern u8 lbl_803C6CF8[];
extern u8 lbl_1_data_A940[];
extern u8 lbl_1_data_ADE0[];

// .text:0x10560 size:0x110
void fn_1_10560(void* object) {
    u8* state = lbl_1_bss_3070;
    switch (*(s16*)(lbl_803CC1B8[0] + 0x10)) {
    case 0:
        *(void**)(state + 0x24) = (void*)ARAMTransfer(lbl_1_data_ADE0, 0, 0, 0);
        *(s16*)(lbl_803CC1B8[0] + 0x10) = 1;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            u8* data = *(u8**)(state + 0x24);
            *(u8**)(state + 0x28) = data + *(u32*)data;
            convertTextureHeader(*(u8**)(state + 0x28));
            *(s32*)(state + 0x3074) = ARAMTransfer(lbl_1_data_A940, 0, 1, 0);
            *(s16*)(lbl_803CC1B8[0] + 0x10) = 2;
        }
        break;
    case 2:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            convertTextureHeader(*(void**)(state + 0x3074));
            ((void (*)(void))fn_800B0A14_removeQueue)();
        }
        break;
    }
}

typedef struct { u8 b[0x38]; } Ch38;
extern u8 lbl_1_data_AA54[];
extern u8 lbl_1_data_AAC4[];
extern u8 lbl_1_data_AB34[];
extern void fn_1_179CC(void);
extern void fn_1_129D0(void);

// .text:0xD8A0 size:0x118
void fn_1_D8A0(void) {
    Mtx44 projection;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_1_179CC();
    PSMTXCopy((f32(*)[4])ch_67E0, (f32(*)[4])(ch_68FC + 0x10));
    ((void (*)(s32, void*))fn_800A7D4C)(7, lbl_1_data_AA54 + lbl_803CBBC0[0] * 0x38);
    if (ch_3078 != 0) {
        ((void (*)(s32, void*))fn_800A7D4C)(7, lbl_1_data_AB34 + lbl_803CBBC0[0] * 0x38);
    }
    ((void (*)(s32, void*))fn_800A7D4C)(7, lbl_1_data_AAC4 + lbl_803CBBC0[0] * 0x38);
    fn_1_129D0();
}

extern u16 lbl_1_data_F56C;
extern u16 lbl_1_data_F56E;

// .text:0xCC24 size:0xA4
void fn_1_CC24(void) {
    u8* object;
    if (ch_30BC == 0) {
        ch_30BC = 1;
        object = fn_800B0A5C_insertQueue((void*)fn_1_CCC8, (u16)(*(u16*)(lbl_803CC1B8[0] + 0x12) + 1));
        if (ch_5F69 != 0) {
            *(s32*)(object + 0x14) = ch_67B8[1];
            *(u16*)(object + 0x18) = lbl_1_data_F56C;
        } else {
            *(s32*)(object + 0x14) = ch_67B8[2];
            *(u16*)(object + 0x18) = lbl_1_data_F56E;
        }
    }
}

#include "C3/control.h"
extern void fn_80030D88(Vec*, Vec*, void*, s32);

// .text:0xF1D8 size:0x120
void fn_1_F1D8(void* unused) {
    Control control;
    Mtx matrix;
    Vec coordinates;
    Vec direction;
    u8* queue = lbl_803CC1B8[0];
    u8* object = ((u8**)(lbl_8036E548 + 0x2C50))[lbl_1_bss_5F73[0]];
    getAnimRelatedCoordinates(0, *(s32*)(queue + 0x24), &coordinates);
    control.type = 0;
    CTRLSetRotation(&control, *(f32*)(object + 0x40), *(f32*)(object + 0x44), *(f32*)(object + 0x48));
    CTRLBuildMatrix(&control, matrix);
    direction.x = lbl_1_rodata_7394;
    direction.z = lbl_1_rodata_73BC;
    direction.y = lbl_1_rodata_7394;
    PSMTXMultVec(matrix, &direction, &direction);
    fn_80030D88(&coordinates, &direction, lbl_1_data_F278[0], 5);
    fn_80030D88(&coordinates, &direction, lbl_1_data_F278[1], 5);
    fn_80030D88(&coordinates, &direction, lbl_1_data_F278[2], 5);
    if (--*(s32*)(queue + 0x20) == 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

extern void fn_8004B208(s32, s32, s32);

// .text:0xD590 size:0xA8
void fn_1_D590(s32 a, s32 b, f32 value) {
    u8* state = lbl_1_bss_3070;
    if (state[0x1A5] == 0 || state[0x1A6] == 0) return;
    if (state[0x1A6] == 2) {
        if ((s32)value == 0) {
            state[0x1A4] += (state[0x1A4] != 0);
        }
        if (state[0x1A4] == 3) state[0x1A4] = 0;
        if (state[0x1A4] == 2) goto call;
    } else {
call:
        fn_8004B208(a, b, (s8)state[0x2EF2] & ~((s8)state[0x2EF2] >> 31));
    }
}

typedef struct { s16 v; u8 pad[6]; } Ch8;
extern Ch8 lbl_1_bss_3218[];
extern void fn_1_D9B8(void);
extern void fn_1_DF14(void);

// .text:0xDE1C size:0xF8
void fn_1_DE1C(void) {
    u8* queue = lbl_803CC1B8[0];
    switch (queue[0x14]) {
    case 0:
        if ((s8)queue[0x15] == 0) {
            *(void**)queue = (void*)fn_1_D9B8;
        } else {
            u8 n;
            while ((s8)(n = queue[0x15]--) != 0) {
                if (lbl_1_bss_3218[(s8)queue[0x15]].v >= 0) {
                    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_DF14, (u16)(*(u16*)(lbl_803CC1B8[0] + 0x12) + 1));
                    *(s16*)(object + 0x10) = 0;
                    object[0x14] = queue[0x15];
                    *(s16*)(queue + 0x10) = 0;
                    queue[0x14] = queue[0x14] + 1;
                    break;
                }
            }
        }
        break;
    case 1:
        if (*(s16*)(queue + 0x10) != 0) queue[0x14] = 0;
        break;
    }
    ((void (*)(void))fn_1_D8A0)();
}

extern u8* lbl_1_data_F4D4[];

// .text:0xD7A4 size:0xFC
void fn_1_D7A4(s32 index) {
    u8* src;
    u8* dst;
    u8* base;
    s32 n;
    src = lbl_1_data_F4D4[1] + index * 0x50 + 0x40;
    dst = (u8*)lbl_1_bss_3218 + 0x40;
    base = lbl_8036E548 + lbl_1_bss_5F73[0] * 0x27C;
    n = 8;
    while ((src -= 8, dst -= 8, n-- != 0)) {
        if ((s8)src[0x10] != 0) {
            u8* table;
            s16 a = *(s16*)(src + 0x12);
            s16 b;
            s16 c;
            *(s16*)dst = a;
            table = *(u8**)(base + a * 4 + 0xC14);
            b = *(s16*)(src + 0x14);
            *(s16*)(dst + 2) = b;
            *(s16*)(dst + 6) = (s8)src[0x11];
            c = *(s16*)(src + 0x16);
            if (c == -2) {
                if (table != NULL) {
                    *(s16*)(dst + 4) = (s32) **(f32**)(*(u8**)(table + 4) + b * 0xC + 4);
                } else {
                    *(s16*)(dst + 4) = 0;
                }
            } else {
                *(s16*)(dst + 4) = c;
            }
        } else {
            *(s16*)dst = -1;
            *(s16*)(dst + 6) = 0;
            *(s16*)(dst + 4) = 0;
        }
    }
}

extern u8 lbl_1_data_ABA8;
extern void fn_1_10E2C(void*, f32(*)[4], u32, u32, u32);
extern void fn_800B2C88(void*, u16, void*);

// .text:0x10CEC size:0x140
void fn_1_10CEC(u8* object) {
    u8 buffer[0x30];
    Mtx matrix;
    u8* state = lbl_1_bss_3070;
    u8* scene;
    s32 i;
    s32 k;
    u32 a;
    u32 b;
    u32 c;
    if (lbl_1_data_ABA8 == 0) {
        u8* row = lbl_8036E548 + state[0x2F03] * 0x27C;
        PSMTXTrans(matrix, *(f32*)(row + 0xC38), *(f32*)(row + 0xC3C), *(f32*)(row + 0xC40));
        PSMTXConcat((f32(*)[4])(object + 8), matrix, matrix);
        scene = lbl_8036E548;
        for (i = 0; k = state[0x2F03] * 0x90, i < *(u16*)(*(u8**)(*(u8**)(scene + 0x60) + k + 0x34) + 6); i++) {
            if ((u32)i != *(u32*)(state + 0x2EFC)) {
                a = 0x80008080;
                b = 0x80800080;
                c = 0x808080;
            } else {
                u8 f = state[0x20];
                state[0x20] = f + 1;
                if (f & 0x20) {
                    a = 0xFF8080FF;
                    b = 0x80FF80FF;
                    c = 0x8080FFFF;
                } else {
                    a = -1;
                    b = -1;
                    c = -1;
                }
            }
            fn_800B2C88(*(u8**)(*(u8**)(scene + 0x60) + k + 0x34), (u16)i, buffer);
            fn_1_10E2C(buffer, matrix, a, b, c);
        }
    }
}

// .text:0xE8D4 size:0x124
void fn_1_E8D4(void) {
    u8* src;
    s32 n;
    u8* dst;
    u8* base;
    src = lbl_1_data_F4D4[1] + 0x40;
    n = 8;
    dst = (u8*)lbl_1_bss_3218 + 0x40;
    base = lbl_8036E548 + lbl_1_bss_5F73[0] * 0x27C;
    while ((src -= 8, dst -= 8, n-- != 0)) {
        if ((s8)src[0x10] != 0) {
            u8* table;
            s16 a = *(s16*)(src + 0x12);
            s16 b;
            s16 c;
            *(s16*)dst = a;
            table = *(u8**)(base + a * 4 + 0xC14);
            b = *(s16*)(src + 0x14);
            *(s16*)(dst + 2) = b;
            *(s16*)(dst + 6) = (s8)src[0x11];
            c = *(s16*)(src + 0x16);
            if (c == -2) {
                if (table != NULL) {
                    *(s16*)(dst + 4) = (s32) **(f32**)(*(u8**)(table + 4) + b * 0xC + 4);
                } else {
                    *(s16*)(dst + 4) = 0;
                }
            } else {
                *(s16*)(dst + 4) = c;
            }
        } else {
            *(s16*)dst = -1;
            *(s16*)(dst + 6) = 0;
            *(s16*)(dst + 4) = 0;
        }
    }
    while ((s8)lbl_1_data_F4D4[1][*(s16*)lbl_1_data_F4D4 * 0x50] != 0) {
        *(s16*)lbl_1_data_F4D4 += 1;
    }
}

extern void fn_1_17B5C(void);

// .text:0x17D90 size:0x124
void fn_1_17D90(void) {
    s32 n;
    u8* src;
    u8* dst;
    u8* base;
    fn_800AD038(lbl_80366158[2]);
    *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
    *(void (**)(void))(lbl_803CC1B8[0]) = fn_1_17B5C;
    src = lbl_1_data_F4D4[1] + 0x40;
    n = 8;
    dst = (u8*)lbl_1_bss_3218 + 0x40;
    base = lbl_8036E548 + lbl_1_bss_5F73[0] * 0x27C;
    while ((src -= 8, dst -= 8, n-- != 0)) {
        if ((s8)src[0x10] != 0) {
            u8* table;
            s16 a = *(s16*)(src + 0x12);
            s16 b;
            s16 c;
            *(s16*)dst = a;
            table = *(u8**)(base + a * 4 + 0xC14);
            b = *(s16*)(src + 0x14);
            *(s16*)(dst + 2) = b;
            *(s16*)(dst + 6) = (s8)src[0x11];
            c = *(s16*)(src + 0x16);
            if (c == -2) {
                if (table != NULL) {
                    *(s16*)(dst + 4) = (s32) **(f32**)(*(u8**)(table + 4) + b * 0xC + 4);
                } else {
                    *(s16*)(dst + 4) = 0;
                }
            } else {
                *(s16*)(dst + 4) = c;
            }
        } else {
            *(s16*)dst = -1;
            *(s16*)(dst + 6) = 0;
            *(s16*)(dst + 4) = 0;
        }
    }
    while ((s8)lbl_1_data_F4D4[1][*(s16*)lbl_1_data_F4D4 * 0x50] != 0) {
        *(s16*)lbl_1_data_F4D4 += 1;
    }
}

// fn_1_10458, size:0x108
void fn_1_10458(void) {
    u8* state = lbl_1_bss_3070;
    s32 cursor;
    s32 buttons;
    if (*(u32*)(state + 0x28) == 0) {
        if (*(u32*)(state + 0x24) == 0) {
            u8* object = fn_800B0A5C_insertQueue((void*)fn_1_10560, 11);
            *(s16*)(object + 0x10) = 0;
        }
        return;
    }
    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 8) {
        cursor = *(s32*)(state + 0xC);
        if (cursor != 0) {
            *(s32*)(state + 0xC) = cursor - 1;
        } else {
            *(s32*)(state + 0xC) = 6;
        }
        return;
    }
    if (buttons & 4) {
        cursor = *(s32*)(state + 0xC) + 1;
        *(s32*)(state + 0xC) = cursor;
        if (cursor == 7) {
            *(s32*)(state + 0xC) = 0;
        }
        return;
    }
    if (!(buttons & 1) && !(buttons & 2)) {
        if (buttons & 0x100) {
            state[0x2F01] += *(s32*)(state + 0xC) + 1;
            *(s32*)(state + 0xC) = 0;
            return;
        }
        if (buttons & 0x200) {
            *(s32*)(state + 0xC) = 0;
            state[0x2F01] = 1;
        }
    }
}

extern void fn_1_ECF8(u8, u8, u8);

typedef struct { u8 pad : 3; u8 mode : 2; u8 rest : 3; } ChallengeFlagBits;

// .text:0x1644C size:0x10C
void fn_1_1644C(void) {
    u32 entry;
    s32 i;
    u8** p;
    entry = *(u32*)(lbl_8036E548 + ch_5F73 * 4 + 0x2C50);
    ch_5F69 = ch_5F69 ^ 1;
    if (entry != 0) {
        u8* slot = *(u8**)(lbl_8036E548 + 0x60) + ch_5F73 * 0x90 + 0x34;
        if (ch_5F69 == 0) {
            *(u32*)(slot + 0x68) = 0;
        } else {
            *(u32*)(slot + 0x68) = entry + 0x72;
        }
        fn_1_ECF8(ch_5F73, (ch_6940 + ch_5F73 * 0x48)[0x44], ch_5F69);
        p = (u8**)ch_67B8;
        for (i = 0; i < 4; i++) {
            if (p[i] != NULL) ((ChallengeFlagBits*)(p[i] + 0x11))->mode = 3;
        }
    }
}

extern const f32 lbl_1_rodata_7480;
extern const f32 lbl_1_rodata_7484;
extern const f32 lbl_1_rodata_7488;
extern const f32 lbl_1_rodata_748C;
extern const f32 lbl_1_rodata_7490;
extern const f32 lbl_1_rodata_7494;
extern const f32 lbl_1_rodata_7498;
extern const f32 lbl_1_rodata_749C;

// .text:0x1347C size:0x144
void fn_1_1347C(void) {
    Mtx44 projection;
    *(f32*)(ch_67E0 + 0x108) = lbl_1_rodata_7394;
    *(f32*)(ch_67E0 + 0x10C) = lbl_1_rodata_7480;
    *(f32*)(ch_67E0 + 0x110) = lbl_1_rodata_7394;
    *(f32*)(ch_67E0 + 0xFC) = lbl_1_rodata_7394;
    *(f32*)(ch_67E0 + 0x100) = lbl_1_rodata_7394;
    *(f32*)(ch_67E0 + 0x104) = lbl_1_rodata_73F8;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_7484, lbl_1_rodata_7488, lbl_1_rodata_748C, lbl_1_rodata_7490,
                lbl_1_rodata_7494, lbl_1_rodata_7498, lbl_1_rodata_749C);
    *(s32*)(ch_67E0 + 0x114) = 0;
    *(f32*)(ch_67E0 + 0xF8) = lbl_1_rodata_7394;
    *(s16*)(ch_67E0 + 0xF0) = 0;
    *(s16*)(ch_67E0 + 0xF2) = 0;
}

typedef struct { u16 a; u16 b; } ChPair;
extern ChPair lbl_1_data_1DC0[];
extern ChPair lbl_1_data_1E18[];

// .text:0x14710 size:0x174
void fn_1_14710(u8* object) {
    s32 i;
    s32 k;
    ChPair* p;
    ChPair* q;
    s32 mode;
    u16 x;
    u16 y;
    for (i = 0; i < 0x78; i++) {
        ((u16*)object)[i + 0x39] = i;
    }
    k = 0;
    p = lbl_1_data_1DC0;
    do {
        x = *(u16*)(object + p->a * 2 + 0x162);
        y = *(u16*)(object + p->b * 2 + 0x162);
        if (x != 0xFFFF && y != 0xFFFF) {
            *(u16*)(object + x * 2 + 0x72) = y;
            *(u16*)(object + y * 2 + 0x72) = x;
        }
        k += 4;
        p = (ChPair*)((u8*)p + 4);
    } while (((u16*)lbl_1_data_1DC0)[k / 2] != 0xFFFF);
    mode = (lbl_1_bss_68FC + lbl_1_bss_5F73[0])[0x40];
    if (mode < 0x2C) {
        if (mode == 0x10) goto yes;
        goto no;
    }
    if (mode >= 0x30) goto no;
yes:
    q = lbl_1_data_1E18;
    goto done;
no:
    q = NULL;
done:
    if (q != NULL) {
        ChPair* r = q;
        for (; r->a != 0xFFFF; r++) {
            u16 x = *(u16*)(object + r->a * 2 + 0x162);
            u16 y = *(u16*)(object + r->b * 2 + 0x162);
            if (x != 0xFFFF && y != 0xFFFF) {
                *(u16*)(object + x * 2 + 0x72) = y;
                *(u16*)(object + y * 2 + 0x72) = x;
            }
        }
    }
}

#include <string.h>
extern void fn_1_107B8(void);

// .text:0xDF14 size:0x184
void fn_1_DF14(void) {
    u8* queue = lbl_803CC1B8[0];
    s16 state = *(s16*)(queue + 0x10);
    s32 idx = queue[0x14];
    u8** p;
    u8* q;
    u8* r;
    s32 n;
    switch (state) {
    case 0:
        {
            s16* e = (s16*)ch_3218;
            (ch_6940 + ch_5F73 * 0x48)[0x44] = *(s16*)(ch_3218 + idx * 8);
            (ch_6940 + ch_5F73 * 0x48)[0x45] = e[idx * 4 + 1];
        }
        fn_800B0A5C_insertQueue((void*)fn_1_107B8, 0xFF);
        ch_5F5C = 2;
        *(s16*)(lbl_803CC1B8[0] + 0x10) += 1;
        break;
    case 1:
        if (ch_5F5C == 0) {
            p = (u8**)ch_67B8 + 5;
            q = ch_3258 + idx * 0xA0 + 0xA0;
            r = ch_3758 + idx * 0x500 + 0x500;
            n = 5;
            while ((p--, q -= 0x20, r -= 0x100, n-- != 0)) {
                if (*p != NULL) {
                    memcpy(q, *p, 0x20);
                    *(u8**)(q + 0x1C) = r;
                    memcpy(r, *(void**)(*p + 0x1C), *(u16*)(*p + 0x1A) * 4);
                } else {
                    memset(q, 0, 0x20);
                }
            }
            {
                u8* o = *(u8**)(lbl_803CC1B8[0] + 0xC);
                *(s16*)(o + 0x10) = 1;
                fn_800B0A14_removeQueue(o);
            }
        }
        break;
    }
}

extern u8 lbl_1_data_F10C[];
extern u8* lbl_1_data_F174[];
extern const f32 lbl_1_rodata_73FC;
extern void fn_1_F50C(void);

// .text:0xF37C size:0x190
void fn_1_F37C(void) {
    u8* state = lbl_1_bss_3070;
    u8* pad;
    u8* object;
    fn_1_F798(lbl_1_data_F10C, lbl_1_data_F0A8, 0x12);
    pad = (u8*)&lbl_803C77B8;
    if (*(u16*)(pad + 4) & 0x1100) {
        *(u32*)lbl_1_data_F10C = *(u32*)(state + 0x28);
        *(u32*)lbl_1_data_F174[0] = *(u32*)(state + 0x28);
        *(u32*)(lbl_1_data_F174[0] + 4) = 5;
        object = fn_800B0A5C_insertQueue((void*)fn_1_F50C, (u16)(*(u16*)(lbl_803CC1B8[0] + 0x12) + 1));
        *(f32*)(object + 0x18) = lbl_1_rodata_7394;
        *(f32*)(object + 0x14) = lbl_1_rodata_7394;
        *(f32*)(object + 0x1C) = lbl_1_rodata_73F8;
        *(f32*)(object + 0x20) = lbl_1_rodata_7394;
        *(f32*)(object + 0x24) = lbl_1_rodata_7394;
        *(f32*)(object + 0x28) = (f32) * (s32*)(lbl_1_data_F10C + 0x5C) / lbl_1_rodata_73FC;
        *(f32*)(object + 0x2C) = lbl_1_rodata_7394;
        *(f32*)(object + 0x30) = lbl_1_rodata_7394;
        *(f32*)(object + 0x34) = (f32) * (s32*)(lbl_1_data_F10C + 0x60) / lbl_1_rodata_73FC;
        *(s16*)(object + 0x3C) = 0x20;
        object[0x3E] = 1;
        *(u32*)(object + 0x38) = *(u16*)(state + 0x34);
        *(u16*)(state + 0x34) = *(u16*)(state + 0x34) + 2;
        object[0x3F] = (*(u16*)(pad + 4) >> 12) & 1;
        return;
    }
    if (*(u16*)(pad + 4) & 0x200) {
        *(u32*)(state + 0xC) = 0;
        state[0x2F01] = 10;
    }
}

extern void fn_8002F258(void*, s32, void*);
extern void fn_8002F1AC(void*, s32);

// .text:0xF50C size:0x1D8
void fn_1_F50C(void) {
    Vec coordinates;
    u8* queue = lbl_803CC1B8[0];
    u8* row = lbl_8036E548 + lbl_1_bss_5F73[0] * 0x27C + 0xC04;
    if (row != NULL) {
        *(f32*)(row + 0x34) = *(f32*)(queue + 0x14);
        *(f32*)(row + 0x38) = *(f32*)(queue + 0x18);
        *(f32*)(row + 0x3C) = *(f32*)(queue + 0x1C);
    }
    fn_80030D88((Vec*)(queue + 0x14), (Vec*)(queue + 0x20), lbl_1_data_F10C, 5);
    if (queue[0x3E] != 0) {
        queue[0x3E] = 0;
        if (queue[0x3F] != 0) {
            getAnimRelatedCoordinates(0, 0x1E, &coordinates);
            coordinates.y = lbl_1_rodata_7394;
            fn_8002F258(&coordinates, *(s32*)(queue + 0x38), lbl_1_data_F174[0]);
            getAnimRelatedCoordinates(0, 0x22, &coordinates);
            coordinates.y = lbl_1_rodata_7394;
            fn_8002F258(&coordinates, *(s32*)(queue + 0x38) + 1, lbl_1_data_F174[0]);
        } else {
            fn_8002F258(queue + 0x14, *(s32*)(queue + 0x38), lbl_1_data_F174[0]);
        }
    } else if (queue[0x3F] != 0) {
        getAnimRelatedCoordinates(0, 0x1E, &coordinates);
        coordinates.y = lbl_1_rodata_7394;
        fn_8002F1AC(&coordinates, *(s32*)(queue + 0x38));
        getAnimRelatedCoordinates(0, 0x22, &coordinates);
        coordinates.y = lbl_1_rodata_7394;
        fn_8002F1AC(&coordinates, *(s32*)(queue + 0x38) + 1);
    } else {
        fn_8002F1AC(queue + 0x14, *(s32*)(queue + 0x38));
    }
    PSVECAdd((Vec*)(queue + 0x20), (Vec*)(queue + 0x2C), (Vec*)(queue + 0x20));
    PSVECAdd((Vec*)(queue + 0x20), (Vec*)(queue + 0x14), (Vec*)(queue + 0x14));
    *(s16*)(queue + 0x3C) = *(u16*)(queue + 0x3C) - 1;
    if (*(u16*)(queue + 0x3C) == 0) {
        ((void (*)(void))fn_800B0A14_removeQueue)();
    }
}

// .text:0x1620C size:0x1F0
void fn_1_1620C(void) {
    s32 i = 0;
    do {
        u8* row = lbl_8036E548 + i * 0x27C;
        *(f32*)(row + 0xC38) = 0.0f;
        *(f32*)(row + 0xC3C) = 0.0f;
        *(f32*)(row + 0xC40) = lbl_1_rodata_73F8;
        *(f32*)(row + 0xC44) = 0.0f;
        *(f32*)(row + 0xC48) = 0.0f;
        *(f32*)(row + 0xC4C) = 0.0f;
        CTRLSetTranslation((Control*)(*(u8**)(lbl_8036E548 + 0x60) + i * 0x90 + 0x44), 0.0f, 0.0f, 0.0f);
        CTRLSetRotation((Control*)(*(u8**)(lbl_8036E548 + 0x60) + i * 0x90 + 0x44), 0.0f, 0.0f, 0.0f);
        i++;
    } while (i < 1);
    fn_1_1347C();
}

// .text:0x151F8 size:0x214
void fn_1_151F8(void) {
    u8* state = lbl_1_bss_3070;
    u8* pad = (u8*)&lbl_803C77B8;
    u16 buttons = *(u16*)(pad + 4);
    s32 cursor;
    f32 step;
    f32 value;
    if (buttons & 8) {
        cursor = *(s32*)(state + 0xC) - 1;
        *(s32*)(state + 0xC) = cursor;
        if (cursor < 0) {
            *(s32*)(state + 0xC) = 1;
        }
    } else if (buttons & 4) {
        cursor = *(s32*)(state + 0xC) + 1;
        *(s32*)(state + 0xC) = cursor;
        if (cursor >= 2) {
            *(s32*)(state + 0xC) = 0;
        }
    } else if (buttons & 1) {
        switch (*(s32*)(state + 0xC)) {
        case 0:
            state[0x2F08] ^= 1;
            fn_800B9A9C(state[0x2F08], *(f32*)(state + 0x2F04));
            break;
        case 1:
            step = lbl_1_rodata_7430;
            if (*(u16*)pad & 0x400) {
                step = step * lbl_1_rodata_73F8;
            }
            step = step * lbl_1_rodata_73A4[0];
            value = *(f32*)(state + 0x2F04) + step;
            *(f32*)(state + 0x2F04) = value;
            if (value > lbl_1_rodata_73BC) {
                *(f32*)(state + 0x2F04) = lbl_1_rodata_7394;
            }
            if (*(f32*)(state + 0x2F04) < lbl_1_rodata_7394) {
                *(f32*)(state + 0x2F04) = lbl_1_rodata_73BC;
            }
            fn_800B9A9C(state[0x2F08], *(f32*)(state + 0x2F04));
            break;
        }
    } else if (buttons & 2) {
        switch (*(s32*)(state + 0xC)) {
        case 0:
            state[0x2F08] ^= 1;
            fn_800B9A9C(state[0x2F08], *(f32*)(state + 0x2F04));
            break;
        case 1:
            step = lbl_1_rodata_7430;
            if (*(u16*)pad & 0x400) {
                step = step * lbl_1_rodata_73F8;
            }
            step = step * lbl_1_rodata_73BC;
            value = *(f32*)(state + 0x2F04) + step;
            *(f32*)(state + 0x2F04) = value;
            if (value > lbl_1_rodata_73BC) {
                *(f32*)(state + 0x2F04) = lbl_1_rodata_7394;
            }
            if (*(f32*)(state + 0x2F04) < lbl_1_rodata_7394) {
                *(f32*)(state + 0x2F04) = lbl_1_rodata_73BC;
            }
            fn_800B9A9C(state[0x2F08], *(f32*)(state + 0x2F04));
            break;
        }
    } else if (buttons & 0x200) {
        *(s32*)(state + 0xC) = 0;
        state[0x2F01] = 1;
    }
}

#include "Dolphin/gx.h"

// .text:0x10ACC size:0x220
void fn_1_10ACC(f32 (*matrix)[4], f32* position, void* unused, u8* color, f32 size) {
    GXCullMode cullMode;
    GXGetCullMode(&cullMode);
    GXLoadPosMtxImm(matrix, 0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxDesc(0xB, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxAttrFmt(0, 0xB, 1, 5, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(0, 4);
    GXSetTevOrder(0, 0xFF, 0xFF, 4);
    GXSetChanCtrl(0, 0, 1, 1, 0, 0, 2);
    GXSetChanCtrl(2, 0, 1, 1, 0, 0, 2);
    GXSetBlendMode(1, 4, 5, 3);
    GXSetCullMode(0);
    GXSetZMode(1, 7, 1);
    GXSetLineWidth(10, 0);
    GXBegin(0xA8, 0, 2);
    GXPosition3f32(position[0], position[1], position[2]);
    GXColor4u8(color[0], color[1], color[2], color[3]);
    GXPosition3f32(position[0] + size, position[1] + size, position[2] + size);
    GXColor4u8(color[0], color[1], color[2], color[3]);
    GXSetLineWidth(6, 0);
    GXSetCullMode(cullMode);
    GXSetZMode(1, 3, 1);
}

extern void fn_1_F2C(s32, s32, s32);
extern f32 lbl_1_data_F570[];

// .text:0xC9E0 size:0x1BC
void fn_1_C9E0(u8* object) {
    Mtx concat;
    Vec scaled;
    fn_1_F2C(4, 0, 0);
    PSMTXConcat((f32(*)[4])(lbl_1_bss_68FC + 0x10), (f32(*)[4])(object + 8), concat);
    GXLoadPosMtxImm(concat, 0);
    GXSetCurrentMtx(0);
    GXSetBlendMode(1, 4, 5, 0);
    GXSetZMode(1, 7, 1);
    GXBegin(0xA8, 0, 6);
    GXWGFifo.f32 = *(f32*)(lbl_1_bss_30C0 + 0xC);
    GXWGFifo.f32 = *(f32*)(lbl_1_bss_30C0 + 0x10);
    GXWGFifo.f32 = *(f32*)(lbl_1_bss_30C0 + 0x14);
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(f32*)(lbl_1_bss_30C0 + 0x0);
    GXWGFifo.f32 = *(f32*)(lbl_1_bss_30C0 + 0x4);
    GXWGFifo.f32 = *(f32*)(lbl_1_bss_30C0 + 0x8);
    GXWGFifo.u32 = 0x00FF00FF;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.u32 = 0x000000FF;
    PSVECScale((Vec*)(lbl_1_bss_30C0 + 0x128), lbl_1_data_F570[0], &scaled);
    GXWGFifo.f32 = scaled.x;
    GXWGFifo.f32 = scaled.y;
    GXWGFifo.f32 = scaled.z;
    GXWGFifo.u32 = 0x000000FF;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.f32 = 0.0f;
    GXWGFifo.u32 = 0xFFFFFFFF;
    PSVECScale((Vec*)(lbl_1_bss_30C0 + 0x140), lbl_1_data_F570[0], &scaled);
    GXWGFifo.f32 = scaled.x;
    GXWGFifo.f32 = scaled.y;
    GXWGFifo.f32 = scaled.z;
    GXWGFifo.u32 = 0xFFFFFFFF;
}

// .text:0x14FB8 size:0x1B8
void fn_1_14FB8(void) {
    u16 buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    u8* q = lbl_803CC1B8[0];

    if (buttons & 8) {
        if (q[0x20] != 0) {
            q[0x20]--;
        } else {
            q[0x20] = 8;
        }
    } else if (buttons & 4) {
        q[0x20]++;
        if (q[0x20] == 9) {
            q[0x20] = 0;
        }
    } else if (lbl_803C77B8._00 & 0x100) {
        switch (q[0x20]) {
        case 0:
            if (buttons & 0x100) lbl_1_bss_5F71 = 3;
            break;
        case 1:
            if (buttons & 0x100) lbl_1_bss_5F71 = 4;
            break;
        case 2:
            if (buttons & 0x100) lbl_1_bss_5F71 = 5;
            break;
        case 3:
            if (buttons & 0x100) lbl_1_bss_5F71 = 6;
            break;
        case 4:
            if (lbl_803C77B8._02 & 0x100) lbl_1_bss_5F71 = 2;
            break;
        case 5:
            if (lbl_803C77B8._02 & 0x100) lbl_1_bss_5F71 = 8;
            break;
        case 6:
            if (lbl_803C77B8._02 & 0x100) lbl_1_bss_5F71 = 7;
            break;
        case 7:
            if (buttons & 0x100) lbl_1_bss_5F71 = 9;
            break;
        case 8:
            if (buttons & 0x100) lbl_1_bss_5F71 = 10;
            break;
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        lbl_1_bss_5F71 = 0;
        minigamesSetSomePointers();
    }
}

extern Vec lbl_1_rodata_730C;
extern Vec lbl_1_data_AD24;
extern const f32 lbl_1_rodata_7448;
extern const f32 lbl_1_rodata_744C;
extern const f32 lbl_1_rodata_7450;
extern void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);

// .text:0x11D00 size:0x208
void fn_1_11D00(u8* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    Vec angle;
    Vec pos;

    pos = lbl_1_rodata_730C;
    if (!(lbl_803C77B8._00 & 0x10)) {
        *(u16*)(camera + 0xF0) -= ((s8*)&lbl_803C77B8)[0x13] * 4;
        *(u16*)(camera + 0xF2) += ((s8*)&lbl_803C77B8)[0x12] * 4;
        *(f32*)(camera + 0xF8) += (f32)((s8*)&lbl_803C77B8)[0x11] * lbl_1_rodata_7448;
        *(f32*)(camera + 0x100) += (f32)((u8*)&lbl_803C77B8)[0x15] * lbl_1_rodata_744C;
        *(f32*)(camera + 0x100) -= (f32)((u8*)&lbl_803C77B8)[0x14] * lbl_1_rodata_744C;
    }
    angle.x = *(u16*)(camera + 0xF0);
    angle.y = *(u16*)(camera + 0xF2);
    angle.z = lbl_1_rodata_7394;
    PSVECScale(&angle, lbl_1_rodata_7450, &angle);
    PSMTXRotRad(rotX, 'X', angle.x);
    PSMTXRotRad(rotY, 'Y', angle.y);
    PSMTXConcat(rotX, rotY, rot);
    pos.z = -*(f32*)(camera + 0xF8);
    PSMTXMultVec(rot, &pos, &pos);
    PSVECAdd(&pos, (Vec*)(camera + 0xFC), (Vec*)(camera + 0x108));
    PSMTXMultVec(rot, &lbl_1_data_AD24, &pos);
    makeLookAtMatrix((f32(*)[4])camera, (Vec*)(camera + 0x108), &pos, (Vec*)(camera + 0xFC));
}

typedef struct { u8 r, g, b, a; } ChallengeLightColor;
extern void LITAlloc(void**);
extern void LITInitAttn(void*, f32, f32, f32, f32, f32, f32);
extern void LITInitPos(void*, f32, f32, f32);
extern void LITInitDir(void*, f32, f32, f32);
extern void LITInitColor(void*, ChallengeLightColor);
extern ChallengeLightColor lbl_1_rodata_72F0;
extern const f32 lbl_1_rodata_7474;
extern const f32 lbl_1_rodata_7478;
extern const f32 lbl_1_rodata_747C;

// .text:0x131E4 size:0x298
void fn_1_131E4(void) {
    ChallengeLightColor color = lbl_1_rodata_72F0;
    void** light0;
    void** light1;
    void** light2;
    void** light3;

    light0 = (void**)(lbl_8036E548 + 0xAC);
    LITAlloc(light0);
    light1 = (void**)(lbl_8036E548 + 0xB0);
    LITAlloc(light1);
    light2 = (void**)(lbl_8036E548 + 0xB4);
    LITAlloc(light2);
    light3 = (void**)(lbl_8036E548 + 0xB8);
    LITAlloc(light3);

    LITInitAttn(*light0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light0, lbl_1_rodata_7474, lbl_1_rodata_7478, lbl_1_rodata_7474);
    LITInitDir(*light0, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light0, color);
    LITInitDir(*light0, lbl_1_rodata_747C, lbl_1_rodata_7394, lbl_1_rodata_747C);

    LITInitAttn(*light1, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light1, lbl_1_rodata_747C, lbl_1_rodata_7478, lbl_1_rodata_7394);
    LITInitDir(*light1, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light1, color);

    LITInitAttn(*light2, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light2, lbl_1_rodata_7394, lbl_1_rodata_7478, lbl_1_rodata_7474);
    LITInitDir(*light2, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light2, color);

    LITInitAttn(*light3, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(*light3, lbl_1_rodata_7394, lbl_1_rodata_7478, lbl_1_rodata_747C);
    LITInitDir(*light3, lbl_1_rodata_7394, lbl_1_rodata_7394, lbl_1_rodata_7394);
    LITInitColor(*light3, color);
}

extern Vec lbl_1_rodata_7300;
extern Vec lbl_1_data_AD18;
extern const f32 lbl_1_rodata_7454;

// .text:0x11F08 size:0x2CC
void fn_1_11F08(u8* camera) {
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    Vec angle;
    Vec pos;
    f32 c;
    f32 s;
    u8* view;

    pos = lbl_1_rodata_7300;
    if (!(lbl_803C77B8._00 & 0x10)) {
        *(u16*)(camera + 0xF0) -= ((s8*)&lbl_803C77B8)[0x13] * 4;
        *(u16*)(camera + 0xF2) += ((s8*)&lbl_803C77B8)[0x12] * 4;
        *(f32*)(camera + 0xF4) = (f32)((s8*)&lbl_803C77B8)[0x10] / lbl_1_rodata_7454;
        *(f32*)(camera + 0xF8) = (f32)((s8*)&lbl_803C77B8)[0x11] * lbl_1_rodata_7448;
        *(f32*)(camera + 0x10C) += (f32)((u8*)&lbl_803C77B8)[0x15] * lbl_1_rodata_744C;
        *(f32*)(camera + 0x10C) -= (f32)((u8*)&lbl_803C77B8)[0x14] * lbl_1_rodata_744C;
    }
    angle.x = *(u16*)(camera + 0xF0);
    angle.y = *(u16*)(camera + 0xF2);
    angle.z = lbl_1_rodata_7394;
    PSVECScale(&angle, lbl_1_rodata_7450, &angle);
    PSMTXRotRad(rotX, 'X', angle.x);
    PSMTXRotRad(rotY, 'Y', angle.y);
    s = rotY[0][2];
    c = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &pos, (Vec*)(camera + 0xFC));
    *(f32*)(camera + 0x108) += *(f32*)(camera + 0xF8) * s - *(f32*)(camera + 0xF4) * c;
    *(f32*)(camera + 0x110) += *(f32*)(camera + 0xF8) * c + *(f32*)(camera + 0xF4) * s;
    *(f32*)(camera + 0xFC) += *(f32*)(camera + 0x108);
    *(f32*)(camera + 0x100) += *(f32*)(camera + 0x10C);
    *(f32*)(camera + 0x104) += *(f32*)(camera + 0x110);
    makeLookAtMatrix((f32(*)[4])camera, (Vec*)(camera + 0x108), &lbl_1_data_AD18, (Vec*)(camera + 0xFC));
    view = (u8*)fn_80052768_getCamera(0);
    memcpy(view + 0x70, camera + 0x108, 0xC);
    memcpy(view + 0x7C, camera + 0xFC, 0xC);
}

// .text:0x165E0 size:0x2E8
void fn_1_165E0(void) {
    u8* state = lbl_1_bss_3070;
    s16 delta;
    u16 buttons;
    u8* light;

    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    delta = 0;
    light = ((u8**)(lbl_8036E548 + 0xAC))[(s8)state[0x2F00]];
    if (buttons & 1) {
        delta = -1;
    } else if (buttons & 2) {
        delta = 1;
    } else if (buttons & 8) {
        if (--*(s32*)(state + 0xC) < 0) {
            *(s32*)(state + 0xC) = 9;
        }
    } else if (buttons & 4) {
        if (++*(s32*)(state + 0xC) >= 10) {
            *(s32*)(state + 0xC) = 0;
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        state[0x2F00] = 0;
        *(s32*)(state + 0xC) = 0;
        state[0x2F01] = 1;
    }
    if (lbl_803C77B8._00 & 0x400) {
        delta *= 10;
    }
    switch (*(u32*)(state + 0xC)) {
    case 0: {
        *(s8*)(state + 0x2F00) += delta;
        if (*(s8*)(state + 0x2F00) < 0) {
            state[0x2F00] = 2;
        } else if (*(s8*)(state + 0x2F00) >= 3) {
            state[0x2F00] = 0;
        }
        break;
    }
    case 1:
        light[0x70] += delta;
        if (light[0x70] > 0xFF) {
            light[0x70] = 0;
        }
        break;
    case 2:
        light[0x71] += delta;
        if (light[0x71] > 0xFF) {
            light[0x71] = 0;
        }
        break;
    case 3:
        light[0x72] += delta;
        if (light[0x72] > 0xFF) {
            light[0x72] = 0;
        }
        break;
    case 4:
        *(f32*)(light + 0x40) += delta;
        break;
    case 5:
        *(f32*)(light + 0x44) += delta;
        break;
    case 6:
        *(f32*)(light + 0x48) += delta;
        break;
    case 7:
        *(f32*)(light + 0x58) += delta;
        break;
    case 8:
        *(f32*)(light + 0x5C) += delta;
        break;
    case 9:
        *(f32*)(light + 0x60) += delta;
        break;
    }
}

extern void fn_1_C2DC(void*, void*, s32, s32, s32, s32*, s32*, s32*);
extern void fn_800B2BA8(void*, u16, void*, u16);
extern s8 lbl_1_data_AC90;

typedef struct {
    u8 pad0[0x34];
    u8* actor;
    u8 pad38[0x58];
} ChallengeModelEntry;

// .text:0x1540C size:0x354
void fn_1_1540C(void) {
    u8 buffer[0x20];
    s32 top;
    s32 count;
    s32 selected;
    u16 buttons;
    u16 id;

    count = 0x14;
    selected = ch_5F6C;
    if (ch_3088 > selected) {
        ch_3088 = selected;
    } else if (ch_3088 < selected - 0x13) {
        ch_3088 = selected - 0x13;
    }
    top = ch_3088;
    fn_1_C2DC(**(void***)((*(ChallengeModelEntry**)(lbl_8036E548 + 0x60))[ch_5F73].actor + 0x18), buffer, 0, 0x13, 4, &selected, &top, &count);
    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 8) {
        if (--ch_307C < 0) {
            ch_307C = 5;
        }
    } else if (buttons & 4) {
        if (++ch_307C >= 6) {
            ch_307C = 0;
        }
    } else if (buttons & 1) {
        switch (ch_307C) {
        case 0:
            ch_3080 ^= 1;
            break;
        case 1:
            lbl_1_data_ABA8 ^= 1;
            break;
        case 2:
            fn_1_16400(-1);
            break;
        case 3:
            break;
        case 4:
            if (lbl_1_data_AC90 >= 0) {
                lbl_1_data_AC90--;
            }
            break;
        case 5:
            ((void (*)(void))fn_1_1644C)();
            break;
        }
    } else if (buttons & 2) {
        switch (ch_307C) {
        case 0:
            ch_3080 ^= 1;
            break;
        case 1:
            lbl_1_data_ABA8 ^= 1;
            break;
        case 2:
            fn_1_16400(1);
            break;
        case 3:
            break;
        case 4:
            if (lbl_1_data_AC90 < 4) {
                lbl_1_data_AC90++;
            }
            break;
        case 5:
            ((void (*)(void))fn_1_1644C)();
            break;
        }
    } else if (buttons & 0x200) {
        ch_307C = 0;
        ch_5F71 = 1;
    }
    id = *(u16*)(lbl_8036E548 + 0xDAE);
    if (id != 0xFFFF) {
        if (lbl_1_data_AC90 >= 0) {
            u8* actor = (*(ChallengeModelEntry**)&ch_60E0)[lbl_1_data_AC90].actor;
            s32 i;
            for (i = 0; i < *(u16*)(actor + 6); i++) {
                if (*(u32*)((*(u8***)(actor + 0x18))[i] + 0x14) != 0) {
                    fn_800B2BA8(*(void**)(*(u8**)(lbl_8036E548 + 0x60) + 0x34), id, actor, i);
                }
            }
        } else {
            fn_800B2BA8(*(void**)(*(u8**)(lbl_8036E548 + 0x60) + 0x34), id, NULL, 0);
        }
    }
}

extern s32 lbl_1_bss_307C;

// .text:0xF798 size:0x400
void fn_1_F798(void* paramsArg, void* typesArg, s32 count) {
    s32* p = paramsArg;
    u8* types = typesArg;
    s32 s;
    s32 m;
    s32 l;
    u16 buttons;
    u8 t;
    s32 v;

    if (lbl_803C77B8._00 & 0x400) {
        s = 10;
        m = 100;
        l = 10000;
    } else if (lbl_803C77B8._00 & 0x800) {
        s = 20;
        l = 1000000;
        m = 10000;
    } else {
        s = 1;
        l = 100000;
        m = 1000;
    }
    buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (buttons & 8) {
        if (lbl_1_bss_307C != 0) {
            lbl_1_bss_307C--;
        } else {
            lbl_1_bss_307C = count - 1;
        }
    } else if (buttons & 4) {
        if (++lbl_1_bss_307C == count) {
            lbl_1_bss_307C = 0;
        }
    } else if (buttons & 1) {
        t = types[lbl_1_bss_307C];
        switch (t) {
        case 0:
            break;
        case 1:
            p[t] = (p[t] + 41) % 42;
            break;
        case 2:
            p[2] -= s;
            if (p[2] < 1) {
                p[2] = 1;
            }
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            if (p[t] - m > 0) {
                p[t] -= m;
            }
            break;
        case 6:
            p[6] -= s;
            if (p[6] < 1) {
                p[6] = 1;
                if (p[7] > p[6]) {
                    p[7] = p[6];
                }
            }
            break;
        case 7:
        case 11:
        case 21:
        case 22:
            p[t] -= s;
            if (p[types[lbl_1_bss_307C]] < 0) {
                p[types[lbl_1_bss_307C]] = 0;
            }
            break;
        case 10:
            p[t] ^= 1;
            break;
        case 12:
        case 13:
            p[t] -= l;
            if (p[types[lbl_1_bss_307C]] < 0) {
                p[types[lbl_1_bss_307C]] = 0;
            }
            break;
        case 23:
        case 24:
            p[t] -= m;
            break;
        case 14:
        case 15:
            p[t] -= l;
        case 16:
            v = ((p[16] >> 8) & 0xFF);
            v -= s;
            if (v < 0) {
                v = 0;
            }
            p[16] = v * 0x01010100;
            break;
        case 17:
        case 18:
        case 19:
            break;
        }
    } else if (buttons & 2) {
        t = types[lbl_1_bss_307C];
        switch (t) {
        case 0:
            break;
        case 1:
            p[t] = (p[t] + 1) % 42;
            break;
        case 2:
            p[2] += s;
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 20:
            p[t] += m;
            break;
        case 6:
            p[6] += s;
            break;
        case 7:
            p[7] += s;
            if (p[7] > p[6]) {
                p[7] = p[6];
            }
            break;
        case 11:
        case 21:
            p[t] += s;
            if (p[types[lbl_1_bss_307C]] > 255) {
                p[types[lbl_1_bss_307C]] = 255;
            }
            break;
        case 22:
            p[t] += s;
            break;
        case 10:
            p[t] ^= 1;
            break;
        case 12:
        case 13:
            p[t] += l;
            break;
        case 23:
        case 24:
            p[t] += m;
            break;
        case 14:
        case 15:
            p[t] += l;
            break;
        case 16:
            v = ((p[16] >> 8) & 0xFF);
            v += s;
            if (v > 255) {
                v = 255;
            }
            p[16] = v * 0x01010100;
            break;
        case 17:
        case 18:
        case 19:
            break;
        }
    }
}

extern void fn_80011640(void*, void*);
extern void fn_80052968(void);

// .text:0x121D4 size:0x4F8
void fn_1_121D4(u8* camera) {
    switch (*(s32*)(camera + 0x114)) {
    case 0:
        fn_1_11F08(camera);
        break;
    case 1:
        fn_1_11D00(camera);
        break;
    }
    fn_80011640(camera, camera);
    PSVECSubtract((Vec*)(camera + 0x108), (Vec*)(camera + 0xFC), (Vec*)(camera + 0x88));
    PSVECNormalize((Vec*)(camera + 0x88), (Vec*)(camera + 0x88));
    fn_80052968();
}

extern u8 lbl_1_data_1F1A;

// .text:0x15CE0 size:0x3F8
void fn_1_15CE0(void) {
    u16 buttons = *(u16*)((u8*)&lbl_803C77B8 + 4);

    if (buttons & 8) {
        if (--ch_307C < 0) {
            ch_307C = 5;
        }
    } else if (buttons & 4) {
        if (++ch_307C >= 6) {
            ch_307C = 0;
        }
    } else if (buttons & 1) {
        switch (ch_307C) {
        case 0:
            if (--ch_5F72 >= 2) {
                ch_5F72 = 1;
            }
            break;
        case 1:
            break;
        case 2:
            ch_67E0[0x118] ^= 1;
            break;
        case 3:
            lbl_1_data_1F1A ^= 1;
            break;
        case 4:
            if (ch_5F62 >= 0) {
                ch_5F62--;
            }
            break;
        case 5:
            if (ch_5F60 > 1) {
                ch_5F60--;
            }
            break;
        }
    } else if (buttons & 2) {
        switch (ch_307C) {
        case 0:
            if (++ch_5F72 >= 2) {
                ch_5F72 = 0;
            }
            break;
        case 1:
            break;
        case 2:
            ch_67E0[0x118] ^= 1;
            break;
        case 3:
            lbl_1_data_1F1A ^= 1;
            break;
        case 4:
            if (ch_5F62 < 1) {
                ch_5F62++;
            }
            break;
        case 5:
            if (ch_5F60 < 0x10) {
                ch_5F60++;
            }
            break;
        }
    } else if (buttons & 0x100) {
        switch (ch_307C) {
        case 1:
            fn_1_1620C();
            break;
        }
    } else if (buttons & 0x200) {
        ch_307C = 0;
        ch_5F71 = 1;
    }
}

extern f32 lbl_1_data_AD0C[3];

// .text:0x126CC size:0x154
// NONMATCHING ~85%: same instructions, float/int load scheduling differs (49 diff lines)
#if NONMATCHING
void fn_1_126CC(void) {
    u8* row = lbl_8036E548 + ch_5F73 * 0x27C + 0xC04;
    f32 x = *(f32*)(row + 0x34);
    f32 y = *(f32*)(row + 0x38);
    f32 z = *(f32*)(row + 0x3C);
    x += (f32)((s8*)&lbl_803C77B8)[0x10] / 768.0f;
    z += (f32)((s8*)&lbl_803C77B8)[0x11] / 768.0f;
    y += (f32)((u8*)&lbl_803C77B8)[0x15] / 768.0f;
    y -= (f32)((u8*)&lbl_803C77B8)[0x14] / 768.0f;
    lbl_1_data_AD0C[1] -= 0.001953125f * (f32)((s8*)&lbl_803C77B8)[0x12];
    lbl_1_data_AD0C[0] -= 0.001953125f * (f32)((s8*)&lbl_803C77B8)[0x13];
    *(f32*)(row + 0x34) = x;
    *(f32*)(row + 0x38) = y;
    *(f32*)(row + 0x3C) = z;
    *(f32*)(row + 0x40) = lbl_1_data_AD0C[0];
    *(f32*)(row + 0x44) = lbl_1_data_AD0C[1];
    *(f32*)(row + 0x48) = lbl_1_data_AD0C[2];
}
#endif

// .text:0x179CC size:0x190
// NONMATCHING ~95%: register-only diffs (r4/r5, f4/f5 swapped around the 1/512 constant and row pointer)
#if NONMATCHING
void fn_1_179CC(void) {
    u8* row;
    f32 x;
    f32 y;
    f32 z;
    switch (ch_5F72) {
    case 0:
        fn_1_121D4(ch_67E0);
        break;
    case 1:
        row = lbl_8036E548 + ch_5F73 * 0x27C + 0xC04;
        x = *(f32*)(row + 0x34);
        y = *(f32*)(row + 0x38);
        z = *(f32*)(row + 0x3C);
        x += (f32)((s8*)&lbl_803C77B8)[0x10] / 768.0f;
        z += (f32)((s8*)&lbl_803C77B8)[0x11] / 768.0f;
        y += (f32)((u8*)&lbl_803C77B8)[0x15] / 768.0f;
        y -= (f32)((u8*)&lbl_803C77B8)[0x14] / 768.0f;
        lbl_1_data_AD0C[1] -= 0.001953125f * (f32)((s8*)&lbl_803C77B8)[0x12];
        lbl_1_data_AD0C[0] -= 0.001953125f * (f32)((s8*)&lbl_803C77B8)[0x13];
        *(f32*)(row + 0x34) = x;
        *(f32*)(row + 0x38) = y;
        *(f32*)(row + 0x3C) = z;
        *(f32*)(row + 0x40) = lbl_1_data_AD0C[0];
        *(f32*)(row + 0x44) = lbl_1_data_AD0C[1];
        *(f32*)(row + 0x48) = lbl_1_data_AD0C[2];
        break;
    }
}
#endif

#include "main/file_800BD8C4.h"
extern GXColor lbl_1_rodata_72FC;

// .text:0x12820 size:0x1B0
// NONMATCHING ~96%: saved-register allocation only (table/matrix/object/base rotated)
#if NONMATCHING
void fn_1_12820(void* tableArg, void* matrixArg) {
    u16 i;
    ActorObject* object;
    f32 (*matrix)[4] = matrixArg;
    u8* row;
    u8 lastAlpha = 0xFF;
    ActorObjectTable* table = tableArg;
    u8* entry;
    u8* data;
    u8 alpha;
    Mtx transform;
    Mtx44 projection;
    GXColor color;

    color = lbl_1_rodata_72FC;
    C_MTXFrustum(projection, lbl_1_rodata_73CC[0], lbl_1_rodata_73D0[0],
                 lbl_1_rodata_73D4[0], lbl_1_rodata_73D8[0],
                 lbl_1_rodata_73DC[0], lbl_1_rodata_73E0[0]);
    GXSetProjection(projection, GX_PERSPECTIVE);
    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    for (i = 0; i < table->count; i++) {
        entry = (u8*)table + i * 0x90;
        object = (ActorObject*)(entry + 0x34);
        row = lbl_8036E548 + i * 0x27C;
        data = row + 0xC04;
        if (object->actor == NULL) continue;
        object->actor->flags98 = 0xFF;
        if (entry[0xA0] == 0) continue;
        alpha = data[0x277];
        if (lastAlpha != alpha) {
            lastAlpha = alpha;
            if (0xFF - alpha != 0) {
                color.a = alpha;
                if (alpha == 0) continue;
                fn_800BD2CC(1, color);
            } else {
                color.a = 0xFF;
                fn_800BD2CC(0, color);
            }
        }
        PSMTXTrans(transform, *(f32*)(row + 0xC38), *(f32*)(row + 0xC3C), *(f32*)(row + 0xC40));
        PSMTXConcat(matrix, transform, transform);
        fn_800BDA94(object, transform);
    }
}
#endif

struct GameActor;
extern void fn_800B2B74(struct GameActor* actor, u16 bone);
extern u16 lbl_1_data_F4E8[][2];
extern void fn_1_CDC8(void);

// .text:0xD13C size:0x1B4
// NONMATCHING ~85%: scheduling/register differences around the row pointer and flag compare
#if NONMATCHING
void fn_1_D13C(void) {
    u16 bones[2];
    u8* row = lbl_8036E548 + ch_5F73 * 0x27C + 0xC04;
    s32 kind = 0; // uninitialized in the original (case 39 / default keep a stale register)
    s32 i;
    u16* bone;
    u16* ids;
    u8* queue;

    queue = fn_800B0A5C_insertQueue((void*)fn_1_CDC8, (u16)(*(u16*)(lbl_803CC1B8[0] + 0x12) + 1));
    ch_60E8 = queue;
    *(s16*)(queue + 0x10) = (ch_6940 + ch_5F73 * 0x48)[0x44];
    switch ((ch_68FC + ch_5F73)[0x40]) {
    case 38:
        kind = 0;
        break;
    case 18:
        kind = 3;
        break;
    case 40:
        kind = 1;
        break;
    case 41:
        kind = 2;
        break;
    case 39:
        break;
    }
    row[0x25A] = ((ch_6940 + ch_5F73 * 0x48)[0x44] < 2) == (ch_5F69 == 0);
    ids = (u16*)(lbl_8036E548 + ch_5F73 * 0x27C + 0xD66);
    bone = bones;
    bone[row[0x25A]] = ids[lbl_1_data_F4E8[kind][0]];
    bone[row[0x25A] == 0] = ids[lbl_1_data_F4E8[kind][1]];
    for (i = 0; i < 2; i++) {
        fn_800B2B74(*(struct GameActor**)(*(u8**)(lbl_8036E548 + 0x60) + ch_5F73 * 0x90 + 0x34), *bone);
        bone++;
    }
}
#endif

// .text:0xD300 size:0x1BC
// NONMATCHING ~96%: switch tree lacks one dead branch; r6/r7 swap
#if NONMATCHING
void fn_1_D300(u8* row) {
    u32 idx;
    s32 first;
    u8** actors;
    s32 second;

    idx = ch_5F73;
    switch ((ch_6940 + idx * 0x48)[0x44]) {
    case 0:
    case 1:
        first = 1;
        second = 2;
        break;
    default:
        if (ch_5F69 != 0) {
            first = 1;
            second = 4;
        } else {
            first = 3;
            second = 2;
        }
        break;
    }
    actors = (u8**)(lbl_8036E548 + 0x2C50);
    *(u8**)(actors[idx] + 0x30) = lbl_8036E548 + idx * 0xD4 + 0x140;
    memcpy(*(u8**)(actors[ch_5F73] + 0x30) + 0x4, ch_60EC + first * 0x5C, 0x5C);
    memcpy(*(u8**)(actors[ch_5F73] + 0x30) + 0x68, ch_60EC + second * 0x5C, 0x5C);
    (*(u8**)(actors[ch_5F73] + 0x30))[0x60] = ch_5F73;
    (*(u8**)(actors[ch_5F73] + 0x30))[0xC4] = ch_5F73;
    (*(u8**)(actors[ch_5F73] + 0x30))[0xCD] = row[0x25A];
    (*(u8**)(actors[ch_5F73] + 0x30))[0xCE] = row[0x25B];
    (*(u8**)(actors[ch_5F73] + 0x30))[0xCF] = ch_5F73;
    (*(u8**)(actors[ch_5F73] + 0x30))[0xD0] = ch_5F73;
    *(void**)actors[ch_5F73] = (*(ChallengeModelEntry**)(lbl_8036E548 + 0x60))[ch_5F73].actor;
}
#endif

extern s16 lbl_1_data_A978[];
extern u8 lbl_1_data_2390[];
extern void fn_80052D70(void);

// .text:0x17B5C size:0x234
// NONMATCHING ~85%: the 7-entry search is fully unrolled with fixed offsets in the original (an if-chain gets ~92%); zero-store scheduling
#if NONMATCHING
void fn_1_17B5C(void) {
    s32 i;
    u8* entry;

    ch_5F62 = -1;
    ch_5F60 = 4;
    for (i = 0; i < 0x36; i++) {
        ch_60A4[i] = lbl_1_data_A978[i] != -1;
    }
    for (i = 0; i < 7; i++) {
        if (lbl_1_data_2390[i] != 0) break;
    }
    ch_68FC[0x40] = 0;
    entry = ch_6940;
    entry[0x44] = i;
    entry[0x45] = 0;
    entry[0x46] = 0;
    ch_5F5C = 0;
    *(void (**)(u8*))lbl_803CC1B8[0] = fn_1_176EC;
    fn_80052D70();
}
#endif

// ScreenFx (main/file_80039AC0.h); that header pulls in game/UnknownHomes_Game.h, which clashes with this file's externs
extern u8 lbl_803C5090[]; // TODO type: ScreenFx
extern void fn_8003A2C0(void);
extern void (*lbl_1_data_ABB4[])(void);
extern u8 lbl_1_data_A9E4[];
extern u8 lbl_1_data_AC7C[];

// .text:0x1770C size:0x248
// NONMATCHING ~90%: the original reaches lbl_1_data_A9E4..AC7C and 1F1A through one pooled .data base (needs the data split)
#if NONMATCHING
void fn_1_1770C(u8* object) {
    u8 active;

    lbl_1_data_ABB4[ch_5F71]();
    active = 0;
    if (ch_5F71 != 0 && (ch_5F68 == 0 || ch_5F64 != 0.0f)) {
        active = 1;
    }
    lbl_1_bss_3215[0] = active;
    if (ch_5F5C == 1) {
        fn_800B0A5C_insertQueue((void*)fn_1_107B8, 0xFF);
        ch_5F5C = 2;
    }
    fn_1_179CC();
    PSMTXCopy((f32(*)[4])ch_67E0, (f32(*)[4])(ch_68FC + 0x10));
    fn_1_129D0();
    PSMTXCopy((f32(*)[4])(ch_68FC + 0x10), (f32(*)[4])(lbl_1_data_AAC4 + lbl_803CBBC0[0] * 0x38 + 8));
    ((void (*)(s32, void*))fn_800A7D4C)(7, lbl_1_data_AAC4 + lbl_803CBBC0[0] * 0x38);
    if (ch_3078 != 0) {
        ((void (*)(s32, void*))fn_800A7D4C)(7, lbl_1_data_AB34 + lbl_803CBBC0[0] * 0x38);
    }
    PSMTXCopy((f32(*)[4])(ch_68FC + 0x10), (f32(*)[4])(lbl_1_data_AA54 + lbl_803CBBC0[0] * 0x38 + 8));
    ((void (*)(s32, void*))fn_800A7D4C)(7, lbl_1_data_AA54 + lbl_803CBBC0[0] * 0x38);
    if (lbl_1_data_1F1A != 0) {
        PSMTXCopy((f32(*)[4])(ch_68FC + 0x10), (f32(*)[4])(lbl_1_data_A9E4 + lbl_803CBBC0[0] * 0x38 + 8));
        ((void (*)(s32, void*))fn_800A7D4C)(9, lbl_1_data_A9E4 + lbl_803CBBC0[0] * 0x38);
    }
    lbl_803C5090[0x1D] = 1;                // flags
    *(f32*)(lbl_803C5090 + 0x0) = 1.0f;    // scale
    *(f32*)(lbl_803C5090 + 0x4) = 1.0f;
    lbl_803C5090[0x17] = 0xFF;             // alpha
    *(f32*)(lbl_803C5090 + 0x8) = 0.0f;    // jitterX
    *(f32*)(lbl_803C5090 + 0xC) = 0.0f;    // jitterY
    *(u16*)(lbl_803C5090 + 0x14) = 0x1C0;  // lines
    fn_8003A2C0();
    ((void (*)(s32, void*))fn_800A7D4C)(0, lbl_1_data_AC7C + lbl_803CBBC0[0] * 8);
}
#endif

#include "Dolphin/OS/OSError.h"
void ACTSetAnimation(ActorInst* actor, void* animBank, int seqName, u16 seqNum, f32 time, f32 speed);
void Set_FUN_800b2b6c(ActorInst* actor, s32 value);
u8 fn_800B3C04(s32 arg0, ActorInst* actor, MtxPtr matrix);
void fn_800B4AFC(ActorInst* actor, u8 value);
void fn_800B4C04(ActorInst* actor, f32 value);
void fn_800B4CA0(ActorInst* actor, f32 time);

// .text:0x12F8C size:0x258
// NONMATCHING ~85%: register allocation, pooled .bss base and the inlined fn_1_1073C differ
#if NONMATCHING
void fn_1_12F8C(void* tableArg, void* matrixArg) {
    ActorObjectTable* table = tableArg;
    Mtx transform;
    ActorObject* object;
    ActorInst* actor;
    u8* row;
    u8* bone;
    u16 i;

    for (i = 0; i < table->count; i++) {
        object = (ActorObject*)((u8*)table + i * 0x90 + 0x34);
        if (object->actor == NULL) {
            continue;
        }
        if (object->setAnimation) {
            ACTSetAnimation(object->actor, object->animBank, 0, object->seqNum, 0.0f, object->speed);
        }
        if (object->setTime) {
            fn_800B4CA0(object->actor, object->time);
        }
        if (object->setSpeed) {
            fn_800B4C04(object->actor, object->unk54);
        }
        if (object->visFlags & 2) {
            fn_800B4AFC(object->actor, object->visFlags & 1);
        }
        Set_FUN_800b2b6c(object->actor, object->unk68);
        if (object->animateBones) {
            fn_800BDA24(object);
            if (ch_3081 != 0) {
                fn_1_1073C(lbl_8036E548 + i * 0x27C + 0xC04);
            }
            if (ch_308C != 0) {
                ch_308C = 0;
                // Debug bone dump. The original reuses the outer loop counter here.
                for (i = 0; i < *(u16*)((u8*)object->actor + 0x6); i++) { // TODO type: ActorInst bone count / table
                    bone = (*(u8***)((u8*)object->actor + 0x18))[i];
                    OSReport("#%3d %f %f %f\n", *(u16*)bone, *(f32*)(bone + 0x64), *(f32*)(bone + 0x68), *(f32*)(bone + 0x6C));
                }
            }
        }
        row = lbl_8036E548 + i * 0x27C;
        PSMTXTrans(transform, *(f32*)(row + 0xC38), *(f32*)(row + 0xC3C), *(f32*)(row + 0xC40));
        PSMTXConcat((f32(*)[4])matrixArg, transform, transform);
        actor = object->actor;
        actor->flags98 = (actor->flags98 & 0xFC) | fn_800B3C04(0, actor, transform);
        object = (ActorObject*)((u8*)table + i * 0x90 + 0x34);
        object->setAnimation = 0;
        object->setTime = 0;
        object->setSpeed = 0;
        object->visFlags &= 1;
    }
}
#endif
