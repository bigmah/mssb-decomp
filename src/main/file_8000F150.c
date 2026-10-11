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

// NONMATCHING 99%: original loads the anim pointer with lwzu (keeps &slot->anim in r31); ours uses addi+lwz
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
    fn_8000CEF0(*anim, animId, 0, owner->_06, (u32*)&info); // TODO type: out is a LayoutInfo (SpaniKey)
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

// NONMATCHING 97%: register allocation differs, and an extra branch after the end-of-substring continue
// .text:0x8000FA9C size:0x2B8
#if NONMATCHING
s32 fn_8000FA9C(s32 index) {
    u16** msgs;
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
                sub = msgs[n];
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
    u16* text = lbl_80366B18.tables[table]->msgs[msg];
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

// NONMATCHING 99%: two address computations (table/msg slwi) scheduled in the other order
// .text:0x8000FF04 size:0x1A0
#if NONMATCHING
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
    e->text = lbl_80366B18.tables[table]->msgs[msg];
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
#endif

// NONMATCHING 99%: f2/f3 swapped for the 0.0f constant, and two extra clrlwi on the u16 s+w sum
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
                sub = lbl_80366B18.tables[0]->msgs[n];
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

// NONMATCHING 96%: extra `mr` when setting up dst before the copy loop
// .text:0x80010FA0 size:0x60
#if NONMATCHING
void fn_80010FA0(void) {
    MsgTable* t = lbl_80366B18.tables[0];
    u16* dst = lbl_80366218;
    u16* src;
    lbl_80366B18.msgs = t->msgs;
    lbl_80366B18._7EC = t->msgs[1];
    lbl_80366B18._7F0 = t->msgs[2];
    lbl_80366B18._7F8 = t->msgs[6];
    lbl_80366B18._7F4 = t->msgs[5];
    src = lbl_80366B18.msgs[7];
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

// NONMATCHING 96%: saved regs r30/r31 swapped (loop counter vs. lbl_80366B18 base)
// .text:0x80011000 size:0x140
#if NONMATCHING
void fn_80011000(void) {
    s32 i;
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
    s32 n = table->count;
    u16** p = table->msgs;
    do {
        *p = (u16*)((u32)*p + (u32)table); // file offset -> pointer (32-bit data)
        p++;
    } while (--n);
}

// .text:0x800111D8 size:0x24
GameActor** fn_800111D8(CharActor* actor) {
    return &lbl_8036E548.slots->objects[actor->modelIndex].actor;
}

// NONMATCHING 99%: original keeps &actors[i] (addi 0xc04) in r5 and copies it to r31; ours folds the offset
// .text:0x800111FC size:0x15C
#if NONMATCHING
CharActor* fn_800111FC(CharActor* actor, s32 second) {
    s32 slot;
    CharActor* next;
    if (g_d_GameSettings.GameModeSelected != 6) {
        return actor;
    }
    slot = actor->modelIndex % 4;
    lbl_8036E548.actors[slot + 4].mode[0] = 0;
    lbl_8036E548.actors[slot].mode[0] = 0;
    next = &lbl_8036E548.actors[slot + ((second != 0) << 2)];
    lbl_8036E548.active[slot] = next;
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
#endif

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

// .text:0x80011468 size:0x108
void fn_80011468(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        CharActor* actor = lbl_8036E548.active[i];
        if (actor != NULL) {
            ActorObject* obj = &lbl_8036E548.slots->objects[actor->modelIndex];
            switch (actor->kind) {
            case 19:
                fn_8004B6EC(actor, obj);
                break;
            case 40:
            case 41:
                fn_8004B7F4(actor, obj);
                break;
            case 38:
                obj->actor->tickFlag = 1;
            case 18:
                fn_8004BAEC(actor, obj);
                break;
            case 14:
            case 37:
                fn_8005240C(actor, obj);
                break;
            case 6:
            case 10:
            case 12:
            case 24:
            case 25:
            case 26:
            case 42:
                obj->actor->tickFlag = 1;
                break;
            case 20:
            case 43:
                if (actor->anim[0] == 0x40) {
                    obj->actor->tickFlag = 0;
                } else {
                    obj->actor->tickFlag = 1;
                }
                break;
            }
        }
    }
}

// fn_80011578, size:0x50
void fn_80011578(void) {
    s8 i = 0;
    s32 n;
    for (n = 13; n != 0; n--) {
        if (i >= 0 && i < 13) {
            CharActor* actor = lbl_8036E548.active[(u32)i];
            if (actor != NULL) {
                actor->tevHook = NULL;
            }
        }
        i++;
    }
}

// fn_800115C8, size:0x3C
void fn_800115C8(s8 index) {
    if (index >= 0 && index < 13) {
        CharActor* actor = lbl_8036E548.active[index];
        if (actor != NULL) {
            actor->tevHook = NULL;
        }
    }
}

// fn_80011570, size:0x8
CharActor* fn_80011570(void) {
    return lbl_803CBC18;
}

// fn_80011604, size:0x3C
void fn_80011604(s8 index, DOTevHook value) {
    CharActor* actor;
    if (index < 0 || index >= 13) {
        return;
    }
    actor = lbl_8036E548.active[index];
    if (actor != NULL) {
        actor->tevHook = value;
    }
}
