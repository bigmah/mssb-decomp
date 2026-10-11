#include "main/file_800ADC40.h"
#include "main/file_80008E00.h"
#include "static/UnknownHomes_Static.h"
#include "Dolphin/os.h"
#include "Dolphin/ai.h"
#include "Dolphin/ar.h"
#include "Dolphin/gx.h"
#include "Dolphin/mtx.h"
#include "Dolphin/stl.h"
#include "string.h"

void* _OSAllocFromHeap(s32 align, u32 size);

// movie.c: HVQM4 movie player.

typedef struct MovThreads {
    /*0x000*/ OSThread decodeThread;
    /*0x318*/ OSThread streamThread;
    /*0x630*/ OSMessage msgs[8];
} MovThreads; // lbl_802FB220, size: 0x650

typedef struct MovQueue {
    /*0x0000*/ OSMessageQueue queue;
    /*0x0020*/ u8 _20[0x10];
    /*0x0030*/ u8 streamStack[0x1000];
    /*0x1030*/ u8 decodeStack[0x2000];
} MovQueue; // lbl_802FB870, size: 0x3030

// YUV->RGB lookup tables; the s16 tables hold byte offsets into clamp.
typedef struct YuvTable {
    /*0x000*/ s16 y[256];
    /*0x200*/ s16 vR[256];
    /*0x400*/ s16 vG[256];
    /*0x600*/ s16 uG[256];
    /*0x800*/ s16 uB[256];
    /*0xA00*/ u8 clamp[0x600];
} YuvTable;

typedef struct MovSync {
    /*0x00*/ u8 _00[0x5C];
    /*0x5C*/ OSThreadQueue sleepQueue;
} MovSync; // lbl_803C7420

// movie.c bss (not split into this unit yet)
extern s16 lbl_802F93A0[16];       // quad vertices, buffer 0
extern s16 lbl_802F93C0[16];       // quad vertices, buffer 1
extern s16 lbl_802F93E0[2][0x780]; // AI DMA double buffer
extern Mtx44 lbl_802FB1E0;         // ortho projection
extern MovThreads lbl_802FB220;
extern MovQueue lbl_802FB870;

extern GXTexObj lbl_803C78A4;
extern ARQRequest lbl_803C78C4[2]; // ARAM -> MRAM
extern ARQRequest lbl_803C7994[2]; // MRAM -> ARAM
extern MovAramRing lbl_803C79D4;
extern MovMramRing lbl_803C7A00;
extern MovSync lbl_803C7420;
// TODO: static in Unknown/File_0x800a6304.c; first word is the free ARAM byte count.
extern u32 data_803C6780;

extern u16 lbl_801101C0[128]; // volume table
extern YuvTable lbl_801102C0;
extern u8 lbl_801112C0[0x20]; // quad display list

extern u8 lbl_803CBAE0;   // audio volume (0-127)
extern u16 lbl_803CBAE2;
extern u16 lbl_803CBAE4;  // AI DMA length in bytes
extern u8** lbl_803CBAE8[2]; // stream read pointer (DVD, MRAM)
extern u8** lbl_803CBAF0[2]; // stream write pointer (DVD, MRAM)
extern u32* lbl_803CBAF8[2]; // stream bytes available (DVD, MRAM)
extern s16* lbl_803CBB00[2]; // quad vertex buffers

extern MovPlayer* lbl_803CC170; // movie being played
extern u8* lbl_803CC174;        // stream buffer
extern u32 lbl_803CC178;        // stream buffer size
extern u8 lbl_803CC17C;         // quit request
extern u8 lbl_803CC17D;
extern u8 lbl_803CC17E;         // decode thread running
extern u8 lbl_803CC17F;         // initialised
extern u8 lbl_803CC180;         // decode step
extern u8 lbl_803CC181;         // movie is cached in ARAM
extern u8 lbl_803CC182;
extern f32 lbl_803CC184;        // quad depth
extern u32 lbl_803CC188;        // AI DMA buffer index
extern AIDCallback lbl_803CC18C; // previous AI DMA callback
extern u32 lbl_803CC190;
extern u8 lbl_803CC194;         // vertex buffer index
extern s32 lbl_803CC19C;        // last decode result
extern u32 lbl_803CC1A0;        // stream bytes consumed
extern u32 lbl_803CC1A4;        // stream length
extern u8 lbl_803CC1A8;         // ARAM write counter
extern u32 lbl_803CC1AC;        // movie file size

#define MOV_STATE_STOP 4

// .text:0x800ADC40 size:0x130
// NONMATCHING: the bss lives in another split; the original addresses it relative to lbl_802F93A0
#if NONMATCHING
void fn_800ADC40(u8* streamBuf, u32 streamBufSize) {
    if (lbl_803CC17F == 0) {
        lbl_803CC174 = streamBuf;
        lbl_803CC178 = streamBufSize;
        if (AIGetDSPSampleRate() == 1) {
            lbl_803CBAE2 = 0xF0;
            lbl_803CBAE4 = 0x3C0;
        } else {
            lbl_803CBAE2 = 0xA0;
            lbl_803CBAE4 = 0x280;
        }
        fn_800E4AC8();
        lbl_803CC170 = NULL;
        lbl_803CC17C = 0;
        lbl_803CC190 = 0;
        lbl_803CC180 = 0;
        lbl_803CC18C = AIRegisterDMACallback(fn_800AE5B8);
        C_MTXOrtho(lbl_802FB1E0, 0.0f, 480.0f, 0.0f, 640.0f, -0.0f, -16777216.0f);
        OSInitMessageQueue(&lbl_802FB870.queue, lbl_802FB220.msgs, 8);
        OSCreateThread(&lbl_802FB220.streamThread, fn_800AE8B8, NULL, lbl_802FB870.streamStack + sizeof(lbl_802FB870.streamStack),
                       sizeof(lbl_802FB870.streamStack), 20, 1);
        OSCreateThread(&lbl_802FB220.decodeThread, MovDecodeThread, NULL, lbl_802FB870.decodeStack + sizeof(lbl_802FB870.decodeStack),
                       sizeof(lbl_802FB870.decodeStack), 31, 1);
        OSResumeThread(&lbl_802FB220.streamThread);
        OSResumeThread(&lbl_802FB220.decodeThread);
        lbl_803CC17F = 1;
    }
}
#endif

// .text:0x800ADD70 size:0x1F0
void fn_800ADD70(void) {
    MovPlayer* mov = lbl_803CC170;
    f32 proj[7];
    Mtx mtx;
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    s16* v;
    s16 z;

    if (mov != NULL) {
        GXGetProjectionv(proj);
        GXSetProjection(lbl_802FB1E0, GX_ORTHOGRAPHIC);
        GXInvalidateTexAll();
        GXLoadTexObj(&lbl_803C78A4, GX_TEXMAP0);
        GXInvalidateVtxCache();
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U8, 0);
        lbl_803CC194 ^= 1;
        v = lbl_803CBB00[lbl_803CC194];
        v[9] = v[0] = mov->posX;
        v[4] = v[1] = mov->posY;
        v[6] = v[3] = mov->posX + (mov->width - 1);
        v[10] = v[7] = mov->posY + (mov->height - 1);
        z = lbl_803CC184;
        v[11] = v[8] = v[5] = v[2] = z;
        DCFlushRange(v, 0x18);
        GXSetArray(GX_VA_POS, v, 6);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(1);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetChanMatColor(GX_COLOR0A0, color);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        PSMTXIdentity(mtx);
        GXLoadPosMtxImm(mtx, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXCallDisplayList(lbl_801112C0, 0x20);
        GXSetProjectionv(proj);
    }
}

#define YUV_CLAMP(t, y, c) ((t)->clamp[(y) + (c)])

// .text:0x800ADF60 size:0x338
// Converts a planar YUV 4:2:0 image to GX RGBA8 tiles.
void YUV2RGB(u8* src, u32* dst, s32 width, s32 height) {
    YuvTable* t = &lbl_801102C0;
    u8* y0;
    u8* y1;
    u8* u;
    u8* v;
    u8* tileRow;
    u8* p;
    u32* out;
    u8 row;
    s32 x;
    s32 vR, g, uB, ya, yb;

    if (src == NULL) {
        OSReport("YUV->RGB Conv SrcAddr is NULL!!\n");
        for (;;) {}
    }
    if (dst == NULL) {
        OSReport("YUV->RGB Conv DstAddr is NULL!!\n");
        for (;;) {}
    }
    x = width;
    y0 = src;
    y1 = src + width;
    u = src + width * height;
    v = u + (width >> 1) * (height >> 1);
    tileRow = (u8*)dst;
    do {
        for (row = 0; row <= 4; row += 4) {
            p = tileRow;
            out = (u32*)(tileRow + row * 4);
            do {
                vR = t->vR[v[0]];
                g = t->vG[v[0]] + t->uG[u[0]];
                uB = t->uB[u[0]];
                ya = t->y[y0[0]];
                yb = t->y[y0[1]];
                out[0] = (YUV_CLAMP(t, ya, vR) << 16) | 0xFF00FF00 | YUV_CLAMP(t, yb, vR);
                out[8] = (YUV_CLAMP(t, ya, g) << 24) | (YUV_CLAMP(t, ya, uB) << 16) | (YUV_CLAMP(t, yb, g) << 8) | YUV_CLAMP(t, yb, uB);
                ya = t->y[y1[0]];
                yb = t->y[y1[1]];
                out[2] = (YUV_CLAMP(t, ya, vR) << 16) | 0xFF00FF00 | YUV_CLAMP(t, yb, vR);
                out[10] = (YUV_CLAMP(t, ya, g) << 24) | (YUV_CLAMP(t, ya, uB) << 16) | (YUV_CLAMP(t, yb, g) << 8) | YUV_CLAMP(t, yb, uB);

                vR = t->vR[v[1]];
                g = t->vG[v[1]] + t->uG[u[1]];
                uB = t->uB[u[1]];
                ya = t->y[y0[2]];
                yb = t->y[y0[3]];
                out[1] = (YUV_CLAMP(t, ya, vR) << 16) | 0xFF00FF00 | YUV_CLAMP(t, yb, vR);
                out[9] = (YUV_CLAMP(t, ya, g) << 24) | (YUV_CLAMP(t, ya, uB) << 16) | (YUV_CLAMP(t, yb, g) << 8) | YUV_CLAMP(t, yb, uB);
                ya = t->y[y1[2]];
                yb = t->y[y1[3]];
                out[3] = (YUV_CLAMP(t, ya, vR) << 16) | 0xFF00FF00 | YUV_CLAMP(t, yb, vR);
                out[11] = (YUV_CLAMP(t, ya, g) << 24) | (YUV_CLAMP(t, ya, uB) << 16) | (YUV_CLAMP(t, yb, g) << 8) | YUV_CLAMP(t, yb, uB);

                v += 2;
                u += 2;
                y0 += 4;
                y1 += 4;
                if (row == 4) {
                    __dcbf(p, 0);
                    __dcbf(p + 0x20, 0);
                }
                x -= 4;
                p += 0x40;
                out += 0x10;
            } while (x > 0);
            y0 = y1;
            x = width;
            y1 += width;
        }
        tileRow = p;
    } while ((height -= 4) > 0);
    PPCSync();
}

#define RGB565(r, g, b) ((((r) << 8) & 0xF800) | (((g) << 3) & 0x7E0) | (((b) & 0xF8) >> 3))

// .text:0x800AE298 size:0x320
// Converts a planar YUV 4:2:0 image to GX RGB565 tiles.
void YUV2RGB_(u8* src, u32* dst, s32 width, s32 height) {
    YuvTable* t = &lbl_801102C0;
    u8* y0;
    u8* y1;
    u8* u;
    u8* v;
    u8* tileRow;
    u8* p;
    u32* out;
    u8 row;
    s32 x;
    s32 vR, g, uB, ya, yb;

    if (src == NULL) {
        OSReport("YUV->RGB Conv SrcAddr is NULL!!\n");
        for (;;) {}
    }
    if (dst == NULL) {
        OSReport("YUV->RGB Conv DstAddr is NULL!!\n");
        for (;;) {}
    }
    x = width;
    y0 = src;
    y1 = src + width;
    u = src + width * height;
    v = u + (width >> 1) * (height >> 1);
    tileRow = (u8*)dst;
    do {
        for (row = 0; row <= 4; row += 4) {
            p = tileRow;
            out = (u32*)(tileRow + row * 4);
            do {
                vR = t->vR[v[0]];
                g = t->vG[v[0]] + t->uG[u[0]];
                uB = t->uB[u[0]];
                ya = t->y[y0[0]];
                yb = t->y[y0[1]];
                out[0] = (RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB));
                ya = t->y[y1[0]];
                yb = t->y[y1[1]];
                out[2] = (RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB));

                vR = t->vR[v[1]];
                g = t->vG[v[1]] + t->uG[u[1]];
                uB = t->uB[u[1]];
                ya = t->y[y0[2]];
                yb = t->y[y0[3]];
                out[1] = (RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB));
                ya = t->y[y1[2]];
                yb = t->y[y1[3]];
                out[3] = (RGB565(YUV_CLAMP(t, ya, vR), YUV_CLAMP(t, ya, g), YUV_CLAMP(t, ya, uB)) << 16) |
                         RGB565(YUV_CLAMP(t, yb, vR), YUV_CLAMP(t, yb, g), YUV_CLAMP(t, yb, uB));

                v += 2;
                u += 2;
                y0 += 4;
                y1 += 4;
                if (row == 4) {
                    __dcbf(p, 0);
                }
                x -= 4;
                p += 0x20;
                out += 8;
            } while (x > 0);
            y0 = y1;
            x = width;
            y1 += width;
        }
        tileRow = p;
    } while ((height -= 4) > 0);
    PPCSync();
}

// Mixes the movie's decoded audio into an AI DMA buffer.
static inline void MovMixAudio(s16* dst) {
    MovPlayer* mov = lbl_803CC170;
    u8 volume = lbl_803CBAE0;
    u16 len = lbl_803CBAE4;
    u8* read;
    u32 off;
    u32 n;
    s16 sample;

    if (mov == NULL || !(mov->state & 1) || (mov->state & 8) || !(mov->flags & 1)) {
        return;
    }
    read = mov->audioRead;
    if (read < mov->audioWrite && (read + len > mov->audioWrite || (mov->state & 2))) {
        return;
    }
    off = 0;
    for (n = len >> 1; n != 0; n--) {
        if (read + off > mov->audioEnd) {
            read = mov->audioStart - off;
        }
        sample = *(s16*)(read + off);
        off += 2;
        *dst += (s16)((sample & 0x8000) + (((u32)(sample * lbl_801101C0[volume & 0x7F]) >> 15) & 0x7FFF));
        dst++;
    }
    mov->audioRead += len;
    mov->samplesPlayed += len;
    mov->startTime = OSGetTime();
    if (mov->audioRead >= mov->audioEnd) {
        mov->audioRead = mov->audioStart + (mov->audioRead - mov->audioEnd);
    }
}

// .text:0x800AE5B8 size:0x300
// AI DMA callback: queues the next buffer and mixes movie audio into it.
void fn_800AE5B8(void) {
    s16* buf;
    s16* cur;
    BOOL intr;

    lbl_803CC18C();
    lbl_803CC188 ^= 1;
    buf = lbl_802F93E0[lbl_803CC188];
    cur = (s16*)OSPhysicalToCached(AIGetDMAStartAddr());
    if (cur != NULL) {
        intr = OSEnableInterrupts();
        DCInvalidateRange(cur, lbl_803CBAE4);
        MovMixAudio(cur);
        DCFlushRange(cur, lbl_803CBAE4);
        OSRestoreInterrupts(intr);
    } else {
        AIInitDMA((u32)buf, lbl_803CBAE4);
        intr = OSEnableInterrupts();
        memset(buf, 0, lbl_803CBAE4);
        MovMixAudio(buf);
        DCFlushRange(buf, lbl_803CBAE4);
        OSRestoreInterrupts(intr);
    }
}

// Reads the next block header and restarts playback timing.
static inline BOOL MovStartBlock(MovPlayer* mov) {
    BOOL intr;

    if (!fn_800AF9B4(&mov->_060, 0x14)) {
        OSPanic("movie.c", 0x355, "sNp_MovDecodeThread()::ERR!! broken file.\n");
        return FALSE;
    }
    if ((mov->flags & 1) && mov->rateMode == 0xFF) {
        mov->flags &= ~1;
    }
    intr = OSDisableInterrupts();
    mov->samplesPlayed = 0;
    mov->startTime = 0;
    mov->decodedFrames = 0;
    mov->decodeTime = 0;
    mov->blockAudioDone = 0;
    mov->blockVideoDone = 0;
    mov->frameBase = 0;
    mov->blockIndex = 0;
    mov->audioRead = mov->audioWrite = mov->audioStart;
    mov->state = 9;
    lbl_803CC180 = 0;
    OSRestoreInterrupts(intr);
    return TRUE;
}

static inline void MovResetFrames(MovPlayer* mov) {
    mov->frames[0].ready = 0;
    mov->frames[1].ready = 0;
    mov->frames[2].ready = 0;
    mov->frames[3].ready = 0;
    mov->frames[4].ready = 0;
    mov->frames[5].ready = 0;
}

// .text:0x800AE8B8 size:0x260
// Stream thread: handles play / restart / stop / pause / quit messages.
s32 fn_800AE8B8(void* arg) {
    OSMessage msg;
    MovPlayer* mov;

    for (;;) {
        OSReceiveMessage(&lbl_802FB870.queue, &msg, OS_MESSAGE_BLOCK);
        mov = lbl_803CC170;
        switch ((s32)msg) {
        case 0:
            if (MovStreamThread(mov) == FALSE) {
                OSSendMessage(&lbl_802FB870.queue, (OSMessage)0, OS_MESSAGE_BLOCK);
            } else {
                lbl_803CC17D = 1;
            }
            break;
        case 1:
            MovStartBlock(mov);
            break;
        case 2:
            mov->state = MOV_STATE_STOP;
            while (mov->decoding) {
                OSSleepThread(&lbl_803C7420.sleepQueue);
            }
            if (!lbl_803CC181) {
                fn_800A6C80();
                while (lbl_803C6CF8._715 != 1) {}
            }
            MovResetFrames(mov);
            mov->samplesPlayed = 0;
            mov->startTime = 0;
            mov->decodedFrames = 0;
            mov->decodeTime = 0;
            mov->blockAudioDone = 0;
            mov->blockVideoDone = 0;
            mov->frameBase = 0;
            mov->blockIndex = 0;
            mov->audioRead = mov->audioWrite = mov->audioStart;
            lbl_803CC170 = NULL;
            if (lbl_803CC181) {
                fn_800AFBF0();
            }
            break;
        case 3:
            lbl_803CC182 = 0;
            lbl_803CC17D = 0;
            break;
        case 4:
            lbl_803CC182 = 0;
            AIRegisterDMACallback(lbl_803CC18C);
            lbl_803CC18C = NULL;
            while (lbl_803CC17E) {
                OSSleepThread(&lbl_803C7420.sleepQueue);
            }
            lbl_803CC17F = 0;
            return 0;
        }
    }
}

// .text:0x800AEB18 size:0x20C
// Opens the movie stream and parses the HVQM4 header.
BOOL MovStreamThread(MovPlayer* mov) {
    s32 i;

    lbl_803CC1A0 = 0;
    fn_800A6E24(mov->file, lbl_803CC174, lbl_803CC178);
    if (lbl_803CC181) {
        fn_800B05E4(-1, 0x10000);
        lbl_803CC174 = lbl_803C7A00.start;
        lbl_803CC178 = lbl_803C7A00.size;
    }
    if (!fn_800AF9B4(mov, 0x44)) {
        OSPanic("movie.c", 0x2ED, "sNp_MovStreamThread()::ERR!! broken file.\n");
        return FALSE;
    }
    if (strncmp("HVQM4 1.3", mov->magic, strlen("HVQM4 1.3")) != 0) {
        for (i = 0; i < 0x44; i++) {}
        OSPanic("movie.c", 0x300, "sNp_MovStreamThread()::ERR!! Invalid version.\n");
        return FALSE;
    }
    mov->rateMode = 0xFF;
    if (mov->sampleRate != 0) {
        if (mov->sampleRate == 0xBBAA) {
            if (AIGetDSPSampleRate() != 1) {
                OSPanic("movie.c", 0x30B, "sNp_MovStreamThread()::ERR!! Invalid audio samples per second \n");
                return FALSE;
            }
            mov->rateMode = 1;
        } else if (mov->sampleRate == 0x7D1C) {
            if (AIGetDSPSampleRate() != 0) {
                OSPanic("movie.c", 0x313, "sNp_MovStreamThread()::ERR!! Invalid audio samples per second \n");
                return FALSE;
            }
            mov->rateMode = 0;
        } else {
            OSPanic("movie.c", 0x31A, "sNp_MovStreamThread()::ERR!! Invalid audio samples per second \n");
            return FALSE;
        }
    }
    fn_800E4AE8(&mov->video, mov->videoInfo);
    if (fn_800E4B1C(&mov->video) == 0) {
        OSPanic("movie.c", 0x324, "sNp_MovStreamThread()::ERR!! failed to allocate the working buffer\n");
        return FALSE;
    }
    mov->width = mov->video.width;
    mov->height = mov->video.height;
    mov->posY = (480 - mov->height) >> 1;
    mov->posX = (640 - mov->width) >> 1;
    return TRUE;
}

// fn_800AED24, size:0x10
s32 fn_800AED24(void) {
    return !lbl_803CC19C;
}

// Frame the playback clock is at: wall time since the last audio DMA,
// plus the audio already played when syncing to audio.
static inline u32 MovClockFrame(MovPlayer* mov) {
    if (mov->flags & 1) {
        return (OSTicksToMicroseconds(OSGetTime() - mov->startTime) +
                mov->samplesPlayed * 1000000 / (mov->sampleRate * 4)) /
               mov->usecPerFrame;
    }
    return OSTicksToMicroseconds(OSGetTime() - mov->startTime) / mov->usecPerFrame;
}

// .text:0x800AED34 size:0x474
// Decode thread: runs the decoder and handles end of movie / looping.
s32 MovDecodeThread(void* arg) {
    MovPlayer* mov;
    BOOL ok;

    OSSuspendThread(&lbl_802FB220.decodeThread);
    lbl_803CC17E = 1;
    while (!lbl_803CC17C) {
        mov = lbl_803CC170;
        if (mov == NULL || !(mov->state & 1)) {
            continue;
        }
        mov->decoding = 1;
        lbl_803CC19C = fn_800AF1A8(mov);
        switch (lbl_803CC19C) {
        case 2:
            OSPanic("movie.c", 0x27D, "sNp_MovDecodeThread()::ERR!! broken file.\n");
            mov->state = MOV_STATE_STOP;
            mov->decoding = 0;
            break;
        case 3:
            if (mov->flags & 2) {
                do {
                    mov->curFrame = MovClockFrame(mov);
                    if (lbl_803CC17C) {
                        goto exit;
                    }
                } while (mov->curFrame < mov->numFrames);
                MovResetFrames(mov);
                lbl_803CC1A0 = 0;
                if (!lbl_803CC181) {
                    fn_800A6E24(mov->file, lbl_803CC174, lbl_803CC178);
                } else {
                    fn_800AFC10();
                    lbl_803CC174 = lbl_803C7A00.start;
                }
                if (!fn_800AF9B4(mov, 0x44)) {
                    ok = FALSE;
                } else {
                    ok = MovStartBlock(mov);
                }
                if (!ok) {
                    mov->state = MOV_STATE_STOP;
                    lbl_803CC170 = NULL;
                }
            } else {
                do {
                    mov->curFrame = MovClockFrame(mov);
                    if (lbl_803CC17C) {
                        goto exit;
                    }
                } while (mov->curFrame < mov->numFrames);
                lbl_803CC170 = NULL;
                mov->state = MOV_STATE_STOP;
            }
            break;
        }
        mov->decoding = 0;
    }
exit:
    lbl_803CC17E = 0;
    return 0;
}

#define MOV_AVAIL() (*lbl_803CBAF8[lbl_803CC181])

// .text:0x800AF1A8 size:0x454
// One decode step. Returns 0 = done/continue, 1 = waiting for data, 2 = error, 3 = end of movie.
s32 fn_800AF1A8(MovPlayer* mov) {
    u32 size;
    u16 type;
    u16 format;
    u32 count;
    u8* end;
    s32 result;
    OSTime start;

    switch (lbl_803CC180) {
    case 0:
        if (mov->blockVideoDone == mov->blockVideoFrames && mov->blockAudioDone == mov->blockAudioFrames) {
            mov->frameBase += mov->blockVideoFrames;
            mov->blockIndex++;
            if (mov->blockIndex >= mov->numBlocks) {
                return 3;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (MOV_AVAIL() < 0x14) {
                mov->frameBase -= mov->blockVideoFrames;
                mov->blockIndex--;
                return 2;
            }
            if (!fn_800AF9B4(&mov->_060, 0x14)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            mov->blockAudioDone = 0;
            mov->blockVideoDone = 0;
        }
        lbl_803CC180++;
    case 1:
        if (MOV_AVAIL() < 8) {
            return 1;
        }
        if (!fn_800AF9B4(&mov->recType, 8)) {
            return 2;
        }
        if (mov->state == MOV_STATE_STOP) {
            return 0;
        }
        lbl_803CC180++;
    case 2:
        size = mov->recSize;
        type = mov->recType;
        format = mov->recFormat;
        if (MOV_AVAIL() < size) {
            return 1;
        }
        switch (type) {
        case 1:
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (!fn_800AF9B4(mov->videoBuf, 4)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            count = *(u32*)mov->videoBuf;
            if (!fn_800AF9B4(mov->videoBuf, size - 4)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            do {
                start = OSGetTime();
                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                result = fn_800AF5FC(mov, format, count);
            } while (result == 2);
            switch (result) {
            case 0:
                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                mov->decodeTime += OSTicksToMicroseconds(OSGetTime() - start);
                mov->decodedFrames++;
                break;
            case 1:
                return 1;
            }
            mov->blockVideoDone++;
            break;
        case 0:
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            if (!fn_800AF9B4(mov->audioBuf, 4)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            count = *(u32*)mov->audioBuf;
            if (!fn_800AF9B4(mov->audioBuf, size - 4)) {
                return 2;
            }
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            end = mov->audioWrite + count * 4;
            do {
                if (end >= mov->audioEnd) {
                    end -= mov->audioEnd - mov->audioRead;
                }
            } while (mov->audioWrite < mov->audioRead && end >= mov->audioRead);
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            fn_800DFDD4(mov->audioBuf, mov->audioWrite, mov->numChannels, format, count, mov->chans);
            end = mov->chans[mov->numChannels - 1].outPtr;
            if (mov->state == MOV_STATE_STOP) {
                return 0;
            }
            mov->audioWrite = end;
            mov->blockAudioDone++;
            break;
        default:
            return 2;
        }
        break;
    }
    lbl_803CC180 = 0;
    return 0;
}

// .text:0x800AF5FC size:0x3B8
// Decodes one video frame into a free slot of the frame queue.
// Returns 0 = decoded, 1 = unknown format, 2 = no free slot, 3 = frame is late / refs missing.
s32 fn_800AF5FC(MovPlayer* mov, s32 format, u32 frame) {
    u32 decodeFrames;
    u32 now;
    u32 margin;
    u8 i;
    u8 found;
    MovFrame* slot;

    if (mov->decodedFrames != 0) {
        decodeFrames = mov->decodeTime / mov->decodedFrames / mov->usecPerFrame;
    } else {
        decodeFrames = 0;
    }
    if (mov->flags & 1) {
        if (mov->samplesPlayed != 0) {
            now = mov->samplesPlayed * 1000000 / (mov->sampleRate * 4) / mov->usecPerFrame;
        } else {
            now = 0;
        }
    } else {
        now = 0;
        if (mov->startTime != 0) {
            now = OSTicksToMicroseconds(OSGetTime() - mov->startTime) / mov->usecPerFrame;
        }
    }
    margin = (now != 0) ? decodeFrames + 1 : 0;

    switch (format) {
    case 0x10:
    case 0x20:
        found = FALSE;
        for (i = 2; i < 6; i++) {
            slot = mov->frameQueue[i];
            if (slot->ready != 1 || now > slot->frame) {
                mov->frameQueue[i] = mov->frameQueue[0];
                mov->frameQueue[0] = mov->frameQueue[1];
                mov->frameQueue[1] = slot;
                found = TRUE;
                break;
            }
        }
        if (!found) {
            return 2;
        }
        mov->frameQueue[1]->ready = 0;
        if (now + margin > frame + mov->frameBase) {
            return 3;
        }
        if (format == 0x10) {
            fn_800E4FF4(&mov->video, mov->videoBuf, mov->frameQueue[1]->buf);
        } else {
            if (!mov->frameQueue[0]->ready) {
                return 3;
            }
            fn_800E591C(&mov->video, mov->videoBuf, mov->frameQueue[1]->buf, mov->frameQueue[0]->buf);
        }
        mov->frameQueue[1]->frame = frame + mov->frameBase;
        if (mov->state == MOV_STATE_STOP) {
            return 0;
        }
        mov->frameQueue[1]->ready = 1;
        return 0;
    case 0x30:
        if (!mov->frameQueue[0]->ready) {
            return 3;
        }
        if (!mov->frameQueue[1]->ready) {
            return 3;
        }
        if (now + margin > frame + mov->frameBase) {
            return 3;
        }
        for (i = 2; i < 6; i++) {
            slot = mov->frameQueue[i];
            if (slot->ready != 1 || now > slot->frame) {
                mov->frameQueue[i]->ready = 0;
                fn_800E5940(&mov->video, mov->videoBuf, mov->frameQueue[i]->buf, mov->frameQueue[0]->buf, mov->frameQueue[1]->buf);
                mov->frameQueue[i]->frame = frame + mov->frameBase;
                if (mov->state == MOV_STATE_STOP) {
                    return 0;
                }
                mov->frameQueue[i]->ready = 1;
                return 0;
            }
        }
        return 2;
    default:
        return 1;
    }
}

// .text:0x800AF9B4 size:0x23C
// Reads len bytes from the movie stream (DVD ring or ARAM-backed MRAM ring).
BOOL fn_800AF9B4(void* dst, u32 len) {
    u8* src;
    u8* wrap;
    u8* read;
    u8* write;
    u32 first;
    u32 blocks;
    s32 room;
    s32 left;
    BOOL intr;

    if (lbl_803CC1A0 + len > lbl_803CC1A4) {
        return FALSE;
    }
    while (MOV_AVAIL() < len) {
        if (!fn_800AFFB0() && lbl_803CC181) {
            fn_800AFD4C();
        } else if (!lbl_803CC181) {
            OSSleepThread(&lbl_803C7420.sleepQueue);
        }
        if (lbl_803CC17C) {
            return FALSE;
        }
        if (lbl_803CC170 != NULL && lbl_803CC170->state == MOV_STATE_STOP) {
            return FALSE;
        }
    }
    intr = OSDisableInterrupts();
    read = *lbl_803CBAE8[lbl_803CC181];
    write = *lbl_803CBAF0[lbl_803CC181];
    if (read < write) {
        src = read + (lbl_803CC1A0 & 0x1F);
        wrap = NULL;
        first = write - src;
    } else {
        src = read + (lbl_803CC1A0 & 0x1F);
        wrap = lbl_803CC174;
        first = lbl_803CC174 + lbl_803CC178 - src;
    }
    OSRestoreInterrupts(intr);
    if (len < first) {
        memcpy(dst, src, len);
    } else {
        memcpy(dst, src, first);
        memcpy((u8*)dst + first, wrap, len - first);
    }
    blocks = ((lbl_803CC1A0 + len) & ~0x1F) - (lbl_803CC1A0 & ~0x1F);
    if (blocks != 0) {
        if (lbl_803CC181) {
            fn_800AFFC0(blocks);
        } else {
            fn_800A6D10(blocks);
        }
        if (lbl_803CC181) {
            room = lbl_803C7A00.size - lbl_803C7A00.filled;
            left = lbl_803CC1AC - lbl_803C79D4.totalOut;
            if (room > 0) {
                if (left > room) {
                    fn_800B0008(room & ~0x1F);
                } else if (lbl_803CC1AC > lbl_803C79D4.totalOut) {
                    fn_800B0008(left);
                }
            }
            if (lbl_803C79D4.totalIn < lbl_803CC1AC) {
                fn_800B0134(blocks);
            }
        }
    }
    lbl_803CC1A0 += len;
    return TRUE;
}

// .text:0x800AFBF0 size:0x20
void fn_800AFBF0(void) {
    fn_800A63C8();
}

// Copies len bytes from the ARAM ring into the MRAM ring.
static inline BOOL MovFillFromAram(u32 len) {
    u32 first;
    u32 second;
    u8* wrap;

    len = OSRoundUp32B(len);
    if (lbl_803C7A00.filled >= lbl_803C7A00.size) {
        return TRUE;
    }
    if (lbl_803C7A00.writePtr + len > lbl_803C7A00.end) {
        first = lbl_803C7A00.end - lbl_803C7A00.writePtr;
        wrap = lbl_803C7A00.start;
        second = len - first;
    } else {
        first = len;
        wrap = NULL;
        second = 0;
    }
    fn_800B0230(lbl_803C7A00.writePtr, first);
    while (lbl_803C79D4.busy) {}
    if (second != 0) {
        fn_800B0230(wrap, second);
        while (lbl_803C79D4.busy) {}
    }
    if (lbl_803C7A00.writePtr + len < lbl_803C7A00.end) {
        lbl_803C7A00.writePtr += first;
    } else {
        lbl_803C7A00.writePtr = lbl_803C7A00.start + second;
    }
    lbl_803C7A00.filled += len;
    if (lbl_803C79D4.totalOut > lbl_803CC1AC) {
        memset(lbl_803C7A00.writePtr - (lbl_803C79D4.totalOut - lbl_803CC1AC), 0, lbl_803C79D4.totalOut - lbl_803CC1AC);
    }
    return TRUE;
}

// Copies len bytes from the DVD stream buffer into the ARAM ring.
static inline BOOL MovStoreToAram(u32 len) {
    u8* src;
    u8* wrap;
    u32 first;
    u32 second;
    BOOL intr;

    while (lbl_803C6CF8.streamAvail < len) {}
    intr = OSDisableInterrupts();
    src = lbl_803C6CF8.streamRead;
    if (src + len < lbl_803C7A00.dvdBufStart + lbl_803C7A00.dvdBufSize) {
        wrap = NULL;
        first = len;
        second = 0;
    } else {
        first = lbl_803C7A00.dvdBufStart + lbl_803C7A00.dvdBufSize - src;
        wrap = lbl_803C7A00.dvdBufStart;
        second = len - first;
    }
    OSRestoreInterrupts(intr);
    if (len >= first) {
        fn_800B03F4(src, len);
    } else {
        fn_800B03F4(src, first);
        while (lbl_803C79D4.busy) {}
        fn_800B03F4(wrap, second);
    }
    while (lbl_803C79D4.busy) {}
    if (len != 0) {
        fn_800A6D10(len);
    }
    return TRUE;
}

// .text:0x800AFC10 size:0x13C
// Rewinds both rings to the start of the ARAM copy and refills MRAM.
void fn_800AFC10(void) {
    lbl_803C79D4.writePos = lbl_803C79D4.readPos = lbl_803C79D4.start;
    lbl_803C79D4.totalOut = 0;
    lbl_803C7A00.writePtr = lbl_803C7A00.readPtr = lbl_803C7A00.start;
    lbl_803C7A00.filled = 0;
    lbl_803C7A00.consumed = 0;
    MovFillFromAram(lbl_803C7A00.size);
}

// .text:0x800AFD4C size:0x264
// Moves the next DVD chunk into ARAM; once the whole file is there, primes MRAM.
BOOL fn_800AFD4C(void) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 len;

    if (aram->full) {
        return TRUE;
    }
    if (aram->size > aram->totalIn + 0x4000) {
        len = 0x4000;
    } else {
        len = aram->size - aram->totalIn;
    }
    MovStoreToAram(len);
    if (lbl_803C79D4.totalIn >= aram->size) {
        MovFillFromAram(lbl_803C7A00.size);
        fn_800A6C80();
        while (lbl_803C6CF8._715 != 1) {}
        aram->full = TRUE;
        return TRUE;
    }
    return TRUE;
}

// fn_800AFFB0, size:0x10
u8 fn_800AFFB0(void) {
    return lbl_803C79D4.full;
}

// fn_800AFFC0, size:0x48
void fn_800AFFC0(u32 count) {
    MovMramRing* ring = &lbl_803C7A00;
    u8* position = ring->readPtr + count;
    ring->readPtr = position;
    if (position >= ring->end) {
        ring->readPtr = position - ring->size;
    }
    ring->filled -= count;
    ring->consumed += count;
}

// .text:0x800B0008 size:0x12C
BOOL fn_800B0008(u32 len) {
    return MovFillFromAram(len);
}

// .text:0x800B0134 size:0xFC
BOOL fn_800B0134(u32 len) {
    return MovStoreToAram(len);
}

// .text:0x800B0230 size:0x160
// Starts an ARAM -> MRAM transfer of len bytes from the ARAM read position.
void fn_800B0230(u8* dst, u32 len) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 first;
    u32 second;
    u32 endPos;

    if (len == 0) {
        return;
    }
    endPos = aram->readPos + len;
    if (endPos > aram->end) {
        first = aram->end - aram->readPos;
        second = len - first;
    } else {
        first = len;
        second = 0;
    }
    if (second != 0) {
        endPos = aram->start + second;
    }
    if ((aram->writePos > aram->readPos && endPos > aram->writePos) ||
        (aram->writePos < aram->readPos && endPos > aram->writePos && second != 0)) {
        aram->busy = 3;
        return;
    }
    aram->readLen = len;
    aram->busy = 2;
    DCInvalidateRange(dst, first);
    ARQPostRequest(&lbl_803C78C4[0], 0, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_HIGH, aram->readPos, (u32)dst, first, fn_800B0390);
    DCInvalidateRange(dst, first);
    if (second != 0) {
        while (aram->busy) {}
        aram->busy = 2;
        DCInvalidateRange(dst + first, second);
        ARQPostRequest(&lbl_803C78C4[1], 0, ARQ_TYPE_ARAM_TO_MRAM, ARQ_PRIORITY_HIGH, aram->start, (u32)(dst + first), second, fn_800B0390);
        DCInvalidateRange(dst + first, second);
    }
}

// .text:0x800B0390 size:0x64
void fn_800B0390(u32 request) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 pos = aram->readPos + aram->readLen;
    aram->readPos = pos;
    if (pos >= aram->end) {
        aram->readPos = pos - aram->size;
    }
    {
        MovAramRing* r = &lbl_803C79D4;
        r->used -= aram->readLen;
        r->totalOut += aram->readLen;
        r->busy = 0;
    }
}

// .text:0x800B03F4 size:0x18C
// Starts an MRAM -> ARAM transfer of len bytes to the ARAM write position.
void fn_800B03F4(u8* src, u32 len) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 first;
    u32 second;
    u32 endPos;

    if (aram->writePos + len > aram->end) {
        first = aram->end - aram->writePos;
        second = len - first;
    } else {
        first = len;
        second = 0;
    }
    if (second != 0) {
        endPos = aram->start + second;
    } else {
        endPos = aram->writePos + len;
    }
    if ((aram->writePos > aram->readPos && endPos > aram->readPos && second != 0) ||
        (aram->writePos < aram->readPos && endPos > aram->readPos)) {
        aram->busy = 3;
        return;
    }
    if (lbl_803C79D4.used > lbl_803C79D4.size) {
        for (;;) {}
    }
    lbl_803CC1A8++;
    aram->writeLen = len;
    aram->busy = 1;
    DCFlushRangeNoSync(src, first);
    ARQPostRequest(&lbl_803C7994[0], 0, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, (u32)src, aram->writePos, first, fn_800B0580);
    if (second != 0) {
        while (aram->busy) {}
        aram->busy = 1;
        DCFlushRangeNoSync(src + first, second);
        ARQPostRequest(&lbl_803C7994[1], 0, ARQ_TYPE_MRAM_TO_ARAM, ARQ_PRIORITY_HIGH, (u32)(src + first), aram->start, second, fn_800B0580);
    }
}

// .text:0x800B0580 size:0x64
void fn_800B0580(u32 request) {
    MovAramRing* aram = &lbl_803C79D4;
    u32 pos = aram->writePos + aram->writeLen;
    aram->writePos = pos;
    if (pos >= aram->end) {
        aram->writePos = pos - aram->size;
    }
    {
        MovAramRing* r = &lbl_803C79D4;
        r->totalIn += aram->writeLen;
        r->used += aram->writeLen;
        r->busy = 0;
    }
}

// .text:0x800B05E4 size:0x140
// Sets up the ARAM ring (aramSize, or all free ARAM when -1) and an MRAM ring of mramSize.
void fn_800B05E4(s32 aramSize, u32 mramSize) {
    MovAramRing* aram = &lbl_803C79D4;
    MovMramRing* mram = &lbl_803C7A00;

    lbl_803CC1A8 = 0;
    memset(aram, 0, sizeof(MovAramRing));
    if (aramSize == -1) {
        aram->size = (lbl_803CC1AC < data_803C6780) ? lbl_803CC1AC : data_803C6780;
    } else {
        aram->size = (lbl_803CC1AC < (u32)aramSize) ? lbl_803CC1AC : (u32)aramSize;
    }
    aram->size = OSRoundUp32B(aram->size);
    aram->start = fn_800A6418(aram->size);
    aram->writePos = aram->readPos = aram->start;
    aram->end = aram->start + aram->size;
    ARQSetChunkSize(0x1000);
    ARQFlushQueue();
    mramSize = OSRoundUp32B(mramSize);
    mram->dvdBufSize = lbl_803C6CF8.streamSize;
    mram->dvdBufStart = lbl_803C6CF8.streamEnd - lbl_803C6CF8.streamSize;
    mram->dvdBufSize = lbl_803C6CF8.streamSize;
    mram->start = _OSAllocFromHeap(0x20, mramSize);
    mram->end = mram->start + mramSize;
    mram->writePtr = mram->readPtr = mram->start;
    mram->size = mramSize;
    mram->filled = 0;
    mram->consumed = 0;
}
