#include "main/file_80069BDC.h"
#include "main/file_800B0724.h"
#include "Dolphin/vi.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"

#include "string.h"
#include "musyx/musyx.h"

extern AnimEventCallback lbl_803CBD38;
extern AnimEventCallback lbl_803CBD3C;
extern GXRenderModeObj* lbl_803CBD34;
extern GXRenderModeObj lbl_80109250;
extern GXRenderModeObj lbl_8010928C;
extern u8 lbl_80366158[0x30]; // TODO type
extern s16 lbl_80109400[8];
extern s16 lbl_80109410[8];
extern f32 lbl_801093E8[6];
extern s16 lbl_803CB8E0[4];
extern s16 lbl_803CB8E8;
extern f32 lbl_8010B590[4][7];
extern f32 lbl_8010B4B4[5][11];
extern s16 lbl_8010B444[5][11];

extern BOOL challengeStarRelatedInd(s32 team, s32 mission);

typedef struct MissionDef {
    /*0x0*/ s16 _0;
    /*0x2*/ s16 type;
    /*0x4*/ s16 starsNeeded;
    /*0x6*/ s16 _6;
    /*0x8*/ s16 _8;
} MissionDef; // size: 0xA

extern MissionDef lbl_8010A768[20][10];
extern u8 lbl_803CB8F0[8];

typedef struct Unk803297E0 {
    /*0x0000*/ u8 _0000[0xCF69];
    /*0xCF69*/ u8 _CF69;
    /*0xCF6A*/ u8 _CF6A;
    /*0xCF6B*/ u8 _CF6B;
    /*0xCF6C*/ u8 _CF6C[4];
} Unk803297E0;

extern Unk803297E0 lbl_803297E0;

typedef struct Unk80366B18 {
    /*0x00*/ u8 _00[0x2F];
    /*0x2F*/ u8 _2F;
    /*0x30*/ u8 _30[8];
} Unk80366B18; // size: 0x38

extern Unk80366B18 lbl_80366B18[36];
extern u8 lbl_801075A8[0xE0]; // TODO type

extern void fn_80034E20(void* task, void* desc);
extern void* fn_80034CEC(void* task);
extern u8 fn_8000F988(void* task, s32 idx, s32 a, s32 b, s32 c, s32 d);
extern void fn_8000FEE8(u8 idx);
extern void fn_8000F8F4(void* task);
extern void fn_80022B68(void);
extern void changeScene(s32 scene, s32 state);

typedef struct Unk803716B8 {
    /*0x000*/ u8 _000[0x1E9];
    /*0x1E9*/ u8 _1E9;
    /*0x1EA*/ u8 _1EA[0x578 - 0x1EA];
} Unk803716B8;

extern Unk803716B8 lbl_803716B8;
extern u8 lbl_801092F8[0x80]; // TODO type
// ARAM file table entry.
typedef struct AramFile {
    /*0x0*/ u32 id;
    /*0x4*/ u32 sizeFlags; // low 28 bits: size
    /*0x8*/ u32 aramAddr;
    /*0xC*/ u32 _C;
} AramFile;

extern AramFile lbl_801092C8[2]; // [0]: intro movie, [1]: logo textures
extern AramFile lbl_801092E8;    // logo sound data

typedef struct Unk801093B8 {
    /*0x0*/ u32 _0;
    /*0x4*/ u32 _4;
    /*0x8*/ SceneTask* task;
} Unk801093B8;

typedef struct Unk80109378 {
    /*0x00*/ u8 _00[0x40];
    /*0x40*/ Unk801093B8 _40;
} Unk80109378;

extern Unk80109378 lbl_80109378;
extern GXColor lbl_803CB8DC;

// Loaded file whose first two words are file-relative offsets.
typedef struct RelocPair {
    /*0x0*/ void* a;
    /*0x4*/ void* b;
} RelocPair;

// TODO port: file data stores 32-bit offsets that are turned into pointers in place.
#define RELOCATE(base, field) ((field) = (void*)((u8*)(base) + (u32)(field)))

extern s32 ARAMTransfer(AramFile* file, void* dst, s32 a, s32 b);
extern void* fn_800ACF34(s32 heap, u32 size);
extern void fn_80035750(void* a, void* b, s32 c);
extern void fn_800215F8(Unk801093B8* p);
extern void convertTextureHeader(void* textures);
typedef struct PadState {
    /*0x00*/ u16 _00;
    /*0x02*/ u16 trig;
    /*0x04*/ u16 trig2;
    /*0x06*/ u8 _06[0x20 - 0x06];
} PadState; // size: 0x20

extern PadState lbl_803C77B8[4];

typedef struct AnimObj {
    /*0x00*/ u8 _00[0x54];
    /*0x54*/ u32 flags;
    /*0x58*/ u8 _58[4];
    /*0x5C*/ u32 frame; // 16.16
    /*0x60*/ u8 _60[8];
    /*0x68*/ u8 _68;
} AnimObj;

typedef struct AnimSlot {
    /*0x0*/ AnimObj* obj;
    /*0x4*/ u32 _4;
} AnimSlot;

extern AnimSlot lbl_80371C30[0x2A7B0 / 8];

typedef struct Unk8037169C {
    /*0x00*/ u8 _00[0x12];
    /*0x12*/ u8 _12;
    /*0x13*/ u8 _13;
    /*0x14*/ u8 _14[0x1C - 0x14];
} Unk8037169C;

extern Unk8037169C lbl_8037169C;
extern u8 lbl_800EFBA4[16];
extern s32 lbl_803CB8D8;

extern void fn_800ACF14(void* p);
extern s32 fn_800214D0(void);
extern void fn_8002149C(s32 a);
extern void fn_80035CA4(s32 a);
extern void fn_8000900C(void);
extern void fn_80008E00(void (*cb)(s32 alt));
extern void fn_800A7F10(s32 alt);

typedef struct Unk803C6CF8 {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ u8 _715; // 1 once the ARAM transfer has finished
} Unk803C6CF8;

extern Unk803C6CF8 lbl_803C6CF8;
extern u8 lbl_803CBBC0;

extern void fn_800A7D4C(s32 layer, DrawNode* node);
extern void* fn_80009018(void* value);
extern void* _OSAllocFromHeap(s32 heap, u32 size);
extern BOOL fn_800ADAFC(void); // returns a u8 flag (lbz)
extern void fn_800ADC40(void* work, u32 size);
extern BOOL fn_800ADB04(AramFile* file, void* player, s32 a, s32 b);
extern u32 fn_800AD6BC(void* player);
extern void fn_800AD500(void* player, void* buffer);
extern void fn_800AD95C(void* player, s32 a);
extern BOOL fn_800AD780(void* player);
extern void fn_800AD9F4(void* player);
extern void fn_800ADBFC(void);
extern void fn_800ACFB0(void* p);
extern void fn_800AD830(void* player);
extern void fn_800AD070(void);
extern void gOz_GXSetTexture(s32 a, s32 b, s32 c);
extern void SetDisplayStateTexture(TexDesc* tex, s32 a, s32 b);

// .text:0x80069BDC size:0x5B8
void fn_80069BDC(TexSet* set, s32 idx, f32 alpha, s32 idx2, f32 alpha2) {
    GXRenderModeObj* mode = &lbl_80109250;
    f32 c;

    GXSetDispCopySrc(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetDispCopyDst(mode->fbWidth, mode->efbHeight);
    GXSetDispCopyYScale((f32)lbl_80109250.xfbHeight / (f32)mode->efbHeight);
    GXSetScissor(0, 0, 608, 448);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture(&set->tex[idx], 0, 0);
    SetDisplayStateTexture(&set->tex[idx2], 1, 1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U16, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_CLR1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, 1 /* GX_TG_MTX2x4 */, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR1A1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTevStages(2);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    c = 255.0f * alpha;
    GXPosition3u16(0, 0, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 0);
    GXPosition3u16(608, 0, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 0);
    GXPosition3u16(608, 448, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 1);
    GXPosition3u16(0, 448, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 1);
    GXEnd();

    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR1A1);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    c = 255.0f * alpha2;
    GXPosition3u16(0, 359, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 0);
    GXPosition3u16(608, 359, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 0);
    GXPosition3u16(608, 407, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 1);
    GXPosition3u16(0, 407, 0);
    GXColor1u32(0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 1);
    GXEnd();
}

// .text:0x8006A194 size:0x36C
void fn_8006A194(TexSet* set, s32 idx, f32 alpha) {
    GXRenderModeObj* mode = &lbl_80109250;
    f32 c;

    GXSetDispCopySrc(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetDispCopyDst(mode->fbWidth, mode->efbHeight);
    GXSetDispCopyYScale((f32)lbl_80109250.xfbHeight / (f32)mode->efbHeight);
    GXSetScissor(0, 0, 608, 448);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture(&set->tex[idx], 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U16, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, 1 /* GX_TG_MTX2x4 */, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTevStages(1);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    c = 255.0f * alpha;
    GXPosition3u16(189, 150, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 0);
    GXPosition3u16(421, 150, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 0);
    GXPosition3u16(421, 262, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 1);
    GXPosition3u16(189, 262, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 1);
    GXEnd();
}

// .text:0x8006A500 size:0x324
void fn_8006A500(TexSet* set, s32 idx, f32 alpha) {
    GXRenderModeObj* mode = &lbl_80109250;
    u32 halfW;
    u32 halfH;
    f32 c;

    GXSetDispCopySrc(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetDispCopyDst(mode->fbWidth, mode->efbHeight);
    GXSetDispCopyYScale((f32)lbl_80109250.xfbHeight / (f32)mode->efbHeight);
    GXSetScissor(0, 0, 608, 448);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture(&set->tex[idx], 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U16, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, 1 /* GX_TG_MTX2x4 */, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTevStages(1);

    halfW = (u32)set->tex[idx].width >> 1;
    halfH = (u32)set->tex[idx].height >> 1;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    c = 255.0f * alpha;
    GXPosition3u16(304 - halfW, 224 - halfH, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 0);
    GXPosition3u16(304 + halfW, 224 - halfH, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 0);
    GXPosition3u16(304 + halfW, 224 + halfH, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(1, 1);
    GXPosition3u16(304 - halfW, 224 + halfH, 0);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2u8(0, 1);
    GXEnd();
}

// .text:0x8006A824 size:0x400
void fn_8006A824(TexSet* set, s32 idx, f32 alpha) {
    GXRenderModeObj* mode = &lbl_80109250;
    f32 c;

    GXSetDispCopySrc(0, 0, mode->fbWidth, mode->efbHeight);
    GXSetDispCopyDst(mode->fbWidth, mode->efbHeight);
    GXSetDispCopyYScale((f32)lbl_80109250.xfbHeight / (f32)mode->efbHeight);
    GXSetScissor(0, 0, 608, 448);
    GXSetViewport(0.0f, 0.0f, 608.0f, 448.0f, -1.0f, 1.0f);
    SetDisplayStateTexture(&set->tex[idx], 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_U16, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_CLR1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR1, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, 1 /* GX_TG_MTX2x4 */, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTexGens(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR1A1);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C0, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTevStages(2);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    c = 220.0f * alpha;
    GXPosition3u16(117, 154, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 255);
    GXTexCoord2u8(0, 0);
    GXPosition3u16(493, 154, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 255);
    GXTexCoord2u8(1, 0);
    GXPosition3u16(493, 258, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 255);
    GXTexCoord2u8(1, 1);
    GXPosition3u16(117, 257, 0);
    GXColor1u32(0);
    GXColor4u8(c, 0, 0, 255);
    GXTexCoord2u8(0, 1);
    GXEnd();
}

// .text:0x8006AC24 size:0x348
void fn_8006AC24(DrawNode* node) {
    switch (node->kind) {
    case 0: {
        Mtx m;
        Mtx44 p;
        PSMTXIdentity(m);
        C_MTXOrtho(p, -23.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        GXSetProjection(p, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        fn_80069BDC(node->texSet, node->texIdx, node->alpha, node->texIdx2, node->alpha2);
        break;
    }
    case 1: {
        Mtx m;
        Mtx44 p;
        PSMTXIdentity(m);
        C_MTXOrtho(p, -23.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        GXSetProjection(p, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        fn_8006A824(node->texSet, node->texIdx, node->alpha);
        break;
    }
    case 2: {
        Mtx m;
        Mtx44 p;
        PSMTXIdentity(m);
        C_MTXOrtho(p, 0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        GXSetProjection(p, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        fn_8006A500(node->texSet, node->texIdx, node->alpha);
        break;
    }
    case 3: {
        Mtx m;
        Mtx44 p;
        PSMTXIdentity(m);
        C_MTXOrtho(p, 0.0f, 448.0f, 0.0f, 608.0f, -100.0f, 100.0f);
        GXSetProjection(p, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        fn_8006A194(node->texSet, node->texIdx, node->alpha);
        break;
    }
    case 4: {
        Mtx m;
        Mtx44 p;
        PSMTXIdentity(m);
        C_MTXOrtho(p, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 1.0f);
        GXSetProjection(p, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        gOz_GXSetTexture(4, 0, 0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * node->alpha / 30.0f));
        GXPosition3f32(640.0f, 0.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * node->alpha / 30.0f));
        GXPosition3f32(640.0f, 448.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * node->alpha / 30.0f));
        GXPosition3f32(0.0f, 448.0f, -0.5f);
        GXColor4u8(0, 0, 0, (u8)(255.0f * node->alpha / 30.0f));
        GXEnd();
        break;
    }
    }
}

// .text:0x8006AF6C size:0x30
void fn_8006AF6C(void) {
    if (lbl_803CC1B8->_3B == 0) {
        fn_800B0A14_removeQueue(lbl_803CC1B8);
    }
}

// .text:0x8006AF9C size:0x294
void fn_8006AF9C(void) {
    SceneTask* task = lbl_803CC1B8;

    switch (task->state) {
    case 0:
        task->_38 = 0;
        task->_36 = 0;
        task->player = _OSAllocFromHeap(0x20, 0x1C0);
        memset(task->player, 0, 0x1C0);
        task->work = _OSAllocFromHeap(0x20, 0x400000);
        fn_800ADC40(task->work, 0x400000);
        task->state++;
        break;
    case 1:
        if (fn_800ADB04(&lbl_801092C8[0], task->player, 0, 0) != 0) {
            fn_80009018(task->player);
            task->state++;
        }
        break;
    case 2:
        if (fn_800ADAFC() != 0) {
            u32 size = fn_800AD6BC(task->player);
            task->buffer = _OSAllocFromHeap(0x20, size);
            fn_800AD500(task->player, task->buffer);
            fn_800AD95C(task->player, 1);
            task->state++;
        }
        break;
    case 3:
        if (lbl_803C77B8[0].trig2 & 0x1000) {
            task->state = 5;
            break;
        }
    case 4:
        if (fn_800AD780(task->player) != 0) {
            fn_80009018(NULL);
            fn_800AD9F4(task->player);
            fn_800ADBFC();
            fn_800ACFB0(task->buffer);
            fn_800ACFB0(task->work);
            fn_800ACFB0(task->player);
            task->state = 0;
            lbl_803CC1B8->_3B = 0;
            lbl_803CC1B8->func = fn_8006B668;
            return;
        }
        break;
    case 5:
        if (++task->_38 == 30) {
            fn_800AD830(task->player);
            task->state = 4;
        }
        break;
    }
    if (task->state >= 3) {
        fn_800AD070();
    }
    if (task->_38 != 0) {
        task->nodes[lbl_803CBBC0].kind = 4;
        task->nodes[lbl_803CBBC0].alpha = task->_38;
        task->nodes[lbl_803CBBC0].next = NULL;
        task->nodes[lbl_803CBBC0].draw = fn_8006AC24;
        fn_800A7D4C(14, &task->nodes[lbl_803CBBC0]);
    }
}

// .text:0x8006B230 size:0x438
void fn_8006B230(void) {
    SceneTask* self = lbl_803CC1B8;
    SceneTask* p = self->parent;

    switch (p->state) {
    case 1:
        if (p->_36 != 0) {
            p->_36 = 0;
            changeScene(1, 6);
            lbl_80371C30[self->u14.objIdx].obj->flags |= 2;
            lbl_80371C30[self->u14.objIdx + 1].obj->frame = 0;
            lbl_80371C30[self->u14.objIdx + 2].obj->frame = 0;
            lbl_80371C30[self->u14.objIdx + 1].obj->flags |= 2;
            lbl_80371C30[self->u14.objIdx + 2].obj->flags |= 2;
            lbl_80371C30[self->u14.objIdx + 1].obj->_68 = 0;
            lbl_80371C30[self->u14.objIdx + 2].obj->_68 = 0;
        } else if (lbl_8037169C._12 != 0) {
            lbl_80371C30[self->u14.objIdx + 1].obj->_68 = 1;
            lbl_80371C30[self->u14.objIdx + 2].obj->_68 = 1;
            p->volStep = 8;
            p->voice = sndFXStartEx(0x318, 110, 255, 0);
            p->_36 = 300;
            p->state++;
        }
        break;
    case 2:
        if ((lbl_80371C30[self->u14.objIdx + 2].obj->frame >> 16) == 100) {
            p->state++;
        }
        break;
    case 3:
        if (lbl_803C77B8[0].trig & 0x1100) {
            PadState* pad = lbl_803C77B8;
            s32 i;
            for (i = 0; i < 4; pad++, i++) {
                if (pad->trig & 0x1100) {
                    lbl_80366158[0x27] = i;
                    break;
                }
            }
            p->state = 4;
            sndFXStartEx(0x1B8, lbl_800EFBA4[1], 0x3F, 0);
        } else if (sndFXCheck(p->voice) == SND_ID_ERROR) {
            if (lbl_803CB8D8 != 0) {
                p->state = 6;
            } else {
                p->state = 5;
            }
            lbl_803CB8D8 ^= 1;
        }
        if (p->state != 3) {
            lbl_80371C30[self->u14.objIdx + 1].obj->_68 = 0;
            lbl_80371C30[self->u14.objIdx + 2].obj->_68 = 0;
            lbl_80371C30[self->u14.objIdx].obj->frame = 0;
            lbl_80371C30[self->u14.objIdx].obj->_68 = 1;
        }
        break;
    case 4:
    case 5:
    case 6:
        if (sndFXCheck(p->voice) != SND_ID_ERROR) {
            if (p->volStep > 0) {
                if (sndFXCtrl(p->voice, 7, --p->volStep * 110 / 8) != 0) {
                    break;
                }
            }
            if (p->volStep >= 0) {
                p->volStep = -1;
                sndFXKeyOff(p->voice);
            }
        }
        if ((lbl_80371C30[self->u14.objIdx].obj->frame >> 16) == 20) {
            fn_80034CEC(self);
            switch (p->state) {
            case 4:
                fn_800214D0();
                fn_8002149C(0x2F);
                fn_800ACF14(p->u14.res);
                fn_80035CA4(0x16);
                fn_800ACF14(p->res28);
                fn_800ACF14(p->nodes);
                p->_3B = 2;
                break;
            case 5:
                p->_3B = 1;
                break;
            case 6:
                fn_800214D0();
                fn_8002149C(0x2F);
                fn_800214D0();
                fn_8002149C(0x25);
                fn_800ACF14(p->u14.res);
                fn_80035CA4(0x16);
                fn_800ACF14(p->res28);
                fn_800ACF14(p->nodes);
                p->_3B = 3;
                break;
            }
            ((void (*)(void))fn_800B0A14_removeQueue)();
        }
        break;
    }
}

// .text:0x8006B668 size:0x124
void fn_8006B668(void) {
    SceneTask* task = lbl_803CC1B8;

    if (lbl_803716B8._1E9 == 0 && task->state != 6) {
        fn_80022B68();
    }
    switch (task->state) {
    case 0:
        if (task->_10 != 0) {
            fn_80034E20(fn_800B0A5C_insertQueue(fn_8006B230, lbl_803CC1B8->priority), lbl_801092F8);
            changeScene(3, 0);
            task->_38 = 0;
            task->_36 = 1;
            task->state++;
        }
        break;
    case 5:
        if (lbl_803CC1B8->_3B != 0) {
            task->state = 0;
            lbl_803CC1B8->func = fn_8006AF9C;
        }
        break;
    case 4:
    case 6:
        if (lbl_803CC1B8->_3B != 0) {
            task->state = 0;
            lbl_803CC1B8->func = fn_8006AF6C;
        }
        break;
    }
}

// .text:0x8006B78C size:0x3D4
void fn_8006B78C(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 busy = 1;
    s16 state = task->state;

    switch (state) {
    case 0:
        fn_8000900C();
        lbl_80366158[0x20] = 1;
    case 3:
    case 6:
        if (++task->_38 == 30) {
            task->_36 = 60;
            task->state++;
        }
        break;
    case 1:
    case 4:
    case 7:
        if (task->_36 != 0) {
            task->_36--;
        } else {
            task->state++;
        }
        break;
    case 8:
        busy = 0;
    case 2:
    case 5:
        if (task->_38 != 0) {
            task->_38--;
            busy = 1;
        } else {
            s32 ready;
            if (state != 8 || (ready = lbl_803C6CF8._715) == 1) {
                task->state++;
            }
        }
        break;
    }
    if (busy) {
        fn_80022B68();
    }
    if (task->state == 9) {
        task->_36 = 0;
        task->state = 0;
        fn_80008E00(fn_800A7F10);
        lbl_803CC1B8->func = fn_8006AF9C;
        return;
    }
    switch (task->state) {
    case 6:
    case 7:
    case 8:
        task->nodes[lbl_803CBBC0].kind = 3;
        task->nodes[lbl_803CBBC0].texSet = task->u14.res->data;
        task->nodes[lbl_803CBBC0].texIdx = 0;
        task->nodes[lbl_803CBBC0].alpha = task->_38 / 30.0f;
        task->nodes[lbl_803CBBC0].next = NULL;
        task->nodes[lbl_803CBBC0].draw = fn_8006AC24;
        fn_800A7D4C(0, &task->nodes[lbl_803CBBC0]);
        break;
    case 3:
    case 4:
    case 5:
        task->nodes[lbl_803CBBC0].kind = 2;
        task->nodes[lbl_803CBBC0].texSet = task->u14.res->data;
        task->nodes[lbl_803CBBC0].texIdx = 2;
        task->nodes[lbl_803CBBC0].alpha = task->_38 / 30.0f;
        task->nodes[lbl_803CBBC0].next = NULL;
        task->nodes[lbl_803CBBC0].draw = fn_8006AC24;
        fn_800A7D4C(0, &task->nodes[lbl_803CBBC0]);
        break;
    case 0:
    case 1:
    case 2:
        task->nodes[lbl_803CBBC0].kind = 1;
        task->nodes[lbl_803CBBC0].texSet = task->u14.res->data;
        task->nodes[lbl_803CBBC0].texIdx = 1;
        task->nodes[lbl_803CBBC0].alpha = task->_38 / 30.0f;
        task->nodes[lbl_803CBBC0].next = NULL;
        task->nodes[lbl_803CBBC0].draw = fn_8006AC24;
        fn_800A7D4C(0, &task->nodes[lbl_803CBBC0]);
        break;
    }
}

// .text:0x8006BB60 size:0x2A0
void fn_8006BB60(void) {
    SceneTask* task = lbl_803CC1B8;

    fn_80022B68();
    switch (task->state) {
    case 0:
        if (++task->_38 == 30) {
            task->_36 = 90;
            task->state++;
        }
        break;
    case 1:
        if (task->_36-- == 0) {
            fn_8000900C();
            lbl_80366158[0x20] = 1;
            task->_36 = 3480;
            task->state++;
        }
        break;
    case 2:
    case 3:
        if (task->state == 2 && ++task->_39 == 30) {
            task->state = 3;
        } else if (task->state == 3 && --task->_39 == 0) {
            task->state = 2;
        }
        if (--task->_36 == 0 || lbl_803C77B8[0]._00 != 0) {
            task->state = 4;
        }
        break;
    case 4:
        if (--task->_38 == 0) {
            task->state = 0;
            lbl_803CC1B8->func = fn_8006B78C;
        }
        break;
    }
    task->nodes[lbl_803CBBC0].kind = 0;
    task->nodes[lbl_803CBBC0].texSet = task->u14.res->data;
    task->nodes[lbl_803CBBC0].texIdx = 6;
    task->nodes[lbl_803CBBC0].alpha = task->_38 / 30.0f;
    task->nodes[lbl_803CBBC0].texIdx2 = 7;
    task->nodes[lbl_803CBBC0].alpha2 = (task->_39 / 30.0f) * task->_38 / 30.0f;
    task->nodes[lbl_803CBBC0].next = NULL;
    task->nodes[lbl_803CBBC0].draw = fn_8006AC24;
    fn_800A7D4C(0, &task->nodes[lbl_803CBBC0]);
}

// .text:0x8006BE00 size:0x288
// NONMATCHING 85%: the original addresses lbl_801092C8/lbl_801092E8/lbl_80109378 relative to
// lbl_80109250 (this file's .data, not split yet); code is otherwise the same
#if NONMATCHING
void fn_8006BE00(void) {
    SceneTask* task = lbl_803CC1B8;

    switch (task->state) {
    case 0:
        if ((task->_3A = lbl_8037169C._13) != 0) {
            changeScene(1, 6);
        }
        GXSetCopyClear(lbl_803CB8DC, 0xFFFFFF);
        task->_36 = 0;
        task->nodes = fn_800ACF34(0x20, 0x40);
        task->res28 = fn_800ACF34(0x20, lbl_801092E8.sizeFlags & 0x0FFFFFFF);
        ARAMTransfer(&lbl_801092E8, task->res28, 0, 0);
        task->state++;
    case 1:
        if (lbl_803C6CF8._715 == 1) {
            RelocPair* snd = task->res28;
            RELOCATE(snd, snd->a);
            RELOCATE(snd, snd->b);
            fn_80035750(snd->b, snd->a, 0x16);
            task->u14.res = fn_800ACF34(0x20, lbl_801092C8[1].sizeFlags & 0x0FFFFFFF);
            ARAMTransfer(&lbl_801092C8[1], task->u14.res, 0, 0);
            task->state++;
        }
        break;
    case 2:
        if (task->_36 != 0) {
            task->_36--;
            break;
        }
        if ((task->_3A == 0 || lbl_8037169C._12 != 0) && lbl_803C6CF8._715 == 1) {
            if (lbl_80366158[0x29] == 0 || lbl_80366158[0x29] == 1) {
                fn_80008E00(fn_8006C088);
            }
            lbl_80109378._40.task = lbl_803CC1B8;
            fn_800215F8(&lbl_80109378._40);
            RELOCATE(task->u14.res, task->u14.res->data);
            convertTextureHeader(task->u14.res->data);
            task->state = 0;
            task->_38 = 0;
            task->_39 = 0;
            switch (lbl_80366158[0x29]) {
            case 0:
                lbl_803CC1B8->func = fn_8006BB60;
                break;
            case 1:
                lbl_803CC1B8->func = fn_8006B78C;
                break;
            case 2:
                lbl_803CC1B8->func = fn_8006B668;
                break;
            }
        }
        break;
    }
}
#endif

// .text:0x8006C088 size:0x48
void fn_8006C088(s32 alt) {
    lbl_803CBD34 = alt ? &lbl_8010928C : &lbl_80109250;
    VIConfigure(lbl_803CBD34);
    VIFlush();
    VIWaitForRetrace();
    VIWaitForRetrace();
}

// .text:0x8006C0D0 size:0x30
SceneTask* fn_8006C0D0(void) {
    return fn_800B0A5C_insertQueue(fn_8006BE00, lbl_803CC1B8->priority);
}

// .text:0x8006C100 size:0x3C
// NONMATCHING 80%: the original keeps a rolled pointer-walk loop with an int counter; CW unrolls it here (u8 counter adds clrlwi)
#if NONMATCHING
u8 fn_8006C100(s16 value) {
    u32 i;

    for (i = 0; i < 7; i++) {
        if (value >= lbl_80109400[i]) {
            return i;
        }
    }
    return 6;
}
#endif

// .text:0x8006C13C size:0x12C
// NONMATCHING: fn_8006C2B4 and fn_8006C268 inlined; those don't match yet (rolled loops)
#if NONMATCHING
s16 fn_8006C13C(StatInput* in) {
    StatOutput out;

    fn_8006C2B4(&out, in);
    return fn_8006C268(&out);
}
#endif

// .text:0x8006C268 size:0x4C
// NONMATCHING 70%: the original keeps the 6-iteration sum loop rolled; CW fully unrolls it here
#if NONMATCHING
s16 fn_8006C268(StatOutput* stats) {
    s16 total = 0;
    u32 i;

    for (i = 0; i < 6; i++) {
        total += stats->vals[i];
    }
    total += stats->_C + stats->_E;
    if (total > 9999) {
        total = 9999;
    }
    return total;
}
#endif

// .text:0x8006C2B4 size:0xE4
// NONMATCHING 90%: CW unrolls the 6-iteration loop 2x (ctr loop); the original keeps it rolled with cmplwi/blt
#if NONMATCHING
void fn_8006C2B4(StatOutput* out, StatInput* in) {
    u32 i;
    u8 k;
    s16 v;
    s16 r;

    for (i = 0; i < 6; i++) {
        k = in->order[i];
        v = in->vals[k - 1];
        if (v > lbl_80109410[k]) {
            v = lbl_80109410[k];
        }
        r = v * lbl_801093E8[k - 1];
        if (r > 999) {
            r = 999;
        }
        out->vals[k - 1] = r;
    }
    v = lbl_803CB8E0[in->_12];
    if (v > 999) {
        v = 999;
    }
    out->_C = v;
    v = in->_13 * lbl_803CB8E8;
    if (v > 999) {
        v = 999;
    }
    out->_E = v;
}
#endif

// .text:0x8006C398 size:0x58
// NONMATCHING 75%: the original keeps the 6-iteration order[] init loop rolled; CW fully unrolls it here
#if NONMATCHING
void fn_8006C398(StatInput* in) {
    u32 i;

    memset(in, 0, sizeof(StatInput));
    for (i = 0; i < 6; i++) {
        in->order[i] = i + 1;
    }
    in->_12 = 3;
}
#endif

// .text:0x8006C3F0 size:0x8
void fn_8006C3F0(AnimEventCallback cb) {
    lbl_803CBD38 = cb;
}

// .text:0x8006C3F8 size:0x44
void fn_8006C3F8(void* obj, f32 frame, s32 a, s32 b) {
    if (lbl_80366158[0x28] != 1 && lbl_803CBD38 != NULL) {
        lbl_803CBD38(obj, frame, a, b);
    }
}

// .text:0x8006C43C size:0x8
void fn_8006C43C(AnimEventCallback cb) {
    lbl_803CBD3C = cb;
}

// .text:0x8006C444 size:0x44
void fn_8006C444(void* obj, f32 frame, s32 a, s32 b) {
    if (lbl_80366158[0x28] != 1 && lbl_803CBD3C != NULL) {
        lbl_803CBD3C(obj, frame, a, b);
    }
}

// .text:0x8006C488 size:0x4
void fn_8006C488(void) {
}

// .text:0x8006C48C size:0x140
// NONMATCHING 85%: register allocation differs (original keeps &info->_2/&info->hasMissions in r29/r28 and compares type with cmpwi)
#if NONMATCHING
void challengeDrawStarsOnMissionMenu(void) {
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    ChallengeTeamInfo* info = lbl_800E8558;
    s32 team;
    s32 m;
    s32 j;
    s32 count;
    u8 level = gChallengeState._4415;

    for (team = 0; team < 54; team++, t++, info++) {
        s32 status;
        if (info->hasMissions != 1) {
            continue;
        }
        status = t->_31;
        if (status != 1) {
            continue;
        }
        for (m = 0; m < 10; m++) {
            MissionDef* d = &lbl_8010A768[info->_2][m];
            s16 type = d->type;
            s16 need = d->starsNeeded;
            s16 needLevel = d->_6;

            if (type == 0) {
                t->inGameMissionTracker[m].shownOnPauseMenu = 1;
            }
            if (challengeStarRelatedInd(team, m)) {
                t->inGameMissionTracker[m].shownOnPauseMenu = 1;
            }
            if (type == 1) {
                if (info->hasMissions == 0) {
                    count = 0;
                } else {
                    count = 0;
                    for (j = 0; j < 10; j++) {
                        if (challengeStarRelatedInd(team, j)) {
                            count++;
                        }
                    }
                }
                if (count >= need && level >= needLevel) {
                    t->inGameMissionTracker[m].shownOnPauseMenu = 1;
                }
            }
        }
    }
}
#endif

// .text:0x8006C5CC size:0xF8
BOOL fn_8006C5CC(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 54; i++) {
        s32 status = starMissionCompletionTracker[i]._31;
        if (status == 1) {
            s32 captain = starMissionCompletionTracker[i].challengeCaptain;
            if (captain != 5) {
                count++;
            }
        }
    }
    return count >= 28;
}

// .text:0x8006C6C4 size:0xD8
s32 fn_8006C6C4(void) {
    s32 count = 0;
    s32 i;

    for (i = 0; i < 54; i++) {
        s32 status = starMissionCompletionTracker[i]._31;
        if (status == 1) {
            count++;
        }
    }
    return count;
}

// .text:0x8006C79C size:0x28
BOOL fn_8006C79C(s32 idx) {
    return (s8)gChallengeState.trackers[idx]._31 == 1;
}

// .text:0x8006C7C4 size:0x214
// NONMATCHING 90%: the original keeps &found[0] in one register for both loops; rest is register numbering
#if NONMATCHING
void starMissionRelated2(void) {
    s32 found[6];
    ChallengeTrackingStruct* t;
    s32 i;
    s32 j;
    s32 cur;

    found[0] = 0;
    cur = gChallengeState._441C;
    found[1] = 0;
    found[2] = 0;
    found[3] = 0;
    found[4] = 0;
    found[5] = 0;
    for (i = 0; i < 54; i++) {
        t = &starMissionCompletionTracker[i];
        for (j = 0; j < 6; j++) {
            if (i == lbl_803CB8F0[j]) {
                s32 status = t->_31;
                if (status == 1 && cur != j) {
                    found[j] = 1;
                }
            }
        }
    }
    // NOTE: t is left over from the loop above (always the last tracker).
    for (j = 0; j < 6; j++) {
        if (found[j] != 0 && (s8)t->_31 == 0) {
            for (i = 0; i < 54; i++) {
                t = &starMissionCompletionTracker[i];
                if ((s8)t->_31 == 0 && (s8)t->challengeCaptain == j) {
                    t->_31 = 2;
                }
            }
        }
    }
}
#endif

// .text:0x8006C9D8 size:0xC4
// NONMATCHING 90%: the original indexes _444D with i (addi/stbx) instead of a strength-reduced pointer; register numbering differs
#if NONMATCHING
void fn_8006C9D8(void) {
    ChallengeTrackingStruct* t = starMissionCompletionTracker;
    s32 row = gChallengeState._4415;
    s32 col = gChallengeState._441C;
    s32 i;

    for (i = 0; i < 54; i++, t++) {
        s8 status = t->_31;
        if (status != 1) {
            s8 flag = ((ScoutFlagTable*)t->scoutFlagPointer)->flags[row][col];
            if ((s8)t->scoutFlagsAchieved == flag && flag != 0) {
                s32 mode = gChallengeState._441F;
                if (mode == 19) {
                    if (status == 2) {
                        t->_31 = 1;
                        gChallengeState._444D[i] = 1;
                    }
                } else if (status != 2 && (s8)t->challengeCaptain == gChallengeState._441E) {
                    t->_31 = 1;
                    gChallengeState._444D[i] = 1;
                }
            }
        }
    }
}
#endif

// .text:0x8006CA9C size:0x2C
f32 fn_8006CA9C(void) {
    return lbl_8010B590[gChallengeState._4415][gChallengeState._4422];
}

// .text:0x8006CAC8 size:0x11C
f32 starMissionMenu(s32 team) {
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[team];
    s32 count;
    s32 i;

    if (lbl_800E8558[team].hasMissions == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if ((s8)t->inGameMissionTracker[i].starMissionStatus < 0) {
                count++;
            }
        }
    }
    return lbl_8010B4B4[t->variantClassification][count];
}

// .text:0x8006CBE4 size:0xC0
// NONMATCHING 99%: the original copies count into i (mr r30,r31) instead of a second li 0
#if NONMATCHING
s16 challengeRelated(s32 team) {
    s32 count;
    s32 i;
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[team];

    if (lbl_800E8558[team].hasMissions == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if (challengeStarRelatedInd(team, i)) {
                count++;
            }
        }
    }
    return lbl_8010B444[t->variantClassification][count];
}
#endif

// .text:0x8006CCA4 size:0x11C
s16 determineIfMissionDescriptionIsShown(s32 team) {
    ChallengeTrackingStruct* t = &starMissionCompletionTracker[team];
    s32 count;
    s32 i;

    if (lbl_800E8558[team].hasMissions == 0) {
        count = 0;
    } else {
        count = 0;
        for (i = 0; i < 10; i++) {
            if ((s8)t->inGameMissionTracker[i].starMissionStatus < 0) {
                count++;
            }
        }
    }
    return lbl_8010B444[t->variantClassification][count];
}

// .text:0x8006CDC0 size:0xFC
s32 fn_8006CDC0(s32 team) {
    ChallengeTrackingStruct* base = starMissionCompletionTracker;
    ChallengeTrackingStruct* t;
    s32 count;
    s32 i;

    if (lbl_800E8558[team].hasMissions == 0) {
        return 0;
    }
    count = 0;
    t = &base[team];
    for (i = 0; i < 10; i++) {
        if ((s8)t->inGameMissionTracker[i].starMissionStatus < 0) {
            count++;
        }
    }
    return count;
}

// .text:0x8006CEBC size:0xB0
void fn_8006CEBC(void) {
    SceneTask* task = lbl_803CC1B8;
    s32 i;

    if (lbl_803297E0._CF6B != 0) {
        lbl_803297E0._CF6B = 0;
        for (i = 0; i < 4; i++) {
            fn_8000FEE8(lbl_803297E0._CF6C[i]);
        }
        fn_8000F8F4(task);
        fn_800B0A14_removeQueue(fn_80034CEC(task));
    }
    if (lbl_803297E0._CF69 == 0) {
        lbl_803297E0._CF69 = 1;
        lbl_803297E0._CF6A = 1;
    }
}

// .text:0x8006CF6C size:0xB8
void fn_8006CF6C(void) {
    void* task = lbl_803CC1B8;
    s32 i;

    lbl_803297E0._CF6B = 0;
    fn_80034E20(task, lbl_801075A8);
    for (i = 0; i < 4; i++) {
        lbl_803297E0._CF6C[i] = fn_8000F988(task, i + 2, 0, 0, i + 0x1C1, 0);
        lbl_80366B18[lbl_803297E0._CF6C[i]]._2F = 1;
    }
    lbl_803CC1B8->func = fn_8006CEBC;
}
