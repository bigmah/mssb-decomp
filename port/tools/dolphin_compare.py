#!/usr/bin/env python3
"""Side-by-side comparison of the web build against Dolphin (ground truth).

Runs one scenario (an MSSB_INPUT script plus a list of frames) on both:
- web: headless Chrome with a fresh profile (no save), MSSB_FREEZE_FRAMES
  holds each listed frame (port/src/freeze_frames.cpp) while the canvas is
  saved (port/tools/compare/web_capture.mjs);
- Dolphin: the same script as a TAS movie (port/tools/compare/dtm.py), private
  user folder with a fresh memory card, frame dumping
  (port/tools/compare/dolphin.py).
Frames are numbered by the port's PADRead count (the MSSB_INPUT clock). The
port and Dolphin drift apart at loads (Dolphin emulates disc timing, the port
loads at once), so each scenario has an offset schedule (script frame ->
Dolphin frame) used for the movie, and each shot is matched to the most
similar Dolphin frame within +-WINDOW of the expected one; the report shows
the offset found (drift from the schedule = alignment error).

  python3 port/tools/dolphin_compare.py menu            # boot -> title -> card prompts -> main menu
  python3 port/tools/dolphin_compare.py game            # menus -> exhibition -> pitching/batting
  python3 port/tools/dolphin_compare.py menu --skip-dolphin   # reuse the Dolphin dump, redo web + report
  python3 port/tools/dolphin_compare.py --list

Output: build/compare/<name>/index.html (side by side, diff, % pixels
differing), shots/<frame>-{web,dolphin,diff}.png (640x480), web/, dolphin/.
Needs build/web (port/tools/build_web.sh), Dolphin.app, Chrome, Python with
Pillow + numpy; starts `node port/tools/web_serve.mjs PORT` if nothing answers.
"""
import argparse
import html
import json
import shutil
import subprocess
import sys
import time
import urllib.request
from pathlib import Path

import numpy as np
from PIL import Image

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE / "compare"))
import dolphin  # noqa: E402

# Boot -> health screen (A) -> logos (A) -> intro movie (START) -> title ->
# START -> "no save file, create one?" -> Yes -> main menu -> Exhibition ->
# captain select. Frames are PADRead counts with the movies played (?movies).
MENU_INPUT = "500:A,800:A,1300:START,2300:RIGHT,2360:A,2600:LEFT,2660:A,3200:A"

SCENARIOS = {
    "menu": {
        "desc": "boot -> health screen -> logos -> intro movie -> title -> memory card prompts -> main menu -> captain select",
        "input": MENU_INPUT,
        "query": "movies",
        "shots": [60, 200, 450, 620, 720, 820, 1000, 1200, 1500, 2000, 2420, 2560, 2640, 2760, 2900, 3100, 3350, 3600],
        # (from script frame, Dolphin frame - script frame): Dolphin shows the
        # health screen 84 fields after the port's first PADRead, and takes
        # ~170 fields longer to create the save file (main menu at port 2840).
        "offsets": [(0, 84), (2820, 253)],
    },
    "game": {
        "desc": "main menu -> Exhibition: Mario captain vs CPU Luigi, random teammates, CPU Weak -> batting orders, "
                "park, options -> stadium intro -> first innings (A every 90 frames: pitches, swings, fielding)",
        "input": MENU_INPUT + ",4400:A,5000:A,6200:A,6800:A,7600:UP,7700:UP,7800:UP,7900:A,8600:A,9400-400000/90:A",
        "query": "movies",
        "shots": [3400, 5100, 6300, 8100, 9300, 9450, 9750, 9900, 10050, 10200, 10350, 10800, 11250, 11700, 12000,
                  12300, 12600, 12900, 13350, 13500, 14100, 14700],
        # Dolphin shows a "Welcome / NOW LOADING" screen for ~280 fields while
        # it loads the stadium (the port loads at once). In-game the RNG differs
        # (teams, pitches), so in-game shots match the closest similar frame.
        "offsets": [(0, 84), (2820, 253), (3300, 248), (9800, 527)],
        "window_from": [(0, 90), (9800, 200)],
    },
}

WINDOW = 90       # search +-WINDOW Dolphin frames around the expected one
SIZE = (640, 480)  # both captures are compared at this size
THRESH = 32       # a pixel differs if any channel differs by more than this (0-255)
THRESH_LO = 8     # second, stricter count (colour shifts, filtering)


def shift_fn(offsets):
    offs = sorted(offsets)

    def shift(f):
        d = offs[0][1]
        for start, off in offs:
            if f >= start:
                d = off
        return f + d
    return shift


def ensure_server(port):
    url = f"http://localhost:{port}/index.html"
    try:
        urllib.request.urlopen(url, timeout=2)
        return None
    except Exception:
        pass
    proc = subprocess.Popen(["node", str(ROOT / "port/tools/web_serve.mjs"), str(port)],
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    for _ in range(50):
        time.sleep(0.2)
        try:
            urllib.request.urlopen(url, timeout=2)
            return proc
        except Exception:
            pass
    proc.kill()
    sys.exit(f"web_serve.mjs didn't start on port {port}")


def load(path):
    return np.asarray(Image.open(path).convert("RGB").resize(SIZE, Image.LANCZOS), dtype=np.int16)


def small(img):
    return np.asarray(Image.fromarray(img.astype(np.uint8)).convert("L").resize((160, 120), Image.BILINEAR), dtype=np.float32)


def diff_image(a, b):
    """Dimmed grey of the Dolphin frame with differing pixels in red (brighter = larger)."""
    d = np.abs(a - b).max(axis=2)
    grey = (a.mean(axis=2) * 0.35).astype(np.int16)
    out = np.stack([grey, grey, grey], axis=2)
    mask = d > THRESH
    out[mask, 0] = np.clip(96 + d[mask], 0, 255)
    out[mask, 1] = grey[mask] // 2
    out[mask, 2] = grey[mask] // 2
    return out.astype(np.uint8), d


def align_and_diff(name, sc, out, frames_web, dumps, window):
    shift = shift_fn(sc["offsets"])
    shots_dir = out / "shots"
    shots_dir.mkdir(exist_ok=True)
    rows = []
    for f in sc["shots"]:
        wpath = out / "web" / f"web-{f}.png"
        if not wpath.exists():
            rows.append({"frame": f, "missing": "web"})
            continue
        web = load(wpath)
        ws = small(web)
        exp = shift(f)
        win = window
        for start, w in sc.get("window_from", []):
            if f >= start and window == WINDOW:
                win = w
        cands = [n for n in range(exp - win, exp + win + 1) if n in dumps]
        if not cands:
            rows.append({"frame": f, "missing": "dolphin", "expected": exp})
            continue
        # Prefer the expected frame on ties (static screens).
        scored = sorted((float(np.abs(small(load(dumps[n])) - ws).mean()) + abs(n - exp) * 1e-4, n) for n in cands)
        score, best = scored[0]
        dol = load(dumps[best])
        dimg, d = diff_image(dol, web)
        pct = float((d > THRESH).mean() * 100)
        pct_lo = float((d > THRESH_LO).mean() * 100)
        Image.fromarray(web.astype(np.uint8)).save(shots_dir / f"{f}-web.png")
        Image.fromarray(dol.astype(np.uint8)).save(shots_dir / f"{f}-dolphin.png")
        Image.fromarray(dimg).save(shots_dir / f"{f}-diff.png")
        rows.append({
            "frame": f, "dolphin_frame": best, "expected": exp, "drift": best - exp,
            "pct_diff": round(pct, 2), "pct_diff_lo": round(pct_lo, 2), "mean_abs": round(float(np.abs(dol - web).mean()), 2),
            "align_score": round(score, 2), "web_info": frames_web.get(str(f), {}),
        })
        rows[-1]["web_src"] = str(wpath.relative_to(out))
        rows[-1]["dolphin_src"] = str(dumps[best].relative_to(out))
        print(f"  frame {f:5d}: dolphin {best} (expected {exp}, drift {best - exp:+d}), {pct:5.1f}% differ (>{THRESH}), {pct_lo:5.1f}% (>{THRESH_LO})")
    return rows


def write_report(name, sc, out, rows):
    def img(src, label):
        return f'<figure><a href="{src}"><img src="{src}" loading="lazy"></a><figcaption>{label}</figcaption></figure>'

    parts = []
    for r in rows:
        f = r["frame"]
        if "missing" in r:
            parts.append(f'<section><h2>frame {f}</h2><p class="warn">no {r["missing"]} capture</p></section>')
            continue
        note = f'Dolphin frame {r["dolphin_frame"]} (expected {r["expected"]}, drift {r["drift"]:+d})'
        parts.append(
            f'<section id="f{f}"><h2>frame {f} <span class="pct">{r["pct_diff"]:.1f}% pixels differ</span>'
            f'<span class="meta">{r["pct_diff_lo"]:.1f}% &gt; {THRESH_LO}/255, mean |d| {r["mean_abs"]}, {note}, '
            f'full size: <a href="{r["dolphin_src"]}">Dolphin</a> <a href="{r["web_src"]}">web</a></span></h2>'
            f'<div class="row">{img(f"shots/{f}-dolphin.png", "Dolphin")}{img(f"shots/{f}-web.png", "web")}'
            f'{img(f"shots/{f}-diff.png", "diff (red: > %d/255)" % THRESH)}</div></section>')
    summary = "".join(
        f'<tr><td><a href="#f{r["frame"]}">{r["frame"]}</a></td>'
        + (f'<td>{r["dolphin_frame"]}</td><td>{r["drift"]:+d}</td><td>{r["pct_diff"]:.1f}%</td><td>{r["pct_diff_lo"]:.1f}%</td><td>{r["mean_abs"]}</td>'
           if "missing" not in r else f'<td colspan=5>missing {r["missing"]}</td>')
        + "</tr>" for r in rows)
    doc = f"""<!doctype html>
<html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<title>{html.escape(name)}: Dolphin vs web</title>
<style>
:root {{ color-scheme: light dark; --bg: #f6f6f4; --fg: #1b1b1b; --muted: #666; --card: #fff; --accent: #c0392b; }}
@media (prefers-color-scheme: dark) {{ :root {{ --bg: #161616; --fg: #e8e8e8; --muted: #9a9a9a; --card: #222; --accent: #ff6b5b; }} }}
body {{ background: var(--bg); color: var(--fg); font: 14px/1.4 -apple-system, system-ui, sans-serif; margin: 16px; }}
h1 {{ font-size: 20px; }} h2 {{ font-size: 16px; margin: 0 0 8px; }}
.pct {{ color: var(--accent); margin-left: 12px; }} .meta {{ color: var(--muted); font-weight: normal; margin-left: 12px; font-size: 13px; }}
section {{ background: var(--card); padding: 12px; margin: 12px 0; border-radius: 6px; }}
.row {{ display: grid; grid-template-columns: repeat(3, minmax(0, 1fr)); gap: 8px; }}
@media (max-width: 800px) {{ .row {{ grid-template-columns: 1fr; }} }}
figure {{ margin: 0; }} img {{ width: 100%; height: auto; display: block; image-rendering: auto; }}
figcaption {{ color: var(--muted); font-size: 12px; }}
table {{ border-collapse: collapse; }} td, th {{ padding: 2px 10px; text-align: right; }}
.warn {{ color: var(--accent); }}
</style></head><body>
<h1>{html.escape(name)}: Dolphin (ground truth) vs web build</h1>
<p>{html.escape(sc["desc"])}<br>Input: <code>{html.escape(sc["input"])}</code>{' (?' + html.escape(sc.get("query", "")) + ')' if sc.get("query") else ''}<br>
Frames are the port's PADRead counts; each web frame is matched to the most similar Dolphin frame within &plusmn;{WINDOW}
of the scheduled one. Compared at {SIZE[0]}x{SIZE[1]}; a pixel differs if a channel differs by more than {THRESH}/255 (stricter count: {THRESH_LO}/255).
Expect differences from animation phase and RNG wherever the drift isn't 0.</p>
<table><tr><th>frame</th><th>Dolphin</th><th>drift</th><th>&gt;{THRESH}</th><th>&gt;{THRESH_LO}</th><th>mean |d|</th></tr>{summary}</table>
{''.join(parts)}
</body></html>
"""
    (out / "index.html").write_text(doc)
    (out / "results.json").write_text(json.dumps({"scenario": name, **sc, "rows": rows}, indent=1))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("scenario", nargs="?")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--port", type=int, default=8090)
    ap.add_argument("--out", help="default build/compare/<scenario>")
    ap.add_argument("--skip-web", action="store_true", help="reuse <out>/web")
    ap.add_argument("--skip-dolphin", action="store_true", help="reuse <out>/dolphin")
    ap.add_argument("--window", type=int, default=WINDOW)
    ap.add_argument("--keep-dumps", action="store_true",
                    help="keep every dumped Dolphin frame (default: only the matched ones, so --skip-dolphin can't re-search)")
    ap.add_argument("--scale", type=int, default=2, help="Dolphin internal resolution (x native)")
    ap.add_argument("--shots", help="override the scenario's frame list (comma-separated)")
    ap.add_argument("--input", help="MSSB_INPUT script (overrides the scenario's; with an unknown scenario name, makes a new one)")
    ap.add_argument("--offsets", help="FROM:OFFSET,... Dolphin frame offset schedule (default 0:84)")
    ap.add_argument("--query", help="extra page query for the web build (default: the scenario's, e.g. movies)")
    a = ap.parse_args()
    if a.list or not a.scenario:
        for k, v in SCENARIOS.items():
            print(f"{k:8s} {v['desc']}")
        return
    if a.scenario in SCENARIOS:
        sc = dict(SCENARIOS[a.scenario])
    elif a.input and a.shots:
        sc = {"desc": "ad-hoc scenario", "input": a.input, "query": "movies", "shots": [], "offsets": [(0, 84)]}
    else:
        sys.exit(f"unknown scenario {a.scenario}: pass --input and --shots for an ad-hoc one (--list shows the built-in ones)")
    if a.input:
        sc["input"] = a.input
    if a.offsets:
        sc["offsets"] = [tuple(map(int, x.split(":"))) for x in a.offsets.split(",")]
    if a.query is not None:
        sc["query"] = a.query
    if a.shots:
        sc["shots"] = [int(x) for x in a.shots.split(",")]
    out = Path(a.out or ROOT / "build/compare" / a.scenario).resolve()
    out.mkdir(parents=True, exist_ok=True)
    shift = shift_fn(sc["offsets"])
    last = max(sc["shots"])

    server = None
    try:
        if not a.skip_web:
            server = ensure_server(a.port)
            shutil.rmtree(out / "web", ignore_errors=True)
            print(f"web: {len(sc['shots'])} frames")
            cmd = ["node", str(HERE / "compare/web_capture.mjs"), "--port", str(a.port), "--input", sc["input"],
                   "--frames", ",".join(map(str, sc["shots"])), "--out", str(out / "web"),
                   "--timeout", str(int(last / 60 * 3 + 120))]
            if sc.get("query"):
                cmd += ["--query", sc["query"]]
            if subprocess.run(cmd).returncode != 0:
                print("web capture incomplete; continuing with what was captured")
        if not a.skip_dolphin:
            print("dolphin:")
            def win(f):
                w = a.window
                for start, ww in sc.get("window_from", []):
                    if f >= start and a.window == WINDOW:
                        w = ww
                return w
            keep = [(shift(f) - win(f), shift(f) + win(f)) for f in sc["shots"]]
            dolphin.run(sc["input"], shift(last) + win(last), out / "dolphin", shift, keep, a.scale,
                        log=lambda s: print(s, flush=True))
    finally:
        if server:
            server.kill()
    dumps = {int(p.stem.split("_")[1]): p for p in (out / "dolphin").glob("framedump_*.png")}
    fw = json.loads((out / "web/frames.json").read_text()) if (out / "web/frames.json").exists() else {}
    print("align + diff:")
    rows = align_and_diff(a.scenario, sc, out, fw, dumps, a.window)
    write_report(a.scenario, sc, out, rows)
    if not a.keep_dumps:
        # Dolphin dumps ~1 MB per frame: keep only the matched ones (and their neighbours).
        used = {r["dolphin_frame"] + k for r in rows if "dolphin_frame" in r for k in range(-2, 3)}
        for n, p in dumps.items():
            if n not in used:
                p.unlink()
    print(f"report: {out / 'index.html'}")


if __name__ == "__main__":
    main()
