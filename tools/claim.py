#!/usr/bin/env python3
"""
Claim a unit (source file) so parallel agents don't work on the same one.

Claims live in the shared git directory (<git-common-dir>/mssb-claims), so
every worktree of this clone sees the same claims. They are local to this
machine and never committed.

Usage:
    python3 tools/claim.py claim game/game/rep_3880 --who agent-3
    python3 tools/claim.py release game/game/rep_3880
    python3 tools/claim.py list
    python3 tools/claim.py release-all --who agent-3

Claims older than 12 hours are treated as stale and can be taken over.
"""

import argparse
import json
import os
import subprocess
import sys
import time
from pathlib import Path

STALE_SECONDS = 12 * 3600


def claims_dir() -> Path:
    common = subprocess.run(
        ["git", "rev-parse", "--path-format=absolute", "--git-common-dir"],
        cwd=Path(__file__).resolve().parent,
        capture_output=True,
        text=True,
        check=True,
    ).stdout.strip()
    d = Path(common) / "mssb-claims"
    d.mkdir(exist_ok=True)
    return d


def claim_file(unit: str) -> Path:
    return claims_dir() / (unit.replace("/", "__") + ".json")


def active_claims() -> dict:
    out = {}
    for p in claims_dir().glob("*.json"):
        try:
            data = json.loads(p.read_text())
        except (OSError, ValueError):
            continue
        if time.time() - data.get("time", 0) < STALE_SECONDS:
            out[data["unit"]] = data
    return out


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0].strip())
    parser.add_argument("action", choices=["claim", "release", "list", "release-all"])
    parser.add_argument("unit", nargs="?")
    parser.add_argument("--who", default=os.environ.get("AGENT_NAME", os.path.basename(os.getcwd())))
    args = parser.parse_args()

    if args.action == "list":
        for unit, data in sorted(active_claims().items()):
            age = (time.time() - data["time"]) / 60
            print(f"{unit:<45} {data['who']:<20} {age:5.0f} min")
        return

    if args.action == "release-all":
        for unit, data in active_claims().items():
            if data["who"] == args.who:
                claim_file(unit).unlink(missing_ok=True)
                print(f"released {unit}")
        return

    if not args.unit:
        sys.exit("unit required")
    path = claim_file(args.unit)

    if args.action == "release":
        path.unlink(missing_ok=True)
        print(f"released {args.unit}")
        return

    payload = json.dumps({"unit": args.unit, "who": args.who, "time": time.time()})
    try:
        fd = os.open(path, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
    except FileExistsError:
        data = json.loads(path.read_text())
        if data["who"] == args.who or time.time() - data["time"] >= STALE_SECONDS:
            path.write_text(payload)
            print(f"claimed {args.unit} (refreshed)")
            return
        sys.exit(f"{args.unit} is already claimed by {data['who']}")
    with os.fdopen(fd, "w") as f:
        f.write(payload)
    print(f"claimed {args.unit}")


if __name__ == "__main__":
    main()
