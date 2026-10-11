#include "game/rep_1C0.h"
#include "header_rep_data.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "Dolphin/mtx.h"
#include "static/Camera.h"
#include "main/file_8000F150.h"
#pragma dont_inline on

typedef struct { u8 b[14]; } Tbl14;
extern u8 lbl_3_rodata_214[];
extern void CTRLBuildMatrix(void*, void*);
extern void DOVARender(void*, void*, int, int);
extern s32 fn_800B7D3C(void*, f32*, void*);
extern u8 lbl_803CBBC0;
extern StadiumDrawFn lbl_3_data_A10[];

extern u32 lbl_3_bss_18[];
extern f32 lbl_3_rodata_504;
extern f32 lbl_3_rodata_524;
extern f32 lbl_3_rodata_528;
extern f32 lbl_3_rodata_52C;
extern f32 lbl_3_rodata_530;
extern f32 lbl_3_rodata_520[];
extern f32 lbl_3_rodata_538[];
extern u8 g_UNK_StadiumDetails[];
extern u32 fn_80009028(void);
extern s32 fn_800527BC(void);
extern void fn_80052694(void*);
extern camera_803c639c_s* fn_80052734(s32);
extern s32 lbl_3_rodata_210;
extern void DCStoreRange(void*, u32);
extern void fn_80023F0C(void*, void*, int, int, int, int, int, int);

// .text:0x000035D4 size:0x10
u32 setFanObjPtr(void) {
    return lbl_3_bss_18[0];
}

// .text:0x000035E4 size:0xC
void fn_3_35E4(u32 val) {
    lbl_3_bss_18[0] = val;
}

// .text:0x000035F0 size:0x48
void fn_3_35F0(void) {
    if (fn_80009028() == 0) {
        GXSetCopyClear(*(GXColor*)(g_UNK_StadiumDetails + 0x76C), 0xFFFFFF);
    }
}

// .text:0x00003638 size:0x1E0
void fn_3_3638(u8* obj) {
    u8* e;
    u8* pA;
    u8* pB;
    s32 i;
    u8* hdr;
    u8* m26;
    u8* tbl;
    Mtx m;
    f32 pts[24];
    i = 0;
    pA = obj + 8;
    pB = obj + 0x38;
    hdr = *(u8**)(obj + 0x68);
    tbl = *(u8**)(hdr + 0x10);
    e = hdr;
    for (i = 0; i < *(u16*)(hdr + 6); e += 0x1C, i++) {
        u16 idx = *(u16*)(e + 0x34);
        if (idx != 0xFFFF) {
            m26 = *(u8**)(*(u8**)(tbl + 0x10) + idx * 8);
            CTRLBuildMatrix(*(void**)(e + 0x20), m26 + 0x18);
            PSMTXConcat((void*)pA, (void*)(m26 + 0x18), (void*)(m26 + 0x18));
            PSMTXConcat((void*)pB, (void*)(m26 + 0x18), m);
#define F(o) (*(f32*)(m26 + o))
            pts[0] = F(0x58); pts[1] = F(0x60); pts[2] = F(0x64);
            pts[3] = F(0x54); pts[4] = F(0x60); pts[5] = F(0x64);
            pts[6] = F(0x54); pts[7] = F(0x60); pts[8] = F(0x68);
            pts[9] = F(0x58); pts[10] = F(0x60); pts[11] = F(0x68);
            pts[12] = F(0x58); pts[13] = F(0x5C); pts[14] = F(0x64);
            pts[15] = F(0x54); pts[16] = F(0x5C); pts[17] = F(0x64);
            pts[18] = F(0x54); pts[19] = F(0x5C); pts[20] = F(0x68);
            pts[21] = F(0x58); pts[22] = F(0x5C); pts[23] = F(0x68);
            if (fn_800B7D3C(*(void**)(obj + 0x6C), pts, m)) {
                if (*(u16*)(e + 0x3A) & 1) {
                    GXSetZMode(1, 7, 1);
                } else {
                    GXSetZMode(1, 3, 1);
                }
                switch (*(u16*)(e + 0x3A) & 6) {
                case 2:
                    GXSetBlendMode(1, 1, 1, 0);
                    break;
                case 4:
                    GXSetBlendMode(1, 2, 0, 0);
                    break;
                default:
                    GXSetBlendMode(1, 4, 5, 0);
                    break;
                }
                DOVARender(m26, (void*)pB, 0, 0);
            }
        }
    }
}

// .text:0x00003818 size:0xD0
void fn_3_3818(void) {
    s32 i;
    if (lbl_3_data_A10[lbl_803CBBC0 == 0] != NULL) {
        i = fn_800527BC() - 1;
        do {
            fn_80052694((void*)i); // TODO type: takes the camera index (s32)
            lbl_3_data_A10[lbl_803CBBC0 == 0](fn_80052734(i)->view, 0, 0);
        } while (i-- != 0);
        lbl_3_data_A10[lbl_803CBBC0 == 0] = NULL;
    }
}

// .text:0x000038E8 size:0x1C
void fn_3_38E8(StadiumDrawFn a) {
    lbl_3_data_A10[lbl_803CBBC0] = a;
}

#pragma dont_inline off
// Glyph codes: wide glyphs (bit 0x8000) are 22x22 cells on a 46-column grid
// spread over font pages; narrow ones are 11x22 cells on page 0.
static inline void DecodeWideGlyph(u16 v, s16* x, s16* y, s16* w, s16* h, s16* page) {
    u16 i = v & 0x7FFF;
    *page = i / 2116;
    i = i % 2116;
    *x = i % 46;
    *y = (i / 46) * 22;
    *x = *x * 22;
    *w = 22;
    *h = 22;
}

static inline void DecodeNarrowGlyph(u16 v, s16* x, s16* y, s16* w, s16* h, s16* page) {
    *x = v % 92;
    *y = (v / 92) * 22;
    *x = (*x % 2 + (*x / 2) * 2) * 11;
    *w = 11;
    *h = 22;
    *page = 0;
}

extern const f32 lbl_3_rodata_4F8; // 16.0f
extern const f32 lbl_3_rodata_4FC; // 18.0f
extern const f32 lbl_3_rodata_500; // 8.0f

// Draws message `msg` of the first message table with the font glyphs at
// (x, y). Control codes: 0 ends, 1 is a newline, 2/3 are half/full spaces.
// .text:0x00003904 size:0x2E4 mapped:0x80642998
// NONMATCHING 86%: scheduling of the inlined wide-glyph decode (i kept in r0 in the original)
#if NONMATCHING
void fn_3_3904(s16 x, s16 y, s32 msg, GXColor* color0, GXColor* color1, u8 flags) {
    GXTexObj tex;
    s16 sx;
    s16 sy;
    s16 sw;
    s16 sh;
    u16* text;
    s16 startX;
    u16 c;
    s16 page;
    f32 advance;
    f32 height;

    startX = x;
    text = lbl_80366B18.tables[0]->msgs[msg];

    for (;;) {
        c = *text++;
        if (c & 0x4000) {
            switch (c & 0x3FFF) {
            case 0:
                return;
            case 2:
                x += 11;
                break;
            case 3:
                x += 22;
                break;
            case 1:
                x = startX;
                y += 22;
                break;
            }
            continue;
        }
        if (c & 0x8000) {
            DecodeWideGlyph(c, &sx, &sy, &sw, &sh, &page);
            advance = lbl_3_rodata_4F8;
            height = lbl_3_rodata_4FC;
        } else {
            DecodeNarrowGlyph(c, &sx, &sy, &sw, &sh, &page);
            advance = lbl_3_rodata_500;
            height = lbl_3_rodata_4FC;
        }
        GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        fn_3_42CC(&tex, x, y, x + advance, y + height, sx, sy, sw, sh, *color0, *color1, flags & 1);
        x += advance;
    }
}
#endif

// .text:0x00003BE8 size:0x300 mapped:0x80642C7C
void fn_3_3BE8(void) {
    return;
}

// .text:0x00003EE8 size:0x3E4 mapped:0x80642F7C
void fn_3_3EE8(void) {
    return;
}

// Draws one font glyph: a quad in color0/color1 one pixel larger than the
// glyph (the outline), then the glyph texel rect (sx, sy, sw, sh) on top.
// Bit 0 of flags inverts the glyph.
// .text:0x000042CC size:0x6B8 mapped:0x80643360
// NONMATCHING 99.8%: r0/r5/r11 allocation of the sx/sw/sy/sh int->float temps, f25/f27 swap
#if NONMATCHING
void fn_3_42CC(GXTexObj* tex, s16 x0, s16 y0, s16 x1, s16 y1, s16 sx, s16 sy, s16 sw, s16 sh,
               GXColor color0, GXColor color1, u8 flags) {
    f32 left = x0;
    f32 top = y0;
    f32 right = x1;
    f32 bottom = y1;
    u32 texW = GXGetTexObjWidth(tex);
    u16 texH = GXGetTexObjHeight(tex);
    f32 u0;
    f32 v0;
    f32 u1;
    f32 v1;
    s32 invert;

    u1 = (f32)(sx + sw) / (f32)(u16)texW;
    v0 = (f32)sy / (f32)texH;
    u0 = (f32)sx / (f32)(u16)texW;
    v1 = (f32)(sy + sh) / (f32)texH;

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevColor(GX_TEVREG0, color0);
    GXSetTevColor(GX_TEVREG1, color1);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    invert = flags & 1;
    if (!invert) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0, GX_CC_C1);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_C0, GX_CC_C1);
    }
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        f32 ot = top - 1.0f;
        f32 ol = left - 1.0f;
        f32 or = 1.0f + right;
        f32 ob = 1.0f + bottom;
        GXWGFifo.f32 = ol;
        GXWGFifo.f32 = ot;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = or;
        GXWGFifo.f32 = ot;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = or;
        GXWGFifo.f32 = ob;
        GXWGFifo.f32 = -0.5f;
        GXWGFifo.f32 = ol;
        GXWGFifo.f32 = ob;
        GXWGFifo.f32 = -0.5f;
    }

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(2);
    if (invert == 0) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C0, GX_CC_C1);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_TEXA, GX_CC_ONE);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C0, GX_CC_C1);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    }
    GXLoadTexObj(tex, GX_TEXMAP0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_OR);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u0;
    GXWGFifo.f32 = v0;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = top;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u1;
    GXWGFifo.f32 = v0;
    GXWGFifo.f32 = right;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u1;
    GXWGFifo.f32 = v1;
    GXWGFifo.f32 = left;
    GXWGFifo.f32 = bottom;
    GXWGFifo.f32 = -0.5f;
    GXWGFifo.f32 = u0;
    GXWGFifo.f32 = v1;
}
#endif

// .text:0x00004984 size:0xB4 mapped:0x80643A18
void fn_3_4984(void) {
    Mtx mtx;
    Mtx44 proj;
    GXSetZMode(1, 7, 1);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    C_MTXOrtho(proj, lbl_3_rodata_504, lbl_3_rodata_524, lbl_3_rodata_504, lbl_3_rodata_528, lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(proj, 1);
    GXSetCullMode(0);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
}

// .text:0x00004A38 size:0x558 mapped:0x80643ACC
void fn_3_4A38(u8 a) {
    return;
}

// .text:0x00004F90 size:0x450 mapped:0x80644024
void fn_3_4F90(void) {
    return;
}


// .text:0x000053E0 size:0x138 mapped:0x80644474
void fn_3_53E0(u16* in, s16* x, s16* y, s16* w, s16* h, s16* page) {
    u16 v = *in;
    if (!(v & 0x4000)) {
        if (v & 0x8000) {
            DecodeWideGlyph(v, x, y, w, h, page);
        } else {
            DecodeNarrowGlyph(v, x, y, w, h, page);
        }
    }
}

// .text:0x00005518 size:0x164 mapped:0x806445AC
// near-match (6 lines): saved reg assignment sd/off swapped
void fn_3_5518(void) {
    u8* sd;
    s16 tbl[7];
    Mtx44 proj;
    Mtx mtx;
    s32 off;
    void* tex;
    *(Tbl14*)tbl = *(Tbl14*)lbl_3_rodata_214;
    sd = *(u8**)g_UNK_StadiumDetails;
    off = tbl[g_d_GameSettings.StadiumID] << 5;
    GXSetZMode(1, 7, 1);
    GXSetScissor(0, 0, 0x280, 0x1C0);
    C_MTXOrtho(proj, lbl_3_rodata_504, lbl_3_rodata_524, lbl_3_rodata_504, lbl_3_rodata_528, lbl_3_rodata_52C, lbl_3_rodata_530);
    GXSetProjection(proj, 1);
    GXSetCullMode(0);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    GXSetTexCopySrc(0, 0, 0x200, 0x1E0);
    GXSetTexCopyDst(0x200, 0x1E0, 0x20, 0);
    fn_3_4A38(g_d_GameSettings.StadiumID);
    tex = *(void**)(sd + off);
    GXDrawDone();
    GXCopyTex(tex, 1);
    GXPixModeSync();
}

// .text:0x0000567C size:0x530 mapped:0x80644710
void fn_3_567C(void) {
    return;
}

// .text:0x00005BAC size:0x20 mapped:0x80644C40
void fn_3_5BAC(void) {
    fn_3_567C();
}

// .text:0x00005BCC size:0x24 mapped:0x80644C60

void fn_3_5BCC(u8* p) {
    fn_80052694(*(void**)(p + 8));
}

// .text:0x00005BF0 size:0x78 mapped:0x80644C84
void fn_3_5BF0(void) {
    s32 col;
    u8* d = g_UNK_StadiumDetails;
    if (lbl_3_bss_18[0] != 0) {
        ((void (*)(void))lbl_3_bss_18[0])();
    }
    col = *(s32*)(d + 0x714);
    SetFog(d[0x717], (GXColor *)&col, *(f32*)(d + 0x718), *(f32*)(d + 0x71C), lbl_3_rodata_520[0], lbl_3_rodata_538[0]); // TODO type
}

// .text:0x00005C68 size:0x1F8 mapped:0x80644CFC
void fn_3_5C68(u8* obj) {
    s32 col;
    u8* p;
    s32 i;
    s32 k;
    s32 cnt;
    GXSetCullMode(2);
    col = lbl_3_rodata_210;
    SetFog(0, (GXColor *)&col, lbl_3_rodata_504, lbl_3_rodata_504, lbl_3_rodata_504, lbl_3_rodata_504); // TODO type
    GXSetBlendMode(1, 4, 5, 0);
    k = 2;
    while (k-- != 0) {
        p = *(u8**)(obj + 8 + k * 4);
        if (p != NULL) {
            cnt = 0;
            for (i = 0; i < *(u16*)(p + 0x14); i++) {
                u8* st = *(u8**)(p + 0x10);
                if (st[(i * 3) + 2]-- == 0) {
                    u8* e;
                    s32 m;
                    u8* t;
                    s32 x, y, ax, ay; u8* tb;
                    u8* st2 = *(u8**)(p + 0x10);
                    st2[(i * 3) + 1] = (st2[(i * 3) + 1] + 1) % *(u16*)(p + 0x18);
                    ay = (i / 8) << 6;
                    ax = (i % 8) << 5;
                    e = *(u8**)(p + 0x10) + (i * 3);
                    m = (*(u8**)(p + 0xC))[e[1]];
                    if (k != 0) {
                        tb = *(u8**)(p + 8);
                        x = tb[e[0] * 4 + m * 2] << 5;
                        y = tb[e[0] * 4 + m * 2 + 1] << 6;
                    } else {
                        tb = *(u8**)(p + 8);
                        x = tb[e[0] * 8 + m * 2] << 5;
                        y = tb[e[0] * 8 + m * 2 + 1] << 6;
                    }
                    fn_80023F0C(*(void**)p, *(void**)(p + 4), x, y, 0x20, 0x40, ax, ay);
                    cnt++;
                    (*(u8**)(p + 0x10))[(i * 3) + 2] = *(u16*)(p + 0x16);
                }
            }
            if (cnt != 0) {
                u8* tex = *(u8**)(p + 4);
                DCStoreRange(*(void**)tex, *(u16*)(tex + 0xA) * *(u16*)(tex + 8));
            }
        }
    }
    if (lbl_3_bss_18[0] != 0) {
        ((void (*)(void))lbl_3_bss_18[0])();
    }
    GXSetZCompLoc(0);
}


extern u8 lbl_8036E548[];
extern void fn_80035CA4(int);
extern void fn_800BCDBC(void*);
extern void fn_800ACFB0(void*);

// .text:0x00005E60 size:0x60
void fn_3_5E60(void) {
    u8* b = lbl_8036E548;
    u8* p = *(u8**)(b + 4);
    fn_80035CA4(5);
    fn_800BCDBC(p + *(s32*)(p + 0x10));
    fn_800BCDBC(p + *(s32*)(p + 0xC));
    fn_800ACFB0(*(void**)(b + 4));
}

extern u8 lbl_3_data_7EC[];
// .text:0x000064DC size:0x54
void fn_3_64DC(void) {
    ARAMTransfer(lbl_3_data_7EC + (g_d_GameSettings.miniGameStadiumIndicator + g_d_GameSettings.StadiumID * 3) * 16, 0, 0, 0);
}

// .text:0x00006424 size:0xB8
// near-match: prologue register allocation (r5/r0/r6) differs
s16 fn_3_6424(u8* base, u8** out) {
    s16 n = *(u16*)base;
    u32* p;
    s32 i;
    p = (u32*)(*out = base + 4);
    for (i = n; i >= 0; i--) {
        *p += (u32)base;
        p++;
    }
    return n;
}
