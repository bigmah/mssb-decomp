#include "main/file_800B9974.h"
#include "C3/geoPalette.h"
#include "Dolphin/os.h"
#include "string.h"

#pragma dont_inline on

typedef struct FogState {
    /* 0x00 */ GXFogType type;
    /* 0x04 */ f32 startz;
    /* 0x08 */ f32 endz;
    /* 0x0C */ f32 nearz;
    /* 0x10 */ f32 farz;
    /* 0x14 */ GXColor color;
} FogState;

extern FogState lbl_80111700; // current fog settings
extern MtxPtr lbl_803CC204;   // skin matrix array for the current DOVARenderSkin call
extern MtxPtr lbl_803CC208;   // skin inverse-transpose matrix array

extern char lbl_800E7F8C[]; // "Display object id %d is greater than number of objects %d"

extern void* _OSAllocFromHeap(s32 align, s32 size);
extern void fn_800ACFB0(void* ptr); // heap free
extern void SKNLoadFile(void* sknHeader, void* skinPositions);

// Geometry palette files store pointers as offsets from a base; turn one into a pointer (32-bit file format).
#define GEO_RELOC(a, b) ((void*)((u32)(a) + (u32)(b)))

// .text:0x800B9974 size:0x50
void SetFogNone(void) {
    GXColor color;

    color.b = 0;
    color.g = 0;
    color.r = 0;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, color);
}

// NONMATCHING 75%: original keeps the f64 args in f5-f7 and rounds them twice (frsp for GXSetFog, stfs for the
// stores); ours rounds once and stores the rounded copies
#if NONMATCHING
// .text:0x800B99C4 size:0x6C
void SetFog(GXFogType type, GXColor* color, f64 startz, f64 endz, f64 nearz, f64 farz) {
    GXColor c = *color;

    lbl_80111700.type = type;
    lbl_80111700.startz = startz;
    lbl_80111700.endz = endz;
    lbl_80111700.nearz = nearz;
    lbl_80111700.farz = farz;
    lbl_80111700.color = c;
    GXSetFog(type, startz, endz, nearz, farz, c);
}
#endif

// .text:0x800B9A30 size:0x6C
void SetFogNoneAgain(void) {
    lbl_80111700.color.b = 0;
    lbl_80111700.color.g = 0;
    lbl_80111700.color.r = 0;
    lbl_80111700.type = GX_FOG_NONE;
    lbl_80111700.startz = 0.0f;
    lbl_80111700.endz = 0.0f;
    lbl_80111700.nearz = 0.0f;
    lbl_80111700.farz = 0.0f;
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, lbl_80111700.color);
}

extern f32 lbl_803CC218;

extern u32 lbl_803CC21C;

extern u32 lbl_803CC1F0;

// fn_800B9AA8, size:0x8
void fn_800B9AA8(u32 value) {
    lbl_803CC1F0 = value;
}

// fn_800B9A9C, size:0xC
void fn_800B9A9C(u32 flag, f32 value) {
    lbl_803CC21C = flag;
    lbl_803CC218 = value;
}

// .text:0x800B9AB0 size:0x3F8
void fn_800B9AB0(void) {
    return;
}

// .text:0x800B9EA8 size:0x5A4
void fn_800B9EA8(void) {
    return;
}

// .text:0x800BA44C size:0x3FC
void fn_800BA44C(s32 type, struct DODisplayObj* dispObj, void* data, u8* tevStage, u8* texCoord) {
    return;
}

// .text:0x800BA848 size:0x12E4
void Custom_SetState(void) {
    return;
}

// .text:0x800BBB2C size:0x430
void SetState(void) {
    return;
}

// .text:0x800BBF5C size:0x168
void GetColorFromQuant(u8* color, u8 quantizeInfo, u8* r, u8* g, u8* b, u8* a) {
    switch ((quantizeInfo >> 4) & 0xF) {
    case GX_RGB565:
        *r = (*(u16*)color >> 8) & 0xF8;
        *g = (*(u16*)color >> 3) & 0xFC;
        *b = (*(u16*)color & 0x1F) << 3;
        *a = 0xFF;
        break;
    case GX_RGBA4:
        *r = (*(u16*)color >> 12) & 0xF;
        *g = (*(u16*)color >> 8) & 0xF;
        *b = (*(u16*)color >> 4) & 0xF;
        *a = *(u16*)color & 0xF;
        *r = *r | (*r << 4);
        *g = *g | (*g << 4);
        *b = *b | (*b << 4);
        *a = *a | (*a << 4);
        break;
    case GX_RGBA8:
        *r = *(u32*)color >> 24;
        *g = (*(u32*)color >> 16) & 0xFF;
        *b = (*(u32*)color >> 8) & 0xFF;
        *a = *(u32*)color & 0xFF;
        break;
    case GX_RGB8:
    case GX_RGBX8:
        *r = *(u32*)color >> 24;
        *g = (*(u32*)color >> 16) & 0xFF;
        *b = (*(u32*)color >> 8) & 0xFF;
        *a = 0xFF;
        break;
    case GX_RGBA6:
        // Reads only 16 bits, so the red channel always comes out 0 (original bug kept).
        *r = (*(u16*)color & 0xFC0000) >> 16;
        *g = (*(u16*)color >> 10) & 0xFC;
        *b = (*(u16*)color >> 4) & 0xFC;
        *a = (*(u16*)color & 0x3F) << 2;
        break;
    }
}

// .text:0x800BC0C4 size:0x724
void DOVARender(struct DODisplayObj* dispObj, MtxPtr camera, u8 numLights, va_list* list) {
    return;
}

// .text:0x800BC7E8 size:0x3C
void DOVARenderSkin(struct DODisplayObj* dispObj, MtxPtr camera, MtxPtr mtxArray, MtxPtr invTransposeMtxArray, u8 numLights, va_list* list) {
    lbl_803CC204 = mtxArray;
    lbl_803CC208 = invTransposeMtxArray;
    DOVARender(dispObj, camera, numLights, list);
    lbl_803CC204 = NULL;
    lbl_803CC208 = NULL;
}

// fn_800BC824, size:0x10
void fn_800BC824(struct DODisplayObj* dispObj, void* shaderData) {
    if (dispObj != NULL) {
        dispObj->shaderData = shaderData;
    }
}

// .text:0x800BC834 size:0x2C
void DOSetWorldMatrix(struct DODisplayObj* dispObj, MtxPtr m) {
    PSMTXCopy(m, dispObj->worldMatrix);
}

// .text:0x800BC860 size:0x258
void InitDisplayObjWithLayout(struct DODisplayObj* dispObj, DODisplayLayout* layout) {
    u16 i;

    if (layout->positionData != NULL) {
        dispObj->positionData = _OSAllocFromHeap(0x20, sizeof(PositionData));
        *dispObj->positionData = *layout->positionData;
    } else {
        dispObj->positionData = NULL;
    }
    if (layout->colorData != NULL) {
        dispObj->colorData = _OSAllocFromHeap(0x20, sizeof(ColorData));
        *dispObj->colorData = *layout->colorData;
    } else {
        dispObj->colorData = NULL;
    }
    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * sizeof(TextureData));
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = layout->textureData[i];
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }
    if (layout->lightingData != NULL) {
        dispObj->lightingData = _OSAllocFromHeap(0x20, sizeof(LightingData));
        *dispObj->lightingData = *layout->lightingData;
    } else {
        dispObj->lightingData = NULL;
    }
    if (layout->displayData != NULL) {
        dispObj->displayData = _OSAllocFromHeap(0x20, sizeof(DisplayData));
        *dispObj->displayData = *layout->displayData;
    } else {
        dispObj->displayData = NULL;
    }
    dispObj->visibility = 1;
    PSMTXIdentity(dispObj->worldMatrix);
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    dispObj->unk15 = layout->unk15;
    memcpy(dispObj->unk54[1], layout->unk1C[1], 4);
    memcpy(dispObj->unk54[0], layout->unk1C[0], 4);
    memcpy(dispObj->unk54[3], layout->unk1C[3], 4);
    memcpy(dispObj->unk54[2], layout->unk1C[2], 4);
    memcpy(dispObj->unk54[5], layout->unk1C[5], 4);
    memcpy(dispObj->unk54[4], layout->unk1C[4], 4);
}

// .text:0x800BCAB8 size:0x8C
void DOGet(struct DODisplayObj** dispObj, DODisplayDataPtr pal, u16 id, char* name) {
    DODisplayLayout* layout;

    if (id >= pal->numDescriptors) {
        OSReport(lbl_800E7F8C, id, pal->numDescriptors);
        *dispObj = NULL;
        return;
    }
    layout = pal->descriptorArray[id].layout;
    *dispObj = _OSAllocFromHeap(0x20, sizeof(struct DODisplayObj));
    InitDisplayObjWithLayout(*dispObj, layout);
}

// .text:0x800BCB44 size:0x21C
void* LoadGeoPalette(DODisplayDataPtr pal) {
    u16 j;
    void* skinPositions;
    DODisplayLayout* layout;
    u16 i;

    skinPositions = NULL;
    if (pal->userDataSize != 0 && pal->userData != NULL) {
        pal->userData = GEO_RELOC(pal->userData, pal);
    }
    pal->descriptorArray = GEO_RELOC(pal->descriptorArray, pal);
    for (i = 0; i < pal->numDescriptors; i++) {
        pal->descriptorArray[i].layout = GEO_RELOC(pal, pal->descriptorArray[i].layout);
        pal->descriptorArray[i].name = GEO_RELOC(pal, pal->descriptorArray[i].name);
        layout = pal->descriptorArray[i].layout;
        if (layout->positionData != NULL) {
            layout->positionData = GEO_RELOC(layout->positionData, layout);
            if (layout->positionData->positionArray != NULL) {
                layout->positionData->positionArray = GEO_RELOC(layout->positionData->positionArray, layout);
            }
            if (layout->positionData->compCount == 6) {
                skinPositions = layout->positionData->positionArray;
            }
        }
        if (layout->colorData != NULL) {
            layout->colorData = GEO_RELOC(layout->colorData, layout);
            if (layout->colorData->colorArray != NULL) {
                layout->colorData->colorArray = GEO_RELOC(layout->colorData->colorArray, layout);
            }
        }
        if (layout->textureData != NULL) {
            layout->textureData = GEO_RELOC(layout->textureData, layout);
            for (j = 0; j < layout->numTextureChannels; j++) {
                if (layout->textureData[j].textureCoordArray != NULL) {
                    layout->textureData[j].textureCoordArray = GEO_RELOC(layout, layout->textureData[j].textureCoordArray);
                }
                if (layout->textureData[j].texturePaletteName != NULL) {
                    layout->textureData[j].texturePaletteName = GEO_RELOC(layout, layout->textureData[j].texturePaletteName);
                }
            }
        }
        if (layout->lightingData != NULL) {
            layout->lightingData = GEO_RELOC(layout->lightingData, layout);
            if (layout->lightingData->normalArray != NULL) {
                layout->lightingData->normalArray = GEO_RELOC(layout->lightingData->normalArray, layout);
            }
        }
        if (layout->displayData != NULL) {
            layout->displayData = GEO_RELOC(layout->displayData, layout);
            if (layout->displayData->primitiveBank != NULL) {
                layout->displayData->primitiveBank = GEO_RELOC(layout->displayData->primitiveBank, layout);
            }
            if (layout->displayData->displayStateList != NULL) {
                layout->displayData->displayStateList = GEO_RELOC(layout->displayData->displayStateList, layout);
            }
            for (j = 0; j < layout->displayData->numStateEntries; j++) {
                if (layout->displayData->displayStateList[j].primitiveList != NULL) {
                    layout->displayData->displayStateList[j].primitiveList =
                        GEO_RELOC(layout, layout->displayData->displayStateList[j].primitiveList);
                }
            }
        }
        if (layout->unk18 != NULL) {
            layout->unk18 = GEO_RELOC(layout->unk18, layout);
        }
    }
    return skinPositions;
}

// .text:0x800BCD60 size:0x5C
void convertGeometryAndSknHeader(DODisplayDataPtr pal, void* sknHeader) {
    void* skinPositions = LoadGeoPalette(pal);

    if (sknHeader != NULL) {
        SKNLoadFile(sknHeader, skinPositions);
    }
    pal->skinPositions = skinPositions;
}

// .text:0x800BCDBC size:0x7C
void fn_800BCDBC(DODisplayDataPtr pal) {
    s32 i;

    for (i = pal->numDescriptors - 1; i >= 0; i--) {
        if (pal->descriptorArray[i].dispObj->textureData != NULL) {
            fn_800ACFB0(pal->descriptorArray[i].dispObj->textureData);
        }
    }
    fn_800ACFB0(pal->descriptorArray[0].dispObj);
}

// .text:0x800BCE38 size:0xC0
void fn_800BCE38(DODisplayDataPtr pal) {
    struct DODisplayObj* dispObjs;
    u32 i;

    pal->userData = GEO_RELOC(pal, pal->userData);
    pal->descriptorArray = GEO_RELOC(pal, pal->descriptorArray);
    dispObjs = _OSAllocFromHeap(0x20, pal->numDescriptors * sizeof(struct DODisplayObj));
    for (i = 0; i < pal->numDescriptors; i++) {
        fn_800BCEF8(GEO_RELOC(pal, pal->descriptorArray[i].layout), &dispObjs[i]);
        pal->descriptorArray[i].dispObj = &dispObjs[i];
        pal->descriptorArray[i].name = GEO_RELOC(pal, pal->descriptorArray[i].name);
    }
}

// .text:0x800BCEF8 size:0x298
void* fn_800BCEF8(DODisplayLayout* layout, struct DODisplayObj* dispObj) {
    void* skinPositions;
    s32 i;

    skinPositions = NULL;
    if (layout->positionData != NULL) {
        dispObj->positionData = GEO_RELOC(layout, layout->positionData);
        dispObj->positionData->positionArray = GEO_RELOC(layout, dispObj->positionData->positionArray);
        if (dispObj->positionData->compCount == 6) {
            skinPositions = dispObj->positionData->positionArray;
        }
    } else {
        dispObj->positionData = NULL;
    }
    if (layout->colorData != NULL) {
        dispObj->colorData = GEO_RELOC(layout, layout->colorData);
        dispObj->colorData->colorArray = GEO_RELOC(layout, dispObj->colorData->colorArray);
    } else {
        dispObj->colorData = NULL;
    }
    if (layout->textureData != NULL && layout->numTextureChannels != 0) {
        dispObj->textureData = _OSAllocFromHeap(0x20, layout->numTextureChannels * sizeof(TextureData));
        dispObj->numTextureChannels = layout->numTextureChannels;
        for (i = 0; i < layout->numTextureChannels; i++) {
            dispObj->textureData[i] = *(TextureData*)GEO_RELOC(&layout->textureData[i], layout);
            dispObj->textureData[i].textureCoordArray = GEO_RELOC(layout, dispObj->textureData[i].textureCoordArray);
        }
    } else {
        dispObj->textureData = NULL;
        dispObj->numTextureChannels = 0;
    }
    if (layout->lightingData != NULL) {
        dispObj->lightingData = GEO_RELOC(layout, layout->lightingData);
        dispObj->lightingData->normalArray = GEO_RELOC(layout, dispObj->lightingData->normalArray);
    } else {
        dispObj->lightingData = NULL;
    }
    if (layout->displayData != NULL) {
        dispObj->displayData = GEO_RELOC(layout, layout->displayData);
        dispObj->displayData->primitiveBank = GEO_RELOC(layout, dispObj->displayData->primitiveBank);
        dispObj->displayData->displayStateList = GEO_RELOC(layout, dispObj->displayData->displayStateList);
        for (i = 0; i < dispObj->displayData->numStateEntries; i++) {
            if (dispObj->displayData->displayStateList[i].primitiveList != NULL) {
                dispObj->displayData->displayStateList[i].primitiveList =
                    GEO_RELOC(layout, dispObj->displayData->displayStateList[i].primitiveList);
            }
        }
    } else {
        dispObj->displayData = NULL;
    }
    dispObj->unk15 = layout->unk15;
    dispObj->visibility = 1;
    dispObj->unk17 = 0;
    dispObj->tevCallback = fn_800BA44C;
    dispObj->shaderFunc = NULL;
    dispObj->shaderData = NULL;
    memcpy(dispObj->unk54[1], layout->unk1C[1], 4);
    memcpy(dispObj->unk54[0], layout->unk1C[0], 4);
    memcpy(dispObj->unk54[3], layout->unk1C[3], 4);
    memcpy(dispObj->unk54[2], layout->unk1C[2], 4);
    memcpy(dispObj->unk54[5], layout->unk1C[5], 4);
    memcpy(dispObj->unk54[4], layout->unk1C[4], 4);
    return skinPositions;
}

extern u32 lbl_803CC20C;

// fn_800BD190, size:0x58
void fn_800BD190(GQRValueGroups* groups, s32 value) {
    u32 i;
    s32 j;
    for (i = 0; i < groups->count; i++) {
        for (j = 0; j < groups->groups[i].group->count; j++) {
            groups->groups[i].group->entries[j].value = value;
        }
    }
}

// __MTGQR5, size:0x8
void __MTGQR5(register u32 value) {
    asm {
        mtspr GQR5, value
    }
}

// fn_800BD1E8, size:0x8
void fn_800BD1E8(u32 value) {
    lbl_803CC20C = value;
}

// __MTGQR6, size:0x8
void __MTGQR6(register u32 value) {
    asm {
        mtspr GQR6, value
    }
}

// __MTGQR7, size:0x8
void __MTGQR7(register u32 value) {
    asm {
        mtspr GQR7, value
    }
}

// .text:0x800BD208 size:0x38
void GQRSetup7(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR7((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

// .text:0x800BD240 size:0x38
void GQRSetup6(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR6((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

// .text:0x800BD278 size:0x38
void GQRSetup5(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType) {
    __MTGQR5((((loadScale << 8) + loadType) << 16) | ((storeScale << 8) + storeType));
}

extern u32 lbl_803CC224;

extern u8 lbl_803CC220;

// fn_800BD2B0, size:0x1C
u8 fn_800BD2B0(u32* value) {
    if (lbl_803CC220 != 0) {
        *value = lbl_803CC224;
    }
    return lbl_803CC220;
}

// fn_800BD2CC, size:0x10
void fn_800BD2CC(u8 flag, u32* value) {
    u32 input = *value;
    lbl_803CC220 = flag;
    lbl_803CC224 = input;
}

// fn_800BD2DC, size:0x24
void fn_800BD2DC(void) {
    lbl_803CC220 = 0;
    ((u8*)&lbl_803CC224)[0] = 0;
    ((u8*)&lbl_803CC224)[2] = 0;
    ((u8*)&lbl_803CC224)[1] = 0;
    ((u8*)&lbl_803CC224)[3] = 0xFF;
}

// .text:0x800BD300 size:0xA0
void LITXForm(Light* light, MtxPtr view) {
    Mtx m;

    CTRLBuildMatrix(&light->control, m);
    if (light->parent != NULL) {
        PSMTXConcat(light->parent, m, m);
    }
    PSMTXConcat(view, m, m);
    PSMTXMultVec(m, &light->position, &light->worldPosition);
    PSMTXInverse(m, m);
    PSMTXTranspose(m, m);
    PSMTXMultVec(m, &light->direction, &light->worldDirection);
}

// .text:0x800BD3A0 size:0xC
void LITInitColor(Light* light, GXColor* color) {
    light->color = *color;
}

// .text:0x800BD3AC size:0x10
void LITInitDir(Light* light, f32 x, f32 y, f32 z) {
    light->direction.x = x;
    light->direction.y = y;
    light->direction.z = z;
}

// .text:0x800BD3BC size:0x10
void LITInitPos(Light* light, f32 x, f32 y, f32 z) {
    light->position.x = x;
    light->position.y = y;
    light->position.z = z;
}

// .text:0x800BD3CC size:0x20
void LITInitAttn(Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2) {
    GXInitLightAttn(&light->lt_obj, a0, a1, a2, k0, k1, k2);
}
