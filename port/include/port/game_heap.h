// The game heap: every engine and C++ allocation comes from one reserved 4GB
// address range, so any game pointer can be stored as a 32-bit offset from
// port_heap_base(). Disc formats that relocate 32-bit pointers in place rely on
// this (see port/ptr32.h).
#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void* port_heap_alloc(size_t size, size_t alignment);
void port_heap_free(void* p);
uintptr_t port_heap_base(void);
int port_heap_contains(const void* p);

// Whether v could point at a live game object, for 32-bit handles that hold
// either a hash or a pointer (callers then check a type tag). Natively game
// pointers are above 4GB; on wasm32 they're any in-bounds address.
int port_heap_pointer_like(uintptr_t v);

// Heap debug mode (MSSB_HEAP_DEBUG=1): report who freed the block containing p.
void port_heap_report_freed(const void* p);

// The heap base is 4GB-aligned: a game pointer's low 32 bits are its heap
// offset. These convert between pointers and 32-bit "physical" addresses.
static inline uint32_t port_heap_phys(const void* p) { return (uint32_t)(uintptr_t)p; }
static inline void* port_heap_virt(uint32_t phys) { return phys ? (void*)(port_heap_base() + phys) : NULL; }

#ifdef __cplusplus
}
#endif
