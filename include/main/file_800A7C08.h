#ifndef __MAIN_FILE_800A7C08_H__
#define __MAIN_FILE_800A7C08_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/dvd.h"

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

// TODO type: the shared system/game state at 0x803C6CF8 (used as u8[] elsewhere)
typedef struct GlobalState6CF8 {
    /*0x000*/ u8 _000[0x715];
    /*0x715*/ u8 _715;
    /*0x716*/ u8 _716[2];
    /*0x718*/ s32 entryNum; // DVD entry of the file being opened
    /*0x71C*/ u8 _71C[6];
    /*0x722*/ s8 _722;
} GlobalState6CF8;

// DVD audio streaming playlist.
enum {
    STREAM_STATE_STOP = 0,
    STREAM_STATE_PLAY = 1,
    STREAM_STATE_PAUSE = 2,
    STREAM_STATE_BUSY = 3 // waiting on an async DVD command
};

enum {
    STREAM_MODE_ONCE = 0,   // play the list through, then stop
    STREAM_MODE_LOOP = 1,   // play the list forever
    STREAM_MODE_REPEAT = 2  // repeat the current track
};

// StreamTrack.flags bits select which events reach the callback.
enum {
    STREAM_EVENT_PLAY = 0x1,
    STREAM_EVENT_STOP = 0x2,
    STREAM_EVENT_PAUSE = 0x4,
    STREAM_EVENT_LOADED = 0x8,
    STREAM_EVENT_END = 0x10,
    STREAM_EVENT_PREPARED = 0x20
};

typedef struct StreamTrack {
    /*0x00*/ struct StreamTrack* prev;
    /*0x04*/ struct StreamTrack* next;
    /*0x08*/ u32 flags;
    /*0x0C*/ void (*callback)(u32 event);
    /*0x10*/ DVDFileInfo fileInfo;
    /*0x4C*/ void* file;
} StreamTrack;

// Controller bookkeeping (lbl_803C77B8), one per port.
typedef struct PadSticks {
    s8 stickX;
    s8 stickY;
    s8 substickX;
    s8 substickY;
} PadSticks;

typedef struct PadAnalog {
    u8 triggerLeft;
    u8 triggerRight;
    u8 analogA;
    u8 analogB;
} PadAnalog;

typedef struct PadState {
    /*0x00*/ u16 held;
    /*0x02*/ u16 down;
    /*0x04*/ u16 repeat;
    /*0x06*/ u16 prev;
    /*0x08*/ s8 err;
    /*0x09*/ u8 rumbleCmd; // 1 = start requested, 2 = rumbling
    /*0x0A*/ u8 rumbleTimer;
    /*0x0B*/ u8 rumbleMode;
    /*0x0C*/ s8 repeatDelay;
    /*0x0D*/ s8 repeatTimer;
    /*0x0E*/ u8 _0E[2];
    /*0x10*/ PadSticks sticks;
    /*0x14*/ PadAnalog analog;
    /*0x18*/ u32 stickDirs;
    /*0x1C*/ u8 _1C[4];
} PadState;

// PadState.stickDirs bits (shifted right by PadConfig.stickShift and ORed into the buttons).
#define PAD_STICK_UP 0x80000
#define PAD_STICK_DOWN 0x40000
#define PAD_STICK_RIGHT 0x20000
#define PAD_STICK_LEFT 0x10000
#define PAD_SUBSTICK_UP 0x8
#define PAD_SUBSTICK_DOWN 0x4
#define PAD_SUBSTICK_RIGHT 0x2
#define PAD_SUBSTICK_LEFT 0x1

// Controller settings (lbl_80110080).
typedef struct PadConfig {
    /*0x0*/ u32 readMask;
    /*0x4*/ u8 repeatDelay;
    /*0x5*/ u8 repeatRate;
    /*0x6*/ u8 rumbleLockMask;
    /*0x7*/ u8 stickShift;
    /*0x8*/ s8 stickNeg;
    /*0x9*/ s8 stickPos;
} PadConfig;

#define STREAM_NOTIFY(track, ev)                                                       \
    if ((track) != NULL && (track)->callback != NULL && ((track)->flags & (ev)) != 0) { \
        (track)->callback((track)->flags & (ev));                                      \
    }

u16 fn_800A8864(void);

StreamTrack* fn_800A88C0(void);

u32 fn_800A88C8(void);

u32 fn_800A88D0(void);

void fn_800A8AB0(u32 value);

void fn_800A94A8(s32 result, DVDCommandBlock* block);

void fn_800A97D0(u8 shift, s32 threshold);

void fn_800A97EC(s32 index, u32 duration, u8 mode);

void fn_800ACCD4(void);

s32 fn_800ACC6C(s32 mode, s32 a, s32 b);

u8 fn_800ADAFC(void);

s32 fn_800A8518(s32 cmd);
void fn_800A86B4(s32 cmd);
void fn_800A8878(u8 left, u8 right);
void fn_800A88D8(u32 state);
void fn_800A8AB8(void (*onShutdown)(void));
s32 fn_800A8B78(StreamTrack* track);
s32 LoadFile(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event), u32 options);
s32 fn_800A8E30(void* file, StreamTrack* track, u32 flags, void (*callback)(u32 event));
void fn_800A8F68(void);
void fn_800A8FDC(s32 result, DVDCommandBlock* block);
void fn_800A9034(s32 result, DVDCommandBlock* block);
void fn_800A908C(s32 result, DVDCommandBlock* block);
void fn_800A90E4(s32 result, DVDCommandBlock* block);
void fn_800A9168(u32 count);
void fn_800A91B0(s32 result, DVDCommandBlock* block);
void fn_800A93AC(s32 result, DVDFileInfo* fileInfo);
void fn_800A9424(s32 result, DVDFileInfo* fileInfo);
void fn_800A94C4(void);
void fn_800A9520(void);
void fn_800A983C(void);

#endif
