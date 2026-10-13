#!/usr/bin/env node
// Frame-exact captures of the web build: runs it in headless Chrome (fresh
// profile, so a fresh IndexedDB: no save) with MSSB_INPUT and
// MSSB_FREEZE_FRAMES (port/src/freeze_frames.cpp); at each listed frame the
// game holds the frame, this saves the canvas and lets it go on.
//   node port/tools/compare/web_capture.mjs --port 8090 --input "500:A" --frames 600,900 \
//     --out build/compare/x/web [--query movies] [--timeout 600]
// Writes <out>/web-<frame>.png, <out>/frames.json ({frame: {padFrame, retrace, t}})
// and <out>/console.log. Needs `node port/tools/web_serve.mjs PORT` running.
import puppeteer from 'puppeteer-core';
import { mkdirSync, writeFileSync, appendFileSync } from 'node:fs';
import { join } from 'node:path';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]]] : acc), []),
);
const port = args.port || '8090';
const frames = (args.frames || '').split(',').filter(Boolean).map(Number).sort((a, b) => a - b);
const out = args.out || 'build/compare/web';
const timeout = Number(args.timeout || 900) * 1000;
const env = [`MSSB_FREEZE_FRAMES=${frames.join(',')}`];
if (args.input) env.push(`MSSB_INPUT=${args.input}`);
if (args.env) env.push(...args.env.split(';').filter(Boolean));
const url = `http://localhost:${port}/?iso=disc.iso&autostart${args.query ? '&' + args.query : ''}&env=${encodeURIComponent(env.join(';'))}`;
mkdirSync(out, { recursive: true });
const logFile = join(out, 'console.log');
writeFileSync(logFile, url + '\n');
const t0 = Date.now();
const stamp = () => ((Date.now() - t0) / 1000).toFixed(1).padStart(6);
const log = (s) => appendFileSync(logFile, `${stamp()} ${s}\n`);

const browser = await puppeteer.launch({
  executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
  headless: args.headed ? false : 'new',
  args: ['--enable-unsafe-webgpu', '--autoplay-policy=no-user-gesture-required', ...(process.env.MSSB_TEST_SOUND ? [] : ['--mute-audio']), '--window-size=1340,1100'],
  defaultViewport: { width: 1280, height: 1010 },
});
const info = {};
let failed = null;
try {
  const page = await browser.newPage();
  page.on('console', (m) => log(`[${m.type()}] ${m.text()}`));
  page.on('pageerror', (e) => { log(`[pageerror] ${e.stack || e.message}`); });
  page.on('crash', () => { failed = 'page crashed'; log('[crash]'); });
  await page.goto(url);
  const canvas = await page.waitForSelector('#canvas');
  for (const f of frames) {
    if (info[f]) continue; // captured together with an earlier one (long frame)
    const left = timeout - (Date.now() - t0);
    const frozen = await page
      .waitForFunction(() => window.Module && Module.mssbFrozen, { timeout: Math.max(left, 1000), polling: 50 })
      .then((h) => h.jsonValue())
      .catch(() => null);
    if (!frozen) {
      failed = `timed out waiting for frame ${f}`;
      break;
    }
    // Let the browser present the held frame before grabbing it.
    await page.evaluate(() => new Promise((r) => requestAnimationFrame(() => requestAnimationFrame(r))));
    const file = join(out, `web-${frozen.frame}.png`);
    await canvas.screenshot({ path: file });
    info[frozen.frame] = { padFrame: frozen.padFrame, retrace: frozen.retrace, t: (Date.now() - t0) / 1000 };
    log(`[shot] frame ${frozen.frame} (pad ${frozen.padFrame}, retrace ${frozen.retrace}) -> ${file}`);
    process.stdout.write(`  web: frame ${frozen.frame} (pad ${frozen.padFrame}, retrace ${frozen.retrace}) at ${stamp()}s\n`);
    await page.evaluate(() => { Module.mssbRelease = true; });
    await page.waitForFunction(() => !Module.mssbFrozen, { polling: 20, timeout: 10000 }).catch(() => {});
  }
} finally {
  writeFileSync(join(out, 'frames.json'), JSON.stringify(info, null, 1));
  await browser.close();
}
if (failed) {
  console.error(`web_capture: ${failed} (see ${logFile})`);
  process.exit(1);
}
