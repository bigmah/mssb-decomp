// Big-endian helpers for reading GameCube data on little-endian hosts (C).
// Disc data is big-endian: swap scalars exactly once, right where the data is
// loaded. Bytes and strings need no swapping; GX texture data and display
// lists stay big-endian.
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static inline uint16_t be16(uint16_t v) { return __builtin_bswap16(v); }
static inline uint32_t be32(uint32_t v) { return __builtin_bswap32(v); }
static inline uint64_t be64(uint64_t v) { return __builtin_bswap64(v); }
static inline int16_t be16s(int16_t v) { return (int16_t)__builtin_bswap16((uint16_t)v); }
static inline int32_t be32s(int32_t v) { return (int32_t)__builtin_bswap32((uint32_t)v); }
static inline float bef(float v)
{
    uint32_t u;
    memcpy(&u, &v, 4);
    u = __builtin_bswap32(u);
    memcpy(&v, &u, 4);
    return v;
}

// In-place swaps for raw buffers loaded from disc.
static inline void swap16_inplace(void* p)
{
    uint16_t v;
    memcpy(&v, p, 2);
    v = __builtin_bswap16(v);
    memcpy(p, &v, 2);
}
static inline void swap32_inplace(void* p)
{
    uint32_t v;
    memcpy(&v, p, 4);
    v = __builtin_bswap32(v);
    memcpy(p, &v, 4);
}
static inline void swap32_array(void* p, size_t count)
{
    uint32_t* w = (uint32_t*)p;
    for (size_t i = 0; i < count; i++)
        w[i] = __builtin_bswap32(w[i]);
}
static inline void swap16_array(void* p, size_t count)
{
    uint16_t* w = (uint16_t*)p;
    for (size_t i = 0; i < count; i++)
        w[i] = __builtin_bswap16(w[i]);
}

// Reads of possibly unaligned big-endian values.
static inline uint32_t read_be32(const void* p)
{
    uint32_t v;
    memcpy(&v, p, 4);
    return __builtin_bswap32(v);
}
static inline uint16_t read_be16(const void* p)
{
    uint16_t v;
    memcpy(&v, p, 2);
    return __builtin_bswap16(v);
}
static inline float read_bef(const void* p)
{
    uint32_t v = read_be32(p);
    float f;
    memcpy(&f, &v, 4);
    return f;
}
