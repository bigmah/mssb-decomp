#!/usr/bin/env python3
"""Check the switch jump tables each function uses against the original's.

objdiff/report.json and fndiff do not compare jump-table contents: a switch that lost a
`case` label (that entry now jumps to `default`) compiles to the same instructions and
counts as 100% matched. This tool finds every jump table a function addresses (a
.text relocation to a .data/.rodata object whose words are relocations back into the
function; the target's table may live in another unit's .data object), maps each entry
to an offset inside the function, and compares:
  - matched functions (100% in report.json): the exact sequence of entry offsets, table
    by table;
  - other functions (equivalent C, compiled with -DNONMATCHING=1 as nmverify does, or
    partial C): the case structure: number of tables, entries per table, and which
    entries share a target (offsets differ, so entries are renamed by first use:
    [a, b, b, a, c] -> 0 1 1 0 2).
Stubs (ours has no table and is less than half the target's size) are skipped.

Reviewed by hand: a `// jtcheck: <why>` line in the comment block above the function
waives its differences (-v lists them).

    python3 tools/jtcheck.py src/menus/auto_00_00001254_text.c [...]
    python3 tools/jtcheck.py --all [-v] [--fn NAME]
Exit status 1 when something is flagged.
"""
import argparse, contextlib, io, json, re, struct, sys, tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import nmcheck  # noqa: E402
from litcheck import Elf, nm_functions  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
DATA_SECTIONS = (".data", ".rodata", ".sdata", ".sdata2")
_EXT = None


def target_data():
    """name -> (Elf, symbol) for every data symbol the target objects define: a function's
    table can live in another unit's .data object."""
    global _EXT
    if _EXT is None:
        _EXT = {}
        for u in json.loads((ROOT / "objdiff.json").read_text())["units"]:
            p = ROOT / u["target_path"]
            if not p.exists():
                continue
            e = Elf(p)
            for nm, sym in e.defined().items():
                if e.secs[sym["shndx"]]["name"] in DATA_SECTIONS and sym["bind"] != 0:
                    _EXT.setdefault(nm, (e, sym))
    return _EXT


def text_target(elf, sym, add):
    """(function name, offset) a relocation into .text points at."""
    if sym["shndx"] == 0 or sym["shndx"] >= len(elf.secs):
        return (sym["name"], add)
    a = sym["value"] + add
    for nm, (idx, st, sz) in elf.functions().items():
        if idx == sym["shndx"] and st <= a < st + sz:
            return (nm, a - st)
    return (sym["name"] or "?", add)


def table_entries(elf, idx, addr, size):
    """[(function, offset)] of the words of the table at addr; None if it is not a table."""
    if not elf.secs[idx]["name"].startswith(DATA_SECTIONS):
        return None
    if not hasattr(elf, "_relmap"):
        elf._relmap = {}
    rm = elf._relmap.get(idx)
    if rm is None:
        rm = elf._relmap[idx] = {o: (t, si, a) for o, t, si, a in elf.relas.get(idx, [])}
    if not size:  # unsized: up to the next symbol in the section
        nxt = [s["value"] for s in elf.syms if s["shndx"] == idx and s["value"] > addr]
        size = (min(nxt) if nxt else elf.secs[idx]["size"]) - addr
    out = []
    for o in range(addr, addr + size, 4):
        r = rm.get(o)
        if not r or r[0] != 1:  # ADDR32
            break
        s = elf.syms[r[1]]
        if not (s["shndx"] == 0 or (s["shndx"] < len(elf.secs) and elf.secs[s["shndx"]]["name"].startswith(".text"))):
            break
        out.append(text_target(elf, s, r[2]))
    return out or None


def fn_tables(elf, fname, ext):
    """Jump tables fname addresses, in order of first reference: [[offset, ...], ...]
    (an entry into another function is kept as 'name+0xOFF')."""
    idx, start, size = elf.functions()[fname]
    seen, tables = set(), []
    for off, rtype, si, add in sorted(elf.relas.get(idx, [])):
        if not (start <= off < start + size) or rtype not in (4, 109):
            continue
        src, sym = elf, elf.syms[si]
        if sym["shndx"] == 0:
            if sym["name"] not in ext:
                continue
            src, sym = ext[sym["name"]]
        if sym["shndx"] >= len(src.secs):
            continue
        a = sym["value"] + add
        key = (id(src), sym["shndx"], a)
        if key in seen:
            continue
        seen.add(key)
        ent = table_entries(src, sym["shndx"], a, sym["size"] if add == 0 else 0)
        if not ent or not any(f == fname for f, _ in ent):
            continue
        tables.append([o if f == fname else f"{f}+0x{o:X}" for f, o in ent])
    return tables


def pattern(t):
    ids = {}
    return [ids.setdefault(x, len(ids)) for x in t]


def show(t):
    return "[" + " ".join(f"{x:X}" if isinstance(x, int) else x for x in t) + "]"


def reviewed(src_text, fn):
    lines = src_text.splitlines()
    for i, l in enumerate(lines):
        if re.match(rf"^[A-Za-z_][^;(]*\b{re.escape(fn)}\s*\(", l) and not l.rstrip().endswith(";"):
            notes, j = [], i - 1
            while j >= 0 and re.match(r"^\s*(//|#if|$)", lines[j]):
                m = re.search(r"jtcheck:(.*)", lines[j])
                if m:
                    notes.append(m.group(1).strip())
                j -= 1
            return " ".join(notes) if notes else None
    return None


def compare(tt, ot, matched):
    """Problems between the target's tables tt and ours ot."""
    if matched:
        if tt == ot:
            return []
        out = []
        if len(tt) != len(ot):
            return [f"{len(tt)} table(s) in target, {len(ot)} in ours"]
        for i, (a, b) in enumerate(zip(tt, ot)):
            if a != b:
                bad = [f"[{k}] {x:X}->{y:X}" if isinstance(x, int) and isinstance(y, int) else f"[{k}] {x}->{y}"
                       for k, (x, y) in enumerate(zip(a, b)) if x != y]
                if len(a) != len(b):
                    bad.append(f"{len(a)} entries in target, {len(b)} in ours")
                out.append(f"table {i}: " + ", ".join(bad))
        return out
    tp, op = [pattern(t) for t in tt], [pattern(t) for t in ot]
    if tp == op or sorted(tp) == sorted(op):
        return []
    if len(tt) != len(ot):
        return [f"{len(tt)} table(s) in target {[len(t) for t in tt]}, {len(ot)} in ours {[len(t) for t in ot]}"]
    out = []
    for i, (a, b) in enumerate(zip(tp, op)):
        if a != b:
            if len(a) != len(b):
                out.append(f"table {i}: {len(a)} cases in target, {len(b)} in ours")
            else:
                out.append(f"table {i}: shared targets differ: target {' '.join(map(str, a))}"
                           f" / ours {' '.join(map(str, b))}")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("sources", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--fn", help="only this function")
    ap.add_argument("-v", "--verbose", action="store_true", help="also list waived differences and tables")
    args = ap.parse_args()

    units = [u for u in json.loads((ROOT / "objdiff.json").read_text())["units"]
             if u.get("base_path") and u["metadata"].get("source_path")]
    report = {u["name"]: {f["name"]: f.get("fuzzy_match_percent", 0) for f in u.get("functions", [])}
              for u in json.loads((ROOT / "build/GYQE01/report.json").read_text())["units"]}
    if args.fn and not args.sources and not args.all:
        unit = next((n for n, fs in report.items() if args.fn in fs), None)
        if not unit:
            sys.exit(f"{args.fn} not in report.json")
        args.sources = [next(u["metadata"]["source_path"] for u in units if u["name"] == unit)]
    if not args.all:
        want = {str(Path(s).resolve().relative_to(ROOT)) if Path(s).is_absolute() else s for s in args.sources}
        units = [u for u in units if u["metadata"]["source_path"] in want]
    ext = target_data()
    flagged = checked = 0
    for u in units:
        src = u["metadata"]["source_path"]
        src_text = (ROOT / src).read_text(errors="replace")
        tpath = ROOT / u["target_path"]
        if not tpath.exists():
            continue
        tgt = Elf(tpath)
        nm = nm_functions(src_text) if re.search(r"^#if\s+NONMATCHING", src_text, re.M) else set()
        # matched functions from the normal build (a -DNONMATCHING=1 compile can change them:
        # an equivalent helper inlined into them), equivalent ones from a NONMATCHING compile
        bpath = ROOT / u["base_path"]
        base = Elf(bpath) if bpath.exists() else None
        nmo = None
        if nm:
            with tempfile.TemporaryDirectory() as d:
                with contextlib.redirect_stdout(io.StringIO()) as out:
                    ok = nmcheck.check(src, d + "/nm.o")
                if not ok:
                    print(out.getvalue().strip()); flagged += 1; continue
                nmo = Elf(d + "/nm.o")
        if base is None and nmo is None:
            continue
        tf = tgt.functions()
        for fname in tf:
            ours = nmo if (fname in nm or base is None) else base
            of = ours.functions()
            if fname not in of or (args.fn and fname != args.fn):
                continue
            if not tgt.secs[tf[fname][0]]["name"].startswith(".text"):
                continue
            tt = fn_tables(tgt, fname, ext)
            ot = fn_tables(ours, fname, {})
            if not tt and not ot:
                continue
            if not ot and of[fname][2] * 2 < tf[fname][2]:
                continue  # stub
            pct = report.get(u["name"], {}).get(fname)
            matched = pct == 100 and fname not in nm
            checked += 1
            if args.verbose:
                for t in tt:
                    print(f"{src}: {fname}: target {show(t)}")
                for t in ot:
                    print(f"{src}: {fname}: ours   {show(t)}")
            probs = compare(tt, ot, matched)
            if not probs:
                continue
            kind = "equivalent" if fname in nm else ("matched" if matched else f"{pct or 0:.0f}%")
            note = reviewed(src_text, fname)
            if note is not None:
                if args.verbose:
                    print(f"{src}: {fname} ({kind}): waived (jtcheck: {note}): " + "; ".join(probs))
                continue
            flagged += 1
            print(f"{src}: {fname} ({kind}): " + "; ".join(probs))
    print(f"{checked} function(s) with jump tables checked, {flagged} flagged")
    sys.exit(1 if flagged else 0)


if __name__ == "__main__":
    main()
