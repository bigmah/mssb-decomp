// Small runtime hooks used by the prelude's helpers.
#include <stdio.h>
#include <stdlib.h>

void port_ptr32_fail(const void* p)
{
    fprintf(stderr, "FATAL: pointer %p is outside the game heap and can't be stored in 32 bits\n", p);
    abort();
}

// Pointers outside the game heap kept in PTR32 fields (port/ptr32.h): each
// distinct address gets a slot; the 32-bit value is PORT_PTR32_EXT_BASE + slot.
#include <pthread.h>
#include <stdint.h>

#define EXT_BASE 0xE0000000u
#define EXT_MAX 65536u
#define EXT_HASH (EXT_MAX * 2)

static const void* s_ext[EXT_MAX];
static uint32_t s_extCount;
static uint32_t s_extHash[EXT_HASH]; // slot + 1, 0 = empty
static pthread_mutex_t s_extLock = PTHREAD_MUTEX_INITIALIZER;

uint32_t port_ptr32_encode_ext(const void* p)
{
    uintptr_t v = (uintptr_t)p;
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
    return EXT_BASE + slot;
}

void* port_ptr32_decode_ext(uint32_t raw)
{
    uint32_t slot = raw - EXT_BASE;
    if (slot >= s_extCount)
    {
        fprintf(stderr, "FATAL: bad 32-bit pointer value 0x%08x\n", raw);
        abort();
    }
    return (void*)s_ext[slot];
}
