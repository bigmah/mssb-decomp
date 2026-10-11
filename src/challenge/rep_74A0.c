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
extern ChallengeConfettiConfig lbl_1_data_FB24;
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
// Set a confetti piece's velocity: `speed` along `degrees` (0 = straight down the screen).
void fn_1_18E04(ChallengeConfetti* piece, f32 degrees) {
    f32 sine;
    f32 radians;
    f32 cosine;
    radians = lbl_1_rodata_7578 * degrees;
    sine = (f32)sin(radians);
    cosine = (f32)cos(radians);
    piece->vel.x = sine * (f32)lbl_1_data_FB24.speed / lbl_1_rodata_757C;
    piece->vel.y = cosine * (f32)lbl_1_data_FB24.speed / lbl_1_rodata_757C;
    piece->vel.z = lbl_1_rodata_7520;
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

extern ChallengeCamera lbl_1_bss_6B7C;
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
    ChallengeCamera* st = &lbl_1_bss_6B7C;
    st->pos.x = lbl_1_rodata_7520;
    st->pos.y = lbl_1_rodata_75F0;
    st->pos.z = lbl_1_rodata_7520;
    st->target.x = lbl_1_rodata_7520;
    st->target.y = lbl_1_rodata_7520;
    st->target.z = lbl_1_rodata_75F4;
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

#include "dolphin/GX/GXFifo.h"
extern const f32 lbl_1_rodata_75B0;
extern const f32 lbl_1_rodata_75B4;

// fn_1_1ADA4, size:0x294
// Debug viewer: draw the ground grid.
void fn_1_1ADA4(void) {
    Mtx44 proj;
    s32 i;

    C_MTXFrustum(proj, lbl_1_rodata_752C, lbl_1_rodata_7530, lbl_1_rodata_7534, lbl_1_rodata_7538, lbl_1_rodata_753C, lbl_1_rodata_7540);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXLoadPosMtxImm(lbl_1_bss_6B7C.view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    for (i = -24; i < 25; i++) {
        f32 t = i;
        GXBegin(GX_LINES, GX_VTXFMT0, 4);
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75B0;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
        GXWGFifo.f32 = t;
        GXColor4u8(0, 0xFF, 0, 0xC8);
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75B4;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
        GXWGFifo.f32 = t;
        GXColor4u8(0, 0xFF, 0, 0xC8);
        GXWGFifo.f32 = t;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75B0;
        GXColor4u8(0, 0xFF, 0, 0xC8);
        GXWGFifo.f32 = t;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75B4;
        GXColor4u8(0, 0xFF, 0, 0xC8);
    }
}

void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);
extern Vec lbl_1_data_FB0C;
extern const Vec lbl_1_rodata_74F4;
extern const f32 lbl_1_rodata_75E0;
extern const f32 lbl_1_rodata_75E4;
extern const f32 lbl_1_rodata_75E8;
extern const f32 lbl_1_rodata_75EC;

// fn_1_1B424, size:0x298
// Debug viewer: orbit/pan the camera with the pad (Z held = freeze) and build the view matrix.
// NONMATCHING 83%: everything after the pad block matches; the pad reads/int->float conversions are scheduled differently
#if NONMATCHING
void fn_1_1B424(void) {
    Mtx rotX;
    Mtx rotY;
    Mtx rot;
    Vec angles;
    Vec offset = lbl_1_rodata_74F4;
    ChallengePad* pad = (ChallengePad*)&lbl_803C77B8;
    ChallengeCamera* cam;
    f32 sideX;
    f32 sideZ;

    if (!(lbl_803C77B8._00 & 0x10 /* Z */)) {
        cam = &lbl_1_bss_6B7C;
        cam->pos.y += pad->triggerR * lbl_1_rodata_75E8;
        cam->rotX -= pad->substickY;
        cam->rotY += pad->substickX;
        cam->panX = pad->stickX / lbl_1_rodata_75E0;
        cam->panY = pad->stickY * lbl_1_rodata_75E4;
        cam->pos.y -= pad->triggerL * lbl_1_rodata_75E8;
    }
    angles.x = lbl_1_bss_6B7C.rotX;
    angles.y = lbl_1_bss_6B7C.rotY;
    angles.z = lbl_1_rodata_7520;
    PSVECScale(&angles, lbl_1_rodata_75EC, &angles);
    PSMTXRotRad(rotX, 'X', angles.x);
    PSMTXRotRad(rotY, 'Y', angles.y);
    sideZ = rotY[0][2];
    sideX = rotY[0][0];
    PSMTXConcat(rotY, rotX, rot);
    PSMTXMultVec(rot, &offset, &lbl_1_bss_6B7C.target);
    cam = &lbl_1_bss_6B7C;
    cam->pos.x += cam->panY * sideZ - cam->panX * sideX;
    cam->pos.z += cam->panY * sideX + cam->panX * sideZ;
    cam->target.x += cam->pos.x;
    cam->target.y += cam->pos.y;
    cam->target.z += cam->pos.z;
    makeLookAtMatrix(cam->view, &cam->pos, &lbl_1_data_FB0C, &cam->target);
}
#endif

extern const f32 lbl_1_rodata_751C;
extern const f32 lbl_1_rodata_7524;
extern const f32 lbl_1_rodata_7528;

// fn_1_182C0, size:0x2BC
// Draw one confetti piece: a two-sided quad (front colour, back colour).
// NONMATCHING 99%: float register choice and the order of the quad corner stores differ
#if NONMATCHING
void fn_1_182C0(ChallengeConfetti* piece) {
    Vec quad[4];
    Mtx mtx;
    Mtx44 proj;
    struct {
        Control c;
        u32 pad[2]; // frame size
    } ctrl;
    f32 halfW = piece->width * lbl_1_rodata_751C;
    f32 halfH = piece->height * lbl_1_rodata_751C;
    s32 i;

    ctrl.c.type = 0;
    quad[0].x = -halfW;
    quad[0].y = -halfH;
    quad[0].z = lbl_1_rodata_7520;
    quad[1].x = halfW;
    quad[1].y = -halfH;
    quad[1].z = lbl_1_rodata_7520;
    quad[2].x = halfW;
    quad[2].y = halfH;
    quad[2].z = lbl_1_rodata_7520;
    quad[3].x = -halfW;
    quad[3].y = halfH;
    quad[3].z = lbl_1_rodata_7520;
    CTRLSetRotation(&ctrl.c, piece->rot.x, piece->rot.y, piece->rot.z);
    CTRLSetTranslation(&ctrl.c, lbl_1_rodata_751C * piece->pos.x * lbl_1_rodata_751C * piece->pos.z,
                       lbl_1_rodata_7524 * piece->pos.y * lbl_1_rodata_751C * piece->pos.z, lbl_1_rodata_7528);
    CTRLBuildMatrix(&ctrl.c, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    C_MTXOrtho(proj, lbl_1_rodata_752C * piece->pos.z, lbl_1_rodata_7530 * piece->pos.z, lbl_1_rodata_7534 * piece->pos.z,
               lbl_1_rodata_7538 * piece->pos.z, lbl_1_rodata_753C, lbl_1_rodata_7540);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);

    GXSetCullMode(GX_CULL_BACK);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(quad[i].x, quad[i].y, quad[i].z);
        GXColor1u32(piece->front.rgba);
    }
    GXSetCullMode(GX_CULL_FRONT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    for (i = 0; i < 4; i++) {
        GXPosition3f32(quad[i].x, quad[i].y, quad[i].z);
        GXColor1u32(piece->back.rgba);
    }
}
#endif

#include <stdlib.h>
extern const f32 lbl_1_rodata_7550;
extern const f32 lbl_1_rodata_7568;
extern const f32 lbl_1_rodata_7580;

// fn_1_18EE4, size:0x2F8
// (Re)spawn a confetti piece at the top of the screen with random depth, spin and colours.
void fn_1_18EE4(ChallengeConfetti* piece) {
    s32 colorMin = lbl_1_data_FB24.colorMin;
    s32 base = (u8)colorMin;
    u8 range;
    f32 spin;

    piece->pos.x = (f32)(piece->index * 2) / (f32)lbl_1_data_FB24.count - lbl_1_rodata_753C;
    piece->pos.y = lbl_1_rodata_7550;
    piece->pos.z = 50.0f * ((f32)rand() / 32767.0f) + 50.0f;
    {
        // fn_1_18E04(piece, 0.0f), with the angle already folded to 0
        f32 sine = (f32)sin(lbl_1_rodata_7520);
        f32 cosine = (f32)cos(lbl_1_rodata_7520);
        piece->vel.x = sine * (f32)lbl_1_data_FB24.speed / lbl_1_rodata_757C;
        piece->vel.y = cosine * (f32)lbl_1_data_FB24.speed / lbl_1_rodata_757C;
        piece->vel.z = lbl_1_rodata_7520;
    }
    piece->rot.z = lbl_1_rodata_7520;
    piece->rot.y = lbl_1_rodata_7520;
    piece->rot.x = lbl_1_rodata_7520;
    spin = (f32)lbl_1_data_FB24.spin / lbl_1_rodata_757C;
    piece->rotVel.x = spin * ((f32)rand() / 32767.0f);
    piece->rotVel.y = spin * ((f32)rand() / 32767.0f);
    piece->rotVel.z = spin * ((f32)rand() / 32767.0f);
    piece->back.c.a = 0xFF;
    piece->front.c.a = 0xFF;
    range = 0xFF - colorMin;
    piece->front.c.g = base + rand() % range;
    piece->front.c.b = base + rand() % range;
    piece->back.c.r = base + rand() % range;
    piece->back.c.g = base + rand() % range;
    piece->back.c.b = base + rand() % range;
}

// fn_1_191DC, size:0x3A0
// Initialise every confetti piece; start delays are staggered in five waves.
// NONMATCHING 99%: register-only, r26/r27 swapped (config base vs. inlined colour base)
#if NONMATCHING
void fn_1_191DC(ChallengeConfettiTask* task) {
    ChallengeConfetti* piece = task->pieces;
    u32 i = 0;

    do {
        s32 wave;
        piece->index = i;
        piece->width = (f32)lbl_1_data_FB24.width / lbl_1_rodata_757C;
        piece->height = (f32)lbl_1_data_FB24.height / lbl_1_rodata_757C;
        fn_1_18EE4(piece);
        wave = lbl_1_data_FB24.count / 5;
        piece->delay = ((i++ % 5) * wave + rand() % wave) * 2;
        piece = piece->next;
    } while (piece != NULL);
}
#endif
