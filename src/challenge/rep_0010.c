#include "challenge/rep_0010.h"
#include "challenge/auto_00_00001538_text.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "main/file_80008E00.h"

#pragma pool_data off

extern void SetDisplayStateTexture(struct TexImage* tex, s32 map, u32 tlutName);
extern void gOz_GXSetTexture(GXTevMode tevMode, s32 texFrac, s32 hasNormal);
extern void fn_800AD054(void* lo, void* hi);
extern void fn_800B0C80(void (*draw)(void));
extern void resetAllDrawingStructs(void);

extern GXColor lbl_1_data_A8; // copy-clear color

// Unreferenced table at the start of this unit's .rodata.
const f32 lbl_1_rodata_10[20] = {
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
};

// .text:0x000005EC size:0x508
// Draws a test pattern: a grey backdrop and four additive diamonds.
void fn_1_5EC(void) {
    Mtx44 p;
    Mtx m;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    // 1 is the SDK GX_TG_MTX2x4 (GXEnum.h has the 2x4/3x4 names swapped)
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    C_MTXOrtho(p, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXSetProjection(p, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXPosition3f32(0.0f, 448.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXPosition3f32(640.0f, 448.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXPosition3f32(640.0f, 0.0f, -0.5f);
    GXColor1u32(0x808080FF);
    GXEnd();

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_CLEAR);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(100.0f, 100.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(50.0f, 150.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(100.0f, 200.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(150.0f, 150.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXEnd();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(120.0f, 100.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(70.0f, 150.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(120.0f, 200.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(170.0f, 150.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXEnd();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(120.0f, 220.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(70.0f, 270.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(120.0f, 320.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXPosition3f32(170.0f, 270.0f, -0.5f);
    GXColor1u32(0xFF000080);
    GXEnd();

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(100.0f, 220.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(50.0f, 270.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(100.0f, 320.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXPosition3f32(150.0f, 270.0f, -0.5f);
    GXColor1u32(0x00FF0080);
    GXEnd();
}

// .text:0x00000AF4 size:0x438
// Draws a white line grid on the y = 0 plane, centred on the origin.
// NONMATCHING 99%: f1/f2 swapped for the 0.5f constant and the (f32)rows temp
#if NONMATCHING
void fn_1_AF4(s32 rows, s32 cols, f32 spacing) {
    f32 x;
    f32 z;
    f32 x0;
    f32 width;
    f32 zEnd;
    f32 xEnd;
    f32 depth;
    s32 i;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    width = cols * spacing;
    x0 = -spacing * cols * 0.5f;
    z = -spacing * rows * 0.5f;
    x = x0;

    GXBegin(GX_LINES, GX_VTXFMT0, (cols + 1) * 2);
    depth = rows * spacing; // separate statement: no fmadds
    zEnd = z + depth;
    for (i = cols; i >= 0; i--) {
        GXPosition3f32(x, 0.0f, z);
        GXColor1u32(0xFFFFFFFF);
        GXPosition3f32(x, 0.0f, zEnd);
        GXColor1u32(0xFFFFFFFF);
        x += spacing;
    }
    GXBegin(GX_LINES, GX_VTXFMT0, (rows + 1) * 2);
    xEnd = x0 + width;
    for (i = rows; i >= 0; i--) {
        GXPosition3f32(x0, 0.0f, z);
        GXColor1u32(0xFFFFFFFF);
        GXPosition3f32(xEnd, 0.0f, z);
        GXColor1u32(0xFFFFFFFF);
        z += spacing;
    }
}
#endif

// .text:0x00000F2C size:0x1D8
// Same as gOz_GXSetTexture without the GX thread check.
void fn_1_F2C(GXTevMode tevMode, s32 texFrac, s32 hasNormal) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    if (hasNormal) {
        GXSetVtxDesc(GX_VA_NRM, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_NBT, GX_F32, 0);
    }
    switch (tevMode) {
    case GX_MODULATE:
    case GX_PASSCLR:
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        if (tevMode == GX_PASSCLR) {
            break;
        }
    case GX_REPLACE:
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        if (texFrac == -1) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        } else {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, (u8)texFrac);
        }
        break;
    }
    GXSetTevOrder(GX_TEVSTAGE0, tevMode == GX_PASSCLR ? GX_TEXCOORD_NULL : GX_TEXCOORD0,
                  tevMode == GX_PASSCLR ? GX_TEXMAP_NULL : GX_TEXMAP0, tevMode == GX_REPLACE ? GX_COLOR_NULL : GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(tevMode != GX_REPLACE);
    GXSetNumTexGens(tevMode != GX_PASSCLR);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, tevMode);
}

// .text:0x00001104 size:0x4
void _epilog(void) {
    return;
}

// .text:0x00001108 size:0x4
void _unresolved(void) {
    return;
}

// .text:0x0000110C size:0x3C
void _prolog(void) {
    fn_800B0C80(fn_1_1148);
    fn_800AD054(lbl_80366158.arenaAfterDll, lbl_80366158.arenaEnd);
}

// .text:0x00001148 size:0x88
// Root task of the challenge test module: resets the menu and the display.
void fn_1_1148(void) {
    ChMenuTask* task = lbl_803CC1B8;

    task->cursor = 0;
    task->_14 = 0;
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054(lbl_80366158.arenaAfterDll, lbl_80366158.arenaEnd);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    ((ChMenuTask*)lbl_803CC1B8)->h.func = fn_1_16A0;
}

// .text:0x000011D0 size:0x70
// Back from a test: resets the display and returns to the menu.
void fn_1_11D0(void) {
    resetAllDrawingStructs();
    fn_80009144();
    fn_800AD054(lbl_80366158.arenaAfterDll, lbl_80366158.arenaEnd);
    GXSetCopyClear(lbl_1_data_A8, 0xFFFFFF);
    ((ChMenuTask*)lbl_803CC1B8)->h.func = fn_1_16A0;
}

