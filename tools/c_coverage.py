#!/usr/bin/env python3
"""Count functions that still have no C: unmatched in report.json and with no
`#if NONMATCHING` definition in their unit's source. This is the headline
metric for the port (see plan.md, "End goal")."""
import argparse, json, os, re
from collections import defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def unit_source(unit, cfg_sources):
    parts = unit.split("/")
    if len(parts) == 3:
        return os.path.join(ROOT, "src", parts[1], parts[2] + ".c")
    return cfg_sources.get(parts[1])


def nonmatching_defs(path):
    """Names of functions defined inside `#if NONMATCHING` blocks."""
    names = set()
    try:
        text = open(path, encoding="utf-8", errors="replace").read()
    except OSError:
        return names
    depth = 0
    nm_depth = None
    for line in text.splitlines():
        s = line.strip()
        if s.startswith("#if"):
            depth += 1
            if nm_depth is None and re.match(r"#if\s+NONMATCHING\b", s):
                nm_depth = depth
        elif s.startswith("#endif"):
            if nm_depth == depth:
                nm_depth = None
            depth -= 1
        elif nm_depth is not None:
            m = re.match(r"^[A-Za-z_][\w\s\*]*?\b(\w+)\s*\([^;]*$", line)
            if m and not line.startswith((" ", "\t")):
                names.add(m.group(1))
    return names


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--units", action="store_true", help="list units with functions left")
    ap.add_argument("--module")
    args = ap.parse_args()
    report = json.load(open(os.path.join(ROOT, "build/GYQE01/report.json")))
    cfg = open(os.path.join(ROOT, "configure.py")).read()
    cfg_sources = {m.group(1): os.path.join(ROOT, "src", m.group(2))
                   for m in re.finditer(r'Object\(\w+,\s*"([^"]+)",\s*source="([^"]+)"', cfg)}
    per_mod = defaultdict(lambda: [0, 0, 0, 0])  # total, matched, equivalent, todo
    todo_units = []
    for u in report["units"]:
        mod = u["metadata"].get("module_name", "?")
        if args.module and mod != args.module:
            continue
        funcs = u.get("functions") or []
        if not funcs:
            continue
        src = unit_source(u["name"], cfg_sources)
        nm = nonmatching_defs(src) if src else set()
        left = []
        for f in funcs:
            per_mod[mod][0] += 1
            if f.get("fuzzy_match_percent") == 100.0:
                per_mod[mod][1] += 1
            elif f["name"] in nm:
                per_mod[mod][2] += 1
            else:
                per_mod[mod][3] += 1
                left.append(int(f["size"]))
        if left:
            todo_units.append((len(left), sum(left), u["name"]))
    if args.units:
        for n, b, name in sorted(todo_units, key=lambda t: (t[1], t[2])):
            print(f"{n:5} {b:8}  {name}")
        return
    tot = [0, 0, 0, 0]
    print(f"{'module':10} {'total':>6} {'matched':>8} {'equiv':>6} {'no C':>6}")
    for mod, v in sorted(per_mod.items()):
        print(f"{mod:10} {v[0]:6} {v[1]:8} {v[2]:6} {v[3]:6}")
        tot = [a + b for a, b in zip(tot, v)]
    print(f"{'all':10} {tot[0]:6} {tot[1]:8} {tot[2]:6} {tot[3]:6}")


if __name__ == "__main__":
    main()
