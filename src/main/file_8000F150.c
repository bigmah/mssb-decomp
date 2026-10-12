#include "main/file_8000F150.h"
#include "main/file_80011640.h"
#include "static/GameSettings.h"
#include "static/Camera.h"
#include "static/Pad.h"
extern PadState lbl_803C77B8[4];
#include "Dolphin/gx.h"
#include "main/file_800B0724.h"
#include "main/file_800BDEA0.h"
#include "main/file_8004B284.h"
#include "main/file_800527C4.h"
#include "main/file_8004C5F8.h"

extern u16 lbl_80366218[];
extern TexArchive* lbl_803CBBE8;
extern TexArchive lbl_800E9920;
extern GXColor lbl_803CB784;
extern u32 lbl_803CB788;
extern u32 lbl_803CB780;
typedef struct PaddedVec {
    Vec v;
    f32 _pad;
} PaddedVec;

// Output of fn_8000CEF0 (layout animation sample).
typedef struct LayoutInfo {
    /*0x00*/ u8 _00[0x6];
    /*0x06*/ u16 _06;
    /*0x08*/ u8 _08[0x4];
    /*0x0C*/ s16 size;
    /*0x0E*/ u8 _0E[0x6];
    /*0x14*/ s16 x;
    /*0x16*/ s16 y;
    /*0x18*/ u8 _18[0x4];
    /*0x1C*/ u32 color;
    /*0x20*/ u8 _20[0x30];
} LayoutInfo; // size: 0x50

typedef struct LayoutAnimSlot {
    /*0x00*/ u8 _00[0x38];
    /*0x38*/ void* anim;
} LayoutAnimSlot; // size: 0x3C

extern LayoutAnimSlot lbl_803C4BE0[];
extern u32 byteWiseMultiply(u32 a, u32 b);
extern u32 multBottomBits_asFloat(u32 a, u32 b);

extern f32 lbl_803CBBDC;
extern f32 lbl_803CBBE0;
extern void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss, u16 ts);

typedef struct TextDisplayList {
    /*0x0*/ u32 size;
    /*0x4*/ u32 width;  // in 9-pixel cells
    /*0x8*/ u32 height; // in 18-pixel cells
} TextDisplayList;

// This file's .data (0x800E8F60-0x800EE6A0). The original code reaches all of it
// from one base, so it is declared as one block here.
typedef struct TextStatics {
    /*0x0000*/ u8 altWidth[101][4]; // [char][fontSize], alternate font
    /*0x0194*/ u8 width[203][4];    // [glyph][fontSize] (lbl_800E90F4)
    /*0x04C0*/ u8 altYOff[101][4];
    /*0x0654*/ u8 yOff[203][4];
    /*0x0980*/ u32 colors[10];
    /*0x09A8*/ u8 _09A8[0x18];              // lbl_800E9908
    /*0x09C0*/ u8 texArchive[0x3060];       // lbl_800E9920
    /*0x3A20*/ s16 positions[0x440 / 2];
    /*0x3E60*/ u16 texCoords[0x1820 / 2];
    /*0x5680*/ void* displayLists[12];
    /*0x56B0*/ TextDisplayList dlInfo[12];
} TextStatics;
extern TextStatics lbl_800E8F60;
extern u8 lbl_800E90F4[][4]; // glyph widths for codes past lbl_800E8F60's table
extern CharMgr lbl_8036E548;

typedef struct FogSetting {
    /*0x0*/ u8 _00[0x8];
    /*0x8*/ s32 value;
} FogSetting;
extern FogSetting lbl_800E9908[];
extern u8 lbl_803CBBC0;
extern u8 lbl_803CB760[5];
extern void fn_800A7D4C(s32, void*);

// NONMATCHING 89%: the original keeps this file's .data base (lbl_800E8F60) in r31; that needs the data defined in this TU
// .text:0x8000F150 size:0x298
#if NONMATCHING
void fn_8000F150(TextWindow* window) {
    Mtx44 proj;
    Mtx mv;
    TextDisplayList* dl;

    GXSetCopyClear(lbl_803CB784, lbl_803CB788);
    C_MTXOrtho(proj, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, 2.0f);
    dl = &lbl_800E8F60.dlInfo[window->size];
    PSMTXTrans(mv, (640 - dl->width * 9) >> 1, (448 - dl->height * 18) >> 1, 0.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(mv, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 10);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 0x400, 0x400);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    SetDisplayStateTexture(TEX_ARCHIVE_IMG(lbl_803CBBE8, 0), 0, 0);
    GXSetArray(GX_VA_POS, lbl_800E8F60.positions, 6);
    GXSetArray(GX_VA_CLR0, &lbl_803CB780, 4);
    GXSetArray(GX_VA_TEX0, lbl_800E8F60.texCoords, 4);
    GXCallDisplayList(lbl_800E8F60.displayLists[window->size], lbl_800E8F60.dlInfo[window->size].size);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0x400, 0x400);
}
#endif

// .text:0x8000F3E8 size:0xA4
void fn_8000F3E8(s32 arg) {
    FogSetting* f = &lbl_800E9908[lbl_803CBBC0];
    switch (arg) {
    case -1:
        f->value = lbl_803CB760[4];
        break;
    case 4:
        f->value = lbl_803CB760[1];
        break;
    case 5:
        f->value = lbl_803CB760[0];
        break;
    case 6:
        f->value = lbl_803CB760[2];
        break;
    case 11:
        f->value = lbl_803CB760[3];
        break;
    }
    fn_800A7D4C(0, f);
}

// .text:0x8000F48C size:0x2C
void somethingSetTexturePointer(void) {
    lbl_803CBBE8 = &lbl_800E9920;
    convertTextureHeader(&lbl_800E9920);
}

// .text:0x8000F4B8 size:0x7C
void fn_8000F4B8(s32 a, s32 b, s32 c, s32 d) {
    lbl_80366B18.padMask = 0;
    if (a >= 0) {
        lbl_80366B18.padMask = 1 << a;
    }
    if (b >= 0) {
        lbl_80366B18.padMask |= 1 << b;
    }
    if (c >= 0) {
        lbl_80366B18.padMask |= 1 << c;
    }
    if (d >= 0) {
        lbl_80366B18.padMask |= 1 << d;
    }
}

// NONMATCHING 98.4%: original loads the anim pointer with lwzu (keeps &slot->anim in r31); ours uses addi+lwz
// .text:0x8000F534 size:0x3C0
#if NONMATCHING
void fn_8000F534(LayoutObj* obj, s32 visible) {
    LayoutInfo info;
    LayoutInfo info2;
    s32 small;
    u16 animId;
    TextOwner* owner;
    void** anim;
    u32 color;
    s32 size;
    s16 x;
    s16 y;
    s32 i;

    small = 0;
    for (i = 0; i < 30; i++) {
        if (obj == lbl_80366B18.owners[i].object) {
            break;
        }
    }
    if (i >= 30) {
        return;
    }
    owner = &lbl_80366B18.owners[i];
    if (visible == 0) {
        lbl_80366B18.entries[owner->entry].state = 1;
        return;
    }
    lbl_80366B18.entries[owner->entry].state = 2;
    animId = obj->_64;
    anim = &lbl_803C4BE0[obj->_66].anim;
    fn_8000CEF0(*anim, animId, 0, owner->_06, (u32*)&info); // fills the key's u32 parameter words
    x = info.x;
    y = info.y;
    if (obj->flags & 8) {
        color = byteWiseMultiply(info.color, obj->color);
    } else {
        color = multBottomBits_asFloat(info.color, obj->color);
    }
    lbl_80366B18.entries[owner->entry].color = color;
    size = (info.size << 8) / 1024;
    if (size == 16) {
        lbl_80366B18.entries[owner->entry].fontSize = 2;
        small = 1;
    } else if (size == 18) {
        lbl_80366B18.entries[owner->entry].fontSize = 1;
    } else if (size == 22) {
        lbl_80366B18.entries[owner->entry].fontSize = 0;
    } else {
        fn_8000CEF0(*anim, info._06, 0, 0, (u32*)&info2);
        size = (info2.size << 8) / 1024;
        if (size < 17) {
            lbl_80366B18.entries[owner->entry].fontSize = 2;
            small = 1;
        } else if (size < 20) {
            lbl_80366B18.entries[owner->entry].fontSize = 1;
        } else {
            lbl_80366B18.entries[owner->entry].fontSize = 0;
        }
    }
    if (small) {
        TextEntry* e = &lbl_80366B18.entries[owner->entry];
        e->x = x;
        e->y = y;
    } else {
        TextEntry* e = &lbl_80366B18.entries[owner->entry];
        e->x = x;
        e->y = y;
    }
    if (fn_8000CEF0(*anim, animId, 1, owner->_06, (u32*)&info) != 0) {
        lbl_80366B18.entries[owner->entry].shadowColor = multBottomBits_asFloat(info.color, obj->color);
        lbl_80366B18.entries[owner->entry].shadowX = info.x - lbl_80366B18.entries[owner->entry].x;
        lbl_80366B18.entries[owner->entry].shadowY = info.y - lbl_80366B18.entries[owner->entry].y;
    } else {
        lbl_80366B18.entries[owner->entry].shadowColor = 0;
    }
}
#endif

// .text:0x8000F8F4 size:0x94
void fn_8000F8F4(LayoutGroup* group) {
    s32 i;
    s32 j;
    u16 start = group->start;
    for (i = 0; i < group->count; i++) {
        LayoutObj* obj = lbl_80371C30[start + (u32)i].obj;
        if (obj != NULL && (obj->flags & 4)) {
            for (j = 0; j < 30; j++) {
                if (lbl_80366B18.owners[j].object == lbl_80371C30[start + (u32)i].obj) {
                    lbl_80366B18.owners[j].object = NULL;
                    break;
                }
            }
        }
    }
}

// .text:0x8000F988 size:0x114
s32 fn_8000F988(LayoutGroup* group, s32 index, u16 arg2, s32 table, s32 msg, s32 shadow) {
    s32 i;
    LayoutObj* obj = lbl_80371C30[group->start + index].obj;
    obj->flags |= 4;
    if (shadow != 0) {
        obj->flags |= 8;
    }
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.owners[i].object == NULL) {
            lbl_80366B18.owners[i].object = obj;
            lbl_80366B18.owners[i]._06 = arg2;
            lbl_80366B18.owners[i].entry = fn_8000FF04(table, msg, 0, 0, obj->layer, -1, 0);
            if (obj->_00 != NULL) {
                lbl_80366B18.entries[lbl_80366B18.owners[i].entry].mtx = obj->mtx;
            } else {
                lbl_80366B18.entries[lbl_80366B18.owners[i].entry].mtx = NULL;
            }
            return lbl_80366B18.owners[i].entry;
        }
    }
    return -1;
}

// NONMATCHING 97.1%: register allocation differs, and an extra branch after the end-of-substring continue
// .text:0x8000FA9C size:0x2B8
#if NONMATCHING
s32 fn_8000FA9C(s32 index) {
    PTR32(u16)* msgs;
    u16* base;
    u16* sub;
    TextEntry* e;
    s32 narrowAdv;
    s32 code;
    s32 n;
    s32 wideAdv;
    s32 maxWidth;
    s32 alt;
    s32 width;
    s32 inSub;
    u16* text;
    u16 c;
    e = &lbl_80366B18.entries[index];
    wideAdv = 22;
    narrowAdv = 11;
    maxWidth = 0;
    width = 0;
    inSub = 0;
    alt = 0;
    text = e->text;

    if (e->fontSize == 2) {
        wideAdv = 18;
        narrowAdv = 9;
    } else if (e->fontSize == 1) {
        wideAdv = 18;
        narrowAdv = 9;
    }
    msgs = lbl_80366B18.tables[0]->msgs;
    base = lbl_80366B18._7F4;
    for (;;) {
        if (inSub) {
            c = *sub++;
        } else {
            c = *text++;
        }
        if (c & 0x4000) {
            code = c & 0x3FFF;
            switch (code) {
            case 0:
                if (inSub) {
                    inSub = 0;
                    continue;
                }
                return maxWidth;
            case 2:
                width += narrowAdv;
                break;
            case 3:
                width += wideAdv;
                break;
            case 1:
                width = 0;
                break;
            case 15:
            case 16:
            case 17:
            case 18:
                n = e->numbers[code - 15];
                if (n < 0) {
                    n = -n;
                    width += wideAdv;
                }
                while (1) {
                    if (n < 10) {
                        break;
                    }
                    width += wideAdv;
                    n /= 10;
                }
                break;
            case 25:
            case 26:
            case 27:
            case 28:
            case 35:
            case 36:
            case 37:
            case 38:
                n = code - 15;
                if (n >= 10) {
                    n = e->strings[n - 10] + 0x3E;
                } else {
                    n = e->strings[n] + 8;
                }
                sub = PTR32_GET(u16, msgs[n]);
                inSub = 1;
                break;
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
                width += 28;
                width += e->charSpacing;
                break;
            case 57:
                alt = 1;
                break;
            case 58:
                alt = 0;
                break;
            }
        } else {
            if (!alt) {
                if (c & 0x8000) {
                    c &= 0x7FFF;
                } else {
                    c = lbl_80366218[c] & 0x7FFF;
                }
                c = c % 0x844;
                n = c - (*base & 0x7FFF) - 1;
                c = lbl_800E90F4[n][e->fontSize];
            } else {
                c = lbl_800E8F60.altWidth[c][e->fontSize];
            }
            width += c;
            width += e->charSpacing;
        }
        if (width > maxWidth) {
            maxWidth = width;
        }
    }
}
#endif

// .text:0x8000FD54 size:0x24
void fn_8000FD54(s32 index, s16 a, s16 b, s16 c, s16 d) {
    TextEntry* e = &lbl_80366B18.entries[index];
    e->strings[0] = a;
    e->strings[1] = b;
    e->strings[2] = c;
    e->strings[3] = d;
}

// .text:0x8000FD78 size:0x24
void fn_8000FD78(s32 index, s16 a, s16 b, s16 c, s16 d) {
    TextEntry* e = &lbl_80366B18.entries[index];
    e->numbers[0] = a;
    e->numbers[1] = b;
    e->numbers[2] = c;
    e->numbers[3] = d;
}

// .text:0x8000FD9C size:0x6C
void fn_8000FD9C(s32 index, s32 speed, s32 limit) {
    if (speed == 0) {
        lbl_80366B18.entries[index].charLimit = -1;
        lbl_80366B18.entries[index].typeSpeed = 0;
        lbl_80366B18.entries[index].typeTimer = 0;
        return;
    }
    if (limit >= 0) {
        lbl_80366B18.entries[index].charLimit = limit;
    }
    lbl_80366B18.entries[index].typeSpeed = speed;
    lbl_80366B18.entries[index].typeTimer = 0;
}

// .text:0x8000FE08 size:0x4C
void fn_8000FE08(s32 index, s32 table, s32 msg) {
    TextEntry* e;
    u16* text = PTR32_GET(u16, lbl_80366B18.tables[table]->msgs[msg]);
    e = &lbl_80366B18.entries[index];
    e->text = text;
    if (e->charLimit >= 0) {
        e->charLimit = 0;
        e->finished = 0;
        e->_35 = 0;
    }
}

// .text:0x8000FE54 size:0x94
void fn_8000FE54(void) {
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].state = 0;
    }
}

// .text:0x8000FEE8 size:0x1C
void fn_8000FEE8(s32 index) {
    lbl_80366B18.entries[index].state = 0;
}

// .text:0x8000FF04 size:0x1A0
s32 fn_8000FF04(s32 table, s32 msg, s16 x, s16 y, u8 layer, u32 color, u8 fontSize) {
    s32 i;
    TextEntry* e;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].state == 0) {
            break;
        }
    }
    if (i >= 30) {
        return 0;
    }
    e = &lbl_80366B18.entries[i];
    e->text = PTR32_GET(u16, lbl_80366B18.tables[table]->msgs[msg]);
    e->x = x;
    e->y = y;
    e->layer = layer;
    e->state = 2;
    e->fontSize = fontSize;
    e->color = color;
    e->numbers[0] = 0;
    e->numbers[1] = 0;
    e->numbers[2] = 0;
    e->numbers[3] = 0;
    e->charSpacing = 0;
    e->lineSpacing = 2;
    e->hAlign = 0;
    e->vAlign = 0;
    e->mtx = NULL;
    e->charLimit = -1;
    e->typeSpeed = 0;
    e->typeTimer = 0;
    e->finished = 0;
    e->_33 = 0;
    e->_35 = 0;
    e->_36 = 0;
    return i;
}

// NONMATCHING 98.6%: f2/f3 swapped for the 0.0f constant, and two extra clrlwi on the u16 s+w sum
// .text:0x800100A4 size:0x3F4
#if NONMATCHING
void fn_800100A4(s32 x, s32 y, u16 s, u16 t, u16 w, u32 color, s32 kind, MtxPtr mtx) {
    QuadVtx quad[4];
    Mtx trans;
    Mtx m;
    PaddedVec p[4];
    f32 scale;
    f32 left = 0.0f;
    f32 top = 0.0f;
    f32 right;
    f32 bottom;
    s32 h = 22;

    fn_800B2160(1);
    if (kind >= 10) {
        h = 20;
        w = 28;
    } else if (kind == 3) {
        h = 22;
    } else if (kind == 2) {
        h = 18;
    } else if (kind == 1) {
        h = 18;
    }
    if (mtx != NULL) {
        PSMTXTrans(trans, x, y, 0.0f);
        PSMTXConcat(mtx, trans, m);
    } else {
        PSMTXTrans(trans, x - 320, y - 224, 0.0f);
    }
    right = left + w;
    bottom = top + h;
    p[0].v.x = left;
    p[0].v.y = top;
    p[1].v.x = right;
    p[1].v.y = top;
    p[2].v.x = left;
    p[2].v.y = bottom;
    p[3].v.x = right;
    p[3].v.y = bottom;
    p[3].v.z = left;
    p[2].v.z = left;
    p[1].v.z = left;
    p[0].v.z = left;
    if (mtx == NULL) {
        scale = lbl_803CBBE0 / lbl_803CBBDC;
        PSMTXScale(m, scale, scale, 1.0f);
        PSMTXConcat(m, trans, m);
    }
    PSMTXMultVec(m, &p[0].v, &p[0].v);
    PSMTXMultVec(m, &p[1].v, &p[1].v);
    PSMTXMultVec(m, &p[2].v, &p[2].v);
    PSMTXMultVec(m, &p[3].v, &p[3].v);
    quad[0].pos.x = p[0].v.x;
    quad[0].pos.y = p[0].v.y;
    quad[1].pos.x = p[2].v.x;
    quad[1].pos.y = p[2].v.y;
    quad[2].pos.x = p[3].v.x;
    quad[2].pos.y = p[3].v.y;
    quad[3].pos.x = p[1].v.x;
    quad[3].pos.y = p[1].v.y;
    if (mtx != NULL) {
        quad[0].pos.z = p[0].v.z;
        quad[1].pos.z = p[2].v.z;
        quad[2].pos.z = p[3].v.z;
        quad[3].pos.z = p[1].v.z;
    } else {
        quad[0].pos.z = quad[1].pos.z = quad[2].pos.z = quad[3].pos.z = -lbl_803CBBE0;
    }
    quad[3].color = color;
    quad[2].color = color;
    quad[1].color = color;
    quad[0].color = color;
    if (kind < 10) {
        s *= lbl_80366B18.scaleX;
        t *= lbl_80366B18.scaleY;
        w *= lbl_80366B18.scaleX;
        h *= lbl_80366B18.scaleY;
    }
    quad[1].s = s;
    quad[0].s = s;
    quad[3].s = s + w;
    quad[2].s = s + w;
    quad[3].t = t;
    quad[0].t = t;
    quad[2].t = t + h;
    quad[1].t = t + h;
    if (kind >= 10) {
        quad[1].s = 0;
        quad[0].s = 0;
        quad[3].s = 0x400;
        quad[2].s = 0x400;
        quad[3].t = 0;
        quad[0].t = 0;
        quad[2].t = 0x400;
        quad[1].t = 0x400;
        DrawSprite_TexObj(quad, lbl_80366B18.iconTexObj[kind - 10]);
    } else if (kind == 3) {
        fn_800B1314(quad, lbl_80366B18.fontTexObj[3], 0x400, 0x400);
    } else if (kind == 2) {
        fn_800B1314(quad, lbl_80366B18.fontTexObj[2], 0x400, 0x400);
    } else if (kind == 1) {
        fn_800B1314(quad, lbl_80366B18.fontTexObj[1], 0x400, 0x400);
    } else {
        fn_800B1314(quad, lbl_80366B18.fontTexObj[0], 0x400, 0x400);
    }
}
#endif

// NONMATCHING 86%: register allocation/spills differ (original spills narrow and the text pointers to the stack); control flow and calls match
// .text:0x80010498 size:0xA94
#if NONMATCHING
void DrawText(s32 index) {
    TextEntry* e = &lbl_80366B18.entries[index];
    TextStatics* data = &lbl_800E8F60;
    s32 charW = 22;
    s32 narrow = 11;
    s32 lineH = 22;
    s32 count = 0;
    s32 kind = 0;
    s32 printed = 1;
    u16* text = e->text;
    u16* sub;
    s32 inSub = 0;
    s32 speedOverride = -1;
    u32 color = e->color;
    s32 startX;
    s32 x;
    s32 y;
    s32 lines;
    s32 total;
    s32 lh;
    u16* p;
    u16 c;
    u32 code;
    s32 n;
    s32 k;
    s32 digits[5];
    u16 glyph;
    u16 col;
    u16 s;
    u16 t;
    u16 w;
    s32 yoff;
    s32 speed;

    if (e->charLimit >= 3) {
        if (((lbl_803C77B8[0].down & 0x1100) && (lbl_80366B18.padMask & 1)) ||
            ((lbl_803C77B8[1].down & 0x1100) && (lbl_80366B18.padMask & 2)) ||
            ((lbl_803C77B8[2].down & 0x1100) && (lbl_80366B18.padMask & 4)) ||
            ((lbl_803C77B8[3].down & 0x1100) && (lbl_80366B18.padMask & 8))) {
            e->finished = 1;
            e->charLimit = 10000;
        }
    }
    if (e->fontSize == 2) {
        narrow = 9;
        kind = 2;
        charW = 18;
        lineH = 18;
    } else if (e->fontSize != 0) {
        narrow = 9;
        kind = 1;
        charW = 18;
        lineH = 18;
    }

    startX = e->x;
    x = startX;
    y = e->y;
    if (e->hAlign == 1) {
        startX = x = narrow + (startX - fn_8000FA9C(index) / 2);
    } else if (e->hAlign == 2) {
        startX = x = charW + (startX - fn_8000FA9C(index));
    }

    if (e->vAlign == 1) {
        lines = 1;
        p = e->text;
        lh = 22;
        if (e->fontSize == 2) {
            lh = 18;
        } else if (e->fontSize == 1) {
            lh = 18;
        }
        for (;;) {
            c = *p++;
            if (!(c & 0x4000)) {
                continue;
            }
            code = c & 0x3FFF;
            if (code == 0) {
                break;
            }
            if (code == 1) {
                lines++;
            }
        }
        total = lines * lh;
        if (lines > 1) {
            total += e->lineSpacing * (lines - 1);
        }
        y = lineH / 2 + (y - total / 2);
    } else if (e->vAlign == 2) {
        lines = 1;
        p = e->text;
        lh = 22;
        if (e->fontSize == 2) {
            lh = 18;
        } else if (e->fontSize == 1) {
            lh = 18;
        }
        for (;;) {
            c = *p++;
            if (!(c & 0x4000)) {
                continue;
            }
            code = c & 0x3FFF;
            if (code == 0) {
                break;
            }
            if (code == 1) {
                lines++;
            }
        }
        total = lines * lh;
        if (lines > 1) {
            total += e->lineSpacing * (lines - 1);
        }
        y = (y + total) - lineH;
    }

    for (;;) {
        if (e->charLimit >= 0 && !e->finished) {
            if (count > e->charLimit) {
                break;
            }
            speedOverride = -1;
        }
        printed = 1;
        if (inSub) {
            c = *sub++;
        } else {
            c = *text++;
        }

        if (c & 0x4000) {
            code = c & 0x3FFF;
            if (code == 0) {
                if (inSub) {
                    inSub = 0;
                    continue;
                }
                printed = 0;
                e->finished = 1;
                break;
            }
            if (code >= 0x4B && code <= 0x72) {
                if (!e->_35) {
                    if (g_d_GameSettings.GameModeSelected == 5) {
                        fn_80062890(code - 0x39);
                    }
                    e->_35 = 1;
                }
                printed = 0;
                continue;
            }
            switch (code) {
            case 2:
                printed = 0;
                count++;
                x += narrow;
                x += e->charSpacing;
                break;
            case 3:
                x += charW;
                printed = 0;
                count++;
                x += e->charSpacing;
                break;
            case 1:
                y += lineH;
                x = startX;
                printed = 0;
                count++;
                y += e->lineSpacing;
                break;
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
                if (code - 5 == 0) {
                    color = e->color;
                } else {
                    color = (color & 0xFF) | data->colors[code - 5];
                }
                printed = 0;
                break;
            case 15:
            case 16:
            case 17:
            case 18:
                n = e->numbers[code - 15];
                if (n < 0) {
                    glyph = (lbl_80366B18._7EC[10] & 0x7FFF) % 0x844;
                    w = charW;
                    n = -n;
                    col = glyph % 46;
                    t = (glyph / 46) * lineH;
                    s = col * charW;
                    if (e->shadowColor != 0) {
                        fn_800100A4(x + e->shadowX, y + e->shadowY, s, t, w, e->shadowColor, kind, e->mtx);
                    }
                    fn_800100A4(x, y, s, t, w, color, kind, e->mtx);
                    x += w;
                    x += e->charSpacing;
                }
                k = 0;
                for (;;) {
                    digits[k] = n % 10;
                    if (n < 10) {
                        break;
                    }
                    n /= 10;
                    k++;
                }
                w = charW;
                for (; k >= 0; k--) {
                    glyph = (lbl_80366B18._7EC[digits[k]] & 0x7FFF) % 0x844;
                    col = glyph % 46;
                    t = (glyph / 46) * lineH;
                    s = col * charW;
                    if (e->shadowColor != 0) {
                        fn_800100A4(x + e->shadowX, y + e->shadowY, s, t, w, e->shadowColor, kind, e->mtx);
                    }
                    fn_800100A4(x, y, s, t, w, color, kind, e->mtx);
                    x += w;
                    count++;
                    x += e->charSpacing;
                }
                break;
            case 25:
            case 26:
            case 27:
            case 28:
            case 35:
            case 36:
            case 37:
            case 38:
                n = code - 15;
                if (n >= 10) {
                    n = e->strings[n - 10] + 0x3E;
                } else {
                    n = e->strings[n] + 8;
                }
                inSub = 1;
                sub = PTR32_GET(u16, lbl_80366B18.tables[0]->msgs[n]);
                break;
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
                fn_800100A4(x, y - 1, 0, 0, 0, color | 0xFFFFFF00, code - 0x23, e->mtx);
                x += 28;
                count++;
                x += e->charSpacing;
                break;
            case 55:
                narrow = 11;
                charW = 22;
                lineH = 22;
                kind = 3;
                printed = 0;
                break;
            case 56:
                kind = e->fontSize;
                if (kind == 2) {
                    narrow = 9;
                    charW = 18;
                    lineH = 18;
                } else if (kind != 0) {
                    narrow = 9;
                    charW = 18;
                    lineH = 18;
                } else {
                    narrow = 11;
                    charW = 22;
                    lineH = 22;
                }
                printed = 0;
                break;
            case 57:
                e->_36 = 1;
                break;
            case 58:
                e->_36 = 0;
                break;
            case 66:
            case 67:
            case 68:
            case 69:
            case 70:
            case 71:
            case 72:
            case 73:
            case 74:
                printed = 0;
                count++;
                speedOverride = (code - 0x41) * 10;
                break;
            }
        } else {
            count++;
            if (e->_36 == 0) {
                if (c & 0x8000) {
                    glyph = c & 0x7FFF;
                } else {
                    glyph = lbl_80366218[c] & 0x7FFF;
                }
                glyph = glyph % 0x844;
                n = glyph - (*lbl_80366B18._7F4 & 0x7FFF) - 1;
                w = data->width[n][kind];
                yoff = data->yOff[n][kind];
                col = glyph % 46;
                t = (glyph / 46) * lineH;
                s = col * charW;
            } else {
                yoff = data->altYOff[c][kind];
                w = data->altWidth[c][kind];
                col = c % 92;
                t = (c / 92) * lineH;
                s = narrow * ((col / 2) * 2 + col % 2);
            }
            if (e->shadowColor != 0) {
                fn_800100A4(x + e->shadowX, y + (e->shadowY + yoff), s, t, w, e->shadowColor, kind, e->mtx);
            }
            fn_800100A4(x, y + yoff, s, t, w, color, kind, e->mtx);
            x += w;
            x += e->charSpacing;
        }
    }

    // typewriter effect
    if (e->charLimit >= 0 && e->charLimit < 10000) {
        speed = e->typeSpeed;
        if (speedOverride >= 0) {
            speed = speedOverride;
        }
        if (e->finished) {
            e->charLimit = 10000;
            e->_35 = 1;
        } else if (e->typeTimer > speed) {
            e->typeTimer = 0;
            if (e->charLimit < 0x7FFE) {
                e->charLimit++;
            } else {
                e->charLimit = 0x7FFF;
            }
            if (printed && g_d_GameSettings.GameModeSelected == 5 && e->charLimit > 2) {
                fn_80062890(2);
            }
        } else {
            e->typeTimer++;
        }
    }
}
#endif

// .text:0x80010F2C size:0x74
void DrawTextOnCondition(s32 layer) {
    s32 i;
    for (i = 0; i < 30; i++) {
        if (lbl_80366B18.entries[i].state == 2 && layer == lbl_80366B18.entries[i].layer) {
            DrawText(i);
        }
    }
}

// NONMATCHING 92.9%: extra `mr` when setting up dst before the copy loop
// .text:0x80010FA0 size:0x60
#if NONMATCHING
void fn_80010FA0(void) {
    MsgTable* t = lbl_80366B18.tables[0];
    u16* dst = lbl_80366218;
    u16* src;
    lbl_80366B18.msgs = t->msgs;
    lbl_80366B18._7EC = PTR32_GET(u16, t->msgs[1]);
    lbl_80366B18._7F0 = PTR32_GET(u16, t->msgs[2]);
    lbl_80366B18._7F8 = PTR32_GET(u16, t->msgs[6]);
    lbl_80366B18._7F4 = PTR32_GET(u16, t->msgs[5]);
    src = PTR32_GET(u16, lbl_80366B18.msgs[7]);
    for (;;) {
        u16 c = *src;
        if (c == 0x4001) {
            return;
        }
        *dst = c;
        src++;
        dst++;
    }
}
#endif

// NONMATCHING 96.4%: saved regs r30/r31 swapped (loop counter vs. lbl_80366B18 base)
// .text:0x80011000 size:0x140
#if NONMATCHING
void fn_80011000(void) {
    s32 i;
#ifdef TARGET_PC
    port_swap_offset_table(lbl_80366B18.fontArchive, 4);
#endif
    lbl_80366B18.fontTex[0] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[0]);
    lbl_80366B18.fontTex[1] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[1]);
    lbl_80366B18.fontTex[2] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[2]);
    lbl_80366B18.fontTex[3] = (TexArchive*)((u8*)lbl_80366B18.fontArchive + lbl_80366B18.fontArchive[3]);
    for (i = 0; i < 4; i++) {
        convertTextureHeader(lbl_80366B18.fontTex[i]);
        lbl_80366B18.fontTexObj[i] = TEX_ARCHIVE_IMG(lbl_80366B18.fontTex[i], 0);
    }
    convertTextureHeader(lbl_80366B18.iconArchive);
    for (i = 0; i < 9; i++) {
        lbl_80366B18.iconTexObj[i] = TEX_ARCHIVE_IMG(lbl_80366B18.iconArchive, i);
    }
    lbl_80366B18.scaleX = 1;
    lbl_80366B18.scaleY = 1;
}
#endif

// .text:0x80011140 size:0x74
void fn_80011140(void) {
    s32 i;
    for (i = 0; i < 30; i++) {
        lbl_80366B18.entries[i].state = 0;
        lbl_80366B18.owners[i].object = NULL;
    }
    lbl_80366B18.padMask = 0;
}

// .text:0x800111B4 size:0x24
void fn_800111B4(MsgTable* table) {
#ifdef TARGET_PC
    port_swap_msg_table(table);
#endif
    s32 n = table->count;
    PTR32(u16)* p = table->msgs;
    do {
        // file offset -> pointer
#ifdef TARGET_PC
        *p += PTR_TO_U32(table);
#else
        *p = (u16*)((uintptr_t)*p + (uintptr_t)table);
#endif
        p++;
    } while (--n);
}

// .text:0x800111D8 size:0x24
GameActor** fn_800111D8(CharActor* actor) {
    return &lbl_8036E548.slots->objects[actor->modelIndex].actor;
}

// .text:0x800111FC size:0x15C
CharActor* fn_800111FC(CharActor* actor, s32 second) {
    s32 slot;
    CharActor* next;
    if (g_d_GameSettings.GameModeSelected != 6) {
        return actor;
    }
    slot = actor->modelIndex % 4;
    lbl_8036E548.actors[slot + 4].mode[0] = 0;
    lbl_8036E548.actors[slot].mode[0] = 0;
    next = lbl_8036E548.active[slot] = &lbl_8036E548.actors[slot + ((second != 0) << 2)];
    if (next->modelIndex != actor->modelIndex) {
        fn_8001BA44(slot, actor->anim[0], actor->_25F[0], actor->_262[0], 0, actor->_265[0], actor->_269[0]);
        next->anim[1] = actor->anim[1];
        next->_06A[1] = actor->_06A[1];
        next->mode[1] = actor->mode[1];
        next->_25F[1] = actor->_25F[1];
        next->_262[1] = actor->_262[1];
        next->_265[1] = actor->_265[1];
        next->_269[1] = actor->_269[1];
        next->_26C[1] = actor->_26C[1];
        next->anim[2] = actor->anim[2];
        next->_06A[2] = actor->_06A[2];
        next->_25F[2] = actor->_25F[2];
        next->_262[2] = actor->_262[2];
        next->_265[2] = actor->_265[2];
        next->_269[2] = actor->_269[2];
        next->_26C[2] = actor->_26C[2];
    }
    return next;
}

// .text:0x80011358 size:0x110
void fn_80011358(s32 index, s32 kind) {
    CharActor* actor;
    ActorObjectTable* models;
    ActorObjectTable* models2;
    GameActor* model;
    GameActor** target;
    u16 anim;
    s32 i;
    if (index < 0 || index >= 13) {
        return;
    }
    actor = lbl_8036E548.active[index];
    if (actor == NULL || (models = lbl_8036E548.slots) == NULL || (models2 = lbl_8036E548.slots64) == NULL) {
        return;
    }
    anim = actor->jointIdx[36];
    if (anim == 0xFFFF) {
        return;
    }
    if (kind < 0 || kind >= 5) {
        kind = 4;
    }
    target = &models->objects[actor->modelIndex].actor;
    if (kind == 4) {
        fn_800B2BA8(*target, anim, NULL, 0);
        return;
    }
    model = models2->objects[kind + 21].actor;
    for (i = 0; i < model->totalBones; i++) {
        if (model->boneArray[i]->dispObj != NULL) {
            fn_800B2BA8(*target, anim, model, i);
            return;
        }
    }
}

// ---- Data (initialisers generated from the original DOL) ----

// .data 0x800E8F60..0x800EE800
TextStatics lbl_800E8F60 = {
    {
        {8, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 6, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {7, 6, 9, 8},
        {10, 7, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {8, 9, 9, 8},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {9, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {8, 9, 9, 7},
        {9, 9, 9, 11},
        {11, 9, 9, 11},
        {8, 9, 9, 7},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
        {11, 9, 9, 11},
    },
    {
        {10, 9, 9, 22},
        {10, 9, 9, 22},
        {8, 9, 8, 22},
        {8, 9, 8, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {8, 10, 8, 7},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {9, 18, 9, 6},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {22, 18, 18, 22},
        {17, 18, 18, 11},
        {12, 10, 10, 18},
        {17, 18, 18, 22},
        {17, 18, 18, 22},
        {19, 18, 18, 22},
        {18, 18, 18, 22},
        {18, 18, 18, 22},
        {17, 18, 18, 22},
        {17, 18, 18, 22},
        {17, 18, 18, 22},
        {20, 18, 16, 20},
        {19, 15, 15, 19},
        {20, 16, 16, 20},
        {19, 16, 16, 19},
        {18, 14, 15, 18},
        {17, 14, 14, 18},
        {20, 16, 16, 20},
        {18, 15, 15, 20},
        {8, 7, 8, 8},
        {13, 11, 11, 13},
        {19, 16, 15, 19},
        {17, 14, 13, 17},
        {20, 18, 18, 22},
        {18, 15, 15, 20},
        {20, 18, 18, 20},
        {17, 15, 15, 19},
        {19, 18, 18, 20},
        {18, 16, 15, 19},
        {18, 15, 14, 18},
        {18, 15, 14, 20},
        {18, 16, 16, 20},
        {20, 16, 16, 20},
        {22, 18, 18, 22},
        {18, 17, 16, 19},
        {18, 15, 15, 19},
        {18, 14, 14, 19},
        {17, 15, 14, 16},
        {17, 14, 13, 16},
        {17, 14, 13, 15},
        {17, 15, 13, 15},
        {17, 14, 13, 15},
        {13, 10, 10, 13},
        {17, 14, 13, 15},
        {17, 14, 13, 15},
        {9, 8, 7, 8},
        {12, 10, 9, 12},
        {15, 14, 12, 15},
        {9, 8, 7, 8},
        {22, 18, 18, 20},
        {17, 14, 13, 15},
        {17, 15, 13, 16},
        {17, 14, 13, 16},
        {17, 15, 13, 15},
        {12, 10, 10, 11},
        {15, 13, 12, 13},
        {14, 11, 10, 13},
        {17, 14, 13, 15},
        {17, 14, 13, 14},
        {22, 18, 18, 20},
        {15, 14, 13, 14},
        {16, 14, 13, 14},
        {15, 14, 12, 14},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 2, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 2, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 2, 3},
        {3, 2, 2, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 2, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 1, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 1, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 0, 3},
        {3, 2, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {0, 0, 0, 3},
        {3, 2, 1, 3},
        {0, 0, 0, 3},
    },
    {0, 0xFF15B100, 0xB8900000, 0xFF000000, 0x990000, 65280, 0x80000000, 0x33996600, 0x33339900, 0},
    {0, 0, 0, 0, 128, 0, 241, 80, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 241, 80, 0, 0, 0, 0},
    {
        0, 1, 0, 0, 0, 0, 0, 96, 0, 0, 0, 64, 0, 18, 4, 0,
        0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 8, 0, 16, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 255, 36, 255, 73, 255, 109, 255, 146, 255, 182, 255, 219, 255, 255, 255,
        255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0, 255, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 4, 97, 0, 0, 6, 114, 0, 0, 22, 116,
        0, 0, 38, 85, 0, 0, 54, 70, 0, 0, 85, 39, 0, 0, 100, 7,
        0, 0, 0, 0, 0, 0, 54, 102, 0, 0, 71, 119, 0, 0, 70, 0,
        0, 0, 69, 0, 0, 0, 70, 0, 16, 0, 69, 0, 32, 0, 70, 0,
        0, 0, 0, 0, 81, 0, 0, 5, 117, 0, 0, 87, 71, 16, 2, 117,
        23, 32, 4, 113, 7, 32, 6, 96, 23, 32, 6, 64, 71, 0, 39, 48,
        33, 0, 0, 0, 118, 48, 4, 102, 103, 114, 5, 119, 0, 101, 5, 96,
        0, 52, 5, 80, 0, 16, 5, 80, 0, 0, 5, 80, 0, 0, 5, 80,
        0, 0, 0, 0, 100, 0, 0, 4, 119, 96, 0, 5, 21, 115, 0, 5,
        0, 117, 0, 5, 0, 71, 16, 5, 0, 39, 32, 5, 0, 23, 80, 5,
        0, 0, 0, 0, 102, 102, 96, 0, 119, 119, 113, 0, 96, 17, 16, 0,
        80, 0, 0, 0, 80, 0, 0, 0, 80, 0, 0, 0, 80, 0, 0, 2,
        0, 2, 0, 0, 0, 87, 64, 0, 5, 118, 115, 0, 39, 64, 102, 0,
        71, 16, 37, 0, 101, 0, 17, 0, 100, 0, 0, 0, 115, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0,
        0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0,
        0, 0, 0, 0, 0, 69, 0, 0, 0, 86, 0, 0, 0, 85, 0, 0,
        0, 85, 0, 0, 0, 85, 0, 0, 0, 85, 0, 0, 0, 85, 0, 0,
        0, 0, 0, 0, 0, 86, 0, 1, 0, 87, 16, 3, 0, 87, 48, 4,
        0, 87, 64, 5, 0, 86, 80, 5, 0, 85, 80, 6, 0, 84, 96, 38,
        0, 0, 0, 0, 119, 0, 54, 16, 119, 0, 71, 48, 119, 0, 55, 80,
        119, 0, 55, 97, 119, 0, 70, 114, 103, 0, 69, 100, 87, 0, 69, 70,
        0, 0, 0, 0, 3, 64, 0, 21, 4, 80, 0, 103, 4, 80, 2, 116,
        4, 80, 4, 112, 4, 80, 6, 80, 4, 80, 6, 64, 4, 80, 39, 32,
        0, 0, 0, 0, 98, 0, 0, 54, 119, 0, 0, 71, 39, 64, 0, 71,
        5, 96, 0, 71, 3, 113, 0, 71, 2, 114, 0, 71, 1, 117, 0, 71,
        0, 0, 0, 0, 102, 81, 0, 4, 119, 118, 0, 5, 0, 71, 16, 5,
        0, 7, 32, 5, 0, 6, 64, 5, 0, 5, 64, 5, 0, 6, 64, 5,
        0, 0, 0, 0, 102, 100, 0, 0, 119, 119, 64, 0, 64, 5, 112, 0,
        64, 2, 114, 0, 64, 1, 114, 0, 64, 1, 114, 0, 64, 3, 113, 0,
        0, 34, 0, 0, 4, 119, 64, 0, 39, 102, 115, 0, 70, 0, 86, 0,
        84, 0, 53, 0, 84, 0, 16, 0, 86, 0, 0, 0, 55, 81, 0, 0,
        0, 0, 0, 0, 20, 68, 68, 83, 39, 119, 119, 117, 2, 20, 114, 33,
        0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0,
        0, 0, 0, 0, 0, 69, 0, 3, 0, 86, 0, 4, 0, 85, 0, 4,
        0, 85, 0, 4, 0, 85, 0, 4, 0, 85, 0, 4, 0, 85, 0, 4,
        0, 0, 0, 0, 64, 68, 0, 0, 80, 71, 16, 0, 80, 39, 32, 1,
        80, 6, 64, 2, 80, 6, 80, 3, 80, 5, 96, 4, 80, 3, 112, 6,
        0, 0, 0, 0, 67, 7, 32, 36, 116, 7, 48, 86, 114, 7, 48, 86,
        113, 7, 32, 86, 112, 7, 35, 86, 96, 7, 36, 85, 80, 7, 37, 53,
        0, 0, 0, 0, 4, 112, 101, 0, 5, 112, 71, 0, 4, 112, 23, 48,
        4, 112, 5, 80, 36, 112, 4, 96, 52, 112, 2, 112, 68, 112, 0, 115,
        0, 0, 0, 0, 1, 98, 0, 0, 3, 112, 0, 0, 5, 80, 0, 0,
        6, 48, 0, 0, 23, 32, 0, 0, 55, 0, 0, 0, 85, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 6,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 36, 65, 0, 0, 119, 119, 32, 0, 81, 23, 80, 0,
        0, 0, 0, 0, 68, 0, 0, 0, 85, 0, 0, 0, 85, 0, 0, 0,
        85, 0, 0, 0, 85, 3, 16, 0, 86, 87, 115, 0, 71, 82, 103, 16,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 66, 0, 0, 87, 119, 80, 3, 116, 3, 98,
        0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 7, 0, 0, 0, 7,
        0, 0, 0, 7, 0, 0, 34, 7, 0, 5, 119, 87, 0, 55, 66, 103,
        0, 0, 0, 0, 48, 0, 0, 0, 48, 0, 0, 0, 48, 0, 0, 0,
        48, 0, 0, 0, 48, 0, 3, 66, 48, 0, 87, 119, 48, 2, 115, 4,
        0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 23, 0, 0, 0, 39,
        0, 0, 0, 39, 0, 0, 0, 39, 48, 0, 119, 119, 112, 0, 85, 87,
        17, 0, 0, 0, 116, 0, 0, 0, 98, 0, 0, 0, 32, 0, 0, 3,
        32, 0, 0, 87, 32, 0, 3, 117, 119, 112, 5, 96, 85, 80, 6, 64,
        0, 0, 0, 0, 0, 0, 0, 68, 0, 0, 0, 87, 66, 2, 0, 87,
        119, 86, 0, 87, 20, 118, 0, 87, 0, 86, 0, 87, 0, 70, 0, 71,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 3, 32, 0, 0, 87, 117, 0, 0, 82, 87, 16, 0,
        0, 0, 0, 0, 3, 96, 0, 0, 4, 112, 0, 0, 3, 80, 0, 0,
        0, 0, 0, 0, 1, 32, 0, 0, 4, 112, 0, 0, 4, 112, 0, 0,
        0, 0, 0, 0, 83, 0, 0, 0, 115, 0, 0, 0, 115, 0, 0, 0,
        115, 0, 0, 0, 115, 0, 17, 0, 115, 1, 115, 0, 115, 6, 96, 0,
        0, 0, 0, 0, 0, 0, 99, 0, 0, 0, 116, 0, 0, 0, 116, 0,
        0, 0, 116, 0, 0, 0, 116, 0, 0, 0, 116, 0, 0, 0, 116, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 19, 0, 48, 6, 119, 87, 116, 7, 100, 117, 87,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 2, 17, 68, 0, 7, 87, 119, 16, 7, 116, 4,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 52, 80, 0, 6, 119, 114, 0, 71, 48,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 34, 4,
        0, 0, 70, 87, 32, 0, 71, 98, 116, 0, 71, 16, 71, 32, 71, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0,
        119, 16, 0, 0, 55, 80, 0, 7, 5, 96, 0, 7, 3, 114, 0, 7,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 80, 20, 64, 0, 82, 119, 112, 2, 119, 99, 16, 22,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 36, 65, 0, 0, 119, 119, 16, 0, 81, 23, 64, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 23, 48, 0, 0, 23, 48, 0,
        0, 23, 48, 0, 19, 55, 51, 48, 23, 119, 119, 112, 20, 71, 68, 64,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 2, 32, 0, 33, 5, 96, 0, 115, 5, 96, 0, 115,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 2, 32, 0, 2, 4, 113, 0, 23, 1, 115, 0, 55,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 32, 98, 4, 80, 64, 100, 4, 80, 16, 85, 5, 112,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 48, 0,
        0, 3, 116, 0, 37, 0, 102, 0, 53, 0, 71, 16, 69, 0, 39, 48,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 48, 0, 0,
        23, 48, 0, 0, 55, 16, 0, 0, 87, 0, 0, 0, 101, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 49, 0, 0,
        3, 118, 0, 0, 6, 118, 0, 0, 3, 118, 0, 0, 1, 115, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 21, 16, 0, 0, 87, 80, 0, 0, 87, 80, 0,
        0, 0, 115, 7, 0, 2, 113, 5, 0, 3, 115, 37, 0, 4, 119, 119,
        0, 5, 100, 69, 0, 6, 48, 0, 0, 39, 32, 0, 0, 87, 0, 0,
        48, 0, 71, 119, 80, 0, 71, 85, 96, 0, 69, 0, 112, 0, 70, 0,
        114, 0, 70, 0, 115, 0, 69, 0, 100, 0, 70, 0, 86, 0, 71, 119,
        115, 0, 39, 32, 118, 0, 39, 32, 23, 48, 39, 48, 5, 80, 7, 64,
        4, 80, 6, 80, 5, 80, 4, 112, 39, 48, 2, 117, 119, 16, 0, 87,
        0, 0, 5, 80, 0, 0, 5, 80, 0, 0, 5, 80, 0, 0, 5, 80,
        0, 0, 5, 80, 0, 36, 5, 80, 1, 101, 5, 96, 103, 114, 5, 119,
        0, 7, 80, 5, 0, 7, 80, 5, 0, 23, 80, 5, 0, 39, 48, 5,
        0, 71, 16, 5, 0, 117, 0, 5, 21, 115, 0, 5, 119, 96, 0, 5,
        118, 103, 64, 2, 118, 103, 64, 2, 80, 0, 0, 2, 80, 0, 0, 1,
        80, 0, 0, 0, 80, 0, 0, 0, 96, 17, 16, 0, 119, 119, 114, 0,
        114, 4, 68, 16, 114, 7, 119, 48, 114, 3, 70, 48, 116, 0, 6, 48,
        101, 0, 22, 48, 71, 0, 6, 48, 39, 64, 71, 16, 5, 118, 116, 0,
        0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0,
        0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 4, 112, 0,
        0, 85, 0, 0, 0, 85, 0, 0, 0, 85, 0, 0, 0, 85, 0, 0,
        0, 85, 0, 0, 0, 85, 0, 0, 0, 86, 34, 34, 0, 87, 119, 118,
        0, 83, 97, 54, 0, 83, 98, 69, 0, 82, 83, 84, 0, 82, 69, 83,
        0, 82, 54, 98, 0, 82, 39, 96, 0, 83, 7, 96, 0, 83, 7, 96,
        71, 0, 69, 39, 71, 0, 69, 7, 71, 0, 70, 6, 71, 0, 70, 3,
        71, 0, 70, 2, 71, 0, 70, 0, 71, 0, 69, 0, 87, 0, 70, 0,
        4, 80, 39, 32, 51, 80, 39, 32, 84, 80, 39, 32, 100, 80, 23, 64,
        118, 80, 6, 80, 103, 80, 5, 112, 71, 80, 2, 116, 39, 80, 0, 103,
        0, 117, 0, 71, 0, 117, 0, 71, 1, 117, 0, 71, 2, 115, 0, 71,
        3, 113, 0, 71, 5, 96, 0, 71, 39, 64, 0, 71, 119, 0, 0, 70,
        0, 23, 32, 5, 68, 103, 0, 5, 119, 115, 0, 5, 51, 32, 0, 5,
        0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5,
        81, 39, 96, 0, 119, 119, 32, 0, 99, 101, 0, 0, 64, 55, 16, 0,
        64, 23, 48, 0, 64, 6, 80, 0, 64, 3, 112, 0, 64, 2, 115, 0,
        5, 119, 64, 0, 0, 71, 115, 0, 0, 2, 118, 0, 0, 0, 55, 32,
        49, 0, 23, 32, 115, 0, 23, 32, 87, 16, 87, 16, 39, 118, 115, 0,
        0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0,
        0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0, 0, 3, 112, 0,
        0, 85, 0, 4, 0, 85, 0, 4, 0, 85, 0, 4, 0, 85, 0, 4,
        0, 85, 0, 4, 0, 71, 0, 6, 0, 39, 48, 39, 0, 6, 117, 119,
        80, 2, 113, 6, 80, 1, 114, 7, 80, 0, 100, 23, 80, 0, 101, 55,
        80, 0, 70, 70, 64, 0, 55, 100, 48, 0, 39, 115, 0, 0, 7, 114,
        64, 7, 54, 36, 32, 7, 54, 19, 16, 7, 70, 2, 0, 7, 85, 0,
        0, 7, 101, 0, 0, 5, 116, 0, 0, 5, 115, 0, 0, 5, 113, 0,
        84, 112, 0, 86, 100, 112, 0, 55, 101, 112, 0, 23, 102, 112, 0, 7,
        87, 112, 0, 6, 87, 80, 0, 7, 71, 80, 0, 6, 55, 80, 0, 7,
        99, 0, 0, 0, 113, 0, 0, 0, 80, 0, 0, 0, 64, 0, 0, 0,
        64, 0, 0, 0, 64, 0, 0, 0, 64, 0, 0, 0, 64, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3,
        0, 0, 0, 6, 0, 0, 0, 39, 0, 0, 0, 39, 0, 0, 0, 22,
        0, 5, 96, 0, 0, 39, 80, 0, 38, 119, 80, 0, 119, 37, 96, 0,
        80, 4, 96, 0, 16, 5, 96, 0, 32, 39, 96, 0, 117, 118, 116, 0,
        87, 0, 23, 48, 85, 0, 6, 64, 85, 0, 5, 80, 85, 0, 5, 80,
        85, 0, 5, 80, 85, 0, 7, 48, 71, 32, 55, 32, 87, 118, 118, 0,
        6, 80, 0, 34, 23, 48, 0, 0, 39, 32, 0, 0, 39, 16, 0, 0,
        39, 32, 0, 0, 6, 64, 0, 16, 4, 114, 1, 98, 1, 119, 87, 97,
        0, 101, 0, 23, 1, 115, 0, 7, 2, 114, 0, 7, 2, 113, 0, 7,
        2, 114, 0, 7, 0, 99, 0, 7, 0, 71, 16, 71, 0, 23, 118, 119,
        48, 5, 80, 0, 48, 37, 48, 0, 48, 54, 68, 103, 48, 54, 119, 101,
        48, 38, 64, 0, 48, 5, 64, 0, 48, 3, 113, 1, 64, 0, 119, 87,
        114, 0, 0, 39, 99, 0, 0, 39, 115, 0, 0, 39, 65, 0, 0, 39,
        0, 0, 0, 39, 49, 0, 0, 39, 115, 0, 0, 39, 112, 0, 0, 39,
        32, 0, 6, 64, 32, 0, 6, 80, 32, 0, 4, 115, 32, 0, 0, 103,
        32, 0, 0, 20, 32, 0, 0, 0, 32, 0, 3, 83, 32, 0, 3, 119,
        0, 70, 0, 87, 0, 70, 0, 87, 2, 118, 0, 87, 119, 102, 0, 87,
        82, 70, 0, 87, 0, 86, 0, 87, 53, 116, 0, 87, 119, 80, 0, 86,
        0, 23, 48, 0, 0, 7, 48, 0, 0, 7, 48, 0, 0, 7, 48, 0,
        0, 7, 48, 0, 0, 7, 48, 0, 0, 7, 48, 0, 0, 7, 64, 0,
        4, 112, 0, 0, 4, 112, 0, 0, 4, 112, 0, 0, 4, 112, 0, 0,
        4, 112, 0, 0, 4, 112, 0, 0, 4, 112, 0, 0, 4, 112, 0, 0,
        115, 39, 16, 0, 116, 100, 0, 0, 119, 114, 0, 0, 119, 117, 0, 0,
        117, 55, 32, 0, 115, 7, 80, 0, 115, 3, 113, 0, 116, 0, 118, 0,
        0, 0, 116, 0, 0, 0, 116, 0, 0, 0, 116, 0, 0, 0, 116, 0,
        0, 0, 116, 0, 0, 0, 116, 0, 0, 0, 116, 0, 0, 0, 116, 0,
        7, 48, 114, 7, 7, 32, 114, 7, 7, 32, 114, 7, 7, 32, 114, 7,
        7, 32, 114, 7, 7, 32, 114, 7, 7, 32, 114, 7, 7, 32, 114, 7,
        48, 7, 96, 0, 48, 7, 80, 0, 48, 7, 80, 0, 48, 7, 80, 0,
        48, 7, 80, 0, 48, 7, 80, 0, 48, 7, 80, 0, 48, 7, 80, 0,
        115, 0, 101, 0, 115, 1, 115, 0, 115, 2, 114, 0, 115, 2, 113, 0,
        115, 2, 114, 0, 115, 0, 100, 0, 115, 0, 87, 16, 116, 0, 23, 117,
        7, 64, 71, 0, 5, 80, 71, 0, 3, 96, 71, 32, 3, 96, 71, 117,
        4, 96, 71, 71, 6, 80, 71, 0, 39, 48, 71, 0, 118, 0, 71, 0,
        2, 115, 0, 7, 4, 113, 0, 7, 6, 96, 0, 7, 103, 48, 0, 7,
        116, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 7, 0, 0, 0, 7,
        118, 48, 0, 38, 80, 0, 0, 21, 80, 0, 0, 3, 80, 0, 0, 0,
        80, 0, 0, 0, 80, 0, 0, 50, 80, 0, 0, 55, 80, 0, 0, 5,
        48, 1, 16, 0, 97, 0, 0, 0, 119, 81, 0, 0, 38, 119, 16, 0,
        0, 39, 64, 0, 0, 5, 97, 0, 48, 5, 97, 0, 118, 103, 48, 0,
        0, 23, 64, 0, 0, 23, 64, 0, 0, 23, 64, 0, 0, 23, 64, 0,
        0, 23, 64, 0, 0, 23, 64, 0, 0, 22, 116, 0, 0, 4, 118, 64,
        5, 96, 0, 115, 5, 96, 0, 115, 5, 96, 0, 115, 5, 96, 0, 115,
        5, 96, 0, 115, 5, 96, 0, 115, 4, 114, 5, 115, 1, 119, 119, 115,
        0, 101, 0, 86, 0, 71, 0, 116, 0, 55, 0, 115, 0, 23, 34, 113,
        0, 7, 68, 112, 0, 5, 102, 80, 0, 3, 119, 48, 0, 1, 87, 16,
        0, 54, 6, 96, 0, 54, 6, 97, 0, 22, 37, 98, 0, 6, 69, 84,
        0, 5, 84, 69, 0, 4, 116, 38, 0, 3, 115, 39, 0, 2, 114, 7,
        84, 0, 7, 80, 83, 0, 5, 98, 98, 0, 3, 117, 81, 0, 1, 119,
        80, 0, 0, 71, 80, 0, 0, 87, 64, 2, 36, 117, 64, 5, 87, 97,
        115, 0, 0, 0, 114, 0, 0, 0, 96, 0, 0, 0, 80, 0, 0, 0,
        32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 16, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 21, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        53, 0, 54, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        98, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        119, 48, 4, 102, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        100, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        102, 102, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 87, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 70, 102, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 66, 5, 64, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        70, 0, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        6, 64, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        98, 0, 0, 53, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        48, 0, 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 119, 49, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 103, 98, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 5, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 5, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        23, 80, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        102, 64, 83, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        50, 54, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 21, 100, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 102, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        32, 0, 21, 101, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        16, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        16, 0, 0, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        83, 0, 0, 51, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 4, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        3, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        66, 0, 37, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 52, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        5, 32, 98, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        32, 3, 48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        66, 0, 1, 86, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        65, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        70, 99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 55, 112, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 38, 98, 66, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 71, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 2, 97, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        48, 3, 85, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, -1, 9, 0, -1, 18, 0,
        -1, 27, 0, -1, 36, 0, -1, 45,
        0, -1, 54, 0, -1, 63, 0, -1,
        72, 0, -1, 81, 0, -1, 90, 0,
        -1, 99, 0, -1, 108, 0, -1, 117,
        0, -1, 126, 0, -1, 135, 0, -1,
        144, 0, -1, 153, 0, -1, 162, 0,
        -1, 171, 0, -1, 180, 0, -1, 189,
        0, -1, 198, 0, -1, 207, 0, -1,
        216, 0, -1, 225, 0, -1, 234, 0,
        -1, 243, 0, -1, 252, 0, -1, 261,
        0, -1, 270, 0, -1, 279, 0, -1,
        288, 0, -1, 297, 0, -1, 306, 0,
        -1, 315, 0, -1, 0, 18, -1, 9,
        18, -1, 18, 18, -1, 27, 18, -1,
        36, 18, -1, 45, 18, -1, 54, 18,
        -1, 63, 18, -1, 72, 18, -1, 81,
        18, -1, 90, 18, -1, 99, 18, -1,
        108, 18, -1, 117, 18, -1, 126, 18,
        -1, 135, 18, -1, 144, 18, -1, 153,
        18, -1, 162, 18, -1, 171, 18, -1,
        180, 18, -1, 189, 18, -1, 198, 18,
        -1, 207, 18, -1, 216, 18, -1, 225,
        18, -1, 234, 18, -1, 243, 18, -1,
        252, 18, -1, 261, 18, -1, 270, 18,
        -1, 279, 18, -1, 288, 18, -1, 297,
        18, -1, 306, 18, -1, 315, 18, -1,
        0, 36, -1, 9, 36, -1, 18, 36,
        -1, 27, 36, -1, 36, 36, -1, 45,
        36, -1, 54, 36, -1, 63, 36, -1,
        72, 36, -1, 81, 36, -1, 90, 36,
        -1, 99, 36, -1, 108, 36, -1, 117,
        36, -1, 126, 36, -1, 135, 36, -1,
        144, 36, -1, 153, 36, -1, 162, 36,
        -1, 171, 36, -1, 180, 36, -1, 189,
        36, -1, 198, 36, -1, 207, 36, -1,
        216, 36, -1, 225, 36, -1, 234, 36,
        -1, 243, 36, -1, 252, 36, -1, 261,
        36, -1, 270, 36, -1, 279, 36, -1,
        288, 36, -1, 297, 36, -1, 306, 36,
        -1, 315, 36, -1, 0, 54, -1, 9,
        54, -1, 18, 54, -1, 27, 54, -1,
        36, 54, -1, 45, 54, -1, 54, 54,
        -1, 63, 54, -1, 72, 54, -1, 81,
        54, -1, 90, 54, -1, 99, 54, -1,
        108, 54, -1, 117, 54, -1, 126, 54,
        -1, 135, 54, -1, 144, 54, -1, 153,
        54, -1, 162, 54, -1, 171, 54, -1,
        180, 54, -1, 189, 54, -1, 198, 54,
        -1, 207, 54, -1, 216, 54, -1, 225,
        54, -1, 234, 54, -1, 243, 54, -1,
        252, 54, -1, 261, 54, -1, 270, 54,
        -1, 279, 54, -1, 288, 54, -1, 297,
        54, -1, 306, 54, -1, 315, 54, -1,
        0, 72, -1, 9, 72, -1, 18, 72,
        -1, 27, 72, -1, 36, 72, -1, 45,
        72, -1, 54, 72, -1, 63, 72, -1,
        72, 72, -1, 81, 72, -1, 90, 72,
        -1, 99, 72, -1, 108, 72, -1, 117,
        72, -1, 126, 72, -1, 135, 72, -1,
        144, 72, -1, 153, 72, -1, 162, 72,
        -1, 171, 72, -1, 180, 72, -1, 189,
        72, -1, 198, 72, -1, 207, 72, -1,
        216, 72, -1, 225, 72, -1, 234, 72,
        -1, 243, 72, -1, 252, 72, -1, 261,
        72, -1, 270, 72, -1, 279, 72, -1,
        288, 72, -1, 297, 72, -1, 306, 72,
        -1, 315, 72, -1, 0, 0, 0, 0,
    },
    {
        0, 0, 9, 0, 18, 0, 27, 0,
        36, 0, 45, 0, 54, 0, 63, 0,
        72, 0, 81, 0, 90, 0, 99, 0,
        108, 0, 117, 0, 126, 0, 135, 0,
        144, 0, 153, 0, 162, 0, 171, 0,
        180, 0, 189, 0, 198, 0, 207, 0,
        216, 0, 225, 0, 234, 0, 243, 0,
        252, 0, 261, 0, 270, 0, 279, 0,
        288, 0, 297, 0, 306, 0, 315, 0,
        324, 0, 333, 0, 342, 0, 351, 0,
        360, 0, 369, 0, 378, 0, 387, 0,
        396, 0, 405, 0, 414, 0, 0, 18,
        9, 18, 18, 18, 27, 18, 36, 18,
        45, 18, 54, 18, 63, 18, 72, 18,
        81, 18, 90, 18, 99, 18, 108, 18,
        117, 18, 126, 18, 135, 18, 144, 18,
        153, 18, 162, 18, 171, 18, 180, 18,
        189, 18, 198, 18, 207, 18, 216, 18,
        225, 18, 234, 18, 243, 18, 252, 18,
        261, 18, 270, 18, 279, 18, 288, 18,
        297, 18, 306, 18, 315, 18, 324, 18,
        333, 18, 342, 18, 351, 18, 360, 18,
        369, 18, 378, 18, 387, 18, 396, 18,
        405, 18, 414, 18, 0, 0, 0, 0,
        32769, 6144, 16, 256, 4389, 64, 9216, 16129,
        29, 512, 7718, 77, 9472, 19458, 26, 768,
        6951, 74, 9728, 18692, 5, 1280, 1577, 53,
        10240, 13317, 30, 1536, 7978, 78, 10496, 19718,
        38, 1792, 10027, 86, 10752, 21767, 24, 2048,
        6444, 72, 11008, 18185, 4, 2560, 1326, 52,
        11520, 13066, 35, 2816, 9263, 83, 11776, 21003,
        41, 3072, 10800, 89, 12032, 22540, 26, 3328,
        6961, 74, 12288, 18701, 37, 3584, 9778, 85,
        12544, 21519, 30, 4096, 7988, 78, 13056, 19728,
        38, 4352, 10037, 86, 13312, 21778, 35, 4864,
        9271, 83, 13824, 21011, 36, 5120, 9528, 84,
        14080, 21268, 26, 5376, 6969, 74, 14336, 18709,
        34, 5632, 9018, 82, 14592, 20758, 1, 5888,
        571, 49, 14848, 12324, 8, 9472, 2377, 56,
        18432, 14117, 27, 9728, 7242, 75, 18688, 18983,
        43, 10240, 11340, 91, 19200, 23080, 35, 10496,
        9293, 83, 19456, 21033, 40, 10752, 10574, 88,
        19712, 22315, 42, 11264, 11088, 90, 20224, 22828,
        22, 11520, 5969, 70, 20480, 17709, 34, 11776,
        9042, 82, 20736, 20782, 39, 12032, 10323, 87,
        20992, 22064, 39, 12544, 10325, 87, 21504, 22065,
        35, 12800, 9302, 83, 21760, 21043, 24, 13312,
        6488, 72, 22272, 18228, 35, 13568, 9305, 83,
        22528, 21045, 34, 13824, 9050, 82, 22784, 20790,
        39, 14080, 10331, 87, 23040, 22071, 30, 14336,
        8028, 78, 23296, 19768, 34, 14592, 9053, 82,
        23552, 20793, 40, 14848, 10590, 88, 23808, 22330,
        26, 15104, 7007, 74, 24064, 18748, 39, 15616,
        10337, 87, 24576, 22077, 29, 15872, 7778, 77,
        24832, 19518, 26, 16128, 7011, 74, 25088, 18752,
        28, 16640, 7525, 76, 25600, 19265, 22, 16896,
        5990, 70, 25856, 17730, 33, 17152, 8807, 81,
        26112, 20547, 26, 17408, 7016, 74, 26368, 18756,
        0, 17664, 361, 48, 26624, 12104, 36, 18688,
        9581, 84, 27648, 21321, 32, 18944, 8558, 80,
        27904, 20298, 26, 19200, 7023, 74, 28160, 18763,
        22, 19456, 6000, 70, 28416, 17740, 38, 19712,
        10097, 86, 28672, 21837, 26, 19968, 7026, 74,
        28928, 18767, 24, 20480, 6516, 72, 29440, 18256,
        32, 20736, 8565, 80, 29696, 20305, 35, 20992,
        9334, 83, 29952, 21074, 38, 21248, 10103, 86,
        30208, 21843, 26, 21504, 7032, 74, 30464, 18773,
        39, 22016, 10362, 87, 30976, 22102, 29, 22272,
        7803, 77, 31232, 19543, 26, 22528, 7036, 74,
        31488, 18777, 5, 23040, 1662, 53, 32000, 13402,
        30, 23296, 8063, 78, 32256, 19803, 38, 23552,
        10112, 86, 32512, 21852, 24, 23808, 6529, 72,
        32768, 18270, 4, 24320, 1411, 52, 33280, 13151,
        35, 24576, 9348, 83, 33536, 21088, 41, 24832,
        10885, 89, 33792, 22625, 26, 25088, 7046, 74,
        34048, 18786, 37, 25344, 9863, 85, 34304, 21603,
        1, 25600, 648, 49, 34560, 12288, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 47104, 13, 256, 3621, 61, 9216, 15361,
        32, 512, 8486, 80, 9472, 20226, 26, 768,
        6951, 74, 9728, 18691, 22, 1024, 5928, 70,
        9984, 17668, 38, 1280, 10025, 86, 10240, 21765,
        26, 1536, 6954, 74, 10496, 18695, 30, 2048,
        7980, 78, 11008, 19720, 34, 2304, 9005, 82,
        11264, 20745, 38, 2560, 10030, 86, 11520, 21770,
        26, 2816, 6959, 74, 11776, 18699, 37, 3072,
        9776, 85, 12032, 21516, 39, 3328, 10289, 87,
        12288, 22030, 39, 3840, 10291, 87, 12800, 22031,
        29, 4096, 7732, 77, 13056, 19472, 26, 4352,
        6965, 74, 13312, 18724, 10, 9472, 2889, 58,
        18432, 14629, 22, 9728, 5962, 70, 18688, 17702,
        37, 9984, 9803, 85, 18944, 21543, 30, 10240,
        8012, 78, 19200, 19752, 35, 10496, 9293, 83,
        19456, 21034, 15, 11008, 4175, 63, 19968, 15915,
        40, 11264, 10576, 88, 20224, 22316, 36, 11520,
        9553, 84, 20480, 21293, 26, 11776, 6994, 74,
        20736, 18734, 37, 12032, 9811, 85, 20992, 21551,
        38, 12288, 10068, 86, 21248, 21808, 39, 12544,
        10325, 87, 21504, 22065, 22, 12800, 5974, 70,
        21760, 17714, 37, 13056, 9815, 85, 22016, 21556,
        3, 13568, 1113, 51, 22528, 12853, 22, 13824,
        5978, 70, 22784, 17718, 38, 14080, 10075, 86,
        23040, 21815, 26, 14336, 7004, 74, 23296, 18744,
        23, 14592, 6237, 71, 23552, 17977, 22, 14848,
        5982, 70, 23808, 17722, 32, 15104, 8543, 80,
        24064, 20283, 32, 15360, 8544, 80, 24320, 20285,
        7, 15872, 2146, 55, 24832, 13886, 22, 16128,
        5987, 70, 25088, 17727, 33, 16384, 8804, 81,
        25344, 20544, 26, 16640, 7013, 74, 25600, 18754,
        5, 17152, 1639, 53, 26112, 13379, 30, 17408,
        8040, 78, 26368, 19780, 38, 17664, 10089, 86,
        26624, 21829, 24, 17920, 6506, 72, 26880, 18246,
        1, 18176, 619, 49, 27136, 12288, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        32769, 28672, 16, 256, 4389, 64, 9216, 16129,
        29, 512, 7718, 77, 9472, 19458, 26, 768,
        6951, 74, 9728, 18692, 7, 1280, 2089, 55,
        10240, 13829, 22, 1536, 5930, 70, 10496, 17670,
        33, 1792, 8747, 81, 10752, 20487, 26, 2048,
        6956, 74, 11008, 18697, 5, 2560, 1582, 53,
        11520, 13322, 30, 2816, 7983, 78, 11776, 19723,
        38, 3072, 10032, 86, 12032, 21772, 24, 3328,
        6449, 72, 12288, 18190, 24, 3840, 6451, 72,
        12800, 18191, 35, 4096, 9268, 83, 13056, 21008,
        40, 4352, 10549, 88, 13312, 22289, 32, 4608,
        8502, 80, 13568, 20242, 25, 4864, 6711, 73,
        13824, 18452, 34, 5376, 9017, 82, 14336, 20757,
        35, 5632, 9274, 83, 14592, 21014, 39, 5888,
        10299, 87, 14848, 22040, 23, 6400, 6205, 71,
        15360, 17945, 26, 6656, 6974, 74, 15616, 18724,
        37, 9472, 9801, 85, 18432, 21541, 26, 9728,
        6986, 74, 18688, 18726, 22, 9984, 5963, 70,
        18944, 17703, 25, 10240, 6732, 73, 19200, 18472,
        1, 10496, 589, 49, 19456, 12330, 13, 11008,
        3663, 61, 19968, 15403, 32, 11264, 8528, 80,
        20224, 20268, 26, 11520, 6993, 74, 20480, 18733,
        22, 11776, 5970, 70, 20736, 17710, 38, 12032,
        10067, 86, 20992, 21807, 26, 12288, 6996, 74,
        21248, 18737, 37, 12800, 9814, 85, 21760, 21554,
        26, 13056, 6999, 74, 22016, 18739, 22, 13312,
        5976, 70, 22272, 17716, 25, 13568, 6745, 73,
        22528, 18486, 39, 14080, 10331, 87, 23040, 22071,
        29, 14336, 7772, 77, 23296, 19512, 26, 14592,
        7005, 74, 23552, 18746, 11, 15104, 3167, 59,
        24064, 14907, 30, 15360, 8032, 78, 24320, 19772,
        34, 15616, 9057, 82, 24576, 20797, 39, 15872,
        10338, 87, 24832, 22078, 26, 16128, 7011, 74,
        25088, 18751, 34, 16384, 9060, 82, 25344, 20800,
        25, 16640, 6757, 73, 25600, 18497, 35, 16896,
        9318, 83, 25856, 21064, 7, 18688, 2157, 55,
        27648, 13897, 22, 18944, 5998, 70, 27904, 17738,
        33, 19200, 8815, 81, 28160, 20555, 26, 19456,
        7024, 74, 28416, 18764, 4, 19712, 1393, 52,
        28672, 13133, 40, 19968, 10610, 88, 28928, 22350,
        23, 20224, 6259, 71, 29184, 17999, 26, 20480,
        7028, 74, 29440, 18769, 8, 20992, 2422, 56,
        29952, 14162, 34, 21248, 9079, 82, 30208, 20819,
        38, 21504, 10104, 86, 30464, 21844, 39, 21760,
        10361, 87, 30720, 22101, 37, 22016, 9850, 85,
        30976, 21590, 40, 22272, 10619, 88, 31232, 22359,
        24, 22528, 6524, 72, 31488, 18264, 39, 22784,
        10365, 87, 31744, 22105, 30, 23040, 8062, 78,
        32000, 19802, 35, 23296, 9343, 83, 32256, 21083,
        34, 23552, 9088, 82, 32512, 20829, 3, 24064,
        1154, 51, 33024, 12894, 35, 24320, 9347, 83,
        33280, 21087, 35, 24576, 9348, 83, 33536, 21088,
        31, 24832, 8325, 79, 33792, 20065, 32, 25088,
        8582, 80, 34048, 20322, 26, 25344, 7047, 74,
        34304, 18787, 39, 25600, 10376, 87, 34560, 22124,
        27, 27904, 7313, 75, 36864, 19053, 35, 28160,
        9362, 83, 37120, 21102, 37, 28416, 9875, 85,
        37376, 21616, 33, 28928, 8853, 81, 37888, 20593,
        35, 29184, 9366, 83, 38144, 21106, 37, 29440,
        9879, 85, 38400, 21619, 26, 29696, 7064, 74,
        38656, 18805, 30, 30208, 8090, 78, 39168, 19830,
        34, 30464, 9115, 82, 39424, 20855, 27, 30720,
        7324, 75, 39680, 19064, 35, 30976, 9373, 83,
        39936, 21113, 37, 31232, 9886, 85, 40192, 21626,
        33, 31488, 8863, 81, 40448, 20603, 22, 31744,
        6048, 70, 40704, 17788, 39, 32000, 10401, 87,
        40960, 22141, 30, 32256, 8098, 78, 41216, 19838,
        35, 32512, 9379, 83, 41472, 21119, 34, 32768,
        9124, 82, 41728, 20864, 1, 33024, 677, 49,
        41984, 12288, 0, 0, 0, 0, 0, 0,
        32769, 40960, 2, 256, 805, 50, 9216, 12545,
        34, 512, 8998, 82, 9472, 20739, 26, 1024,
        6952, 74, 9984, 18692, 37, 1280, 9769, 85,
        10240, 21509, 37, 1536, 9770, 85, 10496, 21510,
        35, 1792, 9259, 83, 10752, 20999, 37, 2048,
        9772, 85, 11008, 21513, 29, 2560, 7726, 77,
        11520, 19466, 22, 2816, 5935, 70, 11776, 17675,
        38, 3072, 10032, 86, 12032, 21773, 35, 3584,
        9266, 83, 12544, 21006, 24, 3840, 6451, 72,
        12800, 18191, 24, 4096, 6452, 72, 13056, 18192,
        40, 4352, 10549, 88, 13312, 22289, 37, 4608,
        9782, 85, 13568, 21522, 37, 4864, 9783, 85,
        13824, 21523, 26, 5120, 6968, 74, 14080, 18708,
        25, 5376, 6713, 73, 14336, 18453, 1, 5632,
        570, 49, 14592, 12324, 16, 9472, 4425, 64,
        18432, 16165, 40, 9728, 10570, 88, 18688, 22310,
        37, 9984, 9803, 85, 18944, 21543, 34, 10240,
        9036, 82, 19200, 20777, 39, 10752, 10318, 87,
        19712, 22058, 29, 11008, 7759, 77, 19968, 19499,
        26, 11264, 6992, 74, 20224, 18733, 36, 11776,
        9554, 84, 20736, 21294, 35, 12032, 9299, 83,
        20992, 21039, 42, 12288, 11092, 90, 21248, 22832,
        26, 12544, 6997, 74, 21504, 18737, 37, 12800,
        9814, 85, 21760, 21555, 35, 13312, 9304, 83,
        22272, 21044, 27, 13568, 7257, 75, 22528, 18997,
        27, 13824, 7258, 75, 22784, 18999, 22, 14336,
        5980, 70, 23296, 17720, 34, 14592, 9053, 82,
        23552, 20793, 25, 14848, 6750, 73, 23808, 18491,
        37, 15360, 9824, 85, 24320, 21564, 26, 15616,
        7009, 74, 24576, 18749, 27, 15872, 7266, 75,
        24832, 19006, 26, 16128, 7011, 74, 25088, 18751,
        37, 16384, 9828, 85, 25344, 21569, 39, 16896,
        10342, 87, 25856, 22082, 35, 17152, 9319, 83,
        26112, 21060, 39, 17664, 10345, 87, 26624, 22085,
        29, 17920, 7786, 77, 26880, 19526, 26, 18176,
        7019, 74, 27136, 18760, 11, 18688, 3181, 59,
        27648, 14921, 30, 18944, 8046, 78, 27904, 19786,
        34, 19200, 9071, 82, 28160, 20811, 39, 19456,
        10352, 87, 28416, 22092, 26, 19712, 7025, 74,
        28672, 18765, 34, 19968, 9074, 82, 28928, 20814,
        25, 20224, 6771, 73, 29184, 18511, 35, 20480,
        9332, 83, 29440, 21073, 7, 20992, 2166, 55,
        29952, 13906, 22, 21248, 6007, 70, 30208, 17747,
        33, 21504, 8824, 81, 30464, 20564, 26, 21760,
        7033, 74, 30720, 18773, 4, 22016, 1402, 52,
        30976, 13142, 40, 22272, 10619, 88, 31232, 22359,
        23, 22528, 6268, 71, 31488, 18008, 26, 22784,
        7037, 74, 31744, 18778, 8, 23296, 2431, 56,
        32256, 14171, 34, 23552, 9088, 82, 32512, 20828,
        38, 23808, 10113, 86, 32768, 21853, 39, 24064,
        10370, 87, 33024, 22110, 37, 24320, 9859, 85,
        33280, 21599, 40, 24576, 10628, 88, 33536, 22368,
        24, 24832, 6533, 72, 33792, 18273, 39, 25088,
        10374, 87, 34048, 22114, 30, 25344, 8071, 78,
        34304, 19811, 35, 25600, 9352, 83, 34560, 21092,
        34, 25856, 9097, 82, 34816, 20844, 3, 27904,
        1169, 51, 36864, 12909, 35, 28160, 9362, 83,
        37120, 21102, 35, 28416, 9363, 83, 37376, 21103,
        31, 28672, 8340, 79, 37632, 20080, 32, 28928,
        8597, 80, 37888, 20337, 26, 29184, 7062, 74,
        38144, 18802, 39, 29440, 10391, 87, 38400, 22132,
        27, 29952, 7321, 75, 38912, 19061, 35, 30208,
        9370, 83, 39168, 21110, 37, 30464, 9883, 85,
        39424, 21624, 27, 30976, 7325, 75, 39936, 19065,
        40, 31232, 10654, 88, 40192, 22394, 37, 31488,
        9887, 85, 40448, 21627, 39, 31744, 10400, 87,
        40704, 22140, 29, 32000, 7841, 77, 40960, 19581,
        26, 32256, 7074, 74, 41216, 18814, 37, 32512,
        9891, 85, 41472, 21632, 30, 33024, 8101, 78,
        41984, 19841, 34, 33280, 9126, 82, 42240, 20866,
        38, 33536, 10151, 86, 42496, 21891, 39, 33792,
        10408, 87, 42752, 22148, 37, 34048, 9897, 85,
        43008, 21637, 40, 34304, 10666, 88, 43264, 22406,
        24, 34560, 6571, 72, 43520, 18311, 39, 34816,
        10412, 87, 43776, 22152, 30, 35072, 8109, 78,
        44032, 19849, 35, 35328, 9390, 83, 44288, 21130,
        34, 35584, 9135, 82, 44544, 20875, 38, 35840,
        10160, 86, 44800, 21900, 1, 36096, 689, 49,
        45056, 12288, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 23552, 16, 256, 4389, 64, 9216, 16129,
        29, 512, 7718, 77, 9472, 19458, 26, 768,
        6951, 74, 9728, 18692, 39, 1280, 10281, 87,
        10240, 22021, 37, 1536, 9770, 85, 10496, 21510,
        30, 1792, 7979, 78, 10752, 19719, 22, 2048,
        5932, 70, 11008, 17672, 32, 2304, 8493, 80,
        11264, 20234, 41, 2816, 10799, 89, 11776, 22539,
        26, 3072, 6960, 74, 12032, 18700, 37, 3328,
        9777, 85, 12288, 21517, 38, 3584, 10034, 86,
        12544, 21774, 30, 3840, 7987, 78, 12800, 19727,
        35, 4096, 9268, 83, 13056, 21008, 34, 4352,
        9013, 82, 13312, 20754, 30, 4864, 7991, 78,
        13824, 19731, 38, 5120, 10040, 86, 14080, 21781,
        26, 5632, 6970, 74, 14592, 18710, 34, 5888,
        9019, 82, 14848, 20759, 25, 6144, 6716, 73,
        15104, 18456, 26, 6400, 6973, 74, 15360, 18713,
        25, 6656, 6718, 73, 15616, 18458, 1, 6912,
        575, 49, 15872, 12288, 0, 0, 0, 0,
        32768, 14336, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 3, 2816,
        1071, 51, 11776, 12811, 17, 3072, 4656, 65,
        12032, 16396, 15, 3328, 4145, 63, 12288, 15885,
        20, 3584, 5426, 68, 12544, 17152, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 17408, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 19, 2816,
        5167, 67, 11776, 16907, 2, 3072, 816, 50,
        12032, 12556, 8, 3328, 2353, 56, 12288, 14093,
        16, 3584, 4402, 64, 12544, 16142, 8, 3840,
        2355, 56, 12800, 14095, 11, 4096, 3124, 59,
        13056, 14864, 7, 4352, 2101, 55, 13312, 13824,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 22528, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 4, 2816,
        1327, 52, 11776, 13067, 12, 3072, 3376, 60,
        12032, 15116, 18, 3328, 4913, 66, 12288, 16653,
        6, 3584, 1842, 54, 12544, 13582, 14, 3840,
        3891, 62, 12800, 15631, 21, 4096, 5684, 69,
        13056, 17424, 4, 4352, 1333, 52, 13312, 13073,
        9, 4608, 2614, 57, 13568, 14354, 12, 4864,
        3383, 60, 13824, 15123, 15, 5120, 4152, 63,
        14080, 15892, 6, 5376, 1849, 54, 14336, 13589,
        5, 5632, 1594, 53, 14592, 13312, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 23552, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 10, 2816,
        2863, 58, 11776, 14603, 12, 3072, 3376, 60,
        12032, 15116, 16, 3328, 4401, 64, 12288, 16141,
        12, 3584, 3378, 60, 12544, 15118, 14, 3840,
        3891, 62, 12800, 15631, 21, 4096, 5684, 69,
        13056, 17424, 15, 4352, 4149, 63, 13312, 15889,
        16, 4608, 4406, 64, 13568, 16146, 12, 4864,
        3383, 60, 13824, 15123, 13, 5120, 3640, 61,
        14080, 15380, 13, 5376, 3641, 61, 14336, 15381,
        6, 5632, 1850, 54, 14592, 13590, 5, 5888,
        1595, 53, 14848, 13312, 0, 0, 0, 0,
        32768, 17408, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 13, 2816,
        3631, 61, 11776, 15371, 2, 3072, 816, 50,
        12032, 12556, 17, 3328, 4657, 65, 12288, 16397,
        15, 3584, 4146, 63, 12544, 15886, 8, 3840,
        2355, 56, 12800, 14095, 11, 4096, 3124, 59,
        13056, 14864, 7, 4352, 2101, 55, 13312, 13824,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 17408, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 8, 2816,
        2351, 56, 11776, 14091, 7, 3072, 2096, 55,
        12032, 13836, 11, 3328, 3121, 59, 12288, 14861,
        12, 3584, 3378, 60, 12544, 15118, 14, 3840,
        3891, 62, 12800, 15631, 6, 4096, 1844, 54,
        13056, 13584, 5, 4352, 1589, 53, 13312, 13312,
        0, 0, 0, 0, 0, 0, 0, 0,
        32768, 18432, 5, 256, 1573, 53, 9216, 13313,
        18, 512, 4902, 66, 9472, 16642, 5, 768,
        1575, 53, 9728, 13315, 21, 1024, 5672, 69,
        9984, 17412, 15, 1280, 4137, 63, 10240, 15877,
        16, 1536, 4394, 64, 10496, 16134, 2, 1792,
        811, 50, 10752, 12551, 16, 2048, 4396, 64,
        11008, 16136, 6, 2304, 1837, 54, 11264, 13577,
        21, 2560, 5678, 69, 11520, 17418, 4, 2816,
        1327, 52, 11776, 13067, 2, 3072, 816, 50,
        12032, 12556, 11, 3328, 3121, 59, 12288, 14861,
        4, 3584, 1330, 52, 12544, 13070, 6, 3840,
        1843, 54, 12800, 13583, 9, 4096, 2612, 57,
        13056, 14352, 6, 4352, 1845, 54, 13312, 13585,
        5, 4608, 1590, 53, 13568, 13312, 0, 0,
    },
    {
        (void*)((u8*)&lbl_800E8F60 + 0x3FE0),
        (void*)((u8*)&lbl_800E8F60 + 0x4340),
        (void*)((u8*)&lbl_800E8F60 + 0x4580),
        (void*)((u8*)&lbl_800E8F60 + 0x49E0),
        (void*)((u8*)&lbl_800E8F60 + 0x4EE0),
        (void*)((u8*)&lbl_800E8F60 + 0x5000),
        (void*)((u8*)&lbl_800E8F60 + 0x50C0),
        (void*)((u8*)&lbl_800E8F60 + 0x51A0),
        (void*)((u8*)&lbl_800E8F60 + 0x52C0),
        (void*)((u8*)&lbl_800E8F60 + 0x53E0),
        (void*)((u8*)&lbl_800E8F60 + 0x54C0),
        (void*)((u8*)&lbl_800E8F60 + 0x55A0),
    },
    {
        {864, 33, 3},
        {576, 35, 2},
        {1120, 30, 4},
        {1280, 35, 4},
        {288, 27, 1},
        {192, 14, 1},
        {224, 17, 1},
        {288, 22, 1},
        {288, 23, 1},
        {224, 17, 1},
        {224, 17, 1},
        {224, 18, 1},
    },
}; // NOTE: type size 0x5740 != symbol size 0x194
// lbl_800E90F4 is part of the object above
// lbl_800E9908 is part of the object above
// lbl_800E9920 is part of the object above
// lbl_800ECF40 is part of the object above
// lbl_800ED2A0 is part of the object above
// lbl_800ED4E0 is part of the object above
// lbl_800ED940 is part of the object above
// lbl_800EDE40 is part of the object above
// lbl_800EDF60 is part of the object above
// lbl_800EE020 is part of the object above
// lbl_800EE100 is part of the object above
// lbl_800EE220 is part of the object above
// lbl_800EE340 is part of the object above
// lbl_800EE420 is part of the object above
// lbl_800EE500 is part of the object above

// .sdata 0x803CB760..0x803CB790
u8 lbl_803CB760[5] = {0, 1, 1, 2, 3}; // NOTE: type size 0x5 != symbol size 0x20
u32 lbl_803CB780 = 0xFFFFFFFF;
GXColor lbl_803CB784 = {0, 0, 0, 255};
u32 lbl_803CB788 = 0xFFFFFF; // NOTE: type size 0x4 != symbol size 0x8

// .sbss 0x803CBBE8..0x803CBBF0 (MWCC lays these out in reverse definition order)
TexArchive* lbl_803CBBE8;

