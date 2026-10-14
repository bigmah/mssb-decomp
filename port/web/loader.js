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
  const flush = () => {
    if (!queue.length) return;
    const lines = queue;
    queue = [];
    fetch('log', { method: 'POST', body: JSON.stringify({ id, lines }), keepalive: true }).catch(() => {});
  };
  setInterval(flush, 1000);
  addEventListener('pagehide', flush);
  for (const level of ['log', 'info', 'warn', 'error']) {
    const orig = console[level].bind(console);
    console[level] = (...a) => {
      orig(...a);
      const text = a.map((x) => (x instanceof Error ? x.stack || x.message : typeof x === 'object' ? (() => { try { return JSON.stringify(x); } catch { return String(x); } })() : String(x))).join(' ');
      queue.push(`${((performance.now() - t0) / 1000).toFixed(1)} ${level} ${text}`);
    };
  }
  console.log(`debug: ${navigator.userAgent} gpu=${!!navigator.gpu} mem=${navigator.deviceMemory} screen=${screen.width}x${screen.height}@${devicePixelRatio}`);
}

// ---- Disc access -----------------------------------------------------------

// Reads go through a block cache. readCached() answers synchronously when every
// block is present; read() fetches the missing ones.
class Disc {
  constructor(size, fetchRange) {
    this.size = size;
    this.fetchRange = fetchRange; // (start, end) -> Promise<ArrayBuffer>
    this.blocks = new Map(); // index -> Uint8Array, in LRU order
  }

  touch(i) {
    const b = this.blocks.get(i);
    if (b) {
      this.blocks.delete(i);
      this.blocks.set(i, b);
    }
    return b;
  }

  assemble(offset, len) {
    len = Math.max(0, Math.min(len, this.size - offset));
    const out = new Uint8Array(len);
    let pos = 0;
    while (pos < len) {
      const abs = offset + pos;
      const i = Math.floor(abs / BLOCK);
      const b = this.touch(i);
      if (!b) return null;
      const start = abs - i * BLOCK;
      const n = Math.min(b.length - start, len - pos);
      out.set(b.subarray(start, start + n), pos);
      pos += n;
    }
    return out;
  }

  readCached(offset, len) {
    return this.assemble(offset, len);
  }

  async read(offset, len) {
    const first = Math.floor(offset / BLOCK);
    const last = Math.floor((Math.min(offset + len, this.size) - 1) / BLOCK);
    let i = first;
    while (i <= last) {
      if (this.blocks.has(i)) {
        i++;
        continue;
      }
      let j = i;
      while (j + 1 <= last && !this.blocks.has(j + 1)) j++;
      const start = i * BLOCK;
      const end = Math.min((j + 1) * BLOCK, this.size);
      const data = new Uint8Array(await this.fetchRange(start, end));
      for (let k = i; k <= j; k++) {
        const s = (k - i) * BLOCK;
        this.blocks.set(k, data.slice(s, Math.min(s + BLOCK, data.length)));
      }
      i = j + 1;
    }
    while (this.blocks.size > MAX_BLOCKS + (last - first + 1)) {
      this.blocks.delete(this.blocks.keys().next().value);
    }
    return this.assemble(offset, len);
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
  const recent = new Map(); // a few whole chunks, in case they're bigger than a block
  const loadChunk = (i) => {
    let p = recent.get(i);
    if (!p) {
      loading.busy(1);
      p = fetch(`disc/${dir}/${letters(i)}`)
        .then((r) => {
          if (!r.ok) throw new Error(`disc read failed (${r.status})`);
          return r.arrayBuffer();
        })
        .then((b) => {
          loading.bytes += b.byteLength;
          return b;
        })
        .finally(() => loading.busy(-1));
      p.catch(() => recent.delete(i));
      recent.set(i, p);
      if (recent.size > 8) recent.delete(recent.keys().next().value);
    }
    return p;
  };
  const disc = new Disc(size, async (start, end) => {
    const out = new Uint8Array(end - start);
    const parts = [];
    for (let i = Math.floor(start / chunk); i * chunk < end; i++) parts.push(i);
    const datas = await Promise.all(parts.map(loadChunk)); // in parallel
    parts.forEach((i, k) => {
      const data = new Uint8Array(datas[k]);
      const from = Math.max(start, i * chunk);
      const to = Math.min(end, (i + 1) * chunk);
      out.set(data.subarray(from - i * chunk, to - i * chunk), from - start);
    });
    return out.buffer;
  });
  disc.gameId = await readGameId(new Blob([await disc.read(0, 0x8020)]));
  return disc.gameId === GAME_ID ? disc : null;
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
  shown: false,
  showTimer: null,
  hideTimer: null,
  busy(delta) {
    this.pending += delta;
    this.update();
  },
  update() {
    const el = $('net-status');
    const busy = started && (!runtimeReady || this.pending > 0);
    if (busy) {
      clearTimeout(this.hideTimer);
      this.hideTimer = null;
      $('net-text').textContent = runtimeReady ? `Loading… ${(this.bytes / 2 ** 20).toFixed(0)} MB` : 'Loading game…';
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
  const ini = [];
  if (params.has('skipfe')) ini.push('skipfe = true');
  for (const k of ['captain1', 'captain2', 'team1', 'team2', 'stadium', 'innings']) if (params.has(k)) ini.push(`${k} = ${params.get(k)}`);
  FS.writeFile('/tmp/user.ini', ini.join('\n') + '\n');
}

function showPlay(text, disc) {
  show('panel-play');
  $('play-name').textContent = text;
  $('play').onclick = () => start(disc);
  if (params.has('autostart')) start(disc);
}

let started = false;
function start(disc) {
  if (started) return;
  started = true;
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
      // gives a tab (it kills the page), so touch devices render at 1x: still
      // twice the GameCube's resolution. ?dpr=N picks the ratio.
      const dpr = params.has('dpr') ? Number(params.get('dpr')) : MssbTouch.isEnabled() ? 1 : null;
      if (dpr > 0) {
        try {
          Object.defineProperty(window, 'devicePixelRatio', { get: () => dpr, configurable: true });
        } catch (e) {
          console.warn("Couldn't set the pixel ratio", e);
        }
      }
      ENV.MSSB_SKIP_MOVIES = params.has('movies') ? '0' : '1';
      // GPU pipelines the game is known to use, compiled in the background at
      // boot so new effects don't stall a frame (aurora's pipeline_cache.cpp;
      // port/tools/pipeline_seed.py builds the file). ?noseed skips it.
      if (!params.has('noseed')) {
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
