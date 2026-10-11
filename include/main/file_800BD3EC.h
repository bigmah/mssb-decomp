#ifndef __MAIN_FILE_800BD3EC_H__
#define __MAIN_FILE_800BD3EC_H__

#include "mssbTypes.h"
#include "C3/charPipeline.h"
#include "main/file_80063028.h" // GameActor

typedef struct DOListEntry DOListEntry;
typedef void (*DOListEntryCallback)(DOListEntry* entry);

// One actor plus the variadic args passed to its render call (fn_800B3A78).
struct DOListEntry {
    /* 0x00 */ GameActor* actor;
    /* 0x04 */ u8 pad04[4];
    /* 0x08 */ DOListEntryCallback callback;
    /* 0x0C */ u8 pad0C[0x6C - 0x0C];
    /* 0x6C */ u8 visible;
    /* 0x6D */ u8 numArgs;
    /* 0x6E */ u8 pad6E[2];
    /* 0x70 */ u32 args[8];
}; // size 0x90

typedef struct DOList {
    /* 0x00 */ u16 count;
    /* 0x02 */ u8 pad02[0x32];
    /* 0x34 */ DOListEntry entries[1];
} DOList;

void LITAlloc(Light** light);
void fn_800BD478(GameActor** actor, ActorLayoutFile* layout);
void fn_800BD548(DOListEntry* entry, u8 numArgs, ...);
void fn_800BD670(DOList* list, MtxPtr camera);

#endif
