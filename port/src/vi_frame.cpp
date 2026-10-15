// VI retrace emulation and frame pacing.
//
// The game presents by calling VIWaitForRetrace after GXCopyDisp. On PC that
// call is the frame boundary: finish aurora's frame (which presents and waits
// for vsync), pump window events, run the retrace callbacks the game installed,
// and begin the next frame.

#include <aurora/aurora.h>
#include <aurora/event.h>
#include <aurora/gfx.h>
#include <dolphin/vi.h>

#include "port/os.h"
#include "port_internal.h"


#include <algorithm>
#include <atomic>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <thread>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include "port/web_stats.h"
extern "C" void port_web_frame_tick(void);
extern "C" void port_web_dvd_poll(void);
extern "C" void port_dtk_web_pump(void);
extern "C" int port_is_main_os_thread(void);
#endif

#ifdef __EMSCRIPTEN__
WebFrameStats g_webStats; // ?stats (port_web_frame_tick prints and resets it)
#endif

namespace {
std::atomic<u32> s_retraceCount{0};
VIRetraceCallback s_preCb = nullptr;
VIRetraceCallback s_postCb = nullptr;
void* s_nextFb = nullptr;
void* s_currentFb = nullptr;
bool s_inFrame = false;
bool s_quitRequested = false;
std::thread::id s_mainThread;

void handle_events()
{
    port_crash_heartbeat();
    const AuroraEvent* event = aurora_update();
    while (event != nullptr && event->type != AURORA_NONE)
    {
        if (event->type == AURORA_EXIT)
            s_quitRequested = true;
        ++event;
    }
}

#ifdef __EMSCRIPTEN__
// Resolves with the rAF timestamp: the start of the display refresh this
// callback belongs to, free of the jitter of when the callback actually runs.
// Hidden tabs get no animation frames; online play must keep going there.
EM_ASYNC_JS(double, web_wait_animation_frame, (), {
    if (document.hidden && Module.mssbNet)
        return await new Promise((resolve) => setTimeout(() => resolve(performance.now()), 4));
    return await new Promise((resolve) => requestAnimationFrame(resolve));
});


// The browser presents the canvas when control returns to its event loop, so
// each frame ends by yielding (Asyncify) until a display refresh. When the
// display runs at a multiple of ~60 Hz (60, 120 Hz ProMotion, 240) every k-th
// refresh is one game frame (the game runs at 60.0 instead of 59.94 Hz, as on
// a TV); otherwise (144 Hz, ...) the frame goes out on the first refresh within
// half a refresh of its 59.94 Hz slot. Audio is topped up while waiting.
void pace_frame()
{
    constexpr double kPeriodMs = 1001.0 / 60.0;
    static double s_next = 0;     // this frame's slot (rAF time base)
    static double s_lastVsync = 0;
    static double s_lastPresent = 0;
    static double s_deltas[32];   // recent refresh-to-refresh times
    static unsigned s_deltaIdx = 0;
    static double s_workStart = 0;

    // A display refreshing at ~30 Hz (iOS Low Power Mode, a throttled tab):
    // the game frame in between runs without waiting, so the game keeps its
    // speed (each refresh shows every other frame).
    static double s_refresh = kPeriodMs;
    static double s_workAvg = 0;
    static int s_catchUp = 0;
    double work = s_workStart != 0 ? emscripten_get_now() - s_workStart : 0;
    s_workAvg += (work - s_workAvg) * 0.05;
    if (s_catchUp > 0)
    {
        s_catchUp--;
        s_next += kPeriodMs;
        g_webStats.frames++;
        g_webStats.workMs += work;
        port_web_frame_tick();
        s_workStart = emscripten_get_now();
        return;
    }
    double t;
    int waits = 0;
    double firstWait = 0;
    for (;;)
    {
        double a0 = emscripten_get_now();
        port_audio_pump();
        g_webStats.audioMs += emscripten_get_now() - a0;
        t = web_wait_animation_frame();
        if (waits++ == 0)
            firstWait = t - s_lastPresent;
        a0 = emscripten_get_now();
        port_audio_pump();
        g_webStats.audioMs += emscripten_get_now() - a0;
        if (s_lastVsync != 0)
            s_deltas[s_deltaIdx++ % 32] = t - s_lastVsync;
        s_lastVsync = t;
        // The display's refresh period: the median of recent deltas (rAF
        // timestamps jitter by a millisecond or so).
        double sorted[32];
        unsigned n = 0;
        for (double d : s_deltas)
            if (d > 3.0 && d < 50.0)
                sorted[n++] = d;
        std::sort(sorted, sorted + n);
        double refresh = n != 0 ? sorted[n / 2] : kPeriodMs;
        s_refresh = refresh;
        if (s_lastPresent == 0 || t - s_lastPresent > 100.0)
        {
            s_next = t; // first frame, or fell behind (slow frame, tab hidden): don't catch up
            break;
        }
        double k = std::max(1.0, std::round(kPeriodMs / refresh));
        if (std::fabs(k * refresh - kPeriodMs) < kPeriodMs * 0.03)
        {
            if (t - s_lastPresent >= (k - 0.5) * refresh)
            {
                s_next = t;
                break;
            }
        }
        else if (t >= s_next - refresh * 0.5)
            break;
    }
    s_next += kPeriodMs;
    // Frames per refresh at a slow refresh, when the CPU can afford them.
    const int perRefresh = s_refresh > kPeriodMs * 1.5 ? std::min(4, (int)std::lround(s_refresh / kPeriodMs)) : 1;
    // Game frames since the last refresh's (for the stats).
    static int s_batch = 1;
    double interval = s_lastPresent != 0 ? (t - s_lastPresent) / s_batch : kPeriodMs;
    if (perRefresh > 1 && s_workAvg * perRefresh < s_refresh * 0.8)
        s_catchUp = perRefresh - 1;
    s_batch = 1 + s_catchUp;
    s_lastPresent = t;
    g_webStats.frames++;
    if (interval > kPeriodMs * 1.5)
        g_webStats.late++;
    {
        // ?stats: each late frame, with what might explain it (a long game
        // frame, or GPU pipelines compiled just before: aurora's pipeline cache).
        static unsigned s_frameNo = 0;
        static u32 s_created[3];
        const AuroraStats* st = aurora_get_stats();
        ++s_frameNo;
        s_created[s_frameNo % 3] = st->createdPipelines;
        u32 recent = st->createdPipelines - s_created[(s_frameNo + 1) % 3];
        if (interval > kPeriodMs * 1.5)
            EM_ASM({
                if (Module.mssbStats)
                    console.log(`[late] frame ${$0}: ${$1.toFixed(1)} ms since the last one (game ${$2.toFixed(1)} ms, ` +
                                `${$3} pipelines built in the last 3 frames, ${$4} queued, ${$5} refreshes waited, ` +
                                `the first ${$6.toFixed(1)} ms after the last frame)`);
            }, s_frameNo, interval, work, recent, st->queuedPipelines, waits, firstWait);
    }
    if (interval > g_webStats.maxIntervalMs)
        g_webStats.maxIntervalMs = interval;
    if (work > g_webStats.maxWorkMs)
        g_webStats.maxWorkMs = work;
    g_webStats.workMs += work;
    port_web_frame_tick();
    s_workStart = emscripten_get_now();
}

void port_sleep_ms(int ms)
{
    emscripten_sleep(ms);
}
#else
// The game runs one tick per NTSC field (59.94 Hz). aurora presents with vsync,
// which runs at the display's rate (120 Hz on ProMotion Macs), so hold each
// frame until its slot comes up.
using clock = std::chrono::steady_clock;
const clock::duration kPeriod =
    std::chrono::duration_cast<clock::duration>(std::chrono::nanoseconds(1001000000LL / 60));
clock::time_point s_next = clock::now() + kPeriod;

void pace_frame()
{
    clock::time_point now = clock::now();
    if (now < s_next)
    {
        std::this_thread::sleep_until(s_next);
        s_next += kPeriod;
    }
    else
    {
        // Running behind (slow frame, window hidden): don't try to catch up.
        s_next = now + kPeriod;
    }
}

void port_sleep_ms(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#endif

void quit_now()
{
    port_audio_shutdown();
    aurora_shutdown();
    std::exit(0);
}
} // namespace

extern "C" void port_pad_sample(void);
extern "C" void port_freeze_frames_check(void);
extern "C" void port_pad_assign(void);
extern "C" void port_pipeline_prewarm_policy(void);

extern "C" {

void port_begin_first_frame(void)
{
    s_mainThread = std::this_thread::get_id();
    handle_events();
    while (!aurora_begin_frame())
    {
        if (s_quitRequested)
            quit_now();
        port_sleep_ms(16);
        handle_events();
    }
    s_inFrame = true;
}

void port_present_frame(void)
{
    if (s_inFrame)
    {
#ifdef __EMSCRIPTEN__
        port_pipeline_prewarm_policy(); // before aurora_end_frame, which starts the background compiles
        double t0 = emscripten_get_now();
        aurora_end_frame();
        g_webStats.endFrameMs += emscripten_get_now() - t0;
#else
        aurora_end_frame();
#endif
        s_inFrame = false;
    }
    pace_frame();
    port_freeze_frames_check(); // MSSB_FREEZE_FRAMES (freeze_frames.cpp)
#ifdef __EMSCRIPTEN__
    port_web_dvd_poll();
    port_dtk_web_pump();
#endif

#ifdef __EMSCRIPTEN__
    double e0 = emscripten_get_now();
    handle_events();
    g_webStats.eventsMs += emscripten_get_now() - e0;
#else
    handle_events();
#endif
    if (s_quitRequested)
        quit_now();
    port_pad_assign();

    // Online play: wait for this frame's inputs from every peer.
    port_net_frame();

    // Retrace "interrupt".
    u32 count = ++s_retraceCount;
    port_interrupt_enter();
    if (s_preCb)
        s_preCb(count);
    s_currentFb = s_nextFb;
    if (s_postCb)
        s_postCb(count);
    port_pad_sample(); // PADSetSamplingCallback (the game polls pads here)
    port_interrupt_leave();
    port_retrace_notify();

    // aurora_begin_frame returns false while the window is minimized or
    // otherwise can't present; block the game until it can.
    while (!aurora_begin_frame())
    {
        port_sleep_ms(16);
        handle_events();
        if (s_quitRequested)
            quit_now();
    }
    s_inFrame = true;
}

void port_request_quit(void)
{
    s_quitRequested = true;
}

// The main thread presents; other game threads wait for the next frame.
void VIWaitForRetrace(void)
{
#ifdef __EMSCRIPTEN__
    if (port_is_main_os_thread())
#else
    if (std::this_thread::get_id() == s_mainThread)
#endif
        port_present_frame();
    else
        port_wait_retrace(s_retraceCount.load());
}

u32 VIGetRetraceCount(void)
{
    return s_retraceCount.load();
}

u32 VIGetNextField(void)
{
    return 0;
}

u32 VIGetDTVStatus(void)
{
    return 1; // progressive scan capable
}

void* VIGetCurrentFrameBuffer(void)
{
    return s_currentFb;
}

void* VIGetNextFrameBuffer(void)
{
    return s_nextFb;
}

void VISetNextFrameBuffer(void* fb)
{
    s_nextFb = fb;
}

void VISetBlack(BOOL black)
{
    (void)black;
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback cb)
{
    VIRetraceCallback old = s_preCb;
    s_preCb = cb;
    return old;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback cb)
{
    VIRetraceCallback old = s_postCb;
    s_postCb = cb;
    return old;
}

} // extern "C"

#ifndef __EMSCRIPTEN__
std::chrono::steady_clock::time_point port_retrace_deadline() { return s_next; }
#endif
unsigned int port_retrace_count() { return s_retraceCount.load(); }
