# Plan: a trimmed "web disc" with only what's playable

Goal: the web build carries everything needed to play, still behind the
password, and nothing the web build can't reach. One download on the first
visit; after that, no network reads during play.

## Status (2026-10-14): done, not yet deployed

All five steps are in; see `port/DEPLOY.md` ("Web disc") for how it works.

- Keep-list: `port/web/web_disc.json`, **256 of 1213 chunks, 128 MB** (101.5 MB
  of data: 62 MB of `ZZZZ.dat`, the Mario Stadium, replay, result and walk-in
  music, `aaaa.dat`, the system area). Built by `port/tools/web_disc.py` from
  four recorded sessions (`port/tools/record_web_disc.sh`: the front end into a
  game, and three skipfe games covering all 54 characters), widened to whole
  file-table entries, whole tables the recordings used most of, and every
  character-indexed table. It includes every boot-pack byte.
- Loader (`port/web/loader.js`, `WebDisc`): after the boot pack, the chunks
  download in the background into the Cache API; later visits skip the boot
  pack and read everything from storage. Checked locally with
  `port/tools/web_disc_check.mjs` against `deploy_cloudflare.sh dev`: second
  visit, 0 disc requests.
- Safety net: reads outside the list are logged with the disc file and offset
  and fetched from the full disc, which stays deployed.
  `MSSB_WEB_DISC_ONLY=1` deploys only the list once real play logs are clean.
- Scope guard (`port/game/menu_scope.c`): online and practice games are at
  Mario Stadium (the lobby offers only it; skipfe falls back to it), and
  Challenge's module refuses to load. Each other stadium would add about 22 MB
  (5 MB of data, 17 MB of music).
- Left: deploy, then watch `?debug` play logs for `[web disc] read outside`
  lines and add what they show (rerecord, or a session that reaches it).

## What's on the disc today

The image is 1.46 GB, but only 20 files (601 MB of data); the rest is empty
space. `mario_baseball.iso` is a CISO that stores 635 MB.

| File | Size | Contents |
|---|---|---|
| `/ZZZZ.dat` | 429 MB | One archive with almost all game data: models, textures, animations, stadiums, menus, sound banks. The game finds entries through its own offset tables. |
| `/snd/my_snd_h/*.adp` (17 files) | 170 MB | Music: one song per stadium (`mario_01`, `peach`, `wario`, `yoshi`, `donkey`, `koopa`), `toy`, Challenge (`cha_map`, `cha_s_roll`, `cha_victry`, `cha_demo`, `cha_end_jin`), `replay`, `result`, `home_in`, `star_01`, `star_03`. |
| `/aaaa.dat` | 1.5 MB | |
| `/opening.bnr` | small | Banner |

## What's playable on the web

The front-end menus (Exhibition at Mario Stadium, Practice, Options) and every
character. Not playable: Challenge mode, minigames, Toy Field, the other
stadiums, movies.

## Size estimate

A front-end session plus a full 3-inning game touched about **64 MB** of the
disc (counted in 512 KB blocks). With every captain and character in the mix
the playable set is probably **100–150 MB**.

## Plan

### 1. Work out exactly what's playable (the keep-list)

Two sources, combined:

- **Recording.** A tool like `port/tools/record_boot_pack.mjs` logs every
  disc read (file, offset, length) during scripted sessions that cover
  everything reachable on the web:
  - every captain and every character (`skipfe` runs through team combinations)
  - all menus, Practice, Options
  - in-game events: home runs, replays, star moves, the mercy rule, the
    result screen
- **Static.** The decomp has the game's asset tables, so `ZZZZ.dat` entries
  can be labelled by what uses them (stadium, character, Challenge,
  minigame). This catches entries the recordings miss, such as a rare
  animation. Keeping every Mario Stadium and character entry wholesale is
  cheap insurance.

The keep-list is the union of the two.

### 2. Build the web disc with the same layout

Keep the same FST and the same file offsets, so the game code needs no
changes. Everything outside the keep-list becomes zeros:

- `ZZZZ.dat` keeps only the needed entries; Challenge, minigames, Toy Field
  and the other stadiums go.
- Music keeps `mario_01`, `replay`, `result`, `home_in`, `star_01`,
  `star_03`, and whatever the menus use.

Zero blocks cost nothing: CISO already skips them, and the chunk deploy can
skip all-zero chunks. The builder is a Python script next to
`port/tools/deploy_cloudflare.sh`.

### 3. Ship it as a one-time download

- The boot pack still streams first, so the main menu stays at ~3 s after Play.
- The rest of the web disc downloads in the background into persistent
  browser storage (Cache API or OPFS), with `navigator.storage.persist()` and
  a small progress indicator.
- After the first visit everything loads from the device; nothing comes over
  the network. 100–150 MB is well within what iOS Safari allows a site.
- Reads go through the asynchronous disc path (`Disc.prefetch`,
  `port/src/dvd_irq.c`), so a read that comes before its bytes have
  downloaded waits without stalling the game.

### 4. Safety net while coverage matures

- Ship a bitmap of the kept ranges with the web disc.
- A read outside it is logged loudly under `?debug` (file and offset), and
  the page fetches those bytes from the full chunked disc, which stays
  deployed behind the password.
- A coverage gap is then a log line and a one-off fetch, not a broken game.
  The keep-list is final once real play logs show no misses; then the full
  disc can come off the site.

### 5. Lock the scope in the game

The menus already offer only Exhibition at Mario Stadium, Practice and
Options. Add a guard so nothing can reach a trimmed mode (a clear error
rather than reading zeros).

## Result

- **Download:** ~100–150 MB once, instead of streaming pieces of a 635 MB image.
- **Hitches:** no network reads during play from the second visit on.
- **Password:** still gates the data exactly as today.

## Work, in order

1. Read-recording tool and scripted coverage runs; static labelling of
   `ZZZZ.dat` entries from the decomp's asset tables. Output: the keep-list.
2. Web-disc builder (keep-list → zero-filled image → chunks + kept-range
   bitmap), wired into `deploy_cloudflare.sh`.
3. Loader: background download into persistent storage, progress UI, reads
   served from storage.
4. Out-of-range read logging and fallback to the full disc.
5. In-game scope guard.

The riskiest part is coverage; step 4 makes it safe to iterate on.
