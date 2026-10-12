// SDK pieces the game links against that aurora doesn't provide. Most are
// hardware queries/controls with no PC equivalent.

#include <dolphin/types.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define WEAK __attribute__((weak))

// OS ------------------------------------------------------------------------
// (aurora's OSReport.cpp is compiled out.)
void OSVReport(const char* msg, va_list list)
{
    vfprintf(stdout, msg, list);
    fflush(stdout);
}

void OSReport(const char* msg, ...)
{
    va_list args;
    va_start(args, msg);
    OSVReport(msg, args);
    va_end(args);
}

void OSPanic(const char* file, int line, const char* msg, ...)
{
    va_list args;
    fprintf(stderr, "PANIC %s:%d: ", file, line);
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "\n");
    abort();
}

// PPC -------------------------------------------------------------------------
void PPCSync(void) { }
u32 PPCMfhid2(void) { return 0; }
void PPCMthid2(u32 val) { (void)val; }

// PAD / SI --------------------------------------------------------------------
typedef void (*PADSamplingCallback)(void);
static PADSamplingCallback s_padSamplingCb = NULL;

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback cb)
{
    PADSamplingCallback old = s_padSamplingCb;
    s_padSamplingCb = cb;
    return old;
}

// Called once per frame from the retrace emulation (vi_frame.cpp).
void port_pad_sample(void)
{
    if (s_padSamplingCb)
        s_padSamplingCb();
}

void SISetSamplingRate(u32 msec) { (void)msec; }

// AI ----------------------------------------------------------------------------
// DMA and sample-rate calls are implemented by the audio backend (weak
// fallbacks here). Disc audio streaming (DVD streaming through AI) has no PC
// equivalent yet: the stream calls are no-ops.
typedef void (*AIDCallback)(void);
typedef void (*AISCallback)(u32 count);

WEAK void AIInit(u8* stack) { (void)stack; }
WEAK void AIInitDMA(u32 start_addr, u32 length) { (void)start_addr; (void)length; }
WEAK AIDCallback AIRegisterDMACallback(AIDCallback callback) { (void)callback; return NULL; }
WEAK u32 AIGetDMAStartAddr(void) { return 0; }
WEAK u32 AIGetDSPSampleRate(void) { return 1; } // AI_SAMPLERATE_48KHZ
WEAK void port_audio_shutdown(void) { }

static AISCallback s_streamCb = NULL;
AISCallback AIRegisterStreamCallback(AISCallback callback)
{
    AISCallback old = s_streamCb;
    s_streamCb = callback;
    return old;
}
void AIResetStreamSampleCount(void) { }
void AISetStreamTrigger(u32 trigger) { (void)trigger; }
void AISetStreamPlayState(u32 state) { (void)state; }
void AISetStreamVolLeft(u8 vol) { (void)vol; }
void AISetStreamVolRight(u8 vol) { (void)vol; }

// ARQ ---------------------------------------------------------------------------
// aurora's ARQ copies synchronously: nothing is ever queued.
void ARQFlushQueue(void) { }
void ARQRemoveOwnerRequest(u32 owner) { (void)owner; }
static u32 s_arqChunkSize = 0x1000;
void ARQSetChunkSize(u32 size) { s_arqChunkSize = (size + 31) & ~31u; }
u32 ARQGetChunkSize(void) { return s_arqChunkSize; }
// ARAM below 0x4000 is reserved for the OS/DSP on hardware (MusyX asks).
u32 ARGetBaseAddress(void) { return 0x4000; }

// GX ----------------------------------------------------------------------------
static OSThread* s_gxThread = NULL;
OSThread* GXSetCurrentGXThread(void)
{
    OSThread* old = s_gxThread;
    s_gxThread = OSGetCurrentThread();
    return old;
}
OSThread* GXGetCurrentGXThread(void) { return s_gxThread; }

void GXSetScissorBoxOffset(s32 xOffset, s32 yOffset) { (void)xOffset; (void)yOffset; }

// Draw sync tokens: aurora executes commands in order, so the last token set
// has always been reached.
static u16 s_drawSyncToken = 0;
void GXSetDrawSync(u16 token) { s_drawSyncToken = token; }
u16 GXReadDrawSync(void) { return s_drawSyncToken; }

// Performance counters read as zero.
void GXSetGPMetric(GXPerf0 perf0, GXPerf1 perf1) { (void)perf0; (void)perf1; }
void GXClearGPMetric(void) { }
void GXReadGPMetric(u32* count0, u32* count1)
{
    if (count0)
        *count0 = 0;
    if (count1)
        *count1 = 0;
}
u32 GXReadGP0Metric(void) { return 0; }
u32 GXReadGP1Metric(void) { return 0; }
void GXReadPixMetric(u32* topIn, u32* topOut, u32* bottomIn, u32* bottomOut, u32* clearIn, u32* copyClocks)
{
    u32* outs[] = {topIn, topOut, bottomIn, bottomOut, clearIn, copyClocks};
    for (int i = 0; i < 6; i++)
        if (outs[i])
            *outs[i] = 0;
}
void GXClearPixMetric(void) { }
void GXSetVCacheMetric(GXVCachePerf attr) { (void)attr; }
void GXReadVCacheMetric(u32* check, u32* miss, u32* stall)
{
    if (check)
        *check = 0;
    if (miss)
        *miss = 0;
    if (stall)
        *stall = 0;
}
void GXClearVCacheMetric(void) { }
