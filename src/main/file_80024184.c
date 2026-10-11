#include "main/file_80024184.h"
#include "Dolphin/os.h"
#include "Dolphin/mtxext.h"
#include "game/UnknownHomes_Game.h"
#include "static/UnknownHomes_Static.h"

// GX setup helpers ("sub.c") and small math/texture utilities.

extern const char lbl_803CC580[6]; // "sub.c"
extern char lbl_800E6720[]; // "gOz_GXSetTexture was called in thread that is not current GX thread.\n"
extern TexImage lbl_800F7700; // default texture
extern StarMissionIndex lbl_800E8558[];
extern StarMission lbl_80109AE8[][10];
extern u8 lbl_803CB748[6];
extern u8 lbl_8034E9A0[]; // TODO type
extern const f32 lbl_803CC598; // 0.5f
extern const f32 lbl_803CC59C; // 255.0f
extern const f32 lbl_803CC5A0; // 0.0f
extern const f32 lbl_803CC5A4; // 1.0f

// TODO: these belong in their own units' headers.
OSThread* GXGetCurrentGXThread(void);
void* fn_800ACF34(u32 align, u32 size);
void fn_800ACF14(void* p);
void* memcpy(void* dst, const void* src, u32 n);
void* memmove(void* dst, const void* src, u32 n);

// .text:0x80024184 size:0x20C
void gOz_GXSetTexture(void) {
    return;
}

// .text:0x80024390 size:0x74
void fn_80024390(void) {
    return;
}

// .text:0x80024404 size:0x1E8
void SetDisplayStateTexture(TexImage* tex, s32 map, u32 tlutName) {
    GXTexObj texObj;
    GXTlutObj tlutObj;
    s32 wrapS;
    s32 wrapT;

    if (OSGetCurrentThread() != GXGetCurrentGXThread()) {
        OSPanic(lbl_803CC580, 0x23E, lbl_800E6720);
    }
    if (tex == NULL) {
        tex = &lbl_800F7700;
    }
    // Repeat/mirror only work for power-of-two sizes.
    wrapS = tex->wrapS;
    if (wrapS != GX_CLAMP) {
        u32 bits = 0;
        u16 v = tex->width;
        while (v != 0) {
            bits += v & 1;
            v >>= 1;
        }
        if (bits > 1) {
            wrapS = GX_CLAMP;
        }
    }
    wrapT = tex->wrapT;
    if (wrapT != GX_CLAMP) {
        u16 v = tex->height;
        u32 bits = 0;
        while (v != 0) {
            bits += v & 1;
            v >>= 1;
        }
        if (bits > 1) {
            wrapT = GX_CLAMP;
        }
    }
    if (tex->tlut != NULL) {
        GXInitTexObjCI(&texObj, tex->data, tex->width, tex->height, tex->format, wrapS, wrapT, tex->minLOD != tex->maxLOD,
                       tlutName);
        GXInitTlutObj(&tlutObj, tex->tlut, tex->tlutFormat, tex->tlutEntries);
        GXLoadTlut(&tlutObj, tlutName);
    } else {
        GXInitTexObj(&texObj, tex->data, tex->width, tex->height, tex->format, wrapS, wrapT, tex->minLOD != tex->maxLOD);
    }
    GXInitTexObjLOD(&texObj, tex->minFilter, tex->magFilter, tex->minLOD, tex->maxLOD, tex->lodBias, GX_FALSE, GX_FALSE,
                    GX_ANISO_1);
    GXLoadTexObj(&texObj, map);
}

// .text:0x800245EC size:0xE8
void fn_800245EC(void) {
    return;
}

// .text:0x800246D4 size:0x110
void fn_800246D4(void) {
    return;
}

// .text:0x800247E4 size:0x5C
void fn_800247E4(void) {
    return;
}

// .text:0x80024840 size:0x134
void challengeStarRelatedInd(void) {
    return;
}

// Scale the byte b by a/255.
static inline s32 scaleByte(u32 b, u32 a) {
    return (s32)((s32)(b & 0xFF) * ((s32)(a & 0xFF) / lbl_803CC59C));
}

// .text:0x80024974 size:0x64
void multBottomBits_asFloat(void) {
    return;
}

// .text:0x800249D8 size:0x128
void byteWiseMultiply(void) {
    return;
}

// .text:0x80024B00 size:0xB4
void LERPToNewRange_Float(void) {
    return;
}

// .text:0x80024BB4 size:0x50
f32 LinearInterpolateToNewRange(f32 value, f32 prevMin, f32 prevMax, f32 nextMin, f32 nextMax) {
    f32 range = prevMax - prevMin;
    f32 t;
    f32 d;

    if (lbl_803CC5A0 == range) {
        t = lbl_803CC5A4;
    } else {
        f32 f = (value - prevMin) / range;
        t = f > lbl_803CC5A4 ? lbl_803CC5A4 : (f < lbl_803CC5A0 ? lbl_803CC5A0 : f);
    }
    d = nextMax - nextMin;
    return d * t + nextMin;
}

// .text:0x80024C04 size:0x68
void fn_80024C04(void) {
    return;
}

// .text:0x80024C6C size:0xC0
void fn_80024C6C(void) {
    return;
}
