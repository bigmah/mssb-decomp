// Small runtime hooks used by the prelude's helpers.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void port_ptr32_fail(const void* p)
{
    fprintf(stderr, "FATAL: pointer %p is outside the game heap and can't be stored in 32 bits\n", p);
    abort();
}

// Pointers outside the game heap kept in PTR32 fields (port/ptr32.h).
// - Inside the executable image (static data, functions): EXT_BASE + the
//   offset from the image start. Stable across runs of one build, so such
//   values may be saved (memory card data holds pointers to static tables
//   and functions, e.g. MenuCtx).
// - Anything else: each distinct address gets a slot; the value is
//   EXT_SLOTS + slot (valid for this run only).
#include <pthread.h>
#include <stdint.h>

#define EXT_BASE 0xE0000000u
#define EXT_SLOTS 0xFE000000u
#define EXT_IMAGE_MAX (EXT_SLOTS - EXT_BASE)

#if defined(__APPLE__) && defined(__LP64__)
#include <mach-o/loader.h>
extern const struct mach_header_64 __dso_handle;

static uintptr_t s_imageBase, s_imageEnd;

static void image_range(void)
{
    if (s_imageEnd != 0)
        return;
    const struct mach_header_64* h = &__dso_handle;
    const struct load_command* lc = (const struct load_command*)(h + 1);
    uint64_t textVm = 0, end = 0;
    for (uint32_t i = 0; i < h->ncmds; i++)
    {
        if (lc->cmd == LC_SEGMENT_64)
        {
            const struct segment_command_64* seg = (const struct segment_command_64*)lc;
            if (seg->filesize != 0 || seg->vmsize != 0)
            {
                if (strcmp(seg->segname, "__TEXT") == 0)
                    textVm = seg->vmaddr;
                if (strcmp(seg->segname, "__PAGEZERO") != 0 && seg->vmaddr + seg->vmsize > end)
                    end = seg->vmaddr + seg->vmsize;
            }
        }
        lc = (const struct load_command*)((const char*)lc + lc->cmdsize);
    }
    s_imageBase = (uintptr_t)h;
    s_imageEnd = s_imageBase + (uintptr_t)(end - textVm);
}
#else
static uintptr_t s_imageBase, s_imageEnd;
static void image_range(void) {}
#endif
#define EXT_MAX 65536u
#define EXT_HASH (EXT_MAX * 2)

static const void* s_ext[EXT_MAX];
static uint32_t s_extCount;
static uint32_t s_extHash[EXT_HASH]; // slot + 1, 0 = empty
static pthread_mutex_t s_extLock = PTHREAD_MUTEX_INITIALIZER;

uint32_t port_ptr32_encode_ext(const void* p)
{
    uintptr_t v = (uintptr_t)p;
    image_range();
    if (v >= s_imageBase && v < s_imageEnd && v - s_imageBase < EXT_IMAGE_MAX)
        return EXT_BASE + (uint32_t)(v - s_imageBase);
    uint32_t h = (uint32_t)((v >> 3) ^ (v >> 19)) % EXT_HASH;
    uint32_t slot;
    pthread_mutex_lock(&s_extLock);
    for (;;)
    {
        uint32_t e = s_extHash[h];
        if (e == 0)
        {
            if (s_extCount == EXT_MAX)
            {
                pthread_mutex_unlock(&s_extLock);
                port_ptr32_fail(p);
            }
            slot = s_extCount++;
            s_ext[slot] = p;
            s_extHash[h] = slot + 1;
            break;
        }
        if (s_ext[e - 1] == p)
        {
            slot = e - 1;
            break;
        }
        h = (h + 1) % EXT_HASH;
    }
    pthread_mutex_unlock(&s_extLock);
    return EXT_SLOTS + slot;
}

void* port_ptr32_decode_ext(uint32_t raw)
{
    if (raw < EXT_SLOTS)
    {
        image_range();
        return (void*)(s_imageBase + (raw - EXT_BASE));
    }
    uint32_t slot = raw - EXT_SLOTS;
    if (slot >= s_extCount)
    {
        fprintf(stderr, "FATAL: bad 32-bit pointer value 0x%08x\n", raw);
        abort();
    }
    return (void*)s_ext[slot];
}
