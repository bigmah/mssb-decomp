// DVD completion callbacks run in interrupt context on the GameCube, so the
// game guards the state they touch with OSDisableInterrupts. aurora calls
// them on its DVD worker thread: wrap them in the port's interrupt lock
// (port_interrupt_enter/leave) so they never race game code.
// The prelude maps DVDReadAsyncPrio to port_DVDReadAsyncPrio for game code.
#include <dolphin/dvd.h>

#include <pthread.h>

void port_interrupt_enter(void);
void port_interrupt_leave(void);

#define SLOTS 32

static struct {
    DVDFileInfo* fileInfo;
    DVDCallback callback;
} s_slots[SLOTS];
static pthread_mutex_t s_lock = PTHREAD_MUTEX_INITIALIZER;

static void set_callback(DVDFileInfo* fileInfo, DVDCallback callback)
{
    int free = -1;
    pthread_mutex_lock(&s_lock);
    for (int i = 0; i < SLOTS; i++)
    {
        if (s_slots[i].fileInfo == fileInfo)
        {
            s_slots[i].callback = callback;
            pthread_mutex_unlock(&s_lock);
            return;
        }
        if (free < 0 && s_slots[i].fileInfo == NULL)
            free = i;
    }
    if (free >= 0)
    {
        s_slots[free].fileInfo = fileInfo;
        s_slots[free].callback = callback;
    }
    pthread_mutex_unlock(&s_lock);
}

static DVDCallback get_callback(DVDFileInfo* fileInfo)
{
    DVDCallback callback = NULL;
    pthread_mutex_lock(&s_lock);
    for (int i = 0; i < SLOTS; i++)
    {
        if (s_slots[i].fileInfo == fileInfo)
        {
            callback = s_slots[i].callback;
            break;
        }
    }
    pthread_mutex_unlock(&s_lock);
    return callback;
}

#ifdef __EMSCRIPTEN__
// Web builds: aurora runs DVD commands synchronously as they're issued, so the
// completion would arrive inside DVDReadAsyncPrio. Queue it as an interrupt
// instead (delivered when the game enables interrupts or waits), like the
// GameCube's DVD interrupt.
#include <stdlib.h>
void port_raise_interrupt(void (*fn)(void*), void* arg);

typedef struct {
    DVDCallback callback;
    s32 result;
    DVDFileInfo* fileInfo;
} PendingDvd;

static void deliver(void* arg)
{
    PendingDvd p = *(PendingDvd*)arg;
    free(arg);
    p.callback(p.result, p.fileInfo);
}

static void trampoline(s32 result, DVDFileInfo* fileInfo)
{
    DVDCallback callback = get_callback(fileInfo);
    if (callback == NULL)
        return;
    PendingDvd* p = (PendingDvd*)malloc(sizeof(PendingDvd));
    p->callback = callback;
    p->result = result;
    p->fileInfo = fileInfo;
    port_raise_interrupt(deliver, p);
}
#else
static void trampoline(s32 result, DVDFileInfo* fileInfo)
{
    DVDCallback callback = get_callback(fileInfo);
    if (callback == NULL)
        return;
    port_interrupt_enter();
    callback(result, fileInfo);
    port_interrupt_leave();
}
#endif

#ifdef __EMSCRIPTEN__
// Web builds: the disc comes over the network, and a read that misses the
// page's cache would suspend the whole game (every thread, and the frame
// loop) for the round trip. Asynchronous reads instead wait here, in issue
// order, until the page has their bytes (port_web_disc_ready starts the
// fetch); the game keeps running, as it does while a GameCube drive seeks.
// Their command block reads as busy meanwhile.
int64_t aurora_dvd_file_disc_offset(const DVDFileInfo* fileInfo);
int port_web_disc_ready(uint64_t offset, uint64_t len);

typedef struct {
    DVDFileInfo* fileInfo;
    void* addr;
    s32 length;
    s32 offset;
    DVDCallback callback;
    s32 prio;
} DeferredRead;

#define MAX_DEFERRED 64
static DeferredRead s_deferred[MAX_DEFERRED];
static int s_deferredCount = 0;

static int read_ready(const DeferredRead* r)
{
    int64_t base = aurora_dvd_file_disc_offset(r->fileInfo);
    if (base < 0 || r->length <= 0)
        return 1;
    return port_web_disc_ready((uint64_t)base + (uint64_t)r->offset, (uint64_t)r->length);
}

static void issue(const DeferredRead* r)
{
    set_callback(r->fileInfo, r->callback);
    DVDReadAsyncPrio(r->fileInfo, r->addr, r->length, r->offset, r->callback != NULL ? trampoline : NULL, r->prio);
}

static void remove_deferred(int i)
{
    for (; i + 1 < s_deferredCount; i++)
        s_deferred[i] = s_deferred[i + 1];
    s_deferredCount--;
}

static int find_deferred(const DVDCommandBlock* block)
{
    for (int i = 0; i < s_deferredCount; i++)
        if (&s_deferred[i].fileInfo->cb == block)
            return i;
    return -1;
}

// Issues the waiting reads whose bytes have arrived (called whenever the
// game's threads wait or a frame ends).
void port_web_dvd_poll(void)
{
    while (s_deferredCount > 0 && read_ready(&s_deferred[0]))
    {
        DeferredRead r = s_deferred[0];
        remove_deferred(0);
        issue(&r);
    }
}

BOOL port_DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio)
{
    DeferredRead r = {fileInfo, addr, length, offset, callback, prio};
    if (s_deferredCount == 0 && read_ready(&r))
    {
        issue(&r);
        return TRUE;
    }
    if (s_deferredCount == MAX_DEFERRED)
    {
        port_web_dvd_poll();
        if (s_deferredCount == MAX_DEFERRED)
        {
            // Out of room: issue the oldest now (it waits for its bytes).
            DeferredRead oldest = s_deferred[0];
            remove_deferred(0);
            issue(&oldest);
        }
    }
    fileInfo->callback = callback;
    fileInfo->cb.state = DVD_STATE_BUSY;
    s_deferred[s_deferredCount++] = r;
    return TRUE;
}

s32 port_DVDCancel(volatile DVDCommandBlock* block)
{
    int i = find_deferred((const DVDCommandBlock*)block);
    if (i < 0)
        return DVDCancel(block);
    remove_deferred(i);
    block->state = DVD_STATE_CANCELED;
    return DVD_RESULT_GOOD;
}

int port_DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    int i = find_deferred(block);
    if (i < 0)
        return DVDCancelAsync(block, callback);
    remove_deferred(i);
    block->state = DVD_STATE_CANCELED;
    if (callback != NULL)
        callback(DVD_RESULT_GOOD, block);
    return TRUE;
}

BOOL port_DVDClose(DVDFileInfo* fileInfo)
{
    for (int i = s_deferredCount - 1; i >= 0; i--)
        if (s_deferred[i].fileInfo == fileInfo)
            remove_deferred(i);
    return DVDClose(fileInfo);
}
#else
BOOL port_DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio)
{
    set_callback(fileInfo, callback);
    return DVDReadAsyncPrio(fileInfo, addr, length, offset, callback != NULL ? trampoline : NULL, prio);
}

s32 port_DVDCancel(volatile DVDCommandBlock* block)
{
    return DVDCancel(block);
}

int port_DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback)
{
    return DVDCancelAsync(block, callback);
}

BOOL port_DVDClose(DVDFileInfo* fileInfo)
{
    return DVDClose(fileInfo);
}
#endif
