#include "challenge/rep_7730.h"

#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"

// POOL BEGIN (high-to-low; memory order is the reverse)
static Mtx44 lbl_1_bss_47010;
static ChallengeCurveTiming lbl_1_bss_45868;
static u8 lbl_1_bss_45890[0x17A8 - 0x28];
static ChallengePathNode lbl_1_bss_43F68[100];
static u8 lbl_1_bss_43EE0[0x88];
static f32 lbl_1_bss_F6E0[0x34800 / 4];
static u8 lbl_1_bss_76E0[0x8000];
static f32 lbl_1_bss_74E0[0x200 / 4];
static ChallengeCurvePoint lbl_1_bss_6FE0[20];
static ChallengeCurveTiming lbl_1_bss_6FB8;
static u8 lbl_1_bss_6FB4[4];
static f32 lbl_1_bss_6FA8[3];
static u8 lbl_1_bss_6FA4[4];
static GXTexObj lbl_1_bss_6EA4[8];
static GXTlutObj lbl_1_bss_6E44[8];
static u8 lbl_1_bss_6D48[0xFC];
static f32 lbl_1_bss_6BF4[0x154 / 4];
static f32 lbl_1_bss_6BE4[4];
static s32 lbl_1_bss_6BE0;
static s32 lbl_1_bss_6BDC;
static s32 lbl_1_bss_6BD8;
// POOL END
extern void fn_1_20BD8(void);

extern void fn_1_246AC(void);

extern u8* lbl_803CC1B8[];


extern void (*lbl_1_data_1066C[])(s16);

extern void fn_80037B18(void*, Vec*, f32);

extern u8 lbl_1_data_10674[];
extern void fn_1_1DA54(void);

extern const f32 lbl_1_rodata_77E4[];
extern void fn_1_272DC(void*, s32);
extern void fn_1_AF4(s32, s32, f32);
extern void fn_1_1E5D0(void*);

extern void fn_1_21408(void);
extern u8 lbl_803C6CF8[];
extern u8 lbl_1_data_104F4[];
extern const f32 lbl_1_rodata_77D8;
extern const f32 lbl_1_rodata_7804;
extern const f32 lbl_1_rodata_7858;
extern const f32 lbl_1_rodata_785C;
extern const f32 lbl_1_rodata_7860;
extern const f32 lbl_1_rodata_7864;
extern const f32 lbl_1_rodata_7868;
extern const f32 lbl_1_rodata_780C;
extern const f32 lbl_1_rodata_77DC[];
extern const f32 lbl_1_rodata_77E0[];
extern const f32 lbl_1_rodata_7814[];
extern const f32 lbl_1_rodata_7820[];
extern void (*lbl_1_data_104A8[])(void);
extern void* lbl_80366158[];
extern void fn_1_267F4(void);
extern void fn_1_25C68(void);
extern void (*lbl_1_data_10508[])(u8*);
extern void (*lbl_1_data_10510[])(u8*);
extern u32 lbl_1_data_104DC[];
extern const f32 lbl_1_rodata_7810;
extern const f64 lbl_1_rodata_7818[];
extern const f32 lbl_1_rodata_784C[];
extern void fn_80038CD0(u8, void*, void*, f32, f32);

// fn_1_20640, size:0x194
void fn_1_20640(ChallengeTextureStages* stages, u32* indices) {
    u32* image;
    GXTexCoordID stage;
    u32 textureIndex;
    u32 paletteIndex;

    GXSetNumTevStages(stages->stageCount);
    GXSetNumTexGens(stages->stageCount);
    image = indices;
    for (stage = 0; stage < (s32)stages->stageCount; image++, stage++) {
        GXSetTexCoordGen2(stage, GX_TG_MTX3X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        if (stage != 0) {
            GXSetTevColorIn(stage, GX_CC_CPREV, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        } else {
            GXSetTevColorIn(stage, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(stage, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
            GXSetTevAlphaOp(stage, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        textureIndex = *image;
        paletteIndex = textureIndex & 0x7FFFFFFF;
        GXLoadTexObj(&lbl_1_bss_6EA4[textureIndex], stage);
        if (textureIndex & 0x80000000) {
            GXLoadTlut(&lbl_1_bss_6E44[paletteIndex], stage);
        }
    }
}

// fn_1_21298, size:0x170
void fn_1_21298(ChallengeCurveDrawing* drawing) {
    s32 count;
    ChallengeCurvePoint* point;
    u32 color;

    if (drawing->drawFlat != 0) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, (drawing->pointCount - 1) * 2);
        count = drawing->pointCount;
        while (--count != 0) {
            point = &lbl_1_bss_6FE0[count];
            GXWGFifo.f32 = point->position.x;
            GXWGFifo.f32 = 0.0f;
            GXWGFifo.f32 = point->position.z;
            GXWGFifo.u32 = 0x80;
            GXWGFifo.f32 = point[-1].position.x;
            GXWGFifo.f32 = 0.0f;
            GXWGFifo.f32 = point[-1].position.z;
            GXWGFifo.u32 = 0x80;
        }
    }
    if (drawing->drawFull != 0) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, (drawing->pointCount - 1) * 2);
        count = drawing->pointCount;
        while (--count != 0) {
            point = &lbl_1_bss_6FE0[count];
            GXWGFifo.f32 = point->position.x;
            GXWGFifo.f32 = -point->position.y;
            GXWGFifo.f32 = point->position.z;
            color = lbl_1_data_104DC[count % 6];
            GXWGFifo.u32 = color;
            GXWGFifo.f32 = point[-1].position.x;
            GXWGFifo.f32 = -point[-1].position.y;
            GXWGFifo.f32 = point[-1].position.z;
            GXWGFifo.u32 = color;
        }
    }
}

// fn_1_202A4, size:0x168
void fn_1_202A4(void) {
    u8* queue = lbl_803CC1B8[0];
    fn_80048C1C();
    lbl_1_data_10508[queue[0x20]](queue);
    if (lbl_803C77B8._02 & 0x200) {
        GXColor clearColor;
        ChallengeTransfer* transfer;
        *(u32*)&clearColor = 0x11775500;
        GXSetCopyClear(clearColor, 0xFFFFFF);
        transfer = *(ChallengeTransfer**)(lbl_803CC1B8[0] + 0x0C);
        transfer->complete = 1;
        fn_800B0A14_removeQueue(transfer);
    }
    fn_80048D4C();
    fn_1_207D4();
    lbl_1_data_10510[queue[0x20]](queue);
    fn_80048C28();
}

// fn_1_2051C, size:0x124
s32 fn_1_2051C(ChallengeTextureHeader* texture, GXTexObj* object, GXTlutObj* palette, GXTlut name) {
    u8 mipmapped = texture->minLod != texture->maxLod;
    if (texture->palette != NULL) {
        GXInitTexObjCI(object, texture->image, texture->width, texture->height,
            texture->format, texture->wrapS, texture->wrapT, mipmapped, name);
        GXInitTlutObj(palette, texture->palette, texture->paletteFormat, texture->paletteEntries);
    } else {
        GXInitTexObj(object, texture->image, texture->width, texture->height,
            texture->format, texture->wrapS, texture->wrapT, mipmapped);
    }
    GXInitTexObjLOD(object, texture->minFilter, texture->magFilter,
        texture->minLod, texture->maxLod, texture->lodBias, GX_FALSE, GX_FALSE, GX_ANISO_1);
    return !!texture->palette;
}

// fn_1_26928, size:0x10C
void fn_1_26928(void) {
    u8* queue = lbl_803CC1B8[0];
    u16 repeated = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (repeated & 2) {
        queue[0x20]++;
        if (queue[0x20] == queue[0x1F]) {
            queue[0x20] = 0;
        }
    } else if (repeated & 1) {
        if (queue[0x20] == 0) {
            queue[0x20] = queue[0x1F];
        }
        queue[0x20]--;
    } else {
        u16 pressed = lbl_803C77B8._02;
        if (pressed & 0x100) {
            queue[0x1E] = 0;
            *(void (**)(void))lbl_803CC1B8[0] = fn_1_267F4;
        } else if (pressed & 0x200) {
            ChallengeTransfer* transfer;
            fn_800AD038(lbl_80366158[2]);
            transfer = *(ChallengeTransfer**)(lbl_803CC1B8[0] + 0x0C);
            transfer->complete = 1;
            fn_800B0A14_removeQueue(transfer);
        } else if (pressed & 0x1000) {
            *(void (**)(void))queue = fn_1_25C68;
        }
    }
    fn_800B24D4(4);
    fn_800B1188();
}

// fn_1_246AC, size:0xCC
void fn_1_246AC(void) {
    u8* queue = lbl_803CC1B8[0];
    u16 repeated = *(u16*)((u8*)&lbl_803C77B8 + 4);
    if (repeated & 8) {
        if (queue[0x14] == 0) {
            queue[0x14] = 4;
        }
        queue[0x14]--;
    } else if (repeated & 4) {
        queue[0x14]++;
        if (queue[0x14] == 4) {
            queue[0x14] = 0;
        }
    } else {
        u16 pressed = lbl_803C77B8._02;
        if (pressed & 0x100) {
            *(void (**)(void))queue = lbl_1_data_104A8[queue[0x14]];
        } else if (pressed & 0x200) {
            ChallengeTransfer* transfer = *(ChallengeTransfer**)(queue + 0x0C);
            transfer->complete = 1;
            fn_800B0A14_removeQueue(transfer);
        }
    }
}

// fn_1_26A34, size:0xC4
void fn_1_26A34(void) {
    GXSetProjection(lbl_1_bss_47010, GX_PERSPECTIVE);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_NONE);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
}

// fn_1_20890, size:0xC0
void fn_1_20890(void) {
    Mtx identity;
    C_MTXOrtho(lbl_1_bss_47010, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0],
        lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_7814[0], lbl_1_rodata_7820[0]);
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    fn_80048C14(3);
    fn_80048E00(0, 32);
    fn_80048E00(1, 0);
}

// fn_1_207D4, size:0xBC
void fn_1_207D4(void) {
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
}

// fn_1_1F23C, size:0x9C
void fn_1_1F23C(ChallengeProjectionState* state) {
    fn_800385F0(lbl_1_bss_6BF4,
        *(f32*)(lbl_803CC1B8[0] + 0x14), *(f32*)(lbl_803CC1B8[0] + 0x18),
        *(f32*)(lbl_803CC1B8[0] + 0x1C), *(f32*)(lbl_803CC1B8[0] + 0x20));
    state->depth = -*(f32*)(lbl_803CC1B8[0] + 0x24);
    state->distance += lbl_1_rodata_780C;
    *(u32*)(lbl_803CC1B8[0] + 0x2C) &= ~2U;
    *(u32*)(lbl_803CC1B8[0] + 0x2C) |= 2;
}

// fn_1_23AD8, size:0x7C
void fn_1_23AD8(Mtx44 projection, Vec* camera, Vec* target) {
    camera->x = lbl_1_rodata_77D8;
    camera->y = lbl_1_rodata_77D8;
    camera->z = lbl_1_rodata_7804;
    target->x = lbl_1_rodata_77D8;
    target->y = lbl_1_rodata_77D8;
    target->z = lbl_1_rodata_77D8;
    C_MTXFrustum(projection, lbl_1_rodata_7858, lbl_1_rodata_785C,
        lbl_1_rodata_7860, lbl_1_rodata_7864, lbl_1_rodata_77E4[0], lbl_1_rodata_7868);
}

// fn_1_20F8C, size:0xB4
void fn_1_20F8C(void) {
    s16 phase = *(s16*)(lbl_803CC1B8[0] + 0x10);
    ChallengeTransfer* transfer = *(ChallengeTransfer**)(lbl_803CC1B8[0] + 0x0C);
    switch (phase) {
    case 0:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            transfer->data = (void*)ARAMTransfer(lbl_1_data_104F4, 0, 0, 0);
            (*(s16*)(lbl_803CC1B8[0] + 0x10))++;
        }
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            transfer->complete = 1;
        }
        break;
    }
}

// .text:0x225B8 size:0x8C
void fn_1_225B8(void) {
    u8* queue = lbl_803CC1B8[0];
    switch ((s32)queue[0x25]) {
    case 0:
        fn_1_20DC8();
        queue[0x25]++;
        break;
    case 1:
        if (*(s16*)(queue + 0x10) != 0) {
            *(void (**)(void))queue = fn_1_21408;
        }
        break;
    }
}

// .text:0x1EFF4 size:0x68
void fn_1_1EFF4(void) {
    fn_1_272DC(lbl_1_bss_6D48, 0);
    fn_1_AF4(20, 20, lbl_1_rodata_77E4[0]);
    if (*(u32*)(lbl_803CC1B8[0] + 0x2C) & 2) {
        fn_1_1E5D0(lbl_1_bss_6BF4);
    }
}

// .text:0x1DCE4 size:0x64
void fn_1_1DCE4(void) {
    u8* queue = lbl_803CC1B8[0];
    *(void**)(queue + 0x14) = (void*)ARAMTransfer(lbl_1_data_10674, 0, 0, 0);
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_1DA54;
}

// .text:0x1DD94 size:0x50
void fn_1_1DD94(void) {
    Vec axis;
    axis.x = lbl_1_bss_6BE4[1];
    axis.y = lbl_1_bss_6BE4[2];
    axis.z = lbl_1_bss_6BE4[3];
    fn_80037B18(lbl_1_bss_6BF4, &axis, lbl_1_bss_6BE4[0]);
}

// .text:0x1E8C0 size:0x4C
void fn_1_1E8C0(s32 index) {
    lbl_1_data_1066C[*(s32*)(lbl_803CC1B8[0] + 0x28)]((s16)(index - 8));
}

// .text:0x1DE5C size:0x4
void fn_1_1DE5C(void) {
}

// .text:0x1E28C size:0x4
void fn_1_1E28C(void) {
}

void fn_1_1DDE4(f32 value) {
    lbl_1_bss_6BE4[3] = value;
}

void fn_1_1DDF4(f32 value) {
    lbl_1_bss_6BE4[2] = value;
}

void fn_1_1DE04(f32 value) {
    lbl_1_bss_6BE4[1] = value;
}

void fn_1_1DE14(f32 value) {
    lbl_1_bss_6BE4[0] = value;
}

f32 fn_1_1DE20(void) {
    return lbl_1_bss_6BE4[3];
}

f32 fn_1_1DE30(void) {
    return lbl_1_bss_6BE4[2];
}

f32 fn_1_1DE40(void) {
    return lbl_1_bss_6BE4[1];
}

f32 fn_1_1DE50(void) {
    return lbl_1_bss_6BE4[0];
}

// fn_1_267BC, size:0x38
void fn_1_267BC(void) {
    if (*(s16*)(lbl_803CC1B8[0] + 0x10) != 0) {
        fn_800B0A14_removeQueue(lbl_803CC1B8[0]);
    }
}

// fn_1_24778, size:0x28
void fn_1_24778(void) {
    lbl_803CC1B8[0][0x14] = 0;
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_246AC;
}

// fn_1_20DC8, size:0x38
void fn_1_20DC8(void) {
    u8* object = fn_800B0A5C_insertQueue((void*)fn_1_20BD8, 1);
    object[0x25] = 0;
    *(s16*)(object + 0x10) = 0;
}

// fn_1_1DD48, size:0x4C
f32 fn_1_1DD48(u16 buttons, s32 reverse, f32 value, f32 positive, f32 delta, f32 negative, f32 minimum, f32 maximum) {
    if (buttons & 0x40) delta = positive;
    else if (buttons & 0x20) delta = negative;
    if (reverse) delta = -delta;
    value += delta;
    if (value < minimum) value = minimum;
    if (value > maximum) value = maximum;
    return value;
}

extern void fn_1_2004C(void);

// fn_1_2040C, size:0x110
void fn_1_2040C(void) {
    Mtx identity;
    u8* queue = lbl_803CC1B8[0];
    *(s32*)(queue + 0x1C) = 0;
    queue[0x23] = 0;
    queue[0x24] = 0;
    queue[0x20] = 0;
    queue[0x21] = 0;
    queue[0x22] = 1;
    C_MTXOrtho(lbl_1_bss_47010, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0],
        lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_7814[0], lbl_1_rodata_7820[0]);
    GXSetProjection(lbl_1_bss_47010, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(identity, GX_TEXMTX0, GX_MTX2x4);
    fn_80048C14(3);
    fn_80048E00(0, 32);
    fn_80048E00(1, 0);
    fn_800AD038(lbl_80366158[2]);
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_2004C;
}

#include "Dolphin/os.h"
extern s32 fn_80035DD4(s32);
extern void fn_80034E20(void*, void*, void*);
extern void fn_1_267BC(void);
extern void fn_1_25F98(void);
extern u8 lbl_1_data_FB98[];
extern u8 lbl_1_data_10344[];
extern u8 lbl_803C4BE0[];
extern char lbl_1_rodata_78F0[];
extern char lbl_1_rodata_78F8[];

// fn_1_267F4, size:0x134
void fn_1_267F4(void) {
    u8* queue = lbl_803CC1B8[0];
    switch (queue[0x1E]) {
    case 0:
        if (fn_80035838(lbl_1_data_FB98 + queue[0x20] * 0x10, 0) != 0) {
            queue[0x1E] = queue[0x1E] + 1;
        }
        break;
    case 1: {
        s32 index;
        u8* entry;
        *(u8**)(queue + 0x14) = fn_800B0A5C_insertQueue((void*)fn_1_267BC, 1);
        *(s16*)(*(u8**)(queue + 0x14) + 0x10) = 0;
        index = fn_80035DD4(0);
        if (index == -1) {
            OSPanic(lbl_1_rodata_78F0, 0xF5, lbl_1_rodata_78F8);
        }
        entry = lbl_803C4BE0;
        entry += index * 0x3C;
        *(s16*)(queue + 0x18) = **(s32**)(*(u8**)(entry + 0x38) + 8);
        fn_80034E20(*(u8**)(queue + 0x14), lbl_1_data_10344, entry);
        queue[0x21] = 0;
        queue[0x22] = 0;
        queue[0x24] = 0;
        *(s16*)(queue + 0x1A) = 0;
        *(s16*)(queue + 0x1C) = 0;
        *(void (**)(void))lbl_803CC1B8[0] = fn_1_25F98;
        break;
    }
    }
}

typedef struct {
    u8 pad0[8];
    u32 flags;
    void* data;
    void* table;
    u16 width;
    u16 height;
    u8 active;
    u8 pad19[3];
} ChallengeAnimEntry;

extern ChallengeAnimEntry lbl_1_data_107E4[];
extern u8 lbl_1_data_107C4[];
extern u8 lbl_803CBBC0[];
extern void fn_800A7D4C(s32, void*);

// .text:0x1D944 size:0x110
void fn_1_1D944(void) {
    u8* q = lbl_803CC1B8[0];
    ChallengeAnimEntry* e;
    u8* obj;
    u8* d;
    u16 a, b;

    if (lbl_803C77B8._02 & 0x200) {
        fn_800AD038(lbl_80366158[2]);
        obj = *(u8**)(lbl_803CC1B8[0] + 0xC);
        *(s16*)(obj + 0x10) = 1;
        fn_800B0A14_removeQueue(obj);
        return;
    }
    if (--*(u16*)(q + 0x20) == 0) {
        *(u16*)(q + 0x20) = *(u16*)(q + 0x22);
        *(u16*)(q + 0x1E) = (*(u16*)(q + 0x1E) + 1) % *(u16*)(q + 0x1C);
    }
    lbl_1_data_107E4[lbl_803CBBC0[0]].data = *(u8**)(q + 0x18) + (*(u16*)(q + 0x28) + *(u16*)(q + 0x1E)) * 32 + 4;
    e = &lbl_1_data_107E4[lbl_803CBBC0[0]];
    e->width = *(u16*)(q + 0x24);
    e->height = *(u16*)(q + 0x26);
    e->active = 1;
    e->table = lbl_1_data_107C4;
    e->flags = *(u32*)(q + 0x2C);
    fn_800A7D4C(0, e);
}

// .text:0x21180 size:0x118
void fn_1_21180(ChallengeCurveDrawing* arg) {
    ChallengeCurveTiming* tm;
    s32 n = arg->steps;
    f32 t;
    ChallengeCurvePoint* pts;
    s32 idx;

    tm = &lbl_1_bss_6FB8;
    tm->steps = n;
    t = (lbl_1_rodata_77E4[0] / (f32)n) / lbl_1_rodata_784C[0];
    tm->step = t;
    tm->stepSq = t * t;
    tm->inv = lbl_1_rodata_77E4[0] / ((&lbl_1_rodata_780C)[0] * t);
    if (lbl_803C77B8._00 & 0x400) {
        tm->steps = 1;
    }
    fn_80038CD0(arg->pointCount, &lbl_1_bss_6FB8, lbl_1_bss_6FE0, lbl_1_rodata_7810, arg->scale);
    pts = lbl_1_bss_6FE0;
    idx = arg->pointCount - 1;
    lbl_1_bss_6FA8[0] = pts[idx].position.x;
    lbl_1_bss_6FA8[1] = pts[idx].position.y;
    lbl_1_bss_6FA8[2] = pts[idx].position.z;
    pts[idx].mode = arg->colorMode;
}

extern void fn_80038B48(void*, void*, u8, Vec*);

// .text:0x247A0 size:0x11C
void fn_1_247A0(void) {
    u8* q = lbl_803CC1B8[0];
    u16 speed = *(u16*)(q + 0x22);
    Vec v;

    v.x = speed * ((s8)((u8*)&lbl_803C77B8)[0x10] * lbl_1_bss_43F68[q[0x2B] - 1].scale);
    v.y = speed * ((s8)((u8*)&lbl_803C77B8)[0x13] * lbl_1_bss_43F68[q[0x2B] - 1].scale);
    v.z = speed * ((s8)((u8*)&lbl_803C77B8)[0x11] * lbl_1_bss_43F68[q[0x2B] - 1].scale);
    fn_80038B48(&lbl_1_bss_45868, lbl_1_bss_43F68, q[0x2B], &v);
}

extern void fn_1_273D8(void*);
extern void fn_1_1F05C(void);

// .text:0x1F2D8 size:0x140
void fn_1_1F2D8(void) {
    fn_1_273D8(lbl_1_bss_6D48);
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_1F05C;
    *(u32*)(lbl_803CC1B8[0] + 0x2C) = 0;
    *(u32*)(lbl_803CC1B8[0] + 0x28) = 0;
    *(f32*)(lbl_803CC1B8[0] + 0x14) = (&lbl_1_rodata_780C)[0];
    *(f32*)(lbl_803CC1B8[0] + 0x18) = (&lbl_1_rodata_7810)[0];
    *(f32*)(lbl_803CC1B8[0] + 0x1C) = (&lbl_1_rodata_7810)[0];
    *(f32*)(lbl_803CC1B8[0] + 0x20) = lbl_1_rodata_77E4[0];
    *(f32*)(lbl_803CC1B8[0] + 0x24) = lbl_1_rodata_77E4[0];
    fn_1_1F23C((ChallengeProjectionState*)lbl_1_bss_6BF4);
    *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
    lbl_1_bss_6BE4[0] = 0.0f;
    lbl_1_bss_6BE4[1] = 0.0f;
    lbl_1_bss_6BE4[2] = 0.0f;
    lbl_1_bss_6BE4[3] = 0.0f;
}

extern const f64 lbl_1_rodata_7878;
extern const f64 lbl_1_rodata_7880;
extern const f64 lbl_1_rodata_7888;

// .text:0x22F4C size:0x14C
void fn_1_22F4C(s32 h, s32 w, f32* out, f32* cur, f32* prev) {
    f64 c = (lbl_1_rodata_7878 * *(f32*)(lbl_1_data_FB98 + 0x928)) / *(f32*)(lbl_1_data_FB98 + 0x924);
    f32 k;
    f32 m;
    s32 y;
    s32 x;
    s32 i;
    s32 row;

    c = c * c;
    k = c;
    m = lbl_1_rodata_7880 - lbl_1_rodata_7888 * c;
    for (y = 0, row = 0; y < h; y++, row += w) {
        for (x = 0, i = row; x < w; x++, i++) {
            out[i] = m * cur[i]
                + k * (cur[(x + 1) % w + row] + (cur[(x + (w - 1)) % w + row]
                + (cur[x + w * ((y + (h - 1)) % h)] + cur[x + w * ((y + 1) % h)])))
                - prev[i];
            out[i] *= *(f32*)(lbl_1_data_FB98 + 0x92C);
            
        }
    }
}

extern const f32 lbl_1_rodata_77F8;
extern const f32 lbl_1_rodata_7854;
extern void fn_80038E2C(void*);

// .text:0x22DF4 size:0x158
void fn_1_22DF4(ChallengeCurveDrawing* arg) {
    arg->scale = lbl_1_rodata_77F8;
    arg->unk1C = lbl_1_rodata_7854;
    arg->unk25 = 0;
    arg->steps = 10;
    arg->pointCount = 10;
    arg->drawFlat = 1;
    arg->colorMode = 0;
    arg->drawFull = 0;
    fn_80038E2C(&lbl_1_bss_6FB8);
    fn_1_21180(arg);
}

extern u32 lbl_1_data_10384[];
extern f32 lbl_1_data_104A4;

// .text:0x248BC size:0x1D0
void fn_1_248BC(s32 count) {
    u8 width;
    GXTexOffset offset;
    s32 i;
    ChallengePathNode* node;

    GXGetLineWidth(&width, &offset);
    GXSetLineWidth(0x18, offset);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, count);
    i = count;
    while (i-- != 0) {
        node = &lbl_1_bss_43F68[i];
        GXWGFifo.f32 = node->position.x;
        GXWGFifo.f32 = node->position.y;
        GXWGFifo.f32 = node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i];
    }
    GXSetLineWidth(width, offset);
    GXBegin(GX_LINES, GX_VTXFMT0, count * 4);
    i = count;
    while (i-- != 0) {
        node = &lbl_1_bss_43F68[i];
        GXWGFifo.f32 = node->position.x;
        GXWGFifo.f32 = node->position.y;
        GXWGFifo.f32 = node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i];
        GXWGFifo.f32 = lbl_1_data_104A4 * node->up.x + node->position.x;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->up.y + node->position.y;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->up.z + node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i];
        GXWGFifo.f32 = node->position.x;
        GXWGFifo.f32 = node->position.y;
        GXWGFifo.f32 = node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i] ^ 0xFFFFFF00;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->side.x + node->position.x;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->side.y + node->position.y;
        GXWGFifo.f32 = lbl_1_data_104A4 * node->side.z + node->position.z;
        GXWGFifo.u32 = lbl_1_data_10384[i] ^ 0xFFFFFF00;
    }
}

extern const f32 lbl_1_rodata_7808[];
extern const f32 lbl_1_rodata_78C4[];
extern const f32 lbl_1_rodata_78C8[];

// .text:0x24A8C size:0x1C0
void fn_1_24A8C(void) {
    u8* q = lbl_803CC1B8[0];
    ChallengeCurveTiming* tm;
    s32 n;
    f32 t;

    fn_80038E2C(&lbl_1_bss_45868);
    tm = &lbl_1_bss_45868;
    tm->params[0] = *(u16*)(q + 0x1A);
    tm->params[1] = *(f32*)(q + 0x14);
    tm->params[2] = *(u16*)(q + 0x18) * lbl_1_rodata_78C4[0];
    tm->params[3] = *(u16*)(q + 0x1C) * lbl_1_rodata_78C4[0];
    tm->params[4] = *(u16*)(q + 0x1E) * lbl_1_rodata_78C4[0];
    tm->params[5] = *(u16*)(q + 0x20) / lbl_1_rodata_78C8[0];
    n = q[0x2A];
    tm->steps = n;
    t = lbl_1_rodata_77E4[0] / (f32)n;
    tm->step = t;
    tm->stepSq = t * t;
    tm->inv = lbl_1_rodata_77E4[0] / ((&lbl_1_rodata_780C)[0] * t);
    if (lbl_803C77B8._00 & 0x40) {
        tm->steps = 1;
    }
    fn_80038CD0(q[0x2B], &lbl_1_bss_45868, lbl_1_bss_43F68, lbl_1_rodata_7808[0], *(u16*)(q + 0x24) * lbl_1_rodata_78C4[0]);
}
