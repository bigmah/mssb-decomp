// Online play: deterministic input lockstep over the page's WebRTC mesh
// (port/web/net.js), as in the strikers port (its docs/plan-online-mesh.md).
//
// Every peer runs the whole game. The unit of lockstep is a game frame (one
// VIWaitForRetrace): at each frame boundary the local pad is sent for frame
// N + delay, and frame N only starts once every playing port's input for it
// has arrived. The game is frame-driven (one tick per retrace), so with the
// same inputs, seed and disc every peer computes the same game.
//
// Every 60 frames a hash of the game state (port/game/net_state.c) goes to the
// page, which compares it with the other peers and stops the game on a
// mismatch.
//
// Outside online play, port_pad_apply_script adds the page's on-screen touch
// controls (port/web/touch.js) and MSSB_INPUT presses to port 1.

#include <dolphin/pad.h>

#include "port/os.h"

#include <emscripten.h>

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {
// One port's input for one frame (8 bytes on the wire).
struct NetPad
{
    u16 buttons;
    s8 stickX, stickY, substickX, substickY;
    u8 triggerL, triggerR;
};
static_assert(sizeof(NetPad) == 8, "wire format");

EM_JS(int, web_net_config, (int* out), {
    const n = Module.mssbNet;
    if (!n)
        return 0;
    HEAP32[out >> 2] = n.localPort;
    HEAP32[(out >> 2) + 1] = n.activeMask;
    HEAP32[(out >> 2) + 2] = n.delay;
    return 1;
});

EM_JS(void, web_net_send, (u32 frame, const void* pad), {
    Module.mssbNet.sendLocal(frame, HEAPU8.slice(pad, pad + 8));
});

// 1: all inputs for `frame` copied to out (4 x 8 bytes); 0: not yet.
EM_JS(int, web_net_poll, (u32 frame, void* out), {
    const bytes = Module.mssbNet.inputsFor(frame);
    if (!bytes)
        return 0;
    HEAPU8.set(bytes, out);
    return 1;
});

// Waits (yielding to the browser) until new input arrives or a few ms pass.
// Returns 0 normally, -1 once the match has been abandoned.
EM_ASYNC_JS(int, web_net_wait, (u32 frame), { return await Module.mssbNet.wait(frame); });

EM_JS(void, web_net_hash, (u32 frame, u32 hash), { Module.mssbNet.localHash(frame, hash); });

// The page's on-screen touch controls (port/web/touch.js) as an 8-byte NetPad;
// 0 while nothing is touched.
EM_JS(int, web_touch_pad, (void* out), {
    const t = Module.mssbTouch;
    if (!t || !t.active)
        return 0;
    HEAPU8.set(t.bytes, out);
    return 1;
});

EM_JS(void, web_net_stalled, (u32 frame, int stalled), { Module.mssbNet.stalled(frame, !!stalled); });

bool s_init = false;
bool s_enabled = false;
int s_localPort = 0;
int s_activeMask = 0;
u32 s_delay = 3;
u32 s_frame = 0;
PADStatus s_pads[PAD_MAX_CONTROLLERS];

void to_pad(const NetPad& n, PADStatus& s, bool active)
{
    memset(&s, 0, sizeof(s));
    if (!active)
    {
        s.err = PAD_ERR_NO_CONTROLLER;
        return;
    }
    s.err = PAD_ERR_NONE;
    s.button = n.buttons;
    s.stickX = n.stickX;
    s.stickY = n.stickY;
    s.substickX = n.substickX;
    s.substickY = n.substickY;
    s.triggerLeft = n.triggerL;
    s.triggerRight = n.triggerR;
}

NetPad from_pad(const PADStatus& s)
{
    NetPad n = {};
    if (s.err != PAD_ERR_NONE)
        return n;
    n.buttons = s.button;
    n.stickX = s.stickX;
    n.stickY = s.stickY;
    n.substickX = s.substickX;
    n.substickY = s.substickY;
    n.triggerL = s.triggerLeft;
    n.triggerR = s.triggerRight;
    return n;
}

void init()
{
    s_init = true;
    int cfg[3];
    if (!web_net_config(cfg))
        return;
    s_enabled = true;
    s_localPort = cfg[0];
    s_activeMask = cfg[1];
    s_delay = (u32)cfg[2];
    printf("[net] lockstep on: local port %d, ports 0x%x, delay %u frames\n", s_localPort, s_activeMask, s_delay);
}
} // namespace

extern "C" void port_pad_script(PADStatus* status);
extern "C" void port_audio_net_frame(void);

namespace {
// Touch input adds to whatever the keyboard / gamepad gives port 1.
void apply_touch(PADStatus& s)
{
    NetPad t;
    if (!web_touch_pad(&t))
        return;
    s.err = PAD_ERR_NONE;
    s.button |= t.buttons;
    if (t.stickX != 0 || t.stickY != 0)
    {
        s.stickX = t.stickX;
        s.stickY = t.stickY;
    }
    if (t.triggerL > s.triggerLeft)
        s.triggerLeft = t.triggerL;
    if (t.triggerR > s.triggerRight)
        s.triggerRight = t.triggerR;
}
} // namespace

extern "C" {

int port_net_active(void)
{
    if (!s_init)
        init();
    return s_enabled;
}

float port_fixed_frame_ms(void)
{
    return port_net_active() ? 1000.0f / 60.0f : 0.0f;
}

// Called at each frame boundary, before the retrace callbacks poll the pads.
void port_net_frame(void)
{
    if (!port_net_active())
        return;

    // Hash the state the coming frame starts from.
    if (s_frame % 60 == 0)
        web_net_hash(s_frame, port_game_state_hash(s_frame));

    // This browser's controller (keyboard / first gamepad) plays as its port.
    PADStatus local[PAD_MAX_CONTROLLERS];
    PADRead(local);
    port_pad_script(local);
    apply_touch(local[0]);
    NetPad mine = from_pad(local[0]);
    web_net_send(s_frame + s_delay, &mine);

    NetPad pads[PAD_MAX_CONTROLLERS];
    bool stalled = false;
    while (!web_net_poll(s_frame, pads))
    {
        if (!stalled)
        {
            stalled = true;
            web_net_stalled(s_frame, 1);
        }
        port_audio_pump();
        if (web_net_wait(s_frame) < 0)
        {
            // The page has shown why; park the game.
            for (;;)
                emscripten_sleep(1000);
        }
    }
    if (stalled)
        web_net_stalled(s_frame, 0);

    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++)
        to_pad(pads[i], s_pads[i], (s_activeMask >> i) & 1);
    s_frame++;
    // Audio advances by exactly one frame's worth (port/src/audio/ai.cpp).
    port_audio_net_frame();
}

// The game's per-frame PADRead result: in net mode, the agreed inputs.
u16 port_intro_buttons(void); // port/game/views.c

void port_pad_apply_script(PADStatus* status)
{
    if (port_net_active())
    {
        memcpy(status, s_pads, sizeof(s_pads));
        return;
    }
    port_pad_script(status);
    apply_touch(status[0]);
    if (u16 intro = port_intro_buttons())
    {
        status[0].err = PAD_ERR_NONE;
        status[0].button |= intro;
    }
}
}
