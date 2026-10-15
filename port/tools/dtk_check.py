#!/usr/bin/env python3
"""Checks the music stream state a ?debug page logged ("[dtk] ... base B pos P filled F ... sum4k S",
port/src/audio/dtk.cpp port_dtk_debug_state) against the disc: does the stream hold the disc's
bytes where it's playing?

    python3 port/tools/dtk_check.py build/wrangler-tail.log [mario_baseball.iso]
"""
import re
import sys

LINE = re.compile(r"\[(\w+)\] ([\d.]+) warn \[dtk\] .*base (-?\d+) pos (\d+) filled (\d+) size (\d+) .*sum4k ([0-9A-F]+)")


class Disc:
    """A plain image or a CISO one (header "CISO", u32 block size, a 1-byte-per-block map)."""

    def __init__(self, path):
        self.f = open(path, "rb")
        head = self.f.read(0x8000)
        self.ciso = head[:4] == b"CISO"
        if self.ciso:
            self.block = int.from_bytes(head[4:8], "little")
            self.where, n = {}, 0
            for i, used in enumerate(head[8:]):
                if used:
                    self.where[i] = 0x8000 + n * self.block
                    n += 1

    def read(self, offset, n):
        if not self.ciso:
            self.f.seek(offset)
            return self.f.read(n)
        out = bytearray()
        while n > 0:
            i, within = divmod(offset, self.block)
            take = min(n, self.block - within)
            if i in self.where:
                self.f.seek(self.where[i] + within)
                out += self.f.read(take)
            else:
                out += bytes(take)
            offset += take
            n -= take
        return bytes(out)


def main():
    log = sys.argv[1]
    iso = sys.argv[2] if len(sys.argv) > 2 else "mario_baseball.iso"
    disc = Disc(iso)
    if True:
        for line in open(log, errors="replace"):
            m = LINE.search(line)
            if not m:
                continue
            session, t, base, pos, filled, size, want = m.groups()
            base, pos, filled = int(base), int(pos), int(filled)
            n = max(0, min(filled, pos + 4096) - pos)
            s = 0
            for b in disc.read(base + pos, n):
                s = (s * 31 + b) & 0xFFFFFFFF
            print(f"{session} {t}s: stream at {base}+{pos}: {'matches the disc' if f'{s:08X}' == want else f'DIFFERS from the disc ({want} vs {s:08X})'}")


if __name__ == "__main__":
    main()
