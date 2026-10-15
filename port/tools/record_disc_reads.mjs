#!/usr/bin/env node
// Records every disc read of one web-build session (headless Chrome, the dev
// server's disc) into build/disc-reads/<name>.json: {size, ranges: [[start,
// len], ...]} in the image file's offsets, merged and sorted. The web disc's
// keep-list is the union of these recordings (port/tools/web_disc.py).
//   node port/tools/web_serve.mjs 8080 &
//   node port/tools/record_disc_reads.mjs --name fe --secs 300 [--query 'skipfe&captain1=...'] [--env 'MSSB_INPUT=...']
//   [--until 'console text'] [--port 8080] [--quiet] [--shots 60,120 (seconds; build/disc-reads/<name>-<t>.png)]
// The session ends after --secs, or --until's text shows up in the console
// (plus --after seconds, default 5). Reads are saved every 20 s, so a session
// that dies still leaves what it read.
import puppeteer from 'puppeteer-core';
import { mkdirSync, writeFileSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]?.startsWith('--') ? '' : all[i + 1]]] : acc), []),
);
const name = args.name || 'session';
const secs = Number(args.secs || 120);
const after = Number(args.after || 5);
const port = Number(args.port || 8080);
const env = ['MSSB_ALLMODES=0', args.env].filter(Boolean).join(';');
const url = `http://localhost:${port}/?iso=disc.iso&autostart${args.query ? `&${args.query}` : ''}&env=${encodeURIComponent(env)}`;
const outDir = join(dirname(fileURLToPath(import.meta.url)), '../../build/disc-reads');
mkdirSync(outDir, { recursive: true });
const out = join(outDir, `${name}.json`);

const browser = await puppeteer.launch({
  executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
  headless: 'new',
  args: ['--enable-unsafe-webgpu', '--mute-audio', '--autoplay-policy=no-user-gesture-required'],
});
const page = await browser.newPage();
await page.evaluateOnNewDocument(() => {
  window.__reads = [];
  const iv = setInterval(() => {
    const d = window.Module && Module.mssbDisc;
    if (!d) return;
    clearInterval(iv);
    window.__discSize = d.size;
    // Every way the game asks for bytes: synchronous, asynchronous, and the
    // asynchronous path's "start fetching" probe.
    for (const fn of ['read', 'readCached', 'prefetch']) {
      const orig = d[fn].bind(d);
      d[fn] = (off, len, ...rest) => {
        if (len > 0) window.__reads.push([off, Math.min(len, d.size - off)]);
        return orig(off, len, ...rest);
      };
    }
  }, 1);
});
const t0 = Date.now();
let resolveUntil;
const until = new Promise((r) => (resolveUntil = r));
page.on('console', (m) => {
  const text = m.text();
  if (!args.quiet) console.log(`${((Date.now() - t0) / 1000).toFixed(1).padStart(6)} ${text}`);
  if (args.until && text.includes(args.until)) resolveUntil();
});
page.on('pageerror', (e) => console.log(`[pageerror] ${e.message}`));
page.on('crash', () => console.log('[crash]'));

let size = 0;
let ranges = []; // merged, sorted [start, end)
async function collect() {
  try {
    const r = await page.evaluate(() => {
      const reads = window.__reads;
      window.__reads = [];
      return { size: window.__discSize || 0, reads };
    });
    size ||= r.size;
    ranges = merge(ranges.concat(r.reads.map(([o, n]) => [o, o + n])));
    writeFileSync(out, JSON.stringify({ size, url, ranges: ranges.map(([a, b]) => [a, b - a]) }) + '\n');
  } catch {}
}
function merge(rs) {
  rs.sort((x, y) => x[0] - y[0]);
  const m = [];
  for (const [a, b] of rs) {
    const last = m[m.length - 1];
    if (last && a <= last[1]) last[1] = Math.max(last[1], b);
    else m.push([a, b]);
  }
  return m;
}

await page.goto(url);
const saver = setInterval(collect, 20000);
for (const t of (args.shots || '').split(',').filter(Boolean).map(Number)) {
  setTimeout(() => page.screenshot({ path: join(outDir, `${name}-${t}.png`) }).catch(() => {}), t * 1000);
}
await Promise.race([
  new Promise((r) => setTimeout(r, secs * 1000)),
  until.then(() => new Promise((r) => setTimeout(r, after * 1000))),
]);
clearInterval(saver);
await collect();
await browser.close();
const bytes = ranges.reduce((n, [a, b]) => n + b - a, 0);
console.log(`${name}: ${ranges.length} ranges, ${(bytes / 2 ** 20).toFixed(1)} MB in ${((Date.now() - t0) / 1000).toFixed(0)} s -> ${out}`);
process.exit(0);
