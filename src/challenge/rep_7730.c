#include "challenge/rep_7730.h"

#include "static/UnknownHomes_Static.h"
#include "Dolphin/gx.h"
#include "main/file_800BD8C4.h"
#include "main/file_8000BA3C.h"
#include "main/file_8000F150.h"
#include "C3/control.h"
#include "stl/math.h"

// POOL BEGIN (high-to-low; memory order is the reverse)
static Mtx44 lbl_1_bss_47010;
static u8 lbl_1_bss_45890[0x17A8 - 0x28];
static ChallengeCurveTiming lbl_1_bss_45868;
static ChallengePathNode lbl_1_bss_43F68[100];
static Mtx lbl_1_bss_43F38;
static ChallengeCameraState lbl_1_bss_43EE0;
static Vec lbl_1_bss_F6E0[160][112];
static f32 lbl_1_bss_76E0[2][32 * 128];
static f32 lbl_1_bss_74E0[0x200 / 4];
static ChallengeCurvePoint lbl_1_bss_6FE0[20];
static ChallengeCurveTiming lbl_1_bss_6FB8;
static u8 lbl_1_bss_6FB4[4];
static f32 lbl_1_bss_6FA8[3];
static void* lbl_1_bss_6FA4[1];
static GXTexObj lbl_1_bss_6EA4[8];
static GXTlutObj lbl_1_bss_6E44[8];
static u32 lbl_1_bss_6E24[8];
static u8 lbl_1_bss_6D48[0xDC];
static ChallengeProjectionState lbl_1_bss_6BF4;
static f32 lbl_1_bss_6BE4[4];
static ActorObjectTable* lbl_1_bss_6BE0[1];
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

extern const f32 lbl_1_rodata_77E4;
extern void fn_1_272DC(void*, s32);
extern void fn_1_AF4(s32, s32, f32);


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
        GXSetTexCoordGen2(stage, GX_TG_MTX2X4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
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
    fn_800385F0(&lbl_1_bss_6BF4,
        *(f32*)(lbl_803CC1B8[0] + 0x14), *(f32*)(lbl_803CC1B8[0] + 0x18),
        *(f32*)(lbl_803CC1B8[0] + 0x1C), *(f32*)(lbl_803CC1B8[0] + 0x20));
    state->depth = -*(f32*)(lbl_803CC1B8[0] + 0x24);
    state->pos.y += lbl_1_rodata_780C;
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
        lbl_1_rodata_7860, lbl_1_rodata_7864, (&lbl_1_rodata_77E4)[0], lbl_1_rodata_7868);
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
    fn_1_AF4(20, 20, (&lbl_1_rodata_77E4)[0]);
    if (*(u32*)(lbl_803CC1B8[0] + 0x2C) & 2) {
        fn_1_1E5D0(&lbl_1_bss_6BF4);
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
    fn_80037B18(&lbl_1_bss_6BF4, &axis, lbl_1_bss_6BE4[0]);
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
extern void fn_80034E20(void* group, void* desc);
extern void fn_1_267BC(void);
extern u8 lbl_1_data_FB98[];
extern ChallengeSpriteDesc lbl_1_data_10344;
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
        fn_80034E20(*(u8**)(queue + 0x14), &lbl_1_data_10344);
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
    t = ((&lbl_1_rodata_77E4)[0] / (f32)n) / lbl_1_rodata_784C[0];
    tm->step = t;
    tm->stepSq = t * t;
    tm->inv = (&lbl_1_rodata_77E4)[0] / ((&lbl_1_rodata_780C)[0] * t);
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
    *(f32*)(lbl_803CC1B8[0] + 0x20) = (&lbl_1_rodata_77E4)[0];
    *(f32*)(lbl_803CC1B8[0] + 0x24) = (&lbl_1_rodata_77E4)[0];
    fn_1_1F23C(&lbl_1_bss_6BF4);
    *(s16*)(lbl_803CC1B8[0] + 0x10) = 0;
    lbl_1_bss_6BE4[0] = 0.0f;
    lbl_1_bss_6BE4[1] = 0.0f;
    lbl_1_bss_6BE4[2] = 0.0f;
    lbl_1_bss_6BE4[3] = 0.0f;
}

extern const f64 lbl_1_rodata_7878;
extern const f64 lbl_1_rodata_7880;
extern const f64 lbl_1_rodata_7888;

// NONMATCHING 69%: original keeps i*4 index (lfsx base,r31) plus a dead `i` counter; ours strength-reduces to 3 pointers
// .text:0x22F4C size:0x14C
#if NONMATCHING
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
#endif

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

// NONMATCHING 91%: f3/f6 swap for 1.0f vs int->float magic, and the tail 78C4 load is CSE'd with the head (orig reloads, addi form)
// .text:0x24A8C size:0x1C0
#if NONMATCHING
void fn_1_24A8C(void) {
    u8* q = lbl_803CC1B8[0];
    s32 n;
    f32 t;

    fn_80038E2C(&lbl_1_bss_45868);
    lbl_1_bss_45868.params[0] = *(u16*)(q + 0x1A);
    lbl_1_bss_45868.params[1] = *(f32*)(q + 0x14);
    lbl_1_bss_45868.params[2] = *(u16*)(q + 0x18) * lbl_1_rodata_78C4[0];
    lbl_1_bss_45868.params[3] = *(u16*)(q + 0x1C) * lbl_1_rodata_78C4[0];
    lbl_1_bss_45868.params[4] = *(u16*)(q + 0x1E) * lbl_1_rodata_78C4[0];
    lbl_1_bss_45868.params[5] = *(u16*)(q + 0x20) / lbl_1_rodata_78C8[0];
    n = q[0x2A];
    lbl_1_bss_45868.steps = n;
    t = (&lbl_1_rodata_77E4)[0] / (f32)n;
    lbl_1_bss_45868.step = t;
    lbl_1_bss_45868.stepSq = t * t;
    lbl_1_bss_45868.inv = (&lbl_1_rodata_77E4)[0] / ((&lbl_1_rodata_780C)[0] * t);
    if (lbl_803C77B8._00 & 0x40) {
        lbl_1_bss_45868.steps = 1;
    }
    fn_80038CD0(q[0x2B], &lbl_1_bss_45868, lbl_1_bss_43F68, lbl_1_rodata_7808[0], *(u16*)(q + 0x24) * lbl_1_rodata_78C4[0]);
}
#endif

extern void fn_1_26D28(void*, u16, u16, u16, void*);
extern void fn_1_27330(void*);
extern void fn_80037BAC(void*);

// .text:0x1F05C size:0x1E0
void fn_1_1F05C(void) {
    u8* q;

    if (*(u32*)(lbl_803CC1B8[0] + 0x2C) & 1) {
        *(s16*)(lbl_803CC1B8[0] + 0x10) = fn_1_1E90C(*(s16*)(lbl_803CC1B8[0] + 0x10), lbl_803C77B8._00,
            lbl_803C77B8._02, *(u16*)((u8*)&lbl_803C77B8 + 4));
    } else {
        fn_1_26D28(lbl_1_bss_6D48, lbl_803C77B8._00, lbl_803C77B8._02, *(u16*)((u8*)&lbl_803C77B8 + 4),
            (u8*)&lbl_803C77B8 + 0x10);
    }
    if (lbl_803C77B8._02 & 0x200) {
        q = lbl_803CC1B8[0];
        if (*(u32*)(q + 0x2C) & 1) {
            *(void (**)(void))q = fn_1_24778;
        } else {
            *(u32*)(q + 0x2C) ^= 1;
        }
    } else if (lbl_803C77B8._02 & 0x1000) {
        *(u32*)(lbl_803CC1B8[0] + 0x2C) ^= 1;
    }
    fn_1_27330(lbl_1_bss_6D48);
    q = lbl_803CC1B8[0];
    switch (*(s32*)(q + 0x28)) {
    case 0:
        if (*(u32*)(q + 0x2C) & 4) {
            *(u32*)(q + 0x2C) ^= 4;
            fn_1_1DD94();
        }
        fn_80037BAC(&lbl_1_bss_6BF4);
        break;
    }
    q = lbl_803CC1B8[0];
    if (*(u32*)(q + 0x2C) & 1) {
        fn_1_1E8C0(*(s16*)(q + 0x10));
    }
    fn_1_1EFF4();
}

typedef struct {
    u32 value;
} ChallengeLightColor;

extern ChallengeLightColor lbl_1_rodata_77B0;
extern const f32 lbl_1_rodata_7840;
extern void LITAlloc(void**);
extern void LITInitAttn(void*, f32, f32, f32, f32, f32, f32);
extern void LITInitPos(void*, f32, f32, f32);
extern void LITInitDir(void*, f32, f32, f32);
extern void LITInitColor(void*, ChallengeLightColor);
extern void LoadActorLayout(void*);
extern void convertGeometryAndSknHeader(void*, s32);
extern void fn_800B2C08(void*, s32);
extern void fn_800BD548(ActorObject*, s32, ...);

extern const f32 lbl_1_rodata_77E4_s;
// NONMATCHING 99.8%: LITInitPos: orig `lis r3,7840; lis r4,6FA4; addi r3,r4` (float const lis first), ours swaps r3/r4
// .text:0x20E00 size:0x18C
#if NONMATCHING
void fn_1_20E00(u8* obj) {
    ChallengeLightColor color = lbl_1_rodata_77B0;
    u8* data;
    u16 i;
    u8* layout;
    u8* geo;

    LITAlloc(lbl_1_bss_6FA4);
    LITInitAttn(lbl_1_bss_6FA4[0], 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    LITInitPos(lbl_1_bss_6FA4[0], lbl_1_rodata_7840, lbl_1_rodata_7840, lbl_1_rodata_7840);
    LITInitDir(lbl_1_bss_6FA4[0], 0.0f, 0.0f, 0.0f);
    LITInitColor(lbl_1_bss_6FA4[0], color);
    data = *(u8**)(obj + 0x14);
    layout = data + ((s32*)data)[0];
    geo = data + ((s32*)data)[1];
    lbl_1_bss_6BE0[0] = ActorObjectInitTable(20);
    LoadActorLayout(layout);
    convertGeometryAndSknHeader(geo, 0);
    haveActLayoutPointToGeoHeader(layout, geo);
    for (i = 0; i < 20; i++) {
        fn_800BDC88(lbl_1_bss_6BE0[0], i, i, layout, 0, 0);
        fn_800B2C08(lbl_1_bss_6BE0[0]->objects[i].actor, 0);
        fn_800BD548(&lbl_1_bss_6BE0[0]->objects[i], 1, lbl_1_bss_6FA4[0]);
    }
}
#endif

// 99.8%: same LITInitPos r3/r4 swap as fn_1_20E00 (inlined here)
// .text:0x20BD8 size:0x1F0
void fn_1_20BD8(void) {
    u8* q = lbl_803CC1B8[0];
    u8* object;

    switch (q[0x25]) {
    case 0:
        object = fn_800B0A5C_insertQueue((void*)fn_1_20F8C, 1);
        *(s16*)(object + 0x10) = 0;
        q[0x25]++;
        break;
    case 1:
        if (*(s16*)(q + 0x10) != 0) {
            fn_1_20E00(q);
            object = *(u8**)(q + 0xC);
            *(s16*)(object + 0x10) = 1;
            fn_800B0A14_removeQueue(object);
        }
        break;
    }
}


// .text:0x1F418 size:0x200
void fn_1_1F418(u8* menu) {
    s32 i;
    s32 v;
    u8 cur;

    for (i = 0; i < 4; i++) {
        cur = menu[0x21];
        switch (i) {
        case 0:
            if (i == cur) {
                if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 1) {
                    if (menu[0x20] == 0) {
                        menu[0x20] = 2;
                    }
                    menu[0x20]--;
                } else if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 2) {
                    menu[0x20]++;
                    if (menu[0x20] == 2) {
                        menu[0x20] = 0;
                    }
                }
            }
            break;
        case 1:
            v = (s32)fn_80048EA8(0);
            if (i == menu[0x21]) {
                if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 1) {
                    v--;
                } else if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 2) {
                    v++;
                }
                fn_80048E00(0, v);
            }
            break;
        case 2:
            v = (s32)fn_80048EA8(1);
            if (i == menu[0x21]) {
                if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 1) {
                    v--;
                } else if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 2) {
                    v++;
                }
                fn_80048E00(1, v);
            }
            break;
        case 3:
            if (i == cur) {
                if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 1) {
                    if (*(u32*)(menu + 0x1C) != 0) {
                        (*(u32*)(menu + 0x1C))--;
                    }
                } else if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 2) {
                    (*(u32*)(menu + 0x1C))++;
                }
            }
            break;
        }
    }
    if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 8) {
        if (menu[0x21] == 0) {
            menu[0x21] = 4;
        }
        menu[0x21]--;
    } else if (*(u16*)((u8*)&lbl_803C77B8 + 4) & 4) {
        menu[0x21]++;
        if (menu[0x21] == 4) {
            menu[0x21] = 0;
        }
    }
}

// .text:0x22644 size:0x230
void fn_1_22644(void) {
    u8* q = lbl_803CC1B8[0];

    fn_800AD038(lbl_80366158[2]);
    q[0x25] = 0;
    fn_1_22DF4((ChallengeCurveDrawing*)lbl_803CC1B8[0]);
    fn_1_23AD8(lbl_1_bss_47010, &lbl_1_bss_43EE0.camera, &lbl_1_bss_43EE0.target);
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_225B8;
}

extern u8 lbl_1_data_10518[];

// 99.5%: saved regs q=r25/i=r26 in orig, ours q=r26/i=r25 (decl/assign order variants did not help)
// .text:0x2004C size:0x258
void fn_1_2004C(void) {
    u8* q = lbl_803CC1B8[0];
    s32 ids[9] = { 5, 6, 7, 8, 9, 13, 0x60, 0x61, 0x55 };
    u8* data;
    u32 i;

    switch (q[0x21]) {
    case 0:
        *(void**)(q + 0x18) = (void*)ARAMTransfer(lbl_1_data_10518, 0, 0, 0);
        q[0x21]++;
        break;
    case 1:
        if ((s32)lbl_803C6CF8[0x715] == 1) {
            data = *(u8**)(q + 0x18);
            *(u8**)(q + 0x14) = data + *(s32*)(data + 0x14);
            convertTextureHeader(*(void**)(q + 0x14));
            for (i = 0; i < 8; i++) {
                lbl_1_bss_6E24[i] = i;
                if (fn_1_2051C((ChallengeTextureHeader*)(*(u8**)(q + 0x14) + ids[i] * 32 + 4),
                        &lbl_1_bss_6EA4[i], &lbl_1_bss_6E44[i], i)) {
                    lbl_1_bss_6E24[i] |= 0x80000000;
                }
            }
            q[0x21] = 0;
            *(void (**)(void))lbl_803CC1B8[0] = fn_1_202A4;
        }
        break;
    }
}

extern void* _OSAllocFromHeap(s32, s32);
extern void* memcpy(void*, const void*, u32);
extern void DCStoreRangeNoSync(void*, u32);
extern void PPCSync(void);

// .text:0x1DA54 size:0x290
void fn_1_1DA54(void) {
    u8* q = lbl_803CC1B8[0];
    ChallengeTextureHeader* tex;
    u8* object;
    s32 size;

    if ((s32)lbl_803C6CF8[0x715] != 1) {
        return;
    }
    *(u8**)(q + 0x18) = *(u8**)(q + 0x14) + *(s32*)(*(u8**)(q + 0x14) + 0x14);
    convertTextureHeader(*(void**)(q + 0x18));
    *(u16*)(q + 0x28) = 2;
    *(u16*)(q + 0x1C) = 3;
    *(u16*)(q + 0x1E) = 0;
    *(u16*)(q + 0x22) = 3;
    *(u16*)(q + 0x20) = 3;
    *(u16*)(q + 0x24) = 0;
    *(u16*)(q + 0x26) = 0;
    *(ChallengeTextureHeader**)(q + 0x2C) = _OSAllocFromHeap(0x20, 0x20);
    memcpy(*(void**)(q + 0x2C), *(u8**)(q + 0x18) + 0x44, 0x20);
    tex = *(ChallengeTextureHeader**)(q + 0x2C);
    if (tex->palette != NULL) {
        switch (tex->paletteFormat) {
        case 0:
        case 1:
        case 2:
            size = tex->paletteEntries * 2;
            (*(ChallengeTextureHeader**)(q + 0x2C))->palette = _OSAllocFromHeap(0x20, size);
            memcpy((*(ChallengeTextureHeader**)(q + 0x2C))->palette, *(void**)(*(u8**)(q + 0x18) + 0x48), size);
            break;
        }
        DCStoreRangeNoSync((*(ChallengeTextureHeader**)(q + 0x2C))->palette, size);
        tex = *(ChallengeTextureHeader**)(q + 0x2C);
        switch (tex->format) {
        case 8:
            size = (tex->width + 7) / 8 * 8 * ((tex->height + 7) / 8 * 8);
            break;
        case 9:
            size = (tex->width + 7) / 8 * 8 * ((tex->height + 3) / 4 * 4);
            break;
        default:
            fn_800AD038(lbl_80366158[2]);
            object = *(u8**)(lbl_803CC1B8[0] + 0xC);
            *(s16*)(object + 0x10) = 1;
            fn_800B0A14_removeQueue(object);
            return;
        }
    } else {
        switch (tex->format) {
        case 14:
            size = (tex->width + 7) / 8 * 8 * ((tex->height + 7) / 8 * 8);
            break;
        default:
            fn_800AD038(lbl_80366158[2]);
            object = *(u8**)(lbl_803CC1B8[0] + 0xC);
            *(s16*)(object + 0x10) = 1;
            fn_800B0A14_removeQueue(object);
            return;
        }
    }
    (*(ChallengeTextureHeader**)(q + 0x2C))->image = _OSAllocFromHeap(0x20, size);
    memcpy((*(ChallengeTextureHeader**)(q + 0x2C))->image, *(void**)(*(u8**)(q + 0x18) + 0x44), size);
    DCStoreRangeNoSync((*(ChallengeTextureHeader**)(q + 0x2C))->image, size);
    PPCSync();
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_1D944;
}

extern const f32 lbl_1_rodata_78AC;
extern const f32 lbl_1_rodata_78B0;
extern const f32 lbl_1_rodata_78B4;
extern const f32 lbl_1_rodata_78B8;
extern const f32 lbl_1_rodata_78BC;
extern const f32 lbl_1_rodata_78C0;
extern double cos(double);
extern int rand(void);
extern void* memset(void*, int, u32);

// .text:0x24410 size:0x29C
void fn_1_24410(void) {
    u8* q = lbl_803CC1B8[0];
    s32 i;
    s32 j;

    fn_1_23AD8(lbl_1_bss_47010, &lbl_1_bss_43EE0.camera, &lbl_1_bss_43EE0.target);
    lbl_1_bss_43EE0.unk30 = 0;
    lbl_1_bss_43EE0.unk38 = (&lbl_1_rodata_77D8)[0];
    lbl_1_bss_43EE0.unk32 = 0;
    q[0x27] = 0x40;
    q[0x29] = 0x40;
    q[0x28] = 0x40;
    q[0x2A] = 0;
    *(f32*)(q + 0x14) = lbl_1_rodata_78AC;
    *(f32*)(q + 0x18) = lbl_1_rodata_78B0;
    *(u16*)(q + 0x24) = 0;
    *(f32*)(q + 0x1C) = lbl_1_rodata_78B4;
    *(f32*)(q + 0x20) = lbl_1_rodata_78B8;
    q[0x2B] = 1;
    for (i = 0; i < 0x80; i++) {
        lbl_1_bss_74E0[i] = cos(lbl_1_rodata_78BC * (lbl_1_rodata_780C * ((f32)i * lbl_1_rodata_78C0)));
    }
    q[0x2C] = 0;
    memset(lbl_1_bss_76E0, 0, sizeof(lbl_1_bss_76E0));
    for (j = 0; j < 0x20; j++) {
        i = rand() % 32 * 128;
        i += rand() % 128;
        lbl_1_bss_76E0[0][i] = lbl_1_rodata_77E4;
    }
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_23B54;
}

extern const f32 lbl_1_rodata_77E8;
extern void fn_80023F0C(void*, ChallengeTextureHeader*, s32, s32, s32, s32, s32, s32);
extern void gOz_GXSetTexture(s32, s32, s32);
extern void DCStoreRange(void*, u32);

// 91%: orig divides height/64, width/32 with srawi/addze (signed); ours srwi (CW knows u16 >= 0); loop regs rotate
// .text:0x1D694 size:0x2B0
void fn_1_1D694(u8* obj) {
    ChallengeTextureHeader* tex;
    u8* src;
    void* dst;
    s32 rows;
    s32 cols;
    s32 y;
    s32 x;
    s32 v;

    if (obj[0x18] != 0) {
        tex = *(ChallengeTextureHeader**)(obj + 8);
        src = *(u8**)(obj + 0x10);
        dst = *(void**)(obj + 0xC);
        memset(tex->image, 0, tex->width * tex->height);
        rows = tex->height / 64;
        cols = tex->width / 32;
        for (y = 0; y < rows; y++) {
            for (x = 0; x < cols; x++) {
                if (x & lbl_803CBBC0[0]) {
                    v = src[y * cols + x];
                    fn_80023F0C(dst, tex, v % cols * 32, v / cols * 64, 0x20, 0x40, x * 32, y * 64);
                }
            }
        }
        DCStoreRange(tex->image, tex->width * tex->height);
    }
    {
        Mtx proj;
        Mtx view;

        C_MTXOrtho(*(Mtx44*)proj, lbl_1_rodata_77D8, lbl_1_rodata_77DC[0], lbl_1_rodata_77D8, lbl_1_rodata_77E0[0], lbl_1_rodata_77D8, (&lbl_1_rodata_77E4)[0]);
        PSMTXIdentity(view);
        GXSetProjection(*(Mtx44*)proj, GX_ORTHOGRAPHIC);
        GXLoadPosMtxImm(view, 0);
        GXSetCurrentMtx(0);
    }
    gOz_GXSetTexture(0, 0, 0);
    SetDisplayStateTexture(*(void**)(obj + 8), 0, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 0;
    {
        f32 y = (*(ChallengeTextureHeader**)(obj + 8))->height;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = y;
    }
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 0;
    GXWGFifo.u16 = 1;
    {
        f32 x = (*(ChallengeTextureHeader**)(obj + 8))->width;
        f32 y = (*(ChallengeTextureHeader**)(obj + 8))->height;
        GXWGFifo.f32 = x;
        GXWGFifo.f32 = y;
    }
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 1;
    GXWGFifo.u16 = 1;
    GXWGFifo.f32 = (*(ChallengeTextureHeader**)(obj + 8))->width;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
    GXWGFifo.u32 = 0xFFFFFFFF;
    GXWGFifo.u16 = 1;
    GXWGFifo.u16 = 0;
}

extern const f32 lbl_1_rodata_7844;
extern const f32 lbl_1_rodata_7848;

// .text:0x21040 size:0x140
void fn_1_21040(void) {
    u32 color;
    s32 pos;
    s32 i;

    GXBegin(GX_LINES, GX_VTXFMT0, 44);
    for (i = 0; i < 11; i++) {
        color = 0xFFFFFFFF;
        if (i == 5) {
            color = 0xFF0000FF;
        }
        pos = (i - 5) * 10;
        GXWGFifo.f32 = pos;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7844;
        GXWGFifo.u32 = color;
        GXWGFifo.f32 = pos;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7848;
        GXWGFifo.u32 = color;
        if (i == 5) {
            color = 0x00FF00FF;
        }
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7844;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = pos;
        GXWGFifo.u32 = color;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7848;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = pos;
        GXWGFifo.u32 = color;
    }
}

extern const f64 lbl_1_rodata_7828;
extern const f64 lbl_1_rodata_7830;
extern const f64 lbl_1_rodata_7838;
extern Vec lbl_1_data_104D0;

// .text:0x20950 size:0x288
void fn_1_20950(ChallengeCurvePoint* points, s32 count, MtxPtr camera) {
    ActorObject* obj;
    s32 i;
    Vec delta;
    Vec mid;
    Quaternion rot;
    Quaternion align;
    Mtx mtx;
    f32 angle;
    f32 zero;

    i = 20;
    while (i-- != 0) {
        obj = &lbl_1_bss_6BE0[0]->objects[i];
        obj->animateBones = i < count;
        if (i < count) {
            PSVECSubtract(&points[i + 1].position, &points[i].position, &delta);
            PSVECScale(&delta, lbl_1_rodata_7814[0], &mid);
            PSVECAdd(&points[i].position, &mid, &mid);
            CTRLSetTranslation((Control*)obj->worldControl, mid.x, -mid.y, mid.z);
            if (PSVECMag(&delta)) {
                PSVECNormalize(&delta, &delta);
                delta.y = -delta.y;
                mid.x = lbl_1_rodata_77E4;
                mid.y = lbl_1_rodata_77D8;
                mid.z = lbl_1_rodata_77D8;
                C_QUATRotAxisRad(&rot, &mid,
                    lbl_1_rodata_7828 * (lbl_1_rodata_7830 + (i & 1)) / lbl_1_rodata_7838);
                angle = acos(PSVECDotProduct(&delta, &mid));
                PSVECCrossProduct(&mid, &delta, &mid);
                if (PSVECMag(&mid)) {
                    C_QUATRotAxisRad(&align, &mid, angle);
                    PSQUATMultiply(&align, &rot, &rot);
                }
                CTRLSetQuat((Control*)obj->worldControl, rot.x, rot.y, rot.z, rot.w);
            }
            CTRLSetScale((Control*)obj->worldControl, lbl_1_data_104D0.x, lbl_1_data_104D0.y, lbl_1_data_104D0.z);
            fn_800BDA24(obj);
        }
        zero = *(volatile f32*)&lbl_1_rodata_77D8;
        PSMTXTrans(mtx, zero, zero, zero);
        PSMTXConcat(camera, mtx, mtx);
        obj->actor->flags98 |= 3;
    }
    fn_800BD670(lbl_1_bss_6BE0[0], (u32)camera);
}

extern const f32 lbl_1_rodata_7894;
extern const f32 lbl_1_rodata_7898;

// NONMATCHING 96%: register coloring only; orig reuses the cols param register for the inner counter (r30) and keeps a copy in r31
// .text:0x23804 size:0x2D4
#if NONMATCHING
void fn_1_23804(s32 arg0, s32 arg1, s32 rows, s32 cols, f32 arg4, f32 arg5) {
    Vec* rowBase;
    Vec* p;
    s32 c;
    s32 odd;

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
    GXLoadPosMtxImm(lbl_1_bss_43EE0.view, 0);
    GXSetCurrentMtx(0);
    rowBase = &lbl_1_bss_F6E0[0][rows];
    while (rowBase--, --rows != 0) {
        c = cols;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, cols * 2);
        odd = rows & 1;
        while (c-- != 0) {
            p = &rowBase[c * 112];
            GXWGFifo.f32 = p[0].x;
            GXWGFifo.f32 = p[0].z;
            GXWGFifo.f32 = p[0].y;
            GXWGFifo.u32 = odd ? 0xFFFFFFFF : 0x0000FFFF;
            GXWGFifo.f32 = p[-1].x;
            GXWGFifo.f32 = p[-1].z;
            GXWGFifo.f32 = p[-1].y;
            if (odd) {
                GXWGFifo.u32 = 0x0000FFFF;
            } else {
                GXWGFifo.u32 = 0xFFFFFFFF;
            }
        }
    }
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 8);
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0x0000FFFF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0x0000FFFF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0xFF0000FF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7898;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0x0000FFFF;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
    GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7894;
    GXWGFifo.u32 = 0x0000FFFF;
}
#endif

#define CHALLENGE_PAD_TRIGGER (*(u16*)((u8*)&lbl_803C77B8 + 4)) // TODO type: lbl_803C77B8_s lacks the 0x04 field

// .text:0x1FD78 size:0x2D4
void fn_1_1FD78(ChallengeTextureStages* menu) {
    u32 step;
    s32 i;
    s32 v;
    u8 cur;

    step = 1;
    if (lbl_803C77B8._00 & 0x20) {
        step = 100;
    }
    for (i = 0; i < 6; i++) {
        cur = menu->cursor;
        switch (i) {
        case 0:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (menu->toggle == 0) {
                        menu->toggle = 2;
                    }
                    menu->toggle--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    menu->toggle++;
                    if (menu->toggle == 2) {
                        menu->toggle = 0;
                    }
                }
            }
            break;
        case 1:
            v = fn_80048EA8(0);
            if (i == menu->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    v--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    v++;
                }
                fn_80048E00(0, v);
            }
            break;
        case 2:
            v = fn_80048EA8(1);
            if (i == menu->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    v--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    v++;
                }
                fn_80048E00(1, v);
            }
            break;
        case 3:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (menu->value <= step) {
                        menu->value = 0;
                    } else {
                        menu->value -= step;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    menu->value += step;
                    if (menu->value > 0x1000) {
                        menu->value = 0x1000;
                    }
                }
            }
            break;
        case 4:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    menu->unk23--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    menu->unk23++;
                }
            }
            break;
        case 5:
            if (i == cur) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (menu->stageCount > 1) {
                        menu->stageCount--;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (menu->stageCount < 4) {
                        menu->stageCount++;
                    }
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (menu->cursor == 0) {
            menu->cursor = 6;
        }
        menu->cursor--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        menu->cursor++;
        if (menu->cursor == 6) {
            menu->cursor = 0;
        }
    }
}

extern const f32 lbl_1_rodata_77FC;

// NONMATCHING 97%: inlined fn_1_20640 keeps the texture index in a register (orig reloads *image for the tlut test) and the FIFO base gets a different saved reg
// .text:0x1F618 size:0x2E8
#if NONMATCHING
void fn_1_1F618(ChallengeTextureStages* stages) {
    s32 i;
    u32 index[1];
    f32 z;

    i = stages->value;
    while (i-- != 0) {
        index[0] = i % 4;
        fn_1_20640(stages, index);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        z = lbl_1_rodata_7814[0] - lbl_1_rodata_77FC * i;
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E0[0];
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77DC[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E0[0];
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77DC[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.f32 = z;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0;
    }
}
#endif

extern void fn_1_F2C(s32, s32, s32);

// .text:0x1E5D0 size:0x2F0
void fn_1_1E5D0(ChallengeProjectionState* body) {
    Vec b;
    Vec a;
    Vec* pb;

    fn_1_F2C(4, 0, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    PSMTXMultVec(body->world, &body->p1, &a);
    PSMTXMultVec(body->world, &body->p0, pb = &b);
    GXBegin(GX_LINES, GX_VTXFMT0, 2);
    GXWGFifo.f32 = a.x;
    GXWGFifo.f32 = a.y;
    GXWGFifo.f32 = a.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = b.x;
    GXWGFifo.f32 = b.y;
    GXWGFifo.f32 = b.z;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0x40;
    GXWGFifo.u8 = 0xFF;
    GXBegin(GX_LINES, GX_VTXFMT0, 4);
    PSVECScale(&body->pos, lbl_1_rodata_77E4, &a);
    PSVECAdd(&a, (Vec*)&body->quat, pb); // TODO type: reads quat.xyz as a vector
    GXWGFifo.f32 = a.x;
    GXWGFifo.f32 = a.y;
    GXWGFifo.f32 = a.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = b.x;
    GXWGFifo.f32 = b.y;
    GXWGFifo.f32 = b.z;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    PSVECScale(&body->angVel, lbl_1_rodata_77E4, pb);
    PSVECAdd(&a, pb, pb);
    GXWGFifo.f32 = a.x;
    GXWGFifo.f32 = a.y;
    GXWGFifo.f32 = a.z;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.f32 = b.x;
    GXWGFifo.f32 = b.y;
    GXWGFifo.f32 = b.z;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0;
    GXWGFifo.u8 = 0xFF;
    GXWGFifo.u8 = 0xFF;
    if (*(s32*)(lbl_803CC1B8[0] + 0x28) == 0) {
        PSVECSubtract(&body->p0, &body->p1, &a);
        PSVECScale(&a, lbl_1_bss_6BE4[0], &a);
        PSVECAdd(&body->p1, &a, &a);
        PSMTXMultVec(body->world, &a, &a);
        b.x = lbl_1_bss_6BE4[1];
        b.y = lbl_1_bss_6BE4[2];
        b.z = lbl_1_bss_6BE4[3];
        PSVECAdd(&a, pb, pb);
        GXBegin(GX_LINES, GX_VTXFMT0, 2);
        GXWGFifo.f32 = a.x;
        GXWGFifo.f32 = a.y;
        GXWGFifo.f32 = a.z;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.f32 = b.x;
        GXWGFifo.f32 = b.y;
        GXWGFifo.f32 = b.z;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0;
        GXWGFifo.u8 = 0xFF;
        GXWGFifo.u8 = 0xFF;
    }
}

extern const f32 lbl_1_rodata_78A4;
extern const f32 lbl_1_rodata_78D4;
extern const f32 lbl_1_rodata_78D8;
extern const f32 lbl_1_rodata_78DC;
extern const f32 lbl_1_rodata_78E0;

// NONMATCHING 89%: orig hoists the lbl_1_data_FB98 pool base into r30 before C_MTXFrustum; the inlined fn_1_24A8C has its own f-reg swap
// .text:0x25C68 size:0x330
#if NONMATCHING
void fn_1_25C68(void) {
    u8* q = lbl_803CC1B8[0];
    u8* cfg = lbl_1_data_FB98;
    GXColor clear;

    *(u32*)&clear = 0;
    GXSetCopyClear(clear, 0xFFFFFF);
    C_MTXFrustum(lbl_1_bss_47010, lbl_1_rodata_78D4, lbl_1_rodata_78D8, lbl_1_rodata_78DC, lbl_1_rodata_78E0,
        (&lbl_1_rodata_77E4)[0], lbl_1_rodata_7868);
    // TODO type: lbl_1_data_FB98 is the base of this file's static .data pool
    C_MTXLookAt(lbl_1_bss_43F38, (Vec*)(cfg + 0x8F4), (Vec*)(cfg + 0x8E8),
        (Vec*)(cfg + 0x900));
    *(u16*)(q + 0x18) = lbl_1_rodata_78A4 * *(f32*)(cfg + 0x8D0);
    *(u16*)(q + 0x1C) = lbl_1_rodata_78A4 * *(f32*)(cfg + 0x8D4);
    *(u16*)(q + 0x1A) = *(f32*)(cfg + 0x8D8);
    *(u16*)(q + 0x1E) = 0x20;
    q[0x2A] = *(s32*)(cfg + 0x8DC);
    *(u16*)(q + 0x22) = 10;
    q[0x2B] = 20;
    *(u16*)(q + 0x20) = lbl_1_rodata_78A4 * *(f32*)(cfg + 0x8E4);
    *(u16*)(q + 0x24) = lbl_1_rodata_78A4 * *(f32*)(cfg + 0x8E0);
    *(f32*)(q + 0x14) = lbl_1_rodata_7814[0];
    *(u16*)(q + 0x26) = 100;
    *(u16*)(q + 0x28) = 10;
    fn_1_24A8C();
    *(void (**)(void))lbl_803CC1B8[0] = fn_1_25064;
    q[0x2C] = 0;
}
#endif

extern const f32 lbl_1_rodata_7800;

static inline void fn_1_1DE60_adjust(f32* value, u16 held, s32 decrease, f32 min, f32 max) {
    f32 v;
    f32 step;

    step = lbl_1_rodata_77F8;
    v = *value;
    if (held & 0x40) {
        step = lbl_1_rodata_77FC;
    } else if (held & 0x20) {
        step = lbl_1_rodata_7800;
    }
    if (decrease) {
        step = -step;
    }
    v += step;
    if (v < min) {
        v = min;
    }
    if (v > max) {
        v = max;
    }
    *value = v;
}

static inline void fn_1_1E290_adjust(f32* value, u16 held, s32 decrease) {
    f32 v;
    f32 step;
    step = lbl_1_rodata_77F8;
    v = *value;
    if (held & 0x40) {
        step = lbl_1_rodata_77FC;
    } else if (held & 0x20) {
        step = lbl_1_rodata_7800;
    }
    if (decrease) {
        step = -step;
    }
    v += step;
    if (v < lbl_1_rodata_7804) {
        v = lbl_1_rodata_7804;
    }
    if (v > lbl_1_rodata_7808[0]) {
        v = lbl_1_rodata_7808[0];
    }
    *value = v;
}

// .text:0x1E290 size:0x340
s16 fn_1_1E290(s16 sel, u16 held, u16 pressed, u16 repeat) {
    if (sel < 0 || sel >= 3) {
        return sel;
    }
    if (repeat & 1) {
        switch (sel) {
        case 0:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.x, held, 1);
            break;
        case 1:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.y, held, 1);
            break;
        case 2:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.z, held, 1);
            break;
        }
    } else if (repeat & 2) {
        switch (sel) {
        case 0:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.x, held, 0);
            break;
        case 1:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.y, held, 0);
            break;
        case 2:
            fn_1_1E290_adjust(&lbl_1_bss_6BF4.angVel.z, held, 0);
            break;
        }
    } else if (repeat & 8) {
        sel--;
    } else if (repeat & 4) {
        sel++;
    }
    return sel;
}

extern s16 (*lbl_1_data_10668[])(s16, u16, u16, u16);
extern s32 lbl_1_data_10670[];

#if NONMATCHING
static inline f32 fn_1_1E90C_adjust(f32 value, u16 held, s32 decrease, f32 min, f32 max) {
    f32 v;
    f32 step;

    step = lbl_1_rodata_77F8;
    if (held & 0x40) {
        step = lbl_1_rodata_77FC;
    } else if (held & 0x20) {
        step = lbl_1_rodata_7800;
    }
    if (decrease) {
        step = -step;
    }
    v = value + step;
    if (v < min) {
        v = min;
    }
    if (v > max) {
        v = max;
    }
    return v;
}
#endif

// NONMATCHING 98%: f0/f1 swapped in the inlined step/clamp helper (orig negates into a fresh reg), r0/r4 in the modulo paths
// .text:0x1E90C size:0x6E8
#if NONMATCHING
s16 fn_1_1E90C(s16 sel, u16 held, u16 pressed, u16 repeat) {
    f32 length = *(f32*)(lbl_803CC1B8[0] + 0x14);
    f32 frac = *(f32*)(lbl_803CC1B8[0] + 0x18);
    f32 radius = *(f32*)(lbl_803CC1B8[0] + 0x1C);
    f32 mass = *(f32*)(lbl_803CC1B8[0] + 0x20);
    f32 height = *(f32*)(lbl_803CC1B8[0] + 0x24);
    s16 sub;

    sub = lbl_1_data_10668[*(s32*)(lbl_803CC1B8[0] + 0x28)]((s16)(sel - 8), held, pressed, repeat) + 8;
    if (sel != sub) {
        s32 n = lbl_1_data_10670[*(s32*)(lbl_803CC1B8[0] + 0x28)] + 8;
        sel = (sub + n) % n;
    } else if (pressed & 0x100) {
        switch (sel) {
        case 0:
            break;
        case 1:
            fn_1_1F23C(&lbl_1_bss_6BF4);
            break;
        case 2:
            *(u32*)(lbl_803CC1B8[0] + 0x2C) ^= 4;
            break;
        case 3:
            break;
        }
    } else if (repeat & 1) {
        switch (sel) {
        case 0:
            *(s32*)(lbl_803CC1B8[0] + 0x28) = (*(s32*)(lbl_803CC1B8[0] + 0x28) + 7) % 8;
            break;
        case 3:
            length = fn_1_1E90C_adjust(length, held, 1, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 4:
            frac = fn_1_1E90C_adjust(frac, held, 1, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 5:
            radius = fn_1_1E90C_adjust(radius, held, 1, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 7:
            height = fn_1_1E90C_adjust(height, held, 1, lbl_1_rodata_77D8, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 2) {
        switch (sel) {
        case 0:
            *(s32*)(lbl_803CC1B8[0] + 0x28) = (*(s32*)(lbl_803CC1B8[0] + 0x28) + 1) % 8;
            break;
        case 3:
            length = fn_1_1E90C_adjust(length, held, 0, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 4:
            frac = fn_1_1E90C_adjust(frac, held, 0, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 5:
            radius = fn_1_1E90C_adjust(radius, held, 0, lbl_1_rodata_77E4, lbl_1_rodata_7808[0]);
            break;
        case 6:
            mass = fn_1_1E90C_adjust(mass, held, 0, lbl_1_rodata_77D8, lbl_1_rodata_7808[0]);
            break;
        case 7:
            height = fn_1_1E90C_adjust(height, held, 0, lbl_1_rodata_77D8, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 8) {
        if (sel < 8) {
            s32 n = lbl_1_data_10670[*(s32*)(lbl_803CC1B8[0] + 0x28)];
            sel = (n + sel + 7) % (n + 8);
        }
    } else if (repeat & 4) {
        if (sel < 8) {
            sel = (sel + 1) % (lbl_1_data_10670[*(s32*)(lbl_803CC1B8[0] + 0x28)] + 8);
        }
    }
    *(f32*)(lbl_803CC1B8[0] + 0x14) = length;
    *(f32*)(lbl_803CC1B8[0] + 0x18) = frac;
    *(f32*)(lbl_803CC1B8[0] + 0x1C) = radius;
    *(f32*)(lbl_803CC1B8[0] + 0x20) = mass;
    *(f32*)(lbl_803CC1B8[0] + 0x24) = height;
    return sel;
}
#endif


// .text:0x1DE60 size:0x42C
s16 fn_1_1DE60(s16 sel, u16 held, u16 pressed, u16 repeat) {
    if (sel < 0 || sel >= 4) {
        return sel;
    }
    if (repeat & 1) {
        switch (sel) {
        case 0:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[0], held, 1, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 1:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[1], held, 1, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 2:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[2], held, 1, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 3:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[3], held, 1, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 2) {
        switch (sel) {
        case 0:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[0], held, 0, lbl_1_rodata_77D8, lbl_1_rodata_77E4);
            break;
        case 1:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[1], held, 0, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 2:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[2], held, 0, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        case 3:
            fn_1_1DE60_adjust(&lbl_1_bss_6BE4[3], held, 0, lbl_1_rodata_7804, lbl_1_rodata_7808[0]);
            break;
        }
    } else if (repeat & 8) {
        sel--;
    } else if (repeat & 4) {
        sel++;
    }
    return sel;
}

// NONMATCHING 73%: orig unrolls the index fill loop x8 (with a load/store-back of lbl_1_bss_6E24[k]) and uses two fewer saved regs; ours keeps it rolled
// .text:0x1F900 size:0x478
#if NONMATCHING
void fn_1_1F900(ChallengeTextureStages* stages) {
    s32 i;
    s32 j;
    s32 cell;
    s32 x;
    s32 y;
    u32 index[4];

    for (i = 0; i < stages->value; i++) {
        cell = i % 480 % 48;
        x = cell % 8;
        y = cell / 8;
        for (j = 0; j < stages->stageCount; j++) {
            index[j] = lbl_1_bss_6E24[(x + y) % 8];
        }
        fn_1_20640(stages, index);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXWGFifo.f32 = x * stages->unk23;
        GXWGFifo.f32 = y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0;
        GXWGFifo.f32 = x * stages->unk23;
        GXWGFifo.f32 = stages->unk23 + y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = stages->unk23 + x * stages->unk23;
        GXWGFifo.f32 = stages->unk23 + y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.f32 = stages->unk23 + x * stages->unk23;
        GXWGFifo.f32 = y * stages->unk23;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77D8;
        GXWGFifo.u32 = 0xFFFFFF80;
        GXWGFifo.u16 = 0x100;
        GXWGFifo.u16 = 0;
    }
}
#endif

extern const f32 lbl_1_rodata_78CC;
extern const f32 lbl_1_rodata_78D0;

// .text:0x24C4C size:0x418
void fn_1_24C4C(ChallengeRopeNode* nodes, s32 count, Vec* force, f32 springK, f32 damping, f32 restLen, f32 dtScale) {
    u8* q = lbl_803CC1B8[0];
    f32 drag;
    s32 k;
    ChallengeRopeNode* node;
    ChallengeRopeNode* prev;
    Vec d;
    Vec dv;
    Vec n;
    f32 first;
    f32 speed;
    f32 len;
    f32 damp;
    f32 stretch;
    f32 friction;
    f32 mag;
    f32 coef;
    s32 i;
    s32 j;

    drag = lbl_1_rodata_7820[0] * dtScale;
    first = lbl_1_rodata_77E4;
    i = count;
    while (i-- != 0) {
        node = &nodes[i];
        if (node->fixed != 0) {
            node->force.x = node->force.y = node->force.z = lbl_1_rodata_77D8;
        } else {
            node->force.x = node->force.z = lbl_1_rodata_77D8;
            node->force.y = lbl_1_rodata_78CC * node->mass;
        }
        speed = PSVECMag(&node->vel);
        if (speed != lbl_1_rodata_77D8) {
            PSVECScale(&node->vel, drag, &d);
            PSVECNormalize(&d, &d);
            PSVECScale(&d, (*(u16*)(q + 0x20) / lbl_1_rodata_78C8[0]) * (speed * speed), &d);
            PSVECAdd(&node->force, &d, &node->force);
        }
        if (first != lbl_1_rodata_77D8) {
            PSVECAdd(&node->force, force, &node->force);
            first = lbl_1_rodata_77D8;
        }
    }

    j = count;
    while (--j != 0) {
        node = &nodes[j];
        prev = &nodes[j - 1];
        PSVECSubtract(&node->pos, &prev->pos, &d);
        PSVECSubtract(&node->vel, &prev->vel, &dv);
        PSVECScale(&dv, dtScale, &dv);
        len = PSVECMag(&d);
        damp = damping * (PSVECDotProduct(&dv, &d) / len);
        PSVECNormalize(&d, &n);
        stretch = springK * (len - restLen);
        PSVECScale(&n, -(stretch + damp), &n);
        if (node->fixed == 0) {
            PSVECAdd(&node->force, &n, &node->force);
        }
        PSVECScale(&n, lbl_1_rodata_7820[0], &n);
        if (prev->fixed == 0) {
            PSVECAdd(&prev->force, &n, &prev->force);
        }
    }

    k = count;
    while (k-- != 0) {
        node = &nodes[k];
        if (node->fixed == 0 && node->pos.y <= *(u16*)(q + 0x28) / lbl_1_rodata_78D0
            && lbl_1_rodata_77D8 != PSVECMag(&node->vel)) {
            coef = *(u16*)(q + 0x1E) * lbl_1_rodata_78C4[0];
            friction = coef * node->force.y;
            if (friction < lbl_1_rodata_77D8) {
                friction = -friction;
            }
            memcpy(&d, &node->force, sizeof(Vec));
            d.y = lbl_1_rodata_77D8;
            mag = PSVECMag(&d);
            if (mag != lbl_1_rodata_77D8) {
                PSVECNormalize(&d, &d);
                if (friction > mag) {
                    PSVECScale(&d, -mag, &d);
                } else {
                    PSVECScale(&d, -friction, &d);
                }
                PSVECAdd(&d, &node->force, &node->force);
            }
        }
    }
}

extern const f32 lbl_1_rodata_786C;
extern const f64 lbl_1_rodata_7870;

#define CHALLENGE_PAD_STICK_Y (((u8*)&lbl_803C77B8)[0x15]) // TODO type: lbl_803C77B8_s lacks the 0x15 field

// NONMATCHING 99.8%: only the prologue's address temps get different GPRs (r5/r7/r9 vs r11/r5/r7)
// .text:0x22874 size:0x580
#if NONMATCHING
s32 fn_1_22874(void) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8[0];
    s32 speed;
    f32 fine;
    f32 step;
    f32 tiny;
    s32 i;
    u8 prevCount;

    if (lbl_803C77B8._00 & 0x20) {
        speed = 100;
    } else if (CHALLENGE_PAD_STICK_Y >= 0x50) {
        speed = 1;
    } else {
        speed = 10;
    }
    fine = lbl_1_rodata_786C * speed;
    step = lbl_1_rodata_77F8 * speed;
    tiny = lbl_1_rodata_77FC * speed;
    for (i = 0; i < 14; i++) {
        switch (i) {
        case 0:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->steps--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->steps++;
                }
                if (q->steps == 0) {
                    q->steps++;
                }
            }
            break;
        case 1:
            prevCount = q->pointCount;
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->pointCount = prevCount - 1;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->pointCount = prevCount + 1;
                }
                if (q->pointCount < 2) {
                    q->pointCount++;
                }
            }
            break;
        case 2:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[0] -= fine;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[0] += fine;
                }
            }
            break;
        case 3:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->scale -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->scale += step;
                }
            }
            break;
        case 4:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[2] -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[2] += step;
                }
            }
            break;
        case 5:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[3] -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[3] += step;
                }
            }
            break;
        case 6:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[4] -= step;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[4] += step;
                }
            }
            break;
        case 7:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_bss_6FB8.params[5] -= tiny;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_bss_6FB8.params[5] += tiny;
                }
            }
            break;
        case 8:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->unk1C -= speed;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->unk1C += speed;
                }
            }
            break;
        case 9:
            if (i == q->unk25 && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->drawFlat = !q->drawFlat;
            }
            break;
        case 10:
            if (i == q->unk25 && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->colorMode = !q->colorMode;
            }
            break;
        case 11:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_data_104D0.x -= lbl_1_rodata_7870;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_data_104D0.x += lbl_1_rodata_7870;
                }
            }
            break;
        case 12:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_data_104D0.y -= lbl_1_rodata_7870;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_data_104D0.y += lbl_1_rodata_7870;
                }
            }
            break;
        case 13:
            if (i == q->unk25) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    lbl_1_data_104D0.z -= lbl_1_rodata_7870;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    lbl_1_data_104D0.z += lbl_1_rodata_7870;
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (q->unk25 == 0) {
            q->unk25 = 14;
        }
        q->unk25--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        q->unk25++;
        if (q->unk25 == 14) {
            q->unk25 = 0;
        }
    }
    return prevCount != q->pointCount;
}
#endif

#include "Dolphin/mtxext.h"

extern const f32 lbl_1_rodata_7890;

// NONMATCHING 83%: frustum setup scheduled differently (orig negates farZ via a double temp, frsp) and the grid row pointers are strength-reduced into different saved regs
// .text:0x23098 size:0x76C
#if NONMATCHING
s32 fn_1_23098(Mtx44 proj, Mtx camera, s32 lines, s32 cols, f32 nearZ, f32 farZ) {
    Mtx44 m;
    Mtx inv;
    Vec rays[4];
    Vec origins[4];
    Vec dir;
    Vec eye;
    f32 t[4];
    f32 dist;
    f32 nearH;
    f32 farH;
    f32 nearW;
    f32 farW;
    f32 height;
    s32 rows;
    s32 k;
    s32 i;
    s32 c;

    eye.x = lbl_1_rodata_77D8;
    eye.y = lbl_1_rodata_77D8;
    eye.z = lbl_1_rodata_77D8;
    dir.x = lbl_1_rodata_77D8;
    dir.y = lbl_1_rodata_7820[0];
    dir.z = lbl_1_rodata_77D8;
    PSMTXMultVec(camera, &eye, &eye);
    PSMTXMultVec(camera, &dir, &dir);
    PSVECSubtract(&dir, &eye, &dir);
    PSVECNormalize(&dir, &dir);
    dist = PSVECDotProduct(&dir, &eye);

    nearH = lbl_1_rodata_77DC[0] * nearZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    farH = lbl_1_rodata_77DC[0] * farZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    nearW = lbl_1_rodata_77E0[0] * nearZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    farW = lbl_1_rodata_77E0[0] * farZ / lbl_1_rodata_7890 * lbl_1_rodata_7814[0];
    nearZ = -nearZ;
    farZ = -farZ;

    origins[0].x = nearW;
    origins[0].y = lbl_1_rodata_77D8;
    origins[0].z = nearZ;
    origins[1].x = farW;
    origins[1].y = lbl_1_rodata_77D8;
    origins[1].z = farZ;
    origins[2].x = farW;
    origins[2].y = farH;
    origins[2].z = farZ;
    origins[3].x = farW;
    origins[3].y = -farH;
    origins[3].z = farZ;
    rays[0].x = lbl_1_rodata_77D8;
    rays[0].y = nearH;
    rays[0].z = lbl_1_rodata_77D8;
    rays[1].x = lbl_1_rodata_77D8;
    rays[1].y = farH;
    rays[1].z = lbl_1_rodata_77D8;
    rays[2].x = nearW - farW;
    rays[2].y = nearH - farH;
    rays[2].z = nearZ - farZ;
    rays[3].x = nearW - farW;
    rays[3].y = -(nearH - farH);
    rays[3].z = nearZ - farZ;

    // Intersect each ray with the plane dot(dir, p) == dist.
    for (i = 0; i < 4; i++) {
        t[i] = PSVECDotProduct(&dir, &rays[i]);
        if (lbl_1_rodata_77D8 == t[i]) {
            rays[i].z = lbl_1_rodata_77D8;
        } else {
            t[i] = -(-dist + PSVECDotProduct(&dir, &origins[i])) / t[i];
            PSVECScale(&rays[i], t[i], &rays[i]);
            PSVECAdd(&origins[i], &rays[i], &rays[i]);
        }
        if (t[i] < lbl_1_rodata_77D8) {
            t[i] = -t[i];
        }
    }

    if (rays[2].z <= nearZ && rays[2].z >= farZ && rays[3].z <= nearZ && rays[3].z >= farZ) {
        memcpy(&rays[0], &rays[2], sizeof(Vec));
        memcpy(&rays[1], &rays[3], sizeof(Vec));
    } else if (t[0] <= lbl_1_rodata_77E4 && t[1] <= lbl_1_rodata_77E4) {
    } else if (t[0] <= lbl_1_rodata_77E4 || t[1] <= lbl_1_rodata_77E4) {
        if (rays[2].z <= nearZ && rays[2].z >= farZ) {
            memcpy(&rays[3], &rays[2], sizeof(Vec));
        }
        if (t[0] < lbl_1_rodata_77E4) {
            memcpy(&rays[1], &rays[3], sizeof(Vec));
        } else {
            memcpy(&rays[0], &rays[3], sizeof(Vec));
        }
    } else {
        return 0;
    }

    // Corner points of the visible ground quad, in camera space -> world (x, z).
    PSMTXInverse(camera, inv);
    PSMTXMultVec(inv, &rays[1], &rays[2]);
    lbl_1_bss_F6E0[cols - 1][0].x = rays[2].x;
    lbl_1_bss_F6E0[cols - 1][0].y = rays[2].z;
    rays[2].x = -rays[1].x;
    rays[2].y = rays[1].y;
    rays[2].z = rays[1].z;
    PSMTXMultVec(inv, &rays[2], &rays[2]);
    lbl_1_bss_F6E0[0][0].x = rays[2].x;
    lbl_1_bss_F6E0[0][0].y = rays[2].z;
    PSMTXMultVec(inv, &rays[0], &rays[2]);
    lbl_1_bss_F6E0[cols - 1][1].x = rays[2].x;
    lbl_1_bss_F6E0[cols - 1][1].y = rays[2].z;
    rays[2].x = -rays[0].x;
    rays[2].y = rays[0].y;
    rays[2].z = rays[0].z;
    PSMTXMultVec(inv, &rays[2], &rays[2]);
    lbl_1_bss_F6E0[0][1].x = rays[2].x;
    lbl_1_bss_F6E0[0][1].y = rays[2].z;

    PSMTX44Identity(m);
    memcpy(m, camera, sizeof(Mtx));
    PSMTX44Concat(proj, m, m);
    C_MTX44Inverse(m, m);
    PSMTX44MultVec(proj, &rays[0], &rays[0]);
    PSMTX44MultVec(proj, &rays[1], &rays[1]);
    height = rays[0].y - rays[1].y;
    if (height < lbl_1_rodata_77D8) {
        height = -height;
    }
    rows = (f32)lines * (height + lbl_1_rodata_780C / (f32)lines) * lbl_1_rodata_7814[0];
    if (rows < 2) {
        rows = 2;
    }

    // Left/right edges: interpolate in screen space and unproject.
    k = rows - 1;
    lbl_1_bss_F6E0[0][k].x = lbl_1_bss_F6E0[0][1].x;
    lbl_1_bss_F6E0[0][k].y = lbl_1_bss_F6E0[0][1].y;
    lbl_1_bss_F6E0[cols - 1][k].x = lbl_1_bss_F6E0[cols - 1][1].x;
    lbl_1_bss_F6E0[cols - 1][k].y = lbl_1_bss_F6E0[cols - 1][1].y;
    PSVECSubtract(&rays[0], &rays[1], &rays[2]);
    for (i = k; --i != 0;) {
        PSVECScale(&rays[2], (f32)i / (f32)k, &rays[3]);
        PSVECAdd(&rays[1], &rays[3], &rays[3]);
        PSMTX44MultVec(m, &rays[3], &eye);
        lbl_1_bss_F6E0[cols - 1][i].x = eye.x;
        lbl_1_bss_F6E0[cols - 1][i].y = eye.z;
        rays[3].x = -rays[3].x;
        PSMTX44MultVec(m, &rays[3], &eye);
        lbl_1_bss_F6E0[0][i].x = eye.x;
        lbl_1_bss_F6E0[0][i].y = eye.z;
    }

    // Fill each row between its left and right edge points.
    rays[0].y = lbl_1_rodata_77D8;
    rays[1].y = lbl_1_rodata_77D8;
    for (i = 0; i < rows; i++) {
        rays[0].x = lbl_1_bss_F6E0[0][i].x;
        rays[0].z = lbl_1_bss_F6E0[0][i].y;
        rays[1].x = lbl_1_bss_F6E0[cols - 1][i].x - rays[0].x;
        rays[1].z = lbl_1_bss_F6E0[cols - 1][i].y - rays[0].z;
        for (c = cols - 1; --c != 0;) {
            PSVECScale(&rays[1], (f32)c / (f32)(cols - 1), &rays[2]);
            PSVECAdd(&rays[0], &rays[2], &rays[2]);
            lbl_1_bss_F6E0[c][i].x = rays[2].x;
            lbl_1_bss_F6E0[c][i].y = rays[2].z;
        }
    }
    return rows;
}
#endif

extern const f32 lbl_1_rodata_789C;
extern const f32 lbl_1_rodata_78A0;
extern const f32 lbl_1_rodata_78A8;
extern void fn_1_121D4(u8* camera);

// NONMATCHING 90%: inherits fn_1_22F4C's indexing mismatch (inlined), and the height lookup uses lfs/add instead of lfsx
// .text:0x23B54 size:0x8BC
#if NONMATCHING
void fn_1_23B54(void) {
    ChallengeWaveState* q = (ChallengeWaveState*)lbl_803CC1B8[0];
    s32 i;
    s32 c;
    s32 r;
    s32 row;
    s32 ix;
    s32 even;
    u8 cur;
    f32 fx;
    f32 fz;
    f32 h;
    f32 maxH;
    f32 minH;
    Vec* p;

    for (i = 0; i < 8; i++) {
        switch (i) {
        case 0:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->lines == 2) {
                        q->lines = 112;
                    }
                    q->lines--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->lines == 112) {
                        q->lines = 2;
                    }
                    q->lines++;
                }
            }
            break;
        case 1:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->cols == 2) {
                        q->cols = 160;
                    }
                    q->cols--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->cols == 160) {
                        q->cols = 2;
                    }
                    q->cols++;
                }
            }
            break;
        case 2:
            if (i == q->cursor && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->freeze = !q->freeze;
            }
            break;
        case 3:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->farZ > lbl_1_rodata_77E4) {
                        q->farZ -= lbl_1_rodata_77E4;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->farZ < lbl_1_rodata_7868) {
                        q->farZ += lbl_1_rodata_77E4;
                    }
                }
            }
            break;
        case 4:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->nearZ > lbl_1_rodata_77E4) {
                        q->nearZ -= lbl_1_rodata_77E4;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->nearZ < lbl_1_rodata_7868) {
                        q->nearZ += lbl_1_rodata_77E4;
                    }
                }
            }
            break;
        case 5:
            if (i == q->cursor && (CHALLENGE_PAD_TRIGGER & 3)) {
                q->waveOn = !q->waveOn;
            }
            break;
        case 6:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->impulse > lbl_1_rodata_77D8) {
                        q->impulse -= lbl_1_rodata_786C;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->impulse < lbl_1_rodata_77E4) {
                        q->impulse += lbl_1_rodata_786C;
                    }
                }
            }
            break;
        case 7:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    if (q->unk20 > lbl_1_rodata_77D8) {
                        q->unk20 -= lbl_1_rodata_786C;
                    }
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->unk20 < lbl_1_rodata_77E4) {
                        q->unk20 += lbl_1_rodata_786C;
                    }
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (q->cursor == 0) {
            q->cursor = 8;
        }
        q->cursor--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        q->cursor++;
        if (q->cursor == 8) {
            q->cursor = 0;
        }
    } else if (lbl_803C77B8._02 & 0x200) {
        ((ChallengeWaveState*)lbl_803CC1B8[0])->func = fn_1_24778;
    } else if (CHALLENGE_PAD_TRIGGER & 0x100) {
        for (i = 0; i < 16; i++) {
            row = rand() % 32;
            lbl_1_bss_76E0[0][row * 128 + rand() % 128] += q->impulse;
        }
    }

    fn_1_121D4((u8*)&lbl_1_bss_43EE0);
    if (q->freeze == 0) {
        q->rows = fn_1_23098(lbl_1_bss_47010, lbl_1_bss_43EE0.view, q->lines, q->cols, q->nearZ, q->farZ);
        if (q->waveOn != 0) {
            cur = q->buffer++;
            fn_1_22F4C(32, 128, lbl_1_bss_76E0[1 - (cur & 1)], lbl_1_bss_76E0[cur & 1], lbl_1_bss_76E0[1 - (cur & 1)]);
            minH = lbl_1_rodata_78A0;
            maxH = lbl_1_rodata_789C;
            for (c = 0; c < q->cols; c++) {
                for (r = 0; r < q->rows; r++) {
                    p = &lbl_1_bss_F6E0[c][r];
                    // wrap the ground position into [0, 2)
                    fx = p->x;
                    fz = p->y;
                    ix = fx < lbl_1_rodata_77D8 ? (s32)-fx : (s32)fx;
                    even = ix / 2 * 2;
                    if (fx < lbl_1_rodata_77D8) {
                        fx = fx + (f32)(even + 2);
                    } else {
                        fx = fx - (f32)even;
                    }
                    ix = fz < lbl_1_rodata_77D8 ? (s32)-fz : (s32)fz;
                    even = ix / 2 * 2;
                    if (fz < lbl_1_rodata_77D8) {
                        fz = fz + (f32)(even + 2);
                    } else {
                        fz = fz - (f32)even;
                    }
                    p->z = lbl_1_bss_76E0[q->buffer & 1][(s32)(lbl_1_rodata_78A4 * fx) + ((s32)(lbl_1_rodata_78A8 * fz) << 7)];
                    h = p->z;
                    if (h < minH) {
                        minH = h;
                    } else if (h > maxH) {
                        maxH = h;
                    }
                }
            }
        } else {
            minH = lbl_1_rodata_77D8;
            maxH = minH;
            for (c = 0; c < q->cols; c++) {
                for (r = 0; r < q->rows; r++) {
                    lbl_1_bss_F6E0[c][r].z = minH;
                }
            }
        }
    }
    // minH/maxH are unused by fn_1_23804 (left unset when frozen, as in the original)
    fn_1_23804(10, 10, q->rows, q->cols, maxH, minH);
    q->frame++;
}
#endif

extern const f32 lbl_1_rodata_7850;

#if NONMATCHING
// Shared by fn_1_21CE8 / fn_1_21408: drive the rope's free end with the stick, then simulate it.
static inline void fn_1_21CE8_moveRope(ChallengeCurveDrawing* q) {
    ChallengeCurvePoint* tip;
    Vec force;
    f32 speed;
    f32 mass;

    if (q->colorMode != 0) {
        // move the free end of the rope directly
        if (((u8*)&lbl_803C77B8)[0x75] >= 0x50) {
            speed = lbl_1_rodata_77FC * q->unk1C;
        } else {
            speed = lbl_1_rodata_7850 * q->unk1C;
        }
        lbl_1_bss_6FE0[q->pointCount - 1].position.x += (s8)((u8*)&lbl_803C77B8)[0x70] * speed;
        lbl_1_bss_6FE0[q->pointCount - 1].position.y += (s8)((u8*)&lbl_803C77B8)[0x73] * speed;
        lbl_1_bss_6FE0[q->pointCount - 1].position.z += (s8)((u8*)&lbl_803C77B8)[0x71] * speed;
        tip = &lbl_1_bss_6FE0[q->pointCount - 1];
        memcpy(&tip->prevPos, &tip->position, sizeof(Vec));
        force.x = lbl_1_rodata_77D8;
        force.y = lbl_1_rodata_77D8;
        force.z = lbl_1_rodata_77D8;
    } else {
        // or pull it with a force
        mass = lbl_1_bss_6FE0[q->pointCount - 1].mass;
        speed = q->unk1C;
        force.x = speed * ((s8)((u8*)&lbl_803C77B8)[0x70] * mass);
        force.y = speed * ((s8)((u8*)&lbl_803C77B8)[0x73] * mass);
        force.z = speed * ((s8)((u8*)&lbl_803C77B8)[0x71] * mass);
    }
    fn_80038B48(&lbl_1_bss_6FB8, lbl_1_bss_6FE0, q->pointCount, &force);
}

static inline void fn_1_21CE8_setupDraw(void) {
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
    GXLoadPosMtxImm(lbl_1_bss_43EE0.view, 0);
    GXSetCurrentMtx(0);
}
#endif

// NONMATCHING 63% (98% when fn_1_20950 is force-inlined, which then drops fn_1_20950's own copy): the original inlines fn_1_20950 here; ours calls it
// .text:0x21CE8 size:0x8D0
#if NONMATCHING
void fn_1_21CE8(void) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8[0];

    if (fn_1_22874() != 0 || (lbl_803C77B8._02 & 0x100)) {
        fn_1_21180(q);
    } else if (lbl_803C77B8._02 & 0x200) {
        *(void (**)(void))lbl_803CC1B8[0] = fn_1_21408;
    }
    fn_1_21CE8_moveRope(q);
    fn_1_21CE8_setupDraw();
    fn_1_21040();
    fn_1_21298(q);
    fn_1_20950(lbl_1_bss_6FE0, q->pointCount - 1, lbl_1_bss_43EE0.view);
}
#endif

// NONMATCHING 63%: same shape as fn_1_21CE8 (the original inlines fn_1_20950 here; ours calls it)
// .text:0x21408 size:0x8E0
#if NONMATCHING
void fn_1_21408(void) {
    ChallengeCurveDrawing* q = (ChallengeCurveDrawing*)lbl_803CC1B8[0];

    if (lbl_803C77B8._02 & 0x1000) {
        *(void (**)(void))q = fn_1_21CE8;
    } else if (lbl_803C77B8._02 & 0x100) {
        fn_1_21180(q);
    } else if (lbl_803C77B8._02 & 0x200) {
        lbl_1_bss_6BE0[0] = NULL;
        *(void (**)(void))q = fn_1_24778;
    }
    fn_1_121D4((u8*)&lbl_1_bss_43EE0);
    fn_1_21CE8_moveRope(q);
    fn_1_21CE8_setupDraw();
    fn_1_21040();
    fn_1_21298(q);
    if (lbl_1_bss_6BE0[0] != NULL) {
        fn_1_20950(lbl_1_bss_6FE0, q->pointCount - 1, lbl_1_bss_43EE0.view);
    }
}
#endif

extern void fn_80035A00(void);
extern void fn_1_26928(void);
extern const ChallengeMtxBox lbl_1_rodata_7780;
extern const f32 lbl_1_rodata_78E4;
extern const f32 lbl_1_rodata_78E8;
extern const f32 lbl_1_rodata_78EC;

#define CHALLENGE_TEX_SLOTS ((ChallengeTexSlot*)lbl_803C4BE0) // TODO type: lbl_803C4BE0 is SpaniTexSlot[] in main
#define CHALLENGE_SPRITE_OBJ(q) (lbl_80371C30[(q)->sprite->slot].obj)

// NONMATCHING 99%: scheduling only, in the case-3 write-back and the SetDisplayStateTexture argument setup
// .text:0x25F98 size:0x824
#if NONMATCHING
void fn_1_25F98(void) {
    ChallengeSpriteViewer* q = (ChallengeSpriteViewer*)lbl_803CC1B8[0];
    AnimFrame frame;
    ChallengeMtxBox mtx;
    ChallengeTexSlot* bank;
    s32 i;

    for (i = 0; i < 6; i++) {
        switch (i) {
        case 0:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    fn_80034CEC(q->sprite);
                    q->track++;
                    if (q->track == q->trackCount) {
                        q->track = 0;
                    }
                    q->frame = 0;
                    lbl_1_data_10344.track = q->track;
                    fn_80034E20(q->sprite, &lbl_1_data_10344);
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    fn_80034CEC(q->sprite);
                    if (q->track == 0) {
                        q->track = q->trackCount;
                    }
                    q->track--;
                    q->frame = 0;
                    lbl_1_data_10344.track = q->track;
                    fn_80034E20(q->sprite, &lbl_1_data_10344);
                } else if (lbl_803C77B8._02 & 0x100) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 1;
                } else if (lbl_803C77B8._02 & 0x200) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 0;
                } else if (lbl_803C77B8._02 & 0x400) {
                    CHALLENGE_SPRITE_OBJ(q)->_5C = 0;
                }
            }
            break;
        case 1:
            if (i == q->cursor) {
                if (lbl_803C77B8._02 & 0x100) {
                    q->hold = !q->hold;
                }
                if (q->hold != 0) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 0;
                } else {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 1;
                }
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    if (q->hold != 0) {
                        CHALLENGE_SPRITE_OBJ(q)->_68 = 1;
                    }
                } else if ((CHALLENGE_PAD_TRIGGER & 1) && q->hold != 0) {
                    CHALLENGE_SPRITE_OBJ(q)->_68 = 4;
                }
            }
            break;
        case 2:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->frame++;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->frame--;
                }
            }
            fn_8000CEF0(CHALLENGE_TEX_SLOTS[CHALLENGE_SPRITE_OBJ(q)->_66].anim, q->track, 0, q->frame, (u32*)&frame);
            break;
        case 3:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 2) {
                    frame.subTrack++;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    frame.subTrack--;
                }
                // write the edited texture index back into the track's first entry
                CHALLENGE_TEX_SLOTS[CHALLENGE_SPRITE_OBJ(q)->_66].anim->table->tracks[q->track]->blocks[0]->entries[0].size
                    = frame.subTrack;
            }
            break;
        case 4:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 0x800) {
                    q->x = 0;
                } else if (CHALLENGE_PAD_TRIGGER & 0x400) {
                    q->x = 320;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->x += 8;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->x -= 8;
                }
                lbl_1_data_10344.x = q->x;
                CHALLENGE_SPRITE_OBJ(q)->x = q->x;
            }
            break;
        case 5:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 0x800) {
                    q->y = 0;
                } else if (CHALLENGE_PAD_TRIGGER & 0x400) {
                    q->y = 224;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->y += 8;
                } else if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->y -= 8;
                }
                lbl_1_data_10344.y = q->y;
                CHALLENGE_SPRITE_OBJ(q)->y = q->y;
            }
            break;
        }
    }
    if (lbl_803C77B8._02 & 4) {
        q->cursor++;
        if (q->cursor == 6) {
            q->cursor = 0;
        }
    } else if (lbl_803C77B8._02 & 8) {
        if (q->cursor == 0) {
            q->cursor = 6;
        }
        q->cursor--;
    }
    if (lbl_803C77B8._02 & 0x1000) {
        fn_80034CEC(q->sprite);
        q->sprite->done = 1;
        *(void (**)(void))lbl_803CC1B8[0] = fn_1_26928;
        fn_80035A00();
    }

    // draw the selected texture of the bank as a quad
    mtx = lbl_1_rodata_7780;
    if (lbl_1_bss_6BD8 != 0) {
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXLoadPosMtxImm(mtx.m, 0);
        GXSetCurrentMtx(0);
        bank = &CHALLENGE_TEX_SLOTS[CHALLENGE_SPRITE_OBJ(q)->_66];
        SetDisplayStateTexture((struct TexImage*)(bank->tex + lbl_1_bss_6BDC * 32 + 4), 0, 0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E4;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 0;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_77E8;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78EC;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 0;
        GXWGFifo.u16 = 1;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7814[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78EC;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 1;
        GXWGFifo.u16 = 1;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_7814[0];
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E4;
        GXWGFifo.f32 = *(volatile f32*)&lbl_1_rodata_78E8;
        GXWGFifo.u16 = 1;
        GXWGFifo.u16 = 0;
    }
}
#endif

// NONMATCHING 86%: the original inlines fn_1_248BC (and fn_1_24A8C/fn_1_247A0) here; ours calls fn_1_248BC
// .text:0x25064 size:0xC04
#if NONMATCHING
void fn_1_25064(void) {
    ChallengePathTest* q = (ChallengePathTest*)lbl_803CC1B8[0];
    s32 big;
    s32 small;
    s32 i;

    if (lbl_803C77B8._00 & 0x20) {
        big = 4;
        small = 1;
    } else {
        big = 64;
        small = 10;
    }
    for (i = 0; i < 11; i++) {
        switch (i) {
        case 0:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->count--;
                    fn_1_24A8C();
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->count++;
                    fn_1_24A8C();
                }
            }
            break;
        case 1:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->steps--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->steps++;
                }
                if (q->steps == 0) {
                    q->steps = 1;
                }
            }
            break;
        case 2:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param2 -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param2 += big;
                }
            }
            break;
        case 3:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param3 -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param3 += big;
                }
            }
            break;
        case 4:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param0 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param0 += small;
                }
            }
            break;
        case 5:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->mass -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->mass += big;
                }
            }
            break;
        case 6:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->force--;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->force++;
                }
            }
            break;
        case 7:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param5 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param5 += small;
                }
            }
            break;
        case 8:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->unk26 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->unk26 += small;
                }
            }
            break;
        case 9:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->param4 -= big;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->param4 += big;
                }
            }
            break;
        case 10:
            if (i == q->cursor) {
                if (CHALLENGE_PAD_TRIGGER & 1) {
                    q->unk28 -= small;
                } else if (CHALLENGE_PAD_TRIGGER & 2) {
                    q->unk28 += small;
                }
            }
            break;
        }
    }
    if (CHALLENGE_PAD_TRIGGER & 8) {
        if (q->cursor == 0) {
            q->cursor = 11;
        }
        q->cursor--;
    } else if (CHALLENGE_PAD_TRIGGER & 4) {
        q->cursor++;
        if (q->cursor == 11) {
            q->cursor = 0;
        }
    } else if (lbl_803C77B8._02 & 0x100) {
        fn_1_24A8C();
    } else if (lbl_803C77B8._02 & 0x200) {
        GXColor clearColor;
        ChallengeTransfer* transfer;

        *(u32*)&clearColor = 0x11775500;
        GXSetCopyClear(clearColor, 0xFFFFFF);
        transfer = ((ChallengePathTest*)lbl_803CC1B8[0])->transfer;
        transfer->complete = 1;
        fn_800B0A14_removeQueue(transfer);
    }
    fn_1_247A0();
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
    GXLoadPosMtxImm(lbl_1_bss_43F38, 0);
    GXSetCurrentMtx(0);
    fn_1_AF4(11, 11, lbl_1_rodata_7848);
    fn_1_248BC(q->count);
}
#endif
