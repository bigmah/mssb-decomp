#ifndef __MAIN_FILE_800B9974_H__
#define __MAIN_FILE_800B9974_H__

#include "mssbTypes.h"
#include "C3/control.h"
#include "C3/light.h"

void fn_800B9AA8(u32 value);

void fn_800B9A9C(u32 flag, f32 value);

struct DODisplayObj;

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

#endif
