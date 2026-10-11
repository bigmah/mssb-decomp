#!/usr/bin/env python3
"""Check the constant values each function loads from .sdata2/.rodata.

objdiff/report.json and fndiff anonymise literals (`@123`, `lbl_3_sdata2_*`), so a
function can count as 100% matched while loading 360.0f where the original loads 180.0f.
This tool resolves every relocation from .text into .sdata2/.rodata to the value it
points at (through the section data of each object) and compares, per function, the set
of values the target object loads with the set ours loads:
  - float (lfs), double (lfd), paired single (psq_l), integer (lwz/lhz/lbz) loads
  - addresses (addi / la): a NUL-terminated string, else the bytes of the object
    (pooled float tables are split into their floats/doubles)

Our object is the normal build (build/GYQE01/src/...o) for units without `#if
NONMATCHING`, else a -DNONMATCHING=1 compile (as nmverify does), so matched and
equivalent functions are both covered. Stubs (ours has no literals and is less than
half the target's size) are skipped.

Accepted automatically:
  - int->float magic doubles (0x43300000_xxxxxxxx) compare equal to each other
  - a value ours loads on its own that lies inside a pooled block the target addresses
    (and vice versa), or a float/double of the same value on the other side when
    the only difference is the precision of a pooled block entry
  - values of a helper from the same source inlined on one side only
Reviewed by hand: values on a `// litcheck: ...` line in the comment block above the
function are left out (write them as printed, e.g. `// litcheck: 0.5 "abc" pooled`);
`// litcheck: all ...` waives every difference. Say why on that line.

    python3 tools/litcheck.py src/game/rep_3C28.c [...]
    python3 tools/litcheck.py --all [-v] [--counts] [--fn NAME]
Exit status 1 when something is flagged.
"""
import argparse, collections, json, re, struct, subprocess, sys, tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import nmcheck  # noqa: E402

ROOT = Path(__file__).resolve().parent.parent
LIT_SECTIONS = (".sdata2", ".rodata")

# ---------------------------------------------------------------- ELF ---------------


class Elf:
    """Just enough of a big-endian ELF32 relocatable object."""

    def __init__(self, path):
        d = Path(path).read_bytes()
        self.d = d
        (shoff,) = struct.unpack_from(">I", d, 0x20)
        shentsize, shnum, shstrndx = struct.unpack_from(">HHH", d, 0x2E)
        self.secs = []
        for i in range(shnum):
            name, typ, flags, addr, off, size, link, info, align, entsize = struct.unpack_from(
                ">10I", d, shoff + i * shentsize)
            self.secs.append(dict(name=name, type=typ, off=off, size=size, link=link, info=info,
                                  entsize=entsize))
        strtab = self.secs[shstrndx]
        for s in self.secs:
            s["name"] = self._str(strtab, s["name"])
        self.syms = []
        for s in self.secs:
            if s["type"] == 2:  # SYMTAB
                st = self.secs[s["link"]]
                for j in range(s["size"] // 16):
                    nm, val, sz, info, oth, shndx = struct.unpack_from(">IIIBBH", d, s["off"] + j * 16)
                    self.syms.append(dict(name=self._str(st, nm), value=val, size=sz,
                                          type=info & 0xF, bind=info >> 4, shndx=shndx))
        self.relas = {}  # target section index -> [(offset, type, sym, addend)]
        for s in self.secs:
            if s["type"] == 4:  # RELA
                lst = self.relas.setdefault(s["info"], [])
                for j in range(s["size"] // 12):
                    off, info, add = struct.unpack_from(">IIi", d, s["off"] + j * 12)
                    lst.append((off, info & 0xFF, info >> 8, add))
        self.sec_index = {s["name"]: i for i, s in enumerate(self.secs)}

    def _str(self, sec, off):
        b = self.d[sec["off"] + off:]
        return b[:b.index(0)].decode("latin-1")

    def data(self, idx, off, n):
        s = self.secs[idx]
        if s["type"] == 8:  # NOBITS
            return b"\0" * n
        return self.d[s["off"] + off:s["off"] + min(off + n, s["size"])]

    def functions(self):
        """name -> (section index, start, size) of every function symbol."""
        out = {}
        for s in self.syms:
            if s["type"] == 2 and s["shndx"] < len(self.secs) and s["name"]:
                out.setdefault(s["name"], (s["shndx"], s["value"], s["size"]))
        return out

    def object_at(self, idx, addr):
        """(start, size) of the sized symbol in section idx that contains addr."""
        best = None
        for s in self.syms:
            if s["shndx"] == idx and s["size"] and s["value"] <= addr < s["value"] + s["size"]:
                if best is None or s["size"] < best[1]:
                    best = (s["value"], s["size"])
        return best

    def defined(self):
        if not hasattr(self, "_defined"):
            self._defined = {s["name"]: s for s in self.syms
                             if s["name"] and 0 < s["shndx"] < len(self.secs)}
        return self._defined

    def has_relocs(self, idx, start, end):
        return any(start <= o < end for o, *_ in self.relas.get(idx, []))


# ---------------------------------------------------------------- values ------------

def fval(bits, kind):
    if kind == "f":
        v = struct.unpack(">f", struct.pack(">I", bits))[0]
        return f"{v:.9g}" if v == v else f"nan(0x{bits:08X})"
    v = struct.unpack(">d", struct.pack(">Q", bits))[0]
    return f"{v:.17g}" if v == v else f"nan(0x{bits:016X})"


def tok_float(b, kind):
    if kind == "f":
        (bits,) = struct.unpack(">I", b)
        return ("f", fval(bits, "f"))
    (bits,) = struct.unpack(">Q", b)
    if bits >> 32 == 0x43300000:
        return ("i2f", "")  # int->float conversion magic: signed/unsigned both count as one
    return ("d", fval(bits, "d"))


def num(tok):
    """Numeric value of a float/double token (None for anything else, or NaN)."""
    if tok[0] in ("f", "d") and not tok[1].startswith("nan"):
        return float(tok[1])
    return None


def show(tok):
    k, v = tok
    if k == "f":
        return v + "f"
    if k == "d":
        return v
    if k == "i2f":
        return "<int->float>"
    if k == "str":
        return json.dumps(v)
    return f"{k}:{v}"


def as_string(b, sized):
    """The string at the start of b, if it looks like one. `sized`: b is exactly one
    object (a symbol's extent); without that, short strings are not trusted: a float
    like 0x435C0000 reads as "C\\"."""
    if 0 not in b:
        return None
    s = b[:b.index(0)]
    short = len(s) < 4
    if short and not (sized and len(b) == len(s) + 1):
        return None
    if not all(32 <= c < 127 or c in (9, 10, 13) or (c >= 0x80 and not short) for c in s):
        return None
    if any(c >= 0x80 for c in s):  # Japanese text: must be valid Shift-JIS
        try:
            s.decode("shift_jis")
        except UnicodeDecodeError:
            return None
    return s.decode("latin-1")


_LITS = None


def target_literals():
    """name -> (Elf, symbol) for every .sdata2/.rodata symbol the target objects define, to
    resolve references to literals that live in another unit."""
    global _LITS
    if _LITS is None:
        _LITS = {}
        for u in json.loads((ROOT / "objdiff.json").read_text())["units"]:
            p = ROOT / u["target_path"]
            if not p.exists():
                continue
            e = Elf(p)
            for nm, sym in e.defined().items():
                if e.secs[sym["shndx"]]["name"] in LIT_SECTIONS:
                    _LITS.setdefault(nm, (e, sym))
    return _LITS


def split_block(b):
    """Values a pooled block (addressed through a base register) may hold."""
    out = set()
    for i in range(0, len(b) - 3, 4):
        out.add(tok_float(b[i:i + 4], "f"))
        out.add(("u32", "0x%08X" % struct.unpack(">I", b[i:i + 4])))
        if i % 8 == 0 and i + 8 <= len(b):
            out.add(tok_float(b[i:i + 8], "d"))
    for i in range(0, len(b) - 1, 2):
        out.add(("u16", "0x%04X" % struct.unpack(">H", b[i:i + 2])))
    for c in b:
        out.add(("u8", "0x%02X" % c))
    s = as_string(b, True)
    if s is not None:
        out.add(("str", s))
    return out


def blob_covered(b, other):
    """Every word of a pooled block shows up on the other side (as a float, double, int,
    or inside a block), or is zero padding."""
    nums = {num(t) for t in other} - {None}
    words = [b[i:i + 4] for i in range(0, len(b) - 3, 4)]
    for i, w in enumerate(words):
        if w == b"\0\0\0\0":
            continue
        f = tok_float(w, "f")
        if f in other or num(f) in nums or ("u32", "0x%08X" % struct.unpack(">I", w)) in other:
            continue
        j = i & ~1
        if 8 * (j // 2) + 8 <= len(b) and tok_float(b[4 * j:4 * j + 8], "d") in other | {("i2f", "")}:
            continue
        d = tok_float(b[4 * j:4 * j + 8], "d") if 4 * j + 8 <= len(b) else None
        if d is not None and (d in other or num(d) in nums):
            continue
        return False
    return True


LOADS = {48: 4, 49: 4, 50: 8, 51: 8, 56: 8, 32: 4, 33: 4, 40: 2, 41: 2, 42: 2, 43: 2, 34: 1, 35: 1}
X_LOADS = {23, 55, 87, 119, 279, 311, 343, 375, 535, 567, 599, 631}  # lwzx lbzx lhzx lhax lfsx lfdx (+u)
X_STORES = {151, 183, 215, 247, 407, 439, 663, 695, 727, 759, 918, 662, 983, 150}
INT_WRITE_RD = {7, 8, 12, 13, 14, 15, 32, 33, 34, 35, 40, 41, 42, 43, 46}
INT_WRITE_RA = {20, 21, 23, 24, 25, 26, 27, 28, 29}


def load_tok(src, sidx, addr, op):
    if addr < 0 or addr + LOADS[op] > src.secs[sidx]["size"]:
        return None  # not really through this base (a register reused on another path)
    if op in (48, 49):
        return tok_float(src.data(sidx, addr, 4), "f")
    if op in (50, 51):
        return tok_float(src.data(sidx, addr, 8), "d")
    if op == 56:
        b = src.data(sidx, addr, 8)
        return ("ps", f"{show(tok_float(b[:4], 'f'))},{show(tok_float(b[4:], 'f'))}")
    if op in (32, 33):
        return ("u32", "0x%08X" % struct.unpack(">I", src.data(sidx, addr, 4)))
    if op in (40, 41, 42, 43):
        return ("u16", "0x%04X" % struct.unpack(">H", src.data(sidx, addr, 2)))
    return ("u8", "0x%02X" % src.data(sidx, addr, 1)[0])


def addr_tok(src, sidx, addr):
    """Token for an address taken (passed on, indexed): a string, or the object's bytes;
    None for a table of pointers (switch jump table etc.)."""
    obj = src.object_at(sidx, addr)
    end = obj[0] + obj[1] if obj else min(addr + 256, src.secs[sidx]["size"])
    b = src.data(sidx, addr, end - addr)
    s = as_string(b, bool(obj) and obj[0] == addr)
    if s is not None:
        return ("str", s), set()
    if src.has_relocs(sidx, addr, end):
        return None, set()
    return ("blob", b.hex() if len(b) <= 32 else b[:32].hex() + "..."), split_block(b)


def fn_literals(elf, fname, ext=None):
    """(multiset of value tokens, set of tokens inside pooled blocks, set of callees).
    Walks the function: a load with a literal relocation gives its value directly; an
    address (addi lbl@l) becomes a base register, followed through addi/mr, and each
    `lfs fN, d(rBase)` etc. gives the value at base + d. A base that is passed on,
    stored or indexed gives its string, or its object's bytes (a "blob").
    `ext` resolves undefined symbols (our C naming the target's lbl_N_rodata_ADDR as an
    extern, or a literal another unit holds): name -> (Elf, symbol), see target_literals()."""
    idx, start, size = elf.functions()[fname]
    text = elf.secs[idx]
    toks, pooled, callees = collections.Counter(), set(), set()
    rel = {}
    for off, rtype, si, add in elf.relas.get(idx, []):
        if not (start <= off < start + size):
            continue
        sym = elf.syms[si]
        if rtype in (10, 11):  # REL24/REL14: calls
            if sym["type"] == 2 or sym["shndx"] == 0:
                callees.add(sym["name"])
            continue
        if rtype not in (4, 109):  # ADDR16_LO, EMB_SDA21 (HA/HI belong to the LO)
            continue
        src = elf
        if sym["shndx"] == 0 and ext is not None and sym["name"] in ext:
            src, sym = ext[sym["name"]]
        if sym["shndx"] >= len(src.secs) or src.secs[sym["shndx"]]["name"] not in LIT_SECTIONS:
            continue
        rel[off & ~3] = (src, sym["shndx"], sym["value"] + add)
    regs, bases = {}, []  # reg -> base; base = [src, sidx, addr, used, escaped]
    for off in range(start, start + size, 4):
        (insn,) = struct.unpack_from(">I", elf.d, text["off"] + off)
        op, rd, ra, rb = insn >> 26, (insn >> 21) & 31, (insn >> 16) & 31, (insn >> 11) & 31
        d = (insn & 0xFFFF) - ((insn & 0x8000) << 1)
        if off in rel:
            src, sidx, addr = rel[off]
            if op in LOADS:
                toks[load_tok(src, sidx, addr, op)] += 1
                if op in INT_WRITE_RD:
                    regs.pop(rd, None)
            elif op in (14, 24):  # addi/ori: an address in a register
                base = [src, sidx, addr, False, False]
                bases.append(base)
                regs[rd if op == 14 else ra] = base
            continue
        if op in LOADS and ra in regs and ra != 0:
            src, sidx, addr = regs[ra][:3]
            if op == 56:
                d = (insn & 0xFFF) - ((insn & 0x800) << 1)
            t = load_tok(src, sidx, addr + d, op)
            if t:
                toks[t] += 1
            regs[ra][3] = True
            if op in INT_WRITE_RD:
                regs.pop(rd, None)
            continue
        if op == 14 and ra in regs and ra != 0:  # addi rD, rBase, d
            b = regs[ra]
            b[3] = True
            nb = [b[0], b[1], b[2] + d, False, False]
            bases.append(nb)
            regs[rd] = nb
            continue
        if op == 18:  # branch: a call passes bases in r3-r10 on, and clobbers volatiles
            if insn & 1:
                for r in range(3, 11):
                    if r in regs:
                        regs[r][4] = True
                for r in [0] + list(range(3, 13)):
                    regs.pop(r, None)
            continue
        if op == 31:
            xo = (insn >> 1) & 0x3FF
            if xo == 444 and rd == rb:  # mr rA, rS
                if rd in regs:
                    regs[ra] = regs[rd]; regs[rd][3] = True
                else:
                    regs.pop(ra, None)
                continue
            if xo in X_LOADS:
                for r in (ra, rb):
                    if r in regs:
                        regs[r][4] = True
                regs.pop(rd, None) if xo not in (535, 567, 599, 631) else None
                continue
            if xo in X_STORES:
                if rd in regs and xo not in (663, 695, 727, 759, 983):
                    regs[rd][4] = True
                continue
            if xo == 266 and (ra in regs or rb in regs):  # add: indexing into the block
                regs[ra if ra in regs else rb][4] = True
            regs.pop(rd, None); regs.pop(ra, None)
            continue
        if op in (36, 37, 38, 39, 44, 45) and rd in regs:  # stw/stb/sth of a base: stored
            regs[rd][4] = True
            continue
        if op in INT_WRITE_RD:
            regs.pop(rd, None)
        elif op in INT_WRITE_RA:
            regs.pop(ra, None)
    for b in bases:
        if b[4] or not b[3]:
            t, pool = addr_tok(b[0], b[1], b[2])
            if t:
                toks[t] += 1
                pooled |= pool
    return toks, pooled, callees


# ---------------------------------------------------------------- source ------------

def nm_functions(src_text):
    """Names of functions defined inside `#if NONMATCHING` blocks."""
    out, depth, inside = set(), 0, []
    for line in src_text.splitlines():
        s = line.strip()
        if re.match(r"#\s*if", s):
            inside.append(bool(re.match(r"#\s*if\s+NONMATCHING\b", s)))
        elif re.match(r"#\s*endif", s) and inside:
            inside.pop()
        elif any(inside):
            m = re.match(r"^[A-Za-z_][^;(]*?\b(\w+)\s*\(", line)
            if m and not s.endswith(";"):
                out.add(m.group(1))
    return out


def reviewed(src_text, fn):
    """Text of `// litcheck:` lines in the comment block above fn's definition."""
    lines = src_text.splitlines()
    for i, l in enumerate(lines):
        if re.match(rf"^[A-Za-z_][^;(]*\b{re.escape(fn)}\s*\(", l) and not l.rstrip().endswith(";"):
            notes, j = [], i - 1
            while j >= 0 and re.match(r"^\s*(//|#if|$)", lines[j]):
                m = re.search(r"litcheck:(.*)", lines[j])
                if m:
                    notes.append(m.group(1))
                j -= 1
            return " ".join(notes) if notes else None
    return None


def waived_by(note, tok):
    if note is None:
        return False
    if re.search(r"\ball\b", note):
        return True
    s = show(tok)
    if tok[0] in ("f", "d"):
        num = tok[1]
        for w in re.findall(r"-?[0-9][0-9.eE+\-]*f?|-?inf|nan", note):
            w = w.rstrip("f")
            try:
                if float(w) == float(num) or w == num:
                    return True
            except ValueError:
                pass
        return False
    return s in note


# ---------------------------------------------------------------- compare -----------

def compare(tgt, ours, src_text, fname, counts, verbose, label):
    tf, of = tgt.functions(), ours.functions()
    lits = target_literals()
    tt, tp, tc = fn_literals(tgt, fname, lits)
    ot, op, oc = fn_literals(ours, fname, lits)
    # a stub (or missing C): nothing to compare
    if not ot and of[fname][2] * 2 < tf[fname][2]:
        return None
    if not counts:
        tt = collections.Counter(set(tt)); ot = collections.Counter(set(ot))
    tonly, oonly = tt - ot, ot - tt
    if not tonly and not oonly:
        return []
    notes = []
    # helpers inlined on one side: their literals count for the caller
    for callee in sorted((oc - tc) | (tc - oc)):
        side = ours if callee in of else (tgt if callee in tf else None)
        if side is None or callee == fname:
            continue
        ht, hp, _ = fn_literals(side, callee, lits)
        hs = set(ht) | hp
        if callee in oc and callee not in tc:  # original inlined it
            hit = [t for t in tonly if t in hs]
        else:
            hit = [t for t in oonly if t in hs]
        if hit:
            notes.append(f"inlined {callee}: {', '.join(map(show, hit))}")
            for t in hit:
                tonly.pop(t, None) if callee in oc else oonly.pop(t, None)
    # values inside a pooled block on the other side
    for a, pool, nm in ((oonly, tp, "target"), (tonly, op, "ours")):
        nums = {num(p) for p in pool} - {None}
        hit = [t for t in a if t in pool or num(t) in nums]
        if hit:
            notes.append(f"in {nm} pooled block: {', '.join(map(show, hit))}")
            for t in hit:
                a.pop(t)
    # pooled blocks themselves are compared through their contents
    for a, b, pool in ((tonly, ot, op), (oonly, tt, tp)):
        for t in [t for t in a if t[0] == "blob"]:
            if not t[1].endswith("...") and blob_covered(bytes.fromhex(t[1]), set(b) | pool):
                a.pop(t)
    note = reviewed(src_text, fname)
    for a in (tonly, oonly):
        for t in [t for t in a if waived_by(note, t)]:
            notes.append(f"litcheck note: {show(t)}"); a.pop(t)
    if verbose and notes:
        print(f"{label}: {fname}: ok: " + "; ".join(notes))
    if not tonly and not oonly:
        return []
    return [", ".join(f"{show(t)}" + (f" x{n}" if n > 1 else "") for t, n in sorted(tonly.items())),
            ", ".join(f"{show(t)}" + (f" x{n}" if n > 1 else "") for t, n in sorted(oonly.items()))]


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("sources", nargs="*")
    ap.add_argument("--all", action="store_true")
    ap.add_argument("--fn", help="only this function")
    ap.add_argument("--counts", action="store_true", help="compare how often each value is loaded too")
    ap.add_argument("-v", "--verbose", action="store_true", help="also list differences that were accepted")
    args = ap.parse_args()

    units = [u for u in json.loads((ROOT / "objdiff.json").read_text())["units"]
             if u.get("base_path") and u["metadata"].get("source_path")]
    report = {u["name"]: {f["name"]: f.get("fuzzy_match_percent", 0) for f in u.get("functions", [])}
              for u in json.loads((ROOT / "build/GYQE01/report.json").read_text())["units"]}
    if args.fn and not args.sources and not args.all:
        unit = next((n for n, fs in report.items() if args.fn in fs), None)
        if not unit:
            sys.exit(f"{args.fn} not in report.json")
        args.sources = [next(u["metadata"]["source_path"] for u in units if u["name"] == unit)]
    if not args.all:
        want = {str(Path(s).resolve().relative_to(ROOT)) if Path(s).is_absolute() else s for s in args.sources}
        units = [u for u in units if u["metadata"]["source_path"] in want]
    flagged = checked = 0
    for u in units:
        src = u["metadata"]["source_path"]
        src_text = (ROOT / src).read_text(errors="replace")
        tpath = ROOT / u["target_path"]
        if not tpath.exists():
            continue
        tgt = Elf(tpath)
        nm = nm_functions(src_text) if re.search(r"^#if\s+NONMATCHING", src_text, re.M) else set()
        if nm:
            with tempfile.TemporaryDirectory() as d:
                import contextlib, io
                with contextlib.redirect_stdout(io.StringIO()) as out:
                    ok = nmcheck.check(src, d + "/nm.o")
                if not ok:
                    print(out.getvalue().strip()); flagged += 1; continue
                ours = Elf(d + "/nm.o")
        else:
            bpath = ROOT / u["base_path"]
            if not bpath.exists():
                continue
            ours = Elf(bpath)
        tf, of = tgt.functions(), ours.functions()
        for fname in tf:
            if fname not in of or (args.fn and fname != args.fn):
                continue
            if tf[fname][0] != tgt.sec_index.get(".text") and tgt.secs[tf[fname][0]]["name"] != ".text":
                continue
            r = compare(tgt, ours, src_text, fname, args.counts, args.verbose, src)
            if r is None:
                continue
            checked += 1
            if r:
                flagged += 1
                pct = report.get(u["name"], {}).get(fname)
                kind = "equivalent" if fname in nm else ("matched" if pct == 100 else f"{pct or 0:.0f}%")
                print(f"{src}: {fname} ({kind}): target-only [{r[0]}]  ours-only [{r[1]}]")
    print(f"{checked} function(s) checked, {flagged} flagged")
    sys.exit(1 if flagged else 0)


if __name__ == "__main__":
    main()
