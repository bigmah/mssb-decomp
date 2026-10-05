#!/usr/bin/env python3
"""
List unmatched functions worth working on next, from build/GYQE01/report.json.

Usage:
    python3 tools/next_targets.py                       # best overall candidates
    python3 tools/next_targets.py --module game --max-size 256
    python3 tools/next_targets.py --unit game/game/rep_3880
    python3 tools/next_targets.py --files               # files ranked by how close to done
    python3 tools/next_targets.py --unclaimed           # hide units claimed via tools/claim.py

Default ranking: functions that are already close (high match %) first, then
smaller functions, preferring units that have a source file and are nearly
complete.
"""

import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from claim import active_claims  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("--module", choices=["main", "game", "menus", "challenge"])
    parser.add_argument("--unit", help="only this unit")
    parser.add_argument("--max-size", type=int, help="max function size in bytes")
    parser.add_argument("--has-source", action="store_true", help="only units with a source file")
    parser.add_argument("--files", action="store_true", help="rank units instead of functions")
    parser.add_argument("--unclaimed", action="store_true", help="skip units claimed by other agents")
    parser.add_argument("--limit", type=int, default=30)
    args = parser.parse_args()

    report = json.loads((ROOT / "build" / "GYQE01" / "report.json").read_text())
    objdiff = {u["name"]: u for u in json.loads((ROOT / "objdiff.json").read_text())["units"]}
    claims = active_claims() if args.unclaimed else {}

    rows = []
    files = []
    for unit in report["units"]:
        name = unit["name"]
        if args.module and name.split("/")[0] != args.module:
            continue
        if args.unit and name != args.unit:
            continue
        if name in claims:
            continue
        has_src = bool(objdiff.get(name, {}).get("metadata", {}).get("source_path"))
        if args.has_source and not has_src:
            continue
        fns = unit.get("functions", [])
        if not fns:
            continue
        left = [f for f in fns if f.get("fuzzy_match_percent", 0) < 100]
        if not left:
            continue
        files.append((len(left), len(fns), sum(int(f.get("size", 0)) for f in left), name, has_src))
        for f in left:
            size = int(f.get("size", 0))
            if args.max_size and size > args.max_size:
                continue
            pct = f.get("fuzzy_match_percent", 0)
            rows.append((pct, size, len(left), name, f["name"], has_src))

    if args.files:
        files.sort(key=lambda r: (r[0], r[2]))
        print(f"{'left':>5} {'total':>5} {'bytes left':>10}  unit")
        for left, total, size, name, has_src in files[: args.limit]:
            print(f"{left:>5} {total:>5} {size:>10}  {name}{'' if has_src else '  (no source)'}")
        return

    # close-to-matching first, then small, then units with few functions left
    rows.sort(key=lambda r: (-(r[0] >= 90), -r[5], r[1] if r[0] < 90 else -r[0], r[2]))
    print(f"{'match':>7} {'size':>6}  {'function':<40} unit")
    for pct, size, _, unit, fn, has_src in rows[: args.limit]:
        print(f"{pct:>6.2f}% {size:>6}  {fn:<40} {unit}{'' if has_src else '  (no source)'}")


if __name__ == "__main__":
    main()
