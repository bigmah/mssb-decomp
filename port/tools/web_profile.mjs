#!/usr/bin/env node
// CPU-profiles the web build in Chrome and lists what runs in long busy
// stretches (frames that miss their refresh): each stretch of samples between
// idle ones longer than --min ms, with its top functions by self time and by
// inclusive time.
//   node port/tools/web_profile.mjs --secs 90 --from 20 --query 'skipfe&env=MSSB_INPUT=600-100000/90:A'
// Needs port/tools/web_serve.mjs running (--port, default 8080).
import puppeteer from 'puppeteer-core';
import { writeFileSync } from 'node:fs';

const args = Object.fromEntries(
  process.argv.slice(2).reduce((acc, a, i, all) => (a.startsWith('--') ? [...acc, [a.slice(2), all[i + 1]]] : acc), []),
);
const secs = Number(args.secs || 60);
const from = Number(args.from || 10);
const minMs = Number(args.min || 20);
const port = args.port || 8080;
const url = `http://localhost:${port}/?iso=disc.iso&autostart&stats` + (args.query ? '&' + args.query : '');

const browser = await puppeteer.launch({
  executablePath: '/Applications/Google Chrome.app/Contents/MacOS/Google Chrome',
  headless: args.headed ? false : 'new',
  args: ['--enable-unsafe-webgpu', '--autoplay-policy=no-user-gesture-required', '--window-size=1340,1100'],
  defaultViewport: { width: 1280, height: 1010 },
});
const page = await browser.newPage();
page.on('console', (m) => {
  if (m.text().startsWith('[stats]') || m.type() === 'error') console.log(m.text());
});
await page.goto(url);
await new Promise((r) => setTimeout(r, from * 1000));
const cdp = await page.createCDPSession();
await cdp.send('Profiler.enable');
await cdp.send('Profiler.setSamplingInterval', { interval: 250 });
await cdp.send('Profiler.start');
await new Promise((r) => setTimeout(r, (secs - from) * 1000));
const { profile } = await cdp.send('Profiler.stop');
await browser.close();
if (args.out) writeFileSync(args.out, JSON.stringify(profile));

const nodes = new Map(profile.nodes.map((n) => [n.id, n]));
const parent = new Map();
for (const n of profile.nodes) for (const c of n.children || []) parent.set(c, n.id);
const name = (n) => n.callFrame.functionName || `(${n.callFrame.url.split('/').pop() || 'anon'})`;
const idle = new Set(profile.nodes.filter((n) => ['(idle)', '(program)'].includes(n.callFrame.functionName)).map((n) => n.id));

// Busy stretches.
const stretches = [];
let cur = null;
let t = profile.startTime;
profile.samples.forEach((id, i) => {
  t += profile.timeDeltas[i];
  if (idle.has(id)) {
    if (cur) stretches.push(cur);
    cur = null;
  } else {
    if (!cur) cur = { start: t, end: t, samples: [] };
    cur.end = t;
    cur.samples.push({ id, dt: profile.timeDeltas[i + 1] || 0 });
  }
});
const total = stretches.reduce((a, s) => a + (s.end - s.start), 0) / 1000;
const long = stretches.filter((s) => (s.end - s.start) / 1000 >= minMs);
console.log(`${stretches.length} busy stretches, ${total.toFixed(0)} ms busy; ${long.length} >= ${minMs} ms`);
const top = (map, n) => [...map.entries()].sort((a, b) => b[1] - a[1]).slice(0, n);
const report = (label, samples) => {
  const self = new Map();
  const incl = new Map();
  for (const { id, dt } of samples) {
    const n = nodes.get(id);
    self.set(name(n), (self.get(name(n)) || 0) + dt);
    const seen = new Set();
    for (let p = id; p !== undefined; p = parent.get(p)) {
      const nm = name(nodes.get(p));
      if (seen.has(nm)) continue;
      seen.add(nm);
      incl.set(nm, (incl.get(nm) || 0) + dt);
    }
  }
  console.log(label);
  console.log('  self: ' + top(self, 12).map(([k, v]) => `${k} ${(v / 1000).toFixed(1)}`).join(', '));
  console.log('  incl: ' + top(incl, 30).map(([k, v]) => `${k} ${(v / 1000).toFixed(1)}`).join(', '));
};
for (const s of long.sort((a, b) => b.end - b.start - (a.end - a.start)).slice(0, Number(args.n || 8)))
  report(`--- ${((s.start - profile.startTime) / 1e6).toFixed(2)} s, ${((s.end - s.start) / 1000).toFixed(1)} ms`, s.samples);
report('=== all long stretches', long.flatMap((s) => s.samples));
report('=== everything', stretches.flatMap((s) => s.samples));
