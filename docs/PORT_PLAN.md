# MSSB PC/browser port: plan

Goal: Mario Superstar Baseball running natively on macOS (arm64) and in the
browser (WebAssembly + WebGPU), built on [aurora](https://github.com/encounter/aurora),
the same way `~/dev/strikers` ports Super Mario Strikers. Read
`~/dev/strikers/PORTING.md` and `~/dev/strikers/docs/STATUS.md` first: almost
every problem below was already solved there.

## Layout (differs from strikers on purpose)

The port lives **inside this repo** instead of vendoring the decomp:

- `port/CMakeLists.txt`: the PC build. It compiles the decomp's own `src/`
  and `include/` (game code from main.dol + game.rel + menus.rel +
  challenge.rel) with `TARGET_PC` defined. The matching build (ninja/MWCC)
  is unaffected because it never defines `TARGET_PC`.
- `port/include/port/`: prelude (force-included), endian helpers, `Ptr32`,
  game heap, SDK shims (copied/adapted from strikers).
- `port/src/`: PC-only code (main loop, OS/VI emulation, heap, input, crash
  handler, REL table, audio glue).
- `port/extern/aurora`: aurora submodule (bigmah fork, `strikers-port` branch,
  as strikers uses).
- PC fixes in game sources go under `#ifdef TARGET_PC` (keep the original in
  `#else` when it's more than a line). The matching build must stay
  byte-identical: run `ninja` + `dtk shasum -c config/GYQE01/build.sha1`
  after touching `src/` or `include/`.

## What we compile

- Game code: all of `src/main/` (main.dol game code), `src/game/`,
  `src/menus/`, `src/challenge/`, with `-DNONMATCHING=1` so equivalent
  functions are built.
- Not compiled: `src/Dolphin/**` (SDK, MSL, Runtime, TRK): aurora + host libc
  replace them. `src/Musyx/**`: use strikers' MusyX runtime and
  `port/src/audio` (both MusyX 2.0.3), or compile ours if closer.
  `src/C3/**`, `src/Unknown/**`: check case by case (C3 is game-side
  character/actor code and is needed).
- Data still in `auto_*` units (not yet in C): generate C from the binary
  (`tools/gendata.py`), or load the sections from the original DOL/RELs at
  startup. Pointer-holding data must become real C (64-bit layout).

## Phases

1. **Skeleton and compile**: CMake, aurora, prelude, SDK headers. Every game
   source compiles for macOS arm64 (no link yet). Fix 64-bit issues found by
   `-Wshorten-64-to-32`, `-Wint-to-pointer-cast`, `-Wpointer-to-int-cast`.
2. **Link**: resolve every undefined symbol: SDK calls go to aurora or
   port stubs, auto-unit data is generated as C, REL module
   prolog/epilog/unresolved hooked into a static table (replace
   `OSLink`/REL loading; MSSB loads game/menus/challenge RELs from
   `aaaa.dat`, see `decompress.py`).
3. **Boot**: game heap (4 GB region, `Ptr32`), disc access through aurora DVD,
   byte-swap disc formats at load, first frames rendering, logos and menus.
4. **Play**: a full game, audio (MusyX), saves (memory card), input.
5. **Web**: Emscripten build like strikers' `tools/build_web.sh`.

Status and findings go in `port/STATUS.md` (like strikers' docs/STATUS.md).
