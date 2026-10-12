// VI retrace emulation and frame pacing.
//
// The game presents by calling VIWaitForRetrace after GXCopyDisp. On PC that
// call is the frame boundary: finish aurora's frame (which presents and waits
// for vsync), pump window events, run the retrace callbacks the game installed,
// and begin the next frame.

#include <aurora/aurora.h>
#include <aurora/event.h>
#include <dolphin/vi.h>

#include "port/os.h"
#include "port_internal.h"


#include <atomic>
#include <chrono>
#include <cstdlib>
#include <thread>

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

void quit_now()
{
    port_audio_shutdown();
    aurora_shutdown();
    std::exit(0);
}
} // namespace

extern "C" void port_pad_sample(void);

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
        aurora_end_frame();
        s_inFrame = false;
    }
    pace_frame();

    handle_events();
    if (s_quitRequested)
        quit_now();

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
    if (std::this_thread::get_id() == s_mainThread)
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

std::chrono::steady_clock::time_point port_retrace_deadline() { return s_next; }
unsigned int port_retrace_count() { return s_retraceCount.load(); }
