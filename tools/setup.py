#!/usr/bin/env python3
"""
One-shot environment setup for a fresh clone or git worktree.

Usage:
    python3 tools/setup.py                      # find the ISO automatically
    python3 tools/setup.py --iso /path/to/game.iso
    MSSB_ISO=/path/to/game.iso python3 tools/setup.py

Steps (each one is skipped when already done):
  1. configure + download build tools (dtk, objdiff-cli, compilers, wibo)
  2. get orig/GYQE01 files: copy them from the main checkout if this is a
     worktree, otherwise extract them from the ISO and decompress the RELs
  3. verify hashes against config/GYQE01/config.yml
  4. create .venv with m2c
  5. full build (ninja), which also writes report.json
"""

import argparse
import hashlib
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
ORIG = ROOT / "orig" / "GYQE01"
DTK = ROOT / "build" / "tools" / "dtk"
NEEDED = ["sys/main.dol", "files/game.rel", "files/menus.rel", "files/challenge.rel"]
M2C_SPEC = "m2c @ git+https://github.com/matt-kempster/m2c"


def run(cmd, **kw):
    print("+", " ".join(str(c) for c in cmd))
    return subprocess.run(cmd, cwd=ROOT, check=True, **kw)


def main_checkout() -> Path:
    common = subprocess.run(
        ["git", "rev-parse", "--path-format=absolute", "--git-common-dir"],
        cwd=ROOT, capture_output=True, text=True, check=True,
    ).stdout.strip()
    return Path(common).parent


def find_iso(arg):
    candidates = [arg, os.environ.get("MSSB_ISO")]
    for base in {ROOT, main_checkout()}:
        candidates += [base.parent / "mario_baseball.iso", base / "mario_baseball.iso"]
    for c in candidates:
        if c and Path(c).is_file():
            return Path(c)
    return None


def expected_hashes() -> dict:
    hashes = {}
    current = "sys/main.dol"
    for line in (ROOT / "config" / "GYQE01" / "config.yml").read_text().splitlines():
        s = line.strip()
        if s.startswith("object:") or s.startswith("- object:"):
            current = s.split("orig/GYQE01/")[-1]
        elif s.startswith("hash:"):
            hashes[current] = s.split(":", 1)[1].strip()
    return hashes


def orig_ok() -> bool:
    exp = expected_hashes()
    for rel in NEEDED:
        p = ORIG / rel
        if not p.exists() or hashlib.sha1(p.read_bytes()).hexdigest() != exp.get(rel):
            return False
    return True


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("--iso", help="path to the GYQE01 disc image (iso/ciso/rvz)")
    parser.add_argument("--no-build", action="store_true", help="skip the final ninja build")
    args = parser.parse_args()

    if shutil.which("ninja") is None:
        sys.exit("ninja not found: brew install ninja (macOS) or pip install ninja")

    # 1. configure + tools. configure.py needs the RELs to fully succeed, but
    # it writes enough of build.ninja to download dtk first.
    subprocess.run([sys.executable, "configure.py"], cwd=ROOT)
    if not DTK.exists():
        run(["ninja", "build/tools/dtk"])

    # 2. original files
    if not orig_ok():
        main_orig = main_checkout() / "orig" / "GYQE01"
        if main_orig != ORIG and all((main_orig / r).exists() for r in NEEDED):
            print(f"copying original files from {main_orig}")
            for rel in NEEDED:
                (ORIG / rel).parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(main_orig / rel, ORIG / rel)
        else:
            iso = find_iso(args.iso)
            if iso is None:
                sys.exit("could not find the disc image; pass --iso or set MSSB_ISO")
            (ORIG / "sys").mkdir(parents=True, exist_ok=True)
            (ORIG / "files").mkdir(parents=True, exist_ok=True)
            run([DTK, "vfs", "cp", f"{iso}:sys/main.dol", ORIG / "sys/"])
            run([DTK, "vfs", "cp", f"{iso}:files/aaaa.dat", ORIG / "files/"])
            run([sys.executable, "decompress.py"])

    # 3. verify
    if not orig_ok():
        sys.exit("original files don't match the expected hashes (wrong game version?)")
    print("original files OK")

    # 4. m2c
    m2c = ROOT / ".venv" / "bin" / "m2c"
    if not m2c.exists():
        if shutil.which("uv"):
            run(["uv", "venv", "-q", ".venv", "--python", "3.12"])
            run(["uv", "pip", "install", "-q", "--python", ".venv/bin/python", M2C_SPEC])
        else:
            run([sys.executable, "-m", "venv", ".venv"])
            run([".venv/bin/pip", "install", "-q", M2C_SPEC])
    print("m2c OK")

    # 5. build
    run([sys.executable, "configure.py"])
    if not args.no_build:
        run(["ninja"])
    print("\nsetup complete. Start with: python3 tools/next_targets.py")


if __name__ == "__main__":
    main()
