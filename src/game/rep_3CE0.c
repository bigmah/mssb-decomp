#include "game/rep_3CE0.h"
#define REP_HEADER_FN repHeader_3CE0
#include "header_rep_inline.h"
#include "stl/stdarg.h"
#include "stl/mem.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"
#include "main/file_80011640.h"
#include "main/file_80024184.h"
#include "main/file_8004C5F8.h"

extern PlayerMarkerData lbl_3_data_27EC0;
extern u8 lbl_803CBBC0; // frame buffer index
// Stadium effect state (lbl_3_common_bss_35154); only the fields used here.
extern struct {
    /*0x000*/ u8 _000[0x4];
    /*0x004*/ u8* effectFile;
    /*0x008*/ u8 _008[0x468 - 0x8];
    /*0x468*/ u32 fadeColor;
    /*0x46C*/ u8 _46C[0x471 - 0x46C];
    /*0x471*/ u8 _471;
    /*0x472*/ u8 _472;
} lbl_3_common_bss_35154;

// NONMATCHING 69%: the original addresses each table (size, sizeClass, layout, nodes) through its own
// pooled base register (separate static objects in the original TU); ours folds them into one struct
// Places one marker per argument (each argument is a player slot 0-3); several
// markers on the same player are spread out using the layout slots.
// .text:0x0015FB84 size:0x3A4 mapped:0x8079EC18
#if NONMATCHING
void fn_3_15FB84(s32 count, ...) {
    PlayerMarkerData* d = &lbl_3_data_27EC0;
    PlayerMarkerLayout* lay = &d->layout;
    s32 perPlayer[4];
    va_list args;
    PlayerMarker* m;
    PlayerMarkerSlot* slot;
    CharActor* actor;
    f32 yOffset;
    s32 i;
    s32 n;
    PlayerMarkerNode* node;

    yOffset = -((f32)lay->height / 100000.0f);
    node = &lay->nodes[lbl_803CBBC0];
    node->count = count;
    node->tex = (TexImage*)(lbl_3_common_bss_35154.effectFile + 0x344); // TODO type
    node->fadeColor = lbl_3_common_bss_35154.fadeColor;

    memset(perPlayer, 0, sizeof(perPlayer));
    va_start(args, count);
    for (i = 0; i < count; i++) {
        perPlayer[va_arg(args, s32)]++;
    }

    n = 0;
    m = lay->nodes[lbl_803CBBC0].markers;
    for (i = 0; i < 4; i++) {
        actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            switch (perPlayer[i]) {
            case 0:
                break;
            case 1:
                slot = lay->one;
                break;
            case 2:
                slot = lay->two;
                break;
            case 3:
            default:
                slot = lay->three;
                break;
            }
            while (perPlayer[i]-- != 0) {
                m->active = 1;
                n++;
                m->top.x = actor->pos.x + (f32)slot->dx / 100000.0f;
                m->top.y = yOffset + (actor->pos.y + (f32)slot->dy / 100000.0f);
                m->top.z = actor->pos.z;
                m->base.x = actor->pos.x;
                m->base.y = actor->pos.y;
                m->base.z = actor->pos.z;
                m->width = (f32)d->size[d->sizeClass[actor->kind]][0] / 100000.0f;
                m->radius = (f32)d->size[d->sizeClass[actor->kind]][1] / 100000.0f;
                m->topColor = slot->topColor;
                m->baseColor = slot->baseColor;
                slot++;
                m++;
            }
        }
    }
    for (; n < 4; n++) {
        m->active = 0;
        m++;
    }
    fn_800A7D4C(11, &lay->nodes[lbl_803CBBC0].hdr);
}

#endif

// NONMATCHING 93%: float constant pooling (docs/patterns/floats.md) and the original keeps the
// lbl_3_data_27EC0 pool base in r30 for the first depth-clear block too
// .text:0x0015FF28 size:0x650 mapped:0x8079EFBC
#if NONMATCHING
void fn_3_15FF28(PlayerMarkerNode* node) {
    Mtx identity;
    Vec v;
    Vec dir;
    camera_803c639c_s* cam;
    s32 camIdx;
    s32 i;
    Mtx clearMtx1;
    Mtx clearMtx2;
    PlayerMarkerData* d = &lbl_3_data_27EC0;

    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    PSMTXIdentity(identity);
    GXSetZCompLoc(GX_FALSE);
    // Fill the depth buffer with the far plane (full-screen quad, colour/alpha writes off).
    GXSetProjection(d->layout.orthoProj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(clearMtx1);
    GXLoadPosMtxImm(clearMtx1, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    gOz_GXSetTexture(4, 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0);
    GXSetArray(GX_VA_POS, d->layout.clearVerts, 0xC);
    GXCallDisplayList(d->layout.clearDL, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    camIdx = fn_8005268C();
    cam = fn_80052734(camIdx);
    fn_80052694(camIdx);
    gOz_GXSetTexture(0, 0, 0);

    if (lbl_3_common_bss_35154._472 != 0 && lbl_3_common_bss_35154._471 != 0) {
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
        GXLoadPosMtxImm(identity, GX_PNMTX0);
        SetDisplayStateTexture(NULL, 0, 0);
        for (i = 0; i < node->count; i++) {
            if (node->markers[i].active != 0) {
                PSMTXMultVec(cam->view, &node->markers[i].top, &v);
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(v.x - node->markers[i].width, v.y, v.z);
                GXColor1u32(node->markers[i].topColor);
                GXTexCoord2u16(0, 0);
                GXPosition3f32(v.x + node->markers[i].width, v.y, v.z);
                GXColor1u32(node->markers[i].topColor);
                GXTexCoord2u16(1, 0);
                PSMTXMultVec(cam->view, &node->markers[i].base, &v);
                dir.x = v.x;
                dir.y = 0.0f;
                dir.z = v.z;
                if (PSVECMag(&dir)) {
                    PSVECNormalize(&dir, &dir);
                    PSVECScale(&dir, node->markers[i].radius, &dir);
                } else {
                    dir.x = node->markers[i].radius;
                    dir.z = 0.0f;
                }
                GXPosition3f32(v.x - dir.z, v.y, v.z + dir.x);
                GXColor1u32(node->markers[i].baseColor);
                GXTexCoord2u16(1, 1);
                GXPosition3f32(v.x + dir.z, v.y, v.z - dir.x);
                GXColor1u32(node->markers[i].baseColor);
                GXTexCoord2u16(0, 1);
            }
        }

        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        GXLoadPosMtxImm(cam->view, GX_PNMTX0);
        SetDisplayStateTexture(node->tex, 0, 0);
        for (i = 0; i < node->count; i++) {
            if (node->markers[i].active != 0) {
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                GXPosition3f32(node->markers[i].base.x - node->markers[i].radius, node->markers[i].base.y, node->markers[i].base.z - node->markers[i].radius);
                GXColor1u32(node->markers[i].baseColor);
                GXTexCoord2u16(0, 0);
                GXPosition3f32(node->markers[i].base.x + node->markers[i].radius, node->markers[i].base.y, node->markers[i].base.z - node->markers[i].radius);
                GXColor1u32(node->markers[i].baseColor);
                GXTexCoord2u16(1, 0);
                GXPosition3f32(node->markers[i].base.x + node->markers[i].radius, node->markers[i].base.y, node->markers[i].base.z + node->markers[i].radius);
                GXColor1u32(node->markers[i].baseColor);
                GXTexCoord2u16(1, 1);
                GXPosition3f32(node->markers[i].base.x - node->markers[i].radius, node->markers[i].base.y, node->markers[i].base.z + node->markers[i].radius);
                GXColor1u32(node->markers[i].baseColor);
                GXTexCoord2u16(0, 1);
            }
        }
    }

    // Full-screen fade quad at the far plane.
    GXSetProjection(d->layout.orthoProj, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    SetDisplayStateTexture(NULL, 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -16777215.0f);
    GXColor1u32(node->fadeColor);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(640.0f, 0.0f, -16777215.0f);
    GXColor1u32(node->fadeColor);
    GXTexCoord2u16(1, 0);
    GXPosition3f32(640.0f, 448.0f, -16777215.0f);
    GXColor1u32(node->fadeColor);
    GXTexCoord2u16(1, 1);
    GXPosition3f32(0.0f, 448.0f, -16777215.0f);
    GXColor1u32(node->fadeColor);
    GXTexCoord2u16(0, 1);
    // Fill the depth buffer again.
    GXSetProjection(d->layout.orthoProj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(clearMtx2);
    GXLoadPosMtxImm(clearMtx2, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    gOz_GXSetTexture(4, 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0);
    GXSetArray(GX_VA_POS, d->layout.clearVerts, 0xC);
    GXCallDisplayList(d->layout.clearDL, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
}
#endif
