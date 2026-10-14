#!/usr/bin/env node
// Signaling for online play (port/web/net.js; from the strikers port): rooms by short code,
// relaying WebRTC offers/answers/ICE candidates and lobby messages between the
// browsers in a room. It never sees game state; once a match starts the peers
// talk directly (or through TURN).
//
// Plain HTTP, no dependencies:
//   GET  /signal/events?room=CODE&name=NAME   Server-Sent Events stream. First
//        event: {t:'welcome', id, token, host, peers:[{id,name}]}, then
//        {t:'join'|'leave', id, name}, {t:'host', id}, {t:'msg', from, msg}.
//   POST /signal/send   {room, id, token, to?, msg}   to one peer, or all others.
//   GET  /signal/ice    {iceServers} for RTCPeerConnection, with time-limited
//        TURN credentials (TURN REST scheme) when TURN_SECRET is set.
//
// Environment: TURN_SECRET (coturn static-auth-secret), TURN_URLS
// (comma-separated turn: URLs), STUN_URLS (default: Google's STUN server).
//
// Used by port/tools/web_serve.mjs for local and LAN play; the deployed site
// has the same protocol in its Cloudflare Worker (port/cloudflare/src/worker.js).
//   node port/tools/signal.mjs [port]      (listens on 127.0.0.1, default 8787)
import { createServer } from 'node:http';
import { createHmac, randomBytes } from 'node:crypto';
import { fileURLToPath } from 'node:url';

const MAX_PEERS = 4;
const MAX_BODY = 64 * 1024;

export function createSignaling(env = process.env) {
  const rooms = new Map(); // code -> { peers: Map<id, peer>, host }

  function iceServers(id) {
    const stun = (env.STUN_URLS ?? 'stun:stun.l.google.com:19302').split(',').filter(Boolean);
    const servers = stun.length ? [{ urls: stun }] : [];
    if (env.TURN_SECRET && env.TURN_URLS) {
      const username = `${Math.floor(Date.now() / 1000) + 12 * 3600}:${id || 'strikers'}`;
      const credential = createHmac('sha1', env.TURN_SECRET).update(username).digest('base64');
      servers.push({ urls: env.TURN_URLS.split(',').filter(Boolean), username, credential });
    }
    return servers;
  }

  function send(peer, event) {
    peer.res.write(`data: ${JSON.stringify(event)}\n\n`);
  }

  function broadcast(room, event, except) {
    for (const p of room.peers.values()) if (p.id !== except) send(p, event);
  }

  function join(req, res, url) {
    const code = (url.searchParams.get('room') || '').toUpperCase().replace(/[^A-Z0-9]/g, '').slice(0, 8);
    const name = (url.searchParams.get('name') || 'Player').slice(0, 24);
    res.writeHead(200, {
      'Content-Type': 'text/event-stream',
      'Cache-Control': 'no-cache',
      Connection: 'keep-alive',
      'X-Accel-Buffering': 'no',
    });
    if (!code) {
      res.end(`data: ${JSON.stringify({ t: 'error', error: 'No room code.' })}\n\n`);
      return;
    }
    let room = rooms.get(code);
    if (!room) rooms.set(code, (room = { peers: new Map(), host: null }));
    if (room.peers.size >= MAX_PEERS) {
      res.end(`data: ${JSON.stringify({ t: 'error', error: 'That room is full.' })}\n\n`);
      return;
    }
    const peer = { id: randomBytes(4).toString('hex'), token: randomBytes(12).toString('hex'), name, res };
    const others = [...room.peers.values()].map((p) => ({ id: p.id, name: p.name }));
    room.peers.set(peer.id, peer);
    if (!room.host) room.host = peer.id;
    send(peer, { t: 'welcome', room: code, id: peer.id, token: peer.token, host: room.host, peers: others });
    broadcast(room, { t: 'join', id: peer.id, name }, peer.id);
    console.log(`[signal] ${code}: ${name} (${peer.id}) joined, ${room.peers.size} in room`);

    const keepAlive = setInterval(() => res.write(': ka\n\n'), 15000);
    req.on('close', () => {
      clearInterval(keepAlive);
      room.peers.delete(peer.id);
      console.log(`[signal] ${code}: ${name} (${peer.id}) left, ${room.peers.size} in room`);
      if (room.peers.size === 0) {
        rooms.delete(code);
        return;
      }
      broadcast(room, { t: 'leave', id: peer.id, name });
      if (room.host === peer.id) {
        room.host = room.peers.keys().next().value;
        broadcast(room, { t: 'host', id: room.host });
      }
    });
  }

  function relay(req, res) {
    let body = '';
    req.on('data', (d) => {
      body += d;
      if (body.length > MAX_BODY) req.destroy();
    });
    req.on('end', () => {
      let m;
      try {
        m = JSON.parse(body);
      } catch {
        res.writeHead(400).end();
        return;
      }
      const room = rooms.get(m.room);
      const from = room?.peers.get(m.id);
      if (!from || from.token !== m.token) {
        res.writeHead(403).end();
        return;
      }
      const event = { t: 'msg', from: from.id, msg: m.msg };
      if (m.to) {
        const to = room.peers.get(m.to);
        if (to) send(to, event);
      } else {
        broadcast(room, event, from.id);
      }
      res.writeHead(204).end();
    });
  }

  // Returns true if it handled the request.
  return function handle(req, res) {
    const url = new URL(req.url, 'http://localhost');
    if (url.pathname === '/signal/events' && req.method === 'GET') {
      join(req, res, url);
      return true;
    }
    if (url.pathname === '/signal/send' && req.method === 'POST') {
      relay(req, res);
      return true;
    }
    if (url.pathname === '/signal/ice' && req.method === 'GET') {
      res.writeHead(200, { 'Content-Type': 'application/json', 'Cache-Control': 'no-store' });
      res.end(JSON.stringify({ iceServers: iceServers(url.searchParams.get('id')) }));
      return true;
    }
    return false;
  };
}

if (process.argv[1] === fileURLToPath(import.meta.url)) {
  const port = Number(process.argv[2] || process.env.PORT || 8787);
  const handle = createSignaling();
  createServer((req, res) => {
    if (!handle(req, res)) res.writeHead(404).end('not found');
  }).listen(port, '127.0.0.1', () => console.log(`signaling on 127.0.0.1:${port}`));
}
