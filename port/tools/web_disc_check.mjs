#!/usr/bin/env node
// Checks the web disc (port/web/loader.js, WebDisc) on a deployed site or
// `port/tools/deploy_cloudflare.sh dev`: two visits in one fresh browser
// profile. The first unlocks the disc, boots, and waits for the game data to
// finish saving into the browser's storage; the second boots into a game and
// must not fetch any disc chunk over the network. Reads outside the web disc
// are listed either way.
//   node port/tools/web_disc_check.mjs [--url http://localhost:8787/] [--password password]
//     [--query 'skipfe&captain1=...'] [--save-secs 900] [--play-secs 90]
import puppeteer from 'puppeteer-core';
import { mkdtempSync, rmSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { join } from 'node:path';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]]] : acc), []),
);
const base = args.url || 'http://localhost:8787/';
const password = args.password || 'password';
const query = args.query || 'skipfe&captain1=mario&captain2=bowser';
const profile = mkdtempSync(join(tmpdir(), 'mssb-webdisc-'));

async function visit(label, url, { untilSaved, secs }) {
  const browser = await puppeteer.launch({
    executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
    headless: 'new',
    userDataDir: profile,
    args: ['--enable-unsafe-webgpu', '--mute-audio', '--autoplay-policy=no-user-gesture-required'],
  });
  const page = await browser.newPage();
  const t0 = Date.now();
  const stamp = () => ((Date.now() - t0) / 1000).toFixed(1).padStart(6);
  const net = { chunks: 0, pack: 0 };
  page.on('response', async (r) => {
    const u = new URL(r.url());
    if (!u.pathname.startsWith('/disc/') || u.pathname.endsWith('manifest.json') || u.pathname.endsWith('unlock')) return;
    if (r.fromCache()) return;
    if (u.pathname.endsWith('.pack')) net.pack++;
    else net.chunks++;
  });
  let saved = null;
  const done = new Promise((resolve) => {
    page.on('console', (m) => {
      const t = m.text();
      if (/\[web disc\]|boot pack|first screen|\[scope\]/.test(t)) console.log(`${label} ${stamp()} ${t}`);
      if (/\[web disc\] \d+ of \d+ chunks kept/.test(t)) {
        saved = t;
        if (untilSaved) resolve();
      }
    });
  });
  page.on('pageerror', (e) => console.log(`${label} ${stamp()} [pageerror] ${e.message}`));
  await page.goto(url);
  await Promise.race([done, new Promise((r) => setTimeout(r, secs * 1000))]);
  const misses = await page.evaluate(() => window.mssbWebDiscMisses || []).catch(() => []);
  const status = await page.evaluate(() => document.getElementById('save-status')?.textContent || '').catch(() => '');
  await browser.close();
  console.log(`${label}: ${net.chunks} disc chunks over the network, ` +
    `${net.pack} boot pack fetches, ${misses.length} reads outside the web disc${saved ? '' : `; still saving: ${status}`}`);
  return { net, misses, saved };
}

try {
  const first = await visit('visit 1', `${base}?password=${encodeURIComponent(password)}&stats&${query}&autostart`, {
    untilSaved: true,
    secs: Number(args['save-secs'] || 900),
  });
  if (!first.saved) throw new Error('the game data never finished saving');
  const second = await visit('visit 2', `${base}?stats&${query}&autostart`, { secs: Number(args['play-secs'] || 90) });
  const ok = second.net.chunks === 0 && second.net.pack === 0;
  console.log(ok ? 'PASS: the second visit read everything from the browser' : 'FAIL: the second visit went to the network');
  process.exitCode = ok ? 0 : 1;
} finally {
  rmSync(profile, { recursive: true, force: true });
}
