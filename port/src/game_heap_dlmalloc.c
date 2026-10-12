// dlmalloc 2.8.6 configured to allocate from the game heap region
// (port/src/game_heap.cpp) via a private sbrk.
#include <stddef.h>

void* port_heap_sbrk(ptrdiff_t increment);

#define USE_DL_PREFIX 1
#define USE_LOCKS 1
#define HAVE_MMAP 0
#define HAVE_MREMAP 0
#define HAVE_MORECORE 1
#define MORECORE port_heap_sbrk
#define MORECORE_CONTIGUOUS 1
#define MORECORE_CANNOT_TRIM 1
#define MALLOC_ALIGNMENT 16
#define DEFAULT_GRANULARITY (2 * 1024 * 1024)
#define ABORT_ON_ASSERT_FAILURE 1
#define NO_MALLOC_STATS 0

#include "../third_party/dlmalloc/dlmalloc.c"
