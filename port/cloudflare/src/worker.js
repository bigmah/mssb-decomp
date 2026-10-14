// The web build on Cloudflare: one Worker serves the page and game (static
// assets). The disc image is deployed with them as 4 MB chunks under /disc/
// (port/tools/deploy_cloudflare.sh), but only served to a browser that has
// unlocked it with DISC_PASSWORD:
//   POST /disc/unlock   {password} -> sets a long-lived HttpOnly cookie
//   GET  /disc/*        the chunks and manifest.json; 401 without the cookie
const encoder = new TextEncoder();

function json(body, status = 200, extra = {}) {
  return new Response(JSON.stringify(body), {
    status,
    headers: { 'Content-Type': 'application/json', 'Cache-Control': 'no-store', ...extra },
  });
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
    return env.ASSETS.fetch(request);
  },
};
