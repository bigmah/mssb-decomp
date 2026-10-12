#!/usr/bin/env python3
"""Extract (and decompress) one game asset from the disc, as ARAMTransfer would.

  port/tools/assetfile.py <compConsts> <sizeFlags> <diskLocation> <compressedSize> [out]
      the four fields of a DiskFileEntry/AssetLoadInstructions (any int syntax);
      offsets are into ZZZZ.dat (MSSB_DAT=/aaaa.dat for the REL archive)
  port/tools/assetfile.py --file aaaa.dat        list the FST path entries matching
Disc: $MSSB_ISO, else mario_baseball.iso in a parent folder of the checkout.
Writes the file to [out] (default: stdout as a hexdump of the first 256 bytes).
"""
import os, struct, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, ROOT)


def find_iso():
    env = os.environ.get('MSSB_ISO')
    if env:
        return env
    d = ROOT
    while True:
        p = os.path.join(d, 'mario_baseball.iso')
        if os.path.exists(p):
            return p
        nd = os.path.dirname(d)
        if nd == d:
            sys.exit('disc not found: set MSSB_ISO')
        d = nd


class Disc:
    """Raw GCM or CISO image, read by disc offset."""
    def __init__(self, path):
        self.f = open(path, 'rb')
        hdr = self.f.read(0x8000)
        self.ciso = hdr[:4] == b'CISO'
        if self.ciso:
            self.bs = struct.unpack('<I', hdr[4:8])[0]
            self.map = []
            n = 0
            for b in hdr[8:]:
                self.map.append(n if b else None)
                n += 1 if b else 0
        self.pos = 0

    def seek(self, pos):
        self.pos = pos

    def read(self, size):
        if not self.ciso:
            self.f.seek(self.pos)
            out = self.f.read(size)
        else:
            out = bytearray()
            while size > 0:
                blk, off = divmod(self.pos, self.bs)
                n = min(size, self.bs - off)
                if self.map[blk] is None:
                    out += bytes(n)
                else:
                    self.f.seek(0x8000 + self.map[blk] * self.bs + off)
                    out += self.f.read(n)
                self.pos += n
                size -= n
            return bytes(out)
        self.pos += len(out)
        return out


def fst(iso):
    f = Disc(iso)
    f.seek(0x424)
    off, size = struct.unpack('>II', f.read(8))
    f.seek(off)
    t = f.read(size)
    n = struct.unpack('>I', t[8:12])[0]
    strtab = t[n * 12:]
    out = {}
    dirs = [(n, '')]
    for i in range(1, n):
        while dirs and i >= dirs[-1][0]:
            dirs.pop()
        e = t[i * 12:i * 12 + 12]
        noff = struct.unpack('>I', b'\0' + e[1:4])[0]
        a, b = struct.unpack('>II', e[4:12])
        name = strtab[noff:strtab.index(b'\0', noff)].decode('latin1')
        path = (dirs[-1][1] if dirs else '') + '/' + name
        if e[0]:
            dirs.append((b, path))
        else:
            out[path] = (a, b)
    return f, out


def main():
    iso = find_iso()
    f, files = fst(iso)
    if sys.argv[1] == '--file':
        for p, (o, s) in files.items():
            if sys.argv[2] in p:
                print('%-40s off 0x%x size 0x%x' % (p, o, s))
        return
    cc, sf, loc, cs = (int(x, 0) for x in sys.argv[1:5])
    base = files[os.environ.get('MSSB_DAT', '/ZZZZ.dat')][0]
    f.seek(base + loc)
    data = f.read((cs + 31) & ~31)
    flag = sf >> 30
    size = sf & 0x0FFFFFFF
    if flag:
        from decompress import ArchiveDecompressor
        d = ArchiveDecompressor(data, cc & 0xFF, (cc >> 8) & 0xFF, size)
        data = bytes(d.decompress())
    else:
        data = data[:cs]
    if len(sys.argv) > 5:
        open(sys.argv[5], 'wb').write(data)
        print('%d bytes' % len(data), file=sys.stderr)
    else:
        for i in range(0, min(256, len(data)), 16):
            print('%06x  %s' % (i, data[i:i + 16].hex(' ')))


if __name__ == '__main__':
    main()
