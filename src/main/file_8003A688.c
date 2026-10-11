#include "main/file_8003A688.h"
#include "main/file_80039AC0.h"
#include "main/file_80008E00.h"
#include "main/file_8001FE00.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/GX.h"
#include "stl/string.h"

extern TrailSystem lbl_802D3D80;
// SoundManager (main/file_80021308.h, whose prototypes clash with UnknownHomes_Static.h).
typedef struct SoundManagerView {
    /*0x000*/ u8 _000[0x397];
    /*0x397*/ u8 outputMode;
    /*0x398*/ u8 unk398;
} SoundManagerView;
extern SoundManagerView lbl_800EF808;
extern u8 lbl_80361B20[0xF8];
extern u8 lbl_803616CC[0x454];

// main/file_800A7C08 (memory card / CRC)
s32 fn_800ACC6C(s32 mode, s32 a, s32 b);
u16 fn_800ABB14(u8* data, s32 len);

// .text:0x8003A688 size:0x28
void fn_8003A688(s32 type, f32 speed, f32 spread) {
    lbl_802D3D80.params[type].speed = speed / 2;
    lbl_802D3D80.params[type].spread = spread / 2;
}

// .text:0x8003A6B0 size:0x198
void fn_8003A6B0(s32 type, TexDesc* desc, f32 speed, f32 spread) {
    if (desc->palette != NULL) {
        lbl_802D3D80.texMode[type] = 2;
        GXInitTexObjCI(&lbl_802D3D80.texObj[type], desc->image, desc->width, desc->height, desc->format, desc->wrapS, desc->wrapT,
                       GX_FALSE, type);
        GXInitTlutObj(&lbl_802D3D80.tlutObj[type], desc->palette, desc->tlutFormat, desc->tlutCount);
    } else {
        lbl_802D3D80.texMode[type] = 1;
        GXInitTexObj(&lbl_802D3D80.texObj[type], desc->image, desc->width, desc->height, desc->format, desc->wrapS, desc->wrapT,
                     GX_FALSE);
    }
    GXInitTexObjLOD(&lbl_802D3D80.texObj[type], desc->minFilter, desc->magFilter, desc->minLod, desc->maxLod, desc->lodBias,
                    GX_FALSE, GX_FALSE, GX_ANISO_1);
    fn_8003A688(type, speed, spread);
}

extern u8 lbl_803CB828[3];

// fn_8003A848, size:0x14
void fn_8003A848(u8 red, u8 green, u8 blue) {
    lbl_803CB828[0] = red;
    lbl_803CB828[1] = green;
    lbl_803CB828[2] = blue;
}

// .text:0x8003A85C size:0x44
void fn_8003A85C(u8 enabled) {
    lbl_802D3D80.enabled = enabled;
    lbl_802D3D80.head = 0;
    lbl_802D3D80.tail = 0;
    memset(lbl_802D3D80.texMode, 0, sizeof(lbl_802D3D80.texMode));
}

// .text:0x8003A8A0 size:0x3F0
void fn_8003A8A0(void) {
    return;
}

extern u32 lbl_803CBCB8;

extern u8 lbl_803CBCB4;

// .text:0x8003AC90 size:0xF4
void fn_8003AC90(void) {
    GXColor color;
    color.a = 0xFF;
    color.b = lbl_803CBCB4;
    color.g = lbl_803CBCB4;
    color.r = lbl_803CBCB4;
    GXSetChanMatColor(GX_COLOR0A0, color);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_RASA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

extern GXTexObj lbl_803C50B0;
extern GXTlutObj lbl_803C50DC;
extern u16 lbl_800F7AC0[16];
extern u8 lbl_803CBCAC;

// .text:0x8003AD84 size:0xD0
void fn_8003AD84(TexSet* set) {
    GXInitTexObjCI(&lbl_803C50B0, set->tex[0].image, set->tex[0].width, set->tex[0].height, GX_TF_C4, set->tex[0].wrapS,
                   set->tex[0].wrapT, GX_FALSE, GX_TLUT0);
    GXInitTlutObj(&lbl_803C50DC, lbl_800F7AC0, GX_TL_IA8, 16);
    GXInitTexObjLOD(&lbl_803C50B0, set->tex[0].minFilter, set->tex[0].magFilter, set->tex[0].minLod, set->tex[0].maxLod,
                    set->tex[0].lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    lbl_803CBCAC = 1;
}

// fn_8003AE70, size:0x5C
u8 fn_8003AE70(s32 selector) {
    u8 value = 0;
    switch (selector) {
    case 0:
        value = lbl_802D4B00._95;
        break;
    case 1:
        value = lbl_802D4B00.soundMode;
        break;
    case 2:
        value = lbl_802D4B00._96;
        break;
    }
    return value;
}

// fn_8003AE54, size:0x8
u8 fn_8003AE54(void) {
    return lbl_803CBCB4;
}

// fn_8003AE5C, size:0x8
void fn_8003AE5C(u8 value) {
    lbl_803CBCB4 = value;
}

// fn_8003AE64, size:0xC
void fn_8003AE64(void) {
    lbl_803CBCB8 = 0x0;
}

// .text:0x8003AECC size:0x6E4
void fn_8003AECC(void) {
    return;
}

// .text:0x8003B5B0 size:0x5E0
void fn_8003B5B0(void) {
    return;
}

// .text:0x8003BB90 size:0x3C4
void fn_8003BB90(void) {
    return;
}

// .text:0x8003BF54 size:0xB8
void fn_8003BF54(u8 a, u8 b, u8 slot, u8 c, u8 d, u8 e, u8 f, u8 g, u8 h) {
    SaveTask* task = fn_800B0A5C_insertQueue(fn_8003C00C, 0x8000);
    task->state = 0;
    task->_15 = a;
    task->_16 = b;
    task->slot = slot;
    task->_18 = c;
    task->_19 = d;
    task->_1A = e;
    task->_1B = f;
    task->_1D = 0;
    task->_20 = g;
    task->_21 = h;
    lbl_802D4AE0[slot] = 0;
    task->_1F = 2;
    lbl_803CC1B8->_10 = 0;
}

// .text:0x8003C00C size:0x28CC
void fn_8003C00C(void) {
    return;
}

// .text:0x8003E8D8 size:0x964
void fn_8003E8D8(void) {
    return;
}

// .text:0x8003F23C size:0x7C
void fn_8003F23C(void) {
    SaveTask* task = fn_800B0A5C_insertQueue(fn_8003F2B8, 0x8000);
    task->state = 0;
    task->_15 = 0;
    task->_16 = 0;
    task->slot = 0;
    task->_18 = 0;
    task->_1A = 0;
    task->_1B = 7;
    task->_1D = 0;
    task->_21 = 0;
    lbl_803CC1B8->_10 = 0;
    lbl_802D4AE0[1] = 0;
    lbl_802D4AE0[0] = 0;
}

// .text:0x8003F2B8 size:0x1284
void fn_8003F2B8(void) {
    return;
}

// .text:0x8004053C size:0x6D8
void fn_8004053C(void) {
    return;
}

// .text:0x80040C14 size:0x3CC
void fn_80040C14(void) {
    return;
}

// .text:0x80040FE0 size:0x94
s32 fn_80040FE0(SaveImage* img) {
    u8* shared = img->_48;
    SaveChallengeBlock* blk;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == 0) {
            img->crc = fn_800ABB14(shared, 0x5B0);
        } else {
            blk = &img->challenge[i - 1];
            blk->crc = fn_800ABB14(blk->data, sizeof(blk->data));
        }
    }
    return 0x11;
}

// .text:0x80041074 size:0xDC
u8 fn_80041074(SaveImage* img, s32 length, u32 mask) {
    u8* shared = img->_48;
    u32 bit;
    SaveChallengeBlock* blk;
    s32 i;
    u16 sum;

    lbl_803C50E8.badMask = 0;
    for (i = 0; i < 4; i++) {
        bit = 1 << i;
        if (mask & bit) {
            if (i == 0) {
                sum = fn_800ABB14(shared, 0x5B0);
                if (sum != img->crc) {
                    lbl_803C50E8.badMask = bit;
                    break;
                }
            } else {
                blk = &img->challenge[i - 1];
                sum = fn_800ABB14(blk->data, sizeof(blk->data));
                if (sum != blk->crc) {
                    lbl_803C50E8.badMask |= bit;
                }
            }
        }
    }
    if (lbl_803C50E8.badMask != 0) {
        return 0xB;
    }
    return 0x11;
}

// .text:0x80041150 size:0x1F8
void fn_80041150(void) {
    return;
}

// .text:0x80041348 size:0x1F4
// Sanity-checks the loaded challenge save; returns 0 if it is corrupt.
void fn_80041348(void) {
    return;
}

// .text:0x8004153C size:0x40
void fn_8004153C(void) {
    lbl_803CBC50 = 0x2380;
    lbl_803CBC4C = 0xE60;
    lbl_803CBC48 = fn_800ACC6C(1, 0x2380, 0x10000);
}

extern u16 lbl_803CBCC0;

// fn_8004157C, size:0x24
s32 fn_8004157C(void) {
    if (lbl_803CBCC0 != 0) {
        lbl_803CBCC0--;
        return 1;
    }
    return 0;
}

// fn_800415A0, size:0x8
void fn_800415A0(u16 value) {
    lbl_803CBCC0 = value;
}

// .text:0x800415A8 size:0xAD4
void fn_800415A8(void) {
    return;
}
