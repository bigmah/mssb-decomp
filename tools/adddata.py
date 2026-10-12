#!/usr/bin/env python3
"""Move a REL unit's .data range from an auto split into the unit, defined in C.

    tools/adddata.py game/rep_3880.c 0x266A8 0x26F00 [--module game] [--dry]

1. Adds `.data start:.. end:..` to the unit's block in splits.txt.
2. Retypes byte-array externs (`extern u8 x[];`) of the objects in that range from
   the access-size hint dtk left in symbols.txt (data:float -> f32, data:4byte -> s32,
   data:2byte -> s16, data:string -> char), so the C data is endian-correct on a port.
   Uses of a retyped name in the code become `((u8*)name)`, which keeps the byte
   arithmetic (and the generated code) unchanged. Objects with relocations keep their
   declared type (give them pointer/struct types by hand first).
3. Runs tools/gendata.py --unit and appends the definitions to the source file.

Review the result: `// TODO type` blobs, size warnings from gendata (stderr), and
objects without any extern declaration. Then build and check the unit's .data in
report.json and `dtk shasum`.
"""
import argparse, re, subprocess, struct, sys

ap = argparse.ArgumentParser()
ap.add_argument("unit")
ap.add_argument("start")
ap.add_argument("end")
ap.add_argument("--module", default="game")
ap.add_argument("--dry", action="store_true")
ap.add_argument("--src", help="source file if not src/<unit> (auto units)")
a = ap.parse_args()
st, en = int(a.start, 16), int(a.end, 16)
cfg = "config/GYQE01/%s/" % a.module
src = a.src or ("src/" + a.unit)

# --- relocations inside .data of the original REL
rel = open("orig/GYQE01/files/%s.rel" % a.module, "rb").read()
nsec, secoff = struct.unpack(">II", rel[0xC:0x14])
secnames = re.findall(r"^\t(\.\w+)\s+type:", open(cfg + "splits.txt").read().split("\n\n")[0], re.M)
DATA = secnames.index(".data") + 1
impoff, impsize = struct.unpack(">II", rel[0x28:0x30])
relocs = set()
for k in range(impsize // 8):
    mod, roff = struct.unpack(">II", rel[impoff + 8 * k: impoff + 8 * k + 8])
    pos = roff; cur = 0; sec = 0
    while True:
        o, typ, tsec, add = struct.unpack(">HBBI", rel[pos:pos + 8]); pos += 8
        cur += o
        if typ == 203: break
        if typ == 202: sec = tsec; cur = 0; continue
        if sec == DATA and typ not in (201,):
            relocs.add(cur)

# --- objects in range
objs = []
for l in open(cfg + "symbols.txt"):
    m = re.match(r"^(\S+) = \.data:0x([0-9A-Fa-f]+); // type:object size:0x([0-9A-Fa-f]+)(.*)", l)
    if m and st <= int(m.group(2), 16) < en:
        objs.append((m.group(1), int(m.group(2), 16), int(m.group(3), 16), m.group(4)))

s = open(src).read()
changed = []
for name, addr, size, rest in objs:
    if name.startswith(("jumptable_", "@", "gap_", "pad_")):
        continue
    if any(addr <= r < addr + size for r in relocs):
        print("keep (relocs): %s" % name); continue
    decls = list(re.finditer(r"^extern\s+(?:const\s+)?(u8|s8|unsigned char|char)\s+" + name + r"\s*\[[^\]]*\]\s*;[^\n]*$", s, re.M))
    if not decls:
        continue
    hint = re.search(r"data:(\w+)", rest)
    hint = hint.group(1) if hint else ""
    if hint == "float" and size % 4 == 0 and addr % 4 == 0:
        t, n = "f32", size // 4
    elif hint == "4byte" and size % 4 == 0 and addr % 4 == 0:
        t, n = "s32", size // 4
    elif hint == "2byte" and size % 2 == 0 and addr % 2 == 0:
        t, n = "s16", size // 2
    elif hint == "string":
        t, n = "char", size
    else:
        continue
    if t == "char" and decls[0].group(1) in ("char",):
        continue
    for d in reversed(decls):
        s = s[:d.start()] + "extern %s %s[%d];" % (t, name, n) + s[d.end():]
    # rewrite uses (not in extern declarations)
    out = []
    for line in s.split("\n"):
        if re.match(r"^extern\b", line):
            out.append(line); continue
        out.append(re.sub(r"(?<![\w(])\b" + name + r"\b", "((u8*)%s)" % name, line))
    s = "\n".join(out)
    changed.append((name, t, n))
for c in changed:
    print("retyped %s -> %s[%d]" % c)
if a.dry:
    sys.exit(0)
open(src, "w").write(s)

# --- split
sp = open(cfg + "splits.txt").read()
m = re.search(r"^" + re.escape(a.unit) + r":[^\n]*\n((?:\t[^\n]*\n)*)", sp, re.M)
if not m and a.unit.startswith("auto_00_"):
    # auto text unit with a source file: give it an explicit block ending at the next .text split
    tst = int(a.unit.split("_")[2], 16)
    nxt = min(int(x, 16) for x in re.findall(r"\.text\s+start:0x([0-9A-Fa-f]+)", sp) if int(x, 16) > tst)
    blkname = None
    for mm in re.finditer(r"^(\S[^\n]*):\n\t\.text\s+start:0x([0-9A-Fa-f]+)", sp, re.M):
        if int(mm.group(2), 16) == nxt: blkname = mm.start(); break
    sp = sp[:blkname] + "%s:\n\t.text       start:0x%08X end:0x%08X\n\n" % (a.unit, tst, nxt) + sp[blkname:]
    m = re.search(r"^" + re.escape(a.unit) + r":[^\n]*\n((?:\t[^\n]*\n)*)", sp, re.M)
blk = m.group(1)
if ".data" not in blk:
    order = [".text", ".ctors", ".dtors", ".rodata", ".data", ".bss"]
    new, ins = [], False
    for l in blk.splitlines():
        if not ins and order.index(l.split()[0]) > order.index(".data"):
            new.append("\t.data       start:0x%08X end:0x%08X" % (st, en)); ins = True
        new.append(l)
    if not ins:
        new.append("\t.data       start:0x%08X end:0x%08X" % (st, en))
    sp = sp[:m.start(1)] + "\n".join(new) + "\n" + sp[m.end(1):]
    open(cfg + "splits.txt", "w").write(sp)

g = subprocess.run([sys.executable, "tools/gendata.py", "--unit", a.unit, "--module", a.module, "--sects", ".data"],
                   capture_output=True, text=True)
sys.stderr.write(g.stderr)
with open(src, "a") as f:
    f.write("\n" + g.stdout)
print(g.stdout)
