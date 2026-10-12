// Force-included into every game translation unit for the PC build
// (adapted from strikers' port/include/port/prelude.h; the MSSB game is C).
#pragma once

#ifndef TARGET_PC
#define TARGET_PC 1
#endif

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

// Metrowerks / PowerPC intrinsics
#define __fabs(x) fabs(x)
#define __fabsf(x) fabsf(x)
#define __fnabs(x) (-fabs(x))
#define __frsqrte(x) (1.0 / sqrt(x))
#define __fres(x) (1.0f / (x))
#define __fsel(a, b, c) ((a) >= 0 ? (b) : (c))
#define __float_nan (__builtin_nanf(""))
#define __float_huge (__builtin_huge_valf())
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
// generator on PC (port/src/msl_rand.c) so RAND_MAX-based math is unchanged.
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

#include "port/endian.h"
#include "port/ptr32.h"

// Pointer <-> 32-bit conversions in code that still assumes 32-bit pointers
// (file formats with in-place relocation, serialized pointers). These abort if
// the pointer doesn't fit, which pinpoints the spots needing a real 64-bit fix.
void port_ptr_trunc_fail(const char* file, int line);
static inline uint32_t port_ptr_to_u32(const void* p, const char* file, int line)
{
    uintptr_t v = (uintptr_t)p;
    if (v > 0xFFFFFFFFu)
        port_ptr_trunc_fail(file, line);
    return (uint32_t)v;
}
#define PORT_PTR_TO_U32(p) port_ptr_to_u32((const void*)(p), __FILE__, __LINE__)
