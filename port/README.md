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

Configuring applies `port/patches/aurora/*.patch` to the submodule once (see
below).

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
(user.ini skip-front-end), `&nomovies` (`MSSB_SKIP_MOVIES`), `&stats` (fps and
audio queue in the console), `&env=KEY=VALUE;KEY=VALUE` (environment, e.g.
`MSSB_INPUT=500:A,800:A`).

Headless check with screenshots (puppeteer-core: `cd port/tools && npm install`):

```sh
node port/tools/web_drive.mjs --secs 60 --shots 20,40,60 --query 'nomovies&stats' --out build/web-shots
```

A whole exhibition through the front-end menus (3 innings, ~14 minutes):
`port/tools/web_full_game.sh 8080` (`build/web-game/console.log`, with
`MSSB_TRACE_GAME` output).

How it differs from the native build:
- The game's OS threads are Emscripten fibers (Asyncify), scheduled
  cooperatively like the native run token (`port/web/src/os_threads_web.inc`,
  included by `port/src/os.cpp`); DVD completions and DSP/AI work are queued
  "interrupts" delivered when the game enables interrupts or waits.
- wasm traps on indirect calls whose signature doesn't match the callee; the
  decomp does that a lot (task and draw callbacks), so the build uses
  `-sEMULATE_FUNCTION_POINTER_CASTS` (and links at -O1: binaryen's emulation
  fails at -O2/-O3 on this module).
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
- `port/extern/aurora`: aurora, `bigmah/aurora` branch `strikers-port`
  (4acfc6a). `port/patches/aurora/0001-*.patch` is strikers' local commit
  3fbe54a (GX fixes and the Emscripten/WebGPU support), which isn't pushed;
  with it the tree is identical to what strikers builds with.

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
