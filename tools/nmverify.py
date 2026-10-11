#!/usr/bin/env python3
"""Sanity-check equivalent (`#if NONMATCHING`) functions against the original.

Compiles each source with -DNONMATCHING=1, disassembles it, and for every
function that is unmatched in report.json compares with the target object:
  - calls (`bl` targets, as a multiset)
  - references to lbl_N_{data,bss,...} globals that only our side makes
  - instruction-level similarity (registers normalised)
  - calls to functions that exist nowhere (made-up names; the port would not link)
Equivalent C should make the same calls and touch the same globals; a
mismatch there is far more likely a bug than a compiler difference.

Accepted automatically (-v lists them):
  - helpers from the same source inlined on one side only: their calls are
    expanded (recursively); a target-only helper counts only if our C calls it
  - ours-only globals the original reaches through a pooled base (lbl@l + offset,
    tracked through addi/addis/subi/mr/add) or that lie inside an object it references
  - globals of a helper inlined on one side
Reviewed by hand: when the checks above still fail, names on a `// nmverify: ...`
line in the comment block above the function are left out of the comparison
(e.g. a call site the original duplicated per branch). Say why on that line.

    python3 tools/nmverify.py src/game/rep_3C28.c [...]
    python3 tools/nmverify.py --all [--min-sim 0.5] [-v] [--seq]
"""
import argparse, collections, difflib, json, re, subprocess, sys, tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import fndiff  # noqa: E402
import nmcheck  # noqa: E402

ROOT = fndiff.ROOT
CALL_RE = re.compile(r"^\s+bl\s+(\S+)", re.M)


def fn_body(asm_text: str, name: str) -> str:
    m = re.search(rf"^\.fn {re.escape(name)},.*?^\.endfn {re.escape(name)}$", asm_text, re.M | re.S)
    return m.group(0) if m else ""


def calls(body: str) -> collections.Counter:
    body = fndiff.COMMENT_RE.sub("", body)
    return collections.Counter(c for c in CALL_RE.findall(body) if not c.startswith(".L"))


def c_functions(src_text: str) -> dict:
    """name -> C text of every function definition in a source file (rough brace matching)."""
    out = {}
    for m in re.finditer(r"^[A-Za-z_][^;{}()]*?\b(\w+)\s*\([^;{}]*\)\s*\{", src_text, re.M):
        depth, i = 0, m.end() - 1
        while i < len(src_text):
            if src_text[i] == "{":
                depth += 1
            elif src_text[i] == "}":
                depth -= 1
                if depth == 0:
                    break
            i += 1
        out.setdefault(m.group(1), src_text[m.start():i + 1])
    return out


def c_mentions(cfns: dict, fn: str, callee: str, depth: int = 4) -> bool:
    """Does `fn`'s C (or a helper it calls that is defined in the same file) call `callee`?"""
    seen, todo = set(), [fn]
    for _ in range(depth):
        nxt = []
        for f in todo:
            if f in seen or f not in cfns:
                continue
            seen.add(f)
            text = cfns[f]
            if re.search(rf"\b{re.escape(callee)}\s*\)?\s*\(", text):
                return True
            nxt += [n for n in re.findall(r"\b(\w+)\s*\(", text) if n in cfns]
        todo = nxt
    return False


def reviewed_names(src_text: str, fn: str) -> set:
    """Names listed on `// ... nmverify: ...` lines in the comment block above `fn`'s
    definition: differences in those calls/globals were checked by hand (e.g. a call site the
    original duplicated, or a helper from another file that the original inlined)."""
    lines = src_text.splitlines()
    for i, l in enumerate(lines):
        if re.match(rf"^[A-Za-z_][^;(]*\b{re.escape(fn)}\s*\(", l) and not l.rstrip().endswith(";"):
            names, j = set(), i - 1
            while j >= 0 and re.match(r"^\s*(//|#if|$)", lines[j]):
                m = re.search(r"nmverify:(.*)", lines[j])
                if m:
                    names |= set(re.findall(r"\b[A-Za-z_]\w*\b", m.group(1)))
                j -= 1
            return names
    return set()


def expand_inlined(tc: collections.Counter, oc: collections.Counter, ours: str, self_name: str,
                   cfns: dict, depth: int = 4):
    """Account for helpers inlined on one side only, replacing each one-sided call by the
    helper's own calls (recursively):
      - ours-only: the original inlined a helper our C calls (defined in the same source);
      - target-only: our compiler inlined a helper the original calls, which only counts when
        our C really calls it.
    Both use the helper as compiled from our source.
    Returns (whether that explains the difference, helpers expanded)."""
    tc, oc, used = collections.Counter(tc), collections.Counter(oc), []
    slack = {id(tc): collections.Counter(), id(oc): collections.Counter()}

    def expand(side, other, ok):
        changed = False
        for callee, n in list((side - other).items()):
            if callee == self_name or not ok(callee):
                continue
            body = fn_body(ours, callee)
            if not body:
                continue
            side[callee] -= n
            for c, k in calls(body).items():
                side[c] += k * n
                slack[id(side)][c] += k * n
            used.append(callee); changed = True
        return changed

    for _ in range(depth):
        a = expand(oc, tc, lambda c: bool(fn_body(ours, c)))
        b = expand(tc, oc, lambda c: bool(fn_body(ours, c)) and c_mentions(cfns, self_name, c))
        tc.update({}); oc.update({})
        for k in [k for k, v in tc.items() if v <= 0]: del tc[k]
        for k in [k for k, v in oc.items() if v <= 0]: del oc[k]
        if not (a or b):
            break
    # an inlined copy has constant arguments folded, so it may keep only some of the
    # helper's calls: leftovers that came from expanded helper bodies are fine
    ok = not ((tc - oc) - slack[id(tc)]) and not ((oc - tc) - slack[id(oc)])
    return ok, used


SYM_RE = re.compile(r"^(\S+) = \.(\w+):0x([0-9A-Fa-f]+);([^\n]*)", re.M)
SIZE_RE = re.compile(r"size:0x([0-9A-Fa-f]+)")
_SYMS = None


def symbols() -> dict:
    """name -> (section, address, size) from every config/GYQE01/**/symbols.txt."""
    global _SYMS
    if _SYMS is None:
        _SYMS = {}
        for f in (ROOT / "config/GYQE01").rglob("symbols.txt"):
            for m in SYM_RE.finditer(f.read_text()):
                sz = SIZE_RE.search(m.group(4))
                _SYMS[m.group(1)] = (m.group(2), int(m.group(3), 16), int(sz.group(1), 16) if sz else 0)
    return _SYMS


def sym_info(name: str):
    """(section, address, size) from symbols.txt, else from the lbl_N_sec_ADDR name (size 1)."""
    if name in symbols():
        return symbols()[name]
    m = re.match(r"lbl_\d+_([a-z0-9]+)_([0-9A-F]+)$", name)
    return (m.group(1), int(m.group(2), 16), 1) if m else None


def module_section(name: str):
    m = re.match(r"lbl_(\d+)_([a-z0-9]+)_", name)
    return m.groups() if m else None


INSN_RE = re.compile(r"^\s+([a-z.]+)\s+(.*)$")
IMM = r"(-?(?:0x[0-9a-fA-F]+|\d+))"


def reached_addresses(body: str) -> set:
    """(name-of-base, offset) pairs the function reaches through a base register: a
    flow-insensitive pass (run twice, for bases set up late in a loop) over `addi rD, rS, lbl@l` bases,
    `addi`/`addis`/`subi` offsets, `mr`/`add` copies and `imm(rS)` memory operands."""
    regs = {}  # reg -> {(base, off)}
    hits = set()
    body = fndiff.COMMENT_RE.sub("", body)
    cap = lambda vals: dict.fromkeys(list(vals)[:64])  # ordered: keeps the earliest (setup) values
    for _ in range(2):
        for line in body.splitlines():
            m = INSN_RE.match(line)
            if not m:
                continue
            op, args = m.group(1), [a.strip() for a in m.group(2).split(",")]
            if op == "subi" and len(args) == 3 and re.fullmatch(IMM, args[2]):
                op, args[2] = "addi", str(-int(args[2], 0))
            new = None
            if op in ("addi", "addis") and len(args) == 3:
                lm = re.match(r"(\w+)@l$", args[2])
                if op == "addi" and lm and fndiff.DATA_REF_RE.fullmatch(lm.group(1)):
                    new = [(lm.group(1), 0)]
                elif re.fullmatch(IMM, args[2]) and args[1] in regs:
                    v = int(args[2], 0) << (16 if op == "addis" else 0)
                    new = [(b, o + v) for b, o in regs[args[1]]]
            elif op in ("mr", "add") and len(args) >= 2:
                new = [v for r in args[1:] if r in regs for v in regs[r]] or None
            else:
                for a in args:
                    mm = re.fullmatch(IMM + r"\((r\d+)\)", a)
                    if mm and mm.group(2) in regs:
                        v = int(mm.group(1), 0)
                        hits |= {(b, o + v) for b, o in regs[mm.group(2)]}
            if new is not None:
                # accumulate (flow-insensitive: switch arms are seen one after another, and a
                # base set up before the switch stays live in every arm), but keep the sets
                # small: a loop's `addi rN, rN, k` would otherwise double them every pass
                regs[args[0]] = cap({**regs.get(args[0], {}), **dict.fromkeys(new)}); hits |= set(new)
    return hits


def pooled_ok(ref: str, target_refs: set, hits: set) -> bool:
    """An ours-only global is fine if it lies inside an object the target references, or the
    target reaches it through a base register (pooled data: lbl_X@l + offset)."""
    info = sym_info(ref)
    if not info:
        return False
    sec, addr, size = info
    ms = module_section(ref)
    for t in target_refs:
        ti = sym_info(t)
        if ti and module_section(t) == ms and ti[1] <= addr < ti[1] + max(ti[2], 1):
            return True
    for base, off in hits:
        bi = sym_info(base)
        if bi and module_section(base) == ms and addr <= bi[1] + off < addr + max(size, 1):
            return True
    return False


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("sources", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("-v", "--verbose", action="store_true", help="also list differences that were accepted")
    ap.add_argument("--seq", action="store_true", help="print a diff of the call sequences of flagged functions")
    ap.add_argument("--min-sim", type=float, default=0.0, help="also flag functions below this similarity")
    args = ap.parse_args()

    units = {u["metadata"].get("source_path"): u for u in json.loads((ROOT / "objdiff.json").read_text())["units"]}
    report = {u["name"]: u for u in json.loads((ROOT / "build/GYQE01/report.json").read_text())["units"]}
    srcs = args.sources
    if args.all:
        srcs = sorted(subprocess.run(["grep", "-rlE", r"^#if\s+NONMATCHING", "src"], cwd=ROOT,
                                     capture_output=True, text=True).stdout.split())
    flagged = 0
    for src in srcs:
        unit = units.get(src)
        if not unit:
            print(f"{src}: no objdiff unit"); continue
        unmatched = [f["name"] for f in report.get(unit["name"], {}).get("functions", [])
                     if f.get("fuzzy_match_percent") != 100.0]
        if not unmatched:
            continue
        with tempfile.TemporaryDirectory() as d:
            if not nmcheck.check(src, d):
                flagged += 1; continue
            objs = list(Path(d).glob("*.o"))
            if not objs:
                print(f"{src}: no object produced"); continue
            ours_s = Path(d) / "ours.s"
            fndiff.disasm(objs[0], ours_s)
            ours = ours_s.read_text()
        target_s = Path(d).parent / f"nmverify_{unit['name'].replace('/', '_')}.target.s"
        fndiff.disasm(ROOT / unit["target_path"], target_s)
        target = target_s.read_text()
        literals = fndiff.literal_names(target_s)
        src_text = (ROOT / src).read_text(errors="replace")
        cfns = c_functions(src_text)
        for name in unmatched:
            tb, ob = fn_body(target, name), fn_body(ours, name)
            if not ob:
                print(f"{src}: {name}: NO C (missing from NONMATCHING build)"); flagged += 1; continue
            problems = []
            tc, oc = calls(tb), calls(ob)
            # a callee that exists nowhere (not in our object, not in any symbols.txt) is a
            # typo or a made-up name: the port would fail to link
            undefined = sorted(c for c in oc if c not in symbols() and not fn_body(ours, c))
            if undefined:
                problems.append(f"calls undefined {undefined}")
            reviewed = reviewed_names(src_text, name)
            waived = set()
            used = []
            if tc != oc:
                # the original inlined helpers our C calls: expand those and compare again
                ok, used = expand_inlined(tc, oc, ours, name, cfns)
                if not ok and reviewed & (set(tc) | set(oc)):
                    # last resort: leave out the calls a `nmverify:` note explains
                    waived = reviewed & (set(tc) | set(oc))
                    tc = collections.Counter({k: v for k, v in tc.items() if k not in waived})
                    oc = collections.Counter({k: v for k, v in oc.items() if k not in waived})
                    ok, used = (True, []) if tc == oc else expand_inlined(tc, oc, ours, name, cfns)
                if not ok:
                    miss = sorted((tc - oc).elements()); extra = sorted((oc - tc).elements())
                    problems.append(f"calls differ (target-only {miss}, ours-only {extra})")
                    if args.seq:
                        strip = lambda b: [c for c in CALL_RE.findall(fndiff.COMMENT_RE.sub("", b)) if not c.startswith(".L")]
                        for l in difflib.unified_diff(strip(tb), strip(ob), "target", "ours", n=2, lineterm=""):
                            print("    " + l)
                elif args.verbose:
                    print(f"{src}: {name}: ok, helpers inlined on one side: {used}")
            tr = set(fndiff.DATA_REF_RE.findall(tb)); orf = fndiff.DATA_REF_RE.findall(ob)
            # globals of a helper inlined on one side show up on that side only
            helper_refs = {r for h in set(used) for r in fndiff.DATA_REF_RE.findall(fn_body(ours, h))}
            extra_refs = sorted(set(orf) - tr - literals - helper_refs)
            if extra_refs:
                hits = reached_addresses(tb)
                pooled = [r for r in extra_refs if pooled_ok(r, tr, hits)]
                extra_refs = [r for r in extra_refs if r not in pooled]
                if pooled and args.verbose:
                    print(f"{src}: {name}: ok, reached via pooled base in original: {pooled}")
            if extra_refs and reviewed & set(extra_refs):
                waived |= reviewed & set(extra_refs)
                extra_refs = [r for r in extra_refs if r not in reviewed]
            if extra_refs:
                problems.append(f"ours-only globals {extra_refs}")
            tl = [fndiff.REG_RE.sub(r"\1N", l) for l in fndiff.extract(target_s, name, literals)]
            ol_path = Path(tempfile.gettempdir()) / "nmverify_ours.s"
            ol_path.write_text(ours)
            ol = [fndiff.REG_RE.sub(r"\1N", l) for l in fndiff.extract(ol_path, name, literals)]
            sim = difflib.SequenceMatcher(None, tl, ol, autojunk=False).ratio()
            if sim < args.min_sim:
                problems.append(f"similarity {sim:.0%}")
            if waived and args.verbose:
                print(f"{src}: {name}: reviewed by hand (nmverify: note): {sorted(waived)}")
            if problems:
                flagged += 1
                print(f"{src}: {name} ({sim:.0%}): " + "; ".join(problems))
    print(f"{flagged} function(s) flagged")


if __name__ == "__main__":
    main()
