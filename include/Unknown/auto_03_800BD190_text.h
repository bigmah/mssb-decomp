#ifndef __UNKNOWN_AUTO_03_800BD190_TEXT_H__
#define __UNKNOWN_AUTO_03_800BD190_TEXT_H__

#include "mssbTypes.h"

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

#endif
