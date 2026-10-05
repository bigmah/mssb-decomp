#!/usr/bin/env python3
"""
Everything needed to start on one function, in one command.

Usage:
    python3 tools/fnstart.py fn_3_147C00
    python3 tools/fnstart.py fn_3_147C00 --no-asm     # skip the raw assembly

Prints:
  1. where the function lives (unit, source file + line, size, current match %)
  2. the original assembly
  3. an m2c draft decompilation, using the unit's headers as context
  4. the current diff against our build (if the unit has a source file)

The m2c draft is a starting point, not an answer: rename its temps, replace
`?` types and `unkXX` fields with real struct members, then iterate with
tools/fndiff.py until it matches.
"""

import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from fndiff import ROOT, diff_fn, extract, find_unit, load_unit  # noqa: E402

M2C = ROOT / ".venv" / "bin" / "m2c"
CACHE = ROOT / "build" / "fnstart"
DEFAULT_INCLUDES = [
    '#include "header_rep_data.h"',
    '#include "game/UnknownHomes_Game.h"',
    '#include "static/UnknownHomes_Static.h"',
]


def report_entry(fn_name: str):
    report = json.loads((ROOT / "build" / "GYQE01" / "report.json").read_text())
    for unit in report["units"]:
        for fn in unit.get("functions", []):
            if fn["name"] == fn_name:
                return unit, fn
    return None, None


def build_context(unit: dict) -> Path:
    """Preprocess just the unit's #include lines into a C file m2c can parse."""
    src_path = unit["metadata"].get("source_path")
    includes = DEFAULT_INCLUDES
    if src_path and (ROOT / src_path).exists():
        found = [l for l in (ROOT / src_path).read_text().splitlines() if l.startswith("#include")]
        if found:
            includes = found

    CACHE.mkdir(parents=True, exist_ok=True)
    tag = unit["name"].replace("/", "_")
    inc = CACHE / f"{tag}.inc.c"
    ctx = CACHE / f"{tag}.ctx.c"
    inc.write_text("\n".join(includes) + "\n")
    subprocess.run(
        [
            "clang", "-E", "-P", "-w", "-x", "c", "-nostdinc",
            "-I", str(ROOT / "include"), "-I", str(ROOT / "include" / "stl"),
            "-DM2C", "-D__declspec(x)=", "-D__attribute__(x)=",
            str(inc), "-o", str(ctx),
        ],
        check=True,
    )
    return ctx


def source_location(src: Path, fn_name: str):
    if not src.exists():
        return None
    for i, line in enumerate(src.read_text().splitlines(), 1):
        if re.match(rf"^[^\s/#].*\b{re.escape(fn_name)}\s*\(", line) and not line.rstrip().endswith(";"):
            return i
    return None


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("function")
    parser.add_argument("--no-asm", action="store_true", help="don't print the original assembly")
    args = parser.parse_args()
    fn_name = args.function

    unit_name = find_unit(fn_name)
    unit = load_unit(unit_name)
    _, fn = report_entry(fn_name)
    target = ROOT / unit["target_path"]
    asm = Path(str(target).replace("/obj/", "/asm/")).with_suffix(".s")
    src_path = unit["metadata"].get("source_path")

    print("=" * 72)
    print(f"function : {fn_name}")
    print(f"unit     : {unit_name}")
    print(f"size     : {int(fn.get('size', 0))} bytes   match: {fn.get('fuzzy_match_percent', 0):.1f}%")
    if src_path:
        line = source_location(ROOT / src_path, fn_name)
        where = f"{src_path}:{line}" if line else f"{src_path} (function not present yet)"
        print(f"source   : {where}")
    else:
        print("source   : NONE - this unit has no source file yet. It needs a split/source file")
        print("           before it can be compiled (see docs/splits.md and plan.md Phase 3/4).")
    print(f"asm      : {asm.relative_to(ROOT)}")

    if not args.no_asm:
        print("\n" + "=" * 72 + "\nORIGINAL ASSEMBLY\n" + "=" * 72)
        print("\n".join(extract(asm, fn_name)) if asm.exists() else "(asm file missing; run ninja)")

    print("\n" + "=" * 72 + "\nM2C DRAFT\n" + "=" * 72)
    if not M2C.exists():
        print("(m2c not installed; run python3 tools/setup.py)")
    else:
        ctx = build_context(unit)
        out = subprocess.run(
            [str(M2C), "-t", "ppc-mwcc-c", "--context", str(ctx), "-f", fn_name, str(asm)],
            capture_output=True,
            text=True,
        )
        print((out.stdout + out.stderr).strip())

    if src_path and unit.get("base_path"):
        print("\n" + "=" * 72 + "\nCURRENT DIFF (< original, > ours)\n" + "=" * 72)
        diff_fn(fn_name, unit_name)


if __name__ == "__main__":
    main()
