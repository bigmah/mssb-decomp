#!/usr/bin/env python3
"""Compile source files with -DNONMATCHING=1 to check that equivalent
(`#if NONMATCHING`) code still compiles. The matching build never sees it.

    python3 tools/nmcheck.py src/game/rep_3C28.c [more.c ...]
    python3 tools/nmcheck.py --all          # every source with a NONMATCHING block
"""
import os, re, subprocess, sys, tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def obj_for(src):
    text = open(os.path.join(ROOT, "build.ninja")).read()
    m = re.search(r"^build (\S+\.o): mwcc\S*(?: \$\n)?\s+" + re.escape(src) + r"\b", text, re.M)
    return m.group(1) if m else None


def check(src, tmp):
    obj = obj_for(src)
    if not obj:
        print(f"{src}: no build rule"); return False
    cmd = subprocess.run(["ninja", "-t", "commands", obj], cwd=ROOT,
                         capture_output=True, text=True).stdout.strip().splitlines()[-1]
    cmd = cmd.split(" && ")[0]
    cmd = cmd.replace("-DNONMATCHING=0", "")
    cmd = re.sub(r" -o \S+", f" -o {tmp}", cmd).replace(" -MMD", "")
    cmd += " -DNONMATCHING=1"
    r = subprocess.run(cmd, shell=True, cwd=ROOT, capture_output=True, text=True)
    if r.returncode != 0:
        print(f"{src}: FAILED\n{r.stdout}{r.stderr}")
        return False
    print(f"{src}: ok")
    return True


def main():
    args = sys.argv[1:]
    if args == ["--all"]:
        out = subprocess.run(["grep", "-rlE", r"^#if\s+NONMATCHING", "src"], cwd=ROOT,
                             capture_output=True, text=True).stdout.split()
        args = sorted(out)
    ok = True
    with tempfile.TemporaryDirectory() as d:
        for src in args:
            src = os.path.relpath(os.path.abspath(src), ROOT) if os.path.isabs(src) else src
            ok &= check(src, d)
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
