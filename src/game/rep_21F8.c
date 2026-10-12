#include "game/rep_21F8.h"
#define REP_HEADER_FN repHeader_21F8
#include "header_rep_inline.h"
#include "Dolphin/mtx.h"
#include "Dolphin/GX/GXPixel.h"

extern f32 fn_3_BFDA4(void*, s32, f32, s32, u8, u8*);

typedef struct {
    f32 f[12];
} M12;
extern const M12 lbl_3_rodata_2248;
extern f32 lbl_3_rodata_2278;
extern f32 lbl_3_rodata_227C;
extern f32 lbl_3_rodata_2280;
// .bss (laid out last-defined-first)
static u8 lbl_3_bss_9F35[0x3]; // unused (alignment gap in the original)
u8 lbl_3_bss_9F34;
u8 lbl_3_bss_9F20[0x14];
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
// Effect description: 8 curves (scale x/y, ..., rotation Y/Z, alpha), see fn_3_C9590.
typedef struct FxCurveSet {
    /*0x00*/ f32 _00[4];
    /*0x10*/ u32 _10;
    /*0x14*/ FxCurveKey* curves[8];
    /*0x34*/ u8 counts[8];
    /*0x3C*/ u8 cur[8]; // current key of each curve
} FxCurveSet;
typedef struct E21F8 {
    /*0x00*/ FxCurveSet* set;
    /*0x04*/ void* tex;
    /*0x08*/ s32 _08;
    /*0x0C*/ s32 _0C;
    /*0x10*/ f32 _10;
    /*0x14*/ f32 time;
} E21F8;
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
static FxCurveSet lbl_3_data_17AC0 = {
    {-1.0f, -0.5f, 1.0f, 1.0f},
    0,
    {lbl_3_data_17898, lbl_3_data_178B0, lbl_3_data_17910, NULL, NULL, lbl_3_data_17A00, lbl_3_data_17940, lbl_3_data_17A54},
    {2, 3, 2, 0, 0, 1, 1, 3},
    {0, 0, 0, 0, 0, 0, 0, 0},
};
static E21F8 lbl_3_data_17B04[5] = {
    {&lbl_3_data_17AC0, NULL, 0x11, 1, 16.0f, 0.0f},
    {&lbl_3_data_17AC0, NULL, 0x11, 1, 16.0f, 0.0f},
    {&lbl_3_data_17AC0, NULL, 0x12, 1, 16.0f, 0.0f},
    {&lbl_3_data_17AC0, NULL, 0x12, 1, 16.0f, 0.0f},
    {NULL, NULL, 0, 0, 0.0f, 0.0f},
};
u32 lbl_3_data_17B7C = 0xFF;
static u8 lbl_3_data_17B80 = 1;       // depth test on while drawing
static f32 lbl_3_data_17B84[4] = {4.0f, 2.0f, 1.0f, 0.9f}; // scale per logo
f32 lbl_3_data_17B94 = 0.0f;
extern u8 lbl_3_common_bss_35154[];
extern void fn_80034120(Mtx);
extern void fn_3_BF8F8(void*, Mtx, void*, void*);
extern void fn_3_C9590(u8*, s32, f32*, f32);

// .text:0x000C937C size:0x214 mapped:0x80708410
int fn_3_C937C(void) {
    u8* b = lbl_3_bss_9F20;
    Mtx sm;
    s32 i;
    M12 id = lbl_3_rodata_2248;
    Mtx a;
    f32 sc;
    f32 t;
    switch (b[0x14]) {
    case 0:
        b[0x14] = 1;
        *(f32*)(b + 0x10) = lbl_3_rodata_2278;
    case 1:
        t = *(f32*)(b + 0x10) + lbl_3_rodata_227C;
        *(f32*)(b + 0x10) = t;
        if (t >= lbl_3_rodata_2280) {
            b[0x14] = 2;
        }
        break;
    }
    fn_80034120(a);
    PSMTXConcat(a, (f32(*)[4])&id, a);
    sc = lbl_3_data_17B84[b[0]];
    PSMTXScale(sm, sc, sc, sc);
    PSMTXConcat(a, sm, a);
    i = b[0];
    lbl_3_data_17B04[i].time = *(f32*)(b + 0x10);
    lbl_3_data_17B04[i].tex = lbl_3_common_bss_35154 + 4;
    if (lbl_3_data_17B80 != 0) {
        GXSetZMode(1, 7, 1);
    }
    GXSetBlendMode(1, 4, 6, 0);
    fn_3_BF8F8(&lbl_3_data_17B04[b[0]], a, b + 4, fn_3_C9590);
    if (lbl_3_data_17B80 != 0) {
        GXSetZMode(1, 3, 1);
    }
    GXSetBlendMode(1, 4, 5, 0);
    return b[0x14] == 2;
}

// .text:0x000C9590 size:0x1A4 mapped:0x80708624
void fn_3_C9590(u8* o, s32 k, f32* m, f32 t) {
    Mtx tmp;
    f32 v;
    PSMTXIdentity((f32(*)[4])m);
    m[0] = fn_3_BFDA4(*(void**)(o + 0x14), o[0x34], t, k, o[0x3C], o + 0x3C);
    m[5] = fn_3_BFDA4(*(void**)(o + 0x18), o[0x35], t, k, o[0x3D], o + 0x3D);
    if (*(void**)(o + 0x1C) != NULL) {
        v = fn_3_BFDA4(*(void**)(o + 0x1C), o[0x36], t, k, o[0x3E], o + 0x3E);
    } else {
        v = 0.0f;
    }
    m[3] = v;
    if (*(void**)(o + 0x28) != NULL) {
        v = fn_3_BFDA4(*(void**)(o + 0x28), o[0x39], t, k, o[0x41], o + 0x41);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Y', v);
        PSMTXConcat(tmp, (f32(*)[4])m, (f32(*)[4])m);
    }
    if (*(void**)(o + 0x2C) != NULL) {
        v = fn_3_BFDA4(*(void**)(o + 0x2C), o[0x3A], t, k, o[0x42], o + 0x42);
    } else {
        v = 0.0f;
    }
    if (v) {
        PSMTXRotRad(tmp, 'Z', v);
        PSMTXConcat(tmp, (f32(*)[4])m, (f32(*)[4])m);
    }
    fn_3_BFDA4(*(void**)(o + 0x30), o[0x3B], t, k, o[0x43], o + 0x43);
}


// .text:0x000C9734 size:0x10
void fn_3_C9734(void) {
    lbl_3_bss_9F34 = 2;
}
