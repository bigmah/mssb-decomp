# Plan: matching the rest of Mario Superstar Baseball

## End goal: a PC and browser port, like `../strikers`

The goal is not the matching build itself. It's a native macOS build and a browser build (WebAssembly + WebGPU) on [aurora](https://github.com/encounter/aurora), set up the way `~/dev/strikers` is for Super Mario Strikers. Read `strikers/PORTING.md` and `strikers/docs/STATUS.md` for the details. The matching build stays as the proof that the C is right.

**How strikers did it.** It vendored the finished smstrikers-decomp sources into `decomp/` (revision pinned in `.decomp_rev`). It added aurora as a submodule and a small `port/` layer, about 1,800 lines: OS/VI stubs, a game heap, input, crash handler, and MusyX audio through an AX DSP HLE. Then it fixed the game sources under `#ifdef TARGET_PC`, about 330 sites in 150 files. From vendoring to a full match running on macOS took **one day** (2026-10-02). The browser build, trimmed game and online play took three more. It was that fast only because the decomp already had **every function as C with real types**.

### What MSSB needs before a port can start

1. **Every function as C, not necessarily matching.** Today about 2,400 functions are stubs or asm. A function that is functionally equivalent but non-matching is enough for the port. Keep it under `#ifdef NONMATCHING` (or similar) so the matching build stays green. When a register-allocation fight runs past its budget, commit the equivalent C rather than nothing.
2. **The `main.dol` game code split into source files** (Phase 4). Those ~900 functions in `auto_*` units have no `.c` file at all.
3. **Real types instead of raw offsets.** Matching code here often reads `*(u16*)(p + 0x14)` and stores pointers in `u32`. On 64-bit that's wrong whenever `p` is a runtime struct that contains pointers, so the offsets would be off. Use named structs and fields (Phase 2). Code written this way needs no rework for the port, and it matches just as well.
4. **Data in source.** Data is at 0.35%. Tables that are pure numbers can be generated from the binaries by a script (u8/u16/u32/f32 arrays emitted as numeric C literals, so endianness takes care of itself). Tables that hold pointers (function tables, string pointers, struct-of-pointer arrays) need hand-written C.

### Port work (can start before the decomp is done)

Mirror strikers' structure: a separate repo (or `port/` directory) that vendors `src/` and `include/` at a pinned revision, with `extern/aurora`, CMake and `TARGET_PC`.

| Step | Strikers equivalent | MSSB specifics |
|---|---|---|
| CMake + aurora + `port/include/port/prelude.h` | first commits | Copy strikers' `CMakeLists.txt`, `port/src/*` and the aurora patches as a starting point. |
| Compile everything for 64-bit macOS | "Get all sources compiling" | `long` → `int`, pointers-in-ints → `uintptr_t`, replace asm/paired-single/hardware access under `#ifdef TARGET_PC`. |
| Link the RELs statically | — (strikers had none) | `game.rel`, `menus.rel` and `challenge.rel` become normal objects linked into the app. Replace `OSLink`/REL loading with a table of their prolog/epilog entry points. |
| Game heap + `PTR32` | "Game heap arena, Ptr32" | Reuse strikers' dlmalloc 4 GB arena and `Ptr32<T>` for disc structs loaded in place. |
| Disc formats: byte-swap at load | "Disc formats …" | Find MSSB's file loaders. Swap scalars once at load; texture data and display lists stay big-endian. |
| Audio | "MusyX on its GC target with AX DSP HLE" | MSSB's headers say MusyX 2.0.3, the same version strikers uses. Confirm it, then reuse strikers' MusyX runtime and `port/src/audio`, which saves a lot of work. |
| Boot → menus → a game | STATUS.md | Use strikers' `tools/run.sh`, crash handler and hang watchdog to iterate. |
| Browser build | `tools/build_web.sh` | Same Emscripten + JSPI/Asyncify setup. wasm signature checks will catch mismatched function prototypes. |

**Start the port early, with what exists.** Getting the existing sources to *compile* for 64-bit (not run) can begin now. It shows which decomp conventions break portability while they're still cheap to change, and those rules then go into `AGENTS.md` so new code is written portable from the start. The port can't boot until items 1–4 above are done for at least the boot path (main.dol + `menus.rel`).

### What this changes in the matching plan

- **Priority order:** split `main.dol` game code (Phase 4) → shared types (Phase 2) → every function at least equivalent → data → full matching. Finishing the libraries (Phase 6) matters less, because aurora replaces the SDK. MusyX can come from strikers.
- **"Done" for a function becomes two levels:** *equivalent*, which is enough for the port, and *matching*, which proves it. Agents should never leave a function as a stub or asm just because it won't match.
- **Linking units (`Matching` in `configure.py`) still matters** because it proves data and code are complete. But it's no longer the headline metric. The headline is "functions with C (any level)", and `next_targets.py` should report it.

## Where we are (2026-10-10)

| Module | Code | Matched (functions) | Unmatched functions by size (≤64B / ≤256B / ≤1KB / >1KB) | At ≥95% |
|---|---|---|---|---|
| `main.dol` SDK, MSL, Runtime, TRK | 230 KB | ~99.5% | 4 / 2 / 4 / 0 | 1 |
| `main.dol` MusyX | 128 KB | — | 0 / 0 / 2 / 5 | 3 |
| `main.dol` game code (unsplit `auto_*`) | 549 KB | — | 133 / 296 / 331 / 153 | 0 |
| `game.rel` | 1.5 MB | 28.4% (1455 / 2406) | 37 / 83 / 429 / 402 | 75 |
| `menus.rel` | 618 KB | 33.7% (831 / 1233) | 9 / 45 / 226 / 122 | 3 |
| `challenge.rel` | 171 KB | 26.0% (198 / 349) | 14 / 22 / 68 / 47 | 6 |

Overall: **32.0% of code matched (4045 / 6479 functions), 7.9% linked (178 / 1334 files, all in `main.dol`), data 0.35%.** No REL file is linked yet.

The easy tail is gone: about 730 functions over 1 KB hold **two-thirds of the remaining code (1.46 MB of 2.18 MB)**. The small ones that remain are mostly the `main.dol` `auto_*` units, which still need splitting into source files (Phase 4).

Most of `src/game/*.c` already exists, but almost all of it is **stubs** (`void fn_3_XXXX(void) { return; }`) with the address and size in a comment. So the file layout is done; the bodies are not. About 640 `game.rel` functions are not in any source file yet (`game/auto_*` units).

The libraries are almost finished, so **nearly all remaining work is MSSB's own game code (~2.8 MB)**, written by Namco in C and built with `GC/2.6 -O4,p -inline deferred`.

## What "progress" means here

- **Matched** (decomp.dev "matched" %): a function compiles to the same bytes as the original.
- **Linked**: an object is marked `Matching` in `configure.py` and goes into the real build. A file can only be linked when **every** function and data item in it matches.

Matched % is what moves the badges. Linked files are what really proves the decomp. So **finish files, not just functions**: once a file is down to one or two stragglers, prioritize those stragglers.

## Workflow for one function

1. **Pick a target** (see Phases). Start from small leaf functions, which don't call other unmatched code.
2. **Get a first draft in C:** `python3 tools/fnstart.py <fn>` prints the original asm, an m2c draft using the unit's headers as context, and the current diff. For decomp.me, generate a context with `python3 tools/decompctx.py src/game/rep_XXXX.c -I include -I include/stl`. The compiler preset is `mwcc_247_107`, and `objdiff.json` lists the exact flags for each unit.
3. **Iterate locally:**
   - `python3 tools/fndiff.py <fn>` rebuilds just that unit and prints an instruction diff, or `MATCH`.
   - `python3 tools/fnvariants.py <fn> v1.c v2.c ... --also caller1,caller2` scores several candidate definitions at once (including callers that inline it) and restores the file afterwards.
   - Or use the objdiff GUI pointed at the repo root, which rebuilds automatically on save.
4. **Check that nothing regressed.** Run a full `ninja`, then confirm the `game:` function count went up, and that `config/GYQE01/build.sha1` still reports `4 files OK`.
5. **Commit one function per commit**, with the message `match <function_name>`.

### Matching patterns we've already hit

The patterns live in `docs/patterns/`, one line each. **Don't read them all.** When a diff shows a symptom, grep for it:

```sh
grep -i 'dont_inline' docs/patterns/*.md      # or: fcmpu, extsb, lwzx, unroll, r27, switch ...
```

| File | Covers | Entries |
|---|---|---|
| `docs/patterns/unsolved.md` | Near-misses that are still unmatched, and what was tried | 55 |
| `docs/patterns/inlining.md` | Inlined callees, `#pragma dont_inline`, stubs inlined into callers, header inlines | 90 |
| `docs/patterns/floats.md` | Float/double constants, f-register order, int<->float conversion, sqrt, fabs, compares | 76 |
| `docs/patterns/loops.md` | Loop shapes, unrolling, induction variables, strength reduction, search loops | 52 |
| `docs/patterns/regalloc.md` | Register numbering, declaration order of locals, statement order, coalescing | 96 |
| `docs/patterns/control-flow.md` | if/else vs switch, early returns, bool/int returns, compare and branch shapes | 31 |
| `docs/patterns/calls.md` | Call arguments, prototypes, sign/zero extension, tail calls, varargs | 20 |
| `docs/patterns/globals.md` | Globals, arrays, struct fields, pointer arithmetic, sda/lis addressing, typed externs | 7 |
| `docs/patterns/misc.md` | Everything else | 12 |

Add a new pattern as one line to the closest file: `- **Symptom (fn_name):** fix.` Keep it short.

## Token efficiency (agent cost)

Most of the remaining work is large functions, and agent tokens are now the main cost. Each item below is a fix that pays off on every later function. Do them roughly in this order.

1. **Compact tool output (done 2026-10-10).** `fndiff` prints a summary line, a diagnosis (stub / registers only / scheduling / which opcodes differ), a target->ours register map, and at most 5 structural hunks. Register-only hunks are folded into the map once a diff has more than 5 hunks. `--full` and `--hunks N` show more. `fnstart` prints an asm summary (calls, globals, float use) instead of the listing (`--asm` for all of it), and a 3-hunk diff. On a 1 KB function at 83%, `fndiff` went from 288 lines to about 100, and `fnstart` from 15 KB to 6.6 KB.
2. **Shrink this file (done 2026-10-10).** The ~440 pattern bullets moved to `docs/patterns/<topic>.md`, and `plan.md` went from 212 KB to 19 KB. Agents grep the pattern files for a symptom and never read them whole.
3. **Route work by difficulty.** Run functions ≤256 B, and most ≤1 KB ones, on a cheaper model with a hard budget (e.g. 25 tool calls) before giving up. Keep the strongest model for >1 KB functions and for functions a cheaper agent left unmatched. Record the stopping point as a `// NN%: <why>` comment so the next attempt doesn't start over.
4. **Near-misses go to the permuter, not agents.** For ≥95% functions whose diff is only register allocation or instruction order (88 at ≥95% right now), run decomp-permuter (CPU time, not tokens). Agents only look at them again if the permuter fails and the diff shows real structure differences.
5. **Types first (Phase 2) before the >1 KB functions.** Large functions are mostly expensive because of unknown struct fields. One agent mapping a module's core structs is cheaper than every agent rediscovering offsets.
6. **Less overhead per function:**
   - Full `ninja` once per batch or unit, not after every function; always pipe it to `tail -20`. Between full builds, `fnvariants --also <callers>` catches inline breakage.
   - New worktrees must start from `main` (`tools/setup.py` or the worktree recipe should do it); old bases cost agents turns on `git reset`.
   - Keep one agent on one unit for a long session (warm prompt cache) instead of a fresh agent per function.
7. **Script the mechanical parts.** Data is at 0.35% and no REL file is linked. Rodata/data splits, `.data` declarations, and flipping fully matched units to `Matching` (with a sha1 check) should be a Python tool, not agent work.

## Phases

### Phase 0: Tooling (done)
- [x] Local build working on macOS arm64 (wibo, no Wine).
- [x] `tools/setup.py`: one-command bootstrap for a clone or worktree (tools, orig files, m2c, build).
- [x] `tools/fnstart.py`: asm + m2c draft (with header context) + current diff for any function.
- [x] `tools/fndiff.py`, `tools/fnvariants.py`: per-function diff and variant scoring.
- [x] `tools/next_targets.py`: ranks functions/units to work on next.
- [x] `tools/claim.py`: unit claims shared across worktrees, for parallel agents.
- [x] `AGENTS.md`: agent workflow and definition of done.
- [ ] Optional: objdiff GUI for humans doing visual diffing.

### Phase 1: First linked game file
Goal: the first `game/*.c` objects switched to `Matching`.

1. `rep_1838.c` is 26 / 27. Only `fn_3_9F79C` is left (99.2%; float register allocation around the inlined `dolsqrtf2`). After that, check the file's data/rodata also match, then flip it to `Matching`.
2. Clear the other 95–99% functions: `game_batter.c` (`calculateBallHorizontalAngleHit`, `calculateBuntHorizontalAngle`, `batterInBoxMovement`) and `rep_720.c` (`fn_3_1C1B0`, `fn_3_197E8`).
3. Learn from flipping a file to `Matching`: which data or rodata issues block linking, and whether more `splits.txt` work is needed. Write it down here.

### Phase 2: Shared types (the multiplier)
Every function gets easier once the big structs are right. Before mass decompiling:

- Build out the core structs in `include/` (`g_Ball`, `g_d_GameSettings`, batter/pitcher/fielder/runner state, `g_Practice`, team/roster data). Use field offsets from matched functions plus asm accesses.
- **Borrow knowledge from the MSSB modding community.** Project Rio (MSSB netplay and stats) and similar groups document many RAM addresses and struct fields. Translate those into names in `symbols.txt` and struct fields. REL addresses are relocated, so use the `mapped:` addresses in the stub comments (and `tools/cvt_rel_addr_to_mapped_addr.py`) to line them up with Dolphin RAM addresses.
- Name functions as their purpose becomes clear, even before they match. Names spread to every caller.
- Check the demo builds (`US_DEMO`, `JP_DEMO`) for strings, asserts or symbols that leaked names.

### Phase 3: `game.rel` file by file
- Work on **one file at a time** so files reach "linked". Within a file, do the leaf functions first, then the functions that call them.
- Order files by size and depth: the smallest stub files first (many `rep_*.c` have only a handful of functions), and the 1K+ functions last.
- Turn `game/auto_*` units into real source files as we reach them. `docs/splits.md` covers adding a split. Look at the `rep_*` naming in `config/GYQE01/game/splits.txt` for how existing files were cut.
- Rough size: about 2,250 functions. ~830 are 256 bytes or less, and these should go quickly once the types are good.

### Phase 4: Game code in `main.dol`
- **Split done (2026-10-10).** The 1,035 unsplit `.text` functions now live in 41 files, `src/main/file_<ADDR>.c` with headers in `include/main/`. Each file is a `.text`-only entry in `config/GYQE01/splits.txt`. The 57 old `src/Unknown/auto_*_text.c` sources were merged into them, and all 129 already-matched functions still match.
- **How the boundaries were found.** The linker keeps file order in every section, and MWCC pools each float/double/string constant once per file. So:
  1. A cut is only allowed where every `.sdata2`/`.rodata` address referenced before it is below every one referenced after it.
  2. A cut is required between two functions that load the same constant value from different addresses.

  167 required intervals were all satisfiable, giving 36 boundaries, plus 5 breaks where library code sits in between.
- **The files are a lower bound.** A file can still hold several real source files where nothing forced a cut (for example `file_80011640.c`, 97 functions, 59 KB). That's harmless for matching, because merged files share no constant values. Split them further when matched code shows a boundary, such as a `static` helper used on only one side, `.data`/`.bss` order, or a change in coding style. Where a cut falls inside its allowed window is a guess (the latest allowed function).
- Several files are SDK sample/library code, not game code: the character pipeline (`ACT*`, `ANIM*`, `SKN*`, `LIT*`, `DS*`, `TEX*`) and the THP player (`MovDecodeThread`, `YUV2RGB`). They may need other compiler flags, so check against known decomps of those libraries before matching by hand.
- Data (`.data`, `.bss`, `.sdata`, `.sbss`, `.rodata`, `.sdata2`) is still in `auto_*` units. Assign it to the files when they get close to linking.
- Unmatched functions are `void f(void) { return; }` stubs. One function declared in a shared header (`fn_80062890`) is a comment placeholder instead.

### Phase 5: `challenge.rel`, then `menus.rel`
- `challenge.rel` is the smallest module (349 functions). It's a realistic target for **the first fully matched module**, and it reuses game types.
- `menus.rel` has many small UI functions and should go faster once the shared types exist.

### Phase 6: Finish the libraries
- **MusyX:** 17 files are not matching. Compare against existing MusyX decomps (the PrimeDecomp projects ship matching MusyX sources). First pin down MSSB's exact MusyX version, then import the matching implementations.
- **Remaining SDK pieces:** `os` (one file), `C3/control`, and the two `Unknown/` files.
- These are mechanical, and good for days when the game code is stuck.

## Picking work day to day

1. Any function at ≥95% in a file that's close to complete.
2. Small leaf functions (≤256 B) in the file currently in progress.
3. Struct/naming work whenever a function is blocked on unknown types.
4. Library cleanup (MusyX/SDK) as filler.

Don't spend more than about 30–45 minutes on a single register-allocation fight. Leave a `// 99%: <what's wrong>` note above the function and move on; the pattern often becomes obvious after a few more functions.

## Coordination

- This is a fork of `roeming/mssb-dtk`. Check upstream regularly for new matches and renamed symbols, and rebase so we don't duplicate work.
- Send finished work upstream as small PRs (one file or a few functions per PR).
- If upstream or the community has a Discord, ask about known compiler-flag quirks (for example per-file `-inline` or `-fp_contract` overrides) before fighting them alone.
