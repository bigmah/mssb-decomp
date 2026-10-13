# PC port status

Plan: `docs/PORT_PLAN.md`. Build and run: `port/README.md`.

## Summary (what works)

- **macOS (arm64):** boots through the logos and intro movie to the title and
  main menu; Exhibition via the menus or `skipfe` (user.ini) into a game;
  a scripted 3-inning exhibition (`port/tools/full_game.sh 3`) plays to "That's
  the game!" and back to the menus without crashing; a scripted Challenge
  match (`port/tools/challenge_game.sh`: new save, walk the map into Bowser
  Jr., play his match, post-game talk and status screen, back on the map)
  runs without a crash; Toy Field, Minigames (Bob-omb Derby) and Practice
  load and run for 2-4 minutes each (`port/tools/mode.sh`). Character models, stadium, HUD and text render
  correctly at screenshot scale (`port/screenshots/`). Audio: MusyX SFX/crowd
  and disc-streamed music (`port/src/audio/dtk.cpp`). Keyboard (strikers'
  mapping) and SDL gamepads; memory card saves create/load.
- **Web (Emscripten, Asyncify, WebGPU):** `port/tools/build_web.sh`,
  `node port/tools/web_serve.mjs [port]`; at 60 fps with audio running in
  headless Chrome, boots through the front-end menus into an exhibition and
  plays a 3-inning game to "That's the game!" and back to the menus
  (`port/tools/web_full_game.sh`; `port/screenshots/web-*.png`).
- **Matching build:** unchanged (4 OK, 5413 matched, nmcheck clean).

Web build: links at -O3 without function-pointer-cast emulation (10.3 MB
wasm, was 22 MB at -O1 with emulation); callbacks have matching signatures.
Dolphin side by side (`port/tools/dolphin_compare.py menu|game`, see
README): boot, health screen, logos, intro movie, title, card prompts and
main menu match Dolphin to <0.1% of pixels at the same frame. Fixed after
the first comparison (2026-10-13): in-game shadows (aurora stretches the
448-row shadow copy over 480 rows), captain select stat bar colour and CPU
captain position, Peach's model colour (geo swap ran past skinned normals).
Frame pacing (2026-10-13): every web frame drop in a game followed GPU
pipeline compiles (gaps up to 500 ms), and aurora skipped draws whose
pipeline wasn't ready (objects missing for frames, a likely cause of the
rare bright rectangle over the top-left quarter during fielding). Draws now
never wait for a pipeline, and known pipelines (765 bundled, plus the ones a
player's runs record) compile in the background at boot. A headed 10-minute
front end + exhibition: 0 pipeline stalls, two 36-40 ms CPU frames.
Scope: Mario Stadium only; Wario Palace and Peach Garden load on the web,
DK Jungle (aliased bss, lbl_3_bss_B55C) and the 64-bit stadium object views
don't. Known issues: the scripted Challenge
match is Bowser Jr.'s (he walks into Mario), not yet a rival team's full
game; there's no separate post-game stats screen in the
scripted run (A goes straight back to team select); gamepads untested with
real hardware. Hand-written struct views that hard-code 64-bit pointer sizes
must use `PORT_LP64` (wasm32 keeps the GameCube layout).

## Phase 1: skeleton and compile (done)

- `port/CMakeLists.txt` configures aurora (`bigmah/aurora` mssb-port: strikers'
  revision plus MSSB's GX/card fixes) and
  builds `mssb_game`, an object library of all 343 game sources: `src/main`
  (81 incl. `common/`), `src/game` (186), `src/menus` (53),
  `src/challenge` (20), `src/C3` (1), `src/Unknown` (2).
- **Every game source compiles** with Apple clang for macOS arm64, with
  `-Wshorten-64-to-32 -Wint-to-pointer-cast -Wpointer-to-int-cast
  -Wincompatible-function-pointer-types -Wimplicit-function-declaration
  -Wint-conversion` as errors (`MSSB_WERROR_64`, on by default) and zero
  warnings left in those groups.
- The matching build is unchanged: 4 OK and the same 5413 matched functions.

Compile errors (failing files / errors), first build vs now:

| module    | files | first build (failed files / errors) | now   |
|-----------|-------|-------------------------------------|-------|
| main      | 81    | 77 / 1775                           | 0 / 0 |
| game      | 186   | 186 / 4204                          | 0 / 0 |
| menus     | 53    | 53 / 790                            | 0 / 0 |
| challenge | 20    | 20 / 527                            | 0 / 0 |
| C3        | 1     | 1 / 25                              | 0 / 0 |
| Unknown   | 2     | 2 / 26                              | 0 / 0 |

(First build: the skeleton with the decomp's own SDK/libc headers, 339 of
343 files failing, 7347 errors, most of them repeats from shared headers.)
64-bit warnings: 351 unique sites
(152 pointer-to-int casts, 107 int-to-pointer casts, 66 shortenings,
6 function-pointer mismatches) plus 36 implicit declarations, all fixed
(src/main: 155 + ~150 sites, game/menus/challenge: ~50).

### How the SDK is wired

- `include/types.h` takes `s32`/`u32`/... from aurora's `dolphin/types.h`
  (32-bit `int`), keeps `bool` a byte, and adds `PTR_TO_U32`/`U32_TO_PTR` and
  (for MWCC) `intptr_t`/`uintptr_t`.
- `include/Dolphin/**`, `include/stl/*`, the MSL headers: under `TARGET_PC`
  they include aurora's SDK or the host libc. The prelude includes the whole
  aurora SDK plus `port/include/port/sdk_compat.h`.
- GD: the game's own GD library (`src/main/file_800A1A70.c`) is used;
  aurora's GD headers are C++-only. aurora also builds a GD library, so Phase
  2 must pick one at link time.
- `rand`/`srand` are MSL's LCG (`port/src/msl.c`), so `RAND_MAX`-based game
  math (32768) is unchanged.

### Fix patterns used

- SDK prototypes declared locally with MWCC types (`memcpy(void*, const
  void*, u32)`) now use `size_t`/`int` (same type under MWCC).
- Prototype-scope structs (`void f(struct MenuTask*)` with no prior
  declaration) got forward declarations.
- The decomp writes float arguments wherever (PowerPC passes them in FPRs):
  `PSVECScale(src, scale, dst)` and `PSQUATScale` are remapped in
  `sdk_compat.h`. Watch for more of these.
- In-place relocation of disc files (`*p += (u32)base`, `(void*)hdr->ofs`)
  uses `PTR_TO_U32`/`U32_TO_PTR`: identical casts under MWCC, game-heap
  offsets on PC.
- Pointer arithmetic and int-carrying `void*` arguments go through
  `uintptr_t`/`intptr_t`; pointer differences are cast explicitly.
- Runtime-only fields that held pointers in `u32` became pointer types.

- The draw list (`DrawLink`, file_800A7C08.h) is a pointer-sized tagged
  pointer on PC (flags in bits 0-1); every node struct's `link` word is
  `uintptr_t`.
- Matching caveat: keep the expression shape when swapping `u32` for
  `uintptr_t` (`(u8*)field + (uintptr_t)base`); reordering operands changed
  MWCC codegen once (fn_800111B4) while the shasum stayed OK, so also check
  the matched-function count, not only `dtk shasum`.

## Deferred (known problems, not fixed in Phase 1)

Grep `TODO(port)` in `src/` and `include/` for the individual sites.

1. **Disc data layout.** Files are loaded in place and their 32-bit offsets
   relocated with `PTR_TO_U32`. That needs (Phase 3) every game allocation in
   a 4GB game heap (strikers' `port/src/game_heap*.c*`) and a big-endian swap
   pass per format at load time. Several structs type these offset tables as
   pointers (`void** files` in `include/main/file_80011640.h`,
   `lbl_3_common_bss_35154.assets` in `rep_1E08.c`, `actor->files` in
   `menus/rep_0F60.c`): 8 bytes per entry on PC, so they read garbage. They
   need `u32` tables plus `U32_TO_PTR`, or a converted native copy.
   More in-place loaders whose 32-bit offset/pointer fields are typed as
   pointers (compile through `uintptr_t`, wrong layout on PC): `GEO_RELOC`
   (file_800B9974, geometry palettes), `ANIMGet` (file_800B4A44),
   `LoadActorLayout`/`fn_800B49E4` (file_800B2C44), `SKNLoadFile` and
   `convertTextureHeader` (file_800BDEA0), `MsgTable.msgs` (file_8000F150),
   `SoundGroupData` (file_80021308), `TEXPalette` (file_800A7C08).
   `fn_8000B9C8` (file_8000A0AC) and `fn_80025DDC` (file_80024D2C) relocate
   with `PTR_TO_U32` and need the file in the game heap.
2. **Raw-offset views of runtime structs** (GameCube layout): about 90
   `u8 pad[0x..]` view structs (e.g. `sta_c2.c` `D5B6CCtl`), 30
   `*(T*)((u8*)p + 0x..)` reads and 41 `// TODO type` spots. Wherever the
   real struct holds pointers before that offset, the view is wrong on PC.
   Replace them with the real struct.
3. **Literal sizes**: about 230 `memcpy`/`memset` calls with hex sizes.
   Those over structs that contain pointers copy too little on PC; use
   `sizeof`.
4. **`(T**)` reinterpretation of u32 tables**: about 150 `(T**)` casts.
   Each must be checked (see item 1).
5. **`GXSetArray`** takes 3 arguments in the game; aurora needs the array's
   size and endianness. `sdk_compat.h` passes size 0 for now (25 call sites).
6. **`GXTexObj` is 0x40 bytes and `GXTlutObj` 0x28 in aurora** (0x20/0xC on
   GameCube). Game buffers sized for the GameCube objects overflow
   (rep_3520 fixed); disc structs that embed them can't be loaded in place.
7. **GX data**: the game writes GX FIFO data and display lists itself
   (`GXPosition*`-style macros, GD). aurora parses big-endian display lists,
   so GD output is fine; direct FIFO writes need checking.
8. **Functions that fall off the end** relying on r3 (`-fno-strict-return`
   keeps them from trapping): `fn_3_164A8` (rep_720.c) and `fn_2_73B94`
   (menus) look complete; `fn_3_109CE8` was fixed. Sweep more with
   `-Wreturn-type` once linking.
9. **Misnamed SDK symbols**: `symbols.txt` calls 0x80088698 `CARDFastDelete`
   but it is `CARDDelete` (mapped under `TARGET_PC` in file_800A7C08.c).
10. **Out-of-bounds writes into neighbouring statics** that rely on the
    GameCube data layout, e.g. `(&lbl_1_bss_60A0)[lbl_1_bss_5F73]` in
    `challenge/rep_0610.c`. Find more with ASan once it runs.
11. **Case sensitivity**: some sources include `"Dolphin/GX.h"` but the file
    is `gx.h`. Fine on macOS; Linux/web builds need the names fixed.
12. **MusyX**: not compiled. The game's MusyX headers (`include/musyx`) must
    match whichever runtime is linked (strikers' MusyX 2.0.3 port or ours).

## Phase 2: link (done)

`mssb` is a default target and links with 0 undefined symbols (before: 3169).

- **Data** (`port/gen/`, generated by `port/tools/gen_data.py` on top of
  `tools/gendata.py --nonmatching`, checked in): all 2819 data symbols no
  source defines, as typed C with native values; REL relocations became
  symbol references. 2640 scalars/arrays in `port/gen/<module>_data.c`, 179
  typed objects in `port/gen/<module>/<unit>.c`. Rerun after building
  `build/port` (~45 s). Review list: `port/gen/REPORT.md` (52 size
  mismatches, 17 with raw big-endian tails, 2 objects with non-address values
  in pointer fields, 6 sub-objects defined as copies). Open question:
  `lbl_800E8754` is declared as both `SavedSettings` and `GameInitOptions`.
- **OS/SDK** (`port/src`, adapted from strikers): `os.cpp` (OSThreads on host
  threads, one running at a time by priority; queues, semaphores, messages;
  interrupts as one lock; 128MB OS arena in the 4GB-aligned game heap;
  retrace callbacks and frame presentation at 60 Hz while the main thread
  waits), `game_heap` + dlmalloc, `main.cpp` (disc from `MSSB_ISO`, an
  argument, or `mario_baseball.iso` in a parent folder), `crash`, `input`,
  `vi_frame`, `os_address`. Stubs in `sdk_stubs.c`: AI streaming, PPC, SI,
  ARQ flush/remove/chunk, GX draw sync, GX perf counters, scissor offset.
- **REL modules** (`port/src/modules.c`): CMake renames each module's
  `_prolog`/`_epilog`/`_unresolved` (`game_prolog`, ...); a table maps the DLL
  index (0 menus, 1 game, 2 challenge) to prolog/epilog; `fn_800097A0` has a
  `TARGET_PC` branch that uses it instead of `ARAMTransfer` + `OSLink`. The
  game's `main` is compiled as `game_main`.
- **MusyX**: strikers' MusyX 2.0.3 runtime (`port/musyx`) and DSP/AI
  emulation (`port/src/audio`); our `src/Musyx` (MSSB's exact runtime) needs
  a full PC hardware layer. `SND_EMITTER` gained strikers' `userData` field
  under `TARGET_PC`. The sound pool lives in the game heap, 4x bigger
  (`synthInit` ran out otherwise).
- `lbl_803C7420` (video system) has one real struct
  (`include/main/video_system.h`); three units used GameCube-offset views.

### First run

aurora starts (Metal), the disc is found, the memory card image loads, the
game's threads start, frames are presented and `sndInit` succeeds. Then:
SIGSEGV in `fn_800111B4` (inlined in `fn_80010FA0`, called from
`fn_800097A0` <- `game_main`): the in-place relocation of `MsgTable.msgs`
reads 4-byte disc offsets as 8-byte pointers (deferred item 1).

## Phase 3: boot (done)

How far it gets: **the main menu**. Health & safety screen, Nintendo and
Namco logos, the intro movie (HVQM4, video in sync), the title screen (spani
animation) and, after START and the memory card prompts (no save file: "No",
then "start anyway"), the main menu with the "Exhibition Game" panel
(preview picture, text, icons). Reproduce with

    IN="500:A,800:A,1300:START"; f=2200
    for i in 1 2 3 4 5 6; do IN="$IN,$f:RIGHT,$((f+60)):A,$((f+120)):LEFT,$((f+180)):A"; f=$((f+240)); done
    MSSB_SKIP_MOVIES=1 MSSB_INPUT="$IN" port/tools/run.sh 75 5

Blockers / known problems:
- Main menu: the left-hand mode list and the menu background are missing
  (probably 3D layouts/actor models, not spani).
- Text glyphs are cyan/pink instead of white (font palette/colour).
- More task-struct views pad the header pointers as bytes (rep_16B8,
  rep_1770, rep_2BF8, auto_00_0015C5F4, auto_00_00097144, auto_00_0011D3AC,
  rep_7730, rep_7BF0): they will break when those screens run.
- Untested: ARAM-cached menu/challenge movies, movie audio by ear, all 3D
  model formats (no model drawn yet), stadium and challenge containers.
- `lbl_2_data_2AADC` has 12 raw big-endian tail bytes (port/gen).
- aurora patch 0002 applies the texcoord SU scale registers (glyph UVs).

### Tooling

- `port/tools/run.sh [secs] [shot-every]`: runs `build/port/mssb`, kills it
  after N seconds, log in `build/port/run.log`, window screenshots in
  `build/port/shots/tNN.png` (`port/tools/winid.swift` + `screencapture`).
- Crash handler with backtrace, hang watchdog (`MSSB_WATCHDOG_SECS`).
- `MSSB_INPUT="frame:BUTTON,..."` scripted pad presses (60 frames/s),
  `MSSB_DEBUG_INPUT=1`; `MSSB_TRACE_TASKS=1` prints the scene task list
  whenever it changes.
- `port/tools/assetfile.py` extracts/decompresses an asset from the disc's
  archive; `port/tools/viewcheck.py` finds struct views of one global that
  disagree on PC; `port/tools/gen_data.py` regenerates port/gen.

### Memory model

Pointer fields of data loaded in place are `PTR32(T)` (plain `T*` under
MWCC): a u32 offset from the 4GB-aligned game heap base; values from
0xE0000000 index a table of pointers outside the heap (static data). They're
read and written with `PTR32_GET`/`PTR32_SET`. A file's scalars are swapped
exactly once at load (`port/src/formats*.c`, sizes from `port/src/blob.c`,
noted by `ARAMTransfer`), then the game's own relocation runs. Texture data,
TLUTs and display lists stay big-endian. Global structs that many units read
through GameCube-offset views can also keep their layout with PTR32 fields
(done for `SceneFade lbl_8037169C`).

### Formats

| format | where | state |
|---|---|---|
| message tables (MsgTable) | file_8000F150 fn_800111B4 | swapped + PTR32, works |
| font archive (4 offsets) | file_8000F150 fn_80011000 | swapped, works |
| texture archives (TexArchive/TexImage), DOTexInfo, challenge texture headers | file_800BDEA0 convertTextureHeader | swapped once (marker) + PTR32, works for logos |
| TPL (TEXPalette, charPipeline) | file_800A7C08, file_80091450 | swapped + PTR32 (memory card banner/icons) |
| spani 2D animation (SpaniAnim, tracks, blocks, keys), spani file headers, SpaniDesc tables | file_8000A0AC fn_8000B9C8, file_80034F50 | swapped + PTR32, title and menus animate |
| sprite elements (bitfields), RGBA colors | file_8000BA3C | PC bitfield order |
| 2-offset resource files (RelocPair/ResHandle) | file_80069BDC | swapped + PTR32 |
| menu song blocks, song tables, archives, model-set containers | menus, m_sound | offset tables swapped |
| MusyX sound groups (SoundGroupData + proj/sdir/pool) | file_80021308 | swapped + PTR32, sndPushGroup works |
| geometry palettes (+ vertex arrays native, le=true) | file_800B9974 | swapped + PTR32, untested |
| actor layouts / bones | file_800B2C44 | swapped + PTR32, untested |
| animation banks | file_800B4A44, file_800B516C | swapped per track type, untested |
| skins | file_800BDEA0 | swapped, untested |
| character file tables | file_80011640, menus rep_0F60/rep_0568 | PTR32 tables, untested |
| shape (morph) data, shape anim sets | file_80024D2C | swapped, untested |
| file load records in .data (u8[] objects) | port/src/data_fixups.c | swapped at startup |
| HVQM4 movies (headers swapped, YUV->BE texels) | file_800ADC40, file_800DFDD4 | intro plays; `MSSB_SKIP_MOVIES=1` skips |
| stadium archives / sta_c* file tables, rep_1E08 assets, rep_3E00, auto_00_0011D3AC | game | not done |
| challenge models (rep_0000, rep_0610, rep_74A0) | challenge | map, walkers and Bowser Jr. match render; not audited |

### Fixes outside the formats (classes to watch for)

- Struct views with GameCube offsets over objects that hold pointers: tasks
  (`MainTask`, `RepTask`), `LayoutObj`, `SceneFade`, `MovPlayer`/`ThpPlayer`
  (now one definition), `VideoSystem`, sprite work areas, CharSelectState,
  SoundManager... (`viewcheck.py` lists the rest).
- Raw byte offsets into structs (`lbl_803C6CF8[0x715]` -> `.idle`).
- Tentative definitions without a size (`u8 buf[];`) are one-element arrays
  in clang: the 0x45000-byte sprite buffer overflowed into globals.
- Display lists built by hand (sprite system) must be written big-endian;
  GD also emits aurora's texture bind commands (reserve room for them).
- Draw callbacks receive their node in r3 on GameCube.
- Busy-wait loops need `OSYieldThread()` on PC (single run token, no
  preemption from interrupts).
- MusyX sample addresses are 32-bit heap offsets (hwSaveSample).
- `lbl_800E8754` is `SavedSettings` (port[4] at 0x07); `GameInitOptions` was
  wrong (fork D, from the rep_1188 asm).

## Phase 4: full game and modes (fork M)

Scripts (each run gets its own binary copy, log and fresh user folder with
`MSSB_RUN_TAG`, so several can run at once):

- `port/tools/full_game.sh [innings] [secs] [shot-every]`: skipfe straight
  into Mario vs Bowser at Mario Stadium (`innings = N` in user.ini sets the
  game length), A every 1.5 s. A 3-inning game runs to "That's the game!" and
  the end scene in ~520 s, returns to the menus (team select) and the A
  presses start the next game, which also plays: no crash in 640 s
  (`screenshots/game-end.png`, `game-result.png`, `after-game-teams.png`).
- `port/tools/web_full_game.sh [port] [secs] [shots]`: the web build in
  headless Chrome, through the front-end menus (no skipfe) into an
  exhibition (Mario vs CPU Luigi, default 3 innings), A every 1.5 s. The
  game went to extra innings and ended 1-0 in the 5th: "That's the game!" at
  ~820 s, the result scene, back to the menus (module reset logged), and the
  next game starts (`screenshots/web-game-end.png`, `web-game-result.png`,
  `web-after-game.png`).
- `port/tools/mode.sh challenge|toyfield|minigames|practice [secs] [shot]`:
  boot to the main menu, enter the mode, press A (`MSSB_MODE_INPUT` adds
  more). Each runs 150-240 s without a crash: Challenge walks the map,
  Toy Field plays turns, Minigames (Bob-omb Derby) plays, Practice runs its
  lessons and returns to the practice menu (`screenshots/mode-*.png`).
- `MSSB_TRACE_GAME=1` also traces loader steps (`port_trace_value`).
- `port/tools/challenge_game.sh [secs] [shot]`: fresh card, main menu ->
  Challenge -> Mario -> intro talk -> map; d-pad up/left/left/left walks
  into Bowser Jr., who challenges Mario; A through his match and the
  post-game talk, B/A out of the status screen back to the roaming map
  (~430 s, no crash; `screenshots/challenge-game.png`).
  `MSSB_TRACE_MAP=1` prints the map walkers' nodes (`MenuCtx.entries`);
  the d-pad picks the direction column of the node table
  (`lbl_2_data_3D30`: up, down, left, right). `MSSB_HANG_SAMPLE=<file>`
  writes every thread's stack (macOS `sample`) on a watchdog hang.

Fixes (classes to watch for):

- The challenge save (`MenuCtx`, 0x4508 bytes) is copied to and from the
  card image as is: its pointers are PTR32 (`MenuRosterEntry.limits` =
  `ChallengeTrackingStruct.scoutFlagPointer`, the MenuEntry/MenuObject
  `update` callbacks). An 8-byte `scoutFlagPointer` moved
  `gChallengeState.teams` and the match loaded garbage characters.
  PTR32 values for static data/functions are image-relative, so they stay
  valid across runs (`port/src/port_runtime.c`).
- Thread deadlock (watchdog hang at boot or entering Challenge, ~1 in 3
  runs, more with parallel runs): a thread holding the interrupt lock waited
  for the run token in `maybe_preempt`/`OSSuspendThread` while the main
  thread, presenting a frame, waited for the interrupt lock. No preemption
  with interrupts disabled; the token is taken before the interrupt lock
  (`port/src/os.cpp`).
- REL modules get fresh .data/.bss at every load (`port/src/modules.c`,
  `port/include/port/module_sections.h`). The web build has no section
  bounds: wasm-ld keeps input order, so CMake brackets each module's sources
  and its `port/gen` data with generated marker objects
  (`mssb_bracket_modules`) and the reset covers the ranges between them.
- Data swapped in place "once per address" breaks when the next load lands
  at the same address: the camera animation list (`fn_3_FC448`) stayed
  big-endian in the second web game (out-of-bounds trap) until
  `fn_3_106E50` reset the guard at each load
  (`port_forget_camera_anim_list`).
- Views of `lbl_8036E548` (CharMgr), `lbl_2_bss_1A8250` (MenuData),
  `lbl_80366B18` (TextSystem), `lbl_3_common_bss_350E4`, `lbl_800EF808`
  regenerated with `pcview.py` (now scales offsets inside pointer arrays).
- Scene-task views whose own area starts at 0x14 need `_u14align` /
  `SCENE_TASK_VIEW_LINKS` (`taskviewcheck.py` misses `void* fn; u8 pad[0x10]`
  style views and macros like `REP_TASK`).
- `u8 lbl_x[]` globals indexed by GameCube offsets (`lbl_80366158[0x28]`,
  `lbl_8036E548[0x307D]`) go through accessors in `port/game/views.c`.
- Stadium object types share one PC size (0x128); collision tables keep
  32-bit group pointers (`PTR32_GET`).
- Offset tables swapped: menus animation archive (73 entries), minigame
  results file (90), trail model header.
- Data that the game writes past its symbol: `lbl_8023DD80` (0x96000),
  `lbl_2_bss_3401C0` (MenuAnimArchive, 0xB8 on PC); `gen_data.py`
  `PC_MIN_SIZE`.

Known issues: the exhibition script exercises the CPU-vs-human flow only
with A; the Challenge script plays Bowser Jr.'s match, not a full game
against a rival team.

## Next

Disc formats: swap and relocate (or convert) each in-place format, starting
with `MsgTable`, then the deferred list above.
