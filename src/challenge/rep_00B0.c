#include "challenge/rep_00B0.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "Dolphin/OS/OSCache.h"
#include "stl/math.h"
#include <string.h>

extern void OSReport(const char* msg, ...);
extern void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);

// Challenge-wide graphics state (shared with rep_0138, which accesses it by offset).
typedef struct ChalGfxState {
    /* 0x000 */ Mtx viewMtx;
    /* 0x030 */ u8 unk30[0x20C - 0x30];
    /* 0x20C */ GDLObj dl;
    /* 0x21C */ u8* dlBuf;
    /* 0x220 */ u32 dlSize;
    /* 0x224 */ ChalColModel* colModel;
    /* 0x228 */ s16 numBlocks;
    /* 0x22A */ u8 unk22A[0x22E - 0x22A];
    /* 0x22E */ s16 selBlock;
    /* 0x230 */ u8 unk230[0x239 - 0x230];
    /* 0x239 */ s8 showBox;
    /* 0x23A */ u8 unk23A[0x240 - 0x23A];
} ChalGfxState;

extern ChalGfxState lbl_1_common_bss_472B4;

// .data 0x200..0x298 (file statics; the split leaves them in the unsplit data section).
static Vec lbl_1_data_200[2] = {
    { 0.21f, -3.0f, 17.26f },
    { 0.21f, 3.0f, 17.26f },
}; // debug ray
static Vec lbl_1_data_218 = { 0.0f, 1.0f, 0.0f }; // up vector for the ray matrix
static Vec lbl_1_data_224 = { 0.0f, 0.0f, 0.0f }; // hit point in ray space
static u32 lbl_1_data_230[4] = { 0, 0, 0, 0 };
static GXColor lbl_1_data_240[21] = {
    { 0x00, 0xC0, 0x00, 0xFF }, { 0x00, 0x70, 0x00, 0xFF }, { 0x00, 0x00, 0xC0, 0xFF },
    { 0x00, 0x00, 0x70, 0xFF }, { 0xC0, 0x00, 0x00, 0xFF }, { 0x70, 0x00, 0x00, 0xFF },
    { 0xC0, 0xC0, 0x00, 0xFF }, { 0x70, 0x70, 0x00, 0xFF }, { 0x00, 0xC0, 0xC0, 0xFF },
    { 0x00, 0x70, 0x70, 0xFF }, { 0xC0, 0x00, 0xC0, 0xFF }, { 0x70, 0x00, 0x70, 0xFF },
    { 0xFF, 0x00, 0x00, 0x40 }, { 0x00, 0xFF, 0x00, 0x40 }, { 0xFF, 0xFF, 0x00, 0x40 },
    { 0x00, 0x00, 0xFF, 0x40 }, { 0xFF, 0x00, 0xFF, 0x40 }, { 0x00, 0xFF, 0xFF, 0x40 },
    { 0xC0, 0xC0, 0x20, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 0x3A, 0x6E, 0xA5, 0xFF },
}; // debug colors (GX_VA_CLR0 index array)
static GXColor lbl_1_data_294 = { 0x00, 0x00, 0x00, 0x00 }; // copy clear color

const f32 lbl_1_rodata_B0[20] = {
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
    1.0f, 1.5707964f, 1.0f, -1.0f, 4.712389f, 3.1415927f, -1.0f, 0.0f, -1.0f, 1.0f,
};

// Corners of the selected block's bounding box.
Vec lbl_1_bss_60[8];

#define CHAL_COLOR(id) (u8)(((u32)(id) >> 7) + (((u32)(id) & 0x7F) - 1) * 2)

// .text:0x000019AC size:0x24C
void fn_1_19AC(void) {
    Vec hit[2];
    u32 size;
    u32 i;
    ChalColBlock** blocks;

    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetCopyClear(lbl_1_data_294, 0xFFFFFF);
    GXSetCullMode(GX_CULL_FRONT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, lbl_1_data_240, 4);
    GXSetLineWidth(0x12, GX_TO_ONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXLoadPosMtxImm(lbl_1_common_bss_472B4.viewMtx, GX_PNMTX0);

    blocks = lbl_1_common_bss_472B4.colModel->blocks;
    GDInitGDLObj(&lbl_1_common_bss_472B4.dl, lbl_1_common_bss_472B4.dlBuf, 0x80000);
    __GDCurrentDL = &lbl_1_common_bss_472B4.dl;

    if (lbl_1_common_bss_472B4.selBlock < 0) {
        for (i = 0; i < lbl_1_common_bss_472B4.numBlocks; i++) {
            fn_1_25BC(*blocks++);
        }
        fn_1_4290(lbl_1_data_200);
    } else {
        fn_1_25BC(blocks[lbl_1_common_bss_472B4.selBlock]);
        fn_1_4290(lbl_1_data_200);
        if (lbl_1_common_bss_472B4.showBox) {
            fn_1_1BF8(lbl_1_common_bss_472B4.colModel->boxes, lbl_1_common_bss_472B4.selBlock);
        }
    }

    if (fn_1_4728(lbl_1_data_200, hit)) {
        PSVECAdd(&hit[0], &hit[1], &hit[1]);
        fn_1_4290(hit);
    }

    GDPadCurr32();
    size = lbl_1_common_bss_472B4.dl.ptr - lbl_1_common_bss_472B4.dl.start;
    DCFlushRangeNoSync(lbl_1_common_bss_472B4.dlBuf, size);
    lbl_1_common_bss_472B4.dlSize = size;
    if (size > 0x80000) {
        OSReport("Gd Buffer overflow:%d\n", size);
        while (1) {
        }
    }
    GXCallDisplayList(lbl_1_common_bss_472B4.dlBuf, size);
}

// .text:0x00001BF8 size:0x1C4
void fn_1_1BF8(ChalColBox* boxes, s32 index) {
    ChalColBox* box = &boxes[index];

    lbl_1_bss_60[0].x = box->min.x;
    lbl_1_bss_60[0].y = box->min.y;
    lbl_1_bss_60[0].z = box->max.z;
    lbl_1_bss_60[1].x = box->max.x;
    lbl_1_bss_60[1].y = box->min.y;
    lbl_1_bss_60[1].z = box->max.z;
    lbl_1_bss_60[2].x = box->max.x;
    lbl_1_bss_60[2].y = box->min.y;
    lbl_1_bss_60[2].z = box->min.z;
    lbl_1_bss_60[3].x = box->min.x;
    lbl_1_bss_60[3].y = box->min.y;
    lbl_1_bss_60[3].z = box->min.z;
    lbl_1_bss_60[4].x = box->min.x;
    lbl_1_bss_60[4].y = box->max.y;
    lbl_1_bss_60[4].z = box->max.z;
    lbl_1_bss_60[5].x = box->max.x;
    lbl_1_bss_60[5].y = box->max.y;
    lbl_1_bss_60[5].z = box->max.z;
    lbl_1_bss_60[6].x = box->max.x;
    lbl_1_bss_60[6].y = box->max.y;
    lbl_1_bss_60[6].z = box->min.z;
    lbl_1_bss_60[7].x = box->min.x;
    lbl_1_bss_60[7].y = box->max.y;
    lbl_1_bss_60[7].z = box->min.z;

    GDBegin(GX_QUADS, GX_VTXFMT0, 24);
    fn_1_1DBC(7, 6, 2, 3, 0xC);
    fn_1_1DBC(5, 4, 0, 1, 0xD);
    fn_1_1DBC(3, 2, 1, 0, 0xE);
    fn_1_1DBC(4, 5, 6, 7, 0xF);
    fn_1_1DBC(4, 7, 3, 0, 0x10);
    fn_1_1DBC(6, 5, 1, 2, 0x11);
}

// .text:0x00001DBC size:0x800
// NONMATCHING 99.9%: the (u8)color copy gets r29 instead of r31, and the y/z row pointers r30/r31 instead of r29/r30
#if NONMATCHING
void fn_1_1DBC(s32 a, s32 b, s32 c, s32 d, s8 color) {
    GDPosition3f32(lbl_1_bss_60[a].x, lbl_1_bss_60[a].y, lbl_1_bss_60[a].z);
    GDColor1x8(color);
    GDPosition3f32(lbl_1_bss_60[b].x, lbl_1_bss_60[b].y, lbl_1_bss_60[b].z);
    GDColor1x8(color);
    GDPosition3f32(lbl_1_bss_60[c].x, lbl_1_bss_60[c].y, lbl_1_bss_60[c].z);
    GDColor1x8(color);
    GDPosition3f32(lbl_1_bss_60[d].x, lbl_1_bss_60[d].y, lbl_1_bss_60[d].z);
    GDColor1x8(color);
}
#endif

// .text:0x000025BC size:0x187C
void fn_1_25BC(ChalColBlock* block) {
    return;
}

// .text:0x00003E38 size:0x23C
void fn_1_3E38(Vec* pos, u32 id) {
    GDPosition3f32(pos->x, pos->y, pos->z);
    GDColor1x8(CHAL_COLOR(id));
}

// .text:0x00004074 size:0x21C
void fn_1_4074(Vec* pos) {
    GDPosition3f32(pos->x, pos->y, pos->z);
    GDColor1x8(0x12);
}

// .text:0x00004290 size:0x498
void fn_1_4290(Vec* line) {
    GDBegin(GX_LINES, GX_VTXFMT0, 2);
    GDPosition3f32(line[0].x, line[0].y, line[0].z);
    GDColor1x8(0x13);
    GDPosition3f32(line[1].x, line[1].y, line[1].z);
    GDColor1x8(0x14);
}

#define SIGN_BITS(f) (*(s32*)&(f))

// .text:0x00004728 size:0x2FC
u32 fn_1_4728(Vec* ray, Vec* out) {
    Vec d[4];
    Mtx inv;
    ChalRayCast cast;
    u8 skip[256];
    ChalColBlock** blocks;
    s32 i;
    u32 allSkipped;
    ChalColBox* box;
    u8* flag;
    f32 len;

    box = lbl_1_common_bss_472B4.colModel->boxes;
    memset(skip, 1, lbl_1_common_bss_472B4.numBlocks);
    flag = skip;
    i = lbl_1_common_bss_472B4.numBlocks;
    allSkipped = 1;
    do {
        PSVECSubtract(&ray[0], &box->min, &d[0]);
        PSVECSubtract(&box->max, &ray[0], &d[1]);
        PSVECSubtract(&ray[1], &box->min, &d[2]);
        PSVECSubtract(&box->max, &ray[1], &d[3]);
        if (!(((SIGN_BITS(d[0].x) & SIGN_BITS(d[2].x)) | (SIGN_BITS(d[1].x) & SIGN_BITS(d[3].x))) & 0x80000000) &&
            !(((SIGN_BITS(d[0].y) & SIGN_BITS(d[2].y)) | (SIGN_BITS(d[1].y) & SIGN_BITS(d[3].y))) & 0x80000000) &&
            !(((SIGN_BITS(d[0].z) & SIGN_BITS(d[2].z)) | (SIGN_BITS(d[1].z) & SIGN_BITS(d[3].z))) & 0x80000000))
        {
            allSkipped = 0;
            *flag = 0;
        }
        i--;
        flag++;
        box++;
    } while (i != 0);

    if (allSkipped) {
        return 0;
    }

    makeLookAtMatrix(cast.mtx, &ray[0], &lbl_1_data_218, &ray[1]);
    len = dolsqrtf2(PSVECSquareDistance(&ray[1], &ray[0]));
    cast.length = len;
    cast.dist = len;
    cast.hitId = 0;

    flag = skip;
    i = lbl_1_common_bss_472B4.numBlocks;
    blocks = lbl_1_common_bss_472B4.colModel->blocks;
    do {
        if (*flag++ == 0) {
            fn_1_4A24(&cast, *blocks);
        }
        i--;
        blocks++;
    } while (i != 0);

    if (cast.hitId != 0) {
        PSMTXInverse(cast.mtx, inv);
        lbl_1_data_224.z = -cast.dist;
        PSMTXMultVec(inv, &lbl_1_data_224, &out[0]);
        PSMTXTranspose(cast.mtx, inv);
        PSMTXMultVec(inv, &cast.normal, &out[1]);
        PSVECNormalize(&out[1], &out[1]);
        return cast.hitId;
    }
    return 0;
}

// .text:0x00004A24 size:0x3B4
void fn_1_4A24(ChalRayCast* cast, ChalColBlock* block) {
    Vec p[3];
    Vec w[3];
    u8 isStrip;
    u32 count;
    u32 flip;
    ChalColVtx* v;
    u32 inside;
    f32 t;

    v = (ChalColVtx*)block;
    while (1) {
        count = ((ChalColBlock*)v)->hdr.h.count;
        if (count == 0) {
            break;
        }
        isStrip = ((ChalColBlock*)v)->hdr.h.isStrip;
        v = ((ChalColBlock*)v)->v;
        if (isStrip == 0) {
            do {
                PSMTXMultVec(cast->mtx, &v[0].pos, &p[0]);
                PSMTXMultVec(cast->mtx, &v[1].pos, &p[1]);
                PSMTXMultVec(cast->mtx, &v[2].pos, &p[2]);
                inside = (p[0].x * p[1].y - p[1].x * p[0].y >= 0.0f);
                inside &= (p[1].x * p[2].y - p[2].x * p[1].y >= 0.0f);
                inside &= (p[2].x * p[0].y - p[0].x * p[2].y >= 0.0f);
                if (inside) {
                    PSVECSubtract(&p[1], &p[0], &w[0]);
                    PSVECSubtract(&p[2], &p[1], &w[1]);
                    PSVECCrossProduct(&w[0], &w[1], &w[2]);
                    t = -PSVECDotProduct(&w[2], &p[0]) / w[2].z;
                    if (t >= 0.0f && cast->dist > t) {
                        cast->dist = t;
                        cast->hitId = v[2].id;
                        cast->normal = w[2];
                    }
                }
                v += 3;
            } while (--count != 0);
        } else {
            flip = 0;
            PSMTXMultVec(cast->mtx, &v[0].pos, &p[0]);
            PSMTXMultVec(cast->mtx, &v[1].pos, &p[1]);
            v += 2;
            do {
                PSMTXMultVec(cast->mtx, &v->pos, &p[2]);
                w[0].x = p[0].x * p[1].y - p[1].x * p[0].y;
                w[0].y = p[1].x * p[2].y - p[2].x * p[1].y;
                w[0].z = p[2].x * p[0].y - p[0].x * p[2].y;
                if (flip) {
                    inside = (w[0].z <= 0.0f) & ((w[0].x <= 0.0f) & (w[0].y <= 0.0f));
                } else {
                    inside = (w[0].z >= 0.0f) & ((w[0].x >= 0.0f) & (w[0].y >= 0.0f));
                }
                if (inside) {
                    PSVECSubtract(&p[1], &p[0], &w[0]);
                    PSVECSubtract(&p[2], &p[1], &w[1]);
                    PSVECCrossProduct(&w[0], &w[1], &w[2]);
                    t = -PSVECDotProduct(&w[2], &p[0]) / w[2].z;
                    if (t >= 0.0f && cast->dist > t) {
                        cast->dist = t;
                        cast->hitId = v->id;
                        if (!flip) {
                            cast->normal = w[2];
                        } else {
                            cast->normal.x = -w[2].x;
                            cast->normal.y = -w[2].y;
                            cast->normal.z = -w[2].z;
                        }
                    }
                }
                flip ^= 1;
                v++;
                p[0] = p[1];
                p[1] = p[2];
            } while (--count != 0);
        }
    }
}

