#ifndef __MAIN_FILE_800B0724_H__
#define __MAIN_FILE_800B0724_H__

#include "mssbTypes.h"
#include "main/file_80063028.h"
#include "Dolphin/mtx.h"

// Arguments to sndInit (default: lbl_801112F0).
typedef struct SoundConfig {
    /*0x0*/ u8 voices;
    /*0x1*/ u8 music;
    /*0x2*/ u8 sfx;
    /*0x3*/ u8 studios;
    /*0x4*/ u32 flags;
    /*0x8*/ u32 aramSize;
} SoundConfig;

// Stack-like heap that the sound library allocates from (SndAlloc/SndFree).
typedef struct SndHeap {
    /*0x0*/ s32 free;
    /*0x4*/ u8* cur;
    /*0x8*/ u8* end;
} SndHeap;

// Header placed just before every SndAlloc block.
typedef struct SndBlockHdr {
    /*0x0*/ u8* prevCur; // heap->cur before the allocation
    /*0x4*/ u32 size;    // bytes taken from the heap, including alignment
} SndBlockHdr;

void makeLookAtMatrix(Mtx m, Vec* camPos, Vec* camUp, Vec* target);
void soundQuit(void);
void initSound(SoundConfig* config, u8* aiStack, u8* heapStart, u32 heapSize);
void SndFree(void* ptr);
void* SndAlloc(u32 size);

void fn_800B0934(void);

typedef struct DrawingQueueNode {
    void (*draw)(void);
    struct DrawingQueueNode* previous;
    struct DrawingQueueNode* next;
} DrawingQueueNode;

void fn_800B0A14_removeQueue(void* unused);

void nop_function(void);

void fn_800B0C80(void (*draw)(void));

void resetAllDrawingStructs(void);

struct SceneTask* fn_800B0A5C_insertQueue(void* draw, u16 priority);

void fn_800B0D28(void* value);

void fn_800B0D38(s32 index, s32 value);

void fn_800B117C(u8 value);

void fn_800B2160(u8 value);

s32 fn_800B216C(u8 flag, u32 mode, u8 index);

void fn_800B21A8(s32 mode);

void fn_800B2B4C(GameActor* actor, f32 value);
void fn_800B2B54(GameActor* actor, u16 bone, u8 value);
void Set_FUN_800b2b6c(GameActor* actor, s32 value);
void fn_800B2B74(GameActor* actor, u16 bone);
struct DODisplayObj* fn_800B2BA8(GameActor* actor, u16 bone, GameActor* src, u16 srcBone);
void fn_800B2BE4(GameActor* actor, u16 bone);
void fn_800B2BFC(GameActor* actor, s16 a, s16 b);
void fn_800B2C08(GameActor* actor, s16 value);
void fn_800B2C10(GameActor* actor, u16 index, Vec* v);

#endif
