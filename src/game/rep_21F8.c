#include "game/rep_21F8.h"
#define REP_HEADER_FN repHeader_21F8
#include "header_rep_inline.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXPixel.h"
#include "game/rep_1E08.h" // SprAnim, SprAnimElem, fn_3_BF8F8, fn_3_BFDA4


typedef struct {
    f32 f[12];
} M12;
// .bss (laid out last-defined-first)
static u8 lbl_3_bss_9F34; // 0: start, 1: running, 2: done
static Rep21F8Logo lbl_3_bss_9F20;
// .data lbl_3_data_17898..17B98: the stadium-intro logo effect. Separate initialized statics
// that the code reaches through one pooled base (CW keeps .data in definition order).
// Keyframe of an effect curve, read by fn_3_BFDA4 (same layout as BFDA4Key in rep_1E08.c).
typedef struct FxCurveKey {
    f32 v;
    f32 t;
    u16 mode : 4;
    u16 time : 12;
    u8 a;
    u8 b;
} FxCurveKey;
// Effect description (SprAnimElem, game/rep_1E08.h): 8 curves (scale x/y, ..., rotation Y/Z, alpha), see fn_3_C9590.
static FxCurveKey lbl_3_data_17898[2] = {
    {1.0f, 0.5f, 1, 0, 1, 1},
    {2.0f, 0.0f, 0, 14, 0, 0},
};
static FxCurveKey lbl_3_data_178B0[8] = {
    {1.0f, 1.0f, 1, 0, 1, 1},
    {2.0f, 1.8f, 1, 2, 0, 1},
    {0.2f, 0.0f, 0, 14, 0, 0},
    {1.0f, 0.5f, 1, 0, 1, 1},
    {2.0f, 0.0f, 0, 16, 0, 0},
    {1.0f, 1.0f, 1, 0, 1, 1},
    {2.0f, 1.8f, 1, 2, 0, 1},
    {0.2f, 0.0f, 0, 16, 0, 0},
};
static FxCurveKey lbl_3_data_17910[4] = {
    {0.0f, 2.0f, 1, 0, 0, 1},
    {-2.0f, 0.0f, 0, 10, 0, 0},
    {0.0f, 2.0f, 1, 0, 0, 1},
    {-2.0f, 0.0f, 0, 12, 0, 0},
};
static FxCurveKey lbl_3_data_17940[16] = {
    {0.31415927f, 0.0f, 0, 0, 0, 0},
    {1.8849558f, 0.0f, 0, 0, 0, 0},
    {3.4557521f, 0.0f, 0, 0, 0, 0},
    {5.0265484f, 0.0f, 0, 0, 0, 0},
    {1.2566371f, 0.0f, 0, 0, 0, 0},
    {2.8274336f, 0.0f, 0, 0, 0, 0},
    {4.3982296f, 0.0f, 0, 0, 0, 0},
    {5.969026f, 0.0f, 0, 0, 0, 0},
    {0.9424779f, 0.0f, 0, 0, 0, 0},
    {2.5132742f, 0.0f, 0, 0, 0, 0},
    {4.0840707f, 0.0f, 0, 0, 0, 0},
    {5.654867f, 0.0f, 0, 0, 0, 0},
    {1.5707964f, 0.0f, 0, 0, 0, 0},
    {3.1415927f, 0.0f, 0, 0, 0, 0},
    {4.712389f, 0.0f, 0, 0, 0, 0},
    {6.2831855f, 0.0f, 0, 0, 0, 0},
};
static FxCurveKey lbl_3_data_17A00[7] = {
    {0.62831855f, 0.0f, 0, 0, 0, 0},
    {0.5654867f, 0.0f, 0, 0, 0, 0},
    {-0.5654867f, 0.0f, 0, 0, 0, 0},
    {-0.62831855f, 0.0f, 0, 0, 0, 0},
    {1.0f, 0.0f, 0, 0, 0, 0},
    {1.0f, 1.0f, 1, 10, 0, 1},
    {0.0f, 0.0f, 0, 14, 0, 0},
};
static FxCurveKey lbl_3_data_17A54[9] = {
    {1.0f, 0.0f, 0, 0, 0, 0},
    {1.0f, 1.0f, 1, 12, 0, 1},
    {0.0f, 0.0f, 0, 16, 0, 0},
    {1.0f, 0.2f, 1, 0, 0, 1},
    {0.4f, 0.0f, 0, 16, 0, 0},
    {3.0f, 2.0f, 1, 0, 0, 1},
    {5.0f, 0.0f, 0, 16, 0, 0},
    {1.0f, 1.0f, 1, 0, 0, 1},
    {0.0f, 0.0f, 0, 16, 0, 0},
};
static SprAnimElem lbl_3_data_17AC0 = {
    -1.0f, -0.5f, 1.0f, 1.0f,
    0, 0,
    {lbl_3_data_17898, lbl_3_data_178B0, lbl_3_data_17910, NULL, NULL, lbl_3_data_17A00, lbl_3_data_17940, lbl_3_data_17A54},
    {2, 3, 2, 0, 0, 1, 1, 3},
    {0, 0, 0, 0, 0, 0, 0, 0},
};
static SprAnim lbl_3_data_17B04[5] = { // the four logos (_0C: 1)
    {&lbl_3_data_17AC0, NULL, 0x11, {0, 0, 0, 1}, 16.0f, 0.0f},
    {&lbl_3_data_17AC0, NULL, 0x11, {0, 0, 0, 1}, 16.0f, 0.0f},
    {&lbl_3_data_17AC0, NULL, 0x12, {0, 0, 0, 1}, 16.0f, 0.0f},
    {&lbl_3_data_17AC0, NULL, 0x12, {0, 0, 0, 1}, 16.0f, 0.0f},
    {NULL, NULL, 0, {0, 0, 0, 0}, 0.0f, 0.0f},
};
u32 lbl_3_data_17B7C = 0xFF;
static u8 lbl_3_data_17B80 = 1;       // depth test on while drawing
static f32 lbl_3_data_17B84[5] = {4.0f, 2.0f, 1.0f, 0.9f, 0.0f}; // scale per logo (last entry unused)
extern Rep21F8Bss35154 lbl_3_common_bss_35154;
extern void fn_80034120(Mtx);

// .text:0x000C9734 size:0x10
void fn_3_C9734(void) {
    lbl_3_bss_9F34 = 2;
}

// .text:0x000C9590 size:0x1A4 mapped:0x80708624
f32 fn_3_C9590(SprAnimElem* o, s32 k, MtxPtr m, f32 t) {
    Mtx tmp;
    f32 v;
    PSMTXIdentity(m);
    m[0][0] = fn_3_BFDA4(o->ch[0], o->chMode[0], t, k, o->chState[0], &o->chState[0]);
    m[1][1] = fn_3_BFDA4(o->ch[1], o->chMode[1], t, k, o->chState[1], &o->chState[1]);
    if (o->ch[2] != NULL) {
        v = fn_3_BFDA4(o->ch[2], o->chMode[2], t, k, o->chState[2], &o->chState[2]);
    } else {
        v = 0.0f;
    }
    m[0][3] = v;
    if (o->ch[5] != NULL) {
        v = fn_3_BFDA4(o->ch[5], o->chMode[5], t, k, o->chState[5], &o->chState[5]);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Y', v);
        PSMTXConcat(tmp, m, m);
    }
    if (o->ch[6] != NULL) {
        v = fn_3_BFDA4(o->ch[6], o->chMode[6], t, k, o->chState[6], &o->chState[6]);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Z', v);
        PSMTXConcat(tmp, m, m);
    }
    return fn_3_BFDA4(o->ch[7], o->chMode[7], t, k, o->chState[7], &o->chState[7]);
}

// .text:0x000C937C size:0x214 mapped:0x80708410
int fn_3_C937C(void) {
    Rep21F8Logo* b = &lbl_3_bss_9F20;
    // TODO type: this is *state, the bss object right after lbl_3_bss_9F20; the original
    // reaches it through lbl_3_bss_9F20's address (naming it directly changes the codegen).
    u8* state = (u8*)(b + 1);
    Mtx sm;
    s32 i;
    M12 id = {{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}};
    Mtx a;
    f32 sc;
    switch (*state) {
    case 0:
        *state = 1;
        b->time = 0.0f;
    case 1:
        b->time += 1.0f;
        if (b->time >= 16.0f) {
            *state = 2;
        }
        break;
    }
    fn_80034120(a);
    PSMTXConcat(a, (f32(*)[4])&id, a);
    sc = lbl_3_data_17B84[b->logo];
    PSMTXScale(sm, sc, sc, sc);
    PSMTXConcat(a, sm, a);
    i = b->logo;
    lbl_3_data_17B04[i]._14 = b->time; // animation time
    lbl_3_data_17B04[i].textures = &lbl_3_common_bss_35154.tex;
    if (lbl_3_data_17B80 != 0) {
        GXSetZMode(1, 7, 1);
    }
    GXSetBlendMode(1, 4, 6, 0);
    fn_3_BF8F8(&lbl_3_data_17B04[b->logo], a, b->pos, fn_3_C9590);
    if (lbl_3_data_17B80 != 0) {
        GXSetZMode(1, 3, 1);
    }
    GXSetBlendMode(1, 4, 5, 0);
    return *state == 2;
}
