#!/usr/bin/env python3
"""Find `#if NONMATCHING` functions that already match, and promote them.

For every function inside a `#if NONMATCHING` block, the unit is compiled as it
would be after promotion (the block unwrapped, or split around that function;
the rest of the file still sees NONMATCHING=0) and the function's asm is
compared with the target the way fndiff does (local labels, anonymous data,
float literals and jump tables anonymised; a global only ours references is a
mismatch). Other functions of the unit that match today must still match.

    python3 tools/nmpromote.py                    # scan every source, list candidates
    python3 tools/nmpromote.py src/game/rep_3C28.c --promote
    python3 tools/nmpromote.py --promote [-j 8]   # scan everything, promote + commit

--promote applies each candidate in turn: removes the wrapper (and its
`// NONMATCHING` / `// nmverify:` comment), runs a full ninja, requires
report.json to show the function at 100% with no previously matched function
dropping, requires litcheck to be clean for it, then commits `match <fn>`.
Anything that fails is reverted and reported.
"""
import argparse, json, os, re, subprocess, sys, tempfile
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import fndiff  # noqa: E402
import nmcheck  # noqa: E402

ROOT = fndiff.ROOT
REPORT = ROOT / "build/GYQE01/report.json"
TRAILER = ("Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>\n"
           "Claude-Session: https://claude.ai/code/session_015niHvxEDkAYvM96H5vnmag")

IF_NM = re.compile(r"^\s*#\s*if\s+NONMATCHING\b")
FN_START = re.compile(r"^[A-Za-z_][^;{}()=#]*?\b(\w+)\s*\([^;{}]*\)\s*\{", re.M)
NOT_FN = {"if", "while", "for", "switch", "return", "sizeof"}

# ------------------------------------------------------------------ source parsing


def brace_end(text: str, i: int) -> int:
    """Index of the `}` closing the `{` at text[i] (skips comments, strings, chars)."""
    depth, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and text.startswith("//", i):
            i = text.find("\n", i)
            if i < 0:
                return -1
        elif c == "/" and text.startswith("/*", i):
            i = text.find("*/", i) + 1
            if i <= 0:
                return -1
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c:
                j += 2 if text[j] == "\\" else 1
            i = j
        elif c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def parse_blocks(lines: list) -> list:
    """Every `#if NONMATCHING` block: dict(start, end, has_else, funcs=[(name, a, b)])
    where start/end are the #if/#endif line indices and [a, b] each function's lines
    (its leading // comment included)."""
    blocks, i = [], 0
    while i < len(lines):
        if not IF_NM.match(lines[i]):
            i += 1
            continue
        depth, j, has_else = 0, i, False
        while j < len(lines):
            s = lines[j].strip()
            if re.match(r"#\s*if", s):
                depth += 1
            elif re.match(r"#\s*endif", s):
                depth -= 1
                if depth == 0:
                    break
            elif re.match(r"#\s*(else|elif)", s) and depth == 1:
                has_else = True
            j += 1
        if j >= len(lines):
            break
        body_lines = lines[i + 1:j]
        text = "\n".join(body_lines)
        offs = [0]
        for l in body_lines:
            offs.append(offs[-1] + len(l) + 1)
        line_of = lambda pos: next(k for k in range(len(offs) - 1) if offs[k + 1] > pos)
        funcs, last = [], -1
        for m in FN_START.finditer(text):
            if m.group(1) in NOT_FN or m.start() <= last:
                continue  # a statement, or inside the previous function
            close = brace_end(text, m.end() - 1)
            if close < 0:
                continue
            last = close
            a = line_of(m.start())
            b = line_of(close)
            while a > 0 and body_lines[a - 1].lstrip().startswith("//"):
                a -= 1
            funcs.append((m.group(1), i + 1 + a, i + 1 + b))
        blocks.append(dict(start=i, end=j, has_else=has_else, funcs=funcs))
        i = j + 1
    return blocks


def has_code(part: list) -> bool:
    return any(l.strip() and not l.lstrip().startswith("//") for l in part)


NM_COMMENT = re.compile(r"^\s*//\s*(NONMATCHING\b|nmverify:)")
KEEP_COMMENT = re.compile(r"^\s*//\s*(\.text:|litcheck:|NONMATCHING\b|nmverify:)")


def drop_nm_comments(lines: list, lo: int, hi: int) -> list:
    """Remove `// NONMATCHING ...` lines (with their // continuation lines) and
    `// nmverify:` lines in lines[lo:hi]."""
    out, k, drop = [], 0, False
    for idx, l in enumerate(lines):
        if lo <= idx < hi:
            if NM_COMMENT.match(l):
                drop = True
                continue
            if drop and l.lstrip().startswith("//") and not KEEP_COMMENT.match(l):
                continue
        drop = False
        out.append(l)
    return out


def promote_lines(lines: list, block: dict, fn: str) -> list:
    """The source with `fn` taken out of its NONMATCHING block (fn=None: the whole
    block unwrapped, for functions that need a helper defined in the same block)."""
    s, e = block["start"], block["end"]
    if fn is None:
        a, b = s + 1, e - 1
    else:
        _, a, b = next(f for f in block["funcs"] if f[0] == fn)
    pre, post = lines[s + 1:a], lines[b + 1:e]
    wrap = lambda part: (["#if NONMATCHING"] + part + ["#endif"]) if has_code(part) else part
    whole = not has_code(pre) and not has_code(post)
    # comment region above the #if (comments / pragmas / blank) belongs to the block
    top = s
    while top > 0 and re.match(r"^\s*(//|#\s*pragma)", lines[top - 1]):
        top -= 1
    head = lines[:s]
    new = head + wrap(pre) + lines[a:b + 1] + wrap(post) + lines[e + 1:]
    fn_lo = len(head) + len(wrap(pre))
    fn_hi = fn_lo + (b + 1 - a)
    if whole:
        return drop_nm_comments(new, top, fn_hi)
    return drop_nm_comments(new, fn_lo, fn_hi)


# ------------------------------------------------------------------ compiling


_CMDS = {}


def compile_cmd(src: str) -> str:
    if src not in _CMDS:
        obj = nmcheck.obj_for(src)
        if not obj:
            return None
        cmd = subprocess.run(["ninja", "-t", "commands", obj], cwd=ROOT,
                             capture_output=True, text=True).stdout.strip().splitlines()[-1]
        _CMDS[src] = cmd.split(" && ")[0].replace(" -MMD", "")
    return _CMDS[src]


_SEQ = [0]


def compile_text(src: str, text: str, workdir: str):
    """Compile `text` as if it were `src` (same directory, so local includes work).
    Returns the object path, or None if it does not compile."""
    cmd = compile_cmd(src)
    if not cmd:
        return None
    _SEQ[0] += 1
    srcp = Path(src)
    tmp_rel = str(srcp.with_name(f"{srcp.stem}.nmtmp{os.getpid()}_{_SEQ[0]}.c"))
    (ROOT / tmp_rel).write_text(text)
    outdir = tempfile.mkdtemp(dir=workdir)
    try:
        c = re.sub(r" -o \S+", f" -o {outdir}", cmd).replace(f" {src} ", f" {tmp_rel} ")
        r = subprocess.run(c, shell=True, cwd=ROOT, capture_output=True, text=True)
    finally:
        (ROOT / tmp_rel).unlink(missing_ok=True)
    objs = list(Path(outdir).glob("*.o"))
    return objs[0] if r.returncode == 0 and objs else None


_TARGETS = {}


def target_asm(unit: dict, workdir: str):
    """(path to target disassembly, literal names) for an objdiff unit."""
    if unit["name"] not in _TARGETS:
        p = Path(workdir) / (unit["name"].replace("/", "_") + ".target.s")
        fndiff.disasm(ROOT / unit["target_path"], p)
        _TARGETS[unit["name"]] = (p, fndiff.literal_names(p))
    return _TARGETS[unit["name"]]


def score_obj(obj: Path, unit: dict, fn: str, workdir: str, others=()) -> int:
    """Differing asm lines for `fn` (0 == match; ours-only global refs count as a
    mismatch). `others`: functions that must stay identical (a change adds 1000)."""
    ts, lits = target_asm(unit, workdir)
    os_ = obj.with_suffix(".s")
    fndiff.disasm(obj, os_)
    t = fndiff.extract(ts, fn, lits)
    o = fndiff.extract(os_, fn, lits)
    if not t or not o:
        return -1
    import difflib
    n = 0
    if t != o:
        ops = difflib.SequenceMatcher(None, t, o, autojunk=False).get_opcodes()
        n = sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in ops if tag != "equal")
    if fndiff.data_refs(os_, fn, lits) - fndiff.data_refs(ts, fn, lits):
        n += 1
    for other in others:
        if fndiff.extract(ts, other, lits) != fndiff.extract(os_, other, lits):
            n += 1000
    return n


# ------------------------------------------------------------------ project data


def units_by_source() -> dict:
    return {u["metadata"].get("source_path"): u
            for u in json.loads((ROOT / "objdiff.json").read_text())["units"]}


def report_pcts() -> dict:
    out = {}
    for u in json.loads(REPORT.read_text())["units"]:
        for f in u.get("functions", []):
            out[(u["name"], f["name"])] = f.get("fuzzy_match_percent", 0.0)
    return out


def nm_sources() -> list:
    return sorted(subprocess.run(["grep", "-rlE", r"^#\s*if\s+NONMATCHING", "src"], cwd=ROOT,
                                 capture_output=True, text=True).stdout.split())


def scan_source(src: str) -> list:
    """[(fn, whole, names, score)] for the functions in NONMATCHING blocks of `src`:
    each function taken out on its own (whole=False), and for blocks with several
    functions the whole block unwrapped (whole=True, fn = its first function; names =
    the functions the target has, which all have to match)."""
    unit = units_by_source().get(src)
    if not unit:
        return []
    pcts = report_pcts()
    matched = [f for (u, f), p in pcts.items() if u == unit["name"] and p == 100.0]
    lines = (ROOT / src).read_text(errors="replace").split("\n")
    out = []
    with tempfile.TemporaryDirectory() as wd:
        for block in parse_blocks(lines):
            if block["has_else"] or not block["funcs"]:
                continue
            ok = []
            for fn, _, _ in block["funcs"]:
                if pcts.get((unit["name"], fn)) == 100.0:
                    continue
                obj = compile_text(src, "\n".join(promote_lines(lines, block, fn)), wd)
                score = -2 if obj is None else score_obj(obj, unit, fn, wd, matched)
                out.append((fn, False, [fn], score))
                ok.append(score == 0)
            if len(block["funcs"]) > 1 and not all(ok):
                obj = compile_text(src, "\n".join(promote_lines(lines, block, None)), wd)
                names, total = [], 0
                ts, lits = target_asm(unit, wd)
                for fn, _, _ in block["funcs"]:
                    if not fndiff.extract(ts, fn, lits):
                        continue  # an inline helper the target does not emit
                    names.append(fn)
                    if obj is None:
                        total = -2
                        break
                    sc = score_obj(obj, unit, fn, wd, matched)
                    total = sc if sc < 0 else total + sc
                    if sc < 0:
                        break
                if names:
                    out.append((block["funcs"][0][0], True, names, total))
        _TARGETS.clear()
    return out


# ------------------------------------------------------------------ promotion


def git(*args, check=True):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, check=check)


def ninja_ok() -> bool:
    return subprocess.run(["ninja"], cwd=ROOT, capture_output=True, text=True).returncode == 0


def promote(src: str, fn: str, whole: bool = False, names=None, commit: bool = True,
            msg: str = None) -> str:
    """Unwrap `fn` (whole: its whole block), verify with a full build that `names`
    (default [fn]) reach 100% and nothing else regresses, commit. Returns 'ok' or why not."""
    names = names or [fn]
    path = ROOT / src
    original = path.read_text()
    lines = original.split("\n")
    block = next((b for b in parse_blocks(lines) if not b["has_else"]
                  and any(f[0] == fn for f in b["funcs"])), None)
    if not block:
        return "not in a NONMATCHING block"
    unit = units_by_source()[src]["name"]
    before = report_pcts()
    path.write_text("\n".join(promote_lines(lines, block, None if whole else fn)))
    why = None
    if not ninja_ok():
        why = "build failed"
    else:
        after = report_pcts()
        low = [f"{n} {after.get((unit, n))}%" for n in names if after.get((unit, n)) != 100.0]
        if low:
            why = "report.json: " + ", ".join(low)
        else:
            lost = [k[1] for k, p in before.items() if p == 100.0 and after.get(k) != 100.0]
            if lost:
                why = f"regresses {lost[:5]}"
            else:
                for n in names:
                    lc = subprocess.run([sys.executable, "tools/litcheck.py", src, "--fn", n], cwd=ROOT,
                                        capture_output=True, text=True)
                    if lc.returncode != 0:
                        why = "litcheck: " + (lc.stdout.strip().splitlines() or ["?"])[0][:200]
                        break
    if why:
        path.write_text(original)
        ninja_ok()
        return why
    if commit:
        git("add", src)
        git("commit", "-q", "-m", f"{msg or 'match'} {', '.join(names)}\n\n{TRAILER}")
    return "ok"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("sources", nargs="*", help="default: every source with a NONMATCHING block")
    ap.add_argument("--promote", action="store_true", help="unwrap, verify and commit every match")
    ap.add_argument("--no-commit", action="store_true", help="with --promote: leave the edits uncommitted")
    ap.add_argument("-j", type=int, default=os.cpu_count(), help="parallel scans")
    ap.add_argument("-v", action="store_true", help="print the score of every function")
    args = ap.parse_args()

    srcs = args.sources or nm_sources()
    if not REPORT.exists():
        sys.exit("run ninja first")
    found = []
    with ProcessPoolExecutor(args.j) as ex:
        for src, res in zip(srcs, ex.map(scan_source, srcs)):
            for fn, whole, names, score in res:
                label = f"{fn} (whole block: {', '.join(names)})" if whole else fn
                if args.v or score == 0:
                    tag = {0: "MATCH", -1: "missing", -2: "does not compile"}.get(score, f"{score} lines")
                    print(f"{src}: {label}: {tag}", flush=True)
                if score == 0 and not any(set(names) & set(f[3]) for f in found):
                    found.append((src, fn, whole, names))
    print(f"{len(found)} candidate(s)")
    if not args.promote:
        return
    done = 0
    for src, fn, whole, names in found:
        r = promote(src, fn, whole, names, commit=not args.no_commit)
        print(f"promote {', '.join(names)}: {r}", flush=True)
        done += r == "ok"
    print(f"{done} promoted")


if __name__ == "__main__":
    main()
