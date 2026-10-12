#!/usr/bin/env python3
"""Find views of scene tasks (structs read from lbl_803CC1B8 or returned by
fn_800B0A5C_insertQueue) whose fields don't sit where SceneTask has them on PC.

    python3 port/tools/taskviewcheck.py        # from the repo root

SceneTask on PC: func 0x00, prev 0x08, next 0x10, parent 0x18, _10 0x20,
priority 0x22, then the task's own area from 0x28 (GameCube 0x14). A view's
first field at GameCube offset >= 0x14 must be at PC 0x28 + (offset - 0x14);
fields at 0x10/0x12 at 0x20/0x22; a field at 0x0C (parent) at 0x18.
Fix: SCENE_TASK_VIEW_HEAD / SCENE_TASK_VIEW_LINKS (main/scene_task.h).
"""
import os, re, sys
sys.argv = sys.argv[:1]
here = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, here)
from pcview import dump  # noqa: E402

src = {}
for d in ['src/main', 'src/game', 'src/menus', 'src/challenge']:
    for r_, _, fs in os.walk(d):
        for f in fs:
            if f.endswith('.c'):
                p = os.path.join(r_, f)
                src[p] = open(p, errors='ignore').read()
uses = {}
pat = re.compile(r'\b(\w+)\s*\*\s*\w+\s*=\s*(?:\(\s*(?:struct\s+)?\w+\s*\*\s*\))?\s*(?:\*\s*\(\s*\w+\s*\*\*\s*\)\s*&\s*)?(?:lbl_803CC1B8|fn_800B0A5C_insertQueue\b)')
pat2 = re.compile(r'\(\s*(?:struct\s+)?(\w+)\s*\*\s*\)\s*(?:lbl_803CC1B8|fn_800B0A5C_insertQueue\b)')
for f, t in src.items():
    for m in list(pat.finditer(t)) + list(pat2.finditer(t)):
        T = m.group(1)
        if T in ('void', 'u8', 'SceneTask', 'SpaniOwner', 'SpaniGroup', 'MenuTask', 'struct'):
            continue
        uses.setdefault(T, set()).add(f)
EXPECT = {0x0C: 0x18, 0x10: 0x20, 0x12: 0x22}
for T, fs in sorted(uses.items()):
    f = sorted(fs)[0]
    P, _ = dump(f, 'pc')
    G, _ = dump(f, 'gc')
    if T not in P or T not in G or len(P[T]) != len(G[T]):
        continue
    for (g, _, name), (p, ty, _) in zip(G[T], P[T]):
        if g in EXPECT:
            want = EXPECT[g]
        elif g >= 0x14:
            want = 0x28 + g - 0x14
        else:
            continue
        if p != want:
            print('%s (%s): %s gc 0x%X pc 0x%X, want 0x%X' % (T, f, name, g, p, want))
        if g >= 0x14:
            break
