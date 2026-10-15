#!/usr/bin/env python3
"""Merges pipeline lists from web runs into port/web/initial_pipeline_cache.bin.gz.

The web build appends every GPU pipeline config it uses to /mssb/pipeline_cache.bin
(aurora's lib/gfx/pipeline_cache.cpp, "AUPC" format). The page ships a merged copy
(gzipped, the page unpacks it) so the pipelines compile in the background at boot instead of stalling a frame
the first time an effect shows up. Collect lists with web_drive.mjs:

    node port/tools/web_drive.mjs --secs 300 --query '...' --fetch /mssb/pipeline_cache.bin:build/pipes/x.bin
    python3 port/tools/pipeline_seed.py build/pipes/*.bin        # merge into the seed (keeps its entries)
    python3 port/tools/pipeline_seed.py --stats port/web/initial_pipeline_cache.bin.gz

The page compiles them in file order. On WebKit that happens only while the game allows it (the
loading screen and intro before a game: port/game/views.c), so --first puts the pipelines the
listed runs (games) use first, in the order they showed up there:

    python3 port/tools/pipeline_seed.py --replace build/pipes2/*.bin --first build/pipes2/ms-*.bin
"""
import argparse
import gzip
import struct
import sys
from pathlib import Path

MAGIC = 0x43505541
SCHEMA = 1
SEED = Path(__file__).resolve().parents[1] / "web" / "initial_pipeline_cache.bin.gz"
REC = struct.Struct("<B3xIII")  # type, configVersion, configSize, firstFrameUsed


def read(path):
    data = Path(path).read_bytes()
    if data[:2] == b"\x1f\x8b":
        data = gzip.decompress(data)
    if len(data) < 8:
        return []
    magic, schema = struct.unpack_from("<II", data)
    if magic != MAGIC or schema != SCHEMA:
        sys.exit(f"{path}: not a pipeline list (schema {SCHEMA})")
    out, pos = [], 8
    while pos + REC.size <= len(data):
        kind, version, size, first = REC.unpack_from(data, pos)
        pos += REC.size
        if size > len(data) - pos:
            break
        out.append((kind, version, data[pos:pos + size], first))
        pos += size
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("inputs", nargs="+")
    ap.add_argument("--out", default=str(SEED))
    ap.add_argument("--stats", action="store_true", help="only print what the inputs hold")
    ap.add_argument("--replace", action="store_true", help="don't keep the existing seed's entries")
    ap.add_argument("--first", nargs="+", default=[], help="these runs' pipelines go first (also merged)")
    args = ap.parse_args()

    inputs = list(args.inputs) + [p for p in args.first if p not in args.inputs]
    if not args.stats and not args.replace and Path(args.out).exists() and args.out not in inputs:
        inputs.insert(0, args.out)
    merged = {}
    for path in inputs:
        recs = read(path)
        new = 0
        for kind, version, config, first in recs:
            key = (kind, version, config)
            if key not in merged:
                new += 1
                merged[key] = first
            else:
                merged[key] = min(merged[key], first)
        print(f"{path}: {len(recs)} pipelines, {new} new")
    versions = sorted({(k, v) for k, v, _ in merged})
    print(f"total {len(merged)} pipelines (type, version: {versions})")
    if args.stats:
        return
    # Newest config version per type only: older ones are skipped at load anyway.
    newest = {}
    for kind, version in versions:
        newest[kind] = max(newest.get(kind, 0), version)
    # --first runs' pipelines in the order they showed up there, then the rest.
    early = {}
    for path in args.first:
        for kind, version, config, first in read(path):
            key = (kind, version, config)
            early[key] = min(early.get(key, first), first)
    rows = sorted(((first, kind, version, config) for (kind, version, config), first in merged.items()
                   if newest[kind] == version),
                  key=lambda r: (r[1:] not in early, early.get(r[1:], r[0]), r[1]))
    blob = bytearray(struct.pack("<II", MAGIC, SCHEMA))
    # The page sorts by first frame used: number them in file order.
    for order, (first, kind, version, config) in enumerate(rows):
        blob += REC.pack(kind, version, len(config), order if early else first) + config
    packed = gzip.compress(bytes(blob), 9, mtime=0) if args.out.endswith(".gz") else bytes(blob)
    Path(args.out).write_bytes(packed)
    print(f"wrote {args.out}: {len(rows)} pipelines ({sum(r[1:] in early for r in rows)} first), {len(packed)} bytes")


if __name__ == "__main__":
    main()
