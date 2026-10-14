// Online play: signaling client, WebRTC mesh, lobby state and the lockstep
// input exchange the game polls each frame (port/web/src/net_web.cpp).
// Ported from the strikers port (its docs/plan-online-mesh.md has the design);
// signaling runs in the Cloudflare Worker (port/cloudflare/src/worker.js).
'use strict';

const FRAME_MS = 1000 / 60;
const MAX_FRAMES_PER_PACKET = 40;
const STALL_NOTICE_MS = 250;
const STALL_ABORT_MS = 10000;
const HASH_SLACK_FRAMES = 6000; // remember hashes for ~100 s

// ---- Signaling (port/cloudflare/src/worker.js) --------------------------------

class Signaling {
  // base: where /signal/* lives ('' = this page's server).
  constructor(base, room, name, handlers) {
    this.base = base;
    this.handlers = handlers;
    this.es = new EventSource(`${base}signal/events?room=${encodeURIComponent(room)}&name=${encodeURIComponent(name)}`);
    this.es.onmessage = (e) => this.onEvent(JSON.parse(e.data));
    this.es.onerror = () => {
      if (this.es.readyState === EventSource.CLOSED) handlers.onClosed?.();
    };
  }

  onEvent(ev) {
    if (ev.t === 'welcome') {
      this.room = ev.room;
      this.id = ev.id;
      this.token = ev.token;
    }
    if (ev.t === 'error') this.es.close();
    this.handlers.onEvent(ev);
  }

  send(msg, to) {
    if (!this.token) return;
    fetch(`${this.base}signal/send`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ room: this.room, id: this.id, token: this.token, to, msg }),
    }).catch((e) => console.warn('[net] signaling send failed', e));
  }

  close() {
    this.es.close();
  }
}

// ---- One WebRTC connection to another browser --------------------------------

class Peer {
  constructor(mesh, id, name, initiator) {
    this.mesh = mesh;
    this.id = id;
    this.name = name;
    this.rtt = null;
    this.jitter = 0;
    this.pc = new RTCPeerConnection({ iceServers: mesh.iceServers, iceTransportPolicy: mesh.iceTransportPolicy });
    this.pc.onicecandidate = (e) => {
      if (e.candidate) mesh.signaling.send({ k: 'ice', cand: e.candidate.toJSON() }, id);
    };
    this.pc.onconnectionstatechange = () => {
      const s = this.pc.connectionState;
      if (s === 'failed' || s === 'closed') mesh.peerLost(this, `connection ${s}`);
      mesh.changed();
    };
    this.pendingIce = [];
    if (initiator) {
      // Inputs: unordered and never retransmitted (each packet repeats the
      // unacknowledged frames). Control: reliable and ordered.
      this.setInput(this.pc.createDataChannel('in', { ordered: false, maxRetransmits: 0 }));
      this.setCtl(this.pc.createDataChannel('ctl'));
      this.pc
        .createOffer()
        .then((o) => this.pc.setLocalDescription(o))
        .then(() => mesh.signaling.send({ k: 'sdp', desc: this.pc.localDescription.toJSON() }, id))
        .catch((e) => console.error('[net] offer failed', e));
    } else {
      this.pc.ondatachannel = (e) => (e.channel.label === 'in' ? this.setInput(e.channel) : this.setCtl(e.channel));
    }
  }

  get connected() {
    return this.input?.readyState === 'open' && this.ctl?.readyState === 'open';
  }

  setInput(ch) {
    this.input = ch;
    ch.binaryType = 'arraybuffer';
    ch.onopen = () => this.mesh.changed();
    ch.onmessage = (e) => {
      const deliver = () => this.mesh.lockstep?.onPacket(this, new Uint8Array(e.data));
      const sim = this.mesh.netSim;
      if (!sim) deliver();
      else if (Math.random() >= sim.loss) setTimeout(deliver, sim.lag + Math.random() * sim.jitter);
    };
  }

  setCtl(ch) {
    this.ctl = ch;
    ch.onopen = () => {
      this.mesh.changed();
      this.ping();
    };
    ch.onclose = () => this.mesh.peerLost(this, 'channel closed');
    ch.onmessage = (e) => {
      const sim = this.mesh.netSim;
      const m = JSON.parse(e.data);
      if (sim) setTimeout(() => this.onCtl(m), sim.lag + sim.jitter / 2);
      else this.onCtl(m);
    };
  }

  async onSignal(msg) {
    if (msg.k === 'sdp') {
      await this.pc.setRemoteDescription(msg.desc);
      if (msg.desc.type === 'offer') {
        await this.pc.setLocalDescription(await this.pc.createAnswer());
        this.mesh.signaling.send({ k: 'sdp', desc: this.pc.localDescription.toJSON() }, this.id);
      }
      for (const c of this.pendingIce.splice(0)) await this.pc.addIceCandidate(c).catch(() => {});
    } else if (msg.k === 'ice') {
      if (this.pc.remoteDescription) await this.pc.addIceCandidate(msg.cand).catch(() => {});
      else this.pendingIce.push(msg.cand);
    }
  }

  sendCtl(msg) {
    if (this.ctl?.readyState === 'open') this.ctl.send(JSON.stringify(msg));
  }

  sendInput(bytes) {
    if (this.input?.readyState === 'open' && this.input.bufferedAmount < 64 * 1024) this.input.send(bytes);
  }

  ping() {
    this.sendCtl({ k: 'ping', t: performance.now() });
  }

  onCtl(m) {
    if (m.k === 'ping') this.sendCtl({ k: 'pong', t: m.t });
    else if (m.k === 'pong') {
      const rtt = performance.now() - m.t;
      if (this.rtt === null) this.rtt = rtt;
      this.jitter = this.jitter * 0.8 + Math.abs(rtt - this.rtt) * 0.2;
      this.rtt = this.rtt * 0.8 + rtt * 0.2;
      this.mesh.changed();
    } else this.mesh.lockstep?.onCtl(this, m);
  }

  close() {
    this.pc.close();
  }
}

// ---- Lockstep: per-frame inputs from every port ------------------------------

// Packet: u8 type (1) | u8 port | u32 firstFrame | u8 count | count x 8 bytes |
// u32 ack (highest frame this sender has from the receiver, contiguous).
class Lockstep {
  constructor(mesh, match, localPort) {
    this.mesh = mesh;
    this.localPort = localPort;
    this.delay = match.delay;
    this.activeMask = match.activeMask;
    // Ports whose inputs each frame waits for: the human ports, plus a practice
    // bot's (its port is CPU-played but its packets still have to arrive).
    this.waitMask = match.waitMask ?? match.activeMask;
    this.stallCount = 0;
    this.stallMs = 0;
    this.portOf = new Map(); // peer id -> port
    match.slots.forEach((id, port) => id && this.portOf.set(id, port));
    this.inputs = [0, 1, 2, 3].map(() => new Map());
    // Frames before `delay` have no input (all neutral).
    this.contig = [0, 1, 2, 3].map(() => this.delay - 1);
    this.acked = new Map(); // peer id -> highest of our frames it has
    this.hashes = new Map(); // frame -> our hash
    this.remoteHashes = new Map(); // frame -> Map(peer name -> hash)
    this.waiters = [];
    this.aborted = null;
    this.frame = 0;
    this.stallStart = 0;
    this.stallTimer = null;
    this.timer = setInterval(() => this.flush(), 16);
  }

  // -- Called by the game (net_web.cpp) --

  sendLocal(frame, bytes) {
    this.inputs[this.localPort].set(frame, bytes);
    this.contig[this.localPort] = frame;
    this.flush();
  }

  inputsFor(frame) {
    this.frame = frame;
    for (let p = 0; p < 4; p++) if ((this.waitMask >> p) & 1 && this.contig[p] < frame) return null;
    const out = new Uint8Array(32);
    for (let p = 0; p < 4; p++) {
      const b = this.inputs[p].get(frame);
      if (b) out.set(b, p * 8);
      this.inputs[p].delete(frame - 600);
    }
    return out;
  }

  wait() {
    if (this.aborted) return Promise.resolve(-1);
    return new Promise((resolve) => {
      const done = () => resolve(this.aborted ? -1 : 0);
      this.waiters.push(done);
      setTimeout(done, 8);
    });
  }

  stalled(frame, on) {
    clearTimeout(this.stallTimer);
    if (!on) {
      this.stallCount++;
      this.stallMs += performance.now() - this.stallStart;
      this.mesh.ui.waiting(null);
      return;
    }
    this.stallStart = performance.now();
    const check = () => {
      const waited = performance.now() - this.stallStart;
      const missing = this.missingNames(frame);
      if (waited >= STALL_ABORT_MS) {
        this.abort(`Lost contact with ${missing.join(', ') || 'the other players'}.`);
        return;
      }
      this.mesh.ui.waiting(missing.length ? `Waiting for ${missing.join(', ')}…` : 'Waiting…');
      this.stallTimer = setTimeout(check, 250);
    };
    this.stallTimer = setTimeout(check, STALL_NOTICE_MS);
  }

  localHash(frame, hash) {
    this.hashes.set(frame, hash >>> 0);
    this.hashes.delete(frame - HASH_SLACK_FRAMES);
    if (frame % 600 === 0) console.log(`[net] frame ${frame} hash ${(hash >>> 0).toString(16)}`);
    for (const peer of this.mesh.playingPeers()) peer.sendCtl({ k: 'hash', f: frame, h: hash >>> 0 });
    this.checkHash(frame);
  }

  // -- Network --

  flush() {
    if (this.aborted) return;
    const local = this.inputs[this.localPort];
    const last = this.contig[this.localPort];
    for (const peer of this.mesh.playingPeers()) {
      const port = this.portOf.get(peer.id);
      // Oldest unacknowledged frames first: the receiver needs them in order.
      const first = Math.max((this.acked.get(peer.id) ?? this.delay - 1) + 1, this.delay);
      const count = Math.max(0, Math.min(last - first + 1, MAX_FRAMES_PER_PACKET));
      const buf = new Uint8Array(11 + count * 8);
      const dv = new DataView(buf.buffer);
      buf[0] = 1;
      buf[1] = this.localPort;
      dv.setUint32(2, first >>> 0, true);
      buf[6] = count;
      for (let i = 0; i < count; i++) {
        const b = local.get(first + i);
        if (b) buf.set(b, 7 + i * 8);
      }
      dv.setUint32(7 + count * 8, Math.max(0, port === undefined ? 0 : this.contig[port]) >>> 0, true);
      peer.sendInput(buf);
    }
  }

  onPacket(peer, buf) {
    if (buf[0] !== 1 || buf.length < 11) return;
    const port = this.portOf.get(peer.id);
    if (port === undefined || buf[1] !== port) return;
    const dv = new DataView(buf.buffer, buf.byteOffset, buf.byteLength);
    const first = dv.getUint32(2, true);
    const count = buf[6];
    if (buf.length < 11 + count * 8) return;
    const store = this.inputs[port];
    for (let i = 0; i < count; i++) {
      const f = first + i;
      if (f > this.contig[port] && !store.has(f)) store.set(f, buf.slice(7 + i * 8, 15 + i * 8));
    }
    while (store.has(this.contig[port] + 1)) this.contig[port]++;
    const ack = dv.getUint32(7 + count * 8, true);
    if (ack > (this.acked.get(peer.id) ?? -1)) this.acked.set(peer.id, ack);
    this.wake();
  }

  onCtl(peer, m) {
    if (m.k === 'hash') {
      let byPeer = this.remoteHashes.get(m.f);
      if (!byPeer) this.remoteHashes.set(m.f, (byPeer = new Map()));
      byPeer.set(peer.name, m.h);
      this.remoteHashes.delete(m.f - HASH_SLACK_FRAMES);
      this.checkHash(m.f);
    } else if (m.k === 'bye') {
      this.abort(`${peer.name} ${m.reason || 'left the match'}.`, false);
    }
  }

  checkHash(frame) {
    const mine = this.hashes.get(frame);
    const theirs = this.remoteHashes.get(frame);
    if (mine === undefined || !theirs) return;
    for (const [name, h] of theirs) {
      if (h !== mine) {
        console.error(`[net] DESYNC at frame ${frame}: ours ${mine.toString(16)}, ${name} ${h.toString(16)}`);
        this.dumpLog(frame);
        this.abort(`The game went out of sync with ${name} (frame ${frame}).`);
        return;
      }
    }
    if (theirs.size === this.mesh.playingPeers().length) this.mesh.syncedFrame = frame;
  }

  dumpLog(frame) {
    const lines = [];
    for (let f = Math.max(0, frame - 120); f <= frame; f++) {
      const row = [0, 1, 2, 3].map((p) => {
        const b = this.inputs[p].get(f);
        return b ? [...b].map((x) => x.toString(16).padStart(2, '0')).join('') : '-'.repeat(16);
      });
      lines.push(`${f}: ${row.join(' ')}`);
    }
    console.error(`[net] inputs before the desync (port 0..3):\n${lines.join('\n')}`);
  }

  peerLost(peer) {
    if (this.portOf.has(peer.id)) this.abort(`${peer.name} disconnected.`);
  }

  abort(message, tellOthers = true) {
    if (this.aborted) return;
    this.aborted = message;
    console.error(`[net] match stopped: ${message}`);
    if (tellOthers) for (const peer of this.mesh.playingPeers()) peer.sendCtl({ k: 'bye', reason: 'stopped the match' });
    clearInterval(this.timer);
    this.mesh.ui.stopped(message);
    this.wake();
  }

  wake() {
    for (const w of this.waiters.splice(0)) w();
  }

  missingNames(frame) {
    const names = [];
    for (const [id, port] of this.portOf) {
      if (port === this.localPort || this.contig[port] >= frame) continue;
      names.push(this.mesh.peers.get(id)?.name || `player ${port + 1}`);
    }
    return names;
  }
}

// ---- The room: signaling, peers and the host-run lobby -------------------------

// The lobby's slots: one human per team. Port 0 plays team 1 (the away
// team, batting first), port 1 team 2. An empty slot's team is the computer's.
const SLOTS = 2;
const CAPTAINS = ['mario', 'luigi', 'peach', 'daisy', 'yoshi', 'birdo', 'wario', 'waluigi', 'dk', 'diddy', 'bowser', 'bowserjr'];
const STADIUMS = ['mario', 'peach', 'yoshi', 'dk', 'wario', 'bowser'];

class Mesh {
  constructor({ room, name, identity, ui, relayOnly, netSim, signalBase = '' }) {
    this.signalBase = signalBase;
    // Test hook: {loss (0..1), lag (ms), jitter (ms)} applied to incoming inputs.
    this.netSim = netSim;
    this.name = name;
    this.identity = identity; // {build, disc}: must match across peers
    this.ui = ui;
    this.peers = new Map(); // id -> Peer
    this.infos = new Map(); // id -> {name, build, disc, conns}
    this.iceTransportPolicy = relayOnly ? 'relay' : 'all';
    this.lobby = {
      slots: Array(SLOTS).fill(null),
      cfg: { captain1: 'mario', captain2: 'bowser', stadium: 'mario', innings: 3 },
    };
    this.lockstep = null;
    this.match = null;
    this.ready = this.init(room);
  }

  async init(room) {
    try {
      this.iceServers = (await (await fetch(`${this.signalBase}signal/ice`)).json()).iceServers;
    } catch {
      this.iceServers = [];
    }
    this.signaling = new Signaling(this.signalBase, room, this.name, {
      onEvent: (ev) => this.onSignal(ev),
      onClosed: () => this.ui.error('Lost the connection to the server.'),
    });
    setInterval(() => {
      for (const p of this.peers.values()) p.ping();
      this.reportConnections();
    }, 1000);
  }

  get id() {
    return this.signaling?.id;
  }

  get isHost() {
    return this.hostId === this.id;
  }

  onSignal(ev) {
    // In a match, peers are watched through their data channels; signaling
    // is being shut down (see startMatch) and its leave events mean nothing.
    if (this.match && ev.t !== 'msg') return;
    switch (ev.t) {
      case 'error':
        this.ui.error(ev.error);
        break;
      case 'welcome':
        this.hostId = ev.host;
        this.room = ev.room;
        this.infos.set(ev.id, { name: this.name, ...this.identity });
        for (const p of ev.peers) {
          this.infos.set(p.id, { name: p.name });
          this.peers.set(p.id, new Peer(this, p.id, p.name, true));
        }
        this.signaling.send({ k: 'hello', ...this.identity });
        if (this.isHost) this.takeSlot(this.ui.wantedPort ?? this.firstFreeSlot());
        else if (this.ui.wantedPort !== undefined) this.takeSlot(this.ui.wantedPort);
        break;
      case 'join':
        this.infos.set(ev.id, { name: ev.name });
        // The newcomer offers; wait for it.
        this.peers.set(ev.id, new Peer(this, ev.id, ev.name, false));
        if (this.isHost) this.signaling.send({ k: 'lobby', lobby: this.lobby }, ev.id);
        this.signaling.send({ k: 'hello', ...this.identity }, ev.id);
        break;
      case 'leave': {
        const peer = this.peers.get(ev.id);
        this.peers.delete(ev.id);
        this.infos.delete(ev.id);
        if (peer) {
          this.peerLost(peer, 'left');
          peer.close();
        }
        if (this.isHost) {
          this.lobby.slots = this.lobby.slots.map((s) => (s === ev.id ? null : s));
          this.publishLobby();
        }
        break;
      }
      case 'host':
        this.hostId = ev.id;
        if (this.isHost) {
          this.lobby.slots = this.lobby.slots.map((s) => (s && this.infos.has(s) ? s : null));
          this.publishLobby();
        }
        break;
      case 'msg':
        this.onMessage(ev.from, ev.msg);
        break;
    }
    this.changed();
  }

  onMessage(from, msg) {
    const peer = this.peers.get(from);
    switch (msg.k) {
      case 'sdp':
      case 'ice':
        peer?.onSignal(msg).catch((e) => console.error('[net] signaling', e));
        break;
      case 'hello':
        this.infos.set(from, { ...this.infos.get(from), build: msg.build, disc: msg.disc });
        break;
      case 'conns':
        this.infos.set(from, { ...this.infos.get(from), conns: msg.conns });
        break;
      case 'lobby':
        if (from === this.hostId) this.lobby = msg.lobby;
        break;
      case 'take':
        if (this.isHost) this.assignSlot(from, msg.port);
        break;
      case 'start':
        if (from === this.hostId) this.startMatch(msg.match);
        break;
    }
    this.changed();
  }

  // -- Lobby (host) --

  firstFreeSlot() {
    const i = this.lobby.slots.indexOf(null);
    return i < 0 ? -1 : i;
  }

  takeSlot(port) {
    if (this.isHost) this.assignSlot(this.id, port);
    else this.signaling.send({ k: 'take', port }, this.hostId);
  }

  assignSlot(id, port) {
    if (this.match) return;
    if (port >= 0 && port < SLOTS && this.lobby.slots[port] && this.lobby.slots[port] !== id) return;
    this.lobby.slots = this.lobby.slots.map((s) => (s === id ? null : s));
    if (port >= 0 && port < SLOTS) this.lobby.slots[port] = id;
    this.publishLobby();
  }

  setConfig(cfg) {
    if (!this.isHost || this.match) return;
    this.lobby.cfg = { ...this.lobby.cfg, ...cfg };
    this.publishLobby();
  }

  publishLobby() {
    this.signaling.send({ k: 'lobby', lobby: this.lobby });
    this.changed();
  }

  reportConnections() {
    const conns = [...this.peers.values()].filter((p) => p.connected).map((p) => p.id);
    this.infos.set(this.id, { ...this.infos.get(this.id), conns });
    if (!this.isHost && this.hostId) this.signaling.send({ k: 'conns', conns }, this.hostId);
    this.changed();
  }

  // Why the host can't start yet, or null.
  startProblem() {
    const players = this.lobby.slots.filter(Boolean);
    if (!players.length) return 'Nobody has a slot.';
    // Port 0 always plays the away team (skipfe); only the home team can be the computer's.
    if (!this.lobby.slots[0]) return 'Someone needs to play the away team.';
    const me = this.infos.get(this.id);
    for (const id of players) {
      const info = this.infos.get(id);
      if (!info) return 'A player left.';
      if (info.build && info.build !== me.build) return `${info.name} is running a different build of the game.`;
      if (info.disc && info.disc !== me.disc) return `${info.name}'s disc is a different version.`;
      if (!info.build || !info.disc) return `Waiting for ${info.name}'s game info…`;
      for (const other of players) {
        if (other === id) continue;
        if (!(info.conns || []).includes(other)) return `${info.name} isn't connected to ${this.infos.get(other)?.name} yet.`;
      }
    }
    if (this.infos.size > players.length) return 'Everyone in the room needs a slot.';
    return null;
  }

  // Input delay: covers the worst one-way trip plus jitter, at least 3 frames.
  pickDelay() {
    let worst = 0;
    for (const p of this.peers.values()) worst = Math.max(worst, (p.rtt ?? 50) / 2 + 2 * p.jitter);
    return Math.min(10, Math.max(3, Math.ceil(worst / FRAME_MS) + 1));
  }

  start() {
    if (!this.isHost || this.match || this.startProblem()) return;
    const seed = crypto.getRandomValues(new Uint32Array(1))[0] & 0x7fffffff;
    const activeMask = this.lobby.slots.reduce((m, s, i) => (s ? m | (1 << i) : m), 0);
    const match = { seed, delay: this.pickDelay(), activeMask, slots: this.lobby.slots, cfg: this.lobby.cfg };
    this.signaling.send({ k: 'start', match });
    this.startMatch(match);
  }

  startMatch(match) {
    if (this.match) return;
    const localPort = match.slots.indexOf(this.id);
    if (localPort < 0) {
      this.ui.error('The match started without you (no slot).');
      return;
    }
    this.match = match;
    this.lockstep = new Lockstep(this, match, localPort);
    console.log(`[net] starting: port ${localPort}, delay ${match.delay}, seed ${match.seed}`);
    this.ui.startGame(match, localPort, this.lockstep);
    // The mesh is up and nothing else goes through the server: let go of it
    // (on Cloudflare this lets the room's Durable Object sleep).
    setTimeout(() => this.signaling.close(), 5000);
  }

  playingPeers() {
    if (!this.match) return [];
    return [...this.peers.values()].filter((p) => this.match.slots.includes(p.id));
  }

  peerLost(peer, why) {
    this.lockstep?.peerLost(peer, why);
  }

  changed() {
    this.ui.render?.(this);
  }
}

// user.ini for an online match: straight into an exhibition game (skipfe,
// port/game/skipfe.c) with the lobby's settings, a human on each taken slot's
// port, and the shared random seed.
function onlineUserIni(match) {
  const c = match.cfg;
  return [
    'skipfe = true',
    `captain1 = ${c.captain1}`,
    `captain2 = ${c.captain2}`,
    `stadium = ${c.stadium}`,
    `innings = ${c.innings}`,
    `human1 = ${match.activeMask & 1 ? 'true' : 'false'}`,
    `human2 = ${match.activeMask & 2 ? 'true' : 'false'}`,
    `seed = ${match.seed}`,
  ].join('\n') + '\n';
}

// ---- Practice: one browser against a simulated remote player -----------------

// Stands in for the other browser of a 1v1: it runs its own copy of the
// lockstep clock (60 frames/s, never ahead of the inputs it has from us),
// sends neutral inputs for its port with the real packet format, redundancy
// and acks, and every packet in either direction goes through a fake network
// with the chosen latency, jitter and loss. Its port is played by the CPU.
class PracticePeer {
  constructor(mesh, port, net) {
    this.mesh = mesh;
    this.id = 'bot';
    this.name = 'Bot';
    this.port = port;
    this.net = net; // {rtt, jitter, loss}: rtt in ms, jitter in ms, loss 0..1
    this.connected = true;
    this.rtt = net.rtt;
    this.jitter = net.jitter;
    this.frame = 0; // the bot's next frame to run
    this.haveOurs = -1; // our frames it has, contiguous
    this.ackedByUs = -1; // its frames we've acknowledged
    this.lastSent = -1;
    this.t0 = 0;
  }

  // One way across the fake network: maybe dropped, else delayed by half the
  // RTT plus jitter (which also reorders packets, like the real thing).
  across(fn) {
    if (Math.random() < this.net.loss) return;
    setTimeout(fn, this.net.rtt / 2 + Math.random() * this.net.jitter);
  }

  start(delay) {
    this.delay = delay;
    this.haveOurs = delay - 1;
    this.ackedByUs = delay - 1;
    this.lastSent = delay - 1;
    this.t0 = performance.now();
    this.timer = setInterval(() => this.tick(), 4);
  }

  tick() {
    const ls = this.mesh.lockstep;
    if (!ls || ls.aborted) return clearInterval(this.timer);
    // Run frames on schedule while our inputs for them have arrived.
    const due = Math.floor((performance.now() - this.t0) / FRAME_MS);
    while (this.frame <= due && this.haveOurs >= this.frame) {
      this.lastSent = this.frame + this.delay; // its (neutral) input for later
      this.frame++;
    }
    // Send what we haven't acknowledged, at most every 16 ms.
    const now = performance.now();
    if (now - (this.lastPacket || 0) < 16) return;
    this.lastPacket = now;
    const first = this.ackedByUs + 1;
    const count = Math.max(0, Math.min(this.lastSent - first + 1, MAX_FRAMES_PER_PACKET));
    const buf = new Uint8Array(11 + count * 8);
    const dv = new DataView(buf.buffer);
    buf[0] = 1;
    buf[1] = this.port;
    dv.setUint32(2, first, true);
    buf[6] = count;
    dv.setUint32(7 + count * 8, Math.max(0, this.haveOurs), true);
    this.across(() => this.mesh.lockstep?.onPacket(this, buf));
  }

  // Our packets to it.
  sendInput(bytes) {
    const copy = bytes.slice();
    this.across(() => {
      const dv = new DataView(copy.buffer);
      const first = dv.getUint32(2, true);
      const count = copy[6];
      if (first <= this.haveOurs + 1) this.haveOurs = Math.max(this.haveOurs, first + count - 1);
      this.ackedByUs = Math.max(this.ackedByUs, dv.getUint32(7 + count * 8, true));
    });
  }

  sendCtl() {}
  ping() {}
}

// Starts a practice match: you on port 0 (team 1), the simulated player on
// port 1 (team 2, CPU-controlled).
function startPractice({ net, cfg, ui }) {
  const mesh = { ui, peers: new Map(), lockstep: null, playingPeers: () => [bot] };
  const bot = new PracticePeer(mesh, 1, net);
  mesh.peers.set(bot.id, bot);
  const delay = Math.min(10, Math.max(3, Math.ceil((net.rtt / 2 + 2 * net.jitter) / FRAME_MS) + 1));
  const match = {
    seed: crypto.getRandomValues(new Uint32Array(1))[0] & 0x7fffffff,
    delay,
    activeMask: 0b01,
    waitMask: 0b11,
    slots: ['me', bot.id],
    cfg,
  };
  mesh.lockstep = new Lockstep(mesh, match, 0);
  bot.start(delay);
  console.log(`[net] practice: ping ${net.rtt} ms, jitter ${net.jitter} ms, loss ${net.loss * 100}%, delay ${delay} frames`);
  return { match, lockstep: mesh.lockstep, bot };
}

window.MssbNet = { Mesh, onlineUserIni, startPractice, CAPTAINS, STADIUMS };
