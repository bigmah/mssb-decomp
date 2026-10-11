#include "challenge/rep_0138.h"


#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#include <string.h>
#include "stl/math.h"
#include "Dolphin/os.h"
#include "C3/geoPalette.h"

extern GXCullMode lbl_1_data_8C4[];
extern void* lbl_1_data_848[3];
extern void fn_1_73B8(void* context, s32 count, ...);

typedef union ChallengeColor {
    GXColor color;
    s32 word;
} ChallengeColor;

typedef struct ChallengeFog {
    ChallengeColor color;
    f32 start;
    f32 end;
} ChallengeFog;

extern ChallengeColor lbl_1_data_858[];
extern ChallengeFog* lbl_1_bss_4E0[];
extern const f32 lbl_1_rodata_1D8;
extern const f32 lbl_1_rodata_208;

extern const f32 lbl_1_rodata_21C[];
extern const f32 lbl_1_rodata_220[];
extern const f32 lbl_1_rodata_224[];
extern const f32 lbl_1_rodata_228[];
extern const f32 lbl_1_rodata_22C[];
extern const f32 lbl_1_rodata_230[];
extern const f32 lbl_1_rodata_234[];
extern const f32 lbl_1_rodata_238[];
extern const f32 lbl_1_rodata_23C;
extern const f32 lbl_1_rodata_240;
extern const f32 lbl_1_rodata_244;

// fn_1_7E04, size:0xF4
void fn_1_7E04(f32 scale) {
    Mtx44 projection;
    f32 inverse = lbl_1_rodata_1D8 / scale;
    C_MTXFrustum(projection, lbl_1_rodata_21C[0] * inverse, lbl_1_rodata_220[0] * inverse,
                 lbl_1_rodata_224[0] * inverse, lbl_1_rodata_228[0] * inverse,
                 lbl_1_rodata_1D8, lbl_1_rodata_208);
    GXSetProjection(projection, GX_PERSPECTIVE);
    fn_800B806C(0, lbl_1_rodata_22C[0] * inverse, lbl_1_rodata_230[0] * inverse,
               lbl_1_rodata_234[0] * inverse, lbl_1_rodata_238[0] * inverse,
               lbl_1_rodata_23C, lbl_1_rodata_240, lbl_1_rodata_244);
}

extern s32 lbl_1_bss_C4;

extern u8 lbl_1_bss_C2[];
extern u8 lbl_1_data_85C[];

extern u8 lbl_1_common_bss_472B4[];
extern u8* lbl_803CC1B8[];
extern void* lbl_80366158[];
extern void* _OSAllocFromHeap(s32, s32);
extern void fn_800B472C(void*);
extern void fn_1_6848(u8*);
extern const f32 lbl_1_rodata_1F0;
extern const f32 lbl_1_rodata_1F4;
extern const f32 lbl_1_rodata_1F8;
typedef struct { u8 b[0x6C]; } Chal6C;
extern void fn_1_4DD8(u16* effects);
extern u8 lbl_803CBBC0;
extern void fn_800A7D4C(int, void*);
extern const f32 lbl_1_rodata_204;
typedef struct { u8 b[8]; } Chal8;
static u8 sPad[0x5E4] = {1};
static Chal8 sTabA[3] = {{{1}}};
static Chal8 sTabB[2] = {{{1}}};
static Chal8 sTabC[2] = {{{1}}};
static u8 sPad2[0x15C] = {1};
static u8 sMipCount = 1;
static f32 sMipScale[4] = {1.0f};
static f32 sLodBias = 1.0f;
static GXTexFilter sMinFilter = GX_LINEAR;
extern const f32 lbl_1_rodata_1A8;
extern Vec lbl_1_data_A3C;
extern const f32 lbl_1_rodata_1C8;
extern const f32 lbl_1_rodata_1CC;
extern const f32 lbl_1_rodata_1DC;
extern const f32 lbl_1_rodata_1E0;
extern const f64 lbl_1_rodata_1E8;

// fn_1_717C, size:0x104
void fn_1_717C(ChallengeModelOffsets* model) {
    u8* geometry;
    u8* actor;
    u8* textures;
    actor = (u8*)model + model->mainActor;
    geometry = (u8*)model + model->mainGeometry;
    textures = (u8*)model + model->textures;
    fn_1_4DD8((u16*)((u8*)model + model->effects));
    fn_800B49E4(actor);
    fn_800BCE38(geometry);
    convertTextureHeader(textures);
    *(u8**)(lbl_1_common_bss_472B4 + 0x58) = textures + 4;
    fn_800BD190((struct GQRValueGroups*)geometry, (s32)textures);
    haveActLayoutPointToGeoHeader(actor, geometry);
    *(u16*)(lbl_1_common_bss_472B4 + 0x22A) = *(u16*)(actor + 6);
    *(u8**)(lbl_1_common_bss_472B4 + 0x130) = actor;
    *(u8**)(lbl_1_common_bss_472B4 + 0xC4) = actor;
    actor = (u8*)model + model->secondaryActor;
    geometry = (u8*)model + model->secondaryGeometry;
    fn_800B49E4(actor);
    fn_800BCE38(geometry);
    fn_800BD190((struct GQRValueGroups*)geometry, (s32)textures);
    haveActLayoutPointToGeoHeader(actor, geometry);
    *(u8**)(lbl_1_common_bss_472B4 + 0x208) = actor;
    *(u8**)(lbl_1_common_bss_472B4 + 0x19C) = actor;
}

// fn_1_7EF8, size:0x100
void fn_1_7EF8(void) {
    switch ((s32)*(u16*)((u8*)&lbl_803C77B8 + 4)) {
    case 4:
    case 8:
        lbl_1_bss_C2[0] = !lbl_1_bss_C2[0];
        break;
    case 1: {
        s32 value = (s32)fn_80048EA8(lbl_1_bss_C2[0]);
        fn_80048E00(lbl_1_bss_C2[0], value - 1);
        break;
    }
    case 2: {
        s32 value = (s32)fn_80048EA8(lbl_1_bss_C2[0]);
        fn_80048E00(lbl_1_bss_C2[0], value + 1);
        break;
    }
    case 0x100: {
        u8 enabled = !lbl_1_data_85C[0];
        lbl_1_data_85C[0] = enabled;
        if (enabled != 0) {
            fn_80048C14(0x3F);
        } else {
            fn_80048C14(0);
        }
        break;
    }
    }
}

// fn_1_78E4, size:0x7C
void fn_1_78E4(void) {
    GXColor clear = lbl_1_data_858[0].color;
    GXSetCopyClear(clear, 0xFFFFFF);
    if (lbl_1_bss_C4 != 0) {
        GXSetCullMode(GX_CULL_NONE);
    } else {
        GXSetCullMode(GX_CULL_BACK);
    }
    SetFogNoneAgain();
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

// fn_1_786C, size:0x78
void fn_1_786C(void) {
    GXColor clear;
    GXColor color;
    ChallengeFog* fog;
    fn_80048D4C();
    clear = lbl_1_data_858[0].color;
    GXSetCopyClear(clear, 0xFFFFFF);
    fog = lbl_1_bss_4E0[0];
    color = fog->color.color;
    // This call passes the packed colour through the GXColor value ABI.
    ((void (*)(u8, GXColor, f32, f32, f32, f32))SetFog)(fog->color.color.a, color, fog->start, fog->end, lbl_1_rodata_1D8, lbl_1_rodata_208);
}

// fn_1_54E0, size:0x60
void fn_1_54E0(void* matrix) {
    s32 i;
    for (i = 0; i < 3; i++) {
        LITXForm(lbl_1_data_848[i], matrix);
    }
}

// fn_1_77EC, size:0x5C
void fn_1_77EC(void* context) {
    GXSetCullMode(lbl_1_data_8C4[0]);
    fn_1_73B8(context, 3, lbl_1_data_848[0], lbl_1_data_848[1], lbl_1_data_848[2]);
}

// .text:0x5540 size:0x4
void fn_1_5540(void) {
}

// fn_1_7848, size:0x24
void fn_1_7848(void) {
    fn_80048C28();
    fn_80048C1C();
}

// fn_1_7280, size:0x138
void fn_1_7280(void) {
    u8* p;
    u8* q;
    p = lbl_1_common_bss_472B4 + lbl_803CBBC0 * 0x6C + 0x5C;
    PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(p + 0x38));
    fn_800A7D4C(0, &sTabC[lbl_803CBBC0]);
    fn_800A7D4C(0, p);
    fn_800A7D4C(0, &sTabB[lbl_803CBBC0]);
    q = lbl_1_common_bss_472B4 + lbl_803CBBC0 * 0x6C + 0x134;
    PSMTXRotRad((f32(*)[4])(q + 8), 0x59, lbl_1_rodata_204 * (f32)*(u16*)(lbl_1_common_bss_472B4 + 0x23A));
    PSMTXCopy((f32(*)[4])lbl_1_common_bss_472B4, (f32(*)[4])(q + 0x38));
    fn_800A7D4C(0, q);
    fn_800A7D4C(0, &sTabA[lbl_803CBBC0]);
}

// fn_1_6578, size:0x14C
void fn_1_6578(void* obj, void* image, s32 w, s32 h) {
    GXTexFilter filter;
    f32* scale;
    s32 w0;
    s32 h0;
    s32 offset;
    s32 level;
    w0 = w;
    h0 = h;
    offset = 0;
    if (sMipCount == 0) {
        w = w / 4;
        h = h / 4;
        fn_1_6050((u16*)image, w, h, lbl_1_rodata_1D8);
        filter = GX_LINEAR;
    } else {
        scale = sMipScale;
        for (level = 0; level <= sMipCount; level++) {
            fn_1_6050((u16*)image + offset, w0, h0, *scale);
            offset += w0 * h0;
            w0 /= 2;
            h0 /= 2;
            scale++;
        }
        filter = sMinFilter;
    }
    GXInitTexObj(obj, image, w, h, GX_TF_IA8, GX_REPEAT, GX_REPEAT, sMipCount);
    GXInitTexObjLOD(obj, filter, GX_LINEAR, lbl_1_rodata_1A8, (f32)sMipCount, sLodBias, 0, 0, GX_ANISO_1);
}

// fn_1_66C4, size:0x184
void fn_1_66C4(void) {
    u8* object = lbl_803CC1B8[0];
    s32 a;
    s32 b;
    fn_800AD038(lbl_80366158[2]);
    *(s16*)(object + 0x10) = 0;
    a = *(s8*)(lbl_1_common_bss_472B4 + 0x230);
    b = *(s8*)(lbl_1_common_bss_472B4 + 0x231);
    memset(lbl_1_common_bss_472B4, 0, 0x240);
    *(u8*)(lbl_1_common_bss_472B4 + 0x230) = a;
    *(u8*)(lbl_1_common_bss_472B4 + 0x231) = b;
    *(void**)(lbl_1_common_bss_472B4 + 0x21C) = _OSAllocFromHeap(0x20, 0x80000);
    *(f32*)(lbl_1_common_bss_472B4 + 0x4C) = lbl_1_rodata_1F0;
    *(f32*)(lbl_1_common_bss_472B4 + 0x50) = lbl_1_rodata_1F4;
    *(u16*)(lbl_1_common_bss_472B4 + 0x30) = 0xF36C;
    *(f32*)(lbl_1_common_bss_472B4 + 0x54) = lbl_1_rodata_1F8;
    *(s16*)(lbl_1_common_bss_472B4 + 0x22E) = -1;
    lbl_1_common_bss_472B4[0x234] = 0;
    PSMTXIdentity((f32(*)[4])(lbl_1_common_bss_472B4 + 0x64));
    *(void**)(lbl_1_common_bss_472B4 + 0x60) = fn_1_77EC;
    *(Chal6C*)(lbl_1_common_bss_472B4 + 0xC8) = *(Chal6C*)(lbl_1_common_bss_472B4 + 0x5C);
    *(void**)(lbl_1_common_bss_472B4 + 0x138) = fn_800B472C;
    *(Chal6C*)(lbl_1_common_bss_472B4 + 0x1A0) = *(Chal6C*)(lbl_1_common_bss_472B4 + 0x134);
    *(void**)lbl_803CC1B8[0] = fn_1_6848;
}

typedef struct ChalTexState {
    u8 pad0[0x11];
    u8 replace;
    u8 pad12[2];
    GXIndTexScale tScale;
    GXIndTexScale sScale;
    u8 flags;
    u8 pad1d[0x424-0x1d];
    GXTexObj obj;
} ChalTexState;
static ChalTexState lbl_1_bss_C0;
extern u8 lbl_1_data_2A8[];


void fn_1_5544(GXTevStageID stage, GXIndTexStageID indStage, GXIndTexMtxID mtx, GXTexCoordID coord, GXTexMapID map) {
    u8* d = lbl_1_data_2A8;
    ChalTexState* st = (ChalTexState*)((u8*)&lbl_1_bss_C0 + 0);
    u8 flags;
    GXLoadTexObj(&st->obj, map);
    flags = st->flags;
    if (flags != 0) {
        if (flags & 2) {
            map--;
        }
        if (flags & 4) {
            coord--;
        }
        GXSetTevOrder(stage, coord, map, GX_COLOR_NULL);
        GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        return;
    }
    GXSetNumIndStages(1);
    GXSetIndTexMtx(mtx, (const f32(*)[3])(d + 0x7CC), (s8) * (f32*)(d + 0x7C8));
    GXSetIndTexOrder(indStage, coord, map);
    GXSetIndTexCoordScale(indStage, st->sScale, st->tScale);
    GXSetTevIndWarp(stage, indStage, d[0x7C5], st->replace, mtx);
}

// fn_1_5924, size:0x19C
// Byte/texel offset of (x, y) in a GX 4x4/8x4/8x8-tiled texture with the given bits per pixel.
// NONMATCHING 62%: same instructions, the x terms are scheduled before the y terms
#if NONMATCHING
s32 fn_1_5924(s32 width, s32 x, s32 y, s32 bpp, s32 alt) {
    s32 offset;
    switch (bpp) {
    case 4:
        return (y / 8) * width * 8 + ((y % 8) * 8 + x % 8) + (x / 8) * 32;
    case 8:
        return (y / 4) * width * 4 + ((y % 4) * 8 + x % 8) + (x / 8) * 32;
    case 16:
        return (y / 4) * width * 4 + ((y % 4) * 4 + x % 4) + (x / 4) * 16;
    case 32:
        offset = (y / 4) * width * 4 + ((y % 4) * 8 + x % 4) + (x / 8) * 16;
        if (alt != 0) {
            offset += 16;
        }
        return offset;
    }
    return width;
}
#endif

extern f32 lbl_1_data_200[];
extern const f32 lbl_1_rodata_210;
extern const f32 lbl_1_rodata_218;

void fn_1_8368(void) {
    s32 v1;
    if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 1) {
        v1 = *(s16*)(lbl_1_common_bss_472B4 + 0x22E) - 1;
        *(s16*)(lbl_1_common_bss_472B4 + 0x22E) = v1;
        if ((s16)v1 < -1) {
            *(s16*)(lbl_1_common_bss_472B4 + 0x22E) = *(s16*)(lbl_1_common_bss_472B4 + 0x228) - 1;
        }
    } else if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 2) {
        s16 v2 = *(s16*)(lbl_1_common_bss_472B4 + 0x22E);
        v2++;
        *(s16*)(lbl_1_common_bss_472B4 + 0x22E) = v2;
        if (v2 >= *(s16*)(lbl_1_common_bss_472B4 + 0x228)) {
            *(s16*)(lbl_1_common_bss_472B4 + 0x22E) = -1;
        }
    } else if (*(u16*)((u8*)&lbl_803C77B8 + 2) & 0x400) {
        lbl_1_common_bss_472B4[0x239] ^= 1;
    } else if (*(u16*)((u8*)&lbl_803C77B8 + 2) & 0x100) {
        lbl_1_common_bss_472B4[0x238] ^= 1;
    }
    lbl_1_data_200[0] = (f32)(s8)((u8*)&lbl_803C77B8)[0x10] * lbl_1_rodata_210 + lbl_1_data_200[0];
    lbl_1_data_200[2] = (f32)(s8)((u8*)&lbl_803C77B8)[0x11] * lbl_1_rodata_210 + lbl_1_data_200[2];
    lbl_1_data_200[3] = (f32)(s8)((u8*)&lbl_803C77B8)[0x12] * lbl_1_rodata_210 + lbl_1_data_200[3];
    lbl_1_data_200[5] = (f32)(s8)((u8*)&lbl_803C77B8)[0x13] * lbl_1_rodata_210 + lbl_1_data_200[5];
    if (!(*(u16*)&lbl_803C77B8 & 0x100)) {
        lbl_1_data_200[1] = -((f32)((u8*)&lbl_803C77B8)[0x15] * lbl_1_rodata_218 - lbl_1_data_200[1]);
        lbl_1_data_200[1] = (f32)((u8*)&lbl_803C77B8)[0x14] * lbl_1_rodata_218 + lbl_1_data_200[1];
    } else {
        lbl_1_data_200[4] = -((f32)((u8*)&lbl_803C77B8)[0x15] * lbl_1_rodata_218 - lbl_1_data_200[4]);
        lbl_1_data_200[4] = (f32)((u8*)&lbl_803C77B8)[0x14] * lbl_1_rodata_218 + lbl_1_data_200[4];
    }
}

extern GXTexObj lbl_1_bss_4E4;
extern const f32 lbl_1_rodata_1AC;
extern const f32 lbl_1_rodata_1B0;
extern const f32 lbl_1_rodata_1B4;
extern const f32 lbl_1_rodata_1B8;
extern const f32 lbl_1_rodata_1BC;
extern const f32 lbl_1_rodata_1C0;
extern const f32 lbl_1_rodata_1C4;

// fn_1_5698, size:0x28C
void fn_1_5698(void) {
    Mtx44 proj;
    Mtx pos;
    C_MTXOrtho(proj, lbl_1_rodata_1A8, lbl_1_rodata_1AC, lbl_1_rodata_1A8, lbl_1_rodata_1B0, lbl_1_rodata_1B4, lbl_1_rodata_1B8);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(pos);
    GXLoadPosMtxImm(pos, 0);
    GXSetCurrentMtx(0);
    GXSetZMode(1, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 2);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, 0x3C, 0, 0x7D);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXLoadTexObj(&lbl_1_bss_4E4, GX_TEXMAP0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1A8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1BC;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1A8;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 0;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1A8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1C0;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1A8;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1C4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1C0;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1A8;
    GXWGFifo.u16 = 4;
    GXWGFifo.u16 = 4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1C4;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1BC;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_1A8;
    GXWGFifo.u16 = 4;
    GXWGFifo.u16 = 0;
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
}

// fn_1_7FF8, size:0x370
// Debug pad editor for the fog settings (mode, colour, start, end).
// NONMATCHING 99%: in the two `+1` clamps the 512 limit and the field load swap f0/f2
#if NONMATCHING
void fn_1_7FF8(void) {
    s32 t;
    s32 u;
    f32 f;
    switch ((s32) * (u16*)((u8*)&lbl_803C77B8 + 4)) {
    case 8:
        t = lbl_1_common_bss_472B4[0x23C] - 1;
        lbl_1_common_bss_472B4[0x23C] = t;
        if ((s8)t < 0) {
            lbl_1_common_bss_472B4[0x23C] = 5;
        }
        return;
    case 4:
        t = lbl_1_common_bss_472B4[0x23C] + 1;
        lbl_1_common_bss_472B4[0x23C] = t;
        if ((s8)t >= 6) {
            lbl_1_common_bss_472B4[0x23C] = 0;
            return;
        }
        break;
    case 1:
        switch ((s8)lbl_1_common_bss_472B4[0x23C]) {
        case 0:
            u = lbl_1_bss_4E0[0]->color.color.a - 1;
            lbl_1_bss_4E0[0]->color.color.a = u;
            switch ((u8)u) {
            case 0xFF:
                lbl_1_bss_4E0[0]->color.color.a = 7;
                return;
            case 3:
                lbl_1_bss_4E0[0]->color.color.a = 2;
                return;
            case 1:
                lbl_1_bss_4E0[0]->color.color.a = 0;
                return;
            }
            break;
        case 1:
            lbl_1_bss_4E0[0]->color.color.r = lbl_1_bss_4E0[0]->color.color.r - 1;
            return;
        case 2:
            lbl_1_bss_4E0[0]->color.color.g = lbl_1_bss_4E0[0]->color.color.g - 1;
            return;
        case 3:
            lbl_1_bss_4E0[0]->color.color.b = lbl_1_bss_4E0[0]->color.color.b - 1;
            return;
        case 4:
            f = lbl_1_bss_4E0[0]->start;
            f = f - lbl_1_rodata_1D8;
            lbl_1_bss_4E0[0]->start = f;
            if (f < lbl_1_rodata_1A8) {
                lbl_1_bss_4E0[0]->start = lbl_1_rodata_1A8;
                return;
            }
            break;
        case 5:
            f = lbl_1_bss_4E0[0]->end;
            f = f - lbl_1_rodata_1D8;
            lbl_1_bss_4E0[0]->end = f;
            if (f < lbl_1_rodata_1A8) {
                lbl_1_bss_4E0[0]->end = lbl_1_rodata_1A8;
                return;
            }
            break;
        }
        break;
    case 2:
        switch ((s8)lbl_1_common_bss_472B4[0x23C]) {
        case 0:
            u = lbl_1_bss_4E0[0]->color.color.a + 1;
            lbl_1_bss_4E0[0]->color.color.a = u;
            switch ((u8)u) {
            case 1:
                lbl_1_bss_4E0[0]->color.color.a = 2;
                return;
            case 3:
                lbl_1_bss_4E0[0]->color.color.a = 4;
                return;
            case 8:
                lbl_1_bss_4E0[0]->color.color.a = 0;
                return;
            }
            break;
        case 1:
            lbl_1_bss_4E0[0]->color.color.r = lbl_1_bss_4E0[0]->color.color.r + 1;
            return;
        case 2:
            lbl_1_bss_4E0[0]->color.color.g = lbl_1_bss_4E0[0]->color.color.g + 1;
            return;
        case 3:
            lbl_1_bss_4E0[0]->color.color.b = lbl_1_bss_4E0[0]->color.color.b + 1;
            return;
        case 4:
            f = lbl_1_bss_4E0[0]->start;
            f = f + lbl_1_rodata_1D8;
            lbl_1_bss_4E0[0]->start = f;
            if (f > lbl_1_rodata_208) {
                lbl_1_bss_4E0[0]->start = lbl_1_rodata_208;
                return;
            }
            break;
        case 5:
            f = lbl_1_bss_4E0[0]->end;
            f = f + lbl_1_rodata_1D8;
            lbl_1_bss_4E0[0]->end = f;
            if (f > lbl_1_rodata_208) {
                lbl_1_bss_4E0[0]->end = lbl_1_rodata_208;
                return;
            }
            break;
        }
        break;
    }
}
#endif

// Display-list opcodes not in GXEnum.h.
#define DL_NOP 0x00
#define DL_LOAD_CP_REG 0x08
#define DL_LOAD_XF_REG 0x10
#define DL_LOAD_INDX_A 0x20
#define DL_LOAD_INDX_B 0x28
#define DL_LOAD_INDX_C 0x30
#define DL_LOAD_INDX_D 0x38
#define DL_LOAD_BP_REG 0x61

void fn_1_4E98(struct DODisplayObj* obj, MtxPtr camera) {
    Mtx m;
    s32 attrType[GX_VA_TEX7 + 1];
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    s16* v;
    s32 nrmIdx;
    s32 posIdx;
    s32 count;
    s32 i;
    u32 offset;
    u8* dl;
    s32 attr;
    s32 shift;
    s32 handled;
    s32 type;
    u32 setting;
    s32 skip;
    u8 quant;
    u8 comp;

    if (obj->lightingData == NULL || obj->positionData == NULL || obj->displayData == NULL) {
        return;
    }
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    PSMTXConcat(camera, obj->worldMatrix, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    for (i = 0; i < obj->displayData->numStateEntries; i++) {
        switch (obj->displayData->displayStateList[i].id) {
        case 1:
        case 3:
            break;
        case 2:
            memset(attrType, 0, sizeof(attrType));
            setting = obj->displayData->displayStateList[i].setting;
            for (attr = GX_VA_POS, shift = 2; attr <= GX_VA_TEX7; attr++, shift += 2) {
                type = (setting >> shift) & 3;
                if (type != 0) {
                    attrType[attr] = type;
                }
            }
            break;
        }
        dl = (u8*)obj->displayData->displayStateList[i].primitiveList;
        if (dl == NULL) {
            continue;
        }
        for (offset = 0; offset < obj->displayData->displayStateList[i].listSize;) {
            handled = 0;
            switch (*dl) {
            case DL_NOP:
                handled = 1;
                dl += 1;
                offset += 1;
                break;
            case DL_LOAD_BP_REG:
                handled = 1;
                dl += 5;
                offset += 5;
                break;
            case DL_LOAD_CP_REG:
                handled = 1;
                dl += 6;
                offset += 6;
                break;
            case DL_LOAD_XF_REG:
                handled = 1;
                // TODO type: reads the opcode byte as the high byte of the length
                skip = *(u16*)dl * 4 + 5;
                dl += skip;
                offset += skip;
                break;
            case DL_LOAD_INDX_A:
            case DL_LOAD_INDX_B:
            case DL_LOAD_INDX_C:
            case DL_LOAD_INDX_D:
                handled = 1;
                dl += 5;
                break;
            case GX_CMD_CALL_DL:
            case GX_CMD_INVL_VC:
                handled = 1;
                dl += 1;
                offset += 1;
                break;
            case GX_QUADS:
            case GX_TRIANGLES:
            case GX_TRIANGLESTRIP:
            case GX_TRIANGLEFAN:
            case GX_LINES:
            case GX_LINESTRIP:
            case GX_POINTS:
                break;
            }
            if (handled != 0) {
                continue;
            }
            count = *(u16*)(dl + 1);
            dl += 3;
            offset += 3;
            GXBegin(GX_LINES, GX_VTXFMT0, count * 2);
            while (count-- != 0) {
                for (attr = GX_VA_POS; attr <= GX_VA_TEX7; attr++) {
                    type = attrType[attr];
                    if (type == 0) {
                        continue;
                    }
                    switch (attr) {
                    case GX_VA_POS:
                        switch (type) {
                        case GX_DIRECT:
                            break;
                        case GX_INDEX8:
                            posIdx = *dl;
                            break;
                        case GX_INDEX16:
                            posIdx = *(u16*)dl;
                            break;
                        }
                        break;
                    case GX_VA_NRM:
                        switch (type) {
                        case GX_DIRECT:
                            break;
                        case GX_INDEX8:
                            nrmIdx = *dl;
                            break;
                        case GX_INDEX16:
                            nrmIdx = *(u16*)dl;
                            break;
                        }
                        break;
                    }
                    switch (type) {
                    case GX_INDEX8:
                        dl += 1;
                        offset += 1;
                        break;
                    case GX_INDEX16:
                        dl += 2;
                        offset += 2;
                        break;
                    }
                }
                quant = obj->positionData->quantizeInfo;
                comp = obj->positionData->compCount;
                scale = 1 << (quant & 0xF);
                switch ((quant >> 4) & 0xF) {
                case GX_S16:
                    v = (s16*)obj->positionData->positionArray;
                    v += comp * posIdx;
                    x = v[0] / scale;
                    y = v[1] / scale;
                    z = v[2] / scale;
                    break;
                }
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
                GXWGFifo.u32 = 0xFF0000FF;
                quant = obj->lightingData->quantizeInfo;
                comp = obj->lightingData->compCount;
                scale = 1 << (quant & 0xF);
                switch ((quant >> 4) & 0xF) {
                case GX_S16:
                    v = (s16*)obj->lightingData->normalArray;
                    v += comp * nrmIdx;
                    x += v[0] / scale;
                    y += v[1] / scale;
                    z += v[2] / scale;
                    break;
                }
                GXWGFifo.f32 = x;
                GXWGFifo.f32 = y;
                GXWGFifo.f32 = z;
                GXWGFifo.u32 = 0x0000FFFF;
            }
        }
    }
}

// fn_1_6050, size:0x528
// Fills an IA8 (4x4-tiled) normal-map texture of a hemisphere, optionally bent towards sUpAxis by scale.
// NONMATCHING 97%: hoisted float constants land in rotated registers (f26-f31)
#if NONMATCHING
void fn_1_6050(u16* image, s32 width, s32 height, f32 scale) {
    Mtx rot;
    Vec normal;
    Vec flat;
    Vec axis;
    Quaternion quat;
    u32 size;
    s32 y;
    s32 x;
    f32 u;
    f32 v;
    f32 fy2;
    f32 fx;
    f32 fy;
    f32 baseU;
    f32 baseV;
    f32 d;
    f32 angle;
    f32 s;
    f32 mag;

    size = height * (width * 2);
    memset(image, 0, size);
    for (y = 0; y < height; y++) {
        fy = lbl_1_rodata_1C8 * ((f32)y / (f32)height - lbl_1_rodata_1CC);
        baseV = fy * lbl_1_rodata_1CC + lbl_1_rodata_1CC;
        fy2 = fy * fy;
        for (x = 0; x < width; x++) {
            fx = lbl_1_rodata_1C8 * ((f32)x / (f32)width - lbl_1_rodata_1CC);
            baseU = fx * lbl_1_rodata_1CC + lbl_1_rodata_1CC;
            if (y == height / 2) {
                d = lbl_1_rodata_1D8 - fx * fx;
            } else {
                d = lbl_1_rodata_1D8 - fx * fx - fy2;
            }
            if (d < lbl_1_rodata_1A8) {
                normal.x = fx;
                normal.y = fy;
                normal.z = lbl_1_rodata_1A8;
                PSVECNormalize(&normal, &normal);
            } else {
                f64 z = -sqrt(d);
                normal.x = fx;
                normal.y = fy;
                normal.z = z;
            }
            if (lbl_1_rodata_1D8 != scale) {
                PSVECCrossProduct(&lbl_1_data_A3C, &normal, &axis);
                mag = PSVECMag(&axis);
                if (mag != lbl_1_rodata_1A8) {
                    PSVECNormalize(&axis, &axis);
                    angle = acos(PSVECDotProduct(&lbl_1_data_A3C, &normal));
                    angle = angle * scale * lbl_1_rodata_1CC;
                    s = sin(angle);
                    quat.w = cos(angle);
                    quat.x = axis.x * s;
                    quat.y = axis.y * s;
                    quat.z = axis.z * s;
                    PSMTXQuat(rot, &quat);
                    PSMTXMultVec(rot, &lbl_1_data_A3C, &normal);
                }
            }
            flat.x = normal.x;
            flat.y = lbl_1_rodata_1A8;
            flat.z = normal.z;
            mag = PSVECMag(&flat);
            if (mag == lbl_1_rodata_1A8) {
                u = lbl_1_rodata_1A8;
                v = lbl_1_rodata_1A8;
            } else {
                PSVECNormalize(&flat, &flat);
                if (lbl_1_rodata_1A8 == fy) {
                    v = lbl_1_rodata_1CC;
                } else {
                    v = acos(PSVECDotProduct(&flat, &normal));
                    PSVECCrossProduct(&flat, &normal, &axis);
                    mag = PSVECMag(&axis);
                    if (mag == lbl_1_rodata_1A8) {
                        v = lbl_1_rodata_1A8;
                    } else if (axis.x < lbl_1_rodata_1A8) {
                        v = -v;
                    }
                    v = v / lbl_1_rodata_1DC + lbl_1_rodata_1CC;
                }
                if (lbl_1_rodata_1A8 == fx) {
                    u = lbl_1_rodata_1CC;
                } else {
                    u = acos(PSVECDotProduct(&lbl_1_data_A3C, &flat));
                    PSVECCrossProduct(&lbl_1_data_A3C, &flat, &axis);
                    mag = PSVECMag(&axis);
                    if (mag == lbl_1_rodata_1A8) {
                        u = lbl_1_rodata_1A8;
                    } else if (axis.y > lbl_1_rodata_1A8) {
                        u = -u;
                    }
                    u = u / lbl_1_rodata_1DC + lbl_1_rodata_1CC;
                }
                u -= baseU;
                v -= baseV;
            }
            image[(y / 4) * width * 4 + (x / 4) * 16 + (y % 4) * 4 + x % 4] =
                (((s32)(lbl_1_rodata_1E0 * u + lbl_1_rodata_1E0) << 8) & 0xFF00) | (u8)(s32)(lbl_1_rodata_1E0 * v + lbl_1_rodata_1E0);
        }
    }
    DCFlushRange(image, size);
}
#endif
