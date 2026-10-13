// Game heap for web builds. wasm32 pointers are 32-bit, so every pointer is
// already its own "physical address": the heap base is 0 and the regular
// allocator backs everything (see port/game_heap.h for the native version).
#include "port/game_heap.h"

#include <emscripten/heap.h>

#include <cstdio>
#include <cstdlib>

extern "C" {

void* port_heap_alloc(size_t size, size_t alignment)
{
    if (size == 0)
        size = 1;
    if (alignment <= 16)
        return malloc(size);
    return aligned_alloc(alignment, (size + alignment - 1) & ~(alignment - 1));
}

void port_heap_free(void* p) { free(p); }

uintptr_t port_heap_base(void) { return 0; }

int port_heap_contains(const void* p) { return p != nullptr; }

int port_heap_pointer_like(uintptr_t v)
{
    return (v & 3) == 0 && v >= 0x10000 && v + 16 <= emscripten_get_heap_size();
}

void port_heap_report_freed(const void* p) { (void)p; }

} // extern "C"
