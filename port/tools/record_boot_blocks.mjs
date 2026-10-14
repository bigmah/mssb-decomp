#!/usr/bin/env node
// Records which 512 KB disc blocks the game reads from boot to the main menu,
// in first-read order, into port/web/boot_blocks.json. The deployed page
// prefetches them in parallel (port/web/loader.js), so a phone isn't waiting on
// ~100 one-at-a-time network reads. Rerun when the disc image changes.
//   node port/tools/web_serve.mjs 8080 &
//   node port/tools/record_boot_blocks.mjs [--port 8080] [--secs 60]
import puppeteer from 'puppeteer-core';
import { writeFileSync } from 'node:fs';
import { join, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]]] : acc), []),
);
const port = Number(args.port || 8080);
const secs = Number(args.secs || 60);
const BLOCK = 512 * 1024;
// The to_menu.sh presses: past the health screen and title to the main menu.
const url = `http://localhost:${port}/?iso=disc.iso&autostart&env=MSSB_INPUT=500:A,800:A,1300:START`;

const browser = await puppeteer.launch({
  executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
  headless: 'new',
  args: ['--enable-unsafe-webgpu', '--mute-audio'],
});
const page = await browser.newPage();
await page.evaluateOnNewDocument((BLOCK) => {
  window.__blocks = [];
  const seen = new Set();
  const iv = setInterval(() => {
    const d = window.Module && Module.mssbDisc;
    if (!d) return;
    clearInterval(iv);
    window.__discSize = d.size;
    for (const fn of ['read', 'readCached']) {
      const orig = d[fn].bind(d);
      d[fn] = (off, len) => {
        for (let b = Math.floor(off / BLOCK); b <= Math.floor((off + len - 1) / BLOCK); b++) {
          if (!seen.has(b)) {
            seen.add(b);
            window.__blocks.push(b);
          }
        }
        return orig(off, len);
      };
    }
  }, 1);
}, BLOCK);
await page.goto(url);
await new Promise((r) => setTimeout(r, secs * 1000));
const { size, blocks } = await page.evaluate(() => ({ size: window.__discSize, blocks: window.__blocks }));
await browser.close();

const out = join(dirname(fileURLToPath(import.meta.url)), '../web/boot_blocks.json');
writeFileSync(out, JSON.stringify({ size, block: BLOCK, blocks }) + '\n');
console.log(`${blocks.length} blocks (${((blocks.length * BLOCK) / 2 ** 20).toFixed(0)} MB) for a ${size}-byte disc -> ${out}`);
