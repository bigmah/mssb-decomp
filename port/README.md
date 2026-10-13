# MSSB PC port

Native macOS (arm64) build of Mario Superstar Baseball on
[aurora](https://github.com/encounter/aurora), following `~/dev/strikers`.
Plan: `docs/PORT_PLAN.md`. Progress and known problems: `port/STATUS.md`.

## Build

```sh
git submodule update --init port/extern/aurora
cmake -S port -B build/port -G Ninja
ninja -C build/port
```

The default target builds `build/port/mssb`. Run it with the disc image as
an argument, `MSSB_ISO=...`, or `mario_baseball.iso` in a parent folder of the
checkout. It does not get far yet: see `port/STATUS.md`.

Options:

- `-DMSSB_WERROR_64=OFF`: report the 64-bit pointer/int warnings instead of
  failing on them (they are errors by default).
- `-DMSSB_AURORA=OFF`: skip configuring aurora (no Dawn/SDL3/nod download).
  The game still compiles against aurora's headers.

## user.ini (straight into a game)

`user.ini` holds PC-only options, one `key = value` per line (`#`/`;`
comments, `[section]` lines ignored). It is read from `$MSSB_USER_INI`, else
from the user data folder. To skip the front end and boot straight into an
exhibition game:

```ini
skipfe = true
captain1 = mario     # player 1 (port 0); names below, or a character id
captain2 = bowser    # CPU
stadium = mario      # mario, bowser, wario, yoshi, peach, dk (or 0..5)
```

The boot task then loads game.rel instead of menus.rel, after loading the
stats file and building both teams the way the team menu's random-team option
does (`port/game/skipfe.c`). Captain names: mario, luigi, dk, diddy, peach,
daisy, yoshi, babymario, babyluigi, bowser, wario, waluigi, koopa, toad, boo,
toadette, shyguy, birdo, monty, bowserjr (see `sCharNames` for the rest).

```sh
printf 'skipfe = true\ncaptain1 = mario\ncaptain2 = bowser\n' > build/port/skipfe.ini
MSSB_USER_INI=$PWD/build/port/skipfe.ini MSSB_SKIP_MOVIES=1 port/tools/run.sh 90 10
```

## Controls, saves, audio

- Keyboard (port 1): arrows = stick, X = A, Z = B, C = X, V = Y,
  Enter = Start, Q/E = L/R, Shift = Z, IJKL = D-pad, WASD = C-stick.
  Gamepads work through SDL (aurora). Bindings saved by aurora
  (`keyboard_bindings.dat`) take precedence.
- Memory card: a GCI folder in the user data folder
  (`<user>/USA/Card A/01-GYQE-MarioBaseball.gci`). `MSSB_USER_DIR=path` uses
  another user folder (tests that must not touch the real save).
  The boot card check asks nothing: it uses the card (creating the save the
  first time) without the "Checking the Memory Card" notices.
  `MSSB_CARD_PROMPTS=1` restores the GameCube prompts (dolphin_compare.py).
- Music is DVD audio streaming (`/snd/my_snd_h/*.adp`), emulated in
  `port/src/audio/dtk.cpp`; sound effects and menu music are MusyX.
- Debug: `MSSB_AI_DUMP=file.raw` (s16 stereo of the final output, 32 kHz),
  `MSSB_DSP_STATS=1`, `MSSB_DSP_DUMP=file.raw`, `MSSB_DEBUG_DTK=1`,
  `MSSB_DEBUG_CARD=1`, `MSSB_DEBUG_INPUT=1`.

## Web build

Emscripten (`brew install emscripten`), WebGPU (Chrome):

```sh
port/tools/build_web.sh          # build/web: mssb.js, mssb.wasm, index.html, ...
node port/tools/web_serve.mjs    # http://localhost:8080
```

The page asks for the disc image once (.iso, .gcm or .ciso) and keeps a copy
in the browser's private storage (OPFS); the memory card and user data live in
IndexedDB (`/mssb`). `web_serve.mjs` also serves `../mario_baseball.iso` (or
`$MSSB_ISO`) as `disc.iso` for tests. Test URL parameters:
`?iso=disc.iso&autostart` (skip the picker), `&skipfe&captain1=mario&captain2=bowser`
(user.ini skip-front-end), `&movies` (play the movies; skipped by default on the web), `&stats` (fps and
audio queue in the console), `&env=KEY=VALUE;KEY=VALUE` (environment, e.g.
`MSSB_INPUT=500:A,800:A`).

Headless check with screenshots (puppeteer-core: `cd port/tools && npm install`):

```sh
node port/tools/web_drive.mjs --secs 60 --shots 20,40,60 --query 'nomovies&stats' --out build/web-shots
```

A whole exhibition through the front-end menus (3 innings, ~14 minutes):
`port/tools/web_full_game.sh 8080` (`build/web-game/console.log`, with
`MSSB_TRACE_GAME` output).

### Side by side with Dolphin

`port/tools/dolphin_compare.py` runs one input script on Dolphin (ground
truth) and on the web build and writes `build/compare/<scenario>/index.html`:
Dolphin, web and a diff image per frame, with the % of pixels that differ.

```sh
python3 port/tools/dolphin_compare.py menu   # boot -> title -> card prompts -> main menu -> captain select (~5 min)
python3 port/tools/dolphin_compare.py game   # -> exhibition, first innings (~25 min)
python3 port/tools/dolphin_compare.py x --input "500:A,800:A" --shots 300,900   # ad hoc
```

- Web (`port/tools/compare/web_capture.mjs`): headless Chrome with a fresh
  profile (no save), `?movies`, `MSSB_INPUT` plus `MSSB_FREEZE_FRAMES=600,900`:
  at each listed frame (PADRead count, the `MSSB_INPUT` clock) the game holds
  that frame (`port/src/freeze_frames.cpp`, `Module.mssbFrozen`) until the
  driver has saved the canvas and sets `Module.mssbRelease`.
- Dolphin (`port/tools/compare/dolphin.py`, `/Applications/Dolphin.app`):
  a private user folder `build/compare/dolphin-user` (fresh config and empty
  memory card each run), the script as a TAS movie (`compare/dtm.py`: MSSB
  polls the pad twice per field; the movie's tick count must be non-zero or
  playback stops at the first poll), frame dumping as PNGs (`-C
  Dolphin.Movie.DumpFrames=True`; ~20 frames/s at 2x, ~1 MB per frame, so
  only windows around the wanted frames are kept).
- Alignment: Dolphin shows the health screen 84 fields after the port's
  first PADRead and loads slower (save creation +170 fields, stadium +280), so
  each scenario has an offset schedule; each shot is then matched to the most
  similar Dolphin frame nearby and the report shows the drift. Menus line up
  to within a few frames; in-game the RNG differs (random teams, pitches:
  `OSGetTick`), so in-game shots are the same kind of scene, not the same
  frame. Movies run on wall-clock time, so captures inside a movie drift.
  `--skip-web`/`--skip-dolphin` reuse a previous capture; `--keep-dumps` keeps
  every Dolphin frame for re-alignment.

Scope (both builds): the menus offer Exhibition at Mario Stadium, Practice,
Records and Options; Challenge, Toy Field, Minigames and the other stadiums
are hidden (`port/game/menu_scope.c`). `allmodes = true` in user.ini or
`MSSB_ALLMODES=1` brings them back for testing. Star Skills is locked off
(no star moves, no star chances) and its Game Options row is gone;
`starskills = true` in user.ini brings it back.

How it differs from the native build:
- GPU pipelines (aurora `lib/gfx/pipeline_cache.cpp`): `createRenderPipeline`
  stalls the browser's GPU queue for a few frames, so the first time an effect
  appeared the game dropped frames (and, with aurora's 5-per-frame cap, drew
  the scene with pieces missing). On the web a draw never waits for its
  pipeline: it's built on the spot. Every config the game uses is appended to
  `/mssb/pipeline_cache.bin` (IndexedDB), and at boot the known ones, plus the
  bundled `port/web/initial_pipeline_cache.bin.gz`, compile in the background
  with `createRenderPipelineAsync`. Refresh the bundled list with
  `port/tools/pipeline_collect.sh 8080` (scripted scenarios in headless
  Chrome, merged by `port/tools/pipeline_seed.py`), e.g. after aurora bumps
  its pipeline config version. `?noseed` skips it; `?stats` logs each late
  frame with the pipelines built just before it.
- The game's OS threads are Emscripten fibers (Asyncify), scheduled
  cooperatively like the native run token (`port/web/src/os_threads_web.inc`,
  included by `port/src/os.cpp`); DVD completions and DSP/AI work are queued
  "interrupts" delivered when the game enables interrupts or waits.
- wasm traps on indirect calls whose signature doesn't match the callee
  (PowerPC doesn't care, so the game does it: tasks get a scratch buffer they
  ignore, draw-list callbacks get their node, emitter updates return a value
  some don't set). The sources are fixed instead: callbacks declare the
  arguments they're called with, scene tasks are called as `void(void)` on PC
  (`TASK_PARAM`, `include/main/scene_task.h`), and `TARGET_PC` thunks cover
  return-type mismatches. The build links at -O3 without emulation
  (`-DMSSB_WEB_LINK_OPT=-O1`, `-DMSSB_WEB_FPCAST=ON` for debugging).
  To find mismatches natively: build with Homebrew LLVM and
  `-DMSSB_SANITIZE_FUNCTION=ON` (`CC=/opt/homebrew/opt/llvm/bin/clang
  CXX=/usr/bin/clang++ cmake -S port -B build/port-fs -G Ninja
  -DMSSB_SANITIZE_FUNCTION=ON`), run with `MSSB_FNCHECK_LOG=file`, then
  `python3 port/tools/fncheck/report.py file` lists the calls whose wasm
  signatures differ from the callee's.
- wasm32 has 4-byte pointers: views with hand-computed 64-bit offsets are under
  `PORT_LP64` (defined by the prelude on 64-bit hosts); wasm32 uses the
  GameCube layout. Use `PORT_LP64`, not `TARGET_PC`, for any layout that
  hard-codes pointer sizes.
- CISO images are expanded on the fly (`port/web/src/web_platform.cpp`).
- REL module data is reset at each load between linker-order marker objects
  (wasm-ld has no section bounds; `mssb_bracket_modules` in
  `port/CMakeLists.txt`, `port/src/modules.c`).

## Layout

- `port/CMakeLists.txt`, `port/sources.cmake`: the PC build. The sources are
  the decomp's own `src/main`, `src/game`, `src/menus`, `src/challenge`,
  `src/C3` and `src/Unknown`, compiled with `TARGET_PC`, `NONMATCHING=1` (so
  equivalent functions are built) and `VERSION=0`. Not compiled:
  `src/Dolphin` (SDK, MSL, runtime: aurora and the host libc replace them),
  `src/Musyx`, `src/executor.c` (REL prolog).
- `port/include/port/prelude.h`: force-included into every game file. Pulls in
  the host libc and aurora's whole SDK, defines the Metrowerks/PowerPC
  intrinsics, MSL's `rand`, `PTR_TO_U32`/`U32_TO_PTR` and `PTR32`.
- `port/include/port/sdk_compat.h`: decomp-only SDK names (`Mtx43`,
  `GXTevClampMode`, ...), the decomp's argument order for `PSVECScale`, the
  3-argument `GXSetArray`, 4x4 matrix helpers.
- `port/include/math.h`, `port/include/Dolphin/gd.h`: shadow headers (the
  decomp's `"math.h"` is its own `include/stl/math.h`; GD is the game's own).
- `port/src/`: PC-only code (entry point stub, MSL bits, 4x4 matrices).
- `port/extern/aurora`: aurora, `bigmah/aurora` branch `mssb-port`: the
  `strikers-port` branch plus strikers' Emscripten/WebGPU commit (3fbe54a),
  then MSSB's fixes (texcoord SU scale, texcoords without a texgen, GCI banner
  TLUT offset, viewport depth clamp). Change aurora there, push, and commit
  the new submodule revision here.

## Rules for game sources

- PC-only code goes under `#ifdef TARGET_PC`, keeping the original in `#else`
  when it is more than a line. Prefer portable C that compiles the same under
  MWCC (no `#ifdef` needed). The matching build must stay byte-identical:
  after touching `src/` or `include/`, run
  `find src -name '*.c' -exec touch {} +; ninja`,
  `./build/tools/dtk shasum -c config/GYQE01/build.sha1` (4 OK) and
  `python3 tools/nmcheck.py --all`.
- The decomp's SDK headers (`include/Dolphin`, `include/stl`, MSL) forward to
  aurora/the host libc under `TARGET_PC`. On macOS's case-insensitive
  filesystem `"Dolphin/gx.h"` can also resolve straight to aurora's
  `dolphin/gx.h`, which is why the prelude includes the whole SDK first.
- `s32`/`u32` are 32-bit (`int`) on PC; never write `long`.
- Pointers never live in `u32`. Use pointer types, `uintptr_t`/`intptr_t`
  (typedef'd for MWCC in `include/types.h`) for address math, and
  `PTR_TO_U32()`/`U32_TO_PTR()` only where a 32-bit field must keep its disc
  layout (in-place relocated files). Mark open problems `TODO(port)`.
