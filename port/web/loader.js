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

function show(id) {
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
// ?stadium= pick it; ?nomovies skips the movies.
function writeUserIni() {
  const ini = [];
  if (params.has('skipfe')) ini.push('skipfe = true');
  for (const k of ['captain1', 'captain2', 'stadium']) if (params.has(k)) ini.push(`${k} = ${params.get(k)}`);
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
      if (params.has('nomovies')) ENV.MSSB_SKIP_MOVIES = '1';
      FS.mkdir('/mssb');
      FS.mount(IDBFS, {}, '/mssb');
      addRunDependency('mssb-userdata');
      FS.syncfs(true, (err) => {
        if (err) console.warn("Couldn't load saved data", err);
        removeRunDependency('mssb-userdata');
      });
    },
  ],
  onRuntimeInitialized: () => {
    runtimeReady = true;
    if (pendingStart) pendingStart();
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

  const stored = await storedDisc();
  if (stored) {
    showPlay(`Disc ready (${(stored.size / 2 ** 30).toFixed(2)} GB, kept in this browser)`, fileDisc(stored));
  } else {
    show('panel-pick');
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
