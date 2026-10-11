# Agent guide: matching functions in the MSSB decomp

Goal: C for every function of Mario Superstar Baseball (GYQE01), ideally compiling **byte-for-byte** to the original. The end goal is a PC/browser port on aurora (see "End goal" in `plan.md`), so every function needs C that is correct and portable. Matching is how we prove it's correct. See `plan.md` for strategy and priorities; this file is the mechanics.

## One-time setup (per checkout or worktree)

```sh
python3 tools/setup.py
```

This downloads the toolchain and gets the original game files: it copies them from the main checkout, or extracts them from `../mario_baseball.iso` (or `--iso PATH` / `$MSSB_ISO`). It verifies hashes, installs m2c into `.venv`, and does a full build. Takes about 15 seconds in a worktree.

## Parallel agents: one worktree each, one file each

Never share a working tree with another agent. `ninja` and `tools/fnvariants.py` rewrite files in place.

```sh
git worktree add ../mssb-agent-3 -b agent-3      # from the main checkout
cd ../mssb-agent-3 && python3 tools/setup.py
```

Claim a unit (source file) before working on it. Claims are shared by all worktrees of this clone:

```sh
python3 tools/next_targets.py --files --has-source --unclaimed   # pick a unit
python3 tools/next_targets.py --unit main/main/ --max-size 256 --unclaimed   # default pool: main.dol game code (src/main/)
python3 tools/claim.py claim game/game/rep_3880 --who agent-3
python3 tools/claim.py list
python3 tools/c_coverage.py --units                              # units by functions still without C (matched or equivalent)
python3 tools/claim.py release game/game/rep_3880                # when done or giving up
```

Only edit your claimed unit's `src/...c` and its own `include/...h`. Changes to shared files (`include/static/*`, `include/game/UnknownHomes_Game.h`, `symbols.txt`) are fine when needed, but keep them small and **additive**: add declarations, fields and names, and don't reorder or reformat. That keeps merges between agents clean.

## The loop for one function

```sh
python3 tools/next_targets.py --unit game/game/rep_3880        # what's left in your unit
python3 tools/fnstart.py fn_3_147C00                           # asm summary + m2c draft + diff summary (--asm for the listing)
#   ...edit src/game/rep_3880.c: replace the stub with the m2c draft, clean it up...
python3 tools/fndiff.py fn_3_147C00                            # MATCH, or diagnosis + first hunks (--full for all)
python3 tools/fnvariants.py fn_3_147C00 a.c b.c --also caller1 # score several candidate versions
```

- `src/main/file_<ADDR>.c` holds `main.dol`'s game code: the engine that all three RELs call. It's the default place to work, because names and types found there spread to every caller.
- Source files are mostly **stubs** (`void fn_3_XXXX(void) { return; }`) with `// .text:0x... size:0x...` comments above them. Replace the stub body and fix the signature (also in the unit's header).
- The m2c draft is only a starting point. Give it real types and struct fields (`include/`), rename `temp_rN` variables, and turn `goto` loops into `for`/`while`.
- **Write portable C** (the port builds this code for 64-bit and wasm):
  - Use named struct fields, not raw offsets like `*(u16*)(p + 0x14)`. Add the field to the struct in `include/`, with padding if needed. It matches the same.
  - Never store a pointer in `u32`/`s32`. Use a pointer type (or `void*`).
  - Give every function a real prototype, with the same signature everywhere it's declared.
  - Only reach for an offset cast when nothing else matches, and leave a `// TODO type` next to it.
- Calls to `main.dol` functions need a prototype. Check `config/GYQE01/symbols.txt` for the name, and add `extern` declarations to `include/static/UnknownHomes_Static.h`. Argument types show in the callee's asm (for example, `clrlwi r3, r3, 24` means a `u8` argument).
- `fndiff` output: a summary, a `diagnosis:` line, then hunks. `<` lines are the original, `>` lines are ours. On large diffs, register-only hunks are folded into the `register map` line; fix the structural hunks first. Named symbols are compared too, so a name mismatch means the header and `symbols.txt` disagree.

## Definition of done for each function

There are two levels. Never leave a function as a stub just because it won't match.

- **Matching:** `fndiff` prints `MATCH`. Follow steps 1–4 below.
- **Equivalent:** the C is correct (same behaviour, same calls, same results) but doesn't match byte-for-byte. Wrap it like this and delete the stub. The matching build then leaves the function out (objdiff shows it unmatched, which is accurate), and the port build gets real code:
  ```c
  // NONMATCHING 97%: r27/r28 swapped in the loop (see docs/patterns/regalloc.md)
  #if NONMATCHING
  s32 fn_8001234(u8* p) { ... }
  #endif
  ```
  Use `#if`, not `#ifdef`: some libraries already compile with `-DNONMATCHING=0`. Check it compiles with `python3 tools/nmcheck.py src/<unit>.c` (the matching build never compiles it), then commit it as `equivalent <function_name>` once the full build still passes steps 2–3. Use this when a function has hit its time budget (see "When stuck"), or right away for very large functions where matching would take hours.

Steps for a matching commit:

1. `python3 tools/fndiff.py <fn>` prints `MATCH`.
2. Run a full `ninja`. In its progress output, the `game:` (or relevant module) function count must go **up**, and no function that matched before may stop matching. Inlining means editing one function can break its callers; check with `fnvariants --also`.
3. `./build/tools/dtk shasum -c config/GYQE01/build.sha1` reports OK for all 4 files.
4. Commit **one function per commit**, staging only the files you touched:
   ```
   git commit -m "match <function_name>"
   ```
   Commits are authored as `bigmah <bigmahdev@gmail.com>` (repo-local git config). Never push; the maintainer merges agent branches.

When every function in a unit matches, tell the maintainer. The unit can then be switched from `NonMatching` to `Matching` in `configure.py`.

## When stuck

Common fixes are in `docs/patterns/<topic>.md`, one per line. **Grep them for your symptom; don't read them whole:**

```sh
grep -i 'fcmpu' docs/patterns/*.md        # or: dont_inline, extsb, lwzx, unroll, switch, r27 ...
```

If you've spent ~30–45 minutes on a function and it still doesn't match, commit it as **equivalent** (see above), with the match % and what's wrong in the `// NONMATCHING` comment, and move on. Add any new pattern you discover as one line to the closest `docs/patterns/` file: `- **Symptom (fn_name):** fix.`

## Don'ts

- Don't edit anything under `orig/` or `build/`, or `config/*/splits.txt`, unless the task is splitting.
- Don't mark objects `Matching` in `configure.py` unless the whole unit matches and you've checked the full build.
- Don't commit a "match" that lowers the total matched-function count.
- Don't run two agents in the same directory.
