#!/usr/bin/env python3
"""Make objdiff credit data of code-complete REL units.

1. Rename target-side auto symbols (lbl_N_rodata_X, lbl_N_data_X, jumptable_N_data_X)
   that the base object emits as compiler-generated `@123` literals to a numeric `@...`
   name in symbols.txt, so objdiff pairs them by content.
2. Trim a split's section end when it ends in a trailing gap_ (alignment padding) and the
   next explicit split in that section starts right there.

usage: litnames.py <module> [--units a,b] [--dry]   (run from repo root, after ninja)
"""
import argparse, json, re, struct, subprocess, sys
from pathlib import Path

SECS = [".rodata", ".data", ".bss"]
SECNUM = {".rodata": 1, ".data": 2, ".bss": 3}


def read_elf(path):
    b = Path(path).read_bytes()
    shoff, = struct.unpack_from(">I", b, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from(">HHH", b, 0x2E)
    shdrs = []
    for i in range(shnum):
        shdrs.append(struct.unpack_from(">IIIIIIIIII", b, shoff + i * shentsize))
    strtab_off = shdrs[shstrndx][4]
    def cstr(off):
        e = b.index(b"\0", off)
        return b[off:e].decode()
    secs = []
    for sh in shdrs:
        name = cstr(strtab_off + sh[0])
        data = b[sh[4]:sh[4] + sh[5]] if sh[1] != 8 else bytes(sh[5])
        secs.append((name, sh, data))
    syms = []
    for name, sh, data in secs:
        if sh[1] != 2:  # SYMTAB
            continue
        stroff = secs[sh[6]][1][4]
        for i in range(sh[5] // 16):
            st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(">IIIBBH", data, i * 16)
            if st_shndx == 0 or st_shndx >= 0xFF00:
                continue
            if st_info & 0xF == 3:  # section
                continue
            nm = cstr(stroff + st_name)
            syms.append(dict(name=nm, sec=secs[st_shndx][0], value=st_value, size=st_size,
                             bind=st_info >> 4))
    return {n: d for n, _, d in secs}, syms


def parse_splits(path):
    units = []  # (unit, [(sec, start, end, lineidx)])
    lines = Path(path).read_text().splitlines()
    cur = None
    for i, l in enumerate(lines):
        m = re.match(r"^(\S.*):\s*$", l)
        if m and not l.startswith("Sections"):
            cur = (m.group(1), [])
            units.append(cur)
            continue
        m = re.match(r"^\s+(\.\w+)\s+start:0x([0-9A-Fa-f]+) end:0x([0-9A-Fa-f]+)", l)
        if m and cur:
            cur[1].append((m.group(1), int(m.group(2), 16), int(m.group(3), 16), i))
    return lines, units


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("module")
    ap.add_argument("--units", default="")
    ap.add_argument("--dry", action="store_true")
    ap.add_argument("--no-trim", action="store_true")
    ap.add_argument("--no-rename", action="store_true")
    a = ap.parse_args()
    mod = a.module
    cfgdir = Path("config/GYQE01") / mod
    report = json.load(open("build/GYQE01/report.json"))
    complete = set()
    for u in report["units"]:
        if not u["name"].startswith(mod + "/"):
            continue
        m = u["measures"]
        if int(m.get("total_functions", 0)) == int(m.get("matched_functions", 0)):
            complete.add(u["name"].split("/", 1)[1])
    want = set(x for x in a.units.split(",") if x)
    objd = json.load(open("objdiff.json"))
    src_text = ""
    for p in list(Path("src").rglob("*.[ch]")) + list(Path("include").rglob("*.h")):
        src_text += p.read_text(errors="ignore")
    referenced = set(re.findall(r"\b(?:lbl|jumptable)_\d_\w+", src_text))

    sym_lines = (cfgdir / "symbols.txt").read_text().splitlines()
    sym_idx = {}
    for i, l in enumerate(sym_lines):
        m = re.match(r"^(\S+) = (\.\w+):0x([0-9A-Fa-f]+);", l)
        if m:
            sym_idx[(m.group(2), int(m.group(3), 16))] = (i, m.group(1))
    lines, splits = parse_splits(cfgdir / "splits.txt")
    split_of = {u: s for u, s in splits}
    starts = {}
    for u, s in splits:
        for sec, st, en, li in s:
            starts.setdefault(sec, set()).add(st)

    renames = trims = 0
    for u in objd["units"]:
        if not u["name"].startswith(mod + "/") or not u.get("base_path"):
            continue
        uname = u["name"].split("/", 1)[1]
        if uname not in complete or (want and uname not in want):
            continue
        srcname = uname + ".c" if not uname.startswith("auto_") else uname
        sp = split_of.get(srcname)
        if not sp or not Path(u["base_path"]).exists():
            continue
        tsec, tsyms = read_elf(u["target_path"])
        bsec, bsyms = read_elf(u["base_path"])
        for sec, st, en, li in sp:
            if sec not in SECS:
                continue
            ts = sorted([s for s in tsyms if s["sec"] == sec and s["size"] > 0], key=lambda s: s["value"])
            bs = [s for s in bsyms if s["sec"] == sec and re.fullmatch(r"@\d+", s["name"])]
            used = set()
            if not a.no_rename and sec != ".bss":
                for s in ts:
                    if not re.fullmatch(r"(lbl|jumptable)_\d_\w+", s["name"]) or s["name"] in referenced:
                        continue
                    tb = tsec[sec][s["value"]:s["value"] + s["size"]]
                    hit = None
                    for b in bs:
                        if id(b) in used:
                            continue
                        bb = bsec[sec][b["value"]:b["value"] + b["size"]]
                        if b["size"] == s["size"] and bb == tb:
                            hit = b
                            break
                    if hit is None:
                        continue
                    used.add(id(hit))
                    addr = st + s["value"]
                    key = (sec, addr)
                    if key not in sym_idx:
                        print("  no symbols.txt line for", s["name"], hex(addr))
                        continue
                    i, old = sym_idx[key]
                    new = "@%d" % (30000000 + SECNUM[sec] * 1000000 + addr)
                    sym_lines[i] = sym_lines[i].replace(old + " = ", new + " = ", 1)
                    renames += 1
            if not a.no_trim and ts and ts[-1]["name"].startswith("gap_"):
                g = ts[-1]
                if st + g["value"] + g["size"] == en and en in starts.get(sec, ()) :
                    new_end = st + g["value"]
                    lines[li] = re.sub(r"end:0x[0-9A-Fa-f]+", "end:0x%08X" % new_end, lines[li])
                    print(f"  trim {uname} {sec} {en:#x} -> {new_end:#x}")
                    trims += 1
    print(f"renames {renames} trims {trims}")
    if not a.dry:
        (cfgdir / "symbols.txt").write_text("\n".join(sym_lines) + "\n")
        (cfgdir / "splits.txt").write_text("\n".join(lines) + "\n")


main()
