#!/usr/bin/env python3
"""
Try several candidate definitions of a function and score each one.

Usage:
    python3 tools/fnvariants.py RandomInt_Game v1.c v2.c v3.c
    python3 tools/fnvariants.py RandomInt_Game v*.c --also RandomInt_Game_Range,RandomF32_Game_Range

Each variant file holds a complete replacement definition of the function
(signature line through the closing brace). For each variant the function is
swapped into its source file, the unit is rebuilt, and the number of differing
disassembly lines is reported (OK == match). --also scores additional
functions in the same unit, which matters when the function is inlined into
callers. The source file is always restored afterwards.
"""

import argparse
import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from fndiff import ROOT, diff_fn, find_unit, load_unit  # noqa: E402


def locate(src: str, fn_name: str) -> tuple:
    m = re.search(rf"^[^\s/#].*\b{re.escape(fn_name)}\s*\([^;]*?\)\s*\{{", src, re.M)
    if not m:
        sys.exit(f"could not find the definition of {fn_name}")
    end = src.find("\n}\n", m.start())
    if end < 0:
        sys.exit(f"could not find the end of {fn_name}")
    return m.start(), end + 3


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("function", help="function to replace")
    parser.add_argument("variants", nargs="+", type=Path, help="files with replacement definitions")
    parser.add_argument("--also", default="", help="comma-separated extra functions to score")
    parser.add_argument("--unit", help="objdiff unit name (default: look up in report.json)")
    args = parser.parse_args()

    unit_name = args.unit or find_unit(args.function)
    source = ROOT / load_unit(unit_name)["metadata"]["source_path"]
    original = source.read_text()
    start, end = locate(original, args.function)
    fns = [args.function] + [f for f in args.also.split(",") if f]

    try:
        for variant in args.variants:
            body = variant.read_text().rstrip("\n") + "\n"
            source.write_text(original[:start] + body + original[end:])
            scores = []
            for fn in fns:
                n = diff_fn(fn, unit_name, quiet=True)
                scores.append("OK" if n == 0 else ("ERR" if n < 0 else str(n)))
            print(f"{variant}: " + "  ".join(f"{f}={s}" for f, s in zip(fns, scores)))
    finally:
        source.write_text(original)


if __name__ == "__main__":
    main()
