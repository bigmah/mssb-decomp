#include "main/file_800B9974.h"
#include "main/file_800B993C.h" // lbl_803CC200, lbl_803CC1F4
#include "C3/geoPalette.h"
#include "Dolphin/os.h"
#include "string.h"
#include "stl/math.h"

#pragma dont_inline on

typedef struct FogState {
    /* 0x00 */ GXFogType type;
    /* 0x04 */ f32 startz;
    /* 0x08 */ f32 endz;
    /* 0x0C */ f32 nearz;
    /* 0x10 */ f32 farz;
    /* 0x14 */ GXColor color;
} FogState;

extern FogState lbl_80111700; // current fog settings
extern MtxPtr lbl_803CC204;   // skin matrix array for the current DOVARenderSkin call
extern MtxPtr lbl_803CC208;   // skin inverse-transpose matrix array

extern char lbl_800E7E84[]; // "Error: DODefaultUserTevMode: Cannot override tev mode AND use default user tev mode function.\n"
extern char lbl_800E7EE4[]; // "Warning: DODefaultUserTevMode: Unknown user tev mode %d\n"
extern char lbl_800E7F58[]; // "DOVARender: Invalid component count for normals %d\n"
extern char lbl_800E7F8C[]; // "Display object id %d is greater than number of objects %d"

extern void* lbl_803CBB58;      // must be non-NULL for the environment-map passes
extern f32 lbl_803CC1F8;         // environment map scroll (s)
extern f32 lbl_803CC1FC;         // environment map scroll (t)
extern const Vec lbl_800E7E78;
extern GXColor lbl_803CCFF8;     // GXColor {0, 0, 0, 0x80} (bump-map TEVREG0)
extern u8 fn_800BEBA0(void);
extern MtxPtr fn_800BEB80(u8 index);
extern void* fn_800BF068(void);
extern void fn_800BF008(void);   // {0, 0, 1}
extern char lbl_800E7F20[];      // "Warning: DisplayObject.c: User TevMode %d not handled.\n"
extern DOShadowTevCallback lbl_803CC20C; // replaces the default shadow TEV stage
extern u8 lbl_803CC210[8];        // per texture map: DisplayStateList.pad16 of the last texture state
extern GXTexObj lbl_803CB5FC[8];  // texture objects, one per texture map
extern GXTlutObj lbl_803CB49C[8]; // TLUT objects, one per texture map
extern u8 lbl_803CBB60;          // quantize info of the built-in normal table
extern f32 lbl_80111750[][3];    // built-in normal table

extern void* _OSAllocFromHeap(s32 align, s32 size);
extern void fn_800ACFB0(void* ptr); // heap free
extern void SKNLoadFile(void* sknHeader, void* skinPositions);

// Geometry palette files store pointers as offsets from a base; turn one into a pointer (32-bit file format).
#define GEO_RELOC(a, b) ((void*)((u32)(a) + (u32)(b)))

// .text:0x800B9974 size:0x50
void SetFogNone(void) {
    GXColor color;

    color.b = 0;
    color.g = 0;
    color.r = 0;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, color);
}

// NONMATCHING 75%: original keeps the f64 args in f5-f7 and rounds them twice (frsp for GXSetFog, stfs for the
// stores); ours rounds once and stores the rounded copies
#if NONMATCHING
// .text:0x800B99C4 size:0x6C
void SetFog(GXFogType type, GXColor* color, f64 startz, f64 endz, f64 nearz, f64 farz) {
    GXColor c = *color;

    lbl_80111700.type = type;
    lbl_80111700.startz = startz;
    lbl_80111700.endz = endz;
    lbl_80111700.nearz = nearz;
    lbl_80111700.farz = farz;
    lbl_80111700.color = c;
    GXSetFog(type, startz, endz, nearz, farz, c);
}
#endif

// .text:0x800B9A30 size:0x6C
void SetFogNoneAgain(void) {
    lbl_80111700.color.b = 0;
    lbl_80111700.color.g = 0;
    lbl_80111700.color.r = 0;
    lbl_80111700.type = GX_FOG_NONE;
    lbl_80111700.startz = 0.0f;
    lbl_80111700.endz = 0.0f;
    lbl_80111700.nearz = 0.0f;
    lbl_80111700.farz = 0.0f;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, lbl_80111700.color);
}

extern f32 lbl_803CC218;

extern u32 lbl_803CC21C;

extern Light* lbl_803CC1F0; // light used for the specular highlight (fn_800B9EA8)

// fn_800B9AA8, size:0x8
void fn_800B9AA8(Light* light) {
    lbl_803CC1F0 = light;
}

// fn_800B9A9C, size:0xC
void fn_800B9A9C(u32 flag, f32 value) {
    lbl_803CC21C = flag;
    lbl_803CC218 = value;
}

// NONMATCHING 93%: original keeps -0.5f in f31 (fneg of the 0.5f constant) and allocates one more saved register
#if NONMATCHING
// .text:0x800B9AB0 size:0x3F8
s32 fn_800B9AB0(u32 type, struct DODisplayObj* dispObj, DisplayStateList* state, s32* stage, s32* coord, s32* map,
                s32* chan, MtxPtr camera) {
    Mtx mv;
    Mtx tmp;
    Mtx nrm;
    Mtx trans;
    Mtx texMtx;
    Mtx texMtx2;
    GXColor konst;
    GXTevColorArg konstArg;
    GXTevColorArg rasColor;
    GXTexGenSrc src;
    f32 negHalf;

    src = GX_TG_NRM;
    if (lbl_803CBB58 == NULL) {
        return -1;
    }
    if (dispObj == NULL || dispObj->lightingData == NULL || state == NULL) {
        return -1;
    }
    PSMTXIdentity(nrm);
    PSMTXIdentity(texMtx);
    PSMTXConcat(camera, dispObj->worldMatrix, mv);
    PSMTXInverse(mv, tmp);
    PSMTXTranspose(tmp, nrm);
    negHalf = -0.5f;
    PSMTXScale(tmp, negHalf, 0.5f, 0.0f);
    PSMTXTrans(trans, 0.5f, 0.5f, 1.0f);
    PSMTXConcat(trans, tmp, texMtx2);
    PSMTXScale(tmp, negHalf, 0.5f, 0.0f);
    PSMTXTrans(trans, 0.5f + lbl_803CC1F8, 0.5f + lbl_803CC1FC, 1.0f);
    PSMTXConcat(trans, tmp, texMtx);
    if (type == 5) {
        *chan = GX_COLOR0A0;
        rasColor = GX_CC_RASC;
        type = GX_CA_RASA;
    } else {
        *chan = GX_COLOR_NULL;
        rasColor = GX_CC_CPREV;
        type = GX_CA_APREV;
    }
    if (state->pad8 != 0) {
        konst.r = konst.g = konst.b = konst.a = state->pad8;
        konstArg = GX_CC_KONST;
        GXSetTevKColor(GX_KCOLOR0, konst);
        GXSetTevKColorSel(*stage, GX_TEV_KCSEL_K0);
    } else {
        konstArg = GX_CC_APREV;
    }
    if (dispObj->lightingData->compCount == 2) {
        src = GX_TG_BINRM;
    }
    GXLoadTexMtxImm(nrm, GX_TEXMTX0 + *map * 3, GX_MTX3x4);
    GXLoadTexMtxImm(texMtx, GX_PTTEXMTX0 + *map * 3, GX_MTX3x4);
    GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
    GXSetTevOrder(*stage, *coord, *map, *chan);
    if (lbl_803CC210[*map] == 1) {
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, konstArg, rasColor);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    } else if (lbl_803CC210[*map] == 0) {
        GXSetTevColorIn(*stage, rasColor, GX_CC_TEXC, konstArg, GX_CC_ZERO);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    } else {
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, konstArg, rasColor);
        GXSetTevColorOp(*stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }
    GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, type);
    GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    if (lbl_803CC1F4 != NULL) {
        (*coord)++;
        GXLoadTexMtxImm(nrm, GX_TEXMTX0 + (*map + 1) * 3, GX_MTX3x4);
        GXLoadTexMtxImm(texMtx2, GX_PTTEXMTX0 + (*map + 1) * 3, GX_MTX3x4);
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + (*map + 1) * 3, GX_TRUE,
                          GX_PTTEXMTX0 + (*map + 1) * 3);
        (*map)++;
        lbl_803CC1F4(*stage, 0, 1, *coord, *map);
    }
    (*stage)++;
    (*coord)++;
    (*map)++;
    return 0;
}
#endif

// NONMATCHING 99%: type/camera registers are reused for konstArg/rasAlpha in a different order
#if NONMATCHING
// .text:0x800B9EA8 size:0x5A4
s32 fn_800B9EA8(u32 type, struct DODisplayObj* dispObj, DisplayStateList* state, s32* stage, s32* coord, s32* map,
                s32* chan, MtxPtr camera) {
    Mtx mv;
    Mtx tmp;
    Mtx trans;
    Mtx texMtx;
    Mtx texMtx2;
    Vec lightDir;
    Vec axis;
    Vec up;
    GXColor konst;
    GXTevColorArg konstArg;
    GXTevColorArg rasColor;
    GXTevAlphaArg rasAlpha;
    GXTexGenSrc src;
    f32 dot;
    f32 size;
    f32 scale;
    s32 nextMap;

    up = lbl_800E7E78;
    src = GX_TG_NRM;
    if (lbl_803CBB58 == NULL) {
        return -1;
    }
    if (dispObj == NULL || dispObj->lightingData == NULL || lbl_803CC1F0 == NULL || state == NULL) {
        return -1;
    }
    PSMTXIdentity(texMtx);
    PSMTXIdentity(texMtx2);
    PSMTXConcat(camera, dispObj->worldMatrix, mv);
    PSMTXInverse(mv, tmp);
    PSMTXTranspose(tmp, mv);
    PSMTXMultVecSR(camera, &lbl_803CC1F0->direction, &lightDir);
    dot = PSVECDotProduct(&lightDir, &up);
    if (dot == -1.0f) {
        PSMTXScale(texMtx, 0.0f, 0.0f, 0.0f);
        PSMTXScale(texMtx2, 0.0f, 0.0f, 0.0f);
    } else {
        lightDir.x = -lightDir.x;
        lightDir.y = -lightDir.y;
        lightDir.z = -lightDir.z;
        if (PSVECMag(&lightDir) == 0.0f) {
            return -1;
        }
        PSVECNormalize(&lightDir, &lightDir);
        if (dot == 1.0f) {
            PSMTXIdentity(tmp);
        } else {
            PSVECCrossProduct(&lightDir, &up, &axis);
            if (PSVECMag(&axis) == 0.0f) {
                PSMTXIdentity(tmp);
            } else {
                PSMTXRotAxisRad(tmp, &axis, acos(PSVECDotProduct(&up, &lightDir)));
            }
        }
        PSMTXConcat(tmp, mv, texMtx);
        if (lbl_803CC21C != 0) {
            size = lbl_803CC218;
        } else {
            size = (s32)(state->pad8 & 0x7F) / 100.0f;
        }
        scale = 0.5f * (0.5f - size) + 0.75f;
        PSMTXScale(tmp, scale, -scale, 0.0f);
        PSMTXTrans(trans, 0.5f, 0.5f, 1.0f);
        PSMTXConcat(trans, tmp, texMtx2);
    }
    if (type == 5) {
        *chan = GX_COLOR0A0;
        rasColor = GX_CC_RASC;
        rasAlpha = GX_CA_RASA;
    } else {
        *chan = GX_COLOR_NULL;
        rasColor = GX_CC_CPREV;
        rasAlpha = GX_CA_APREV;
    }
    if (dispObj->unk15 != 0) {
        konst.r = konst.g = konst.b = konst.a = dispObj->unk15;
        konstArg = GX_CC_KONST;
        GXSetTevKColor(GX_KCOLOR0, konst);
        GXSetTevKColorSel(*stage, GX_TEV_KCSEL_K0);
    } else {
        konstArg = GX_CC_APREV;
    }
    if (dispObj->lightingData->compCount == 2) {
        src = GX_TG_BINRM;
    }
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0 + *map * 3, GX_MTX3x4);
    GXLoadTexMtxImm(texMtx2, GX_PTTEXMTX0 + *map * 3, GX_MTX3x4);
    if (state->pad16 == 0) {
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
        GXSetTevOrder(*stage, *coord, *map, *chan);
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_TEXC, konstArg, rasColor);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, rasAlpha);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        (*stage)++;
        (*coord)++;
        (*map)++;
    } else {
        // Stage 1: the highlight mask texture (next map) into TEVREG0.
        nextMap = *map + 1;
        GXSetTexCoordGen2(*coord, GX_TG_MTX2X4, GX_TG_TEX0 + nextMap, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(*stage, *coord, nextMap, GX_COLOR0A0);
        GXSetTevColorIn(*stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
        (*stage)++;
        (*coord)++;
        // Stage 2: the highlight, masked by TEVREG0.
        GXSetTexCoordGen2(*coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + *map * 3, GX_TRUE, GX_PTTEXMTX0 + *map * 3);
        GXSetTevOrder(*stage, *coord, *map, GX_COLOR_NULL);
        GXSetTevColorIn(*stage, rasColor, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevColorOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(*stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, rasAlpha);
        GXSetTevAlphaOp(*stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        (*stage)++;
        (*coord)++;
        *map += 2;
    }
    return 0;
}
#endif

#pragma dont_inline off
// .text:0x800BA44C size:0x3FC
void fn_800BA44C(s32 type, struct DODisplayObj* dispObj, MtxPtr camera, u8* numTexGens, u8* numTevStages) {
    Mtx m;
    GXTevStageID stage;
    GXTexCoordID coord;
    GXTexMapID map;
    GXTevColorArg rasColor;
    GXTevAlphaArg rasAlpha;
    GXChannelID chan;
    f32 x;
    f32 y;
    f32 len;
    f32 scroll;

    if (dispObj->unk17 != 0) {
        OSReport(lbl_800E7E84);
        return;
    }
    map = coord = stage = *numTevStages;
    if (stage == 0) {
        rasColor = GX_CC_RASC;
        rasAlpha = GX_CA_RASA;
        chan = GX_COLOR0A0;
    } else {
        rasColor = GX_CC_CPREV;
        rasAlpha = GX_CA_APREV;
        chan = GX_COLOR_NULL;
    }
    switch (type) {
    case 9: // texture + raster
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, rasColor);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, rasAlpha);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        break;
    case 10: // raster - texture
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, rasColor);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, rasAlpha);
        GXSetTevColorOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        break;
    case 11: // texture modulated by raster, with the texture scrolled by the angle of (x, y)
        x = camera[2][0];
        y = camera[2][1];
        if (x == 0.0f && y == 0.0f) {
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + *numTevStages, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        } else {
            len = dolsqrtf2(x * x + y * y);
            scroll = 0.159154f * (f32)asin(y / len);
            if (x < 0.0f) {
                scroll = 0.5f - scroll;
            }
            PSMTXIdentity(m);
            m[0][0] = 2.0f;
            m[0][3] = -scroll;
            GXLoadTexMtxImm(m, GX_TEXMTX0 + *numTevStages * 3, GX_MTX3x4);
            GXSetTexCoordGen2(coord, GX_TG_MTX3X4, GX_TG_TEX0 + *numTevStages, GX_TEXMTX0 + *numTevStages * 3, GX_FALSE,
                              GX_PTIDENTITY);
        }
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_APREV, rasColor);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        break;
    default:
        OSReport(lbl_800E7EE4, type);
        return;
    }
    (*numTexGens)++;
    (*numTevStages)++;
}
#pragma dont_inline on

// NONMATCHING 98%: stack layout of the stage/coord/map locals and saved-register assignment differ
// nmverify: GXSetTexCoordGen2 original has the bump coord call in both arms of an if with identical arms
// nmverify:  inlined on one side (calls match once expanded)
#if NONMATCHING
// .text:0x800BA848 size:0x12E4
void Custom_SetState(struct DODisplayObj* dispObj, DisplayStateList* state, MtxPtr camera) {
    Mtx mv;
    Mtx scaleMtx;
    Mtx transMtx;
    Mtx texMtx;
    Mtx shadowMtx;
    GXColor konst;
    GXColor color;
    GXColor fogColor;
    s32 stage;
    s32 coord;
    s32 map;
    s32 chan;
    u8 numTexGens;
    u8 numTevStages;
    u8 texIdx;
    u8 envMode;
    u8 shift;
    u8 numChans;
    u32 setting;
    u32 mode;
    f32 scale;
    GXTevColorArg konstArg;
    GXTevColorArg rasColor;
    GXTevAlphaArg rasAlpha;
    GXTexGenSrc src;
    s32 i;

    stage = 0;
    coord = 0;
    numChans = 0;
    shift = 0;
    envMode = 0;
    texIdx = 0;
    map = 0;
    setting = state->setting;
    numTevStages = 0;
    numTexGens = 0;
    GXSetNumIndStages(0);
    for (i = 0; i < 16; i++) {
        GXSetTevDirect(i);
    }

    // setting holds one 4-bit TEV mode per texture channel.
    do {
        mode = (setting >> shift) & 0xF;
        if (mode == 0) {
            break;
        }
        switch (mode) {
        case 10: // texture alpha * raster, colour from raster
            chan = GX_COLOR0A0;
            numChans++;
            GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIdx, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            texIdx++;
            numTexGens++;
            numTevStages++;
            break;
        case 12: // texture * previous
            chan = GX_COLOR_NULL;
            GXSetTevOrder(stage, coord, map, GX_COLOR_NULL);
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIdx, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            if (lbl_803CC210[map] == 2) {
                numTevStages++;
                GXSetTevOrder(stage + 1, coord, map, chan);
                GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
                GXSetTevColorOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            texIdx++;
            numTexGens++;
            numTevStages++;
            break;
        case 1: // GX_MODULATE
        case 2: // GX_DECAL
        case 3: // GX_BLEND
        case 4: // GX_REPLACE
            if (numTevStages != 0 || mode == 4) {
                chan = GX_COLOR_NULL;
            } else {
                chan = GX_COLOR0A0;
            }
            GXSetTevOrder(stage, coord, map, chan);
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIdx, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOp(stage, mode - 1);
            if (lbl_803CC210[map] == 2) {
                numTevStages++;
                GXSetTevOrder(stage + 1, coord, map, GX_COLOR_NULL);
                GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_APREV, GX_CC_ZERO);
                GXSetTevColorOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            }
            texIdx++;
            numTexGens++;
            numTevStages++;
            break;
        case 5: // raster colour only, ends the list
            if (dispObj->shaderFunc == NULL) {
                GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                GXSetTevOp(stage, GX_PASSCLR);
                numTevStages++;
            }
            break;
        case 6: // two textures blended by the second one's alpha, result in TEVREG0
            if (numTevStages != 0 || mode == 4) {
                chan = GX_COLOR_NULL;
            } else {
                chan = GX_COLOR0A0;
            }
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIdx, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            numTexGens++;
            GXSetTexCoordGen2(coord + 1, GX_TG_MTX2X4, GX_TG_TEX0 + texIdx + 1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(stage, coord + 1, map + 1, GX_COLOR0A0);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            numTevStages++;
            stage++;
            GXSetTevOrder(stage, coord, map, chan);
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
            envMode = 1;
            texIdx++;
            numTexGens++;
            numTevStages++;
            break;
        case 7: // combine TEVREG0 with this texture
            if (envMode == 0) {
                GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + texIdx, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                numTexGens++;
                GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
                numTevStages++;
                GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
                GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
                GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
                GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG0);
                stage++;
            }
            GXSetTevOrder(stage, coord, map, GX_COLOR_NULL);
            texIdx++;
            numTevStages++;
            if (envMode == 1) {
                switch (lbl_803CC210[map]) {
                case 1:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_C0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                case 2:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_C0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                default:
                    GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_C0, GX_CC_A0, GX_CC_ZERO);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                }
            } else {
                switch (lbl_803CC210[map]) {
                case 1:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_A0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                case 2:
                    GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_C0, GX_CC_A0, GX_CC_CPREV);
                    GXSetTevColorOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                default:
                    GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_C0, GX_CC_TEXA, GX_CC_ZERO);
                    GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
                    GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                    break;
                }
            }
            envMode = 2;
            break;
        case 8: { // bump mapping; state->listSize / 1000 is the bump scale
            scale = state->listSize / 1000.0f;
            color = lbl_803CCFF8;
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_CLEAR);
            PSMTXConcat(camera, dispObj->worldMatrix, mv);
            GXLoadPosMtxImm(mv, GX_PNMTX0);
            PSMTXScale(scaleMtx, scale, scale, scale);
            PSMTXConcat(mv, scaleMtx, scaleMtx);
            GXLoadNrmMtxImm(scaleMtx, GX_PNMTX0);
            numChans++;
            GXSetChanCtrl(GX_COLOR0, GX_ENABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
            GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
            numTexGens += 2;
            // (the original uses the stage count, not texIdx, for the texture source here)
            GXSetTexCoordGen2(coord, GX_TG_MTX2X4, GX_TG_TEX0 + numTevStages, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTexCoordGen2(coord + 1, GX_TG_BUMP0, GX_TG_TEXCOORD0 + coord, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
            GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
            GXSetTevOrder(stage + 1, coord + 1, map, GX_COLOR_NULL);
            GXSetTevColor(GX_TEVREG0, color);
            if (numTevStages == 0) {
                GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_RASC);
            } else {
                GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_RASC);
            }
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            GXSetTevColorIn(stage + 1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
            GXSetTevColorOp(stage + 1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage + 1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(stage + 1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
            texIdx += 2;
            numTevStages += 2;
            break;
        }
        default: // 9, 11 and anything unknown: per-object user TEV mode
            if (dispObj->tevCallback != NULL) {
                dispObj->tevCallback(mode, dispObj, camera, &numTexGens, &numTevStages);
            } else {
                OSReport(lbl_800E7F20, mode);
            }
            break;
        }
        if (mode == 5) {
            break;
        }
        coord = texIdx;
        shift += 4;
        stage = numTevStages;
        map = texIdx;
    } while (map < dispObj->numTextureChannels);

    if (dispObj->lightingData != NULL && envMode != 0) {
        GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        numTevStages++;
        stage++;
    }

    if (state->pad16 & 0x80) {
        if (fn_800B9AB0(mode, dispObj, state, &stage, &coord, &map, &chan, camera) == 0) {
            numTexGens++;
            numTevStages++;
            if (lbl_803CC1F4 != NULL) {
                numTexGens++;
            }
        }
    } else if (state->pad8 & 0x80) {
        if (fn_800B9EA8(mode, dispObj, state, &stage, &coord, &map, &chan, camera) == 0) {
            if (state->pad16 == 0) {
                numTexGens++;
                numTevStages++;
            } else {
                numTexGens += 2;
                numTevStages += 2;
            }
        }
    }

    // Sphere-map environment texture.
    if (dispObj->shaderFunc != NULL && dispObj->lightingData != NULL) {
        rasColor = GX_CC_CPREV;
        rasAlpha = GX_CA_APREV;
        src = GX_TG_NRM;
        if (dispObj->lightingData->compCount == 2) {
            src = GX_TG_BINRM;
        }
        chan = GX_COLOR_NULL;
        if (mode == 5) {
            chan = GX_COLOR0A0;
            rasColor = GX_CC_RASC;
            rasAlpha = GX_CA_RASA;
        }
        if (dispObj->unk15 != 0) {
            konst.r = konst.g = konst.b = konst.a = dispObj->unk15;
            konstArg = GX_CC_KONST;
            GXSetTevKColor(GX_KCOLOR0, konst);
            GXSetTevKColorSel(stage, GX_TEV_KCSEL_K0);
        } else {
            konstArg = GX_CC_APREV;
            rasAlpha = GX_CA_KONST;
        }
        PSMTXScale(scaleMtx, 0.5f, -0.5f, 0.0f);
        PSMTXTrans(transMtx, 0.5f, 0.5f, 1.0f);
        PSMTXConcat(camera, dispObj->worldMatrix, texMtx);
        PSMTXInverse(texMtx, texMtx);
        PSMTXTranspose(texMtx, texMtx);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0 + numTevStages * 3, GX_MTX3x4);
        PSMTXConcat(transMtx, scaleMtx, texMtx);
        GXLoadTexMtxImm(texMtx, GX_PTTEXMTX0 + numTevStages * 3, GX_MTX3x4);
        GXSetTexCoordGen2(coord, GX_TG_MTX3X4, src, GX_TEXMTX0 + numTevStages * 3, GX_TRUE,
                          GX_PTTEXMTX0 + numTevStages * 3);
        GXLoadTexObj(dispObj->shaderFunc, map);
        GXSetTevOrder(stage, coord, map, chan);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_TEXC, konstArg, rasColor);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, rasAlpha);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        numTexGens++;
        numTevStages++;
        stage++;
        coord++;
        map++;
    }

    // Projected shadow texture.
    if (dispObj->shaderData != NULL && fn_800BEBA0() != 0 &&
        (((u8*)fn_800BF068())[0x4C] & state->pad16)) { // TODO type
        PSMTXConcat(fn_800BEB80(fn_800BEBA0() - 1), dispObj->worldMatrix, shadowMtx);
        if (lbl_803CC20C != NULL) {
            lbl_803CC20C(shadowMtx, &stage, &coord, &map, &numTevStages, &numTexGens);
        } else {
            GXSetTevOrder(stage, coord, map, GX_COLOR0A0);
            GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_ZERO, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_APREV, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTexCoordGen2(coord, GX_TG_MTX3X4, GX_TG_POS, GX_TEXMTX0 + numTevStages * 3, GX_FALSE, GX_PTIDENTITY);
            fn_800BF008();
            GXLoadTexObj(dispObj->shaderData, map);
            GXLoadTexMtxImm(shadowMtx, GX_TEXMTX0 + numTevStages * 3, GX_MTX3x4);
            numTexGens++;
            numTevStages++;
            stage++;
            coord++;
            map++;
        }
    }

    if (state->pad16 & 0x10) {
        fogColor.b = 0;
        fogColor.g = 0;
        fogColor.r = 0;
        GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogColor);
    } else {
        GXSetFog(lbl_80111700.type, lbl_80111700.startz, lbl_80111700.endz, lbl_80111700.nearz, lbl_80111700.farz,
                 lbl_80111700.color);
    }
    if (lbl_803CC200 != NULL) {
        lbl_803CC200(dispObj, &stage, &coord, &map, &numTevStages, &numTexGens, camera);
    }
    GXSetNumTexGens(numTexGens);
    if (numTevStages != 0) {
        GXSetNumTevStages(numTevStages);
    }
    if (numChans != 0) {
        GXSetNumChans(numChans);
    }
}
#endif

// NONMATCHING 96%: saved registers for state/camera swapped (r29/r28 in the original), texture-state temps
// land in different volatile registers
#if NONMATCHING
// .text:0x800BBB2C size:0x430
void SetState(DisplayStateList* state, struct DODisplayObj* dispObj, MtxPtr camera) {
    Mtx m;
    GXVtxDescList vcd[27];
    GXVtxDescList* desc;
    u32 texMap;
    DOTexBank* bank;
    DOTexInfo* tex;
    GXTexWrapMode wrapS;
    GXTexWrapMode wrapT;
    GXBool mipmap;
    f32 minLOD;
    f32 maxLOD;
    f32 lodBias;
    GXTexFilter minFilter;
    GXTexFilter magFilter;
    u32 setting;
    s32 n;
    u32 shift;
    u32 attr;
    u32 type;
    u32 slot;

    switch (state->id) {
    case 1: // texture
        texMap = (state->setting >> 13) & 7;
        bank = dispObj->textureData[texMap].texturePalette;
        tex = &bank->tex[bank->tex[state->setting & 0x1FFF].texIndex];
        lbl_803CC210[texMap] = state->pad16;
        wrapS = (state->setting >> 16) & 0xF;
        switch (wrapS) {
        case 0:
            wrapS = GX_CLAMP;
            break;
        case 1:
            wrapS = GX_REPEAT;
            break;
        case 2:
            wrapS = GX_MIRROR;
            break;
        }
        wrapT = (state->setting >> 20) & 0xF;
        switch (wrapT) {
        case 0:
            wrapT = GX_CLAMP;
            break;
        case 1:
            wrapT = GX_REPEAT;
            break;
        case 2:
            wrapT = GX_MIRROR;
            break;
        }
        mipmap = tex->minLOD != tex->maxLOD;
        minLOD = tex->minLOD;
        maxLOD = tex->maxLOD;
        minFilter = tex->minFilter;
        magFilter = tex->magFilter;
        lodBias = tex->lodBias;
        if (tex->tlut != NULL) {
            GXInitTexObjCI(&lbl_803CB5FC[texMap], tex->image, tex->width, tex->height, tex->format, wrapS, wrapT, mipmap,
                           texMap);
            GXInitTlutObj(&lbl_803CB49C[texMap], tex->tlut, tex->tlutFormat, tex->tlutEntries);
            GXLoadTlut(&lbl_803CB49C[texMap], texMap);
        } else {
            GXInitTexObj(&lbl_803CB5FC[texMap], tex->image, tex->width, tex->height, tex->format, wrapS, wrapT, mipmap);
        }
        GXInitTexObjLOD(&lbl_803CB5FC[texMap], minFilter, magFilter, minLOD, maxLOD, lodBias, GX_FALSE, GX_FALSE,
                        GX_ANISO_1);
        GXLoadTexObj(&lbl_803CB5FC[texMap], texMap);
        break;
    case 2: // vertex descriptor: 2 bits per attribute
        setting = state->setting;
        GXClearVtxDesc();
        n = 0;
        if (setting & 3) {
            vcd[n].mAttr = GX_VA_PNMTXIDX;
            vcd[n].mType = setting & 3;
            n++;
        }
        desc = &vcd[n];
        for (shift = 2, attr = GX_VA_POS; attr <= GX_VA_TEX7; attr++, shift += 2) {
            type = (setting >> shift) & 3;
            if (type != 0) {
                desc->mAttr = attr;
                desc->mType = type;
                n++;
                desc++;
            }
        }
        type = (setting >> 26) & 3;
        if (type != 0) {
            vcd[n].mAttr = GX_VA_NBT;
            vcd[n].mType = type;
            n++;
        }
        vcd[n].mAttr = GX_VA_NULL;
        GXSetVtxDescv(vcd);
        break;
    case 3:
        Custom_SetState(dispObj, state, camera);
        break;
    case 4: // skinning matrix load: high half = matrix index, low half = PNMTX slot
        slot = (state->setting & 0xFFFF) * 3;
        PSMTXConcat(camera, lbl_803CC204 + (state->setting >> 16) * 3, m);
        GXLoadPosMtxImm(m, slot);
        if (dispObj->lightingData != NULL) {
            PSMTXConcat(camera, lbl_803CC208 + (state->setting >> 16) * 3, m);
            GXLoadNrmMtxImm(m, slot);
        }
        break;
    }
}
#endif

// .text:0x800BBF5C size:0x168
void GetColorFromQuant(u8* color, u8 quantizeInfo, u8* r, u8* g, u8* b, u8* a) {
    switch ((quantizeInfo >> 4) & 0xF) {
    case GX_RGB565:
        *r = (*(u16*)color >> 8) & 0xF8;
        *g = (*(u16*)color >> 3) & 0xFC;
        *b = (*(u16*)color & 0x1F) << 3;
        *a = 0xFF;
        break;
    case GX_RGBA4:
        *r = (*(u16*)color >> 12) & 0xF;
        *g = (*(u16*)color >> 8) & 0xF;
        *b = (*(u16*)color >> 4) & 0xF;
        *a = *(u16*)color & 0xF;
        *r = *r | (*r << 4);
        *g = *g | (*g << 4);
        *b = *b | (*b << 4);
        *a = *a | (*a << 4);
        break;
    case GX_RGBA8:
        *r = *(u32*)color >> 24;
        *g = (*(u32*)color >> 16) & 0xFF;
        *b = (*(u32*)color >> 8) & 0xFF;
        *a = *(u32*)color & 0xFF;
        break;
    case GX_RGB8:
    case GX_RGBX8:
        *r = *(u32*)color >> 24;
        *g = (*(u32*)color >> 16) & 0xFF;
        *b = (*(u32*)color >> 8) & 0xFF;
        *a = 0xFF;
        break;
    case GX_RGBA6:
        // Reads only 16 bits, so the red channel always comes out 0 (original bug kept).
        *r = (*(u16*)color & 0xFC0000) >> 16;
        *g = (*(u16*)color >> 10) & 0xFC;
        *b = (*(u16*)color >> 4) & 0xFC;
        *a = (*(u16*)color & 0x3F) << 2;
        break;
    }
}

// NONMATCHING 99%: saved-register assignment differs (dispObj r30/camera r31 in the original) and the GXColor
// by-value temporaries sit in a different stack order
#if NONMATCHING
// .text:0x800BC0C4 size:0x724
void DOVARender(struct DODisplayObj* dispObj, MtxPtr camera, u8 numLights, va_list* list) {
    Mtx mv;
    Mtx tmp;
    GXColor matColor;
    u8 compSize;
    s32 colorSize;
    u32 i;
    u32 j;
    u32 lightMask;
    GXColorSrc matSrc;
    f32 ambient;
    Light* light;
    DisplayStateList* state;

    matSrc = GX_SRC_VTX;
    if (dispObj == NULL || dispObj->visibility == 0) {
        return;
    }
    if (lbl_803CC204 == NULL) {
        PSMTXConcat(camera, dispObj->worldMatrix, mv);
        GXLoadPosMtxImm(mv, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
    }

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
    GXSetArray(GX_VA_POS, dispObj->positionData->positionArray, dispObj->positionData->compCount * compSize);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, dispObj->positionData->quantizeInfo >> 4,
                    dispObj->positionData->quantizeInfo & 0xF);

    if (dispObj->colorData != NULL) {
        if (dispObj->colorData->numColors == 1) {
            matSrc = GX_SRC_REG;
            GetColorFromQuant((u8*)dispObj->colorData->colorArray, dispObj->colorData->quantizeInfo, &matColor.r,
                              &matColor.g, &matColor.b, &matColor.a);
            GXSetChanMatColor(GX_COLOR0A0, matColor);
        } else {
            switch ((u8)(dispObj->colorData->quantizeInfo >> 4)) {
            case GX_RGB565:
            case GX_RGBA4:
                colorSize = 2;
                break;
            case GX_RGB8:
            case GX_RGBA6:
                colorSize = 3;
                break;
            case GX_RGBX8:
            case GX_RGBA8:
                colorSize = 4;
                break;
            default:
                colorSize = 0;
                break;
            }
            GXSetArray(GX_VA_CLR0, dispObj->colorData->colorArray, colorSize);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, dispObj->colorData->compCount == 3 ? GX_CLR_RGB : GX_CLR_RGBA,
                            dispObj->colorData->quantizeInfo >> 4, 0);
        }
        GXSetNumChans(1);
    } else {
        matColor.r = 0xFF;
        matColor.g = 0xFF;
        matColor.b = 0xFF;
        matColor.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, matColor);
        GXSetNumChans(1);
        matSrc = GX_SRC_REG;
    }

    if (dispObj->textureData != NULL) {
        for (i = 0; i < dispObj->numTextureChannels; i++) {
            switch ((u8)(dispObj->textureData[i].quantizeInfo >> 4)) {
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
            GXSetArray(GX_VA_TEX0 + i, dispObj->textureData[i].textureCoordArray,
                       compSize * dispObj->textureData[i].compCount);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + i, GX_TEX_ST, dispObj->textureData[i].quantizeInfo >> 4,
                            dispObj->textureData[i].quantizeInfo & 0xF);
            GXSetTexCoordGen2(GX_TEXCOORD0 + i, GX_TG_MTX2X4, GX_TG_TEX0 + i, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        }
    }

    if (dispObj->lightingData != NULL) {
        if (dispObj->lightingData->normalArray != NULL) {
            if (dispObj->lightingData->compCount == 3 || dispObj->lightingData->compCount == 6) {
                switch ((u8)(dispObj->lightingData->quantizeInfo >> 4)) {
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
                GXSetArray(GX_VA_NRM, dispObj->lightingData->normalArray,
                           dispObj->lightingData->compCount * compSize);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, dispObj->lightingData->quantizeInfo >> 4,
                                dispObj->lightingData->quantizeInfo & 0xF);
            } else if (dispObj->lightingData->compCount == 2) {
                switch ((u8)(dispObj->lightingData->quantizeInfo >> 4)) {
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
                GXSetArray(GX_VA_NBT, dispObj->lightingData->normalArray, compSize * 3);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NBT, GX_NRM_NBT3, dispObj->lightingData->quantizeInfo >> 4,
                                dispObj->lightingData->quantizeInfo & 0xF);
            } else {
                OSReport(lbl_800E7F58, dispObj->lightingData->compCount);
            }
        } else {
            switch ((u8)(lbl_803CBB60 >> 4)) {
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
            GXSetArray(GX_VA_NRM, lbl_80111750, compSize * 3);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, lbl_803CBB60 >> 4, lbl_803CBB60 & 0xF);
        }
        if (lbl_803CC204 == NULL) {
            PSMTXInverse(mv, tmp);
            PSMTXTranspose(tmp, mv);
            GXLoadNrmMtxImm(mv, GX_PNMTX0);
        }
    }

    if (dispObj->lightingData != NULL && dispObj->colorData != NULL && numLights != 0) {
        GXColor color;

        ambient = 0.01f * dispObj->lightingData->ambientPercentage;
        lightMask = 0;
        if (!fn_800BD2B0(&color)) {
            color.a = 0xFF;
            color.r = color.g = color.b = 255.0f * ambient;
        }
        GXSetChanAmbColor(GX_COLOR0A0, color);
        ambient = 1.0f - ambient;
        for (j = 0; j < numLights; j++) {
            light = va_arg(*list, Light*);
            color.r = light->color.r * ambient;
            color.g = light->color.g * ambient;
            color.b = light->color.b * ambient;
            GXInitLightColor(&light->lt_obj, color);
            GXInitLightPos(&light->lt_obj, light->worldPosition.x, light->worldPosition.y, light->worldPosition.z);
            GXInitLightDir(&light->lt_obj, light->worldDirection.x, light->worldDirection.y, light->worldDirection.z);
            GXLoadLightObjImm(&light->lt_obj, 1 << j);
            lightMask |= 1 << j;
        }
        GXSetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_REG, matSrc, lightMask, GX_DF_CLAMP, GX_AF_SPOT);
    } else {
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, matSrc, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    }

    state = dispObj->displayData->displayStateList;
    for (j = 0; j < dispObj->displayData->numStateEntries; j++, state++) {
        SetState(state, dispObj, camera);
        if (state->primitiveList != NULL) {
            GXCallDisplayList(state->primitiveList, state->listSize);
        }
    }
}
#endif

// .text:0x800BC7E8 size:0x3C
void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray, u8 numLights, va_list* list) {
    lbl_803CC204 = mtxArray;
    lbl_803CC208 = invTransposeMtxArray;
    DOVARender(dispObj, camera, numLights, list);
    lbl_803CC204 = NULL;
    lbl_803CC208 = NULL;
}

// fn_800BC824, size:0x10
void fn_800BC824(struct DODisplayObj* dispObj, void* shaderData) {
    if (dispObj != NULL) {
        dispObj->shaderData = shaderData;
    }
}

// .text:0x800BC834 size:0x2C
void DOSetWorldMatrix(struct DODisplayObj* dispObj, MtxPtr m) {
    PSMTXCopy(m, dispObj->worldMatrix);
}

// .text:0x800BC860 size:0x258
void InitDisplayObjWithLayout(struct DODisplayObj* dispObj, DODisplayLayout* layout) {
    u16 i;

    if (layout->positionData != NULL) {
        dispObj->positionData = _OSAllocFromHeap(0x20, sizeof(PositionData));
        *dispObj->positionData = *layout->positionData;
    } else {
        dispObj->positionData = NULL;
    }
    if (layout->colorData != NULL) {
        dispObj->colorData = _OSAllocFromHeap(0x20, sizeof(ColorData));
        *dispObj->colorData = *layout->colorData;
    } else {
        dispObj->colorData = NULL;
    }
    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * sizeof(TextureData));
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = layout->textureData[i];
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }
    if (layout->lightingData != NULL) {
        dispObj->lightingData = _OSAllocFromHeap(0x20, sizeof(LightingData));
        *dispObj->lightingData = *layout->lightingData;
    } else {
        dispObj->lightingData = NULL;
    }
    if (layout->displayData != NULL) {
        dispObj->displayData = _OSAllocFromHeap(0x20, sizeof(DisplayData));
        *dispObj->displayData = *layout->displayData;
    } else {
        dispObj->displayData = NULL;
    }
    dispObj->visibility = 1;
    PSMTXIdentity(dispObj->worldMatrix);
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    dispObj->unk15 = layout->unk15;
    memcpy(&dispObj->bounds[1], &layout->bounds[1], 4);
    memcpy(&dispObj->bounds[0], &layout->bounds[0], 4);
    memcpy(&dispObj->bounds[3], &layout->bounds[3], 4);
    memcpy(&dispObj->bounds[2], &layout->bounds[2], 4);
    memcpy(&dispObj->bounds[5], &layout->bounds[5], 4);
    memcpy(&dispObj->bounds[4], &layout->bounds[4], 4);
}

// .text:0x800BCAB8 size:0x8C
void DOGet(struct DODisplayObj** dispObj, DODisplayDataPtr pal, u16 id) {
    DODisplayLayout* layout;

    if (id >= pal->numDescriptors) {
        OSReport(lbl_800E7F8C, id, pal->numDescriptors);
        *dispObj = NULL;
        return;
    }
    layout = pal->descriptorArray[id].layout;
    *dispObj = _OSAllocFromHeap(0x20, sizeof(struct DODisplayObj));
    InitDisplayObjWithLayout(*dispObj, layout);
}

// .text:0x800BCB44 size:0x21C
void* LoadGeoPalette(DODisplayDataPtr pal) {
    u16 j;
    void* skinPositions;
    DODisplayLayout* layout;
    u16 i;

    skinPositions = NULL;
    if (pal->userDataSize != 0 && pal->userData != NULL) {
        pal->userData = GEO_RELOC(pal->userData, pal);
    }
    pal->descriptorArray = GEO_RELOC(pal->descriptorArray, pal);
    for (i = 0; i < pal->numDescriptors; i++) {
        pal->descriptorArray[i].layout = GEO_RELOC(pal, pal->descriptorArray[i].layout);
        pal->descriptorArray[i].name = GEO_RELOC(pal, pal->descriptorArray[i].name);
        layout = pal->descriptorArray[i].layout;
        if (layout->positionData != NULL) {
            layout->positionData = GEO_RELOC(layout->positionData, layout);
            if (layout->positionData->positionArray != NULL) {
                layout->positionData->positionArray = GEO_RELOC(layout->positionData->positionArray, layout);
            }
            if (layout->positionData->compCount == 6) {
                skinPositions = layout->positionData->positionArray;
            }
        }
        if (layout->colorData != NULL) {
            layout->colorData = GEO_RELOC(layout->colorData, layout);
            if (layout->colorData->colorArray != NULL) {
                layout->colorData->colorArray = GEO_RELOC(layout->colorData->colorArray, layout);
            }
        }
        if (layout->textureData != NULL) {
            layout->textureData = GEO_RELOC(layout->textureData, layout);
            for (j = 0; j < layout->numTextureChannels; j++) {
                if (layout->textureData[j].textureCoordArray != NULL) {
                    layout->textureData[j].textureCoordArray = GEO_RELOC(layout, layout->textureData[j].textureCoordArray);
                }
                if (layout->textureData[j].texturePaletteName != NULL) {
                    layout->textureData[j].texturePaletteName = GEO_RELOC(layout, layout->textureData[j].texturePaletteName);
                }
            }
        }
        if (layout->lightingData != NULL) {
            layout->lightingData = GEO_RELOC(layout->lightingData, layout);
            if (layout->lightingData->normalArray != NULL) {
                layout->lightingData->normalArray = GEO_RELOC(layout->lightingData->normalArray, layout);
            }
        }
        if (layout->displayData != NULL) {
            layout->displayData = GEO_RELOC(layout->displayData, layout);
            if (layout->displayData->primitiveBank != NULL) {
                layout->displayData->primitiveBank = GEO_RELOC(layout->displayData->primitiveBank, layout);
            }
            if (layout->displayData->displayStateList != NULL) {
                layout->displayData->displayStateList = GEO_RELOC(layout->displayData->displayStateList, layout);
            }
            for (j = 0; j < layout->displayData->numStateEntries; j++) {
                if (layout->displayData->displayStateList[j].primitiveList != NULL) {
                    layout->displayData->displayStateList[j].primitiveList =
                        GEO_RELOC(layout, layout->displayData->displayStateList[j].primitiveList);
                }
            }
        }
        if (layout->unk18 != NULL) {
            layout->unk18 = GEO_RELOC(layout->unk18, layout);
        }
    }
    return skinPositions;
}

// .text:0x800BCD60 size:0x5C
void convertGeometryAndSknHeader(DODisplayDataPtr pal, void* sknHeader) {
    void* skinPositions = LoadGeoPalette(pal);

    if (sknHeader != NULL) {
        SKNLoadFile(sknHeader, skinPositions);
    }
    pal->skinPositions = skinPositions;
}

// .text:0x800BCDBC size:0x7C
void fn_800BCDBC(DODisplayDataPtr pal) {
    s32 i;

    for (i = pal->numDescriptors - 1; i >= 0; i--) {
        if (pal->descriptorArray[i].dispObj->textureData != NULL) {
            fn_800ACFB0(pal->descriptorArray[i].dispObj->textureData);
        }
    }
    fn_800ACFB0(pal->descriptorArray[0].dispObj);
}

// .text:0x800BCE38 size:0xC0
void fn_800BCE38(DODisplayDataPtr pal) {
    struct DODisplayObj* dispObjs;
    u32 i;

    pal->userData = GEO_RELOC(pal, pal->userData);
    pal->descriptorArray = GEO_RELOC(pal, pal->descriptorArray);
    dispObjs = _OSAllocFromHeap(0x20, pal->numDescriptors * sizeof(struct DODisplayObj));
    for (i = 0; i < pal->numDescriptors; i++) {
        fn_800BCEF8(GEO_RELOC(pal, pal->descriptorArray[i].layout), &dispObjs[i]);
        pal->descriptorArray[i].dispObj = &dispObjs[i];
        pal->descriptorArray[i].name = GEO_RELOC(pal, pal->descriptorArray[i].name);
    }
}

// .text:0x800BCEF8 size:0x298
void* fn_800BCEF8(DODisplayLayout* layout, struct DODisplayObj* dispObj) {
    void* skinPositions;
    s32 i;

    skinPositions = NULL;
    if (layout->positionData != NULL) {
        dispObj->positionData = GEO_RELOC(layout, layout->positionData);
        dispObj->positionData->positionArray = GEO_RELOC(layout, dispObj->positionData->positionArray);
        if (dispObj->positionData->compCount == 6) {
            skinPositions = dispObj->positionData->positionArray;
        }
    } else {
        dispObj->positionData = NULL;
    }
    if (layout->colorData != NULL) {
        dispObj->colorData = GEO_RELOC(layout, layout->colorData);
        dispObj->colorData->colorArray = GEO_RELOC(layout, dispObj->colorData->colorArray);
    } else {
        dispObj->colorData = NULL;
    }
    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * sizeof(TextureData));
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = *(TextureData*)GEO_RELOC(&layout->textureData[i], layout);
            dispObj->textureData[i].textureCoordArray = GEO_RELOC(layout, dispObj->textureData[i].textureCoordArray);
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }
    if (layout->lightingData != NULL) {
        dispObj->lightingData = GEO_RELOC(layout, layout->lightingData);
        dispObj->lightingData->normalArray = GEO_RELOC(layout, dispObj->lightingData->normalArray);
    } else {
        dispObj->lightingData = NULL;
    }
    if (layout->displayData != NULL) {
        dispObj->displayData = GEO_RELOC(layout, layout->displayData);
        dispObj->displayData->primitiveBank = GEO_RELOC(layout, dispObj->displayData->primitiveBank);
        dispObj->displayData->displayStateList = GEO_RELOC(layout, dispObj->displayData->displayStateList);
        for (i = 0; i < dispObj->displayData->numStateEntries; i++) {
            if (dispObj->displayData->displayStateList[i].primitiveList != NULL) {
                dispObj->displayData->displayStateList[i].primitiveList =
                    GEO_RELOC(layout, dispObj->displayData->displayStateList[i].primitiveList);
            }
        }
    } else {
        dispObj->displayData = NULL;
    }
    dispObj->unk15 = layout->unk15;
    dispObj->visibility = 1;
    dispObj->unk17 = 0;
    dispObj->tevCallback = fn_800BA44C;
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    memcpy(&dispObj->bounds[1], &layout->bounds[1], 4);
    memcpy(&dispObj->bounds[0], &layout->bounds[0], 4);
    memcpy(&dispObj->bounds[3], &layout->bounds[3], 4);
    memcpy(&dispObj->bounds[2], &layout->bounds[2], 4);
    memcpy(&dispObj->bounds[5], &layout->bounds[5], 4);
    memcpy(&dispObj->bounds[4], &layout->bounds[4], 4);
    return skinPositions;
}

extern DOShadowTevCallback lbl_803CC20C;

// fn_800BD190, size:0x58
void fn_800BD190(GQRValueGroups* groups, s32 value) {
    u32 i;
    s32 j;
    for (i = 0; i < groups->count; i++) {
        for (j = 0; j < groups->groups[i].group->count; j++) {
            groups->groups[i].group->entries[j].value = value;
        }
    }
}

// __MTGQR5, size:0x8
void __MTGQR5(register u32 value) {
    asm {
        mtspr GQR5, value
    }
}

// fn_800BD1E8, size:0x8
void fn_800BD1E8(DOShadowTevCallback callback) {
    lbl_803CC20C = callback;
}

// __MTGQR6, size:0x8
void __MTGQR6(register u32 value) {
    asm {
        mtspr GQR6, value
    }
}

// __MTGQR7, size:0x8
void __MTGQR7(register u32 value) {
    asm {
        mtspr GQR7, value
    }
}

// .text:0x800BD208 size:0x38
void GQRSetup7(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR7((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

// .text:0x800BD240 size:0x38
void GQRSetup6(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR6((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

// .text:0x800BD278 size:0x38
void GQRSetup5(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR5((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

extern GXColor lbl_803CC224;

extern u8 lbl_803CC220;

// fn_800BD2B0, size:0x1C
u8 fn_800BD2B0(GXColor* color) {
    if (lbl_803CC220 != 0) {
        *color = lbl_803CC224;
    }
    return lbl_803CC220;
}

// fn_800BD2CC, size:0x10
void fn_800BD2CC(s32 flag, GXColor color) {
    lbl_803CC220 = flag;
    lbl_803CC224 = color;
}

// fn_800BD2DC, size:0x24
void fn_800BD2DC(void) {
    lbl_803CC220 = 0;
    lbl_803CC224.r = 0;
    lbl_803CC224.b = 0;
    lbl_803CC224.g = 0;
    lbl_803CC224.a = 0xFF;
}

// .text:0x800BD300 size:0xA0
void LITXForm(Light* light, MtxPtr view) {
    Mtx m;

    CTRLBuildMatrix(&light->control, m);
    if (light->parent != NULL) {
        PSMTXConcat(light->parent, m, m);
    }
    PSMTXConcat(view, m, m);
    PSMTXMultVec(m, &light->position, &light->worldPosition);
    PSMTXInverse(m, m);
    PSMTXTranspose(m, m);
    PSMTXMultVec(m, &light->direction, &light->worldDirection);
}

// .text:0x800BD3A0 size:0xC
void LITInitColor(Light* light, GXColor* color) {
    light->color = *color;
}

// .text:0x800BD3AC size:0x10
void LITInitDir(Light* light, f32 x, f32 y, f32 z) {
    light->direction.x = x;
    light->direction.y = y;
    light->direction.z = z;
}

// .text:0x800BD3BC size:0x10
void LITInitPos(Light* light, f32 x, f32 y, f32 z) {
    light->position.x = x;
    light->position.y = y;
    light->position.z = z;
}

// .text:0x800BD3CC size:0x20
void LITInitAttn(Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) {
    GXInitLightAttn(&light->lt_obj, a0, a1, a2, k0, k1, k2);
}
