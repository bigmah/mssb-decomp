#!/usr/bin/env python3
"""
Rebuild one unit and diff a single function against the original.

Usage:
    python3 tools/fndiff.py getComponentsFromSAng
    python3 tools/fndiff.py fn_3_9F79C --unit game/game/rep_1838

Prints MATCH (exit 0), or (exit 1) a one-line summary, a diagnosis (stub /
register allocation only / scheduling / which instructions differ), a
target->ours register map, and the first few hunks that differ in more than
register numbers. --full prints every hunk.
"<" lines are the original (target), ">" lines are our build (base).

Local branch labels and anonymous data labels (lbl_N_rodata_X / "@123") are
normalized away since they never line up by name. Named symbols are NOT
normalized, so a symbol-name mismatch shows up as a real diff.
"""

import argparse
import collections
import difflib
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DTK = ROOT / "build" / "tools" / "dtk"
CACHE = ROOT / "build" / "fndiff"

COMMENT_RE = re.compile(r"/\*[^*]*\*/")
LOCAL_LABEL_RE = re.compile(r"\.L_[0-9A-F]+")
ANON_DATA_RE = re.compile(r'lbl_\d+_(?:rodata|data|sdata2?|sbss2?|bss)_[0-9A-F]+|"@\d+"')


def find_unit(fn_name: str) -> str:
    report = ROOT / "build" / "GYQE01" / "report.json"
    if not report.exists():
        sys.exit("build/GYQE01/report.json not found; run ninja first")
    for unit in json.loads(report.read_text())["units"]:
        for fn in unit.get("functions", []):
            if fn["name"] == fn_name:
                return unit["name"]
    sys.exit(f"function {fn_name} not found in report.json")


def load_unit(unit_name: str) -> dict:
    for unit in json.loads((ROOT / "objdiff.json").read_text())["units"]:
        if unit["name"] == unit_name:
            return unit
    sys.exit(f"unit {unit_name} not found in objdiff.json")


def disasm(obj: Path, out: Path) -> None:
    out.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [str(DTK), "elf", "disasm", str(obj), str(out)],
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )


LITERAL_SECTIONS = (".sdata2", ".rodata")


def literal_names(asm: Path) -> set:
    """Names of objects the target defines in its own .sdata2/.rodata (float/string literals)
    and its own switch jump tables.
    Our build emits these as anonymous @NNN, so they are compared as DATA on both sides."""
    names, sec = set(), None
    for line in asm.read_text().splitlines():
        s = line.strip()
        if s.startswith(".section"):
            sec = s.split()[1].rstrip(",")
        elif s in (".text", ".data", ".rodata", ".bss", ".sdata", ".sbss", ".sdata2", ".sbss2"):
            sec = s
        elif s.startswith(".obj "):
            name = s.split()[1].rstrip(",").strip('"')
            if sec in LITERAL_SECTIONS or (sec == ".data" and name.startswith("jumptable_")):
                names.add(name)
    return names


def extract(asm: Path, fn_name: str, literals: set = frozenset()) -> list:
    lit_re = re.compile(r"\b(?:" + "|".join(map(re.escape, sorted(literals))) + r")\b") if literals else None
    lines = []
    inside = False
    for line in asm.read_text().splitlines():
        if line.startswith(f".fn {fn_name},"):
            inside = True
        if inside:
            line = COMMENT_RE.sub("", line)
            line = LOCAL_LABEL_RE.sub("L", line)
            line = ANON_DATA_RE.sub("DATA", line)
            if lit_re:
                line = lit_re.sub("DATA", line)
            lines.append(line.rstrip())
            if line.startswith(f".endfn {fn_name}"):
                break
    return lines


def diff_fn(fn_name: str, unit_name: str, quiet: bool = False, full: bool = False, max_hunks: int = 5) -> int:
    """Returns the number of differing lines (0 == match)."""
    unit = load_unit(unit_name)
    target = ROOT / unit["target_path"]
    base = ROOT / unit["base_path"]

    build = subprocess.run(
        ["ninja", unit["target_path"], unit["base_path"]],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if build.returncode != 0:
        if not quiet:
            print(build.stdout[-3000:])
        return -1

    tag = unit_name.replace("/", "_")
    target_s = CACHE / f"{tag}.target.s"
    base_s = CACHE / f"{tag}.base.s"
    if not target_s.exists() or target_s.stat().st_mtime < target.stat().st_mtime:
        disasm(target, target_s)
    disasm(base, base_s)

    literals = literal_names(target_s)
    t = extract(target_s, fn_name, literals)
    b = extract(base_s, fn_name, literals)
    if not t:
        sys.exit(f"{fn_name} not found in target object {target}")
    if not b:
        if not quiet:
            print(f"{fn_name} not found in our build of {base}")
        return -1
    if t == b:
        if not quiet:
            print("MATCH")
        return 0

    ops = difflib.SequenceMatcher(None, t, b, autojunk=False).get_opcodes()
    if not quiet:
        print("\n".join(render(t, b, ops, full, max_hunks)))
    return sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in ops if tag != "equal")


REG_RE = re.compile(r"\b([rf])([0-9]|[12][0-9]|3[01])\b")


def norm_regs(lines: list) -> list:
    return [REG_RE.sub(r"\1N", l) for l in lines]


def is_insn(line: str) -> bool:
    return line.startswith("\t")


def render(t: list, b: list, ops: list, full: bool, max_hunks: int) -> list:
    """Summary line, diagnosis, then hunks. Register-only hunks are folded
    into a register map unless `full`."""
    changed = [o for o in ops if o[0] != "equal"]
    regonly = [
        o for o in changed
        if o[0] == "replace" and o[2] - o[1] == o[4] - o[3]
        and norm_regs(t[o[1]:o[2]]) == norm_regs(b[o[3]:o[4]])
    ]
    structural = [o for o in changed if o not in regonly]
    nt = sum(map(is_insn, t))
    nb = sum(map(is_insn, b))
    out = [f"DIFF: target {nt} insns, ours {nb}; {len(changed)} hunks "
           f"({len(structural)} structural, {len(regonly)} register-only)"]

    if nb <= 3 and nt > 3:
        out.append("diagnosis: ours is a stub")
        return out
    if not structural:
        out.append("diagnosis: registers only (allocation or operand order)")
    elif norm_regs(sorted(t)) == norm_regs(sorted(b)) or sorted(norm_regs(t)) == sorted(norm_regs(b)):
        out.append("diagnosis: same instructions, different order (scheduling)")
    else:
        opc = lambda ls: collections.Counter(l.split()[0] for l in ls if is_insn(l))
        missing = opc(t) - opc(b)
        extra = opc(b) - opc(t)
        fmt = lambda c: ", ".join(f"{k} x{v}" for k, v in c.most_common(6)) or "-"
        out.append(f"diagnosis: instructions differ; ours lacks [{fmt(missing)}], has extra [{fmt(extra)}]")

    if regonly:
        pairs = collections.Counter()
        for _, i1, i2, j1, j2 in regonly:
            for lt, lb in zip(t[i1:i2], b[j1:j2]):
                for rt, rb in zip(REG_RE.findall(lt), REG_RE.findall(lb)):
                    if rt != rb:
                        pairs["".join(rt) + "->" + "".join(rb)] += 1
        out.append("register map (target->ours): " + ", ".join(f"{k} x{v}" for k, v in pairs.most_common(8)))

    # Small diffs: show everything (an operand swap looks "register-only").
    shown = changed if full or len(changed) <= max_hunks or not structural else structural
    limit = len(shown) if full else max_hunks
    for tag, i1, i2, j1, j2 in shown[:limit]:
        out.append("@@")
        if i1 > 0:
            out.append(" " + t[i1 - 1])
        out.extend("<" + l for l in t[i1:i2])
        out.extend(">" + l for l in b[j1:j2])
        if i2 < len(t):
            out.append(" " + t[i2])
    if len(shown) > limit:
        out.append(f"... {len(shown) - limit} more structural hunks (--full shows everything)")
    elif regonly and shown is structural:
        out.append(f"({len(regonly)} register-only hunks hidden; --full shows them)")
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("function", help="function symbol name")
    parser.add_argument("--unit", help="objdiff unit name (default: look up in report.json)")
    parser.add_argument("--full", action="store_true", help="print every hunk, including register-only ones")
    parser.add_argument("--hunks", type=int, default=5, help="structural hunks to print (default 5)")
    args = parser.parse_args()

    unit = args.unit or find_unit(args.function)
    n = diff_fn(args.function, unit, full=args.full, max_hunks=args.hunks)
    sys.exit(0 if n == 0 else 1)


if __name__ == "__main__":
    main()
