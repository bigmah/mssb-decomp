#!/usr/bin/env python3
"""
Rebuild one unit and diff a single function against the original.

Usage:
    python3 tools/fndiff.py getComponentsFromSAng
    python3 tools/fndiff.py fn_3_9F79C --unit game/game/rep_1838

Prints MATCH (exit 0) or a unified-style diff of the disassembly (exit 1).
"<" lines are the original (target), ">" lines are our build (base).

Local branch labels and anonymous data labels (lbl_N_rodata_X / "@123") are
normalized away since they never line up by name. Named symbols are NOT
normalized, so a symbol-name mismatch shows up as a real diff.
"""

import argparse
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


def extract(asm: Path, fn_name: str) -> list:
    lines = []
    inside = False
    for line in asm.read_text().splitlines():
        if line.startswith(f".fn {fn_name},"):
            inside = True
        if inside:
            line = COMMENT_RE.sub("", line)
            line = LOCAL_LABEL_RE.sub("L", line)
            line = ANON_DATA_RE.sub("DATA", line)
            lines.append(line.rstrip())
            if line.startswith(f".endfn {fn_name}"):
                break
    return lines


def diff_fn(fn_name: str, unit_name: str, quiet: bool = False) -> int:
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

    t = extract(target_s, fn_name)
    b = extract(base_s, fn_name)
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

    import difflib

    diff = [
        l
        for l in difflib.unified_diff(t, b, "target", "base", n=1, lineterm="")
    ]
    if not quiet:
        for l in diff:
            if l.startswith("-") and not l.startswith("---"):
                print("<" + l[1:])
            elif l.startswith("+") and not l.startswith("+++"):
                print(">" + l[1:])
            elif l.startswith("@@"):
                print("@@")
            elif not l.startswith(("---", "+++")):
                print(" " + l[1:])
    return sum(
        1
        for l in diff
        if l[:1] in "+-" and not l.startswith(("---", "+++"))
    )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("function", help="function symbol name")
    parser.add_argument("--unit", help="objdiff unit name (default: look up in report.json)")
    args = parser.parse_args()

    unit = args.unit or find_unit(args.function)
    n = diff_fn(args.function, unit)
    sys.exit(0 if n == 0 else 1)


if __name__ == "__main__":
    main()
