#!/usr/bin/env node
// Records the disc bytes the game reads from Play to the main menu, in the
// order it first needs them, into port/web/boot_ranges.json. The deploy
// (port/tools/deploy_cloudflare.sh) packs those bytes into one file,
// disc/<id>/boot.pack, that the page streams as soon as the disc is unlocked
// (port/web/loader.js), so boot isn't waiting on dozens of separate reads.
// Rerun when the disc image or the boot path changes.
//   node port/tools/web_serve.mjs 8080 &
//   node port/tools/record_boot_pack.mjs [--port 8080] [--after 3]
import puppeteer from 'puppeteer-core';
import { writeFileSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]]] : acc), []),
);
const port = Number(args.port || 8080);
const after = Number(args.after || 3); // seconds of the main menu to include
const url = `http://localhost:${port}/?iso=disc.iso&autostart&env=MSSB_TRACE_TASKS=1`;

const browser = await puppeteer.launch({
  executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
  headless: 'new',
  args: ['--enable-unsafe-webgpu', '--mute-audio'],
});
const page = await browser.newPage();
await page.evaluateOnNewDocument(() => {
  window.__reads = [];
  const iv = setInterval(() => {
    const d = window.Module && Module.mssbDisc;
    if (!d) return;
    clearInterval(iv);
    window.__discSize = d.size;
    for (const fn of ['read', 'readCached']) {
      const orig = d[fn].bind(d);
      d[fn] = (off, len, ...rest) => {
        window.__reads.push([off, Math.min(len, d.size - off)]);
        return orig(off, len, ...rest);
      };
    }
  }, 1);
});
const menu = new Promise((resolve) => page.on('console', (m) => m.text().includes('[scene] scene 5 step 2') && resolve()));
await page.goto(url);
await Promise.race([menu, new Promise((_, reject) => setTimeout(() => reject(new Error('no main menu after 60 s')), 60000))]);
await new Promise((r) => setTimeout(r, after * 1000));
const { size, reads } = await page.evaluate(() => ({ size: window.__discSize, reads: window.__reads }));
await browser.close();

// Each read's bytes not already covered, in read order; touching pieces merge.
const covered = []; // sorted, disjoint [start, end)
const segments = [];
for (const [off, len] of reads) {
  let pos = off;
  const end = off + len;
  for (const [a, b] of covered) {
    if (b <= pos) continue;
    if (a >= end) break;
    if (a > pos) add(pos, a);
    pos = Math.max(pos, b);
  }
  if (pos < end) add(pos, end);
}
function add(a, b) {
  const last = segments[segments.length - 1];
  if (last && last[0] + last[1] === a) last[1] += b - a;
  else segments.push([a, b - a]);
  covered.push([a, b]);
  covered.sort((x, y) => x[0] - y[0]);
  for (let i = covered.length - 1; i > 0; i--) {
    if (covered[i - 1][1] >= covered[i][0]) {
      covered[i - 1][1] = Math.max(covered[i - 1][1], covered[i][1]);
      covered.splice(i, 1);
    }
  }
}

const out = join(dirname(fileURLToPath(import.meta.url)), '../web/boot_ranges.json');
writeFileSync(out, JSON.stringify({ size, segments }) + '\n');
const bytes = segments.reduce((n, s) => n + s[1], 0);
console.log(`${reads.length} reads -> ${segments.length} segments, ${(bytes / 2 ** 20).toFixed(1)} MB, for a ${size}-byte disc -> ${out}`);
