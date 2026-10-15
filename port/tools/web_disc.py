#!/usr/bin/env python3
"""Builds the web disc's keep-list: the parts of the disc image the web build
can reach (Exhibition at Mario Stadium, Practice, Options, every character),
as the image's 512 KB chunks (port/web/web_disc.json). The deploy
(port/tools/deploy_cloudflare.sh) lists them in disc/manifest.json; the page
downloads them once into the browser's storage (port/web/loader.js) and
fetches anything else from the full disc, logging it under ?debug.

  port/tools/web_disc.py [recordings...]   default: build/disc-reads/*.json
  port/tools/web_disc.py --report          what's kept, by file and table

The keep-list is the union of
  - recorded sessions (port/tools/record_disc_reads.mjs), each touched range
    widened to the whole ZZZZ.dat entry it belongs to (the game's file tables
    in main.dol and the RELs) or the whole file (music, aaaa.dat, ...);
  - the disc header, FST and main.dol;
  - every entry of the character-indexed file tables, so a character no
    recording happened to use is still there;
  - the always-kept music (KEEP_FILES).
Offsets in the recordings and the output are the image file's own (a CISO
image's, not the disc's): the page reads the image file as it is deployed.
"""
import bisect, glob, json, os, struct, sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import assetfile  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
OUT = os.path.join(ROOT, 'port/web/web_disc.json')
CHUNK = 512 * 1024  # the deploy's chunk size (deploy_cloudflare.sh)
ZZZZ = '/ZZZZ.dat'

# Music the playable modes use, kept whole whether or not a recording played
# all of it: Mario Stadium, the replay and result screens, the walk-in.
KEEP_FILES = [
    '/snd/my_snd_h/mario_01_h.adp',
    '/snd/my_snd_h/replay_h.adp',
    '/snd/my_snd_h/result_h.adp',
    '/snd/my_snd_h/home_in_h.adp',
    '/opening.bnr',
    '/aaaa.dat',
]

# Executables and their symbol files, for the file tables.
MODULES = [
    ('main', 'orig/GYQE01/sys/main.dol', 'config/GYQE01/symbols.txt'),
    ('game', 'orig/GYQE01/files/game.rel', 'config/GYQE01/game/symbols.txt'),
    ('menus', 'orig/GYQE01/files/menus.rel', 'config/GYQE01/menus/symbols.txt'),
    ('challenge', 'orig/GYQE01/files/challenge.rel', 'config/GYQE01/challenge/symbols.txt'),
]
CHARACTERS = 54
MAX_ENTRY = 8 << 20


class Image:
    """Maps the image file's offsets to the disc's and back (CISO or plain)."""

    def __init__(self, path):
        self.disc, self.files = assetfile.fst(path)
        self.size = os.path.getsize(path)
        d = self.disc
        if d.ciso:
            self.where = {}  # disc block -> image offset
            for blk, used in enumerate(d.map):
                if used is not None:
                    self.where[blk] = 0x8000 + used * d.bs

    def to_image(self, start, end):
        """Image ranges holding disc bytes [start, end)."""
        d = self.disc
        if not d.ciso:
            return [(start, end)]
        out = []
        pos = start
        while pos < end:
            blk, off = divmod(pos, d.bs)
            n = min(end - pos, d.bs - off)
            if blk in self.where:
                out.append((self.where[blk] + off, self.where[blk] + off + n))
            pos += n
        return out

    def to_disc(self, start, end):
        """Disc ranges for image bytes [start, end) (the CISO header maps to the disc's start)."""
        d = self.disc
        if not d.ciso:
            return [(start, end)]
        out = []
        if start < 0x8000:
            out.append((0, 0x440))
            start = 0x8000
        inv = {v: k for k, v in self.where.items()}
        pos = start
        while pos < end:
            base = 0x8000 + ((pos - 0x8000) // d.bs) * d.bs
            n = min(end - pos, base + d.bs - pos)
            if base in inv:
                a = inv[base] * d.bs + pos - base
                out.append((a, a + n))
            pos += n
        return out

    def file_at(self, disc_off):
        for p, (o, s) in self.files.items():
            if o <= disc_off < o + s:
                return p, o, s
        return None


def symbols(path):
    out = []
    for line in open(os.path.join(ROOT, path)):
        parts = line.split()
        if len(parts) < 3 or 'size:0x' not in line:
            continue
        sec, addr = parts[2].rstrip(';').split(':')
        size = int(line.split('size:0x')[1].split()[0], 16)
        out.append((sec, int(addr, 16), size, parts[0]))
    return out


def file_tables(zsize):
    """{(module, symbol): [(offset, size) in ZZZZ.dat, ...]}: 16-byte file table
    entries (DiskFileEntry: compression, flags|size, location, stored size)
    found in the executables' data, by the symbol holding them."""
    tables = {}
    for mod, path, symf in MODULES:
        d = open(os.path.join(ROOT, path), 'rb').read()
        syms = symbols(symf)
        if mod == 'main':
            offs = struct.unpack('>18I', d[0:72])
            addrs = struct.unpack('>18I', d[72:144])
            sizes = struct.unpack('>18I', d[144:216])
            secs = [(o, a, s, None) for o, a, s in zip(offs, addrs, sizes) if s]
        else:
            n, off = struct.unpack('>II', d[0xC:0x14])
            secs = []
            for i in range(n):
                o, s = struct.unpack('>II', d[off + i * 8:off + i * 8 + 8])
                if o & ~1 and s:
                    secs.append((o & ~1, 0, s, {4: '.rodata', 5: '.data'}.get(i)))

        def label(o):
            for so, a, s, name in secs:
                if so <= o < so + s:
                    addr = a + o - so
                    for sec, sa, sz, nm in syms:
                        if sa <= addr < sa + sz and (name is None or sec == name):
                            return nm
            return None

        for o in range(0, len(d) - 16, 4):
            cc, sf, loc, cs = struct.unpack('>IIII', d[o:o + 16])
            size, flag = sf & 0x0FFFFFFF, sf >> 28
            if not (cc < 0x10000 and 0 < cs <= size + 64 and size < 0x4000000 and loc % 32 == 0
                    and loc + cs <= zsize and flag in (0, 4, 8, 0xC) and (flag or cs == size)):
                continue
            sym = label(o)
            if sym:
                tables.setdefault((mod, sym), []).append((loc, (cs + 31) & ~31))
    return tables


def merge(ranges):
    out = []
    for a, b in sorted(ranges):
        if out and a <= out[-1][1]:
            out[-1][1] = max(out[-1][1], b)
        else:
            out.append([a, b])
    return out


def build(paths, report=False):
    img = Image(assetfile.find_iso())
    zoff, zsize = img.files[ZZZZ]
    tables = file_tables(zsize)
    # Each ZZZZ.dat entry once, and which tables list it.
    entries = {}
    for key, es in tables.items():
        for e in es:
            entries.setdefault(e, set()).add(key)
    starts = sorted(entries)

    recorded = []  # disc ranges
    for p in paths:
        r = json.load(open(p))
        if r['size'] != img.size:
            sys.exit('%s was recorded on another disc image' % p)
        for off, n in r['ranges']:
            recorded += img.to_disc(off, off + n)
    recorded = merge(recorded)

    keep = []  # disc ranges, with a reason
    why = {}

    def add(a, b, reason):
        keep.append((a, b))
        why[reason] = why.get(reason, 0) + b - a

    add(0, 0x440, 'disc header')
    hdr = img.disc
    hdr.seek(0x420)
    dol, fst, fst_size = struct.unpack('>III', hdr.read(12))
    hdr.seek(dol)
    head = hdr.read(0x100)
    dol_size = max(o + s for o, s in zip(struct.unpack('>18I', head[0:72]), struct.unpack('>18I', head[0x90:0xD8])))
    add(0x440, 0x2440, 'disc header')  # bi2.bin
    add(0x2440, dol, 'apploader')
    add(dol, dol + dol_size, 'main.dol')
    add(fst, fst + fst_size, 'FST')

    touched_tables = {}  # table -> entries the recordings read
    for a, b in recorded:
        if zoff <= a < zoff + zsize:
            # The ZZZZ.dat entries this read starts (the game reads an entry
            # from its start), whole. The table scan is a heuristic, so an
            # "entry" bigger than any real one is noise.
            lo, hi = a - zoff, b - zoff
            for e in starts[bisect.bisect_left(starts, (lo, 0)):]:
                if e[0] >= hi:
                    break
                if e[1] <= MAX_ENTRY:
                    add(zoff + e[0], zoff + e[0] + e[1], 'ZZZZ.dat entries (recorded)')
                    for t in entries[e]:
                        touched_tables.setdefault(t, set()).add(e)
            add(a, b, 'ZZZZ.dat (recorded reads)')
        else:
            f = img.file_at(a)
            if f and f[0] != '/opening.bnr':
                add(f[1], f[1] + f[2], f[0])
            else:
                add(a, b, 'system area (recorded)')
    for p in KEEP_FILES:
        o, s = img.files[p]
        add(o, o + s, p)
    # Tables the recordings used most of (per-captain menu assets, say) or that
    # have one entry per character: all of their entries, for the rare one no
    # recording happened to load.
    for key, es in tables.items():
        used = len(touched_tables.get(key, ()))
        if used and (len(es) == CHARACTERS or 2 * used >= len(es)):
            for loc, n in es:
                if n <= MAX_ENTRY:
                    add(zoff + loc, zoff + loc + n, 'ZZZZ.dat tables, whole')

    keep = merge(keep)
    image = merge(r for a, b in keep for r in img.to_image(a, b))
    chunks = sorted({i for a, b in image for i in range(a // CHUNK, (b - 1) // CHUNK + 1)})
    data = sum(b - a for a, b in image)

    if report:
        print('recordings: %d, %.1f MB read' % (len(paths), sum(b - a for a, b in recorded) / 2**20))
        print('kept by reason (overlapping):')
        for k, v in sorted(why.items(), key=lambda kv: -kv[1]):
            print('  %-40s %7.1f MB' % (k, v / 2**20))
        merged = merge(keep)
        byfile = {}
        for p, (o, n) in img.files.items():
            got = sum(max(0, min(b, o + n) - max(a, o)) for a, b in merged)
            if got:
                byfile[p] = got
        byfile['(system)'] = sum(b - a for a, b in merged) - sum(byfile.values())
        print('kept by file:')
        for k, v in sorted(byfile.items(), key=lambda kv: -kv[1]):
            print('  %-40s %7.1f MB' % (k, v / 2**20))
        print('tables the recordings used (entries used / entries):')
        for k, used in sorted(touched_tables.items(), key=lambda kv: -sum(e[1] for e in tables[kv[0]])):
            es = tables[k]
            print('  %-10s %-24s %4d / %4d  %6.1f MB' % (k[0], k[1], len(used), len(es), sum(e[1] for e in es) / 2**20))
    print('keep-list: %.1f MB of data in %d chunks (%.1f MB to download) of %d' % (
        data / 2**20, len(chunks), len(chunks) * CHUNK / 2**20, (img.size + CHUNK - 1) // CHUNK))
    return img.size, chunks, image


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    paths = args or sorted(glob.glob(os.path.join(ROOT, 'build/disc-reads/*.json')))
    if not paths:
        sys.exit('no recordings: run port/tools/record_disc_reads.mjs first')
    size, chunks, image = build(paths, report='--report' in sys.argv)
    if '--dry-run' not in sys.argv:
        with open(OUT, 'w') as f:
            json.dump({'size': size, 'chunk': CHUNK, 'chunks': chunks}, f, separators=(',', ':'))
            f.write('\n')
        print('->', os.path.relpath(OUT, ROOT))


if __name__ == '__main__':
    main()
