#!/usr/bin/env python3
"""Runs Dolphin on the MSSB disc with an input movie generated from an
MSSB_INPUT script and dumps frames, in a private user folder
(build/compare/dolphin-user, never the user's own Dolphin config), with a
fresh memory card each run.

  python3 port/tools/compare/dolphin.py --script "500:A,800:A" --frames 1500 --offset 0:84,2820:253 \
      --out build/compare/x/dolphin [--keep 400-700,1200-1300]

Dolphin dumps every frame it presents as Dump/Frames/framedump_N.png (N counts
video fields from the first one shown); frames outside --keep windows are
deleted while it runs. Kept frames are moved to <out>/framedump_N.png;
<out>/movie.dtm and <out>/run.log are kept too.
"""
import argparse
import os
import re
import shutil
import signal
import subprocess
import sys
import time
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(HERE))
import dtm  # noqa: E402

DOLPHIN = "/Applications/Dolphin.app/Contents/MacOS/Dolphin"

# CPUThread off and DSP HLE: deterministic, and the movie stays in sync.
# Frame dumping itself is switched on from the command line (-C): it's a
# runtime setting Dolphin doesn't read from Dolphin.ini.
DOLPHIN_INI = """[Analytics]
PermissionAsked = True
Enabled = False
[Interface]
ConfirmStop = False
SkipNKitWarning = True
ShowActiveTitle = False
UsePanicHandlers = False
OnScreenDisplayMessages = False
[Core]
SIDevice0 = 6
SIDevice1 = 0
SIDevice2 = 0
SIDevice3 = 0
SlotA = 1
SlotB = 255
EmulationSpeed = 0
CPUThread = False
EnableCheats = False
AutoDiscChange = False
[DSP]
DSPHLE = True
Backend = No Audio Output
[Movie]
PauseMovie = {pause}
ShowInputDisplay = False
ShowFrameCounter = False
"""

GFX_INI = """[Settings]
InternalResolution = {scale}
DumpFormat = avi
ShowFPS = False
OSDMessages = False
[Hacks]
EFBToTextureEnable = True
XFBToTextureEnable = True
ImmediateXFBEnable = False
"""

LOGGER_INI = """[Logs]
MASTER = True
CORE = True
BOOT = True
SI = True
[Options]
Verbosity = 4
WriteToConsole = False
WriteToFile = True
WriteToWindow = False
"""

DUMP_RE = re.compile(r"framedump_(\d+)\.png$")


def find_iso():
    cands = [os.environ.get("MSSB_ISO")] + [p / "mario_baseball.iso" for p in [ROOT, *ROOT.parents][:6]]
    for p in cands:
        if p and Path(p).is_file():
            return Path(p)
    sys.exit("no disc image: set MSSB_ISO")


def prepare_user_dir(user, scale=2, pause=False):
    """Fresh config each run; a fresh (empty) memory card in slot A."""
    cfg = user / "Config"
    cfg.mkdir(parents=True, exist_ok=True)
    (cfg / "Dolphin.ini").write_text(DOLPHIN_INI.format(pause="True" if pause else "False"))
    (cfg / "GFX.ini").write_text(GFX_INI.format(scale=scale))
    (cfg / "Logger.ini").write_text(LOGGER_INI)
    (user / "Logs").mkdir(parents=True, exist_ok=True)
    (user / "Logs/dolphin.log").unlink(missing_ok=True)
    for d in ["GC/USA", "GC/EUR", "GC/JAP", "Dump/Frames", "StateSaves"]:
        shutil.rmtree(user / d, ignore_errors=True)
    (user / "GC/USA").mkdir(parents=True, exist_ok=True)
    (user / "Dump/Frames").mkdir(parents=True, exist_ok=True)


def dumped(dump_dir):
    out = {}
    for name in os.listdir(dump_dir):
        m = DUMP_RE.match(name)
        if m:
            out[int(m.group(1))] = dump_dir / name
    return out


def run(script, ndump, out, shift=lambda f: f, keep=None, scale=2, wall=None, user=None, iso=None, log=print):
    """Dumps frames 1..ndump (only those inside `keep` [(lo, hi)] windows, if given)."""
    out = Path(out).resolve()
    shutil.rmtree(out, ignore_errors=True)
    out.mkdir(parents=True)
    user = Path(user or ROOT / "build/compare/dolphin-user").resolve()
    prepare_user_dir(user, scale)
    movie = out / "movie.dtm"
    # The movie runs a little past the last wanted frame; after it ends the pad is idle.
    dtm.write_dtm(movie, script, ndump + 300, shift)
    iso = iso or find_iso()
    cmd = [DOLPHIN, "-u", str(user), "-b", "-C", "Dolphin.Movie.DumpFrames=True",
           "-C", "Dolphin.Movie.DumpFramesSilent=True", "-e", str(iso), "-m", str(movie)]
    logf = open(out / "run.log", "w")
    logf.write(" ".join(cmd) + "\n")
    logf.flush()
    t0 = time.time()
    proc = subprocess.Popen(cmd, stdout=logf, stderr=subprocess.STDOUT)
    dump_dir = user / "Dump/Frames"
    wall = wall or max(300, ndump / 10 + 300)  # Dolphin dumps at ~15-25 fps

    def wanted(n):
        return keep is None or any(lo <= n <= hi for lo, hi in keep)

    def collect(final=False):
        frames = dumped(dump_dir)
        top = max(frames) if frames else 0
        for n, p in frames.items():
            if n > ndump:
                p.unlink(missing_ok=True)
            elif not wanted(n):
                p.unlink(missing_ok=True)
            elif final or n < top - 2:  # the newest ones may still be being written
                shutil.move(str(p), out / p.name)
        return top

    top, last_report = 0, 0
    try:
        while proc.poll() is None and time.time() - t0 < wall:
            time.sleep(2)
            top = collect()
            if time.time() - last_report > 15:
                log(f"  dolphin: {time.time() - t0:4.0f}s, frame {top}/{ndump}")
                last_report = time.time()
            if top >= ndump + 3:
                break
    finally:
        if proc.poll() is None:
            proc.send_signal(signal.SIGINT)  # first signal: clean stop
            try:
                proc.wait(20)
            except subprocess.TimeoutExpired:
                proc.kill()
                proc.wait()
        logf.close()
    top = max(top, collect(final=True))
    if top < ndump:
        log(f"  dolphin: stopped at frame {top} of {ndump} (wall-clock budget {wall:.0f}s)")
    shutil.copy(user / "Logs/dolphin.log", out / "dolphin.log") if (user / "Logs/dolphin.log").exists() else None
    return {n: out / f"framedump_{n}.png" for n in sorted(dumped(out))}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--script", default="")
    ap.add_argument("--frames", type=int, required=True, help="last Dolphin frame to dump")
    ap.add_argument("--offset", default="0",
                    help="Dolphin frame = script frame + offset; or a schedule FROM:OFFSET,FROM:OFFSET")
    ap.add_argument("--keep", help="lo-hi,lo-hi: frame windows to keep")
    ap.add_argument("--out", required=True)
    ap.add_argument("--scale", type=int, default=2)
    a = ap.parse_args()
    keep = [tuple(map(int, w.split("-"))) for w in a.keep.split(",")] if a.keep else None
    sched = sorted(tuple(map(int, x.split(":"))) if ":" in x else (0, int(x)) for x in a.offset.split(","))

    def shift(f):
        d = sched[0][1]
        for start, off in sched:
            if f >= start:
                d = off
        return f + d
    frames = run(a.script, a.frames, a.out, shift, keep, a.scale)
    print(f"{len(frames)} frames in {a.out}")


if __name__ == "__main__":
    main()
