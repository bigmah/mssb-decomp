#!/usr/bin/env node
// Drives the web build in Chrome for testing: loads the page with the dev
// server's disc (?iso=disc.iso&autostart), logs the console, presses keys on a
// schedule and saves screenshots.
//   node port/tools/web_drive.mjs --secs 60 --shots 10,20,30 --keys 12:Enter,14:x --out build/web-shots
// Needs puppeteer-core (NODE_PATH or a local install) and port/tools/web_serve.mjs running.
import puppeteer from 'puppeteer-core';
import { mkdirSync, writeFileSync, appendFileSync } from 'node:fs';
import { join } from 'node:path';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]]] : acc), []),
);
const secs = Number(args.secs || 30);
const shots = (args.shots || '').split(',').filter(Boolean).map(Number);
const keys = (args.keys || '').split(',').filter(Boolean).map((k) => {
  const [t, key, hold] = k.split(':');
  return { t: Number(t), key, hold: Number(hold || 120) };
});
const out = args.out || 'build/web-shots';
const url = args.url || 'http://localhost:8080/?iso=disc.iso&autostart' + (args.query ? '&' + args.query : '');
const headless = args.headed ? false : 'new';
mkdirSync(out, { recursive: true });
const logFile = join(out, 'console.log');
writeFileSync(logFile, '');
const log = (s) => {
  appendFileSync(logFile, s + '\n');
  if (!args.quiet) console.log(s);
};

const browser = await puppeteer.launch({
  executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
  headless,
  args: ['--enable-unsafe-webgpu', '--autoplay-policy=no-user-gesture-required', '--window-size=1340,1100'],
  defaultViewport: { width: 1280, height: 1010 },
});
const page = await browser.newPage();
const t0 = Date.now();
const stamp = () => ((Date.now() - t0) / 1000).toFixed(1).padStart(6);
page.on('console', (m) => log(`${stamp()} [${m.type()}] ${m.text()}`));
page.on('pageerror', (e) => log(`${stamp()} [pageerror] ${e.stack || e.message}`));
page.on('crash', () => log(`${stamp()} [crash]`));
await page.goto(url);

const events = [
  ...shots.map((t) => ({ t, shot: true })),
  ...keys.map((k) => ({ t: k.t, key: k.key, hold: k.hold })),
].sort((a, b) => a.t - b.t);
for (const ev of events) {
  const wait = ev.t * 1000 - (Date.now() - t0);
  if (wait > 0) await new Promise((r) => setTimeout(r, wait));
  if (ev.shot) {
    const file = join(out, `shot-${String(ev.t).padStart(4, '0')}.png`);
    await page.screenshot({ path: file });
    log(`${stamp()} [shot] ${file}`);
  } else {
    await page.focus('#canvas').catch(() => {});
    await page.keyboard.down(ev.key);
    await new Promise((r) => setTimeout(r, ev.hold));
    await page.keyboard.up(ev.key);
    log(`${stamp()} [key] ${ev.key}`);
  }
}
const rest = secs * 1000 - (Date.now() - t0);
if (rest > 0) await new Promise((r) => setTimeout(r, rest));
// --pause: stop the page at the end and print the JS/wasm stack (finds hangs).
if (args.pause) {
  const cdp = await page.createCDPSession();
  await cdp.send('Debugger.enable');
  const paused = new Promise((r) => cdp.once('Debugger.paused', r));
  await cdp.send('Debugger.pause');
  const ev = await Promise.race([paused, new Promise((r) => setTimeout(() => r(null), 5000))]);
  if (ev) for (const f of ev.callFrames.slice(0, 25)) log(`${stamp()} [stack] ${f.functionName || '?'}`);
  else log(`${stamp()} [stack] (no pause)`);
}
// --fetch /memfs/path:local/path copies a file out of the page's filesystem
// (e.g. a file set with ?env=).
if (args.fetch) {
  const [from, to] = args.fetch.split(':');
  const b64 = await page.evaluate((p) => {
    const d = Module.FS.readFile(p);
    let s = '';
    for (let i = 0; i < d.length; i += 0x8000) s += String.fromCharCode.apply(null, d.subarray(i, i + 0x8000));
    return btoa(s);
  }, from);
  writeFileSync(to, Buffer.from(b64, 'base64'));
  log(`${stamp()} [fetch] ${from} -> ${to}`);
}
await browser.close();
