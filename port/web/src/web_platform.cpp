// Browser glue: the disc image and persistent storage (from strikers).
//
// The disc comes from the page (port/web/loader.js) as Module.mssbDisc:
// { size, readCached(offset, len) -> Uint8Array|null, read(offset, len) -> Promise<Uint8Array> }.
// Reads served from its block cache are synchronous; misses suspend the game
// (Asyncify) until the bytes arrive. CISO images (a block map, then the used
// blocks) are expanded here, so the page can keep the compact file.
//
// The user folder (/mssb: memory card, user.ini) is IndexedDB-backed; the
// page loads it before main() and it's written back every few seconds.

#include <aurora/dvd.h>

#include <emscripten.h>

#include "port/web_stats.h"

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {
EM_JS(double, web_disc_size, (), { return Module.mssbDisc ? Module.mssbDisc.size : 0; });

EM_JS(int, web_disc_read_cached, (double offset, void* out, int len), {
    const bytes = Module.mssbDisc.readCached(offset, len);
    if (!bytes)
        return -1;
    HEAPU8.set(bytes, out);
    return bytes.length;
});

EM_ASYNC_JS(int, web_disc_read_async, (double offset, void* out, int len), {
    try {
        const bytes = await Module.mssbDisc.read(offset, len);
        HEAPU8.set(bytes, out);
        return bytes.length;
    } catch (e) {
        console.error('disc read failed', e);
        return -1;
    }
});

// Raw reads of the file the page holds.
int64_t raw_read(uint64_t offset, void* out, size_t len)
{
    size_t done = 0;
    while (done < len)
    {
        size_t want = len - done;
        int chunk = want > (8u << 20) ? (8 << 20) : (int)want;
        int n = web_disc_read_cached((double)(offset + done), (uint8_t*)out + done, chunk);
        if (n < 0)
        {
            double t0 = emscripten_get_now();
            n = web_disc_read_async((double)(offset + done), (uint8_t*)out + done, chunk);
            g_webStats.discWaits++;
            g_webStats.discWaitMs += emscripten_get_now() - t0;
        }
        if (n <= 0)
            break;
        done += (size_t)n;
    }
    return (int64_t)done;
}

// CISO: "CISO", u32 block size (LE), u8 map[0x7FF8] (1: stored), data at 0x8000.
struct Ciso
{
    bool active = false;
    uint32_t blockSize = 0;
    std::vector<int32_t> fileBlock; // disc block -> stored index, -1: zeros
    uint64_t discSize = 0;
} s_ciso;

void detect_ciso()
{
    uint8_t head[0x8000];
    if (raw_read(0, head, sizeof(head)) != (int64_t)sizeof(head) || memcmp(head, "CISO", 4) != 0)
        return;
    uint32_t bs = head[4] | (head[5] << 8) | (head[6] << 16) | ((uint32_t)head[7] << 24);
    if (bs == 0)
        return;
    int32_t idx = 0;
    size_t last = 0;
    for (size_t i = 0; i < 0x8000 - 8; i++)
    {
        if (head[8 + i])
        {
            s_ciso.fileBlock.push_back(idx++);
            last = i + 1;
        }
        else
        {
            s_ciso.fileBlock.push_back(-1);
        }
    }
    s_ciso.fileBlock.resize(last);
    s_ciso.blockSize = bs;
    s_ciso.discSize = (uint64_t)last * bs;
    s_ciso.active = true;
    printf("[web] CISO disc: %u-byte blocks, %llu bytes\n", bs, (unsigned long long)s_ciso.discSize);
}

int64_t disc_read_at(void*, uint64_t offset, void* out, size_t len)
{
    if (len == 0)
        return 0;
    if (!s_ciso.active)
        return raw_read(offset, out, len > (8u << 20) ? (8u << 20) : len);
    if (offset >= s_ciso.discSize)
        return 0;
    if (offset + len > s_ciso.discSize)
        len = (size_t)(s_ciso.discSize - offset);
    size_t done = 0;
    while (done < len)
    {
        uint64_t pos = offset + done;
        uint64_t block = pos / s_ciso.blockSize;
        uint64_t inBlock = pos % s_ciso.blockSize;
        size_t n = (size_t)(s_ciso.blockSize - inBlock);
        if (n > len - done)
            n = len - done;
        int32_t stored = s_ciso.fileBlock[block];
        if (stored < 0)
        {
            memset((uint8_t*)out + done, 0, n);
        }
        else
        {
            uint64_t src = 0x8000 + (uint64_t)stored * s_ciso.blockSize + inBlock;
            if (raw_read(src, (uint8_t*)out + done, n) != (int64_t)n)
                return (int64_t)done;
        }
        done += n;
    }
    return (int64_t)done;
}

int64_t disc_length(void*)
{
    return s_ciso.active ? (int64_t)s_ciso.discSize : (int64_t)web_disc_size();
}

EM_JS(void, web_sync_storage, (), {
    if (Module.mssbSyncing)
        return;
    Module.mssbSyncing = true;
    FS.syncfs(false, (err) => {
        Module.mssbSyncing = false;
        if (err)
            console.warn('saving user data failed', err);
    });
});
} // namespace

extern "C" {
bool port_web_open_disc(void)
{
    if (web_disc_size() <= 0)
        return false;
    detect_ciso();
    static const AuroraDiscStream stream = {nullptr, disc_read_at, disc_length, nullptr};
    return aurora_dvd_open_stream(&stream);
}

int port_audio_queued_ms(void);

// Called once per game frame.
void port_web_frame_tick(void)
{
    static unsigned s_frames = 0;
    if (++s_frames % 300 == 0) // ~5 s
    {
        web_sync_storage();
        EM_ASM({
            const now = performance.now();
            if (Module.mssbStats && Module.lastStatsTime) {
                const ctx = Module.SDL3 && Module.SDL3.audioContext;
                console.log(`[stats] ${(300000 / (now - Module.lastStatsTime)).toFixed(1)} fps, ` +
                            `late ${$1}, worst gap ${$2.toFixed(1)} ms, game ${$3.toFixed(1)} ms avg / ${$4.toFixed(1)} max, ` +
                            `disc waits ${$5} (${$6.toFixed(0)} ms), audio queued ${$0} ms` +
                            (ctx ? `, audio ${ctx.state}` : ''));
            }
            Module.lastStatsTime = now;
        }, port_audio_queued_ms(), g_webStats.late, g_webStats.maxIntervalMs, g_webStats.workMs / g_webStats.frames,
           g_webStats.maxWorkMs, g_webStats.discWaits, g_webStats.discWaitMs);
        g_webStats = WebFrameStats{};
    }
}

void port_web_report_fatal(const char* message)
{
    EM_ASM({ if (Module.mssbFatal) Module.mssbFatal(UTF8ToString($0)); }, message);
}
}
