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

extern u8 lbl_80366158[];
extern ChallengeRosterQueue* lbl_803CC1B8;
extern u8 lbl_1_bss_69FC[];
extern ChallengeConfettiConfig lbl_1_data_FB24;
extern const f32 lbl_1_rodata_7578;
extern const f32 lbl_1_rodata_757C;
extern const f32 lbl_1_rodata_7520;
extern ChallengeBoneSelection lbl_1_bss_69F0;
extern u8 lbl_8036E548[];

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
            fn_800B2C88((struct GameActor *)(*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60))->nodes[lbl_1_bss_69F0.selectedActor].drawing.actor, index, matrix); // TODO type
            fn_1_1A850(matrix, lbl_1_bss_69F0.matrix, red, green, blue, alpha);
        }
    }
}
#pragma opt_loop_invariants reset

// fn_1_1A290, size:0x124
void fn_1_1A290(ChallengeDrawCollection* collection, MtxPtr camera) {
    u16 index;

    GXSetZMode(1, GX_LEQUAL, 1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    for (index = 0; index < collection->count; index++) {
        ChallengeActorDrawing* drawing = &collection->nodes[index].drawing;
        if (drawing->actor != NULL && collection->nodes[index].visible != 0) {
            fn_1_1A1EC(drawing, camera);
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
void fn_1_1A1EC(ChallengeActorDrawing* drawing, MtxPtr camera) {
    ChallengeDrawActor* actor = drawing->actor;
    if (drawing->prepare != NULL) {
        drawing->prepare(drawing);
    }
    if (actor->display != NULL) {
        fn_800B2D5C((struct GameActor *)actor); // TODO type
        GXInvalidateVtxCache();
        fn_1_19D60(actor->display, camera);
    } else {
        for (actor = actor->children; actor != NULL; actor = actor->next) {
            if (actor->display != NULL) {
                DOSetWorldMatrix(actor->display, actor->worldMatrix);
            }
            fn_1_19D60(actor->display, camera);
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
    u8* b = (u8*)&lbl_1_bss_69F0; // TODO type: ChallengeBoneSelection fields (typed pointer changes scheduling)
    fn_800AD038(*(void**)(lbl_80366158 + 8));
    lbl_803CC1B8->state = 0;
    lbl_803CC1B8->update = (void (*)(u8*))fn_1_1D470;
    b[6] = 0xFF; // matAlpha
    b[7] = 0xFF; // matBlue
    b[8] = 0xFF; // matGreen
    b[9] = 0xFF; // matRed
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
extern const GXColor lbl_1_rodata_7508;

// Shared by fn_1_1B038 and its inlined copy in fn_1_1D110.
static inline void initViewerLights(MtxPtr view) {
    s32 i;
    GXColor white = lbl_1_rodata_7508;

    for (i = 0; i < 3; i++) {
        GXColor color;
        LITInitAttn(((ChallengeActorMgr*)lbl_8036E548)->lights[i], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
        LITInitPos(((ChallengeActorMgr*)lbl_8036E548)->lights[i], lbl_80367318[i].pos.x, lbl_80367318[i].pos.y, lbl_80367318[i].pos.z);
        color = white;
        LITInitColor(((ChallengeActorMgr*)lbl_8036E548)->lights[i], &color);
        LITXForm(((ChallengeActorMgr*)lbl_8036E548)->lights[i], view);
    }
}

// NONMATCHING 95%: prologue scheduling of the GXColor stack copy (same as fn_2_48DB4, docs/patterns/unsolved.md)
#if NONMATCHING
// fn_1_1B038, size:0xC4
void fn_1_1B038(void) {
    initViewerLights((MtxPtr)(lbl_1_bss_69FC + 0x10)); // TODO type
}
#endif

extern Vec lbl_1_data_FB18;
extern const f32 lbl_1_rodata_75CC;
extern const f32 lbl_1_rodata_75D0;

// fn_1_1B2C8, size:0x15C
// Debug viewer: move the selected actor with the sticks/triggers.
static inline void moveSelectedActor(void) {
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

// NONMATCHING 32%: same operations; the original loads every input before the first store (scheduling/conversion order)
#if NONMATCHING
void fn_1_1B2C8(void) {
    moveSelectedActor();
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
// Shared by fn_1_1B0FC and its inlined copy in fn_1_1CBE4.
static inline void allocViewerLights(void) {
    GXColor white = lbl_1_rodata_7500;
    GXColor cyan = lbl_1_rodata_7504;
    GXColor color0;
    GXColor color1;
    GXColor color2;

    LITAlloc(&((ChallengeActorMgr*)lbl_8036E548)->lights[0]);
    LITAlloc(&((ChallengeActorMgr*)lbl_8036E548)->lights[1]);
    LITAlloc(&((ChallengeActorMgr*)lbl_8036E548)->lights[2]);

    LITInitAttn(((ChallengeActorMgr*)lbl_8036E548)->lights[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(((ChallengeActorMgr*)lbl_8036E548)->lights[0], lbl_1_rodata_75B8, lbl_1_rodata_75B8, lbl_1_rodata_75BC);
    color0 = white;
    LITInitColor(((ChallengeActorMgr*)lbl_8036E548)->lights[0], &color0);

    LITInitAttn(((ChallengeActorMgr*)lbl_8036E548)->lights[1], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(((ChallengeActorMgr*)lbl_8036E548)->lights[1], lbl_1_rodata_75C0, lbl_1_rodata_75C4, lbl_1_rodata_75C8);
    color1 = cyan;
    LITInitColor(((ChallengeActorMgr*)lbl_8036E548)->lights[1], &color1);

    LITInitAttn(((ChallengeActorMgr*)lbl_8036E548)->lights[2], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(((ChallengeActorMgr*)lbl_8036E548)->lights[2], lbl_1_rodata_7520, lbl_1_rodata_75C4, lbl_1_rodata_75C8);
    color2 = cyan;
    LITInitColor(((ChallengeActorMgr*)lbl_8036E548)->lights[2], &color2);

    LITInitDir(((ChallengeActorMgr*)lbl_8036E548)->lights[0], lbl_1_rodata_75BC, lbl_1_rodata_75BC, lbl_1_rodata_75B8);
}

// NONMATCHING 99%: only the prologue scheduling of the two GXColor rodata loads differs (as fn_2_48DB4)
#if NONMATCHING
void fn_1_1B0FC(void) {
    allocViewerLights();
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
static inline void updateViewerCamera(void) {
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

// NONMATCHING 83%: everything after the pad block matches; the pad reads/int->float conversions are scheduled differently
#if NONMATCHING
void fn_1_1B424(void) {
    updateViewerCamera();
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
// Shared by fn_1_191DC and its inlined copies in fn_1_1957C/fn_1_1994C.
static inline void initConfetti(ChallengeConfettiTask* task) {
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

// NONMATCHING 99%: register-only, r26/r27 swapped (config base vs. inlined colour base)
#if NONMATCHING
void fn_1_191DC(ChallengeConfettiTask* task) {
    initConfetti(task);
}
#endif

#include <string.h>
void* _OSAllocFromHeap(s32 align, s32 size);
void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count);
void fn_1_17EFC(void); // sort compare (ChallengeConfettiSort by depth)
extern const Vec lbl_1_rodata_7510;
extern const f32 lbl_1_rodata_7554;
extern const f64 lbl_1_rodata_7548;
extern const f64 lbl_1_rodata_7558;
extern const f64 lbl_1_rodata_7560;
extern const f64 lbl_1_rodata_7570;

// fn_1_1857C, size:0x888
// Confetti task: depth-sort the pieces, then draw and move each one.
// NONMATCHING 99%: r29/r30 and f30/f31 swapped, int->float temp stack slots allocated differently in the inlined fn_1_18E04/fn_1_18EE4
#if NONMATCHING
s32 fn_1_1857C(ChallengeConfettiTask* task) {
    Vec down = lbl_1_rodata_7510;
    Vec dir;
    ChallengeConfettiSort* sorted;
    ChallengeConfettiSort* entry;
    ChallengeConfetti* piece;
    ChallengeConfetti* head;
    s32 count;

    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);

    // sort back to front
    count = task->count & 0xFFF;
    piece = task->pieces;
    sorted = _OSAllocFromHeap(0x20, count * sizeof(ChallengeConfettiSort));
    entry = sorted;
    while (piece != NULL) {
        entry->piece = piece;
        entry->depth = piece->pos.z;
        entry++;
        piece = piece->next;
    }
    fn_800246D4((s32 (*)(void*, void*))fn_1_17EFC, (u8*)sorted, (u8*)sorted, sizeof(ChallengeConfettiSort), count);
    head = sorted->piece;
    entry = sorted;
    while (--count != 0) {
        entry->piece->next = entry[1].piece;
        entry++;
    }
    entry->piece->next = NULL;
    fn_800ACFB0(sorted);
    task->pieces = head;

    piece = head;
    do {
        if (piece->delay <= 0) {
            fn_1_182C0(piece);
            PSVECAdd(&piece->vel, &piece->pos, &piece->pos);
            PSVECAdd(&piece->rotVel, &piece->rot, &piece->rot);
            if (fabs(piece->pos.x) > lbl_1_rodata_7548) {
                // bounce off the screen edge
                piece->pos.x = fabs(piece->pos.x) / piece->pos.x;
                piece->vel.x *= lbl_1_rodata_7550;
            } else if (rand() % 5 == 0) {
                // drift: turn by up to +-20 degrees, staying within 20 degrees of straight down
                f32 angle;
                f32 delta;
                memcpy(&dir, &piece->vel, sizeof(Vec));
                PSVECNormalize(&dir, &dir);
                angle = lbl_1_rodata_7554 * (f32)acos(PSVECDotProduct(&down, &dir));
                if (dir.x < lbl_1_rodata_7520) {
                    angle *= lbl_1_rodata_7550;
                }
                delta = lbl_1_rodata_7558 * (lbl_1_rodata_7560 * ((f32)rand() / 32767.0f - lbl_1_rodata_7570));
                if (fabs(angle + delta) > lbl_1_rodata_7558) {
                    angle = lbl_1_rodata_7558 * (fabs(angle) / angle);
                } else {
                    angle += delta;
                }
                fn_1_18E04(piece, angle);
            }
            if (piece->pos.y > lbl_1_rodata_753C) {
                fn_1_18EE4(piece);
            }
        } else {
            piece->delay--;
        }
        piece = piece->next;
    } while (piece != NULL);

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXLoadPosMtxImm(fn_80052768_getCamera(0)->view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(fn_80052768_getCamera(0)->proj, GX_PERSPECTIVE);
    return 0;
}
#endif

// main.dol: create a task with a linked list of `count` work blocks of `size` bytes.
extern void* fn_80033A24(void* func, int priority, int flags, int count, int arg4, int size);

// fn_1_1957C, size:0x3D0
// Start the confetti.
// NONMATCHING 99%: register-only (saved GPRs r24-r27 permuted in the inlined init loop)
#if NONMATCHING
void fn_1_1957C(void) {
    ChallengeConfettiTask* task = fn_80033A24(fn_1_1857C, 0, 0, lbl_1_data_FB24.count, 1, 0x80);
    if (task != NULL) {
        initConfetti(task);
    }
}
#endif

// fn_1_1994C, size:0x3D0
// Start the confetti (identical copy).
// NONMATCHING 99%: register-only (saved GPRs r24-r27 permuted in the inlined init loop)
#if NONMATCHING
void fn_1_1994C(void) {
    ChallengeConfettiTask* task = fn_80033A24(fn_1_1857C, 0, 0, lbl_1_data_FB24.count, 1, 0x80);
    if (task != NULL) {
        initConfetti(task);
    }
}
#endif

// fn_1_19D60, size:0x48C
// Draw a display object with a flat material colour (no textures/lighting).
void fn_1_19D60(struct DODisplayObj* dispObj, MtxPtr camera) {
    Mtx mtx;
    GXVtxDescList desc[28];
    GXColor color;
    TextureData* tex;
    DisplayStateList* state;
    s32 compSize;
    s32 i;
    s32 j;
    s32 n;
    s32 attr;
    s32 shift;
    u32 type;

    color.r = lbl_1_bss_69F0.matRed;
    color.g = lbl_1_bss_69F0.matGreen;
    color.b = lbl_1_bss_69F0.matBlue;
    color.a = lbl_1_bss_69F0.matAlpha;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    PSMTXConcat(camera, dispObj->worldMatrix, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    switch ((u8)(dispObj->positionData->quantizeInfo >> 4)) {
    case GX_U8:
    case GX_S8:
        compSize = 1;
        break;
    case GX_U16:
    case GX_S16:
        compSize = 2;
        break;
    case GX_F32:
        compSize = 4;
        break;
    default:
        compSize = 0;
        break;
    }
    GXSetArray(GX_VA_POS, dispObj->positionData->positionArray, (u8)(dispObj->positionData->compCount * compSize));
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, dispObj->positionData->quantizeInfo >> 4,
                    dispObj->positionData->quantizeInfo & 0xF);

    if (dispObj->textureData != NULL) {
        for (i = 0; i < dispObj->numTextureChannels; i++) {
            tex = &dispObj->textureData[i];
            switch ((u8)(tex->quantizeInfo >> 4)) {
            case GX_U8:
            case GX_S8:
                compSize = 1;
                break;
            case GX_U16:
            case GX_S16:
                compSize = 2;
                break;
            case GX_F32:
                compSize = 4;
                break;
            default:
                compSize = 0;
                break;
            }
            GXSetArray(GX_VA_TEX0 + i, tex->textureCoordArray, (u8)(tex->compCount * compSize));
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, dispObj->textureData[i].quantizeInfo >> 4,
                            dispObj->textureData[i].quantizeInfo & 0xF);
            GXSetTexCoordGen2(i, GX_MTX2x4, GX_TG_TEX0 + i, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
    }

    state = dispObj->displayData->displayStateList;
    for (j = 0; j < dispObj->displayData->numStateEntries; j++) {
        switch (state->id) {
        case 2: // vertex descriptors
            GXClearVtxDesc();
            n = 0;
            type = state->setting & 3;
            if (type != 0) {
                desc[0].mType = type;
                n = 1;
                desc[0].mAttr = GX_VA_PNMTXIDX;
            }
            for (attr = GX_VA_POS, shift = 2; attr < GX_VA_TEX7 + 1; attr++, shift += 2) {
                type = (state->setting >> shift) & 3;
                if (type != 0) {
                    desc[n].mAttr = attr;
                    n++;
                    desc[n - 1].mType = type;
                }
            }
            type = (state->setting >> 26) & 3;
            if (type != 0) {
                desc[n].mAttr = attr;
                desc[n].mType = type;
                n++;
            }
            desc[n].mAttr = GX_VA_NULL;
            GXSetVtxDescv(desc);
            break;
        case 1: // texture: ignored (flat colour)
            break;
        case 3: // callback: ignored
            break;
        }
        if (state->primitiveList != NULL) {
            GXCallDisplayList(state->primitiveList, state->listSize);
        }
        state++;
    }
}

extern ChallengeTexBank* lbl_1_bss_6AAC[];
extern const GXColor lbl_1_rodata_750C;
extern const f32 lbl_1_rodata_7590;
extern const f32 lbl_1_rodata_7594;

// fn_1_1A3B4, size:0x3C0
// Debug viewer: show the selected texture bank's first texture on a quad.
// NONMATCHING 99%: prologue scheduling of the GXColor copy and an extra mr for the texture record pointer
#if NONMATCHING
void fn_1_1A3B4(void) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    GXColor white = lbl_1_rodata_750C;
    GXColor color;
    ChallengeTexBank* bank = lbl_1_bss_6AAC[lbl_803CC1B8->actorIndex];
    DOTexInfo* rec;
    u32 count = bank->count;
    u32 i;

    rec = bank->tex + bank->tex[0].texIndex;

    if (rec->tlut != NULL) {
        for (i = 0; i < count; i++) {
            GXInitTlutObj(&tlutObj, rec->tlut, rec->tlutFormat, rec->tlutEntries);
            GXLoadTlut(&tlutObj, GX_TLUT0);
            GXInitTexObjCI(&texObj, rec->image, rec->width, rec->height, rec->format, GX_CLAMP, GX_CLAMP, GX_FALSE, GX_TLUT0);
            GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            rec++;
        }
    } else {
        for (i = 0; i < count; i++) {
            GXInitTexObj(&texObj, rec->image, rec->width, rec->height, rec->format, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
            GXLoadTexObj(&texObj, GX_TEXMAP0);
            rec++;
        }
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    color = white;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXSetCullMode(GX_CULL_NONE);
    GXLoadPosMtxImm(lbl_1_bss_6B7C.view, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7590;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7594;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_753C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7590;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7590;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7594;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7590;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7594;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_753C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7594;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_753C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_753C;
}
#endif

extern const f32 lbl_1_rodata_7598;
extern const f32 lbl_1_rodata_759C;
extern const f32 lbl_1_rodata_75A0;
extern const f32 lbl_1_rodata_75A4;
extern const f32 lbl_1_rodata_75A8;
extern const f32 lbl_1_rodata_75AC;

// fn_1_1A850, size:0x554
// Debug viewer: draw one bone (at `bone` in `camera` space) as coloured lines.
void fn_1_1A850(MtxPtr bone, MtxPtr camera, u8 r, u8 g, u8 b, u8 a) {
    GXCullMode cullMode;
    Mtx mtx;

    GXGetCullMode(&cullMode);
    PSMTXConcat(camera, bone, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
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
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetLineWidth(7, GX_TO_ZERO);
    GXBegin(GX_LINES, GX_VTXFMT0, 22);
    // bone: a pyramid pointing along +x
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7598;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_759C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A0;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_759C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7598;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_759C;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7598;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A0;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7598;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(r, g, b, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7598;
    GXColor4u8(r, g, b, a);
    // green marker along +y
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0, 0xFF, 0, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0, 0xFF, 0, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0, 0xFF, 0, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0, 0xFF, 0, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75AC;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0, 0xFF, 0, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0, 0xFF, 0, a);
    // magenta marker along +z
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0xFF, 0, 0xFF, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A4;
    GXColor4u8(0xFF, 0, 0xFF, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0xFF, 0, 0xFF, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A4;
    GXColor4u8(0xFF, 0, 0xFF, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75AC;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXColor4u8(0xFF, 0, 0xFF, a);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7520;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_75A4;
    GXColor4u8(0xFF, 0, 0xFF, a);
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetCullMode(cullMode);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
}

extern u8 lbl_1_bss_69F5; // 0 = normal actor rendering, else flat-colour debug rendering
extern const f32 lbl_1_rodata_772C;
void fn_800BD8C4(ChallengeDrawCollection* table, MtxPtr camera);

// fn_1_1D110, size:0x340
// Debug viewer: place the 24 actors from their viewer positions and draw them.
// NONMATCHING 93%: saved-register assignment (task/camera/node pointers) and the task load scheduling differ
#if NONMATCHING
void fn_1_1D110(void) {
    ChallengeRosterQueue* task = lbl_803CC1B8;
    MtxPtr camera = (MtxPtr)(lbl_1_bss_69FC + 0x10); // TODO type
    ChallengeViewerActor* actor;
    ChallengeDrawNode* node;
    s32 i;

    initViewerLights(camera);
    for (i = 0; i < 24; i++) {
        actor = &((ChallengeActorMgr*)lbl_8036E548)->actors[i];
        node = &(*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60))->nodes[i];
        node->visible = (task->viewMode != 1) & (i == task->actorIndex);
        CTRLSetTranslation(&node->worldControl, ((ChallengeActorMgr*)lbl_8036E548)->actors[i].pos.x,
                           ((ChallengeActorMgr*)lbl_8036E548)->actors[i].pos.y,
                           ((ChallengeActorMgr*)lbl_8036E548)->actors[i].pos.z);
        CTRLSetRotation(&node->worldControl, lbl_1_rodata_772C * actor->rot.x, lbl_1_rodata_772C * actor->rot.y,
                        lbl_1_rodata_772C * actor->rot.z);
        node->scale = actor->scale;
        node->setSpeed = 1;
    }
    if (lbl_1_bss_69F5 == 0) {
        // TODO type: UnknownHomes_Static.h declares the camera argument as u32
        fn_800BD670(*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60), (u32)camera);
    } else {
        fn_1_1A290(*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60), camera);
    }
    for (i = 0; i < 24; i++) {
        node = &(*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60))->nodes[i];
        node->visible = 1;
    }
    fn_800BD8C4(*(ChallengeDrawCollection**)(lbl_8036E548 + 0x60), camera);
}
#endif

// Asset table entries (lbl_1_data_F968): load instructions passed to ARAMTransfer.
typedef struct ChallengeAssetEntry {
    const char* path;
    u8 pad04[0xC];
} ChallengeAssetEntry;
extern ChallengeAssetEntry lbl_1_data_F968[];
extern u8 lbl_1_bss_6A94[]; // 1 = actor uses a test model
extern const char lbl_1_rodata_7610[]; // "test/obj/skin/mario/model11.dat"
extern const char lbl_1_rodata_7630[]; // "test/obj/skin/test01/model11.dat"
extern const char lbl_1_rodata_7654[]; // ... test02 .. test07
extern const char lbl_1_rodata_7678[];
extern const char lbl_1_rodata_769C[];
extern const char lbl_1_rodata_76C0[];
extern const char lbl_1_rodata_76E4[];
extern const char lbl_1_rodata_7708[];
// view of the ARAM loader (lbl_803C6CF8, ARAMLoader in main/file_800A6870.h)
typedef struct ChallengeAramLoader {
    u8 pad000[0x715];
    u8 transferDone;
} ChallengeAramLoader;
extern ChallengeAramLoader lbl_803C6CF8;

// fn_1_1CBE4, size:0x504
// Debug viewer loader: set up camera/lights, then load the 24 actor models one by one.
// NONMATCHING 92%: case 0 (inlined fn_1_1B6BC/fn_1_1B0FC) uses one saved register less than the original (which reuses r31 and saves r27)
#if NONMATCHING
void fn_1_1CBE4(u8* object) {
    ChallengeRosterQueue* task = lbl_803CC1B8;
    u8 idx;
    const char* path;

    switch (task->state) {
    case 0:
        lbl_1_bss_6A94[0] = 0;
        lbl_1_bss_6A94[1] = 0;
        lbl_1_bss_6A94[2] = 0;
        lbl_1_bss_6A94[3] = 0;
        lbl_1_bss_6A94[4] = 0;
        lbl_1_bss_6A94[5] = 0;
        lbl_1_bss_6A94[6] = 0;
        lbl_1_bss_6A94[7] = 0;
        lbl_1_bss_6A94[8] = 0;
        lbl_1_bss_6A94[9] = 0;
        lbl_1_bss_6A94[10] = 0;
        lbl_1_bss_6A94[11] = 0;
        lbl_1_bss_6A94[12] = 0;
        lbl_1_bss_6A94[13] = 0;
        lbl_1_bss_6A94[14] = 0;
        lbl_1_bss_6A94[15] = 0;
        lbl_1_bss_6A94[16] = 0;
        lbl_1_bss_6A94[17] = 0;
        lbl_1_bss_6A94[18] = 0;
        lbl_1_bss_6A94[19] = 0;
        lbl_1_bss_6A94[20] = 0;
        lbl_1_bss_6A94[21] = 0;
        lbl_1_bss_6A94[22] = 0;
        lbl_1_bss_6A94[23] = 0;
        task->actorIndex = 0;
        task->viewMode = 0;
        task->_17 = 0;
        task->_18 = 1;
        fn_1_1B6BC();
        allocViewerLights();
        lbl_803CC1B8->state = 2;
        break;
    case 1:
        task->actorIndex++;
        if (task->actorIndex == 24) {
            lbl_803CC1B8->state = 8;
        } else {
            lbl_803CC1B8->state = 2;
        }
        break;
    case 2:
        idx = task->actorIndex;
        path = lbl_1_data_F968[idx].path;
        if (path == lbl_1_rodata_7610 || path == lbl_1_rodata_7630 || path == lbl_1_rodata_7654 ||
            path == lbl_1_rodata_7678 || path == lbl_1_rodata_769C || path == lbl_1_rodata_76C0 ||
            path == lbl_1_rodata_76E4 || path == lbl_1_rodata_7708) {
            lbl_1_bss_6A94[idx] = 1;
        }
        // TODO type: ARAMTransfer returns the loaded data (void*), UnknownHomes_Static.h says s32
        ((ChallengeActorMgr*)lbl_8036E548)->actors[task->actorIndex].model =
            (ChallengeFileRef*)ARAMTransfer(&lbl_1_data_F968[task->actorIndex], 0, 0, 0);
        lbl_803CC1B8->state++;
        break;
    case 3:
        if ((s32)lbl_803C6CF8.transferDone == 1) {
            task->state = 1;
        }
        break;
    case 8:
        task->actorIndex = 0;
        lbl_803CC1B8->state = 0;
        lbl_803CC1B8->update = fn_1_1C8C0;
        break;
    }
}
#endif

ChallengeDrawCollection* ActorObjectInitTable(u16 count);
void LoadActorLayout(void* layout);
void convertGeometryAndSknHeader(void* geometry, void* sknHeader);
void ANIMGet(void* animBank);
void fn_800BDC88(ChallengeDrawCollection* table, u16 index, u16 id, void* layout, void* animBank, void* sknHeader);
void fn_800BD548(ChallengeDrawNode* entry, u8 numArgs, ...);
void fn_800B2C08(ChallengeDrawActor* actor, u16 bone);

// fn_1_1C8C0, size:0x324
// Debug viewer: relocate the 24 loaded model files and create their actors.
// NONMATCHING 81%: same calls and stores; register allocation and node/actor address forms (stfsx vs add+stfs) differ
#if NONMATCHING
void fn_1_1C8C0(u8* object) {
    ChallengeActorMgr* mgr;
    ChallengeFileRef* file;
    u8* isTest;
    ChallengeTexBank** banks;
    void* textures;
    void* geometry;
    void* layout;
    void* skin;
    u32 i;
    u32 j;

    ((ChallengeActorMgr*)lbl_8036E548)->collection = ActorObjectInitTable(24);
    mgr = (ChallengeActorMgr*)lbl_8036E548;
    isTest = lbl_1_bss_6A94;
    banks = lbl_1_bss_6AAC;
    for (i = 0; i < 24; i++) {
        if (i < 24) {
            file = mgr->actors[i].model;
            if (*isTest != 0) {
                for (j = 0; j < 5; j++) {
                    if (j == 4) {
                        mgr->actors[i].anim = (u8*)file + file[j].offset;
                        ANIMGet(mgr->actors[i].anim);
                    } else {
                        mgr->actors[i].model[j].ptr = (u8*)file + file[j].offset;
                    }
                }
            } else {
                file[0].ptr = (u8*)file + file[0].offset;
                mgr->actors[i].model[1].ptr = (u8*)file + file[1].offset;
                mgr->actors[i].model[2].ptr = (u8*)file + file[2].offset;
            }
            textures = mgr->actors[i].model[0].ptr;
            geometry = mgr->actors[i].model[1].ptr;
            layout = mgr->actors[i].model[2].ptr;
            if (*isTest != 0) {
                skin = mgr->actors[i].model[3].ptr;
            } else {
                skin = NULL;
            }
            convertTextureHeader(textures);
            LoadActorLayout(layout);
            if (*isTest != 0) {
                convertGeometryAndSknHeader(geometry, skin);
            } else {
                fn_800BCE38(geometry);
            }
            *banks = textures;
            haveActLayoutPointToGeoHeader(layout, geometry);
            fn_800BD190(geometry, (s32)textures); // TODO type: UnknownHomes_Static.h takes s32
        }
        fn_800BDC88(mgr->collection, i, i, layout, *isTest != 0 ? mgr->actors[i].anim : NULL, skin);
        fn_800BD548(&mgr->collection->nodes[i], 3, mgr->lights[0], mgr->lights[1], mgr->lights[2], mgr->lights[3]);
        CTRLSetTranslation(&mgr->collection->nodes[i].worldControl, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520);
        CTRLSetRotation(&mgr->collection->nodes[i].worldControl, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520);
        mgr->collection->nodes[i].scale = lbl_1_rodata_751C;
        mgr->collection->nodes[i].setSpeed = 1;
        mgr->collection->nodes[i].drawing.actor->flags98 |= 4;
        if (i == 1) {
            fn_800B2C08(mgr->collection->nodes[i].drawing.actor, 0);
        } else {
            fn_800B2C08(mgr->collection->nodes[i].drawing.actor, 1);
        }
        mgr->actors[i].drawActor = mgr->collection->nodes[i].drawing.actor;
        mgr->actors[i].pos.x = lbl_1_rodata_7520;
        mgr->actors[i].pos.y = lbl_1_rodata_7520;
        mgr->actors[i].pos.z = lbl_1_rodata_75F4;
        mgr->actors[i].scale = lbl_1_rodata_751C;
        mgr->actors[i]._25D = (i == 0);
        mgr->collection->nodes[i].drawing.prepare = (void (*)(ChallengeActorDrawing*))fn_1_1D0E8;
        isTest++;
        banks++;
    }
    lbl_803CC1B8->update = fn_1_1C3CC;
}
#endif

extern const GXColor lbl_1_rodata_74F0; // black
extern GXColor lbl_1_data_FB08; // fog colour
extern u8 lbl_80366158[];

// fn_1_1B7DC, size:0xBF0
// Debug viewer menu: B quits; up/down select an item, left/right change it.
// Items: 0 actor, 1 view mode, 2 stick mode, 3 texture view, 4 fog, 5 confetti, 6 colour edit,
// 7-10 material red/green/blue/alpha (only while colour edit is on).
// NONMATCHING 81%: same structure and calls; saved-register numbering in the two inlined confetti init loops differs
#if NONMATCHING
void fn_1_1B7DC(void) {
    ChallengePad* pad = (ChallengePad*)&lbl_803C77B8;
    GXColor black = lbl_1_rodata_74F0;
    GXColor exitFog;
    GXColor leftFogOn;
    GXColor leftFogOff;
    GXColor rightFogOn;
    GXColor rightFogOff;
    ChallengeRosterQueue* task = lbl_803CC1B8;
    ChallengeBoneSelection* sel = &lbl_1_bss_69F0;

    if (pad->down & 0x200) {
        fn_800AD038(*(void**)(lbl_80366158 + 8)); // TODO type
        exitFog = black;
        SetFog(0, (GXColor *)(s32*)&exitFog, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520); // TODO type
        ((ChallengeRosterQueue*)lbl_803CC1B8->_0C)->state = 1;
        minigamesSetSomePointers();
    } else if (pad->repeat & 8) { // up
        if (task->menu != 0) {
            task->menu--;
        } else if (sel->colorEdit != 0) {
            task->menu = 10;
        } else {
            task->menu = 6;
        }
    } else if (pad->repeat & 4) { // down
        task->menu++;
        if (task->menu > 6 && task->menu < 11 && sel->colorEdit == 0) {
            task->menu = 0;
        }
        if (task->menu == 11) {
            task->menu = 0;
        }
    } else if (pad->repeat & 1) { // left
        switch (task->menu) {
        case 0:
            if (task->actorIndex != 0) {
                task->actorIndex--;
            } else {
                task->actorIndex = 23;
            }
            break;
        case 1:
            if (task->viewMode != 0) {
                task->viewMode--;
            } else {
                task->viewMode = 2;
            }
            break;
        case 2:
            if (task->_17 != 0) {
                task->_17--;
            } else {
                task->_17 = 1;
            }
            break;
        case 3:
            if (task->_18 != 0) {
                task->_18--;
            } else {
                task->_18 = 1;
            }
            break;
        case 4:
            if ((sel->fog = !sel->fog)) {
                leftFogOn = lbl_1_data_FB08;
                SetFog(4, (GXColor *)(s32*)&leftFogOn, lbl_1_rodata_7520, lbl_1_rodata_75C0, lbl_1_rodata_753C, lbl_1_rodata_7540); // TODO type
            } else {
                leftFogOff = black;
                SetFog(0, (GXColor *)(s32*)&leftFogOff, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520); // TODO type
            }
            break;
        case 5:
            if ((sel->confetti = !sel->confetti)) {
                ChallengeConfettiTask* confetti = fn_80033A24(fn_1_1857C, 0, 0, lbl_1_data_FB24.count, 1, 0x80);
                if (confetti != NULL) {
                    initConfetti(confetti);
                }
            } else {
                minigamesSetSomePointers();
            }
            break;
        case 6:
            sel->colorEdit = !sel->colorEdit;
            break;
        case 7:
            if (sel->colorEdit != 0) {
                sel->matRed--;
            }
            break;
        case 8:
            if (sel->colorEdit != 0) {
                sel->matGreen--;
            }
            break;
        case 9:
            if (sel->colorEdit != 0) {
                sel->matBlue--;
            }
            break;
        case 10:
            if (sel->colorEdit != 0) {
                sel->matAlpha--;
            }
            break;
        }
    } else if (pad->repeat & 2) { // right
        switch (task->menu) {
        case 0:
            task->actorIndex++;
            if (task->actorIndex == 24) {
                task->actorIndex = 0;
            }
            break;
        case 1:
            task->viewMode++;
            if (task->viewMode == 3) {
                task->viewMode = 0;
            }
            break;
        case 2:
            task->_17++;
            if (task->_17 == 2) {
                task->_17 = 0;
            }
            break;
        case 3:
            task->_18++;
            if (task->_18 == 2) {
                task->_18 = 0;
            }
            break;
        case 4:
            if ((sel->fog = !sel->fog)) {
                rightFogOn = lbl_1_data_FB08;
                SetFog(4, (GXColor *)(s32*)&rightFogOn, lbl_1_rodata_7520, lbl_1_rodata_75C0, lbl_1_rodata_753C, lbl_1_rodata_7540); // TODO type
            } else {
                rightFogOff = black;
                SetFog(0, (GXColor *)(s32*)&rightFogOff, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520, lbl_1_rodata_7520); // TODO type
            }
            break;
        case 5:
            if ((sel->confetti = !sel->confetti)) {
                ChallengeConfettiTask* confetti = fn_80033A24(fn_1_1857C, 0, 0, lbl_1_data_FB24.count, 1, 0x80);
                if (confetti != NULL) {
                    initConfetti(confetti);
                }
            } else {
                minigamesSetSomePointers();
            }
            break;
        case 6:
            sel->colorEdit = !sel->colorEdit;
            break;
        case 7:
            if (sel->colorEdit != 0) {
                sel->matRed++;
            }
            break;
        case 8:
            if (sel->colorEdit != 0) {
                sel->matGreen++;
            }
            break;
        case 9:
            if (sel->colorEdit != 0) {
                sel->matBlue++;
            }
            break;
        case 10:
            if (sel->colorEdit != 0) {
                sel->matAlpha++;
            }
            break;
        }
    }
}
#endif

extern u8 lbl_803CBBC0; // current frame buffer (0/1)
// Minimal draw-list links (cf. DrawNode in main/file_80069BDC.h), one per frame buffer.
typedef struct ChallengeDrawLink {
    u32 link; // set by fn_800A7D4C
    void (*draw)(void);
} ChallengeDrawLink;
extern ChallengeDrawLink lbl_1_data_FAE8[2]; // fn_1_1ADA4 (grid)
extern ChallengeDrawLink lbl_1_data_FAF8[2]; // fn_1_1A774 (bones)
extern void fn_800A7D4C(s32 layer, void* node);

// fn_1_1C3CC, size:0x4F4
// Debug viewer main update: menu, actor/camera control, then queue the draws.
// NONMATCHING 58%: the original addresses lbl_1_data_FB0C/FB18/FAE8/FAF8 from one .data base (lbl_1_data_F888 + off); plus the scheduling of the inlined fn_1_1B2C8/fn_1_1B424
#if NONMATCHING
void fn_1_1C3CC(u8* object) {
    Mtx44 proj;
    ChallengeRosterQueue* task = lbl_803CC1B8;

    C_MTXFrustum(proj, lbl_1_rodata_752C, lbl_1_rodata_7530, lbl_1_rodata_7534, lbl_1_rodata_7538, lbl_1_rodata_753C, lbl_1_rodata_7540);
    GXSetProjection(proj, GX_PERSPECTIVE);
    fn_1_1B7DC();
    if (task->_17 != 0) {
        moveSelectedActor();
    } else {
        updateViewerCamera();
    }
    PSMTXCopy(lbl_1_bss_69F0.matrix, (MtxPtr)(lbl_1_bss_69FC + 0x10)); // TODO type
    lbl_1_bss_69F0.selectedActor = task->actorIndex;
    fn_800A7D4C(0, &lbl_1_data_FAE8[lbl_803CBBC0]);
    if (task->viewMode != 2) {
        fn_800A7D4C(0, &lbl_1_data_FAF8[lbl_803CBBC0]);
    }
    fn_1_1D110();
    if (task->_18 != 0) {
        fn_1_1A3B4();
    }
}
#endif
