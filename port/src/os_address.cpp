// GameCube cached/uncached/physical address conversions. On PC a "physical"
// address is a game-heap offset (the heap is 4GB-aligned, see game_heap.h), so
// code that stores 32-bit physical addresses (MusyX, DSP command lists, AI DMA)
// round-trips through these. Defining all of them here keeps aurora's
// MEM1-relative versions from being linked.
#include <dolphin/os.h>

#include "port/game_heap.h"

#include <cstdio>

namespace {
// Only game-heap pointers survive the round trip; anything else (statics,
// stack, host allocations) would come back as a different address.
u32 to_phys(void* p)
{
    if (p != nullptr && !port_heap_contains(p))
    {
        static int s_warned = 0;
        if (s_warned++ < 8)
            fprintf(stderr, "[os] physical address requested for non-heap pointer %p\n", p);
    }
    return port_heap_phys(p);
}
} // namespace

extern "C" {
void* OSPhysicalToCached(u32 paddr) { return port_heap_virt(paddr); }
void* OSPhysicalToUncached(u32 paddr) { return port_heap_virt(paddr); }
u32 OSCachedToPhysical(void* caddr) { return to_phys(caddr); }
u32 OSUncachedToPhysical(void* ucaddr) { return to_phys(ucaddr); }
void* OSCachedToUncached(void* caddr) { return caddr; }
void* OSUncachedToCached(void* ucaddr) { return ucaddr; }
}
