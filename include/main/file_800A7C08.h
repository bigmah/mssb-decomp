#ifndef __MAIN_FILE_800A7C08_H__
#define __MAIN_FILE_800A7C08_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"

// Entry in the per-frame draw callback list. `next` holds the next entry's address with
// flags in the low two bits: bit 0 = disabled, bit 1 = field the callback runs on.
typedef union DrawLink {
    u32 raw; // TODO type: tagged pointer (DrawCallbackNode* | flags)
    struct {
        u32 addr : 30;
        u32 field : 1;
        u32 disabled : 1;
    } bits;
} DrawLink;

typedef struct DrawCallbackNode {
    /*0x0*/ DrawLink next;
    /*0x4*/ void (*func)(void);
} DrawCallbackNode;

// Video / GX system state.
typedef struct VideoSystem {
    /*0x000*/ void* xfb;
    /*0x004*/ void* fifoBase;
    /*0x008*/ GXFifoObj* fifo;
    /*0x00C*/ GXRenderModeObj* renderMode;
    /*0x010*/ GXRenderModeObj renderModeCopy;
    /*0x04C*/ DrawLink* drawList; // list heads; each links to the next head
    /*0x050*/ u8* heapLo;
    /*0x054*/ u8* heapHi;
    /*0x058*/ s32 heapSize;
    /*0x05C*/ OSThreadQueue retraceQueue;
    /*0x064*/ u8 _064[4];
    /*0x068*/ OSThread drawThread;
    /*0x380*/ OSThreadQueue drawQueue;
    /*0x388*/ OSSemaphore drawDone;
    /*0x394*/ u8 retraceInterval;
    /*0x395*/ s8 retraceCounter;
    /*0x396*/ u8 drawing;
    /*0x397*/ u8 field;
} VideoSystem;

extern VideoSystem lbl_803C7420;

u16 fn_800A8864(void);

u32 fn_800A88C0(void);

u32 fn_800A88C8(void);

u32 fn_800A88D0(void);

void fn_800A8AB0(u32 value);

void fn_800A94A8(u8 flag);

void fn_800A97D0(u8 value, s32 index);

void fn_800A97EC(s32 index, u32 enable, u8 type);

void fn_800ACCD4(void);

s32 fn_800ACC6C(s32 mode, s32 a, s32 b);

u8 fn_800ADAFC(void);

#endif
