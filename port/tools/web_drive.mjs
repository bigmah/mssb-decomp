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
  args: ['--enable-unsafe-webgpu', '--autoplay-policy=no-user-gesture-required', ...(process.env.MSSB_TEST_SOUND ? [] : ['--mute-audio']), '--window-size=1340,1100'],
  defaultViewport: { width: 1280, height: 1010 },
});
const page = await browser.newPage();
const t0 = Date.now();
const stamp = () => ((Date.now() - t0) / 1000).toFixed(1).padStart(6);
page.on('console', (m) => log(`${stamp()} [${m.type()}] ${m.text()}`));
page.on('pageerror', (e) => log(`${stamp()} [pageerror] ${e.stack || e.message}`));
page.on('crash', () => log(`${stamp()} [crash]`));
// --fakepad: a scripted "standard" gamepad in place of a real one (Chrome
// can't connect one headless). --pad 12:a,14:start presses its buttons.
const PAD_BUTTONS = { a: 0, b: 1, x: 2, y: 3, l: 4, r: 5, z: 5, start: 9, up: 12, down: 13, left: 14, right: 15 };
const pads = (args.pad || '').split(',').filter(Boolean).map((k) => {
  const [t, button, hold] = k.split(':');
  return { t: Number(t), button, hold: Number(hold || 120) };
});
if (args.fakepad || pads.length) {
  // --padconnect SECS: the pad appears only then (Chrome reports a pad after
  // its first button press), as a hot-plug.
  // --padid/--padmapping imitate a particular controller and browser;
  // --padslot N lists N idle devices before it.
  await page.evaluateOnNewDocument((connectAt, id, mapping, slot) => {
    const idle = (index) => ({
      id: `Idle Device ${index} (Vendor: 1234 Product: 000${index})`, index, connected: true, mapping: '', timestamp: 0,
      axes: [0, 0], buttons: Array.from({ length: 4 }, () => ({ pressed: false, touched: false, value: 0 })),
    });
    const others = Array.from({ length: slot }, (_, i) => idle(i));
    const pad = {
      id, index: slot, connected: true, mapping, timestamp: 0,
      axes: [0, 0, 0, 0],
      buttons: Array.from({ length: 17 }, () => ({ pressed: false, touched: false, value: 0 })),
    };
    window.__fakePad = pad;
    let present = !connectAt;
    navigator.getGamepads = () => [...others, present ? pad : null, null, null, null].slice(0, 4);
    window.__fakePadPress = (i, down) => {
      pad.buttons[i] = { pressed: down, touched: down, value: down ? 1 : 0 };
      pad.timestamp = performance.now();
    };
    const connect = () => {
      present = true;
      for (const p of [...others, pad]) {
        const ev = new Event('gamepadconnected');
        ev.gamepad = p;
        dispatchEvent(ev);
      }
    };
    if (connectAt) setTimeout(connect, connectAt * 1000);
    else addEventListener('load', connect);
  }, Number(args.padconnect || 0), args.padid || 'Fake Controller (STANDARD GAMEPAD Vendor: 045e Product: 028e)',
  args.padmapping ?? 'standard', Number(args.padslot || 0));
}
// --mobile [CPU slowdown]: a landscape phone (iPhone user agent, touch, 844x390
// at 3x) with the CPU throttled by the given factor (default 4).
if (args.mobile) {
  await page.emulate({
    userAgent: 'Mozilla/5.0 (iPhone; CPU iPhone OS 18_0 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/18.0 Mobile/15E148 Safari/604.1',
    viewport: { width: 844, height: 390, deviceScaleFactor: 3, isMobile: true, hasTouch: true, isLandscape: true },
  });
  const cdp = await page.createCDPSession();
  await cdp.send('Emulation.setCPUThrottlingRate', { rate: Number(args.mobile) || 4 });
}
// --audiorate HZ: the page's AudioContext runs at that rate (iPhones run at 48000).
if (args.audiorate) {
  await page.evaluateOnNewDocument((rate) => {
    const Base = window.AudioContext;
    window.AudioContext = window.webkitAudioContext = class extends Base {
      constructor(opts) {
        super({ ...opts, sampleRate: rate });
      }
    };
  }, Number(args.audiorate));
}
// --mbps N: a phone network, N megabits/s down with 60 ms latency (with --url to the live site).
if (args.mbps) {
  const cdp = await page.createCDPSession();
  await cdp.send('Network.enable');
  const bps = (Number(args.mbps) * 1e6) / 8;
  await cdp.send('Network.emulateNetworkConditions', { offline: false, latency: 60, downloadThroughput: bps, uploadThroughput: bps / 4 });
}
await page.goto(url);
// --blur SECS: take focus off the canvas then (a click elsewhere on the page).
if (args.blur)
  setTimeout(() => page.evaluate(() => { document.activeElement?.blur?.(); document.body.focus(); }).catch(() => {}),
    Number(args.blur) * 1000);

const events = [
  ...shots.map((t) => ({ t, shot: true })),
  ...keys.map((k) => ({ t: k.t, key: k.key, hold: k.hold })),
  ...pads.map((k) => ({ t: k.t, button: k.button, hold: k.hold })),
].sort((a, b) => a.t - b.t);
for (const ev of events) {
  const wait = ev.t * 1000 - (Date.now() - t0);
  if (wait > 0) await new Promise((r) => setTimeout(r, wait));
  if (ev.shot) {
    const file = join(out, `shot-${String(ev.t).padStart(4, '0')}.png`);
    await page.screenshot({ path: file });
    log(`${stamp()} [shot] ${file}`);
  } else if (ev.button) {
    const i = PAD_BUTTONS[ev.button.toLowerCase()];
    await page.evaluate((i) => window.__fakePadPress(i, true), i);
    await new Promise((r) => setTimeout(r, ev.hold));
    await page.evaluate((i) => window.__fakePadPress(i, false), i);
    log(`${stamp()} [pad] ${ev.button}`);
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
