// Frame-exact captures for the Dolphin comparison (port/tools/dolphin_compare.py).
//
// MSSB_FREEZE_FRAMES="600,900": once the scripted-input frame counter (the
// PADRead count MSSB_INPUT is keyed to, port/src/input.cpp) reaches a listed
// frame, the game stops right after presenting that frame. On the web the
// canvas keeps showing it; Module.mssbFrozen = {frame, padFrame, retrace} is
// set until the driver sets Module.mssbRelease = true. Native builds ignore it.
//
// Called once per presented frame from port_present_frame (vi_frame.cpp).

#include <dolphin/types.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

extern "C" u32 port_pad_script_frame(void);
#include "port_internal.h"

#ifdef __EMSCRIPTEN__
EM_ASYNC_JS(void, freeze_wait_release, (int frame, int padFrame, int retrace), {
    Module.mssbRelease = false;
    Module.mssbFrozen = { frame: frame, padFrame: padFrame, retrace: retrace };
    while (!Module.mssbRelease)
        await new Promise((resolve) => requestAnimationFrame(resolve));
    Module.mssbFrozen = null;
    Module.mssbRelease = false;
});
#endif

namespace {
std::vector<u32>& freeze_list()
{
    static std::vector<u32> list = [] {
        std::vector<u32> out;
        const char* env = getenv("MSSB_FREEZE_FRAMES");
        if (env == nullptr)
            return out;
        for (const char* p = env; *p != '\0';)
        {
            char* end = nullptr;
            unsigned long v = strtoul(p, &end, 10);
            if (end == p)
            {
                ++p;
                continue;
            }
            out.push_back((u32)v);
            p = end;
        }
        std::sort(out.begin(), out.end());
        return out;
    }();
    return list;
}
} // namespace

extern "C" void port_freeze_frames_check(void)
{
    std::vector<u32>& list = freeze_list();
    static size_t s_next = 0;
    if (s_next >= list.size())
        return;
    u32 pad = port_pad_script_frame();
    if (pad < list[s_next])
        return;
    u32 frame = list[s_next];
    while (s_next < list.size() && list[s_next] <= pad)
        ++s_next; // frames skipped by a long frame are captured once
#ifdef __EMSCRIPTEN__
    freeze_wait_release((int)frame, (int)pad, (int)port_retrace_count());
#else
    (void)frame; // native: nothing to capture against yet
#endif
}
