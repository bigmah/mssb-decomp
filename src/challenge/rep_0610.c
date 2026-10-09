#include "challenge/rep_0610.h"

// POOL BEGIN
static u8 ch_68FC[0x30];
static u8 ch_fill68F8[0x4];
static u8 ch_67E0[0x118];
static s32 ch_67B8[0xA];
static u8 ch_fill5F74[0x844];
static u8 ch_5F73;
static u8 ch_fill5F72;
static u8 ch_fill5F71;
static u8 ch_fill5F70;
static u8 ch_fill5F6C[0x4];
static u8 ch_fill5F6B;
static u8 ch_fill5F6A;
static u8 ch_5F69;
static u8 ch_fill5F68;
static u8 ch_3218[0x2D50];
static u8 ch_fill30C0[0x158];
static s32 ch_30BC;
static u8 ch_fill307C[0x40];
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
    base += lbl_1_bss_5F73[0] * 0x27C;
    row = *(u8**)(base + 0xC08);
    mod = *(u16*)(row + 0x6);
    lbl_1_bss_5F6C = (lbl_1_bss_5F6C + mod + arg) % mod;
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
