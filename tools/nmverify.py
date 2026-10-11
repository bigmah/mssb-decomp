#!/usr/bin/env python3
"""Sanity-check equivalent (`#if NONMATCHING`) functions against the original.

Compiles each source with -DNONMATCHING=1, disassembles it, and for every
function that is unmatched in report.json compares with the target object:
  - calls (`bl` targets, as a multiset)
  - references to lbl_N_{data,bss,...} globals that only our side makes
  - instruction-level similarity (registers normalised)
Equivalent C should make the same calls and touch the same globals; a
mismatch there is far more likely a bug than a compiler difference.

    python3 tools/nmverify.py src/game/rep_3C28.c [...]
    python3 tools/nmverify.py --all [--min-sim 0.5]
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


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("sources", nargs="*")
    ap.add_argument("--all", action="store_true")
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
        for name in unmatched:
            tb, ob = fn_body(target, name), fn_body(ours, name)
            if not ob:
                print(f"{src}: {name}: NO C (missing from NONMATCHING build)"); flagged += 1; continue
            problems = []
            tc, oc = calls(tb), calls(ob)
            if tc != oc:
                miss = sorted((tc - oc).elements()); extra = sorted((oc - tc).elements())
                # an inlined callee in the original shows up as an extra call in ours: still worth a look
                problems.append(f"calls differ (target-only {miss}, ours-only {extra})")
            tr = fndiff.DATA_REF_RE.findall(tb); orf = fndiff.DATA_REF_RE.findall(ob)
            extra_refs = sorted(set(orf) - set(tr) - literals)
            if extra_refs:
                problems.append(f"ours-only globals {extra_refs}")
            tl = [fndiff.REG_RE.sub(r"\1N", l) for l in fndiff.extract(target_s, name, literals)]
            ol_path = Path(tempfile.gettempdir()) / "nmverify_ours.s"
            ol_path.write_text(ours)
            ol = [fndiff.REG_RE.sub(r"\1N", l) for l in fndiff.extract(ol_path, name, literals)]
            sim = difflib.SequenceMatcher(None, tl, ol, autojunk=False).ratio()
            if sim < args.min_sim:
                problems.append(f"similarity {sim:.0%}")
            if problems:
                flagged += 1
                print(f"{src}: {name} ({sim:.0%}): " + "; ".join(problems))
    print(f"{flagged} function(s) flagged")


if __name__ == "__main__":
    main()
