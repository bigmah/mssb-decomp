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

// 32-bit values from PORT_PTR32_EXT_BASE up index a table of pointers outside
// the game heap (static data such as built-in texture images); the heap never
// grows that far (port/src/game_heap.cpp).
#define PORT_PTR32_EXT_BASE 0xE0000000u

#ifdef __cplusplus
extern "C" {
#endif
void port_ptr32_fail(const void* p);
uint32_t port_ptr32_encode_ext(const void* p);
void* port_ptr32_decode_ext(uint32_t raw);
#ifdef __cplusplus
}
#endif

static inline uint32_t port_ptr32_encode(const void* p)
{
    if (p == 0)
        return 0;
    if (!port_heap_contains(p))
        return port_ptr32_encode_ext(p);
    return (uint32_t)((uintptr_t)p - port_heap_base());
}

static inline void* port_ptr32_decode(uint32_t raw)
{
    if (raw == 0)
        return 0;
    if (raw >= PORT_PTR32_EXT_BASE)
        return port_ptr32_decode_ext(raw);
    return (void*)(port_heap_base() + raw);
}

#define PTR32(T) uint32_t
#define PTR32_GET(T, field) ((T*)port_ptr32_decode(field))
#define PTR32_SET(field, p) ((field) = port_ptr32_encode(p))
