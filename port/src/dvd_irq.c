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

BOOL port_DVDReadAsyncPrio(DVDFileInfo* fileInfo, void* addr, s32 length, s32 offset, DVDCallback callback, s32 prio)
{
    set_callback(fileInfo, callback);
    return DVDReadAsyncPrio(fileInfo, addr, length, offset, callback != NULL ? trampoline : NULL, prio);
}
