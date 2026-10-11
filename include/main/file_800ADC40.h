#ifndef __MAIN_FILE_800ADC40_H__
#define __MAIN_FILE_800ADC40_H__

#include "mssbTypes.h"
#include "Dolphin/os.h"
#include "Dolphin/ar.h"
#include "Dolphin/mtx.h"

// movie.c: HVQM4 movie player (stream thread, decode thread, AI DMA audio mix).

// One decoded video frame slot.
typedef struct MovFrame {
    /*0x0*/ u8* buf;
    /*0x4*/ u32 frame; // frame number this slot holds
    /*0x8*/ u8 ready;
    /*0x9*/ u8 _9[3];
} MovFrame; // size: 0xC

// Per-channel ADPCM decoder state used by fn_800DFDD4.
typedef struct MovAudioChan {
    /*0x00*/ u32 _00;
    /*0x04*/ u8* outPtr; // write position after decoding
    /*0x08*/ u8 _08[0x10];
} MovAudioChan; // size: 0x18

// HVQM4 video decoder context (fn_800E4xxx).
typedef struct MovVideoCtx {
    /*0x00*/ u32 _00;
    /*0x04*/ u16 width;
    /*0x06*/ u16 height;
    /*0x08*/ u8 _08[0x18];
} MovVideoCtx; // size: 0x20

typedef struct MovPlayer {
    // HVQM4 file header (0x44 bytes read from the stream)
    /*0x000*/ char magic[0x18];     // "HVQM4 1.3"
    /*0x018*/ u32 numBlocks;
    /*0x01C*/ u32 numFrames;
    /*0x020*/ u32 _020;
    /*0x024*/ u32 usecPerFrame;
    /*0x028*/ u8 _028[0xC];
    /*0x034*/ u8 videoInfo[8];      // passed to the video decoder setup
    /*0x03C*/ u8 numChannels;
    /*0x03D*/ u8 _03D[3];
    /*0x040*/ u32 sampleRate;       // 0xBBAA (48k) or 0x7D1C (32k), 0 = no audio
    /*0x044*/ u8 _044[0x1C];
    // block header (0x14 bytes)
    /*0x060*/ u32 _060;
    /*0x064*/ u32 _064;
    /*0x068*/ u32 blockVideoFrames;
    /*0x06C*/ u32 blockAudioFrames;
    /*0x070*/ u32 _070;
    /*0x074*/ u8 _074[0xC];
    // record header (8 bytes)
    /*0x080*/ u16 recType;          // 0 = audio, 1 = video
    /*0x082*/ u16 recFormat;        // video: 0x10/0x20/0x30 = I/P/B frame
    /*0x084*/ u32 recSize;
    /*0x088*/ u8 _088[0x18];
    /*0x0A0*/ MovVideoCtx video;
    /*0x0C0*/ MovAudioChan chans[2];
    /*0x0F0*/ void* file;
    /*0x0F4*/ MovFrame frames[6];
    /*0x13C*/ MovFrame* frameQueue[6];
    /*0x154*/ u8* audioStart;
    /*0x158*/ u8* audioRead;
    /*0x15C*/ u8* audioEnd;
    /*0x160*/ u8* audioWrite;
    /*0x164*/ u8* videoBuf;
    /*0x168*/ u8* audioBuf;
    /*0x16C*/ u8 _16C[0xC];
    /*0x178*/ u32 blockIndex;
    /*0x17C*/ u32 frameBase;        // first frame of the current block
    /*0x180*/ u32 curFrame;
    /*0x184*/ u32 decodedFrames;
    /*0x188*/ u32 decodeTime;       // total microseconds spent decoding
    /*0x18C*/ u32 blockVideoDone;
    /*0x190*/ u32 blockAudioDone;
    /*0x194*/ u32 _194;
    /*0x198*/ OSTime startTime;
    /*0x1A0*/ u8 _1A0[8];
    /*0x1A8*/ u64 samplesPlayed;
    /*0x1B0*/ u16 width;
    /*0x1B2*/ u16 height;
    /*0x1B4*/ s16 posY;
    /*0x1B6*/ s16 posX;
    /*0x1B8*/ u8 _1B8;
    /*0x1B9*/ u8 flags;             // bit0: sync to audio, bit1: drop frames
    /*0x1BA*/ u8 state;             // bit0 playing, bit1 loop, bit3 paused; 4 = stopped
    /*0x1BB*/ u8 rateMode;          // 1 = 48k, 0 = 32k, 0xFF = no audio
    /*0x1BC*/ volatile u8 decoding;
} MovPlayer;

// ARAM ring buffer (lbl_803C79D4) used when the whole movie is cached in ARAM.
typedef struct MovAramRing {
    /*0x00*/ u32 start;
    /*0x04*/ u32 end;
    /*0x08*/ u32 readPos;
    /*0x0C*/ u32 writePos;
    /*0x10*/ u32 size;
    /*0x14*/ u32 used;
    /*0x18*/ volatile u32 writeLen;
    /*0x1C*/ volatile u32 totalIn;
    /*0x20*/ volatile u32 totalOut;
    /*0x24*/ volatile u32 readLen;
    /*0x28*/ u8 full;
    /*0x29*/ volatile u8 busy; // 0 idle, 1 writing, 2 reading, 3 overflow
    /*0x2A*/ u8 _2A[2];
} MovAramRing;

// Main-memory ring buffer (lbl_803C7A00) fed from ARAM.
typedef struct MovMramRing {
    /*0x00*/ u8* dvdBufStart;
    /*0x04*/ u32 dvdBufSize;
    /*0x08*/ u8* start;
    /*0x0C*/ u8* end;
    /*0x10*/ u8* readPtr;
    /*0x14*/ u8* writePtr;
    /*0x18*/ u32 size;
    /*0x1C*/ u32 filled;
    /*0x20*/ u32 consumed;
} MovMramRing;

void fn_800ADC40(u8* streamBuf, u32 streamBufSize);
void fn_800ADD70(void);
void YUV2RGB(u8* src, u32* dst, s32 width, s32 height);
void YUV2RGB_(u8* src, u32* dst, s32 width, s32 height);
void fn_800AE5B8(void);
s32 fn_800AE8B8(void* arg);
BOOL MovStreamThread(MovPlayer* mov);
s32 fn_800AED24(void);
s32 MovDecodeThread(void* arg);
s32 fn_800AF1A8(MovPlayer* mov);
s32 fn_800AF5FC(MovPlayer* mov, s32 format, u32 frame);
BOOL fn_800AF9B4(void* dst, u32 len);
void fn_800AFBF0(void);
void fn_800AFC10(void);
BOOL fn_800AFD4C(void);
u8 fn_800AFFB0(void);
void fn_800AFFC0(u32 count);
BOOL fn_800B0008(u32 len);
BOOL fn_800B0134(u32 len);
void fn_800B0230(u8* dst, u32 len);
void fn_800B0390(u32 request);
void fn_800B03F4(u8* src, u32 len);
void fn_800B0580(u32 request);
void fn_800B05E4(s32 aramSize, u32 mramSize);

#endif
