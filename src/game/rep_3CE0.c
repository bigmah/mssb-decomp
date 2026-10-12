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

#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "main/file_80069BDC.h"

extern u8 lbl_803CBBC0; // frame buffer index

// Marker width/radius per size class (x100000).
static s32 lbl_3_data_27EC0[3][2] = {{15000, 90000}, {20000, 129999}, {30000, 180000}};
// Marker size class per character kind.
static u8 lbl_3_data_27ED8[0x38] = {
    1, 1, 2, 1, 1, 1, 1, 0, 0, 2, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 2, 2, 2, 0, 0, 0, 1,
    0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
};
static PlayerMarkerLayout lbl_3_data_27F10 = {
    64, 16,
    {{0, 0, 0xFFFF0080, 0xFFFFC818}},
    {{-200000, 0, 0xFFFF0080, 0xFFFFC818}, {200000, 0, 0xFFFF0080, 0xFFFFC818}},
    {{0, 0, 0xFFFF0080, 0xFFFFC818}, {-300000, 0, 0xFFFF0080, 0xFFFFC818}, {300000, 0, 0xFFFF0080, 0xFFFFC818}},
    900000,
};
// Orthographic projection for the full-screen quads (640x448).
static Mtx44 lbl_3_data_28104 = {
    {0.003125f, 0.0f, 0.0f, -1.0f},
    {0.0f, -0.004464286f, 0.0f, 1.0f},
    {0.0f, 0.0f, -5.9604645e-08f, -1.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};
// Display list: one quad through position indices 0-3, colour 0xFFFF (GX_RGBA4).
static u8 lbl_3_data_28160[0x20] ATTRIBUTE_ALIGN(32) = {
    0x80, 0x00, 0x04, 0x00, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0x02, 0xFF, 0xFF, 0x03, 0xFF, 0xFF, 0x00,
};
// Its positions: a full-screen quad at the far plane (A) or at z = -1 (B).
static f32 lbl_3_data_28180[4][3] ATTRIBUTE_ALIGN(32) = {
    {0.0f, 0.0f, -16777215.0f}, {0.0f, 448.0f, -16777215.0f}, {640.0f, 448.0f, -16777215.0f}, {640.0f, 0.0f, -16777215.0f},
};
static f32 lbl_3_data_281C0[4][3] ATTRIBUTE_ALIGN(32) = {
    {0.0f, 0.0f, -1.0f}, {0.0f, 448.0f, -1.0f}, {640.0f, 448.0f, -1.0f}, {640.0f, 0.0f, -1.0f},
};

// NONMATCHING 99%: node and camIdx/i get r27/r28 the other way round (declaration order and
// reusing i for camIdx do not change it)
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

    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    PSMTXIdentity(identity);
    GXSetZCompLoc(GX_FALSE);
    // Fill the depth buffer with the far plane (full-screen quad, colour/alpha writes off).
    GXSetProjection(lbl_3_data_28104, GX_ORTHOGRAPHIC);
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
    GXSetArray(GX_VA_POS, lbl_3_data_28180, 0xC);
    GXCallDisplayList(lbl_3_data_28160, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    camIdx = fn_8005268C();
    cam = fn_80052734(camIdx);
    fn_80052694(camIdx);
    gOz_GXSetTexture(0, 0, 0);

    if (lbl_3_common_bss_35154.count != 0 && lbl_3_common_bss_35154.done != 0) {
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
    GXSetProjection(lbl_3_data_28104, GX_ORTHOGRAPHIC);
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
    GXSetProjection(lbl_3_data_28104, GX_ORTHOGRAPHIC);
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
    GXSetArray(GX_VA_POS, lbl_3_data_28180, 0xC);
    GXCallDisplayList(lbl_3_data_28160, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
}
#endif

// NONMATCHING 67%: data pool layout now right (statics); scheduling of the pool/rodata loads in the
// prologue and the saved-register numbering differ (stmw r24 vs r25)
// Places one marker per argument (each argument is a player slot 0-3); several
// markers on the same player are spread out using the layout slots.
// .text:0x0015FB84 size:0x3A4 mapped:0x8079EC18
#if NONMATCHING
void fn_3_15FB84(s32 count, ...) {
    PlayerMarkerLayout* lay = &lbl_3_data_27F10;
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
    node->fadeColor = lbl_3_common_bss_35154.level;

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
                m->width = (f32)lbl_3_data_27EC0[lbl_3_data_27ED8[actor->kind]][0] / 100000.0f;
                m->radius = (f32)lbl_3_data_27EC0[lbl_3_data_27ED8[actor->kind]][1] / 100000.0f;
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

// .text:0x0015FA58 size:0x12C mapped:0x8079EAEC
void fn_3_15FA58(s32 n, s32* ids) {
    SceneTask* task;
    s32 i;

    task = fn_800B0A5C_insertQueue(fn_3_15F9C0, lbl_803CC1B8->priority);
    lbl_3_common_bss_35154.active = 1;
    lbl_3_common_bss_35154.done = 0;
    lbl_3_common_bss_35154.level = 0;
    lbl_3_common_bss_35154.count = 0;
    for (i = n; i != 0; i--) {
        lbl_3_common_bss_35154.ids[lbl_3_common_bss_35154.count++] = *ids++;
    }
    task->_10 = lbl_3_data_27F10.fadeDuration;
}

// .text:0x0015F9C0 size:0x98 mapped:0x8079EA54
void fn_3_15F9C0(void) {

    if (g_d_GameSettings._55 != 0 || lbl_3_common_bss_35154.disabled != 0) {
        REMOVE_QUEUE_NOARG();
        return;
    }
    lbl_803CC1B8->_10--;
    lbl_3_common_bss_35154.level = lbl_3_data_27F10.fadeScale * (lbl_3_data_27F10.fadeDuration - lbl_803CC1B8->_10) / lbl_3_data_27F10.fadeDuration;
    if (lbl_803CC1B8->_10 == 0) {
        REMOVE_QUEUE_NOARG();
    }
}

// .text:0x0015F9AC size:0x14 mapped:0x8079EA40
void fn_3_15F9AC(void) {
    lbl_3_common_bss_35154.done = 1;
}

// .text:0x0015F998 size:0x14 mapped:0x8079EA2C
void fn_3_15F998(void) {
    lbl_3_common_bss_35154.active = 0;
}

// .text:0x0015F874 size:0x124 mapped:0x8079E908
void fn_3_15F874(s32 useB) {
    Mtx m;

    GXSetProjection(lbl_3_data_28104, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    gOz_GXSetTexture(GX_PASSCLR, 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0);
    if (useB) {
        GXSetArray(GX_VA_POS, lbl_3_data_281C0, 0xC);
    } else {
        GXSetArray(GX_VA_POS, lbl_3_data_28180, 0xC);
    }
    GXCallDisplayList(lbl_3_data_28160, 0x20);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
}
