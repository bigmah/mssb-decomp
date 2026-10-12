#include "challenge/rep_0000.h"
#include "challenge/rep_0010.h"
#include "challenge/auto_00_00001538_text.h"
#include "challenge/auto_00_000085A8_text.h"
#include "challenge/auto_00_00026AF8_text.h"
#include "challenge/ch_data.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "main/file_80008E00.h"
#include "Unknown/File_0x800a64e0.h"

// The first source file of challenge.rel: rep_0000, rep_0010 and
// auto_00_00001538_text were split out of it (one .rodata/.data/.bss).

// Unreferenced constants ahead of the shared rodata table: like that table,
// the local static of an unused inline function (see header_rep_inline.h).
#ifdef __MWERKS__
extern
#else
static
#endif
inline f32 repHeaderConst_0000(s32 i) {
    static const f32 values[4] = { 1.75f, 0.0f, 2.125f, 0.0f };
    return values[i];
}
#define REP_HEADER_FN repHeader_0000
#include "header_rep_inline.h"

extern u8 lbl_803C6CF8[]; // TODO type: ARAMLoader (main/file_800A6870.h); idle at 0x715


extern void fn_800A7D4C(s32 list, void* node);
extern u8 lbl_803CBBC0; // frame buffer index (0/1)

// Test entry points (other challenge units).
extern void fn_1_66C4(void);
extern void fn_1_17D90(void);
extern void fn_1_28200(void);
extern void fn_1_1D514(void);
extern void fn_1_A2E4(void);
extern void fn_1_24778(void);
extern void fn_1_2852C(void);
extern void fn_1_29A9C(void);

// Texture viewer task (fn_1_1634 -> fn_1_15CC -> fn_1_1538).
typedef struct ChTexViewTask {
    /*0x00*/ ChTaskHeader h;
    /*0x14*/ s32* file;         // loaded file; word 0 is the offset of the texture archive
    /*0x18*/ ChTexArchive* tex; // inside file
} ChTexViewTask;


// .data of this file; the jump tables of fn_1_1E0 and fn_1_1634 follow it.
// Texture viewer: the archive files, a draw node per frame buffer and the draw mode.
static ChFileEntry lbl_1_data_0[7] = {
    { 0x40B, 0x40022EF0, 0x07684800, 0x16B18 },
    { 0x40B, 0x40020260, 0x0769B800, 0x12864 },
    { 0x40B, 0x4002FDC0, 0x076AE800, 0x207F8 },
    { 0x40B, 0x40024E2C, 0x076CF000, 0x159AC },
    { 0x40B, 0x4001CB88, 0x076E5000, 0xEE60 },
    { 0x40B, 0x40035BD0, 0x076F4000, 0x257FC },
    { 0x40B, 0x400397CC, 0x07719800, 0x23FF4 },
};
static ChTexDrawNode lbl_1_data_70[2] = {
    { NULL, fn_1_1240, NULL, 0, 0, { 0, 0, 0, 0 } },
    { NULL, fn_1_1240, NULL, 0, 0, { 0, 0, 0, 0 } },
};
static u32 lbl_1_data_A0 = 2;                              // draw mode of the nodes
static GXColor lbl_1_data_A4 = { 0xFF, 0xFF, 0xFF, 0xFF }; // colour of the nodes
static GXColor lbl_1_data_A8 = { 0x11, 0x77, 0x55, 0x00 }; // copy-clear color (fn_1_1148)
// Disc file table loaded by fn_1_1E0: { 0, size, disc offset, size } per file.
static ChFileEntry lbl_1_data_AC[15] = {
    { 0, 0x01070000, 0x00000000, 0x01070000 },
    { 0, 0x01040000, 0x01070000, 0x01040000 },
    { 0, 0x01020000, 0x020B0000, 0x01020000 },
    { 0, 0x01070000, 0x030D0000, 0x01070000 },
    { 0, 0x01088000, 0x04140000, 0x01088000 },
    { 0, 0x01040000, 0x051C8000, 0x01040000 },
    { 0, 0x00A18000, 0x06208000, 0x00A18000 },
    { 0, 0x00A18000, 0x06C20000, 0x00A18000 },
    { 0, 0x00AC0000, 0x07638000, 0x00AC0000 },
    { 0, 0x01010000, 0x080F8000, 0x01010000 },
    { 0, 0x009A8000, 0x09108000, 0x009A8000 },
    { 0, 0x00198000, 0x09AB0000, 0x00198000 },
    { 0, 0x00038000, 0x09C48000, 0x00038000 },
    { 0, 0x00C40000, 0x09C80000, 0x00C40000 },
    { 0, 0x00040000, 0x0A8C0000, 0x00040000 },
};

// .bss, laid out in reverse definition order.
static u8 lbl_1_bss_4[0x5C]; // LoadFile buffer (fn_1_1E0)
static s32 lbl_1_bss_0;      // texture shown by the viewer
extern ChDrawNode lbl_1_data_298[2];

extern void fn_1_16A0(void);
extern void fn_1_1E0(void);
extern void ANIMGet(void* bank);
extern void LoadActorLayout(void* actor);
extern void convertGeometryAndSknHeader(void* geometry, void* skin);
extern void fn_80025DDC(void* object);
extern u8 lbl_800F1D78[];
extern s32 LoadFile(void* entry, void* track, u32 offset, void (*callback)(u32), u32 mode);
extern s32 fn_800A8518(s32);
extern u32 fn_800A88C8(void);
extern s32 fn_800A8B78(void*);

extern void SetDisplayStateTexture(struct TexImage* tex, s32 map, u32 tlutName);
extern void gOz_GXSetTexture(GXTevMode tevMode, s32 texFrac, s32 hasNormal);
extern void fn_800AD054(void* lo, void* hi);
extern void fn_800B0C80(void (*draw)(void));
extern void resetAllDrawingStructs(void);

// .text:0x0000196C size:0x40
void fn_1_196C(void) {
    fn_800A7D4C(0, &lbl_1_data_298[lbl_803CBBC0]);
}

// .text:0x00001948 size:0x24
// Waits for the running test to finish.
void fn_1_1948(void) {
    ChTaskHeader* task = lbl_803CC1B8;

    if (task->result != 0) {
        task->func = fn_1_11D0;
    }
}

// .text:0x000016A0 size:0x2A8
// Test menu: up/down picks a test, A starts it, Z quits.
void fn_1_16A0(void) {
    ChMenuTask* task = lbl_803CC1B8;

    if (lbl_803C77B8._04 == 8) {
        if (--task->cursor < 0) {
            task->cursor = 9;
        }
    } else if (lbl_803C77B8._04 == 4) {
        if (++task->cursor >= 10) {
            task->cursor = 0;
        }
    } else if (lbl_803C77B8._02 == 0x100) {
        switch ((u8)task->cursor) {
        case 0:
            fn_800B0A5C_insertQueue(fn_1_66C4, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 1:
            fn_800B0A5C_insertQueue(fn_1_8B90, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 2:
            fn_800B0A5C_insertQueue(fn_1_17D90, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 3:
            fn_800B0A5C_insertQueue(fn_1_28200, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 4:
            fn_800B0A5C_insertQueue(fn_1_1D514, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 5:
            fn_800B0A5C_insertQueue(fn_1_26AF8, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 6:
            fn_800B0A5C_insertQueue(fn_1_A2E4, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 7:
            fn_800B0A5C_insertQueue(fn_1_24778, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 8:
            fn_800B0A5C_insertQueue(fn_1_2852C, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 9:
            fn_800B0A5C_insertQueue(fn_1_29A9C, 10);
            ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1948;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            break;
        }
    } else if (lbl_803C77B8._02 == 0x1000) {
        task->h.parent->result = 1;
    } else if ((lbl_803C77B8._00 & 0xA00) == 0xA00) {
        task->h.func = fn_1_58C;
    }
}

// .text:0x00001634 size:0x6C
void fn_1_1634(void) {
    if ((s32)lbl_803C6CF8[0x715] == 1) {
        ((ChTexViewTask*)lbl_803CC1B8)->file = (s32*)ARAMTransfer(&lbl_1_data_0[3], 0, 0, 0);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_15CC;
    }
}

// .text:0x000015CC size:0x68
void fn_1_15CC(void) {
    ChTexViewTask* task = lbl_803CC1B8;

    if ((s32)lbl_803C6CF8[0x715] == 1) {
        task->tex = (ChTexArchive*)((u8*)task->file + *task->file);
        convertTextureHeader(task->tex);
        ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_1538;
    }
}

// .text:0x00001538 size:0x94
// Queues this frame's texture draw node.
void fn_1_1538(void) {
    ChTexViewTask* task = lbl_803CC1B8;

    fn_800A7D4C(0, &lbl_1_data_70[lbl_803CBBC0]);
    lbl_1_data_70[lbl_803CBBC0].tex = task->tex;
    lbl_1_data_70[lbl_803CBBC0].texIdx = lbl_1_bss_0;
    lbl_1_data_70[lbl_803CBBC0].mode = lbl_1_data_A0;
    lbl_1_data_70[lbl_803CBBC0].color = lbl_1_data_A4;
}

// .text:0x00001240 size:0x2F8
// Draws texture node->texIdx of node->tex as a 256x256 quad in the top-left corner.
void fn_1_1240(ChTexDrawNode* node) {
    Mtx44 p;
    Mtx m;
    GXColor color;

    SetDisplayStateTexture((struct TexImage*)node->tex->images[node->texIdx], GX_TEXMAP0, 0);
    PSMTXIdentity(m);
    C_MTXOrtho(p, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetProjection(p, GX_ORTHOGRAPHIC);
    gOz_GXSetTexture(GX_MODULATE, 0, 0);
    color.r = node->color.r;
    color.g = node->color.g;
    color.b = node->color.b;
    color.a = node->color.a;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    if (node->mode == 1) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    } else if (node->mode == 2) {
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(256.0f, 0.0f, 0.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(1, 0);
    GXPosition3f32(256.0f, 256.0f, 0.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(1, 1);
    GXPosition3f32(0.0f, 256.0f, 0.0f);
    GXColor1u32(0xFFFFFFFF);
    GXTexCoord2u16(0, 1);
    GXEnd();
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

// .text:0x0000110C size:0x3C
void _prolog(void) {
    fn_800B0C80(fn_1_1148);
    fn_800AD054(lbl_80366158.arenaAfterDll, lbl_80366158.arenaEnd);
}

// .text:0x00001108 size:0x4
void _unresolved(void) {
    return;
}

// .text:0x00001104 size:0x4
void _epilog(void) {
    return;
}

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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(tevMode != GX_REPLACE);
    GXSetNumTexGens(tevMode != GX_PASSCLR);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, tevMode);
}

// .text:0x00000AF4 size:0x438
// Draws a white line grid on the y = 0 plane, centred on the origin.
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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

    width = cols * spacing;
    x0 = -spacing * cols / 2;
    z = -spacing * rows / 2;
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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
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

void fn_1_5E8(void) {
}

// .text:0x0000058C size:0x5C
// Starts the loader task fn_1_1E0 and waits for it in fn_1_568.
void fn_1_58C(void) {
    ((ChTaskHeader*)fn_800B0A5C_insertQueue(fn_1_1E0, 0))->result = 0;
    ((ChTaskHeader*)lbl_803CC1B8)->func = fn_1_568;
    ((ChTaskHeader*)lbl_803CC1B8)->result = 0;
}

void fn_1_568(void) {
    u8* queue = lbl_803CC1B8;
    if (*(s16*)(queue + 0x10) == 1) {
        *(void**)queue = (void*)fn_1_16A0;
    }
}

void fn_1_1E0(void) {
    u8* queue = lbl_803CC1B8;
    switch (*(s16*)(queue + 0x10)) {
    case 0:
        LoadFile(lbl_1_data_AC, lbl_1_bss_4, 0, NULL, 1);
        *(s16*)((u8*)lbl_803CC1B8 + 0x10) += 1;
    case 1:
        if (fn_800A8518(1) != 0) {
            *(s16*)((u8*)lbl_803CC1B8 + 0x10) += 1;
        }
        break;
    case 2:
        if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 0x100) {
            *(void**)(queue + 0x14) = ARAMTransfer(lbl_800F1D78 + queue[0x18] * 16, 0, 0, 0);
            *(s16*)((u8*)lbl_803CC1B8 + 0x10) += 1;
        }
        break;
    case 3:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            s32 v = queue[0x18] % 19;
            switch (v) {
            case 0:
                fn_1_20(*(ChallengeModelHeader**)(queue + 0x14));
                break;
            case 1:
                fn_1_E8(*(ChallengeModelHeader**)(queue + 0x14));
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                ANIMGet(*(void**)(queue + 0x14));
                break;
            }
            fn_800ACFB0(*(void**)(queue + 0x14));
            if (*(u16*)&lbl_803C77B8 & 0x200) {
                *(s16*)((u8*)lbl_803CC1B8 + 0x10) += 1;
            } else {
                s32 n = queue[0x18] + 1;
                queue[0x18] = n;
                *(void**)(queue + 0x14) = ARAMTransfer(lbl_800F1D78 + (u8)n * 16, 0, 0, 0);
            }
        }
        break;
    case 4:
        if (fn_800A8518(3) != 0) {
            *(s16*)((u8*)lbl_803CC1B8 + 0x10) += 1;
        }
        break;
    case 5:
        if (fn_800A88C8() == 0) {
            fn_800A8B78(lbl_1_bss_4);
            *(s16*)((u8*)lbl_803CC1B8 + 0x10) += 1;
        }
        break;
    case 6: {
        u8* object = *(u8**)(queue + 4);
        *(s16*)(object + 0x10) = 1;
        fn_800B0A14_removeQueue(object);
        break;
    }
    }
}

void fn_1_1B0(u32* table, s32 count) {
    s32 i;
    for (i = 0; i < count; i++) {
        if (table[i] != 0) {
            table[i] += (u32)table;
        }
    }
}

void fn_1_E8(ChallengeModelHeader* model) {
    s32 i;
    u32* p = (u32*)model;
    for (i = 0; i < 5; i++) {
        if (p[i] != 0) p[i] += (u32)model;
    }
    convertTextureHeader((void*)model->textures);
    LoadActorLayout((void*)model->actor);
    convertGeometryAndSknHeader((void*)model->geometry, (void*)model->skin);
    haveActLayoutPointToGeoHeader((void*)model->actor, (void*)model->geometry);
    if (model->extra != 0) fn_80025DDC((void*)model->extra);
}

void fn_1_20(ChallengeModelHeader* model) {
    s32 i;
    u32* p = (u32*)model;
    for (i = 0; i < 5; i++) {
        if (p[i] != 0) p[i] += (u32)model;
    }
    convertTextureHeader((void*)model->textures);
    LoadActorLayout((void*)model->actor);
    convertGeometryAndSknHeader((void*)model->geometry, (void*)model->skin);
    haveActLayoutPointToGeoHeader((void*)model->actor, (void*)model->geometry);
    if (model->extra != 0) fn_80025DDC((void*)model->extra);
}

void fn_1_0(void* bank, char* name) {
    ANIMGet(bank);
}
