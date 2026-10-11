#ifndef __MAIN_FILE_800A7C08_H__
#define __MAIN_FILE_800A7C08_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "Dolphin/gx.h"
#include "Dolphin/dvd.h"
#include "Dolphin/card.h"

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

#include "static/Pad.h" // PadState lbl_803C77B8[4]

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

// Task node handed out by fn_800B0A5C_insertQueue (main/file_800B0724). The 0x2C bytes
// at `data` belong to the task; the memory card tasks overlay their own layouts on it.
typedef struct Task {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct Task* prev;
    /*0x08*/ struct Task* next;
    /*0x0C*/ struct Task* parent; // task that was running when this one was queued
    /*0x10*/ s16 result;          // set by child tasks: 1 = done, 2 = failed
    /*0x12*/ u16 priority;
    /*0x14*/ u8 data[0x2C];
} Task;

typedef struct CardMountTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct Task* prev;
    /*0x08*/ struct Task* next;
    /*0x0C*/ struct Task* parent;
    /*0x10*/ s16 result;
    /*0x12*/ u16 priority;
    /*0x14*/ s32 step;
    /*0x18*/ u8 chan;
    /*0x19*/ u8 mode; // 1 = use the async CARD calls
} CardMountTask;

// Format, delete-file and file-exists/free-space tasks.
typedef struct CardNameTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct Task* prev;
    /*0x08*/ struct Task* next;
    /*0x0C*/ struct Task* parent;
    /*0x10*/ s16 result;
    /*0x12*/ u16 priority;
    /*0x14*/ s32 step;
    /*0x18*/ u8 chan;
    /*0x19*/ u8 mode;
    /*0x1A*/ s16 arg; // file-exists flag (fn_800AA44C) or blocks needed (fn_800AB534)
    /*0x1C*/ char* fileName;
    /*0x20*/ u8 outcome;
} CardNameTask;

// Load task (fn_800AAA70); fn_800ABBD0 runs as its child and uses the file fields.
typedef struct CardFileTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct Task* prev;
    /*0x08*/ struct Task* next;
    /*0x0C*/ struct Task* parent;
    /*0x10*/ s16 result;
    /*0x12*/ u16 priority;
    /*0x14*/ CARDFileInfo fileInfo;
    /*0x28*/ s32 step;
    /*0x2C*/ void* buffer;
    /*0x30*/ s32 length;
    /*0x34*/ char* fileName;
    /*0x38*/ s32 fileNo;
    /*0x3C*/ u8 chan;
    /*0x3D*/ u8 mode;
} CardFileTask;

// Save task (fn_800AAFEC); fn_800ABF44 runs as its child.
typedef struct CardWriteTask {
    /*0x00*/ void (*func)(void);
    /*0x04*/ struct Task* prev;
    /*0x08*/ struct Task* next;
    /*0x0C*/ struct Task* parent;
    /*0x10*/ s16 result;
    /*0x12*/ u16 priority;
    /*0x14*/ CARDFileInfo fileInfo;
    /*0x28*/ s32 step;
    /*0x2C*/ void* buffer;
    /*0x30*/ s32 length;
    /*0x34*/ s32 fileNo;
    /*0x38*/ u8 chan;
    /*0x39*/ u8 mode;
    /*0x3A*/ u8 permissions;
} CardWriteTask;

// Load/save request passed to fn_800AA930 / fn_800AAEE4.
typedef struct CardRequest {
    /*0x00*/ char* fileName;
    /*0x04*/ void* buffer;
    /*0x08*/ s32 length; // multiple of CARD_READ_SIZE
    /*0x0C*/ u8 chan;
    /*0x0D*/ u8 mode;
    /*0x0E*/ u8 permissions; // 0 = CARD_ATTR_PUBLIC
    /*0x0F*/ u8 _0F;
    /*0x10*/ u8 (*verify)(void* buffer, s32 length, u32 arg); // returns CARD_STATUS_READY if OK
    /*0x14*/ u32 verifyArg;
    /*0x18*/ u32 flags; // bit 0: skip the CRC
} CardRequest;

// Start of every save buffer.
typedef struct CardSaveHeader {
    /*0x00*/ char comment[2][0x20];
    /*0x40*/ u16 crc; // CRC-16 of everything after the header
    /*0x42*/ u16 _42;
} CardSaveHeader;

typedef struct CardSlot {
    /*0x00*/ u64 serial;
    /*0x08*/ s32 probeResult;
    /*0x0C*/ s32 memSize; // megabits
    /*0x10*/ s32 sectorSize;
    /*0x14*/ s32 blocksFree;
    /*0x18*/ s32 bytesFree;
    /*0x1C*/ s32 filesFree;
    /*0x20*/ s32 blocksTotal;
    /*0x24*/ u8 _24[4];
} CardSlot;

// Memory card state (lbl_803C7838).
typedef struct CardSystem {
    /*0x00*/ CardSlot slots[2];
    /*0x50*/ s32 lastResult;
    /*0x54*/ u8 status; // CARD_STATUS_* or an error code
    /*0x55*/ u8 op;     // current operation
    /*0x56*/ u8 hasBanner;
    /*0x57*/ u8 iconCount;
    /*0x58*/ s32 xferred;
    /*0x5C*/ s8 progress; // percent
    /*0x5D*/ u8 _5D[3];
} CardSystem;

#define CARD_STATUS_BUSY 0xF
#define CARD_STATUS_SERIAL_MISMATCH 0x10
#define CARD_STATUS_READY 0x11
#define CARD_RESULT_BAD_SECTOR_SIZE -129

// Movie (THP) playback.
typedef struct ThpVideoInfo {
    /*0x0*/ void* work;
    /*0x4*/ u16 width;
    /*0x6*/ u16 height;
    /*0x8*/ u8 mcuX;
    /*0x9*/ u8 mcuY;
    /*0xA*/ u8 _A[2];
} ThpVideoInfo;

typedef struct ThpFrame {
    /*0x0*/ u8* data;
    /*0x4*/ u32 frameNo;
    /*0x8*/ u8 state; // 1 = decoded, 2 = shown
    /*0x9*/ u8 _9[3];
} ThpFrame;

typedef struct ThpMovie {
    /*0x00*/ u8 _00[0xC];
    /*0x0C*/ u32 _0C;
} ThpMovie;

typedef struct ThpBufferInfo {
    /*0x0*/ u8 _0[8];
    /*0x8*/ void* buffer;
    /*0xC*/ u8 _C[4];
} ThpBufferInfo;

typedef struct ThpPlayer {
    /*0x000*/ u8 _000[0x24];
    /*0x024*/ u32 frameTime; // microseconds per frame
    /*0x028*/ u32 readBufSize;
    /*0x02C*/ u8 _02C[4];
    /*0x030*/ u32 audioBufSize;
    /*0x034*/ u8 _034[0xC];
    /*0x040*/ u32 audioRate;
    /*0x044*/ u8 _044[0x5C];
    /*0x0A0*/ ThpVideoInfo video;
    /*0x0AC*/ u8 _0AC[0x24];
    /*0x0D0*/ u8* _D0;
    /*0x0D4*/ u8* _D4;
    /*0x0D8*/ u8 _0D8[0x10];
    /*0x0E8*/ u8* _E8;
    /*0x0EC*/ u8* _EC;
    /*0x0F0*/ ThpMovie* movie;
    /*0x0F4*/ ThpFrame frames[6];
    /*0x13C*/ ThpFrame* framePtrs[6];
    /*0x154*/ u8* _154;
    /*0x158*/ u8* _158;
    /*0x15C*/ u8* _15C;
    /*0x160*/ u8* _160;
    /*0x164*/ u8* readBuf;
    /*0x168*/ u8* audioBuf;
    /*0x16C*/ u8* texBuf[2];
    /*0x174*/ u32 texIndex;
    /*0x178*/ u8 _178[8];
    /*0x180*/ u32 currentFrame;
    /*0x184*/ u8 _184[0x14];
    /*0x198*/ OSTime startTime;
    /*0x1A0*/ OSTime pauseStart;
    /*0x1A8*/ u64 startFrameTime;
    /*0x1B0*/ u8 _1B0[8];
    /*0x1B8*/ u8 format;
    /*0x1B9*/ u8 flags;
    /*0x1BA*/ u8 state;
    /*0x1BB*/ u8 _1BB;
} ThpPlayer;

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

BOOL fn_800ADAFC(void);

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
void fn_800A9864(u8 chan, u8 mode, u64 serial);
void fn_800A98FC(void);
void fn_800A9CF8(void);
void fn_800A9E34(u8 chan, u8 mode, u64 serial);
void fn_800A9ECC(void);
u16 fn_800ABB14(u8* data, s32 len);
void fn_800ABB60(void);
void fn_800ACCE8(void);
void fn_800ACD44(void);
void fn_800ACD64(s32 result);
void fn_800AA34C(u8 chan, u8 mode, char* fileName, u64 serial, u8 setSerial);
void fn_800AA44C(void);
void fn_800AA930(CardRequest* req, u64 serial);
void fn_800AAA70(void);
void fn_800AAEE4(CardRequest* req, u64 serial);
void fn_800AAFEC(void);
void fn_800AB474(u8 chan, u8 mode, s16 blocks, char* fileName, u64 serial);
void fn_800AB534(void);
void fn_800ABBD0(void);
void fn_800ABF44(void);
void fn_800ACF14(void* block);
void* fn_800ACF34(s32 align, s32 size);
void fn_800ACF78(void* block, s32 size);
void fn_800ACFB0(void* block);
void* _OSAllocFromHeap(s32 align, s32 size);
void fn_800AD01C(void* hi);
void fn_800AD038(void* lo);
void fn_800AD054(void* lo, void* hi);
void fn_800AC508(char* fileName, void* bannerTpl, s32 bannerSize, void* iconTpl, s32 iconSize, u32 iconSpeed,
                 u32 bannerFlags, char* comment, char* subComment, s32 blocks);
void fn_800AD070(void);
u32 fn_800AD490(ThpPlayer* p);
void fn_800AD500(ThpPlayer* p, u8* work);
u32 fn_800AD6BC(ThpPlayer* p);
BOOL fn_800AD780(ThpPlayer* p);
void fn_800AD830(ThpPlayer* p);
void fn_800AD914(ThpPlayer* p);
void fn_800AD95C(ThpPlayer* p, u8 flags);
void fn_800AD9F4(ThpPlayer* p);
BOOL fn_800ADB04(ThpMovie* movie, ThpPlayer* p, u8 format, u8 freeBuffer);
void fn_800ADBFC(void);
void* fn_800A7C08(void* arg);
void fn_800A84C4(u32 retraceCount);
void initRenderMode(GXRenderModeObj* rmode, u32 fifoSize, u32 overscan);

#endif
