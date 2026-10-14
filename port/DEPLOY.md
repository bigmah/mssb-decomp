# Deploying the web build

The browser build runs on Cloudflare's free plan as one Worker, set up the same
way as the strikers port's.

The live URL (`https://mssb.<subdomain>.workers.dev`) and the account ID are
deliberately not written anywhere in this repo. Keep it that way. To find the
URL, run `port/tools/deploy_cloudflare.sh` (it prints it) or look in the
Cloudflare dashboard under Workers & Pages.

## What's deployed

```
browser ──HTTPS──> Worker "mssb" (port/cloudflare/src/worker.js)
                     ├─ static assets: index.html, loader.js, net.js, pad.js, touch.js,
                     │                 mssb.js, mssb.wasm, initial_pipeline_cache.bin.gz
                     ├─ /disc/*  (password-locked disc chunks)
                     ├─ /signal/events, /signal/send ──> Durable Object "Room"
                     │                                    (one per room code)
                     └─ /signal/ice ──> Cloudflare TURN API (credentials)

browser <──WebRTC (direct, or relayed by Cloudflare TURN)──> browser
```

- **Static assets.** The web build's files, served by the Worker's asset
  binding.
- **Disc (password-locked).** If `mario_baseball.iso` is in the repo root or
  next to the repo (or `$MSSB_ISO`), the deploy script adds it as 512 KB chunks
  under `/disc/<sha256 prefix>/` plus `/disc/manifest.json`. Those paths always
  go through the Worker (`run_worker_first`), which returns 401 unless the
  request carries the unlock cookie. The page shows an Unlock screen;
  `POST /disc/unlock` with the right password (`DISC_PASSWORD` in
  `port/cloudflare/src/worker.js`) sets an HttpOnly cookie (Path=/disc, ~400
  days) holding an HMAC of the password, so changing the password locks every
  browser out again. Opening the site with `?password=...` fills in the
  Unlock screen and submits it, so that link can be shared. The chunks are
  the loader's 512 KB block size because the game's reads are scattered
  (booting to the first screen touches ~30 blocks across the disc); 4 MB chunks
  downloaded 2.5x as much. They barely compress (~10%), so they're stored raw.
  `boot_blocks.json` lists the ~50 blocks read from boot to the main menu
  (`port/tools/record_boot_blocks.mjs`; rerun it if the disc image changes),
  and the page fetches them six at a time as soon as the disc unlocks, while
  the player is still on the Play screen.

- **Online play** (`port/web/net.js`, `port/web/src/net_web.cpp`, from the
  strikers port). Two browsers, one per team, run the same game in input
  lockstep: only controller input crosses the network. The lobby (room code,
  captains, stadium, innings) is HTML; Start boots both straight into an
  exhibition game (`skipfe` with `human2` and a shared `seed`), and every 60
  frames the peers compare a hash of the game state (`port/game/net_state.c`).
- **Signaling.** Same protocol as `port/tools/signal.mjs` (Server-Sent Events
  plus POST). Each room code maps to a Durable Object (`idFromName(code)`),
  which relays lobby messages and WebRTC offers, answers and ICE candidates.
  Rooms exist only in memory; five seconds into a game each page closes its
  stream and the room goes idle.
- **TURN.** `/signal/ice` asks Cloudflare's TURN service for 12-hour
  credentials, using a TURN key stored as two Worker secrets (`TURN_KEY_ID`,
  `TURN_KEY_API_TOKEN`). Without them it returns STUN only plus an `error`
  field saying why. Players whose networks allow direct connections never touch
  the relay.

Config: `port/cloudflare/wrangler.jsonc`. The Durable Object class is
SQLite-backed (`new_sqlite_classes`), which is what the free plan allows.

## One-time setup

1. A Cloudflare account with a `workers.dev` subdomain.
2. An API token with **Workers Scripts: Edit** (and **Realtime / Calls: Edit**
   to create the TURN key), in your shell:
   ```sh
   export CLOUDFLARE_API_TOKEN=...
   export CLOUDFLARE_ACCOUNT_ID=...   # 32 hex characters
   ```
3. Node (for `npx wrangler`; the script pins wrangler 4).
4. After the first deploy, the TURN key (the secrets attach to the deployed
   Worker): `port/tools/deploy_cloudflare.sh turn`. Cloudflare only returns the
   key's secret when it's created, so if this goes wrong run it again and
   delete the old key in the dashboard (Realtime > TURN).

## Deploying a change

```sh
port/tools/build_web.sh              # rebuild build/web
port/tools/deploy_cloudflare.sh      # stage build/cf-assets and deploy
```

The script copies the web files and the disc chunks into `build/cf-assets`
(`build/web` also holds the CMake build tree, which must not be uploaded), then
runs `wrangler deploy` in `port/cloudflare/`. Only changed files are uploaded,
so the disc chunks go up once.

## Checking it works

Online play, locally: `node port/tools/web_serve.mjs &` then
`node port/tools/net_test.mjs --secs 120` (two headless Chromes join a room,
mash keys and compare state hashes; `PASS ... no desync`). Against the deployed
signaling and TURN: add `--signal $URL/ --relay`.

```sh
URL=https://mssb.<subdomain>.workers.dev
curl -sI $URL/mssb.wasm               # 200, application/wasm
curl -s $URL/disc/manifest.json       # "locked" (401) without the cookie
node port/tools/web_drive.mjs --url "$URL/?password=...&autostart" --secs 45 --shots 44 --out build/web-live
```

Locally: `port/tools/deploy_cloudflare.sh dev` (wrangler dev on
http://localhost:8787).

## Logs, rollback

- Live logs: `cd port/cloudflare && npx wrangler tail`.
- A phone's console: open the site with `?debug` (e.g. `?password=...&debug`) and
  the page posts its console to `/log`, which shows up in `wrangler tail`.
- Roll back to the previous version: `cd port/cloudflare && npx wrangler rollback`.
