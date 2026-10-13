// Force-included into every game translation unit for the PC build
// (adapted from strikers' port/include/port/prelude.h; the MSSB game is C).
#pragma once

#ifndef TARGET_PC
#define TARGET_PC 1
#endif

#include <stdint.h>

// Hand-computed PC layouts (views with numeric offsets for 64-bit pointers)
// apply to LP64 hosts only; wasm32 keeps the GameCube (ILP32) layout.
#if __SIZEOF_POINTER__ == 8
#define PORT_LP64 1
#endif

// Metrowerks / PowerPC intrinsics. Defined before any system header: the
// decomp's math.h (port/include/math.h) uses them.
// (functions, not macros: game sources also declare some of them, and the
// SDK headers declare __frsqrte.)
static inline double port_fabs(double x) { return __builtin_fabs(x); }
static inline float port_fabsf(float x) { return __builtin_fabsf(x); }
static inline double port_fnabs(double x) { return -__builtin_fabs(x); }
static inline double port_frsqrte(double x) { return 1.0 / __builtin_sqrt(x); }
static inline float port_fres(float x) { return 1.0f / x; }
static inline double port_fsel(double a, double b, double c) { return a >= 0 ? b : c; }
#define __fabs port_fabs
#define __fabsf port_fabsf
#define __fnabs port_fnabs
#define __frsqrte port_frsqrte
#define __fres port_fres
#define __fsel port_fsel
static inline int port_abs(int x) { return x < 0 ? -x : x; }
#define __abs port_abs
// rlwinm: rotate left by sh, keep bits mb..me (big-endian bit numbering).
static inline uint32_t port_rlwinm(uint32_t x, int sh, int mb, int me)
{
    uint32_t rot = (x << (sh & 31)) | (x >> ((32 - sh) & 31));
    uint32_t mask = (mb <= me) ? ((0xFFFFFFFFu >> mb) & (0xFFFFFFFFu << (31 - me)))
                               : ((0xFFFFFFFFu >> mb) | (0xFFFFFFFFu << (31 - me)));
    return rot & mask;
}
#define __rlwinm port_rlwinm

#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <alloca.h>
#include <dolphin/types.h>

#define __alloca(n) __builtin_alloca(n)
typedef va_list __va_list;

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <strings.h>

#define __float_max (FLT_MAX)
#define __float_epsilon (FLT_EPSILON)

#define __cntlzw(x) ((x) == 0 ? 32 : __builtin_clz((unsigned int)(x)))
#define __rlwimi(a, b, sh, mb, me) port_rlwimi((a), (b), (sh), (mb), (me))
#define __sync()
#define __isync()
#define __eieio()
#define __dcbz(p, off) memset((char*)(p) + (off), 0, 32)
#define __dcbf(p, off)
#define __dcbst(p, off)
#define __dcbi(p, off)
#define __icbi(p, off)
#define strcmpi strcasecmp
#define stricmp strcasecmp

// The game links against MSL's rand()/srand() (15-bit LCG); use the same
// generator on PC (port/src/msl.c) so RAND_MAX-based math is unchanged.
int msl_rand(void);
void msl_srand(unsigned int seed);
#define rand msl_rand
#define srand msl_srand

// rlwimi: rotate b left by sh and insert it into a under the mask mb..me.
static inline uint32_t port_rlwimi(uint32_t a, uint32_t b, int sh, int mb, int me)
{
    uint32_t rot = (b << (sh & 31)) | (b >> ((32 - sh) & 31));
    uint32_t mask = (mb <= me) ? ((0xFFFFFFFFu >> mb) & (0xFFFFFFFFu << (31 - me)))
                               : ((0xFFFFFFFFu >> mb) | (0xFFFFFFFFu << (31 - me)));
    return (a & ~mask) | (rot & mask);
}

// The SDK is aurora's. The decomp's include/Dolphin headers forward here under
// TARGET_PC; on case-insensitive filesystems "Dolphin/x.h" may even resolve
// to aurora's header directly, so include the whole SDK up front.
#include <dolphin/types.h>
#include <dolphin/os.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <dolphin/vi.h>
#include <dolphin/pad.h>
#include <dolphin/dvd.h>
#include <dolphin/card.h>
#include <dolphin/ar.h>
#include <dolphin/arq.h>
#include <dolphin/ai.h>
#include <dolphin/dsp.h>
#include <dolphin/si.h>
#include <dolphin/exi.h>
#include <dolphin/base/PPCArch.h>
#include "port/sdk_compat.h"

// DVD callbacks run under the port's interrupt lock (port/src/dvd_irq.c).
BOOL port_DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio);
#define DVDReadAsyncPrio port_DVDReadAsyncPrio
// DVD audio streaming (music) is emulated in port/src/audio/dtk.cpp.
BOOL port_DVDPrepareStreamAsync(DVDFileInfo* fileInfo, u32 length, u32 offset, DVDCallback callback);
BOOL port_DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL port_DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL port_DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback);
BOOL port_DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback);
#define DVDPrepareStreamAsync port_DVDPrepareStreamAsync
#define DVDCancelStreamAsync port_DVDCancelStreamAsync
#define DVDStopStreamAtEndAsync port_DVDStopStreamAtEndAsync
#define DVDGetStreamErrorStatusAsync port_DVDGetStreamErrorStatusAsync
#define DVDGetStreamPlayAddrAsync port_DVDGetStreamPlayAddrAsync
// aurora's GCI-folder cards have serial number 0 (port/src/sdk_stubs.c).
s32 port_CARDGetSerialNo(s32 chan, u64* serialNo);
#define CARDGetSerialNo port_CARDGetSerialNo
s32 port_CARDUnmount(s32 chan);
#define CARDUnmount port_CARDUnmount

#include "port/endian.h"
#include "port/ptr32.h"
#include "port/blob.h"
#include "port/formats.h"

// MSSB_TRACE_GAME: print a tagged state value when it changes (port/src/trace.c).
void port_trace_value(const char* tag, int value);

// Pointers kept in 32-bit integers (fields of disc formats relocated in place,
// handles, callback arguments): stored as offsets into the game heap, the same
// encoding as PTR32 (port/ptr32.h). Encoding a pointer outside the game heap
// aborts, which pinpoints the spots needing a real 64-bit fix. The decomp
// spells these PTR_TO_U32/U32_TO_PTR (include/types.h).
#define PORT_PTR_TO_U32(p) port_ptr32_encode((const void*)(p))
#define PORT_U32_TO_PTR(v) port_ptr32_decode((uint32_t)(v))

#include "port/module_sections.h"
