# Plan: matching the rest of Mario Superstar Baseball

## Where we are (2026-10-05)

| Module | Code | Matched | Unmatched functions by size (≤64B / ≤256B / ≤1KB / >1KB) |
|---|---|---|---|
| `main.dol` SDK, MSL, Runtime, TRK | 230 KB | 99.5% | ~5 left |
| `main.dol` MusyX | 128 KB | 55.6% | 90 left, many at 95%+ |
| `main.dol` game code (unsplit `auto_*`) | 549 KB | 0% | 241 / 316 / 332 / 153 |
| `game.rel` | 1.5 MB | 3.1% (148 / 2406) | 211 / 625 / 1002 / 420 |
| `menus.rel` | 618 KB | 0% | 240 / 293 / 569 / 131 |
| `challenge.rel` | 171 KB | 0% | 68 / 96 / 137 / 48 |

Overall: **~11% of code matched, 0 game files linked.**

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

These came up repeatedly in `rep_1838.c`. Try them first when a diff is only register order or branch shape:

- **Register swaps:** copy a parameter into a local before modifying it (`s16 a = ang;`), or modify the parameter in place and keep a separate copy (`sign = max; if (max < 0) max = -max;`).
- **`ABS(x)` vs `if (x < 0) x = -x;`:** both can produce the branch-free `srawi/xor/subf` sequence, but they give different register allocation. Try both.
- **Argument shape decides inlined code.** When a function is inlined, how the caller builds the argument matters. `f(max - min + 1)` gave the branch-free abs, while `int n = ... + 1; f(n)` gave the branching (`addic.`) version.
- **Inlining couples functions.** Small functions in the same file get inlined into their callers (`-inline deferred`), so changing one function's body changes every caller's code. Always score callers with `--also`. A "match" that breaks a caller is not a gain.
- **Write the result straight to the global** (`g.x = g.x + ...; r = g.x % n;`) instead of using a temp, when the original stores the value and then reuses the register.
- **Symbol names must agree.** A header `extern` name and `symbols.txt` have to use the same name. Otherwise the diff shows a relocation mismatch even when the code is right. Rename in `symbols.txt` when the header name is better.

- **Prologue loads the global straight into the saved register:** if the original does `lwz r31, g@l(r4)` before the first call (instead of `lwz r3` + `mr r31, r3`), write the first call as `fn(p = g, ...)`.
- **Fixed-stride global arrays:** if the compiler hoists `base+8`/`base+0x10` into registers, declare the array as `T *arr[]` and index by `(i + 1) * 2` instead of a struct array.
- **Globals in game units: declare an `extern` with the symbol's name from `config/GYQE01/game/symbols.txt`** (`extern u8 lbl_3_bss_995C;`, `extern u8 lbl_3_common_bss_35154[];`, `extern u8 g_Ball[];`). Use `u8[]` plus casts (`*(s16*)(g_Ball + 0x1BBC)`) when there is no struct. The name has to match; the object does not need to define it. Put every `extern` at the **top** of the file; a later declaration is not visible to earlier functions. `.data` symbols (`lbl_3_data_XXXX`) work the same way.
- **Scalar vs. array decides `lis+stw` vs `lis+addi+lwz`:** `extern u32 x; x = v;` gives `lis; stw x@l(r4)`. `extern u8 x[]; *(T*)(x+off)` gives `lis; addi; ...off(r3)`. Pick whichever the original does. A pointer-to-pointer global read as `lis; addi; lwz 0(r3)` is `extern void* g[]; p = g[0];`.
- **Calls into stubs of the same file vanish.** Unimplemented stubs (`return;`) are inlined into callers defined after them, so the `bl` disappears. Put `#pragma dont_inline on` after the includes of that file, and give the stub the right parameters (`void f(u32 a, u32 b) { return; }`). Callee prototypes in other units are `void f(void)` placeholders; declare a local `extern` with the real arguments instead.
- **Unrolled loops:** `#pragma opt_unroll_loops off` before the function (and `reset` after), plus a `do { ... i++; } while (i < N);` form for bottom-tested loops.
- **Struct-array element address:** if the original does `mulli; add; lwz 0x80(r3)` but we get `mulli; addi 0x80; lwzx`, index a typedef'd struct of the right size instead of `u8*` plus a byte offset. For a plain `u8*` base, `u8* f = base + i * SIZE; f[OFF]` (separate pointer) often fixes the same thing.
- **Float compare functions** (`return -1` / `return a > b`): read both values into locals first (`f32 x = *a; f32 y = *b;`). The register order then matches.
- **`while (n--)` empty delay loops:** `for (i = 13; i != 0; i--) {}` gives `li r0,13; mtctr r0; bdnz`.
- **A `.sdata2`/`.rodata` symbol used by a function needs a split** (`.sdata2 start:... end:...` in `splits.txt`) before the report counts it as matched (see `Musyx/snd_math.c`).
- **Bitfield flags:** `rlwimi r0, r4, 7, 24, 24` on a byte is a `u8 f : 1;` member (msb). Use a small typedef'd struct with padding up to the byte.
- **Known blocker: float constant pooling.** Functions that use several `.rodata` floats get a single pooled base register in our build (`...@l` held in a saved register), while the original does `lis`/`lfs` per constant. No source form found yet; skip float-heavy functions with many constants for now. A single `extern f32 lbl_3_rodata_XXXX;` constant works fine. Declaring every constant as its own `extern const f32/f64` (real symbol names) avoids the pooling in some functions; a local `M12 id = lbl_3_rodata_XXXX;` copy works for identity matrices.
- **Float compare against 0:** `if (v)` emits `fcmpu f1,f0` (call result first) like the original; `v != 0.0f` swaps the operands. `x / 2.0` gives `fmul f0,f1,f0` where `x * 0.5` doesn't.
- **`#pragma dont_inline on` blocks `inline` callees too:** with `-inline deferred`, `dolsqrtf2` stays a `bl` until the pragma is removed. Check that before blaming float constants.
- **Pointer-array loops:** `((u8**)sym)[i + OFF/4]` (indexed by the loop counter) or `u8* b = sym; ... b += 4` reproduces the original's `lwz OFF(rN)` / `addi rN,rN,4` shapes.
- **Declaration order matters:** the order of local declarations changes saved-register assignment and stack layout (earlier-declared locals get higher stack addresses). Permute it; a small hill-climb script helps.
- **Replace a struct with separate locals** declared in reverse memory order, plus `u32 pad` before/after for the frame size, when the compiler hoists member addresses (`__OSBootDolSimple`).
- **`a ? b : c` min** in place of `x = a; if (a >= b) x = b;` changes register allocation (`aramStoreData`).
- **Reuse one local** for an index and a later loop counter, or write `q[0x34] = i = 0;`, to keep the original's register sharing.
- **Calling a stub the original calls with no args:** cast it `((void(*)(void))f)()` so `r3` stays stale.
- **A function inlined into its caller must land in the same commit** as the caller's match (`fn_3_6BEA4` and `fn_3_6C1D8`).
- **`fndiff` line counts do not track the objdiff score;** trust `build/GYQE01/report.json`. A `DATA` vs `lbl_...` name difference in `fndiff` is noise if the report says 100%.
- **`(s8)`/`s8` params:** `extsb r3, r3` on a loaded byte argument comes from `*(s8*)(base + off)`, not `(s8)base[off]`.
- **`base + idx*4` with a big field offset, base hoisted before the shift:** write `p = ((u8**)(sym + 0x2C50))[idx];` (cast base+offset, then index) instead of `*(u8**)(sym + idx*4 + 0x2C50)`.
- **Unused-looking float arg in a callee:** if the original multiplies a constant into f1 and the constant sits in f2, the callee takes `(.., f32 a, f32 b)` and is passed the constant as 2nd float. Cast the call: `((void (*)(int, int, f32, f32))fn)(...)`.
- **Call to a stub declared `(void)`:** cast to the real signature at the call site so the args are live (also decides which scratch regs get used).
- **State-setup functions on `lbl_803CC1B8`:** `extern u8* lbl_803CC1B8; u8* p = lbl_803CC1B8; fn_80034E20(p, data); ... *(void**)((u8**)&lbl_803CC1B8)[0] = fn;` reproduces the mixed direct/`addi`+`lwz` loads.
- **Low-byte read-modify-write:** `w = v | (w & ~0xFF)` gives `rlwimi r0, r4, 0, 24, 31`; the other operand order gives swapped operands.
- **Float literal vs. extern rodata:** comparing against a literal (`0.17f`) instead of the extern rodata symbol can fix `lfs` scheduling; loading an extern float into a local first fixes others.
- **`switch` on an `s8`** reproduced an odd `beq`/`b` shape; `*(s16*)(p+off) += 1` matched where `x = *p; if (x < N) *p = x + 1` did not.
- **`add rN, base, off; lwz 8(rN)` (displacement after the add) for `tbl[idx*8 + 8]`:** write `u8* e = tbl; e += idx * 8; p = *(u8**)(e + 8);` (separate pointer, `+=`), not a single expression. Likewise `u8* e = g_X; e += *(s8*)(e + 0x1904) * 2; *(s16*)(e + 0x1898)` re-materializes the base like the original (fn_3_120F5C, fn_3_11F778).
- **Float constant compare via bool value:** a `cntlzw/srwi./beq` for `x == 2` is `if ((u32)__cntlzw(2 - x) >> 5)` (fn_3_120FF8).
- **Stubs called with fewer args than the real function:** call through a cast (`((void (*)(void))fn_800B0A14_removeQueue)()`), and pass only the args the original sets up (stale `r4` in `fn_80035CA4(5)`).
- **Pointer induction loops:** `while (k-- != 0) p = *(u8**)(obj + 8 + k * 4);` gives the `subi r30, r30, 4` induction pointer.
- **Shared scratchpad dir:** parallel agents share one scratchpad directory; use a private subdirectory for variant files or `a.c` gets clobbered.
- **Inlined state-queue check (`fn_3_12536C`):** the leaf `fn_3_12536C` is inlined into `fn_3_11F508`-style functions; its return type must be `u32` so the caller emits `cmplwi`.
- **Float literal instead of extern rodata (fixes prologue scheduling and constant reuse):** `CTRLSetScale(c, 0.2f, 0.2f, 0.2f); a[0xB4] = 0.2f;` matched where `extern f32 lbl_3_rodata_2B28` did not (fn_3_E45A8, fn_3_E45F0, fn_3_E2034, fn_3_13D5E8 with `100.0f`). Look up the value in the `.obj lbl_3_rodata_XXXX` block of `build/GYQE01/game/asm/...`. Works when a function uses one or two distinct constants; with 3+ the literals get pooled again, so use externs there. Declaring an unused `extern const f32` for a rodata symbol can break a *different* function that uses the same literal.
- **`2.5 >= PSVECMag(&v)`** (constant on the left) gives `fcmpo f0,f1; cror eq,gt,eq`; `PSVECMag(&v) <= 2.5` gives the swapped form.
- **Bottom-tested update order in `for` headers:** `for (...; i++, a += 0xC, b += 2, c += 1)` vs another order changes where the `addi`s are scheduled (fn_3_13F6C8). Try all 24 permutations with `fnvariants`.
- **Do-while with two pointers advancing at different strides** (`u8* m` +1 and `s16* sp` +1): declaring the pointer locals in a different order changes which one gets r4/r5; permute declaration order with a script.
- **`#pragma dont_inline on` also stops `static inline` helpers from inlining** in the same file region; to inline a helper, put `#pragma dont_inline off` around it AND its callers, and even then CW may not inline a body this large.
- **`fndiff` MATCH can hide branch-target differences.** It ignores label names, so a branch that jumps to the wrong place still prints MATCH (`fn_3_A0F0` had `done == 0` outside the `if`). Always confirm 100.0 in `build/GYQE01/report.json` (fuzzy_match_percent) before committing.
- **Struct-array deref after a call:** `((T**)sym)[0][idx].field` (T = padded struct of the element size) gives `lwz r0,sym@l; add r3,r0,off; lwz field(r3)` (`fn_3_B91C8`). `*(u8**)sym + off` and `((T*)(...))->field` give `addi/lwzx` instead. Also `((u32*)(c + 0x1C))[n]` (not `c[n*4+0x1C]`) keeps the displacement on the load (`fn_3_B95EC`).
- **Return type matters for register choice:** `processStadiumObjectFunction` only matched as `void` (an `int` return burned r3 as a live value).
- **Stale argument registers:** a callee the original calls with a stale r3 (e.g. `fn_800BF068`) must be declared with `()` and called with no args. Params that the original never reads should still be named in the definition (C needs names).
- **A function in the same unit is inlined into its callers** and its body shows up there (`fn_3_B8184` into `fn_3_B8298`; `fn_3_A0F0` into `fn_3_BC54`). Match the small one first, then write the caller as a plain call.
- **Return-shape trick:** `if (cond) { ...; if (!(a || b)) return; } helper();` produced the single shared tail (`bne L` into one inlined copy) for `fn_3_BC54`; `if (x) helper(); else helper();` duplicated the inline.
- **Loop counter registers:** declaring `s32 off; u32 i;` and assigning `i = 0; off = 0;` after the float setup (not in the declaration) fixed which saved reg got which (`fn_3_B98E8`). Declaring a float local first gives it the higher f-reg (f31).
- **Countdown `for (i = N; i != 0; i--)`** gives `mtctr/bdnz` for big N (`fn_3_A83C` first loop), but a trip count of 3 is fully unrolled whatever the pragma; do-while forms give `subic.` instead. Unsolved.
- **Compiler-unrolled copy loops:** `for (i = 0; i < 0x3C; i++) { copy 3 floats }` reproduces the 8x unrolled ctr loop with the `cmpwi r6,0x3c; bge` guard (`fn_3_F9F8`).
- **Constants reloaded per use (no CSE across stores):** with `extern f32` constants the compiler sometimes keeps one in a register across stores to `g_Ball[]` (`fn_3_9B74` stuck), while `fn_3_BC54` reloaded as in the original. Untangled cause not found; float literals instead give the pooled-base blocker.
- **Musyx units are an OLDER MusyX than the reference source.** Before matching, compare field offsets in the asm with the header structs (`SND_EMITTER` has no `room`, `SND_LISTENER` has no `room` and an extra float at +0x8C, `FX_GROUP` is 0xC with a refcount, `CHANNEL_DEFAULTS` is 9 bytes `#pragma pack(1)`, `VS_BUFFER` is 0x2C, `SND_PARAMETER.ctrl` is u16, `dataAddSampleReference` takes a 2nd pointer arg). A struct fix often turns 99.9% functions into matches. Functions the reference has but the asm doesn't (rooms, doors) can be deleted.
- **Static-name noise:** `key$604` vs `key$618`, `...bss.0` vs `vidList` and `DATA` vs `lbl_803CDxxx` in `fndiff` do not stop `report.json` from counting a match. Only trust the report. `.bss` splits in the middle of Musyx cause a cyclic link-order error (only `.sbss`/`.sdata2` splits worked); add `.sbss`/`.sdata2` splits and rename `lbl_...` in `symbols.txt` to the static's name.
- **A `(u8)` cast on the compare operand** (`x != (u8)(v & 0x7f)`) changed instruction scheduling and fixed `inpSetMidiCtrl`. Try it when only two instructions are swapped.
- **Same inline helper at two call sites gets separate register allocation**, which is how the original has duplicated blocks (`GetEmitterKey` in `AddEmitter`/`s3dHandle`/`StartContinousEmitters`). A helper with a different declaration order of its locals fixes the pointer/counter register swap.
- **Two identical loops over different variables** (`macHandle`): use separate locals (`sv`/`sv2`) to get the separate registers.
- **`dolsqrtf` (from `stl/math.h`)** gives the inline `frsqrte` sequence with the `vf32` round-trip; implicit `sqrtf` becomes a bl returning int.
- **Float clamp:** `clip3FFF(f32)` that compares the float against 16383.f before converting; `x < lo ? lo : (x > hi ? hi : x)` for signed clamps (`bgt` then `mr` shape).
- **`fmuls` operand order** follows how the product is split: `sScale = a * b; x += (s32)(sScale * c)` fixed `mcmdSetADSR`; `(a*b)*c` in one expression did not.
- **LE byte reads** (`lbz`/`rlwimi` chains, or `lhz` + `srawi`/`rlwimi` for u16) come from `p[0] | p[1] << 8 | ...` and `(v >> 8) | (v << 8)` macros (inline functions are blocked by `dont_inline on`).
- **Inline call before optimisation:** if the original CSEs an index/field across an inlined static call (`voiceSetPriority`), it was a macro or hand-merged code, not an inline function.
- **Nested early returns `bge L; b L` SOLVED:** write the guard as one early-return `if (a != 7 || b != 6 || x > 4 || x < 0) { return; } call();` (fn_3_150010, fn_3_14DC80, fn_3_15521C, fn_3_14CB28, fn_3_14A070 `if (n > 4 || n == 0 || src == NULL) return;`). Positive `&&` guards wrapping the body give `beq L` instead; use the positive form only when the original has plain `bne L` (fn_3_14C904).
- **Dead stack copy of a rodata triple (fn_3_FD51C):** `V3U v = *(V3U*)rodata; *(V3U*)(p+0xC) = v;` reproduces lwz once + both stores + the stack store. A `u32 t[3]` dead copy is optimized away.
- **Float constants as locals fix scheduling (fn_3_14D318):** `f32* d = (f32*)data; f32 h = 0.5f; ... d[3] * h` matched where the bare literal did not.
- **`(u32)rand() % 23`** gives `mulhwu`, `rand() % 23` gives signed `mulhw`.
- **Struct with bitfield for list refcount (fn_3_154238):** `typedef struct { u8 pad0[0xC]; u8* head; u8 pad[4]; u16 hi:4; u16 cnt:12; } H;` then `h->cnt--`; keep `link = &h->head` for the unlink pointer.
- **Still unsolved:** pooled float constants in float-heavy functions (fn_3_148EF0, fn_3_14C3BC); `divwu` by 7 (fn_3_1575F0, fn_3_15730C: `n / 7` gives mulhwu); fn_3_FCE38/FCEB0 (out-of-line loop init blocks); fn_3_14E894 (99%, `li r30,0; mr r31,r30` zero reg).
- **Brute-force expression/statement orderings:** when only scheduling or operand order differs, generate dozens of variants (term order, grouping, statement permutations) into files and score them all with `fnvariants.py`; this found `fn_3_142030`, `fn_3_1118B4` (`tbl[k] + rand() % 7 - 3`) quickly.
- **Callee-passthrough arg:** if the original's first `lis` lands in r4 (r3 left untouched), the function takes an unused-looking arg that it forwards to its tail call (`void f(s32 x) { ...; ((void(*)(s32))g)(x); }`, `fn_3_143FAC`).
- **Redundant `beq L; beq L` pair:** write the condition as `a == 0 || (a != 0 && ...)` (`fn_3_111AC4`).
- **Nested fixed loops fully unrolled with `cmpwi r0,0xa` leftovers:** plain nested `for` over a typedef'd struct with `s16 a[4]; u8 b[4][10]` matched (`fn_3_142CA8`).

- **`bge L; b L` nested early returns (fn_3_BD6AC):** `if (v < 0xD) { if (v >= 0xB) call(); }` and the `return`-style forms all give `blt`; `switch (v) { case 0xB: case 0xC: call(v == 0xC); break; }` produces the original `bge L; b L` shape.
- **Brute-force declaration/initialisation order with a script** (all permutations of local declarations x init statements, scored with `fndiff`): fixed `fn_3_3AAF8`, `fn_3_33458`, `fn_3_A3B30`-style register swaps. Plain `u8* f; s16 i;` (decls first, then assign) beats `u8* f = ...` initialisers.
- **Second struct-array access that the original re-materialises:** `u8* f; f = g_Fielders; f += idx * 0x268;` (or `f = g_Runners; f += ...`) stops the compiler from CSE-ing with an earlier `g_Fielders + off` (`fn_3_870AC`: arg `*(s16*)(f + 0x178)` after `f += *(s16*)(g_Ball + 0x1B78) * 0x268`).
- **Fixed 4/9-element loops over a struct array get fully unrolled by the compiler** when written as `for (i = 0; i < N; i++) { ...; r += 0x154; }` with a `u8* r` pointer (fn_3_27648, fn_3_86DFC); `for (i = 0; i < 4; i++) { RunnerT* r = &((RunnerT*)g_Runners)[i]; }` with `typedef struct { u8 b[0x154]; } RunnerT;` fixes the pointer-induction form (fn_3_88F98).
- **Float literal for the constant used once or twice, `extern f32` for the rest** (fn_3_A4158 `2.0f`, fn_3_BB07C `100000.0f`/`0.0f`); declare the float locals in the order `f32 s; f32 a; f32 c;` to get f31/f30 right.
- **Still unsolved (hoisted global address):** `lis rX, g_Fielders@ha` scheduled before `mr r30, r3` when a function keeps its index across a call (`fn_3_483CC`, `fn_3_7F9C4`).

Add new patterns to this list as we find them.

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
- 549 KB / ~1,040 functions currently sit in ~880 `auto_*` units. Many already have meaningful names (`FillRosterPos`, `characterSelectScreen`, `Custom_SetState`).
- First split them into source files by address range, following natural boundaries (where alignment padding, string tables and `.ctors` show a new file starts). Then match them the same way as `game.rel`.
- This code is probably the core engine (memory, file loading, controller/state helpers) that the RELs call. Matching it early gives names and types to all three RELs.

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
- **A near-match with only register swaps may hide a control-flow difference.** `checkCollision` was stuck on r28/r29/r30 swaps until the `b L` after `processStadiumObjectFunction` was noticed: that branch goes to the function's end, so write `goto done;` (return label) instead of falling through to the next `if`.
- **Several `||` compares of one `x & mask` merge into subi/cmplwi ranges**; the original's unmerged `cmplwi r0,N / beq` chain came from `t = f(); t &= 0x7F; if (t==2||t==3||...) return 1; else return 0;` with an explicit `else` (`fn_3_B7C2C`).
- **Inlined `dolsqrtf2` in a file that has `#pragma dont_inline on`:** put the pragma `off` from the sqrt user to the end of the file (re-enabling `on` afterwards undoes the inlining) and keep earlier callers under `on` so they do not inline the big function. Use an `s16` parameter when the prologue has `extsh r28, r6` (`didCollideWithBoundingBoxes`).
- **`...rodata.0@ha` base-register pooling appears when an inlined helper uses float literals** (0.5/3.0/0.0). To get the original's separate `lis/lfd` per constant, write the helper with `extern f32/f64 lbl_3_rodata_xxx` operands instead of literals.
- **`int` vs `bool` returns:** callers compare with `cmpwi` only if the callee prototype returns `int`; for `checkTriangleCollisions` the local `ret` had to be `int` (not `bool`) for the callee to keep matching.
- **`__abs(x)`** gives the branch-free `srawi/xor/subf` abs (plain `abs` becomes a `bl`).
- **Direct `lwz r0, sym@l(rN)` (no `addi`) for a pointer stored in a global array/struct:** read it as `*(T**)&sym` (`T* p = *(T**)&sym + idx;`), not `sym[0]`/`sym.field`. Keeps the CSE'd `idx*size` register and matched `fn_3_C823C`.
- **Stub callee inlined into a matched caller (`bl` vanished):** a `return;` stub in the same file gets inlined. Add `#pragma dont_inline on` at the top (kinoko.c) so the call stays.
- **Float compare operand order (`fcmpu f1,f2`):** `if (0.0f_extern == PSVECMag(v))` and `if (PSVECMag(v) == z)` both emit `fcmpu z,mag`. Store first: `m = PSVECMag(v); if (m == z)` flips it (`fn_3_169E70`).
- **`s8` args to int-prototyped callees (`lbz r3; extsb r3,r3`):** declare the callee params `s32` and the local/param `s8`; that reproduces the explicit extsb at each call (`fn_3_16B488`).
- **Statement order vs. register choice:** two independent stores (`x = -1; y = 0;`) swapping order fixed `li r0/r4` allocation (`fn_3_169600`). Try swapping before restructuring.
- **Locals declared in an order that decides r27..r31:** when pointer/index locals come out permuted, add `u8* q;` as a separate declaration assigned later (not `u8* q = ...` inside the loop) (`fn_3_169D00`).

- **Data addressed via one section-base register (`fn_3_168704`, `fn_3_168DFC`):** the original TU defines the `lbl_3_data_285A8` area itself as separate `.data` objects, so it keeps one base register and emits `addi rX,r31,off; lbzx`. `extern` declarations give `lbzu` or one `lis` per symbol. Probably needs the data split into this unit in `splits.txt` before it can match.
- **Struct-array stride fixes `addi/stbx` vs `mulli/add/stb`:** `((E28*)*(u8**)(base + OFF))[i].f = 0;` with a typedef'd struct of the element size matched where `p[i * 0x28 + 0x26]` did not (fn_3_116B38).
- **Float `a*idx + lo` with a precomputed span:** `f32 lo = d[0]; f32 st = d[1] - lo; st = st / 5.0f; x = st * (f32)idx + lo;` (three statements) gave the original f2/f3 allocation; one-expression forms did not (fn_3_20EEC).
- **`if/else if` chain instead of `switch` for small case sets:** CW emits a jump tree for `switch (u8)` with cases 1..3, while the original compares the same reloaded byte with `cmplwi` per case (fn_3_21768, fn_3_20FB0).
- **`(tbl + a*4)[b]` instead of `tbl[a*4 + b]`:** keeps the original's `lbz b` before `lbz a` and `lbzx` shape for 2-D byte tables. `s32 chance` (not `u8`) avoids the extra `clrlwi` when later `+= s8`.
- **Struct field signedness is a free parameter:** a `lha` where the header says `u16`/`u8` means change the shared header field to `s16`/`s8` (fn_3_215AC, fn_3_20CEC); check no other file uses it.
- **Inlined matched siblings:** once `fn_A`/`fn_B` match, a caller defined later gets them inlined; write the caller as plain calls (fn_3_215AC = `if (cnt==1) fn_3_20EEC(); fn_3_20E50(); ...`). Stubs it must still call need `#pragma dont_inline on/reset` around them.
- **Unmatched near misses:** fn_3_8B890 (m_sound) 98%: original has `bne L; b end; L:` before the emitter body for `if (range) { if (flag == 0) return; ...}` and no source form found; fn_3_90220/fn_3_90150 (m_sound): original loads `tbl[off]` before `tbl[off+0x180]`, load order not reproduced.
- **Sibling function inlined despite `#pragma dont_inline on`:** if a function asm contains the whole body of another function in the same file (OSPanic/memset/switch of `fn_3_16B488` inside `fn_3_16B5B4`), copy the body by hand; the extra params become the outer function params (`fn_3_16B5B4(u8* out, s8 id, int t)`).
- **Lerp with `1.0 - k` (double) and `k` (float):** declare `f64 k1;` before `f32 k`, then assign `k1 = lbl_3_rodata_4048 - k;` to get the original f4/f3 assignment; use `extern const f32/f64` per rodata constant (`fn_3_16B5B4`).
- **Compound assignment vs. `x = x - ...`:** `vel->x -= vel->x * k;` matched where `vel->x = vel->x - vel->x * k;` picked the wrong float regs for an inlined block (`fn_3_15B79C` / `fn_3_15C024`).
- **Unmatched notes (agent-af57):** `fn_3_FCE38` is at 6 diff lines (original puts `slwi r6,r3,6` for the second loop out of line after the first loop; while loops with a separate `off` variable and `off += 0x40; i++` order get the regs right). `fn_3_B7E44` needs the 0.06 double loaded via `addi` base like the magic double. `fn_3_104B20` (3-float copy, loads f2,f1,f0 then stores) resisted every local-variable ordering.
- **Signed `% 2^n` shape:** `slwi r0,x,32-n; srwi r4,x,31; subf; rotlwi n; add` is `(s32)rand() % 2^n` (so `slwi 30 / rotlwi 2` is `% 4`, not `% 2`). Declare `rand` as `u32 rand()` and cast to `s32` (`fn_3_C9C94`).
- **Two float rodata constants pooled via one `addi` base (`lis r4; addi r5,r4; lfs 0(r5)`):** use float literals (`0.5f`, `0.0f`) instead of extern symbols; with the externs the registers swapped (`fn_3_C9C94`). A `s8` temp loaded from a byte needs `s8 prev` (an `s32` gives a different extsb placement) (`fn_3_C9B5C`).
- **Search loop `do { if (v == *q) break; q -= 0x10; } while (k-- != 0);`** reproduces the `k = 1 .. -1` loop, but `fn_3_C0854`/`fn_3_C11CC` still differ in saved-register order and `lis` rematerialization of the data base; unsolved.
- **By-value struct args:** a 12-byte struct copied to the stack and passed by address is a by-value struct parameter forwarded to the callee (`fn_3_EF7B4(V3i v, s32 x)`); declare unused-looking extra params since they shift scratch regs.
- **Missing stubs:** some units lack a stub for a function (`fn_3_EDFAC` in `sta_c5.c`); fndiff says "not found in our build". Add it in address order.
- **Stale-r3 result:** `sndFXCtrl(vid, 0x5B, x)` after `sndFXStartEx(...)` passes the first call result.
- **Identical copy-pasted prologues** (`fn_3_F3AE0`/`F3BB0`) are separate bodies; load `z`/`x` into locals right after the stores to reproduce hoisted `lfs` order.

- **Index a pointer array with the loop counter instead of a manual byte offset:** `((u8**)*(u8**)(t + 0x18))[i]` lets the compiler build the strength-reduced `addi rN,rN,4` induction register (the `off += 4` version gives the right code with two registers swapped) (`fn_3_C3F70`).
- **Pointer-global deref + element field:** `(*(T**)&lbl_3_common_bss_350E4 + idx)->field` (T padded to the element size) gives `lwz r0, sym@l(r3); add r3,r0,off; lwz field(r3)` where `*(u8**)sym + idx*N + off` gives `addi/lwzx` (`fn_3_F6504`).
- **Cloned render/matrix helpers:** when a function looks like an already-matched sibling (`fn_3_B8184` vs `fn_3_C2310`), copy the matched body and only change the constants/globals. Use `Mtx` locals and a `(f32 (*)[4])` cast for `PSMTXConcat`; declare the callee prototypes only if they do not clash with `Dolphin/mtx.h`.
- **`h = sndFXStartEx(...); sndFXCtrl(h, 0x5B, v);`:** the original passes the first call's return value (r3) straight through as the first argument of the second call. Declare `sndFXCtrl(int, int, u8)`. A `u32 stad` (not `u8`) avoids the extra `clrlslwi` on `stad * 2`.
- **A local `u32 i` loop counter passed to a `u8` parameter** gives `clrlwi r4,r30,24` at the call and a bare `cmplwi` in the loop test (`fn_3_C298C`); a `u8 i` gives the opposite.
- **Struct copy of a rodata constant plus `memset`:** `Vec pos = lbl_3_rodata_2080;` copies with three `lwz/stw`, and `PSVECMag(&d) <= lim` (limit loaded into a local first) gives `fcmpo f1,f31; cror eq,lt,eq` (`fn_3_C5CE0`).
- **Float loads scheduled early:** reading `x`, `z` into locals (`z` first) before the stores moved the `lfs` above the stores in `fn_3_F3AE0`. A unused-size struct pad must be referenced (wrap it in a struct with the Control) or the compiler drops it and the frame size changes (`fn_3_F65C8`).
- **Stale-register calls:** the GX setup functions (`fn_3_C4B80`) match as plain `int`-prototyped externs, and `fn_80052734()+0x40` is passed straight to `GXLoadPosMtxImm`.
