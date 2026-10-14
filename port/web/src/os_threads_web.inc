// Web builds: OS threads, interrupts, semaphores and message queues on one
// host thread. Included by port/src/os.cpp (inside its extern "C" block).
//
// Every OSThread is an Emscripten fiber (Asyncify) with its own stacks. The
// scheduler is cooperative, like the native one's run token: a thread runs
// until it blocks (sleep, semaphore, message, suspend, exit) or wakes a
// higher-priority thread; then the highest-priority ready thread runs. When
// nothing is ready, the waiting thread idles: it delivers queued "interrupts"
// (DVD completions, DSP callbacks), tops up audio and, while the main thread
// is blocked, presents frames and runs the VI retrace callbacks (which is what
// wakes the game's frame loop), yielding to the browser in between.
//
// Interrupts: there are no other host threads, so interrupt work is queued
// (port_raise_interrupt) and delivered when interrupts get enabled or a
// thread waits. "Interrupts disabled" is per thread, as it is per context on
// the GameCube.

namespace {
struct WebThread
{
    OSThread* os = nullptr;
    void* (*func)(void*) = nullptr;
    void* param = nullptr;
    bool started = false;
    bool finished = false;
    bool waiting = false;
    std::function<bool()> done; // wait condition while waiting
    bool irqDisabled = false;
    int pendingResume = 0;
    emscripten_fiber_t fiber;
    void* cStack = nullptr;
    void* asyncStack = nullptr;
};

constexpr size_t kFiberStack = 512u << 10;
constexpr size_t kAsyncifyStack = 512u << 10;

std::unordered_map<OSThread*, WebThread*> g_wthreads;
WebThread* g_cur = nullptr;
WebThread* g_main = nullptr;
OSThread g_mainThread;
bool g_irqDisabled = false;
bool g_delivering = false;
std::vector<std::pair<void (*)(void*), void*>> g_pendingIrqs;
double g_lastYieldMs = 0;
bool g_presenting = false;

WebThread* wt_of(OSThread* t)
{
    auto it = g_wthreads.find(t);
    return it == g_wthreads.end() ? nullptr : it->second;
}

bool runnable(WebThread* w)
{
    return w->started && !w->finished && w->os->suspend <= 0 && (!w->waiting || w->done());
}

WebThread* best_ready(WebThread* exclude)
{
    WebThread* best = nullptr;
    for (auto& [t, w] : g_wthreads)
    {
        if (w == exclude || !runnable(w))
            continue;
        if (best == nullptr || t->priority < best->os->priority)
            best = w;
    }
    return best;
}

void deliver_interrupts(bool audio)
{
    if (g_irqDisabled || g_delivering)
        return;
    g_delivering = true;
    g_irqDisabled = true;
    while (!g_pendingIrqs.empty())
    {
        auto pending = std::move(g_pendingIrqs);
        for (auto& [fn, arg] : pending)
            fn(arg);
    }
    if (audio)
        port_audio_pump();
    g_irqDisabled = false;
    g_delivering = false;
}

void trace_os(const char* what)
{
    static int s_on = -1;
    if (s_on < 0)
        s_on = getenv("MSSB_TRACE_OS") != nullptr;
    if (!s_on)
        return;
    static double s_last = 0;
    static unsigned s_counts[4];
    int k = what[0] == 'p' ? 0 : what[1] == 'l' ? 1 : what[0] == 'i' ? 2 : 3;
    s_counts[k]++;
    double now = emscripten_get_now();
    if (now - s_last > 2000)
    {
        s_last = now;
        fprintf(stderr, "[os] present %u sleep %u idle %u switch %u; cur prio %d main waiting %d\n", s_counts[0],
                s_counts[1], s_counts[2], s_counts[3], g_cur ? (int)g_cur->os->priority : -1, g_main ? (int)g_main->waiting : -1);
        for (auto& [t, w] : g_wthreads)
            fprintf(stderr, "[os]   thread %p prio %d started %d fin %d waiting %d done %d suspend %d\n", (void*)t,
                    (int)t->priority, w->started, w->finished, w->waiting, w->waiting ? (int)w->done() : -1, (int)t->suspend);
    }
}

void fiber_entry(void* arg);

// Runs `to` (the current thread stays as it is: ready, waiting or finished).
void switch_to(WebThread* to)
{
    WebThread* from = g_cur;
    if (to == from)
        return;
    from->irqDisabled = g_irqDisabled;
    if (from->os->state == OS_THREAD_STATE_RUNNING)
        from->os->state = OS_THREAD_STATE_READY;
    if (to->cStack == nullptr && to != g_main)
    {
        to->cStack = std::malloc(kFiberStack);
        to->asyncStack = std::malloc(kAsyncifyStack);
        emscripten_fiber_init(&to->fiber, fiber_entry, to, to->cStack, kFiberStack, to->asyncStack,
                              kAsyncifyStack);
    }
    trace_os("switch");
    g_cur = to;
    to->os->state = OS_THREAD_STATE_RUNNING;
    g_irqDisabled = to->irqDisabled;
    emscripten_fiber_swap(&from->fiber, &to->fiber);
    // Back on `from`.
    g_irqDisabled = from->irqDisabled;
}

void yield_to_browser()
{
    emscripten_sleep(0);
    g_lastYieldMs = emscripten_get_now();
}

// Nothing can run: deliver interrupts and audio; if the main thread is
// blocked, present (which waits for the frame's slot and runs the retrace).
void idle()
{
    trace_os("idle");
    bool wasDisabled = g_irqDisabled;
    g_irqDisabled = false;
    deliver_interrupts(true);
    g_irqDisabled = wasDisabled;
    // The calling thread may be runnable (a busy wait in OSYieldThread):
    // only other ready threads skip the frame.
    if (best_ready(g_cur) != nullptr)
        return;
    if (g_main->waiting && !g_presenting)
    {
        g_presenting = true;
        trace_os("present");
        port_present_frame();
        g_presenting = false;
        g_lastYieldMs = emscripten_get_now();
    }
    else
    {
        trace_os("sleep");
        emscripten_sleep(1);
        g_lastYieldMs = emscripten_get_now();
    }
}

// Blocks the current thread until done() holds, running others meanwhile.
// Interrupts are enabled while waiting, as on the GameCube.
void block_until(std::function<bool()> done)
{
    WebThread* self = g_cur;
    if (done())
        return;
    bool hadIrq = g_irqDisabled;
    self->waiting = true;
    self->done = std::move(done);
    self->os->state = OS_THREAD_STATE_WAITING;
    g_irqDisabled = false;
    for (;;)
    {
        deliver_interrupts(false);
        if (self->done() && self->os->suspend <= 0)
        {
            // Ready: run unless a higher-priority thread is ready too.
            WebThread* best = best_ready(self);
            if (best == nullptr || best->os->priority >= self->os->priority)
                break;
            self->waiting = false;
            self->irqDisabled = false;
            switch_to(best);
            break;
        }
        WebThread* next = best_ready(self);
        if (next != nullptr)
            switch_to(next);
        else
            idle();
    }
    self->waiting = false;
    self->done = nullptr;
    self->os->state = OS_THREAD_STATE_RUNNING;
    g_irqDisabled = hadIrq;
}

int g_irqNest = 0; // inside port_interrupt_enter/leave (VI, DSP, AI callbacks)

// True while interrupt work runs: wakeups only take effect at the next switch.
bool in_interrupt()
{
    return g_delivering || g_irqNest > 0 || g_presenting;
}

// The running thread lets a higher-priority ready thread run first.
void maybe_preempt()
{
    WebThread* self = g_cur;
    if (self == nullptr || in_interrupt())
        return;
    WebThread* best = best_ready(self);
    if (best != nullptr && best->os->priority < self->os->priority)
        switch_to(best);
}

// Gives the CPU away until `self` is runnable again (suspended or finished threads).
void park()
{
    WebThread* self = g_cur;
    for (;;)
    {
        if (runnable(self))
            return;
        WebThread* next = best_ready(self);
        if (next != nullptr)
            switch_to(next);
        else
            idle();
    }
}

unsigned long long& gen(const void* q)
{
    static std::unordered_map<const void*, unsigned long long> s_gen;
    return s_gen[q];
}

void finish(WebThread* w, void* val)
{
    w->os->val = val;
    w->os->state = OS_THREAD_STATE_MORIBUND;
    w->finished = true;
    gen(&w->os->queueJoin)++;
    // A fiber can't return: run others forever.
    g_irqDisabled = false;
    for (;;)
    {
        WebThread* next = best_ready(w);
        if (next != nullptr)
            switch_to(next);
        else
            idle();
    }
}

void fiber_entry(void* arg)
{
    WebThread* w = (WebThread*)arg;
    g_irqDisabled = false;
    void* val = w->func(w->param);
    finish(w, val);
}
} // namespace

BOOL OSDisableInterrupts(void)
{
    BOOL was = !g_irqDisabled;
    g_irqDisabled = true;
    return was;
}

BOOL OSEnableInterrupts(void)
{
    BOOL was = !g_irqDisabled;
    g_irqDisabled = false;
    if (!g_pendingIrqs.empty())
        deliver_interrupts(false);
    return was;
}

BOOL OSRestoreInterrupts(BOOL level)
{
    if (level)
        return OSEnableInterrupts();
    return OSDisableInterrupts();
}

static bool s_irqSaved[16];
static int s_irqNest = 0;

void port_interrupt_enter(void)
{
    s_irqSaved[s_irqNest++ & 15] = g_irqDisabled;
    g_irqNest++;
    g_irqDisabled = true;
}

void port_interrupt_leave(void)
{
    g_irqNest--;
    g_irqDisabled = s_irqSaved[--s_irqNest & 15];
}

void port_raise_interrupt(void (*fn)(void*), void* arg)
{
    g_pendingIrqs.emplace_back(fn, arg);
}

void port_yield_to_browser(void)
{
    yield_to_browser();
}

// ?debug: every thread's scheduling state (port/game/web_debug.c).
void port_debug_threads(void)
{
    for (auto& [t, w] : g_wthreads)
        printf("[dbg]   thread %p prio %d%s started %d fin %d waiting %d done %d suspend %d state %d\n", (void*)t,
               (int)t->priority, w == g_cur ? " (current)" : "", w->started, w->finished, w->waiting,
               w->waiting ? (int)w->done() : -1, (int)t->suspend, (int)t->state);
    printf("[dbg]   irq disabled %d delivering %d pending irqs %zu presenting %d\n", g_irqDisabled, g_delivering,
           g_pendingIrqs.size(), g_presenting);
}

int port_is_main_os_thread(void)
{
    return g_cur == g_main;
}

void port_threads_init(void)
{
    OSThread* t = &g_mainThread;
    t->state = OS_THREAD_STATE_RUNNING;
    t->suspend = 0;
    t->priority = t->base = 16;
    auto* w = new WebThread();
    w->os = t;
    w->started = true;
    w->asyncStack = std::malloc(kAsyncifyStack);
    emscripten_fiber_init_from_current_context(&w->fiber, w->asyncStack, kAsyncifyStack);
    g_wthreads[t] = w;
    g_main = w;
    g_cur = w;
}

BOOL OSCreateThread(OSThread* thread, void* (*func)(void*), void* param, void* stack, u32 stackSize,
                    OSPriority priority, u16 attr)
{
    thread->state = OS_THREAD_STATE_READY;
    thread->attr = attr;
    thread->suspend = 1;
    thread->priority = thread->base = priority;
    thread->val = nullptr;
    thread->queue = nullptr;
    thread->queueJoin.head = thread->queueJoin.tail = nullptr;
    thread->stackBase = (u8*)stack;
    thread->stackEnd = (u8*)stack - stackSize;
    thread->error = 0;
    WebThread* w = wt_of(thread);
    if (w == nullptr)
    {
        w = new WebThread();
        g_wthreads[thread] = w;
    }
    else if (w == g_cur)
    {
        return FALSE;
    }
    // A recreated thread gets fresh stacks (the old fiber is dead).
    std::free(w->cStack);
    std::free(w->asyncStack);
    *w = WebThread{};
    w->os = thread;
    w->func = func;
    w->param = param;
    return TRUE;
}

s32 OSResumeThread(OSThread* thread)
{
    s32 prev = thread->suspend;
    WebThread* w = wt_of(thread);
    if (prev <= 0)
    {
        // Resumed from "interrupt context" before it suspended itself: keep it.
        if (w != nullptr && w->started && !w->finished && in_interrupt())
            w->pendingResume++;
        return prev;
    }
    if (--thread->suspend == 0)
    {
        if (w != nullptr && !w->started)
            w->started = true;
        maybe_preempt();
    }
    return prev;
}

s32 OSSuspendThread(OSThread* thread)
{
    WebThread* w = wt_of(thread);
    if (w != nullptr && w == g_cur && w->pendingResume > 0)
    {
        w->pendingResume--;
        return thread->suspend;
    }
    s32 prev = thread->suspend++;
    if (w != nullptr && w == g_cur)
    {
        bool hadIrq = g_irqDisabled;
        g_irqDisabled = false;
        w->irqDisabled = false;
        park();
        g_irqDisabled = hadIrq;
    }
    return prev;
}

BOOL OSIsThreadSuspended(OSThread* thread)
{
    return thread->suspend > 0;
}

BOOL OSIsThreadTerminated(OSThread* thread)
{
    return thread->state == OS_THREAD_STATE_MORIBUND || thread->state == 0;
}

OSThread* OSGetCurrentThread(void)
{
    return g_cur != nullptr ? g_cur->os : nullptr;
}

void OSCancelThread(OSThread* thread)
{
    WebThread* w = wt_of(thread);
    if (w == nullptr)
        return;
    w->finished = true;
    thread->state = 0;
    if (w == g_cur)
        finish(w, nullptr);
}

void OSExitThread(void* val)
{
    if (g_cur == nullptr || g_cur == g_main)
        return;
    finish(g_cur, val);
}

void OSYieldThread(void)
{
    // A busy-waiting thread: let interrupts, other threads and the browser run.
    bool wasDisabled = g_irqDisabled;
    g_irqDisabled = false;
    deliver_interrupts(true);
    WebThread* self = g_cur;
    WebThread* next = best_ready(self);
    if (next != nullptr && next->os->priority <= self->os->priority)
        switch_to(next);
    else if (g_main->waiting && self != g_main && !g_presenting)
        idle(); // the frame loop is waiting on this busy thread's progress
    else if (emscripten_get_now() - g_lastYieldMs > 4.0)
        yield_to_browser();
    g_irqDisabled = wasDisabled;
}

void OSInitThreadQueue(OSThreadQueue* queue)
{
    queue->head = nullptr;
    queue->tail = nullptr;
}

void OSSleepThread(OSThreadQueue* queue)
{
    unsigned long long start = gen(queue);
    block_until([queue, start] { return gen(queue) != start; });
}

void OSWakeupThread(OSThreadQueue* queue)
{
    gen(queue)++;
    maybe_preempt();
}

void OSInitSemaphore(OSSemaphore* sem, s32 count)
{
    sem->count = count;
    OSInitThreadQueue(&sem->queue);
}

s32 OSWaitSemaphore(OSSemaphore* sem)
{
    block_until([sem] { return sem->count > 0; });
    return sem->count--;
}

s32 OSTryWaitSemaphore(OSSemaphore* sem)
{
    s32 count = sem->count;
    if (count > 0)
        sem->count--;
    return count;
}

s32 OSSignalSemaphore(OSSemaphore* sem)
{
    s32 count = sem->count++;
    gen(&sem->queue)++;
    maybe_preempt();
    return count;
}

s32 OSGetSemaphoreCount(OSSemaphore* sem)
{
    return sem->count;
}

void OSInitMessageQueue(OSMessageQueue* mq, OSMessage* msgArray, s32 msgCount)
{
    OSInitThreadQueue(&mq->queueSend);
    OSInitThreadQueue(&mq->queueReceive);
    mq->msgArray = msgArray;
    mq->msgCount = msgCount;
    mq->firstIndex = 0;
    mq->usedCount = 0;
}

BOOL OSSendMessage(OSMessageQueue* mq, OSMessage msg, s32 flags)
{
    if (mq->usedCount >= mq->msgCount)
    {
        if (!(flags & OS_MESSAGE_BLOCK))
            return FALSE;
        block_until([mq] { return mq->usedCount < mq->msgCount; });
    }
    mq->msgArray[(mq->firstIndex + mq->usedCount) % mq->msgCount] = msg;
    mq->usedCount++;
    gen(&mq->queueReceive)++;
    maybe_preempt();
    return TRUE;
}

BOOL OSJamMessage(OSMessageQueue* mq, OSMessage msg, s32 flags)
{
    if (mq->usedCount >= mq->msgCount)
    {
        if (!(flags & OS_MESSAGE_BLOCK))
            return FALSE;
        block_until([mq] { return mq->usedCount < mq->msgCount; });
    }
    mq->firstIndex = (mq->firstIndex + mq->msgCount - 1) % mq->msgCount;
    mq->msgArray[mq->firstIndex] = msg;
    mq->usedCount++;
    gen(&mq->queueReceive)++;
    maybe_preempt();
    return TRUE;
}

BOOL OSReceiveMessage(OSMessageQueue* mq, OSMessage* msg, s32 flags)
{
    if (mq->usedCount == 0)
    {
        if (!(flags & OS_MESSAGE_BLOCK))
            return FALSE;
        block_until([mq] { return mq->usedCount != 0; });
    }
    if (msg != nullptr)
        *msg = mq->msgArray[mq->firstIndex];
    mq->firstIndex = (mq->firstIndex + 1) % mq->msgCount;
    mq->usedCount--;
    gen(&mq->queueSend)++;
    maybe_preempt();
    return TRUE;
}

// A non-main thread waits for the next presented frame.
void port_wait_retrace(unsigned int count)
{
    block_until([count] { return port_retrace_count() != count; });
}

void port_retrace_notify(void) {}
