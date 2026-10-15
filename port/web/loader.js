// Mario Superstar Baseball web loader: picks the disc image, keeps a copy in the
// browser's private storage (OPFS) so it's only chosen once, and starts the game.
'use strict';

const DISC_NAME = 'mssb.iso';
const DISC_DONE = 'mssb.iso.size'; // written once the copy is complete
const GAME_ID = 'GYQE01';
const BLOCK = 512 * 1024;
const MAX_BLOCKS = 160; // ~80 MB read cache

const $ = (id) => document.getElementById(id);
const params = new URLSearchParams(location.search);

// ?debug: the console goes to the site's /log too (port/cloudflare/src/worker.js),
// so a phone's errors can be read with `wrangler tail`.
if (params.has('debug')) {
  const id = Math.random().toString(36).slice(2, 8);
  let queue = [];
  const t0 = performance.now();
  // Batches stay small: a keepalive request over 64 KB is refused outright
  // (startup's GPU log alone is bigger), the Worker logs at most 200 lines of a
  // batch, and only the pagehide flush needs keepalive.
  const flush = (keepalive = false) => {
    while (queue.length) {
      const lines = [];
      let size = 0;
      while (queue.length && (lines.length === 0 || (lines.length < 100 && size + queue[0].length < 16000))) {
        size += queue[0].length;
        lines.push(queue.shift());
      }
      fetch('log', { method: 'POST', body: JSON.stringify({ id, lines }), keepalive }).catch(() => {});
    }
  };
  setInterval(flush, 1000);
  addEventListener('pagehide', () => flush(true));
  addEventListener('error', (e) => console.error('[page error]', e.message));
  addEventListener('unhandledrejection', (e) => console.error('[unhandled rejection]', String(e.reason?.stack || e.reason)));
  for (const level of ['log', 'info', 'warn', 'error']) {
    const orig = console[level].bind(console);
    console[level] = (...a) => {
      orig(...a);
      const text = a.map((x) => (x instanceof Error ? x.stack || x.message : typeof x === 'object' ? (() => { try { return JSON.stringify(x); } catch { return String(x); } })() : String(x))).join(' ');
      queue.push(`${((performance.now() - t0) / 1000).toFixed(1)} ${level} ${text}`);
    };
  }
  // GPU errors (validation, out of memory, shaders and pipelines the browser
  // rejects, a lost device): the browser only shows them in its own devtools.
  if (typeof GPUAdapter !== 'undefined') {
    let gpuErrors = 0;
    const gpuError = (what, msg) => {
      if (gpuErrors++ < 40) console.error(`[gpu] ${what}: ${String(msg).slice(0, 1500)}`);
    };
    const requestDevice = GPUAdapter.prototype.requestDevice;
    GPUAdapter.prototype.requestDevice = async function (...a) {
      const device = await requestDevice.apply(this, a);
      device.addEventListener('uncapturederror', (e) => gpuError('error', e.error?.message));
      device.lost.then((info) => console.error(`[gpu] device lost (${info.reason}): ${info.message}`));
      const createShaderModule = device.createShaderModule;
      device.createShaderModule = function (...b) {
        const m = createShaderModule.apply(this, b);
        m.getCompilationInfo?.().then((ci) => {
          for (const msg of ci.messages) {
            if (msg.type === 'error') gpuError('shader', `${msg.message} (line ${msg.lineNum}): ${b[0]?.label || ''}`);
          }
        }).catch(() => {});
        return m;
      };
      const createRenderPipelineAsync = device.createRenderPipelineAsync;
      device.createRenderPipelineAsync = function (...b) {
        const p = createRenderPipelineAsync.apply(this, b);
        p.catch((e) => gpuError('pipeline', e?.message || e));
        return p;
      };
      return device;
    };
    // Render pass calls the spec rejects (WebKit enforces them; Chrome lets some through), with arguments.
    const beginRenderPass = GPUCommandEncoder.prototype.beginRenderPass;
    GPUCommandEncoder.prototype.beginRenderPass = function (desc) {
      const pass = beginRenderPass.call(this, desc);
      const att = desc.colorAttachments?.find((a) => a) ?? null;
      const tex = att?.view?.__tex ?? desc.depthStencilAttachment?.view?.__tex;
      pass.__size = tex ? [tex.width, tex.height] : null;
      pass.__label = desc.label || '';
      return pass;
    };
    const createView = GPUTexture.prototype.createView;
    GPUTexture.prototype.createView = function (...a) {
      const v = createView.apply(this, a);
      v.__tex = this;
      return v;
    };
    const P = GPURenderPassEncoder.prototype;
    const setViewport = P.setViewport;
    P.setViewport = function (x, y, w, h, n, f) {
      const s = this.__size;
      if (x < 0 || y < 0 || w < 0 || h < 0 || n < 0 || n > 1 || f < 0 || f > 1 || n > f ||
          (s && (x + w > s[0] || y + h > s[1])))
        gpuError('setViewport', `${x},${y} ${w}x${h} depth ${n}..${f} on ${s} (${this.__label})`);
      return setViewport.call(this, x, y, w, h, n, f);
    };
    const setScissorRect = P.setScissorRect;
    P.setScissorRect = function (x, y, w, h) {
      const s = this.__size;
      if (s && (x + w > s[0] || y + h > s[1])) gpuError('setScissorRect', `${x},${y} ${w}x${h} on ${s} (${this.__label})`);
      return setScissorRect.call(this, x, y, w, h);
    };
  }
  // GPU lag: how long the GPU takes to finish what was submitted (sampled every
  // 30 submits). Large and growing means frames are queuing up on the GPU.
  let gpuSubmits = 0;
  let gpuLagMs = 0;
  let gpuInFlight = 0;
  if (typeof GPUQueue !== 'undefined') {
    const submit = GPUQueue.prototype.submit;
    GPUQueue.prototype.submit = function (...a) {
      const r = submit.apply(this, a);
      if (gpuSubmits++ % 30 === 0) {
        const t = performance.now();
        gpuInFlight++;
        this.onSubmittedWorkDone().then(() => {
          gpuLagMs = performance.now() - t;
          gpuInFlight--;
        });
      }
      return r;
    };
  }
  // The browser's audio callbacks (SDL plays through a ScriptProcessor on the main thread): one
  // that runs after its buffer was due to start leaves a gap, heard as a click or crackle.
  const au = { calls: 0, late: 0, worstMs: 0, silent: 0, rate: 48000 };
  // The last 4 s of what went to the speakers (s16 stereo), posted to the log by the button below.
  let ring = null;
  let ringPos = 0;
  const keepAudio = (buf) => {
    const n = buf.length;
    if (!ring) {
      au.rate = buf.sampleRate;
      ring = new Int16Array(Math.round(buf.sampleRate * 4) * 2);
    }
    const l = buf.getChannelData(0);
    const r = buf.numberOfChannels > 1 ? buf.getChannelData(1) : l;
    for (let i = 0; i < n; i++) {
      ring[ringPos] = Math.max(-32768, Math.min(32767, Math.round(l[i] * 32767)));
      ring[ringPos + 1] = Math.max(-32768, Math.min(32767, Math.round(r[i] * 32767)));
      ringPos = (ringPos + 2) % ring.length;
    }
  };
  let dumps = 0;
  const postAudio = async () => {
    if (!ring) return;
    const pcm = new Int16Array(ring.length);
    pcm.set(ring.subarray(ringPos), 0);
    pcm.set(ring.subarray(0, ringPos), ring.length - ringPos);
    const gz = new Uint8Array(await new Response(new Blob([pcm.buffer]).stream().pipeThrough(new CompressionStream('gzip'))).arrayBuffer());
    let bin = '';
    for (let i = 0; i < gz.length; i += 0x8000) bin += String.fromCharCode(...gz.subarray(i, i + 0x8000));
    const b64 = btoa(bin);
    const id = dumps++;
    const n = Math.ceil(b64.length / 1800);
    for (let i = 0; i < n; i++) console.log(`[audiodump] ${id} ${au.rate} ${i + 1}/${n} ${b64.slice(i * 1800, (i + 1) * 1800)}`);
  };
  if (typeof AudioContext !== 'undefined') {
    const orig = AudioContext.prototype.createScriptProcessor;
    AudioContext.prototype.createScriptProcessor = function (...a) {
      const node = orig.apply(this, a);
      const ctx = this;
      let handler = null;
      Object.defineProperty(node, 'onaudioprocess', {
        set(fn) {
          handler = fn;
        },
        get() {
          return handler;
        },
      });
      node.addEventListener('audioprocess', (e) => {
        au.calls++;
        const lateMs = (ctx.currentTime - e.playbackTime) * 1000;
        if (lateMs > 0) {
          au.late++;
          au.worstMs = Math.max(au.worstMs, lateMs);
          console.log(`[audio] late callback: ${lateMs.toFixed(0)} ms after its buffer was due`);
        }
        if (handler) handler.call(node, e);
        keepAudio(e.outputBuffer);
        const ch = e.outputBuffer.getChannelData(0);
        let zero = true;
        for (let i = 0; i < ch.length; i += 64) if (ch[i] !== 0) { zero = false; break; }
        if (zero) au.silent++;
      });
      return node;
    };
  }
  // A button to tap when something sounds wrong: stamps the moment in the log.
  window.addEventListener('DOMContentLoaded', () => {
    const b = document.createElement('button');
    b.textContent = 'static!';
    b.style.cssText = 'position:fixed;top:4px;left:50%;transform:translateX(-50%);z-index:99999;font:600 12px sans-serif;padding:4px 10px;opacity:.7';
    b.addEventListener('pointerdown', (e) => {
      e.stopPropagation();
      console.log(`[mark] heard something (audio callbacks ${au.calls}, late ${au.late})`);
      // A moment later, so the recording covers it.
      setTimeout(postAudio, 1000);
      b.textContent = 'marked';
      setTimeout(() => (b.textContent = 'static!'), 800);
    });
    document.body.appendChild(b);
  });
  setInterval(() => {
    if (!started) return;
    const ctx = window.Module?.SDL3?.audioContext;
    console.log(`gpu: ${gpuSubmits} submits, last sampled lag ${gpuLagMs.toFixed(0)} ms, ${gpuInFlight} samples in flight; ` +
      `audio ${ctx ? `${ctx.state} t=${ctx.currentTime.toFixed(2)} rate ${ctx.sampleRate} base latency ${((ctx.baseLatency || 0) * 1000).toFixed(0)} ms` : 'none'}, ` +
      `callbacks ${au.calls} (late ${au.late}, worst ${au.worstMs.toFixed(0)} ms, silent ${au.silent})`);
    au.worstMs = 0;
  }, 2000);
  // Heartbeat: shows whether the page is alive and the game drawing frames.
  let frames = 0;
  const countFrame = () => {
    frames++;
    requestAnimationFrame(countFrame);
  };
  requestAnimationFrame(countFrame);
  setInterval(() => {
    if (!started) return;
    const c = $('canvas');
    console.log(`alive: ${frames} frames, ${(loading.bytes / 2 ** 20).toFixed(1)} MB loaded, ${loading.pending} pending, canvas ${c.width}x${c.height}, heap ${typeof HEAPU8 !== 'undefined' ? (HEAPU8.length / 2 ** 20) | 0 : '?'} MB, visible ${document.visibilityState}`);
  }, 2000);
  addEventListener('pagehide', () => console.log('pagehide'));
  console.log(`debug: ${navigator.userAgent} gpu=${!!navigator.gpu} mem=${navigator.deviceMemory} screen=${screen.width}x${screen.height}@${devicePixelRatio}`);
}

// ?pipestats: how long creating GPU pipelines and shader modules takes (the
// call itself, which blocks the page, and until an async one is ready).
if (params.has('pipestats') && typeof GPUDevice !== 'undefined') {
  const st = { sync: 0, syncMs: 0, async: 0, asyncCallMs: 0, asyncReadyMs: 0, modules: 0, moduleMs: 0, maxCallMs: 0 };
  const P = GPUDevice.prototype;
  const wrap = (name, fn) => {
    const orig = P[name];
    P[name] = function (...a) {
      return fn.call(this, orig, a);
    };
  };
  wrap('createRenderPipeline', function (orig, a) {
    const t0 = performance.now();
    const r = orig.apply(this, a);
    const dt = performance.now() - t0;
    st.sync++, (st.syncMs += dt), (st.maxCallMs = Math.max(st.maxCallMs, dt));
    if (params.has('pipelog')) console.log(`[pipe] ${(t0 / 1000).toFixed(2)} sync ${dt.toFixed(1)} ms`);
    return r;
  });
  wrap('createRenderPipelineAsync', function (orig, a) {
    const t0 = performance.now();
    const p = orig.apply(this, a);
    const dt = performance.now() - t0;
    st.async++, (st.asyncCallMs += dt), (st.maxCallMs = Math.max(st.maxCallMs, dt));
    if (params.has('pipelog')) console.log(`[pipe] ${(t0 / 1000).toFixed(2)} async`);
    p.then(() => (st.asyncReadyMs += performance.now() - t0)).catch(() => {});
    return p;
  });
  wrap('createShaderModule', function (orig, a) {
    const code = a[0]?.code || '';
    st.codeBytes = (st.codeBytes || 0) + code.length;
    (st.codes ||= new Set()).add(code);
    if (params.has('pipelog')) console.log(`[module] ${st.modules + 1} unique ${st.codes.size}`);
    const t0 = performance.now();
    const r = orig.apply(this, a);
    st.modules++, (st.moduleMs += performance.now() - t0);
    return r;
  });
  setInterval(() => {
    const f = (n, ms) => (n ? `${n} (${ms.toFixed(0)} ms, ${(ms / n).toFixed(1)} each)` : '0');
    console.log(`[pipes] sync ${f(st.sync, st.syncMs)}, async calls ${f(st.async, st.asyncCallMs)} ready after ${(st.asyncReadyMs / Math.max(1, st.async)).toFixed(0)} ms avg, ` +
      `modules ${f(st.modules, st.moduleMs)} ${((st.codeBytes || 0) / Math.max(1, st.modules) / 1024).toFixed(1)} KB avg, longest call ${st.maxCallMs.toFixed(1)} ms`);
  }, 3000);
}

// ---- Disc access -----------------------------------------------------------

// Reads go through a block cache. readCached() answers synchronously when every
// byte is present; read() fetches the missing ones.
class Disc {
  constructor(size, fetchRange) {
    this.size = size;
    this.fetchRange = fetchRange; // (start, end, priority) -> Promise<ArrayBuffer>
    this.blocks = new Map(); // index -> Uint8Array, in LRU order
    this.pack = null; // a BootPack, when the site has one
  }

  touch(i) {
    const b = this.blocks.get(i);
    if (b) {
      this.blocks.delete(i);
      this.blocks.set(i, b);
    }
    return b;
  }

  // Copies [offset, offset + len) into out (when given) from the blocks and the
  // boot pack. Returns -1 when every byte is there, else the first missing one.
  gather(offset, len, out) {
    let pos = 0;
    while (pos < len) {
      const abs = offset + pos;
      const i = Math.floor(abs / BLOCK);
      const b = this.touch(i);
      let src = null;
      let from = 0;
      if (b) {
        src = b;
        from = abs - i * BLOCK;
      } else {
        const seg = this.pack?.find(abs);
        if (seg && abs < seg.start + seg.filled) {
          src = seg.buf.subarray(0, seg.filled);
          from = abs - seg.start;
        }
      }
      if (!src) return abs;
      const n = Math.min(src.length - from, len - pos);
      if (out) out.set(src.subarray(from, from + n), pos);
      pos += n;
    }
    return -1;
  }

  assemble(offset, len) {
    len = Math.max(0, Math.min(len, this.size - offset));
    if (this.gather(offset, len, null) >= 0) return null;
    const out = new Uint8Array(len);
    this.gather(offset, len, out);
    return out;
  }

  readCached(offset, len) {
    return this.assemble(offset, len);
  }

  // Calls this.outside(offset, len) when a read needs bytes the site's web
  // disc doesn't have (WebDisc), before fetching them from the full disc.
  checkKept(offset, len) {
    if (this.kept && len > 0 && !this.kept(offset, len)) this.outside(offset, len);
  }

  // True when [offset, offset + len) can be read without waiting; otherwise
  // starts fetching what's missing (once) and returns false. The game's
  // asynchronous reads wait on this instead of stalling every thread on a
  // network round trip (port/src/dvd_irq.c).
  prefetch(offset, len) {
    len = Math.max(0, Math.min(len, this.size - offset));
    if (this.gather(offset, len, null) < 0) return true;
    this.checkKept(offset, len);
    this.inflight ??= new Set();
    const first = Math.floor(offset / BLOCK);
    const last = Math.floor((offset + len - 1) / BLOCK);
    for (let i = first; i <= last; i++) {
      if (this.blocks.has(i) || this.inflight.has(i) || this.pack?.pending(i * BLOCK)) continue;
      let j = i;
      while (j + 1 <= last && !this.blocks.has(j + 1) && !this.inflight.has(j + 1) && !this.pack?.pending((j + 1) * BLOCK)) j++;
      const a = i;
      const b = j;
      for (let k = a; k <= b; k++) this.inflight.add(k);
      const start = a * BLOCK;
      const end = Math.min((b + 1) * BLOCK, this.size);
      const t0 = performance.now();
      this.fetchRange(start, end, 'high')
        .then((buf) => {
          const data = new Uint8Array(buf);
          for (let k = a; k <= b; k++) {
            const s = (k - a) * BLOCK;
            this.blocks.set(k, data.slice(s, Math.min(s + BLOCK, data.length)));
          }
          while (this.blocks.size > MAX_BLOCKS) this.blocks.delete(this.blocks.keys().next().value);
          if (params.has('stats') || params.has('debug'))
            console.log(`[disc] prefetched ${end - start} bytes at ${start} in ${(performance.now() - t0).toFixed(0)} ms`);
        })
        .catch((e) => console.warn('disc prefetch failed', e))
        .finally(() => {
          for (let k = a; k <= b; k++) this.inflight.delete(k);
        });
      i = j;
    }
    return false;
  }

  async read(offset, len, priority = 'high') {
    len = Math.max(0, Math.min(len, this.size - offset));
    const first = Math.floor(offset / BLOCK);
    const last = Math.floor((offset + len - 1) / BLOCK);
    for (;;) {
      const gap = this.gather(offset, len, null);
      if (gap < 0) break;
      this.checkKept(offset, len);
      // Bytes the boot pack is still bringing: wait for them rather than
      // fetch their blocks too.
      if (this.pack?.pending(gap)) {
        loading.busy(1);
        try {
          await this.pack.next();
        } finally {
          loading.busy(-1);
        }
        continue;
      }
      // The run of missing blocks from the gap on, in one fetch.
      const i = Math.floor(gap / BLOCK);
      let j = i;
      while (j + 1 <= last && !this.blocks.has(j + 1) && !this.pack?.pending((j + 1) * BLOCK)) j++;
      const start = i * BLOCK;
      const end = Math.min((j + 1) * BLOCK, this.size);
      const t0 = performance.now();
      const data = new Uint8Array(await this.fetchRange(start, end, priority));
      if (params.has('stats') || params.has('debug'))
        console.log(`[disc] miss ${offset}+${len}: fetched ${end - start} bytes at ${start} in ${(performance.now() - t0).toFixed(0)} ms`);
      for (let k = i; k <= j; k++) {
        const s = (k - i) * BLOCK;
        this.blocks.set(k, data.slice(s, Math.min(s + BLOCK, data.length)));
      }
    }
    while (this.blocks.size > MAX_BLOCKS + (last - first + 1)) {
      this.blocks.delete(this.blocks.keys().next().value);
    }
    return this.assemble(offset, len);
  }
}

// The bytes boot reads up to the main menu, as one stream in the order the game
// first needs them (disc/<id>/boot-<hash>.pack: see port/tools/record_boot_pack.mjs).
// Segments fill in as the stream arrives; reads can use a segment's bytes
// before the rest of it is there.
class BootPack {
  constructor(segments) {
    this.segs = segments.map(([start, len]) => ({ start, end: start + len, buf: null, filled: 0 }));
    this.byStart = [...this.segs].sort((a, b) => a.start - b.start); // disjoint
    this.done = false;
    this.waiters = [];
  }

  find(abs) {
    let lo = 0;
    let hi = this.byStart.length - 1;
    while (lo <= hi) {
      const mid = (lo + hi) >> 1;
      const s = this.byStart[mid];
      if (abs < s.start) hi = mid - 1;
      else if (abs >= s.end) lo = mid + 1;
      else return s;
    }
    return null;
  }

  // Whether the stream will still bring this byte.
  pending(abs) {
    if (this.done) return false;
    const s = this.find(abs);
    return !!s && abs >= s.start + s.filled;
  }

  // Resolves when more of the stream arrives, or it ends.
  next() {
    return new Promise((r) => this.waiters.push(r));
  }

  wake() {
    const w = this.waiters;
    this.waiters = [];
    for (const r of w) r();
  }

  // Phone connections drop and stall: a broken stream picks up where it left
  // off (a Range request), and after a few failures the reads it would have
  // covered fetch their own blocks.
  async stream(url) {
    const total = this.segs.reduce((n, s) => n + s.end - s.start, 0);
    loading.total = total;
    let got = 0;
    let seg = 0;
    for (let attempt = 0; got < total; ) {
      const abort = new AbortController();
      let timer = setTimeout(() => abort.abort(), STALL_MS);
      try {
        const r = await fetch(url, { signal: abort.signal, headers: got ? { Range: `bytes=${got}-` } : {} });
        if (!r.ok) throw new Error(`HTTP ${r.status}`);
        let skip = got && r.status !== 206 ? got : 0; // the server sent it all again
        const reader = r.body.getReader();
        for (;;) {
          const { done, value } = await reader.read();
          if (done) break;
          clearTimeout(timer);
          timer = setTimeout(() => abort.abort(), STALL_MS);
          let v = value;
          if (skip) {
            const k = Math.min(skip, v.length);
            v = v.subarray(k);
            skip -= k;
          }
          for (let p = 0; p < v.length && seg < this.segs.length; ) {
            const s = this.segs[seg];
            if (!s.buf) s.buf = new Uint8Array(s.end - s.start);
            const n = Math.min(v.length - p, s.buf.length - s.filled);
            s.buf.set(v.subarray(p, p + n), s.filled);
            s.filled += n;
            p += n;
            got += n;
            if (s.filled === s.buf.length) seg++;
          }
          loading.bytes += v.length;
          this.wake();
        }
        if (got < total) throw new Error('ended early');
      } catch (e) {
        if (++attempt > 5) break;
        console.warn(`boot pack: ${abort.signal.aborted ? 'stalled' : e.message} at ${got} of ${total} bytes; retrying (${attempt})`);
        await new Promise((r) => setTimeout(r, Math.min(500 * 2 ** attempt, 5000)));
      } finally {
        clearTimeout(timer);
      }
    }
    if (params.has('debug')) console.log(`boot pack: ${got} of ${total} bytes`);
    this.done = true;
    this.wake();
  }
}

function fileDisc(file) {
  return new Disc(file.size, (start, end) => file.slice(start, end).arrayBuffer());
}

async function urlDisc(url) {
  const head = await fetch(url, { method: 'HEAD' });
  if (!head.ok) throw new Error(`Couldn't load ${url} (${head.status})`);
  const size = Number(head.headers.get('Content-Length'));
  const disc = new Disc(size, async (start, end) => {
    const r = await fetch(url, { headers: { Range: `bytes=${start}-${end - 1}` } });
    if (r.status !== 206) throw new Error(`disc read failed (${r.status})`);
    return r.arrayBuffer();
  });
  const first = await disc.read(0, 0x8020);
  disc.gameId = await readGameId(new Blob([first]));
  return disc;
}

// tools/web_serve.mjs offers the repo's disc image at disc.iso.
async function serverDisc() {
  try {
    const disc = await urlDisc('disc.iso');
    return disc.gameId === GAME_ID ? disc : null;
  } catch {
    return null;
  }
}

// The deployed site carries the disc as chunks under disc/ (see
// port/cloudflare/src/worker.js), readable once this browser has unlocked them.
// One disc chunk from the site. Phone connections drop and stall, and the game
// can't go on without the data, so a chunk that fails, or gets no bytes for
// STALL_MS, is fetched again (after a pause that grows to a few seconds).
const STALL_MS = 15000;
async function fetchChunk(url, priority, counter = loading) {
  for (let attempt = 0; ; attempt++) {
    const abort = new AbortController();
    let timer = setTimeout(() => abort.abort(), STALL_MS);
    const alive = () => {
      clearTimeout(timer);
      timer = setTimeout(() => abort.abort(), STALL_MS);
    };
    let got = 0;
    try {
      const r = await fetch(url, { signal: abort.signal, priority });
      if (r.status === 401) throw Object.assign(new Error('disc locked'), { fatal: true });
      if (r.status === 404) throw Object.assign(new Error('not on the site'), { fatal: true });
      if (!r.ok) throw new Error(`HTTP ${r.status}`);
      const parts = [];
      const reader = r.body.getReader();
      for (;;) {
        const { done, value } = await reader.read();
        if (done) break;
        alive();
        parts.push(value);
        got += value.length;
        counter.bytes += value.length;
      }
      const out = new Uint8Array(got);
      let pos = 0;
      for (const v of parts) {
        out.set(v, pos);
        pos += v.length;
      }
      return out.buffer;
    } catch (e) {
      counter.bytes -= got;
      if (e.fatal) throw e;
      console.warn(`disc chunk ${url}: ${abort.signal.aborted ? 'stalled' : e.message}; retrying (${attempt + 1})`);
      await new Promise((r) => setTimeout(r, Math.min(500 * 2 ** attempt, 5000)));
    } finally {
      clearTimeout(timer);
    }
  }
}

// Returns the disc, 'locked', or null when the site has no disc.
async function siteDisc() {
  let manifest;
  try {
    const r = await fetch('disc/manifest.json', { credentials: 'same-origin' });
    if (r.status === 401) return 'locked';
    if (!r.ok || !(r.headers.get('Content-Type') || '').includes('json')) return null;
    manifest = await r.json();
  } catch {
    return null;
  }
  const { size, chunk, dir } = manifest;
  const letters = (i) => String.fromCharCode(97 + Math.floor(i / 676), 97 + (Math.floor(i / 26) % 26), 97 + (i % 26));
  const chunkUrl = (i) => `disc/${dir}/${letters(i)}`;
  const web = manifest.web && chunk === BLOCK ? await WebDisc.open(manifest, chunkUrl) : null;
  const recent = new Map(); // a few whole chunks, in case they're bigger than a block
  // background: the web disc's download (not the game waiting).
  const loadChunk = (i, priority = 'high', background = false) => {
    let p = recent.get(i);
    if (!p) {
      if (!background) loading.busy(1);
      p = (async () => {
        const stored = await web?.get(i);
        if (stored) return stored;
        if (web?.only && !web.keep.has(i)) return new ArrayBuffer(chunk); // not deployed: see WebDisc
        const data = await fetchChunk(chunkUrl(i), priority, background ? web.progress : loading);
        web?.put(i, data);
        return data;
      })().finally(() => background || loading.busy(-1));
      p.catch(() => recent.delete(i));
      recent.set(i, p);
      if (recent.size > 16) recent.delete(recent.keys().next().value);
    }
    return p;
  };
  const disc = new Disc(size, async (start, end, priority) => {
    const out = new Uint8Array(end - start);
    const parts = [];
    for (let i = Math.floor(start / chunk); i * chunk < end; i++) parts.push(i);
    const datas = await Promise.all(parts.map((i) => loadChunk(i, priority))); // in parallel
    parts.forEach((i, k) => {
      const data = new Uint8Array(datas[k]);
      const from = Math.max(start, i * chunk);
      const to = Math.min(end, (i + 1) * chunk);
      out.set(data.subarray(from - i * chunk, to - i * chunk), from - start);
    });
    return out.buffer;
  });
  let boot = Promise.resolve();
  if (web) {
    disc.kept = (offset, len) => web.covers(offset, len);
    disc.outside = (offset, len) => web.outside(disc, offset, len);
  }
  if (manifest.boot && !web?.hasAll(manifest.boot.segments)) {
    disc.pack = new BootPack(manifest.boot.segments);
    boot = disc.pack.stream(`disc/${dir}/${manifest.boot.file}`);
  } else if (manifest.boot) {
    // Everything boot reads is already in this browser: bring it into memory
    // in the order the game wants it.
    for (const [start, len] of manifest.boot.segments) disc.prefetch(start, len);
  }
  disc.gameId = await readGameId(new Blob([await disc.read(0, 0x8020)]));
  if (disc.gameId !== GAME_ID) return null;
  // The rest of the web disc comes after the boot pack, in the background.
  if (web && !params.has('nosave')) boot.then(() => web.download(loadChunk));
  return disc;
}

// The web disc: the disc chunks the web build can reach (manifest "web", from
// port/tools/web_disc.py). They download once, in the background, into the
// browser's Cache API storage, and every later visit reads them from there, so
// play needs no network. A read outside them is fetched from the full disc and
// logged (under ?debug it reaches the site's log, with the disc file it's in):
// that's a gap in the keep-list. When the deploy leaves the rest of the disc
// out (manifest "web.only"), such a read gets zeros instead.
class WebDisc {
  static async open(manifest, chunkUrl) {
    const web = new WebDisc(manifest, chunkUrl);
    if (typeof caches === 'undefined') return web; // not a secure context: no storage, still logs gaps
    try {
      const name = `mssb-disc-${manifest.dir}`;
      for (const k of await caches.keys()) if (k.startsWith('mssb-disc-') && k !== name) await caches.delete(k); // an older disc
      web.cache = await caches.open(name);
      for (const req of await web.cache.keys()) {
        const i = web.index.get(new URL(req.url).pathname.split('/').pop());
        if (i !== undefined) web.have.add(i);
      }
    } catch (e) {
      console.warn("Couldn't open the browser's storage for the game data; it'll stream instead.", e);
      web.cache = null;
    }
    return web;
  }

  constructor(manifest, chunkUrl) {
    this.chunk = manifest.chunk;
    this.keep = new Set(manifest.web.chunks);
    this.only = !!manifest.web.only;
    this.chunkUrl = chunkUrl;
    this.index = new Map(manifest.web.chunks.map((i) => [chunkUrl(i).split('/').pop(), i]));
    this.cache = null;
    this.have = new Set(); // chunks in storage
    this.progress = { bytes: 0 }; // downloaded this visit
    this.reported = new Set(); // chunks outside the web disc already logged
    this.misses = []; // [offset, len] of reads outside it (tools read window.mssbWebDiscMisses)
    window.mssbWebDiscMisses = this.misses;
  }

  covers(offset, len) {
    for (let i = Math.floor(offset / this.chunk); i * this.chunk < offset + len; i++) if (!this.keep.has(i)) return false;
    return true;
  }

  hasAll(segments) {
    if (!this.cache) return false;
    for (const [start, len] of segments)
      for (let i = Math.floor(start / this.chunk); i * this.chunk < start + len; i++) if (!this.have.has(i)) return false;
    return true;
  }

  async get(i) {
    if (!this.have.has(i)) return null;
    try {
      const r = await this.cache.match(this.chunkUrl(i));
      if (r) return await r.arrayBuffer();
    } catch {}
    this.have.delete(i); // evicted
    return null;
  }

  put(i, data) {
    if (!this.cache || this.full || !this.keep.has(i) || this.have.has(i)) return;
    this.have.add(i);
    this.cache.put(this.chunkUrl(i), new Response(data)).catch((e) => {
      this.have.delete(i);
      if (!this.full) console.warn(`Couldn't keep the game data in this browser (${e.name}); it'll stream instead.`, e);
      this.full = true;
    });
  }

  // Downloads what's missing, a few chunks at a time, at low priority.
  async download(loadChunk) {
    if (!this.cache) return;
    const todo = [...this.keep].filter((i) => !this.have.has(i)).sort((a, b) => a - b);
    const total = this.keep.size * this.chunk;
    const status = () => {
      const done = this.have.size === this.keep.size;
      const mb = (n) => (n / 2 ** 20).toFixed(0);
      const text = done ? '' : `Saving game data to this device: ${mb(this.have.size * this.chunk)} / ${mb(total)} MB`;
      $('save-status').hidden = !text;
      $('save-status').textContent = text;
      $('save-progress').hidden = !text || !started;
      $('save-progress').textContent = text && `Saving game data ${Math.floor((100 * this.have.size) / this.keep.size)}%`;
    };
    status();
    const log = params.has('debug') || params.has('stats');
    if (!todo.length) {
      if (log) console.log(`[web disc] ${this.have.size} of ${this.keep.size} chunks kept, all already in this browser`);
      return;
    }
    navigator.storage?.persist?.().catch(() => {});
    const t0 = performance.now();
    const timer = setInterval(status, 1000);
    // Three at a time until Play is pressed. Once the game runs, one at a
    // time, and none while the game is waiting for disc data itself: a phone's
    // connection and main thread are shared with the game (and its music).
    const sleep = (ms) => new Promise((r) => setTimeout(r, ms));
    const worker = async (onlyBeforePlay) => {
      while (todo.length && !this.full && !(onlyBeforePlay && started)) {
        while (started && loading.pending > 0) await sleep(100);
        const i = todo.shift();
        if (i === undefined) break;
        if (this.have.has(i)) continue;
        try {
          await loadChunk(i, 'low', true);
        } catch (e) {
          console.warn(`game data download: chunk ${i}: ${e.message}`);
        }
      }
    };
    await Promise.all([worker(false), worker(true), worker(true)]);
    clearInterval(timer);
    status();
    if (log)
      console.log(`[web disc] ${this.have.size} of ${this.keep.size} chunks kept, ${(this.progress.bytes / 2 ** 20).toFixed(1)} MB downloaded in ${((performance.now() - t0) / 1000).toFixed(1)} s${this.full ? ' (storage full)' : ''}`);
  }

  // A read the web disc doesn't cover: logged once per chunk, with the disc
  // file and offset it's in.
  async outside(disc, offset, len) {
    this.misses.push([offset, len]);
    const i = Math.floor(offset / this.chunk);
    if (this.reported.has(i)) return;
    this.reported.add(i);
    let where = '';
    try {
      where = ` (${await describeImageOffset(disc, offset)})`;
    } catch {}
    console.error(`[web disc] read outside the web disc: ${offset}+${len}, chunk ${i}${where}${this.only ? '; not deployed, reads zeros' : '; fetching it from the full disc'}`);
  }
}

// "ZZZZ.dat +0x1234" for an offset in the image file (plain or CISO).
async function describeImageOffset(disc, offset) {
  const head = await disc.read(0, 0x8000);
  let discOffset = offset;
  if (String.fromCharCode(...head.subarray(0, 4)) === 'CISO') {
    const blockSize = new DataView(head.buffer, head.byteOffset).getUint32(4, true);
    const used = Math.floor((offset - 0x8000) / blockSize);
    let n = 0;
    discOffset = -1;
    for (let b = 0; b < 0x8000 - 8; b++) {
      if (!head[8 + b]) continue;
      if (n++ === used) {
        discOffset = b * blockSize + ((offset - 0x8000) % blockSize);
        break;
      }
    }
    if (offset < 0x8000 || discOffset < 0) return 'CISO header';
  }
  const read = await discReader(disc);
  const dv = (b) => new DataView(b.buffer, b.byteOffset);
  const hdr = dv(await read(0x424, 8));
  const fst = await read(hdr.getUint32(0), hdr.getUint32(4));
  const f = dv(fst);
  const count = f.getUint32(8);
  const names = 12 * count;
  for (let k = 1; k < count; k++) {
    if (fst[k * 12]) continue; // a directory
    const at = f.getUint32(k * 12 + 4);
    const n = f.getUint32(k * 12 + 8);
    if (discOffset >= at && discOffset < at + n) {
      const nameAt = names + (f.getUint32(k * 12) & 0xffffff);
      const name = String.fromCharCode(...fst.subarray(nameAt, fst.indexOf(0, nameAt)));
      return `${name} +0x${(discOffset - at).toString(16)}`;
    }
  }
  return `disc 0x${discOffset.toString(16)}, system area`;
}

async function unlockSite(password) {
  const r = await fetch('disc/unlock', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ password }),
  });
  return r.ok;
}

// Plain GameCube images and CISO (compressed ISO: a 0x8000-byte block map,
// then the used blocks; the game reads it through port/web/src/web_platform.cpp).
async function readGameId(blob) {
  let head = new Uint8Array(await blob.slice(0, 0x20).arrayBuffer());
  if (String.fromCharCode(...head.subarray(0, 4)) === 'CISO') head = new Uint8Array(await blob.slice(0x8000, 0x8020).arrayBuffer());
  const id = String.fromCharCode(...head.subarray(0, 6));
  const gcMagic = head[0x1c] === 0xc2 && head[0x1d] === 0x33 && head[0x1e] === 0x9f && head[0x1f] === 0x3d;
  return gcMagic ? id : null;
}

// ---- Stored disc (OPFS) ----------------------------------------------------

async function opfsRoot() {
  try {
    return await navigator.storage.getDirectory();
  } catch {
    return null;
  }
}

async function storedDisc() {
  const root = await opfsRoot();
  if (!root) return null;
  try {
    const file = await (await root.getFileHandle(DISC_NAME)).getFile();
    const done = await (await (await root.getFileHandle(DISC_DONE)).getFile()).text();
    return Number(done) === file.size && (await readGameId(file)) === GAME_ID ? file : null;
  } catch {
    return null;
  }
}

async function storeDisc(file, onProgress) {
  const root = await opfsRoot();
  if (!root) return file;
  try {
    navigator.storage.persist?.();
    await root.removeEntry(DISC_DONE).catch(() => {});
    const handle = await root.getFileHandle(DISC_NAME, { create: true });
    const writable = await handle.createWritable();
    let done = 0;
    const reader = file.stream().getReader();
    for (;;) {
      const { value, done: end } = await reader.read();
      if (end) break;
      await writable.write(value);
      done += value.length;
      onProgress(done / file.size);
    }
    await writable.close();
    const stored = await handle.getFile();
    if (stored.size !== file.size) throw new Error('incomplete copy');
    const marker = await (await root.getFileHandle(DISC_DONE, { create: true })).createWritable();
    await marker.write(String(stored.size));
    await marker.close();
    return stored;
  } catch (e) {
    console.warn("Couldn't keep a copy of the disc; it'll need choosing again next time.", e);
    try {
      await root.removeEntry(DISC_NAME);
    } catch {}
    return file;
  }
}

async function forgetDisc() {
  const root = await opfsRoot();
  for (const name of [DISC_DONE, DISC_NAME]) {
    try {
      await root?.removeEntry(name);
    } catch {}
  }
}

// ---- UI --------------------------------------------------------------------

// The "Loading…" badge over the game: shown while the game waits for its code
// or for disc data from the site (slow on phones), after a short delay so
// quick reads don't flash it.
const loading = {
  pending: 0,
  bytes: 0,
  total: 0, // the boot pack's size (BootPack)
  shown: false,
  showTimer: null,
  hideTimer: null,
  busy(delta) {
    this.pending += delta;
    this.update();
  },
  update() {
    const el = $('load-status');
    const busy = started && (!runtimeReady || this.pending > 0);
    if (busy) {
      clearTimeout(this.hideTimer);
      this.hideTimer = null;
      const mb = (n) => (n / 2 ** 20).toFixed(0);
      $('load-text').textContent = !runtimeReady
        ? 'Loading game…'
        : this.bytes < this.total
          ? `Loading… ${mb(this.bytes)} / ${mb(this.total)} MB`
          : `Loading… ${mb(this.bytes)} MB`;
      if (!this.shown && !this.showTimer) {
        this.showTimer = setTimeout(() => {
          this.showTimer = null;
          el.hidden = false;
          this.shown = true;
        }, 300);
      }
    } else {
      clearTimeout(this.showTimer);
      this.showTimer = null;
      if (this.shown && !this.hideTimer) {
        this.hideTimer = setTimeout(() => {
          this.hideTimer = null;
          this.shown = false;
          el.hidden = true;
        }, 500);
      }
    }
  },
};

function show(id) {
  if (params.has('debug')) console.log(`panel ${id}`);
  for (const el of document.querySelectorAll('.panel')) el.hidden = el.id !== id;
  $('overlay').hidden = false;
  MssbPad.setActive(id === 'panel-play');
}

function fatal(message) {
  $('error-text').textContent = message;
  show('panel-error');
  document.body.classList.remove('playing');
}

function unsupportedReason() {
  if (!navigator.gpu) return 'This browser has no WebGPU.';
  return null;
}

// One build (Asyncify: the game's OS threads are fibers).
const BUILD_DIR = '';

async function chooseFile(file) {
  if (!file) return;
  const id = await readGameId(file);
  if (id !== GAME_ID) {
    $('pick-error').textContent = id
      ? `That's a different GameCube game (${id}). This needs Mario Superstar Baseball (USA), ${GAME_ID}.`
      : "That doesn't look like a GameCube disc image (.iso / .gcm / .ciso).";
    return;
  }
  $('pick-error').textContent = '';
  show('panel-copy');
  const stored = await storeDisc(file, (f) => {
    $('copy-bar').style.width = `${(f * 100).toFixed(1)}%`;
  });
  showPlay('Disc ready.', fileDisc(stored));
}

// user.ini, read by the game at boot (see port/README.md). Test hooks:
// ?skipfe starts straight in an exhibition game; ?captain1=, ?captain2=,
// ?team1=, ?team2= (other players, comma-separated), ?stadium=, ?innings= pick it. Movies are always skipped; ?movies plays them.
function writeUserIni() {
  if (Module.mssbUserIni) {
    FS.writeFile('/tmp/user.ini', Module.mssbUserIni); // an online game's settings (net.js)
    return;
  }
  const ini = [];
  if (params.has('skipfe')) ini.push('skipfe = true');
  for (const k of ['captain1', 'captain2', 'team1', 'team2', 'stadium', 'innings']) if (params.has(k)) ini.push(`${k} = ${params.get(k)}`);
  FS.writeFile('/tmp/user.ini', ini.join('\n') + '\n');
}

function showPlay(text, disc) {
  show('panel-play');
  $('play-name').textContent = text;
  $('play').onclick = () => start(disc);
  $('online').onclick = () => showJoin(disc);
  $('practice').onclick = () => showPractice(disc);
  if (params.has('room') && params.has('autojoin')) joinRoom(disc, params.get('room'), params.get('name') || 'Player');
  else if (params.has('room')) showJoin(disc); // a friend's invite link
  else if (params.has('practice')) {
    // Test hook: ?practice=RTT,JITTER,LOSS starts a practice game right away.
    const [rtt, jitter, loss] = (params.get('practice') || '100,10,0.02').split(',').map(Number);
    startPractice(disc, { rtt, jitter, loss, captain1: 'mario', captain2: 'bowser', stadium: 'mario', innings: Number(params.get('innings')) || 3 });
  } else if (params.has('autostart')) start(disc);
}

// ---- Online play (net.js) ---------------------------------------------------

const NAME_KEY = 'mssb.netName';
const CAPTAIN_NAMES = { mario: 'Mario', luigi: 'Luigi', peach: 'Peach', daisy: 'Daisy', yoshi: 'Yoshi', birdo: 'Birdo',
  wario: 'Wario', waluigi: 'Waluigi', dk: 'Donkey Kong', diddy: 'Diddy Kong', bowser: 'Bowser', bowserjr: 'Bowser Jr.' };
const STADIUM_NAMES = { mario: 'Mario Stadium', peach: 'Peach Garden', yoshi: 'Yoshi Park', dk: 'DK Jungle',
  wario: 'Wario City', bowser: 'Bowser Castle' };
const INNINGS = [[1, '1 inning'], [3, '3 innings'], [5, '5 innings'], [7, '7 innings'], [9, '9 innings']];
const captainOptions = () => MssbNet.CAPTAINS.map((c) => [c, CAPTAIN_NAMES[c]]);
const stadiumOptions = () => MssbNet.STADIUMS.map((c) => [c, STADIUM_NAMES[c]]);

function hex(buf) {
  return [...new Uint8Array(buf)].map((b) => b.toString(16).padStart(2, '0')).join('');
}

async function digest(bytes) {
  if (crypto.subtle) return hex(await crypto.subtle.digest('SHA-256', bytes)).slice(0, 16);
  let h = 2166136261; // no crypto.subtle outside secure contexts: FNV-1a
  for (const b of bytes) h = Math.imul(h ^ b, 16777619) >>> 0;
  return h.toString(16);
}

// Players must run the same build on the same disc revision, or they desync.
// The disc's identity is its header and file table (read through the CISO
// block map when it's compressed, so a .ciso and an .iso of one disc match).
async function netIdentity(disc) {
  const wasm = new Uint8Array(await (await fetch(`${BUILD_DIR}mssb.wasm`, { cache: 'force-cache' })).arrayBuffer());
  const read = await discReader(disc);
  const header = await read(0, 0x440);
  const dv = new DataView(header.buffer, header.byteOffset);
  const fst = await read(dv.getUint32(0x424), Math.min(dv.getUint32(0x428), 1 << 20));
  const discBytes = new Uint8Array(header.length + fst.length);
  discBytes.set(header);
  discBytes.set(fst, header.length);
  return { build: await digest(wasm), disc: await digest(discBytes) };
}

// read(offset, len) in the disc's own address space, for plain and CISO images.
async function discReader(disc) {
  const magic = await disc.read(0, 8);
  if (String.fromCharCode(...magic.subarray(0, 4)) !== 'CISO') return (o, n) => disc.read(o, n);
  const head = await disc.read(0, 0x8000);
  const blockSize = new DataView(head.buffer, head.byteOffset).getUint32(4, true);
  const map = [];
  let used = 0;
  for (let i = 0; i < 0x8000 - 8; i++) map.push(head[8 + i] ? used++ : -1);
  return async (offset, len) => {
    const out = new Uint8Array(len);
    for (let pos = 0; pos < len; ) {
      const b = Math.floor((offset + pos) / blockSize);
      const within = (offset + pos) % blockSize;
      const n = Math.min(blockSize - within, len - pos);
      if (map[b] >= 0) out.set(await disc.read(0x8000 + map[b] * blockSize + within, n), pos);
      pos += n;
    }
    return out;
  };
}

// Practice: a solo lockstep game against a simulated remote player (net.js).
const PRACTICE_KEY = 'mssb.practice';
const PRACTICE_OPTIONS = {
  rtt: [[0, 'LAN (0 ms)'], [30, '30 ms'], [60, '60 ms'], [100, '100 ms'], [150, '150 ms'], [250, '250 ms']],
  jitter: [[0, 'None'], [10, '10 ms'], [30, '30 ms'], [60, '60 ms']],
  loss: [[0, 'None'], [0.02, '2%'], [0.05, '5%'], [0.1, '10%'], [0.2, '20%']],
};

function practiceDelay(rtt, jitter) {
  return Math.min(10, Math.max(3, Math.ceil((rtt / 2 + 2 * jitter) / (1000 / 60)) + 1));
}

function showPractice(disc) {
  show('panel-practice');
  let saved = {};
  try {
    saved = JSON.parse(localStorage.getItem(PRACTICE_KEY) || '{}');
  } catch {}
  fillSelect($('pr-rtt'), PRACTICE_OPTIONS.rtt, saved.rtt ?? 100);
  fillSelect($('pr-jitter'), PRACTICE_OPTIONS.jitter, saved.jitter ?? 10);
  fillSelect($('pr-loss'), PRACTICE_OPTIONS.loss, saved.loss ?? 0.02);
  fillSelect($('pr-captain1'), captainOptions(), saved.captain1 || 'mario');
  fillSelect($('pr-captain2'), captainOptions(), saved.captain2 || 'bowser');
  fillSelect($('pr-stadium'), stadiumOptions(), saved.stadium || 'mario');
  fillSelect($('pr-innings'), INNINGS, saved.innings || 3);
  const read = () => ({
    rtt: Number($('pr-rtt').value), jitter: Number($('pr-jitter').value), loss: Number($('pr-loss').value),
    captain1: $('pr-captain1').value, captain2: $('pr-captain2').value, stadium: $('pr-stadium').value,
    innings: Number($('pr-innings').value),
  });
  const update = () => {
    const o = read();
    const d = practiceDelay(o.rtt, o.jitter);
    $('pr-delay').textContent = `Input delay: ${d} frames (${Math.round((d * 1000) / 60)} ms), the same rule an online game uses.`;
    try {
      localStorage.setItem(PRACTICE_KEY, JSON.stringify(o));
    } catch {}
  };
  for (const id of ['pr-rtt', 'pr-jitter', 'pr-loss', 'pr-captain1', 'pr-captain2', 'pr-stadium', 'pr-innings']) $(id).onchange = update;
  update();
  $('pr-back').onclick = () => show('panel-play');
  $('pr-start').onclick = () => startPractice(disc, read());
}

function startPractice(disc, o) {
  const ui = {
    waiting: (text) => {
      $('net-status').hidden = !text;
      $('net-status').textContent = text || '';
    },
    stopped: (msg) => fatal(msg),
  };
  const cfg = { captain1: o.captain1, captain2: o.captain2, stadium: o.stadium, innings: o.innings };
  const { match, lockstep } = MssbNet.startPractice({ net: { rtt: o.rtt, jitter: o.jitter, loss: o.loss }, cfg, ui });
  showNetStats(lockstep, `ping ${o.rtt} ms ±${o.jitter}, loss ${Math.round(o.loss * 100)}%`);
  launchNetGame(disc, match, 0, lockstep);
}

// Live numbers in the corner: input delay, stalls, frame rate.
function showNetStats(lockstep, label) {
  const el = $('net-stats');
  el.hidden = false;
  let last = { t: performance.now(), frame: 0, stalls: 0, stallMs: 0 };
  setInterval(() => {
    const now = performance.now();
    const fps = ((lockstep.frame - last.frame) * 1000) / (now - last.t);
    const stalls = lockstep.stallCount - last.stalls;
    const stallMs = lockstep.stallMs - last.stallMs;
    last = { t: now, frame: lockstep.frame, stalls: lockstep.stallCount, stallMs: lockstep.stallMs };
    el.textContent = `${label}\ndelay ${lockstep.delay} frames (${Math.round((lockstep.delay * 1000) / 60)} ms) · ${fps.toFixed(0)} fps\n` +
      `stalls ${stalls}/s (${Math.round(stallMs)} ms) · total ${lockstep.stallCount}`;
  }, 1000);
}

function launchNetGame(disc, match, localPort, lockstep) {
  Module.mssbUserIni = MssbNet.onlineUserIni(match);
  Module.mssbNet = {
    localPort,
    activeMask: match.activeMask,
    delay: match.delay,
    lockstep,
    sendLocal: (f, b) => lockstep.sendLocal(f, b),
    inputsFor: (f) => lockstep.inputsFor(f),
    wait: (f) => lockstep.wait(f),
    localHash: (f, h) => lockstep.localHash(f, h),
    stalled: (f, on) => lockstep.stalled(f, on),
  };
  start(disc);
}

function showJoin(disc) {
  show('panel-join');
  try {
    $('net-name').value = localStorage.getItem(NAME_KEY) || '';
  } catch {}
  $('net-room').value = params.get('room') || '';
  $('net-error').textContent = '';
  const go = (room) => {
    const name = $('net-name').value.trim() || 'Player';
    try {
      localStorage.setItem(NAME_KEY, name);
    } catch {}
    if (!room) {
      $('net-error').textContent = 'Enter the room code your friend sent you.';
      return;
    }
    joinRoom(disc, room, name);
  };
  $('net-join').onclick = () => go($('net-room').value.trim().toUpperCase());
  $('net-create').onclick = () => {
    const abc = 'ABCDEFGHJKLMNPQRSTUVWXYZ23456789';
    go([...crypto.getRandomValues(new Uint8Array(5))].map((b) => abc[b % abc.length]).join(''));
  };
  $('net-back').onclick = () => show('panel-play');
}

function fillSelect(sel, entries, value) {
  if (!sel.options.length) {
    for (const [v, label] of entries) sel.add(new Option(label, v));
  }
  sel.value = String(value);
  if (sel.selectedIndex < 0) sel.selectedIndex = 0; // a saved choice that's no longer offered
}

async function joinRoom(disc, room, name) {
  show('panel-room');
  $('room-code').textContent = room;
  $('room-status').textContent = 'Connecting…';
  const shareUrl = new URL(location.href);
  shareUrl.search = `?room=${encodeURIComponent(room)}`;
  $('room-share').textContent = `Your friend joins with code ${room}, or at ${shareUrl}`;
  let identity;
  try {
    identity = await netIdentity(disc);
  } catch (e) {
    fatal(`Couldn't check the game files: ${e.message}`);
    return;
  }
  const hostStart = Number(params.get('hoststart')) || 0;
  const ui = {
    wantedPort: params.has('port') ? Number(params.get('port')) : undefined,
    render: (mesh) => renderRoom(mesh, hostStart),
    error: (msg) => {
      if (started) fatal(msg);
      else {
        show('panel-join');
        $('net-error').textContent = msg;
      }
    },
    waiting: (text) => {
      $('net-status').hidden = !text;
      $('net-status').className = '';
      $('net-status').textContent = text || '';
    },
    stopped: (msg) => fatal(msg),
    startGame: (match, localPort, lockstep) => {
      if (params.has('netstats')) showNetStats(lockstep, 'online');
      launchNetGame(disc, match, localPort, lockstep);
    },
  };
  // Test hook: ?netsim=LOSS,LAG,JITTER (e.g. 0.05,40,20) degrades incoming input packets.
  const [loss, lag, jitter] = (params.get('netsim') || '').split(',').map(Number);
  const netSim = params.has('netsim') ? { loss: loss || 0, lag: lag || 0, jitter: jitter || 0 } : null;
  // ?signal=URL/ uses another server's signaling (e.g. the deployed one while testing locally).
  const signalBase = params.get('signal') || '';
  const mesh = new MssbNet.Mesh({ room, name, identity, ui, relayOnly: params.has('relay'), netSim, signalBase });
  window.mssbMesh = mesh;
  if (params.has('innings')) mesh.lobby.cfg.innings = Number(params.get('innings')) || 3; // test hook (host's choice)
  for (const k of ['captain1', 'captain2', 'stadium', 'innings']) {
    $(`cfg-${k}`).onchange = (e) => mesh.setConfig({ [k]: k === 'innings' ? Number(e.target.value) : e.target.value });
  }
  $('room-start').onclick = () => mesh.start();
  $('room-leave').onclick = () => {
    location.search = '';
  };
}

function renderRoom(mesh, hostStart) {
  if (started || !mesh.id) return;
  const { slots, cfg } = mesh.lobby;
  fillSelect($('cfg-captain1'), captainOptions(), cfg.captain1);
  fillSelect($('cfg-captain2'), captainOptions(), cfg.captain2);
  fillSelect($('cfg-stadium'), stadiumOptions(), cfg.stadium);
  fillSelect($('cfg-innings'), INNINGS, cfg.innings);
  for (const k of ['captain1', 'captain2', 'stadium', 'innings']) $(`cfg-${k}`).disabled = !mesh.isHost;

  for (const el of document.querySelectorAll('#panel-room .slot')) {
    const port = Number(el.dataset.port);
    const id = slots[port];
    const info = id && mesh.infos.get(id);
    el.className = 'slot' + (id === mesh.id ? ' me' : '');
    el.replaceChildren();
    const who = document.createElement('span');
    who.className = 'who' + (id ? '' : ' cpu');
    who.textContent = id ? `${info?.name || '?'}${id === mesh.hostId ? ' (host)' : ''}` : 'Computer';
    el.append(who);
    if (id && id !== mesh.id) {
      const peer = mesh.peers.get(id);
      const meta = document.createElement('span');
      meta.className = 'meta';
      meta.textContent = peer?.connected ? (peer.rtt !== null ? `${Math.round(peer.rtt)} ms` : 'connected') : 'connecting…';
      el.append(meta);
    }
    if (!id) {
      const b = document.createElement('button');
      b.textContent = 'Play here';
      b.onclick = () => mesh.takeSlot(port);
      el.append(b);
    } else if (id === mesh.id) {
      const b = document.createElement('button');
      b.textContent = 'Leave slot';
      b.onclick = () => mesh.takeSlot(-1);
      el.append(b);
    }
  }

  const problem = mesh.startProblem();
  $('room-start').hidden = !mesh.isHost;
  $('room-start').disabled = !!problem;
  const watchers = [...mesh.infos.keys()].filter((id) => !slots.includes(id)).length;
  $('room-status').textContent = mesh.isHost
    ? problem || 'Ready to start.'
    : `Waiting for ${mesh.infos.get(mesh.hostId)?.name || 'the host'} to start.` + (watchers ? ' Take a slot to play.' : '');

  // Test hook: ?hoststart=N starts as soon as N players are in and connected.
  if (hostStart && mesh.isHost && !problem && slots.filter(Boolean).length >= hostStart) mesh.start();
}

let started = false;
function start(disc) {
  if (started) return;
  started = true;
  Module.mssbStartTime = performance.now();
  if (params.has('debug')) console.log(`start, runtime ready: ${runtimeReady}`);
  Module.mssbDisc = disc;
  MssbPad.setActive(false);
  $('overlay').hidden = true;
  document.body.classList.add('playing');
  $('canvas').focus();
  if (MssbTouch.isEnabled()) {
    // Phones: fill the screen, sideways if the browser allows it.
    $('stage').requestFullscreen?.({ navigationUI: 'hide' })
      .then(() => screen.orientation?.lock?.('landscape'))
      .catch(() => {});
  }
  const run = () => {
    writeUserIni();
    Module.callMain([]);
  };
  if (Module.calledRun || runtimeReady) run();
  else pendingStart = run;
  loading.update();
}

let runtimeReady = false;
let pendingStart = null;

window.Module = {
  canvas: $('canvas'),
  print: (t) => console.log(t),
  printErr: (t) => console.warn(t),
  mssbFatal: (msg) => fatal(msg),
  mssbStats: params.has('stats'),
  mssbDebug: params.has('debug'),
  preRun: [
    () => {
      // Test hooks: ?env=KEY=VALUE;KEY=VALUE sets environment variables the
      // native build reads (MSSB_INPUT, ...).
      for (const kv of (params.get('env') || '').split(';').filter(Boolean)) {
        const i = kv.indexOf('=');
        ENV[kv.slice(0, i)] = kv.slice(i + 1);
      }
      // The environment is fixed once the runtime starts; writeUserIni() fills
      // the file in when Play is pressed.
      ENV.MSSB_USER_INI = '/tmp/user.ini';
      // The game's window is 1280x960 times the screen's pixel ratio. At a
      // phone's 3x that's a 3840x2880 render target, more GPU memory than iOS
      // gives a tab (it kills the page), so touch devices render at 0.5x: the
      // GameCube's own 640x480. ?dpr=N picks the ratio.
      const dpr = params.has('dpr') ? Number(params.get('dpr')) : MssbTouch.isEnabled() ? 0.5 : null;
      if (dpr > 0) {
        try {
          Object.defineProperty(window, 'devicePixelRatio', { get: () => dpr, configurable: true });
        } catch (e) {
          console.warn("Couldn't set the pixel ratio", e);
        }
      }
      // WebKit (Safari, every iPhone browser) compiles GPU pipelines in the
      // way of presenting frames, even the asynchronous ones: background
      // compiles go one per frame, skipping frames that ran late.
      // Even so, prewarming the 765 known pipelines held an iPhone at 16-40 fps
      // for the first minute (and the audio broke up), and building each one
      // when a draw first needs it stutters mid-game (~200 in a game). So the
      // game picks the moments (port/game/views.c: Now Loading, the stadium
      // intro, between batters) and the known ones compile then. ?prewarm
      // compiles them all at boot, ?noprewarm only on first use.
      const ua = navigator.userAgent;
      const webkit = /AppleWebKit/.test(ua) && !/Chrome\/|Chromium|Edg\//.test(ua);
      if (webkit) ENV.AURORA_PIPELINES_PER_FRAME = params.get('pipesperframe') || '1';
      else if (params.has('pipesperframe')) ENV.AURORA_PIPELINES_PER_FRAME = params.get('pipesperframe');
      if (params.has('noprewarm')) ENV.AURORA_PIPELINE_PREWARM = '0';
      else if (webkit && !params.has('prewarm')) ENV.AURORA_PIPELINE_PREWARM = 'app';
      ENV.MSSB_SKIP_MOVIES = params.has('movies') ? '0' : '1';
      // Audio buffering (port/src/audio/ai.cpp). A phone's main thread stalls
      // for longer (WebKit compiling GPU pipelines), so there the browser's
      // audio callback takes 2 x 2048 frames (85 ms) at a time instead of
      // 2 x 1024, and more is queued ahead of it (it grows by itself after a
      // dropout). ?audioframes= / ?audioms= override.
      const phone = MssbTouch.isEnabled();
      ENV.MSSB_AUDIO_FRAMES = params.get('audioframes') || (phone ? '2048' : '1024');
      ENV.MSSB_AUDIO_QUEUE_MS = params.get('audioms') || (phone ? '120' : '70');
      // The health screen, logo and title are pressed through to the main menu; ?intro shows them.
      ENV.MSSB_SKIP_INTRO = params.has('intro') ? '0' : '1';
      // ?debug: the game's state (batter, pitch) in the log, to line up with what was heard.
      if (params.has('debug') && !ENV.MSSB_TRACE_GAME) ENV.MSSB_TRACE_GAME = '1';
      // GPU pipelines the game is known to use, compiled in the background at
      // boot so new effects don't stall a frame (aurora's pipeline_cache.cpp;
      // port/tools/pipeline_seed.py builds the file). ?noseed skips it.
      if (!params.has('noseed') && ENV.AURORA_PIPELINE_PREWARM !== '0') {
        addRunDependency('mssb-pipelines');
        fetch('initial_pipeline_cache.bin.gz')
          .then((r) => (r.ok ? new Response(r.body.pipeThrough(new DecompressionStream('gzip'))).arrayBuffer() : null))
          .then((b) => b && FS.writeFile('/initial_pipeline_cache.bin', new Uint8Array(b)))
          .catch(() => {})
          .finally(() => removeRunDependency('mssb-pipelines'));
      }
      FS.mkdir('/mssb');
      FS.mount(IDBFS, {}, '/mssb');
      addRunDependency('mssb-userdata');
      if (params.has('debug')) console.log('preRun: loading saved data');
      FS.syncfs(true, (err) => {
        if (params.has('debug')) console.log(`saved data loaded${err ? `: ${err}` : ''}`);
        if (err) console.warn("Couldn't load saved data", err);
        removeRunDependency('mssb-userdata');
      });
    },
  ],
  monitorRunDependencies: (left) => {
    if (params.has('debug')) console.log(`run dependencies left: ${left}`);
  },
  onRuntimeInitialized: () => {
    runtimeReady = true;
    if (params.has('debug')) console.log('runtime ready');
    if (pendingStart) pendingStart();
    loading.update();
  },
  onAbort: (what) => fatal(`The game stopped: ${what}`),
};

window.addEventListener('error', (e) => {
  console.error('[fatal]', e.error?.stack || e.message);
  if (started) fatal(e.message || String(e.error));
});
window.addEventListener('unhandledrejection', (e) => {
  console.error('[fatal]', e.reason?.stack || e.reason);
  if (started) fatal(String(e.reason?.message || e.reason));
});
document.addEventListener('visibilitychange', () => {
  if (document.hidden && typeof FS !== 'undefined' && runtimeReady) FS.syncfs(false, () => {});
});
// The game calls this at moments a hitch doesn't show (port/game/views.c): saves and the list of
// GPU pipelines this device has used (compiled ahead next time) reach the browser's storage even
// when the page is closed without being hidden first, as iOS often does.
let savingData = false;
window.mssbSaveData = () => {
  if (savingData || typeof FS === 'undefined' || !runtimeReady) return;
  savingData = true;
  FS.syncfs(false, (err) => {
    savingData = false;
    if (err) console.warn("Couldn't save data", err);
  });
  if (params.has('debug')) reportPipelines();
};
// ?debug: the pipelines this device used that the page didn't know go to the site's log, gzipped
// in lines short enough for it ("[pipelist] part i/n ..."); port/tools/pipeline_from_log.py turns
// them back into a list for pipeline_seed.py.
let pipelinesReported = 0;
let pipelistPart = 0;
async function reportPipelines() {
  let data;
  try {
    data = FS.readFile('/mssb/pipeline_cache.bin');
  } catch (e) {
    return;
  }
  if (data.length <= pipelinesReported) return;
  const start = pipelinesReported;
  pipelinesReported = data.length;
  const gz = await new Response(new Blob([data.slice(start)]).stream().pipeThrough(new CompressionStream('gzip'))).arrayBuffer();
  let b64 = '';
  const bytes = new Uint8Array(gz);
  for (let i = 0; i < bytes.length; i += 0x8000) b64 += String.fromCharCode(...bytes.subarray(i, i + 0x8000));
  b64 = btoa(b64);
  const part = pipelistPart++;
  const n = Math.ceil(b64.length / 1800);
  for (let i = 0; i < n; i++) console.log(`[pipelist] ${part} ${start} ${i + 1}/${n} ${b64.slice(i * 1800, (i + 1) * 1800)}`);
}

async function init() {
  MssbPad.init();
  MssbTouch.init(params);
  const reason = unsupportedReason();
  if (reason) {
    $('unsupported-text').textContent = reason;
    show('panel-unsupported');
    return;
  }

  const script = document.createElement('script');
  script.src = `${BUILD_DIR}mssb.js`;
  script.async = true;
  if (params.has('debug')) {
    script.onload = () => console.log('mssb.js loaded');
    script.onerror = () => console.error('mssb.js failed to load');
  }
  document.body.appendChild(script);

  const isoUrl = params.get('iso');
  if (isoUrl) {
    try {
      const disc = await urlDisc(isoUrl);
      showPlay(isoUrl, disc);
      if (params.has('autostart')) start(disc);
    } catch (e) {
      fatal(e.message);
    }
    return;
  }

  const local = await serverDisc();
  if (local) {
    showPlay('Disc found on this computer.', local);
    $('forget').hidden = true;
    return;
  }

  const site = await siteDisc();
  if (site && site !== 'locked') {
    showPlay('Disc ready.', site);
    $('forget').hidden = true;
    return;
  }

  const stored = await storedDisc();
  if (stored) {
    showPlay(`Disc ready (${(stored.size / 2 ** 30).toFixed(2)} GB, kept in this browser)`, fileDisc(stored));
  } else {
    show(site === 'locked' ? 'panel-unlock' : 'panel-pick');
  }

  $('unlock-form').onsubmit = async (e) => {
    e.preventDefault();
    $('unlock-error').textContent = '';
    $('unlock-go').disabled = true;
    try {
      if (!(await unlockSite($('unlock-password').value))) {
        $('unlock-error').textContent = 'Wrong password.';
        return;
      }
      const disc = await siteDisc();
      if (disc && disc !== 'locked') {
        showPlay('Disc ready.', disc);
        $('forget').hidden = true;
      } else {
        $('unlock-error').textContent = "Unlocked, but the disc couldn't be read.";
      }
    } catch (err) {
      $('unlock-error').textContent = String(err.message || err);
    } finally {
      $('unlock-go').disabled = false;
    }
  };
  $('unlock-file').onclick = () => show('panel-pick');
  // ?password=... fills in the Unlock screen and submits it, then drops out of the address bar.
  if (params.has('password')) {
    const password = params.get('password');
    params.delete('password');
    history.replaceState(null, '', location.pathname + (params.size ? `?${params}` : '') + location.hash);
    if (!$('panel-unlock').hidden) {
      $('unlock-password').value = password;
      $('unlock-form').requestSubmit();
    }
  }

  $('forget').onclick = async () => {
    await forgetDisc();
    show('panel-pick');
  };
  $('file').onchange = (e) => chooseFile(e.target.files[0]);
  const drop = $('drop');
  drop.addEventListener('dragover', (e) => {
    e.preventDefault();
    drop.classList.add('over');
  });
  drop.addEventListener('dragleave', () => drop.classList.remove('over'));
  drop.addEventListener('drop', (e) => {
    e.preventDefault();
    drop.classList.remove('over');
    chooseFile(e.dataTransfer.files[0]);
  });
}

$('fullscreen').onclick = (e) => {
  e.currentTarget.blur(); // Enter is the Start button
  $('stage').requestFullscreen?.();
};
document.addEventListener('fullscreenchange', () => {
  if (started) $('canvas').focus();
});
$('reload').onclick = () => location.reload();
init();
