// The web build on Cloudflare: one Worker serves the page and game (static
// assets), the disc behind a password, and online play's signaling, with each
// room held by a Durable Object (the same protocol as the strikers port's
// server/signal.mjs):
//   GET  /signal/events?room=CODE&name=NAME   Server-Sent Events stream
//   POST /signal/send   {room, id, token, to?, msg}
//   GET  /signal/ice    {iceServers}, with Cloudflare TURN credentials when the
//                       TURN_KEY_ID / TURN_KEY_API_TOKEN secrets are set.
// Rooms only matter until a match starts: the page closes its stream a few
// seconds in, and the Durable Object goes idle.
// The disc image is deployed with the static assets as 512 KB chunks under
// /disc/ (port/tools/deploy_cloudflare.sh), but only served to a browser that
// has unlocked it with DISC_PASSWORD:
//   POST /disc/unlock   {password} -> sets a long-lived HttpOnly cookie
//   GET  /disc/*        the chunks and manifest.json; 401 without the cookie
// Pages opened with ?debug post their console to /log, which lands in the
// Worker's logs: watch with `cd port/cloudflare && npx wrangler tail`.
//   POST /log           {id, lines: [string]}
import { DurableObject } from 'cloudflare:workers';

const MAX_PEERS = 4; // two players plus friends watching the lobby
const encoder = new TextEncoder();
const CORS = {
  'Access-Control-Allow-Origin': '*',
  'Access-Control-Allow-Methods': 'GET, POST, OPTIONS',
  'Access-Control-Allow-Headers': 'Content-Type',
};

function json(body, status = 200, extra = {}) {
  return new Response(JSON.stringify(body), {
    status,
    headers: { 'Content-Type': 'application/json', 'Cache-Control': 'no-store', ...CORS, ...extra },
  });
}

function roomCode(s) {
  return (s || '').toUpperCase().replace(/[^A-Z0-9]/g, '').slice(0, 8);
}

function randomHex(bytes) {
  return [...crypto.getRandomValues(new Uint8Array(bytes))].map((b) => b.toString(16).padStart(2, '0')).join('');
}

function sse(event) {
  return encoder.encode(`data: ${JSON.stringify(event)}\n\n`);
}

const SSE_HEADERS = {
  'Content-Type': 'text/event-stream',
  'Cache-Control': 'no-cache',
  ...CORS,
};

export class Room extends DurableObject {
  constructor(ctx, env) {
    super(ctx, env);
    this.peers = new Map(); // id -> {id, token, name, controller}
    this.host = null;
  }

  async fetch(request) {
    const url = new URL(request.url);
    if (url.pathname === '/signal/events') return this.join(url);
    if (url.pathname === '/signal/send') return this.relay(await request.json());
    return new Response('not found', { status: 404 });
  }

  send(peer, event) {
    try {
      peer.controller.enqueue(sse(event));
    } catch {
      this.leave(peer); // stream already gone
    }
  }

  broadcast(event, except) {
    for (const p of [...this.peers.values()]) if (p.id !== except) this.send(p, event);
  }

  join(url) {
    const code = roomCode(url.searchParams.get('room'));
    const name = (url.searchParams.get('name') || 'Player').slice(0, 24);
    if (this.peers.size >= MAX_PEERS) {
      return new Response(sse({ t: 'error', error: 'That room is full.' }), { headers: SSE_HEADERS });
    }
    const peer = { id: randomHex(4), token: randomHex(12), name, controller: null, keepAlive: null };
    const room = this;
    const body = new ReadableStream({
      start(controller) {
        peer.controller = controller;
        const others = [...room.peers.values()].map((p) => ({ id: p.id, name: p.name }));
        room.peers.set(peer.id, peer);
        if (!room.host) room.host = peer.id;
        room.send(peer, { t: 'welcome', room: code, id: peer.id, token: peer.token, host: room.host, peers: others });
        room.broadcast({ t: 'join', id: peer.id, name }, peer.id);
        peer.keepAlive = setInterval(() => {
          try {
            controller.enqueue(encoder.encode(': ka\n\n'));
          } catch {
            room.leave(peer);
          }
        }, 15000);
      },
      cancel() {
        room.leave(peer);
      },
    });
    return new Response(body, { headers: SSE_HEADERS });
  }

  leave(peer) {
    if (!this.peers.has(peer.id)) return;
    clearInterval(peer.keepAlive);
    this.peers.delete(peer.id);
    try {
      peer.controller.close();
    } catch {}
    if (this.peers.size === 0) {
      this.host = null;
      return;
    }
    this.broadcast({ t: 'leave', id: peer.id, name: peer.name });
    if (this.host === peer.id) {
      this.host = this.peers.keys().next().value;
      this.broadcast({ t: 'host', id: this.host });
    }
  }

  relay(m) {
    const from = this.peers.get(m.id);
    if (!from || from.token !== m.token) return new Response(null, { status: 403, headers: CORS });
    const event = { t: 'msg', from: from.id, msg: m.msg };
    if (m.to) {
      const to = this.peers.get(m.to);
      if (to) this.send(to, event);
    } else {
      this.broadcast(event, from.id);
    }
    return new Response(null, { status: 204, headers: CORS });
  }
}

// Returns {iceServers, error?}: STUN only (with the reason) if TURN isn't available.
async function iceServers(env) {
  const stun = { urls: ['stun:stun.cloudflare.com:3478'] };
  if (!env.TURN_KEY_ID || !env.TURN_KEY_API_TOKEN) return { iceServers: [stun], error: 'TURN not configured' };
  try {
    const r = await fetch(`https://rtc.live.cloudflare.com/v1/turn/keys/${env.TURN_KEY_ID}/credentials/generate-ice-servers`, {
      method: 'POST',
      headers: { Authorization: `Bearer ${env.TURN_KEY_API_TOKEN}`, 'Content-Type': 'application/json' },
      body: JSON.stringify({ ttl: 12 * 3600 }),
    });
    if (!r.ok) throw new Error(`TURN credentials: HTTP ${r.status}`);
    const { iceServers } = await r.json();
    // Browsers stall on the port-53 alternatives; drop them.
    const servers = (Array.isArray(iceServers) ? iceServers : [iceServers]).map((s) => ({
      ...s,
      urls: [].concat(s.urls).filter((u) => !/:53(\?|$)/.test(u)),
    }));
    return { iceServers: servers };
  } catch (e) {
    console.error(e);
    return { iceServers: [stun], error: String(e.message || e) };
  }
}

// ---- Disc ------------------------------------------------------------------

const DISC_COOKIE = 'mssb_disc';
const DISC_PASSWORD = 'password';

// The cookie holds an HMAC of a fixed string under the password, so changing
// DISC_PASSWORD locks out every browser.
async function discToken() {
  const key = await crypto.subtle.importKey('raw', encoder.encode(DISC_PASSWORD), { name: 'HMAC', hash: 'SHA-256' }, false, ['sign']);
  const mac = await crypto.subtle.sign('HMAC', key, encoder.encode('mssb-disc-v1'));
  return btoa(String.fromCharCode(...new Uint8Array(mac))).replace(/[+/=]/g, (c) => ({ '+': '-', '/': '_', '=': '' })[c]);
}

function sameBytes(a, b) {
  const x = encoder.encode(a);
  const y = encoder.encode(b);
  let diff = x.length ^ y.length;
  for (let i = 0; i < Math.min(x.length, y.length); i++) diff |= x[i] ^ y[i];
  return diff === 0;
}

function cookie(request, name) {
  for (const part of (request.headers.get('Cookie') || '').split(';')) {
    const [k, ...v] = part.trim().split('=');
    if (k === name) return v.join('=');
  }
  return null;
}

async function disc(request, env, url) {
  const token = await discToken();
  if (url.pathname === '/disc/unlock' && request.method === 'POST') {
    let password = '';
    try {
      password = String((await request.json()).password || '');
    } catch {}
    if (!sameBytes(password, DISC_PASSWORD)) {
      await new Promise((r) => setTimeout(r, 1000)); // slow down guessing
      return json({ ok: false }, 403);
    }
    const secure = url.protocol === 'https:' ? '; Secure' : '';
    return json({ ok: true }, 200, {
      'Set-Cookie': `${DISC_COOKIE}=${token}; Path=/disc; Max-Age=34560000; HttpOnly; SameSite=Strict${secure}`,
    });
  }
  const have = cookie(request, DISC_COOKIE);
  if (!have || !sameBytes(have, token)) return new Response('locked', { status: 401, headers: { 'Cache-Control': 'no-store' } });
  const r = await env.ASSETS.fetch(request);
  if (!r.ok) return r;
  const headers = new Headers(r.headers);
  headers.set('Cache-Control', 'private, max-age=31536000, immutable');
  if (url.pathname.endsWith('manifest.json')) headers.set('Cache-Control', 'private, no-cache');
  return new Response(r.body, { status: r.status, headers });
}

export default {
  async fetch(request, env) {
    const url = new URL(request.url);
    if (url.pathname.startsWith('/disc/')) return disc(request, env, url);
    if (url.pathname === '/log' && request.method === 'POST') {
      try {
        const { id, lines } = await request.json();
        for (const line of [].concat(lines).slice(0, 200)) console.log(`[${String(id).slice(0, 8)}] ${String(line).slice(0, 2000)}`);
      } catch {}
      return new Response(null, { status: 204 });
    }
    if (!url.pathname.startsWith('/signal/')) return env.ASSETS.fetch(request);
    if (request.method === 'OPTIONS') return new Response(null, { status: 204, headers: CORS });

    if (url.pathname === '/signal/ice' && request.method === 'GET') {
      return json(await iceServers(env));
    }
    if (url.pathname === '/signal/events' && request.method === 'GET') {
      const code = roomCode(url.searchParams.get('room'));
      if (!code) return new Response(sse({ t: 'error', error: 'No room code.' }), { headers: SSE_HEADERS });
      return env.ROOMS.get(env.ROOMS.idFromName(code)).fetch(request);
    }
    if (url.pathname === '/signal/send' && request.method === 'POST') {
      let m;
      try {
        m = await request.json();
      } catch {
        return new Response(null, { status: 400, headers: CORS });
      }
      const code = roomCode(m.room);
      if (!code) return new Response(null, { status: 400, headers: CORS });
      return env.ROOMS.get(env.ROOMS.idFromName(code)).fetch('https://room/signal/send', {
        method: 'POST',
        body: JSON.stringify(m),
      });
    }
    return new Response('not found', { status: 404, headers: CORS });
  },
};
