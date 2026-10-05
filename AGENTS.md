# Agent guide: matching functions in the MSSB decomp

Goal: write C that compiles **byte-for-byte** to the original Mario Superstar Baseball (GYQE01) code. See `plan.md` for strategy and priorities; this file is the mechanics.

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
python3 tools/claim.py claim game/game/rep_3880 --who agent-3
python3 tools/claim.py list
python3 tools/claim.py release game/game/rep_3880                # when done or giving up
```

Only edit your claimed unit's `src/...c` and its own `include/...h`. Changes to shared files (`include/static/*`, `include/game/UnknownHomes_Game.h`, `symbols.txt`) are fine when needed, but keep them small and **additive**: add declarations, fields and names, and don't reorder or reformat. That keeps merges between agents clean.

## The loop for one function

```sh
python3 tools/next_targets.py --unit game/game/rep_3880        # what's left in your unit
python3 tools/fnstart.py fn_3_147C00                           # asm + m2c draft + current diff
#   ...edit src/game/rep_3880.c: replace the stub with the m2c draft, clean it up...
python3 tools/fndiff.py fn_3_147C00                            # MATCH, or the instruction diff
python3 tools/fnvariants.py fn_3_147C00 a.c b.c --also caller1 # score several candidate versions
```

- Source files are mostly **stubs** (`void fn_3_XXXX(void) { return; }`) with `// .text:0x... size:0x...` comments above them. Replace the stub body and fix the signature (also in the unit's header).
- The m2c draft is only a starting point. Give it real types and struct fields (`include/`), rename `temp_rN` variables, and turn `goto` loops into `for`/`while`.
- Calls to `main.dol` functions need a prototype. Check `config/GYQE01/symbols.txt` for the name, and add `extern` declarations to `include/static/UnknownHomes_Static.h`. Argument types show in the callee's asm (for example, `clrlwi r3, r3, 24` means a `u8` argument).
- `fndiff` output: `<` lines are the original, `>` lines are ours. Named symbols are compared too, so a name mismatch means the header and `symbols.txt` disagree.

## Definition of done for each function

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

Common fixes are listed under "Matching patterns" in `plan.md`. Try them first. If a function is at 95%+ and you've spent ~30–45 minutes on it, leave a comment above it, like `// 99%: float regs f4/f5 swapped around inlined dolsqrtf2`, commit nothing for it, and move on. Add any new pattern you discover to `plan.md`.

## Don'ts

- Don't edit anything under `orig/` or `build/`, or `config/*/splits.txt`, unless the task is splitting.
- Don't mark objects `Matching` in `configure.py` unless the whole unit matches and you've checked the full build.
- Don't commit a "match" that lowers the total matched-function count.
- Don't run two agents in the same directory.
