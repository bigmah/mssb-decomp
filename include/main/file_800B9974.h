#ifndef __MAIN_FILE_800B9974_H__
#define __MAIN_FILE_800B9974_H__

#include "mssbTypes.h"
#include "C3/control.h"
#include "C3/light.h"
#include "C3/geoPalette.h"

void SetFogNone(void);

void SetFog(GXFogType type, GXColor* color, f64 startz, f64 endz, f64 nearz, f64 farz);

void SetFogNoneAgain(void);

void fn_800B9AA8(u32 value);

void fn_800B9A9C(u32 flag, f32 value);

void fn_800BC824(struct DODisplayObj* dispObj, void* shaderData);

typedef struct GQRValueEntry {
    u8 pad[0xC];
    s32 value;
} GQRValueEntry;

typedef struct GQRValueGroup {
    u8 pad[8];
    GQRValueEntry* entries;
    u8 padC[8];
    u8 count;
} GQRValueGroup;

typedef struct GQRGroupSlot {
    GQRValueGroup* group;
    u32 pad;
} GQRGroupSlot;

typedef struct GQRValueGroups {
    u8 pad[0xC];
    u32 count;
    GQRGroupSlot* groups;
} GQRValueGroups;

void fn_800BD190(GQRValueGroups* groups, s32 value);

void __MTGQR5(u32 value);

void fn_800BD1E8(u32 value);

void __MTGQR6(u32 value);

void __MTGQR7(u32 value);

u8 fn_800BD2B0(u32* value);

void fn_800BD2CC(u8 flag, u32* value);

void fn_800BD2DC(void);

void LITXForm(Light* light, MtxPtr view);

void LITInitColor(Light* light, GXColor* color);

void LITInitDir(Light* light, f32 x, f32 y, f32 z);

void LITInitPos(Light* light, f32 x, f32 y, f32 z);

void LITInitAttn(Light* light, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1, f32 k2);

void GetColorFromQuant(u8* color, u8 quantizeInfo, u8* r, u8* g, u8* b, u8* a);

void fn_800BA44C(s32 type, struct DODisplayObj* dispObj, void* data, u8* tevStage, u8* texCoord);

void InitDisplayObjWithLayout(struct DODisplayObj* dispObj, DODisplayLayout* layout);

void* LoadGeoPalette(DODisplayDataPtr pal);

void convertGeometryAndSknHeader(DODisplayDataPtr pal, void* sknHeader);

void fn_800BCDBC(DODisplayDataPtr pal);

void fn_800BCE38(DODisplayDataPtr pal);

void* fn_800BCEF8(DODisplayLayout* layout, struct DODisplayObj* dispObj);

void GQRSetup7(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType);

void GQRSetup6(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType);

void GQRSetup5(u32 loadScale, u32 loadType, u32 storeScale, u32 storeType);

#endif
