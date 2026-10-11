#ifndef __MAIN_FILE_80021308_H__
#define __MAIN_FILE_80021308_H__

#include "mssbTypes.h"
#include "musyx/musyx.h"

// One entry of the game's disc file tables (lbl_800EFD38 and friends).
typedef struct DiskFileEntry {
    /* 0x0 */ u32 offset;
    /* 0x4 */ u32 sizeFlags; // low 28 bits: size, top 4 bits: flags
    /* 0x8 */ u32 aramOffset;
    /* 0xC */ u32 unkC;
} DiskFileEntry; // size: 0x10

#define DISK_FILE_SIZE(e) ((e)->sizeFlags & 0x0FFFFFFF)
// Same as &table[id], but keeps the original's (id * 16) address arithmetic.
#define DISK_FILE_ENTRY(table, id) ((DiskFileEntry*)((u8*)(table) + (id) * sizeof(DiskFileEntry)))

// lbl_800F71D8: more disc file entries plus index tables used by the loaders.
typedef struct SoundFileTables {
    /* 0x000 */ DiskFileEntry files[0x1D];
    /* 0x1D0 */ u8 unk1D0[0x10];
    /* 0x1E0 */ s8 aramFiles[0x36][2];        // {lbl_800EFD38 index, sub index or -1}
    /* 0x24C */ s8 variantFiles[2][6][2];     // file offsets added to index * 7
    /* 0x264 */ s8 variantSet[0x36];          // row of variantFiles to use
    /* 0x29A */ u8 unk29A[6];
} SoundFileTables; // size: 0x2A0

// Musyx sound group data as loaded from disc. The pointers are stored as
// offsets from the start of the block and relocated after loading.
typedef struct SoundGroupData {
    /* 0x00 */ void* proj;
    /* 0x04 */ u32 projSize;
    /* 0x08 */ void* sdir;
    /* 0x0C */ u32 sdirSize;
    /* 0x10 */ void* pool;
    /* 0x14 */ u32 poolSize;
    /* 0x18 */ void* samp; // also the end of the data kept in main memory
} SoundGroupData;

typedef struct SoundManager {
    /* 0x000 */ u32 unk0;
    /* 0x004 */ SoundGroupData* groups[48];
    /* 0x0C4 */ SND_AUX_REVERBHI reverb;
    /* 0x2A4 */ SND_AUX_CHORUS chorus;
    /* 0x340 */ u8 groupStack[0x50];
    /* 0x390 */ u8 groupStackCount;
    /* 0x391 */ u8 volumeA;
    /* 0x392 */ u8 volumeB;
    /* 0x393 */ u8 unk393[3];
    /* 0x396 */ u8 soundMode;
    /* 0x397 */ u8 outputMode;
    /* 0x398 */ u8 unk398;
    /* 0x399 */ u8 loadFromAram;
    /* 0x39A */ u8 unk39A[2];
} SoundManager; // size: 0x39C

typedef void (*AramQueueCallback)(DiskFileEntry* entry, void* dst, void* user);

typedef struct AramQueueEntry {
    /* 0x00 */ DiskFileEntry* entry;
    /* 0x04 */ void* dst;
    /* 0x08 */ s32 mode;
    /* 0x0C */ u32 aramAddr;
    /* 0x10 */ AramQueueCallback callback;
    /* 0x14 */ void* user;
} AramQueueEntry; // size: 0x18

#define ARAM_QUEUE_LEN 18

typedef struct AramLoader {
    /* 0x000 */ AramQueueEntry current;
    /* 0x018 */ AramQueueEntry queue[ARAM_QUEUE_LEN];
    /* 0x1C8 */ s8 head;
    /* 0x1C9 */ s8 tail;
    /* 0x1CA */ s8 busy;
    /* 0x1CC */ u32 stadiumAram;
    /* 0x1D0 */ u32 stadiumAramPending;
    /* 0x1D4 */ u32 aramBase;
    /* 0x1D8 */ u32* aramAddrs[4];
    /* 0x1E8 */ u8 keepTask;
    /* 0x1E9 */ u8 loading;
    /* 0x1EA */ u8 loadedFlags;
    /* 0x1EB */ u8 unk1EB[0x55C - 0x1EB];
    /* 0x55C */ u32 unk55C;
    /* 0x560 */ u8 unk560[0x18];
} AramLoader; // size: 0x578

// A process-queue node (see fn_800B0A5C_insertQueue) used by the sound loader.
typedef struct SoundLoadTask {
    /* 0x00 */ void (*func)(void);
    /* 0x04 */ struct SoundLoadTask* prev;
    /* 0x08 */ struct SoundLoadTask* next;
    /* 0x0C */ struct SoundLoadTask* parent;
    /* 0x10 */ s16 done;
    /* 0x12 */ u16 priority;
    /* 0x14 */ s32 (*callback)(u8* state);
    /* 0x18 */ u8 state;
    /* 0x19 */ u8 group;
    /* 0x1A */ u8 callbackState;
} SoundLoadTask;

typedef struct SoundGroupRequest {
    /* 0x0 */ s32 group;
    /* 0x4 */ void (*onLoaded)(struct SoundGroupRequest* req, SoundGroupData* data);
    /* 0x8 */ SoundLoadTask* task;
} SoundGroupRequest;

void fn_80021308(void);
void fn_800213F4(void* p);
void* fn_800213F8(u32 size);
s32 fn_80021410(void);
void fn_8002149C(s32 group);
s32 fn_800214D0(void);
s32 fn_80021518(u16 gid, SoundGroupData* data);
s32 fn_8002158C(void);
void fn_800215F8(SoundGroupRequest* req);
void fn_80021650(DiskFileEntry* entry, void* dst, void* user);
void fn_800216F8(u8 group, s32 (*callback)(u8* state));
void fn_80021758(void);
void fn_80021954(SoundGroupData** data);
void fn_80021980(SoundGroupData* data);
void f_initSound(void);
void fn_80021AA0(void);
void fn_80021AC0(void);
void fn_80021AC4(void);
void fn_80021AC8(void);
void* fn_80021ADC(s32 index, void* dst);
void* fn_80021BBC(s32 index, void* dst);
void fn_80022620(DiskFileEntry* entry, void* dst, void* user);
void fn_8002244C(s32 unused, s32* hdr, s32 arg);
void fn_8002254C(s32 unused, s32* hdr, s32 index);
void fn_80022634(void);
void fn_800227A0(DiskFileEntry* entry, void* dst, void* user);
void fn_800227E4(void);
void fn_800229CC(void);
s32 fn_80022A24(s32 stadium, s32 variant);
void fn_80022B14(void);
s32 fn_80022CB4(DiskFileEntry* entry, void* dst, s32 mode, u32 aramAddr, AramQueueCallback callback, void* user);

#endif
