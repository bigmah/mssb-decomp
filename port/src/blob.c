// Size registry for loaded files (port/include/port/blob.h). Open addressing
// keyed by address; an entry is overwritten when the same address is loaded
// again, so stale entries for freed buffers are harmless.
#include "port/blob.h"

#include <pthread.h>

#define BLOB_SLOTS 4096

static struct {
    const void* p;
    uint32_t size;
} s_blobs[BLOB_SLOTS];
static pthread_mutex_t s_lock = PTHREAD_MUTEX_INITIALIZER;

static unsigned slot_of(const void* p)
{
    uintptr_t v = (uintptr_t)p >> 5;
    return (unsigned)((v ^ (v >> 13)) % BLOB_SLOTS);
}

void port_blob_note(const void* p, uint32_t size)
{
    pthread_mutex_lock(&s_lock);
    unsigned i = slot_of(p);
    for (unsigned n = 0; n < BLOB_SLOTS; n++, i = (i + 1) % BLOB_SLOTS)
    {
        if (s_blobs[i].p == p || s_blobs[i].p == NULL || n == BLOB_SLOTS - 1)
        {
            s_blobs[i].p = p;
            s_blobs[i].size = size;
            break;
        }
    }
    pthread_mutex_unlock(&s_lock);
}

uint32_t port_blob_size(const void* p)
{
    uint32_t size = 0;
    pthread_mutex_lock(&s_lock);
    unsigned i = slot_of(p);
    for (unsigned n = 0; n < BLOB_SLOTS && s_blobs[i].p != NULL; n++, i = (i + 1) % BLOB_SLOTS)
    {
        if (s_blobs[i].p == p)
        {
            size = s_blobs[i].size;
            break;
        }
    }
    pthread_mutex_unlock(&s_lock);
    return size;
}
