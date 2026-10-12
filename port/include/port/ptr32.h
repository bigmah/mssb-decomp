// 32-bit pointers for structs that keep their GameCube (disc) layout (C).
//
// The game is C, so strikers' Ptr32<T> template becomes a plain u32 holding an
// offset from the game heap base (port/game_heap.h); 0 means null. Every game
// allocation lives in the game heap, so any pointer the game stores fits.
//
//   PTR32(T) field;                       // u32 on PC, T* on GameCube
//   T* p = PTR32_GET(T, s->field);
//   PTR32_SET(s->field, p);
//
// Runtime-only structs should use real pointers instead (layout may change).
#pragma once

#include "port/game_heap.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void port_ptr32_fail(const void* p);
#ifdef __cplusplus
}
#endif

static inline uint32_t port_ptr32_encode(const void* p)
{
    if (p == 0)
        return 0;
    if (!port_heap_contains(p))
        port_ptr32_fail(p);
    return (uint32_t)((uintptr_t)p - port_heap_base());
}

static inline void* port_ptr32_decode(uint32_t raw)
{
    return raw == 0 ? 0 : (void*)(port_heap_base() + raw);
}

#define PTR32(T) uint32_t
#define PTR32_GET(T, field) ((T*)port_ptr32_decode(field))
#define PTR32_SET(field, p) ((field) = port_ptr32_encode(p))
