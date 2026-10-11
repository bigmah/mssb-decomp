#include "challenge/rep_74A0.h"


#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "C3/control.h"
#include "C3/light.h"

// main.dol lighting (see include/main/file_800B9974.h, which can't be included
// next to UnknownHomes_Static.h)
void LITInitColor(Light* light, GXColor* color);
void LITInitPos(Light* light, f32 x, f32 y, f32 z);
void LITInitAttn(Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);
#include <math.h>

extern void fn_1_1CBE4(u8* object);
extern u8 lbl_80366158[];
extern ChallengeRosterQueue* lbl_803CC1B8;
extern u8 lbl_1_bss_69FC[];
extern void fn_1_19D60(struct DODisplayObj*, s32);
extern s32 lbl_1_data_FB24[];
extern const f32 lbl_1_rodata_7578;
extern const f32 lbl_1_rodata_757C;
extern const f32 lbl_1_rodata_7520;
extern ChallengeBoneSelection lbl_1_bss_69F0;
extern u8 lbl_8036E548[];
extern void fn_1_1A850(MtxPtr, MtxPtr, u8, u8, u8, u8);

// fn_1_1A774, size:0xDC
#pragma opt_loop_invariants off
void fn_1_1A774(void) {
    Mtx matrix;
    s32 index;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;

    if (lbl_1_bss_69F0.selectedBone < (*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60))->nodes[lbl_1_bss_69F0.selectedActor].drawing.actor->boneCount) {
        for (index = 0; index < (*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60))->nodes[lbl_1_bss_69F0.selectedActor].drawing.actor->boneCount; index++) {
            if (index == lbl_1_bss_69F0.selectedBone) {
                red = 0;
                green = 0xFF;
                blue = 0xFF;
                alpha = 0xFF;
            } else {
                red = 0;
                green = 0x80;
                blue = 0x80;
                alpha = 0x40;
            }
            fn_800B2C88((*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60))->nodes[lbl_1_bss_69F0.selectedActor].drawing.actor, index, matrix);
            fn_1_1A850(matrix, lbl_1_bss_69F0.matrix, red, green, blue, alpha);
        }
    }
}
#pragma opt_loop_invariants reset

// fn_1_1A290, size:0x124
void fn_1_1A290(ChallengeDrawCollection* collection, s32 mode) {
    u16 index;

    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (index = 0; index < collection->count; index++) {
        ChallengeActorDrawing* drawing = &collection->nodes[index].drawing;
        if (drawing->actor != NULL && collection->nodes[index].visible != 0) {
            fn_1_1A1EC(drawing, mode);
        }
    }
}

// fn_1_18E04, size:0xE0
void fn_1_18E04(ChallengeOrbitPosition* position, f32 degrees) {
    f32 sine;
    f32 radians;
    f32 cosine;
    radians = lbl_1_rodata_7578 * degrees;
    sine = (f32)sin(radians);
    cosine = (f32)cos(radians);
    position->x = sine * (f32)lbl_1_data_FB24[1] / lbl_1_rodata_757C;
    position->y = cosine * (f32)lbl_1_data_FB24[1] / lbl_1_rodata_757C;
    position->z = lbl_1_rodata_7520;
}

// fn_1_1A1EC, size:0xA4
void fn_1_1A1EC(ChallengeActorDrawing* drawing, s32 mode) {
    ChallengeDrawActor* actor = drawing->actor;
    if (drawing->prepare != NULL) {
        drawing->prepare(drawing);
    }
    if (actor->display != NULL) {
        fn_800B2D5C(actor);
        GXInvalidateVtxCache();
        fn_1_19D60(actor->display, mode);
    } else {
        for (actor = actor->children; actor != NULL; actor = actor->next) {
            if (actor->display != NULL) {
                DOSetWorldMatrix(actor->display, actor->worldMatrix);
            }
            fn_1_19D60(actor->display, mode);
        }
    }
}

// fn_1_1D470, size:0xA4
void fn_1_1D470(void) {
    ChallengeRosterQueue* queue = lbl_803CC1B8;
    s32 index;
    for (index = 0; index < 24; index++) {
        lbl_1_bss_69FC[0x40 + index] = 0;
    }
    queue->menu = 0;
    lbl_803CC1B8->update = fn_1_1D450;
}


// .text:0x1D10C size:0x4
void fn_1_1D10C(void) {
}

// fn_1_1D0E8, size:0x24
void fn_1_1D0E8(u8* object) {
    fn_800B9AA8(*(void**)(object + 0x70));
}

// fn_1_1D450, size:0x20
void fn_1_1D450(u8* object) {
    fn_1_1CBE4(object);
}

// fn_1_19D1C, size:0x44
s32 fn_1_19D1C(u8 value) {
    switch ((value >> 4) & 0xF) {
    case 0:
    case 1: return 1;
    case 2:
    case 3: return 2;
    case 4: return 4;
    default: return 0;
    }
}

// fn_1_1D514, size:0x7C
void fn_1_1D514(void) {
    u8* b = (u8*)&lbl_1_bss_69F0;
    fn_800AD038(*(void**)(lbl_80366158 + 8));
    lbl_803CC1B8->state = 0;
    lbl_803CC1B8->update = (void (*)(u8*))fn_1_1D470;
    b[6] = 0xFF;
    b[7] = 0xFF;
    b[8] = 0xFF;
    b[9] = 0xFF;
    b[5] = 0;
    b[3] = 0;
}

typedef struct { u8 pad[0x3C]; f32 f3C, f40, f44, f48, f4C, f50; } ChallengeProjState;
extern ChallengeProjState lbl_1_bss_6B7C;
extern const f32 lbl_1_rodata_75F0;
extern const f32 lbl_1_rodata_75F4;
extern const f32 lbl_1_rodata_752C;
extern const f32 lbl_1_rodata_7530;
extern const f32 lbl_1_rodata_7534;
extern const f32 lbl_1_rodata_7538;
extern const f32 lbl_1_rodata_7540;
extern const f32 lbl_1_rodata_753C;
extern const f32 lbl_1_rodata_75F8;
extern const f32 lbl_1_rodata_75FC;
extern const f32 lbl_1_rodata_7600;
extern const f32 lbl_1_rodata_7604;
extern const f32 lbl_1_rodata_7608;
extern const f32 lbl_1_rodata_7550;
extern const f32 lbl_1_rodata_760C;

// fn_1_1B6BC, size:0x120
void fn_1_1B6BC(void) {
    Mtx44 proj;
    ChallengeProjState* st = &lbl_1_bss_6B7C;
    st->f48 = lbl_1_rodata_7520;
    st->f4C = lbl_1_rodata_75F0;
    st->f50 = lbl_1_rodata_7520;
    st->f3C = lbl_1_rodata_7520;
    st->f40 = lbl_1_rodata_7520;
    st->f44 = lbl_1_rodata_75F4;
    C_MTXFrustum(proj, lbl_1_rodata_752C, lbl_1_rodata_7530, lbl_1_rodata_7534, lbl_1_rodata_7538, lbl_1_rodata_753C, lbl_1_rodata_7540);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_75F8, lbl_1_rodata_75FC, lbl_1_rodata_7600, lbl_1_rodata_7604, lbl_1_rodata_7608, lbl_1_rodata_7550, lbl_1_rodata_760C);
}

typedef struct {
    Vec pos;
    u8 pad0C[4];
} ChallengeLightPos;
extern ChallengeLightPos lbl_80367318[3];
// view of lbl_8036E548 (global actor manager) used here
typedef struct {
    u8 pad00[0xAC];
    Light* lights[3];
} ChallengeLightMgr;
extern const GXColor lbl_1_rodata_7508;

// NONMATCHING 95%: prologue scheduling of the GXColor stack copy (same as fn_2_48DB4, docs/patterns/unsolved.md)
#if NONMATCHING
// fn_1_1B038, size:0xC4
void fn_1_1B038(void) {
    s32 i;
    GXColor white = lbl_1_rodata_7508;

    for (i = 0; i < 3; i++) {
        GXColor color;
        LITInitAttn(((ChallengeLightMgr*)lbl_8036E548)->lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(((ChallengeLightMgr*)lbl_8036E548)->lights[i], lbl_80367318[i].pos.x, lbl_80367318[i].pos.y, lbl_80367318[i].pos.z);
        color = white;
        LITInitColor(((ChallengeLightMgr*)lbl_8036E548)->lights[i], &color);
        LITXForm(((ChallengeLightMgr*)lbl_8036E548)->lights[i], lbl_1_bss_69FC + 0x10);
    }
}
#endif

extern Vec lbl_1_data_FB18;
extern const f32 lbl_1_rodata_75CC;
extern const f32 lbl_1_rodata_75D0;

// fn_1_1B2C8, size:0x15C
// Debug viewer: move the selected actor with the sticks/triggers.
// NONMATCHING 32%: same operations; the original loads every input before the first store (scheduling/conversion order)
#if NONMATCHING
void fn_1_1B2C8(void) {
    ChallengePad* pad = (ChallengePad*)&lbl_803C77B8;
    ChallengeViewerActor* actor = (ChallengeViewerActor*)(lbl_8036E548 + lbl_803CC1B8->actorIndex * 0x27C + 0xC04);
    f32 rx;
    f32 ry;

    actor->pos.x += pad->stickX / 768.0f;
    actor->pos.y = actor->pos.y + pad->triggerR / 768.0f - pad->triggerL / 768.0f;
    actor->pos.z += pad->stickY / 768.0f;
    rx = lbl_1_data_FB18.x - pad->substickY * 0.001953125f;
    ry = lbl_1_data_FB18.y - pad->substickX * 0.001953125f;
    actor->rot.x = rx;
    actor->rot.y = ry;
    lbl_1_data_FB18.y = ry;
    lbl_1_data_FB18.x = rx;
    actor->rot.z = lbl_1_data_FB18.z;
}
#endif

void LITAlloc(Light** light);
void LITInitDir(Light* light, f32 x, f32 y, f32 z);
extern const GXColor lbl_1_rodata_7500;
extern const GXColor lbl_1_rodata_7504;
extern const f32 lbl_1_rodata_75B8;
extern const f32 lbl_1_rodata_75BC;
extern const f32 lbl_1_rodata_75C0;
extern const f32 lbl_1_rodata_75C4;
extern const f32 lbl_1_rodata_75C8;

// fn_1_1B0FC, size:0x1CC
// Debug viewer: set up three point lights.
// NONMATCHING 99%: only the prologue scheduling of the two GXColor rodata loads differs (as fn_2_48DB4)
#if NONMATCHING
void fn_1_1B0FC(void) {
    GXColor white = lbl_1_rodata_7500;
    GXColor cyan = lbl_1_rodata_7504;
    GXColor color0;
    GXColor color1;
    GXColor color2;

    LITAlloc(&((ChallengeLightMgr*)lbl_8036E548)->lights[0]);
    LITAlloc(&((ChallengeLightMgr*)lbl_8036E548)->lights[1]);
    LITAlloc(&((ChallengeLightMgr*)lbl_8036E548)->lights[2]);

    LITInitAttn(((ChallengeLightMgr*)lbl_8036E548)->lights[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(((ChallengeLightMgr*)lbl_8036E548)->lights[0], lbl_1_rodata_75B8, lbl_1_rodata_75B8, lbl_1_rodata_75BC);
    color0 = white;
    LITInitColor(((ChallengeLightMgr*)lbl_8036E548)->lights[0], &color0);

    LITInitAttn(((ChallengeLightMgr*)lbl_8036E548)->lights[1], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(((ChallengeLightMgr*)lbl_8036E548)->lights[1], lbl_1_rodata_75C0, lbl_1_rodata_75C4, lbl_1_rodata_75C8);
    color1 = cyan;
    LITInitColor(((ChallengeLightMgr*)lbl_8036E548)->lights[1], &color1);

    LITInitAttn(((ChallengeLightMgr*)lbl_8036E548)->lights[2], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(((ChallengeLightMgr*)lbl_8036E548)->lights[2], lbl_1_rodata_7520, lbl_1_rodata_75C4, lbl_1_rodata_75C8);
    color2 = cyan;
    LITInitColor(((ChallengeLightMgr*)lbl_8036E548)->lights[2], &color2);

    LITInitDir(((ChallengeLightMgr*)lbl_8036E548)->lights[0], lbl_1_rodata_75BC, lbl_1_rodata_75BC, lbl_1_rodata_75B8);
}
#endif
