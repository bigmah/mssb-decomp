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
void gOz_GXSetTexture(GXTevMode tevMode, s32 texFrac, s32 hasNormal) {
    if (OSGetCurrentThread() != GXGetCurrentGXThread()) {
        OSPanic(lbl_803CC580, 0x2A2, lbl_800E6720);
    }
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
        if (texFrac < 0) {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        } else {
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, (u8)texFrac);
        }
        break;
    }
    GXSetTevOrder(GX_TEVSTAGE0, tevMode == GX_PASSCLR ? GX_TEXCOORD_NULL : GX_TEXCOORD0,
                  tevMode == GX_PASSCLR ? GX_TEXMAP_NULL : GX_TEXMAP0, tevMode == GX_REPLACE ? GX_COLOR_NULL : GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    // 1 is the SDK GX_TG_MTX2x4 (GXEnum.h has the 2x4/3x4 names swapped)
    GXSetTexCoordGen2(GX_TEXCOORD0, (GXTexGenType)1, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(tevMode != GX_REPLACE);
    GXSetNumTexGens(tevMode != GX_PASSCLR);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, tevMode);
}

// .text:0x80024390 size:0x74
// NONMATCHING 77%: index `which ? 3 : 2` built with subfic instead of the original cntlzw/extrwi/neg sequence
#if NONMATCHING
void fn_80024390(f32* src, f32* out, s32 which) {
    s32 i = which ? 3 : 2;


    out[0] = which;
    out[1] = src[0];
    out[2] = src[i];
    out[3] = src[5];
    out[4] = src[i + 4];
    out[5] = src[10];
    out[6] = src[11];
}
#endif

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
// Project `count` points to normalized [0,1] screen coordinates.
// NONMATCHING 99%: f0/f1 swapped in the y-coordinate fmuls
#if NONMATCHING
void fn_800245EC(Mtx44 proj, Mtx view, Vec* points, f32* out, s32 count, s32 ySign) {
    Vec p;
    Mtx44 m;

    PSMTX44Identity(m);
    PSMTXCopy(view, m);
    PSMTX44Concat(proj, m, m);
    while (count-- != 0) {
        PSMTX44MultVec(m, points, &p);
        points++;
        out[0] = lbl_803CC598 * p.x + lbl_803CC598;
        out[1] = -ySign * (lbl_803CC598 * p.y) + lbl_803CC598;
        out += 2;
    }
}
#endif

// .text:0x800246D4 size:0x110
// Sort `count` elements of `size` bytes from src into dst (binary insertion sort, stable).
// NONMATCHING 98%: saved-register assignment differs; same instructions
#if NONMATCHING
void fn_800246D4(s32 (*compare)(void* key, void* elem), u8* src, u8* dst, s32 size, s32 count) {
    s32 mid;
    s32 rest;
    s32 cmp;
    s32 hi;
    s32 lo;
    u8* buf;
    s32 total;
    s32 n;
    s32 off;
    s32 i;

    total = size * count;
    buf = fn_800ACF34(0x20, total);
    i = count;
    n = 0;

    while (i-- != 0) {
        hi = n;
        lo = 0;
        while (lo != hi) {
            mid = lo + (hi - lo) / 2;
            cmp = compare(src, buf + mid * size);
            if (cmp == 0) {
                lo = mid;
                break;
            }
            if (cmp < 0) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        off = lo * size;
        rest = n - lo;
        if (rest != 0) {
            memmove(buf + off + size, buf + off, rest * size);
        }
        memcpy(buf + off, src, size);
        src += size;
        n++;
    }
    memcpy(dst, buf, total);
    fn_800ACF14(buf);
}
#endif

// .text:0x800247E4 size:0x5C
// Byte offset of texel (x, y) in a texture of 4x4 texel tiles.
// NONMATCHING 58%: same arithmetic, the original schedules the y terms first
#if NONMATCHING
s32 fn_800247E4(s32 x, s32 y, s32 width, s32 bytesPerTexel) {
    return bytesPerTexel * (width * (y / 4 * 4) + (x / 4 * 16 + y % 4 * 4 + x % 4));
}
#endif

// .text:0x80024840 size:0x134
// NONMATCHING 99%: r0/r3 swapped loading the mission status
#if NONMATCHING
s32 challengeStarRelatedInd(s32 team, s32 mission) {
    u8 status = starMissionCompletionTracker[team].inGameMissionTracker[mission].starMissionStatus;
    u8 row = lbl_800E8558[team].missionRow;
    s16 flags;

    if ((s8)status == -2) {
        return 1;
    }
    if (g_d_GameSettings.GameModeSelected == 5 && (s8)status == -1) {
        flags = lbl_80109AE8[row][mission].flags;
        if (flags & 1) {
            return 0;
        }
        if (flags & 2) {
            if (g_d_GameSettings.challengeDifficulty < 1) {
                return 0;
            }
        } else if (flags & 4) {
            if (g_d_GameSettings.challengeDifficulty < 2) {
                return 0;
            }
        } else if (flags & 8) {
            if (g_d_GameSettings.challengeDifficulty < 3) {
                return 0;
            }
        }
        if ((flags & 0x800) && *(s8*)((u8*)starMissionCompletionTracker + 0x44EF) == 0 && // TODO type
            *(s8*)((u8*)starMissionCompletionTracker + 0x44F0) == 0 && *(s32*)(lbl_8034E9A0 + 0x46E4) != 9) {
            return 0;
        }
        return 1;
    }
    return 0;
}
#endif

// Scale the byte b by a/255.
static inline s32 scaleByte(u32 b, u32 a) {
    return (s32)((s32)(b & 0xFF) * ((s32)(a & 0xFF) / lbl_803CC59C));
}

// .text:0x80024974 size:0x64
// Scale the low byte of color by scale/255.
// NONMATCHING 99%: int-to-float temps use swapped stack slots
#if NONMATCHING
u32 multBottomBits_asFloat(u32 color, u32 scale) {
    return (color & ~0xFF) | scaleByte(color, scale);
}
#endif

// .text:0x800249D8 size:0x128
// Scale each byte of color by scale/255.
// NONMATCHING 42%: same operations, the four byte conversions are scheduled differently
#if NONMATCHING
u32 byteWiseMultiply(u32 scale, u32 color) {
    return scaleByte(scale, color) | (scaleByte(scale, color >> 8) << 8) | (scaleByte(scale, color >> 16) << 16) |
           (scaleByte(scale, color >> 24) << 24);
}
#endif

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
