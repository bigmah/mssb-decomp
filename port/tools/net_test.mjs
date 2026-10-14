#!/usr/bin/env node
// Online play soak test (from the strikers port): opens two headless Chromes,
// joins them to one room through port/tools/web_serve.mjs's signaling, starts
// a game, mashes random keys on both and checks the peers' state hashes agree.
//   node port/tools/net_test.mjs --secs 120 [--innings 1] [--relay] [--out build/net-test]
//     [--netsim 0.05,40,20]   drop 5% of input packets, delay the rest 40-60 ms
//     [--signal URL/]         use another signaling server (e.g. the Cloudflare one)
//     [--shots 30,60]         screenshots of every player at those seconds
//     [--base https://SITE/ --password PW]   the deployed site end to end
// Needs puppeteer-core (cd port/tools && npm install) and web_serve.mjs running.
// Exit code 0: no desync and every peer got past --min-frames frames.
import puppeteer from 'puppeteer-core';
import { mkdirSync, writeFileSync, appendFileSync } from 'node:fs';
import { join } from 'node:path';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]?.startsWith('--') ? '1' : all[i + 1] ?? '1']] : acc), []),
);
const players = Number(args.players || 2); // one per team
const secs = Number(args.secs || 90);
const out = args.out || 'build/net-test';
const base = args.base || 'http://localhost:8080/';
const room = args.room || `T${Date.now().toString(36).slice(-5).toUpperCase()}`;
const minFrames = Number(args['min-frames'] || 600);
const ports = (args.ports || '0,1').split(',').map(Number);
const shots = (args.shots || '').split(',').filter(Boolean).map(Number);
mkdirSync(out, { recursive: true });

const t0 = Date.now();
const stamp = () => ((Date.now() - t0) / 1000).toFixed(1).padStart(6);
const logFile = join(out, 'console.log');
writeFileSync(logFile, '');
const log = (s) => {
  appendFileSync(logFile, s + '\n');
  if (!args.quiet || /\[net\]|pageerror|crash|fatal/.test(s)) console.log(s);
};

// port/src/input.cpp's keyboard: stick (arrows), A (X), B (Z), X (C), Y (V).
// No Start: its pause menu can end the game.
const keys = ['ArrowLeft', 'ArrowRight', 'ArrowUp', 'ArrowDown', 'x', 'x', 'x', 'z', 'c', 'v'];
const sessions = [];
let failed = null;
let finished = false;

for (let i = 0; i < players; i++) {
  const browser = await puppeteer.launch({
    executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
    headless: args.headed ? false : 'new',
    args: [
      '--enable-unsafe-webgpu',
      '--autoplay-policy=no-user-gesture-required',
      '--disable-features=WebRtcHideLocalIpsWithMdns',
      '--disable-background-timer-throttling',
      '--disable-renderer-backgrounding',
      '--disable-backgrounding-occluded-windows',
      '--window-size=700,600',
    ],
    defaultViewport: { width: 640, height: 540 },
  });
  const page = await browser.newPage();
  const tag = `P${i}`;
  page.on('console', (m) => {
    const text = m.text();
    log(`${stamp()} ${tag} [${m.type()}] ${text}`);
    if (/\[net\] (DESYNC|match stopped)/.test(text) && !failed && !finished) failed = `${tag}: ${text}`;
  });
  page.on('pageerror', (e) => log(`${stamp()} ${tag} [pageerror] ${e.stack || e.message}`));
  page.on('crash', () => log(`${stamp()} ${tag} [crash]`));
  // --password: the deployed site's own disc (unlocked with it) instead of web_serve's disc.iso.
  const q = new URLSearchParams({ ...(args.password ? { password: args.password } : { iso: 'disc.iso' }), room, name: tag, port: String(ports[i]) });
  q.set('autojoin', '');
  if (i === 0) q.set('hoststart', String(players));
  if (args.relay) q.set('relay', '');
  if (args.innings) q.set('innings', args.innings);
  if (args.netsim) q.set('netsim', args.netsim);
  if (args.signal) q.set('signal', args.signal);
  await page.goto(`${base}?${q}`.replace(/=(&|$)/g, '$1'));
  sessions.push({ browser, page, tag });
  // Let the host claim the room first.
  await new Promise((r) => setTimeout(r, i === 0 ? 1500 : 300));
}

// Random key mashing on every player once the match is running.
const mash = async (s) => {
  while (Date.now() - t0 < secs * 1000 && !failed) {
    const key = keys[Math.floor(Math.random() * keys.length)];
    try {
      await s.page.focus('#canvas');
      await s.page.keyboard.down(key);
      await new Promise((r) => setTimeout(r, 50 + Math.random() * 600));
      await s.page.keyboard.up(key);
    } catch {}
    await new Promise((r) => setTimeout(r, Math.random() * 200));
  }
};
const shoot = async () => {
  for (const t of shots) {
    const wait = t * 1000 - (Date.now() - t0);
    if (wait > 0) await new Promise((r) => setTimeout(r, wait));
    for (const s of sessions) {
      const file = join(out, `${s.tag}-${String(t).padStart(4, '0')}.png`);
      await s.page.screenshot({ path: file }).catch(() => {});
      log(`${stamp()} ${s.tag} [shot] ${file}`);
    }
  }
};
// Start mashing after the game has had time to load (~20 s).
await new Promise((r) => setTimeout(r, Math.max(0, 20000 - (Date.now() - t0))));
await Promise.all([...sessions.map(mash), shoot()]);

const stats = [];
for (const s of sessions) {
  const st = await s.page
    .evaluate(() => {
      const ls = window.Module?.mssbNet?.lockstep;
      if (!ls) return null;
      return { frame: ls.frame, synced: window.mssbMesh.syncedFrame ?? -1, hashes: [...ls.hashes].slice(-20), aborted: ls.aborted };
    })
    .catch((e) => ({ error: String(e) }));
  stats.push({ tag: s.tag, ...st });
}
finished = true;
for (const s of sessions) await s.browser.close().catch(() => {});

// Hashes for the same frame must agree across peers.
const byFrame = new Map();
for (const st of stats) for (const [f, h] of st.hashes || []) (byFrame.get(f) || byFrame.set(f, new Map()).get(f)).set(st.tag, h);
let compared = 0;
for (const [f, m] of byFrame) {
  if (m.size < 2) continue;
  compared++;
  if (new Set(m.values()).size > 1 && !failed) failed = `hash mismatch at frame ${f}: ${JSON.stringify(Object.fromEntries(m))}`;
}
for (const st of stats) {
  console.log(`${st.tag}: frame ${st.frame}, last frame all peers agreed on ${st.synced}${st.aborted ? `, stopped: ${st.aborted}` : ''}${st.error ? `, ${st.error}` : ''}`);
  if (!failed && !(st.frame >= minFrames)) failed = `${st.tag} only reached frame ${st.frame}`;
}
console.log(failed ? `FAIL: ${failed}` : `PASS: ${players} players, ${compared} common hash checkpoints, no desync`);
process.exit(failed ? 1 : 0);
